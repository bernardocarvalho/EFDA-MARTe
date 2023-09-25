/*
Michele's test to learn MARTe
**/

#include "RelayGAM.h"
#include "RelayGAMInputStructure.h"
#include "RelayGAMOutputStructure.h"
#include "CDBExtended.h"

#include "DDBInputInterface.h"
#include "DDBOutputInterface.h"

#include "LoadCDBObjectClass.h"

#define TSTARTDEFAULT    0.0
#define TENDDEFAULT    100.0

bool RelayGAM::Initialise(ConfigurationDataBase& cdbData) {

    CDBExtended cdb(cdbData);


    ////////////////////////////////////////////////////
    //                Add interfaces to DDB           //
    ////////////////////////////////////////////////////
    if(!AddInputInterface(input,"InputInterface")){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s failed to add input interface",Name());
        return False;
    }

    if(!AddOutputInterface(output,"OutputInterface")){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s failed to add output interface",Name());
        return False;
    }


    ////////////////////////////////////////////////////
    //                Add input signals               //
    ////////////////////////////////////////////////////
    if(!cdb->Move("InputSignals")){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s did not specify InputSignals entry",Name());
        return False;
    }

    if(!input->ObjectLoadSetup(cdb,NULL)){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s ObjectLoadSetup Failed DDBInterface %s ",Name(),input->InterfaceName());
        return False;
    }

    cdb->MoveToFather();




    ////////////////////////////////////////////////////
    //                Add output signals              //
    ////////////////////////////////////////////////////
    if(!cdb->Move("OutputSignals")){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s did not specify OutputSignals entry",Name());
        return False;
    }

    if(!output->ObjectLoadSetup(cdb,NULL)){
        AssertErrorCondition(InitialisationError,"RelayGAM::Initialise: %s ObjectLoadSetup Failed DDBInterface %s ",Name(),output->InterfaceName());
        return False;
    }

    cdb->MoveToFather();


    ////////////////////////////////////////////////////
    //               Controller enabled               //
    ////////////////////////////////////////////////////
    {
        FString tmp;
        controllerEnabled = True;
        if(cdb.ReadFString(tmp, "ControllerOn")) {
	    if (tmp == "OFF") {
	        controllerEnabled = False;
                AssertErrorCondition(Warning,"RelayGAM::Initialise: %s Relay is NOT enabled",Name());
	    }
        }
    }



    ////////////////////////////////////////////////////
    //            Time interval for control           //
    ////////////////////////////////////////////////////
    {
        CheckAndFreeDynamicMemory();

        int tStartLength = 1;
        int tEndLength   = 1;
	FString error;
        if(!LoadVectorObject(cdb, "TStart", (void*&)tStart, tStartLength, CDBTYPE_float, error)) {
            AssertErrorCondition(Information,"RelayGAM %s::Initialise: TStart entry not found, assuming %f secs", Name(), TSTARTDEFAULT);
	    tStart[0] = TSTARTDEFAULT;
	    tStartLength = 1;
        }
        if(!LoadVectorObject(cdb, "TEnd", (void*&)tEnd, tEndLength, CDBTYPE_float, error)) {
            AssertErrorCondition(Information,"RelayGAM %s::Initialise: TEnd entry not found, assuming %f secs", Name(), TENDDEFAULT);
	    tEnd[0] = TENDDEFAULT;
	    tEndLength = 1;
        }

	// Check if tStart and tEnd array lengths are the same, if not issue an error
	if(tStartLength != tEndLength) {
            AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: Time windows mismatch -> (tStartLength = %d) != (tEndLength = %d)", Name(), tStartLength, tEndLength);
	    return False;
	} else {
	    numberOfTimeWindows = tStartLength;
	}

	// Check if time windows are consistent in terms of tStart and tEnd
	for( int i = 0 ; i < numberOfTimeWindows ; i++ ){
	    if( tStart[i] >= tEnd[i] ){
	        AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: For time window %d the start time (%f) is larger than the end time (%f)", Name(), i, tStart[i], tEnd[i]);
                return False;
	    }
            if( i < numberOfTimeWindows - 1 ){
	        if( tStart[i+1] < tEnd[i] ){
	            AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: tStart for time window %d is smaller than tEnd for time window %d", Name(), i+1, i);
                    return False;
	        }
            }
	}
	AssertErrorCondition(Information, "RelayGAM %s::Initialise: %d time windows correctly setup", Name(), numberOfTimeWindows);

        // Allocate memory for tStartUsec and tEndUsec
        if((tStartUsec = (uint32 *)malloc(tStartLength*sizeof(uint32))) == NULL) {
            AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: unable to allocate memory for tStartUsec", Name());
            return False;
        }
        if((tEndUsec = (uint32 *)malloc(tStartLength*sizeof(uint32))) == NULL) {
            AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: unable to allocate memory for tEndUsec", Name());
            return False;
        }
        
        // Initialise window's microsecond start and end time
        for(int32 i = 0 ; i < tStartLength ; i++) {
            tStartUsec[i] = (uint32)(1e6*tStart[i]);
            tEndUsec[i]   = (uint32)(1e6*tEnd[i]);
        }
    }

    ////////////////////////////////////////////////////
    //                  Saturation                    //
    ////////////////////////////////////////////////////
    {

        // Saturation levels
        if(!cdb.ReadFloat(upperControlSaturation,"UpperControlSaturation")){
            AssertErrorCondition(InitialisationError,"RelayGAM %s::Initialise: UpperControlSaturation entry not found", Name());
            return False;
        }

        
        if(!cdb.ReadFloat(neutralValue,"neutralValue")){
            AssertErrorCondition(InitialisationError,"RelayGAM %s::Initialise: neutralValue entry not found", Name());
            return False;
        }

        if(!cdb.ReadFloat(lowerControlSaturation,"LowerControlSaturation")){
            AssertErrorCondition(InitialisationError,"RelayGAM %s::Initialise: LowerControlSaturation entry not found", Name());
            return False;
        }
    }

    return True;
}

bool RelayGAM::Execute(GAM_FunctionNumbers functionNumber) {

    // Get input and output data pointers
    RelayGAMInputStructure  *inputData  = (RelayGAMInputStructure  *)input->Buffer();
    RelayGAMOutputStructure *outputData = (RelayGAMOutputStructure *)output->Buffer();

    // Set all the outputs to zero
    outputData->controlSignal       = 0.0;
    outputData->error               = 0.0;

    switch(functionNumber) {
        case GAMPrepulse: {
            // Reset everything
            Reset();
        }
        default: {
            if(controllerEnabled) {
                input->Read();
                
                if(inputData->usecTime >= tStartUsec[currentTimeWindow] && inputData->usecTime <= tEndUsec[currentTimeWindow]) {
                    //float error = inputData->errorSignal;
                    float error            = inputData->reference - inputData->measurement;
                    float controlValue     = 0.0;

                    
                    // Calculate discharge action if enabled
                    if (fastDischargeEnabled) {
		        if((integrator*error) < 0) {
			    float absoluteErrorContribution = error*fastDischargeAbsoluteErrorScalingFactor;
			    if (fabs(absoluteErrorContribution) > fastDischargeAbsoluteErrorMaximumContribution) {
			        absoluteErrorContribution = absoluteErrorContribution*fastDischargeAbsoluteErrorMaximumContribution/fabs(absoluteErrorContribution);
			    }
			    dischargeAction = absoluteErrorContribution;
			} else {
			    dischargeAction = 0.0;
			}
                    }
                    
                    // Calculate the action
                    if(error>0){
                        controlValue=upperControlSaturation;
                    }
                    else{ 
                        controlValue=lowerControlSaturation;
                    }                    
                
                    
                    // Write signals to DDB
                    outputData->controlSignal       = controlValue;
                    outputData->error               = error;

                } else if(inputData->usecTime > tEndUsec[currentTimeWindow]) {
                    if(currentTimeWindow < numberOfTimeWindows-1) {
		        IsPreviousControlValueAvailable = False;
			previousControlValue = 0.0;
                        currentTimeWindow++;
                    }
                } else {
                    IsPreviousControlValueAvailable = False;
		    previousControlValue = 0.0;
                }
            } // end if controllerEnabled
        }
    }
    
    // Update the data output buffer
    output->Write();

    return True;
}





bool RelayGAM::ProcessHttpMessage(HttpStream &hStream) {
    hStream.SSPrintf("OutputHttpOtions.Content-Type","text/html");
    hStream.keepAlive = False;
    hStream.WriteReplyHeader(False);
    hStream.Printf("<html><head><title>Relay %s</title></head><body>\n", Name());

    hStream.Printf("<h1>Relay %s</h1>", Name());
    if (!controllerEnabled) hStream.Printf("<br><p style=\"color: 'red'\">CONTROLLER DISABLED</p><br>\n");

    hStream.Printf("<p>Upper saturation: %f</p>\n", upperControlSaturation);
    hStream.Printf("<p>Lower saturation: %f</p>\n", lowerControlSaturation);
    hStream.Printf("<p>Neutral value: %f</p>\n", neutralValue);
    


    hStream.Printf("</body></html>");
    hStream.WriteReplyHeader(True);
    return True;
}
OBJECTLOADREGISTER(RelayGAM,"$Id: RelayGAM.cpp 3 2012-01-15 16:26:07Z aneto $")

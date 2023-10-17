/*
Michele's test to learn MARTe
**/

#include "RelayGAM.h"
#include "CDBExtended.h"

#include "DDBInputInterface.h"
#include "DDBOutputInterface.h"


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

// Load parameter

    if(!cdb.ReadFloat(maxOut, "maxOut", 5.0)){
    AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: maxOut entry not found", Name());
    return False;
    }
    if(!cdb.ReadFloat(minOut, "minOut", 0.0)){
    AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: minOut entry not found", Name());
    return False;
    }
    if(!cdb.ReadFloat(tolerance, "tolerance", 1.0)){
    AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: tolerance entry not found", Name());
    return False;
    }
    if(!cdb.ReadFloat(reference, "reference", 1.0)){
    AssertErrorCondition(InitialisationError, "RelayGAM %s::Initialise: reference entry not found", Name());
    return False;
    }


    return True;
}

bool RelayGAM::Execute(GAM_FunctionNumbers functionNumber) {

    // Get input and output data pointers
    input->Read();
    float measure     = *((float *)input->Buffer());
    float *outputBuff = (float*)  output->Buffer();

    // Set all the outputs to zero
    float outvar = 0;

    switch(functionNumber) {
        case GAMPrepulse: {
            // Reset everything
            lastOutput = 0;
            Reset();
        }
        default: { 
            
                input->Read();

                //float error = inputData->errorSignal;
                float error            = reference - measure;
                float controlValue     = 0.0;
                    
                // Calculate the action
                if(error>tolerance){
                    controlValue = maxOut;
                }
                else if (error<-1*tolerance){ 
                    controlValue = minOut;
                }
                else{
                    controlValue = lastOutput;
                }                    
                
                    
                // Write signals to DDB
                *outputBuff     = controlValue;
                lastOutput      = controlValue;
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

    hStream.Printf("<p>Upper value: %f</p>\n", maxOut);
    hStream.Printf("<p>Lower value: %f</p>\n", minOut);
    


    hStream.Printf("</body></html>");
    hStream.WriteReplyHeader(True);
    return True;
}
OBJECTLOADREGISTER(RelayGAM,"$Id: RelayGAM.cpp 3 2012-01-15 16:26:07Z aneto $")

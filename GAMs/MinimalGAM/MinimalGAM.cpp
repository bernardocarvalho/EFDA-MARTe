
#include "MinimalGAM.h"
#include "MinimalGAMInputStructure.h"
#include "MinimalGAMOutputStructure.h"
#include "CDBExtended.h"

#include "DDBInputInterface.h"
#include "DDBOutputInterface.h"

#include "LoadCDBObjectClass.h"

#define TSTARTDEFAULT    0.0
#define TENDDEFAULT    100.0

bool MinimalGAM::Initialise(ConfigurationDataBase& cdbData) {

    CDBExtended cdb(cdbData);


    ////////////////////////////////////////////////////
    //                Add interfaces to DDB           //
    ////////////////////////////////////////////////////
    if(!AddInputInterface(input,"InputInterface")){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s failed to add input interface",Name());
        return False;
    }

    if(!AddOutputInterface(output,"OutputInterface")){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s failed to add output interface",Name());
        return False;
    }


    ////////////////////////////////////////////////////
    //                Add input signals               //
    ////////////////////////////////////////////////////
    if(!cdb->Move("InputSignals")){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s did not specify InputSignals entry",Name());
        return False;
    }

    if(!input->ObjectLoadSetup(cdb,NULL)){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s ObjectLoadSetup Failed DDBInterface %s ",Name(),input->InterfaceName());
        return False;
    }

    cdb->MoveToFather();




    ////////////////////////////////////////////////////
    //                Add output signals              //
    ////////////////////////////////////////////////////
    if(!cdb->Move("OutputSignals")){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s did not specify OutputSignals entry",Name());
        return False;
    }

    if(!output->ObjectLoadSetup(cdb,NULL)){
        AssertErrorCondition(InitialisationError,"MinimalGAM::Initialise: %s ObjectLoadSetup Failed DDBInterface %s ",Name(),output->InterfaceName());
        return False;
    }

    // Load parameter
            if(!cdb.ReadFloat(param, "param")){
            AssertErrorCondition(InitialisationError, "PIDGAM %s::Initialise: param entry not found", Name());
            return False;
        }



    return True;
}

bool MinimalGAM::Execute(GAM_FunctionNumbers functionNumber) {

    // Get input and output data pointers
    MinimalGAMInputStructure  *inputData  = (MinimalGAMInputStructure  *)input->Buffer();
    MinimalGAMOutputStructure *outputData = (MinimalGAMOutputStructure *)output->Buffer();

    // Set all the outputs to zero
    outputData->outvar              = false;

    switch(functionNumber) {
        case GAMPrepulse: {
            // Reset everything
            Reset();
        }
        default: {
            
            input->Read();
                
            if(inputData->signal >= 0.0) {
                outputData->outvar          = true;

                
            } 
        }
    }
    
    // Update the data output buffer
    output->Write();

    return True;
}





bool MinimalGAM::ProcessHttpMessage(HttpStream &hStream) {
    hStream.SSPrintf("OutputHttpOtions.Content-Type","text/html");
    hStream.keepAlive = False;
    hStream.WriteReplyHeader(False);
    hStream.Printf("<html><head><title>MinimalGAM %s</title></head><body>\n", Name());

    hStream.Printf("<h1>MinimalGAM %s</h1>", Name());
    hStream.Printf("<h1>Parameter %f</h1>", param);
    hStream.Printf("</body></html>");
    hStream.WriteReplyHeader(True);
    return True;
}
OBJECTLOADREGISTER(MinimalGAM,"$Id: MinimalGAM.cpp 3 2012-01-15 16:26:07Z aneto $")

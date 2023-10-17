/*
Test from Michele to learn MARTe
**/

#ifndef Relay_H
#define Relay_H

#include "GAM.h"
#include "HttpInterface.h"


/**
 * A GAM  implementing a Relay controller with 2 possible outputs: ON or OFF
 */
OBJECT_DLL(RelayGAM)
class RelayGAM : public GAM, public HttpInterface {
OBJECT_DLL_STUFF(RelayGAM)

// DDB Interfaces
private:
    /** Input interface to read data from */
    DDBInputInterface                      *input;
    /** Output interface to write data to */
    DDBOutputInterface                     *output;

// Parameters
private:
    float                                  lastOutput;
    float                                  maxOut;
    float                                  minOut;
    float                                  tolerance;
    float                                  reference;


public:
    /** Constructor */
    RelayGAM() {
        input                                         = NULL;
        output                                        = NULL;

        maxOut                                        = 0.0;
        minOut                                        = 0.0;
        tolerance                                     = 0.0;
        reference                                     = 0.0;

        lastOutput                                    = 0.0;
	
        Reset();
    }

    /** Destructor */
    ~RelayGAM(){
        Reset();
    }


    /**
     * Resets the PIDGAM's states
     */
    inline void Reset() {
      lastOutput               =   0;
    }

    /**
    * Loads GAM parameters from a CDB
    * @param cdbData the CDB
    * @return True if the initialisation went ok, False otherwise
    */
    virtual bool Initialise(ConfigurationDataBase& cdbData);

    /**
    * GAM main body
    * @param functionNumber The current state of MARTe
    * @return False on error, True otherwise
    */
    virtual bool Execute(GAM_FunctionNumbers functionNumber);

    /**
    * Saves parameters to a CDB
    * @param info the CDB to save to
    * @return True
    */
    virtual bool ObjectSaveSetup(ConfigurationDataBase &info, StreamInterface *err){ return True; };


    /**
    * The message is actually a multi stream (HttpStream)
    * with a convention described in HttpStream
    */
    virtual bool ProcessHttpMessage(HttpStream &hStream);
};


#endif /* Relay_H */

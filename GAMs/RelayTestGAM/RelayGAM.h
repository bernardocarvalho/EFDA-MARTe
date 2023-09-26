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
    /** True if the controller is enabled */
    bool                                   controllerEnabled;
    /** Control Start Time */
    float                                  *tStart;
    /** Control Start Time in Microseconds */
    uint32                                 *tStartUsec;
    /** Control End Time */
    float                                  *tEnd;
    /** Control End Time in Microsconds */
    uint32                                 *tEndUsec;
    /** Number of time windows */
    int                                     numberOfTimeWindows;
    /** Current time window */
    int                                     currentTimeWindow;
    /** Upper control saturation */
    float                                   upperControlSaturation;
    /** Neutral Value */
    float                                   neutralValue;
    /** Lower control saturation */
    float                                   lowerControlSaturation;

// States
private:
    /** The error signal at the previous step */
    float                                   previousStepError;

    /** The integrator */
    float                                   integrator;

public:
    /** Constructor */
    RelayGAM() {
        input                                         = NULL;
        output                                        = NULL;

        tStart                                        = NULL;
        tEnd                                          = NULL;
        tStartUsec                                    = NULL;
        tEndUsec                                      = NULL;

        currentTimeWindow                             =  0;
        numberOfTimeWindows                           = -1;

        upperControlSaturation                        = 0.0;
        neutralValue                                  = 0.0;
        lowerControlSaturation                        = 0.0;

        controllerEnabled                             = True;
	
        Reset();
    }

    /** Destructor */
    ~RelayGAM(){
        CheckAndFreeDynamicMemory();
    }


    /** Free dynamic memory for tStart and tEnd arrays of each time window */
    inline void CheckAndFreeDynamicMemory(){
        if( tStart != NULL ){
	    free((void*&)tStart);
	    tStart = NULL;
	}
        if( tEnd != NULL ){
	    free((void*&)tEnd);
	    tEnd = NULL;
	}
        if( tStartUsec != NULL ){
	    free((void*&)tStartUsec);
	    tStartUsec = NULL;
	}
        if( tEndUsec != NULL ){
	    free((void*&)tEndUsec);
	    tEndUsec = NULL;
	}
    }

    /**
     * Resets the PIDGAM's states
     */
    inline void Reset() {
      currentTimeWindow               =   0;
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

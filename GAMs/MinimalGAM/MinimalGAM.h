#ifndef MIN_H_
#define MIN_H_

#include "GAM.h"
#include "HttpInterface.h"



OBJECT_DLL(MinimalGAM)
class MinimalGAM : public GAM, public HttpInterface {
OBJECT_DLL_STUFF(MinimalGAM)

// DDB Interfaces
private:
    /** Input interface to read data from */
    DDBInputInterface                      *input;
    /** Output interface to write data to */
    DDBOutputInterface                     *output;

// Parameters
private:
    /** Just one parameter */
    float                                   param;

public:
    /** Constructor */
    MinimalGAM() {
        input                                         = NULL;
        output                                        = NULL;

        param                                         = 0.0;
        Reset();
    }

    /** Destructor */
    ~MinimalGAM(){
        
    }

    inline void Reset() {
        param                                         = 0.0;
    }

    /**
    * Loads GAM parameters from a CDB
    * @param cdbData the CDBreference
    * GAM main body
    * @param functionNumber The current state of MARTe
    * @return False on error, True otherwise
    */

    virtual bool Initialise(ConfigurationDataBase& cdbData);

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


#endif

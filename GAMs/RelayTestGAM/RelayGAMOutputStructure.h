#ifndef RelayGAMOUTPUTSTRUCTURE_H_
#define RelayGAMOUTPUTSTRUCTURE_H_

#include "System.h"

struct RelayGAMOutputStructure {
    /** Output of the relay */
    float                  controlSignal;
    /** Error signal -> reference - measurement */
    float                  error;
};

#endif /* RelayGAMOUTPUTSTRUCTURE_H_ */

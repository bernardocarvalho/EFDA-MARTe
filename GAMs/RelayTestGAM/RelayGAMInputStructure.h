
#ifndef RelayGAMINPUTSTRUCTURE_H_
#define RelayGAMINPUTSTRUCTURE_H_

#include "System.h"

struct RelayGAMInputStructure {
    /** Time signal */
    uint32                   usecTime;
    /** Reference signal to be followed */
    float                    reference;
    /** Measurement signal */
    float                    measurement;

};

#endif /* RelayGAMINPUTSTRUCTURE_H_ */

/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they 
   will be approved by the European Commission - subsequent  
   versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
   Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
   writing, software distributed under the Licence is 
   distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
   express or implied. 
 * See the Licence for the specific language governing 
   permissions and limitations under the Licence. 
 *
 * $Id: ConstantWaveform.h 3 2012-01-15 16:26:07Z aneto $
 *
**/

/**
 * @file
 * @brief A constant waveform
 */
#ifndef CONSTANTWAVEFORM_H_
#define CONSTANTWAVEFORM_H_

#include "System.h"
#include "WaveformInterface.h"
#include "GCNamedObject.h"
#include "HttpInterface.h"
#include "CDBExtended.h"


OBJECT_DLL(ConstantWaveform)
class ConstantWaveform: public WaveformInterface, public GCNamedObject, public HttpInterface {
OBJECT_DLL_STUFF(ConstantWaveform)
// Parameters
private:
    float                                 value;

public:
    virtual void Reset() {}

    virtual bool ObjectLoadSetup(ConfigurationDataBase &cdbData, StreamInterface * err);

    virtual bool ProcessHttpMessage(HttpStream &hStream);

    virtual float GetValue(int32 usecTime) {
        return value;
    }

};


#endif /* CONSTANTWAVEFORM_H_ */

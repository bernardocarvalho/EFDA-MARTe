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
 * $Id: DDBIOInterface.h 3 2012-01-15 16:26:07Z aneto $
 *
**/

/** 
 * @file
 * DBIOInterface class definition.
 */
#if !defined (DDBIOINTERFACE_H)
#define DDBIOINTERFACE_H

#include "DDBInterface.h"

/** 
 * The DDBIOInterface used by GAMs. 
 */
class DDBIOInterface: public DDBInterface{
public:

    /** Constructor. */
    DDBIOInterface(
        const char* ownerName, const char* interfaceName,
        DDBInterfaceAccessMode requestedAccessMode) :
        DDBInterface(ownerName, interfaceName, requestedAccessMode){}

    /** Fast function to read the databuffer. */
    inline void Read(){
        DDBInterface::Read();
    }

    /** Fast function to write the databuffer. */
    inline void Write(){
        DDBInterface::Write();
    }

};

#endif

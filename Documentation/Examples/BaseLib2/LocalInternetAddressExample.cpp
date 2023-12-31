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
 * $Id: LocalInternetAddressExample.cpp 3 2012-01-15 16:26:07Z aneto $
 *
**/
/**
 * @file Basic InternetAddress functionality
 */
#include "ErrorManagement.h"
#include "InternetAddress.h"

int main(int argc, char *argv[]){
    //Output logging messages to the console
    LSSetUserAssembleErrorMessageFunction(NULL); 
    //Output this computer local address and local ip
    CStaticAssertErrorCondition(Information, "This computer local address is:%s", InternetAddress::LocalAddress());
    CStaticAssertErrorCondition(Information, "This computer local ip is:%s", InternetAddress::LocalIpNumber());

    return 0;
}


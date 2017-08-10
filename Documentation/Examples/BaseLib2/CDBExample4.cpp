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
 * $Id: CDBExample4.cpp 3 2012-01-15 16:26:07Z aneto $
 *
**/
/**
 * @file Object creation with a GlobalObjectDataBase
 */
#include "GCNamedObject.h"
#include "ConfigurationDataBase.h"
#include "CDB.h"
#include "CDBExtended.h"
#include "GlobalObjectDataBase.h"

int main(int argc, char *argv[]){
    FString *myStringArray = new FString[4];
    myStringArray[0] = "AAA";
    myStringArray[1] = "BBB";
    myStringArray[2] = "CCC";
    myStringArray[3] = "DDD";
   
    int32 *myIntArray = new int32[4];
    myIntArray[0] = -1;
    myIntArray[1] = 0;
    myIntArray[2] = 1;
    myIntArray[3] = 2;
    
 
    int32 arraySize[1];
    arraySize[0] = 4;
    int32 arrayDimension = 1;

    ConfigurationDataBase cdb;
    CDBExtended cdbe(cdb);

    cdbe.WriteFStringArray(myStringArray, arraySize, arrayDimension, "MyStringArray");
    cdbe.WriteInt32Array(myIntArray, arraySize, arrayDimension, "MyIntArray");

    FString out;
    cdbe->WriteToStream(out);        
    printf("%s\n", out.Buffer());

    delete []myStringArray;
    delete []myIntArray;

    myStringArray = new FString[4];
    myIntArray = new int32[4];

    cdbe.ReadFStringArray(myStringArray, arraySize, arrayDimension, "MyStringArray");
    int32 i=0;
    for(i=0; i<4; i++){
        printf("%s\n", myStringArray[i].Buffer());
    }
    delete []myStringArray;

    cdbe.ReadInt32Array(myIntArray, arraySize, arrayDimension, "MyIntArray");
    for(i=0; i<4; i++){
            printf("%d\n", myIntArray[i]);
    }
    delete []myIntArray;


    return 0;
}


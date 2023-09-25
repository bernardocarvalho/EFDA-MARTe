#define protected public
#define private public
#include "RelayGAMClassInfo.h"
#include "ObjectRegistryItem.h"
#include "ClassStructure.h"
#include "ObjectMacros.h"
static ClassStructureEntry RelayGAMOutputStructure_controlSignal_CSE_EL("float","",0,0,0,0,0 ,"controlSignal",msizeof(RelayGAMOutputStructure,controlSignal),indexof(RelayGAMOutputStructure,controlSignal));
static ClassStructureEntry RelayGAMOutputStructure_error_CSE_EL("float","",0,0,0,0,0 ,"error",msizeof(RelayGAMOutputStructure,error),indexof(RelayGAMOutputStructure,error));
static ClassStructureEntry * RelayGAMOutputStructure__CSE__[] = {
    &RelayGAMOutputStructure_controlSignal_CSE_EL,
    &RelayGAMOutputStructure_error_CSE_EL,
    NULL
};
ClassStructure RelayGAMOutputStructure__CS__("RelayGAMOutputStructure",sizeof(RelayGAMOutputStructure),0 ,RelayGAMOutputStructure__CSE__);
STRUCTREGISTER("RelayGAMOutputStructure",RelayGAMOutputStructure__CS__)


static ClassStructureEntry RelayGAMInputStructure_usecTime_CSE_EL("unsigned int","",0,0,0,0,0 ,"usecTime",msizeof(RelayGAMInputStructure,usecTime),indexof(RelayGAMInputStructure,usecTime));
static ClassStructureEntry RelayGAMInputStructure_reference_CSE_EL("float","",0,0,0,0,0 ,"reference",msizeof(RelayGAMInputStructure,reference),indexof(RelayGAMInputStructure,reference));
static ClassStructureEntry RelayGAMInputStructure_measurement_CSE_EL("float","",0,0,0,0,0 ,"measurement",msizeof(RelayGAMInputStructure,measurement),indexof(RelayGAMInputStructure,measurement));
static ClassStructureEntry * RelayGAMInputStructure__CSE__[] = {
    &RelayGAMInputStructure_usecTime_CSE_EL,
    &RelayGAMInputStructure_reference_CSE_EL,
    &RelayGAMInputStructure_measurement_CSE_EL,
    NULL
};
ClassStructure RelayGAMInputStructure__CS__("RelayGAMInputStructure",sizeof(RelayGAMInputStructure),0 ,RelayGAMInputStructure__CSE__);
STRUCTREGISTER("RelayGAMInputStructure",RelayGAMInputStructure__CS__)


static ClassStructureEntry RelayGAMClassInfo_input_CSE_EL("RelayGAMInputStructure","",0,0,0,0,0 ,"input",msizeof(RelayGAMClassInfo,input),indexof(RelayGAMClassInfo,input));
static ClassStructureEntry RelayGAMClassInfo_output_CSE_EL("RelayGAMInputStructure","",0,0,0,0,0 ,"output",msizeof(RelayGAMClassInfo,output),indexof(RelayGAMClassInfo,output));
static ClassStructureEntry * RelayGAMClassInfo__CSE__[] = {
    &RelayGAMClassInfo_input_CSE_EL,
    &RelayGAMClassInfo_output_CSE_EL,
    NULL
};
ClassStructure RelayGAMClassInfo__CS__("RelayGAMClassInfo",sizeof(RelayGAMClassInfo),0 ,RelayGAMClassInfo__CSE__);
STRUCTREGISTER("RelayGAMClassInfo",RelayGAMClassInfo__CS__)
ClassStructure * RelayGAMClassInfo_sinfo[] = {
    &RelayGAMOutputStructure__CS__,
    &RelayGAMInputStructure__CS__,
    &RelayGAMClassInfo__CS__,
    NULL
};

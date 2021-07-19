#include "../include/engine.h"

using namespace foxintango;

IOEngineLWSInterface::IOEngineLWSInterface(){
}

IOEngineLWSInterface::~IOEngineLWSInterface(){
}

bool IOEngineLWSInterface::containClass(const unsigned char* name) {
    return false;
}

void* IOEngineLWSInterface::createObject(const unsigned char* name) {
    return 0;
}

void* IOEngineLWSInterface::createObject(const unsigned char* name,const Model& model){
    return 0;
}

bool IOEngineLWSInterface::containFunction(const unsigned char* name) {
    return false;
}

void* IOEngineLWSInterface::exportFunction(const unsigned char* name) {
    return 0;
}

void* IOEngineLWSInterface::exportVariable(const unsigned char* name) {
    return 0;
}

//EXTERN_C_BEGIN

IOEngineLWSInterface foxintangoAPI MODULE_INTERFACE_INSTANCE;

//extern "C" IOEngineLWSInterface foxintangoAPI MODULE_INTERFACE_INSTANCE;

/**
extern "C" int foxintangoAPI MODULE_INTERFACE_INSTANCE() {
    return 0;
}*/

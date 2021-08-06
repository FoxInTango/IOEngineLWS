#include "../include/module.h"
#include "../include/engine.h"
using namespace foxintango;
#include <string.h>

IOEngineLWSInterface::IOEngineLWSInterface(){
}

IOEngineLWSInterface::~IOEngineLWSInterface(){
}

bool IOEngineLWSInterface::containClass(const char* name) {
    if(0 == strcmp(name,"IOEngineLWS")) return true;
    return false;
}

void* IOEngineLWSInterface::createObject(const char* name) {
    if(strcmp((char*)name,"engine") == 0) {
        return new EngineLWS(); 
    }
    return 0;
}

void* IOEngineLWSInterface::createObject(const char* name,const Model& model){
    return 0;
}

bool IOEngineLWSInterface::containFunction(const char* name) {
    return false;
}

void* IOEngineLWSInterface::exportFunction(const char* name) {
    return 0;
}

void* IOEngineLWSInterface::exportVariable(const char* name) {
    return 0;
}

IOEngineLWSInterface foxintangoAPI MODULE_INTERFACE_INSTANCE;


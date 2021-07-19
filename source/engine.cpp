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

IOEngineLWSInterface foxintangoAPI MODULE_INTERFACE_INSTANCE;


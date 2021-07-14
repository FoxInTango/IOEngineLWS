#include <libmodule/libmodule.h>
#include <libmodel/libmodel.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

namespace foxintango {

class IOEngineLWSInterface :public ModuleInterface {
public:
    IOEngineLWSInterface();
   ~IOEngineLWSInterface();
public:
    virtual bool  containClass(const unsigned char* name) {
        return false;
    }

    virtual void* createObject(const unsigned char* name) {
        return 0;
    }

    virtual void* createObject(const unsigned char* name,const Model& model){
        return 0;
    }

    virtual bool  containFunction(const unsigned char* name) {
        return false;
    }

    virtual void* exportFunction(const unsigned char* name) {
        return 0;
    }

    virtual void* exportVariable(const unsigned char* name) {
        return 0;
    }
};

extern IOEngineLWSInterface MODULE_INTERFACE_INSTANCE;
}
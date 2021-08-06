#include <libmodule/libmodule.h>
#include <libmodel/libmodel.h>
#include <libcpp/libcpp.h>

EXTERN_C_BEGIN
namespace foxintango {

class foxintangoAPI IOEngineLWSInterface :public ModuleInterface {
public:
    IOEngineLWSInterface();
    virtual ~IOEngineLWSInterface();
public:
    virtual bool  containClass(const char* name);
    virtual void* createObject(const char* name);

    virtual void* createObject(const char* name,const Model& model);

    virtual bool  containFunction(const char* name);

    virtual void* exportFunction(const char* name);
    virtual void* exportVariable(const char* name);
};
}
EXTERN_C_END

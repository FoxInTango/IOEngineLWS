#include <libioevent/libioevent.h>
#include <libmodule/libmodule.h>
#include <libcpp/libcpp.h>

EXTERN_C_BEGIN
namespaceBegin(foxintango)
class foxintangoAPI EngineLWS :public IOEngine {
public:
    EngineLWS();
    ~EngineLWS();
public:
    virtual IOEndpoint* createEndpoint(const Model& model);
};
namespaceEnd
EXTERN_C_END

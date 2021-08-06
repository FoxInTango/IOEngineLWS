#ifndef _ENDPOINT_UDP_
#define _ENDPOINT_UDP_
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointUDP :public IOEndpoint {
public:
    EndpointUDP(const Model& model);
    virtual ~EndpointUDP();
};
EXTERN_C_END
#endif

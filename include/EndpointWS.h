#ifndef _ENDPOINT_UDP_
#define _ENDPOINT_UDP_
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointWSClient :public IOEndpoint {
public:
    EndpointWSClient(const Model& model);
    virtual ~EndpointWSClient();
};
class foxintangoAPI EndpointWSServer :public IOEndpoint {
public:
    EndpointWSServer(const Model& model);
    virtual ~EndpointWSServer();
};
EXTERN_C_END
#endif

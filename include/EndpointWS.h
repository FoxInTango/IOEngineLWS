#ifndef _ENDPOINT_WS_H_foxintango_
#define _ENDPOINT_WS_H_foxintango
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointWSClient :public IOEndpoint {
public:
    EndpointWSClient(const Model& model);
    virtual ~EndpointWSClient();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
class foxintangoAPI EndpointWSServer :public IOEndpoint {
public:
    EndpointWSServer(const Model& model);
    virtual ~EndpointWSServer();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
EXTERN_C_END
#endif

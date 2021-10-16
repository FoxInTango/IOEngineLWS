#ifndef _ENDPOINT_TCP_H_foxintango
#define _ENDPOINT_TCP_H_foxintango
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointTCPClient :public IOEndpoint {
public:
    EndpointTCPClient(const Model& model);
    virtual ~EndpointTCPClient();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
class foxintangoAPI EndpointTCPServer :public IOEndpoint {
public:
    EndpointTCPServer(const Model& model);
    virtual ~EndpointTCPServer();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
EXTERN_C_END
#endif

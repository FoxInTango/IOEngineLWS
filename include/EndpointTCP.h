#ifndef _ENDPOINT_TCP_
#define _ENDPOINT_TCP_
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointTCPClient :public IOEndpoint {
public:
    EndpointTCPClient(const Model& model);
    virtual ~EndpointTCPClient();
};
class foxintangoAPI EndpointTCPServer :public IOEndpoint {
public:
    EndpointTCPServer(const Model& model);
    virtual ~EndpointTCPServer();
};
EXTERN_C_END
#endif

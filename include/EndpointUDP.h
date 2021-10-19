#ifndef _ENDPOINT_UDP_H_foxintango
#define _ENDPOINT_UDP_H_foxintango
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN

class EndpointUDPIMPL;
class foxintangoAPI EndpointUDP :public IOEndpoint {
private:
    EndpointUDPIMPL* impl;
public:
    EndpointUDP(const Model& model);
    virtual ~EndpointUDP();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
EXTERN_C_END
#endif

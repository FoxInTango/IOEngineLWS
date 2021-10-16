#ifndef _ENDPOINT_HTTP_H_foxintango
#define _ENDPOINT_HTTP_H_foxintango
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class EndpointHTTPClientIMPL;
class foxintangoAPI EndpointHTTPClient :public IOEndpoint {
protected:
    EndpointHTTPClientIMPL* impl;
public:
    EndpointHTTPClient(const Model& model);
    virtual ~EndpointHTTPClient();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};

class EndpointHTTPServerIMPL;
class foxintangoAPI EndpointHTTPServer :public IOEndpoint {
public:
    EndpointHTTPServer(const Model& model);
    virtual ~EndpointHTTPServer();
public:
    virtual IOEndpointStatus boot();
    virtual IOEndpointStatus stop();
};
EXTERN_C_END
#endif

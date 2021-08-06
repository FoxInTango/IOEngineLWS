#ifndef _ENDPOINT_HTTP_
#define _ENDPOINT_HTTP_
#include <libioevent/libioevent.h>
#include <libcpp/libcpp.h>
using namespace foxintango;

EXTERN_C_BEGIN
class foxintangoAPI EndpointHTTPClient :public IOEndpoint {
public:
    EndpointHTTPClient(const Model& model);
    virtual ~EndpointHTTPClient();
};

class foxintangoAPI EndpointHTTPServer :public IOEndpoint {
public:
    EndpointHTTPServer(const Model& model);
    virtual ~EndpointHTTPServer();
};
EXTERN_C_END
#endif

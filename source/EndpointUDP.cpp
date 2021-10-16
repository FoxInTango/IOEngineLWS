#include "../include/EndpointUDP.h"
#include <libwebsockets.h>

class EndpointUDPIMPL {
public:
    struct lws_context_creation_info lwsInfo;
    struct lws_context* lwsContext;
public:
};

EndpointUDP::EndpointUDP(const Model& m) {
    this->impl = new EndpointUDPIMPL();

    if(this->impl) {

    }
}

EndpointUDP::~EndpointUDP() {
    if(this->impl) delete this->impl;
}

IOEndpointStatus EndpointUDP::boot() {

}

IOEndpointStatus EndpointUDP::stop() {

}

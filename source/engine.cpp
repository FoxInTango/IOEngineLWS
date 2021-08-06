#include "../include/engine.h"

#include "../include/EndpointUDP.h"
#include "../include/EndpointTCP.h"
#include "../include/EndpointWS.h"
#include "../include/EndpointHTTP.h"
using namespace foxintango;
#include <iostream>

#include <libwebsockets.h>
static const struct lws_http_mount mount = {
/* .mount_next */                  NULL,             /* linked-list "next" */
/* .mountpoint */                  "/",              /* mountpoint URL */
/* .origin */                      "./mount-origin", /* serve from dir */
/* .def */                         "index.html",     /* default filename */
/* .protocol */                    NULL,
/* .cgienv */                      NULL,
/* .extra_mimetypes */             NULL,
/* .interpret */                   NULL,
/* .cgi_timeout */                 0,
/* .cache_max_age */               0,
/* .auth_mask */                   0,
/* .cache_reusable */              0,
/* .cache_revalidate */            0,
/* .cache_intermediaries */        0,
/* .origin_protocol */             LWSMPRO_FILE,   /* files in a dir */
/* .mountpoint_len */              1,      /* char count */
/* .basic_auth_login_file */       NULL,
};

EngineLWS::EngineLWS() {

}

EngineLWS::~EngineLWS() {

}

IOEndpoint* EngineLWS::createEndpoint(const Model& model){
    ME* t = model.subelementAt("type");
    if(t) {
        char* ts;
        ts << *t;
        std::cout << "EngineLWS : createEndpoint - " << ts << std::endl;

        IOEndpointType et;
        if(0 == strcmp("IOET_UDP"              ,ts))  { et = IOET_UDP;        }
        else if(0 == strcmp("IOET_TCP_SERVER"  ,ts))  { et = IOET_TCP_SERVER; }
        else if(0 == strcmp("IOET_TCP_CLIENT"  ,ts))  { et = IOET_TCP_CLIENT; }
        else if(0 == strcmp("IOET_HTTP_SERVER" ,ts))  { et = IOET_HTTP_SERVER;}
        else if(0 == strcmp("IOET_HTTP_CLINE"  ,ts))  { et = IOET_HTTP_CLIENT;}
        else if(0 == strcmp("IOET_WS_SERVER"   ,ts))  { et = IOET_WS_SERVER;  }
        else if(0 == strcmp("IOET_WS_CLINE"    ,ts))  { et = IOET_WS_CLIENT;  }

        switch(et) {
            case IOEndpointType::IOET_UDP:{}break;
            case IOET_TCP_SERVER:{}break;
            case IOET_TCP_CLIENT:{}break;
            case IOET_HTTP_SERVER:{}break;
            case IOET_HTTP_CLIENT:{}break;
            case IOET_WS_SERVER:{}break;
            case IOET_WS_CLIENT:{}break;
            default:return 0;
        }
    }

    return 0;
}

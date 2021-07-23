#include "../include/engine.h"
using namespace foxintango;

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

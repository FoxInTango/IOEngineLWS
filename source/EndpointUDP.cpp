#include "../include/EndpointUDP.h"
#include <libwebsockets.h>
#include <thread>
#include <chrono>
#include <iostream>
/** TEST BEGIN
 * */
const int TEST_PORT_A = 8801;
const int TEST_PORT_B = 8802;
const char* TEST_NAME_A = "name.A";
const char* TEST_NAME_B = "name.B";
/** TEST END
 * */

class EndpointUDPIMPL {
public:
    bool interrupted = false;
    uint8_t sendbuf[4096];
    size_t  sendlen;
    struct lws_udp lwsUDP;
    struct lws_context_creation_info lwsInfo;
    struct lws_context* lwsContext;
    struct lws_vhost* lwsVhost;
public:
};

extern "C" int callback_raw_udp(struct lws *wsi,enum lws_callback_reasons reason,void *user,void *in,size_t len);
extern "C" int thread_process(EndpointUDPIMPL*);
void sigint_handler(int sig)
{
    
	//interrupted = 1;
}

EndpointUDP::EndpointUDP(const Model& m) {
    this->impl = new EndpointUDPIMPL();

    if(this->impl) {
        //signal(SIGINT,sigint_handler);
        memset(&this->impl->lwsInfo,0,sizeof(this->impl->lwsInfo)); /* otherwise uninitialized garbage */
	    this->impl->lwsInfo.options = LWS_SERVER_OPTION_EXPLICIT_VHOSTS;
        this->impl->lwsContext = lws_create_context(&this->impl->lwsInfo);
	    if(!this->impl->lwsContext) {
	        lwsl_err("EndpointUDP::EndpointUDP() LWSContext create failed.\n");
	        //return 1;
            return;
	    }
        const ME* ne = m["name"];
        char* name = 0;
        if(ne) {
            //*ne >> name;
            ne->as(&name);
        }
        this->impl->lwsInfo.port = 8080;//CONTEXT_PORT_NO_LISTEN_SERVER;
	    struct lws_protocols protocols[] = { { name,callback_raw_udp,sizeof(void*),0,0,this->impl,0 },
	                                         LWS_PROTOCOL_LIST_TERM
                                           };
        this->impl->lwsInfo.protocols = protocols;
        this->impl->lwsVhost = lws_create_vhost(this->impl->lwsContext,&this->impl->lwsInfo);
        if(!this->impl->lwsVhost) {
	        lwsl_err("EndpointUDP::EndpointUDP() LWSVhost create failed.\n");
            lws_context_destroy(this->impl->lwsContext);
            return;
	    }
    }
}

EndpointUDP::~EndpointUDP() {
    this->stop();
    if(this->impl) delete this->impl;
}

IOEndpointStatus EndpointUDP::boot() {
    std::thread thread(thread_process,this->impl);
    thread.detach();
}

IOEndpointStatus EndpointUDP::stop() {
    this->impl->interrupted = true;
}

int callback_raw_udp(struct lws *wsi,enum lws_callback_reasons reason,void *user,void *in,size_t len)
{
	ssize_t n;
	lws_sockfd_type fd;

    EndpointUDPIMPL *endpointIMPL = static_cast<EndpointUDPIMPL*>(user);
    struct lws_udp udp;

    if(!endpointIMPL) { return 0;/**log*/ }
	
    switch (reason) {

	/* callbacks related to raw socket descriptor */

        case LWS_CALLBACK_RAW_ADOPT:
		lwsl_user("LWS_CALLBACK_RAW_ADOPT\n");
                break;

	case LWS_CALLBACK_RAW_CLOSE:
		lwsl_user("LWS_CALLBACK_RAW_CLOSE\n");
		break;

	case LWS_CALLBACK_RAW_RX:
		lwsl_user("LWS_CALLBACK_RAW_RX (%d)\n", (int)len);
		lwsl_hexdump_level(LLL_NOTICE, in, len);
		/*
		 * Take a copy of the buffer and the source socket address...
		 */
		endpointIMPL->lwsUDP  = *(lws_get_udp(wsi));
		endpointIMPL->sendlen = len;
		if (endpointIMPL->sendlen > sizeof(endpointIMPL->sendbuf))
			endpointIMPL->sendlen = sizeof(endpointIMPL->sendbuf);
		memcpy(endpointIMPL->sendbuf,in, endpointIMPL->sendlen);
        std::cout << "IOEngineLWS : message from " << sa46_sockaddr(&endpointIMPL->lwsUDP.sa46) << "-" << endpointIMPL->sendbuf << std::endl;
		/*
		 * ... and we send it next time around the event loop.  This
		 * can be extended to having a ringbuffer of different send
		 * buffers and targets queued.
		 *
		 * Note that UDP is ALWAYS writable as far as poll() knows
		 * because there is no mechanism like the tcp window to
		 * understand that packets are not being acknowledged.  But
		 * this allows the event loop to share out the work.
		 */
		lws_callback_on_writable(wsi);
		break;

	case LWS_CALLBACK_RAW_WRITEABLE:

		if (!endpointIMPL->sendlen)
			break;

		fd = lws_get_socket_fd(wsi);
#if defined(WIN32)
		if ((int)fd < 0)
			break;
#else
		if (fd < 0) /* keep Coverity happy: actually it cannot be < 0 */
			break;
#endif

		/*
		 * We can write directly on the UDP socket, specifying
		 * the peer the write is directed to.
		 *
		 * However the kernel may only accept parts of large sendto()s,
		 * leaving you to try to resend the remainder later.  However
		 * depending on how your protocol on top of UDP works, that
		 * may involve sticking new headers before the remainder.
		 *
		 * For clarity partial sends just drop the remainder here.
		 */
		n = sendto(fd,
#if defined(WIN32)
				(const char *)
#endif
			endpointIMPL->sendbuf,
#if defined(WIN32)
			(int)
#endif
			endpointIMPL->sendlen, 0, sa46_sockaddr(&endpointIMPL->lwsUDP.sa46),
			sa46_socklen(&endpointIMPL->lwsUDP.sa46));
		if (n < (ssize_t)len)
			lwsl_notice("%s: send returned %d\n", __func__, (int)n);
		break;

	default:
		break;
	}

	return 0;
}

int thread_process(EndpointUDPIMPL* e) {
    if(!e) return -1;

    int n = 0;
    while (n >= 0 && !e->interrupted)
        n = lws_service(e->lwsContext,0);

    return 0;
}

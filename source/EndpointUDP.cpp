#include "../include/EndpointUDP.h"
#include <libwebsockets.h>

/** TEST BEGIN
 * */

/** TEST END
 * */

class EndpointUDPIMPL {
public:
    uint8_t sendbuf[4096];
    size_t  sendlen;
    struct lws_udp lwsUDP;
    struct lws_context_creation_info lwsInfo;
    struct lws_context* lwsContext;
public:
};

extern "C" int callback_raw_udp(struct lws *wsi,enum lws_callback_reasons reason,void *user,void *in,size_t len);

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

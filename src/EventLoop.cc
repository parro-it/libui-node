#include "nbind/nbind.h"
#include <uv.h>
#include "../ui.h"

extern int uiConnectionNumber();
extern int uiEventsPending();

static void onEventsPending(uv_poll_t* handle, int status, int events) {
	printf ("onEventsPending\n");

	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}

}

uv_poll_t * handle;

struct EventLoop {
	static void start () {

		uiMainSteps();

		int fd = uiConnectionNumber();
		printf("uiConnectionNumber %d\n", fd);
		handle = new uv_poll_t();
		printf("uv_poll_t %p\n", handle);

		uv_poll_init(uv_default_loop(), handle, fd);
		printf("uv_poll_init\n");

		uv_poll_start(handle, UV_READABLE, onEventsPending);
		printf("uv_poll_start\n");

	}

	static void stop () {
		uiQuit();
		uv_poll_stop(handle);
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

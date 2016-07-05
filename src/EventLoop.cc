#include "nbind/nbind.h"
#include <uv.h>
#include "../ui.h"


void onEventsPending(uv_poll_t* handle, int status, int events) {

	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}

}

uv_poll_t * handle;

struct EventLoop {
	static void start () {

		uiMainSteps();

		int fd =uiConnectionNumber();

		handle = new uv_poll_t();

		uv_poll_init(uv_default_loop(), handle, fd);
		uv_poll_start(handle, UV_READABLE, onEventsPending);
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

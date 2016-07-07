#include <uv.h>
#include "../../../ui.h"
#include "nbind/nbind.h"

extern int uiConnectionNumber();
extern int uiEventsPending();

uv_poll_t * handle;



static void onEventsPending(uv_poll_t* handle, int status, int events) {
	printf("onEventsPending\n");
	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}
	printf("onEventsPending exited\n");
}

bool running = false;

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}
		running = true;
		uiMainSteps();

		int fd = uiConnectionNumber();
		handle = new uv_poll_t();

		uv_poll_init(uv_default_loop(), handle, fd);

		uv_poll_start(handle, UV_READABLE, onEventsPending);
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;
		uiQuit();
		uv_poll_stop(handle);
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

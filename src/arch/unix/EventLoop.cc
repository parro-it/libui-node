#include <uv.h>
#include "../../../ui.h"
#include "nbind/nbind.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <poll.h>

extern int uiEventsPending();
extern int uiConnectionNumber();


uv_thread_t *thread;
bool running = false;

void asyncClosed(uv_handle_t* handle) {
	delete handle;
}

static void eventsPending(uv_async_t* handle) {
	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}
}

void pollEvents(void* arg) {
	int fd = uiConnectionNumber();
	struct pollfd fds;
	fds.fd = fd;
	fds.events = POLLIN | POLLPRI;

	uv_async_t * asyncCall = new uv_async_t();
	uv_async_init(uv_default_loop(),  asyncCall, eventsPending);

	while(running) {
		if (poll(&fds, 1, 50) == 1) {
			uv_async_send(asyncCall);
		}

	}
	uv_close((uv_handle_t*) asyncCall, asyncClosed);
}

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}


		running = true;
		uiMainSteps();

		thread = new uv_thread_t();
		uv_thread_create(thread, pollEvents, NULL);

	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;

		uiQuit();
		uv_thread_join(thread);
		delete thread;
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

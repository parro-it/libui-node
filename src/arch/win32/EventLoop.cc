#include "../../../ui.h"
#include "nbind/nbind.h"
#include <uv.h>
#include <Windows.h>

bool running = false;
uv_timer_t * keepAliveTimer;

void keepAliveCb(uv_timer_t* handle) {
	Nan::HandleScope scope;
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		uiMainStep(0);
	}
}

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}

		running = true;
		uiMainSteps();

		keepAliveTimer = new uv_timer_t();
		uv_timer_init(uv_default_loop(), keepAliveTimer);
		uv_timer_start(keepAliveTimer, keepAliveCb, 100, 100);
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;

		uiQuit();

		uv_timer_stop(keepAliveTimer);
		delete keepAliveTimer;
	}
};

NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

#include "../../../ui.h"
#include "nbind/nbind.h"

bool running = false;

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}

		running = true;
		uiMain();
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;
		uiQuit();
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

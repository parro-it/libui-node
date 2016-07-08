#include "../../../ui.h"
#include "nbind/nbind.h"

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}

		running = true;
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;

	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

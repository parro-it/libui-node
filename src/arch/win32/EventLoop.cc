#include "../../../ui.h"
#include "nbind/nbind.h"
#include <uv.h>
#include <Windows.h>

bool running = false;
uv_thread_t *thread;

LRESULT CALLBACK onEvents(int nCode, WPARAM wParam, LPARAM lParam) {
	printf("%d\n", nCode);
}


void pollEvents(void* threadId) {
	SetWindowsHookEx(
  		WH_CALLWNDPROC,
  		onEvents,
  		NULL,
  		threadId
	);
}

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}

		running = true;
		thread = new uv_thread_t();
		int threadId = GetCurrentThreadId();
		uv_thread_create(thread, pollEvents, threadId);
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

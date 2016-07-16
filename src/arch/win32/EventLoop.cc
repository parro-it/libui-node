#include "../../../ui.h"
#include "nbind/nbind.h"
#include <uv.h>
#include <Windows.h>

bool running = false;
uv_thread_t *thread;
uv_async_t * asyncCall;
bool runningSteps = false;
HHOOK hhook;

static void eventsPending(uv_async_t* handle) {
	Nan::HandleScope scope;
	while (uiMainStep(0));
	runningSteps = false;
}

LRESULT CALLBACK onEvents(int nCode, WPARAM wParam, LPARAM lParam) {


	if (!runningSteps) {
		runningSteps = true;
		//printf("%d\n", nCode);
		uv_async_send(asyncCall);
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void pollEvents(void* pThreadId) {
	int threadId = *((int *) pThreadId);
	hhook = SetWindowsHookEx(
		WH_CALLWNDPROC,
		onEvents,
		NULL,
		threadId
	);

	asyncCall = new uv_async_t();
	uv_async_init(uv_default_loop(),  asyncCall, eventsPending);

	MSG msg;
	while(running && GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

struct EventLoop {
	static void start () {
		if (running) {
			return;
		}

		running = true;

		uiMainSteps();

		thread = new uv_thread_t();
		int threadId = GetCurrentThreadId();
		uv_thread_create(thread, pollEvents, &threadId);
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;
		UnhookWindowsHookEx(hhook);
		uiQuit();
		uv_thread_join(thread);
		delete thread;
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

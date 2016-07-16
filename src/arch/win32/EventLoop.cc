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
	printf("Async event received in main loop. Running steps.\n", nCode);
	while (uiMainStep(0));
	printf("No more steps to run.\n", nCode);
	runningSteps = false;
}

LRESULT CALLBACK onEvents(int nCode, WPARAM wParam, LPARAM lParam) {


	if (!runningSteps) {
		runningSteps = true;
		printf("Sending async event to main loop\n", nCode);
		uv_async_send(asyncCall);
	}
	rintf("Skipping because main is running steps\n", nCode);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}


void pollEvents(void* pThreadId) {
	int threadId = *((int *) pThreadId);
	rintf("Setting hooks for %d\n", threadId);
	hhook = SetWindowsHookEx(
		WH_CALLWNDPROC,
		onEvents,
		NULL,
		threadId
	);
	printf("hooks ok for %d\n", threadId);
	asyncCall = new uv_async_t();
	uv_async_init(uv_default_loop(),  asyncCall, eventsPending);

	printf("starting background loop\n");
	MSG msg;
	while(running && GetMessage(&msg, NULL, 0, 0) > 0) {
		printf("background message received\n");
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	printf("exit background loop\n");
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

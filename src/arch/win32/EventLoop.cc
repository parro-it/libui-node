#include "../../../ui.h"
#include "nbind/nbind.h"
#include <uv.h>
#include <Windows.h>

bool running = false;
uv_thread_t *thread;
uv_async_t *asyncCall;
bool runningSteps = false;
HHOOK hhook;

static void eventsPending(uv_async_t* handle) {
	Nan::HandleScope scope;
	printf("Async event received in main loop. Running steps.\n");
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		uiMainStep(0);
	}
	printf("No more steps to run.\n");
	runningSteps = false;
}

LRESULT CALLBACK onEvents(int nCode, WPARAM wParam, LPARAM lParam) {


	if (!runningSteps) {
		runningSteps = true;
		printf("Sending async event to main loop\n", nCode);
		uv_async_send(asyncCall);
	} else {
		//printf("Skipping because main is running steps\n", nCode);

	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void asyncClosed(uv_handle_t* handle) {
	delete handle;
}

void pollEvents(void* pThreadId) {
	int threadId = *((int *) pThreadId);
	printf("Setting hooks for %d\n", threadId);
	hhook = SetWindowsHookEx(
		WH_CALLWNDPROC,
		onEvents,
		NULL,
		threadId
	);
	printf("hooks ok for %d\n", threadId);
	asyncCall = new uv_async_t();
	uv_async_init(uv_default_loop(),  asyncCall, eventsPending);

	printf("running:%d\n", running);
	printf("starting background loop\n");
	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	// MessageBox(NULL, "test", "ciao", MB_OK);
	/*while(running && GetMessage(&msg, NULL, 0, 0) > 0) {
		printf("background message received\n");
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/
	GetMessage(&msg, NULL, 0, 0);
	uv_close((uv_handle_t*) asyncCall, asyncClosed);
	printf("exit background loop\n");
}

void keepAliveCb(uv_timer_t* handle) {
	MSG msg;
	PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE);
	return;
	if (GetMessage(&msg, NULL, 0, 0) > 0) {
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
		printf("uiMainSteps\n");
		uiMainSteps();
		printf("uiMainSteps done\n");
		thread = new uv_thread_t();
		printf("thread alloc\n");
		int * threadId = new int();
		*threadId = GetCurrentThreadId();
		printf("main thread %d\n", *threadId);

		
		int ret = uv_thread_create(thread, pollEvents, threadId);


		printf("back thread created %d\n", ret);


		uv_timer_t * keepAliveTimer = new uv_timer_t();
		uv_timer_init(uv_default_loop(), keepAliveTimer);
		uv_timer_start(keepAliveTimer, keepAliveCb, 100, 100);

		/*MSG msg;
		while(running && GetMessage(&msg, NULL, 0, 0) > 0) {
			//printf("foreground message received\n");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}*/
	}

	static void stop () {
		if (!running) {
			return;
		}
		running = false;
		printf("stop\n");
		UnhookWindowsHookEx(hhook);
		printf("UnhookWindowsHookEx done\n");
		uiQuit();
		printf("uiQuit done\n");
		uv_thread_join(thread);
		printf("uv_thread_join done\n");
		delete thread;
	}
};


NBIND_CLASS(EventLoop) {
		method(start);
		method(stop);
}

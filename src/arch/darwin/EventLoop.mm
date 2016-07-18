#include "nbind/nbind.h"
#include <uv.h>
#include "../../../ui.h"
#import <Cocoa/Cocoa.h>
#include <unistd.h>

uv_thread_t *thread;
bool running = false;

void asyncClosed(uv_handle_t* handle) {
	delete handle;
}

static int uiEventsPending() {
	NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask
			untilDate: [NSDate distantPast]
			inMode:NSDefaultRunLoopMode
			dequeue:YES];
	[NSApp sendEvent:event];
	return nil != event;
}

static void eventsPending(uv_async_t* handle) {
	Nan::HandleScope scope;
	while(uiEventsPending()) {
		uiMainStep(0);
	}
}

void pollEvents(void* arg) {
	uv_async_t * asyncCall = new uv_async_t();
	uv_async_init(uv_default_loop(),  asyncCall, eventsPending);

	while(running) {
		[NSApp nextEventMatchingMask:NSAnyEventMask
			untilDate: [NSDate distantFuture]
			inMode:NSDefaultRunLoopMode
			dequeue:NO];
		uv_async_send(asyncCall);
		usleep(1000 * 50);
	}
	uv_close((uv_handle_t*) asyncCall, asyncClosed);
}

void threadClosed(uv_handle_t* handle) {
	delete handle;
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

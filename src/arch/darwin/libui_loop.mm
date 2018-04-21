#include "event-loop-darwin.h"
#include "event-loop.h"

int uiLoopWakeup() {
	[NSApp postEvent:[NSEvent otherEventWithType:NSApplicationDefined
										location:NSZeroPoint
								   modifierFlags:0
									   timestamp:0.0
									windowNumber:0
										 context:nil
										 subtype:0
										   data1:0
										   data2:0]
			 atStart:NO];

	return 0;
}

int uiEventsPending() {
	NSEvent *event = [NSApp nextEventMatchingMask:NSAnyEventMask
										untilDate:[NSDate distantPast]
										   inMode:NSDefaultRunLoopMode
										  dequeue:NO];
	return nil != event;
}

int waitForNodeEvents(uv_loop_t *loop, int timeout) {
	int nodeBackendFd = uv_backend_fd(loop);
	if (nodeBackendFd == -1) {
		fprintf(stderr, "Invalid node backend fd.\n");
		return 0;
	}

	struct kevent event;
	struct timespec ts;
	struct timespec *tsp = nullptr;

	if (timeout != -1) {
		tsp = &ts;
		ts.tv_sec = timeout / 1000;
		ts.tv_nsec = (timeout % 1000) * 1000000;
	}

	return kevent(nodeBackendFd, NULL, 0, &event, 1, tsp);
}

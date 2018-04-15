#include "timer.h"
#include "nbind/api.h"
#import <Cocoa/Cocoa.h>

TimeoutHandle *setTimeout(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	timeoutHandle->handle =
		[NSTimer scheduledTimerWithTimeInterval:timeout / 1000.0
										repeats:NO
										  block:^(NSTimer *timer) {
											CALL_JSCB(timeoutHandle);
											timeoutHandle->destroy();
										  }];
	return timeoutHandle;
}

void clearTimeout(TimeoutHandle *timeoutHandle) {
	NSTimer *handle = (NSTimer *)timeoutHandle->handle;
	[handle invalidate];
	timeoutHandle->destroy();
}

TimeoutHandle *setInterval(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	timeoutHandle->handle =
		[NSTimer scheduledTimerWithTimeInterval:timeout / 1000.0
										repeats:YES
										  block:^(NSTimer *timer) {
											CALL_JSCB(timeoutHandle);
										  }];
	return timeoutHandle;
}

void clearInterval(TimeoutHandle *timeoutHandle) {
	NSTimer *handle = (NSTimer *)timeoutHandle->handle;
	[handle invalidate];
	timeoutHandle->destroy();
}

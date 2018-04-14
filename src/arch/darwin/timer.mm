#include "../../includes/event-loop-darwin.h"
#include "nbind/api.h"

class TimeoutHandle {
  public:
	NSTimer *handle;
	nbind::cbFunction *callbackJs;
	bool destroyed;

	TimeoutHandle(nbind::cbFunction *callbackJs) {
		this->callbackJs = callbackJs;
		this->destroyed = false;
	}

	void destroy() {
		if (this->destroyed) {
			return;
		}

		delete this->callbackJs;
		this->destroyed = true;
	}
};

#define CALL_JSCB(timeoutHandle) (*(timeoutHandle->callbackJs))()

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
	[timeoutHandle->handle invalidate];
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
	[timeoutHandle->handle invalidate];
	timeoutHandle->destroy();
}

#include "nbind/nbind.h"

NBIND_GLOBAL() {
	function(setTimeout);
	function(clearTimeout);
	function(setInterval);
	function(clearInterval);
}

NBIND_CLASS(TimeoutHandle) {}

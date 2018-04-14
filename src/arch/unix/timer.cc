#include <gdk/gdk.h>
#include <glib.h>
#include "nbind/api.h"

class TimeoutHandle {
  public:
	unsigned int handle;
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

gboolean glib_timeout_cb(TimeoutHandle *timeoutHandle) {
	CALL_JSCB(timeoutHandle);
	timeoutHandle->destroy();
	return FALSE;
}

gboolean glib_interval_cb(TimeoutHandle *timeoutHandle) {
	CALL_JSCB(timeoutHandle);
	return TRUE;
}

TimeoutHandle *setTimeout(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	timeoutHandle->handle =
		g_timeout_add(timeout, (GSourceFunc)glib_timeout_cb, timeoutHandle);
	return timeoutHandle;
}

void clearTimeout(TimeoutHandle *timeoutHandle) {
	g_source_remove(timeoutHandle->handle);
	timeoutHandle->destroy();
}

TimeoutHandle *setInterval(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	timeoutHandle->handle =
		g_timeout_add(timeout, (GSourceFunc)glib_interval_cb, timeoutHandle);
	return timeoutHandle;
}

void clearInterval(TimeoutHandle *timeoutHandle) {
	printf("clearInterval called\n");
	g_source_remove(timeoutHandle->handle);
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

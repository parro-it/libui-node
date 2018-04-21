#include "timer.h"
#include "nbind/api.h"

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
	g_source_remove(timeoutHandle->handle);
	timeoutHandle->destroy();
}

#include <map>
#include "nbind/api.h"
#include "timer.h"

static std::map<UINT_PTR, TimeoutHandle *> timersMap;

void killTimer(TimeoutHandle *timeoutHandle) {
	KillTimer(NULL, timeoutHandle->handle);
	timersMap.erase(timeoutHandle->handle);
	timeoutHandle->destroy();
}

void CALLBACK win_timeout_cb(HWND hwnd, UINT uMsg, UINT_PTR idEvent,
							 DWORD dwTime) {
	TimeoutHandle *timeoutHandle = timersMap[idEvent];
	CALL_JSCB(timeoutHandle);
	killTimer(timeoutHandle);
}

void CALLBACK win_interval_cb(HWND hwnd, UINT uMsg, UINT_PTR idEvent,
							  DWORD dwTime) {
	TimeoutHandle *timeoutHandle = timersMap[idEvent];
	CALL_JSCB(timeoutHandle);
}

TimeoutHandle *setTimeout(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	// SetTimer could work with a NULL window.
	// https://stackoverflow.com/questions/7531650/can-i-use-a-settimer-api-in-a-console-c-application
	timeoutHandle->handle = SetTimer(NULL, NULL, timeout, win_timeout_cb);
	timersMap[timeoutHandle->handle] = timeoutHandle;
	return timeoutHandle;
}

void clearTimeout(TimeoutHandle *timeoutHandle) {
	if (!timeoutHandle->destroyed) {
		killTimer(timeoutHandle);
	}
}

TimeoutHandle *setInterval(nbind::cbFunction &cb, unsigned int timeout) {
	nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
	TimeoutHandle *timeoutHandle = new TimeoutHandle(callbackJs);
	timeoutHandle->handle = SetTimer(NULL, NULL, timeout, win_interval_cb);
	timersMap[timeoutHandle->handle] = timeoutHandle;
	return timeoutHandle;
}

void clearInterval(TimeoutHandle *timeoutHandle) {
	killTimer(timeoutHandle);
}

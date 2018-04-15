#ifndef UI_NODE_CONTROL
#define UI_NODE_CONTROL 1

#include "nbind/api.h"

#ifdef WIN32
#include <Windows.h>
typedef UINT_PTR TIMER_HANDLE;
#endif

#ifdef __APPLE__
typedef void *TIMER_HANDLE;
#endif

#ifdef __linux__
#include <gdk/gdk.h>
#include <glib.h>
typedef unsigned int TIMER_HANDLE;
#endif

class TimeoutHandle {
  public:
	TIMER_HANDLE handle;
	nbind::cbFunction *callbackJs;
	bool destroyed;

	TimeoutHandle(nbind::cbFunction *callbackJs);
	void destroy();
};

#define CALL_JSCB(timeoutHandle) (*(timeoutHandle->callbackJs))()

TimeoutHandle *setInterval(nbind::cbFunction &cb, unsigned int timeout);
void clearInterval(TimeoutHandle *timeoutHandle);
TimeoutHandle *setTimeout(nbind::cbFunction &cb, unsigned int timeout);
void clearTimeout(TimeoutHandle *timeoutHandle);

#endif

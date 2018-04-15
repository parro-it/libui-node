#ifndef UI_NODE_CONTROL
#define UI_NODE_CONTROL 1

class TimeoutHandle {
  public:
	unsigned int handle;
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

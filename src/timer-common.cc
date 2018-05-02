#include "nbind/api.h"
#include "timer.h"

TimeoutHandle::TimeoutHandle(nbind::cbFunction *callbackJs) {
	this->callbackJs = callbackJs;
	this->destroyed = false;
}

void TimeoutHandle::destroy() {
	if (this->destroyed) {
		return;
	}

	delete this->callbackJs;
	this->destroyed = true;
}

#include "nbind/nbind.h"

NBIND_GLOBAL() {
	function(setTimeout);
	function(clearTimeout);
	function(setInterval);
	function(clearInterval);
}

NBIND_CLASS(TimeoutHandle) {}

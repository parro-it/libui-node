#include "ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

/* TODO: this file has to be removed */

static int onShouldQuit_cb(void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	(*cb)();
	return 0;
}

static int uiTimer_cb(void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	return cb->call<int>();
}

struct Ui {
	static void main() {
		uiMain();
	}

	static void mainSteps() {
		uiMainSteps();
	}

	static int mainStep(int wait) {
		return uiMainStep(wait);
	}

	static void onShouldQuit(nbind::cbFunction &cb) {
		uiOnShouldQuit(onShouldQuit_cb, new nbind::cbFunction(cb));
	}

	static void quit() {
		uiQuit();
	}

	static void init() {
		uiInitOptions o;
		memset(&o, 0, sizeof(uiInitOptions));
		const char *err = uiInit(&o);
		if (err != NULL) {
			NBIND_ERR(err);
			uiFreeInitError(err);
		}
	}

	static void startTimer(int ms, nbind::cbFunction &cb) {
		nbind::cbFunction *callbackJs = new nbind::cbFunction(cb);
		uiTimer(ms, uiTimer_cb, callbackJs);
	}
};

NBIND_CLASS(Ui) {
	method(init);
	method(main);
	method(quit);
	method(mainStep);
	method(mainSteps);
	method(onShouldQuit);
	method(startTimer);
}

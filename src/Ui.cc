#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

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

	static void quit() {
		uiQuit();
	}

	static void init() {
		uiInitOptions o;
		memset(&o, 0, sizeof (uiInitOptions));
		const char *err = uiInit(&o);
		if (err != NULL) {
			NBIND_ERR(err);
			uiFreeInitError(err);
		}
	}
};

NBIND_CLASS(Ui) {
	method(init);
	method(main);
	method(quit);
	method(mainStep);
	method(mainSteps);
}

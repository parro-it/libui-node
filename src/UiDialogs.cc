#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

struct UiDialogs {

	static char *openFile(UiWindow *parent) {
		return uiOpenFile(parent->getHandle());
	}

	static char *saveFile(UiWindow *parent) {
		return uiSaveFile(parent->getHandle());
	}

	static void msgBox(UiWindow *parent, const char *title,
					   const char *description) {
		uiMsgBox(parent->getHandle(), title, description);
	}

	static void msgBoxError(UiWindow *parent, const char *title,
							const char *description) {
		uiMsgBoxError(parent->getHandle(), title, description);
	}
};

NBIND_CLASS(UiDialogs) {
	method(openFile);
	method(saveFile);
	method(msgBox);
	method(msgBoxError);
}

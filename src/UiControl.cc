#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"

uiControl * UiControl::getHandle() {
	return handle;
}

UiControl::UiControl(uiControl* hnd) {
	handle = hnd;
}

void UiControl::destroy() {
	uiControlDestroy(handle);
}

void UiControl::setParent (UiControl *parent) {
	uiControlSetParent(handle, parent->getHandle());
}

int UiControl::toplevel() {
	return uiControlToplevel(handle);
}

int UiControl::getVisible() {
	return uiControlVisible(handle);
}

void UiControl::setVisible(int visible) {
	if (visible == 1) {
		uiControlShow(handle);
	} else {
		uiControlHide(handle);
	}
}

int UiControl::getEnabled() {
	return uiControlEnabled(handle);
}

void UiControl::setEnabled(int enabled) {
	if (enabled == 1) {
		uiControlEnable(handle);
	} else {
		uiControlDisable(handle);
	}
}

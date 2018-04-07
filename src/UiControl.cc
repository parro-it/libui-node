#include "../ui.h"
#include "nbind/api.h"
#include "includes/control.h"

uiControl *UiControl::getHandle() {
	return handle;
}

UiControl::UiControl(uiControl *hnd) {
	handle = hnd;
}

void UiControl::destroy() {
	uiControlDestroy(handle);
}

void UiControl::setParent(UiControl *parent) {
	uiControlSetParent(handle, parent->getHandle());
}

bool UiControl::toplevel() {
	return uiControlToplevel(handle);
}

bool UiControl::getVisible() {
	return uiControlVisible(handle);
}

void UiControl::setVisible(bool visible) {
	if (visible == 1) {
		uiControlShow(handle);
	} else {
		uiControlHide(handle);
	}
}

bool UiControl::getEnabled() {
	return uiControlEnabled(handle);
}

void UiControl::setEnabled(bool enabled) {
	if (enabled == 1) {
		uiControlEnable(handle);
	} else {
		uiControlDisable(handle);
	}
}

NBIND_CLASS(UiControl) {
	DECLARE_CONTROL_METHODS()
}

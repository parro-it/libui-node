#include <map>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

std::map<uiControl *, UiControl *> controlsMap;

uiControl *UiControl::getHandle() {
	return handle;
}

static void _uicontrol_onDestroy(uiControl *control) {
	UiControl *wrapper = controlsMap[control];
	wrapper->onDestroy(control);
	wrapper->originalDestroy(control);
	wrapper->destroyed = true;
	controlsMap.erase(control);
}

void UiControl::onDestroy(uiControl *control) {
	// this method should be overriden
	// in control classes to perform
	// specific cleanup when natove control
	// is destroyed by libui
}

UiControl::~UiControl() {
	// printf("Control %p destroyed with wrapper %p.\n", getHandle(), this);
}

UiControl::UiControl(uiControl *hnd) {
	handle = hnd;
	originalDestroy = hnd->Destroy;
	hnd->Destroy = _uicontrol_onDestroy;
	destroyed = false;
	controlsMap[hnd] = this;
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
	method(destroy);
	method(setParent);
	method(toplevel);
	method(getVisible);
	method(setVisible);
	method(getEnabled);
	method(setEnabled);
	getset(getVisible, setVisible);
	getset(getEnabled, setEnabled);
}

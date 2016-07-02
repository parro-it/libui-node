#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiGroup::UiGroup(const char *text) : UiControl( (uiControl*) uiNewGroup(text) ) {}
UiGroup::UiGroup() : UiControl( (uiControl*) uiNewGroup("") ) {}


void UiGroup::setChild(UiControl *control) {
	uiGroupSetChild(
		(uiGroup *) getHandle(),
		control->getHandle()
	);
}

bool UiGroup::getMargined() {
	return uiGroupMargined( (uiGroup *) getHandle() );
}

void UiGroup::setMargined(bool margined) {
	uiGroupSetMargined(
		(uiGroup *) getHandle(),
		margined
	);
}

const char * UiGroup::getTitle() {
	return uiGroupTitle( (uiGroup *) getHandle() );
}

void UiGroup::setTitle(const char * title) {
	uiGroupSetTitle(
		(uiGroup *) getHandle(),
		title
	);
}

INHERITS_CONTROL_METHODS(UiGroup)

NBIND_CLASS(UiGroup) {
	construct<const char *>();
	construct<>();
	method(setChild);
	method(getTitle);
	method(setTitle);
	method(getMargined);
	method(setMargined);
	getset(getTitle, setTitle);
	getset(getMargined, setMargined);
	DECLARE_CONTROL_METHODS()
}


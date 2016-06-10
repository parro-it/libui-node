#include "../libui/ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiGroup::UiGroup(const char *text) : UiControl( (uiControl*) uiNewGroup(text) ) {}


void UiGroup::setChild(UiControl *control) {
	uiGroupSetChild(
		(uiGroup *) getHandle(),
		control->getHandle()
	);
}

int UiGroup::getMargined() {
	return uiGroupMargined( (uiGroup *) getHandle() );
}

void UiGroup::setMargined(int margined) {
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
	method(setChild);
	getset(getTitle, setTitle);
	getset(getMargined, setMargined);
	DECLARE_CONTROL_METHODS()
}


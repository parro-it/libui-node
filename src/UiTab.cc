#include "../ui.h"
#include "nbind/api.h"
#include "nbind/nbind.h"
#include "ui-node.h"


UiTab::UiTab() : UiControl( (uiControl*) uiNewTab() ) {}

INHERITS_CONTROL_METHODS(UiTab)

void UiTab::append(const char *text, UiControl *child) {
	uiTabAppend(
		(uiTab *) getHandle(),
		text,
		child->getHandle()
	);
}

void UiTab::insertAt(const char *name, int before, UiControl *child) {
	uiTabInsertAt(
		(uiTab *) getHandle(),
		name,
		before,
		child->getHandle()
	);
}

void UiTab::deleteAt(int index) {
	uiTabDelete(
		(uiTab *) getHandle(),
		index
	);
}

int UiTab::numPages() {
	return uiTabNumPages((uiTab *) getHandle());
}

bool UiTab::getMargined(int page) {
	return uiTabMargined((uiTab *) getHandle(), page);
}

void UiTab::setMargined(int page, bool margined) {
	uiTabSetMargined(
		(uiTab *) getHandle(),
		page,
		margined
	);
}

NBIND_CLASS(UiTab) {
	construct<>();
	DECLARE_CONTROL_METHODS()
	method(append);
	method(numPages);
	method(deleteAt);
	method(insertAt);
	method(getMargined);
	method(setMargined);
}



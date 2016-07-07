#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"

static void UiMenuItem_onClicked(uiMenuItem *sender, uiWindow *window, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	(*cb)();
}

void UiMenuItem::onClicked(nbind::cbFunction & cb) {
	onClickedCallback = new nbind::cbFunction(cb);
	uiMenuItemOnClicked(
		handle,
		UiMenuItem_onClicked,
		onClickedCallback
	);
}


UiMenuItem::UiMenuItem(uiMenuItem *hnd) {
	handle = hnd;
}


void UiMenuItem::enable() {
	uiMenuItemEnable(handle);
}

void UiMenuItem::disable() {
	uiMenuItemDisable(handle);
}

bool UiMenuItem::getChecked() {
	return uiMenuItemChecked(handle);
}

void UiMenuItem::setChecked(bool checked) {
	uiMenuItemSetChecked(handle, checked);
}


UiMenu::UiMenu(const char* name) {
	handle = uiNewMenu(name);
}

UiMenuItem * UiMenu::appendItem(const char* name) {
	return new UiMenuItem(uiMenuAppendItem(
		handle,
		name
	));
}

UiMenuItem * UiMenu::appendCheckItem(const char* name) {
	return new UiMenuItem(uiMenuAppendCheckItem(
		handle,
		name
	));
}

UiMenuItem * UiMenu::appendQuitItem() {
	return new UiMenuItem(uiMenuAppendQuitItem(
		handle
	));
}

UiMenuItem * UiMenu::appendPreferencesItem() {
	return new UiMenuItem(uiMenuAppendPreferencesItem(
		handle
	));
}

UiMenuItem * UiMenu::appendAboutItem() {
	return new UiMenuItem(uiMenuAppendAboutItem(
		handle
	));
}

void UiMenu::appendSeparator() {
	uiMenuAppendSeparator(
		handle
	);
}






NBIND_CLASS(UiMenu) {
	construct<const char *>();
  method(appendItem);
	method(appendCheckItem);
	method(appendQuitItem);
	method(appendPreferencesItem);
	method(appendAboutItem);
	method(appendSeparator);
}

NBIND_CLASS(UiMenuItem) {
	construct<uiMenuItem *>();
	method(enable);
	method(disable);
	method(onClicked);
	getset(getChecked, setChecked);
}


#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

// TODO - document
class UiMenuItem {
	DEFINE_EVENT(onClicked)

  private:
	uiMenuItem *handle;

  public:
	UiMenuItem(uiMenuItem *hnd);
	void enable();
	void disable();
	bool getChecked();
	void setChecked(bool checked);
};

// TODO - document
class UiMenu {
  private:
	uiMenu *handle;

  public:
	UiMenu(std::string name);
	UiMenuItem *appendItem(std::string name);
	UiMenuItem *appendCheckItem(std::string name);
	UiMenuItem *appendQuitItem();
	UiMenuItem *appendPreferencesItem();
	UiMenuItem *appendAboutItem();
	void appendSeparator();
};

static void UiMenuItem_onClicked(uiMenuItem *sender, uiWindow *window,
								 void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	(*cb)();
}

void UiMenuItem::onClicked(nbind::cbFunction &cb) {
	onClickedCallback = new nbind::cbFunction(cb);
	uiMenuItemOnClicked(handle, UiMenuItem_onClicked, onClickedCallback);
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

UiMenu::UiMenu(std::string name) {
	handle = uiNewMenu(name.c_str());
}

UiMenuItem *UiMenu::appendItem(std::string name) {
	return new UiMenuItem(uiMenuAppendItem(handle, name.c_str()));
}

UiMenuItem *UiMenu::appendCheckItem(std::string name) {
	return new UiMenuItem(uiMenuAppendCheckItem(handle, name.c_str()));
}

UiMenuItem *UiMenu::appendQuitItem() {
	return new UiMenuItem(uiMenuAppendQuitItem(handle));
}

UiMenuItem *UiMenu::appendPreferencesItem() {
	return new UiMenuItem(uiMenuAppendPreferencesItem(handle));
}

UiMenuItem *UiMenu::appendAboutItem() {
	return new UiMenuItem(uiMenuAppendAboutItem(handle));
}

void UiMenu::appendSeparator() {
	uiMenuAppendSeparator(handle);
}

NBIND_CLASS(UiMenu) {
	construct<std::string>();
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

#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiCombobox : public UiControl {
	DEFINE_EVENT(onSelected)

  public:
	UiCombobox();

	void append(std::string text);
	int getSelected();
	void setSelected(int n);
	~UiCombobox();
	void onDestroy(uiControl *control) override;
};

void UiCombobox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onSelected);
}

UiCombobox::~UiCombobox() {
	// printf("UiCombobox %p destroyed with wrapper %p.\n", getHandle(), this);
}

UiCombobox::UiCombobox() : UiControl((uiControl *)uiNewCombobox()) {}

IMPLEMENT_EVENT(UiCombobox, uiCombobox, onSelected, uiComboboxOnSelected)

void UiCombobox::append(std::string text) {
	uiComboboxAppend((uiCombobox *)getHandle(), text.c_str());
}

int UiCombobox::getSelected() {
	return uiComboboxSelected((uiCombobox *)getHandle());
}

void UiCombobox::setSelected(int n) {
	uiComboboxSetSelected((uiCombobox *)getHandle(), n);
	if (onSelectedCallback != NULL) {
		(*onSelectedCallback)();
	}
}

NBIND_CLASS(UiCombobox) {
	inherit(UiControl);
	construct<>();
	method(append);
	getset(getSelected, setSelected);
	method(getSelected);
	method(setSelected);
	method(onSelected);
}

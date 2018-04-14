#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiRadioButtons : public UiControl {
	DEFINE_EVENT(onSelected)

  public:
	UiRadioButtons();
	void append(std::string text);
	int getSelected();
	void setSelected(int n);

	~UiRadioButtons();
	void onDestroy(uiControl *control) override;
};

UiRadioButtons::~UiRadioButtons() {
	// printf("UiRadioButtons %p destroyed with wrapper %p.\n", getHandle(),
	// this);
}

void UiRadioButtons::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/
	DISPOSE_EVENT(onSelected);
}

UiRadioButtons::UiRadioButtons()
	: UiControl((uiControl *)uiNewRadioButtons()) {}

IMPLEMENT_EVENT(UiRadioButtons, uiRadioButtons, onSelected,
				uiRadioButtonsOnSelected)

int UiRadioButtons::getSelected() {
	return uiRadioButtonsSelected((uiRadioButtons *)getHandle());
}

void UiRadioButtons::setSelected(int n) {
	uiRadioButtonsSetSelected((uiRadioButtons *)getHandle(), n);
	if (onSelectedCallback != NULL) {
		(*onSelectedCallback)();
	}
}

void UiRadioButtons::append(std::string text) {
	uiRadioButtonsAppend(uiRadioButtons(getHandle()), text.c_str());
}

NBIND_CLASS(UiRadioButtons) {
	inherit(UiControl);
	construct<>();
	method(append);
	getset(getSelected, setSelected);
	method(getSelected);
	method(setSelected);
	method(onSelected);
}

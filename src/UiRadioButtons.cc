#include <string>
#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiRadioButtons : public UiControl {
	DEFINE_EVENT(onSelected)

  public:
	UiRadioButtons();
	void append(std::string text);
	int getSelected();
	void setSelected(int n);

	DEFINE_CONTROL_METHODS()
};

UiRadioButtons::UiRadioButtons()
	: UiControl((uiControl *)uiNewRadioButtons()) {}

INHERITS_CONTROL_METHODS(UiRadioButtons)

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
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	method(append);
	getset(getSelected, setSelected);
	method(getSelected);
	method(setSelected);
	method(onSelected);
}

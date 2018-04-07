#include <string>
#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiForm : public UiControl {
  public:
	UiForm();
	DEFINE_CONTROL_METHODS()
	void append(std::string label, UiControl *c, bool stretchy);
	void deleteAt(int index);
	bool getPadded();
	void setPadded(bool padded);
};

UiForm::UiForm() : UiControl(uiControl(uiNewForm())) {}

void UiForm::append(std::string label, UiControl *c, bool stretchy) {
	uiFormAppend(uiForm(getHandle()), label.c_str(), c->getHandle(), stretchy);
}

void UiForm::deleteAt(int index) {
	uiFormDelete(uiForm(getHandle()), index);
}

bool UiForm::getPadded() {
	return uiFormPadded(uiForm(getHandle()));
}

void UiForm::setPadded(bool padded) {
	uiFormSetPadded(uiForm(getHandle()), padded);
}

INHERITS_CONTROL_METHODS(UiForm)

NBIND_CLASS(UiForm) {
	construct<>();
	method(append);
	method(deleteAt);
	method(getPadded);
	method(setPadded);
	getset(getPadded, setPadded);
	DECLARE_CHILD_CONTROL_METHODS()
}

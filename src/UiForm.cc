#include <string>
#include "ui.h"

#include "nbind/api.h"
#include "control.h"

class UiForm : public UiControl {
  public:
	UiForm();
	void append(std::string label, std::shared_ptr<UiControl> c, bool stretchy);
	void deleteAt(int index);
	bool getPadded();
	void setPadded(bool padded);
	~UiForm();
	void onDestroy(uiControl *control) override;

  private:
	// this hold references to children controls
	// to avoid them being garbage collected
	// until not destroyed.
	std::vector<std::shared_ptr<UiControl>> children;
};
UiForm::~UiForm() {
	//	printf("UiForm %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiForm::onDestroy(uiControl *control) {
	/*
		freeing children to allow JS to garbage collect their wrapper classes
		when there are no references to them left in JS code.
	*/
	children.clear();
}
UiForm::UiForm() : UiControl(uiControl(uiNewForm())) {}

void UiForm::append(std::string label, std::shared_ptr<UiControl> c,
					bool stretchy) {
	children.push_back(c);

	uiFormAppend(uiForm(getHandle()), label.c_str(), c.get()->getHandle(),
				 stretchy);
}

void UiForm::deleteAt(int index) {
	children.erase(children.begin() + index);
	uiFormDelete(uiForm(getHandle()), index);
}

bool UiForm::getPadded() {
	return uiFormPadded(uiForm(getHandle()));
}

void UiForm::setPadded(bool padded) {
	uiFormSetPadded(uiForm(getHandle()), padded);
}

NBIND_CLASS(UiForm) {
	inherit(UiControl);
	construct<>();
	method(append);
	method(deleteAt);
	method(getPadded);
	method(setPadded);
	getset(getPadded, setPadded);
}

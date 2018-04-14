#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiGroup : public UiControl {
  private:
	// this hold a reference to child control
	// to avoid it being garbage collected
	// until not destroyed.
	std::shared_ptr<UiControl> child;

  public:
	UiGroup(std::string text);
	UiGroup();
	~UiGroup();
	void onDestroy(uiControl *control) override;
	void setChild(std::shared_ptr<UiControl> control);
	bool getMargined();
	void setMargined(bool margined);
	std::string getTitle();
	void setTitle(std::string title);
};

UiGroup::~UiGroup() {
	//	printf("UiGroup %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiGroup::onDestroy(uiControl *control) {
	/*
		freeing children to allow JS to garbage collect their wrapper classes
		when there are no references to them left in JS code.
	*/
	child = nullptr;
}
UiGroup::UiGroup(std::string text)
	: UiControl(uiControl(uiNewGroup(text.c_str()))) {}
UiGroup::UiGroup() : UiControl(uiControl(uiNewGroup(""))) {}

void UiGroup::setChild(std::shared_ptr<UiControl> control) {
	child = control;
	uiGroupSetChild(uiGroup(getHandle()), control.get()->getHandle());
}

bool UiGroup::getMargined() {
	return uiGroupMargined(uiGroup(getHandle()));
}

void UiGroup::setMargined(bool margined) {
	uiGroupSetMargined(uiGroup(getHandle()), margined);
}

std::string UiGroup::getTitle() {
	char *char_ptr = uiGroupTitle(uiGroup(getHandle()));
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

void UiGroup::setTitle(std::string title) {
	uiGroupSetTitle(uiGroup(getHandle()), title.c_str());
}

NBIND_CLASS(UiGroup) {
	inherit(UiControl);
	construct<std::string>();
	construct<>();
	method(setChild);
	method(getTitle);
	method(setTitle);
	method(getMargined);
	method(setMargined);
	getset(getTitle, setTitle);
	getset(getMargined, setMargined);
}

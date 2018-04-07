#include <string>
#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiGroup : public UiControl {
  public:
	UiGroup(std::string text);
	UiGroup();
	void setChild(UiControl *control);
	bool getMargined();
	void setMargined(bool margined);
	std::string getTitle();
	void setTitle(std::string title);
	DEFINE_CONTROL_METHODS()
};

UiGroup::UiGroup(std::string text)
	: UiControl(uiControl(uiNewGroup(text.c_str()))) {}
UiGroup::UiGroup() : UiControl(uiControl(uiNewGroup(""))) {}

void UiGroup::setChild(UiControl *control) {
	uiGroupSetChild(uiGroup(getHandle()), control->getHandle());
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

INHERITS_CONTROL_METHODS(UiGroup)

NBIND_CLASS(UiGroup) {
	construct<std::string>();
	construct<>();
	method(setChild);
	method(getTitle);
	method(setTitle);
	method(getMargined);
	method(setMargined);
	getset(getTitle, setTitle);
	getset(getMargined, setMargined);
	DECLARE_CHILD_CONTROL_METHODS()
}

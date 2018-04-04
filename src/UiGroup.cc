#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiGroup : public UiControl {
  public:
	UiGroup(const char *text);
	UiGroup();
	void setChild(UiControl *control);
	bool getMargined();
	void setMargined(bool margined);
	const char *getTitle();
	void setTitle(const char *title);
	DEFINE_CONTROL_METHODS()
};

UiGroup::UiGroup(const char *text) : UiControl((uiControl *)uiNewGroup(text)) {}
UiGroup::UiGroup() : UiControl((uiControl *)uiNewGroup("")) {}

void UiGroup::setChild(UiControl *control) {
	uiGroupSetChild((uiGroup *)getHandle(), control->getHandle());
}

bool UiGroup::getMargined() {
	return uiGroupMargined((uiGroup *)getHandle());
}

void UiGroup::setMargined(bool margined) {
	uiGroupSetMargined((uiGroup *)getHandle(), margined);
}

const char *UiGroup::getTitle() {
	return uiGroupTitle((uiGroup *)getHandle());
}

void UiGroup::setTitle(const char *title) {
	uiGroupSetTitle((uiGroup *)getHandle(), title);
}

INHERITS_CONTROL_METHODS(UiGroup)

NBIND_CLASS(UiGroup) {
	construct<const char *>();
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

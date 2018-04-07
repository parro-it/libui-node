#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiTab : public UiControl {
  public:
	UiTab();
	void append(std::string text, UiControl *child);
	void insertAt(std::string name, int before, UiControl *child);
	void deleteAt(int index);
	int numPages();
	bool getMargined(int page);
	void setMargined(int page, bool margined);

	DEFINE_CONTROL_METHODS()
};

UiTab::UiTab() : UiControl((uiControl *)uiNewTab()) {}

INHERITS_CONTROL_METHODS(UiTab)

void UiTab::append(std::string text, UiControl *child) {
	uiTabAppend(uiTab(getHandle()), text.c_str(), child->getHandle());
}

void UiTab::insertAt(std::string name, int before, UiControl *child) {
	uiTabInsertAt(uiTab(getHandle()), name.c_str(), before, child->getHandle());
}

void UiTab::deleteAt(int index) {
	uiTabDelete(uiTab(getHandle()), index);
}

int UiTab::numPages() {
	return uiTabNumPages(uiTab(getHandle()));
}

bool UiTab::getMargined(int page) {
	return uiTabMargined(uiTab(getHandle()), page);
}

void UiTab::setMargined(int page, bool margined) {
	uiTabSetMargined(uiTab(getHandle()), page, margined);
}

NBIND_CLASS(UiTab) {
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	method(append);
	method(numPages);
	method(deleteAt);
	method(insertAt);
	method(getMargined);
	method(setMargined);
}

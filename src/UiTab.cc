#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiTab : public UiControl {
  public:
	UiTab();
	void append(std::string text, std::shared_ptr<UiControl> child);
	void insertAt(std::string name, int before,
				  std::shared_ptr<UiControl> child);
	void deleteAt(int index);
	int numPages();
	bool getMargined(int page);
	void setMargined(int page, bool margined);

	~UiTab();
	void onDestroy(uiControl *control) override;

  private:
	// this hold references to children controls
	// to avoid them being garbage collected
	// until not destroyed.
	std::vector<std::shared_ptr<UiControl>> children;
};

UiTab::~UiTab() {
	//	printf("UiTab %p destroyed with wrapper %p.\n", getHandle(), this);
}

void UiTab::onDestroy(uiControl *control) {
	/*
		freeing children to allow JS to garbage collect their wrapper classes
		when there are no references to them left in JS code.
	*/
	children.clear();
}
UiTab::UiTab() : UiControl((uiControl *)uiNewTab()) {}

void UiTab::append(std::string text, std::shared_ptr<UiControl> child) {
	children.push_back(child);
	uiTabAppend(uiTab(getHandle()), text.c_str(), child.get()->getHandle());
}

void UiTab::insertAt(std::string name, int before,
					 std::shared_ptr<UiControl> child) {
	children.insert(children.begin() + before, child);
	uiTabInsertAt(uiTab(getHandle()), name.c_str(), before,
				  child.get()->getHandle());
}

void UiTab::deleteAt(int index) {
	children.erase(children.begin() + index);
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
	inherit(UiControl);
	construct<>();
	method(append);
	method(numPages);
	method(deleteAt);
	method(insertAt);
	method(getMargined);
	method(setMargined);
}

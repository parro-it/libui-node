#include <string>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"
#include "values.h"

class UiWindow {
	DEFINE_EVENT(onClosing)
	DEFINE_EVENT(onContentSizeChanged)

  private:
	uiWindow *win;

  public:
	UiWindow(std::string title, int width, int height, bool hasMenubar);
	uiWindow *getHandle();
	void show();
	void close();
	void setMargined(bool margined);
	bool getMargined();
	void setChild(UiControl *control);
	void setTitle(std::string title);
	std::string getTitle();
	bool getFullscreen();
	void setFullscreen(bool value);
	bool getBorderless();
	void setBorderless(bool value);
	Size getContentSize();
	void setContentSize(Size value);
};

static int UiWindow_onClosing(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	(*cb)();
	return 0;
}

void UiWindow::onClosing(nbind::cbFunction &cb) {
	onClosingCallback = new nbind::cbFunction(cb);
	uiWindowOnClosing(uiWindow(getHandle()), UiWindow_onClosing,
					  onClosingCallback);
}

static void UiWindow_onContentSizeChanged(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	(*cb)();
}

void UiWindow::onContentSizeChanged(nbind::cbFunction &cb) {
	onContentSizeChangedCallback = new nbind::cbFunction(cb);
	uiWindowOnContentSizeChanged(uiWindow(getHandle()),
								 UiWindow_onContentSizeChanged,
								 onContentSizeChangedCallback);
}

UiWindow::UiWindow(std::string title, int width, int height, bool hasMenubar) {
	win = uiNewWindow(title.c_str(), width, height, hasMenubar);
}

uiWindow *UiWindow::getHandle() {
	return win;
}

void UiWindow::show() {
	uiControlShow(uiControl(win));
}

void UiWindow::close() {
	uiControlDestroy(uiControl(win));
}

void UiWindow::setMargined(bool margined) {
	uiWindowSetMargined(win, margined);
}

bool UiWindow::getMargined() {
	return uiWindowMargined(win);
}

void UiWindow::setChild(UiControl *control) {
	uiWindowSetChild(win, control->getHandle());
}

void UiWindow::setTitle(std::string title) {
	uiWindowSetTitle(win, title.c_str());
}

std::string UiWindow::getTitle() {
	char *char_ptr = uiWindowTitle(win);
	std::string s(char_ptr);
	uiFreeText(char_ptr);
	return s;
}

bool UiWindow::getFullscreen() {
	return uiWindowFullscreen(win);
}

void UiWindow::setFullscreen(bool value) {
	uiWindowSetFullscreen(win, value);
}

void UiWindow::setBorderless(bool value) {
	uiWindowSetBorderless(win, value);
}
bool UiWindow::getBorderless() {
	return uiWindowBorderless(win);
}

void UiWindow::setContentSize(Size value) {
	uiWindowSetContentSize(win, value.getWidth(), value.getHeight());
}

Size UiWindow::getContentSize() {
	int w = 0;
	int h = 0;
	uiWindowContentSize(win, &w, &h);
	return Size(w, h);
}

NBIND_CLASS(UiWindow) {
	construct<std::string, int, int, bool>();
	method(show);
	method(close);
	method(setChild);
	method(onClosing);
	method(onContentSizeChanged);
	getset(getMargined, setMargined);
	getset(getTitle, setTitle);

	getset(getContentSize, setContentSize);
	method(getContentSize);
	method(setContentSize);
	method(onContentSizeChanged);

	getset(getFullscreen, setFullscreen);
	method(getFullscreen);
	method(setFullscreen);
	getset(getBorderless, setBorderless);
	method(getBorderless);
	method(setBorderless);
}

struct UiDialogs {

	static std::string openFile(UiWindow *parent) {
		char *char_ptr = uiOpenFile(parent->getHandle());
		std::string s(char_ptr);
		uiFreeText(char_ptr);
		return s;
	}

	static std::string saveFile(UiWindow *parent) {
		char *char_ptr = uiSaveFile(parent->getHandle());
		std::string s(char_ptr);
		uiFreeText(char_ptr);
		return s;
	}

	static void msgBox(UiWindow *parent, std::string title,
					   std::string description) {
		uiMsgBox(parent->getHandle(), title.c_str(), description.c_str());
	}

	static void msgBoxError(UiWindow *parent, std::string title,
							std::string description) {
		uiMsgBoxError(parent->getHandle(), title.c_str(), description.c_str());
	}
};

NBIND_CLASS(UiDialogs) {
	method(openFile);
	method(saveFile);
	method(msgBox);
	method(msgBoxError);
}

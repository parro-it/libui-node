#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"

class UiWindow {
	DEFINE_EVENT(onClosing)
	DEFINE_EVENT(onContentSizeChanged)

  private:
	uiWindow *win;

  public:
	UiWindow(const char *title, int width, int height, bool hasMenubar);
	uiWindow *getHandle();
	void show();
	void close();
	void setMargined(bool margined);
	bool getMargined();
	void setChild(UiControl *control);
	void setTitle(const char *title);
	const char *getTitle();
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
	uiWindowOnClosing((uiWindow *)getHandle(), UiWindow_onClosing,
					  onClosingCallback);
}

static void UiWindow_onContentSizeChanged(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *)data;
	(*cb)();
}

void UiWindow::onContentSizeChanged(nbind::cbFunction &cb) {
	onContentSizeChangedCallback = new nbind::cbFunction(cb);
	uiWindowOnContentSizeChanged((uiWindow *)getHandle(),
								 UiWindow_onContentSizeChanged,
								 onContentSizeChangedCallback);
}

UiWindow::UiWindow(const char *title, int width, int height, bool hasMenubar) {
	win = uiNewWindow(title, width, height, hasMenubar);
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

void UiWindow::setTitle(const char *title) {
	uiWindowSetTitle(win, title);
}

const char *UiWindow::getTitle() {
	return uiWindowTitle(win);
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
	construct<const char *, int, int, bool>();
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

	static char *openFile(UiWindow *parent) {
		return uiOpenFile(parent->getHandle());
	}

	static char *saveFile(UiWindow *parent) {
		return uiSaveFile(parent->getHandle());
	}

	static void msgBox(UiWindow *parent, const char *title,
					   const char *description) {
		uiMsgBox(parent->getHandle(), title, description);
	}

	static void msgBoxError(UiWindow *parent, const char *title,
							const char *description) {
		uiMsgBoxError(parent->getHandle(), title, description);
	}
};

NBIND_CLASS(UiDialogs) {
	method(openFile);
	method(saveFile);
	method(msgBox);
	method(msgBoxError);
}

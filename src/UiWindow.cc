#include "../ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"


Point UiWindow::getPosition() {
	int x = 0;
	int y = 0;
	uiWindowPosition(
		(uiWindow *) getHandle(),
		&x,
		&y
	);
	return Point(x, y);
}

void UiWindow::setPosition(Point position) {
	uiWindowSetPosition(
		(uiWindow *) getHandle(),
		position.getX(),
		position.getY()
	);
}

void UiWindow::center() {
	uiWindowCenter((uiWindow *) getHandle());
}



static int UiWindow_onClosing(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	(*cb)();
	return 0;
}

void UiWindow::onClosing(nbind::cbFunction & cb) {
	onClosingCallback = new nbind::cbFunction(cb);
	uiWindowOnClosing(
		(uiWindow *) getHandle(),
		UiWindow_onClosing,
		onClosingCallback
	);
}

static void UiWindow_onContentSizeChanged(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	(*cb)();
}

void UiWindow::onContentSizeChanged(nbind::cbFunction & cb) {
	onContentSizeChangedCallback = new nbind::cbFunction(cb);
	uiWindowOnContentSizeChanged(
		(uiWindow *) getHandle(),
		UiWindow_onContentSizeChanged,
		onContentSizeChangedCallback
	);
}


static void UiWindow_onPositionChanged(uiWindow *w, void *data) {
	nbind::cbFunction *cb = (nbind::cbFunction *) data;
	(*cb)();
}

void UiWindow::onPositionChanged(nbind::cbFunction & cb) {
	onPositionChangedCallback = new nbind::cbFunction(cb);
	uiWindowOnPositionChanged(
		(uiWindow *) getHandle(),
		UiWindow_onPositionChanged,
		onPositionChangedCallback
	);
}

UiWindow::UiWindow(const char* title, int width, int height, bool hasMenubar) {
	win = uiNewWindow(title, width, height, hasMenubar);
}

uiWindow * UiWindow::getHandle() {
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

void UiWindow::setTitle(const char * title) {
	uiWindowSetTitle(win, title);
}

const char * UiWindow::getTitle() {
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
//	printf("setting content to (%d x %d)\n", value.getWidth(), value.getHeight());
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
  getset(getPosition, setPosition);
  method(getPosition);
  method(setPosition);
  method(onPositionChanged);
  method(center);

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


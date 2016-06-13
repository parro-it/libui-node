#include "../libui/ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"



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

UiWindow::UiWindow(const char* title, int width, int height, int hasMenubar) {
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

void UiWindow::setMargined(int margined) {
	uiWindowSetMargined(win, margined);
}

int UiWindow::getMargined() {
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

NBIND_CLASS(UiWindow) {
  construct<const char *, int, int, int>();
  method(show);
  method(close);
  method(setChild);
  method(onClosing);
  getset(getMargined, setMargined);
  getset(getTitle, setTitle);
  method(getMargined);
  method(setMargined);
  method(setTitle);
  method(getTitle);
}


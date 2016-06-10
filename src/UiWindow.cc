#include "../libui/ui.h"
#include "ui-node.h"
#include "nbind/api.h"
#include "nbind/nbind.h"


static int closing(uiWindow *w, void *data)
{
	uiControlDestroy(uiControl(w));
	return 0;
}

UiWindow::UiWindow(const char* title, int width, int height, int hasMenubar) {
	win = uiNewWindow(title, width, height, hasMenubar);
	uiWindowOnClosing(win, closing, NULL);
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

NBIND_CLASS(UiWindow) {
  construct<const char *, int, int, int>();
  method(show);
  method(close);
  method(setChild);
  getset(getMargined, setMargined);
}


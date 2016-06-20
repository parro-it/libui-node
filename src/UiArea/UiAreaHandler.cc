#include "../../libui/ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

void Draw (UiAreaHandler *self, UiArea *area, uiAreaDrawParams *params) {
	(*(self->draw))(self, area, new UiAreaDrawParams(params));
}

void MouseEvent (UiAreaHandler *self, UiArea *area, uiAreaMouseEvent *event) {
	(*(self->mouseEvent))(self, area, new UiAreaMouseEvent(event));
}

void MouseCrossed (UiAreaHandler *self, UiArea *area, int left) {
	(*(self->mouseCrossed))(self, area, left);
}

void DragBroken (UiAreaHandler *self, UiArea *area) {
	(*(self->dragBroken))(self, area);
}

int KeyEvent (UiAreaHandler *self, UiArea *area, uiAreaKeyEvent *event) {
	return (self->keyEvent)->call<int>(self, area, new UiAreaKeyEvent(event));
}


UiAreaHandler * UiAreaHandlerFactory::build(
	nbind::cbFunction &drawCb,
	nbind::cbFunction &mouseEventCb ,
	nbind::cbFunction &mouseCrossedCb,
	nbind::cbFunction &dragBrokenCb,
	nbind::cbFunction &keyEventCb
) {
	UiAreaHandler *handler = new UiAreaHandler();

	handler->draw = new nbind::cbFunction(drawCb);
	handler->mouseEvent = new nbind::cbFunction(mouseEventCb);
	handler->mouseCrossed = new nbind::cbFunction(mouseCrossedCb);
	handler->dragBroken = new nbind::cbFunction(dragBrokenCb);
	handler->keyEvent = new nbind::cbFunction(keyEventCb);

	handler->Draw = Draw;
	handler->MouseEvent = MouseEvent;
	handler->MouseCrossed = MouseCrossed;
	handler->DragBroken = DragBroken;
	handler->KeyEvent = KeyEvent;

	return handler;
}

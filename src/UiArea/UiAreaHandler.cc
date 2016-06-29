#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


void Draw (UiAreaHandler *self, uiArea *area, uiAreaDrawParams *params) {
	UiAreaDrawParams *pp = new UiAreaDrawParams(params);
	(*self->draw)(areasMap[area], pp);
}

void MouseEvent (UiAreaHandler *self, uiArea *area, uiAreaMouseEvent *event) {
	UiAreaMouseEvent *ev = new UiAreaMouseEvent(event);
	(*(self->mouseEvent))(areasMap[area], ev);
}

void MouseCrossed (UiAreaHandler *self, uiArea *area, int left) {
	(*(self->mouseCrossed))(areasMap[area], left);
}

void DragBroken (UiAreaHandler *self, uiArea *area) {
	(*(self->dragBroken))(areasMap[area]);
}

int KeyEvent (UiAreaHandler *self, uiArea *area, uiAreaKeyEvent *event) {
	UiAreaKeyEvent * ev = new UiAreaKeyEvent(event);
	return (self->keyEvent)->call<int>(areasMap[area], ev);
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

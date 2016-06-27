#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


void Draw (UiAreaHandler *self, UiArea *area, uiAreaDrawParams *params) {
	printf("Drawing, hnd:%p, area:%p, params:%p\n, draw:%p\n", self, area, params, self->draw);
	UiAreaDrawParams *pp = new UiAreaDrawParams(params);
	printf("params created: %p\n", pp);
	(*self->draw)((void*)NULL,(void*) NULL, (void*) NULL); // (self, area, pp);
	printf("Drawing called, hnd:%p, area:%p, params:%p\n", self, area, params);
}

void MouseEvent (UiAreaHandler *self, UiArea *area, uiAreaMouseEvent *event) {
	UiAreaMouseEvent * ev = new UiAreaMouseEvent();
	ev->setEvent(event);
	(*(self->mouseEvent))((void*)NULL, (void*)NULL, ev);
}

void MouseCrossed (UiAreaHandler *self, UiArea *area, int left) {
	//(*(self->mouseCrossed))(self, area, left);
}

void DragBroken (UiAreaHandler *self, UiArea *area) {
	//(*(self->dragBroken))(self, area);
}

int KeyEvent (UiAreaHandler *self, UiArea *area, uiAreaKeyEvent *event) {
	return 0; //(self->keyEvent)->call<int>(self, area, new UiAreaKeyEvent(event));
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
printf("address of dra is %p\n", handler->draw);
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

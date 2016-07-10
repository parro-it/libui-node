#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

UiAreaMouseEvent::UiAreaMouseEvent(uiAreaMouseEvent * event) {
	e = event;
}

double UiAreaMouseEvent::getX() {
	return e->X;
}

double UiAreaMouseEvent::getY() {
	return e->Y;
}

double UiAreaMouseEvent::getAreaWidth() {
	return e->AreaWidth;
}

double UiAreaMouseEvent::getAreaHeight() {
	return e->AreaHeight;
}

int UiAreaMouseEvent::getDown() {
	return e->Down;
}

int UiAreaMouseEvent::getUp() {
	return e->Up;
}

int UiAreaMouseEvent::getCount() {
	return e->Count;
}

int UiAreaMouseEvent::getModifiers() {
	return e->Modifiers;
}

unsigned int UiAreaMouseEvent::getHeld1To64() {
	return e->Held1To64;
}

NBIND_CLASS(UiAreaMouseEvent) {
  construct<uiAreaMouseEvent *>();
  method(getX);
  method(getY);
  method(getAreaWidth);
  method(getAreaHeight);
  method(getDown);
  method(getCount);
  method(getModifiers);
  method(getHeld1To64);
}


#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"




UiAreaKeyEvent::UiAreaKeyEvent(uiAreaKeyEvent *event) {
	e = event;
}

char * UiAreaKeyEvent::getKey() {
	char *k = new char[2];
	k[0] = e->Key;
	k[1] = '\0';
	return k;
}

int UiAreaKeyEvent::getExtKey() {
	return e->ExtKey;
}

int UiAreaKeyEvent::getModifier() {
	return e->Modifier;
}

int UiAreaKeyEvent::getModifiers() {
	return e->Modifiers;
}

int UiAreaKeyEvent::getUp() {
	return e->Up;
}

NBIND_CLASS(UiAreaKeyEvent) {
	construct<uiAreaKeyEvent *>();
	method(getKey);
	method(getExtKey);
	method(getModifier);
	method(getModifiers);
	method(getUp);
}

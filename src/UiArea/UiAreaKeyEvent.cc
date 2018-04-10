#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

#include <string>

UiAreaKeyEvent::UiAreaKeyEvent(uiAreaKeyEvent *event) {
	e = event;
}

std::string UiAreaKeyEvent::getKey() {
	return std::string(1, e->Key);
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

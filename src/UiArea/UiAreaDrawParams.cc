#include "../../libui/ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


UiAreaDrawParams::UiAreaDrawParams(uiAreaDrawParams *params) {
	p = params;
}

void * UiAreaDrawParams::getContext() {
	return p->Context;
}

double UiAreaDrawParams::getAreaWidth() {
	return p->AreaWidth;
}

double UiAreaDrawParams::getAreaHeight() {
	return p->AreaHeight;
}

double UiAreaDrawParams::getClipX() {
	return p->ClipX;
}

double UiAreaDrawParams::getClipY() {
	return p->ClipY;
}

double UiAreaDrawParams::getClipWidth() {
	return p->ClipWidth;
}

double UiAreaDrawParams::getClipHeight() {
	return p->ClipHeight;
}


NBIND_CLASS(UiAreaDrawParams) {
	method(getContext);
	method(getAreaWidth);
	method(getAreaHeight);
	method(getClipX);
	method(getClipY);
	method(getClipWidth);
	method(getClipHeight);
}

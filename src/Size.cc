#include "values.h"

Size::Size(int width, int height) {
	w = width;
	h = height;
}

int Size::getWidth() {
	return w;
}

void Size::setWidth(int value) {
	w = value;
}

int Size::getHeight() {
	return h;
}

void Size::setHeight(int value) {
	h = value;
}

void Size::toJS(nbind::cbOutput output) {
	output(w, h);
}

NBIND_CLASS(Size) {
	construct<int, int>();
	method(getWidth);
	method(setWidth);
	method(getHeight);
	method(setHeight);

	getset(getWidth, setWidth);
	getset(getHeight, setHeight);
}

#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

DrawTextLayout::DrawTextLayout(const char *text, DrawTextFont *defaultFont, double width) {
	handle = uiDrawNewTextLayout(text, defaultFont->getHandle(), width);
	w = width;
}

void DrawTextLayout::free() {
	uiDrawFreeTextLayout(handle);
}

void DrawTextLayout::setWidth(double value) {
	uiDrawTextLayoutSetWidth(handle, value);
	w = value;
}

double DrawTextLayout::getWidth() {
	return w;
}

uiDrawTextLayout * DrawTextLayout::getHandle() {
	return handle;
}

SizeDouble DrawTextLayout::getExtents() {
	double width;
	double height;
	uiDrawTextLayoutExtents(handle, &width, &height);
	return SizeDouble(width, height);
}


void DrawTextLayout::setColor(int startChar, int endChar, Color color) {
	uiDrawTextLayoutSetColor(
		handle,
		startChar,
		endChar,
		color.getR(),
		color.getG(),
		color.getB(),
		color.getA()
	);
}





NBIND_CLASS(DrawTextLayout) {
		construct<const char *, DrawTextFont *, double>();
		method(free);
		method(setWidth);
		method(getWidth);
		method(getExtents);
		method(setColor);
		getset(getWidth, setWidth);
}


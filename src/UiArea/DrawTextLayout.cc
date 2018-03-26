#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"

DrawTextLayout::DrawTextLayout(const char *text, UiFontDescriptor *defaultFont, double width, int align) {
	handle = uiDrawNewTextLayout({
		text, defaultFont->getHandle(), width, align
	});
}

void DrawTextLayout::free() {
	uiDrawFreeTextLayout(handle);
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

NBIND_CLASS(DrawTextLayout) {
		construct<const char *, UiFontDescriptor *, double, int>();
		method(free);
		method(getExtents);
}


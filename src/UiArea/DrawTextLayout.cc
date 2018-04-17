#include "area.h"
#include "ui.h"

DrawTextLayout::DrawTextLayout(AttributedString *str,
							   FontDescriptor *defaultFont, double width,
							   int align) {
	uiDrawTextLayoutParams params = {str->getHandle(), defaultFont->getHandle(),
									 width, (uiDrawTextAlign)align};

	handle = uiDrawNewTextLayout(&params);
}

DrawTextLayout::~DrawTextLayout() {
	uiDrawFreeTextLayout(handle);
}

uiDrawTextLayout *DrawTextLayout::getHandle() {
	return handle;
}

SizeDouble DrawTextLayout::getExtents() {
	double width;
	double height;
	uiDrawTextLayoutExtents(handle, &width, &height);
	return SizeDouble(width, height);
}

NBIND_CLASS(DrawTextLayout) {
	construct<AttributedString *, FontDescriptor *, double, int>();
	method(getExtents);
}

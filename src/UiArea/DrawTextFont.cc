#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


DrawTextFont::DrawTextFont () {}
DrawTextFont::DrawTextFont (uiDrawTextFont * h) {
	handle = h;
}

uiDrawTextFont * DrawTextFont::getHandle () {
	return handle;
}

void DrawTextFont::free() {
	uiDrawFreeTextFont(handle);
}

DrawTextFontDescriptor * DrawTextFont::describe() {
	uiDrawTextFontDescriptor * desc = new uiDrawTextFontDescriptor();
	uiDrawTextFontDescribe(handle, desc);
	return new DrawTextFontDescriptor(desc);
}

DrawTextFontMetrics * DrawTextFont::getMetrics() {
	uiDrawTextFontMetrics * metrics = new uiDrawTextFontMetrics();
	uiDrawTextFontGetMetrics(handle, metrics);
	return new DrawTextFontMetrics(metrics);
}

std::vector<char *> DrawTextFont::listFontFamilies() {
	uiDrawFontFamilies * families = uiDrawListFontFamilies();
	int numFamilies = uiDrawFontFamiliesNumFamilies(families);
	std::vector<char *> result(numFamilies);

	for (int i = 0; i < numFamilies; i++) {
		result[i] = uiDrawFontFamiliesFamily(families, i);
	}

	uiDrawFreeFontFamilies(families);

	return result;
}

void DrawTextFont::loadClosestFont(const char *family, double size, int weight, int italic, int stretch) {
	uiDrawTextFontDescriptor *descr = new uiDrawTextFontDescriptor();
	descr->Family = family;
	descr->Size = size;
	descr->Weight = weight;
	descr->Italic = italic;
	descr->Stretch = stretch;

	handle = uiDrawLoadClosestFont(descr);
//	printf("font handle %p\n", handle);
}

NBIND_CLASS(DrawTextFont) {
	construct<>();
	method(listFontFamilies);
	method(loadClosestFont);
	method(free);
	method(describe);
	method(getMetrics);
}

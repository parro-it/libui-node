#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


DrawTextFont::DrawTextFont (uiDrawTextFont * hnd) {
	handle = hnd;
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

DrawTextFont * DrawTextFont::loadClosestFont(const char *family, double size, int weight, int italic, int stretch) {
	uiDrawTextFontDescriptor descr;
	descr.Family = family;
	descr.Size = size;
	descr.Weight = weight;
	descr.Italic = italic;
	descr.Stretch = stretch;

	uiDrawTextFont * hnd = uiDrawLoadClosestFont(&descr);

	return new DrawTextFont(hnd);
}

NBIND_CLASS(DrawTextFont) {
	method(listFontFamilies);
	method(loadClosestFont);
	method(free);
	method(describe);
	method(getMetrics);
}

#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"



DrawTextFontMetrics::DrawTextFontMetrics(uiDrawTextFontMetrics * metrics) {
	m = metrics;
}

double DrawTextFontMetrics::getAscent() {
	return m->Ascent;
}

double DrawTextFontMetrics::getDescent() {
	return m->Descent;
}

double DrawTextFontMetrics::getLeading() {
	return m->Leading;
}

double DrawTextFontMetrics::getUnderlinePos() {
	return m->UnderlinePos;
}

double DrawTextFontMetrics::getUnderlineThickness() {
	return m->UnderlineThickness;
}


NBIND_CLASS(DrawTextFontMetrics) {
	method(getAscent);
	method(getDescent);
	method(getLeading);
	method(getUnderlinePos);
	method(getUnderlineThickness);
}

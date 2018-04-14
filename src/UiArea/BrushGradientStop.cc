#include "area.h"
#include "ui.h"

BrushGradientStop::BrushGradientStop(double pos, Color color) : c(color) {
	p = pos;
}

Color BrushGradientStop::getColor() {
	return c;
}

void BrushGradientStop::setColor(Color value) {
	c = value;
}

double BrushGradientStop::getPos() {
	return p;
}

void BrushGradientStop::setPos(double value) {
	p = value;
}

void BrushGradientStop::toJS(nbind::cbOutput output) {
	output(p, c);
}

NBIND_CLASS(BrushGradientStop) {
	construct<double, Color>();
	method(getColor);
	method(setColor);
	method(getPos);
	method(setPos);
	method(toJS);
	getset(getColor, setColor);
	getset(getPos, setPos);
}

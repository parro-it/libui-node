#include "../ui.h"
#include "ui-node.h"
#include "nbind/nbind.h"

SizeDouble::SizeDouble(double width, double height) {
	w = width;
	h = height;
}

double SizeDouble::getWidth() {
	return w;
}

void SizeDouble::setWidth(double value) {
	w = value;
}


double SizeDouble::getHeight() {
	return h;
}

void SizeDouble::setHeight(double value) {
	h = value;
}

void SizeDouble::toJS(nbind::cbOutput output) {
	output(w, h);
}

NBIND_CLASS(SizeDouble) {
  construct<double, double>();
  method(getWidth);
  method(setWidth);
  method(getHeight);
  method(setHeight);
  method(toJS);

  getset(getWidth, setWidth);
  getset(getHeight, setHeight);
}

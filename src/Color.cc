#include "values.h"

Color::Color(const Color &other) {
	r = other.r;
	g = other.g;
	b = other.b;
	a = other.a;
}

Color::Color(double red, double green, double blue, double alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

double Color::getR() {
	return r;
}

void Color::setR(double value) {
	r = value;
}

double Color::getG() {
	return g;
}

void Color::setG(double value) {
	g = value;
}

double Color::getB() {
	return b;
}

void Color::setB(double value) {
	b = value;
}

double Color::getA() {
	return a;
}

void Color::setA(double value) {
	a = value;
}

void Color::toJS(nbind::cbOutput output) {
	output(r, g, b, a);
}

NBIND_CLASS(Color) {
	construct<double, double, double, double>();
	method(getR);
	method(setR);
	method(getG);
	method(setG);
	method(getB);
	method(setB);
	method(getA);
	method(setA);

	getset(getR, setR);
	getset(getG, setG);
	getset(getB, setB);
	getset(getA, setA);
}

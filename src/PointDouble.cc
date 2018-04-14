#include "values.h"

PointDouble::PointDouble(const PointDouble &other) {
	x = other.x;
	y = other.y;
}

PointDouble::PointDouble(double xCoord, double yCoord) {
	x = xCoord;
	y = yCoord;
}

double PointDouble::getX() {
	return x;
}

void PointDouble::setX(double value) {
	x = value;
}

double PointDouble::getY() {
	return y;
}

void PointDouble::setY(double value) {
	y = value;
}

void PointDouble::toJS(nbind::cbOutput output) {
	output(x, y);
}

NBIND_CLASS(PointDouble) {
	construct<double, double>();
	method(getX);
	method(setX);
	method(getY);
	method(setY);

	getset(getX, setX);
	getset(getY, setY);
}

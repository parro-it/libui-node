#include "values.h"

Point::Point(const Point &other) {
	x = other.x;
	y = other.y;
}

Point::Point(int xCoord, int yCoord) {
	x = xCoord;
	y = yCoord;
}

int Point::getX() {
	return x;
}

void Point::setX(int value) {
	x = value;
}

int Point::getY() {
	return y;
}

void Point::setY(int value) {
	y = value;
}

void Point::toJS(nbind::cbOutput output) {
	output(x, y);
}

NBIND_CLASS(Point) {
	construct<int, int>();
	method(getX);
	method(setX);
	method(getY);
	method(setY);

	getset(getX, setX);
	getset(getY, setY);
}

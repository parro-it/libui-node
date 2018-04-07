#include "area.h"
#include "ui.h"

UiDrawPath::UiDrawPath(int fillMode) {
	handle = uiDrawNewPath(fillMode);
}

void UiDrawPath::freePath() {
	uiDrawFreePath(handle);
}

void UiDrawPath::newFigure(double x, double y) {
	uiDrawPathNewFigure(handle, x, y);
}

void UiDrawPath::newFigureWithArc(double xCenter, double yCenter, double radius,
								  double startAngle, double sweep,
								  int negative) {
	uiDrawPathNewFigureWithArc(handle, xCenter, yCenter, radius, startAngle,
							   sweep, negative);
}

void UiDrawPath::lineTo(double x, double y) {
	uiDrawPathLineTo(handle, x, y);
}

void UiDrawPath::arcTo(double xCenter, double yCenter, double radius,
					   double startAngle, double sweep, int negative) {
	uiDrawPathArcTo(handle, xCenter, yCenter, radius, startAngle, sweep,
					negative);
}

void UiDrawPath::bezierTo(double c1x, double c1y, double c2x, double c2y,
						  double endX, double endY) {
	uiDrawPathBezierTo(handle, c1x, c1y, c2x, c2y, endX, endY);
}

void UiDrawPath::closeFigure() {
	uiDrawPathCloseFigure(handle);
}

void UiDrawPath::addRectangle(double x, double y, double width, double height) {
	uiDrawPathAddRectangle(handle, x, y, width, height);
}

void UiDrawPath::end() {
	uiDrawPathEnd(handle);
}

uiDrawPath *UiDrawPath::getHandle() {
	return handle;
}

NBIND_CLASS(UiDrawPath) {
	construct<int>();
	method(freePath);
	method(newFigure);
	method(newFigureWithArc);
	method(lineTo);
	method(arcTo);
	method(bezierTo);
	method(closeFigure);
	method(addRectangle);
	method(end);
}

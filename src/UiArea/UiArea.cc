#include "../../ui.h"
#include "../ui-node.h"
#include "nbind/nbind.h"


std::map <uiArea *, UiArea *> areasMap;


INHERITS_CONTROL_METHODS(UiArea)

void UiArea::setSize(int width, int height) {
	uiAreaSetSize(
		(uiArea *) getHandle(),
		width,
		height
	);
}

void UiArea::queueRedrawAll() {
	uiAreaQueueRedrawAll(
		(uiArea *) getHandle()
	);
}

void UiArea::scrollTo(double x, double y, double width, double height) {
	uiAreaScrollTo(
		(uiArea *) getHandle(),
		x,
		y,
		width,
		height
	);
}


UiArea::UiArea(
	nbind::cbFunction &drawCb,
	nbind::cbFunction &mouseEventCb ,
	nbind::cbFunction &mouseCrossedCb,
	nbind::cbFunction &dragBrokenCb,
	nbind::cbFunction &keyEventCb
) : UiControl( (uiControl*) uiNewArea(
	(uiAreaHandler *) UiAreaHandlerFactory::build(
		drawCb,
		mouseEventCb,
		mouseCrossedCb,
		dragBrokenCb,
		keyEventCb
	)
)) {
	areasMap[(uiArea *) getHandle()] = this;
}



UiArea::UiArea(
	nbind::cbFunction &drawCb,
	nbind::cbFunction &mouseEventCb ,
	nbind::cbFunction &mouseCrossedCb,
	nbind::cbFunction &dragBrokenCb,
	nbind::cbFunction &keyEventCb,
	int width,
	int height
) : UiControl( (uiControl*) uiNewScrollingArea(
	(uiAreaHandler *) UiAreaHandlerFactory::build(
		drawCb,
		mouseEventCb,
		mouseCrossedCb,
		dragBrokenCb,
		keyEventCb
	),
	width,
	height
)) {
	areasMap[(uiArea *) getHandle()] = this;
}

// Workaround for nbind bug solved in 0.3
UiArea::UiArea(int dummy) : UiControl(NULL) {}


#include "nbind/api.h"

NBIND_CLASS(UiArea) {
	construct<int>();
	construct<nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &>();
	construct<nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &,nbind::cbFunction &, int, int>();
	DECLARE_CONTROL_METHODS()
	method(setSize);
	method(queueRedrawAll);
	method(scrollTo);
}

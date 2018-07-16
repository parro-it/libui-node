'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

const RESIZE_HANDLE_WIDTH = 8;

const redBrush = new libui.DrawBrush();
redBrush.type = libui.brushType.solid;
redBrush.color = new libui.Color(1, 0, 0, 1);

const greyBrush = new libui.DrawBrush();
greyBrush.type = libui.brushType.solid;
greyBrush.color = new libui.Color(0.6, 0.6, 0.6, 1);

const blueBrush = new libui.DrawBrush();
blueBrush.type = libui.brushType.solid;
blueBrush.color = new libui.Color(0, 0, 1, 1);

const dashedStroke = new libui.DrawStrokeParams();
dashedStroke.thickness = 6;
dashedStroke.dashes = [10, 5];
console.log(dashedStroke.dashes);

const linearBrush = new libui.DrawBrush();
linearBrush.type = libui.brushType.linearGradient;
linearBrush.start = new libui.Point(50, 50);
linearBrush.end = new libui.Point(200, 200);
linearBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(1, 0, 0, 1)), new libui.BrushGradientStop(1, new libui.Color(0, 1, 0, 1))]);

const radialBrush = new libui.DrawBrush();
radialBrush.type = libui.brushType.radialGradient;
radialBrush.start = new libui.Point(300, 330);
radialBrush.end = new libui.Point(300, 330);
radialBrush.outerRadius = 40;
radialBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(0, 0, 1, 1)), new libui.BrushGradientStop(1, new libui.Color(0.5, 0.5, 1, 1))]);
console.log(radialBrush.getStops());

const matrix = new libui.UiDrawMatrix();
matrix.setIdentity();
matrix.rotate(70, 280, (Math.PI / 180) * 45)

const onCloseHandle = (x, y, p) => (3 <= x && x <= 19 && 2 <= y && y <= 18);
const onMoveHandle = (x, y, p) => (0 <= x && x <= p.getAreaWidth() && 0 <= y && y <= 20);
const onResizeBottomHandle = (x, y, p) => ((p.getAreaHeight() - RESIZE_HANDLE_WIDTH) <= y && y <= p.getAreaHeight());
const onResizeRightHandle = (x, y, p) => (p.getAreaWidth() - RESIZE_HANDLE_WIDTH <= x && x <= p.getAreaWidth() && 20 < y);
const onResizeLeftHandle = (x, y, p) => (0 <= x && x <= RESIZE_HANDLE_WIDTH && 20 < y);

function handlerDraw(area, p) {
	let path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(50, 50, 200, 200);
	path.end();
	p.getContext().fill(path, linearBrush);
	path.freePath();

	// ------

	// Circle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigureWithArc(300, 330, 50, 0, 2 * Math.PI, false);
	path.end();
	p.getContext().fill(path, radialBrush);
	path.freePath();

	// Dashed line
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigure(300, 50);
	path.lineTo(350, 250);
	path.end();
	p.getContext().stroke(path, redBrush, dashedStroke);
	path.freePath();

	// Move handle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(0, 0, p.getAreaWidth(), 20);
	path.end();
	p.getContext().fill(path, greyBrush);
	path.freePath();

	// Close button
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(3, 2, 16, 16);
	path.end();
	p.getContext().fill(path, redBrush);
	path.freePath();

	p.getContext().save();
	// Rotated square
	path = new libui.UiDrawPath(libui.fillMode.winding);
	p.getContext().transform(matrix);
	path.addRectangle(90, 240, 100, 100);
	path.end();
	p.getContext().fill(path, redBrush);
	path.freePath();
	p.getContext().restore();

	// Resize handle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	// bottom
	path.addRectangle(0, p.getAreaHeight() - RESIZE_HANDLE_WIDTH, p.getAreaWidth(), RESIZE_HANDLE_WIDTH);
	// right
	path.addRectangle(p.getAreaWidth() - RESIZE_HANDLE_WIDTH, 20, RESIZE_HANDLE_WIDTH, p.getAreaHeight());
	// left
	path.addRectangle(0, 20, RESIZE_HANDLE_WIDTH, p.getAreaHeight());
	path.end();
	p.getContext().fill(path, blueBrush);
	path.freePath();
}

function mouseEvent(area, evt) {
	const x = evt.getX(), y = evt.getY();

	if (evt.getDown() === 1) {
		if (onCloseHandle(x, y, evt)) {
			mainwin.close();
			libui.stopLoop();
		} else if (onMoveHandle(x, y, evt)) {
			area.beginWindowMove();
		} else {
			const left = onResizeLeftHandle(x, y, evt);
			const right = onResizeRightHandle(x, y, evt);
			const bottom = onResizeBottomHandle(x, y, evt);
			if (bottom && right) {
				area.beginWindowResize(libui.resizeEdge.bottomRight);
			} else if (bottom && left) {
				area.beginWindowResize(libui.resizeEdge.bottomLeft);
			} else if (right) {
				area.beginWindowResize(libui.resizeEdge.right);
			} else if (left) {
				area.beginWindowResize(libui.resizeEdge.left);
			} else if (bottom) {
				area.beginWindowResize(libui.resizeEdge.bottom);
			}
		}
	}
}

function noop() {}

let mainwin;

function main() {
	mainwin = new libui.UiWindow('libui textDrawArea Example', 400, 430, 1);
	mainwin.borderless = true;
	mainwin.onClosing(() => {
		mainwin.close();
		libui.stopLoop();
	});

	const textDrawArea = new libui.UiArea(handlerDraw, mouseEvent, noop, noop, noop);
	const wrapper = new libui.UiVerticalBox();
	wrapper.append(textDrawArea, true);
	mainwin.setChild(wrapper);

	mainwin.show();

	libui.startLoop();
}

main();

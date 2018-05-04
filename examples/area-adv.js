'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

const redBrush = new libui.DrawBrush();
redBrush.type = libui.brushType.solid;
redBrush.color = new libui.Color(1, 0, 0, 1);

const blueBrush = new libui.DrawBrush();
blueBrush.type = libui.brushType.solid;
blueBrush.color = new libui.Color(0, 0, 1, 1);

const dashedStroke = new libui.DrawStrokeParams();
dashedStroke.thickness = 6;
dashedStroke.dashes = [10, 5];
console.log(dashedStroke.dashes);

const linearBrush = new libui.DrawBrush();
linearBrush.type = libui.brushType.linearGradient;
linearBrush.start = new libui.Point(0, 0);
linearBrush.end = new libui.Point(200, 200);
linearBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(1, 0, 0, 1)), new libui.BrushGradientStop(1, new libui.Color(0, 1, 0, 1))]);

const radialBrush = new libui.DrawBrush();
radialBrush.type = libui.brushType.radialGradient;
radialBrush.start = new libui.Point(250, 300);
radialBrush.end = new libui.Point(250, 300);
radialBrush.outerRadius = 40;
radialBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(0, 0, 1, 1)), new libui.BrushGradientStop(1, new libui.Color(0.5, 0.5, 1, 1))]);
console.log(radialBrush.getStops());

const matrix = new libui.UiDrawMatrix();
matrix.setIdentity();
matrix.rotate(70, 280, (Math.PI / 180) * 45)

const onMoveHandle = (x, y) => (330 <= x && x <= 350 && 0 <= y && y <= 20);
const onResizeHandle = (x, y, p) => (0 <= x && x <= p.getAreaWidth() && (p.getAreaHeight() - 20) <= y && y <= p.getAreaHeight());

function handlerDraw(area, p) {
	let path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(0, 0, 200, 200);
	path.end();
	p.getContext().fill(path, linearBrush);
	path.freePath();

	// ------

	// Circle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigure(0, 0);
	path.arcTo(250, 300, 50, 0, 2 * Math.PI, false);
	path.end();
	p.getContext().fill(path, radialBrush);
	path.freePath();

	// Dashed line
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigure(250, 20);
	path.lineTo(300, 150);
	path.end();
	p.getContext().stroke(path, redBrush, dashedStroke);
	path.freePath();

	// Move handle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(330, 0, 20, 20);
	path.end();
	p.getContext().fill(path, redBrush);
	path.freePath();

	p.getContext().save();
	// Rotated square
	path = new libui.UiDrawPath(libui.fillMode.winding);
	p.getContext().transform(matrix);
	path.addRectangle(20, 230, 100, 100);
	path.end();
	p.getContext().fill(path, redBrush);
	path.freePath();
	p.getContext().restore();

	// Resize handle
	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(0, p.getAreaHeight() - 20, p.getAreaWidth(), 20);
	path.end();
	p.getContext().fill(path, blueBrush);
	path.freePath();
}

function mouseEvent(area, evt) {
	const x = evt.getX(), y = evt.getY();

	if(evt.getDown() === 1) {
		if (onMoveHandle(x, y)) {
			area.beginWindowMove();
		}

		if (onResizeHandle(x, y, evt)) {
			area.beginWindowResize(libui.resizeEdge.bottom);
		}
	}
}

function noop() {}

function main() {
	const mainwin = new libui.UiWindow('libui textDrawArea Example', 400, 430, 1);
	mainwin.margined = true;
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

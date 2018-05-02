'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

const solidBrush = new libui.DrawBrush();
solidBrush.type = libui.brushType.solid;
solidBrush.color = new libui.Color(1, 0, 0, 1);

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

function handlerDraw(area, p) {
	let path = new libui.UiDrawPath(libui.fillMode.winding);
	path.addRectangle(0, 0, 200, 200);
	path.end();
	p.getContext().fill(path, linearBrush);
	path.freePath();

	// ------

	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigure(0, 0);
	path.arcTo(250, 300, 50, 0, 2 * Math.PI, false);
	path.end();
	p.getContext().fill(path, radialBrush);
	path.freePath();

	path = new libui.UiDrawPath(libui.fillMode.winding);
	path.newFigure(250, 20);
	path.lineTo(300, 150);
	path.end();
	p.getContext().stroke(path, solidBrush, dashedStroke);
	path.freePath();

	path = new libui.UiDrawPath(libui.fillMode.winding);
	p.getContext().transform(matrix);
	path.addRectangle(20, 230, 100, 100);
	path.end();
	p.getContext().fill(path, solidBrush);
	path.freePath();
}

function noop() {}

function main() {
	const mainwin = new libui.UiWindow('libui textDrawArea Example', 400, 400, 1);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		mainwin.close();
		libui.stopLoop();
	});

	const textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	const wrapper = new libui.UiVerticalBox();
	wrapper.append(textDrawArea, true);
	mainwin.setChild(wrapper);

	mainwin.show();

	libui.startLoop();
}

main();

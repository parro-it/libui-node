'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

function handlerDraw(area, p) {
	const brush = new libui.DrawBrush();
	brush.type = libui.brushType.linearGradient;
	brush.start = new libui.Point(0, 0);
	brush.end = new libui.Point(200, 200);

	brush.setStops([new libui.BrushGradientStop(0, new libui.Color(1, 0, 0, 1)), new libui.BrushGradientStop(1, new libui.Color(0, 1, 0, 1))]);

	let path = new libui.UiDrawPath(0);
	path.addRectangle(0, 0, 200, 200);
	path.end();
	p.getContext().fill(path, brush);
	path.freePath();

	// ------

	brush.type = libui.brushType.radialGradient;
	brush.start = new libui.Point(200, 300);
	brush.end = new libui.Point(200, 300);
	brush.outerRadius = 40;

	brush.setStops([new libui.BrushGradientStop(0, new libui.Color(0, 0, 1, 1)), new libui.BrushGradientStop(1, new libui.Color(0.5, 0.5, 1, 1))]);
	// console.log(brush.getStops())

	path = new libui.UiDrawPath(0);
	path.arcTo(200, 300, 50, 0, 2 * Math.PI, false);
	path.end();
	p.getContext().fill(path, brush);
	path.freePath();
}

function noop() {}

function main() {
	const mainwin = new libui.UiWindow('libui textDrawArea Example', 400, 400, 1);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		libui.stopLoop();
	});

	const textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	mainwin.setChild(textDrawArea);

	mainwin.show();

	libui.startLoop();
}

main();

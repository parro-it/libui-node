'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

const linearBrush = new libui.DrawBrush();
linearBrush.type = libui.brushType.linearGradient;
linearBrush.start = new libui.Point(0, 0);
linearBrush.end = new libui.Point(200, 200);
linearBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(1, 0, 0, 1)), new libui.BrushGradientStop(1, new libui.Color(0, 1, 0, 1))]);


const radialBrush = new libui.DrawBrush();
radialBrush.type = libui.brushType.radialGradient;
radialBrush.start = new libui.Point(200, 300);
radialBrush.end = new libui.Point(200, 300);
radialBrush.outerRadius = 40;

radialBrush.setStops([new libui.BrushGradientStop(0, new libui.Color(0, 0, 1, 1)), new libui.BrushGradientStop(1, new libui.Color(0.5, 0.5, 1, 1))]);
console.log(radialBrush.getStops())

function handlerDraw(area, p) {

	let path = new libui.UiDrawPath(0);
	path.addRectangle(0, 0, 200, 200);
	path.end();
	p.getContext().fill(path, linearBrush);
	path.freePath();

	// ------

	path = new libui.UiDrawPath(0);
	path.arcTo(200, 300, 50, 0, 2 * Math.PI, false);
	path.end();
	p.getContext().fill(path, radialBrush);
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

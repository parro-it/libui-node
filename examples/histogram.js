'use strict';
/* eslint-disable unicorn/number-literal-case */

const libui = require('..');

let mainwin = null;
let histogram = null;
const colorWhite = 0xffffff;
const colorBlack = 0x000000;
const colorDodgerBlue = 0x1e90ff;

const datapoints = [];
let currentPoint = -1;

// Some metrics
const xoffLeft = 20;
const yoffTop = 20;
const xoffRight = 20;
const yoffBottom = 20;
const pointRadius = 5;
const uiDrawFillModeWinding = 0;

function graphSize(clientWidth, clientHeight) {
	return {
		width: clientWidth - xoffLeft - xoffRight,
		height: clientHeight - yoffTop - yoffBottom
	};
}

function pointLocations(width, height, xs, ys) {
	let i;
	let n;

	const xincr = width / 9; // 10 - 1 to make the last point be at the end
	const yincr = height / 100;

	for (i = 0; i < 10; i++) {
		// Get the value of the point
		n = datapoints[i].value;
		// Because y=0 is the top but n=0 is the bottom, we need to flip
		n = 100 - n;
		xs[i] = xincr * i;
		ys[i] = yincr * n;
	}
}

function constructGraph(width, height, extend) {
	const xs = [];
	const ys = [];

	pointLocations(width, height, xs, ys);

	const path = new libui.UiDrawPath(uiDrawFillModeWinding);

	path.newFigure(xs[0], ys[0]);
	for (let i = 1; i < 10; i++) {
		path.lineTo(xs[i], ys[i]);
	}

	if (extend) {
		path.lineTo(width, height);
		path.lineTo(0, height);
		path.closeFigure();
	}

	path.end();
	return path;
}

const handler = {
	Draw(area, p) {
		let path;
		let brush = buildSolidBrush(colorWhite, 1.0);
		const graphA = 0.9;

		path = new libui.UiDrawPath(uiDrawFillModeWinding);
		path.addRectangle(0, 0, p.getAreaWidth(), p.getAreaHeight());
		path.end();
		p.getContext().fill(path, brush);
		path.freePath();

		// Figure out dimensions
		const graph = graphSize(p.getAreaWidth(), p.getAreaHeight());

		// Clear sp to avoid passing garbage to uiDrawStroke()
		// For example, we don't use dashing
		const sp = new libui.DrawStrokeParams();

		// Make a stroke for both the axes and the histogram line
		sp.cap = 0;
		sp.join = 0;
		sp.thickness = 2;
		sp.miterLimit = 10.0;

		// Draw the axes
		brush = buildSolidBrush(colorBlack, 1.0);

		path = new libui.UiDrawPath(uiDrawFillModeWinding);
		path.newFigure(xoffLeft, yoffTop);
		path.lineTo(xoffLeft, yoffTop + graph.height);
		path.lineTo(xoffLeft + graph.width, yoffTop + graph.height);
		path.end();
		p.getContext().stroke(path, brush, sp);
		path.freePath();

		// Now transform the coordinate space so (0, 0) is the top-left corner of the graph
		const m = new libui.UiDrawMatrix();
		m.setIdentity();
		m.translate(xoffLeft, yoffTop);
		p.getContext().transform(m);

		brush = buildSolidBrush(colorDodgerBlue, 1.0);

		// Now create the fill for the graph below the graph line
		path = constructGraph(graph.width, graph.height, 1);
		brush.color.a = graphA / 2;
		p.getContext().fill(path, brush);
		path.freePath();

		// Now draw the histogram line
		path = constructGraph(graph.width, graph.height, 0);
		brush.color.a = graphA;
		p.getContext().stroke(path, brush, sp);
		path.freePath();

		// Now draw the point being hovered over
		if (currentPoint !== -1) {
			const xs = [];
			const ys = [];

			pointLocations(graph.width, graph.height, xs, ys);
			path = new libui.UiDrawPath(uiDrawFillModeWinding);
			path.newFigureWithArc(
				xs[currentPoint],
				ys[currentPoint],
				pointRadius,
				0,
				6.23,
				0);
			path.end();
			// Use the same brush as for the histogram lines
			p.getContext().fill(path, brush);
			path.freePath();
		}
	},

	MouseEvent(area, e) {
		const xs = [];
		const ys = [];
		let i;

		const graph = graphSize(e.getAreaWidth(), e.getAreaHeight());
		pointLocations(graph.width, graph.height, xs, ys);

		for (i = 0; i < 10; i++) {
			if (inPoint(e.getX(), e.getY(), xs[i], ys[i])) {
				break;
			}
		}

		if (i === 10) {
			// Not in a point
			i = -1;
		}

		currentPoint = i;

		redraw();
	},

	MouseCrossed() {},
	DragBroken() {},
	KeyEvent() {}
};

// Helper to quickly set a brush color
function buildSolidBrush(color, alpha) {
	let component;

	component = (color >> 16) & 0xff;
	const R = component / 255;
	component = (color >> 8) & 0xff;
	const G = component / 255;
	component = color & 0xff;
	const B = component / 255;
	const A = alpha;

	const brush = new libui.DrawBrush();
	brush.color = new libui.Color(R, G, B, A);
	brush.type = libui.brushType.solid;

	return brush;
}

function inPoint(x, y, xtest, ytest) {
	// TO-DO switch to using a matrix
	x -= xoffLeft;
	y -= yoffTop;
	return (
		x >= xtest - pointRadius &&
		x <= xtest + pointRadius &&
		y >= ytest - pointRadius &&
		y <= ytest + pointRadius);
}

function redraw() {
	histogram.queueRedrawAll();
}

function main() {
	mainwin = new libui.UiWindow('libui Histogram Example', 640, 480, 1);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		libui.stopLoop();
	});

	const hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	const vbox = new libui.UiVerticalBox();
	vbox.padded = true;
	hbox.append(vbox, 0);

	for (let i = 0; i < 10; i++) {
		datapoints[i] = new libui.UiSpinbox(0, 100);
		datapoints[i].value = Math.round(Math.random() * 100);
		datapoints[i].onChanged(redraw);
		vbox.append(datapoints[i], 0);
	}

	histogram = new libui.UiArea(
		handler.Draw,
		handler.MouseEvent,
		handler.MouseCrossed,
		handler.DragBroken,
		handler.KeyEvent);
	hbox.append(histogram, 1);

	mainwin.show();

	libui.startLoop();
}

main();

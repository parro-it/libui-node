'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

let mainwin;
let textDrawArea;
let fontSize;
let textString;
const colorWhite = 0xff00ff;

function buildSolidBrush(color, alpha) {
	let component;

	component = (color >> 16) & 0xff;
	const R = component / 255;
	component = (color >> 8) & 0xff;
	const G = component / 255;
	component = color & 0xff;
	const B = component / 255;
	const A = alpha;

	const uiDrawBrushTypeSolid = 0;
	const brush = new libui.DrawBrush();
	brush.color = new libui.Color(R, G, B, A);
	brush.type = uiDrawBrushTypeSolid;

	return brush;
}

function handlerDraw(area, p) {
	const brush = buildSolidBrush(colorWhite, 1.0);

	const path = new libui.UiDrawPath(0);
	path.addRectangle(0, 0, p.getAreaWidth(), p.getAreaHeight());
	path.end();
	p.getContext().fill(path, brush);
	path.freePath();

	const font = new libui.DrawTextFont();

	font.loadClosestFont(
		'Monospace',
		fontSize.value,
		libui.textWeight.ultraLight,
		libui.textItalic.oblique,
		libui.textStretch.normal);

	const layout = new libui.DrawTextLayout(textString.text, font, 40);

	layout.setColor(0, textString.text.length, new libui.Color(1, 0, 0, 1));

	p.getContext().text(0, 0, layout);

	layout.free();
	font.free();
}

function noop() {}

function redraw() {
	textDrawArea.queueRedrawAll();
}

function main() {
	mainwin = new libui.UiWindow('libui textDrawArea Example', 640, 480, 1);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		libui.stopLoop();
	});

	const hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	const vbox = new libui.UiVerticalBox();
	vbox.padded = true;
	hbox.append(vbox, true);

	fontSize = new libui.UiSpinbox();
	fontSize.value = 24;
	fontSize.onChanged(redraw);

	textString = new libui.UiEntry();
	textString.text = 'Sample';
	textString.onChanged(redraw);

	vbox.append(textString, false);
	vbox.append(fontSize, false);
	textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	hbox.append(textDrawArea, true);

	mainwin.show();

	libui.startLoop();
}

main();

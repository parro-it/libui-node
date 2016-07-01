var libui = require('../index.js');

var mainwin;
var textDrawArea;
var fontSize;
var textString;
var colorWhite = 0xFF00FF;

function buildSolidBrush(color, alpha) {
	var component;

	component = (color >> 16) & 0xFF;
	var R = component / 255;
	component = (color >> 8) & 0xFF;
	var G = component / 255;
	component = color & 0xFF;
	var B = component / 255;
	var A = alpha;

	var uiDrawBrushTypeSolid = 0;
	var brush = new libui.DrawBrush();
	brush.color =	new libui.Color(R, G, B, A);
	brush.type = uiDrawBrushTypeSolid;

	return brush;
}

function handlerDraw(area, p) {
	var brush = buildSolidBrush(colorWhite, 1.0);

	var path = new libui.UiDrawPath(0);
	path.addRectangle(0, 0, p.getAreaWidth(), p.getAreaHeight());
	path.end();
	p.getContext().fill(path, brush);
	path.freePath();

	var font = new libui.DrawTextFont();

	font.loadClosestFont(
		'Monospace',
		fontSize.value,
		libui.textWeight.ultraLight,
		libui.textItalic.oblique,
		libui.textStretch.normal
	);

	var layout = new libui.DrawTextLayout(textString.text, font, 40);

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
	libui.Ui.init();

	var hbox;
	var vbox;

	mainwin = new libui.UiWindow("libui textDrawArea Example", 640, 480, 1);
	mainwin.margined = true;
	mainwin.onClosing(function () {
		libui.stopLoop();
	});

	hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	vbox = new libui.UiVerticalBox();
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
	textDrawArea = new libui.UiArea(
		handlerDraw,
		noop,
		noop,
		noop,
		noop
	);
	hbox.append(textDrawArea, true);

	mainwin.show();

	libui.startLoop();
}

main();

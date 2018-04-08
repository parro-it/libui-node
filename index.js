const nbind = require('nbind');

const binding = nbind.init(__dirname);

module.exports = binding.lib;

binding.lib.Ui.init();

function stopLoop() {
	binding.lib.EventLoop.stop();
}

function startLoop() {
	binding.lib.EventLoop.start();
}

function Color(r, g, b, a) {
	this.r = r;
	this.g = g;
	this.b = b;
	this.a = a;
}

function fromJSColor(output) {
	output(this.r, this.g, this.b, this.a);
}
Color.prototype.fromJS = fromJSColor;

binding.bind('Color', Color);

function Point(x, y) {
	this.x = x;
	this.y = y;
}

function fromJSPoint(output) {
	output(this.x, this.y);
}
Point.prototype.fromJS = fromJSPoint;

binding.bind('Point', Point);

function PointDouble(x, y) {
	this.x = x;
	this.y = y;
}

function fromJSPointDouble(output) {
	output(this.x, this.y);
}

PointDouble.prototype.fromJS = fromJSPointDouble;

binding.bind('PointDouble', PointDouble);

function Size(w, h) {
	this.w = w;
	this.h = h;
}

function fromJSSize(output) {
	output(this.w, this.h);
}
Size.prototype.fromJS = fromJSSize;

binding.bind('Size', Size);

function SizeDouble(w, h) {
	this.w = w;
	this.h = h;
}

function fromJSSizeDouble(output) {
	output(this.w, this.h);
}
SizeDouble.prototype.fromJS = fromJSSizeDouble;

binding.bind('SizeDouble', SizeDouble);

function BrushGradientStop(pos, color) {
	this.pos = pos;
	this.color = color;
}

function fromJSBrushGradientStop(output) {
	output(this.pos, this.color);
}
BrushGradientStop.prototype.fromJS = fromJSBrushGradientStop;

binding.bind('BrushGradientStop', BrushGradientStop);

const textWeight = {
	thin: 0,
	ultraLight: 1,
	light: 2,
	book: 3,
	normal: 4,
	medium: 5,
	semiBold: 6,
	bold: 7,
	utraBold: 8,
	heavy: 9,
	ultraHeavy: 10
};

const textItalic = {
	normal: 0,
	oblique: 1,
	italic: 2
};

const textStretch = {
	ultraCondensed: 0,
	extraCondensed: 1,
	condensed: 2,
	semiCondensed: 3,
	normal: 4,
	semiExpanded: 5,
	expanded: 6,
	extraExpanded: 7,
	ultraExpanded: 8
};

const brushType = {
	solid: 0,
	linearGradient: 1,
	radialGradient: 2
	// IMPL uiDrawBrushTypeImage: 3
};

const lineCap = {
	flat: 0,
	round: 1,
	square: 2
};

const lineJoin = {
	miter: 0,
	round: 1,
	bevel: 2
};

const fillMode = {
	winding: 0,
	alternate: 1
};

module.exports.textStretch = textStretch;
module.exports.textItalic = textItalic;
module.exports.textWeight = textWeight;
module.exports.Size = Size;
module.exports.Point = Point;
module.exports.Color = Color;
module.exports.BrushGradientStop = BrushGradientStop;
module.exports.brushType = brushType;
module.exports.lineCap = lineCap;
module.exports.lineJoin = lineJoin;
module.exports.fillMode = fillMode;
module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

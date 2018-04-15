const nbind = require('nbind');

const binding = nbind.init(__dirname);

module.exports = binding.lib;

binding.lib.Ui.init();

var setTimeoutNode;
var clearTimeoutNode;
var setIntervalNode;
var clearIntervalNode;

function stopLoop() {
	binding.lib.EventLoop.stop();

	if (!setTimeoutNode) {
		return;
	}

	global.setTimeout = setTimeoutNode;
	global.clearTimeout = clearTimeoutNode;
	global.setInterval = setIntervalNode;
	global.clearInterval = clearIntervalNode;

	setTimeoutNode = null;
	clearTimeoutNode = null;
	setIntervalNode = null;
	clearIntervalNode = null;
}

function startLoop() {
	binding.lib.EventLoop.start();

	if (setTimeoutNode) {
		return;
	}

	setTimeoutNode = global.setTimeout;
	global.setTimeout = function(cb, t) {
		const args = Array.prototype.slice.call(arguments, 2);
		return binding.lib.setTimeout(function() {
			cb.apply(null, args);
		}, t);
	};

	clearTimeoutNode = global.clearTimeout;
	global.clearTimeout = binding.lib.clearTimeout;

	setIntervalNode = global.setInterval;
	global.setInterval = function(cb, t) {
		const args = Array.prototype.slice.call(arguments, 2);
		return binding.lib.setInterval(function() {
			cb.apply(null, args);
		}, t);
	};

	clearIntervalNode = global.clearInterval;
	global.clearInterval = binding.lib.clearInterval;
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

const modifierKeys = {
	ctrl: 1 << 0,
	alt: 1 << 1,
	shift: 1 << 2,
	super: 1 << 3
};

const extKeys = {
	escape: 1,
	insert: 2, // equivalent to "Help" on Apple keyboards
	delete: 3,
	home: 4,
	end: 5,
	pageUp: 6,
	pageDown: 7,
	up: 8,
	down: 9,
	left: 10,
	right: 11,
	f1: 12, // F1..F12 are guaranteed to be consecutive
	f2: 13,
	f3: 14,
	f4: 15,
	f5: 16,
	f6: 17,
	f7: 18,
	f8: 19,
	f9: 20,
	f10: 21,
	f11: 22,
	f12: 23,
	n0: 24, // numpad keys; independent of Num Lock state
	n1: 25, // N0..N9 are guaranteed to be consecutive
	n2: 26,
	n3: 27,
	n4: 28,
	n5: 29,
	n6: 30,
	n7: 31,
	n8: 32,
	n9: 33,
	nDot: 34,
	nEnter: 35,
	nAdd: 36,
	nSubtract: 37,
	nMultiply: 38,
	nDivide: 39
};

module.exports.textStretch = textStretch;
module.exports.textItalic = textItalic;
module.exports.textWeight = textWeight;
module.exports.Size = Size;
module.exports.Point = Point;
module.exports.Color = Color;
module.exports.PointDouble = PointDouble;
module.exports.SizeDouble = SizeDouble;
module.exports.BrushGradientStop = BrushGradientStop;
module.exports.brushType = brushType;
module.exports.lineCap = lineCap;
module.exports.lineJoin = lineJoin;
module.exports.fillMode = fillMode;
module.exports.modifierKeys = modifierKeys;
module.exports.extKeys = extKeys;
module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;
module.exports.onShouldQuit = binding.lib.Ui.onShouldQuit;

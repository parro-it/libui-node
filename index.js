const nbind = require('nbind');
const async_hooks = require('async_hooks');

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

	// Create a new AsyncHook instance. All of these callbacks are optional.
	const asyncHook =
		async_hooks.createHook({init /*, before, after, destroy, promiseResolve*/});

	// Allow callbacks of this AsyncHook instance to call. This is not an implicit
	// action after running the constructor, and must be explicitly run to begin
	// executing callbacks.
	asyncHook.enable();

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

// init is called during object construction. The resource may not have
// completed construction when this callback runs, therefore all fields of the
// resource referenced by "asyncId" may not have been populated.
function init(asyncId, type, triggerAsyncId, resource) {
	// console.log('init', asyncId);
	binding.lib.EventLoop.wakeupBackgroundThread();
}
/*
// before is called just before the resource's callback is called. It can be
// called 0-N times for handles (e.g. TCPWrap), and will be called exactly 1
// time for requests (e.g. FSReqWrap).
function before(asyncId) {
	console.log('before', asyncId);
}

// after is called just after the resource's callback has finished.
function after(asyncId) {
	console.log('after', asyncId);
}

// destroy is called when an AsyncWrap instance is destroyed.
function destroy(asyncId) {
	console.log('destroy', asyncId);
}

// promiseResolve is called only for promise resources, when the
// `resolve` function passed to the `Promise` constructor is invoked
// (either directly or through other means of resolving a promise).
function promiseResolve(asyncId) {
	console.log('promiseResolve', asyncId);
}
*/

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
	minimum: 0,
	thin: 100,
	ultraLight: 200,
	light: 300,
	book: 350,
	normal: 400,
	medium: 500,
	semiBold: 600,
	bold: 700,
	ultraBold: 800,
	heavy: 900,
	ultraHeavy: 950,
	maximum: 1000
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

const textAttributeType = {
	family: 0,
	size: 1,
	weight: 2,
	italic: 3,
	stretch: 4,
	color: 5,
	background: 6,
	underline: 7,
	underlineColor: 8,
	features: 9
};

const textUnderline = {
	none: 0,
	single: 1,
	double: 2,
	suggestion: 3
};

const textUnderlineColor = {
	custom: 0,
	spelling: 1,
	grammar: 2,
	auxiliary: 3
};

const textAlign = {
	left: 0,
	center: 1,
	right: 2
};

const forEach = {
	continue: 0,
	stop: 1
};

binding.lib.AttributedString.prototype.appendAttributed = function(str) {
	return this.appendAttributedInternal(str, Array.prototype.slice.call(arguments, 1));
};

binding.lib.AttributedString.prototype.insertAttributed = function(str, start) {
	return this.insertAttributedInternal(str, start, Array.prototype.slice.call(arguments, 2));
};

binding.lib.FontAttribute.newUnderlineColor = function(type, color) {
	if (type === textUnderlineColor.custom && !color) {
		console.error('With textUnderlineColor.custom, a color needs to passed');
	}
	color = color || new Color(0, 0, 0, 0);
	return binding.lib.FontAttribute.newUnderlineColor2(type, color);
};

binding.lib.OpenTypeFeatures.prototype.get = function(str) {
	const value = this.getInternal(str);
	if (value[1]) {
		return value[0];
	}
	return null;
};

binding.lib.FontAttribute.prototype.getFamily = function() {
	if (this.getAttributeType() !== textAttributeType.family) {
		return null;
	}
	return this.getFamilyInternal();
};

binding.lib.FontAttribute.prototype.getSize = function() {
	if (this.getAttributeType() !== textAttributeType.size) {
		return null;
	}
	return this.getSizeInternal();
};

binding.lib.FontAttribute.prototype.getWeight = function() {
	if (this.getAttributeType() !== textAttributeType.weight) {
		return null;
	}
	return this.getWeightInternal();
};

binding.lib.FontAttribute.prototype.getItalic = function() {
	if (this.getAttributeType() !== textAttributeType.italic) {
		return null;
	}
	return this.getItalicInternal();
};

binding.lib.FontAttribute.prototype.getStretch = function() {
	if (this.getAttributeType() !== textAttributeType.stretch) {
		return null;
	}
	return this.getStretchInternal();
};

binding.lib.FontAttribute.prototype.getColor = function() {
	if (this.getAttributeType() !== textAttributeType.color) {
		return null;
	}
	return this.getColorInternal();
};

binding.lib.FontAttribute.prototype.getUnderline = function() {
	if (this.getAttributeType() !== textAttributeType.underline) {
		return null;
	}
	return this.getUnderlineInternal();
};

binding.lib.FontAttribute.prototype.getUnderlineColor = function() {
	if (this.getAttributeType() !== textAttributeType.underlineColor) {
		return null;
	}
	const v = this.getUnderlineColorInternal();
	const type = Math.round(v[1].r);
	return {type, color: type === textUnderlineColor.custom ? v[0] : null};
};

binding.lib.FontAttribute.prototype.getOTFeatures = function() {
	if (this.getAttributeType() !== textAttributeType.features) {
		return null;
	}
	return this.getOTFeaturesInternal();
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
module.exports.textItalic = textItalic;
module.exports.textStretch = textStretch;
module.exports.textAttributeType = textAttributeType;
module.exports.textUnderline = textUnderline;
module.exports.textUnderlineColor = textUnderlineColor;
module.exports.textAlign = textAlign;
module.exports.forEach = forEach;
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

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
	Family: 0,
	Size: 1,
	Weight: 2,
	Italic: 3,
	Stretch: 4,
	Color: 5,
	Background: 6,
	Underline: 7,
	UnderlineColor: 8,
	Features: 9
};


const textUnderline = {
	None: 0,
	Single: 1,
	Double: 2,
	Suggestion: 3
};

const textUnderlineColor = {
	Custom: 0,
	Spelling: 1,
	Grammar: 2,
	Auxiliary: 3
};

const textAlign = {
	Left: 0,
	Center: 1,
	Right: 2
};


module.exports.textWeight = textWeight;
module.exports.textItalic = textItalic;
module.exports.textStretch = textStretch;
module.exports.textAttributeType = textAttributeType;
module.exports.textUnderline = textUnderline;
module.exports.textUnderlineColor = textUnderlineColor;
module.exports.textAlign = textAlign;
module.exports.Size = Size;
module.exports.Point = Point;
module.exports.Color = Color;
module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

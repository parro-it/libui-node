var nbind = require('nbind');
var binding = nbind.init(__dirname);
var Ui = binding.lib.Ui;

var loopRunning = false;

module.exports = binding.lib;

function stopLoop() {
	if (!loopRunning) {
		return;
	}
	clearInterval(frequencyCheck);
	boost();
	Ui.quit();
	console.log('quit done')
}

var boosted = false;
function boost() {
	boosted = true;
	console.log('boost')
}

var frequencyCheck = null;

function startLoop(cb) {
	var counter = 0;

	function step() {
		counter++;
		if (Ui.mainStep(false)) {
			if (boosted) {
				setImmediate(step);
				boosted = false;
			} else {
				setTimeout(step);
			}
		} else if (cb) {
			console.log('exit')
			cb();
		}
	}

	if (loopRunning) {
		return;
	}

	frequencyCheck = setInterval(function () {
		console.log(counter + "Hz");
		counter = 0;
	}, 1000);

	loopRunning = true;
	Ui.mainSteps();
	step();
}

function Color(r, g, b, a) {
	this.r = r;
	this.g = g;
	this.b = b;
	this.a = a;
}

Color.prototype.fromJS = function fromJS(output) {
	output(this.r, this.g, this.b, this.a);
};

binding.bind('Color', Color);

function Point(x, y) {
	this.x = x;
	this.y = y;
}

Point.prototype.fromJS = function fromJS(output) {
	output(this.x, this.y);
};

binding.bind('Point', Point);

function PointDouble(x, y) {
	this.x = x;
	this.y = y;
}

PointDouble.prototype.fromJS = function fromJS(output) {
	output(this.x, this.y);
};

binding.bind('PointDouble', PointDouble);

function Size(w, h) {
	this.w = w;
	this.h = h;
}

Size.prototype.fromJS = function fromJS(output) {
	output(this.w, this.h);
};

binding.bind('Size', Size);

function SizeDouble(w, h) {
	this.w = w;
	this.h = h;
}

SizeDouble.prototype.fromJS = function fromJS(output) {
	output(this.w, this.h);
};

binding.bind('SizeDouble', SizeDouble);

var textWeight = {
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

var textItalic = {
	normal: 0,
	oblique: 1,
	italic: 2
};

var textStretch = {
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

module.exports.boost = boost;
module.exports.textStretch = textStretch;
module.exports.textItalic = textItalic;
module.exports.textWeight = textWeight;
module.exports.Size = Size;
module.exports.Point = Point;
module.exports.Color = Color;
module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

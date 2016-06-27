var nbind = require('nbind');
var binding = nbind.init(__dirname);
var Ui = binding.lib.Ui;

var loopRunning = false;

module.exports = binding.lib;

function stopLoop() {
	if (!loopRunning) {
		return;
	}
	loopRunning = false;
	Ui.quit();
}

function startLoop(cb) {
	function step() {
		Ui.mainStep(false);
		if (loopRunning) {
			setImmediate(step);
		} else if (cb) {
			cb();
		}
	}

	if (loopRunning) {
		return;
	}

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

function Size(w, h) {
	this.w = w;
	this.h = h;
}

Size.prototype.fromJS = function fromJS(output) {
	output(this.w, this.h);
};

binding.bind('Size', Size);

function UiAreaMouseEvent(e) {
	this.e = e;
}

UiAreaMouseEvent.prototype.fromJS = function fromJS(output) {
	output(this.e);
};

binding.bind('UiAreaMouseEvent', UiAreaMouseEvent);

module.exports.Size = Size;
module.exports.Point = Point;
module.exports.Color = Color;
module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

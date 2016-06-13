var os = require('os');
var nbind = require('nbind');
var binding = nbind.init(__dirname);
var Ui = binding.lib.Ui;

var loopRunning = false;

module.exports = binding.lib;

function stopLoop() {
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

	loopRunning = true;
	if (os.platform() === 'darwin') {
		return Ui.main();
	}

	step();
}

module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

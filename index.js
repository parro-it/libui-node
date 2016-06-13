var os = require('os');
const nbind = require('nbind');
const binding = nbind.init(__dirname);
const Ui = binding.lib.Ui;

let loopRunning = false;
module.exports = binding.lib;

function stopLoop() {
	loopRunning = false;
	Ui.quit();
}

function startLoop() {
	loopRunning = true;
	if (os.platform() === 'darwin') {
		return Ui.main();
	}
	return new Promise(resolve => {
		function step() {
			Ui.mainStep(false);
			if (loopRunning) {
				setImmediate(step);
			} else {
				resolve();
			}
		}
		step();
	});
}

module.exports.startLoop = startLoop;
module.exports.stopLoop = stopLoop;

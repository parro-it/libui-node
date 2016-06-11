const nbind = require('nbind');
const binding = nbind.init(__dirname);

module.exports = binding.lib;

function step() {
	binding.lib.Ui.mainStep(false);
	setImmediate(step);
}

module.exports.start = step;

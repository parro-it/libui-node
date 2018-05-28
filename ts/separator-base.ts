const {UiControl} = require('./ui-control');

/**
 * Base class for vertical and horizontal separator
 * @extends UiControl
 */
class SeparatorBase extends UiControl {
	constructor(handle) {
		super(handle);
	}
}

module.exports = {SeparatorBase};

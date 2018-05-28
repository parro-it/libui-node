const {Separator} = require('..');
const {SeparatorBase} = require('./separator-base');

/**
 * A vertical line to visually separate controls.
 * @extends SeparatorBase
 */
class UiVerticalSeparator extends SeparatorBase {
	/**
	 * Create a new UiVerticalSeparator object.
	 * @return {UiVerticalSeparator}
	 */
	constructor() {
		super(Separator.createVertical());
	}
}

module.exports = {UiVerticalSeparator};

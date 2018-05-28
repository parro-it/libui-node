const {Separator} = require('..');
const {SeparatorBase} = require('./separator-base');

/**
 * A horizontal line to visually separate controls.
 * @extends SeparatorBase
 */
class UiHorizontalSeparator extends SeparatorBase {
	/**
	 * Create a new UiHorizontalSeparator object.
	 * @return {UiHorizontalSeparator}
	 */
	constructor() {
		super(Separator.createHorizontal());
	}
}

module.exports = {UiHorizontalSeparator};

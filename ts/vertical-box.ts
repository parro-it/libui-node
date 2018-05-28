const {Box} = require('..');
const {UiBox} = require('./box');

/**
 * A container that stacks its children vertically.
 * @extends UiBox
 */
class UiVerticalBox extends UiBox {
	/**
	 * Create a new UiVerticalBox object.
	 * @return {UiVerticalBox}
	 */
	constructor() {
		super(Box.createVertical());
	}
}

module.exports = {UiVerticalBox};

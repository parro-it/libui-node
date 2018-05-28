const {Box} = require('..');
const {UiBox} = require('./box');
/**
 * A container that stacks its chidren horizontally.
 * @extends UiBox
 */
class UiHorizontalBox extends UiBox {
	/**
	 * Create a new UiHorizontalBox object.
	 * @return {UiHorizontalBox}
	 */
	constructor() {
		super(Box.createHorizontal());
	}
}

module.exports = {UiHorizontalBox};

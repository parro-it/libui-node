const {Entries} = require('..');
const {UiEntryBase} = require('./entry-base');

/**
 * A single line text entry control that hides the input, useful for passwords
 * and other sensible data.
 * @extends UiEntryBase
 */
class UiPasswordEntry extends UiEntryBase {
	/**
	 * Create a new UiPasswordEntry object.
	 * @return {UiPasswordEntry}
	 */
	constructor() {
		super(Entries.createPassword());
	}
}

module.exports = {UiPasswordEntry};

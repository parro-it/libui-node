const {Entries} = require('..');
const {UiEntryBase} = require('./entry-base');

/**
 * A simple, single line text entry control.
 * @extends UiEntryBase
 */
class UiEntry extends UiEntryBase {
	/**
	 * Create a new UiEntry object.
	 * @return {UiEntry}
	 */
	constructor() {
		super(Entries.createEntry());
	}
}

module.exports = {UiEntry};

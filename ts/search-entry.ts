const {Entries} = require('..');
const {UiEntryBase} = require('./entry-base');

/**
 * A single line text entry control to search text.
 * @extends UiEntryBase
 */
class UiSearchEntry extends UiEntryBase {
	/**
	 * Create a new UiSearchEntry object.
	 * @return {UiSearchEntry}
	 */
	constructor() {
		super(Entries.createSearch());
	}
}

module.exports = {UiSearchEntry};

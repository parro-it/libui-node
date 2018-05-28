const {MultilineEntry} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A multiline text entry.
 * @extends UiControl
 */
class UiMultilineEntry extends UiControl {
	/**
	 * Create a new UiMultilineEntry object.
	 * @return {UiMultilineEntry}
	 */
	constructor() {
		super(MultilineEntry.create());
	}

	/**
	 * Set or return the the content of the multiline entry.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiMultilineEntry);
		return MultilineEntry.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiMultilineEntry);
		MultilineEntry.setText(this.handle, String(value));
	}

	/**
	 * Whether the user is allowed to change the entry's contents.
	 * @return {boolean}
	 */
	get readOnly() {
		this._ensureType(UiMultilineEntry);
		return MultilineEntry.getReadOnly(this.handle);
	}

	set readOnly(value) {
		this._ensureType(UiMultilineEntry);
		MultilineEntry.setReadOnly(this.handle, Boolean(value));
	}

	/**
	 * Append the specified text to the entry's contents.
	 * @param  {string} text - the text to append.
	 */
	append(text) {
		this._ensureType(UiMultilineEntry);
		MultilineEntry.append(this.handle, String(text));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry's contents
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(UiMultilineEntry);
		MultilineEntry.onChanged(this.handle, callback);
	}
}

module.exports = {UiMultilineEntry};

const {Entries} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A base class for text related entries.
 * @extends UiControl
 */
class UiEntryBase extends UiControl {
	constructor(handle) {
		super(handle);
	}

	/**
	 * Set or return the the content of the entry.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiEntryBase);
		return Entries.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiEntryBase);
		Entries.setText(this.handle, String(value));
	}

	/**
	 * Whether the user is allowed to change the entry's contents.
	 * @return {boolean}
	 */
	get readOnly() {
		this._ensureType(UiEntryBase);
		return Entries.getReadOnly(this.handle);
	}

	set readOnly(value) {
		this._ensureType(UiEntryBase);
		Entries.setReadOnly(this.handle, Boolean(value));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(UiEntryBase);
		Entries.onChanged(this.handle, callback);
	}
}

module.exports = {UiEntryBase};

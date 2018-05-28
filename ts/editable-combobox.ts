const {EditableCombobox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A drop down combo box that allows to select an item from list or to specify a custom
 * value.
 * @extends UiControl
 */
class UiEditableCombobox extends UiControl {
	/**
	 * Create a new UiEditableCombobox object.
	 * @return {UiEditableCombobox}
	 */
	constructor() {
		super(EditableCombobox.create());
	}

	/**
	 * Return or set the current text.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiEditableCombobox);
		return EditableCombobox.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiEditableCombobox);
		EditableCombobox.setText(this.handle, String(value));
	}

	/**
	 * Append a new text item to the drop down list.
	 * @param  {string} text - the item to append.
	 */
	append(text) {
		this._ensureType(UiEditableCombobox);
		EditableCombobox.append(this.handle, String(text));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the text (or item) changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(UiEditableCombobox);
		EditableCombobox.onChanged(this.handle, callback);
	}
}

module.exports = {UiEditableCombobox};

const {Combobox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A drop down combo box that allow list selection only.
 * @extends UiControl
 */
class UiCombobox extends UiControl {
	/**
	 * Create a new UiCombobox object.
	 * @return {UiCombobox}
	 */
	constructor() {
		super(Combobox.create());
	}

	/**
	 * Return or set the current selected item by index.
	 * @return {number}
	 */
	get selected() {
		this._ensureType(UiCombobox);
		return Combobox.getSelected(this.handle);
	}

	set selected(value) {
		this._ensureType(UiCombobox);
		Combobox.setSelected(this.handle, value);
	}

	/**
	 * Append a new text item to the drop down list.
	 * @param  {string} text - the item to append.
	 */
	append(text) {
		this._ensureType(UiCombobox);
		Combobox.append(this.handle, String(text));
	}

	/**
	 * Add a listener to the `selected` event. Emitted whenever the selected
	 * item changes.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onSelected(callback) {
		this._ensureType(UiCombobox);
		Combobox.onSelected(this.handle, callback);
	}
}

module.exports = {UiCombobox};

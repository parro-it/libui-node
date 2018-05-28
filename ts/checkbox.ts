const {Checkbox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A checkbox control.
 * @extends UiControl
 */
class UiCheckbox extends UiControl {
	/**
	 * Create a new UiCheckbox object.
	 * @return {UiCheckbox}
	 */
	constructor(label = '') {
		super(Checkbox.create(String(label)));
	}

	/**
	 * Set or return the text label for the checkbox.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiCheckbox);
		return Checkbox.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiCheckbox);
		Checkbox.setText(this.handle, String(value));
	}

	/**
	 * Whether the control is checked.
	 * @return {boolean}
	 */
	get checked() {
		this._ensureType(UiCheckbox);
		return Checkbox.getChecked(this.handle);
	}

	set checked(value) {
		this._ensureType(UiCheckbox);
		Checkbox.setChecked(this.handle, Boolean(value));
	}

	/**
	 * Add a listener to the `toggled` event. Emitted whenever the control
	 * `checked` state change.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onToggled(callback) {
		this._ensureType(UiCheckbox);
		Checkbox.onToggled(this.handle, callback);
	}
}

module.exports = {UiCheckbox};

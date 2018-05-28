const {Spinbox} = require('..');
const {UiControl} = require('./ui-control');

/**
 * An entry control for numerical values.
 * @extends UiControl
 */
class UiSpinbox extends UiControl {
	/**
	 * Create a new UiSpinbox object.
	 * @param  {number} min - minimum value of the spinbox.
	 * @param  {number} max - maximum value of the spinbox.
	 * @return {UiSpinbox}
	 */
	constructor(min, max) {
		super(Spinbox.create(min, max));
	}

	/**
	 * Set or return the the content of spinbox.
	 * @return {number}
	 */
	get value() {
		this._ensureType(UiSpinbox);
		return Spinbox.getValue(this.handle);
	}

	set value(value) {
		this._ensureType(UiSpinbox);
		Spinbox.setValue(this.handle, value);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the spinbox value changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is fired.
	 */
	onChanged(callback) {
		this._ensureType(UiSpinbox);
		Spinbox.onChanged(this.handle, callback);
	}
}

module.exports = {UiSpinbox};

const {UiControl} = require('./ui-control');
const {DateTimePickers} = require('..');

/**
 * A base class for date/time related entries.
 * @extends UiControl
 */
class DateTimePickerBase extends UiControl {
	constructor(handle) {
		super(handle);
	}

	/**
	 * Set or return the date/time represented by the control.
	 * @return {Date}
	 */
	get time() {
		this._ensureType(DateTimePickerBase);
		const fromEpoch = DateTimePickers.getTime(this.handle);
		return new Date(fromEpoch * 1000);
	}

	set time(value) {
		this._ensureType(DateTimePickerBase);
		DateTimePickers.setTime(this.handle, value.getTime() / 1000);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the entry contents
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(DateTimePickerBase);
		DateTimePickers.onChanged(this.handle, callback);
	}
}

module.exports = {DateTimePickerBase};

const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A control to set a date.
 * @extends DateTimePickerBase
 */
class UiDatePicker extends DateTimePickerBase {
	/**
	 * Create a new UiDatePicker object.
	 * @return {UiDatePicker}
	 */
	constructor() {
		super(DateTimePickers.createDatePicker());
	}
}

module.exports = {UiDatePicker};

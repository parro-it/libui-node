const {DateTimePickers} = require('..');
const {DateTimePickerBase} = require('./date-time-picker-base');

/**
 * A control to set a time.
 * @extends DateTimePickerBase
 */
class UiTimePicker extends DateTimePickerBase {
	/**
	 * Create a new UiTimePicker object.
	 * @return {UiTimePicker}
	 */
	constructor() {
		super(DateTimePickers.createTimePicker());
	}
}

module.exports = {UiTimePicker};

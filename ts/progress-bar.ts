const {ProgressBar} = require('..');
const {UiControl} = require('./ui-control');

/**
 * Progress bar control.
 * @extends UiControl
 */
class UiProgressBar extends UiControl {
	/**
	 * Create a new UiProgressBar object.
	 * @return {UiProgressBar}
	 */
	constructor() {
		super(ProgressBar.create());
	}

	/**
	 * The current position of the progress bar. Can be set to -1 to create
	 * an indeterminate progress bar.
	 * @return {number}
	 */
	get value() {
		this._ensureType(UiProgressBar);
		return this._value;
	}

	set value(value) {
		this._ensureType(UiProgressBar);
		this._value = Number(value);
		ProgressBar.setValue(this.handle, this._value);
	}
}

module.exports = {UiProgressBar};

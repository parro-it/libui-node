const {Slider} = require('..');
const {UiControl} = require('./ui-control');

/**
 * Horizontal slider to set numerical values.
 * @extends UiControl
 */
class UiSlider extends UiControl {
	/**
	 * Create a new UiSlider object.
	 * @param  {number} min - minimum value of the slider.
	 * @param  {number} max - maximum value of the slider.
	 * @return {UiSlider}
	 */
	constructor(min = 0, max = 100) {
		super(Slider.create(min, max));
	}

	/**
	 * Set or return the the content of the slider.
	 * @return {number}
	 */
	get value() {
		this._ensureType(UiSlider);
		return Slider.getValue(this.handle);
	}

	set value(value) {
		this._ensureType(UiSlider);
		Slider.setValue(this.handle, value);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the slider value
	 * changed.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(UiSlider);
		Slider.onChanged(this.handle, callback);
	}
}

module.exports = {UiSlider};

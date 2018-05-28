const {ColorButton} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A button that opens a color palette popup.
 * @extends UiControl
 */
class UiColorButton extends UiControl {
	/**
	 * Create a new UiColorButton object.
	 * @return {UiColorButton}
	 */
	constructor() {
		super(ColorButton.create());
	}

	/**
	 * Set or return the ColorButton color value.
	 * @return {Color}
	 */
	get color() {
		this._ensureType(UiColorButton);
		return ColorButton.getColor(this.handle);
	}

	set color(value) {
		this._ensureType(UiColorButton);
		ColorButton.setColor(this.handle, value.r, value.g, value.b, value.a);
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user
	 * changed the selected color.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onChanged(callback) {
		this._ensureType(UiColorButton);
		ColorButton.onChanged(this.handle, callback);
	}
}

module.exports = {UiColorButton};

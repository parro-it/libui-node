const {FontButton} = require('..');
const {FontDescriptor} = require('./font-descriptor');
const {UiControl} = require('./ui-control');

/**
 * A button that opens a popup to choose a font.
 * @extends UiControl
 */
class UiFontButton extends UiControl {
	/**
	 * Create a new UiFontButton object.
	 * @return {UiFontButton}
	 */
	constructor() {
		super(FontButton.create());
	}

	/**
	 * Return the FontButton font value.
	 * @return {FontDescriptor}
	 */
	get font() {
		this._ensureType(UiFontButton);
		return new FontDescriptor(FontButton.getFont(this.handle));
	}

	/**
	 * Add a listener to the `changed` event. Emitted whenever the user
	 * changed the selected font.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 * @return {undefined}
	 */
	onChanged(callback) {
		this._ensureType(UiFontButton);
		FontButton.onChanged(this.handle, callback);
	}
}

module.exports = {UiFontButton};

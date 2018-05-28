const {Button} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A simple button.
 * @extends UiControl
 */
class UiButton extends UiControl {
	/**
	 * Create a new UiButton object.
	 * @return {UiButton}
	 */
	constructor(label) {
		super(Button.create(String(label)));
	}

	/**
	 * Set or return the text of the button.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiButton);
		return Button.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiButton);
		Button.setText(this.handle, String(value));
	}

	/**
	 * Emitted when the button is clicked
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onClicked(callback) {
		this._ensureType(UiButton);
		Button.onClicked(this.handle, callback);
	}
}

module.exports = {UiButton};

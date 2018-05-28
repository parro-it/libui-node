const {Label} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A static text label.
 * @extends UiControl
 */
class UiLabel extends UiControl {
	/**
	 * Create a new UiLabel object.
	 * @param  {string} text - initial content of the label
	 * @return {UiLabel}
	 */
	constructor(text = '') {
		super(Label.create(String(text)));
	}

	/**
	 * Set or return the the content of the label.
	 * @return {string}
	 */
	get text() {
		this._ensureType(UiLabel);
		return Label.getText(this.handle);
	}

	set text(value) {
		this._ensureType(UiLabel);
		Label.setText(this.handle, String(value));
	}
}

module.exports = {UiLabel};

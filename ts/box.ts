const {Box} = require('..');
const {UiControl} = require('./ui-control');
/**
 * Base class for vertical and horizontal boxes
 * @extends UiControl
 */
class UiBox extends UiControl {
	constructor(handle) {
		super(handle);
	}

	/**
	 * If true, the container inserts some space between children.
	 * @return {boolean}
	 */
	get padded() {
		this._ensureType(UiBox);
		return Box.getPadded(this.handle);
	}

	set padded(value) {
		this._ensureType(UiBox);
		Box.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Append a new child control as the last child.
	 * @param  {UiControl} control - the control to add as a child.
	 * @param  {boolean} stretchy - whever the control should fill all the
	 * available space.
	 */
	append(control, stretchy) {
		this._ensureType(UiBox);
		control._ensureType(UiControl, 'control');
		Box.append(this.handle, control.handle, Boolean(stretchy));
	}

	/**
	 * Remove a child control at specified position.
	 * @param  {number} index - the index of the control to remove
	 */
	deleteAt(index) {
		this._ensureType(UiBox);
		Box.deleteAt(this.handle, index);
	}
}

module.exports = {UiBox};

const {Group} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A container for a single control that provides a caption and visually groups
 * it's child.
 * @extends UiControl
 */
class UiGroup extends UiControl {
	/**
	 * Create a new UiGroup object.
	 *
	 * @param {string} title - text to show in Group title bar.
	 * @return {UiGroup} new instance.
	 */
	constructor(title = '') {
		super(Group.create(String(title)));
	}

	/**
	 * Set or return the text to show in group caption.
	 *
	 * @return {string}
	 */
	get title() {
		this._ensureType(UiGroup);
		return Group.getTitle(this.handle);
	}

	set title(value) {
		this._ensureType(UiGroup);
		Group.setTitle(this.handle, String(value));
	}

	/**
	 * Set the control to show in this group content area.
	 * UiGroup instances can contain only one control. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param {UiControl} control - the control to add as child.
	 * @param {boolean} stretchy - whever the control should fill all the
	 * available space.
	 */
	setChild(control, stretchy) {
		this._ensureType(UiGroup);
		control._ensureType(UiControl, 'control');
		Group.setChild(this.handle, control.handle, Boolean(stretchy));
	}

	/**
	 * When true, an internal margin is added to the group.
	 *
	 * @return {boolean}
	 */
	get margined() {
		this._ensureType(UiGroup);
		return Group.getMargined(this.handle);
	}

	set margined(value) {
		this._ensureType(UiGroup);
		Group.setMargined(this.handle, Boolean(value));
	}
}

module.exports = {UiGroup};

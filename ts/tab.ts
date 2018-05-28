const {Tab} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A container that show each chidren in a separate tab.
 * @extends UiControl
 */
class UiTab extends UiControl {
	/**
	 * Create a new UiTab object.
	 *
	 * @return {UiTab} new instance.
	 */
	constructor() {
		super(Tab.create());
	}

	/**
	 * When true, an internal margin is added to the Tab.
	 * @return {boolean}
	 */
	get margined() {
		this._ensureType(UiTab);
		return Tab.getMargined(this.handle);
	}

	set margined(value) {
		this._ensureType(UiTab);
		Tab.setMargined(this.handle, Boolean(value));
	}

	/**
	 * Append a new child control as last tab page.
	 * @param  {UiControl} control - the control to add as a child.
	 * @param  {boolean} string - the text to show for the new page caption.
	 */
	append(label, control) {
		this._ensureType(UiTab);
		control._ensureType(UiControl, 'control');

		Tab.append(this.handle, String(label), control.handle);
	}

	/**
	 * Insert a new child control before specified position.
	 * @param  {string} label - the text to show for the new page caption.
	 * @param  {number} before - the control will be inserted before this position
	 * @param  {UiControl} control - the control to insert
	 */
	insertAt(label, before, control) {
		this._ensureType(UiTab);
		before._ensureType(UiControl, 'before');
		control._ensureType(UiControl, 'control');

		Tab.insertAt(this.handle, String(label), before, control.handle);
	}

	/**
	 * Return the total number of tab pages contained in the control.
	 * @return {number} number of pages
	 */
	numPages() {
		this._ensureType(UiTab);
		return Tab.numPages(this.handle);
	}

	/**
	 * Remove the tab and control at specified position.
	 * @param  {number} index - the index of the tab to remove.
	 */
	deleteAt(index) {
		this._ensureType(UiTab);
		Tab.numPages(this.handle, Number(index));
	}
}

module.exports = {UiTab};

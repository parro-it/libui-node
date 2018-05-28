const {Window} = require('..');
const {UiControl} = require('./ui-control');

/**
 * The UiWindow class is responsible for showing and managing native windows.
 * A UiWindow instance can contain only one child. If you need
 * more than one, you have to use [Containers](containers.md).
 */
class UiWindow {
	/**
	 * Create a new UiWindow object.
	 *
	 * @param {string} title - text to show in window title bar.
	 * @param {number} width - width of window in pixels.
	 * @param {number} height -  height of window in pixels.
	 * @param {boolean} hasMenubar - whether this window has a menu bar.
	 * See [Menu](#menubar).
	 * @return {UiWindow} new instance.
	 */
	constructor(title, width, height, hasMenubar) {
		this.handle = Window.create(String(title), width, height, Boolean(hasMenubar));
	}

	/**
	 * Show the window.
	 *
	 */
	show() {
		this._ensureType(UiWindow);
		return Window.show(this.handle);
	}

	/**
	 * Add a listener to the `closing` event. This event is emitted when the OS
	 * window close button is clicked. You are responsible for closing the
	 * window in response to this event.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onClosing(callback) {
		this._ensureType(UiWindow);
		Window.onClosing(this.handle, callback);
	}

	/**
	 * Add a listener to the `contentSizeChanged` event. This event is emitted
	 * when window content size change.
	 *
	 * @param  {Function} callback - callback to execute when the event is
	 * fired.
	 */
	onContentSizeChanged(callback) {
		this._ensureType(UiWindow);
		Window.onContentSizeChanged(this.handle, callback);
	}

	/**
	 * Close the window.
	 *
	 */
	close() {
		this._ensureType(UiWindow);
		Window.close(this.handle);
	}

	/**
	 * Set or return the text to show in window title bar.
	 *
	 * @return {string}
	 */
	get title() {
		this._ensureType(UiWindow);
		return Window.getTitle(this.handle);
	}

	set title(value) {
		this._ensureType(UiWindow);
		Window.setTitle(this.handle, String(value));
	}

	/**
	 * Set or return the size in pixel of the content area of the window
	 * (excluding the size of the window decoration). This mean that if you set window
	 * size to 0,0 you still see title bar and OS window buttons.
	 *
	 * @return {{width: number, height: number}}
	 */
	get contentSize() {
		this._ensureType(UiWindow);
		return Window.getContentSize(this.handle);
	}

	set contentSize({width, height}) {
		this._ensureType(UiWindow);
		Window.setContentSize(this.handle, width, height);
	}

	/**
	 * Set the control to show in this window content area.
	 * UiWindow instances can contain only one child. If you need
	 * more, you have to use [Containers](containers.md).
	 *
	 * @param {UiControl} control - the control to add as child.
	 * @param {boolean} stretchy - whever the control should fill all the
	 * available space.
	 */
	setChild(control, stretchy) {
		this._ensureType(UiWindow);
		control._ensureType(UiControl, 'control');

		Window.setChild(this.handle, control.handle, Boolean(stretchy));
	}

	/**
	 * When true, an internal margin is added to the window.
	 *
	 * @return {boolean}
	 */
	get margined() {
		this._ensureType(UiWindow);
		return Window.getMargined(this.handle);
	}

	set margined(value) {
		this._ensureType(UiWindow);
		Window.setMargined(this.handle, Boolean(value));
	}

	/**
	 * When true, the window is displayed without a border.
	 *
	 * @return {boolean}
	 */
	get borderless() {
		this._ensureType(UiWindow);
		return Window.getBorderless(this.handle);
	}

	set borderless(value) {
		this._ensureType(UiWindow);
		Window.setBorderless(this.handle, Boolean(value));
	}

	/**
	 * When true, the window is displayed in full screen mode.
	 *
	 * @return {boolean}
	 */
	get fullscreen() {
		this._ensureType(UiWindow);
		return Window.getFullscreen(this.handle);
	}

	set fullscreen(value) {
		this._ensureType(UiWindow);
		Window.setFullscreen(this.handle, Boolean(value));
	}

	_ensureType(expectedContructor, argName = 'this') {
		if (this instanceof expectedContructor) {
			return;
		}
		throw new TypeError(`Expect a ${expectedContructor.name} "${argName}", got a ${
			this.constructor.name}`);
	}
}

module.exports = {UiWindow};

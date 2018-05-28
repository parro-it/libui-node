const {Menu} = require('..');
/**
 * The top bar on a window that can have multiple items.
 * The menu must be created before the first UiWindow for it to take effect.
 * It is made up of UiMenuItem instances.
 */
class UiMenu {
	/**
	 * Create a new UiMenu object.
	 * @param  {string} caption - The caption of the menu.
	 * @return {UiMenu}
	 */
	constructor(caption) {
		this.handle = Menu.create(String(caption));
	}

	/**
	 * Append a normal menu button.
	 * @param  {string} caption - The caption of the menu item.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendItem(caption) {
		return new UiMenuItem(Menu.appendItem(this.handle, String(caption)));
	}

	/**
	 * Append a menu button with a checkable option.
	 * @param  {String} caption - The caption of the menu item.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendCheckItem(caption) {
		return new UiMenuItem(Menu.appendCheckItem(this.handle, String(caption)));
	}

	/**
	 * Append a Quit button. This accepts no text, the caption defaults
	 * to `Quit`.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendQuitItem() {
		return new UiMenuItem(Menu.appendQuitItem(this.handle));
	}

	/**
	 * Append a Preferences button. This accepts no text, the caption
	 * defaults to `Preferences`.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendPreferencesItem() {
		return new UiMenuItem(Menu.appendPreferencesItem(this.handle));
	}

	/**
	 * Append an About button. This accepts no text, the caption
	 * defaults to `About`.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendAboutItem() {
		return new UiMenuItem(Menu.appendAboutItem(this.handle));
	}

	/**
	 * Append a Separator between menu items.
	 * @return {UiMenuItem} the new appended UiMenuItem
	 */
	appendSeparator() {
		return new UiMenuItem(Menu.appendSeparator(this.handle));
	}
}

/**
 * A single button contained in a menu.
 */
class UiMenuItem {
	/**
	 * Create a new UiMenuItem object.
	 * @return {UiMenuItem}
	 */
	constructor(handle) {
		this.handle = handle;
	}

	/**
	 * Enable the menu item.
	 */
	enable() {
		Menu.enableItem(this.handle);
	}

	/**
	 * Disable the menu item
	 */
	disable() {
		Menu.disableItem(this.handle);
	}

	/**
	 * Register a callback for the click event of the menu item.
	 * @param  {Function} callback - the function to register as
	 * callback for the event.
	 */
	onClicked(callback) {
		Menu.onItemClicked(this.handle, callback);
	}

	/**
	 * If the item is created using appendCheckItem, then set
	 * whether it is checked or not.
	 * @return {boolean}
	 */
	get checked() {
		return Menu.getItemChecked(this.handle);
	}

	set checked(value) {
		Menu.setItemChecked(this.handle, Boolean(value));
	}
}

module.exports = {
	UiMenu,
	UiMenuItem
};

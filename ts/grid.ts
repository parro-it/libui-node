const {Grid} = require('..');
const {UiControl} = require('./ui-control');

/**
 * A powerful container that allow to specify size and position of each children.
 * @extends UiControl
 */
class UiGrid extends UiControl {
	/**
	 * Create a new UiGrid object.
	 * @return {UiGrid}
	 */
	constructor() {
		super(Grid.create());
	}

	/**
	 * If true, the container inserts some space between children.
	 * @return {boolean}
	 */
	get padded() {
		return Grid.getPadded(this.handle);
	}

	set padded(value) {
		this._ensureType(UiGrid);
		Grid.setPadded(this.handle, Boolean(value));
	}

	/**
	 * Insert a new child control before specified control.
	 * @param  {UiControl} child - the control to insert
	 * @param  {UiControl} before - the control will be inserted before this position
	 * @param  {number} at      [description]
	 * @param  {number} xspan - How many columns the component takes off.
	 * @param  {number} yspan - How many rows the component takes off.
	 * @param  {number} hexpand - whether the component can expand horizontally.
	 * @param  {number} halign - whether the component is aligned with the other
	 components in the column.
	 * @param  {number} vexpand - whether the component can expand vertically.
	 * @param  {number} valign - whether the component is aligned with the other
	 components in the row.
	 */
	insertAt(child, before, at, xspan, yspan, hexpand, halign, vexpan, valign) {
		this._ensureType(UiGrid);
		child._ensureType(UiControl, 'child');
		before._ensureType(UiControl, 'before');

		Tab.insertAt(this.handle, child.handle, before.handle, at, xspan, yspan, hexpand,
					 halign, vexpan, valign);
	}

	/**
	 * Insert a new child control.
	 *
	 * > UIGrid expand does not work correctly when both align horizontal and align
	 * vertical are set. You must choose one so libui knows which direction to expand.
	 *
	 * @param  {UiControl} child - the control to add as child.
	 * @param  {number} left - What column the component resides in.
	 * @param  {number} top - What row the component resides in.
	 * @param  {number} xspan - How many columns the component takes off.
	 * @param  {number} yspan - How many rows the component takes off.
	 * @param  {number} hexpand - whether the component can expand horizontally.
	 * @param  {number} halign - whether the component is aligned with the other
	 * components in the column.
	 * @param  {number} vexpand - whether the component can expand vertically.
	 * @param  {number} valign - whether the component is aligned with the other
	 * components in the row.
	 */
	append(child, left, top, xspan, yspan, hexpand, halign, vexpand, valign) {
		this._ensureType(UiGrid);
		child._ensureType(UiControl, 'control');

		Grid.append(this.handle, child.handle, left, top, xspan, yspan, hexpand, halign,
					vexpand, valign);
	}
}

UiGrid.align = {
	fill: 0,
	start: 1,
	center: 2,
	end: 3,
};

UiGrid.at = {
	leading: 0,
	top: 1,
	trailing: 2,
	bottom: 3,
};

module.exports = {UiGrid};

const {AreaContext} = require('../..');
const {UiDrawPath, DrawBrush, DrawStrokeParams} = require('./draw');
const UiDrawMatrix = require('./matrix');
const DrawTextLayout = require('./textlayout');

class AreaDrawParams {
	constructor(context, areaWidth, areaHeight, clipX, clipY, clipWidth, clipHeight) {
		this.context = context;
		this.areaWidth = areaWidth;
		this.areaHeight = areaHeight;
		this.clipX = clipX;
		this.clipY = clipY;
		this.clipWidth = clipWidth;
		this.clipHeight = clipHeight;
	}
}

class AreaDrawContext {
	constructor(handle) {
		this.handle = handle;
	}

	/**
	 * Draw a path (the outline).
	 * @param {UiDrawPath} path - the path to draw
	 * @param {DrawBrush} brush - the brush to draw with
	 * @param {DrawStrokeParams} stroke - the stroke params to draw with
	 */
	stroke(path, brush, stroke) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be an UiDrawPath object');
		}
		if (!(brush instanceof DrawBrush)) {
			throw new TypeError('The \'brush\' argument has to be an DrawBrush object');
		}
		if (!(stroke instanceof DrawStrokeParams)) {
			throw new TypeError(
				'The \'stroke\' argument has to be an DrawStrokeParams object');
		}
		AreaContext.stroke(this.handle, path.handle, brush.handle, stroke.handle);
	}

	/**
	 * Draw a path (filled).
	 * @param {UiDrawPath} path - the path to draw
	 * @param {DrawBrush} brush - the brush to draw with
	 */
	fill(path, brush) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
		}
		if (!(brush instanceof DrawBrush)) {
			throw new TypeError('The \'brush\' argument has to be a DrawBrush object');
		}
		AreaContext.fill(this.handle, path.handle, brush.handle);
	}

	/**
	 * Apply a matrix transformation
	 * @param {UiDrawMatrix} matrix - the matrix to apply
	 */
	transform(matrix) {
		if (!(matrix instanceof UiDrawMatrix)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
		}
		AreaContext.transform(this.handle, matrix.handle);
	}

	/**
	 * @param {UiDrawPath} path -
	 */
	clip(path) {
		if (!(path instanceof UiDrawPath)) {
			throw new TypeError('The \'path\' argument has to be a UiDrawPath object');
		}
		AreaContext.clip(this.handle, path.handle);
	}

	/**
	 * Save a transformation state.
	 */
	save() {
		AreaContext.save(this.handle);
	}

	/**
	 * Restore a transformation state.
	 */
	restore() {
		AreaContext.restore(this.handle);
	}

	text(x, y, textLayout) {
		if (!(textLayout instanceof DrawTextLayout)) {
			throw new TypeError(
				'The \'textLayout\' argument has to be a DrawTextLayout object');
		}
		AreaContext.text(this.handle, x, y, textLayout.handle);
	}
}

module.exports = {
	AreaDrawParams,
	AreaDrawContext
};

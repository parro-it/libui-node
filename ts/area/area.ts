const {Area} = require('../..');
const {UiControl} = require('../ui-control');

/**
 * An area to draw on.
 */
class UiArea extends UiControl {
	/**
	 * Create a new UiArea object.
	 * @param {Function} draw - callback to draw onto area
	 * @param {Function} mouse - callback for mouse events
	 * @param {Function} mouseCrossed - callback for entering or leaving the area
	 * @param {Function} dragBroken - callback
	 * @param {Function} keyEvent - callback for key events
	 * @return {UiArea}
	 */
	constructor(draw, mouse, mouseCrossed, dragBroken, key, width, height) {
		const drawCb = p => draw(this, p);
		const mouseCb = evt => mouse(this, evt);
		const mouseCrossedCb = left => mouseCrossed(this, left);
		const dragBrokenCb = () => dragBroken(this);
		const keyCb = evt => key(this, evt);

		if (typeof width == 'undefined') {
			super(Area.create(drawCb, mouseCb, mouseCrossedCb, dragBrokenCb, keyCb));
		} else {
			super(Area.createScrolling(drawCb, mouseCb, mouseCrossedCb, dragBrokenCb,
									   keyCb, width, height));
			this.type = 'scrolling';
		}
	}

	/**
	 * Force a redraw of the area (calls draw callback).
	 */
	queueRedrawAll() {
		this._ensureType(UiArea);
		Area.queueRedrawAll(this.handle);
	}

	/**
	 * Let the mouse move the window (only callable in the draw callback)
	 */
	beginWindowMove() {
		this._ensureType(UiArea);
		Area.beginWindowMove(this.handle);
	}

	/**
	 * Let the mouse resize the window (only callable in the draw callback)
	 * @param {number} edge - the size which is held by the mouse
	 */
	beginWindowResize(edge) {
		this._ensureType(UiArea);
		Area.beginWindowResize(this.handle, edge);
	}

	setSize(w, h) {
		this._ensureType(UiArea);
		if (this.type !== 'scrolling') {
			throw new TypeError('setSize can only be called on scrolling areas!');
		}
		Area.setSize(this.handle, w, h);
	}

	scrollTo(x, y, w, h) {
		this._ensureType(UiArea);
		if (this.type !== 'scrolling') {
			throw new TypeError('scrollTo can only be called on scrolling areas!');
		}
		Area.scrollTo(this.handle, x, y, w, h);
	}
}

UiArea.resizeEdge = {
	left: 0,
	top: 1,
	right: 2,
	bottom: 3,
	topLeft: 4,
	topRight: 5,
	bottomLeft: 6,
	bottomRight: 7
};

class UiAreaMouseEvent {
	constructor(x, y, areaWidth, areaHeight, down, up, count, modifiers, held1To64) {
		this.x = x;
		this.y = y;
		this.areaWidth = areaWidth;
		this.areaHeight = areaHeight;
		this.down = down;
		this.up = up;
		this.count = count;
		this.modifiers = modifiers;
		this.held1To64 = held1To64;
	}
}

class UiAreaKeyEvent {
	constructor(key, extKey, modifier, modifiers, up) {
		this.key = String.fromCharCode(key);
		this.extKey = extKey;
		this.modifier = modifier;
		this.modifiers = modifiers;
		this.up = up;
	}
}

UiAreaKeyEvent.modifierKeys = {
	ctrl: 1 << 0,
	alt: 1 << 1,
	shift: 1 << 2,
	super: 1 << 3
};

UiAreaKeyEvent.extKeys = {
	escape: 1,
	insert: 2, // equivalent to "Help" on Apple keyboards
	delete: 3,
	home: 4,
	end: 5,
	pageUp: 6,
	pageDown: 7,
	up: 8,
	down: 9,
	left: 10,
	right: 11,
	f1: 12, // F1..F12 are guaranteed to be consecutive
	f2: 13,
	f3: 14,
	f4: 15,
	f5: 16,
	f6: 17,
	f7: 18,
	f8: 19,
	f9: 20,
	f10: 21,
	f11: 22,
	f12: 23,
	n0: 24, // numpad keys; independent of Num Lock state
	n1: 25, // N0..N9 are guaranteed to be consecutive
	n2: 26,
	n3: 27,
	n4: 28,
	n5: 29,
	n6: 30,
	n7: 31,
	n8: 32,
	n9: 33,
	nDot: 34,
	nEnter: 35,
	nAdd: 36,
	nSubtract: 37,
	nMultiply: 38,
	nDivide: 39
};

module.exports = {
	UiArea,
	UiAreaMouseEvent,
	UiAreaKeyEvent
};

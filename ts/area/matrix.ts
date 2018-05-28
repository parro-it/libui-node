const {AreaMatrix} = require('../..');

class UiDrawMatrix {
	constructor() {
		this.handle = AreaMatrix.create();
	}

	setIdentity() {
		AreaMatrix.setIdentity(this.handle);
	}

	scale(xCenter, yCenter, x, y) {
		AreaMatrix.scale(this.handle, xCenter, yCenter, x, y);
	}

	translate(x, y) {
		AreaMatrix.translate(this.handle, x, y);
	}

	rotate(x, y, amount) {
		AreaMatrix.rotate(this.handle, x, y, amount);
	}

	skew(x, y, xAmount, yAmount) {
		AreaMatrix.skew(this.handle, x, y, xAmount, yAmount);
	}

	multiply(m) {
		AreaMatrix.multiply(this.handle, m.handle);
	}

	invertible(m) {
		return AreaMatrix.invertible(this.handle);
	}

	// returns true it it worked
	invert(m) {
		return AreaMatrix.invert(this.handle);
	}

	set(i, j, v) {
		if (i < 0 || 2 < i) {
			throw new TypeError('i has to be: 0 <= i <= 2')
		}
		if (j < 0 || 2 < j) {
			throw new TypeError('j has to be: 0 <= j <= 2')
		}
		AreaMatrix.set(this.handle, i, j, v);
	}

	get(i, j) {
		if (i < 0 || 2 < i) {
			throw new TypeError('i has to be: 0 <= i <= 2')
		}
		if (j < 0 || 2 < j) {
			throw new TypeError('j has to be: 0 <= j <= 2')
		}
		return AreaMatrix.get(this.handle, i, j);
	}

	// for matrix[0][1] (getter & setter)
	_getter(i) {
		return new Proxy({}, {
			get: (target, propertyName, receiver) => {
				return this.get(i, parseInt(propertyName));
			},
			set: (target, propertyName, value, receiver) => {
				this.set(i, Number(propertyName), value);
				return true;
			}
		});
	}

	get 0() {
		return this._getter(0);
	}

	get 1() {
		return this._getter(1);
	}

	get 2() {
		return this._getter(2);
	}
}

module.exports = UiDrawMatrix;

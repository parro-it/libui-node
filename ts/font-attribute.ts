const {FontAttribute: FontAttributeC} = require('..');
const {OpenTypeFeatures} = require('./font-opentype')

class FontAttribute {
	constructor(handle) {
		this.handle = handle;
	}

	_check(name) {
		if (this.type !== FontAttribute.type[name]) {
			throw new Error('Only ' + name + ' attributes have a \'' + name +
							'\' attribute')
		}
	}

	get type() {
		return FontAttributeC.getType(this.handle);
	}

	getAttributeType() {
		return this.type;
	}

	get family() {
		this._check('family');
		return FontAttributeC.getFamily(this.handle);
	}

	get size() {
		this._check('size');
		return FontAttributeC.getSize(this.handle);
	}

	get weight() {
		this._check('weight');
		return FontAttributeC.getWeight(this.handle);
	}

	get italic() {
		this._check('italic');
		return FontAttributeC.getItalic(this.handle);
	}

	get stretch() {
		this._check('stretch');
		return FontAttributeC.getStretch(this.handle);
	}

	get color() {
		this._check('color');
		return FontAttributeC.getColor(this.handle);
	}

	get underlineColor() {
		this._check('underlineColor');
		return FontAttributeC.getUnderlineColor(this.handle);
	}

	get OTFeatures() {
		this._check('features');
		return new OpenTypeFeatures(FontAttributeC.getOTFeatures(this.handle));
	}

	static newFamily(v) {
		return new FontAttribute(FontAttributeC.createFamily(v));
	}

	static newSize(v) {
		return new FontAttribute(FontAttributeC.createSize(v));
	}

	static newWeight(v) {
		return new FontAttribute(FontAttributeC.createWeight(v));
	}

	static newItalic(v) {
		return new FontAttribute(FontAttributeC.createItalic(v));
	}

	static newStretch(v) {
		return new FontAttribute(FontAttributeC.createStretch(v));
	}

	static newColor(c) {
		return new FontAttribute(FontAttributeC.createColor(c.r, c.g, c.b, c.a));
	}

	static newBackgroundColor(c) {
		return new FontAttribute(
			FontAttributeC.createBackgroundColor(c.r, c.g, c.b, c.a));
	}

	static newUnderline(v) {
		return new FontAttribute(FontAttributeC.createUnderline(v));
	}

	static newUnderlineColor(type, {r = 0, g = 0, b = 0, a = 0} = {}) {
		return new FontAttribute(FontAttributeC.createUnderlineColor(type, r, g, b, a));
	}

	static newOTFeatures(otf) {
		if (!(otf instanceof OpenTypeFeatures)) {
			throw new TypeError(
				'The \'otf\' argument has to be a OpenTypeFeatures object');
		}
		return new FontAttribute(FontAttributeC.createOTFeatures(otf.handle));
	}
}

FontAttribute.weight = {
	minimum: 0,
	thin: 100,
	ultraLight: 200,
	light: 300,
	book: 350,
	normal: 400,
	medium: 500,
	semiBold: 600,
	bold: 700,
	ultraBold: 800,
	heavy: 900,
	ultraHeavy: 950,
	maximum: 1000
};

FontAttribute.italic = {
	normal: 0,
	oblique: 1,
	italic: 2
};

FontAttribute.stretch = {
	ultraCondensed: 0,
	extraCondensed: 1,
	condensed: 2,
	semiCondensed: 3,
	normal: 4,
	semiExpanded: 5,
	expanded: 6,
	extraExpanded: 7,
	ultraExpanded: 8
};

FontAttribute.type = {
	family: 0,
	size: 1,
	weight: 2,
	italic: 3,
	stretch: 4,
	color: 5,
	background: 6,
	underline: 7,
	underlineColor: 8,
	features: 9
};

FontAttribute.underline = {
	none: 0,
	single: 1,
	double: 2,
	suggestion: 3
};

FontAttribute.underlineColor = {
	custom: 0,
	spelling: 1,
	grammar: 2,
	auxiliary: 3
};

module.exports = {FontAttribute};

const {FontDescriptor: FontDescriptorC} = require('..');

/**
 * An object that contains information on a system font.
 */
class FontDescriptor {
	/**
	 * Create a new FontDescriptor object.
	 * @return {FontDescriptor}
	 * @param  {string} family - the name of the font, e.g. "Helvetica"
	 * @param  {number} size - size in point of the font
	 * @param  {number} weight - weight of the font
	 * @param  {number} italic - 1 if the font is italic, otherwise 0
	 * @param  {number} stretch - horizontal stretch value for the font
	 * @return {FontDescriptor}
	 */
	constructor(family, size, weight, italic, stretch) {
		if (typeof family === 'object') {
			this.handle = family;
		} else {
			this.handle = FontDescriptorC.create(family, size, weight, italic, stretch);
		}
	}

	/**
	 * Return the name of the font, e.g. "Helvetica".
	 * @return {string}
	 */
	get family() {
		return FontDescriptorC.getFamily(this.handle);
	}

	/**
	 * Return the size in point of the font.
	 * @return {number}
	 */
	get size() {
		return FontDescriptorC.getSize(this.handle);
	}

	/**
	 * Return weight of the font.
	 * @return {number}
	 */
	get weight() {
		return FontDescriptorC.getWeight(this.handle);
	}

	/**
	 * Return 1 if the font is italic, otherwise 0.
	 * @return {number}
	 */
	get italic() {
		return FontDescriptorC.getItalic(this.handle);
	}

	/**
	 * Return horizontal stretch value for the font.
	 * @return {number}
	 */
	get stretch() {
		return FontDescriptorC.getStretch(this.handle);
	}
}

module.exports = {FontDescriptor};

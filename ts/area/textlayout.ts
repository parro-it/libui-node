const {DrawTextLayout: DrawTextLayoutC} = require('../..');
const {FontDescriptor} = require('../font-descriptor');
const {AttributedString} = require('../font-string');

class DrawTextLayout {
	constructor(str, font, width, align) {
		if (!(str instanceof AttributedString)) {
			throw new TypeError(
				'The \'str\' argument has to be a AttributedString object');
		}
		if (!(font instanceof FontDescriptor)) {
			throw new TypeError(
				'The \'font\' argument has to be a FontDescriptor object');
		}
		this.handle = DrawTextLayoutC.create(str.handle, font.handle, width, align);
	}

	get extents() {
		return DrawTextLayoutC.getExtents(this.handle);
	}
}

DrawTextLayout.align = {
	left: 0,
	center: 1,
	right: 2
};

module.exports = DrawTextLayout;
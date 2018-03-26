'use strict';
/* eslint-disable unicorn/number-literal-case */
const libui = require('..');

const {UiFontAttribute} = libui;

let textDrawArea;
let fontButton;
let align;

const str = new libui.UiAttributedString(
	'Drawing strings with libui is done with the uiAttributedString and uiDrawTextLayout objects.\n' +
	'uiAttributedString lets you have a variety of attributes: ');

str.appendAttributed('font family', UiFontAttribute.newFamily('Courier New'));
str.appendUnattributed(', ');

str.appendAttributed('font size', UiFontAttribute.newSize(18));
str.appendUnattributed(', ');

str.appendAttributed('font weight', UiFontAttribute.newWeight(libui.textWeight.bold));
str.appendUnattributed(', ');

str.appendAttributed('font italicness', UiFontAttribute.newItalic(libui.textItalic.italic));
str.appendUnattributed(', ');

str.appendAttributed('font stretch', UiFontAttribute.newStretch(libui.textStretch.condensed));
str.appendUnattributed(', ');

str.appendAttributed('text color', UiFontAttribute.newColor(new libui.Color(0.75, 0.25, 0.5, 0.75)));
str.appendUnattributed(', ');

str.appendAttributed('text background color', UiFontAttribute.newBackground(new libui.Color(0.5, 0.5, 0.25, 0.5)));
str.appendUnattributed(', ');

str.appendAttributed('underline style', UiFontAttribute.newUnderline(libui.textUnderline.single));
str.appendUnattributed(', ');

str.appendUnattributed('and ');
str.appendAttributed2('underline color',
					UiFontAttribute.newUnderline(libui.textUnderline.double),
					UiFontAttribute.newUnderlineColor(libui.textUnderlineColor.custom, new libui.Color(1.0, 0.0, 0.5, 1.0)));
str.appendUnattributed('. ');

str.appendUnattributed('Furthermore, there are attributes allowing for ');
str.appendAttributed2('special underlines for indicating spelling errors',
					UiFontAttribute.newUnderline(libui.textUnderline.suggestion),
					UiFontAttribute.newUnderlineColor(libui.textUnderlineColor.spelling, new libui.Color(0, 0, 0, 0)));
str.appendUnattributed(' (and ');
str.appendAttributed2('other types of errors',
					UiFontAttribute.newUnderline(libui.textUnderline.suggestion),
					UiFontAttribute.newUnderlineColor(libui.textUnderlineColor.grammar, new libui.Color(0, 0, 0, 0)));
str.appendUnattributed(') ');

str.appendUnattributed('and control over OpenType features such as ligatures (with a suitable font - for instance, ');

const otf = new libui.UiOpenTypeFeatures();
otf.add('liga', 0);
str.appendAttributed('affix', UiFontAttribute.newOTFeatures(otf));
str.appendUnattributed(' vs. ');

otf.add('liga', 1);
str.appendAttributed('affix', UiFontAttribute.newOTFeatures(otf));

otf.forEach((feat, str, val) => {
	console.log({feat, str, val});
});

otf.free();
str.appendUnattributed(').\n');

str.appendUnattributed('Use the controls opposite to the text to control properties of the text.');

str.forEach((str, attr, start, end) => {
	console.log({str, attr, start, end});
});

function handlerDraw(area, p) {
	const font = fontButton.getFont();

	const layout = new libui.DrawTextLayout(str, font, p.getAreaWidth(), align.getSelected());

	p.getContext().text(0, 0, layout);

	layout.free();
	font.free();
}

function noop() {}

function redraw() {
	textDrawArea.queueRedrawAll();
}

function main() {
	const mainwin = new libui.UiWindow('libui textDrawArea Example', 640, 480, 1);
	mainwin.margined = true;
	mainwin.onClosing(() => {
		libui.stopLoop();
	});

	const hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	const vbox = new libui.UiVerticalBox();
	vbox.padded = true;
	hbox.append(vbox, false);

	fontButton = new libui.UiFontButton();
	fontButton.onChanged(redraw);
	vbox.append(fontButton, false);

	const form = new libui.UiForm();
	form.padded = true;
	vbox.append(form, false);

	align = new libui.UiCombobox();
	// Note that the items match with the values of the uiDrawTextAlign values
	align.append('Left');
	align.append('Center');
	align.append('Right');
	align.setSelected(0);
	align.onSelected(redraw);
	form.append('Alignment', align, false);

	textDrawArea = new libui.UiArea(handlerDraw, noop, noop, noop, noop);
	hbox.append(textDrawArea, true);

	mainwin.show();

	libui.startLoop();
}

main();

/* eslint-disable unicorn/filename-case */

const libui = require('..');
const mnu = new libui.UiMenu('mnu');
const mnuItem = mnu.appendItem('click me');
mnuItem.onClicked(() => {
	console.log(`menu clicked ${mnuItem}`);
});

function createWindow() {
	const win = new libui.UiWindow('UiSpinbox example', 320, 60, true);

	win.margined = true;

	const widget1 = new libui.UiSpinbox();
	widget1.value = 42;
	widget1.onChanged(() => {
		console.log(`widget1 changed to ${widget1.value}`);
	});

	const widget2 = new libui.UiButton('btn1');
	widget2.onClicked(() => {
		widget6.setEnabled(false);
		console.log(`${widget2.text} clicked`);
	});

	const widget3 = new libui.UiCheckbox('chk1');
	widget3.onToggled(() => {
		console.log(`${widget3.text} toggled`);
	});

	const widget4 = new libui.UiColorButton();
	widget4.onChanged(() => {
		console.log(`widget4 changed to ${widget4.color}`);
	});

	const widget5 = new libui.UiCombobox();
	widget5.append('a');
	widget5.append('b');
	widget5.onSelected(() => {
		console.log(`widget5 changed to ${widget5.selected}`);
	});

	const widget6 = new libui.UiEditableCombobox();
	widget6.append('sally');
	widget6.append('tati');
	widget6.append('parro');
	widget6.onChanged(() => {
		console.log(`widget6 changed to ${widget6.text}`);
	});

	const widget7 = new libui.UiSearchEntry();
	widget7.onChanged(() => {
		console.log(`${widget7.text} changed`);
	});

	const widget8 = new libui.UiPasswordEntry();
	widget8.onChanged(() => {
		console.log(`${widget8.text} changed`);
	});

	const widget9 = new libui.UiEntry();
	widget9.onChanged(() => {
		console.log(`${widget9.text} changed`);
	});

	const widget10 = new libui.UiFontButton();
	widget10.onChanged(() => {
		console.log(`${widget10.text} changed`);
	});

	const widget11 = new libui.UiMultilineEntry();
	widget11.onChanged(() => {
		console.log(`${widget11.text} changed`);
	});

	const widget12 = new libui.UiRadioButtons();
	widget12.append('a');
	widget12.append('b');
	widget12.onSelected(() => {
		console.log(`widget12 changed to ${widget12.selected}`);
	});

	const widget13 = new libui.UiSlider();
	widget13.onChanged(() => {
		console.log(`widget13 changed to ${widget13.value}`);
	});

	const box = new libui.UiVerticalBox();
	box.append(widget1, true);
	box.append(widget2, true);
	box.append(widget3, true);
	box.append(widget4, true);
	box.append(widget5, true);
	box.append(widget6, true);
	box.append(widget7, true);
	box.append(widget8, true);

	const box2 = new libui.UiVerticalBox();
	box2.append(widget9, true);
	box2.append(widget10, true);
	box2.append(widget11, true);
	box2.append(widget12, true);
	box2.append(widget13, true);

	const widget14 = new libui.UiGroup();
	widget14.child = new libui.UiEntry();

	const widget15 = new libui.UiTab();
	widget15.append('xxx', new libui.UiEntry());
	widget15.append('yyy', new libui.UiEntry());

	const widget16 = new libui.UiForm();
	widget16.append('xxx', new libui.UiEntry(), true);
	widget16.append('yyy', new libui.UiEntry(), true);

	box2.append(widget14, true);
	box2.append(widget15, true);
	box2.append(widget16, true);

	const horz = new libui.UiHorizontalBox();
	horz.append(box, true);
	horz.append(box2, true);

	win.setChild(horz);

	win.onClosing(() => {
		win.close();
		global.gc();
		libui.stopLoop();
	});

	return win;
}

function op() {
	global.gc();
	const win = createWindow();
	win.show();
	setTimeout(() => {
		win.close();
		op();
	}, 100);
}

libui.startLoop();
op();

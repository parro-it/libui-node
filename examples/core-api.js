'use strict';
const os = require('os');
const http = require('http');
const libui = require('..');

const win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

const box = new libui.UiVerticalBox();
const hBox = new libui.UiHorizontalBox();
const e1 = new libui.UiEntry();
e1.enabled = 0;
const lblCiao = new libui.UiLabel('ciao');
hBox.append(lblCiao, false);

hBox.append(e1, false);
let idxLbl = 0;

const interval = setInterval(() => {
	lblCiao.text = String(idxLbl++);
}, 1000);

// Create an HTTP tunneling proxy
const proxy = http.createServer((req, res) => {
	lblCiao.text = String(idxLbl++);
	res.writeHead(200, {'Content-Type': 'text/plain'});
	res.end(String(idxLbl));
});
proxy.listen(3000, '127.0.0.1', () => {
	console.log('listening...');
});

win.onClosing(() => {
	win.close();
	clearInterval(interval);
	proxy.close();
	libui.stopLoop();
});

box.append(new libui.UiEntry(), false);
box.append(hBox, false);

if (os.platform() !== 'darwin') {
	box.append(new libui.UiSearchEntry(), false);
}

box.append(new libui.UiPasswordEntry(), false);

const cmb = new libui.UiCombobox();

cmb.append('item 1');
cmb.append('item 2');
cmb.append('item 3');

box.append(cmb, false);
const hBox4 = new libui.UiHorizontalBox();
hBox4.append(new libui.UiDateTimePicker(), false);
hBox4.append(new libui.UiVerticalSeparator(), false);
hBox4.append(new libui.UiEditableCombobox(), false);
hBox4.append(new libui.UiCheckbox('Optionally'), false);

box.append(hBox4, false);

const group = new libui.UiGroup('Options');
const radios = new libui.UiRadioButtons();
radios.append('option 1');
radios.append('option 2');
radios.append('option 3');

group.setChild(radios);
box.append(group, true);

box.append(new libui.UiHorizontalSeparator(), true);

const hBox2 = new libui.UiHorizontalBox();
const spin = new libui.UiSpinbox(0, 100);
spin.value = 33;
hBox2.append(new libui.UiLabel('Number'), false);
hBox2.append(spin, true);
box.append(hBox2, false);

const hBox3 = new libui.UiHorizontalBox();
const slider = new libui.UiSlider(0, 100);
slider.value = 33;
hBox3.append(new libui.UiLabel('Number'), false);
hBox3.append(slider, false);
box.append(hBox3, false);

box.append(new libui.UiMultilineEntry(), false);

const buttons = new libui.UiHorizontalBox();
buttons.append(new libui.UiButton('Ok'), false);
buttons.append(new libui.UiButton('Maybe'), false);
buttons.append(new libui.UiButton('Cancel'), false);

box.append(new libui.UiProgressBar(), false);
box.append(new libui.UiFontButton(), false);

box.append(buttons, false);

const tabs = new libui.UiTab();

tabs.append('controls', box);
tabs.append('text', new libui.UiMultilineEntry());

win.setChild(tabs);

win.show();
libui.startLoop();

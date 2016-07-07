var os = require('os');
var libui = require('../index.js');

libui.Ui.init();
var win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

var box = new libui.UiVerticalBox();
var hBox = new libui.UiHorizontalBox();
var e1 = new libui.UiEntry();
e1.enabled = 0;
hBox.append(new libui.UiLabel('ciao'), false);
hBox.append(e1, false);

box.append(new libui.UiEntry(), false);
box.append(hBox, false);

if (os.platform() !== 'darwin') {
	box.append(new libui.UiSearchEntry(), false);
}

box.append(new libui.UiPasswordEntry(), false);

var cmb = new libui.UiCombobox();

cmb.append('item 1');
cmb.append('item 2');
cmb.append('item 3');

box.append(cmb, false);
var hBox4 = new libui.UiHorizontalBox();
hBox4.append(new libui.UiDateTimePicker(), false);
hBox4.append(new libui.UiVerticalSeparator(), false);
hBox4.append(new libui.UiEditableCombobox(), false);
hBox4.append(new libui.UiCheckbox('Optionally'), false);

box.append(hBox4, false);

var group = new libui.UiGroup('Options');
var radios = new libui.UiRadioButtons();
radios.append('option 1');
radios.append('option 2');
radios.append('option 3');

group.setChild(radios);
box.append(group, true);

box.append(new libui.UiHorizontalSeparator(), true);

var hBox2 = new libui.UiHorizontalBox();
var spin = new libui.UiSpinbox(0, 100);
spin.value = 33;
hBox2.append(new libui.UiLabel('Number'), false);
hBox2.append(spin, true);
box.append(hBox2, false);

var hBox3 = new libui.UiHorizontalBox();
var slider = new libui.UiSlider(0, 100);
slider.value = 33;
hBox3.append(new libui.UiLabel('Number'), false);
hBox3.append(slider, false);
box.append(hBox3, false);

box.append(new libui.UiMultilineEntry(), false);

var buttons = new libui.UiHorizontalBox();
buttons.append(new libui.UiButton('Ok'), false);
buttons.append(new libui.UiButton('Maybe'), false);
buttons.append(new libui.UiButton('Cancel'), false);

box.append(new libui.UiProgressBar(), false);
box.append(new libui.UiFontButton(), false);

box.append(buttons, false);

var tabs = new libui.UiTab();

tabs.append('controls', box);
tabs.append('text', new libui.UiMultilineEntry());

win.setChild(tabs);
win.show();
libui.startLoop();

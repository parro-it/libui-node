var os = require('os');
var libui = require('../index.js');

libui.Ui.init();
var win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

var box = new libui.UiVerticalBox();
var hBox = new libui.UiHorizontalBox();
var e1 = new libui.UiEntry();
e1.enabled = 0;
hBox.append(new libui.UiLabel('ciao'), 0);
hBox.append(e1, 1);

box.append(new libui.UiEntry(), 1);
box.append(hBox, 0);

if (os.platform() !== 'darwin') {
	box.append(new libui.UiSearchEntry(), 0);
}

box.append(new libui.UiPasswordEntry(), 0);

var cmb = new libui.UiCombobox();

cmb.append('item 1');
cmb.append('item 2');
cmb.append('item 3');

box.append(cmb, 0);
box.append(new libui.UiDateTimePicker(), 1);
box.append(new libui.UiEditableCombobox(), 1);
box.append(new libui.UiCheckbox('Optionally'), 1);

var group = new libui.UiGroup('Options');
var radios = new libui.UiRadioButtons();
radios.append('option 1');
radios.append('option 2');
radios.append('option 3');

group.setChild(radios);
box.append(group, 1);

box.append(new libui.UiSeparator(), 1);

var hBox2 = new libui.UiHorizontalBox();
var spin = new libui.UiSpinbox(0, 100);
spin.value = 33;
hBox2.append(new libui.UiLabel('Number'), 0);
hBox2.append(spin, 1);
box.append(hBox2, 0);

var hBox3 = new libui.UiHorizontalBox();
var slider = new libui.UiSlider(0, 100);
slider.value = 33;
hBox3.append(new libui.UiLabel('Number'), 0);
hBox3.append(slider, 1);
box.append(hBox3, 0);

box.append(new libui.UiMultilineEntry(), 0);

var buttons = new libui.UiHorizontalBox();
buttons.append(new libui.UiButton('Ok'), 0);
buttons.append(new libui.UiButton('Maybe'), 0);
buttons.append(new libui.UiButton('Cancel'), 0);

box.append(new libui.UiProgressBar(), 0);

box.append(buttons, 0);

var tabs = new libui.UiTab();

tabs.append('controls', box);
tabs.append('text', new libui.UiMultilineEntry());

win.setChild(tabs);
win.show();
libui.Ui.main();

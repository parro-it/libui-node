const libui = require('.');
libui.Ui.init();
const win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

const box = new libui.UiVerticalBox();
const hBox = new libui.UiHorizontalBox();
const e1 = new libui.UiEntry();
e1.enabled = 0;
hBox.append(new libui.UiLabel('ciao'), 0);
hBox.append(e1, 1);

box.append(new libui.UiEntry(), 1);
box.append(hBox, 0);
box.append(new libui.UiEntry(), 0);

box.append(new libui.UiCombobox(), 1);
box.append(new libui.UiEditableCombobox(), 1);
box.append(new libui.UiCheckbox('Optionally'), 1);

box.append(new libui.UiSeparator(), 1);

const hBox2 = new libui.UiHorizontalBox();
const spin = new libui.UiSpinbox(0, 100);
spin.value = 33;
hBox2.append(new libui.UiLabel('Number'), 0);
hBox2.append(spin, 1);
box.append(hBox2, 0);

const hBox3 = new libui.UiHorizontalBox();
const slider = new libui.UiSlider(0, 100);
slider.value = 33;
hBox3.append(new libui.UiLabel('Number'), 0);
hBox3.append(slider, 1);
box.append(hBox3, 0);

const buttons = new libui.UiHorizontalBox();
buttons.append(new libui.UiButton('Ok'), 0);
buttons.append(new libui.UiButton('Maybe'), 0);
buttons.append(new libui.UiButton('Cancel'), 0);

box.append(new libui.UiProgressBar(), 0);

box.append(buttons, 0);

win.setChild(box);
win.show();
libui.Ui.main();


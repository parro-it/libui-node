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

const buttons = new libui.UiHorizontalBox();
buttons.append(new libui.UiButton('Ok'), 0);
buttons.append(new libui.UiButton('Maybe'), 0);
buttons.append(new libui.UiButton('Cancel'), 0);
box.append(buttons, 0);

win.setChild(box);
win.show();
libui.Ui.main();


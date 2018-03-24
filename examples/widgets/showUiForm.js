/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiForm example', 320, 60, true);
win.margined = true;

const widget = new libui.UiForm();
widget.padded = true;
widget.append('name', new libui.UiEntry(), false);
widget.append('surname', new libui.UiEntry(), false);
widget.append('age', new libui.UiEntry(), false);
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

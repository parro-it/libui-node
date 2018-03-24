/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiCheckbox example', 320, 60, true);
win.margined = true;

const widget = new libui.UiCheckbox();
widget.text = 'sample text';
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiProgressBar example', 320, 60, true);
win.margined = true;

const widget = new libui.UiProgressBar();
widget.value = 50;
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

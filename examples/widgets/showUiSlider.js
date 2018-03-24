/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiSlider example', 320, 60, true);
win.margined = true;

const widget = new libui.UiSlider();
widget.value = 50;

const cnt = new libui.UiVerticalBox();
cnt.padded = true;
cnt.append(widget, false);

win.setChild(cnt);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiHorizontalBox example', 320, 60, true);
win.margined = true;

const widget = new libui.UiHorizontalBox();
widget.padded = true;
widget.append(new libui.UiMultilineEntry(), false);
widget.append(new libui.UiMultilineEntry(), false);
widget.append(new libui.UiMultilineEntry(), false);
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

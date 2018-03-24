/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiVerticalSeparator example', 320, 60, true);
win.margined = true;

const widget = new libui.UiHorizontalBox();
widget.padded = true;
widget.append(new libui.UiMultilineEntry(), true);
widget.append(new libui.UiVerticalSeparator(), false);
widget.append(new libui.UiMultilineEntry(), true);
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

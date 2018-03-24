/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiHorizontalSeparator example', 320, 60, true);
win.margined = true;

const widget = new libui.UiVerticalBox();
widget.padded = true;
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiHorizontalSeparator(), false);
widget.append(new libui.UiEntry(), false);
win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

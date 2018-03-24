/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiEditableCombobox example', 320, 60, true);
win.margined = true;

const widget = new libui.UiEditableCombobox();

widget.append('Item1');
widget.append('Item2');
widget.append('Item3');

win.setChild(widget);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();

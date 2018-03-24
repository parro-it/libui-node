/* eslint-disable unicorn/filename-case */

const libui = require('../..');

const win = new libui.UiWindow('UiGroup example', 320, 60, true);
win.margined = true;

const widget = new libui.UiVerticalBox();
widget.padded = true;
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);

const group = new libui.UiGroup();
group.margined = true;
group.title = 'A group of entries';
group.setChild(widget);

win.setChild(group);

win.onClosing(() => {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();


var libui = require('../../index');

libui.Ui.init();
var win = new libui.UiWindow('UiGroup example', 320, 60, true);
win.margined = true;

var widget = new libui.UiVerticalBox();
widget.padded = true;
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);
widget.append(new libui.UiEntry(), false);

var group = new libui.UiGroup();
group.margined = true;
group.title = 'A group of entries';
group.setChild(widget);

win.setChild(group);

win.onClosing(function () {
	win.close();
	libui.Ui.quit();
});

win.show();

libui.Ui.main();


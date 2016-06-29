var libui = require('../index.js');

libui.Ui.init();

var win = new libui.UiWindow("Example window", 640, 480, true);
win.borderless = true;
var box = new libui.UiVerticalBox();
var entry = new libui.UiMultilineEntry();
entry.text = 'This is some text';

box.append(entry, 1);

win.setChild(box);

win.onClosing(function () {
	libui.stopLoop();
});

win.show();

libui.startLoop();

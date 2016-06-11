const libui = require('../index.js');
libui.Ui.init();
const win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

const box = new libui.UiVerticalBox();
const entry = new libui.UiMultilineEntry();
const status = new libui.UiLabel('status 1');
const btnQuit = new libui.UiButton('Quit');

win.onClosing(() => {
	libui.stopLoop();
});

entry.onChanged(() => {
	status.text = entry.text;
});

btnQuit.onClicked(() => {
	libui.stopLoop();
});

box.append(entry, 1);
box.append(btnQuit, 0);
box.append(status, 0);

win.setChild(box);
win.show();
libui.startLoop();

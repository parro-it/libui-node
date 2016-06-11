const libui = require('../index.js');
libui.Ui.init();
const win = new libui.UiWindow('Test window', 800, 600, false);
win.margined = 1;

const box = new libui.UiVerticalBox();
const entry = new libui.UiEntry();
const status1 = new libui.UiLabel('status 1');
const status2 = new libui.UiLabel('status 2');
const btnQuit = new libui.UiButton('Quit');

entry.onChange(() => {
	status1.text = entry.text;
});

entry.onChange(() => {
	status2.text = entry.text;
});

btnQuit.onClicked(() => {
	libui.stopLoop();
});

box.append(entry, 1);
box.append(btnQuit, 0);
box.append(status1, 0);
box.append(status2, 0);

win.setChild(box);
win.show();
libui.startLoop();

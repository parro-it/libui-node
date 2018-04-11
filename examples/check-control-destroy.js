/* eslint-disable unicorn/filename-case */

const libui = require('..');
function createWindow() {
	const win = new libui.UiWindow('UiSpinbox example', 320, 60, true);

	win.margined = true;

	const widget = new libui.UiSpinbox();
	widget.value = 42;
	widget.onChanged(() => {
		console.log(`value changed to ${widget.value}`);
	});
	win.setChild(widget);

	win.onClosing(() => {
		win.close();
		global.gc();
		libui.stopLoop();
	});

	return win;
}

const win = createWindow();
win.show();
global.gc();

libui.startLoop();

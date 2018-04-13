/* eslint-disable unicorn/filename-case */

const libui = require('..');
function createWindow() {
	const win = new libui.UiWindow('UiSpinbox example', 320, 60, true);

	win.margined = true;

	const widget1 = new libui.UiSpinbox();
	widget1.value = 42;
	widget1.onChanged(() => {
		console.log(`value1 changed to $ {widget1.value}`);
	});

	const widget2 = new libui.UiButton('btn1');
	widget2.onClicked(() => {
		console.log(`${widget2.text} clicked`);
	});

	const box = new libui.UiVerticalBox();
	box.append(widget1, true);
	box.append(widget2, true);

	win.setChild(box);

	win.onClosing(() => {
		win.close();
		global.gc();
		libui.stopLoop();
	});

	return win;
}

function op() {
	global.gc();
	const win = createWindow();
	win.show();
	setTimeout(() => {
		win.close();
		op();
	}, 100);
}

libui.startLoop();
op();

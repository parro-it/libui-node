const libui = require('..');

const {UiWindow, UiHorizontalBox, UiMultilineEntry} = libui;

libui.onShouldQuit(() => {
	libui.stopLoop();
	global.gc();
});

function createWindow() {
	let win = new UiWindow('Test Window', 800, 600, false);
	win.margined = true;
	const logEntry = new UiMultilineEntry();

	const entry = new UiMultilineEntry();
	entry.text = 'A test line\n';
	entry.append('A second test line\n');
	entry.onChanged(() => {
		const msg = `Text changed to ${entry.text}`;
		console.log(msg);
		logEntry.append(msg + '\n');
	});

	const box = new UiHorizontalBox();
	box.setPadded(true);
	box.append(entry, true);
	box.append(logEntry, true);

	win.setChild(box);

	win.onContentSizeChanged(() => {
		const size = win.getContentSize();
		console.log(`size changed to ${size.width}x${size.height}`);
	});
	let step = 0;
	win.onClosing(() => {
		if (win.getTitle() == 'Test Window') {
			let interval = setInterval(() => {
				if (step === 0) {
					win.contentSize = {width: 400, height: 300};
				}
				if (step === 1) {
					win.margined = true;
				}
				if (step === 2) {
					win.margined = false;
					win.fullscreen = true;
				}
				if (step === 3) {
					win.fullscreen = false;
					win.borderless = true;
				}
				if (step === 4) {
					win.borderless = false;
				}

				if (step > 4) {
					clearInterval(interval);
				}

				step++;

				console.log({
					Margined: win.margined,
					Fullscreen: win.fullscreen,
					Borderless: win.borderless,
				});
			}, 1000);
			box.deleteAt(1);
			return win.title = 'Wait some seconds please...';
		}
		console.log('closing', win.title);
		win.close();
		win = null;
		libui.stopLoop();
	});

	win.show();
}

createWindow();
libui.startLoop();
setInterval(() => {
	global.gc();
}, 10);

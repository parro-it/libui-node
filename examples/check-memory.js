'use strict';
const libui = require('..');
const humanize = require('humanize');
const procStats = require('proc-stats');

function openBigWindow() {
	const win = new libui.UiWindow('Forms window', 80, 60, false);
	win.margined = 1;
	win.onClosing(() => {
		win.close();
	});

	const vBox = new libui.UiVerticalBox();
	vBox.padded = true;

	const entries = [];
	for (let i = 0; i < 300; i++) {
		entries[i] = new libui.UiEntry();
		entries[i].text = i;
		vBox.append(entries[i], 1);
	}

	win.setChild(vBox);
	win.show();
}

const winCheckMem = new libui.UiWindow('Memory', 200, 100, true);
const label = new libui.UiLabel();
const btn = new libui.UiButton();
btn.text = 'Open';
btn.onClicked(openBigWindow);
const vBox2 = new libui.UiVerticalBox();
vBox2.padded = true;

vBox2.append(label, true);
vBox2.append(btn, false);

winCheckMem.setChild(vBox2);
winCheckMem.show();

const interval = setInterval(() => {
	procStats.stats((err, result) => {
		if (err) {
			label.text = err.message;
		} else {
			const text = `
Memory: ${humanize.filesize(result.memory)}
Heap: ${humanize.filesize(result.memoryInfo.heapUsed)}
CPU: ${result.cpu} %
`;
			label.text = text;
		}
	});
}, 1000);

winCheckMem.onClosing(() => {
	clearInterval(interval);
	libui.stopLoop();
});

libui.startLoop();

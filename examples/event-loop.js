'use strict';
const libui = require('..');

let setIntervalHandle = null;
let lastTimeout = 0;
let setIntervalLast = Date.now();

const win = new libui.UiWindow('Event loop tests', 800, 600, false);
win.margined = 1;

const box = new libui.UiVerticalBox();
box.padded = true;
win.setChild(box);

const setIntervalMs = new libui.UiSlider(0, 1000);
setIntervalMs.onChanged(setIntervalChanged);
setIntervalMs.value = 0;

const form = new libui.UiForm();
form.padded = true;
form.append('setInterval', setIntervalMs, 0);
form.append('actions', makeToolbar(), 0);
box.append(form, true);

const log = new libui.UiMultilineEntry();
box.append(log, true);

win.onClosing(() => {
	if (setIntervalHandle !== null) {
		clearInterval(setIntervalHandle);
		setIntervalHandle = null;
	}
	win.close();
	libui.stopLoop();
});

win.show();
libui.startLoop();

function logAppend(line) {
	const lines = log.text.split('\n');
	if (lines.length > 20) {
		log.text = lines.slice(1).join('\n');
	}
	log.append(line + '\n');
}

function setIntervalChanged() {
	const ms = setIntervalMs.value;
	if (Math.abs(ms - lastTimeout) < 100) {
		return;
	}
	lastTimeout = ms;
	if (setIntervalHandle !== null) {
		clearInterval(setIntervalHandle);
		setIntervalHandle = null;
	}

	if (ms > 0) {
		setIntervalHandle = setInterval(() => {
			const now = Date.now();
			const elapsed = now - setIntervalLast;
			logAppend(`setInterval:${now} - elapsed ${elapsed} ms`);
			setIntervalLast = now;
		}, ms);
	}
}

function makeToolbar() {
	const toolbar = new libui.UiHorizontalBox();
	toolbar.padded = true;

	const btnSetImmediate = new libui.UiButton('setImmediate');
	btnSetImmediate.onClicked(() => {
		const now = Date.now();
		setImmediate(() => {
			const elapsed = Date.now() - now;
			logAppend(`setImmediate:${now} - elapsed ${elapsed} ms`);
		});
	});

	toolbar.append(btnSetImmediate, false);

	const btnPromise = new libui.UiButton('Promise');
	btnPromise.onClicked(() => {
		const now = Date.now();

		Promise.resolve(true).then(() => {
			const elapsed = Date.now() - now;
			logAppend(`Promise: ${now} - elapsed ${elapsed} ms`);
		});
	});

	toolbar.append(btnPromise, false);

	const btnNextTick = new libui.UiButton('NextTick');
	btnNextTick.onClicked(() => {
		const now = Date.now();
		process.nextTick(() => {
			const elapsed = Date.now() - now;
			logAppend(`nextTick:${now} - elapsed ${elapsed} ms`);
		});
	});

	toolbar.append(btnNextTick, false);

	const btnReadFile = new libui.UiButton('ReadFile');
	btnReadFile.onClicked(() => {
		const {createReadStream} = require('fs');
		const stream = createReadStream('/tmp/big');
		let i = 0;
		stream.on('data', data => {
			logAppend(`ReadFile: chunk ${i++} - ` + data.length);
		});
	});

	const btnHttp = new libui.UiButton('Http');
	btnHttp.onClicked(() => {
		const http = require('http');
		let i = 0;

		const server = http.createServer((req, res) => {
			res.writeHead(200, {'Content-Type': 'text/plain'});
			logAppend(`Http: request ${i}`);
			res.end(String(i++));
		});

		server.listen(3000, '127.0.0.1', () => {
			logAppend('listening...');
		});
	});

	toolbar.append(btnHttp, false);

	return toolbar;
}

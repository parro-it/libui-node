import test from 'ava';
import libui from './index';

test('new UiWindow - throw if too few arguments', t => {
	const err = t.throws(() => new libui.UiWindow('Test window'));
	t.true(err instanceof Error);
	t.is(err.message, 'Wrong number of arguments');
});

test('setting Entry text emit onChange', async (t) => {
	libui.Ui.init();
	let emitted;

	const entry = new libui.UiEntry();
	entry.onChange(() => {
		emitted = true;
		libui.stopLoop();
	});

	const win = new libui.UiWindow('Test window', 800, 600, false);
	win.setChild(entry);
	win.show();

	const loopRunning = libui.startLoop();
	entry.text = 'changed';
	await loopRunning;
	t.true(emitted);
});

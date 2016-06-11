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

	libui.startLoop();
	entry.text = 'changed';
	t.true(emitted);
});

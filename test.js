import test from 'ava';
import libui from './index';

/*

test('newWindow - throw if too few arguments', t => {
	libui.Ui.init();
	const err = t.throws(() => new libui.UiWindow('Test window'));
	t.true(err instanceof Error);
	t.is(err.message, 'Wrong number of arguments');
});

test.skip('newWindow - throw if width is not a number', t => {
	const err = t.throws(() => new libui.UiWindow('Test window', 'some text', 600, true));
	t.true(err instanceof Error);
	t.is(err.message, 'width should be a number');
});
*/

test('newWindow - throw if too few arguments', t => {
	libui.Ui.init();
	let emitted;
	const entry = new libui.UiEntry();
	entry.onChange(() => {
		emitted = true;
	});
	entry.text = 'some value';
	t.true(emitted);
});

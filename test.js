import test from 'ava';
import libui from '.';

test('newWindow - throw if too few arguments', t => {
	const err = t.throws(() => libui.newWindow('Test window', 800, 600));
	t.true(err instanceof TypeError);
	t.is(err.message, 'Too few arguments, expected 4');
});

test('controlShow - throw if too few arguments', t => {
	const err = t.throws(() => libui.controlShow());
	t.true(err instanceof TypeError);
	t.is(err.message, 'Too few arguments, expected 1');
});

test('newWindow - throw if width is not a number', t => {
	const err = t.throws(() => libui.newWindow('Test window', '', 600, true));
	t.true(err instanceof TypeError);
	t.is(err.message, 'width should be a number');
});

test('newWindow - throw if height is not a number', t => {
	const err = t.throws(() => libui.newWindow('Test window', 600, '', true));
	t.true(err instanceof TypeError);
	t.is(err.message, 'height should be a number');
});

test('newWindow - throw if title is not a string', t => {
	const err = t.throws(() => libui.newWindow(true, 600, 400, true));
	t.true(err instanceof TypeError);
	t.is(err.message, 'title should be a string');
});

test('newWindow - throw if hasMenubar is not a boolean', t => {
	const err = t.throws(() => libui.newWindow('Test window', 600, 400, 0));
	t.true(err instanceof TypeError);
	t.is(err.message, 'hasMenubar should be a boolean');
});

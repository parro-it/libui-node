import test from 'ava';
import libuiNode from './';

test('it work!', t => {
	const result = libuiNode();
	t.is(result, 42);
});

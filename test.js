import test from 'ava';
import libui from './index';

libui.Ui.init();

test('new UiWindow - throw if too few arguments', t => {
	const err = t.throws(() => new libui.UiWindow('Test window'));
	t.true(err instanceof Error);
	t.is(err.message, 'Wrong number of arguments');
});

test.before(() => {
	libui.startLoop();
});

test.after(() => {
	// libui.stopLoop();
});

function checkEvent(Class, eventName, propertyName, propertyType, builder = () => new Class()) {
	return [`Widget ${Class.name} has event ${eventName}`, t => {
		let emitted = false;

		const widget = builder();
		widget[eventName](() => {
			emitted = true;
		});

		if (propertyType === Boolean) {
			widget[propertyName] = true;
		} else if (propertyType === String) {
			widget[propertyName] = 'some value';
		} else if (propertyType === Number) {
			widget[propertyName] = 2;
		} else if (propertyType === libui.Color) {
			widget[propertyName] = new libui.Color(1, 2, 3, 0.4);
		}
		t.true(emitted);
	}];
}

function checkProperty(Class, propertyName, type, builder = () => new Class()) {
	return [`Widget ${Class.name} has property ${propertyName}`, t => {
		const widget = builder();
		const setterName = 'set' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const getterName = 'get' + propertyName[0].toUpperCase() + propertyName.slice(1);
		const setter = widget[setterName].bind(widget);
		const getter = widget[getterName].bind(widget);
		t.true(typeof getter === 'function');
		t.true(typeof setter === 'function');

		if (type === Boolean) {
			setter(true);
			t.true(getter());
			t.true(widget[propertyName]);

			setter(false);
			t.false(getter());
			t.false(widget[propertyName]);

			widget[propertyName] = true;
			t.true(getter());

			widget[propertyName] = false;
			t.false(getter());
		}

		if (type === String) {
			setter('some value');
			t.is(widget[propertyName], 'some value');
			t.is(getter(), 'some value');

			setter('');
			t.is(getter(), '');
			t.is(widget[propertyName], '');

			widget[propertyName] = 'some value';
			t.is(getter(), 'some value');

			widget[propertyName] = '';
			setter('');
			t.is(getter(), '');
		}

		if (type === libui.Color) {
			setter(new libui.Color(1, 2, 3, 0.4));
			const c1 = widget[propertyName];
			t.is(c1.r, 1);
			t.is(c1.g, 2);
			t.is(c1.b, 3);
			t.is(c1.a, 0.4);
			const c2 = getter();
			t.is(c2.r, 1);
			t.is(c2.g, 2);
			t.is(c2.b, 3);
			t.is(c2.a, 0.4);

			setter(new libui.Color(3, 1, 2, 0.5));
			const c3 = widget[propertyName];
			t.is(c3.r, 3);
			t.is(c3.g, 1);
			t.is(c3.b, 2);
			t.is(c3.a, 0.5);
			const c4 = getter();
			t.is(c4.r, 3);
			t.is(c4.g, 1);
			t.is(c4.b, 2);
			t.is(c4.a, 0.5);

			widget[propertyName] = new libui.Color(1, 2, 3, 0.4);
			const c5 = widget[propertyName];
			t.is(c5.r, 1);
			t.is(c5.g, 2);
			t.is(c5.b, 3);
			t.is(c5.a, 0.4);
			const c6 = getter();
			t.is(c6.r, 1);
			t.is(c6.g, 2);
			t.is(c6.b, 3);
			t.is(c6.a, 0.4);

			widget[propertyName] = new libui.Color(3, 1, 2, 0.5);
			const c7 = widget[propertyName];
			t.is(c7.r, 3);
			t.is(c7.g, 1);
			t.is(c7.b, 2);
			t.is(c7.a, 0.5);
			const c8 = getter();
			t.is(c8.r, 3);
			t.is(c8.g, 1);
			t.is(c8.b, 2);
			t.is(c8.a, 0.5);
		}

		if (type === Number) {
			setter(2);
			t.is(getter(), 2);
			t.is(widget[propertyName], 2);

			setter(0);
			t.is(getter(), 0);
			t.is(widget[propertyName], 0);

			widget[propertyName] = 2;
			t.is(getter(), 2);

			widget[propertyName] = 0;
			t.is(getter(), 0);
		}
	}];
}

/* eslint-disable ava/test-title */
/* eslint-disable ava/no-identical-title */

test(...checkProperty(libui.UiForm, 'visible', Boolean));
test(...checkProperty(libui.UiForm, 'enabled', Boolean));
test(...checkProperty(libui.UiForm, 'padded', Boolean));

test(...checkProperty(libui.UiGrid, 'visible', Boolean));
test(...checkProperty(libui.UiGrid, 'enabled', Boolean));
test(...checkProperty(libui.UiGrid, 'padded', Boolean));

test(...checkProperty(libui.UiEntry, 'visible', Boolean));
test(...checkProperty(libui.UiEntry, 'enabled', Boolean));
test(...checkProperty(libui.UiEntry, 'readOnly', Boolean));
test(...checkProperty(libui.UiEntry, 'text', String));

test(...checkProperty(libui.UiMultilineEntry, 'visible', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'enabled', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'readOnly', Boolean));
test(...checkProperty(libui.UiMultilineEntry, 'text', String));

test(...checkProperty(libui.UiLabel, 'visible', Boolean));
test(...checkProperty(libui.UiLabel, 'enabled', Boolean));
test(...checkProperty(libui.UiLabel, 'text', String));

test(...checkProperty(libui.UiVerticalSeparator, 'visible', Boolean));
test(...checkProperty(libui.UiVerticalSeparator, 'enabled', Boolean));

test(...checkProperty(libui.UiHorizontalSeparator, 'visible', Boolean));
test(...checkProperty(libui.UiHorizontalSeparator, 'enabled', Boolean));

test(...checkProperty(libui.UiDatePicker, 'visible', Boolean));
test(...checkProperty(libui.UiDatePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiTimePicker, 'visible', Boolean));
test(...checkProperty(libui.UiTimePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiDateTimePicker, 'visible', Boolean));
test(...checkProperty(libui.UiDateTimePicker, 'enabled', Boolean));

test(...checkProperty(libui.UiButton, 'visible', Boolean));
test(...checkProperty(libui.UiButton, 'enabled', Boolean));
test(...checkProperty(libui.UiButton, 'text', String));

test(...checkProperty(libui.UiCheckbox, 'visible', Boolean));
test(...checkProperty(libui.UiCheckbox, 'enabled', Boolean));
test(...checkProperty(libui.UiCheckbox, 'checked', Boolean));
test(...checkProperty(libui.UiCheckbox, 'text', String));

test(...checkProperty(libui.UiSpinbox, 'visible', Boolean));
test(...checkProperty(libui.UiSpinbox, 'enabled', Boolean));
test(...checkProperty(libui.UiSpinbox, 'value', Number));

test(...checkProperty(libui.UiSlider, 'visible', Boolean));
test(...checkProperty(libui.UiSlider, 'enabled', Boolean));
test(...checkProperty(libui.UiSlider, 'value', Number));

test(...checkProperty(libui.UiProgressBar, 'visible', Boolean));
test(...checkProperty(libui.UiProgressBar, 'enabled', Boolean));
test(...checkProperty(libui.UiProgressBar, 'value', Number));

const comboBuilder = () => {
	const cmb = new libui.UiCombobox();
	cmb.append('1');
	cmb.append('2');
	cmb.append('3');
	return cmb;
};

const radioBuilder = () => {
	const cmb = new libui.UiRadioButtons();
	cmb.append('1');
	cmb.append('2');
	cmb.append('3');
	return cmb;
};

test(...checkProperty(libui.UiCombobox, 'visible', Boolean, comboBuilder));
test(...checkProperty(libui.UiCombobox, 'enabled', Boolean, comboBuilder));
test(...checkProperty(libui.UiCombobox, 'selected', Number, comboBuilder));

test(...checkProperty(libui.UiRadioButtons, 'visible', Boolean, radioBuilder));
test(...checkProperty(libui.UiRadioButtons, 'enabled', Boolean, radioBuilder));
test(...checkProperty(libui.UiRadioButtons, 'selected', Number, radioBuilder));

test(...checkProperty(libui.UiEditableCombobox, 'visible', Boolean));
test(...checkProperty(libui.UiEditableCombobox, 'enabled', Boolean));
test(...checkProperty(libui.UiEditableCombobox, 'text', String));

test(...checkEvent(libui.UiSlider, 'onChanged', 'value', Number));
test(...checkEvent(libui.UiCombobox, 'onSelected', 'selected', Number, comboBuilder));
test(...checkEvent(libui.UiRadioButtons, 'onSelected', 'selected', Number, radioBuilder));
test(...checkEvent(libui.UiEditableCombobox, 'onChanged', 'text', String));
test(...checkEvent(libui.UiEntry, 'onChanged', 'text', String));
test(...checkEvent(libui.UiSpinbox, 'onChanged', 'value', Number));
test(...checkEvent(libui.UiCheckbox, 'onToggled', 'checked', Boolean));

test(...checkProperty(libui.UiColorButton, 'color', libui.Color));
test(...checkEvent(libui.UiColorButton, 'onChanged', 'color', libui.Color));

const resolve = require('path').resolve;
const writeFileSync = require('fs').writeFileSync;
const existsSync = require('fs').existsSync;

const bs = '```js';
const be = '```';
const t = '`';

function writeFile(name, description, ...contents) {
	const path = resolve(__dirname, '../docs', name.slice(2).toLowerCase() + '.md');
	const imagePath = resolve(__dirname, '../docs/media/', name + '.png');
	const image = existsSync(imagePath) ? `![${name} example](media/${name}.png)` : '';
	const code = `
var libui = require('libui');

libui.Ui.init();
var win = new libui.UiWindow('${name} example', 640, 480, true);

var widget = new libui.${name}();
win.setChild(widget);

win.onClosing(function () {
	win.close();
	libui.stopLoop();
});

win.show();

libui.startLoop();
`;

	const template = `
# ${name.slice(2)}

> ${description}

${image}

${bs}
${code}
${be}

---

# Constructor

> new libui.${name}()

Create a new ${name} object.

---

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.

${contents.filter(c => c.type === 'property').map(c => c.content).join('\n')}


---

# Methods

${contents.filter(c => c.type === 'method').map(c => c.content).join('\n')}

---

# Events

See [events implementation](events.md) for generic details on how events are implemented.

${contents.filter(c => c.type === 'event').map(c => c.content).join('\n')}

`;

	writeFileSync(path, template);
	// writeFileSync(resolve(__dirname, 'show' + name + '.js'), code.replace(`require('libui')`, `require('../index')`));
	// require('./show' + name + '.js');
}

function property(name, type, description) {
	return {
		type: 'property',
		content: `
### ${name}: ${type}

${description}

`
	};
}

function event(name, property) {
	return {
		type: 'event',
		content: `
### ${name}

Emitted whenever property ${t}${property}${t} change.

`
	};
}

function method(name, description) {
	return {
		type: 'method',
		content: ``
	};
}

writeFile('UiForm', 'A container that organize children as labeled fields.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between widgets. \nDefaults to false.')
);

writeFile('UiGrid', 'A powerful container that allow to specify size and position of each children.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between widgets. \nDefaults to false.')
);

writeFile('UiEntry', 'A simple, single line text entry widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the entry.\nRead write.'),
	event('onChanged', 'text')
);

writeFile('UiMultilineEntry', 'A multiline text entry widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the multiline entry.\nRead write.'),
	event('onChanged', 'text')
);

writeFile('UiLabel', 'A static text label.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The static text of the label.\nRead write.')
);

writeFile('UiVerticalSeparator', 'A vertical line to visually separate widgets.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.')
);

writeFile('UiHorizontalSeparator', 'An horizontal line to visually separate widgets.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.')
);

writeFile('UiDatePicker', 'A widgets to edit dates.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.')
);

writeFile('UiTimePicker', 'A widgets to edit times.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.')
);

writeFile('UiDateTimePicker', 'A widgets to edit date/times.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.')
);

writeFile('UiButton', 'A simple button.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The static text of the button.\nRead write.')
);

writeFile('UiCheckbox', 'A checkbox widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('checked', 'Boolean', 'Whether the checkbox is checked or unchecked.\nRead write.\nDefaults to false'),
	property('text', 'String', 'The static text of the button.\nRead write.'),
	event('onToggled', 'checked', 'Boolean')
);

writeFile('UiSpinbox', 'An entry widget for numerical values.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current numeric value of the spinbox.\nRead write.'),
	event('onChanged', 'value', 'Number')
);

writeFile('UiSlider', 'Horizontal slide to set numerical values.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current numeric value of the slider.\nRead write.'),
	event('onChanged', 'value', 'Number')

);

writeFile('UiProgressBar', 'Progress bar widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current position of the progress bar. Could be setted to -1 to create an indeterminate progress bar.\nRead write.')
);

writeFile('UiCombobox', 'A drop down combo box that allow list selection only.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('selected', 'Number', 'Return or set the current selected item by index.'),
	event('onSelected', 'selected', 'Number')
);

writeFile('UiRadioButtons', 'A widget that represent a group of radio options.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('selected', 'Number', 'Return or set the current choosed option by index.'),
	event('onSelected', 'selected', 'Number')
);

writeFile('UiEditableCombobox', 'A drop down combo box that allow selection from list or free text entry.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'Return or set the current selected text or the text value of the selected item in the list.'),
	event('onChanged', 'text', 'String')
);

writeFile('UiColorButton', 'A button that open a color palette popup.',
	property('color', 'Color', 'Return or set the currently selected color'),
	event('onChanged', 'color', 'Color')
);

/*
var libui = require('../index.js');

libui.Ui.init();

var win = new libui.UiWindow("Example window", 640, 480, true);
win.borderless = true;
var box = new libui.UiVerticalBox();
var entry = new libui.UiMultilineEntry();
entry.text = 'This is some text';

box.append(entry, 1);

win.setChild(box);

win.onClosing(function () {
	libui.stopLoop();
});

win.show();

libui.startLoop();
*/

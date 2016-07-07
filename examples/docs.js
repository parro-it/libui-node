const resolve = require('path').resolve;
const writeFileSync = require('fs').writeFileSync;
const existsSync = require('fs').existsSync;

const bs = '```js';
const be = '```';
const t = '`';
let readme = `# libui-node

These pages document the ${t}libui-node${t} classes.
If you are new to the framework, you should start reading basic documentation on how it work:

* [initialization & event loop](initialization.md) - explains how to initialize the framework and how the event loop works.
* [properties](properties.md) - explains how widgets properties are implemented by ${t}libui-node${t}.
* [events](events.md) - explains how widgets events are implemented by ${t}libui-node${t}.
* [UiWindow](window.md) - explains how to create and manage OS windows.
* [Containers](containers.md) - explains how you can group widgets in tree hierarchies using different layout strategies.



`;
// const readmePath = resolve(__dirname, '../docs/readme.md');

function writeFile(name, description, ...contents) {
	const filename = name.slice(2).toLowerCase() + '.md';
	const path = resolve(__dirname, '../docs', filename);
	const imagePath = resolve(__dirname, '../docs/media/', name + '.png');
	const image = existsSync(imagePath) ? `![${name} example](media/${name}.png)` : '';
	readme += `
* [${name}](${filename}) - ${description}`;
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
${contents.filter(c => c.type === 'property').map(c => c.methods).join('\n')}

${contents.filter(c => c.type === 'event').length === 0 ? '' : `---

# Events

See [events implementation](events.md) for generic details on how events are implemented.

${contents.filter(c => c.type === 'event').map(c => c.content).join('\n')}
`}
`;

	writeFileSync(path, template);
	// writeFileSync(resolve(__dirname, 'show' + name + '.js'), code.replace(`require('libui')`, `require('../index')`));
	// require('./show' + name + '.js');
}

function property(name, type, description) {
	const getterName = 'get' + name[0].toUpperCase() + name.slice(1);
	const setterName = 'set' + name[0].toUpperCase() + name.slice(1);
	return {
		type: 'property',
		methods: `
## ${setterName}

Set the value of property ${t}${name}${t}

**Arguments**

* value: ${type} - The new value for ${t}${name}${t} property.

## ${getterName}

Return the value of property ${t}${name}${t}

`,
		content: `
### ${name}: ${type}

${description}

`
	};
}

function event(name, property, description) {
	return {
		type: 'event',
		content: `
### ${name}
${description || `
Emitted whenever property ${t}${property}${t} change.
`}

`
	};
}

function method(name, description, args) {
	return {
		type: 'method',
		content: `
## ${name}

${description}

${args ? `
**Arguments**

* ${args.join('\n* ')}
` : ''}
`
	};
}

writeFile('UiForm', 'A container that organize children as labeled fields.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between children. \nDefaults to false.'),
	method('append', 'Append a new child widget as last field with specified label.', [
		'label: String - the text to use as label of the field.',
		'control: UiControl - the control to append.',
		'stretchy: Boolean - whether the child should expand to use all available size.'
	]),
	method('deleteAt', 'Remove a child widget and albel at specified position.', [
		'index: Number - the index of the control to remove.'
	]),
	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')

);

writeFile('UiGrid', 'A powerful container that allow to specify size and position of each children.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between children. \nDefaults to false.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiEntry', 'A simple, single line text entry widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the entry.\nRead write.'),
	event('onChanged', 'text'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiPasswordEntry', 'A single line text entry widget that mask the input, useful to edit passwords or other sensible data.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the entry.\nRead write.'),
	event('onChanged', 'text'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiSearchEntry', 'A single line text entry widget to search text.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the entry.\nRead write.'),
	event('onChanged', 'text'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiMultilineEntry', 'A multiline text entry widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('readOnly', 'Boolean', 'Whether the user is allowed to change the entry text. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The current text of the multiline entry.\nRead write.'),
	event('onChanged', 'text'),
	method('append', 'Append specified text to the entry content.', [
		'text: String - the text to append.'
	]),
	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiLabel', 'A static text label.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The static text of the label.\nRead write.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiVerticalSeparator', 'A vertical line to visually separate widgets.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiHorizontalSeparator', 'An horizontal line to visually separate widgets.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiDatePicker', 'A widgets to edit dates.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiTimePicker', 'A widgets to edit times.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiDateTimePicker', 'A widgets to edit date/times.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiButton', 'A simple button.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'The static text of the button.\nRead write.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.'),

	event('onClicked', null, 'Emitted when the button is clicked')
);

writeFile('UiCheckbox', 'A checkbox widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('checked', 'Boolean', 'Whether the checkbox is checked or unchecked.\nRead write.\nDefaults to false'),
	property('text', 'String', 'The static text of the button.\nRead write.'),
	event('onToggled', 'checked'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiSpinbox', 'An entry widget for numerical values.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current numeric value of the spinbox.\nRead write.'),
	event('onChanged', 'value'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiSlider', 'Horizontal slide to set numerical values.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current numeric value of the slider.\nRead write.'),
	event('onChanged', 'value'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')

);

writeFile('UiProgressBar', 'Progress bar widget.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('value', 'Number', 'The current position of the progress bar. Could be setted to -1 to create an indeterminate progress bar.\nRead write.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiCombobox', 'A drop down combo box that allow list selection only.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('selected', 'Number', 'Return or set the current selected item by index.'),
	event('onSelected', 'selected'),
	method('append', 'Append a new text item to the drop down list.', [
		'text: String - the text item to append.'
	]),
	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiRadioButtons', 'A widget that represent a group of radio options.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('selected', 'Number', 'Return or set the current choosed option by index.'),
	event('onSelected', 'selected'),
	method('append', 'Append a new radio option as last one with specified text.', [
		'text: String - the text to show as radio widget label.'
	]),
	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiEditableCombobox', 'A drop down combo box that allow selection from list or free text entry.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('text', 'String', 'Return or set the current selected text or the text value of the selected item in the list.'),
	event('onChanged', 'text'),
	method('append', 'Append a new text item to the drop down list.', [
		'text: String - the text item to append.'
	]),
	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiColorButton', 'A button that open a color palette popup.',
	property('color', 'Color', 'Return or set the currently selected color'),
	event('onChanged', 'color'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiVerticalBox', 'A container that stack its chidren vertically.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between children. \nDefaults to false.'),
	method('append', 'Append a new child widget as last one.', [
		'control: UiControl - the control to append.',
		'stretchy: Boolean - whether the child should expand to use all available size.'
	]),
	method('deleteAt', 'Remove a child widget at specified position.', [
		'index: Number - the index of the control to remove.'
	]),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiTab', 'A container that show each chidren in a separate tab.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	method('append', 'Append a new child widget as last tab.', [
		'label: String - the text to show in the new tab caption.',
		'control: UiControl - the control to append.'
	]),
	method('insertAt', 'Insert a new child widget before specified position.', [
		'label: String - the text to show in the new tab caption.',
		'before: Number - the control will be inserted before this position',
		'control: UiControl - the control to insert.'
	]),

	method('deleteAt', 'Remove the tab and widget at specified position.', [
		'index: Number - the index of the tab to remove.'
	]),

	method('setMargined', 'Specifies that a tab should use a margin around its content.', [
		'page: Number - the index of the tab.',
		'margined: Boolean - whether to display a margin or not.'
	]),

	method('getMargined', 'Return a boolean that indicate if a tab is displaying a margin around its content.', [
		'page: Number - the index of the tab.'
	]),

	method('numPages', 'Return the total number of tab pages contained in the widgets.'),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiHorizontalBox', 'A container that stack its chidren horizontally.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('padded', 'Boolean', 'If true, the container insert some space between children. \nDefaults to false.'),
	method('append', 'Append a new child widget as last one.', [
		'control: UiControl - the control to append.',
		'stretchy: Boolean - whether the child should expand to use all available size.'
	]),
	method('deleteAt', 'Remove a child widget at specified position.', [
		'index: Number - the index of the control to remove.'
	]),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

writeFile('UiGroup', 'A container for a single widget that provide a caption and visually group it\'s children.',
	property('visible', 'Boolean', 'Whether the widget should be visible or hidden. \nRead write.\nDefaults to `true`.'),
	property('enabled', 'Boolean', 'Whether the widget should be enabled or disabled. \nRead write.\nDefaults to `true`.'),
	property('margined', 'Boolean', 'This property specify if the group content area should have a margin or not.\nDefaults to false.'),
	property('title', 'String', 'This property specify the caption of the group.\nDefaults to empty string.'),
	method('setChild', 'Set the child widget of the group.', [
		'control: UiControl - the control to append.'
	]),

	method('destroy', 'Destroy and free the control.'),
	method('setParent', 'Change the parent of the control', [
		'parent: UiControl - the new parent of the widget or null to detach it.'
	]),
	method('toplevel', 'Return whether the control is a top level one or not.')
);

// writeFileSync(readmePath, readme);

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

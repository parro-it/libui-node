'use strict';
const {readFile, writeFile} = require('fs');
const libui = require('..');

const {label, window, tab, menu, multilineEntry} = require('./utils.js');

const onClosing = () => libui.stopLoop();

libui.Ui.onShouldQuit(() => {
	onClosing();
});

const winProps = {
	hasMenubar: true,
	title: 'Node Pad',
	width: 640,
	height: 480,
	onClosing
};

let win = null;
let editor;
let status;
let currentFileName = '';

function newFile() {
	editor.text = '';
	currentFileName = '';
	status.text = 'Not saved';
}

function openFile() {
	const filename = libui.UiDialogs.openFile(win);
	if (filename) {
		readFile(filename, 'utf8', (err, content) => {
			if (err) {
				return libui.UiDialogs.msgBoxError(
					win,
					'Error while reading file',
					err.stack);
			}
			editor.text = content;
			status.text = filename;
			currentFileName = filename;
		});
	}
}

function saveFileAs() {
	const filename = libui.UiDialogs.saveFile(win);
	if (filename) {
		currentFileName = filename;
		writeFile(currentFileName, editor.text, err => {
			if (err) {
				return libui.UiDialogs.msgBoxError(
					win,
					'Error while writing file',
					err.stack);
			}
		});
	}
}

function saveFile() {
	if (!currentFileName) {
		return saveFileAs();
	}

	writeFile(currentFileName, editor.text, err => {
		if (err) {
			return libui.UiDialogs.msgBoxError(
				win,
				'Error while writing file',
				err.stack);
		}
	});
}

menu([
	{
		label: 'File',
		submenu: [
			{
				label: 'New file',
				click: newFile
			},
			{
				label: 'Open',
				click: openFile
			},
			// {
			// 	label: 'Close current tab',
			// 	click: () => {}
			// },
			{
				label: 'Save',
				click: saveFile
			},
			{
				label: 'Save as',
				click: saveFileAs
			},
			{
				role: 'quit'
			}
		]
	},
	{
		label: 'Edit',
		submenu: [
			{
				label: 'Copy'
			},
			{
				label: 'Paste'
			},
			{
				label: 'Cut'
			},
			{
				label: 'Select all'
			}
		]
	},
	{
		label: 'Help',
		submenu: [
			{
				label: 'Help',
				click: () => {}
			},
			{
				role: 'about'
			}
		]
	}
]);

win = window(
	winProps,
	tab(
		{stretchy: true},
		(editor = multilineEntry({stretchy: true, tabTitle: 'New file'}))),
	(status = label({stretchy: false, text: 'Not saved'})));

win.show();
libui.startLoop();

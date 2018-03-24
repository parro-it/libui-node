# Window

> Create and control windows.

```js
var libui = require('libui');

var win = new libui.UiWindow("Example window", 640, 480, true);

win.onClosing(function () {
	libui.stopLoop();
});

libui.startLoop();
win.show();
```

The UiWindow class is responsible to show and manage native windows.
UiWindow instance could contains only one control. If you need more, you have to use [Containers](containers.md).

---

# Constructor

> new libui.UiWindow()

Create a new UiWindow object.

### Arguments

* title: String - text to show in window title bar.
* width: Number	- width of window in pixels
* height: Number - height of window in pixels
* hasMenubar: Boolean - specify that this window has a menu bar. See [Menu](#menubar)

---

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.

## margined: Bool

This property specify if the window content should have a margin or not.
It defaults to false.


![image](https://cloud.githubusercontent.com/assets/11197111/16465935/804a30d4-3e41-11e6-8189-150e8cddc152.png)

A window with `margined: false`


![image](https://cloud.githubusercontent.com/assets/11197111/16465906/68304cfe-3e41-11e6-8ae0-3123205ee136.png)

Same window with `margined: true`

## title: String

Set or return the text to show in window title bar.

## position: [Point](point.md)

Set or return the position in pixel relative to the top-left window angle.


## contentSize: [Size](size.md)

Set or return the size in pixel of the content area of the window. Window decoration size are excluded. This mean that if you set window size to 0,0 you still see title bar and OS window buttons.

## fullscreen: Boolean

Whether the window should show in fullscreen or not.

## borderless: Boolean

Allow to specify that the window is a frameless one, without borders, title bar and OS window control widgets.


![image](https://cloud.githubusercontent.com/assets/11197111/16465986/b1befd0c-3e41-11e6-8421-20c106a096f0.png)

A window with `borderless: true`

---

# Methods

## show

Show the window.


## close

Close the window.

## setChild

Allow to specify the control to show in window content area. UiWindow instances can contain only one control. If you need more, you have to use [Containers](containers.md).

### Arguments

* control: UiControl - the control to use in window content area.


## center

Center the window on screen, both horizontally and vertically.

---

# Events

See [events implementation](events.md) for generic details on how events are implemented.

## onClosing

Emitted when the OS window close button is clicked. You are responsible to close window in response to this event.

```js
win.onClosing(function() {
	win.close();
});
```

## onPositionChanged

Emitted when the window position on screen changed, on when fullscreen state change.


## onContentSizeChanged

Emitted when window content size change.

# Window

> Create and control windows.

```js
var libui = require('libui');

libui.Ui.init();

var win = new libui.UiWindow("Example window", 640, 480, true);

win.onClosing(function () {
	libui.stopLoop();
});

win.show();

libui.startLoop();
```

The UiWindow class is responsible to show and manage native windows.
UiWindow instance could contains only one control. If you need more, you have to use [Containers](containers.md).

# Constructor

> new libui.UiWindow()

Create a new UiWindow object.

### Arguments

* title: String - text to show in window title bar.
* width: Number	- width of window in pixels
* height: Number - height of window in pixels
* hasMenubar: Boolean - specify that this window has a menu bar. See [Menu](#menubar)

# Properties

See [properties implementation](properties.md) for generic details on how properties are implemented.

## margined: Bool

This property specify if the window content should have a margin or not.
It defaults to false.

![image](https://cloud.githubusercontent.com/assets/11197111/16465543/9bd37358-3e3f-11e6-89e5-68c918320640.png)
<small>A window with `margined: false`</small>

![image](https://cloud.githubusercontent.com/assets/11197111/16465525/7dead124-3e3f-11e6-83da-4b4aa322634a.png)
<small>Same window with `margined: true`</small>

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

![image](https://cloud.githubusercontent.com/assets/11197111/16465572/c56de93c-3e3f-11e6-9b0c-f5a31f6483fe.png)

<small>A window with `borderless: true`</small>

# Methods

## show

Show the window.


## close

Close the window.

## setChild

Allow to specify the control to show in window content area. UiWindow instances could contains only one control. If you need more, you have to use [Containers](containers.md).

### Arguments

* control: UiControl - the control to use in window content area.


## center

Center the window on screen, both horizontally and vertically.


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

# libui-node

> libui Node.js bindings.

[![Travis Build Status](https://img.shields.io/travis/parro-it/libui-node.svg)](http://travis-ci.org/parro-it/libui-node)
[![NPM module](https://img.shields.io/npm/v/libui-node.svg)](https://npmjs.org/package/libui-node)
[![NPM downloads](https://img.shields.io/npm/dt/libui-node.svg)](https://npmjs.org/package/libui-node)

[libui](https://github.com/andlabs/libui) is a simple and portable (but not inflexible) GUI library in C that uses the native GUI technologies of each platform it supports.

It is in early stage of development, but is evolving at great pace and is really awesome.

It could become an awesome, lightweight alternative to Electron to develop multiplatform GUI.

![image](https://cloud.githubusercontent.com/assets/11197111/15990529/68e924f4-3095-11e6-8a13-b91678def555.png)

# Supported platform

* Windows: Windows Vista SP2 with Platform Update or newer
* Unix: GTK+ 3.10 or newer
* Mac OS X: OS X 10.8 or newer

# Project status

* All current `libui` API, except for [these ones](https://github.com/parro-it/libui-node/issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement) are implemented.
* I'm developing on `linux`, so this is the preferred platform to test. OSX should work too, but it's not tested. Windows has yet to be configured in build scripts, but it will be supported in further releases.
* There are very few tests developed, but they are passing in `Travis` thank you to @jjrv awesome work.
* This is not yet battle-tested in a real app, but the control gallery example you saw in the screenshot above is fully working.

# Build Requirements

* All platforms:
	- CMake 2.8.11 or newer
* Windows: either
	-Microsoft Visual Studio 2013 or newer (2013 is needed for va_copy())
	-MinGW-w64 (other flavors of MinGW may not work)
* Unix: nothing else specific
* Mac OS X: nothing else specific, so long as you can build Cocoa programs

# Installation

```bash
npm install --save libui-node
```

# Usage

Plase look in [examples folder](https://github.com/parro-it/libui-node/tree/master/examples).
We will write complete API documentation soon...

# License

The MIT License (MIT)

Copyright (c) 2016 parro-it

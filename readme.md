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

We don't publish new versions to NPM yet.

```bash
git clone
npm install
```

To run the control gallery example, type:

```bash
npm start
```

# Usage

Plase look in [examples folder](https://github.com/parro-it/libui-node/tree/master/examples).
We will write complete API documentation soon...


# Future directions of the project

## API

This binding is actually implementing low-level API straight to the `libui` ones.
We plan to add another level of API on top of it to simplify GUI building. You can get a taste of how they will be in [example utils.js file](https://github.com/parro-it/libui-node/blob/master/examples/utils.js).

This new API will support transpilation from JSX to further simplify GUI building.

These works will become in future the base for a React-Native like project.

## Publishing

Since `libui` binaries are relatively small, we plan to precompile them for supported platforms and publish binaries file directly to NPM, to avoid the native build stage on install.

# Contribution & design

	* Each `libui` widget implementaion is written in it's own C++ file in `src` folder.
	* Each widget is implemented in it's own C++ class, each class is a simple wrapper for related libui C functions.
	* There is an header file called `ui-node.h` that contains all classes definitions.
	* We build the project using the awesome [nbind](https://github.com/charto/nbind) tool, that automate the process of linking a straight C++ class to Node.js stuff...
	* All the GUI code run in the node javascript main thread. You must call `libui.startLoop` to start the GUI event loop. It run one step at a time, you can see in [index.js](https://github.com/parro-it/libui-node/blob/master/index.js) how this is implemented.

## Useful NPM scripts

	* test - run AVA tests && XO linting.
	* start - start the control gallery example
	* build - rebuild C++ sources
	* build:libui - rebuild libui sources under `libui` git submodule

## Related projects

* [libui](https://github.com/andlabs/libui) - Simple and portable (but not inflexible) GUI library in C that uses the native GUI technologies of each platform it supports.
* [nbind](https://github.com/charto/nbind) - Magical headers that make your C++ library accessible from JavaScript

# Contributors


[![Andrea Parodi](https://avatars0.githubusercontent.com/u/11197111?s=130)](https://github.com/parro-it) | [![Juha Järvi](https://avatars3.githubusercontent.com/u/778781?s=130)](https://github.com/jjrv) | [![Chan Guan Hao](https://avatars1.githubusercontent.com/u/5748750?s=130)](https://github.com/mavenave)
---|---|---
[Andrea Parodi](https://github.com/parro-it) [Juha Järvi](https://github.com/jjrv) | [Chan Guan Hao](https://github.com/mavenave)



# License

The MIT License (MIT)

Copyright (c) 2016 parro-it

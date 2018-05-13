# libui-node

> Node.js bindings for [libui](https://github.com/andlabs/libui) library.

[libui](https://github.com/andlabs/libui) is a lightweight, portable GUI library that uses the native GUI technologies of each platform it supports.

It is in early stage of development, but is evolving at great pace and is really awesome. It could become an awesome alternative to Electron to develop multiplatform GUI, expecially suited to develop small apps.

[![Travis Build Status](https://img.shields.io/travis/parro-it/libui-node/master.svg)](http://travis-ci.org/parro-it/libui-node)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/ebcssfrpaypfwha4?svg=true)](https://ci.appveyor.com/project/parro-it/libui-node)
[![NPM module](https://img.shields.io/npm/v/libui-node.svg)](https://npmjs.org/package/libui-node)
[![NPM downloads](https://img.shields.io/npm/dt/libui-node.svg)](https://npmjs.org/package/libui-node)

# Screenshots

---

<p align="center">
macOS
</p>

![macOS](docs/media/Window-macOS.png)

---

<p align="center">
Linux
</p>

![Linux](docs/media/Window-Linux.png)

---

<p align="center">
Windows
</p>

![Windows](docs/media/Window-Windows.png)

---

# Supported platforms

* Windows: Windows Vista SP2 with Platform Update or newer
* Unix: GTK+ 3.10 or newer
* Mac OS X: OS X 10.8 or newer
* Node.js version 4 or greater.

# Prerequisites

## Windows

- [windows-build-tools](https://www.npmjs.com/package/windows-build-tools) or Visual Studio 2015 to compile the project.
- [Visual C++ Redistributable Package per Visual Studio 2013](https://www.microsoft.com/it-it/download/details.aspx?id=40784)

## Linux

If they are not provided by default in your distribution:
- [build-essential](https://packages.ubuntu.com/xenial/build-essential) to compile the project.
- [GTK+ 3](https://packages.ubuntu.com/source/xenial/gtk+3.0)

## macOS

- [Xcode 8](https://developer.apple.com/xcode/) to compile the project.

# Installation

```bash
npm install -S libui-node
```

`libui` prebuilt binaries are automatically downloaded after install.

If you get this error on Windows:

```
'__pfnDliNotifyHook2': redefinition; different type modifiers
```

you need to install latest npm version:

```bash
$ npm i -g npm
```

see [this node-gyp issue](https://github.com/nodejs/node-gyp/issues/972)
for more details.

# Documentation & examples

Documentation is in [docs folder](docs).
You can also find working examples in [examples folder](https://github.com/parro-it/libui-node/tree/master/examples).

## How to run the examples

First, you have to clone the GitHub repo and npm install it:

```bash
git clone https://github.com/parro-it/libui-node.git
npm install
```

Then, to run the control gallery example (requires Node.js >= 6), type:

```bash
npm start
```

For the core api, example, type:

```bash
npm run start-core
```

To run other examples:
```bash
node <path to example file>
```

# Contribution & design

* Each `libui` control implementation is written in it's own C++ file in `src` folder.
* Each control is implemented in it's own C++ class, each class is a simple wrapper of related libui C functions.
* Header files are in `src/includes` folder.
* Control events does not follow `node` convention: if you attach an handler to an event, previous one will be overwritten and never be called.
* We build the project using the awesome [nbind](https://github.com/charto/nbind) tool, that automate the process of linking a straight C++ class to Node.js stuff...

# Related projects

* [libui](https://github.com/andlabs/libui) - Simple and portable (but not inflexible) GUI library in C that uses the native GUI technologies of each platform it supports.
* [nbind](https://github.com/charto/nbind) - Magical headers that make your C++ library accessible from JavaScript
* [proton-native](https://github.com/kusti8/proton-native) - A React environment for cross platform native desktop apps https://proton-native.js.org

# Contributors

[![Andrea Parodi](https://avatars0.githubusercontent.com/u/11197111?s=130)](https://github.com/parro-it) |
[![Juha Järvi](https://avatars3.githubusercontent.com/u/778781?s=130)](https://github.com/jjrv) |
[![Niklas Mischkulnig](https://avatars2.githubusercontent.com/u/4586894?s=130)](https://github.com/mischnic) |
[![Gustav Hansen](https://avatars0.githubusercontent.com/u/9812956?s=130)](https://github.com/kusti8)
---|---|---|---
[Andrea Parodi](https://github.com/parro-it) | [Juha Järvi](https://github.com/jjrv) | [Niklas Mischkulnig](https://github.com/mischnic) | [Gustav Hansen](https://github.com/kusti8)

# License

The MIT License (MIT)

Copyright (c) 2018 parro-it

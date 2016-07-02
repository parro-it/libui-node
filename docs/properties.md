# libui-node widgets properties

Every widget properties has a dual implementation.

You can read and write them both using javascript properties and using setter/getter methods.

Javascript properties are implemented on top of getter/setter methods provided by `libui`.
We've choosen to provide access to getter/setter method to increase flexibility. They could be useful for a functional style paradigm style coding. You can bind / map / filter on them.


### using javascript properties

```js
var widget = new libui.UiEntry();
// set the text contained in the entry
widget.text = 'sample text';

// retrieve it
console.log(widget.text);
```

### using setter/getter methods

```js
var widget = new libui.UiEntry();
// set the text contained in the entry
widget.setText('sample text');

// retrieve it
console.log(widget.getText());
```




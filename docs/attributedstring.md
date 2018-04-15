# AttributedString

```cpp
class AttributedString {
    AttributedString(const char *str);
    void free();
    const char * toString();
    size_t toStringLen();

    void appendUnattributed(const char *str);
    void insertUnattributed(const char *str, size_t at);
    void deleteString(size_t start, size_t end);
    void setAttribute(FontAttribute *attr, size_t start, size_t end);

    void appendAttributed(const char *str, FontAttribute *attr);
    void appendAttributed(const char *str, FontAttribute *attr, FontAttribute *attr2);

    void forEach(nbind::cbFunction& cb);

    size_t numGraphemes();
    size_t byteIndexToGrapheme(size_t pos);
    size_t graphemeToByteIndex(size_t pos);
};

class FontAttribute {
  public:
    // It is an error to call this on a uiAttribute that does not hold the corresponding type
    const char *getFamily();
    double getSize();
    int getWeight();
    int getItalic();
    int getStretch();
    Color getColor();
    int getUnderline();
    int getUnderlineColor(Color *c);
    OpenTypeFeatures *getOTFeatures();
};

```

# Classes

---

# AttributedString

## Constructor

## Methods

### forEach

Iterates over all tags. Return `libui.forEach.stop` in the callback to break.

**Arguments**

* cb: `function(OpenTypeFeatures, tag, value)`


# FontAttribute

not every font supports every style


## Static Functions

### newFamily

Returns a new FontAttribute for the font `family`.

**Arguments**

* family: String

### newSize

Returns a new FontAttribute for the font size `size`.

**Arguments**

* size: Number

### newWeight(int weightAttribute)

Returns a new FontAttribute for the font weight `weight`.

**Arguments**

* weight: Number. Possible values:
    * `libui.textWeight.minimum`
    * `libui.textWeight.thin`
    * `libui.textWeight.ultraLight`
    * `libui.textWeight.light`
    * `libui.textWeight.book`
    * `libui.textWeight.normal`
    * `libui.textWeight.medium`
    * `libui.textWeight.semiBold`
    * `libui.textWeight.bold`
    * `libui.textWeight.ultraBold`
    * `libui.textWeight.heavy`
    * `libui.textWeight.ultraHeavy`
    * `libui.textWeight.maximum`
	* any number between `minimum` and `maximum`

### newItalic

Returns a new FontAttribute for the italic style `style`.

**Arguments**

* style:
	* `libui.textItalic.normal`
	* `libui.textItalic.oblique` ("slanted version of normal")
	* `libui.textItalic.italic` ("true italics")

### newStretch

Returns a new FontAttribute for the stretch (or width) style `style`.

**Arguments**

* style:
	* `libui.textStretch.ultraCondensed`
	* `libui.textStretch.extraCondensed`
	* `libui.textStretch.condensed`
	* `libui.textStretch.semiCondensed`
	* `libui.textStretch.normal`
	* `libui.textStretch.semiExpanded`
	* `libui.textStretch.expanded`
	* `libui.textStretch.extraExpanded`
	* `libui.textStretch.ultraExpanded`

### newColor

Returns a new FontAttribute for the text color `color`.

**Arguments**

* color: Color

### newBackgroundColor

Returns a new FontAttribute for the background color `color`.

**Arguments**

* color: Color

### newUnderline

Returns a new FontAttribute for the underline style `style`.

**Arguments**

* style:
	* `libui.textUnderline.none`
	* `libui.textUnderline.single`
	* `libui.textUnderline.double`
	* `libui.textUnderline.suggestion`

### newUnderlineColor

Returns a new FontAttribute for the underline color.

**Arguments**

* colorAttr: 
	* `libui.textUnderlineColor.custom`
	* `libui.textUnderlineColor.spelling`
	* `libui.textUnderlineColor.grammar`
	* `libui.textUnderlineColor.auxiliary`
* color: Color (required only with `textUnderlineColor.custom`)

### newOTFeatures(OpenTypeFeatures *otf);

Returns a new FontAttribute with the OpenTypeFeatures `otf`.

**Arguments**

* otf: [OpenTypeFeatures](#opentypefeatures)


## Methods

### getAttributeType

Returns the type of the attribute. Possible values:

* `libui.textAttributeType.family`
* `libui.textAttributeType.size`
* `libui.textAttributeType.weight`
* `libui.textAttributeType.italic`
* `libui.textAttributeType.stretch`
* `libui.textAttributeType.color`
* `libui.textAttributeType.background`
* `libui.textAttributeType.underline`
* `libui.textAttributeType.underlineColor`
* `libui.textAttributeType.features`


### free

Frees the object immediately.

# OpenTypeFeatures

Defines font glyph settings (ignored if not supported by the font).

See [here](https://docs.microsoft.com/de-de/typography/opentype/spec/featuretags) for more information and a list of feature tags.

Example: Setting `liga` to `1` enables ligatures (not supported by every font):

```js
const otf = new libui.OpenTypeFeatures();
otf.add('liga', 1)

str.appendAttributed('affix', FontAttribute.newOTFeatures(otf));
```


## Static Functions

### clone

Returns a new object containg all tags from f2.

**Arguments**

* f2: OpenTypeFeatures

## Methods

### add

Adds/overwrites a `tag` with `value`.

**Arguments**

* tag: String
* value: Number


### remove

Remove a tag (and use the default).

**Arguments**

* tag: String

### get

Returns the value of `tag` or `null` if not set.

**Arguments**

* tag: String

### forEach

Iterates over all tags. Return `libui.forEach.stop` in the callback to break.

**Arguments**

* cb: `function(OpenTypeFeatures, tag, value)`

### free

Frees the object immediately.

# FontDescriptor

Defines a font.

## Constructor

**Arguments**

* family: String
* size: Number
* weight: 
* italic:
* stretch:

## Methods

### getFamily
### getSize
### getWeight
### getItalic
### getStretch

### free

Frees the object immediately.

# DrawTextLayout

Defines how an attributed string should get drawn onto an area. (See [Area UiDrawContext.text](area.md#text))

## Constructor

**Arguments**

* str: [AttributedString](#attributedstring)
* defaultFont: [FontDescriptor](#fontdescriptor)
* width: Number (i.e. `params.getAreaWidth()`)
* align:
	- `libui.textAlign.left`
	- `libui.textAlign.center`
	- `libui.textAlign.right`


## Methods

### getExtends

Returns a SizeDouble containing the actual width and height of the text.

### free

Frees the object immediately.

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
    // doesn't need to be called when appended
    void free();
    int getAttributeType();

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

    static FontAttribute newFamily(const char *family);
    static FontAttribute newSize(double size);
    static FontAttribute newWeight(int weightAttribute);
    static FontAttribute newItalic(int italicAttribute);
    static FontAttribute newStretch(int stretchAttribute);
    static FontAttribute newColor(Color c);
    static FontAttribute newBackground(Color c);
    static FontAttribute newUnderline(int underlineAttr);
    static FontAttribute newUnderlineColor(int underlineColorAttr, Color c);
    static FontAttribute newOTFeatures(OpenTypeFeatures *otf);
};

    // cb(OpenTypeFeatures, tag, value)
    void forEach(nbind::cbFunction& cb);
};

```

# Classes

---

# OpenTypeFeatures

Defines font glyph settings (if supported by the font).

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

Returns a [SizeDouble](size.md) containing the actual width and height of the text.

### free

Frees the object immediately.


```js
libui.textWeight = {
    minimum: 0,
    thin: 100,
    ultraLight: 200,
    light: 300,
    book: 350,
    normal: 400,
    medium: 500,
    semiBold: 600,
    bold: 700,
    ultraBold: 800,
    heavy: 900,
    ultraHeavy: 950,
    maximum: 1000
};

libui.textItalic = {
    normal: 0,
    oblique: 1,
    italic: 2
};

libui.textStretch = {
    ultraCondensed: 0,
    extraCondensed: 1,
    condensed: 2,
    semiCondensed: 3,
    normal: 4,
    semiExpanded: 5,
    expanded: 6,
    extraExpanded: 7,
    ultraExpanded: 8
};

libui.textAttributeType = {
    family: 0,
    size: 1,
    weight: 2,
    italic: 3,
    stretch: 4,
    color: 5,
    background: 6,
    underline: 7,
    underlineColor: 8,
    features: 9
};

libui.textUnderline = {
    none: 0,
    single: 1,
    double: 2,
    suggestion: 3
};

libui.textUnderlineColor = {
    custom: 0,
    spelling: 1,
    grammar: 2,
    auxiliary: 3
};
```

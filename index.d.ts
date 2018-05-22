declare namespace LibUINode {
	export const enum textWeight {
		minimum = 0,
		thin = 100,
		ultraLight = 200,
		light = 300,
		book = 350,
		normal = 400,
		medium = 500,
		semiBold = 600,
		bold = 700,
		ultraBold = 800,
		heavy = 900,
		ultraHeavy = 950,
		maximum = 1000
	}

	export const enum textItalic {
		normal = 0,
		oblique = 1,
		italic = 2
	}

	export const enum textStretch {
		ultraCondensed = 0,
		extraCondensed = 1,
		condensed = 2,
		semiCondensed = 3,
		normal = 4,
		semiExpanded = 5,
		expanded = 6,
		extraExpanded = 7,
		ultraExpanded = 8
	}

	export const enum textAttributeType {
		family = 0,
		size = 1,
		weight = 2,
		italic = 3,
		stretch = 4,
		color = 5,
		background = 6,
		underline = 7,
		underlineColor = 8,
		features = 9
	}

	export const enum textUnderline {
		none = 0,
		single = 1,
		double = 2,
		suggestion = 3
	}

	export const enum textUnderlineColor {
		custom = 0,
		spelling = 1,
		grammar = 2,
		auxiliary = 3
	}

	export const enum textAlign {
		left = 0,
		center = 1,
		right = 2
	}

	export const enum forEach {
		continue = 0,
		stop = 1
	}

	export const enum brushType {
		solid = 0,
		linearGradient = 1,
		radialGradient = 2
		// IMPL uiDrawBrushTypeImage = 3
	}

	export const enum lineCap {
		flat = 0,
		round = 1,
		square = 2
	}

	export const enum lineJoin {
		miter = 0,
		round = 1,
		bevel = 2
	}

	export const enum fillMode {
		winding = 0,
		alternate = 1
	}

	export const enum modifierKeys {
		ctrl = 1 << 0,
		alt = 1 << 1,
		shift = 1 << 2,
		super = 1 << 3
	}

	export const enum extKeys {
		escape = 1,
		insert = 2, // equivalent to "Help" on Apple keyboards
		delete = 3,
		home = 4,
		end = 5,
		pageUp = 6,
		pageDown = 7,
		up = 8,
		down = 9,
		left = 10,
		right = 11,
		f1 = 12, // F1..F12 are guaranteed to be consecutive
		f2 = 13,
		f3 = 14,
		f4 = 15,
		f5 = 16,
		f6 = 17,
		f7 = 18,
		f8 = 19,
		f9 = 20,
		f10 = 21,
		f11 = 22,
		f12 = 23,
		n0 = 24, // numpad keys; independent of Num Lock state
		n1 = 25, // N0..N9 are guaranteed to be consecutive
		n2 = 26,
		n3 = 27,
		n4 = 28,
		n5 = 29,
		n6 = 30,
		n7 = 31,
		n8 = 32,
		n9 = 33,
		nDot = 34,
		nEnter = 35,
		nAdd = 36,
		nSubtract = 37,
		nMultiply = 38,
		nDivide = 39
	}

	export function stopLoop(): void;
	export function startLoop(): void;

	export class FontAttribute {
		constructor(other: FontAttribute);

		static newUnderlineColor(
			type: textUnderlineColor,
			color: Color): FontAttribute;

		static getFamily(): string|null;

		static getSize(): number|null;

		static getWeight(): textWeight|null;

		static getItalic(): textItalic|null;

		static getStretch(): textStretch|null;

		static getColor(): Color|null;

		static getUnderline(): textUnderline|null;

		static getUnderlineColor(): {
			type: textAttributeType;
			color: Color | null;
		}|null;

		static getOTFeatures(): OpenTypeFeatures|null;
	}

	export class OpenTypeFeatures {
		add(tag: string, value: number): void;
		remove(tag: string): void;
		get(tag: string): number;
		forEach(
			cb: (feat: OpenTypeFeatures, str: string, val: number) => void): void;
		static clone(feat: OpenTypeFeatures): OpenTypeFeatures;
	}

	export class Color {
		public r: number;
		public g: number;
		public b: number;
		public a: number;
		constructor(r: number, g: number, b: number, a: number);
		constructor(other: Color);
	}

	export class Point {
		public x: number;
		public y: number;
		constructor(x: number, y: number);
		constructor(other: Point);
	}

	export class Size {
		public w: number;
		public h: number;
		constructor(w: number, h: number);
	}

	export class PointDouble {
		public x: number;
		public y: number;
		constructor(x: number, y: number);
		constructor(other: PointDouble);
	}

	export class SizeDouble {
		public w: number;
		public h: number;
		constructor(w: number, h: number);
	}

	export class BrushGradientStop {
		public pos: number;
		public color: Color;
		constructor(pos: number, color: Color);
	}

	export class AttributedString {
		constructor(str: string);

		toString(): string;
		toStringLen(): number;

		appendAttributed(str: string): void;
		appendUnattributed(str: string): void;
		insertAttributed(str: string, start: number): void;
		insertUnattributed(str: string, at: number): void;
		deleteString(start: number, end: number): void;
		setAttribute(attr: FontAttribute, start: number, end: number): void;

		// TODO: add cb parameters
		forEach(cb: () => void): void;

		numGraphemes(): number;
		byteIndexToGrapheme(pos: number): number;
		graphemeToByteIndex(pos: number): number;
	}
}

export = LibUINode;

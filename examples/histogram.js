var libui = require('../index.js');

var mainwin;
var histogram;
var colorWhite = 0xFFFFFF;
var colorBlack = 0x000000;
var colorDodgerBlue = 0x1E90FF;


var datapoints = [];
var colorButton;
var currentPoint = -1;

// some metrics
var xoffLeft = 20;
var yoffTop = 20;
var xoffRight = 20;
var yoffBottom = 20;
var pointRadius = 5;
var uiDrawFillModeWinding = 0;

function graphSize(clientWidth, clientHeight) {
	return {
		width: clientWidth - xoffLeft - xoffRight,
		height: clientHeight - yoffTop - yoffBottom
	};
}

var handler = {
	Draw: function handlerDraw(self, area, p) {
		console.log(0)
		return;
		var path;
		var brush = buildSolidBrush(colorWhite, 1.0);
		var sp;
		var m;
		var graphR, graphG, graphB, graphA;

		path = new libui.UiDrawPath(uiDrawFillModeWinding);
		console.log(1)
		path.addRectangle(0, 0, p.AreaWidth, p.AreaHeight);
		console.log(2)
		path.end();
		console.log(3)
		p.getContext().fill(path, brush);
		console.log(4)
		path.freePath();
		console.log(5)

		// figure out dimensions
		var graph = graphSize(p.AreaWidth, p.AreaHeight);
		console.log(6)

		// clear sp to avoid passing garbage to uiDrawStroke()
		// for example, we don't use dashing
		sp = new libui.Ui.DrawStrokeParams();
		console.log(7)

		// make a stroke for both the axes and the histogram line
		sp.Cap = 0;
		sp.Join = 0;
		sp.Thickness = 2;
		sp.MiterLimit = 10.0;

		// draw the axes
		brush = buildSolidBrush(colorBlack, 1.0);
		console.log(8)

		path = new libui.UiDrawPath(uiDrawFillModeWinding);

		path.newFigure(xoffLeft, yoffTop);
		path.lineTo(xoffLeft, yoffTop + graph.height);
		path.lineTo(xoffLeft + graph.width, yoffTop + graph.height);
		path.end();
		p.getContext().stroke(path, brush, sp);
		path.freePath();

		// now transform the coordinate space so (0, 0) is the top-left corner of the graph
		m = new  libui.UiDrawMatrix();
		m.setIdentity();
		m.translate(xoffLeft, yoffTop);
		p.getContext().transform(m);

/*
		// now get the color for the graph itself and set up the brush
		uiColorButtonColor(colorButton, &graphR, &graphG, &graphB, &graphA);
		brush.Type = uiDrawBrushTypeSolid;
		brush.R = graphR;
		brush.G = graphG;
		brush.B = graphB;
		// we set brush->A below to different values for the fill and stroke

		// now create the fill for the graph below the graph line
		path = constructGraph(graph.width, graph.height, 1);
		brush.A = graphA / 2;
		uiDrawFill(p->Context, path, &brush);
		uiDrawFreePath(path);

		// now draw the histogram line
		path = constructGraph(graph.width, graph.height, 0);
		brush.A = graphA;
		uiDrawStroke(p->Context, path, &brush, &sp);
		uiDrawFreePath(path);

		// now draw the point being hovered over
		if (currentPoint != -1) {
			double xs[10], ys[10];

			pointLocations(graph.width, graph.height, xs, ys);
			path = uiDrawNewPath(uiDrawFillModeWinding);
			uiDrawPathNewFigureWithArc(path,
				xs[currentPoint], ys[currentPoint],
				pointRadius,
				0, 6.23,		// TODO pi
				0);
			uiDrawPathEnd(path);
			// use the same brush as for the histogram lines
			uiDrawFill(p->Context, path, &brush);
			uiDrawFreePath(path);
		}*/

	},

	MouseEvent: function handlerMouseEvent(area, e) {
		/*
		double graph.width, graph.height;
		double xs[10], ys[10];
		int i;

		graphSize(e->AreaWidth, e->AreaHeight, &graph.width, &graph.height);
		pointLocations(graph.width, graph.height, xs, ys);

		for (i = 0; i < 10; i++)
			if (inPoint(e->X, e->Y, xs[i], ys[i]))
				break;
		if (i == 10)		// not in a point
			i = -1;

		currentPoint = i;
		// TODO only redraw the relevant area
		uiAreaQueueRedrawAll(histogram);
		*/
	},

	MouseCrossed: function () {},
	DragBroken: function () {},
	KeyEvent: function () {}

};


// helper to quickly set a brush color
function buildSolidBrush(color, alpha) {
	var component;

	component = (color >> 16) & 0xFF;
	var R = component / 255;
	component = (color >> 8) & 0xFF;
	var G = component / 255;
	component = color & 0xFF;
	var B = component / 255;
	var A = alpha;

	var uiDrawBrushTypeSolid = 0;
	var brush = new libui.DrawBrush(
		new libui.Color(R, G, B, A),
		new libui.Point(0, 0),
		new libui.Point(0, 0),
		uiDrawBrushTypeSolid,
		[]
	);

	return brush;
}

// and some colors
// names and values from https://msdn.microsoft.com/en-us/library/windows/desktop/dd370907%28v=vs.85%29.aspx
/*
static void pointLocations(double width, double height, double *xs, double *ys)
{
	double xincr, yincr;
	int i, n;

	xincr = width / 9;		// 10 - 1 to make the last point be at the end
	yincr = height / 100;

	for (i = 0; i < 10; i++) {
		// get the value of the point
		n = uiSpinboxValue(datapoints[i]);
		// because y=0 is the top but n=0 is the bottom, we need to flip
		n = 100 - n;
		xs[i] = xincr * i;
		ys[i] = yincr * n;
	}
}

static uiDrawPath *constructGraph(double width, double height, int extend)
{
	uiDrawPath *path;
	double xs[10], ys[10];
	int i;

	pointLocations(width, height, xs, ys);

	path = uiDrawNewPath(uiDrawFillModeWinding);

	uiDrawPathNewFigure(path, xs[0], ys[0]);
	for (i = 1; i < 10; i++)
		uiDrawPathLineTo(path, xs[i], ys[i]);

	if (extend) {
		uiDrawPathLineTo(path, width, height);
		uiDrawPathLineTo(path, 0, height);
		uiDrawPathCloseFigure(path);
	}

	uiDrawPathEnd(path);
	return path;
}

static int inPoint(double x, double y, double xtest, double ytest)
{
	// TODO switch to using a matrix
	x -= xoffLeft;
	y -= yoffTop;
	return (x >= xtest - pointRadius) &&
		(x <= xtest + pointRadius) &&
		(y >= ytest - pointRadius) &&
		(y <= ytest + pointRadius);
}

static void onDatapointChanged(uiSpinbox *s, void *data)
{
	uiAreaQueueRedrawAll(histogram);
}

static void onColorChanged(uiColorButton *b, void *data)
{
	uiAreaQueueRedrawAll(histogram);
}

static int onClosing(uiWindow *w, void *data)
{
	uiControlDestroy(uiControl(mainwin));
	uiQuit();
	return 0;
}

static int shouldQuit(void *data)
{
	uiControlDestroy(uiControl(mainwin));
	return 1;
}
*/

function main() {
	libui.Ui.init();

	var hbox, vbox;
	var i;
	var brush;

	mainwin = new libui.UiWindow("libui Histogram Example", 640, 480, 1);
	mainwin.margined = true;
	mainwin.onClosing(function () {
		libui.stopLoop();
	});

	hbox = new libui.UiHorizontalBox();
	hbox.padded = true;
	mainwin.setChild(hbox);

	vbox = new libui.UiVerticalBox();
	vbox.padded = true;
	hbox.append(vbox, 0);

	for (i = 0; i < 10; i++) {
		datapoints[i] = new libui.UiSpinbox(0, 100);
		datapoints[i].value = Math.round(Math.random() * 100);
		// uiSpinboxOnChanged(datapoints[i], onDatapointChanged, NULL);
		vbox.append(datapoints[i], 0);
	}

/*
	colorButton = uiNewColorButton();
	// TODO inline these
	setSolidBrush(&brush, colorDodgerBlue, 1.0);
	uiColorButtonSetColor(colorButton,
		brush.R,
		brush.G,
		brush.B,
		brush.A);
	uiColorButtonOnChanged(colorButton, onColorChanged, NULL);
	uiBoxAppend(vbox, uiControl(colorButton), 0);
*/

	histogram = new libui.UiArea(
		handler.Draw,
		handler.MouseEvent,
		handler.MouseCrossed,
		handler.DragBroken,
		handler.KeyEvent
	);
	hbox.append(histogram, 1);

	mainwin.show();

	libui.startLoop();
	return 0;
}

main();

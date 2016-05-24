#include "libui/ui.h"
#include <nan.h>

using namespace v8;

void returnPtr(char** ptr, const Nan::FunctionCallbackInfo<v8::Value>& info) {
    Nan::MaybeLocal<v8::Object> buff = Nan::CopyBuffer((char*) ptr, sizeof(ptr));
    info.GetReturnValue().Set(buff.ToLocalChecked());
}

char* ptrFromArg(const Nan::FunctionCallbackInfo<v8::Value>& info, int pos) {
    Local<Object> bufferObj    = info[pos]->ToObject();
    char** bufferData = (char**) node::Buffer::Data(bufferObj);
    return *bufferData;
}

#define EXPECT_ARGUMENT_COUNT(N) \
	if (info.Length() < N) { \
		Nan::ThrowTypeError("Too few arguments, expected " #N); \
		return; \
	}

#define EXPECT_NUMBER_ARGUMENT(POS,NAME) \
	if (!info[POS]->IsNumber()) { \
		Nan::ThrowTypeError(#NAME " should be a number"); \
		return; \
	}

#define EXPECT_STRING_ARGUMENT(POS,NAME) \
	if (!info[POS]->IsString()) { \
		Nan::ThrowTypeError(#NAME " should be a string"); \
		return; \
	}

#define EXPECT_STRING_ARGUMENT(POS,NAME) \
	if (!info[POS]->IsString()) { \
		Nan::ThrowTypeError(#NAME " should be a string"); \
		return; \
	}

#define EXPECT_BOOLEAN_ARGUMENT(POS,NAME) \
	if (!info[POS]->IsBoolean()) { \
		Nan::ThrowTypeError(#NAME " should be a boolean"); \
		return; \
	}


NAN_METHOD(NewWindow) {

	EXPECT_ARGUMENT_COUNT(4)
	EXPECT_STRING_ARGUMENT(0,title)
	EXPECT_NUMBER_ARGUMENT(1,width)
	EXPECT_NUMBER_ARGUMENT(2,height)
	EXPECT_BOOLEAN_ARGUMENT(3,hasMenubar)

	String::Utf8Value sTitle(info[0]->ToString());
	std::string stdsTitle = std::string(*sTitle);

	const char* title = stdsTitle.c_str();
	int width = info[1]->IntegerValue();
	int height = info[2]->IntegerValue();
	int hasMenubar = info[3]->BooleanValue();

	uiWindow *mainwin = uiNewWindow(title, width, height, hasMenubar);

	returnPtr((char **) &mainwin, info);

}

NAN_METHOD(WindowSetMargined) {

	EXPECT_ARGUMENT_COUNT(2)
	EXPECT_BOOLEAN_ARGUMENT(1,margined)

	uiWindow *win = (uiWindow *) ptrFromArg(info, 0);

	Nan::Maybe<int> maybeMargined = Nan::To<int>(info[1]);

	if (!maybeMargined.IsNothing()) {
		int margined = maybeMargined.FromJust();
		uiWindowSetMargined(win, margined);
	}
}



NAN_METHOD(Init) {
	uiInitOptions o;
	memset(&o, 0, sizeof (uiInitOptions));
	const char *err = uiInit(&o);
	if (err != NULL) {
		Nan::ThrowTypeError(err);
		uiFreeInitError(err);
	}
}

NAN_METHOD(ControlShow) {
	EXPECT_ARGUMENT_COUNT(1)

	uiWindow *win = (uiWindow *) ptrFromArg(info, 0);
	uiControlShow(uiControl(win));
}


NAN_METHOD(ControlDestroy) {
	EXPECT_ARGUMENT_COUNT(1)

	uiWindow *win = (uiWindow *) ptrFromArg(info, 0);
	uiControlDestroy(uiControl(win));
}

NAN_METHOD(Main) {
	uiMain();
}

static Persistent<Function> persistentCallback;


static int onClosing(uiWindow *w, void *data)
{
	Local<Function> callback = Local<Function>::New(Isolate::GetCurrent(), persistentCallback);
	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, 0, NULL);
	return 0;
}

NAN_METHOD(WindowOnClosing) {
	EXPECT_ARGUMENT_COUNT(2)

	uiWindow *win = (uiWindow *) ptrFromArg(info, 0);
	Local<Function> callback = info[1].As<Function>();
	persistentCallback.Reset(Isolate::GetCurrent(), callback);

	uiWindowOnClosing(win, onClosing, NULL);
}


NAN_METHOD(Quit) {
	uiQuit();
}



NAN_MODULE_INIT(InitModule) {
	Nan::Set(target,
		Nan::New("windowOnClosing").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(WindowOnClosing)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("controlDestroy").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(ControlDestroy)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("quit").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(Quit)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("newWindow").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(NewWindow)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("init").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(Init)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("controlShow").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(ControlShow)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("main").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(Main)->GetFunction()
	);

	Nan::Set(target,
		Nan::New("windowSetMargined").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(WindowSetMargined)->GetFunction()
	);
}

NODE_MODULE(libui, InitModule)

#include "libui/ui.h"
#include <nan.h>

using namespace v8;

/*
void Pow(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}

	if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
		Nan::ThrowTypeError("Both arguments should be numbers");
		return;
	}

	double arg0 = info[0]->NumberValue();
	double arg1 = info[1]->NumberValue();
	v8::Local<v8::Number> num = Nan::New(pow(arg0, arg1));

	info.GetReturnValue().Set(num);
}

typedef struct {
   std::string s0;
   std::string s1;
} full_name;

void BuildFullName(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("nome e cognome");
		return;
	}

	if (!info[0]->IsString() || !info[1]->IsString()) {
		Nan::ThrowTypeError("Both arguments should be string");
		return;
	}

	String::Utf8Value s0(info[0]->ToString());
	String::Utf8Value s1(info[1]->ToString());
	full_name *fn = (full_name *) malloc(sizeof(full_name));
	fn->s0 = std::string(*s0);
	fn->s1 = std::string(*s1);

	info.GetReturnValue().Set(Nan::NewBuffer((char*)fn, sizeof(full_name)).ToLocalChecked());
}


void GetFullName(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 1) {
		Nan::ThrowTypeError("una struct");
		return;
	}

	Local<Object> bufferObj    = info[0]->ToObject();
	full_name *fn = (full_name *) node::Buffer::Data(bufferObj);

	std::string result = fn->s0 + " " + fn->s1;
	Nan::MaybeLocal<v8::String> ret = Nan::New(result.c_str());
	info.GetReturnValue().Set( ret.ToLocalChecked() );
}

*/
void newWindow(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 4) {
		Nan::ThrowTypeError("too few arguments");
		return;
	}

	if (!info[0]->IsString()) {
		Nan::ThrowTypeError("title should be string");
		return;
	}

	if (!info[1]->IsNumber()) {
		Nan::ThrowTypeError("width should be a number");
		return;
	}

	if (!info[2]->IsNumber()) {
		Nan::ThrowTypeError("height should be a number");
		return;
	}

	if (!info[3]->IsBoolean()) {
		Nan::ThrowTypeError("hasMenubar should be a boolean");
		return;
	}

	String::Utf8Value sTitle(info[0]->ToString());
	std::string stdsTitle = std::string(*sTitle);

	const char* title = stdsTitle.c_str();
	int width = info[1]->IntegerValue();
	int height = info[2]->IntegerValue();
	int hasMenubar = info[2]->BooleanValue();

	uiWindow *mainwin = uiNewWindow(title, width, height, hasMenubar);
	info.GetReturnValue().Set(
		Nan::NewBuffer(
			(char *) mainwin,
			sizeof(char *)
		).ToLocalChecked()
	);
}

void init(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	uiInitOptions o;
	memset(&o, 0, sizeof (uiInitOptions));
	const char *err = uiInit(&o);
	if (err != NULL) {
		Nan::ThrowTypeError(err);
		uiFreeInitError(err);
	}
}

void show(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	if (info.Length() < 1) {
		Nan::ThrowTypeError("too few arguments");
		return;
	}

	Local<Object> bufferObj    = info[0]->ToObject();
	uiWindow *mainwin = (uiWindow *) node::Buffer::Data(bufferObj);
	uiControlShow(uiControl(mainwin));
	uiMain();
	uiUninit();

}

void Init(v8::Local<v8::Object> exports) {
	exports->Set(
		Nan::New("newWindow").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(newWindow)->GetFunction()
	);

	exports->Set(
		Nan::New("init").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(init)->GetFunction()
	);

	exports->Set(
		Nan::New("show").ToLocalChecked(),
		Nan::New<v8::FunctionTemplate>(show)->GetFunction()
	);
}

NODE_MODULE(pow, Init)

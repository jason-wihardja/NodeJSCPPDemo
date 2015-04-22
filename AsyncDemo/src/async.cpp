#include "Async.hpp"
#include "API\RESTController.hpp"

using namespace std;

Async::Async() {}
Async::~Async() {}

Persistent<Function> Async::constructor;

void Async::Init() {
	Isolate* isolate = Isolate::GetCurrent();

	// Prepare Constructor Function Template
	Local<FunctionTemplate> localFunctionTemplate = FunctionTemplate::New(isolate, New);
	localFunctionTemplate->SetClassName(String::NewFromUtf8(isolate, "APIController"));
	localFunctionTemplate->InstanceTemplate()->SetInternalFieldCount(1);

	// Register Prototype Methods


	constructor.Reset(isolate, localFunctionTemplate->GetFunction());
}

void Async::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.IsConstructCall()) {
		// Invoked as constructor: `new APIController(...)`
		Async* object = new Async();
		object->Wrap(args.This());
		args.GetReturnValue().Set(args.This());
	} else {
		// Invoked as plain function `APIController(...)`, turn into construct call.
		const int argc = 1;
		Local<Value> argv[argc] = { args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance(argc, argv));
	}
}

void Async::NewInstance(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };
	Local<Function> cons = Local<Function>::New(isolate, constructor);
	Local<Object> instance = cons->NewInstance(argc, argv);

	args.GetReturnValue().Set(instance);
}
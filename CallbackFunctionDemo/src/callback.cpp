#include <node.h>

using namespace v8;

int factorial(int n) {
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}

void Factorial(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.Length() != 2) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!(args[0]->IsNumber() && args[1]->IsFunction())) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			int result = factorial(args[0]->Int32Value());

			Local<Function> callbackFunction = Local<Function>::Cast(args[1]);
			const unsigned argc = 1;
			Local<Value> argv[argc] = { Number::New(isolate, result) };

			callbackFunction->Call(isolate->GetCurrentContext()->Global(), argc, argv);
		}
	}
}

void Init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "factorial", Factorial);
}

NODE_MODULE(CallbackFunctionDemo, Init)
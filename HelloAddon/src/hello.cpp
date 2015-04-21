#include <node.h>
#include <string>

using namespace std;
using namespace v8;

void SayHello(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.Length() > 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Too many arguments")));
		return;
	} else {
		if (args.Length() == 1) {
			if (!args[0]->IsString()) {
				isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
			} else {
				string argument(*String::Utf8Value(args[0]->ToString()));
				args.GetReturnValue().Set(String::NewFromUtf8(isolate, argument.c_str()));
			}
		} else {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Hello World"));
		}
	}
}

void Init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "hello", SayHello);
}

NODE_MODULE(HelloAddon, Init)
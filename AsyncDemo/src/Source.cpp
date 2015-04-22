#include "Async.hpp"

#include <node.h>

using namespace v8;

void CreateInstance(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	Async::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
	Async::Init();
	NODE_SET_METHOD(module, "exports", CreateInstance);
}

NODE_MODULE(AsyncDemo, InitAll)
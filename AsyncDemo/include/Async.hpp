#ifndef __Async_hpp__
#define __Async_hpp__

#include <node.h>
#include <node_object_wrap.h>
#include <v8.h>
#include <uv.h>

using namespace v8;
using namespace node;

class Async : public ObjectWrap {
public:
	static void Init();
	static void NewInstance(const FunctionCallbackInfo<Value>& args);

private:
	explicit Async();
	~Async();

	static Persistent<Function> constructor;
	static void New(const FunctionCallbackInfo<Value>& args);
};

#endif // !__Async_hpp__
#ifndef __prime_async_hpp__
#define __prime_async_hpp__

#include <node.h>
#include <uv.h>

using namespace v8;

namespace PrimeAsync {
	void RegisterMethod(Handle<Object> exports);

	void FindPrimeAsync(const FunctionCallbackInfo<Value>& args);
	void FindPrimeWork(uv_work_t* request);
	void FindPrimeAsyncAfter(uv_work_t* request, int status);
}

#endif // !__prime_async_hpp__

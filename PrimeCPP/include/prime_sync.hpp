#ifndef __prime_sync_hpp__
#define __prime_sync_hpp__

#include <node.h>

using namespace v8;

namespace PrimeSync {
	void RegisterMethod(Handle<Object> exports);

	void FindPrime(const FunctionCallbackInfo<Value>& args);
}

#endif // !__prime_sync_hpp__

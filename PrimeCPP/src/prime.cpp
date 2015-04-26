#include "prime_sync.hpp"
#include "prime_async.hpp"

#include <node.h>

using namespace v8;

void InitAll(Handle<Object> exports) {
	PrimeSync::RegisterMethod(exports);
	PrimeAsync::RegisterMethod(exports);
}

NODE_MODULE(PrimeCPP, InitAll)
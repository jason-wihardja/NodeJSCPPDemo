#include <node.h>
#include "performance_algorithm.hpp"

using namespace v8;

void InitAll(Handle<Object> exports) {
	PerformanceAlgorithm::Initialize();
	PerformanceAlgorithm::RegisterMethod(exports);
}

NODE_MODULE(Performance, InitAll)
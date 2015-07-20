#ifndef __performance_algorithm_hpp__
#define __performance_algorithm_hpp__

#include <node.h>
#include <uv.h>

#include <Windows.h>
#include <tchar.h>
#include <Pdh.h>

using namespace v8;

namespace PerformanceAlgorithm {
	static PDH_HQUERY cpuQuery;
	static PDH_HCOUNTER cpuTotal;

	void Initialize();
	void RegisterMethod(Handle<Object> exports);

	void GetPerformanceDataAsync(const FunctionCallbackInfo<Value>& args);
	void GetPerformanceDataWork(uv_work_t* request);
	void GetPerformanceDataAsyncAfter(uv_work_t* request, int status);
}

#endif // !__performance_algorithm_hpp__

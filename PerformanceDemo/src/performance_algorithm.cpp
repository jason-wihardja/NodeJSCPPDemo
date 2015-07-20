#include <algorithm>

#include "baton.hpp"
#include "structs.hpp"
#include "performance_algorithm.hpp"

void PerformanceAlgorithm::Initialize() {
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, "\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);
}

void PerformanceAlgorithm::RegisterMethod(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "getPerformanceData", PerformanceAlgorithm::GetPerformanceDataAsync);
}

void PerformanceAlgorithm::GetPerformanceDataAsync(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.Length() != 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!args[0]->IsFunction()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			Local<Function> callbackFunction = Local<Function>::Cast(args[0]);

			Baton<string, PerformanceData>* baton = new Baton<string, PerformanceData>();
			baton->request.data = baton;
			baton->callbackFunction.Reset(isolate, callbackFunction);

			uv_queue_work(uv_default_loop(), &baton->request, PerformanceAlgorithm::GetPerformanceDataWork, PerformanceAlgorithm::GetPerformanceDataAsyncAfter);
		}
	}
}

void PerformanceAlgorithm::GetPerformanceDataWork(uv_work_t* request) {
	Baton<string, PerformanceData>* baton = static_cast<Baton<string, PerformanceData>*>(request->data);

	baton->result.memory_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&baton->result.memory_info);

	PDH_FMT_COUNTERVALUE counterVal;
	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	baton->result.cpu_usage = counterVal.doubleValue;

	DWORD processIDs[1024], bytesReturned;
	EnumProcesses(processIDs, sizeof(processIDs), &bytesReturned);

	DWORD numberOfProcesses = bytesReturned / sizeof(DWORD);
	for (int i = 0; i < numberOfProcesses; i++) {
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIDs[i]);

		HMODULE hMods[1024];
		DWORD cbNeeded;
		if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
			for (int j = 0; j < (cbNeeded / sizeof(HMODULE)); j++) {
				TCHAR szModName[MAX_PATH];
				GetModuleFileNameEx(hProcess, hMods[j], szModName, sizeof(szModName) / sizeof(TCHAR));

				ProcessInfo info;
				info.process_id = processIDs[i];
				info.path = string(szModName);
				
				baton->result.processes.push_back(info);

				break;
			}
		}

		CloseHandle(hProcess);
	}

	sort(baton->result.processes.begin(), baton->result.processes.end(), [](ProcessInfo a, ProcessInfo b) -> bool {
		return a.process_id < b.process_id;
	});

	GetPerformanceInfo(&baton->result.performance_info, sizeof(PERFORMACE_INFORMATION));
}

void PerformanceAlgorithm::GetPerformanceDataAsyncAfter(uv_work_t* request, int status) {
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);

	Baton<string, PerformanceData>* baton = static_cast<Baton<string, PerformanceData>*>(request->data);
	Local<Function> callbackFunction = Local<Function>::New(isolate, baton->callbackFunction);

	Local<Object> returnValue = Object::New(isolate);
	returnValue->Set(String::NewFromUtf8(isolate, "cpu_usage"), Number::New(isolate, baton->result.cpu_usage));
	returnValue->Set(String::NewFromUtf8(isolate, "ram_usage"), Number::New(isolate, baton->result.memory_info.dwMemoryLoad));
	returnValue->Set(String::NewFromUtf8(isolate, "total_physical_memory"), Number::New(isolate, baton->result.memory_info.ullTotalPhys));
	returnValue->Set(String::NewFromUtf8(isolate, "available_physical_memory"), Number::New(isolate, baton->result.memory_info.ullAvailPhys));
	returnValue->Set(String::NewFromUtf8(isolate, "total_page_file"), Number::New(isolate, baton->result.memory_info.ullTotalPageFile));
	returnValue->Set(String::NewFromUtf8(isolate, "available_page_file"), Number::New(isolate, baton->result.memory_info.ullAvailPageFile));
	returnValue->Set(String::NewFromUtf8(isolate, "total_virtual"), Number::New(isolate, baton->result.memory_info.ullTotalVirtual));
	returnValue->Set(String::NewFromUtf8(isolate, "available_virtual"), Number::New(isolate, baton->result.memory_info.ullAvailVirtual));

	Local<Array> processes = Array::New(isolate, baton->result.processes.size());
	for (int i = 0; i < baton->result.processes.size(); i++) {
		Local<Object> processInfo = Object::New(isolate);
		processInfo->Set(String::NewFromUtf8(isolate, "process_id"), Number::New(isolate, baton->result.processes[i].process_id));
		processInfo->Set(String::NewFromUtf8(isolate, "path"), String::NewFromUtf8(isolate, baton->result.processes[i].path.c_str()));

		processes->Set(i, processInfo);
	}
	returnValue->Set(String::NewFromUtf8(isolate, "running_processes"), processes);

	const unsigned int argc = 1;
	Handle<Value> argv[argc] = { scope.Escape(returnValue) };
	callbackFunction->Call(isolate->GetCurrentContext()->Global(), argc, argv);

	baton->callbackFunction.Reset();
	delete baton;
}
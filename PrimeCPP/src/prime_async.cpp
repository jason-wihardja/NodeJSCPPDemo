#include "prime_async.hpp"
#include "baton.hpp"

void PrimeAsync::RegisterMethod(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "findPrimeAsync", PrimeAsync::FindPrimeAsync);
}

void PrimeAsync::FindPrimeAsync(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.Length() != 2) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!(args[0]->IsInt32() && args[1]->IsFunction())) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			int number = args[0]->Int32Value();
			Local<Function> callbackFunction = Local<Function>::Cast(args[1]);

			Baton<int, vector<int>>* baton = new Baton<int, vector<int>>();
			baton->request.data = baton;
			baton->callbackFunction.Reset(isolate, callbackFunction);

			baton->params.insert({ "number", number });

			uv_queue_work(uv_default_loop(), &baton->request, PrimeAsync::FindPrimeWork, PrimeAsync::FindPrimeAsyncAfter);
		}
	}
}

void PrimeAsync::FindPrimeWork(uv_work_t* request) {
	Baton<int, vector<int>>* baton = static_cast<Baton<int, vector<int>>*>(request->data);

	baton->result.clear();

	int number = baton->params["number"];

	for (int i = 2; i <= number; i++) {
		bool isPrime = true;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			baton->result.push_back(i);
		}
	}
}

void PrimeAsync::FindPrimeAsyncAfter(uv_work_t* request, int status) {
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);

	Baton<int, vector<int>>* baton = static_cast<Baton<int, vector<int>>*>(request->data);
	Local<Function> callbackFunction = Local<Function>::New(isolate, baton->callbackFunction);

	Local<Array> returnValues = Array::New(isolate, baton->result.size());
	for (int i = 0; i < baton->result.size(); i++) {
		returnValues->Set(i, Int32::New(isolate, baton->result[i]));
	}

	const unsigned int argc = 1;
	Handle<Value> argv[argc] = { scope.Escape(returnValues) };
	callbackFunction->Call(isolate->GetCurrentContext()->Global(), argc, argv);

	baton->callbackFunction.Reset();
	delete baton;
}
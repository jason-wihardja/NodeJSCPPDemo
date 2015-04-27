#include "prime_sync.hpp"
#include "prime_algorithm.hpp"

void PrimeSync::RegisterMethod(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "findPrime", PrimeSync::FindPrime);
}

#pragma region FindPrime
void PrimeSync::FindPrime(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);

	if (args.Length() != 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!args[0]->IsInt32()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			vector<int> primeNumbers = PrimeAlgorithm::GeneratePrime(args[0]->Int32Value());

			Local<Array> returnValues = Array::New(isolate, primeNumbers.size());
			for (int i = 0; i < primeNumbers.size(); i++) {
				returnValues->Set(i, Int32::New(isolate, primeNumbers[i]));
			}

			args.GetReturnValue().Set(scope.Escape(returnValues));
		}
	}
}
#pragma endregion
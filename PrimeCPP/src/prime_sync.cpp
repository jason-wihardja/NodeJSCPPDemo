#include "prime_sync.hpp"

#include <vector>

using namespace std;

void PrimeSync::RegisterMethod(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "findPrime", PrimeSync::FindPrime);
}

void PrimeSync::FindPrime(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);

	if (args.Length() != 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!args[0]->IsInt32()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			int number = args[0]->Int32Value();
			vector<int> primeNumbers;

			for (int i = 2; i <= number; i++) {
				bool isPrime = true;
				for (int j = 2; j < i; j++) {
					if (i % j == 0) {
						isPrime = false;
						break;
					}
				}
				if (isPrime) {
					primeNumbers.push_back(i);
				}
			}

			Local<Array> returnValues = Array::New(isolate, primeNumbers.size());
			for (int i = 0; i < primeNumbers.size(); i++) {
				returnValues->Set(i, Int32::New(isolate, primeNumbers[i]));
			}

			args.GetReturnValue().Set(scope.Escape(returnValues));
		}
	}
}
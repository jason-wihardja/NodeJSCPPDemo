#include <node.h>
#include <string>
#include <vector>

using namespace v8;
using namespace std;

void FindPrime(const FunctionCallbackInfo<Value>& args) {
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
				if (number > 2) {
					for (int j = 2; j < i; j++) {
						if (i % j == 0) {
							isPrime = false;
						}
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

void Init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "findPrime", FindPrime);
}

NODE_MODULE(PrimeCPP, Init)
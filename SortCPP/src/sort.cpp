#include <node.h>
#include <string>
#include <vector>

using namespace v8;
using namespace std;

void swap(Isolate* isolate, Local<Array>& source, int index_A, int index_B) {
	int temp = source->Get(index_A)->Int32Value();
	source->Set(index_A, Integer::New(isolate, source->Get(index_B)->Int32Value()));
	source->Set(index_B, Integer::New(isolate, temp));
}

void Sort(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);

	if (args.Length() != 1) {
		isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
	} else {
		if (!args[0]->IsArray()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments type")));
		} else {
			Local<Array> unsortedNumbers = Local<Array>::Cast(args[0]);

			vector<int> sortedNumbers;
			for (int i = 1; i < unsortedNumbers->Length(); i++) {
				sortedNumbers.push_back(unsortedNumbers->Get(i)->Int32Value());
			}

			// Bubble Sort
			bool swapped;
			do {
				swapped = false;
				for (int i = 1; i < sortedNumbers.size(); i++) {
					if (sortedNumbers[i] < sortedNumbers[i - 1]) {
						swap(isolate, unsortedNumbers, i, i - 1);
						swapped = true;
					}
				}
			} while (swapped);

			args.GetReturnValue().Set(scope.Escape(unsortedNumbers));
		}
	}
}

void Init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "sort", Sort);
}

NODE_MODULE(SortCPP, Init)
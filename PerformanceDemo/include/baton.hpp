#ifndef __baton_hpp__
#define __baton_hpp__

#include <node.h>
#include <uv.h>

#include <string>
#include <vector>
#include <map>

using namespace v8;
using namespace std;

template <typename ParamType, typename ResultType>
struct Baton {
public:
	uv_work_t request;
	Persistent<Function> callbackFunction;

	map<string, ParamType> params;

	ResultType result;
};

#endif // !__baton_hpp__

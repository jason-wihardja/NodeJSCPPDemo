#ifndef __structs_hpp__
#define __structs_hpp__

#include <Psapi.h>
#include <vector>

using namespace std;

typedef struct {
	long process_id;
	string path;
} ProcessInfo;

typedef struct {
	double cpu_usage;
	PERFORMACE_INFORMATION performance_info;
	MEMORYSTATUSEX memory_info;
	vector<ProcessInfo> processes;
} PerformanceData;

#endif // !__structs_hpp__
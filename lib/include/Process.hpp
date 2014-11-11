#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

using namespace std;

class Process {
private:
	bool end(string id);
	string exec(const char* cmd);

	string getJobID(string cmd);

public:
	char* make_config_file(string SYS, string REF, int thread);
	char* make_run_file(string config_file, string metric);

	string run_job(char* run_file, char* metric);
	string run_job_dep(char* run_file, char* metric, char* dep);

};

#endif



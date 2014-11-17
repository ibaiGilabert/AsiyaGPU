#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <string>

using namespace std;

class Process {
private:
	string exec(const char* cmd);

	string getJobID(string cmd);

public:
	bool end(string id);

	string make_config_file(string SYS, string REF, int thread);
	string make_run_file(string config_file, string TGT, string REF, int thread, string metric);

	string run_job(string run_file, string metric);
	string run_job_dep(string run_file, string metric, string dep);

};

#endif



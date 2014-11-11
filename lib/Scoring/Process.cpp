#include "../include/Process.hpp"
#include "../include/TESTBED.hpp"
#include "../Config.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

string Process::exec(const char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
		result += buffer;
	}
	pclose(pipe);
	return result;
}

bool Process::end(string id) {
	// check whether id job is already ended
	bool ended = true;
	string out = exec("qstat");
	istringstream bufo(out);
	int i = 0;
	for (string token; getline(bufo, token, '\n'); ++i) {
		string job_aux;
		istringstream aux(token);
		getline(aux, job_aux, ' ');
		if (job_aux == id) ended = false;
		/*if (atoi(job_aux.c_str()) > 0)
		cout << "job_ID: " << atoi(job_aux.c_str()) << endl;*/
	}
	return ended;
}

string Process::getJobID(string cmd) {
	// get the id job from qsub's return value
	boost::algorithm::trim(cmd);
	//printf("return qsub: |%s|\n", job.c_str());
	vector<string> v;
	istringstream buf(cmd);
	for (string token; getline(buf, token, ' '); ) v.push_back(token);
	/*for (int j = 0; j < v.size(); ++j) cout << "v[" << j << "]: " << v[j] << "\t";
	cout << endl;*/
	return v[2];
}


string Process::run_job(char* run_file, char* metric) {
	char qsub[] = "/usr/local/sge/bin/linux-x64/qsub ";
    strcat(qsub, run_file);
    strcat(qsub, " ");
    strcat(qsub, metric);

    string qsub_r = exec(qsub);
    string jobid_r = getJobID(qsub_r);

    return jobid_r;
}

string Process::run_job_dep(char* run_file, char* metric, char* dep) {
    char qsub[] = "/usr/local/sge/bin/linux-x64/qsub -hold_jid ";
    strcat(qsub, dep);
    strcat(qsub, " ");
    strcat(qsub, run_file);
    strcat(qsub, " ");
    strcat(qsub, metric);

    string qsub_r = exec(qsub);
    string jobid_r = getJobID(qsub_r);

    return jobid_r;
}

char* Process::make_config_file(string SYS, string REF, int thread) {
    // build config file for one thread
    // return: config_file name
    char buffer[128];
    sprintf(buffer, "%s.%.3d.%s", TESTBED::Hsystems[SYS].c_str(), thread, Common::TXTEXT.c_str());   // get the system split

    char config_name[] = "Asiya.config.";
    char c_thread[8];    sprintf(c_thread, "%.3d", thread);
    strcat(config_name, c_thread);

    ofstream config_file(config_name);
    if (config_file) {
        config_file << "input=raw" << endl << endl;
        config_file << "data_path=" << Common::DATA_PATH << endl << endl;
        config_file << "srclang=" << Config::SRCLANG << endl;
        config_file << "srccase=" << Config::SRCCASE << endl;
        config_file << "trglang=" << Config::LANG << endl;
        config_file << "trgcase=" << Config::CASE << endl << endl;;
        config_file << "src=" << TESTBED::src << endl;
        config_file << "ref=" << REF << endl;
        config_file << "sys=" << SYS << endl << endl;
        config_file << "metric_set=";
        for (set<string>::const_iterator it = Config::metrics.begin(); it != Config::metrics.end(); ++ìt) config_file << *it << " ";
        config_file << endl << endl;
        config_file.close();
    } else { fprintf(stderr, "couldn't build config file: %s\n", ); exit(1); }

    return config_name;
}

void Proces::make_run_file(string config_file, string metric) {
    // build run script file
    // return: script file name
    char run_buffer[50];
    sprintf(run_buffer, "run_%s_%.3d.sh", metric_set.c_str(), thread);   // get the system split

    ofstream run_file(run_buffer);
    if (run_file) {
        run_file << "#$ -S /bin/bash" << endl;
        run_file << "#$ -V" << endl;
        run_file << "#$ -cwd" << endl;
        run_file << "#$ -m eas" << endl;
        run_file << "#$ -M gilabert@cs.upc.edu" << endl;
        run_file << "#$ -l h_vmem=4G" << endl;          //LA MEMORIA QUE CADA METRICA DEMANI

        string cmd = "./Asiya " + config_file + " -eval single -metric_set metric_" << metric;
        //if (Config::verbose) fprintf(stderr, "[EXEC] %s\n", cmd.c_str());
    printf(stderr, "[EXEC] %s\n", cmd.c_str());

        run_file << "echo " << cmd << endl;
        run_file << cmd << endl;

        run_file.close();
    } else { fprintf(stderr, "couldn't build config file: %s\n", ); exit(1); }

    return run_buffer;
}

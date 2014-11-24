#include "../include/Process.hpp"
#include "../include/TB_FORMAT.hpp"
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


string Process::run_job(string run_file, string metric) {
	/*char qsub[] = "/usr/local/sge/bin/linux-x64/qsub ";
    strcat(qsub, run_file);
    strcat(qsub, " ");
    strcat(qsub, metric);*/

    string qsub = "/usr/local/sge/bin/linux-x64/qsub " + run_file + " " + metric;
    string qsub_r = exec(qsub.c_str());

    return getJobID(qsub_r);
}

string Process::run_job_dep(string run_file, string metric, string dep) {
    /*char qsub[] = "/usr/local/sge/bin/linux-x64/qsub -hold_jid ";
    strcat(qsub, dep);
    strcat(qsub, " ");
    strcat(qsub, run_file);
    strcat(qsub, " ");
    strcat(qsub, metric);*/

    string qsub = "/usr/local/sge/bin/linux-x64/qsub -hold_jid " + dep + " " + run_file + " " + metric;
    string qsub_r = exec(qsub.c_str());

    return getJobID(qsub_r);
}

string Process::make_config_file(string SYS, string REF, string metric_set, int thread) {
    // build config file for one thread
    // return: config_file name
    char buffer[64];
    sprintf(buffer, "%s.%.3d.%s", TESTBED::Hsystems[SYS].c_str(), thread, Common::TXTEXT.c_str());   // get the system split

    char config_name[64];
    sprintf(config_name, "Asiya_%s_%s_%s_%.3d.config", metric_set.c_str(), SYS.c_str(), REF.c_str(), thread);
    //char c_thread[8];       sprintf(c_thread, "%.3d", thread);
    //strcat(config_name, c_thread);

    string source = TB_FORMAT::get_split(TESTBED::src, Common::TXTEXT, thread);
    string reference = TB_FORMAT::get_split(TESTBED::Hrefs[REF], Common::TXTEXT, thread);
    string syst = TB_FORMAT::get_split(TESTBED::Hsystems[SYS], Common::TXTEXT, thread);

    ofstream config_file(config_name);
    if (config_file) {
        config_file << "input=raw" << endl << endl;
        //config_file << "data_path=" << Common::DATA_PATH << endl << endl;
        config_file << "srclang=" << Config::SRCLANG << endl;
        config_file << "srccase=" << Config::SRCCASE << endl;
        config_file << "trglang=" << Config::LANG << endl;
        config_file << "trgcase=" << Config::CASE << endl << endl;;
        config_file << "src=" << source << endl;
        config_file << "ref=" << reference << endl;
        config_file << "sys=" << syst << endl << endl;
        config_file << "metrics_" << metric_set << "=";
        for(set<string>::const_iterator it = Config::metrics.begin(); it != Config::metrics.end(); ++it)
            config_file << *it << " ";
        config_file << endl << endl;
        config_file.close();
    } else { fprintf(stderr, "[ERROR] Could not build config file <%s>\n", config_name); exit(1); }

    return string(config_name);
}

string Process::make_run_file(string config_file, string TGT, string REF, int thread, string metric) {
    // build run script file
    // return: script file name
    char run_buffer[50], report_buffer[50];
    sprintf(run_buffer, "run_%s_%s_%s_%.3d.sh", metric.c_str(), TGT.c_str(), REF.c_str(), thread);   // get the system split
    sprintf(report_buffer, "run_%s_%s_%s_%.3d.report", metric.c_str(), TGT.c_str(), REF.c_str(), thread);   // get the system split

    ofstream run_file(run_buffer);
    if (run_file) {
        run_file << "#$ -S /bin/bash" << endl;
        run_file << "#$ -V" << endl;
        run_file << "#$ -cwd" << endl;
        run_file << "#$ -m eas" << endl;
        run_file << "#$ -M gilabert@cs.upc.edu" << endl;
        run_file << "#$ -l h_vmem=4G" << endl << endl;          //LA MEMORIA QUE CADA METRICA DEMANI


        stringstream s_cmd;
        s_cmd << "./Asiya " << config_file << " -serialize " << (thread-1)*TB_FORMAT::chunk + 1 << " -g seg -eval single -metric_set metrics_" << metric << " > " << string(report_buffer);
	string cmd = s_cmd.str();
        //if (Config::verbose) fprintf(stderr, "[EXEC] %s\n", cmd.c_str());
    fprintf(stderr, "[EXEC] %s\n", cmd.c_str());

        run_file << "echo " << cmd << endl;
        run_file << cmd << endl;

        run_file.close();
    } else { fprintf(stderr, "[ERROR] Could not build config file <%s>\n", run_buffer); exit(1); }

    return string(run_buffer);
}

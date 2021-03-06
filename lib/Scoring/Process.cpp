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

void Process::get_s_time(string id, double &time) {
    // get the ru_ru_wallclock  of a <id> job
    //string qacct = "/usr/local/sge/bin/linux-x64/qacct -j "+id;
    string qacct = "qacct -j "+id;
    //fprintf(stderr, "[Pr] to execute: |%s|\n", qacct.c_str());
    string qacct_r = exec(qacct.c_str());
    //fprintf(stderr, "[Pr]: qacct_r: |%s|\n", qacct_r.c_str());
    if (qacct_r == "") get_s_time(id, time);

    boost::algorithm::trim(qacct_r);
    istringstream buf(qacct_r);
    for (string token; getline(buf, token, '\n'); ) {
        string ru_time;
        istringstream sru(token);
        getline(sru, ru_time, ' ');

        //cout << "\tru_time: |" << ru_time << "|" << endl;
        if (ru_time == "ru_wallclock") {
            vector<string> strs;
            boost::split(strs, token, boost::is_any_of("\t "));
            time = atof(strs[1].c_str());
            //return atof(strs[5].c_str()); (s_time)
        }
    }
}

double Process::get_time(string e_file) {
    // get the total execution time from error file
    string exe_cat = "cat " + e_file + " | grep TOTAL";
    string time_out = exec(exe_cat.c_str());

    vector<string> strs;
    boost::split(strs, time_out, boost::is_any_of("\t "));
    if (strs.size() == 0) { fprintf(stderr, "[ERROR] Could not parse total time of split execution <%s>\n", e_file.c_str()); exit(1); }

    return atof(strs[strs.size()-1].c_str());
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

    //string qsub = "/usr/local/sge/bin/linux-x64/qsub -q \\!gpu " + run_file + " " + metric;
    string qsub = "qsub -q \\!gpu " + run_file + " " + metric;
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

    //string qsub = "/usr/local/sge/bin/linux-x64/qsub -q \\!gpu -hold_jid " + dep + " " + run_file + " " + metric;
    string qsub = "qsub -q \\!gpu -hold_jid " + dep + " " + run_file + " " + metric;
    string qsub_r = exec(qsub.c_str());

    return getJobID(qsub_r);
}

string Process::make_config_file(string TGT, string REF, string metric_set, int thread) {
    // build config file for one thread
    // return: config_file name
    //char buffer[100];
    //sprintf(buffer, "%s.%.3d.%s", TESTBED::Hsystems[SYS].c_str(), thread, Common::TXTEXT.c_str());   // get the system split
    string source_txt    = TB_FORMAT::get_split(TESTBED::src, Common::TXTEXT, thread);
    string reference_txt = TB_FORMAT::get_split(TESTBED::Hrefs[REF], Common::TXTEXT, thread);
    string syst_txt      = TB_FORMAT::get_split(TESTBED::Hsystems[TGT], Common::TXTEXT, thread);
  
    string source_tgt_txt = TESTBED::replace_extension(source_txt, TGT)+"."+Common::TXTEXT;
    string reference_tgt_txt = TESTBED::replace_extension(reference_txt, TGT)+"."+Common::TXTEXT;

    // idx
    string source_idx    = TB_FORMAT::get_split(TESTBED::src, Common::IDXEXT, thread);
    string reference_idx = TB_FORMAT::get_split(TESTBED::Hrefs[REF], Common::IDXEXT, thread);

    string source_tgt_idx = TESTBED::replace_extension(source_idx, TGT)+"."+Common::IDXEXT;
    string reference_tgt_idx = TESTBED::replace_extension(reference_idx, TGT)+"."+Common::IDXEXT;
    

    // copy txt files    
    string cmd, err;
    cmd = "cp "+reference_txt+" "+reference_tgt_txt;    err = "[ERROR] could not copy <"+reference_txt+"> into <"+reference_tgt_txt+">";
    Common::execute_or_die(cmd, err);
    
    cmd = "cp "+source_txt+" "+source_tgt_txt;          err = "[ERROR] could not copy <"+source_txt+"> into <"+source_tgt_txt+">";
    Common::execute_or_die(cmd, err);

    // copy idx files
    cmd = "cp "+reference_idx+" "+reference_tgt_idx;    err = "[ERROR] could not copy <"+reference_idx+"> into <"+reference_tgt_idx+">";
    Common::execute_or_die(cmd, err);

    cmd = "cp "+source_idx+" "+source_tgt_idx;          err = "[ERROR] could not copy <"+source_idx+"> into <"+source_tgt_idx+">";
    Common::execute_or_die(cmd, err);
    
    char config_name[150];
    sprintf(config_name, "Asiya_%s_%s_%s_%.3d.config", metric_set.c_str(), TGT.c_str(), REF.c_str(), thread);
    
    ofstream config_file(config_name);
    if (config_file) {
        config_file << "input=raw" << endl << endl;
        config_file << "srclang=" << Config::SRCLANG << endl;
        config_file << "srccase=" << Config::SRCCASE << endl;
        config_file << "trglang=" << Config::LANG << endl;
        config_file << "trgcase=" << Config::CASE << endl << endl;;
        config_file << "src=" << source_tgt_txt << endl;
        config_file << "ref=" << reference_tgt_txt << endl;
        config_file << "sys=" << syst_txt << endl << endl;
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
    char run_buffer[150], report_buffer[150];
    sprintf(run_buffer, "run_%s_%s_%s_%.3d.sh", metric.c_str(), TGT.c_str(), REF.c_str(), thread);   // get the system split
    sprintf(report_buffer, "run_%s_%s_%s_%.3d.report", metric.c_str(), TGT.c_str(), REF.c_str(), thread);   // get the system split

    ofstream run_file(run_buffer);
    if (run_file) {
        run_file << "#$ -S /bin/bash" << endl;
        run_file << "#$ -V" << endl;
        run_file << "#$ -cwd" << endl;
        //run_file << "#$ -m eas" << endl;
        //run_file << "#$ -M gilabert@cs.upc.edu" << endl;
        run_file << "#$ -l h_vmem=10G" << endl;                 //LA MEMORIA QUE CADA METRICA DEMANI
        //run_file << endl << "DATAPATH=" << Common::DATA_PATH << endl;

        run_file << endl;
        //run_file << "#$ -q short@node115,short@node116,short@node117,short@node315,short@node316" << endl << endl;
        //run_file << endl << ". /home/soft/asiya/ASIYA12.04.PATH" << endl;

        stringstream s_cmd;
        s_cmd << "./Asiya " << config_file << " -serialize " << (thread-1)*TB_FORMAT::chunk + 1 << " -time -g seg -eval single -metric_set metrics_" << metric << " -data_path=" << Common::DATA_PATH << " > " << string(report_buffer);
        string cmd = s_cmd.str();

        if (Config::verbose) fprintf(stderr, "[EXEC] %s\n", cmd.c_str());

        run_file << "echo " << cmd << endl;
        run_file << cmd << endl;

        run_file.close();
    } else { fprintf(stderr, "[ERROR] Could not build config file <%s>\n", run_buffer); exit(1); }

    return string(run_buffer);
}

#include "include/TESTBED.hpp"
#include "include/Core.hpp"
#include "Common.hpp"
#include "Config.hpp"

#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <map>

//#include <stdlib.h>	//atoi

using namespace std;

int v, help;
map<string, string> Options;

void usage() {
	fprintf(stderr, "Wrong answer\n");
}

void process_configuration() {
	Core CORE;
	Scores hOQ;//(, TESTBED::wc);

    // ============= NAMES ===============================================================
	/*TESTBED::do_metric_names();
	TESTBED::do_system_names();
	TESTBED::do_reference_names();*/

    // ============= COMPUTE SCORES (if necessary) =======================================
	fprintf(stderr, "LET'S DO SOME STUFF SCORES!!!\n");
	CORE.do_scores(hOQ);
	fprintf(stderr, "[FINISHED]\n");
	//CORE.do_combination_metrics();
	fprintf(stderr, "LET'S PRINT DA FINAL REPORT!!!\n");
	CORE.do_print(hOQ);
	fprintf(stderr, "[EMD] ASIYA\n");
}

int main(int argc, char *argv[]) {

	const struct option long_opts[] =
	{
		{"v",	        	no_argument,        0, 'v'},
		{"help",        	no_argument,        0, 'h'},
		{"time",			no_argument,		0, 't'},
		{"metric_set",  	required_argument,  0, 'm'},
		{"system_set",		required_argument,	0, 's'},
		{"reference_set",	required_argument,	0, 'r'},
		{"granularity",		required_argument,	0, 'g'},
		{"input",			required_argument,	0, 'i'},
		{"eval",        	required_argument,  0, 'e'},
		{"output",			required_argument,	0, 'o'},
		{"data_path",		required_argument,  0, 'd'},
		{"paralel",			required_argument,	0, 'p'},
		{0,0,0,0},
	};
	//NO CANVIAR L'ORDRE, PRIMER EL CONFIG
	char* Asiya_config = argv[1];
	fprintf(stderr, "Config_file: %s\n", Asiya_config);

	int opt, long_index;
	while((opt = getopt_long_only(argc, argv, "", long_opts, &long_index)) != -1) {
		switch (opt) {
			case 'e': Options["eval"] = optarg; break;
			case 'm': Options["metric_set"] = optarg; break;
			case 's': Options["system_set"] = optarg; break;
			case 'r': Options["reference_set"] = optarg; break;
			case 'g': Options["granularity"] = optarg; break;
			case 'i': Options["input"] = optarg; break;
			case 'h': help = 1; break;
			case 't': Options["time"] = "1"; break;
			case 'v': Options["v"] = "1"; break;
			case 'o': Options["output"] = optarg; break;
			case 'd': Options["data_path"] = optarg; break;
			case 'p': Options["paralel"] = optarg; break;
			//default: usage();
		}
	}
	if (help) usage();

	// -- check number of argments
	int narg = 1;
	if (argc < narg) usage;


	Config CONFIG;
	vector<string> metaeval_options, optimize_options;

	// -- read config file --------------------------------------------------------------------------------
	CONFIG.read_configuration_options(Asiya_config, Options, metaeval_options, optimize_options);

	// -- process configuration options -------------------------------------------------------------------
	process_configuration();
}




	/*
	cout << "rLANGS:" << endl;
	for (map<string, int>::const_iterator it = rLANGS.begin(); it != rLANGS.end(); it++) {
		cout << '\t' <<  it->first << " -> " << it->second << endl;
	} cout << endl;

	cout << "eval_schemes:" << endl;
	for (map<string, int>::const_iterator it = eval_schemes.begin(); it != eval_schemes.end(); it++) {
		cout << '\t' << it->first << " -> " << it->second << endl;
	} cout << endl;

	cout << "rCI:" << endl;
	for (map<string, int>::const_iterator it = rCI.begin(); it != rCI.end(); it++) {
		cout << '\t' << it->first << " -> " << it->second << endl;
	} cout << endl;

	cout << "rCORRS:" << endl;
	for (map<string, int>::const_iterator it = rCORRS.begin(); it != rCORRS.end(); it++) {
		cout << '\t' << it->first << " -> " << it->second << endl;
	} cout << endl;

	cout << "rMRANKS:" << endl;
	for (map<string, int>::const_iterator it = rMRANKS.begin(); it != rMRANKS.end(); it++) {
		cout << '\t' << it->first << " -> " << it->second << endl;
	} cout << endl;

	cout << "metaeval_criteria:" << endl;
	for (map<string, int>::const_iterator it = metaeval_criteria.begin(); it != metaeval_criteria.end(); it++) {
		cout << '\t' << it->first << " -> " << it->second << endl;
	} cout << endl;*/
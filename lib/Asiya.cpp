#include "Common.hpp"
#include "Config.hpp"
#include "include/Core.hpp"

#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <map>

//#include <stdlib.h>	//atoi

using namespace std;

map<string, string> Options;
int v, help;

void usage() {
	fprintf(stderr, "Wrong answer\n");
}

void process_configuration() {
	Core CORE;
	cout << "LET'S DO SOME STUFF SCORES!!!" << endl;
	CORE.do_scores();
	cout << "[FINISHED]" << endl;
}

int main(int argc, char *argv[]) {

	const struct option long_opts[] =
	{
		{"v",	        no_argument,        0, 'v'},
		{"help",        no_argument,        0, 'h'},
		{"metric_set",  required_argument,  0, 'm'},
		{"eval",        required_argument,  0, 'e'},
		{"data_path",   required_argument,  0, 'd'},
		{0,0,0,0},
	};

	int opt, long_index;

	char* Asiya_config = argv[1];
	cout << "Config_file: " << string(Asiya_config) << endl;

	while( (opt = getopt_long_only(argc, argv, "", long_opts, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'e': Options["eval"] = optarg; break;
		case 'm': Options["metric_set"] = optarg; break;
		case 'h': help = 1; break;
		case 'v': Options["v"] = "3"; break;
		case 'd': Options["data_path"] = optarg; break;
		//default: usage();
		}
	}

    for (map<string,string>::const_iterator it = Options.begin(); it != Options.end(); it++) {
    	cout << it->first << " -> " << it->second << endl;
    }
    //if (Options["v"]) cout << "v" << " -> " << v << endl;
	//if (Options.find("v") == Options.end())

	if (help) usage;
/*
if ($options{"help"}) { usage2(); }
if ($options{"version"}) { die "$Common::appNAME v.$Common::appVERSION\n"; }

//--- if - metric_names, srclang and trglang, then no need for config file! --#
if ($options{"metric_names"} && $options{"srclang"} && $options{"trglang"} ){
	Metrics::print_metric_names( $options{"srclang"}, $options{"trglang"});
	exit;
}
*/
// -- check number of argments
int narg = 1;
if (argc < narg) usage;

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

Config CONFIG;
vector<string> metaeval_options, optimize_options;
// -- read config file --------------------------------------------------------------------------------
//Config CONFIG = read_configuration_options(Asiya_config, Options, metaeval_options, optimize_options);

CONFIG.read_configuration_options(Asiya_config, Options, metaeval_options, optimize_options);
/*, metaevaluation_params, optimization_params);*/

process_configuration();

// -- process configuration options -------------------------------------------------------------------
	//process_configuration(CONFIG);

/*
	cout << "# Args: " << argc << endl;
	for (int i = 0; i < argc; ++i) {
		cout << "\t#" << i << ": " << argv[i] << endl;
	}*/
}
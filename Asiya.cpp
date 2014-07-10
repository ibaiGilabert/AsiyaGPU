#include <iostream>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include <map>
#include "Common.hpp"
using namespace std;

map<string, string> Options;
int v, help;

void usage() {
	fprintf(stderr, "Wrong answer\n");
}

int main(int argc, char *argv[]) {

	const struct option long_opts[] =
	{
		{"v",	        no_argument,        0, 'v'},
		{"help",        no_argument,        0, 'h'},
		{"metric_set",  required_argument,  0, 'm'},
		{"eval",        required_argument,  0, 'e'},
		{0,0,0,0},
	};

	int opt, long_index;

	while( (opt = getopt_long_only(argc, argv, "", long_opts, &long_index)) != -1)
	{
		switch (opt)
		{
		case 'e': Options["eval"] = optarg; break;
		case 'm': Options["metric_set"] = optarg; break;
		case 'h': help = 1; break;
		case 'v': v = 1; break;
		//default: usage();
		}
	}

    for (map<string,string>::const_iterator it = Options.begin(); it != Options.end(); it++) {
    	cout << it->first << " -> " << it->second << endl;
    }
    if (v) cout << "v" << " -> " << v << endl;
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

char* Asiya_config = argv[1];

cout << "AppAuthor: " << appAUTHOR << endl;

// -- read config file --------------------------------------------------------------------------------
	//Config CONFIG = read_configuration_options(Asiya_config, options/*, metaevaluation_params, optimization_params*/);

// -- process configuration options -------------------------------------------------------------------
	//process_configuration(CONFIG);

/*
	cout << "# Args: " << argc << endl;
	for (int i = 0; i < argc; ++i) {
		cout << "\t#" << i << ": " << argv[i] << endl;
	}*/
}
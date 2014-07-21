#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <set>


#include "Common.hpp"
#include "NISTXML.hpp"
using namespace std;

struct Config {
	map<string, string> Hrefs, 		Hsystems;
	map<string, int> 	Hmetrics, 	wc, 	eval_schemes,	metaeval_criteria;
	vector<string> 		COMBO;	//metrics,	systems,		references;
	map<string, vector<vector<string> > > 	IDX;
	set<string> metrics,	systems,	references;

	string IQ_config, learn_scheme, ci, SORT, LANG, CASE, G, I ,O, SRCCASE, SRCLANG, src, tools, model;

	int do_metric_names,do_system_names,do_reference_names, do_refs, do_time;
	int O_STORAGE, verbose, debug, tsearch;
	int min_dist, setid_length, segid_length, docid_length;
	int TEX, TEX_table_count, TEX_font_size;
	int alignments, n_epochs, n_resamplings;
	int float_precision, float_length;
	int tokenize, remake;
	double train_prop, alfa;
	//map<,> segments
	//testbedid
    char* PATH;
};


void set_output_format();
void set_metrics();
void process_nist_file(Config &CONFIG, string file, string type);
void process_raw_file(Config &CONFIG, string file, string type);
Config default_config();
void read_selection();
Config process_config_file(char* config_file, map<string, string> options);
void process_command_line_options(Config &CONFIG, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options);
void validate_configuration();
void print_configuration_options();
void use_nist_output_format();
void use_default_metrics();
void use_DR_metrics();
void use_DRdoc_metrics();
void use_ULCh_metrics();
Config read_configuration_options(char* config_file, map<string, string >options, vector<string> metaeval_options, vector<string> optimize_options);
void terminate();
void finish_asiya();

#endif
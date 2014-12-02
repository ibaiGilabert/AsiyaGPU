#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "Common.hpp"

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Config {
private:
	//Default config
	void default_config();

	//Print attributes
	static void Dumper();

	void validate_configuration();


	//Setting attributes
	void process_config_file(char* config_file, map<string, string> options);
	void process_command_line_options(map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options);

public:
	static map<string, map<string, double> > max_score,	min_score;	//<granularity, [metric, value]>
	static map<string, int> 	Hmetrics, 	/*wc,*/ 	eval_schemes,	metaeval_schemes,	optimize_schemes,	metaeval_criteria,	optimize_criteria;
	//static vector<string> 		COMBO;	//metrics,	systems,		references;
	//static map<string, vector<vector<string> > > 	IDX;
	static set<string> Fmetrics,	metrics,	systems,	references;

	static string IQ_config, learn_scheme, ci, SORT, LANG, CASE, G, I ,O, SRCCASE, SRCLANG,/* src,*/ tools, model, parser, SRCparser;

	static int do_metric_names,do_system_names,do_reference_names, do_refs, do_time;
	static int O_STORAGE, verbose, debug, tsearch;
	static int min_dist, setid_length, sysid_length, segid_length, docid_length;
	static int TEX, TEX_table_count, TEX_font_size;
	static int alignments, n_epochs, n_resamplings;
	static int float_precision, float_length;
	static int tokenize, remake;
	static int num_process, serialize;
	static double train_prop, alfa;
	//map<,> segments
	//testbedid
    static char* PATH;



    /*void set_output_format();
	void set_metrics();



	void read_selection();
	void validate_configuration();
	void print_configuration_options();
	void use_nist_output_format();
	void use_default_metrics();
	void use_DR_metrics();
	void use_DRdoc_metrics();
	void use_ULCh_metrics();*/

	//Print methods
	/*static void printMapInt(const map<string, int> &m);
	static void printMapString(const map<string, string> &m);*/

	//Process
	void read_configuration_options(char* config_file, map<string, string >options, vector<string> metaeval_options, vector<string> optimize_options);

	//Ending
	void terminate();
	void finish_asiya();
};

#endif
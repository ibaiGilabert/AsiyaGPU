#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <set>


#include "Common.hpp"
#include "NISTXML.hpp"
using namespace std;

class Config {
private:
	//Default config
	void default_config();

	//Print attributes
	void Dumper();

	//Process configuration file
	void process_nist_file(string file, string type);
	void process_raw_file(string file, string type);

	//Setting attributes
	void process_config_file(char* config_file, map<string, string> options);
	void process_command_line_options(map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options);

public:
	static map<string, string> Hrefs, 		Hsystems;
	static map<string, int> 	Hmetrics, 	wc, 	eval_schemes,	metaeval_schemes,	optimize_schemes,	metaeval_criteria,	optimize_criteria;
	static vector<string> 		COMBO;	//metrics,	systems,		references;
	static map<string, vector<vector<string> > > 	IDX;
	static set<string> metrics,	systems,	references;

	static string IQ_config, learn_scheme, ci, SORT, LANG, CASE, G, I ,O, SRCCASE, SRCLANG, src, tools, model, parser, SRCparser;

	static int do_metric_names,do_system_names,do_reference_names, do_refs, do_time;
	static int O_STORAGE, verbose, debug, tsearch;
	static int min_dist, setid_length, segid_length, docid_length;
	static int TEX, TEX_table_count, TEX_font_size;
	static int alignments, n_epochs, n_resamplings;
	static int float_precision, float_length;
	static int tokenize, remake;
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

	//Process
	void read_configuration_options(char* config_file, map<string, string >options, vector<string> metaeval_options, vector<string> optimize_options);

	//Ending
	void terminate();
	void finish_asiya();
};

#endif
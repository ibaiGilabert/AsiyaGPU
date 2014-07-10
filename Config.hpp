#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include <Common.hpp>

struct Config {
	string IQ_config, learn_scheme, ci, SORT, LANG, CASE, PATH, G, I ,O, SRCCASE, SRCLANG, src, tools;
	int O_STORAGE, verbose, debug, tsearch,
	int do_metric_names, do_system_names, do_reference_names, do_refs, do_time
	int min_dist, setid_length, segid_length, docid_length
	int TEX, TEX_table_count, TEX_font_size;
	int alignments;
	int train_prop,
	int n_epochs, n_resamplings;
	int tokenize;
	int float_precision, float_length;
	int alfa, remake;
	vector<string> metrics, COMBO, model, systems, references;
	map<string, int> Hmetrics, wc, eval_schemes;
	map<string, string> Hrefs, Hsystems;
	map<string, vector<vector<string> > > IDX;
	//map<,> segments
	//testbedid
    char* PATH;
};


void set_output_format();
void set_metrics();
void process_nist_file();
void process_raw_file();
void default_config();
void read_selection();
void process_config_file(char* config_file, map<string, string> options);
void process_command_line_options();
void validate_configuration();
void print_configuration_options();
void use_nist_output_format();
void use_default_metrics();
void use_DR_metrics();
void use_DRdoc_metrics();
void use_ULCh_metrics();
void read_configuration_options(char* config_file, map<string, string >options, vector<string> metaeval_options, vector<string> optimize_options);
void terminate();
void finish_asiya();

#endif
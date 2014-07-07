#include <string>
#include <vector>
#include <map>

struct Config {
	string IQ_config, learn_scheme, ci, SORT, LANG, CASE, PATH, G, I ,O, SRCCASE, SRCLANG, src, tools;
	int O_STORAGE, verbose, debug, tsearch, 
	int do_metric_names, do_system_names, do_reference_names, do_refs, do_time
	int min_dist, setid_length, segid_length, docid_length
	int TEX, TEX_table_count, TEX_font_size;
	int alignments;
	int train_prop,
	int n_epochs, n_resamplings
	int tokenize;
	int float_precision, float_length;
	int alfa, remake;
	vector<string> metrics, COMBO, model, systems, references;
	map<string, int> Hmetrics, wc, eval_schemes;
	map<string, string> Hrefs, Hsystems;
	map<string, vector<vector<string> > > IDX;
	//map<,> segments
	//testbedid
	//ASIYA_HOME
};


void set_output_format();
void set_metrics();
void process_nist_file();
void process_raw_file();
void default_config();
void read_selection();
void process_config_file();
void process_command_line_options();
void validate_configuration();
void print_configuration_options();
void use_nist_output_format();
void use_default_metrics();
void use_DR_metrics();
void use_DRdoc_metrics();
void use_ULCh_metrics();
void read_configuration_options(config_file, options, metaeval_options, optimize_options);
void terminate();
void finish_asiya();

Config default_config() {
	
	Config CONFIG;
  
    my $ug = new Data::UUID;
    $CONFIG{testbedid} = $ug->create_str();
    $CONFIG{IQ_config} = "";
    $CONFIG{verbose} = 0;
    $CONFIG{debug} = 0;
    $CONFIG{tsearch} = 0;
    $CONFIG{tokenize} = $Common::tokenize;
    $CONFIG{do_metric_names} = 0;    
    $CONFIG{do_system_names} = 0;    
    $CONFIG{do_reference_names} = 0;
    $CONFIG{do_refs} = 0;
    $CONFIG{G} = $Common::G_DEFAULT;
    $CONFIG{I} = $Common::I_DEFAULT;
    $CONFIG{O} = $Common::O_DEFAULT;
    $CONFIG{O_STORAGE} = 1;
    $CONFIG{TEX} = 0;
    $CONFIG{TEX_table_count} = 0;
    $CONFIG{TEX_font_size} = TeX::get_font_size($Common::FS_DEFAULT);
    $CONFIG{SORT} = $Common::SORT_DEFAULT;
    $CONFIG{SRCLANG} = $Common::L_DEFAULT;
    $CONFIG{LANG} = $Common::L_DEFAULT;
    $CONFIG{SRCCASE} = $Common::CASE_DEFAULT;
    $CONFIG{CASE} = $Common::CASE_DEFAULT;
    $CONFIG{alfa} = $Common::ALFA_DEFAULT;
    $CONFIG{ci} = $Common::CI_DEFAULT;
    $CONFIG{n_resamplings} = $Common::N_RESAMPLINGS_DEFAULT;
    $CONFIG{float_length} = $Common::FLOAT_LENGTH_DEFAULT;
    $CONFIG{float_precision} = $Common::FLOAT_PRECISION_DEFAULT;
    $CONFIG{references} = [];
    $CONFIG{systems} = [];
    $CONFIG{metrics} = [];
    $CONFIG{segments} = {};
    $CONFIG{alignments} = 0;
    $CONFIG{learn_scheme} = "";
    $CONFIG{n_epochs} = $Common::N_EPOCHS_DEFAULT;
    $CONFIG{min_dist} = $Common::MIN_DIST_DEFAULT;
    $CONFIG{train_prop} = $Common::TRAINING_PROPORTION_DEFAULT;
    $CONFIG{model} = $Common::MODEL_DEFAULT;

    if (exists($ENV{ASIYA_HOME})) { $CONFIG{PATH} = $ENV{ASIYA_HOME}; }

    return CONFIG;
}

void process_config_file($config_file, $options) {

}

//$Asiya_config, \%options, \@metaevaluation_params, \@optimization_params);
void read_configuration_options(config_file, options, metaeval_options, optimize_options) {
    //description _ process configuration file and command-line options
    //param1  _ configuration file
    //param2  _ command-line options
    //param4  _ command-line optimization options

    my $CONFIG = process_config_file($config_file, $options);
    process_command_line_options($CONFIG, $options, $metaeval_options, $optimize_options);
    validate_configuration($CONFIG);
    print_configuration_options($CONFIG);
    
    return $CONFIG;
}
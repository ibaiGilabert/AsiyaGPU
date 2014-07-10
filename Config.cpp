#include <Config.hpp>
//using namespace std;


Config default_config() {

	Config CONFIG;

    /*my $ug = new Data::UUID;
    $CONFIG{testbedid} = $ug->create_str();*/
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
    //$CONFIG{TEX_font_size} = TeX::get_font_size($Common::FS_DEFAULT);
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

    char* path = getenv("ASIYA_HOME");
    if (path) CONFIG.PATH = path;//cout << "path: " << path << endl;

    return CONFIG;
}

void process_config_file(char* config_file, map<string, string> options) {
    string IQ_config(config_file);
    my $options = options;

    Config CONFIG = default_config();
    string METRICS = "";
    string SYSTEMS = "";
    string REFERENCES = "";
    string SEGMENTS = "";

    for (map<string,string>::const_iterator it = Options.begin(); it != Options.end(); it++) {
        switch(it->first) {
            case "metric_set": METRICS = it->second; break;
            case "system_set": SYSTEMS = it->second; break;
            case "reference_set": REFERENCES = it->second; break;
            case "test_cases": SEGMENTS = it->second; break;
            case "no_tok": CONFIG.tokenize = 0; break;
            case "remake": CONFIG.remake = 1; break;
            case "data_path":
                boost::regex re("\\/\\s*$");//, boost::regex::perl|boost::regex::icase);
                it->second = boost::regex_replace(it->second, re, ""); break;
        }
    }
    // string TOOLS = CONFIG.PATH;
    string TOOLS = "/home/soft/asiya/tools";
    boost::regex re2("/+");
    TOOLS = boost::regex_replace(TOOLS, re2, "/");

    boost::filesystem::path p (TOOLS);   // p reads clearer than argv[1] in the following code

    if (!is_directory(p)) {
        fprintf(stderr, "[%s] directory <%s> does not exist!\n", Common::appNAME, TOOLS.c_str());
        exit(1);
    }

    CONFIG.tools = TOOLS;

    boost::filesystem::path p ($Common::DATA_PATH/$Common::TMP);

    if (!is_directory(p)) { system "mkdir $Common::DATA_PATH/$Common::TMP"; } //TEMPORARY DIRECTORY

    map<string,string>::const_iterator it = Options.find("verbose");
    if (it != Options.end() { fprintf(stderr, "[%s] READING IQsetup config file <%s>...", Common::appNAME, IQ_config.c_str()); } //TEMPORARY DIRECTORY

    boost::filesystem::path p(IQ_config);
    if (!exists(p)) {
        char *appName,
        fprintf(stderr, "[%s] config file <%s> does not exist!\n", Common::appNAME, IQ_config.c_str());
        exit(1);
    }
    else { CONFIG.IQ_config = IQ_config; }

}

//$Asiya_config, \%options, \@metaevaluation_params, \@optimization_params);
void read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
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
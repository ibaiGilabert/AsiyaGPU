#include "Config.hpp"
#include <sstream>
#include <fstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

//using namespace std;


Config default_config() {

	Config CONFIG;

    /*my $ug = new Data::UUID;
    $CONFIG{testbedid} = $ug->create_str();*/
    CONFIG.IQ_config = "";
    CONFIG.verbose = 0;
    CONFIG.debug = 0;
    CONFIG.tsearch = 0;
    CONFIG.tokenize = tokenize;
    CONFIG.do_metric_names = 0;
    CONFIG.do_system_names = 0;
    CONFIG.do_reference_names = 0;
    CONFIG.do_refs = 0;
    CONFIG.G = G_DEFAULT;
    CONFIG.I = I_DEFAULT;
    CONFIG.O = O_DEFAULT;
    CONFIG.O_STORAGE = 1;
    CONFIG.TEX = 0;
    CONFIG.TEX_table_count = 0;
    //$CONFIG{TEX_font_size} = TeX::get_font_size(FS_DEFAULT);
    CONFIG.SORT = SORT_DEFAULT;
    CONFIG.SRCLANG = L_DEFAULT;
    CONFIG.LANG = L_DEFAULT;
    CONFIG.SRCCASE = CASE_DEFAULT;
    CONFIG.CASE = CASE_DEFAULT;
    CONFIG.alfa = ALFA_DEFAULT;
    CONFIG.ci = CI_DEFAULT;
    CONFIG.n_resamplings = N_RESAMPLINGS_DEFAULT;
    CONFIG.float_length = FLOAT_LENGTH_DEFAULT;
    CONFIG.float_precision = FLOAT_PRECISION_DEFAULT;
    /*CONFIG.references = s<string>();
    CONFIG.systems = vector<string>();
    CONFIG.metrics = vector<string>();*/
    //CONFIG.segments = {};
    CONFIG.alignments = 0;
    CONFIG.learn_scheme = "";
    CONFIG.n_epochs = N_EPOCHS_DEFAULT;
    CONFIG.min_dist = MIN_DIST_DEFAULT;
    CONFIG.train_prop = TRAINING_PROPORTION_DEFAULT;
    CONFIG.model = MODEL_DEFAULT;

    char* path = getenv("ASIYA_HOME");
    if (path) {
        cout << "path: " << string(path) << endl;
        CONFIG.PATH = path;   //cout << "path: " << path << endl;
    } else cout << "There's no path." << endl;

    return CONFIG;
}

void Dumper(Config CONFIG) {
    cout << "\tverbose -> " << CONFIG.verbose << endl;
    cout << "\tmin_dist -> " << CONFIG.min_dist << endl;
    cout << "\tmodel -> " << CONFIG.model << endl;
    cout << "\tdo_reference_names ->" << CONFIG.do_reference_names << endl;
    cout << "\ttrain_prop -> " << CONFIG.train_prop << endl;
    cout << "\tn_epochs -> " << CONFIG.n_epochs << endl;
    cout << "\tci -> " << CONFIG.ci << endl;
    cout << "\tTEX -> " << CONFIG.TEX << endl;
    cout << "\tdebug -> " << CONFIG.debug << endl;
    cout << "\tSORT -> " << CONFIG.SORT << endl;
    cout << "\tLANG -> " << CONFIG.LANG << endl;
    cout << "\ttokenize -> " << CONFIG.tokenize << endl;
    cout << "\tn_resamplings -> " << CONFIG.n_resamplings << endl;
    cout << "\tdo_metric_names -> " << CONFIG.do_metric_names << endl;
    cout << "\ttools -> " << CONFIG.tools << endl;
    cout << "\tCASE -> " << CONFIG.CASE << endl;
    cout << "\tfloat_precision -> " << CONFIG.float_precision << endl;
    cout << "\tPATH -> " << CONFIG.PATH << endl;
    cout << "\tfloat_length -> " << CONFIG.float_length << endl;
    cout << "\tdo_system_names -> " << CONFIG.do_system_names << endl;
    cout << "\tI -> " << CONFIG.I << endl;
    cout << "\tG -> " << CONFIG.G << endl;
    cout << "\talignments -> " << CONFIG.alignments << endl;
    cout << "\tTEX_table_count -> " << CONFIG.TEX_table_count << endl;
    cout << "\tO_STORAGE -> " << CONFIG.O_STORAGE << endl;
    cout << "\tO -> " << CONFIG.O << endl;
    cout << "\ttsearch -> " << CONFIG.tsearch << endl;
    cout << "\tSRCCASE -> " << CONFIG.SRCCASE << endl;
    cout << "\talfa -> " << CONFIG.alfa << endl;
    cout << "\tdo_refs -> " << CONFIG.do_refs << endl;
    cout << "\tSRCLANG -> " << CONFIG.SRCLANG << endl;
}

Config process_config_file(char* config_file, map<string, string> Options) {
    string IQ_config(config_file);
    //my $options = options;

    Config CONFIG = default_config();
    string METRICS = "";
    string SYSTEMS = "";
    string REFERENCES = "";
    string SEGMENTS = "";

    for (map<string,string>::iterator it = Options.begin(); it != Options.end(); it++) {
        if (it->first == "metric_set") METRICS = it->second;
        else if (it->first == "system_set") SYSTEMS = it->second;
        else if (it->first == "reference_set") REFERENCES = it->second;
        else if (it->first == "test_cases") SEGMENTS = it->second;
        else if (it->first == "no_tok") CONFIG.tokenize = 0;
        else if (it->first == "remake") CONFIG.remake = 1;
        else if (it->first == "data_path") {
                boost::regex re("\\/\\s*$");//, boost::regex::perl|boost::regex::icase);
                it->second = boost::regex_replace(it->second, re, "");
        }
    }

    // string TOOLS = CONFIG.PATH;
    string TOOLS = "/home/ibai/Escriptori/AsiyaGPU"; ///home/soft/asiya/tools";
    boost::regex re2("/+");
    TOOLS = boost::regex_replace(TOOLS, re2, "/");

    boost::filesystem::path p (TOOLS);   // p reads clearer than argv[1] in the following code

    if (!is_directory(p)) {
        fprintf(stderr, "[%s] directory <%s> does not exist!\n", appNAME.c_str(), TOOLS.c_str());
        exit(1);
    }

    CONFIG.tools = TOOLS;

    string path_aux = DATA_PATH; path_aux += "/"; path_aux += TMP;
    p = path_aux;

    if (!is_directory(p)) {
        stringstream ss;
        ss << "mkdir " << DATA_PATH << "/" << TMP;
        string s = ss.str();
        system(s.c_str());
    } //TEMPORARY DIRECTORY

    map<string,string>::const_iterator it = Options.find("verbose");
    if (it != Options.end()) {
        fprintf(stderr, "[%s] READING IQsetup config file <%s>...", appNAME.c_str(), IQ_config.c_str());
    } //TEMPORARY DIRECTORY

    p = IQ_config;
    if (!exists(p)) {
        fprintf(stderr, "[%s] config file <%s> does not exist!\n", appNAME.c_str(), IQ_config.c_str());
        exit(1);
    }
    else { CONFIG.IQ_config = IQ_config; }


    //cout << "CONFIG fins ara: " << endl;
    //Dumper(CONFIG);

    ifstream file(IQ_config);

    if (file) {
        boost::regex re("^[^#].*=.*");
        string str;
        int i = 0;

        while (getline(file, str)) {
            cout << "Linia " << ++i << endl;
            cout << '\t' << str << endl;
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str, results, re)) {
                cout << "\t That was a kind of line" << endl;

                string s = results[0];

                boost::regex reeq("=");
                boost::sregex_token_iterator i(s.begin(), s.end(), reeq, -1);
                //boost::sregex_token_iterator j;
                //int count = 0;
                pair<string, string> entry(*i++, *i++);
                /*while (i != j) {
                cout << *i++ << '|';
                count++;
                }*/
                cout << "\tTokens: " << entry.first << " | " << entry.second << endl;
                //std::transform(str.begin(), str.end(), str.begin(), ::tolower);

                // read input mode
                if (boost::to_lower(entry.second) == "input") {
                    if (boost::to_lower(entry.first) == I_NIST) CONFIG.I = I_NIST;
                    else CONFIG.I = I_RAW;
                }

                // read whole config
                string type = boost::to_lower(entry.second);
                if (type == "source" or type == "src" or type == "reference" or type == "ref" or type == "system" or type == "sys") {

                    string file = entry.first;

                    if (CONFIG.I == I_NIST) process_nist_file(CONFIG, file, type);
                    else process_raw_file(CONFIG, file, type);
                }
                else if (type == "srclang") {
                    if (rLANGS.find(entry.first) != rLANGS.end()) {
                        CONFIG.SRCLANG = boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED SOURCE LANGUAGE ('".%s."')!!\n", boost::to_lower(entry.first));
                    }
                }
                else if (type == "lang" or type == "trglang") {
                    if (rLANGS.find(entry.first) != rLANGS.end()) {
                        CONFIG.LANG = boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED TARGET LANGUAGE ('".%s."')!!\n", boost::to_lower(entry.first));
                    }
                }
                else if (type == "srccase") {
                    if (boost::to_lower(entry.first) == CASE_CI) {
                        CONFIG.SRCCASE = CASE_CI;
                    } else {
                        CONFIG.SRCCASE = CASE_CS;
                    }
                }
                else if (type == "trgcase" or type == "case") {
                    if (boost::to_lower(entry.first) == CASE_CI) {
                        CONFIG.CASE = CASE_CI;
                    } else {
                        CONFIG.CASE = CASE_CS;
                    }
                }
                else if (entry.second == METRICS) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.first.begin(), entry.first.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        CONFIG.Hmetrics[*i] = 1;
                        CONFIG.metrics.insert(*i);
                        /*pair<string, int> res = CONFIG.Hmetrics.insert( pair<string,int>(*i,1) );
                        if (res.second) CONFIG.metrics.push(*i);
                        else cout << "element " << *i << " already exist in Hmetrics." << endl;*/
                        ++i;
                    }
                }
                else if (entry.second == SYSTEMS) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.first.begin(), entry.first.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        CONFIG.metrics.insert(*i++);
                    }
                }
                else if (entry.second == REFERENCES) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.first.begin(), entry.first.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        CONFIG.references.insert(*i++);
                    }
                }
                else if (entry.second == SEGMENTS) {
                    //read_selection();
                }
            }
        }
        file.close();
    } else {
        fprintf(stderr, "couldn't open file: %s\n", IQ_config.c_str());
        exit(1);
    }
    if (CONFIG.verbose) fprintf(stderr, " [DONE]\n");

    //DUMP DUDE!

    return CONFIG;
}

//$Asiya_config, \%options, \@metaevaluation_params, \@optimization_params);
Config read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
    //description _ process configuration file and command-line options
    //param1  _ configuration file
    //param2  _ command-line options
    //param4  _ command-line optimization options

    Config CONFIG = process_config_file(config_file,options);

    /*my $CONFIG = process_config_file($config_file, $options);
    process_command_line_options($CONFIG, $options, $metaeval_options, $optimize_options);
    validate_configuration($CONFIG);
    print_configuration_options($CONFIG);*/

    return CONFIG;
}
#include "Config.hpp"
#include "include/TESTBED.hpp"
#include "include/TB_NIST.hpp"
#include "include/TB_RAW.hpp"

#include <sstream>
#include <fstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

    /*string Config::IQ_config;
    int Config::verbose;
    int Config::debug;
    int Config::tsearch;
    int Config::tokenize;
    int Config::do_metric_names;
    int Config::do_system_names;
    int Config::do_reference_names;
    int Config::do_refs;
    string Config::G;
    string Config::I;
    string Config::O;
    int Config::O_STORAGE;
    int Config::TEX;
    int Config::TEX_table_count;
    string Config::SORT;
    string Config::SRCLANG;
    string Config::LANG;
    string Config::SRCCASE;
    string Config::CASE;
    double Config::alfa;
    string Config::ci;
    int Config::n_resamplings;
    int Config::float_length;
    int Config::float_precision;
    int Config::alignments;
    string Config::learn_scheme;
    int Config::n_epochs;
    int Config::min_dist;
    double Config::train_prop;
    string Config::model;

    char* Config::PATH;*/
    set<string>                 Config::Hmetrics,           Config::eval_schemes,       Config::metaeval_schemes;
    map<string, int>            Config::optimize_schemes,   Config::metaeval_criteria,  Config::optimize_criteria;
    set<string>                 Config::Fmetrics,           Config::metrics,            Config::systems,            Config::references;
    //vector<string>              Config::COMBO;  //metrics,  systems,        references;

    string Config::IQ_config,   Config::learn_scheme,   Config::ci;
    string Config::SORT,        Config::LANG,           Config::CASE;
    string Config::G,           Config::I,              Config::O;
    string Config::SRCCASE,     Config::SRCLANG;
    string Config::tools,       Config::model;
    string Config::parser,      Config::SRCparser;

    int Config::do_metric_names,    Config::do_system_names,    Config::do_reference_names, Config::do_refs,        Config::do_time;
    int Config::min_dist,           Config::setid_length,       Config::sysid_length,       Config::segid_length,   Config::docid_length;
    int Config::TEX,                Config::TEX_table_count,    Config::TEX_font_size,      Config::alignments;
    int Config::float_precision,    Config::float_length,       Config::n_epochs,           Config::n_resamplings;
    int Config::O_STORAGE,          Config::verbose,            Config::debug,              Config::tsearch;
    int Config::tokenize,           Config::remake;
    int Config::num_process,        Config::serialize;

    double Config::train_prop,      Config::alfa;
    //map<,> segments
    //testbedid
    char* Config::PATH;

void Config::default_config() {

	//Config CONFIG;

    /*my $ug = new Data::UUID;
    $CONFIG{testbedid} = $ug->create_str();*/
    Config::IQ_config = "";
    Config::verbose = 0;
    Config::debug = 0;
    Config::tsearch = 0;
    Config::tokenize = Common::tokenize;
    Config::do_metric_names = 0;
    Config::do_system_names = 0;
    Config::do_reference_names = 0;
    Config::do_refs = 0;
    Config::G = Common::G_DEFAULT;
    Config::I = Common::I_DEFAULT;
    Config::O = Common::O_DEFAULT;
    Config::O_STORAGE = 1;
    Config::TEX = 0;
    Config::TEX_table_count = 0;
    //$CONFIG{TEX_font_size} = TeX::get_font_size(FS_DEFAULT);
    Config::SORT = Common::SORT_DEFAULT;
    Config::SRCLANG = Common::L_DEFAULT;
    Config::LANG = Common::L_DEFAULT;
    Config::SRCCASE = Common::CASE_DEFAULT;
    Config::CASE = Common::CASE_DEFAULT;
    Config::alfa = Common::ALFA_DEFAULT;
    Config::ci = Common::CI_DEFAULT;
    Config::n_resamplings = Common::N_RESAMPLINGS_DEFAULT;
    Config::float_length = Common::FLOAT_LENGTH_DEFAULT;
    Config::float_precision = Common::FLOAT_PRECISION_DEFAULT;
    /*Config::references = s<string>();
    Config::systems = vector<string>();
    Config::metrics = vector<string>();*/
    //Config::segments = {};
    Config::alignments = 0;
    Config::learn_scheme = "";
    Config::n_epochs = Common::N_EPOCHS_DEFAULT;
    Config::min_dist = Common::MIN_DIST_DEFAULT;
    Config::train_prop = Common::TRAINING_PROPORTION_DEFAULT;
    Config::model = Common::MODEL_DEFAULT;
    Config::num_process = 0;
    Config::serialize = 0;

    char* path = getenv("ASIYA_HOME");
    if (path) {
        //cout << "path: " << string(path) << endl;
        Config::PATH = path;   //cout << "path: " << path << endl;
    }
    //return CONFIG;
}

/*void Config::printMapInt(const map<string, int> &m) {
    cout << "---------------------" << endl;
    for (map<string, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
        cout << "\t" << it->first << " -> " << it->second << endl;
    }
    cout << "---------------------" << endl;
}

void Config::printMapString(const map<string, string> &m) {
    cout << "---------------------" << endl;
    for (map<string, string>::const_iterator it = m.begin(); it != m.end(); ++it) {
        cout << "\t" << it->first << " -> " << it->second << endl;
    }
    cout << "---------------------" << endl;
}*/

void Config::Dumper() {
    cout << "\tverbose -> " << Config::verbose << endl;
    cout << "\tmin_dist -> " << Config::min_dist << endl;
    cout << "\tmodel -> " << Config::model << endl;
    cout << "\tlearn_scheme -> " << Config::learn_scheme << endl;
    cout << "\tdo_reference_names ->" << Config::do_reference_names << endl;
    cout << "\ttrain_prop -> " << Config::train_prop << endl;
    cout << "\tn_epochs -> " << Config::n_epochs << endl;
    cout << "\tci -> " << Config::ci << endl;
    cout << "\tTEX -> " << Config::TEX << endl;
    cout << "\tsystems -> " << endl;
    for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tdebug -> " << Config::debug << endl;
    cout << "\tSORT -> " << Config::SORT << endl;
    cout << "\tLANG -> " << Config::LANG << endl;
    cout << "\ttokenize -> " << Config::tokenize << endl;
    cout << "\tHmetrics -> (" << Config::Hmetrics.size() << ")" << endl;
    for (set<string>::const_iterator it = Config::Hmetrics.begin(); it != Config::Hmetrics.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tn_resamplings -> " << Config::n_resamplings << endl;
    cout << "\tdo_metric_names -> " << Config::do_metric_names << endl;
    //cout << "\tsrc -> " << Config::src << endl;
    cout << "\ttools -> " << Config::tools << endl;
    cout << "\tCASE -> " << Config::CASE << endl;
    cout << "\tfloat_precision -> " << Config::float_precision << endl;
    cout << "\tPATH -> " << Config::PATH << endl;
    cout << "\tfloat_length -> " << Config::float_length << endl;
    cout << "\tdo_system_names -> " << Config::do_system_names << endl;
    cout << "\tI -> " << Config::I << endl;
    cout << "\tG -> " << Config::G << endl;
    cout << "\tHrefs -> " << endl;
    /*for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }*/
    cout << "\talignments -> " << Config::alignments << endl;
    cout << "\tTEX_table_count -> " << Config::TEX_table_count << endl;
    //cout << segments
    cout << "\tIQ_config -> " << Config::IQ_config << endl;
    //cout << TEX_font_size
    cout << "\treferences -> (" << Config::references.size() << ")" << endl;
    for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tO_STORAGE -> " << Config::O_STORAGE << endl;
    cout << "\tmetrics-> (" << Config::metrics.size() << ")" << endl;
    for (set<string>::const_iterator it = Config::metrics.begin(); it != Config::metrics.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    /*cout << "\teval_schemes-> (" << Config::Hmetrics.size() << ")" << endl;
    for (map<string, int>::const_iterator it = Config::eval_schemes.begin(); it != Config::eval_schemes.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }*/
    cout << "\tO -> " << Config::O << endl;
    cout << "\ttsearch -> " << Config::tsearch << endl;
    cout << "\tSRCCASE -> " << Config::SRCCASE << endl;
    cout << "\talfa -> " << Config::alfa << endl;
    cout << "\tdo_refs -> " << Config::do_refs << endl;
    cout << "\tSRCLANG -> " << Config::SRCLANG << endl;
}

void Config::process_command_line_options(map<string, string> Options, vector<string> metaeval_options, vector<string> optimize_options) {
    if (Options.find("paralel") != Options.end() and !atoi(Options["paralel"].c_str())) {
        fprintf(stderr, "[ERROR] Enter a valid number of processes.\n"); exit(1);
    }
    else if (atoi(Options["paralel"].c_str()) < 1) {
        fprintf(stderr, "Paralel (%s) -> No paralelism\n", Options["paralel"].c_str());
    }
    else Config::num_process = atoi(Options["paralel"].c_str());

    if (Options.find("serialize") != Options.end()) {
        Config::serialize = atoi(Options["serialize"].c_str());
        fprintf(stderr, "SERIALIZE\n");
    } else { fprintf(stderr, "DO NOT SERIALIZE\n"); }

    if (Options.find("v") != Options.end()) Config::verbose = 1;//atoi(Options["v"].c_str());
    else Config::verbose = 0;   // no cal ja que el default ja es = 0

    if (Options.find("d") != Options.end()) Config::debug = atoi(Options["d"].c_str());
    else Config::debug = 0;

    if (Options.find("remake") != Options.end()) Config::remake = atoi(Options["remake"].c_str());
    else Config::remake = 0;

    if (Options.find("time") != Options.end()) Config::do_time = 1; //atoi(Options["time"].c_str());
    else Config::do_time = 0;

    if (Options.find("no_tok") != Options.end()) Config::tokenize = 0;
    if (Options.find("tsearch") != Options.end()) Config::tsearch = 1;
    else Config::tsearch = 0;
    //if (Options.find("testbedid") != Options.end()) Config::testbedid = Options["testbedid"];
    if (Options.find("m") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["m"].begin(), Options["m"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            //fprintf(stderr, "Added%s to metrics (command line options)\n", i->c_str());
            Config::metrics.insert(*i);
            //Config::Hmetrics[*i] = 1;
            Config::Hmetrics.insert(*i);
            ++i;
        }
    }
    if (Options.find("s") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["s"].begin(), Options["s"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            Config::systems.insert(*i);
            //cout << "Added " << *i << " to systems (command line options)" << endl;
            ++i;
        }
    }
    if (Options.find("r") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["r"].begin(), Options["r"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            Config::references.insert(*i);
            //cout << "Added " << *i << " to references (command line options)" << endl;
            ++i;
        }
    }
    if (Options.find("t") != Options.end()) {
        //read_selection
    }
    if (Options.find("eval") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["eval"].begin(), Options["eval"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            string aux = *i;

            if (Common::eval_schemes.find(aux) != Common::eval_schemes.end()) Config::eval_schemes.insert(aux);
            else { fprintf(stderr, "[ERROR] unknown evaluation method '%s'\n", aux.c_str()); exit(1); }

            //cout << "Added " << *i << " to eval_schemes (command line options)" << endl;
            ++i;
        }
    }
    if (metaeval_options.size() > 0) {}

    if (optimize_options.size() > 0) {}

    if (Options.find("include_refs") != Options.end()) Config::do_refs = atoi(Options["include_refs"].c_str());
    if (Options.find("align") != Options.end()) Config::alignments= atoi(Options["align"].c_str());
    if (Options.find("metric_names") != Options.end()) Config::do_metric_names = atoi(Options["metric_names"].c_str());
    if (Options.find("system_names") != Options.end()) Config::do_system_names = atoi(Options["system_names"].c_str());
    if (Options.find("reference_names") != Options.end()) Config::do_reference_names = atoi(Options["referece_names"].c_str());
    if (Options.find("g") != Options.end()) Config::G = Options["g"];
    if (Options.find("o") != Options.end()) Config::O = Options["o"];
    if (Options.find("no_storage") != Options.end()) Config::O_STORAGE = atoi(Options["no_storage"].c_str());
    if (Options.find("sorted") != Options.end()) Config::SORT = Options["sorted"];
    if (Options.find("tex") != Options.end()) Config::TEX = atoi(Options["tex"].c_str());
    if (Options.find("pdf") != Options.end()) { /*Config::PDF = Options["pdf"]; Config::TEX_REPORT = "";*/ }
    //if (Options.find("font_size") != Options.end()) Config::TEX_font_size = Options["font_size"];
    if (Options.find("srclang") != Options.end()) {
        string aux = Options["srclang"];
        boost::to_lower(aux);
        if (Common::rLANGS.find(aux) != Common::rLANGS.end()) Config::SRCLANG = aux;
        else { fprintf(stderr, "[ERROR] UNSUPPORTED SOURCE LANGUAGE ('%s'))!!\n", aux.c_str()); exit(1); }
    }
    if (Options.find("trclang") != Options.end()) {
        string aux = Options["trclang"];
        boost::to_lower(aux);
        if (Common::rLANGS.find(aux) != Common::rLANGS.end()) Config::LANG = aux;
        else { fprintf(stderr, "[ERROR] UNSUPPORTED TARGET LANGUAGE ('%s'))!!\n", aux.c_str()); exit(1); }
    }
    if (Options.find("srccase") != Options.end()) {
        string aux = Options["srccase"];
        boost::to_lower(aux);
        if (aux == Common::CASE_CI) Config::SRCCASE = Common::CASE_CI;
        else Config::SRCCASE = Common::CASE_CS;
    }
    if (Options.find("trgcase") != Options.end()) {
        string aux = Options["trgcase"];
        boost::to_lower(aux);
        if (aux == Common::CASE_CI) Config::CASE = Common::CASE_CI;
        else Config::CASE = Common::CASE_CS;
    }
    if (Options.find("float_length") != Options.end()) Config::float_length = atoi(Options["float_length"].c_str());
    if (Options.find("float_precision") != Options.end()) Config::float_precision = atoi(Options["float_precision"].c_str());

    // META-EVALUATION PARAMETERS ---------------------------------------------------
    /*if (Options.find("assessments") != Options.end()) {
       //(my $assesstype, $CONFIG->{assessments}) = Assessments::read_NISTCSV_file($options->{"assessments"}, $CONFIG->{IDX}->{"source"}, $CONFIG->{verbose});
       //$CONFIG->{avgassessments} = Assessments::average_assessments( $assesstype, $CONFIG->{assessments} );    }*/
    if (Options.find("alfa") != Options.end()) Config::alfa = atof(Options["alfa"].c_str());
    if (Options.find("ci") != Options.end()) {
        string aux = Options["ci"];
        if (Common::rCI.find(aux) == Common::rCI.end()) { fprintf(stderr, "[ERROR] unknown confidence-interval computation method '%s'!!\n", aux.c_str()); exit(1); }
        Config::ci = aux;
    }
    if (Options.find("n_resamplings") != Options.end()) Config::n_resamplings = atoi(Options["n_resamplings"].c_str());

    // LEARNING PARAMETERS ----------------------------------------------------------
    if (Options.find("learn") != Options.end()) Config::learn_scheme = Options["learn"];
    if (Options.find("n_epochs") != Options.end()) Config::n_epochs = atoi(Options["n_epochs"].c_str());
    if (Options.find("min_dist") != Options.end()) Config::min_dist = atoi(Options["min_dist"].c_str());
    if (Options.find("train_prop") != Options.end()) Config::train_prop = atof(Options["train_prop"].c_str());
    if (Options.find("model") != Options.end()) Config::model = Options["model"];
    else Config::model = Common::DATA_PATH + "/" + Common::MODEL_DEFAULT;
}

void Config::process_config_file(char* config_file, map<string, string> Options) {
    string IQ_config(config_file);
    //my $options = options;

    //Config CONFIG = default_config();
    //Config::default_config();

    string METRICS = "";
    string SYSTEMS = "";
    string REFERENCES = "";
    string SEGMENTS = "";

    for (map<string,string>::iterator it = Options.begin(); it != Options.end(); it++) {
        if (it->first == "metric_set") METRICS = it->second;
        else if (it->first == "system_set") SYSTEMS = it->second;
        else if (it->first == "reference_set") REFERENCES = it->second;
        else if (it->first == "test_cases") SEGMENTS = it->second;
        else if (it->first == "no_tok") Config::tokenize = 0;
        else if (it->first == "remake") Config::remake = 1;
        else if (it->first == "data_path") {
                boost::regex re("\\/\\s*$");//, boost::regex::perl|boost::regex::icase);
                it->second = boost::regex_replace(it->second, re, "");
                Common::DATA_PATH = it->second;
        }
    }

    fprintf(stderr, "METRICS = %s\n", METRICS.c_str());
    fprintf(stderr, "SYSTEMS = %s\n", SYSTEMS.c_str());
    fprintf(stderr, "REFERENCES = %s\n", REFERENCES.c_str());

    // string TOOLS = Config::PATH;
    string TOOLS = "/home/soft/asiya/tools";
    boost::regex re2("/+");
    TOOLS = boost::regex_replace(TOOLS, re2, "/");

    //fprintf(stderr, "[Config]: replaced tools:(%s)\n", TOOLS.c_str());
    boost::filesystem::path p (TOOLS);   // p reads clearer than argv[1] in the following code
    //fprintf(stderr, "[Config]: pathed\n");

    if (!is_directory(p)) { fprintf(stderr, "[%s] directory <%s> does not exist!\n", Common::appNAME.c_str(), TOOLS.c_str()); exit(1); }

    Config::tools = TOOLS;

    //fprintf(stderr, "[Config]: repathed\n");
    string path_aux = Common::DATA_PATH; path_aux += "/"; path_aux += Common::TMP;
    p = boost::filesystem::path(path_aux);
    //fprintf(stderr, "[Config]: check directory path_aux:(%s)\n", path_aux.c_str());

    if (!is_directory(p)) {
        string s = "mkdir " + Common::DATA_PATH + "/" + Common::TMP;
        system(s.c_str());
        //fprintf(stderr, "tmp:(%s) create\n", s.c_str());

        /*for (int i = 1; i <= Config::num_process; ++i) {
            stringstream ss;
            ss << s << "/" << i;
            system(ss.str().c_str());
        }*/

    } //TEMPORARY DIRECTORY

    if (Options.find("verbose") != Options.end()) fprintf(stderr, "[%s] READING ASIYA setup config file <%s>...", Common::appNAME.c_str(), config_file); //TEMPORARY DIRECTORY
    //fprintf(stderr, "[Config]: tmp created\n");

    p = boost::filesystem::path(IQ_config);
    if (!exists(p)) { fprintf(stderr, "[%s] config file <%s> does not exist!\n", Common::appNAME.c_str(), config_file); exit(1); }
    else Config::IQ_config = IQ_config;


    ifstream file;              //read input mode
    file.open(config_file);
    //fprintf(stderr, "[Config]: OK, let's read da confics\n");
    if (file) {
        boost::regex re("^[^#].*=.*");
        string str;
        int i = 0;

        while (getline(file, str)) {
            //cout << "Linia " << ++i << endl;
            //cout << '\t' << str << endl;
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str, results, re)) {
                //cout << "\t That was a kind of line" << endl;

                string s = results[0];

                boost::regex reeq("=");
                boost::sregex_token_iterator i(s.begin(), s.end(), reeq, -1);

                string type = *i++;
                string data = *i;

                boost::regex re("\\s*$");//, boost::regex::perl|boost::regex::icase);
                boost::regex re2("^\\s*");//, boost::regex::perl|boost::regex::icase);

                type = boost::regex_replace(type, re, "");
                data = boost::regex_replace(data, re2, "");
                //fprintf(stderr, "[Config]: replaced\n");

                boost::to_lower(type);
                boost::to_lower(data);
                //fprintf(stderr, "[Config]: lowered type: %s/ data: %s\n", type.c_str(), data.c_str());

                if (type == "input") {
                    if (data == Common::I_NIST) {
                        fprintf(stderr, "[INPUT DATA NIST]\n");
                        Config::I = Common::I_NIST;
                    }
                    else {
                        fprintf(stderr, "[INPUT DATA RAW]\n");
                        Config::I = Common::I_RAW;
                    }
                }
            }
        }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", config_file); exit(1); }

    // read whole config
    file.open(config_file);     //(IQ_config.c_str());
    if (file) {
        boost::regex re("^[^#].*=.*");
        string str;
        int i = 0;
        while (getline(file, str)) {
            //cout << "Linia " << ++i << endl;
            //cout << '\t' << str << endl;
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str, results, re)) {
                //cout << "\t That was a kind of line" << endl;

                string s = results[0];

                boost::regex reeq("=");
                boost::sregex_token_iterator i(s.begin(), s.end(), reeq, -1);

                string type, file;
                type = *i++;
                file = *i;

                boost::regex re("\\s*$"); //, boost::regex::perl|boost::regex::icase);
                boost::regex re2("^\\s*"); //, boost::regex::perl|boost::regex::icase);
                type = boost::regex_replace(type, re, "");
                type = boost::regex_replace(type, re2, "");
                file = boost::regex_replace(file, re, "");
                file = boost::regex_replace(file, re2, "");
                //fprintf(stderr, "[Config]: replaced\n");

                pair<string, string> entry(type, file);

                string file_cs = file;
                boost::to_lower(type);
                boost::to_lower(file_cs);
                //fprintf(stderr, "[Config]: lowered type: %s/ file_cs: %s\n", type.c_str(), file_cs.c_str());
                if (type == "source" or type == "src" or type == "reference" or type == "ref" or type == "system" or type == "sys") {

                    //string file = entry.first;
                    if (Config::I == Common::I_NIST) {
                        TB_NIST tb_nist;
                        string proc_file = tb_nist.process_file(file, type);

                        if (Config::num_process) {
                            //fprintf(stderr, "[Config]: to split <%s>\n", proc_file.c_str());
                            tb_nist.split_txt_idx(proc_file);
                            //fprintf(stderr, "[Config]: splited\n");
                        }
                    }
                    else  {
                        TB_RAW tb_raw;
                        string proc_file = tb_raw.process_file(file, type);

                        if (Config::num_process) {
                            //printf(stderr, "[Config]: to split <%s>\n", proc_file.c_str());
                            tb_raw.split_txt_idx(proc_file);
                            //fprintf(stderr, "[Config]: splited\n");
                        }
                    }
                }
                else if (type == "srclang") {
                    if (Common::rLANGS.find(file_cs) != Common::rLANGS.end()) {
                        Config::SRCLANG = file_cs; //boost::to_lower(entry.first);
                    }
                    else { fprintf(stderr,"[ERROR] UNSUPPORTED SOURCE LANGUAGE ('.%s.')!!\n", file_cs.c_str()); }
                    //fprintf(stderr, "# srclang readed #\n");
                }
                else if (type == "lang" or type == "trglang") {
                    if (Common::rLANGS.find(file_cs) != Common::rLANGS.end()) {
                        Config::LANG = file_cs; //boost::to_lower(entry.first);
                    }
                    else { fprintf(stderr,"[ERROR] UNSUPPORTED TARGET LANGUAGE ('.%s.')!!\n", file_cs.c_str()); }
                    //fprintf(stderr, "# lang or trglang readed #\n");
                }
                else if (type == "srccase") {
                    if (file_cs == Common::CASE_CI)
                        Config::SRCCASE = Common::CASE_CI;
                    else
                        Config::SRCCASE = Common::CASE_CS;
                }
                else if (type == "trgcase" or type == "case") {
                    if (file_cs == Common::CASE_CI)
                        Config::CASE = Common::CASE_CI;
                    else
                        Config::CASE = Common::CASE_CS;

                    //fprintf(stderr, "# case or trgcase readed #\n");
                }
                else if (entry.first == METRICS) {
                    boost::regex reeq(" ");     //alternative to splitting: strtok, check it out if you hate boost...
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        //cout << "Add " << *i << " to Hmetrics/metrics" << endl;
                        //fprintf(stderr, "Add %s to Hmetrics/metrics\n", i->c_str());
                        //Config::Hmetrics[*i] = 1;
                        Config::Hmetrics.insert(*i);
                        Config::metrics.insert(*i);
                        ++i;
                    }
                    //fprintf(stderr, "# metrics %s readed #\n", METRICS.c_str());
                }
                else if (entry.first == SYSTEMS) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        //fprintf(stderr, "Add %s to systems\n", i->c_str());
                        Config::systems.insert(*i++);
                    }
                    //fprintf(stderr, "# systems %s readed #\n", SYSTEMS.c_str());
                }
                else if (entry.first == REFERENCES) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        //fprintf(stderr, "Add %s to references\n", i->c_str());
                        Config::references.insert(*i++);
                    }
                    //fprintf(stderr, "# references %s readed #\n", REFERENCES.c_str());
                }
                else if (entry.first == SEGMENTS) {
                    //map<s> h = (,read_selection(options["t"]));
                }
            }
        }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", config_file); exit(1); }

    if (Config::verbose) fprintf(stderr, " [DONE]\n");
}

void Config::validate_configuration() {
    // description _ validate configuration (through simple verifications on mandatory arguments and option values)

    if (Config::PATH == "") { fprintf(stderr, "[ERROR] PATH undefined\n"); exit(1); }

    boost::filesystem::path p(Config::PATH);   // p reads clearer than argv[1] in the following code
    if (!is_directory(p)) { fprintf(stderr, "[ERROR] PATH directory <%s> does not exist!\n", Config::PATH); exit(1); }

    boost::filesystem::path t(Config::tools);   // p reads clearer than argv[1] in the following code
    if (!is_directory(t)) { fprintf(stderr, "[ERROR] PATH directory <%s> does not exist!\n", Config::tools.c_str()); exit(1); }

    if (!Config::references.empty()) {
        for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {
            if (TESTBED::Hrefs.find(*it) == TESTBED::Hrefs.end()) { fprintf(stderr, "[ERROR] reference '%s' not in test suite!!\n", it->c_str()); exit(1); }
        }
    } else {
        for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) Config::references.insert(it->first);
    }

    if (!Config::systems.empty()) {
        for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
            if (TESTBED::Hsystems.find(*it) == TESTBED::Hsystems.end()) { fprintf(stderr, "[ERROR] system '%s' not in test suite!!\n", it->c_str()); exit(1); }
        }
    } else {
        for (map<string, string>::const_iterator it = TESTBED::Hsystems.begin(); it != TESTBED::Hsystems.end(); ++it) Config::systems.insert(it->first);
        if (Config::systems.empty()) { fprintf(stderr, "[ERROR] set of systems undefined!!\n"); exit(1); }
    }
    /*if (!Config::Hmetrics.empty()) {
        //metric_set = Metrics::load_metric_set();
        //if ()
    } else use_default_metrics;*/

    int max_system_name_length = 0;
    for(set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
        if (it->size() > max_system_name_length) max_system_name_length = it->size();
    }
    for(set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {
        if (it->size() > max_system_name_length) max_system_name_length = it->size();
    }
    Config::sysid_length = max_system_name_length;
    if (Config::sysid_length < Common::MIN_ID_LENGTH) Config::sysid_length = Common::MIN_ID_LENGTH;

    Config::setid_length = TESTBED::get_setid_length(*Config::systems.begin());
    if (Config::setid_length < Common::MIN_ID_LENGTH) Config::setid_length = Common::MIN_ID_LENGTH;

    Config::docid_length = TESTBED::get_max_docid_length(*Config::systems.begin());
    if (Config::docid_length < Common::MIN_ID_LENGTH) Config::docid_length = Common::MIN_ID_LENGTH;

    Config::segid_length = TESTBED::get_max_segid_length(*Config::systems.begin());
    if (Config::segid_length < Common::MIN_ID_LENGTH) Config::segid_length = Common::MIN_ID_LENGTH;

    if (Config::num_process) {
        for (set<string>::const_iterator it = Config::metrics.begin(); it != Config::metrics.end(); ++it) {
            boost::regex re_BLEU("^BLEU.*");
            boost::regex re_GTM("^GTM.*");
            boost::regex re_NIST("^NIST.*");
            boost::regex re_ROUGE("^ROUGE.*");
            boost::regex re_WER("^.*WER.*");
            boost::regex re_PER("^.*PER.*");
            boost::regex re_TER("^.*TER.*");
            boost::regex re_LEM("^LeM$");
            boost::regex re_METEOR("^METEOR.*");
            boost::regex re_NGRAM("^NGRAM.*");
            boost::regex re_ESA("^ESA.*");
            boost::regex re_Ol("^Ol.*");
            boost::regex re_Pl("^Pl.*");
            boost::regex re_Fl("^Fl.*");
            boost::regex re_Rl("^Rl.*");
            boost::regex re_SP("^SP.*");
            boost::regex re_CE("^CE.*");
            boost::regex re_NE("^NE.*");
            //boost::regex re_CP("^CP.*");
            boost::regex re_SR("^SR.*");

            /*boost::regex re_SP("SP");
            boost::regex re_CP("CP");
            boost::regex re_DP("DP");
            boost::regex re_SR("SR");
            boost::regex re_NE("NE");
            boost::regex re_ALGN("ALGN");*/

            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(*it, results, re_BLEU)) Config::Fmetrics.insert("BLEU");
            else if (boost::regex_match(*it, results, re_GTM)) Config::Fmetrics.insert("GTM");
            else if (boost::regex_match(*it, results, re_NIST)) Config::Fmetrics.insert("NIST");
            else if (boost::regex_match(*it, results, re_ROUGE)) Config::Fmetrics.insert("ROUGE");
            else if (boost::regex_match(*it, results, re_WER)) Config::Fmetrics.insert("WER");
            else if (boost::regex_match(*it, results, re_PER)) Config::Fmetrics.insert("PER");
            else if (boost::regex_match(*it, results, re_TER)) Config::Fmetrics.insert("TER");
            else if (boost::regex_match(*it, results, re_LEM)) Config::Fmetrics.insert("LeM");
            else if (boost::regex_match(*it, results, re_METEOR)) Config::Fmetrics.insert("METEOR");
            else if (boost::regex_match(*it, results, re_NGRAM)) Config::Fmetrics.insert("NGRAM");
            else if (boost::regex_match(*it, results, re_ESA)) Config::Fmetrics.insert("ESA");
            else if (boost::regex_match(*it, results, re_Ol)) Config::Fmetrics.insert("Ol");
            else if (boost::regex_match(*it, results, re_Pl)) Config::Fmetrics.insert("Pl");
            else if (boost::regex_match(*it, results, re_Fl)) Config::Fmetrics.insert("Fl");
            else if (boost::regex_match(*it, results, re_Rl)) Config::Fmetrics.insert("Rl");
            else if (boost::regex_match(*it, results, re_SP)) Config::Fmetrics.insert("SP");
            else if (boost::regex_match(*it, results, re_CE)) Config::Fmetrics.insert("CE");
            else if (boost::regex_match(*it, results, re_NE)) Config::Fmetrics.insert("NE");
            //else if (boost::regex_match(*it, results, re_CP)) Config::Fmetrics.insert("CP");
            else if (boost::regex_match(*it, results, re_SR)) Config::Fmetrics.insert("SR");

        }

        fprintf(stderr, "METRICS (families): ");
        for (set<string>::const_iterator it = Config::Fmetrics.begin(); it != Config::Fmetrics.end(); ++it) {
            fprintf(stderr, "%s, ", it->c_str());
        }
        fprintf(stderr, "\n");
    }
    /*cout << "-------" << endl;
    cout << "\tsysid: " << Config::sysid_length << endl;
    cout << "\tsetid: " << Config::setid_length << endl;
    cout << "\tdocid: " << Config::docid_length << endl;
    cout << "\tsegid: " << Config::segid_length << endl;
    cout << "-------" << endl;*/

    //check the length of the files
}

void Config::read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
    //description _ process configuration file and command-line options
    //param1  _ configuration file
    //param2  _ command-line options
    //param4  _ command-line optimization options
    Config::default_config();

    process_command_line_options(options, metaeval_options, optimize_options);
    process_config_file(config_file, options);
    validate_configuration();

}

void Config::terminate() {
    //description _ terminates, if the given configuration parameters determine so
    if (Config::do_metric_names or Config::do_system_names or Config::do_reference_names) exit(0);
}

void Config::finish_asiya() {
    //description _ clean the workspace and announces the end of the execution

    //if (-d "$Common::DATA_PATH/$Common::TMP") { system "rm -rf $Common::DATA_PATH/$Common::TMP"; } #TEMPORARY DIRECTORY
    if (verbose) fprintf(stderr, "[FINISHED]\n");
}

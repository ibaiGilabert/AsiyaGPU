#include "Config.hpp"
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


    map<string, string>                      Config::Hrefs,         Config::Hsystems;
    map<string, int>                         Config::Hmetrics,      Config::wc;
    map<string, int>                         Config::eval_schemes,  Config::metaeval_schemes,     Config::optimize_schemes,     Config::metaeval_criteria,  Config::optimize_criteria;
    map<string, vector<vector<string> > >    Config::IDX;
    set<string>                              Config::metrics,       Config::systems,    Config::references;
    vector<string>                           Config::COMBO;  //metrics,  systems,        references;

    string Config::IQ_config,   Config::learn_scheme,   Config::ci;
    string Config::SORT,        Config::LANG,           Config::CASE;
    string Config::G,           Config::I,              Config::O;
    string Config::SRCCASE,     Config::SRCLANG,        Config::src;
    string Config::tools,       Config::model;
    string Config::parser,      Config::SRCparser;

    int Config::do_metric_names,    Config::do_system_names,    Config::do_reference_names, Config::do_refs,        Config::do_time;
    int Config::min_dist,           Config::setid_length,       Config::segid_length,       Config::docid_length;
    int Config::TEX,                Config::TEX_table_count,    Config::TEX_font_size,      Config::alignments;
    int Config::float_precision,    Config::float_length,       Config::n_epochs,           Config::n_resamplings;
    int Config::O_STORAGE,          Config::verbose,            Config::debug,              Config::tsearch;
    int Config::tokenize,           Config::remake;

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

    char* path = getenv("ASIYA_HOME");
    if (path) {
        cout << "path: " << string(path) << endl;
        Config::PATH = path;   //cout << "path: " << path << endl;
    } else cout << "There's no path." << endl;

    //return CONFIG;
}

void Config::printMapInt(const map<string, int> &m) {
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
}


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
    for (map<string, int>::const_iterator it = Config::Hmetrics.begin(); it != Config::Hmetrics.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\tn_resamplings -> " << Config::n_resamplings << endl;
    cout << "\tdo_metric_names -> " << Config::do_metric_names << endl;
    cout << "\tsrc -> " << Config::src << endl;
    cout << "\ttools -> " << Config::tools << endl;
    cout << "\tCASE -> " << Config::CASE << endl;
    cout << "\tfloat_precision -> " << Config::float_precision << endl;
    cout << "\tPATH -> " << Config::PATH << endl;
    cout << "\tfloat_length -> " << Config::float_length << endl;
    cout << "\tdo_system_names -> " << Config::do_system_names << endl;
    cout << "\tI -> " << Config::I << endl;
    cout << "\tG -> " << Config::G << endl;
    cout << "\tHrefs -> " << endl;
    for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\talignments -> " << Config::alignments << endl;
    cout << "\tTEX_table_count -> " << Config::TEX_table_count << endl;
    //cout << segments
    cout << "\tIQ_config -> " << Config::IQ_config << endl;
    //cout << TEX_font_size
    cout << "\treferences -> (" << Config::references.size() << ")" << endl;
    for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tIDX -> " << endl;
    for (map<string, vector<vector<string> > >::const_iterator it = Config::IDX.begin(); it != Config::IDX.end(); ++it) {
        vector<vector<string> > aux = it->second;
        cout << "\t\t" << it->first << " -> [" << endl;
        for (int i = 0; i < aux.size(); ++i) {
            cout << "\t\t\t[";
            for (int j = 0; j < aux[i].size(); ++j) {
                cout << aux[i][j] << ", ";
            }
            cout << endl;
        }
        cout << "\t\t]" << endl;
    }
    cout << "\tO_STORAGE -> " << Config::O_STORAGE << endl;
    cout << "\tmetrics-> (" << Config::metrics.size() << ")" << endl;
    for (set<string>::const_iterator it = Config::metrics.begin(); it != Config::metrics.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\twc-> (" << Config::Hmetrics.size() << ")" << endl;
    for (map<string, int>::const_iterator it = Config::wc.begin(); it != Config::wc.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\teval_schemes-> (" << Config::Hmetrics.size() << ")" << endl;
    for (map<string, int>::const_iterator it = Config::eval_schemes.begin(); it != Config::eval_schemes.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\tO -> " << Config::O << endl;
    cout << "\ttsearch -> " << Config::tsearch << endl;
    cout << "\tSRCCASE -> " << Config::SRCCASE << endl;
    cout << "\talfa -> " << Config::alfa << endl;
    cout << "\tdo_refs -> " << Config::do_refs << endl;
    cout << "\tSRCLANG -> " << Config::SRCLANG << endl;
    cout << "\tHsystems -> " << endl;
    for (map<string, string>::const_iterator it = Config::Hsystems.begin(); it != Config::Hsystems.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
}

void Config::process_command_line_options(map<string, string> Options, vector<string> metaeval_options, vector<string> optimize_options) {
    if (Options.find("v") != Options.end()) Config::verbose = atoi(Options["v"].c_str());
    else Config::verbose = 0;
    if (Options.find("d") != Options.end()) Config::debug = atoi(Options["d"].c_str());
    else Config::debug = 0;
    if (Options.find("remake") != Options.end()) Config::remake = atoi(Options["remake"].c_str());
    else Config::remake = 0;
    if (Options.find("time") != Options.end()) Config::do_time = atoi(Options["time"].c_str());
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
            cout << "Added " << *i << " to metrics (command line options)" << endl;
            Config::metrics.insert(*i);
            Config::Hmetrics[*i] = 1;
            ++i;
        }
    }
    if (Options.find("s") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["s"].begin(), Options["s"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            Config::systems.insert(*i);
            cout << "Added " << *i << " to systems (command line options)" << endl;
            ++i;
        }
    }
    if (Options.find("r") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["r"].begin(), Options["r"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            Config::references.insert(*i);
            cout << "Added " << *i << " to references (command line options)" << endl;
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

            if (Common::eval_schemes.find(aux) != Common::eval_schemes.end()) Config::eval_schemes[aux] = 1;
            else { fprintf(stderr, "[ERROR] unknown evaluation method '%s'\n", aux.c_str()); exit(1); }

            cout << "Added " << *i << " to eval_schemes (command line options)" << endl;
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
    else {
        stringstream ss;
        ss << Common::DATA_PATH << "/" << Common::MODEL_DEFAULT;
        Config::model = ss.str();
    }
}

void Config::process_nist_file(string file, string type) {}

void Config::process_raw_file(string file, string type) {
    // description _ read the contents of a RAW plain text file (one sentence per line) and generate fake idx files
    //               (idx structure is also stored onto memory)
    // param1  _ configuration structure
    // param2  _ input file
    // param3  _ file type (source|references|systems)

    stringstream ss;
    ss << file << "." << Common::IDXEXT;
    string IDX = ss.str();

    vector<vector<string> > rIDX = NISTXML::write_fake_idx_file(file, IDX, Config::verbose);

    ss.str("");
    ss << file << "." << Common::TOKEXT;
    string tokfile = ss.str();


    //cout << "process_raw_file: file : '" << file << "' type: '" << type << "'" << endl;

    string lang;
    if (type == "source" or type == "src") {
        Config::src = tokfile;
        Config::IDX["source"] = rIDX;
        Config::wc["source"] = rIDX.size() - 1;
        lang = Config::SRCLANG;
    }
    else if (type == "reference" or type == "ref") {
        string R = Common::give_system_name(file);
        cout << "\tR: '" << R << "'" << endl;
        Config::IDX[R] = rIDX;
        map<string, string>::const_iterator it = Config::Hrefs.find(R);
        if (it != Config::Hrefs.end()) { fprintf(stderr, "[ERROR] reference name '%s' duplicated!\n", R.c_str()); exit(1); }
        /*pair<map<string, vector<vector<string> > >::iterator, bool> res = Config::IDX.insert(make_pair(R, rIDX));
        if (!res.second) { fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", R); exit(1); }*/

        Config::wc[R] = rIDX.size()-1;
        Config::Hrefs[R] = tokfile;
        lang = Config::LANG;
    }
    else if (type == "system" or type =="sys") {
        string S = Common::give_system_name(file);
        Config::IDX[S] = rIDX;
        map<string, string>::const_iterator it = Config::Hsystems.find(S);
        if (it != Config::Hsystems.end()) { fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", S.c_str()); exit(1); }
        Config::wc[S] = rIDX.size()-1;
        Config::Hsystems[S] = tokfile;
        lang = Config::LANG;
    }
    else { fprintf(stderr, "[ERROR] unkown file type <%s>!!\n", type.c_str()); exit(1); }

    stringstream sc, ms;
    sc << "cp -f "<< file << " " << tokfile;
    ms << "[ERROR] could not copy " << file << " into " << tokfile;

    Common::execute_or_die(sc.str(), ms.str());

    if(Config::tokenize) {
        string l = lang;
        //if w
    }
}

void Config::process_config_file(char* config_file, map<string, string> Options) {
    string IQ_config(config_file);
    //my $options = options;

    //Config CONFIG = default_config();
    Config::default_config();

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
        }
    }
    cout << "METRICS = " << METRICS << endl;
    cout << "SYSTEMS = " << SYSTEMS << endl;;
    cout << "REFERENCES = " << REFERENCES << endl;

    // string TOOLS = Config::PATH;
    string TOOLS = "/home/ibai/Escriptori/AsiyaGPUsvn/tools"; // /home/soft/asiya/tools";
    boost::regex re2("/+");
    TOOLS = boost::regex_replace(TOOLS, re2, "/");

    boost::filesystem::path p (TOOLS);   // p reads clearer than argv[1] in the following code

    if (!is_directory(p)) {
        fprintf(stderr, "[%s] directory <%s> does not exist!\n", Common::appNAME.c_str(), TOOLS.c_str());
        exit(1);
    }

    Config::tools = TOOLS;

    string path_aux = Common::DATA_PATH; path_aux += "/"; path_aux += Common::TMP;
    p = path_aux;

    if (!is_directory(p)) {
        stringstream ss;
        ss << "mkdir " << Common::DATA_PATH << "/" << Common::TMP;
        string s = ss.str();
        system(s.c_str());
    } //TEMPORARY DIRECTORY

    map<string,string>::const_iterator it = Options.find("verbose");
    if (it != Options.end()) {
        fprintf(stderr, "[%s] READING IQsetup config file <%s>...", Common::appNAME.c_str(), config_file); // IQ_Config::c_str());
    } //TEMPORARY DIRECTORY

    p = IQ_config;
    if (!exists(p)) {
        fprintf(stderr, "[%s] config file <%s> does not exist!\n", Common::appNAME.c_str(), config_file); //IQ_Config::c_str());
        exit(1);
    }
    else { Config::IQ_config = IQ_config; }

    ifstream file;

    //read input mode
    file.open(config_file);     //(IQ_Config::c_str());
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

                boost::to_lower(type);
                boost::to_lower(data);

                if (type == "input") {
                    if (data == Common::I_NIST) Config::I = Common::I_NIST;
                    else Config::I = Common::I_RAW;
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

                string type, data;
                type = *i++;
                data = *i;

                boost::regex re("\\s*$"); //, boost::regex::perl|boost::regex::icase);
                type = boost::regex_replace(type, re, "");
                boost::regex re2("^\\s*"); //, boost::regex::perl|boost::regex::icase);
                data = boost::regex_replace(data, re2, "");

                pair<string, string> entry(type, data);

                boost::to_lower(type);
                boost::to_lower(data);

                if (type == "source" or type == "src" or type == "reference" or type == "ref" or type == "system" or type == "sys") {

                    //string file = entry.first;

                    if (Config::I == Common::I_NIST) process_nist_file(data, type);
                    else process_raw_file(data, type);
                }
                else if (type == "srclang") {
                    if (Common::rLANGS.find(data) != Common::rLANGS.end()) {
                        Config::SRCLANG = data; //boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED SOURCE LANGUAGE ('.%s.')!!\n", data.c_str());
                    }

                    cout << "# srclang readed #" << endl;
                }
                else if (type == "lang" or type == "trglang") {
                    if (Common::rLANGS.find(data) != Common::rLANGS.end()) {
                        Config::LANG = data; //boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED TARGET LANGUAGE ('.%s.')!!\n", data.c_str());
                    }

                    cout << "# lang or trglang readed #" << endl;
                }
                else if (type == "srccase") {
                    if (data == Common::CASE_CI) {
                        Config::SRCCASE = Common::CASE_CI;
                    } else {
                        Config::SRCCASE = Common::CASE_CS;
                    }
                }
                else if (type == "trgcase" or type == "case") {
                    if (data == Common::CASE_CI) {
                        Config::CASE = Common::CASE_CI;
                    } else {
                        Config::CASE = Common::CASE_CS;
                    }

                    cout << "# case or trgcase readed #" << endl;
                }
                else if (entry.first == METRICS) {
                    boost::regex reeq(" ");     //alternative to splitting: strtok, check it out if you hate boost...
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        cout << "Add " << *i << " to Hmetrics/metrics" << endl;
                        Config::Hmetrics[*i] = 1;
                        Config::metrics.insert(*i);
                        /*pair<string, int> res = Config::Hmetrics.insert( pair<string,int>(*i,1) );
                        if (res.second) Config::metrics.push(*i);
                        else cout << "element " << *i << " already exist in Hmetrics." << endl;*/
                        ++i;
                    }

                    cout << "# metrics " << METRICS << " readed #" << endl;
                }
                else if (entry.first == SYSTEMS) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        cout << "Add " << *i << " to systems" << endl;

                        Config::systems.insert(*i++);
                    }

                    cout << "# systems " << SYSTEMS << " readed #" << endl;
                }
                else if (entry.first == REFERENCES) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        cout << "Add " << *i << " to references" << endl;

                        Config::references.insert(*i++);
                    }

                    cout << "# references " << REFERENCES << " readed #" << endl;
                }
                else if (entry.first == SEGMENTS) {
                    //read_selection();
                }
            }
        }
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", config_file); exit(1); }

    if (Config::verbose) fprintf(stderr, " [DONE]\n");
}

void Config::validate_configuration() {
    // description _ validate configuration (through simple verifications on mandatory arguments and option values)

    if (Config::PATH == "") {
        fprintf(stderr, "[ERROR] PATH undefined\n");
        exit(1);
    }
    boost::filesystem::path p (Config::PATH);   // p reads clearer than argv[1] in the following code
    if (!is_directory(p)) {
        fprintf(stderr, "[ERROR] PATH directory <%s> does not exist!\n", Config::PATH);
        exit(1);
    }
    boost::filesystem::path t (Config::tools);   // p reads clearer than argv[1] in the following code
    if (!is_directory(t)) {
        fprintf(stderr, "[ERROR] PATH directory <%s> does not exist!\n", Config::tools.c_str());
        exit(1);
    }
    if (!Config::references.empty()) {
        for (set<string>::const_iterator it = Config::references.begin(); it != Config::references.end(); ++it) {
            if (Config::Hrefs.find(*it) == Config::Hrefs.end()) {
                fprintf(stderr, "[ERROR] reference '%s' not in test suite!!\n", it->c_str());
                exit(1);
            }
        }
    } else {
        for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) Config::references.insert(it->first);
    }

    if (!Config::systems.empty()) {
        for (set<string>::const_iterator it = Config::systems.begin(); it != Config::systems.end(); ++it) {
            if (Config::Hsystems.find(*it) == Config::Hsystems.end()) {
                fprintf(stderr, "[ERROR] system '%s' not in test suite!!\n", it->c_str());
                exit(1);
            }
        }
    } else {
        for (map<string, string>::const_iterator it = Config::Hsystems.begin(); it != Config::Hsystems.end(); ++it) Config::systems.insert(it->first);
        if (Config::systems.empty()) {
            fprintf(stderr, "[ERROR] set of systems undefined!!\n");
            exit(1);
        }
    }

}



//$Asiya_config, \%options, \@metaevaluation_params, \@optimization_params);
//Config read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
void Config::read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
    //description _ process configuration file and command-line options
    //param1  _ configuration file
    //param2  _ command-line options
    //param4  _ command-line optimization options

    //Config CONFIG = process_config_file(config_file, options);
    process_config_file(config_file, options);
    process_command_line_options(options, metaeval_options, optimize_options);

    /*Dumper();
    cout << "Options readed, dump:" << endl;
    Config::printMapString(options);*/
    validate_configuration();

    /*process_command_line_options($CONFIG, $options, $metaeval_options, $optimize_options);
    validate_configuration($CONFIG);
    print_configuration_options($CONFIG);*/

    //return CONFIG;
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
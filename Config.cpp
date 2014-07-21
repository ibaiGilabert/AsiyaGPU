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
    cout << "\tlearn_scheme -> " << CONFIG.learn_scheme << endl;
    cout << "\tdo_reference_names ->" << CONFIG.do_reference_names << endl;
    cout << "\ttrain_prop -> " << CONFIG.train_prop << endl;
    cout << "\tn_epochs -> " << CONFIG.n_epochs << endl;
    cout << "\tci -> " << CONFIG.ci << endl;
    cout << "\tTEX -> " << CONFIG.TEX << endl;
    cout << "\tsystems -> " << endl;
    for (set<string>::const_iterator it = CONFIG.systems.begin(); it != CONFIG.systems.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tdebug -> " << CONFIG.debug << endl;
    cout << "\tSORT -> " << CONFIG.SORT << endl;
    cout << "\tLANG -> " << CONFIG.LANG << endl;
    cout << "\ttokenize -> " << CONFIG.tokenize << endl;
    cout << "\tHmetrics -> (" << CONFIG.Hmetrics.size() << ")" << endl;
    for (map<string, int>::const_iterator it = CONFIG.Hmetrics.begin(); it != CONFIG.Hmetrics.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\tn_resamplings -> " << CONFIG.n_resamplings << endl;
    cout << "\tdo_metric_names -> " << CONFIG.do_metric_names << endl;
    cout << "\tsrc -> " << CONFIG.src << endl;
    cout << "\ttools -> " << CONFIG.tools << endl;
    cout << "\tCASE -> " << CONFIG.CASE << endl;
    cout << "\tfloat_precision -> " << CONFIG.float_precision << endl;
    cout << "\tPATH -> " << CONFIG.PATH << endl;
    cout << "\tfloat_length -> " << CONFIG.float_length << endl;
    cout << "\tdo_system_names -> " << CONFIG.do_system_names << endl;
    cout << "\tI -> " << CONFIG.I << endl;
    cout << "\tG -> " << CONFIG.G << endl;
    cout << "\tHrefs -> " << endl;
    for (map<string, string>::const_iterator it = CONFIG.Hrefs.begin(); it != CONFIG.Hrefs.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
    cout << "\talignments -> " << CONFIG.alignments << endl;
    cout << "\tTEX_table_count -> " << CONFIG.TEX_table_count << endl;
    //cout << segments
    cout << "\tIQ_config -> " << CONFIG.IQ_config << endl;
    //cout << TEX_font_size
    cout << "\treferences -> (" << CONFIG.references.size() << ")" << endl;
    for (set<string>::const_iterator it = CONFIG.references.begin(); it != CONFIG.references.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tIDX -> " << endl;
    for (map<string, vector<vector<string> > >::const_iterator it = CONFIG.IDX.begin(); it != CONFIG.IDX.end(); ++it) {
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
    cout << "\tO_STORAGE -> " << CONFIG.O_STORAGE << endl;
    cout << "\tmetrics-> (" << CONFIG.metrics.size() << ")" << endl;
    for (set<string>::const_iterator it = CONFIG.metrics.begin(); it != CONFIG.metrics.end(); ++it) {
        cout << "\t\t" << *it << endl;
    }
    cout << "\tO -> " << CONFIG.O << endl;
    cout << "\ttsearch -> " << CONFIG.tsearch << endl;
    cout << "\tSRCCASE -> " << CONFIG.SRCCASE << endl;
    cout << "\talfa -> " << CONFIG.alfa << endl;
    cout << "\tdo_refs -> " << CONFIG.do_refs << endl;
    cout << "\tSRCLANG -> " << CONFIG.SRCLANG << endl;
    cout << "\tHsystems -> " << endl;
    for (map<string, string>::const_iterator it = CONFIG.Hsystems.begin(); it != CONFIG.Hsystems.end(); ++it) {
        cout << "\t\t" << it->first << " -> " << it->second << endl;
    }
}

void process_command_line_options(Config &CONFIG, map<string, string> Options, vector<string> metaeval_options, vector<string> optimize_options) {
    if (Options.find("v") != Options.end()) CONFIG.verbose = atoi(Options["v"].c_str());
    else CONFIG.verbose = 0;
    if (Options.find("d") != Options.end()) CONFIG.debug = atoi(Options["d"].c_str());
    else CONFIG.debug = 0;
    if (Options.find("remake") != Options.end()) CONFIG.remake = atoi(Options["remake"].c_str());
    else CONFIG.remake = 0;
    if (Options.find("time") != Options.end()) CONFIG.do_time = atoi(Options["time"].c_str());
    else CONFIG.do_time = 0;
    if (Options.find("no_tok") != Options.end()) CONFIG.tokenize = 0;
    if (Options.find("tsearch") != Options.end()) CONFIG.tsearch = 1;
    else CONFIG.tsearch = 0;
    //if (Options.find("testbedid") != Options.end()) CONFIG.testbedid = Options["testbedid"];
    if (Options.find("m") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["m"].begin(), Options["m"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            cout << "Added " << *i << " to metrics (command line options)" << endl;
            CONFIG.metrics.insert(*i);
            CONFIG.Hmetrics[*i] = 1;
            ++i;
        }
    }
    if (Options.find("s") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["s"].begin(), Options["s"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            CONFIG.systems.insert(*i);
            cout << "Added " << *i << " to systems (command line options)" << endl;
            ++i;
        }
    }
    if (Options.find("r") != Options.end()) {
        boost::regex reeq(",");
        boost::sregex_token_iterator i(Options["r"].begin(), Options["r"].end(), reeq, -1);
        boost::sregex_token_iterator j;
        while (i != j) {
            CONFIG.references.insert(*i);
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

            if (eval_schemes.find(aux) != eval_schemes.end()) CONFIG.eval_schemes[aux] = 1;
            else { fprintf(stderr, "[ERROR] unknown evaluation method '%s'\n", aux.c_str()); exit(1); }

            cout << "Added " << *i << " to eval_schemes (command line options)" << endl;
            ++i;
        }
    }
    if (metaeval_options.size() > 0) {}

    if (optimize_options.size() > 0) {}

    if (Options.find("include_refs") != Options.end()) CONFIG.do_refs = atoi(Options["include_refs"].c_str());
    if (Options.find("align") != Options.end()) CONFIG.alignments= atoi(Options["align"].c_str());
    if (Options.find("metric_names") != Options.end()) CONFIG.do_metric_names = atoi(Options["metric_names"].c_str());
    if (Options.find("system_names") != Options.end()) CONFIG.do_system_names = atoi(Options["system_names"].c_str());
    if (Options.find("reference_names") != Options.end()) CONFIG.do_reference_names =atoi(Options["referece_names"].c_str());
    if (Options.find("g") != Options.end()) CONFIG.G = Options["g"];
    if (Options.find("o") != Options.end()) CONFIG.O = Options["o"];
    if (Options.find("no_storage") != Options.end()) CONFIG.O_STORAGE = atoi(Options["no_storage"].c_str());
    if (Options.find("sorted") != Options.end()) CONFIG.SORT = Options["sorted"];
    if (Options.find("tex") != Options.end()) CONFIG.TEX = atoi(Options["tex"].c_str());
    if (Options.find("pdf") != Options.end()) { /*CONFIG.PDF = Options["pdf"]; CONFIG.TEX_REPORT = "";*/ }
    //if (Options.find("font_size") != Options.end()) CONFIG.TEX_font_size = Options["font_size"];
    if (Options.find("srclang") != Options.end()) {
        string aux = Options["srclang"];
        boost::to_lower(aux);
        if (rLANGS.find(aux) != rLANGS.end()) CONFIG.SRCLANG = aux;
        else { fprintf(stderr, "[ERROR] UNSUPPORTED SOURCE LANGUAGE ('%s'))!!\n", aux.c_str()); exit(1); }
    }
    if (Options.find("trclang") != Options.end()) {
        string aux = Options["trclang"];
        boost::to_lower(aux);
        if (rLANGS.find(aux) != rLANGS.end()) CONFIG.LANG = aux;
        else { fprintf(stderr, "[ERROR] UNSUPPORTED TARGET LANGUAGE ('%s'))!!\n", aux.c_str()); exit(1); }
    }
    if (Options.find("srccase") != Options.end()) {
        string aux = Options["srccase"];
        boost::to_lower(aux);
        if (aux == CASE_CI) CONFIG.SRCCASE = CASE_CI;
        else CONFIG.SRCCASE = CASE_CS;
    }
    if (Options.find("trgcase") != Options.end()) {
        string aux = Options["trgcase"];
        boost::to_lower(aux);
        if (aux == CASE_CI) CONFIG.CASE = CASE_CI;
        else CONFIG.CASE = CASE_CS;
    }
    if (Options.find("float_length") != Options.end()) CONFIG.float_length = atoi(Options["float_length"].c_str());
    if (Options.find("float_precision") != Options.end()) CONFIG.float_precision = atoi(Options["float_precision"].c_str());

    // META-EVALUATION PARAMETERS ---------------------------------------------------
    /*if (Options.find("assessments") != Options.end()) {
       //(my $assesstype, $CONFIG->{assessments}) = Assessments::read_NISTCSV_file($options->{"assessments"}, $CONFIG->{IDX}->{"source"}, $CONFIG->{verbose});
       //$CONFIG->{avgassessments} = Assessments::average_assessments( $assesstype, $CONFIG->{assessments} );    }*/
    if (Options.find("alfa") != Options.end()) CONFIG.alfa = atof(Options["alfa"].c_str());
    if (Options.find("ci") != Options.end()) {
        string aux = Options["ci"];
        if (rCI.find(aux) == rCI.end()) { fprintf(stderr, "[ERROR] unknown confidence-interval computation method '%s'!!\n", aux.c_str()); exit(1); }
        CONFIG.ci = aux;
    }
    if (Options.find("n_resamplings") != Options.end()) CONFIG.n_resamplings = atoi(Options["n_resamplings"].c_str());

    // LEARNING PARAMETERS ----------------------------------------------------------
    if (Options.find("learn") != Options.end()) CONFIG.learn_scheme = Options["learn"];
    if (Options.find("n_epochs") != Options.end()) CONFIG.n_epochs = atoi(Options["n_epochs"].c_str());
    if (Options.find("min_dist") != Options.end()) CONFIG.min_dist = atoi(Options["min_dist"].c_str());
    if (Options.find("train_prop") != Options.end()) CONFIG.train_prop = atof(Options["train_prop"].c_str());
    if (Options.find("model") != Options.end()) CONFIG.model = Options["model"];
    else {
        stringstream ss;
        ss << DATA_PATH << "/" << MODEL_DEFAULT;
        CONFIG.model = ss.str();
    }
}

void process_nist_file(Config &CONFIG, string file, string type) {}

void process_raw_file(Config &CONFIG, string file, string type) {
    // description _ read the contents of a RAW plain text file (one sentence per line) and generate fake idx files
    //               (idx structure is also stored onto memory)
    // param1  _ configuration structure
    // param2  _ input file
    // param3  _ file type (source|references|systems)

    stringstream ss;
    ss << file << "." << IDXEXT;
    string IDX = ss.str();

    vector<vector<string> > rIDX = write_fake_idx_file(file, IDX, CONFIG.verbose);

    ss.str("");
    ss << file << "." << TOKEXT;
    string tokfile = ss.str();


    cout << "process_raw_file: file : '" << file << "' type: '" << type << "'" << endl;

    string lang;
    if (type == "source" or type == "src") {
        CONFIG.src = tokfile;
        CONFIG.IDX["source"] = rIDX;
        CONFIG.wc["source"] = rIDX.size() - 1;
        lang = CONFIG.SRCLANG;
    }
    else if (type == "reference" or type == "ref") {
        string R = give_system_name(file);
        cout << "\tR: '" << R << "'" << endl;
        CONFIG.IDX[R] = rIDX;
        map<string, string>::const_iterator it = CONFIG.Hrefs.find(R);
        if (it != CONFIG.Hrefs.end()) { fprintf(stderr, "[ERROR] reference name '%s' duplicated!\n", R.c_str()); exit(1); }
        /*pair<map<string, vector<vector<string> > >::iterator, bool> res = CONFIG.IDX.insert(make_pair(R, rIDX));
        if (!res.second) { fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", R); exit(1); }*/

        CONFIG.wc[R] = rIDX.size()-1;
        CONFIG.Hrefs[R] = tokfile;
        lang = CONFIG.LANG;
    }
    else if (type == "system" or type =="sys") {
        string S = give_system_name(file);
        CONFIG.IDX[S] = rIDX;
        map<string, string>::const_iterator it = CONFIG.Hsystems.find(S);
        if (it != CONFIG.Hsystems.end()) { fprintf(stderr, "[ERROR] system name '%s' duplicated!\n", S.c_str()); exit(1); }
        CONFIG.wc[S] = rIDX.size()-1;
        CONFIG.Hsystems[S] = tokfile;
        lang = CONFIG.LANG;
    }
    else { fprintf(stderr, "[ERROR] unkown file type <%s>!!\n", type.c_str()); exit(1); }

    stringstream sc, ms;
    sc << "cp -f "<< file << " " << tokfile;
    ms << "[ERROR] could not copy " << file << " into " << tokfile;

    execute_or_die(sc.str(), ms.str());

    if(CONFIG.tokenize) {
        string l = lang;
        //if w
    }
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
    cout << "METRICS = " << METRICS << endl;
    cout << "SYSTEMS = " << SYSTEMS << endl;;
    cout << "REFERENCES = " << REFERENCES << endl;

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
        fprintf(stderr, "[%s] READING IQsetup config file <%s>...", appNAME.c_str(), config_file); // IQ_config.c_str());
    } //TEMPORARY DIRECTORY

    p = IQ_config;
    if (!exists(p)) {
        fprintf(stderr, "[%s] config file <%s> does not exist!\n", appNAME.c_str(), config_file); //IQ_config.c_str());
        exit(1);
    }
    else { CONFIG.IQ_config = IQ_config; }

    ifstream file;

    //read input mode
    file.open(config_file);     //(IQ_config.c_str());
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

                string type = *i++;
                string data = *i;

                boost::regex re("\\s*$");//, boost::regex::perl|boost::regex::icase);
                boost::regex re2("^\\s*");//, boost::regex::perl|boost::regex::icase);

                type = boost::regex_replace(type, re, "");
                data = boost::regex_replace(data, re2, "");

                boost::to_lower(type);
                boost::to_lower(data);

                if (type == "input") {
                    if (data == I_NIST) CONFIG.I = I_NIST;
                    else CONFIG.I = I_RAW;
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
            cout << "Linia " << ++i << endl;
            cout << '\t' << str << endl;
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str, results, re)) {
                cout << "\t That was a kind of line" << endl;

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

                    if (CONFIG.I == I_NIST) process_nist_file(CONFIG, data, type);
                    else process_raw_file(CONFIG, data, type);
                }
                else if (type == "srclang") {
                    if (rLANGS.find(data) != rLANGS.end()) {
                        CONFIG.SRCLANG = data; //boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED SOURCE LANGUAGE ('.%s.')!!\n", data.c_str());
                    }

                    cout << "# srclang readed #" << endl;
                }
                else if (type == "lang" or type == "trglang") {
                    if (rLANGS.find(data) != rLANGS.end()) {
                        CONFIG.LANG = data; //boost::to_lower(entry.first);
                    } else {
                        fprintf(stderr,"[ERROR] UNSUPPORTED TARGET LANGUAGE ('.%s.')!!\n", data.c_str());
                    }

                    cout << "# lang or trglang readed #" << endl;
                }
                else if (type == "srccase") {
                    if (data == CASE_CI) {
                        CONFIG.SRCCASE = CASE_CI;
                    } else {
                        CONFIG.SRCCASE = CASE_CS;
                    }
                }
                else if (type == "trgcase" or type == "case") {
                    if (data == CASE_CI) {
                        CONFIG.CASE = CASE_CI;
                    } else {
                        CONFIG.CASE = CASE_CS;
                    }

                    cout << "# case or trgcase readed #" << endl;
                }
                else if (entry.first == METRICS) {
                    boost::regex reeq(" ");     //alternative to splitting: strtok, check it out if you hate boost...
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        cout << "Add " << *i << " to Hmetrics/metrics" << endl;
                        CONFIG.Hmetrics[*i] = 1;
                        CONFIG.metrics.insert(*i);
                        /*pair<string, int> res = CONFIG.Hmetrics.insert( pair<string,int>(*i,1) );
                        if (res.second) CONFIG.metrics.push(*i);
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
                        CONFIG.systems.insert(*i++);
                    }

                    cout << "# systems " << SYSTEMS << " readed #" << endl;
                }
                else if (entry.first == REFERENCES) {
                    boost::regex reeq(" ");
                    boost::sregex_token_iterator i(entry.second.begin(), entry.second.end(), reeq, -1);
                    boost::sregex_token_iterator j;
                    while (i != j) {
                        CONFIG.references.insert(*i++);
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

    if (CONFIG.verbose) fprintf(stderr, " [DONE]\n");

    Dumper(CONFIG);

    return CONFIG;
}

//$Asiya_config, \%options, \@metaevaluation_params, \@optimization_params);
Config read_configuration_options(char* config_file, map<string, string> options, vector<string> metaeval_options, vector<string> optimize_options) {
    //description _ process configuration file and command-line options
    //param1  _ configuration file
    //param2  _ command-line options
    //param4  _ command-line optimization options

    Config CONFIG = process_config_file(config_file, options);
    process_command_line_options(CONFIG, options, metaeval_options, optimize_options);
    /*process_command_line_options($CONFIG, $options, $metaeval_options, $optimize_options);
    validate_configuration($CONFIG);
    print_configuration_options($CONFIG);*/

    return CONFIG;
}
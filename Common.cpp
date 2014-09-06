#include "Common.hpp"

#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

//FILE EXTENSIONS
const string Common::SGMLEXT = "sgml";
const string Common::REPORTEXT = "report";
const string Common::SRCEXT = "src";
const string Common::REFEXT = "ref";
const string Common::SYSEXT = "out";
const string Common::XMLEXT = "xml";
const string Common::GZEXT = "gz";
const string Common::TXTEXT = "txt";
const string Common::IDXEXT = "idx";
const string Common::DOCEXT = "doc";
const string Common::TOKEXT = "tok";

//compression
const string Common::GZIP = "gzip -f";
const string Common::GUNZIP = "gunzip";

//tools directory
const string Common::TOOLS = "tools";

//application details
const string Common::VERSION = "3.0";
const string Common::appVERSION = "3.0";
const string Common::appNAME = "ASIYA";
const string Common::appYEAR = "2014";
const string Common::appAUTHOR = "Meritxell Gonzalez, Jesus Gimenez";

//languages
const string Common::L_ARA = "ar"; //arabic
const string Common::L_CAT = "ca"; //catalan
const string Common::L_CHN = "ch"; //chinesse
const string Common::L_CZE = "cz"; //czech
const string Common::L_DAN = "da"; //danish
const string Common::L_GER = "de"; //german
const string Common::L_ENG = "en"; //english
const string Common::L_SPA = "es"; //spanish
const string Common::L_FIN = "fi"; //finnish
const string Common::L_FRN = "fr"; //french
const string Common::L_HUN = "hu"; //hungarian
const string Common::L_ITA = "it"; //italian
const string Common::L_DUT = "nl"; //dutch
const string Common::L_NOR = "no"; //norwegian
const string Common::L_POR = "pt"; //portuguese
const string Common::L_ROM = "ro"; //romanian
const string Common::L_RUS = "ru"; //russian
const string Common::L_SWE = "sv"; //swedish
const string Common::L_TUR = "tr"; //turkish
const string Common::L_OTHER = "other";
const string Common::L_DEFAULT = L_ENG;

map<string, int> create_rLANGS() {
	map<string, int> rLANGS;
	rLANGS[Common::L_ENG] = 1; rLANGS[Common::L_SPA] = 1; rLANGS[Common::L_CAT] = 1; rLANGS[Common::L_GER] = 1;
	rLANGS[Common::L_FRN] = 1; rLANGS[Common::L_CZE] = 1; rLANGS[Common::L_ARA] = 1; rLANGS[Common::L_DAN] = 1;
	rLANGS[Common::L_FIN] = 1; rLANGS[Common::L_HUN] = 1; rLANGS[Common::L_ITA] = 1; rLANGS[Common::L_DUT] = 1;
	rLANGS[Common::L_NOR] = 1; rLANGS[Common::L_POR] = 1; rLANGS[Common::L_ROM] = 1; rLANGS[Common::L_RUS] = 1;
	rLANGS[Common::L_SWE] = 1; rLANGS[Common::L_TUR] = 1; rLANGS[Common::L_OTHER] = 1;
	return rLANGS;
}
const map<string, int> Common::rLANGS = create_rLANGS();

// granularity
const string Common::G_SYS = "sys";
const string Common::G_DOC = "doc";
const string Common::G_SEG = "seg";
const string Common::G_ALL = "all";
const string Common::G_DEFAULT = G_SYS;

// output format
const string Common::O_MMATRIX = "mmatrix";
const string Common::O_SMATRIX = "smatrix";
const string Common::O_RLISTS = "rlists";
const string Common::O_NIST = "nist";
const string Common::O_NONE = "none";
const string Common::O_DEFAULT = O_MMATRIX;
const string Common::SORT_NAME = "name";
const string Common::SORT_SCORE = "score";
const string Common::SORT_NONE = "none";
const string Common::SORT_DEFAULT = SORT_NONE;
const int Common::O_STORAGE = 1;

// evaluation
const string Common::S_SINGLE = "single";
const string Common::S_ULC = "ulc";
const string Common::S_QUEEN = "queen";
const string Common::S_MODEL = "model";

map<string, int> create_eval_schemes() {
	map<string, int> eval_schemes;
	eval_schemes[Common::S_SINGLE] = 1; eval_schemes[Common::S_ULC] = 1; eval_schemes[Common::S_QUEEN] = 1; eval_schemes[Common::S_MODEL] = 1;
	return eval_schemes;
}
const map<string, int> Common::eval_schemes = create_eval_schemes();

const string Common::DEFAULT_EVAL_CRITERION = S_SINGLE;

// learning
const string Common::LEARN_PERCEPTRON = "perceptron";
const double Common::TRAINING_PROPORTION_DEFAULT = 0.8;
const int Common::N_EPOCHS_DEFAULT = 100;
const int Common::MIN_DIST_DEFAULT = 0;
const string Common::MODELS = "models";

string get_model_default() {
    stringstream ss;
    ss << Common::MODELS << "/" << Common::LEARN_PERCEPTRON << ".mod";
    return ss.str();
}
const string Common::MODEL_DEFAULT = get_model_default();	//"const MODELS/const LEARN_PERCEPTRON.mod";

// meta-evaluation
const string Common::C_REGRESSION = "regression";
const string Common::C_PEARSON = "pearson";
const string Common::C_SPEARMAN = "spearman";
const string Common::C_KENDALL = "kendall";
const string Common::CI_NONE = "none";
const string Common::CI_FISHER = "fisher";
const string Common::CI_BOOTSTRAP = "bootstrap";
const string Common::CI_EXHAUSTIVE_BOOTSTRAP = "xbootstrap";
const string Common::CI_PAIRED_BOOTSTRAP = "paired_bootstrap";
const string Common::CI_EXHAUSTIVE_PAIRED_BOOTSTRAP = "paired_xbootstrap";
const string Common::CI_DEFAULT = CI_NONE;

map<string, int> create_rCI() {
	map<string, int> rCI;
	rCI[Common::CI_FISHER] = 1; rCI[Common::CI_BOOTSTRAP] = 1; rCI[Common::CI_EXHAUSTIVE_BOOTSTRAP] = 1; rCI[Common::CI_PAIRED_BOOTSTRAP] = 1;
	rCI[Common::CI_EXHAUSTIVE_PAIRED_BOOTSTRAP] = 1; rCI[Common::CI_NONE] = 1;
	return rCI;
}
const map<string, int> Common::rCI = create_rCI();

const double Common::ALFA_DEFAULT = 0.05;
const int Common::N_RESAMPLINGS_DEFAULT = 1000;

map<string, int> create_rCOORS() {
	map<string, int> rCORRS;
	rCORRS[Common::C_PEARSON] = 1; rCORRS[Common::C_SPEARMAN]; rCORRS[Common::C_KENDALL];
	return rCORRS;
}
const map<string, int> Common::rCORRS = create_rCOORS();

const string Common::C_KING = "king";
const string Common::C_ORANGE = "orange";
const string Common::C_CONSISTENCY = "consistency";
const string Common::C_MRANKENDALL = "mrankskendall";

map<string, int> create_rMRANKS() {
	map<string, int> rMRANKS;
	rMRANKS[Common::C_CONSISTENCY] = 1; rMRANKS[Common::C_MRANKENDALL] = 1;
	return rMRANKS;
}
const map<string, int> Common::rMRANKS = create_rMRANKS();

map<string, int> create_metaeval_criteria() {
	map<string, int> metaeval_criteria;
	metaeval_criteria[Common::C_PEARSON] = 1; metaeval_criteria[Common::C_SPEARMAN] = 1; metaeval_criteria[Common::C_KENDALL]; metaeval_criteria[Common::C_KING] = 1; metaeval_criteria[Common::C_ORANGE] = 1; metaeval_criteria[Common::C_CONSISTENCY] = 1; metaeval_criteria[Common::C_MRANKENDALL] = 1;
	return metaeval_criteria;
}
const map<string, int> Common::metaeval_criteria = create_metaeval_criteria();
const string Common::DEFAULT_METAEVAL_CRITERION = C_ORANGE;

// input file format
const string Common::I_NIST = "nist";
const string Common::I_RAW = "raw";
const string Common::I_DEFAULT = I_NIST;
const int Common::tokenize = 1;

// text case
const string Common::CASE_CS = "cs";
const string Common::CASE_CI = "ci";
const string Common::CASE_DEFAULT = CASE_CS;

// progress values
const int Common::progress0 = 10;
const int Common::progress1 = 100;
const int Common::progress2 = 1000;
const int Common::progress3 = 10000;

// font sizes
const string Common::FS_HUGE = "huge";
const string Common::FS_LARGE = "large";
const string Common::FS_NORMAL = "normal";
const string Common::FS_SMALL = "small";
const string Common::FS_TINY = "tiny";
const string Common::FS_DEFAULT = FS_NORMAL;

// other constants
const string Common::EMPTY_ITEM = "***EMPTY***";
string Common::DATA_PATH = ".";
const string Common::ALIGN = "alignments";
const string Common::TMP = "tmp";
const string Common::REPORTS = "scores";
const int Common::NRAND = 10000;
const int Common::MINVALUE = -99999999;
const string Common::SOURCEID = "source";
const int Common::FLOAT_LENGTH_DEFAULT = 10;
const int Common::FLOAT_PRECISION_DEFAULT = 8;
const int Common::METRIC_NAME_LENGTH = 12;
const int Common::SET_NAME_LENGTH = 40;
const int Common::SYS_NAME_LENGTH = 30;
const int Common::DOC_NAME_LENGTH = 30;
const int Common::SEG_ID_LENGTH = 10;
const int Common::MIN_ID_LENGTH = 3;
const int Common::HLINE_LENGTH = 120;
const string Common::UNKNOWN_SET = "UNKNOWN_SET";
const string Common::UNKNOWN_LANG = "UNKNOWN_LANG";
const string Common::UNKNOWN_GENRE = "UNKNOWN_GENRE";
const string Common::UNKNOWN_DOC = "UNKNOWN_DOC";
const int Common::SENSIBLE_MAX_N = 1000000;
const string Common::ID_SEPARATOR = "@@";
const string Common::CE = "CE";
const string Common::LeM = "LeM";

void Common::execute_or_die(string command, string message) {
    boost::regex re("\\R");
    command = boost::regex_replace(command, re, "");
    if (system(command.c_str())) {
    	fprintf(stderr, "%s\n%s\n", message.c_str(), command.c_str());
    	exit(1);
    }
}

string Common::give_system_name(string file) {
	// description _ get system name from filename

	boost::filesystem::path pathname (file);
	return pathname.filename().string();
}

string Common::replace_special_characters(string &input) {
   // description _ replaces conflictive characters inside a given string (~filename)
	boost::regex re;
    re = ("\\*");   input = boost::regex_replace(input, re, "\\\\*");
    re = (";");     input = boost::regex_replace(input, re, "\\\\;");
    re = ("`");     input = boost::regex_replace(input, re, "\\\\`");
    re = ("'");     input = boost::regex_replace(input, re, "\\\\'");
    re = ("\\(");   input = boost::regex_replace(input, re, "\\\\(");
    re = ("\\)");   input = boost::regex_replace(input, re, "\\\\)");
    re = ("\\?");   input = boost::regex_replace(input, re, "\\\\?");
    return input;
}

double Common::safe_division(double numerator, double denominator) {
	// description _ if denominator is different from 0 returns regular division; otherwise returns default value (0 if not specified)
	double default_value = -999999;
	return denominator == 0 ? default_value : numerator/denominator;
}

/*
sub safe_division {
    #description _ if denominator is different from 0 returns regular division; otherwise returns default value (0 if not specified)
    #param1  _ numerator
    #param2  _ denominator
    #param3  _ default value
    #@return _ safe division

    my $numerator = shift;
    my $denominator = shift;
    my $default = shift;

    if (!defined($default)) { $default = 0; }

    if (!defined($denominator)) { $denominator = 0; }

    if ($denominator == 0) { return $default; }

    return $numerator / $denominator;
}*/


/*double Common::trunk_and_trim_number(double n, int l, int p) {
	// description _ trunks the given number into a float (given length and precision) and trims trailing white spaces.
	if (n == -1) return 0;

	char buffer[64];

	cout << "COMMON::->n : " << n << ", l: " << l << ", p: " << p << endl;

	sprintf(buffer, "%.d.%df", l, p); //sz contains 0.6000
	cout << "->x: |" << atof(buffer) << "|" << endl;

	return atof(buffer);
}*/



void Common::print_hline(char c, int l) {
    //description _ print horizontal line
    //param1 _ character
    //param1 _ length
    string s = "";
    for (int i = 0; i < l; ++i) s += c;
    cout << s << endl;
}

void Common::print_hline_stderr(char c, int l) {
    //description _ print horizontal line
    //param1 _ character
    //param1 _ length

    string s = "";
    for (int i = 0; i < l; ++i) s += c;
    fprintf(stderr, "%s\n", s.c_str());
}

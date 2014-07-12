#include <sstream>
#include "Common.hpp"

//FILE EXTENSIONS
const string SGMLEXT = "sgml";
const string REPORTEXT = "report";
const string SRCEXT = "src";
const string REFEXT = "ref";
const string SYSEXT = "out";
const string XMLEXT = "xml";
const string GZEXT = "gz";
const string TXTEXT = "txt";
const string IDXEXT = "idx";
const string DOCEXT = "doc";
const string TOKEXT = "tok";

//compression
const string GZIP = "gzip -f";
const string GUNZIP = "gunzip";

//tools directory
const string TOOLS = "tools";

//application details
const string VERSION = "3.0";
const string appVERSION = "3.0";
const string appNAME = "ASIYA";
const string appYEAR = "2014";
const string appAUTHOR = "Meritxell Gonzalez, Jesus Gimenez";

//languages
const string L_ARA = "ar"; //arabic
const string L_CAT = "ca"; //catalan
const string L_CHN = "ch"; //chinesse
const string L_CZE = "cz"; //czech
const string L_DAN = "da"; //danish
const string L_GER = "de"; //german
const string L_ENG = "en"; //english
const string L_SPA = "es"; //spanish
const string L_FIN = "fi"; //finnish
const string L_FRN = "fr"; //french
const string L_HUN = "hu"; //hungarian
const string L_ITA = "it"; //italian
const string L_DUT = "nl"; //dutch
const string L_NOR = "no"; //norwegian
const string L_POR = "pt"; //portuguese
const string L_ROM = "ro"; //romanian
const string L_RUS = "ru"; //russian
const string L_SWE = "sv"; //swedish
const string L_TUR = "tr"; //turkish
const string L_OTHER = "other";
const string L_DEFAULT = L_ENG;

map<string, int> create_rLANGS() {
	map<string, int> rLANGS;
	rLANGS[L_ENG] = 1; rLANGS[L_SPA] = 1; rLANGS[L_CAT] = 1; rLANGS[L_GER] = 1;
	rLANGS[L_FRN] = 1; rLANGS[L_CZE] = 1; rLANGS[L_ARA] = 1; rLANGS[L_DAN] = 1;
	rLANGS[L_FIN] = 1; rLANGS[L_HUN] = 1; rLANGS[L_ITA] = 1; rLANGS[L_DUT] = 1;
	rLANGS[L_NOR] = 1; rLANGS[L_POR] = 1; rLANGS[L_ROM] = 1; rLANGS[L_RUS] = 1;
	rLANGS[L_SWE] = 1; rLANGS[L_TUR] = 1; rLANGS[L_OTHER] = 1;
	return rLANGS;
}

const map<string, int> rLANGS = create_rLANGS();

// granularity
const string G_SYS = "sys";
const string G_DOC = "doc";
const string G_SEG = "seg";
const string G_ALL = "all";
const string G_DEFAULT = G_SYS;

// output format
const string O_MMATRIX = "mmatrix";
const string O_SMATRIX = "smatrix";
const string O_RLISTS = "rlists";
const string O_NIST = "nist";
const string O_NONE = "none";
const string O_DEFAULT = O_MMATRIX;
const string SORT_NAME = "name";
const string SORT_SCORE = "score";
const string SORT_NONE = "none";
const string SORT_DEFAULT = SORT_NONE;
const int O_STORAGE = 1;

// evaluation
const string S_SINGLE = "single";
const string S_ULC = "ulc";
const string S_QUEEN = "queen";
const string S_MODEL = "model";

map<string, int> create_eval_schemes() {
	map<string, int> eval_schemes;
	eval_schemes[S_SINGLE] = 1; eval_schemes[S_ULC] = 1; eval_schemes[S_QUEEN] = 1; eval_schemes[S_MODEL] = 1;
	return eval_schemes;
}

const map<string, int> eval_schemes = create_eval_schemes();
const string DEFAULT_EVAL_CRITERION = S_SINGLE;

// learning
const string LEARN_PERCEPTRON = "perceptron";
const double TRAINING_PROPORTION_DEFAULT = 0.8;
const int N_EPOCHS_DEFAULT = 100;
const int MIN_DIST_DEFAULT = 0;
const string MODELS = "models";

string get_model_default() {
    stringstream ss;
    ss << MODELS << "/" << LEARN_PERCEPTRON << ".mod";
    return ss.str();
}

const string MODEL_DEFAULT = get_model_default();	//"const MODELS/const LEARN_PERCEPTRON.mod";

// meta-evaluation
const string C_REGRESSION = "regression";
const string C_PEARSON = "pearson";
const string C_SPEARMAN = "spearman";
const string C_KENDALL = "kendall";
const string CI_NONE = "none";
const string CI_FISHER = "fisher";
const string CI_BOOTSTRAP = "bootstrap";
const string CI_EXHAUSTIVE_BOOTSTRAP = "xbootstrap";
const string CI_PAIRED_BOOTSTRAP = "paired_bootstrap";
const string CI_EXHAUSTIVE_PAIRED_BOOTSTRAP = "paired_xbootstrap";
const string CI_DEFAULT = CI_NONE;

map<string, int> create_rCI() {
	map<string, int> rCI;
	rCI[CI_FISHER] = 1; rCI[CI_BOOTSTRAP] = 1; rCI[CI_EXHAUSTIVE_BOOTSTRAP] = 1; rCI[CI_PAIRED_BOOTSTRAP] = 1;
	rCI[CI_EXHAUSTIVE_PAIRED_BOOTSTRAP] = 1; rCI[CI_NONE] = 1;
	return rCI;
}
const map<string, int> rCI = create_rCI();
const double ALFA_DEFAULT = 0.05;
const int N_RESAMPLINGS_DEFAULT = 1000;

map<string, int> create_rCOORS() {
	map<string, int> rCORRS;
	rCORRS[C_PEARSON] = 1; rCORRS[C_SPEARMAN]; rCORRS[C_KENDALL];
	return rCORRS;
}
const map<string, int> rCORRS = create_rCOORS();
const string C_KING = "king";
const string C_ORANGE = "orange";
const string C_CONSISTENCY = "consistency";
const string C_MRANKENDALL = "mrankskendall";

map<string, int> create_rMRANKS() {
	map<string, int> rMRANKS;
	rMRANKS[C_CONSISTENCY] = 1; rMRANKS[C_MRANKENDALL] = 1;
	return rMRANKS;
}
const map<string, int> rMRANKS = create_rMRANKS();

map<string, int> create_metaeval_criteria() {
	map<string, int> metaeval_criteria;
	metaeval_criteria[C_PEARSON] = 1; metaeval_criteria[C_SPEARMAN] = 1; metaeval_criteria[C_KENDALL]; metaeval_criteria[C_KING] = 1; metaeval_criteria[C_ORANGE] = 1; metaeval_criteria[C_CONSISTENCY] = 1; metaeval_criteria[C_MRANKENDALL] = 1;
	return metaeval_criteria;
}
const map<string, int> metaeval_criteria = create_metaeval_criteria();
const string DEFAULT_METAEVAL_CRITERION = C_ORANGE;

// input file format
const string I_NIST = "nist";
const string I_RAW = "raw";
const string I_DEFAULT = I_NIST;
const int tokenize = 1;

// text case
const string CASE_CS = "cs";
const string CASE_CI = "ci";
const string CASE_DEFAULT = CASE_CS;

// progress values
const int progress0 = 10;
const int progress1 = 100;
const int progress2 = 1000;
const int progress3 = 10000;

// font sizes
const string FS_HUGE = "huge";
const string FS_LARGE = "large";
const string FS_NORMAL = "normal";
const string FS_SMALL = "small";
const string FS_TINY = "tiny";
const string FS_DEFAULT = FS_NORMAL;

// other constants
const string EMPTY_ITEM = "***EMPTY***";
const string DATA_PATH = ".";
const string ALIGN = "alignments";
const string TMP = "tmp";
const string REPORTS = "scores";
const int NRAND = 10000;
const int MINVALUE = -99999999;
const string SOURCEID = "source";
const int FLOAT_LENGTH_DEFAULT = 10;
const int FLOAT_PRECISION_DEFAULT = 8;
const int METRIC_NAME_LENGTH = 12;
const int SET_NAME_LENGTH = 40;
const int SYS_NAME_LENGTH = 30;
const int DOC_NAME_LENGTH = 30;
const int SEG_ID_LENGTH = 10;
const int MIN_ID_LENGTH = 3;
const int HLINE_LENGTH = 120;
const string UNKNOWN_SET = "UNKNOWN_SET";
const string UNKNOWN_LANG = "UNKNOWN_LANG";
const string UNKNOWN_GENRE = "UNKNOWN_GENRE";
const string UNKNOWN_DOC = "UNKNOWN_DOC";
const int SENSIBLE_MAX_N = 1000000;
const string ID_SEPARATOR = "@@";
const string CE = "CE";
const string LeM = "LeM";
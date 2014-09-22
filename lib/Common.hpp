#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <vector>
#include <map>
using namespace std;


class Common {
private:

public:
	//FILE EXTENSIONS
	static const string SGMLEXT;
	static const string REPORTEXT;
	static const string SRCEXT;
	static const string REFEXT;
	static const string SYSEXT;
	static const string XMLEXT;
	static const string GZEXT;
	static const string TXTEXT;
	static const string IDXEXT;
	static const string DOCEXT;
	static const string TOKEXT;

	//compression
	static const string GZIP;
	static const string GUNZIP;

	//tools directory
	static const string TOOLS;

	//application details
	static const string VERSION;
	static const string appVERSION;
	static const string appNAME;
	static const string appYEAR;
	static const string appAUTHOR;

	//languages
	static const string L_ARA;
	static const string L_CAT;
	static const string L_CHN;
	static const string L_CZE;
	static const string L_DAN;
	static const string L_GER;
	static const string L_ENG;
	static const string L_SPA;
	static const string L_FIN;
	static const string L_FRN;
	static const string L_HUN;
	static const string L_ITA;
	static const string L_DUT;
	static const string L_NOR;
	static const string L_POR;
	static const string L_ROM;
	static const string L_RUS;
	static const string L_SWE;
	static const string L_TUR;
	static const string L_OTHER;
	static const string L_DEFAULT;
	static const map<string, int> rLANGS;

	// granularity
	static const string G_SYS;
	static const string G_DOC;
	static const string G_SEG;
	static const string G_ALL;
	static const string G_DEFAULT;

	// output format
	static const string O_MMATRIX;
	static const string O_SMATRIX;
	static const string O_RLISTS;
	static const string O_NIST;
	static const string O_NONE;
	static const string O_DEFAULT;
	static const string SORT_NAME;
	static const string SORT_SCORE;
	static const string SORT_NONE;
	static const string SORT_DEFAULT;
	static const int O_STORAGE;

	// evaluation
	static const string S_SINGLE;
	static const string S_ULC;
	static const string S_QUEEN;
	static const string S_MODEL;
	static const map<string, int> eval_schemes;
	static const string DEFAULT_EVAL_CRITERION;

	// learning
	static const string LEARN_PERCEPTRON;
	static const double TRAINING_PROPORTION_DEFAULT;
	static const int N_EPOCHS_DEFAULT;
	static const int MIN_DIST_DEFAULT;
	static const string MODELS;
	static const string MODEL_DEFAULT;

	// meta-evaluation
	static const string C_REGRESSION;
	static const string C_PEARSON;
	static const string C_SPEARMAN;
	static const string C_KENDALL;
	static const string CI_NONE;
	static const string CI_FISHER;
	static const string CI_BOOTSTRAP;
	static const string CI_EXHAUSTIVE_BOOTSTRAP;
	static const string CI_PAIRED_BOOTSTRAP;
	static const string CI_EXHAUSTIVE_PAIRED_BOOTSTRAP;
	static const string CI_DEFAULT;
	static const map<string, int> rCI;
	static const double ALFA_DEFAULT;
	static const int N_RESAMPLINGS_DEFAULT;
	static const map<string, int> rCORRS;
	static const string C_KING;
	static const string C_ORANGE;
	static const string C_CONSISTENCY;
	static const string C_MRANKENDALL;
	static const map<string, int> rMRANKS;
	static const map<string, int> metaeval_criteria;
	static const string DEFAULT_METAEVAL_CRITERION;

	// input file format
	static const string I_NIST;
	static const string I_RAW;
	static const string I_DEFAULT;
	static const int tokenize;

	// text case
	static const string CASE_CS;
	static const string CASE_CI;
	static const string CASE_DEFAULT;

	// progress values
	static const int progress0;
	static const int progress1;
	static const int progress2;
	static const int progress3;

	// font sizes
	static const string FS_HUGE;
	static const string FS_LARGE;
	static const string FS_NORMAL;
	static const string FS_SMALL;
	static const string FS_TINY;
	static const string FS_DEFAULT;

	// other constants
	static const string EMPTY_ITEM;
	static string DATA_PATH;
	static const string ALIGN;
	static const string TMP;
	static const string REPORTS;
	static const int NRAND;
	static const int MINVALUE;
	static const string SOURCEID;
	static const int FLOAT_LENGTH_DEFAULT;
	static const int FLOAT_PRECISION_DEFAULT;
	static const int METRIC_NAME_LENGTH;
	static const int SET_NAME_LENGTH;
	static const int SYS_NAME_LENGTH;
	static const int DOC_NAME_LENGTH;
	static const int SEG_ID_LENGTH;
	static const int MIN_ID_LENGTH;
	static const int HLINE_LENGTH;
	static const string UNKNOWN_SET;
	static const string UNKNOWN_LANG;
	static const string UNKNOWN_GENRE;
	static const string UNKNOWN_DOC;
	static const int SENSIBLE_MAX_N;
	static const string ID_SEPARATOR;
	static const string CE ;
	static const string LeM;

	static void execute_or_die(string command, string message);
	static string give_system_name(string file);
	static string replace_special_characters(string &input);
	static double safe_division(double numerator, double denominator);

	//static double trunk_and_trim_number(double n, int l, int p);

	//static vector<int> reorder_scores(map<string, int> &hscores, string TGT, string G);

	//Printing
	static void print_hline(char c, int l);
	static void print_hline_stderr(char c, int l);

};


#endif
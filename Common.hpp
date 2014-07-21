#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>
#include <map>
using namespace std;

//FILE EXTENSIONS
extern const string SGMLEXT;
extern const string REPORTEXT;
extern const string SRCEXT;
extern const string REFEXT;
extern const string SYSEXT;
extern const string XMLEXT;
extern const string GZEXT;
extern const string TXTEXT;
extern const string IDXEXT;
extern const string DOCEXT;
extern const string TOKEXT;

//compression
extern const string GZIP;
extern const string GUNZIP;

//tools directory
extern const string TOOLS;

//application details
extern const string VERSION;
extern const string appVERSION;
extern const string appNAME;
extern const string appYEAR;
extern const string appAUTHOR;

//languages
extern const string L_ARA;
extern const string L_CAT;
extern const string L_CHN;
extern const string L_CZE;
extern const string L_DAN;
extern const string L_GER;
extern const string L_ENG;
extern const string L_SPA;
extern const string L_FIN;
extern const string L_FRN;
extern const string L_HUN;
extern const string L_ITA;
extern const string L_DUT;
extern const string L_NOR;
extern const string L_POR;
extern const string L_ROM;
extern const string L_RUS;
extern const string L_SWE;
extern const string L_TUR;
extern const string L_OTHER;
extern const string L_DEFAULT;
extern const map<string, int> rLANGS;

// granularity
extern const string G_SYS;
extern const string G_DOC;
extern const string G_SEG;
extern const string G_ALL;
extern const string G_DEFAULT;

// output format
extern const string O_MMATRIX;
extern const string O_SMATRIX;
extern const string O_RLISTS;
extern const string O_NIST;
extern const string O_NONE;
extern const string O_DEFAULT;
extern const string SORT_NAME;
extern const string SORT_SCORE;
extern const string SORT_NONE;
extern const string SORT_DEFAULT;
extern const int O_STORAGE;

// evaluation
extern const string S_SINGLE;
extern const string S_ULC;
extern const string S_QUEEN;
extern const string S_MODEL;
extern const map<string, int> eval_schemes;
extern const string DEFAULT_EVAL_CRITERION;

// learning
extern const string LEARN_PERCEPTRON;
extern const double TRAINING_PROPORTION_DEFAULT;
extern const int N_EPOCHS_DEFAULT;
extern const int MIN_DIST_DEFAULT;
extern const string MODELS;
extern const string MODEL_DEFAULT;

// meta-evaluation
extern const string C_REGRESSION;
extern const string C_PEARSON;
extern const string C_SPEARMAN;
extern const string C_KENDALL;
extern const string CI_NONE;
extern const string CI_FISHER;
extern const string CI_BOOTSTRAP;
extern const string CI_EXHAUSTIVE_BOOTSTRAP;
extern const string CI_PAIRED_BOOTSTRAP;
extern const string CI_EXHAUSTIVE_PAIRED_BOOTSTRAP;
extern const string CI_DEFAULT;
extern const map<string, int> rCI;
extern const double ALFA_DEFAULT;
extern const int N_RESAMPLINGS_DEFAULT;
extern const map<string, int> rCORRS;
extern const string C_KING;
extern const string C_ORANGE;
extern const string C_CONSISTENCY;
extern const string C_MRANKENDALL;
extern const map<string, int> rMRANKS;
extern const map<string, int> metaeval_criteria;
extern const string DEFAULT_METAEVAL_CRITERION;

// input file format
extern const string I_NIST;
extern const string I_RAW;
extern const string I_DEFAULT;
extern const int tokenize;

// text case
extern const string CASE_CS;
extern const string CASE_CI;
extern const string CASE_DEFAULT;

// progress values
extern const int progress0;
extern const int progress1;
extern const int progress2;
extern const int progress3;

// font sizes
extern const string FS_HUGE;
extern const string FS_LARGE;
extern const string FS_NORMAL;
extern const string FS_SMALL;
extern const string FS_TINY;
extern const string FS_DEFAULT;

// other constants
extern const string EMPTY_ITEM;
extern const string DATA_PATH;
extern const string ALIGN;
extern const string TMP;
extern const string REPORTS;
extern const int NRAND;
extern const int MINVALUE;
extern const string SOURCEID;
extern const int FLOAT_LENGTH_DEFAULT;
extern const int FLOAT_PRECISION_DEFAULT;
extern const int METRIC_NAME_LENGTH;
extern const int SET_NAME_LENGTH;
extern const int SYS_NAME_LENGTH;
extern const int DOC_NAME_LENGTH;
extern const int SEG_ID_LENGTH;
extern const int MIN_ID_LENGTH;
extern const int HLINE_LENGTH;
extern const string UNKNOWN_SET;
extern const string UNKNOWN_LANG;
extern const string UNKNOWN_GENRE;
extern const string UNKNOWN_DOC;
extern const int SENSIBLE_MAX_N;
extern const string ID_SEPARATOR;
extern const string CE ;
extern const string LeM;

void execute_or_die(string command, string message);
string give_system_name(string file);

#endif
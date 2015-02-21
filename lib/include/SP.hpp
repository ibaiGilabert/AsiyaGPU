#ifndef SP_HPP
#define SP_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

typedef vector<string> wParsed;
typedef vector<wParsed> sParsed;
typedef map<string, map< string, map<string, int> > > SNTfeatures;

class SP : public SingleMetric {
private:
	static set<string> create_rSPeng();
	static set<string> create_rSPspacat();
	static set<string> create_rSPfrench();
	static set<string> create_rSPgerman();

	static map<string, string> create_rLANGBIOS();
	static map<string, string> create_rLANGSVM();
	static map<string, string> create_rLANGBKLY();

	static const set<string> rSPeng, rSPspacat, rSPfrench, rSPgerman;
	static map<string, string> rLANGBIOS, rLANGSVM, rLANGBKLY;

	static const string SPEXT,	POSSEP, CSEP;
	static const string SVMT, 	BIOS;
	int USE_LEMMAS, USE_DICTS, USE_CHUNKS;

	void SNT_extract_features(const sParsed &snt, bool use_chunks, SNTfeatures &SNTc, SNTfeatures &SNTp);
	void SNT_compute_overlap_scores(SNTfeatures &Tout_c, SNTfeatures &Tout_p, SNTfeatures &Tref_c, SNTfeatures &Tref_p, map<string, double> &SCORES);

	void get_segment_scores(const vector< map<string, double> > &scores, string feature, int mode, double &SYSscore, vector<double> &SEGscores);

	void FILE_compute_overlap_metrics(const vector<sParsed> &FDout, const vector<sParsed> &FDref, vector< map<string, double> > &SCORES);

	void FILE_merge_BIOS(string input1, string input2, string output);

	void FILE_parse_BIOS(string input);
	int FILE_parse_BKLY(string input);
	int FILE_parse_SVM(string input);
	void FILE_parse(string input);
	void FILE_parse_and_read(string input, vector<sParsed> &FILE);

	void FILE_parse_split(string input);

public:
	SP();
	~SP();

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif
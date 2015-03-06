#ifndef CE_HPP
#define CE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class CE : public SingleMetric {
private:
	static set<string> create_rCE();
	static set<string> create_srcENG();
	static set<string> create_trgENG();
	static set<string> create_notENGSPA();
	static set<string> create_anyLANG();
	static set<string> create_rPUNCT();
	static map<string, string> create_rBIDICT();
	static map<string, map<string, double> > create_length_factor();
	static map<string, map<string, string> > create_LM_name();

	static const int BIDICT_MAX_NGRAM_LENGTH;
	static const string CEEXT, BIDICT_SEPARATOR, LM_path, LM_ext, lm_ext, raw, pos, chunk;

	static const set<string> rCE, srcENG, trgENG, notENGSPA, anyLANG, rPUNCT;
	static const map<string, string> rBIDICT;
	static const map<string, map<string, double> > length_factor;
	static map<string, map<string, string> > LM_name;



	void compute_language_modeling_features(string file, string lang, string cs, string variant, double &SYSoov, double &SYSlogp, double &SYSippl, vector<double> &SEGSoov, vector<double> &SEGSlogp, vector<double> &SEGSippl);
	void computeCE_segment_length(double &SYS, vector<double> &SEGS);

public:
	void doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ);

};



#endif
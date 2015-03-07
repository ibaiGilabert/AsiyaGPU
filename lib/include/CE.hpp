#ifndef CE_HPP
#define CE_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>
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
	static map<string, string> rBIDICT;
	static map<string, map<string, double> > length_factor;
	static map<string, map<string, string> > LM_name;

	void load_bidict(string source_lang, string target_lang, map<string, map<string, int> > &bidict);

	void compute_language_modeling_features(string file, string lang, string cs, string variant, double &SYSoov, double &SYSlogp, double &SYSippl, vector<double> &SEGSoov, vector<double> &SEGSlogp, vector<double> &SEGSippl);
	void computeCE_segment_length(double &SYS, vector<double> &SEGS);
	void computeCE_segment_length_ratio(string source, string target, double &length_score, double &long_score, double &short_score);
	void computeCE_length_ratio(string TGT, double &SYSlength, double &SYSlong, double &SYSshort, vector<double> &SEGSlength, vector<double> &SEGSlong, vector<double> &SEGSshort);

	map<string, int> extract_symbol_set(string text);
	double computeCE_segment_symbol_overlap(string source, string target);
	void computeCE_symbols_overlap(string TGT, double &SYS, vector<double> &SEGS);

	void merge_ngrams(map<string, int> &ngrams1, map<string, int> &ngrams2);
	void retrieve_mixed_ngrams(const vector<string> &tokens, const vector<string> &lemmas, int length, map<string, int> &ngrams);
	void retrieve_all_mixed_ngrams(const vector<string> &tokens, const vector<string> &lemmas, map<string, int> ngrams);
	pair<int, int> computeCE_bidict_segment_ambiguity(string segment, string lemma_segment, map<string, map<string, int> > &bidict);
	void computeCE_bidict_ambiguity(string lemma, map<string, map<string, int> > &bidict, double &SYS, vector<double> &SEGS);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif
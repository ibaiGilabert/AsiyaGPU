#ifndef NGRAM_HPP
#define NGRAM_HPP

#include "SingleMetric.hpp"

#include <vector>

class NGRAM : public SingleMetric {
private:
	static map<string, int> create_rNGRAM();
	static map<string, int> create_rCENGRAM();

	void read_NGRAM_segments(string reportNGRAM, string opt, map<string, vector<double> > &SEGS);

	void NGRAM_f_create_doc(string input, string output);

	void computeNGRAM(string opt, string ref, string out, int issrcbased, map<string, vector<double> > &SEGS);
	void computeMultiNGRAM(string opt, string out, int issrcbased, map<string, double> &MAXSYS, map<string, vector<double> > &MAXSEG);

	static const map<string, int> rNGRAM, rCENGRAM;
	static const string EMPTY_ITEM, TNGRAM, TNGRAMdir, TRANSLITERATOR;
	static const string NGRAMSRC, NGRAMREF, NGRAMEXT, CENGRAMEXT;

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);
};



#endif
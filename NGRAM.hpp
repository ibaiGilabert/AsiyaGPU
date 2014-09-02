#ifndef NGRAM_HPP
#define NGRAM_HPP

#include "SingleMetric.hpp"

#include <vector>

class NGRAM : public SingleMetric {
private:
	static map<string, int> create_rMETEOR();
	static map<string, int> create_rLANG_STM();
	static map<string, int> create_rLANG_PARA();
	static map<string, int> create_rLANG_SYN();
	static map<string, string> create_rLANG();

	MetricScore computeMETEOR(string TGT, string variant);

public:

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string MTREXT, TMETEOR, METEORSCRIPT;
	static const map<string, int> rMETEOR, rLANG_STM, rLANG_PARA, rLANG_SYN;
	static map<string, string> rLANG;

	static const string EMPTY_ITEM, TNGRAM, TNGRAMdir, TRANSLITERATOR;
	static const string NGRAMSRC, NGRAMREF, NGRAMEXT, CENGRAMEXT;
};



#endif
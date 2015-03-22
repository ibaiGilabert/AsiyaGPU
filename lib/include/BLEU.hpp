#ifndef BLEU_HPP
#define BLEU_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <set>

class BLEU : public SingleMetric {
private:
	static set<string> create_rBLEU();
	
	static const string BLEUEXT,	BLEUEXTi,	TBLEU;
	static const set<string> rBLEU;

	void read_bleu(string reportBLEU, vector<double> &SYS);
	void read_bleu_segments(string reportBLEU, vector<vector<double> > &SEG);

	MetricScore computeBLEUN(string TGT);
	void computeBLEU(string TGT, vector<double> &SYS, vector<vector<double> > &SEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif
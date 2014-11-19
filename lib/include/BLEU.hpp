#ifndef BLEU_HPP
#define BLEU_HPP

#include "SingleMetric.hpp"

#include <vector>

class BLEU : public SingleMetric {
private:
	static map<string, int> create_rBLEU();
	static const string BLEUEXT,	BLEUEXTi,	TBLEU;
	static const map<string, int> rBLEU;

	vector<double> read_bleu(string reportBLEU);
	vector<vector<double> > read_bleu_segments(string reportBLEU);

	MetricScore computeBLEUN(string TGT);
	void computeBLEU(string TGT, vector<double> &SYS, vector<vector<double> > &SEG);

public:
	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif
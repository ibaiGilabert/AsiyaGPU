#ifndef BLEU_HPP
#define BLEU_HPP

#include "Scores"

#include <vector>

class BLEU : public SingleMetric {
private:
	vector<double> read_bleu(string reportBLEU);
	vector<vector<double> > read_bleu_segments(string reportBLEU);

	pair<vector<double>, vector<vector<double> > > computeBLEU();


public:
	void doMetric(Scores &hOQ);	//map<string, double> &hOQ);

	static const string BLEUEXT,	BLEUEXTi,	TBLEU;
	static const map<string, int> rBLEU;
};



#endif
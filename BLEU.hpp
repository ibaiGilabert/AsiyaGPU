#ifndef BLEU_HPP
#define BLEU_HPP

#include "SingleMetric.hpp"

#include <vector>

class BLEU : public SingleMetric {
private:
	static map<string, int> create_rBLEU();

	vector<double> read_bleu(string reportBLEU);
	vector<vector<double> > read_bleu_segments(string reportBLEU);

	pair<vector<double>, vector<vector<double> > > computeBLEU(string TGT);

public:
	//BLEU() { cout << "######################## CONSTRUCTOR BLEU #########################" << endl; }
	//~BLEU() { cout << "######################## DESTRUCTOR BLEU #########################" << endl; }

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

	static const string BLEUEXT,	BLEUEXTi,	TBLEU;
	static const map<string, int> rBLEU;
};



#endif
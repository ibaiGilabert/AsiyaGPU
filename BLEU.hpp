#ifndef BLEU_HPP
#define BLEU_HPP

class BLEU : public SingleMetric {
private:

public:
	void doMetric(map<string, double> &hOQ);

	static const string BLEUEXT,	BLEUEXTi,	TBLEU;
	static const map<string, int> rBLEU;
};



#endif
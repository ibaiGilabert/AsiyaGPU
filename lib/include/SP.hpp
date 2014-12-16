#ifndef SP_HPP
#define SP_HPP

#include "SingleMetric.hpp"

#include <vector>
#include <map>

class SP : public SingleMetric {
private:
	static set<string> create_rSPeng();
	static set<string> create_rSPspacat();
	static set<string> create_rSPfrench();
	static set<string> create_rSPgerman();

	static map<string, string> create_rLANGBIOS();
	static map<string, string> create_rLANGSVM();
	static map<string, string> create_rLANGBKLY();
	static map<string, string> create_rLANGTOK();

	static const set<string> rSPeng, rSPspacat, rSPfrench, rSPgerman;
	static const map<string, string> rLANGBIOS, rLANGSVM, rLANGBKLY, rLANGTOK;

	static const string SPEXT, POSSEP, CSEP;
	static const string SVMT, DICTS, BIOS, TOK;
	int USE_LEMMAS, USE_DICTS, USE_CHUNKS;

	void FILE_parse_BIOS(string input);
	int FILE_parse_BKLY(string input);
	int FILE_parse_SVM(string input);
	void FILE_parse(string input);
	void FILE_parse_and_read(string input);

public:
	SP();
	~SP();

	void doMetric(string TGT, string REF, string prefix, Scores &hOQ);

};



#endif
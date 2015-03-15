#include "../include/SR.hpp"
#include "../include/SRXLike.hpp"
#include "../include/NE.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


const string SR::SREXT = "SR";
const string SR::SWIRL = "swirl-1.1.0";

set<string> SR::create_rSReng() {
	set<string> rSReng;
	rSReng.insert(SR::SREXT+"-Nv"); 			rSReng.insert(SR::SREXT+"-Ov"); 			rSReng.insert(SR::SREXT+"-Or");				rSReng.insert(SR::SREXT+"-Orv");
	rSReng.insert(SR::SREXT+"-Mrv(*)"); 		rSReng.insert(SR::SREXT+"-Mrv(A0)"); 		rSReng.insert(SR::SREXT+"-Mrv(A1)");
	rSReng.insert(SR::SREXT+"-Mrv(A2)"); 		rSReng.insert(SR::SREXT+"-Mrv(A3)"); 		rSReng.insert(SR::SREXT+"-Mrv(A4)");
	rSReng.insert(SR::SREXT+"-Mrv(A5)"); 		rSReng.insert(SR::SREXT+"-Mrv(AA)"); 		rSReng.insert(SR::SREXT+"-Mrv(AM-ADV)");
	rSReng.insert(SR::SREXT+"-Mrv(AM-CAU)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-DIR)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-DIS)");
	rSReng.insert(SR::SREXT+"-Mrv(AM-EXT)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-LOC)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-MNR)");
	rSReng.insert(SR::SREXT+"-Mrv(AM-MOD)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-NEG)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-PNC)");
	rSReng.insert(SR::SREXT+"-Mrv(AM-PRD)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-REC)"); 	rSReng.insert(SR::SREXT+"-Mrv(AM-TMP)");
	rSReng.insert(SR::SREXT+"-Orv(*)"); 		rSReng.insert(SR::SREXT+"-Orv(A0)"); 		rSReng.insert(SR::SREXT+"-Orv(A1)");
	rSReng.insert(SR::SREXT+"-Orv(A2)"); 		rSReng.insert(SR::SREXT+"-Orv(A3)"); 		rSReng.insert(SR::SREXT+"-Orv(A4)");
	rSReng.insert(SR::SREXT+"-Orv(A5)"); 		rSReng.insert(SR::SREXT+"-Orv(AA)"); 		rSReng.insert(SR::SREXT+"-Orv(AM-ADV)");
	rSReng.insert(SR::SREXT+"-Orv(AM-CAU)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-DIR)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-DIS)");
	rSReng.insert(SR::SREXT+"-Orv(AM-EXT)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-LOC)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-MNR)");
	rSReng.insert(SR::SREXT+"-Orv(AM-MOD)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-NEG)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-PNC)");
	rSReng.insert(SR::SREXT+"-Orv(AM-PRD)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-REC)"); 	rSReng.insert(SR::SREXT+"-Orv(AM-TMP)");
	rSReng.insert(SR::SREXT+"-Mr(*)"); 			rSReng.insert(SR::SREXT+"-Mr(A0)"); 		rSReng.insert(SR::SREXT+"-Mr(A1)");
	rSReng.insert(SR::SREXT+"-Mr(A2)"); 		rSReng.insert(SR::SREXT+"-Mr(A3)"); 		rSReng.insert(SR::SREXT+"-Mr(A4)");
	rSReng.insert(SR::SREXT+"-Mr(A5)"); 		rSReng.insert(SR::SREXT+"-Mr(AA)"); 		rSReng.insert(SR::SREXT+"-Mr(AM-ADV)");
	rSReng.insert(SR::SREXT+"-Mr(AM-CAU)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-DIR)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-DIS)");
	rSReng.insert(SR::SREXT+"-Mr(AM-EXT)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-LOC)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-MNR)");
	rSReng.insert(SR::SREXT+"-Mr(AM-MOD)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-NEG)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-PNC)");
	rSReng.insert(SR::SREXT+"-Mr(AM-PRD)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-REC)"); 	rSReng.insert(SR::SREXT+"-Mr(AM-TMP)");
	rSReng.insert(SR::SREXT+"-Or(*)"); 			rSReng.insert(SR::SREXT+"-Or(A0)"); 		rSReng.insert(SR::SREXT+"-Or(A1)");
	rSReng.insert(SR::SREXT+"-Or(A2)"); 		rSReng.insert(SR::SREXT+"-Or(A3)"); 		rSReng.insert(SR::SREXT+"-Or(A4)");
	rSReng.insert(SR::SREXT+"-Or(A5)"); 		rSReng.insert(SR::SREXT+"-Or(AA)"); 		rSReng.insert(SR::SREXT+"-Or(AM-ADV)");
	rSReng.insert(SR::SREXT+"-Or(AM-CAU)"); 	rSReng.insert(SR::SREXT+"-Or(AM-DIR)"); 	rSReng.insert(SR::SREXT+"-Or(AM-DIS)");
	rSReng.insert(SR::SREXT+"-Or(AM-EXT)"); 	rSReng.insert(SR::SREXT+"-Or(AM-LOC)"); 	rSReng.insert(SR::SREXT+"-Or(AM-MNR)");
	rSReng.insert(SR::SREXT+"-Or(AM-MOD)"); 	rSReng.insert(SR::SREXT+"-Or(AM-NEG)"); 	rSReng.insert(SR::SREXT+"-Or(AM-PNC)");
	rSReng.insert(SR::SREXT+"-Or(AM-PRD)"); 	rSReng.insert(SR::SREXT+"-Or(AM-REC)"); 	rSReng.insert(SR::SREXT+"-Or(AM-TMP)"); 
	rSReng.insert(SR::SREXT+"-Ol"); 			rSReng.insert(SR::SREXT+"-Or(*)_b"); 		rSReng.insert(SR::SREXT+"-Or(*)_i");
	rSReng.insert(SR::SREXT+"-Mr(*)_b"); 		rSReng.insert(SR::SREXT+"-Mr(*)_i"); 		rSReng.insert(SR::SREXT+"-Orv(*)_b");
	rSReng.insert(SR::SREXT+"-Orv(*)_i"); 		rSReng.insert(SR::SREXT+"-Mrv(*)_b"); 		rSReng.insert(SR::SREXT+"-Mrv(*)_i");
	rSReng.insert(SR::SREXT+"-Or_b"); 			rSReng.insert(SR::SREXT+"-Or_i"); 			rSReng.insert(SR::SREXT+"-Orv_b");
	rSReng.insert(SR::SREXT+"-Orv_i");
	rSReng.insert(SR::SREXT+"-Pr(*)"); 			rSReng.insert(SR::SREXT+"-Rr(*)"); 			rSReng.insert(SR::SREXT+"-Fr(*)");
	rSReng.insert(SR::SREXT+"-MPr(*)"); 		rSReng.insert(SR::SREXT+"-MRr(*)"); 		rSReng.insert(SR::SREXT+"-MFr(*)");
	rSReng.insert(SR::SREXT+"-Ora"); 			rSReng.insert(SR::SREXT+"-Mra(*)");			rSReng.insert(SR::SREXT+"-Ora(*)");               
	return rSReng;
}
set<string> SR::rSReng = create_rSReng();
/*
set<string> SR::create_rSRspacat() {
	set<string> rSRspacat;
	rSRspacat.insert(SR::SREXT+"-Nv"); rSRspacat.insert(SR::SREXT+"-Ov"); rSRspacat.insert(SR::SREXT+"-Or"); rSRspacat.insert(SR::SREXT+"-Orv");
	rSRspacat.insert(SR::SREXT+"-Mrv(*)"); rSRspacat.insert(SR::SREXT+"-Mrv(A0)"); rSRspacat.insert(SR::SREXT+"-Mrv(A1)");
	rSRspacat.insert(SR::SREXT+"-Mrv(A2)"); rSRspacat.insert(SR::SREXT+"-Mrv(A3)"); rSRspacat.insert(SR::SREXT+"-Mrv(A4)");
	rSRspacat.insert(SR::SREXT+"-Mrv(A5)"); rSRspacat.insert(SR::SREXT+"-Mrv(A6)"); rSRspacat.insert(SR::SREXT+"-Mrv(A7)");
	rSRspacat.insert(SR::SREXT+"-Mrv(A8)"); rSRspacat.insert(SR::SREXT+"-Mrv(A9)"); rSRspacat.insert(SR::SREXT+"-Mrv(AM-LOC)");
	rSRspacat.insert(SR::SREXT+"-Mrv(AM-TMP)"); rSRspacat.insert(SR::SREXT+"-Mrv(AM-MNR)"); rSRspacat.insert(SR::SREXT+"-Mrv(AM-ADV)");
	rSRspacat.insert(SR::SREXT+"-Mrv(Attribute)"); rSRspacat.insert(SR::SREXT+"-Mrv(Beneficiary)"); rSRspacat.insert(SR::SREXT+"-Mrv(Cause)");
	rSRspacat.insert(SR::SREXT+"-Mrv(Destination)"); rSRspacat.insert(SR::SREXT+"-Mrv(Final_State)"); rSRspacat.insert(SR::SREXT+"-Mrv(Initial_State)");
	rSRspacat.insert(SR::SREXT+"-Mrv(Experiencer)"); rSRspacat.insert(SR::SREXT+"-Mrv(Extent)"); rSRspacat.insert(SR::SREXT+"-Mrv(Goal)");
	rSRspacat.insert(SR::SREXT+"-Mrv(Instrument)"); rSRspacat.insert(SR::SREXT+"-Mrv(Location)"); rSRspacat.insert(SR::SREXT+"-Mrv(Initial_Location)");
	rSRspacat.insert(SR::SREXT+"-Mrv(Patient)"); rSRspacat.insert(SR::SREXT+"-Mrv(Source)"); rSRspacat.insert(SR::SREXT+"-Mrv(Theme)");

	rSRspacat.insert(SR::SREXT+"-Orv(*)"); rSRspacat.insert(SR::SREXT+"-Orv(A0)"); rSRspacat.insert(SR::SREXT+"-Orv(A1)");
	rSRspacat.insert(SR::SREXT+"-Orv(A2)"); rSRspacat.insert(SR::SREXT+"-Orv(A3)"); rSRspacat.insert(SR::SREXT+"-Orv(A4)");
	rSRspacat.insert(SR::SREXT+"-Orv(A5)"); rSRspacat.insert(SR::SREXT+"-Orv(A6)"); rSRspacat.insert(SR::SREXT+"-Orv(A7)");
	rSRspacat.insert(SR::SREXT+"-Orv(A8)"); rSRspacat.insert(SR::SREXT+"-Orv(A9)"); rSRspacat.insert(SR::SREXT+"-Orv(AM-LOC)");
	rSRspacat.insert(SR::SREXT+"-Orv(AM-TMP)"); rSRspacat.insert(SR::SREXT+"-Orv(AM-MNR)"); rSRspacat.insert(SR::SREXT+"-Orv(AM-ADV)");
	rSRspacat.insert(SR::SREXT+"-Orv(Attribute)"); rSRspacat.insert(SR::SREXT+"-Orv(Beneficiary)"); rSRspacat.insert(SR::SREXT+"-Orv(Cause)");
	rSRspacat.insert(SR::SREXT+"-Orv(Destination)"); rSRspacat.insert(SR::SREXT+"-Orv(Final_State)"); rSRspacat.insert(SR::SREXT+"-Orv(Initial_State)");
	rSRspacat.insert(SR::SREXT+"-Orv(Experiencer)"); rSRspacat.insert(SR::SREXT+"-Orv(Extent)"); rSRspacat.insert(SR::SREXT+"-Orv(Goal)");
	rSRspacat.insert(SR::SREXT+"-Orv(Instrument)"); rSRspacat.insert(SR::SREXT+"-Orv(Location)"); rSRspacat.insert(SR::SREXT+"-Orv(Initial_Location)");
	rSRspacat.insert(SR::SREXT+"-Orv(Patient)"); rSRspacat.insert(SR::SREXT+"-Orv(Source)"); rSRspacat.insert(SR::SREXT+"-Orv(Theme)");

	rSRspacat.insert(SR::SREXT+"-Mr(*)"); rSRspacat.insert(SR::SREXT+"-Mr(A0)"); rSRspacat.insert(SR::SREXT+"-Mr(A1)");
	rSRspacat.insert(SR::SREXT+"-Mr(A2)"); rSRspacat.insert(SR::SREXT+"-Mr(A3)"); rSRspacat.insert(SR::SREXT+"-Mr(A4)");
	rSRspacat.insert(SR::SREXT+"-Mr(A5)"); rSRspacat.insert(SR::SREXT+"-Mr(A6)"); rSRspacat.insert(SR::SREXT+"-Mr(A7)");
	rSRspacat.insert(SR::SREXT+"-Mr(A8)"); rSRspacat.insert(SR::SREXT+"-Mr(A9)"); rSRspacat.insert(SR::SREXT+"-Mr(AM-LOC)");
	rSRspacat.insert(SR::SREXT+"-Mr(AM-TMP)"); rSRspacat.insert(SR::SREXT+"-Mr(AM-MNR)"); rSRspacat.insert(SR::SREXT+"-Mr(AM-ADV)");
	rSRspacat.insert(SR::SREXT+"-Mr(Attribute)"); rSRspacat.insert(SR::SREXT+"-Mr(Beneficiary)"); rSRspacat.insert(SR::SREXT+"-Mr(Cause)");
	rSRspacat.insert(SR::SREXT+"-Mr(Destination)"); rSRspacat.insert(SR::SREXT+"-Mr(Final_State)"); rSRspacat.insert(SR::SREXT+"-Mr(Initial_State)");
	rSRspacat.insert(SR::SREXT+"-Mr(Experiencer)"); rSRspacat.insert(SR::SREXT+"-Mr(Extent)"); rSRspacat.insert(SR::SREXT+"-Mr(Goal)");
	rSRspacat.insert(SR::SREXT+"-Mr(Instrument)"); rSRspacat.insert(SR::SREXT+"-Mr(Location)"); rSRspacat.insert(SR::SREXT+"-Mr(Initial_Location)");
	rSRspacat.insert(SR::SREXT+"-Mr(Patient)"); rSRspacat.insert(SR::SREXT+"-Mr(Source)"); rSRspacat.insert(SR::SREXT+"-Mr(Theme)");

	rSRspacat.insert(SR::SREXT+"-Or(*)"); rSRspacat.insert(SR::SREXT+"-Or(A0)"); rSRspacat.insert(SR::SREXT+"-Or(A1)");
	rSRspacat.insert(SR::SREXT+"-Or(A2)"); rSRspacat.insert(SR::SREXT+"-Or(A3)"); rSRspacat.insert(SR::SREXT+"-Or(A4)");
	rSRspacat.insert(SR::SREXT+"-Or(A5)"); rSRspacat.insert(SR::SREXT+"-Or(A6)"); rSRspacat.insert(SR::SREXT+"-Or(A7)");
	rSRspacat.insert(SR::SREXT+"-Or(A8)"); rSRspacat.insert(SR::SREXT+"-Or(A9)"); rSRspacat.insert(SR::SREXT+"-Or(AM-LOC)");
	rSRspacat.insert(SR::SREXT+"-Or(AM-TMP)"); rSRspacat.insert(SR::SREXT+"-Or(AM-MNR)"); rSRspacat.insert(SR::SREXT+"-Or(AM-ADV)");
	rSRspacat.insert(SR::SREXT+"-Or(Attribute)"); rSRspacat.insert(SR::SREXT+"-Or(Beneficiary)"); rSRspacat.insert(SR::SREXT+"-Or(Cause)");
	rSRspacat.insert(SR::SREXT+"-Or(Destination)"); rSRspacat.insert(SR::SREXT+"-Or(Final_State)"); rSRspacat.insert(SR::SREXT+"-Or(Initial_State)");
	rSRspacat.insert(SR::SREXT+"-Or(Experiencer)"); rSRspacat.insert(SR::SREXT+"-Or(Extent)"); rSRspacat.insert(SR::SREXT+"-Or(Goal)");
	rSRspacat.insert(SR::SREXT+"-Or(Instrument)"); rSRspacat.insert(SR::SREXT+"-Or(Location)"); rSRspacat.insert(SR::SREXT+"-Or(Initial_Location)");
	rSRspacat.insert(SR::SREXT+"-Or(Patient)"); rSRspacat.insert(SR::SREXT+"-Or(Source)"); rSRspacat.insert(SR::SREXT+"-Or(Theme)");

	rSRspacat.insert(SR::SREXT+"-Ol"); rSRspacat.insert(SR::SREXT+"-Or(*)_b"); rSRspacat.insert(SR::SREXT+"-Or(*)_i");
	rSRspacat.insert(SR::SREXT+"-Mr(*)_b"); rSRspacat.insert(SR::SREXT+"-Mr(*)_i"); rSRspacat.insert(SR::SREXT+"-Orv(*)_b");
	rSRspacat.insert(SR::SREXT+"-Orv(*)_i"); rSRspacat.insert(SR::SREXT+"-Mrv(*)_b"); rSRspacat.insert(SR::SREXT+"-Mrv(*)_i");
	rSRspacat.insert(SR::SREXT+"-Or_b"); rSRspacat.insert(SR::SREXT+"-Or_i"); rSRspacat.insert(SR::SREXT+"-Orv_b");
	rSRspacat.insert(SR::SREXT+"-Orv_i");
	rSRspacat.insert(SR::SREXT+"-Pr(*)"); rSRspacat.insert(SR::SREXT+"-Rr(*)"); rSRspacat.insert(SR::SREXT+"-Fr(*)");
	rSRspacat.insert(SR::SREXT+"-MPr(*)"); rSRspacat.insert(SR::SREXT+"-MRr(*)"); rSRspacat.insert(SR::SREXT+"-MFr(*)");
	rSRspacat.insert(SR::SREXT+"-Ora"); rSRspacat.insert(SR::SREXT+"-Mra(*)"); rSRspacat.insert(SR::SREXT+"-Ora(*)");
	return rSRspacat;
}
set<string> SR::rSRspacat = create_rSRspacat();
*/

void SR::parse_SR(string input, string L, string C, vector<sParsed> &FILE_S, vector< vector<rParsed> > &FILE_R, vector< vector<vector<string> > > &FILE_V) {
    // description _ responsible for SR
    //               (WORD + PoS)  ->  (WORD + SR)
    //  -------------- FILES -----------------------------------------------------
	string wpnercfile 	= input+"."+NE::NEEXT+".wpn";
	string srlfile 		= input+"."+SR::SREXT;
	string wpnsrlfile	= input+"."+SR::SREXT+".wpn";
	string wlpcnercfile = input+"."+NE::NEEXT+".wlpcn";

	NE ne;
	//	void FILE_parse_and_read(string input, string L, string C, vector<sParsed> &FILE);	// SR
	vector<sParsed> NERC;
	ne.FILE_parse_and_read(input, L, C, NERC);

	//  -------------- WLPCN -----------------------------------------------------
	if (!exists(boost::filesystem::path(wlpcnercfile)) and exists(boost::filesystem::path(wlpcnercfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+wlpcnercfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	vector<sParsed> wlpcn;

	ifstream CAND(input.c_str());
	if (!CAND.is_open()) { fprintf(stderr, "couldn't open file: %s\n", input.c_str()); exit(1); }

	ifstream WLPCN(wlpcnercfile.c_str());
	if (WLPCN) {
		int i = 0;
		int EMPTY = 1;
		string line, candline;
		getline(CAND, candline);
	 	boost::match_results<string::const_iterator> results;
		while( getline(WLPCN, line) ) {
			if (line.empty()) {	
				if (EMPTY) {	// empty sentence
					vector<string> l(5);
					l[0] = Common::EMPTY_ITEM;	l[1] = Common::EMPTY_ITEM;	l[2] = Common::EMPTY_ITEM;	l[3] = "O";	l[4] = "O";
					wlpcn[i].push_back(l);
					EMPTY = 0;
				}
				else {	// sentence separator
					EMPTY = 1;
					++i;
					// read next line in CAND
					getline(CAND, candline);
					// if it contains only punctuation, add the asterisk at the beginning to prevent parser failure
					if (!candline.empty() and boost::regex_match(candline, results, Common::reSR_punct)) {
						// add the asterisk
						vector<string> l(5, "*");	l[3] = "O";	l[4] = "O";		// W P L C NE  (empty)
						wlpcn[i].push_back(l);
					}
				}
			}
			else {
				vector<string> entry;
				boost::split(entry, line, boost::is_any_of("\t "));
				wlpcn[i].push_back(entry);
				EMPTY = 0;
			}
		}
		CAND.close();
		WLPCN.close();
	}
    else { fprintf(stderr, "couldn't open file: %s\n", wlpcnercfile.c_str()); exit(1); }

    if (exists(boost::filesystem::path(wlpcnercfile))) {
    	string sys_aux = Common::GZIP+" "+wlpcnercfile;
    	system(sys_aux.c_str());
    }
	// -------------------------------------------------------------------------

	if (!exists(boost::filesystem::path(srlfile)) and !exists(boost::filesystem::path(srlfile+"."+Common::GZEXT))) {
		ofstream AUX(wpnsrlfile.c_str());
		if (AUX) {	
			int i = 0;
			for(int snt = 0; snt < wlpcn.size(); ++snt) {
				vector<string> line;
				int countw = 0;
				for (int elem = 0; elem < wlpcn[snt].size(); ++elem) {
					string word = wlpcn[snt][elem][0];	word = boost::regex_replace(word, Common::reSR_parse1, "\\\"");
					string pos  = wlpcn[snt][elem][2];	pos  = boost::regex_replace(pos, Common::reSR_parse1, "\\\"");
					string ne 	= wlpcn[snt][elem][4];	ne   = boost::regex_replace(ne, Common::reSR_parse1, "\\\"");
					string aux = word+" "+pos+" "+ne;
					line.push_back(aux);
					++countw;
					if (countw >= 400) break;
				}
				AUX << "1 ";
				if (line.size()) {
					AUX << line[0];
					for(int k = 1; k < line.size(); ++k) AUX << " " << line[k];
					AUX << endl;
				}
			}
			AUX.close();
		}
	    else { fprintf(stderr, "couldn't open file: %s\n", wpnsrlfile.c_str()); exit(1); }

	    if (L == Common::L_ENG) {
	    	if (!exists(boost::filesystem::path(srlfile)) and !exists(boost::filesystem::path(srlfile+"."+Common::GZEXT))) {
	         	string exe = "cd "+Common::DATA_PATH+"; "+Config::tools+"/"+SR::SWIRL+"/src/bin/swirl_parse_classify"+((C == Common::CASE_CI)? " --case-insensitive" : "")+" "+Config::tools+"/"+SR::SWIRL+"/model_swirl "+Config::tools+"/"+SR::SWIRL+"/model_charniak "+wpnsrlfile+" > "+srlfile;
	         	Common::execute_or_die(exe, "[ERROR] problems running SwiRL...");
	    	}
	    }
	    else { fprintf(stderr, "[SR] tool for <%s> unavailable!!!\n", L.c_str()); exit(1); }

	    if (exists(boost::filesystem::path(wpnsrlfile))) {
	    	string sys_aux = "rm -f "+wpnsrlfile;
	    	system(sys_aux.c_str());
	    }
	}

	if (!exists(boost::filesystem::path(srlfile)) and exists(boost::filesystem::path(srlfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+srlfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

fprintf(stderr, "[wlpcn].size(): %d\n", (int)wlpcn.size());

	ifstream AUX(srlfile.c_str());
	if (AUX) {
		int i = 0, j = 0;
		vector<string> TAG;
		boost::match_results<string::const_iterator> results;
		string line;
		while( getline(AUX, line) ) {
			if (line.empty()) {
				++i; j = 0;
				if ((i-1) < wlpcn.size())
					FILE_S[i-1] = wlpcn[i-1];
			}
			else {
				vector<string> entry;
				boost::split(entry, line, boost::is_any_of("\t"), boost::token_compress_on);
				if (entry[0] != "-") {
					vector<string> l(2);	l[0] = boost::lexical_cast<string>(j);	l[1] = entry[0];
					FILE_V[i].push_back(l);
				}
				FILE_R[i].resize(entry.size());
				TAG.resize(entry.size());
				for (int k = 1; k < entry.size(); ++k) {
					if (entry[k] != "*") {
						vector<string> tag;
						boost::split(tag, entry[k], boost::is_any_of("[\\(\\*]"));
					 	if (boost::regex_match(entry[k], results, Common::reSR_INSIDE_PAR))
					 		FILE_R[i][k-1][tag[1]].push_back(j);
						else {
							if (tag[1] == ")")
								FILE_R[i][k-1][TAG[k-1]].push_back(j);
							else {
								FILE_R[i][k-1][tag[1]].push_back(j);	
								TAG[k-1] = tag[1];
							}
						}
					}
				}
				++j;
			}
		}
		AUX.close();
	}
    else { fprintf(stderr, "couldn't open file: %s\n", srlfile.c_str()); exit(1); }

    if (exists(boost::filesystem::path(srlfile))) {
    	string sys_aux = Common::GZIP+" "+srlfile;
    	system(sys_aux.c_str());
    }
}

void SR::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes SR score (multiple references)
	set<string> rF;
	if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) rF = SRXLike::rSRspacat;
	else rF = SR::rSReng;

	bool GO_ON = false;
	for (set<string>::const_iterator it = rF.begin(); !GO_ON and it != rF.end(); ++it) {
		if (Config::Hmetrics.count(*it))
			GO_ON = true;
	}

	if (GO_ON) {
		if (Config::verbose) fprintf(stderr, "%s\n", SR::SREXT.c_str());

		int DO_METRICS = Config::remake;
		if (!DO_METRICS) {
			for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
				string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+*it+"."+Common::XMLEXT;
				if (Config::Hmetrics.count(*it)  and !exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML+"."+Common::GZEXT))) DO_METRICS = 1;
			}
		}

		if (DO_METRICS) {
			// parse
			if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) {
				//FDout = SRXLike::parse_SR();
			}
			else if (Config::LANG == Common::L_ENG) {
				// RESIZE all vectors output to TESTBED::wc[TGT]
				vector<sParsed> FDout_S(TESTBED::wc[TGT]);
				vector< vector<rParsed> > FDout_R(TESTBED::wc[TGT]);
				vector< vector<vector<string> > > FDout_V(TESTBED::wc[TGT]);
				parse_SR(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, FDout_S, FDout_R, FDout_V);
			}
			else { fprintf(stderr, "[SR] tool for <%s> unavailable!!!\n", Config::LANG.c_str()); exit(1); }

		}
	}

	/*
	vector<string> mSR(SR::rLANG[Config::LANG].size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = SR::rLANG[Config::LANG].begin(); it != SR::rLANG[Config::LANG].end(); ++it, ++i)
		mSR[i] = *it;


	for (i = 0; i < mSR.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mSR[i]) != Config::Hmetrics.end()) GO = 1;
	}
	
	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s...\n", rSReng.insert(SR::SREXT.c_str());

		for (i = 0; i < mSR.size(); ++i) {
			string reportSRxml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+mSR[i]+"."+Common::XMLEXT;
		    boost::filesystem::path reportSRxml_path(reportSRxml);
	   		boost::filesystem::path reportSRxml_gz(reportSRxml+"."+Common::GZEXT);
	   		if ( (!exists(reportSRxml_path) and !exists(reportSRxml_gz)) or Config::remake) {
	   			double SYS;
	   			vector<double> SEG, d_scores, s_scores;

	   			computeMultiSR(mSR[i], TGT, SYS, SEG);
				TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);

				string pref = prefix + mSR[i];
		    	if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, pref, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
				}
	         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(rSReng.insert(SR::SREXT, TGT, REF));
	   		}
		}
	}*/
}


/*
for(map<string, set<string> >::const_iterator it = SR::rLANG.begin(); it != SR::rLANG.end(); ++it) {
    cout << "\t" << it->first << " -> " << endl;
    set<string> aux = it->second;
    for(set<string>::const_iterator is = aux.begin(); is != aux.end(); ++is) {
            cout << "\t\t[" << *is << "]" << endl;
    }
}
*/
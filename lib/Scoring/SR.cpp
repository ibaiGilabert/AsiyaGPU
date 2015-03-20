#include "../include/SR.hpp"
#include "../include/SRXLike.hpp"
#include "../include/NE.hpp"
#include "../include/Overlap.hpp"

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
	vector<sParsed> NERC(FILE_S.size());
	ne.FILE_parse_and_read(input, L, C, NERC);

	//  -------------- WLPCN -----------------------------------------------------
	if (!exists(boost::filesystem::path(wlpcnercfile)) and exists(boost::filesystem::path(wlpcnercfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+wlpcnercfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	vector<sParsed> wlpcn(FILE_S.size());

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

	//fprintf(stderr, "[wlpcn].size(): %d\n", (int)wlpcn.size());
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
				FILE_R[i].resize(entry.size()-1);
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

//typedef map<string, vector<int> > rParsed;
void SR::SNT_extract_features(const sParsed &snt_s, const vector<rParsed> &snt_r, const vector<vector<string> > &snt_v, SNTextract_feat &SNT) {
	// description _ extracts features from a given SR-parsed sentence.
	if (snt_s.size()) {		// if (snt is defined???)		OJU AQUI!
		if (snt_r.size()) {

	/*fprintf(stderr, "---- snt_r ----\n");
	for (int r = 0; r < snt_r.size(); ++r) {
		map<string, vector<int> > r_aux = snt_r[r];
		for (map<string, vector<int> >::const_iterator it = r_aux.begin(); it != r_aux.end(); ++it) {
			fprintf(stderr, "[%s", it->first.c_str());
			for(int l = 0; l < it->second.size(); ++l) fprintf(stderr, ", %d\n", it->second[l]);
		}
	}
	fprintf(stderr, "---------------\n");*/

    /*fprintf(stderr, "check snt_v[%d] (%d)\n", i, (int)snt_v[i].size());
    for (int v = 0; v < snt_v[i].size(); ++v) {
            fprintf(stderr, "PUTA!!!!\n");
            fprintf(stderr, "snt_v[%d][%d]: %s\n", i, v, (snt_v[i][v]).c_str());
    }
    fprintf(stderr, "vale o no?\n");*/


			int i = 0;
			while (i < snt_r.size()) {	// i -> num of predicates
				string verb = snt_v[i][1];	 // verb of the predicate
				for (rParsed::const_iterator it = snt_r[i].begin(); it != snt_r[i].end(); ++it) {	// each role of the predicate $i
					string cleanrole = it->first;
					cleanrole = boost::regex_replace(cleanrole, Common::reSR_sntC, "");	// C - continuation ARGUMENTS
					cleanrole = boost::regex_replace(cleanrole, Common::reSR_sntR, "");	// R - reference ARGUMENTS
					int j = 0;
					while (j < it->second.size()) {
						vector<string> Rwords;
						int k = it->second[j];
						int k_end = (j+1 < it->second.size() ? it->second[j+1] : k);
						while (k <= k_end) {
							if (k < snt_s.size()) {			// if defined	OJU AQUI!
								string word = snt_s[k][0];
								// bags-of-words ---------------
								stringstream v_bow, a_bow;
								v_bow << verb << "##" << word;
								a_bow << cleanrole << "##" << i;
								++SNT.A["bow"][cleanrole][word];
								++SNT.A["Vbow"][cleanrole][v_bow.str()];
								++SNT.A["Abow"][a_bow.str()][word];
								Rwords.push_back(word);
							}
							// bags-of-rols ---------------
							stringstream v_bor, a_bor;
							v_bor << verb << "##" << cleanrole;
							a_bor << cleanrole << "##" << i;
							++SNT.B["bor"][cleanrole];
							++SNT.B["Vbor"][v_bor.str()];
							++SNT.B["Abor"][a_bor.str()];
							++k;
						}
	                  	// exact role matches -----------------------
	                  	string r_words = "";
						if (Rwords.size()) {
							r_words = Rwords[0];
							for(int sub = 1; sub < Rwords.size(); ++sub) r_words = r_words+" "+Rwords[sub]; 
						}
						stringstream v_exact, a_exact;
						v_exact << verb << "##" << r_words;
						a_exact << cleanrole << "##" << i;
						++SNT.A["exact"][cleanrole][r_words];
						++SNT.A["Vexact"][cleanrole][v_exact.str()];
						++SNT.A["Aexact"][a_exact.str()][r_words];
						j += 2;
					}
				}
				++i;
			}
		}
		SNT.nVerbs = 0;
		if (snt_v.size()) {
			SNT.nVerbs = snt_v.size();
			for (int i = 0; i < snt_v.size(); ++i)
				++SNT.B["Verbs"][snt_v[i][1]];
		}

		if (snt_s.size()) {		// only for lexical overlap (e.g., to backoff when parsing fails) 
			for (int i = 0; i < snt_s.size(); ++i) {
				if (snt_s[i].size()) {			// if defined¿?			OJU AQUI!
					string theworld = snt_s[i][0];
					++SNT.B["BOW"][theworld];
				}
			}
		}
	}
}

void SR::SNT_compute_overlap_scores(SNTextract_feat &Tout, SNTextract_feat &Tref, int LC, map<string, double> &SCORES) {
	// description _ computes distances between a candidate and a reference sentence (+features)
	if (!Tout.A.empty() and !Tout.B.empty() and !Tref.A.empty() and !Tref.B.empty()) {	// BOTH SEGMENTS AVAILABLE
	//if (Tout.A.size() and Tout.B.size() and Tref.A.size() and Tref.B.size()) {	// BOTH SEGMENTS AVAILABLE
			Overlap Ov;

		// BOTH SEGMENTS HAVE BEEN 'SUCCESSFULLY' SR-PARSED? (BOW for lexical overlap is always there)
		if (Tref.B.size() > 1 and Tout.B.size() > 1) SCORES["OK"] = 1;
		else SCORES["OK"] = 0;

		// SR::SREXT-Nv ---------------------------------------------------------------------------------
		int diff = abs( Tref.nVerbs - Tout.nVerbs );
		SCORES[SR::SREXT+"-Nv"] = 1 / (diff == 0 ? 1 : diff);

		// SR::SREXT-Ov --------------------------------------------------------------------------------
		pair<double, double> hits_total = Ov.compute_overlap(Tout.B["Verbs"], Tref.B["Verbs"], 0);
		SCORES[SR::SREXT+"-Ov"] = Common::safe_division(hits_total.first, hits_total.second);

		// SR::SREXT-Or --------------------------------------------------------------------------------
		hits_total = Ov.compute_overlap(Tout.B["bor"], Tref.B["bor"], 0);
		SCORES[SR::SREXT+"-Or"] = Common::safe_division(hits_total.first, hits_total.second);
	
		// SR::SREXT-Orv -------------------------------------------------------------------------------
		hits_total = Ov.compute_overlap(Tout.B["Vbor"], Tref.B["Vbor"], 0);
		SCORES[SR::SREXT+"-Orv"] = Common::safe_division(hits_total.first, hits_total.second);
		
		// SR::SREXT-Mr(*) ----------------------------------------------------------------------------------
		double HITS  = 0, TOTAL  = 0;
		double PHITS = 0, PTOTAL = 0;
		double RHITS = 0, RTOTAL = 0;

		set<string> F;
		for(map<string, map<string, int> >::const_iterator it = Tout.A["exact"].begin(); it != Tout.A["exact"].end(); ++it)
			F.insert(it->first);
		for(map<string, map<string, int> >::const_iterator it = Tref.A["exact"].begin(); it != Tref.A["exact"].end(); ++it)
			F.insert(it->first);

		for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
			hits_total = Ov.compute_overlap(Tout.A["exact"][*it], Tref.A["exact"][*it], LC);
			SCORES[SR::SREXT+"-Mr("+(*it)+")"] = Common::safe_division(hits_total.first, hits_total.second);
			HITS += hits_total.first;	TOTAL += hits_total.second;
			
			hits_total = Ov.compute_precision(Tout.A["exact"][*it], Tref.A["exact"][*it], LC);
			PHITS += hits_total.first;	PTOTAL += hits_total.second;
			
			hits_total = Ov.compute_recall(Tout.A["exact"][*it], Tref.A["exact"][*it], LC);
			RHITS += hits_total.first;	RTOTAL += hits_total.second;
		}
		SCORES[SR::SREXT+"-Mr(*)"] = Common::safe_division(HITS, TOTAL);
		double P = Common::safe_division(PHITS, PTOTAL);
		double R = Common::safe_division(RHITS, RTOTAL);
		SCORES[SR::SREXT+"-MPr(*)"] = P;
		SCORES[SR::SREXT+"-MRr(*)"] = R;
		SCORES[SR::SREXT+"-MFr(*)"] = Common::f_measure(P, R, 1);

		// SR::SREXT-Or(*) ----------------------------------------------------------------------------------
		HITS  = TOTAL  = 0;
		PHITS = PTOTAL = 0;
		RHITS = RTOTAL = 0;

		F.clear();
		for(map<string, map<string, int> >::const_iterator it = Tout.A["bow"].begin(); it != Tout.A["bow"].end(); ++it)
			F.insert(it->first);
		for(map<string, map<string, int> >::const_iterator it = Tref.A["bow"].begin(); it != Tref.A["bow"].end(); ++it)
			F.insert(it->first);

		for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
			hits_total = Ov.compute_overlap(Tout.A["bow"][*it], Tref.A["bow"][*it], LC);
			SCORES[SR::SREXT+"-Or("+(*it)+")"] = Common::safe_division(hits_total.first, hits_total.second);
			HITS += hits_total.first;	TOTAL += hits_total.second;

			hits_total = Ov.compute_precision(Tout.A["bow"][*it], Tref.A["bow"][*it], LC);
			PHITS += hits_total.first;	PTOTAL += hits_total.second;

			hits_total = Ov.compute_recall(Tout.A["bow"][*it], Tref.A["bow"][*it], LC);
			RHITS += hits_total.first;	RTOTAL += hits_total.second;
		}
		SCORES[SR::SREXT+"-Or(*)"] = Common::safe_division(HITS, TOTAL);
		P = Common::safe_division(PHITS, PTOTAL);
		R = Common::safe_division(RHITS, RTOTAL);
		SCORES[SR::SREXT+"-Pr(*)"] = P;
		SCORES[SR::SREXT+"-Rr(*)"] = R;
		SCORES[SR::SREXT+"-Fr(*)"] = Common::f_measure(P, R, 1);

		// SR::SREXT-Mrv(*) ----------------------------------------------------------------------------------
		HITS = TOTAL = 0;
		F.clear();
		for(map<string, map<string, int> >::const_iterator it = Tout.A["Vexact"].begin(); it != Tout.A["Vexact"].end(); ++it)
			F.insert(it->first);
		for(map<string, map<string, int> >::const_iterator it = Tref.A["Vexact"].begin(); it != Tref.A["Vexact"].end(); ++it)
			F.insert(it->first);

		for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
			hits_total = Ov.compute_overlap(Tout.A["Vexact"][*it], Tref.A["Vexact"][*it], LC);
			SCORES[SR::SREXT+"-Mrv("+(*it)+")"] = Common::safe_division(hits_total.first, hits_total.second);
			HITS += hits_total.first;	TOTAL += hits_total.second;
		}
		SCORES[SR::SREXT+"-Mrv(*)"] = Common::safe_division(HITS, TOTAL);

		// SR::SREXT-Orv(*) ----------------------------------------------------------------------------------
		HITS = TOTAL = 0;
		F.clear();
		for(map<string, map<string, int> >::const_iterator it = Tout.A["Vbow"].begin(); it != Tout.A["Vbow"].end(); ++it)
			F.insert(it->first);
		for(map<string, map<string, int> >::const_iterator it = Tref.A["Vbow"].begin(); it != Tref.A["Vbow"].end(); ++it)
			F.insert(it->first);

		for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
			hits_total = Ov.compute_overlap(Tout.A["Vbow"][*it], Tref.A["Vbow"][*it], LC);
			SCORES[SR::SREXT+"-Orv("+(*it)+")"] = Common::safe_division(hits_total.first, hits_total.second);
			HITS += hits_total.first;	TOTAL += hits_total.second;
		}
		SCORES[SR::SREXT+"-Orv(*)"] = Common::safe_division(HITS, TOTAL);

		// SR::SREXT-Ol ------------------------------------------------------------------------------------
		//  lexical overlap alone
		hits_total = Ov.compute_overlap(Tout.B["BOW"], Tref.B["BOW"], LC);
		SCORES[SR::SREXT+"-Ol"] = Common::safe_division(hits_total.first, hits_total.second);
	}
}



void SR::FILE_compute_overlap_metrics(const vector<sParsed> &POUT_S, const vector< vector<rParsed> > &POUT_R, const vector< vector<vector<string> > > &POUT_V, 
									  const vector<sParsed> &PREF_S, const vector< vector<rParsed> > &PREF_R, const vector< vector<vector<string> > > &PREF_V, 
									  vector< map<string, double> > &SCORES) {
	// description _ computes CHUNK scores (single reference)
	//string LANG = Config::LANG;
	SCORES.resize(PREF_S.size());
	for (int topic = 0; topic < PREF_S.size(); ++topic) {
		SNTextract_feat OUTSNT, REFSNT;

		SNT_extract_features(POUT_S[topic], POUT_R[topic], POUT_V[topic], OUTSNT);

		/*fprintf(stderr, "---- OUTSNT.A (%d) ----\n", (int)OUTSNT.A.size());
		for(map<string, map<string, map<string, int> > >::const_iterator it_ = OUTSNT.A.begin(); it_ != OUTSNT.A.end(); ++it_) {
			fprintf(stderr, "\t%s -> {\n", it_->first.c_str());
			
			map<string, map<string, int> > aux_a = it_->second;
			for(map<string, map<string, int> >::const_iterator it_a = aux_a.begin(); it_a != aux_a.end(); ++it_a) {
				fprintf(stderr, "\t\t%s -> {\n", it_a->first.c_str());
				
				map<string, int> aux_aa = it_a->second;
				for(map<string, int>::const_iterator it_aa = aux_aa.begin(); it_aa != aux_aa.end(); ++it_aa) {
					fprintf(stderr, "\t\t\t[%s -> %d]\n", it_aa->first.c_str(), it_aa->second);
				}
			}
		} 
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "---- OUTSNT.B (%d) ----\n", (int)OUTSNT.B.size());	
		for(map<string, map<string, int> >::const_iterator it_b = OUTSNT.B.begin(); it_b != OUTSNT.B.end(); ++it_b) {
			fprintf(stderr, "\t%s -> {\n", it_b->first.c_str());
			
			map<string, int> aux_bb = it_b->second;
			for(map<string, int>::const_iterator it_bb = aux_bb.begin(); it_bb != aux_bb.end(); ++it_bb) {
				fprintf(stderr, "\t\t[%s -> %d]\n", it_bb->first.c_str(), it_bb->second);
			}
		}
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "-> nVerbs: (%d)\n", OUTSNT.nVerbs);
		fprintf(stderr, "-----------------\n");*/

		SNT_extract_features(PREF_S[topic], PREF_R[topic], PREF_V[topic], REFSNT);


		/*fprintf(stderr, "---- REFSNT.A (%d) ----\n", (int)REFSNT.A.size());
		for(map<string, map<string, map<string, int> > >::const_iterator it_ = REFSNT.A.begin(); it_ != REFSNT.A.end(); ++it_) {
			fprintf(stderr, "\t%s -> {\n", it_->first.c_str());
			
			map<string, map<string, int> > aux_a = it_->second;
			for(map<string, map<string, int> >::const_iterator it_a = aux_a.begin(); it_a != aux_a.end(); ++it_a) {
				fprintf(stderr, "\t\t%s -> {\n", it_a->first.c_str());
				
				map<string, int> aux_aa = it_a->second;
				for(map<string, int>::const_iterator it_aa = aux_aa.begin(); it_aa != aux_aa.end(); ++it_aa) {
					fprintf(stderr, "\t\t\t[%s -> %d]\n", it_aa->first.c_str(), it_aa->second);
				}
			}
		} 
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "---- REFSNT.B (%d) ----\n", (int)REFSNT.B.size());	
		for(map<string, map<string, int> >::const_iterator it_b = REFSNT.B.begin(); it_b != REFSNT.B.end(); ++it_b) {
			fprintf(stderr, "\t%s -> {\n", it_b->first.c_str());
			
			map<string, int> aux_bb = it_b->second;
			for(map<string, int>::const_iterator it_bb = aux_bb.begin(); it_bb != aux_bb.end(); ++it_bb) {
				fprintf(stderr, "\t\t[%s -> %d]\n", it_bb->first.c_str(), it_bb->second);
			}
		}
		fprintf(stderr, "-----------------\n");
		fprintf(stderr, "-> nVerbs: (%d)\n", REFSNT.nVerbs);
		fprintf(stderr, "-----------------\n");*/


		SNT_compute_overlap_scores(OUTSNT, REFSNT, (Config::CASE != Common::CASE_CI), SCORES[topic]);
		/*fprintf(stderr, "---- TOPIC (%d) ----\n", (int)SCORES[topic].size());
		for(map<string, double>::const_iterator it = SCORES[topic].begin(); it != SCORES[topic].end(); ++it) {
			fprintf(stderr, "\t[%s -> %f]\n", it->first.c_str(), it->second);
		}*/

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

		SRXLike srl;
		if (DO_METRICS) {
			// parse
			vector<sParsed> FDout_S(TESTBED::wc[TGT]);
			vector< vector<rParsed> > FDout_R(TESTBED::wc[TGT]);
			vector< vector<vector<string> > > FDout_V(TESTBED::wc[TGT]);

			if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) {
				srl.parse_SR(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, FDout_S, FDout_R, FDout_V);
			}
			else if (Config::LANG == Common::L_ENG) {
				// RESIZE all vectors output to TESTBED::wc[TGT]
				parse_SR(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, FDout_S, FDout_R, FDout_V);

				/*fprintf(stderr, "------- FDout_R ------\n");
				for (int i = 0; i < FDout_R.size(); ++i) {
					fprintf(stderr, "\tFDout_R[%d]\n", i);
					for (int j = 0; j < FDout_R[i].size(); ++j) {
						fprintf(stderr, "\t\tFDout_R[%d][%d]\n", i, j);
						rParsed aux = FDout_R[i][j];

						for(rParsed::const_iterator it = aux.begin(); it != aux.end(); ++it) {
							fprintf(stderr, "\t\t\t[%s", it->first.c_str());
							for(int l = 0; l < it->second.size(); ++l) fprintf(stderr, ", %d", it->second[l]);
							fprintf(stderr, "]\n");
						}
					}
				}
				fprintf(stderr, "----------------------\n");*/

				//fprintf(stderr, "USE SR parse_SR\n");
			}
			else { fprintf(stderr, "[SR] tool for <%s> unavailable!!!\n", Config::LANG.c_str()); exit(1); }

				/*fprintf(stderr, "----- parse_v ------\n");
				for (int x = 0; x < FDout_V.size(); ++x) {
					
					fprintf(stderr, "\tFDout_v[%d]\n", x);
					for (int y = 0; y < FDout_V[x].size(); ++y) {
						
						fprintf(stderr, "\t\tFDout_v[%d][%d]\n", x, y);
						for (int z = 0; z < FDout_V[x][y].size(); ++z) {
							fprintf(stderr, "\t\t\t FDòut_v[%d][%d][%d] = %s\n", x, y, z, FDout_V[x][y][z].c_str());
						}
					}
				}
				fprintf(stderr, "--------------------\n");*/

			Overlap Ov;
			vector< map<string, double> > maxscores(TESTBED::wc[TGT]);
			/*for (int i = 0; i < maxscores.size(); ++i) {
				for (set<string>::const_iterator it_rF = rF.begin(); it_rF != rF.end(); ++it_rF)
					maxscores[i][*it_rF] = Common::NOT_DEFINED;
			}*/

			map< string, vector<double> > maxOK;


			for (map<string, string>::const_iterator it_r = TESTBED::Hrefs.begin(); it_r != TESTBED::Hrefs.end(); ++it_r) {
				vector<sParsed> FDref_S(TESTBED::wc[TGT]);
				vector< vector<rParsed> > FDref_R(TESTBED::wc[TGT]);
				vector< vector<vector<string> > > FDref_V(TESTBED::wc[TGT]);
				
				if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) {
					srl.parse_SR(it_r->second, Config::LANG, Config::CASE, FDref_S, FDref_R, FDref_V);
				}
				else if (Config::LANG == Common::L_ENG) {
					parse_SR(it_r->second, Config::LANG, Config::CASE, FDref_S, FDref_R, FDref_V);
				}
				else { fprintf(stderr, "[SR] tool for <%s> unavailable!!!\n", Config::LANG.c_str()); exit(1); }

				vector< map<string, double> > scores;
				FILE_compute_overlap_metrics(FDout_S, FDout_R, FDout_V, FDref_S, FDref_R, FDref_V, scores);

				for (set<string>::const_iterator it_rF = rF.begin(); it_rF != rF.end(); ++it_rF) {
					if (Config::Hmetrics.count(*it_rF) or Config::Hmetrics.count((*it_rF)+"_b") or Config::Hmetrics.count((*it_rF)+"_i")) {
						double SYS, MAXSYS;
						vector<double> SEGS, MAXSEGS;
						maxOK[*it_rF].resize(TESTBED::wc[TGT]);
						Ov.get_segment_scores_M(maxscores, *it_rF, 0, maxOK, MAXSYS, MAXSEGS);

						Ov.get_segment_scores(scores, *it_rF, 0, SYS, SEGS);

					/*fprintf(stderr, "\tSYS: %f\n", SYS);
					fprintf(stderr, "\tSEGS: [ |");
					for(int i = 0; i < SEGS.size(); ++i) fprintf(stderr, "%f|", SEGS[i]);
					fprintf(stderr, "| ]\n");*/

						for (int i = 0; i < SEGS.size(); ++i) {		// update max scores
							if (SEGS[i] != Common::NOT_DEFINED) {
								if (i < MAXSEGS.size() and MAXSEGS[i] != Common::NOT_DEFINED) {
									if (SEGS[i] > MAXSEGS[i]) {
										if (scores[i].count(*it_rF)) {
											maxscores[i][*it_rF] = scores[i][*it_rF];
											maxOK[*it_rF][i] = scores[i]["OK"];
										}
									}

								}
								else {
									maxscores[i][*it_rF] = scores[i][*it_rF];
									maxOK[*it_rF][i] = scores[i]["OK"];
								}
							}
							else {
								maxscores[i][*it_rF] = scores[i][*it_rF];
								maxOK[*it_rF][i] = scores[i]["OK"];
							}
						}
					}
				}
			}

			for (set<string>::const_iterator it_rF = rF.begin(); it_rF != rF.end(); ++it_rF) {
				if (Config::Hmetrics.count(*it_rF)) {
					string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+*it_rF+"."+Common::XMLEXT;
					if (!exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML+"."+Common::GZEXT)) or Config::remake) {
					 	boost::match_results<string::const_iterator> results;
						if (boost::regex_match(*it_rF, results, Common::reSR_b) or boost::regex_match(*it_rF, results, Common::reSR_i)) {
							int verbo = Config::verbose;			Config::verbose = 0;
							set<string> M = Config::Hmetrics;		Config::Hmetrics = Overlap::rOl;

							Ov.doMetric(TGT, REF, "", hOQ);

							Config::verbose = verbo;
							Config::Hmetrics = M;

							set<string> sOl = Overlap::rOl;
	/* SIZE MAXSCORES? */	hOQ.add_metrics(TGT, REF, /*Overlap::rOl*/ sOl, Common::G_SEG, maxscores);
						}
						double SYS;
						vector<double> SEG, d_scores, s_scores;
						if (boost::regex_match(*it_rF, results, Common::reSR_b)) {
							string backm = *it_rF;	backm = boost::regex_replace(backm, Common::reSR_b_end, "");
							Ov.merge_metrics_M(maxscores, backm, Overlap::OlEXT, 0, maxOK, SYS, SEG);
						}
						else if (boost::regex_match(*it_rF, results, Common::reSR_i)) {
							string backm = *it_rF;	backm = boost::regex_replace(backm, Common::reSR_i_end, "");
							Ov.merge_metrics_M(maxscores, backm, Overlap::OlEXT, 1, maxOK, SYS, SEG);
						}
						else {
							Ov.get_segment_scores_M(maxscores, *it_rF, 2, maxOK, SYS, SEG);
						}
						TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
						if (Config::O_STORAGE == 1) {
							sc_asiya.write_report(TGT, REF, *it_rF, SYS, d_scores, s_scores);
							fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", it_rF->c_str());
						}
			         	hOQ.save_hash_scores(*it_rF, TGT, REF, SYS, d_scores, s_scores);
					}

				}
			}

			if (Config::serialize)
        		hOQ.save_struct_scores(TB_FORMAT::make_serial(SR::SREXT, TGT, REF));
		}
	}
}


		/*fprintf(stderr, "----------- maxscores -----------\n");
		for (int m = 0; m < maxscores.size(); ++m) {
			map<string, double> aux_m = maxscores[m];
			fprintf(stderr, "\tmaxscores[%d]\n", m);
			for (map<string, double>::const_iterator it = aux_m.begin(); it != aux_m.end(); ++it) {
				fprintf(stderr, "\t\t[%s -> %f]\n", it->first.c_str(), it->second);
			}
		}
		fprintf(stderr, "---------------------------------\n");*/


/*
for(map<string, set<string> >::const_iterator it = SR::rLANG.begin(); it != SR::rLANG.end(); ++it) {
    cout << "\t" << it->first << " -> " << endl;
    set<string> aux = it->second;
    for(set<string>::const_iterator is = aux.begin(); is != aux.end(); ++is) {
            cout << "\t\t[" << *is << "]" << endl;
    }
}
*/
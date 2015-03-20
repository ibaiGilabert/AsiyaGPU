#include "../include/SRXLike.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

//#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

const string SRXLike::SREXT = "SR";
const string SRXLike::XLike = "xlike/runxlikeparser.sh";

set<string> SRXLike::create_rSRspacat() {
	set<string> rSRspacat;
	rSRspacat.insert(SRXLike::SREXT+"-Nv"); rSRspacat.insert(SRXLike::SREXT+"-Ov"); rSRspacat.insert(SRXLike::SREXT+"-Or"); rSRspacat.insert(SRXLike::SREXT+"-Orv");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Orv(*)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Mr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Or(*)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Ol"); rSRspacat.insert(SRXLike::SREXT+"-Or(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Or(*)_i");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Mr(*)_i"); rSRspacat.insert(SRXLike::SREXT+"-Orv(*)_b");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(*)_i"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)_i");
	rSRspacat.insert(SRXLike::SREXT+"-Or_b"); rSRspacat.insert(SRXLike::SREXT+"-Or_i"); rSRspacat.insert(SRXLike::SREXT+"-Orv_b");
	rSRspacat.insert(SRXLike::SREXT+"-Orv_i");
	rSRspacat.insert(SRXLike::SREXT+"-Pr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Rr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Fr(*)");
	rSRspacat.insert(SRXLike::SREXT+"-MPr(*)"); rSRspacat.insert(SRXLike::SREXT+"-MRr(*)"); rSRspacat.insert(SRXLike::SREXT+"-MFr(*)");
	rSRspacat.insert(SRXLike::SREXT+"-Ora"); rSRspacat.insert(SRXLike::SREXT+"-Mra(*)"); rSRspacat.insert(SRXLike::SREXT+"-Ora(*)");
	return rSRspacat;
}
set<string> SRXLike::rSRspacat = create_rSRspacat();




void SRXLike::FILE_create_input(string input, string auxconllfile) {
	// description _ creates the input file in conll format
	ofstream CONLLFILE(auxconllfile.c_str());
	if (!CONLLFILE.is_open()) { fprintf(stderr, "[SRXLike] Could not open file: %s\n", auxconllfile.c_str()); exit(1); }

	ifstream FILE(input.c_str());
	if (FILE) {
		int iter = 0;
		string line;
		while( getline(FILE, line) ) {
			vector<string> toks;
			boost::split(toks, line, boost::is_any_of("\t "));
			
			int wcount = 1;
			for (int i = 0; i < toks.size(); ++i) {
				CONLLFILE << wcount << " " << toks[i] << endl;
				++wcount;
			}
			CONLLFILE << endl;

			if (Config::verbose) {
				if (iter%10 == 0)	fprintf(stderr, ".");
				if (iter%100 == 0)	fprintf(stderr, "%d", iter);
			}
			++iter;
		}
		CONLLFILE.close();
		FILE.close();
	}
	else { fprintf(stderr, "[SRXLike] Could not open file: %s\n", input.c_str()); exit(1); }

	//return iter;
}

string SRXLike::getRoleName(string role_id, string L) {
	// description _ responsible to convert the tagger notation into Asiya notation
	if (L == Common::L_SPA) {
		if (role_id == "arg0") return "A0";
		else if (role_id == "arg1") return "A1";
		else if (role_id == "arg2") return "A2";
		else if (role_id == "arg3") return "A3";
		else if (role_id == "arg4") return "A4";
		else if (role_id == "arg5") return "A5";
		else if (role_id == "arg6") return "A6";
		else if (role_id == "arg7") return "A7";
		else if (role_id == "arg8") return "A8";
		else if (role_id == "arg9") return "A9";
		else if (role_id == "argM-loc") return "AM-LOC";
		else if (role_id == "argM-tmp") return "AM-TMP";
		else if (role_id == "argM-mnr") return "AM-MNR";
		else if (role_id == "argM-adv") return "AM-ADV";
	}

	boost::to_upper(role_id);
	return role_id;
}

pair<int, int> SRXLike::find_role_boundaries(map<int, vector<int> > &DPtree, int head) {
	int start = head, end = head;

	if (DPtree.count(head)) {
		for(int node = 0; node < DPtree[head].size(); ++node) {
			pair<int, int> tmp_start_end = find_role_boundaries(DPtree, DPtree[head][node]);
			start = min(start, 	tmp_start_end.first);
			end   = max(end, 	tmp_start_end.second);
		}
	}
	return make_pair(start, end);
}

void SRXLike::extract_DP_subtress(map<int, vector<int> > &DPtree, vector<rParsed> &rolestruct) {
	//description:	process the DPtrees to extract the beginning and end of the role chunks
	//			  	the file structure contains only the head of the subtree, and it should contain the first and last word of the role chunks
	//			 	the role range is defined as the complete subtree starting from the head
	for(int v_idx = 0; v_idx < rolestruct.size(); ++v_idx) {
		//if (rolestruct[v_idx])
		
		// for each role
		for(rParsed::iterator it = rolestruct[v_idx].begin(); it != rolestruct[v_idx].end(); ++it) {
			// for each word
			vector<int> updatedList;
			for (int w_idx = 0; w_idx < it->second.size(); ++w_idx) {
				pair<int, int> w_start_end = find_role_boundaries(DPtree, it->second[w_idx]+1);
				updatedList.push_back(w_start_end.first);
				updatedList.push_back(w_start_end.second);
			}
			rolestruct[v_idx][it->first] = updatedList;
		}
	}
}


void SRXLike::parse_SR(string input, string L, string C, vector<sParsed> &FILE_S, vector< vector<rParsed> > &FILE_R, vector< vector<vector<string> > > &FILE_V) {
	// description _ responsible for SR
	//               (WORD + PoS)  ->  (WORD + SR)
	string srlfile = input+"."+SRXLike::SREXT;
	srand(time(NULL));

	if (L == Common::L_SPA or L == Common::L_CAT) {
		if (!exists(boost::filesystem::path(srlfile)) and !exists(boost::filesystem::path(srlfile+"."+Common::GZEXT))) {
			double nr = rand() % (Common::NRAND + 1);
		    string basename = boost::filesystem::path(input).filename().string();

			stringstream auxconllfile;
			auxconllfile << Common::DATA_PATH << "/" << Common::TMP << "/" << basename << "." << nr;

			FILE_create_input(input, auxconllfile.str());
	    	
	    	string cmd = "cd "+Common::DATA_PATH+"; "+Config::tools+"/"+SRXLike::XLike+" "+auxconllfile.str()+" > "+srlfile;
			Common::execute_or_die(cmd, "[ERROR] problems running XLike Parser...");
		}
	}
	else { fprintf(stderr, "[SR] tool for <%s> unavailable!!!\n", L.c_str()); exit(1); }

	if (!exists(boost::filesystem::path(srlfile)) and exists(boost::filesystem::path(srlfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+srlfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	ifstream AUX(srlfile.c_str());
	if (AUX) {
		int num_sent = 0, num_word = 0, num_line = 0;

		vector<map<int, vector<int> > > DPforest;

		string line;
		while( getline(AUX, line) ) {
			++num_line;
			if (line.empty()) {
				extract_DP_subtress(DPforest[num_sent], FILE_R[num_sent]);
				++num_sent;
				num_word = 0;
			}
			else {
				vector<string> entry;
				boost::split(entry, line, boost::is_any_of("[ ]")); 	//0:7 1:deja 2:dejar 3:VMIP3S0 4:cpos=V|postype=main|mood=indicative|tense=present|person=3|num=s 5:_ 6:3 7:cd 8:dejar.01 9:arg1-pat 10:arg1-pat
	    		// save the DP tree
	    		DPforest[num_sent][ boost::lexical_cast<int>(entry[6]) ].push_back( boost::lexical_cast<int>(entry[0]) );
	    		// save word
	    		vector<string> l(3);	l[0] = entry[1];	l[1] = entry[3];	l[2] = entry[2];
	    		FILE_S[num_sent].push_back(l);
	    		// save verb
	    		if (entry[8] != "_") {
	    			vector<string> ll(2);	ll[0] = num_word;	ll[1] = entry[2];
	    			FILE_V[num_sent].push_back(ll);
	    		}
	    		// start processing items
	    		int role_idx = 9;	// position of roles
	    		int verb_idx = 0;	// index of verbs
	    		while (role_idx < entry.size()) {
	    			if (entry[role_idx] != "_") {
	    				// save role
	    				string tag = getRoleName(entry[role_idx], L);
	    				FILE_R[num_sent][verb_idx][tag].push_back(num_word);
	    			}
	    			++role_idx;		// next role
	    			++verb_idx;		// belongs to next verb
	    		}
	    		++num_word;
			}
		}
		AUX.close();
	}
	else { fprintf(stderr, "[SRXLike] Could not open file: %s\n", srlfile.c_str()); exit(1); }

	if (exists(boost::filesystem::path(srlfile))) {
		string sys_aux = Common::GZIP+" "+srlfile;
		system(sys_aux.c_str());
	}
}
#include "../include/Overlap.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libgen.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

const string Overlap::OlEXT = "Ol";
const string Overlap::PlEXT = "Pl";
const string Overlap::RlEXT = "Rl";
const string Overlap::FlEXT = "Fl";

set<string> Overlap::create_rOl() {
	set<string> rOverlap;
	rOverlap.insert(Overlap::OlEXT);
	rOverlap.insert(Overlap::PlEXT);
	rOverlap.insert(Overlap::RlEXT);
	rOverlap.insert(Overlap::FlEXT);
	return rOverlap;
}
const set<string> Overlap::rOl = create_rOl();

void Overlap::extract_temrs(const map<string, int> &h_cand, const map<string, int> &h_ref, int LC, map<string, double> &t_cand, map<string, double> &t_ref, map<string, double> &t_tot) {
	// description _ extract the hash-counts of features
	for(map<string, int>::const_iterator it = h_cand.begin(); it != h_cand.end(); ++it) {
		string t = it->first;
		if (LC) boost::to_lower(t);
		t_cand[t] += it->second;
		t_tot[t] += it->second;
	}
	for(map<string, int>::const_iterator it = h_ref.begin(); it != h_ref.end(); ++it) {
		string t = it->first;
		if (LC) boost::to_lower(t);
		t_ref[t] += it->second;
		t_tot[t] += it->second;
	}
}

pair<double, double> Overlap::compute_overlap(const map<string, int> &hO, const map<string, int> &hR, int LC) {
	// description _ computes overlap between elems in candidate and reference hash of features
	double hits, total;
	hits = total = 0;

	map<string, double> t_cand, t_ref, t_tot;
	extract_temrs(hO, hR, LC, t_cand, t_ref, t_tot);

	if (!hO.empty() and !hR.empty()) {
		for(map<string, double>::const_iterator it = t_tot.begin(); it != t_tot.end(); ++it) {
			if (t_cand[it->first] and t_ref[it->first]) {
				if (t_cand[it->first] > t_ref[it->first]) {
					hits += t_ref[it->first];
					total += t_cand[it->first];
				}
				else {
					hits += t_cand[it->first];
					total += t_ref[it->first];
				}
			}
			else {
				if (t_cand[it->first]) total += t_cand[it->first];
				else if (t_ref[it->first]) total += t_ref[it->first];
			}
		}
	}
	else {
		for (map<string, double>::const_iterator it = t_tot.begin(); it != t_tot.end(); ++it) total += it->second;
	}

	return make_pair(hits, total);
}

pair<double, double> Overlap::compute_precision(const map<string, int> &hO, const map<string, int> &hR, int LC) {
	// description _ computes precision (proportion of elems in the candidate also in the reference hash of features)
	double hits, total;
	hits = total = 0;

	map<string, double> t_cand, t_ref, t_tot;
	extract_temrs(hO, hR, LC, t_cand, t_ref, t_tot);
	if (!hO.empty() and !hR.empty()) {
		for(map<string, double>::const_iterator it = t_tot.begin(); it != t_tot.end(); ++it) {
			if (t_cand[it->first] and t_ref[it->first]) {
				if (t_cand[it->first] > t_ref[it->first]) {
					hits += t_ref[it->first];
					total += t_cand[it->first];
				}
				else {
					hits += t_cand[it->first];
					total += t_cand[it->first];
				}
			}
			else {
				if (t_cand[it->first]) total += t_cand[it->first];
			}
		}
	}

	return make_pair(hits, total);
}

pair<double, double> Overlap::compute_recall(const map<string, int> &hO, const map<string, int> &hR, int LC) {
	// description _ computes recall (proportion of elems in the reference also in the candidate hash of features)
	double hits, total;
	hits = total = 0;

	map<string, double> t_cand, t_ref, t_tot;
	extract_temrs(hO, hR, LC, t_cand, t_ref, t_tot);
	if (!hO.empty() and !hR.empty()) {
		for(map<string, double>::const_iterator it = t_tot.begin(); it != t_tot.end(); ++it) {
			if (t_cand[it->first] and t_ref[it->first]) {
				if (t_cand[it->first] > t_ref[it->first]) {
					hits += t_ref[it->first];
					total += t_ref[it->first];
				}
				else {
					hits += t_cand[it->first];
					total += t_ref[it->first];
				}
			}
			else {
				if (t_ref[it->first]) total += t_ref[it->first];
			}
		}
	}

	return make_pair(hits, total);
}


void Overlap::computeOl(string out, string ref, double &SYS, vector<double> &SEG) {
	// description _ computes lexical overlap (single reference)
    ifstream ref_file(ref.c_str());
    ifstream out_file(out.c_str());
	if (!ref_file) { fprintf(stderr, "couldn't open input file: %s\n", ref.c_str()); exit(1); }
	if (out_file) {
		bool STOP = false;
		double HITS, TOTAL;
		HITS = TOTAL = 0;
		string o;
		while(getline(out_file, o) and !STOP) {
			double SEGscore;
			string r;
			if (getline(ref_file, r)) {
				vector<string> lO, lR;
				map<string, int> hO, hR;

				istringstream iss_o(o);
				for (string token; getline(iss_o, token, ' '); ) {
					lO.push_back(token);
					hO[token]++;
				}
				//for (int i = 0; i < lO.size(); ++i) hO[lO[i]]++;

				istringstream iss_r(r);
				for (string token; getline(iss_r, token, ' '); ) {
					lR.push_back(token);
					hR[token]++;
				}

				pair<double, double> hits_total = compute_overlap(hO, hR, 1);
				SEGscore = Common::safe_division(hits_total.first, hits_total.second);
				HITS += hits_total.first;
				TOTAL += hits_total.second;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs <%s>\n", out.c_str(), ref.c_str()); STOP = true; }
			SEG.push_back(SEGscore);
		}
		out_file.close();
		ref_file.close();

		SYS = Common::safe_division(HITS, TOTAL);
	} else { fprintf(stderr, "\n[ERROR] couldn't open input file: %s\n", out.c_str()); exit(1); }
}

void Overlap::computePl(string out, string ref, double &SYS, vector<double> &SEG) {
	// description _ computes lexical precision (single reference)
    ifstream ref_file(ref.c_str());
    ifstream out_file(out.c_str());
	if (!ref_file) { fprintf(stderr, "couldn't open input file: %s\n", ref.c_str()); exit(1); }
	if (out_file) {
		bool STOP = false;
		double HITS, TOTAL;
		HITS = TOTAL = 0;
		string o;
		while(getline(out_file, o) and !STOP) {
			double SEGscore;
			string r;
			if (getline(ref_file, r)) {
				vector<string> lO, lR;
				map<string, int> hO, hR;
				istringstream iss_o(o);
				for (string token; getline(iss_o, token, ' '); ) {
					lO.push_back(token);
					hO[token]++;
				}
				istringstream iss_r(r);
				for (string token; getline(iss_r, token, ' '); ) {
					lR.push_back(token);
					hR[token]++;
				}
				pair<double, double> hits_total = compute_precision(hO, hR, 1);
				SEGscore = Common::safe_division(hits_total.first, hits_total.second);
				HITS += hits_total.first;
				TOTAL += hits_total.second;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs <%s>\n", out.c_str(), ref.c_str()); STOP = true; }
			SEG.push_back(SEGscore);
		}
		out_file.close();
		ref_file.close();

		SYS = Common::safe_division(HITS, TOTAL);
	} else { fprintf(stderr, "\n[ERROR] couldn't open input file: %s\n", out.c_str()); exit(1); }
}

void Overlap::computeRl(string out, string ref, double &SYS, vector<double> &SEG) {
	// description _ computes lexical recall (single reference)
    ifstream ref_file(ref.c_str());
    ifstream out_file(out.c_str());
	if (!ref_file) { fprintf(stderr, "couldn't open input file: %s\n", ref.c_str()); exit(1); }
	if (out_file) {
		bool STOP = false;
		double HITS, TOTAL;
		HITS = TOTAL = 0;
		string o;
		while(getline(out_file, o) and !STOP) {
			double SEGscore;
			string r;
			if (getline(ref_file, r)) {
				vector<string> lO, lR;
				map<string, int> hO, hR;
				istringstream iss_o(o);
				for (string token; getline(iss_o, token, ' '); ) {
					lO.push_back(token);
					hO[token]++;
				}
				istringstream iss_r(r);
				for (string token; getline(iss_r, token, ' '); ) {
					lR.push_back(token);
					hR[token]++;
				}
				pair<double, double> hits_total = compute_recall(hO, hR, 1);
				SEGscore = Common::safe_division(hits_total.first, hits_total.second);
				HITS += hits_total.first;
				TOTAL += hits_total.second;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs <%s>\n", out.c_str(), ref.c_str()); STOP = true; }
			SEG.push_back(SEGscore);
		}
		out_file.close();
		ref_file.close();

		SYS = Common::safe_division(HITS, TOTAL);
	} else { fprintf(stderr, "\n[ERROR] couldn't open input file: %s\n", out.c_str()); exit(1); }
}

void Overlap::computeFl(string out, string ref, double &SYS, vector<double> &SEG) {
	// description _ computes lexical f-measure 2 * P * R / (P + R) (single reference)
    ifstream ref_file(ref.c_str());
    ifstream out_file(out.c_str());
	if (!ref_file) { fprintf(stderr, "couldn't open input file: %s\n", ref.c_str()); exit(1); }
	if (out_file) {
		bool STOP = false;
		double PHITS, PTOTAL, RHITS, RTOTAL;
		PHITS = PTOTAL = 0;
		RHITS = RTOTAL = 0;
		string o;
		while(getline(out_file, o) and !STOP) {
			double SEGscore;
			string r;
			if (getline(ref_file, r)) {
				vector<string> lO, lR;
				map<string, int> hO, hR;
				istringstream iss_o(o);
				for (string token; getline(iss_o, token, ' '); ) {
					lO.push_back(token);
					hO[token]++;
				}
				istringstream iss_r(r);
				for (string token; getline(iss_r, token, ' '); ) {
					lR.push_back(token);
					hR[token]++;
				}
				pair<double, double> hits_total_p = compute_precision(hO, hR, 1);
				pair<double, double> hits_total_r = compute_recall(hO, hR, 1);
				double P = Common::safe_division(hits_total_p.first, hits_total_p.second);
				double R = Common::safe_division(hits_total_r.first, hits_total_r.second);
				SEGscore = Common::f_measure(P, R, 1);
				PHITS += hits_total_p.first;	PTOTAL += hits_total_p.second;
				RHITS += hits_total_r.first;	RTOTAL += hits_total_r.second;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs <%s>\n", out.c_str(), ref.c_str()); STOP = true; }
			SEG.push_back(SEGscore);
		}
		out_file.close();
		ref_file.close();

		double P = Common::safe_division(PHITS, PTOTAL);
		double R = Common::safe_division(RHITS, RTOTAL);
		SYS = Common::f_measure(P, R, 1);
	} else { fprintf(stderr, "\n[ERROR] couldn't open input file: %s\n", out.c_str()); exit(1); }
}


void Overlap::computeMultiOl(string out, double &MAXSYS, vector<double> &MAXSEG) {
 	// description _ computes lexical overlap (multiple reference)
 	map<int, double> max_seg;
	for(map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		double SYS;
		vector<double> SEG;
		computeOl(out, it->second, SYS, SEG);
		for (int i = 0; i < SEG.size(); ++i) {
			if (max_seg.find(i) != max_seg.end()) max_seg[i] = SEG[i];
			else if (SEG[i] > max_seg[i]) max_seg[i] = SEG[i];
		}
	}
	int i = 0;
	MAXSEG.resize(max_seg.size());
	for(map<int, double>::const_iterator it = max_seg.begin(); it != max_seg.end(); ++it, ++i) {
		MAXSEG[i] = it->second;
		MAXSYS += it->second;
	}
	MAXSYS /= MAXSEG.size();
}

void Overlap::computeMultiPl(string out, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes lexical precision (multiple reference)
 	map<int, double> max_seg;
	for(map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		double SYS;
		vector<double> SEG;
		computePl(out, it->second, SYS, SEG);
		for (int i = 0; i < SEG.size(); ++i) {
			if (max_seg.find(i) != max_seg.end()) max_seg[i] = SEG[i];
			else if (SEG[i] > max_seg[i]) max_seg[i] = SEG[i];
		}
	}
	int i = 0;
	MAXSEG.resize(max_seg.size());
	for(map<int, double>::const_iterator it = max_seg.begin(); it != max_seg.end(); ++it, ++i) {
		MAXSEG[i] = it->second;
		MAXSYS += it->second;
	}
	MAXSYS /= MAXSEG.size();
}

void Overlap::computeMultiRl(string out, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes lexical recall (multiple reference)
 	map<int, double> max_seg;
	for(map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		double SYS;
		vector<double> SEG;
		computeRl(out, it->second, SYS, SEG);
		for (int i = 0; i < SEG.size(); ++i) {
			if (max_seg.find(i) != max_seg.end()) max_seg[i] = SEG[i];
			else if (SEG[i] > max_seg[i]) max_seg[i] = SEG[i];
		}
	}
	int i = 0;
	MAXSEG.resize(max_seg.size());
	for(map<int, double>::const_iterator it = max_seg.begin(); it != max_seg.end(); ++it, ++i) {
		MAXSEG[i] = it->second;
		MAXSYS += it->second;
	}
	MAXSYS /= MAXSEG.size();
}

void Overlap::computeMultiFl(string out, double &MAXSYS, vector<double> &MAXSEG) {
	// description _ computes lexical f-measure 2 * P * R / (P + R) (multiple reference)
 	map<int, double> max_seg;
	for(map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		double SYS;
		vector<double> SEG;
		computeFl(out, it->second, SYS, SEG);
		for (int i = 0; i < SEG.size(); ++i) {
			if (max_seg.find(i) != max_seg.end()) max_seg[i] = SEG[i];
			else if (SEG[i] > max_seg[i]) max_seg[i] = SEG[i];
		}
	}
	int i = 0;
	MAXSEG.resize(max_seg.size());
	for(map<int, double>::const_iterator it = max_seg.begin(); it != max_seg.end(); ++it, ++i) {
		MAXSEG[i] = it->second;
		MAXSYS += it->second;
	}
	MAXSYS /= MAXSEG.size();
}

void Overlap::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes lexical overlap (multiple references)
	int GO , i;
	GO = i = 0;
	vector<string> mOl(Overlap::rOl.size());
	for (set<string>::const_iterator it = Overlap::rOl.begin(); it != Overlap::rOl.end(); ++it, ++i) mOl[i] = *it;
	for (i = 0; i < mOl.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mOl[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::Hmetrics.find(Overlap::OlEXT) != Config::Hmetrics.end()) {
			if (Config::verbose == 1) fprintf(stderr, "%s\n", Overlap::OlEXT.c_str());
			//stringstream ssReport;
			//ssReport << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << Overlap::OlEXT << "/" << Common::XMLEXT;
			string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+Overlap::OlEXT+"/"+Common::XMLEXT;
			string reportXML_gz = reportXML+"."+Common::GZEXT;
	    	if ((!exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML_gz))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG;
				computeMultiOl(TESTBED::Hsystems[TGT], SYS, SEG);
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
		    	SC_ASIYA sc_asiya;
				if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, Overlap::OlEXT, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", Overlap::OlEXT.c_str());
				}
				hOQ.save_hash_scores(Overlap::OlEXT, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(Overlap::OlEXT, TGT, REF));
			}
		}
		if (Config::Hmetrics.find(Overlap::PlEXT) != Config::Hmetrics.end()) {
			if (Config::verbose == 1) fprintf(stderr, "%s\n", Overlap::PlEXT.c_str());

			string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+Overlap::PlEXT+"/"+Common::XMLEXT;
			string reportXML_gz = reportXML+"."+Common::GZEXT;
	    	if ((!exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML_gz))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG;
	    		computeMultiPl(TESTBED::Hsystems[TGT], SYS, SEG);
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
		    	SC_ASIYA sc_asiya;
				if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, Overlap::PlEXT, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", Overlap::PlEXT.c_str());
				}
				hOQ.save_hash_scores(Overlap::PlEXT, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(Overlap::PlEXT, TGT, REF));

			}
		}
		if (Config::Hmetrics.find(Overlap::RlEXT) != Config::Hmetrics.end()) {
			if (Config::verbose == 1) fprintf(stderr, "%s\n", Overlap::RlEXT.c_str());

			string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+Overlap::RlEXT+"/"+Common::XMLEXT;
			string reportXML_gz = reportXML+"."+Common::GZEXT;
	    	if ((!exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML_gz))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG;
	    		computeMultiRl(TESTBED::Hsystems[TGT], SYS, SEG);
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
		    	SC_ASIYA sc_asiya;
				if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, Overlap::PlEXT, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", Overlap::RlEXT.c_str());
				}
				hOQ.save_hash_scores(Overlap::RlEXT, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(Overlap::RlEXT, TGT, REF));

			}
		}
		if (Config::Hmetrics.find(Overlap::FlEXT) != Config::Hmetrics.end()) {
			if (Config::verbose == 1) fprintf(stderr, "%s\n", Overlap::FlEXT.c_str());

			string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+Overlap::FlEXT+"/"+Common::XMLEXT;
			string reportXML_gz = reportXML+"."+Common::GZEXT;
	    	if ((!exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML_gz))) or Config::remake) {
	    		double SYS;
	    		vector<double> SEG;
	    		computeMultiFl(TESTBED::Hsystems[TGT], SYS, SEG);
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG, 0, TGT, d_scores, s_scores);
		    	SC_ASIYA sc_asiya;
				if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, Overlap::FlEXT, SYS, d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", Overlap::FlEXT.c_str());
				}
				hOQ.save_hash_scores(Overlap::FlEXT, TGT, REF, SYS, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(Overlap::FlEXT, TGT, REF));

			}
		}

	}
}

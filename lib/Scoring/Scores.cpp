#include "../include/Scores.hpp"
#include "../include/SC_NIST.hpp"
#include "../include/TESTBED.hpp"
#include "../Common.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>

Scores::Scores() {
	doc = vector<oMap>(TESTBED::get_num_docs());
	seg = vector<oMap>(TESTBED::get_num_segs());
}

Scores::~Scores() {}

vector<double> Scores::read_scores_G(string basename, string G, string TGT, int do_neg) {
	// description _ reads MetricsMaTr format scr file for a given metric and a given granularity

	string file = basename + "-" + G + ".scr";

	//read scr file
	SC_NIST sc_format;
	map<string, double> hscores = sc_format.read_scores_file(file, G, do_neg); //0);

	//delete scr file
	string sys_aux = "rm -f " + file;
	system (sys_aux.c_str());

		/*Crec que no cal, al ser un map ja esta reordenat
		vector<int> arscores = Common::reorder_scores(hscores, TGT, G);*/

	vector<double> scores;
	//for (map<string, int>::const_iterator it = hscores.begin(), int i = 0; it != hscores.end(); ++it, ++i) scores[i] = *it;

	for (map<string, double>::const_iterator it = hscores.begin(); it != hscores.end(); ++it) scores.push_back(it->second);

	if (!do_neg) {		//compute abs for those non do_neg metrics
		for (int i = 0; i < scores.size(); ++i) scores[i] = fabs(scores[i]);
	}

	return scores;
}

MetricScore Scores::read_scores(string basename, string TGT, int do_neg) {
	// description _ read system, document and segment scores (from the corresponding Metrics_MaTR-like format files)
	MetricScore read_scores;

	read_scores.sys_score = read_scores_G(basename, Common::G_SYS, TGT, do_neg)[0];
	read_scores.doc_scores = read_scores_G(basename, Common::G_DOC, TGT, do_neg);
	read_scores.seg_scores = read_scores_G(basename, Common::G_SEG, TGT, do_neg);

	return read_scores;
}

oMap Scores::get_sys_scores() const {
	return sys;
}

oMap Scores::get_doc_scores(int doc_id) const {
	return doc[doc_id];
}

oMap Scores::get_seg_scores(int seg_id) const {
	return seg[seg_id];
}

int Scores::get_num_doc_scores() const {
	return doc.size();
}

int Scores::get_num_seg_scores() const {
	return seg.size();
}

bool Scores::exists_sys_score(string METRIC, string TGT, string REF) {
	return (sys[METRIC][TGT].find(REF) != sys[METRIC][TGT].end());
}

bool Scores::exists_doc_score(string METRIC, string TGT, string REF) {
	return (doc[0][METRIC][TGT].find(REF) != doc[0][METRIC][TGT].end());
}

bool Scores::exists_seg_score(string METRIC, string TGT, string REF) {
	return (seg[0][METRIC][TGT].find(REF) != seg[0][METRIC][TGT].end());
}

bool Scores::exists_all_score(string METRIC, string TGT, string REF) {
	return (all[METRIC][TGT].find(REF) != all[METRIC][TGT].end());
}

void Scores::set_sys_score(string METRIC, string TGT, string REF, double x) {
	sys[METRIC][TGT][REF] = x;
}

void Scores::set_doc_score(int n, string METRIC, string TGT, string REF, double x) {
	doc[n][METRIC][TGT][REF] = x;
}

void Scores::set_seg_score(int n, string METRIC, string TGT, string REF, double x) {
	seg[n][METRIC][TGT][REF] = x;
}

/*void Scores::save_struct_scores(const char* filename) {
    ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

void Scores::load_struct_scores(const char* filename) {
    ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);
    ia >> *this;
}*/

void Scores::save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {
	MetricScore m;
	m.sys_score = sys_score;
	m.doc_scores = doc_scores;
	m.seg_scores = seg_scores;
	save_hash_scores(metric_name, system_name, refere_name, m);
}

void Scores::save_hash_scores(string metric_name, string system_name, string refere_name, const MetricScore &scores) {
	// description _ saves as a hash of scores

	// system-level
	sys[metric_name][system_name][refere_name] = scores.sys_score;

	//document-level
	for (int i = 0; i < scores.doc_scores.size(); ++i) {
		doc[i][metric_name][system_name][refere_name] = scores.doc_scores[i];
	}

	//segment-level
	for (int i = 0; i < scores.seg_scores.size(); ++i) {
		seg[i][metric_name][system_name][refere_name] = scores.seg_scores[i];
	}

	all[metric_name][system_name][refere_name] = -1;

	// system-level
//sys[metric_name][system_name] = vector<Score>(1, Score(refere_name, scores.sys_score));

	//document-level
/*vector<Score> aux_doc(scores.doc_scores.size());
for (int i = 0; i < scores.doc_scores.size(); ++i) {
	aux_doc[i] = Score(refere_name, scores.doc_scores[i]);
}
doc[metric_name][system_name] = aux_doc;*/

	//segment-level
/*vector<Score> aux_seg(scores.seg_scores.size());
for (int i = 0; i < scores.seg_scores.size(); ++i) {
	aux_seg[i] = Score(refere_name, scores.seg_scores[i]);
}
seg[metric_name][system_name] = aux_seg;*/

//all[metric_name][system_name] = vector<Score>(1, Score(refere_name, -1));
}

void Scores::save_struct_scores(string filename) {
    ofstream file(filename.c_str());
    if (file) {
        for (int n = 0; n < seg.size(); ++n) {
            for (oMap::const_iterator i = seg[n].begin(); i != seg[n].end(); ++i) {
                iMap metric_name = i->second;
                for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
                    sMap system_name = j->second;
                    for (sMap::const_iterator k = system_name.begin(); k != system_name.end(); ++k) {
                    	file << i->first << " " << j->first << " " << k->first << " " << k->second << endl;
                    }
                }
            }
        }
        file.close();
    } else { fprintf(stderr, "[ERROR] Could not serialize HASH scores: %s\n", filename.c_str()); exit(1); }
}

void Scores::load_struct_scores(char* filename, int &n_seg) {
    ifstream score_file(filename);
    if (score_file) {
        string str;
        while (getline(score_file, str)) {
            string token;
        	vector<string> strs(4);
            istringstream buf(str);
	    	for(int i = 0; i < 4; ++i) {
	    		getline(buf, token, ' ');
	    		strs[i] = token;
			}
                //string metric = strs[0];
                //string tgt = strs[1];
                //string ref = strs[2];
                //string score = strs[3];
                //hOQ.set_seg_score(n_seg, strs[0], strs[1], strs[2], strs[3]);
            seg[n_seg][strs[0]][strs[1]][strs[2]] = atof(strs[3].c_str());
            ++n_seg;
        }
    } else { fprintf(stderr, "[ERROR] Could not rebuild HASH scores file: %s\n", filename); exit(1); }
}

void Scores::print_sys_scores() const {
	cout << "----sys scores----" << endl;
	for (oMap::const_iterator i = sys.begin(); i != sys.end(); ++i) {
		cout << "\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t" << j->first << " -> {" << endl;
			sMap system_name = j->second;
			for (sMap::const_iterator k = system_name.begin(); k != system_name.end(); ++k) {
				cout << "\t\t\t" << k->first << " => " << k->second << endl;
			}
			cout << "\t\t}" << endl;
		}
		cout << "\t}" << endl;
	}
	cout << "}" << endl;
	cout << "------------------" << endl;
}

void Scores::print_doc_scores(int n) const {
	cout << "----doc[" << n << "] scores----" << endl;
	for (oMap::const_iterator i = doc[n].begin(); i != doc[n].end(); ++i) {
		cout << "\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t" << j->first << " -> {" << endl;
			sMap system_name = j->second;
			for (sMap::const_iterator k = system_name.begin(); k != system_name.end(); ++k) {
				cout << "\t\t\t" << k->first << " => " << k->second << endl;
			}
			cout << "\t\t}" << endl;
		}
		cout << "\t}" << endl;
	}
	cout << "}" << endl;
	cout << "---------------------" << endl;
}

void Scores::print_seg_scores(int n) const {
	cout << "----seg[" << n << "] scores----" << endl;
	for (oMap::const_iterator i = seg[n].begin(); i != seg[n].end(); ++i) {
		cout << "\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t" << j->first << " -> {" << endl;
			sMap system_name = j->second;
			for (sMap::const_iterator k = system_name.begin(); k != system_name.end(); ++k) {
				cout << "\t\t\t" << k->first << " => " << k->second << endl;
			}
			cout << "\t\t}" << endl;
		}
		cout << "\t}" << endl;
	}
	cout << "}" << endl;
	cout << "---------------------" << endl;
}
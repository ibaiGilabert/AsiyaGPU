#include "Scores.hpp"
#include "Common.hpp"
#include "NISTSCR.hpp"

#include <iostream>
#include <stdlib.h>

vector<double> Scores::read_scores_G(string basename, string G, string TGT) {
	// description _ reads MetricsMaTr format scr file for a given metric and a given granularity

	string file = basename + "-" + G + ".scr";

	//read scr file
	map<string, double> hscores = NISTSCR::read_scr_file(file, G, 0);

	//delete scr file
	string sys_aux = "rm -f " + file;
	system (sys_aux.c_str());

		/*Crec que no cal, al ser un map ja esta reordenat
		vector<int> arscores = Common::reorder_scores(hscores, TGT, G);*/

	vector<double> scores;
	//for (map<string, int>::const_iterator it = hscores.begin(), int i = 0; it != hscores.end(); ++it, ++i) scores[i] = *it;
	for (map<string, double>::const_iterator it = hscores.begin(); it != hscores.end(); ++it) scores.push_back(it->second);

	return scores;
}

MetricScore Scores::read_scores(string basename, string TGT) {
	// description _ read system, document and segment scores (from the corresponding Metrics_MaTR-like format files)
	MetricScore read_scores;

	read_scores.sys_score = read_scores_G(basename, Common::G_SYS, TGT)[0];
	read_scores.doc_scores = read_scores_G(basename, Common::G_DOC, TGT);
	read_scores.seg_scores = read_scores_G(basename, Common::G_SEG, TGT);

	return read_scores;
}


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
	sys[metric_name][system_name] = vector<Score>(1, Score(refere_name, scores.sys_score));

	//document-level
	//for (int i = 0; i < doc_scores.size(); ++i) {
		//doc[metric_name][system_name] = Score(refere_name, doc_scores[i]);
	//}

	//document-level
	vector<Score> aux_doc(scores.doc_scores.size());
	for (int i = 0; i < scores.doc_scores.size(); ++i) {
		aux_doc[i] = Score(refere_name, scores.doc_scores[i]);
	}
	doc[metric_name][system_name] = aux_doc;

	//segment-level
	vector<Score> aux_seg(scores.seg_scores.size());
	for (int i = 0; i < scores.seg_scores.size(); ++i) {
		aux_seg[i] = Score(refere_name, scores.seg_scores[i]);
	}
	seg[metric_name][system_name] = aux_seg;

	all[metric_name][system_name] = vector<Score>(1, Score(refere_name, -1));
}

void Scores::print_scores() {
	cout << "\tsys : " << endl;
	for (oMap::const_iterator i = sys.begin(); i != sys.end(); ++i) {
		cout << "\t\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t\t" << j->first << " -> {" << endl;
			vector<Score> system_name = j->second;
			for (int k = 0; k < system_name.size(); ++k) {
				cout << "\t\t\t\t" << system_name[k].first << " => " << system_name[k].second << endl;
			}
			cout << "\t\t\t}" << endl;
		}
		cout << "\t\t}" << endl;
	}
	cout << "\t}" << endl;

	cout << "\tdoc : " << endl;
	for (oMap::const_iterator i = doc.begin(); i != doc.end(); ++i) {
		cout << "\t\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t\t" << j->first << " -> {" << endl;
			vector<Score> system_name = j->second;
			for (int k = 0; k < system_name.size(); ++k) {
				cout << "\t\t\t\t" << system_name[k].first << " => " << system_name[k].second << endl;
			}
			cout << "\t\t\t}" << endl;
		}
		cout << "\t\t}" << endl;
	}
	cout << "\tseg : " << endl;
	for (oMap::const_iterator i = seg.begin(); i != seg.end(); ++i) {
		cout << "\t\t" << i->first << " -> " << endl;
		iMap metric_name = i->second;
		for (iMap::const_iterator j = metric_name.begin(); j != metric_name.end(); ++j) {
			cout << "\t\t\t" << j->first << " -> {" << endl;
			vector<Score> system_name = j->second;
			for (int k = 0; k < system_name.size(); ++k) {
				cout << "\t\t\t\t" << system_name[k].first << " => " << system_name[k].second << endl;
			}
			cout << "\t\t\t}" << endl;
		}
		cout << "\t\t}" << endl;
	}
}

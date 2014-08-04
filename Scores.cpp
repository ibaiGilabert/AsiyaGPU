#include "Scores.hpp"
#include "Common.hpp"

#include <iostream>

void Scores::save_hash_scores(string metric_name, string system_name, string refere_name, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {
	// description _ saves as a hash of scores

	// system-level
	sys[metric_name][system_name] = vector<Score>(1, Score(refere_name, sys_score));

	//document-level
	//for (int i = 0; i < doc_scores.size(); ++i) {
		//doc[metric_name][system_name] = Score(refere_name, doc_scores[i]);
	//}

	//document-level
	vector<Score> aux_doc(doc_scores.size());
	for (int i = 0; i < doc_scores.size(); ++i) {
		aux_doc[i] = Score(refere_name, doc_scores[i]);
	}
	doc[metric_name][system_name] = aux_doc;

	//segment-level
	vector<Score> aux_seg(seg_scores.size());
	for (int i = 0; i < seg_scores.size(); ++i) {
		aux_seg[i] = Score(refere_name, seg_scores[i]);
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
}

#include "../include/ULC.hpp"

const string ULC::ULC_NAME = "ULC";


void ULC::doMetric(Scores &hOQ, const set<string> &systems, const set<string> &references, const set<string> &metrics) {
	// description _ computes normalized ULC (i.e., normalized arithmetic mean) of metric scores (ULC scores are in the [0..1] range)
    string REF = Common::join_set(references, '_');

    for (set<string>::const_iterator it_s = systems.begin(); it_s != systems.end(); ++it_s) {
    	if (Config::G == Common::G_SYS) {
    		double x = 0;
    		for (set<string>::const_iterator it_m = metrics.begin(); it_m != metrics.end(); ++it_m) {
    			double min_score = hOQ.get_min_sys_score(*it_m);
    			double max_score = hOQ.get_max_sys_score(*it_m);
    			if (min_score < 0)
    				x += Common::safe_division( hOQ.get_sys_scores()[*it_m][*it_s][REF]+abs(min_score), max_score+abs(min_score) );
    			else
    				x += Common::safe_division( hOQ.get_sys_scores()[*it_m][*it_s][REF], max_score );
    		}
    		hOQ.set_sys_score(ULC::ULC_NAME, *it_s, REF, Common::safe_division(x, metrics.size()));
    	}
    	else if (Config::G == Common::G_DOC) {
    		for (int i = 0; i < hOQ.get_num_doc_scores(); ++i) {
    			double x = 0;
	    		for (set<string>::const_iterator it_m = metrics.begin(); it_m != metrics.end(); ++it_m) {
					double min_score = hOQ.get_min_doc_score(*it_m);
					double max_score = hOQ.get_max_doc_score(*it_m);
	    			if (min_score < 0)
	    				x += Common::safe_division( hOQ.get_doc_scores(i)[*it_m][*it_s][REF]+abs(min_score), max_score+abs(min_score) );
	    			else
	    				x += Common::safe_division( hOQ.get_doc_scores(i)[*it_m][*it_s][REF], max_score );
	    		}
	    		hOQ.set_doc_score(i, ULC::ULC_NAME, *it_s, REF, Common::safe_division(x, metrics.size()));
    		}
    	}
    	else {		//G_SEG
    		for (int i = 0; i < hOQ.get_num_seg_scores(); ++i) {
				double x = 0;
	    		for (set<string>::const_iterator it_m = metrics.begin(); it_m != metrics.end(); ++it_m) {
					double min_score = hOQ.get_min_seg_score(*it_m);
					double max_score = hOQ.get_max_seg_score(*it_m);
	    			if (min_score < 0)
	    				x += Common::safe_division( hOQ.get_seg_scores(i)[*it_m][*it_s][REF]+abs(min_score), max_score+abs(min_score) );
	    			else
	    				x += Common::safe_division( hOQ.get_seg_scores(i)[*it_m][*it_s][REF], max_score );
	    		}
	    		hOQ.set_seg_score(i, ULC::ULC_NAME, *it_s, REF, Common::safe_division(x, metrics.size()));
			}
    	}
	}
}
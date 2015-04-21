// g++ make_csv.cpp -o make_csv -lboost_system -lboost_filesystem 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

typedef map<string, string> 					split_score;
typedef map<string, split_score> 				metric_split_score;
typedef map<string, metric_split_score> 		system_metric_split_score; 
typedef map<string, system_metric_split_score>	corpus_system_metric_split_score;

string exec(const char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
		result += buffer;
	}
	pclose(pipe);
	return result;
}

int main(int argc, char *argv[]) {
	vector<string> corpuses(5);
	corpuses[0] = "ws_corpus100";	corpuses[1] = "ws_corpus200";	corpuses[2] = "ws_corpus500";
	corpuses[3] = "ws_corpus1000";	corpuses[4] = "ws_corpus2000";
	
	vector<string> splits(6);
	splits[0] = "1";	splits[1] = "2";	splits[2] = "4";
	splits[3] = "8";	splits[4] = "16";	splits[5] = "32";

	vector<string> systems(5);
	systems[0] = "Asiya-1.config";	systems[1] = "Asiya-2.config";		systems[2] = "Asiya-5.config";
	systems[3] = "Asiya-10.config";	systems[4] = "Asiya-all.config";
	
	vector<string> metrics(14);
	metrics[0]  = "SP";		metrics[1]  = "SR";			metrics[2]  = "CE";		metrics[3]  = "ESA";		metrics[4] = "GTM";
	metrics[5]  = "LEM";	metrics[6]  = "METEOR";		metrics[7]  = "NE";		metrics[8]  = "NGRAM";		metrics[9] = "O";
	metrics[10] = "PER";	metrics[11] = "ROUGE";		metrics[12] = "TER";	metrics[13] = "WER";

	corpus_system_metric_split_score times;

	for(int i = 0; i < corpuses.size(); ++i) {
		for(int j = 0; j < systems.size(); ++j) {
			for(int k = 0; k < metrics.size(); ++k) {
				for(int z = 0; z < splits.size(); ++z) {
			
					string path = corpuses[i]+"/"+splits[z];
					string file = path+"/" + (systems[j]+"."+splits[z]+".metrics_"+metrics[k]+".err");
					//cout << "file: <" << file << ">" << endl;
					if (exists(boost::filesystem::path(file)) ) {
						string exe = "cat "+file+" | grep --text TOTAL";
						//cout << "execute: " << exe << endl;
						string res = exec(exe.c_str());
						//cout << "res: " << res << endl;
						vector<string> strs;
						boost::split(strs, res, boost::is_any_of("\t ")); 	
						boost::algorithm::trim(strs[3]);

						//for(int r = 0; r < strs.size(); ++r) cout << "[" << r << "]: " << strs[r] << endl;
						//cout << "time: " << strs[3];
						times[corpuses[i]][systems[j]][metrics[k]][splits[z]] = strs[3];
					}
				}
			}
		}
	}

	/*cout << "------------" << endl;
	for(corpus_system_metric_split_score::const_iterator it_c = times.begin(); it_c != times.end(); ++it_c) {
		cout << "\t" << it_c->first << " - > " << endl;
		
		system_metric_split_score aux_c = it_c->second;
		for(system_metric_split_score::const_iterator it_s = aux_c.begin(); it_s != aux_c.end(); ++it_s) {
			cout << "\t\t" << it_s->first << " - > " << endl;

			metric_split_score aux_m = it_s->second;
			for(metric_split_score::const_iterator it_m = aux_m.begin(); it_m != aux_m.end(); ++it_m) {
				cout << "\t\t\t" << it_m->first << " - > " << endl;

				split_score aux_t = it_m->second;
				for(split_score::const_iterator it_t = aux_t.begin(); it_t != aux_t.end(); ++it_t) {
					cout << "\t\t\t\t" << it_t->first << " - > " << it_t->second << endl;
				}
			}
		}
	}
	cout << "------------" << endl;*/


	for(int i = 0; i < corpuses.size(); ++i) {
		string csv = corpuses[i]+".csv";
		ofstream corpus_csv(csv.c_str());
		if (corpus_csv) {

			for(int j = 0; j < systems.size(); ++j) {
				corpus_csv << systems[j] << endl;
				corpus_csv << endl;

				// header
				corpus_csv << "METRIC," << splits[0];
				for(int z = 1; z < splits.size(); ++z)
					corpus_csv << "," << splits[z];
				corpus_csv << endl;

				// each line
				for(int k = 0; k < metrics.size(); ++k) {
					corpus_csv << metrics[k];
					for(int z = 0; z < splits.size(); ++z)
						corpus_csv << ", " << times[corpuses[i]][systems[j]][metrics[k]][splits[z]];
					corpus_csv << endl;
				}
				corpus_csv << endl << endl;
			}
		}
		else { cout << "Could not open csv file <" << csv << ">" << endl; exit(1); }
	}
}
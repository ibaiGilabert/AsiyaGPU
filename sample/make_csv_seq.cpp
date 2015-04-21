// g++ make_csv_seq.cpp -o make_csv_seq -lboost_system -lboost_filesystem 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

typedef map<string, string>                     metric_score;
typedef map<string, metric_score>               system_metric_score; 
typedef map<string, system_metric_score>        corpus_system_metric_score;

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
        corpuses[0] = "ws_corpus100";   corpuses[1] = "ws_corpus200";   corpuses[2] = "ws_corpus500";
        corpuses[3] = "ws_corpus1000";  corpuses[4] = "ws_corpus2000";

        vector<string> systems(5);
        systems[0] = "Asiya-1.config";          systems[1] = "Asiya-2.config";          systems[2] = "Asiya-5.config";
        systems[3] = "Asiya-10.config";         systems[4] = "Asiya-all.config";

        vector<string> metrics(14);
        metrics[0]  = "SP";     metrics[1]  = "SR";             metrics[2]  = "CE";             metrics[3]  = "ESA";            metrics[4] = "GTM";
        metrics[5]  = "LEM";    metrics[6]  = "METEOR";         metrics[7]  = "NE";             metrics[8]  = "NGRAM";          metrics[9] = "O";
        metrics[10] = "PER";    metrics[11] = "ROUGE";          metrics[12] = "TER";            metrics[13] = "WER";

        corpus_system_metric_score times;

        for(int i = 0; i < corpuses.size(); ++i) {
                for(int j = 0; j < systems.size(); ++j) {
                        for(int k = 0; k < metrics.size(); ++k) {

                                string path = corpuses[i];
                                string file = path+"/" + (systems[j]+".metrics_"+metrics[k]+".err");
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
                                        times[corpuses[i]][systems[j]][metrics[k]] = strs[3];
                                }
                        }
                }
        }

        for(int i = 0; i < corpuses.size(); ++i) {
                string csv = corpuses[i]+"_seq.csv";
                ofstream corpus_csv(csv.c_str());
                if (corpus_csv) {

                        for(int j = 0; j < systems.size(); ++j) {
                                corpus_csv << systems[j] << endl;
                                corpus_csv << endl;

                                // header
                                corpus_csv << "METRIC" << endl;

                                // each line
                                for(int k = 0; k < metrics.size(); ++k) {
                                        corpus_csv << metrics[k];
                                        corpus_csv << ", " << times[corpuses[i]][systems[j]][metrics[k]] << endl;
                                }
                                corpus_csv << endl << endl;
                        }
                }
                else { cout << "Could not open csv file <" << csv << ">" << endl; exit(1); }
        }
}
#include "../include/TB_FORMAT.hpp"
#include "../Common.hpp"
#include "../Config.hpp"

#include <math.h>
#include <stdio.h>
#include <libgen.h>

#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

int TB_FORMAT::chunk = -1;

const string TB_FORMAT::TOK = "tokenizer";

map<string, string> TB_FORMAT::create_rLANGTOK() {
    map<string, string> rLANGTOK;
    rLANGTOK[Common::L_ENG] = "en"; rLANGTOK[Common::L_GER] = "de"; rLANGTOK[Common::L_SPA] = "es"; rLANGTOK[Common::L_CAT] = "ca";
    return rLANGTOK;
}
map<string, string> TB_FORMAT::rLANGTOK = create_rLANGTOK();


void TB_FORMAT::split_file(const char* file, const char* ext) {
    // split file for s processes
    double n_segs = TESTBED::get_num_segs();
    TB_FORMAT::chunk = n_segs/Config::num_process + (ceil(n_segs/Config::num_process) - floor(n_segs/Config::num_process));
    if (TB_FORMAT::chunk*(Config::num_process - 1) >= n_segs) --Config::num_process;    //parche. Ex -> n_segs: 33/ s: 10 (>)| Ex -> n_segs: 33/ s: 12 (==)
    //int n_files = s + (ceil(n_segs/s) - chunk);

/*cout << "--------split <" << string(file) << "---------" << endl;
cout << "num_process: " << s << endl;
cout << "n_segs: " << n_segs << endl;
cout << "n_files: " << n_files << " expected" << endl;
cout << "chunk: " << chunk << endl;*/
    boost::filesystem::path p(file);
    string basename_abs = p.parent_path().string() + "/" + p.stem().string();

    ofstream output_file;
    ifstream input_file(file);
    if (input_file) {
        string str, header;
        char buffer[128];
        int c_file = 1;
        int c_seg = 0;
        //int c_line = 0;
        sprintf(buffer, "%s.%.3d.%s", basename_abs.c_str(), c_file, ext);
        //fprintf(stderr, "[SPLIT] input to read <%s> /ext: %s/ output: %s\n", file, ext, buffer);
        output_file.open(buffer);

        if (strcmp (Common::IDXEXT.c_str(), ext) == 0) {
            getline(input_file, header);    //get header
            output_file << header << endl;
        }
        while(getline(input_file,str)) {
            //cout << "line[" << c_line << "]: seg: " << c_seg  << endl;
            //if (c_seg == 0 and strcmp (Common::IDXEXT.c_str(), ext) == 0)
            if (c_seg == TB_FORMAT::chunk) {
                ++c_file;
                c_seg %= chunk;
                sprintf(buffer, "%s.%.3d.%s", basename_abs.c_str(), c_file, ext);
                output_file.close();
                output_file.open(buffer);
                if (strcmp (Common::IDXEXT.c_str(), ext) == 0) output_file << header << endl;
            }
            output_file << str << endl;
            // ++c_line;
            ++c_seg;
        }
        output_file.close();
        input_file.close();

        if (c_file != Config::num_process) {
            Config::num_process = c_file;
            fprintf(stderr, "--- NUM_PROCESS UNIFORMED TO CORPUS SIZE (%d) ---\n", Config::num_process);
        }
    } else { fprintf(stderr, "couldn't open file: %s\n", file); exit(1); }
    //cout << "-----------------------------" << endl;
}

void TB_FORMAT::split_txt_idx(string file) {
    // description _ split input file into ".txt" and ".idx" format. 's' fragments.
    boost::filesystem::path p (file);
    //cout << "[SPLIT]: " << file << endl;

    split_file(file.c_str(), Common::TXTEXT.c_str());
    //cout << "[DONE]" << endl;
    //cout << "[SPLIT]: " << p.replace_extension(".idx") << endl;
    //string idx_ext = Common::TXTEXT + "." + Common::IDXEXT;
    split_file(TESTBED::replace_extension(file, Common::IDXEXT).c_str(), Common::IDXEXT.c_str());
    //split_file(p.replace_extension(".idx").c_str(), s);
    //cout << "[DONE]" << endl;
}

string TB_FORMAT::get_split(string file, string ext, int thread) {
    boost::filesystem::path p (file);
    string basename = p.parent_path().string() + "/" + p.stem().string();
    char split_file[100];
    if (ext == Common::TXTEXT) {
        sprintf(split_file,"%s.%.3d.%s", basename.c_str(), thread, Common::TXTEXT.c_str());
    } else if (ext == Common::IDXEXT) {
        sprintf(split_file,"%s.%.3d.%s", basename.c_str(), thread, Common::IDXEXT.c_str());
        //sprintf(split_file,"%s.%.3d.%s.%s", basename.c_str(), thread, Common::TXTEXT.c_str(), Common::IDXEXT.c_str());
    } else if (ext == Common::TOKEXT) {
        sprintf(split_file,"%s.%.3d.%s", basename.c_str(), thread, Common::TOKEXT.c_str());
    } else { fprintf(stderr, "[ERROR] Unknown extension <%s>\n", ext.c_str()); exit(1); }

    p = boost::filesystem::path(split_file);
    if (!exists(p)) { fprintf(stderr, "[ERROR] split file <%s> doesn't exist!\n", split_file); exit(1); }

    return string(split_file);
}

char* TB_FORMAT::get_serial(string METRIC, string TGT, string REF, int thread) {
    char* buffer = new char[128];
    sprintf(buffer, "serialized_%s_%s.%.3d_%s.%.3d", METRIC.c_str(), TGT.c_str(), thread, REF.c_str(), thread);
    return buffer;
}

char* TB_FORMAT::make_serial(string METRIC, string TGT, string REF) {
    char* buffer = new char[128];
    sprintf(buffer, "serialized_%s_%s_%s", METRIC.c_str(), TGT.c_str(), REF.c_str());
    return buffer;
}

int TB_FORMAT::get_thread(string file) {
	//cout << "[GET THREAD] file_name: " << file << " /extension: " << boost::filesystem::path(file).extension().string() << endl;
	return atof(file.substr(file.find_last_of(".") + 1).c_str());
    //return atof(boost::filesystem::path(file).extension().string().c_str());
}

/*string TB_FORMAT::get_formated_thread(string file) {
    return file.substr(file.find_last_of(".") + 1);
}*/


void TB_FORMAT::tokenize_file(string file, string lang) {
    // description _ tokenizes the given file
    srand(time(NULL));
    double nr = rand() % (Common::NRAND + 1);       // random number [0, Common::NRAND];
    string basename = boost::filesystem::path(file).filename().string();
    
    stringstream auxF, auxFT;
    auxF << Common::DATA_PATH << "/" << Common::TMP << "/" << basename << "." << nr;
    auxFT << Common::DATA_PATH << "/" << Common::TMP << "/" << basename << "." << nr << ".tok";

    string aux_file = auxF.str();
    string aux_file_tok = auxFT.str();

    ofstream o_file(aux_file.c_str());
    if (!o_file.is_open()) { fprintf(stderr, "couldn't open output aux file: %s\n", aux_file.c_str()); exit(1); }

    ifstream i_file(file.c_str());
    if (i_file) {
        string str;
        while ( getline(i_file, str) ) {
            if (lang == Common::L_ENG) {     // special cases
                boost::regex re("");
                str = boost::regex_replace(str, re, "");
                // ...

            }
            o_file << str << endl;
            
        }
        o_file.close();
        i_file.close();
    } else { fprintf(stderr, "couldn't open input file: %s\n", file.c_str()); exit(1); }

    string lang_opt = "";
    if (TB_FORMAT::rLANGTOK.find(lang) != TB_FORMAT::rLANGTOK.end())
        lang_opt = "-l " + rLANGTOK[lang];

    string cmd = "cat "+aux_file+" | "+Config::tools+"/"+TB_FORMAT::TOK+"/tokenizer.pl "+lang_opt+" > "+aux_file_tok+" 2> "+aux_file_tok+".err";
    Common::execute_or_die(cmd, "[ERROR] problems running tokenizer...");

    string sys_aux;
    sys_aux = "mv "+aux_file_tok+" "+file;  system(sys_aux.c_str());
    sys_aux = "rm "+aux_file;               system(sys_aux.c_str());
    sys_aux = "rm -f "+aux_file_tok+".err"; system(sys_aux.c_str());
}
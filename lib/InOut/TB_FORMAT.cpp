#include "../include/TB_FORMAT.hpp"
#include "../Common.hpp"

#include <math.h>
#include <stdio.h>
#include <libgen.h>

#include <fstream>

#include <boost/filesystem.hpp>

int TB_FORMAT::chunk = -1;

void TB_FORMAT::split_file(const char* file, const char* ext, int s) {
    // split file for s processes
    double n_segs = TESTBED::get_num_segs();
    TB_FORMAT::chunk = n_segs/s + (ceil(n_segs/s) - floor(n_segs/s));
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
    } else { fprintf(stderr, "couldn't open file: %s\n", file); exit(1); }
    //cout << "-----------------------------" << endl;
}

void TB_FORMAT::split_txt_idx(string file, int s) {
    // description _ split input file into ".txt" and ".idx" format
    boost::filesystem::path p (file);
    //cout << "[SPLIT]: " << file << endl;

    split_file(file.c_str(), Common::TXTEXT.c_str(), s);
    //cout << "[DONE]" << endl;
    //cout << "[SPLIT]: " << p.replace_extension(".idx") << endl;
    //string idx_ext = Common::TXTEXT + "." + Common::IDXEXT;
    split_file(TESTBED::replace_extension(file, Common::IDXEXT).c_str(), Common::IDXEXT.c_str(), s);
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

#include "../include/TB_FORMAT.hpp"

#include <math.h>
#include <stdio.h>

#include <fstream>

#include <boost/filesystem.hpp>

void TB_FORMAT::split_file(const char* file, int s) {
    // split file for s processes
    double n_segs = TESTBED::get_num_segs();
    int chunk = floor(n_segs/s);
    int n_files = s + (ceil(n_segs/s) - chunk);

/*cout << "--------split <" << string(file) << "---------" << endl;
cout << "num_process: " << s << endl;
cout << "n_segs: " << n_segs << endl;
cout << "n_files: " << n_files << " expected" << endl;
cout << "chunk: " << chunk << endl;*/

    ofstream output_file;
    ifstream input_file(file);
    if (input_file) {
        string str;
        char buffer[128];
        int c_file = 1;
        int c_seg = 1;
        //int c_line = 1;
        sprintf(buffer, "%s.%.3d", file, c_file);
        output_file.open(buffer);

        while(c_file < n_files) {
            getline(input_file,str);
                //cout << "line[" << c_line << "]: " << str << endl;
            if (c_seg > chunk) {
                ++c_file;
                c_seg %= chunk;
                sprintf(buffer, "%s.%.3d", file, c_file);
                output_file.close();
                output_file.open(buffer);
            }
                //cout << "\tFILE: " << c_file << "; seg: " << c_seg << endl;
            output_file << str << endl;
            //++c_line;
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
    split_file(file.c_str(), s);
    //cout << "[DONE]" << endl;
    //cout << "[SPLIT]: " << p.replace_extension(".idx") << endl;
    split_file(p.replace_extension(".idx").c_str(), s);
    //cout << "[DONE]" << endl;
}
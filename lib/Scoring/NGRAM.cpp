#include "../include/NGRAM.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

const string EMPTY_ITEM = "*";
const string NGRAMSRC = "src";
const string NGRAMREF = "ref";

const string NGRAMEXT = "NGRAM";
const string CENGRAMEXT = "CENGRAM";
const string TNGRAM = "ComputeSimilaritiesQE.jar";
const string TNGRAMdir = "lengthmodel";
const string TRANSLITERATOR = "transliterator/Transliterator.jar";

map<string, int> NGRAM::create_rNGRAM() {
	map<string, int> rNGRAM;
	rNGRAM[NGRAM::NGRAMEXT + "-cosTok2ngrams"] = 1;	rNGRAM[NGRAM::NGRAMEXT + "-cosTok3ngrams"] = 1;
	rNGRAM[NGRAM::NGRAMEXT + "-cosTok4ngrams"] = 1;	rNGRAM[NGRAM::NGRAMEXT + "-cosTok5ngrams"] = 1;
	rNGRAM[NGRAM::NGRAMEXT + "-jacTok2ngrams"] = 1;	rNGRAM[NGRAM::NGRAMEXT + "-jacTok3ngrams"] = 1;
	rNGRAM[NGRAM::NGRAMEXT + "-jacTok4ngrams"] = 1;	rNGRAM[NGRAM::NGRAMEXT + "-jacTok5ngrams"] = 1;
	return rNGRAM;
}
const map<string, int> NGRAM::rNGRAM = create_rNGRAM();

map<string, int> NGRAM::create_rCENGRAM() {
	map<string, int> rCENGRAM;
	rCENGRAM[NGRAM::NGRAMEXT + "-cosChar2ngrams"] = 1;	rCENGRAM[NGRAM::NGRAMEXT + "-cosChar3ngrams"] = 1;
	rCENGRAM[NGRAM::NGRAMEXT + "-cosChar4ngrams"] = 1;	rCENGRAM[NGRAM::NGRAMEXT + "-cosChar5ngrams"] = 1;
	rCENGRAM[NGRAM::NGRAMEXT + "-jacChar2ngrams"] = 1;	rCENGRAM[NGRAM::NGRAMEXT + "-jacChar3ngrams"] = 1;
	rCENGRAM[NGRAM::NGRAMEXT + "-jacChar4ngrams"] = 1;	rCENGRAM[NGRAM::NGRAMEXT + "-jacChar5ngrams"] = 1;
	rCENGRAM[NGRAM::NGRAMEXT + "-jacCognates"] = 1;		rCENGRAM[NGRAM::NGRAMEXT + "-lenratio"] = 1;
	return rNGRAM;
}
const map<string, int> NGRAM::rNGRAM = create_rNGRAM();

NGRAM::NGRAM_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for NGRAM parsing...\n", input.c_str());

    boost::filesystem::path input_path(input);

	if (!exists(input_path)) {
		if (Config::verbose > 1) fprintf(stderr, "reading <%s>\n", input.c_str());

	    ifstream input_file(input.c_str());
	    ofstream output_file(output.c_str());

	    if (input_file) {
	    	string str;
		    while (getline(file, str)) {
      			boost::regex re("\\/\\s*$");//, boost::regex::perl|boost::regex::icase);
        		it->second = boost::regex_replace(it->second, re, "");
/*
		    	boost::match_results<string::const_iterator> results;
		        if (boost::regex_match(str, results, re)) {
		            cout << "\t That was a kind of line" << endl;
		            string s = results[0];
		            cout << "line: |" << s << "|" << endl;

					boost::regex re2("^\\s+BLEU:\\s+");
					s = boost::regex_replace(s, re2, "");

					cout << "\tline1: " << s << endl;

		            istringstream iss(s);
					double value;
					for (int i = 0; i < 4; ++i) {
						iss >> value;
						if (individual) lbleu[i] = value;
						else lbleui[i] = value;
					}
					individual = true;
		        }*/


		    }
	        file.close();
	    } else { fprintf(stderr, "couldn't open file: %s\n", input_file.c_str()); exit(1); }
	}
}


    ofstream f_idx(system_name.c_str());
    if (f_idx) {
        stringstream ss;
        ss << Common::UNKNOWN_SET << " " << Common::UNKNOWN_LANG << " " << Common::UNKNOWN_LANG;
        string fake_header = ss.str();

        f_idx << fake_header << endl;

        vector<string> l_header;

        boost::regex reeq(" ");
        boost::sregex_token_iterator j;
        for(boost::sregex_token_iterator i(fake_header.begin(), fake_header.end(), reeq, -1); i != j; ++i) {
            l_header.push_back(*i);
        }
        lIDX.push_back(l_header);

        ifstream f_raw(file.c_str());
        if (f_raw) {
            string line;
            int i = 1;

            while (getline(f_raw, line)) {
                stringstream sf;
                sf << Common::UNKNOWN_DOC << " " << Common::UNKNOWN_GENRE << " " << system_name << " " << i;
                string fake_line = sf.str();

                vector<string> l;

                boost::sregex_token_iterator jj;
                for(boost::sregex_token_iterator ii(fake_line.begin(), fake_line.end(), reeq, -1); ii != jj; ++ii) {
                    l.push_back(*ii);
                }
                lIDX.push_back(l);
                f_idx << fake_line << endl;
                i++;
            }
            f_raw.close();
        } else { fprintf(stderr, "couldn't open input file: %s\n", file.c_str());   exit(1); }

        f_idx.close();
    } else { fprintf(stderr, "couldn't open output IDX file: %s\n", system_name.c_str());	exit(1); }


//computeNGRAM($NGRAM::NGRAMREF, $out, $Href->{$ref}, $tools, $case, $srclang, $trglang, $verbose, $issrcbased);
NGRAM::computeNGRAM(string opt, string ref, string TGT) {
	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];

	stringstream ssOut, ssRef, ssReport;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << "." << Common::SYSEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << "." << Common::REFEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << "." << Common::REPORTEXT;

	string outRND= ssOut.str();
	string refRND= ssRef.str();
	string reportNGRAM = ssReport.str();

	NGRAM_f_create_doc(TESTBED::Hsystems[TGT], outRND);
	NGRAM_f_create_doc(ref, refRND);

	if (verbose > 1) fprintf(stderr, "building %s...\n", reportNGRAM.c_str());


}

//my ($SYS,$SEGS) = NGRAM::computeMultiNGRAM($NGRAM::NGRAMSRC, $out, $Href, $src, $config->{CASE}, $srcL, $trgL, $tools, $verbose, 1 );
pair<vector<double>, vector<vector<double> > > NGRAM::computeMultiNGRAM(string opt, string TGT) {
	if (opt == NGRAM::NGRAMREF) {
    	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    		computeNGRAM(NGRAM::NGRAMREF, it->second, TGT);
    	}
	}
	else if (opt== NGRAM::NGRAMSRC) {

	}
}


void NGRAM::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes NGRAM score (multiple references)
	vector<string> mNGRAM(NGRAM::rNGRAM.size());

	int GO , i;
	GO = i = 0;
	for (map<string, int>::const_iterator it = NGRAM::rNGRAM.begin(); it != NGRAM::rNGRAM.end(); ++it, ++i)
		mNGRAM[i] = it->first;

	i = 0;
	while (i < mNGRAM.size() and !GO) {
		if (Config::Hmetrics.find(mNGRAM[i]) != Config::Hmetrics.end()) GO = 1;
		++i;
	}

	cout << "NGRAM ei!" << endl;
	if (GO) {
		cout << "GO! NGRAM GO!" << endl;
		if (Config::verbose == 1) fprintf(stderr, "%s\n", NGRAM::NGRAMEXT.c_str());

		stringstream ss2cos, ss3cos, ss4cos, ss5cos, ss2jac, ss3jac, ss4jac, ss5jac;
		ss2cos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-cosTok2ngrams." << Common::XMLEXT;
		ss3cos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-cosTok2ngrams." << Common::XMLEXT;
		ss4cos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-cosTok2ngrams." << Common::XMLEXT;
		ss5cos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-cosTok2ngrams." << Common::XMLEXT;

		ss2jac << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-jacTok2ngrams." << Common::XMLEXT;
		ss3jac << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-jacTok3ngrams." << Common::XMLEXT;
		ss4jac << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-jacTok4ngrams." << Common::XMLEXT;
		ss5jac << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << REF << "/" << prefix << NGRAM::NGRAMEXT << "-jacTok5ngrams." << Common::XMLEXT;

		string reportNGRAMcos2 = ss2cos.str();
		string reportNGRAMcos3 = ss3cos.str();
		string reportNGRAMcos4 = ss4cos.str();
		string reportNGRAMcos5 = ss5cos.str();
		string reportNGRAMjac2 = ss2jac.str();
		string reportNGRAMjac3 = ss3jac.str();
		string reportNGRAMjac4 = ss4jac.str();
		string reportNGRAMjac5 = ss5jac.str();

	    boost::filesystem::path reportNGRAMcos2_path(reportNGRAMcos2);
	    boost::filesystem::path reportNGRAMcos3_path(reportNGRAMcos3);
	    boost::filesystem::path reportNGRAMcos4_path(reportNGRAMcos4);
	    boost::filesystem::path reportNGRAMcos5_path(reportNGRAMcos5);
	    boost::filesystem::path reportNGRAMjac2_path(reportNGRAMjac2);
	    boost::filesystem::path reportNGRAMjac3_path(reportNGRAMjac3);
	    boost::filesystem::path reportNGRAMjac4_path(reportNGRAMjac4);
	    boost::filesystem::path reportNGRAMjac5_path(reportNGRAMjac5);

	    boost::filesystem::path reportNGRAMcos2_gz(reportNGRAMcos2 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMcos3_gz(reportNGRAMcos3 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMcos4_gz(reportNGRAMcos4 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMcos5_gz(reportNGRAMcos5 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMjac2_gz(reportNGRAMjac2 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMjac3_gz(reportNGRAMjac3 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMjac4_gz(reportNGRAMjac4 + "." + Common::GZEXT);
	    boost::filesystem::path reportNGRAMjac5_gz(reportNGRAMjac5 + "." + Common::GZEXT);

	    if ( (!exists(reportNGRAMcos2_path) and !exists(reportNGRAMcos2_gz)) or \
	    	(!exists(reportNGRAMcos3_path) and !exists(reportNGRAMcos3_gz)) or \
    		(!exists(reportNGRAMcos4_path) and !exists(reportNGRAMcos4_gz)) or \
			(!exists(reportNGRAMcos5_path) and !exists(reportNGRAMcos5_gz)) or \
			(!exists(reportNGRAMjac2_path) and !exists(reportNGRAMjac2_gz)) or \
			(!exists(reportNGRAMjac3_path) and !exists(reportNGRAMjac3_gz)) or \
			(!exists(reportNGRAMjac4_path) and !exists(reportNGRAMjac4_gz)) or \
			(!exists(reportNGRAMjac5_path) and !exists(reportNGRAMjac5_gz)) or Config::remake) {

	    	pair<vector<double>, vector<vector<double> > > res = computeMultiNGRAM(TGT);

	    }


	}

}
#include "../include/NGRAM.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <libgen.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

const string NGRAM::EMPTY_ITEM = "*";
const string NGRAM::NGRAMSRC = "src";
const string NGRAM::NGRAMREF = "ref";

const string NGRAM::NGRAMEXT = "NGRAM";
const string NGRAM::CENGRAMEXT = "CENGRAM";
const string NGRAM::TNGRAM = "ComputeSimilaritiesQE.jar";
const string NGRAM::TNGRAMdir = "lengthmodel";
const string NGRAM::TRANSLITERATOR = "transliterator/Transliterator.jar";

set<string> NGRAM::create_rNGRAM() {
	set<string> rNGRAM;
	rNGRAM.insert(NGRAM::NGRAMEXT + "-cosTok2ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-cosTok3ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-cosTok4ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-cosTok5ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-jacTok2ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-jacTok3ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-jacTok4ngrams");
	rNGRAM.insert(NGRAM::NGRAMEXT + "-jacTok5ngrams");
	return rNGRAM;
}
const set<string> NGRAM::rNGRAM = create_rNGRAM();

set<string> NGRAM::create_rCENGRAM() {
	set<string> rCENGRAM;
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-cosChar2ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-cosChar3ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-cosChar4ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-cosChar5ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-jacChar2ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-jacChar3ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-jacChar4ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-jacChar5ngrams");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-jacCognates");
	rCENGRAM.insert(NGRAM::NGRAMEXT + "-lenratio");
	return rNGRAM;
}
const set<string> NGRAM::rCENGRAM = create_rCENGRAM();


void NGRAM::NGRAM_f_create_doc(string input, string output) {
	// description _ creation of a RAW evaluation document
	if (Config::verbose) fprintf(stderr, "OPENING <%s> for NGRAM parsing...\n", input.c_str());

	if (exists(boost::filesystem::path(input))) {
		if (Config::verbose) fprintf(stderr, "reading <%s>\n", input.c_str());

	    ifstream input_file(input.c_str());
	    ofstream output_file(output.c_str());
	    if (!output_file) { fprintf(stderr, "couldn't open output file: %s\n", output.c_str()); exit(1); }
	    if (input_file) {
	    	string str;
  			//boost::regex re("\\s*$"), re_1("^$"), re_2("^[!?.]$");
			boost::match_results<string::const_iterator> results;
  			while (getline(input_file, str)) {
				str = boost::regex_replace(str, Common::reEND_SPACE, "");

				if (/*boost::regex_match(str, results, Common::reEMPTY)*/ str.empty()) str = NGRAM::EMPTY_ITEM + " .";
				else if (boost::regex_match(str, results, Common::reSPECIAL_CHAR)) str = NGRAM::EMPTY_ITEM + " " + str;

				//if (Config::CASE == Common::CASE_CI) boost::to_lower(str);
				boost::to_lower(str);
				output_file << str << endl;
			}
			output_file.close();
	        input_file.close();
	    } else { fprintf(stderr, "couldn't open input file: %s\n", input.c_str()); exit(1); }
	} else { fprintf(stderr, "\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str()); exit(1); }
}

void NGRAM::read_NGRAM_segments(string reportNGRAM, string opt, map<string, vector<double> > &SEGS) {
	// description _ read NGRAM value from report file (for all segments)
	ifstream file(reportNGRAM.c_str());
    if (file) {
    	string str;
    	vector<string> lheader;
    	getline(file, str);
	    istringstream iss_h(str);
	    for(string token; getline(iss_h, token, ','); ) lheader.push_back(token);

		//boost::regex re_t("^.*Tok.*$"), re_ch("^.*Char.*$"), re_co("^.*Cognates.*$"), re_l("^.*lenratio.*$");

		//boost::regex re_c("Char");
		boost::match_results<string::const_iterator> results;

	    while (getline(file, str)) {
	    	vector<string> laux;
	    	istringstream iss(str);
		    for (string token; getline(iss, token, ','); ) laux.push_back(token);
		    for (int i = 0; i < laux.size(); ++i) {
		    	string header = lheader[i];
		    	double value = (laux[i] != "NaN") ? atof(laux[i].c_str()) : 0;

    		    if (opt == NGRAM::NGRAMREF and boost::regex_match(header, results, Common::reNGRAM_t))
    		    	SEGS[header].push_back(value);
    		    else if (opt == NGRAM::NGRAMSRC and (boost::regex_match(header, results, Common::reNGRAM_ch) or boost::regex_match(header, results, Common::reNGRAM_co) or boost::regex_match(header, results, Common::reNGRAM_re_l)) )
    		    	SEGS[header].push_back(value);
		    }
		}
        file.close();
    } else { fprintf(stderr, "couldn't open file: %s\n", reportNGRAM.c_str()); exit(1); }
}

void NGRAM::computeNGRAM(string opt, string ref, string TGT, int issrcbased, map<string, vector<double> > &SEGS) {
	//srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);	//random number [0, Common::NRAND];
	string t_id;
    if (Config::serialize) t_id = "_" + TGT;//TB_FORMAT::get_formated_thread(TGT);

	string out = TESTBED::Hsystems[TGT];
	string pwd = boost::filesystem::current_path().string();

	stringstream ssOut, ssRef, ssReport;
	ssOut << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << t_id << "." << Common::SYSEXT;
	ssRef << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << t_id << "." << Common::REFEXT;
	ssReport << Common::DATA_PATH << "/" << Common::TMP << "/" << nr << "." << NGRAM::NGRAMEXT << t_id << "." << Common::REPORTEXT;

	string outRND = ssOut.str();
	string refRND = ssRef.str();
	string reportNGRAM = ssReport.str();

	NGRAM_f_create_doc(out, outRND);
	NGRAM_f_create_doc(ref, refRND);

//fprintf(stderr, "[NGRAM] f_create_doc <%s> CREATED\n", outRND.c_str());
//fprintf(stderr, "[NGRAM] f_create_doc <%s> CREATED\n", refRND.c_str());

	if (Config::verbose) fprintf(stderr, "building %s...\n", reportNGRAM.c_str());

/*	string pwd = boost::filesystem::current_path().string();

	boost::regex re("\\.\\/");
    boost::match_results<string::const_iterator> results;
    if (boost::regex_match(outRND, results, re)) {
		boost::regex_replace(outRND, re, "");
		outRND = pwd+"/"+outRND;
	}
	if (boost::regex_match(refRND, results, re)) {
    	boost::regex_replace(refRND, re, "");
		refRND = pwd+"/"+refRND;
	}
    if (boost::regex_match(reportNGRAM, results, re)) {
		boost::regex_replace(reportNGRAM, re, "");
		reportNGRAM = pwd+"/"+reportNGRAM;
	}
*/
	// if language is russian, first transliterate
	if (Config::LANG == Common::L_RUS) {
		string transliterator = "/usr/local/jdk1.7.0/bin/java -Xms1024M -Xmx1024M -Dfile.encoding=UTF-8 -jar "+Config::tools+"/"+NGRAM::TRANSLITERATOR+" -l ru -i "+outRND;
		string sc = transliterator+" > /dev/null 2> /dev/null";
		//string ms = "[ERROR] problems running TRANSLITERATOR...";
		Common::execute_or_die(sc, "[ERROR] problems running TRANSLITERATOR...");
		stringstream transname;
		transname << dirname(&outRND[0]) << "/trans." << boost::filesystem::path(outRND).filename();
		string mv = "mv " + transname.str() + " " + outRND;
		system(mv.c_str());
	}
	if ((Config::LANG == Common::L_RUS and issrcbased == 0) or (Config::LANG == Common::L_RUS and issrcbased == 1)) {
		string transliterator = "/usr/local/jdk1.7.0/bin/java -Xms1024M -Xmx1024M -Dfile.encoding=UTF-8 -jar "+Config::tools+"/"+NGRAM::TRANSLITERATOR+" -l ru -i "+refRND;
		string sc = transliterator+" > /dev/null 2> /dev/null";
		Common::execute_or_die(sc, "[ERROR] problems running TRANSLITERATOR...");
		stringstream transname;
		transname << dirname(&refRND[0]) << "/trans." << boost::filesystem::path(refRND).filename();
		string mv = "mv " + transname.str() + " " + refRND;
		system(mv.c_str());
	}

	string mem_options = "-Xms1024M -Xmx3072M";
	string toolNGRAM = "java -Dfile.encoding=UTF-8 "+mem_options+" -jar "+Config::tools+"/"+NGRAM::TNGRAMdir+"/"+NGRAM::TNGRAM;
	string sc = "cd "+Config::tools+"/"+NGRAM::TNGRAMdir+"; "+toolNGRAM+" -i "+outRND+" -j "+refRND+" -o "+reportNGRAM+" > /dev/null 2> /dev/null ; cd "+pwd+";";
//fprintf(stderr, "[NGRAM] EXE: %s\n", sc.c_str());
	Common::execute_or_die(sc,"[ERROR] problems running NGRAM...");

	read_NGRAM_segments(reportNGRAM, opt, SEGS);

	string rm;
	rm = "rm -f " + refRND;			system(rm.c_str());
	rm = "rm -f " + outRND;			system(rm.c_str());
	rm = "rm -f " + reportNGRAM;	system(rm.c_str());
}

void NGRAM::computeMultiNGRAM(string opt, string TGT, int issrcbased, map<string, double> &MAXSYS, map<string, vector<double> > &MAXSEG) {
	// description _ computes NGRAM score (multiple references)

	if (opt == NGRAM::NGRAMREF) {
    	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
    		map<string, vector<double> > SEGS;
    		computeNGRAM(NGRAM::NGRAMREF, it->second, TGT, issrcbased, SEGS);
    		for (map<string, vector<double> >::const_iterator it = SEGS.begin(); it != SEGS.end(); ++it) {
    			if (MAXSEG[it->first].empty()) MAXSEG[it->first] = vector<double>(it->second.size(), Common::NOT_DEFINED);
    			for (int i = 0; i < it->second.size(); ++i) {	// update max scores
    				if (MAXSEG[it->first][i] != Common::NOT_DEFINED) {
    					if (it->second[i] > MAXSEG[it->first][i]) MAXSEG[it->first][i] = it->second[i];
    				}
    				else 
    					MAXSEG[it->first][i] = it->second[i];
    			}
    		}
    	}
		for (map<string, vector<double> >::const_iterator it = MAXSEG.begin(); it != MAXSEG.end(); ++it) {
			double maxsys = 0;
			for (int i = 0; i < it->second.size(); ++i)
				maxsys += it->second[i];
			MAXSYS[it->first] = Common::safe_division(maxsys, it->second.size());
		}
	}
	else if (opt== NGRAM::NGRAMSRC) {
		map<string, vector<double> > SEGS;
		computeNGRAM(NGRAM::NGRAMSRC, TESTBED::src, TGT, issrcbased, SEGS);

        /*fprintf(stderr, "[NGRAM-SRC] SEGS (after computeNGRAM, TGT: %s)\n", TGT.c_str());
        for(map<string, vector<double> >::const_iterator it = SEGS.begin(); it != SEGS.end(); ++it) {
                fprintf(stderr, "\t%s -> [", it->first.c_str());
                for(int k = 0; k < it->second.size(); ++k) {
                        fprintf(stderr, " %f, ", it->second[k]);
                }
                fprintf(stderr, "]\n");
        }*/

		for (map<string, vector<double> >::const_iterator it = SEGS.begin(); it != SEGS.end(); ++it) {
			if (MAXSEG[it->first].empty()) MAXSEG[it->first] = vector<double>(it->second.size(), Common::NOT_DEFINED);
			for (int i = 0; i < it->second.size(); ++i) {	// update max scores
				if (MAXSEG[it->first][i] != Common::NOT_DEFINED) {
					if (it->second[i] > MAXSEG[it->first][i]) MAXSEG[it->first][i] = it->second[i];
				}
				else 
					MAXSEG[it->first][i] = it->second[i];
			}
		}
		for (map<string, vector<double> >::const_iterator it = MAXSEG.begin(); it != MAXSEG.end(); ++it) {
			double maxsys = 0;
			for (int i = 0; i < it->second.size(); ++i)
				maxsys += it->second[i];
			MAXSYS[it->first] = Common::safe_division(maxsys, it->second.size());
		}

	}
}

void NGRAM::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes NGRAM score (multiple references)
	int GO = 0;
	for (set<string>::const_iterator it = NGRAM::rNGRAM.begin(); !GO and it != NGRAM::rNGRAM.end(); ++it) {
		if (Config::Hmetrics.count(*it)) GO = 1;
	}
	// reference-based measures
	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", NGRAM::NGRAMEXT.c_str());

		string reportNGRAMcos2 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosTok2ngrams."+Common::XMLEXT;
		string reportNGRAMcos3 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosTok3ngrams."+Common::XMLEXT;
		string reportNGRAMcos4 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosTok4ngrams."+Common::XMLEXT;
		string reportNGRAMcos5 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosTok5ngrams."+Common::XMLEXT;
		string reportNGRAMjac2 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacTok2ngrams."+Common::XMLEXT;
		string reportNGRAMjac3 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacTok3ngrams."+Common::XMLEXT;
		string reportNGRAMjac4 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacTok4ngrams."+Common::XMLEXT;
		string reportNGRAMjac5 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacTok5ngrams."+Common::XMLEXT;

	    if ((!exists(boost::filesystem::path(reportNGRAMcos2)) and !exists(boost::filesystem::path(reportNGRAMcos2+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos3)) and !exists(boost::filesystem::path(reportNGRAMcos3+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos4)) and !exists(boost::filesystem::path(reportNGRAMcos4+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos5)) and !exists(boost::filesystem::path(reportNGRAMcos5+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac2)) and !exists(boost::filesystem::path(reportNGRAMjac2+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac3)) and !exists(boost::filesystem::path(reportNGRAMjac3+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac4)) and !exists(boost::filesystem::path(reportNGRAMjac4+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac5)) and !exists(boost::filesystem::path(reportNGRAMjac5+"."+Common::GZEXT))) or Config::remake) {

	    	map<string, double> SYS;
	    	map<string, vector<double> > SEG;
	    	computeMultiNGRAM(NGRAM::NGRAMREF, TGT, 0, SYS, SEG);
			for (map<string, double>::const_iterator it = SYS.begin(); it != SYS.end(); ++it) {
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG[it->first], 0, TGT, d_scores, s_scores);
				string pref = prefix + NGRAM::NGRAMEXT+"-"+it->first;
				if (Config::O_STORAGE == 1) {
					sc_asiya.write_report(TGT, REF, pref, SYS[it->first], d_scores, s_scores);
					fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
				}
				hOQ.save_hash_scores(pref, TGT, REF, it->second, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(NGRAM::NGRAMEXT, TGT, REF));
			}
	    }
	}

    // source-based measures (CE)
	GO = 0;
	for (set<string>::const_iterator it = NGRAM::rCENGRAM.begin(); !GO and it != NGRAM::rCENGRAM.end(); ++it)
		if (Config::Hmetrics.count(*it)) GO = 1;

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", NGRAM::NGRAMEXT.c_str());

		string reportNGRAMcos2 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosChar2ngrams."+Common::XMLEXT;
		string reportNGRAMcos3 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosChar3ngrams."+Common::XMLEXT;
		string reportNGRAMcos4 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosChar4ngrams."+Common::XMLEXT;
		string reportNGRAMcos5 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-cosChar5ngrams."+Common::XMLEXT;
		string reportNGRAMjac2 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacChar2ngrams."+Common::XMLEXT;
		string reportNGRAMjac3 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacChar3ngrams."+Common::XMLEXT;
		string reportNGRAMjac4 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacChar4ngrams."+Common::XMLEXT;
		string reportNGRAMjac5 = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacChar5ngrams."+Common::XMLEXT;
		string reportNGRAMjacC = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-jacCognates."+Common::XMLEXT;
		string reportNGRAMlen  = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+prefix+NGRAM::NGRAMEXT+"-lenratio"+Common::XMLEXT;

	    if ((!exists(boost::filesystem::path(reportNGRAMcos2)) and !exists(boost::filesystem::path(reportNGRAMcos2+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos3)) and !exists(boost::filesystem::path(reportNGRAMcos3+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos4)) and !exists(boost::filesystem::path(reportNGRAMcos4+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMcos5)) and !exists(boost::filesystem::path(reportNGRAMcos5+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac2)) and !exists(boost::filesystem::path(reportNGRAMjac2+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac3)) and !exists(boost::filesystem::path(reportNGRAMjac3+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac4)) and !exists(boost::filesystem::path(reportNGRAMjac4+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjac5)) and !exists(boost::filesystem::path(reportNGRAMjac5+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMjacC)) and !exists(boost::filesystem::path(reportNGRAMjacC+"."+Common::GZEXT))) or
	    	(!exists(boost::filesystem::path(reportNGRAMlen))  and !exists(boost::filesystem::path(reportNGRAMlen+"."+Common::GZEXT)))  or Config::remake) {

	    	map<string, double> SYS;
	    	map<string, vector<double> > SEG;
	    	computeMultiNGRAM(NGRAM::NGRAMSRC, TGT, 1, SYS, SEG);
			for (map<string, double>::const_iterator it = SYS.begin(); it != SYS.end(); ++it) {
				vector<double> d_scores, s_scores;
		    	TESTBED::get_seg_doc_scores(SEG[it->first], 0, TGT, d_scores, s_scores);
				string pref = prefix + NGRAM::NGRAMEXT+"-"+it->first;
				sc_asiya.write_report(TGT, REF, pref, it->second, d_scores, s_scores);
				fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());

				hOQ.save_hash_scores(pref, TGT, REF, it->second, d_scores, s_scores);
		        if (Config::serialize) hOQ.save_struct_scores(TB_FORMAT::make_serial(NGRAM::NGRAMEXT, TGT, REF));
			}
	    }
	}
}

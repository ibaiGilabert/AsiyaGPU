#include "../include/CE.hpp"
#include "../include/SP.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string CE::CEEXT = Common::CE;
const string CE::BIDICT_SEPARATOR = "\\|";	// quotemeta("|");

const int CE::BIDICT_MAX_NGRAM_LENGTH = 5;

const string CE::LM_path = "srilm";
const string CE::LM_ext = "LM";
const string CE::lm_ext = "lm";
const string CE::raw = "raw";
const string CE::pos = "pos";
const string CE::chunk = "chunk";

set<string> CE::create_rCE() {
	set<string> rCE;
	rCE.insert(CE::CEEXT+"-srclen");		rCE.insert(CE::CEEXT+"-srclogp");	rCE.insert(CE::CEEXT+"-srcippl");
	rCE.insert(CE::CEEXT+"-srcoov");		rCE.insert(CE::CEEXT+"-logp");		rCE.insert(CE::CEEXT+"-ippl");
	rCE.insert(CE::CEEXT+"-oov");
	rCE.insert(CE::CEEXT+"-srclogpP");		rCE.insert(CE::CEEXT+"-srcipplP");	rCE.insert(CE::CEEXT+"-logpP");		rCE.insert(CE::CEEXT+"-ipplP");
	rCE.insert(CE::CEEXT+"-srclogpC");		rCE.insert(CE::CEEXT+"-srcipplC");	rCE.insert(CE::CEEXT+"-logpC");		rCE.insert(CE::CEEXT+"-ipplC");
	rCE.insert(CE::CEEXT+"-length");		rCE.insert(CE::CEEXT+"-long");		rCE.insert(CE::CEEXT+"-short");
	rCE.insert(CE::CEEXT+"-symbols");		rCE.insert(CE::CEEXT+"-Op");		rCE.insert(CE::CEEXT+"-Oc");
	rCE.insert(CE::CEEXT+"-Nc");			rCE.insert(CE::CEEXT+"-Oe");		rCE.insert(CE::CEEXT+"-Ne");
	rCE.insert(CE::CEEXT+"-BiDictA");		rCE.insert(CE::CEEXT+"-BiDictO");
	return rCE;
}
const set<string> CE::rCE = create_rCE();


set<string> CE::create_srcENG() {
	set<string> srcENG;
	srcENG.insert(CE::CEEXT+"-srclen");
	srcENG.insert(CE::CEEXT+"-srclogp");		srcENG.insert(CE::CEEXT+"-srcippl");		srcENG.insert(CE::CEEXT+"-srcoov");
	srcENG.insert(CE::CEEXT+"-srclogpP");		srcENG.insert(CE::CEEXT+"-srcipplP");
	srcENG.insert(CE::CEEXT+"-srclogpC");		srcENG.insert(CE::CEEXT+"-srcipplC");
	srcENG.insert(CE::CEEXT+"-BiDictA");
	return srcENG;
}
const set<string> CE::srcENG = create_srcENG();


set<string> CE::create_trgENG() {
	set<string> trgENG;
	trgENG.insert(CE::CEEXT+"-logp");	trgENG.insert(CE::CEEXT+"-ippl");	trgENG.insert(CE::CEEXT+"-oov");
	trgENG.insert(CE::CEEXT+"-logpP");	trgENG.insert(CE::CEEXT+"-ipplP");
	trgENG.insert(CE::CEEXT+"-logpC");	trgENG.insert(CE::CEEXT+"-ipplC");
	return trgENG;
}
const set<string> CE::trgENG = create_trgENG();


set<string> CE::create_notENGSPA() {
	set<string> notENGSPA;
	notENGSPA.insert(CE::CEEXT+"-length");	notENGSPA.insert(CE::CEEXT+"-long");	notENGSPA.insert(CE::CEEXT+"-short");	notENGSPA.insert(CE::CEEXT+"-symbols");
	notENGSPA.insert(CE::CEEXT+"-Op");		notENGSPA.insert(CE::CEEXT+"-Oc");		notENGSPA.insert(CE::CEEXT+"-Nc");		notENGSPA.insert(CE::CEEXT+"-Oe");	
	notENGSPA.insert(CE::CEEXT+"-Ne");
	return notENGSPA;
}
const set<string> CE::notENGSPA = create_notENGSPA();


set<string> CE::create_anyLANG() {
	set<string> any_LANG;
	any_LANG.insert(CE::CEEXT+"-length");	any_LANG.insert(CE::CEEXT+"-long");	any_LANG.insert(CE::CEEXT+"-short");	any_LANG.insert(CE::CEEXT+"-symbols");
	return any_LANG;
}
const set<string> CE::anyLANG = create_anyLANG();


set<string> CE::create_rPUNCT() {
	set<string> rPUNCT;
	rPUNCT.insert(".");	 rPUNCT.insert(",");	rPUNCT.insert("!");	rPUNCT.insert("?");	rPUNCT.insert("\'"); rPUNCT.insert("\""); rPUNCT.insert("("); rPUNCT.insert(")");
	rPUNCT.insert("[");	 rPUNCT.insert("]");	rPUNCT.insert("{");	rPUNCT.insert("}");	rPUNCT.insert("$");	 rPUNCT.insert("%"); rPUNCT.insert("&");  rPUNCT.insert("/");
	rPUNCT.insert("\\"); rPUNCT.insert("=");	rPUNCT.insert("*");	rPUNCT.insert("-");	rPUNCT.insert("_");  rPUNCT.insert("|"); rPUNCT.insert("<");  rPUNCT.insert(">");
	rPUNCT.insert("@");	 rPUNCT.insert("€");	rPUNCT.insert("#");
	rPUNCT.insert("\x00A3");	// pound
	rPUNCT.insert("\x0060");	rPUNCT.insert("\x00B4");	rPUNCT.insert("\x20""18");	rPUNCT.insert("\x20""19");	rPUNCT.insert("\x02""BC");	// apostrophe
	rPUNCT.insert("\x00AB");	rPUNCT.insert("\x00BB");	rPUNCT.insert("\x20""1C");	rPUNCT.insert("\x20""1D"); 	// quotation
	rPUNCT.insert("\x002D");	rPUNCT.insert("\x20""10");	rPUNCT.insert("\x20""11");	rPUNCT.insert("\x20""12");
	rPUNCT.insert("\x20""13");	rPUNCT.insert("\x20""14");	rPUNCT.insert("\x20""15");	rPUNCT.insert("\x20""7B");
	rPUNCT.insert("\x20""8B");	rPUNCT.insert("\x22""12");	// hyphen
	rPUNCT.insert("\x20""26");	// three dots
	return rPUNCT;
}
const set<string> CE::rPUNCT = create_rPUNCT();


map<string, string> CE::create_rBIDICT() {
	map<string, string> rBIDICT;
	rBIDICT[Common::L_ENG+"-"+Common::L_SPA] = "apertium-dicts/en-es.dict";
	rBIDICT[Common::L_SPA+"-"+Common::L_ENG] = "apertium-dicts/es-en.dict";
	return rBIDICT;
}
const map<string, string> CE::rBIDICT = create_rBIDICT();


map<string, map<string, double> > CE::create_length_factor() {
	map<string, map<string, double> > length_factor;
	length_factor[Common::L_CAT][Common::L_SPA] = ((double)65748722 / 68494845);
	length_factor[Common::L_ENG][Common::L_SPA] = ((double)272396865 / 244144301);
	return length_factor;
}
const map<string, map<string, double> > CE::length_factor = create_length_factor();

map<string, map<string, string> > CE::create_LM_name() {
	map<string, map<string, string> > LM_name;
	map<string, string> LM_name_eng, LM_name_spa;

	LM_name_eng[CE::raw] = "europarl-v5";
	LM_name_eng[CE::pos] = "europarl-v5";
	LM_name_eng[CE::chunk] = "europarl-v5";
	LM_name[Common::L_ENG] = LM_name_eng;

	LM_name_spa[CE::raw] = "europarl-v5";
	LM_name_spa[CE::pos] = "europarl-v5";
	LM_name_spa[CE::chunk] = "europarl-v5";
	LM_name[Common::L_SPA] = LM_name_spa;
	return LM_name;
}
map<string, map<string, string> > CE::LM_name = create_LM_name();


/*
    my $src = $config->{src};                    # source file 
    my $remakeREPORTS = $config->{remake};       # remake reports? (1 - yes :: 0 - no)
    my $tools = $config->{tools};                # TOOL directory
    my $SRCLANG = $config->{SRCLANG};            # source language
    my $TRGLANG = $config->{LANG};               # target language
    my $SRCCASE = $config->{SRCCASE};            # source case
    my $TRGCASE = $config->{CASE};               # target case
    my $M = $config->{Hmetrics};                 # set of metrics
    my $verbose = $config->{verbose};            # verbosity (0/1)
    my $debug = $config->{debug};                # verbosity (0/1)
    my $IDX = $config->{IDX};                    # sys-doc-seg index structure
    my $SRCparser = $config->{SRCparser};        # source-language shallow parser (object)
    my $TRGparser = $config->{parser};           # target-language shallow parser (object)
*/
//my ($SYS, $SEGS) = CE::compute_language_modeling_features($src, $SRCLANG, $SRCCASE, $tools, $CE::raw, $debug);


void CE::compute_language_modeling_features(string file, string lang, string cs, string variant, double &SYSoov, double &SYSlogp, double &SYSippl, vector<double> &SEGSoov, vector<double> &SEGSlogp, vector<double> &SEGSippl) {
	// description _ compute language modeling features (logp, inverse perplexity and oov proportion)
	//               variants -> (raw, pos, chunk) according to the type of linguistic units
	srand(time(NULL));
	double nr = rand() % (Common::NRAND + 1);
	stringstream ss_tmp_out;	ss_tmp_out << file << "." << CE::LM_ext << "." << nr;
	string tmp_out = ss_tmp_out.str();

	map<string, string> lm_name_lang = LM_name[lang];
	if (lm_name_lang.find(variant) != lm_name_lang.end()) {
		if (variant == CE::raw) {
			string exe = "ngram -lm "+Config::tools+"/"+CE::LM_path+"/"+lang+"/"+cs+"/"+lm_name_lang[variant]+"."+CE::lm_ext+" -debug 1"+((cs == Common::CASE_CI) ? " -tolower" : "") + " -ppl "+file+" > "+tmp_out+" 2> /dev/null";
			Common::execute_or_die(exe, "[ERROR] SRILM - language modeling toolkit not available!!");
		} 
		else {
			string exe = "ngram -lm "+Config::tools+"/"+LM_path+"/"+lang+"/"+lm_name_lang[variant]+"."+variant+"."+CE::lm_ext+" -debug 1 -ppl "+file+" > "+tmp_out+" 2> /dev/null";
			Common::execute_or_die(exe, "[ERROR] SRILM - language modeling toolkit not available!!");
		}
	}
	else { fprintf(stderr, "[ERROR] unavailable language model for language <%s> - variant <%s>!!\n", lang.c_str(), variant.c_str()); exit(1); }

	//vector<double> SEGoov, SEGlogp, SEGippl;
	double SUMoov = 0, SUMlogp = 0, SUMippl = 0;

	ifstream tmp_out_file(tmp_out.c_str());
    if (!tmp_out_file.is_open()) { fprintf(stderr, "couldn't open output file: %s\n", tmp_out.c_str()); exit(1); }

	ifstream in_file(file.c_str());
	if (in_file) {
		string str;
		while ( getline(in_file, str) ) {
			while(str.empty()) {
				SEGSoov.push_back(0);
				SEGSlogp.push_back(0);
				SEGSippl.push_back(0);
				getline(in_file, str);
			}
			string source, info, scores, padding;
			getline(tmp_out_file, source);
			getline(tmp_out_file, info);
			getline(tmp_out_file, scores);
			getline(tmp_out_file, padding);
			vector<string> l_info, l_scores;
			
			boost::split(l_info, info, boost::is_any_of("\t "));
			int num_words = atoi(l_info[2].c_str());
			int num_oov = atoi(l_info[4].c_str());
			double oov = 1 - Common::safe_division(num_oov, num_words);
			
			boost::split(l_scores, scores, boost::is_any_of("\t "));
			int logp = atoi(l_scores[3].c_str());
			int ppl = atoi(l_scores[5].c_str());
			double ippl = 1 / ppl;
			if (Config::verbose) {
				fprintf(stderr, "source: %s\n", source.c_str());

				fprintf(stderr, "oov = 1 - %d / %d = %f\n", num_oov, num_words, oov);
				fprintf(stderr, "logp = %d\n", logp);
				fprintf(stderr, "ippl = 1 / %d = %f\n", ppl, ippl);
			}
			SUMoov += oov;
			SUMlogp += logp;
			SUMippl += ippl;
			SEGSoov.push_back(oov);
			SEGSlogp.push_back(logp);
			SEGSippl.push_back(ippl);
		}
		tmp_out_file.close();
		in_file.close();
	}
	else { fprintf(stderr, "Couldn't open input file: %s\n", file.c_str()); exit(1); }

	string sys_aux = "rm -rf "+tmp_out;
	system(sys_aux.c_str());

	SYSoov = Common::safe_division(SUMoov, SEGSoov.size());
	SYSlogp = Common::safe_division(SUMlogp, SEGSlogp.size());
	SYSippl = Common::safe_division(SUMippl, SEGSippl.size());

	//SYS["oov"] = SEGoov;
	//SYS["logp"] = SEGlogp;
	//SYS["ippl"] = SEGippl
}

void CE::computeCE_segment_length(double &SYS, vector<double> &SEGS) {
	// description _ computes segment length scores   (no references)
	double SUM;
	ifstream F(TESTBED::src.c_str());
    if (F) {
        string line;
        while (getline(F, line)) {
			vector<string> l;
		    istringstream buf(line);
		    for(string token; getline(buf, token, ' '); ) l.push_back(token);

		    double SEGscore = Common::safe_division(1, l.size());
			if (Config::verbose) fprintf(stderr, "score = 1 / %d = %f\n", (int)l.size(), SEGscore);
            SUM += SEGscore;
            SEGS.push_back(SEGscore);
        }
        F.close();
    } else { fprintf(stderr, "Couldn't open input file: %s\n", TESTBED::src.c_str());  exit(1); }

    SYS = Common::safe_division(SUM, SEGS.size());
}


void CE::doMetric(string TGT, string REF, string prefix, int stemming, Scores &hOQ) {
	// description _ computes CE scores   (no references)

	//map<string, int> M = Config::Hmetrics;
	vector<string> mCE(CE::rCE.size());

	int GO, i;
	GO = i = 0;
	for (set<string>::const_iterator it = CE::rCE.begin(); it != CE::rCE.end(); ++it, ++i)
		mCE[i] = *it;
	for (i = 0; i < mCE.size() and !GO; ++i) {
		//string aux = prefix + mCE[i];
		if (Config::Hmetrics.find(prefix+mCE[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s\n", CE::CEEXT.c_str());
		
		SC_ASIYA sc_asiya;
		SP sp;

		stringstream ssReportCEsrclen;
		ssReportCEsrclen << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclen." << Common::XMLEXT;
		string reportCEsrclenXML = ssReportCEsrclen.str();
	    
		// TRANSLATION DIFFICULTY ###
       	// LENGTH
	    string ce_srclen = CE::CEEXT + "-srclen";
	    if ( ((!exists(boost::filesystem::path(reportCEsrclenXML)) and !exists(boost::filesystem::path(reportCEsrclenXML+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[ce_srclen] ) {	//source length ratio
	    	double sys_score;
	    	vector<double> SEGS, doc_scores, seg_scores;
	    	
	    	computeCE_segment_length(sys_score, SEGS);
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, doc_scores, seg_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, ce_srclen, sys_score, doc_scores, seg_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", ce_srclen.c_str());
         	}
         	hOQ.save_hash_scores(ce_srclen, TGT, REF, sys_score, doc_scores, seg_scores);
	    }

	    // LANGUAGE MODELING
	    stringstream ssReportCEsrclogp, ssReportCEsrcippl, ssReportCEsrcoov;
		ssReportCEsrclogp << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclogp." << Common::XMLEXT;
		ssReportCEsrcippl << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcippl." << Common::XMLEXT;
		ssReportCEsrcoov << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcoov." << Common::XMLEXT;
		string reportCEsrclogpXML = ssReportCEsrclogp.str();
		string reportCEsrcipplXML = ssReportCEsrcippl.str();
		string reportCEsrcoovXML = ssReportCEsrcoov.str();

	    if (((!exists(boost::filesystem::path(reportCEsrclogpXML)) and !exists(boost::filesystem::path(reportCEsrclogpXML+"."+Common::GZEXT))) or
	    	 (!exists(boost::filesystem::path(reportCEsrcipplXML)) and !exists(boost::filesystem::path(reportCEsrcipplXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEsrcoovXML)) and !exists(boost::filesystem::path(reportCEsrcoovXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-srclogp"] or Config::Hmetrics[CE::CEEXT+"-srcippl"] or Config::Hmetrics[CE::CEEXT+"-srcoov"])) {	//source language modeling

	    	double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(TESTBED::src, Config::SRCLANG, Config::SRCCASE, CE::raw, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);

	    	// log probabilities
	    	string pref = CE::CEEXT+"-srclogp";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-srcippl";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);

         	// proportion of Out-of-vocabulary (oov) tokens
			pref = CE::CEEXT+"-srclogp";
	    	TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);
	    }

	    stringstream reportCEsrclogp_pos, reportCEsrcippl_pos;
	    reportCEsrclogp_pos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclogpP." << Common::XMLEXT;
		reportCEsrcippl_pos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcipplP." << Common::XMLEXT;
		string reportCEsrclogp_posXML = reportCEsrclogp_pos.str();
		string reportCEsrcippl_posXML = reportCEsrcippl_pos.str();

	    if (((!exists(boost::filesystem::path(reportCEsrclogp_posXML)) and !exists(boost::filesystem::path(reportCEsrclogp_posXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEsrcippl_posXML)) and !exists(boost::filesystem::path(reportCEsrcippl_posXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-srclogpP"] or Config::Hmetrics[CE::CEEXT+"-srcipplP"])) {	//source PoS language modeling

	    	string src_posfile = sp.create_PoS_file(TESTBED::src, Config::SRCLANG, Config::SRCCASE);
			double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(src_posfile, Config::SRCLANG, Config::SRCCASE, CE::pos, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);
	    	string sys_aux = Common::GZIP+" "+src_posfile;	system(sys_aux.c_str());

	    	// log probabilities
	    	string pref = CE::CEEXT+"-srclogpP";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-srcipplP";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);
		}

	    stringstream reportCEsrclogp_chunk, reportCEsrcippl_chunk;
	    reportCEsrclogp_chunk << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srclogpC." << Common::XMLEXT;
		reportCEsrcippl_chunk << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-srcipplC." << Common::XMLEXT;
		string reportCEsrclogp_chunkXML = reportCEsrclogp_chunk.str();
		string reportCEsrcippl_chunkXML = reportCEsrcippl_chunk.str();

	    if (((!exists(boost::filesystem::path(reportCEsrclogp_chunkXML)) and !exists(boost::filesystem::path(reportCEsrclogp_chunkXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEsrcippl_chunkXML)) and !exists(boost::filesystem::path(reportCEsrcippl_chunkXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-srclogpC"] or Config::Hmetrics[CE::CEEXT+"-srcipplC"])) {	//source Chunk language modeling

	    	string src_chunkfile = sp.create_chunk_file(TESTBED::src, Config::SRCLANG, Config::SRCCASE);
			double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(src_chunkfile, Config::SRCLANG, Config::SRCCASE, CE::chunk, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);
	    	string sys_aux = Common::GZIP+" "+src_chunkfile;	system(sys_aux.c_str());

	    	// log probabilities
	    	string pref = CE::CEEXT+"-srclogpC";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-srcipplC";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);

		}
       // FLUENCY ###
       // LANGUAGE MODELING



	}
}
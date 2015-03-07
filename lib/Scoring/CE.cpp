#include "../include/CE.hpp"
#include "../include/SP.hpp"
#include "../include/Overlap.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

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
map<string, string> CE::rBIDICT = create_rBIDICT();


map<string, map<string, double> > CE::create_length_factor() {
	map<string, map<string, double> > length_factor;
	length_factor[Common::L_CAT][Common::L_SPA] = ((double)65748722 / 68494845);
	length_factor[Common::L_ENG][Common::L_SPA] = ((double)272396865 / 244144301);
	return length_factor;
}
map<string, map<string, double> > CE::length_factor = create_length_factor();

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

void CE::load_bidict(string source_lang, string target_lang, map<string, map<string, int> > &bidict) {
	// description _ load bilingual dictionary (according to the given language pair) if available
	string dict_aux = source_lang+"-"+target_lang;

	if (CE::rBIDICT.find(dict_aux) != CE::rBIDICT.end()) {
		string bidict_path = Config::tools + "/" + CE::rBIDICT[dict_aux];

		ifstream bidict_file(bidict_path.c_str());
		if (bidict_file) {
			string str;
			while( getline(bidict_file, str) ) {
				vector<string> elems;
				boost::split(elems, str, boost::is_any_of(CE::BIDICT_SEPARATOR));
				if (elems.size() == 2) {
					string source = elems[0];
					string target = elems[1];
			        boost::to_lower(source);
			        boost::to_lower(target);
			        if (target != "prpers" and target != "pn000")
			        	++bidict[source][target];
				}
			}
			bidict_file.close();
		} 
		else { fprintf(stderr, "Couldn't open input file: %s\n", bidict_path.c_str()); exit(1); }
	}
}

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
			double ippl = 1. / ppl;
			/*if (Config::verbose) {
				fprintf(stderr, "source: %s\n", source.c_str());

				fprintf(stderr, "oov = 1 - %d / %d = %f\n", num_oov, num_words, oov);
				fprintf(stderr, "logp = %d\n", logp);
				fprintf(stderr, "ippl = 1 / %d = %f\n", ppl, ippl);
			}*/
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

void CE::computeCE_segment_length_ratio(string source, string target, double &length_score, double &long_score, double &short_score) {
	// description _ compute segment length ratio (three variants: 'length', 'long', 'short')
	vector<string> source_tokens, target_tokens;
	boost::split(source_tokens, source, boost::is_any_of("\t "));
	boost::split(target_tokens, target, boost::is_any_of("\t "));
	int source_length = source_tokens.size();
	int target_length = target_tokens.size();

	double compression_factor = 1;	// aimed at compensating for difference in length inherent ot the language pair
	if (CE::length_factor[Config::SRCLANG].find(Config::LANG) != CE::length_factor[Config::SRCLANG].end())
		compression_factor = CE::length_factor[Config::SRCLANG][Config::LANG];
	else if (CE::length_factor[Config::LANG].find(Config::SRCLANG) != CE::length_factor[Config::LANG].end())
		compression_factor = 1 / CE::length_factor[Config::LANG][Config::SRCLANG];

	double numerator_length = min(source_length * compression_factor, (double)target_length);
	double denominator_length = max(source_length * compression_factor, (double)target_length);
	length_score = Common::safe_division(numerator_length, denominator_length);

	double numerator_long = source_length * compression_factor;
	double denominator_long = max(source_length * compression_factor, (double)target_length);
	long_score = Common::safe_division(numerator_long, denominator_long);

	double numerator_short = target_length;
	double denominator_short = max(source_length * compression_factor, (double)target_length);
	short_score = Common::safe_division(numerator_short, denominator_short);

	if (Config::verbose) {
		fprintf(stderr, "source length = %d\n", source_length);
		fprintf(stderr, "target length = %d\n", target_length);
		fprintf(stderr, "length(source, target) = %f / %f = %f\n", numerator_length, denominator_length, length_score);
		fprintf(stderr, "long(source, target) = %f / %f = %f\n", numerator_long, denominator_long, long_score);
		fprintf(stderr, "short(source, target) = %f / %f = %f\n", numerator_short, denominator_short, short_score);
	}
}

void CE::computeCE_length_ratio(string TGT, double &SYSlength, double &SYSlong, double &SYSshort, vector<double> &SEGSlength, vector<double> &SEGSlong, vector<double> &SEGSshort) {
	// description _ computes length ratio scores (three variants: 'length', 'long', 'short')   (no references)
	double SUMlength = 0, SUMlong = 0, SUMshort = 0;

	ifstream out_file(TESTBED::Hsystems[TGT].c_str());
    if (!out_file.is_open()) { fprintf(stderr, "couldn't open input file: %s\n", TESTBED::Hsystems[TGT].c_str()); exit(1); }

	ifstream src_file(TESTBED::src.c_str());
	if (src_file) {
		bool STOP = false;

		string str1, str2;
		while( getline(src_file, str1) and !STOP) {
			double slength = 0, slong = 0, sshort = 0;
			if ( getline(out_file, str2) ) {
				computeCE_segment_length_ratio(str1, str2, slength, slong, sshort);

				SUMlength += slength;
				SUMlong += slong;
				SUMshort += sshort;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs. <%s>\n", TESTBED::src.c_str(), TESTBED::Hsystems[TGT].c_str()); STOP = true; }
			SEGSlength.push_back(slength);
			SEGSlong.push_back(slong);
			SEGSshort.push_back(sshort);
		}
		src_file.close();
		out_file.close();
	} else { fprintf(stderr, "Couldn't open input file: %s\n", TESTBED::src.c_str());  exit(1); }

	SYSlength = Common::safe_division(SUMlength, SEGSlength.size());
	SYSlong = Common::safe_division(SUMlong, SEGSlong.size());
	SYSshort = Common::safe_division(SUMshort, SEGSshort.size());
}

map<string, int> CE::extract_symbol_set(string text) {
	// description _ extract set of symbols in tex
	vector<string> tokens;
	boost::split(tokens, text, boost::is_any_of("\t "));

	map<string, int> symbol_set;
	for (int i = 0; i < tokens.size(); ++i) {
		if (CE::rPUNCT.find(tokens[i]) != rPUNCT.end() or isdigit(atoi(tokens[i].c_str())))
			++symbol_set[tokens[i]];
	}

	return symbol_set;
}

double CE::computeCE_segment_symbol_overlap(string source, string target) {
	// description _ compute segment symbol overlap between source and target
	map<string, int> source_symbols = extract_symbol_set(source);
	map<string, int> target_symbols = extract_symbol_set(target);

	Overlap Ov;
	pair<double, double> hits_total = Ov.compute_overlap(source_symbols, target_symbols, 0);

	double score = Common::safe_division(hits_total.first, hits_total.second);

	if (Config::verbose) {
		fprintf(stderr, "source = %s\n", source.c_str());
		for (map<string, int>::const_iterator it = source_symbols.begin(); it != source_symbols.end(); ++it)
			fprintf(stderr, "[%s -> %d]\n", it->first.c_str(), it->second);
		fprintf(stderr, "target = %s\n", target.c_str());
		for (map<string, int>::const_iterator it = target_symbols.begin(); it != target_symbols.end(); ++it)
			fprintf(stderr, "[%s -> %d]\n", it->first.c_str(), it->second);
		fprintf(stderr, "OVERLAP = %f / %f = %f\n", hits_total.first, hits_total.second, score);
	}

	return score;
}


void CE::computeCE_symbols_overlap(string TGT, double &SYS, vector<double> &SEGS) {
	// description _ computes symbol overlap scores   (no references)
	//               (pending: make it language dependent? because the use of punctuation symbols may vary between languages)
	double SUM = 0;

	ifstream out_file(TESTBED::Hsystems[TGT].c_str());
    if (!out_file.is_open()) { fprintf(stderr, "couldn't open input file: %s\n", TESTBED::Hsystems[TGT].c_str()); exit(1); }

	ifstream src_file(TESTBED::src.c_str());
	if (src_file) {
		bool STOP = false;

		string str1, str2;
		while( getline(src_file, str1) and !STOP) {
			double SEGscore = 0;
			if ( getline(out_file, str2) ) {
				SEGscore = computeCE_segment_symbol_overlap(str1, str2);

				SUM += SEGscore;
			}
			else { fprintf(stderr, "[ERROR] number of lines differs <%s> Vs. <%s>\n", TESTBED::src.c_str(), TESTBED::Hsystems[TGT].c_str()); STOP = true; }
			SEGS.push_back(SEGscore);
		}
		src_file.close();
		out_file.close();
	} else { fprintf(stderr, "Couldn't open input file: %s\n", TESTBED::src.c_str());  exit(1); }

	if (SEGS.size() > 0)
		SYS = SUM / SEGS.size();
	else 
		SYS = 0;
}

void CE::merge_ngrams(map<string, int> &ngrams1, map<string, int> &ngrams2) {
	// description _ merge two ngram sets (adding counts) into the first
	for(map<string, int>::iterator it = ngrams2.begin(); it != ngrams2.end(); ++it) {
		if (ngrams1.find(it->first) != ngrams1.end())
			ngrams1[it->first] += it->second;
		else
			ngrams1[it->first] = it->second;
	}
}

void CE::retrieve_mixed_ngrams(const vector<string> &tokens, const vector<string> &lemmas, int length, map<string, int> &ngrams) {
	// description _ retrieve all mixed ngrams (in the two sequences) up to a given length
	if (length < 1) length = 1;

	set<string> window;
	for (int i = 0; i < tokens.size(); ++i) {
		string token = tokens[i];	boost::to_lower(token);
		string lemma = lemmas[i];	boost::to_lower(lemma);
		if (length == 1) {
			++ngrams[token];
			if (lemma != token) ++ngrams[lemma];
		}
		else {
			if (i < length) {
				if (window.size() == 0) {	// empty window
					window.insert(token);
					if (lemma != token) window.insert(lemma);
					if (i == length - 1) {
						++ngrams[token];
						if (lemma != token) ++ngrams[lemma];
					}
				}
				else {
					for (set<string>::iterator it = window.begin(); it != window.end(); ++it) {
						string trim_tok = *it + " " + token;
						string trim_lem = *it + " " + lemma;
						window.erase(it);
						window.insert(trim_tok);
						if (lemma != token) window.insert(trim_lem);
						if (i == length-1) {
							++ngrams[trim_tok];
							if (lemma != token) ++ngrams[trim_lem];
						}
					}
				}
			}
			else {
				for (set<string>::iterator it = window.begin(); it != window.end(); ++it) {
					vector<string> lgram;
					boost::split(lgram, *it, boost::is_any_of("\t "));
					lgram.erase(lgram.begin());
					string new_ngram;
					if (lgram.size() > 0) { new_ngram = lgram[0]; for (int i = 1; i < lgram.size(); ++i) new_ngram = new_ngram + " " + lgram[i]; }

					string trim_new_tok = new_ngram + " " + token;
					string trim_new_lemma = new_ngram + " " + lemma;
					window.insert(trim_new_tok);
					++ngrams[trim_new_tok];
					if (lemma != token) {
						window.insert(trim_new_lemma);
						++ngrams[trim_new_lemma];
					}
				}
			}
		}
	}
}

void CE::retrieve_all_mixed_ngrams(const vector<string> &tokens, const vector<string> &lemmas, map<string, int> ngrams) {
	// description _ retrieve all mixed ngrams (in the two sequences) of any length
	for (int i = 1; i <= tokens.size() and i <= CE::BIDICT_MAX_NGRAM_LENGTH; ++i) {
		map<string, int> i_ngrams;
		retrieve_mixed_ngrams(tokens, lemmas, i, i_ngrams);
		merge_ngrams(ngrams, i_ngrams);
	}
}

pair<int, int> CE::computeCE_bidict_segment_ambiguity(string segment, string lemma_segment, map<string, map<string, int> > &bidict) {
	// description _ computes segment ambiguity scores   (no references)
	vector<string> tokens, lemmas;
	boost::split(tokens, segment, boost::is_any_of("\t "));
	boost::split(lemmas, lemma_segment, boost::is_any_of("\t "));

	if (tokens.size() != lemmas.size()) { fprintf(stderr, "[ERROR] number of tokens and lemmas differ (%d) Vs. (%d)!!\n", (int)tokens.size(), (int)lemmas.size()); exit(1); }

	map<string, int> ngrams;
	retrieve_all_mixed_ngrams(tokens, lemmas, ngrams);

	int n = 0, total = 0;

	for(map<string, int>::const_iterator it = ngrams.begin(); it != ngrams.end(); ++it) {
		if (bidict.find(it->first) != bidict.end()) {
			//int n_occurrences = it->second;
			//int n_translations = bidict[it->first].size();
			n += it->second * bidict[it->first].size();
			total += it->second;
			if (Config::verbose) fprintf(stderr, "%s --> %s :: #occurrences = %d :: #translations = %d\n", it->first.c_str(), it->first.c_str(), it->second, (int)bidict[it->first].size());
		}
	}
}

void CE::computeCE_bidict_ambiguity(string lemma, map<string, map<string, int> > &bidict, double &SYS, vector<double> &SEGS) {
	// description _ computes segment ambiguity scores   (no references)
	double SUM = 0;

	ifstream lemma_file(lemma.c_str());
    if (!lemma_file.is_open()) { fprintf(stderr, "couldn't open input file: %s\n", lemma.c_str()); exit(1); }

	ifstream src_file(TESTBED::src.c_str());
	if (src_file) {
		string segment;
		while( getline(src_file, segment) ) {
			string lemma_segment;
			if ( getline(lemma_file, lemma_segment) ) {
				if (Config::verbose) printf("tokens = %s\nlemmas = %s\n", segment.c_str(), lemma_segment.c_str());

				pair<int, int> n_total = computeCE_bidict_segment_ambiguity(segment, lemma_segment, bidict);
				double ambiguity = Common::safe_division(n_total.first, n_total.second);
				double SEGscore = Common::safe_division(1, ambiguity);
				if (Config::verbose) fprintf(stderr, "score = 1 / %f = %f\n", ambiguity, SEGscore);
				
				SUM += SEGscore;
				SEGS.push_back(SEGscore);
			}
		}
		lemma_file.close();
		src_file.close();
	}
	else { fprintf(stderr, "couldn't open input file: %s\n", TESTBED::src.c_str()); exit(1); }

	SYS = Common::safe_division(SUM, SEGS.size());
}

void CE::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
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
	    		sc_asiya.write_report(TGT, CE::CEEXT, ce_srclen, sys_score, doc_scores, seg_scores);
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
			pref = CE::CEEXT+"-srcoov";
	    	TESTBED::get_seg_doc_scores(SEGSoov, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSoov, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSoov, d_scores, s_scores);
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
	    stringstream reportCElogp, reportCEippl, reportCEoov;
	    reportCElogp << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-logp." << Common::XMLEXT;
		reportCEippl << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-ippl." << Common::XMLEXT;
		reportCEoov << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-oov." << Common::XMLEXT;
		string reportCElogpXML = reportCElogp.str();
		string reportCEipplXML = reportCEippl.str();
		string reportCEoovXML = reportCEoov.str();

	    if (((!exists(boost::filesystem::path(reportCElogpXML)) and !exists(boost::filesystem::path(reportCElogpXML+"."+Common::GZEXT))) or
	    	 (!exists(boost::filesystem::path(reportCEipplXML)) and !exists(boost::filesystem::path(reportCEipplXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEoovXML)) and !exists(boost::filesystem::path(reportCEoovXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-logp"] or Config::Hmetrics[CE::CEEXT+"-ippl"] or Config::Hmetrics[CE::CEEXT+"-oov"])) {	// target language modeling

	    	double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, CE::raw, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);

	    	// log probabilities
	    	string pref = CE::CEEXT+"-logp";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-ippl";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);

         	// proportion of Out-of-vocabulary (oov) tokens
			pref = CE::CEEXT+"-oov";
	    	TESTBED::get_seg_doc_scores(SEGSoov, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSoov, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSoov, d_scores, s_scores);
        }

		stringstream reportCElogp_pos, reportCEippl_pos;
	    reportCElogp_pos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-logpP." << Common::XMLEXT;
		reportCEippl_pos << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-ipplP." << Common::XMLEXT;
		string reportCElogp_posXML = reportCElogp_pos.str();
		string reportCEippl_posXML = reportCEippl_pos.str();

	    if (((!exists(boost::filesystem::path(reportCElogp_posXML)) and !exists(boost::filesystem::path(reportCElogp_posXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEippl_posXML)) and !exists(boost::filesystem::path(reportCEippl_posXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-logpP"] or Config::Hmetrics[CE::CEEXT+"-ipplP"])) {	//source PoS language modeling

	    	string out_posfile = sp.create_PoS_file(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE);
			double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(out_posfile, Config::LANG, Config::CASE, CE::pos, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);
	    	string sys_aux = Common::GZIP+" "+out_posfile;	system(sys_aux.c_str());

	    	// log probabilities
	    	string pref = CE::CEEXT+"-logpP";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-ipplP";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);
		}

	    stringstream reportCElogp_chunk, reportCEippl_chunk;
	    reportCElogp_chunk << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-logpC." << Common::XMLEXT;
		reportCEippl_chunk << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-ipplC." << Common::XMLEXT;
		string reportCElogp_chunkXML = reportCElogp_chunk.str();
		string reportCEippl_chunkXML = reportCEippl_chunk.str();

	    if (((!exists(boost::filesystem::path(reportCElogp_chunkXML)) and !exists(boost::filesystem::path(reportCElogp_chunkXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEippl_chunkXML)) and !exists(boost::filesystem::path(reportCEippl_chunkXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-logpC"] or Config::Hmetrics[CE::CEEXT+"-ipplC"])) {	//source Chunk language modeling

	    	string out_chunkfile = sp.create_chunk_file(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE);
			double SYSoov, SYSlogp, SYSippl;
	    	vector<double> SEGSoov, SEGSlogp, SEGSippl;
	    	compute_language_modeling_features(out_chunkfile, Config::LANG, Config::CASE, CE::chunk, SYSoov, SYSlogp, SYSippl, SEGSoov, SEGSlogp, SEGSippl);
	    	string sys_aux = Common::GZIP+" "+out_chunkfile;	system(sys_aux.c_str());

	    	// log probabilities
	    	string pref = CE::CEEXT+"-logpC";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlogp, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlogp, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlogp, d_scores, s_scores);

         	// inverse perplexities
			pref = CE::CEEXT+"-ipplC";
	    	TESTBED::get_seg_doc_scores(SEGSippl, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSippl, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSippl, d_scores, s_scores);
		}


       // ADEQUACY ###
       // LENGTH RATIOS
	    stringstream reportCElength, reportCElong, reportCEshort;
	    reportCElength << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-length." << Common::XMLEXT;
		reportCElong << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-long." << Common::XMLEXT;
		reportCEshort << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-short." << Common::XMLEXT;
		string reportCElengthXML = reportCElength.str();
		string reportCElongXML = reportCElong.str();
		string reportCEshortXML = reportCEshort.str();

	    if (((!exists(boost::filesystem::path(reportCElongXML)) and !exists(boost::filesystem::path(reportCElengthXML+"."+Common::GZEXT))) or
	    	 (!exists(boost::filesystem::path(reportCElongXML)) and !exists(boost::filesystem::path(reportCElongXML+"."+Common::GZEXT))) or
    		 (!exists(boost::filesystem::path(reportCEshortXML)) and !exists(boost::filesystem::path(reportCEshortXML+"."+Common::GZEXT))) or Config::remake) and
    		 (Config::Hmetrics[CE::CEEXT+"-length"] or Config::Hmetrics[CE::CEEXT+"-long"] or Config::Hmetrics[CE::CEEXT+"-short"])) {	// source / target length ratio

	    	double SYSlength, SYSlong, SYSshort;
	    	vector<double> SEGSlength, SEGSlong, SEGSshort;
	    	computeCE_length_ratio(TGT, /*TESTBED::src, TESTBED::Hsystems[out], Config::SRCLANG, Config::LANG*/ SYSlength, SYSlong, SYSshort, SEGSlength, SEGSlong, SEGSshort);

	    	// length ratio
	    	string pref = CE::CEEXT+"-length";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGSlength, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlength, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlength, d_scores, s_scores);

	    	// lengthiness ratio
	    	pref = CE::CEEXT+"-long";
	    	TESTBED::get_seg_doc_scores(SEGSlong, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSlong, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSlong, d_scores, s_scores);

	    	// shortness ratio
	    	pref = CE::CEEXT+"-short";
	    	TESTBED::get_seg_doc_scores(SEGSshort, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYSshort, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYSshort, d_scores, s_scores);
        }

        // SYMBOL OVERLAP (punctuation, numbers, ...)
	    stringstream reportCEsymbol;
	    reportCEsymbol << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-symbols." << Common::XMLEXT;
		string reportCEsymbolXML = reportCEsymbol.str();

	    if (((!exists(boost::filesystem::path(reportCEsymbolXML)) and !exists(boost::filesystem::path(reportCEsymbolXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-symbols"]) {	// source / target punctuation and numerical symbols overlap

			double SYS;
			vector<double> SEGS;
			computeCE_symbols_overlap(TGT, SYS, SEGS);

	    	string pref = CE::CEEXT+"-symbols";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}

		// Op --- PoS overlap
	    stringstream reportCE_Op;
	    reportCE_Op << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-Op" << Common::XMLEXT;
		string reportCE_OpXML = reportCE_Op.str();

	    if (((!exists(boost::filesystem::path(reportCE_OpXML)) and !exists(boost::filesystem::path(reportCE_OpXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-Op"]) {

			SP sp;
	    	Overlap ov;
			double SYS;
			vector<double> SEGS;			
			string src_posfile = sp.create_PoS_file(TESTBED::src, Config::LANG, Config::CASE);
	    	string out_posfile = sp.create_PoS_file(TESTBED::Hsystems[TGT], Config::SRCLANG, Config::SRCCASE);

			ov.computeOl(out_posfile, src_posfile, SYS, SEGS);

			string sys_aux;
			sys_aux = Common::GZIP+" "+src_posfile;	system(sys_aux.c_str());
			sys_aux = Common::GZIP+" "+out_posfile;	system(sys_aux.c_str());

	    	string pref = CE::CEEXT+"-Op";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}

		// Oc --- chunk overlap
	    stringstream reportCE_Oc;
	    reportCE_Oc << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-Oc" << Common::XMLEXT;
		string reportCE_OcXML = reportCE_Oc.str();

	    if (((!exists(boost::filesystem::path(reportCE_OcXML)) and !exists(boost::filesystem::path(reportCE_OcXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-Oc"]) {

			SP sp;
	    	Overlap ov;
			double SYS;
			vector<double> SEGS;			
			string src_chunkfile = sp.create_chunk_file(TESTBED::src, Config::LANG, Config::CASE);
	    	string out_chunkfile = sp.create_chunk_file(TESTBED::Hsystems[TGT], Config::SRCLANG, Config::SRCCASE);

			ov.computeOl(out_chunkfile, src_chunkfile, SYS, SEGS);

			string sys_aux;
			sys_aux = Common::GZIP+" "+src_chunkfile;	system(sys_aux.c_str());
			sys_aux = Common::GZIP+" "+out_chunkfile;	system(sys_aux.c_str());

	    	string pref = CE::CEEXT+"-Oc";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}

		// Nc --- chunk N ratio
	    stringstream reportCE_Nc;
	    reportCE_Nc << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-Nc" << Common::XMLEXT;
		string reportCE_NcXML = reportCE_Nc.str();

	    if (((!exists(boost::filesystem::path(reportCE_NcXML)) and !exists(boost::filesystem::path(reportCE_NcXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-Nc"]) {

			SP sp;
	    	Overlap ov;
			double SYS;
			vector<double> SEGS;			
			string src_chunkfile = sp.create_chunk_file(TESTBED::src, Config::LANG, Config::CASE);
	    	string out_chunkfile = sp.create_chunk_file(TESTBED::Hsystems[TGT], Config::SRCLANG, Config::SRCCASE);

			ov.computeOn(out_chunkfile, src_chunkfile, SYS, SEGS);

			string sys_aux;
			sys_aux = Common::GZIP+" "+src_chunkfile;	system(sys_aux.c_str());
			sys_aux = Common::GZIP+" "+out_chunkfile;	system(sys_aux.c_str());

	    	string pref = CE::CEEXT+"-Nc";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}
/*
		// Oe --- NE overlap
	    stringstream reportCE_Oe;
	    reportCE_Oe << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-Oe" << Common::XMLEXT;
		string reportCE_OeXML = reportCE_Oe.str();

	    if (((!exists(boost::filesystem::path(reportCE_OeXML)) and !exists(boost::filesystem::path(reportCE_OeXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-Oe"]) {

			NE ne;
	    	Overlap ov;
			double SYS;
			vector<double> SEGS;			
			string src_NEfile = ne.create_NE_file(TESTBED::src, Config::LANG, Config::CASE);
	    	string out_NEfile = ne.create_NE_file(TESTBED::Hsystems[TGT], Config::SRCLANG, Config::SRCCASE);

			ov.computeOl(out_NEfile, src_NEfile, SYS, SEGS);

			string sys_aux;
			sys_aux = Common::GZIP+" "+src_NEfile;	system(sys_aux.c_str());
			sys_aux = Common::GZIP+" "+out_NEfile;	system(sys_aux.c_str());

	    	string pref = CE::CEEXT+"-Oe";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}

		// Ne --- NE N ratio
	    stringstream reportCE_Ne;
	    reportCE_Ne << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-Ne" << Common::XMLEXT;
		string reportCE_NeXML = reportCE_Ne.str();

	    if (((!exists(boost::filesystem::path(reportCE_NeXML)) and !exists(boost::filesystem::path(reportCE_NeXML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-Ne"]) {

			NE ne;
	    	Overlap ov;
			double SYS;
			vector<double> SEGS;			
			string src_NEfile = ne.create_NE_file(TESTBED::src, Config::LANG, Config::CASE);
	    	string out_NEfile = ne.create_NE_file(TESTBED::Hsystems[TGT], Config::SRCLANG, Config::SRCCASE);

			ov.computeOn(out_NEfile, src_NEfile, SYS, SEGS);

			string sys_aux;
			sys_aux = Common::GZIP+" "+src_NEfile;	system(sys_aux.c_str());
			sys_aux = Common::GZIP+" "+out_NEfile;	system(sys_aux.c_str());

	    	string pref = CE::CEEXT+"-Oe";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}
*/

/*
		// --------------------------------
		// BiDictA (ambiguity)
	    stringstream reportCEBiDictA;
	    reportCEBiDictA << Common::DATA_PATH << "/" << Common::REPORTS << "/" << TGT << "/" << CE::CEEXT << "/" << CE::CEEXT << "-BiDictA" << Common::XMLEXT;
		string reportCEBiDictA_XML = reportCEBiDictA.str();

		map<string, map<string, int> > bidict;
	    if (((!exists(boost::filesystem::path(reportCEBiDictA_XML)) and !exists(boost::filesystem::path(reportCEBiDictA_XML+"."+Common::GZEXT))) or Config::remake) 
	    	and Config::Hmetrics[CE::CEEXT+"-BiDictA"]) {	// source ambiguity according to a bilingual dictionary

			load_bidict(Config::SRCLANG, Config::LANG, bidict);

			SP sp;
			string src_lemmafile = sp.create_lemma_file(TESTBED::src, Config::SRCLANG, Config::SRCCASE);
			
			double SYS;
			vector<double> SEGS;			
			computeCE_bidict_ambiguity(src_lemmafile, bidict, SYS, SEGS);

	    	string pref = CE::CEEXT+"-BiDictA";
	    	vector<double> d_scores, s_scores;
			TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
	    	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, CE::CEEXT, pref, SYS, d_scores, s_scores);
         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", pref.c_str());
         	}	
         	hOQ.save_hash_scores(pref, TGT, REF, SYS, d_scores, s_scores);
		}

		// BiDictO (overlap)
*/
	}
}
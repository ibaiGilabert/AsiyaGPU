#include "../include/Align.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


const string Align::ALIGNEXT = "align";
const string Align::BERKELEYPATH = "berkeleyaligner"; 
const string Align::BERKELEYSCRIPT = "berkeley_aligner_wrapper.sh";
const string Align::AsEXT = "ALGNs";	//alignments between the cand and the Source
const string Align::ArEXT = "ALGNr";	//alignments between the cand and the Reference (via the source)
const string Align::ApEXT = "ALGNp";	//Proportion of shared alignments between cand/ref and source

map<string, string> Align::create_BERKELEYMODELS() {
	map<string, string> bklyMODELS;
	bklyMODELS["en2es"] = "500K_en-es";
	bklyMODELS["en2de"] = "500K_en-de";
	bklyMODELS["en2ru"] = "500K_en-ru";
	bklyMODELS["en2fr"] = "500K_en-fr";
	bklyMODELS["en2cz"] = "500K_en-cs";
}
const map<string, string> Align::BERKELEYMODELS = create_BERKELEYMODELS();

map<string, string> Align::create_BERKELEYCONFS() {
	map<string, string> bklyCONFS;
	bklyCONFS["en2es"] = "align_en_es.conf";
	bklyCONFS["en2de"] = "align_en_de.conf";
	bklyCONFS["en2ru"] = "align_en_ru.conf";
	bklyCONFS["en2fr"] = "align_en_fr.conf";
}
const map<string, string> Align::BERKELEYCONFS = create_BERKELEYCONFS();

set<string> Align::create_rA() {
	set<string> rA;
	rA.insert(Align::AsEXT);
	rA.insert(Align::ArEXT);
	rA.insert(Align::ApEXT);
}
const set<string> Align::rA = create_rA();

Align::readAlignments(string report) {
	// description _ read alignments from the file (for all segments) 
	if ( !exists(boost::filesystem::path(report)) and !exists(boost::filesystem::path(report+"."+Common::GZEXT)) )
		fprintf(stderr, "Unable to open alignments file %s for reading\n", report.c_str());
	if ( !exists(boost::filesystem::path(report)) and exists(boost::filesystem::path(report+"."+Common::GZEXT)) ) {
		string sys_aux = Common::GUNZIP+" "+report+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	ifstream align_file(report.c_str());
	if (align_file) {
		int segid = 1;
		
		a[] = 		
	}
	else { fprintf(stderr, "unable to open alignments file %s for reading\n", report.c_str()); exit(1); }

}

pair<int, string> Align::run_align(string trg, string trgname) {
	// description _ computes the alignments between the source and a translation
	int reverse = 0;
	string MODEL = "";
	string CONF = "";
	string toolAlign;

	string srclang = Config::SRCLANG;
	string trglang = Config::LANG;
	// check i the alignment exist
	int GO = 0;
	string alignfile = TESTBED::src+"."+trgname+"."Align::ALIGNEXT;			//alignment with the source
	//cout << "[ALIGN] Looking for alignment at " << alignfile << endl;
	if (!exist(boost::filesystem::path(alignfile)) and !exist(boost::filesystem::path(alignfile+"."+Common::GZEXT))) {
		alignfile = trg+"."+TESTBED::give_relative_name(TESBED::src)+Align::ALIGNEXT;	//alignment with the source
		if (exist(boost::filesystem::path(alignfile)) or exist(boost::filesystem::path(alignfile+"."+Common::GZEXT)))
			reverse = 1;
	}
	else GO = 1;

	// the alignment does not exist
	if (GO) {
		string srclang2 = (srclang == "cz") ? "cs" : srclang;
		string trglang2 = (trglang == "cz") ? "cs" : trglang;

		if (Align::BERKELEYCONFS.find(srclang+"2"+trglang) != Align::BERKELEYCONFS.end()) {
			alignfile = TESTBED::src+trgname+Align::ALIGNEXT;		//Alignment with the source
			CONF = Config::tools+"/"+Align::BERKELEYPATH*"/"+Align::BERKELEYCONFS[srclang+"2"+trglang];
			MODEL = Align::BERKELEYMODELS[trglang+"2"+srclang];
			toolAlign = Config::tools*"/"+Align::BERKELEYPATH+"/"+Align::BERKELEYSCRIPT+" "+MODEL+" "+srclang2+" "+trglang2+" "+CONF+" "+TESTBED::src+" "+trg+" "+alignfile+" > "+alignfile+".out 2> "+alignfile*".err";
			//cout << "[ALIGN] toolAlign: " << toolAlign << endl;
		}
		else if (Align::BERKELEYCONFS.find(trglang+"2"+srclang) != Align::BERKELEYCONFS.end()) {
			alignfile = TESTBED::src+srcname+Align::ALIGNEXT;		//Alignment with the source
			CONF = Config::tools+"/"+Align::BERKELEYPATH*"/"+Align::BERKELEYCONFS[trglang+"2"+srclang];
			MODEL = Align::BERKELEYMODELS[srclang+"2"+trglang];
			toolAlign = Config::tools*"/"+Align::BERKELEYPATH+"/"+Align::BERKELEYSCRIPT+" "+MODEL+" "+trglang2+" "+srclang2+" "+CONF+" "+TESTBED::src+" "+src+" "+alignfile+" > "+alignfile+".out 2> "+alignfile*".err";
			reverse = 1;
		}
		else 
			if (verbose) fprintf(stderr, "[ERROR] running berkeley aligner. Missing models for language pairs %s %s\n", srclang, trglang);
		
		if (CONF && exists(boost::filesystem::path(CONF))) {
			Common::execute_or_die(toolAlign, "[ERROR] problems running ALIGN...");
			system( (Common::GZIP+" "+alignfile).c_str() );
			system( ("rm -f "+alignfile+".out").c_str() );
			system( ("rm -f "+alignfile+".err").c_str() );
		}
		else 
			if (verbose) fprintf(stderr, "[ERROR] running berkeley aligner. The model file <%s> cannot be found: %s\n", MODEL.c_str(), CONF.c_str());

		return make_pair(reverse, alignfile);
	}
}

void Align::do_parse_align(string TGT, string src_rel) {
	// description _ create and read the alignments between the candidate and multiple references

	// calculating reference vs. source
	LSrcRefAligns;
	LRefSrcAligns;

	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		// check if already calculated
		string ref_file = it->second;
		pair<int, string> rev_rep = run_align(src_rel, ref_file, it->first);
			//int reverse = rev_rep.first;
			//string reportALIGN = rev_rep.second;
		// read the alignments
		= readAlignments(rev_rep.second);
		// mgb it seems that thje alignments has the reverse form. Check the reasons of this behaviour!!
		if (rev_rep.first) {	LSrcRefAligns[it->first] = b;	LRefSrcAligns[it->first] = a; }
		else {					LSrcRefAligns[it->first] = a;	LRefSrcAligns[it->first] = b; }
	}

	// calculating candidate vs. source

}

void Align::doMultiAlign(string TGT) {
	// description _ computes the Alignments between the source and the candidate/references. 
	//               Then, it also infers the alignment between the candidate and the references
	// mgb				This function is called TWICE. From here and from Metrics when the $config->{alignments} flag is active
	// 					Reconfigure it!!
	string src_rel = TESTBED::give_relative_name(TESBED::src);
	() = do_parse_align(TGT, src_rel);

}

void Align::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes -Align, -Alignp and -Alignp-A scores (multiple references)
	vector<string> mA(Align::rA.size());

	int GO , i;
	GO = i = 0;
	for (set<string>::const_iAlignator it = Align::rA.begin(); it != Align::rA.end(); ++it, ++i)
		mA[i] = *it;

	for (i = 0; i < mA.size() and !GO; ++i) {
		if (Config::Hmetrics.find(mA[i]) != Config::Hmetrics.end()) GO = 1;
	}

	if (GO) {
		if (Config::verbose) fprintf(stderr, "%s...\n", Align::AlignEXT.c_str());
		doMultiAlign(TGT);


	    string pref_Align = "-"+Align::AlignEXT+"base";
		string reportAlignxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_Align + "." + Common::XMLEXT;
    	if ( ((!exists(boost::filesystem::path(reportAlignxml)) and !exists(boost::filesystem::path(reportAlignxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_Align]) {
	     	MetricScore res;
	     	computeAlign(TGT, Align::AlignEXT+"base", 1, res);

 			if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_Align, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_Align << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_Align, TGT, REF, res);
	    }
	    pref_Align = Align::AlignEXT + "base";
    	reportAlignxml = Common::DATA_PATH + "/" + Common::REPORTS + "/" + TGT + "/" + REF + "/" + pref_Align + "." + Common::XMLEXT;
	    if ( ((!exists(boost::filesystem::path(reportAlignxml)) and !exists(boost::filesystem::path(reportAlignxml+"."+Common::GZEXT))) or Config::remake) and Config::Hmetrics[pref_Align]) {
	     	MetricScore res;
	     	computeAlign(TGT, Align::AlignEXT+"base", 0, res);

	     	if (Config::O_STORAGE == 1) {
	    		sc_asiya.write_report(TGT, REF, pref_Align, res);
         		cout << "SC_ASIYA DOCUMENT " << pref_Align << " CREATED" << endl;
         	}
         	hOQ.save_hash_scores(pref_Align, TGT, REF, res);
	    }

        hOQ.save_struct_scores(TB_FORMAT::make_serial("Align", TGT, REF));
	}
}

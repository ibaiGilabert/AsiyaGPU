#include "../include/SP.hpp"
#include "../include/Overlap.hpp"
#include "../include/NIST.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string SP::SPEXT = "SP";
const string SP::POSSEP = "##";
const string SP::CSEP = "__";
const string SP::SVMT = "svmtool-1.3.1";
	//const string SP::DICTS = "svmtool-1.3.1/dicts";	//fr
const string SP::BIOS = "bios-1.1.0";


map<string, string> SP::create_rLANGBIOS() {
	map<string, string> rLANGBIOS;
	rLANGBIOS[Common::L_ENG] = "en";	rLANGBIOS[Common::L_SPA] = "es";	rLANGBIOS[Common::L_CAT] = "ca";
	return rLANGBIOS;
}
map<string, string> SP::rLANGBIOS = create_rLANGBIOS();

map<string, string> SP::create_rLANGSVM() {
	map<string, string> rLANGSVM;
	rLANGSVM[Common::L_ENG] = "en";	rLANGSVM[Common::L_SPA] = "es";	rLANGSVM[Common::L_CAT] = "ca";	rLANGSVM[Common::L_FRN] = "fr";
	return rLANGSVM;
}
map<string, string> SP::rLANGSVM = create_rLANGSVM();

map<string, string> SP::create_rLANGBKLY() {
	map<string, string> rLANGBKLY;
	rLANGBKLY[Common::L_GER] = "de";
	return rLANGBKLY;
}
map<string, string> SP::rLANGBKLY = create_rLANGBKLY();


// SPA / CAT ---------------------------------------------------------

//AO AQ CC CS DA DD DE DI DN DP DT Faa Fat Fc Fd Fe Fg Fh Fia Fit Fp Fpa Fpt Fs Fx Fz I NC NP P0 PD PE PI PN PP PR PT PX RG RN SP VAG VAI VAM VAN VAP VAS VMG VMI VMM VMN VMP VMS VSG VSI VSM VSN VSP VSS W X Y Z Zm Zp
//A C D F I N P S V VA VM VS
//ADJP ADVP CONJP INTJ NP PP SBAR VP NEG MORFV O

set<string> SP::create_rSPspacat() {
	set<string> rSPspacat;
	rSPspacat.insert(SP::SPEXT+"-Oc(ADJP)"); rSPspacat.insert(SP::SPEXT+"-Oc(ADVP)"); rSPspacat.insert(SP::SPEXT+"-Oc(CONJP)");
	rSPspacat.insert(SP::SPEXT+"-Oc(INTJ)"); rSPspacat.insert(SP::SPEXT+"-Oc(NP)"); rSPspacat.insert(SP::SPEXT+"-Oc(PP)");
	rSPspacat.insert(SP::SPEXT+"-Oc(SBAR)"); rSPspacat.insert(SP::SPEXT+"-Oc(VP)"); rSPspacat.insert(SP::SPEXT+"-Oc(NEG)");
	rSPspacat.insert(SP::SPEXT+"-Oc(MORFV)"); rSPspacat.insert(SP::SPEXT+"-Oc(O)"); rSPspacat.insert(SP::SPEXT+"-Op(AO)");
	rSPspacat.insert(SP::SPEXT+"-Op(AQ)"); rSPspacat.insert(SP::SPEXT+"-Op(CC)"); rSPspacat.insert(SP::SPEXT+"-Op(CS)");
	rSPspacat.insert(SP::SPEXT+"-Op(DA)"); rSPspacat.insert(SP::SPEXT+"-Op(DD)"); rSPspacat.insert(SP::SPEXT+"-Op(DE)");
	rSPspacat.insert(SP::SPEXT+"-Op(DI)"); rSPspacat.insert(SP::SPEXT+"-Op(DN)"); rSPspacat.insert(SP::SPEXT+"-Op(DP)");
	rSPspacat.insert(SP::SPEXT+"-Op(DT)"); rSPspacat.insert(SP::SPEXT+"-Op(Faa)"); rSPspacat.insert(SP::SPEXT+"-Op(Fat)");
	rSPspacat.insert(SP::SPEXT+"-Op(Fc)"); rSPspacat.insert(SP::SPEXT+"-Op(Fd)"); rSPspacat.insert(SP::SPEXT+"-Op(Fe)");
	rSPspacat.insert(SP::SPEXT+"-Op(Fg)"); rSPspacat.insert(SP::SPEXT+"-Op(Fh)"); rSPspacat.insert(SP::SPEXT+"-Op(Fia)");
	rSPspacat.insert(SP::SPEXT+"-Op(Fit)"); rSPspacat.insert(SP::SPEXT+"-Op(Fp)"); rSPspacat.insert(SP::SPEXT+"-Op(Fpa)");
	rSPspacat.insert(SP::SPEXT+"-Op(Fpt)"); rSPspacat.insert(SP::SPEXT+"-Op(Fs)"); rSPspacat.insert(SP::SPEXT+"-Op(Fx)");
	rSPspacat.insert(SP::SPEXT+"-Op(Fz)"); rSPspacat.insert(SP::SPEXT+"-Op(I)"); rSPspacat.insert(SP::SPEXT+"-Op(NC)");
	rSPspacat.insert(SP::SPEXT+"-Op(NP)"); rSPspacat.insert(SP::SPEXT+"-Op(P0)"); rSPspacat.insert(SP::SPEXT+"-Op(PD)");
	rSPspacat.insert(SP::SPEXT+"-Op(PE)"); rSPspacat.insert(SP::SPEXT+"-Op(PI)"); rSPspacat.insert(SP::SPEXT+"-Op(PN)");
	rSPspacat.insert(SP::SPEXT+"-Op(PP)"); rSPspacat.insert(SP::SPEXT+"-Op(PR)"); rSPspacat.insert(SP::SPEXT+"-Op(PT)");
	rSPspacat.insert(SP::SPEXT+"-Op(PX)"); rSPspacat.insert(SP::SPEXT+"-Op(RG)"); rSPspacat.insert(SP::SPEXT+"-Op(RN)");
	rSPspacat.insert(SP::SPEXT+"-Op(SP)"); rSPspacat.insert(SP::SPEXT+"-Op(VAG)"); rSPspacat.insert(SP::SPEXT+"-Op(VAI)");
	rSPspacat.insert(SP::SPEXT+"-Op(VAM)"); rSPspacat.insert(SP::SPEXT+"-Op(VAN)"); rSPspacat.insert(SP::SPEXT+"-Op(VAP)");
	rSPspacat.insert(SP::SPEXT+"-Op(VAS)"); rSPspacat.insert(SP::SPEXT+"-Op(VMG)"); rSPspacat.insert(SP::SPEXT+"-Op(VMI)");
	rSPspacat.insert(SP::SPEXT+"-Op(VMM)"); rSPspacat.insert(SP::SPEXT+"-Op(VMN)"); rSPspacat.insert(SP::SPEXT+"-Op(VMP)");
	rSPspacat.insert(SP::SPEXT+"-Op(VMS)"); rSPspacat.insert(SP::SPEXT+"-Op(VSG)"); rSPspacat.insert(SP::SPEXT+"-Op(VSI)");
	rSPspacat.insert(SP::SPEXT+"-Op(VSM)"); rSPspacat.insert(SP::SPEXT+"-Op(VSN)"); rSPspacat.insert(SP::SPEXT+"-Op(VSP)");
	rSPspacat.insert(SP::SPEXT+"-Op(VSS)"); rSPspacat.insert(SP::SPEXT+"-Op(W)"); rSPspacat.insert(SP::SPEXT+"-Op(X)");
	rSPspacat.insert(SP::SPEXT+"-Op(Y)"); rSPspacat.insert(SP::SPEXT+"-Op(Z)"); rSPspacat.insert(SP::SPEXT+"-Op(Zm)");
	rSPspacat.insert(SP::SPEXT+"-Op(Zp)"); rSPspacat.insert(SP::SPEXT+"-Op(A)"); rSPspacat.insert(SP::SPEXT+"-Op(C)");
	rSPspacat.insert(SP::SPEXT+"-Op(D)"); rSPspacat.insert(SP::SPEXT+"-Op(F)"); rSPspacat.insert(SP::SPEXT+"-Op(I)");
	rSPspacat.insert(SP::SPEXT+"-Op(N)"); rSPspacat.insert(SP::SPEXT+"-Op(P)"); rSPspacat.insert(SP::SPEXT+"-Op(S)");
	rSPspacat.insert(SP::SPEXT+"-Op(V)"); rSPspacat.insert(SP::SPEXT+"-Op(VA)"); rSPspacat.insert(SP::SPEXT+"-Op(VM)");
	rSPspacat.insert(SP::SPEXT+"-Op(VS)"); rSPspacat.insert(SP::SPEXT+"-Op(*)"); rSPspacat.insert(SP::SPEXT+"-Oc(*)");
	rSPspacat.insert(SP::SPEXT+"-lNIST-1"); rSPspacat.insert(SP::SPEXT+"-lNIST-2"); rSPspacat.insert(SP::SPEXT+"-lNIST-3");
	rSPspacat.insert(SP::SPEXT+"-lNIST-4"); rSPspacat.insert(SP::SPEXT+"-lNIST-5"); rSPspacat.insert(SP::SPEXT+"-pNIST-1");
	rSPspacat.insert(SP::SPEXT+"-pNIST-2"); rSPspacat.insert(SP::SPEXT+"-pNIST-3"); rSPspacat.insert(SP::SPEXT+"-pNIST-4");
	rSPspacat.insert(SP::SPEXT+"-pNIST-5"); rSPspacat.insert(SP::SPEXT+"-iobNIST-1"); rSPspacat.insert(SP::SPEXT+"-iobNIST-2");
	rSPspacat.insert(SP::SPEXT+"-iobNIST-3"); rSPspacat.insert(SP::SPEXT+"-iobNIST-4"); rSPspacat.insert(SP::SPEXT+"-iobNIST-5");
	rSPspacat.insert(SP::SPEXT+"-cNIST-1"); rSPspacat.insert(SP::SPEXT+"-cNIST-2"); rSPspacat.insert(SP::SPEXT+"-cNIST-3");
	rSPspacat.insert(SP::SPEXT+"-cNIST-4"); rSPspacat.insert(SP::SPEXT+"-cNIST-5"); rSPspacat.insert(SP::SPEXT+"-lNISTi-2");
	rSPspacat.insert(SP::SPEXT+"-lNISTi-3"); rSPspacat.insert(SP::SPEXT+"-lNISTi-4"); rSPspacat.insert(SP::SPEXT+"-lNISTi-5");
	rSPspacat.insert(SP::SPEXT+"-pNISTi-2"); rSPspacat.insert(SP::SPEXT+"-pNISTi-3"); rSPspacat.insert(SP::SPEXT+"-pNISTi-4");
	rSPspacat.insert(SP::SPEXT+"-pNISTi-5"); rSPspacat.insert(SP::SPEXT+"-iobNISTi-2"); rSPspacat.insert(SP::SPEXT+"-iobNISTi-3");
	rSPspacat.insert(SP::SPEXT+"-iobNISTi-4"); rSPspacat.insert(SP::SPEXT+"-iobNISTi-5"); rSPspacat.insert(SP::SPEXT+"-cNISTi-2");
	rSPspacat.insert(SP::SPEXT+"-cNISTi-3"); rSPspacat.insert(SP::SPEXT+"-cNISTi-4"); rSPspacat.insert(SP::SPEXT+"-cNISTi-5");
	rSPspacat.insert(SP::SPEXT+"-lNIST"); rSPspacat.insert(SP::SPEXT+"-pNIST");
	rSPspacat.insert(SP::SPEXT+"-iobNIST"); rSPspacat.insert(SP::SPEXT+"-cNIST");
	return rSPspacat;
}
const set<string> SP::rSPspacat = create_rSPspacat();

// ENG ---------------------------------------------------------------

//CC CD DT EX FW IN JJ JJR JJS LS MD NN NNP NNPS NNS PDT POS PRP PRP$ RB RBR RBS RP SYM TO UH VB VBD VBG VBN VBP VBZ WDT WP WP$ WRB # $ '' ( ) , . : ``
//J N P R V W F
//ADJP ADVP CONJP INTJ LST NP PP PRT SBAR UCP VP

set<string> SP::create_rSPeng() {
	set<string> rSPeng;
	rSPeng.insert(SP::SPEXT+"-Oc(ADJP)"); rSPeng.insert(SP::SPEXT+"-Oc(ADVP)"); rSPeng.insert(SP::SPEXT+"-Oc(CONJP)");
	rSPeng.insert(SP::SPEXT+"-Oc(INTJ)"); rSPeng.insert(SP::SPEXT+"-Oc(LST)"); rSPeng.insert(SP::SPEXT+"-Oc(NP)");
	rSPeng.insert(SP::SPEXT+"-Oc(O)"); rSPeng.insert(SP::SPEXT+"-Oc(PP)"); rSPeng.insert(SP::SPEXT+"-Oc(PRT)");
	rSPeng.insert(SP::SPEXT+"-Oc(SBAR)"); rSPeng.insert(SP::SPEXT+"-Oc(UCP)"); rSPeng.insert(SP::SPEXT+"-Oc(VP)");
	rSPeng.insert(SP::SPEXT+"-Op(CC)"); rSPeng.insert(SP::SPEXT+"-Op(CD)"); rSPeng.insert(SP::SPEXT+"-Op(DT)");
	rSPeng.insert(SP::SPEXT+"-Op(EX)"); rSPeng.insert(SP::SPEXT+"-Op(FW)"); rSPeng.insert(SP::SPEXT+"-Op(IN)");
	rSPeng.insert(SP::SPEXT+"-Op(JJ)"); rSPeng.insert(SP::SPEXT+"-Op(JJR)"); rSPeng.insert(SP::SPEXT+"-Op(JJS)");
	rSPeng.insert(SP::SPEXT+"-Op(LS)"); rSPeng.insert(SP::SPEXT+"-Op(MD)"); rSPeng.insert(SP::SPEXT+"-Op(NN)");
	rSPeng.insert(SP::SPEXT+"-Op(NNP)"); rSPeng.insert(SP::SPEXT+"-Op(NNPS)"); rSPeng.insert(SP::SPEXT+"-Op(NNS)");
	rSPeng.insert(SP::SPEXT+"-Op(PDT)"); rSPeng.insert(SP::SPEXT+"-Op(POS)"); rSPeng.insert(SP::SPEXT+"-Op(PRP)");
	rSPeng.insert(SP::SPEXT+"-Op(PRP$)"); rSPeng.insert(SP::SPEXT+"-Op(RB)"); rSPeng.insert(SP::SPEXT+"-Op(RBR)");
	rSPeng.insert(SP::SPEXT+"-Op(RBS)"); rSPeng.insert(SP::SPEXT+"-Op(RP)"); rSPeng.insert(SP::SPEXT+"-Op(SYM)");
	rSPeng.insert(SP::SPEXT+"-Op(TO)"); rSPeng.insert(SP::SPEXT+"-Op(UH)"); rSPeng.insert(SP::SPEXT+"-Op(VB)");
	rSPeng.insert(SP::SPEXT+"-Op(VBD)"); rSPeng.insert(SP::SPEXT+"-Op(VBG)"); rSPeng.insert(SP::SPEXT+"-Op(VBN)");
	rSPeng.insert(SP::SPEXT+"-Op(VBP)"); rSPeng.insert(SP::SPEXT+"-Op(VBZ)"); rSPeng.insert(SP::SPEXT+"-Op(WDT)");
	rSPeng.insert(SP::SPEXT+"-Op(WP)"); rSPeng.insert(SP::SPEXT+"-Op(WP$)"); rSPeng.insert(SP::SPEXT+"-Op(WRB)");
	rSPeng.insert(SP::SPEXT+"-Op(#)"); rSPeng.insert(SP::SPEXT+"-Op($)"); rSPeng.insert(SP::SPEXT+"-Op(\'\')");
	rSPeng.insert(SP::SPEXT+"-Op(()"); rSPeng.insert(SP::SPEXT+"-Op())"); rSPeng.insert(SP::SPEXT+"-Op(,)");
	rSPeng.insert(SP::SPEXT+"-Op(.)"); rSPeng.insert(SP::SPEXT+"-Op(:)"); rSPeng.insert(SP::SPEXT+"-Op(``)");
	rSPeng.insert(SP::SPEXT+"-Op(J)"); rSPeng.insert(SP::SPEXT+"-Op(N)"); rSPeng.insert(SP::SPEXT+"-Op(P)");
	rSPeng.insert(SP::SPEXT+"-Op(R)"); rSPeng.insert(SP::SPEXT+"-Op(V)"); rSPeng.insert(SP::SPEXT+"-Op(W)");
	rSPeng.insert(SP::SPEXT+"-Op(F)"); rSPeng.insert(SP::SPEXT+"-Op(*)"); rSPeng.insert(SP::SPEXT+"-Oc(*)");
	rSPeng.insert(SP::SPEXT+"-lNIST-1"); rSPeng.insert(SP::SPEXT+"-lNIST-2"); rSPeng.insert(SP::SPEXT+"-lNIST-3");
	rSPeng.insert(SP::SPEXT+"-lNIST-4"); rSPeng.insert(SP::SPEXT+"-lNIST-5"); rSPeng.insert(SP::SPEXT+"-pNIST-1");
	rSPeng.insert(SP::SPEXT+"-pNIST-2"); rSPeng.insert(SP::SPEXT+"-pNIST-3"); rSPeng.insert(SP::SPEXT+"-pNIST-4");
	rSPeng.insert(SP::SPEXT+"-pNIST-5"); rSPeng.insert(SP::SPEXT+"-iobNIST-1"); rSPeng.insert(SP::SPEXT+"-iobNIST-2");
	rSPeng.insert(SP::SPEXT+"-iobNIST-3"); rSPeng.insert(SP::SPEXT+"-iobNIST-4"); rSPeng.insert(SP::SPEXT+"-iobNIST-5");
	rSPeng.insert(SP::SPEXT+"-cNIST-1"); rSPeng.insert(SP::SPEXT+"-cNIST-2"); rSPeng.insert(SP::SPEXT+"-cNIST-3");
	rSPeng.insert(SP::SPEXT+"-cNIST-4"); rSPeng.insert(SP::SPEXT+"-cNIST-5"); rSPeng.insert(SP::SPEXT+"-lNISTi-2");
	rSPeng.insert(SP::SPEXT+"-lNISTi-3"); rSPeng.insert(SP::SPEXT+"-lNISTi-4"); rSPeng.insert(SP::SPEXT+"-lNISTi-5");
	rSPeng.insert(SP::SPEXT+"-pNISTi-2"); rSPeng.insert(SP::SPEXT+"-pNISTi-3"); rSPeng.insert(SP::SPEXT+"-pNISTi-4");
	rSPeng.insert(SP::SPEXT+"-pNISTi-5"); rSPeng.insert(SP::SPEXT+"-iobNISTi-2"); rSPeng.insert(SP::SPEXT+"-iobNISTi-3");
	rSPeng.insert(SP::SPEXT+"-iobNISTi-4"); rSPeng.insert(SP::SPEXT+"-iobNISTi-5"); rSPeng.insert(SP::SPEXT+"-cNISTi-2");
	rSPeng.insert(SP::SPEXT+"-cNISTi-3"); rSPeng.insert(SP::SPEXT+"-cNISTi-4"); rSPeng.insert(SP::SPEXT+"-cNISTi-5");
	rSPeng.insert(SP::SPEXT+"-lNIST"); rSPeng.insert(SP::SPEXT+"-pNIST");
	rSPeng.insert(SP::SPEXT+"-iobNIST"); rSPeng.insert(SP::SPEXT+"-cNIST");
	return rSPeng;
}
const set<string> SP::rSPeng = create_rSPeng();

// FRN ---------------------------------------------------------------
//ADJ ADJWH ADV ADVWH CC CLO CLR CLS CS DET ET I NC NPP P P+D P+PRO PONCT PREF PRO PROREL V VIMP VINF VPP VPR VS

set<string> SP::create_rSPfrench() {
	set<string> rSPfrench;
	rSPfrench.insert(SP::SPEXT+"-Op(ADJ)"); rSPfrench.insert(SP::SPEXT+"-Op(ADJWH)"); rSPfrench.insert(SP::SPEXT+"-Op(ADV)");
	rSPfrench.insert(SP::SPEXT+"-Op(ADVWH)"); rSPfrench.insert(SP::SPEXT+"-Op(CC)"); rSPfrench.insert(SP::SPEXT+"-Op(CLO)");
	rSPfrench.insert(SP::SPEXT+"-Op(CLR)"); rSPfrench.insert(SP::SPEXT+"-Op(CLS)"); rSPfrench.insert(SP::SPEXT+"-Op(CS)");
	rSPfrench.insert(SP::SPEXT+"-Op(DET)"); rSPfrench.insert(SP::SPEXT+"-Op(ET)"); rSPfrench.insert(SP::SPEXT+"-Op(I)");
	rSPfrench.insert(SP::SPEXT+"-Op(NC)"); rSPfrench.insert(SP::SPEXT+"-Op(NPP)"); rSPfrench.insert(SP::SPEXT+"-Op(P)");
	rSPfrench.insert(SP::SPEXT+"-Op(P+D)"); rSPfrench.insert(SP::SPEXT+"-Op(P+PRO)"); rSPfrench.insert(SP::SPEXT+"-Op(PONCT)");
	rSPfrench.insert(SP::SPEXT+"-Op(PREF)"); rSPfrench.insert(SP::SPEXT+"-Op(PRO)"); rSPfrench.insert(SP::SPEXT+"-Op(PROREL)");
	rSPfrench.insert(SP::SPEXT+"-Op(V)"); rSPfrench.insert(SP::SPEXT+"-Op(VIMP)"); rSPfrench.insert(SP::SPEXT+"-Op(VINF)");
	rSPfrench.insert(SP::SPEXT+"-Op(VPP)"); rSPfrench.insert(SP::SPEXT+"-Op(VPR)"); rSPfrench.insert(SP::SPEXT+"-Op(VS)");
	rSPfrench.insert(SP::SPEXT+"-Op(*)");
	rSPfrench.insert(SP::SPEXT+"-lNIST-1"); rSPfrench.insert(SP::SPEXT+"-lNIST-2"); rSPfrench.insert(SP::SPEXT+"-lNIST-3");
	rSPfrench.insert(SP::SPEXT+"-lNIST-4"); rSPfrench.insert(SP::SPEXT+"-lNIST-5"); rSPfrench.insert(SP::SPEXT+"-pNIST-1");
	rSPfrench.insert(SP::SPEXT+"-pNIST-2"); rSPfrench.insert(SP::SPEXT+"-pNIST-3"); rSPfrench.insert(SP::SPEXT+"-pNIST-4");
	rSPfrench.insert(SP::SPEXT+"-pNIST-5"); rSPfrench.insert(SP::SPEXT+"-lNISTi-2"); rSPfrench.insert(SP::SPEXT+"-lNISTi-3");
	rSPfrench.insert(SP::SPEXT+"-lNISTi-4"); rSPfrench.insert(SP::SPEXT+"-lNISTi-5"); rSPfrench.insert(SP::SPEXT+"-pNISTi-2");
	rSPfrench.insert(SP::SPEXT+"-pNISTi-3"); rSPfrench.insert(SP::SPEXT+"-pNISTi-4"); rSPfrench.insert(SP::SPEXT+"-pNISTi-5");
	rSPfrench.insert(SP::SPEXT+"-lNIST"); rSPfrench.insert(SP::SPEXT+"-pNIST");
	return rSPfrench;
}
const set<string> SP::rSPfrench = create_rSPfrench();

set<string> SP::create_rSPgerman() {
	set<string> rSPgerman;
	rSPgerman.insert(SP::SPEXT+"-Op($*LRB*)"); rSPgerman.insert(SP::SPEXT+"-Op($,)"); rSPgerman.insert(SP::SPEXT+"-Op($.)");
	rSPgerman.insert(SP::SPEXT+"-Op(*T1*)"); rSPgerman.insert(SP::SPEXT+"-Op(*T2*)"); rSPgerman.insert(SP::SPEXT+"-Op(*T3*)");
	rSPgerman.insert(SP::SPEXT+"-Op(*T4*)"); rSPgerman.insert(SP::SPEXT+"-Op(*T5*)"); rSPgerman.insert(SP::SPEXT+"-Op(*T6*)");
	rSPgerman.insert(SP::SPEXT+"-Op(*T7*)"); rSPgerman.insert(SP::SPEXT+"-Op(*T8*)"); rSPgerman.insert(SP::SPEXT+"-Op(--)");
	rSPgerman.insert(SP::SPEXT+"-Op(ADJA)"); rSPgerman.insert(SP::SPEXT+"-Op(ADJD)"); rSPgerman.insert(SP::SPEXT+"-Op(ADV)");
	rSPgerman.insert(SP::SPEXT+"-Op(APPO)"); rSPgerman.insert(SP::SPEXT+"-Op(APPR)"); rSPgerman.insert(SP::SPEXT+"-Op(APPRART)");
	rSPgerman.insert(SP::SPEXT+"-Op(APZR)"); rSPgerman.insert(SP::SPEXT+"-Op(ART)"); rSPgerman.insert(SP::SPEXT+"-Op(CARD)");
	rSPgerman.insert(SP::SPEXT+"-Op(FM)"); rSPgerman.insert(SP::SPEXT+"-Op(ITJ)"); rSPgerman.insert(SP::SPEXT+"-Op(KOKOM)");
	rSPgerman.insert(SP::SPEXT+"-Op(KON)"); rSPgerman.insert(SP::SPEXT+"-Op(KOUI)"); rSPgerman.insert(SP::SPEXT+"-Op(KOUS)");
	rSPgerman.insert(SP::SPEXT+"-Op(NE)"); rSPgerman.insert(SP::SPEXT+"-Op(NN)"); rSPgerman.insert(SP::SPEXT+"-Op(PDAT)");
	rSPgerman.insert(SP::SPEXT+"-Op(PDS)"); rSPgerman.insert(SP::SPEXT+"-Op(PIAT)"); rSPgerman.insert(SP::SPEXT+"-Op(PIDAT)");
	rSPgerman.insert(SP::SPEXT+"-Op(PIS)"); rSPgerman.insert(SP::SPEXT+"-Op(PPER)"); rSPgerman.insert(SP::SPEXT+"-Op(PPOSAT)");
	rSPgerman.insert(SP::SPEXT+"-Op(PPOSS)"); rSPgerman.insert(SP::SPEXT+"-Op(PRELAT)"); rSPgerman.insert(SP::SPEXT+"-Op(PRELS)");
	rSPgerman.insert(SP::SPEXT+"-Op(PRF)"); rSPgerman.insert(SP::SPEXT+"-Op(PROAV)"); rSPgerman.insert(SP::SPEXT+"-Op(PTKA)");
	rSPgerman.insert(SP::SPEXT+"-Op(PTKANT)"); rSPgerman.insert(SP::SPEXT+"-Op(PTKNEG)"); rSPgerman.insert(SP::SPEXT+"-Op(PTKVZ)");
	rSPgerman.insert(SP::SPEXT+"-Op(PTKZU)"); rSPgerman.insert(SP::SPEXT+"-Op(PWAT)"); rSPgerman.insert(SP::SPEXT+"-Op(PWAV)");
	rSPgerman.insert(SP::SPEXT+"-Op(PWS)"); rSPgerman.insert(SP::SPEXT+"-Op(TRUNC)"); rSPgerman.insert(SP::SPEXT+"-Op(VAFIN)");
	rSPgerman.insert(SP::SPEXT+"-Op(VAIMP)"); rSPgerman.insert(SP::SPEXT+"-Op(VAINF)"); rSPgerman.insert(SP::SPEXT+"-Op(VAPP)");
	rSPgerman.insert(SP::SPEXT+"-Op(VMFIN)"); rSPgerman.insert(SP::SPEXT+"-Op(VMINF)"); rSPgerman.insert(SP::SPEXT+"-Op(VMPP)");
	rSPgerman.insert(SP::SPEXT+"-Op(VVFIN)"); rSPgerman.insert(SP::SPEXT+"-Op(VVIMP)"); rSPgerman.insert(SP::SPEXT+"-Op(VVINF)");
	rSPgerman.insert(SP::SPEXT+"-Op(VVIZU)"); rSPgerman.insert(SP::SPEXT+"-Op(VVPP)"); rSPgerman.insert(SP::SPEXT+"-Op(XY)");
	rSPgerman.insert(SP::SPEXT+"-Op(*)");
	rSPgerman.insert(SP::SPEXT+"-pNIST-1"); rSPgerman.insert(SP::SPEXT+"-pNIST-2"); rSPgerman.insert(SP::SPEXT+"-pNIST-3");
	rSPgerman.insert(SP::SPEXT+"-pNIST-4"); rSPgerman.insert(SP::SPEXT+"-pNIST-5"); rSPgerman.insert(SP::SPEXT+"-pNISTi-2");
	rSPgerman.insert(SP::SPEXT+"-pNISTi-3"); rSPgerman.insert(SP::SPEXT+"-pNISTi-4"); rSPgerman.insert(SP::SPEXT+"-pNISTi-5");
	rSPgerman.insert(SP::SPEXT+"-pNIST");
	return rSPgerman;
}
const set<string> SP::rSPgerman = create_rSPgerman();

SP::SP() {
	USE_LEMMAS = 1;
	USE_DICTS = 1;
	USE_CHUNKS = 1;
}

SP::~SP() {}


void SP::FILE_merge_BIOS(string input1, string input2, string output) {
	// description _ merges tokens in two files so they conform the tokenization of the first file 

	//fprintf(stderr, "[SP] to merge_BIOS (input1:%s, input2:%s, output: %s)\n", input1.c_str(), input2.c_str(), output.c_str());
    ofstream o_file(output.c_str());
    if (!o_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", output.c_str()); exit(1); }

    ifstream in2_file(input2.c_str());
    if (!in2_file.is_open()) { fprintf(stderr, "couldn't open input file <%s>\n", input2.c_str()); exit(1); }
    
    ifstream in1_file(input1.c_str());
    if (in1_file) {
    	string str1, str2;
    	int empty = 1;
        boost::regex re("^$");
        while( getline(in1_file, str1) ) {
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(str1, results, re)) {
            	if (empty) empty = 0;	// empty sentence
            	else empty = 1;			// sentence separator
            	o_file << endl;
			}
			else {
				getline(in2_file, str2);
	            if (boost::regex_match(str2, results, re))
					getline(in2_file, str2);		// line 2 is empty
				vector<string> l1, l2;
				boost::split(l1, str1, boost::is_any_of("\t "));
				boost::split(l2, str2, boost::is_any_of("\t "));
				for (int i = 0; i < l1.size(); ++i) {
					o_file << l1[i] << " ";
				}
				for (int i = 1; i < l2.size(); ++i) {
					o_file << l2[i] << " ";
				}
				//istringstream buf1(str1), buf2(str2);
    			/*for(string token; getline(buf1, token, ' '); ) {
			    	//l1.push_back(token);
			    	o_file << token << " ";
			    }
			    for(string token; getline(buf2, token, ' '); ) {
			    	//l2.push_back(token);
		    		o_file << token << " ";
			    }*/
			    o_file << endl;
			    empty = 0;
			}
		}
		o_file.close();
		in1_file.close();
		in2_file.close();
	}
    else { fprintf(stderr, "couldn't open input file <%s>\n", input1.c_str()); exit(1); }
}

void SP::FILE_parse_BIOS(string input) {
	// description _ performs the shallow parsing and writes a several files (using SVMTool)
	string wlpc_file = input+"."+SP::SPEXT+".wlpc";
	string wlp_file = input+"."+SP::SPEXT+".wlp";
	string wp_file = input+"."+SP::SPEXT+".wp";
	string wc_file = input+"."+SP::SPEXT+".wc";

	if ( !exists(boost::filesystem::path(wc_file)) and !exists(boost::filesystem::path(wc_file+"."+Common::GZEXT)) ) {
		if ( !exists(boost::filesystem::path(wp_file)) and !exists(boost::filesystem::path(wp_file+"."+Common::GZEXT)) ) {
			string sys_aux = Common::GUNZIP+" "+wp_file+"."+Common::GZEXT;
			system(sys_aux.c_str());
		}
		string command = "cat "+ wp_file+" | java -Dfile.encoding=UTF-8 -Xmx1024m -cp "+Config::tools+"/"+SP::BIOS+"/output/classes/:"+ 
                             Config::tools+"/mill/output/classes:"+Config::tools+"/"+SP::BIOS+"/jars/maxent-2.3.0.jar:"+
                             Config::tools+"/"+SP::BIOS+"/jars/trove.jar:"+Config::tools+"/"+SP::BIOS+"/jars/antlr-2.7.5.jar:"+
                             Config::tools+"/"+SP::BIOS+"/jars/log4j.jar bios.chunker.Chunker"+
                             " --predict --data="+Config::tools+"/"+SP::BIOS+"/data/chunker/"+SP::rLANGBIOS[Config::LANG]+
                             " --model=conll.paum."+((Config::CASE == Common::CASE_CI)? "ci" : "cs")+".model"+
                             " --type=paum --case-sensitive="+((Config::CASE == Common::CASE_CI)? "false" : "true")+
                             " --log4j="+Config::tools+"/"+SP::BIOS+"/log4j.properties > "+wc_file+" 2> "+wc_file+".err";
        Common::execute_or_die(command, "[ERROR] problems running BIOS...");

        system( ("rm -f "+wc_file+".err").c_str() );

        string wpc_file = input+"."+SP::SPEXT+".wpc";
        // merging tagging + chunking
      	FILE_merge_BIOS(wp_file, wc_file, wpc_file);
		// merging tagging + lemma + chunking
		if ( !exists(boost::filesystem::path(wlp_file)) and exists(boost::filesystem::path(wlp_file+"."+Common::GZEXT)) ) {
			system( (Common::GUNZIP+" "+wlp_file+"."+Common::GZEXT).c_str() );
		}
		FILE_merge_BIOS(wlp_file, wc_file, wlpc_file);
	}
}

int SP::FILE_parse_BKLY(string input) {

}

int SP::FILE_parse_SVM(string input) {
	// description _ performs the shallow parsing and writes a several files (using SVMTool)
	//               (wplc -> TOKEN PoS LEMMA CHUNK)
	string L = Config::LANG;
	string C = Config::CASE;
	string lblex;
	string lpath = Config::tools+"/"+SP::SVMT+"/models/"+L+"/"+C+"/";
    string wlp_file = input+"."+SP::SPEXT+".wlp";

    boost::regex re("^"+Common::L_SPA+".*");
    boost::match_results<string::const_iterator> results;
    if (boost::regex_match(L, results, re)) {
    	if (C == Common::CASE_CI) lpath += "Ancora_es_lc";
    	else lpath += "Ancora_es";
    }
    else if (L == Common::L_CAT) {
    	if (C == Common::CASE_CI) lpath += "Ancora_ca_lc";
    	else lpath += "Ancora_ca";
    }
    else if (L == Common::L_ENG) {
    	if (C == Common::CASE_CI) lpath += "WSJQB_en_lc";
    	else lpath += "WSJQB_en";
    }
    else if (L == Common::L_FRN) {
    	USE_DICTS = 0;
    	if (C == Common::CASE_CI) lpath += "FTB_fr_lc";
    	else lpath += "FTB_fr";
    }
    else { fprintf(stderr, "SVMTool for '%s' LANGUAGE NOT AVAILABLE!!\n", L.c_str()); exit(1); }

    if (USE_DICTS) {
    	//string l = L.substr(0, 2);
    	//lblex = Config::tools+"/"+SP::SVMT+"/dicts/"+l+"/backup_lexicon.DICT";
    		//cout << "[SP]initialize-> l:" << l << " lblex:" << lblex << " L:" << L << " C:" << C << endl;

    	lblex = Config::tools+"/"+SP::SVMT+"/dicts/"+L+"/lemmas.txt";
    }
    //if (verbose) fprintf(stderr, "<[SVMTool] and [Pos-tagger] %s>\n", L.c_str());


	string command = Config::tools+"/"+SP::SVMT+"/scripts/doSVMTtagger.sh "+input+" "+wlp_file+" 0 "+lpath+" 4 LRL 0 0 "+lblex+" 0";
		fprintf(stderr, "[SP]doSVMTagger: %s\n", command.c_str());
    Common::execute_or_die(command, "[ERROR] problems running SVMTtagger...");

	string conll_file = input+"."+SP::SPEXT+".conll";
	//string wpl_file = input+"."+SP::SPEXT+".wpl";
	string wp_file = input+"."+SP::SPEXT+".wp";

	ofstream wp_out_file(wp_file.c_str());
    if (!wp_out_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", wp_file.c_str()); exit(1); }

	ofstream conll_out_file(conll_file.c_str());
    if (!conll_out_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", conll_file.c_str()); exit(1); }

	int iter = 0;
	ifstream out_file(wlp_file.c_str());
	if (out_file) {
		string str;
		int line = 1;
		while ( getline(out_file, str) ) {
			istringstream iss(str);
			if (str.empty()) { 
				wp_out_file << endl;
				conll_out_file << endl;
				line = 1;
			}
			else {
				string w, l, p;
				iss >> w >> l >> p;
				
				wp_out_file << w << " " << p << endl;
				conll_out_file << line << "\t" << w << "\t" << l << "\t" << p.substr(0, 1) << "\t" << p << "\t_" << endl;
				//cout << "[conll]line: " << line << "\t" << w << "\t" << l << "\t" << p.substr(0, 1) << "\t" << p << "\t_" << endl;

				if (Config::verbose) {
					if ( (iter%10) == 0) fprintf(stderr, ".");
					if ( (iter%100) == 0) fprintf(stderr, "%d", iter);
				}
				++line;
				++iter;
			}
		}
		out_file.close();
	}
	else { fprintf(stderr, "couldn't open input file <%s>\n", wlp_file.c_str()); exit(1); }

	conll_out_file.close();
	wp_out_file.close();

	return iter;
}

/*SP::initialize_svmt() {
	// description _ initializes the SVMTool models for languages involved
	int mode = 0;
	string direction = "LRL";
	string lpath = Config::tools+"/"+SP::SVMT+"/"+models+"/"+Config::LANG+"/"+Config::CASE+"/";
	string lblex;

	if
}
void SP::start_parser(int which) {
	// description _ responsible for starting the shallow parser  [allowing for loading individual components]
	//               (WORD + PoS + LEMMA) tagging

	if (Config::verbose) fprintf(stderr, "\n[PARSER] starting parser...\n");
    // ------------------------------------------------------------------
    // initializing pos-tagger
	svmtool = initialize_svmt();
    // ------------------------------------------------------------------
    // initializing lemmatizer
	if ((which == 0 or which > 1) and SP::USE_LEMMAS)
		lemmatizer = initialize_lemmatizer();
    // ------------------------------------------------------------------
	parser["svmt"] = svmtool;
	parser["LANG"] = Config::LANG;
}*/

void SP::FILE_parse(string input) {
	// description _ performs the shallow parsing and writes a several files (using SVMTool and BIOS)
	//               (wplc -> TOKEN PoS LEMMA CHUNK)
	int use_chunks = SP::rLANGBIOS.find(Config::LANG) != SP::rLANGBIOS.end() ? 1 : 0;

	if (SP::rLANGSVM.find(Config::LANG) != SP::rLANGSVM.end() or SP::rLANGBKLY.find(Config::LANG) != SP::rLANGBKLY.end()) {
		string spfile = use_chunks ? input+"."+SP::SPEXT+".wlpc" : input+"."+SP::SPEXT+".wlp";

		if ( !exists(boost::filesystem::path(spfile)) and !exists(boost::filesystem::path(spfile+"."+Common::GZEXT)) ) {
			string wpfile = input+"."+SP::SPEXT+".wp";
			//string wplfile = input+"."+SP::SPEXT+".wpl";
			string wlpfile = input+"."+SP::SPEXT+".wlp";
			string conllfile = input+"."+SP::SPEXT+".conll";
			if (!exists(boost::filesystem::path(wpfile)) and !exists(boost::filesystem::path(wpfile+"."+Common::GZEXT))) {
	            //tokenizing + tagging via SVMTool (en, ca, es) or Berkeley (fr, de)
				if (Config::verbose) fprintf(stderr, "Running shallow-parsing [%s -> %s]\n", wpfile.c_str(), wpfile.c_str());

				int iter = 0;
				if (SP::rLANGSVM.find(Config::LANG) != SP::rLANGSVM.end()) {
					fprintf(stderr, " - to FILE_parse_SVM <intput:%s>\n", input.c_str());
					iter = FILE_parse_SVM(input);
					fprintf(stderr, " - iter: %d\n", iter);
				}
				else if (SP::rLANGBKLY.find(Config::LANG) != SP::rLANGBKLY.end()) {
					USE_LEMMAS = 0;
					fprintf(stderr, " - to FILE_parse_BKLY <intput:%s>\n", input.c_str());
					iter = FILE_parse_BKLY(input);
					fprintf(stderr, " - iter: %d\n", iter);
				}
				if (Config::verbose) fprintf(stderr, ".. %d segments [DONE]\n", iter);
			}
			//chunking via BIOS
			if (use_chunks) {
				string wcfile = input+"."+SP::SPEXT+".wc";
				string wpcfile = input+"."+SP::SPEXT+".wpc";
				FILE_parse_BIOS(input);
				//end - gzip the files
				string gz_aux;
				gz_aux = Common::GZIP+" "+wpcfile;	system(gz_aux.c_str());
				gz_aux = Common::GZIP+" "+wcfile;	system(gz_aux.c_str());
			}
			//end - gzip the files, DON'T zip before because bios use them!
			string gz_aux;
			gz_aux = Common::GZIP+" "+wpfile;		system(gz_aux.c_str());
			gz_aux = Common::GZIP+" "+wlpfile;		system(gz_aux.c_str());
			gz_aux = Common::GZIP+" "+conllfile;	system(gz_aux.c_str());

		}
	}
	else { fprintf(stderr, "[ERROR] Shallow parser not available for '%s' language!!\n", Config::LANG.c_str()); exit(1); }
}


void SP::FILE_parse_split(string input) {
	// description _ performs the shallow parsing and writes 5 different files (used as input for SP metrics computation)
	//               (ALL_WLPC, PoS, lemma, chunk label, chunk)
   
	//check whether chunks were calculated
	bool use_chunks = (SP::rLANGBIOS.find(Config::LANG) != SP::rLANGBIOS.end()) ? true : false;

	// wlpc or wlp
	string spfile = (use_chunks) ? input+"."+SP::SPEXT+".wlpc" : input+"."+SP::SPEXT+".wlp";
	if (!exists(boost::filesystem::path(spfile))) {
		if (!exists(boost::filesystem::path(spfile+"."+Common::GZEXT))) {
			string sys_aux = Common::GUNZIP+" "+spfile+"."+Common::GZEXT;	system(sys_aux.c_str());
		}
		else FILE_parse(input);
	}

	string pfile = input+"."+SP::SPEXT+".P";
	string lfile = input+"."+SP::SPEXT+".L";
	string cfile = input+"."+SP::SPEXT+".iob";
	string Cfile = input+"."+SP::SPEXT+".C";

	if ( (!exists(boost::filesystem::path(pfile)) and !exists(boost::filesystem::path(pfile+"."+Common::GZEXT))) or 
		 (!exists(boost::filesystem::path(lfile)) and !exists(boost::filesystem::path(lfile+"."+Common::GZEXT))) or
		 (!exists(boost::filesystem::path(cfile)) and !exists(boost::filesystem::path(cfile+"."+Common::GZEXT)) and use_chunks) or
		 (!exists(boost::filesystem::path(Cfile)) and !exists(boost::filesystem::path(Cfile+"."+Common::GZEXT)) and use_chunks) ) {

		// open files
		ofstream p_file, l_file, c_file, C_file;

		p_file.open(pfile.c_str());
	    if (!p_file.is_open()) { fprintf(stderr, "couldn't open output pFILE file <%s>\n", pfile.c_str()); exit(1); }

		l_file.open(lfile.c_str());
	    if (!l_file.is_open()) { fprintf(stderr, "couldn't open output lFILE file <%s>\n", lfile.c_str()); exit(1); }

	    if (use_chunks) {
			c_file.open(cfile.c_str());
		    if (!c_file.is_open()) { fprintf(stderr, "couldn't open output cFILE file <%s>\n", cfile.c_str()); exit(1); }

			C_file.open(Cfile.c_str());
		    if (!C_file.is_open()) { fprintf(stderr, "couldn't open output CFILE file <%s>\n", Cfile.c_str()); exit(1); }
	    }

	    // process SPFILE
		int EMPTY = 1;
		boost::regex re("B-.*");
		vector<string> Lp, Ll, Lc, LC;
	    ifstream sp_file(spfile.c_str());
	    if (sp_file) {
	    	string line;
	    	while( getline(sp_file, line) ) {
	    			//cout << "line: |" << line << "|" << endl;	//fprintf(stderr, "line: |%s|\n", line.c_str());
	    		if (line.empty()) {
		    		if (EMPTY) {	// empty sentence 
		    			EMPTY = 0;
		    		}
					else {				// sentence separator
						/*p_file << Lp[0];								// OJU!!!!!
						for (int j = 1; j < Lp.size(); ++j) p_file << " " << Lp[j];
						p_file << endl;*/
						for (int k = 0; k < Lp.size(); ++k)
							p_file << Lp[k] << " ";
						p_file << endl;

						/*l_file << Ll[0];								// OJU!!!!!
						for (int j = 1; j < Ll.size(); ++j) l_file << " " << Ll[j];
						l_file << endl;*/
						for (int k = 0; k < Ll.size(); ++k)
							l_file << Ll[k] << " ";
						l_file << endl;

	                        /*fprintf(stderr, "\tLp(after) ->");
	                        for (int k = 0; k < Lp.size(); ++k) fprintf(stderr, " %s", Lp[k].c_str());
	                        fprintf(stderr, "\n"); 
	                        fprintf(stderr, "\tLl(after) ->");
	                        for (int k = 0; k < Ll.size(); ++k) fprintf(stderr, " %s", Ll[k].c_str());
	                        fprintf(stderr, "\n");
	                    	eixt(1);*/


						if (use_chunks) {
							/*c_file << Lc[0];								// OJU!!!!!
							for (int j = 1; j < Lc.size(); ++j) c_file << " " << Lc[j];
							c_file << endl;*/
							for (int k = 0; k < Lc.size(); ++k)
								c_file << Lc[k] << " ";
							c_file << endl;

							/*C_file << LC[0];								// OJU!!!!!
							for (int j = 1; j < LC.size(); ++j) C_file << " " << LC[j];
							C_file << endl;*/	
							for (int k = 0; k < LC.size(); ++k)
								C_file << LC[k] << " ";
							C_file << endl;
						}
						Lp.clear();	Ll.clear();	Lc.clear();	LC.clear();
						EMPTY = 1;
					}
				}
				else {
					vector<string> l;
				    istringstream buf(line);
				    for(string token; getline(buf, token, ' '); )
				        l.push_back(token);

					    /*fprintf(stderr, "--- l parsed --\n");
					    for (int k = 0; k < l.size(); ++k) {
					    	fprintf(stderr, "l[%d]: %s\n", k, l[k].c_str());
					    }
					    fprintf(stderr, "---------------\n");*/

				    Ll.push_back(l[1]);
				 	Lp.push_back(l[2]);
				 	boost::match_results<string::const_iterator> results;
				 	if (use_chunks) Lc.push_back(l[3]);
				 	if (use_chunks and l[3] == "O") LC.push_back(l[3]);
				 	else if (use_chunks and boost::regex_match(l[3], results, re)) {
				 		vector<string> C;
					 	istringstream bufC(l[3]);
					    for(string token; getline(bufC, token, '-'); )
					        C.push_back(token);
					    LC.push_back(C[1]);
					}
					EMPTY = 0;
				}
	    	}
	    	// close files
	    	l_file.close();
	    	p_file.close();
	    	sp_file.close();
	    	if (use_chunks) { c_file.close(); C_file.close(); }
	    }
    	else { fprintf(stderr, "couldn't open file <%s>\n", spfile.c_str()); exit(1); }
	}
	string sys_aux = Common::GZIP+" "+spfile;	system(sys_aux.c_str());
}


void SP::FILE_parse_and_read(string input, vector<sParsed> &FILE) {
	// description _ reads "wplc or wpl" file, performing the shallow parsing (using SVMTool and BIOS) only if required
	//               (wlpc -> TOKEN LEMMA PoS CHUNK)
	FILE_parse(input);

	// WLPC
	string spfile = input+"."+SP::SPEXT+".wlpc";
	if (!exists(boost::filesystem::path(spfile)) and !exists(boost::filesystem::path(spfile+"."+Common::GZEXT))) {
		// WLP (without C)
		spfile = input+"."+SP::SPEXT+".wlp";
	}

	// unzip
	if (!exists(boost::filesystem::path(spfile)) and exists(boost::filesystem::path(spfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+spfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	ifstream sp_file(spfile.c_str());
	if (sp_file) {
		int i = 0;
		string str;
		//fprintf(stderr, "TESTEB::wc[%s]: %d\n", TGT.c_str(), TESTBED::wc[TGT]);
		/*for (map<string, int>::const_iterator it = TESTBED::wc.begin(); it != TESTBED::wc.end(); ++it) {
			fprintf(stderr, "\t[%s -> %d]\n", it->first.c_str(), it->second);
		}*/
		while ( getline(sp_file, str) ) {
			if (str.empty()) ++i;
			else {
				//if (i >= FILE.size());
				wParsed word;
			    istringstream iss(str);
				for(string token; getline(iss, token, ' '); )
			        word.push_back(token);
				FILE[i].push_back(word); 
			}
		}
		sp_file.close();
	}
	else { fprintf(stderr, "couldn't open file <%s>\n", spfile.c_str()); exit(1); }
}

void SP::SNT_extract_features(const sParsed &snt, bool use_chunks, SNTfeatures &SNTc, SNTfeatures &SNTp) {
	// description _ extracts features from a given shallow-parsed sentence.
		boost::regex re("^[BI]-");
		for(int i = 0; i < snt.size(); ++i) {
		string word, lemma, pos, chunklabel;
		if (use_chunks) {
			word = snt[i][0];	lemma = snt[i][1];	pos = snt[i][2];	chunklabel = snt[i][3];
		}
		else {
			word = snt[i][0];	lemma = snt[i][1];	pos = snt[i][2];	chunklabel = "";
		}

		string chunk = chunklabel;
		if (USE_LEMMAS) {
		    	//fprintf(stderr, "\n\n chunK(a): %s", chunk.c_str());
		    chunk = boost::regex_replace(chunk, re, "");
				//fprintf(stderr, "\t -> \t chunk(b): %s\n\n", chunk.c_str());
			if (USE_LEMMAS) {
				SNTc[chunk]["W"][lemma]++;
				SNTp[pos]["W"][lemma]++;
			}
			else {
				SNTc[chunk]["W"][word]++;
				SNTp[pos]["W"][word]++;	
			}
		}
	}
}

void SP::SNT_compute_overlap_scores(SNTfeatures &Tout_c, SNTfeatures &Tout_p, SNTfeatures &Tref_c, SNTfeatures &Tref_p, map<string, double> &SCORES) {
	// description _ computes distances between a candidate and a reference sentence (+features)
	
	//$LC = ($CONFIG::CASE ne $Common::CASE_CI), 

	double HITS, TOTAL;
	HITS = TOTAL = 0;
	//map<string, int> F;
	set<string> F;
	for (map<string, map< string, map<string, int> > >::const_iterator it = Tout_c.begin(); it != Tout_c.end(); ++it) {
		F.insert(it->first);
	}
	for (map<string, map< string, map<string, int> > >::const_iterator it = Tref_c.begin(); it != Tref_c.end(); ++it) {
		F.insert(it->first);
	}
	// $SP::SPEXT-Oc(*)  -----------------------------------------------------------------------------
	/*for (map<string, map< string, map<string, int> > >::const_iterator it = Tout["C"].begin(); it != Tout["C"].end(); ++it)
		F[it->first] = 1;
	for (map<string, map< string, map<string, int> > >::const_iterator it = Tref["C"].begin(); it != Tref["C"].end(); ++it)
		F[it->first] = 1;*/
	//for (map<string, int>::const_iterator it = F.begin(); it != F.end(); ++it) {
	Overlap Ov;
	for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
		map<string, int> out_c = Tout_c[*it]["W"];
		map<string, int> ref_c = Tref_c[*it]["W"];

		pair<double, double> hits_total = Ov.compute_overlap(/*Tout_c[*it]["W"], Tref_c[*it]["W"],*/out_c, ref_c, (Config::CASE != Common::CASE_CI));
		SCORES[SP::SPEXT+"-Oc("+*it+")"] = (hits_total.second == 0) ? 0 : (hits_total.first/hits_total.second);
		HITS += hits_total.first;	TOTAL += hits_total.second;
	}
	SCORES[SP::SPEXT+"-Oc(*)"] = (TOTAL == 0) ? 0 : (HITS / TOTAL);

	// $SP::SPEXT-Op(*)  -----------------------------------------------------------------------------
	HITS = TOTAL = 0;
	F.clear();
	map<string, double> ADD, TADD;
	for (SNTfeatures::const_iterator it = Tout_p.begin(); it != Tout_p.end(); ++it)
		F.insert(it->first);
	for (SNTfeatures::const_iterator it = Tref_p.begin(); it != Tref_p.end(); ++it)
		F.insert(it->first);
	for (set<string>::const_iterator it = F.begin(); it != F.end(); ++it) {
		pair<double, double> hits_total = Ov.compute_overlap(Tout_p[*it]["W"], Tref_p[*it]["W"], (Config::CASE != Common::CASE_CI));
		SCORES[SP::SPEXT+"-Op("+*it+")"] = (hits_total.second == 0) ? 0 : (hits_total.first/hits_total.second);
		HITS += hits_total.first;	TOTAL += hits_total.second;
	
		// additional --
		if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) {
            boost::regex re_A("^A.*");
            boost::regex re_C("^C.*");
            boost::regex re_D("^D.*");
            boost::regex re_F("^F.*");
            boost::regex re_I("^I.*");
            boost::regex re_N("^N.*");
            boost::regex re_P("^P.*");
            boost::regex re_S("^S.*");
            boost::regex re_V("^V.*");
            boost::regex re_VA("^VA.*");
            boost::regex re_VS("^VS.*");
            boost::regex re_VM("^VM.*");
			boost::match_results<string::const_iterator> results;
            if (boost::regex_match(*it, results, re_A)) { ADD["A"] += hits_total.first; TADD["A"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_C)) { ADD["C"] += hits_total.first; TADD["C"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_D)) { ADD["D"] += hits_total.first; TADD["D"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_F)) { ADD["F"] += hits_total.first; TADD["F"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_I)) { ADD["I"] += hits_total.first; TADD["I"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_N)) { ADD["N"] += hits_total.first; TADD["N"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_P)) { ADD["P"] += hits_total.first; TADD["P"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_S)) { ADD["S"] += hits_total.first; TADD["S"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_V)) { ADD["V"] += hits_total.first; TADD["V"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_VA)) { ADD["VA"] += hits_total.first; TADD["VA"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_VS)) { ADD["VS"] += hits_total.first; TADD["VS"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_VM)) { ADD["VM"] += hits_total.first; TADD["VM"] += hits_total.second; }
		}
		else if (Config::LANG == Common::L_ENG) {
            boost::regex re_JJ("^JJ.*");
            boost::regex re_NN("^NN.*");
            boost::regex re_PRP("^PRP.*");
            boost::regex re_RB("^RB.*");
            boost::regex re_VB("^VB.*");
            boost::regex re_W("^W.*");
            boost::regex re_sch("^[\\#\\$\\'\\(\\)\\,\\.\\:\\`].*");
			boost::match_results<string::const_iterator> results;
            if (boost::regex_match(*it, results, re_JJ)) { ADD["JJ"] += hits_total.first; TADD["JJ"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_NN)) { ADD["NN"] += hits_total.first; TADD["NN"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_PRP)) { ADD["PRP"] += hits_total.first; TADD["PRP"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_RB)) { ADD["RB"] += hits_total.first; TADD["RB"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_VB)) { ADD["VB"] += hits_total.first; TADD["VB"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_W)) { ADD["W"] += hits_total.first; TADD["W"] += hits_total.second; }
            else if (boost::regex_match(*it, results, re_sch)) { ADD["F"] += hits_total.first; TADD["F"] += hits_total.second; }           
		}
	}
	SCORES[SP::SPEXT+"-Op(*)"] = (TOTAL == 0) ? 0 : (HITS / TOTAL);

	for(map<string, double>::const_iterator it = TADD.begin(); it != TADD.end(); ++it) {
		SCORES[SP::SPEXT+"-Op("+it->first+")"] = (it->second == 0) ? 0 : (ADD[it->first] / it->second);
	}	
}

void SP::FILE_compute_overlap_metrics(const vector<sParsed> &FDout, const vector<sParsed> &FDref, vector< map<string, double> > &SCORES) {
	// description _ computes SP scores (single reference)

	//$LANG = CONFIG::LANG,
	//$LC = ($CONFIG::CASE ne $Common::CASE_CI), 
	//$UL = SP::USE_LEMMAS);
	SCORES.resize(FDref.size());
	bool use_chunks = SP::rLANGBIOS.find(Config::LANG) != SP::rLANGBIOS.end();
	for (int topic = 0; topic < FDref.size(); ++topic) {
		SNTfeatures OUTSNTc, OUTSNTp, REFSNTc, REFSNTp;

		SNT_extract_features(FDout[topic], use_chunks, OUTSNTc, OUTSNTp);
		SNT_extract_features(FDref[topic], use_chunks, REFSNTc, REFSNTp);

		//map<string, double> score;
		SNT_compute_overlap_scores(OUTSNTc, OUTSNTp, REFSNTc, REFSNTp, SCORES[topic]);
		//SCORES[topic] = score;
	}
}

void SP::get_segment_scores(const vector< map<string, double> > &scores, string feature, int mode, double &SYSscore, vector<double> &SEGscores) {
	// description _ retrieves scores at the segment level for the given feature
	//               as well as the average system score (dealing with void values
	//               according to the given 'mode' value)	
	int N = 0;
	SYSscore = 0;
	SEGscores.resize(scores.size());
	for (int i = 0; i < scores.size(); ++i) {
		int n = 0;		// feature exists? 0:no, 1:yes
		double SEGscr = 0;
		map<string, double> topic = scores[i];
		if (topic.find(feature) != topic.end()) {
			SEGscr = topic[feature]; n = 1;
		}

		SYSscore += SEGscr;		N +=n;
		if (n == 0) {
			if (mode == 0) SEGscr = Common::NOT_DEFINED;
			else if (mode == 1) SEGscr = 1;
			else if (mode == 2) SEGscr = 0;
		}
		SEGscores[i] = SEGscr;
	}

	if (N == 0) {
		if (mode == 0) SYSscore = Common::NOT_DEFINED;
		else if (mode == 1) SYSscore = 1;
		else if (mode == 2) SYSscore = 0;
	}
	else SYSscore /= N;
}

void SP::FILE_compute_MultiNIST_metrics(string TGT, string REF, Scores &hOQ) {
	// description _ computes SP scores (single reference) on a NIST basis
	bool use_chunks = SP::rLANGBIOS.find(Config::LANG) != SP::rLANGBIOS.end();
	string out = TESTBED::Hsystems[TGT];

	string pfile_out = out+"."+SP::SPEXT+".P";
	string lfile_out = out+"."+SP::SPEXT+".L";
	string cfile_out = out+"."+SP::SPEXT+".iob";
	string Cfile_out = out+"."+SP::SPEXT+".C";
	
	map<string, string> lHref, pHref, cHref, CHref;
	for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
		lHref[it->first] = it->second+"."+SP::SPEXT+".L";
		pHref[it->first] = it->second+"."+SP::SPEXT+".P";
		if (use_chunks) {
			cHref[it->first] = it->second+"."+SP::SPEXT+".iob";
			CHref[it->first] = it->second+"."+SP::SPEXT+".C";
		}
	}

	NIST nist;
	nist.doMetric(TGT, pfile_out, REF, pHref, SP::SPEXT+"-p", hOQ);
	if (USE_LEMMAS)
		nist.doMetric(TGT, lfile_out, REF, lHref, SP::SPEXT+"-l", hOQ);
	if (use_chunks) {
		nist.doMetric(TGT, cfile_out, REF, cHref, SP::SPEXT+"-iob", hOQ);
		nist.doMetric(TGT, Cfile_out, REF, CHref, SP::SPEXT+"-c", hOQ);
	}
}

void SP::remove_parse_plit_file(string input) {
	// description _ removes auxiliar files created for NERC computation
	string pfile = input+"."+SP::SPEXT+".P";
	string lfile = input+"."+SP::SPEXT+".L";
	string cfile = input+"."+SP::SPEXT+".iob";
	string Cfile = input+"."+SP::SPEXT+".C";

	if (Config::verbose) fprintf(stderr, "[SP] erasing SP auxiliar file [PLcC]...\n");

	string sys_aux;
	if ( exists(boost::filesystem::path(pfile)) ) { sys_aux = "rm -f "+pfile; system(sys_aux.c_str()); }
	if ( exists(boost::filesystem::path(lfile)) ) { sys_aux = "rm -f "+lfile; system(sys_aux.c_str()); }
	if ( exists(boost::filesystem::path(cfile)) ) { sys_aux = "rm -f "+cfile; system(sys_aux.c_str()); }
	if ( exists(boost::filesystem::path(Cfile)) ) { sys_aux = "rm -f "+Cfile; system(sys_aux.c_str()); }
}

void SP::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes SP scores (multiple references)
	set<string> rF;
	if (Config::LANG == Common::L_SPA or Config::LANG == Common::L_CAT) rF = SP::rSPspacat;
	else rF = SP::rSPeng;

	bool GO_ON, GO_NIST;
	GO_ON = GO_NIST = false;
	for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
		if (Config::Hmetrics.find(*it) != Config::Hmetrics.end()) {
			GO_ON = true;
            boost::regex re(".*NIST.*");
            boost::match_results<string::const_iterator> results;
            if (boost::regex_match(*it, results, re)) GO_NIST = true;
		}
	}

	if (GO_ON) {
		if (Config::verbose) fprintf(stderr, "%s\n", SP::SPEXT.c_str());

		int DO_METRICS, DO_NIST_METRICS;
		DO_METRICS = DO_NIST_METRICS = Config::remake;

        boost::regex re(".*NIST.*");

		if (!DO_METRICS) {
			for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
				string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+*it+"."+Common::XMLEXT;
				boost::filesystem::path p(reportXML);
				boost::filesystem::path p_gz(reportXML+"."+Common::GZEXT);
				if (Config::Hmetrics.find(*it) != Config::Hmetrics.end() and !exists(p) and !exists(p_gz)) {
					DO_METRICS = 1;
		            boost::match_results<string::const_iterator> results;
		            if (boost::regex_match(*it, results, re)) DO_NIST_METRICS = 1;
		        }
			}
		}
		if (DO_METRICS) {
			vector<sParsed> FDout(TESTBED::wc[TGT]);									// OJU!!!!
			FILE_parse_and_read(TESTBED::Hsystems[TGT], FDout);
			vector< map<string , double> > maxscores(TESTBED::wc[TGT]);					// OJU!!!!

			SC_ASIYA sc_asiya;

			for (map<string, string>::const_iterator it_r = TESTBED::Hrefs.begin(); it_r != TESTBED::Hrefs.end(); ++it_r) {
				//fprintf(stderr, "ref: [%s -> %s]\n", it->first.c_str(), it->second.c_str());
				vector<sParsed> FDref(TESTBED::wc[it_r->first]);
				FILE_parse_and_read(it_r->second, FDref);
				
				vector< map<string, double> > scores;
				FILE_compute_overlap_metrics(FDout, FDref, scores);

				for (set<string>::const_iterator it_m = rF.begin(); it_m != rF.end(); ++it_m) {
					if (Config::Hmetrics.find(*it_m) != Config::Hmetrics.end()) {
						double MAXSYS, SYS;
						vector<double> MAXSEGS, SEGS;
						get_segment_scores(maxscores, *it_m, 0, MAXSYS, MAXSEGS);
						get_segment_scores(scores, *it_m, 2, SYS, SEGS);
						for (int i = 0; i < SEGS.size(); ++i) {
							if (MAXSEGS[i] != Common::NOT_DEFINED) {
								if (SEGS[i] > MAXSEGS[i]) {
									if (scores[i].find(*it_m) != scores[i].end()) 
										maxscores[i][*it_m] = scores[i][*it_m];
								}
							}
							else
								maxscores[i][*it_m] = scores[i][*it_m];
						}
					}
				}

				if (GO_NIST and DO_NIST_METRICS) {
					FILE_parse_split(it_r->second);
				}
			}

				/*for (int i = 0; i < maxscores.size(); ++i) {
                        fprintf(stderr, "--- SCORES[%d] ---\n", i);
                        for(map<string, double>::const_iterator it = maxscores[i].begin(); it != maxscores[i].end(); ++it)
                            fprintf(stderr, "\t[%s -> %f]\n", it->first.c_str(), it->second);
                        fprintf(stderr, "-------------------\n");  
                }*/

			for (set<string>::const_iterator it_m = rF.begin(); it_m != rF.end(); ++it_m) {
			    boost::match_results<string::const_iterator> results;
		        if (Config::Hmetrics.find(*it_m) != Config::Hmetrics.end() and !boost::regex_match(*it_m, results, re)) {
		        	string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+*it_m+"."+Common::XMLEXT;
					if ( (!exists(boost::filesystem::path(report_xml)) and !exists(boost::filesystem::path(report_xml+"."+Common::GZEXT))) or Config::remake) {
						double SYS;
						vector<double> SEGS, d_scores, s_scores;
						get_segment_scores(maxscores, *it_m, 2, SYS, SEGS);
						TESTBED::get_seg_doc_scores(SEGS, 0, TGT, d_scores, s_scores);
						if (Config::O_STORAGE == 1) {
				    		sc_asiya.write_report(TGT, REF, *it_m, SYS, d_scores, s_scores);
			         		fprintf(stderr, "SC_ASIYA DOCUMENT %s CREATED\n", it_m->c_str());
			         	}
         	         	hOQ.save_hash_scores(*it_m, TGT, REF, SYS, d_scores, s_scores);
					}
		        }
			}

			if (GO_NIST and DO_NIST_METRICS) {
				FILE_parse_split(TESTBED::Hsystems[TGT]);
				FILE_compute_MultiNIST_metrics(TGT, REF, hOQ);
				remove_parse_plit_file(TESTBED::Hsystems[TGT]);
				for (map<string, string>::const_iterator it_r = TESTBED::Hrefs.begin(); it_r != TESTBED::Hrefs.end(); ++it_r)
					remove_parse_plit_file(it_r->second);
			}
		}
	}
}

			/*for (int i = 0; i < scores.size(); ++i) {
                            fprintf(stderr, "--- SCORES[%d] ---\n", i);
                            for(map<string, double>::const_iterator it = scores[i].begin(); it != scores[i].end(); ++it)
                                    fprintf(stderr, "\t[%s -> %f]\n", it->first.c_str(), it->second);
                            fprintf(stderr, "-------------------\n");  
                    }*/
                    
			/*fprintf(stderr, "--- FDout ---(%d)\n", (int)FDout.size());
			for (int i = 0; i < FDout[0].size(); ++i) {
				wParsed w_aux = FDout[0][i];
				cout << "FDout[" << i << "]:";
				fprintf(stderr, "FDout[%d](%d): ", i, (int)w_aux.size());
				for (int j = 0; j < w_aux.size(); ++j) 
					fprintf(stderr, " %s", w_aux[j].c_str());
				fprintf(stderr, "\n");
			}
			fprintf(stderr, "-------------\n");*/
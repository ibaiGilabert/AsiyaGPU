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
    ofstream o_file;
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
				istringstream buf1(str1), buf2(str2);
			    for(string token; getline(buf1, token, ' '); ) {
			    	l1.push_back(token);
			    	o_file << token;
			    }
			    for(string token; getline(buf2, token, ' '); ) {
			    	l2.push_back(token);
		    		o_file << token;
			    }
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
	string wplc_file = input+"."+SP::SPEXT+".wplc";
	string wpl_file = input+"."+SP::SPEXT+".wpl";
	string wp_file = input+"."+SP::SPEXT+".wp";
	string wc_file = input+"."+SP::SPEXT+".wc";

	//string L = Config::LANG;
	//string C = Config::CASE;

	if ( !exists(boost::filesystem::path(wc_file)) and !exists(boost::filesystem::path(wc_file+"."+Common::GZEXT)) ) {
		if ( !exists(boost::filesystem::path(wp_file)) and !exists(boost::filesystem::path(wp_file+"."+Common::GZEXT)) ) {
			string sys_aux = Common::GUNZIP+" "+wp_file+"."+Common::GZEXT;
			system(sys_aux.c_str());
		}
		string command = "cat "+ wp_file+" | java -Dfile.encoding=UTF-8 -Xmx1024m -cp "+Config::tools+"/"+SP::BIOS+"/output/classes/:"+ 
                             Config::tools+"/mill/output/classes:"+Config::tools+"/"+SP::BIOS+"/jars/maxent-2.3.0.jar:"+
                             Config::tools+"/"+SP::BIOS+"/jars/trove.jar:"+Config::tools+"/"+SP::BIOS+"/jars/antlr-2.7.5.jar:"+
                             Config::tools+"/$BIOS/jars/log4j.jar bios.chunker.Chunker"+
                             " --predict --data="+Config::tools+"/"+SP::BIOS+"/data/chunker/"+SP::rLANGBIOS[Config::LANG]+
                             " --model=conll.paum."+((Config::CASE == Common::CASE_CI)? "ci" : "cs")+".model"+
                             " --type=paum --case-sensitive="+((Config::CASE == Common::CASE_CI)? "false" : "true")+
                             " --log4j="+Config::tools+"/"+SP::BIOS+"/log4j.properties > "+wc_file+" 2> "+wc_file+".err";
        Common::execute_or_die(command, "[ERROR] problems running BIOS...");

        system( ("rm -f"+wc_file+".err").c_str() );
        string wpc_file = input+"."+SP::SPEXT+".wpc";
        // merging tagging + chunking
      	FILE_merge_BIOS(wp_file, wc_file, wpc_file);
		// merging tagging + lemma + chunking
		if ( !exists(boost::filesystem::path(wpl_file)) and !exists(boost::filesystem::path(wpl_file+"."+Common::GZEXT)) ) {
			system( (Common::GUNZIP+" "+wpl_file+"."+Common::GZEXT).c_str() );
		}
		FILE_merge_BIOS(wpl_file, wc_file, wpl_file);
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
	string lpath = Config::tools+"/"+SP::SVMT+"/models"+L+"/"+C+"/";
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


	string command = Config::tools+"/"+SP::SVMT+"/scripts/doSVMTtagger.sh 1 "+input+" "+wlp_file+" "+lpath+" 4 LRL 0 0 "+lblex+" 0";
		cout << "[SP]doSVMTagger: " << command << endl;
    Common::execute_or_die(command, "[ERROR] problems running SVMTtagger...");


exit(1);

	string conll_file = input+"."+SP::SPEXT+".conll";
	//string wpl_file = input+"."+SP::SPEXT+".wpl";
	string wp_file = input+"."+SP::SPEXT+".wp";

	ofstream wp_out_file(wp_file.c_str());
    if (!wp_out_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", wp_file.c_str()); exit(1); }

	//ofstream wpl_out_file(wpl_file.c_str());
    //if (!wpl_out_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", wpl_file.c_str()); exit(1); }

	ofstream conll_out_file(conll_file.c_str());
    if (!conll_out_file.is_open()) { fprintf(stderr, "couldn't open output file <%s>\n", conll_file.c_str()); exit(1); }

	int iter = 0;
	ifstream out_file(wlp_file.c_str());
	if (out_file) {
		string str;
		int line = 0;
		while ( getline(out_file, str) ) {
			istringstream iss(str);
			string w, l, p;
			iss >> w >> l >> p;
				cout << "line[" << line++ << "]: " << w << " " << l << " " << p << endl;
			wp_out_file << w << " " << p << endl;
			//conll_file << wcount << "\t" << w << "\t" << l << "\t" << p.substr(0, 1) << "\t" << p << "\t_" << endl;

			if (Config::verbose) {
				if ( (iter%10) == 0) fprintf(stderr, ".");
				if ( (iter%100) == 0) fprintf(stderr, "%d", iter);
			}

			++iter;
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
		string spfile = use_chunks ? input+"."+SP::SPEXT+".wplc" : input+"."+SP::SPEXT+".wpl";

		if ( !exists(boost::filesystem::path(spfile)) and !exists(boost::filesystem::path(spfile+"."+Common::GZEXT)) ) {
			string wpfile = input+"."+SP::SPEXT+".wp";
			string wplfile = input+"."+SP::SPEXT+".wpl";
			string conllfile = input+"."+SP::SPEXT+".conll";
			if (!exists(boost::filesystem::path(wpfile)) and !exists(boost::filesystem::path(wpfile+"."+Common::GZEXT))) {
	            //tokenizing + tagging via SVMTool (en, ca, es) or Berkeley (fr, de)
				if (Config::verbose) fprintf(stderr, "Running shallow-parsing [%s -> %s]\n", wpfile.c_str(), wpfile.c_str());

				int iter = 0;
				if (SP::rLANGSVM.find(Config::LANG) != SP::rLANGSVM.end()) {
					iter = FILE_parse_SVM(input);
				}
				else if (SP::rLANGBKLY.find(Config::LANG) != SP::rLANGBKLY.end()) {
					USE_LEMMAS = 0;
					iter = FILE_parse_BKLY(input);
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
			gz_aux = Common::GZIP+" "+wplfile;		system(gz_aux.c_str());
			gz_aux = Common::GZIP+" "+conllfile;	system(gz_aux.c_str());

		}
	}
	else { fprintf(stderr, "[ERROR] Shallow parser not available for '%s' language!!\n", Config::LANG.c_str()); exit(1); }
}

void SP::FILE_parse_and_read(string input) {
	// description _ reads "wplc or wpl" file, performing the shallow parsing (using SVMTool and BIOS) only if required
	//               (wplc -> TOKEN PoS LEMMA CHUNK)
	FILE_parse(input);
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

		if (!DO_METRICS) {
			for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
				string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+*it+"."+Common::XMLEXT;
				boost::filesystem::path p(reportXML);
				boost::filesystem::path p_gz(reportXML+"."+Common::GZEXT);
				if (Config::Hmetrics.find(*it) != Config::Hmetrics.end() and !exists(p) and !exists(p_gz)) {
					DO_METRICS = 1;
		            boost::regex re(".*NIST.*");
		            boost::match_results<string::const_iterator> results;
		            if (boost::regex_match(*it, results, re)) DO_NIST_METRICS = 1;
		        }
			}
		}
		if (DO_METRICS) {
			FILE_parse_and_read(TESTBED::Hsystems[TGT]);
		}

	}

}

#include "../include/CP.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

const string CP::SPATOOL = "collins";
const string CP::ENGTOOL = "reranking-parser";
const string CP::FRETOOL = "bonsai_v3.2";	// berkeley via bonsai -> remember to set the BKY and CLASSPATH variables
const string CP::GERTOOL = "berkeleyparser";	// berkeley
const string CP::CPEXT = "CP";
const string CP::CSEP = "__";
const string CP::EMPTY_ITEM = "*";
const int CP::SNTLEN_COLLINS = 199;
const int CP::SNTLEN_CHARNIAK = 399;
const int CP::MAXSTM_LENGTH = 9;

map<string, string> CP::create_rLANG() {
	map<string, string> rLANG;
	rLANG[Common::L_ENG] = "en";	rLANG[Common::L_SPA] = "es";	rLANG[Common::L_FRN] = "fr";	rLANG[Common::L_GER] = "de";
	return rLANG;
}
map<string, string> CP::rLANG = create_rLANG();


set<string> CP::create_rCPeng() {
	set<sstring> rCPeng;
	rCPeng.insert(CP::CPEXT+"-STM-1");		rCPeng.insert(CP::CPEXT+"-STM-2"); 		rCPeng.insert(CP::CPEXT+"-STM-3"); 		rCPeng.insert(CP::CPEXT+"-STM-4");
	rCPeng.insert(CP::CPEXT+"-STM-5"); 		rCPeng.insert(CP::CPEXT+"-STM-6"); 		rCPeng.insert(CP::CPEXT+"-STM-7"); 		rCPeng.insert(CP::CPEXT+"-STM-8");
	rCPeng.insert(CP::CPEXT+"-STM-9"); 		rCPeng.insert(CP::CPEXT+"-STMi-2"); 	rCPeng.insert(CP::CPEXT+"-STMi-3");
	rCPeng.insert(CP::CPEXT+"-STMi-4"); 	rCPeng.insert(CP::CPEXT+"-STMi-5"); 	rCPeng.insert(CP::CPEXT+"-STMi-6");
	rCPeng.insert(CP::CPEXT+"-STMi-7"); 	rCPeng.insert(CP::CPEXT+"-STMi-8"); 	rCPeng.insert(CP::CPEXT+"-STMi-9");
	rCPeng.insert(CP::CPEXT+"-Oc(ADJP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(ADVP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(CONJP)");
	rCPeng.insert(CP::CPEXT+"-Oc(INTJ)"); 	rCPeng.insert(CP::CPEXT+"-Oc(LST)"); 	rCPeng.insert(CP::CPEXT+"-Oc(NP)");
	rCPeng.insert(CP::CPEXT+"-Oc(O)"); 		rCPeng.insert(CP::CPEXT+"-Oc(PP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(PRT)");
	rCPeng.insert(CP::CPEXT+"-Oc(SBAR)"); 	rCPeng.insert(CP::CPEXT+"-Oc(UCP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(VP)");
	rCPeng.insert(CP::CPEXT+"-Oc(FRAG)"); 	rCPeng.insert(CP::CPEXT+"-Oc(NAC)"); 	rCPeng.insert(CP::CPEXT+"-Oc(NX)");
	rCPeng.insert(CP::CPEXT+"-Oc(PRN)"); 	rCPeng.insert(CP::CPEXT+"-Oc(QP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(RRC)");
	rCPeng.insert(CP::CPEXT+"-Oc(S)"); 		rCPeng.insert(CP::CPEXT+"-Oc(SINV)"); 	rCPeng.insert(CP::CPEXT+"-Oc(SQ)");
	rCPeng.insert(CP::CPEXT+"-Oc(WHADJP)"); rCPeng.insert(CP::CPEXT+"-Oc(WHADVP)"); rCPeng.insert(CP::CPEXT+"-Oc(WHNP)");
	rCPeng.insert(CP::CPEXT+"-Oc(WHPP)"); 	rCPeng.insert(CP::CPEXT+"-Oc(X)"); 		rCPeng.insert(CP::CPEXT+"-Op(CC)");
	rCPeng.insert(CP::CPEXT+"-Op(CD)"); 	rCPeng.insert(CP::CPEXT+"-Op(DT)"); 	rCPeng.insert(CP::CPEXT+"-Op(EX)");
	rCPeng.insert(CP::CPEXT+"-Op(FW)"); 	rCPeng.insert(CP::CPEXT+"-Op(IN)"); 	rCPeng.insert(CP::CPEXT+"-Op(JJ)");
	rCPeng.insert(CP::CPEXT+"-Op(JJR)"); 	rCPeng.insert(CP::CPEXT+"-Op(JJS)"); 	rCPeng.insert(CP::CPEXT+"-Op(LS)");
	rCPeng.insert(CP::CPEXT+"-Op(MD)"); 	rCPeng.insert(CP::CPEXT+"-Op(NN)"); 	rCPeng.insert(CP::CPEXT+"-Op(NNP)");
	rCPeng.insert(CP::CPEXT+"-Op(NNPS)"); 	rCPeng.insert(CP::CPEXT+"-Op(NNS)"); 	rCPeng.insert(CP::CPEXT+"-Op(PDT)");
	rCPeng.insert(CP::CPEXT+"-Op(POS)"); 	rCPeng.insert(CP::CPEXT+"-Op(PRP)"); 	rCPeng.insert(CP::CPEXT+"-Op(PRP\\$)");
	rCPeng.insert(CP::CPEXT+"-Op(RB)"); 	rCPeng.insert(CP::CPEXT+"-Op(RBR)"); 	rCPeng.insert(CP::CPEXT+"-Op(RBS)");
	rCPeng.insert(CP::CPEXT+"-Op(RP)"); 	rCPeng.insert(CP::CPEXT+"-Op(SYM)"); 	rCPeng.insert(CP::CPEXT+"-Op(TO)");
	rCPeng.insert(CP::CPEXT+"-Op(UH)"); 	rCPeng.insert(CP::CPEXT+"-Op(VB)"); 	rCPeng.insert(CP::CPEXT+"-Op(VBD)");
	rCPeng.insert(CP::CPEXT+"-Op(VBG)"); 	rCPeng.insert(CP::CPEXT+"-Op(VBN)"); 	rCPeng.insert(CP::CPEXT+"-Op(VBP)");
	rCPeng.insert(CP::CPEXT+"-Op(VBZ)"); 	rCPeng.insert(CP::CPEXT+"-Op(WDT)"); 	rCPeng.insert(CP::CPEXT+"-Op(WP)");
	rCPeng.insert(CP::CPEXT+"-Op(WP\\$)"); 	rCPeng.insert(CP::CPEXT+"-Op(WRB)"); 	rCPeng.insert(CP::CPEXT+"-Op(#)");
	rCPeng.insert(CP::CPEXT+"-Op(\\$)"); 	rCPeng.insert(CP::CPEXT+"-Op(\'\')"); 	rCPeng.insert(CP::CPEXT+"-Op(()");
	rCPeng.insert(CP::CPEXT+"-Op())"); 		rCPeng.insert(CP::CPEXT+"-Op(,)"); 		rCPeng.insert(CP::CPEXT+"-Op(.)"); 		rCPeng.insert(CP::CPEXT+"-Op(:)");
	rCPeng.insert(CP::CPEXT+"-Op(``)"); 	rCPeng.insert(CP::CPEXT+"-Op(J)"); 		rCPeng.insert(CP::CPEXT+"-Op(N)"); 		rCPeng.insert(CP::CPEXT+"-Op(P)");
	rCPeng.insert(CP::CPEXT+"-Op(R)"); 		rCPeng.insert(CP::CPEXT+"-Op(V)"); 		rCPeng.insert(CP::CPEXT+"-Op(W)"); 		rCPeng.insert(CP::CPEXT+"-Op(F)");
	rCPeng.insert(CP::CPEXT+"-Op(*)"); 		rCPeng.insert(CP::CPEXT+"-Oc(*)");
	return rCPeng;
}
const set<string> CP::rCPeng = create_rCPeng();

//POS-eng --->  ,, :, ., ``, '', $, #, -LRB-, -RRB-, CC, CD, DT, EX, IN, JJ, JJR, JJS, LS, LST, MD, NN, NNP, NNPS, NNS, PDT, POS, PRP, PRP$, RB, RBR, RBS, RP, SYM, TO, UH, VB, VBD, VBG, VBN, VBP, VBZ, WDT, WP, WP$, WRB
//PHRASE-eng ---> ADJP, ADVP, CONJP, FRAG, INTJ, LST, NAC, NP, NX, PP, PRN, PRT, QP, RRC, S, SBAR, SINV, SQ, UCP, VP, WHADJP, WHADVP, WHNP, WHPP, X

set<string> CP::create_rCPspacat() {
	set<string> rCPspacat;
	rCPspacat.insert(CP::CPEXT+"-STM-1"); 			rCPspacat.insert(CP::CPEXT+"-STM-2"); 			rCPspacat.insert(CP::CPEXT+"-STM-3");
	rCPspacat.insert(CP::CPEXT+"-STM-4"); 			rCPspacat.insert(CP::CPEXT+"-STM-5"); 			rCPspacat.insert(CP::CPEXT+"-STM-6");
	rCPspacat.insert(CP::CPEXT+"-STM-7"); 			rCPspacat.insert(CP::CPEXT+"-STM-8"); 			rCPspacat.insert(CP::CPEXT+"-STM-9");
	rCPspacat.insert(CP::CPEXT+"-STMi-2"); 			rCPspacat.insert(CP::CPEXT+"-STMi-3"); 			rCPspacat.insert(CP::CPEXT+"-STMi-4");
	rCPspacat.insert(CP::CPEXT+"-STMi-5"); 			rCPspacat.insert(CP::CPEXT+"-STMi-6"); 			rCPspacat.insert(CP::CPEXT+"-STMi-7");
	rCPspacat.insert(CP::CPEXT+"-STMi-8"); 			rCPspacat.insert(CP::CPEXT+"-STMi-9"); 			rCPspacat.insert(CP::CPEXT+"-Op(aop)");
	rCPspacat.insert(CP::CPEXT+"-Op(aos)"); 		rCPspacat.insert(CP::CPEXT+"-Op(aqn)"); 		rCPspacat.insert(CP::CPEXT+"-Op(aqp)");
	rCPspacat.insert(CP::CPEXT+"-Op(aqs)"); 		rCPspacat.insert(CP::CPEXT+"-Op(cc)"); 			rCPspacat.insert(CP::CPEXT+"-Op(cs)");
	rCPspacat.insert(CP::CPEXT+"-Op(dn)"); 			rCPspacat.insert(CP::CPEXT+"-Op(dp)"); 			rCPspacat.insert(CP::CPEXT+"-Op(ds)");
	rCPspacat.insert(CP::CPEXT+"-Op(F)"); 			rCPspacat.insert(CP::CPEXT+"-Op(i)"); 			rCPspacat.insert(CP::CPEXT+"-Op(n0)");
	rCPspacat.insert(CP::CPEXT+"-Op(nn)"); 			rCPspacat.insert(CP::CPEXT+"-Op(np)"); 			rCPspacat.insert(CP::CPEXT+"-Op(ns)");
	rCPspacat.insert(CP::CPEXT+"-Op(p0)"); 			rCPspacat.insert(CP::CPEXT+"-Op(pn)"); 			rCPspacat.insert(CP::CPEXT+"-Op(pp)");
	rCPspacat.insert(CP::CPEXT+"-Op(ps)"); 			rCPspacat.insert(CP::CPEXT+"-Op(rg)"); 			rCPspacat.insert(CP::CPEXT+"-Op(rn)");
	rCPspacat.insert(CP::CPEXT+"-Op(sps)"); 		rCPspacat.insert(CP::CPEXT+"-Op(v0g)"); 		rCPspacat.insert(CP::CPEXT+"-Op(v0n)");
	rCPspacat.insert(CP::CPEXT+"-Op(vpi)"); 		rCPspacat.insert(CP::CPEXT+"-Op(vpm)"); 		rCPspacat.insert(CP::CPEXT+"-Op(vpp)");
	rCPspacat.insert(CP::CPEXT+"-Op(vps)"); 		rCPspacat.insert(CP::CPEXT+"-Op(vsi)"); 		rCPspacat.insert(CP::CPEXT+"-Op(vsm)");
	rCPspacat.insert(CP::CPEXT+"-Op(vsp)"); 		rCPspacat.insert(CP::CPEXT+"-Op(vss)"); 		rCPspacat.insert(CP::CPEXT+"-Op(w)");
	rCPspacat.insert(CP::CPEXT+"-Op(z)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(conj)"); 		rCPspacat.insert(CP::CPEXT+"-Oc(coord)");
	rCPspacat.insert(CP::CPEXT+"-Oc(CP)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(data)"); 		rCPspacat.insert(CP::CPEXT+"-Oc(espec)");
	rCPspacat.insert(CP::CPEXT+"-Oc(gerundi)"); 	rCPspacat.insert(CP::CPEXT+"-Oc(gv)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(INC)");
	rCPspacat.insert(CP::CPEXT+"-Oc(infinitiu)"); 	rCPspacat.insert(CP::CPEXT+"-Oc(interjeccio)"); rCPspacat.insert(CP::CPEXT+"-Oc(morf)");
	rCPspacat.insert(CP::CPEXT+"-Oc(neg)"); 		rCPspacat.insert(CP::CPEXT+"-Oc(numero)"); 		rCPspacat.insert(CP::CPEXT+"-Oc(prep)");
	rCPspacat.insert(CP::CPEXT+"-Oc(relatiu)"); 	rCPspacat.insert(CP::CPEXT+"-Oc(s.)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(S)");
	rCPspacat.insert(CP::CPEXT+"-Oc(sa)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(sadv)"); 		rCPspacat.insert(CP::CPEXT+"-Oc(SBAR)");
	rCPspacat.insert(CP::CPEXT+"-Oc(sn)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(sp)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(TOP)");
	rCPspacat.insert(CP::CPEXT+"-Op(A)"); 			rCPspacat.insert(CP::CPEXT+"-Op(C)"); 			rCPspacat.insert(CP::CPEXT+"-Op(D)"); 		rCPspacat.insert(CP::CPEXT+"-Op(F)");
	rCPspacat.insert(CP::CPEXT+"-Op(I)"); 			rCPspacat.insert(CP::CPEXT+"-Op(N)"); 			rCPspacat.insert(CP::CPEXT+"-Op(P)"); 		rCPspacat.insert(CP::CPEXT+"-Op(S)");
	rCPspacat.insert(CP::CPEXT+"-Op(V)"); 			rCPspacat.insert(CP::CPEXT+"-Op(VA)"); 			rCPspacat.insert(CP::CPEXT+"-Op(VM)");
	rCPspacat.insert(CP::CPEXT+"-Op(VS)"); 			rCPspacat.insert(CP::CPEXT+"-Op(*)"); 			rCPspacat.insert(CP::CPEXT+"-Oc(*)");
	return rCPspacat;
}
const set<string> CP::rCPspacat = create_rCPspacat();

//rCPgerman.insert(CP::CPEXT+"-Oc(grup)") --- removed

//POS-spacat ---> aop, aos, aqn, aqp, aqs, cc, cs, dn, dp, ds, F, i, n0, nn, np, ns, p0, pn, pp, ps, rg, rn, sps, v0g, v0n, vpi, vpm, vpp, vps, vsi, vsm, vsp, vss, w, z
//PHRASE-spacat ---> conj, coord, CP, data, espec, gerundi, grup, gv, INC, infinitiu, interjeccio, morf, neg, numero, prep, relatiu, s., S, sa, sadv, SBAR, sn, sp, TOP


set<string> CP::create_rCPfrench() {
	set<string> rCPfrench;
	rCPfrench.insert(CP::CPEXT+"-STM-1"); 		rCPfrench.insert(CP::CPEXT+"-STM-2"); 		rCPfrench.insert(CP::CPEXT+"-STM-3");
	rCPfrench.insert(CP::CPEXT+"-STM-4"); 		rCPfrench.insert(CP::CPEXT+"-STM-5"); 		rCPfrench.insert(CP::CPEXT+"-STM-6");
	rCPfrench.insert(CP::CPEXT+"-STM-7"); 		rCPfrench.insert(CP::CPEXT+"-STM-8"); 		rCPfrench.insert(CP::CPEXT+"-STM-9");
	rCPfrench.insert(CP::CPEXT+"-STMi-2"); 		rCPfrench.insert(CP::CPEXT+"-STMi-3"); 		rCPfrench.insert(CP::CPEXT+"-STMi-4");
	rCPfrench.insert(CP::CPEXT+"-STMi-5"); 		rCPfrench.insert(CP::CPEXT+"-STMi-6"); 		rCPfrench.insert(CP::CPEXT+"-STMi-7");
	rCPfrench.insert(CP::CPEXT+"-STMi-8"); 		rCPfrench.insert(CP::CPEXT+"-STMi-9");
	rCPfrench.insert(CP::CPEXT+"-Oc(AP)"); 		rCPfrench.insert(CP::CPEXT+"-Oc(AdP)"); 	rCPfrench.insert(CP::CPEXT+"-Oc(NP)"); 
	rCPfrench.insert(CP::CPEXT+"-Oc(PP)"); 		rCPfrench.insert(CP::CPEXT+"-Oc(VN)"); 		rCPfrench.insert(CP::CPEXT+"-Oc(VPinf)"); 
	rCPfrench.insert(CP::CPEXT+"-Oc(VPpart)"); 	rCPfrench.insert(CP::CPEXT+"-Oc(SENT)"); 	rCPfrench.insert(CP::CPEXT+"-Oc(Sint)"); 
	rCPfrench.insert(CP::CPEXT+"-Oc(Srel)"); 	rCPfrench.insert(CP::CPEXT+"-Oc(Ssub)"); 	rCPfrench.insert(CP::CPEXT+"-Oc(*)");
	rCPfrench.insert(CP::CPEXT+"-Op(A)"); 		rCPfrench.insert(CP::CPEXT+"-Op(ADV)"); 	rCPfrench.insert(CP::CPEXT+"-Op(CC)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(CL)"); 		rCPfrench.insert(CP::CPEXT+"-Op(CS)"); 		rCPfrench.insert(CP::CPEXT+"-Op(D)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(ET)"); 		rCPfrench.insert(CP::CPEXT+"-Op(I)"); 		rCPfrench.insert(CP::CPEXT+"-Op(NC)");
	rCPfrench.insert(CP::CPEXT+"-Op(NP)"); 		rCPfrench.insert(CP::CPEXT+"-Op(P)"); 		rCPfrench.insert(CP::CPEXT+"-Op(PREF)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(PRO)"); 	rCPfrench.insert(CP::CPEXT+"-Op(V)"); 		rCPfrench.insert(CP::CPEXT+"-Op(PONCT)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(,)"); 		rCPfrench.insert(CP::CPEXT+"-Op(:)"); 		rCPfrench.insert(CP::CPEXT+"-Op(.)"); 
	rCPfrench.insert(CP::CPEXT+"-Op('')"); 		rCPfrench.insert(CP::CPEXT+"-Op(()"); 		rCPfrench.insert(CP::CPEXT+"-Op())"); 
	rCPfrench.insert(CP::CPEXT+"-Op(prs)"); 	rCPfrench.insert(CP::CPEXT+"-Op(N)"); 		rCPfrench.insert(CP::CPEXT+"-Op(C)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(Afs)"); 	rCPfrench.insert(CP::CPEXT+"-Op(PC)"); 		rCPfrench.insert(CP::CPEXT+"-Op(ND)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(X)"); 		rCPfrench.insert(CP::CPEXT+"-Op(p)"); 		rCPfrench.insert(CP::CPEXT+"-Op(Dmp)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(pr)"); 		rCPfrench.insert(CP::CPEXT+"-Op(ADVP)"); 	rCPfrench.insert(CP::CPEXT+"-Op(S)"); 
	rCPfrench.insert(CP::CPEXT+"-Op(*)");
	return rCPfrench;
}
const set<string> CP::rCPfrench = create_rCPfrench();

// PHRASE-french grammar --> 
//     AP (adjectival phrases)
//     AdP (adverbial phrases) 
//     NP (noun phrases)
//     PP (prepositional phrases)
//     VN (verbal nucleus)
//     VPinf (infinitive clauses)
//     VPpart (nonfinite clauses)
//     SENT (sentences)
//     Sint, Srel, Ssub (finite clauses)


// POS-french grammar -->
//     A (adjective)
//     ADV (adverb)
//     CC (coordinating conjunction)
//     CL (weak clitic pronoun)
//     CS (subordinating conjunction)
//     D (determiner)
//     ET (foreign word)
//     I (interjection)
//     NC (common noun)
//     NP (proper noun)
//     P (preposition)
//     PREF (prefix)
//     PRO (strong pronoun)
//     V (verb)
//     PONCT (punctuation mark)
//     , : . " -LRB- -RRB-
//     prs N C Afs PC ND X p Dmp pr ADVP S (?)

set<string> CP::create_rCPgerman() {
	set<string> rCPgerman;
	rCPgerman.insert(CP::CPEXT+"-STM-1"); 			rCPgerman.insert(CP::CPEXT+"-STM-2"); 		rCPgerman.insert(CP::CPEXT+"-STM-3");
	rCPgerman.insert(CP::CPEXT+"-STM-4"); 			rCPgerman.insert(CP::CPEXT+"-STM-5"); 		rCPgerman.insert(CP::CPEXT+"-STM-6");
	rCPgerman.insert(CP::CPEXT+"-STM-7"); 			rCPgerman.insert(CP::CPEXT+"-STM-8"); 		rCPgerman.insert(CP::CPEXT+"-STM-9");
	rCPgerman.insert(CP::CPEXT+"-STMi-2"); 			rCPgerman.insert(CP::CPEXT+"-STMi-3"); 		rCPgerman.insert(CP::CPEXT+"-STMi-4");
	rCPgerman.insert(CP::CPEXT+"-STMi-5"); 			rCPgerman.insert(CP::CPEXT+"-STMi-6"); 		rCPgerman.insert(CP::CPEXT+"-STMi-7");
	rCPgerman.insert(CP::CPEXT+"-STMi-8"); 			rCPgerman.insert(CP::CPEXT+"-STMi-9"); 
	rCPgerman.insert(CP::CPEXT+"-Oc(S)"); 			rCPgerman.insert(CP::CPEXT+"-Oc(NP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(PP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(CNP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(CS)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(VP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(CVP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(ISU)"); 	rCPgerman.insert(CP::CPEXT+"-Oc(AP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(PSEUDO)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(MPN)"); 	rCPgerman.insert(CP::CPEXT+"-Oc(CAP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(CAVP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(CO)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(AVP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(CPP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(DP)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(---CJ)");
	rCPgerman.insert(CP::CPEXT+"-Oc(CAC)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(NM)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(CVZ)");
	rCPgerman.insert(CP::CPEXT+"-Oc(QL)"); 			rCPgerman.insert(CP::CPEXT+"-Oc(MTA)"); 	rCPgerman.insert(CP::CPEXT+"-Oc(CH)");
	rCPgerman.insert(CP::CPEXT+"-Oc(AA)"); 			rCPgerman.insert(CP::CPEXT+"-Oc(VZ)"); 		rCPgerman.insert(CP::CPEXT+"-Oc(CCP)");
	rCPgerman.insert(CP::CPEXT+"-Oc(*)");
	rCPgerman.insert(CP::CPEXT+"-Op(\\$*LRB*)");	rCPgerman.insert(CP::CPEXT+"-Op(\\$,)"); 	rCPgerman.insert(CP::CPEXT+"-Op(\\$.)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(*T1*)"); 		rCPgerman.insert(CP::CPEXT+"-Op(*T2*)"); 	rCPgerman.insert(CP::CPEXT+"-Op(*T3*)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(*T4*)"); 		rCPgerman.insert(CP::CPEXT+"-Op(*T5*)"); 	rCPgerman.insert(CP::CPEXT+"-Op(*T6*)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(*T7*)"); 		rCPgerman.insert(CP::CPEXT+"-Op(*T8*)"); 	rCPgerman.insert(CP::CPEXT+"-Op(--)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(ADJA)"); 		rCPgerman.insert(CP::CPEXT+"-Op(ADJD)"); 	rCPgerman.insert(CP::CPEXT+"-Op(ADV)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(APPO)"); 		rCPgerman.insert(CP::CPEXT+"-Op(APPR)"); 	rCPgerman.insert(CP::CPEXT+"-Op(APPRART)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(APZR)"); 		rCPgerman.insert(CP::CPEXT+"-Op(ART)"); 	rCPgerman.insert(CP::CPEXT+"-Op(CARD)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(FM)"); 			rCPgerman.insert(CP::CPEXT+"-Op(ITJ)"); 	rCPgerman.insert(CP::CPEXT+"-Op(KOKOM)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(KON)"); 		rCPgerman.insert(CP::CPEXT+"-Op(KOUI)"); 	rCPgerman.insert(CP::CPEXT+"-Op(KOUS)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(NE)"); 			rCPgerman.insert(CP::CPEXT+"-Op(NN)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PDAT)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PDS)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PIAT)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PIDAT)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PIS)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PPER)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PPOSAT)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PPOSS)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PRELAT)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PRELS)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PRF)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PROAV)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PTKA)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PTKANT)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PTKNEG)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PTKVZ)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PTKZU)"); 		rCPgerman.insert(CP::CPEXT+"-Op(PWAT)"); 	rCPgerman.insert(CP::CPEXT+"-Op(PWAV)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(PWS)"); 		rCPgerman.insert(CP::CPEXT+"-Op(TRUNC)"); 	rCPgerman.insert(CP::CPEXT+"-Op(VAFIN)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(VAIMP)"); 		rCPgerman.insert(CP::CPEXT+"-Op(VAINF)"); 	rCPgerman.insert(CP::CPEXT+"-Op(VAPP)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(VMFIN)"); 		rCPgerman.insert(CP::CPEXT+"-Op(VMINF)"); 	rCPgerman.insert(CP::CPEXT+"-Op(VMPP)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(VVFIN)"); 		rCPgerman.insert(CP::CPEXT+"-Op(VVIMP)"); 	rCPgerman.insert(CP::CPEXT+"-Op(VVINF)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(VVIZU)"); 		rCPgerman.insert(CP::CPEXT+"-Op(VVPP)"); 	rCPgerman.insert(CP::CPEXT+"-Op(XY)"); 
	rCPgerman.insert(CP::CPEXT+"-Op(*)"); 
	return rCPgerman;
}
const set<string> CP::rCPgerman = create_rCPgerman();

// PHRASE german grammar --> S NP PP CNP CS VP CVP ISU AP PSEUDO MPN CAP CAVP CO AVP CPP DL ---CJ CAC NM CVZ QL MTA CH AA VZ CCP
// POS german grammar --> $*LRB* $, $. *T1* *T2* *T3* *T4* *T5* *T6* *T7* *T8* -- ADJA ADJD ADV APPO APPR APPRART APZR ART CARD FM ITJ KOKOM KON KOUI KOUS NE NN PDAT PDS PIAT PIDAT PIS PPER PPOSAT PPOSS PRELAT PRELS PRF PROAV PTKA PTKANT PTKNEG PTKVZ PTKZU PWAT PWAV PWS TRUNC VAFIN VAIMP VAINF VAPP VMFIN VMINF VMPP VVFIN VVIMP VVINF VVIZU VVPP XY 


void CP::prepare4charniak(string input, string output) {
	// description _ responsible for adapting input file to a format
	//               that's convenient for Charniak's parser (<s> ... </s>)
	ofstream out_file(output.c_str());
	if (!out_file.is_open()) { fprintf(stderr, "couldn't open file: %s\n", output.c_str()); exit(1); }

	ifstream in_file(input.c_str());
	if (in_file) {
		string str;
	 	boost::match_results<string::const_iterator> results;
		while( getline(in_file, str) ) {
			if (str.empty())
				str = CP::EMPTY_ITEM+" .";
			else if (boost::regex_match(str, results, Common::reSPECIAL_CHAR) or (boost::regex_match(str, results, Common::reCP4charniak1))
				str = CP::EMPTY_ITEM+" "+str;
			else {	//check sentence length
				vector<string> L;
				boost::split(L, str, boost::is_any_of("\t "));
				if (L.size() > CP::SNTLEN_CHARNIAK) {
					while (L.size() > CP::SNTLEN_CHARNIAK) L.pop_back();
					str = L[0];
					for (int k = 1; k < L.size(); ++k) str += " "+L[k];
				}
				str = boost::regex_replace(str, Common::reCP4charniak2, " -mgbLRB- ");
				str = boost::regex_replace(str, Common::reCP4charniak3, " -mgbRRB- ");
				str = boost::regex_replace(str, Common::reLEFT_PAR, "-lrb-");
				str = boost::regex_replace(str, Common::reRIGTH_PAR, "-rrb-");
				str = boost::regex_replace(str, Common::reCP4charniak4, " ( ");
				str = boost::regex_replace(str, Common::reCP4charniak5, " ) ");
			}
			out_file << "<s> " << str << " <s>" << endl;
		}
		out_file.close();
		in_file.close();
	}
    else { fprintf(stderr, "couldn't open file: %s\n", input.c_str()); exit(1); }
}

void CP::read_CHARNIAK_BERKELEY_parsing(string input, string CPfile, string L) {
	// description _ responsible for reading Charniak's parser output into memory
	if (!exists(boost::filesystem::path(CPfile)) and exists(boost::filesystem::path(CPfile+"."+Common::GZEXT))) {
		string sys_aux = Common::GUNZIP+" "+CPfile+"."+Common::GZEXT;
		system(sys_aux.c_str());
	}

	ifstream IN(input.c_str());
	if (!IN.is_open()) { fprintf(stderr, "couldn't open file: %s\n", input.c_str()); exit(1); }

	ifstream CP(CPfile.c_str());
	if (CP) {
		string line;
		boost::match_results<string::const_iterator> results;
		while( getline(CP, line) ) {
			if (L == Common::L_FRN or L == Common::L_GER) {
          		// remove extra root that favors higher scores in BERKELEY PARSING
				str = boost::regex_replace(str, Common::reCPread_charniak1, "(ROOT");
				str = boost::regex_replace(str, Common::reCPread_charniak2, ")");
			}

			string in;
			getline(IN, in);
			TreeNode tree;
			tree.n = "*START*";
			//tree.node.resize(2);		tree.node[0] = "*START*";	tree.node[1] = "0";
		 	if (!in.empty() or boost::regex_match(in, results, Common::reSPECIAL_CHAR)) {
				vector<string> entry, segment;
				boost::split(entry, line, boost::is_any_of("\t "));
				boost::split(segment, in, boost::is_any_of("\t "));
				int segidx = 0;
				int depth = 0;
				TreeNode root = tree;
				for(int i = 0; i < entry.size(); ++i) {
					if (boost::regex_match(entry[i], results, Common::reCPopen_tag)) {
						string tag = entry[i];	tag = boost::regex_replace(tag, Common::reLEFT_PAR, "");
						TreeNode node;
						node.n = tag;
						node.child = &root;
						root = node;
						++depth;
					}
					else if (boost::regex_match(entry[i], results, Common::reCPclose_tag)) {
						if (segidx < segment.size() && boost::regex_match(segment[segidx], results, Common::reRIGHT_PAR)) {	// remove ) in the lexical entry
							string newtok = segment[segidx];
							newtok = boost::regex_replace(newtok, Common::reRIGHT_PAR, "*RRB*");
//TORNAR AQUI
						}
					}

				}
		 	}
		}

	}
    else { fprintf(stderr, "couldn't open file: %s\n", CPfile.c_str()); exit(1); }
}

//my $Fout = CP::parse_FULL($tools, $L, $C, $out, $parser, $verbose);
void CP::parse_FULL(string input, string L, string C, vector<sParsed> &FDout) {
	// description _ responsible for FULL PARSING (by calling Charniak-Johnson's
	//                                             MaxEnt reranking parser)
	//               <s> sentence </s>  ->  (parse_tree)
	string CPfile = input+"."CP::CPEXT;
	FILE;

	if (CP::LANG.count(L)) {
		if (L == Common::L_ENG) {
			if (!exists(boost::filesystem::path(CPfile)) and !exists(boost::filesystem::path(CPfile+"."+Common::GZEXT))) {
				string inputS = input+"."+CP::CPEXT+".SS";
				prepare4charniak(input, inputS);
				// -K to avoid tokenization
				string exe = "cd "+Common::DATA_PATH+"; "+Config::tools+"/"+CP::ENGTOOL+"/first-stage/PARSE/parseIt -l999 -N50 -K "+Config::tools+"/"+CP::ENGTOOL+"/first-stage/DATA/EN/ "+SinputS+" | "+
					Config::tools"/"+CP::ENGTOOL+"/second-stage/programs/features/best-parses -l "+Config::tools+"/"+CP::ENGTOOL+"/second-stage/models/ec50spfinal/features.gz "+
					Config::tools+"/"+CP::ENGTOOL+"/second-stage/models/ec50spfinal/cvlm-l1c10P1-weights.gz > "+CPfile+" 2> /dev/null";
				Common::execute_or_die(exe, "[ERROR] problems running $L constituency parser...");
				
				string sys_aux = "rm -f "+inputS;
				system(sys_aux.c_str());
			}
			read_CHARNIAK_BERKELEY_parsing(input, CPfile, L, FILE);
		}
	}

}












void CP::doMetric(string TGT, string REF, string prefix, Scores &hOQ) {
	// description _ computes CP scores (multiple references)
	set<string> rF;
	if (Config::LANG == Common::L_SPA)
		rf = CP::rCPspacat;
	else if (Config::LANG == Common::L_FRN)
		rf = CP::rCPfrench;
	else if (Config::LANG == Common::L_GER)
		rf = CP::rCPgerman;
	else
		rf = CP::rCPeng;

	bool GO_ON = false;
	for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
		if (Config::Hmetrics.find(*it) != Config::Hmetrics.end())
			GO_ON = true;
    }

	if (GO_ON) {
		if (Config::verbose) fprintf(stderr, "%s\n", CP::CPEXT.c_str());
		bool DO_METRICS = Config::remake;

		if (!DO_METRICS) {
			for (set<string>::const_iterator it = rF.begin(); it != rF.end(); ++it) {
				string reportXML = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+*it+"."+Common::XMLEXT;
				if (Config::Hmetrics.count(*it) and !exists(boost::filesystem::path(reportXML)) and !exists(boost::filesystem::path(reportXML+"."+Common::GZEXT))) {
					DO_METRICS = true;
		        }
			}
		}

		if (DO_METRICS) {
			vector<sParsed> FDout(TESTBED::wc[TGT]);									// OJU!!!!
			parse_FULL(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE, FDout);


			vector< map<string , double> > maxscores(TESTBED::wc[TGT]);					// OJU!!!!

			SC_ASIYA sc_asiya;

			for (map<string, string>::const_iterator it_r = TESTBED::Hrefs.begin(); it_r != TESTBED::Hrefs.end(); ++it_r) {
				//fprintf(stderr, "ref: [%s -> %s]\n", it->first.c_str(), it->second.c_str());
				vector<sParsed> FDref(TESTBED::wc[it_r->first]);
				FILE_parse_and_read(it_r->second, Config::LANG, Config::CASE, FDref);
				
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
					FILE_parse_split(it_r->second, Config::LANG, Config::CASE);
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
		        if (Config::Hmetrics.find(*it_m) != Config::Hmetrics.end() and !boost::regex_match(*it_m, results, Common::reSP_NIST)) {
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
				FILE_parse_split(TESTBED::Hsystems[TGT], Config::LANG, Config::CASE);
				FILE_compute_MultiNIST_metrics(TGT, REF, hOQ);
				remove_parse_plit_file(TESTBED::Hsystems[TGT]);
				for (map<string, string>::const_iterator it_r = TESTBED::Hrefs.begin(); it_r != TESTBED::Hrefs.end(); ++it_r)
					remove_parse_plit_file(it_r->second);
			}
		}
	}
}
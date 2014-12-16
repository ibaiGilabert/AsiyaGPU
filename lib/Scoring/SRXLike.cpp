#include "../include/SR.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


const string SRXLike::SREXTT = "SR";
const string SRXLike::XLike = "xlike/runxlikeparser.sh";

set<string> SR::create_rSRspacat() {
	set<string> rSRspacat;
	rSRspacat.insert(SRXLike::SREXT+"-Nv"); rSRspacat.insert(SRXLike::SREXT+"-Ov"); rSRspacat.insert(SRXLike::SREXT+"-Or"); rSRspacat.insert(SRXLike::SREXT+"-Orv");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Mrv(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Orv(*)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Orv(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Mr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Mr(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Or(*)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A0)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A1)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A2)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A3)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A4)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A5)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A6)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A7)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(A8)"); rSRspacat.insert(SRXLike::SREXT+"-Or(A9)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-LOC)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(AM-TMP)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-MNR)"); rSRspacat.insert(SRXLike::SREXT+"-Or(AM-ADV)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Attribute)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Beneficiary)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Cause)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Destination)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Final_State)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Initial_State)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Experiencer)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Extent)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Goal)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Instrument)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Location)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Initial_Location)");
	rSRspacat.insert(SRXLike::SREXT+"-Or(Patient)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Source)"); rSRspacat.insert(SRXLike::SREXT+"-Or(Theme)");

	rSRspacat.insert(SRXLike::SREXT+"-Ol"); rSRspacat.insert(SRXLike::SREXT+"-Or(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Or(*)_i");
	rSRspacat.insert(SRXLike::SREXT+"-Mr(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Mr(*)_i"); rSRspacat.insert(SRXLike::SREXT+"-Orv(*)_b");
	rSRspacat.insert(SRXLike::SREXT+"-Orv(*)_i"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)_b"); rSRspacat.insert(SRXLike::SREXT+"-Mrv(*)_i");
	rSRspacat.insert(SRXLike::SREXT+"-Or_b"); rSRspacat.insert(SRXLike::SREXT+"-Or_i"); rSRspacat.insert(SRXLike::SREXT+"-Orv_b");
	rSRspacat.insert(SRXLike::SREXT+"-Orv_i");
	rSRspacat.insert(SRXLike::SREXT+"-Pr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Rr(*)"); rSRspacat.insert(SRXLike::SREXT+"-Fr(*)");
	rSRspacat.insert(SRXLike::SREXT+"-MPr(*)"); rSRspacat.insert(SRXLike::SREXT+"-MRr(*)"); rSRspacat.insert(SRXLike::SREXT+"-MFr(*)");
	rSRspacat.insert(SRXLike::SREXT+"-Ora"); rSRspacat.insert(SRXLike::SREXT+"-Mra(*)"); rSRspacat.insert(SRXLike::SREXT+"-Ora(*)");
	return rSRspacat;
}
set<string> SR::rSRspacat = create_rSRspacat();
IDIR = /usr/include/libxml2

CC		= g++
CFLAGS = -I$(IDIR)
LDFLAGS	= -lboost_system -lboost_filesystem -lboost_regex -lboost_serialization -lxml2 -lgomp

all: Asiya

Asiya: Asiya.o Config.o Common.o Core.o Scores.o Process.o BLEU.o NIST.o GTM.o METEOR.o ROUGE.o NGRAM.o Overlap.o ESA.o TER.o ULC.o TESTBED.o TB_FORMAT.o TB_NIST.o TB_RAW.o SC_FORMAT.o SC_ASIYA.o SC_NIST.o SC_RAW.o
	g++ -o ../sample/Asiya Asiya.o Config.o Common.o Core.o Scores.o Process.o BLEU.o NIST.o GTM.o METEOR.o ROUGE.o NGRAM.o Overlap.o ESA.o TER.o ULC.o TESTBED.o TB_FORMAT.o TB_NIST.o TB_RAW.o SC_FORMAT.o SC_ASIYA.o SC_NIST.o SC_RAW.o $(LDFLAGS) $(CFLAGS)

Asiya.o: Asiya.cpp
	g++ -c Asiya.cpp $(CFLAGS)

Config.o: Config.hpp Config.cpp
	g++ -c Config.cpp $(CFLAGS)

Common.o: Common.hpp Common.cpp
	g++ -c Common.cpp

Core.o: include/Core.hpp Scoring/Core.cpp
	g++ -c Scoring/Core.cpp $(CFLAGS)

Scores.o: include/Scores.hpp Scoring/Scores.cpp
	g++ -c Scoring/Scores.cpp $(CFLAGS)

Process.o: include/Process.hpp Scoring/Process.cpp
	g++ -c Scoring/Process.cpp $(CFLAGS)

BLEU.o: include/BLEU.hpp Scoring/BLEU.cpp
	g++ -c Scoring/BLEU.cpp $(CFLAGS)

NIST.o: include/NIST.hpp Scoring/NIST.cpp
	g++ -c Scoring/NIST.cpp $(CFLAGS)

GTM.o: include/GTM.hpp Scoring/GTM.cpp
	g++ -c Scoring/GTM.cpp $(CFLAGS)

METEOR.o: include/METEOR.hpp Scoring/METEOR.cpp
	g++ -c Scoring/METEOR.cpp $(CFLAGS)

ROUGE.o: include/ROUGE.hpp Scoring/ROUGE.cpp
	g++ -c Scoring/ROUGE.cpp $(CFLAGS)

NGRAM.o: include/NGRAM.hpp Scoring/NGRAM.cpp
	g++ -c Scoring/NGRAM.cpp $(CFLAGS)

Overlap.o: include/Overlap.hpp Scoring/Overlap.cpp
	g++ -c Scoring/Overlap.cpp $(CFLAGS)

ESA.o: include/ESA.hpp Scoring/ESA.cpp
	g++ -c Scoring/ESA.cpp $(CFLAGS)

TER.o: include/TER.hpp Scoring/TER.cpp
	g++ -c Scoring/TER.cpp $(CFLAGS)

ULC.o: include/ULC.hpp Scoring/ULC.cpp
	g++ -c Scoring/ULC.cpp $(CFLAGS)

TESTBED.o: include/TESTBED.hpp InOut/TESTBED.cpp
	g++ -c InOut/TESTBED.cpp $(CFLAGS)

TB_FORMAT.o: include/TB_FORMAT.hpp InOut/TB_FORMAT.cpp
	g++ -c InOut/TB_FORMAT.cpp $(CFLAGS)

TB_NIST.o: include/TB_NIST.hpp InOut/TB_NIST.cpp
	g++ -c InOut/TB_NIST.cpp $(CFLAGS)

TB_RAW.o: include/TB_RAW.hpp InOut/TB_RAW.cpp
	g++ -c InOut/TB_RAW.cpp $(CFLAGS)

SC_FORMAT.o: include/SC_FORMAT.hpp InOut/SC_FORMAT.cpp
	g++ -c InOut/SC_FORMAT.cpp $(CFLAGS)

SC_ASIYA.o: include/SC_ASIYA.hpp InOut/SC_ASIYA.cpp
	g++ -c InOut/SC_ASIYA.cpp $(CFLAGS)

SC_NIST.o: include/SC_NIST.hpp InOut/SC_NIST.cpp
	g++ -c InOut/SC_NIST.cpp $(CFLAGS)

SC_RAW.o: include/SC_RAW.hpp InOut/SC_RAW.cpp
	g++ -c InOut/SC_RAW.cpp $(CFLAGS)

clean:
	rm *.o ../sample/Asiya

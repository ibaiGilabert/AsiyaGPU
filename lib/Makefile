IDIR = /usr/include/libxml2

CC		= g++
CFLAGS = -I$(IDIR)
LDFLAGS	= -lboost_system -lboost_filesystem -lboost_regex -lxml2 -lgomp

all: Asiya

Asiya: Asiya.o Config.o Common.o Core.o Scores.o BLEU.o NIST.o BLEUNIST.o GTM.o METEOR.o ROUGE.o TER.o TESTBED.o NISTXML.o RAW.o IQXML.o
	g++ -o ../sample/Asiya Asiya.o Config.o Common.o Core.o Scores.o BLEU.o NIST.o BLEUNIST.o GTM.o METEOR.o ROUGE.o TER.o TESTBED.o NISTXML.o RAW.o IQXML.o $(LDFLAGS) $(CFLAGS)

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

BLEU.o: include/BLEU.hpp Scoring/BLEU.cpp
	g++ -c Scoring/BLEU.cpp $(CFLAGS)

NIST.o: include/NIST.hpp Scoring/NIST.cpp
	g++ -c Scoring/NIST.cpp $(CFLAGS)

BLEUNIST.o: include/BLEUNIST.hpp Scoring/BLEUNIST.cpp
	g++ -c Scoring/BLEUNIST.cpp $(CFLAGS)

GTM.o: include/GTM.hpp Scoring/GTM.cpp
	g++ -c Scoring/GTM.cpp $(CFLAGS)

METEOR.o: include/METEOR.hpp Scoring/METEOR.cpp
	g++ -c Scoring/METEOR.cpp $(CFLAGS)

ROUGE.o: include/ROUGE.hpp Scoring/ROUGE.cpp
	g++ -c Scoring/ROUGE.cpp $(CFLAGS)

TER.o: include/TER.hpp Scoring/TER.cpp
	g++ -c Scoring/TER.cpp $(CFLAGS)

TESTBED.o: include/TESTBED.hpp InOut/TESTBED.cpp
	g++ -c InOut/TESTBED.cpp $(CFLAGS)

NISTXML.o: include/NISTXML.hpp InOut/NISTXML.cpp
	g++ -c InOut/NISTXML.cpp $(CFLAGS)

RAW.o: include/RAW.hpp InOut/RAW.cpp
	g++ -c InOut/RAW.cpp $(CFLAGS)

IQXML.o: include/IQXML.hpp InOut/IQXML.cpp
	g++ -c InOut/IQXML.cpp $(CFLAGS)

clean:
	rm *.o ../sample/Asiya

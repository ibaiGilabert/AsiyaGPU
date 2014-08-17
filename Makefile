IDIR = /usr/include/libxml2

CC		= g++
CFLAGS = -I$(IDIR)
LDFLAGS	= -lboost_system -lboost_filesystem -lboost_regex -lgomp -lxml2

all: Asiya

Asiya: Asiya.o Config.o Common.o Core.o Scores.o BLEU.o NIST.o BLEUNIST.o NISTXML.o NISTSCR.o
	g++ -o Asiya Asiya.o Config.o Common.o Core.o Scores.o BLEU.o NIST.o BLEUNIST.o NISTXML.o NISTSCR.o $(LDFLAGS) $(CFLAGS)

Asiya.o: Asiya.cpp
	g++ -c Asiya.cpp $(CFLAGS)

Config.o: Config.hpp Config.cpp
	g++ -c Config.cpp $(CFLAGS)

Common.o: Common.hpp Common.cpp
	g++ -c Common.cpp

Core.o: Core.hpp Core.cpp
	g++ -c Core.cpp $(CFLAGS)

Scores.o: Scores.hpp Scores.cpp
	g++ -c Scores.cpp

BLEU.o: BLEU.hpp BLEU.cpp
	g++ -c BLEU.cpp $(CFLAGS)

NIST.o: NIST.hpp NIST.cpp
	g++ -c NIST.cpp $(CFLAGS)

BLEUNIST.o: BLEUNIST.hpp BLEUNIST.cpp
	g++ -c BLEUNIST.cpp $(CFLAGS)

NISTXML.o: NISTXML.hpp NISTXML.cpp
	g++ -c NISTXML.cpp $(CFLAGS)

NISTSCR.o: NISTSCR.hpp NISTSCR.cpp
	g++ -c NISTSCR.cpp

clean:
	rm *.o Asiya
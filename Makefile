CC		= g++
LDFLAGS	= -lboost_system -lboost_filesystem -lboost_regex

all: Asiya

Asiya: Asiya.o Config.o Common.o NISTXML.o
	g++ -o Asiya Asiya.o Config.o Common.o NISTXML.o $(LDFLAGS)

Asiya.o: Asiya.cpp
	g++ -c Asiya.cpp

Config.o: Config.hpp Config.cpp
	g++ -c Config.cpp

Common.o: Common.hpp Common.cpp
	g++ -c Common.cpp

NISTXML.o: NISTXML.hpp NISTXML.cpp
	g++ -c NISTXML.cpp

clean:
	rm *.o Asiya
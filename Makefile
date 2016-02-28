
CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -O0
TAR = tar
TARFLAGS = -cvf
TARNAME = ex1.tar
TARSRCS = osm.cpp Makefile README

all: osm.o
	ar rcs libosm.a osm.o

osm.o: osm.cpp osm.h
	$(CC) $(CFLAGS) osm.cpp -c

clean:
	-rm osm.o libosm.a ex1.tar

tar:
	$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)


.PHONY: clean, all

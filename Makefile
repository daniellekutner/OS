CC=gcc

LIBSRC = osm.cpp
LIBOBJ=$(LIBSRC:.c=.o)
CFLAGS = -Wall -g $(INCS)
TAR=tar
TARGETS = $(OSMLIB)
TARFLAGS = -cvf
TARNAME = ex1.tar
TARSRCS = Makefile README

all: $(TARGETS) 


$(TARGETS): $(LIBOBJ)



clean:
$(RM) $(TARGETS) $(OSMLIB) $(OBJ) $(LIBOBJ) *~ *core


depend:

makedepend -- $(CFLAGS) -- $(SRC) $(LIBSRC)

tar:

$(TAR) $(TARFLAGS) $(TARNAME) $(TARSRCS)
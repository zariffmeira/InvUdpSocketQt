IDIR   = include
ODIR   = src/obj
LDIR   = lib
SRDIR  = src
BINDIR = bin

CFLAGS = -I $(IDIR) -std=c++11
CXX    = g++
LIBS   = -lm

_DEPS = inverter.h inverterSocket.h
DEPS  = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ  = main.o inverter.o inverterSocket.o
OBJ   = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(BINDIR)/inverter: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

run:
	@ cd bin; ./inverter
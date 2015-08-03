IDIR =../include
CC=gcc
CFLAGS=-O2 -O3 -g -Wall -pedantic -std=c11 -I$(IDIR)

ODIR=obj

LIBS=-lm -L/usr/local/lib -lcblas\
	 /usr/local/lib/libsundials_cvode.a \
	 /usr/local/lib/libsundials_nvecserial.a


_DEPS = common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o solver.o model.o auxiliary.o initialization.o memory.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

net-sim: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm net-sim

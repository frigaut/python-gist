# $Id: Makefile 31967 2011-02-22 05:19:19Z mdcb $
SHELL=/bin/sh
MAKE=make
include ../Make.cfg

CFLAGS=$(COPTIONS) -I. -I../play
COPTIONS=$(COPT) $(Y_CFLAGS)
COPT=$(COPT_DEFAULT)

CBLASY=cblasy.o

# to use external blas (e.g.- atlas), comment above, uncomment below
# also need to add -lblas (or whatever) to MATHLIB in ../Make.cfg
#CFLAGS=$(COPTIONS) -DUSE_CBLAS -DCBLAS_INDEX=int -I.
#CBLASY=

OBJS=dlamc3.o dgyor.o dgtsv.o dgesv.o dgecon.o dgels.o dgelss.o \
  dbdsqr.o dlasr.o dgesvd.o dgesv2.o $(CBLASY)

all: $(OBJS)

libyor: $(OBJS)
	touch $@

oinsert: $(OBJS) ../yorick/libyor.a
	$(AR) r ../yorick/libyor.a $(OBJS)

config:
	@:

clean::
	rm -f *~ '#'* *.o *.a core a.out libyor

distclean:: clean

# ------------- dependencies -------------

dlamc3.o: dlamc3.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -g -I. -I../play -c dlamc3.c

dbdsqr.o: dg.h cblasy.h ../play/plugin.h
dgecon.o: dg.h cblasy.h ../play/plugin.h
dgels.o: dg.h cblasy.h ../play/plugin.h
dgelss.o: dg.h cblasy.h ../play/plugin.h
dgesv.o: dg.h cblasy.h ../play/plugin.h
dgesv2.o: dg.h cblasy.h ../play/plugin.h
dgesvd.o: dg.h cblasy.h ../play/plugin.h
dgtsv.o: dg.h cblasy.h ../play/plugin.h
dgyor.o: dg.h cblasy.h ../play/plugin.h
dlasr.o: dg.h cblasy.h ../play/plugin.h

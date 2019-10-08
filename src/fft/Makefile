# $Id: Makefile 598 2006-12-13 11:12:09Z mbec $
SHELL=/bin/sh
MAKE=make
include ../Make.cfg

CFLAGS=$(COPTIONS) -I../play
COPTIONS=$(COPT) $(Y_CFLAGS)
COPT=$(COPT_DEFAULT)

OBJS=cfft2.o cfftb.o cfftf.o cffti.o roll2.o

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


cffti.o: cfft.h ../play/plugin.h
cfftf.o: cfft.h ../play/plugin.h
cfftb.o: cfft.h ../play/plugin.h
cfft2.o: cfft.h ../play/plugin.h
roll2.o: cfft.h ../play/plugin.h

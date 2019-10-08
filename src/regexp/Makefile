# $Id: Makefile 598 2006-12-13 11:12:09Z mbec $
SHELL=/bin/sh
MAKE=make
include ../Make.cfg

CFLAGS=$(COPTIONS) -I../play -I../yorick
COPTIONS=$(COPT) $(Y_CFLAGS)
COPT=$(COPT_DEFAULT)

OBJS=yfnmatch.o yregexp.o

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


yfnmatch.o: yfnmatch.h ../play/plugin.h
yregexp.o: yregexp.h ../play/pstdlib.h ../play/plugin.h

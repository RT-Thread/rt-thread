# Double precision Cephes library
# Makefile for unix or GCC

CC = gcc
CFLAGS = -g -O2 -Wall -fno-builtin
AR = ar
RANLIB = ranlib
INCS = mconf.h
AS = as

OBJS = acosh.o airy.o asin.o asinh.o atan.o atanh.o bdtr.o beta.o \
btdtr.o cbrt.o chbevl.o chdtr.o clog.o cmplx.o const.o \
cosh.o dawsn.o drand.o ellie.o ellik.o ellpe.o ellpj.o ellpk.o \
exp.o exp10.o exp2.o expn.o fabs.o fac.o fdtr.o \
fresnl.o gamma.o gdtr.o hyp2f1.o hyperg.o i0.o i1.o igami.o \
incbet.o incbi.o igam.o isnan.o iv.o j0.o j1.o jn.o jv.o k0.o k1.o \
kn.o log.o log2.o log10.o lrand.o nbdtr.o ndtr.o ndtri.o pdtr.o \
polevl.o polmisc.o polyn.o pow.o powi.o psi.o rgamma.o round.o \
shichi.o sici.o sin.o sindg.o sinh.o spence.o stdtr.o struve.o \
tan.o tandg.o tanh.o unity.o yn.o zeta.o zetac.o \
sqrt.o floor.o setprec.o mtherr.o

all: libmd.a mtst dtestvec dcalc paranoia # stamp-timing

stamp-timing: libmd.a mtst time-it
	time-it "mtst > /dev/null"
	touch stamp-timing

time-it: time-it.o
	$(CC) -o time-it time-it.o

time-it.o: time-it.c
	$(CC) -O2 -c time-it.c

dcalc: dcalc.o libmd.a
	$(CC) -o dcalc dcalc.o libmd.a
#	aout2exe mtst

mtst: mtst.o libmd.a
	$(CC) -v -o mtst mtst.o libmd.a
#	gcc -Wl,-verbose -b i486-linuxaout -v -o mtst mtst.o libmd.a
#	coff2exe mtst

mtst.o: mtst.c
	$(CC) -O2 -Wall -c mtst.c

dtestvec: dtestvec.o libmd.a
	$(CC) -o dtestvec dtestvec.o libmd.a

dtestvec.o: dtestvec.c
	$(CC) -g -c dtestvec.c

paranoia: paranoia.o setprec.o libmd.a
	$(CC) -o paranoia paranoia.o setprec.o libmd.a

paranoia.o: paranoia.c
	$(CC) $(CFLAGS) -c paranoia.c

libmd.a: $(OBJS) $(INCS)
# for real Unix:
	$(AR) rv libmd.a $(OBJS)
# for djgcc MSDOS:
#	>libmd.rf -rv libmd.a $(OBJS)
#	$(AR) @libmd.rf
	$(RANLIB) libmd.a

# If the following are all commented out, the C versions
# will be used by default.

# IBM PC:
#sqrt.o: sqrt.387
#	$(AS) -o sqrt.o sqrt.387
#
#floor.o: floor.387
#	$(AS) -o floor.o floor.387
#
#setprec.o: setprec.387
#	$(AS) -o setprec.o setprec.387

# ELF versions for linux (no underscores)
sqrt.o: sqrtelf.387
	$(AS) -o sqrt.o sqrtelf.387

#floor.o: floorelf.387
#	$(AS) -o floor.o floorelf.387

setprec.o: setprelf.387
	$(AS) -o setprec.o setprelf.387

# Motorola 68881. Caution, subroutine return conventions vary.
#sqrt.o: sqrt.688
#	$(AS) -o sqrt.o sqrt.688
#
#setprec.o: setprec.688
#	$(AS) -o setprec.o setprec.688

# SPARC:
#sqrt.o: sqrt.spa
#	$(AS) -o sqrt.o sqrt.spa

clean:
	rm -f *.o
	rm -f mtst
	rm -f paranoia
	rm -f dcalc
	rm -f libmd.a
	rm -f time-it
	rm -f dtestvec


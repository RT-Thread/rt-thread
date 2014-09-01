# MSDOS Microsoft C makefile for Cephes library
CFLAGS=/c
# For large memory model:
#CFLAGS=/c /AL
# Add /FPa to the CFLAGS if you want to use the fast software FPa arithmetic.
#
# Use the following with /FPa if you do not want to use the 80x87 coprocessor
# or software emulator.
#polevl.obj: polevl.c mconf.h
#	cl /c /Ox polevl.c
#
# Use the following instead if you want to use an 80x87 chip or
# software emulator for maximum accuracy computation of the
# polynomial expansions:
polevl.obj: polevl.asm mconf.h
	masm polevl.asm/r;

floor.obj: floor.asm
	masm floor.asm;

#floor.obj: floor.c mconf.h
#	cl $(CFLAGS) floor.c

acosh.obj: acosh.c mconf.h
	cl $(CFLAGS) acosh.c

airy.obj: airy.c mconf.h
	cl $(CFLAGS) airy.c

asin.obj: asin.c  mconf.h
	cl $(CFLAGS) asin.c

asinh.obj: asinh.c mconf.h
	cl $(CFLAGS) asinh.c

atan.obj: atan.c mconf.h
	cl $(CFLAGS) atan.c

atanh.obj: atanh.c mconf.h
	cl $(CFLAGS) atanh.c

asinh.obj: asinh.c mconf.h
	cl $(CFLAGS) asinh.c

bdtr.obj: bdtr.c mconf.h
	cl $(CFLAGS) bdtr.c

beta.obj: beta.c mconf.h
	cl $(CFLAGS) beta.c

btdtr.obj: btdtr.c mconf.h
	cl $(CFLAGS) btdtr.c

cbrt.obj: cbrt.c mconf.h
	cl $(CFLAGS) cbrt.c

chbevl.obj: chbevl.c mconf.h
	cl $(CFLAGS) chbevl.c

chdtr.obj: chdtr.c mconf.h
	cl $(CFLAGS) chdtr.c

clog.obj: clog.c mconf.h
	cl $(CFLAGS) clog.c

cmplx.obj: cmplx.c mconf.h
	cl $(CFLAGS) cmplx.c

const.obj: const.c mconf.h
	cl $(CFLAGS) const.c

cosh.obj: cosh.c mconf.h
	cl $(CFLAGS) cosh.c

dawsn.obj: dawsn.c mconf.h
	cl $(CFLAGS) dawsn.c

drand.obj: drand.c mconf.h
	cl $(CFLAGS) drand.c

ellie.obj: ellie.c mconf.h
	cl $(CFLAGS) ellie.c

ellik.obj: ellik.c mconf.h
	cl $(CFLAGS) ellik.c

ellpe.obj: ellpe.c mconf.h
	cl $(CFLAGS) ellpe.c

ellpj.obj: ellpj.c mconf.h
	cl $(CFLAGS) ellpj.c

ellpk.obj: ellpk.c mconf.h
	cl $(CFLAGS) ellpk.c

exp.obj: exp.c mconf.h
	cl $(CFLAGS) exp.c

exp10.obj: exp10.c mconf.h
	cl $(CFLAGS) exp10.c

exp2.obj: exp2.c mconf.h
	cl $(CFLAGS) exp2.c

expn.obj: expn.c mconf.h
	cl $(CFLAGS) expn.c

fabs.obj: fabs.c mconf.h
	cl $(CFLAGS) fabs.c

fac.obj: fac.c mconf.h
	cl $(CFLAGS) fac.c

fdtr.obj: fdtr.c mconf.h
	cl $(CFLAGS) fdtr.c

fresnl.obj: fresnl.c mconf.h
	cl $(CFLAGS) fresnl.c

gamma.obj: gamma.c mconf.h
	cl $(CFLAGS) gamma.c

gdtr.obj: gdtr.c mconf.h
	cl $(CFLAGS) gdtr.c

hyp2f1.obj: hyp2f1.c mconf.h
	cl $(CFLAGS) hyp2f1.c

hyperg.obj: hyperg.c mconf.h
	cl $(CFLAGS) hyperg.c

i0.obj: i0.c mconf.h
	cl $(CFLAGS) i0.c

i1.obj: i1.c mconf.h
	cl $(CFLAGS) i1.c

igam.obj: igam.c mconf.h
	cl $(CFLAGS) igam.c

igami.obj: igami.c mconf.h
	cl $(CFLAGS) igami.c

incbet.obj: incbet.c mconf.h
	cl $(CFLAGS) incbet.c

incbi.obj: incbi.c mconf.h
	cl $(CFLAGS) incbi.c

isnan.obj: isnan.c mconf.h
	cl $(CFLAGS) isnan.c

iv.obj: iv.c mconf.h
	cl $(CFLAGS) iv.c

j0.obj: j0.c mconf.h
	cl $(CFLAGS) j0.c

j1.obj: j1.c mconf.h
	cl $(CFLAGS) j1.c

jn.obj: jn.c mconf.h
	cl $(CFLAGS) jn.c

jv.obj: jv.c mconf.h
	cl $(CFLAGS) jv.c

k0.obj: k0.c mconf.h
	cl $(CFLAGS) k0.c

k1.obj: k1.c mconf.h
	cl $(CFLAGS) k1.c

kn.obj: kn.c mconf.h
	cl $(CFLAGS) kn.c

log.obj: log.c mconf.h
	cl $(CFLAGS) log.c

log2.obj: log2.c mconf.h
	cl $(CFLAGS) log2.c

log10.obj: log10.c mconf.h
	cl $(CFLAGS) log10.c

mtherr.obj: mtherr.c mconf.h
	cl $(CFLAGS) mtherr.c

nbdtr.obj: nbdtr.c mconf.h
	cl $(CFLAGS) nbdtr.c

ndtr.obj: ndtr.c mconf.h
	cl $(CFLAGS) ndtr.c

ndtri.obj: ndtri.c mconf.h
	cl $(CFLAGS) ndtri.c

pdtr.obj: pdtr.c mconf.h
	cl $(CFLAGS) pdtr.c

pow.obj: pow.c mconf.h
	cl $(CFLAGS) pow.c

powi.obj: powi.c mconf.h
	cl $(CFLAGS) powi.c

psi.obj: psi.c mconf.h
	cl $(CFLAGS) psi.c

rgamma.obj: rgamma.c mconf.h
	cl $(CFLAGS) rgamma.c

round.obj: round.c mconf.h
	cl $(CFLAGS) round.c

setprec.obj: setprec.87
	masm setprec.87;

shichi.obj: shichi.c mconf.h
	cl $(CFLAGS) shichi.c

sici.obj: sici.c mconf.h
	cl $(CFLAGS) sici.c

sin.obj: sin.c mconf.h
	cl $(CFLAGS) sin.c

sindg.obj: sindg.c mconf.h
	cl $(CFLAGS) sindg.c

sinh.obj: sinh.c mconf.h
	cl $(CFLAGS) sinh.c

spence.obj: spence.c mconf.h
	cl $(CFLAGS) spence.c

sqrt.obj: sqrt.87
	masm sqrt.87;

#sqrt.obj: sqrt.c
#	cl $(CFLAGS) sqrt.c

stdtr.obj: stdtr.c mconf.h
	cl $(CFLAGS) stdtr.c

struve.obj: struve.c mconf.h
	cl $(CFLAGS) struve.c

tan.obj: tan.c mconf.h
	cl $(CFLAGS) tan.c

tandg.obj: tandg.c mconf.h
	cl $(CFLAGS) tandg.c 

tanh.obj: tanh.c mconf.h
	cl $(CFLAGS) tanh.c

yn.obj: yn.c mconf.h
	cl $(CFLAGS) yn.c

zeta.obj: zeta.c mconf.h
	cl $(CFLAGS) zeta.c

zetac.obj: zetac.c mconf.h
	cl $(CFLAGS) zetac.c

polyn.obj: polyn.c mconf.h
	cl $(CFLAGS) polyn.c

polmisc.obj: polmisc.c mconf.h
	cl $(CFLAGS) polmisc.c

unity.obj: unity.c mconf.h
	cl $(CFLAGS) unity.c

fti.lib: acosh.obj airy.obj asin.obj asinh.obj atan.obj atanh.obj bdtr.obj \
beta.obj btdtr.obj cbrt.obj chbevl.obj chdtr.obj clog.obj \
cmplx.obj const.obj cosh.obj dawsn.obj drand.obj ellie.obj ellik.obj \
ellpe.obj ellpj.obj ellpk.obj exp.obj exp10.obj \
exp2.obj expn.obj fabs.obj fac.obj fdtr.obj floor.obj fresnl.obj gamma.obj \
gdtr.obj hyp2f1.obj hyperg.obj i0.c i1.c igam.c igami.obj incbet.obj \
incbi.obj isnan.obj iv.obj j0.obj j1.obj jn.obj jv.obj k0.obj k1.obj \
kn.obj log.obj log2.obj log10.obj mtherr.obj nbdtr.obj ndtr.obj ndtri.obj \
pdtr.obj polevl.obj polmisc.obj polyn.obj pow.obj powi.obj psi.obj \
rgamma.obj round.obj shichi.obj sici.obj sin.obj sindg.obj sinh.obj \
spence.obj sqrt.obj stdtr.obj setprec.obj struve.obj tan.obj \
tandg.obj tanh.obj unity.obj yn.obj zeta.obj zetac.obj \
mconf.h
	lib @ftilib.rsp

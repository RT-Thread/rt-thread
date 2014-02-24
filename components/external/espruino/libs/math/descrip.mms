CFLAGS=		/DEBUG/NOLIST
hfiles=		mconf.h-

ofiles=		acosh.obj-
		asin.obj-
		asinh.obj-
		atan.obj-
		atanh.obj-
		cbrt.obj-
		chbevl.obj-
		const.obj-
		cosh.obj-
		drand.obj-
		exp.obj-
		exp10.obj-
		fabs.obj-
		floor.obj-
		log.obj-
		log10.obj-
		polevl.obj-
		pow.obj-
		powi.obj-
		round.obj-
		sin.obj-
		sinh.obj-
		tan.obj-
		tanh.obj-
		unity.obj-
		sqrt.obj-
		floor.obj-
		polevl.obj-
		mtherr.obj

mtst.exe : $(ofiles)
	LINK  mtst/option
acosh.obj : acosh.c,$(HFILES)
    CC $(CFLAGS) acosh
asin.obj : asin.c,$(HFILES)
    CC $(CFLAGS) asin
asinh.obj : asinh.c,$(HFILES)
    CC $(CFLAGS) asinh
atan.obj : atan.c,$(HFILES)
    CC $(CFLAGS) atan
atan.obj : atan.c,$(HFILES)
    CC $(CFLAGS) atan
atanh.obj : atanh.c,$(HFILES)
    CC $(CFLAGS) atanh
cbrt.obj : cbrt.c,$(HFILES)
    CC $(CFLAGS) cbrt
chbevl.obj : chbevl.c,$(HFILES)
    CC $(CFLAGS) chbevl
const.obj : const.c,$(HFILES)
    CC $(CFLAGS) const
cosh.obj : cosh.c,$(HFILES)
    CC $(CFLAGS) cosh
drand.obj : drand.c,$(HFILES)
    CC $(CFLAGS) drand
exp.obj : exp.c,$(HFILES)
    CC $(CFLAGS) exp
exp10.obj : exp10.c,$(HFILES)
    CC $(CFLAGS) exp10
fabs.obj : fabs.c,$(HFILES)
    CC $(CFLAGS) fabs
floor.obj : floor.c,$(HFILES)
    CC $(CFLAGS) floor
log.obj : log.c,$(HFILES)
    CC $(CFLAGS) log
log10.obj : log10.c,$(HFILES)
    CC $(CFLAGS) log10
polevl.obj : polevl.c,$(HFILES)
    CC $(CFLAGS) polevl
pow.obj : pow.c,$(HFILES)
    CC $(CFLAGS) pow
powi.obj : powi.c,$(HFILES)
    CC $(CFLAGS) powi
round.obj : round.c,$(HFILES)
    CC $(CFLAGS) round
sin.obj : sin.c,$(HFILES)
    CC $(CFLAGS) sin
sinh.obj : sinh.c,$(HFILES)
    CC $(CFLAGS) sinh
tan.obj : tan.c,$(HFILES)
    CC $(CFLAGS) tan
tanh.obj : tanh.c,$(HFILES)
    CC $(CFLAGS) tanh
unity.obj : unity.c,$(HFILES)
    CC $(CFLAGS) unity
sqrt.obj : sqrt.c,$(HFILES)
    CC $(CFLAGS) sqrt
mtherr.obj : mtherr.c,$(HFILES)
    CC $(CFLAGS) mtherr









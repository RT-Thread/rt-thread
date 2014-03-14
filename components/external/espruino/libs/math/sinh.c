/*							sinh.c
 *
 *	Hyperbolic sine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, sinh();
 *
 * y = sinh( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns hyperbolic sine of argument in the range MINLOG to
 * MAXLOG.
 *
 * The range is partitioned into two segments.  If |x| <= 1, a
 * rational function of the form x + x**3 P(x)/Q(x) is employed.
 * Otherwise the calculation is sinh(x) = ( exp(x) - exp(-x) )/2.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      +- 88        50000       4.0e-17     7.7e-18
 *    IEEE     +-MAXLOG     30000       2.6e-16     5.7e-17
 *
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
const static double P[] = {
-7.89474443963537015605E-1,
-1.63725857525983828727E2,
-1.15614435765005216044E4,
-3.51754964808151394800E5
};
const static double Q[] = {
/* 1.00000000000000000000E0,*/
-2.77711081420602794433E2,
 3.61578279834431989373E4,
-2.11052978884890840399E6
};
#endif

#ifdef DEC
static unsigned short P[] = {
0140112,0015377,0042731,0163255,
0142043,0134721,0146177,0123761,
0143464,0122706,0034353,0006017,
0144653,0140536,0157665,0054045
};
static unsigned short Q[] = {
/*0040200,0000000,0000000,0000000,*/
0142212,0155404,0133513,0022040,
0044015,0036723,0173271,0011053,
0145400,0150407,0023710,0001034
};
#endif

#ifdef IBMPC
static unsigned short P[] = {
0x3cd6,0xe8bb,0x435f,0xbfe9,
0xf4fe,0x398f,0x773a,0xc064,
0x6182,0xc71d,0x94b8,0xc0c6,
0xab05,0xdbf6,0x782b,0xc115
};
static unsigned short Q[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
0x6484,0x96e9,0x5b60,0xc071,
0x2245,0x7ed7,0xa7ba,0x40e1,
0x0044,0xe4f9,0x1a20,0xc140
};
#endif

#ifdef MIEEE
static unsigned short P[] = {
0xbfe9,0x435f,0xe8bb,0x3cd6,
0xc064,0x773a,0x398f,0xf4fe,
0xc0c6,0x94b8,0xc71d,0x6182,
0xc115,0x782b,0xdbf6,0xab05
};
static unsigned short Q[] = {
0xc071,0x5b60,0x96e9,0x6484,
0x40e1,0xa7ba,0x7ed7,0x2245,
0xc140,0x1a20,0xe4f9,0x0044
};
#endif

#ifdef ANSIPROT
extern double fabs ( double );
extern double exp ( double );
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
#else
double fabs(), exp(), polevl(), p1evl();
#endif
extern double INFINITY, MINLOG, MAXLOG, LOGE2;

double sinh(x)
double x;
{
double a;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
a = fabs(x);
if( (x > (MAXLOG + LOGE2)) || (x > -(MINLOG-LOGE2) ) )
	{
	mtherr( "sinh", DOMAIN );
	if( x > 0 )
		return( INFINITY );
	else
		return( -INFINITY );
	}
if( a > 1.0 )
	{
	if( a >= (MAXLOG - LOGE2) )
		{
		a = exp(0.5*a);
		a = (0.5 * a) * a;
		if( x < 0 )
			a = -a;
		return(a);
		}
	a = exp(a);
	a = 0.5*a - (0.5/a);
	if( x < 0 )
		a = -a;
	return(a);
	}

a *= a;
return( x + x * a * (polevl(a,P,3)/p1evl(a,Q,3)) );
}

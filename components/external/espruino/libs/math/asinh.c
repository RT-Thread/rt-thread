/*							asinh.c
 *
 *	Inverse hyperbolic sine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, asinh();
 *
 * y = asinh( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns inverse hyperbolic sine of argument.
 *
 * If |x| < 0.5, the function is approximated by a rational
 * form  x + x**3 P(x)/Q(x).  Otherwise,
 *
 *     asinh(x) = log( x + sqrt(1 + x*x) ).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      -3,3         75000       4.6e-17     1.1e-17
 *    IEEE     -1,1         30000       3.7e-16     7.8e-17
 *    IEEE      1,3         30000       2.5e-16     6.7e-17
 *
 */

/*						asinh.c	*/

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/


#include "mconf.h"

#ifdef UNK
const static double P[] = {
-4.33231683752342103572E-3,
-5.91750212056387121207E-1,
-4.37390226194356683570E0,
-9.09030533308377316566E0,
-5.56682227230859640450E0
};
const static double Q[] = {
/* 1.00000000000000000000E0,*/
 1.28757002067426453537E1,
 4.86042483805291788324E1,
 6.95722521337257608734E1,
 3.34009336338516356383E1
};
#endif

#ifdef DEC
static unsigned short P[] = {
0136215,0173033,0110410,0105475,
0140027,0076361,0020056,0164520,
0140613,0173401,0160136,0053142,
0141021,0070744,0000503,0176261,
0140662,0021550,0073106,0133351
};
static unsigned short Q[] = {
/* 0040200,0000000,0000000,0000000,*/
0041116,0001336,0034120,0173054,
0041502,0065300,0013144,0021231,
0041613,0022376,0035516,0153063,
0041405,0115216,0054265,0004557
};
#endif

#ifdef IBMPC
static unsigned short P[] = {
0x1168,0x7221,0xbec3,0xbf71,
0xdd2a,0x2405,0xef9e,0xbfe2,
0xcacc,0x3c0b,0x7ee0,0xc011,
0x7f96,0x8028,0x2e3c,0xc022,
0xd6dd,0x0ec8,0x446d,0xc016
};
static unsigned short Q[] = {
/* 0x0000,0x0000,0x0000,0x3ff0,*/
0x1ec5,0xc70a,0xc05b,0x4029,
0x8453,0x02cc,0x4d58,0x4048,
0xdac6,0xc769,0x649f,0x4051,
0xa12e,0xcb16,0xb351,0x4040
};
#endif

#ifdef MIEEE
static unsigned short P[] = {
0xbf71,0xbec3,0x7221,0x1168,
0xbfe2,0xef9e,0x2405,0xdd2a,
0xc011,0x7ee0,0x3c0b,0xcacc,
0xc022,0x2e3c,0x8028,0x7f96,
0xc016,0x446d,0x0ec8,0xd6dd
};
static unsigned short Q[] = {
0x4029,0xc05b,0xc70a,0x1ec5,
0x4048,0x4d58,0x02cc,0x8453,
0x4051,0x649f,0xc769,0xdac6,
0x4040,0xb351,0xcb16,0xa12e
};
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double sqrt ( double );
extern double log ( double );
#else
double log(), sqrt(), polevl(), p1evl();
#endif
extern double LOGE2, INFINITY;

double asinh(xx)
double xx;
{
double a, z, x;
int sign;

#ifdef MINUSZERO
if( xx == 0.0 )
  return(xx);
#endif
if( xx < 0.0 )
	{
	sign = -1;
	x = -xx;
	}
else
	{
	sign = 1;
	x = xx;
	}

if( x > 1.0e8 )
	{
#ifdef INFINITIES
	  if( x == INFINITY )
	    return(xx);
#endif
	return( sign * (log(x) + LOGE2) );
	}

z = x * x;
if( x < 0.5 )
	{
	a = ( polevl(z, P, 4)/p1evl(z, Q, 4) ) * z;
	a = a * x  +  x;
	if( sign < 0 )
		a = -a;
	return(a);
	}	

a = sqrt( z + 1.0 );
return( sign * log(x + a) );
}

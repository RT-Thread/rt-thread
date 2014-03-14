/*							acosh.c
 *
 *	Inverse hyperbolic cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, acosh();
 *
 * y = acosh( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns inverse hyperbolic cosine of argument.
 *
 * If 1 <= x < 1.5, a rational approximation
 *
 *	sqrt(z) * P(z)/Q(z)
 *
 * where z = x-1, is used.  Otherwise,
 *
 * acosh(x)  =  log( x + sqrt( (x-1)(x+1) ).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       1,3         30000       4.2e-17     1.1e-17
 *    IEEE      1,3         30000       4.6e-16     8.7e-17
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * acosh domain       |x| < 1            NAN
 *
 */

/*							acosh.c	*/

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/


/* acosh(z) = sqrt(x) * R(x), z = x + 1, interval 0 < x < 0.5 */

#include "mconf.h"

#ifdef UNK
const static double P[] = {
 1.18801130533544501356E2,
 3.94726656571334401102E3,
 3.43989375926195455866E4,
 1.08102874834699867335E5,
 1.10855947270161294369E5
};
const static double Q[] = {
/* 1.00000000000000000000E0,*/
 1.86145380837903397292E2,
 4.15352677227719831579E3,
 2.97683430363289370382E4,
 8.29725251988426222434E4,
 7.83869920495893927727E4
};
#endif

#ifdef DEC
static unsigned short P[] = {
0041755,0115055,0144002,0146444,
0043166,0132103,0155150,0150302,
0044006,0057360,0003021,0162753,
0044323,0021557,0175225,0056253,
0044330,0101771,0040046,0006636
};
static unsigned short Q[] = {
/*0040200,0000000,0000000,0000000,*/
0042072,0022467,0126670,0041232,
0043201,0146066,0152142,0034015,
0043750,0110257,0121165,0026100,
0044242,0007103,0034667,0033173,
0044231,0014576,0175573,0017472
};
#endif

#ifdef IBMPC
static unsigned short P[] = {
0x59a4,0xb900,0xb345,0x405d,
0x1a18,0x7b4d,0xd688,0x40ae,
0x3cbd,0x00c2,0xcbde,0x40e0,
0xab95,0xff52,0x646d,0x40fa,
0xc1b4,0x2804,0x107f,0x40fb
};
static unsigned short Q[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
0x0853,0xf5b7,0x44a6,0x4067,
0x4702,0xda8c,0x3986,0x40b0,
0xa588,0xf44e,0x1215,0x40dd,
0xe6cf,0x6736,0x41c8,0x40f4,
0x63e7,0xdf6f,0x232f,0x40f3
};
#endif

#ifdef MIEEE
static unsigned short P[] = {
0x405d,0xb345,0xb900,0x59a4,
0x40ae,0xd688,0x7b4d,0x1a18,
0x40e0,0xcbde,0x00c2,0x3cbd,
0x40fa,0x646d,0xff52,0xab95,
0x40fb,0x107f,0x2804,0xc1b4
};
static unsigned short Q[] = {
0x4067,0x44a6,0xf5b7,0x0853,
0x40b0,0x3986,0xda8c,0x4702,
0x40dd,0x1215,0xf44e,0xa588,
0x40f4,0x41c8,0x6736,0xe6cf,
0x40f3,0x232f,0xdf6f,0x63e7,
};
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double log ( double );
extern double sqrt ( double );
#else
double log(), sqrt(), polevl(), p1evl();
#endif
extern double LOGE2, INFINITY, NAN;

double acosh(x)
double x;
{
double a, z;

if( x < 1.0 )
	{
	mtherr( "acosh", DOMAIN );
	return(NAN);
	}

if( x > 1.0e8 )
	{
#ifdef INFINITIES
	if( x == INFINITY )
		return( INFINITY );
#endif
	return( log(x) + LOGE2 );
	}

z = x - 1.0;

if( z < 0.5 )
	{
	a = sqrt(z) * (polevl(z, P, 4) / p1evl(z, Q, 5) );
	return( a );
	}

a = sqrt( z*(x+1.0) );
return( log(x + a) );
}

/*							tan.c
 *
 *	Circular tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, tan();
 *
 * y = tan( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular tangent of the radian argument x.
 *
 * Range reduction is modulo pi/4.  A rational function
 *       x + x**3 P(x**2)/Q(x**2)
 * is employed in the basic interval [0, pi/4].
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      +-1.07e9      44000      4.1e-17     1.0e-17
 *    IEEE     +-1.07e9      30000      2.9e-16     8.1e-17
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * tan total loss   x > 1.073741824e9     0.0
 *
 */
/*							cot.c
 *
 *	Circular cotangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cot();
 *
 * y = cot( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular cotangent of the radian argument x.
 *
 * Range reduction is modulo pi/4.  A rational function
 *       x + x**3 P(x**2)/Q(x**2)
 * is employed in the basic interval [0, pi/4].
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     +-1.07e9      30000      2.9e-16     8.2e-17
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * cot total loss   x > 1.073741824e9       0.0
 * cot singularity  x = 0                  INFINITY
 *
 */

/*
Cephes Math Library Release 2.8:  June, 2000
yright 1984, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
const static double P[] = {
-1.30936939181383777646E4,
 1.15351664838587416140E6,
-1.79565251976484877988E7
};
const static double Q[] = {
/* 1.00000000000000000000E0,*/
 1.36812963470692954678E4,
-1.32089234440210967447E6,
 2.50083801823357915839E7,
-5.38695755929454629881E7
};
const static double DP1 = 7.853981554508209228515625E-1;
const static double DP2 = 7.94662735614792836714E-9;
const static double DP3 = 3.06161699786838294307E-17;
const static double lossth = 1.073741824e9;
#endif

#ifdef DEC
static unsigned short P[] = {
0143514,0113306,0111171,0174674,
0045214,0147545,0027744,0167346,
0146210,0177526,0114514,0105660
};
static unsigned short Q[] = {
/*0040200,0000000,0000000,0000000,*/
0043525,0142457,0072633,0025617,
0145241,0036742,0140525,0162256,
0046276,0146176,0013526,0143573,
0146515,0077401,0162762,0150607
};
/*  7.853981629014015197753906250000E-1 */
static unsigned short P1[] = {0040111,0007732,0120000,0000000,};
/*  4.960467869796758577649598009884E-10 */
static unsigned short P2[] = {0030410,0055060,0100000,0000000,};
/*  2.860594363054915898381331279295E-18 */
static unsigned short P3[] = {0021523,0011431,0105056,0001560,};
#define DP1 *(double *)P1
#define DP2 *(double *)P2
#define DP3 *(double *)P3
const static double lossth = 1.073741824e9;
#endif

#ifdef IBMPC
static unsigned short P[] = {
0x3f38,0xd24f,0x92d8,0xc0c9,
0x9ddd,0xa5fc,0x99ec,0x4131,
0x9176,0xd329,0x1fea,0xc171
};
static unsigned short Q[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
0x6572,0xeeb3,0xb8a5,0x40ca,
0xbc96,0x582a,0x27bc,0xc134,
0xd8ef,0xc2ea,0xd98f,0x4177,
0x5a31,0x3cbe,0xafe0,0xc189
};
/*
  7.85398125648498535156E-1,
  3.77489470793079817668E-8,
  2.69515142907905952645E-15,
*/
static unsigned short P1[] = {0x0000,0x4000,0x21fb,0x3fe9};
static unsigned short P2[] = {0x0000,0x0000,0x442d,0x3e64};
static unsigned short P3[] = {0x5170,0x98cc,0x4698,0x3ce8};
#define DP1 *(double *)P1
#define DP2 *(double *)P2
#define DP3 *(double *)P3
const static double lossth = 1.073741824e9;
#endif

#ifdef MIEEE
static unsigned short P[] = {
0xc0c9,0x92d8,0xd24f,0x3f38,
0x4131,0x99ec,0xa5fc,0x9ddd,
0xc171,0x1fea,0xd329,0x9176
};
static unsigned short Q[] = {
0x40ca,0xb8a5,0xeeb3,0x6572,
0xc134,0x27bc,0x582a,0xbc96,
0x4177,0xd98f,0xc2ea,0xd8ef,
0xc189,0xafe0,0x3cbe,0x5a31
};
static unsigned short P1[] = {
0x3fe9,0x21fb,0x4000,0x0000
};
static unsigned short P2[] = {
0x3e64,0x442d,0x0000,0x0000
};
static unsigned short P3[] = {
0x3ce8,0x4698,0x98cc,0x5170,
};
#define DP1 *(double *)P1
#define DP2 *(double *)P2
#define DP3 *(double *)P3
const static double lossth = 1.073741824e9;
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double floor ( double );
extern double ldexp ( double, int );
extern int isnan ( double );
extern int isfinite ( double );
const static double tancot(double, int);
#else
double polevl(), p1evl(), floor(), ldexp();
const static double tancot();
int isnan(), isfinite();
#endif
extern double PIO4;
extern double INFINITY;
extern double NAN;

double tan(x)
double x;
{
#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	mtherr( "tan", DOMAIN );
	return(NAN);
	}
#endif
return( tancot(x,0) );
}


double cot(x)
double x;
{

if( x == 0.0 )
	{
	mtherr( "cot", SING );
	return( INFINITY );
	}
return( tancot(x,1) );
}


const static double tancot( xx, cotflg )
double xx;
int cotflg;
{
double x, y, z, zz;
int j, sign;

/* make argument positive but save the sign */
if( xx < 0 )
	{
	x = -xx;
	sign = -1;
	}
else
	{
	x = xx;
	sign = 1;
	}

if( x > lossth )
	{
	if( cotflg )
		mtherr( "cot", TLOSS );
	else
		mtherr( "tan", TLOSS );
	return(0.0);
	}

/* compute x mod PIO4 */
y = floor( x/PIO4 );

/* strip high bits of integer part */
z = ldexp( y, -3 );
z = floor(z);		/* integer part of y/8 */
z = y - ldexp( z, 3 );  /* y - 16 * (y/16) */

/* integer and fractional part modulo one octant */
j = z;

/* map zeros and singularities to origin */
if( j & 1 )
	{
	j += 1;
	y += 1.0;
	}

z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( zz > 1.0e-14 )
	y = z  +  z * (zz * polevl( zz, P, 2 )/p1evl(zz, Q, 4));
else
	y = z;
	
if( j & 2 )
	{
	if( cotflg )
		y = -y;
	else
		y = -1.0/y;
	}
else
	{
	if( cotflg )
		y = 1.0/y;
	}

if( sign < 0 )
	y = -y;

return( y );
}

/*							sin.c
 *
 *	Circular sine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, sin();
 *
 * y = sin( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Range reduction is into intervals of pi/4.  The reduction
 * error is nearly eliminated by contriving an extended precision
 * modular arithmetic.
 *
 * Two polynomial approximating functions are employed.
 * Between 0 and pi/4 the sine is approximated by
 *      x  +  x**3 P(x**2).
 * Between pi/4 and pi/2 the cosine is represented as
 *      1  -  x**2 Q(x**2).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain      # trials      peak         rms
 *    DEC       0, 10       150000       3.0e-17     7.8e-18
 *    IEEE -1.07e9,+1.07e9  130000       2.1e-16     5.4e-17
 * 
 * ERROR MESSAGES:
 *
 *   message           condition        value returned
 * sin total loss   x > 1.073741824e9      0.0
 *
 * Partial loss of accuracy begins to occur at x = 2**30
 * = 1.074e9.  The loss is not gradual, but jumps suddenly to
 * about 1 part in 10e7.  Results may be meaningless for
 * x > 2**49 = 5.6e14.  The routine as implemented flags a
 * TLOSS error for x > 2**30 and returns 0.0.
 */
/*							cos.c
 *
 *	Circular cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cos();
 *
 * y = cos( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Range reduction is into intervals of pi/4.  The reduction
 * error is nearly eliminated by contriving an extended precision
 * modular arithmetic.
 *
 * Two polynomial approximating functions are employed.
 * Between 0 and pi/4 the cosine is approximated by
 *      1  -  x**2 Q(x**2).
 * Between pi/4 and pi/2 the sine is represented as
 *      x  +  x**3 P(x**2).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain      # trials      peak         rms
 *    IEEE -1.07e9,+1.07e9  130000       2.1e-16     5.4e-17
 *    DEC        0,+1.07e9   17000       3.0e-17     7.2e-18
 */

/*							sin.c	*/

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
const static double sincof[] = {
 1.58962301576546568060E-10,
-2.50507477628578072866E-8,
 2.75573136213857245213E-6,
-1.98412698295895385996E-4,
 8.33333333332211858878E-3,
-1.66666666666666307295E-1,
};
const static double coscof[6] = {
-1.13585365213876817300E-11,
 2.08757008419747316778E-9,
-2.75573141792967388112E-7,
 2.48015872888517045348E-5,
-1.38888888888730564116E-3,
 4.16666666666665929218E-2,
};
const static double DP1 =   7.85398125648498535156E-1;
const static double DP2 =   3.77489470793079817668E-8;
const static double DP3 =   2.69515142907905952645E-15;
/* const static double lossth = 1.073741824e9; */
#endif

#ifdef DEC
static unsigned short sincof[] = {
0030056,0143750,0177214,0163153,
0131727,0027455,0044510,0175352,
0033470,0167432,0131752,0042414,
0135120,0006400,0146776,0174027,
0036410,0104210,0104207,0137202,
0137452,0125252,0125252,0125103,
};
static unsigned short coscof[24] = {
0127107,0151115,0002060,0152325,
0031017,0072353,0155161,0174053,
0132623,0171173,0172542,0057056,
0034320,0006400,0147102,0023652,
0135666,0005540,0133012,0076213,
0037052,0125252,0125252,0125126,
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
#endif

#ifdef IBMPC
static unsigned short sincof[] = {
0x9ccd,0x1fd1,0xd8fd,0x3de5,
0x1f5d,0xa929,0xe5e5,0xbe5a,
0x48a1,0x567d,0x1de3,0x3ec7,
0xdf03,0x19bf,0x01a0,0xbf2a,
0xf7d0,0x1110,0x1111,0x3f81,
0x5548,0x5555,0x5555,0xbfc5,
};
static unsigned short coscof[24] = {
0x1a9b,0xa086,0xfa49,0xbda8,
0x3f05,0x7b4e,0xee9d,0x3e21,
0x4bc6,0x7eac,0x7e4f,0xbe92,
0x44f5,0x19c8,0x01a0,0x3efa,
0x4f91,0x16c1,0xc16c,0xbf56,
0x554b,0x5555,0x5555,0x3fa5,
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
#endif

#ifdef MIEEE
static unsigned short sincof[] = {
0x3de5,0xd8fd,0x1fd1,0x9ccd,
0xbe5a,0xe5e5,0xa929,0x1f5d,
0x3ec7,0x1de3,0x567d,0x48a1,
0xbf2a,0x01a0,0x19bf,0xdf03,
0x3f81,0x1111,0x1110,0xf7d0,
0xbfc5,0x5555,0x5555,0x5548,
};
static unsigned short coscof[24] = {
0xbda8,0xfa49,0xa086,0x1a9b,
0x3e21,0xee9d,0x7b4e,0x3f05,
0xbe92,0x7e4f,0x7eac,0x4bc6,
0x3efa,0x01a0,0x19c8,0x44f5,
0xbf56,0xc16c,0x16c1,0x4f91,
0x3fa5,0x5555,0x5555,0x554b,
};
static unsigned short P1[] = {0x3fe9,0x21fb,0x4000,0x0000};
static unsigned short P2[] = {0x3e64,0x442d,0x0000,0x0000};
static unsigned short P3[] = {0x3ce8,0x4698,0x98cc,0x5170};
#define DP1 *(double *)P1
#define DP2 *(double *)P2
#define DP3 *(double *)P3
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double floor ( double );
extern double ldexp ( double, int );
extern int isnan ( double );
extern int isfinite ( double );
#else
double polevl(), floor(), ldexp();
int isnan(), isfinite();
#endif
extern double PIO4;
const static double lossth = 1.073741824e9;
#ifdef NANS
extern double NAN;
#endif
#ifdef INFINITIES
extern double INFINITY;
#endif


double sin(x)
double x;
{
double y, z, zz;
int j, sign;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	mtherr( "sin", DOMAIN );
	return(NAN);
	}
#endif
/* make argument positive but save the sign */
sign = 1;
if( x < 0 )
	{
	x = -x;
	sign = -1;
	}

if( x > lossth )
	{
	mtherr( "sin", TLOSS );
	return(0.0);
	}

y = floor( x/PIO4 ); /* integer part of x/PIO4 */

/* strip high bits of integer part to prevent integer overflow */
z = ldexp( y, -4 );
z = floor(z);           /* integer part of y/8 */
z = y - ldexp( z, 4 );  /* y - 16 * (y/16) */

j = z; /* convert to integer for tests on the phase angle */
/* map zeros to origin */
if( j & 1 )
	{
	j += 1;
	y += 1.0;
	}
j = j & 07; /* octant modulo 360 degrees */
/* reflect in x axis */
if( j > 3)
	{
	sign = -sign;
	j -= 4;
	}

/* Extended precision modular arithmetic */
z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( (j==1) || (j==2) )
	{
	y = 1.0 - ldexp(zz,-1) + zz * zz * polevl( zz, coscof, 5 );
	}
else
	{
/*	y = z  +  z * (zz * polevl( zz, sincof, 5 ));*/
	y = z  +  z * z * z * polevl( zz, sincof, 5 );
	}

if(sign < 0)
	y = -y;

return(y);
}





double cos(x)
double x;
{
double y, z, zz;
long i;
int j, sign;

#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	mtherr( "cos", DOMAIN );
	return(NAN);
	}
#endif

/* make argument positive */
sign = 1;
if( x < 0 )
	x = -x;

if( x > lossth )
	{
	mtherr( "cos", TLOSS );
	return(0.0);
	}

y = floor( x/PIO4 );
z = ldexp( y, -4 );
z = floor(z);		/* integer part of y/8 */
z = y - ldexp( z, 4 );  /* y - 16 * (y/16) */

/* integer and fractional part modulo one octant */
i = z;
if( i & 1 )	/* map zeros to origin */
	{
	i += 1;
	y += 1.0;
	}
j = i & 07;
if( j > 3)
	{
	j -=4;
	sign = -sign;
	}

if( j > 1 )
	sign = -sign;

/* Extended precision modular arithmetic */
z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( (j==1) || (j==2) )
	{
/*	y = z  +  z * (zz * polevl( zz, sincof, 5 ));*/
	y = z  +  z * z * z * polevl( zz, sincof, 5 );
	}
else
	{
	y = 1.0 - ldexp(zz,-1) + zz * zz * polevl( zz, coscof, 5 );
	}

if(sign < 0)
	y = -y;

return(y);
}





/* Degrees, minutes, seconds to radians: */

/* 1 arc second, in radians = 4.8481368110953599358991410e-5 */
#ifdef DEC
static unsigned short P648[] = {034513,054170,0176773,0116043,};
#define P64800 *(double *)P648
#else
const static double P64800 = 4.8481368110953599358991410e-5;
#endif

double radian(d,m,s)
double d,m,s;
{

return( ((d*60.0 + m)*60.0 + s)*P64800 );
}

/*							asin.c
 *
 *	Inverse circular sine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, asin();
 *
 * y = asin( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle between -pi/2 and +pi/2 whose sine is x.
 *
 * A rational function of the form x + x**3 P(x**2)/Q(x**2)
 * is used for |x| in the interval [0, 0.5].  If |x| > 0.5 it is
 * transformed by the identity
 *
 *    asin(x) = pi/2 - 2 asin( sqrt( (1-x)/2 ) ).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      -1, 1        40000       2.6e-17     7.1e-18
 *    IEEE     -1, 1        10^6        1.9e-16     5.4e-17
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * asin domain        |x| > 1           NAN
 *
 */
/*							acos()
 *
 *	Inverse circular cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, acos();
 *
 * y = acos( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle between 0 and pi whose cosine
 * is x.
 *
 * Analytically, acos(x) = pi/2 - asin(x).  However if |x| is
 * near 1, there is cancellation error in subtracting asin(x)
 * from pi/2.  Hence if x < -0.5,
 *
 *    acos(x) =	 pi - 2.0 * asin( sqrt((1+x)/2) );
 *
 * or if x > +0.5,
 *
 *    acos(x) =	 2.0 * asin(  sqrt((1-x)/2) ).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       -1, 1       50000       3.3e-17     8.2e-18
 *    IEEE      -1, 1       10^6        2.2e-16     6.5e-17
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * asin domain        |x| > 1           NAN
 */

/*							asin.c	*/

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

/* arcsin(x)  =  x + x^3 P(x^2)/Q(x^2)
   0 <= x <= 0.625
   Peak relative error = 1.2e-18  */
#if UNK
const static double P[6] = {
 4.253011369004428248960E-3,
-6.019598008014123785661E-1,
 5.444622390564711410273E0,
-1.626247967210700244449E1,
 1.956261983317594739197E1,
-8.198089802484824371615E0,
};
const static double Q[5] = {
/* 1.000000000000000000000E0, */
-1.474091372988853791896E1,
 7.049610280856842141659E1,
-1.471791292232726029859E2,
 1.395105614657485689735E2,
-4.918853881490881290097E1,
};
#endif
#if DEC
static short P[24] = {
0036213,0056330,0057244,0053234,
0140032,0015011,0114762,0160255,
0040656,0035130,0136121,0067313,
0141202,0014616,0170474,0101731,
0041234,0100076,0151674,0111310,
0141003,0025540,0033165,0077246,
};
static short Q[20] = {
/* 0040200,0000000,0000000,0000000, */
0141153,0155310,0055360,0072530,
0041614,0177001,0027764,0101237,
0142023,0026733,0064653,0133266,
0042013,0101264,0023775,0176351,
0141504,0140420,0050660,0036543,
};
#endif
#if IBMPC
static short P[24] = {
0x8ad3,0x0bd4,0x6b9b,0x3f71,
0x5c16,0x333e,0x4341,0xbfe3,
0x2dd9,0x178a,0xc74b,0x4015,
0x907b,0xde27,0x4331,0xc030,
0x9259,0xda77,0x9007,0x4033,
0xafd5,0x06ce,0x656c,0xc020,
};
static short Q[20] = {
/* 0x0000,0x0000,0x0000,0x3ff0, */
0x0eab,0x0b5e,0x7b59,0xc02d,
0x9054,0x25fe,0x9fc0,0x4051,
0x76d7,0x6d35,0x65bb,0xc062,
0xbf9d,0x84ff,0x7056,0x4061,
0x07ac,0x0a36,0x9822,0xc048,
};
#endif
#if MIEEE
static short P[24] = {
0x3f71,0x6b9b,0x0bd4,0x8ad3,
0xbfe3,0x4341,0x333e,0x5c16,
0x4015,0xc74b,0x178a,0x2dd9,
0xc030,0x4331,0xde27,0x907b,
0x4033,0x9007,0xda77,0x9259,
0xc020,0x656c,0x06ce,0xafd5,
};
static short Q[20] = {
/* 0x3ff0,0x0000,0x0000,0x0000, */
0xc02d,0x7b59,0x0b5e,0x0eab,
0x4051,0x9fc0,0x25fe,0x9054,
0xc062,0x65bb,0x6d35,0x76d7,
0x4061,0x7056,0x84ff,0xbf9d,
0xc048,0x9822,0x0a36,0x07ac,
};
#endif

/* arcsin(1-x) = pi/2 - sqrt(2x)(1+R(x))
   0 <= x <= 0.5
   Peak relative error = 4.2e-18  */
#if UNK
const static double R[5] = {
 2.967721961301243206100E-3,
-5.634242780008963776856E-1,
 6.968710824104713396794E0,
-2.556901049652824852289E1,
 2.853665548261061424989E1,
};
const static double S[4] = {
/* 1.000000000000000000000E0, */
-2.194779531642920639778E1,
 1.470656354026814941758E2,
-3.838770957603691357202E2,
 3.424398657913078477438E2,
};
#endif
#if DEC
static short R[20] = {
0036102,0077034,0142164,0174103,
0140020,0036222,0147711,0044173,
0040736,0177655,0153631,0171523,
0141314,0106525,0060015,0055474,
0041344,0045422,0003630,0040344,
};
static short S[16] = {
/* 0040200,0000000,0000000,0000000, */
0141257,0112425,0132772,0166136,
0042023,0010315,0075523,0175020,
0142277,0170104,0126203,0017563,
0042253,0034115,0102662,0022757,
};
#endif
#if IBMPC
static short R[20] = {
0x9f08,0x988e,0x4fc3,0x3f68,
0x290f,0x59f9,0x0792,0xbfe2,
0x3e6a,0xbaf3,0xdff5,0x401b,
0xab68,0xac01,0x91aa,0xc039,
0x081d,0x40f3,0x8962,0x403c,
};
static short S[16] = {
/* 0x0000,0x0000,0x0000,0x3ff0, */
0x5d8c,0xb6bf,0xf2a2,0xc035,
0x7f42,0xaf6a,0x6219,0x4062,
0x63ee,0x9590,0xfe08,0xc077,
0x44be,0xb0b6,0x6709,0x4075,
};
#endif
#if MIEEE
static short R[20] = {
0x3f68,0x4fc3,0x988e,0x9f08,
0xbfe2,0x0792,0x59f9,0x290f,
0x401b,0xdff5,0xbaf3,0x3e6a,
0xc039,0x91aa,0xac01,0xab68,
0x403c,0x8962,0x40f3,0x081d,
};
static short S[16] = {
/* 0x3ff0,0x0000,0x0000,0x0000, */
0xc035,0xf2a2,0xb6bf,0x5d8c,
0x4062,0x6219,0xaf6a,0x7f42,
0xc077,0xfe08,0x9590,0x63ee,
0x4075,0x6709,0xb0b6,0x44be,
};
#endif

/* pi/2 = PIO2 + MOREBITS.  */
#ifdef DEC
#define MOREBITS 5.721188726109831840122E-18
#else
#define MOREBITS 6.123233995736765886130E-17
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double sqrt ( double );
double asin ( double );
#else
double sqrt(), polevl(), p1evl();
double asin();
#endif
extern double PIO2, PIO4, NAN;

double asin(x)
double x;
{
double a, p, z, zz;
short sign;

if( x > 0 )
	{
	sign = 1;
	a = x;
	}
else
	{
	sign = -1;
	a = -x;
	}

if( a > 1.0 )
	{
	mtherr( "asin", DOMAIN );
	return( NAN );
	}

if( a > 0.625 )
	{
	/* arcsin(1-x) = pi/2 - sqrt(2x)(1+R(x))  */
	zz = 1.0 - a;
	p = zz * polevl( zz, R, 4)/p1evl( zz, S, 4);
	zz = sqrt(zz+zz);
	z = PIO4 - zz;
	zz = zz * p - MOREBITS;
	z = z - zz;
	z = z + PIO4;
	}
else
	{
	if( a < 1.0e-8 )
		{
		return(x);
		}
	zz = a * a;
	z = zz * polevl( zz, P, 5)/p1evl( zz, Q, 5);
	z = a * z + a;
	}
if( sign < 0 )
	z = -z;
return(z);
}



double acos(x)
double x;
{
double z;

if( (x < -1.0) || (x > 1.0) )
	{
	mtherr( "acos", DOMAIN );
	return( NAN );
	}
if( x > 0.5 )
	{
	return( 2.0 * asin(  sqrt(0.5 - 0.5*x) ) );
	}
z = PIO4 - asin(x);
z = z + MOREBITS;
z = z + PIO4;
return( z );
}

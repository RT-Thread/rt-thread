/*							atan.c
 *
 *	Inverse circular tangent
 *      (arctangent)
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, atan();
 *
 * y = atan( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle between -pi/2 and +pi/2 whose tangent
 * is x.
 *
 * Range reduction is from three intervals into the interval
 * from zero to 0.66.  The approximant uses a rational
 * function of degree 4/5 of the form x + x**3 P(x)/Q(x).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       -10, 10     50000       2.4e-17     8.3e-18
 *    IEEE      -10, 10      10^6       1.8e-16     5.0e-17
 *
 */
/*							atan2()
 *
 *	Quadrant correct inverse circular tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, z, atan2();
 *
 * z = atan2( y, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle whose tangent is y/x.
 * Define compile time symbol ANSIC = 1 for ANSI standard,
 * range -PI < z <= +PI, args (y,x); else ANSIC = 0 for range
 * 0 to 2PI, args (x,y).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10, 10      10^6       2.5e-16     6.9e-17
 * See atan.c.
 *
 */

/*							atan.c */


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/


#include "mconf.h"

/* arctan(x)  = x + x^3 P(x^2)/Q(x^2)
   0 <= x <= 0.66
   Peak relative error = 2.6e-18  */
#ifdef UNK
const static double P[5] = {
-8.750608600031904122785E-1,
-1.615753718733365076637E1,
-7.500855792314704667340E1,
-1.228866684490136173410E2,
-6.485021904942025371773E1,
};
const static double Q[5] = {
/* 1.000000000000000000000E0, */
 2.485846490142306297962E1,
 1.650270098316988542046E2,
 4.328810604912902668951E2,
 4.853903996359136964868E2,
 1.945506571482613964425E2,
};

/* tan( 3*pi/8 ) */
const static double T3P8 = 2.41421356237309504880;
#endif

#ifdef DEC
static short P[20] = {
0140140,0001775,0007671,0026242,
0141201,0041242,0155534,0001715,
0141626,0002141,0132100,0011625,
0141765,0142771,0064055,0150453,
0141601,0131517,0164507,0062164,
};
static short Q[20] = {
/* 0040200,0000000,0000000,0000000, */
0041306,0157042,0154243,0000742,
0042045,0003352,0016707,0150452,
0042330,0070306,0113425,0170730,
0042362,0130770,0116602,0047520,
0042102,0106367,0156753,0013541,
};

/* tan( 3*pi/8 ) = 2.41421356237309504880 */
static unsigned short T3P8A[] = {040432,0101171,0114774,0167462,};
#define T3P8 *(double *)T3P8A
#endif

#ifdef IBMPC
static short P[20] = {
0x2594,0xa1f7,0x007f,0xbfec,
0x807a,0x5b6b,0x2854,0xc030,
0x0273,0x3688,0xc08c,0xc052,
0xba25,0x2d05,0xb8bf,0xc05e,
0xec8e,0xfd28,0x3669,0xc050,
};
static short Q[20] = {
/* 0x0000,0x0000,0x0000,0x3ff0, */
0x603c,0x5b14,0xdbc4,0x4038,
0xfa25,0x43b8,0xa0dd,0x4064,
0xbe3b,0xd2e2,0x0e18,0x407b,
0x49ea,0x13b0,0x563f,0x407e,
0x62ec,0xfbbd,0x519e,0x4068,
};

/* tan( 3*pi/8 ) = 2.41421356237309504880 */
static unsigned short T3P8A[] = {0x9de6,0x333f,0x504f,0x4003};
#define T3P8 *(double *)T3P8A
#endif

#ifdef MIEEE
static short P[20] = {
0xbfec,0x007f,0xa1f7,0x2594,
0xc030,0x2854,0x5b6b,0x807a,
0xc052,0xc08c,0x3688,0x0273,
0xc05e,0xb8bf,0x2d05,0xba25,
0xc050,0x3669,0xfd28,0xec8e,
};
static short Q[20] = {
/* 0x3ff0,0x0000,0x0000,0x0000, */
0x4038,0xdbc4,0x5b14,0x603c,
0x4064,0xa0dd,0x43b8,0xfa25,
0x407b,0x0e18,0xd2e2,0xbe3b,
0x407e,0x563f,0x13b0,0x49ea,
0x4068,0x519e,0xfbbd,0x62ec,
};

/* tan( 3*pi/8 ) = 2.41421356237309504880 */
static unsigned short T3P8A[] = {
0x4003,0x504f,0x333f,0x9de6
};
#define T3P8 *(double *)T3P8A
#endif

#ifdef ANSIPROT
extern double polevl ( double, void *, int );
extern double p1evl ( double, void *, int );
extern double atan ( double );
extern double fabs ( double );
extern int signbit ( double );
extern int isnan ( double );
#else
double polevl(), p1evl(), atan(), fabs();
int signbit(), isnan();
#endif
extern double PI, PIO2, PIO4, INFINITY, NEGZERO, MAXNUM;

/* pi/2 = PIO2 + MOREBITS.  */
#ifdef DEC
#define MOREBITS 5.721188726109831840122E-18
#else
#define MOREBITS 6.123233995736765886130E-17
#endif


double atan(x)
double x;
{
double y, z;
short sign, flag;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef INFINITIES
if(x == INFINITY)
	return(PIO2);
if(x == -INFINITY)
	return(-PIO2);
#endif
/* make argument positive and save the sign */
sign = 1;
if( x < 0.0 )
	{
	sign = -1;
	x = -x;
	}
/* range reduction */
flag = 0;
if( x > T3P8 )
	{
	y = PIO2;
	flag = 1;
	x = -( 1.0/x );
	}
else if( x <= 0.66 )
	{
	y = 0.0;
	}
else
	{
	y = PIO4;
	flag = 2;
	x = (x-1.0)/(x+1.0);
	}
z = x * x;
z = z * polevl( z, P, 4 ) / p1evl( z, Q, 5 );
z = x * z + x;
if( flag == 2 )
	z += 0.5 * MOREBITS;
else if( flag == 1 )
	z += MOREBITS;
y = y + z;
if( sign < 0 )
	y = -y;
return(y);
}

/*							atan2	*/

#ifdef ANSIC
double atan2( y, x )
#else
double atan2( x, y )
#endif
double x, y;
{
double z, w;
short code;

code = 0;

#ifdef NANS
if( isnan(x) )
	return(x);
if( isnan(y) )
	return(y);
#endif
#ifdef MINUSZERO
if( y == 0.0 )
	{
	if( signbit(y) )
		{
		if( x > 0.0 )
			z = y;
		else if( x < 0.0 )
			z = -PI;
		else
			{
			if( signbit(x) )
				z = -PI;
			else
				z = y;
			}
		}
	else /* y is +0 */
		{
		if( x == 0.0 )
			{
			if( signbit(x) )
				z = PI;
			else
				z = 0.0;
			}
		else if( x > 0.0 )
			z = 0.0;
		else
			z = PI;
		}
	return z;
	}
if( x == 0.0 )
	{
	if( y > 0.0 )
		z = PIO2;
	else
		z = -PIO2;
	return z;
	}
#endif /* MINUSZERO */
#ifdef INFINITIES
if( x == INFINITY )
	{
	if( y == INFINITY )
		z = 0.25 * PI;
	else if( y == -INFINITY )
		z = -0.25 * PI;
	else if( y < 0.0 )
		z = NEGZERO;
	else
		z = 0.0;
	return z;
	}
if( x == -INFINITY )
	{
	if( y == INFINITY )
		z = 0.75 * PI;
	else if( y <= -INFINITY )
		z = -0.75 * PI;
	else if( y >= 0.0 )
		z = PI;
	else
		z = -PI;
	return z;
	}
if( y == INFINITY )
	return( PIO2 );
if( y == -INFINITY )
	return( -PIO2 );
#endif

if( x < 0.0 )
	code = 2;
if( y < 0.0 )
	code |= 1;

#ifdef INFINITIES
if( x == 0.0 )
#else
if( fabs(x) <= (fabs(y) / MAXNUM) )
#endif
	{
	if( code & 1 )
		{
#if ANSIC
		return( -PIO2 );
#else
		return( 3.0*PIO2 );
#endif
		}
	if( y == 0.0 )
		return( 0.0 );
	return( PIO2 );
	}

if( y == 0.0 )
	{
	if( code & 2 )
		return( PI );
	return( 0.0 );
	}


switch( code )
	{
#if ANSIC
	default:
	case 0:
	case 1: w = 0.0; break;
	case 2: w = PI; break;
	case 3: w = -PI; break;
#else
	default:
	case 0: w = 0.0; break;
	case 1: w = 2.0 * PI; break;
	case 2:
	case 3: w = PI; break;
#endif
	}

z = w + atan( y/x );
#ifdef MINUSZERO
if( z == 0.0 && y < 0 )
	z = NEGZERO;
#endif
return( z );
}

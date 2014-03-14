/*							atanh.c
 *
 *	Inverse hyperbolic tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, atanh();
 *
 * y = atanh( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns inverse hyperbolic tangent of argument in the range
 * MINLOG to MAXLOG.
 *
 * If |x| < 0.5, the rational form x + x**3 P(x)/Q(x) is
 * employed.  Otherwise,
 *        atanh(x) = 0.5 * log( (1+x)/(1-x) ).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       -1,1        50000       2.4e-17     6.4e-18
 *    IEEE      -1,1        30000       1.9e-16     5.2e-17
 *
 */

/*						atanh.c	*/


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright (C) 1987, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
const static double P[] = {
-8.54074331929669305196E-1,
 1.20426861384072379242E1,
-4.61252884198732692637E1,
 6.54566728676544377376E1,
-3.09092539379866942570E1
};
const static double Q[] = {
/* 1.00000000000000000000E0,*/
-1.95638849376911654834E1,
 1.08938092147140262656E2,
-2.49839401325893582852E2,
 2.52006675691344555838E2,
-9.27277618139601130017E1
};
#endif
#ifdef DEC
static unsigned short P[] = {
0140132,0122235,0105775,0130300,
0041100,0127327,0124407,0034722,
0141470,0100113,0115607,0130535,
0041602,0164721,0003257,0013673,
0141367,0043046,0166673,0045750
};
static unsigned short Q[] = {
/*0040200,0000000,0000000,0000000,*/
0141234,0101326,0015460,0134564,
0041731,0160115,0116451,0032045,
0142171,0153343,0000532,0167226,
0042174,0000665,0077604,0000310,
0141671,0072235,0031114,0074377
};
#endif

#ifdef IBMPC
static unsigned short P[] = {
0xb618,0xb17f,0x5493,0xbfeb,
0xe73a,0xf520,0x15da,0x4028,
0xf62c,0x7370,0x1009,0xc047,
0xe2f7,0x20d5,0x5d3a,0x4050,
0x697d,0xddb7,0xe8c4,0xc03e
};
static unsigned short Q[] = {
/*0x0000,0x0000,0x0000,0x3ff0,*/
0x172f,0xc366,0x905a,0xc033,
0x2685,0xb3a5,0x3c09,0x405b,
0x5dd3,0x602b,0x3adc,0xc06f,
0x8019,0xaff0,0x8036,0x406f,
0x8f20,0xa649,0x2e93,0xc057
};
#endif

#ifdef MIEEE
static unsigned short P[] = {
0xbfeb,0x5493,0xb17f,0xb618,
0x4028,0x15da,0xf520,0xe73a,
0xc047,0x1009,0x7370,0xf62c,
0x4050,0x5d3a,0x20d5,0xe2f7,
0xc03e,0xe8c4,0xddb7,0x697d
};
static unsigned short Q[] = {
0xc033,0x905a,0xc366,0x172f,
0x405b,0x3c09,0xb3a5,0x2685,
0xc06f,0x3adc,0x602b,0x5dd3,
0x406f,0x8036,0xaff0,0x8019,
0xc057,0x2e93,0xa649,0x8f20
};
#endif

#ifdef ANSIPROT
extern double fabs ( double );
extern double log ( double x );
extern double polevl ( double x, void *P, int N );
extern double p1evl ( double x, void *P, int N );
#else
double fabs(), log(), polevl(), p1evl();
#endif
extern double INFINITY, NAN;

double atanh(x)
double x;
{
double s, z;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
z = fabs(x);
if( z >= 1.0 )
	{
	if( x == 1.0 )
		return( INFINITY );
	if( x == -1.0 )
		return( -INFINITY );
	mtherr( "atanh", DOMAIN );
	return( NAN );
	}

if( z < 1.0e-7 )
	return(x);

if( z < 0.5 )
	{
	z = x * x;
	s = x   +  x * z * (polevl(z, P, 4) / p1evl(z, Q, 5));
	return(s);
	}

return( 0.5 * log((1.0+x)/(1.0-x)) );
}

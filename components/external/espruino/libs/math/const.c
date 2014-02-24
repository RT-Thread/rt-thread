/*							const.c
 *
 *	Globally declared constants
 *
 *
 *
 * SYNOPSIS:
 *
 * extern const double nameofconstant;
 *
 *
 *
 *
 * DESCRIPTION:
 *
 * This file contains a number of mathematical constants and
 * also some needed size parameters of the computer arithmetic.
 * The values are supplied as arrays of hexadecimal integers
 * for IEEE arithmetic; arrays of octal constants for DEC
 * arithmetic; and in a normal decimal scientific notation for
 * other machines.  The particular notation used is determined
 * by a symbol (DEC, IBMPC, or UNK) defined in the include file
 * mconf.h.
 *
 * The default size parameters are as follows.
 *
 * For DEC and UNK modes:
 * MACHEP =  1.38777878078144567553E-17       2**-56
 * MAXLOG =  8.8029691931113054295988E1       log(2**127)
 * MINLOG = -8.872283911167299960540E1        log(2**-128)
 * MAXNUM =  1.701411834604692317316873e38    2**127
 *
 * For IEEE arithmetic (IBMPC):
 * MACHEP =  1.11022302462515654042E-16       2**-53
 * MAXLOG =  7.09782712893383996843E2         log(2**1024)
 * MINLOG = -7.08396418532264106224E2         log(2**-1022)
 * MAXNUM =  1.7976931348623158E308           2**1024
 *
 * The global symbols for mathematical constants are
 * PI     =  3.14159265358979323846           pi
 * PIO2   =  1.57079632679489661923           pi/2
 * PIO4   =  7.85398163397448309616E-1        pi/4
 * SQRT2  =  1.41421356237309504880           sqrt(2)
 * SQRTH  =  7.07106781186547524401E-1        sqrt(2)/2
 * LOG2E  =  1.4426950408889634073599         1/log(2)
 * SQ2OPI =  7.9788456080286535587989E-1      sqrt( 2/pi )
 * LOGE2  =  6.93147180559945309417E-1        log(2)
 * LOGSQ2 =  3.46573590279972654709E-1        log(2)/2
 * THPIO4 =  2.35619449019234492885           3*pi/4
 * TWOOPI =  6.36619772367581343075535E-1     2/pi
 *
 * These lists are subject to change.
 */

/*							const.c */

/*
Cephes Math Library Release 2.3:  March, 1995
Copyright 1984, 1995 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
#if 1
const double MACHEP =  1.11022302462515654042E-16;   /* 2**-53 */
#else
const double MACHEP =  1.38777878078144567553E-17;   /* 2**-56 */
#endif
const double UFLOWTHRESH =  2.22507385850720138309E-308; /* 2**-1022 */
#ifdef DENORMAL
const double MAXLOG =  7.09782712893383996732E2;     /* log(MAXNUM) */
/* const double MINLOG = -7.44440071921381262314E2; */     /* log(2**-1074) */
const double MINLOG = -7.451332191019412076235E2;     /* log(2**-1075) */
#else
const double MAXLOG =  7.08396418532264106224E2;     /* log 2**1022 */
const double MINLOG = -7.08396418532264106224E2;     /* log 2**-1022 */
#endif
const double MAXNUM =  1.79769313486231570815E308;    /* 2**1024*(1-MACHEP) */
const double PI     =  3.14159265358979323846;       /* pi */
const double PIO2   =  1.57079632679489661923;       /* pi/2 */
const double PIO4   =  7.85398163397448309616E-1;    /* pi/4 */
const double SQRT2  =  1.41421356237309504880;       /* sqrt(2) */
const double SQRTH  =  7.07106781186547524401E-1;    /* sqrt(2)/2 */
const double LOG2E  =  1.4426950408889634073599;     /* 1/log(2) */
const double SQ2OPI =  7.9788456080286535587989E-1;  /* sqrt( 2/pi ) */
const double LOGE2  =  6.93147180559945309417E-1;    /* log(2) */
const double LOGSQ2 =  3.46573590279972654709E-1;    /* log(2)/2 */
const double THPIO4 =  2.35619449019234492885;       /* 3*pi/4 */
const double TWOOPI =  6.36619772367581343075535E-1; /* 2/pi */
#ifdef INFINITIES
const double INFINITY = 1.0/0.0;  /* 99e999; */
#else
const double INFINITY =  1.79769313486231570815E308;    /* 2**1024*(1-MACHEP) */
#endif
#ifdef NANS
const double NAN = 1.0/0.0 - 1.0/0.0;
#else
const double NAN = 0.0;
#endif
#ifdef MINUSZERO
const double NEGZERO = -0.0;
#else
const double NEGZERO = 0.0;
#endif
#endif

#ifdef IBMPC
			/* 2**-53 =  1.11022302462515654042E-16 */
const unsigned short MACHEP[4] = {0x0000,0x0000,0x0000,0x3ca0};
const unsigned short UFLOWTHRESH[4] = {0x0000,0x0000,0x0000,0x0010};
#ifdef DENORMAL
			/* log(MAXNUM) =  7.09782712893383996732224E2 */
const unsigned short MAXLOG[4] = {0x39ef,0xfefa,0x2e42,0x4086};
			/* log(2**-1074) = - -7.44440071921381262314E2 */
/*const unsigned short MINLOG[4] = {0x71c3,0x446d,0x4385,0xc087};*/
const unsigned short MINLOG[4] = {0x3052,0xd52d,0x4910,0xc087};
#else
			/* log(2**1022) =   7.08396418532264106224E2 */
const unsigned short MAXLOG[4] = {0xbcd2,0xdd7a,0x232b,0x4086};
			/* log(2**-1022) = - 7.08396418532264106224E2 */
const unsigned short MINLOG[4] = {0xbcd2,0xdd7a,0x232b,0xc086};
#endif
			/* 2**1024*(1-MACHEP) =  1.7976931348623158E308 */
const unsigned short MAXNUM[4] = {0xffff,0xffff,0xffff,0x7fef};
const unsigned short PI[4]     = {0x2d18,0x5444,0x21fb,0x4009};
const unsigned short PIO2[4]   = {0x2d18,0x5444,0x21fb,0x3ff9};
const unsigned short PIO4[4]   = {0x2d18,0x5444,0x21fb,0x3fe9};
const unsigned short SQRT2[4]  = {0x3bcd,0x667f,0xa09e,0x3ff6};
const unsigned short SQRTH[4]  = {0x3bcd,0x667f,0xa09e,0x3fe6};
const unsigned short LOG2E[4]  = {0x82fe,0x652b,0x1547,0x3ff7};
const unsigned short SQ2OPI[4] = {0x3651,0x33d4,0x8845,0x3fe9};
const unsigned short LOGE2[4]  = {0x39ef,0xfefa,0x2e42,0x3fe6};
const unsigned short LOGSQ2[4] = {0x39ef,0xfefa,0x2e42,0x3fd6};
const unsigned short THPIO4[4] = {0x21d2,0x7f33,0xd97c,0x4002};
const unsigned short TWOOPI[4] = {0xc883,0x6dc9,0x5f30,0x3fe4};
#ifdef INFINITIES
const unsigned short INFINITY[4] = {0x0000,0x0000,0x0000,0x7ff0};
#else
const unsigned short INFINITY[4] = {0xffff,0xffff,0xffff,0x7fef};
#endif
#ifdef NANS
const unsigned short NAN[4] = {0x0000,0x0000,0x0000,0x7ffc};
#else
const unsigned short NAN[4] = {0x0000,0x0000,0x0000,0x0000};
#endif
#ifdef MINUSZERO
const unsigned short NEGZERO[4] = {0x0000,0x0000,0x0000,0x8000};
#else
const unsigned short NEGZERO[4] = {0x0000,0x0000,0x0000,0x0000};
#endif
#endif

#ifdef MIEEE
			/* 2**-53 =  1.11022302462515654042E-16 */
const unsigned short MACHEP[4] = {0x3ca0,0x0000,0x0000,0x0000};
const unsigned short UFLOWTHRESH[4] = {0x0010,0x0000,0x0000,0x0000};
#ifdef DENORMAL
			/* log(2**1024) =   7.09782712893383996843E2 */
const unsigned short MAXLOG[4] = {0x4086,0x2e42,0xfefa,0x39ef};
			/* log(2**-1074) = - -7.44440071921381262314E2 */
/* const unsigned short MINLOG[4] = {0xc087,0x4385,0x446d,0x71c3}; */
const unsigned short MINLOG[4] = {0xc087,0x4910,0xd52d,0x3052};
#else
			/* log(2**1022) =  7.08396418532264106224E2 */
const unsigned short MAXLOG[4] = {0x4086,0x232b,0xdd7a,0xbcd2};
			/* log(2**-1022) = - 7.08396418532264106224E2 */
const unsigned short MINLOG[4] = {0xc086,0x232b,0xdd7a,0xbcd2};
#endif
			/* 2**1024*(1-MACHEP) =  1.7976931348623158E308 */
const unsigned short MAXNUM[4] = {0x7fef,0xffff,0xffff,0xffff};
const unsigned short PI[4]     = {0x4009,0x21fb,0x5444,0x2d18};
const unsigned short PIO2[4]   = {0x3ff9,0x21fb,0x5444,0x2d18};
const unsigned short PIO4[4]   = {0x3fe9,0x21fb,0x5444,0x2d18};
const unsigned short SQRT2[4]  = {0x3ff6,0xa09e,0x667f,0x3bcd};
const unsigned short SQRTH[4]  = {0x3fe6,0xa09e,0x667f,0x3bcd};
const unsigned short LOG2E[4]  = {0x3ff7,0x1547,0x652b,0x82fe};
const unsigned short SQ2OPI[4] = {0x3fe9,0x8845,0x33d4,0x3651};
const unsigned short LOGE2[4]  = {0x3fe6,0x2e42,0xfefa,0x39ef};
const unsigned short LOGSQ2[4] = {0x3fd6,0x2e42,0xfefa,0x39ef};
const unsigned short THPIO4[4] = {0x4002,0xd97c,0x7f33,0x21d2};
const unsigned short TWOOPI[4] = {0x3fe4,0x5f30,0x6dc9,0xc883};
#ifdef INFINITIES
const unsigned short INFINITY[4] = {0x7ff0,0x0000,0x0000,0x0000};
#else
const unsigned short INFINITY[4] = {0x7fef,0xffff,0xffff,0xffff};
#endif
#ifdef NANS
const unsigned short NAN[4] = {0x7ff8,0x0000,0x0000,0x0000};
#else
const unsigned short NAN[4] = {0x0000,0x0000,0x0000,0x0000};
#endif
#ifdef MINUSZERO
const unsigned short NEGZERO[4] = {0x8000,0x0000,0x0000,0x0000};
#else
const unsigned short NEGZERO[4] = {0x0000,0x0000,0x0000,0x0000};
#endif
#endif

#ifdef DEC
			/* 2**-56 =  1.38777878078144567553E-17 */
const unsigned short MACHEP[4] = {0022200,0000000,0000000,0000000};
const unsigned short UFLOWTHRESH[4] = {0x0080,0x0000,0x0000,0x0000};
			/* log 2**127 = 88.029691931113054295988 */
const unsigned short MAXLOG[4] = {041660,007463,0143742,025733,};
			/* log 2**-128 = -88.72283911167299960540 */
const unsigned short MINLOG[4] = {0141661,071027,0173721,0147572,};
			/* 2**127 = 1.701411834604692317316873e38 */
const unsigned short MAXNUM[4] = {077777,0177777,0177777,0177777,};
const unsigned short PI[4]     = {040511,007732,0121041,064302,};
const unsigned short PIO2[4]   = {040311,007732,0121041,064302,};
const unsigned short PIO4[4]   = {040111,007732,0121041,064302,};
const unsigned short SQRT2[4]  = {040265,002363,031771,0157145,};
const unsigned short SQRTH[4]  = {040065,002363,031771,0157144,};
const unsigned short LOG2E[4]  = {040270,0125073,024534,013761,};
const unsigned short SQ2OPI[4] = {040114,041051,0117241,0131204,};
const unsigned short LOGE2[4]  = {040061,071027,0173721,0147572,};
const unsigned short LOGSQ2[4] = {037661,071027,0173721,0147572,};
const unsigned short THPIO4[4] = {040426,0145743,0174631,007222,};
const unsigned short TWOOPI[4] = {040042,0174603,067116,042025,};
/* Approximate infinity by MAXNUM.  */
const unsigned short INFINITY[4] = {077777,0177777,0177777,0177777,};
const unsigned short NAN[4] = {0000000,0000000,0000000,0000000};
#ifdef MINUSZERO
const unsigned short NEGZERO[4] = {0000000,0000000,0000000,0100000};
#else
const unsigned short NEGZERO[4] = {0000000,0000000,0000000,0000000};
#endif
#endif

#ifndef UNK
extern const unsigned short MACHEP[];
extern const unsigned short UFLOWTHRESH[];
extern const unsigned short MAXLOG[];
extern const unsigned short UNDLOG[];
extern const unsigned short MINLOG[];
extern const unsigned short MAXNUM[];
extern const unsigned short PI[];
extern const unsigned short PIO2[];
extern const unsigned short PIO4[];
extern const unsigned short SQRT2[];
extern const unsigned short SQRTH[];
extern const unsigned short LOG2E[];
extern const unsigned short SQ2OPI[];
extern const unsigned short LOGE2[];
extern const unsigned short LOGSQ2[];
extern const unsigned short THPIO4[];
extern const unsigned short TWOOPI[];
extern const unsigned short INFINITY[];
extern const unsigned short NAN[];
extern const unsigned short NEGZERO[];
#endif

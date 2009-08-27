/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis 'TREMOR' CODEC SOURCE CODE.   *
 *                                                                  *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis 'TREMOR' SOURCE CODE IS (C) COPYRIGHT 1994-2002    *
 * BY THE Xiph.Org FOUNDATION http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: normalized modified discrete cosine transform
           power of two length transform only [64 <= n ]


 Original algorithm adapted long ago from _The use of multirate filter
 banks for coding of high quality digital audio_, by T. Sporer,
 K. Brandenburg and B. Edler, collection of the European Signal
 Processing Conference (EUSIPCO), Amsterdam, June 1992, Vol.1, pp
 211-214

 The below code implements an algorithm that no longer looks much like
 that presented in the paper, but the basic structure remains if you
 dig deep enough to see it.

 This module DOES NOT INCLUDE code to generate/apply the window
 function.  Everybody has their own weird favorite including me... I
 happen to like the properties of y=sin(.5PI*sin^2(x)), but others may
 vehemently disagree.

 ********************************************************************/

/*Tremor IMDCT adapted for use with libwmai*/


#include "mdct2.h"
#include "mdct_lookup.h"
#include "codeclib.h"
#include "asm_arm.h"

extern void mdct_butterfly_32(int32_t *x);
extern void mdct_butterfly_generic_loop(int32_t *x1, int32_t *x2,
	const int32_t *T0, int step,
	const int32_t *Ttop);

static inline void mdct_butterfly_generic(int32_t *x,int points, int step)
{
	mdct_butterfly_generic_loop(x + points, x + (points>>1),  sincos_lookup0, step, sincos_lookup0+1024);
}

static inline void mdct_butterflies(int32_t *x,int points,int shift)
{
	int stages=8-shift;
	int i,j;

	for(i=0;--stages>0;i++)
	{
		for(j=0;j<(1<<i);j++)
			mdct_butterfly_generic(x+(points>>i)*j,points>>i,4<<(i+shift));
	}

	for(j=0;j<points;j+=32)
		mdct_butterfly_32(x+j);
}


static const unsigned char bitrev[16]=
	{
		0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15
	};

static inline int bitrev12(int x)
{
	return bitrev[x>>8]|(bitrev[(x&0x0f0)>>4]<<4)|(((int)bitrev[x&0x00f])<<8);
}

static inline void mdct_bitreverse(int32_t *x,int n,int step,int shift)
{
	int          bit   = 0;
	int32_t   *w0    = x;
	int32_t   *w1    = x = w0+(n>>1);
	const int32_t    *T = (step>=4)?(sincos_lookup0+(step>>1)):sincos_lookup1;
	const int32_t    *Ttop  = T+1024;
	int32_t    r2;

	do
	{
		int32_t r3      = bitrev12(bit++);
		int32_t *x0    = x + ((r3 ^ 0xfff)>>shift) -1;
		int32_t *x1    = x + (r3>>shift);

		register int32_t  r0     = x0[0]  + x1[0];
		register int32_t  r1     = x1[1]  - x0[1];

		XPROD32( r0, r1, T[1], T[0], &r2, &r3 );
		T+=step;

		w1    -= 4;

		r0     = (x0[1] + x1[1])>>1;
		r1     = (x0[0] - x1[0])>>1;
		w0[0]  = r0     + r2;
		w0[1]  = r1     + r3;
		w1[2]  = r0     - r2;
		w1[3]  = r3     - r1;

		r3     = bitrev12(bit++);
		x0     = x + ((r3 ^ 0xfff)>>shift) -1;
		x1     = x + (r3>>shift);

		r0     = x0[0]  + x1[0];
		r1     = x1[1]  - x0[1];

		XPROD32( r0, r1, T[1], T[0], &r2, &r3 );
		T+=step;

		r0     = (x0[1] + x1[1])>>1;
		r1     = (x0[0] - x1[0])>>1;
		w0[2]  = r0     + r2;
		w0[3]  = r1     + r3;
		w1[0]  = r0     - r2;
		w1[1]  = r3     - r1;

		w0    += 4;
	}
	while(T<Ttop);

	do
	{
		int32_t r3     = bitrev12(bit++);
		int32_t *x0    = x + ((r3 ^ 0xfff)>>shift) -1;
		int32_t *x1    = x + (r3>>shift);

		register int32_t  r0     = x0[0]  + x1[0];
		register int32_t  r1     = x1[1]  - x0[1];

		T-=step;
		XPROD32( r0, r1, T[0], T[1], &r2, &r3 );

		w1    -= 4;

		r0     = (x0[1] + x1[1])>>1;
		r1     = (x0[0] - x1[0])>>1;
		w0[0]  = r0     + r2;
		w0[1]  = r1     + r3;
		w1[2]  = r0     - r2;
		w1[3]  = r3     - r1;

		r3     = bitrev12(bit++);
		x0     = x + ((r3 ^ 0xfff)>>shift) -1;
		x1     = x + (r3>>shift);

		r0     = x0[0]  + x1[0];
		r1     = x1[1]  - x0[1];

		T-=step;
		XPROD32( r0, r1, T[0], T[1], &r2, &r3 );

		r0     = (x0[1] + x1[1])>>1;
		r1     = (x0[0] - x1[0])>>1;
		w0[2]  = r0     + r2;
		w0[3]  = r1     + r3;
		w1[0]  = r0     - r2;
		w1[1]  = r3     - r1;

		w0    += 4;
	}
	while(w0<w1);
}

void mdct_backward(int n, int32_t *in, int32_t *out)
{
	int n2=n>>1;
	int n4=n>>2;
	int32_t *iX;
	int32_t *oX;
	const int32_t *T;
	const int32_t *V;
	int shift;
	int step;
	for (shift=6;!(n&(1<<shift));shift++);
	shift=13-shift;
	step=2<<shift;

	/* rotate */

	iX            = in+n2-7;
	oX            = out+n2+n4;
	T             = sincos_lookup0;

	do
	{
		oX-=4;
		XPROD31( iX[4], iX[6], T[0], T[1], &oX[2], &oX[3] );
		T+=step;
		XPROD31( iX[0], iX[2], T[0], T[1], &oX[0], &oX[1] );
		T+=step;
		iX-=8;
	}
	while(iX>=in+n4);
	do
	{
		oX-=4;
		XPROD31( iX[4], iX[6], T[1], T[0], &oX[2], &oX[3] );
		T-=step;
		XPROD31( iX[0], iX[2], T[1], T[0], &oX[0], &oX[1] );
		T-=step;
		iX-=8;
	}
	while(iX>=in);

	iX            = in+n2-8;
	oX            = out+n2+n4;
	T             = sincos_lookup0;

	do
	{
		T+=step;
		XNPROD31( iX[6], iX[4], T[0], T[1], &oX[0], &oX[1] );
		T+=step;
		XNPROD31( iX[2], iX[0], T[0], T[1], &oX[2], &oX[3] );
		iX-=8;
		oX+=4;
	}
	while(iX>=in+n4);
	do
	{
		T-=step;
		XNPROD31( iX[6], iX[4], T[1], T[0], &oX[0], &oX[1] );
		T-=step;
		XNPROD31( iX[2], iX[0], T[1], T[0], &oX[2], &oX[3] );
		iX-=8;
		oX+=4;
	}
	while(iX>=in);

	mdct_butterflies(out+n2,n2,shift);
	mdct_bitreverse(out,n,step,shift);
	/* rotate + window */

	step>>=2;
	{
		int32_t *oX1=out+n2+n4;
		int32_t *oX2=out+n2+n4;
		int32_t *iX =out;

		switch(step)
		{
		default:
		{
			T=(step>=4)?(sincos_lookup0+(step>>1)):sincos_lookup1;
			do
			{
				oX1-=4;
				XPROD31( iX[0], -iX[1], T[0], T[1], &oX1[3], &oX2[0] );
				T+=step;
				XPROD31( iX[2], -iX[3], T[0], T[1], &oX1[2], &oX2[1] );
				T+=step;
				XPROD31( iX[4], -iX[5], T[0], T[1], &oX1[1], &oX2[2] );
				T+=step;
				XPROD31( iX[6], -iX[7], T[0], T[1], &oX1[0], &oX2[3] );
				T+=step;
				oX2+=4;
				iX+=8;
			}
			while(iX<oX1);
			break;
		}

		case 1:
		{
			/* linear interpolation between table values: offset=0.5, step=1 */
			register int32_t  t0,t1,v0,v1;
			T         = sincos_lookup0;
			V         = sincos_lookup1;
			t0        = (*T++)>>1;
			t1        = (*T++)>>1;
			do
			{
				oX1-=4;

				t0 += (v0 = (*V++)>>1);
				t1 += (v1 = (*V++)>>1);
				XPROD31( iX[0], -iX[1], t0, t1, &oX1[3], &oX2[0] );
				v0 += (t0 = (*T++)>>1);
				v1 += (t1 = (*T++)>>1);
				XPROD31( iX[2], -iX[3], v0, v1, &oX1[2], &oX2[1] );
				t0 += (v0 = (*V++)>>1);
				t1 += (v1 = (*V++)>>1);
				XPROD31( iX[4], -iX[5], t0, t1, &oX1[1], &oX2[2] );
				v0 += (t0 = (*T++)>>1);
				v1 += (t1 = (*T++)>>1);
				XPROD31( iX[6], -iX[7], v0, v1, &oX1[0], &oX2[3] );

				oX2+=4;
				iX+=8;
			}
			while(iX<oX1);
			break;
		}

		case 0:
		{
			/* linear interpolation between table values: offset=0.25, step=0.5 */
			register int32_t  t0,t1,v0,v1,q0,q1;
			T         = sincos_lookup0;
			V         = sincos_lookup1;
			t0        = *T++;
			t1        = *T++;
			do
			{
				oX1-=4;

				v0  = *V++;
				v1  = *V++;
				t0 +=  (q0 = (v0-t0)>>2);
				t1 +=  (q1 = (v1-t1)>>2);
				XPROD31( iX[0], -iX[1], t0, t1, &oX1[3], &oX2[0] );
				t0  = v0-q0;
				t1  = v1-q1;
				XPROD31( iX[2], -iX[3], t0, t1, &oX1[2], &oX2[1] );

				t0  = *T++;
				t1  = *T++;
				v0 += (q0 = (t0-v0)>>2);
				v1 += (q1 = (t1-v1)>>2);
				XPROD31( iX[4], -iX[5], v0, v1, &oX1[1], &oX2[2] );
				v0  = t0-q0;
				v1  = t1-q1;
				XPROD31( iX[6], -iX[7], v0, v1, &oX1[0], &oX2[3] );

				oX2+=4;
				iX+=8;
			}
			while(iX<oX1);
			break;
		}
		}

		iX=out+n2+n4;
		oX1=out+n4;
		oX2=oX1;

		do
		{
			oX1-=4;
			iX-=4;

			oX2[0] = -(oX1[3] = iX[3]);
			oX2[1] = -(oX1[2] = iX[2]);
			oX2[2] = -(oX1[1] = iX[1]);
			oX2[3] = -(oX1[0] = iX[0]);

			oX2+=4;
		}
		while(oX2<iX);

		iX=out+n2+n4;
		oX1=out+n2+n4;
		oX2=out+n2;

		do
		{
			oX1-=4;
			oX1[0]= iX[3];
			oX1[1]= iX[2];
			oX1[2]= iX[1];
			oX1[3]= iX[0];
			iX+=4;
		}
		while(oX1>oX2);
	}
}

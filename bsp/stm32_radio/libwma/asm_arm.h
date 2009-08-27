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

 function: arm7 and later wide math functions

 ********************************************************************/

#ifndef __ASM_ARM_H__
#define __ASM_ARM_H__

int32_t MULT32(int32_t x, int32_t y);
int32_t MULT31(int32_t x, int32_t y);
int32_t MULT31_SHIFT15(int32_t x, int32_t y);

#define MB() 

void XPROD32(int32_t a, int32_t b,
	int32_t t, int32_t v,
	int32_t *x, int32_t *y);
void XPROD31(int32_t a, int32_t b,
	int32_t t, int32_t v,
	int32_t *x, int32_t *y);
void XNPROD31(int32_t a, int32_t b, 
	int32_t t, int32_t v,
	int32_t *x, int32_t *y);

int32_t CLIP_TO_15(int32_t x);

#endif

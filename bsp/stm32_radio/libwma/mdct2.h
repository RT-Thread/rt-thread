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

 function: modified discrete cosine transform prototypes

 ********************************************************************/

#ifndef _OGG_mdct_H_
#define _OGG_mdct_H_

#include "ffmpeg_config.h"

#ifdef _LOW_ACCURACY_
#  define X(n) (((((n)>>22)+1)>>1) - ((((n)>>22)+1)>>9))
#  //define LOOKUP_T const unsigned char
#else
#  define X(n) (n)
#  //define LOOKUP_T const ogg_int32_t
#endif

// #include <codecs.h>
#include "asm_arm.h"
// #include "asm_mcf5249.h"
// #include "codeclib_misc.h"

#ifndef ICONST_ATTR_TREMOR_WINDOW
#define ICONST_ATTR_TREMOR_WINDOW ICONST_ATTR
#endif

#ifndef ICODE_ATTR_TREMOR_MDCT
#define ICODE_ATTR_TREMOR_MDCT ICODE_ATTR
#endif

#ifndef ICODE_ATTR_TREMOR_NOT_MDCT
#define ICODE_ATTR_TREMOR_NOT_MDCT ICODE_ATTR
#endif



#ifdef _LOW_ACCURACY_
#define cPI3_8 (0x0062)
#define cPI2_8 (0x00b5)
#define cPI1_8 (0x00ed)
#else
#define cPI3_8 (0x30fbc54d)
#define cPI2_8 (0x5a82799a)
#define cPI1_8 (0x7641af3d)
#endif


extern void mdct_backward(int n, int32_t *in, int32_t *out);

#endif













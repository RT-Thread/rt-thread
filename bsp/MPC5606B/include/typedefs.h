/**************************************************************************
 * FILE NAME: $RCSfile: typedefs.h,v $       COPYRIGHT (c) Freescale 2005 *
 * DESCRIPTION:                                     All Rights Reserved   *
 * This file defines all of the data types for the Motorola header file.  *
 *========================================================================*
 * ORIGINAL AUTHOR: r12110                                                *
 * $Log: typedefs.h,v $
 * Revision 1.5 2016/05/23 11:20:19   b47769
 * Diab compiler compatibility
 *
 * Revision 1.4  2008/02/19 11:10:09  b04629
 * Fixed previous comment.
 *
 * Revision 1.3  2008/02/19 11:01:43  b04629
 * Replaced // comments for MISRA.
 *
 * Revision 1.2  2007/11/22 13:18:55  b04629
 * Removed original author name and replaced with author ID.
 *
 * Revision 1.1  2007/03/22 08:55:15  b04629
 * Imported and updated from MPC55xx Headers Rev 1.9
 *                                                                        *
 *                                                                        *
 **************************************************************************/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_
#if defined (__GNUC__)  /* GCC compiler*/
#include <stdint.h>
    /* Short names for volatiles used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;    

#elif defined (__MWERKS__)    /* Metrowerk CodeWarrior */
    #include <stdint.h>

    /*  Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;

#elif defined (__ghs__)    /* GreenHills */
    #include <stdint.h>

    /* Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;
#else
/* This is needed for compilers that don't have a stdint.h file i.e. DIAB */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef volatile signed char vint8_t;
typedef volatile unsigned char vuint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef volatile signed short vint16_t;
typedef volatile unsigned short vuint16_t;

typedef signed long int32_t;
typedef unsigned long uint32_t;
typedef volatile signed long vint32_t;
typedef volatile unsigned long vuint32_t;

/* 8-byte Extended type, supported by DIAB */
typedef long long int64_t;
typedef unsigned long long uint64_t;

#endif
#endif

/*********************************************************************
 *
 * Copyright:
 *	Freescale Semiconductor, INC. All Rights Reserved.
 *  You are hereby granted a copyright license to use, modify, and
 *  distribute the SOFTWARE so long as this entire notice is
 *  retained without alteration in any modified and/or redistributed
 *  versions, and that such modified versions are clearly identified
 *  as such. No licenses are granted by implication, estoppel or
 *  otherwise under any patents or trademarks of Freescale
 *  Semiconductor, Inc. This software is provided on an "AS IS"
 *  basis and without warranty.
 *
 *  To the maximum extent permitted by applicable law, Freescale
 *  Semiconductor DISCLAIMS ALL WARRANTIES WHETHER EXPRESS OR IMPLIED,
 *  INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A
 *  PARTICULAR PURPOSE AND ANY WARRANTY AGAINST INFRINGEMENT WITH
 *  REGARD TO THE SOFTWARE (INCLUDING ANY MODIFIED VERSIONS THEREOF)
 *  AND ANY ACCOMPANYING WRITTEN MATERIALS.
 *
 *  To the maximum extent permitted by applicable law, IN NO EVENT
 *  SHALL Freescale Semiconductor BE LIABLE FOR ANY DAMAGES WHATSOEVER
 *  (INCLUDING WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *  BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR OTHER
 *  PECUNIARY LOSS) ARISING OF THE USE OR INABILITY TO USE THE SOFTWARE.
 *
 *  Freescale Semiconductor assumes no responsibility for the
 *  maintenance and support of this software
 *
 ********************************************************************/



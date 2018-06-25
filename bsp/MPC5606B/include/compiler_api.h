/**************************************************************************
 * FILE NAME: compiler_api.h                COPYRIGHT (c) Freescale 2016  *
 *                                                All Rights Reserved     *
 * DESCRIPTION:  compiler specific file                                   *
 *                                                                        *
***************************************************************************/
#ifndef _COMPILER_API_H_
#define _COMPILER_API_H_

#if !defined(__GNUC__) && !defined(__ghs__) && !defined (__DCC__)
#error "Compiler is not defined"
#endif

#define stringify(s) tostring(s)
#define tostring(s) #s

/* definitions for assembler functions */

#ifdef __GNUC__   /* GCC */
#define PPCASM             __asm__
#define MFSPR( rn )        ({unsigned int rval; PPCASM volatile("mfspr %0," stringify(rn) : "=r" (rval)); rval;})
#define MTSPR(rn, v)       PPCASM volatile("mtspr " stringify(rn) ",%0" : : "r" (v))
#endif

#ifdef __ghs__    /* GreenHills */
#include <ppc_ghs.h>    /* for intrinsic functions only */
#define PPCASM   asm
#define MFSPR( spr )       __MFSPR( spr )
#define MTSPR( spr, val )  __MTSPR( spr, val )
#endif

#ifdef __DCC__
#include <diab/ppcasm.h>    /* for intrinsic functions only */
#define PPCASM   asm
#define MFSPR( spr )       __mfspr( spr )
#define MTSPR( spr, val )  __mtspr( spr, val )
#endif

#define VEC_ALIGN          PPCASM (" .align 4 ")

#endif

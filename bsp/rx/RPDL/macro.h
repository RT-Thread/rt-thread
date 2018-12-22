/********************************************************************************/
/* RX FAMILY C/C++ Compiler                                                     */
/* Copyright (C) 2007 Renesas Technology Corp. and Renesas Solutions Corp.      */
/* All Rights Reserved.                                                         */
/********************************************************************************/

#ifndef _MACRO
#define _MACRO

#ifdef __RX

#ifndef _NO_MT
#define _NO_MT
#endif /* !_NO_MT */

#ifdef __STDC_VERSION__
#if 199901L <= __STDC_VERSION__
#define _C99
#endif /* 199901L <= __STDC_VERSION__ */
#endif /* __STDC_VERSION__ */

#ifndef _HAS_TR1
#define _HAS_TR1 0
#endif /* !_HAS_TR1 */

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 0
#endif /* !__STDC_WANT_LIB_EXT1 */

#ifndef _ADDED_C_LIB
#define _ADDED_C_LIB 0
#endif /* !_ADDED_C_LIB */

#ifndef __STDC_WANT_SAFER_LIB__
#define __STDC_WANT_SAFER_LIB__ 0
#endif /* !__STDC_WANT_SAFER_LIB__ */

#ifndef _ALT_NS
#define _ALT_NS 0
#endif /* !_ALT_NS */

#ifdef __cplusplus

#ifndef _C99
#define _C99
#endif /* !_C99*/ 

#endif /* __cplusplus */

#ifdef __embedded_cplusplus

#ifndef _NO_NS
#define _NO_NS
#endif /* !_NO_NS */

#ifndef _ECPP
#define _ECPP
#endif /* !_ECPP */

#endif /* __embedded_cplusplus */

#ifdef _REENTRANT

#ifndef _R_REENT
#define _R_REENT
#endif /* !_R_REENT */

#endif /* _REENTRANT */

#endif /* __RX */

#endif /* _MACRO */

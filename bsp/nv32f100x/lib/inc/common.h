/******************************************************************************
*
* @brief provide header files to be included by all project files. 
*
*******************************************************************************/


#ifndef _COMMON_H_
#define _COMMON_H_

#define swap_bytes(ptrWord)   *ptrWord = (*ptrWord >>8) | (*ptrWord<<8)
typedef unsigned long   dword;
typedef unsigned short  word;

/********************************************************************/

/*
 * Debug prints ON (#define) or OFF (#undef)
 */

#define DEBUG
#define DEBUG_PRINT

/* 
 * Include the generic CPU header file 
 */
#include "arm_cm0.h"

/* 
 * Include the platform specific header file 
 */
#if (defined(NV32))
 #include  "NV32_config.h"
#elif (defined(FRDM_NV32M3))
 #include  "NV32M3_config.h"
#elif (defined(FRDM_NV32M4))
 #include  "NV32M4_config.h"
#else
  #error "No valid board defined"
#endif

/* 
 * Include the cpu specific header file 
*/
#if (defined(CPU_NV32))
 #include "NV32.h"
#elif (defined(CPU_NV32M3))
 #include "NV32M3.h"
#elif (defined(CPU_NV32M4))
 #include "NV32M4.h"
#else
  #error "No valid CPU defined"
#endif


/* 
 * Include any toolchain specfic header files 
 */
#if (defined(__MWERKS__))
  #include "mwerks.h"
#elif (defined(__DCC__))
  #include "build/wrs/diab.h"
#elif (defined(__ghs__))
  #include "build/ghs/ghs.h"
#elif (defined(__GNUC__))
  #if (defined(IAR))
    #include "build/gnu/gnu.h"
  #endif
#elif (defined(IAR))
  #include "iar.h"
#elif (defined(KEIL))
  
#else
#warning "No toolchain specific header included"
#endif

/* 
 * Include common utilities
 */

#define ASSERT(x)

#if (defined(IAR))
#include "intrinsics.h"
#endif
/********************************************************************/

#endif /* _COMMON_H_ */

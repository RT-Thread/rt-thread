/*******************************************************************************
 * (c) Copyright 2009-2013 Microsemi SoC Products Group. All rights reserved.
 * 
 * Assertion implementation.
 *
 * This file provides the implementation of the ASSERT macro. This file can be
 * modified to cater for project specific requirements regarding the way
 * assertions are handled.
 *
 * SVN $Revision: 6422 $
 * SVN $Date: 2014-05-14 14:37:56 +0100 (Wed, 14 May 2014) $
 */
#ifndef __MSS_ASSERT_H_
#define __MSS_ASSERT_H_

#if defined(NDEBUG)

#define ASSERT(CHECK)

#else   /* NDEBUG */

#include <assert.h>

#if defined ( __GNUC__   )

/*
 * SoftConsole assertion handling
 */
#define ASSERT(CHECK)  \
    do { \
        if (!(CHECK)) \
        { \
            __asm volatile ("BKPT\n\t"); \
        } \
    } while (0);
    
#elif defined ( __ICCARM__ )
/*
 * IAR Embedded Workbench assertion handling.
 * Call C library assert function which should result in error message
 * displayed in debugger.
 */
#define ASSERT(X)   assert(X)

#else
/*
 * Keil assertion handling.
 * Call C library assert function which should result in error message
 * displayed in debugger.
 */

#ifndef __MICROLIB
  #define ASSERT(X)   assert(X)
#else
  #define ASSERT(X)
#endif

#endif  /* Tool Chain */

#endif  /* NDEBUG */

#endif  /* __MSS_ASSERT_H_ */

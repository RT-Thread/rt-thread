/***************************************************************************//**
 * @file
 * @brief EFM32 peripheral API "assert" implementation.
 * @author Energy Micro AS
 * @version 3.0.0
 *
 * @details
 * By default, EFM32 library assert usage is not included in order to reduce
 * footprint and processing overhead. Further, EFM32 assert usage is decoupled
 * from ISO C assert handling (NDEBUG usage), to allow a user to use ISO C
 * assert without including EFM32 assert statements.
 *
 * Below are available defines for controlling EFM32 assert inclusion. The defines
 * are typically defined for a project to be used by the preprocessor.
 *
 * @li If DEBUG_EFM is defined, the internal EFM32 library assert handling will
 * be used, which may be a quite rudimentary implementation.
 *
 * @li If DEBUG_EFM_USER is defined instead, the user must provide its own EFM32
 * assert handling routine (assertEFM()).
 *
 * As indicated above, if none of the above defines are used, EFM32 assert
 * statements are not compiled.
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __EM_ASSERT_H
#define __EM_ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#if defined(DEBUG_EFM) || defined(DEBUG_EFM_USER)

/* Due to footprint considerations, we only pass file name and line number, */
/* not the assert expression (nor function name (C99)) */
void assertEFM(const char *file, int line);
#define EFM_ASSERT(expr)    ((expr) ? ((void)0) : assertEFM(__FILE__, __LINE__))

#else

#define EFM_ASSERT(expr)    ((void)0)

#endif /* defined(DEBUG_EFM) || defined(DEBUG_EFM_USER) */

/** @endcond */

#ifdef __cplusplus
}
#endif

#endif /* __EM_ASSERT_H */

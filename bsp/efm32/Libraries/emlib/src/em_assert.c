/***************************************************************************//**
 * @file
 * @brief Assert API
 * @author Energy Micro AS
 * @version 3.0.0
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
#include "em_assert.h"

#if defined(DEBUG_EFM)

/***************************************************************************//**
 * @brief
 *   EFM internal assert handling.
 *
 *   This function is invoked through EFM_ASSERT() macro usage only, it should
 *   not be used explicitly.
 *
 *   Currently this implementation only enters an indefinite loop, allowing
 *   the use of a debugger to determine cause of failure. By defining
 *   DEBUG_EFM_USER to the preprocessor for all files, a user defined version
 *   of this function must be defined and will be invoked instead, possibly
 *   providing output of assertion location.
 *
 *   Please notice that this function is not used unless DEBUG_EFM is defined
 *   during preprocessing of EFM_ASSERT() usage.
 *
 * @par file
 *   Name of source file where assertion failed.
 *
 * @par line
 *   Line number in source file where assertion failed.
 ******************************************************************************/
void assertEFM(const char *file, int line)
{
  (void)file;  /* Unused parameter */
  (void)line;  /* Unused parameter */

  while (1)
    ;
}

#endif /* DEBUG_EFM */

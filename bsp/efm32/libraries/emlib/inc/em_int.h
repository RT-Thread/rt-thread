/***************************************************************************//**
 * @file
 * @brief Interrupt enable/disable unit API
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
#ifndef __EM_INT_H
#define __EM_INT_H

#include "em_part.h"

extern uint32_t INT_LockCnt;

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup INT
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Disable interrupts.
 *
 * @return
 *   The resulting interrupt nesting level.
 *
 * @details
 *   Disable interrupts and increment lock level counter.
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t INT_Disable(void)
{
  __disable_irq();
  if (INT_LockCnt < UINT32_MAX)
  {
    INT_LockCnt++;
  }

  return INT_LockCnt;
}

/***************************************************************************//**
 * @brief
 *   Enable interrupts.
 *
 * @return
 *   The resulting interrupt nesting level.
 *
 * @details
 *   Decrement interrupt lock level counter and enable interrupts if counter
 *   reached zero.
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t INT_Enable(void)
{
  uint32_t retVal;

  if (INT_LockCnt > 0)
  {
    INT_LockCnt--;
    retVal = INT_LockCnt;
    if (retVal == 0)
    {
      __enable_irq();
    }
    return retVal;
  }
  else
  {
    return 0;
  }
}

/** @} (end addtogroup INT) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_INT_H */

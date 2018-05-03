/**************************************************************************//**
 * @file
 * @brief Interrupt enable/disable unit API
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
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
 *****************************************************************************/
#include <stdint.h>
#include "em_int.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup INT
 * @brief Safe nesting interrupt disable/enable API
 * @details
 *  This module contains functions to safely disable and enable interrupts
 *  at cpu level. INT_Disable() disables interrupts and increments a lock
 *  level counter. INT_Enable() decrements the lock level counter and enable
 *  interrupts if the counter was decremented to zero.
 *
 *  These functions would normally be used to secure critical regions.
 *
 *  These functions should also be used inside interrupt handlers:
 *  @verbatim
 *  void SysTick_Handler(void)
 *  {
 *    INT_Disable();
 *      .
 *      .
 *      .
 *    INT_Enable();
 *  }
 * @endverbatim
 ******************************************************************************/

/** Interrupt lock level counter. Set to zero initially as we normally enter
 * main with interrupts enabled  */
uint32_t INT_LockCnt = 0;


/** @} (end addtogroup INT) */
/** @} (end addtogroup EM_Library) */

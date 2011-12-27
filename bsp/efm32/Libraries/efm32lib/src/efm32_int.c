/**************************************************************************//**
 * @file
 * @brief Interrupt enable/disable unit API for EFM32.
 * @author Energy Micro AS
 * @version 2.3.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2011 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
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
#include "efm32_int.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup INT
 * @brief Safe nesting interrupt disable/enable API for EFM32.
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
/** @} (end addtogroup EFM32_Library) */

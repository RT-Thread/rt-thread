/**************************************************************************//**
 * @file
 * @brief SWO Trace API (for eAProfiler)
 * @author Energy Micro AS
 * @version 2.0.1
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
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
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
#ifndef __TRACE_H
#define __TRACE_H

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "em_msc.h"

#ifdef __cplusplus
extern "C" {
#endif

void TRACE_SWOSetup(void);
bool TRACE_ProfilerSetup(void);

#define USER_PAGE 0x0FE00000UL

/**************************************************************************//**
 * @brief Set or clear word in user page which enables or disables SWO
 *        in TRACE_ProfilerSetup. If TRACE_ProfilerEnable(false) has been run,
 *        no example project will enable SWO trace.
 * @param[in] enable
 * @note Add "em_msc.c" to build to use this function.
 *****************************************************************************/
__STATIC_INLINE void TRACE_ProfilerEnable(bool enable)
{
  uint32_t data;
  volatile uint32_t *userpage = (uint32_t *) USER_PAGE;

  /* Check that configuration needs to change */
  data = *userpage;
  if(enable)
  {
    if(data == 0xFFFFFFFF)
    {
      return;
    }
  }
  else
  {
    if(data == 0x00000000)
    {
      return;
    }
  }

  /* Initialize MSC */
  MSC_Init();

  /* Write enble or disable trigger word into flash */
  if(enable)
  {
    data = 0xFFFFFFFF;
    MSC_ErasePage((uint32_t *)USER_PAGE);
    MSC_WriteWord((uint32_t *)USER_PAGE, (void *) &data, 4);
  }
  else
  {
    data = 0x00000000;
    MSC_ErasePage((uint32_t *)USER_PAGE);
    MSC_WriteWord((uint32_t *)USER_PAGE, (void *) &data, 4);
  }
}

#ifdef __cplusplus
}
#endif

/** @} (end group BSP) */

#endif

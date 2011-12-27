/***************************************************************************//**
 * @file
 * @brief Debug (DBG) Peripheral API for EFM32
 * @author Energy Micro AS
 * @version 2.3.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
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
 ******************************************************************************/

#include "efm32_assert.h"
#include "efm32_dbg.h"
#include "efm32_cmu.h"
#include "efm32_gpio.h"

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup DBG
 * @brief Debug (DBG) Peripheral API for EFM32
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enable Serial Wire Output (SWO) pin.
 *
 * @details
 *   The SWO pin (sometimes denoted SWV, serial wire viewer) allows for
 *   miscellaneous output to be passed from the Cortex-M3 debug trace module to
 *   an external debug probe. By default, the debug trace module and pin output
 *   may be disabled.
 *
 *   Since the SWO pin is only useful when using a debugger, a suggested use
 *   of this function during startup may be:
 * @verbatim
 * if (DBG_Connected())
 * {
 * DBG_SWOEnable(1);
 * }
 * @endverbatim
 *   By checking if debugger is attached, some setup leading to higher energy
 *   consumption when debugger is attached, can be avoided when not using
 *   a debugger.
 *
 *   Another alternative may be to set the debugger tool chain to configure
 *   the required setup (similar to the content of this function) by some
 *   sort of toolchain scripting during its attach/reset procedure. In that
 *   case, the above suggested code for enabling the SWO pin is not required
 *   in the application.
 *
 * @param[in] location
 *   Pin location used for SWO pin on the application in use.
 ******************************************************************************/
void DBG_SWOEnable(unsigned int location)
{
  int port;
  int pin;

  EFM_ASSERT(location < AFCHANLOC_MAX);

  port = AF_DBG_SWO_PORT(location);
  pin  = AF_DBG_SWO_PIN(location);

  /* Port/pin location not defined for device? */
  if ((pin < 0) || (port < 0))
  {
    EFM_ASSERT(0);
    return;
  }

  /* Ensure auxiliary clock going to the Cortex debug trace module is enabled */
  CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, false);

  /* Set selected pin location for SWO pin and enable it */
  GPIO_DbgLocationSet(location);
  GPIO_DbgSWOEnable(true);

  /* Configure SWO pin for output */
  GPIO_PinModeSet((GPIO_Port_TypeDef)port, pin, gpioModePushPull, 0);
}

/** @} (end addtogroup DBG) */
/** @} (end addtogroup EFM32_Library) */

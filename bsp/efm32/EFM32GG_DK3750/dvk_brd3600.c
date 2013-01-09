/**************************************************************************//**
 * @file
 * @brief EFM32GG_DK3750 board support package BRD3600A API implementation
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

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

#include "efm32.h"
#include "em_gpio.h"
#include "em_ebi.h"
#include "em_cmu.h"
#include "dvk.h"
#include "dvk_bcregisters.h"

/**************************************************************************//**
 * @brief Configure BRD3600A on-board peripherals.
 *****************************************************************************/
void DVK_BRD3600A_init(void)
{
  /* Enable CMU GPIO clocks */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* USB status LED - configure PE1 as push pull */
  GPIO_PinModeSet(gpioPortE, 1, gpioModePushPull, 0);

  /* USB overcurrent status - configure PE2 as push pull */
  GPIO_PinModeSet(gpioPortE, 2, gpioModeInput, 0);

  /* USB VBUS switch - configure PF5 as push pull - Default OFF */
  GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, 0);

  return;
}


/**************************************************************************//**
 * @brief Disable EFM32GG_DK3750 EBI board support package functionality
 *****************************************************************************/
void DVK_BRD3600A_deInit(void)
{
  /* Disable PE1 */
  GPIO_PinModeSet(gpioPortE, 1, gpioModePushPull, 0);

  /* Disable CMU GPIO clocks */
  CMU_ClockEnable(cmuClock_GPIO, false);


  return;
}

/**************************************************************************//**
 * @brief Set state of USB status LED
 * @param[in] enable Set to true to light LED, false to dim it
 *****************************************************************************/
void DVK_BRD3600A_usbStatusLEDEnable(int enable)
{
  GPIO_PinModeSet(gpioPortE, 1, gpioModePushPull, enable);

  return;
}

/**************************************************************************//**
 * @brief Enable VBUS switch
 * @param[in] enable Set to true to enable switch
 *****************************************************************************/
void DVK_BRD3600A_usbVBUSSwitchEnable(int enable)
{
  GPIO_PinModeSet(gpioPortF, 5, gpioModePushPull, enable);

  return;
}

/**************************************************************************//**
 * @brief Get state of VBUS switch overcurrent flag
 *****************************************************************************/
int DVK_BRD3600A_usbVBUSGetOCFlagState(void)
{
  return ~GPIO_PinInGet(gpioPortE, 2);
}

/** @} (end group BSP) */

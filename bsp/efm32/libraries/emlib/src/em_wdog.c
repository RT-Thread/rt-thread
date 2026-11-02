/***************************************************************************//**
 * @file
 * @brief Watchdog (WDOG) peripheral API
 *   devices.
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
#include "em_wdog.h"
#include "em_bitband.h"

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup WDOG
 * @brief Watchdog (WDOG) Peripheral API
 * @{
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Enable/disable the watchdog timer.
 *
 * @note
 *   This function modifies the WDOG CTRL register which requires
 *   synchronization into the low frequency domain. If this register is modified
 *   before a previous update to the same register has completed, this function
 *   will stall until the previous synchronization has completed.
 *
 * @param[in] enable
 *   true to enable watchdog, false to disable. Watchdog cannot be disabled if
 *   watchdog has been locked.
 ******************************************************************************/
void WDOG_Enable(bool enable)
{
  if (!enable)
  {
    /* Wait for any pending previous write operation to have been completed in */
    /* low frequency domain */
    while (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CTRL)
      ;
  }
  BITBAND_Peripheral(&(WDOG->CTRL), _WDOG_CTRL_EN_SHIFT, (unsigned int)enable);
}


/***************************************************************************//**
 * @brief
 *   Feed the watchdog.
 *
 * @details
 *   When the watchdog is activated, it must be fed (ie clearing the counter)
 *   before it reaches the defined timeout period. Otherwise, the watchdog
 *   will generate a reset.
 ******************************************************************************/
void WDOG_Feed(void)
{
  /* If a previous clearing is being synchronized to LF domain, then there */
  /* is no point in waiting for it to complete before clearing over again. */
  /* This avoids stalling the core in the typical use case where some idle loop */
  /* keeps clearing the watchdog. */
  if (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CMD)
    return;

  WDOG->CMD = WDOG_CMD_CLEAR;
}


/***************************************************************************//**
 * @brief
 *   Initialize watchdog (assuming the watchdog configuration has not been
 *   locked).
 *
 * @note
 *   This function modifies the WDOG CTRL register which requires
 *   synchronization into the low frequency domain. If this register is modified
 *   before a previous update to the same register has completed, this function
 *   will stall until the previous synchronization has completed.
 *
 * @param[in] init
 *   Structure holding watchdog configuration. A default setting
 *   #WDOG_INIT_DEFAULT is available for init.
 ******************************************************************************/
void WDOG_Init(const WDOG_Init_TypeDef *init)
{
  uint32_t setting;

  if (init->enable)
  {
    setting = WDOG_CTRL_EN;
  }
  else
  {
    setting = 0;
  }

  if (init->debugRun)
  {
    setting |= WDOG_CTRL_DEBUGRUN;
  }

  if (init->em2Run)
  {
    setting |= WDOG_CTRL_EM2RUN;
  }

  if (init->em3Run)
  {
    setting |= WDOG_CTRL_EM3RUN;
  }

  if (init->em4Block)
  {
    setting |= WDOG_CTRL_EM4BLOCK;
  }

  if (init->swoscBlock)
  {
    setting |= WDOG_CTRL_SWOSCBLOCK;
  }

  setting |= ((uint32_t)(init->clkSel) << _WDOG_CTRL_CLKSEL_SHIFT) |
             ((uint32_t)(init->perSel) << _WDOG_CTRL_PERSEL_SHIFT);

  /* Wait for any pending previous write operation to have been completed in */
  /* low frequency domain */
  while (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CTRL)
    ;

  WDOG->CTRL = setting;

  /* Optional register locking */
  if (init->lock)
  {
    if (init->enable)
    {
      WDOG_Lock();
    }
    else
    {
      BITBAND_Peripheral(&(WDOG->CTRL), _WDOG_CTRL_LOCK_SHIFT, 1);
    }
  }
}


/***************************************************************************//**
 * @brief
 *   Lock the watchdog configuration.
 *
 * @details
 *   This prevents errors from overwriting the watchdog configuration, possibly
 *   disabling it. Only a reset can unlock the watchdog config, once locked.
 *
 *   If the LFRCO or LFXO clocks are used to clock the watchdog, one should
 *   consider using the option of inhibiting those clocks to be disabled,
 *   please see the WDOG_Enable() init structure.
 *
 * @note
 *   This function modifies the WDOG CTRL register which requires
 *   synchronization into the low frequency domain. If this register is modified
 *   before a previous update to the same register has completed, this function
 *   will stall until the previous synchronization has completed.
 ******************************************************************************/
void WDOG_Lock(void)
{
  /* Wait for any pending previous write operation to have been completed in */
  /* low frequency domain */
  while (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CTRL)
    ;

  /* Disable writing to the control register */
  BITBAND_Peripheral(&(WDOG->CTRL), _WDOG_CTRL_LOCK_SHIFT, 1);
}


/** @} (end addtogroup WDOG) */
/** @} (end addtogroup EM_Library) */

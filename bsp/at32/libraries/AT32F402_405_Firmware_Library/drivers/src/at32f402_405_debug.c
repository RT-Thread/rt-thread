/**
  **************************************************************************
  * @file     at32f402_405_mcudbg.c
  * @brief    contains all the functions for the mcudbg firmware library
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f402_405_conf.h"

/** @addtogroup AT32F402_405_periph_driver
  * @{
  */

/** @defgroup DEBUG
  * @brief DEBUG driver modules
  * @{
  */

#ifdef DEBUG_MODULE_ENABLED

/** @defgroup DEBUG_private_functions
  * @{
  */

/**
  * @brief  get debug device id
  * @param  none
  * @retval the debug device id
  */
uint32_t debug_device_id_get(void)
{
  return DEBUGMCU->pid;
}
/**
  * @brief  set periph debug mode
  * @param  periph_debug_mode
  *         this parameter can be one of the following values:
  *         - DEBUG_SLEEP
  *         - DEBUG_DEEPSLEEP
  *         - DEBUG_STANDBY
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void debug_low_power_mode_set(uint32_t low_power_mode, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    DEBUGMCU->ctrl |= low_power_mode;
  }
  else
  {
    DEBUGMCU->ctrl &= ~low_power_mode;
  }
}
/**
  * @brief  set apb1 periph debug mode
  * @param  periph_debug_mode
  *         this parameter can be any combination of the following values:
  *         - DEBUG_TMR2_PAUSE                      - DEBUG_TMR3_PAUSE
  *         - DEBUG_TMR4_PAUSE                      - DEBUG_TMR6_PAUSE
  *         - DEBUG_TMR7_PAUSE                      - DEBUG_TMR13_PAUSE
  *         - DEBUG_TMR14_PAUSE                     - DEBUG_ERTC_PAUSE
  *         - DEBUG_WWDT_PAUSE                      - DEBUG_WDT_PAUSE
  *         - DEBUG_ERTC_512_PAUSE                  - DEBUG_I2C1_SMBUS_TIMEOUT
  *         - DEBUG_I2C2_SMBUS_TIMEOUT              - DEBUG_I2C3_SMBUS_TIMEOUT
  *         - DEBUG_CAN1_PAUSE
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void debug_apb1_periph_mode_set(uint32_t apb1_periph, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    DEBUGMCU->apb1_frz |= apb1_periph;
  }
  else
  {
    DEBUGMCU->apb1_frz &= ~apb1_periph;
  }
}
/**
  * @brief  set apb2 periph debug mode
  * @param  periph_debug_mode
  *         this parameter can be any combination of the following values:
  *         - DEBUG_TMR1_PAUSE                      - DEBUG_TMR9_PAUSE
  *         - DEBUG_TMR10_PAUSE                     - DEBUG_TMR11_PAUSE
  * @param  new_state (TRUE or FALSE)
  * @retval none
  */
void debug_apb2_periph_mode_set(uint32_t apb2_periph, confirm_state new_state)
{
  if(new_state != FALSE)
  {
    DEBUGMCU->apb2_frz |= apb2_periph;
  }
  else
  {
    DEBUGMCU->apb2_frz &= ~apb2_periph;
  }
}

/**
  * @}
  */

#endif

/**
  * @}
  */

/**
  * @}
  */

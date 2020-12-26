/**
  ******************************************************************************
  * @brief   MCUDBG functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_mcudbg.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup MCUDBG
  * @brief MCUDBG driver modules
  * @{
  */


/** @defgroup MCUDBG_Private_Defines
  * @{
  */

#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)
/**
  * @}
  */


/** @defgroup MCUDBG_Private_Functions
  * @{
  */

/**
  * @brief  Returns the device revision identifier.
  * @param  None
  * @retval Device revision identifier
  */
uint32_t MCUDBG_GetREVID(void)
{
    return (MCUDBG->IDR >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t MCUDBG_GetDEVID(void)
{
    return (MCUDBG->IDR & IDCODE_DEVID_MASK);
}

/**
  * @brief  Configure the specified peripheral and low power mode behavior
  *   when the MCU under Debug mode.
  * @param  MCUDBG_Periph: specifies the peripheral and low power mode.
  *   This parameter can be any combination of the following values:
  *     @arg MCUDBG_SLEEP_HOLD:     Keep debugger connection during SLEEP mode
  *     @arg MCUDBG_DEEPSLEEP_HOLD: Keep debugger connection during DEEPSLEEP mode
  *     @arg MCUDBG_STDBY_HOLD:     Keep debugger connection during STANDBY mode
  *     @arg MCUDBG_IWDG_HOLD:      Debug IWDG hold when Core is halted
  *     @arg MCUDBG_WWDG_HOLD:      Debug WWDG hold when Core is halted
  *     @arg MCUDBG_TIMER1_HOLD:    TIMER1 counter hold when Core is halted
  *     @arg MCUDBG_TIMER2_HOLD:    TIMER2 counter hold when Core is halted
  *     @arg MCUDBG_TIMER3_HOLD:    TIMER3 counter hold when Core is halted
  *     @arg MCUDBG_TIMER4_HOLD:    TIMER4 counter hold when Core is halted
  *     @arg MCUDBG_CAN1_HOLD:      Debug CAN1 hold when Core is halted
  *     @arg MCUDBG_I2C1_HOLD:      I2C1 SMBUS timeout mode hold when Core is halted
  *     @arg MCUDBG_I2C2_HOLD:      I2C2 SMBUS timeout mode hold when Core is halted
  *     @arg MCUDBG_TIMER5_HOLD:    TIMER5 counter hold when Core is halted
  *     @arg MCUDBG_TIMER6_HOLD:    TIMER6 counter hold when Core is halted
  *     @arg MCUDBG_TIMER7_HOLD:    TIMER7 counter hold when Core is halted
  *     @arg MCUDBG_TIMER8_HOLD:    TIMER8 counter hold when Core is halted
  *     @arg MCUDBG_CAN2_HOLD:      Debug CAN2 hold when Core is halted
  *     @arg MCUDBG_TIMER12_HOLD:   TIMER12 counter hold when Core is halted
  *     @arg MCUDBG_TIMER13_HOLD:   TIMER13 counter hold when Core is halted
  *     @arg MCUDBG_TIMER14_HOLD:   TIMER14 counter hold when Core is halted
  *     @arg MCUDBG_TIMER9_HOLD:    TIMER9 counter hold when Core is halted
  *     @arg MCUDBG_TIMER10_HOLD:   TIMER10 counter hold when Core is halted
  *     @arg MCUDBG_TIMER11_HOLD:   TIMER11 counter hold when Core is halted
  * @param  NewState: new state of the specified peripheral in Debug mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCUDBG_PeriphConfig(uint32_t MCUDBG_Periph, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        MCUDBG->CTLR |= MCUDBG_Periph;
    } else {
        MCUDBG->CTLR &= ~MCUDBG_Periph;
    }
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


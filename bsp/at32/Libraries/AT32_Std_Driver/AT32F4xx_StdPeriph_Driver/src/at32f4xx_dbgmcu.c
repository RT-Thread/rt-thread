/**
 **************************************************************************
 * File Name    : at32f4xx_dbgmcu.c
 * Description  : at32f4xx MCUDBG source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_dbgmcu.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup DBGMCU
  * @brief DBGMCU driver modules
  * @{
  */

/** @defgroup DBGMCU_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Private_Defines
  * @{
  */

#define IDCODE_DEVID_MASK           ((uint32_t)0x00000FFF)
/**
  * @}
  */

/** @defgroup DBGMCU_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup DBGMCU_Private_Functions
  * @{
  */

/**
  * @brief  Returns the device revision identifier.
  * @param  None
  * @retval Device revision identifier
  */
uint32_t MCUDBG_GetRevID(void)
{
  return(DBGMCU->IDCR >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t MCUDBG_GetDevID(void)
{
  return(DBGMCU->IDCR & IDCODE_DEVID_MASK);
}

/**
  * @brief  Configures the specified peripheral and low power mode behavior
  *   when the MCU under Debug mode.
  * @param  DBGMCU_Periph: specifies the peripheral and low power mode.
  *   This parameter can be any combination of the following values:
  *     @arg MCUDBG_SLEEP: Keep debugger connection during SLEEP mode
  *     @arg MCUDBG_STOP: Keep debugger connection during STOP mode
  *     @arg MCUDBG_STANDBY: Keep debugger connection during STANDBY mode
  *     @arg MCUDBG_IWDG_STOP: Debug IWDG stopped when Core is halted
  *     @arg MCUDBG_WWDG_STOP: Debug WWDG stopped when Core is halted
  *     @arg MCUDBG_TMR1_STOP: TMR1 counter stopped when Core is halted
  *     @arg MCUDBG_TMR2_STOP: TMR2 counter stopped when Core is halted
  *     @arg MCUDBG_TMR3_STOP: TMR3 counter stopped when Core is halted
  *     @arg MCUDBG_TMR4_STOP: TMR4 counter stopped when Core is halted
  *     @arg MCUDBG_CAN1_STOP: Debug CAN1 stopped when Core is halted
  *     @arg MCUDBG_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped when Core is halted
  *     @arg MCUDBG_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped when Core is halted
  *     @arg MCUDBG_I2C3_SMBUS_TIMEOUT: I2C3 SMBUS timeout mode stopped when Core is halted
  *     @arg MCUDBG_TMR5_STOP: TMR5 counter stopped when Core is halted
  *     @arg MCUDBG_TMR6_STOP: TMR6 counter stopped when Core is halted
  *     @arg MCUDBG_TMR7_STOP: TMR7 counter stopped when Core is halted
  *     @arg MCUDBG_TMR8_STOP: TMR8 counter stopped when Core is halted
  *     @arg MCUDBG_TMR15_STOP: TMR15 counter stopped when Core is halted
  *     @arg MCUDBG_TMR9_STOP: TMR9 counter stopped when Core is halted
  *     @arg MCUDBG_TMR10_STOP: TMR10 counter stopped when Core is halted
  *     @arg MCUDBG_TMR11_STOP: TMR11 counter stopped when Core is halted
  *     @arg MCUDBG_TMR12_STOP: TMR12 counter stopped when Core is halted
  *     @arg MCUDBG_TMR13_STOP: TMR13 counter stopped when Core is halted
  *     @arg MCUDBG_TMR14_STOP: TMR14 counter stopped when Core is halted
  * @param  NewState: new state of the specified peripheral in Debug mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void MCUDBG_PeriphDebugModeConfig(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_MCUDBG_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CTRL |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CTRL &= ~DBGMCU_Periph;
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



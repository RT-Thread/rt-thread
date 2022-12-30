/* Includes ------------------------------------------------------------------*/
#include "air32f10x_dbgmcu.h"


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

#define IDCODE_DEVID_MASK    ((uint32_t)0x00000FFF)
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
uint32_t DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/**
  * @brief  Returns the device identifier.
  * @param  None
  * @retval Device identifier
  */
uint32_t DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_MASK);
}

/**
  * @brief  Configures the specified peripheral and low power mode behavior
  *   when the MCU under Debug mode.
  * @param  DBGMCU_Periph: specifies the peripheral and low power mode.
  *   This parameter can be any combination of the following values:
  *     @arg DBGMCU_SLEEP: Keep debugger connection during SLEEP mode
  *     @arg DBGMCU_STOP: Keep debugger connection during STOP mode
  *     @arg DBGMCU_STANDBY: Keep debugger connection during STANDBY mode
  *     @arg DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted
  *     @arg DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted
  *     @arg DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted
  *     @arg DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted
  *     @arg DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted
  *     @arg DBGMCU_TIM4_STOP: TIM4 counter stopped when Core is halted
  *     @arg DBGMCU_CAN1_STOP: Debug CAN2 stopped when Core is halted
  *     @arg DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped when Core is halted
  *     @arg DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped when Core is halted
  *     @arg DBGMCU_TIM5_STOP: TIM5 counter stopped when Core is halted
  *     @arg DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted
  *     @arg DBGMCU_TIM7_STOP: TIM7 counter stopped when Core is halted
  *     @arg DBGMCU_TIM8_STOP: TIM8 counter stopped when Core is halted
  *     @arg DBGMCU_CAN2_STOP: Debug CAN2 stopped when Core is halted
  *     @arg DBGMCU_TIM15_STOP: TIM15 counter stopped when Core is halted
  *     @arg DBGMCU_TIM16_STOP: TIM16 counter stopped when Core is halted
  *     @arg DBGMCU_TIM17_STOP: TIM17 counter stopped when Core is halted
  *     @arg DBGMCU_TIM9_STOP: TIM9 counter stopped when Core is halted
  *     @arg DBGMCU_TIM10_STOP: TIM10 counter stopped when Core is halted
  *     @arg DBGMCU_TIM11_STOP: TIM11 counter stopped when Core is halted
  *     @arg DBGMCU_TIM12_STOP: TIM12 counter stopped when Core is halted
  *     @arg DBGMCU_TIM13_STOP: TIM13 counter stopped when Core is halted
  *     @arg DBGMCU_TIM14_STOP: TIM14 counter stopped when Core is halted
  * @param  NewState: new state of the specified peripheral in Debug mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
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

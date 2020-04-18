/**
 **************************************************************************
 * File Name    : at32f4xx_acc.c
 * Description  : at32f4xx ACC source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_acc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ACC
  * @brief ACC driver modules
  * @{
  */
#if defined (AT32F413xx) || defined (AT32F415xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)

/** @defgroup ACC_Private_Functions
  * @{
  */
  
/**
  * @brief  Stores Calibration Step data in ACC's CTRL1 register.
  * @param  StepValue:  value to be stored in the ACC's CTRL1 register 					
  * @retval None
  */
void ACC_SetStep(uint8_t StepValue)
{
  ACC->CTRL1 |= StepValue<<8;
}

/**
  * @brief  Enables the specified ACC Calibration.
  * @param  ACC_CAL: specifies the ACC CAL sources.
  *   This parameter can be one of the following values:
  *     @arg ACC_CAL_HSICAL:  Calibration HSICAL
  *     @arg ACC_CAL_HSITRIM:  Calibration HSITRIM
  * @retval None
  */
void ACC_CAL_Choose(uint16_t ACC_CAL)
{
  ACC->CTRL1 &= ~0x2;
  
  ACC->CTRL1 |= ACC_CAL;
  
}

/**
  * @brief  Enables or disables the specified ACC interrupts.
  * @param  ACC_IT: specifies the ACC interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg ACC_IT_CALRDYIEN:  CALRDY interrupt enable
  *     @arg ACC_IT_EIEN:  RSLOST error interrupt enable
  * @param  NewState: new state of the specified ACC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ACC_ITConfig(uint16_t ACC_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    ACC->CTRL1  |= ACC_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    ACC->CTRL1 &= (uint16_t)~ACC_IT;
  }
}

/**
  * @brief  Enters the ACC Calibration mode.
  * @param  ACC_IT: specifies the ACC interrupt sources to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg ACC_CAL_ON:  CALRDY interrupt enable
  *     @arg ACC_TRIM_ON:  RSLOST error interrupt enable
  * @param  NewState: new state of the specified ACC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ACC_EnterCALMode(uint16_t ACC_ON, FunctionalState NewState)
{
  ACC->CTRL1 |= ACC_ON;
}
/**
  * @brief  Exits from the ACC Calibration mode.
  * @param  None
  * @retval None
  */
void ACC_ExitCALMode(void)
{
  ACC->CTRL1 &= ~ACC_CAL_Enable;
}

/**
  * @brief  Checks whether the specified ACC flag is set or not.
  * @param  ACC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ACC_FLAG_RSLOST:  Reference Signal Lost
  *     @arg ACC_FLAG_CALRDY:  Internal high-speed clock calibration ready
  * @retval The new state of ACC_FLAG (SET or RESET).
  */
FlagStatus ACC_GetFlagStatus(uint16_t ACC_FLAG)
{
  FlagStatus bitstatus = RESET;  
  
  if ((ACC->STS & ACC_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Wtire the value to  ACC C1 register.
  * @param  ACC_C1_Value
  * @retval none.
  */
void ACC_WriteC1(uint16_t ACC_C1_Value)
{
  ACC->C1 = ACC_C1_Value;
}

/**
  * @brief  Wtire the value to  ACC C2 register.
  * @param  ACC_C2_Value
  * @retval none.
  */
void ACC_WriteC2(uint16_t ACC_C2_Value)
{
  ACC->C2 = ACC_C2_Value;
}
/**
  * @brief  Wtire the value to  ACC C3 register.
  * @param  ACC_C3_Value
  * @retval none.
  */
void ACC_WriteC3(uint16_t ACC_C3_Value)
{
  ACC->C3 = ACC_C3_Value;
}

/**
  * @brief  Returns the current ACC HSITRIM value.
  * @param  None
  * @retval 8-bit HSITRIM value.
  */
uint8_t ACC_GetHSITRIM(void)
{
  return ((uint8_t)((ACC->CTRL2)>>8));
}


/**
  * @brief  Returns the current ACC HSICAL value.
  * @param  None
  * @retval 8-bit HSITRIM value.
  */
uint8_t ACC_GetHSICAL(void)
{
  return ((uint8_t)(ACC->CTRL2));
}

/**
  * @brief  Returns the current ACC C1 value.
  * @param  None
  * @retval 16-bit C1 value.
  */
uint16_t ACC_ReadC1(void)
{
  return ((uint16_t)(ACC->C1));
}

/**
  * @brief  Returns the current ACC C2 value.
  * @param  None
  * @retval 16-bit C2 value.
  */
uint16_t ACC_ReadC2(void)
{
  return ((uint16_t)(ACC->C2));
}
/**
  * @brief  Returns the current ACC C3 value.
  * @param  None
  * @retval 16-bit C3 value.
  */
uint16_t ACC_ReadC3(void)
{
  return ((uint16_t)(ACC->C3));
}

/**
  * @brief  Checks whether the specified ACC flag is set or not.
  * @param  ACC_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg ACC_FLAG_RSLOST:  Reference Signal Lost
  *     @arg ACC_FLAG_CALRDY:  Internal high-speed clock calibration ready
  * @retval None.
  */
void ACC_ClearFlag(uint16_t ACC_FLAG)            
{
  if(ACC_FLAG == ACC_FLAG_CALRDY)
  {
    ACC->STS &= ~1;
  }
  
  if(ACC_FLAG == ACC_FLAG_RSLOST)
  {
    ACC->STS &= ~2;
  }
}

/**
  * @}
  */

#endif /* AT32F413xx || AT32F415xx || AT32F403Axx || AT32F407xx */

/**
  * @}
  */

/**
  * @}
  */

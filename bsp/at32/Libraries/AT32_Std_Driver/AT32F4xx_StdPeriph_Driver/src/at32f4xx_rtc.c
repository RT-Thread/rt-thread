/**
 **************************************************************************
 * File Name    : at32f4xx_rtc.c
 * Description  : at32f4xx RTC source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_rtc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */

#if defined (AT32F403xx) || defined (AT32F413xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)

/** @defgroup RTC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup RTC_Private_Defines
  * @{
  */
#define RTC_LSB_MASK            ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */
#define DIVH_MSB_MASK           ((uint32_t)0x000F0000)  /*!< RTC Prescaler MSB Mask */

/**
  * @}
  */

/** @defgroup RTC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup RTC_Private_Functions
  * @{
  */

/**
  * @brief  Enables or disables the specified RTC interrupts.
  * @param  RTC_INT: specifies the RTC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_INT_OV: Overflow interrupt
  *     @arg RTC_INT_ALA: Alarm interrupt
  *     @arg RTC_INT_PACE: Second interrupt
  * @param  NewState: new state of the specified RTC interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_INTConfig(uint16_t RTC_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_INT(RTC_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RTC->CTRLH |= RTC_INT;
  }
  else
  {
    RTC->CTRLH &= (uint16_t)~RTC_INT;
  }
}

/**
  * @brief  Enters the RTC configuration mode.
  * @param  None
  * @retval None
  */
void RTC_EnterConfigMode(void)
{
  /* Set the CNF flag to enter in the Configuration Mode */
  RTC->CTRLL |= RTC_CTRLL_CMF;
}

/**
  * @brief  Exits from the RTC configuration mode.
  * @param  None
  * @retval None
  */
void RTC_ExitConfigMode(void)
{
  /* Reset the CNF flag to exit from the Configuration Mode */
  RTC->CTRLL &= (uint16_t)~((uint16_t)RTC_CTRLL_CMF);
}

/**
  * @brief  Gets the RTC counter value.
  * @param  None
  * @retval RTC counter value.
  */
uint32_t RTC_GetCounter(void)
{
  uint16_t tmp = 0;
  tmp = RTC->CNTL;
  return (((uint32_t)RTC->CNTH << 16 ) | tmp) ;
}

/**
  * @brief  Sets the RTC counter value.
  * @param  CounterValue: RTC counter new value.
  * @retval None
  */
void RTC_SetCounter(uint32_t CounterValue)
{
  RTC_EnterConfigMode();
  /* Set RTC COUNTER MSB word */
  RTC->CNTH = CounterValue >> 16;
  /* Set RTC COUNTER LSB word */
  RTC->CNTL = (CounterValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
  * @brief  Sets the RTC prescaler value.
  * @param  PrescalerValue: RTC prescaler new value.
  * @retval None
  */
void RTC_SetDIV(uint32_t PrescalerValue)
{
  /* Check the parameters */
  assert_param(IS_RTC_DIV(PrescalerValue));

  RTC_EnterConfigMode();
  /* Set RTC PRESCALER MSB word */
  RTC->DIVH = (PrescalerValue & DIVH_MSB_MASK) >> 16;
  /* Set RTC PRESCALER LSB word */
  RTC->DIVL = (PrescalerValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
  * @brief  Sets the RTC alarm value.
  * @param  AlarmValue: RTC alarm new value.
  * @retval None
  */
void RTC_SetAlarmValue(uint32_t AlarmValue)
{
  RTC_EnterConfigMode();
  /* Set the ALARM MSB word */
  RTC->ALAH = AlarmValue >> 16;
  /* Set the ALARM LSB word */
  RTC->ALAL = (AlarmValue & RTC_LSB_MASK);
  RTC_ExitConfigMode();
}

/**
  * @brief  Gets the RTC divider value.
  * @param  None
  * @retval RTC Divider value.
  */
uint32_t RTC_GetDivider(void)
{
  uint32_t tmp = 0x00;
  tmp = ((uint32_t)RTC->DIVCNTH & (uint32_t)0x000F) << 16;
  tmp |= RTC->DIVCNTL;
  return tmp;
}

/**
  * @brief  Waits until last write operation on RTC registers has finished.
  * @note   This function must be called before any write to RTC registers.
  * @param  None
  * @retval None
  */
void RTC_WaitForLastTask(void)
{
  /* Loop until RTOFF flag is set */
  while ((RTC->CTRLL & RTC_FLAG_RTF) == (uint16_t)RESET)
  {
  }
}

/**
  * @brief  Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
  *   are synchronized with RTC APB clock.
  * @note   This function must be called before any read operation after an APB reset
  *   or an APB clock stop.
  * @param  None
  * @retval None
  */
void RTC_WaitForSynchro(void)
{
  /* Clear RSF flag */
  RTC->CTRLL &= (uint16_t)~RTC_FLAG_RSYNF;

  /* Loop until RSF flag is set */
  while ((RTC->CTRLL & RTC_FLAG_RSYNF) == (uint16_t)RESET)
  {
  }
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *   This parameter can be one the following values:
  *     @arg RTC_FLAG_RTF: RTC Operation OFF flag
  *     @arg RTC_FLAG_RSYNF: Registers Synchronized flag
  *     @arg RTC_FLAG_OV: Overflow flag
  *     @arg RTC_FLAG_ALA: Alarm flag
  *     @arg RTC_FLAG_PACE: Second flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(uint16_t RTC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

  if ((RTC->CTRLL & RTC_FLAG) != (uint16_t)RESET)
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
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_FLAG_RSYNF: Registers Synchronized flag. This flag is cleared only after
  *                        an APB reset or an APB Clock stop.
  *     @arg RTC_FLAG_OV: Overflow flag
  *     @arg RTC_FLAG_ALA: Alarm flag
  *     @arg RTC_FLAG_PACE: Second flag
  * @retval None
  */
void RTC_ClearFlag(uint16_t RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

  /* Clear the corresponding RTC flag */
  RTC->CTRLL &= (uint16_t)~RTC_FLAG;
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_INT: specifies the RTC interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg RTC_INT_OV: Overflow interrupt
  *     @arg RTC_INT_ALA: Alarm interrupt
  *     @arg RTC_INT_PACE: Second interrupt
  * @retval The new state of the RTC_INT (SET or RESET).
  */
ITStatus RTC_GetINTStatus(uint16_t RTC_INT)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_RTC_GET_INT(RTC_INT));

  bitstatus = (ITStatus)(RTC->CTRLL & RTC_INT);

  if (((RTC->CTRLH & RTC_INT) != (uint16_t)RESET) && (bitstatus != (uint16_t)RESET))
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
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_INT_OV: Overflow interrupt
  *     @arg RTC_INT_ALA: Alarm interrupt
  *     @arg RTC_INT_PACE: Second interrupt
  * @retval None
  */
void RTC_ClearINTPendingBit(uint16_t RTC_INT)
{
  /* Check the parameters */
  assert_param(IS_RTC_INT(RTC_INT));

  /* Clear the corresponding RTC pending bit */
  RTC->CTRLL &= (uint16_t)~RTC_INT;
}

/**
  * @}
  */

#endif /* AT32F403xx || AT32F413xx || AT32F403Axx || AT32F407xx */

/**
  * @}
  */

/**
  * @}
  */



/**
  ******************************************************************************
  * @file               ft32f0xx_wwdg.c
  * @author             FMD AE
  * @brief              This file provides firmware functions to manage the following
  *                     functionalities of the Window watchdog (WWDG) peripheral:
  *                 + Prescaler, Refresh window and Counter configuration
  *                 + WWDG activation
  *                 + Interrupts and flags management
  * @version            V1.0.0
  * @data                   2021-07-01
    ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_wwdg.h"
#include "ft32f0xx_rcc.h"
/* --------------------- WWDG registers bit mask ---------------------------- */
/* CFR register bit mask */
#define CFR_WDGTB_MASK    ((uint32_t)0xFFFFFE7F)
#define CFR_W_MASK        ((uint32_t)0xFFFFFF80)
#define BIT_MASK          ((uint8_t)0x7F)


/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *          This parameter can be one of the following values:
  *            @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
  *            @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
  *            @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
  *            @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFR & CFR_WDGTB_MASK;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;
  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *          This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear W[6:0] bits */

  tmpreg = WWDG->CFR & CFR_W_MASK;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & (uint32_t) BIT_MASK;

  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
  * @note   Once enabled this interrupt cannot be disabled except by a system reset.
  * @param  None
  * @retval None
  */
void WWDG_EnableIT(void)
{
  WWDG->CFR |= WWDG_CFR_EWI;
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Counter: specifies the watchdog counter value.
  *          This parameter must be a number between 0x40 and 0x7F (to prevent
  *          generating an immediate reset).
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = Counter & BIT_MASK;
}

/**
  * @}
  */

/**
  * @brief  Enables WWDG and load the counter value.
  * @param  Counter: specifies the watchdog counter value.
  *          This parameter must be a number between 0x40 and 0x7F (to prevent
  *          generating an immediate reset).
  * @retval None
  */
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = WWDG_CR_WDGA | Counter;
}

/**
  * @}
  */

/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  None
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET).
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((WWDG->SR) != (uint32_t)RESET)
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
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
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

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

/**
  ******************************************************************************
  * @brief   RTC functions of the firmware library.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_rtc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup RTC
  * @brief RTC driver modules
  * @{
  */

/** @defgroup RTC_Private_Defines
  * @{
  */

/* RTC LSB Mask */
#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)

/* RTC Prescaler MSB Mask */
#define PRL1_MSB_MASK    ((uint32_t)0x000F0000)

/**
  * @}
  */

/** @defgroup RTC_Private_Functions
  * @{
  */

/**
  * @brief  Enable or disable the specified RTC interrupts.
  * @param  RTC_INT: specify the RTC interrupt sources
  *   This parameter can be any combination of the following value:
  *     @arg RTC_INT_OVI: Overflow event interrupt
  *     @arg RTC_INT_AI:  Alarm event interrupt
  *     @arg RTC_INT_SI:  Tamper event interrupt
  * @param  NewValue:  RTC interrupt state to configure
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_INT_Enable(uint16_t RTC_INT, TypeState NewValue)
{
    if (NewValue == ENABLE) {
        /* Enable the interrupts in RTC_CTLR register */
        RTC->CTLR1 |= RTC_INT;
    } else {
        /* Disable the interrupts in RTC_CTLR register */
        RTC->CTLR1 &= ~((uint16_t)RTC_INT);
    }
}

/**
  * @brief  Enter the RTC configuration mode.
  * @param  None
  * @retval None
  */
void RTC_EnterConfigMode(void)
{
    /* Enter in the Configuration Mode by set the CMF flag */
    RTC->CTLR2 |= RTC_CTLR2_CMF;
}

/**
  * @brief  Exit from the RTC configuration mode.
  * @param  None
  * @retval None
  */
void RTC_ExitConfigMode(void)
{
    /* Exit from the Configuration Mode by reset the CMF flag */
    RTC->CTLR2 &= ~((uint16_t)RTC_CTLR2_CMF);
}

/**
  * @brief  Get the RTC counter value.
  * @param  None
  * @retval The value of RTC counter.
  */
uint32_t RTC_GetCounter(void)
{
    uint16_t temp = 0;
    temp = RTC->CNT2;
    return (((uint32_t)RTC->CNT1 << 16) | temp) ;
}

/**
  * @brief  Set the RTC counter value.
  * @param  CounterValue: New value of the RTC counter.
  * @retval None
  */
void RTC_SetCounter(uint32_t CounterValue)
{
    RTC_EnterConfigMode();
    /* Set the RTC counter MSB word */
    RTC->CNT1 = CounterValue >> 16;
    /* Set the RTC counter LSB word */
    RTC->CNT2 = (CounterValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Set the RTC prescaler value.
  * @param  PrescalerValue: New value of the RTC prescaler.
  * @retval None
  */
void RTC_SetPrescaler(uint32_t PrescalerValue)
{
    RTC_EnterConfigMode();
    /* Set the RTC prescaler MSB word */
    RTC->PLR1 = (PrescalerValue & PRL1_MSB_MASK) >> 16;
    /* Set the RTC prescaler LSB word */
    RTC->PLR2 = (PrescalerValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Set the RTC alarm value.
  * @param  AlarmValue: New value of the RTC alarm.
  * @retval None
  */
void RTC_SetAlarm(uint32_t AlarmValue)
{
    RTC_EnterConfigMode();
    /* Set the alarm MSB word */
    RTC->ALRMR1 = AlarmValue >> 16;
    /* Set the alarm LSB word */
    RTC->ALRMR2 = (AlarmValue & RTC_LSB_MASK);
    RTC_ExitConfigMode();
}

/**
  * @brief  Get the RTC divider value.
  * @param  None
  * @retval The value of RTC Divider.
  */
uint32_t RTC_GetDivider(void)
{
    uint32_t temp = 0x00;
    temp = ((uint32_t)RTC->PREDIV1 & (uint32_t)0x000F) << 16;
    temp |= RTC->PREDIV2;
    return temp;
}

/**
  * @brief  Wait until last write operation on RTC registers has finished.
  * @note   This function must be called before any write to RTC registers.
  * @param  None
  * @retval None
  */
void RTC_WaitLWOFF(void)
{
    /* Loop until RTOFF flag is set */
    while ((RTC->CTLR2 & RTC_FLAG_LWOFF) == (uint16_t)RESET) {
    }
}

/**
  * @brief  Wait until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
  *   are synchronized with RTC APB clock.
  * @note   This function must be called before any read operation after an APB reset
  *   or an APB clock stop.
  * @param  None
  * @retval None
  */
void RTC_WaitRSF(void)
{
    /* Clear RSF flag */
    RTC->CTLR2 &= ~((uint16_t)RTC_FLAG_RSF);
    /* Loop until RSF flag is set */
    while ((RTC->CTLR2 & RTC_FLAG_RSF) == (uint16_t)RESET) {
    }
}

/**
  * @brief  Check whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifie the flag to check.
  *   This parameter can be one the following values:
  *     @arg RTC_FLAG_LWOFF: RTC Operation Off flag
  *     @arg RTC_FLAG_RSF:   Registers Synchronized flag
  *     @arg RTC_FLAG_OVF:   Overflow flag
  *     @arg RTC_FLAG_AF:    Alarm flag
  *     @arg RTC_FLAG_SF:    Second flag
  * @retval The new bitstate of RTC_FLAG (SET or RESET).
  */
TypeState RTC_GetBitState(uint16_t RTC_FLAG)
{
    if ((RTC->CTLR2 & RTC_FLAG) != (uint16_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the RTC's pending flags.
  * @param  RTC_FLAG: specifie the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_FLAG_RSF: Registers Synchronized flag. This flag is cleared only after
  *                        an APB reset or an APB Clock stop.
  *     @arg RTC_FLAG_OVF:   Overflow flag
  *     @arg RTC_FLAG_AF:    Alarm flag
  *     @arg RTC_FLAG_SF:    Second flag
  * @retval None
  */
void RTC_ClearBitState(uint16_t RTC_flag)
{
    /* Clear the corresponding RTC flag */
    RTC->CTLR2 &= ~((uint16_t)RTC_flag);
}

/**
  * @brief  Check whether the specified RTC interrupt has occurred or not.
  * @param  RTC_INT: specifie the RTC interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg RTC_INT_OVI: Overflow event interrupt
  *     @arg RTC_INT_AI:  Alarm event interrupt
  *     @arg RTC_INT_SI:  Tamper event interrupt
  * @retval The new state of the RTC_IT (SET or RESET).
  */
TypeState RTC_GetIntBitState(uint16_t RTC_INT)
{

    if (((RTC->CTLR1 & RTC_INT) != (uint16_t)RESET) && ((RTC->CTLR2 & RTC_INT) != (uint16_t)RESET)) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Clear the RTC's interrupt bit.
  * @param  RTC_INT: specifie the interrupt bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_INT_OVI: Overflow event interrupt
  *     @arg RTC_INT_AI:  Alarm event interrupt
  *     @arg RTC_INT_SI:  Tamper event interrupt
  * @retval None
  */
void RTC_ClearIntBitState(uint16_t RTC_INT)
{
    /* Clear the RTC's interrupt bitstate */
    RTC->CTLR2 &= ~((uint16_t)RTC_INT);
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


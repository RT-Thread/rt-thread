/*********************************************************************************************************//**
 * @file    ht32f5xxxx_exti.c
 * @version $Rev:: 6745         $
 * @date    $Date:: 2023-02-23 #$
 * @brief   This file provides all the EXTI firmware functions.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f5xxxx_exti.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup EXTI EXTI
  * @brief EXTI driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Private_Define EXTI private definitions
  * @{
  */
/* EXTI EVWUPIEN mask                                                                                       */
#define WAKUPCR_EVWUPIEN_SET      ((u32)0x80000000)
#define WAKUPCR_EVWUPIEN_RESET    ((u32)0x7FFFFFFF)

#if (LIBCFG_EXTI_8CH)
  const IRQn_Type gEXTIn_IRQn[16] = {
    EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn,
    EXTI4_IRQn, EXTI5_IRQn, EXTI6_IRQn, EXTI7_IRQn,
    EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn,
    EXTI4_IRQn, EXTI5_IRQn, EXTI6_IRQn, EXTI7_IRQn,
  };
#else
  const IRQn_Type gEXTIn_IRQn[16] = {
    EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn,
    EXTI4_IRQn, EXTI5_IRQn, EXTI6_IRQn, EXTI7_IRQn,
    EXTI8_IRQn, EXTI9_IRQn, EXTI10_IRQn, EXTI11_IRQn,
    EXTI12_IRQn, EXTI13_IRQn, EXTI14_IRQn, EXTI15_IRQn,
  };
#endif
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the EXTI peripheral registers.
 * @param EXTI_Channel: can be 0, 1 to 15 to select the EXTI Channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval None
 ************************************************************************************************************/
void EXTI_DeInit(u32 EXTI_Channel)
{
  u32 tmp;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  tmp = 1 << EXTI_Channel;

  *((u32 *) HT_EXTI + EXTI_Channel) = 0x0;
  HT_EXTI->CR &= (~tmp);
  HT_EXTI->EDGEFLGR = tmp;
  HT_EXTI->EDGESR = tmp;
  HT_EXTI->SSCR &= (~tmp);
  HT_EXTI->WAKUPCR &= (~tmp);
  HT_EXTI->WAKUPPOLR &= (~tmp);
  HT_EXTI->WAKUPFLG = tmp;
}

/*********************************************************************************************************//**
 * @brief Initialize the EXTI peripheral.
 * @param EXTI_InitStruct: pointer to a EXTI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
{
  u32 regval;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_InitStruct->EXTI_Channel));
  Assert_Param(IS_EXTI_DEBOUNCE_TYPE(EXTI_InitStruct->EXTI_Debounce));
  Assert_Param(IS_EXTI_DEBOUNCE_SIZE(EXTI_InitStruct->EXTI_DebounceCnt));
  Assert_Param(IS_EXTI_INT_TYPE(EXTI_InitStruct->EXTI_IntType));

  /* Set EXTI interrupt configuration                                                                       */
  regval = (EXTI_InitStruct->EXTI_Debounce << 31) | (EXTI_InitStruct->EXTI_IntType << 28) | (EXTI_InitStruct->EXTI_DebounceCnt);
  *((u32 *) HT_EXTI + EXTI_InitStruct->EXTI_Channel) = regval;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified EXTI channelx interrupts.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void EXTI_IntConfig(u32 EXTI_Channel, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  /* Configure EXTI interrupt                                                                               */
  if (NewState == ENABLE)
  {
    HT_EXTI->CR |= (1 << EXTI_Channel);
  }
  else
  {
    HT_EXTI->CR &= ~(1 << EXTI_Channel);
  }
}

#if (LIBCFG_EXTI_DEBCNTPRE)
/*********************************************************************************************************//**
 * @brief Configure the Debounce Counter prescaler.
 * @param EXTI_DebCntPre_DIVn: specify the prescaler value.
 *   This parameter can be one of the following values:
 *     @arg EXTI_DBCNTPRE_DIV1    : CK_DBCNT = EXTI_PCLK / 1
 *     @arg EXTI_DBCNTPRE_DIV2    : CK_DBCNT = EXTI_PCLK / 2
 *     @arg EXTI_DBCNTPRE_DIV4    : CK_DBCNT = EXTI_PCLK / 4
 *     @arg EXTI_DBCNTPRE_DIV8    : CK_DBCNT = EXTI_PCLK / 8
 *     @arg EXTI_DBCNTPRE_DIV16   : CK_DBCNT = EXTI_PCLK / 16
 *     @arg EXTI_DBCNTPRE_DIV32   : CK_DBCNT = EXTI_PCLK / 32
 *     @arg EXTI_DBCNTPRE_DIV64   : CK_DBCNT = EXTI_PCLK / 64
 *     @arg EXTI_DBCNTPRE_DIV128  : CK_DBCNT = EXTI_PCLK / 128
 * @retval None
 ************************************************************************************************************/
void EXTI_SetDebounceCounterPrescaler(EXTI_DebCntPre_TypeDef EXTI_DBCNTPRE_DIVn)
{
  /* Check the parameters */
  Assert_Param(IS_EXTI_DEBOUNCE_COUNTER_PRESCALER(EXTI_DBCNTPRE_DIVn));

  HT_EXTI->CFGR0 = ((HT_EXTI->CFGR0 & 0xF8FFFFFF) | (EXTI_DBCNTPRE_DIVn << 24));
}
#endif

/*********************************************************************************************************//**
 * @brief Configure the EXTI channelx event wakeup function.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @param EXTI_WakeUpType: determines the type of signal to trigger EXTI interrupt.
 *   This parameter can be one of the following values:
 *     @arg EXTI_WAKEUP_HIGH_LEVEL
 *     @arg EXTI_WAKEUP_LOW_LEVEL
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void EXTI_WakeupEventConfig(u32 EXTI_Channel, u8 EXTI_WakeUpType, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_EXTI_WAKEUP_TYPE(EXTI_WakeUpType));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == ENABLE)
  {
    if (EXTI_WakeUpType == EXTI_WAKEUP_HIGH_LEVEL)
    {
      HT_EXTI->WAKUPPOLR &= ~(1 << EXTI_Channel);
    }
    else
    {
      HT_EXTI->WAKUPPOLR |= (1 << EXTI_Channel);
    }

    HT_EXTI->WAKUPCR |=  (1 << EXTI_Channel);
  }
  else
  {
    HT_EXTI->WAKUPCR &= ~(1 << EXTI_Channel);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the EXTI channelx event wakeup interrupt.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void EXTI_WakeupEventIntConfig(ControlStatus NewState)
{
  if (NewState == ENABLE)
  {
    /* Set EVWUPIEN bit                                                                                     */
    HT_EXTI->WAKUPCR |= WAKUPCR_EVWUPIEN_SET;
  }
  else
  {
    /* Clear EVWUPIEN bit                                                                                   */
    HT_EXTI->WAKUPCR &= WAKUPCR_EVWUPIEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified EXTI channelx edge flag.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval None
 ************************************************************************************************************/
void EXTI_ClearEdgeFlag(u32 EXTI_Channel)
{
  u32 tmp;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  tmp = 1 << EXTI_Channel;

  /* Write 1 to clear both edge detection flag                                                              */
  HT_EXTI->EDGEFLGR = tmp;
  /* Write 1 to clear positive edge detection flag                                                          */
  HT_EXTI->EDGESR = tmp;
}

/*********************************************************************************************************//**
 * @brief Clear the specified EXTI channelx wakeup flag.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval None
 ************************************************************************************************************/
void EXTI_ClearWakeupFlag(u32 EXTI_Channel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  /* Write 1 to clear wake up flag                                                                          */
  HT_EXTI->WAKUPFLG = 1 << EXTI_Channel;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-Mx when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Get the specified EXTI channelx edge flag.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EXTI_GetEdgeFlag(u32 EXTI_Channel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  return ((HT_EXTI->EDGEFLGR & (1UL << EXTI_Channel)) ? SET : RESET);
}

/*********************************************************************************************************//**
 * @brief Get the specified EXTI channelx edge status.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @param EXTI_Edge: can be status of edge that user want to monitor.
 *   This parameter can be one of the following values:
 *     @arg EXTI_EDGE_POSITIVE
 *     @arg EXTI_EDGE_NEGATIVE
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EXTI_GetEdgeStatus(u32 EXTI_Channel, u32 EXTI_Edge)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_EXTI_EDGE(EXTI_Edge));

  if (HT_EXTI->EDGEFLGR & (1UL << EXTI_Channel))
  {
    if (GetBit_BB((u32)&HT_EXTI->EDGESR, EXTI_Channel) ^ EXTI_Edge)
    {
      return SET;
    }
    else
    {
      return RESET;
    }
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Get the specified EXTI channelx wakeup flag.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EXTI_GetWakeupFlagStatus(u32 EXTI_Channel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  if (HT_EXTI->WAKUPFLG & (1 << EXTI_Channel))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Activate or Deactivate an EXTI channelx interrupt by software.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void EXTI_SWIntCmd(u32 EXTI_Channel, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState == ENABLE)
  {
    HT_EXTI->SSCR = 1 << EXTI_Channel;
  }
  else
  {
    HT_EXTI->SSCR &= ~(1 << EXTI_Channel);
  }
}

/*********************************************************************************************************//**
 * @brief Get the specified EXTI channelx software command register bit.
 * @param EXTI_Channel: specify the EXTI channel.
 *   This parameter can be one of the following values:
 *     @arg EXTI_CHANNEL_0
 *     @arg EXTI_CHANNEL_1
 *     @arg EXTI_CHANNEL_2
 *     @arg EXTI_CHANNEL_3
 *     @arg EXTI_CHANNEL_4
 *     @arg EXTI_CHANNEL_5
 *     @arg EXTI_CHANNEL_6
 *     @arg EXTI_CHANNEL_7
 *     @arg EXTI_CHANNEL_8
 *     @arg EXTI_CHANNEL_9
 *     @arg EXTI_CHANNEL_10
 *     @arg EXTI_CHANNEL_11
 *     @arg EXTI_CHANNEL_12
 *     @arg EXTI_CHANNEL_13
 *     @arg EXTI_CHANNEL_14
 *     @arg EXTI_CHANNEL_15
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus EXTI_GetSWCmdStatus(u32 EXTI_Channel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_EXTI_CHANNEL(EXTI_Channel));

  if (HT_EXTI->SSCR & (1 << EXTI_Channel))
  {
    return SET;
  }
  else
  {
    return RESET;
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

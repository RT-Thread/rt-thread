/*********************************************************************************************************//**
 * @file    ht32f1xxxx_sci.c
 * @version $Rev:: 2797         $
 * @date    $Date:: 2022-11-28 #$
 * @brief   This file provides all the SCI firmware functions.
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
#include "ht32f1xxxx_sci.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup SCI SCI
  * @brief SCI driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup SCI_Private_Define SCI private definitions
  * @{
  */
/* SCI ENSCI mask                                                                                           */
#define CR_ENSCI_SET             ((u32)0x00000020)
#define CR_ENSCI_RESET           ((u32)0xFFFFFFDF)

/* SCI WTEN mask                                                                                            */
#define CR_WTEN_SET              ((u32)0x00000004)
#define CR_WTEN_RESET            ((u32)0xFFFFFFFB)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SCI_Exported_Functions SCI exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the SCI peripheral registers to their default reset values.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @retval None
 ************************************************************************************************************/
void SCI_DeInit(HT_SCI_TypeDef* SCIx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  if (SCIx == HT_SCI0)
  {
    RSTCUReset.Bit.SCI0 = 1;
  }
  #if (LIBCFG_SCI1)
  else
  {
    RSTCUReset.Bit.SCI1 = 1;
  }
  #endif
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the SCI peripheral according to the specified parameters in the SCI_InitStruct.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_InitStruct: pointer to a SCI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SCI_Init(HT_SCI_TypeDef* SCIx, SCI_InitTypeDef* SCI_InitStruct)
{
  u32 tmpreg;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_MODE(SCI_InitStruct->SCI_Mode));
  Assert_Param(IS_SCI_RETRY(SCI_InitStruct->SCI_Retry));
  Assert_Param(IS_SCI_CONVENTION(SCI_InitStruct->SCI_Convention));
  Assert_Param(IS_SCI_CARD_POLARITY(SCI_InitStruct->SCI_CardPolarity));
  Assert_Param(IS_SCI_CLOCK_PRESCALER(SCI_InitStruct->SCI_ClockPrescale));


  /*------------------------- SCI Control Register Configuration -------------------------------------------*/
  tmpreg = SCIx->CR;
  tmpreg &= 0xFFFFFFA4;

  tmpreg |= SCI_InitStruct->SCI_Mode | SCI_InitStruct->SCI_Retry | SCI_InitStruct->SCI_Convention |
            SCI_InitStruct->SCI_CardPolarity;

  SCIx->CR = tmpreg;

  /*------------------------- SCI Prescaler Register Configuration -----------------------------------------*/
  SCIx->PSC = SCI_InitStruct->SCI_ClockPrescale;
}

/*********************************************************************************************************//**
 * @brief Initialize the SCI peripheral according to the specified parameters in the SCI_InitStruct.
 * @param SCI_InitStruct: pointer to a SCI_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SCI_StructInit(SCI_InitTypeDef* SCI_InitStruct)
{
  /* Initialize the SCI_Mode member                                                                         */
  SCI_InitStruct->SCI_Mode = SCI_MODE_MANUAL;

  /* Initialize the SCI_Retry member                                                                        */
  SCI_InitStruct->SCI_Retry = SCI_RETRY_NO;

  /* Initialize the SCI_Convention member                                                                   */
  SCI_InitStruct->SCI_Convention = SCI_CONVENTION_DIRECT;

  /* Initialize the SCI_CardPolarity member                                                                 */
  SCI_InitStruct->SCI_CardPolarity = SCI_CARDPOLARITY_LOW;

  /* Initialize the SCI_ClockPrescale member                                                                */
  SCI_InitStruct->SCI_ClockPrescale = SCI_CLKPRESCALER_1;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SCI peripheral.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SCI_Cmd(HT_SCI_TypeDef* SCIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCIx->CR |= CR_ENSCI_SET;
  }
  else
  {
    SCIx->CR &= CR_ENSCI_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief This function is used to configure the Elementary Time Unit.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_ETU: specify the SCI Elementary Time Unit.
 * @param SCI_Compensation: Enable or Disable the Compensation mode.
 *   This parameter can be one of the following values:
 *     @arg SCI_COMPENSATION_ENABLE  : Compensation mode enabled
 *     @arg SCI_COMPENSATION_DISABLE : Compensation mode disabled
 * @retval None
 ************************************************************************************************************/
void SCI_ETUConfig(HT_SCI_TypeDef* SCIx, u32 SCI_ETU, u32 SCI_Compensation)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_ETU(SCI_ETU));
  Assert_Param(IS_SCI_ETU_COMPENSATION(SCI_Compensation));

  SCIx->ETU = SCI_ETU | SCI_Compensation;
}

/*********************************************************************************************************//**
 * @brief This function is used to set the value of SCI GuardTime.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_GuardTime: specify the value of SCI GuardTime value.
 * @retval None
 ************************************************************************************************************/
void SCI_SetGuardTimeValue(HT_SCI_TypeDef* SCIx, u16 SCI_GuardTime)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_GUARDTIME(SCI_GuardTime));

  SCIx->GT = SCI_GuardTime;
}

/*********************************************************************************************************//**
 * @brief This function is used to set the value of SCI Waiting Time.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_WaitingTime: specify the value of SCI Waiting Time value.
 * @retval None
 ************************************************************************************************************/
void SCI_SetWaitingTimeValue(HT_SCI_TypeDef* SCIx, u32 SCI_WaitingTime)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_WAITING_TIME(SCI_WaitingTime));

  SCIx->WT = SCI_WaitingTime;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Waiting Time Counter.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SCI_WaitingTimeCounterCmd(HT_SCI_TypeDef* SCIx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCIx->CR |= CR_WTEN_SET;
  }
  else
  {
    SCIx->CR &= CR_WTEN_RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Sends a data byte through the SCI peripheral.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_Data: byte to be transmitted.
 * @retval None
 ************************************************************************************************************/
void SCI_SendData(HT_SCI_TypeDef* SCIx, u8 SCI_Data)
{
  SCIx->TXB = SCI_Data;
}

/*********************************************************************************************************//**
 * @brief Returns the received data through the SCI peripheral.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @retval The value of the received data.
 ************************************************************************************************************/
u8 SCI_ReceiveData(HT_SCI_TypeDef* SCIx)
{
  return ((u8)SCIx->RXB);
}

/*********************************************************************************************************//**
 * @brief Determines the SCI output clock signal is driven by hardware or software.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_CLKMode: specify the SCI clock pin mode.
 *   This parameter can be one of the following values:
 *     @arg SCI_CLK_SOFTWARE : SCI output clock is controlled by software
 *     @arg SCI_CLK_HARDWARE : SCI output clock is controlled by hardware
 * @retval None
 ************************************************************************************************************/
void SCI_ClockModeConfig(HT_SCI_TypeDef* SCIx, u32 SCI_CLKMode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_CLK_MODE(SCI_CLKMode));

  if (SCI_CLKMode != SCI_CLK_SOFTWARE)
  {
    SCIx->CCR |= SCI_CLK_HARDWARE;
  }
  else
  {
    SCIx->CCR &= SCI_CLK_SOFTWARE;
  }
}

/*********************************************************************************************************//**
 * @brief Output the SCI clock pin low or high by software.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_CLK: specify if the SCI clock pin to be high or low.
 *   This parameter can be one of the following values:
 *     @arg SCI_CLK_HIGH : Software drive SCI output clock high
 *     @arg SCI_CLK_LOW  : Software drive SCI output clock low
 * @retval None
 ************************************************************************************************************/
void SCI_SoftwareClockCmd(HT_SCI_TypeDef* SCIx, u32 SCI_CLK)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_CLK(SCI_CLK));

  if (SCI_CLK != SCI_CLK_LOW)
  {
    SCIx->CCR |= SCI_CLK_HIGH;
  }
  else
  {
    SCIx->CCR &= SCI_CLK_LOW;
  }
}

/*********************************************************************************************************//**
 * @brief Output the SCI DIO pin low or high by software.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_DIO: specify if the SCI DIO pin to be high or low.
 *   This parameter can be one of the following values:
 *     @arg SCI_DIO_HIGH : Drive SCI DIO signal high
 *     @arg SCI_DIO_LOW  : Drive SCI DIO signal low
 * @retval None
 ************************************************************************************************************/
void SCI_OutputDIO(HT_SCI_TypeDef* SCIx, u32 SCI_DIO)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_DIO(SCI_DIO));

  if (SCI_DIO != SCI_DIO_LOW)
  {
    SCIx->CCR |= SCI_DIO_HIGH;
  }
  else
  {
    SCIx->CCR &= SCI_DIO_LOW;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified SCI interrupt.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_Int: specify the SCI interrupt source to be enabled or disable.
 *   This parameter can be any combination of the following values:
 *     @arg SCI_INT_PAR  : SCI parity error interrupt
 *     @arg SCI_INT_RXC  : SCI received character interrupt
 *     @arg SCI_INT_TXC  : SCI transmitted character interrupt
 *     @arg SCI_INT_WT   : SCI waiting timer interrupt
 *     @arg SCI_INT_CARD : SCI card insert/remove interrupt
 *     @arg SCI_INT_TXBE : SCI transmit buffer empty interrupt
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SCI_IntConfig(HT_SCI_TypeDef* SCIx, u32 SCI_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_INT(SCI_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCIx->IER |= SCI_Int;
  }
   else
  {
    SCIx->IER &= ~SCI_Int;
  }
}

/*********************************************************************************************************//**
 * @brief Get the status of specified SCI flag.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_Flag: specify the flag that is to be check.
 *   This parameter can be one of the following values:
 *     @arg SCI_FLAG_PAR  : SCI parity error flag
 *     @arg SCI_FLAG_RXC  : SCI received character flag
 *     @arg SCI_FLAG_TXC  : SCI transmitted character flag
 *     @arg SCI_FLAG_WT   : SCI waiting timer flag
 *     @arg SCI_FLAG_CARD : SCI card insert/remove flag
 *     @arg SCI_FLAG_TXBE : SCI transmit buffer empty flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus SCI_GetFlagStatus(HT_SCI_TypeDef* SCIx, u32 SCI_Flag)
{
  u32 statusreg = 0;
  FlagStatus bitstatus = RESET;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_FLAG(SCI_Flag));

  statusreg = SCIx->SR;

  if ((statusreg & SCI_Flag) != (u32)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*********************************************************************************************************//**
 * @brief Clears the flag status of specified SCI flag.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_Flag: specify the flag to be cleared.
 *   This parameter can be one of the following values:
 *     @arg SCI_FLAG_PAR : SCI parity error flag
 *     @arg SCI_FLAG_TXC : SCI transmitted character flag
 *     @arg SCI_FLAG_WT  : SCI waiting timer flag
 * @retval None
 ************************************************************************************************************/
void SCI_ClearFlag(HT_SCI_TypeDef* SCIx, u32 SCI_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_CLEAR_FLAG(SCI_Flag));

  if (SCI_Flag != SCI_FLAG_WT)
  {
    SCIx->SR &= ~SCI_Flag;
  }
  else
  {
    SCIx->CR &= CR_WTEN_RESET;
    SCIx->CR |= CR_WTEN_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or disables the SCI PDMA interface.
 * @param SCIx: where SCIx is the selected SCI from the SCI peripherals.
 * @param SCI_PDMAREQ: specify the SCI PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg SCI_PDMAREQ_TX : Tx PDMA transfer request
 *     @arg SCI_PDMAREQ_RX : Rx PDMA transfer request
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SCI_PDMACmd(HT_SCI_TypeDef* SCIx, u32 SCI_PDMAREQ, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SCI_PDMA_REQ(SCI_PDMAREQ));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SCIx->CR |= SCI_PDMAREQ;
  }
  else
  {
    SCIx->CR &= ~SCI_PDMAREQ;
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

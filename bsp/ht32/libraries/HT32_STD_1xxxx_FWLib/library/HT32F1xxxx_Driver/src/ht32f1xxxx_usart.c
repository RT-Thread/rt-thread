/*********************************************************************************************************//**
 * @file    ht32f1xxxx_usart.c
 * @version $Rev:: 2972         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   This file provides all the USART firmware functions.
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
#include "ht32f1xxxx_usart.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup USART USART
  * @brief USART driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup USART_Private_Define USART private definitions
  * @{
  */
#if (LIBCFG_USART_V01)
#define MDR_CLEAR_Mask            ((u32)0xFFFFFFFC)
#define LCR_CLEAR_Mask            ((u32)0xFFFFFFE0)

#define USART_TIMEOUT_ON          ((u32)0x00000080)
#define USART_TIMEOUT_OFF         ((u32)0xFFFFFF7F)

#define USART_BREAK_ON            ((u32)0x00000040)
#define USART_BREAK_OFF           ((u32)0xFFFFFFBF)

#define USART_SPE_ON              ((u32)0x00000020)
#define USART_SPE_OFF             ((u32)0xFFFFFFDF)

#define USART_EN_ON               ((u32)0x00000100)

#define USART_HFCEN_ON            ((u32)0x00000004)
#define USART_HFCEN_OFF           ((u32)0xFFFFFFFB)
#else
#define CR_CLEAR_Mask             ((u32)0xFFFFE0FC)

#define USART_BREAK_ON            ((u32)0x00004000)
#define USART_BREAK_OFF           ((u32)0xFFFFBFFF)

#define USART_PBE_ON              ((u32)0x00000800)
#define USART_SPE_ON              ((u32)0x00002000)
#define USART_SPE_OFF             ((u32)0xFFFFDFFF)

#define USART_EN_ON               ((u32)0x00000010)

#define USART_HFCEN_ON            ((u32)0x00000008)
#define USART_HFCEN_OFF           ((u32)0xFFFFFFF7)

#define USART_RXTOEN_ON           ((u32)0x00000080)
#endif

#define FCR_TL_Mask               ((u32)0x00000030)

#define TRSM_CLEAR_Mask           ((u32)0xFFFFFFFB)
#define TPR_TG_Mask               ((u32)0xFFFF00FF)
#define ICR_IRDAPSC_Mask          ((u32)0xFFFF00FF)
#define TPR_RXTOIC_Mask           ((u32)0xFFFFFF80)
#define RS485CR_ADDM_Mask         ((u32)0xFFFF00FF)

#define USART_IRDA_ON             ((u32)0x00000001)
#define USART_IRDA_OFF            ((u32)0xFFFFFFFE)

#define USART_INV_ON              ((u32)0x00000010)

#define USART_RS485NMM_ON         ((u32)0x00000002)
#define USART_RS485NMM_OFF        ((u32)0xFFFFFFFD)

#define USART_RS485AAD_ON         ((u32)0x00000004)
#define USART_RS485AAD_OFF        ((u32)0xFFFFFFFB)
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup USART_Exported_Functions USART exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the USART/UART peripheral registers to their default reset values.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @retval None
 ************************************************************************************************************/
void USART_DeInit(HT_USART_TypeDef* USARTx)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};
  u32 uIPAddr = (u32)USARTx;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));

  switch (uIPAddr)
  {
    case HT_USART0_BASE:
    {
      RSTCUReset.Bit.USART0 = 1;
      break;
    }
    #if !(LIBCFG_NO_USART1)
    case HT_USART1_BASE:
    {
      RSTCUReset.Bit.USART1 = 1;
      break;
    }
    #endif
    case HT_UART0_BASE:
    {
      RSTCUReset.Bit.UART0 = 1;
      break;
    }
    case HT_UART1_BASE:
    {
      RSTCUReset.Bit.UART1 = 1;
      break;
    }
  }

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the USART/UART peripheral according to the specified parameters in the USART_InitStruct.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_InitStruct: pointer to a USART_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void USART_Init(HT_USART_TypeDef* USARTx, USART_InitTypeDef* USART_InitStruct)
{
  u32 uIPClock = 0;
  u32 uIPAddr = (u32)USARTx;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
  Assert_Param(IS_USART_WORD_LENGTH(USART_InitStruct->USART_WordLength));
  Assert_Param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
  Assert_Param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
  Assert_Param(IS_USART_MODE(USART_InitStruct->USART_Mode));

  #if (LIBCFG_USART_V01)
  USARTx->LCR = (USARTx->LCR & LCR_CLEAR_Mask) | USART_InitStruct->USART_StopBits |
                 USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity;

  USARTx->MDR = (USARTx->MDR & MDR_CLEAR_Mask) | USART_InitStruct->USART_Mode;
  #else
  USARTx->CR = (USARTx->CR & CR_CLEAR_Mask) | USART_InitStruct->USART_StopBits |
                USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
                USART_InitStruct->USART_Mode;
  #endif

  switch (uIPAddr)
  {
    case HT_USART0_BASE:
    {
      uIPClock = CKCU_GetPeripFrequency(CKCU_PCLK_USART0);
      break;
    }
    #if !(LIBCFG_NO_USART1)
    case HT_USART1_BASE:
    {
      uIPClock = CKCU_GetPeripFrequency(CKCU_PCLK_USART1);
      break;
    }
    #endif
    case HT_UART0_BASE:
    {
      uIPClock = CKCU_GetPeripFrequency(CKCU_PCLK_UART0);
      break;
    }
    case HT_UART1_BASE:
    {
      uIPClock = CKCU_GetPeripFrequency(CKCU_PCLK_UART1);
      break;
    }
  }

  USARTx->DLR = uIPClock / (u32)USART_InitStruct->USART_BaudRate;
}

/*********************************************************************************************************//**
 * @brief Fill each USART_InitStruct member with its default value.
 * @param USART_InitStruct: pointer to a USART_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void USART_StructInit(USART_InitTypeDef* USART_InitStruct)
{
  /* USART_InitStruct members default value                                                                 */
  USART_InitStruct->USART_BaudRate = 9600;
  USART_InitStruct->USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStruct->USART_StopBits = USART_STOPBITS_1;
  USART_InitStruct->USART_Parity = USART_PARITY_NO;
  USART_InitStruct->USART_Mode = USART_MODE_NORMAL;
}

/*********************************************************************************************************//**
 * @brief USART/UART send data to Tx.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param Data: the data to be transmitted.
 * @retval None
 ************************************************************************************************************/
void USART_SendData(HT_USART_TypeDef* USARTx, u16 Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_DATA(Data));

  USARTx->DR = Data;
}

/*********************************************************************************************************//**
 * @brief USART/UART receive data from Rx.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @retval The received data.
 ************************************************************************************************************/
u16 USART_ReceiveData(HT_USART_TypeDef* USARTx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));

  return (u16)(USARTx->DR);
}

/*********************************************************************************************************//**
 * @brief Get the specified USART/UART status flags.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_FLAG_x: Specify the flag to be check.
 *   This parameter can be one of the following values:
 *          LIBCFG_USART_V01 / LIBCFG_USART_V01_LEGACY:
 *     @arg USART_FLAG_RXDNE / USART_LSR_RFDR
 *     @arg USART_FLAG_THRE  / USART_LSR_THRE
 *     @arg USART_FLAG_TXC   / USART_LSR_TE
 *     @arg USART_FLAG_ERR   / USART_LSR_ERR
 *     @arg USART_FLAG_MODIS
 *     @arg USART_FLAG_TXDE
 *     @arg USART_FLAG_RXDR
 *     @arg USART_FLAG_RLSI
 *     @arg USART_FLAG_TOUT
 *     HT32F1xxxx:
 *     @arg USART_FLAG_RXDNE :
 *     @arg USART_FLAG_OE    :
 *     @arg USART_FLAG_PE    :
 *     @arg USART_FLAG_FE    :
 *     @arg USART_FLAG_BI    :
 *     @arg USART_FLAG_RXDR  :
 *     @arg USART_FLAG_TOUT  :
 *     @arg USART_FLAG_TXDE  :
 *     @arg USART_FLAG_TXC   :
 *     @arg USART_FLAG_RSADD :
 *     @arg USART_FLAG_CTSC  :
 *     @arg USART_FLAG_CTSS  :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus USART_GetFlagStatus(HT_USART_TypeDef* USARTx, u32 USART_FLAG_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_FLAG(USART_FLAG_x));

  #if (LIBCFG_USART_V01)
  if (USART_FLAG_x & USART_FLAG_FROM_IIR)
  {
    if (USARTx->IIR == (USART_FLAG_x & (~(USART_FLAG_FROM_IIR))))
    {
      return (SET);
    }
    else
    {
      return (RESET);
    }
  }
  else
  {
  #endif

  if ((USARTx->SR & USART_FLAG_x) != (u32)RESET)
  {
    return (SET);
  }
  else
  {
    return (RESET);
  }

  #if (LIBCFG_USART_V01)
  }
  #endif
}

#if (LIBCFG_USART_V01)
#else
/*********************************************************************************************************//**
 * @brief Get the specified USART/UART INT status.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_INT_x: Specify if the USART/UART interrupt source.
 *   This parameter can be one of the following values:
 *     @arg USART_INT_RXDR  :
 *     @arg USART_INT_TXDE  :
 *     @arg USART_INT_TXC   :
 *     @arg USART_INT_OE    :
 *     @arg USART_INT_PE    :
 *     @arg USART_INT_FE    :
 *     @arg USART_INT_BI    :
 *     @arg USART_INT_RSADD :
 *     @arg USART_INT_TOUT  :
 *     @arg USART_INT_CTS   :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus USART_GetIntStatus(HT_USART_TypeDef* USARTx, u32 USART_INT_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_INT(USART_INT_x));

  if ((USARTx->IER & USART_INT_x) != (u32)RESET)
  {
    return (SET);
  }
  else
  {
    return (RESET);
  }
}

/*********************************************************************************************************//**
 * @brief Clear the specified USART/UART flags.
 * @param USARTx: where USARTx is the selected USART/UART from the USART/UART peripherals.
 * @param USART_Flag: Specify the flag to check.
 *   This parameter can be any combination of the following values:
 *     @arg USART_FLAG_OE    :
 *     @arg USART_FLAG_PE    :
 *     @arg USART_FLAG_FE    :
 *     @arg USART_FLAG_BI    :
 *     @arg USART_FLAG_TOUT  :
 *     @arg USART_FLAG_RSADD :
 *     @arg USART_FLAG_CTSC  :
 * @retval SET or RESET
 ************************************************************************************************************/
void USART_ClearFlag(HT_USART_TypeDef* USARTx, u32 USART_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_CLEAR_FLAG(USART_Flag));

  USARTx->SR &= USART_Flag;
}
#endif

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART/UART interrupts.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_INT_x: Specify if the USART/UART interrupt source to be enabled or disabled.
 *   This parameter can be one of the following values:
 *          LIBCFG_USART_V01 / LIBCFG_USART_V01_LEGACY
 *     @arg USART_INT_RXDR   / USART_IER_RDAIE  :
 *     @arg USART_INT_TXDE   / USART_IER_THREIE :
 *     @arg USART_INT_RLSIE  / USART_IER_RLSIE  : TXC, OE, PE, FE, BI, RSADD
 *     @arg USART_INT_MSIE   / USART_IER_MSIE   :
 *     HT32F1xxxx:
 *     @arg USART_INT_RXDR  :
 *     @arg USART_INT_TXDE  :
 *     @arg USART_INT_TXC   :
 *     @arg USART_INT_OE    :
 *     @arg USART_INT_PE    :
 *     @arg USART_INT_FE    :
 *     @arg USART_INT_BI    :
 *     @arg USART_INT_RSADD :
 *     @arg USART_INT_TOUT  :
 *     @arg USART_INT_CTS   :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_IntConfig(HT_USART_TypeDef* USARTx, u32 USART_INT_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_INT(USART_INT_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (USART_INT_x & USART_INT_TOUT)
  {
    if (NewState != DISABLE)
    {
      USARTx->TPR |= USART_TIMEOUT_ON;
    }
    else
    {
      USARTx->TPR &= USART_TIMEOUT_OFF;
    }
  }
  #endif

  if (NewState != DISABLE)
  {
    USARTx->IER |= USART_INT_x;
  }
  else
  {
    USARTx->IER &= ~USART_INT_x;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART Tx/Rx.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param TxRx: This parameter can be USART_CMD_TX or USART_CMD_RX.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_TxRxCmd(HT_USART_TypeDef* USARTx, u32 TxRx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (NewState != DISABLE)
  {
    USARTx->FCR |= (USART_EN_ON << TxRx);
  }
  else
  {
    USARTx->FCR &= ~(USART_EN_ON << TxRx);
  }
  #else
  if (NewState != DISABLE)
  {
    USARTx->CR |= (USART_EN_ON << TxRx);
  }
  else
  {
    USARTx->CR &= ~(USART_EN_ON << TxRx);
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART/UART PDMA interface.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_PDMAREQ: specify the USART/UART PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg USART_PDMAREQ_TX
 *     @arg USART_PDMAREQ_RX
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_PDMACmd(HT_USART_TypeDef* USARTx, u32 USART_PDMAREQ, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_PDMA_REQ(USART_PDMAREQ));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (NewState != DISABLE)
  {
    USARTx->MDR |= USART_PDMAREQ;
  }
  else
  {
    USARTx->MDR &= ~USART_PDMAREQ;
  }
  #else
  if (NewState != DISABLE)
  {
    USARTx->CR |= USART_PDMAREQ;
  }
  else
  {
    USARTx->CR &= ~USART_PDMAREQ;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART/UART break control function.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_ForceBreakCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (NewState != DISABLE)
  {
    USARTx->LCR |= USART_BREAK_ON;
  }
  else
  {
    USARTx->LCR &= USART_BREAK_OFF;
  }
  #else
  if (NewState != DISABLE)
  {
    USARTx->CR |= USART_BREAK_ON;
  }
  else
  {
    USARTx->CR &= USART_BREAK_OFF;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART/UART stick parity function.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_StickParityCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (NewState != DISABLE)
  {
    USARTx->LCR |= USART_SPE_ON;
  }
  else
  {
    USARTx->LCR &= USART_SPE_OFF;
  }
  #else
  if (NewState != DISABLE)
  {
    USARTx->CR |= USART_SPE_ON | USART_PBE_ON;
  }
  else
  {
    USARTx->CR &= USART_SPE_OFF;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Configure the stick parity value of the USART/UART.
 * @param USARTx: Parameter to select the UxART peripheral.
 * @param USART_StickParity: Specify the stick parity of the USART/UART.
 *   This parameter can be one of the following values:
 *     @arg USART_STICK_LOW
 *     @arg USART_STICK_HIGH
 * @retval None
 ************************************************************************************************************/
void USART_StickParityConfig(HT_USART_TypeDef * USARTx, u32 USART_StickParity)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_STICK_PARITY(USART_StickParity));

  #if (LIBCFG_USART_V01)
  if (USART_StickParity != USART_STICK_HIGH)
  {
    USARTx->LCR |= USART_STICK_LOW;
  }
  else
  {
    USARTx->LCR &= USART_STICK_HIGH;
  }
  #else
  if (USART_StickParity != USART_STICK_HIGH)
  {
    USARTx->CR |= USART_STICK_LOW;
  }
  else
  {
    USARTx->CR &= USART_STICK_HIGH;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Set the specified USART guard time.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_GuardTime: Specify the guard time.
 * @retval None
 ************************************************************************************************************/
void USART_SetGuardTime(HT_USART_TypeDef* USARTx, u32 USART_GuardTime)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_GUARD_TIME(USART_GuardTime));

  USARTx->TPR = (USARTx->TPR & TPR_TG_Mask) | (USART_GuardTime << 0x08);
}

/*********************************************************************************************************//**
 * @brief Configure the Tx/Rx FIFO Interrupt Trigger Level.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param TxRx: This parameter can be USART_CMD_TX or USART_CMD_RX.
 * @param USART_tl: Specify the USART Tx/Rx FIFO interrupt trigger level.
 *   This parameter can be one of the following values:
 *     For LIBCFG_USART_V01:
 *     @arg USART_RXTL_01
 *     @arg USART_RXTL_04
 *     @arg USART_RXTL_08
 *     @arg USART_RXTL_14
 *     @arg USART_TXTL_00
 *     @arg USART_TXTL_02
 *     @arg USART_TXTL_04
 *     @arg USART_TXTL_08
 *     For HT32F1xxxx:
 *     @arg USART_RXTL_01
 *     @arg USART_RXTL_02
 *     @arg USART_RXTL_04
 *     @arg USART_RXTL_06
 *     @arg USART_TXTL_00
 *     @arg USART_TXTL_02
 *     @arg USART_TXTL_04
 *     @arg USART_TXTL_06
 * @retval None
 ************************************************************************************************************/
void USART_TXRXTLConfig(HT_USART_TypeDef* USARTx, u32 TxRx, u32 USART_tl)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_TL(USART_tl));

  USARTx->FCR = (USARTx->FCR & ~(FCR_TL_Mask << (TxRx * 2))) | (USART_tl << (TxRx * 2));
}

/*********************************************************************************************************//**
 * @brief Set the USART FIFO time-out value.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_TimeOut: Specify the time-out value.
 * @retval None
 ************************************************************************************************************/
void USART_SetTimeOutValue(HT_USART_TypeDef* USARTx, u32 USART_TimeOut)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_TIMEOUT(USART_TimeOut));

  #if (LIBCFG_USART_V01)
  USARTx->TPR = (USARTx->TPR & TPR_RXTOIC_Mask) | USART_TimeOut;
  #else
  USARTx->TPR = (USARTx->TPR & TPR_RXTOIC_Mask) | USART_TimeOut | USART_RXTOEN_ON;
  #endif
}

/*********************************************************************************************************//**
 * @brief Clear both the write and read point in USART Tx FIFO or Rx FIFO.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_FIFODirection: Determine TX FIFO or Rx FIFO that is to be reset.
 *   This parameter can be any combination of the following values:
 *     @arg USART_FIFO_TX
 *     @arg USART_FIFO_RX
 * @retval None
 ************************************************************************************************************/
void USART_FIFOReset(HT_USART_TypeDef* USARTx, u32 USART_FIFODirection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_FIFO_DIRECTION(USART_FIFODirection));

  USARTx->FCR |= USART_FIFODirection;
}

/*********************************************************************************************************//**
 * @brief Return the status of specified USART FIFO.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_FIFODirection: specify the FIFO that is to be check.
 *   This parameter can be one of the following values:
 *     @arg USART_FIFO_TX
 *     @arg USART_FIFO_RX
 * @retval The number of data in Tx FIFO or Rx FIFO.
 ************************************************************************************************************/
u8 USART_GetFIFOStatus(HT_USART_TypeDef* USARTx, u32 USART_FIFODirection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_FIFO_DIRECTION(USART_FIFODirection));

  #if (LIBCFG_USART_V01)
  if (USART_FIFODirection == USART_FIFO_TX)
  {
    return (u8)(USARTx->FSR & 0x1F);
  }
  else
  {
    return (u8)((USARTx->FSR & 0x1F00) >> 8);
  }
  #else
  if (USART_FIFODirection == USART_FIFO_TX)
  {
    return (u8)((USARTx->FCR & 0xF0000) >> 16);
  }
  else
  {
    return (u8)((USARTx->FCR & 0xF000000) >> 24);
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART hardware flow control.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_HardwareFlowControlCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  #if (LIBCFG_USART_V01)
  if (NewState != DISABLE)
  {
    USARTx->MCR |= USART_HFCEN_ON;
  }
  else
  {
    USARTx->MCR &= USART_HFCEN_OFF;
  }
  #else
  if (NewState != DISABLE)
  {
    USARTx->CR |= USART_HFCEN_ON;
  }
  else
  {
    USARTx->CR &= USART_HFCEN_OFF;
  }
  #endif
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART IrDA interface.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_IrDACmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    USARTx->ICR |= USART_IRDA_ON;
  }
  else
  {
    USARTx->ICR &= USART_IRDA_OFF;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the USART IrDA interface.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_IrDAMode: Specify the USART IrDA mode.
 *   This parameter can be one of the following values:
 *     @arg USART_IRDA_LOWPOWER
 *     @arg USART_IRDA_NORMAL
 * @retval None
 ************************************************************************************************************/
void USART_IrDAConfig(HT_USART_TypeDef* USARTx, u32 USART_IrDAMode)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_IRDA_MODE(USART_IrDAMode));

  if (USART_IrDAMode != USART_IRDA_NORMAL)
  {
    USARTx->ICR |= USART_IRDA_LOWPOWER;
  }
  else
  {
    USARTx->ICR &= USART_IRDA_NORMAL;
  }
}

/*********************************************************************************************************//**
 * @brief Set the specified USART IrDA prescaler.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_IrDAPrescaler: Specify the USART IrDA prescaler.
 * @retval None
 ************************************************************************************************************/
void USART_SetIrDAPrescaler(HT_USART_TypeDef* USARTx, u32 USART_IrDAPrescaler)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_IRDA_PRESCALER(USART_IrDAPrescaler));

  USARTx->ICR = (USARTx->ICR & ICR_IRDAPSC_Mask) | (USART_IrDAPrescaler << 0x08);
}

/*********************************************************************************************************//**
 * @brief Enable the IrDA transmitter or receiver.
 * @param USARTx: Parameter to select the USART peripheral, x can be 0 or 1.
 * @param USART_IrDADirection: Specify the USART IrDA direction select.
 *   This parameter can be one of the following values:
 *     @arg USART_IRDA_TX
 *     @arg USART_IRDA_RX
 * @retval None
 ************************************************************************************************************/
void USART_IrDADirectionConfig(HT_USART_TypeDef* USARTx, u32 USART_IrDADirection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_IRDA_DIRECTION(USART_IrDADirection));

  if (USART_IrDADirection != USART_IRDA_RX)
  {
    USARTx->ICR |= USART_IRDA_TX;
  }
  else
  {
    USARTx->ICR &= USART_IRDA_RX;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable inverting serial output/input function of IrDA on the specified USART.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param inout: This parameter can be USART_CMD_OUT or USART_CMD_IN.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_IrDAInvtCmd(HT_USART_TypeDef* USARTx, u32 inout, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    USARTx->ICR |= (USART_INV_ON << inout);
  }
  else
  {
    USARTx->ICR &= ~(USART_INV_ON << inout);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the polarity of USART RS485 transmitter enable signal.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_RS485Polarity: Specify the polarity of USART RS485 Tx enable signal.
 *   This parameter can be one of the following values:
 *     @arg USART_RS485POL_LOW
 *     @arg USART_RS485POL_HIGH
 * @retval None
 ************************************************************************************************************/
void USART_RS485TxEnablePolarityConfig(HT_USART_TypeDef* USARTx, u32 USART_RS485Polarity)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_RS485_POLARITY(USART_RS485Polarity));

  if (USART_RS485Polarity != USART_RS485POLARITY_HIGH)
  {
    USARTx->RCR |= USART_RS485POLARITY_LOW;
  }
  else
  {
    USARTx->RCR &= USART_RS485POLARITY_HIGH;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART RS485 normal multi-drop operation mode.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_RS485NMMCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    USARTx->RCR |= USART_RS485NMM_ON;
  }
  else
  {
    USARTx->RCR &= USART_RS485NMM_OFF;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the USART RS485 normal multi-drop operation mode.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_RS485AADCmd(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    USARTx->RCR |= USART_RS485AAD_ON;
  }
  else
  {
    USARTx->RCR &= USART_RS485AAD_OFF;
  }
}

/*********************************************************************************************************//**
 * @brief Set the specified USART RS485 address match value.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_AddressMatchValue: specify the USART RS485 address match value.
 * @retval None
 ************************************************************************************************************/
void USART_SetAddressMatchValue(HT_USART_TypeDef* USARTx, u32 USART_AddressMatchValue)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_ADDRESS_MATCH_VALUE(USART_AddressMatchValue));

  USARTx->RCR = (USARTx->RCR & RS485CR_ADDM_Mask) | (u32)(USART_AddressMatchValue << 0x08);
}

/*********************************************************************************************************//**
 * @brief Initialize the clock of the USART peripheral according to the specified parameters
 *        in the USART_ClockInitStruct.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_SynClock_InitStruct: pointer to a USART_SynClock_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void USART_SynClockInit(HT_USART_TypeDef* USARTx, USART_SynClock_InitTypeDef* USART_SynClock_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_SYNCHRONOUS_CLOCK(USART_SynClock_InitStruct->USART_ClockEnable));
  Assert_Param(IS_USART_SYNCHRONOUS_PHASE(USART_SynClock_InitStruct->USART_ClockPhase));
  Assert_Param(IS_USART_SYNCHRONOUS_POLARITY(USART_SynClock_InitStruct->USART_ClockPolarity));
  Assert_Param(IS_USART_TRANSFER_MODE(USART_SynClock_InitStruct->USART_TransferSelectMode));

  USARTx->SCR = USART_SynClock_InitStruct->USART_ClockEnable | USART_SynClock_InitStruct->USART_ClockPhase |
                USART_SynClock_InitStruct->USART_ClockPolarity;

  #if (LIBCFG_USART_V01)
  USARTx->MDR = (USARTx->MDR & TRSM_CLEAR_Mask) | USART_SynClock_InitStruct->USART_TransferSelectMode;
  #else
  USARTx->CR = (USARTx->CR & TRSM_CLEAR_Mask) | USART_SynClock_InitStruct->USART_TransferSelectMode;
  #endif
}

/*********************************************************************************************************//**
 * @brief Fill each USART_SynClockInitStruct member with its default value.
 * @param USART_SynClock_InitStruct: pointer to a USART_SynClock_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void USART_SynClockStructInit(USART_SynClock_InitTypeDef* USART_SynClock_InitStruct)
{
  /* USART_ClockInitStruct members default value                                                            */
  USART_SynClock_InitStruct->USART_ClockEnable =  USART_SYN_CLOCK_DISABLE;
  USART_SynClock_InitStruct->USART_ClockPhase = USART_SYN_CLOCK_PHASE_FIRST;
  USART_SynClock_InitStruct->USART_ClockPolarity = USART_SYN_CLOCK_POLARITY_LOW;
  USART_SynClock_InitStruct->USART_TransferSelectMode = USART_LSB_FIRST;
}

#if (LIBCFG_USART_V01)
/*********************************************************************************************************//**
 * @brief Force pin DTR/RTS to low or high state.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param USART_ModemPin: Specify the USART modem pin to be forced.
 *   This parameter can be one of the following values:
 *         @arg USART_MODEM_DTR
 *         @arg USART_MODEM_RTS
 * @param USART_ModemState: the USART modem pin state.
 *   This parameter can be one of the following values:
 *         @arg USART_MODEMSTATE_HIGH
 *         @arg USART_MODEMSTATE_LOW
 * @retval None
 ************************************************************************************************************/
void USART_ForceModemPinState(HT_USART_TypeDef* USARTx, u32 USART_ModemPin, u32 USART_ModemState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_USART_MODEM_PIN(USART_ModemPin));
  Assert_Param(IS_USART_MODEM_STATE(USART_ModemState));

  if (USART_ModemState != USART_MODEMSTATE_HIGH)
  {
    USARTx->MCR |= USART_MODEMSTATE_LOW << USART_ModemPin;
  }
  else
  {
    USARTx->MCR &= ~(USART_MODEMSTATE_HIGH << USART_ModemPin);
  }
}

/*********************************************************************************************************//**
 * @brief Get Modem status.
 * @param USARTx: Parameter to select the USART peripheral.
 * @retval The current status of Modem Status Register.
 ************************************************************************************************************/
u8 USART_GetModemStatus(HT_USART_TypeDef* USARTx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));

  return (u8)(USARTx->MSR);
}

#if 0
/*********************************************************************************************************//**
 * @brief Enable or Disable time out interrupt of the USART.
 * @param USARTx: Parameter to select the USART peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void USART_TimeOutIntConfig(HT_USART_TypeDef* USARTx, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    USARTx->TPR |= USART_TIMEOUT_ON;
  }
  else
  {
    USARTx->TPR &= USART_TIMEOUT_OFF;
  }
}
#endif

/*********************************************************************************************************//**
 * @brief Get Interrupt ID value.
 * @param USARTx: Parameter to select the USART peripheral.
 * @retval The interrupt ID of USART.
 *          @arg USART_IID_RLS
 *          @arg USART_IID_RDA
 *          @arg USART_IID_CTI
 *          @arg USART_IID_THRE
 *          @arg USART_IID_MS
 *          @arg USART_IID_NON
 ************************************************************************************************************/
u8 USART_GetIntID(HT_USART_TypeDef* USARTx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));

  return (u8)(USARTx->IIR);
}

/*********************************************************************************************************//**
 * @brief Get Line Status Value.
 * @param USARTx: Parameter to select the USART peripheral.
 * @retval The vlaue of LSR.
 ************************************************************************************************************/
u32 USART_GetLineStatusValue(HT_USART_TypeDef* USARTx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_USART(USARTx));

  return (u8)(USARTx->LSR);
}
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

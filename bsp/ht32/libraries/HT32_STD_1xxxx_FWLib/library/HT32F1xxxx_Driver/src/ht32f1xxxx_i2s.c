/*********************************************************************************************************//**
 * @file    ht32f1xxxx_i2s.c
 * @version $Rev:: 2140         $
 * @date    $Date:: 2020-07-23 #$
 * @brief   This file provides all the I2S firmware functions.
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
#include "ht32f1xxxx_i2s.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup I2S I2S
  * @brief I2S driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup I2S_Private_Define I2S private definitions
  * @{
  */
#define I2S_EN          (1UL)
#define MCLK_OP_EN      (1UL << 9)
#define TX_MUTE_EN      (1UL << 12)
#define CLK_DIV_EN      (1UL << 15)
#define BCLK_INV_EN     (1UL << 18)
#define MCLK_INV_EN     (1UL << 19)

#define I2S_SLAVE       (1UL << 3)
/**
  * @}
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup I2S_Exported_Functions I2S exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the I2S peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void I2S_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.I2S = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the I2S peripheral according to the specified parameters in the I2S_InitStruct.
 * @param I2S_InitStruct: pointer to a I2S_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void I2S_Init(I2S_InitTypeDef* I2S_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  Assert_Param(IS_I2S_FORMAT(I2S_InitStruct->I2S_Format));
  Assert_Param(IS_I2S_WORD_WIDTH(I2S_InitStruct->I2S_WordWidth));
  Assert_Param(IS_I2S_MCLK_DIV(I2S_InitStruct->I2S_X_Div, I2S_InitStruct->I2S_Y_Div));
  Assert_Param(IS_I2S_BCLK_DIV(I2S_InitStruct->I2S_N_Div));

  HT_I2S->CR = I2S_InitStruct->I2S_Mode | I2S_InitStruct->I2S_Format | I2S_InitStruct->I2S_WordWidth;

  if (I2S_InitStruct->I2S_BclkInv == ENABLE)
  {
    HT_I2S->CR |= BCLK_INV_EN;
  }

  if (I2S_InitStruct->I2S_MclkInv == ENABLE)
  {
    HT_I2S->CR |= MCLK_INV_EN;
  }

  if ((I2S_InitStruct->I2S_Mode & I2S_SLAVE) == RESET)
  {
    HT_I2S->CDR = (I2S_InitStruct->I2S_N_Div << 16) | (I2S_InitStruct->I2S_X_Div << 8) |
                  (I2S_InitStruct->I2S_Y_Div);
    HT_I2S->CR |= CLK_DIV_EN;
    while (I2S_GetFlagStatus(I2S_FLAG_CLK_RDY) == RESET);

    if (I2S_InitStruct->I2S_MclkOut == ENABLE)
    {
      HT_I2S->CR |= MCLK_OP_EN;
    }
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the I2S peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2S_Cmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_I2S->CR |= I2S_EN;
  }
  else
  {
    HT_I2S->CR &= ~I2S_EN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the Tx mute for the I2S peripheral.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2S_TxMuteCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_I2S->CR |= TX_MUTE_EN;
  }
  else
  {
    HT_I2S->CR &= ~TX_MUTE_EN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the I2S PDMA interface.
 * @param I2S_PDMAREQ: specify the I2S PDMA transfer request to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg I2S_PDMAREQ_TX : Tx PDMA transfer request
 *     @arg I2S_PDMAREQ_RX : Rx PDMA transfer request
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2S_PDMACmd(u32 I2S_PDMAREQ, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_PDMA_REQ(I2S_PDMAREQ));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_I2S->CR |= I2S_PDMAREQ;
  }
  else
  {
    HT_I2S->CR &= I2S_PDMAREQ;
  }
}

/*********************************************************************************************************//**
 * @brief Reset the specified I2S FIFO.
 * @param I2S_FIFO: specify the FIFO that is to be reset.
 *   This parameter can be any combination of the following values:
 *     @arg I2S_TX_FIFO : I2S Tx FIFO
 *     @arg I2S_RX_FIFO : I2S Rx FIFO
 * @retval None
 ************************************************************************************************************/
void I2S_FIFOReset(u32 I2S_FIFO)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_TWO_FIFO(I2S_FIFO));

  HT_I2S->FCR |= I2S_FIFO;
}

/*********************************************************************************************************//**
 * @brief Set the trigger level of specified I2S FIFO.
 * @param I2S_FIFO: specify the FIFO that is to be set.
 *   This parameter can be any combination of the following values:
 *     @arg I2S_TX_FIFO : I2S Tx FIFO
 *     @arg I2S_RX_FIFO : I2S Rx FIFO
 * @param  I2S_FIFOLevel: Specify the FIFO trigger level.
 * @retval None
 ************************************************************************************************************/
void I2S_FIFOTrigLevelConfig(u32 I2S_FIFO, u32 I2S_FIFOLevel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_TWO_FIFO(I2S_FIFO));
  Assert_Param(IS_I2S_FIFO_LEVEL(I2S_FIFOLevel));

  if (I2S_FIFO == I2S_TX_FIFO)
  {
    HT_I2S->FCR = ((HT_I2S->FCR & (~0x0000000F)) | I2S_FIFOLevel);
  }
  else
  {
    HT_I2S->FCR = ((HT_I2S->FCR & (~0x000000F0)) | (I2S_FIFOLevel << 4));
  }
}

/*********************************************************************************************************//**
 * @brief Return the status of specified I2S FIFO.
 * @param I2S_FIFO: specify the FIFO that is to be checked.
 *   This parameter can be one of the following values:
 *     @arg I2S_TX_FIFO : I2S Tx FIFO
 *     @arg I2S_RX_FIFO : I2S Rx FIFO
 * @retval The number of data in specified I2S FIFO.
 ************************************************************************************************************/
u8 I2S_GetFIFOStatus(u32 I2S_FIFO)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_ONE_FIFO(I2S_FIFO));

  if (I2S_FIFO == I2S_TX_FIFO)
  {
    return (u8)((HT_I2S->SR >> 24) & 0x0F);
  }
  else
  {
    return (u8)(HT_I2S->SR >> 28);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the I2S interrupt.
 * @param I2S_Int: specify if the I2S interrupt source to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg I2S_INT_TXFIFO_TRI : I2S Tx FIFO trigger level interrupt
 *     @arg I2S_INT_TXFIFO_UF  : I2S Rx FIFO underflow interrupt
 *     @arg I2S_INT_TXFIFO_OV  : I2S Tx FIFO overflow interrupt
 *     @arg I2S_INT_RXFIFO_TRI : I2S Rx FIFO trigger level interrupt
 *     @arg I2S_INT_RXFIFO_UV  : I2S Rx FIFO underflow interrupt
 *     @arg I2S_INT_RXFIFO_OV  : I2S Rx FIFO overflow interrupt
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void I2S_IntConfig(u32 I2S_Int, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_INT(I2S_Int));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_I2S->IER |= I2S_Int;
  }
  else
  {
    HT_I2S->IER &= ~I2S_Int;
  }
}

/*********************************************************************************************************//**
 * @brief  Check whether the specified I2S flag has been set or not.
 * @param  I2S_Flag: specify the flag that is to be check.
 *   This parameter can be one of the following values:
 *     @arg I2S_FLAG_TXFIFO_TRI : I2S Tx FIFO trigger level flag
 *     @arg I2S_FLAG_TXFIFO_UDF : I2S Tx FIFO underflow flag
 *     @arg I2S_FLAG_TXFIFO_OVF : I2S Tx FIFO overflow flag
 *     @arg I2S_FLAG_TXFIFO_EMP : I2S Tx FIFO empty flag
 *     @arg I2S_FLAG_TXFIFO_FUL : I2S Tx FIFO full flag
 *     @arg I2S_FLAG_RXFIFO_TRI : I2S Rx FIFO trigger level flag
 *     @arg I2S_FLAG_RXFIFO_UDF : I2S Rx FIFO underflow flag
 *     @arg I2S_FLAG_RXFIFO_OVF : I2S Rx FIFO overflow flag
 *     @arg I2S_FLAG_RXFIFO_EMP : I2S Rx FIFO empty flag
 *     @arg I2S_FLAG_RXFIFO_FUL : I2S Rx FIFO full flag
 *     @arg I2S_FLAG_RIGHT_CH   : I2S right channel flag
 *     @arg I2S_FLAG_TX_BUSY    : I2S Tx busy flag
 *     @arg I2S_FLAG_CLK_RDY    : I2S clock ready flag
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus I2S_GetFlagStatus(u32 I2S_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_FLAG(I2S_Flag));

  if (HT_I2S->SR & I2S_Flag)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief  Clear the specified I2S flag.
 * @param  I2S_Flag: specify the flag that is to be cleared.
 *   This parameter can be any combination of the following values:
 *     @arg I2S_FLAG_TXFIFO_TRI : I2S Tx FIFO trigger level flag
 *     @arg I2S_FLAG_TXFIFO_UV  : I2S Tx FIFO underflow flag
 *     @arg I2S_FLAG_TXFIFO_OV  : I2S Tx FIFO overflow flag
 *     @arg I2S_FLAG_RXFIFO_TRI : I2S Rx FIFO trigger level flag
 *     @arg I2S_FLAG_RXFIFO_UV  : I2S Rx FIFO underflow flag
 *     @arg I2S_FLAG_RXFIFO_OV  : I2S Rx FIFO overflow flag
 * @retval None
 ************************************************************************************************************/
void I2S_ClearFlag(u32 I2S_Flag)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_I2S_FLAG_CLEAR(I2S_Flag));

  HT_I2S->SR = I2S_Flag;
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

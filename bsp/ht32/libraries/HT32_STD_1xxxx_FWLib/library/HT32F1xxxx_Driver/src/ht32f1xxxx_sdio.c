/*********************************************************************************************************//**
 * @file    ht32f1xxxx_sdio.c
 * @version $Rev:: 2459         $
 * @date    $Date:: 2021-08-13 #$
 * @brief   This file provides all the SDIO firmware functions.
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
#include "ht32f1xxxx_sdio.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @defgroup SDIO SDIO
  * @brief SDIO driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup SDIO_Exported_Functions SDIO exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the SDIO peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void SDIO_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.SDIO = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the SDIO peripheral according to the specified parameters in the SDIO_InitStruct.
 * @param SDIO_InitStruct: pointer to a SDIO_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SDIO_Init(SDIO_InitTypeDef* SDIO_InitStruct)
{
  u32 t;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_CLOC_DIV(SDIO_InitStruct->SDIO_ClockDiv));
  Assert_Param(IS_SDIO_CLOCK_PERIOD(SDIO_InitStruct->SDIO_ClockPeriod));
  Assert_Param(IS_SDIO_CLOCK_POWER_SAVE(SDIO_InitStruct->SDIO_ClockPowerSave));
  Assert_Param(IS_SDIO_BUS_WIDE(SDIO_InitStruct->SDIO_BusWide));
  Assert_Param(IS_SDIO_BUS_MODE(SDIO_InitStruct->SDIO_BusMode));

  /* Disable the SDIO clock and wait for a while                                                            */
  SDIO_ClockCmd(DISABLE);
  for (t = 500; t > 0; t--);

  /* Configure SDIO bus and clock                                                                           */
  HT_SDIO->CR = SDIO_InitStruct->SDIO_BusWide | SDIO_InitStruct->SDIO_BusMode;

  HT_SDIO->CLKCR = SDIO_InitStruct->SDIO_ClockPeriod | SDIO_InitStruct->SDIO_ClockPowerSave |
                   ((SDIO_InitStruct->SDIO_ClockDiv - 1) << 8);

  /* Enable SDIO bus clock                                                                                  */
  SDIO_ClockCmd(ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or disable the SDIO Clock.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SDIO_ClockCmd(ControlStatus Cmd)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(Cmd));

  if (Cmd != DISABLE)
  {
    BitBand((u32)&HT_SDIO->CLKCR, 2) = Cmd;
  }
  else
  {
    BitBand((u32)&HT_SDIO->CLKCR, 2) = Cmd;
  }
}

/*********************************************************************************************************//**
 * @brief Initialize the SDIO command according to the specified parameters in the SDIO_CmdInitStruct.
 * @param SDIO_CmdInitStruct: pointer to a SDIO_CmdInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SDIO_SendCommand(SDIO_CmdInitTypeDef *SDIO_CmdInitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_CMD_INDEX(SDIO_CmdInitStruct->SDIO_CmdIndex));
  Assert_Param(IS_SDIO_RESPONSE(SDIO_CmdInitStruct->SDIO_Response));
  Assert_Param(IS_SDIO_DATA_PRESENT(SDIO_CmdInitStruct->SDIO_DatPresent));
  Assert_Param(IS_SDIO_CMD_IDX_CHK(SDIO_CmdInitStruct->SDIO_CmdIdxChk));
  Assert_Param(IS_SDIO_CMD_CRC_CHK(SDIO_CmdInitStruct->SDIO_CmdCrcChk));

  HT_SDIO->ARG = SDIO_CmdInitStruct->SDIO_Argument;

  HT_SDIO->CMD = SDIO_CmdInitStruct->SDIO_CmdIndex   | SDIO_CmdInitStruct->SDIO_Response  |
                 SDIO_CmdInitStruct->SDIO_DatPresent | SDIO_CmdInitStruct->SDIO_CmdIdxChk |
                 SDIO_CmdInitStruct->SDIO_CmdCrcChk;
}

/*********************************************************************************************************//**
 * @brief Return response received from the card for the last command.
 * @param SDIO_RESP: Specify the SDIO response register.
 *   This parameter can be one of the following values:
 *     @arg SDIO_RESP1 : Response Register 1
 *     @arg SDIO_RESP2 : Response Register 2
 *     @arg SDIO_RESP3 : Response Register 3
 *     @arg SDIO_RESP4 : Response Register 4
 * @retval The Corresponding response register value.
 ************************************************************************************************************/
u32 SDIO_GetResponse(u32 SDIO_RESP)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_RESP(SDIO_RESP));

  return(rw((u32)&HT_SDIO->RESP0 + SDIO_RESP));
}

/*********************************************************************************************************//**
 * @brief Initialize the SDIO data path according to the specified parameters in the SDIO_DataInitStruct.
 * @param SDIO_DataInitStruct: pointer to a SDIO_DataInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void SDIO_DataConfig(SDIO_DataInitTypeDef* SDIO_DataInitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_DATA_BLOCK_COUNT(SDIO_DataInitStruct->SDIO_DataBlockCount));
  Assert_Param(IS_SDIO_DATA_BLOCK_SIZE(SDIO_DataInitStruct->SDIO_DataBlockSize));
  Assert_Param(IS_SDIO_TRANSFER_MODE(SDIO_DataInitStruct->SDIO_TransferMode));
  Assert_Param(IS_SDIO_TRANSFER_DIR(SDIO_DataInitStruct->SDIO_TransferDir));
  Assert_Param(IS_SDIO_DATA_TIMEOUT(SDIO_DataInitStruct->SDIO_DataTimeOut));

  /* configure DPSM                                                                                         */
  RESET_DPSM();
  HT_SDIO->BLKCNT  = SDIO_DataInitStruct->SDIO_DataBlockCount;
  HT_SDIO->BLKSIZE = SDIO_DataInitStruct->SDIO_DataBlockSize;
  HT_SDIO->TMR     = SDIO_DataInitStruct->SDIO_TransferMode | SDIO_DataInitStruct->SDIO_TransferDir;
  HT_SDIO->TMOCR   = SDIO_DataInitStruct->SDIO_DataTimeOut;
}

/*********************************************************************************************************//**
 * @brief Read one data word from FIFO.
 * @return Data received
 ************************************************************************************************************/
u32 SDIO_ReadData(void)
{
  return HT_SDIO->DR;
}

/*********************************************************************************************************//**
 * @brief Write one data word to FIFO.
 * @param Data: 32-bit data word to write.
 * @retval None
 ************************************************************************************************************/
void SDIO_WriteData(u32 Data)
{
  HT_SDIO->DR = Data;
}

/*********************************************************************************************************//**
 * @brief Return the number of words left to be written to or read from FIFO.
 * @return Remaining number of words.
 ************************************************************************************************************/
u32 SDIO_GetFIFOCount(void)
{
  return (HT_SDIO->PSR >> 20);
}

/*********************************************************************************************************//**
 * @brief Enable the SDIO's flag.
 * @param SDIO_FLAG: specify the flag to enable.
 *   This parameter can be one of the following values:
 *     @arg SDIO_FLAG_CMD_SEND      :
 *     @arg SDIO_FLAG_TRANS_END     :
 *     @arg SDIO_FLAG_BUF_OVERFLOW  :
 *     @arg SDIO_FLAG_BUF_UNDERFLOW :
 *     @arg SDIO_FLAG_BUF_HALF      :
 *     @arg SDIO_FLAG_BUF_FULL      :
 *     @arg SDIO_FLAG_BUF_EMPTY     :
 *     @arg SDIO_FLAG_CMD_TIMEOUT   :
 *     @arg SDIO_FLAG_CMD_CRCERR    :
 *     @arg SDIO_FLAG_CMD_IDXERR    :
 *     @arg SDIO_FLAG_DATA_TIMEOUT  :
 *     @arg SDIO_FLAG_DATA_CRCERR   :
 *     @arg SDIO_FLAG_CARD_INT      :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void SDIO_FlagConfig(u32 SDIO_FLAG, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_FLAG(SDIO_FLAG));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_SDIO->SER |= (SDIO_FLAG);
  }
  else
  {
    HT_SDIO->SER &= ~(SDIO_FLAG);
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified SDIO flag is set or not.
 * @param SDIO_FLAG: specify the flag to check.
 *   This parameter can be one of the following values:
 *     @arg SDIO_FLAG_CMD_SEND      :
 *     @arg SDIO_FLAG_TRANS_END     :
 *     @arg SDIO_FLAG_BUF_OVERFLOW  :
 *     @arg SDIO_FLAG_BUF_UNDERFLOW :
 *     @arg SDIO_FLAG_BUF_HALF      :
 *     @arg SDIO_FLAG_BUF_FULL      :
 *     @arg SDIO_FLAG_BUF_EMPTY     :
 *     @arg SDIO_FLAG_CMD_TIMEOUT   :
 *     @arg SDIO_FLAG_CMD_CRCERR    :
 *     @arg SDIO_FLAG_CMD_IDXERR    :
 *     @arg SDIO_FLAG_DATA_TIMEOUT  :
 *     @arg SDIO_FLAG_DATA_CRCERR   :
 *     @arg SDIO_FLAG_CARD_INT      :
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus SDIO_GetFlagStatus(u32 SDIO_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_FLAG(SDIO_FLAG));

  if (HT_SDIO->SR & (SDIO_FLAG))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear the SDIO's pending flags.
 * @param SDIO_FLAG: specify the flag to clear.
 *   This parameter can be one of the following values:
 *     @arg SDIO_FLAG_CMD_SEND      :
 *     @arg SDIO_FLAG_TRANS_END     :
 *     @arg SDIO_FLAG_BUF_OVERFLOW  :
 *     @arg SDIO_FLAG_BUF_UNDERFLOW :
 *     @arg SDIO_FLAG_BUF_HALF      :
 *     @arg SDIO_FLAG_BUF_FULL      :
 *     @arg SDIO_FLAG_BUF_EMPTY     :
 *     @arg SDIO_FLAG_ERR           :
 *     @arg SDIO_FLAG_CMD_TIMEOUT   :
 *     @arg SDIO_FLAG_CMD_CRCERR    :
 *     @arg SDIO_FLAG_CMD_ENDERR    :
 *     @arg SDIO_FLAG_CMD_IDXERR    :
 *     @arg SDIO_FLAG_DATA_TIMEOUT  :
 *     @arg SDIO_FLAG_DATA_CRCERR   :
 *     @arg SDIO_FLAG_DATA_ENDERR   :
 *     @arg SDIO_FLAG_CARD_INT      :
 *     @arg SDIO_FLAG_DAT_ERR       :
 *     @arg SDIO_FLAG_CMD_ERR       :
 * @retval SET or RESET
 ************************************************************************************************************/
void SDIO_ClearFlag(u32 SDIO_FLAG)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_FLAG(SDIO_FLAG));

  HT_SDIO->SR = (SDIO_FLAG);

  if (SDIO_FLAG & SDIO_FLAG_BUF_OVERFLOW)
  {
    HT_SDIO->SER &= ~(SDIO_FLAG_BUF_OVERFLOW);
    HT_SDIO->SER |= (SDIO_FLAG_BUF_OVERFLOW);
  }
  if (SDIO_FLAG & SDIO_FLAG_BUF_UNDERFLOW)
  {
    HT_SDIO->SER &= ~(SDIO_FLAG_BUF_UNDERFLOW);
    HT_SDIO->SER |= (SDIO_FLAG_BUF_UNDERFLOW);
  }
}

/*********************************************************************************************************//**
 * @brief Clear the SDIO's pending flags.
 * @param SDIO_INT: specify the flag to clear.
 *   This parameter can be one of the following values:
 *     @arg SDIO_INT_CMD_SEND      :
 *     @arg SDIO_INT_TRANS_END     :
 *     @arg SDIO_INT_BUF_OVERFLOW  :
 *     @arg SDIO_INT_BUF_UNDERFLOW :
 *     @arg SDIO_INT_BUF_HALF      :
 *     @arg SDIO_INT_BUF_FULL      :
 *     @arg SDIO_INT_BUF_EMPTY     :
 *     @arg SDIO_INT_CMD_TIMEOUT   :
 *     @arg SDIO_INT_CMD_CRCERR    :
 *     @arg SDIO_INT_CMD_IDXERR    :
 *     @arg SDIO_INT_DATA_TIMEOUT  :
 *     @arg SDIO_INT_DATA_CRCERR   :
 *     @arg SDIO_INT_CARD_INT      :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval SET or RESET
 ************************************************************************************************************/
void SDIO_IntConfig(u32 SDIO_INT, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_SDIO_INT(SDIO_INT));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_SDIO->IER |= (SDIO_INT);
  }
  else
  {
    HT_SDIO->IER &= ~(SDIO_INT);
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

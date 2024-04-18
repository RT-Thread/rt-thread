/*********************************************************************************************************//**
 * @file    ht32f5xxxx_aes.c
 * @version $Rev:: 7390         $
 * @date    $Date:: 2023-12-12 #$
 * @brief   This file provides all the ADC firmware functions.
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
#include "ht32f5xxxx_aes.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup AES AES
  * @brief AES driver modules
  * @{
  */


/* Global variables ----------------------------------------------------------------------------------------*/
u32 *gpu32OutputBuff;
u32 gu32OutputIndex = 0;

u32 *gpu32InputBuff;
u32 gu32InputSize = 0;
u32 gu32InputIndex = 0;

/* Private functions ---------------------------------------------------------------------------------------*/
static void _AES_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct);

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup AES_Exported_Functions AES exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the AES peripheral registers to their default reset values.
 * @param  HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @retval None
 ************************************************************************************************************/
void AES_DeInit(HT_AES_TypeDef* HT_AESn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  if (HT_AESn == NULL) // Remove the compiler warning
  {
  }

  RSTCUReset.Bit.AES = 1;
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Flush the FIFO.
 * @param  HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @retval None
 ************************************************************************************************************/
void AES_FIFOFlush(HT_AES_TypeDef* HT_AESn)
{
  AES_Cmd(HT_AESn, DISABLE);
  HT_AESn->CR |= AES_FLUSH_ENABLE;
  AES_Cmd(HT_AESn, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified AES.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void AES_Cmd(HT_AES_TypeDef* HT_AESn, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_AESn->CR |= AES_ENABLE;
  }
  else
  {
    HT_AESn->CR &= ~AES_ENABLE;
  }
}

/*********************************************************************************************************//**
 * @brief Start the AES key.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @retval None
 ************************************************************************************************************/
void AES_StartKey(HT_AES_TypeDef* HT_AESn)
{
  HT_AESn->CR |= (1 << 4);
}

/*********************************************************************************************************//**
 * @brief Initialize the AES peripheral according to the specified parameters in the AES_InitStruct.
 * @param HT_AESn: where AES is the selected AES peripheral.
 * @param AES_InitStruct: pointer to a AES_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void _AES_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_AES_KEY_SIZE(AES_InitStruct->AES_KeySize));
  Assert_Param(IS_AES_DIR(AES_InitStruct->AES_Dir));
  Assert_Param(IS_AES_MODE(AES_InitStruct->AES_Mode));
  Assert_Param(IS_AES_SWAP(AES_InitStruct->AES_Swap));

  HT_AESn->CR = (HT_AESn->CR & 0xFFFFFE81) | AES_InitStruct->AES_KeySize |
                 AES_InitStruct->AES_Dir | AES_InitStruct->AES_Mode |
                 AES_InitStruct->AES_Swap;

  AES_Cmd(HT_AESn, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Initialize the AES peripheral on ECB mode according to the specified parameters in the AES_InitStruct.
 * @param HT_AESn: where AES is the selected AES peripheral.
 * @param AES_InitStruct: pointer to a AES_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void AES_ECB_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct)
{
  AES_InitStruct->AES_Mode = AES_MODE_ECB;
  _AES_Init(HT_AESn, AES_InitStruct);

  AES_IntConfig(HT_AESn, AES_IER_OFINTEN, ENABLE);
  NVIC_EnableIRQ(AES_IRQn);
}

/*********************************************************************************************************//**
 * @brief Initialize the AES peripheral on CBC mode according to the specified parameters in the AES_InitStruct.
 * @param HT_AESn: where AES is the selected AES peripheral.
 * @param AES_InitStruct: pointer to a AES_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void AES_CBC_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct)
{
  AES_InitStruct->AES_Mode = AES_MODE_CBC;
  _AES_Init(HT_AESn, AES_InitStruct);

  AES_IntConfig(HT_AESn, AES_IER_OFINTEN, ENABLE);
  NVIC_EnableIRQ(AES_IRQn);
}

/*********************************************************************************************************//**
 * @brief Initialize the AES peripheral on CTR mode according to the specified parameters in the AES_InitStruct.
 * @param HT_AESn: where HT_AESn is the selected AES peripheral.
 * @param AES_InitStruct: pointer to a AES_InitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void AES_CTR_Init(HT_AES_TypeDef* HT_AESn, AES_InitTypeDef* AES_InitStruct)
{
  AES_InitStruct->AES_Mode = AES_MODE_CTR;
  _AES_Init(HT_AESn, AES_InitStruct);

  AES_IntConfig(HT_AESn, AES_IER_OFINTEN, ENABLE);
  NVIC_EnableIRQ(AES_IRQn);
}

/*********************************************************************************************************//**
 * @brief Check whether the specified AES status has been set.
 * @param HT_AESn: where HT_AESn is the selected AES peripheral.
 * @param AES_SR_x: specify the flag to be check.
 *   This parameter can be one of the following values:
 *     @arg AES_SR_IFEMPTY  : AES Input FIFO is Empty
 *     @arg AES_SR_IFNFULL  : AES Input FIFO is not Full
 *     @arg AES_SR_OFNEMPTY : AES Output FIFO is not Empty
 *     @arg AES_SR_OFFULL   : AES Output FIFO is Full
 *     @arg AES_SR_BUSY     : AES is busy when AES is in encrypt/decrypt action and key expansion
 * @retval SET or RESET
 ************************************************************************************************************/
FlagStatus AES_GetStatus(HT_AES_TypeDef* HT_AESn, u32 AES_SR_x)
{
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_AES_STATUS(AES_SR_x));

  if ((HT_AESn->SR & AES_SR_x) != (u32)RESET)
  {
    return (SET);
  }
  else
  {
    return (RESET);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the AES PDMA interface.
 * @param HT_AESn: where HT_AESn is the selected HT_AESn peripheral.
 * @param AES_PDMA_xFDMAEN: specify the AES FIFO DMA to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg AES_PDMA_IFDMAEN : input FIFO PDMA
 *     @arg AES_PDMA_OFDMAEN : Output FIFO PDMA
 * @param  NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void AES_PDMACmd(HT_AES_TypeDef* HT_AESn, u32 AES_PDMA_xFDMAEN, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_AESn->PDMAR |= AES_PDMA_xFDMAEN;
  }
  else
  {
    HT_AESn->PDMAR &= ~AES_PDMA_xFDMAEN;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified AES interrupt has occurred.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @param AES_INTSR_x: Specify the interrupt status to check.
 *   This parameter can be any combination of the following values:
 *     @arg AES_INTSR_IFINT :
 *     @arg AES_INTSR_OFINT :
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus AES_GetIntStatus(HT_AES_TypeDef* HT_AESn, u32 AES_INTSR_x)
{
  FlagStatus Status;
  u32 aes_isr = HT_AESn->ISR;
  u32 aes_ier = HT_AESn->IER;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_AES_INTSR(AES_INTSR_x));

  Status = (FlagStatus)(aes_isr & aes_ier);
  if ((Status & AES_INTSR_x) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified AES interrupts.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @param AES_IER_x: Specify the AES interrupt sources that is to be enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg AES_IER_IFINTEN :
 *     @arg AES_IER_OFINTEN :
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void AES_IntConfig(HT_AES_TypeDef* HT_AESn, u32 AES_IER_x, ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_AES(HT_AESn));
  Assert_Param(IS_AES_IER(AES_IER_x));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    HT_AESn->IER |= AES_IER_x;
  }
  else
  {
    HT_AESn->IER &= ~AES_IER_x;
  }
}

/*********************************************************************************************************//**
 * @brief Set the specified AES Input data.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @param AES_Data: Data input
 * @retval None
 ************************************************************************************************************/
void AES_SetInputData(HT_AES_TypeDef* HT_AESn, uc32 AES_Data)
{
  Assert_Param(IS_AES(HT_AESn));
  #if (LIBCFG_AES_SWAP)
  HT_AESn->DINR = __REV(AES_Data);
  #else
  HT_AESn->DINR = AES_Data;
  #endif
}

/*********************************************************************************************************//**
 * @brief Get the specified AES output data.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @retval Output Data
 ************************************************************************************************************/
u32 AES_GetOutputData(HT_AES_TypeDef* HT_AESn)
{
  Assert_Param(IS_AES(HT_AESn));
  #if (LIBCFG_AES_SWAP)
  return __REV(HT_AESn->DOUTR);
  #else
  return HT_AESn->DOUTR;
  #endif
}

/*********************************************************************************************************//**
 * @brief Set the specified AES key table.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @param Key: Key table
 * @param keySize: Key table's size
 * @retval None
 ************************************************************************************************************/
void AES_SetKeyTable(HT_AES_TypeDef* HT_AESn, u32 *Key, u32 keySize)
{
  u32 i;
  u32 uCRTemp = HT_AESn->CR & (~(0x00000060UL));
  if (keySize == 128/8)
  {
    uCRTemp |= AES_KEYSIZE_128B;
  }
  #if (LIBCFG_AES_KEYSIZE_256B)
  else if (keySize == 192/8)
  {
    uCRTemp |= AES_KEYSIZE_192B;
  }
  else if (keySize == 256/8)
  {
    uCRTemp |= AES_KEYSIZE_256B;
  }
  #endif
  else
  {
    return;
  }
  HT_AESn->CR = uCRTemp;

  for (i = 0; i < keySize; i += 4)
  {
    #if (LIBCFG_AES_SWAP)
    HT_AESn->KEYR[i >> 2] = __REV(*&Key[i]);
    #else
    HT_AESn->KEYR[i >> 2] = *&Key[i];
    #endif
  }

  AES_StartKey(HT_AES);
}

/*********************************************************************************************************//**
 * @brief Set the specified AES Vector table.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @param Vector:
 * @retval None
 ************************************************************************************************************/
void AES_SetVectorTable(HT_AES_TypeDef* HT_AESn, u32 *Vector)
{
  int i;
  Assert_Param(IS_AES(HT_AESn));

  for (i = 0; i < 16; i += 4)
  {
    #if (LIBCFG_AES_SWAP)
    HT_AESn->IVR[i >> 2] = __REV(*&Vector[i]);
    #else
    HT_AESn->IVR[i >> 2] = *&Vector[i];
    #endif
  }
}

/*********************************************************************************************************//**
 * @brief AES Crypt Data
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @param dir: Crypt Data's direction
 * @param iv: initial vector table
 * @param length: data size
 * @param inputData: InputData
 * @param outputData: Output Data
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus _AES_CryptData(HT_AES_TypeDef* HT_AESn,
                         AES_DIR_Enum dir,
                         u32 *iv,
                         u32 length,
                         u32 *inputData,
                         u32 *outputData)
{
  /*AES Data blocks 16 byte                                                                                 */
  if ((length % 16) != 0)
  {
    /* Data size can not be divisible by 16.                                                                */
    return ERROR;
  }

  /*Set inital Vector                                                                                       */
  if (iv != NULL)
  {
    AES_SetVectorTable(HT_AESn, iv);
  }

  /*FIFO Flush                                                                                              */
  AES_FIFOFlush(HT_AES);

  /*Set direction                                                                                           */
  HT_AESn->CR = (HT_AESn->CR & 0xFFFFFFFD) | dir;

  /*Create input/output data                                                                                */
  gpu32InputBuff = inputData;
  gpu32OutputBuff = outputData;

  /*Init Index                                                                                              */
  gu32OutputIndex = 0;
  gu32InputSize  = length/4;

  /*Set input data                                                                                          */
  AES_IntConfig(HT_AES, AES_IER_IFINTEN, ENABLE);

  /*Waitting for conversion                                                                                 */
  while (AES_GetStatus(HT_AES, AES_SR_OFNEMPTY));
  return SUCCESS;
}

#if 0
/*********************************************************************************************************//**
 * @brief AES Crypt Data on ECB mode
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @param dir: Crypt Data's direction
 * @param length: data size
 * @param inputData: InputData
 * @param outputData: Output Data
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus AES_ECB_CryptData(HT_AES_TypeDef* HT_AESn,
                       AES_DIR_Enum dir,
                       u32 length,
                       u32 *inputData,
                       u32 *outputData)
{
  return _AES_CryptData(HT_AESn,
                        dir,
                        NULL,
                        length,
                        inputData,
                        outputData);
}

/*********************************************************************************************************//**
 * @brief AES Crypt Data on CBC mode
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @param dir: Crypt Data's direction
 * @param iv: initial vector table
 * @param length: data size
 * @param inputData: InputData
 * @param outputData: Output Data
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus AES_CBC_CryptData(HT_AES_TypeDef* HT_AESn,
                       AES_DIR_Enum dir,
                       u32 *iv,
                       u32 length,
                       u32 *inputData,
                       u32 *outputData)
{
  return _AES_CryptData(HT_AESn,
                        dir,
                        iv,
                        length,
                        inputData,
                        outputData);
}

/*********************************************************************************************************//**
 * @brief AES Crypt Data on CTR mode
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals
 * @param iv: initial vector table
 * @param length: data size
 * @param inputData: InputData
 * @param outputData: Output Data
 * @retval SUCCESS or ERROR
 ************************************************************************************************************/
ErrStatus AES_CTR_CryptData(HT_AES_TypeDef* HT_AESn,
                       u32 *iv,
                       u32 length,
                       u32 *inputData,
                       u32 *outputData)
{
  return _AES_CryptData(HT_AESn,
                        AES_DIR_ENCRYPT,
                        iv,
                        length,
                        inputData,
                        outputData);
}
#endif

/*********************************************************************************************************//**
 * @brief This function handles AES Core interrupt.
 * @param HT_AESn: where HT_AESn is the selected AES from the AES peripherals.
 * @retval None
 ************************************************************************************************************/
void AESCore_IRQHandler(HT_AES_TypeDef* HT_AESn)
{
  if (AES_GetIntStatus(HT_AES, AES_INTSR_OFINT))
  {
    gpu32OutputBuff[gu32OutputIndex++] = AES_GetOutputData(HT_AES);
  }
  if (AES_GetIntStatus(HT_AES, AES_INTSR_IFINT))
  {
    if (gu32InputIndex < gu32InputSize)
    {
      AES_SetInputData(HT_AES, gpu32InputBuff[gu32InputIndex]);
      gu32InputIndex++;
    }
    else
    {
      AES_IntConfig(HT_AES, AES_IER_IFINTEN, DISABLE);
      gu32InputIndex = 0;
    }
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

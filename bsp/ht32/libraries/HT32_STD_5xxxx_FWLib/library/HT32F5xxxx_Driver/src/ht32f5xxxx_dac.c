/*********************************************************************************************************//**
 * @file    ht32f5xxxx_dac.c
 * @version $Rev:: 7081         $
 * @date    $Date:: 2023-08-01 #$
 * @brief   This file provides all the DAC firmware functions.
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
#include "ht32f5xxxx_dac.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup DAC DAC
  * @brief DAC driver modules
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Functions DAC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the HT_DACn peripheral registers to their default reset values.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @retval None
 ************************************************************************************************************/
void DAC_DeInit(HT_DAC_TypeDef* HT_DACn)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));

  if (HT_DACn == HT_DAC0)
  {
    RSTCUReset.Bit.DAC0 = 1;
  }
  #if (LIBCFG_DAC1)
  else if (HT_DACn == HT_DAC1)
  {
    RSTCUReset.Bit.DAC1 = 1;
  }
  #endif
  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure the DAC conversion mode.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param ModeSel: specify the conversion mode
 *   This parameter can be one of the following values:
 *     @arg ASYNC_MODE : asynchronous conversion mode
 *     @arg SYNC_MODE  : synchronous conversion mode
 * @retval None
 ************************************************************************************************************/
void DAC_ModeConfig(HT_DAC_TypeDef* HT_DACn, u8 ModeSel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CONVERSION_MODE(ModeSel));

  HT_DACn->CFGR = ModeSel;
}

/*********************************************************************************************************//**
 * @brief Configure the specified DAC channel reference voltage.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param RefSel: DAC reference voltage source
 *   This parameter can be one of the following values:
 *     @arg DAC_REFERENCE_VDDA : VDDA
 *     @arg DAC_REFERENCE_VREF : VREF
 * @retval None
 ************************************************************************************************************/
void DAC_ReferenceConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 RefSel)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_DAC_REFERENCE(RefSel));

  DACnCH->CR = (DACnCH->CR & ~(3UL << 14)) | RefSel;
}

/*********************************************************************************************************//**
 * @brief Configure the specified DAC channel resolution.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param ResoSel: DAC Channel Resolution
 *   This parameter can be one of the following values:
 *     @arg DAC_RESOLUTION_8BIT  : 8-bit resolution
 *     @arg DAC_RESOLUTION_12BIT : 12-bit resolution
 * @retval None
 ************************************************************************************************************/
void DAC_ResolutionConfig(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 ResoSel)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_DAC_RESOLUTION(ResoSel));

  DACnCH->CR = (DACnCH->CR & ~(1UL << 2)) | ResoSel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC Channel output buffer.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_OutBufCmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    DACnCH->CR = (DACnCH->CR & ~(3UL << 6)) | (2UL << 6);
  }
  else
  {
    DACnCH->CR = (DACnCH->CR & ~(3UL << 6)) | (1UL << 6);
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void DAC_Cmd(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, ControlStatus NewState)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    SetBit_BB((u32)&DACnCH->CR, 0);
  }
  else
  {
    ResetBit_BB((u32)&DACnCH->CR, 0);
  }
}

/*********************************************************************************************************//**
 * @brief Set the data holding register value for the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @param Data: next conversion data.
 * @retval None
 ************************************************************************************************************/
void DAC_SetData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch, u32 Data)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));

  DACnCH->DHR = Data;
}

/*********************************************************************************************************//**
 * @brief Return the data output register value of the specified DAC channel.
 * @param HT_DACn: where HT_DACn is the selected DAC from the DAC peripherals.
 * @param DAC_Ch: the DAC channel to configure
*   This parameter can be one of the following values:
*     @arg DAC_CH0 : DAC channel 0
*     @arg DAC_CH1 : DAC channel 1
 * @return The selected DAC channel data output value.
 ************************************************************************************************************/
u16 DAC_GetOutData(HT_DAC_TypeDef* HT_DACn, u8 DAC_Ch)
{
  HT_DACCH_TypeDef *DACnCH = (HT_DACCH_TypeDef *)((u32)&HT_DACn->DACCH0 + DAC_Ch * 8 * 4);

  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(HT_DACn));
  Assert_Param(IS_DAC_CHANNEL(DAC_Ch));

  return ((u16)DACnCH->DOR);
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

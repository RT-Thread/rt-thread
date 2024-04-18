/*********************************************************************************************************//**
 * @file    ht32f5xxxx_dac_dual16.c
 * @version $Rev:: 7071         $
 * @date    $Date:: 2023-07-28 #$
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
#include "ht32f5xxxx_dac_dual16.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @defgroup DAC_DUAL16 DAC_DUAL16
  * @brief DAC driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup DAC_DUAL16_Private_Define DAC private definitions
  * @{
  */
#define DAC_POS_RCH                         0
#define DAC_POS_LCH                         8

#define DAC_TRIG_SOFTWARE_RESET            (0x00000000)
#define DAC_TRIG_SOFTWARE_SET              (0x00000001)

#define DAC_RCH_RESET                      (0xFFFFFFFE)
#define DAC_LCH_RESET                      (0xFFFFFEFF)
/**
  * @}
  */

/* Private macro -------------------------------------------------------------------------------------------*/
/** @defgroup DAC_DUAL16_Private_Macro DAC private macros
  * @{
  */
#define IS_DAC(x)                           (x == HT_DACDUAL16)

#define IS_DAC_CHANNEL(CHANNEL)             (((CHANNEL) == DAC_CH_R)   || \
                                             ((CHANNEL) == DAC_CH_L))

#define IS_DAC_DATA_SOURCE(SOURCE)          (((SOURCE) == DATA_FROM_UC)   || \
                                             ((SOURCE) == DATA_FROM_MIDI))

#define IS_DAC_DATA(DATA)                   ((DATA) <= 0xFFFF)
/**
  * @}
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup DAC_DUAL16_Exported_Functions DAC exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitialize the DAC peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void DACD16_DeInit(void)
{
  RSTCU_PeripReset_TypeDef RSTCUReset = {{0}};

  RSTCUReset.Bit.DAC0 = 1;

  RSTCU_PeripReset(RSTCUReset, ENABLE);
}

/*********************************************************************************************************//**
 * @brief  Configure the data source for the DAC channel.
 * @param  DACx: where DACx is the selected DAC from the DAC peripherals.
 * @param  DAC_CH_x: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH_R : DAC Right Channel selected
 *     @arg DAC_CH_L : DAC Left  Channel selected
 * @param  DATA_FROM_x: Configure the data source.
 *   This parameter can be one of the following values:
 *     @arg DATA_FROM_UC    : data and control signal from uC
 *     @arg DATA_FROM_MIDI  : data and control signal from MIDI
 * @retval None
 ************************************************************************************************************/
void DACD16_DataSourceConfig(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x, DAC_Dual16_Source DATA_FROM_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(DACx));
  Assert_Param(IS_DAC_CHANNEL(DAC_CH_x));
  Assert_Param(IS_DAC_DATA_SOURCE(DATA_FROM_x));

  /* Set the select channel data source                                                                     */
  if (DAC_CH_x == DAC_CH_R)
  {
    DACx->CR &= DAC_RCH_RESET;
    DACx->CR |= DATA_FROM_x << DAC_POS_RCH;
  }
  else
  {
    DACx->CR &= DAC_LCH_RESET;
    DACx->CR |= DATA_FROM_x << DAC_POS_LCH;
  }
}

/*********************************************************************************************************//**
 * @brief  Configure the data source for the DAC channel.
 * @param  DACx: where DACx is the selected DAC from the DAC peripherals.
 * @param  DAC_CH_x: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH_R : DAC Right Channel selected
 *     @arg DAC_CH_L : DAC Left  Channel selected
 * @param  Data : Data to be loaded in the selected channel data register.
 * @retval None
 ************************************************************************************************************/
void DACD16_SetChannelData(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x, u16 Data)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(DACx));
  Assert_Param(IS_DAC_CHANNEL(DAC_CH_x));
  Assert_Param(IS_DAC_DATA(Data));

  /* Set the select channel data                                                                            */
  if (DAC_CH_x == DAC_CH_R)
  {
    DACx->RH = Data;
  }
  else
  {
    DACx->LH = Data;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the channel conversion of the selected DAC .
 * @param  DACx: where DACx is the selected DAC from the DAC peripherals.
 * @param  DAC_CH_x: the DAC channel to configure
 *   This parameter can be one of the following values:
 *     @arg DAC_CH_R : DAC Right Channel selected
 *     @arg DAC_CH_L : DAC Left  Channel selected
 * @retval None
 ************************************************************************************************************/
void DACD16_SoftwareStartConvCmd(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_DAC(DACx));
  Assert_Param(IS_DAC_CHANNEL(DAC_CH_x));

  /* Start Conversion                                                                                       */
  if (DAC_CH_x == DAC_CH_R)
  {
      DACx->TG &= DAC_RCH_RESET ;
      DACx->TG |= DAC_TRIG_SOFTWARE_SET << DAC_POS_RCH;
  }
  else
  {
      DACx->TG &= DAC_LCH_RESET;
      DACx->TG |= DAC_TRIG_SOFTWARE_SET << DAC_POS_LCH;
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

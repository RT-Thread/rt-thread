/*********************************************************************************************************//**
 * @file    ht32f5xxxx_dac_dual16.h
 * @version $Rev:: 4282         $
 * @date    $Date:: 2019-10-18 #$
 * @brief   The header file of the DAC library.
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

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_DAC_DUAL16_DAC_H
#define __HT32F5XXXX_DAC_DUAL16_DAC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup DAC_DUAL16
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup DAC_Exported_Types DAC exported types
  * @{
  */
typedef enum
{
  DAC_CH_R    = 0,
  DAC_CH_L    = 1,
} DAC_Dual16_Ch;

typedef enum
{
  DATA_FROM_UC   = 0,
  DATA_FROM_MIDI = 1,
} DAC_Dual16_Source;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup DAC_DUAL16_Exported_Functions DAC exported functions
  * @{
  */
void DACD16_DeInit(void);
void DACD16_DataSourceConfig(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x, DAC_Dual16_Source DATA_FROM_x);
void DACD16_SetChannelData(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x, u16 Data);
void DACD16_SoftwareStartConvCmd(HT_DAC_DUAL16_TypeDef* DACx, DAC_Dual16_Ch DAC_CH_x);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

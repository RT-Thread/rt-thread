/*********************************************************************************************************//**
 * @file    ht32f1xxxx_tm_type.h
 * @version $Rev:: 2971         $
 * @date    $Date:: 2023-10-25 #$
 * @brief   The header file of the TM library.
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
#ifndef __HT32F1XXXX_TM_TYPE_H
#define __HT32F1XXXX_TM_TYPE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup TM
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup TM_Exported_Types TM exported types
  * @{
  */
/**
 * @brief Enumeration of TM channel.
 */
typedef enum
{
  TM_CH_0 = 0,                    /*!< TM channel 0                                                         */
  TM_CH_1,                        /*!< TM channel 1                                                         */
  TM_CH_2,                        /*!< TM channel 2                                                         */
  TM_CH_3                         /*!< TM channel 3                                                         */
} TM_CH_Enum;
/**
 * @brief Enumeration of TM channel control.
 */
typedef enum
{
  TM_CHCTL_DISABLE = 0,           /*!< TM channel disable                                                   */
  TM_CHCTL_ENABLE                 /*!< TM channel enable                                                    */
} TM_CHCTL_Enum;
/**
 * @brief Enumeration of TM channel polarity.
 */
typedef enum
{
  TM_CHP_NONINVERTED = 0,         /*!< TM channel polarity is active high or rising edge                    */
  TM_CHP_INVERTED                 /*!< TM channel polarity is active low or falling edge                    */
} TM_CHP_Enum;
/**
 * @brief Enumeration of MCTM channel output idle state.
 */
typedef enum
{
  MCTM_OIS_LOW = 0,               /*!< MCTM channel output low when CHMOE equal to 0                        */
  MCTM_OIS_HIGH                   /*!< MCTM channel output high when CHMOE equal to 0                       */
} MCTM_OIS_Enum;
/**
 * @brief Enumeration of MCTM COMUS.
 */
typedef enum
{
  MCTM_COMUS_STIOFF = 0,            /*!< MCTM capture/compare control bits are updated by
                                         setting the UEV2G bit only */
  MCTM_COMUS_STION                  /*!< MCTM capture/compare control bits are updated by both
                                         setting the UEV2G bit or when a rising edge occurs on STI */
} MCTM_COMUS_Enum;
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

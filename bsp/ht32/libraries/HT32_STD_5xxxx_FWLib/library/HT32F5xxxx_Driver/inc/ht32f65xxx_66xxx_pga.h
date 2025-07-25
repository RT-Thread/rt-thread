/*********************************************************************************************************//**
 * @file    ht32f65xxx_66xxx_pga.h
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   The header file of the PGA library.
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
#ifndef __HT32F65XXX_66XXX_PGA_H
#define __HT32F65XXX_66XXX_PGA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup PGA
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup PGA_Exported_Types PGA exported types
  * @{
  */
#define PGA_GAIN_LEVEL_0                              (0x0)
#define PGA_GAIN_LEVEL_1                              (0x1)
#define PGA_GAIN_LEVEL_2                              (0x2)
#define PGA_GAIN_LEVEL_3                              (0x3)
#define PGA_GAIN_LEVEL_4                              (0x4)
#define PGA_GAIN_LEVEL_5                              (0x5)

/**
 * @brief Enumeration of PGA Gain Type 1.
 */
typedef enum
{
  /* PGAnPGA = 1, PGAnHVDDAEN[1:0] = b0x, PGAnNUG = 0                                                       */
  PGA_GAIN_6  = PGA_GAIN_LEVEL_0,
  PGA_GAIN_8  = PGA_GAIN_LEVEL_1,
  PGA_GAIN_12 = PGA_GAIN_LEVEL_2,
  PGA_GAIN_16 = PGA_GAIN_LEVEL_3,
  PGA_GAIN_24 = PGA_GAIN_LEVEL_4,
  PGA_GAIN_32 = PGA_GAIN_LEVEL_5,
} PGA_GAIN_TYPE1_Enum;
/**
 * @brief Enumeration of PGA Gain Type 2.
 */
typedef enum
{
  /* PGAnPGA = 1, PGAnHVDDAEN[1:0] = b10, PGAnNUG = 0                                                       */
  PGA_GAIN_5  = PGA_GAIN_LEVEL_0,
  PGA_GAIN_7  = PGA_GAIN_LEVEL_1,
  PGA_GAIN_11 = PGA_GAIN_LEVEL_2,
  PGA_GAIN_15 = PGA_GAIN_LEVEL_3,
  PGA_GAIN_23 = PGA_GAIN_LEVEL_4,
  PGA_GAIN_31 = PGA_GAIN_LEVEL_5,
} PGA_GAIN_TYPE2_Enum;
/**
 * @brief Enumeration of Calibration Reference Input.
 */
typedef enum
{
  PGA_CALIBRATION_INPUT_NEGATIVE = 0,
  PGA_CALIBRATION_INPUT_POSITIVE = 1,
} PGA_CALIBRATION_INPUT_Enum;
/**
 * @brief Definition of PGA init structure.
 */
typedef struct
{
  u8 PGA_REF;
  u8 PGA_NUG;
  u8 PGA_NE;
  u8 PGA_PGA;
  u8 PGA_HVDDA;
} PGA_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup PGA_Exported_Constants PGA exported constants
  * @{
  */
#define PGA_UNPROTECT_KEY                         (0x9C3A)

#define PGA_HVDDA_DISABLE                         (0x0)
#define PGA_HVDDA_RESISTOR                        (0x2)
#define PGA_HVDDA_POS_INPUT                       (0x3)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup PGA_Exported_Functions PGA exported functions
  * @{
  */
void PGA_DeInit(void);
void PGA_Cmd(HT_PGA0_X_TypeDef* HT_PGAn, ControlStatus NewState);
void PGA_SetUnProtectKey(u32 uUnProtectKey);
void PGA_ProtectConfig(HT_PGA0_X_TypeDef* HT_PGAn);
void PGA_UnprotectConfig(HT_PGA0_X_TypeDef* HT_PGAn);
void PGA_Init(HT_PGA0_X_TypeDef* HT_PGAn, PGA_InitTypeDef* PGA_InitStruct);
void PGA_StructInit(PGA_InitTypeDef* PGA_InitStruct);
void PGA_GainConfig(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x);
void PGA_HVDDACmd(ControlStatus NewState);
void PGA_CalibrationCmd(HT_PGA0_X_TypeDef* HT_PGAn, ControlStatus NewState);
void PGA_SetCalibrationInput(HT_PGA0_X_TypeDef* HT_PGAn, PGA_CALIBRATION_INPUT_Enum PGA_INPUT_x);
void PGA_SetCalibrationValue(HT_PGA0_X_TypeDef* HT_PGAn, u32 Value);
FlagStatus PGA_ReadOutputBit(HT_PGA0_X_TypeDef* HT_PGAn);
void PGA_SetModeInverting(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x);
void PGA_SetModeDifferentiator(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x);
void PGA_SetModeNonInverting(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x);
void PGA_SetModeInvertingAdder(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x);
void PGA_SetModeExponent(HT_PGA0_X_TypeDef* HT_PGAn, u32 PGA_GAIN_LEVEL_x);
void PGA_SetModeManual(HT_PGA0_X_TypeDef* HT_PGAn);
void PGA_SetModeNonInvertingAdder(HT_PGA0_X_TypeDef* HT_PGAn, PGA_GAIN_TYPE1_Enum PGA_GAIN_x);
void PGA_SetModeComparator(HT_PGA0_X_TypeDef* HT_PGAn);

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

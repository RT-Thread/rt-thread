/*********************************************************************************************************//**
 * @file    ht32f65xxx_66xxx_opa.h
 * @version $Rev:: 6911         $
 * @date    $Date:: 2023-05-10 #$
 * @brief   The header file of the OPA library.
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
#ifndef __HT32F65XXX_66XXX_OPA_H
#define __HT32F65XXX_66XXX_OPA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup OPA
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
#if (LIBCFG_OPA_V2)
/** @defgroup OPA_Exported_Types OPA exported types
  * @{
  */
/**
 * @brief Definition of CMP init structure.
 */
typedef struct
{
  u32 OPA_ScalerEnable;
  u32 OPA_ExternalPinEnable;
  #if (LIBCFG_OPA_PGA)
  u32 OPA_PGAEnable;
  u32 OPA_UnitGainEnable;
  u32 OPA_PGAGain;
  #endif
} OPA_InitTypeDef;
/**
 * @brief Enumeration of OPA PGA Gain.
 */
typedef enum
{
  /* OPnPGA = 1, OPnDACEN = 0                                                                               */
  PGA_GAIN_6  = 0x0,
  PGA_GAIN_8  = 0x1,
  PGA_GAIN_12 = 0x2,
  PGA_GAIN_16 = 0x3,
  PGA_GAIN_24 = 0x4,
  PGA_GAIN_32 = 0x5,
  PGA_GAIN_48 = 0x6,
  PGA_GAIN_64 = 0x7,

  /* OPnPGA = 1, OPnDACEN = 1                                                                               */
  PGA_GAIN_5  = 0x0,
  PGA_GAIN_7  = 0x1,
  PGA_GAIN_11 = 0x2,
  PGA_GAIN_15 = 0x3,
  PGA_GAIN_23 = 0x4,
  PGA_GAIN_31 = 0x5,
  PGA_GAIN_47 = 0x6,
  PGA_GAIN_63 = 0x7,
} OPA_PGA_Enum;
/**
  * @}
  */
#endif

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup OPA_Exported_Constants OPA exported constants
  * @{
  */
#define OPA_UNPROTECT_KEY                         (0x9C3A)

#if (LIBCFG_OPA1)
#define IS_OPA1(PERIPH)                           (PERIPH == HT_OPA1)
#else
#define IS_OPA1(PERIPH)                           (0)
#endif
#define IS_OPA(PERIPH)                            ((PERIPH == HT_OPA0) || IS_OPA1(PERIPH))

#if (LIBCFG_OPA_V2)
/* Definitions of OPA DAC Enable Bit                                                                        */
#define OPA_SCALER_ENABLE                         ((u32)0x00000100)
#define OPA_SCALER_DISABLE                        ((u32)0x00000000)

/* Definitions of OPA External Pin Enable Bit                                                               */
#define OPA_ExternalPin_ENABLE                    ((u32)0x00000008)
#define OPA_ExternalPin_DISABLE                   ((u32)0x00000000)

/* Definitions of OPA PGA Enable Bit                                                                        */
#define OPA_PGA_ENABLE                            ((u32)0x00000004)
#define OPA_PGA_DISABLE                           ((u32)0x00000000)

/* Definitions of OPA UnitGain Enable Bit                                                                   */
#define OPA_UNITGAIN_ENABLE                       ((u32)0x00000002)
#define OPA_UNITGAIN_DISABLE                      ((u32)0x00000000)

/* Definitions of OPA Output Status                                                                         */
#define OPA_OUTPUT_HIGH                           ((u32)0x00000080)
#define OPA_OUTPUT_LOW                            ((u32)0x00000000)

#define OPA_NORMAL_MODE                           (0)
#define OPA_OFFSET_CALIBRATION_MODE               (1)

#define OPA_INPUT_OFFSET_INN                      (0)
#define OPA_INPUT_OFFSET_INP                      (1)

/**
 * @brief Used to check parameter of the OPAx.
 */
#define IS_OPA_ScalerEnable(x)                    ((x == OPA_SCALER_ENABLE) || (x == OPA_SCALER_DISABLE))

#define IS_OPA_ExtPinEnable(x)                    ((x == OPA_ExternalPin_ENABLE) || (x == OPA_ExternalPin_DISABLE))

#define IS_OPA_PGAEnable(x)                       ((x == OPA_PGA_ENABLE) || (x == OPA_PGA_DISABLE))

#define IS_OPA_UnitGainEnable(x)                  ((x == OPA_UNITGAIN_ENABLE) || (x == OPA_UNITGAIN_DISABLE))

#define IS_OPA_PGA_SEL(SEL)                       ((SEL == PGA_GAIN_5)  || (SEL == PGA_GAIN_6)  || \
                                                   (SEL == PGA_GAIN_7)  || (SEL == PGA_GAIN_8)  || \
                                                   (SEL == PGA_GAIN_11) || (SEL == PGA_GAIN_12) || \
                                                   (SEL == PGA_GAIN_15) || (SEL == PGA_GAIN_16) || \
                                                   (SEL == PGA_GAIN_23) || (SEL == PGA_GAIN_24) || \
                                                   (SEL == PGA_GAIN_31) || (SEL == PGA_GAIN_32) || \
                                                   (SEL == PGA_GAIN_47) || (SEL == PGA_GAIN_48) || \
                                                   (SEL == PGA_GAIN_63) || (SEL == PGA_GAIN_64))

#define IS_OPA_OFMMODE(MODE)                      ((MODE == OPA_OFFSET_CALIBRATION_MODE) || \
                                                   (MODE == OPA_NORMAL_MODE))

#define IS_OPA_INPUTOFFSET_SEL(SEL)               ((SEL == OPA_INPUT_OFFSET_INN) || \
                                                   (SEL == OPA_INPUT_OFFSET_INP))

/* Check the OPA Scaler Value                                                                               */
#define IS_OPA_SCALER_VALUE(x)                    (x <= 0x3FF)

/* Check the OPA Input Offset Value                                                                         */
#define IS_OPA_INPUTOFFSET_VALUE(x)               (x <= 0x1F)
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup OPA_Exported_Functions OPA exported functions
  * @{
  */
void OPA_DeInit(void);
void OPA_Cmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState);
void OPA_SetUnProtectKey(u32 uUnProtectKey);
void OPA_ProtectConfig(HT_OPA_TypeDef* HT_OPAn);
void OPA_UnprotectConfig(HT_OPA_TypeDef* HT_OPAn);

#if (LIBCFG_OPA_V2)
void OPA_Init(HT_OPA_TypeDef* HT_OPAn, OPA_InitTypeDef* OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef* OPA_InitStruct);
void OPA_ExternalInputCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState);
#if (LIBCFG_OPA_PGA)
void OPA_UnitGainCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState);
void OPA_PGACmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState);
void OPA_PGAGain(HT_OPA_TypeDef* HT_OPAn, u8 bGAIN_SEL);
#endif
void OPA_ScalerCmd(HT_OPA_TypeDef* HT_OPAn, ControlStatus NewState);
void OPA_SetScalerValue(HT_OPA_TypeDef* HT_OPAn, u32 Scaler_Value);
FlagStatus OPA_GetOutputStatus(HT_OPA_TypeDef* HT_OPAn);
void OPA_OFMMode(HT_OPA_TypeDef* HT_OPAn, u8 bMODE);
void OPA_OFM_InputOffsetReferenceSelect(HT_OPA_TypeDef* HT_OPAn, u8 bSEL);
void OPA_SetInputOffsetVoltage(HT_OPA_TypeDef* HT_OPAn, u8 bData);
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

#ifdef __cplusplus
}
#endif

#endif

/*********************************************************************************************************//**
 * @file    ht32f66xxx_pid.h
 * @version $Rev:: 8260         $
 * @date    $Date:: 2024-11-05 #$
 * @brief   The header file of the PID library.
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
#ifndef __HT32F66XXX_PID_H
#define __HT32F66XXX_PID_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup PID
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup PID_Exported_Types PID exported types
  * @{
  */

/**
 * @brief PID PID_Mode
 */
typedef enum
{
  PID_SPD_MODE   = 0,
  PID_IQ_MODE,
  PID_ID_MODE,
  PID_FWNK_MODE,
  PID_PLL_MODE,
  PID_USR_MODE,
} PID_Mode_Enum;

#define IS_PID_MODE(PID_MODE)    (((PID_MODE) == PID_SPD_MODE)   || \
                                  ((PID_MODE) == PID_IQ_MODE)    || \
                                  ((PID_MODE) == PID_ID_MODE)    || \
                                  ((PID_MODE) == PID_FWNK_MODE)  || \
                                  ((PID_MODE) == PID_PLL_MODE)   || \
                                  ((PID_MODE) == PID_USR_MODE))

/**
 * @brief PID paramater init structure
 */
typedef struct
{
  s32 ERRn_1;
  s32 UIn_1;
  s32 KP;
  s32 KI;
  s32 KD;
  s32 UI_MAX;
  s32 UI_MIN;
  s16 OUT_MAX;
  s16 OUT_MIN;
} PID_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup PID_Exported_Constants PID exported constants
  * @{
  */
#define IS_PID(x)                IS_PID0(x)
#define IS_PID0(x)               (x == HT_PID0)

/**
 * @brief PID CR Bit Field Definitions
 */
#define PID_CR_MODSEL_Pos        24
#define PID_CR_MODSEL_Msk        (0xFul << PID_CR_MODSEL_Pos)

#define PID_CR_UIF               (0x00000008)
#define PID_CR_PIDEN             (0x00000001)

#define PID_FLAG_OVF             (0x00020000)
#define PID_FLAG_CMP             (0x00000200)

#define IS_PID_FLAG(FLAG)        ((FLAG == PID_FLAG_OVF) || \
                                  (FLAG == PID_FLAG_CMP))

#define PID_INT_OVF              (0x00010000)
#define PID_INT_CMP              (0x00000100)

#define IS_PID_INT(INT)          ((INT == PID_INT_OVF) || \
                                  (INT == PID_INT_CMP))

#define PID_INT_Status_Pos       2
#define PID_INT_Clear_Pos        3

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup PID_Exported_Functions PID exported functions
  * @{
  */
void PID_DeInit(HT_PID_TypeDef* HT_PIDn);
void PID_Init(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode, PID_InitTypeDef* PID_Para);
void PID_IntConfig(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x, ControlStatus NewState);
FlagStatus PID_GetIntStatus(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x);
void PID_ClearIntPendingBit(HT_PID_TypeDef* HT_PIDn, u32 PID_INT_x);
void PID_SetComPara_ERRn(HT_PID_TypeDef* HT_PIDn, s32 ERRn);
void PID_SetComPara_UI_Input(HT_PID_TypeDef* HT_PIDn, s32 UI_Input);
void PID_Compute(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode);
s16  PID_GetOutResult(HT_PID_TypeDef* HT_PIDn);
FlagStatus PID_GetFlagStatus(HT_PID_TypeDef* HT_PIDn, u32 PID_FLAG_x);
void PID_UI_InputCmd(HT_PID_TypeDef* HT_PIDn, ControlStatus NewState);
s32  PID_GetERRn_1(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode);
s32  PID_GetUIn_1(HT_PID_TypeDef* HT_PIDn, PID_Mode_Enum PID_Mode);
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

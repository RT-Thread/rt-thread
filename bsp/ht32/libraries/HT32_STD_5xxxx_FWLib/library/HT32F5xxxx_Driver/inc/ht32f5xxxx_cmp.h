/*********************************************************************************************************//**
 * @file    ht32f5xxxx_cmp.h
 * @version $Rev:: 7319         $
 * @date    $Date:: 2023-10-28 #$
 * @brief   The header file of the CMP library.
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
#ifndef __HT32F5XXXX_CMP_H
#define __HT32F5XXXX_CMP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup CMP
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CMP_Exported_Types CMP exported types
  * @{
  */

typedef struct
{
  u32 CMP_Wakeup;
  u32 CMP_OutputSelection;
  u32 CMP_ScalerSource;
  u32 CMP_ScalerOutputBuf;
  u32 CMP_ScalerEnable;
  u32 CMP_CoutSync;
  u32 CMP_OutputPol;
  #if (LIBCFG_CMP_65x_VER)
  u32 CMP_InputSelection;
  #endif
  u32 CMP_InvInputSelection;
  u32 CMP_Hysteresis;
  u32 CMP_Speed;
} CMP_InitTypeDef;

#if (LIBCFG_CMP_CO)
typedef enum
{
  CMP_SYNCOUT_CMPnO       = 0,
  CMP_SYNCOUT_MCTM_CH0O   = 1,
  CMP_SYNCOUT_MCTM_CH0NO  = 2,
  CMP_SYNCOUT_MCTM_CH1O   = 3,
  CMP_SYNCOUT_MCTM_CH1NO  = 4,
  CMP_SYNCOUT_MCTM_CH2O   = 5,
  CMP_SYNCOUT_MCTM_CH2NO  = 6,
  CMP_SYNCOUT_MCTM_CH3O   = 7,
  CMP_SYNCOUT_MCTM_CH3OB  = 8,  // Inverted of MCTM_CH3O
} CMP_SYNCOUT_Enum;
#endif

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CMP_Exported_Constants CMP exported constants
  * @{
  */

/* Definitions of CMP Protection Key                                                                        */
#define CMP_PROTECT_KEY                           ((u32)0x9C3A0000)


/* Definitions of CMP Output Status                                                                         */
#define CMP_OUTPUT_HIGH                           ((u32)0x00008000)
#define CMP_OUTPUT_LOW                            ((u32)0x00000000)


/* Definitions of CMP Wakeup Control Bit                                                                    */
#define CMP_WUP_ENABLE                            ((u32)0x00004000)
#define CMP_WUP_DISABLE                           ((u32)0x00000000)

#define IS_CMP_Wakeup_Set(x)                      ((x == CMP_WUP_ENABLE) || (x == CMP_WUP_DISABLE))


/* Definitions of CMP Output Selection for IP Trigger Source                                                */
#if (LIBCFG_CMP_65x_VER)
#define CMP_TRIG_NONE                             ((u32)0x0 << 11)
#define CMP_TRIG_GPTM_CH0                         ((u32)0x1 << 11) // CMP0
#define CMP_TRIG_GPTM_CH1                         ((u32)0x1 << 11) // CMP1

#define IS_CMP_OutputSelection2(x)                (0)
#if (LIBCFG_CMP2)
#define CMP_TRIG_GPTM_CH2                         ((u32)0x1 << 11) // CMP2
#undef IS_CMP_OutputSelection2
#define IS_CMP_OutputSelection2(x)                (x == CMP_TRIG_GPTM_CH2)
#endif

#define CMP_TRIG_GPTM_CH3                         ((u32)0x2 << 11)
#define CMP_TRIG_SCTM                             ((u32)0x3 << 11)
#define CMP_TRIG_MCTM_CH3                         ((u32)0x4 << 11)
#define CMP_TRIG_MCTM_BK0                         ((u32)0x5 << 11)
#define CMP_TRIG_MCTM_BK1                         ((u32)0x6 << 11)
#define CMP_TRIG_ADC                              ((u32)0x7 << 11)

#define IS_CMP_OutputSelection(x)                 ((x == CMP_TRIG_NONE)       || \
                                                   (x == CMP_TRIG_GPTM_CH0)   || \
                                                   (x == CMP_TRIG_GPTM_CH1)   || \
                                                   IS_CMP_OutputSelection2(x) || \
                                                   (x == CMP_TRIG_GPTM_CH3)   || \
                                                   (x == CMP_TRIG_SCTM)       || \
                                                   (x == CMP_TRIG_MCTM_CH3)   || \
                                                   (x == CMP_TRIG_MCTM_BK0)   || \
                                                   (x == CMP_TRIG_MCTM_BK1)   || \
                                                   (x == CMP_TRIG_ADC))
#else
#define CMP_TRIG_NONE                             ((u32)0x0 << 11)
#define CMP_TRIG_GPTM_CH3                         ((u32)0x1 << 11)
#if (LIBCFG_MCTM0)
#define CMP_TRIG_MCTM_CH3                         ((u32)0x2 << 11)
#define CMP_TRIG_MCTM_BK1                         ((u32)0x3 << 11)
#endif
#define CMP_TRIG_ADC                              ((u32)0x4 << 11)

#if (LIBCFG_MCTM0)
#define IS_CMP_OutSelMCTM(x)                      ((x == CMP_TRIG_MCTM_CH3) || (x == CMP_TRIG_MCTM_BK1))
#else
#define IS_CMP_OutSelMCTM(x)                      (0)
#endif

#define IS_CMP_OutputSelection(x)                 ((x == CMP_TRIG_NONE)     || \
                                                   (x == CMP_TRIG_GPTM_CH3) || \
                                                   IS_CMP_OutSelMCTM(x)     || \
                                                   (x == CMP_TRIG_ADC))
#endif

/* Definitions of CMP Scaler Source Selection                                                               */
#define CMP_SCALER_SRC_VDDA                       ((u32)0x00000000)

#if (LIBCFG_CMP_NOSCALER_SRC)
#define IS_CMP_ScalerSource(x)                    ((x == CMP_SCALER_SRC_VDDA))
#else
#define CMP_SCALER_SRC_VREF                       ((u32)0x00000400)
#define IS_CMP_ScalerSource(x)                    ((x == CMP_SCALER_SRC_VDDA) || (x == CMP_SCALER_SRC_VREF))
#endif


/* Definitions of CMP Scaler Output Enable Bit                                                              */
#define CMP_SCALER_OBUF_DISABLE                   ((u32)0x00000000)
#define CMP_SCALER_OBUF_ENABLE                    ((u32)0x00000200)

#define IS_CMP_ScalerOutputBuf(x)                 ((x == CMP_SCALER_OBUF_DISABLE) || (x == CMP_SCALER_OBUF_ENABLE))


/* Definitions of CMP Scaler Enable Bit                                                                     */
#define CMP_SCALER_DISABLE                        ((u32)0x00000000)
#define CMP_SCALER_ENABLE                         ((u32)0x00000100)

#define IS_CMP_ScalerEnable(x)                    ((x == CMP_SCALER_DISABLE) || (x == CMP_SCALER_ENABLE))


/* Definitions of CMP Sync Output Enable bit                                                                */
#define CMP_ASYNC_OUTPUT                          ((u32)0x00000000)
#define CMP_SYNC_OUTPUT                           ((u32)0x00000080)

#define IS_CMP_CoutSynchronized(x)                ((x == CMP_ASYNC_OUTPUT) || (x == CMP_SYNC_OUTPUT))


/* Definitions of CMP Output Polarity Selection                                                             */
#define CMP_NONINV_OUTPUT                         ((u32)0x00000000)
#define CMP_INV_OUTPUT                            ((u32)0x00000040)

#define IS_CMP_OutputPol_Set(x)                   ((x == CMP_NONINV_OUTPUT) || (x == CMP_INV_OUTPUT))


/* Definitions of CMP Inverted Input Source Selection                                                       */
#if (LIBCFG_CMP_65x_VER)
#if (LIBCFG_CMP_POS_INPUT_SEL_V2)
#define CMP_INPUT_CMPnP                           ((u32)0x00000000)
#define CMP_INPUT_CMPnP0                          ((u32)0x00000000)
#define CMP_INPUT_CMPnP1                          ((u32)0x00000001)
#define CMP_INPUT_CMPnP2                          ((u32)0x00000002)
#define CMP_INPUT_OPA0O                           ((u32)0x00000003)

#define IS_CMP_InputSelection(x)                  ((x == CMP_INPUT_CMPnP)  || \
                                                   (x == CMP_INPUT_CMPnP0) || \
                                                   (x == CMP_INPUT_CMPnP1) || \
                                                   (x == CMP_INPUT_CMPnP2) || \
                                                   (x == CMP_INPUT_OPA0O))
#else
#define CMP_INPUT_CMPnP                           ((u32)0x00000000)
#define CMP_INPUT_OPA0O                           ((u32)0x00000001)
#define CMP_INPUT_OPA1O                           ((u32)0x00000002)

#define IS_CMP_InputSelection(x)                  ((x == CMP_INPUT_CMPnP) || (x == CMP_INPUT_OPA0O) || (x == CMP_INPUT_OPA1O))
#endif
#endif


/* Definitions of CMP Inverted Input Source Selection                                                       */
#define CMP_EXTERNAL_CN_IN                        ((u32)0x00000000)
#define CMP_SCALER_CN_IN                          ((u32)0x00000010)

#define IS_CMP_InvInSel2(x)                       (0)

#if (LIBCFG_CMP_IVREF_CN_IN)
#define CMP_IVREF_CN_IN                           ((u32)0x00000020)
#undef  IS_CMP_InvInSel2
#define IS_CMP_InvInSel2(x)                       ((x == CMP_IVREF_CN_IN))
#endif

#if defined(USE_HT32F65230_40)
#define CMP_CMP0N_CN_IN                           ((u32)0x00000020)
#undef  IS_CMP_InvInSel2
#define IS_CMP_InvInSel2(x)                       ((x == CMP_CMP0N_CN_IN))
#endif

#if defined(USE_HT32F65232)
#define CMP0_CMP1N_CN_IN                          ((u32)0x00000020)
#define CMP1_CMP0N_CN_IN                          ((u32)0x00000020)
#undef  IS_CMP_InvInSel2
#define IS_CMP_InvInSel2(x)                       ((x == CMP0_CMP1N_CN_IN))
#endif

#define IS_CMP_InvInputSelection(x)               ((x == CMP_EXTERNAL_CN_IN) || (x == CMP_SCALER_CN_IN) || IS_CMP_InvInSel2(x))


/* Definitions of CMP Hysteresis Level Selection                                                            */
#define CMP_NO_HYSTERESIS                         ((u32)0x00000000)
#define CMP_LOW_HYSTERESIS                        ((u32)0x00000004)
#define CMP_MID_HYSTERESIS                        ((u32)0x00000008)
#define CMP_HIGH_HYSTERESIS                       ((u32)0x0000000C)

#define IS_CMP_Hysteresis_Set(x)                  ((x == CMP_NO_HYSTERESIS) || (x == CMP_LOW_HYSTERESIS) || (x == CMP_MID_HYSTERESIS) || \
                                                   (x == CMP_HIGH_HYSTERESIS))

/* Definitions of CMP Speed Mode Selection                                                                  */
#define CMP_HIGH_SPEED                            ((u32)0x00000002)
#define CMP_LOW_SPEED                             ((u32)0x00000000)

#define IS_CMP_Speed_Set(x)                       ((x == CMP_HIGH_SPEED) || (x == CMP_LOW_SPEED))


/* Definitions of CMP Enable bit                                                                            */
#define CMP_ENABLE                                ((u32)0x00000001)


/* Definitions of CMP Output Edge Interrupt Enable bit                                                      */
#define CMP_INT_RE                                ((u32)0x00000002)
#define CMP_INT_FE                                ((u32)0x00000001)

/* Check the CMP Interrupt Parameter                                                                        */
#define IS_CMP_INT(x)                             ((x & 0xFFFFFF00) != 0x0)


/* Definitions of CMP Output Edge Detection Enable bit                                                      */
#define CMP_RE_Detect                             ((u32)0x00000200)
#define CMP_FE_Detect                             ((u32)0x00000100)

#define IS_CMP_EdgeDetect(x)                      ((x == CMP_RE_Detect) || (x == CMP_FE_Detect))


/* Definitions of CMP Output Edge Flag                                                                      */
#define CMP_FLAG_RE                               ((u32)0x00000002)
#define CMP_FLAG_FE                               ((u32)0x00000001)

/* Check the CMP flag Parameter                                                                             */
#define IS_CMP_FLAG(x)                            ((x & 0xFFFFFF00) != 0x0)


/* Check the CMPx Parameter                                                                                 */
#if (LIBCFG_CMP2)
#define IS_CMP2(x)                                (x == HT_CMP2)
#else
#define IS_CMP2(x)                                (0)
#endif
#define IS_CMP(x)                                 ((x == HT_CMP0) || (x == HT_CMP1) || IS_CMP2(x))


/* Check the Scaler Value                                                                                   */
#if (LIBCFG_CMP_SCALER_8BIT)
#define IS_SCALER_VALUE(x)                        (x <= 0xFF)
#else
#define IS_SCALER_VALUE(x)                        (x <= 0x3F)
#endif

#if (LIBCFG_CMP_CO)
#define  IS_CMP_SYNC_SOURCE(x)                    ((x == CMP_SYNCOUT_CMPnO)      || \
                                                   (x == CMP_SYNCOUT_MCTM_CH0O)  || \
                                                   (x == CMP_SYNCOUT_MCTM_CH0NO) || \
                                                   (x == CMP_SYNCOUT_MCTM_CH1O)  || \
                                                   (x == CMP_SYNCOUT_MCTM_CH1NO) || \
                                                   (x == CMP_SYNCOUT_MCTM_CH2O)  || \
                                                   (x == CMP_SYNCOUT_MCTM_CH2NO) || \
                                                   (x == CMP_SYNCOUT_MCTM_CH3O)  || \
                                                   (x == CMP_SYNCOUT_MCTM_CH3OB))
#endif

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CMP_Exported_Functions CMP exported functions
  * @{
  */
void CMP_DeInit(HT_CMP_TypeDef* HT_CMPn);
void CMP_UnprotectConfig(HT_CMP_TypeDef* HT_CMPn);
void CMP_Init(HT_CMP_TypeDef* HT_CMPn, CMP_InitTypeDef* CMP_InitStruct);
void CMP_StructInit(CMP_InitTypeDef* CMP_InitStruct);
void CMP_Cmd(HT_CMP_TypeDef* HT_CMPn, ControlStatus NewState);
void CMP_IntConfig(HT_CMP_TypeDef* HT_CMPn, u32 CMP_INT_x, ControlStatus NewState);
void CMP_EdgeDetectConfig(HT_CMP_TypeDef* HT_CMPn, u32 CMP_xE_Detect, ControlStatus NewState);
FlagStatus CMP_GetFlagStatus(HT_CMP_TypeDef* HT_CMPn, u32 CMP_FLAG_x);
void CMP_ClearFlag(HT_CMP_TypeDef* HT_CMPn, u32 CMP_FLAG_x);
FlagStatus CMP_GetOutputStatus(HT_CMP_TypeDef* HT_CMPn);
void CMP_SetScalerValue(HT_CMP_TypeDef* HT_CMPn, u8 Scaler_Value);
#if (LIBCFG_CMP_CO)
void CMP_Output_SyncSource_Select(HT_CMP_TypeDef* HT_CMPn, CMP_SYNCOUT_Enum CMP_SYNCOUT_x);
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

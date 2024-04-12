/*********************************************************************************************************//**
 * @file    ht32f5xxxx_tkey.h
 * @version $Rev:: 5483         $
 * @date    $Date:: 2021-07-19 #$
 * @brief   The header file of the TKEY library.
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
#ifndef __HT32F5XXXX_TKEY_H
#define __HT32F5XXXX_TKEY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup TKEY
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup TKEY_Exported_Types TKEY exported types
  * @{
  */

typedef enum
{                                /*!< Touch key IP clock source                                             */
  TKEY_PCLK = 0 ,                /*!< PCLK                                                                  */
  TKEY_LSI                       /*!< LSI                                                                   */
} TKEY_IP_CLK_Enum;

typedef enum
{                                             /*!< Periodic auto scan mode time-out selection               */
  TKEY_RefOSC_DelayTime_0 = (0 << 13),        /*!< 4 RefOSC clock                                           */
  TKEY_RefOSC_DelayTime_1 = (1 << 13),        /*!< 2 RefOSC clock                                           */
  TKEY_RefOSC_DelayTime_2 = (2 << 13),        /*!< 4 RefOSC clock                                           */
  TKEY_RefOSC_DelayTime_3 = (3 << 13),        /*!< 8 RefOSC clock                                           */
  TKEY_RefOSC_DelayTime_4 = (4 << 13),        /*!< 16 RefOSC clock                                          */
  TKEY_RefOSC_DelayTime_5 = (5 << 13),        /*!< 32 RefOSC clock                                          */
  TKEY_RefOSC_DelayTime_6 = (6 << 13),        /*!< 64 RefOSC clock                                          */
  TKEY_RefOSC_DelayTime_7 = (7 << 13),        /*!< 4 RefOSC clock                                           */
} TKEY_RefOSC_DelayTime_Enum;


typedef enum
{                                         /*!< Periodic auto scan mode time-out selection                   */
  TKEY_PASM_TIMEOUT_0 = (0 << 10),        /*!< 2^13/FLIRC                                                   */
  TKEY_PASM_TIMEOUT_1 = (1 << 10),        /*!< 2^14/FLIRC                                                   */
  TKEY_PASM_TIMEOUT_2 = (2 << 10),        /*!< 2^15/FLIRC                                                   */
  TKEY_PASM_TIMEOUT_3 = (3 << 10),        /*!< 2^16/FLIRC                                                   */
  TKEY_PASM_TIMEOUT_4 = (4 << 10),        /*!< 2^17/FLIRC                                                   */
  TKEY_PASM_TIMEOUT_5 = (5 << 10),        /*!< 2^18/FLIRC                                                   */
} TKEY_PASM_TIMEOUT_Enum;

typedef enum
{                                         /*!< Periodic auto scan mode period selection                     */
  TKEY_PASM_PERIOD_0 = (0 << 8),          /*!< 2^14/FLIRC                                                   */
  TKEY_PASM_PERIOD_1 = (1 << 8),          /*!< 2^13/FLIRC                                                   */
  TKEY_PASM_PERIOD_2 = (2 << 8),          /*!< 2^12/FLIRC                                                   */
  TKEY_PASM_PERIOD_3 = (3 << 8),          /*!< 2^11/FLIRC                                                   */
} TKEY_PASM_PERIOD_Enum;

typedef enum
{                                         /*!< 16-bit counter clock source selection                        */
  TKEY_TK16S_CLK_0 = (0 << 5),            /*!< TKCLK/16                                                     */
  TKEY_TK16S_CLK_1 = (1 << 5),            /*!< TKCLK/32                                                     */
  TKEY_TK16S_CLK_2 = (2 << 5),            /*!< TKCLK/64                                                     */
  TKEY_TK16S_CLK_3 = (3 << 5),            /*!< TKCLK/128                                                    */
} TKEY_TK16S_CLK_Enum;

typedef enum
{                                         /*!< OSC frequency selection                                      */
  TKEY_TKFS_FREQ_0 = (0 << 3),            /*!< 1MHz                                                         */
  TKEY_TKFS_FREQ_1 = (1 << 3),            /*!< 3MHz                                                         */
  TKEY_TKFS_FREQ_2 = (2 << 3),            /*!< 7MHz                                                         */
  TKEY_TKFS_FREQ_3 = (3 << 3),            /*!< 11MHz                                                        */
} TKEY_TKFS_FREQ_Enum;

typedef enum
{                                         /*!< Mode selection                                               */
  TKEY_MODE_AUTOSCAN = (0 << 1),          /*!< Auto scan mode                                               */
  TKEY_MODE_MANUAL   = (1 << 1),          /*!< Manual mode                                                  */
  TKEY_MODE_PASM     = (2 << 1),          /*!< Periodic auto scan mode                                      */
} TKEY_MODE_Enum;

typedef enum
{                                         /*!< TKEY module selection                                        */
  TKM_0 = 0,                              /*!< TKEY module 0                                                */
  TKM_1,                                  /*!< TKEY module 1                                                */
  TKM_2,                                  /*!< TKEY module 2                                                */
  TKM_3,                                  /*!< TKEY module 3                                                */
  TKM_4,                                  /*!< TKEY module 4                                                */
  TKM_5,                                  /*!< TKEY module 5                                                */
} TKM_Enum;

typedef enum
{                                         /*!< 8-bit time slot counter clock source                         */
  TKM_TSS_CLK_0 = (0 << 8),               /*!< Ref. OSC                                                     */
  TKM_TSS_CLK_1 = (1 << 8),               /*!< TKCLK/32                                                     */
  TKM_TSS_CLK_2 = (2 << 8),               /*!< TKCLK/64                                                     */
  TKM_TSS_CLK_3 = (3 << 8),               /*!< TKCLK/128                                                    */
} TKM_TSS_CLK_Enum;

typedef enum
{                                         /*!< C/F OSC frequency hopping selection                          */
  TKM_SOF_CTRL_SW = (0 << 3),             /*!< S/W controlled frequency hopping                             */
  TKM_SOF_CTRL_HW = (1 << 3),             /*!< H/W controlled frequency hopping                             */
} TKM_SOF_CTRL_Enum;

typedef enum
{                                         /*!< Key OSC and Ref OSC frequency selection                      */
  TKM_SOF_FREQ_0 = (0 << 0),              /*!< 1.020MHz.                                                    */
  TKM_SOF_FREQ_1 = (1 << 0),              /*!< 1.040MHz.                                                    */
  TKM_SOF_FREQ_2 = (2 << 0),              /*!< 1.059MHz.                                                    */
  TKM_SOF_FREQ_3 = (3 << 0),              /*!< 1.074MHz.                                                    */
  TKM_SOF_FREQ_4 = (4 << 0),              /*!< 1.085MHz.                                                    */
  TKM_SOF_FREQ_5 = (5 << 0),              /*!< 1.099MHz.                                                    */
  TKM_SOF_FREQ_6 = (6 << 0),              /*!< 1.111MHz.                                                    */
  TKM_SOF_FREQ_7 = (7 << 0)               /*!< 1.125MHz.                                                    */
} TKM_SOF_FREQ_Enum;

typedef enum
{                                         /*!< Key selection                                                */
  TKM_KEY_0 = 0,                          /*!< Key 0                                                        */
  TKM_KEY_1,                              /*!< Key 1                                                        */
  TKM_KEY_2,                              /*!< Key 2                                                        */
  TKM_KEY_3,                              /*!< Key 3                                                        */
} TKM_KEY_Enum;

typedef enum
{                                         /*!< Time slot selection                                          */
  TKM_TIME_SLOT_0 = 0,                    /*!< Time slot 0                                                  */
  TKM_TIME_SLOT_1,                        /*!< Time slot 1                                                  */
  TKM_TIME_SLOT_2,                        /*!< Time slot 2                                                  */
  TKM_TIME_SLOT_3,                        /*!< Time slot 3                                                  */
} TKM_TIME_SLOT_Enum;

typedef enum
{                                         /*!< Key threshold selection                                      */
  TKM_KEY_THR_LOWER = 0,                  /*!< Lower threshold                                              */
  TKM_KEY_THR_UPPER,                      /*!< Upper threshold                                              */
} TKM_KEY_THR_Enum;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup TKEY_Exported_Constants TKEY exported constants
  * @{
  */
#define IS_TKEY_IP_CLK(x)         (((x) == TKEY_PCLK) || ((x) == TKEY_LSI) )

#define IS_TKEY_RefOSC_DelayTime(x)      (((x) == TKEY_RefOSC_DelayTime_0) || ((x) == TKEY_RefOSC_DelayTime_1) || \
                                         ((x) == TKEY_RefOSC_DelayTime_2) || ((x) == TKEY_RefOSC_DelayTime_3) || \
                                         ((x) == TKEY_RefOSC_DelayTime_4) || ((x) == TKEY_RefOSC_DelayTime_5)|| \
                                         ((x) == TKEY_RefOSC_DelayTime_6) || ((x) == TKEY_RefOSC_DelayTime_7))

#define IS_TKEY_PASM_TIMEOUT(x)         (((x) == TKEY_PASM_TIMEOUT_0) || ((x) == TKEY_PASM_TIMEOUT_1) || \
                                         ((x) == TKEY_PASM_TIMEOUT_2) || ((x) == TKEY_PASM_TIMEOUT_3) || \
                                         ((x) == TKEY_PASM_TIMEOUT_4) || ((x) == TKEY_PASM_TIMEOUT_5))

#define IS_TKEY_PASM_PERIOD(x)          (((x) == TKEY_PASM_PERIOD_0) || ((x) == TKEY_PASM_PERIOD_1) || \
                                         ((x) == TKEY_PASM_PERIOD_2) || ((x) == TKEY_PASM_PERIOD_3))

#define IS_TKEY_TK16S_CLK(x)            (((x) == TKEY_TK16S_CLK_0) || ((x) == TKEY_TK16S_CLK_1) || \
                                         ((x) == TKEY_TK16S_CLK_2) || ((x) == TKEY_TK16S_CLK_3))


#define IS_TKEY_TKFS_FREQ(x)            (((x) == TKEY_TKFS_FREQ_0) || ((x) == TKEY_TKFS_FREQ_1) || \
                                         ((x) == TKEY_TKFS_FREQ_2) || ((x) == TKEY_TKFS_FREQ_3))

#define IS_TKEY_MODE(x)                 (((x) == TKEY_MODE_AUTOSCAN) || ((x) == TKEY_MODE_MANUAL) || \
                                         ((x) == TKEY_MODE_PASM))

#define TKEY_INT_TKTHE                  ((u32)0x00000001)
#define TKEY_INT_TKRCOVE                ((u32)0x00000002)
#define TKEY_INT_TKTHWUEN               ((u32)0x00000004)
#define TKEY_INT_TKRCOVWUEN             ((u32)0x00000008)

#define IS_TKEY_INT(TKEY_INT)           (((TKEY_INT & 0xFFFFFFFC) == 0) && (TKEY_INT != 0))

#define TKEY_FLAG_TKTHF                 ((u32)0x00000001)
#define TKEY_FLAG_TKRCOVF               ((u32)0x00000002)
#define TKEY_FLAG_TK16OV                ((u32)0x00000004)
#define TKEY_FLAG_TKCFOV                ((u32)0x00000008)
#define TKEY_FLAG_TKBUSY                ((u32)0x00000010)

#define IS_TKEY_FLAG(FLAG)              ((FLAG == TKEY_FLAG_TKTHF)   || \
                                         (FLAG == TKEY_FLAG_TKRCOVF) || \
                                         (FLAG == TKEY_FLAG_TK16OV)  || \
                                         (FLAG == TKEY_FLAG_TKCFOV)  || \
                                         (FLAG == TKEY_FLAG_TKBUSY))


#define IS_TKEY_FLAG_CLEAR(CLEAR)       ((CLEAR == TKEY_FLAG_TKTHF)   || \
                                         (CLEAR == TKEY_FLAG_TKRCOVF) || \
                                         (CLEAR == TKEY_FLAG_TK16OV)  || \
                                         (CLEAR == TKEY_FLAG_TKCFOV))

#define IS_TKM(x)                       (((x) == TKM_0) || ((x) == TKM_1) || \
                                         ((x) == TKM_2) || ((x) == TKM_3) || \
                                         ((x) == TKM_4) || ((x) == TKM_5))

#define IS_TKM_TSS_CLK(x)               (((x) == TKM_TSS_CLK_0) || ((x) == TKM_TSS_CLK_1) || \
                                         ((x) == TKM_TSS_CLK_2) || ((x) == TKM_TSS_CLK_3))


#define IS_TKM_SOFC_CTRL(x)             (((x) == TKM_SOFC_SW) || ((x) == TKM_SOFC_HW))

#define IS_TKM_SOF_FREQ(x)              (((x) == TKM_SOF_FREQ_0) || ((x) == TKM_SOF_FREQ_1) || \
                                         ((x) == TKM_SOF_FREQ_2) || ((x) == TKM_SOF_FREQ_3) || \
                                         ((x) == TKM_SOF_FREQ_4) || ((x) == TKM_SOF_FREQ_5) || \
                                         ((x) == TKM_SOF_FREQ_6) || ((x) == TKM_SOF_FREQ_7))

#define IS_TKM_KEY(x)                   (((x) == TKM_KEY_3) || ((x) == TKM_KEY_2) || \
                                         ((x) == TKM_KEY_1) || ((x) == TKM_KEY_0))

#define IS_TKM_SOF_CTRL(x)              (((x) == TKM_SOF_CTRL_SW) || ((x) == TKM_SOF_CTRL_HW))

#define IS_TKM_TIME_SLOT(x)             (((x) == TKM_TIME_SLOT_0) || ((x) == TKM_TIME_SLOT_1) || \
                                         ((x) == TKM_TIME_SLOT_2) || ((x) == TKM_TIME_SLOT_3))

#define IS_TKM_KEY_THR(x)               (((x) == TKM_KEY_THR_LOWER) || ((x) == TKM_KEY_THR_UPPER))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup TKEY_Exported_Functions TKEY exported functions
  * @{
  */
void TKEY_DeInit(void);
void TKEY_IPClockConfig(TKEY_IP_CLK_Enum Sel);
void TKEY_RefOSCDelayTimeConfig(TKEY_RefOSC_DelayTime_Enum Sel);
void TKEY_PASMTimeoutConfig(TKEY_PASM_TIMEOUT_Enum Sel);
void TKEY_PASMPeriodConfig(TKEY_PASM_PERIOD_Enum Sel);
void TKEY_16BitCounterClockConfig(TKEY_TK16S_CLK_Enum Sel);
void TKEY_OSCFreqConfig(TKEY_TKFS_FREQ_Enum Sel);
void TKEY_ModeConfig(TKEY_MODE_Enum Sel);
void TKEY_StartCmd(ControlStatus NewState);
void TKEY_IntConfig(u32 TKEY_Int, ControlStatus NewState);
FlagStatus TKEY_GetFlagStatus(u32 TKEY_Flag);
void TKEY_ClearFlag(u32 TKEY_Flag);
u32 TKEY_Get16BitCounterValue(void);
void TKEY_Set8BitCounterReload(u32 Reload);
u32 TKEY_Get8BitCounterReload(void);

void TKM_TimeSlotCounterClockConfig(TKM_Enum TKMn, TKM_TSS_CLK_Enum Sel);
void TKM_RefOSCCmd(TKM_Enum TKMn, ControlStatus NewState);
void TKM_KeyOSCCmd(TKM_Enum TKMn, ControlStatus NewState);
void TKM_MultiFreqCmd(TKM_Enum TKMn, ControlStatus NewState);
void TKM_SOFCtrlConfig(TKM_Enum TKMn, TKM_SOF_CTRL_Enum Sel);
void TKM_SOFFreqConfig(TKM_Enum TKMn, TKM_SOF_FREQ_Enum Sel);
void TKM_KeyCmd(TKM_Enum TKMn, TKM_KEY_Enum Key, ControlStatus NewState);
void TKM_TimeSlotKeyConfig(TKM_Enum TKMn, TKM_TIME_SLOT_Enum Slot, TKM_KEY_Enum Key);
void TKM_KeyThresholdConfig(TKM_Enum TKMn, TKM_KEY_Enum Key, TKM_KEY_THR_Enum Sel);
FlagStatus TKM_GetMatchFlagStatus(TKM_Enum TKMn, TKM_KEY_Enum Key);
void TKM_ClearMatchFlag(TKM_Enum TKMn, TKM_KEY_Enum Key);
void TKM_SetRefOSCCapacitor(TKM_Enum TKMn, u32 Value);
u32 TKM_GetRefOSCCapacitor(TKM_Enum TKMn);
void TKM_SetKeyCapacitor(TKM_Enum TKMn, TKM_KEY_Enum Key, u32 Value);
u32 TKM_GetKeyCapacitor(TKM_Enum TKMn, TKM_KEY_Enum Key);
u32 TKM_Get16BitCFCounterValue(TKM_Enum TKMn);
u32 TKM_GetKeyCounterValue(TKM_Enum TKMn, TKM_KEY_Enum Key);
void TKM_SetKeyThreshold(TKM_Enum TKMn, TKM_KEY_Enum Key, u32 Value);
u32 TKM_GetKeyThreshold(TKM_Enum TKMn, TKM_KEY_Enum Key);
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

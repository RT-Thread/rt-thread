/*********************************************************************************************************//**
 * @file    ht32f1xxxx_rtc.h
 * @version $Rev:: 2971         $
 * @date    $Date:: 2023-10-25 #$
 * @brief   The header file of the RTC library.
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
#ifndef __HT32F1XXXX_RTC_H
#define __HT32F1XXXX_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup RTC_Exported_Types RTC exported types
  * @{
  */

/**
 * @brief Selection of RTC clock source
 */
typedef enum
{
  RTC_SRC_LSI = 0,                /*!< Low speed internal clock, about 32 kHz                               */
  RTC_SRC_LSE                     /*!< Low speed external 32768 Hz clock                                    */
} RTC_SRC_Enum;
/**
 * @brief Selection of RTC LSE startup mode
 */
typedef enum
{
  RTC_LSESM_NORMAL = 0,       /*!< Little power consumption but longer startup time.                        */
  RTC_LSESM_FAST              /*!< Shortly startup time but higher power consumption.                       */
} RTC_LSESM_Enum;
/**
 * @brief Selection of RTC prescaler
 */
typedef enum
{
  RTC_RPRE_1     = 0x0000,           /*!< CK_SECOND = CK_RTC                                                */
  RTC_RPRE_2     = 0x0100,           /*!< CK_SECOND = CK_RTC / 2                                            */
  RTC_RPRE_4     = 0x0200,           /*!< CK_SECOND = CK_RTC / 4                                            */
  RTC_RPRE_8     = 0x0300,           /*!< CK_SECOND = CK_RTC / 8                                            */
  RTC_RPRE_16    = 0x0400,           /*!< CK_SECOND = CK_RTC / 16                                           */
  RTC_RPRE_32    = 0x0500,           /*!< CK_SECOND = CK_RTC / 32                                           */
  RTC_RPRE_64    = 0x0600,           /*!< CK_SECOND = CK_RTC / 64                                           */
  RTC_RPRE_128   = 0x0700,           /*!< CK_SECOND = CK_RTC / 128                                          */
  RTC_RPRE_256   = 0x0800,           /*!< CK_SECOND = CK_RTC / 256                                          */
  RTC_RPRE_512   = 0x0900,           /*!< CK_SECOND = CK_RTC / 512                                          */
  RTC_RPRE_1024  = 0x0A00,           /*!< CK_SECOND = CK_RTC / 1024                                         */
  RTC_RPRE_2048  = 0x0B00,           /*!< CK_SECOND = CK_RTC / 2048                                         */
  RTC_RPRE_4096  = 0x0C00,           /*!< CK_SECOND = CK_RTC / 4096                                         */
  RTC_RPRE_8192  = 0x0D00,           /*!< CK_SECOND = CK_RTC / 8192                                         */
  RTC_RPRE_16384 = 0x0E00,           /*!< CK_SECOND = CK_RTC / 16384                                        */
  RTC_RPRE_32768 = 0x0F00            /*!< CK_SECOND = CK_RTC / 32768                                        */
} RTC_RPRE_Enum;
/**
 * @brief Active polarity of RTC output
 */
typedef enum
{
  RTC_ROAP_HIGH = 0,              /*!< Active level is high                                                 */
  RTC_ROAP_LOW                    /*!< Active level is low                                                  */
} RTC_ROAP_Enum;
/**
 * @brief Waveform mode of RTC output
 */
typedef enum
{
  RTC_ROWM_PULSE = 0,              /*!< Pulse mode.                                                         */
  RTC_ROWM_LEVEL                   /*!< Level mode.                                                         */
} RTC_ROWM_Enum;
/**
 * @brief Waveform mode of RTC output
 */
typedef enum
{
  RTC_ROES_MATCH = 0,              /*!< Selected RTC compare match.                                         */
  RTC_ROES_SECOND                  /*!< Selected RTC second clock.                                          */
} RTC_ROES_Enum;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup RTC_Exported_Constants RTC exported constants
  * @{
  */

/** @defgroup RTC_WAKEUP  Selection of RTC wakeup source
  * @{
  */
#define RTC_WAKEUP_CSEC   0x00000100
#define RTC_WAKEUP_CM     0x00000200
#define RTC_WAKEUP_OV     0x00000400
/**
  * @}
  */

/** @defgroup RTC_IT RTC Selection of interrupt source
  * @{
  */
#define RTC_INT_CSEC      0x00000001
#define RTC_INT_CM        0x00000002
#define RTC_INT_OV        0x00000004
/**
  * @}
  */

/** @defgroup RTC_FLAG RTC Definitions of flags
  * @{
  */
#define RTC_FLAG_CSEC     0x00000001
#define RTC_FLAG_CM       0x00000002
#define RTC_FLAG_OV       0x00000004
/**
  * @}
  */

/** @defgroup RTC_Check_Parameter Selection of Vdd18 power good
  * @{
  */

/**
 * @brief Used to check RTC_SRC_Enum parameter
 */
#define IS_RTC_SRC(x) ((x == RTC_SRC_LSI) || (x == RTC_SRC_LSE))
/**
 * @brief Used to check RTC_LSESM_Enum parameter
 */
#define IS_RTC_LSESM(x) ((x == RTC_LSESM_NORMAL) || (x == RTC_LSESM_FAST))
/**
 * @brief Used to check RTC_RPRE_Enum parameter
 */
#define IS_RTC_PSC(x) ((x == RTC_RPRE_1) || (x == RTC_RPRE_2) || (x == RTC_RPRE_4) ||\
                       (x == RTC_RPRE_8) || (x == RTC_RPRE_16) || (x == RTC_RPRE_32) ||\
                       (x == RTC_RPRE_64) || (x == RTC_RPRE_128) || (x == RTC_RPRE_256) ||\
                       (x == RTC_RPRE_512) || (x == RTC_RPRE_1024) || (x == RTC_RPRE_2048) ||\
                       (x == RTC_RPRE_4096) || (x == RTC_RPRE_8192) || (x == RTC_RPRE_16384) ||\
                       (x == RTC_RPRE_32768))
/**
 * @brief Used to check RTC_ROAP_Enum parameter
 */
#define IS_RTC_ROAP(x) ((x == RTC_ROAP_HIGH) || (x == RTC_ROAP_LOW))
/**
 * @brief Used to check RTC_ROWM_Enum parameter
 */
#define IS_RTC_ROWM(x) ((x == RTC_ROWM_PULSE) || (x == RTC_ROWM_LEVEL))
/**
 * @brief Used to check RTC_ROES_Enum parameter
 */
#define IS_RTC_ROES(x) ((x == RTC_ROES_MATCH) || (x == RTC_ROES_SECOND))
/**
 * @brief Used to check RTC_WAKEUP parameter
 */
#define IS_RTC_WAKEUP(x) ((((x) & (u32)0xFFFFF8FF) == 0x00) && ((x) != 0x00))
/**
 * @brief Used to check RTC_INT parameter
 */
#define IS_RTC_INT(x) ((((x) & (u32)0xFFFFFFF8) == 0x00) && ((x) != 0x00))
/**
 * @brief Used to check RTC_FLAG parameter
 */
#define IS_RTC_FLAG(x) ((((x) & (u32)0xFFFFFFF8) == 0x00) && ((x) != 0x00))
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup RTC_Exported_Functions RTC exported functions
  * @{
  */
void RTC_DeInit(void);
void RTC_ClockSourceConfig(RTC_SRC_Enum Source);
void RTC_LSESMConfig(RTC_LSESM_Enum Mode);
void RTC_LSECmd(ControlStatus NewState);
void RTC_CMPCLRCmd(ControlStatus NewState);
void RTC_SetPrescaler(RTC_RPRE_Enum Psc);
u16 RTC_GetPrescaler(void);
void RTC_Cmd(ControlStatus NewState);
u32 RTC_GetCounter(void);
void RTC_SetCompare(u32 Compare);
u32 RTC_GetCompare(void);
void RTC_WakeupConfig(u32 RTC_WAKEUP, ControlStatus NewState);
void RTC_IntConfig(u32 RTC_INT, ControlStatus NewState);
u8 RTC_GetFlagStatus(void);
void RTC_OutConfig(RTC_ROWM_Enum WMode, RTC_ROES_Enum EventSel, RTC_ROAP_Enum Pol);
void RTC_OutCmd(ControlStatus NewState);
FlagStatus RTC_GetOutStatus(void);
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

/*********************************************************************************************************//**
 * @file    ht32f5xxxx_sled.h
 * @version $Rev:: 3875         $
 * @date    $Date:: 2019-05-10 #$
 * @brief   The header file of the SLED library.
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
#ifndef __HT32F5XXXX_SLED_H
#define __HT32F5XXXX_SLED_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup SLED
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup SLED_Exported_Types SLED exported types
  * @{
  */

/**
 * @brief Enumeration of CK_SLED prescaler.
 */
typedef enum
{
  SLED_CLKPRE_DIV1 = 0,
  SLED_CLKPRE_DIV2,
  SLED_CLKPRE_DIV4,
  SLED_CLKPRE_DIV3
} SLED_CLKPRE_TypeDef;

/**
 * @brief Definition of SLED Init Structure.
 */
typedef struct
{
  u8 ClockPrescaler;
  u8 BaudRate;
  u8 T0H;
  u8 T1H;
  u8 TRST;
  u8 SyncState;
  u8 IdleState;
  u8 ResetState;
  u8 SyncMode;
  u8 OutputPolarity;
} SLED_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup SLED_Exported_Constants SLED exported constants
  * @{
  */
#define SLED_SYNC_STATE_T0              (0)
#define SLED_SYNC_STATE_T1              (1)

#define SLED_IDLE_STATE_LOW             (0)
#define SLED_IDLE_STATE_HIGH            (1)

#define SLED_RESET_STATE_LOW            (0)
#define SLED_RESET_STATE_HIGH           (1)

#define SLED_SYNC_MODE_DISABLE          (0)
#define SLED_SYNC_MODE_ENABLE           (1)

#define SLED_OUTPUT_NONINVERTING        (0)
#define SLED_OUTPUT_INVERTING           (1)

#define SLED_FIFO_LEVEL_0               (0 << 6)
#define SLED_FIFO_LEVEL_1               (1 << 6)
#define SLED_FIFO_LEVEL_2               (2 << 6)
#define SLED_FIFO_LEVEL_3               (3 << 6)

#define IS_SLED_FIFO_LEVEL(LEVEL)       ((LEVEL == SLED_FIFO_LEVEL_0) || \
                                         (LEVEL == SLED_FIFO_LEVEL_1) || \
                                         (LEVEL == SLED_FIFO_LEVEL_2) || \
                                         (LEVEL == SLED_FIFO_LEVEL_3))

#define IS_SLED(SLED)                   ((SLED == HT_SLED0) || (SLED == HT_SLED1))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup SLED_Exported_Functions SLED exported functions
  * @{
  */
void SLED_DeInit(HT_SLED_TypeDef* SLEDx);
void SLED_Init(HT_SLED_TypeDef* SLEDx, SLED_InitTypeDef* SLED_InitStruct);

void SLED_Cmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState);
void SLED_OutputCmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState);
void SLED_PDMACmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState);

void SLED_IntCmd(HT_SLED_TypeDef* SLEDx, ControlStatus NewState);
void SLED_ClearIntFlag(HT_SLED_TypeDef* SLEDx);

void SLED_InsertResetCode(HT_SLED_TypeDef* SLEDx);
FlagStatus SLED_GetResetCodeStatus(HT_SLED_TypeDef* SLEDx);

FlagStatus SLED_GetBusyStatus(HT_SLED_TypeDef* SLEDx);

void SLED_FIFOTrigLevelConfig(HT_SLED_TypeDef* SLEDx, u8 FifoLevel);
u8 SLED_GetFIFOStatus(HT_SLED_TypeDef* SLEDx);
void SLED_FIFOReset(HT_SLED_TypeDef* SLEDx);
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

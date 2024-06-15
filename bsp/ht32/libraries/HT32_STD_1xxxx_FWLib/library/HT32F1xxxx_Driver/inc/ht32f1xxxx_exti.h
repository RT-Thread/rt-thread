/*********************************************************************************************************//**
 * @file    ht32f1xxxx_exti.h
 * @version $Rev:: 2971         $
 * @date    $Date:: 2023-10-25 #$
 * @brief   The header file of the EXTI library.
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
#ifndef __HT32F1XXXX_EXTI_H
#define __HT32F1XXXX_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F1xxxx_Peripheral_Driver HT32F1xxxx Peripheral Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macro EXTI exported macros
  * @{
  */
/*********************************************************************************************************//**
 * @brief Convert the pin number of GPIO to the channel of EXTI.
 * @param n: can be 0, 1 to 15 to select the pin number of GPIO.
 ************************************************************************************************************/
#define  GPIO2EXTI(n)                             (n)
#define  EXTI_GetIRQn(ch)                         gEXTIn_IRQn[ch]
/**
  * @}
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Types EXTI exported types
  * @{
  */

/* Definitions of EXTI interrupt line                                                                       */
typedef enum
{
  EXTI_CHANNEL_0 = 0,
  EXTI_CHANNEL_1,
  EXTI_CHANNEL_2,
  EXTI_CHANNEL_3,
  EXTI_CHANNEL_4,
  EXTI_CHANNEL_5,
  EXTI_CHANNEL_6,
  EXTI_CHANNEL_7,
  EXTI_CHANNEL_8,
  EXTI_CHANNEL_9,
  EXTI_CHANNEL_10,
  EXTI_CHANNEL_11,
  EXTI_CHANNEL_12,
  EXTI_CHANNEL_13,
  EXTI_CHANNEL_14,
  EXTI_CHANNEL_15,
} EXTI_Channel_TypeDef;

#define IS_EXTI_CHANNEL(CHANNEL)                    ((CHANNEL == EXTI_CHANNEL_0) || \
                                                     (CHANNEL == EXTI_CHANNEL_1) || \
                                                     (CHANNEL == EXTI_CHANNEL_2) || \
                                                     (CHANNEL == EXTI_CHANNEL_3) || \
                                                     (CHANNEL == EXTI_CHANNEL_4) || \
                                                     (CHANNEL == EXTI_CHANNEL_5) || \
                                                     (CHANNEL == EXTI_CHANNEL_6) || \
                                                     (CHANNEL == EXTI_CHANNEL_7) || \
                                                     (CHANNEL == EXTI_CHANNEL_8) || \
                                                     (CHANNEL == EXTI_CHANNEL_9) || \
                                                     (CHANNEL == EXTI_CHANNEL_10) || \
                                                     (CHANNEL == EXTI_CHANNEL_11) || \
                                                     (CHANNEL == EXTI_CHANNEL_12) || \
                                                     (CHANNEL == EXTI_CHANNEL_13) || \
                                                     (CHANNEL == EXTI_CHANNEL_14) || \
                                                     (CHANNEL == EXTI_CHANNEL_15))

/* Definitions of EXTI init structure                                                                       */
typedef enum
{
  EXTI_LOW_LEVEL     = 0x0,
  EXTI_HIGH_LEVEL    = 0x1,
  EXTI_NEGATIVE_EDGE = 0x2,
  EXTI_POSITIVE_EDGE = 0x3,
  EXTI_BOTH_EDGE     = 0x4
} EXTI_Interrupt_TypeDef;

#define IS_EXTI_INT_TYPE(TYPE)                      ((TYPE == EXTI_LOW_LEVEL) || \
                                                     (TYPE == EXTI_HIGH_LEVEL) || \
                                                     (TYPE == EXTI_NEGATIVE_EDGE) || \
                                                     (TYPE == EXTI_POSITIVE_EDGE) || \
                                                     (TYPE == EXTI_BOTH_EDGE))

typedef enum
{
  EXTI_DEBOUNCE_DISABLE = 0x0,
  EXTI_DEBOUNCE_ENABLE  = 0x1
} EXTI_Deb_TypeDef;

#define IS_EXTI_DEBOUNCE_TYPE(TYPE)                 ((TYPE == EXTI_DEBOUNCE_DISABLE) || \
                                                     (TYPE == EXTI_DEBOUNCE_ENABLE))

typedef struct
{
  u32 EXTI_Channel;
  EXTI_Deb_TypeDef EXTI_Debounce;
  #if (LIBCFG_EXTI_8BIT_DEBOUNCE_COUNTER)
  u8 EXTI_DebounceCnt;
  #else
  u16 EXTI_DebounceCnt;
  #endif
  EXTI_Interrupt_TypeDef EXTI_IntType;
} EXTI_InitTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI exported constants
  * @{
  */

/* Definitions of EXTI wake up polarity                                                                     */
#define EXTI_WAKEUP_HIGH_LEVEL                      ((u8)0x0)
#define EXTI_WAKEUP_LOW_LEVEL                       ((u8)0x1)

#define IS_EXTI_WAKEUP_TYPE(TYPE)                   ((TYPE == EXTI_WAKEUP_HIGH_LEVEL) || \
                                                     (TYPE == EXTI_WAKEUP_LOW_LEVEL))


#define EXTI_EDGE_POSITIVE                          ((u8)0x0)
#define EXTI_EDGE_NEGATIVE                          ((u8)0x1)

#define IS_EXTI_EDGE(EDGE)                          ((EDGE == EXTI_EDGE_POSITIVE) || \
                                                     (EDGE == EXTI_EDGE_NEGATIVE))

#if (LIBCFG_EXTI_8BIT_DEBOUNCE_COUNTER)
#define IS_EXTI_DEBOUNCE_SIZE(SIZE)                 (SIZE <= 0xFF)
#else
#define IS_EXTI_DEBOUNCE_SIZE(SIZE)                 (SIZE <= 0xFFFF)
#endif

extern const IRQn_Type gEXTIn_IRQn[16];

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Functions EXTI exported functions
  * @{
  */
void EXTI_DeInit(u32 EXTI_Channel);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_IntConfig(u32 EXTI_Channel, ControlStatus NewState);
void EXTI_WakeupEventConfig(u32 EXTI_Channel, u8 EXTI_WakeUpType, ControlStatus NewState);
void EXTI_WakeupEventIntConfig(ControlStatus NewState);
void EXTI_ClearEdgeFlag(u32 EXTI_Channel);
void EXTI_ClearWakeupFlag(u32 EXTI_Channel);
FlagStatus EXTI_GetEdgeFlag(u32 EXTI_Channel);
FlagStatus EXTI_GetEdgeStatus(u32 EXTI_Channel, u32 EXTI_Edge);
FlagStatus EXTI_GetWakeupFlagStatus(u32 EXTI_Channel);
void EXTI_SWIntCmd(u32 EXTI_Channel, ControlStatus NewState);
FlagStatus EXTI_GetSWCmdStatus(u32 EXTI_Channel);
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

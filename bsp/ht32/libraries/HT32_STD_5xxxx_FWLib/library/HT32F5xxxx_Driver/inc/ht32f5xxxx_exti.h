/*********************************************************************************************************//**
 * @file    ht32f5xxxx_exti.h
 * @version $Rev:: 6496         $
 * @date    $Date:: 2022-11-28 #$
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
#ifndef __HT32F5XXXX_EXTI_H
#define __HT32F5XXXX_EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
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
#if (LIBCFG_EXTI_8CH)
  #define  GPIO2EXTI(n)                             ((n >= 8) ? (n - 8) : n)
#else
  #define  GPIO2EXTI(n)                             (n)
#endif

#define  EXTI_GetIRQn(ch)                           gEXTIn_IRQn[ch]
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
#if (!LIBCFG_EXTI_8CH)
  EXTI_CHANNEL_8,
  EXTI_CHANNEL_9,
  EXTI_CHANNEL_10,
  EXTI_CHANNEL_11,
  EXTI_CHANNEL_12,
  EXTI_CHANNEL_13,
  EXTI_CHANNEL_14,
  EXTI_CHANNEL_15,
#endif
} EXTI_Channel_TypeDef;

#if (LIBCFG_EXTI_8CH)
#define IS_CHANNEL_8(x)                             (0)
#define IS_CHANNEL_9(x)                             (0)
#define IS_CHANNEL_10(x)                            (0)
#define IS_CHANNEL_11(x)                            (0)
#define IS_CHANNEL_12(x)                            (0)
#define IS_CHANNEL_13(x)                            (0)
#define IS_CHANNEL_14(x)                            (0)
#define IS_CHANNEL_15(x)                            (0)
#else
#define IS_CHANNEL_8(x)                             (x == EXTI_CHANNEL_8)
#define IS_CHANNEL_9(x)                             (x == EXTI_CHANNEL_9)
#define IS_CHANNEL_10(x)                            (x == EXTI_CHANNEL_10)
#define IS_CHANNEL_11(x)                            (x == EXTI_CHANNEL_11)
#define IS_CHANNEL_12(x)                            (x == EXTI_CHANNEL_12)
#define IS_CHANNEL_13(x)                            (x == EXTI_CHANNEL_13)
#define IS_CHANNEL_14(x)                            (x == EXTI_CHANNEL_14)
#define IS_CHANNEL_15(x)                            (x == EXTI_CHANNEL_15)
#endif


#define IS_EXTI_CHANNEL(CHANNEL)                    ((CHANNEL == EXTI_CHANNEL_0) || \
                                                     (CHANNEL == EXTI_CHANNEL_1) || \
                                                     (CHANNEL == EXTI_CHANNEL_2) || \
                                                     (CHANNEL == EXTI_CHANNEL_3) || \
                                                     (CHANNEL == EXTI_CHANNEL_4) || \
                                                     (CHANNEL == EXTI_CHANNEL_5) || \
                                                     (CHANNEL == EXTI_CHANNEL_6) || \
                                                     (CHANNEL == EXTI_CHANNEL_7) || \
                                                     IS_CHANNEL_8(CHANNEL) || \
                                                     IS_CHANNEL_9(CHANNEL) || \
                                                     IS_CHANNEL_10(CHANNEL) || \
                                                     IS_CHANNEL_11(CHANNEL) || \
                                                     IS_CHANNEL_12(CHANNEL) || \
                                                     IS_CHANNEL_13(CHANNEL) || \
                                                     IS_CHANNEL_14(CHANNEL) || \
                                                     IS_CHANNEL_15(CHANNEL))


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

#if (LIBCFG_EXTI_DEBCNTPRE)
typedef enum
{
  EXTI_DBCNTPRE_DIV1   = 0,
  EXTI_DBCNTPRE_DIV2,
  EXTI_DBCNTPRE_DIV4,
  EXTI_DBCNTPRE_DIV8,
  EXTI_DBCNTPRE_DIV16,
  EXTI_DBCNTPRE_DIV32,
  EXTI_DBCNTPRE_DIV64,
  EXTI_DBCNTPRE_DIV128,
} EXTI_DebCntPre_TypeDef;

#define IS_EXTI_DEBOUNCE_COUNTER_PRESCALER(TYPE)    ((TYPE == EXTI_DBCNTPRE_DIV1) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV2) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV4) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV8) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV16) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV32) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV64) || \
                                                     (TYPE == EXTI_DBCNTPRE_DIV128))
#endif

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
#if (LIBCFG_EXTI_DEBCNTPRE)
void EXTI_SetDebounceCounterPrescaler(EXTI_DebCntPre_TypeDef EXTI_DBCNTPRE_DIVn);
#endif
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

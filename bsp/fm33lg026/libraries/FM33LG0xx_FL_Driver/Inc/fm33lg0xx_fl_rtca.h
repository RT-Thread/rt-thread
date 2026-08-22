/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_rtca.h
  * @author  FMSH Application Team
  * @brief   Head file of RTCA FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LG0XX_FL_RTCA_H
#define __FM33LG0XX_FL_RTCA_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup RTCA RTCA
  * @brief RTCA FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RTCA_FL_ES_INIT RTCA Exported Init structures
  * @{
  */

/**
  * @brief FL RTCA Init Sturcture definition
  */
typedef struct
{
    /** 年 */
    uint32_t year;
    /** 月 */
    uint32_t month;
    /** 日 */
    uint32_t day;
    /** 周 */
    uint32_t week;
    /** 时 */
    uint32_t hour;
    /** 分 */
    uint32_t minute;
    /** 秒 */
    uint32_t second;

} FL_RTCA_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RTCA_FL_Exported_Constants RTCA Exported Constants
  * @{
  */

#define    RTCA_IER_ADJ_IE_Pos                                    (12U)
#define    RTCA_IER_ADJ_IE_Msk                                    (0x1U << RTCA_IER_ADJ_IE_Pos)
#define    RTCA_IER_ADJ_IE                                        RTCA_IER_ADJ_IE_Msk

#define    RTCA_IER_ALARM_IE_Pos                                  (11U)
#define    RTCA_IER_ALARM_IE_Msk                                  (0x1U << RTCA_IER_ALARM_IE_Pos)
#define    RTCA_IER_ALARM_IE                                      RTCA_IER_ALARM_IE_Msk

#define    RTCA_IER_1KHZ_IE_Pos                                   (10U)
#define    RTCA_IER_1KHZ_IE_Msk                                   (0x1U << RTCA_IER_1KHZ_IE_Pos)
#define    RTCA_IER_1KHZ_IE                                       RTCA_IER_1KHZ_IE_Msk

#define    RTCA_IER_256HZ_IE_Pos                                  (9U)
#define    RTCA_IER_256HZ_IE_Msk                                  (0x1U << RTCA_IER_256HZ_IE_Pos)
#define    RTCA_IER_256HZ_IE                                      RTCA_IER_256HZ_IE_Msk

#define    RTCA_IER_64HZ_IE_Pos                                   (8U)
#define    RTCA_IER_64HZ_IE_Msk                                   (0x1U << RTCA_IER_64HZ_IE_Pos)
#define    RTCA_IER_64HZ_IE                                       RTCA_IER_64HZ_IE_Msk

#define    RTCA_IER_16HZ_IE_Pos                                   (7U)
#define    RTCA_IER_16HZ_IE_Msk                                   (0x1U << RTCA_IER_16HZ_IE_Pos)
#define    RTCA_IER_16HZ_IE                                       RTCA_IER_16HZ_IE_Msk

#define    RTCA_IER_8HZ_IE_Pos                                    (6U)
#define    RTCA_IER_8HZ_IE_Msk                                    (0x1U << RTCA_IER_8HZ_IE_Pos)
#define    RTCA_IER_8HZ_IE                                        RTCA_IER_8HZ_IE_Msk

#define    RTCA_IER_4HZ_IE_Pos                                    (5U)
#define    RTCA_IER_4HZ_IE_Msk                                    (0x1U << RTCA_IER_4HZ_IE_Pos)
#define    RTCA_IER_4HZ_IE                                        RTCA_IER_4HZ_IE_Msk

#define    RTCA_IER_2HZ_IE_Pos                                    (4U)
#define    RTCA_IER_2HZ_IE_Msk                                    (0x1U << RTCA_IER_2HZ_IE_Pos)
#define    RTCA_IER_2HZ_IE                                        RTCA_IER_2HZ_IE_Msk

#define    RTCA_IER_SEC_IE_Pos                                    (3U)
#define    RTCA_IER_SEC_IE_Msk                                    (0x1U << RTCA_IER_SEC_IE_Pos)
#define    RTCA_IER_SEC_IE                                        RTCA_IER_SEC_IE_Msk

#define    RTCA_IER_MIN_IE_Pos                                    (2U)
#define    RTCA_IER_MIN_IE_Msk                                    (0x1U << RTCA_IER_MIN_IE_Pos)
#define    RTCA_IER_MIN_IE                                        RTCA_IER_MIN_IE_Msk

#define    RTCA_IER_HOUR_IE_Pos                                   (1U)
#define    RTCA_IER_HOUR_IE_Msk                                   (0x1U << RTCA_IER_HOUR_IE_Pos)
#define    RTCA_IER_HOUR_IE                                       RTCA_IER_HOUR_IE_Msk

#define    RTCA_IER_DAY_IE_Pos                                    (0U)
#define    RTCA_IER_DAY_IE_Msk                                    (0x1U << RTCA_IER_DAY_IE_Pos)
#define    RTCA_IER_DAY_IE                                        RTCA_IER_DAY_IE_Msk

#define    RTCA_ISR_ADJ_IF_Pos                                    (12U)
#define    RTCA_ISR_ADJ_IF_Msk                                    (0x1U << RTCA_ISR_ADJ_IF_Pos)
#define    RTCA_ISR_ADJ_IF                                        RTCA_ISR_ADJ_IF_Msk

#define    RTCA_ISR_ALARM_IF_Pos                                  (11U)
#define    RTCA_ISR_ALARM_IF_Msk                                  (0x1U << RTCA_ISR_ALARM_IF_Pos)
#define    RTCA_ISR_ALARM_IF                                      RTCA_ISR_ALARM_IF_Msk

#define    RTCA_ISR_1KHZ_IF_Pos                                   (10U)
#define    RTCA_ISR_1KHZ_IF_Msk                                   (0x1U << RTCA_ISR_1KHZ_IF_Pos)
#define    RTCA_ISR_1KHZ_IF                                       RTCA_ISR_1KHZ_IF_Msk

#define    RTCA_ISR_256HZ_IF_Pos                                  (9U)
#define    RTCA_ISR_256HZ_IF_Msk                                  (0x1U << RTCA_ISR_256HZ_IF_Pos)
#define    RTCA_ISR_256HZ_IF                                      RTCA_ISR_256HZ_IF_Msk

#define    RTCA_ISR_64HZ_IF_Pos                                   (8U)
#define    RTCA_ISR_64HZ_IF_Msk                                   (0x1U << RTCA_ISR_64HZ_IF_Pos)
#define    RTCA_ISR_64HZ_IF                                       RTCA_ISR_64HZ_IF_Msk

#define    RTCA_ISR_16HZ_IF_Pos                                   (7U)
#define    RTCA_ISR_16HZ_IF_Msk                                   (0x1U << RTCA_ISR_16HZ_IF_Pos)
#define    RTCA_ISR_16HZ_IF                                       RTCA_ISR_16HZ_IF_Msk

#define    RTCA_ISR_8HZ_IF_Pos                                    (6U)
#define    RTCA_ISR_8HZ_IF_Msk                                    (0x1U << RTCA_ISR_8HZ_IF_Pos)
#define    RTCA_ISR_8HZ_IF                                        RTCA_ISR_8HZ_IF_Msk

#define    RTCA_ISR_4HZ_IF_Pos                                    (5U)
#define    RTCA_ISR_4HZ_IF_Msk                                    (0x1U << RTCA_ISR_4HZ_IF_Pos)
#define    RTCA_ISR_4HZ_IF                                        RTCA_ISR_4HZ_IF_Msk

#define    RTCA_ISR_2HZ_IF_Pos                                    (4U)
#define    RTCA_ISR_2HZ_IF_Msk                                    (0x1U << RTCA_ISR_2HZ_IF_Pos)
#define    RTCA_ISR_2HZ_IF                                        RTCA_ISR_2HZ_IF_Msk

#define    RTCA_ISR_SEC_IF_Pos                                    (3U)
#define    RTCA_ISR_SEC_IF_Msk                                    (0x1U << RTCA_ISR_SEC_IF_Pos)
#define    RTCA_ISR_SEC_IF                                        RTCA_ISR_SEC_IF_Msk

#define    RTCA_ISR_MIN_IF_Pos                                    (2U)
#define    RTCA_ISR_MIN_IF_Msk                                    (0x1U << RTCA_ISR_MIN_IF_Pos)
#define    RTCA_ISR_MIN_IF                                        RTCA_ISR_MIN_IF_Msk

#define    RTCA_ISR_HOUR_IF_Pos                                   (1U)
#define    RTCA_ISR_HOUR_IF_Msk                                   (0x1U << RTCA_ISR_HOUR_IF_Pos)
#define    RTCA_ISR_HOUR_IF                                       RTCA_ISR_HOUR_IF_Msk

#define    RTCA_ISR_DAY_IF_Pos                                    (0U)
#define    RTCA_ISR_DAY_IF_Msk                                    (0x1U << RTCA_ISR_DAY_IF_Pos)
#define    RTCA_ISR_DAY_IF                                        RTCA_ISR_DAY_IF_Msk

#define    RTCA_TMSEL_TMSEL_Pos                                   (0U)
#define    RTCA_TMSEL_TMSEL_Msk                                   (0xfU << RTCA_TMSEL_TMSEL_Pos)
#define    RTCA_TMSEL_TMSEL                                       RTCA_TMSEL_TMSEL_Msk

#define    RTCA_ADJUST_ADSIGN_Pos                                 (9U)
#define    RTCA_ADJUST_ADSIGN_Msk                                 (0x1U << RTCA_ADJUST_ADSIGN_Pos)
#define    RTCA_ADJUST_ADSIGN                                     RTCA_ADJUST_ADSIGN_Msk

#define    RTCA_CR_EN_Pos                                         (0U)
#define    RTCA_CR_EN_Msk                                         (0x1U << RTCA_CR_EN_Pos)
#define    RTCA_CR_EN                                             RTCA_CR_EN_Msk






#define    FL_RTCA_TIME_MARK_SECOND                               (0x2U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_MINUTE                               (0x3U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_HOUR                                 (0x4U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_DAY                                  (0x5U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_ALARM                                (0x6U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_32_SEC                               (0x7U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_SECOND_REVERSE                       (0x9U << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_MINUTE_REVERSE                       (0xaU << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_HOUR_REVERSE                         (0xbU << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_DAY_REVERSE                          (0xcU << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_ALARM_REVERSE                        (0xdU << RTCA_TMSEL_TMSEL_Pos)
#define    FL_RTCA_TIME_MARK_SEC                                  (0xfU << RTCA_TMSEL_TMSEL_Pos)


#define    FL_RTCA_ADJUST_DIR_INCREASE                            (0x0U << RTCA_ADJUST_ADSIGN_Pos)
#define    FL_RTCA_ADJUST_DIR_DECREASE                            (0x1U << RTCA_ADJUST_ADSIGN_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RTCA_FL_Exported_Functions RTCA Exported Functions
  * @{
  */

/**
  * @brief    Enable RTCA Config Time
  * @rmtoll   WER        FL_RTCA_WriteEnable
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteEnable(RTCA_Type *RTCAx)
{
    RTCAx->WER = 0xACACACAC;
}

/**
  * @brief    Disable RTCA Config Time
  * @rmtoll   WER        FL_RTCA_WriteDisable
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteDisable(RTCA_Type *RTCAx)
{
    RTCAx->WER = 0x5A5A5A5A;
}

/**
  * @brief    Enable RTCA Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTCA_EnableIT_Adjust
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Adjust(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_ADJ_IE_Msk);
}

/**
  * @brief    Get RTCA Time Adjust Interrupt Enable Status
  * @rmtoll   IER    ADJ_IE    FL_RTCA_IsEnabledIT_Adjust
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Adjust(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_ADJ_IE_Msk) == RTCA_IER_ADJ_IE_Msk);
}

/**
  * @brief    Disable RTCA Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTCA_DisableIT_Adjust
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Adjust(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_ADJ_IE_Msk);
}

/**
  * @brief    Enable RTCA Alarm Interrupt
  * @rmtoll   IER    ALARM_IE    FL_RTCA_EnableIT_Alarm
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Alarm(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_ALARM_IE_Msk);
}

/**
  * @brief    Get RTCA Alarm Interrupt Enable Status
  * @rmtoll   IER    ALARM_IE    FL_RTCA_IsEnabledIT_Alarm
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Alarm(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_ALARM_IE_Msk) == RTCA_IER_ALARM_IE_Msk);
}

/**
  * @brief    Disable RTCA Alarm    Interrupt
  * @rmtoll   IER    ALARM_IE    FL_RTCA_DisableIT_Alarm
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Alarm(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_ALARM_IE_Msk);
}

/**
  * @brief    Enable RTCA 1KHz Interrupt
  * @rmtoll   IER    1KHZ_IE    FL_RTCA_EnableIT_1KHz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_1KHz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Get RTCA 1KHz Interrupt Enable Status
  * @rmtoll   IER    1KHZ_IE    FL_RTCA_IsEnabledIT_1KHz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_1KHz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_1KHZ_IE_Msk) == RTCA_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 1KHz Interrupt
  * @rmtoll   IER    1KHZ_IE    FL_RTCA_DisableIT_1KHz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_1KHz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 256Hz Interrupt
  * @rmtoll   IER    256HZ_IE    FL_RTCA_EnableIT_256Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_256Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_256HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 256Hz Interrupt Enable Status
  * @rmtoll   IER    256HZ_IE    FL_RTCA_IsEnabledIT_256Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_256Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_256HZ_IE_Msk) == RTCA_IER_256HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 256Hz Interrupt
  * @rmtoll   IER    256HZ_IE    FL_RTCA_DisableIT_256Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_256Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_256HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 64Hz Interrupt
  * @rmtoll   IER    64HZ_IE    FL_RTCA_EnableIT_64Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_64Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_64HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 64Hz Interrupt Enable Status
  * @rmtoll   IER    64HZ_IE    FL_RTCA_IsEnabledIT_64Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_64Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_64HZ_IE_Msk) == RTCA_IER_64HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 64Hz Interrupt
  * @rmtoll   IER    64HZ_IE    FL_RTCA_DisableIT_64Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_64Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_64HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 16Hz Interrupt
  * @rmtoll   IER    16HZ_IE    FL_RTCA_EnableIT_16Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_16Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_16HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 16Hz Interrupt Enable Status
  * @rmtoll   IER    16HZ_IE    FL_RTCA_IsEnabledIT_16Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_16Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_16HZ_IE_Msk) == RTCA_IER_16HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 16Hz Interrupt
  * @rmtoll   IER    16HZ_IE    FL_RTCA_DisableIT_16Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_16Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_16HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 8Hz Interrupt
  * @rmtoll   IER    8HZ_IE    FL_RTCA_EnableIT_8Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_8Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_8HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 8Hz Interrupt Enable Status
  * @rmtoll   IER    8HZ_IE    FL_RTCA_IsEnabledIT_8Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_8Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_8HZ_IE_Msk) == RTCA_IER_8HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 8Hz Interrupt
  * @rmtoll   IER    8HZ_IE    FL_RTCA_DisableIT_8Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_8Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_8HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 4Hz Interrupt
  * @rmtoll   IER    4HZ_IE    FL_RTCA_EnableIT_4Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_4Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_4HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 4Hz Interrupt Enable Status
  * @rmtoll   IER    4HZ_IE    FL_RTCA_IsEnabledIT_4Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_4Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_4HZ_IE_Msk) == RTCA_IER_4HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 4Hz Interrupt
  * @rmtoll   IER    4HZ_IE    FL_RTCA_DisableIT_4Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_4Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_4HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA 2Hz Interrupt
  * @rmtoll   IER    2HZ_IE    FL_RTCA_EnableIT_2Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_2Hz(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_2HZ_IE_Msk);
}

/**
  * @brief    Get RTCA 2Hz Interrupt Enable Status
  * @rmtoll   IER    2HZ_IE    FL_RTCA_IsEnabledIT_2Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_2Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_2HZ_IE_Msk) == RTCA_IER_2HZ_IE_Msk);
}

/**
  * @brief    Disable RTCA 2Hz Interrupt
  * @rmtoll   IER    2HZ_IE    FL_RTCA_DisableIT_2Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_2Hz(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_2HZ_IE_Msk);
}

/**
  * @brief    Enable RTCA Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTCA_EnableIT_Second
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Second(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_SEC_IE_Msk);
}

/**
  * @brief    Get RTCA Second Interrupt Enable Status
  * @rmtoll   IER    SEC_IE    FL_RTCA_IsEnabledIT_Second
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Second(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_SEC_IE_Msk) == RTCA_IER_SEC_IE_Msk);
}

/**
  * @brief    Disable RTCA Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTCA_DisableIT_Second
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Second(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_SEC_IE_Msk);
}

/**
  * @brief    Enable RTCA Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTCA_EnableIT_Minute
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Minute(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_MIN_IE_Msk);
}

/**
  * @brief    Get RTCA Minute Interrupt Enable Status
  * @rmtoll   IER    MIN_IE    FL_RTCA_IsEnabledIT_Minute
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Minute(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_MIN_IE_Msk) == RTCA_IER_MIN_IE_Msk);
}

/**
  * @brief    Disable RTCA Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTCA_DisableIT_Minute
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Minute(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_MIN_IE_Msk);
}

/**
  * @brief    Enable RTCA Hour Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTCA_EnableIT_Hour
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Hour(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_HOUR_IE_Msk);
}

/**
  * @brief    Get RTCA Hour Interrupt Enable Status
  * @rmtoll   IER    HOUR_IE    FL_RTCA_IsEnabledIT_Hour
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Hour(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_HOUR_IE_Msk) == RTCA_IER_HOUR_IE_Msk);
}

/**
  * @brief    Disable RTCA Hour  Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTCA_DisableIT_Hour
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Hour(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_HOUR_IE_Msk);
}

/**
  * @brief    Enable RTCA Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTCA_EnableIT_Day
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_EnableIT_Day(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->IER, RTCA_IER_DAY_IE_Msk);
}

/**
  * @brief    Get RTCA Day Interrupt Enable Status
  * @rmtoll   IER    DAY_IE    FL_RTCA_IsEnabledIT_Day
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabledIT_Day(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->IER, RTCA_IER_DAY_IE_Msk) == RTCA_IER_DAY_IE_Msk);
}

/**
  * @brief    Disable RTCA Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTCA_DisableIT_Day
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_DisableIT_Day(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->IER, RTCA_IER_DAY_IE_Msk);
}

/**
  * @brief    Clear RTCA Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTCA_ClearFlag_Adjust
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Adjust(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_ADJ_IF_Msk);
}

/**
  * @brief    Get RTCA Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTCA_IsActiveFlag_Adjust
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Adjust(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_ADJ_IF_Msk) == (RTCA_ISR_ADJ_IF_Msk));
}

/**
  * @brief    Clear RTCA Alarm Interrupt Flag
  * @rmtoll   ISR    ALARM_IF    FL_RTCA_ClearFlag_Alarm
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Alarm(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_ALARM_IF_Msk);
}

/**
  * @brief    Get RTCA Alarm Interrupt Flag
  * @rmtoll   ISR    ALARM_IF    FL_RTCA_IsActiveFlag_Alarm
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Alarm(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_ALARM_IF_Msk) == (RTCA_ISR_ALARM_IF_Msk));
}

/**
  * @brief    Clear RTCA 1KHz Interrupt Flag
  * @rmtoll   ISR    1KHZ_IF    FL_RTCA_ClearFlag_1KHz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_1KHz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_1KHZ_IF_Msk);
}

/**
  * @brief    Get RTCA 1KHz Interrupt Flag
  * @rmtoll   ISR    1KHZ_IF    FL_RTCA_IsActiveFlag_1KHz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_1KHz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_1KHZ_IF_Msk) == (RTCA_ISR_1KHZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 256Hz Interrupt Flag
  * @rmtoll   ISR    256HZ_IF    FL_RTCA_ClearFlag_256Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_256Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_256HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 256Hz Interrupt Flag
  * @rmtoll   ISR    256HZ_IF    FL_RTCA_IsActiveFlag_256Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_256Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_256HZ_IF_Msk) == (RTCA_ISR_256HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 64Hz Interrupt Flag
  * @rmtoll   ISR    64HZ_IF    FL_RTCA_ClearFlag_64Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_64Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_64HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 64Hz Interrupt Flag
  * @rmtoll   ISR    64HZ_IF    FL_RTCA_IsActiveFlag_64Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_64Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_64HZ_IF_Msk) == (RTCA_ISR_64HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 16Hz Interrupt Flag
  * @rmtoll   ISR    16HZ_IF    FL_RTCA_ClearFlag_16Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_16Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_16HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 16Hz Interrupt Flag
  * @rmtoll   ISR    16HZ_IF    FL_RTCA_IsActiveFlag_16Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_16Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_16HZ_IF_Msk) == (RTCA_ISR_16HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 8Hz Interrupt Flag
  * @rmtoll   ISR    8HZ_IF    FL_RTCA_ClearFlag_8Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_8Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_8HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 8Hz Interrupt Flag
  * @rmtoll   ISR    8HZ_IF    FL_RTCA_IsActiveFlag_8Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_8Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_8HZ_IF_Msk) == (RTCA_ISR_8HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 4Hz Interrupt Flag
  * @rmtoll   ISR    4HZ_IF    FL_RTCA_ClearFlag_4Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_4Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_4HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 4Hz Interrupt Flag
  * @rmtoll   ISR    4HZ_IF    FL_RTCA_IsActiveFlag_4Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_4Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_4HZ_IF_Msk) == (RTCA_ISR_4HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA 2Hz Interrupt Flag
  * @rmtoll   ISR    2HZ_IF    FL_RTCA_ClearFlag_2Hz
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_2Hz(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_2HZ_IF_Msk);
}

/**
  * @brief    Get RTCA 2Hz Interrupt Flag
  * @rmtoll   ISR    2HZ_IF    FL_RTCA_IsActiveFlag_2Hz
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_2Hz(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_2HZ_IF_Msk) == (RTCA_ISR_2HZ_IF_Msk));
}

/**
  * @brief    Clear RTCA Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTCA_ClearFlag_Second
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Second(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_SEC_IF_Msk);
}

/**
  * @brief    Get RTCA Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTCA_IsActiveFlag_Second
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Second(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_SEC_IF_Msk) == (RTCA_ISR_SEC_IF_Msk));
}

/**
  * @brief    Clear RTCA Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTCA_ClearFlag_Minute
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Minute(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_MIN_IF_Msk);
}

/**
  * @brief    Get RTCA Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTCA_IsActiveFlag_Minute
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Minute(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_MIN_IF_Msk) == (RTCA_ISR_MIN_IF_Msk));
}

/**
  * @brief    Clear RTCA Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTCA_ClearFlag_Hour
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Hour(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_HOUR_IF_Msk);
}

/**
  * @brief    Get RTCA Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTCA_IsActiveFlag_Hour
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Hour(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_HOUR_IF_Msk) == (RTCA_ISR_HOUR_IF_Msk));
}

/**
  * @brief    Clear RTCA Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTCA_ClearFlag_Day
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_ClearFlag_Day(RTCA_Type *RTCAx)
{
    WRITE_REG(RTCAx->ISR, RTCA_ISR_DAY_IF_Msk);
}

/**
  * @brief    Get RTCA Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTCA_IsActiveFlag_Day
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsActiveFlag_Day(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ISR, RTCA_ISR_DAY_IF_Msk) == (RTCA_ISR_DAY_IF_Msk));
}

/**
  * @brief    Get RTCA Second Value
  * @rmtoll   BCDSEC        FL_RTCA_ReadSecond
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadSecond(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDSEC, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Second Value
  * @rmtoll   BCDSEC        FL_RTCA_WriteSecond
  * @param    RTCAx RTCA instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteSecond(RTCA_Type *RTCAx, uint32_t second)
{
    MODIFY_REG(RTCAx->BCDSEC, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Get RTCA Minute Value
  * @rmtoll   BCDMIN        FL_RTCA_ReadMinute
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadMinute(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDMIN, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Minute Value
  * @rmtoll   BCDMIN        FL_RTCA_WriteMinute
  * @param    RTCAx RTCA instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteMinute(RTCA_Type *RTCAx, uint32_t minute)
{
    MODIFY_REG(RTCAx->BCDMIN, (0x7fU << 0U), (minute << 0U));
}

/**
  * @brief    Get RTCA Hour Value
  * @rmtoll   BCDHOUR        FL_RTCA_ReadHour
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadHour(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDHOUR, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Hour Value
  * @rmtoll   BCDHOUR        FL_RTCA_WriteHour
  * @param    RTCAx RTCA instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteHour(RTCA_Type *RTCAx, uint32_t hour)
{
    MODIFY_REG(RTCAx->BCDHOUR, (0x3fU << 0U), (hour << 0U));
}

/**
  * @brief    Get RTCA Day Value
  * @rmtoll   BCDDAY        FL_RTCA_ReadDay
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadDay(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDDAY, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Day Value
  * @rmtoll   BCDDAY        FL_RTCA_WriteDay
  * @param    RTCAx RTCA instance
  * @param    day
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteDay(RTCA_Type *RTCAx, uint32_t day)
{
    MODIFY_REG(RTCAx->BCDDAY, (0x3fU << 0U), (day << 0U));
}

/**
  * @brief    Get RTCA Week Value
  * @rmtoll   BCDWEEK        FL_RTCA_ReadWeek
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadWeek(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDWEEK, (0x7U << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Week Value
  * @rmtoll   BCDWEEK        FL_RTCA_WriteWeek
  * @param    RTCAx RTCA instance
  * @param    week
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteWeek(RTCA_Type *RTCAx, uint32_t week)
{
    MODIFY_REG(RTCAx->BCDWEEK, (0x7U << 0U), (week << 0U));
}

/**
  * @brief    Get RTCA Month Value
  * @rmtoll   BCDMONTH        FL_RTCA_ReadMonth
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadMonth(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDMONTH, (0x1fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Month Value
  * @rmtoll   BCDMONTH        FL_RTCA_WriteMonth
  * @param    RTCAx RTCA instance
  * @param    month
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteMonth(RTCA_Type *RTCAx, uint32_t month)
{
    MODIFY_REG(RTCAx->BCDMONTH, (0x1fU << 0U), (month << 0U));
}

/**
  * @brief    Get RTCA Year Value
  * @rmtoll   BCDYEAR        FL_RTCA_ReadYear
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadYear(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->BCDYEAR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Year Value
  * @rmtoll   BCDYEAR        FL_RTCA_WriteYear
  * @param    RTCAx RTCA instance
  * @param    year
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteYear(RTCA_Type *RTCAx, uint32_t year)
{
    MODIFY_REG(RTCAx->BCDYEAR, (0xffU << 0U), (year << 0U));
}

/**
  * @brief    Get RTCA Alarm Hour Value
  * @rmtoll   ALARM        FL_RTCA_ReadHourAlarm
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadHourAlarm(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ALARM, (0x3fU << 16U)) >> 16U);
}

/**
  * @brief    Set RTCA Alarm Hour Value
  * @rmtoll   ALARM        FL_RTCA_WriteHourAlarm
  * @param    RTCAx RTCA instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteHourAlarm(RTCA_Type *RTCAx, uint32_t hour)
{
    MODIFY_REG(RTCAx->ALARM, (0x3fU << 16U), (hour << 16U));
}

/**
  * @brief    Get RTCA Alarm Minute Value
  * @rmtoll   ALARM        FL_RTCA_ReadMinuteAlarm
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadMinuteAlarm(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ALARM, (0x7fU << 8U)) >> 8U);
}

/**
  * @brief    Set RTCA Alarm Minute Value
  * @rmtoll   ALARM        FL_RTCA_WriteMinuteAlarm
  * @param    RTCAx RTCA instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteMinuteAlarm(RTCA_Type *RTCAx, uint32_t minute)
{
    MODIFY_REG(RTCAx->ALARM, (0x7fU << 8U), (minute << 8U));
}

/**
  * @brief    Get RTCA Alarm Second Value
  * @rmtoll   ALARM        FL_RTCA_ReadSecondAlarm
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadSecondAlarm(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ALARM, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Alarm Second Value
  * @rmtoll   ALARM        FL_RTCA_WriteSecondAlarm
  * @param    RTCAx RTCA instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteSecondAlarm(RTCA_Type *RTCAx, uint32_t second)
{
    MODIFY_REG(RTCAx->ALARM, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Set RTCA Output Time Mark Signal
  * @rmtoll   TMSEL    TMSEL    FL_RTCA_SetTimeMarkOutput
  * @param    RTCAx RTCA instance
  * @param    markSelect This parameter can be one of the following values:
  *           @arg @ref FL_RTCA_TIME_MARK_SECOND
  *           @arg @ref FL_RTCA_TIME_MARK_MINUTE
  *           @arg @ref FL_RTCA_TIME_MARK_HOUR
  *           @arg @ref FL_RTCA_TIME_MARK_DAY
  *           @arg @ref FL_RTCA_TIME_MARK_ALARM
  *           @arg @ref FL_RTCA_TIME_MARK_32_SEC
  *           @arg @ref FL_RTCA_TIME_MARK_SECOND_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_MINUTE_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_HOUR_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_DAY_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_ALARM_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_SEC
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_SetTimeMarkOutput(RTCA_Type *RTCAx, uint32_t markSelect)
{
    MODIFY_REG(RTCAx->TMSEL, RTCA_TMSEL_TMSEL_Msk, markSelect);
}

/**
  * @brief    Get RTCA Output Time Mark Signal Setting
  * @rmtoll   TMSEL    TMSEL    FL_RTCA_GetTimeMarkOutput
  * @param    RTCAx RTCA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCA_TIME_MARK_SECOND
  *           @arg @ref FL_RTCA_TIME_MARK_MINUTE
  *           @arg @ref FL_RTCA_TIME_MARK_HOUR
  *           @arg @ref FL_RTCA_TIME_MARK_DAY
  *           @arg @ref FL_RTCA_TIME_MARK_ALARM
  *           @arg @ref FL_RTCA_TIME_MARK_32_SEC
  *           @arg @ref FL_RTCA_TIME_MARK_SECOND_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_MINUTE_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_HOUR_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_DAY_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_ALARM_REVERSE
  *           @arg @ref FL_RTCA_TIME_MARK_SEC
  */
__STATIC_INLINE uint32_t FL_RTCA_GetTimeMarkOutput(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->TMSEL, RTCA_TMSEL_TMSEL_Msk));
}

/**
  * @brief    Get RTCA Adjust Value
  * @rmtoll   ADJUST        FL_RTCA_ReadAdjustValue
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadAdjustValue(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ADJUST, (0x1ffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA Adjust Value
  * @rmtoll   ADJUST        FL_RTCA_WriteAdjustValue
  * @param    RTCAx RTCA instance
  * @param    adjustValue
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteAdjustValue(RTCA_Type *RTCAx, uint32_t adjustValue)
{
    MODIFY_REG(RTCAx->ADJUST, (0x1ffU << 0U), (adjustValue << 0U));
}

/**
  * @brief    Set RTCA Adjust Direction
  * @rmtoll   ADJUST    ADSIGN    FL_RTCA_SetAdjustDirection
  * @param    RTCAx RTCA instance
  * @param    adjustDir This parameter can be one of the following values:
  *           @arg @ref FL_RTCA_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTCA_ADJUST_DIR_DECREASE
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_SetAdjustDirection(RTCA_Type *RTCAx, uint32_t adjustDir)
{
    MODIFY_REG(RTCAx->ADJUST, RTCA_ADJUST_ADSIGN_Msk, adjustDir);
}

/**
  * @brief    Get RTCA Adjust Direction
  * @rmtoll   ADJUST    ADSIGN    FL_RTCA_GetAdjustDirection
  * @param    RTCAx RTCA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCA_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTCA_ADJUST_DIR_DECREASE
  */
__STATIC_INLINE uint32_t FL_RTCA_GetAdjustDirection(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->ADJUST, RTCA_ADJUST_ADSIGN_Msk));
}

/**
  * @brief    Get RTCA MilliSecond Counter Value
  * @rmtoll   SBSCNT        FL_RTCA_ReadMilliSecondCounter
  * @param    RTCAx RTCA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCA_ReadMilliSecondCounter(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->SBSCNT, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCA MilliSecond Counter Value
  * @rmtoll   SBSCNT        FL_RTCA_WriteMilliSecondCounter
  * @param    RTCAx RTCA instance
  * @param    milliSecondCount
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_WriteMilliSecondCounter(RTCA_Type *RTCAx, uint32_t milliSecondCount)
{
    MODIFY_REG(RTCAx->SBSCNT, (0xffU << 0U), (milliSecondCount << 0U));
}

/**
  * @brief    RTCA enable
  * @rmtoll   CR    EN    FL_RTCA_Enable
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_Enable(RTCA_Type *RTCAx)
{
    SET_BIT(RTCAx->CR, RTCA_CR_EN_Msk);
}

/**
  * @brief    Get RTCA enable status
  * @rmtoll   CR    EN    FL_RTCA_IsEnabled
  * @param    RTCAx RTCA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCA_IsEnabled(RTCA_Type *RTCAx)
{
    return (uint32_t)(READ_BIT(RTCAx->CR, RTCA_CR_EN_Msk) == RTCA_CR_EN_Msk);
}

/**
  * @brief    RTCA disable
  * @rmtoll   CR    EN    FL_RTCA_Disable
  * @param    RTCAx RTCA instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCA_Disable(RTCA_Type *RTCAx)
{
    CLEAR_BIT(RTCAx->CR, RTCA_CR_EN_Msk);
}

/**
  * @}
  */

/** @defgroup RTCA_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_RTCA_DeInit(RTCA_Type *RTCAx);
void FL_RTCA_StructInit(FL_RTCA_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCA_GetTime(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCA_Init(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCA_ConfigTime(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct);

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

#endif /* __FM33LG0XX_FL_RTCA_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

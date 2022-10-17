/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_rtc.h
  * @author  FMSH Application Team
  * @brief   Head file of RTC FL Module
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
#ifndef __FM33LC0XX_FL_RTC_H
#define __FM33LC0XX_FL_RTC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup RTC RTC
  * @brief RTC FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RTC_FL_ES_INIT RTC Exported Init structures
  * @{
  */

/**
  * @brief Configuration with temporary structure variable users will not be used directly
  */
typedef struct
{
    __IO uint32_t backup[7];
} FL_RTC_Backup_ADDR;

/**
  * @brief RTC Init Sturcture definition
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

} FL_RTC_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RTC_FL_Exported_Constants RTC Exported Constants
  * @{
  */

#define    RTC_IER_ADJ_IE_Pos                                     (12U)
#define    RTC_IER_ADJ_IE_Msk                                     (0x1U << RTC_IER_ADJ_IE_Pos)
#define    RTC_IER_ADJ_IE                                         RTC_IER_ADJ_IE_Msk

#define    RTC_IER_ALARM_IE_Pos                                   (11U)
#define    RTC_IER_ALARM_IE_Msk                                   (0x1U << RTC_IER_ALARM_IE_Pos)
#define    RTC_IER_ALARM_IE                                       RTC_IER_ALARM_IE_Msk

#define    RTC_IER_1KHZ_IE_Pos                                    (10U)
#define    RTC_IER_1KHZ_IE_Msk                                    (0x1U << RTC_IER_1KHZ_IE_Pos)
#define    RTC_IER_1KHZ_IE                                        RTC_IER_1KHZ_IE_Msk

#define    RTC_IER_256HZ_IE_Pos                                   (9U)
#define    RTC_IER_256HZ_IE_Msk                                   (0x1U << RTC_IER_256HZ_IE_Pos)
#define    RTC_IER_256HZ_IE                                       RTC_IER_256HZ_IE_Msk

#define    RTC_IER_64HZ_IE_Pos                                    (8U)
#define    RTC_IER_64HZ_IE_Msk                                    (0x1U << RTC_IER_64HZ_IE_Pos)
#define    RTC_IER_64HZ_IE                                        RTC_IER_64HZ_IE_Msk

#define    RTC_IER_16HZ_IE_Pos                                    (7U)
#define    RTC_IER_16HZ_IE_Msk                                    (0x1U << RTC_IER_16HZ_IE_Pos)
#define    RTC_IER_16HZ_IE                                        RTC_IER_16HZ_IE_Msk

#define    RTC_IER_8HZ_IE_Pos                                     (6U)
#define    RTC_IER_8HZ_IE_Msk                                     (0x1U << RTC_IER_8HZ_IE_Pos)
#define    RTC_IER_8HZ_IE                                         RTC_IER_8HZ_IE_Msk

#define    RTC_IER_4HZ_IE_Pos                                     (5U)
#define    RTC_IER_4HZ_IE_Msk                                     (0x1U << RTC_IER_4HZ_IE_Pos)
#define    RTC_IER_4HZ_IE                                         RTC_IER_4HZ_IE_Msk

#define    RTC_IER_2HZ_IE_Pos                                     (4U)
#define    RTC_IER_2HZ_IE_Msk                                     (0x1U << RTC_IER_2HZ_IE_Pos)
#define    RTC_IER_2HZ_IE                                         RTC_IER_2HZ_IE_Msk

#define    RTC_IER_SEC_IE_Pos                                     (3U)
#define    RTC_IER_SEC_IE_Msk                                     (0x1U << RTC_IER_SEC_IE_Pos)
#define    RTC_IER_SEC_IE                                         RTC_IER_SEC_IE_Msk

#define    RTC_IER_MIN_IE_Pos                                     (2U)
#define    RTC_IER_MIN_IE_Msk                                     (0x1U << RTC_IER_MIN_IE_Pos)
#define    RTC_IER_MIN_IE                                         RTC_IER_MIN_IE_Msk

#define    RTC_IER_HOUR_IE_Pos                                    (1U)
#define    RTC_IER_HOUR_IE_Msk                                    (0x1U << RTC_IER_HOUR_IE_Pos)
#define    RTC_IER_HOUR_IE                                        RTC_IER_HOUR_IE_Msk

#define    RTC_IER_DAY_IE_Pos                                     (0U)
#define    RTC_IER_DAY_IE_Msk                                     (0x1U << RTC_IER_DAY_IE_Pos)
#define    RTC_IER_DAY_IE                                         RTC_IER_DAY_IE_Msk

#define    RTC_ISR_ADJ_IF_Pos                                     (12U)
#define    RTC_ISR_ADJ_IF_Msk                                     (0x1U << RTC_ISR_ADJ_IF_Pos)
#define    RTC_ISR_ADJ_IF                                         RTC_ISR_ADJ_IF_Msk

#define    RTC_ISR_ALARM_IF_Pos                                   (11U)
#define    RTC_ISR_ALARM_IF_Msk                                   (0x1U << RTC_ISR_ALARM_IF_Pos)
#define    RTC_ISR_ALARM_IF                                       RTC_ISR_ALARM_IF_Msk

#define    RTC_ISR_1KHZ_IF_Pos                                    (10U)
#define    RTC_ISR_1KHZ_IF_Msk                                    (0x1U << RTC_ISR_1KHZ_IF_Pos)
#define    RTC_ISR_1KHZ_IF                                        RTC_ISR_1KHZ_IF_Msk

#define    RTC_ISR_256HZ_IF_Pos                                   (9U)
#define    RTC_ISR_256HZ_IF_Msk                                   (0x1U << RTC_ISR_256HZ_IF_Pos)
#define    RTC_ISR_256HZ_IF                                       RTC_ISR_256HZ_IF_Msk

#define    RTC_ISR_64HZ_IF_Pos                                    (8U)
#define    RTC_ISR_64HZ_IF_Msk                                    (0x1U << RTC_ISR_64HZ_IF_Pos)
#define    RTC_ISR_64HZ_IF                                        RTC_ISR_64HZ_IF_Msk

#define    RTC_ISR_16HZ_IF_Pos                                    (7U)
#define    RTC_ISR_16HZ_IF_Msk                                    (0x1U << RTC_ISR_16HZ_IF_Pos)
#define    RTC_ISR_16HZ_IF                                        RTC_ISR_16HZ_IF_Msk

#define    RTC_ISR_8HZ_IF_Pos                                     (6U)
#define    RTC_ISR_8HZ_IF_Msk                                     (0x1U << RTC_ISR_8HZ_IF_Pos)
#define    RTC_ISR_8HZ_IF                                         RTC_ISR_8HZ_IF_Msk

#define    RTC_ISR_4HZ_IF_Pos                                     (5U)
#define    RTC_ISR_4HZ_IF_Msk                                     (0x1U << RTC_ISR_4HZ_IF_Pos)
#define    RTC_ISR_4HZ_IF                                         RTC_ISR_4HZ_IF_Msk

#define    RTC_ISR_2HZ_IF_Pos                                     (4U)
#define    RTC_ISR_2HZ_IF_Msk                                     (0x1U << RTC_ISR_2HZ_IF_Pos)
#define    RTC_ISR_2HZ_IF                                         RTC_ISR_2HZ_IF_Msk

#define    RTC_ISR_SEC_IF_Pos                                     (3U)
#define    RTC_ISR_SEC_IF_Msk                                     (0x1U << RTC_ISR_SEC_IF_Pos)
#define    RTC_ISR_SEC_IF                                         RTC_ISR_SEC_IF_Msk

#define    RTC_ISR_MIN_IF_Pos                                     (2U)
#define    RTC_ISR_MIN_IF_Msk                                     (0x1U << RTC_ISR_MIN_IF_Pos)
#define    RTC_ISR_MIN_IF                                         RTC_ISR_MIN_IF_Msk

#define    RTC_ISR_HOUR_IF_Pos                                    (1U)
#define    RTC_ISR_HOUR_IF_Msk                                    (0x1U << RTC_ISR_HOUR_IF_Pos)
#define    RTC_ISR_HOUR_IF                                        RTC_ISR_HOUR_IF_Msk

#define    RTC_ISR_DAY_IF_Pos                                     (0U)
#define    RTC_ISR_DAY_IF_Msk                                     (0x1U << RTC_ISR_DAY_IF_Pos)
#define    RTC_ISR_DAY_IF                                         RTC_ISR_DAY_IF_Msk

#define    RTC_TMSEL_TMSEL_Pos                                    (0U)
#define    RTC_TMSEL_TMSEL_Msk                                    (0xfU << RTC_TMSEL_TMSEL_Pos)
#define    RTC_TMSEL_TMSEL                                        RTC_TMSEL_TMSEL_Msk

#define    RTC_ADSIGN_ADSIGN_Pos                                  (0U)
#define    RTC_ADSIGN_ADSIGN_Msk                                  (0x1U << RTC_ADSIGN_ADSIGN_Pos)
#define    RTC_ADSIGN_ADSIGN                                      RTC_ADSIGN_ADSIGN_Msk



#define    FL_RTC_BACKUP_0                                        (0x0U)
#define    FL_RTC_BACKUP_1                                        (0x1U)
#define    FL_RTC_BACKUP_2                                        (0x2U)
#define    FL_RTC_BACKUP_3                                        (0x3U)
#define    FL_RTC_BACKUP_4                                        (0x4U)
#define    FL_RTC_BACKUP_5                                        (0x5U)
#define    FL_RTC_BACKUP_6                                        (0x6U)
#define    FL_RTC_BACKUP_7                                        (0x7U)



#define    FL_RTC_TIME_MARK_SECOND                                (0x2U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_MINUTE                                (0x3U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_HOUR                                  (0x4U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_DAY                                   (0x5U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_ALARM                                 (0x6U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_32_SEC                                (0x7U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_SECOND_REVERSE                        (0x9U << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_MINUTE_REVERSE                        (0xaU << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_HOUR_REVERSE                          (0xbU << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_DAY_REVERSE                           (0xcU << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_ALARM_REVERSE                         (0xdU << RTC_TMSEL_TMSEL_Pos)
#define    FL_RTC_TIME_MARK_SEC                                   (0xfU << RTC_TMSEL_TMSEL_Pos)


#define    FL_RTC_ADJUST_DIR_INCREASE                             (0x0U << RTC_ADSIGN_ADSIGN_Pos)
#define    FL_RTC_ADJUST_DIR_DECREASE                             (0x1U << RTC_ADSIGN_ADSIGN_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RTC_FL_Exported_Functions RTC Exported Functions
  * @{
  */

/**
  * @brief    Enable RTC Config Time
  * @rmtoll   WER        FL_RTC_WriteEnable
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteEnable(RTC_Type *RTCx)
{
    RTCx->WER = 0xACACACAC;
}

/**
  * @brief    Disable RTC Config Time
  * @rmtoll   WER        FL_RTC_WriteDisable
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteDisable(RTC_Type *RTCx)
{
    RTCx->WER = 0x5A5A5A5A;
}

/**
  * @brief    Enable RTC Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTC_EnableIT_Adjust
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Adjust(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_ADJ_IE_Msk);
}

/**
  * @brief    Get RTC Time Adjust Interrupt Enable Status
  * @rmtoll   IER    ADJ_IE    FL_RTC_IsEnabledIT_Adjust
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Adjust(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_ADJ_IE_Msk) == RTC_IER_ADJ_IE_Msk);
}

/**
  * @brief    Disable RTC Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTC_DisableIT_Adjust
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Adjust(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_ADJ_IE_Msk);
}

/**
  * @brief    Enable RTC Alarm Interrupt
  * @rmtoll   IER    ALARM_IE    FL_RTC_EnableIT_Alarm
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Alarm(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_ALARM_IE_Msk);
}

/**
  * @brief    Get RTC Alarm Interrupt Enable Status
  * @rmtoll   IER    ALARM_IE    FL_RTC_IsEnabledIT_Alarm
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Alarm(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_ALARM_IE_Msk) == RTC_IER_ALARM_IE_Msk);
}

/**
  * @brief    Disable RTC Alarm    Interrupt
  * @rmtoll   IER    ALARM_IE    FL_RTC_DisableIT_Alarm
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Alarm(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_ALARM_IE_Msk);
}

/**
  * @brief    Enable RTC 1KHz Interrupt
  * @rmtoll   IER    1KHZ_IE    FL_RTC_EnableIT_1KHz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_1KHz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Get RTC 1KHz Interrupt Enable Status
  * @rmtoll   IER    1KHZ_IE    FL_RTC_IsEnabledIT_1KHz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_1KHz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_1KHZ_IE_Msk) == RTC_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Disable RTC 1KHz Interrupt
  * @rmtoll   IER    1KHZ_IE    FL_RTC_DisableIT_1KHz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_1KHz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_1KHZ_IE_Msk);
}

/**
  * @brief    Enable RTC 256Hz Interrupt
  * @rmtoll   IER    256HZ_IE    FL_RTC_EnableIT_256Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_256Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_256HZ_IE_Msk);
}

/**
  * @brief    Get RTC 256Hz Interrupt Enable Status
  * @rmtoll   IER    256HZ_IE    FL_RTC_IsEnabledIT_256Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_256Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_256HZ_IE_Msk) == RTC_IER_256HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 256Hz Interrupt
  * @rmtoll   IER    256HZ_IE    FL_RTC_DisableIT_256Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_256Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_256HZ_IE_Msk);
}

/**
  * @brief    Enable RTC 64Hz Interrupt
  * @rmtoll   IER    64HZ_IE    FL_RTC_EnableIT_64Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_64Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_64HZ_IE_Msk);
}

/**
  * @brief    Get RTC 64Hz Interrupt Enable Status
  * @rmtoll   IER    64HZ_IE    FL_RTC_IsEnabledIT_64Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_64Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_64HZ_IE_Msk) == RTC_IER_64HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 64Hz Interrupt
  * @rmtoll   IER    64HZ_IE    FL_RTC_DisableIT_64Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_64Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_64HZ_IE_Msk);
}

/**
  * @brief    Enable RTC 16Hz Interrupt
  * @rmtoll   IER    16HZ_IE    FL_RTC_EnableIT_16Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_16Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_16HZ_IE_Msk);
}

/**
  * @brief    Get RTC 16Hz Interrupt Enable Status
  * @rmtoll   IER    16HZ_IE    FL_RTC_IsEnabledIT_16Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_16Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_16HZ_IE_Msk) == RTC_IER_16HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 16Hz Interrupt
  * @rmtoll   IER    16HZ_IE    FL_RTC_DisableIT_16Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_16Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_16HZ_IE_Msk);
}

/**
  * @brief    Enable RTC 8Hz Interrupt
  * @rmtoll   IER    8HZ_IE    FL_RTC_EnableIT_8Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_8Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_8HZ_IE_Msk);
}

/**
  * @brief    Get RTC 8Hz Interrupt Enable Status
  * @rmtoll   IER    8HZ_IE    FL_RTC_IsEnabledIT_8Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_8Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_8HZ_IE_Msk) == RTC_IER_8HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 8Hz Interrupt
  * @rmtoll   IER    8HZ_IE    FL_RTC_DisableIT_8Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_8Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_8HZ_IE_Msk);
}

/**
  * @brief    Enable RTC 4Hz Interrupt
  * @rmtoll   IER    4HZ_IE    FL_RTC_EnableIT_4Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_4Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_4HZ_IE_Msk);
}

/**
  * @brief    Get RTC 4Hz Interrupt Enable Status
  * @rmtoll   IER    4HZ_IE    FL_RTC_IsEnabledIT_4Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_4Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_4HZ_IE_Msk) == RTC_IER_4HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 4Hz Interrupt
  * @rmtoll   IER    4HZ_IE    FL_RTC_DisableIT_4Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_4Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_4HZ_IE_Msk);
}

/**
  * @brief    Enable RTC 2Hz Interrupt
  * @rmtoll   IER    2HZ_IE    FL_RTC_EnableIT_2Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_2Hz(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_2HZ_IE_Msk);
}

/**
  * @brief    Get RTC 2Hz Interrupt Enable Status
  * @rmtoll   IER    2HZ_IE    FL_RTC_IsEnabledIT_2Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_2Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_2HZ_IE_Msk) == RTC_IER_2HZ_IE_Msk);
}

/**
  * @brief    Disable RTC 2Hz Interrupt
  * @rmtoll   IER    2HZ_IE    FL_RTC_DisableIT_2Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_2Hz(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_2HZ_IE_Msk);
}

/**
  * @brief    Enable RTC Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTC_EnableIT_Second
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Second(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_SEC_IE_Msk);
}

/**
  * @brief    Get RTC Second Interrupt Enable Status
  * @rmtoll   IER    SEC_IE    FL_RTC_IsEnabledIT_Second
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Second(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_SEC_IE_Msk) == RTC_IER_SEC_IE_Msk);
}

/**
  * @brief    Disable RTC Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTC_DisableIT_Second
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Second(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_SEC_IE_Msk);
}

/**
  * @brief    Enable RTC Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTC_EnableIT_Minute
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Minute(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_MIN_IE_Msk);
}

/**
  * @brief    Get RTC Minute Interrupt Enable Status
  * @rmtoll   IER    MIN_IE    FL_RTC_IsEnabledIT_Minute
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Minute(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_MIN_IE_Msk) == RTC_IER_MIN_IE_Msk);
}

/**
  * @brief    Disable RTC Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTC_DisableIT_Minute
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Minute(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_MIN_IE_Msk);
}

/**
  * @brief    Enable RTC Hour Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTC_EnableIT_Hour
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Hour(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_HOUR_IE_Msk);
}

/**
  * @brief    Get RTC Hour Interrupt Enable Status
  * @rmtoll   IER    HOUR_IE    FL_RTC_IsEnabledIT_Hour
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Hour(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_HOUR_IE_Msk) == RTC_IER_HOUR_IE_Msk);
}

/**
  * @brief    Disable RTC Hour  Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTC_DisableIT_Hour
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Hour(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_HOUR_IE_Msk);
}

/**
  * @brief    Enable RTC Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTC_EnableIT_Day
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_EnableIT_Day(RTC_Type *RTCx)
{
    SET_BIT(RTCx->IER, RTC_IER_DAY_IE_Msk);
}

/**
  * @brief    Get RTC Day Interrupt Enable Status
  * @rmtoll   IER    DAY_IE    FL_RTC_IsEnabledIT_Day
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsEnabledIT_Day(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->IER, RTC_IER_DAY_IE_Msk) == RTC_IER_DAY_IE_Msk);
}

/**
  * @brief    Disable RTC Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTC_DisableIT_Day
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_DisableIT_Day(RTC_Type *RTCx)
{
    CLEAR_BIT(RTCx->IER, RTC_IER_DAY_IE_Msk);
}

/**
  * @brief    Clear RTC Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTC_ClearFlag_Adjust
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Adjust(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_ADJ_IF_Msk);
}

/**
  * @brief    Get RTC Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTC_IsActiveFlag_Adjust
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Adjust(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_ADJ_IF_Msk) == (RTC_ISR_ADJ_IF_Msk));
}

/**
  * @brief    Clear RTC Alarm Interrupt Flag
  * @rmtoll   ISR    ALARM_IF    FL_RTC_ClearFlag_Alarm
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Alarm(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_ALARM_IF_Msk);
}

/**
  * @brief    Get RTC Alarm Interrupt Flag
  * @rmtoll   ISR    ALARM_IF    FL_RTC_IsActiveFlag_Alarm
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Alarm(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_ALARM_IF_Msk) == (RTC_ISR_ALARM_IF_Msk));
}

/**
  * @brief    Clear RTC 1KHz Interrupt Flag
  * @rmtoll   ISR    1KHZ_IF    FL_RTC_ClearFlag_1KHz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_1KHz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_1KHZ_IF_Msk);
}

/**
  * @brief    Get RTC 1KHz Interrupt Flag
  * @rmtoll   ISR    1KHZ_IF    FL_RTC_IsActiveFlag_1KHz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_1KHz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_1KHZ_IF_Msk) == (RTC_ISR_1KHZ_IF_Msk));
}

/**
  * @brief    Clear RTC 256Hz Interrupt Flag
  * @rmtoll   ISR    256HZ_IF    FL_RTC_ClearFlag_256Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_256Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_256HZ_IF_Msk);
}

/**
  * @brief    Get RTC 256Hz Interrupt Flag
  * @rmtoll   ISR    256HZ_IF    FL_RTC_IsActiveFlag_256Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_256Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_256HZ_IF_Msk) == (RTC_ISR_256HZ_IF_Msk));
}

/**
  * @brief    Clear RTC 64Hz Interrupt Flag
  * @rmtoll   ISR    64HZ_IF    FL_RTC_ClearFlag_64Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_64Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_64HZ_IF_Msk);
}

/**
  * @brief    Get RTC 64Hz Interrupt Flag
  * @rmtoll   ISR    64HZ_IF    FL_RTC_IsActiveFlag_64Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_64Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_64HZ_IF_Msk) == (RTC_ISR_64HZ_IF_Msk));
}

/**
  * @brief    Clear RTC 16Hz Interrupt Flag
  * @rmtoll   ISR    16HZ_IF    FL_RTC_ClearFlag_16Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_16Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_16HZ_IF_Msk);
}

/**
  * @brief    Get RTC 16Hz Interrupt Flag
  * @rmtoll   ISR    16HZ_IF    FL_RTC_IsActiveFlag_16Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_16Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_16HZ_IF_Msk) == (RTC_ISR_16HZ_IF_Msk));
}

/**
  * @brief    Clear RTC 8Hz Interrupt Flag
  * @rmtoll   ISR    8HZ_IF    FL_RTC_ClearFlag_8Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_8Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_8HZ_IF_Msk);
}

/**
  * @brief    Get RTC 8Hz Interrupt Flag
  * @rmtoll   ISR    8HZ_IF    FL_RTC_IsActiveFlag_8Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_8Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_8HZ_IF_Msk) == (RTC_ISR_8HZ_IF_Msk));
}

/**
  * @brief    Clear RTC 4Hz Interrupt Flag
  * @rmtoll   ISR    4HZ_IF    FL_RTC_ClearFlag_4Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_4Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_4HZ_IF_Msk);
}

/**
  * @brief    Get RTC 4Hz Interrupt Flag
  * @rmtoll   ISR    4HZ_IF    FL_RTC_IsActiveFlag_4Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_4Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_4HZ_IF_Msk) == (RTC_ISR_4HZ_IF_Msk));
}

/**
  * @brief    Clear RTC 2Hz Interrupt Flag
  * @rmtoll   ISR    2HZ_IF    FL_RTC_ClearFlag_2Hz
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_2Hz(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_2HZ_IF_Msk);
}

/**
  * @brief    Get RTC 2Hz Interrupt Flag
  * @rmtoll   ISR    2HZ_IF    FL_RTC_IsActiveFlag_2Hz
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_2Hz(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_2HZ_IF_Msk) == (RTC_ISR_2HZ_IF_Msk));
}

/**
  * @brief    Clear RTC Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTC_ClearFlag_Second
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Second(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_SEC_IF_Msk);
}

/**
  * @brief    Get RTC Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTC_IsActiveFlag_Second
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Second(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_SEC_IF_Msk) == (RTC_ISR_SEC_IF_Msk));
}

/**
  * @brief    Clear RTC Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTC_ClearFlag_Minute
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Minute(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_MIN_IF_Msk);
}

/**
  * @brief    Get RTC Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTC_IsActiveFlag_Minute
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Minute(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_MIN_IF_Msk) == (RTC_ISR_MIN_IF_Msk));
}

/**
  * @brief    Clear RTC Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTC_ClearFlag_Hour
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Hour(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_HOUR_IF_Msk);
}

/**
  * @brief    Get RTC Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTC_IsActiveFlag_Hour
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Hour(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_HOUR_IF_Msk) == (RTC_ISR_HOUR_IF_Msk));
}

/**
  * @brief    Clear RTC Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTC_ClearFlag_Day
  * @param    RTCx RTC instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_ClearFlag_Day(RTC_Type *RTCx)
{
    WRITE_REG(RTCx->ISR, RTC_ISR_DAY_IF_Msk);
}

/**
  * @brief    Get RTC Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTC_IsActiveFlag_Day
  * @param    RTCx RTC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTC_IsActiveFlag_Day(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ISR, RTC_ISR_DAY_IF_Msk) == (RTC_ISR_DAY_IF_Msk));
}

/**
  * @brief    Get RTC Second Value
  * @rmtoll   BCDSEC        FL_RTC_ReadSecond
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadSecond(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDSEC, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Second Value
  * @rmtoll   BCDSEC        FL_RTC_WriteSecond
  * @param    RTCx RTC instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteSecond(RTC_Type *RTCx, uint32_t second)
{
    MODIFY_REG(RTCx->BCDSEC, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Get RTC Minute Value
  * @rmtoll   BCDMIN        FL_RTC_ReadMinute
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadMinute(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDMIN, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Minute Value
  * @rmtoll   BCDMIN        FL_RTC_WriteMinute
  * @param    RTCx RTC instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteMinute(RTC_Type *RTCx, uint32_t minute)
{
    MODIFY_REG(RTCx->BCDMIN, (0x7fU << 0U), (minute << 0U));
}

/**
  * @brief    Get RTC Hour Value
  * @rmtoll   BCDHOUR        FL_RTC_ReadHour
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadHour(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDHOUR, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Hour Value
  * @rmtoll   BCDHOUR        FL_RTC_WriteHour
  * @param    RTCx RTC instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteHour(RTC_Type *RTCx, uint32_t hour)
{
    MODIFY_REG(RTCx->BCDHOUR, (0x3fU << 0U), (hour << 0U));
}

/**
  * @brief    Get RTC Day Value
  * @rmtoll   BCDDAY        FL_RTC_ReadDay
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadDay(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDDAY, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Day Value
  * @rmtoll   BCDDAY        FL_RTC_WriteDay
  * @param    RTCx RTC instance
  * @param    day
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteDay(RTC_Type *RTCx, uint32_t day)
{
    MODIFY_REG(RTCx->BCDDAY, (0x3fU << 0U), (day << 0U));
}

/**
  * @brief    Get RTC Week Value
  * @rmtoll   BCDWEEK        FL_RTC_ReadWeek
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadWeek(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDWEEK, (0x7U << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Week Value
  * @rmtoll   BCDWEEK        FL_RTC_WriteWeek
  * @param    RTCx RTC instance
  * @param    week
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteWeek(RTC_Type *RTCx, uint32_t week)
{
    MODIFY_REG(RTCx->BCDWEEK, (0x7U << 0U), (week << 0U));
}

/**
  * @brief    Get RTC Month Value
  * @rmtoll   BCDMONTH        FL_RTC_ReadMonth
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadMonth(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDMONTH, (0x1fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Month Value
  * @rmtoll   BCDMONTH        FL_RTC_WriteMonth
  * @param    RTCx RTC instance
  * @param    month
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteMonth(RTC_Type *RTCx, uint32_t month)
{
    MODIFY_REG(RTCx->BCDMONTH, (0x1fU << 0U), (month << 0U));
}

/**
  * @brief    Get RTC Year Value
  * @rmtoll   BCDYEAR        FL_RTC_ReadYear
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadYear(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->BCDYEAR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Year Value
  * @rmtoll   BCDYEAR        FL_RTC_WriteYear
  * @param    RTCx RTC instance
  * @param    year
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteYear(RTC_Type *RTCx, uint32_t year)
{
    MODIFY_REG(RTCx->BCDYEAR, (0xffU << 0U), (year << 0U));
}

/**
  * @brief    Get RTC Alarm Hour Value
  * @rmtoll   ALARM        FL_RTC_ReadHourAlarm
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadHourAlarm(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ALARM, (0x3fU << 16U)) >> 16U);
}

/**
  * @brief    Set RTC Alarm Hour Value
  * @rmtoll   ALARM        FL_RTC_WriteHourAlarm
  * @param    RTCx RTC instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteHourAlarm(RTC_Type *RTCx, uint32_t hour)
{
    MODIFY_REG(RTCx->ALARM, (0x3fU << 16U), (hour << 16U));
}

/**
  * @brief    Get RTC Alarm Minute Value
  * @rmtoll   ALARM        FL_RTC_ReadMinuteAlarm
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadMinuteAlarm(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ALARM, (0x7fU << 8U)) >> 8U);
}

/**
  * @brief    Set RTC Alarm Minute Value
  * @rmtoll   ALARM        FL_RTC_WriteMinuteAlarm
  * @param    RTCx RTC instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteMinuteAlarm(RTC_Type *RTCx, uint32_t minute)
{
    MODIFY_REG(RTCx->ALARM, (0x7fU << 8U), (minute << 8U));
}

/**
  * @brief    Get RTC Alarm Second Value
  * @rmtoll   ALARM        FL_RTC_ReadSecondAlarm
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadSecondAlarm(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ALARM, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Alarm Second Value
  * @rmtoll   ALARM        FL_RTC_WriteSecondAlarm
  * @param    RTCx RTC instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteSecondAlarm(RTC_Type *RTCx, uint32_t second)
{
    MODIFY_REG(RTCx->ALARM, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Set RTC Output Time Mark Signal
  * @rmtoll   TMSEL    TMSEL    FL_RTC_SetTimeMarkOutput
  * @param    RTCx RTC instance
  * @param    markSelect This parameter can be one of the following values:
  *           @arg @ref FL_RTC_TIME_MARK_SECOND
  *           @arg @ref FL_RTC_TIME_MARK_MINUTE
  *           @arg @ref FL_RTC_TIME_MARK_HOUR
  *           @arg @ref FL_RTC_TIME_MARK_DAY
  *           @arg @ref FL_RTC_TIME_MARK_ALARM
  *           @arg @ref FL_RTC_TIME_MARK_32_SEC
  *           @arg @ref FL_RTC_TIME_MARK_SECOND_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_MINUTE_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_HOUR_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_DAY_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_ALARM_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_SEC
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_SetTimeMarkOutput(RTC_Type *RTCx, uint32_t markSelect)
{
    MODIFY_REG(RTCx->TMSEL, RTC_TMSEL_TMSEL_Msk, markSelect);
}

/**
  * @brief    Get RTC Output Time Mark Signal Setting
  * @rmtoll   TMSEL    TMSEL    FL_RTC_GetTimeMarkOutput
  * @param    RTCx RTC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTC_TIME_MARK_SECOND
  *           @arg @ref FL_RTC_TIME_MARK_MINUTE
  *           @arg @ref FL_RTC_TIME_MARK_HOUR
  *           @arg @ref FL_RTC_TIME_MARK_DAY
  *           @arg @ref FL_RTC_TIME_MARK_ALARM
  *           @arg @ref FL_RTC_TIME_MARK_32_SEC
  *           @arg @ref FL_RTC_TIME_MARK_SECOND_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_MINUTE_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_HOUR_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_DAY_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_ALARM_REVERSE
  *           @arg @ref FL_RTC_TIME_MARK_SEC
  */
__STATIC_INLINE uint32_t FL_RTC_GetTimeMarkOutput(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->TMSEL, RTC_TMSEL_TMSEL_Msk));
}

/**
  * @brief    Get RTC Adjust Value
  * @rmtoll   ADJUST        FL_RTC_ReadAdjustValue
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadAdjustValue(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ADJUST, (0x1ffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC Adjust Value
  * @rmtoll   ADJUST        FL_RTC_WriteAdjustValue
  * @param    RTCx RTC instance
  * @param    adjustValue
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteAdjustValue(RTC_Type *RTCx, uint32_t adjustValue)
{
    MODIFY_REG(RTCx->ADJUST, (0x1ffU << 0U), (adjustValue << 0U));
}

/**
  * @brief    Set RTC Adjust Direction
  * @rmtoll   ADSIGN    ADSIGN    FL_RTC_SetAdjustDirection
  * @param    RTCx RTC instance
  * @param    adjustDir This parameter can be one of the following values:
  *           @arg @ref FL_RTC_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTC_ADJUST_DIR_DECREASE
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_SetAdjustDirection(RTC_Type *RTCx, uint32_t adjustDir)
{
    MODIFY_REG(RTCx->ADSIGN, RTC_ADSIGN_ADSIGN_Msk, adjustDir);
}

/**
  * @brief    Get RTC Adjust Direction
  * @rmtoll   ADSIGN    ADSIGN    FL_RTC_GetAdjustDirection
  * @param    RTCx RTC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTC_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTC_ADJUST_DIR_DECREASE
  */
__STATIC_INLINE uint32_t FL_RTC_GetAdjustDirection(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->ADSIGN, RTC_ADSIGN_ADSIGN_Msk));
}

/**
  * @brief    Get RTC MilliSecond Counter Value
  * @rmtoll   SBSCNT        FL_RTC_ReadMilliSecondCounter
  * @param    RTCx RTC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadMilliSecondCounter(RTC_Type *RTCx)
{
    return (uint32_t)(READ_BIT(RTCx->SBSCNT, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTC MilliSecond Counter Value
  * @rmtoll   SBSCNT        FL_RTC_WriteMilliSecondCounter
  * @param    RTCx RTC instance
  * @param    milliSecondCount
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteMilliSecondCounter(RTC_Type *RTCx, uint32_t milliSecondCount)
{
    MODIFY_REG(RTCx->SBSCNT, (0xffU << 0U), (milliSecondCount << 0U));
}

/**
  * @brief    Get RTC Backup Register
  * @rmtoll   BACKUP        FL_RTC_ReadBackupRegisters
  * @param    RTCx RTC instance
  * @param    backupRegNum This parameter can be one of the following values:
  *           @arg @ref FL_RTC_BACKUP_0
  *           @arg @ref FL_RTC_BACKUP_1
  *           @arg @ref FL_RTC_BACKUP_2
  *           @arg @ref FL_RTC_BACKUP_3
  *           @arg @ref FL_RTC_BACKUP_4
  *           @arg @ref FL_RTC_BACKUP_5
  *           @arg @ref FL_RTC_BACKUP_6
  *           @arg @ref FL_RTC_BACKUP_7
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTC_ReadBackupRegisters(RTC_Type *RTCx, uint32_t backupRegNum)
{
    FL_RTC_Backup_ADDR  *addr = (FL_RTC_Backup_ADDR *)&RTCx->BKR0;
    return (uint32_t)(READ_BIT(addr->backup[backupRegNum], 0xFFFFFFFFu));
}

/**
  * @brief    Set RTC Backup Register
  * @rmtoll   BACKUP        FL_RTC_WriteBackupRegisters
  * @param    RTCx RTC instance
  * @param    backupReg
  * @param    backupNum
  * @retval   None
  */
__STATIC_INLINE void FL_RTC_WriteBackupRegisters(RTC_Type *RTCx, uint32_t backupReg, uint32_t backupNum)
{
    FL_RTC_Backup_ADDR  *addr = (FL_RTC_Backup_ADDR *)&RTCx->BKR0;
    MODIFY_REG(addr->backup[backupNum], (0xFFFFFFFFu), backupReg);
}

/**
  * @}
  */

/** @defgroup RTC_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_RTC_DeInit(RTC_Type *RTCx);
void FL_RTC_StructInit(FL_RTC_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTC_GetTime(RTC_Type *RTCx, FL_RTC_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTC_Init(RTC_Type *RTCx, FL_RTC_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTC_ConfigTime(RTC_Type *RTCx, FL_RTC_InitTypeDef *initStruct);

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

#endif /* __FM33LC0XX_FL_RTC_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-22*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/

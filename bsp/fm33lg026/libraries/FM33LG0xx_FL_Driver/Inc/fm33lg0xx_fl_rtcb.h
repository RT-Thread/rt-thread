/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_rtcb.h
  * @author  FMSH Application Team
  * @brief   Head file of RTCB FL Module
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
#ifndef __FM33LG0XX_FL_RTCB_H
#define __FM33LG0XX_FL_RTCB_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup RTCB RTCB
  * @brief RTCB FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup RTCB_FL_ES_INIT RTCB Exported Init structures
  * @{
  */

/**
  * @brief Configuration with temporary structure variable users will not be used directly
  */
typedef __IO struct
{
    __IO uint32_t backup[5];
} FL_RTCB_Backup_ADDR;
/**
  * @brief FL RTCB Init Sturcture definition
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

} FL_RTCB_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup RTCB_FL_Exported_Constants RTCB Exported Constants
  * @{
  */

#define    RTCB_IER_STP_IE_Pos                                    (13U)
#define    RTCB_IER_STP_IE_Msk                                    (0x1U << RTCB_IER_STP_IE_Pos)
#define    RTCB_IER_STP_IE                                        RTCB_IER_STP_IE_Msk

#define    RTCB_IER_ADJ_IE_Pos                                    (12U)
#define    RTCB_IER_ADJ_IE_Msk                                    (0x1U << RTCB_IER_ADJ_IE_Pos)
#define    RTCB_IER_ADJ_IE                                        RTCB_IER_ADJ_IE_Msk

#define    RTCB_IER_SEC_IE_Pos                                    (3U)
#define    RTCB_IER_SEC_IE_Msk                                    (0x1U << RTCB_IER_SEC_IE_Pos)
#define    RTCB_IER_SEC_IE                                        RTCB_IER_SEC_IE_Msk

#define    RTCB_IER_MIN_IE_Pos                                    (2U)
#define    RTCB_IER_MIN_IE_Msk                                    (0x1U << RTCB_IER_MIN_IE_Pos)
#define    RTCB_IER_MIN_IE                                        RTCB_IER_MIN_IE_Msk

#define    RTCB_IER_HOUR_IE_Pos                                   (1U)
#define    RTCB_IER_HOUR_IE_Msk                                   (0x1U << RTCB_IER_HOUR_IE_Pos)
#define    RTCB_IER_HOUR_IE                                       RTCB_IER_HOUR_IE_Msk

#define    RTCB_IER_DAY_IE_Pos                                    (0U)
#define    RTCB_IER_DAY_IE_Msk                                    (0x1U << RTCB_IER_DAY_IE_Pos)
#define    RTCB_IER_DAY_IE                                        RTCB_IER_DAY_IE_Msk

#define    RTCB_ISR_STP_IF_Pos                                    (13U)
#define    RTCB_ISR_STP_IF_Msk                                    (0x1U << RTCB_ISR_STP_IF_Pos)
#define    RTCB_ISR_STP_IF                                        RTCB_ISR_STP_IF_Msk

#define    RTCB_ISR_ADJ_IF_Pos                                    (12U)
#define    RTCB_ISR_ADJ_IF_Msk                                    (0x1U << RTCB_ISR_ADJ_IF_Pos)
#define    RTCB_ISR_ADJ_IF                                        RTCB_ISR_ADJ_IF_Msk

#define    RTCB_ISR_SEC_IF_Pos                                    (3U)
#define    RTCB_ISR_SEC_IF_Msk                                    (0x1U << RTCB_ISR_SEC_IF_Pos)
#define    RTCB_ISR_SEC_IF                                        RTCB_ISR_SEC_IF_Msk

#define    RTCB_ISR_MIN_IF_Pos                                    (2U)
#define    RTCB_ISR_MIN_IF_Msk                                    (0x1U << RTCB_ISR_MIN_IF_Pos)
#define    RTCB_ISR_MIN_IF                                        RTCB_ISR_MIN_IF_Msk

#define    RTCB_ISR_HOUR_IF_Pos                                   (1U)
#define    RTCB_ISR_HOUR_IF_Msk                                   (0x1U << RTCB_ISR_HOUR_IF_Pos)
#define    RTCB_ISR_HOUR_IF                                       RTCB_ISR_HOUR_IF_Msk

#define    RTCB_ISR_DAY_IF_Pos                                    (0U)
#define    RTCB_ISR_DAY_IF_Msk                                    (0x1U << RTCB_ISR_DAY_IF_Pos)
#define    RTCB_ISR_DAY_IF                                        RTCB_ISR_DAY_IF_Msk

#define    RTCB_TMSEL_TMSEL_Pos                                   (0U)
#define    RTCB_TMSEL_TMSEL_Msk                                   (0xfU << RTCB_TMSEL_TMSEL_Pos)
#define    RTCB_TMSEL_TMSEL                                       RTCB_TMSEL_TMSEL_Msk

#define    RTCB_ADJR_ADSIGN_Pos                                   (9U)
#define    RTCB_ADJR_ADSIGN_Msk                                   (0x1U << RTCB_ADJR_ADSIGN_Pos)
#define    RTCB_ADJR_ADSIGN                                       RTCB_ADJR_ADSIGN_Msk

#define    RTCB_CR_EN_Pos                                         (0U)
#define    RTCB_CR_EN_Msk                                         (0x1U << RTCB_CR_EN_Pos)
#define    RTCB_CR_EN                                             RTCB_CR_EN_Msk

#define    RTCB_STPCR_TAMPSEL_Pos                                 (8U)
#define    RTCB_STPCR_TAMPSEL_Msk                                 (0x3U << RTCB_STPCR_TAMPSEL_Pos)
#define    RTCB_STPCR_TAMPSEL                                     RTCB_STPCR_TAMPSEL_Msk

#define    RTCB_STPCR_DF_Pos                                      (7U)
#define    RTCB_STPCR_DF_Msk                                      (0x1U << RTCB_STPCR_DF_Pos)
#define    RTCB_STPCR_DF                                          RTCB_STPCR_DF_Msk

#define    RTCB_STPCR_TSEDGE_Pos                                  (2U)
#define    RTCB_STPCR_TSEDGE_Msk                                  (0x1U << RTCB_STPCR_TSEDGE_Pos)
#define    RTCB_STPCR_TSEDGE                                      RTCB_STPCR_TSEDGE_Msk

#define    RTCB_STPCR_TAMPEN_Pos                                  (1U)
#define    RTCB_STPCR_TAMPEN_Msk                                  (0x1U << RTCB_STPCR_TAMPEN_Pos)
#define    RTCB_STPCR_TAMPEN                                      RTCB_STPCR_TAMPEN_Msk

#define    RTCB_STPCR_TSEN_Pos                                    (0U)
#define    RTCB_STPCR_TSEN_Msk                                    (0x1U << RTCB_STPCR_TSEN_Pos)
#define    RTCB_STPCR_TSEN                                        RTCB_STPCR_TSEN_Msk



#define    FL_RTCB_BACKUP_0                                       (0x0U)
#define    FL_RTCB_BACKUP_1                                       (0x1U)
#define    FL_RTCB_BACKUP_2                                       (0x2U)
#define    FL_RTCB_BACKUP_3                                       (0x3U)
#define    FL_RTCB_BACKUP_4                                       (0x4U)



#define    FL_RTCB_TIME_MARK_CLOSE                                (0x0U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_XTLF                                 (0x1U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_SECOND                               (0x2U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_MINUTE                               (0x3U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_HOUR                                 (0x4U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_DAY                                  (0x5U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_32_SEC                               (0x7U << RTCB_TMSEL_TMSEL_Pos)
#define    FL_RTCB_TIME_MARK_SEC                                  (0x8U << RTCB_TMSEL_TMSEL_Pos)


#define    FL_RTCB_ADJUST_DIR_INCREASE                            (0x0U << RTCB_ADJR_ADSIGN_Pos)
#define    FL_RTCB_ADJUST_DIR_DECREASE                            (0x1U << RTCB_ADJR_ADSIGN_Pos)


#define    FL_RTCB_TIME_CLEAR_NONE                                (0x0U << RTCB_STPCR_TAMPSEL_Pos)
#define    FL_RTCB_TIME_CLEAR_TAMPER_PIN                          (0x1U << RTCB_STPCR_TAMPSEL_Pos)
#define    FL_RTCB_TIME_CLEAR_XTLF                                (0x2U << RTCB_STPCR_TAMPSEL_Pos)
#define    FL_RTCB_TIME_CLEAR_BOTH                                (0x3U << RTCB_STPCR_TAMPSEL_Pos)


#define    FL_RTCB_TIMESTAMP_EDGE_RISING                          (0x0U << RTCB_STPCR_TSEDGE_Pos)
#define    FL_RTCB_TIMESTAMP_EDGE_FALLING                         (0x1U << RTCB_STPCR_TSEDGE_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup RTCB_FL_Exported_Functions RTCB Exported Functions
  * @{
  */

/**
  * @brief    Enable RTCB Config Time
  * @rmtoll   WER        FL_RTCB_WriteEnable
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteEnable(RTCB_Type *RTCBx)
{
    RTCBx->WER = 0xACACACAC;
}

/**
  * @brief    Disable RTCB Config Time
  * @rmtoll   WER        FL_RTCB_WriteDisable
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteDisable(RTCB_Type *RTCBx)
{
    RTCBx->WER = 0x5A5A5A5A;
}

/**
  * @brief    Enable RTCB STP Interrupt
  * @rmtoll   IER    STP_IE    FL_RTCB_EnableIT_Stamp
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Stamp(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_STP_IE_Msk);
}

/**
  * @brief    Get RTCB STP Interrupt Enable Status
  * @rmtoll   IER    STP_IE    FL_RTCB_IsEnabledIT_Stamp
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Stamp(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_STP_IE_Msk) == RTCB_IER_STP_IE_Msk);
}

/**
  * @brief    Disable RTCB  STP Interrupt
  * @rmtoll   IER    STP_IE    FL_RTCB_DisableIT_Stamp
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Stamp(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_STP_IE_Msk);
}

/**
  * @brief    Enable RTCB Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTCB_EnableIT_Adjust
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Adjust(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_ADJ_IE_Msk);
}

/**
  * @brief    Get RTCB Time Adjust Interrupt Enable Status
  * @rmtoll   IER    ADJ_IE    FL_RTCB_IsEnabledIT_Adjust
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Adjust(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_ADJ_IE_Msk) == RTCB_IER_ADJ_IE_Msk);
}

/**
  * @brief    Disable RTCB Time Adjust Interrupt
  * @rmtoll   IER    ADJ_IE    FL_RTCB_DisableIT_Adjust
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Adjust(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_ADJ_IE_Msk);
}

/**
  * @brief    Enable RTCB Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTCB_EnableIT_Second
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Second(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_SEC_IE_Msk);
}

/**
  * @brief    Get RTCB Second Interrupt Enable Status
  * @rmtoll   IER    SEC_IE    FL_RTCB_IsEnabledIT_Second
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Second(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_SEC_IE_Msk) == RTCB_IER_SEC_IE_Msk);
}

/**
  * @brief    Disable RTCB Second Interrupt
  * @rmtoll   IER    SEC_IE    FL_RTCB_DisableIT_Second
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Second(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_SEC_IE_Msk);
}

/**
  * @brief    Enable RTCB Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTCB_EnableIT_Minute
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Minute(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_MIN_IE_Msk);
}

/**
  * @brief    Get RTCB Minute Interrupt Enable Status
  * @rmtoll   IER    MIN_IE    FL_RTCB_IsEnabledIT_Minute
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Minute(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_MIN_IE_Msk) == RTCB_IER_MIN_IE_Msk);
}

/**
  * @brief    Disable RTCB Minute Interrupt
  * @rmtoll   IER    MIN_IE    FL_RTCB_DisableIT_Minute
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Minute(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_MIN_IE_Msk);
}

/**
  * @brief    Enable RTCB Hour Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTCB_EnableIT_Hour
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Hour(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_HOUR_IE_Msk);
}

/**
  * @brief    Get RTCB Hour Interrupt Enable Status
  * @rmtoll   IER    HOUR_IE    FL_RTCB_IsEnabledIT_Hour
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Hour(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_HOUR_IE_Msk) == RTCB_IER_HOUR_IE_Msk);
}

/**
  * @brief    Disable RTCB Hour  Interrupt
  * @rmtoll   IER    HOUR_IE    FL_RTCB_DisableIT_Hour
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Hour(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_HOUR_IE_Msk);
}

/**
  * @brief    Enable RTCB Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTCB_EnableIT_Day
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableIT_Day(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->IER, RTCB_IER_DAY_IE_Msk);
}

/**
  * @brief    Get RTCB Day Interrupt Enable Status
  * @rmtoll   IER    DAY_IE    FL_RTCB_IsEnabledIT_Day
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledIT_Day(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->IER, RTCB_IER_DAY_IE_Msk) == RTCB_IER_DAY_IE_Msk);
}

/**
  * @brief    Disable RTCB Day Interrupt
  * @rmtoll   IER    DAY_IE    FL_RTCB_DisableIT_Day
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableIT_Day(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->IER, RTCB_IER_DAY_IE_Msk);
}

/**
  * @brief    Clear RTCB STP Interrupt Flag
  * @rmtoll   ISR    STP_IF    FL_RTCB_ClearFlag_Stamp
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Stamp(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_STP_IF_Msk);
}

/**
  * @brief    Get RTCB STP Interrupt Flag
  * @rmtoll   ISR    STP_IF    FL_RTCB_IsActiveFlag_Stamp
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Stamp(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_STP_IF_Msk) == (RTCB_ISR_STP_IF_Msk));
}

/**
  * @brief    Clear RTCB Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTCB_ClearFlag_Adjust
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Adjust(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_ADJ_IF_Msk);
}

/**
  * @brief    Get RTCB Time Adjust Interrupt Flag
  * @rmtoll   ISR    ADJ_IF    FL_RTCB_IsActiveFlag_Adjust
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Adjust(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_ADJ_IF_Msk) == (RTCB_ISR_ADJ_IF_Msk));
}

/**
  * @brief    Clear RTCB Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTCB_ClearFlag_Second
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Second(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_SEC_IF_Msk);
}

/**
  * @brief    Get RTCB Second Interrupt Flag
  * @rmtoll   ISR    SEC_IF    FL_RTCB_IsActiveFlag_Second
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Second(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_SEC_IF_Msk) == (RTCB_ISR_SEC_IF_Msk));
}

/**
  * @brief    Clear RTCB Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTCB_ClearFlag_Minute
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Minute(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_MIN_IF_Msk);
}

/**
  * @brief    Get RTCB Minute Interrupt Flag
  * @rmtoll   ISR    MIN_IF    FL_RTCB_IsActiveFlag_Minute
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Minute(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_MIN_IF_Msk) == (RTCB_ISR_MIN_IF_Msk));
}

/**
  * @brief    Clear RTCB Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTCB_ClearFlag_Hour
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Hour(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_HOUR_IF_Msk);
}

/**
  * @brief    Get RTCB Hour Interrupt Flag
  * @rmtoll   ISR    HOUR_IF    FL_RTCB_IsActiveFlag_Hour
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Hour(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_HOUR_IF_Msk) == (RTCB_ISR_HOUR_IF_Msk));
}

/**
  * @brief    Clear RTCB Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTCB_ClearFlag_Day
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_ClearFlag_Day(RTCB_Type *RTCBx)
{
    WRITE_REG(RTCBx->ISR, RTCB_ISR_DAY_IF_Msk);
}

/**
  * @brief    Get RTCB Day Interrupt Flag
  * @rmtoll   ISR    DAY_IF    FL_RTCB_IsActiveFlag_Day
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsActiveFlag_Day(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ISR, RTCB_ISR_DAY_IF_Msk) == (RTCB_ISR_DAY_IF_Msk));
}

/**
  * @brief    Get RTCB Second Value
  * @rmtoll   BCDSEC        FL_RTCB_ReadSecond
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadSecond(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDSEC, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Second Value
  * @rmtoll   BCDSEC        FL_RTCB_WriteSecond
  * @param    RTCBx RTCB instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteSecond(RTCB_Type *RTCBx, uint32_t second)
{
    MODIFY_REG(RTCBx->BCDSEC, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Get RTCB Minute Value
  * @rmtoll   BCDMIN        FL_RTCB_ReadMinute
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadMinute(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDMIN, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Minute Value
  * @rmtoll   BCDMIN        FL_RTCB_WriteMinute
  * @param    RTCBx RTCB instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteMinute(RTCB_Type *RTCBx, uint32_t minute)
{
    MODIFY_REG(RTCBx->BCDMIN, (0x7fU << 0U), (minute << 0U));
}

/**
  * @brief    Get RTCB Hour Value
  * @rmtoll   BCDHOUR        FL_RTCB_ReadHour
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadHour(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDHOUR, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Hour Value
  * @rmtoll   BCDHOUR        FL_RTCB_WriteHour
  * @param    RTCBx RTCB instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteHour(RTCB_Type *RTCBx, uint32_t hour)
{
    MODIFY_REG(RTCBx->BCDHOUR, (0x3fU << 0U), (hour << 0U));
}

/**
  * @brief    Get RTCB Day Value
  * @rmtoll   BCDDAY        FL_RTCB_ReadDay
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadDay(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDDAY, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Day Value
  * @rmtoll   BCDDAY        FL_RTCB_WriteDay
  * @param    RTCBx RTCB instance
  * @param    day
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteDay(RTCB_Type *RTCBx, uint32_t day)
{
    MODIFY_REG(RTCBx->BCDDAY, (0x3fU << 0U), (day << 0U));
}

/**
  * @brief    Get RTCB Week Value
  * @rmtoll   BCDWEEK        FL_RTCB_ReadWeek
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadWeek(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDWEEK, (0x7U << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Week Value
  * @rmtoll   BCDWEEK        FL_RTCB_WriteWeek
  * @param    RTCBx RTCB instance
  * @param    week
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteWeek(RTCB_Type *RTCBx, uint32_t week)
{
    MODIFY_REG(RTCBx->BCDWEEK, (0x7U << 0U), (week << 0U));
}

/**
  * @brief    Get RTCB Month Value
  * @rmtoll   BCDMONTH        FL_RTCB_ReadMonth
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadMonth(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDMONTH, (0x1fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Month Value
  * @rmtoll   BCDMONTH        FL_RTCB_WriteMonth
  * @param    RTCBx RTCB instance
  * @param    month
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteMonth(RTCB_Type *RTCBx, uint32_t month)
{
    MODIFY_REG(RTCBx->BCDMONTH, (0x1fU << 0U), (month << 0U));
}

/**
  * @brief    Get RTCB Year Value
  * @rmtoll   BCDYEAR        FL_RTCB_ReadYear
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadYear(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->BCDYEAR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Year Value
  * @rmtoll   BCDYEAR        FL_RTCB_WriteYear
  * @param    RTCBx RTCB instance
  * @param    year
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteYear(RTCB_Type *RTCBx, uint32_t year)
{
    MODIFY_REG(RTCBx->BCDYEAR, (0xffU << 0U), (year << 0U));
}

/**
  * @brief    Set RTCB Output Time Mark Signal
  * @rmtoll   TMSEL    TMSEL    FL_RTCB_SetTimeMarkOutput
  * @param    RTCBx RTCB instance
  * @param    markSelect This parameter can be one of the following values:
  *           @arg @ref FL_RTCB_TIME_MARK_CLOSE
  *           @arg @ref FL_RTCB_TIME_MARK_XTLF
  *           @arg @ref FL_RTCB_TIME_MARK_SECOND
  *           @arg @ref FL_RTCB_TIME_MARK_MINUTE
  *           @arg @ref FL_RTCB_TIME_MARK_HOUR
  *           @arg @ref FL_RTCB_TIME_MARK_DAY
  *           @arg @ref FL_RTCB_TIME_MARK_32_SEC
  *           @arg @ref FL_RTCB_TIME_MARK_SEC
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_SetTimeMarkOutput(RTCB_Type *RTCBx, uint32_t markSelect)
{
    MODIFY_REG(RTCBx->TMSEL, RTCB_TMSEL_TMSEL_Msk, markSelect);
}

/**
  * @brief    Get RTCB Output Time Mark Signal Setting
  * @rmtoll   TMSEL    TMSEL    FL_RTCB_GetTimeMarkOutput
  * @param    RTCBx RTCB instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCB_TIME_MARK_CLOSE
  *           @arg @ref FL_RTCB_TIME_MARK_XTLF
  *           @arg @ref FL_RTCB_TIME_MARK_SECOND
  *           @arg @ref FL_RTCB_TIME_MARK_MINUTE
  *           @arg @ref FL_RTCB_TIME_MARK_HOUR
  *           @arg @ref FL_RTCB_TIME_MARK_DAY
  *           @arg @ref FL_RTCB_TIME_MARK_32_SEC
  *           @arg @ref FL_RTCB_TIME_MARK_SEC
  */
__STATIC_INLINE uint32_t FL_RTCB_GetTimeMarkOutput(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->TMSEL, RTCB_TMSEL_TMSEL_Msk));
}

/**
  * @brief    Get RTCB Adjust Value
  * @rmtoll   ADJR        FL_RTCB_ReadAdjustValue
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadAdjustValue(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ADJR, (0x1ffU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Adjust Value
  * @rmtoll   ADJR        FL_RTCB_WriteAdjustValue
  * @param    RTCBx RTCB instance
  * @param    adjustValue
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteAdjustValue(RTCB_Type *RTCBx, uint32_t adjustValue)
{
    MODIFY_REG(RTCBx->ADJR, (0x1ffU << 0U), (adjustValue << 0U));
}

/**
  * @brief    Set RTCB Adjust Direction
  * @rmtoll   ADJR    ADSIGN    FL_RTCB_SetAdjustDirection
  * @param    RTCBx RTCB instance
  * @param    adjustDir This parameter can be one of the following values:
  *           @arg @ref FL_RTCB_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTCB_ADJUST_DIR_DECREASE
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_SetAdjustDirection(RTCB_Type *RTCBx, uint32_t adjustDir)
{
    MODIFY_REG(RTCBx->ADJR, RTCB_ADJR_ADSIGN_Msk, adjustDir);
}

/**
  * @brief    Get RTCB Adjust Direction
  * @rmtoll   ADJR    ADSIGN    FL_RTCB_GetAdjustDirection
  * @param    RTCBx RTCB instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCB_ADJUST_DIR_INCREASE
  *           @arg @ref FL_RTCB_ADJUST_DIR_DECREASE
  */
__STATIC_INLINE uint32_t FL_RTCB_GetAdjustDirection(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->ADJR, RTCB_ADJR_ADSIGN_Msk));
}

/**
  * @brief    RTCB enable
  * @rmtoll   CR    EN    FL_RTCB_Enable
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_Enable(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->CR, RTCB_CR_EN_Msk);
}

/**
  * @brief    Get RTCB enable status
  * @rmtoll   CR    EN    FL_RTCB_IsEnabled
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabled(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->CR, RTCB_CR_EN_Msk) == RTCB_CR_EN_Msk);
}

/**
  * @brief    RTCB disable
  * @rmtoll   CR    EN    FL_RTCB_Disable
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_Disable(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->CR, RTCB_CR_EN_Msk);
}

/**
  * @brief    Set RTCB Tamper Source
  * @rmtoll   STPCR    TAMPSEL    FL_RTCB_SetTamperSource
  * @param    RTCBx RTCB instance
  * @param    select This parameter can be one of the following values:
  *           @arg @ref FL_RTCB_TIME_CLEAR_NONE
  *           @arg @ref FL_RTCB_TIME_CLEAR_TAMPER_PIN
  *           @arg @ref FL_RTCB_TIME_CLEAR_XTLF
  *           @arg @ref FL_RTCB_TIME_CLEAR_BOTH
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_SetTamperSource(RTCB_Type *RTCBx, uint32_t select)
{
    MODIFY_REG(RTCBx->STPCR, RTCB_STPCR_TAMPSEL_Msk, select);
}

/**
  * @brief    Get RTCB Tamper Source
  * @rmtoll   STPCR    TAMPSEL    FL_RTCB_GetTamperSource
  * @param    RTCBx RTCB instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCB_TIME_CLEAR_NONE
  *           @arg @ref FL_RTCB_TIME_CLEAR_TAMPER_PIN
  *           @arg @ref FL_RTCB_TIME_CLEAR_XTLF
  *           @arg @ref FL_RTCB_TIME_CLEAR_BOTH
  */
__STATIC_INLINE uint32_t FL_RTCB_GetTamperSource(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCR, RTCB_STPCR_TAMPSEL_Msk));
}

/**
  * @brief    RTCB Tamper Pin Digital Filter enable
  * @rmtoll   STPCR    DF    FL_RTCB_EnableTamperPinDigitalFilter
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableTamperPinDigitalFilter(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->STPCR, RTCB_STPCR_DF_Msk);
}

/**
  * @brief    Get RTCB Tamper Pin Digital Filter enable  status
  * @rmtoll   STPCR    DF    FL_RTCB_IsEnabledTamperPinDigitalFilter
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledTamperPinDigitalFilter(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCR, RTCB_STPCR_DF_Msk) == RTCB_STPCR_DF_Msk);
}

/**
  * @brief    RTCB Tamper Pin Digital Filter disable
  * @rmtoll   STPCR    DF    FL_RTCB_DisableTamperPinDigitalFilter
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableTamperPinDigitalFilter(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->STPCR, RTCB_STPCR_DF_Msk);
}

/**
  * @brief    Set RTCB Time Stamp Edge
  * @rmtoll   STPCR    TSEDGE    FL_RTCB_SetTimeStampEdge
  * @param    RTCBx RTCB instance
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_RTCB_TIMESTAMP_EDGE_RISING
  *           @arg @ref FL_RTCB_TIMESTAMP_EDGE_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_SetTimeStampEdge(RTCB_Type *RTCBx, uint32_t edge)
{
    MODIFY_REG(RTCBx->STPCR, RTCB_STPCR_TSEDGE_Msk, edge);
}

/**
  * @brief    Get RTCB Time Stamp Edge
  * @rmtoll   STPCR    TSEDGE    FL_RTCB_GetTimeStampEdge
  * @param    RTCBx RTCB instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_RTCB_TIMESTAMP_EDGE_RISING
  *           @arg @ref FL_RTCB_TIMESTAMP_EDGE_FALLING
  */
__STATIC_INLINE uint32_t FL_RTCB_GetTimeStampEdge(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCR, RTCB_STPCR_TSEDGE_Msk));
}

/**
  * @brief    RTCB Tamper enable
  * @rmtoll   STPCR    TAMPEN    FL_RTCB_EnableTamper
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableTamper(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->STPCR, RTCB_STPCR_TAMPEN_Msk);
}

/**
  * @brief    Get RTCB Tamper enable  status
  * @rmtoll   STPCR    TAMPEN    FL_RTCB_IsEnabledTamper
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledTamper(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCR, RTCB_STPCR_TAMPEN_Msk) == RTCB_STPCR_TAMPEN_Msk);
}

/**
  * @brief    RTCB Tamper Disable
  * @rmtoll   STPCR    TAMPEN    FL_RTCB_DisableTamper
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableTamper(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->STPCR, RTCB_STPCR_TAMPEN_Msk);
}

/**
  * @brief    RTCB Time Stamp enable
  * @rmtoll   STPCR    TSEN    FL_RTCB_EnableTimestamp
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_EnableTimestamp(RTCB_Type *RTCBx)
{
    SET_BIT(RTCBx->STPCR, RTCB_STPCR_TSEN_Msk);
}

/**
  * @brief    Get RTCB Time Stamp enable  status
  * @rmtoll   STPCR    TSEN    FL_RTCB_IsEnabledTimestamp
  * @param    RTCBx RTCB instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_RTCB_IsEnabledTimestamp(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCR, RTCB_STPCR_TSEN_Msk) == RTCB_STPCR_TSEN_Msk);
}

/**
  * @brief    RTCB Time Stamp Disable
  * @rmtoll   STPCR    TSEN    FL_RTCB_DisableTimestamp
  * @param    RTCBx RTCB instance
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_DisableTimestamp(RTCB_Type *RTCBx)
{
    CLEAR_BIT(RTCBx->STPCR, RTCB_STPCR_TSEN_Msk);
}

/**
  * @brief    Get RTCB Stamp Hour Value
  * @rmtoll   STPCLKRR        FL_RTCB_ReadTimestampHour
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampHour(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCLKRR, (0x3fU << 16U)) >> 16U);
}

/**
  * @brief    Set RTCB Stamp Hour Value
  * @rmtoll   STPCLKRR        FL_RTCB_WriteTimestampHour
  * @param    RTCBx RTCB instance
  * @param    hour
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampHour(RTCB_Type *RTCBx, uint32_t hour)
{
    MODIFY_REG(RTCBx->STPCLKRR, (0x3fU << 16U), (hour << 16U));
}

/**
  * @brief    Get RTCB Stamp Minute Value
  * @rmtoll   STPCLKRR        FL_RTCB_ReadTimestampMinute
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampMinute(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCLKRR, (0x7fU << 8U)) >> 8U);
}

/**
  * @brief    Set RTCB Stamp Minute Value
  * @rmtoll   STPCLKRR        FL_RTCB_WriteTimestampMinute
  * @param    RTCBx RTCB instance
  * @param    minute
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampMinute(RTCB_Type *RTCBx, uint32_t minute)
{
    MODIFY_REG(RTCBx->STPCLKRR, (0x7fU << 8U), (minute << 8U));
}

/**
  * @brief    Get RTCB Stamp Second Value
  * @rmtoll   STPCLKRR        FL_RTCB_ReadTimestampSecond
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampSecond(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCLKRR, (0x7fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Stamp Second Value
  * @rmtoll   STPCLKRR        FL_RTCB_WriteTimestampSecond
  * @param    RTCBx RTCB instance
  * @param    second
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampSecond(RTCB_Type *RTCBx, uint32_t second)
{
    MODIFY_REG(RTCBx->STPCLKRR, (0x7fU << 0U), (second << 0U));
}

/**
  * @brief    Get RTCB Stamp Year Value
  * @rmtoll   STPCALRR        FL_RTCB_ReadTimestampYear
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampYear(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCALRR, (0xffU << 24U)) >> 24U);
}

/**
  * @brief    Set RTCB Stamp Year Value
  * @rmtoll   STPCALRR        FL_RTCB_WriteTimestampYear
  * @param    RTCBx RTCB instance
  * @param    year
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampYear(RTCB_Type *RTCBx, uint32_t year)
{
    MODIFY_REG(RTCBx->STPCALRR, (0xffU << 24U), (year << 24U));
}

/**
  * @brief    Get RTCB Stamp Month Value
  * @rmtoll   STPCALRR        FL_RTCB_ReadTimestampMonth
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampMonth(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCALRR, (0x1fU << 16U)) >> 16U);
}

/**
  * @brief    Set RTCB Stamp Month Value
  * @rmtoll   STPCALRR        FL_RTCB_WriteTimestampMonth
  * @param    RTCBx RTCB instance
  * @param    month
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampMonth(RTCB_Type *RTCBx, uint32_t month)
{
    MODIFY_REG(RTCBx->STPCALRR, (0x1fU << 16U), (month << 16U));
}

/**
  * @brief    Get RTCB Stamp Day Value
  * @rmtoll   STPCALRR        FL_RTCB_ReadTimestampDay
  * @param    RTCBx RTCB instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadTimestampDay(RTCB_Type *RTCBx)
{
    return (uint32_t)(READ_BIT(RTCBx->STPCALRR, (0x3fU << 0U)) >> 0U);
}

/**
  * @brief    Set RTCB Stamp Day Value
  * @rmtoll   STPCALRR        FL_RTCB_WriteTimestampDay
  * @param    RTCBx RTCB instance
  * @param    day
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteTimestampDay(RTCB_Type *RTCBx, uint32_t day)
{
    MODIFY_REG(RTCBx->STPCALRR, (0x3fU << 0U), (day << 0U));
}

/**
  * @brief    Get RTCB Backup Register
  * @rmtoll   BACKUP        FL_RTCB_ReadBackupRegisters
  * @param    RTCBx RTCB instance
  * @param    backupRegNum This parameter can be one of the following values:
  *           @arg @ref FL_RTCB_BACKUP_0
  *           @arg @ref FL_RTCB_BACKUP_1
  *           @arg @ref FL_RTCB_BACKUP_2
  *           @arg @ref FL_RTCB_BACKUP_3
  *           @arg @ref FL_RTCB_BACKUP_4
  * @retval
  */
__STATIC_INLINE uint32_t FL_RTCB_ReadBackupRegisters(RTCB_Type *RTCBx, uint32_t backupRegNum)
{
    FL_RTCB_Backup_ADDR  *addr = (FL_RTCB_Backup_ADDR *)&RTCBx->BKR0;
    return (uint32_t)(READ_BIT(addr->backup[backupRegNum], 0xFFFFFFFFu));
}

/**
  * @brief    Set RTCB Backup Register
  * @rmtoll   BACKUP        FL_RTCB_WriteBackupRegisters
  * @param    RTCBx RTCB instance
  * @param    backupReg
  * @param    backupNum
  * @retval   None
  */
__STATIC_INLINE void FL_RTCB_WriteBackupRegisters(RTCB_Type *RTCBx, uint32_t backupReg, uint32_t backupNum)
{
    FL_RTCB_Backup_ADDR  *addr = (FL_RTCB_Backup_ADDR *)&RTCBx->BKR0;
    MODIFY_REG(addr->backup[backupNum], (0xFFFFFFFFu), backupReg);
}

/**
  * @}
  */

/** @defgroup RTCB_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_RTCB_DeInit(RTCB_Type *RTCBx);
void FL_RTCB_StructInit(FL_RTCB_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCB_GetTime(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCB_Init(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct);
FL_ErrorStatus FL_RTCB_ConfigTime(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct);

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

#endif /* __FM33LG0XX_FL_RTCB_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

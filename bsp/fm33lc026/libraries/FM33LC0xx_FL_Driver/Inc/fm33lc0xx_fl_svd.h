/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_svd.h
  * @author  FMSH Application Team
  * @brief   Head file of SVD FL Module
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
#ifndef __FM33LC0XX_FL_SVD_H
#define __FM33LC0XX_FL_SVD_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup SVD SVD
  * @brief SVD FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup SVD_FL_ES_INIT SVD Exported Init structures
  * @{
  */

/**
  * @brief SVD Init Sturcture definition
  */
typedef struct
{
    /* 参考电压 */
    uint32_t referenceVoltage;

    /* 报警阈值 */
    uint32_t warningThreshold;

    /* 数字滤波 */
    uint32_t digitalFilter;

    /* SVS通道选择 */
    uint32_t SVSChannel;

} FL_SVD_InitTypeDef;

/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup SVD_FL_Exported_Constants SVD Exported Constants
  * @{
  */

#define    SVD_CFGR_ADSVD_SEL_Pos                                 (9U)
#define    SVD_CFGR_ADSVD_SEL_Msk                                 (0x7U << SVD_CFGR_ADSVD_SEL_Pos)
#define    SVD_CFGR_ADSVD_SEL                                     SVD_CFGR_ADSVD_SEL_Msk

#define    SVD_CFGR_ADSVD_EN_Pos                                  (8U)
#define    SVD_CFGR_ADSVD_EN_Msk                                  (0x1U << SVD_CFGR_ADSVD_EN_Pos)
#define    SVD_CFGR_ADSVD_EN                                      SVD_CFGR_ADSVD_EN_Msk

#define    SVD_CFGR_LVL_Pos                                       (4U)
#define    SVD_CFGR_LVL_Msk                                       (0xfU << SVD_CFGR_LVL_Pos)
#define    SVD_CFGR_LVL                                           SVD_CFGR_LVL_Msk

#define    SVD_CFGR_DFEN_Pos                                      (3U)
#define    SVD_CFGR_DFEN_Msk                                      (0x1U << SVD_CFGR_DFEN_Pos)
#define    SVD_CFGR_DFEN                                          SVD_CFGR_DFEN_Msk

#define    SVD_CFGR_MOD_Pos                                       (2U)
#define    SVD_CFGR_MOD_Msk                                       (0x1U << SVD_CFGR_MOD_Pos)
#define    SVD_CFGR_MOD                                           SVD_CFGR_MOD_Msk

#define    SVD_CFGR_ITVL_Pos                                      (0U)
#define    SVD_CFGR_ITVL_Msk                                      (0x3U << SVD_CFGR_ITVL_Pos)
#define    SVD_CFGR_ITVL                                          SVD_CFGR_ITVL_Msk

#define    SVD_CR_SVSEN_Pos                                       (1U)
#define    SVD_CR_SVSEN_Msk                                       (0x1U << SVD_CR_SVSEN_Pos)
#define    SVD_CR_SVSEN                                           SVD_CR_SVSEN_Msk

#define    SVD_CR_EN_Pos                                          (0U)
#define    SVD_CR_EN_Msk                                          (0x1U << SVD_CR_EN_Pos)
#define    SVD_CR_EN                                              SVD_CR_EN_Msk

#define    SVD_IER_PFIE_Pos                                       (1U)
#define    SVD_IER_PFIE_Msk                                       (0x1U << SVD_IER_PFIE_Pos)
#define    SVD_IER_PFIE                                           SVD_IER_PFIE_Msk

#define    SVD_IER_PRIE_Pos                                       (0U)
#define    SVD_IER_PRIE_Msk                                       (0x1U << SVD_IER_PRIE_Pos)
#define    SVD_IER_PRIE                                           SVD_IER_PRIE_Msk

#define    SVD_ISR_ADLVDO_Pos                                     (16U)
#define    SVD_ISR_ADLVDO_Msk                                     (0x1U << SVD_ISR_ADLVDO_Pos)
#define    SVD_ISR_ADLVDO                                         SVD_ISR_ADLVDO_Msk

#define    SVD_ISR_SVDO_Pos                                       (8U)
#define    SVD_ISR_SVDO_Msk                                       (0x1U << SVD_ISR_SVDO_Pos)
#define    SVD_ISR_SVDO                                           SVD_ISR_SVDO_Msk

#define    SVD_ISR_SVDR_Pos                                       (7U)
#define    SVD_ISR_SVDR_Msk                                       (0x1U << SVD_ISR_SVDR_Pos)
#define    SVD_ISR_SVDR                                           SVD_ISR_SVDR_Msk

#define    SVD_ISR_PFF_Pos                                        (1U)
#define    SVD_ISR_PFF_Msk                                        (0x1U << SVD_ISR_PFF_Pos)
#define    SVD_ISR_PFF                                            SVD_ISR_PFF_Msk

#define    SVD_ISR_PRF_Pos                                        (0U)
#define    SVD_ISR_PRF_Msk                                        (0x1U << SVD_ISR_PRF_Pos)
#define    SVD_ISR_PRF                                            SVD_ISR_PRF_Msk

#define    SVD_VSR_EN_Pos                                         (0U)
#define    SVD_VSR_EN_Msk                                         (0x7U << SVD_VSR_EN_Pos)
#define    SVD_VSR_EN                                             SVD_VSR_EN_Msk



#define    FL_SVD_REFERENCE_1P2V                                  (0x1U << 2U)
#define    FL_SVD_REFERENCE_1P1V                                  (0x1U << 1U)
#define    FL_SVD_REFERENCE_1P0V                                  (0x1U << 0U)



#define    FL_SVD_ADC_THRESHOLD_3P300V                            (0x0U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_3P514V                            (0x1U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_3P729V                            (0x2U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_3P943V                            (0x3U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_4P157V                            (0x4U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_4P371V                            (0x5U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_4P586V                            (0x6U << SVD_CFGR_ADSVD_SEL_Pos)
#define    FL_SVD_ADC_THRESHOLD_4P800V                            (0x7U << SVD_CFGR_ADSVD_SEL_Pos)


#define    FL_SVD_WARNING_THRESHOLD_GROUP0                        (0x0U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP1                        (0x1U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP2                        (0x2U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP3                        (0x3U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP4                        (0x4U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP5                        (0x5U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP6                        (0x6U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP7                        (0x7U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP8                        (0x8U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP9                        (0x9U << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP10                       (0xaU << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP11                       (0xbU << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP12                       (0xcU << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP13                       (0xdU << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP14                       (0xeU << SVD_CFGR_LVL_Pos)
#define    FL_SVD_WARNING_THRESHOLD_GROUP15                       (0xfU << SVD_CFGR_LVL_Pos)


#define    FL_SVD_WORK_MODE_CONTINUOUS                            (0x0U << SVD_CFGR_MOD_Pos)
#define    FL_SVD_WORK_MODE_PERIODIC                              (0x1U << SVD_CFGR_MOD_Pos)


#define    FL_SVD_ENABLE_PERIOD_62MS                              (0x0U << SVD_CFGR_ITVL_Pos)
#define    FL_SVD_ENABLE_PERIOD_256MS                             (0x1U << SVD_CFGR_ITVL_Pos)
#define    FL_SVD_ENABLE_PERIOD_1000MS                            (0x2U << SVD_CFGR_ITVL_Pos)
#define    FL_SVD_ENABLE_PERIOD_4000MS                            (0x3U << SVD_CFGR_ITVL_Pos)


#define    FL_SVD_ADC_POWER_STATUS_RISING                         (0x0U << SVD_ISR_ADLVDO_Pos)
#define    FL_SVD_ADC_POWER_STATUS_FALLING                        (0x1U << SVD_ISR_ADLVDO_Pos)

#define    FL_SVD_POWER_STATUS_FALLING                            (0x0U << SVD_ISR_SVDO_Pos)
#define    FL_SVD_POWER_STATUS_RISING                             (0x1U << SVD_ISR_SVDO_Pos)

#define    FL_SVD_LATCHED_POWER_STATUS_FALLING                    (0x0U << SVD_ISR_SVDR_Pos)
#define    FL_SVD_LATCHED_POWER_STATUS_RISING                     (0x1U << SVD_ISR_SVDR_Pos)

/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup SVD_FL_Exported_Functions SVD Exported Functions
  * @{
  */

/**
  * @brief    Set ADC SVD Level
  * @rmtoll   CFGR    ADSVD_SEL    FL_SVD_SetADCThreshold
  * @param    SVDx SVD instance
  * @param    level This parameter can be one of the following values:
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P300V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P514V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P729V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P943V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P157V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P371V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P586V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P800V
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_SetADCThreshold(SVD_Type *SVDx, uint32_t level)
{
    MODIFY_REG(SVDx->CFGR, SVD_CFGR_ADSVD_SEL_Msk, level);
}

/**
  * @brief    Get ADC SVD Level
  * @rmtoll   CFGR    ADSVD_SEL    FL_SVD_GetADCThreshold
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P300V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P514V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P729V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_3P943V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P157V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P371V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P586V
  *           @arg @ref FL_SVD_ADC_THRESHOLD_4P800V
  */
__STATIC_INLINE uint32_t FL_SVD_GetADCThreshold(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CFGR, SVD_CFGR_ADSVD_SEL_Msk));
}

/**
  * @brief    Enable ADC SVD
  * @rmtoll   CFGR    ADSVD_EN    FL_SVD_EnableADCMonitor
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableADCMonitor(SVD_Type *SVDx)
{
    SET_BIT(SVDx->CFGR, SVD_CFGR_ADSVD_EN_Msk);
}

/**
  * @brief    Get ADC SVD Enable Status
  * @rmtoll   CFGR    ADSVD_EN    FL_SVD_IsEnabledADCMonitor
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledADCMonitor(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CFGR, SVD_CFGR_ADSVD_EN_Msk) == SVD_CFGR_ADSVD_EN_Msk);
}

/**
  * @brief    Disable ADC SVD
  * @rmtoll   CFGR    ADSVD_EN    FL_SVD_DisableADCMonitor
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableADCMonitor(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->CFGR, SVD_CFGR_ADSVD_EN_Msk);
}

/**
  * @brief    Set SVD Threshold Level
  * @rmtoll   CFGR    LVL    FL_SVD_SetWarningThreshold
  * @param    SVDx SVD instance
  * @param    level This parameter can be one of the following values:
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP0
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP1
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP2
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP3
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP4
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP5
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP6
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP7
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP8
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP9
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP10
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP11
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP12
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP13
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP14
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP15
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_SetWarningThreshold(SVD_Type *SVDx, uint32_t level)
{
    MODIFY_REG(SVDx->CFGR, SVD_CFGR_LVL_Msk, level);
}

/**
  * @brief    Get SVD Threshold Level
  * @rmtoll   CFGR    LVL    FL_SVD_GetWarningThreshold
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP0
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP1
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP2
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP3
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP4
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP5
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP6
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP7
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP8
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP9
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP10
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP11
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP12
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP13
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP14
  *           @arg @ref FL_SVD_WARNING_THRESHOLD_GROUP15
  */
__STATIC_INLINE uint32_t FL_SVD_GetWarningThreshold(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CFGR, SVD_CFGR_LVL_Msk));
}

/**
  * @brief    Enable SVD Digital Filtering
  * @rmtoll   CFGR    DFEN    FL_SVD_EnableDigitalFilter
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableDigitalFilter(SVD_Type *SVDx)
{
    SET_BIT(SVDx->CFGR, SVD_CFGR_DFEN_Msk);
}

/**
  * @brief    Get SVD Digital Filtering Enable Status
  * @rmtoll   CFGR    DFEN    FL_SVD_IsEnabledDigitalFilter
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledDigitalFilter(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CFGR, SVD_CFGR_DFEN_Msk) == SVD_CFGR_DFEN_Msk);
}

/**
  * @brief    Disable SVD Digital Filtering
  * @rmtoll   CFGR    DFEN    FL_SVD_DisableDigitalFilter
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableDigitalFilter(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->CFGR, SVD_CFGR_DFEN_Msk);
}

/**
  * @brief    Set SVD Working Mode
  * @rmtoll   CFGR    MOD    FL_SVD_SetWorkMode
  * @param    SVDx SVD instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_SVD_WORK_MODE_CONTINUOUS
  *           @arg @ref FL_SVD_WORK_MODE_PERIODIC
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_SetWorkMode(SVD_Type *SVDx, uint32_t mode)
{
    MODIFY_REG(SVDx->CFGR, SVD_CFGR_MOD_Msk, mode);
}

/**
  * @brief    Get SVD Working Mode
  * @rmtoll   CFGR    MOD    FL_SVD_GetWorkMode
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_WORK_MODE_CONTINUOUS
  *           @arg @ref FL_SVD_WORK_MODE_PERIODIC
  */
__STATIC_INLINE uint32_t FL_SVD_GetWorkMode(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CFGR, SVD_CFGR_MOD_Msk));
}

/**
  * @brief    Enable External SVS Channel
  * @rmtoll   CR    SVSEN    FL_SVD_EnableSVSChannel
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableSVSChannel(SVD_Type *SVDx)
{
    SET_BIT(SVDx->CR, SVD_CR_SVSEN_Msk);
}

/**
  * @brief    Get External SVS Channel Enable Status
  * @rmtoll   CR    SVSEN    FL_SVD_IsEnabledSVSChannel
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledSVSChannel(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CR, SVD_CR_SVSEN_Msk) == SVD_CR_SVSEN_Msk);
}

/**
  * @brief    Disable External SVS Channel
  * @rmtoll   CR    SVSEN    FL_SVD_DisableSVSChannel
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableSVSChannel(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->CR, SVD_CR_SVSEN_Msk);
}

/**
  * @brief    Enable SVD
  * @rmtoll   CR    EN    FL_SVD_Enable
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_Enable(SVD_Type *SVDx)
{
    SET_BIT(SVDx->CR, SVD_CR_EN_Msk);
}

/**
  * @brief    Get SVD Enable Status
  * @rmtoll   CR    EN    FL_SVD_IsEnabled
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabled(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->CR, SVD_CR_EN_Msk) == SVD_CR_EN_Msk);
}

/**
  * @brief    Disable SVD
  * @rmtoll   CR    EN    FL_SVD_Disable
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_Disable(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->CR, SVD_CR_EN_Msk);
}

/**
  * @brief    Enable Power Fall Interrupt
  * @rmtoll   IER    PFIE    FL_SVD_EnableIT_PowerFall
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableIT_PowerFall(SVD_Type *SVDx)
{
    SET_BIT(SVDx->IER, SVD_IER_PFIE_Msk);
}

/**
  * @brief    Get Power Fall Interrupt Status
  * @rmtoll   IER    PFIE    FL_SVD_IsEnabledIT_PowerFall
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledIT_PowerFall(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->IER, SVD_IER_PFIE_Msk) == SVD_IER_PFIE_Msk);
}

/**
  * @brief    Disable Power Fall Interrupt
  * @rmtoll   IER    PFIE    FL_SVD_DisableIT_PowerFall
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableIT_PowerFall(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->IER, SVD_IER_PFIE_Msk);
}

/**
  * @brief    Enable Power Rise Interrupt
  * @rmtoll   IER    PRIE    FL_SVD_EnableIT_PowerRise
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableIT_PowerRise(SVD_Type *SVDx)
{
    SET_BIT(SVDx->IER, SVD_IER_PRIE_Msk);
}

/**
  * @brief    Get Power Rise  Interrupt Status
  * @rmtoll   IER    PRIE    FL_SVD_IsEnabledIT_PowerRise
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledIT_PowerRise(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->IER, SVD_IER_PRIE_Msk) == SVD_IER_PRIE_Msk);
}

/**
  * @brief    Disable Power Rise Interrupt
  * @rmtoll   IER    PRIE    FL_SVD_DisableIT_PowerRise
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableIT_PowerRise(SVD_Type *SVDx)
{
    CLEAR_BIT(SVDx->IER, SVD_IER_PRIE_Msk);
}

/**
  * @brief    Get ADC SVD Status
  * @rmtoll   ISR    ADLVDO    FL_SVD_GetADCPowerStatus
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_ADC_POWER_STATUS_RISING
  *           @arg @ref FL_SVD_ADC_POWER_STATUS_FALLING
  */
__STATIC_INLINE uint32_t FL_SVD_GetADCPowerStatus(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->ISR, SVD_ISR_ADLVDO_Msk));
}

/**
  * @brief    Get SVD Status
  * @rmtoll   ISR    SVDO    FL_SVD_GetCurrentPowerStatus
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_POWER_STATUS_FALLING
  *           @arg @ref FL_SVD_POWER_STATUS_RISING
  */
__STATIC_INLINE uint32_t FL_SVD_GetCurrentPowerStatus(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->ISR, SVD_ISR_SVDO_Msk));
}

/**
  * @brief    Get SVD Latched Status
  * @rmtoll   ISR    SVDR    FL_SVD_GetLatchedPowerStatus
  * @param    SVDx SVD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_SVD_LATCHED_POWER_STATUS_FALLING
  *           @arg @ref FL_SVD_LATCHED_POWER_STATUS_RISING
  */
__STATIC_INLINE uint32_t FL_SVD_GetLatchedPowerStatus(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->ISR, SVD_ISR_SVDR_Msk));
}

/**
  * @brief    Get SVD Power Fall Flag
  * @rmtoll   ISR    PFF    FL_SVD_IsActiveFlag_PowerFall
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsActiveFlag_PowerFall(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->ISR, SVD_ISR_PFF_Msk) == (SVD_ISR_PFF_Msk));
}

/**
  * @brief    Clear SVD Power Fall Flag
  * @rmtoll   ISR    PFF    FL_SVD_ClearFlag_PowerFall
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_ClearFlag_PowerFall(SVD_Type *SVDx)
{
    WRITE_REG(SVDx->ISR, SVD_ISR_PFF_Msk);
}

/**
  * @brief    Get SVD Power Rise Flag
  * @rmtoll   ISR    PRF    FL_SVD_IsActiveFlag_PowerRise
  * @param    SVDx SVD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsActiveFlag_PowerRise(SVD_Type *SVDx)
{
    return (uint32_t)(READ_BIT(SVDx->ISR, SVD_ISR_PRF_Msk) == (SVD_ISR_PRF_Msk));
}

/**
  * @brief    Clear SVD Power Rise Flag
  * @rmtoll   ISR    PRF    FL_SVD_ClearFlag_PowerRise
  * @param    SVDx SVD instance
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_ClearFlag_PowerRise(SVD_Type *SVDx)
{
    WRITE_REG(SVDx->ISR, SVD_ISR_PRF_Msk);
}

/**
  * @brief    Enable SVD Reference
  * @rmtoll   VSR    EN    FL_SVD_EnableReference
  * @param    SVDx SVD instance
  * @param    ref This parameter can be one of the following values:
  *           @arg @ref FL_SVD_REFERENCE_1P2V
  *           @arg @ref FL_SVD_REFERENCE_1P1V
  *           @arg @ref FL_SVD_REFERENCE_1P0V
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_EnableReference(SVD_Type *SVDx, uint32_t ref)
{
    WRITE_REG(SVDx->VSR, ((ref & 0x7) << 0x0U));
}

/**
  * @brief    Get SVD Reference Enable Status
  * @rmtoll   VSR    EN    FL_SVD_IsEnabledReference
  * @param    SVDx SVD instance
  * @param    ref This parameter can be one of the following values:
  *           @arg @ref FL_SVD_REFERENCE_1P2V
  *           @arg @ref FL_SVD_REFERENCE_1P1V
  *           @arg @ref FL_SVD_REFERENCE_1P0V
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_SVD_IsEnabledReference(SVD_Type *SVDx, uint32_t ref)
{
    return (uint32_t)(READ_BIT(SVDx->VSR, ((ref & 0x7) << 0x0U)) == ((ref & 0x7) << 0x0U));
}

/**
  * @brief    Disable SVD Reference
  * @rmtoll   VSR    EN    FL_SVD_DisableReference
  * @param    SVDx SVD instance
  * @param    ref This parameter can be one of the following values:
  *           @arg @ref FL_SVD_REFERENCE_1P2V
  *           @arg @ref FL_SVD_REFERENCE_1P1V
  *           @arg @ref FL_SVD_REFERENCE_1P0V
  * @retval   None
  */
__STATIC_INLINE void FL_SVD_DisableReference(SVD_Type *SVDx, uint32_t ref)
{
    CLEAR_BIT(SVDx->VSR, ((ref & 0x7) << 0x0U));
}

/**
  * @}
  */

/** @defgroup SVD_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_SVD_DeInit(SVD_Type *SVDx);
FL_ErrorStatus FL_SVD_Init(SVD_Type *SVDx, FL_SVD_InitTypeDef *initStruct);
void FL_SVD_StructInit(FL_SVD_InitTypeDef *initStruct);

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

#endif /* __FM33LC0XX_FL_SVD_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-25*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/

/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_opa.h
  * @author  FMSH Application Team
  * @brief   Head file of OPA FL Module
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
#ifndef __FM33LC0XX_FL_OPA_H
#define __FM33LC0XX_FL_OPA_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup OPA OPA
  * @brief OPA FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup OPA_FL_ES_INIT OPA Exported Init structures
  * @{
  */

/**
  * @brief OPA Init Sturcture definition
  */
typedef struct
{
    /** 正向输入选择 */
    uint32_t INP;

    /** 反向输入选择*/
    uint32_t INN;

    /** OPA 工作模式*/
    uint32_t mode;

    /** 数字滤波器使能 */
    uint32_t digitalFilter;

    /** PGA反向输入到选择由Pin输入 */
    uint32_t negtiveToPin;

    /** PGA模式下的放大倍数*/
    uint32_t gain;

    /** 低功耗模式使能 */
    uint32_t lowPowermode;

} FL_OPA_InitTypeDef;

/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup OPA_FL_Exported_Constants OPA Exported Constants
  * @{
  */

#define    OPA_CR_BUFFEN_Pos                                      (31U)
#define    OPA_CR_BUFFEN_Msk                                      (0x1U << OPA_CR_BUFFEN_Pos)
#define    OPA_CR_BUFFEN                                          OPA_CR_BUFFEN_Msk

#define    OPA_CR_BUFBYP_Pos                                      (30U)
#define    OPA_CR_BUFBYP_Msk                                      (0x1U << OPA_CR_BUFBYP_Pos)
#define    OPA_CR_BUFBYP                                          OPA_CR_BUFBYP_Msk

#define    OPA_CR_VNSEL_Pos                                       (9U)
#define    OPA_CR_VNSEL_Msk                                       (0x7U << OPA_CR_VNSEL_Pos)
#define    OPA_CR_VNSEL                                           OPA_CR_VNSEL_Msk

#define    OPA_CR_VPSEL_Pos                                       (8U)
#define    OPA_CR_VPSEL_Msk                                       (0x1U << OPA_CR_VPSEL_Pos)
#define    OPA_CR_VPSEL                                           OPA_CR_VPSEL_Msk

#define    OPA_CR_DF_Pos                                          (7U)
#define    OPA_CR_DF_Msk                                          (0x1U << OPA_CR_DF_Pos)
#define    OPA_CR_DF                                              OPA_CR_DF_Msk

#define    OPA_CR_VN_EXC_Pos                                      (6U)
#define    OPA_CR_VN_EXC_Msk                                      (0x1U << OPA_CR_VN_EXC_Pos)
#define    OPA_CR_VN_EXC                                          OPA_CR_VN_EXC_Msk

#define    OPA_CR_PGA_GAIN_Pos                                    (4U)
#define    OPA_CR_PGA_GAIN_Msk                                    (0x3U << OPA_CR_PGA_GAIN_Pos)
#define    OPA_CR_PGA_GAIN                                        OPA_CR_PGA_GAIN_Msk

#define    OPA_CR_MOD_Pos                                         (2U)
#define    OPA_CR_MOD_Msk                                         (0x3U << OPA_CR_MOD_Pos)
#define    OPA_CR_MOD                                             OPA_CR_MOD_Msk

#define    OPA_CR_LPM_Pos                                         (1U)
#define    OPA_CR_LPM_Msk                                         (0x1U << OPA_CR_LPM_Pos)
#define    OPA_CR_LPM                                             OPA_CR_LPM_Msk

#define    OPA_CR_EN_Pos                                          (0U)
#define    OPA_CR_EN_Msk                                          (0x1U << OPA_CR_EN_Pos)
#define    OPA_CR_EN                                              OPA_CR_EN_Msk

#define    OPA_CALR_NCAL_EN_Pos                                   (31U)
#define    OPA_CALR_NCAL_EN_Msk                                   (0x1U << OPA_CALR_NCAL_EN_Pos)
#define    OPA_CALR_NCAL_EN                                       OPA_CALR_NCAL_EN_Msk

#define    OPA_CALR_NCAL_Pos                                      (16U)
#define    OPA_CALR_NCAL_Msk                                      (0x1fU << OPA_CALR_NCAL_Pos)
#define    OPA_CALR_NCAL                                          OPA_CALR_NCAL_Msk

#define    OPA_CALR_PCAL_EN_Pos                                   (15U)
#define    OPA_CALR_PCAL_EN_Msk                                   (0x1U << OPA_CALR_PCAL_EN_Pos)
#define    OPA_CALR_PCAL_EN                                       OPA_CALR_PCAL_EN_Msk

#define    OPA_CALR_PCAL_Pos                                      (0U)
#define    OPA_CALR_PCAL_Msk                                      (0x1fU << OPA_CALR_PCAL_Pos)
#define    OPA_CALR_PCAL                                          OPA_CALR_PCAL_Msk

#define    OPA_IER_FIE_Pos                                        (1U)
#define    OPA_IER_FIE_Msk                                        (0x1U << OPA_IER_FIE_Pos)
#define    OPA_IER_FIE                                            OPA_IER_FIE_Msk

#define    OPA_IER_RIE_Pos                                        (0U)
#define    OPA_IER_RIE_Msk                                        (0x1U << OPA_IER_RIE_Pos)
#define    OPA_IER_RIE                                            OPA_IER_RIE_Msk

#define    OPA_ISR_OUT_Pos                                        (15U)
#define    OPA_ISR_OUT_Msk                                        (0x1U << OPA_ISR_OUT_Pos)
#define    OPA_ISR_OUT                                            OPA_ISR_OUT_Msk

#define    OPA_ISR_FIF_Pos                                        (1U)
#define    OPA_ISR_FIF_Msk                                        (0x1U << OPA_ISR_FIF_Pos)
#define    OPA_ISR_FIF                                            OPA_ISR_FIF_Msk

#define    OPA_ISR_RIF_Pos                                        (0U)
#define    OPA_ISR_RIF_Msk                                        (0x1U << OPA_ISR_RIF_Pos)
#define    OPA_ISR_RIF                                            OPA_ISR_RIF_Msk






#define    FL_OPA_INN_SOURCE_INN1                                 (0x0U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_INN2                                 (0x1U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_VREF                                 (0x2U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_THREE_QUARTERS_VREF                  (0x3U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_HALF_VREF                            (0x4U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_ONE_QUARTER_VREF                     (0x5U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_ONE_EIGHTH_VREF                      (0x6U << OPA_CR_VNSEL_Pos)


#define    FL_OPA_INP_SOURCE_INP1                                 (0x0U << OPA_CR_VPSEL_Pos)
#define    FL_OPA_INP_SOURCE_INP2                                 (0x1U << OPA_CR_VPSEL_Pos)


#define    FL_OPA_GAIN_X2                                         (0x0U << OPA_CR_PGA_GAIN_Pos)
#define    FL_OPA_GAIN_X4                                         (0x1U << OPA_CR_PGA_GAIN_Pos)
#define    FL_OPA_GAIN_X8                                         (0x2U << OPA_CR_PGA_GAIN_Pos)
#define    FL_OPA_GAIN_X16                                        (0x3U << OPA_CR_PGA_GAIN_Pos)


#define    FL_OPA_MODE_STANDALONE                                 (0x0U << OPA_CR_MOD_Pos)
#define    FL_OPA_MODE_COMPARATOR                                 (0x1U << OPA_CR_MOD_Pos)
#define    FL_OPA_MODE_PGA                                        (0x2U << OPA_CR_MOD_Pos)
#define    FL_OPA_MODE_BUFFER                                     (0x3U << OPA_CR_MOD_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup OPA_FL_Exported_Functions OPA Exported Functions
  * @{
  */

/**
  * @brief    Enable VREF Buffer
  * @rmtoll   CR    BUFFEN    FL_OPA_EnableVrefBuffer
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableVrefBuffer(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_BUFFEN_Msk);
}

/**
  * @brief    Get VREF Buffer Enable Status
  * @rmtoll   CR    BUFFEN    FL_OPA_IsEnabledVrefBuffer
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledVrefBuffer(OPA_Type *OPAx)
{
    return (uint32_t)!(READ_BIT(OPAx->CR, OPA_CR_BUFFEN_Msk) == OPA_CR_BUFFEN_Msk);
}

/**
  * @brief    Disable VREF Buffer
  * @rmtoll   CR    BUFFEN    FL_OPA_DisableVrefBuffer
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableVrefBuffer(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_BUFFEN_Msk);
}

/**
  * @brief    Enable VREF Buffer Bypass
  * @rmtoll   CR    BUFBYP    FL_OPA_EnableBypassVrefBuffer
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableBypassVrefBuffer(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_BUFBYP_Msk);
}

/**
  * @brief    Get VREF Buffer Bypass Enable Status
  * @rmtoll   CR    BUFBYP    FL_OPA_IsEnabledBypassVrefBuffer
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledBypassVrefBuffer(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_BUFBYP_Msk) == OPA_CR_BUFBYP_Msk);
}

/**
  * @brief    Disable VREF Buffer Bypass
  * @rmtoll   CR    BUFBYP    FL_OPA_DisableBypassVrefBuffer
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableBypassVrefBuffer(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_BUFBYP_Msk);
}

/**
  * @brief    Set OPA Negative Input Channel
  * @rmtoll   CR    VNSEL    FL_OPA_SetINNSource
  * @param    OPAx OPA instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_OPA_INN_SOURCE_INN1
  *           @arg @ref FL_OPA_INN_SOURCE_INN2
  *           @arg @ref FL_OPA_INN_SOURCE_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_THREE_QUARTERS_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_HALF_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_ONE_QUARTER_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_ONE_EIGHTH_VREF
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_SetINNSource(OPA_Type *OPAx, uint32_t source)
{
    MODIFY_REG(OPAx->CR, OPA_CR_VNSEL_Msk, source);
}

/**
  * @brief    Get OPA Negative Input Channel Setting
  * @rmtoll   CR    VNSEL    FL_OPA_GetINNSource
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_INN_SOURCE_INN1
  *           @arg @ref FL_OPA_INN_SOURCE_INN2
  *           @arg @ref FL_OPA_INN_SOURCE_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_THREE_QUARTERS_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_HALF_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_ONE_QUARTER_VREF
  *           @arg @ref FL_OPA_INN_SOURCE_ONE_EIGHTH_VREF
  */
__STATIC_INLINE uint32_t FL_OPA_GetINNSource(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_VNSEL_Msk));
}

/**
  * @brief    Set OPA Positive Input Channel
  * @rmtoll   CR    VPSEL    FL_OPA_SetINPSource
  * @param    OPAx OPA instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_OPA_INP_SOURCE_INP1
  *           @arg @ref FL_OPA_INP_SOURCE_INP2
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_SetINPSource(OPA_Type *OPAx, uint32_t source)
{
    MODIFY_REG(OPAx->CR, OPA_CR_VPSEL_Msk, source);
}

/**
  * @brief    Get OPA Positive Input Channel Setting
  * @rmtoll   CR    VPSEL    FL_OPA_GetINPSource
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_INP_SOURCE_INP1
  *           @arg @ref FL_OPA_INP_SOURCE_INP2
  */
__STATIC_INLINE uint32_t FL_OPA_GetINPSource(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_VPSEL_Msk));
}

/**
  * @brief    Enable OPA Comparator Mode Output Digital Filter
  * @rmtoll   CR    DF    FL_OPA_EnableCOMPModeDigitalFilter
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableCOMPModeDigitalFilter(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_DF_Msk);
}

/**
  * @brief    Get OPA Comparator Mode Output Digital Filter Enable Status
  * @rmtoll   CR    DF    FL_OPA_IsEnabledCOMPModeDigitalFilter
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledCOMPModeDigitalFilter(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_DF_Msk) == OPA_CR_DF_Msk);
}

/**
  * @brief    Disable OPA Comparator Mode Output Digital Filter
  * @rmtoll   CR    DF    FL_OPA_DisableCOMPModeDigitalFilter
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableCOMPModeDigitalFilter(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_DF_Msk);
}

/**
  * @brief    Enable OPA Negtive Input Connected to GPIO
  * @rmtoll   CR    VN_EXC    FL_OPA_PGA_EnableINNConnectToPin
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_PGA_EnableINNConnectToPin(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_VN_EXC_Msk);
}

/**
  * @brief    Get OPA Negtive Input Connected to GPIO Enable Status
  * @rmtoll   CR    VN_EXC    FL_OPA_PGA_IsEnabledINNConnectToPin
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_PGA_IsEnabledINNConnectToPin(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_VN_EXC_Msk) == OPA_CR_VN_EXC_Msk);
}

/**
  * @brief    Disable OPA Negtive Input Connected to GPIO
  * @rmtoll   CR    VN_EXC    FL_OPA_PGA_DisableINNConnectToPin
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_PGA_DisableINNConnectToPin(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_VN_EXC_Msk);
}

/**
  * @brief    Set OPA PGA Mode Gain
  * @rmtoll   CR    PGA_GAIN    FL_OPA_PGA_SetGain
  * @param    OPAx OPA instance
  * @param    value This parameter can be one of the following values:
  *           @arg @ref FL_OPA_GAIN_X2
  *           @arg @ref FL_OPA_GAIN_X4
  *           @arg @ref FL_OPA_GAIN_X8
  *           @arg @ref FL_OPA_GAIN_X16
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_PGA_SetGain(OPA_Type *OPAx, uint32_t value)
{
    MODIFY_REG(OPAx->CR, OPA_CR_PGA_GAIN_Msk, value);
}

/**
  * @brief    Get OPA PGA Mode Gain Setting
  * @rmtoll   CR    PGA_GAIN    FL_OPA_PGA_GetGain
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_GAIN_X2
  *           @arg @ref FL_OPA_GAIN_X4
  *           @arg @ref FL_OPA_GAIN_X8
  *           @arg @ref FL_OPA_GAIN_X16
  */
__STATIC_INLINE uint32_t FL_OPA_PGA_GetGain(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_PGA_GAIN_Msk));
}

/**
  * @brief    Set OPA Mode
  * @rmtoll   CR    MOD    FL_OPA_SetMode
  * @param    OPAx OPA instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_OPA_MODE_STANDALONE
  *           @arg @ref FL_OPA_MODE_COMPARATOR
  *           @arg @ref FL_OPA_MODE_PGA
  *           @arg @ref FL_OPA_MODE_BUFFER
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_SetMode(OPA_Type *OPAx, uint32_t mode)
{
    MODIFY_REG(OPAx->CR, OPA_CR_MOD_Msk, mode);
}

/**
  * @brief    Get OPA Mode Setting
  * @rmtoll   CR    MOD    FL_OPA_GetMode
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_MODE_STANDALONE
  *           @arg @ref FL_OPA_MODE_COMPARATOR
  *           @arg @ref FL_OPA_MODE_PGA
  *           @arg @ref FL_OPA_MODE_BUFFER
  */
__STATIC_INLINE uint32_t FL_OPA_GetMode(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_MOD_Msk));
}

/**
  * @brief    Enable OPA Low Power Mode
  * @rmtoll   CR    LPM    FL_OPA_EnableLowPowerMode
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableLowPowerMode(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_LPM_Msk);
}

/**
  * @brief    Get OPA Low Power Mode Enable Status
  * @rmtoll   CR    LPM    FL_OPA_IsEnabledLowPowerMode
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledLowPowerMode(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_LPM_Msk) == OPA_CR_LPM_Msk);
}

/**
  * @brief    Disable OPA Low Power Mode
  * @rmtoll   CR    LPM    FL_OPA_DisableLowPowerMode
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableLowPowerMode(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_LPM_Msk);
}

/**
  * @brief    Enable OPA
  * @rmtoll   CR    EN    FL_OPA_Enable
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_Enable(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_EN_Msk);
}

/**
  * @brief    Get OPA Enable Status
  * @rmtoll   CR    EN    FL_OPA_IsEnabled
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabled(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_EN_Msk) == OPA_CR_EN_Msk);
}

/**
  * @brief    Disable OPA
  * @rmtoll   CR    EN    FL_OPA_Disable
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_Disable(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CR, OPA_CR_EN_Msk);
}

/**
  * @brief    Enable OPA Negative Input Calibration
  * @rmtoll   CALR    NCAL_EN    FL_OPA_EnableINNTrim
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableINNTrim(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CALR, OPA_CALR_NCAL_EN_Msk);
}

/**
  * @brief    Get OPA Negative Input Calibration Enable Status
  * @rmtoll   CALR    NCAL_EN    FL_OPA_IsEnabledINNTrim
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledINNTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, OPA_CALR_NCAL_EN_Msk) == OPA_CALR_NCAL_EN_Msk);
}

/**
  * @brief    Disable OPA Negative Input Calibration
  * @rmtoll   CALR    NCAL_EN    FL_OPA_DisableINNTrim
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableINNTrim(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CALR, OPA_CALR_NCAL_EN_Msk);
}

/**
  * @brief    Set OPA Negative Trim Value
  * @rmtoll   CALR    NCAL    FL_OPA_WriteNegativeTrim
  * @param    OPAx OPA instance
  * @param    value
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_WriteNegativeTrim(OPA_Type *OPAx, uint32_t value)
{
    MODIFY_REG(OPAx->CALR, (0x1fU << 16U), (value << 16U));
}

/**
  * @brief    Get OPA Negative Trim Value
  * @rmtoll   CALR    NCAL    FL_OPA_ReadNegativeTrim
  * @param    OPAx OPA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadNegativeTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, (0x1fU << 16U)) >> 16U);
}

/**
  * @brief    Enable OPA Positive Input Calibration
  * @rmtoll   CALR    PCAL_EN    FL_OPA_EnableINPTrim
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableINPTrim(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CALR, OPA_CALR_PCAL_EN_Msk);
}

/**
  * @brief    Get OPA Positive Input Calibration Enable Status
  * @rmtoll   CALR    PCAL_EN    FL_OPA_IsEnabledINPTrim
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledINPTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, OPA_CALR_PCAL_EN_Msk) == OPA_CALR_PCAL_EN_Msk);
}

/**
  * @brief    Disable OPA Positive Input Calibration
  * @rmtoll   CALR    PCAL_EN    FL_OPA_DisableINPTrim
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableINPTrim(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->CALR, OPA_CALR_PCAL_EN_Msk);
}

/**
  * @brief    Set OPA Positive Trim Value
  * @rmtoll   CALR    PCAL    FL_OPA_WritePositiveTrim
  * @param    OPAx OPA instance
  * @param    value
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_WritePositiveTrim(OPA_Type *OPAx, uint32_t value)
{
    MODIFY_REG(OPAx->CALR, (0x1fU << 0U), (value << 0U));
}

/**
  * @brief    Get OPA Positive Trim Value
  * @rmtoll   CALR    PCAL    FL_OPA_ReadPositiveTrim
  * @param    OPAx OPA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadPositiveTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, (0x1fU << 0U)) >> 0U);
}

/**
  * @brief    Enable OPA Comparator Mode Fall Interrupt
  * @rmtoll   IER    FIE    FL_OPA_EnableIT_FallingEdge
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableIT_FallingEdge(OPA_Type *OPAx)
{
    SET_BIT(OPAx->IER, OPA_IER_FIE_Msk);
}

/**
  * @brief    Get OPA Comparator Mode Fall Interrupt Enable Status
  * @rmtoll   IER    FIE    FL_OPA_IsEnabledIT_FallingEdge
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledIT_FallingEdge(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->IER, OPA_IER_FIE_Msk) == OPA_IER_FIE_Msk);
}

/**
  * @brief    Disable OPA Comparator Mode Fall Interrupt
  * @rmtoll   IER    FIE    FL_OPA_DisableIT_FallingEdge
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableIT_FallingEdge(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->IER, OPA_IER_FIE_Msk);
}

/**
  * @brief    Enable OPA Comparator Mode Rise Interrupt
  * @rmtoll   IER    RIE    FL_OPA_EnableIT_RisingEdge
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_EnableIT_RisingEdge(OPA_Type *OPAx)
{
    SET_BIT(OPAx->IER, OPA_IER_RIE_Msk);
}

/**
  * @brief    Get OPA Comparator Mode Rise Interrupt Enable Status
  * @rmtoll   IER    RIE    FL_OPA_IsEnabledIT_RisingEdge
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsEnabledIT_RisingEdge(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->IER, OPA_IER_RIE_Msk) == OPA_IER_RIE_Msk);
}

/**
  * @brief    Disable OPA Comparator Mode Rise Interrupt
  * @rmtoll   IER    RIE    FL_OPA_DisableIT_RisingEdge
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_DisableIT_RisingEdge(OPA_Type *OPAx)
{
    CLEAR_BIT(OPAx->IER, OPA_IER_RIE_Msk);
}

/**
  * @brief    Get OPA Comparator Mode Output Level
  * @rmtoll   ISR    OUT    FL_OPA_ReadCOMPModeOutput
  * @param    RNGx RNG instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadCOMPModeOutput(OPA_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->ISR, (0x1U << 15U)) >> 15U);
}

/**
  * @brief    Get OPA Comparator Mode Fall Interrupt Flag
  * @rmtoll   ISR    FIF    FL_OPA_IsActiveFlag_FallingEdge
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsActiveFlag_FallingEdge(OPA_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->ISR, OPA_ISR_FIF_Msk) == (OPA_ISR_FIF_Msk));
}

/**
  * @brief    Clear OPA Comparator Mode Fall Interrupt Flag
  * @rmtoll   ISR    FIF    FL_OPA_ClearFlag_FallingEdge
  * @param    RNGx RNG instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_ClearFlag_FallingEdge(OPA_Type *RNGx)
{
    WRITE_REG(RNGx->ISR, OPA_ISR_FIF_Msk);
}

/**
  * @brief    Get OPA Comparator Mode Rise Interrupt Flag
  * @rmtoll   ISR    RIF    FL_OPA_IsActiveFlag_RisingEdge
  * @param    RNGx RNG instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_IsActiveFlag_RisingEdge(OPA_Type *RNGx)
{
    return (uint32_t)(READ_BIT(RNGx->ISR, OPA_ISR_RIF_Msk) == (OPA_ISR_RIF_Msk));
}

/**
  * @brief    Clear OPA Comparator Mode Rise Interrupt Flag
  * @rmtoll   ISR    RIF    FL_OPA_ClearFlag_RisingEdge
  * @param    RNGx RNG instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_ClearFlag_RisingEdge(OPA_Type *RNGx)
{
    WRITE_REG(RNGx->ISR, OPA_ISR_RIF_Msk);
}

/**
  * @}
  */

/** @defgroup OPA_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_OPA_DeInit(OPA_Type *OPAx);
void FL_OPA_StructInit(FL_OPA_InitTypeDef *initStruct);
FL_ErrorStatus FL_OPA_Init(OPA_Type *OPAx, FL_OPA_InitTypeDef *initStruct);

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

#endif /* __FM33LC0XX_FL_OPA_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/

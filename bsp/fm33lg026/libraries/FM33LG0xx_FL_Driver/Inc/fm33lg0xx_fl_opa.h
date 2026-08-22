/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_opa.h
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
#ifndef __FM33LG0XX_FL_OPA_H
#define __FM33LG0XX_FL_OPA_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
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
  * @brief FL OPA Init Sturcture definition
  */
typedef struct
{
    /*! 正向输入选择 */
    uint32_t INP;
    /*! 反向输入选择*/
    uint32_t INN;
    /*!  OPA 工作模式*/
    uint32_t mode;
    /*! PGA反向输入到选择由Pin输入 */
    uint32_t negtiveToPin;
    /*! PGA模式下的放大倍数*/
    uint32_t gain;
    /*! 低功耗模式使能 */
    uint32_t lowPowermode;
    /*PGA模式选择*/
    uint32_t PGAModeSelect;

} FL_OPA_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup OPA_FL_Exported_Constants OPA Exported Constants
  * @{
  */

#define    OPA_CR_MSEL_Pos                                        (14U)
#define    OPA_CR_MSEL_Msk                                        (0x3U << OPA_CR_MSEL_Pos)
#define    OPA_CR_MSEL                                            OPA_CR_MSEL_Msk

#define    OPA_CR_VNSEL_Pos                                       (10U)
#define    OPA_CR_VNSEL_Msk                                       (0x3U << OPA_CR_VNSEL_Pos)
#define    OPA_CR_VNSEL                                           OPA_CR_VNSEL_Msk

#define    OPA_CR_VPSEL_Pos                                       (8U)
#define    OPA_CR_VPSEL_Msk                                       (0x3U << OPA_CR_VPSEL_Pos)
#define    OPA_CR_VPSEL                                           OPA_CR_VPSEL_Msk

#define    OPA_CR_VN_EXC_Pos                                      (6U)
#define    OPA_CR_VN_EXC_Msk                                      (0x1U << OPA_CR_VN_EXC_Pos)
#define    OPA_CR_VN_EXC                                          OPA_CR_VN_EXC_Msk

#define    OPA_CR_PGA_GAIN_Pos                                    (4U)
#define    OPA_CR_PGA_GAIN_Msk                                    (0x3U << OPA_CR_PGA_GAIN_Pos)
#define    OPA_CR_PGA_GAIN                                        OPA_CR_PGA_GAIN_Msk

#define    OPA_CR_FBSEL_Pos                                       (2U)
#define    OPA_CR_FBSEL_Msk                                       (0x3U << OPA_CR_FBSEL_Pos)
#define    OPA_CR_FBSEL                                           OPA_CR_FBSEL_Msk

#define    OPA_CR_LPM_Pos                                         (1U)
#define    OPA_CR_LPM_Msk                                         (0x1U << OPA_CR_LPM_Pos)
#define    OPA_CR_LPM                                             OPA_CR_LPM_Msk

#define    OPA_CR_EN_Pos                                          (0U)
#define    OPA_CR_EN_Msk                                          (0x1U << OPA_CR_EN_Pos)
#define    OPA_CR_EN                                              OPA_CR_EN_Msk

#define    OPA_CALR_NCAL_Pos                                      (16U)
#define    OPA_CALR_NCAL_Msk                                      (0xffU << OPA_CALR_NCAL_Pos)
#define    OPA_CALR_NCAL                                          OPA_CALR_NCAL_Msk

#define    OPA_CALR_PCAL_Pos                                      (8U)
#define    OPA_CALR_PCAL_Msk                                      (0xffU << OPA_CALR_PCAL_Pos)
#define    OPA_CALR_PCAL                                          OPA_CALR_PCAL_Msk

#define    OPA_CALR_NCAL_EN_Pos                                   (2U)
#define    OPA_CALR_NCAL_EN_Msk                                   (0x1U << OPA_CALR_NCAL_EN_Pos)
#define    OPA_CALR_NCAL_EN                                       OPA_CALR_NCAL_EN_Msk

#define    OPA_CALR_PCAL_EN_Pos                                   (1U)
#define    OPA_CALR_PCAL_EN_Msk                                   (0x1U << OPA_CALR_PCAL_EN_Pos)
#define    OPA_CALR_PCAL_EN                                       OPA_CALR_PCAL_EN_Msk

#define    OPA_CALR_TRIM_MODE_Pos                                 (0U)
#define    OPA_CALR_TRIM_MODE_Msk                                 (0x1U << OPA_CALR_TRIM_MODE_Pos)
#define    OPA_CALR_TRIM_MODE                                     OPA_CALR_TRIM_MODE_Msk

#define    OPA_COR_OUT_Pos                                        (0U)
#define    OPA_COR_OUT_Msk                                        (0x1U << OPA_COR_OUT_Pos)
#define    OPA_COR_OUT                                            OPA_COR_OUT_Msk



#define    FL_OPA_GAIN_NOINVERT_X2                                (0x0U << 4U)
#define    FL_OPA_GAIN_NOINVERT_X4                                (0x1U << 4U)
#define    FL_OPA_GAIN_NOINVERT_X8                                (0x2U << 4U)
#define    FL_OPA_GAIN_NOINVERT_X16                               (0x3U << 4U)
#define    FL_OPA_GAIN_INVERT_X1                                  (0x0U << 4U)
#define    FL_OPA_GAIN_INVERT_X3                                  (0x1U << 4U)
#define    FL_OPA_GAIN_INVERT_X7                                  (0x2U << 4U)
#define    FL_OPA_GAIN_INVERT_X15                                 (0x3U << 4U)



#define    FL_OPA_PGA_MODE_FB_TO_NEGATIVE                         (0x1U << OPA_CR_MSEL_Pos)
#define    FL_OPA_PGA_MODE_FB_TO_GND                              (0x2U << OPA_CR_MSEL_Pos)


#define    FL_OPA_INN_SOURCE_INN1                                 (0x0U << OPA_CR_VNSEL_Pos)
#define    FL_OPA_INN_SOURCE_INN2                                 (0x1U << OPA_CR_VNSEL_Pos)


#define    FL_OPA_INP_SOURCE_INP1                                 (0x0U << OPA_CR_VPSEL_Pos)
#define    FL_OPA_INP_SOURCE_INP2                                 (0x1U << OPA_CR_VPSEL_Pos)
#define    FL_OPA_INP_SOURCE_DAC                                  (0x2U << OPA_CR_VPSEL_Pos)


#define    FL_OPA_MODE_STANDALONE                                 (0x0U << OPA_CR_FBSEL_Pos)
#define    FL_OPA_MODE_PGA                                        (0x2U << OPA_CR_FBSEL_Pos)
#define    FL_OPA_MODE_BUFFER                                     (0x3U << OPA_CR_FBSEL_Pos)


#define    FL_OPA_TRIM_MODE_EXTERNAL                              (0x0U << OPA_CALR_TRIM_MODE_Pos)
#define    FL_OPA_TRIM_MODE_AUTO                                  (0x1U << OPA_CALR_TRIM_MODE_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup OPA_FL_Exported_Functions OPA Exported Functions
  * @{
  */

/**
  * @brief    Set PGA Mode
  * @rmtoll   CR    MSEL    FL_OPA_PGA_SetMode
  * @param    OPAx OPA instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_OPA_PGA_MODE_FB_TO_NEGATIVE
  *           @arg @ref FL_OPA_PGA_MODE_FB_TO_GND
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_PGA_SetMode(OPA_Type *OPAx, uint32_t mode)
{
    MODIFY_REG(OPAx->CR, OPA_CR_MSEL_Msk, mode);
}

/**
  * @brief    Get PGA Mode
  * @rmtoll   CR    MSEL    FL_OPA_PGA_GetMode
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_PGA_MODE_FB_TO_NEGATIVE
  *           @arg @ref FL_OPA_PGA_MODE_FB_TO_GND
  */
__STATIC_INLINE uint32_t FL_OPA_PGA_GetMode(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_MSEL_Msk));
}

/**
  * @brief    Set OPA Negative Input Channel
  * @rmtoll   CR    VNSEL    FL_OPA_SetINNSource
  * @param    OPAx OPA instance
  * @param    source This parameter can be one of the following values:
  *           @arg @ref FL_OPA_INN_SOURCE_INN1
  *           @arg @ref FL_OPA_INN_SOURCE_INN2
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
  *           @arg @ref FL_OPA_INP_SOURCE_DAC
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
  *           @arg @ref FL_OPA_INP_SOURCE_DAC
  */
__STATIC_INLINE uint32_t FL_OPA_GetINPSource(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_VPSEL_Msk));
}

/**
  * @brief    Enable OPA Negative Input Connected to GPIO
  * @rmtoll   CR    VN_EXC    FL_OPA_PGA_EnableINNConnectToPin
  * @param    OPAx OPA instance
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_PGA_EnableINNConnectToPin(OPA_Type *OPAx)
{
    SET_BIT(OPAx->CR, OPA_CR_VN_EXC_Msk);
}

/**
  * @brief    Get OPA Negative Input Connected to GPIO Enable Status
  * @rmtoll   CR    VN_EXC    FL_OPA_PGA_IsEnabledINNConnectToPin
  * @param    OPAx OPA instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_OPA_PGA_IsEnabledINNConnectToPin(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_VN_EXC_Msk) == OPA_CR_VN_EXC_Msk);
}

/**
  * @brief    Disable OPA Negative Input Connected to GPIO
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
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X2
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X4
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X8
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X16
  *           @arg @ref FL_OPA_GAIN_INVERT_X1
  *           @arg @ref FL_OPA_GAIN_INVERT_X3
  *           @arg @ref FL_OPA_GAIN_INVERT_X7
  *           @arg @ref FL_OPA_GAIN_INVERT_X15
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
  * @param    value This parameter can be one of the following values:
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X2
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X4
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X8
  *           @arg @ref FL_OPA_GAIN_NOINVERT_X16
  *           @arg @ref FL_OPA_GAIN_INVERT_X1
  *           @arg @ref FL_OPA_GAIN_INVERT_X3
  *           @arg @ref FL_OPA_GAIN_INVERT_X7
  *           @arg @ref FL_OPA_GAIN_INVERT_X15
  */
__STATIC_INLINE uint32_t FL_OPA_PGA_GetGain(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_PGA_GAIN_Msk));
}

/**
  * @brief    Set OPA Mode
  * @rmtoll   CR    FBSEL    FL_OPA_SetMode
  * @param    OPAx OPA instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_OPA_MODE_STANDALONE
  *           @arg @ref FL_OPA_MODE_PGA
  *           @arg @ref FL_OPA_MODE_BUFFER
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_SetMode(OPA_Type *OPAx, uint32_t mode)
{
    MODIFY_REG(OPAx->CR, OPA_CR_FBSEL_Msk, mode);
}

/**
  * @brief    Get OPA Mode Setting
  * @rmtoll   CR    FBSEL    FL_OPA_GetMode
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_MODE_STANDALONE
  *           @arg @ref FL_OPA_MODE_PGA
  *           @arg @ref FL_OPA_MODE_BUFFER
  */
__STATIC_INLINE uint32_t FL_OPA_GetMode(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CR, OPA_CR_FBSEL_Msk));
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
  * @brief    Set OPA Negative Trim Value
  * @rmtoll   CALR    NCAL    FL_OPA_WriteNegativeTrim
  * @param    OPAx OPA instance
  * @param    value
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_WriteNegativeTrim(OPA_Type *OPAx, uint32_t value)
{
    MODIFY_REG(OPAx->CALR, (0xffU << 16U), (value << 16U));
}

/**
  * @brief    Get OPA Negative Trim Value
  * @rmtoll   CALR    NCAL    FL_OPA_ReadNegativeTrim
  * @param    OPAx OPA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadNegativeTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, (0xffU << 16U)) >> 16U);
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
    MODIFY_REG(OPAx->CALR, (0xffU << 8U), (value << 8U));
}

/**
  * @brief    Get OPA Positive Trim Value
  * @rmtoll   CALR    PCAL    FL_OPA_ReadPositiveTrim
  * @param    OPAx OPA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadPositiveTrim(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, (0xffU << 8U)) >> 8U);
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
  * @brief    Set OPA Trim mode
  * @rmtoll   CALR    TRIM_MODE    FL_OPA_SetTrimMode
  * @param    OPAx OPA instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_OPA_TRIM_MODE_EXTERNAL
  *           @arg @ref FL_OPA_TRIM_MODE_AUTO
  * @retval   None
  */
__STATIC_INLINE void FL_OPA_SetTrimMode(OPA_Type *OPAx, uint32_t mode)
{
    MODIFY_REG(OPAx->CALR, OPA_CALR_TRIM_MODE_Msk, mode);
}

/**
  * @brief    Get OPA Trim mode
  * @rmtoll   CALR    TRIM_MODE    FL_OPA_GetTrimMode
  * @param    OPAx OPA instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_OPA_TRIM_MODE_EXTERNAL
  *           @arg @ref FL_OPA_TRIM_MODE_AUTO
  */
__STATIC_INLINE uint32_t FL_OPA_GetTrimMode(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->CALR, OPA_CALR_TRIM_MODE_Msk));
}

/**
  * @brief    Get OPA operational flag
  * @rmtoll   COR    OUT    FL_OPA_ReadTrimOutput
  * @param    OPAx OPA instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_OPA_ReadTrimOutput(OPA_Type *OPAx)
{
    return (uint32_t)(READ_BIT(OPAx->COR, (0x1U << 0U)) >> 0U);
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

#endif /* __FM33LG0XX_FL_OPA_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-12*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

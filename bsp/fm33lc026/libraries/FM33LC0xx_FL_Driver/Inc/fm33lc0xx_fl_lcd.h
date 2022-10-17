/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_lcd.h
  * @author  FMSH Application Team
  * @brief   Head file of LCD FL Module
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
#ifndef __FM33LC0XX_FL_LCD_H
#define __FM33LC0XX_FL_LCD_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup LCD LCD
  * @brief LCD FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup LCD_FL_ES_INIT LCD Exported Init structures
  * @{
  */

/**
  * @brief LCD Init Sturcture definition
  */
typedef struct
{
    /*! 电流源大小控制 */
    uint32_t biasCurrent;
    /*! 驱动模式 */
    uint32_t mode;
    /*! 偏执电平 */
    uint32_t biasVoltage;
    /*! 偏执类型 */
    uint32_t biasMode;
    /*! 驱动波形 */
    uint32_t waveform;
    /*! COM数目 */
    uint32_t COMxNum;
    /*! 显示频率 */
    uint32_t displayFreq;
    /*! 显示闪烁点亮时间(ms) */
    uint32_t flickOnTime;
    /*! 显示闪烁熄灭时间(ms) */
    uint32_t flickOffTime;
} FL_LCD_InitTypeDef;

/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup LCD_FL_Exported_Constants LCD Exported Constants
  * @{
  */

#define    LCD_CR_IC_CTRL_Pos                                     (16U)
#define    LCD_CR_IC_CTRL_Msk                                     (0x3U << LCD_CR_IC_CTRL_Pos)
#define    LCD_CR_IC_CTRL                                         LCD_CR_IC_CTRL_Msk

#define    LCD_CR_ENMODE_Pos                                      (15U)
#define    LCD_CR_ENMODE_Msk                                      (0x1U << LCD_CR_ENMODE_Pos)
#define    LCD_CR_ENMODE                                          LCD_CR_ENMODE_Msk

#define    LCD_CR_FLICK_Pos                                       (14U)
#define    LCD_CR_FLICK_Msk                                       (0x1U << LCD_CR_FLICK_Pos)
#define    LCD_CR_FLICK                                           LCD_CR_FLICK_Msk

#define    LCD_CR_BIAS_Pos                                        (8U)
#define    LCD_CR_BIAS_Msk                                        (0xfU << LCD_CR_BIAS_Pos)
#define    LCD_CR_BIAS                                            LCD_CR_BIAS_Msk

#define    LCD_CR_BIASMD_Pos                                      (5U)
#define    LCD_CR_BIASMD_Msk                                      (0x1U << LCD_CR_BIASMD_Pos)
#define    LCD_CR_BIASMD                                          LCD_CR_BIASMD_Msk

#define    LCD_CR_ANTIPOLAR_Pos                                   (4U)
#define    LCD_CR_ANTIPOLAR_Msk                                   (0x1U << LCD_CR_ANTIPOLAR_Pos)
#define    LCD_CR_ANTIPOLAR                                       LCD_CR_ANTIPOLAR_Msk

#define    LCD_CR_WFT_Pos                                         (3U)
#define    LCD_CR_WFT_Msk                                         (0x1U << LCD_CR_WFT_Pos)
#define    LCD_CR_WFT                                             LCD_CR_WFT_Msk

#define    LCD_CR_LMUX_Pos                                        (1U)
#define    LCD_CR_LMUX_Msk                                        (0x3U << LCD_CR_LMUX_Pos)
#define    LCD_CR_LMUX                                            LCD_CR_LMUX_Msk

#define    LCD_CR_EN_Pos                                          (0U)
#define    LCD_CR_EN_Msk                                          (0x1U << LCD_CR_EN_Pos)
#define    LCD_CR_EN                                              LCD_CR_EN_Msk

#define    LCD_FCR_DF_Pos                                         (0U)
#define    LCD_FCR_DF_Msk                                         (0xffU << LCD_FCR_DF_Pos)
#define    LCD_FCR_DF                                             LCD_FCR_DF_Msk

#define    LCD_FLKT_TOFF_Pos                                      (8U)
#define    LCD_FLKT_TOFF_Msk                                      (0xffU << LCD_FLKT_TOFF_Pos)
#define    LCD_FLKT_TOFF                                          LCD_FLKT_TOFF_Msk

#define    LCD_FLKT_TON_Pos                                       (0U)
#define    LCD_FLKT_TON_Msk                                       (0xffU << LCD_FLKT_TON_Pos)
#define    LCD_FLKT_TON                                           LCD_FLKT_TON_Msk

#define    LCD_IER_DONIE_Pos                                      (1U)
#define    LCD_IER_DONIE_Msk                                      (0x1U << LCD_IER_DONIE_Pos)
#define    LCD_IER_DONIE                                          LCD_IER_DONIE_Msk

#define    LCD_IER_DOFFIE_Pos                                     (0U)
#define    LCD_IER_DOFFIE_Msk                                     (0x1U << LCD_IER_DOFFIE_Pos)
#define    LCD_IER_DOFFIE                                         LCD_IER_DOFFIE_Msk

#define    LCD_ISR_DONIF_Pos                                      (1U)
#define    LCD_ISR_DONIF_Msk                                      (0x1U << LCD_ISR_DONIF_Pos)
#define    LCD_ISR_DONIF                                          LCD_ISR_DONIF_Msk

#define    LCD_ISR_DOFFIF_Pos                                     (0U)
#define    LCD_ISR_DOFFIF_Msk                                     (0x1U << LCD_ISR_DOFFIF_Pos)
#define    LCD_ISR_DOFFIF                                         LCD_ISR_DOFFIF_Msk

#define    LCD_DATA0_DSDA_Pos                                     (0U)
#define    LCD_DATA0_DSDA_Msk                                     (0xffffffffU << LCD_DATA0_DSDA_Pos)
#define    LCD_DATA0_DSDA                                         LCD_DATA0_DSDA_Msk



#define    FL_LCD_DATA_REG0                                       (0x0U << 0U)
#define    FL_LCD_DATA_REG1                                       (0x1U << 0U)
#define    FL_LCD_DATA_REG2                                       (0x2U << 0U)
#define    FL_LCD_DATA_REG3                                       (0x3U << 0U)
#define    FL_LCD_DATA_REG4                                       (0x4U << 0U)
#define    FL_LCD_DATA_REG5                                       (0x5U << 0U)
#define    FL_LCD_DATA_REG6                                       (0x6U << 0U)
#define    FL_LCD_DATA_REG7                                       (0x7U << 0U)
#define    FL_LCD_COMEN_COM0                                      (0x1U << 0U)
#define    FL_LCD_COMEN_COM1                                      (0x1U << 1U)
#define    FL_LCD_COMEN_COM2                                      (0x1U << 2U)
#define    FL_LCD_COMEN_COM3                                      (0x1U << 3U)
#define    FL_LCD_COMEN_COM4                                      (0x1U << 28U)
#define    FL_LCD_COMEN_COM5                                      (0x1U << 29U)
#define    FL_LCD_COMEN_COM6                                      (0x1U << 30U)
#define    FL_LCD_COMEN_COM7                                      (0x1U << 31U)
#define    FL_LCD_SEGEN0_SEG0                                     (0x1U << 0U)
#define    FL_LCD_SEGEN0_SEG1                                     (0x1U << 1U)
#define    FL_LCD_SEGEN0_SEG2                                     (0x1U << 2U)
#define    FL_LCD_SEGEN0_SEG3                                     (0x1U << 3U)
#define    FL_LCD_SEGEN0_SEG4                                     (0x1U << 4U)
#define    FL_LCD_SEGEN0_SEG5                                     (0x1U << 5U)
#define    FL_LCD_SEGEN0_SEG6                                     (0x1U << 6U)
#define    FL_LCD_SEGEN0_SEG7                                     (0x1U << 7U)
#define    FL_LCD_SEGEN0_SEG8                                     (0x1U << 8U)
#define    FL_LCD_SEGEN0_SEG9                                     (0x1U << 9U)
#define    FL_LCD_SEGEN0_SEG10                                    (0x1U << 10U)
#define    FL_LCD_SEGEN0_SEG11                                    (0x1U << 11U)
#define    FL_LCD_SEGEN0_SEG12                                    (0x1U << 12U)
#define    FL_LCD_SEGEN0_SEG13                                    (0x1U << 13U)
#define    FL_LCD_SEGEN0_SEG14                                    (0x1U << 14U)
#define    FL_LCD_SEGEN0_SEG15                                    (0x1U << 15U)
#define    FL_LCD_SEGEN0_SEG16                                    (0x1U << 16U)
#define    FL_LCD_SEGEN0_SEG17                                    (0x1U << 17U)
#define    FL_LCD_SEGEN0_SEG18                                    (0x1U << 18U)
#define    FL_LCD_SEGEN0_SEG19                                    (0x1U << 19U)
#define    FL_LCD_SEGEN0_SEG20                                    (0x1U << 20U)
#define    FL_LCD_SEGEN0_SEG21                                    (0x1U << 21U)
#define    FL_LCD_SEGEN0_SEG22                                    (0x1U << 22U)
#define    FL_LCD_SEGEN0_SEG23                                    (0x1U << 23U)
#define    FL_LCD_SEGEN0_SEG24                                    (0x1U << 24U)
#define    FL_LCD_SEGEN0_SEG25                                    (0x1U << 25U)
#define    FL_LCD_SEGEN0_SEG26                                    (0x1U << 26U)
#define    FL_LCD_SEGEN0_SEG27                                    (0x1U << 27U)
#define    FL_LCD_SEGEN0_SEG28                                    (0x1U << 28U)
#define    FL_LCD_SEGEN0_SEG29                                    (0x1U << 29U)
#define    FL_LCD_SEGEN0_SEG30                                    (0x1U << 30U)
#define    FL_LCD_SEGEN0_SEG31                                    (0x1U << 31U)



#define    FL_LCD_BIAS_CURRENT_VERYHIGH                           (0x0U << LCD_CR_IC_CTRL_Pos)
#define    FL_LCD_BIAS_CURRENT_HIGH                               (0x1U << LCD_CR_IC_CTRL_Pos)
#define    FL_LCD_BIAS_CURRENT_MEDIUM                             (0x2U << LCD_CR_IC_CTRL_Pos)
#define    FL_LCD_BIAS_CURRENT_LOW                                (0x3U << LCD_CR_IC_CTRL_Pos)


#define    FL_LCD_DRIVER_MODE_INNER_RESISTER                      (0x1U << LCD_CR_ENMODE_Pos)


#define    FL_LCD_BIAS_VOLTAGE_LEVEL0                             (0x0U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL1                             (0x1U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL2                             (0x2U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL3                             (0x3U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL4                             (0x4U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL5                             (0x5U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL6                             (0x6U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL7                             (0x7U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL8                             (0x8U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL9                             (0x9U << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL10                            (0xaU << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL11                            (0xbU << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL12                            (0xcU << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL13                            (0xdU << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL14                            (0xeU << LCD_CR_BIAS_Pos)
#define    FL_LCD_BIAS_VOLTAGE_LEVEL15                            (0xfU << LCD_CR_BIAS_Pos)


#define    FL_LCD_BIAS_MODE_4BIAS                                 (0x0U << LCD_CR_BIASMD_Pos)
#define    FL_LCD_BIAS_MODE_3BIAS                                 (0x1U << LCD_CR_BIASMD_Pos)


#define    FL_LCD_ANTIPOLAR_FLOATING                              (0x0U << LCD_CR_ANTIPOLAR_Pos)
#define    FL_LCD_ANTIPOLAR_GND                                   (0x1U << LCD_CR_ANTIPOLAR_Pos)

#define    FL_LCD_WAVEFORM_TYPEA                                  (0x0U << LCD_CR_WFT_Pos)
#define    FL_LCD_WAVEFORM_TYPEB                                  (0x1U << LCD_CR_WFT_Pos)


#define    FL_LCD_COM_NUM_4COM                                    (0x0U << LCD_CR_LMUX_Pos)
#define    FL_LCD_COM_NUM_6COM                                    (0x1U << LCD_CR_LMUX_Pos)
#define    FL_LCD_COM_NUM_8COM                                    (0x2U << LCD_CR_LMUX_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup LCD_FL_Exported_Functions LCD Exported Functions
  * @{
  */

/**
  * @brief    Set Input Bias Current
  * @rmtoll   CR    IC_CTRL    FL_LCD_SetBiasCurrent
  * @param    LCDx LCD instance
  * @param    current This parameter can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_CURRENT_VERYHIGH
  *           @arg @ref FL_LCD_BIAS_CURRENT_HIGH
  *           @arg @ref FL_LCD_BIAS_CURRENT_MEDIUM
  *           @arg @ref FL_LCD_BIAS_CURRENT_LOW
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetBiasCurrent(LCD_Type *LCDx, uint32_t current)
{
    MODIFY_REG(LCDx->CR, LCD_CR_IC_CTRL_Msk, current);
}

/**
  * @brief    Set Input Bias Current
  * @rmtoll   CR    IC_CTRL    FL_LCD_GetBiasCurrent
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_CURRENT_VERYHIGH
  *           @arg @ref FL_LCD_BIAS_CURRENT_HIGH
  *           @arg @ref FL_LCD_BIAS_CURRENT_MEDIUM
  *           @arg @ref FL_LCD_BIAS_CURRENT_LOW
  */
__STATIC_INLINE uint32_t FL_LCD_GetBiasCurrent(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_IC_CTRL_Msk));
}

/**
  * @brief    Set LCD Enabling Mode
  * @rmtoll   CR    ENMODE    FL_LCD_SetDriverMode
  * @param    LCDx LCD instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LCD_DRIVER_MODE_INNER_RESISTER
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetDriverMode(LCD_Type *LCDx, uint32_t mode)
{
    MODIFY_REG(LCDx->CR, LCD_CR_ENMODE_Msk, mode);
}

/**
  * @brief    Get LCD Enabling Mode
  * @rmtoll   CR    ENMODE    FL_LCD_GetDriverMode
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_DRIVER_MODE_INNER_RESISTER
  */
__STATIC_INLINE uint32_t FL_LCD_GetDriverMode(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_ENMODE_Msk));
}

/**
  * @brief    Enable LCD Blink
  * @rmtoll   CR    FLICK    FL_LCD_EnableDisplayBlink
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_EnableDisplayBlink(LCD_Type *LCDx)
{
    SET_BIT(LCDx->CR, LCD_CR_FLICK_Msk);
}

/**
  * @brief    Disable LCD Blink
  * @rmtoll   CR    FLICK    FL_LCD_DisableDisplayBlink
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_DisableDisplayBlink(LCD_Type *LCDx)
{
    CLEAR_BIT(LCDx->CR, LCD_CR_FLICK_Msk);
}

/**
  * @brief    Get LCD Blink State
  * @rmtoll   CR    FLICK    FL_LCD_IsEnabledDisplayBlink
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabledDisplayBlink(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_FLICK_Msk) == LCD_CR_FLICK_Msk);
}

/**
  * @brief    Set LCD Bias Voltage Select
  * @rmtoll   CR    BIAS    FL_LCD_SetBiasVoltage
  * @param    LCDx LCD instance
  * @param    voltage This parameter can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL0
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL1
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL2
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL3
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL4
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL5
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL6
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL7
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL8
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL9
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL10
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL11
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL12
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL13
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL14
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL15
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetBiasVoltage(LCD_Type *LCDx, uint32_t voltage)
{
    MODIFY_REG(LCDx->CR, LCD_CR_BIAS_Msk, voltage);
}

/**
  * @brief    Get LCD Bias Voltage Select
  * @rmtoll   CR    BIAS    FL_LCD_GetBiasVoltage
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL0
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL1
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL2
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL3
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL4
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL5
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL6
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL7
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL8
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL9
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL10
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL11
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL12
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL13
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL14
  *           @arg @ref FL_LCD_BIAS_VOLTAGE_LEVEL15
  */
__STATIC_INLINE uint32_t FL_LCD_GetBiasVoltage(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_BIAS_Msk));
}

/**
  * @brief    Set LCD Bias Mode
  * @rmtoll   CR    BIASMD    FL_LCD_SetBiasMode
  * @param    LCDx LCD instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_MODE_4BIAS
  *           @arg @ref FL_LCD_BIAS_MODE_3BIAS
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetBiasMode(LCD_Type *LCDx, uint32_t mode)
{
    MODIFY_REG(LCDx->CR, LCD_CR_BIASMD_Msk, mode);
}

/**
  * @brief    Get LCD Bias Mode
  * @rmtoll   CR    BIASMD    FL_LCD_GetBiasMode
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_BIAS_MODE_4BIAS
  *           @arg @ref FL_LCD_BIAS_MODE_3BIAS
  */
__STATIC_INLINE uint32_t FL_LCD_GetBiasMode(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_BIASMD_Msk));
}

/**
  * @brief    Set LCD Anti-Polarization
  * @rmtoll   CR    ANTIPOLAR    FL_LCD_SetAntiPolar
  * @param    LCDx LCD instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_LCD_ANTIPOLAR_FLOATING
  *           @arg @ref FL_LCD_ANTIPOLAR_GND
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetAntiPolar(LCD_Type *LCDx, uint32_t state)
{
    MODIFY_REG(LCDx->CR, LCD_CR_ANTIPOLAR_Msk, state);
}

/**
  * @brief    Get LCD Anti-Polarization
  * @rmtoll   CR    ANTIPOLAR    FL_LCD_GetAntiPolar
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_LCD_GetAntiPolar(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_ANTIPOLAR_Msk));
}

/**
  * @brief    Set LCD Waveform Format
  * @rmtoll   CR    WFT    FL_LCD_SetWaveform
  * @param    LCDx LCD instance
  * @param    state This parameter can be one of the following values:
  *           @arg @ref FL_LCD_WAVEFORM_TYPEA
  *           @arg @ref FL_LCD_WAVEFORM_TYPEB
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetWaveform(LCD_Type *LCDx, uint32_t state)
{
    MODIFY_REG(LCDx->CR, LCD_CR_WFT_Msk, state);
}

/**
  * @brief    Get LCD Waveform Format
  * @rmtoll   CR    WFT    FL_LCD_GetWaveform
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_WAVEFORM_TYPEA
  *           @arg @ref FL_LCD_WAVEFORM_TYPEB
  */
__STATIC_INLINE uint32_t FL_LCD_GetWaveform(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_WFT_Msk));
}

/**
  * @brief    Set LCD Segment Line Mux
  * @rmtoll   CR    LMUX    FL_LCD_SetCOMNumber
  * @param    LCDx LCD instance
  * @param    number This parameter can be one of the following values:
  *           @arg @ref FL_LCD_COM_NUM_4COM
  *           @arg @ref FL_LCD_COM_NUM_6COM
  *           @arg @ref FL_LCD_COM_NUM_8COM
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_SetCOMNumber(LCD_Type *LCDx, uint32_t number)
{
    MODIFY_REG(LCDx->CR, LCD_CR_LMUX_Msk, number);
}

/**
  * @brief    Get LCD Segment Line Mux
  * @rmtoll   CR    LMUX    FL_LCD_GetCOMNumber
  * @param    LCDx LCD instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_LCD_COM_NUM_4COM
  *           @arg @ref FL_LCD_COM_NUM_6COM
  *           @arg @ref FL_LCD_COM_NUM_8COM
  */
__STATIC_INLINE uint32_t FL_LCD_GetCOMNumber(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_LMUX_Msk));
}

/**
  * @brief    Enable LCD
  * @rmtoll   CR    EN    FL_LCD_Enable
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_Enable(LCD_Type *LCDx)
{
    SET_BIT(LCDx->CR, LCD_CR_EN_Msk);
}

/**
  * @brief    Get LCD State
  * @rmtoll   CR    EN    FL_LCD_IsEnabled
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabled(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->CR, LCD_CR_EN_Msk) == LCD_CR_EN_Msk);
}

/**
  * @brief    Disable LCD
  * @rmtoll   CR    EN    FL_LCD_Disable
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_Disable(LCD_Type *LCDx)
{
    CLEAR_BIT(LCDx->CR, LCD_CR_EN_Msk);
}

/**
  * @brief    Set LCD Display Frequency
  * @rmtoll   FCR    DF    FL_LCD_WriteDisplayFrequency
  * @param    LCDx LCD instance
  * @param    frequency
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_WriteDisplayFrequency(LCD_Type *LCDx, uint32_t frequency)
{
    MODIFY_REG(LCDx->FCR, (0xffU << 0U), (frequency << 0U));
}

/**
  * @brief    Get LCD Display Frequency
  * @rmtoll   FCR    DF    FL_LCD_ReadDisplayFrequency
  * @param    LCDx LCD instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LCD_ReadDisplayFrequency(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->FCR, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Set LCD Display Off Time
  * @rmtoll   FLKT    TOFF    FL_LCD_WriteDisplayOffTime
  * @param    LCDx LCD instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_WriteDisplayOffTime(LCD_Type *LCDx, uint32_t time)
{
    MODIFY_REG(LCDx->FLKT, (0xffU << 8U), (time << 8U));
}

/**
  * @brief    Get LCD Display Off Time
  * @rmtoll   FLKT    TOFF    FL_LCD_ReadDisplayOffTime
  * @param    LCDx LCD instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LCD_ReadDisplayOffTime(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->FLKT, (0xffU << 8U)) >> 8U);
}

/**
  * @brief    Set LCD Display On Time
  * @rmtoll   FLKT    TON    FL_LCD_WriteDisplayOnTime
  * @param    LCDx LCD instance
  * @param    time
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_WriteDisplayOnTime(LCD_Type *LCDx, uint32_t time)
{
    MODIFY_REG(LCDx->FLKT, (0xffU << 0U), (time << 0U));
}

/**
  * @brief    Get LCD Display On Time
  * @rmtoll   FLKT    TON    FL_LCD_ReadDisplayOnTime
  * @param    LCDx LCD instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_LCD_ReadDisplayOnTime(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->FLKT, (0xffU << 0U)) >> 0U);
}

/**
  * @brief    Enable LCD Display OFF IRQ
  * @rmtoll   IER    DONIE    FL_LCD_EnableIT_DisplayOff
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_EnableIT_DisplayOff(LCD_Type *LCDx)
{
    SET_BIT(LCDx->IER, LCD_IER_DONIE_Msk);
}

/**
  * @brief    Disable LCD Display OFF IRQ
  * @rmtoll   IER    DONIE    FL_LCD_DisableIT_DisplayOff
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_DisableIT_DisplayOff(LCD_Type *LCDx)
{
    CLEAR_BIT(LCDx->IER, LCD_IER_DONIE_Msk);
}

/**
  * @brief    Getable LCD Display OFF IRQ
  * @rmtoll   IER    DONIE    FL_LCD_IsEnabledIT_DisplayOff
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabledIT_DisplayOff(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->IER, LCD_IER_DONIE_Msk) == LCD_IER_DONIE_Msk);
}

/**
  * @brief    Enable LCD Display ON Interrupt
  * @rmtoll   IER    DOFFIE    FL_LCD_EnableIT_DisplayOn
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_EnableIT_DisplayOn(LCD_Type *LCDx)
{
    SET_BIT(LCDx->IER, LCD_IER_DOFFIE_Msk);
}

/**
  * @brief    Disable LCD Display ON Interrupt
  * @rmtoll   IER    DOFFIE    FL_LCD_DisableIT_DisplayOn
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_DisableIT_DisplayOn(LCD_Type *LCDx)
{
    CLEAR_BIT(LCDx->IER, LCD_IER_DOFFIE_Msk);
}

/**
  * @brief    Getable LCD Display ON Interrupt
  * @rmtoll   IER    DOFFIE    FL_LCD_IsEnabledIT_DisplayOn
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabledIT_DisplayOn(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->IER, LCD_IER_DOFFIE_Msk) == LCD_IER_DOFFIE_Msk);
}

/**
  * @brief    Get LCD Display OFF Flag
  * @rmtoll   ISR    DONIF    FL_LCD_IsActiveFlag_DisplayOff
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsActiveFlag_DisplayOff(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->ISR, LCD_ISR_DONIF_Msk) == (LCD_ISR_DONIF_Msk));
}

/**
  * @brief    Clear LCD Display OFF Flag
  * @rmtoll   ISR    DONIF    FL_LCD_ClearFlag_DisplayOff
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_ClearFlag_DisplayOff(LCD_Type *LCDx)
{
    WRITE_REG(LCDx->ISR, LCD_ISR_DONIF_Msk);
}

/**
  * @brief    Get LCD Display On Flag
  * @rmtoll   ISR    DOFFIF    FL_LCD_IsActiveFlag_DisplayOn
  * @param    LCDx LCD instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsActiveFlag_DisplayOn(LCD_Type *LCDx)
{
    return (uint32_t)(READ_BIT(LCDx->ISR, LCD_ISR_DOFFIF_Msk) == (LCD_ISR_DOFFIF_Msk));
}

/**
  * @brief    Clear LCD Display On Flag
  * @rmtoll   ISR    DOFFIF    FL_LCD_ClearFlag_DisplayOn
  * @param    LCDx LCD instance
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_ClearFlag_DisplayOn(LCD_Type *LCDx)
{
    WRITE_REG(LCDx->ISR, LCD_ISR_DOFFIF_Msk);
}

/**
  * @brief    Write LCD Display Data
  * @rmtoll   DATA0    DSDA    FL_LCD_WriteData
  * @param    LCDx LCD instance
  * @param    reg This parameter can be one of the following values:
  *           @arg @ref FL_LCD_DATA_REG0
  *           @arg @ref FL_LCD_DATA_REG1
  *           @arg @ref FL_LCD_DATA_REG2
  *           @arg @ref FL_LCD_DATA_REG3
  *           @arg @ref FL_LCD_DATA_REG4
  *           @arg @ref FL_LCD_DATA_REG5
  *           @arg @ref FL_LCD_DATA_REG6
  *           @arg @ref FL_LCD_DATA_REG7
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_WriteData(LCD_Type *LCDx, uint32_t reg, uint32_t data)
{
    volatile uint32_t *pData = &(LCDx->DATA0);
    MODIFY_REG(pData[reg], LCD_DATA0_DSDA_Msk, data);
}

/**
  * @brief    Read LCD Display Data
  * @rmtoll   DATA0    DSDA    FL_LCD_ReadData
  * @param    LCDx LCD instance
  * @param    reg This parameter can be one of the following values:
  *           @arg @ref FL_LCD_DATA_REG0
  *           @arg @ref FL_LCD_DATA_REG1
  *           @arg @ref FL_LCD_DATA_REG2
  *           @arg @ref FL_LCD_DATA_REG3
  *           @arg @ref FL_LCD_DATA_REG4
  *           @arg @ref FL_LCD_DATA_REG5
  *           @arg @ref FL_LCD_DATA_REG6
  *           @arg @ref FL_LCD_DATA_REG7
  * @retval
  */
__STATIC_INLINE uint32_t FL_LCD_ReadData(LCD_Type *LCDx, uint32_t reg)
{
    volatile uint32_t *pData = &(LCDx->DATA0);
    return (uint32_t)(READ_BIT(pData[reg], LCD_DATA0_DSDA_Msk));
}

/**
  * @brief    Get LCD COMx State
  * @rmtoll   COMEN        FL_LCD_IsEnabledCOMEN
  * @param    LCDx LCD instance
  * @param    COM This parameter can be one of the following values:
  *           @arg @ref FL_LCD_COMEN_COM0
  *           @arg @ref FL_LCD_COMEN_COM1
  *           @arg @ref FL_LCD_COMEN_COM2
  *           @arg @ref FL_LCD_COMEN_COM3
  *           @arg @ref FL_LCD_COMEN_COM4
  *           @arg @ref FL_LCD_COMEN_COM5
  *           @arg @ref FL_LCD_COMEN_COM6
  *           @arg @ref FL_LCD_COMEN_COM7
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabledCOMEN(LCD_Type *LCDx, uint32_t COM)
{
    if(COM < FL_LCD_COMEN_COM4)
    {
        return (uint32_t)(READ_BIT(LCDx->COMEN, ((COM & 0xffffffff) << 0x0U)) == ((COM & 0xffffffff) << 0x0U));
    }
    else
    {
        return (uint32_t)(READ_BIT(LCDx->SEGEN0, ((COM & 0xffffffff) << 0x0U)) == ((COM & 0xffffffff) << 0x0U));
    }
}

/**
  * @brief    Enable LCD COMx
  * @rmtoll   COMEN        FL_LCD_EnableCOMEN
  * @param    LCDx LCD instance
  * @param    COM This parameter can be one of the following values:
  *           @arg @ref FL_LCD_COMEN_COM0
  *           @arg @ref FL_LCD_COMEN_COM1
  *           @arg @ref FL_LCD_COMEN_COM2
  *           @arg @ref FL_LCD_COMEN_COM3
  *           @arg @ref FL_LCD_COMEN_COM4
  *           @arg @ref FL_LCD_COMEN_COM5
  *           @arg @ref FL_LCD_COMEN_COM6
  *           @arg @ref FL_LCD_COMEN_COM7
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_EnableCOMEN(LCD_Type *LCDx, uint32_t COM)
{
    if(COM < FL_LCD_COMEN_COM4)
    {
        SET_BIT(LCDx->COMEN, ((COM & 0xffffffff) << 0x0U));
    }
    else
    {
        SET_BIT(LCDx->SEGEN0, ((COM & 0xffffffff) << 0x0U));
    }
}

/**
  * @brief    Disable LCD COMx
  * @rmtoll   COMEN        FL_LCD_DisableCOMEN
  * @param    LCDx LCD instance
  * @param    COM This parameter can be one of the following values:
  *           @arg @ref FL_LCD_COMEN_COM0
  *           @arg @ref FL_LCD_COMEN_COM1
  *           @arg @ref FL_LCD_COMEN_COM2
  *           @arg @ref FL_LCD_COMEN_COM3
  *           @arg @ref FL_LCD_COMEN_COM4
  *           @arg @ref FL_LCD_COMEN_COM5
  *           @arg @ref FL_LCD_COMEN_COM6
  *           @arg @ref FL_LCD_COMEN_COM7
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_DisableCOMEN(LCD_Type *LCDx, uint32_t COM)
{
    if(COM < FL_LCD_COMEN_COM4)
    {
        CLEAR_BIT(LCDx->COMEN, ((COM & 0xffffffff) << 0x0U));
    }
    else
    {
        CLEAR_BIT(LCDx->SEGEN0, ((COM & 0xffffffff) << 0x0U));
    }
}

/**
  * @brief    Get LCD SEGx State
  * @rmtoll   SEGEN0        FL_LCD_IsEnabledSEGEN0
  * @param    LCDx LCD instance
  * @param    SEG This parameter can be one of the following values:
  *           @arg @ref FL_LCD_SEGEN0_SEG0
  *           @arg @ref FL_LCD_SEGEN0_SEG1
  *           @arg @ref FL_LCD_SEGEN0_SEG2
  *           @arg @ref FL_LCD_SEGEN0_SEG3
  *           @arg @ref FL_LCD_SEGEN0_SEG4
  *           @arg @ref FL_LCD_SEGEN0_SEG5
  *           @arg @ref FL_LCD_SEGEN0_SEG6
  *           @arg @ref FL_LCD_SEGEN0_SEG7
  *           @arg @ref FL_LCD_SEGEN0_SEG8
  *           @arg @ref FL_LCD_SEGEN0_SEG9
  *           @arg @ref FL_LCD_SEGEN0_SEG10
  *           @arg @ref FL_LCD_SEGEN0_SEG11
  *           @arg @ref FL_LCD_SEGEN0_SEG12
  *           @arg @ref FL_LCD_SEGEN0_SEG13
  *           @arg @ref FL_LCD_SEGEN0_SEG14
  *           @arg @ref FL_LCD_SEGEN0_SEG15
  *           @arg @ref FL_LCD_SEGEN0_SEG16
  *           @arg @ref FL_LCD_SEGEN0_SEG17
  *           @arg @ref FL_LCD_SEGEN0_SEG18
  *           @arg @ref FL_LCD_SEGEN0_SEG19
  *           @arg @ref FL_LCD_SEGEN0_SEG20
  *           @arg @ref FL_LCD_SEGEN0_SEG21
  *           @arg @ref FL_LCD_SEGEN0_SEG22
  *           @arg @ref FL_LCD_SEGEN0_SEG23
  *           @arg @ref FL_LCD_SEGEN0_SEG24
  *           @arg @ref FL_LCD_SEGEN0_SEG25
  *           @arg @ref FL_LCD_SEGEN0_SEG26
  *           @arg @ref FL_LCD_SEGEN0_SEG27
  *           @arg @ref FL_LCD_SEGEN0_SEG28
  *           @arg @ref FL_LCD_SEGEN0_SEG29
  *           @arg @ref FL_LCD_SEGEN0_SEG30
  *           @arg @ref FL_LCD_SEGEN0_SEG31
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_LCD_IsEnabledSEGEN0(LCD_Type *LCDx, uint32_t SEG)
{
    return (uint32_t)(READ_BIT(LCDx->SEGEN0, ((SEG & 0xffffffff) << 0x0U)) == ((SEG & 0xffffffff) << 0x0U));
}

/**
  * @brief    Enable LCD SEGx
  * @rmtoll   SEGEN0        FL_LCD_EnableSEGEN0
  * @param    LCDx LCD instance
  * @param    SEG This parameter can be one of the following values:
  *           @arg @ref FL_LCD_SEGEN0_SEG0
  *           @arg @ref FL_LCD_SEGEN0_SEG1
  *           @arg @ref FL_LCD_SEGEN0_SEG2
  *           @arg @ref FL_LCD_SEGEN0_SEG3
  *           @arg @ref FL_LCD_SEGEN0_SEG4
  *           @arg @ref FL_LCD_SEGEN0_SEG5
  *           @arg @ref FL_LCD_SEGEN0_SEG6
  *           @arg @ref FL_LCD_SEGEN0_SEG7
  *           @arg @ref FL_LCD_SEGEN0_SEG8
  *           @arg @ref FL_LCD_SEGEN0_SEG9
  *           @arg @ref FL_LCD_SEGEN0_SEG10
  *           @arg @ref FL_LCD_SEGEN0_SEG11
  *           @arg @ref FL_LCD_SEGEN0_SEG12
  *           @arg @ref FL_LCD_SEGEN0_SEG13
  *           @arg @ref FL_LCD_SEGEN0_SEG14
  *           @arg @ref FL_LCD_SEGEN0_SEG15
  *           @arg @ref FL_LCD_SEGEN0_SEG16
  *           @arg @ref FL_LCD_SEGEN0_SEG17
  *           @arg @ref FL_LCD_SEGEN0_SEG18
  *           @arg @ref FL_LCD_SEGEN0_SEG19
  *           @arg @ref FL_LCD_SEGEN0_SEG20
  *           @arg @ref FL_LCD_SEGEN0_SEG21
  *           @arg @ref FL_LCD_SEGEN0_SEG22
  *           @arg @ref FL_LCD_SEGEN0_SEG23
  *           @arg @ref FL_LCD_SEGEN0_SEG24
  *           @arg @ref FL_LCD_SEGEN0_SEG25
  *           @arg @ref FL_LCD_SEGEN0_SEG26
  *           @arg @ref FL_LCD_SEGEN0_SEG27
  *           @arg @ref FL_LCD_SEGEN0_SEG28
  *           @arg @ref FL_LCD_SEGEN0_SEG29
  *           @arg @ref FL_LCD_SEGEN0_SEG30
  *           @arg @ref FL_LCD_SEGEN0_SEG31
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_EnableSEGEN0(LCD_Type *LCDx, uint32_t SEG)
{
    SET_BIT(LCDx->SEGEN0, ((SEG & 0xffffffff) << 0x0U));
}

/**
  * @brief    Disable LCD SEGx
  * @rmtoll   SEGEN0        FL_LCD_DisableSEGEN0
  * @param    LCDx LCD instance
  * @param    SEG This parameter can be one of the following values:
  *           @arg @ref FL_LCD_SEGEN0_SEG0
  *           @arg @ref FL_LCD_SEGEN0_SEG1
  *           @arg @ref FL_LCD_SEGEN0_SEG2
  *           @arg @ref FL_LCD_SEGEN0_SEG3
  *           @arg @ref FL_LCD_SEGEN0_SEG4
  *           @arg @ref FL_LCD_SEGEN0_SEG5
  *           @arg @ref FL_LCD_SEGEN0_SEG6
  *           @arg @ref FL_LCD_SEGEN0_SEG7
  *           @arg @ref FL_LCD_SEGEN0_SEG8
  *           @arg @ref FL_LCD_SEGEN0_SEG9
  *           @arg @ref FL_LCD_SEGEN0_SEG10
  *           @arg @ref FL_LCD_SEGEN0_SEG11
  *           @arg @ref FL_LCD_SEGEN0_SEG12
  *           @arg @ref FL_LCD_SEGEN0_SEG13
  *           @arg @ref FL_LCD_SEGEN0_SEG14
  *           @arg @ref FL_LCD_SEGEN0_SEG15
  *           @arg @ref FL_LCD_SEGEN0_SEG16
  *           @arg @ref FL_LCD_SEGEN0_SEG17
  *           @arg @ref FL_LCD_SEGEN0_SEG18
  *           @arg @ref FL_LCD_SEGEN0_SEG19
  *           @arg @ref FL_LCD_SEGEN0_SEG20
  *           @arg @ref FL_LCD_SEGEN0_SEG21
  *           @arg @ref FL_LCD_SEGEN0_SEG22
  *           @arg @ref FL_LCD_SEGEN0_SEG23
  *           @arg @ref FL_LCD_SEGEN0_SEG24
  *           @arg @ref FL_LCD_SEGEN0_SEG25
  *           @arg @ref FL_LCD_SEGEN0_SEG26
  *           @arg @ref FL_LCD_SEGEN0_SEG27
  *           @arg @ref FL_LCD_SEGEN0_SEG28
  *           @arg @ref FL_LCD_SEGEN0_SEG29
  *           @arg @ref FL_LCD_SEGEN0_SEG30
  *           @arg @ref FL_LCD_SEGEN0_SEG31
  * @retval   None
  */
__STATIC_INLINE void FL_LCD_DisableSEGEN0(LCD_Type *LCDx, uint32_t SEG)
{
    CLEAR_BIT(LCDx->SEGEN0, ((SEG & 0xffffffff) << 0x0U));
}

/**
  * @}
  */

/** @defgroup LCD_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_LCD_DeInit(LCD_Type *LCDx);
void FL_LCD_StructInit(FL_LCD_InitTypeDef *initStruct);
FL_ErrorStatus FL_LCD_Init(LCD_Type *LCDx, FL_LCD_InitTypeDef *initStruct);

/**
  * @}
  */

/** @defgroup LCD_FL_EF_Operation Opeartion functions
  * @{
  */

void FL_LCD_4COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state);
void FL_LCD_6COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state);
void FL_LCD_8COMDisplay(uint32_t *display, uint8_t com, uint8_t seg, uint8_t state);

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

#endif /* __FM33LC0XX_FL_LCD_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2021-02-02*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/

/**
 *******************************************************************************
 * @file  hc32_ll_cmp.h
 * @brief Head file for CMP module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_CMP_H__
#define __HC32_LL_CMP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_CMP
 * @{
 */

#if (LL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CMP_Global_Types CMP Global Types
 * @{
 */

/**
 * @brief CMP normal mode configuration structure
 */
typedef struct {
    uint16_t u16PositiveInput;      /*!< Positive(compare voltage) input @ref CMP_Positive_Input_Select */
    uint16_t u16NegativeInput;      /*!< Negative(Reference voltage) input @ref CMP_Negative_Input_Select */
    uint16_t u16OutPolarity;        /*!< Output polarity select, @ref CMP_Out_Polarity_Select */
    uint16_t u16OutDetectEdge;      /*!< Output detect edge, @ref CMP_Out_Detect_Edge_Select */
    uint16_t u16OutFilter;          /*!< Output Filter, @ref CMP_Out_Filter */
} stc_cmp_init_t;

/**
 * @brief CMP window mode configuration structure
 */
typedef struct {
    uint8_t u8WinVolLow;            /*!< CMP reference low voltage for window mode @ref CMP_Window_Low_Select */
    uint8_t u8WinVolHigh;           /*!< CMP reference high voltage for window mode @ref CMP_Window_High_Select */
    uint16_t u16OutPolarity;        /*!< Output polarity select, @ref CMP_Out_Polarity_Select */
    uint16_t u16OutDetectEdge;      /*!< Output detect edge, @ref CMP_Out_Detect_Edge_Select */
    uint16_t u16OutFilter;          /*!< Output Filter, @ref CMP_Out_Filter */
} stc_cmp_window_init_t;

/**
 * @brief CMP blank window function configuration structure
 */
typedef struct {
    uint16_t u16Src;                /*!< blank window source select,
                                         can be any combination of @ref CMP_BlankWindow_Src */
    uint8_t u8ValidLevel;           /*!< Blank window valid level @ref CMP_BlankWindow_Valid_Level */
    uint8_t u8OutLevel;             /*!< CMP output level when blank window valid @ref CMP_BlankWindow_output_Level */
} stc_cmp_blankwindow_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Macros CMP Global Macros
 * @{
 */

#define VISR_OFFSET                 (8U)

/**
 * @defgroup CMP_Window_Mode_Unit CMP Window Mode Unit
 * @{
 */
#define CMP_WIN_CMP12               (0x01U)
#define CMP_WIN_CMP34               (0x02U)

/**
 * @}
 */

/**
 * @defgroup CMP_Positive_Input_Select CMP Positive(Compare) Voltage Input
 * @{
 */
#define CMP_POSITIVE_NONE           (0x0U)

/* Select positive input for CMP1 */
#define CMP1_POSITIVE_PGA1_BP       (CMP_PMSR_CVSL_0)                                       /*!< Select PGA1_BP */
#define CMP1_POSITIVE_PGA1          ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_0 << VISR_OFFSET))  /*!< Select PGA1 */
#define CMP1_POSITIVE_PGA2          ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_1 << VISR_OFFSET))  /*!< Select PGA2 */
#define CMP1_POSITIVE_CMP1_INP2     ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_2 << VISR_OFFSET))  /*!< Select CMP1_INP2 */
#define CMP1_POSITIVE_CMP1_INP3     ((CMP_PMSR_CVSL_2) | (CMP_VISR_P3SL_0 << VISR_OFFSET))  /*!< Select CMP1_INP3 */
#define CMP1_POSITIVE_CMP2_INP3     ((CMP_PMSR_CVSL_2) | (CMP_VISR_P3SL_1 << VISR_OFFSET))  /*!< Select CMP2_INP3 */
#define CMP1_POSITIVE_CMP1_INP4     (CMP_PMSR_CVSL_3)                                       /*!< Select CMP1_INP4 */
/* Select positive input for CMP2 */
#define CMP2_POSITIVE_PGA2_BP       (CMP_PMSR_CVSL_0)   /*!< Select PGA2_BP */
#define CMP2_POSITIVE_PGA2          (CMP_PMSR_CVSL_1)   /*!< Select PGA2 */
#define CMP2_POSITIVE_CMP2_INP3     (CMP_PMSR_CVSL_2)   /*!< Select CMP2_INP3 */
#define CMP2_POSITIVE_CMP2_INP4     (CMP_PMSR_CVSL_3)   /*!< Select CMP2_INP4 */
/* Select positive input for CMP3 */
#define CMP3_POSITIVE_PGA3_BP       (CMP_PMSR_CVSL_0)                                       /*!< Select PGA3_BP */
#define CMP3_POSITIVE_PGA3          ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_0 << VISR_OFFSET))  /*!< Select PGA3 */
#define CMP3_POSITIVE_PGA4          ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_1 << VISR_OFFSET))  /*!< Select PGA4_BP */
#define CMP3_POSITIVE_CMP3_INP2     ((CMP_PMSR_CVSL_1) | (CMP_VISR_P2SL_2 << VISR_OFFSET))  /*!< Select CMP3_INP2 */
#define CMP3_POSITIVE_CMP3_INP3     ((CMP_PMSR_CVSL_2) | (CMP_VISR_P2SL_0 << VISR_OFFSET))  /*!< Select CMP3_INP3 */
#define CMP3_POSITIVE_CMP4_INP3     ((CMP_PMSR_CVSL_2) | (CMP_VISR_P2SL_1 << VISR_OFFSET))  /*!< Select CMP4_INP3 */
#define CMP3_POSITIVE_CMP3_INP4     (CMP_PMSR_CVSL_3)                                       /*!< Select CMP3_INP4 */
/* Select positive input for CMP4 */
#define CMP4_POSITIVE_PGA4_BP       (CMP_PMSR_CVSL_0)   /*!< Select PGA4_BP */
#define CMP4_POSITIVE_PGA4          (CMP_PMSR_CVSL_1)   /*!< Select PGA4 */
#define CMP4_POSITIVE_CMP4_INP3     (CMP_PMSR_CVSL_2)   /*!< Select CMP4_INP3 */
#define CMP4_POSITIVE_CMP4_INP4     (CMP_PMSR_CVSL_3)   /*!< Select CMP4_INP4 */

/**
 * @}
 */

/**
 * @defgroup CMP_Negative_Input_Select CMP Negative(Reference) Voltage Input
 * @{
 */
#define CMP_NEGATIVE_NONE           (0x0U)

/* Select negative input for CMP1 */
#define CMP1_NEGATIVE_DAC1_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC1_OUT1 */
#define CMP1_NEGATIVE_DAC1_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC1_OUT2 */
#define CMP1_NEGATIVE_CMP123_INM3   (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP1_NEGATIVE_CMP1_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP1_INM4 */
/* Select negative input for CMP2 */
#define CMP2_NEGATIVE_DAC1_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC1_OUT1 */
#define CMP2_NEGATIVE_DAC1_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC1_OUT2 */
#define CMP2_NEGATIVE_CMP123_INM3   (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP2_NEGATIVE_CMP2_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP2_INM4 */
/* Select negative input for CMP3 */
#define CMP3_NEGATIVE_DAC2_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC2_OUT1 */
#define CMP3_NEGATIVE_DAC2_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC2_OUT2 */
#define CMP3_NEGATIVE_CMP123_INM3   (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP3_NEGATIVE_CMP3_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP3_INM4 */
/* Select negative input for CMP4 */
#define CMP4_NEGATIVE_DAC2_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC2_OUT1 */
#define CMP4_NEGATIVE_DAC2_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC2_OUT2 */
#define CMP4_NEGATIVE_CMP4_INM3     (CMP_PMSR_RVSL_2)         /*!< Pin CMP4_INM3 */
#define CMP4_NEGATIVE_CMP4_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP4_INM4 */

/**
 * @}
 */

/**
 * @defgroup CMP_Window_Low_Select CMP Window Mode Window Low Voltage
 * @{
 */
#define CMP_WIN_LOW_NONE            (0x0U)
/* Select input for window mode CMP_WIN_CMP12 */
#define CMP12_WIN_LOW_DAC1_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC1_OUT1 */
#define CMP12_WIN_LOW_DAC1_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC1_OUT2 */
#define CMP12_WIN_LOW_CMP123_INM3   (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP12_WIN_LOW_CMP1_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP1_INM4 */
/* Select input for window mode CMP_WIN_CMP34 */
#define CMP34_WIN_LOW_DAC2_OUT1     (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC2_OUT1 */
#define CMP34_WIN_LOW_DAC2_OUT2     (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC2_OUT2 */
#define CMP34_WIN_LOW_CMP123_INM3   (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP34_WIN_LOW_CMP3_INM4     (CMP_PMSR_RVSL_3)         /*!< Pin CMP3_INM4 */

/**
 * @}
 */

/**
 * @defgroup CMP_Window_High_Select CMP Window Mode Window High Voltage
 * @{
 */
#define CMP_WIN_HIGH_NONE           (0x0U)
/* Select input for window mode CMP_WIN_CMP12 */
#define CMP12_WIN_HIGH_DAC1_OUT1    (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC1_OUT1 */
#define CMP12_WIN_HIGH_DAC1_OUT2    (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC1_OUT2 */
#define CMP12_WIN_HIGH_CMP123_INM3  (CMP_PMSR_RVSL_2)         /*!< Pin CMP123_INM3 */
#define CMP12_WIN_HIGH_CMP2_INM4    (CMP_PMSR_RVSL_3)         /*!< Pin CMP2_INM4 */
/* Select input for window mode CMP_WIN_CMP34 */
#define CMP34_WIN_HIGH_DAC2_OUT1    (CMP_PMSR_RVSL_0)         /*!< DAC voltage DAC2_OUT1 */
#define CMP34_WIN_HIGH_DAC2_OUT2    (CMP_PMSR_RVSL_1)         /*!< DAC voltage DAC2_OUT2 */
#define CMP34_WIN_HIGH_CMP4_INM3    (CMP_PMSR_RVSL_2)         /*!< Pin CMP4_INM3 */
#define CMP34_WIN_HIGH_CMP4_INM4    (CMP_PMSR_RVSL_3)         /*!< Pin CMP4_INM4 */

/**
 * @}
 */

/**
 * @defgroup CMP_Out_Polarity_Select CMP Output Polarity
 * @{
 */
#define CMP_OUT_INVT_OFF            (0x0U)                    /*!< CMP output don't reverse */
#define CMP_OUT_INVT_ON             (CMP_OCR_COPS)            /*!< CMP output level reverse */
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Detect_Edge_Select CMP Output Detect Edge
 * @{
 */
#define CMP_DETECT_EDGS_NONE        (0U)                       /*!< Do not detect edge */

#define CMP_DETECT_EDGS_RISING      (1U << CMP_FIR_EDGS_POS)   /*!< Detect rising edge */
#define CMP_DETECT_EDGS_FALLING     (2U << CMP_FIR_EDGS_POS)   /*!< Detect falling edge */
#define CMP_DETECT_EDGS_BOTH        (3U << CMP_FIR_EDGS_POS)   /*!< Detect rising and falling edges */

/**
 * @}
 */

/**
 * @defgroup CMP_Out_Filter CMP Output Filter Configuration
 * @{
 */
#define CMP_OUT_FILTER_NONE         (0U)                       /*!< Do not filter */

#define CMP_OUT_FILTER_CLK          (1U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV8     (2U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV32    (3U << CMP_FIR_FCKS_POS)

/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_Src CMP Output blank window Function Control Signal
 * @{
 */
/* CMP1 blank window signal */
#define CMP1_BLANKWIN_TMRA_1_PWM1     (CMP_TWSR_CTWS0)          /*!< Select TMRA_1_PWM1 for CMP1 */
#define CMP1_BLANKWIN_TMRA_1_PWM2     (CMP_TWSR_CTWS1)          /*!< Select TMRA_1_PWM2 for CMP1 */
#define CMP1_BLANKWIN_TMRA_1_PWM3     (CMP_TWSR_CTWS2)          /*!< Select TMRA_1_PWM3 for CMP1 */
#define CMP1_BLANKWIN_TMRA_2_PWM1     (CMP_TWSR_CTWS3)          /*!< Select TMRA_2_PWM1 for CMP1 */
#define CMP1_BLANKWIN_TMRA_2_PWM2     (CMP_TWSR_CTWS4)          /*!< Select TMRA_2_PWM2 for CMP1 */
#define CMP1_BLANKWIN_TMRA_2_PWM3     (CMP_TWSR_CTWS5)          /*!< Select TMRA_2_PWM3 for CMP1 */
#define CMP1_BLANKWIN_TMR6_1_PWMA     (CMP_TWSR_CTWS6)          /*!< Select TMR6_1_PWMA for CMP1 */
#define CMP1_BLANKWIN_TMR6_2_PWMA     (CMP_TWSR_CTWS7)          /*!< Select TMR6_2_PWMA for CMP1 */
#define CMP1_BLANKWIN_TMR6_3_PWMA     (CMP_TWSR_CTWS8)          /*!< Select TMR6_3_PWMA for CMP1 */
#define CMP1_BLANKWIN_TMR6_4_PWMA     (CMP_TWSR_CTWS9)          /*!< Select TMR6_4_PWMA for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OUH      (CMP_TWSR_CTWS10)         /*!< Select TMR4_1_OUH for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OUL      (CMP_TWSR_CTWS11)         /*!< Select TMR4_1_OUL for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OVH      (CMP_TWSR_CTWS12)         /*!< Select TMR4_1_OVH for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OVL      (CMP_TWSR_CTWS13)         /*!< Select TMR4_1_OVL for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OWH      (CMP_TWSR_CTWS14)         /*!< Select TMR4_1_OWH for CMP1 */
#define CMP1_BLANKWIN_TMR4_1_OWL      (CMP_TWSR_CTWS15)         /*!< Select TMR4_1_OWL for CMP1 */
/* CMP2 blank window signal */
#define CMP2_BLANKWIN_TMRA_3_PWM1     (CMP_TWSR_CTWS0)          /*!< Select TMRA_3_PWM1 for CMP2 */
#define CMP2_BLANKWIN_TMRA_3_PWM2     (CMP_TWSR_CTWS1)          /*!< Select TMRA_3_PWM2 for CMP2 */
#define CMP2_BLANKWIN_TMRA_3_PWM3     (CMP_TWSR_CTWS2)          /*!< Select TMRA_3_PWM3 for CMP2 */
#define CMP2_BLANKWIN_TMRA_4_PWM1     (CMP_TWSR_CTWS3)          /*!< Select TMRA_4_PWM1 for CMP2 */
#define CMP2_BLANKWIN_TMRA_4_PWM2     (CMP_TWSR_CTWS4)          /*!< Select TMRA_4_PWM2 for CMP2 */
#define CMP2_BLANKWIN_TMRA_4_PWM3     (CMP_TWSR_CTWS5)          /*!< Select TMRA_4_PWM3 for CMP2 */
#define CMP2_BLANKWIN_TMR6_5_PWMA     (CMP_TWSR_CTWS6)          /*!< Select TMR6_5_PWMA for CMP2 */
#define CMP2_BLANKWIN_TMR6_6_PWMA     (CMP_TWSR_CTWS7)          /*!< Select TMR6_6_PWMA for CMP2 */
#define CMP2_BLANKWIN_TMR6_7_PWMA     (CMP_TWSR_CTWS8)          /*!< Select TMR6_7_PWMA for CMP2 */
#define CMP2_BLANKWIN_TMR6_8_PWMA     (CMP_TWSR_CTWS9)          /*!< Select TMR6_8_PWMA for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OUH      (CMP_TWSR_CTWS10)         /*!< Select TMR4_2_OUH for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OUL      (CMP_TWSR_CTWS11)         /*!< Select TMR4_2_OUL for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OVH      (CMP_TWSR_CTWS12)         /*!< Select TMR4_2_OVH for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OVL      (CMP_TWSR_CTWS13)         /*!< Select TMR4_2_OVL for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OWH      (CMP_TWSR_CTWS14)         /*!< Select TMR4_2_OWH for CMP2 */
#define CMP2_BLANKWIN_TMR4_2_OWL      (CMP_TWSR_CTWS15)         /*!< Select TMR4_2_OWL for CMP2 */
/* CMP3 blank window signal */
#define CMP3_BLANKWIN_TMRA_1_PWM1     (CMP_TWSR_CTWS0)          /*!< Select TMRA_1_PWM1 for CMP3 */
#define CMP3_BLANKWIN_TMRA_1_PWM2     (CMP_TWSR_CTWS1)          /*!< Select TMRA_1_PWM2 for CMP3 */
#define CMP3_BLANKWIN_TMRA_1_PWM3     (CMP_TWSR_CTWS2)          /*!< Select TMRA_1_PWM3 for CMP3 */
#define CMP3_BLANKWIN_TMRA_3_PWM1     (CMP_TWSR_CTWS3)          /*!< Select TMRA_3_PWM1 for CMP3 */
#define CMP3_BLANKWIN_TMRA_3_PWM2     (CMP_TWSR_CTWS4)          /*!< Select TMRA_3_PWM2 for CMP3 */
#define CMP3_BLANKWIN_TMRA_3_PWM3     (CMP_TWSR_CTWS5)          /*!< Select TMRA_3_PWM3 for CMP3 */
#define CMP3_BLANKWIN_TMR6_1_PWMB     (CMP_TWSR_CTWS6)          /*!< Select TMR6_1_PWMB for CMP3 */
#define CMP3_BLANKWIN_TMR6_2_PWMB     (CMP_TWSR_CTWS7)          /*!< Select TMR6_2_PWMB for CMP3 */
#define CMP3_BLANKWIN_TMR6_3_PWMB     (CMP_TWSR_CTWS8)          /*!< Select TMR6_3_PWMB for CMP3 */
#define CMP3_BLANKWIN_TMR6_4_PWMB     (CMP_TWSR_CTWS9)          /*!< Select TMR6_4_PWMB for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OUH      (CMP_TWSR_CTWS10)         /*!< Select TMR4_3_OUH for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OUL      (CMP_TWSR_CTWS11)         /*!< Select TMR4_3_OUL for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OVH      (CMP_TWSR_CTWS12)         /*!< Select TMR4_3_OVH for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OVL      (CMP_TWSR_CTWS13)         /*!< Select TMR4_3_OVL for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OWH      (CMP_TWSR_CTWS14)         /*!< Select TMR4_3_OWH for CMP3 */
#define CMP3_BLANKWIN_TMR4_3_OWL      (CMP_TWSR_CTWS15)         /*!< Select TMR4_3_OWL for CMP3 */
/* CMP4 blank window signal */
#define CMP4_BLANKWIN_TMRA_2_PWM1     (CMP_TWSR_CTWS0)          /*!< Select TMRA_2_PWM1 for CMP4 */
#define CMP4_BLANKWIN_TMRA_2_PWM2     (CMP_TWSR_CTWS1)          /*!< Select TMRA_2_PWM2 for CMP4 */
#define CMP4_BLANKWIN_TMRA_2_PWM3     (CMP_TWSR_CTWS2)          /*!< Select TMRA_2_PWM3 for CMP3 */
#define CMP4_BLANKWIN_TMRA_4_PWM1     (CMP_TWSR_CTWS3)          /*!< Select TMRA_4_PWM1 for CMP4 */
#define CMP4_BLANKWIN_TMRA_4_PWM2     (CMP_TWSR_CTWS4)          /*!< Select TMRA_4_PWM2 for CMP4 */
#define CMP4_BLANKWIN_TMRA_4_PWM3     (CMP_TWSR_CTWS5)          /*!< Select TMRA_4_PWM3 for CMP4 */
#define CMP4_BLANKWIN_TMR6_5_PWMB     (CMP_TWSR_CTWS6)          /*!< Select TMR6_5_PWMB for CMP4 */
#define CMP4_BLANKWIN_TMR6_6_PWMB     (CMP_TWSR_CTWS7)          /*!< Select TMR6_6_PWMB for CMP4 */
#define CMP4_BLANKWIN_TMR6_7_PWMB     (CMP_TWSR_CTWS8)          /*!< Select TMR6_7_PWMB for CMP4 */
#define CMP4_BLANKWIN_TMR6_8_PWMB     (CMP_TWSR_CTWS9)          /*!< Select TMR6_8_PWMB for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OUH      (CMP_TWSR_CTWS10)         /*!< Select TMR4_4_OUH for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OUL      (CMP_TWSR_CTWS11)         /*!< Select TMR4_4_OUL for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OVH      (CMP_TWSR_CTWS12)         /*!< Select TMR4_4_OVH for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OVL      (CMP_TWSR_CTWS13)         /*!< Select TMR4_4_OVL for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OWH      (CMP_TWSR_CTWS14)         /*!< Select TMR4_4_OWH for CMP4 */
#define CMP4_BLANKWIN_TMR4_3_OWL      (CMP_TWSR_CTWS15)         /*!< Select TMR4_4_OWL for CMP4 */

/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_Valid_Level CMP Blank Window Valid Level
 * @{
 */
#define CMP_BLANKWIN_VALID_LVL_LOW    (0U)                   /*!< Blank window valid level is low */
#define CMP_BLANKWIN_VALID_LVL_HIGH   (1U)                   /*!< Blank window valid level is high */
/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_output_Level CMP Output Level When Blank Windows Valid
 * @{
 */
#define CMP_BLANKWIN_OUTPUT_LVL_LOW   (0U)                   /*!< Output low when blank windows valid */
#define CMP_BLANKWIN_OUTPUT_LVL_HIGH  (CMP_OCR_TWOL)         /*!< Output high when blank windows valid */
/**
 * @}
 */

/**
 * @defgroup CMP_8BitDAC_Adc_Ref_Switch CMP 8 bit DAC ADC Reference Voltage Switch
 * @{
 */
/**
 * @}
 */

/**
 * @defgroup CMP_8Bit_Dac_Ch CMP 8 bit DAC Channel
 * @{
 */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup CMP_Global_Functions
 * @{
 */

int32_t CMP_StructInit(stc_cmp_init_t *pstcCmpInit);
int32_t CMP_NormalModeInit(CM_CMP_TypeDef *CMPx, const stc_cmp_init_t *pstcCmpInit);
void CMP_DeInit(CM_CMP_TypeDef *CMPx);

void CMP_FuncCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_IntCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_CompareOutCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_PinVcoutCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
en_flag_status_t CMP_GetStatus(const CM_CMP_TypeDef *CMPx);
void CMP_SetOutDetectEdge(CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges);
void CMP_SetOutFilter(CM_CMP_TypeDef *CMPx, uint8_t u8CmpFilter);
void CMP_SetOutPolarity(CM_CMP_TypeDef *CMPx, uint16_t u16CmpPolarity);
void CMP_SetPositiveInput(CM_CMP_TypeDef *CMPx, uint16_t  u16PositiveInput);
void CMP_SetNegativeInput(CM_CMP_TypeDef *CMPx, uint16_t u16NegativeInput);

int32_t CMP_WindowModeInit(uint8_t u8WinCMPx, const stc_cmp_window_init_t *pstcCmpWindowInit);
int32_t CMP_WindowStructInit(stc_cmp_window_init_t *pstcCmpWindowInit);

void CMP_BlankWindowSrcDisable(CM_CMP_TypeDef *CMPx, uint16_t u16BlankWindowSrc);
int32_t CMP_BlankWindowConfig(CM_CMP_TypeDef *CMPx, const stc_cmp_blankwindow_t *pstcBlankWindowInit);
void CMP_BlankWindowCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_CMP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_CMP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

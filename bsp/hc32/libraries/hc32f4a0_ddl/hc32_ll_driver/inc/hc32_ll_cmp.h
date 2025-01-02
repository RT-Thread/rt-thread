/**
 *******************************************************************************
 * @file  hc32_ll_cmp.h
 * @brief This file contains all the functions prototypes of the CMP driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify structure stc_cmp_window_init_t
                                    Modify macro define for API
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
    /* Window mode Positive(compare voltage) input:
       CMP2_INP3 valid for u16PositiveInput of CMP_WIN_CMP12
       CMP4_INP3 valid for u16PositiveInput of CMP_WIN_CMP34 */
    uint16_t u16WinVolLow;          /*!< CMP reference low voltage for window mode @ref CMP_Window_Low_Select */
    uint16_t u16WinVolHigh;         /*!< CMP reference high voltage for window mode @ref CMP_Window_High_Select */
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
/* Negative input select table
        CMP1            CMP2            CMP3            CMP4
--------------------------------------------------------------------
INM1    DAC1_OUT1       DAC1_OUT1       DAC2_OUT1       DAC2_OUT1
INM2    DAC1_OUT2       DAC1_OUT2       DAC2_OUT2       DAC2_OUT2
INM3    CMP123_INM3     CMP123_INM3     CMP123_INM3     CMP4_INM3
INM4    CMP1_INM4       CMP2_INM4       CMP3_INM4       CMP4_INM4
*/
#define CMP_NEGATIVE_INM1           (CMP_PMSR_RVSL_0)
#define CMP_NEGATIVE_INM2           (CMP_PMSR_RVSL_1)
#define CMP_NEGATIVE_INM3           (CMP_PMSR_RVSL_2)
#define CMP_NEGATIVE_INM4           (CMP_PMSR_RVSL_3)
/**
 * @}
 */

/**
 * @defgroup CMP_Window_Low_Select CMP Window Mode Window Low Voltage
 * @{
 */
#define CMP_WIN_LOW_NONE            (0x0U)
/* Window mode low voltage select table
        WIN_CMP12       WIN_CMP34
------------------------------------
INM1    DAC1_OUT1       DAC2_OUT1
INM2    DAC1_OUT2       DAC2_OUT2
INM3    CMP123_INM3     CMP123_INM3
INM4    CMP1_INM4       CMP3_INM4
*/
#define CMP_WIN_LOW_INM1            (CMP_PMSR_RVSL_0)
#define CMP_WIN_LOW_INM2            (CMP_PMSR_RVSL_1)
#define CMP_WIN_LOW_INM3            (CMP_PMSR_RVSL_2)
#define CMP_WIN_LOW_INM4            (CMP_PMSR_RVSL_3)
/**
 * @}
 */

/**
 * @defgroup CMP_Window_High_Select CMP Window Mode Window High Voltage
 * @{
 */
#define CMP_WIN_HIGH_NONE           (0x0U)
/* Window mode high voltage select table
        WIN_CMP12       WIN_CMP34
-------------------------------------------------------
INM1    DAC1_OUT1       DAC2_OUT1
INM2    DAC1_OUT2       DAC2_OUT2
INM3    CMP123_INM3     CMP4_INM3
INM4    CMP2_INM4       CMP4_INM4
*/
#define CMP_WIN_HIGH_INM1           (CMP_PMSR_RVSL_0)
#define CMP_WIN_HIGH_INM2           (CMP_PMSR_RVSL_1)
#define CMP_WIN_HIGH_INM3           (CMP_PMSR_RVSL_2)
#define CMP_WIN_HIGH_INM4           (CMP_PMSR_RVSL_3)
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
/* Blank window PWM source select table
        CMP1            CMP2            CMP3            CMP4
------------------------------------------------------------------------
SRC1    TMRA_1_PWM1     TMRA_3_PWM1     TMRA_1_PWM1     TMRA_2_PWM1
SRC2    TMRA_1_PWM2     TMRA_3_PWM2     TMRA_1_PWM2     TMRA_2_PWM2
SRC3    TMRA_1_PWM3     TMRA_3_PWM3     TMRA_1_PWM3     TMRA_2_PWM3
SRC4    TMRA_2_PWM1     TMRA_4_PWM1     TMRA_3_PWM1     TMRA_4_PWM1
SRC5    TMRA_2_PWM2     TMRA_4_PWM2     TMRA_3_PWM2     TMRA_4_PWM2
SRC6    TMRA_2_PWM3     TMRA_4_PWM3     TMRA_3_PWM3     TMRA_4_PWM3
SRC7    TMR6_1_PWMA     TMR6_5_PWMA     TMR6_1_PWMB     TMR6_5_PWMB
SRC8    TMR6_2_PWMA     TMR6_6_PWMA     TMR6_2_PWMB     TMR6_6_PWMB
SRC9    TMR6_3_PWMA     TMR6_7_PWMA     TMR6_3_PWMB     TMR6_7_PWMB
SRC10   TMR6_4_PWMA     TMR6_8_PWMA     TMR6_4_PWMB     TMR6_8_PWMB
SRC11   TMR4_1_OUH      TMR4_2_OUH      TMR4_3_OUH      TMR4_3_OUH
SRC12   TMR4_1_OUL      TMR4_2_OUL      TMR4_3_OUL      TMR4_3_OUL
SRC13   TMR4_1_OVH      TMR4_2_OVH      TMR4_3_OVH      TMR4_3_OVH
SRC14   TMR4_1_OVL      TMR4_2_OVL      TMR4_3_OVL      TMR4_3_OVL
SRC15   TMR4_1_OWH      TMR4_2_OWH      TMR4_3_OWH      TMR4_3_OWH
SRC16   TMR4_1_OWL      TMR4_2_OWL      TMR4_3_OWL      TMR4_3_OWL
*/
#define CMP_BLANKWIN_SRC1           (CMP_TWSR_CTWS0)
#define CMP_BLANKWIN_SRC2           (CMP_TWSR_CTWS1)
#define CMP_BLANKWIN_SRC3           (CMP_TWSR_CTWS2)
#define CMP_BLANKWIN_SRC4           (CMP_TWSR_CTWS3)
#define CMP_BLANKWIN_SRC5           (CMP_TWSR_CTWS4)
#define CMP_BLANKWIN_SRC6           (CMP_TWSR_CTWS5)
#define CMP_BLANKWIN_SRC7           (CMP_TWSR_CTWS6)
#define CMP_BLANKWIN_SRC8           (CMP_TWSR_CTWS7)
#define CMP_BLANKWIN_SRC9           (CMP_TWSR_CTWS8)
#define CMP_BLANKWIN_SRC10          (CMP_TWSR_CTWS9)
#define CMP_BLANKWIN_SRC11          (CMP_TWSR_CTWS10)
#define CMP_BLANKWIN_SRC12          (CMP_TWSR_CTWS11)
#define CMP_BLANKWIN_SRC13          (CMP_TWSR_CTWS12)
#define CMP_BLANKWIN_SRC14          (CMP_TWSR_CTWS13)
#define CMP_BLANKWIN_SRC15          (CMP_TWSR_CTWS14)
#define CMP_BLANKWIN_SRC16          (CMP_TWSR_CTWS15)

/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_Valid_Level CMP Blank Window Valid Level
 * @{
 */
#define CMP_BLANKWIN_VALID_LVL_LOW  (0U)                   /*!< Blank window valid level is low */
#define CMP_BLANKWIN_VALID_LVL_HIGH (1U)                   /*!< Blank window valid level is high */
/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_output_Level CMP Output Level When Blank Windows Valid
 * @{
 */
#define CMP_BLANKWIN_OUTPUT_LVL_LOW     (0U)                   /*!< Output low when blank windows valid */
#define CMP_BLANKWIN_OUTPUT_LVL_HIGH    (CMP_OCR_TWOL)         /*!< Output high when blank windows valid */
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
int32_t CMP_BlankWindowConfig(CM_CMP_TypeDef *CMPx, const stc_cmp_blankwindow_t *pstcBlankWindowConfig);
int32_t CMP_BlankWindowStructInit(stc_cmp_blankwindow_t *pstcBlankWindowConfig);
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

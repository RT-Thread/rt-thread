/**
 *******************************************************************************
 * @file  hc32_ll_cmp.h
 * @brief This file contains all the functions prototypes of the CMP driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-12-15       CDT             Modify comments related to chip series
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
    uint16_t u16HystVoltage;        /*!< CMP hysteresis voltage @ref CMP_Hyst_Voltage */
} stc_cmp_init_t;

/**
 * @brief CMP window mode configuration structure
 */
typedef struct {
    uint16_t u16PositiveInput;      /*!< Window mode Positive(compare voltage) input @ref CMP_Window_Positive_Select */
    uint16_t u16WinVolLow;          /*!< CMP reference low voltage for window mode @ref CMP_Window_Low_Select */
    uint16_t u16WinVolHigh;         /*!< CMP reference high voltage for window mode @ref CMP_Window_High_Select */
    uint16_t u16OutPolarity;        /*!< Output polarity select, @ref CMP_Out_Polarity_Select */
    uint16_t u16OutDetectEdge;      /*!< Output detect edge, @ref CMP_Out_Detect_Edge_Select */
    uint16_t u16OutFilter;          /*!< Output Filter, @ref CMP_Out_Filter */
    uint16_t u16HystVoltage;        /*!< CMP hysteresis voltage @ref CMP_Hyst_Voltage */
} stc_cmp_window_init_t;

/**
 * @brief CMP blank window function configuration structure
 */
typedef struct {
    uint8_t u8Mode;                 /*!< blank window mode select, @ref CMP_BlankWindow_Mode */
    uint16_t u16Src;                /*!< blank window source select,
                                         can be any combination of @ref CMP_BlankWindow_Src */
    uint16_t u16ValidLevelEdge;     /*!< Valid level for blank window level mode @ref CMP_BlankWindow_Valid_Level
                                         Valid edge for blank window edge mode @ref CMP_BlankWindow_Valid_Edge */
    uint16_t u16MaskWidth;          /*!< Mask width when valid edge occurs for blank window edge mode, which range
                                         from 0~255 */
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
#define CMP_WIN_CMP34               (0x02U)  /* Only effective for HC32F472KCHI/HC32F472KEHI */

/**
 * @}
 */

/**
 * @defgroup CMP_Positive_Input_Select CMP Positive(Compare) Voltage Input
 * @{
 */
#define CMP_POSITIVE_NONE           (0x0U)
/* Positive input select table
        CMP1    CMP2    CMP3    CMP4
-------------------------------------
INP1    PA1     PA1     PB0     PB0
INP2    PA3     PA3     PB11    PB11
INP3    PA4     PA4     PGA1    PGA1 (Only effective for HC32F472KCHI/HC32F472KEHI)
INP4    PA7     PA7     PGA2    PGA2 (Only effective for HC32F472KCHI/HC32F472KEHI)
*/
#define CMP_POSITIVE_INP1           (CMP_PMSR_CVSL_0 >> CMP_PMSR_CVSL_POS)
#define CMP_POSITIVE_INP2           (CMP_PMSR_CVSL_1 >> CMP_PMSR_CVSL_POS)
#define CMP_POSITIVE_INP3           (CMP_PMSR_CVSL_2 >> CMP_PMSR_CVSL_POS)
#define CMP_POSITIVE_INP4           (CMP_PMSR_CVSL_3 >> CMP_PMSR_CVSL_POS)
/**
 * @}
 */

/**
 * @defgroup CMP_Window_Positive_Select CMP Window Mode positive(compare) Voltage
 * @{
 */
#define CMP_WIN_POSITIVE_NONE       (0x0U)
/* Positive input select table for window mode
        WIN_CMP12    WIN_CMP34
----------------------------------------------
INP1    PA1          PB0
INP2    PA3          PB11
INP3    PA4          PGA1  (Only effective for HC32F472KCHI/HC32F472KEHI)
INP4    PA7          PGA2  (Only effective for HC32F472KCHI/HC32F472KEHI)
*/
#define CMP_WIN_POSITIVE_INP1       (CMP_PMSR_CVSL_0 >> CMP_PMSR_CVSL_POS)
#define CMP_WIN_POSITIVE_INP2       (CMP_PMSR_CVSL_1 >> CMP_PMSR_CVSL_POS)
#define CMP_WIN_POSITIVE_INP3       (CMP_PMSR_CVSL_2 >> CMP_PMSR_CVSL_POS)
#define CMP_WIN_POSITIVE_INP4       (CMP_PMSR_CVSL_3 >> CMP_PMSR_CVSL_POS)
/**
 * @}
 */

/**
 * @defgroup CMP_Negative_Input_Select CMP Negative(Reference) Voltage Input
 * @{
 */
#define CMP_NEGATIVE_NONE           (0x0U)
/* Negative input select table for HC32F472KCHI/HC32F472KEHI
        CMP1        CMP2        CMP3        CMP4
-------------------------------------------------------
INM1    VREF*1/4    VREF*1/4    VREF*1/4    VREF*1/4
INM2    VREF*1/2    VREF*1/2    VREF*1/2    VREF*1/2
INM3    VREF*3/4    VREF*3/4    VREF*3/4    VREF*3/4
INM4    VREF        VREF        VREF        VREF
INM5    DA3O2       DA1O2       DA2O1       DA2O2
INM6    DA3O1       DA3O1       DA3O1       DA3O1
INM7    PA0         PA2         PB15        PB2
INM8    PA2         PA4         PA4         PA4
INM9    PA4         PA6         PA5         PA5
INM10   PA5         PA7         PA7         PA6
*/
/* Negative input select table for HC32F472JCTI/HC32F472JETI/HC32F472PCTI/HC32F472PETI
        CMP1        CMP2
------------------------------
INM1    VREF*1/4    VREF*1/4
INM2    VREF*1/2    VREF*1/2
INM3    VREF*3/4    VREF*3/4
INM4    VREF        VREF
INM5    DA1O1       DA1O2
INM6    DA1O2       DA1O2
INM7    PA0         PA2
INM8    PA2         -
*/
#define CMP_NEGATIVE_INM1           (CMP_PMSR_RVSL_0)
#define CMP_NEGATIVE_INM2           (CMP_PMSR_RVSL_1)
#define CMP_NEGATIVE_INM3           (CMP_PMSR_RVSL_2)
#define CMP_NEGATIVE_INM4           (CMP_PMSR_RVSL_3)
#define CMP_NEGATIVE_INM5           (CMP_PMSR_RVSL_4)
#define CMP_NEGATIVE_INM6           (CMP_PMSR_RVSL_5)
#define CMP_NEGATIVE_INM7           (CMP_PMSR_RVSL_6)
#define CMP_NEGATIVE_INM8           (CMP_PMSR_RVSL_7)
#define CMP_NEGATIVE_INM9           (CMP_PMSR_RVSL_8)
#define CMP_NEGATIVE_INM10          (CMP_PMSR_RVSL_9)
/**
 * @}
 */

/**
 * @defgroup CMP_Window_Low_Select CMP Window Mode Window Low Voltage
 * @{
 */
#define CMP_WIN_LOW_NONE            (0x0U)
/* Window mode low voltage select table
        WIN_CMP12    WIN_CMP34
--------------------------------
INM1    VREF*1/4     VREF*1/4
INM2    VREF*1/2     VREF*1/2
INM3    VREF*3/4     VREF*3/4
INM4    VREF         VREF
INM5    DA3O2        DA2O1
INM6    DA3O1        DA3O1
INM7    PA0          PB15
INM8    PA2          PA4
INM9    PA4          PA5   (Only effective for HC32F472KCHI/HC32F472KEHI)
INM10   PA5          PA7   (Only effective for HC32F472KCHI/HC32F472KEHI)
*/
#define CMP_WIN_LOW_INM1            (CMP_PMSR_RVSL_0)
#define CMP_WIN_LOW_INM2            (CMP_PMSR_RVSL_1)
#define CMP_WIN_LOW_INM3            (CMP_PMSR_RVSL_2)
#define CMP_WIN_LOW_INM4            (CMP_PMSR_RVSL_3)
#define CMP_WIN_LOW_INM5            (CMP_PMSR_RVSL_4)
#define CMP_WIN_LOW_INM6            (CMP_PMSR_RVSL_5)
#define CMP_WIN_LOW_INM7            (CMP_PMSR_RVSL_6)
#define CMP_WIN_LOW_INM8            (CMP_PMSR_RVSL_7)
#define CMP_WIN_LOW_INM9            (CMP_PMSR_RVSL_8)
#define CMP_WIN_LOW_INM10           (CMP_PMSR_RVSL_9)
/**
 * @}
 */

/**
 * @defgroup CMP_Window_High_Select CMP Window Mode Window High Voltage
 * @{
 */
#define CMP_WIN_HIGH_NONE           (0x0U)
/* Window mode high voltage select table
        WIN_CMP12    WIN_CMP34
-------------------------------------------------------
INM1    VREF*1/4     VREF*1/4
INM2    VREF*1/2     VREF*1/2
INM3    VREF*3/4     VREF*3/4
INM4    VREF         VREF
INM5    DA1O2        DA2O2
INM6    DA3O1        DA3O1
INM7    PA2          PB2
INM8    PA4          PA4  (Only effective for HC32F472KCHI/HC32F472KEHI)
INM9    PA6          PA5  (Only effective for HC32F472KCHI/HC32F472KEHI)
INM10   PA7          PA6  (Only effective for HC32F472KCHI/HC32F472KEHI)
*/
#define CMP_WIN_HIGH_INM1           (CMP_PMSR_RVSL_0)
#define CMP_WIN_HIGH_INM2           (CMP_PMSR_RVSL_1)
#define CMP_WIN_HIGH_INM3           (CMP_PMSR_RVSL_2)
#define CMP_WIN_HIGH_INM4           (CMP_PMSR_RVSL_3)
#define CMP_WIN_HIGH_INM5           (CMP_PMSR_RVSL_4)
#define CMP_WIN_HIGH_INM6           (CMP_PMSR_RVSL_5)
#define CMP_WIN_HIGH_INM7           (CMP_PMSR_RVSL_6)
#define CMP_WIN_HIGH_INM8           (CMP_PMSR_RVSL_7)
#define CMP_WIN_HIGH_INM9           (CMP_PMSR_RVSL_8)
#define CMP_WIN_HIGH_INM10          (CMP_PMSR_RVSL_9)
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
#define CMP_OUT_FILTER_CLK_DIV2     (2U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV4     (3U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV8     (4U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV16    (5U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV32    (6U << CMP_FIR_FCKS_POS)
#define CMP_OUT_FILTER_CLK_DIV64    (7U << CMP_FIR_FCKS_POS)
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
SRC1    TIMA_1_PWM1     TIMA_3_PWM1     TIMA_1_PWM1     TIMA_2_PWM1
SRC2    TIMA_1_PWM2     TIMA_3_PWM2     TIMA_1_PWM2     TIMA_2_PWM2
SRC3    TIMA_1_PWM3     TIMA_3_PWM3     TIMA_1_PWM3     TIMA_2_PWM3
SRC4    TIMA_2_PWM1     TIMA_4_PWM1     TIMA_3_PWM1     TIMA_4_PWM1
SRC5    TIMA_2_PWM2     TIMA_4_PWM2     TIMA_3_PWM2     TIMA_4_PWM2
SRC6    TIMA_2_PWM3     TIMA_4_PWM3     TIMA_3_PWM3     TIMA_4_PWM3
SRC7    TIM6_1_PWMA     TIM6_2_PWMA     TIM6_1_PWMA     TIM6_2_PWMA
SRC8    TIM6_3_PWMA     TIM6_4_PWMA     TIM6_3_PWMA     TIM6_4_PWMA
SRC9    TIM6_5_PWMA     TIM6_6_PWMA     TIM6_5_PWMA     TIM6_6_PWMA
SRC10   TIM6_7_PWMA     TIM6_8_PWMA     TIM6_7_PWMA     TIM6_8_PWMA
SRC11   TIM4_1_OUH      TIM4_1_OUH      TIM4_1_OUH      TIM4_1_OUH
SRC12   TIM4_1_OUL      TIM4_1_OUL      TIM4_1_OUL      TIM4_1_OUL
SRC13   TIM4_1_OVH      TIM4_1_OVH      TIM4_1_OVH      TIM4_1_OVH
SRC14   TIM4_1_OVL      TIM4_1_OVL      TIM4_1_OVL      TIM4_1_OVL
SRC15   TIM4_1_OWH      TIM4_1_OWH      TIM4_1_OWH      TIM4_1_OWH
SRC16   TIM4_1_OWL      TIM4_1_OWL      TIM4_1_OWL      TIM4_1_OWL
*/
#define CMP_BLANKWIN_SRC1           (CMP_BWSR1_CTWS0)
#define CMP_BLANKWIN_SRC2           (CMP_BWSR1_CTWS1)
#define CMP_BLANKWIN_SRC3           (CMP_BWSR1_CTWS2)
#define CMP_BLANKWIN_SRC4           (CMP_BWSR1_CTWS3)
#define CMP_BLANKWIN_SRC5           (CMP_BWSR1_CTWS4)
#define CMP_BLANKWIN_SRC6           (CMP_BWSR1_CTWS5)
#define CMP_BLANKWIN_SRC7           (CMP_BWSR1_CTWS6)
#define CMP_BLANKWIN_SRC8           (CMP_BWSR1_CTWS7)
#define CMP_BLANKWIN_SRC9           (CMP_BWSR1_CTWS8)
#define CMP_BLANKWIN_SRC10          (CMP_BWSR1_CTWS9)
#define CMP_BLANKWIN_SRC11          (CMP_BWSR1_CTWS10)
#define CMP_BLANKWIN_SRC12          (CMP_BWSR1_CTWS11)
#define CMP_BLANKWIN_SRC13          (CMP_BWSR1_CTWS12)
#define CMP_BLANKWIN_SRC14          (CMP_BWSR1_CTWS13)
#define CMP_BLANKWIN_SRC15          (CMP_BWSR1_CTWS14)
#define CMP_BLANKWIN_SRC16          (CMP_BWSR1_CTWS15)
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
#define CMP_BLANKWIN_OUTPUT_LVL_LOW     (0U)                       /*!< Output low when blank windows valid */
#define CMP_BLANKWIN_OUTPUT_LVL_HIGH    (1U << CMP_OCR_BWOL_POS)   /*!< Output high when blank windows valid */
#define CMP_BLANKWIN_OUTPUT_LVL_HOLD    (2U << CMP_OCR_BWOL_POS)   /*!< Output level hold when blank windows valid */
/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_Mode CMP Blank Windows Mode
 * @{
 */
#define CMP_BLANKWIN_MD_LVL         (0U)
#define CMP_BLANKWIN_MD_EDGE        (CMP_OCR_BWMD)
/**
 * @}
 */

/**
 * @defgroup CMP_BlankWindow_Valid_Edge CMP Blank Windows valid edge for edge mode
 * @{
 */
#define CMP_BLANKWIN_VALID_EDGE_NONE    (0U)                                    /*!< Blank window valid edge none */
#define CMP_BLANKWIN_VALID_EDGE_RISING  (CMP_BWSR2_TWEG_0)                      /*!< Blank window rising edge valid */
#define CMP_BLANKWIN_VALID_EDGE_FALLING (CMP_BWSR2_TWEG_1)                      /*!< Blank window falling edge valid */
#define CMP_BLANKWIN_VALID_EDGE_ALL     (CMP_BWSR2_TWEG_0 | CMP_BWSR2_TWEG_1)   /*!< Blank window all edge valid */
/**
 * @}
 */

/**
 * @defgroup CMP_Hyst_Voltage CMP Hysteresis Voltage
 * @{
 */
#define CMP_HYST_VOLT_NONE          (0U)
#define CMP_HYST_VOLT_10MV          (1U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_20MV          (2U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_30MV          (3U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_40MV          (4U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_50MV          (5U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_60MV          (6U << CMP_MDR_HYST_POS)
#define CMP_HYST_VOLT_70MV          (7U << CMP_MDR_HYST_POS)
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
/** Note: The parameter CMPx for CMP API
 *        HC32F472KCHI/HC32F472KEHI: CM_CMP1/CM_CMP2/CM_CMP3/CM_CMP4
 *        HC32F472JCTI/HC32F472JETI/HC32F472PCTI/HC32F472PETI: CM_CMP1/CM_CMP2
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
void CMP_SetHystVoltage(CM_CMP_TypeDef *CMPx, uint16_t u16HystVoltage);
void CMP_ClearOutDetectFlag(CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges);
en_flag_status_t CMP_GetOutDetectFlag(const CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges);

int32_t CMP_WindowModeInit(uint8_t u8WinCMPx, const stc_cmp_window_init_t *pstcCmpWindowInit);
int32_t CMP_WindowStructInit(stc_cmp_window_init_t *pstcCmpWindowInit);

void CMP_BlankWindowSrcDisable(CM_CMP_TypeDef *CMPx, uint16_t u16BlankWindowSrc);
int32_t CMP_BlankWindowConfig(CM_CMP_TypeDef *CMPx, const stc_cmp_blankwindow_t *pstcBlankWindowConfig);
int32_t CMP_BlankWindowStructInit(stc_cmp_blankwindow_t *pstcBlankWindowConfig);
void CMP_BlankWindowCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);
void CMP_BlankWindowMode(CM_CMP_TypeDef *CMPx, uint8_t u8Mode);

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

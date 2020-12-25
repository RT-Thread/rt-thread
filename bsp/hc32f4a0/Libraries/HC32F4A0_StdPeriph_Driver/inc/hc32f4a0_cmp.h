/**
 *******************************************************************************
 * @file  hc32f4a0_cmp.h
 * @brief Head file for CMP module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_CMP_H__
#define __HC32F4A0_CMP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_CMP
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CMP_Global_Types CMP Global Types
 * @{
 */

/**
 * @brief CMP configuration structure
 */
typedef struct
{
    uint8_t u8CmpCh;                /*!< Select the compare voltage channel for normal mode
                                        @ref CMP_CVSL_Channal */
    uint16_t u16CmpVol;             /*!< Select the compare voltage source for normal mode
                                        (Config the parameter when use CMP1 or CMP3)@ref CMP1_3_CVSL_Source */
    uint8_t u8RefVol;               /*!< Reference voltage for normal mode, @ref CMP_RVSL_Source*/

    uint8_t u8OutPolarity;          /*!< Output polarity select, @ref CMP_Out_Polarity_Select */

    uint8_t u8OutDetectEdges;       /*!< Output detecte edge, @ref CMP_Out_Detect_Edge */

    uint8_t u8OutFilter;            /*!< Output Filter, @ref CMP_Out_Filter */
}stc_cmp_init_t;

/**
 * @brief CMP reference voltage for window mode configuration structure
 */
typedef struct
{
    uint8_t u8CmpCh1;               /*!< Select the compare voltage channel for window mode
                                        @ref CMP_CVSL_Channal */
    uint16_t u16CmpVol;             /*!< Select the compare voltage source for window mode
                                        (Config the parameter when use CMP1 or CMP3)@ref CMP1_3_CVSL_Source */
    uint8_t u8CmpCh2;               /*!< Select the compare voltage channel for window mode
                                        @ref CMP_CVSL_Channal */
    uint8_t u8WinVolLow;            /*!< CMP reference low voltage for window mode
                                        @ref CMP_RVSL_Source */
    uint8_t u8WinVolHigh;           /*!< CMP reference high voltage for window mode
                                        @ref CMP_RVSL_Source */
}stc_cmp_win_ref_t;

/**
 * @brief CMP timer windows function configuration structure
 */
typedef struct
{
    uint16_t u16TWSelect;           /*!< Timer window source select
                                         @ref CMP_TimerWin_Select */
    uint8_t u8TWOutLevel;           /*!< Timer window mode output level
                                        @ref CMP_TimerWin_output_Level*/
    uint8_t u8TWInvalidLevel;       /*!< Output level when timer window invalid
                                        @ref CMP_TimerWin_Invalid_Level */
}stc_cmp_timerwindow_t;

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

/** @defgroup CMP_Mode CMP compare mode
  * @{
  */
#define CMP_MODE_NORMAL         (0x00U)                  /*!< Normal mode */
#define CMP_MODE_WINDOW         (CMP_MDR_CWDE)           /*!< Window mode */
/**
 * @}
 */

/** @defgroup CMP_CVSL_Channal CMP compare voltage channel selection
  * @{
  */
#define CMP_CVSL_NONE           (0x0U)                    /*!< No input compare voltage */
#define CMP_CVSL_INP1           (CMP_PMSR_CVSL_0)         /*!< Select INP1 as compare voltage */
#define CMP_CVSL_INP2           (CMP_PMSR_CVSL_1)         /*!< Select INP2 as compare voltage */
#define CMP_CVSL_INP3           (CMP_PMSR_CVSL_2)         /*!< Select INP3 as compare voltage */
#define CMP_CVSL_INP4           (CMP_PMSR_CVSL_3)         /*!< Select INP4 as compare voltage */
/**
 * @}
 */

/** @defgroup CMP_RVSL_Source CMP reference voltage selection
  * @{
  */
#define CMP_RVSL_NONE           (0x0U)                    /*!< No input reference voltage */
#define CMP_RVSL_INM1           (CMP_PMSR_RVSL_0)         /*!< Select INM1 as reference voltage */
#define CMP_RVSL_INM2           (CMP_PMSR_RVSL_1)         /*!< Select INM2 as reference voltage */
#define CMP_RVSL_INM3           (CMP_PMSR_RVSL_2)         /*!< Select INM3 as reference voltage */
#define CMP_RVSL_INM4           (CMP_PMSR_RVSL_3)         /*!< Select INM4 as reference voltage */
/**
 * @}
 */

/** @defgroup CMP1_3_CVSL_Source CMP1 CMP3 compare voltage selection
  * @{
  */
#define CMP1_INP3_NONE          (0x0U)                    /*!< No input voltage to CMP1 INP3 */
#define CMP1_INP3_CMP1_INP3     (CMP_VISR_P3SL_0)         /*!< Select CMP1_INP3 as CMP1 INP3 input */
#define CMP1_INP3_CMP2_INP3     (CMP_VISR_P3SL_1)         /*!< Select CMP2_INP3 as CMP1 INP3 input */
#define CMP1_INP2_NONE          (0x0U)                    /*!< No input voltage to CMP1 INP2 */
#define CMP1_INP2_PGA1          (CMP_VISR_P2SL_0)         /*!< Select PGA1 as CMP1 INP2 input */
#define CMP1_INP2_PGA2          (CMP_VISR_P2SL_1)         /*!< Select PGA2 as CMP1 INP2 input */
#define CMP1_INP2_CMP1_INP2     (CMP_VISR_P2SL_2)         /*!< Select CMP1_INP2 as CMP1 INP2 input */
#define CMP3_INP3_NONE          (0x0U)                    /*!< No input voltage to CMP3 INP3 */
#define CMP3_INP3_CMP3_INP3     (CMP_VISR_P3SL_0)         /*!< Select CMP3_INP3 as CMP3 INP3 input */
#define CMP3_INP3_CMP4_INP3     (CMP_VISR_P3SL_1)         /*!< Select CMP4_INP3 as CMP3 INP3 input */
#define CMP3_INP2_NONE          (0x0U)                    /*!< No input voltage to CMP3 INP2 */
#define CMP3_INP2_PGA3          (CMP_VISR_P2SL_0)         /*!< Select PGA3 as CMP3 INP2 input */
#define CMP3_INP2_PGA4          (CMP_VISR_P2SL_1)         /*!< Select PGA4 as CMP3 INP2 input */
#define CMP3_INP2_CMP3_INP2     (CMP_VISR_P2SL_2)         /*!< Select CMP3_INP2 as CMp3 INP2 input */
/**
 * @}
 */

/** @defgroup CMP_Out_Polarity_Select CMP output polarity selection
  * @{
  */
#define CMP_OUT_REVERSE_OFF     (0x0U)                    /*!< CMP output don't reverse */
#define CMP_OUT_REVERSE_ON      (CMP_OCR_COPS)            /*!< CMP output level reverse */
/**
 * @}
 */

/** @defgroup CMP_Out_Detect_Edge CMP output detect edge selection
  * @{
  */
#define CMP_DETECT_EDGS_NONE      (0U)                       /*!< Do not detect edge */
#define CMP_DETECT_EDGS_RISING    (1U << CMP_FIR_EDGS_POS)   /*!< Detect rising edge */
#define CMP_DETECT_EDGS_FALLING   (2U << CMP_FIR_EDGS_POS)   /*!< Detect falling edge */
#define CMP_DETECT_EDGS_BOTH      (3U << CMP_FIR_EDGS_POS)   /*!< Detect rising and falling edges */
/**
 * @}
 */

/** @defgroup CMP_Out_Filter CMP output filter configuration
  * @{
  */
#define CMP_OUT_FILTER_NONE         (0U)                  /*!< Do not filter */
#define CMP_OUT_FILTER_PCLK3        (1U)                  /*!< Use pclk3 */
#define CMP_OUT_FILTER_PCLK3_DIV8   (2U)                  /*!< Use pclk3/8 */
#define CMP_OUT_FILTER_PCLK3_DIV32  (3U)                  /*!< Use pclk3/32 */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_func CMP timer window function configuration
  * @{
  */
#define CMP_TIMERWIN_OFF            (0x0U)                /*!< Disable Timer Window function */
#define CMP_TIMERWIN_ON             (CMP_OCR_TWOE)        /*!< Enable Timer Window function */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Select CMP output timer window function control signal definition for CMP
  * @{
  */
#define CMP_1_TIMERWIN_TIMA_1_PWM1    (CMP_TWSR_CTWS0)  /*!< Selection TIMA_1_PWM1 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_3_PWM1    (CMP_TWSR_CTWS0)  /*!< Selection TIMA_3_PWM1 as timer window signal for CMP2*/
#define CMP_3_TIMERWIN_TIMA_1_PWM1    (CMP_TWSR_CTWS0)  /*!< Selection TIMA_1_PWM1 as timer window signal for CMP3*/
#define CMP_4_TIMERWIN_TIMA_2_PWM1    (CMP_TWSR_CTWS0)  /*!< Selection TIMA_2_PWM1 as timer window signal for CMP4*/

#define CMP_1_TIMERWIN_TIMA_1_PWM2    (CMP_TWSR_CTWS1)  /*!< Selection TIMA_1_PWM2 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_3_PWM2    (CMP_TWSR_CTWS1)  /*!< Selection TIMA_3_PWM2 as timer window signal for CMP2*/
#define CMP_3_TIMERWIN_TIMA_1_PWM2    (CMP_TWSR_CTWS1)  /*!< Selection TIMA_1_PWM2 as timer window signal for CMP3*/
#define CMP_4_TIMERWIN_TIMA_2_PWM2    (CMP_TWSR_CTWS1)  /*!< Selection TIMA_2_PWM2 as timer window signal for CMP4*/

#define CMP_1_TIMERWIN_TIMA_1_PWM3    (CMP_TWSR_CTWS2)  /*!< Selection TIMA_1_PWM3 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_3_PWM3    (CMP_TWSR_CTWS2)  /*!< Selection TIMA_3_PWM3 as timer window signal for CMP2*/
#define CMP_3_TIMERWIN_TIMA_1_PWM3    (CMP_TWSR_CTWS2)  /*!< Selection TIMA_1_PWM3 as timer window signal for CMP3*/
#define CMP_4_TIMERWIN_TIMA_2_PWM3    (CMP_TWSR_CTWS2)  /*!< Selection TIMA_2_PWM3 as timer window signal for CMP3*/

#define CMP_1_TIMERWIN_TIMA_2_PWM1    (CMP_TWSR_CTWS3)  /*!< Selection TIMA_2_PWM1 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_4_PWM1    (CMP_TWSR_CTWS3)  /*!< Selection TIMA_4_PWM1 as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIMA_3_PWM1    (CMP_TWSR_CTWS3)  /*!< Selection TIMA_3_PWM1 as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIMA_4_PWM1    (CMP_TWSR_CTWS3)  /*!< Selection TIMA_4_PWM1 as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIMA_2_PWM2    (CMP_TWSR_CTWS4)  /*!< Selection TIMA_2_PWM2 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_4_PWM2    (CMP_TWSR_CTWS4)  /*!< Selection TIMA_4_PWM2 as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIMA_3_PWM2    (CMP_TWSR_CTWS4)  /*!< Selection TIMA_3_PWM2 as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIMA_4_PWM2    (CMP_TWSR_CTWS4)  /*!< Selection TIMA_4_PWM2 as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIMA_2_PWM3    (CMP_TWSR_CTWS5)  /*!< Selection TIMA_2_PWM3 as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIMA_4_PWM3    (CMP_TWSR_CTWS5)  /*!< Selection TIMA_4_PWM3 as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIMA_3_PWM3    (CMP_TWSR_CTWS5)  /*!< Selection TIMA_3_PWM3 as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIMA_4_PWM3    (CMP_TWSR_CTWS5)  /*!< Selection TIMA_4_PWM3 as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM6_1_PWMA    (CMP_TWSR_CTWS6)  /*!< Selection TIM6_1_PWMA as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM6_5_PWMA    (CMP_TWSR_CTWS6)  /*!< Selection TIM6_5_PWMA as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM6_1_PWMB    (CMP_TWSR_CTWS6)  /*!< Selection TIM6_1_PWMB as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM6_5_PWMB    (CMP_TWSR_CTWS6)  /*!< Selection TIM6_5_PWMB as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM6_2_PWMA    (CMP_TWSR_CTWS7)  /*!< Selection TIM6_2_PWMA as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM6_6_PWMA    (CMP_TWSR_CTWS7)  /*!< Selection TIM6_6_PWMA as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM6_2_PWMB    (CMP_TWSR_CTWS7)  /*!< Selection TIM6_2_PWMB as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM6_6_PWMB    (CMP_TWSR_CTWS7)  /*!< Selection TIM6_6_PWMB as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM6_3_PWMA    (CMP_TWSR_CTWS8)  /*!< Selection TIM6_3_PWMA as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM6_7_PWMA    (CMP_TWSR_CTWS8)  /*!< Selection TIM6_7_PWMA as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM6_3_PWMB    (CMP_TWSR_CTWS8)  /*!< Selection TIM6_3_PWMB as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM6_7_PWMB    (CMP_TWSR_CTWS8)  /*!< Selection TIM6_7_PWMB as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM6_4_PWMA    (CMP_TWSR_CTWS9)  /*!< Selection TIM6_4_PWMA as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM6_8_PWMA    (CMP_TWSR_CTWS9)  /*!< Selection TIM6_8_PWMA as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM6_4_PWMB    (CMP_TWSR_CTWS9)  /*!< Selection TIM6_4_PWMB as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM6_8_PWMB    (CMP_TWSR_CTWS9)  /*!< Selection TIM6_8_PWMB as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OUH    (CMP_TWSR_CTWS10)  /*!< Selection TIM4_1_OUH as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OUH    (CMP_TWSR_CTWS10)  /*!< Selection TIM4_2_OUH as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OUH    (CMP_TWSR_CTWS10)  /*!< Selection TIM4_3_OUH as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OUH    (CMP_TWSR_CTWS10)  /*!< Selection TIM4_4_OUH as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OUL    (CMP_TWSR_CTWS11)  /*!< Selection TIM4_1_OUL as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OUL    (CMP_TWSR_CTWS11)  /*!< Selection TIM4_2_OUL as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OUL    (CMP_TWSR_CTWS11)  /*!< Selection TIM4_3_OUL as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OUL    (CMP_TWSR_CTWS11)  /*!< Selection TIM4_4_OUL as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OVH    (CMP_TWSR_CTWS12)  /*!< Selection TIM4_1_OVH as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OVH    (CMP_TWSR_CTWS12)  /*!< Selection TIM4_2_OVH as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OVH    (CMP_TWSR_CTWS12)  /*!< Selection TIM4_3_OVH as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OVH    (CMP_TWSR_CTWS12)  /*!< Selection TIM4_4_OVH as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OVL    (CMP_TWSR_CTWS13)  /*!< Selection TIM4_1_OVL as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OVL    (CMP_TWSR_CTWS13)  /*!< Selection TIM4_2_OVL as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OVL    (CMP_TWSR_CTWS13)  /*!< Selection TIM4_3_OVL as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OVL    (CMP_TWSR_CTWS13)  /*!< Selection TIM4_4_OVL as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OWH    (CMP_TWSR_CTWS14)  /*!< Selection TIM4_1_OWH as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OWH    (CMP_TWSR_CTWS14)  /*!< Selection TIM4_2_OWH as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OWH    (CMP_TWSR_CTWS14)  /*!< Selection TIM4_3_OWH as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OWH    (CMP_TWSR_CTWS14)  /*!< Selection TIM4_4_OWH as timer window signal for CMP4 */

#define CMP_1_TIMERWIN_TIM4_1_OWL    (CMP_TWSR_CTWS15)  /*!< Selection TIM4_1_OWL as timer window signal for CMP1 */
#define CMP_2_TIMERWIN_TIM4_2_OWL    (CMP_TWSR_CTWS15)  /*!< Selection TIM4_2_OWL as timer window signal for CMP2 */
#define CMP_3_TIMERWIN_TIM4_3_OWL    (CMP_TWSR_CTWS15)  /*!< Selection TIM4_3_OWL as timer window signal for CMP3 */
#define CMP_4_TIMERWIN_TIM4_3_OWL    (CMP_TWSR_CTWS15)  /*!< Selection TIM4_4_OWL as timer window signal for CMP4 */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Invalid_Level CMP output level when timer window invalid
  * @{
  */
#define CMP_TIMERWIN_INVALID_LEVEL_LOW   (0x0U)            /*!< Output Low when timer window invalid */
#define CMP_TIMERWIN_INVALID_LEVEL_HIGH  (CMP_OCR_TWOL)    /*!< Output High when timer window invalid */
/**
 * @}
 */

/** @defgroup CMP_TimerWin_output_Level CMP output level in timer windows mode
  * @{
  */
#define CMP_TIMERWIN_OUT_LEVEL_LOW       (0U)              /*!< Output Low in timer windows mode */
#define CMP_TIMERWIN_OUT_LEVEL_HIGH      (1U)              /*!< Output High in timer windows mode */
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
en_result_t CMP_StructInit(stc_cmp_init_t *pstcCMP_InitStruct);
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                               const stc_cmp_init_t *pstcCmpInit);
en_result_t CMP_WindowModeInit(const M4_CMP_TypeDef *CMPx,
                               const stc_cmp_init_t *pstcCmpInit,
                               const stc_cmp_win_ref_t *pstcCmpWinRef);
en_result_t CMP_TimerWindowConfig(M4_CMP_TypeDef *CMPx,
                                  const stc_cmp_timerwindow_t *pstcCMP_TimerWinStruct);

void CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus);
void CMP_SetOutDetectEdges(M4_CMP_TypeDef *CMPx, uint8_t u8CmpEdges);
void CMP_SetOutputFilter(M4_CMP_TypeDef *CMPx, uint8_t u8CmpFilter);
void CMP_SetOutputPolarity(M4_CMP_TypeDef *CMPx, uint8_t u8CmpPolarity);
void CMP_SetCompareVol(M4_CMP_TypeDef *CMPx, uint8_t u8CmpCh, uint8_t u8CmpVol);
void CMP_SetRefVol(M4_CMP_TypeDef *CMPx, uint8_t u8RefVol);
void CMP_DeInit(M4_CMP_TypeDef *CMPx);
void CMP_SetTimerWinSignal(M4_CMP_TypeDef *CMPx,          \
                            uint16_t u16TWSignal, en_functional_state_t enNewStatus);
en_flag_status_t CMP_GetResult(const M4_CMP_TypeDef *CMPx);
/**
 * @}
 */

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_CMP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

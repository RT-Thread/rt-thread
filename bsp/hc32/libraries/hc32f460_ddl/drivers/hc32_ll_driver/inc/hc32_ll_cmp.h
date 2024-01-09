/**
 *******************************************************************************
 * @file  hc32_ll_cmp.h
 * @brief This file contains all the functions prototypes of the CMP driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify macro define for API
   2023-01-15       CDT             Code refine for scan function
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
 * @defgroup CMP_Positive_Input_Select CMP Positive(Compare) Voltage Input
 * @{
 */
#define CMP_POSITIVE_NONE           (0x0U)
/* Note:
   Normal mode:
        1) Select one positive input from the following values.
   Scan mode:
        2) Select any combination of the following values, but the XXX_PGAO/ XXX_PGAO_BP/ XXX_CMP1_INP4/ XXX_CMP3_INP4
           should not be valid at the same time.
*/
/* CMP1 */
#define CMP1_POSITIVE_CMP1_INP1     (CMP_VLTSEL_CVSL_0)       /*!< Pin CMP1_INP1 */
#define CMP1_POSITIVE_CMP1_INP2     (CMP_VLTSEL_CVSL_1)       /*!< Pin CMP1_INP2 */
#define CMP1_POSITIVE_CMP1_INP3     (CMP_VLTSEL_CVSL_2)       /*!< Pin CMP1_INP3 */
#define CMP1_POSITIVE_PGAO          (CMP_VLTSEL_CVSL_3 | CMP_VLTSEL_C4SL_0) /*!< Internal voltage PGAO */
#define CMP1_POSITIVE_PGAO_BP       (CMP_VLTSEL_CVSL_3 | CMP_VLTSEL_C4SL_1) /*!< Internal voltage PGAO_BP */
#define CMP1_POSITIVE_CMP1_INP4     (CMP_VLTSEL_CVSL_3 | CMP_VLTSEL_C4SL_2) /*!< Pin CMP1_INP4 */
/* CMP2 */
#define CMP2_POSITIVE_CMP2_INP1     (CMP_VLTSEL_CVSL_0)       /*!< Pin CMP2_INP1 */
#define CMP2_POSITIVE_CMP2_INP2     (CMP_VLTSEL_CVSL_1)       /*!< Pin CMP2_INP2 */
#define CMP2_POSITIVE_CMP2_INP3     (CMP_VLTSEL_CVSL_2)       /*!< Pin CMP2_INP3 */
#define CMP2_POSITIVE_PGAO          (CMP_VLTSEL_CVSL_3 | CMP_VLTSEL_C4SL_0) /*!< Internal voltage PGAO */
#define CMP2_POSITIVE_PGAO_BP       (CMP_VLTSEL_CVSL_3 | CMP_VLTSEL_C4SL_1) /*!< Internal voltage PGAO_BP */
/* CMP3 */
#define CMP3_POSITIVE_CMP3_INP1     (CMP_VLTSEL_CVSL_0)       /*!< Pin CMP3_INP1 */
#define CMP3_POSITIVE_CMP3_INP2     (CMP_VLTSEL_CVSL_1)       /*!< Pin CMP3_INP2 */
#define CMP3_POSITIVE_CMP3_INP3     (CMP_VLTSEL_CVSL_2)       /*!< Pin CMP3_INP3 */
#define CMP3_POSITIVE_CMP3_INP4     (CMP_VLTSEL_CVSL_3)       /*!< Pin CMP3_INP4 */
/**
 * @}
 */

/**
 * @defgroup CMP_Scan_Inp_Status CMP Scan Function Positive In INP Source
 * @{
 */
#define CMP_SCAN_STAT_INP_NONE      (0U)
#define CMP_SCAN_STAT_INP1          (1U << CMP_OUTMON_CVST_POS)
#define CMP_SCAN_STAT_INP2          (2U << CMP_OUTMON_CVST_POS)
#define CMP_SCAN_STAT_INP3          (4U << CMP_OUTMON_CVST_POS)
#define CMP_SCAN_STAT_INP4          (8U << CMP_OUTMON_CVST_POS)
/**
 * @}
 */

/**
 * @defgroup CMP_Negative_Input_Select CMP Negative(Reference) Voltage Input
 * @{
 */
#define CMP_NEGATIVE_NONE           (0x0U)
/* Negative input select table
        CMP1            CMP2            CMP3
----------------------------------------------------
INM1    CMP1_INM1       CMP2_INM1       CMP3_INM1
INM2    CMP1_INM2       CMP2_INM2       CMP3_INM2
INM3    DAC1            DAC2            DAC1
INM4    VREF            VREF            DAC2
*/
#define CMP_NEGATIVE_INM1           (1U << CMP_VLTSEL_RVSL_POS)
#define CMP_NEGATIVE_INM2           (2U << CMP_VLTSEL_RVSL_POS)
#define CMP_NEGATIVE_INM3           (4U << CMP_VLTSEL_RVSL_POS)
#define CMP_NEGATIVE_INM4           (8U << CMP_VLTSEL_RVSL_POS)
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Polarity_Select CMP Output Polarity
 * @{
 */
#define CMP_OUT_INVT_OFF            (0x0U)                    /*!< CMP output don't reverse */
#define CMP_OUT_INVT_ON             (CMP_CTRL_INV)            /*!< CMP output level reverse */
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Detect_Edge_Select CMP Output Detect Edge
 * @{
 */
#define CMP_DETECT_EDGS_NONE        (0U)                       /*!< Do not detect edge */
#define CMP_DETECT_EDGS_RISING      (1U << CMP_CTRL_EDGSL_POS) /*!< Detect rising edge */
#define CMP_DETECT_EDGS_FALLING     (2U << CMP_CTRL_EDGSL_POS) /*!< Detect falling edge */
#define CMP_DETECT_EDGS_BOTH        (3U << CMP_CTRL_EDGSL_POS) /*!< Detect rising and falling edges */
/**
 * @}
 */

/**
 * @defgroup CMP_Out_Filter CMP Output Filter Configuration
 * @{
 */
#define CMP_OUT_FILTER_NONE         (0U)                       /*!< Do not filter */
#define CMP_OUT_FILTER_CLK          (1U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV2     (2U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV4     (3U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV8     (4U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV16    (5U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV32    (6U << CMP_CTRL_FLTSL_POS)
#define CMP_OUT_FILTER_CLK_DIV64    (7U << CMP_CTRL_FLTSL_POS)
/**
 * @}
 */

/**
 * @defgroup CMP_8BitDAC_Adc_Ref_Switch CMP 8 bit DAC ADC Reference Voltage Switch
 * @{
 */
#define CMP_ADC_REF_VREF            (CMPCR_RVADC_VREFSW)
#define CMP_ADC_REF_DA2             (CMPCR_RVADC_DA2SW)
#define CMP_ADC_REF_DA1             (CMPCR_RVADC_DA1SW)
/**
 * @}
 */

/**
 * @defgroup CMP_8Bit_Dac_Ch CMP 8 bit DAC Channel
 * @{
 */
#define CMP_8BITDAC_CH1             (CMPCR_DACR_DA1EN)
#define CMP_8BITDAC_CH2             (CMPCR_DACR_DA2EN)
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

uint32_t CMP_GetScanInpSrc(CM_CMP_TypeDef *CMPx);
int32_t CMP_ScanTimeConfig(CM_CMP_TypeDef *CMPx, uint16_t u16Stable, uint16_t u16Period);
void CMP_ScanCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState);

void CMP_8BitDAC_Cmd(uint8_t u8Ch, en_functional_state_t enNewState);
void CMP_8BitDAC_AdcRefCmd(uint16_t u16AdcRefSw, en_functional_state_t enNewState);

void CMP_8BitDAC_WriteData(uint8_t u8Ch, uint16_t u16DACData);

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

/**
 *******************************************************************************
 * @file  hc32_ll_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_cmp.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_CMP CMP
 * @brief CMP Driver Library
 * @{
 */

#if (LL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CMP_Local_Macros CMP Local Macros
 * @{
 */

/**
 * @defgroup CMP_Check_Parameters_Validity CMP Check Parameters Validity
 * @{
 */
#define IS_CMP_UNIT(x)                                                         \
(   ((x) == CM_CMP1)                            ||                             \
    ((x) == CM_CMP2)                            ||                             \
    ((x) == CM_CMP3)                            ||                             \
    ((x) == CM_CMP4))

#define IS_CMP_WIN_MD_UNIT(x)                                                  \
(   ((x) == CMP_WIN_CMP12)                      ||                             \
    ((x) == CMP_WIN_CMP34))

#define IS_CMP1_3_POSITIVE_IN(x)                                               \
(   ((x) == CMP_POSITIVE_NONE)                  ||                             \
    ((x) == CMP1_POSITIVE_PGA1_BP)              ||                             \
    ((x) == CMP1_POSITIVE_PGA1)                 ||                             \
    ((x) == CMP1_POSITIVE_PGA2)                 ||                             \
    ((x) == CMP1_POSITIVE_CMP1_INP2)            ||                             \
    ((x) == CMP1_POSITIVE_CMP1_INP3)            ||                             \
    ((x) == CMP1_POSITIVE_CMP2_INP3)            ||                             \
    ((x) == CMP1_POSITIVE_CMP1_INP4))

#define IS_CMP2_4_POSITIVE_IN(x)                                               \
(   ((x) == CMP_POSITIVE_NONE)                  ||                             \
    ((x) == CMP2_POSITIVE_PGA2_BP)              ||                             \
    ((x) == CMP2_POSITIVE_PGA2)                 ||                             \
    ((x) == CMP2_POSITIVE_CMP2_INP3)            ||                             \
    ((x) == CMP2_POSITIVE_CMP2_INP4))

#define IS_CMP_NEGATIVE_IN(x)                                                  \
(   ((x) == CMP_NEGATIVE_NONE)                  ||                             \
    ((x) == CMP1_NEGATIVE_DAC1_OUT1)            ||                             \
    ((x) == CMP1_NEGATIVE_DAC1_OUT2)            ||                             \
    ((x) == CMP1_NEGATIVE_CMP123_INM3)          ||                             \
    ((x) == CMP1_NEGATIVE_CMP1_INM4))

#define IS_CMP_WIN_LOW_IN(x)                                                   \
(   ((x) == CMP_WIN_LOW_NONE)                   ||                             \
    ((x) == CMP12_WIN_LOW_DAC1_OUT1)            ||                             \
    ((x) == CMP12_WIN_LOW_DAC1_OUT2)            ||                             \
    ((x) == CMP12_WIN_LOW_CMP123_INM3)          ||                             \
    ((x) == CMP12_WIN_LOW_CMP1_INM4))

#define IS_CMP_WIN_HIGH_IN(x)                                                  \
(   ((x) == CMP_WIN_HIGH_NONE)                  ||                             \
    ((x) == CMP12_WIN_HIGH_DAC1_OUT1)           ||                             \
    ((x) == CMP12_WIN_HIGH_DAC1_OUT2)           ||                             \
    ((x) == CMP12_WIN_HIGH_CMP123_INM3)         ||                             \
    ((x) == CMP12_WIN_HIGH_CMP2_INM4))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   ((x) == CMP_OUT_INVT_OFF)                   ||                             \
    ((x) == CMP_OUT_INVT_ON))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   ((x) == CMP_OUT_FILTER_NONE)                ||                             \
    ((x) == CMP_OUT_FILTER_CLK)                 ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV8)            ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV32))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   ((x) == CMP_DETECT_EDGS_NONE)               ||                             \
    ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

#define IS_CMP_BLANKWIN_VALID_LVL(x)                                           \
(   ((x) == CMP_BLANKWIN_VALID_LVL_LOW)         ||                             \
    ((x) == CMP_BLANKWIN_VALID_LVL_HIGH))

#define IS_CMP_BLANKWIN_OUT_LVL(x)                                             \
(   ((x) == CMP_BLANKWIN_OUTPUT_LVL_LOW)        ||                             \
    ((x) == CMP_BLANKWIN_OUTPUT_LVL_HIGH))

/**
 * @}
 */
/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CMP_Local_Functions CMP Local Functions
 * @{
 */

/**
 * @brief Delay function, delay us approximately
 * @param [in] u32Count                   us
 * @retval None
 */
static void CMP_DelayUS(uint32_t u32Count)
{
    __IO uint32_t i;
    const uint32_t u32Cyc = HCLK_VALUE / 10000000UL;

    while (u32Count-- > 0UL) {
        i = u32Cyc;
        while (i-- > 0UL) {
            ;
        }
    }
}

/**
 * @brief  Get CMP function status and disable CMP
 * @param  [in] CMPx            Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval uint16_t             The register value
 */
static uint16_t GetCmpFuncStatusAndDisFunc(CM_CMP_TypeDef *CMPx)
{
    uint16_t u16temp;
    /* Read CMP status */
    u16temp = (uint16_t)(uint8_t)READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    return u16temp;
}

/**
 * @brief  Revcover CMP function status
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16CmpFuncStatus    CMP function status backup value
 * @retval None
 */
static void RecoverCmpFuncStatus(CM_CMP_TypeDef *CMPx, uint16_t u16CmpFuncStatus)
{
    if (u16CmpFuncStatus != 0U) {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u16CmpFuncStatus);
        /* Delay 1us */
        CMP_DelayUS(1U);
    }
}

/**
 * @}
 */

/**
 * @defgroup CMP_Global_Functions CMP Global Functions
 * @{
 */

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [in] pstcCmpInit         Pointer to a structure variable which will be initialized. @ref stc_cmp_init_t
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t CMP_StructInit(stc_cmp_init_t *pstcCmpInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (pstcCmpInit != NULL) {
        pstcCmpInit->u16PositiveInput = CMP_POSITIVE_NONE;
        pstcCmpInit->u16NegativeInput = CMP_NEGATIVE_NONE;
        pstcCmpInit->u16OutPolarity = CMP_OUT_INVT_OFF;
        pstcCmpInit->u16OutDetectEdge = CMP_DETECT_EDGS_NONE;
        pstcCmpInit->u16OutFilter = CMP_OUT_FILTER_NONE;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [in] pstcCmpWindowInit   Pointer to a structure variable. @ref stc_cmp_window_init_t
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t CMP_WindowStructInit(stc_cmp_window_init_t *pstcCmpWindowInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (pstcCmpWindowInit != NULL) {
        pstcCmpWindowInit->u8WinVolLow = CMP_NEGATIVE_NONE;
        pstcCmpWindowInit->u8WinVolHigh = CMP_NEGATIVE_NONE;
        pstcCmpWindowInit->u16OutPolarity = CMP_OUT_INVT_OFF;
        pstcCmpWindowInit->u16OutDetectEdge = CMP_DETECT_EDGS_NONE;
        pstcCmpWindowInit->u16OutFilter = CMP_OUT_FILTER_NONE;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  De-initialize CMP unit
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval None
 */
void CMP_DeInit(CM_CMP_TypeDef *CMPx)
{
    DDL_ASSERT(IS_CMP_UNIT(CMPx));

    CLR_REG8(CMPx->MDR);
    CLR_REG8(CMPx->FIR);
    CLR_REG8(CMPx->OCR);
    CLR_REG8(CMPx->PMSR);
    CLR_REG16(CMPx->VISR);
    CLR_REG16(CMPx->TWSR);
    CLR_REG16(CMPx->TWPR);
}

/**
 * @brief  CMP normal mode initialize
 * @param  [in] CMPx                        Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] pstcCmpInit                 CMP function base parameter structure
 *   @arg  pstcCmpInit->u16PositiveInput:   @ref CMP_Positive_Input_Select
 *   @arg  pstcCmpInit->u16NegativeInput:   @ref CMP_Negative_Input_Select
 *   @arg  pstcCmpInit->u16OutPolarity:     @ref CMP_Out_Polarity_Select
 *   @arg  pstcCmpInit->u16OutDetectEdge:   @ref CMP_Out_Detect_Edge_Select
 *   @arg  pstcCmpInit->u16OutFilter:       @ref CMP_Out_Filter
 * @retval int32_t
 *         - LL_OK:                         Success
 *         - LL_ERR_INVD_PARAM:             Parameter error
 */
int32_t CMP_NormalModeInit(CM_CMP_TypeDef *CMPx, const stc_cmp_init_t *pstcCmpInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check CMPx instance and configuration structure*/
    if (NULL != pstcCmpInit) {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpInit->u16OutPolarity));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpInit->u16OutDetectEdge));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpInit->u16OutFilter));
        if ((CM_CMP1 == CMPx) || (CM_CMP3 == CMPx)) {
            DDL_ASSERT(IS_CMP1_3_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        } else {
            DDL_ASSERT(IS_CMP2_4_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        }
        DDL_ASSERT(IS_CMP_NEGATIVE_IN(pstcCmpInit->u16NegativeInput));

        /* Stop CMP compare */
        CLR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);

        /* Set voltage in */
        WRITE_REG8(CMPx->PMSR, (pstcCmpInit->u16PositiveInput & CMP_PMSR_CVSL) | pstcCmpInit->u16NegativeInput);
        if ((CM_CMP1 == CMPx) || (CM_CMP3 == CMPx)) {
            if ((CMP_PMSR_CVSL_1 == (pstcCmpInit->u16PositiveInput & CMP_PMSR_CVSL)) \
                    || (CMP_PMSR_CVSL_2 == (pstcCmpInit->u16PositiveInput & CMP_PMSR_CVSL))) {
                WRITE_REG16(CMPx->VISR, (pstcCmpInit->u16PositiveInput >> VISR_OFFSET) & (CMP_VISR_P3SL | CMP_VISR_P2SL));
            }
        }

        /* Delay 1us*/
        CMP_DelayUS(1U);
        /* Start CMP compare */
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 1us*/
        CMP_DelayUS(1U);
        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(CMPx->FIR, (pstcCmpInit->u16OutFilter | pstcCmpInit->u16OutDetectEdge));
        WRITE_REG8(CMPx->OCR, pstcCmpInit->u16OutPolarity);
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Voltage compare function command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_FuncCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 1us*/
        CMP_DelayUS(1U);
    } else {
        CLR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    }

}

/**
 * @brief  Voltage compare interrupt function command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_IntCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    } else {
        CLR_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
}

/**
 * @brief  Voltage compare output command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_CompareOutCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    } else {
        CLR_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }

}

/**
 * @brief  Voltage compare output port VCOUT function command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_PinVcoutCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    } else {
        CLR_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }

}

/**
 * @brief  Voltage compare result flag read
 * @param  [in] CMPx            Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval An @ref en_flag_status_t enumeration type value.
 *         In normal mode
 *         - RESET:             compare voltage < reference voltage
 *         - SET:               compare voltage > reference voltage
 *         In Window mode
 *         - RESET:             compare voltage < reference low voltage or compare voltage > reference high voltage
 *         - SET:               reference low voltage < compare voltage < reference high voltage
 */
en_flag_status_t CMP_GetStatus(const CM_CMP_TypeDef *CMPx)
{
    en_flag_status_t i32Ret;
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    i32Ret = (READ_REG8_BIT(CMPx->MDR, CMP_MDR_CMON) != 0U) ? SET : RESET;
    return i32Ret;
}

/**
 * @brief  Set output detect edge
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u8CmpEdges          CMP output detect edge selection. @ref CMP_Out_Detect_Edge_Select
 * @retval None
 */
void CMP_SetOutDetectEdge(CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges)
{
    uint16_t u16temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(u8CmpEdges));
    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* CMP output detect edge selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_EDGS, u8CmpEdges);
    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  Set output filter
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u8CmpFilter         CMP output filter selection. @ref CMP_Out_Filter
 * @retval None
 */
void CMP_SetOutFilter(CM_CMP_TypeDef *CMPx, uint8_t u8CmpFilter)
{
    uint16_t u16temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_FILTER(u8CmpFilter));
    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);
    /* CMP output filter selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_FCKS, u8CmpFilter);
    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  Set output polarity
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16CmpPolarity      CMP output polarity selection. @ref CMP_Out_Polarity_Select
 * @retval None
 */
void CMP_SetOutPolarity(CM_CMP_TypeDef *CMPx, uint16_t u16CmpPolarity)
{
    uint16_t u16temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_POLARITY(u16CmpPolarity));
    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* CMP output polarity selection */
    MODIFY_REG8(CMPx->OCR, CMP_OCR_COPS, u16CmpPolarity);
    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  Set positive in(compare voltage)
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16PositiveInput    @ref CMP_Positive_Input_Select
 * @retval None
 */
void CMP_SetPositiveInput(CM_CMP_TypeDef *CMPx, uint16_t u16PositiveInput)
{
    uint16_t u16temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    if ((CM_CMP1 == CMPx) || (CM_CMP3 == CMPx)) {
        DDL_ASSERT(IS_CMP1_3_POSITIVE_IN(u16PositiveInput));
    } else {
        DDL_ASSERT(IS_CMP2_4_POSITIVE_IN(u16PositiveInput));
    }

    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* Set voltage in */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_CVSL, (u16PositiveInput & CMP_PMSR_CVSL));
    if ((CM_CMP1 == CMPx) || (CM_CMP3 == CMPx)) {
        if ((CMP_PMSR_CVSL_1 == (u16PositiveInput & CMP_PMSR_CVSL)) || (CMP_PMSR_CVSL_2 == (u16PositiveInput & CMP_PMSR_CVSL))) {
            MODIFY_REG16(CMPx->VISR, (CMP_VISR_P3SL | CMP_VISR_P2SL), (u16PositiveInput >> VISR_OFFSET));
        }
    }

    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  Set negative in(reference voltage)
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16NegativeInput    @ref CMP_Negative_Input_Select
 * @retval None
 */
void CMP_SetNegativeInput(CM_CMP_TypeDef *CMPx, uint16_t u16NegativeInput)
{
    uint16_t u16temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_NEGATIVE_IN(u16NegativeInput));
    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* Set voltage in */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_RVSL, u16NegativeInput);

    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] u8WinCMPx                        @ref CMP_Window_Mode_Unit
 * @param  [in] pstcCmpWindowInit                CMP function base parameter structure @ref stc_cmp_window_init_t
 * @retval int32_t
 *         - LL_OK:                             Success
 *         - LL_ERR_INVD_PARAM:                 Parameter error
 * @note   Window mode compare input:
 *         HC32F4A0:
 *              CMP2_INP3 valid for u16PositiveInput of CMP_WIN_CMP12
 *              CMP4_INP3 valid for u16PositiveInput of CMP_WIN_CMP34
 *         HC32M423
 *              IVCMP2_2 valid for u16PositiveInput of CMP_WIN_CMP23
 *         HC32M424
 *              IVCMP1_0 or IVCMP1_1 valid for u16PositiveInput CMP_WIN_CMP13
 *              IVCMP2_0 or IVCMP2_1 valid for u16PositiveInput CMP_WIN_CMP24
 *         HC32M120
 *              IVCMP2_0 valid for u16PositiveInput of CMP_WIN_CMP12
 */
int32_t CMP_WindowModeInit(uint8_t u8WinCMPx, const stc_cmp_window_init_t *pstcCmpWindowInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check configuration structure */
    if (NULL != pstcCmpWindowInit) {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_WIN_MD_UNIT(u8WinCMPx));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpWindowInit->u16OutPolarity));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpWindowInit->u16OutDetectEdge));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpWindowInit->u16OutFilter));
        DDL_ASSERT(IS_CMP_WIN_LOW_IN(pstcCmpWindowInit->u8WinVolLow));
        DDL_ASSERT(IS_CMP_WIN_HIGH_IN(pstcCmpWindowInit->u8WinVolHigh));

        CM_CMP_TypeDef *pCMP_MAIN;
        CM_CMP_TypeDef *pCMP_MINOR;

        if (u8WinCMPx == CMP_WIN_CMP12) {
            pCMP_MAIN = CM_CMP2;
            pCMP_MINOR = CM_CMP1;
        } else {
            pCMP_MAIN = CM_CMP4;
            pCMP_MINOR = CM_CMP3;
        }
        /* Stop CMP compare */
        CLR_REG8_BIT(pCMP_MINOR->MDR, CMP_MDR_CENB);
        CLR_REG8_BIT(pCMP_MAIN->MDR, CMP_MDR_CENB);

        /* Set positive in(compare voltage), window voltage */
        WRITE_REG8(pCMP_MINOR->PMSR, (CMP1_POSITIVE_CMP2_INP3 & CMP_PMSR_CVSL) | pstcCmpWindowInit->u8WinVolLow);
        WRITE_REG8(pCMP_MAIN->PMSR, (CMP2_POSITIVE_CMP2_INP3 & CMP_PMSR_CVSL) | pstcCmpWindowInit->u8WinVolHigh);
        WRITE_REG16(pCMP_MINOR->VISR, (CMP1_POSITIVE_CMP2_INP3 >> VISR_OFFSET) & (CMP_VISR_P3SL | CMP_VISR_P2SL));
        WRITE_REG16(pCMP_MAIN->VISR, (CMP2_POSITIVE_CMP2_INP3 >> VISR_OFFSET) & (CMP_VISR_P3SL | CMP_VISR_P2SL));
        /* Select window compare mode */
        SET_REG8_BIT(pCMP_MAIN->MDR, CMP_MDR_CWDE);
        /* Start CMP compare function */
        SET_REG8_BIT(pCMP_MINOR->MDR, CMP_MDR_CENB);
        SET_REG8_BIT(pCMP_MAIN->MDR, CMP_MDR_CENB);
        /* Delay 1us*/
        CMP_DelayUS(1U);
        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(pCMP_MAIN->FIR, pstcCmpWindowInit->u16OutFilter | pstcCmpWindowInit->u16OutDetectEdge);
        WRITE_REG8(pCMP_MAIN->OCR, pstcCmpWindowInit->u16OutPolarity);

        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Blank window function disable specified window source
 * @param  [in] CMPx                    Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16BlankWindowSrc       Blank window source.
 * @retval None
 */
void CMP_BlankWindowSrcDisable(CM_CMP_TypeDef *CMPx, uint16_t u16BlankWindowSrc)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));

    /* Set blank window valid level high */
    CLR_REG16_BIT(CMPx->TWPR, u16BlankWindowSrc);
    /* Disable blank window source  */
    CLR_REG16_BIT(CMPx->TWSR, u16BlankWindowSrc);
}

/**
 * @brief  Voltage compare blank window function configuration
 * @param  [in] CMPx                    Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] pstcBlankWindowInit     Configuration structure for blank window mode.
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t CMP_BlankWindowConfig(CM_CMP_TypeDef *CMPx, const stc_cmp_blankwindow_t *pstcBlankWindowInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check CMPx instance and configuration structure*/
    if (NULL != pstcBlankWindowInit) {
        i32Ret = LL_OK;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_BLANKWIN_VALID_LVL(pstcBlankWindowInit->u8ValidLevel));
        DDL_ASSERT(IS_CMP_BLANKWIN_OUT_LVL(pstcBlankWindowInit->u8OutLevel));

        /* Select output level when blank window valid */
        MODIFY_REG8(CMPx->OCR, CMP_OCR_TWOL, pstcBlankWindowInit->u8OutLevel);
        /* Select blank window valid level */
        if (CMP_BLANKWIN_VALID_LVL_LOW == pstcBlankWindowInit->u8ValidLevel) {
            SET_REG16_BIT(CMPx->TWPR, pstcBlankWindowInit->u16Src);
        } else {
            CLR_REG16_BIT(CMPx->TWPR, pstcBlankWindowInit->u16Src);
        }
        /* Select blank window source  */
        SET_REG16_BIT(CMPx->TWSR, pstcBlankWindowInit->u16Src);
    }
    return i32Ret;
}

/**
 * @brief  CMP out blank window function command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_BlankWindowCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
    } else {
        CLR_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
    }
}

/**
 * @}
 */

#endif  /* LL_CMP_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

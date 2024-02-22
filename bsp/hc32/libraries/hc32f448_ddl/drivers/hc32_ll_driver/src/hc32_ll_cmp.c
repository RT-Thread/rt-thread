/**
 *******************************************************************************
 * @file  hc32_ll_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-06-30       CDT             Modify typo
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

#define IS_CMP_POSITIVE_IN(x)                                                  \
(   ((x) == CMP_POSITIVE_NONE)                  ||                             \
    ((x) == CMP_POSITIVE_INP1)                  ||                             \
    ((x) == CMP_POSITIVE_INP2)                  ||                             \
    ((x) == CMP_POSITIVE_INP3)                  ||                             \
    ((x) == CMP_POSITIVE_INP4))

#define IS_CMP_NEGATIVE_IN(x)                                                  \
(   ((x) == CMP_NEGATIVE_NONE)                  ||                             \
    ((x) == CMP_NEGATIVE_INM1)                  ||                             \
    ((x) == CMP_NEGATIVE_INM2)                  ||                             \
    ((x) == CMP_NEGATIVE_INM3)                  ||                             \
    ((x) == CMP_NEGATIVE_INM4))

#define IS_CMP_WIN_LOW_IN(x)                                                   \
(   ((x) == CMP_WIN_LOW_NONE)                   ||                             \
    ((x) == CMP_WIN_LOW_INM1)                   ||                             \
    ((x) == CMP_WIN_LOW_INM2)                   ||                             \
    ((x) == CMP_WIN_LOW_INM3)                   ||                             \
    ((x) == CMP_WIN_LOW_INM4))

#define IS_CMP_WIN_HIGH_IN(x)                                                  \
(   ((x) == CMP_WIN_HIGH_NONE)                  ||                             \
    ((x) == CMP_WIN_HIGH_INM1)                  ||                             \
    ((x) == CMP_WIN_HIGH_INM2)                  ||                             \
    ((x) == CMP_WIN_HIGH_INM3)                  ||                             \
    ((x) == CMP_WIN_HIGH_INM4))

#define IS_CMP_WIN12_POSITIVE_IN(x)                                            \
(   ((x) == CMP_WIN_POSITIVE_NONE)              ||                             \
    ((x) == CMP_WIN_POSITIVE_INP4))

#define IS_CMP_WIN34_POSITIVE_IN(x)                                            \
(   ((x) == CMP_WIN_POSITIVE_NONE)              ||                             \
    ((x) == CMP_WIN_POSITIVE_INP2)              ||                             \
    ((x) == CMP_WIN_POSITIVE_INP3))

#define IS_CMP_SCAN_STABLE(x)                                                  \
(   (x) <= 0x3FU)

#define IS_CMP_SCAN_PERIOD(x)                                                  \
(   ((x) > 0x08U)                               &&                             \
    ((x) <= 0xFFU))

#define IS_CMP_SCAN_SRC(x)                                                     \
(   ((x) & (~CMP_SCCR_SISL)) == 0U)

#define IS_CMP_SCAN_MD(x)                                                      \
(   ((x) == CMP_SCAN_NONE)                      ||                             \
    ((x) == CMP_SCAN_INP)                       ||                             \
    ((x) == CMP_SCAN_INM))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   ((x) == CMP_OUT_INVT_OFF)                   ||                             \
    ((x) == CMP_OUT_INVT_ON))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   ((x) == CMP_OUT_FILTER_NONE)                ||                             \
    ((x) == CMP_OUT_FILTER_CLK)                 ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV2)            ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV4)            ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV8)            ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV16)           ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV32))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   ((x) == CMP_DETECT_EDGS_NONE)               ||                             \
    ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

#define IS_CMP_OUT_DETECT_EDGE_FLAG(x)                                         \
(   ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

#define IS_CMP_BLANKWIN_VALID_LVL(x)                                           \
(   ((x) == CMP_BLANKWIN_VALID_LVL_LOW)         ||                             \
    ((x) == CMP_BLANKWIN_VALID_LVL_HIGH))

#define IS_CMP_BLANKWIN_OUT_LVL(x)                                             \
(   ((x) == CMP_BLANKWIN_OUTPUT_LVL_LOW)        ||                             \
    ((x) == CMP_BLANKWIN_OUTPUT_LVL_HIGH)       ||                             \
    ((x) == CMP_BLANKWIN_OUTPUT_LVL_HOLD))

#define IS_CMP_BLANKWIN_MD(x)                                                  \
(   ((x) == CMP_BLANKWIN_MD_LVL)                ||                             \
    ((x) == CMP_BLANKWIN_MD_EDGE))

#define IS_CMP_BLANKWIN_EDGE(x)                                                \
(   ((x) == CMP_BLANKWIN_VALID_EDGE_NONE)       ||                             \
    ((x) == CMP_BLANKWIN_VALID_EDGE_RISING)     ||                             \
    ((x) == CMP_BLANKWIN_VALID_EDGE_FALLING)    ||                             \
    ((x) == CMP_BLANKWIN_VALID_EDGE_ALL))

#define IS_CMP_BLANKWIN_MASK_WIDTH(x)                                          \
(   (x) <= 255U)

/**
 * @}
 */

#define CMP_SCAN_PERIOD_IMME                (0x08U)

#define CMP_MDR_CENB        (CMP_MDR_CENA)
#define CMP_OCR_TWOE        (CMP_OCR_BWEN)
#define CMP_OCR_TWOL        (CMP_OCR_BWOL)

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
    /* It is possible that the interrupt may occurs after CMP status switch. */
    DDL_ASSERT(READ_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN) == 0U);

    /* Read CMP status */
    u16temp = (uint16_t)(uint8_t)READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    return u16temp;
}

/**
 * @brief  Recover CMP function status
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
 * @brief  Initialize structure stc_cmp_window_init_t variable with default value.
 * @param  [in] pstcCmpWindowInit   Pointer to a structure variable. @ref stc_cmp_window_init_t
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t CMP_WindowStructInit(stc_cmp_window_init_t *pstcCmpWindowInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (pstcCmpWindowInit != NULL) {
        pstcCmpWindowInit->u16PositiveInput = CMP_WIN_POSITIVE_NONE;
        pstcCmpWindowInit->u16WinVolLow = CMP_NEGATIVE_NONE;
        pstcCmpWindowInit->u16WinVolHigh = CMP_NEGATIVE_NONE;
        pstcCmpWindowInit->u16OutPolarity = CMP_OUT_INVT_OFF;
        pstcCmpWindowInit->u16OutDetectEdge = CMP_DETECT_EDGS_NONE;
        pstcCmpWindowInit->u16OutFilter = CMP_OUT_FILTER_NONE;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Initialize structure stc_cmp_blankwindow_t variable with default value.
 * @param  [in] pstcBlankWindowConfig   Pointer to a structure variable. @ref stc_cmp_blankwindow_t
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t CMP_BlankWindowStructInit(stc_cmp_blankwindow_t *pstcBlankWindowConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (pstcBlankWindowConfig != NULL) {
        pstcBlankWindowConfig->u8Mode = CMP_BLANKWIN_MD_LVL;
        pstcBlankWindowConfig->u16ValidLevelEdge = CMP_BLANKWIN_VALID_LVL_LOW;
        pstcBlankWindowConfig->u16MaskWidth = 0U;
        pstcBlankWindowConfig->u8OutLevel = CMP_BLANKWIN_OUTPUT_LVL_LOW;
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
    CLR_REG32(CMPx->PMSR);
    CLR_REG32(CMPx->BWSR1);
    CLR_REG16(CMPx->BWSR2);
    CLR_REG32(CMPx->SCCR);
    CLR_REG32(CMPx->SCMR);
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
        DDL_ASSERT(IS_CMP_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        DDL_ASSERT(IS_CMP_NEGATIVE_IN(pstcCmpInit->u16NegativeInput));

        /* Stop CMP compare */
        CLR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);

        /* Set voltage in */
        WRITE_REG32(CMPx->PMSR, ((uint32_t)pstcCmpInit->u16PositiveInput << CMP_PMSR_CVSL_POS) | (uint32_t)pstcCmpInit->u16NegativeInput);

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
    en_flag_status_t enRet;
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    enRet = (READ_REG8_BIT(CMPx->MDR, CMP_MDR_CMON) != 0U) ? SET : RESET;
    return enRet;
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
 * @brief  Clear output detect edge flag
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u8CmpEdges          CMP output detect edge selection.
 *   @arg  CMP_DETECT_EDGS_RISING
 *   @arg  CMP_DETECT_EDGS_FALLING
 *   @arg  CMP_DETECT_EDGS_BOTH
 * @retval None
 */
void CMP_ClearOutDetectFlag(CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE_FLAG(u8CmpEdges));
    MODIFY_REG8(CMPx->FIR, CMP_FIR_CFF | CMP_FIR_CRF, u8CmpEdges << (CMP_FIR_CFF_POS - CMP_FIR_EDGS_POS));
}

/**
 * @brief Get output detect edge flags
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u8CmpEdges          CMP output detect edge selection.
 *   @arg  CMP_DETECT_EDGS_RISING
 *   @arg  CMP_DETECT_EDGS_FALLING
 *   @arg  CMP_DETECT_EDGS_BOTH
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t CMP_GetOutDetectFlag(const CM_CMP_TypeDef *CMPx, uint8_t u8CmpEdges)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE_FLAG(u8CmpEdges));
    return ((0U != READ_REG8_BIT(CMPx->FIR, u8CmpEdges << (CMP_FIR_CFF_POS - CMP_FIR_EDGS_POS))) ? SET : RESET);
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
    DDL_ASSERT(IS_CMP_POSITIVE_IN(u16PositiveInput));

    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* Set voltage in */
    MODIFY_REG32(CMPx->PMSR, CMP_PMSR_CVSL, (uint32_t)u16PositiveInput << CMP_PMSR_CVSL_POS);

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
    MODIFY_REG32(CMPx->PMSR, CMP_PMSR_RVSL, u16NegativeInput);

    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] u8WinCMPx               @ref CMP_Window_Mode_Unit
 * @param  [in] pstcCmpWindowInit       CMP function base parameter structure @ref stc_cmp_window_init_t
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
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
        DDL_ASSERT(IS_CMP_WIN_LOW_IN(pstcCmpWindowInit->u16WinVolLow));
        DDL_ASSERT(IS_CMP_WIN_HIGH_IN(pstcCmpWindowInit->u16WinVolHigh));
        if (u8WinCMPx == CMP_WIN_CMP12) {
            DDL_ASSERT(IS_CMP_WIN12_POSITIVE_IN(pstcCmpWindowInit->u16PositiveInput));
        } else {
            DDL_ASSERT(IS_CMP_WIN34_POSITIVE_IN(pstcCmpWindowInit->u16PositiveInput));
        }

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
        WRITE_REG32(pCMP_MINOR->PMSR,
                    ((uint32_t)pstcCmpWindowInit->u16PositiveInput << CMP_PMSR_CVSL_POS)
                    | (uint32_t)pstcCmpWindowInit->u16WinVolLow);
        WRITE_REG32(pCMP_MAIN->PMSR,
                    ((uint32_t)pstcCmpWindowInit->u16PositiveInput << CMP_PMSR_CVSL_POS)
                    | (uint32_t)pstcCmpWindowInit->u16WinVolHigh);
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
 * @param  [in] u16BlankWindowSrc       Blank window source. can be any combination of @ref CMP_BlankWindow_Src
 * @retval None
 */
void CMP_BlankWindowSrcDisable(CM_CMP_TypeDef *CMPx, uint16_t u16BlankWindowSrc)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));

    /* Set blank window valid level high */
    CLR_REG32_BIT(CMPx->BWSR1, (uint32_t)u16BlankWindowSrc << CMP_BWSR1_CTWP0_POS);
    /* Disable blank window source  */
    CLR_REG32_BIT(CMPx->BWSR1, u16BlankWindowSrc);
}

/**
 * @brief  Voltage compare blank window function configuration
 * @param  [in] CMPx                    Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] pstcBlankWindowConfig   Configuration structure for blank window mode.
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t CMP_BlankWindowConfig(CM_CMP_TypeDef *CMPx, const stc_cmp_blankwindow_t *pstcBlankWindowConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    /* Check CMPx instance and configuration structure*/
    if (NULL != pstcBlankWindowConfig) {
        i32Ret = LL_OK;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_BLANKWIN_MD(pstcBlankWindowConfig->u8Mode));
        if (CMP_BLANKWIN_MD_LVL == pstcBlankWindowConfig->u8Mode) {
            DDL_ASSERT(IS_CMP_BLANKWIN_VALID_LVL(pstcBlankWindowConfig->u16ValidLevelEdge));
        } else {
            DDL_ASSERT(IS_CMP_BLANKWIN_EDGE(pstcBlankWindowConfig->u16ValidLevelEdge));
            DDL_ASSERT(IS_CMP_BLANKWIN_MASK_WIDTH(pstcBlankWindowConfig->u16MaskWidth));
        }
        DDL_ASSERT(IS_CMP_BLANKWIN_OUT_LVL(pstcBlankWindowConfig->u8OutLevel));

        /* Select blank window mode and output level when blank window valid */
        MODIFY_REG8(CMPx->OCR, CMP_OCR_TWOL | CMP_OCR_BWMD,
                    pstcBlankWindowConfig->u8OutLevel | pstcBlankWindowConfig->u8Mode);
        if (CMP_BLANKWIN_MD_LVL == pstcBlankWindowConfig->u8Mode) {
            /* Select blank window valid level */
            if (CMP_BLANKWIN_VALID_LVL_LOW == pstcBlankWindowConfig->u16ValidLevelEdge) {
                SET_REG32_BIT(CMPx->BWSR1, (uint32_t)pstcBlankWindowConfig->u16Src << CMP_BWSR1_CTWP0_POS);
            } else {
                CLR_REG32_BIT(CMPx->BWSR1, (uint32_t)pstcBlankWindowConfig->u16Src << CMP_BWSR1_CTWP0_POS);
            }
        } else {
            WRITE_REG16(CMPx->BWSR2,
                        pstcBlankWindowConfig->u16ValidLevelEdge | pstcBlankWindowConfig->u16MaskWidth);
        }
        /* Select blank window source  */
        SET_REG32_BIT(CMPx->BWSR1, pstcBlankWindowConfig->u16Src);
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
 * @brief  CMP blank window mode set
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u8Mode              Blank window mode @ref CMP_BlankWindow_Mode.
 * @retval None
 */
void CMP_BlankWindowMode(CM_CMP_TypeDef *CMPx, uint8_t u8Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_BLANKWIN_MD(u8Mode));
    MODIFY_REG8(CMPx->OCR, CMP_OCR_BWMD, u8Mode);
}

/**
 * @brief  Get CMP scan INP source
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval An uint32_t value @ref CMP_Scan_Inp_Status
 */
uint32_t CMP_GetScanInpSrc(CM_CMP_TypeDef *CMPx)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    return READ_REG32_BIT(CMPx->SCMR, CMP_SCMR_CVST);
}

/**
 * @brief  Get CMP scan INM source
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval An uint16_t value @ref CMP_Scan_Inm_Status
 */
uint32_t CMP_GetScanInmSrc(CM_CMP_TypeDef *CMPx)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    return READ_REG32_BIT(CMPx->SCMR, CMP_SCMR_RVST);
}

/**
 * @brief  CMP set scan input source
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16Src              INM or INP source select for scan mode, it can be any combination of member of
 *                                  @ref CMP_Scan_Inm_Inp_Src
 * @retval None
 */
void CMP_ScanSetSrc(CM_CMP_TypeDef *CMPx, uint16_t u16Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_SCAN_MD(CMPx->MDR));
    DDL_ASSERT(IS_CMP_SCAN_SRC(u16Src));

    MODIFY_REG32(CMPx->SCCR, CMP_SCCR_SISL, u16Src);
}

/**
 * @brief  CMP set scan mode
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16Mode             CMP scan mode @ref CMP_Scan_Mode
 * @retval None
 */
void CMP_ScanSetMode(CM_CMP_TypeDef *CMPx, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_SCAN_MD(u16Mode));

    MODIFY_REG8(CMPx->MDR, CMP_MDR_CSMD, u16Mode);
}

/**
 * @brief  CMP scan function configuration
 * @param  [in] CMPx                    Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] pstcCmpScanConfig       Configuration structure for scan mode.
 * @retval int32_t
 *         - LL_OK:                     Success
 *         - LL_ERR_INVD_PARAM:         Parameter error
 */
int32_t CMP_ScanConfig(CM_CMP_TypeDef *CMPx, stc_cmp_scan_config_t *pstcCmpScanConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint16_t u16Fltsl;
    uint16_t u16FltslDiv;
    /* Check instance and configuration structure*/
    if (NULL != pstcCmpScanConfig) {
        i32Ret = LL_OK;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_UNIT(CMPx));
        DDL_ASSERT(IS_CMP_SCAN_MD(pstcCmpScanConfig->u16Mode));
        DDL_ASSERT(IS_CMP_SCAN_STABLE(pstcCmpScanConfig->u16Stable));
        DDL_ASSERT(IS_CMP_SCAN_PERIOD(pstcCmpScanConfig->u16Period));
        DDL_ASSERT(IS_CMP_SCAN_SRC(pstcCmpScanConfig->u16Src));

        u16Fltsl = READ_REG16_BIT(CMPx->FIR, CMP_FIR_FCKS);
        if (0U != u16Fltsl) {
            u16FltslDiv = ((uint16_t)1U << (u16Fltsl - 1U));
        } else {
            u16FltslDiv = 0U;
        }
        if (pstcCmpScanConfig->u16Period <= (pstcCmpScanConfig->u16Stable + u16FltslDiv * 4U + CMP_SCAN_PERIOD_IMME)) {
            i32Ret = LL_ERR_INVD_PARAM;
        } else {
            MODIFY_REG32(CMPx->SCCR, CMP_SCCR_SSTB | CMP_SCCR_SPRD | CMP_SCCR_SISL,
                         ((uint32_t)pstcCmpScanConfig->u16Stable << CMP_SCCR_SSTB_POS) |
                         ((uint32_t)pstcCmpScanConfig->u16Period << CMP_SCCR_SPRD_POS) |
                         pstcCmpScanConfig->u16Src);
            MODIFY_REG8(CMPx->MDR, CMP_MDR_CSMD, pstcCmpScanConfig->u16Mode);
        }
    }
    return i32Ret;
}

/**
 * @brief  Initialize structure stc_cmp_scan_config_t variable with default value.
 * @param  [in] pstcCmpScanConfig   Pointer to a structure variable. @ref stc_cmp_scan_config_t
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Parameter error
 */
int32_t CMP_ScanStructInit(stc_cmp_scan_config_t *pstcCmpScanConfig)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    if (pstcCmpScanConfig != NULL) {
        pstcCmpScanConfig->u16Mode = CMP_SCAN_NONE;
        pstcCmpScanConfig->u16Src = 0U;
        pstcCmpScanConfig->u16Stable = 0U;
        pstcCmpScanConfig->u16Period = 9U;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Get CMP scan function stable time and period configuration
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16Stable           The CMP stable time = T(CMP clock) x u16Stable, The stable time is recommended
 *                                  greater than 100nS
 *   @arg  range from 0x00U to 0x3FU
 * @param  [in] u16Period           CMP scan period = T(CMP clock) x u16Period
 *   @arg  range from 0x09 to 0xFF
 * @retval int32_t
 *         - LL_OK:                 Success
 *         - LL_ERR_INVD_PARAM:     Parameter error
 * @note   1. u16Period > (u16Stable + u16OutFilter * 4 + CMP_SCAN_PERIOD_IMME)
 *            u16OutFilter is configured in CMP_NormalModeInit() function.
 */
int32_t CMP_ScanTimeConfig(CM_CMP_TypeDef *CMPx, uint16_t u16Stable, uint16_t u16Period)
{
    uint16_t u16Fltsl;
    uint16_t u16FltslDiv;
    int32_t i32Ret = LL_OK;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_CMP_SCAN_STABLE(u16Stable));
    DDL_ASSERT(IS_CMP_SCAN_PERIOD(u16Period));

    u16Fltsl = READ_REG16_BIT(CMPx->FIR, CMP_FIR_FCKS);
    if (0U != u16Fltsl) {
        u16FltslDiv = ((uint16_t)1U << (u16Fltsl - 1U));
    } else {
        u16FltslDiv = 0U;
    }

    if (u16Period <= (u16Stable + u16FltslDiv * 4U + CMP_SCAN_PERIOD_IMME)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        MODIFY_REG32(CMPx->SCCR, CMP_SCCR_SSTB | CMP_SCCR_SPRD,
                     ((uint32_t)u16Stable << CMP_SCCR_SSTB_POS) | ((uint32_t)u16Period << CMP_SCCR_SPRD_POS));
    }
    return i32Ret;
}

/**
 * @brief  CMP scan function command
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_ScanCmd(CM_CMP_TypeDef *CMPx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_UNIT(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    MODIFY_REG8(CMPx->MDR, CMP_MDR_CSST, (uint8_t)enNewState << CMP_MDR_CSST_POS);
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

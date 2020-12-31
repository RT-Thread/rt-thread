/**
 *******************************************************************************
 * @file  hc32f4a0_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12        Heqb         First version
   2020-08-31        Heqb         Replace CMP_Delay300ns() with the function DDL_DelayUS()
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_cmp.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CMP CMP
 * @brief CMP Driver Library
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

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

#define IS_CMP_INSTANCE(x)                                                     \
(   ((x) == M4_CMP1)                            ||                             \
    ((x) == M4_CMP2)                            ||                             \
    ((x) == M4_CMP3)                            ||                             \
    ((x) == M4_CMP4))

#define IS_CMP_MODE(x)                                                         \
(   ((x) == CMP_MODE_NORMAL)                    ||                             \
    ((x) == CMP_MODE_WINDOW))

#define IS_CMP_CVSL_CH(x)                                                     \
(   ((x) == CMP_CVSL_NONE)                      ||                             \
    ((x) == CMP_CVSL_INP1)                      ||                             \
    ((x) == CMP_CVSL_INP2)                      ||                             \
    ((x) == CMP_CVSL_INP3)                      ||                             \
    ((x) == CMP_CVSL_INP4))

#define IS_CMP1_CVSL_SOURCE(x)                                                 \
(   ((x) == CMP1_INP3_NONE)                     ||                             \
    ((x) == CMP1_INP3_CMP1_INP3)                ||                             \
    ((x) == CMP1_INP3_CMP2_INP3)                ||                             \
    ((x) == CMP1_INP2_NONE)                     ||                             \
    ((x) == CMP1_INP2_PGA1)                     ||                             \
    ((x) == CMP1_INP2_PGA2)                     ||                             \
    ((x) == CMP1_INP2_CMP1_INP2))

#define IS_CMP3_CVSL_SOURCE(x)                                                 \
(   ((x) == CMP3_INP3_NONE)                     ||                             \
    ((x) == CMP3_INP3_CMP3_INP3)                ||                             \
    ((x) == CMP3_INP3_CMP4_INP3)                ||                             \
    ((x) == CMP3_INP2_NONE)                     ||                             \
    ((x) == CMP3_INP2_PGA3)                     ||                             \
    ((x) == CMP3_INP2_PGA4)                     ||                             \
    ((x) == CMP3_INP2_CMP3_INP2))

#define IS_CMP_RVSL(x)                                                         \
(   ((x) == CMP_RVSL_NONE)                      ||                             \
    ((x) == CMP_RVSL_INM1)                      ||                             \
    ((x) == CMP_RVSL_INM2)                      ||                             \
    ((x) == CMP_RVSL_INM3)                      ||                             \
    ((x) == CMP_RVSL_INM4))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   ((x) == CMP_OUT_REVERSE_OFF)                ||                             \
    ((x) == CMP_OUT_REVERSE_ON))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   ((x) == CMP_DETECT_EDGS_NONE)               ||                             \
    ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   ((x) == CMP_OUT_FILTER_NONE)                ||                             \
    ((x) == CMP_OUT_FILTER_PCLK3)               ||                             \
    ((x) == CMP_OUT_FILTER_PCLK3_DIV8)          ||                             \
    ((x) == CMP_OUT_FILTER_PCLK3_DIV32))

#define IS_CMP_TIMWIN_FUNC(x)                                                  \
(   ((x) == CMP_TIMERWIN_OFF)                   ||                             \
    ((x) == CMP_TIMERWIN_ON))

#define IS_CMP_TIMWIN_INVALIDLEVEL(x)                                          \
(   ((x) == CMP_TIMERWIN_INVALID_LEVEL_LOW)     ||                             \
    ((x) == CMP_TIMERWIN_INVALID_LEVEL_HIGH))

#define IS_CMP_TIMWIN_OUT_LEVEL(x)                                             \
(   ((x) == CMP_TIMERWIN_OUT_LEVEL_LOW)         ||                             \
    ((x) == CMP_TIMERWIN_OUT_LEVEL_HIGH))
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
 * @defgroup CMP_Global_Functions CMP Global Functions
 * @{
 */

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [in] pstcCMP_InitStruct     Pointer to a stc_cmp_init_t structure variable which will be initialized.
 *   @arg  See the struct @ref stc_cmp_init_t.
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_StructInit(stc_cmp_init_t *pstcCMP_InitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;
    if (pstcCMP_InitStruct != NULL)
    {
        pstcCMP_InitStruct->u8CmpCh = CMP_CVSL_NONE;
        pstcCMP_InitStruct->u8RefVol = CMP_RVSL_NONE;
        pstcCMP_InitStruct->u8OutDetectEdges = CMP_DETECT_EDGS_NONE;
        pstcCMP_InitStruct->u8OutFilter = CMP_OUT_FILTER_NONE;
        pstcCMP_InitStruct->u8OutPolarity = CMP_OUT_REVERSE_OFF;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  De-initialize CMP unit
 * @param  [in] CMPx  Pointer to CMP instance register base,This
 * parameter can be one of the following values:
 *   @arg  M0P_CMP1:   CMP unit 1 instance register base
 *   @arg  M0P_CMP2:   CMP unit 2 instance register base
 *   @arg  M0P_CMP3:   CMP unit 3 instance register base
 *   @arg  M0P_CMP4:   CMP unit 4 instance register base
 * @retval None
 */
void CMP_DeInit(M4_CMP_TypeDef *CMPx)
{
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    CLEAR_REG8(CMPx->MDR);
    CLEAR_REG8(CMPx->FIR);
    CLEAR_REG8(CMPx->OCR);
    CLEAR_REG8(CMPx->PMSR);
    CLEAR_REG16(CMPx->VISR);
    CLEAR_REG16(CMPx->TWSR);
    CLEAR_REG16(CMPx->TWPR);
}

/**
 * @brief  CMP normal mode initialize
 * @param  [in] CMPx   Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] pstcCmpInit     CMP function base parameter structure
 *   @arg  See the structure definition for @ref stc_cmp_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                                const stc_cmp_init_t *pstcCmpInit)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check CMPx instance and configuration structure*/
    if  (NULL != pstcCmpInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_CVSL_CH(pstcCmpInit->u8CmpCh));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpInit->u8RefVol));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpInit->u8OutPolarity));

        /* Stop CMP compare */
        CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Set compare voltage */
        WRITE_REG8(CMPx->PMSR, pstcCmpInit->u8CmpCh);
        if((M4_CMP1 == CMPx) && ((pstcCmpInit->u8CmpCh == CMP_CVSL_INP2) ||
                                 (pstcCmpInit->u8CmpCh == CMP_CVSL_INP3)))
        {
            DDL_ASSERT(IS_CMP1_CVSL_SOURCE(pstcCmpInit->u16CmpVol));
            WRITE_REG8(CMPx->VISR, pstcCmpInit->u16CmpVol);
        }
        if((M4_CMP3 == CMPx) && ((pstcCmpInit->u8CmpCh == CMP_CVSL_INP2) ||
                                 (pstcCmpInit->u8CmpCh == CMP_CVSL_INP3)))
        {
            DDL_ASSERT(IS_CMP3_CVSL_SOURCE(pstcCmpInit->u16CmpVol));
            WRITE_REG8(CMPx->VISR, pstcCmpInit->u16CmpVol);
        }
        /* Set reference voltage */
        MODIFY_REG8(CMPx->PMSR, CMP_PMSR_RVSL, pstcCmpInit->u8RefVol);
        /* Delay 1us*/
        DDL_DelayUS(1U);
        /* Start CMP compare */
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 1us*/
        DDL_DelayUS(1U);
        /* Set output filter and output detect edge and output polarity */
        WRITE_REG8(CMPx->FIR, (pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges));
        WRITE_REG8(CMPx->OCR, pstcCmpInit->u8OutPolarity);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] CMPx   Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   Select CMP1 and CMP2 for window comparison
 *   @arg  M4_CMP2:   Select CMP1 and CMP2 for window comparison
 *   @arg  M4_CMP3:   Select CMP3 and CMP4 for window comparison
 *   @arg  M4_CMP4:   Select CMP3 and CMP4 for window comparison
 * @param  [in] pstcCmpInit    Configuration structure for window mode initialize
 *   @arg  See the structure definition for @ref stc_cmp_init_t
 * @param  [in] pstcCmpWinRef  Configuration structure for window mode reference voltage
 *   @arg  See the structure definition for @ref stc_cmp_win_ref_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_WindowModeInit(const M4_CMP_TypeDef *CMPx,
                               const stc_cmp_init_t *pstcCmpInit,
                               const stc_cmp_win_ref_t *pstcCmpWinRef)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check configuration structure */
    if (NULL != pstcCmpInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_CVSL_CH(pstcCmpWinRef->u8CmpCh1));
        DDL_ASSERT(IS_CMP_CVSL_CH(pstcCmpWinRef->u8CmpCh2));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpWinRef->u8WinVolLow));
        DDL_ASSERT(IS_CMP_RVSL(pstcCmpWinRef->u8WinVolHigh));
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCmpInit->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCmpInit->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCmpInit->u8OutPolarity));
        if((CMPx == M4_CMP1) || (CMPx == M4_CMP2))
        {
            /* Stop CMP1 CMP2 compare */
            CLEAR_REG8_BIT(M4_CMP1->MDR, CMP_MDR_CENB);
            CLEAR_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CENB);
            /* Set compare voltage */
            WRITE_REG8(M4_CMP1->PMSR, pstcCmpWinRef->u8CmpCh1);
            WRITE_REG8(M4_CMP1->VISR, pstcCmpWinRef->u16CmpVol);
            WRITE_REG8(M4_CMP2->PMSR, pstcCmpWinRef->u8CmpCh2);
            /* Set reference Voltage */
            MODIFY_REG8(M4_CMP1->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolLow);
            MODIFY_REG8(M4_CMP2->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolHigh);
            /* Select window compare mode */
            SET_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CWDE);
            /* Start CMP compare function */
            SET_REG8_BIT(M4_CMP1->MDR, CMP_MDR_CENB);
            SET_REG8_BIT(M4_CMP2->MDR, CMP_MDR_CENB);
            /* Delay 1us*/
            DDL_DelayUS(1U);
            /* Set output filter and output detect edge and output polarity */
            WRITE_REG8(M4_CMP2->FIR, pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges);
            WRITE_REG8(M4_CMP2->OCR, pstcCmpInit->u8OutPolarity);
        }
        else
        {
            /* Stop CMP3 CMP4 compare */
            CLEAR_REG8_BIT(M4_CMP3->MDR, CMP_MDR_CENB);
            CLEAR_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CENB);
            /* Set compare voltage */
            WRITE_REG8(M4_CMP3->PMSR, pstcCmpWinRef->u8CmpCh1);
            WRITE_REG8(M4_CMP3->VISR, pstcCmpWinRef->u16CmpVol);
            WRITE_REG8(M4_CMP4->PMSR, pstcCmpWinRef->u8CmpCh2);
            /* Set reference Voltage */
            MODIFY_REG8(M4_CMP3->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolLow);
            MODIFY_REG8(M4_CMP4->PMSR, CMP_PMSR_RVSL, pstcCmpWinRef->u8WinVolHigh);
            /* Select window compare mode */
            SET_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CWDE);
            /* Start CMP compare function */
            SET_REG8_BIT(M4_CMP3->MDR, CMP_MDR_CENB);
            SET_REG8_BIT(M4_CMP4->MDR, CMP_MDR_CENB);
            /* Delay 1us*/
            DDL_DelayUS(1U);
            /* Set output filter and output detect edge and output polarity */
            WRITE_REG8(M4_CMP4->FIR, pstcCmpInit->u8OutFilter | pstcCmpInit->u8OutDetectEdges);
            WRITE_REG8(M4_CMP4->OCR, pstcCmpInit->u8OutPolarity);
        }
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Voltage compare function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus     The function new status.
 * This parameter can be: Enable or Disable.
 * @retval None
 */
void CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));

    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 1us*/
        DDL_DelayUS(1U);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    }
}

/**
 * @brief  Voltage compare interrupt function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));
    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
}

/**
 * @brief  Voltage compare output command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));
    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
}

/**
 * @brief  Voltage compare output port VCOUT function command
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] enNewStatus    The function new status.
 *   This parameter can be: Enable or Disable.
 * @retval None
 */
void CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewStatus)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));
    if(Enable == enNewStatus)
    {
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
    else
    {
        CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
}

/**
 * @brief  Voltage compare result flag read
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @retval In normal mode:
 *         Reset:     compare voltage < reference voltage
 *         Set:       compare voltage > reference voltage
 *         In Window mode:
 *         Reset:     compare voltage < reference low voltage or
 *                    compare voltage > reference high voltage
 *         Set:       reference low voltage < compare voltage < reference high voltage
 */
en_flag_status_t CMP_GetResult(const M4_CMP_TypeDef *CMPx)
{
    en_flag_status_t enRet;
    /* Check CMPx instance */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    enRet = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CMON) ? Set : Reset;
    return enRet;
}

/**
 * @brief  Voltage compare timer window function configuration
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] pstcCMP_TimerWinStruct  Configuration structure for Timer window mode.
 * @retval Ok: Successfully
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t CMP_TimerWindowConfig(M4_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindow_t *pstcCMP_TimerWinStruct)
{
    en_result_t enRet = ErrorInvalidParameter;
    /* Check CMPx instance and configuration structure*/
    if (NULL != pstcCMP_TimerWinStruct)
    {
        enRet = Ok;
        /* Check parameters */
        DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
        DDL_ASSERT(IS_CMP_TIMWIN_INVALIDLEVEL(pstcCMP_TimerWinStruct->u8TWInvalidLevel));
        DDL_ASSERT(IS_CMP_TIMWIN_OUT_LEVEL(pstcCMP_TimerWinStruct->u8TWOutLevel));
        /* Select timer window mode */
        SET_REG8_BIT(CMPx->OCR, CMP_OCR_TWOE);
        /* Select output level when timer window invalid */
        MODIFY_REG8(CMPx->OCR, CMP_OCR_TWOL, pstcCMP_TimerWinStruct->u8TWInvalidLevel);
        /* Select Timer window source  */
        WRITE_REG16(CMPx->TWSR, pstcCMP_TimerWinStruct->u16TWSelect);
        /* Select timer window mode output level */
        if(CMP_TIMERWIN_OUT_LEVEL_HIGH == pstcCMP_TimerWinStruct->u8TWOutLevel)
        {
            SET_REG16_BIT(CMPx->TWPR, pstcCMP_TimerWinStruct->u16TWSelect);
        }
        else
        {
            CLEAR_REG16_BIT(CMPx->TWPR, pstcCMP_TimerWinStruct->u16TWSelect);
        }
    }
    return enRet;
}

/**
 * @brief  Set output detect edge
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpEdges    CMP output detect edge selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_DETECT_EDGS_NONE:      Do not detect edge
 *   @arg  CMP_DETECT_EDGS_RISING:    Detect rising edge
 *   @arg  CMP_DETECT_EDGS_FALLING:   Detect falling edge
 *   @arg  CMP_DETECT_EDGS_BOTH:      Detect rising and falling edges
 * @retval None
 */
void CMP_SetOutDetectEdges(M4_CMP_TypeDef *CMPx, uint8_t u8CmpEdges)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(u8CmpEdges));
    /* Read CMP status */
    u8temp = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output detect edge selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_EDGS, u8CmpEdges);
    if(u8temp != 0U)
    {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
        /* Delay 1us */
        DDL_DelayUS(1U);
    }
}

/**
 * @brief  Set output filter
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpFilter    CMP output filter selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_OUT_FILTER_NONE:          Don't filter
 *   @arg  CMP_OUT_FILTER_PCLK3:         Use PCLK3
 *   @arg  CMP_OUT_FILTER_PCLK3_DIV8:    Use PCLK3 / 8
 *   @arg  CMP_OUT_FILTER_PCLK3_DIV32:   Use PCLK3 / 32
 * @retval None
 */
void CMP_SetOutputFilter(M4_CMP_TypeDef *CMPx, uint8_t u8CmpFilter)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_FILTER(u8CmpFilter));
    /* Read CMP status */
    u8temp = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output filter selection */
    MODIFY_REG8(CMPx->FIR, CMP_FIR_FCKS, u8CmpFilter);
    if(u8temp != 0U)
    {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
        /* Delay 1us */
        DDL_DelayUS(1U);
    }
}

/**
 * @brief  Set output polarity
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpPolarity    CMP output polarity selection.
 *   This parameter can be one of the following values:
 *   @arg  CMP_OUT_REVERSE_OFF:      CMP output don't reverse
 *   @arg  CMP_OUT_REVERSE_ON:       CMP output level reverse
 * @retval None
 */
void CMP_SetOutputPolarity(M4_CMP_TypeDef *CMPx, uint8_t u8CmpPolarity)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_OUT_POLARITY(u8CmpPolarity));
    /* Read CMP status */
    u8temp = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* CMP output polarity selection */
    MODIFY_REG8(CMPx->OCR, CMP_OCR_COPS, u8CmpPolarity);
    if(u8temp != 0U)
    {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
        /* Delay 1us */
        DDL_DelayUS(1U);
    }
}

/**
 * @brief  Set compare voltage
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8CmpCh    Select the compare voltage.
 *   This parameter can be one of the following values:
 *   @arg  CMP_CVSL_NONE:      Don't input compare voltage
 *   @arg  CMP_CVSL_INP1:      Select INP1 as compare voltage
 *   @arg  CMP_CVSL_INP2:      Select INP2 as compare voltage
 *   @arg  CMP_CVSL_INP3:      Select INP3 as compare voltage
 *   @arg  CMP_CVSL_INP4:      Select INP4 as compare voltage
 * @param  [in] u8CmpVol   Select the compare voltage source (Config the parameter when use CMP1 or CMP3)
 *   This parameter can be one of the following values:
 *   When use CMP1:
 *   @arg  CMP1_INP3_NONE:      Don't input voltage to CMP1 INP3
 *   @arg  CMP1_INP3_CMP1_INP3: Select CMP1_INP3 as CMP1 INP3 input
 *   @arg  CMP1_INP3_CMP2_INP3: Select CMP2_INP3 as CMP1 INP3 input
 *   @arg  CMP1_INP2_NONE:      Don't input voltage to CMP1 INP2
 *   @arg  CMP1_INP2_PGA1:      Select PGA1 as CMP1 INP2 input
 *   @arg  CMP1_INP2_PGA2:      Select PGA2 as CMP1 INP2 input
 *   @arg  CMP1_INP2_CMP1_INP2: Select CMP1_INP2 as CMP1 INP2 input
 *   When use CMP3:
 *   @arg  CMP3_INP3_NONE:      Don't input voltage to CMP3 INP3
 *   @arg  CMP3_INP3_CMP3_INP3: Select CMP3_INP3 as CMP3 INP3 input
 *   @arg  CMP3_INP3_CMP4_INP3: Select CMP4_INP3 as CMP3 INP3 input
 *   @arg  CMP3_INP2_NONE:      Don't input voltage to CMP3 INP2
 *   @arg  CMP3_INP2_PGA3:      Select PGA3 as CMP3 INP2 input
 *   @arg  CMP3_INP2_PGA4:      Select PGA4 as CMP3 INP2 input
 *   @arg  CMP3_INP2_CMP3_INP2: Select CMP3_INP2 as CMp3 INP2 input
 * @retval None
 * @note   When use INP1 or INP4, please set u8CmpVol to 0
 */
void CMP_SetCompareVol(M4_CMP_TypeDef *CMPx, uint8_t u8CmpCh, uint8_t u8CmpVol)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_CVSL_CH(u8CmpCh));
    /* Read CMP status */
    u8temp = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Set compare voltage */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_CVSL, u8CmpCh);
    if((M4_CMP1 == CMPx) && ((u8CmpCh == CMP_CVSL_INP2) || (u8CmpCh == CMP_CVSL_INP3)))
    {
        DDL_ASSERT(IS_CMP1_CVSL_SOURCE(u8CmpVol));
        WRITE_REG8(CMPx->VISR, u8CmpVol);
    }
    if((M4_CMP3 == CMPx) && ((u8CmpCh == CMP_CVSL_INP2) || (u8CmpCh == CMP_CVSL_INP3)))
    {
        DDL_ASSERT(IS_CMP3_CVSL_SOURCE(u8CmpVol));
        WRITE_REG8(CMPx->VISR, u8CmpVol);
    }
    if(u8temp != 0U)
    {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
        /* Delay 1us */
        DDL_DelayUS(1U);
    }
}

/**
 * @brief  Set reference voltage
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u8RefVol    Select the reference voltage.
 *   This parameter can be one of the following values:
 *   @arg  CMP_RVSL_NONE:      Don't input reference voltage
 *   @arg  CMP_RVSL_INM1:      Select INM1 as reference voltage
 *   @arg  CMP_RVSL_INM2:      Select INM2 as reference voltage
 *   @arg  CMP_RVSL_INM3:      Select INM3 as reference voltage
 *   @arg  CMP_RVSL_INM4:      Select INM4 as reference voltage
 * @retval None
 */
void CMP_SetRefVol(M4_CMP_TypeDef *CMPx, uint8_t u8RefVol)
{
    uint8_t u8temp;
    /* Check parameters */
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    DDL_ASSERT(IS_CMP_RVSL(u8RefVol));
    /* Read CMP status */
    u8temp = READ_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Stop CMP function */
    CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
    /* Set reference voltage */
    MODIFY_REG8(CMPx->PMSR, CMP_PMSR_RVSL, u8RefVol);
    if(u8temp != 0U)
    {
        /* Recover CMP status */
        MODIFY_REG8(CMPx->MDR, CMP_MDR_CENB, u8temp);
        /* Delay 1us */
        DDL_DelayUS(1U);
    }
}

/**
 * @brief  Ste CMP Timer window signal.
 * @param  [in] CMPx    Pointer to CMP instance register base
 *   This parameter can be one of the following values:
 *   @arg  M4_CMP1:   CMP unit 1 instance register base
 *   @arg  M4_CMP2:   CMP unit 2 instance register base
 *   @arg  M4_CMP3:   CMP unit 3 instance register base
 *   @arg  M4_CMP4:   CMP unit 4 instance register base
 * @param  [in] u16TWSignal             Selection timer window signal
 *  This parameter can be value of @ref CMP_TimerWin_Select
 * @param  [in] enNewStatus    The function new status.
 *   This parameter can be: Enable or Disable.
 * @retval None
 */
void CMP_SetTimerWinSignal(M4_CMP_TypeDef *CMPx,          \
                            uint16_t u16TWSignal, en_functional_state_t enNewStatus)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewStatus));
    DDL_ASSERT(IS_CMP_INSTANCE(CMPx));
    if (enNewStatus == Enable)
    {
        MODIFY_REG16(CMPx->TWSR, u16TWSignal, u16TWSignal);
    }
    else
    {
        CLEAR_REG16_BIT(CMPx->TWSR, u16TWSignal);
    }
}

/**
 * @}
 */

#endif  /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

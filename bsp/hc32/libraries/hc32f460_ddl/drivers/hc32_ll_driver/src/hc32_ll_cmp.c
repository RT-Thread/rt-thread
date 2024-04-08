/**
 *******************************************************************************
 * @file  hc32_ll_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Modify macro define for API
   2023-01-15       CDT             Code refine for scan function
   2023-06-30       CDT             Modify typo
   2023-09-30       CDT             Add assert for IEN bit in GetCmpFuncStatusAndDisFunc function
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
    ((x) == CM_CMP3))

#define CMP1_INP4_MASK                       (CMP1_POSITIVE_PGAO      |        \
                                              CMP1_POSITIVE_PGAO_BP   |        \
                                              CMP1_POSITIVE_CMP1_INP4)
#define CMP1_POSITIVE_MASK                   (CMP_POSITIVE_NONE       |        \
                                              CMP1_POSITIVE_CMP1_INP1 |        \
                                              CMP1_POSITIVE_CMP1_INP2 |        \
                                              CMP1_POSITIVE_CMP1_INP3 |        \
                                              CMP1_INP4_MASK)

#define CMP2_INP4_MASK                       (CMP2_POSITIVE_PGAO      |        \
                                              CMP2_POSITIVE_PGAO_BP)
#define CMP2_POSITIVE_MASK                   (CMP_POSITIVE_NONE       |        \
                                              CMP2_POSITIVE_CMP2_INP1 |        \
                                              CMP2_POSITIVE_CMP2_INP2 |        \
                                              CMP2_POSITIVE_CMP2_INP3 |        \
                                              CMP2_INP4_MASK)

#define CMP3_POSITIVE_MASK                   (CMP_POSITIVE_NONE       |        \
                                              CMP3_POSITIVE_CMP3_INP1 |        \
                                              CMP3_POSITIVE_CMP3_INP2 |        \
                                              CMP3_POSITIVE_CMP3_INP3 |        \
                                              CMP3_POSITIVE_CMP3_INP4)

#define IS_CMP1_POSITIVE_IN(x)                                                 \
(   (((x) & (~CMP1_POSITIVE_MASK)) == 0U) &&                                   \
    ((((x) & CMP1_INP4_MASK) == 0U) ||                                         \
     (((x) & CMP1_INP4_MASK) == CMP1_POSITIVE_PGAO) ||                         \
     (((x) & CMP1_INP4_MASK) == CMP1_POSITIVE_PGAO_BP) ||                      \
     (((x) & CMP1_INP4_MASK) == CMP1_POSITIVE_CMP1_INP4)))

#define IS_CMP2_POSITIVE_IN(x)                                                 \
(   (((x) & (~CMP2_POSITIVE_MASK)) == 0U) &&                                   \
    ((((x) & CMP2_INP4_MASK) == 0U) ||                                         \
     (((x) & CMP2_INP4_MASK) == CMP2_POSITIVE_PGAO) ||                         \
     (((x) & CMP2_INP4_MASK) == CMP2_POSITIVE_PGAO_BP)))

#define IS_CMP3_POSITIVE_IN(x)                                                 \
(   ((x) & (~CMP3_POSITIVE_MASK)) == 0U)

#define IS_CMP_NEGATIVE_IN(x)                                                  \
(   ((x) == CMP_NEGATIVE_NONE)                  ||                             \
    ((x) == CMP_NEGATIVE_INM1)                  ||                             \
    ((x) == CMP_NEGATIVE_INM2)                  ||                             \
    ((x) == CMP_NEGATIVE_INM3)                  ||                             \
    ((x) == CMP_NEGATIVE_INM4))

#define IS_CMP_SCAN_STABLE(x)                                                  \
(   (x) <= 0x0FU)

#define IS_CMP_SCAN_PERIOD(x)                                                  \
(   ((x) >= 0x0FU)                              &&                             \
    ((x) <= 0xFFU))

#define IS_CMP_8_BIT_DAC_CH(x)                                                 \
(   ((x) == CMP_8BITDAC_CH1)                    ||                             \
    ((x) == CMP_8BITDAC_CH2))

#define IS_CMP_8_BIT_DAC_DATA(x)                                               \
(   (x) <= 0xFFU)

#define IS_CMP_8_BIT_DAC_SW(x)                                                 \
(   ((x) == CMP_ADC_REF_VREF)                   ||                             \
    ((x) == CMP_ADC_REF_DA2)                    ||                             \
    ((x) == CMP_ADC_REF_DA1))

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
    ((x) == CMP_OUT_FILTER_CLK_DIV32)           ||                             \
    ((x) == CMP_OUT_FILTER_CLK_DIV64))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   ((x) == CMP_DETECT_EDGS_NONE)               ||                             \
    ((x) == CMP_DETECT_EDGS_RISING)             ||                             \
    ((x) == CMP_DETECT_EDGS_FALLING)            ||                             \
    ((x) == CMP_DETECT_EDGS_BOTH))

/**
 * @}
 */
#define CMP_DADC_RVADC_REG_UNLOCK               (0x5500U)

#define CMP_SCAN_PERIOD_IMME                (0x05U)

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
    DDL_ASSERT(READ_REG8_BIT(CMPx->CTRL, CMP_CTRL_IEN) == 0U);

    /* Read CMP status */
    u16temp = READ_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);
    /* Stop CMP function */
    CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);
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
        MODIFY_REG16(CMPx->CTRL, CMP_CTRL_CMPON, u16CmpFuncStatus);
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
 * @brief  De-initialize CMP unit
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @retval None
 */
void CMP_DeInit(CM_CMP_TypeDef *CMPx)
{
    DDL_ASSERT(IS_CMP_UNIT(CMPx));

    CLR_REG16(CMPx->CTRL);
    CLR_REG16(CMPx->VLTSEL);
    WRITE_REG16(CMPx->CVSSTB, 0x0005U);
    WRITE_REG16(CMPx->CVSPRD, 0x000FU);
    CLR_REG16(CM_CMPCR->DADR1);
    CLR_REG16(CM_CMPCR->DADR2);
    CLR_REG16(CM_CMPCR->DACR);
    CLR_REG16(CM_CMPCR->RVADC);
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
        if (CM_CMP1 == CMPx) {
            DDL_ASSERT(IS_CMP1_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        } else if (CM_CMP2 == CMPx) {
            DDL_ASSERT(IS_CMP2_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        } else {
            DDL_ASSERT(IS_CMP3_POSITIVE_IN(pstcCmpInit->u16PositiveInput));
        }
        DDL_ASSERT(IS_CMP_NEGATIVE_IN(pstcCmpInit->u16NegativeInput));

        /* Stop CMP compare */
        CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);

        /* Set voltage in */
        WRITE_REG16(CMPx->VLTSEL, pstcCmpInit->u16PositiveInput | pstcCmpInit->u16NegativeInput);

        /* Delay 1us*/
        CMP_DelayUS(1U);
        /* Start CMP compare */
        SET_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);
        /* Delay 1us*/
        CMP_DelayUS(1U);
        /* Set output filter and output detect edge and output polarity */
        MODIFY_REG16(CMPx->CTRL, CMP_CTRL_FLTSL | CMP_CTRL_EDGSL | CMP_CTRL_INV, (pstcCmpInit->u16OutFilter | pstcCmpInit->u16OutDetectEdge | pstcCmpInit->u16OutPolarity));
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
        SET_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);
        /* Delay 1us*/
        CMP_DelayUS(1U);
    } else {
        CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPON);
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
        SET_REG16_BIT(CMPx->CTRL, CMP_CTRL_IEN);
    } else {
        CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_IEN);
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
        SET_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPOE);
    } else {
        CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_CMPOE);
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
        SET_REG16_BIT(CMPx->CTRL, CMP_CTRL_OUTEN);
    } else {
        CLR_REG16_BIT(CMPx->CTRL, CMP_CTRL_OUTEN);
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
    enRet = (READ_REG16_BIT(CMPx->OUTMON, CMP_OUTMON_OMON) != 0U) ? SET : RESET;
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
    MODIFY_REG16(CMPx->CTRL, CMP_CTRL_EDGSL, u8CmpEdges);
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
    MODIFY_REG16(CMPx->CTRL, CMP_CTRL_FLTSL, u8CmpFilter);
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
    MODIFY_REG16(CMPx->CTRL, CMP_CTRL_INV, u16CmpPolarity);
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
    if (CM_CMP1 == CMPx) {
        DDL_ASSERT(IS_CMP1_POSITIVE_IN(u16PositiveInput));
    } else if (CM_CMP2 == CMPx) {
        DDL_ASSERT(IS_CMP2_POSITIVE_IN(u16PositiveInput));
    } else {
        DDL_ASSERT(IS_CMP3_POSITIVE_IN(u16PositiveInput));
    }

    /* Read CMP status */
    u16temp = GetCmpFuncStatusAndDisFunc(CMPx);

    /* Set voltage in */
    MODIFY_REG16(CMPx->VLTSEL, (CMP_VLTSEL_CVSL | CMP_VLTSEL_C4SL), u16PositiveInput);

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
    MODIFY_REG16(CMPx->VLTSEL, CMP_VLTSEL_RVSL, u16NegativeInput);

    /* Recover CMP function */
    RecoverCmpFuncStatus(CMPx, u16temp);
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
    return (uint32_t)READ_REG16_BIT(CMPx->OUTMON, CMP_OUTMON_CVST);
}

/**
 * @brief  Get CMP scan function stable time and period configuration
 * @param  [in] CMPx                Pointer to CMP instance register base
 *   @arg  CM_CMPx
 * @param  [in] u16Stable           The CMP stable time = T(CMP clock) x u16Stable, The stable time is recommended
 *                                  greater than 100nS
 *   @arg  range from 0x00U to 0x0FU
 * @param  [in] u16Period           CMP scan period = T(CMP clock) x u16Period
 *   @arg  range from 0x0F to 0xFF
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

    u16Fltsl = READ_REG16_BIT(CMPx->CTRL, CMP_CTRL_FLTSL);
    if (0U != u16Fltsl) {
        u16FltslDiv = ((uint16_t)1U << (u16Fltsl - 1U));
    } else {
        u16FltslDiv = 0U;
    }

    if (u16Period <= (u16Stable + u16FltslDiv * 4U + CMP_SCAN_PERIOD_IMME)) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        WRITE_REG16(CMPx->CVSSTB, u16Stable);
        WRITE_REG16(CMPx->CVSPRD, u16Period);
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
    MODIFY_REG16(CMPx->CTRL, CMP_CTRL_CVSEN, (uint16_t)enNewState << CMP_CTRL_CVSEN_POS);
}

/**
 * @brief  CMP 8 bit DAC reference voltage command
 * @param  [in] u8Ch                The DAC channel @ref CMP_8Bit_Dac_Ch
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_8BitDAC_Cmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_8_BIT_DAC_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG16_BIT(CM_CMPCR->DACR, u8Ch);
    } else {
        CLR_REG16_BIT(CM_CMPCR->DACR, u8Ch);
    }
}

/**
 * @brief  CMP 8 bit DAC connect to ADC reference voltage command
 * @param  [in] u16AdcRefSw         @ref CMP_8BitDAC_Adc_Ref_Switch
 * @param  [in] enNewState          An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CMP_8BitDAC_AdcRefCmd(uint16_t u16AdcRefSw, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_8_BIT_DAC_SW(u16AdcRefSw));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    uint16_t WrTmp;
    if (ENABLE == enNewState) {
        WrTmp = u16AdcRefSw;
    } else {
        WrTmp = 0U;
    }
    WRITE_REG16(CM_CMPCR->RVADC, CMP_DADC_RVADC_REG_UNLOCK);
    WRITE_REG16(CM_CMPCR->RVADC, WrTmp);
}

/**
 * @brief  Write raw data to DAC
 * @param  [in] u8Ch             DAC channel @ref CMP_8Bit_Dac_Ch
 * @param  [in] u16DACData       DAC voltage data
 * @retval None
 */
void CMP_8BitDAC_WriteData(uint8_t u8Ch, uint16_t u16DACData)
{
    DDL_ASSERT(IS_CMP_8_BIT_DAC_CH(u8Ch));
    DDL_ASSERT(IS_CMP_8_BIT_DAC_DATA(u16DACData));

    if (CMP_8BITDAC_CH1 == u8Ch) {
        WRITE_REG16(CM_CMPCR->DADR1, u16DACData);
    } else {
        WRITE_REG16(CM_CMPCR->DADR2, u16DACData);
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

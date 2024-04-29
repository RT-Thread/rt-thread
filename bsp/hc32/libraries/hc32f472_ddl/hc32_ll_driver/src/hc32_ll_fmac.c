/**
 *******************************************************************************
 * @file  hc32_ll_fmac.c
 * @brief This file provides firmware functions to manage the Filter Math
 *        Accelerate (FMAC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify API FMAC_DeInit()
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
#include "hc32_ll_fmac.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_FMAC FMAC
 * @brief FMAC Driver Library
 * @{
 */

#if (LL_FMAC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FMAC_Local_Macros FMAC Local Macros
 * @{
 */
#define FMAC_RMU_TIMEOUT                        (100U)

/**
 * @defgroup FMAC_Check_Parameters_Validity FMAC Check Parameters Validity
 * @{
 */
#define IS_FMAC_FIR_SHIFT(x)                    ((x) <= FMAC_FIR_SHIFT_21BIT)

#define IS_FMAC_FIR_STAGE(x)                    ((x) <= FMAC_FIR_STAGE_16)

#define IS_FMAC_INT_FUNC(x)                                                     \
(   ((x) == FMAC_INT_ENABLE)                    ||                              \
    ((x) == FMAC_INT_DISABLE))

#define IS_VALID_UNIT(x)                                                        \
(   ((x) == CM_FMAC1)                           ||                              \
    ((x) == CM_FMAC2)                           ||                              \
    ((x) == CM_FMAC3)                           ||                              \
    ((x) == CM_FMAC4))
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
 * @defgroup FMAC_Global_Functions FMAC Global Functions
 * @{
 */

/**
 * @brief  FMAC peripheral initialization structure clear
 * @param  [in] pstcFmacInit      FMAC function structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval int32_t:
 *           - LL_OK: Success
 *           - LL_ERR_INVD_PARAM: Parameter error
 */
int32_t FMAC_StructInit(stc_fmac_init_t *pstcFmacInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcFmacInit != NULL) {
        pstcFmacInit->u32Stage   = FMAC_FIR_STAGE_0;
        pstcFmacInit->u32Shift   = FMAC_FIR_SHIFT_0BIT;
        pstcFmacInit->pi16Factor = NULL;
        pstcFmacInit->u32IntCmd  = FMAC_INT_DISABLE;
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  De-Initialize FMAC function
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:             FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:             FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:             FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:             FMAC unit 4 instance register base
 * @retval int32_t:
 *           - LL_OK:           Reset success.
 *           - LL_ERR_TIMEOUT:  Reset time out.
 */
int32_t FMAC_DeInit(CM_FMAC_TypeDef *FMACx)
{
    int32_t i32Ret = LL_OK;
    uint32_t i;
    __IO uint8_t u8TimeOut = 0U;
    __IO uint32_t *bCM_RMU_FRST1_FMACx = NULL;
    const uint32_t au32FMACx[] = {CM_FMAC1_BASE, CM_FMAC2_BASE, CM_FMAC3_BASE, CM_FMAC4_BASE};

    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    for (i = 0U; i < ARRAY_SZ(au32FMACx); i++) {
        if ((uint32_t)FMACx == au32FMACx[i]) {
            bCM_RMU_FRST1_FMACx = (uint32_t *)((uint32_t)&bCM_RMU->FRST1_b.FMAC1 + (i << 2UL));
            break;
        }
    }
    /* Reset FMAC */
    WRITE_REG32(*bCM_RMU_FRST1_FMACx, 0UL);
    /* Ensure reset procedure is completed */
    while (READ_REG32(*bCM_RMU_FRST1_FMACx) != 1UL) {
        u8TimeOut++;
        if (u8TimeOut > FMAC_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    return i32Ret;
}

/**
 * @brief  FMAC peripheral function initialize
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:             FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:             FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:             FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:             FMAC unit 4 instance register base
 * @param  [in] pstcFmacInit     FMAC function base parameter structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval int32_t:
 *           - LL_OK: Success
 *           - LL_ERR_INVD_PARAM: Parameter error
 */
int32_t FMAC_Init(CM_FMAC_TypeDef *FMACx, const stc_fmac_init_t *pstcFmacInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    int16_t *pi16Factor;
    __IO uint32_t *FMAC_CORx;
    uint32_t i;
    if ((pstcFmacInit != NULL) && (pstcFmacInit->pi16Factor != NULL)) {
        DDL_ASSERT(IS_VALID_UNIT(FMACx));
        DDL_ASSERT(IS_FMAC_FIR_SHIFT(pstcFmacInit->u32Shift));
        DDL_ASSERT(IS_FMAC_FIR_STAGE(pstcFmacInit->u32Stage));
        DDL_ASSERT(IS_FMAC_INT_FUNC(pstcFmacInit->u32IntCmd));

        pi16Factor = (pstcFmacInit->pi16Factor);
        /* Configure filter stage and results right shift bits */
        WRITE_REG32(FMACx->CTR, (pstcFmacInit->u32Stage | (pstcFmacInit->u32Shift << FMAC_CTR_SHIFT_POS)));
        /* Configure interrupt command */
        WRITE_REG32(FMACx->IER, pstcFmacInit->u32IntCmd);
        for (i = 0U; i < pstcFmacInit->u32Stage + 1U; i++) {
            FMAC_CORx = (__IO uint32_t *)((uint32_t)(&FMACx->COR0) + (i << 2UL));
            WRITE_REG32(*FMAC_CORx, *pi16Factor++);
        }
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @brief  Enable or Disable FMAC
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void FMAC_Cmd(CM_FMAC_TypeDef *FMACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(FMACx->ENR, enNewState);
}

/**
 * @brief  Set Filter result shift bits.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:             FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:             FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:             FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:             FMAC unit 4 instance register base
 * @param  [in] u32ShiftNum      Result shift times.
 * This parameter can be one of @ref FMAC_Filter_Shift
 * @retval None
 */
void FMAC_SetResultShift(CM_FMAC_TypeDef *FMACx, uint32_t u32ShiftNum)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FIR_SHIFT(u32ShiftNum));
    /* Set Filter result shift bits */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_SHIFT, u32ShiftNum << FMAC_CTR_SHIFT_POS);
}

/**
 * @brief  Set filter stage and filter factor.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] u32FilterStage  FMAC filter stage.
 * This parameter can be one of @ref FMAC_Filter_Stage
 * @param  [in] pi16Factor       FMAC filter factor.
 * This parameter can be set -32768 ~ 32767
 * @retval None
 */
void FMAC_SetStageFactor(CM_FMAC_TypeDef *FMACx, uint32_t u32FilterStage, int16_t *pi16Factor)
{
    __IO uint32_t *FMAC_CORx;
    uint8_t i;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FIR_STAGE(u32FilterStage));
    /* FMAC Software reset */
    CLR_REG32_BIT(FMACx->ENR, FMAC_ENR_FMACEN);
    SET_REG32_BIT(FMACx->ENR, FMAC_ENR_FMACEN);
    /* Set the filter stage  */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_STAGE_NUM, u32FilterStage);
    for (i = 0U; i < (u32FilterStage + 1UL); i++) {
        FMAC_CORx = (__IO uint32_t *)((uint32_t)(&FMACx->COR0) + ((uint32_t)i << 2UL));
        WRITE_REG32(*FMAC_CORx, *pi16Factor++);
    }
}

/**
 * @brief  Configure interrupt command.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void FMAC_IntCmd(CM_FMAC_TypeDef *FMACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(FMACx->IER, enNewState);
}

/**
 * @brief  Data input.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] i16Factor       Data that needs to be processed.
 * @retval None
 */
void FMAC_FIRInput(CM_FMAC_TypeDef *FMACx, int16_t i16Factor)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    WRITE_REG32(FMACx->DTR, i16Factor);
}

/**
 * @brief  Get FMAC status.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @retval An @ref en_flag_status_t enumeration type value.
 *              - SET           Calculate complete
 *              - RESET         Calculation in progress
 */
en_flag_status_t FMAC_GetStatus(const CM_FMAC_TypeDef *FMACx)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    return ((READ_REG32_BIT(FMACx->STR, FMAC_STR_READY) != 0UL) ? SET : RESET);
}

/**
 * @brief  Get calculation results.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  CM_FMAC1:            FMAC unit 1 instance register base
 *   @arg  CM_FMAC2:            FMAC unit 2 instance register base
 *   @arg  CM_FMAC3:            FMAC unit 3 instance register base
 *   @arg  CM_FMAC4:            FMAC unit 4 instance register base
 * @param  [out] pstcResult     Get result.
 *         u32ResultHigh:       The high value of the result
 *         u32ResultLow:        The low value of the result
 * @retval int32_t:
 *           - LL_OK: Success
 *           - LL_ERR_INVD_PARAM: pstcResult == NULL
 */
int32_t FMAC_GetResult(const CM_FMAC_TypeDef *FMACx, stc_fmac_result_t *pstcResult)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));

    if (pstcResult != NULL) {
        pstcResult->u32ResultHigh = READ_REG32(FMACx->RTR0);
        pstcResult->u32ResultLow  = READ_REG32(FMACx->RTR1);
        i32Ret = LL_OK;
    }
    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_FMAC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


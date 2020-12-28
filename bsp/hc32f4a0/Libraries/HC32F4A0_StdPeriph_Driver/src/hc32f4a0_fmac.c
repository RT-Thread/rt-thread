/**
 *******************************************************************************
 * @file  hc32f4a0_fmac.c
 * @brief This file provides firmware functions to manage the Filter Math
 *        Accelerate (FMAC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
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
#include "hc32f4a0_fmac.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_FMAC FMAC
 * @brief FMAC Driver Library
 * @{
 */

#if (DDL_FMAC_ENABLE == DDL_ON)

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

/**
 * @defgroup FMAC_Check_Parameters_Validity FMAC Check Parameters Validity
 * @{
 */
#define IS_FMAC_FILTER_SHIFT(x)               ((x) <= FMAC_FILTER_SHIFT_21BIT)


#define IS_FMAC_FILTER_STAGE(x)                  ((x) <= FMAC_FILTER_STAGE_16)

#define IS_FMAC_INT_FUNC(x)                                                  \
(   ((x) == FMAC_INT_ENABLE)                      ||                         \
    ((x) == FMAC_INT_DISABLE))

#define IS_VALID_UNIT(x)                                                     \
(   ((x) == M4_FMAC1)                             ||                         \
    ((x) == M4_FMAC2)                             ||                         \
    ((x) == M4_FMAC3)                             ||                         \
    ((x) == M4_FMAC4))
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
 * @brief  FMAC peripheral initialization stucture clear
 * @param  [in] pstcInitStruct    FMAC function structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_StructInit(stc_fmac_init_t* pstcInitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInitStruct != NULL)
    {
        pstcInitStruct->u32FiltStage  = FMAC_FILTER_STAGE_0;
        pstcInitStruct->u32FiltShift  = FMAC_FILTER_SHIFT_0BIT;
        pstcInitStruct->i16FiltFactor = 0;
        pstcInitStruct->u32IntCmd     = FMAC_INT_DISABLE;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  De-Initialize FMAC function
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:             FMAC unit 4 instance register base
 * @retval None
 */
void FMAC_DeInit(M4_FMAC_TypeDef* FMACx)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));

    WRITE_REG32(FMACx->CTR, 0UL);
    WRITE_REG32(FMACx->IER, 0UL);
    WRITE_REG32(FMACx->DTR, 0UL);
    WRITE_REG32(FMACx->RTR0, 0UL);
    WRITE_REG32(FMACx->RTR1, 0UL);
    WRITE_REG32(FMACx->STR, 0UL);
}

/**
 * @brief  FMAC peripheral function initialize
 * @param  [in] FMACx            Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:             FMAC unit 4 instance register base
 * @param  [in] pstcFmacInit     FMAC function base parameter structure
 *   @arg  See the structure definition for @ref stc_fmac_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 */
en_result_t FMAC_Init(M4_FMAC_TypeDef* FMACx, const stc_fmac_init_t *pstcFmacInit)
{
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t *FMAC_CORx;
    uint32_t u32temp;
    if(pstcFmacInit != NULL)
    {
        DDL_ASSERT(IS_VALID_UNIT(FMACx));
        DDL_ASSERT(IS_FMAC_FILTER_SHIFT(pstcFmacInit->u32FiltShift));
        DDL_ASSERT(IS_FMAC_FILTER_STAGE(pstcFmacInit->u32FiltStage));
        DDL_ASSERT(IS_FMAC_INT_FUNC(pstcFmacInit->u32IntCmd));
        u32temp = pstcFmacInit->u32FiltStage;
        /* Configure filter stage and results right shift bits */
        WRITE_REG32(FMACx->CTR, (pstcFmacInit->u32FiltStage | \
                     (pstcFmacInit->u32FiltShift << FMAC_CTR_SHIFT_POS)));
        /* Configure interrupt command */
        WRITE_REG32(FMACx->IER, pstcFmacInit->u32IntCmd);
        do{
            FMAC_CORx = (__IO uint32_t *)((uint32_t)(&FMACx->COR0) + (u32temp << 2UL));
            WRITE_REG32(*FMAC_CORx, pstcFmacInit->i16FiltFactor);
        }while((u32temp--) > 0UL);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Enable or Disable FMAC
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] enNewState      Disable or Enable the function
 * @retval None
 */
void FMAC_Cmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(FMACx->ENR, enNewState);
}

/**
 * @brief  Set Filter result shift bits.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:             FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:             FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:             FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:             FMAC unit 4 instance register base
 * @param  [in] u32ShiftNum      Result shift times.
 * This parameter can be set 0-21
 * @retval None
 */
void FMAC_SetResultShift(M4_FMAC_TypeDef* FMACx, uint32_t u32ShiftNum)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FILTER_SHIFT(u32ShiftNum));
    /* Set Filter result shift bits */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_SHIFT, u32ShiftNum << FMAC_CTR_SHIFT_POS);
}

/**
 * @brief  Set filter stage and filter factor.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] u32FilterStage  FMAC filter stage.
 * This parameter can be set 0 ~ 16
 * @param  [in] i16Factor       FMAC filter factor.
 * This parameter can be set -32768 ~ 32767
 * @retval None
 */
void FMAC_SetStageFactor(M4_FMAC_TypeDef* FMACx, uint32_t u32FilterStage, int16_t i16Factor)
{
    __IO uint32_t *FMAC_CORx;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FMAC_FILTER_STAGE(u32FilterStage));
    /* FMAC Software reset */
    CLEAR_REG32_BIT(FMACx->ENR, FMAC_ENR_FMACEN);
    SET_REG32_BIT(FMACx->ENR, FMAC_ENR_FMACEN);
    /* Set the filter stage  */
    MODIFY_REG32(FMACx->CTR, FMAC_CTR_STAGE_NUM, u32FilterStage);
    do
    {
        FMAC_CORx = (__IO uint32_t*)((uint32_t)(&FMACx->COR0) + (u32FilterStage << 2UL));
        WRITE_REG32(*FMAC_CORx, i16Factor);
    }while((u32FilterStage--) > 0UL);
}

/**
 * @brief  Configure interrupt command.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] enNewState      Disable or Enable the function.
 * @retval None
 */
void FMAC_IntCmd(M4_FMAC_TypeDef* FMACx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(FMACx->IER, enNewState);
}

/**
 * @brief  Data input.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @param  [in] i16Factor       Data that needs to be processed.
 * @retval None
 */
void FMAC_FIRInput(M4_FMAC_TypeDef* FMACx, int16_t i16Factor)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    WRITE_REG32(FMACx->DTR, i16Factor);
}

/**
 * @brief  Get FMAC status.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @retval Set                  Calculate complete
 *         Reset                Calculation in progress
 */
en_flag_status_t FMAC_GetStatus(const M4_FMAC_TypeDef* FMACx)
{
    DDL_ASSERT(IS_VALID_UNIT(FMACx));
    return (READ_REG32_BIT(FMACx->STR, FMAC_STR_READY) ? Set : Reset);
}

/**
 * @brief  Get calculation results.
 * @param  [in] FMACx           Pointer to FMAC instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_FMAC1:            FMAC unit 1 instance register base
 *   @arg  M4_FMAC2:            FMAC unit 2 instance register base
 *   @arg  M4_FMAC3:            FMAC unit 3 instance register base
 *   @arg  M4_FMAC4:            FMAC unit 4 instance register base
 * @param  [out] stcResult      Get result.
 *         u32ResultHigh:       The high value of the result
 *         u32ResultLow:        The low value of the result
 * @retval Ok: Success
 *         ErrorInvalidParameter: stcResult == NULL
 */
en_result_t FMAC_GetResult(const M4_FMAC_TypeDef* FMACx, stc_fmac_result_t *stcResult)
{
    en_result_t enRet = ErrorInvalidParameter;
    DDL_ASSERT(IS_VALID_UNIT(FMACx));

    if (stcResult != NULL)
    {
        stcResult->u32ResultHigh = READ_REG32(FMACx->RTR0);
        stcResult->u32ResultLow  = READ_REG32(FMACx->RTR1);
        enRet = Ok;
    }
    return enRet;
}

/**
 * @}
 */

#endif /* DDL_FMAC_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


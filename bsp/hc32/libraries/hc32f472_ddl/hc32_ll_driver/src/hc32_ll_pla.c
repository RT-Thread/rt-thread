/**
 *******************************************************************************
 * @file  hc32_ll_pla.c
 * @brief This file provides firmware functions to manage the Programmable Logic
 *        Array(PLA).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Optimized PLA_DeInit function
   2023-09-30       CDT             Modify API for Reference Manual Rev1.0
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
#include "hc32_ll_pla.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_PLA PLA
 * @brief Programmable Logic Array
 * @{
 */

#if (LL_PLA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PLA_Local_Macros PLA Local Macros
 * @{
 */

/* PLA maximum channel */
#define PLA_UNIT_MAX                    (16UL)

/**
 * @defgroup PLA_Calculate_Register_Address PLA Calculate Register Address
 * @{
 */
#define PLA_MUXS_ADDR(__PLA__, __UNIT__)       (__IO uint32_t*)((uint32_t)(&((__PLA__)->MUXS0)) + ((__UNIT__) * 0xCUL))
#define PLA_LUTCTL_ADDR(__PLA__, __UNIT__)     (__IO uint32_t*)((uint32_t)(&((__PLA__)->LUTCTL0)) + ((__UNIT__) * 0xCUL))
#define PLA_CTL_ADDR(__PLA__, __UNIT__)        (__IO uint32_t*)((uint32_t)(&((__PLA__)->CTL0)) + ((__UNIT__) * 0xCUL))
/**
 * @}
 */

/**
 * @defgroup PLA_Check_Parameters_Validity PLA Check Parameters Validity
 * @{
 */
#define IS_PLA_PERIPH(x)                        ((x) == CM_PLA)

#define IS_PLA_UNIT(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | PLA_UNIT_ALL) == PLA_UNIT_ALL))

#define IS_PLA_MUX_CH(x)                                                       \
(   ((x) == PLA_MUX_CH0)                        ||                             \
    ((x) == PLA_MUX_CH1))

#define IS_PLA_MUX_SRC(x)                       ((x) <= PLA_MUX_SRC_SIGNAL27)

#define IS_PLA_COMB_LOGIC(x)                    ((x) <= 0xFFUL)

#define IS_PLA_OUTPUT_SRC(x)                                                   \
(   ((x) == PLA_OUTPUT_SRC_NONE)                ||                             \
    ((x) == PLA_OUTPUT_SRC_LUT))

#define IS_PLA_INT(x)                                                          \
(   ((x) != 0UL)                                &&                             \
    (((x) | PLA_INT_ALL) == PLA_INT_ALL))

#define IS_PLA_FLAG(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | PLA_FLAG_ALL) == PLA_FLAG_ALL))

#define IS_PLA_PWC_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* PLA reset timeout */
#define PLA_RMU_TIMEOUT                 (100UL)

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
 * @defgroup PLA_Global_Functions PLA Global Functions
 * @{
 */

/**
 * @brief  De-Initialize PLA unit base function.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t PLA_DeInit(CM_PLA_TypeDef *PLAx)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_PLA_PWC_UNLOCKED());

    CLR_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_PLA);
    /* Ensure reset procedure is completed */
    while (RMU_FRST0_PLA != READ_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_PLA)) {
        u32TimeOut++;
        if (u32TimeOut > PLA_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize PLA base function.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @param  [in] pstcPlaInit            Pointer to a @ref stc_pla_init_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcPlaInit is NULL
 */
int32_t PLA_Init(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, const stc_pla_init_t *pstcPlaInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *LUTCTL;
    __IO uint32_t *MUXS;
    __IO uint32_t *CTL;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    if (NULL == pstcPlaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_PLA_PERIPH(PLAx));
        DDL_ASSERT(IS_PLA_UNIT(u32Unit));
        DDL_ASSERT(IS_PLA_MUX_SRC(pstcPlaInit->u32Mux0Src));
        DDL_ASSERT(IS_PLA_MUX_SRC(pstcPlaInit->u32Mux1Src));
        DDL_ASSERT(IS_PLA_COMB_LOGIC(pstcPlaInit->u32CombLogic));
        DDL_ASSERT(IS_PLA_OUTPUT_SRC(pstcPlaInit->u32OutputSrc));

        u32Temp = u32Unit;
        while (0UL != u32Temp) {
            if (0UL != (u32Temp & 0x1UL)) {
                MUXS = PLA_MUXS_ADDR(PLAx, u32UnitPos);
                WRITE_REG32(*MUXS, ((pstcPlaInit->u32Mux1Src & 0x0FUL) | ((pstcPlaInit->u32Mux1Src & 0x10UL) << 10U) |
                                    ((pstcPlaInit->u32Mux0Src & 0x0FUL) << 4U) | ((pstcPlaInit->u32Mux0Src & 0x10UL) << 11U)));
                LUTCTL = PLA_LUTCTL_ADDR(PLAx, u32UnitPos);
                WRITE_REG32(*LUTCTL, pstcPlaInit->u32CombLogic);
                CTL = PLA_CTL_ADDR(PLAx, u32UnitPos);
                MODIFY_REG32(*CTL, PLA_CTL_OSEL, pstcPlaInit->u32OutputSrc);
            }
            u32Temp >>= 1UL;
            u32UnitPos++;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_pla_init_t to default values.
 * @param  [out] pstcPlaInit            Pointer to a @ref stc_pla_init_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcPlaInit is NULL
 */
int32_t PLA_StructInit(stc_pla_init_t *pstcPlaInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcPlaInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcPlaInit->u32Mux0Src         = PLA_MUX_SRC_SIGNAL0;
        pstcPlaInit->u32Mux1Src         = PLA_MUX_SRC_SIGNAL0;
        pstcPlaInit->u32CombLogic       = 0UL;
        pstcPlaInit->u32OutputSrc       = PLA_OUTPUT_SRC_LUT;
    }

    return i32Ret;
}

/**
 * @brief  Get output level of the PLA unit.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @retval An @ref en_functional_state_t enumeration value.
 *           - ENABLE: The PLA output high level
 *           - DISABLE: The PLA output low level
 */
en_functional_state_t PLA_GetOutputLevel(CM_PLA_TypeDef *PLAx, uint32_t u32Unit)
{
    en_functional_state_t enState = DISABLE;

    /* Check parameters */
    DDL_ASSERT(IS_PLA_PERIPH(PLAx));
    DDL_ASSERT(IS_PLA_UNIT(u32Unit));

    if (0UL != (READ_REG32_BIT(PLAx->STAT, u32Unit))) {
        enState = ENABLE;
    }

    return enState;
}

/**
 * @brief  Set the MUX source of the PLA unit.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @param  [in] u32Ch                   PLA MUX channel
 *         This parameter can be one of the following values:
 *           @arg @ref PLA_MUX_Channel
 * @param  [in] u32Src                  Select the MUX source.
 *         This parameter can be one of the following values:
 *           @arg @ref PLA_MUX_Source
 * @retval None
 */
void PLA_SetMuxSrc(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, uint32_t u32Ch, uint32_t u32Src)
{
    __IO uint32_t *MUXS;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_PLA_PERIPH(PLAx));
    DDL_ASSERT(IS_PLA_UNIT(u32Unit));
    DDL_ASSERT(IS_PLA_MUX_CH(u32Ch));
    DDL_ASSERT(IS_PLA_MUX_SRC(u32Src));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            MUXS = PLA_MUXS_ADDR(PLAx, u32UnitPos);
            MODIFY_REG32(*MUXS, ((PLA_MUXS_MUX1 << (u32Ch << 2U)) | (PLA_MUXS_MUX1_4 << u32Ch)),
                         (((u32Src & 0x0FUL) << (u32Ch << 2U)) | ((u32Src & 0x10UL) << (10U + u32Ch))));
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Set the combinatorial logic of the PLA unit.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @param  [in] u32Value                Combinatorial logic value.
 *         This parameter can be a number between 0UL and 0xFFUL.
 * @retval None
 */
void PLA_SetCombLogic(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, uint32_t u32Value)
{
    __IO uint32_t *LUTCTL;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;
    uint32_t u32GctlVal;

    /* Check parameters */
    DDL_ASSERT(IS_PLA_PERIPH(PLAx));
    DDL_ASSERT(IS_PLA_UNIT(u32Unit));
    DDL_ASSERT(IS_PLA_COMB_LOGIC(u32Value));

    u32GctlVal = READ_REG32(PLAx->GCTL);
    WRITE_REG32(PLAx->GCTL, 0UL);
    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            LUTCTL = PLA_LUTCTL_ADDR(PLAx, u32UnitPos);
            WRITE_REG32(*LUTCTL, u32Value);
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
    WRITE_REG32(PLAx->GCTL, u32GctlVal);
}

/**
 * @brief  Enable or disable output of the PLA unit.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PLA_OutputCmd(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CTL;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_PLA_PERIPH(PLAx));
    DDL_ASSERT(IS_PLA_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            CTL = PLA_CTL_ADDR(PLAx, u32UnitPos);
            if (DISABLE != enNewState) {
                SET_REG32_BIT(*CTL, PLA_CTL_OEN);
            } else {
                CLR_REG32_BIT(*CTL, PLA_CTL_OEN);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the PLA unit.
 * @param  [in] PLAx                    Pointer to PLA unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_PLA or CM_PLAx: PLA unit instance
 * @param  [in] u32Unit                 The PLA unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref PLA_Unit
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void PLA_Cmd(CM_PLA_TypeDef *PLAx, uint32_t u32Unit, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_PLA_PERIPH(PLAx));
    DDL_ASSERT(IS_PLA_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(PLAx->GCTL, u32Unit);
    } else {
        CLR_REG32_BIT(PLAx->GCTL, u32Unit);
    }
}

/**
 * @}
 */

#endif /* LL_PLA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

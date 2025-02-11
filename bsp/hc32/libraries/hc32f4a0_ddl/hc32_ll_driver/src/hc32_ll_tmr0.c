/**
 *******************************************************************************
 * @file  hc32_ll_tmr0.c
 * @brief This file provides firmware functions to manage the TMR0
 *        (TMR0).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
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
#include "hc32_ll_tmr0.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TMR0 TMR0
 * @brief TMR0 Driver Library
 * @{
 */

#if (LL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Local_Macros TMR0 Local Macros
 * @{
 */
/* Max channel number */
#define TMR0_CH_MAX                     (2UL)

#define TMR0_CLK_SRC_MASK               (TMR0_BCONR_SYNSA | TMR0_BCONR_SYNCLKA | TMR0_BCONR_ASYNCLKA)
#define TMR0_BCONR_CLR_MASK             (TMR0_BCONR_CAPMDA | TMR0_BCONR_CKDIVA | TMR0_BCONR_HICPA | TMR0_CLK_SRC_MASK)

/**
 * @defgroup TMR0_Register_Address TMR0 Register Address
 * @{
 */
#define TMR0_CNTR_ADDR(__UNIT__, __CH__)    (__IO uint32_t*)((uint32_t)(&((__UNIT__)->CNTAR)) + ((__CH__) << 2UL))
#define TMR0_CMPR_ADDR(__UNIT__, __CH__)    (__IO uint32_t*)((uint32_t)(&((__UNIT__)->CMPAR)) + ((__CH__) << 2UL))
/**
 * @}
 */
#define TMR0_CH_OFFSET(__CH__)          ((__CH__) << 4U)

/**
 * @defgroup TMR0_Check_Parameters_Validity TMR0 Check Parameters Validity
 * @{
 */
#define IS_TMR0_UNIT(x)                                                        \
(   ((x) == CM_TMR0_1)                              ||                         \
    ((x) == CM_TMR0_2))

#define IS_TMR0_CH(x)                                                          \
(   ((x) == TMR0_CH_A)                              ||                         \
    ((x) == TMR0_CH_B))

#define IS_TMR0_CLK_SRC(x)                                                     \
(   ((x) == TMR0_CLK_SRC_INTERN_CLK)                ||                         \
    ((x) == TMR0_CLK_SRC_SPEC_EVT)                  ||                         \
    ((x) == TMR0_CLK_SRC_LRC)                       ||                         \
    ((x) == TMR0_CLK_SRC_XTAL32))

#define IS_TMR0_CLK_DIV(x)                                                     \
(   ((x) == TMR0_CLK_DIV1)                          ||                         \
    ((x) == TMR0_CLK_DIV2)                          ||                         \
    ((x) == TMR0_CLK_DIV4)                          ||                         \
    ((x) == TMR0_CLK_DIV8)                          ||                         \
    ((x) == TMR0_CLK_DIV16)                         ||                         \
    ((x) == TMR0_CLK_DIV32)                         ||                         \
    ((x) == TMR0_CLK_DIV64)                         ||                         \
    ((x) == TMR0_CLK_DIV128)                        ||                         \
    ((x) == TMR0_CLK_DIV256)                        ||                         \
    ((x) == TMR0_CLK_DIV512)                        ||                         \
    ((x) == TMR0_CLK_DIV1024))

#define IS_TMR0_FUNC(x)                                                        \
(   ((x) == TMR0_FUNC_CMP)                          ||                         \
    ((x) == TMR0_FUNC_CAPT))

#define IS_TMR0_INT(x)                                                         \
(   ((x) != 0U)                                     &&                         \
    (((x) | TMR0_INT_ALL) == TMR0_INT_ALL))

#define IS_TMR0_FLAG(x)                                                        \
(   ((x) != 0U)                                     &&                         \
    (((x) | TMR0_FLAG_ALL) == TMR0_FLAG_ALL))

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
 * @defgroup TMR0_Global_Functions TMR0 Global Functions
 * @{
 */

/**
 * @brief  De-Initialize TMR0 function
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @retval None
 */
void TMR0_DeInit(CM_TMR0_TypeDef *TMR0x)
{
    uint32_t u32Ch;
    __IO uint32_t *CNTR;
    __IO uint32_t *CMPR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));

    WRITE_REG32(TMR0x->BCONR, 0UL);
    WRITE_REG32(TMR0x->STFLR, 0UL);
    for (u32Ch = 0UL; u32Ch < TMR0_CH_MAX; u32Ch++) {
        CNTR = TMR0_CNTR_ADDR(TMR0x, u32Ch);
        WRITE_REG32(*CNTR, 0UL);
        CMPR = TMR0_CMPR_ADDR(TMR0x, u32Ch);
        WRITE_REG32(*CMPR, 0x0000FFFFUL);
    }
}

/**
 * @brief  Initialize TMR0 function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] pstcTmr0Init            Pointer to a @ref stc_tmr0_init_t.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcTmr0Init is NULL
 */
int32_t TMR0_Init(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, const stc_tmr0_init_t *pstcTmr0Init)
{
    __IO uint32_t *CNTR;
    __IO uint32_t *CMPR;
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTmr0Init) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
        DDL_ASSERT(IS_TMR0_CH(u32Ch));
        DDL_ASSERT(IS_TMR0_CLK_SRC(pstcTmr0Init->u32ClockSrc));
        DDL_ASSERT(IS_TMR0_CLK_DIV(pstcTmr0Init->u32ClockDiv));
        DDL_ASSERT(IS_TMR0_FUNC(pstcTmr0Init->u32Func));

        CNTR = TMR0_CNTR_ADDR(TMR0x, u32Ch);
        WRITE_REG32(*CNTR, 0UL);
        CMPR = TMR0_CMPR_ADDR(TMR0x, u32Ch);
        WRITE_REG32(*CMPR, pstcTmr0Init->u16CompareValue);
        MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CLR_MASK << TMR0_CH_OFFSET(u32Ch)),
                     ((pstcTmr0Init->u32ClockSrc | pstcTmr0Init->u32ClockDiv |
                       pstcTmr0Init->u32Func) << TMR0_CH_OFFSET(u32Ch)));
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_tmr0_init_t to default values.
 * @param  [out] pstcTmr0Init           Pointer to a @ref stc_tmr0_init_t structure.
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: pstcTmr0Init is NULL
 */
int32_t TMR0_StructInit(stc_tmr0_init_t *pstcTmr0Init)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTmr0Init) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcTmr0Init->u32ClockSrc       = TMR0_CLK_SRC_INTERN_CLK;
        pstcTmr0Init->u32ClockDiv       = TMR0_CLK_DIV1;
        pstcTmr0Init->u32Func           = TMR0_FUNC_CMP;
        pstcTmr0Init->u16CompareValue   = 0xFFFFU;
    }
    return i32Ret;
}

/**
 * @brief  Start TMR0.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @retval None
 */
void TMR0_Start(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_CSTA << TMR0_CH_OFFSET(u32Ch)));
}

/**
 * @brief  Stop TMR0.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @retval None
 */
void TMR0_Stop(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    CLR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_CSTA << TMR0_CH_OFFSET(u32Ch)));
}

/**
 * @brief  Set Tmr0 counter value.
 * @note   Setting the count requires stop tmr0.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] u16Value                The data to write to the counter register
 * @retval None
 */
void TMR0_SetCountValue(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint32_t *CNTR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    CNTR = TMR0_CNTR_ADDR(TMR0x, u32Ch);
    WRITE_REG32(*CNTR, u16Value);
}

/**
 * @brief  Get Tmr0 counter value.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @retval uint16_t                     The counter register data
 */
uint16_t TMR0_GetCountValue(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch)
{
    __IO uint32_t *CNTR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    CNTR = TMR0_CNTR_ADDR(TMR0x, u32Ch);
    return (uint16_t)READ_REG32(*CNTR);
}

/**
 * @brief  Set Tmr0 compare value.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] u16Value                The data to write to the compare register
 * @retval None
 */
void TMR0_SetCompareValue(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint16_t u16Value)
{
    __IO uint32_t *CMPR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    CMPR = TMR0_CMPR_ADDR(TMR0x, u32Ch);
    WRITE_REG32(*CMPR, u16Value);
}

/**
 * @brief  Get Tmr0 compare value.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @retval The compare register data
 */
uint16_t TMR0_GetCompareValue(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch)
{
    __IO uint32_t *CMPR;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));

    CMPR = TMR0_CMPR_ADDR(TMR0x, u32Ch);
    return (uint16_t)READ_REG32(*CMPR);
}

/**
 * @brief  Set clock source.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] u32Src                  Specifies the clock source
 *         This parameter can be a value of the following:
 *           @arg @ref TMR0_Clock_Source
 * @retval None
 */
void TMR0_SetClockSrc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_TMR0_CLK_SRC(u32Src));

    MODIFY_REG32(TMR0x->BCONR, (TMR0_CLK_SRC_MASK << TMR0_CH_OFFSET(u32Ch)), (u32Src << TMR0_CH_OFFSET(u32Ch)));
}

/**
 * @brief  Set the division of clock.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] u32Div                  Specifies the clock source division
 *         This parameter can be a value of the following:
 *           @arg TMR0_CLK_DIV1:        Clock source / 1
 *           @arg TMR0_CLK_DIV2:        Clock source / 2
 *           @arg TMR0_CLK_DIV4:        Clock source / 4
 *           @arg TMR0_CLK_DIV8:        Clock source / 8
 *           @arg TMR0_CLK_DIV16:       Clock source / 16
 *           @arg TMR0_CLK_DIV32:       Clock source / 32
 *           @arg TMR0_CLK_DIV64:       Clock source / 64
 *           @arg TMR0_CLK_DIV128:      Clock source / 128
 *           @arg TMR0_CLK_DIV256:      Clock source / 256
 *           @arg TMR0_CLK_DIV512:      Clock source / 512
 *           @arg TMR0_CLK_DIV1024:     Clock source / 1024
 * @retval None.
 */
void TMR0_SetClockDiv(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_TMR0_CLK_DIV(u32Div));

    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CKDIVA << TMR0_CH_OFFSET(u32Ch)), (u32Div << TMR0_CH_OFFSET(u32Ch)));
}

/**
 * @brief  Set Tmr0 Function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] u32Func                 Select TMR0 function
 *         This parameter can be a value of the following:
 *           @arg TMR0_FUNC_CMP:        Select the Compare function
 *           @arg TMR0_FUNC_CAPT:       Select the Capture function
 * @retval None
 */
void TMR0_SetFunc(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, uint32_t u32Func)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_TMR0_FUNC(u32Func));

    MODIFY_REG32(TMR0x->BCONR, ((TMR0_BCONR_CAPMDA | TMR0_BCONR_HICPA) << TMR0_CH_OFFSET(u32Ch)),
                 (u32Func << TMR0_CH_OFFSET(u32Ch)));
}

/**
 * @brief  Enable or disable HardWare trigger capture function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR0_HWCaptureCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HICPA << TMR0_CH_OFFSET(u32Ch)));
    } else {
        CLR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HICPA << TMR0_CH_OFFSET(u32Ch)));
    }
}

/**
 * @brief  Enable or disable HardWare trigger start function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR0_HWStartCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTAA << TMR0_CH_OFFSET(u32Ch)));
    } else {
        CLR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTAA << TMR0_CH_OFFSET(u32Ch)));
    }
}

/**
 * @brief  Enable or disable HardWare trigger stop function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR0_HWStopCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTPA << TMR0_CH_OFFSET(u32Ch)));
    } else {
        CLR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HSTPA << TMR0_CH_OFFSET(u32Ch)));
    }
}

/**
 * @brief  Enable or disable HardWare trigger clear function.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Ch                   TMR0 channel
 *         This parameter can be one of the following values:
 *           @arg @ref TMR0_Channel
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR0_HWClearCondCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HCLEA << TMR0_CH_OFFSET(u32Ch)));
    } else {
        CLR_REG32_BIT(TMR0x->BCONR, (TMR0_BCONR_HCLEA << TMR0_CH_OFFSET(u32Ch)));
    }
}

/**
 * @brief  Enable or disable specified Tmr0 interrupt.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32IntType              TMR0 interrupt type
 *         This parameter can be any combination value of the following values:
 *           @arg @ref TMR0_Interrupt.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR0_IntCmd(CM_TMR0_TypeDef *TMR0x, uint32_t u32IntType, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        SET_REG32_BIT(TMR0x->BCONR, u32IntType);
    } else {
        CLR_REG32_BIT(TMR0x->BCONR, u32IntType);
    }
}

/**
 * @brief  Get Tmr0 status.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Flag                 TMR0 flag type
 *         This parameter can be any combination value of the following values:
 *           @arg @ref TMR0_FLAG
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t TMR0_GetStatus(const CM_TMR0_TypeDef *TMR0x, uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(TMR0x->STFLR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear Tmr0 status.
 * @param  [in] TMR0x                   Pointer to TMR0 unit instance
 *         This parameter can be one of the following values:
 *           @arg CM_TMR0 or CM_TMR0_x: TMR0 unit instance
 * @param  [in] u32Flag                 TMR0 flag type
 *         This parameter can be any combination value of the following values:
 *           @arg @ref TMR0_FLAG
 * @retval None
 */
void TMR0_ClearStatus(CM_TMR0_TypeDef *TMR0x, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMR0_UNIT(TMR0x));
    DDL_ASSERT(IS_TMR0_FLAG(u32Flag));

    CLR_REG32_BIT(TMR0x->STFLR, u32Flag);
}

/**
 * @}
 */

#endif /* LL_TMR0_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

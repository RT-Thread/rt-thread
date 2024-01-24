/**
 *******************************************************************************
 * @file  hc32_ll_fcm.c
 * @brief This file provides firmware functions to manage the Frequency Clock
 *        Measurement (FCM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Modify parameter check for reference clock source
   2023-06-30       CDT             Modify API FCM_DeInit()
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
#include "hc32_ll_fcm.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_FCM FCM
 * @brief FCM Driver Library
 * @{
 */

#if (LL_FCM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FCM_Local_Macros FCM Local Macros
 * @{
 */

/* FCM Registers RESET Value */
#define FCM_REG_RST_VALUE     (0x00000000UL)

/* FCM interrupt mask */
#define FCM_INT_MASK          (FCM_INT_OVF | FCM_INT_END | FCM_INT_ERR)
/* FCM status flag mask */
#define FCM_FLAG_MASK         (FCM_SR_ERRF | FCM_SR_MENDF | FCM_SR_OVF)

/**
 * @defgroup FCM_Check_Parameters_Validity FCM Check Parameters Validity
 * @{
 */

/* Parameter validity check for FCM target and reference clock source. */
#define IS_FCM_TARGET_SRC(x)                                                 \
(   ((x) == FCM_TARGET_CLK_XTAL)          ||                                 \
    ((x) == FCM_TARGET_CLK_XTAL32)        ||                                 \
    ((x) == FCM_TARGET_CLK_HRC)           ||                                 \
    ((x) == FCM_TARGET_CLK_LRC)           ||                                 \
    ((x) == FCM_TARGET_CLK_SWDTLRC)       ||                                 \
    ((x) == FCM_TARGET_CLK_PCLK1)         ||                                 \
    ((x) == FCM_TARGET_CLK_PLLAP)         ||                                 \
    ((x) == FCM_TARGET_CLK_MRC)           ||                                 \
    ((x) == FCM_TARGET_CLK_PLLHP)         ||                                 \
    ((x) == FCM_TARGET_CLK_RTCLRC))

#define IS_FCM_REF_SRC(x)                                                    \
(   ((x) == FCM_REF_CLK_EXTCLK)           ||                                 \
    ((x) == FCM_REF_CLK_XTAL)             ||                                 \
    ((x) == FCM_REF_CLK_XTAL32)           ||                                 \
    ((x) == FCM_REF_CLK_HRC)              ||                                 \
    ((x) == FCM_REF_CLK_LRC)              ||                                 \
    ((x) == FCM_REF_CLK_SWDTLRC)          ||                                 \
    ((x) == FCM_REF_CLK_PCLK1)            ||                                 \
    ((x) == FCM_REF_CLK_PLLAP)            ||                                 \
    ((x) == FCM_REF_CLK_MRC)              ||                                 \
    ((x) == FCM_REF_CLK_PLLHP)            ||                                 \
    ((x) == FCM_REF_CLK_RTCLRC))

/* Parameter validity check for FCM target clock division. */
#define IS_FCM_TARGET_DIV(x)                                                 \
(   ((x) == FCM_TARGET_CLK_DIV1)          ||                                 \
    ((x) == FCM_TARGET_CLK_DIV4)          ||                                 \
    ((x) == FCM_TARGET_CLK_DIV8)          ||                                 \
    ((x) == FCM_TARGET_CLK_DIV32))

/* Parameter validity check for FCM external reference input function. */
#define IS_FCM_EXT_REF_FUNC(x)                                               \
(   ((x) == FCM_EXT_REF_OFF)              ||                                 \
    ((x) == FCM_EXT_REF_ON))

/* Parameter validity check for FCM reference clock edge. */
#define IS_FCM_REF_EDGE(x)                                                   \
(   ((x) == FCM_REF_CLK_RISING)           ||                                 \
    ((x) == FCM_REF_CLK_FALLING)          ||                                 \
    ((x) == FCM_REF_CLK_BOTH))

/* Parameter validity check for FCM digital filter function. */
#define IS_FCM_DIG_FILTER(x)                                                 \
(   ((x) == FCM_DIG_FILTER_OFF)           ||                                 \
    ((x) == FCM_DIG_FILTER_DIV1)          ||                                 \
    ((x) == FCM_DIG_FILTER_DIV4)          ||                                 \
    ((x) == FCM_DIG_FILTER_DIV16))

/* Parameter validity check for FCM reference clock division. */
#define IS_FCM_REF_DIV(x)                                                    \
(   ((x) == FCM_REF_CLK_DIV32)            ||                                 \
    ((x) == FCM_REF_CLK_DIV128)           ||                                 \
    ((x) == FCM_REF_CLK_DIV1024)          ||                                 \
    ((x) == FCM_REF_CLK_DIV8192))

/* Parameter validity check for FCM exception type function. */
#define IS_FCM_EXP_TYPE(x)                                                   \
(   ((x) == FCM_EXP_TYPE_INT)             ||                                 \
    ((x) == FCM_EXP_TYPE_RST))

/* Parameter validity check for FCM interrupt. */
#define IS_FCM_INT(x)      (((x) | FCM_INT_MASK) == FCM_INT_MASK)

/* Parameter validity check for FCM flag state. */
#define IS_FCM_FLAG(x)                                                       \
(   ((x) != 0x00UL)                       &&                                 \
    (((x) | FCM_FLAG_MASK) == FCM_FLAG_MASK))

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
 * @defgroup FCM_Global_Functions FCM Global Functions
 * @{
 */

/**
 * @brief  Initialize FCM.
 * @param  [in] pstcFcmInit         Pointer to a @ref stc_fcm_init_t structure
 *                                  that contains configuration information.
 * @retval int32_t:
 *       - LL_OK:                   FCM initialize successful
 *       - LL_ERR_INVD_PARAM:       Invalid parameter
 */
int32_t FCM_Init(const stc_fcm_init_t *pstcFcmInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Parameter validity checking */
        DDL_ASSERT(IS_FCM_TARGET_SRC(pstcFcmInit->u32TargetClock));
        DDL_ASSERT(IS_FCM_TARGET_DIV(pstcFcmInit->u32TargetClockDiv));
        DDL_ASSERT(IS_FCM_EXT_REF_FUNC(pstcFcmInit->u32ExtRefClockEnable));
        DDL_ASSERT(IS_FCM_REF_EDGE(pstcFcmInit->u32RefClockEdge));
        DDL_ASSERT(IS_FCM_DIG_FILTER(pstcFcmInit->u32DigitalFilter));
        DDL_ASSERT(IS_FCM_REF_SRC(pstcFcmInit->u32RefClock));
        DDL_ASSERT(IS_FCM_REF_DIV(pstcFcmInit->u32RefClockDiv));
        DDL_ASSERT(IS_FCM_EXP_TYPE(pstcFcmInit->u32ExceptionType));

        WRITE_REG32(CM_FCM->LVR, pstcFcmInit->u16LowerLimit);
        WRITE_REG32(CM_FCM->UVR, pstcFcmInit->u16UpperLimit);
        WRITE_REG32(CM_FCM->MCCR, (pstcFcmInit->u32TargetClock | pstcFcmInit->u32TargetClockDiv));
        WRITE_REG32(CM_FCM->RCCR, (pstcFcmInit->u32ExtRefClockEnable | pstcFcmInit->u32RefClockEdge |
                                   pstcFcmInit->u32DigitalFilter | pstcFcmInit->u32RefClock |
                                   pstcFcmInit->u32RefClockDiv));
        MODIFY_REG32(CM_FCM->RIER, FCM_RIER_ERRINTRS, pstcFcmInit->u32ExceptionType);
    }
    return i32Ret;
}

/**
 * @brief  Initialize FCM structure. Fill each pstcFcmInit with default value.
 * @param  [in] pstcFcmInit         Pointer to a @ref stc_fcm_init_t structure
 *                                  that contains configuration information.
 * @retval int32_t:
 *       - LL_OK:                   FCM structure initialize successful
 *       - LL_ERR_INVD_PARAM:       Invalid parameter
 */
int32_t FCM_StructInit(stc_fcm_init_t *pstcFcmInit)
{
    int32_t i32Ret = LL_OK;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* RESET FCM init structure parameters values */
        pstcFcmInit->u16LowerLimit = 0U;
        pstcFcmInit->u16UpperLimit = 0U;
        pstcFcmInit->u32TargetClock = FCM_TARGET_CLK_XTAL;
        pstcFcmInit->u32TargetClockDiv = FCM_TARGET_CLK_DIV1;
        pstcFcmInit->u32ExtRefClockEnable = FCM_EXT_REF_OFF;
        pstcFcmInit->u32RefClockEdge = FCM_REF_CLK_RISING;
        pstcFcmInit->u32DigitalFilter = FCM_DIG_FILTER_OFF;
        pstcFcmInit->u32RefClock = FCM_REF_CLK_XTAL;
        pstcFcmInit->u32RefClockDiv = FCM_REF_CLK_DIV32;
        pstcFcmInit->u32ExceptionType = FCM_EXP_TYPE_INT;
    }
    return i32Ret;
}

/**
 * @brief  De-Initialize FCM.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 */
int32_t FCM_DeInit(void)
{
    WRITE_REG32(CM_FCM->STR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->CLR, FCM_FLAG_MASK);
    WRITE_REG32(CM_FCM->LVR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->UVR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->MCCR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->RCCR, FCM_REG_RST_VALUE);
    WRITE_REG32(CM_FCM->RIER, FCM_REG_RST_VALUE);
    return LL_OK;
}

/**
 * @brief  Get FCM state, get FCM overflow, complete, error flag.
 * @param  [in] u32Flag         FCM flags.This parameter can be one or any
 *                              combination of the following values: @ref FCM_Flag_Sel
 *   @arg  FCM_FLAG_ERR:        FCM error.
 *   @arg  FCM_FLAG_END:        FCM measure end.
 *   @arg  FCM_FLAG_OVF:        FCM overflow.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t FCM_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    return ((READ_REG32_BIT(CM_FCM->SR, u32Flag) != 0UL) ? SET : RESET);
}

/**
 * @brief  Clear FCM state, Clear FCM overflow, complete, error flag.
 * @param  [in] u32Flag     FCM flags.This parameter can be one or any
 *                          combination of the following values: @ref FCM_Flag_Sel
 *   @arg  FCM_FLAG_ERR:    FCM error.
 *   @arg  FCM_FLAG_END:    FCM measure end.
 *   @arg  FCM_FLAG_OVF:    FCM overflow.
 * @retval None.
 */
void FCM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    SET_REG32_BIT(CM_FCM->CLR, u32Flag);
}

/**
 * @brief  Get FCM counter value.
 * @param  None
 * @retval FCM counter value.
 */
uint16_t FCM_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(CM_FCM->CNTR) & 0xFFFFU);
}

/**
 * @brief  FCM target clock type and division config.
 * @param  [in] u32ClockSrc Target clock type. @ref FCM_Target_Clock_Src
 * @param  [in] u32Div Target clock division. @ref FCM_Target_Clock_Div
 *   @arg  FCM_TARGET_CLK_DIV1
 *   @arg  FCM_TARGET_CLK_DIV4
 *   @arg  FCM_TARGET_CLK_DIV8
 *   @arg  FCM_TARGET_CLK_DIV32
 * @retval None.
 */
void FCM_SetTargetClock(uint32_t u32ClockSrc, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_TARGET_SRC(u32ClockSrc));
    DDL_ASSERT(IS_FCM_TARGET_DIV(u32Div));
    WRITE_REG32(CM_FCM->MCCR, (u32ClockSrc | u32Div));
}

/**
 * @brief  FCM reference clock type and division config.
 * @param  [in] u32ClockSrc Reference clock type. @ref FCM_Ref_Clock_Src
 * @param  [in] u32Div Reference clock division. @ref FCM_Ref_Clock_Div
 *   @arg  FCM_REF_CLK_DIV32
 *   @arg  FCM_REF_CLK_DIV128
 *   @arg  FCM_REF_CLK_DIV1024
 *   @arg  FCM_REF_CLK_DIV8192
 * @retval None.
 */
void FCM_SetRefClock(uint32_t u32ClockSrc, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_REF_SRC(u32ClockSrc));
    DDL_ASSERT(IS_FCM_REF_DIV(u32Div));
    MODIFY_REG32(CM_FCM->RCCR, (FCM_RCCR_INEXS | FCM_RCCR_RCKS | FCM_RCCR_RDIVS), (u32ClockSrc | u32Div));
}

/**
 * @brief  Enable or disable the FCM reset
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void FCM_ResetCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_FCM->RIER_b.ERRE, enNewState);
}

/**
 * @brief  Enable or disable the FCM interrupt
 * @param  [in] u32IntType      The FCM interrupt type. This parameter can be
 *                              one or any combination @ref FCM_Int_Type
 *    @arg FCM_INT_OVF:         FCM overflow interrupt
 *    @arg FCM_INT_END:         FCM calculate end interrupt
 *    @arg FCM_INT_ERR:         FCM frequency abnormal interrupt
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void FCM_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FCM_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_FCM->RIER, u32IntType);
    } else {
        CLR_REG32_BIT(CM_FCM->RIER, u32IntType);
    }
}

/**
 * @brief  FCM function config.
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None.
 */
void FCM_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_FCM->STR_b.START, enNewState);
}

/**
 * @}
 */

#endif /* LL_FCM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

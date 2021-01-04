/**
 *******************************************************************************
 * @file  hc32f4a0_fcm.c
 * @brief This file provides firmware functions to manage the Frequency Clock
 *        Measurement (FCM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-03-09       Zhangxl         First version
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
#include "hc32f4a0_fcm.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_FCM FCM
 * @brief FCM Driver Library
 * @{
 */

#if (DDL_FCM_ENABLE == DDL_ON)

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

/**
 * @defgroup FCM_Check_Parameters_Validity FCM Check Parameters Validity
 * @{
 */
/*! Parameter validity check for FCM target clock source. */
#define IS_FCM_TAR_SOURCE(src)                                                  \
(   ((src) == FCM_TAR_CLK_XTAL)             ||                                  \
    ((src) == FCM_TAR_CLK_XTAL32)           ||                                  \
    ((src) == FCM_TAR_CLK_HRC)              ||                                  \
    ((src) == FCM_TAR_CLK_LRC)              ||                                  \
    ((src) == FCM_TAR_CLK_SWDTLRC)          ||                                  \
    ((src) == FCM_TAR_CLK_PCLK1)            ||                                  \
    ((src) == FCM_TAR_CLK_PLLAP)            ||                                  \
    ((src) == FCM_TAR_CLK_MRC)              ||                                  \
    ((src) == FCM_TAR_CLK_PLLHP)            ||                                  \
    ((src) == FCM_TAR_CLK_RTCLRC))

/*! Parameter validity check for FCM target clock division. */
#define IS_FCM_TAR_DIV(div)                                                     \
(   ((div) == FCM_TAR_CLK_DIV1)             ||                                  \
    ((div) == FCM_TAR_CLK_DIV4)             ||                                  \
    ((div) == FCM_TAR_CLK_DIV8)             ||                                  \
    ((div) == FCM_TAR_CLK_DIV32))

/*! Parameter validity check for FCM external reference input function. */
#define IS_FCM_EX_REF_FUNC(func)                                                \
(   ((func) == FCM_EX_REF_OFF)              ||                                  \
    ((func) == FCM_EX_REF_ON))

/*! Parameter validity check for FCM reference clock edge. */
#define IS_FCM_REF_EDGE(edge)                                                   \
(   ((edge) == FCM_REF_CLK_RISING)          ||                                  \
    ((edge) == FCM_REF_CLK_FALLING)         ||                                  \
    ((edge) == FCM_REF_CLK_BOTH))

/*! Parameter validity check for FCM digital filter function. */
#define IS_FCM_DF(df)                                                           \
(   ((df) == FCM_DF_OFF)                    ||                                  \
    ((df) == FCM_DF_MCKS_DIV1)              ||                                  \
    ((df) == FCM_DF_MCKS_DIV4)              ||                                  \
    ((df) == FCM_DF_MCKS_DIV16))

/*! Parameter validity check for FCM reference clock source. */
#define IS_FCM_REF_SOURCE(src)                                                  \
(   ((src) == FCM_REF_CLK_EXINPUT)          ||                                  \
    ((src) == FCM_REF_CLK_XTAL)             ||                                  \
    ((src) == FCM_REF_CLK_XTAL32)           ||                                  \
    ((src) == FCM_REF_CLK_HRC)              ||                                  \
    ((src) == FCM_REF_CLK_LRC)              ||                                  \
    ((src) == FCM_REF_CLK_SWDTLRC)          ||                                  \
    ((src) == FCM_REF_CLK_PCLK1)            ||                                  \
    ((src) == FCM_REF_CLK_PCLKAP)           ||                                  \
    ((src) == FCM_REF_CLK_MRC)              ||                                  \
    ((src) == FCM_REF_CLK_PLLHP)            ||                                  \
    ((src) == FCM_REF_CLK_RTCLRC))

/*! Parameter validity check for FCM reference clock division. */
#define IS_FCM_REF_DIV(div)                                                     \
(   ((div) == FCM_REF_CLK_DIV32)            ||                                  \
    ((div) == FCM_REF_CLK_DIV128)           ||                                  \
    ((div) == FCM_REF_CLK_DIV1024)          ||                                  \
    ((div) == FCM_REF_CLK_DIV8192))

/*! Parameter validity check for FCM abnormal reset function. */
#define IS_FCM_RESET_FUNC(func)                                                 \
(   ((func) == FCM_RST_OFF)                 ||                                  \
    ((func) == FCM_RST_ON))

/*! Parameter validity check for FCM abnormal behavior function. */
#define IS_FCM_ERR_HANDLE(hd)                                                   \
(   ((hd) == FCM_ERR_INT)                   ||                                  \
    ((hd) == FCM_ERR_RESET))

/*! Parameter validity check for FCM interrupt. */
#define IS_FCM_INT(it)      (((it) | FCM_INT_MSK) == FCM_INT_MSK)

/*! Parameter validity check for FCM flag state. */
#define IS_FCM_FLAG(flag)                                                       \
(   ((flag) != 0x00UL)                      &&                                  \
    (((flag) | FCM_FLAG_MSK) == FCM_FLAG_MSK))

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
 * @param  [in] pstcFcmInit Pointer to a stc_fcm_init_t structure
 *                                 that contains configuration information.
 * @retval Ok: FCM initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t FCM_Init(const stc_fcm_init_t *pstcFcmInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_FCM_TAR_SOURCE(pstcFcmInit->u32TarClk));
        DDL_ASSERT(IS_FCM_TAR_DIV(pstcFcmInit->u32TarClkDiv));
        DDL_ASSERT(IS_FCM_EX_REF_FUNC(pstcFcmInit->u32ExRefClkEn));
        DDL_ASSERT(IS_FCM_REF_EDGE(pstcFcmInit->u32RefClkEdge));
        DDL_ASSERT(IS_FCM_DF(pstcFcmInit->u32DigFilter));
        DDL_ASSERT(IS_FCM_REF_SOURCE(pstcFcmInit->u32RefClk));
        DDL_ASSERT(IS_FCM_REF_DIV(pstcFcmInit->u32RefClkDiv));
        DDL_ASSERT(IS_FCM_RESET_FUNC(pstcFcmInit->u32RstEn));
        DDL_ASSERT(IS_FCM_ERR_HANDLE(pstcFcmInit->u32IntRstSel));
        DDL_ASSERT(IS_FCM_INT(pstcFcmInit->u32IntType));

        WRITE_REG32(M4_FCM->LVR, pstcFcmInit->u16LowerLimit);
        WRITE_REG32(M4_FCM->UVR, pstcFcmInit->u16UpperLimit);
        WRITE_REG32(M4_FCM->MCCR, (pstcFcmInit->u32TarClk | pstcFcmInit->u32TarClkDiv));
        WRITE_REG32(M4_FCM->RCCR, (pstcFcmInit->u32ExRefClkEn | pstcFcmInit->u32RefClkEdge |    \
                                   pstcFcmInit->u32DigFilter  | pstcFcmInit->u32RefClk     |    \
                                   pstcFcmInit->u32RefClkDiv));
        WRITE_REG32(M4_FCM->RIER, (pstcFcmInit->u32RstEn | pstcFcmInit->u32IntRstSel |    \
                                   pstcFcmInit->u32IntType));
    }
    return enRet;
}

/**
 * @brief  Initialize FCM structure. Fill each pstcFcmInit with
 *         default value
 * @param  [in] pstcFcmInit Pointer to a stc_fcm_init_t structure
 *                                 that contains configuration information.
 * @retval Ok: FCM structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t FCM_StructInit(stc_fcm_init_t *pstcFcmInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcFcmInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Reset FCM init structure parameters values */
        pstcFcmInit->u16LowerLimit = 0U;
        pstcFcmInit->u16UpperLimit = 0U;
        pstcFcmInit->u32TarClk = FCM_TAR_CLK_XTAL;
        pstcFcmInit->u32TarClkDiv = FCM_TAR_CLK_DIV1;
        pstcFcmInit->u32ExRefClkEn = FCM_EX_REF_OFF;
        pstcFcmInit->u32RefClkEdge = FCM_REF_CLK_RISING;
        pstcFcmInit->u32DigFilter = FCM_DF_OFF;
        pstcFcmInit->u32RefClk = FCM_REF_CLK_XTAL;
        pstcFcmInit->u32RefClkDiv = FCM_REF_CLK_DIV32;
        pstcFcmInit->u32RstEn = FCM_RST_OFF;
        pstcFcmInit->u32IntRstSel = FCM_ERR_INT;
        pstcFcmInit->u32IntType = (FCM_ERR_INT_OFF | FCM_END_INT_OFF | FCM_OVF_INT_OFF);
    }
    return enRet;
}

/**
 * @brief  De-Initialize FCM.
 * @param  None
 * @retval None
 */
void FCM_DeInit(void)
{
    WRITE_REG32(M4_FCM->STR, FCM_REG_RESET_VALUE);
    WRITE_REG32(M4_FCM->CLR, FCM_FLAG_MSK);
    WRITE_REG32(M4_FCM->LVR, FCM_REG_RESET_VALUE);
    WRITE_REG32(M4_FCM->UVR, FCM_REG_RESET_VALUE);
    WRITE_REG32(M4_FCM->MCCR,FCM_REG_RESET_VALUE);
    WRITE_REG32(M4_FCM->RCCR,FCM_REG_RESET_VALUE);
    WRITE_REG32(M4_FCM->RIER,FCM_REG_RESET_VALUE);
}

/**
 * @brief  Get FCM state, get FCM overflow, complete, error flag.
 * @param  [in] u32Flag FCM flags.
 *   @arg  FCM_FLAG_ERR: FCM error.
 *   @arg  FCM_FLAG_END: FCM measure end.
 *   @arg  FCM_FLAG_OVF: FCM overflow.
 * @retval en_flag_status_t: FCM flag status.
 */
en_flag_status_t FCM_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    return (READ_REG32_BIT(M4_FCM->SR, u32Flag) ? Set : Reset);
}

/**
 * @brief  Clear FCM state, Clear FCM overflow, complete, error flag.
 * @param  [in] u32Flag FCM flags.
 *   @arg  FCM_FLAG_ERR: FCM error.
 *   @arg  FCM_FLAG_END: FCM measure end.
 *   @arg  FCM_FLAG_OVF: FCM overflow.
 *   @arg  FCM_FLAG_MSK: All above 3 flags of FCM.
 * @retval None.
 */
void FCM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_FCM_FLAG(u32Flag));

    SET_REG32_BIT(M4_FCM->CLR, u32Flag);
}

/**
 * @brief  Get FCM counter value.
 * @param  None
 * @retval FCM counter value.
 */
uint16_t FCM_GetCounter(void)
{
    return (uint16_t)(READ_REG32(M4_FCM->CNTR) & 0xFFFFU);
}

/**
 * @brief  FCM target clock type and division config.
 * @param  [in] u32Tar Target clock type.
 *   @arg  FCM_TAR_CLK_XTAL
 *   @arg  FCM_TAR_CLK_XTAL32
 *   @arg  FCM_TAR_CLK_HRC
 *   @arg  FCM_TAR_CLK_LRC
 *   @arg  FCM_TAR_CLK_SWDTLRC
 *   @arg  FCM_TAR_CLK_PCLK1
 *   @arg  FCM_TAR_CLK_PLLAP
 *   @arg  FCM_TAR_CLK_MRC
 *   @arg  FCM_TAR_CLK_PLLHP
 *   @arg  FCM_TAR_CLK_RTCLRC
 * @param  [in] u32Div Target clock division.
 *   @arg  FCM_TAR_CLK_DIV1
 *   @arg  FCM_TAR_CLK_DIV4
 *   @arg  FCM_TAR_CLK_DIV8
 *   @arg  FCM_TAR_CLK_DIV32
 * @retval None.
 */
void FCM_SetTarClk(uint32_t u32Tar, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_TAR_SOURCE(u32Tar));
    DDL_ASSERT(IS_FCM_TAR_DIV(u32Div));
    WRITE_REG32(M4_FCM->MCCR, (u32Tar | u32Div));
}

/**
 * @brief  FCM reference clock type and division config.
 * @param  [in] u32Ref Reference clock type.
 *   @arg  FCM_REF_CLK_EXINPUT
 *   @arg  FCM_REF_CLK_XTAL
 *   @arg  FCM_REF_CLK_XTAL32
 *   @arg  FCM_REF_CLK_HRC
 *   @arg  FCM_REF_CLK_LRC
 *   @arg  FCM_REF_CLK_SWDTLRC
 *   @arg  FCM_REF_CLK_PCLK1
 *   @arg  FCM_REF_CLK_PCLKAP
 *   @arg  FCM_REF_CLK_MRC
 *   @arg  FCM_REF_CLK_PLLHP
 *   @arg  FCM_REF_CLK_RTCLRC
 * @param  [in] u32Div Reference clock division.
 *   @arg  FCM_REF_CLK_DIV32
 *   @arg  FCM_REF_CLK_DIV128
 *   @arg  FCM_REF_CLK_DIV1024
 *   @arg  FCM_REF_CLK_DIV8192
 * @retval None.
 */
void FCM_SetRefClk(uint32_t u32Ref, uint32_t u32Div)
{
    DDL_ASSERT(IS_FCM_REF_SOURCE(u32Ref));
    DDL_ASSERT(IS_FCM_REF_DIV(u32Div));
    MODIFY_REG32(M4_FCM->RCCR,                                                  \
                (FCM_RCCR_INEXS | FCM_RCCR_RCKS | FCM_RCCR_RDIVS),              \
                (u32Ref | u32Div));
}

/**
 * @brief  FCM function config.
 * @param  [in] enNewState
 *   @arg  Enable
 *   @arg  Disable
 * @retval None.
 */
void FCM_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bM4_FCM->STR_b.START, enNewState);
}

/**
 * @}
 */

#endif /* DDL_FCM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

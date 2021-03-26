/**
 *******************************************************************************
 * @file  hc32f4a0_tmr2.c
 * @brief This file provides firmware functions to manage the TMR2(Timer2).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
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
#include "hc32f4a0_tmr2.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR2 TMR2
 * @brief TMR2 Driver Library
 * @{
 */
#if (DDL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR2_Local_Macros TMR2 Local Macros
 * @{
 */

/**
 * @defgroup TMR2_Configuration_Bit_Mask TMR2 Configuration Bit Mask
 * @{
 */
#define TMR2_BCONR_INIT_MSK                 (TMR2_BCONR_CAPMDA | TMR2_BCONR_SYNSA | TMR2_BCONR_SYNCLKA | TMR2_BCONR_ASYNCLKA | \
                                             TMR2_BCONR_CKDIVA | TMR2_BCONR_SYNCLKAT_0 | TMR2_BCONR_SYNCLKAT_1)
#define TMR2_FUNC_MODE_MSK                  (TMR2_BCONR_CAPMDA)
#define TMR2_CLK_SRC_MSK                    (TMR2_BCONR_SYNSA |TMR2_BCONR_SYNCLKA |TMR2_BCONR_ASYNCLKA | TMR2_BCONR_SYNCLKAT_0 | \
                                             TMR2_BCONR_SYNCLKAT_1)
#define TMR2_CLK_DIV_MSK                    (TMR2_BCONR_CKDIVA)
#define TMR2_PWM_START_POLARITY_MSK         (TMR2_PCONR_STACA)
#define TMR2_PWM_STOP_POLARITY_MSK          (TMR2_PCONR_STPCA)
#define TMR2_PWM_CMP_POLARITY_MSK           (TMR2_PCONR_CMPCA)
#define TMR2_PWM_POLARITY_MSK               (TMR2_PCONR_STACA | TMR2_PCONR_STPCA | TMR2_PCONR_CMPCA)
#define TMR2_FILTER_CLK_DIV_MSK             (TMR2_PCONR_NOFICKA)
#define TMR2_START_COND_MSK                 (TMR2_HCONR_HSTAA0 | TMR2_HCONR_HSTAA1 | TMR2_HCONR_HSTAA2)
#define TMR2_STOP_COND_MSK                  (TMR2_HCONR_HSTPA0 | TMR2_HCONR_HSTPA1 | TMR2_HCONR_HSTPA2)
#define TMR2_CLR_COND_MSK                   (TMR2_HCONR_HCLEA0 | TMR2_HCONR_HCLEA1 | TMR2_HCONR_HCLEA2)
#define TMR2_CAPT_COND_MSK                  (TMR2_HCONR_HICPA0 | TMR2_HCONR_HICPA1 | TMR2_HCONR_HICPA2)
#define TMR2_TRIG_COND_MSK                  (TMR2_START_COND_MSK | TMR2_STOP_COND_MSK | TMR2_CLR_COND_MSK | TMR2_CAPT_COND_MSK)
#define TMR2_INT_TYPE_MSK                   (TMR2_ICONR_CMENA | TMR2_ICONR_OVENA)
#define TMR2_COM_TRIG_MSK                   (TMR2_COM_TRIG1 | TMR2_COM_TRIG2)
#define TMR2_TRIG_EVENT_MSK                 (AOS_TMR2_HTSSR_TRGSEL)
/**
 * @}
 */

/**
 * @defgroup TMR2_Channel_Cfg_Bit_Field_Offset TMR2 Channel Configuration Bit Field Offset
 * @{
 */
#define TMR2_BCONR_OFFSET                   (TMR2_BCONR_CSTB_POS)
#define TMR2_ICONR_OFFSET                   (TMR2_ICONR_CMENB_POS)
#define TMR2_PCONR_OFFSET                   (TMR2_PCONR_STACB_POS)
#define TMR2_HCONR_OFFSET                   (TMR2_HCONR_HSTAB0_POS)
/**
 * @}
 */

/**
 * @defgroup TMR2_Register_Bit_Band TMR2 Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                     (0x42000000UL)
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(regAddr)                  ((regAddr) - __PERIP_BASE)
#define __BIT_BAND_ADDR(regAddr, pos)       ((__REG_OFS(regAddr) << 5U) + ((uint32_t)(pos) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(regAddr, pos)              (*(__IO uint32_t *)__BIT_BAND_ADDR((regAddr), (pos)))
/**
 * @}
 */

/**
 * @defgroup TMR2_Check_Parameters_Validity TMR2 check parameters validity
 * @{
 */
#define IS_TMR2_UNIT(x)                                                        \
(   ((x) == M4_TMR2_1)                       ||                                \
    ((x) == M4_TMR2_2)                       ||                                \
    ((x) == M4_TMR2_3)                       ||                                \
    ((x) == M4_TMR2_4))

#define IS_TMR2_CH(x)                                                          \
(   ((x) <= TMR2_CH_B))

#define IS_TMR2_FUNC_MODE(x)                                                   \
(   ((x) == TMR2_FUNC_COMPARE)              ||                                 \
    ((x) == TMR2_FUNC_CAPTURE))

#define IS_TMR2_CLK_SRC(x)                                                     \
(   ((x) == TMR2_CLK_SYNC_PCLK1)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TRIGR)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TRIGF)            ||                                 \
    ((x) == TMR2_CLK_SYNC_EVENT)            ||                                 \
    ((x) == TMR2_CLK_SYNC_TIMER6_OVF)       ||                                 \
    ((x) == TMR2_CLK_SYNC_TIMER6_UDF)       ||                                 \
    ((x) == TMR2_CLK_ASYNC_LRC)             ||                                 \
    ((x) == TMR2_CLK_ASYNC_XTAL32)          ||                                 \
    ((x) == TMR2_CLK_ASYNC_PIN_CLK))

#define IS_TMR2_STATUS_FLAG(x)                                                 \
(   ((x) == TMR2_FLAG_CMP)                  ||                                 \
    ((x) == TMR2_FLAG_OVF))

#define IS_TMR2_CLK_DIV(x)                                                     \
(   ((x) == TMR2_CLK_DIV1)                  ||                                 \
    ((x) == TMR2_CLK_DIV2)                  ||                                 \
    ((x) == TMR2_CLK_DIV4)                  ||                                 \
    ((x) == TMR2_CLK_DIV8)                  ||                                 \
    ((x) == TMR2_CLK_DIV16)                 ||                                 \
    ((x) == TMR2_CLK_DIV32)                 ||                                 \
    ((x) == TMR2_CLK_DIV64)                 ||                                 \
    ((x) == TMR2_CLK_DIV128)                ||                                 \
    ((x) == TMR2_CLK_DIV256)                ||                                 \
    ((x) == TMR2_CLK_DIV512)                ||                                 \
    ((x) == TMR2_CLK_DIV1024))

#define IS_TMR2_FILTER_CLK_DIV(x)                                              \
(   ((x) == TMR2_FILTER_CLK_DIV1)           ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV4)           ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV16)          ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV64))

#define IS_TMR2_PWM_START_POLARITY(x)                                          \
(   ((x) == TMR2_PWM_START_LOW)             ||                                 \
    ((x) == TMR2_PWM_START_HIGH)            ||                                 \
    ((x) == TMR2_PWM_START_KEEP))

#define IS_TMR2_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMR2_PWM_STOP_LOW)              ||                                 \
    ((x) == TMR2_PWM_STOP_HIGH)             ||                                 \
    ((x) == TMR2_PWM_STOP_KEEP))

#define IS_TMR2_PWM_CMP_POLARITY(x)                                            \
(   ((x) == TMR2_PWM_CMP_LOW)               ||                                 \
    ((x) == TMR2_PWM_CMP_HIGH)              ||                                 \
    ((x) == TMR2_PWM_CMP_KEEP)              ||                                 \
    ((x) == TMR2_PWM_CMP_REVERSE))

#define IS_TMR2_COM_TRIGGER(x)                                                 \
(   ((x) != 0U)                             &&                                 \
    (((x) | TMR2_COM_TRIG_MSK) == TMR2_COM_TRIG_MSK))

#define IS_TMR2_VALID_VAL(x)                                                   \
(   (x) <= 0xFFFFUL)

/**
 * @}
 */

/**
 * @defgroup TMR2_Miscellaneous_Macros TMR2 Miscellaneous Macros
 * @{
 */
#define TMR2_CH_COUNT                       (2U)
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
 * @defgroup TMR2_Global_Functions TMR2 Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified TMR2 channel according to the specified parameters \
 *         in the structure stc_tmr2_init_t
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  pstcInit               Pointer to a stc_tmr2_init_t structure value that \
 *                                      contains the configuration information for the TMR2 channel.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t TMR2_Init(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_init_t *pstcInit)
{
    uint32_t u32Temp;
    uint32_t u32CMPRAddr;
    uint32_t u32CNTRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
        DDL_ASSERT(IS_TMR2_FUNC_MODE(pstcInit->u32FuncMode));
        DDL_ASSERT(IS_TMR2_CLK_SRC(pstcInit->u32ClkSrc));
        DDL_ASSERT(IS_TMR2_CLK_DIV(pstcInit->u32ClkDiv));
        DDL_ASSERT(IS_TMR2_VALID_VAL(pstcInit->u32CmpVal));
        DDL_ASSERT(IS_TMR2_VALID_VAL(pstcInit->u32CntVal));

        u32Temp     = (uint32_t)u8Tmr2Ch * 4U;
        u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + u32Temp;
        u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + u32Temp;
        RW_MEM32(u32CMPRAddr) = pstcInit->u32CmpVal;
        RW_MEM32(u32CNTRAddr) = pstcInit->u32CntVal;

        u32Temp = pstcInit->u32FuncMode | \
                  pstcInit->u32ClkSrc   | \
                  pstcInit->u32ClkDiv;

        /* Channel bit filed offset. */
        u8Tmr2Ch *= TMR2_BCONR_OFFSET;
        MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_INIT_MSK << u8Tmr2Ch), (u32Temp << u8Tmr2Ch));

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for TMR2 initialization structure.
 * @param  [in]  pstcInit               Pointer to a stc_tmr2_init_t structure that
 *                                      contains configuration information.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No errors occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t TMR2_StructInit(stc_tmr2_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u32FuncMode = TMR2_FUNC_COMPARE;
        pstcInit->u32ClkSrc   = TMR2_CLK_SYNC_PCLK1;
        pstcInit->u32ClkDiv   = TMR2_CLK_DIV1;
        pstcInit->u32CmpVal   = 0xFFFFUL;
        pstcInit->u32CntVal   = 0U;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the specified TMR2 unit.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @retval None
 */
void TMR2_DeInit(M4_TMR2_TypeDef *TMR2x)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));

    TMR2_Stop(TMR2x, TMR2_CH_A);
    TMR2_Stop(TMR2x, TMR2_CH_B);

    CLEAR_REG32(TMR2x->CNTAR);
    CLEAR_REG32(TMR2x->CNTBR);
    CLEAR_REG32(TMR2x->BCONR);
    CLEAR_REG32(TMR2x->ICONR);
    CLEAR_REG32(TMR2x->PCONR);
    CLEAR_REG32(TMR2x->HCONR);
    CLEAR_REG32(TMR2x->STFLR);

    WRITE_REG32(TMR2x->CMPAR, 0xFFFFU);
    WRITE_REG32(TMR2x->CMPBR, 0xFFFFU);
}

/**
 * @brief  Configures the specified channel's PWM output polarity according to the specified \
 *         parameters in the structure stc_tmr2_pwm_cfg_t
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  pstcCfg                Pointer to a stc_tmr2_pwm_cfg_t structure value that contains \
 *                                      the configuration information for the PWM output polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMR2_PWM_Config(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_pwm_cfg_t *pstcCfg)
{
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
        DDL_ASSERT(IS_TMR2_PWM_START_POLARITY(pstcCfg->u32StartPolarity));
        DDL_ASSERT(IS_TMR2_PWM_STOP_POLARITY(pstcCfg->u32StopPolarity));
        DDL_ASSERT(IS_TMR2_PWM_CMP_POLARITY(pstcCfg->u32CmpPolarity));

        u32Cfg = pstcCfg->u32StartPolarity | \
                 pstcCfg->u32StopPolarity  | \
                 pstcCfg->u32CmpPolarity;
        u8Tmr2Ch *= TMR2_PCONR_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, (TMR2_PWM_POLARITY_MSK << u8Tmr2Ch), (u32Cfg << u8Tmr2Ch));

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for TMR2 PWM configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_tmr2_pwm_cfg_t structure value that contains \
 *                                      the configuration information for the PWM output polarity.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMR2_PWM_StructInit(stc_tmr2_pwm_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u32StartPolarity = TMR2_PWM_START_HIGH;
        pstcCfg->u32StopPolarity  = TMR2_PWM_STOP_LOW;
        pstcCfg->u32CmpPolarity   = TMR2_PWM_CMP_REVERSE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable PWM output of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable PWM output of the specified TMR2's channel.
 *   @arg  Disable:                     Disable PWM output of the specified TMR2's channel.
 * @retval None
 */
void TMR2_PWM_Cmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint8_t au8EnPos[] = {TMR2_PCONR_OUTENA_POS, TMR2_PCONR_OUTENB_POS};

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&TMR2x->PCONR;
    BIT_BAND(u32Addr, au8EnPos[u8Tmr2Ch]) = (uint32_t)enNewState;
}

/**
 * @brief  Specify the channel's hardware trigger condition according to the specified \
 *         parameters in the structure stc_tmr2_trig_cond_t
 * @param  [in]  TMR2x                      Pointer to TMR2 instance register base.
 *                                          This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                       TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                       TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                       TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                       TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch                   The channel number of TMR2.
 *                                          This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                       Channel A of TMR2.
 *   @arg  TMR2_CH_B:                       Channel B of TMR2.
 * @param  [in]  pstcCond                   Pointer to a stc_tmr2_trig_cond_t structure value that contains \
 *                                          the configuration information for the hardware condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                              No error occurred.
 *   @arg  ErrorInvalidParameter:           pstcCond == NULL.
 */
en_result_t TMR2_SetTrigCond(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_trig_cond_t *pstcCond)
{
    uint32_t u32Cfg;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
        DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));

        u32Cfg  = (pstcCond->u32StartCond | \
                   pstcCond->u32StopCond  | \
                   pstcCond->u32ClrCond   | \
                   pstcCond->u32CaptCond) & TMR2_TRIG_COND_MSK;
        u8Tmr2Ch *= TMR2_HCONR_OFFSET;
        MODIFY_REG32(TMR2x->HCONR, (TMR2_TRIG_COND_MSK << u8Tmr2Ch), (u32Cfg << u8Tmr2Ch));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for TMR2 hardware trigger condition structure.
 * @param  [in]  pstcCond               Pointer to a stc_tmr2_trig_cond_t structure value that contains \
 *                                      the configuration information for the hardware condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCond == NULL.
 */
en_result_t TMR2_TrigCondStructInit(stc_tmr2_trig_cond_t *pstcCond)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        pstcCond->u32StartCond = TMR2_START_COND_INVALID;
        pstcCond->u32StopCond  = TMR2_STOP_COND_INVALID;
        pstcCond->u32ClrCond   = TMR2_CLR_COND_INVALID;
        pstcCond->u32CaptCond  = TMR2_CAPT_COND_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set trigger source for TMR2.
 * @param  [in]  enEvent                An en_event_src_t enumeration type value.
 * @retval None
 */
void TMR2_SetTriggerSrc(en_event_src_t enEvent)
{
    MODIFY_REG32(M4_AOS->TMR2_HTSSR, TMR2_TRIG_EVENT_MSK, enEvent);
}

/**
 * @brief  Enable or disable common trigger event for the specified usage.
 * @param  [in]  u32ComTrig             Common trigger event enable bit mask.
 *                                      This parameter can be a value of @ref TMR2_Common_Trigger_Sel
 *   @arg  TMR2_COM_TRIG1:              Common trigger 1.
 *   @arg  TMR2_COM_TRIG2:              Common trigger 2.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified common trigger.
 *   @arg Disable:                      Disable the specified common trigger.
 * @retval None
 */
void TMR2_ComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_COM_TRIGGER(u32ComTrig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG32_BIT(M4_AOS->TMR2_HTSSR, u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(M4_AOS->TMR2_HTSSR, u32ComTrig);
    }
}

/**
 * @brief  Set clock divider for the filter of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32ClkDiv              Clock divider for the specified TMR2 unit channel filter.
 *                                      This parameter can be a value of @ref TMR2_Filter_Clock_Divider
 *   @arg  TMR2_FILTER_CLK_DIV1:        Clock source.
 *   @arg  TMR2_FILTER_CLK_DIV4:        Clock source / 4.
 *   @arg  TMR2_FILTER_CLK_DIV16:       Clock source / 16.
 *   @arg  TMR2_FILTER_CLK_DIV64:       Clock source / 64.
 * @retval None
 */
void TMR2_FilterConfig(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_FILTER_CLK_DIV(u32ClkDiv));

    u8Tmr2Ch *= TMR2_PCONR_OFFSET;
    MODIFY_REG32(TMR2x->PCONR, \
                 (TMR2_FILTER_CLK_DIV_MSK << u8Tmr2Ch), \
                 (u32ClkDiv << u8Tmr2Ch));
}

/**
 * @brief  Enable or disable the filter of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the filter of the specified channel.
 *   @arg  Disable:                     Disable the filter of the specified channel.
 * @retval None
 */
void TMR2_FilterCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState)
{
    uint32_t u32Addr;
    uint8_t au8EnPos[] = {TMR2_PCONR_NOFIENA_POS, TMR2_PCONR_NOFIENB_POS};

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&TMR2x->PCONR;
    BIT_BAND(u32Addr, au8EnPos[u8Tmr2Ch]) = (uint32_t)enNewState;
}

/**
 * @brief  Enable or disable the interrupt of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32IntType             The interrupt type.
 *                                      This parameter can be a value(s) of @ref TMR2_Interrupt_Type
 *   @arg  TMR2_INT_CMP:                TMR2 count match interrupt.
 *   @arg  TMR2_INT_OVF:                TMR2 count overflow interrupt.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the specified interrupt.
 *   @arg  Disable:                     Disable the specified interrupt.
 * @retval None
 */
void TMR2_IntCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, \
                 uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Tmr2Ch    *= TMR2_ICONR_OFFSET;
    u32IntType  &= TMR2_INT_TYPE_MSK;
    u32IntType <<= u8Tmr2Ch;

    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMR2x->ICONR, u32IntType);
    }
    else
    {
        CLEAR_REG32_BIT(TMR2x->ICONR, u32IntType);
    }
}

/**
 * @brief  Start the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @retval None
 */
void TMR2_Start(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t au32Cfg[] = {TMR2_BCONR_CSTA, TMR2_BCONR_CSTB};

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    SET_REG32_BIT(TMR2x->BCONR, au32Cfg[u8Tmr2Ch]);
}

/**
 * @brief  Stop the specified channel of the specified TMR2 unit.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @retval None
 */
void TMR2_Stop(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t au32Cfg[] = {TMR2_BCONR_CSTA, TMR2_BCONR_CSTB};

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    CLEAR_REG32_BIT(TMR2x->BCONR, au32Cfg[u8Tmr2Ch]);
}

/**
 * @brief  Get the specified flag's status of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Flag                TMR2 state flag.
 *                                      This parameter can be values of @ref TMR2_State_Flag
 *   @arg  TMR2_FLAG_CMP:               Counting match flag.
 *   @arg  TMR2_FLAG_OVF:               Counting overflow flag.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         At least one of the specified flags is set.
 *   @arg  Reset:                       None of the specified flags is set.
 */
en_flag_status_t TMR2_GetStatus(const M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag)
{
    en_flag_status_t enFlag = Reset;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_STATUS_FLAG(u32Flag));

    u32Flag  &= TMR2_FLAG_ALL;
    u32Flag <<= ((uint32_t)u8Tmr2Ch * TMR2_ICONR_OFFSET);
    if (READ_REG32_BIT(TMR2x->STFLR, u32Flag) != 0U)
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear the specified flag state of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Flag                TMR2 state flag.
 *                                      This parameter can be values of @ref TMR2_State_Flag
 *   @arg  TMR2_FLAG_CMP:               Counter match flag of channel A/B.
 *   @arg  TMR2_FLAG_OVF:               Counter overflow flag of channel A/B.
 * @retval None
 */
void TMR2_ClrStatus(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));

    /* Bit filed offset. */
    u8Tmr2Ch *= TMR2_ICONR_OFFSET;
    u32Flag  &= TMR2_FLAG_ALL;
    u32Flag <<= u8Tmr2Ch;
    CLEAR_REG32_BIT(TMR2x->STFLR, u32Flag);
}

/**
 * @brief  Set compare value for the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Val                 The compare reference value for the specified TMR2's channel.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMR2_SetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val)
{
    uint32_t u32CMPRAddr;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_VALID_VAL(u32Val));
    u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + (uint32_t)u8Tmr2Ch * 4U;
    RW_MEM32(u32CMPRAddr) = u32Val;
}

/**
 * @brief  Get compare value of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @retval The compare value of the specified TMR2's channel. A number between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMR2_GetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t u32CMPRAddr;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));

    u32CMPRAddr = (uint32_t)&TMR2x->CMPAR + (uint32_t)u8Tmr2Ch * 4U;
    return RW_MEM32(u32CMPRAddr);
}

/**
 * @brief  Set counter value for the specified channel of the specified TMR2 unit.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel of the specified TMR2 unit.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Val                 The counter value for the specified TMR2's channel.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMR2_SetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val)
{
    uint32_t u32CNTRAddr;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_VALID_VAL(u32Val));

    u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + (uint32_t)u8Tmr2Ch * 4U;
    RW_MEM32(u32CNTRAddr) = u32Val;
}

/**
 * @brief  Get counter value of the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @retval The counter value of the specified TMR2's channel. A number between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMR2_GetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch)
{
    uint32_t u32CNTRAddr;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    u32CNTRAddr = (uint32_t)&TMR2x->CNTAR + (uint32_t)u8Tmr2Ch * 4U;

    return RW_MEM32(u32CNTRAddr);
}

/**
 * @brief  Set function mode for the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32FuncMode            Specifies the function for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_Function_Mode
 *   @arg  TMR2_FUNC_COMPARE:           Set the function of the specified channel of TMR2 unit as compare output.
 *   @arg  TMR2_FUNC_CAPTURE:           Set the function of the specified channel of TMR2 unit as capturing input.
 * @retval None
 */
void TMR2_SetFuncMode(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32FuncMode)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_FUNC_MODE(u32FuncMode));

    /* Bit filed offset. */
    u8Tmr2Ch *= TMR2_BCONR_OFFSET;
    u32Msk    = TMR2_FUNC_MODE_MSK << u8Tmr2Ch;
    u32Cfg    = u32FuncMode << u8Tmr2Ch;
    MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);
}

/**
 * @brief  Specify the clock source for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32ClkSrc              Specifies the clock source for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_Clock_Source
 *   @arg  TMR2_SYNC_CLK_PCLK1:         Synchronous clock source, PCLK1.
 *   @arg  TMR2_SYNC_CLK_TRIG_RISE:     Synchronous clock source, rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_SYNC_CLK_TRIG_FALL:     Synchronous clock source, falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_SYNC_CLK_EVENT:         Synchronous clock source, peripheral event.
 *   @arg  TMR2_CLK_SYNC_TIMER6_OVF:    Synchronous clock source, the event of counting overflow of TIMER6. \
 *                                      It is NOT need to set register TMR2_HTSSR.
 *   @arg  TMR2_CLK_SYNC_TIMER6_UDF:    Synchronous clock source, the event of counting underflow of TIMER6. \
 *                                      It is NOT need to set register TMR2_HTSSR.
 *   @arg  TMR2_ASYNC_CLK_LRC:          Asynchronous clock source, LRC.
 *   @arg  TMR2_ASYNC_CLK_XTAL32:       Asynchronous clock source, XTAL32.
 *   @arg  TMR2_ASYNC_CLK_PIN_CLK:      Asynchronous clock source, from pin TIM2_x_CLKA/B.
 * @retval None
 */
void TMR2_SetClkSrc(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkSrc)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_CLK_SRC(u32ClkSrc));

    /* Bit filed offset. */
    u8Tmr2Ch *= TMR2_BCONR_OFFSET;
    u32Msk    = TMR2_CLK_SRC_MSK << u8Tmr2Ch;
    u32Cfg    = u32ClkSrc << u8Tmr2Ch;
    MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);
}

/**
 * @brief  Specify the division of the clock source for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32ClkDiv              Specifies the clock source division for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_Clock_Divider
 *   @arg  TMR2_CLK_DIV1:               Clock source.
 *   @arg  TMR2_CLK_DIV2:               Clock source / 2.
 *   @arg  TMR2_CLK_DIV4:               Clock source / 4.
 *   @arg  TMR2_CLK_DIV8:               Clock source / 8.
 *   @arg  TMR2_CLK_DIV16:              Clock source / 16.
 *   @arg  TMR2_CLK_DIV32:              Clock source / 32.
 *   @arg  TMR2_CLK_DIV64:              Clock source / 64.
 *   @arg  TMR2_CLK_DIV128:             Clock source / 128.
 *   @arg  TMR2_CLK_DIV256:             Clock source / 256.
 *   @arg  TMR2_CLK_DIV512:             Clock source / 512.
 *   @arg  TMR2_CLK_DIV1024:            Clock source / 1024.
 * @retval None
 */
void TMR2_SetClkDiv(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv)
{
    uint32_t u32Msk;
    uint32_t u32Cfg;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_CLK_DIV(u32ClkDiv));

    /* Bit filed offset. */
    u8Tmr2Ch *= TMR2_BCONR_OFFSET;
    u32Msk    = TMR2_CLK_DIV_MSK << u8Tmr2Ch;
    u32Cfg    = u32ClkDiv << u8Tmr2Ch;
    MODIFY_REG32(TMR2x->BCONR, u32Msk, u32Cfg);
}

/**
 * @brief  Enable or disable the specified trigger conditions of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Cond                The specified conditions.
 *                                      This parameter can be a value of
 *                                      @ref TMR2_Hardware_Start_Condition \
 *                                      @ref TMR2_Hardware_Stop_Condition  \
 *                                      @ref TMR2_Hardware_Clear_Condition \
 *                                      @ref TMR2_Hardware_Capture_Condition
 *   @arg  TMR2_START_COND_TRIG_RISE:   The condition of start is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_START_COND_TRIG_FALL:   The condition of start is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_START_COND_EVENT:       The condition of start is the specified event occurred.
 *   @arg  TMR2_STOP_COND_TRIG_RISE:    The condition of stop is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_STOP_COND_TRIG_FALL:    The condition of stop is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_STOP_COND_EVENT:        The condition of stop is the specified event occurred.
 *   @arg  TMR2_CLR_COND_TRIG_RISE:     The condition of clear(clear CNTAR/CNTBR) is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CLR_COND_TRIG_FALL:     The condition of clear(clear CNTAR/CNTBR) is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CLR_COND_EVENT:         The condition of clear(clear CNTAR/CNTBR) is the specified event occurred.
 *   @arg  TMR2_CAPT_COND_TRIG_RISE:    The condition for capturing is the rising edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CAPT_COND_TRIG_FALL:    The condition for capturing is the falling edge of TIM2_x_TRIGA/B.
 *   @arg  TMR2_CAPT_COND_EVENT:        The condition for capturing is the specified event occurred.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the sepcified trigger conditions.
 *   @arg  Disable:                     Disable the sepcified trigger conditions.
 * @retval None
 */
void TMR2_TrigCondCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Cond  &= TMR2_TRIG_COND_MSK;
    u8Tmr2Ch *= TMR2_HCONR_OFFSET;
    u32Cond <<= u8Tmr2Ch;
    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
    else
    {
        CLEAR_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
}

/**
 * @brief  Set PWM polarity when counting start for the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Polarity            Specifies the PWM start polarity for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Start_Polarity
 *   @arg  TMR2_PWM_START_LOW:          PWM output low when counting start.
 *   @arg  TMR2_PWM_START_HIGH:         PWM output high when counting start.
 *   @arg  TMR2_PWM_START_KEEP:         PWM output keeps the current polarity when counting start.
 * @retval None
 */
void TMR2_PWM_SetStartPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_PWM_START_POLARITY(u32Polarity));

    u8Tmr2Ch *= TMR2_PCONR_OFFSET;
    MODIFY_REG32(TMR2x->PCONR, \
                 (TMR2_PWM_START_POLARITY_MSK << u8Tmr2Ch), \
                 (u32Polarity << u8Tmr2Ch));
}

/**
 * @brief  Set PWM polarity when counting stop for the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Polarity            Specifies the PWM stop polarity for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Stop_Polarity
 *   @arg  TMR2_PWM_STOP_LOW:           PWM output low when counting stop.
 *   @arg  TMR2_PWM_STOP_HIGH:          PWM output high when counting stop.
 *   @arg  TMR2_PWM_STOP_KEEP:          PWM output keeps the current polarity when counting stop.
 * @retval None
 */
void TMR2_PWM_SetStopPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_PWM_STOP_POLARITY(u32Polarity));

    u8Tmr2Ch *= TMR2_PCONR_OFFSET;
    MODIFY_REG32(TMR2x->PCONR, \
                 (TMR2_PWM_STOP_POLARITY_MSK << u8Tmr2Ch), \
                 (u32Polarity << u8Tmr2Ch));
}

/**
 * @brief  Set PWM polarity when counting compare match for the specified TMR2's channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMR2_1:                   TMR2 unit 1 instance register base.
 *   @arg  M4_TMR2_2:                   TMR2 unit 2 instance register base.
 *   @arg  M4_TMR2_3:                   TMR2 unit 3 instance register base.
 *   @arg  M4_TMR2_4:                   TMR2 unit 4 instance register base.
 * @param  [in]  u8Tmr2Ch               The channel number of TMR2.
 *                                      This parameter can be a value of @ref TMR2_Channel_Number
 *   @arg  TMR2_CH_A:                   Channel A of TMR2.
 *   @arg  TMR2_CH_B:                   Channel B of TMR2.
 * @param  [in]  u32Polarity            Specifies the PWM count match polarity for the specified TMR2's channel.
 *                                      This parameter can be a value of @ref TMR2_PWM_Cmp_Polarity
 *   @arg  TMR2_PWM_CMP_LOW:            PWM output low when counting compare match.
 *   @arg  TMR2_PWM_CMP_HIGH:           PWM output high when counting compare match.
 *   @arg  TMR2_PWM_CMP_KEEP:           PWM output keeps the current polarity when counting compare match.
 *   @arg  TMR2_PWM_CMP_REVERSE:        PWM output reverses the current polarity when counting compare match.
 * @retval None
 */
void TMR2_PWM_SetCmpPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u8Tmr2Ch));
    DDL_ASSERT(IS_TMR2_PWM_CMP_POLARITY(u32Polarity));

    u8Tmr2Ch *= TMR2_PCONR_OFFSET;
    MODIFY_REG32(TMR2x->PCONR, \
                 (TMR2_PWM_CMP_POLARITY_MSK << u8Tmr2Ch), \
                 (u32Polarity << u8Tmr2Ch));
}

/**
 * @}
 */

#endif /* DDL_TMR2_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

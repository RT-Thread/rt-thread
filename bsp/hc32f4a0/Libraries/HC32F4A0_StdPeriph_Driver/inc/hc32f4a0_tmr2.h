/**
 *******************************************************************************
 * @file  hc32f4a0_tmr2.h
 * @brief This file contains all the functions prototypes of the TMR2(Timer2)
 *        driver library.
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
#ifndef __HC32F4A0_TMR2_H__
#define __HC32F4A0_TMR2_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_TMR2
 * @{
 */
#if (DDL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Types TMR2 Global Types
 * @{
 */

/**
 * @brief TMR2 initialization structure.
 */
typedef struct
{
    uint32_t u32FuncMode;                   /*!< Specify the function mode for TMR2's channel.
                                                 This parameter can be a value of @ref TMR2_Function_Mode */
    uint32_t u32ClkSrc;                     /*!< Specify the clock source for TMR2's channel.
                                                 This parameter can be a value of @ref TMR2_Clock_Source */
    uint32_t u32ClkDiv;                     /*!< Specify the division of the clock source.
                                                 This parameter can be a value of @ref TMR2_Clock_Divider */
    uint32_t u32CmpVal;                     /*!< Specify the compare value depends on your application.
                                                 This parameter can be a number between 0U and 0xFFFFU, inclusive. */
    uint32_t u32CntVal;                     /*!< Initial value of the count register.
                                                 This parameter can be a number between 0U and 0xFFFFU, inclusive. */
} stc_tmr2_init_t;

/**
 * @brief TMR2 PWM output polarity configuration structure.
 */
typedef struct
{
    uint32_t u32StartPolarity;              /*!< Specify the polarity of PWM output when TMR2 counting start.
                                                 This parameter can be a value of @ref TMR2_PWM_Start_Polarity */
    uint32_t u32StopPolarity;               /*!< Specify the polarity of PWM output when TMR2 counting stop.
                                                 This parameter can be a value of @ref TMR2_PWM_Stop_Polarity */
    uint32_t u32CmpPolarity;                /*!< Specify the polarity of PWM output when TMR2 counting matches the compare value.
                                                 This parameter can be a value of @ref TMR2_PWM_Cmp_Polarity */
} stc_tmr2_pwm_cfg_t;

/**
 * @brief TMR2 hardware trigger condition configuration structure.
 */
typedef struct
{
    uint32_t u32StartCond;                  /*!< Specify the trigger condition of start counting.
                                                 This parameter can be a value of @ref TMR2_Hardware_Start_Condition */
    uint32_t u32StopCond;                   /*!< Specify the trigger condition of stop counting.
                                                 This parameter can be a value of @ref TMR2_Hardware_Stop_Condition */
    uint32_t u32ClrCond;                    /*!< Specify the trigger condition of clearing counter register.
                                                 This parameter can be a value of @ref TMR2_Hardware_Clear_Condition */
    uint32_t u32CaptCond;                   /*!< Specify the trigger condition of start capturing.
                                                 This parameter can be a value of @ref TMR2_Hardware_Capture_Condition */
} stc_tmr2_trig_cond_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Macros TMR2 Global Macros
 * @{
 */

/**
 * @defgroup TMR2_Channel_Number TMR2 Channel Number
 * @{
 */
#define TMR2_CH_A                       (0U)                            /*!< Channel A of TMR2. */
#define TMR2_CH_B                       (1U)                            /*!< Channel B of TMR2. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Function_Mode TMR2 Function Mode
 * @{
 */
#define TMR2_FUNC_COMPARE               (0x0U)                          /*!< The function mode of TMR2 is comparison ouput. */
#define TMR2_FUNC_CAPTURE               (TMR2_BCONR_CAPMDA)             /*!< The function mode of TMR2 is capture the input. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Divider TMR2 Clock Divider
 * @{
 */
#define TMR2_CLK_DIV1                   (0x0U)                          /*!< Clock source. */
#define TMR2_CLK_DIV2                   (TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 2. */
#define TMR2_CLK_DIV4                   (TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 4. */
#define TMR2_CLK_DIV8                   (TMR2_BCONR_CKDIVA_1 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 8. */
#define TMR2_CLK_DIV16                  (TMR2_BCONR_CKDIVA_2)           /*!< Clock source / 16. */
#define TMR2_CLK_DIV32                  (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 32. */
#define TMR2_CLK_DIV64                  (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 64. */
#define TMR2_CLK_DIV128                 (TMR2_BCONR_CKDIVA_2 | \
                                         TMR2_BCONR_CKDIVA_1 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 128. */
#define TMR2_CLK_DIV256                 (TMR2_BCONR_CKDIVA_3)           /*!< Clock source / 256. */
#define TMR2_CLK_DIV512                 (TMR2_BCONR_CKDIVA_3 | \
                                         TMR2_BCONR_CKDIVA_0)           /*!< Clock source / 512. */
#define TMR2_CLK_DIV1024                (TMR2_BCONR_CKDIVA_3 | \
                                         TMR2_BCONR_CKDIVA_1)           /*!< Clock source / 1024. */

/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Source TMR2 Clock Source
 * @{
 */
#define TMR2_CLK_SYNC_PCLK1             (0x0U)                          /*!< Synchronous clock source, PCLK1. */
#define TMR2_CLK_SYNC_TRIGR             (TMR2_BCONR_SYNCLKA_0)          /*!< Synchronous clock source, rising edge of TIM2_x_TRIGA/B. \
                                                                             One rising edge causes one count. */
#define TMR2_CLK_SYNC_TRIGF             (TMR2_BCONR_SYNCLKA_1)          /*!< Synchronous clock source, falling edge of TIM2_x_TRIGA/B. \
                                                                             One falling edge causes one count. */
#define TMR2_CLK_SYNC_EVENT             (TMR2_BCONR_SYNCLKA)            /*!< Synchronous clock source, peripheral event. The event is specified by register TMR2_HTSSR. \
                                                                             The event causes one count. */
#define TMR2_CLK_SYNC_TIMER6_OVF        (TMR2_BCONR_SYNCLKAT_0)         /*!< Synchronous clock source, the event of counting overflow of TIMER6. \
                                                                             It is NO need to set register TMR2_HTSSR. */
#define TMR2_CLK_SYNC_TIMER6_UDF        (TMR2_BCONR_SYNCLKAT_1)         /*!< Synchronous clock source, the event of counting underflow of TIMER6. \
                                                                             It is NO need to set register TMR2_HTSSR. */
#define TMR2_CLK_ASYNC_LRC              (TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, LRC(32.768KHz). */
#define TMR2_CLK_ASYNC_XTAL32           (TMR2_BCONR_ASYNCLKA_0 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, XTAL32(32.768KHz). */
#define TMR2_CLK_ASYNC_PIN_CLK          (TMR2_BCONR_ASYNCLKA_1 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, input from pin TIM2_x_CLKA/B. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Interrupt_Type TMR2 Interrupt Type
 * @{
 */
#define TMR2_INT_CMP                    (TMR2_ICONR_CMENA)              /*!< TMR2 count match interrupt. */
#define TMR2_INT_OVF                    (TMR2_ICONR_OVENA)              /*!< TMR2 count overflow interrupt. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Start_Polarity TMR2 PWM Start Polarity
 * @{
 */
#define TMR2_PWM_START_LOW              (0x0U)                          /*!< PWM output low when counting start. */
#define TMR2_PWM_START_HIGH             (TMR2_PCONR_STACA_0)            /*!< PWM output high when counting start. */
#define TMR2_PWM_START_KEEP             (TMR2_PCONR_STACA_1)            /*!< PWM output keeps the current polarity when counting start. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Stop_Polarity TMR2 PWM Stop Polarity
 * @{
 */
#define TMR2_PWM_STOP_LOW               (0x0U)                          /*!< PWM output low when counting stop. */
#define TMR2_PWM_STOP_HIGH              (TMR2_PCONR_STPCA_0)            /*!< PWM output high when counting stop. */
#define TMR2_PWM_STOP_KEEP              (TMR2_PCONR_STPCA_1)            /*!< PWM output keeps the current polarity when counting stop. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Cmp_Polarity TMR2 PWM Polarity When Counting Compare Matches The Compare Value
 * @{
 */
#define TMR2_PWM_CMP_LOW                (0x0U)                          /*!< PWM output low when counting match. */
#define TMR2_PWM_CMP_HIGH               (TMR2_PCONR_CMPCA_0)            /*!< PWM output high when counting match. */
#define TMR2_PWM_CMP_KEEP               (TMR2_PCONR_CMPCA_1)            /*!< PWM output keeps the current polarity when counting match. */
#define TMR2_PWM_CMP_REVERSE            (TMR2_PCONR_CMPCA_1 | \
                                         TMR2_PCONR_CMPCA_0)            /*!< PWM output reverses the current polarity when counting match. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Filter_Clock_Divider TMR2 Filter Clock Divider
 * @{
 */
#define TMR2_FILTER_CLK_DIV1            (0x0U)                          /*!< Clock source. */
#define TMR2_FILTER_CLK_DIV4            (TMR2_PCONR_NOFICKA_0)          /*!< Clock source / 4. */
#define TMR2_FILTER_CLK_DIV16           (TMR2_PCONR_NOFICKA_1)          /*!< Clock source / 16. */
#define TMR2_FILTER_CLK_DIV64           (TMR2_PCONR_NOFICKA)            /*!< Clock source / 64. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Start_Condition TMR2 Hardware Start Condition
 * @{
 */
#define TMR2_START_COND_INVALID         (0x0U)                          /*!< The start condition of TMR2 is INVALID. */
#define TMR2_START_COND_TRIGR           (TMR2_HCONR_HSTAA0)  /*!< The start condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_TRIGF           (TMR2_HCONR_HSTAA1)  /*!< The start condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_EVENT           (TMR2_HCONR_HSTAA2)  /*!< The start condition of TMR2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Stop_Condition TMR2 Hardware Stop Condition
 * @{
 */
#define TMR2_STOP_COND_INVALID          (0x0U)                          /*!< The stop condition of TMR2 is INVALID. */
#define TMR2_STOP_COND_TRIGR            (TMR2_HCONR_HSTPA0)             /*!< The stop condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_TRIGF            (TMR2_HCONR_HSTPA1)             /*!< The stop condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_EVENT            (TMR2_HCONR_HSTPA2)             /*!< The stop condition of TMR2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Clear_Condition TMR2 Hardware Clear Condition
 * @{
 */
#define TMR2_CLR_COND_INVALID           (0x0U)                          /*!< The clear condition of TMR2 is INVALID. */
#define TMR2_CLR_COND_TRIGR             (TMR2_HCONR_HCLEA0)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_TRIGF             (TMR2_HCONR_HCLEA1)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_EVENT             (TMR2_HCONR_HCLEA2)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Hardware_Capture_Condition TMR2 Hardware Capture Condition
 * @{
 */
#define TMR2_CAPT_COND_INVALID          (0x0U)                          /*!< The capture condition of TMR2 is INVALID. */
#define TMR2_CAPT_COND_TRIGR            (TMR2_HCONR_HICPA0)             /*!< The capture condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_TRIGF            (TMR2_HCONR_HICPA1)             /*!< The capture condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_EVENT            (TMR2_HCONR_HICPA2)             /*!< The capture condition of TMR2 is the specified event occurred. */
/**
 * @}
 */

/**
 * @defgroup TMR2_State_Flag TMR2 State Flag
 * @{
 */
#define TMR2_FLAG_CMP                   (TMR2_STFLR_CMFA)               /*!< Counter match flag. */
#define TMR2_FLAG_OVF                   (TMR2_STFLR_OVFA)               /*!< Counter overflow flag. */
#define TMR2_FLAG_ALL                   (TMR2_FLAG_CMP | TMR2_FLAG_OVF)
/**
 * @}
 */

/**
 * @defgroup TMR2_Common_Trigger_Sel TMR2 Common Trigger Source Select
 * @{
 */
#define TMR2_COM_TRIG1                  (AOS_TMR2_HTSSR_COMTRG_EN_0)
#define TMR2_COM_TRIG2                  (AOS_TMR2_HTSSR_COMTRG_EN_1)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup TMR2_Global_Functions
 * @{
 */
     en_result_t TMR2_Init(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_init_t *pstcInit);
     en_result_t TMR2_StructInit(stc_tmr2_init_t *pstcInit);
            void TMR2_DeInit(M4_TMR2_TypeDef *TMR2x);

     en_result_t TMR2_PWM_Config(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_pwm_cfg_t *pstcCfg);
     en_result_t TMR2_PWM_StructInit(stc_tmr2_pwm_cfg_t *pstcCfg);
            void TMR2_PWM_Cmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState);

     en_result_t TMR2_SetTrigCond(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, const stc_tmr2_trig_cond_t *pstcCond);
     en_result_t TMR2_TrigCondStructInit(stc_tmr2_trig_cond_t *pstcCond);
            void TMR2_SetTriggerSrc(en_event_src_t enEvent);
            void TMR2_ComTriggerCmd(uint32_t u32ComTrig, en_functional_state_t enNewState);

            void TMR2_FilterConfig(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv);
            void TMR2_FilterCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, en_functional_state_t enNewState);

            void TMR2_IntCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, \
                             uint32_t u32IntType, en_functional_state_t enNewState);

            void TMR2_Start(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);
            void TMR2_Stop(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

en_flag_status_t TMR2_GetStatus(const M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag);
            void TMR2_ClrStatus(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Flag);

            void TMR2_SetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val);
        uint32_t TMR2_GetCmpVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

            void TMR2_SetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Val);
        uint32_t TMR2_GetCntVal(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch);

            void TMR2_SetFuncMode(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32FuncMode);

            void TMR2_SetClkSrc(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkSrc);
            void TMR2_SetClkDiv(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32ClkDiv);

            void TMR2_TrigCondCmd(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Cond, en_functional_state_t enNewState);

            void TMR2_PWM_SetStartPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);
            void TMR2_PWM_SetStopPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);
            void TMR2_PWM_SetCmpPolarity(M4_TMR2_TypeDef *TMR2x, uint8_t u8Tmr2Ch, uint32_t u32Polarity);

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

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMR2_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

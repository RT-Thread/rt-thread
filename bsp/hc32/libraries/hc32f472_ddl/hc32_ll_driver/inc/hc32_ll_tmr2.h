/**
 *******************************************************************************
 * @file  hc32_ll_tmr2.h
 * @brief This file contains all the functions prototypes of the TMR2(Timer2)
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
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
#ifndef __HC32_LL_TMR2_H__
#define __HC32_LL_TMR2_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_TMR2
 * @{
 */
#if (LL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMR2_Global_Types TMR2 Global Types
 * @{
 */

/**
 * @brief TMR2 PWM configuration structure.
 */
typedef struct {
    uint32_t u32StartPolarity;          /*!< Specifies the polarity of PWM output when TMR2 counting start.
                                             This parameter can be a value of @ref TMR2_PWM_Polarity */
    uint32_t u32StopPolarity;           /*!< Specifies the polarity of PWM output when TMR2 counting stop.
                                             This parameter can be a value of @ref TMR2_PWM_Polarity */
    uint32_t u32CompareMatchPolarity;   /*!< Specifies the polarity of PWM output when TMR2 counter matches the compare value.
                                             This parameter can be a value of @ref TMR2_PWM_Polarity */
} stc_tmr2_pwm_init_t;

/**
 * @brief TMR2 initialization structure.
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Specifies the clock source for TMR2 channel.
                                             This parameter can be a value of @ref TMR2_Clock_Source */
    uint32_t u32ClockDiv;               /*!< Specifies the division of the clock source.
                                             This parameter can be a value of @ref TMR2_Clock_Divider */
    uint32_t u32Func;                   /*!< Specifies the function mode for TMR2 channel.
                                             This parameter can be a value of @ref TMR2_Function */
    uint32_t u32CompareValue;           /*!< Specifies the compare value.
                                             This parameter can be a number between 0U and 0xFFFFU, inclusive. */
} stc_tmr2_init_t;

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
 * @defgroup TMR2_Channel TMR2 Channel
 * @{
 */
#define TMR2_CH_A                       (0U)                            /*!< Channel A of TMR2. */
#define TMR2_CH_B                       (1U)                            /*!< Channel B of TMR2. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Function TMR2 Function
 * @{
 */
#define TMR2_FUNC_CMP                   (0x0U)                          /*!< The function of TMR2 channel is ouput compare. */
#define TMR2_FUNC_CAPT                  (TMR2_BCONR_CAPMDA)             /*!< The function of TMR2 channel is input capture. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Source TMR2 Clock Source
 * @{
 */
#define TMR2_CLK_PCLK1                  (0x0U)                          /*!< Synchronous clock source, PCLK1. */
#define TMR2_CLK_TRIG_RISING            (TMR2_BCONR_SYNCLKA_0)          /*!< Synchronous clock source, rising edge of TIM2_<t>_TRIGA/B.
                                                                             One rising edge causes one count. */
#define TMR2_CLK_TRIG_FALLING           (TMR2_BCONR_SYNCLKA_1)          /*!< Synchronous clock source, falling edge of TIM2_<t>_TRIGA/B.
                                                                             One falling edge causes one count. */
#define TMR2_CLK_EVT                    (TMR2_BCONR_SYNCLKA)            /*!< Synchronous clock source, peripheral event. The event is specified by register TMR2_HTSSR.
                                                                             One event causes one count. */
#define TMR2_CLK_TMR6_OVF               (TMR2_BCONR_SYNCLKAT_0)         /*!< Synchronous clock source, the event of counting overflow of TIMER6.
                                                                             It is NOT need to set register TMR2_HTSSR. */
#define TMR2_CLK_TMR6_UDF               (TMR2_BCONR_SYNCLKAT_1)         /*!< Synchronous clock source, the event of counting underflow of TIMER6.
                                                                             It is NOT need to set register TMR2_HTSSR. */
#define TMR2_CLK_TMR6_OVF_UDF           (TMR2_BCONR_SYNCLKAT_0 | \
                                         TMR2_BCONR_SYNCLKAT_1)         /*!< Synchronous clock source, both overflow and underflow of TIMER6. */
#define TMR2_CLK_LRC                    (TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, LRC(32.768KHz). */
#define TMR2_CLK_XTAL32                 (TMR2_BCONR_ASYNCLKA_0 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, XTAL32(32.768KHz). */
#define TMR2_CLK_PIN_CLK                (TMR2_BCONR_ASYNCLKA_1 | \
                                         TMR2_BCONR_SYNSA)              /*!< Asynchronous clock source, input from pin TIM2_<t>_CLKA/B. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Clock_Divider TMR2 Clock Divider
 * @{
 */
#define TMR2_CLK_DIV1                   (0x0U)                              /*!< Clock source. */
#define TMR2_CLK_DIV2                   (0x1UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 2. */
#define TMR2_CLK_DIV4                   (0x2UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 4. */
#define TMR2_CLK_DIV8                   (0x3UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 8. */
#define TMR2_CLK_DIV16                  (0x4UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 16. */
#define TMR2_CLK_DIV32                  (0x5UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 32. */
#define TMR2_CLK_DIV64                  (0x6UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 64. */
#define TMR2_CLK_DIV128                 (0x7UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 128. */
#define TMR2_CLK_DIV256                 (0x8UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 256. */
#define TMR2_CLK_DIV512                 (0x9UL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 512. */
#define TMR2_CLK_DIV1024                (0xAUL << TMR2_BCONR_CKDIVA_POS)    /*!< Clock source / 1024. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Interrupt_Type TMR2 Interrupt Type
 * @{
 */
#define TMR2_INT_MATCH_CH_A             (TMR2_ICONR_CMENA)              /*!< TMR2 count match interrupt. */
#define TMR2_INT_OVF_CH_A               (TMR2_ICONR_OVENA)              /*!< TMR2 count overflow interrupt. */
#define TMR2_INT_MATCH_CH_B             (TMR2_ICONR_CMENB)              /*!< TMR2 count match interrupt. */
#define TMR2_INT_OVF_CH_B               (TMR2_ICONR_OVENB)              /*!< TMR2 count overflow interrupt. */
#define TMR2_INT_ALL                    (TMR2_INT_MATCH_CH_A | TMR2_INT_OVF_CH_A | \
                                         TMR2_INT_MATCH_CH_B | TMR2_INT_OVF_CH_B)
/**
 * @}
 */

/**
 * @defgroup TMR2_Status_Flag TMR2 Status Flag
 * @{
 */
#define TMR2_FLAG_MATCH_CH_A            (TMR2_STFLR_CMFA)               /*!< Counter match flag of channel A. */
#define TMR2_FLAG_OVF_CH_A              (TMR2_STFLR_OVFA)               /*!< Counter overflow flag channel A. */
#define TMR2_FLAG_MATCH_CH_B            (TMR2_STFLR_CMFB)               /*!< Counter match flag channel B. */
#define TMR2_FLAG_OVF_CH_B              (TMR2_STFLR_OVFB)               /*!< Counter overflow flag channel B. */
#define TMR2_FLAG_CAPT_AGAIN_CH_A       (TMR2_STFLR_ICPA)               /*!< Capture occurs again after successful capture of channel A */
#define TMR2_FLAG_CAPT_AGAIN_CH_B       (TMR2_STFLR_ICPB)               /*!< Capture occurs again after successful capture of channel B */
#define TMR2_FLAG_ALL                   (TMR2_FLAG_MATCH_CH_A | TMR2_FLAG_OVF_CH_A | \
                                         TMR2_FLAG_MATCH_CH_B | TMR2_FLAG_OVF_CH_B | \
                                         TMR2_FLAG_CAPT_AGAIN_CH_A | TMR2_FLAG_CAPT_AGAIN_CH_B)
/**
 * @}
 */

/**
 * @defgroup TMR2_Counter_State TMR2 Counter State
 * @{
 */
#define TMR2_CNT_STAT_START             (0U)                            /*!< Counter start counting. */
#define TMR2_CNT_STAT_STOP              (1U)                            /*!< Counter stop counting. */
#define TMR2_CNT_STAT_MATCH_CMP         (2U)                            /*!< Counter value matches the compare value. */
/**
 * @}
 */

/**
 * @defgroup TMR2_PWM_Polarity TMR2 PWM Polarity
 * @{
 */
#define TMR2_PWM_LOW                    (0x0U)                          /*!< PWM output low. */
#define TMR2_PWM_HIGH                   (0x1U)                          /*!< PWM output high. */
#define TMR2_PWM_HOLD                   (0x2U)                          /*!< PWM output keeps the current polarity. */
#define TMR2_PWM_INVT                   (0x3U)                          /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMR2_Start_Condition TMR2 Start Condition
 * @{
 */
#define TMR2_START_COND_INVD            (0x0U)                          /*!< The start condition of TMR2 is INVALID. */
#define TMR2_START_COND_TRIG_RISING     (TMR2_HCONR_HSTAA0)             /*!< The start condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_TRIG_FALLING    (TMR2_HCONR_HSTAA1)             /*!< The start condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_START_COND_EVT             (TMR2_HCONR_HSTAA2)             /*!< The start condition of TMR2 is the specified event occurred. */
#define TMR2_START_COND_ALL             (TMR2_START_COND_TRIG_RISING | TMR2_START_COND_TRIG_FALLING | \
                                         TMR2_START_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMR2_Stop_Condition TMR2 Stop Condition
 * @{
 */
#define TMR2_STOP_COND_INVD             (0x0U)                          /*!< The stop condition of TMR2 is INVALID. */
#define TMR2_STOP_COND_TRIG_RISING      (TMR2_HCONR_HSTPA0)             /*!< The stop condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_TRIG_FALLING     (TMR2_HCONR_HSTPA1)             /*!< The stop condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_STOP_COND_EVT              (TMR2_HCONR_HSTPA2)             /*!< The stop condition of TMR2 is the specified event occurred. */
#define TMR2_STOP_COND_ALL              (TMR2_STOP_COND_TRIG_RISING | TMR2_STOP_COND_TRIG_FALLING | \
                                         TMR2_STOP_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMR2_Clear_Condition TMR2 Clear Condition
 * @{
 */
#define TMR2_CLR_COND_INVD              (0x0U)                          /*!< The clear condition of TMR2 is INVALID. */
#define TMR2_CLR_COND_TRIG_RISING       (TMR2_HCONR_HCLEA0)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_TRIG_FALLING      (TMR2_HCONR_HCLEA1)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CLR_COND_EVT               (TMR2_HCONR_HCLEA2)             /*!< The clear(clear CNTAR/CNTBR) condition of TMR2 is the specified event occurred. */
#define TMR2_CLR_COND_ALL               (TMR2_CLR_COND_TRIG_RISING | TMR2_CLR_COND_TRIG_FALLING | \
                                         TMR2_CLR_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMR2_Capture_Condition TMR2 Capture Condition
 * @{
 */
#define TMR2_CAPT_COND_INVD             (0x0U)                          /*!< The capture condition of TMR2 is INVALID. */
#define TMR2_CAPT_COND_TRIG_RISING      (TMR2_HCONR_HICPA0)             /*!< The capture condition of TMR2 is the rising edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_TRIG_FALLING     (TMR2_HCONR_HICPA1)             /*!< The capture condition of TMR2 is the falling edge of TIM2_x_PWMA/B. */
#define TMR2_CAPT_COND_EVT              (TMR2_HCONR_HICPA2)             /*!< The capture condition of TMR2 is the specified event occurred. */
#define TMR2_CAPT_COND_ALL              (TMR2_CAPT_COND_TRIG_RISING | TMR2_CAPT_COND_TRIG_FALLING | \
                                         TMR2_CAPT_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMR2_Filter_Clock_Divider TMR2 Filter Clock Divider
 * @{
 */
#define TMR2_FILTER_CLK_DIV1            (0x0U)                          /*!< The filter clock is the clock of timer2 / 1 */
#define TMR2_FILTER_CLK_DIV4            (TMR2_PCONR_NOFICKA_0)          /*!< The filter clock is the clock of timer2 / 4 */
#define TMR2_FILTER_CLK_DIV16           (TMR2_PCONR_NOFICKA_1)          /*!< The filter clock is the clock of timer2 / 16 */
#define TMR2_FILTER_CLK_DIV64           (TMR2_PCONR_NOFICKA)            /*!< The filter clock is the clock of timer2 / 64 */
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
int32_t TMR2_Init(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, const stc_tmr2_init_t *pstcTmr2Init);
int32_t TMR2_StructInit(stc_tmr2_init_t *pstcTmr2Init);
void TMR2_DeInit(CM_TMR2_TypeDef *TMR2x);

void TMR2_SetFunc(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Func);
void TMR2_SetClockSrc(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Src);
void TMR2_SetClockDiv(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Div);

int32_t TMR2_PWM_StructInit(stc_tmr2_pwm_init_t *pstPwmInit);
int32_t TMR2_PWM_Init(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, const stc_tmr2_pwm_init_t *pstPwmInit);
void TMR2_PWM_OutputCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, en_functional_state_t enNewState);

void TMR2_HWCaptureCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState);

void TMR2_HWStartCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR2_HWStopCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState);
void TMR2_HWClearCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState);

void TMR2_SetFilterClockDiv(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Div);
void TMR2_FilterCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, en_functional_state_t enNewState);

void TMR2_IntCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32IntType, en_functional_state_t enNewState);

void TMR2_Start(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch);
void TMR2_Stop(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch);

en_flag_status_t TMR2_GetStatus(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Flag);
void TMR2_ClearStatus(CM_TMR2_TypeDef *TMR2x, uint32_t u32Flag);

void TMR2_SetCompareValue(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Value);
uint32_t TMR2_GetCompareValue(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch);

void TMR2_SetCountValue(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Value);
uint32_t TMR2_GetCountValue(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch);

void TMR2_PWM_SetPolarity(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint8_t u8CountState, uint32_t u32Polarity);

/**
 * @}
 */

#endif /* LL_TMR2_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TMR2_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

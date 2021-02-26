/**
 *******************************************************************************
 * @file  hc32f4a0_tmra.h
 * @brief This file contains all the functions prototypes of the TMRA(TimerA)
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
#ifndef __HC32F4A0_TMRA_H__
#define __HC32F4A0_TMRA_H__

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
 * @addtogroup DDL_TMRA
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Types TMRA Global Types
 * @{
 */
/**
 * @brief TMRA initialization structure.
 * @note 'u32PCLKDiv', 'u32CntDir' and 'u32CntMode' are valid only when the clock source is PCLK(PCLK0 for unit1 ~ uint4. PCLK1 for unit5 ~ uint12).
 */
typedef struct
{
    uint32_t u32ClkSrc;                     /*!< Specify the counting clock source of TMRA.
                                                 This parameter can be a value of @ref TMRA_Clock_Source */
    uint32_t u32PCLKDiv;                    /*!< Specify the divider of clock source while the clock source is PCLK.
                                                 This parameter can be a value of @ref TMRA_PCLK_Divider */
    uint32_t u32CntDir;                     /*!< Specify the direction of counting.
                                                 This parameter can be a value of @ref TMRA_Count_Direction */
    uint32_t u32CntMode;                    /*!< Specify the mode of counting.
                                                 This parameter can be a value of @ref TMRA_Count_Mode */
    uint32_t u32CntOvfOp;                   /*!< Specify the operation when counting overflow/underflow.
                                                 This parameter can be a value of @ref TMRA_Count_Overflow_Operation */
    uint32_t u32PeriodVal;                  /*!< Specify the period reference value.
                                                 This parameter can be a number between 0U and 0xFFFFU, inclusive. */
    uint32_t u32CntVal;                     /*!< Specify the initial value of count register.
                                                 This parameter can be a number between 0U and 0xFFFFU, inclusive. */
} stc_tmra_init_t;

/**
 * @brief TMRA PWM configuration structure.
 */
typedef struct
{
    uint32_t u32StartPolarity;              /*!< Specify the polarity when the specified TMRA channel start counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Start_Polarity */
    uint32_t u32StopPolarity;               /*!< Specify the polarity when the specified TMRA channel stop counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Stop_Polarity */
    uint32_t u32CmpPolarity;                /*!< Specify the polarity when the specified TMRA channel counting matches the compare register.
                                                 This parameter can be a value of @ref TMRA_PWM_Match_Cmp_Polarity */
    uint32_t u32PeriodPolarity;             /*!< Specify the polarity when the specified TMRA channel counting matches the period register.
                                                 This parameter can be a value of @ref TMRA_PWM_Match_Period_Polarity */
    uint32_t u32ForcePolarity;              /*!< Specify the polarity when the specified TMRA channel at the beginning of the next cycle.
                                                 This parameter can be a value of @ref TMRA_PWM_Force_Polarity */
} stc_tmra_pwm_cfg_t;

/**
 * @brief TMRA hardware trigger condition configuration structure.
 */
typedef struct
{
    uint32_t u32StartCond;                  /*!< Specify the condition to start the specified TMRA unit.
                                                 This parameter can be a value of @ref TMRA_Hardware_Start_Condition */
    uint32_t u32StopCond;                   /*!< Specify the condition to stop the specified TMRA unit.
                                                 This parameter can be a value of @ref TMRA_Hardware_Stop_Condition */
    uint32_t u32ClrCond;                    /*!< Specify the condition to clear the specified TMRA unit's count register.
                                                 This parameter can be a value of @ref TMRA_Hardware_Clear_Condition */
} stc_tmra_trig_cond_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Macros TMRA Global Macros
 * @{
 */

/**
 * @defgroup TMRA_Channel TMRA Channel
 * @{
 */
#define TMRA_CH_1                           (0U)                        /*!< Channel 1 of TMRA. */
#define TMRA_CH_2                           (1U)                        /*!< Channel 2 of TMRA. */
#define TMRA_CH_3                           (2U)                        /*!< Channel 3 of TMRA. */
#define TMRA_CH_4                           (3U)                        /*!< Channel 4 of TMRA. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Input_Pin TMRA Input Pin
 * @{
 */
#define TMRA_PIN_TRIG                       (1UL << 0U)                 /*!< Pin TIMA_<t>_TRIG. */
#define TMRA_PIN_CLKA                       (1UL << 1U)                 /*!< Pin TIMA_<t>_CLKA. */
#define TMRA_PIN_CLKB                       (1UL << 2U)                 /*!< Pin TIMA_<t>_CLKB. */
#define TMRA_PIN_PWM1                       (1UL << 3U)                 /*!< Pin TIMA_<t>_PWM1. */
#define TMRA_PIN_PWM2                       (1UL << 4U)                 /*!< Pin TIMA_<t>_PWM2. */
#define TMRA_PIN_PWM3                       (1UL << 5U)                 /*!< Pin TIMA_<t>_PWM3. */
#define TMRA_PIN_PWM4                       (1UL << 6U)                 /*!< Pin TIMA_<t>_PWM4. */
#define TMRA_PIN_ALL                        (TMRA_PIN_TRIG | \
                                             TMRA_PIN_CLKA | \
                                             TMRA_PIN_CLKB | \
                                             TMRA_PIN_PWM1 | \
                                             TMRA_PIN_PWM2 | \
                                             TMRA_PIN_PWM3 | \
                                             TMRA_PIN_PWM4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Direction TMRA Counting Direction
 * @{
 */
#define TMRA_DIR_DOWN                       (0x0U)                      /*!< TMRA count down. */
#define TMRA_DIR_UP                         (TMRA_BCSTR_DIR)            /*!< TMRA count up. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Mode TMRA Counting Mode
 * @{
 */
#define TMRA_MODE_SAWTOOTH                  (0x0U)                      /*!< Count mode is sawtooth wave. */
#define TMRA_MODE_TRIANGLE                  (TMRA_BCSTR_MODE)           /*!< Count mode is triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Clock_Source TMRA Counting Clock Source
 * @note PCLK is automatically disabled when other clock is selected.
 * @note Symmetric units: uint 1 and 2; uint 3 and 4; ...; uint 11 and 12.
 * @{
 */
#define TMRA_CLK_PCLK                       (0x0U)                      /*!< PCLK. PCLK0 for unit1 ~ uint4. PCLK1 for unit5 ~ uint12. */

#define TMRA_CLK_HW_UP_CLKAL_CLKBR          (1UL << 0U)                 /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKAL_CLKBF          (1UL << 1U)                 /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKAH_CLKBR          (1UL << 2U)                 /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKAH_CLKBF          (1UL << 3U)                 /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKBL_CLKAR          (1UL << 4U)                 /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKBL_CLKAF          (1UL << 5U)                 /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKBH_CLKAR          (1UL << 6U)                 /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CLK_HW_UP_CLKBH_CLKAF          (1UL << 7U)                 /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CLK_HW_UP_TRIGR                (1UL << 8U)                 /*!< When a rising edge occurred on TRIG, the counter register counts up. */
#define TMRA_CLK_HW_UP_TRIGF                (1UL << 9U)                 /*!< When a falling edge occurred on TRIG, the counter register counts up. */
#define TMRA_CLK_HW_UP_EVENT                (1UL << 10U)                /*!< When the event specified by TMRA_HTSSR occurred, the counter register counts up. */
#define TMRA_CLK_HW_UP_SYM_OVF              (1UL << 11U)                /*!< When the symmetric unit overflow, the counter register counts up. */
#define TMRA_CLK_HW_UP_SYM_UNF              (1UL << 12U)                /*!< When the symmetric unit underflow, the counter register counts up. */
#define TMRA_CLK_HW_UP_ALL                  (0x1FFFUL)

#define TMRA_CLK_HW_DOWN_CLKAL_CLKBR        (1UL << 16U)                /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKAL_CLKBF        (1UL << 17U)                /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKAH_CLKBR        (1UL << 18U)                /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKAH_CLKBF        (1UL << 19U)                /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKBL_CLKAR        (1UL << 20U)                /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKBL_CLKAF        (1UL << 21U)                /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKBH_CLKAR        (1UL << 22U)                /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_CLKBH_CLKAF        (1UL << 23U)                /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_TRIGR              (1UL << 24U)                /*!< When a rising edge occurred on TRIG, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_TRIGF              (1UL << 25U)                /*!< When a falling edge occurred on TRIG, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_EVENT              (1UL << 26U)                /*!< When the event specified by TMRA_HTSSR occurred, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_SYM_OVF            (1UL << 27U)                /*!< When the symmetric unit overflow, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_SYM_UNF            (1UL << 28U)                /*!< When the symmetric unit underflow, the counter register counts down. */
#define TMRA_CLK_HW_DOWN_ALL                (0x1FFF0000UL)
/**
 * @}
 */

/**
 * @defgroup TMRA_PCLK_Divider TMRA PCLK Divider
 * @note Clock divider is only valid for PCLK(PCLK0 for unit1 ~ uint4. PCLK1 for unit5 ~ uint12).
 * @{
 */
#define TMRA_PCLK_DIV1                      (0x0U)                      /*!< The clock source of TMRA is PCLK. */
#define TMRA_PCLK_DIV2                      (TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TMRA is PCLK / 2. */
#define TMRA_PCLK_DIV4                      (TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TMRA is PCLK / 4. */
#define TMRA_PCLK_DIV8                      (TMRA_BCSTR_CKDIV_1 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TMRA is PCLK / 8. */
#define TMRA_PCLK_DIV16                     (TMRA_BCSTR_CKDIV_2)        /*!< The clock source of TMRA is PCLK / 16. */
#define TMRA_PCLK_DIV32                     (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TMRA is PCLK / 32. */
#define TMRA_PCLK_DIV64                     (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TMRA is PCLK / 64. */
#define TMRA_PCLK_DIV128                    (TMRA_BCSTR_CKDIV_2 | \
                                             TMRA_BCSTR_CKDIV_1 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TMRA is PCLK / 128. */
#define TMRA_PCLK_DIV256                    (TMRA_BCSTR_CKDIV_3)        /*!< The clock source of TMRA is PCLK / 256. */
#define TMRA_PCLK_DIV512                    (TMRA_BCSTR_CKDIV_3 | \
                                             TMRA_BCSTR_CKDIV_0)        /*!< The clock source of TMRA is PCLK / 512. */
#define TMRA_PCLK_DIV1024                   (TMRA_BCSTR_CKDIV_3 | \
                                             TMRA_BCSTR_CKDIV_1)        /*!< The clock source of TMRA is PCLK / 1024. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Overflow_Operation TMRA Count Overflow Operation
 * @note Count up corresponds to overflow, counter zeroing when counting value overflow period value.
 * @note Count down corresponds to underflow, counter reload period value when counting value underflow 0.
 * @{
 */
#define TMRA_OVF_CNT_CONTINUE               (0x0U)                      /*!< When counting overflow(or underflow), counting continue. */
#define TMRA_OVF_CNT_STOP                   (TMRA_BCSTR_OVSTP)          /*!< When counting overflow(or underflow), counting stop. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Interrupt_Type TMRA Interrupt Type
 * @{
 */
#define TMRA_INT_OVF                        (1UL << 12U)                /*!< The interrupt of counting overflow. */
#define TMRA_INT_UNF                        (1UL << 13U)                /*!< The interrupt of counting underflow. */
#define TMRA_INT_CMP_CH1                    (1UL << 16U)                /*!< The interrupt of compare-match of channel 1. */
#define TMRA_INT_CMP_CH2                    (1UL << 17U)                /*!< The interrupt of compare-match of channel 2. */
#define TMRA_INT_CMP_CH3                    (1UL << 18U)                /*!< The interrupt of compare-match of channel 3. */
#define TMRA_INT_CMP_CH4                    (1UL << 19U)                /*!< The interrupt of compare-match of channel 4. */
#define TMRA_INT_ALL                        (TMRA_INT_OVF     | \
                                             TMRA_INT_UNF     | \
                                             TMRA_INT_CMP_CH1 | \
                                             TMRA_INT_CMP_CH2 | \
                                             TMRA_INT_CMP_CH3 | \
                                             TMRA_INT_CMP_CH4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Type TMRA Event Type
 * @{
 */
#define TMRA_EVENT_CMP_CH1                  (TMRA_ECONR_ETEN1)          /*!< The event of compare-match of channel 1. */
#define TMRA_EVENT_CMP_CH2                  (TMRA_ECONR_ETEN2)          /*!< The event of compare-match of channel 2. */
#define TMRA_EVENT_CMP_CH3                  (TMRA_ECONR_ETEN3)          /*!< The event of compare-match of channel 3. */
#define TMRA_EVENT_CMP_CH4                  (TMRA_ECONR_ETEN4)          /*!< The event of compare-match of channel 4. */
#define TMRA_EVENT_ALL                      (TMRA_EVENT_CMP_CH1 | \
                                             TMRA_EVENT_CMP_CH2 | \
                                             TMRA_EVENT_CMP_CH3 | \
                                             TMRA_EVENT_CMP_CH4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Status_Flag TMRA Status Flag
 * @{
 */
#define TMRA_FLAG_OVF                       (1UL << 14U)                /*!< The flag of counting overflow. */
#define TMRA_FLAG_UNF                       (1UL << 15U)                /*!< The flag of counting underflow. */
#define TMRA_FLAG_CMP_CH1                   (1UL << 16U)                /*!< The flag of compare-match of channel 1. */
#define TMRA_FLAG_CMP_CH2                   (1UL << 17U)                /*!< The flag of compare-match of channel 2. */
#define TMRA_FLAG_CMP_CH3                   (1UL << 18U)                /*!< The flag of compare-match of channel 3. */
#define TMRA_FLAG_CMP_CH4                   (1UL << 19U)                /*!< The flag of compare-match of channel 4. */
#define TMRA_FLAG_ALL                       (TMRA_FLAG_OVF | \
                                             TMRA_FLAG_UNF | \
                                             TMRA_FLAG_CMP_CH1 | \
                                             TMRA_FLAG_CMP_CH2 | \
                                             TMRA_FLAG_CMP_CH3 | \
                                             TMRA_FLAG_CMP_CH4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Cmp_Value_Cache_Condition TMRA Compare Value Cache Condition
 * @{
 */
#define TMRA_CACHE_COND_OVF_CLR             (0x0U)                      /*!< This configuration value applies to non-triangular wave counting mode. \
                                                                             When counting overflow or underflow or counting register was cleared, \
                                                                             transfer CMPARm(m=2, 4) to CMPARn(n=1, 3). */
#define TMRA_CACHE_COND_TW_PEAK             (TMRA_BCONR_BSE0)           /*!< In triangle wave count mode, when count reached peak, \
                                                                             transfer CMPARm(m=2, 4) to CMPARn(n=1, 3). */
#define TMRA_CACHE_COND_TW_VALLEY           (TMRA_BCONR_BSE1)           /*!< In triangle wave count mode, when count reached valley, \
                                                                             transfer CMPARm(m=2, 4) to CMPARn(n=1, 3). */
/**
 * @}
 */

/**
 * @defgroup TMRA_Function_Mode TMRA Function Mode
 * @{
 */
#define TMRA_FUNC_COMPARE                   (0x0U)                      /*!< The function mode of TMRA is comparison ouput. */
#define TMRA_FUNC_CAPTURE                   (TMRA_CCONR_CAPMD)          /*!< The function mode of TMRA is capture the input. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Channel_Capture_Condition TMRA Capturing Condition Of Channel
 * @note 'TMRA_CAPT_COND_TRIGR' and 'TMRA_CAPT_COND_TRIGF' are only valid for channel 4.
 * @{
 */
#define TMRA_CAPT_COND_INVALID              (0x0U)                     /*!< The condition of capture is INVALID. */
#define TMRA_CAPT_COND_PWMR                 (TMRA_CCONR_HICP0)         /*!< The condition of capture is a rising edge is sampled on pin TIMA_<t>_PWMn. */
#define TMRA_CAPT_COND_PWMF                 (TMRA_CCONR_HICP1)         /*!< The condition of capture is a falling edge is sampled on pin TIMA_<t>_PWMn. */
#define TMRA_CAPT_COND_EVENT                (TMRA_CCONR_HICP2)         /*!< The condition of capture is the specified event occurred. */
#define TMRA_CAPT_COND_TRIGR                (TMRA_CCONR_HICP3)         /*!< The condition of capture is a rising edge is sampled on pin TIMA_<t>_TRIG. \
                                                                            This condition is only valid for channel 4. */
#define TMRA_CAPT_COND_TRIGF                (TMRA_CCONR_HICP4)         /*!< The condition of capture is a falling edge is sampled on pin TIMA_<t>_TRIG. \
                                                                            This condition is only valid for channel 4. */
#define TMRA_CAPT_COND_ALL                  (TMRA_CAPT_COND_PWMR  | \
                                             TMRA_CAPT_COND_PWMF  | \
                                             TMRA_CAPT_COND_EVENT | \
                                             TMRA_CAPT_COND_TRIGR | \
                                             TMRA_CAPT_COND_TRIGF)
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Clock_Divider TMRA Filter Clock Divider
 * @{
 */
#define TMRA_FILTER_CLK_DIV1                (0x0U)                      /*!< The filter clock is PCLK / 1. */
#define TMRA_FILTER_CLK_DIV4                (0x1U)                      /*!< The filter clock is PCLK / 4. */
#define TMRA_FILTER_CLK_DIV16               (0x2U)                      /*!< The filter clock is PCLK / 16. */
#define TMRA_FILTER_CLK_DIV64               (0x3U)                      /*!< The filter clock is PCLK / 64. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Out_Command TMRA PWM Out Command
 * @{
 */
#define TMRA_PWM_DISABLE                    (0x0U)                      /*!< Disable PWM output. */
#define TMRA_PWM_ENABLE                     (TMRA_PCONR_OUTEN)          /*!< Enable PWM output. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Start_Polarity TMRA PWM Start Polarity
 * @note The 'START' in the following macros is the state 'counting start'.
 * @{
 */
#define TMRA_PWM_START_LOW                  (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_START_HIGH                 (TMRA_PCONR_STAC_0)         /*!< PWM output high. */
#define TMRA_PWM_START_KEEP                 (TMRA_PCONR_STAC_1)         /*!< PWM output keeps the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Stop_Polarity TMRA PWM Stop Polarity
 * @note The 'STOP' in the following macros is the state 'counting stop'.
 * @{
 */
#define TMRA_PWM_STOP_LOW                   (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_STOP_HIGH                  (TMRA_PCONR_STPC_0)         /*!< PWM output high. */
#define TMRA_PWM_STOP_KEEP                  (TMRA_PCONR_STPC_1)         /*!< PWM output keeps the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Match_Cmp_Polarity TMRA PWM Polarity When Counting Matchs Compare Reference Value
 * @{
 */
#define TMRA_PWM_CMP_LOW                    (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_CMP_HIGH                   (TMRA_PCONR_CMPC_0)         /*!< PWM output high. */
#define TMRA_PWM_CMP_KEEP                   (TMRA_PCONR_CMPC_1)         /*!< PWM output keeps the current polarity. */
#define TMRA_PWM_CMP_REVERSE                (TMRA_PCONR_CMPC_1 | \
                                             TMRA_PCONR_CMPC_0)         /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Match_Period_Polarity TMRA PWM Polarity When Counting Matchs Period Reference Value
 * @{
 */
#define TMRA_PWM_PERIOD_LOW                 (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_PERIOD_HIGH                (TMRA_PCONR_PERC_0)         /*!< PWM output high. */
#define TMRA_PWM_PERIOD_KEEP                (TMRA_PCONR_PERC_1)         /*!< PWM output keeps the current polarity. */
#define TMRA_PWM_PERIOD_REVERSE             (TMRA_PCONR_PERC_1 | \
                                             TMRA_PCONR_PERC_0)         /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Force_Polarity TMRA PWM Force Polarity
 * @{
 */
#define TMRA_PWM_FORCE_INVALID              (0x0U)                      /*!< Force polarity is invalid. */
#define TMRA_PWM_FORCE_LOW                  (TMRA_PCONR_FORC_1)         /*!< Force the PWM output low at the beginning of the next cycle. \
                                                                             The beginning of the next cycle: overflow position or underflow position \
                                                                             of sawtooth wave; valley position of triangle wave. */
#define TMRA_PWM_FORCE_HIGH                 (TMRA_PCONR_FORC_1 | \
                                             TMRA_PCONR_FORC_0)         /*!< Force the PWM output high at the beginning of the next cycle. \
                                                                             The beginning of the next cycle: overflow position or underflow position \
                                                                             of sawtooth wave; valley position of triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Start_Condition TMRA Hardware Start Condition
 * @{
 */
#define TMRA_START_COND_INVALID             (0x0U)                  /*!< The condition of start is INVALID. */
#define TMRA_START_COND_TRIGR               (TMRA_HCONR_HSTA0)      /*!< 1. Sync start is invalid: The condition is that a rising edge is sampled on TRIG of the current TMRA unit. \
                                                                         2. Sync start is valid: The condition is that a rising edge is sampled on TRIG of the symmetric TMRA unit. */
#define TMRA_START_COND_TRIGF               (TMRA_HCONR_HSTA1)      /*!< 1. Sync start is invalid: The condition is that a falling edge is sampled on TRIG of the current TMRA unit. \
                                                                         2. Sync start is valid: The condition is that a falling edge is sampled on TRIG of the symmetric TMRA unit. */
#define TMRA_START_COND_EVENT               (TMRA_HCONR_HSTA2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_START_COND_ALL                 (TMRA_START_COND_TRIGR | \
                                             TMRA_START_COND_TRIGF | \
                                             TMRA_START_COND_EVENT)
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Stop_Condition TMRA Hardware Stop Condition
 * @{
 */
#define TMRA_STOP_COND_INVALID              (0x0U)                  /*!< The condition of stop is INVALID. */
#define TMRA_STOP_COND_TRIGR                (TMRA_HCONR_HSTP0)      /*!< The condition is that a rising edge is sampled on pin TRIG of the current TMRA unit. */
#define TMRA_STOP_COND_TRIGF                (TMRA_HCONR_HSTP1)      /*!< The condition is that a falling edge is sampled on pin TRIG of the current TMRA unit. */
#define TMRA_STOP_COND_EVENT                (TMRA_HCONR_HSTP2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_STOP_COND_ALL                  (TMRA_STOP_COND_TRIGR | \
                                             TMRA_STOP_COND_TRIGF | \
                                             TMRA_STOP_COND_EVENT)
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Clear_Condition TMRA Hardware Clear Condition
 * @note Symmetric units: uint 1 and 2; uint 3 and 4; ... ; uint 11 and 12.
 * @{
 */
#define TMRA_CLR_COND_INVALID               (0x0U)                  /*!< The condition of clear is INVALID. */
#define TMRA_CLR_COND_TRIGR                 (TMRA_HCONR_HCLE0)      /*!< The condition is that a rising edge is sampled on TRIG of the current TMRA unit. */
#define TMRA_CLR_COND_TRIGF                 (TMRA_HCONR_HCLE1)      /*!< The condition is that a falling edge is sampled on TRIG of the current TMRA unit. */
#define TMRA_CLR_COND_EVENT                 (TMRA_HCONR_HCLE2)      /*!< The condition is that the event which is set in register TMRA_HTSSR0 has occurred. */
#define TMRA_CLR_COND_SYM_TRIGR             (TMRA_HCONR_HCLE3)      /*!< The condition is that a rising edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_SYM_TRIGF             (TMRA_HCONR_HCLE4)      /*!< The condition is that a falling edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_PWM3R                 (TMRA_HCONR_HCLE5)      /*!< The condition is that a rising edge is sampled on PWM3 of the current TMRA unit. */
#define TMRA_CLR_COND_PWM3F                 (TMRA_HCONR_HCLE6)      /*!< The condition is that a falling edge is sampled on PWM3 of the current TMRA unit. */
#define TMRA_CLR_COND_ALL                   (TMRA_CLR_COND_TRIGR     | \
                                             TMRA_CLR_COND_TRIGF     | \
                                             TMRA_CLR_COND_EVENT     | \
                                             TMRA_CLR_COND_SYM_TRIGR | \
                                             TMRA_CLR_COND_SYM_TRIGF | \
                                             TMRA_CLR_COND_PWM3R     | \
                                             TMRA_CLR_COND_PWM3F)
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Usage TMRA Event Usage
 * @{
 */
#define TMRA_EVENT_USAGE_CNT                (0U)                    /*!< The specified event is used for counting. */
#define TMRA_EVENT_USAGE_CAPT               (1U)                    /*!< The specified event is used for capturing. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Common_Trigger_Sel TMRA Common Trigger Source Select
 * @{
 */
#define TMRA_COM_TRIG1                      (AOS_TMRA_HTSSR_COMTRG_EN_0)
#define TMRA_COM_TRIG2                      (AOS_TMRA_HTSSR_COMTRG_EN_1)
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
 * @addtogroup TMRA_Global_Functions
 * @{
 */
     en_result_t TMRA_Init(M4_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcInit);
     en_result_t TMRA_StructInit(stc_tmra_init_t *pstcInit);
            void TMRA_DeInit(M4_TMRA_TypeDef *TMRAx);

            void TMRA_SetCntVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val);
        uint32_t TMRA_GetCntVal(const M4_TMRA_TypeDef *TMRAx);
            void TMRA_SetPeriodVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val);
        uint32_t TMRA_GetPeriodVal(const M4_TMRA_TypeDef *TMRAx);

            void TMRA_SetFuncMode(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32FuncMode);

            void TMRA_SetCmpVal(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Val);
        uint32_t TMRA_GetCmpVal(const M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh);

     en_result_t TMRA_PWM_Config(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, const stc_tmra_pwm_cfg_t *pstcCfg);
     en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_cfg_t *pstcCfg);
            void TMRA_PWM_Cmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState);

            void TMRA_FilterConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, uint32_t u32ClkDiv);
            void TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, en_functional_state_t enNewState);

            void TMRA_SetCaptCond(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Cond);
     en_result_t TMRA_SetTrigCond(M4_TMRA_TypeDef *TMRAx, const stc_tmra_trig_cond_t *pstcCond);
     en_result_t TMRA_TrigCondStructInit(stc_tmra_trig_cond_t *pstcCond);
            void TMRA_SetTriggerSrc(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, en_event_src_t enEvent);
            void TMRA_ComTriggerCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, \
                                    uint32_t u32ComTrig, en_functional_state_t enNewState);

            void TMRA_CmpValCacheConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CacheCond);
            void TMRA_CmpValCacheCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState);

            void TMRA_SetOvfOperation(M4_TMRA_TypeDef *TMRAx, uint32_t u32OvfOp);
            void TMRA_SyncStartCmd(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);

            void TMRA_IntCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState);
            void TMRA_EventCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32EvtType, en_functional_state_t enNewState);

en_flag_status_t TMRA_GetStatus(const M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag);
            void TMRA_ClrStatus(M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag);

            void TMRA_Start(M4_TMRA_TypeDef *TMRAx);
            void TMRA_Stop(M4_TMRA_TypeDef *TMRAx);

            void TMRA_SetCntDir(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntDir);
            void TMRA_SetCntMode(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntMode);
            void TMRA_SetPCLKDiv(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkDiv);
        uint32_t TMRA_GetCntDir(const M4_TMRA_TypeDef *TMRAx);

            void TMRA_SetClkSrc(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkSrc);
            void TMRA_HwClkSrcCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32HwClkSrc, en_functional_state_t enNewState);

            void TMRA_PWM_SetStartPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity);
            void TMRA_PWM_SetStopPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity);
            void TMRA_PWM_SetMatchCmpPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity);
            void TMRA_PWM_SetMatchPeriodPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity);
            void TMRA_PWM_SetForcePolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity);

            void TMRA_CaptCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CaptCond, en_functional_state_t enNewState);
            void TMRA_TrigCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32TrigCond, en_functional_state_t enNewState);
/**
 * @}
 */

#endif /* DDL_TMRA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_TMRA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

/**
 *******************************************************************************
 * @file  hc32_ll_tmra.h
 * @brief This file contains all the functions prototypes of the TMRA(TimerA)
 *        driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Delete union in stc_tmra_init_t structure
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
#ifndef __HC32_LL_TMRA_H__
#define __HC32_LL_TMRA_H__

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
 * @addtogroup LL_TMRA
 * @{
 */

#if (LL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup TMRA_Global_Types TMRA Global Types
 * @{
 */
/**
 * @brief TMRA initialization structure.
 */
typedef struct {
    uint8_t u8CountSrc;                     /*!< Specifies the count source of TMRA.
                                                 This parameter can be a value of @ref TMRA_Count_Src */
    struct {
        uint8_t u8ClockDiv;                 /*!< Specifies the divider of software clock source.
                                                 This parameter can be a value of @ref TMRA_Clock_Divider */
        uint8_t u8CountMode;                /*!< Specifies count mode.
                                                 This parameter can be a value of @ref TMRA_Count_Mode */
        uint8_t u8CountDir;                 /*!< Specifies count direction.
                                                    This parameter can be a value of @ref TMRA_Count_Dir */
    } sw_count;
    struct {
        uint16_t u16CountUpCond;            /*!< Hardware count up condition.
                                                 This parameter can be a value of @ref TMRA_Hard_Count_Up_Condition */
        uint16_t u16CountDownCond;          /*!< Hardware count down condition.
                                                 This parameter can be a value of @ref TMRA_Hard_Count_Down_Condition */
    } hw_count;
    uint32_t u32PeriodValue;                /*!< Specifies the period reference value.
                                                 This parameter can be a number between 0U and 0xFFFFU, inclusive. */
    uint8_t u8CountReload;                  /*!< Continue counting or stop when counter overflow/underflow.
                                                 This parameter can be a value of @ref TMRA_Count_Reload_En */
} stc_tmra_init_t;

/**
 * @brief TMRA PWM configuration structure.
 */
typedef struct {
    uint32_t u32CompareValue;               /*!< Specifies compare value of the TMRA channel.
                                                 This parameter can be a number between:
                                                 0UL and 0xFFFFFFFFUL for 32-bit TimerA units.
                                                 0UL and 0xFFFFUL for 16-bit TimerA units. */
    uint16_t u16StartPolarity;              /*!< Specifies the polarity when the counter start counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Polarity
                                                 NOTE: CAN NOT be specified as TMRA_PWM_LOW or TMRA_PWM_HIGH when
                                                       sw_count.u16ClockDiv of @ref stc_tmra_init_t is NOT specified
                                                       as @ref TMRA_CLK_DIV1 */
    uint16_t u16StopPolarity;               /*!< Specifies the polarity when the counter stop counting.
                                                 This parameter can be a value of @ref TMRA_PWM_Polarity */
    uint16_t u16CompareMatchPolarity;       /*!< Specifies the polarity when the counter matches the compare register.
                                                 This parameter can be a value of @ref TMRA_PWM_Polarity */
    uint16_t u16PeriodMatchPolarity;        /*!< Specifies the polarity when the counter matches the period register.
                                                 This parameter can be a value of @ref TMRA_PWM_Polarity */
} stc_tmra_pwm_init_t;

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
 * @defgroup TMRA_Count_Src TMRA Count Source
 * @{
 */
#define TMRA_CNT_SRC_SW                     (0U)                        /*!< Clock source is PCLK. */
#define TMRA_CNT_SRC_HW                     (1U)                        /*!< Clock source is from external pin or peripheral event. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Channel TMRA Channel
 * @{
 */
#define TMRA_CH1                            (0U)                        /*!< Channel 1 of TMRA. */
#define TMRA_CH2                            (1U)                        /*!< Channel 2 of TMRA. */
#define TMRA_CH3                            (2U)                        /*!< Channel 3 of TMRA. */
#define TMRA_CH4                            (3U)                        /*!< Channel 4 of TMRA. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Dir TMRA Count Direction
 * @{
 */
#define TMRA_DIR_DOWN                       (0x0U)                      /*!< TMRA count down. */
#define TMRA_DIR_UP                         (TMRA_BCSTRL_DIR)           /*!< TMRA count up. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Mode TMRA Count Mode
 * @{
 */
#define TMRA_MD_SAWTOOTH                    (0x0U)                      /*!< Count mode is sawtooth wave. */
#define TMRA_MD_TRIANGLE                    (TMRA_BCSTRL_MODE)          /*!< Count mode is triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Function_Mode TMRA TMRA Function Mode
 * @{
 */
#define TMRA_FUNC_CMP                       (0x0U)                      /*!< Function mode of TMRA channel is ouput compare. */
#define TMRA_FUNC_CAPT                      (TMRA_CCONR_CAPMD)          /*!< Function mode of TMRA channel is input capture. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Count_Reload_En TMRA Count Reload
 * @{
 */
#define TMRA_CNT_RELOAD_DISABLE             (TMRA_BCSTRH_OVSTP)         /*!< Stop when counter overflow/underflow. */
#define TMRA_CNT_RELOAD_ENABLE              (0U)                        /*!< When counter overflow/underflow, counter reload to continue counting. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Clock_Divider TMRA Clock Divider
 * @{
 */
#define TMRA_CLK_DIV1                       (0x0U)                              /*!< The clock source of TMRA is PCLK. */
#define TMRA_CLK_DIV2                       (0x1U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 2. */
#define TMRA_CLK_DIV4                       (0x2U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 4. */
#define TMRA_CLK_DIV8                       (0x3U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 8. */
#define TMRA_CLK_DIV16                      (0x4U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 16. */
#define TMRA_CLK_DIV32                      (0x5U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 32. */
#define TMRA_CLK_DIV64                      (0x6U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 64. */
#define TMRA_CLK_DIV128                     (0x7U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 128. */
#define TMRA_CLK_DIV256                     (0x8U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 256. */
#define TMRA_CLK_DIV512                     (0x9U << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 512. */
#define TMRA_CLK_DIV1024                    (0xAU << TMRA_BCSTRL_CKDIV_POS)     /*!< The clock source of TMRA is PCLK / 1024. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Pin TMRA Pin With Filter
 * @{
 */
#define TMRA_PIN_TRIG                       (0U)                        /*!< Pin TIMA_<t>_TRIG. */
#define TMRA_PIN_CLKA                       (1U)                        /*!< Pin TIMA_<t>_CLKA. */
#define TMRA_PIN_CLKB                       (2U)                        /*!< Pin TIMA_<t>_CLKB. */
#define TMRA_PIN_PWM1                       (3U)                        /*!< Pin TIMA_<t>_PWM1. */
#define TMRA_PIN_PWM2                       (4U)                        /*!< Pin TIMA_<t>_PWM2. */
#define TMRA_PIN_PWM3                       (5U)                        /*!< Pin TIMA_<t>_PWM3. */
#define TMRA_PIN_PWM4                       (6U)                        /*!< Pin TIMA_<t>_PWM4. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hard_Count_Up_Condition TMRA Hardware Count Up Condition
 * @note Symmetric units: unit 1 and 2; unit 3 and 4; ...; unit 11 and 12.
 * @{
 */
#define TMRA_CNT_UP_COND_INVD                        (0U)                    /*!< TMRA hardware count up condition is INVALID. */
#define TMRA_CNT_UP_COND_CLKA_LOW_CLKB_RISING        (TMRA_HCUPR_HCUP0)      /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKA_LOW_CLKB_FALLING       (TMRA_HCUPR_HCUP1)      /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING       (TMRA_HCUPR_HCUP2)      /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_FALLING      (TMRA_HCUPR_HCUP3)      /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKB_LOW_CLKA_RISING        (TMRA_HCUPR_HCUP4)      /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKB_LOW_CLKA_FALLING       (TMRA_HCUPR_HCUP5)      /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKB_HIGH_CLKA_RISING       (TMRA_HCUPR_HCUP6)      /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CNT_UP_COND_CLKB_HIGH_CLKA_FALLING      (TMRA_HCUPR_HCUP7)      /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts up. */
#define TMRA_CNT_UP_COND_TRIG_RISING                 (TMRA_HCUPR_HCUP8)      /*!< When a rising edge occurred on TRIG, the counter register counts up. */
#define TMRA_CNT_UP_COND_TRIG_FALLING                (TMRA_HCUPR_HCUP9)      /*!< When a falling edge occurred on TRIG, the counter register counts up. */
#define TMRA_CNT_UP_COND_EVT                         (TMRA_HCUPR_HCUP10)     /*!< When the TMRA common trigger event occurred, the counter register counts up. */
#define TMRA_CNT_UP_COND_SYM_OVF                     (TMRA_HCUPR_HCUP11)     /*!< When the symmetric unit overflow, the counter register counts up. */
#define TMRA_CNT_UP_COND_SYM_UDF                     (TMRA_HCUPR_HCUP12)     /*!< When the symmetric unit underflow, the counter register counts up. */
#define TMRA_CNT_UP_COND_ALL                         (0x1FFFU)
/**
 * @}
 */

/**
 * @defgroup TMRA_Hard_Count_Down_Condition TMRA Hardware Count Down Condition
 * @note Symmetric units: unit 1 and 2; unit 3 and 4; ...; unit 11 and 12.
 * @{
 */
#define TMRA_CNT_DOWN_COND_INVD                      (0U)                    /*!< TMRA hardware count down condition is INVALID. */
#define TMRA_CNT_DOWN_COND_CLKA_LOW_CLKB_RISING      (TMRA_HCDOR_HCDO0)      /*!< When CLKA is low, a rising edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKA_LOW_CLKB_FALLING     (TMRA_HCDOR_HCDO1)      /*!< When CLKA is low, a falling edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKA_HIGH_CLKB_RISING     (TMRA_HCDOR_HCDO2)      /*!< When CLKA is high, a rising edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKA_HIGH_CLKB_FALLING    (TMRA_HCDOR_HCDO3)      /*!< When CLKA is high, a falling edge is sampled on CLKB, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKB_LOW_CLKA_RISING      (TMRA_HCDOR_HCDO4)      /*!< When CLKB is low, a rising edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKB_LOW_CLKA_FALLING     (TMRA_HCDOR_HCDO5)      /*!< When CLKB is low, a falling edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING     (TMRA_HCDOR_HCDO6)      /*!< When CLKB is high, a rising edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_FALLING    (TMRA_HCDOR_HCDO7)      /*!< When CLKB is high, a falling edge is sampled on CLKA, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_TRIG_RISING               (TMRA_HCDOR_HCDO8)      /*!< When a rising edge occurred on TRIG, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_TRIG_FALLING              (TMRA_HCDOR_HCDO9)      /*!< When a falling edge occurred on TRIG, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_EVT                       (TMRA_HCDOR_HCDO10)     /*!< When the TMRA common trigger event occurred, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_SYM_OVF                   (TMRA_HCDOR_HCDO11)     /*!< When the symmetric unit overflow, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_SYM_UDF                   (TMRA_HCDOR_HCDO12)     /*!< When the symmetric unit underflow, the counter register counts down. */
#define TMRA_CNT_DOWN_COND_ALL                       (0x1FFFU)
/**
 * @}
 */

/**
 * @defgroup TMRA_Interrupt_Type TMRA Interrupt Type
 * @{
 */
#define TMRA_INT_OVF                        (1UL << 4U)                 /*!< The interrupt of counting overflow. */
#define TMRA_INT_UDF                        (1UL << 5U)                 /*!< The interrupt of counting underflow. */
#define TMRA_INT_CMP_CH1                    (1UL << 16U)                /*!< The interrupt of compare-match of channel 1. */
#define TMRA_INT_CMP_CH2                    (1UL << 17U)                /*!< The interrupt of compare-match of channel 2. */
#define TMRA_INT_CMP_CH3                    (1UL << 18U)                /*!< The interrupt of compare-match of channel 3. */
#define TMRA_INT_CMP_CH4                    (1UL << 19U)                /*!< The interrupt of compare-match of channel 4. */
#define TMRA_INT_ALL                        (0xF0030UL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Event_Type TMRA Event Type
 * @{
 */
#define TMRA_EVT_CMP_CH1                    (TMRA_ECONR_ETEN1)          /*!< The event of compare-match of channel 1. */
#define TMRA_EVT_CMP_CH2                    (TMRA_ECONR_ETEN2)          /*!< The event of compare-match of channel 2. */
#define TMRA_EVT_CMP_CH3                    (TMRA_ECONR_ETEN3)          /*!< The event of compare-match of channel 3. */
#define TMRA_EVT_CMP_CH4                    (TMRA_ECONR_ETEN4)          /*!< The event of compare-match of channel 4. */
#define TMRA_EVT_ALL                        (TMRA_EVT_CMP_CH1 | TMRA_EVT_CMP_CH2 | \
                                             TMRA_EVT_CMP_CH3 | TMRA_EVT_CMP_CH4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Status_Flag TMRA Status Flag
 * @{
 */
#define TMRA_FLAG_OVF                       (1UL << 6U)                 /*!< The flag of counting overflow. */
#define TMRA_FLAG_UDF                       (1UL << 7U)                 /*!< The flag of counting underflow. */
#define TMRA_FLAG_CMP_CH1                   (1UL << 16U)                /*!< The flag of compare-match of channel 1. */
#define TMRA_FLAG_CMP_CH2                   (1UL << 17U)                /*!< The flag of compare-match of channel 2. */
#define TMRA_FLAG_CMP_CH3                   (1UL << 18U)                /*!< The flag of compare-match of channel 3. */
#define TMRA_FLAG_CMP_CH4                   (1UL << 19U)                /*!< The flag of compare-match of channel 4. */
#define TMRA_FLAG_CAPT_AGAIN_CH1            (1UL << 24U)                /*!< The flag of capture occurs again after successful capture of channel 1. */
#define TMRA_FLAG_CAPT_AGAIN_CH2            (1UL << 25U)                /*!< The flag of capture occurs again after successful capture of channel 2. */
#define TMRA_FLAG_CAPT_AGAIN_CH3            (1UL << 26U)                /*!< The flag of capture occurs again after successful capture of channel 3. */
#define TMRA_FLAG_CAPT_AGAIN_CH4            (1UL << 27U)                /*!< The flag of capture occurs again after successful capture of channel 4. */
#define TMRA_FLAG_ALL                       (0xF0F00C0UL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Capture_Cond TMRA Capture Condition
 * @note 'TMRA_CAPT_COND_TRIG_RISING' and 'TMRA_CAPT_COND_TRIG_FALLING' are only valid for channel 4.
 * @{
 */
#define TMRA_CAPT_COND_INVD                 (0x0U)                      /*!< The condition of capture is INVALID. */
#define TMRA_CAPT_COND_PWM_RISING           (TMRA_CCONR_HICP0)          /*!< The condition of capture is a rising edge is sampled on pin TIMA_<t>_PWMn. */
#define TMRA_CAPT_COND_PWM_FALLING          (TMRA_CCONR_HICP1)          /*!< The condition of capture is a falling edge is sampled on pin TIMA_<t>_PWMn. */
#define TMRA_CAPT_COND_EVT                  (TMRA_CCONR_HICP2)          /*!< The condition of capture is the specified event occurred. */
#define TMRA_CAPT_COND_TRIG_RISING          (TMRA_CCONR_HICP3)          /*!< The condition of capture is a rising edge is sampled on pin TIMA_<t>_TRIG.
                                                                            This condition is only valid for channel 4. */
#define TMRA_CAPT_COND_TRIG_FALLING         (TMRA_CCONR_HICP4)          /*!< The condition of capture is a falling edge is sampled on pin TIMA_<t>_TRIG.
                                                                            This condition is only valid for channel 4. */
#define TMRA_CAPT_COND_ALL                  (TMRA_CAPT_COND_PWM_RISING | TMRA_CAPT_COND_PWM_FALLING | \
                                             TMRA_CAPT_COND_EVT | TMRA_CAPT_COND_TRIG_RISING | \
                                             TMRA_CAPT_COND_TRIG_FALLING)

/**
 * @}
 */

/**
 * @defgroup TMRA_Cmp_Value_Buf_Trans_Cond TMRA Compare Value Buffer Transmission Condition
 * @{
 */
#define TMRA_BUF_TRANS_COND_OVF_UDF_CLR     (0x0U)                      /*!< This configuration value applies to non-triangular wave counting mode.
                                                                             When counting overflow or underflow or counting register was cleared,
                                                                             transfer CMPARm(m=2,4,6,8,...) to CMPARn(n=1,3,5,7,...). */
#define TMRA_BUF_TRANS_COND_PEAK            (TMRA_BCONR_BSE0)           /*!< In triangle wave count mode, when count reached peak,
                                                                             transfer CMPARm(m=2,4,6,8,...) to CMPARn(n=1,3,5,7,...). */
#define TMRA_BUF_TRANS_COND_VALLEY          (TMRA_BCONR_BSE1)           /*!< In triangle wave count mode, when count reached valley,
                                                                             transfer CMPARm(m=2,4,6,8,...) to CMPARn(n=1,3,5,7,.... */
#define TMRA_BUF_TRANS_COND_PEAK_VALLEY     (TMRA_BCONR_BSE1 | \
                                             TMRA_BCONR_BSE0)           /*!< In triangle wave count mode, when count reached peak or valley,
                                                                             transfer CMPARm(m=2,4,6,8,...) to CMPARn(n=1,3,5,7,...). */
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Clock_Divider TMRA Filter Clock Divider
 * @{
 */
#define TMRA_FILTER_CLK_DIV1                (0x0U)                      /*!< The filter clock is the clock of TimerA / 1 */
#define TMRA_FILTER_CLK_DIV4                (0x1U)                      /*!< The filter clock is the clock of TimerA / 4 */
#define TMRA_FILTER_CLK_DIV16               (0x2U)                      /*!< The filter clock is the clock of TimerA / 16 */
#define TMRA_FILTER_CLK_DIV64               (0x3U)                      /*!< The filter clock is the clock of TimerA / 64 */
/**
 * @}
 */

/**
 * @defgroup TMRA_Counter_State TMRA Counter State
 * @{
 */
#define TMRA_CNT_STAT_START                 (0U)                        /*!< Counter start counting. */
#define TMRA_CNT_STAT_STOP                  (1U)                        /*!< Counter stop counting. */
#define TMRA_CNT_STAT_MATCH_CMP             (2U)                        /*!< Counter value matches the compare value. */
#define TMRA_CNT_STAT_MATCH_PERIOD          (3U)                        /*!< Counter value matches the period value. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Polarity TMRA PWM Polarity
 * @{
 */
#define TMRA_PWM_LOW                        (0x0U)                      /*!< PWM output low. */
#define TMRA_PWM_HIGH                       (0x1U)                      /*!< PWM output high. */
#define TMRA_PWM_HOLD                       (0x2U)                      /*!< PWM output holds the current polarity. */
#define TMRA_PWM_INVT                       (0x3U)                      /*!< PWM output reverses the current polarity. */
/**
 * @}
 */

/**
 * @defgroup TMRA_PWM_Force_Polarity TMRA PWM Force Polarity
 * @{
 */
#define TMRA_PWM_FORCE_INVD                 (0x0U)                      /*!< Force polarity is invalid. */
#define TMRA_PWM_FORCE_LOW                  (TMRA_PCONR_FORC_1)         /*!< Force the PWM output low at the beginning of the next cycle.
                                                                             The beginning of the next cycle: overflow position or underflow position
                                                                             of sawtooth wave; valley position of triangle wave. */
#define TMRA_PWM_FORCE_HIGH                 (TMRA_PCONR_FORC)           /*!< Force the PWM output high at the beginning of the next cycle.
                                                                             The beginning of the next cycle: overflow position or underflow position
                                                                             of sawtooth wave; valley position of triangle wave. */
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Start_Condition TMRA Hardware Start Condition
 * @{
 */
#define TMRA_START_COND_INVD                (0x0U)                      /*!< The condition of start is INVALID. */
#define TMRA_START_COND_TRIG_RISING         (TMRA_HCONR_HSTA0)          /*!< 1. Sync start is invalid: The condition is that a rising edge is sampled on TRIG of the current TMRA unit.
                                                                             2. Sync start is valid: The condition is that a rising edge is sampled on TRIG of the symmetric TMRA unit. */
#define TMRA_START_COND_TRIG_FALLING        (TMRA_HCONR_HSTA1)          /*!< 1. Sync start is invalid: The condition is that a falling edge is sampled on TRIG of the current TMRA unit.
                                                                             2. Sync start is valid: The condition is that a falling edge is sampled on TRIG of the symmetric TMRA unit. */
#define TMRA_START_COND_EVT                 (TMRA_HCONR_HSTA2)          /*!< The condition is that the TMRA common trigger event has occurred. */
#define TMRA_START_COND_ALL                 (TMRA_START_COND_TRIG_RISING | TMRA_START_COND_TRIG_FALLING | \
                                             TMRA_START_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Stop_Condition TMRA Hardware Stop Condition
 * @{
 */
#define TMRA_STOP_COND_INVD                 (0x0U)                      /*!< The condition of stop is INVALID. */
#define TMRA_STOP_COND_TRIG_RISING          (TMRA_HCONR_HSTP0)          /*!< The condition is that a rising edge is sampled on pin TRIG of the current TMRA unit. */
#define TMRA_STOP_COND_TRIG_FALLING         (TMRA_HCONR_HSTP1)          /*!< The condition is that a falling edge is sampled on pin TRIG of the current TMRA unit. */
#define TMRA_STOP_COND_EVT                  (TMRA_HCONR_HSTP2)          /*!< The condition is that the TMRA common trigger event has occurred. */
#define TMRA_STOP_COND_ALL                  (TMRA_STOP_COND_TRIG_RISING | TMRA_STOP_COND_TRIG_FALLING | \
                                             TMRA_STOP_COND_EVT)
/**
 * @}
 */

/**
 * @defgroup TMRA_Hardware_Clear_Condition TMRA Hardware Clear Condition
 * @note Symmetric units: unit 1 and 2; unit 3 and 4; ... ; unit 11 and 12.
 * @{
 */
#define TMRA_CLR_COND_INVD                  (0x0U)                      /*!< The condition of clear is INVALID. */
#define TMRA_CLR_COND_TRIG_RISING           (TMRA_HCONR_HCLE0)          /*!< The condition is that a rising edge is sampled on TRIG of the current TMRA unit. */
#define TMRA_CLR_COND_TRIG_FALLING          (TMRA_HCONR_HCLE1)          /*!< The condition is that a falling edge is sampled on TRIG of the current TMRA unit. */
#define TMRA_CLR_COND_EVT                   (TMRA_HCONR_HCLE2)          /*!< The condition is that the TMRA common trigger event has occurred. */
#define TMRA_CLR_COND_SYM_TRIG_RISING       (TMRA_HCONR_HCLE3)          /*!< The condition is that a rising edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_SYM_TRIG_FALLING      (TMRA_HCONR_HCLE4)          /*!< The condition is that a falling edge is sampled on TRIG of the symmetric unit. */
#define TMRA_CLR_COND_PWM3_RISING           (TMRA_HCONR_HCLE5)          /*!< The condition is that a rising edge is sampled on PWM3 of the current TMRA unit. */
#define TMRA_CLR_COND_PWM3_FALLING          (TMRA_HCONR_HCLE6)          /*!< The condition is that a falling edge is sampled on PWM3 of the current TMRA unit. */
#define TMRA_CLR_COND_ALL                   (TMRA_CLR_COND_TRIG_RISING | TMRA_CLR_COND_TRIG_FALLING | \
                                             TMRA_CLR_COND_EVT| TMRA_CLR_COND_SYM_TRIG_RISING | \
                                             TMRA_CLR_COND_SYM_TRIG_FALLING | TMRA_CLR_COND_PWM3_RISING| \
                                             TMRA_CLR_COND_PWM3_FALLING)
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
/* Base count(use software clock PCLK/HCLK) */
int32_t TMRA_Init(CM_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcTmraInit);
int32_t TMRA_StructInit(stc_tmra_init_t *pstcTmraInit);
void TMRA_SetCountMode(CM_TMRA_TypeDef *TMRAx, uint8_t u8Mode);
void TMRA_SetCountDir(CM_TMRA_TypeDef *TMRAx, uint8_t u8Dir);
void TMRA_SetClockDiv(CM_TMRA_TypeDef *TMRAx, uint8_t u8Div);

/* Hardware count */
void TMRA_HWCountUpCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWCountDownCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
/* Set function mode */
void TMRA_SetFunc(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Func);

/* Ouput compare */
int32_t TMRA_PWM_Init(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, const stc_tmra_pwm_init_t *pstcPwmInit);
int32_t TMRA_PWM_StructInit(stc_tmra_pwm_init_t *pstcPwmInit);
void TMRA_PWM_OutputCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState);
void TMRA_PWM_SetPolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint8_t u8CountState, uint16_t u16Polarity);
void TMRA_PWM_SetForcePolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Polarity);
/* Input capture */
void TMRA_HWCaptureCondCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState);

/* Trigger: hardware trigger to start/stop/clear the counter */
void TMRA_HWStartCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWStopCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);
void TMRA_HWClearCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState);

/* Filter */
void TMRA_SetFilterClockDiv(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, uint16_t u16Div);
void TMRA_FilterCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, en_functional_state_t enNewState);

/* Global */
void TMRA_DeInit(CM_TMRA_TypeDef *TMRAx);
/* Counting direction, period value, counter value, compare value */
uint8_t TMRA_GetCountDir(const CM_TMRA_TypeDef *TMRAx);

void TMRA_SetPeriodValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Value);
uint32_t TMRA_GetPeriodValue(const CM_TMRA_TypeDef *TMRAx);
void TMRA_SetCountValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Value);
uint32_t TMRA_GetCountValue(const CM_TMRA_TypeDef *TMRAx);
void TMRA_SetCompareValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint32_t u32Value);
uint32_t TMRA_GetCompareValue(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch);

/* Sync start */
void TMRA_SyncStartCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);
/* Reload and continue counting when overflow/underflow */
void TMRA_CountReloadCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState);

void TMRA_SetCompareBufCond(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond);
void TMRA_CompareBufCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState);

en_flag_status_t TMRA_GetStatus(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Flag);
void TMRA_ClearStatus(CM_TMRA_TypeDef *TMRAx, uint32_t u32Flag);
void TMRA_IntCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState);
void TMRA_EventCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32EventType, en_functional_state_t enNewState);
void TMRA_Start(CM_TMRA_TypeDef *TMRAx);
void TMRA_Stop(CM_TMRA_TypeDef *TMRAx);

/**
 * @}
 */

#endif /* LL_TMRA_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_TMRA_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

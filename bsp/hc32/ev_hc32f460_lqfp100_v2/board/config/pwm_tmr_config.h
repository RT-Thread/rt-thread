/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-22     CDT               first version
 */

#ifndef __PWM_TMR_CONFIG_H__
#define __PWM_TMR_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PWM_TMRA

#ifdef BSP_USING_PWM_TMRA_1
#ifndef PWM_TMRA_1_CONFIG
#define PWM_TMRA_1_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a1",             \
        .instance                       = CM_TMRA_1,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_1_CONFIG */
#endif /* BSP_USING_PWM_TMRA_1 */

#ifdef BSP_USING_PWM_TMRA_2
#ifndef PWM_TMRA_2_CONFIG
#define PWM_TMRA_2_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a2",             \
        .instance                       = CM_TMRA_2,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_2_CONFIG */
#endif /* BSP_USING_PWM_TMRA_2 */

#ifdef BSP_USING_PWM_TMRA_3
#ifndef PWM_TMRA_3_CONFIG
#define PWM_TMRA_3_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a3",             \
        .instance                       = CM_TMRA_3,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_3_CONFIG */
#endif /* BSP_USING_PWM_TMRA_3 */

#ifdef BSP_USING_PWM_TMRA_4
#ifndef PWM_TMRA_4_CONFIG
#define PWM_TMRA_4_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a4",             \
        .instance                       = CM_TMRA_4,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_4_CONFIG */
#endif /* BSP_USING_PWM_TMRA_4 */

#ifdef BSP_USING_PWM_TMRA_5
#ifndef PWM_TMRA_5_CONFIG
#define PWM_TMRA_5_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a5",             \
        .instance                       = CM_TMRA_5,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_5_CONFIG */
#endif /* BSP_USING_PWM_TMRA_5 */

#ifdef BSP_USING_PWM_TMRA_6
#ifndef PWM_TMRA_6_CONFIG
#define PWM_TMRA_6_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_a6",             \
        .instance                       = CM_TMRA_6,            \
        .channel                        = 0,                    \
        .stcTmraInit =                                          \
        {                                                       \
            .u8CountSrc                 = TMRA_CNT_SRC_SW,      \
            .u32PeriodValue             = 0xFFFF,               \
            .sw_count =                                         \
            {                                                   \
                .u8ClockDiv             = TMRA_CLK_DIV1,        \
                .u8CountMode            = TMRA_MD_SAWTOOTH,     \
                .u8CountDir             = TMRA_DIR_DOWN,        \
            },                                                  \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            .u32CompareValue            = 0x0000,               \
            .u16StartPolarity           = TMRA_PWM_LOW,         \
            .u16StopPolarity            = TMRA_PWM_LOW,         \
            .u16CompareMatchPolarity    = TMRA_PWM_HIGH,        \
            .u16PeriodMatchPolarity     = TMRA_PWM_LOW,         \
        },                                                      \
    }
#endif /* PWM_TMRA_6_CONFIG */
#endif /* BSP_USING_PWM_TMRA_6 */

#endif /* BSP_USING_PWM_TMRA */

#ifdef BSP_USING_PWM_TMR4

#ifdef BSP_USING_PWM_TMR4_1
#ifndef PWM_TMR4_1_CONFIG
#define PWM_TMR4_1_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t41",            \
        .instance                       = CM_TMR4_1,            \
        .channel                        = 0,                    \
        .stcTmr4Init =                                          \
        {                                                       \
            .u16ClockDiv                = TMR4_CLK_DIV1,        \
            .u16PeriodValue             = 0xFFFFU,              \
            .u16CountMode               = TMR4_MD_SAWTOOTH,     \
            .u16ClockSrc               = TMR4_CLK_SRC_INTERNCLK,\
        },                                                      \
        .stcTmr4OcInit =                                        \
        {                                                       \
            .u16CompareValue            = 0x0000,               \
            .u16OcInvalidPolarity       = TMR4_OC_INVD_LOW,     \
            .u16CompareModeBufCond     = TMR4_OC_BUF_COND_IMMED,\
            .u16CompareValueBufCond    = TMR4_OC_BUF_COND_PEAK, \
            .u16BufLinkTransObject      = 0U,                   \
        },                                                      \
        .stcTmr4PwmInit =                                       \
        {                                                       \
            .u16Mode                    = TMR4_PWM_MD_THROUGH,  \
            .u16ClockDiv                = TMR4_PWM_CLK_DIV1,    \
            .u16Polarity           = TMR4_PWM_OXH_HOLD_OXL_HOLD,\
        },                                                      \
    }
#endif /* PWM_TMR4_1_CONFIG */
#endif /* BSP_USING_PWM_TMR4_1 */

#ifdef BSP_USING_PWM_TMR4_2
#ifndef PWM_TMR4_2_CONFIG
#define PWM_TMR4_2_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t42",            \
        .instance                       = CM_TMR4_2,            \
        .channel                        = 0,                    \
        .stcTmr4Init =                                          \
        {                                                       \
            .u16ClockDiv                = TMR4_CLK_DIV1,        \
            .u16PeriodValue             = 0xFFFFU,              \
            .u16CountMode               = TMR4_MD_SAWTOOTH,     \
            .u16ClockSrc               = TMR4_CLK_SRC_INTERNCLK,\
        },                                                      \
        .stcTmr4OcInit =                                        \
        {                                                       \
            .u16CompareValue            = 0x0000,               \
            .u16OcInvalidPolarity       = TMR4_OC_INVD_LOW,     \
            .u16CompareModeBufCond     = TMR4_OC_BUF_COND_IMMED,\
            .u16CompareValueBufCond    = TMR4_OC_BUF_COND_PEAK, \
            .u16BufLinkTransObject      = 0U,                   \
        },                                                      \
        .stcTmr4PwmInit =                                       \
        {                                                       \
            .u16Mode                    = TMR4_PWM_MD_THROUGH,  \
            .u16ClockDiv                = TMR4_PWM_CLK_DIV1,    \
            .u16Polarity           = TMR4_PWM_OXH_HOLD_OXL_HOLD,\
        },                                                      \
    }
#endif /* PWM_TMR4_2_CONFIG */
#endif /* BSP_USING_PWM_TMR4_2 */

#ifdef BSP_USING_PWM_TMR4_3
#ifndef PWM_TMR4_3_CONFIG
#define PWM_TMR4_3_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t43",            \
        .instance                       = CM_TMR4_3,            \
        .channel                        = 0,                    \
        .stcTmr4Init =                                          \
        {                                                       \
            .u16ClockDiv                = TMR4_CLK_DIV1,        \
            .u16PeriodValue             = 0xFFFFU,              \
            .u16CountMode               = TMR4_MD_SAWTOOTH,     \
            .u16ClockSrc               = TMR4_CLK_SRC_INTERNCLK,\
        },                                                      \
        .stcTmr4OcInit =                                        \
        {                                                       \
            .u16CompareValue            = 0x0000,               \
            .u16OcInvalidPolarity       = TMR4_OC_INVD_LOW,     \
            .u16CompareModeBufCond     = TMR4_OC_BUF_COND_IMMED,\
            .u16CompareValueBufCond    = TMR4_OC_BUF_COND_PEAK, \
            .u16BufLinkTransObject      = 0U,                   \
        },                                                      \
        .stcTmr4PwmInit =                                       \
        {                                                       \
            .u16Mode                    = TMR4_PWM_MD_THROUGH,  \
            .u16ClockDiv                = TMR4_PWM_CLK_DIV1,    \
            .u16Polarity           = TMR4_PWM_OXH_HOLD_OXL_HOLD,\
        },                                                      \
    }
#endif /* PWM_TMR4_3_CONFIG */
#endif /* BSP_USING_PWM_TMR4_3 */

#endif /* BSP_USING_PWM_TMR4 */

#ifdef BSP_USING_PWM_TMR6

#ifdef BSP_USING_PWM_TMR6_1
#ifndef PWM_TMR6_1_CONFIG
#define PWM_TMR6_1_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t61",            \
        .instance                       = CM_TMR6_1,            \
        .channel                        = 0,                    \
        .stcTmr6Init =                                          \
        {                                                       \
            .u8CountSrc                 = TMR6_CNT_SRC_SW,      \
            .sw_count =                                         \
            {                                                   \
                .u32ClockDiv            = TMR6_CLK_DIV1,        \
                .u32CountMode           = TMR6_MD_SAWTOOTH,     \
                .u32CountDir            = TMR6_CNT_UP,          \
            },                                                  \
            .u32PeriodValue             = 0xFFFF,               \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_HIGH,    \
                .u32StopPolarity            = TMR6_PWM_HIGH,    \
                .u32CompareMatchPolarity    = TMR6_PWM_LOW,     \
                .u32PeriodMatchPolarity     = TMR6_PWM_HIGH,    \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            },                                                  \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_HIGH,    \
                .u32StopPolarity            = TMR6_PWM_HIGH,    \
                .u32CompareMatchPolarity    = TMR6_PWM_LOW,     \
                .u32PeriodMatchPolarity     = TMR6_PWM_HIGH,    \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            }                                                   \
        },                                                      \
    }
#endif /* PWM_TMR6_1_CONFIG */
#endif /* BSP_USING_PWM_TMR6_1 */
#ifdef BSP_USING_PWM_TMR6_2
#ifndef PWM_TMR6_2_CONFIG
#define PWM_TMR6_2_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t61",            \
        .instance                       = CM_TMR6_2,            \
        .channel                        = 0,                    \
        .stcTmr6Init =                                          \
        {                                                       \
            .u8CountSrc                 = TMR6_CNT_SRC_SW,      \
            .sw_count =                                         \
            {                                                   \
                .u32ClockDiv            = TMR6_CLK_DIV1,        \
                .u32CountMode           = TMR6_MD_SAWTOOTH,     \
                .u32CountDir            = TMR6_CNT_DOWN,        \
            },                                                  \
            .u32PeriodValue             = 0xFFFF,               \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_LOW,     \
                .u32StopPolarity            = TMR6_PWM_LOW,     \
                .u32CompareMatchPolarity    = TMR6_PWM_HIGH,    \
                .u32PeriodMatchPolarity     = TMR6_PWM_LOW,     \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            },                                                  \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_LOW,     \
                .u32StopPolarity            = TMR6_PWM_LOW,     \
                .u32CompareMatchPolarity    = TMR6_PWM_HIGH,    \
                .u32PeriodMatchPolarity     = TMR6_PWM_LOW,     \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            }                                                   \
        },                                                      \
    }
#endif /* PWM_TMR6_2_CONFIG */
#endif /* BSP_USING_PWM_TMR6_2 */
#ifdef BSP_USING_PWM_TMR6_3
#ifndef PWM_TMR6_3_CONFIG
#define PWM_TMR6_3_CONFIG                                       \
    {                                                           \
        .name                           = "pwm_t61",            \
        .instance                       = CM_TMR6_3,            \
        .channel                        = 0,                    \
        .stcTmr6Init =                                          \
        {                                                       \
            .u8CountSrc                 = TMR6_CNT_SRC_SW,      \
            .sw_count =                                         \
            {                                                   \
                .u32ClockDiv            = TMR6_CLK_DIV1,        \
                .u32CountMode           = TMR6_MD_SAWTOOTH,     \
                .u32CountDir            = TMR6_CNT_DOWN,        \
            },                                                  \
            .u32PeriodValue             = 0xFFFF,               \
        },                                                      \
        .stcPwmInit =                                           \
        {                                                       \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_LOW,     \
                .u32StopPolarity            = TMR6_PWM_LOW,     \
                .u32CompareMatchPolarity    = TMR6_PWM_HIGH,    \
                .u32PeriodMatchPolarity     = TMR6_PWM_LOW,     \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            },                                                  \
            {                                                   \
                .u32CompareValue            = 0x0000,           \
                .u32StartPolarity           = TMR6_PWM_LOW,     \
                .u32StopPolarity            = TMR6_PWM_LOW,     \
                .u32CompareMatchPolarity    = TMR6_PWM_HIGH,    \
                .u32PeriodMatchPolarity     = TMR6_PWM_LOW,     \
                .u32StartStopHold   = TMR6_PWM_START_STOP_HOLD, \
            }                                                   \
        },                                                      \
    }
#endif /* PWM_TMR6_3_CONFIG */
#endif /* BSP_USING_PWM_TMR6_3 */

#endif /* BSP_USING_PWM_TMR6 */

#ifdef __cplusplus
}
#endif

#endif /* __PWM_TMRA_CONFIG_H__ */

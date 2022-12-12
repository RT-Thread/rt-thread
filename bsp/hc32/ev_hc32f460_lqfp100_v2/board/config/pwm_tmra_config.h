/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-06-27     lianghongquan     first version
 */

#ifndef __PWM_TMRA_CONFIG_H__
#define __PWM_TMRA_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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
                .u16ClockDiv            = TMRA_CLK_DIV1,        \
                .u16CountMode           = TMRA_MD_SAWTOOTH,     \
                .u16CountDir            = TMRA_DIR_DOWN,        \
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


#ifdef __cplusplus
}
#endif

#endif /* __PWM_TMRA_CONFIG_H__ */

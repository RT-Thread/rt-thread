/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 * 2020-07-10     lik          rewrite
 */

#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include "board.h"

struct swm_pwm_cfg
{
    const char *name;
    PWM_TypeDef *PWMx;
    PWM_InitStructure pwm_initstruct;
};

struct swm_pwm
{
    struct swm_pwm_cfg *cfg;
    struct rt_device_pwm pwm_device;
};

#ifdef BSP_USING_PWM0
#ifndef PWM0_CFG
#define PWM0_CFG                                \
    {                                           \
        .name = "pwm0",                         \
        .PWMx = PWM0,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM0_CFG */
#endif /* BSP_USING_PWM0 */

#ifdef BSP_USING_PWM1
#ifndef PWM1_CFG
#define PWM1_CFG                                \
    {                                           \
        .name = "pwm1",                         \
        .PWMx = PWM1,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM1_CFG */
#endif /* BSP_USING_PWM1 */

#ifdef BSP_USING_PWM2
#ifndef PWM2_CFG
#define PWM2_CFG                                \
    {                                           \
        .name = "pwm2",                         \
        .PWMx = PWM2,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM2_CFG */
#endif /* BSP_USING_PWM2 */

#ifdef BSP_USING_PWM3
#ifndef PWM3_CFG
#define PWM3_CFG                                \
    {                                           \
        .name = "pwm3",                         \
        .PWMx = PWM3,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM3_CFG */
#endif /* BSP_USING_PWM3 */

#ifdef BSP_USING_PWM4
#ifndef PWM4_CFG
#define PWM4_CFG                                \
    {                                           \
        .name = "pwm4",                         \
        .PWMx = PWM4,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM4_CFG */
#endif /* BSP_USING_PWM4 */

#ifdef BSP_USING_PWM5
#ifndef PWM5_CFG
#define PWM5_CFG                                \
    {                                           \
        .name = "pwm5",                         \
        .PWMx = PWM5,                           \
        .pwm_initstruct.clk_div = PWM_CLKDIV_8, \
        .pwm_initstruct.mode = PWM_MODE_INDEP,  \
        .pwm_initstruct.cycleA = 10000,         \
        .pwm_initstruct.hdutyA = 5000,          \
        .pwm_initstruct.initLevelA = 1,         \
        .pwm_initstruct.cycleB = 10000,         \
        .pwm_initstruct.hdutyB = 5000,          \
        .pwm_initstruct.initLevelB = 1,         \
        .pwm_initstruct.HEndAIEn = 0,           \
        .pwm_initstruct.NCycleAIEn = 0,         \
        .pwm_initstruct.HEndBIEn = 0,           \
        .pwm_initstruct.NCycleBIEn = 0,         \
    }
#endif /* PWM5_CFG */
#endif /* BSP_USING_PWM5 */

int rt_hw_pwm_init(void);

#endif /* __DRV_PWM_H__ */

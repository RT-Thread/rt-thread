/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-06-27     lianghongquan     first version
 * 2023-02-22     CDT               add hc32f4a0 support
 */

#include <board.h>

#include "drv_config.h"
#include <drivers/dev_pwm.h>
#include <pwm_tmr_config.h>

#if defined(BSP_USING_PWM)

//#define DRV_DEBUG
#define LOG_TAG             "drv_pwm"
#include <drv_log.h>

#if defined(BSP_USING_PWM_TMRA)

#if defined(HC32F460)
    #define TMRA_CHANNEL_NUM_MAX     8U
#elif defined(HC32F4A0)
    #define TMRA_CHANNEL_NUM_MAX     4U
#endif

enum
{
#ifdef BSP_USING_PWM_TMRA_1
    PWM_TMRA_1_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_2
    PWM_TMRA_2_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_3
    PWM_TMRA_3_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_4
    PWM_TMRA_4_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_5
    PWM_TMRA_5_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_6
    PWM_TMRA_6_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_7
    PWM_TMRA_7_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_8
    PWM_TMRA_8_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_9
    PWM_TMRA_9_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_10
    PWM_TMRA_10_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_11
    PWM_TMRA_11_INDEX,
#endif
#ifdef BSP_USING_PWM_TMRA_12
    PWM_TMRA_12_INDEX,
#endif
    PWM_TMRA_UNIT_NUM,
};

struct hc32_pwm_tmra
{
    struct rt_device_pwm pwm_device;
    char *name;
    CM_TMRA_TypeDef *instance;
    rt_uint32_t channel;
    uint32_t CompareValue[TMRA_CHANNEL_NUM_MAX];
    rt_bool_t complementary[TMRA_CHANNEL_NUM_MAX];
    stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_init_t stcPwmInit;
};

static struct hc32_pwm_tmra g_pwm_tmra_array[] =
{
#ifdef BSP_USING_PWM_TMRA_1
    PWM_TMRA_1_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_2
    PWM_TMRA_2_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_3
    PWM_TMRA_3_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_4
    PWM_TMRA_4_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_5
    PWM_TMRA_5_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_6
    PWM_TMRA_6_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_7
    PWM_TMRA_7_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_8
    PWM_TMRA_8_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_9
    PWM_TMRA_9_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_10
    PWM_TMRA_10_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_11
    PWM_TMRA_11_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMRA_12
    PWM_TMRA_12_CONFIG,
#endif
};

static rt_uint32_t tmra_get_clk_notdiv(CM_TMRA_TypeDef *TMRAx)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t u32BusName;

#if defined(HC32F4A0)
    switch ((rt_uint32_t)TMRAx)
    {
    case (rt_uint32_t)CM_TMRA_1:
    case (rt_uint32_t)CM_TMRA_2:
    case (rt_uint32_t)CM_TMRA_3:
    case (rt_uint32_t)CM_TMRA_4:
        u32BusName = CLK_BUS_PCLK0;
        break;
    default:
        u32BusName = CLK_BUS_PCLK1;     /* Uint5-12 */
        break;
    }
#elif defined(HC32F460)
    u32BusName = CLK_BUS_PCLK1;
#endif
    u32clkFreq = CLK_GetBusClockFreq(u32BusName);

    return (u32clkFreq ? u32clkFreq : HCLK_VALUE);
}

static rt_uint32_t tmra_get_clk_bydiv(CM_TMRA_TypeDef *TMRAx)
{
    rt_uint32_t u32clkFreq;
    uint16_t u16Div;

    u32clkFreq = tmra_get_clk_notdiv(TMRAx);
    u16Div = (READ_REG16(TMRAx->BCSTRL) & TMRA_BCSTRL_CKDIV);
    switch (u16Div)
    {
    case (TMRA_CLK_DIV1):
        break;
    case (TMRA_CLK_DIV2):
        u32clkFreq /= 2;
        break;
    case (TMRA_CLK_DIV4):
        u32clkFreq /= 4;
        break;
    case (TMRA_CLK_DIV8):
        u32clkFreq /= 8;
        break;
    case (TMRA_CLK_DIV16):
        u32clkFreq /= 16;
        break;
    case (TMRA_CLK_DIV32):
        u32clkFreq /= 32;
        break;
    case (TMRA_CLK_DIV64):
        u32clkFreq /= 64;
        break;
    case (TMRA_CLK_DIV128):
        u32clkFreq /= 128;
        break;
    case (TMRA_CLK_DIV256):
        u32clkFreq /= 256;
        break;
    case (TMRA_CLK_DIV512):
        u32clkFreq /= 512;
        break;
    case (TMRA_CLK_DIV1024):
        u32clkFreq /= 1024;
        break;
    default:
        break;
    }
    return u32clkFreq;
}

static void tmra_duyt100or0_output(CM_TMRA_TypeDef *TMRAx, uint32_t channel, uint32_t CompareValue)
{
    if ((TMRA_GetPeriodValue(TMRAx) + 1) == CompareValue)
    {
        TMRA_PWM_SetForcePolarity(TMRAx, channel, TMRA_PWM_FORCE_HIGH);
    }
    else if (CompareValue <= 1)
    {
        TMRA_PWM_SetForcePolarity(TMRAx, channel, TMRA_PWM_FORCE_LOW);
    }
    else
    {
        TMRA_PWM_SetForcePolarity(TMRAx, (channel), TMRA_PWM_FORCE_INVD);
    }
}

static rt_err_t tmra_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    struct hc32_pwm_tmra *pwm = (struct hc32_pwm_tmra *)device;
    CM_TMRA_TypeDef *TMRAx = pwm->instance;
    rt_uint32_t compare_value = TMRA_GetCompareValue(TMRAx, configuration->channel) + 1;
    if (configuration->complementary)
    {
        return -RT_EPERM;
    }

    tmra_duyt100or0_output(TMRAx, configuration->channel, compare_value);

    if (enable)
    {
        TMRA_PWM_OutputCmd(TMRAx, configuration->channel, ENABLE);
    }
    else
    {
        TMRA_PWM_OutputCmd(TMRAx, configuration->channel, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t tmra_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    struct hc32_pwm_tmra *pwm = (struct hc32_pwm_tmra *)device;
    CM_TMRA_TypeDef *TMRAx = pwm->instance;
    u32clkFreq = tmra_get_clk_bydiv(TMRAx);
    configuration->period = (rt_uint64_t)1000000000UL * (TMRA_GetPeriodValue(TMRAx) + 1) / u32clkFreq;
    configuration->pulse = (rt_uint64_t)1000000000UL * (TMRA_GetCompareValue(TMRAx, configuration->channel) + 1) / u32clkFreq;
    return RT_EOK;
}

static rt_uint32_t tmra_auto_set_div(CM_TMRA_TypeDef *TMRAx, uint32_t period)
{
    rt_uint8_t i;
    rt_uint32_t u32clkFreq, division;
    rt_uint64_t period_value;

    u32clkFreq = tmra_get_clk_notdiv(TMRAx);
    period_value = (rt_uint64_t)period * u32clkFreq / (rt_uint64_t)1000000000UL;
    if (!period_value)
    {
        return 0;
    }

    division = period_value / 0xFFFF + 1;

    for (i = 0; i <= 10; i++)
    {
        if (division == 1)
        {
            break;
        }
        division = division / 2 + division % 2;
    }
    if (i > 10)
    {
        return 0;
    }

    TMRA_SetClockDiv(TMRAx, i << TMRA_BCSTRL_CKDIV_POS);
    u32clkFreq = tmra_get_clk_bydiv(TMRAx);

    return u32clkFreq;
}

static rt_err_t tmra_pwm_set_period(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t period_value, compare_value;
    rt_uint32_t *compare_value_channelx = (rt_uint32_t *)device->parent.user_data;
    struct hc32_pwm_tmra *pwm = (struct hc32_pwm_tmra *)device;
    CM_TMRA_TypeDef *TMRAx = pwm->instance;

    /* if need to modify the clock division */
    u32clkFreq = tmra_auto_set_div(TMRAx, configuration->period);
    if (!u32clkFreq)
    {
        return -RT_ERROR;
    }
    period_value = configuration->period * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
    period_value =  period_value > 1 ? period_value - 1 : 1;
    TMRA_SetPeriodValue(TMRAx, period_value);

    /* setting PeriodValue maybe change the div,so we need to recalculate the CompareValue */
    for (rt_uint32_t i = 0; i < TMRA_CHANNEL_NUM_MAX; i++)
    {
        if (pwm->channel & (0x01UL << i))
        {
            compare_value = (*(compare_value_channelx + i)) * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
            compare_value = compare_value >= period_value ? period_value : compare_value > 1 ? compare_value - 1 : compare_value;
            TMRA_SetCompareValue(TMRAx, i, compare_value);
            tmra_duyt100or0_output(TMRAx, i, compare_value + 1);
        }
    }

    return RT_EOK;
}

static rt_err_t tmra_pwm_set_pulse(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t compare_value, period_value;
    rt_uint32_t *compare_value_channel = (rt_uint32_t *)device->parent.user_data;
    struct hc32_pwm_tmra *pwm = (struct hc32_pwm_tmra *)device;
    CM_TMRA_TypeDef *TMRAx = pwm->instance;

    u32clkFreq = tmra_get_clk_bydiv(TMRAx);
    period_value = TMRA_GetPeriodValue(TMRAx) + 1;
    compare_value = configuration->pulse * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
    compare_value = compare_value > period_value ? period_value - 1 : compare_value > 1 ? compare_value - 1 : compare_value;
    TMRA_SetCompareValue(TMRAx, configuration->channel, compare_value);
    tmra_duyt100or0_output(TMRAx, configuration->channel, compare_value + 1);

    *(compare_value_channel + configuration->channel) = configuration->pulse;

    return RT_EOK;
}

static rt_err_t tmra_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    tmra_pwm_set_period(device, configuration);
    tmra_pwm_set_pulse(device, configuration);

    return RT_EOK;
}

static rt_err_t pwm_tmra_init(struct hc32_pwm_tmra *device)
{
    CM_TMRA_TypeDef *TMRAx;
    uint32_t i;
    RT_ASSERT(device != RT_NULL);

    TMRAx = device->instance;
    TMRA_Init(TMRAx, &device->stcTmraInit);
    for (i = 0; i < TMRA_CHANNEL_NUM_MAX; i++)
    {
        if ((device->channel >> i) & 0x01)
        {
            TMRA_PWM_Init(TMRAx, i, &device->stcPwmInit);
        }
    }
    TMRA_Start(TMRAx);

    return RT_EOK;
}

static void pwm_tmra_get_channel(void)
{
#ifdef BSP_USING_PWM_TMRA_1
#ifdef BSP_USING_PWM_TMRA_1_CH1
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH2
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH3
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH4
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH5
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH6
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH7
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH8
    g_pwm_tmra_array[PWM_TMRA_1_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_2
#ifdef BSP_USING_PWM_TMRA_2_CH1
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH2
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH3
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH4
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH5
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH6
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH7
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH8
    g_pwm_tmra_array[PWM_TMRA_2_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_3
#ifdef BSP_USING_PWM_TMRA_3_CH1
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH2
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH3
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH4
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH5
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH6
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH7
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_3_CH8
    g_pwm_tmra_array[PWM_TMRA_3_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_4
#ifdef BSP_USING_PWM_TMRA_4_CH1
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH2
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH3
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH4
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH5
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH6
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH7
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH8
    g_pwm_tmra_array[PWM_TMRA_4_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_5
#ifdef BSP_USING_PWM_TMRA_5_CH1
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH2
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH3
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH4
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH5
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH6
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH7
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH8
    g_pwm_tmra_array[PWM_TMRA_5_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_6
#ifdef BSP_USING_PWM_TMRA_6_CH1
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH2
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH3
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH4
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH5
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH6
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 5);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH7
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 6);
#endif
#ifdef BSP_USING_PWM_TMRA_6_CH8
    g_pwm_tmra_array[PWM_TMRA_6_INDEX].channel |= (1 << 7);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_7
#ifdef BSP_USING_PWM_TMRA_7_CH1
    g_pwm_tmra_array[PWM_TMRA_7_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_7_CH2
    g_pwm_tmra_array[PWM_TMRA_7_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_7_CH3
    g_pwm_tmra_array[PWM_TMRA_7_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_7_CH4
    g_pwm_tmra_array[PWM_TMRA_7_INDEX].channel |= (1 << 3);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_8
#ifdef BSP_USING_PWM_TMRA_8_CH1
    g_pwm_tmra_array[PWM_TMRA_8_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_8_CH2
    g_pwm_tmra_array[PWM_TMRA_8_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_8_CH3
    g_pwm_tmra_array[PWM_TMRA_8_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_8_CH4
    g_pwm_tmra_array[PWM_TMRA_8_INDEX].channel |= (1 << 3);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_9
#ifdef BSP_USING_PWM_TMRA_9_CH1
    g_pwm_tmra_array[PWM_TMRA_9_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_9_CH2
    g_pwm_tmra_array[PWM_TMRA_9_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_9_CH3
    g_pwm_tmra_array[PWM_TMRA_9_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_9_CH4
    g_pwm_tmra_array[PWM_TMRA_9_INDEX].channel |= (1 << 3);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_10
#ifdef BSP_USING_PWM_TMRA_10_CH1
    g_pwm_tmra_array[PWM_TMRA_10_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_10_CH2
    g_pwm_tmra_array[PWM_TMRA_10_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_10_CH3
    g_pwm_tmra_array[PWM_TMRA_10_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_10_CH4
    g_pwm_tmra_array[PWM_TMRA_10_INDEX].channel |= (1 << 3);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_11
#ifdef BSP_USING_PWM_TMRA_11_CH1
    g_pwm_tmra_array[PWM_TMRA_11_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_11_CH2
    g_pwm_tmra_array[PWM_TMRA_11_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_11_CH3
    g_pwm_tmra_array[PWM_TMRA_11_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_11_CH4
    g_pwm_tmra_array[PWM_TMRA_11_INDEX].channel |= (1 << 3);
#endif
#endif
#ifdef BSP_USING_PWM_TMRA_12
#ifdef BSP_USING_PWM_TMRA_12_CH1
    g_pwm_tmra_array[PWM_TMRA_12_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMRA_12_CH2
    g_pwm_tmra_array[PWM_TMRA_12_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMRA_12_CH3
    g_pwm_tmra_array[PWM_TMRA_12_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMRA_12_CH4
    g_pwm_tmra_array[PWM_TMRA_12_INDEX].channel |= (1 << 3);
#endif
#endif
}

static void enable_tmra_unit_clk(void)
{
#ifdef BSP_USING_PWM_TMRA_1
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_1, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_2
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_2, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_3
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_3, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_4
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_4, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_5
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_5, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_6
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_6, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_7
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_7, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_8
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_8, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_9
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_9, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_10
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_10, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_11
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_11, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMRA_12
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_12, ENABLE);
#endif
}

static rt_err_t _tmra_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    if (!configuration->channel)    return -RT_EINVAL;

    configuration->channel = (configuration->channel - 1) % TMRA_CHANNEL_NUM_MAX;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return tmra_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return tmra_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return tmra_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return tmra_pwm_get(device, configuration);
    case PWM_CMD_SET_PERIOD:
        return tmra_pwm_set_period(device, configuration);
    case PWM_CMD_SET_PULSE:
        return tmra_pwm_set_pulse(device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _tmra_ops =
{
    _tmra_pwm_control
};

#endif  /* BSP_USING_PWM_TMRA */

#if defined(BSP_USING_PWM_TMR4)

#define TMR4_CHANNEL_NUM_MAX     6U

enum
{
#ifdef BSP_USING_PWM_TMR4_1
    PWM_TMR4_1_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR4_2
    PWM_TMR4_2_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR4_3
    PWM_TMR4_3_INDEX,
#endif
    PWM_TMR4_UNIT_NUM,
};

struct hc32_pwm_tmr4
{
    struct rt_device_pwm pwm_device;
    char *name;
    CM_TMR4_TypeDef *instance;
    rt_uint32_t channel;
    rt_uint32_t PeriodValue;
    rt_uint32_t CompareValue[TMR4_CHANNEL_NUM_MAX];
    stc_tmr4_init_t stcTmr4Init;
    stc_tmr4_oc_init_t stcTmr4OcInit;
    stc_tmr4_pwm_init_t stcTmr4PwmInit;
};

static struct hc32_pwm_tmr4 g_pwm_tmr4_array[] =
{
#ifdef BSP_USING_PWM_TMR4_1
    PWM_TMR4_1_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR4_2
    PWM_TMR4_2_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR4_3
    PWM_TMR4_3_CONFIG,
#endif
};

static rt_uint32_t tmr4_get_clk_notdiv(CM_TMR4_TypeDef *TMR4x)
{
    rt_uint32_t u32clkFreq;
    switch ((rt_uint32_t)TMR4x)
    {
    case (rt_uint32_t)CM_TMR4_1:
    case (rt_uint32_t)CM_TMR4_2:
    case (rt_uint32_t)CM_TMR4_3:
#if defined(HC32F4A0)
        u32clkFreq = CLK_GetBusClockFreq(CLK_BUS_PCLK0);
#elif defined(HC32F460)
        u32clkFreq = CLK_GetBusClockFreq(CLK_BUS_PCLK1);
#endif
        break;
    default:
        break;
    }
    return (u32clkFreq ? u32clkFreq : HCLK_VALUE);
}

static rt_uint32_t tmr4_get_clk_bydiv(CM_TMR4_TypeDef *TMR4x)
{
    rt_uint32_t u32clkFreq;
    uint16_t u16Div;

    u32clkFreq = tmr4_get_clk_notdiv(TMR4x);
    u16Div = (READ_REG16(TMR4x->CCSR) & TMR4_CCSR_CKDIV);
    switch (u16Div)
    {
    case (TMR4_CLK_DIV1):
        break;
    case (TMR4_CLK_DIV2):
        u32clkFreq /= 2;
        break;
    case (TMR4_CLK_DIV4):
        u32clkFreq /= 4;
        break;
    case (TMR4_CLK_DIV8):
        u32clkFreq /= 8;
        break;
    case (TMR4_CLK_DIV16):
        u32clkFreq /= 16;
        break;
    case (TMR4_CLK_DIV32):
        u32clkFreq /= 32;
        break;
    case (TMR4_CLK_DIV64):
        u32clkFreq /= 64;
        break;
    case (TMR4_CLK_DIV128):
        u32clkFreq /= 128;
        break;
    case (TMR4_CLK_DIV256):
        u32clkFreq /= 256;
        break;
    case (TMR4_CLK_DIV512):
        u32clkFreq /= 512;
        break;
    case (TMR4_CLK_DIV1024):
        u32clkFreq /= 1024;
        break;
    default:
        break;
    }
    return u32clkFreq;
}

static rt_err_t tmr4_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    struct hc32_pwm_tmr4 *pwm = (struct hc32_pwm_tmr4 *)device;
    CM_TMR4_TypeDef *TMR4x = pwm->instance;

    if (configuration->complementary)
    {
        return -RT_EPERM;
    }

    if (enable)
    {
        TMR4_OC_Cmd(TMR4x, configuration->channel, ENABLE);
    }
    else
    {
        TMR4_OC_Cmd(TMR4x, configuration->channel, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t tmr4_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    struct hc32_pwm_tmr4 *pwm = (struct hc32_pwm_tmr4 *)device;
    CM_TMR4_TypeDef *TMR4x = pwm->instance;

    u32clkFreq = tmr4_get_clk_bydiv(TMR4x);
    configuration->period = (rt_uint64_t)1000000000UL * (TMR4_GetPeriodValue(TMR4x) + 1) / u32clkFreq;
    configuration->pulse = (rt_uint64_t)1000000000UL * (TMR4_OC_GetCompareValue(TMR4x, configuration->channel) + 1) / u32clkFreq;

    return RT_EOK;
}

static rt_uint32_t tmr4_auto_set_div(CM_TMR4_TypeDef *TMR4x, uint32_t period)
{
    rt_uint8_t i;
    rt_uint32_t u32clkFreq, division;
    rt_uint64_t period_value;

    u32clkFreq = tmr4_get_clk_notdiv(TMR4x);
    period_value = (rt_uint64_t)period * u32clkFreq / (rt_uint64_t)1000000000UL;
    if (!period_value)
    {
        return 0;
    }

    division = period_value / 0xFFFF + 1;

    for (i = 0; i <= 10; i++)
    {
        if (division == 1)
        {
            break;
        }
        division = division / 2 + division % 2;
    }
    if (i > 10)
    {
        return 0;
    }

    TMR4_SetClockDiv(TMR4x, i << TMR4_CCSR_CKDIV_POS);
    u32clkFreq = tmr4_get_clk_bydiv(TMR4x);

    return u32clkFreq;
}

static rt_err_t tmr4_pwm_set_period(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t period_value, compare_value;
    rt_uint32_t *compare_value_channelx = (rt_uint32_t *)device->parent.user_data;
    struct hc32_pwm_tmr4 *pwm = (struct hc32_pwm_tmr4 *)device;
    CM_TMR4_TypeDef *TMR4x = pwm->instance;

    u32clkFreq = tmr4_auto_set_div(TMR4x, configuration->period);
    if (!u32clkFreq)
    {
        return -RT_ERROR;
    }
    period_value = configuration->period * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
    period_value =  period_value > 1 ? period_value - 1 : 1;
    TMR4_SetPeriodValue(TMR4x, period_value);

    for (rt_uint32_t i = 0; i < TMR4_CHANNEL_NUM_MAX; i++)
    {
        if (pwm->channel & (0x01UL << i))
        {
            compare_value = (*(compare_value_channelx + i)) * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
            compare_value = compare_value >= period_value ? period_value : compare_value > 1 ? compare_value - 1 : compare_value;
            TMR4_OC_SetCompareValue(TMR4x, i, compare_value);
        }
    }

    return RT_EOK;
}

static void tmr4_pwm_set_cmpmode(CM_TMR4_TypeDef *TMR4x, uint32_t channel)
{
    un_tmr4_oc_ocmrh_t unTmr4OcOcmrh;
    un_tmr4_oc_ocmrl_t unTmr4OcOcmrl;
    uint32_t ch = channel % TMR4_CHANNEL_NUM_MAX;
    if (ch % 2)
    {
        /* TMR4 OC low channel: compare mode OCMR[31:0] 0x4A60 4A6F = b 0100 1010 0110 0000   0100 1010 0110 1111 */
        unTmr4OcOcmrl.OCMRx = 0x4A604A6FU;
        TMR4_OC_SetLowChCompareMode(TMR4x, ch, unTmr4OcOcmrl);
    }
    else
    {
        /* TMR4 OC high channel: compare mode OCMR[15:0] = 0x4A6F = b 0100 1010 0110 1111 */
        unTmr4OcOcmrh.OCMRx = 0x4A6F;
        TMR4_OC_SetHighChCompareMode(TMR4x, ch, unTmr4OcOcmrh);
    }
}

static rt_err_t tmr4_pwm_set_pulse(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t compare_value, period_value;
    rt_uint32_t *compare_value_channelx = (rt_uint32_t *)device->parent.user_data;
    struct hc32_pwm_tmr4 *pwm = (struct hc32_pwm_tmr4 *)device;
    CM_TMR4_TypeDef *TMR4x = pwm->instance;

    u32clkFreq = tmr4_get_clk_bydiv(TMR4x);
    period_value = TMR4_GetPeriodValue(TMR4x) + 1;
    compare_value = (rt_uint64_t)configuration->pulse * u32clkFreq / (rt_uint64_t)1000000000;;
    compare_value = compare_value > period_value ? period_value - 1 : compare_value > 1 ? compare_value - 1 : compare_value;

    TMR4_OC_SetCompareValue(TMR4x, configuration->channel, compare_value);
    *(compare_value_channelx +  configuration->channel) = configuration->pulse;

    return RT_EOK;
}

static rt_err_t tmr4_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    tmr4_pwm_set_period(device, configuration);
    tmr4_pwm_set_pulse(device, configuration);

    return RT_EOK;
}

static void enable_tmr4_unit_clk(void)
{
#ifdef BSP_USING_PWM_TMR4_1
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR4_1, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR4_2
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR4_2, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR4_3
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR4_3, ENABLE);
#endif
}

static rt_err_t pwm_tmr4_init(struct hc32_pwm_tmr4 *device)
{
    CM_TMR4_TypeDef *TMR4x;
    uint32_t i;
    RT_ASSERT(device != RT_NULL);

    TMR4x = device->instance;
    TMR4_Init(TMR4x, &device->stcTmr4Init);
    for (i = 0; i < TMR4_CHANNEL_NUM_MAX; i++)
    {
        if ((device->channel >> i) & 0x01)
        {
            TMR4_OC_Init(TMR4x, i, &device->stcTmr4OcInit);
            TMR4_PWM_Init(TMR4x, (i >> 1), &device->stcTmr4PwmInit);
#if defined(HC32F4A0)
            TMR4_PWM_SetPortOutputMode(TMR4x, i, TMR4_PWM_PIN_OUTPUT_NORMAL);
#endif
            tmr4_pwm_set_cmpmode(TMR4x, i);
        }
    }
#if defined(HC32F4A0)
    TMR4_PWM_MainOutputCmd(TMR4x, ENABLE);
#endif
    TMR4_Start(TMR4x);

    return RT_EOK;
}

static void pwm_tmr4_get_channel(void)
{
#ifdef BSP_USING_PWM_TMR4_1
#ifdef BSP_USING_PWM_TMR4_1_OUH
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OUL
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OVH
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OVL
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OWH
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OWL
    g_pwm_tmr4_array[PWM_TMR4_1_INDEX].channel |= (1 << 5);
#endif
#endif
#ifdef BSP_USING_PWM_TMR4_2
#ifdef BSP_USING_PWM_TMR4_2_OUH
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR4_2_OUL
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMR4_2_OVH
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMR4_2_OVL
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMR4_2_OWH
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMR4_2_OWL
    g_pwm_tmr4_array[PWM_TMR4_2_INDEX].channel |= (1 << 5);
#endif
#endif
#ifdef BSP_USING_PWM_TMR4_3
#ifdef BSP_USING_PWM_TMR4_3_OUH
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR4_3_OUL
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 1);
#endif
#ifdef BSP_USING_PWM_TMR4_3_OVH
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 2);
#endif
#ifdef BSP_USING_PWM_TMR4_3_OVL
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 3);
#endif
#ifdef BSP_USING_PWM_TMR4_3_OWH
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 4);
#endif
#ifdef BSP_USING_PWM_TMR4_3_OWL
    g_pwm_tmr4_array[PWM_TMR4_3_INDEX].channel |= (1 << 5);
#endif
#endif
}

static rt_err_t _tmr4_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    if (!configuration->channel) return -RT_EPERM;

    configuration->channel = (configuration->channel - 1) % TMR4_CHANNEL_NUM_MAX;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return tmr4_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return tmr4_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return tmr4_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return tmr4_pwm_get(device, configuration);
    case PWM_CMD_SET_PERIOD:
        return tmr4_pwm_set_period(device, configuration);
    case PWM_CMD_SET_PULSE:
        return tmr4_pwm_set_pulse(device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _tmr4_ops =
{
    _tmr4_pwm_control
};

#endif  /* BSP_USING_PWM_TMR4 */

#if defined(BSP_USING_PWM_TMR6)

#define TMR6_CHANNEL_NUM_MAX     2U

enum
{
#ifdef BSP_USING_PWM_TMR6_1
    PWM_TMR6_1_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_2
    PWM_TMR6_2_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_3
    PWM_TMR6_3_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_4
    PWM_TMR6_4_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_5
    PWM_TMR6_5_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_6
    PWM_TMR6_6_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_7
    PWM_TMR6_7_INDEX,
#endif
#ifdef BSP_USING_PWM_TMR6_8
    PWM_TMR6_8_INDEX,
#endif
    PWM_TMR6_UNIT_NUM,
};

struct hc32_pwm_tmr6
{
    struct rt_device_pwm pwm_device;
    char *name;
    CM_TMR6_TypeDef *instance;
    rt_uint32_t channel;
    stc_tmr6_init_t stcTmr6Init;
    stc_tmr6_pwm_init_t stcPwmInit[TMR6_CHANNEL_NUM_MAX];
    rt_bool_t complementary[TMR6_CHANNEL_NUM_MAX];
};

static struct hc32_pwm_tmr6 g_pwm_tmr6_array[] =
{
#ifdef BSP_USING_PWM_TMR6_1
    PWM_TMR6_1_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_2
    PWM_TMR6_2_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_3
    PWM_TMR6_3_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_4
    PWM_TMR6_4_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_5
    PWM_TMR6_5_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_6
    PWM_TMR6_6_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_7
    PWM_TMR6_7_CONFIG,
#endif
#ifdef BSP_USING_PWM_TMR6_8
    PWM_TMR6_8_CONFIG,
#endif
};

static rt_uint32_t tmr6_get_clk_notdiv(CM_TMR6_TypeDef *TMR6x)
{
    rt_uint32_t u32clkFreq;
    switch ((rt_uint32_t)TMR6x)
    {
    case (rt_uint32_t)CM_TMR6_1:
    case (rt_uint32_t)CM_TMR6_2:
    case (rt_uint32_t)CM_TMR6_3:
#if defined(HC32F4A0)
    case (rt_uint32_t)CM_TMR6_4:
    case (rt_uint32_t)CM_TMR6_5:
    case (rt_uint32_t)CM_TMR6_6:
    case (rt_uint32_t)CM_TMR6_7:
    case (rt_uint32_t)CM_TMR6_8:
#endif
        u32clkFreq = CLK_GetBusClockFreq(CLK_BUS_PCLK0);
        break;
    default:
        break;
    }
    return (u32clkFreq ? u32clkFreq : HCLK_VALUE);
}

static rt_uint32_t tmr6_get_clk_bydiv(CM_TMR6_TypeDef *TMR6x)
{
    rt_uint32_t u32clkFreq;
    uint16_t u16Div;

    u32clkFreq = tmr6_get_clk_notdiv(TMR6x);
    u16Div = (READ_REG16(TMR6x->GCONR) & TMR6_GCONR_CKDIV);
    switch (u16Div)
    {
    case (TMR6_CLK_DIV1):
        break;
    case (TMR6_CLK_DIV2):
        u32clkFreq /= 2;
        break;
    case (TMR6_CLK_DIV4):
        u32clkFreq /= 4;
        break;
    case (TMR6_CLK_DIV8):
        u32clkFreq /= 8;
        break;
    case (TMR6_CLK_DIV16):
        u32clkFreq /= 16;
        break;
    case (TMR6_CLK_DIV64):
        u32clkFreq /= 64;
        break;
    case (TMR6_CLK_DIV256):
        u32clkFreq /= 256;
        break;
    case (TMR6_CLK_DIV1024):
        u32clkFreq /= 1024;
        break;
#if defined(HC32F4A0)
    case (TMR6_CLK_DIV32):
        u32clkFreq /= 32;
        break;
    case (TMR6_CLK_DIV128):
        u32clkFreq /= 128;
        break;
    case (TMR6_CLK_DIV512):
        u32clkFreq /= 512;
        break;
#endif
    default:
        break;
    }
    return u32clkFreq;
}

static void tmr6_duyt100or0_output(CM_TMR6_TypeDef *TMR6x, rt_uint32_t channel, rt_uint32_t compare_value)
{
    if (compare_value <= 1)
    {
#if defined(HC32F4A0)
        TMR6_PWM_SetPolarity(TMR6x, channel, TMR6_STAT_OVF, TMR6_PWM_LOW);
#elif defined(HC32F460)
        TMR6_PWM_SetPolarity(TMR6x, TMR6_STAT_MATCH_PERIOD, TMR6_PWM_LOW);
#endif
    }
    else
    {
#if defined(HC32F4A0)
        TMR6_PWM_SetPolarity(TMR6x, channel, TMR6_STAT_OVF, TMR6_PWM_HIGH);
#elif defined(HC32F460)
        TMR6_PWM_SetPolarity(TMR6x, TMR6_STAT_MATCH_PERIOD, TMR6_PWM_HIGH);
#endif
    }
}

static rt_err_t tmr6_pwm_enable(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint32_t compare_value;
    struct hc32_pwm_tmr6 *pwm = (struct hc32_pwm_tmr6 *)device;
    CM_TMR6_TypeDef *TMR6x = pwm->instance;

    if (configuration->complementary)
    {
        return -RT_EPERM;
    }

    compare_value = TMR6_GetCompareValue(TMR6x, configuration->channel) + 1;
    tmr6_duyt100or0_output(TMR6x, configuration->channel, compare_value);

    if (enable)
    {
        TMR6_PWM_OutputCmd(TMR6x, configuration->channel, ENABLE);
    }
    else
    {
        TMR6_PWM_OutputCmd(TMR6x, configuration->channel, DISABLE);
    }

    return RT_EOK;
}

static rt_err_t tmr6_pwm_get(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    struct hc32_pwm_tmr6 *pwm = (struct hc32_pwm_tmr6 *)device;
    CM_TMR6_TypeDef *TMR6x = pwm->instance;

    u32clkFreq = tmr6_get_clk_bydiv(TMR6x);
    configuration->period = (rt_uint64_t)1000000000UL * (TMR6_GetPeriodValue(TMR6x, TMR6_PERIOD_REG_A) + 1) / u32clkFreq;
    configuration->pulse = (rt_uint64_t)1000000000UL * (TMR6_GetCompareValue(TMR6x, configuration->channel) + 1) / u32clkFreq;
    return RT_EOK;
}

static rt_uint32_t tmr6_auto_set_div(CM_TMR6_TypeDef *TMR6x, uint32_t period)
{
    rt_uint8_t i;
    rt_uint32_t u32clkFreq, division;
    rt_uint64_t period_value;

    u32clkFreq = tmr6_get_clk_notdiv(TMR6x);
    period_value = (rt_uint64_t)period * u32clkFreq / (rt_uint64_t)1000000000UL;
    if (!period_value)
    {
        return 0;
    }

    division = period_value / 0xFFFF + 1;

    for (i = 0; i <= 10; i++)
    {
        if (division == 1)
        {
            break;
        }
        division = division / 2 + division % 2;
    }
    if (i > 10)
    {
        return 0;
    }
    TMR6_SetClockDiv(TMR6x, i << TMR6_GCONR_CKDIV_POS);
    u32clkFreq = tmr6_get_clk_bydiv(TMR6x);

    return u32clkFreq;
}

static rt_err_t tmr6_pwm_set_period(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint8_t i;
    rt_uint32_t compare_value, period_value;
    stc_tmr6_pwm_init_t *pwm_init_t = (stc_tmr6_pwm_init_t *)device->parent.user_data;
    struct hc32_pwm_tmr6 *pwm = (struct hc32_pwm_tmr6 *)device;
    CM_TMR6_TypeDef *TMR6x = pwm->instance;
    rt_uint32_t u32clkFreq = tmr6_auto_set_div(TMR6x, configuration->period);

    if (!u32clkFreq)
    {
        return -RT_ERROR;
    }
    period_value = configuration->period * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
    period_value = period_value > 1 ? period_value - 1 : 1;
    TMR6_SetPeriodValue(TMR6x, TMR6_PERIOD_REG_A, period_value);

    for (i = 0; i < TMR6_CHANNEL_NUM_MAX; i++)
    {
        if (pwm->channel & (0x01UL << i))
        {
            compare_value = (pwm_init_t + i)->u32CompareValue * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
            compare_value = compare_value >= period_value ? period_value : compare_value > 1 ? compare_value - 1 : compare_value;
            TMR6_SetCompareValue(TMR6x, i, compare_value);
            tmr6_duyt100or0_output(TMR6x, i, compare_value + 1);
        }
    }
    return RT_EOK;
}

static rt_err_t tmr6_pwm_set_pulse(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t u32clkFreq;
    rt_uint32_t compare_value, period_value;
    stc_tmr6_pwm_init_t *pwm_init_t = (stc_tmr6_pwm_init_t *)device->parent.user_data;
    struct hc32_pwm_tmr6 *pwm = (struct hc32_pwm_tmr6 *)device;
    CM_TMR6_TypeDef *TMR6x = pwm->instance;

    u32clkFreq = tmr6_get_clk_bydiv(TMR6x);
    period_value = TMR6_GetPeriodValue(TMR6x, TMR6_PERIOD_REG_A) + 1;

    compare_value = configuration->pulse * (rt_uint64_t)u32clkFreq / (rt_uint64_t)1000000000;
    compare_value = compare_value > period_value ? period_value - 1 : compare_value > 1 ? compare_value - 1 : compare_value;

    TMR6_SetCompareValue(TMR6x, configuration->channel, compare_value);
    tmr6_duyt100or0_output(TMR6x, configuration->channel, compare_value + 1);
    (pwm_init_t + configuration->channel)->u32CompareValue = configuration->pulse;

    return RT_EOK;
}

static rt_err_t tmr6_pwm_set(struct rt_device_pwm *device, struct rt_pwm_configuration *configuration)
{
    tmr6_pwm_set_period(device, configuration);
    tmr6_pwm_set_pulse(device, configuration);

    return RT_EOK;
}

static void enable_tmr6_unit_clk(void)
{
#ifdef BSP_USING_PWM_TMR6_1
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_1, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_2
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_2, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_3
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_3, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_4
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_4, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_5
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_5, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_6
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_6, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_7
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_7, ENABLE);
#endif
#ifdef BSP_USING_PWM_TMR6_8
    FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMR6_8, ENABLE);
#endif
}

static rt_err_t pwm_tmr6_init(struct hc32_pwm_tmr6 *device)
{
    CM_TMR6_TypeDef *TMR6x;
    uint32_t i;
    RT_ASSERT(device != RT_NULL);

    TMR6x = device->instance;
    TMR6_Init(TMR6x, &device->stcTmr6Init);
    for (i = 0; i < TMR6_CHANNEL_NUM_MAX; i++)
    {
        if ((device->channel >> i) & 0x01)
        {
            TMR6_PWM_Init(TMR6x, i, &device->stcPwmInit[i]);
        }
    }
    TMR6_Start(TMR6x);

    return RT_EOK;
}

static void pwm_tmr6_get_channel(void)
{
#ifdef BSP_USING_PWM_TMR6_1
#ifdef BSP_USING_PWM_TMR6_1_A
    g_pwm_tmr6_array[PWM_TMR6_1_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_1_B
    g_pwm_tmr6_array[PWM_TMR6_1_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_2
#ifdef BSP_USING_PWM_TMR6_2_A
    g_pwm_tmr6_array[PWM_TMR6_2_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_2_B
    g_pwm_tmr6_array[PWM_TMR6_2_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_3
#ifdef BSP_USING_PWM_TMR6_3_A
    g_pwm_tmr6_array[PWM_TMR6_3_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_3_B
    g_pwm_tmr6_array[PWM_TMR6_3_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_4
#ifdef BSP_USING_PWM_TMR6_4_A
    g_pwm_tmr6_array[PWM_TMR6_4_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_4_B
    g_pwm_tmr6_array[PWM_TMR6_4_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_5
#ifdef BSP_USING_PWM_TMR6_5_A
    g_pwm_tmr6_array[PWM_TMR6_5_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_5_B
    g_pwm_tmr6_array[PWM_TMR6_5_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_6
#ifdef BSP_USING_PWM_TMR6_6_A
    g_pwm_tmr6_array[PWM_TMR6_6_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_6_B
    g_pwm_tmr6_array[PWM_TMR6_6_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_7
#ifdef BSP_USING_PWM_TMR6_7_A
    g_pwm_tmr6_array[PWM_TMR6_7_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_7_B
    g_pwm_tmr6_array[PWM_TMR6_7_INDEX].channel |= (1 << 1);
#endif
#endif
#ifdef BSP_USING_PWM_TMR6_8
#ifdef BSP_USING_PWM_TMR6_8_A
    g_pwm_tmr6_array[PWM_TMR6_8_INDEX].channel |= (1 << 0);
#endif
#ifdef BSP_USING_PWM_TMR6_8_B
    g_pwm_tmr6_array[PWM_TMR6_8_INDEX].channel |= (1 << 1);
#endif
#endif
}

static rt_err_t _tmr6_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    if (!configuration->channel)    return -RT_EINVAL;

    configuration->channel = (configuration->channel - 1) % TMR6_CHANNEL_NUM_MAX;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return tmr6_pwm_enable(device, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return tmr6_pwm_enable(device, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return tmr6_pwm_set(device, configuration);
    case PWM_CMD_GET:
        return tmr6_pwm_get(device, configuration);
    case PWM_CMD_SET_PERIOD:
        return tmr6_pwm_set_period(device, configuration);
    case PWM_CMD_SET_PULSE:
        return tmr6_pwm_set_pulse(device, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _tmr6_ops =
{
    _tmr6_pwm_control
};

#endif  /* BSP_USING_PWM_TMR6 */

static int rt_hw_pwm_tmr_init(void)
{
    int i = 0;
    rt_err_t result = RT_EOK;

#if defined(BSP_USING_PWM_TMRA)
    pwm_tmra_get_channel();
    enable_tmra_unit_clk();
    for (i = 0; i < sizeof(g_pwm_tmra_array) / sizeof(g_pwm_tmra_array[0]); i++)
    {
        /* pwm init */
        pwm_tmra_init(&g_pwm_tmra_array[i]);
        /* gpio init */
        extern rt_err_t rt_hw_board_pwm_tmra_init(CM_TMRA_TypeDef * TMRAx);
        rt_hw_board_pwm_tmra_init(g_pwm_tmra_array[i].instance);
        /* register pwm device */
        result = rt_device_pwm_register(&g_pwm_tmra_array[i].pwm_device, g_pwm_tmra_array[i].name, &_tmra_ops, &g_pwm_tmra_array[i].CompareValue[0]);
        RT_ASSERT(result == RT_EOK);
    }
#endif

#if defined(BSP_USING_PWM_TMR4)
    pwm_tmr4_get_channel();
    enable_tmr4_unit_clk();
    for (i = 0; i < sizeof(g_pwm_tmr4_array) / sizeof(g_pwm_tmr4_array[0]); i++)
    {
        /* pwm init */
        pwm_tmr4_init(&g_pwm_tmr4_array[i]);
        /* gpio init */
        extern rt_err_t rt_hw_board_pwm_tmr4_init(CM_TMR4_TypeDef * TMR4x);
        rt_hw_board_pwm_tmr4_init(g_pwm_tmr4_array[i].instance);
        /* register pwm device */
        result = rt_device_pwm_register(&g_pwm_tmr4_array[i].pwm_device, g_pwm_tmr4_array[i].name, &_tmr4_ops, &g_pwm_tmr4_array[i].CompareValue[0]);
        RT_ASSERT(result == RT_EOK);
    }
#endif

#if defined(BSP_USING_PWM_TMR6)
    pwm_tmr6_get_channel();
    enable_tmr6_unit_clk();
    for (i = 0; i < sizeof(g_pwm_tmr6_array) / sizeof(g_pwm_tmr6_array[0]); i++)
    {
        /* pwm init */
        pwm_tmr6_init(&g_pwm_tmr6_array[i]);
        /* gpio init */
        extern rt_err_t rt_hw_board_pwm_tmr6_init(CM_TMR6_TypeDef * TMR6x);
        rt_hw_board_pwm_tmr6_init(g_pwm_tmr6_array[i].instance);
        /* register pwm device */
        result = rt_device_pwm_register(&g_pwm_tmr6_array[i].pwm_device, g_pwm_tmr6_array[i].name, &_tmr6_ops, &g_pwm_tmr6_array[i].stcPwmInit[0]);
        RT_ASSERT(result == RT_EOK);
    }
#endif

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_tmr_init);

#endif  /* BSP_USING_PWM */

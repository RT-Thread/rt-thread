/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "drv_common.h"

#ifdef RT_USING_PWM
#include "drv_pwm.h"
#include <drivers/rt_drv_pwm.h>

//#define DRV_DEBUG
#define LOG_TAG                         "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD                      65535

struct rt_device_pwm pwm_device;

struct at32_pwm
{
    struct rt_device_pwm pwm_device;
    tmr_type* tmr_x;
    rt_uint8_t channel;
    char *name;
};

enum
{
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
#ifdef BSP_USING_PWM4
    PWM4_INDEX,
#endif
#ifdef BSP_USING_PWM5
    PWM5_INDEX,
#endif
#ifdef BSP_USING_PWM6
    PWM6_INDEX,
#endif
#ifdef BSP_USING_PWM7
    PWM7_INDEX,
#endif
#ifdef BSP_USING_PWM8
    PWM8_INDEX,
#endif
#ifdef BSP_USING_PWM9
    PWM9_INDEX,
#endif
#ifdef BSP_USING_PWM10
    PWM10_INDEX,
#endif
#ifdef BSP_USING_PWM11
    PWM11_INDEX,
#endif
#ifdef BSP_USING_PWM12
    PWM12_INDEX,
#endif
#ifdef BSP_USING_PWM13
    PWM13_INDEX,
#endif
};

static struct at32_pwm at32_pwm_obj[] =
{
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif

#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif

#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif

#ifdef BSP_USING_PWM4
    PWM4_CONFIG,
#endif

#ifdef BSP_USING_PWM5
    PWM5_CONFIG,
#endif

#ifdef BSP_USING_PWM6
    PWM6_CONFIG,
#endif

#ifdef BSP_USING_PWM7
    PWM7_CONFIG,
#endif

#ifdef BSP_USING_PWM8
    PWM8_CONFIG,
#endif

#ifdef BSP_USING_PWM9
    PWM9_CONFIG,
#endif

#ifdef BSP_USING_PWM10
    PWM10_CONFIG,
#endif

#ifdef BSP_USING_PWM11
    PWM11_CONFIG,
#endif

#ifdef BSP_USING_PWM12
    PWM12_CONFIG,
#endif

#ifdef BSP_USING_PWM13
    PWM13_CONFIG,
#endif
};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static void tmr_pclk_get(rt_uint32_t *pclk1_doubler, rt_uint32_t *pclk2_doubler)
{
    crm_clocks_freq_type  clocks_struct;

    *pclk1_doubler = 1;
    *pclk2_doubler = 1;

    crm_clocks_freq_get(&clocks_struct);

    if(clocks_struct.ahb_freq != clocks_struct.apb1_freq)
    {
        *pclk1_doubler = 2;
    }

    if(clocks_struct.ahb_freq != clocks_struct.apb2_freq)
    {
        *pclk2_doubler = 2;
    }
}

static rt_err_t drv_pwm_enable(tmr_type* tmr_x, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    /* get the value of channel */
    rt_uint32_t channel = configuration->channel;

    if (!configuration->complementary)
    {
        if (!enable)
        {
            if(channel == 1)
            {
               tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_1, FALSE);
            }
            else if(channel == 2)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_2, FALSE);
            }
            else if(channel == 3)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_3, FALSE);
            }
            else if(channel == 4)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_4, FALSE);
            }
        }
        else
        {
            if(channel == 1)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_1, TRUE);
            }
            else if(channel == 2)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_2, TRUE);
            }
            else if(channel == 3)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_3, TRUE);
            }
            else if(channel == 4)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_4, TRUE);
            }
        }
    }
    else
    {
        if (!enable)
        {
            if(channel == 1)
            {
               tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_1C, FALSE);
            }
            else if(channel == 2)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_2C, FALSE);
            }
            else if(channel == 3)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_3C, FALSE);
            }
        }
        else
        {
            if(channel == 1)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_1C, TRUE);
            }
            else if(channel == 2)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_2C, TRUE);
            }
            else if(channel == 3)
            {
              tmr_channel_enable(tmr_x, TMR_SELECT_CHANNEL_3C, TRUE);
            }
        }
    }

    /* tmr_x enable counter */
    tmr_counter_enable(tmr_x, TRUE);

    return RT_EOK;
}

static rt_err_t drv_pwm_get(tmr_type* tmr_x, struct rt_pwm_configuration *configuration)
{
    crm_clocks_freq_type clocks_struct;
    rt_uint32_t pr, div, c1dt, c2dt, c3dt, c4dt;
    rt_uint32_t pclk1_doubler = 0, pclk2_doubler = 0;
    rt_uint32_t channel = configuration->channel;
    rt_uint64_t tmr_clock;

    pr = tmr_x->pr;
    div = tmr_x->div;
    c1dt = tmr_x->c1dt;
    c2dt = tmr_x->c2dt;
    c3dt = tmr_x->c3dt;
    c4dt = tmr_x->c4dt;

    tmr_pclk_get(&pclk1_doubler, &pclk2_doubler);

    crm_clocks_freq_get(&clocks_struct);

    if(
#if defined (TMR1)
    (tmr_x == TMR1)
#endif
#if defined (TMR8)
    || (tmr_x == TMR8)
#endif
#if defined (TMR9)
    || (tmr_x == TMR9)
#endif
#if defined (TMR10)
    || (tmr_x == TMR10)
#endif
#if defined (TMR11)
    || (tmr_x == TMR11)
#endif
    )
    {
        tmr_clock = clocks_struct.apb2_freq * pclk2_doubler;
    }
    else
    {
        tmr_clock = clocks_struct.apb1_freq * pclk1_doubler;
    }

    /* convert nanosecond to frequency and duty cycle. */
    tmr_clock /= 1000000UL;
    configuration->period = (pr + 1) * (div + 1) * 1000UL / tmr_clock;

    if(channel == 1)
        configuration->pulse = (c1dt) * (div + 1) * 1000UL / tmr_clock;
    if(channel == 2)
        configuration->pulse = (c2dt) * (div + 1) * 1000UL / tmr_clock;
    if(channel == 3)
        configuration->pulse = (c3dt) * (div + 1) * 1000UL / tmr_clock;
    if(channel == 4)
        configuration->pulse = (c4dt) * (div + 1) * 1000UL / tmr_clock;

    return RT_EOK;
}

static rt_err_t drv_pwm_set(tmr_type* tmr_x, struct rt_pwm_configuration *configuration)
{
    crm_clocks_freq_type clocks_struct;
    tmr_output_config_type tmr_oc_config_struct;
    tmr_channel_select_type channel_select;
    rt_uint32_t period, pulse, channel, tmr_clock;
    rt_uint32_t pclk1_doubler = 0, pclk2_doubler = 0;
    rt_uint64_t psc;

    /* init timer pin and enable clock */
    at32_msp_tmr_init(tmr_x);

    tmr_pclk_get(&pclk1_doubler, &pclk2_doubler);

    crm_clocks_freq_get(&clocks_struct);

    if(
#if defined (TMR1)
    (tmr_x == TMR1)
#endif
#if defined (TMR8)
    || (tmr_x == TMR8)
#endif
#if defined (TMR9)
    || (tmr_x == TMR9)
#endif
#if defined (TMR10)
    || (tmr_x == TMR10)
#endif
#if defined (TMR11)
    || (tmr_x == TMR11)
#endif
    )
    {
        tmr_clock = clocks_struct.apb2_freq * pclk2_doubler;
    }
    else
    {
        tmr_clock = clocks_struct.apb1_freq * pclk1_doubler;
    }

    /* convert nanosecond to frequency and duty cycle. */
    tmr_clock /= 1000000UL;
    /* calculate pwm period */
    period = (unsigned long long)configuration->period * tmr_clock / 1000ULL;;
    psc = period / MAX_PERIOD + 1;
    period = period / psc;
    /* calculate pulse width */
    pulse = (unsigned long long)configuration->pulse * tmr_clock / psc / 1000ULL;
    /* get channel parameter */
    channel = configuration->channel;

    /* tmr base init */
    tmr_base_init(tmr_x, period - 1, psc - 1);
    tmr_clock_source_div_set(tmr_x, TMR_CLOCK_DIV1);

    /* pwm mode configuration */
    tmr_output_default_para_init(&tmr_oc_config_struct);
    /* config pwm mode */
    tmr_oc_config_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;

    if (!configuration->complementary)
    {
        tmr_oc_config_struct.oc_idle_state = FALSE;
        tmr_oc_config_struct.oc_output_state = FALSE;
        tmr_oc_config_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    }
    else
    {
        tmr_oc_config_struct.occ_idle_state = FALSE;
        tmr_oc_config_struct.occ_output_state = FALSE;
        tmr_oc_config_struct.occ_polarity = TMR_OUTPUT_ACTIVE_HIGH;
    }

    if(channel == 1)
    {
        channel_select = TMR_SELECT_CHANNEL_1;
    }
    else if(channel == 2)
    {
        channel_select = TMR_SELECT_CHANNEL_2;
    }
    else if(channel == 3)
    {
        channel_select = TMR_SELECT_CHANNEL_3;
    }
    else if(channel == 4)
    {
        channel_select = TMR_SELECT_CHANNEL_4;
    }

    /* config tmr pwm output */
    tmr_output_channel_config(tmr_x, channel_select, &tmr_oc_config_struct);
    tmr_output_channel_buffer_enable(tmr_x, channel_select, TRUE);
    tmr_channel_value_set(tmr_x, channel_select, pulse);
    /* enable tmr period buffer */
    tmr_period_buffer_enable(tmr_x, TRUE);
    /* enable output */
    tmr_output_enable(tmr_x, TRUE);

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    tmr_type *tmr_x = (tmr_type *)device->parent.user_data;

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(tmr_x, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(tmr_x, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(tmr_x, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(tmr_x, configuration);
    default:
        return -RT_EINVAL;
    }
}

static void pwm_get_channel(void)
{
#ifdef BSP_USING_PWM1_CH1
    at32_pwm_obj[PWM1_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM1_CH2
    at32_pwm_obj[PWM1_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM1_CH3
    at32_pwm_obj[PWM1_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM1_CH4
    at32_pwm_obj[PWM1_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM2_CH1
    at32_pwm_obj[PWM2_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM2_CH2
    at32_pwm_obj[PWM2_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM2_CH3
    at32_pwm_obj[PWM2_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM2_CH4
    at32_pwm_obj[PWM2_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM3_CH1
    at32_pwm_obj[PWM3_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM3_CH2
    at32_pwm_obj[PWM3_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM3_CH3
    at32_pwm_obj[PWM3_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM3_CH4
    at32_pwm_obj[PWM3_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM4_CH1
    at32_pwm_obj[PWM4_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM4_CH2
    at32_pwm_obj[PWM4_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM4_CH3
    at32_pwm_obj[PWM4_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM4_CH4
    at32_pwm_obj[PWM4_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM5_CH1
    at32_pwm_obj[PWM5_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM5_CH2
    at32_pwm_obj[PWM5_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM5_CH3
    at32_pwm_obj[PWM5_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM5_CH4
    at32_pwm_obj[PWM5_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM6_CH1
    at32_pwm_obj[PWM6_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM6_CH2
    at32_pwm_obj[PWM6_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM6_CH3
    at32_pwm_obj[PWM6_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM6_CH4
    at32_pwm_obj[PWM6_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM7_CH1
    at32_pwm_obj[PWM7_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM7_CH2
    at32_pwm_obj[PWM7_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM7_CH3
    at32_pwm_obj[PWM7_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM7_CH4
    at32_pwm_obj[PWM7_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM8_CH1
    at32_pwm_obj[PWM8_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM8_CH2
    at32_pwm_obj[PWM8_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM8_CH3
    at32_pwm_obj[PWM8_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM8_CH4
    at32_pwm_obj[PWM8_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM9_CH1
    at32_pwm_obj[PWM9_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM9_CH2
    at32_pwm_obj[PWM9_INDEX].channel = 2;
#endif
#ifdef BSP_USING_PWM9_CH3
    at32_pwm_obj[PWM9_INDEX].channel = 3;
#endif
#ifdef BSP_USING_PWM9_CH4
    at32_pwm_obj[PWM9_INDEX].channel = 4;
#endif
#ifdef BSP_USING_PWM12_CH1
    at32_pwm_obj[PWM12_INDEX].channel = 1;
#endif
#ifdef BSP_USING_PWM12_CH2
    at32_pwm_obj[PWM12_INDEX].channel = 2;
#endif
}

static int rt_hw_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    pwm_get_channel();

    for(i = 0; i < sizeof(at32_pwm_obj) / sizeof(at32_pwm_obj[0]); i++)
    {
        if(rt_device_pwm_register(&at32_pwm_obj[i].pwm_device, at32_pwm_obj[i].name, &drv_ops, at32_pwm_obj[i].tmr_x) == RT_EOK)
        {
          LOG_D("%s register success", at32_pwm_obj[i].name);
        }
        else
        {
          LOG_D("%s register failed", at32_pwm_obj[i].name);
          result = -RT_ERROR;
        }
    }

    return result;
}

INIT_BOARD_EXPORT(rt_hw_pwm_init);

#endif /* RT_USING_PWM */

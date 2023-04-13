/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-26     supperthomas first version
 *
 */


#include <board.h>
#include "rtdevice.h"
#include "rtservice.h"

#ifdef RT_USING_PWM

#include <nrfx_pwm.h>

struct mcu_pwm
{
    struct rt_device_pwm pwm_device;

    nrfx_pwm_t *pwm_handle;
    nrf_pwm_values_individual_t m_demo1_seq_values;
    nrf_pwm_sequence_t m_demo1_seq;

    rt_uint8_t channel;
    char *name;
    rt_uint64_t pwm_src_clk;
    uint8_t channel_0_pin;
    uint8_t channel_1_pin;
    uint8_t channel_2_pin;
    uint8_t channel_3_pin;
};

enum
{
#ifdef BSP_USING_PWM0
    PWM0_INDEX,
#endif
#ifdef BSP_USING_PWM1
    PWM1_INDEX,
#endif
#ifdef BSP_USING_PWM2
    PWM2_INDEX,
#endif
#ifdef BSP_USING_PWM3
    PWM3_INDEX,
#endif
};
#ifdef BSP_USING_PWM0
static nrfx_pwm_t m_pwm0 = NRFX_PWM_INSTANCE(0);
#define PWM0_CONFIG                             \
    {                                           \
       .pwm_handle              =  &m_pwm0,     \
       .name                    = "pwm0",       \
       .pwm_src_clk             = 1000000,      \
    }
#endif

#ifdef BSP_USING_PWM1
static nrfx_pwm_t m_pwm1 = NRFX_PWM_INSTANCE(1);
#define PWM1_CONFIG                             \
    {                                           \
       .pwm_handle              =  &m_pwm1,         \
       .name                    = "pwm1",       \
       .pwm_src_clk             = 1000000,             \
    }
#endif

#ifdef BSP_USING_PWM2
static nrfx_pwm_t m_pwm2 = NRFX_PWM_INSTANCE(2);
#define PWM2_CONFIG                             \
    {                                           \
       .pwm_handle              =  &m_pwm2,         \
       .name                    = "pwm2",       \
       .pwm_src_clk             = 1000000,             \
    }
#endif

#ifdef BSP_USING_PWM3
static nrfx_pwm_t m_pwm3 = NRFX_PWM_INSTANCE(3);
#define PWM3_CONFIG                             \
    {                                           \
       .pwm_handle              =  &m_pwm3,         \
       .name                    = "pwm3",       \
       .pwm_src_clk             = 1000000,             \
    }
#endif

static struct mcu_pwm mcu_pwm_obj[] =
{
#ifdef BSP_USING_PWM0
    PWM0_CONFIG,
#endif
#ifdef BSP_USING_PWM1
    PWM1_CONFIG,
#endif

#ifdef BSP_USING_PWM2
    PWM2_CONFIG,
#endif

#ifdef BSP_USING_PWM3
    PWM3_CONFIG,
#endif
};

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg);
static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static rt_err_t drv_pwm_enable(struct mcu_pwm *p_mcu, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    if (!enable)
    {
        nrfx_pwm_stop(p_mcu->pwm_handle, true);
    }
    else
    {
        (void)nrfx_pwm_simple_playback(p_mcu->pwm_handle, &p_mcu->m_demo1_seq, 1, NRFX_PWM_FLAG_LOOP);
    }

    return RT_EOK;
}

uint8_t mcu_get_channel_number(uint8_t channel)
{
    if (channel & 0x01)
    {
        return 0;
    }
    else if (channel & 0x02)
    {
        return 1;
    }
    else if (channel & 0x04)
    {
        return 2;
    }
    else if (channel & 0x08)
    {
        return 3;
    }
    return 0;
}

static rt_err_t drv_pwm_get(struct mcu_pwm *pwm_handle, struct rt_pwm_configuration *configuration)
{
    rt_uint8_t channel_number = mcu_get_channel_number(configuration->channel);
    uint8_t tick_pscond;

    tick_pscond = pwm_handle->pwm_src_clk / 1000000UL;
    configuration->period = pwm_handle->pwm_handle->p_registers->COUNTERTOP * 1000UL / tick_pscond;
    configuration->pulse = pwm_handle->pwm_handle->p_registers->SEQ[channel_number].PTR / tick_pscond;

    return RT_EOK;
}

static void nrfx_set_prioid(nrfx_pwm_t *pwm_handle, uint32_t perioid)
{
    pwm_handle->p_registers->COUNTERTOP = perioid;
}

static rt_err_t drv_pwm_set(struct mcu_pwm *p_mcu, struct rt_pwm_configuration *configuration)
{
    rt_uint32_t period, pulse;
    uint8_t tick_pscond;
    tick_pscond = p_mcu->pwm_src_clk / 1000000UL;

    p_mcu->pwm_handle->p_registers->COUNTERTOP = (unsigned long long)configuration->period * tick_pscond;
    if (configuration->channel & 0x01)
    {
        p_mcu->m_demo1_seq_values.channel_0 = configuration->pulse;
    }

    if (configuration->channel & 0x02)
    {
        p_mcu->m_demo1_seq_values.channel_1 = configuration->pulse;
    }

    if (configuration->channel & 0x04)
    {
        p_mcu->m_demo1_seq_values.channel_2 = configuration->pulse;
    }

    if (configuration->channel & 0x08)
    {
        p_mcu->m_demo1_seq_values.channel_3 = configuration->pulse;
    }
    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    void *pwm_handle = (void *)device->parent.user_data;
    nrfx_pwm_t *p_handle = (nrfx_pwm_t *)pwm_handle;
    struct mcu_pwm *p_mcu = rt_container_of(p_handle, struct mcu_pwm, pwm_handle);
    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(p_mcu, configuration, RT_TRUE);
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(p_mcu, configuration, RT_FALSE);
    case PWM_CMD_SET:
        return drv_pwm_set(p_mcu, configuration);
    case PWM_CMD_GET:
        return drv_pwm_get(p_mcu, configuration);
    default:
        return -RT_EINVAL;
    }
}

static rt_err_t mcu_hw_pwm_init(struct mcu_pwm *device)
{
#define NRFX_PWM_PIN_INVERTED    0x80
#define _PRIO_APP_LOWEST    7
    nrfx_pwm_config_t config0 =
    {
        .irq_priority = _PRIO_APP_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,  //default value
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = 5000,              //default vaule
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
        .step_mode    = NRF_PWM_STEP_AUTO
    };
    rt_err_t result = RT_EOK;
    if (device->pwm_src_clk == 1000000)
    {
        config0.base_clock = NRF_PWM_CLK_1MHz;
    }
    else if (device->pwm_src_clk == 2000000)
    {
        config0.base_clock = NRF_PWM_CLK_2MHz;
    }
    else if (device->pwm_src_clk == 8000000)
    {
        config0.base_clock = NRF_PWM_CLK_8MHz;
    }
    else
    {
        config0.base_clock = NRF_PWM_CLK_1MHz;
    }

    if (device->channel & 0x01)
    {
        config0.output_pins[0] = device->channel_0_pin | NRFX_PWM_PIN_INVERTED;
    }

    if (device->channel & 0x02)
    {
        config0.output_pins[1] = device->channel_1_pin | NRFX_PWM_PIN_INVERTED;
    }

    if (device->channel & 0x04)
    {
        config0.output_pins[2] = device->channel_2_pin | NRFX_PWM_PIN_INVERTED;
    }

    if (device->channel & 0x08)
    {
        config0.output_pins[3] = device->channel_3_pin | NRFX_PWM_PIN_INVERTED;
    }
    device->m_demo1_seq.values.p_individual = &device->m_demo1_seq_values;
    device->m_demo1_seq.length = NRF_PWM_VALUES_LENGTH(device->m_demo1_seq_values),
                        nrfx_pwm_init(device->pwm_handle, &config0, NULL, NULL);
    return result;
}

static void pwm_get_channel(void)
{
#ifdef BSP_USING_PWM0_CH0
    mcu_pwm_obj[PWM0_INDEX].channel |= 1 << 0;
    mcu_pwm_obj[PWM0_INDEX].channel_0_pin = BSP_USING_PWM0_CH0;
#endif
#ifdef BSP_USING_PWM0_CH1
    mcu_pwm_obj[PWM0_INDEX].channel |= 1 << 1;
    mcu_pwm_obj[PWM0_INDEX].channel_1_pin = BSP_USING_PWM0_CH1;
#endif
#ifdef BSP_USING_PWM0_CH2
    mcu_pwm_obj[PWM0_INDEX].channel |= 1 << 2;
    mcu_pwm_obj[PWM0_INDEX].channel_2_pin = BSP_USING_PWM0_CH2;
#endif
#ifdef BSP_USING_PWM0_CH3
    mcu_pwm_obj[PWM0_INDEX].channel |= 1 << 3;
    mcu_pwm_obj[PWM0_INDEX].channel_3_pin = BSP_USING_PWM0_CH3;
#endif
#ifdef BSP_USING_PWM1_CH0
    mcu_pwm_obj[PWM1_INDEX].channel |= 1 << 0;
    mcu_pwm_obj[PWM1_INDEX].channel_0_pin = BSP_USING_PWM1_CH0;
#endif
#ifdef BSP_USING_PWM1_CH1
    mcu_pwm_obj[PWM1_INDEX].channel |= 1 << 1;
    mcu_pwm_obj[PWM1_INDEX].channel_1_pin = BSP_USING_PWM1_CH1;
#endif
#ifdef BSP_USING_PWM1_CH2
    mcu_pwm_obj[PWM1_INDEX].channel |= 1 << 2;
    mcu_pwm_obj[PWM1_INDEX].channel_2_pin = BSP_USING_PWM1_CH2;
#endif
#ifdef BSP_USING_PWM1_CH3
    mcu_pwm_obj[PWM1_INDEX].channel |= 1 << 3;
    mcu_pwm_obj[PWM1_INDEX].channel_3_pin = BSP_USING_PWM1_CH3;
#endif
#ifdef BSP_USING_PWM2_CH0
    mcu_pwm_obj[PWM2_INDEX].channel |= 1 << 0;
    mcu_pwm_obj[PWM2_INDEX].channel_0_pin = BSP_USING_PWM2_CH0;
#endif
#ifdef BSP_USING_PWM2_CH1
    mcu_pwm_obj[PWM2_INDEX].channel |= 1 << 1;
    mcu_pwm_obj[PWM2_INDEX].channel_1_pin = BSP_USING_PWM2_CH1;
#endif
#ifdef BSP_USING_PWM2_CH2
    mcu_pwm_obj[PWM2_INDEX].channel |= 1 << 2;
    mcu_pwm_obj[PWM2_INDEX].channel_2_pin = BSP_USING_PWM2_CH2;
#endif
#ifdef BSP_USING_PWM2_CH3
    mcu_pwm_obj[PWM2_INDEX].channel |= 1 << 3;
    mcu_pwm_obj[PWM2_INDEX].channel_3_pin = BSP_USING_PWM2_CH3;
#endif
#ifdef BSP_USING_PWM3_CH0
    mcu_pwm_obj[PWM3_INDEX].channel |= 1 << 0;
    mcu_pwm_obj[PWM3_INDEX].channel_0_pin = BSP_USING_PWM3_CH0;
#endif
#ifdef BSP_USING_PWM3_CH1
    mcu_pwm_obj[PWM3_INDEX].channel |= 1 << 1;
    mcu_pwm_obj[PWM3_INDEX].channel_1_pin = BSP_USING_PWM3_CH1;
#endif
#ifdef BSP_USING_PWM3_CH2
    mcu_pwm_obj[PWM3_INDEX].channel |= 1 << 2;
    mcu_pwm_obj[PWM3_INDEX].channel_2_pin = BSP_USING_PWM3_CH2;
#endif
#ifdef BSP_USING_PWM3_CH3
    mcu_pwm_obj[PWM3_INDEX].channel |= 1 << 3;
    mcu_pwm_obj[PWM3_INDEX].channel_3_pin = BSP_USING_PWM3_CH3;
#endif
}

static int mcu_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    pwm_get_channel();
    for (i = 0; i < sizeof(mcu_pwm_obj) / sizeof(mcu_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (mcu_hw_pwm_init(&mcu_pwm_obj[i]) != RT_EOK)
        {
            rt_kprintf("\r\n %s init failed", mcu_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            rt_kprintf("\r\n %s init success", mcu_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&mcu_pwm_obj[i].pwm_device, mcu_pwm_obj[i].name, &drv_ops, &mcu_pwm_obj[i].pwm_handle) == RT_EOK)
            {
                rt_kprintf("\r\n %s register success", mcu_pwm_obj[i].name);
            }
            else
            {
                rt_kprintf("\r\n %s register failed", mcu_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }
__exit:
    return result;
}
INIT_DEVICE_EXPORT(mcu_pwm_init);



/* test example */
#define PWM_DEV_NAME        "pwm0"  /* PWM  name*/
#define PWM_DEV_CHANNEL     15       /* PWM  channel */

struct rt_device_pwm *pwm_dev;

static int pwm_led_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir;

    period = 50000;   /* 50ms*/
    dir = 1;
    pulse = 0;


    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return -RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);

    while (1)
    {
        rt_thread_mdelay(50);
        if (dir)
        {
            pulse += 500;
        }
        else
        {
            pulse -= 500;
        }
        if (pulse >= period)
        {
            dir = 0;
        }
        if (0 == pulse)
        {
            dir = 1;
        }


        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    }
}
MSH_CMD_EXPORT(pwm_led_sample, pwm sample);

#endif

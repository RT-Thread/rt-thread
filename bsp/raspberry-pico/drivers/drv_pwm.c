/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-10-20       ChuShicheng      first version
 */
#include "drv_pwm.h"
#include "board.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#ifdef BSP_USING_PWM

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

struct pico_pwm
{
    struct rt_device_pwm pwm_device;
    rt_uint8_t slice_num;
    rt_uint8_t pin_a;
    rt_uint8_t pin_b;
    rt_uint8_t a_all_flag;   /* 1: Two pins simultaneously output PWM A channel */
    rt_uint8_t b_all_flag;   /* 1: Two pins simultaneously output PWM B channel */
    char *name;
};

static struct pico_pwm pico_pwm_obj[] =
{
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .slice_num = 0,
        .pin_a = BSP_PWM0_A_PIN,
        .pin_b = BSP_PWM0_B_PIN,
#ifdef BSP_PWM0_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM0_A_ALL */
#ifdef BSP_PWM0_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM0_B_ALL */
    },
#endif /* BSP_USING_PWM0 */
#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .slice_num = 1,
        .pin_a = BSP_PWM1_A_PIN,
        .pin_b = BSP_PWM1_B_PIN,
#ifdef BSP_PWM1_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM1_A_ALL */
#ifdef BSP_PWM1_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM1_B_ALL */
    },
#endif /* BSP_USING_PWM1 */
#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .slice_num = 2,
        .pin_a = BSP_PWM2_A_PIN,
        .pin_b = BSP_PWM2_B_PIN,
#ifdef BSP_PWM2_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM2_A_ALL */
#ifdef BSP_PWM2_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM2_B_ALL */
    },
#endif /* BSP_USING_PWM2 */
#ifdef BSP_USING_PWM3
    {
        .name = "pwm3",
        .slice_num = 3,
        .pin_a = BSP_PWM3_A_PIN,
        .pin_b = BSP_PWM3_B_PIN,
#ifdef BSP_PWM3_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM3_A_ALL */
#ifdef BSP_PWM3_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM3_B_ALL */
    },
#endif /* BSP_USING_PWM3 */
#ifdef BSP_USING_PWM4
    {
        .name = "pwm4",
        .slice_num = 4,
        .pin_a = BSP_PWM4_A_PIN,
        .pin_b = BSP_PWM4_B_PIN,
#ifdef BSP_PWM4_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM4_A_ALL */
#ifdef BSP_PWM4_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM4_B_ALL */
    },
#endif /* BSP_USING_PWM4 */
#ifdef BSP_USING_PWM5
    {
        .name = "pwm5",
        .slice_num = 5,
        .pin_a = BSP_PWM5_A_PIN,
        .pin_b = BSP_PWM5_B_PIN,
#ifdef BSP_PWM5_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM5_A_ALL */
#ifdef BSP_PWM5_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM5_B_ALL */
    },
#endif /* BSP_USING_PWM5 */
#ifdef BSP_USING_PWM6
    {
        .name = "pwm6",
        .slice_num = 6,
        .pin_a = BSP_PWM6_A_PIN,
        .pin_b = BSP_PWM6_B_PIN,
#ifdef BSP_PWM6_A_ALL
        .a_all_flag = 1,
#endif /* BSP_PWM6_A_ALL */
#ifdef BSP_PWM6_B_ALL
        .b_all_flag = 1,
#endif /* BSP_PWM6_B_ALL */
    },
#endif /* BSP_USING_PWM6 */
#ifdef BSP_USING_PWM7
    {
        .name = "pwm7",
        .slice_num = 7,
        .pin_a = BSP_PWM7_A_PIN,
        .pin_b = BSP_PWM7_B_PIN,
    },
#endif /* BSP_USING_PWM7 */
};


static rt_err_t _pwm_set(rt_uint8_t slice_num, struct rt_pwm_configuration *configuration)
{
    uint32_t period_hz = 1000000000 / configuration->period;
    uint32_t pulse = 1000000000 / configuration->pulse;

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.33f);
    pwm_init(slice_num, &config, true);
    pwm_set_wrap(slice_num, 100000000 / period_hz);
    pwm_set_chan_level(slice_num, configuration->channel, 100000000 / pulse);

    return RT_EOK;
}

static rt_err_t _pwm_get(rt_uint8_t slice_num, struct rt_pwm_configuration *configuration)
{
    uint32_t period_hz = pwm_hw->slice[slice_num].top;

    configuration->period = period_hz * 10;

    configuration->pulse = pwm_hw->slice[slice_num].cc * 10;

    return RT_EOK;
}

static rt_err_t _pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct pico_pwm *_pwm = rt_container_of(device, struct pico_pwm, pwm_device);
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;

    switch (cmd)
    {
    case PWM_CMD_ENABLE:
        pwm_set_enabled (_pwm->slice_num, RT_TRUE);
        return RT_EOK;
    case PWM_CMD_DISABLE:
        pwm_set_enabled (_pwm->slice_num, RT_FALSE);
        return RT_EOK;
    case PWM_CMD_SET:
        return _pwm_set(_pwm->slice_num, configuration);
    case PWM_CMD_GET:
        return _pwm_get(_pwm->slice_num, configuration);
    default:
        return -RT_EINVAL;
    }
}

static struct rt_pwm_ops _pwm_ops =
{
    _pwm_control
};

int rt_hw_pwm_init(void)
{
    int result = RT_EOK;

    for (int i = 0; i < sizeof(pico_pwm_obj) / sizeof(pico_pwm_obj[0]); i++)
    {
        if(pico_pwm_obj[i].a_all_flag)
        {
            gpio_set_function(pico_pwm_obj[i].slice_num * 2, GPIO_FUNC_PWM);
            gpio_set_function(pico_pwm_obj[i].slice_num * 2 + 16, GPIO_FUNC_PWM);
        }
        else
        {
            gpio_set_function(pico_pwm_obj[i].pin_a, GPIO_FUNC_PWM);
        }
        if(pico_pwm_obj[i].b_all_flag)
        {
            gpio_set_function(pico_pwm_obj[i].slice_num * 2 + 1, GPIO_FUNC_PWM);
            gpio_set_function(pico_pwm_obj[i].slice_num * 2 + 17, GPIO_FUNC_PWM);
        }
        else
        {
            gpio_set_function(pico_pwm_obj[i].pin_b, GPIO_FUNC_PWM);
        }
        result = rt_device_pwm_register(&pico_pwm_obj[i].pwm_device, pico_pwm_obj[i].name, &_pwm_ops, 0);
        if(result != RT_EOK)
        {
            LOG_E("%s register fail.", pico_pwm_obj[i].name);
        }
    }

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */

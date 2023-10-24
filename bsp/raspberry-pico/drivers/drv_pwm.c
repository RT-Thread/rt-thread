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

#ifdef BSP_USING_PWM

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.PWM"

struct pico_pwm
{
    struct rt_device_pwm pwm_device;
    rt_uint8_t slice_num;
    char *name;
};

static struct pico_pwm pico_pwm_obj[] =
{
#ifdef BSP_USING_PWM0
    {
        .name = "pwm0",
        .slice_num = 0,
    },
#endif
#ifdef BSP_USING_PWM1
    {
        .name = "pwm1",
        .slice_num = 1,
    },
#endif
#ifdef BSP_USING_PWM2
    {
        .name = "pwm2",
        .slice_num = 2,
    },
#endif
#ifdef BSP_USING_PWM3
    {
        .name = "pwm3",
        .slice_num = 3,
    },
#endif
#ifdef BSP_USING_PWM4
    {
        .name = "pwm4",
        .slice_num = 4,
    },
#endif
#ifdef BSP_USING_PWM5
    {
        .name = "pwm5",
        .slice_num = 5,
    },
#endif
#ifdef BSP_USING_PWM6
    {
        .name = "pwm6",
        .slice_num = 6,
    },
#endif
#ifdef BSP_USING_PWM7
    {
        .name = "pwm7",
        .slice_num = 7,
    },
#endif
};


static rt_err_t _pwm_set(rt_uint8_t slice_num, struct rt_pwm_configuration *configuration)
{
    uint32_t period_hz = 1000000000 / configuration->period;
    uint32_t pulse = 1000000000 / configuration->pulse;

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 1.25f);
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
        gpio_set_function(pico_pwm_obj[i].slice_num * 2, GPIO_FUNC_PWM);
        gpio_set_function(pico_pwm_obj[i].slice_num * 2 + 1, GPIO_FUNC_PWM);
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

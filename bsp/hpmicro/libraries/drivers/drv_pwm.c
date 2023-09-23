/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-05-09   HPMicro     First version
 * 2023-04-12   HPMicro     Adapt hpm_sdk v1.0.0
 * 2023-05-13   HPMicro     Fix compiling error on HPM6360/HPM6200
 */

#include <rtthread.h>

#ifdef BSP_USING_PWM
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"
#include "hpm_pwm_drv.h"
#include "hpm_clock_drv.h"

#ifdef HPM_PWM3
#define PWM_INSTANCE_NUM 4
#elif defined(HPM_PWM2)
#define PWM_INSTANCE_NUM 3
#elif defined(HPM_PWM1)
#define PWM_INSTANCE_NUM 2
#else
#define PWM_INSTANCE_NUM 1
#endif


static PWM_Type * pwm_base_tbl[PWM_INSTANCE_NUM] = {
    HPM_PWM0,
#ifdef HPM_PWM1
    HPM_PWM1,
#endif
#ifdef HPM_PWM2
    HPM_PWM2,
#endif
#ifdef HPM_PWM3
    HPM_PWM3
#endif
    };
static const clock_name_t pwm_clock_tbl[4] = {clock_mot0,
#if (PWM_INSTANCE_NUM > 1)
clock_mot1,
#endif
#if (PWM_INSTANCE_NUM > 2)
clock_mot2,
#endif
#if (PWM_INSTANCE_NUM > 3)
clock_mot3
#endif
};

rt_err_t hpm_generate_central_aligned_waveform(uint8_t pwm_index, uint8_t channel, uint32_t period, uint32_t pulse)
{
    uint32_t duty;
    pwm_cmp_config_t cmp_config[4] = {0};
    pwm_config_t pwm_config = {0};
    uint32_t reload = 0;
    uint32_t freq;
    PWM_Type * pwm_name_index;
    clock_name_t pwm_clock;
    pwm_clock = pwm_clock_tbl[pwm_index];
    pwm_name_index = pwm_base_tbl[pwm_index];

    freq = clock_get_frequency(pwm_clock);
    if(period != 0) {
        reload = (uint64_t)freq * period / 1000000000;
    } else {
        reload = 0;
    }

    pwm_stop_counter(pwm_name_index);
    pwm_get_default_pwm_config(pwm_name_index, &pwm_config);

    /*
     * reload and start counter
     */
    pwm_set_reload(pwm_name_index, 0, reload);
    pwm_set_start_count(pwm_name_index, 0, 0);

    /*
     * config cmp1 and cmp2 and cmp3
     */
    cmp_config[0].mode = pwm_cmp_mode_output_compare;
    cmp_config[0].cmp = reload + 1;
    cmp_config[0].update_trigger = pwm_shadow_register_update_on_hw_event;

    cmp_config[1].mode = pwm_cmp_mode_output_compare;
    cmp_config[1].cmp = reload + 1;
    cmp_config[1].update_trigger = pwm_shadow_register_update_on_hw_event;

    cmp_config[3].mode = pwm_cmp_mode_output_compare;
    cmp_config[3].cmp = reload;
    cmp_config[3].update_trigger = pwm_shadow_register_update_on_modify;

    pwm_config.enable_output = true;
    pwm_config.dead_zone_in_half_cycle = 0;
    pwm_config.invert_output = true;
    /*
     * config pwm
     */
    if (status_success != pwm_setup_waveform(pwm_name_index, channel, &pwm_config, channel * 2, cmp_config, 2)) {
        return RT_FALSE;
    }
    pwm_load_cmp_shadow_on_match(pwm_name_index, 17,  &cmp_config[3]);
    pwm_start_counter(pwm_name_index);
    pwm_issue_shadow_register_lock_event(pwm_name_index);
    duty = (uint64_t)freq * pulse / 1000000000;

    pwm_update_raw_cmp_central_aligned(pwm_name_index, channel * 2, channel * 2 + 1, (reload - duty) >> 1, (reload + duty) >> 1);

    return RT_TRUE;

}

rt_err_t hpm_set_central_aligned_waveform(uint8_t pwm_index, uint8_t channel, uint32_t period, uint32_t pulse)
{
    uint32_t duty;
    pwm_cmp_config_t cmp_config[4] = {0};
    pwm_config_t pwm_config = {0};
    uint32_t reload = 0;
    uint32_t freq;
    PWM_Type * pwm_name_index;
    clock_name_t pwm_clock;
    pwm_clock = pwm_clock_tbl[pwm_index];
    pwm_name_index = pwm_base_tbl[pwm_index];

    freq = clock_get_frequency(pwm_clock);
    if(period != 0) {
        reload = (uint64_t)freq * period / 1000000000;
    } else {
        reload = 0;
    }

    pwm_get_default_pwm_config(pwm_name_index, &pwm_config);
    pwm_set_reload(pwm_name_index, 0, reload);
    cmp_config[3].mode = pwm_cmp_mode_output_compare;
    cmp_config[3].cmp = reload;
    cmp_config[3].update_trigger = pwm_shadow_register_update_on_modify;
    pwm_config_cmp(pwm_name_index, 17, &cmp_config[3]);
    pwm_issue_shadow_register_lock_event(pwm_name_index);
    duty = (uint64_t)freq * pulse / 1000000000;
    pwm_update_raw_cmp_central_aligned(pwm_name_index, channel * 2, channel * 2 + 1, (reload - duty) >> 1, (reload + duty) >> 1);

    return RT_TRUE;
}

rt_err_t hpm_disable_pwm(uint8_t pwm_index, uint8_t channel)
{

    pwm_disable_output(pwm_base_tbl[pwm_index], channel);
    return RT_TRUE;

}

rt_err_t hpm_pwm_control(struct rt_device_pwm * device, int cmd, void *arg)
{
    uint8_t channel;
    uint32_t period;
    uint32_t pulse;
    rt_err_t sta = RT_TRUE;
    unsigned char pwm_name;
    struct rt_pwm_configuration * configuration;
    configuration = (struct rt_pwm_configuration * )arg;
    channel = configuration->channel;
    period  = configuration->period;
    pulse   = configuration->pulse;
    if (strcmp("pwm0", device->parent.parent.name) == 0) {
        pwm_name = 0;
    } else if (strcmp("pwm1", device->parent.parent.name) == 0) {
        pwm_name = 1;
    } else if (strcmp("pwm2", device->parent.parent.name) == 0) {
        pwm_name = 2;
    } else if (strcmp("pwm3", device->parent.parent.name) == 0) {
        pwm_name = 3;
    } else {
        return RT_FALSE;
    }

    switch(cmd) {
        case PWM_CMD_ENABLE: {
            sta = hpm_generate_central_aligned_waveform(pwm_name, channel, period, pulse);
            break;
        }
        case PWM_CMD_DISABLE: {
            hpm_disable_pwm(pwm_name, channel);
            break;
        }
        case PWM_CMD_SET: {
            sta = hpm_set_central_aligned_waveform(pwm_name, channel, period, pulse);
            break;
        }
        case PWM_CMD_GET: {
            sta = RT_TRUE;
            break;
        }
        default: {
            sta = RT_FALSE;
            break;
        }
    }
    return sta;
}

rt_err_t hpm_pwm_dev_control(rt_device_t device, int cmd, void *arg)
{
    uint8_t channel;
    uint32_t period;
    uint32_t pulse;
    rt_err_t sta = RT_TRUE;
    uint8_t pwm_name;
    struct rt_pwm_configuration * configuration;
    configuration = (struct rt_pwm_configuration * )arg;
    channel = configuration->channel;
    period  = configuration->period;
    pulse   = configuration->pulse;
    if (strcmp("pwm0", device->parent.name) == 0) {
        pwm_name = 0;
    } else if (strcmp("pwm1", device->parent.name) == 0) {
        pwm_name = 1;
    } else if (strcmp("pwm2", device->parent.name) == 0) {
        pwm_name = 2;
    } else if (strcmp("pwm3", device->parent.name) == 0) {
        pwm_name = 3;
    } else {
        return RT_FALSE;
    }

    switch(cmd) {
        case PWM_CMD_ENABLE: {
            sta = hpm_generate_central_aligned_waveform(pwm_name, channel, period, pulse);
            break;
        }
        case PWM_CMD_DISABLE: {
            hpm_disable_pwm(pwm_name, channel);
            break;
        }
        case PWM_CMD_SET: {
            sta = hpm_set_central_aligned_waveform(pwm_name, channel, period, pulse);
            break;
        }
        case PWM_CMD_GET: {
            sta = RT_TRUE;
            break;
        }
        default: {
            sta = RT_FALSE;
            break;
        }
    }
    return sta;
}

const static struct rt_pwm_ops hpm_pwm_ops = {
        .control = &hpm_pwm_control
};

static struct rt_device hpm_pwm_parent = {
        .control = hpm_pwm_dev_control
};

#ifdef HPM_PWM0
static struct rt_device_pwm hpm_dev_pwm0 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM1
static struct rt_device_pwm hpm_dev_pwm1 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM2
static struct rt_device_pwm hpm_dev_pwm2 = {
        .ops = &hpm_pwm_ops,
};
#endif

#ifdef HPM_PWM3
static struct rt_device_pwm hpm_dev_pwm3 = {
        .ops = &hpm_pwm_ops,
};
#endif


int rt_hw_pwm_init(void)
{
    int ret = RT_EOK;

#ifdef HPM_PWM0
    hpm_dev_pwm0.parent = hpm_pwm_parent;
    ret = rt_device_pwm_register(&hpm_dev_pwm0, "pwm0", &hpm_pwm_ops, RT_NULL);
#endif

#ifdef HPM_PWM1
    hpm_dev_pwm1.parent = hpm_pwm_parent;
    ret = rt_device_pwm_register(&hpm_dev_pwm1, "pwm1", &hpm_pwm_ops, RT_NULL);
#endif
#ifdef HPM_PWM2
    hpm_dev_pwm2.parent = hpm_pwm_parent;
    ret = rt_device_pwm_register(&hpm_dev_pwm2, "pwm2", &hpm_pwm_ops, RT_NULL);
#endif
#ifdef HPM_PWM3
    hpm_dev_pwm3.parent = hpm_pwm_parent;
    ret = rt_device_pwm_register(&hpm_dev_pwm3, "pwm3", &hpm_pwm_ops, RT_NULL);
#endif

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_pwm_init);

#endif /* BSP_USING_PWM */

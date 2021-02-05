/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-01-28     greedyhao         first version
 */

#include <board.h>

#ifdef RT_USING_PWM
#include "pwm_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwm"
#include <drv_log.h>

#define MAX_PERIOD 65535
#define MIN_PERIOD 3
#define MIN_PULSE 2

void hal_pwm_mspinit(void);

enum
{
#ifdef BSP_USING_T3_PWM
    T3_PWM_INDEX,
#endif
#ifdef BSP_USING_T4_PWM
    T4_PWM_INDEX,
#endif
#ifdef BSP_USING_T5_PWM
    T5_PWM_INDEX,
#endif
#ifdef BSP_USING_LPWM0
    LPWM0_INDEX,
#endif
#ifdef BSP_USING_LPWM1
    LPWM1_INDEX,
#endif
#ifdef BSP_USING_LPWM2
    LPWM2_INDEX,
#endif
#ifdef BSP_USING_LPWM3
    LPWM3_INDEX,
#endif
};

struct ab32_pwm
{
    struct rt_device_pwm pwm_device;
    hal_sfr_t   pwm_handle;
    char *name;
    rt_uint8_t  channel;
    rt_uint32_t period;
    rt_uint32_t pulse;
};

static struct ab32_pwm ab32_pwm_obj[] =
{
#ifdef BSP_USING_T3_PWM
    T3_PWM_CONFIG,
#endif
#ifdef BSP_USING_T4_PWM
    T4_PWM_CONFIG,
#endif
#ifdef BSP_USING_T5_PWM
    T5_PWM_CONFIG,
#endif
#ifdef BSP_USING_LPWM0
    LPWM0_CONFIG,
#endif
#ifdef BSP_USING_LPWM1
    LPWM1_CONFIG,
#endif
#ifdef BSP_USING_LPWM2
    LPWM2_CONFIG,
#endif
#ifdef BSP_USING_LPWM3
    LPWM3_CONFIG,
#endif
};

static rt_err_t drv_pwm_enable(hal_sfr_t pwm, char *name, struct rt_pwm_configuration *configuration, rt_bool_t enable)
{
    rt_uint8_t channel = configuration->channel;
    rt_uint8_t pwm_num = 0;

    if (!configuration->complementary) {
        if (name[0] == 'l') {
            pwm[PWMxCON] &= ~BIT(5);
        }
    } else {
        if (name[0] == 'l') {
            pwm[PWMxCON] |= BIT(5);
        } else {
            LOG_W("Timer no support complementary PWM output!");
        }
    }

    if (!enable) {
        if (name[0] == 'l') {
            pwm_num = name[4] - '0';
            pwm[PWMxCON] &= ~(1 << (pwm_num));
        } else {
            if (channel & 0x1) { /* pwm0 */
                pwm[TMRxCON] &= ~(1 << (9 + 0));
            }
            if (channel & 0x2) { /* pwm1 */
                pwm[TMRxCON] &= ~(1 << (9 + 1));
            }
            if (channel & 0x4) { /* pwm2 */
                pwm[TMRxCON] &= ~(1 << (9 + 2));
            }
        }
    } else {
        if (name[0] == 'l') {
            pwm_num = name[4] - '0';
            pwm[PWMxCON] |= 1 << (pwm_num);
        } else {
            if (channel & 0x1) { /* pwm0 */
                pwm[TMRxCON] |= (1 << (9 + 0));
            }
            if (channel & 0x2) { /* pwm1 */
                pwm[TMRxCON] |= (1 << (9 + 1));
            }
            if (channel & 0x4) { /* pwm2 */
                pwm[TMRxCON] |= (1 << (9 + 2));
            }
        }
    }

    return RT_EOK;
}

static rt_err_t drv_pwm_control(struct rt_device_pwm *device, int cmd, void *arg)
{
    struct rt_pwm_configuration *configuration = (struct rt_pwm_configuration *)arg;
    struct ab32_pwm *pwm_obj = (struct ab32_pwm *)device->parent.user_data;
    hal_sfr_t pwm = pwm_obj->pwm_handle;
    char *name = pwm_obj->name;
    rt_uint8_t channel = configuration->channel;
    rt_uint32_t period, pulse;
    rt_uint64_t tim_clock, psc;

    if (name[0] == 'l') {
        tim_clock = 6500; /* lpwm clock is 6.5MHz */
    } else {
        tim_clock = get_sysclk_nhz() / 1000ul;
    }

    switch (cmd)
    {
    case PWMN_CMD_ENABLE:
        configuration->complementary = RT_TRUE;
    case PWM_CMD_ENABLE:
        return drv_pwm_enable(pwm, name, configuration, RT_TRUE);
    case PWMN_CMD_DISABLE:
        configuration->complementary = RT_FALSE;
    case PWM_CMD_DISABLE:
        return drv_pwm_enable(pwm, name, configuration, RT_FALSE);
    case PWM_CMD_SET:
        pwm_obj->pulse = configuration->pulse;
        pwm_obj->period = configuration->period;

        period = pwm_obj->period * tim_clock / 1000000ul;
        psc = period / MAX_PERIOD + 1;
        period = period / psc;

        if (period < MIN_PERIOD)
        {
            period = MIN_PERIOD;
        }

        pulse = pwm_obj->pulse * tim_clock / psc / 1000000ul;
        if (pulse < MIN_PULSE)
        {
            pulse = MIN_PULSE;
        }
        else if (pulse > period)
        {
            pulse = period;
        }

        if (name[0] == 'l') {
            pwm[PWMxPR] = period - 1;
            switch (name[4] - '0')
            {
            case 0: /* lpwm0 */
                pwm[PWMxxDUT] = pulse - 1;
                break;
            case 1: /* lpwm1 */
                pwm[PWMxxDUT] = (pulse - 1) << 16;
                break;
            case 2: /* lpwm2 */
                pwm[PWMyyDUT] = pulse - 1;
                break;
            case 3: /* lpwm3 */
                pwm[PWMyyDUT] = (pulse - 1) << 16;
                break;
            default:
                break;
            }
        } else {
            pwm[TMRxPR] = period - 1;
            if (channel & 0x1) { /* pwm0 */
                pwm[TMRxDUTY0] = pulse - 1;
            }
            if (channel & 0x2) { /* pwm1 */
                pwm[TMRxDUTY1] = pulse - 1;
            }
            if (channel & 0x4) { /* pwm2 */
                pwm[TMRxDUTY2] = pulse - 1;
            }
        }
        return RT_EOK;
    case PWM_CMD_GET:
        configuration->pulse = pwm_obj->pulse;
        configuration->period = pwm_obj->period;
        return RT_EOK;
    default:
        return -RT_EINVAL;
    }
}

static rt_err_t ab32_hw_pwm_init(struct ab32_pwm *device)
{
    rt_err_t result = RT_EOK;
    hal_sfr_t pwm = RT_NULL;
    char *name = RT_NULL;

    RT_ASSERT(device != RT_NULL);

    pwm = (hal_sfr_t)device->pwm_handle;
    name = device->name;

    if (name[0] == 'l') {
        pwm[PWMxCON] = 0;
    } else {
        pwm[TMRxCON] &= ~(7 << 9);
    }

    return result;
}

static void pwm_get_channel(void)
{
#ifdef BSP_USING_T3_PWM0
    ab32_pwm_obj[T3_PWM_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_T3_PWM1
    ab32_pwm_obj[T3_PWM_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_T3_PWM2
    ab32_pwm_obj[T3_PWM_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_T4_PWM0
    ab32_pwm_obj[T4_PWM_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_T4_PWM1
    ab32_pwm_obj[T4_PWM_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_T4_PWM2
    ab32_pwm_obj[T4_PWM_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_T5_PWM0
    ab32_pwm_obj[T5_PWM_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_T5_PWM1
    ab32_pwm_obj[T5_PWM_INDEX].channel |= 1 << 1;
#endif
#ifdef BSP_USING_T5_PWM2
    ab32_pwm_obj[T5_PWM_INDEX].channel |= 1 << 2;
#endif
#ifdef BSP_USING_LPWM0
    ab32_pwm_obj[LPWM0_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_LPWM1
    ab32_pwm_obj[LPWM1_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_LPWM2
    ab32_pwm_obj[LPWM2_INDEX].channel |= 1 << 0;
#endif
#ifdef BSP_USING_LPWM3
    ab32_pwm_obj[LPWM3_INDEX].channel |= 1 << 0;
#endif
}

static struct rt_pwm_ops drv_ops =
{
    drv_pwm_control
};

static int ab32_pwm_init(void)
{
    int i = 0;
    int result = RT_EOK;

    pwm_get_channel();
    hal_pwm_mspinit();

    for (i = 0; i < sizeof(ab32_pwm_obj) / sizeof(ab32_pwm_obj[0]); i++)
    {
        /* pwm init */
        if (ab32_hw_pwm_init(&ab32_pwm_obj[i]) != RT_EOK)
        {
            LOG_E("%s init failed", ab32_pwm_obj[i].name);
            result = -RT_ERROR;
            goto __exit;
        }
        else
        {
            LOG_D("%s init success", ab32_pwm_obj[i].name);

            /* register pwm device */
            if (rt_device_pwm_register(&ab32_pwm_obj[i].pwm_device, ab32_pwm_obj[i].name, &drv_ops, (void *)&ab32_pwm_obj[i]) == RT_EOK)
            {
                LOG_D("%s register success", ab32_pwm_obj[i].name);
            }
            else
            {
                LOG_E("%s register failed", ab32_pwm_obj[i].name);
                result = -RT_ERROR;
            }
        }
    }

__exit:
    return result;
}
INIT_DEVICE_EXPORT(ab32_pwm_init);
#endif /* RT_USING_PWM */

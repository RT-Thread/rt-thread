/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Dual-channel PWM output test for the GD32H77D GinoPi board.
 */

#include <rtdevice.h>
#include <rtthread.h>

#ifdef BSP_USING_PWM_DUAL_TEST

#define PWM2_DEVICE_NAME          "pwm2"
#define PWM2_DEVICE_CHANNEL       2
#define PWM30_DEVICE_NAME         "pwm30"
#define PWM30_DEVICE_CHANNEL      3
#define PWM_TEST_PERIOD_NS        500000U
#define PWM_TEST_STEP_NS          5000U
#define PWM_TEST_DELAY_MS         50U
#define PWM_TEST_THREAD_STACK     1024U
#define PWM_TEST_THREAD_PRIORITY  20U
#define PWM_TEST_THREAD_TICK      10U

static struct rt_device_pwm *pwm2_device;
static struct rt_device_pwm *pwm30_device;
static rt_thread_t pwm_test_thread;
static volatile rt_bool_t pwm_test_stop;

static void pwm_dual_disable(void)
{
    if (pwm2_device != RT_NULL)
    {
        rt_pwm_disable(pwm2_device, PWM2_DEVICE_CHANNEL);
    }
    if (pwm30_device != RT_NULL)
    {
        rt_pwm_disable(pwm30_device, PWM30_DEVICE_CHANNEL);
    }
}

static void pwm_dual_test_entry(void *parameter)
{
    rt_uint32_t pulse = 0U;
    rt_bool_t increasing = RT_TRUE;

    (void)parameter;

    while (pwm_test_stop == RT_FALSE)
    {
        if (rt_pwm_set(pwm2_device, PWM2_DEVICE_CHANNEL,
                       PWM_TEST_PERIOD_NS, pulse) != RT_EOK ||
            rt_pwm_set(pwm30_device, PWM30_DEVICE_CHANNEL,
                       PWM_TEST_PERIOD_NS, pulse) != RT_EOK)
        {
            rt_kprintf("set dual PWM pulse failed\n");
            break;
        }

        rt_thread_mdelay(PWM_TEST_DELAY_MS);

        if (increasing == RT_TRUE)
        {
            pulse += PWM_TEST_STEP_NS;
            if (pulse >= PWM_TEST_PERIOD_NS)
            {
                pulse = PWM_TEST_PERIOD_NS;
                increasing = RT_FALSE;
            }
        }
        else if (pulse > PWM_TEST_STEP_NS)
        {
            pulse -= PWM_TEST_STEP_NS;
        }
        else
        {
            pulse = 0U;
            increasing = RT_TRUE;
        }
    }

    pwm_dual_disable();
    pwm_test_thread = RT_NULL;
    rt_kprintf("dual PWM test stopped\n");
}

static int pwm_dual_start(void)
{
    rt_err_t result;

    if (pwm_test_thread != RT_NULL)
    {
        rt_kprintf("dual PWM test is already running\n");
        return -RT_EBUSY;
    }

    pwm2_device = (struct rt_device_pwm *)rt_device_find(PWM2_DEVICE_NAME);
    pwm30_device = (struct rt_device_pwm *)rt_device_find(PWM30_DEVICE_NAME);
    if (pwm2_device == RT_NULL || pwm30_device == RT_NULL)
    {
        rt_kprintf("cannot find %s or %s device\n",
                   PWM2_DEVICE_NAME, PWM30_DEVICE_NAME);
        return -RT_ERROR;
    }

    result = rt_pwm_set(pwm2_device, PWM2_DEVICE_CHANNEL,
                        PWM_TEST_PERIOD_NS, 0U);
    if (result == RT_EOK)
    {
        result = rt_pwm_set(pwm30_device, PWM30_DEVICE_CHANNEL,
                            PWM_TEST_PERIOD_NS, 0U);
    }
    if (result == RT_EOK)
    {
        result = rt_pwm_enable(pwm2_device, PWM2_DEVICE_CHANNEL);
    }
    if (result == RT_EOK)
    {
        result = rt_pwm_enable(pwm30_device, PWM30_DEVICE_CHANNEL);
    }
    if (result != RT_EOK)
    {
        pwm_dual_disable();
        rt_kprintf("enable dual PWM failed: %d\n", result);
        return result;
    }

    pwm_test_stop = RT_FALSE;
    pwm_test_thread = rt_thread_create("pwmdual", pwm_dual_test_entry, RT_NULL,
                                       PWM_TEST_THREAD_STACK,
                                       PWM_TEST_THREAD_PRIORITY,
                                       PWM_TEST_THREAD_TICK);
    if (pwm_test_thread == RT_NULL)
    {
        pwm_dual_disable();
        rt_kprintf("create dual PWM test thread failed\n");
        return -RT_ENOMEM;
    }

    result = rt_thread_startup(pwm_test_thread);
    if (result != RT_EOK)
    {
        pwm_dual_disable();
        rt_thread_delete(pwm_test_thread);
        pwm_test_thread = RT_NULL;
        rt_kprintf("start dual PWM test thread failed: %d\n", result);
        return result;
    }

    rt_kprintf("dual PWM test started: pwm2 ch2 and pwm30 ch3\n");
    return RT_EOK;
}

static int pwm_dual_test(int argc, char *argv[])
{
    if (argc == 1 || (argc == 2 && rt_strcmp(argv[1], "start") == 0))
    {
        return pwm_dual_start();
    }

    if (argc == 2 && rt_strcmp(argv[1], "stop") == 0)
    {
        if (pwm_test_thread == RT_NULL)
        {
            rt_kprintf("dual PWM test is not running\n");
            return RT_EOK;
        }

        pwm_test_stop = RT_TRUE;
        return RT_EOK;
    }

    rt_kprintf("usage: pwm_dual_test [start|stop]\n");
    return -RT_EINVAL;
}

MSH_CMD_EXPORT(pwm_dual_test, test pwm2 channel 2 and pwm30 channel 3);
#endif /* BSP_USING_PWM_DUAL_TEST */

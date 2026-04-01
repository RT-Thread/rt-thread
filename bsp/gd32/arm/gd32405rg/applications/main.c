/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-08     ShiHongChao  first implementation
 */

#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED2 pin: PB5 */
#define LED2_PIN GET_PIN(B, 5)

int main(void)
{
    int count = 1;

    /* set LED2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}

#ifdef BSP_USING_HWTIMER
/* hwtimer callback function */
static rt_err_t hwtimer_test_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

#define HWTIMER_DEV_NAME "timer13"

/* hwtimer test */
static void hwtimer_test(void)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;      /* 定时器超时值 */
    rt_device_t hw_dev = RT_NULL;   /* 定时器设备句柄 */
    rt_hwtimer_mode_t mode;         /* 定时器模式 */
    rt_uint32_t freq = 10000;               /* 计数频率 */

    /* 查找定时器设备 */
    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return;
    }

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, hwtimer_test_cb);

    /* 设置计数频率(若未设置该项，默认为1Mhz 或 支持的最小计数频率) */
    rt_device_control(hw_dev, HWTIMER_CTRL_FREQ_SET, &freq);
    /* 设置模式为周期性定时器（若未设置，默认是HWTIMER_MODE_ONESHOT）*/
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return;
    }

    /* 设置定时器超时值为5s并启动定时器 */
    timeout_s.sec = 5;      /* 秒 */
    timeout_s.usec = 0;     /* 微秒 */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return;
    }
}
MSH_CMD_EXPORT(hwtimer_test, hwtimer test);
#endif //BSP_USING_HWTIMER

#ifdef BSP_USING_PWM

/* pwm test */
static void pwm_test(void)
{
    rt_err_t ret = RT_EOK;
    struct rt_device_pwm *pwm2 = RT_NULL, *pwm8 = RT_NULL, *pwm1 = RT_NULL, *pwm4 = RT_NULL;
    rt_uint32_t period = 1000;      /* 周期 */
    rt_uint32_t pulse = 500;        /* 占空比 */

    /* 查找PWM设备 */
    pwm2 = (struct rt_device_pwm *)rt_device_find("pwm2");
    if (pwm2 == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", "pwm2");
        return;
    }
    rt_pwm_set(pwm2, 3, period, pulse);
    rt_pwm_enable(pwm2, 3);
    rt_pwm_set(pwm2, 4, period, pulse);
    rt_pwm_enable(pwm2, 4);

    pwm8 = (struct rt_device_pwm *)rt_device_find("pwm8");
    rt_pwm_set(pwm8, 2, period, pulse);
    rt_pwm_enable(pwm8, 2);

    pwm1 = (struct rt_device_pwm *)rt_device_find("pwm1");
    rt_pwm_set(pwm1, 3, period, pulse);
    rt_pwm_enable(pwm1, 3);

    pwm4 = (struct rt_device_pwm *)rt_device_find("pwm4");
    rt_pwm_set(pwm4, 1, period, pulse);
    rt_pwm_enable(pwm4, 1);
    rt_pwm_set(pwm4, 2, period, pulse);
    rt_pwm_enable(pwm4, 2);
}
MSH_CMD_EXPORT(pwm_test, pwm test);
#endif // BSP_USING_PWM

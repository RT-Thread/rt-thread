/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是 PWM 设备使用例程
 * 例程导出了 pwm_sample 命令到控制终端。
 * 命令调用格式：pwm_sample x
 * 命令解释：x 对应的是设备名称，可以通过 list device 获取，例如：pwm_sample pwm_a1
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#ifdef BSP_USING_PWM

#define PWM_DEV_CHANNEL                 1

struct rt_device_pwm *pwm_dev;


static rt_int32_t pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period = 50000;
    rt_uint32_t pulse = 45000;

    if (argc != 2)
    {
        return -RT_ERROR;
    }

    pwm_dev = (struct rt_device_pwm *)rt_device_find(argv[1]);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", argv[1]);
        return -RT_ERROR;
    }

    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL + 1, period, pulse);
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL + 1);
//    rt_pwm_set_period(pwm_dev,PWM_DEV_CHANNEL,100000);

    while (1)
    {
        rt_thread_mdelay(50);
        pulse += 5000;
        rt_pwm_set_pulse(pwm_dev, PWM_DEV_CHANNEL, pulse);
        rt_pwm_set_pulse(pwm_dev, PWM_DEV_CHANNEL + 1, pulse);
        if (pulse >= period)
        {
            pulse = 0;
        }
    }
}
MSH_CMD_EXPORT(pwm_sample, pwm_sample [opt])
#endif
/*
 EOF
*/

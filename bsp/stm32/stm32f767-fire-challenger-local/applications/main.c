/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   change to new framework
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>
#include <stdio.h>
// #include <dfs_posix.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/stat.h>


// #include "drv_gpio.h"
// #include "drv_config.h"
// #include <rt_drv_pwm.h>
/* defined the LED0 pin: PH10 */
#define LED0_PIN    GET_PIN(H, 10)

int main(void)
{
    int count = 1;
    // struct rt_device_pwm *pwm_device_led = RT_NULL; //定义 pwm 设备指针
    // pwm_device_led = (struct rt_device_pwm *)rt_device_find("pwm5");
    // // rt_pwm_enable(pwm_device_led, 1);
    // // rt_pwm_set(pwm_device_led,1,100,50);
    // struct rt_pwm_configuration pwm_led_struct = {2,100,50};
    // pwm_device_led->ops->control(pwm_device_led,PWM_CMD_ENABLE,&pwm_led_struct);

    // rt_device_t dev;
    // struct rt_pwm_configuration configuration = {0};
    // dev = rt_device_find("pwm5");
    // rt_device_open(dev, RT_DEVICE_FLAG_RDWR);

    // configuration.period = 1000*1000; /* 1ms ==> 1Khz */
    // configuration.pulse = configuration.period / 2; /* 50% duty */
    // rt_device_write(dev, 2, &configuration, sizeof(struct rt_pwm_configuration));

    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (count++)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}

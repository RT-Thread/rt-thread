/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-19     Magicoe      The first version for LPC55S6x
 */

#include <rtthread.h>

#include "rtconfig.h"

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_inputmux.h"

#define LED_DEVICE_CTRL     0x81        /*LED control command*/

#define LED_NUM    2

struct led_ctrl
{
    uint8_t  port;
    uint32_t pin;
};

struct lpc_led
{
    /* inherit from rt_device */
    struct rt_device parent;

    struct led_ctrl ctrl[LED_NUM];
};

static struct lpc_led led;

static rt_err_t rt_led_init(rt_device_t dev)
{
    gpio_pin_config_t pin_config = {kGPIO_DigitalOutput, 1};

    GPIO_PinInit(GPIO, 1, 7, &pin_config);
    GPIO_PinInit(GPIO, 1, 6, &pin_config);

    led.ctrl[0].pin  = 7;
    led.ctrl[0].port = 1;
    led.ctrl[1].pin  = 6;
    led.ctrl[1].port = 1;

    return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_led_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
    rt_uint8_t *value = buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nr; index++)
    {
        if(GPIO_PinRead(GPIO, led.ctrl[pos + index].port, led.ctrl[pos + index].pin) == 0)
        {
            *value = 0;
        }
        else
        {
            *value = 1;
        }
        value++;
    }
    return index;
}

static rt_size_t rt_led_write(rt_device_t dev, rt_off_t pos,
                              const void *buffer, rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nw = size;
    const rt_uint8_t *value = buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nw; index++)
    {
        if (*value++)
        {
            GPIO_PinWrite(GPIO, led.ctrl[pos + index].port, led.ctrl[pos + index].pin, 0);
        }
        else
        {
            GPIO_PinWrite(GPIO, led.ctrl[pos + index].port, led.ctrl[pos + index].pin, 1);
        }
    }
    return index;
}

static rt_err_t rt_led_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev == &led.parent);

    if (cmd == LED_DEVICE_CTRL)
    {
        rt_uint32_t *led_num = args;
        *led_num = LED_NUM;
    }
    return RT_EOK;
}

int rt_hw_led_init(void)
{
    led.parent.type         = RT_Device_Class_Char;
    led.parent.rx_indicate  = RT_NULL;
    led.parent.tx_complete  = RT_NULL;
    led.parent.init         = rt_led_init;
    led.parent.open         = rt_led_open;
    led.parent.close        = rt_led_close;
    led.parent.read         = rt_led_read;
    led.parent.write        = rt_led_write;
    led.parent.control      = rt_led_control;
    led.parent.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&led.parent, "led", RT_DEVICE_FLAG_RDWR);
    /* init led device */
    rt_led_init(&led.parent);
    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_led_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
#include "msh.h"

void led_test(rt_uint32_t led_num, rt_uint32_t value)
{
    rt_uint8_t led_value = value;

    rt_led_write(&led.parent, led_num, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(0, 1).);

#endif

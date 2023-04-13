/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "board.h"

#define LED_DEVICE_CTRL     0x81        /*LED control command*/

#define LED_NUM    4
struct led_ctrl
{
    uint32_t num;
    LPC_GPIO_TypeDef *port;
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
    /* led0 : P4.27,led1:P4.15 ,led2:P4.16 ,led3:P4.17*/
    /* set P4.14,P4.15,P4.16,P4.17 as GPIO. */
    LPC_IOCON->P4_27 = 0x00;
    LPC_IOCON->P4_15 = 0x00;
    LPC_IOCON->P4_16 = 0x00;
    LPC_IOCON->P4_17 = 0x00;
    /* set P4.27,P4.15,P4.16,P4.17  output. */
    LPC_GPIO4->DIR |= (0x07 << 15) | (0x01 << 27);
    /* turn off all the led */
    LPC_GPIO4->SET = (0x07 << 15) | (0x01 << 27);
    led.ctrl[3].num = 27;
    led.ctrl[3].port = LPC_GPIO4;
    led.ctrl[2].num = 15;
    led.ctrl[2].port = LPC_GPIO4;
    led.ctrl[1].num = 16;
    led.ctrl[1].port = LPC_GPIO4;
    led.ctrl[0].num = 17;
    led.ctrl[0].port = LPC_GPIO4;
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

static rt_ssize_t rt_led_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
    rt_uint8_t *value = buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nr; index++)
    {
        if ((led.ctrl[pos + index].port->PIN) & 1 << led.ctrl[pos + index].num)
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

static rt_ssize_t rt_led_write(rt_device_t dev, rt_off_t pos,
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
            led.ctrl[pos + index].port->CLR |= (1 << led.ctrl[pos + index].num);
        }
        else
        {
            led.ctrl[pos + index].port->SET |= (1 << led.ctrl[pos + index].num);
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
void led_test(rt_uint32_t led_num, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&led.parent, led_num, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(0, 100).)
#endif

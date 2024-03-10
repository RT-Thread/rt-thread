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

#define LED_NUM 3

struct led_ctrl
{
    uint32_t num;
    uint32_t port;
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
    /*led2 Blue:P0.31 ,led1 Green:P0.30 ,led0 Red:P0_29  P38,P32*/
    LPC_SYSCON->AHBCLKCTRLSET[0] = (1UL << 14);       /* enable GPIO0 clock*/

    LPC_SYSCON->PRESETCTRLSET[0] = (1UL << 14);             /* Resets a GPIO0 peripheral */
    LPC_SYSCON->PRESETCTRLCLR[0] = (1UL << 14);

    /* set P0.31, P0.30, P0.29  output. */
    LPC_GPIO->DIR[0] |= 0x07UL << 29;

    /* turn off all the led */
    LPC_GPIO->SET[0] = 0x07UL << 29;

    led.ctrl[0].num = 29;
    led.ctrl[0].port = 0;
    led.ctrl[1].num = 30;
    led.ctrl[1].port = 0;
    led.ctrl[2].num = 31;
    led.ctrl[2].port = 0;

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
        if ((LPC_GPIO->B[0][led.ctrl[pos + index].num]))
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
        if (*value > 0)
        {
             //LPC_GPIO->CLR[led.ctrl[pos + index].port] |= (1 << led.ctrl[pos + index].num);
             LPC_GPIO->CLR[0] |= (1 << led.ctrl[pos + index].num);
        }
        else
        {
            //LPC_GPIO->SET[led.ctrl[pos + index].port] |= (1 << led.ctrl[pos + index].num);
            LPC_GPIO->SET[0] |= (1 << led.ctrl[pos + index].num);
        }
    }

        return index;
}

static rt_err_t rt_led_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

int rt_led_hw_init(void)
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

void Led_Control(rt_uint32_t Set_led, rt_uint32_t value)
{
    if ( Set_led == 0 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            /* Light off */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 1UL;
            break;
        case 1:
            /* Lights on */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 0UL;
            break;
        default:
            break;
        }
    }

    if ( Set_led == 1 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            /* Light off */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 1UL;
            break;
        case 1:
            /* Lights on */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 0UL;
            break;
        default:
            break;
        }
    }
        if ( Set_led == 2 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            /* Lights off */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 1UL;
            break;
        case 1:
            /* Lights on */
            LPC_GPIO->B[0][led.ctrl[Set_led].num] = 0UL;
            break;
        default:
            break;
        }
    }
}
INIT_DEVICE_EXPORT(rt_led_hw_init);

#ifdef RT_USING_FINSH
#include <finsh.h>
void led_test(rt_uint32_t led_num, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&led.parent, led_num, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(0, 100).)
#endif

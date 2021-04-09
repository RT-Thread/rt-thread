/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-01-13     weety     first version
 */

#include <rtthread.h>
#include "gpio.h"

#define GPIO0_BASE          (DAVINCI_GPIO_BASE + 0x10)
#define GPIO1_BASE          (DAVINCI_GPIO_BASE + 0x38)
#define GPIO2_BASE          (DAVINCI_GPIO_BASE + 0x60)
#define GPIO3_BASE          (DAVINCI_GPIO_BASE + 0x88)


static unsigned int dm365_gpio_base = (unsigned int)GPIO0_BASE;

#define GPIO_OE         (dm365_gpio_base + 0x00)
#define GPIO_DATAIN     (dm365_gpio_base + 0x10)
#define GPIO_DATAOUT        (dm365_gpio_base + 0x04)
#define GPIO_CLROUT     (dm365_gpio_base + 0x0C)
#define GPIO_SETOUT     (dm365_gpio_base + 0x08)

#define gpio_dirin(n)       *(volatile unsigned int *)((GPIO_OE)) |= 1<<(n)
#define gpio_dirout(n)  *(volatile unsigned int *)((GPIO_OE)) &= ~(1u<<(n))
#define gpio_set(n)     *(volatile unsigned int *)((GPIO_SETOUT)) = 1<<(n)
#define gpio_clr(n)     *(volatile unsigned int *)((GPIO_CLROUT)) = 1<<(n)
#define gpio_get(n)     ( ( *(volatile unsigned int *)((GPIO_DATAIN)) & (1<<(n)) ) ? 1 : 0 )

 #define GPIO_GRP_MASK (5)

static int gpio_to_base(unsigned int gpio)
{
    unsigned int grp_idx;
    int ret;

    grp_idx = gpio >> GPIO_GRP_MASK;

    switch (grp_idx) {
        case 0:
            dm365_gpio_base = (unsigned int)GPIO0_BASE;
            ret = 0;
            break;
        case 1:
            dm365_gpio_base = (unsigned int)GPIO1_BASE;
            ret = 0;
            break;
        case 2:
            dm365_gpio_base = (unsigned int)GPIO2_BASE;
            ret = 0;
            break;
        case 3:
            dm365_gpio_base = (unsigned int)GPIO3_BASE;
            ret = 0;
            break;
        default:
            ret =-RT_EIO;
            break;
    }
    return ret;
}


int gpio_direction_input(unsigned int gpio)
{
    unsigned int offset;
    int ret=0;

    rt_ubase_t temp = rt_hw_interrupt_disable();
    ret = gpio_to_base(gpio);
    if (ret < 0) {
        goto gpio_free;
    }
    offset =  gpio & ((1 << GPIO_GRP_MASK) -1);

    gpio_dirin(offset);

gpio_free:
    rt_hw_interrupt_enable(temp);

    return ret;
}

int gpio_direction_output(unsigned int gpio, int value)
{
    unsigned int offset;
    int ret=0;

    rt_ubase_t temp = rt_hw_interrupt_disable();
    ret = gpio_to_base(gpio);
    if (ret < 0) {
        goto gpio_free;
    }

    offset =  gpio & ((1 << GPIO_GRP_MASK) -1);

    if (value) {
        gpio_set(offset);
    }
    else {
        gpio_clr(offset);
    }

    gpio_dirout(offset);

gpio_free:
    rt_hw_interrupt_enable(temp);

    return ret;
}

int  gpio_set_value(unsigned int gpio, int value)
{
    unsigned int offset;
    int ret=0;

    rt_ubase_t temp = rt_hw_interrupt_disable();
    ret = gpio_to_base(gpio);
    if (ret < 0) {
        goto gpio_free;
    }

    offset =  gpio & ((1 << GPIO_GRP_MASK) -1);

    if (value) {
        gpio_set(offset);
    }
    else {
        gpio_clr(offset);
    }

gpio_free:
    rt_hw_interrupt_enable(temp);

    return ret;
}

int gpio_get_value(unsigned int gpio)
{
    unsigned int offset;
    int ret=0;

    rt_ubase_t temp = rt_hw_interrupt_disable();
    ret = gpio_to_base(gpio);
    if (ret < 0) {
        goto gpio_free;
    }

    offset =  gpio & ((1 << GPIO_GRP_MASK) -1);
    ret = gpio_get(offset);

gpio_free:
    rt_hw_interrupt_enable(temp);

    return ret;
}



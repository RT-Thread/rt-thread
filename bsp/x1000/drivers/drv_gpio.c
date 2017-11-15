/*
 * File      : drv_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-11-19     Urey         the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_gpio.h"

#define GPIO_DEBUG   0

#if GPIO_DEBUG
#define GPIO_DBG(...)     rt_kprintf(__VA_ARGS__)
#else
#define GPIO_DBG(...)
#endif

struct jz_gpio_irq_def  _g_gpio_irq_tbl[GPIO_NR_PORTS] = {0};

rt_inline int _fls(int x)
{
    __asm__("clz %0, %1" : "=r" (x) : "r" (x));

    return 32 - x;
}

void gpio_set_func(enum gpio_port port, uint32_t pins, enum gpio_function func)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    // Write to shadow register
    writel(func & 0x8 ? pins : 0, GPIO_PXINTS(GPIO_PORT_Z));
    writel(func & 0x4 ? pins : 0, GPIO_PXMSKS(GPIO_PORT_Z));
    writel(func & 0x2 ? pins : 0, GPIO_PXPAT1S(GPIO_PORT_Z));
    writel(func & 0x1 ? pins : 0, GPIO_PXPAT0S(GPIO_PORT_Z));

    writel(func & 0x8 ? 0 : pins, GPIO_PXINTC(GPIO_PORT_Z));
    writel(func & 0x4 ? 0 : pins, GPIO_PXMSKC(GPIO_PORT_Z));
    writel(func & 0x2 ? 0 : pins, GPIO_PXPAT1C(GPIO_PORT_Z));
    writel(func & 0x1 ? 0 : pins, GPIO_PXPAT0C(GPIO_PORT_Z));

    //Load shadown reigster
    writel(port,GPIO_PZGID2LD(GPIO_PORT_Z));

    writel(func & 0x10 ? pins : 0, GPIO_PXPENC(port));
    writel(func & 0x10 ? 0 : pins, GPIO_PXPENS(port));
}

void gpio_set_value(enum gpio_port port,enum gpio_pin pin,int value)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    if (value)
        writel(pin, GPIO_PXPAT0S(port));
    else
        writel(pin, GPIO_PXPAT0C(port));
}

void gpio_enable_pull(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXPENC(port));
}

void gpio_disable_pull(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXPENS(port));
}

void gpio_ctrl_pull(enum gpio_port port, uint32_t pins,int enable)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    if (enable)
        writel(pins, GPIO_PXPENC(port));
    else
        writel(pins, GPIO_PXPENS(port));
}

int gpio_get_value(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    return !!(readl(GPIO_PXPIN(port)) & pin);
}

int gpio_get_flag(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    return (readl(GPIO_PXFLG(port)) & pin);
}

void gpio_clear_flag(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXFLGC(port));
}

void gpio_direction_input(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    gpio_set_func(port,pin,GPIO_INPUT);
}

void gpio_direction_output(enum gpio_port port, enum gpio_pin pin,int value)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    gpio_set_func(port, pin, value ? GPIO_OUTPUT1 : GPIO_OUTPUT0);
}

/*********************************************************************************************************
**   IRQ
*********************************************************************************************************/
void gpio_unmask_irq(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXMSKC(port));
}

void gpio_mask_irq(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXMSKS(port));
}

int gpio_set_irq_type(enum gpio_port port,  enum gpio_pin pin, enum gpio_irq_type irq_type)
{
    enum gpio_function  func;

    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    if (irq_type & IRQ_TYPE_PROBE)
        return 0;
    switch (irq_type & IRQ_TYPE_SENSE_MASK)
    {
    case IRQ_TYPE_LEVEL_HIGH:
        func = GPIO_INT_HI;
        break;
    case IRQ_TYPE_LEVEL_LOW:
        func = GPIO_INT_LO;
        break;
    case IRQ_TYPE_EDGE_RISING:
        func = GPIO_INT_RE;
        break;
    case IRQ_TYPE_EDGE_FALLING:
        func = GPIO_INT_FE;
        break;
    case IRQ_TYPE_EDGE_BOTH:
        if (gpio_get_value(port, pin))
            func = GPIO_INT_FE;
        else
            func = GPIO_INT_RE;
        break;
    default:
        return -1;
    }

    gpio_set_func(port,pin, func);

    return 0;
}

void gpio_ack_irq(enum gpio_port port,  enum gpio_pin pin)
{
    RT_ASSERT(IS_GPIO_ALL_PORT(port));

    writel(pin, GPIO_PXFLGC(port));
}

void gpio_set_irq_callback(enum gpio_port port, enum gpio_pin pin, void (*irq_cb)(void *),void *irq_arg)
{
    uint32_t    pin_id;
    RT_ASSERT(IS_GPIO_ALL_PORT(port));
    pin_id = _fls(pin) - 1;

    GPIO_DBG("port = %d,pin = %d \n",port,pin_id);

    _g_gpio_irq_tbl[port].irq_cb[pin_id]    = irq_cb;
    _g_gpio_irq_tbl[port].irq_arg[pin_id]   = irq_arg;

    GPIO_DBG("set irq callback end... \n");
}

void gpio_irq_handler(int irq, void *param)
{
    struct jz_gpio_irq_def  *irq_def = (struct jz_gpio_irq_def  *)param;
    uint32_t    pend,mask;
    uint32_t    pin_id;
    enum gpio_port  port = (IRQ_GPIO0 - irq);
    enum gpio_pin   pin;

    RT_ASSERT(param != RT_NULL);
    GPIO_DBG("GPIO irq handler,irq=%d\n",irq);

    pend = readl(GPIO_PXFLG(port));
    mask = readl(GPIO_PXMSK(port));

    GPIO_DBG("port =%d pend =%08x mask =%08x\n",port,pend,mask);

    pend = pend & ~mask;
    while(pend)
    {
        pin_id = _fls(pend) - 1;
        pin    = 0x01 << pin_id;

        GPIO_DBG("PORT%d PIN%d interrupt happened..\n",port,pin_id);
        if(irq_def->irq_cb[pin_id] != RT_NULL)
        {
            GPIO_DBG("do irq callback...\n",port,pin);
            irq_def->irq_cb[pin_id](irq_def->irq_arg[pin_id]);
        }

        pend &= ~(0x01 << pin_id);
        gpio_ack_irq(port, pin);
    }
}

int rt_hw_gpio_init(void)
{
    GPIO_DBG("Install gpio interrupt source...\n");
    /* install ISR */
    rt_hw_interrupt_install(IRQ_GPIO0,gpio_irq_handler,&_g_gpio_irq_tbl[GPIO_PORT_A],"GPIOAINT");
    rt_hw_interrupt_umask(IRQ_GPIO0);

    rt_hw_interrupt_install(IRQ_GPIO1,gpio_irq_handler,&_g_gpio_irq_tbl[GPIO_PORT_B],"GPIOBINT");
    rt_hw_interrupt_umask(IRQ_GPIO1);

    rt_hw_interrupt_install(IRQ_GPIO2,gpio_irq_handler,&_g_gpio_irq_tbl[GPIO_PORT_C],"GPIOCINT");
    rt_hw_interrupt_umask(IRQ_GPIO2);

    rt_hw_interrupt_install(IRQ_GPIO3,gpio_irq_handler,&_g_gpio_irq_tbl[GPIO_PORT_D],"GPIODINT");
    rt_hw_interrupt_umask(IRQ_GPIO3);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_gpio_init);

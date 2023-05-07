/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-19     ZYH          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <fpioa.h>
#include <gpiohs.h>
#include "drv_gpio.h"
#include "drv_io_config.h"
#include <plic.h>
#include <rthw.h>
#include <utils.h>
#include <string.h>

#define DBG_ENABLE
#define DBG_TAG  "PIN"
#define DBG_LVL  DBG_WARNING
#define DBG_COLOR
#include <rtdbg.h>

#define FUNC_GPIOHS(n) (FUNC_GPIOHS0 + n)

static short pin_alloc_table[FPIOA_NUM_IO];
static uint32_t free_pin = 0;

static int alloc_pin_channel(rt_base_t pin_index)
{
    if(free_pin == 32)
    {
        LOG_E("no free gpiohs channel to alloc");
        return -1;
    }

    if(pin_alloc_table[pin_index] != -1)
    {
        LOG_W("already alloc gpiohs channel for pin %d", pin_index);
        return pin_alloc_table[pin_index];
    }

    pin_alloc_table[pin_index] = free_pin;
    free_pin++;

    fpioa_set_function(pin_index, FUNC_GPIOHS(pin_alloc_table[pin_index]));
    return pin_alloc_table[pin_index];
}

int get_pin_channel(rt_base_t pin_index)
{
    return pin_alloc_table[pin_index];
}

static void free_pin_channel(rt_base_t pin_index)
{
    if(pin_alloc_table[pin_index] == -1)
    {
        LOG_W("free error:not alloc gpiohs channel for pin %d", pin_index);
        return;
    }
    pin_alloc_table[pin_index] = -1;
    free_pin--;
}


static void drv_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    int pin_channel = get_pin_channel(pin);
    if(pin_channel == -1)
    {
        pin_channel = alloc_pin_channel(pin);
        if(pin_channel == -1)
        {
            return;
        }
    }

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            gpiohs_set_drive_mode(pin_channel, GPIO_DM_OUTPUT);
            break;
        case PIN_MODE_INPUT:
            gpiohs_set_drive_mode(pin_channel, GPIO_DM_INPUT);
            break;
        case PIN_MODE_INPUT_PULLUP:
            gpiohs_set_drive_mode(pin_channel, GPIO_DM_INPUT_PULL_UP);
            break;
        case PIN_MODE_INPUT_PULLDOWN:
            gpiohs_set_drive_mode(pin_channel, GPIO_DM_INPUT_PULL_DOWN);
            break;
        default:
            LOG_E("Not support mode %d", mode);
            break;
    }
}

static void drv_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    int pin_channel = get_pin_channel(pin);
    if(pin_channel == -1)
    {
        LOG_E("pin %d not set mode", pin);
        return;
    }
    gpiohs_set_pin(pin_channel, value == PIN_HIGH ? GPIO_PV_HIGH : GPIO_PV_LOW);
}

static rt_int8_t drv_pin_read(struct rt_device *device, rt_base_t pin)
{
    int pin_channel = get_pin_channel(pin);
    if(pin_channel == -1)
    {
        LOG_E("pin %d not set mode", pin);
        return -1;
    }
    return gpiohs_get_pin(pin_channel) == GPIO_PV_HIGH ? PIN_HIGH : PIN_LOW;
}

static struct
{
    void (*hdr)(void *args);
    void* args;
    gpio_pin_edge_t edge;
} irq_table[32];

static void pin_irq(int vector, void *param)
{
    int pin_channel = vector - IRQN_GPIOHS0_INTERRUPT;
    if(irq_table[pin_channel].edge & GPIO_PE_FALLING)
    {
        set_gpio_bit(gpiohs->fall_ie.u32, pin_channel, 0);
        set_gpio_bit(gpiohs->fall_ip.u32, pin_channel, 1);
        set_gpio_bit(gpiohs->fall_ie.u32, pin_channel, 1);
    }

    if(irq_table[pin_channel].edge & GPIO_PE_RISING)
    {
        set_gpio_bit(gpiohs->rise_ie.u32, pin_channel, 0);
        set_gpio_bit(gpiohs->rise_ip.u32, pin_channel, 1);
        set_gpio_bit(gpiohs->rise_ie.u32, pin_channel, 1);
    }

    if(irq_table[pin_channel].edge & GPIO_PE_LOW)
    {
        set_gpio_bit(gpiohs->low_ie.u32, pin_channel, 0);
        set_gpio_bit(gpiohs->low_ip.u32, pin_channel, 1);
        set_gpio_bit(gpiohs->low_ie.u32, pin_channel, 1);
    }

    if(irq_table[pin_channel].edge & GPIO_PE_HIGH)
    {
        set_gpio_bit(gpiohs->high_ie.u32, pin_channel, 0);
        set_gpio_bit(gpiohs->high_ip.u32, pin_channel, 1);
        set_gpio_bit(gpiohs->high_ie.u32, pin_channel, 1);
    }
    if(irq_table[pin_channel].hdr)
    {
        irq_table[pin_channel].hdr(irq_table[pin_channel].args);
    }
}

static rt_err_t drv_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    int pin_channel = get_pin_channel(pin);
    char irq_name[10];
    if(pin_channel == -1)
    {
        LOG_E("pin %d not set mode", pin);
        return -RT_ERROR;
    }
    irq_table[pin_channel].hdr = hdr;
    irq_table[pin_channel].args = args;
    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            irq_table[pin_channel].edge = GPIO_PE_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            irq_table[pin_channel].edge = GPIO_PE_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            irq_table[pin_channel].edge = GPIO_PE_BOTH;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            irq_table[pin_channel].edge = GPIO_PE_LOW;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            irq_table[pin_channel].edge = GPIO_PE_HIGH;
            break;
        default:
            break;
    }
    gpiohs_set_pin_edge(pin_channel, irq_table[pin_channel].edge);
    rt_snprintf(irq_name, sizeof irq_name, "pin%d", pin);
    rt_hw_interrupt_install(IRQN_GPIOHS0_INTERRUPT + pin_channel, pin_irq, RT_NULL, irq_name);

    return RT_EOK;
}

static rt_err_t drv_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_err_t ret = RT_EOK;

    int pin_channel = get_pin_channel(pin);
    if(pin_channel == -1)
    {
        LOG_E("pin %d not set mode", pin);
        return -RT_ERROR;
    }

    irq_table[pin_channel].hdr = RT_NULL;
    irq_table[pin_channel].args = RT_NULL;

    return ret;
}

static rt_err_t drv_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    int pin_channel = get_pin_channel(pin);

    if(pin_channel == -1)
    {
        LOG_E("pin %d not set mode", pin);
        return -RT_ERROR;
    }

    if(enabled)
    {
        rt_hw_interrupt_umask(IRQN_GPIOHS0_INTERRUPT + pin_channel);
    }
    else
    {
        rt_hw_interrupt_mask(IRQN_GPIOHS0_INTERRUPT + pin_channel);
    }

    return RT_EOK;
}

const static struct rt_pin_ops drv_pin_ops =
{
    drv_pin_mode,
    drv_pin_write,
    drv_pin_read,

    drv_pin_attach_irq,
    drv_pin_detach_irq,
    drv_pin_irq_enable
};

int rt_hw_pin_init(void)
{
    rt_err_t ret = RT_EOK;
    memset(pin_alloc_table, 0xff, sizeof pin_alloc_table);
    free_pin = GPIO_ALLOC_START;
    ret = rt_device_pin_register("pin", &drv_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);


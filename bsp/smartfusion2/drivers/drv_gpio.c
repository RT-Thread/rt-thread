/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-09     whik         first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>

#include "drv_gpio.h"

#ifdef BSP_USING_GPIO

static struct rt_pin_irq_hdr sf2_pin_irq_hdr_tab[] =
{
    /* pin, hdr, mode, args */
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

/* configure an individual GPIO port */
static void sf2_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    uint32_t config;
    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            config = MSS_GPIO_OUTPUT_MODE;
            break;
        case PIN_MODE_INPUT:
            config = MSS_GPIO_INPUT_MODE;
            break;
        default:
            config = MSS_GPIO_INOUT_MODE;
            break;
    }
    MSS_GPIO_config((mss_gpio_id_t )pin, config);
}

static rt_ssize_t sf2_pin_read(rt_device_t dev, rt_base_t pin)
{
    uint32_t value;
    value = MSS_GPIO_get_inputs() & (1<<pin);
    return ((value) ? PIN_HIGH : PIN_LOW);
}

static void sf2_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    if (value == PIN_HIGH)
        MSS_GPIO_set_output((mss_gpio_id_t )pin, 1);
    else
        MSS_GPIO_set_output((mss_gpio_id_t )pin, 0);
}

static rt_err_t sf2_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                        rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (sf2_pin_irq_hdr_tab[pin].pin == pin   &&
        sf2_pin_irq_hdr_tab[pin].hdr == hdr   &&
        sf2_pin_irq_hdr_tab[pin].mode == mode &&
        sf2_pin_irq_hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (sf2_pin_irq_hdr_tab[pin].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    sf2_pin_irq_hdr_tab[pin].pin = pin;
    sf2_pin_irq_hdr_tab[pin].hdr = hdr;
    sf2_pin_irq_hdr_tab[pin].mode = mode;
    sf2_pin_irq_hdr_tab[pin].args = args;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t sf2_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (sf2_pin_irq_hdr_tab[pin].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    sf2_pin_irq_hdr_tab[pin].pin = -1;
    sf2_pin_irq_hdr_tab[pin].hdr = RT_NULL;
    sf2_pin_irq_hdr_tab[pin].mode = 0;
    sf2_pin_irq_hdr_tab[pin].args = RT_NULL;

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t sf2_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    uint32_t mode = 0;
    rt_base_t level;

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        if (sf2_pin_irq_hdr_tab[pin].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }
        switch(sf2_pin_irq_hdr_tab[pin].mode)
        {
            case PIN_IRQ_MODE_RISING :
                mode = MSS_GPIO_IRQ_EDGE_POSITIVE;
                break;
            case PIN_IRQ_MODE_FALLING :
                mode = MSS_GPIO_IRQ_EDGE_NEGATIVE;
                break;
            case PIN_IRQ_MODE_RISING_FALLING:
                mode = MSS_GPIO_IRQ_EDGE_BOTH;
                break;
            case PIN_IRQ_MODE_HIGH_LEVEL :
                mode = MSS_GPIO_IRQ_LEVEL_HIGH;
                break;
            case PIN_IRQ_MODE_LOW_LEVEL:
                mode = MSS_GPIO_IRQ_LEVEL_LOW;
                break;
        }
        MSS_GPIO_config((mss_gpio_id_t )pin, MSS_GPIO_INPUT_MODE | mode);
        MSS_GPIO_enable_irq((mss_gpio_id_t )pin);

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        MSS_GPIO_config((mss_gpio_id_t )pin, MSS_GPIO_INPUT_MODE);
        MSS_GPIO_disable_irq((mss_gpio_id_t )pin);
    }
    else
        return -RT_ENOSYS;

    return RT_EOK;
}

static const struct rt_pin_ops sf2_pin_ops =
{
    sf2_pin_mode,
    sf2_pin_write,
    sf2_pin_read,
    sf2_pin_attach_irq,
    sf2_pin_detach_irq,
    sf2_pin_irq_enable
};


int rt_hw_pin_init(void)
{
    rt_err_t result = RT_EOK;
    MSS_GPIO_init();
    result = rt_device_pin_register("pin", &sf2_pin_ops, RT_NULL);
    RT_ASSERT(result == RT_EOK);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int pin)
{
    MSS_GPIO_clear_irq((mss_gpio_id_t )pin);

    if (sf2_pin_irq_hdr_tab[pin].hdr)
        sf2_pin_irq_hdr_tab[pin].hdr(sf2_pin_irq_hdr_tab[pin].args);
}

void GPIO0_IRQHandler( void )
{
    /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(0);
    /* leave interrupt */
    rt_interrupt_leave();
}

void GPIO1_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(1);
    rt_interrupt_leave();
}

void GPIO2_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(2);
    rt_interrupt_leave();
}

void GPIO3_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(3);
    rt_interrupt_leave();
}

void GPIO4_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(4);
    rt_interrupt_leave();
}

void GPIO5_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(5);
    rt_interrupt_leave();
}

void GPIO6_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(6);
    rt_interrupt_leave();
}
void GPIO7_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(7);
    rt_interrupt_leave();
}

void GPIO8_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(8);
    rt_interrupt_leave();
}

void GPIO9_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(9);
    rt_interrupt_leave();
}

void GPIO10_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(10);
    rt_interrupt_leave();
}

void GPIO11_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(11);
    rt_interrupt_leave();
}

void GPIO12_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(12);
    rt_interrupt_leave();
}

void GPIO13_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(13);
    rt_interrupt_leave();
}

void GPIO14_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(14);
    rt_interrupt_leave();
}

void GPIO15_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(15);
    rt_interrupt_leave();
}

void GPIO16_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(16);
    rt_interrupt_leave();
}

void GPIO17_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(17);
    rt_interrupt_leave();
}

void GPIO18_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(18);
    rt_interrupt_leave();
}

void GPIO19_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(19);
    rt_interrupt_leave();
}

void GPIO20_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(20);
    rt_interrupt_leave();
}

void GPIO21_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(21);
    rt_interrupt_leave();
}

void GPIO22_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(22);
    rt_interrupt_leave();
}

void GPIO23_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(23);
    rt_interrupt_leave();
}

void GPIO24_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(24);
    rt_interrupt_leave();
}

void GPIO25_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(25);
    rt_interrupt_leave();
}

void GPIO26_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(26);
    rt_interrupt_leave();
}

void GPIO27_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(27);
    rt_interrupt_leave();
}

void GPIO28_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(28);
    rt_interrupt_leave();
}

void GPIO29_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(29);
    rt_interrupt_leave();
}

void GPIO30_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(30);
    rt_interrupt_leave();
}

void GPIO31_IRQHandler( void )
{
    rt_interrupt_enter();
    pin_irq_hdr(31);
    rt_interrupt_leave();
}

#endif

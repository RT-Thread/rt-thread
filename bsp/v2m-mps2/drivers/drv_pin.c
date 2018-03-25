/*
 * File      : drv_pin.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-25     Tanek        the first version.
 */
#include <rtthread.h>
#include <rthw.h>
#include <drivers/pin.h>
#include <SMM_MPS2.h>

#ifdef RT_USING_PIN

// pin 0 ~ 7  : switch 0 ~ 7
// pin 8 ~ 15 : user led 0 ~ 7

static void v2m_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    return ;
}

static int v2m_pin_read(rt_device_t dev, rt_base_t pin)
{
    RT_ASSERT(dev != RT_NULL);

    if (0 <= pin && pin <= 7)
    {
        return !!(MPS2_SCC->CFG_REG3 & (0x01 << pin));   // switchs
    }
    else if (8 <= pin && pin <= 15)
    {
        return !!(MPS2_SCC->CFG_REG1 & (0x01 << (pin - 8)));   // leds
    }
    else
    {
        RT_ASSERT(RT_NULL);
        return 0;
    }
}

static void v2m_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    RT_ASSERT(dev != RT_NULL);

    if (8 <= pin && pin <= 15)
    {
        rt_uint32_t reg = MPS2_SCC->CFG_REG1;

        if (value)
            reg |= 1 << (pin - 8);
        else
            reg &= ~(1 << (pin - 8));

        MPS2_SCC->CFG_REG1 = reg;
    }
    else
    {
        RT_ASSERT(RT_NULL);
    }
}

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    static const struct rt_pin_ops v2m_pin_ops =
    {
        v2m_pin_mode,
        v2m_pin_write,
        v2m_pin_read,
        RT_NULL,
        RT_NULL,
        RT_NULL
    };

    ret = rt_device_pin_register("pin", &v2m_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /*RT_USING_PIN */

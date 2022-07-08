/*
 * Copyright (c) 2021-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-06-03     supperthomas first version
 *
 */

#include "drv_gpio.h"
#include <stdio.h>
#ifdef RT_USING_PIN

#define DBG_LEVEL   DBG_LOG
#define LOG_TAG                "drv.gpio"
#include <rtdbg.h>


static void mcu_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    gpio_set_level(pin, value);
    /*TODO:set gpio out put mode */
}

static int mcu_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    value = gpio_get_level(pin);
    return value;
}
static gpio_config_t init_io(gpio_num_t num)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << num);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    return io_conf;
}

static void mcu_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    if (mode == PIN_MODE_OUTPUT)
    {
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    }
    /*TODO:set gpio out put mode */
}


static rt_err_t mcu_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                   rt_uint32_t irq_mode, void (*hdr)(void *args), void *args)
{

    /*TODO: start irq handle */
    return RT_EOK;
}

static rt_err_t mcu_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    /*TODO:disable gpio irq handle */
    return RT_EOK;
}

static rt_err_t mcu_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint32_t enabled)
{
    /*TODO:start irq handle */
    return RT_EOK;
}

const static struct rt_pin_ops _mcu_pin_ops =
{
    mcu_pin_mode,
    mcu_pin_write,
    mcu_pin_read,
    mcu_pin_attach_irq,
    mcu_pin_dettach_irq,
    mcu_pin_irq_enable,
    ///NULL,
};

int rt_hw_pin_init(void)
{
    /*TODO: INIT THE GPIO CLOCK AND OTHER */
    return rt_device_pin_register("pin", &_mcu_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);


#endif /* RT_USING_PIN */

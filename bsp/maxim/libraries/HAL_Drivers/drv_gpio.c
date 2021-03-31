/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-11     supperthomas first version
 *
 */


#include "drv_gpio.h"
#include <stdbool.h>
#include "gpio.h"

#ifdef RT_USING_PIN

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG                "drv.gpio"

#define PIN_PORT_OFFSET 4

#define PIN_NUM(port, no) ((((((port) & 0xFu) << PIN_PORT_OFFSET) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> PIN_PORT_OFFSET) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))


#define PIN_MCU_PORT(pin)  PIN_PORT(pin)
#define PIN_MCU_PIN(pin) ((uint32_t)(1u << PIN_NO(pin)))

static void mcu_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    gpio_cfg_t tmp_gpio_cfg;
    tmp_gpio_cfg.port = PIN_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);
    if (value)
    {
        GPIO_OutSet(&tmp_gpio_cfg);
    }
    else
    {
        GPIO_OutClr(&tmp_gpio_cfg);
    }

}

static int mcu_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    gpio_cfg_t tmp_gpio_cfg;
    tmp_gpio_cfg.port = PIN_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);

    if (GPIO_InGet(&tmp_gpio_cfg))
    {
        value = 1;
    }
    else
    {
        value = 0;
    }

    return value;
}

static void mcu_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    gpio_cfg_t tmp_gpio_cfg;
    int ret = 0;
    tmp_gpio_cfg.port = PIN_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        tmp_gpio_cfg.func = GPIO_FUNC_OUT;
        tmp_gpio_cfg.pad = GPIO_PAD_NONE;
        break;
    case PIN_MODE_INPUT:
        tmp_gpio_cfg.func = GPIO_FUNC_IN;
        tmp_gpio_cfg.pad = GPIO_PAD_NONE;
        break;
    case PIN_MODE_INPUT_PULLUP:
        tmp_gpio_cfg.func = GPIO_FUNC_IN;
        tmp_gpio_cfg.pad = GPIO_PAD_PULL_UP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        tmp_gpio_cfg.func = GPIO_FUNC_IN;
        tmp_gpio_cfg.pad = GPIO_PAD_PULL_DOWN;
        break;
    case PIN_MODE_OUTPUT_OD:
        //not support
        LOG_E("NOT SUPPORT");
        break;
    }
    ret = GPIO_Config(&tmp_gpio_cfg);
    if (E_NO_ERROR != ret)
    {
        LOG_E("GPIO_Config error :%d", ret);
    }
}


static rt_err_t mcu_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                   rt_uint32_t irq_mode, void (*hdr)(void *args), void *args)
{
    gpio_cfg_t tmp_gpio_cfg;
    tmp_gpio_cfg.port = PIN_MCU_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);


    tmp_gpio_cfg.pad = GPIO_PAD_PULL_UP;
    tmp_gpio_cfg.func = GPIO_FUNC_IN;
    GPIO_Config(&tmp_gpio_cfg);
    GPIO_RegisterCallback(&tmp_gpio_cfg, hdr, args);

    gpio_int_mode_t mcu_mode;
    gpio_int_pol_t mcu_pol;

    switch (irq_mode)
    {
    case PIN_IRQ_MODE_RISING:
        mcu_mode = GPIO_INT_EDGE;
        mcu_pol = GPIO_INT_RISING;
        break;
    case PIN_IRQ_MODE_FALLING:
        mcu_mode = GPIO_INT_EDGE;
        mcu_pol = GPIO_INT_FALLING;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        mcu_mode = GPIO_INT_EDGE;
        mcu_pol = GPIO_INT_BOTH;
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        mcu_mode = GPIO_INT_LEVEL;
        mcu_pol = GPIO_INT_HIGH;
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        mcu_mode = GPIO_INT_LEVEL;
        mcu_pol = GPIO_INT_LOW;
        break;
    }

    GPIO_IntConfig(&tmp_gpio_cfg, mcu_mode, mcu_pol);


    return RT_EOK;
}

static rt_err_t mcu_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    gpio_cfg_t tmp_gpio_cfg;
    tmp_gpio_cfg.port = PIN_MCU_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);
    tmp_gpio_cfg.pad = GPIO_PAD_PULL_UP;
    tmp_gpio_cfg.func = GPIO_FUNC_IN;
    GPIO_Config(&tmp_gpio_cfg);
    GPIO_IntDisable(&tmp_gpio_cfg);
    GPIO_RegisterCallback(&tmp_gpio_cfg, NULL, NULL);
    return RT_EOK;
}

static rt_err_t mcu_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint32_t enabled)
{
    gpio_cfg_t tmp_gpio_cfg;
    tmp_gpio_cfg.port = PIN_MCU_PORT(pin);
    tmp_gpio_cfg.mask = PIN_MCU_PIN(pin);
    if (enabled)
    {
        GPIO_IntEnable(&tmp_gpio_cfg);
        NVIC_EnableIRQ((IRQn_Type)MXC_GPIO_GET_IRQ(PIN_MCU_PORT(pin)));
    }
    else
    {
        GPIO_IntDisable(&tmp_gpio_cfg);
        NVIC_DisableIRQ((IRQn_Type)MXC_GPIO_GET_IRQ(PIN_MCU_PORT(pin)));
    }
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
    NULL,
};

int rt_hw_pin_init(void)
{
    GPIO_Init();
    return rt_device_pin_register("pin", &_mcu_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);


void GPIO0_IRQHandler(void)
{
    GPIO_Handler(PORT_0);
}

#endif /* RT_USING_PIN */

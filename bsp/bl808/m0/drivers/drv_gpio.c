/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023/01/5      chushicheng  first version
 *
 */

#include "drv_gpio.h"
#include <stdbool.h>
#include "bl808_gpio.h"
#include "bl808_glb.h"
#include "bl808.h"

#ifdef RT_USING_PIN

#define DBG_LEVEL   DBG_LOG
// #include <rtdbg.h>
#define LOG_TAG                "drv.gpio"

static void GPIO0_IRQHandler(void);

struct gpio_int_cfg_private {
    slist_t list;
    uint32_t pin;
    void (*hdr)(uint32_t pin);
};

static slist_t gpio_int_head = SLIST_OBJECT_INIT(gpio_int_head);


static void bl808_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GLB_GPIO_Write(pin, value);
}

static int bl808_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    value = GLB_GPIO_Read(pin);;
    return value;
}

static void bl808_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
        GLB_GPIO_Cfg_Type gpio_cfg;

    gpio_cfg.gpioFun = GPIO_FUN_GPIO;
    gpio_cfg.gpioPin = pin;
    gpio_cfg.drive = 0;
    gpio_cfg.smtCtrl = 1;
    gpio_cfg.outputMode = 0;

    switch (mode) {
        case GPIO_OUTPUT_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_NONE;
            break;

        case GPIO_OUTPUT_PP_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_UP;
            break;

        case GPIO_OUTPUT_PD_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_OUTPUT;
            gpio_cfg.pullType = GPIO_PULL_DOWN;
            break;

        case GPIO_INPUT_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_NONE;
            break;

        case GPIO_INPUT_PP_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_UP;
            break;

        case GPIO_INPUT_PD_MODE:
            gpio_cfg.gpioMode = GPIO_MODE_INPUT;
            gpio_cfg.pullType = GPIO_PULL_DOWN;
            break;
        case GPIO_HZ_MODE:
            GLB_GPIO_Set_HZ(pin);
        default:
            CPU_Interrupt_Disable(GPIO_INT0_IRQn);
            GLB_GPIO_IntMask(pin, MASK);

            GLB_GPIO_INT_Cfg_Type intCfg;

            intCfg.gpioPin = pin;
            intCfg.intMask = MASK;

            gpio_cfg.gpioMode = GPIO_MODE_INPUT;

            if (mode == GPIO_ASYNC_RISING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_RISING_EDGE;
            } else if (mode == GPIO_ASYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_FALLING_EDGE;
            } else if (mode == GPIO_ASYNC_HIGH_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_HIGH_LEVEL;
            } else if (mode == GPIO_ASYNC_LOW_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_ASYNC_LOW_LEVEL;
            } else if (mode == GPIO_SYNC_RISING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_RISING_EDGE;
            } else if (mode == GPIO_SYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_FALLING_EDGE;
            } else if (mode == GPIO_SYNC_FALLING_TRIGER_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_NONE;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_FALLING_RISING_EDGE;
            } else if (mode == GPIO_SYNC_HIGH_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_DOWN;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_HIGH_LEVEL;
            } else if (mode == GPIO_SYNC_LOW_LEVEL_INT_MODE) {
                gpio_cfg.pullType = GPIO_PULL_UP;
                intCfg.trig = GLB_GPIO_INT_TRIG_SYNC_LOW_LEVEL;
            }

            GLB_GPIO_Int_Init(&intCfg);
            break;
    }

    GLB_GPIO_Init(&gpio_cfg);
}


static rt_err_t bl808_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                   rt_uint32_t irq_mode, void (*hdr)(void *args), void *args)
{
    struct gpio_int_cfg_private *int_cfg = malloc(sizeof(struct gpio_int_cfg_private));
    int_cfg->hdr = hdr;
    int_cfg->pin = pin;
    slist_add_tail(&gpio_int_head, &int_cfg->list);
    CPU_Interrupt_Disable(GPIO_INT0_IRQn);
    Interrupt_Handler_Register(GPIO_INT0_IRQn, GPIO0_IRQHandler);
    CPU_Interrupt_Enable(GPIO_INT0_IRQn);
    return RT_EOK;
}


static rt_err_t bl808_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint32_t enabled)
{
    if (enabled) {
        GLB_GPIO_IntMask(pin, UNMASK);
    } else {
        GLB_GPIO_IntMask(pin, MASK);
    }
    return RT_EOK;
}

const static struct rt_pin_ops _bl808_pin_ops =
{
    bl808_pin_mode,
    bl808_pin_write,
    bl808_pin_read,
    bl808_pin_attach_irq,
    bl808_pin_irq_enable,
    NULL,
};

int rt_hw_pin_init(void)
{

    return rt_device_pin_register("pin", &_bl808_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

//irq handle
void GPIO0_IRQHandler(void)
{
    rt_interrupt_enter();
    // GPIO_INT0_IRQHandler();
    rt_interrupt_leave();
}

#endif /* RT_USING_PIN */

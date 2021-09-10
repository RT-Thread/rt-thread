/*
 * Copyright (c) 2006-2021, YICHIP Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WSY          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>

typedef void (*pin_callback_t)(void *args);
struct pin
{
    uint32_t package_index;
    const char *name;
    IRQn_Type irq;
    rt_uint32_t irq_mode;
    pin_callback_t callback;
    void *callback_args;
};
typedef struct pin pin_t;

static void yc_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    /* Configure GPIO_InitStructure */
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_CONFIG(pin) = OUTPUT_LOW;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_CONFIG(pin) = INPUT;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_CONFIG(pin) = PULL_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_CONFIG(pin) = PULL_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_CONFIG(pin) = PULL_UP;
    }
}

static void yc_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if (value)
    {
        GPIO_CONFIG(pin) = OUTPUT_HIGH;
    }
    else
    {
        GPIO_CONFIG(pin) = OUTPUT_LOW;
    }
}

static int yc_pin_read(rt_device_t dev, rt_base_t pin)
{
    return GPIO_IN(pin / 16) & (1 << (pin % 16)) ? 1 : 0;
}

static rt_err_t yc_pin_attach_irq(struct rt_device *device,
                                  rt_int32_t pin,
                                  rt_uint32_t mode,
                                  pin_callback_t cb,
                                  void *args)
{
    pin_t *index;
    rt_base_t level;
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    level = rt_hw_interrupt_disable();
    index->callback = cb;
    index->callback_args = args;
    index->irq_mode = mode;

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t yc_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    pin_t *index;
    rt_base_t level;
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    level = rt_hw_interrupt_disable();
    index->callback = 0;
    index->callback_args = 0;
    index->irq_mode = 0;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t yc_pin_irq_enable(struct rt_device *device,
                                  rt_base_t pin,
                                  rt_uint32_t enabled)
{
    pin_t *index;
    rt_base_t level = 0;
    if (index == RT_NULL)
    {
        return RT_EINVAL;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (index->irq_mode)
        {
        case PIN_IRQ_MODE_RISING:

            break;
        case PIN_IRQ_MODE_FALLING:

            break;
        case PIN_IRQ_MODE_RISING_FALLING:

            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_CONFIG(pin) = PULL_DOWN;
            GPIO_TRIG_MODE(pin/16) &= (1 << (pin % 16));
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_CONFIG(pin) = PULL_UP;
            GPIO_TRIG_MODE(pin/16) |= (1 << (pin % 16));
            break;
        default:
            rt_hw_interrupt_enable(level);
            return RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        NVIC_EnableIRQ(index->irq);
        GPIO_INTR_EN(pin / 16) |= (1 << (pin % 16));
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        NVIC_DisableIRQ(index->irq);
        GPIO_INTR_EN(pin / 16) &= ~(1 << (pin % 16));
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops yc3121_pin_ops =
    {
        yc_pin_mode,
        yc_pin_write,
        yc_pin_read,
        yc_pin_attach_irq,
        yc_pin_detach_irq,
        yc_pin_irq_enable,
        RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;
    result = rt_device_pin_register("pin", &yc3121_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

void GPIOA_Handler(void)
{
    int i;

    /* enter interrupt */
    rt_interrupt_enter();

    for (i = 0; i < 48; i++)
    {
        // if(GPIO_IN(pin / 16) & (1 << (pin % 16)))

    }

    /* leave interrupt */
    rt_interrupt_leave();
}

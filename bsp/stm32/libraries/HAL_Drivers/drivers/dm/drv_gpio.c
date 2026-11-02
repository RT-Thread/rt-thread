/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-29     RTT          the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "drv.gpio.dm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/platform.h>
#include <drivers/ofw.h>
#include <drivers/ofw_irq.h>
#include <drivers/pic.h>

#include "dev_pin_dm.h"
#include "drv_exti.h"

#define STM32_GPIO_PIN_NR 16

struct stm32_gpio_irq
{
    int irq;
    rt_uint8_t mode;
    rt_bool_t acquired;
    rt_bool_t pic_attached;
    rt_bool_t enabled;
    void (*handler)(void *args);
    void *args;
};

struct stm32_gpio
{
    struct rt_device_pin parent;
    GPIO_TypeDef *gpio;
    struct stm32_exti *exti;
    rt_uint32_t pulls[STM32_GPIO_PIN_NR];
    struct stm32_gpio_irq irqs[STM32_GPIO_PIN_NR];
};

static struct stm32_gpio *device_to_stm32_gpio(struct rt_device *device)
{
    struct rt_device_pin *pin = rt_container_of(device, struct rt_device_pin, parent);

    return rt_container_of(pin, struct stm32_gpio, parent);
}

static rt_err_t stm32_gpio_resolve(rt_uint64_t address, GPIO_TypeDef **out_gpio)
{
#define STM32_GPIO_CASE(port)                \
    if (address == (rt_ubase_t)GPIO##port)   \
    {                                        \
        __HAL_RCC_GPIO##port##_CLK_ENABLE(); \
        *out_gpio = GPIO##port;              \
        return RT_EOK;                       \
    }

#if defined(GPIOA)
    STM32_GPIO_CASE(A);
#endif
#if defined(GPIOB)
    STM32_GPIO_CASE(B);
#endif
#if defined(GPIOC)
    STM32_GPIO_CASE(C);
#endif
#if defined(GPIOD)
    STM32_GPIO_CASE(D);
#endif
#if defined(GPIOE)
    STM32_GPIO_CASE(E);
#endif
#if defined(GPIOF)
    STM32_GPIO_CASE(F);
#endif
#if defined(GPIOG)
    STM32_GPIO_CASE(G);
#endif
#if defined(GPIOH)
    STM32_GPIO_CASE(H);
#endif
#if defined(GPIOI)
    STM32_GPIO_CASE(I);
#endif
#if defined(GPIOJ)
    STM32_GPIO_CASE(J);
#endif
#if defined(GPIOK)
    STM32_GPIO_CASE(K);
#endif

#undef STM32_GPIO_CASE

    return -RT_EINVAL;
}

static void stm32_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef gpio_init = { 0 };
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);

    if (pin < 0 || pin >= STM32_GPIO_PIN_NR)
    {
        return;
    }

    gpio_init.Pin = RT_BIT(pin);
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
        gpio_init.Pull = GPIO_NOPULL;
        break;

    case PIN_MODE_INPUT:
        gpio_init.Mode = GPIO_MODE_INPUT;
        gpio_init.Pull = GPIO_NOPULL;
        break;

    case PIN_MODE_INPUT_PULLUP:
        gpio_init.Mode = GPIO_MODE_INPUT;
        gpio_init.Pull = GPIO_PULLUP;
        break;

    case PIN_MODE_INPUT_PULLDOWN:
        gpio_init.Mode = GPIO_MODE_INPUT;
        gpio_init.Pull = GPIO_PULLDOWN;
        break;

    case PIN_MODE_OUTPUT_OD:
        gpio_init.Mode = GPIO_MODE_OUTPUT_OD;
        gpio_init.Pull = GPIO_NOPULL;
        break;

    default:
        return;
    }

    gpio->pulls[pin] = gpio_init.Pull;
    HAL_GPIO_Init(gpio->gpio, &gpio_init);
}

static void stm32_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);

    if (pin >= 0 && pin < STM32_GPIO_PIN_NR)
    {
        HAL_GPIO_WritePin(gpio->gpio, RT_BIT(pin),
                          value == PIN_LOW ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
}

static rt_ssize_t stm32_gpio_read(struct rt_device *device, rt_base_t pin)
{
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);

    if (pin < 0 || pin >= STM32_GPIO_PIN_NR)
    {
        return -RT_EINVAL;
    }

    return HAL_GPIO_ReadPin(gpio->gpio, RT_BIT(pin)) == GPIO_PIN_RESET ? PIN_LOW : PIN_HIGH;
}

static rt_err_t stm32_gpio_irq_prepare(struct stm32_gpio *gpio, rt_base_t pin,
                                       rt_uint8_t mode, GPIO_InitTypeDef *gpio_init, rt_uint32_t *irq_mode)
{
    gpio_init->Pin = RT_BIT(pin);
    gpio_init->Pull = gpio->pulls[pin];
    gpio_init->Speed = GPIO_SPEED_FREQ_HIGH;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        gpio_init->Mode = GPIO_MODE_IT_RISING;
        *irq_mode = RT_IRQ_MODE_EDGE_RISING;
        break;

    case PIN_IRQ_MODE_FALLING:
        gpio_init->Mode = GPIO_MODE_IT_FALLING;
        *irq_mode = RT_IRQ_MODE_EDGE_FALLING;
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        gpio_init->Mode = GPIO_MODE_IT_RISING_FALLING;
        *irq_mode = RT_IRQ_MODE_EDGE_BOTH;
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static void stm32_gpio_irq_handler(int vector, void *param)
{
    struct stm32_gpio_irq *irq = param;

    RT_UNUSED(vector);

    if (irq->handler)
    {
        irq->handler(irq->args);
    }
}

static rt_err_t stm32_gpio_attach_irq(struct rt_device *device, rt_base_t pin,
                                      rt_uint8_t mode, void (*handler)(void *args), void *args)
{
    struct stm32_gpio_irq *irq;
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);

    if (pin < 0 || pin >= STM32_GPIO_PIN_NR || !handler)
    {
        return -RT_EINVAL;
    }

    irq = &gpio->irqs[pin];
    if (irq->handler && (irq->handler != handler || irq->args != args))
    {
        return -RT_EBUSY;
    }

    irq->mode = mode;
    irq->handler = handler;
    irq->args = args;

    return RT_EOK;
}

static rt_err_t stm32_gpio_irq_enable(struct rt_device *device, rt_base_t pin,
                                      rt_uint8_t enabled)
{
    rt_err_t err, cleanup_err;
    rt_bool_t was_enabled;
    rt_uint32_t irq_mode;
    struct stm32_gpio_irq *irq;
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);
    GPIO_InitTypeDef gpio_init = { 0 };

    if (pin < 0 || pin >= STM32_GPIO_PIN_NR)
    {
        return -RT_EINVAL;
    }

    irq = &gpio->irqs[pin];
    if (enabled == PIN_IRQ_ENABLE)
    {
        if (!irq->handler)
        {
            return -RT_EINVAL;
        }
        if (irq->enabled)
        {
            return RT_EOK;
        }
        if ((err = stm32_gpio_irq_prepare(gpio, pin, irq->mode,
                                          &gpio_init, &irq_mode)))
        {
            return err;
        }

        if (!irq->acquired)
        {
            irq->irq = stm32_exti_acquire(gpio->exti, gpio->gpio, pin,
                                          irq_mode);
            if (irq->irq < 0)
            {
                return irq->irq;
            }
            irq->acquired = RT_TRUE;
        }

        if (!irq->pic_attached)
        {
            err = rt_pic_attach_irq(irq->irq, stm32_gpio_irq_handler,
                                    irq, "stm32-gpio", RT_IRQ_F_NONE);
            if (err)
            {
                cleanup_err = stm32_exti_release(gpio->exti, gpio->gpio,
                                                 pin);
                if (!cleanup_err)
                {
                    irq->acquired = RT_FALSE;
                    irq->irq = -1;
                }

                return cleanup_err ? cleanup_err : err;
            }
            irq->pic_attached = RT_TRUE;
        }

        HAL_GPIO_Init(gpio->gpio, &gpio_init);
        rt_pic_irq_unmask(irq->irq);
        irq->enabled = RT_TRUE;
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        if (!irq->acquired && !irq->pic_attached)
        {
            irq->enabled = RT_FALSE;
            return RT_EOK;
        }

        was_enabled = irq->enabled;
        if (was_enabled)
        {
            rt_pic_irq_mask(irq->irq);
        }

        if (irq->pic_attached)
        {
            err = rt_pic_detach_irq(irq->irq, irq);
            if (err)
            {
                if (was_enabled)
                {
                    rt_pic_irq_unmask(irq->irq);
                }
                return err;
            }
            irq->pic_attached = RT_FALSE;
        }

        if (irq->acquired)
        {
            err = stm32_exti_release(gpio->exti, gpio->gpio, pin);
            if (err)
            {
                cleanup_err = rt_pic_attach_irq(irq->irq,
                                                stm32_gpio_irq_handler, irq, "stm32-gpio",
                                                RT_IRQ_F_NONE);
                if (!cleanup_err)
                {
                    irq->pic_attached = RT_TRUE;
                    if (was_enabled)
                    {
                        rt_pic_irq_unmask(irq->irq);
                    }
                }
                else
                {
                    irq->enabled = RT_FALSE;
                }

                return cleanup_err ? cleanup_err : err;
            }
            irq->acquired = RT_FALSE;
            irq->irq = -1;
            HAL_GPIO_DeInit(gpio->gpio, RT_BIT(pin));
        }

        irq->enabled = RT_FALSE;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t stm32_gpio_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_err_t err;
    struct stm32_gpio_irq *irq;
    struct stm32_gpio *gpio = device_to_stm32_gpio(device);

    if (pin < 0 || pin >= STM32_GPIO_PIN_NR)
    {
        return -RT_EINVAL;
    }

    irq = &gpio->irqs[pin];
    if ((irq->enabled || irq->pic_attached || irq->acquired) &&
        (err = stm32_gpio_irq_enable(device, pin, PIN_IRQ_DISABLE)))
    {
        return err;
    }

    irq->handler = RT_NULL;
    irq->args = RT_NULL;
    irq->mode = 0;

    return RT_EOK;
}

static rt_ssize_t stm32_gpio_parse(struct rt_device *device,
                                   struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    RT_UNUSED(device);

    if (args->args_count != 2 || args->args[0] >= STM32_GPIO_PIN_NR)
    {
        return -RT_EINVAL;
    }

    if (flags)
    {
        *flags = args->args[1];
    }

    return args->args[0];
}

static const struct rt_pin_ops stm32_gpio_ops = {
    .pin_mode = stm32_gpio_mode,
    .pin_write = stm32_gpio_write,
    .pin_read = stm32_gpio_read,
    .pin_attach_irq = stm32_gpio_attach_irq,
    .pin_detach_irq = stm32_gpio_detach_irq,
    .pin_irq_enable = stm32_gpio_irq_enable,
    .pin_parse = stm32_gpio_parse,
};

static rt_err_t stm32_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t address, size;
    struct rt_ofw_node *exti_np;
    struct rt_device *dev = &pdev->parent;
    struct stm32_gpio *gpio = rt_calloc(1, sizeof(*gpio));

    if (!gpio)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_ofw_get_address(dev->ofw_node, 0, &address, &size)) || !size)
    {
        goto _fail;
    }

    if ((err = stm32_gpio_resolve(address, &gpio->gpio)))
    {
        goto _fail;
    }

    exti_np = rt_ofw_find_irq_parent(dev->ofw_node, RT_NULL);
    if (!exti_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    gpio->exti = stm32_exti_get(exti_np);
    rt_ofw_node_put(exti_np);
    if (!gpio->exti)
    {
        err = -RT_EIO;
        goto _fail;
    }

    for (int i = 0; i < STM32_GPIO_PIN_NR; ++i)
    {
        gpio->irqs[i].irq = -1;
    }

    gpio->parent.ops = &stm32_gpio_ops;
    if ((err = pin_api_init(&gpio->parent, STM32_GPIO_PIN_NR)))
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, &gpio->parent);

    return RT_EOK;

_fail:
    rt_free(gpio);

    return err;
}

static const struct rt_ofw_node_id stm32_gpio_ofw_ids[] = {
    { .compatible = "st,stm32-gpio" },
    { /* sentinel */ }
};

static struct rt_platform_driver stm32_gpio_driver = {
    .name = "stm32-gpio",
    .ids = stm32_gpio_ofw_ids,
    .probe = stm32_gpio_probe,
};

static int stm32_gpio_driver_register(void)
{
    return rt_platform_driver_register(&stm32_gpio_driver);
}
INIT_SUBSYS_EXPORT(stm32_gpio_driver_register);

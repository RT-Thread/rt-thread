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

#define PIN_MAX_NUM     (48)

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


struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
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
    rt_int32_t index = -1;
    rt_base_t level;
    if (pin >= PIN_MAX_NUM)
    {
        return -RT_EINVAL;
    }

    index = pin;
    level = rt_hw_interrupt_disable();

    pin_irq_hdr_tab[index].pin = pin;
    pin_irq_hdr_tab[index].hdr = cb;
    pin_irq_hdr_tab[index].mode = mode;
    pin_irq_hdr_tab[index].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t yc_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_int32_t index = -1;
    rt_base_t level;
    if (pin >= PIN_MAX_NUM)
    {
        return -RT_EINVAL;
    }

    index = pin;
    level = rt_hw_interrupt_disable();

    pin_irq_hdr_tab[index].pin = -1;
    pin_irq_hdr_tab[index].hdr = RT_NULL;
    pin_irq_hdr_tab[index].mode = 0;
    pin_irq_hdr_tab[index].args = RT_NULL;

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t yc_pin_irq_enable(struct rt_device *device,
                                  rt_base_t pin,
                                  rt_uint32_t enabled)
{
    rt_int32_t index;
    rt_base_t level = 0;
    if (pin >= PIN_MAX_NUM)
    {
        return -RT_EINVAL;
    }

    index = pin;

    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (pin_irq_hdr_tab[index].mode)
        {
        case PIN_IRQ_MODE_RISING:

            break;
        case PIN_IRQ_MODE_FALLING:

            break;
        case PIN_IRQ_MODE_RISING_FALLING:

            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_CONFIG(pin) = PULL_DOWN;
            GPIO_TRIG_MODE(pin / 16) &= (1 << (pin % 16));
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_CONFIG(pin) = PULL_UP;
            GPIO_TRIG_MODE(pin / 16) |= (1 << (pin % 16));
            break;
        default:
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        NVIC_EnableIRQ(GPIO_IRQn);
        GPIO_INTR_EN(pin / 16) |= (1 << (pin % 16));
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        NVIC_DisableIRQ(GPIO_IRQn);
        GPIO_INTR_EN(pin / 16) &= ~(1 << (pin % 16));
    }
    else
    {
        return -RT_ENOSYS;
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

void GPIO_IRQHandler(void)
{
    int i;

    rt_interrupt_enter();
    for (i = 0; i < PIN_MAX_NUM; i++)
    {
        if ((GPIO_TRIG_MODE(i / 16) & (1 << (i % 16))) == (GPIO_IN(i / 16) & (1 << (i % 16))))
        {
            if (pin_irq_hdr_tab[i].hdr)
            {
                pin_irq_hdr_tab[i].hdr(pin_irq_hdr_tab[i].args);
            }
        }
    }
    rt_interrupt_leave();
}

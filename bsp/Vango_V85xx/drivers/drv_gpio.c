/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-12-27     iysheng           first version
 * 2021-01-01     iysheng           support exti interrupt
 * 2021-09-07     FuC               Suit for Vango V85xx
 * 2021-09-09     ZhuXW             Fixing GPIO interrupt ...
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#if defined(GPIOF)
#define __V85XX_PORT_MAX 6u
#elif defined(GPIOE)
#define __V85XX_PORT_MAX 5u
#elif defined(GPIOD)
#define __V85XX_PORT_MAX 4u
#elif defined(GPIOC)
#define __V85XX_PORT_MAX 3u
#elif defined(GPIOB)
#define __V85XX_PORT_MAX 2u
#elif defined(GPIOA)
#define __V85XX_PORT_MAX 1u
#else
#define __V85XX_PORT_MAX 0u
#error Unsupported V85XX GPIO peripheral.
#endif

#define PIN_GDPORT_MAX __V85XX_PORT_MAX

static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
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
};
static uint32_t pin_irq_enable_mask = 0;

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static rt_base_t v85xx_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'F'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);

    return pin;
}

static void v85xx_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_GDPORT_MAX)
    {
        gpio_port = PIN_GDPORT(pin);
        gpio_pin = PIN_GDPIN(pin);

        GPIOBToF_WriteBit(gpio_port, gpio_pin, (BitState)value);//GPIOA ignored
    }
}

static int v85xx_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_GDPORT_MAX)
    {
        gpio_port = PIN_GDPORT(pin);
        gpio_pin = PIN_GDPIN(pin);
        value = GPIOBToF_ReadInputDataBit(gpio_port, gpio_pin);//GPIOA ignored
    }

    return value;
}

static void v85xx_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitType GPIO_InitStruct = {0};

    if (PIN_PORT(pin) >= PIN_GDPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin  = PIN_GDPIN(pin);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUTPUT_CMOS;
            break;
        case PIN_MODE_INPUT:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
            break;
        case PIN_MODE_INPUT_PULLUP:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_CMOS;
            break;
        case PIN_MODE_INPUT_PULLDOWN:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_OD;
            break;
        case PIN_MODE_OUTPUT_OD:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_OD;
            break;
        default:
            break;
    }

    GPIOBToF_Init(PIN_GDPORT(pin), &GPIO_InitStruct);//ignore GPIOA
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}


static rt_err_t v85xx_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_GDPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_GDPIN(pin));

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == pin &&
        pin_irq_hdr_tab[irqindex].hdr == hdr &&
        pin_irq_hdr_tab[irqindex].mode == mode &&
        pin_irq_hdr_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
static rt_err_t v85xx_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{

    return RT_EOK;
}
static rt_err_t v85xx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{

    return RT_EOK;
}



const static struct rt_pin_ops _v85xx_pin_ops =
{
    v85xx_pin_mode,
    v85xx_pin_write,
    v85xx_pin_read,
    v85xx_pin_attach_irq,
    v85xx_pin_detach_irq,
    v85xx_pin_irq_enable,
    v85xx_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

int rt_hw_pin_init(void)
{
  GPIO_InitType GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;

#if defined(GPIOF)
    GPIOBToF_Init(GPIOF, &GPIO_InitStruct);
#endif
#if defined(GPIOE)
    GPIOBToF_Init(GPIOE, &GPIO_InitStruct);
#endif
#if defined(GPIOD)
    GPIOBToF_Init(GPIOD, &GPIO_InitStruct);
#endif
#if defined(GPIOC)
    GPIOBToF_Init(GPIOC, &GPIO_InitStruct);
#endif
#if defined(GPIOB)
    GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
#endif
#if defined(GPIOA)
    GPIOA_Init(GPIOA, &GPIO_InitStruct);
#endif

    return rt_device_pin_register("pin", &_v85xx_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);
#endif /* RT_USING_PIN */


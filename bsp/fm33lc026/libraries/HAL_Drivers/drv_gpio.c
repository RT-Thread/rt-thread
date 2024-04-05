/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-7-20     wudiyidashi        first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no) (((((port)&0xFu) << 4) | ((no)&0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin)&0xFu))

#define PIN_STPORT(pin) ((GPIO_Type *)(GPIOA_BASE + (0x40u * PIN_PORT(pin))))
#define PIN_STPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

#define PIN_STPORT_MAX 4u

/*
    --GPIO-- |   EXTI INPUT   | --EXTI--
    PA0~PA3  | EXTI_ASEL[1:0] | EXTI[0]
    PA4~PA7  | EXTI_ASEL[3:2] | EXTI[1]
    PA8~PA11 | EXTI_ASEL[5:4] | EXTI[2]
    PA12~PA15| EXTI_ASEL[7:6] | EXTI[3]
    PB0~PB3  | EXTI_BSEL[1:0] | EXTI[4]
    PB4~PB7  | EXTI_BSEL[3:2] | EXTI[5]
    PB8~PB11 | EXTI_BSEL[5:4] | EXTI[6]
  PB12~PB15  | EXTI_BSEL[7:6] | EXTI[7]
    PC0~PC3  | EXTI_CSEL[1:0] | EXTI[8]
    PC4~PC7  | EXTI_CSEL[3:2] | EXTI[9]
  PC8~PC11   | EXTI_CSEL[5:4] | EXTI[10]
    PC12     |     -          | EXTI[11]
    PD0~PD3  | EXTI_DSEL[1:0] | EXTI[12]
    PD4~PD7  | EXTI_DSEL[3:2] | EXTI[13]
    PD8~PD11 | EXTI_DSEL[5:4] | EXTI[14]
    PD12     |     -          | EXTI[15]

{PIN_NUM(PA3),FL_GPIO_EXTI_LINE_0}
{PIN_NUM(PA7),FL_GPIO_EXTI_LINE_0}
    ...
{PIN_NUM(PD12),FL_GPIO_EXTI_LINE_0}
*/

static const struct pin_irq_map pin_irq_map[] =
    {
        {3, FL_GPIO_EXTI_LINE_0},
        {7, FL_GPIO_EXTI_LINE_1},
        {11, FL_GPIO_EXTI_LINE_2},
        {15, FL_GPIO_EXTI_LINE_3},
        {19, FL_GPIO_EXTI_LINE_4},
        {23, FL_GPIO_EXTI_LINE_5},
        {27, FL_GPIO_EXTI_LINE_6},
        {31, FL_GPIO_EXTI_LINE_7},
        {35, FL_GPIO_EXTI_LINE_8},
        {39, FL_GPIO_EXTI_LINE_9},
        {43, FL_GPIO_EXTI_LINE_10},
        {44, FL_GPIO_EXTI_LINE_11},
        {51, FL_GPIO_EXTI_LINE_12},
        {55, FL_GPIO_EXTI_LINE_13},
        {59, FL_GPIO_EXTI_LINE_14},
        {60, FL_GPIO_EXTI_LINE_15},
};

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

static rt_base_t fm33_pin_get(const char *name)
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

    if ((name[1] >= 'A') && (name[1] <= 'Z'))
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

static void fm33_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);

        if (value == PIN_LOW)
        {
            FL_GPIO_ResetOutputPin(gpio_port, gpio_pin);
        }
        else
        {
            FL_GPIO_SetOutputPin(gpio_port, gpio_pin);
        }
    }
}

static rt_ssize_t fm33_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    rt_ssize_t value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);
        value = FL_GPIO_GetInputPin(gpio_port, gpio_pin);
    }
    else
    {
        value = -RT_EINVAL;
    }

    return value;
}

static void fm33_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.pin = PIN_STPIN(pin);
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
        GPIO_InitStruct.pull = FL_DISABLE;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStruct.pull = FL_DISABLE;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStruct.pull = FL_ENABLE;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStruct.pull = FL_DISABLE;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.mode = FL_GPIO_OUTPUT_OPENDRAIN;
        GPIO_InitStruct.pull = FL_DISABLE;
    }

    FL_GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);
}

rt_inline rt_int32_t pin2irqindex(rt_uint32_t pin)
{
    rt_uint8_t irqindex;
    for (irqindex = 4 * PIN_PORT(pin); irqindex <= ITEM_NUM(pin_irq_map); irqindex++)
    {
        if (pin_irq_map[irqindex].pin >= pin && pin_irq_map[irqindex - 1].pin < pin)
        {
            return irqindex;
        }
    }
    return -1;
}

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_base_t pin)
{
    rt_int32_t mapindex;
    mapindex = pin2irqindex(pin);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t fm33_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = pin2irqindex(pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

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
        return -RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t fm33_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = pin2irqindex(PIN_STPIN(pin));
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t fm33_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int8_t irqindex = 0;
    FL_GPIO_InitTypeDef GPIO_InitStruct;
    FL_EXTI_InitTypeDef extiInitStruct = {0};
    FL_EXTI_CommonInitTypeDef extiCommonInitStruct = {0};

    FL_RCC_EnableEXTIOnSleep();

    extiCommonInitStruct.clockSource = FL_RCC_EXTI_CLK_SOURCE_HCLK;
    FL_EXTI_CommonInit(&extiCommonInitStruct);

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_ENOSYS;
        }

        irqindex = pin2irqindex(pin);
        irqmap = &pin_irq_map[irqindex];

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        /* Configure GPIO_InitStructure */
        GPIO_InitStruct.pin = PIN_STPIN(pin);
        GPIO_InitStruct.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStruct.pull = FL_DISABLE;
        GPIO_InitStruct.remapPin = FL_DISABLE;

        extiInitStruct.input = pin - pin_irq_map[irqindex - 1].pin - 1;
        extiInitStruct.filter = FL_ENABLE;

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            extiInitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            extiInitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            extiInitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_BOTH;
            break;
        }
        FL_GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);
        FL_EXTI_Init(irqmap->irqno, &extiInitStruct);

        NVIC_DisableIRQ(GPIO_IRQn);
        NVIC_SetPriority(GPIO_IRQn, 2);
        NVIC_EnableIRQ(GPIO_IRQn);
        pin_irq_enable_mask |= irqmap->irqno;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(PIN_STPIN(pin));
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        FL_GPIO_DeInit(PIN_STPORT(pin), PIN_STPIN(pin));

        pin_irq_enable_mask &= ~irqmap->irqno;

        NVIC_DisableIRQ(GPIO_IRQn);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _fm33_pin_ops =
{
        fm33_pin_mode,
        fm33_pin_write,
        fm33_pin_read,
        fm33_pin_attach_irq,
        fm33_pin_dettach_irq,
        fm33_pin_irq_enable,
        fm33_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_IRQHandler(void)
{
    rt_interrupt_enter();
    for (uint8_t extinum = 0; extinum < 16; ++extinum)
    {
        if (FL_GPIO_IsActiveFlag_EXTI(GPIO, 0x1U << extinum))
        {
            FL_GPIO_ClearFlag_EXTI(GPIO, 0x1U << extinum);
            pin_irq_hdr(extinum);
        }
    }
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_fm33_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */

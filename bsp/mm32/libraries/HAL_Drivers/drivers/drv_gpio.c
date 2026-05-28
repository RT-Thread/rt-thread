/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rthw.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define LOG_TAG             "drv.gpio"
#include <rtdbg.h>

#define PIN_NUM(port, no)       (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)           ((rt_uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)             ((rt_uint8_t)((pin) & 0xFu))
#define ITEM_NUM(items)         (sizeof(items) / sizeof((items)[0]))

static struct rt_pin_irq_hdr pin_irq_hdr_tab[16] =
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

static rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_uint8_t i;

    for (i = 0; i < 32; i++)
    {
        if ((1UL << i) == bit)
        {
            return i;
        }
    }

    return -1;
}

#if defined(SOC_SERIES_MM32F3277)

#include <hal_gpio.h>
#include <hal_exti.h>
#include <hal_syscfg.h>
#include <hal_rcc.h>

typedef GPIO_Type mm32_gpio_t;

struct mm32_pin_desc
{
    mm32_gpio_t *gpio;
    rt_uint16_t pin;
};

#if defined(GPIOF)
#define PIN_PORT_MAX    6u
#elif defined(GPIOE)
#define PIN_PORT_MAX    5u
#elif defined(GPIOD)
#define PIN_PORT_MAX    4u
#elif defined(GPIOC)
#define PIN_PORT_MAX    3u
#elif defined(GPIOB)
#define PIN_PORT_MAX    2u
#elif defined(GPIOA)
#define PIN_PORT_MAX    1u
#else
#error Unsupported MM32 GPIO peripheral.
#endif

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn, EXTI_LINE_0, SYSCFG_EXTILine_0},
    {GPIO_PIN_1, EXTI1_IRQn, EXTI_LINE_1, SYSCFG_EXTILine_1},
    {GPIO_PIN_2, EXTI2_IRQn, EXTI_LINE_2, SYSCFG_EXTILine_2},
    {GPIO_PIN_3, EXTI3_IRQn, EXTI_LINE_3, SYSCFG_EXTILine_3},
    {GPIO_PIN_4, EXTI4_IRQn, EXTI_LINE_4, SYSCFG_EXTILine_4},
    {GPIO_PIN_5, EXTI9_5_IRQn, EXTI_LINE_5, SYSCFG_EXTILine_5},
    {GPIO_PIN_6, EXTI9_5_IRQn, EXTI_LINE_6, SYSCFG_EXTILine_6},
    {GPIO_PIN_7, EXTI9_5_IRQn, EXTI_LINE_7, SYSCFG_EXTILine_7},
    {GPIO_PIN_8, EXTI9_5_IRQn, EXTI_LINE_8, SYSCFG_EXTILine_8},
    {GPIO_PIN_9, EXTI9_5_IRQn, EXTI_LINE_9, SYSCFG_EXTILine_9},
    {GPIO_PIN_10, EXTI15_10_IRQn, EXTI_LINE_10, SYSCFG_EXTILine_10},
    {GPIO_PIN_11, EXTI15_10_IRQn, EXTI_LINE_11, SYSCFG_EXTILine_11},
    {GPIO_PIN_12, EXTI15_10_IRQn, EXTI_LINE_12, SYSCFG_EXTILine_12},
    {GPIO_PIN_13, EXTI15_10_IRQn, EXTI_LINE_13, SYSCFG_EXTILine_13},
    {GPIO_PIN_14, EXTI15_10_IRQn, EXTI_LINE_14, SYSCFG_EXTILine_14},
    {GPIO_PIN_15, EXTI15_10_IRQn, EXTI_LINE_15, SYSCFG_EXTILine_15},
};

static rt_err_t mm32_pin_to_desc(rt_base_t pin, struct mm32_pin_desc *desc)
{
    if ((PIN_PORT(pin) >= PIN_PORT_MAX) || (PIN_NO(pin) > 15))
    {
        return -RT_EINVAL;
    }

    desc->gpio = (mm32_gpio_t *)(GPIOA_BASE + (0x400u * PIN_PORT(pin)));
    desc->pin = (rt_uint16_t)(1u << PIN_NO(pin));

    return RT_EOK;
}

static void mm32_gpio_clock_enable(rt_uint8_t port)
{
    switch (port)
    {
#ifdef RCC_AHB1_PERIPH_GPIOA
    case 0: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOA, true); break;
#endif
#ifdef RCC_AHB1_PERIPH_GPIOB
    case 1: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOB, true); break;
#endif
#ifdef RCC_AHB1_PERIPH_GPIOC
    case 2: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOC, true); break;
#endif
#ifdef RCC_AHB1_PERIPH_GPIOD
    case 3: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOD, true); break;
#endif
#ifdef RCC_AHB1_PERIPH_GPIOE
    case 4: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOE, true); break;
#endif
#ifdef RCC_AHB1_PERIPH_GPIOF
    case 5: RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOF, true); break;
#endif
    default: break;
    }
}

static void mm32_gpio_write(mm32_gpio_t *gpio, rt_uint16_t pin, rt_uint8_t value)
{
    GPIO_WriteBit(gpio, pin, value == PIN_LOW ? 0 : 1);
}

static rt_uint8_t mm32_gpio_read(mm32_gpio_t *gpio, rt_uint16_t pin)
{
    return GPIO_ReadInDataBit(gpio, pin) ? PIN_HIGH : PIN_LOW;
}

static void mm32_gpio_mode(mm32_gpio_t *gpio, rt_uint16_t pin, rt_uint8_t mode)
{
    GPIO_Init_Type init;

    init.Pins = pin;
    init.Speed = GPIO_Speed_50MHz;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        init.PinMode = GPIO_PinMode_Out_PushPull;
        break;
    case PIN_MODE_OUTPUT_OD:
        init.PinMode = GPIO_PinMode_Out_OpenDrain;
        break;
    case PIN_MODE_INPUT_PULLUP:
        init.PinMode = GPIO_PinMode_In_PullUp;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        init.PinMode = GPIO_PinMode_In_PullDown;
        break;
    case PIN_MODE_INPUT:
    default:
        init.PinMode = GPIO_PinMode_In_Floating;
        break;
    }

    GPIO_Init(gpio, &init);
}

static void mm32_gpio_irq_config(rt_base_t pin, const struct pin_irq_map *irqmap, rt_uint8_t mode)
{
    struct mm32_pin_desc desc;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return;
    }

    mm32_gpio_mode(desc.gpio, desc.pin, PIN_MODE_INPUT_PULLUP);
    SYSCFG_SetExtIntMux((SYSCFG_EXTIPort_Type)(SYSCFG_EXTIPort_GPIOA + PIN_PORT(pin)), irqmap->syscfg_extiline);

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_RisingEdge);
        break;
    case PIN_IRQ_MODE_FALLING:
        EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_FallingEdge);
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_BothEdges);
        break;
    default:
        EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_Disable);
        break;
    }

    EXTI_EnableLineInterrupt(EXTI, irqmap->extiline, true);
    NVIC_SetPriority(irqmap->irqno, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
    NVIC_EnableIRQ(irqmap->irqno);
}

static void mm32_gpio_irq_disable(const struct pin_irq_map *irqmap)
{
    EXTI_EnableLineInterrupt(EXTI, irqmap->extiline, false);
    NVIC_DisableIRQ(irqmap->irqno);
}

static void mm32_gpio_clear_irq(const struct pin_irq_map *irqmap)
{
    EXTI->PR = irqmap->extiline;
}

static rt_bool_t mm32_gpio_irq_pending(const struct pin_irq_map *irqmap)
{
    return (EXTI->PR & irqmap->extiline) != 0;
}

#else

#include <hal_gpio.h>
#include <hal_exti.h>
#include <hal_misc.h>
#include <hal_rcc.h>
#if defined(SOC_SERIES_MM32F526)
#include <hal_syscfg.h>
#endif

typedef GPIO_TypeDef mm32_gpio_t;

struct mm32_pin_desc
{
    mm32_gpio_t *gpio;
    rt_uint16_t pin;
    rt_uint32_t rcc;
    rt_uint8_t port_source;
    rt_uint8_t pin_source;
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    rt_uint32_t irqbit;
    IRQn_Type irqno;
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_Pin_0, EXTI_Line0, EXTI0_IRQn},
    {GPIO_Pin_1, EXTI_Line1, EXTI1_IRQn},
    {GPIO_Pin_2, EXTI_Line2, EXTI2_IRQn},
    {GPIO_Pin_3, EXTI_Line3, EXTI3_IRQn},
    {GPIO_Pin_4, EXTI_Line4, EXTI4_IRQn},
    {GPIO_Pin_5, EXTI_Line5, EXTI9_5_IRQn},
    {GPIO_Pin_6, EXTI_Line6, EXTI9_5_IRQn},
    {GPIO_Pin_7, EXTI_Line7, EXTI9_5_IRQn},
    {GPIO_Pin_8, EXTI_Line8, EXTI9_5_IRQn},
    {GPIO_Pin_9, EXTI_Line9, EXTI9_5_IRQn},
    {GPIO_Pin_10, EXTI_Line10, EXTI15_10_IRQn},
    {GPIO_Pin_11, EXTI_Line11, EXTI15_10_IRQn},
    {GPIO_Pin_12, EXTI_Line12, EXTI15_10_IRQn},
    {GPIO_Pin_13, EXTI_Line13, EXTI15_10_IRQn},
    {GPIO_Pin_14, EXTI_Line14, EXTI15_10_IRQn},
    {GPIO_Pin_15, EXTI_Line15, EXTI15_10_IRQn},
};

#if defined(GPIOF)
#define PIN_PORT_MAX    6u
#elif defined(GPIOE)
#define PIN_PORT_MAX    5u
#elif defined(GPIOD)
#define PIN_PORT_MAX    4u
#elif defined(GPIOC)
#define PIN_PORT_MAX    3u
#elif defined(GPIOB)
#define PIN_PORT_MAX    2u
#elif defined(GPIOA)
#define PIN_PORT_MAX    1u
#else
#error Unsupported MM32 GPIO peripheral.
#endif

static rt_uint32_t mm32_gpio_rcc(rt_uint8_t port)
{
#if defined(SOC_SERIES_MM32F103) || defined(SOC_SERIES_MM32L3)
    switch (port)
    {
    case 0: return RCC_APB2Periph_GPIOA;
    case 1: return RCC_APB2Periph_GPIOB;
    case 2: return RCC_APB2Periph_GPIOC;
    case 3: return RCC_APB2Periph_GPIOD;
#ifdef RCC_APB2Periph_GPIOE
    case 4: return RCC_APB2Periph_GPIOE;
#endif
#ifdef RCC_APB2Periph_GPIOF
    case 5: return RCC_APB2Periph_GPIOF;
#endif
    default: return 0;
    }
#else
    return (rt_uint32_t)(1u << port);
#endif
}

static rt_err_t mm32_pin_to_desc(rt_base_t pin, struct mm32_pin_desc *desc)
{
    if ((PIN_PORT(pin) >= PIN_PORT_MAX) || (PIN_NO(pin) > 15))
    {
        return -RT_EINVAL;
    }

    desc->gpio = (mm32_gpio_t *)(GPIOA_BASE + (0x400u * PIN_PORT(pin)));
    desc->pin = (rt_uint16_t)(1u << PIN_NO(pin));
    desc->rcc = mm32_gpio_rcc(PIN_PORT(pin));
    desc->port_source = PIN_PORT(pin);
    desc->pin_source = PIN_NO(pin);

    return RT_EOK;
}

static void mm32_gpio_clock_enable(rt_uint32_t rcc)
{
#if defined(SOC_SERIES_MM32F327) || defined(SOC_SERIES_MM32F526)
    RCC_AHBPeriphClockCmd(rcc, ENABLE);
#else
    RCC_APB2PeriphClockCmd(rcc, ENABLE);
#endif
}

static void mm32_gpio_write(mm32_gpio_t *gpio, rt_uint16_t pin, rt_uint8_t value)
{
    GPIO_WriteBit(gpio, pin, value == PIN_LOW ? Bit_RESET : Bit_SET);
}

static rt_uint8_t mm32_gpio_read(mm32_gpio_t *gpio, rt_uint16_t pin)
{
    return GPIO_ReadInputDataBit(gpio, pin) == Bit_RESET ? PIN_LOW : PIN_HIGH;
}

static void mm32_gpio_mode(mm32_gpio_t *gpio, rt_uint16_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef init;

    init.GPIO_Pin = pin;
#if defined(SOC_SERIES_MM32F526)
    init.GPIO_Speed = GPIO_Speed_High;
#else
    init.GPIO_Speed = GPIO_Speed_50MHz;
#endif

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        init.GPIO_Mode = GPIO_Mode_Out_PP;
        break;
    case PIN_MODE_OUTPUT_OD:
        init.GPIO_Mode = GPIO_Mode_Out_OD;
        break;
    case PIN_MODE_INPUT_PULLUP:
        init.GPIO_Mode = GPIO_Mode_IPU;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        init.GPIO_Mode = GPIO_Mode_IPD;
        break;
    case PIN_MODE_INPUT:
    default:
#if defined(SOC_SERIES_MM32F526)
        init.GPIO_Mode = GPIO_Mode_FLOATING;
#else
        init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif
        break;
    }

    GPIO_Init(gpio, &init);
}

static void mm32_gpio_irq_config(rt_base_t pin, const struct pin_irq_map *irqmap, rt_uint8_t mode)
{
    struct mm32_pin_desc desc;
    NVIC_InitTypeDef nvic_init;
    EXTI_InitTypeDef exti_init;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return;
    }

    mm32_gpio_clock_enable(desc.rcc);
    mm32_gpio_mode(desc.gpio, desc.pin, PIN_MODE_INPUT_PULLUP);

    nvic_init.NVIC_IRQChannel = irqmap->irqno;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init.NVIC_IRQChannelSubPriority = 2;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

#if defined(SOC_SERIES_MM32F526)
    SYSCFG_EXTILineConfig(desc.port_source, desc.pin_source);
#else
    GPIO_EXTILineConfig(desc.port_source, desc.pin_source);
#endif

    exti_init.EXTI_Line = irqmap->irqbit;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_LineCmd = ENABLE;

    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
        break;
    case PIN_IRQ_MODE_FALLING:
        exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        exti_init.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
        break;
    default:
        exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
        break;
    }

    EXTI_Init(&exti_init);
}

static void mm32_gpio_irq_disable(const struct pin_irq_map *irqmap)
{
    EXTI_InitTypeDef exti_init;

    exti_init.EXTI_Line = irqmap->irqbit;
    exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
    exti_init.EXTI_Trigger = EXTI_Trigger_Rising;
    exti_init.EXTI_LineCmd = DISABLE;
    EXTI_Init(&exti_init);
    NVIC_DisableIRQ(irqmap->irqno);
}

static void mm32_gpio_clear_irq(const struct pin_irq_map *irqmap)
{
    EXTI_ClearITPendingBit(irqmap->irqbit);
}

static rt_bool_t mm32_gpio_irq_pending(const struct pin_irq_map *irqmap)
{
    return EXTI_GetITStatus(irqmap->irqbit) != RESET;
}

#endif

static rt_base_t mm32_pin_get(const char *name)
{
    int hw_port_num;
    int hw_pin_num = 0;
    int i;
    int name_len;

    RT_ASSERT(name != RT_NULL);

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
        if ((name[i] < '0') || (name[i] > '9'))
        {
            return -RT_EINVAL;
        }
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    if ((hw_pin_num < 0) || (hw_pin_num > 15))
    {
        return -RT_EINVAL;
    }

    return PIN_NUM(hw_port_num, hw_pin_num);
}

static const struct pin_irq_map *get_pin_irq_map(rt_uint32_t pinbit)
{
    rt_int32_t index = bit2bitno(pinbit);

    if ((index < 0) || ((rt_size_t)index >= ITEM_NUM(pin_irq_map)))
    {
        return RT_NULL;
    }

    return &pin_irq_map[index];
}

static void mm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    struct mm32_pin_desc desc;

    if (mm32_pin_to_desc(pin, &desc) == RT_EOK)
    {
        mm32_gpio_write(desc.gpio, desc.pin, value);
    }
}

static rt_ssize_t mm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    struct mm32_pin_desc desc;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    return mm32_gpio_read(desc.gpio, desc.pin);
}

static void mm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    struct mm32_pin_desc desc;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return;
    }

#if defined(SOC_SERIES_MM32F3277)
    mm32_gpio_clock_enable(PIN_PORT(pin));
#else
    mm32_gpio_clock_enable(desc.rcc);
#endif
    mm32_gpio_mode(desc.gpio, desc.pin, mode);
}

static rt_err_t mm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    struct mm32_pin_desc desc;
    rt_base_t level;
    rt_int32_t irqindex;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(desc.pin);
    if ((irqindex < 0) || ((rt_size_t)irqindex >= ITEM_NUM(pin_irq_hdr_tab)))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if ((pin_irq_hdr_tab[irqindex].pin == pin) &&
        (pin_irq_hdr_tab[irqindex].hdr == hdr) &&
        (pin_irq_hdr_tab[irqindex].mode == mode) &&
        (pin_irq_hdr_tab[irqindex].args == args))
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

static rt_err_t mm32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    struct mm32_pin_desc desc;
    rt_base_t level;
    rt_int32_t irqindex;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(desc.pin);
    if ((irqindex < 0) || ((rt_size_t)irqindex >= ITEM_NUM(pin_irq_hdr_tab)))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t mm32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    struct mm32_pin_desc desc;
    const struct pin_irq_map *irqmap;
    rt_int32_t irqindex;

    if (mm32_pin_to_desc(pin, &desc) != RT_EOK)
    {
        return -RT_ENOSYS;
    }

    irqmap = get_pin_irq_map(desc.pin);
    if (irqmap == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(desc.pin);
    if ((irqindex < 0) || ((rt_size_t)irqindex >= ITEM_NUM(pin_irq_hdr_tab)))
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            return -RT_ENOSYS;
        }

        mm32_gpio_irq_config(pin, irqmap, pin_irq_hdr_tab[irqindex].mode);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        mm32_gpio_irq_disable(irqmap);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static const struct rt_pin_ops mm32_pin_ops =
{
    .pin_mode = mm32_pin_mode,
    .pin_write = mm32_pin_write,
    .pin_read = mm32_pin_read,
    .pin_attach_irq = mm32_pin_attach_irq,
    .pin_detach_irq = mm32_pin_detach_irq,
    .pin_irq_enable = mm32_pin_irq_enable,
    .pin_get = mm32_pin_get,
};

static void pin_irq_hdr(int irqno)
{
    if ((irqno < 0) || ((rt_size_t)irqno >= ITEM_NUM(pin_irq_hdr_tab)))
    {
        return;
    }

    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

static void mm32_gpio_exti_handle(int irqno)
{
    const struct pin_irq_map *irqmap = &pin_irq_map[irqno];

    if (mm32_gpio_irq_pending(irqmap))
    {
        mm32_gpio_clear_irq(irqmap);
        pin_irq_hdr(irqno);
    }
}

#define MM32_EXTI_IRQHandler(name, first, last)   \
void name(void)                                   \
{                                                 \
    int i;                                        \
    rt_interrupt_enter();                         \
    for (i = (first); i <= (last); i++)           \
    {                                             \
        mm32_gpio_exti_handle(i);                 \
    }                                             \
    rt_interrupt_leave();                         \
}

MM32_EXTI_IRQHandler(EXTI0_IRQHandler, 0, 0)
MM32_EXTI_IRQHandler(EXTI1_IRQHandler, 1, 1)
MM32_EXTI_IRQHandler(EXTI2_IRQHandler, 2, 2)
MM32_EXTI_IRQHandler(EXTI3_IRQHandler, 3, 3)
MM32_EXTI_IRQHandler(EXTI4_IRQHandler, 4, 4)
MM32_EXTI_IRQHandler(EXTI9_5_IRQHandler, 5, 9)
MM32_EXTI_IRQHandler(EXTI15_10_IRQHandler, 10, 15)

int rt_hw_pin_init(void)
{
#if defined(SOC_SERIES_MM32F3277)
#ifdef RCC_APB2_PERIPH_SYSCFG
    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_SYSCFG, true);
#endif
#endif

    return rt_device_pin_register("pin", &mm32_pin_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */

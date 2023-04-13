/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 * 2022-07-15     Aligagago    add apm32F4 series MCU support
 * 2022-12-26     luobeihai    add apm32F0 series MCU support
 * 2022-03-18     luobeihai    fix warning about incompatible function pointer types
 * 2023-03-27     luobeihai    add APM32E1/S1 series MCU support
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_APMPORT(pin) ((GPIO_T *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_APMPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

#if defined(GPIOZ)
    #define __APM32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __APM32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __APM32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __APM32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __APM32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __APM32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __APM32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __APM32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __APM32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __APM32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __APM32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __APM32_PORT_MAX 1u
#else
    #define __APM32_PORT_MAX 0u
    #error Unsupported APM32 GPIO peripheral.
#endif

#define PIN_APMPORT_MAX __APM32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
#if defined(SOC_SERIES_APM32F0)
    {GPIO_PIN_0, EINT0_1_IRQn},
    {GPIO_PIN_1, EINT0_1_IRQn},
    {GPIO_PIN_2, EINT2_3_IRQn},
    {GPIO_PIN_3, EINT2_3_IRQn},
    {GPIO_PIN_4, EINT4_15_IRQn},
    {GPIO_PIN_5, EINT4_15_IRQn},
    {GPIO_PIN_6, EINT4_15_IRQn},
    {GPIO_PIN_7, EINT4_15_IRQn},
    {GPIO_PIN_8, EINT4_15_IRQn},
    {GPIO_PIN_9, EINT4_15_IRQn},
    {GPIO_PIN_10, EINT4_15_IRQn},
    {GPIO_PIN_11, EINT4_15_IRQn},
    {GPIO_PIN_12, EINT4_15_IRQn},
    {GPIO_PIN_13, EINT4_15_IRQn},
    {GPIO_PIN_14, EINT4_15_IRQn},
    {GPIO_PIN_15, EINT4_15_IRQn},
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    {GPIO_PIN_0, EINT0_IRQn},
    {GPIO_PIN_1, EINT1_IRQn},
    {GPIO_PIN_2, EINT2_IRQn},
    {GPIO_PIN_3, EINT3_IRQn},
    {GPIO_PIN_4, EINT4_IRQn},
    {GPIO_PIN_5, EINT9_5_IRQn},
    {GPIO_PIN_6, EINT9_5_IRQn},
    {GPIO_PIN_7, EINT9_5_IRQn},
    {GPIO_PIN_8, EINT9_5_IRQn},
    {GPIO_PIN_9, EINT9_5_IRQn},
    {GPIO_PIN_10, EINT15_10_IRQn},
    {GPIO_PIN_11, EINT15_10_IRQn},
    {GPIO_PIN_12, EINT15_10_IRQn},
    {GPIO_PIN_13, EINT15_10_IRQn},
    {GPIO_PIN_14, EINT15_10_IRQn},
    {GPIO_PIN_15, EINT15_10_IRQn},
#endif /* SOC_SERIES_APM32F0 */
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

static rt_base_t apm32_pin_get(const char *name)
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

static void apm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_T *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_APMPORT_MAX)
    {
        gpio_port = PIN_APMPORT(pin);
        gpio_pin = PIN_APMPIN(pin);
#if defined(SOC_SERIES_APM32F0)
        GPIO_WriteBitValue(gpio_port, gpio_pin, (GPIO_BSRET_T)value);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        GPIO_WriteBitValue(gpio_port, gpio_pin, (uint8_t)value);
#endif
    }
}

static rt_int8_t apm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_T *gpio_port;
    uint16_t gpio_pin;
    int value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_APMPORT_MAX)
    {
        gpio_port = PIN_APMPORT(pin);
        gpio_pin = PIN_APMPIN(pin);
        value = GPIO_ReadInputBit(gpio_port, gpio_pin);
    }

    return value;
}

static void apm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_Config_T gpioConfig;

    if (PIN_PORT(pin) >= PIN_APMPORT_MAX)
    {
        return;
    }

    /* Configure gpioConfigure */
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
    gpioConfig.pin = PIN_APMPIN(pin);
    gpioConfig.mode = GPIO_MODE_OUT_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpioConfig.mode = GPIO_MODE_OUT_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpioConfig.mode = GPIO_MODE_IN_PU;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpioConfig.mode = GPIO_MODE_IN_PU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpioConfig.mode = GPIO_MODE_IN_PD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpioConfig.mode = GPIO_MODE_OUT_OD;
    }
#elif defined(SOC_SERIES_APM32F4)
    gpioConfig.pin = PIN_APMPIN(pin);
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.otype = GPIO_OTYPE_PP;
    gpioConfig.speed = GPIO_SPEED_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpioConfig.mode = GPIO_MODE_OUT;
        gpioConfig.otype = GPIO_OTYPE_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpioConfig.mode = GPIO_MODE_OUT;
        gpioConfig.otype = GPIO_OTYPE_OD;
    }
#elif defined(SOC_SERIES_APM32F0)
    gpioConfig.pin = PIN_APMPIN(pin);
    gpioConfig.mode = GPIO_MODE_OUT;
    gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    gpioConfig.pupd = GPIO_PUPD_NO;
    gpioConfig.speed = GPIO_SPEED_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpioConfig.mode = GPIO_MODE_OUT;
        gpioConfig.outtype = GPIO_OUT_TYPE_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_NO;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_PU;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpioConfig.mode = GPIO_MODE_IN;
        gpioConfig.pupd = GPIO_PUPD_PD;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpioConfig.mode = GPIO_MODE_OUT;
        gpioConfig.outtype = GPIO_OUT_TYPE_OD;
    }
#endif
    GPIO_Config(PIN_APMPORT(pin), &gpioConfig);
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

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t apm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_APMPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_APMPIN(pin));
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

static rt_err_t apm32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_APMPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_APMPIN(pin));
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

static rt_err_t apm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_Config_T gpioConfig;
    EINT_Config_T eintConfig;

    if (PIN_PORT(pin) >= PIN_APMPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_APMPIN(pin));
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        irqmap = &pin_irq_map[irqindex];

        /* Configure gpioConfigure */
        gpioConfig.pin = PIN_APMPIN(pin);
        gpioConfig.speed = GPIO_SPEED_50MHz;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
#if defined(SOC_SERIES_APM32F0)
        case PIN_IRQ_MODE_RISING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_PD;
            eintConfig.trigger = EINT_TRIGGER_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_PU;
            eintConfig.trigger = EINT_TRIGGER_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_NO;
            eintConfig.trigger = EINT_TRIGGER_ALL;
            break;
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
        case PIN_IRQ_MODE_RISING:
            gpioConfig.mode = GPIO_MODE_IN_PD;
            eintConfig.trigger = EINT_TRIGGER_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            gpioConfig.mode = GPIO_MODE_IN_PU;
            eintConfig.trigger = EINT_TRIGGER_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            gpioConfig.mode = GPIO_MODE_IN_FLOATING;
            eintConfig.trigger = EINT_TRIGGER_RISING_FALLING;
            break;
#elif defined(SOC_SERIES_APM32F4)
        case PIN_IRQ_MODE_RISING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_DOWN;
            eintConfig.trigger = EINT_TRIGGER_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_UP;
            eintConfig.trigger = EINT_TRIGGER_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            gpioConfig.mode = GPIO_MODE_IN;
            gpioConfig.pupd = GPIO_PUPD_NOPULL;
            eintConfig.trigger = EINT_TRIGGER_RISING_FALLING;
            break;
#endif
        }
        GPIO_Config(PIN_APMPORT(pin), &gpioConfig);

#if defined(SOC_SERIES_APM32F0)
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
        SYSCFG_EINTLine((SYSCFG_PORT_T)(((pin) >> 4) & 0xFu), (SYSCFG_PIN_T)irqindex);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
        GPIO_ConfigEINTLine((GPIO_PORT_SOURCE_T)(((pin) >> 4) & 0xFu), (GPIO_PIN_SOURCE_T)irqindex);
#elif defined(SOC_SERIES_APM32F4)
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);
        SYSCFG_ConfigEINTLine((SYSCFG_PORT_T)(((pin) >> 4) & 0xFu), (SYSCFG_PIN_T)irqindex);
#endif
        eintConfig.line = (EINT_LINE_T)(1u << PIN_NO(pin));
        eintConfig.mode = EINT_MODE_INTERRUPT;
        eintConfig.lineCmd = ENABLE;
        EINT_Config(&eintConfig);

#if defined(SOC_SERIES_APM32F0)
        NVIC_EnableIRQRequest(irqmap->irqno, 5);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        NVIC_EnableIRQRequest(irqmap->irqno, 5, 0);
#endif
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(PIN_APMPIN(pin));
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;

#if defined(SOC_SERIES_APM32F0)
        if ((irqmap->pinbit >= GPIO_PIN_0) && (irqmap->pinbit <= GPIO_PIN_1))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_0 | GPIO_PIN_1)))
            {
                NVIC_DisableIRQRequest(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_PIN_2) && (irqmap->pinbit <= GPIO_PIN_3))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_2 | GPIO_PIN_3)))
            {
                NVIC_DisableIRQRequest(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_PIN_4) && (irqmap->pinbit <= GPIO_PIN_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
                                         GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)))
            {
                NVIC_DisableIRQRequest(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQRequest(irqmap->irqno);
        }
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
        if ((irqmap->pinbit >= GPIO_PIN_5) && (irqmap->pinbit <= GPIO_PIN_9))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9)))
            {
                NVIC_DisableIRQRequest(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_PIN_10) && (irqmap->pinbit <= GPIO_PIN_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)))
            {
                NVIC_DisableIRQRequest(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQRequest(irqmap->irqno);
        }
#endif /* SOC_SERIES_APM32F0 */
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

const static struct rt_pin_ops apm32_pin_ops =
{
    apm32_pin_mode,
    apm32_pin_write,
    apm32_pin_read,
    apm32_pin_attach_irq,
    apm32_pin_dettach_irq,
    apm32_pin_irq_enable,
    apm32_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_IRQHandler(uint8_t exti_line)
{
#if defined(SOC_SERIES_APM32F0)
    if (EINT_ReadIntFlag(1U << exti_line) != RESET)
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    if (EINT_ReadIntFlag((EINT_LINE_T)(1U << exti_line)) != RESET)
#endif
    {
        EINT_ClearIntFlag(1U << exti_line);
        pin_irq_hdr(exti_line);
    }
}

#if defined(SOC_SERIES_APM32F0)
void EINT0_1_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(0);
    GPIO_EXTI_IRQHandler(1);
    rt_interrupt_leave();
}

void EINT2_3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(2);
    GPIO_EXTI_IRQHandler(3);
    rt_interrupt_leave();
}
void EINT4_15_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(4);
    GPIO_EXTI_IRQHandler(5);
    GPIO_EXTI_IRQHandler(6);
    GPIO_EXTI_IRQHandler(7);
    GPIO_EXTI_IRQHandler(8);
    GPIO_EXTI_IRQHandler(9);
    GPIO_EXTI_IRQHandler(10);
    GPIO_EXTI_IRQHandler(11);
    GPIO_EXTI_IRQHandler(12);
    GPIO_EXTI_IRQHandler(13);
    GPIO_EXTI_IRQHandler(14);
    GPIO_EXTI_IRQHandler(15);
    rt_interrupt_leave();
}
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
void EINT0_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(0);
    rt_interrupt_leave();
}

void EINT1_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(1);
    rt_interrupt_leave();
}

void EINT2_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(2);
    rt_interrupt_leave();
}

void EINT3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(3);
    rt_interrupt_leave();
}

void EINT4_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(4);
    rt_interrupt_leave();
}

void EINT9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(5);
    GPIO_EXTI_IRQHandler(6);
    GPIO_EXTI_IRQHandler(7);
    GPIO_EXTI_IRQHandler(8);
    GPIO_EXTI_IRQHandler(9);
    rt_interrupt_leave();
}

void EINT15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(10);
    GPIO_EXTI_IRQHandler(11);
    GPIO_EXTI_IRQHandler(12);
    GPIO_EXTI_IRQHandler(13);
    GPIO_EXTI_IRQHandler(14);
    GPIO_EXTI_IRQHandler(15);
    rt_interrupt_leave();
}
#endif

int rt_hw_pin_init(void)
{
#if defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1)
#ifdef GPIOA
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
#endif
#ifdef GPIOB
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
#endif
#ifdef GPIOC
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);
#endif
#ifdef GPIOD
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOD);
#endif
#ifdef GPIOE
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOE);
#endif
#ifdef GPIOF
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOF);
#endif
#ifdef GPIOG
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOG);
#endif
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);
#elif defined(SOC_SERIES_APM32F4)
#ifdef GPIOA
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
#endif
#ifdef GPIOB
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);
#endif
#ifdef GPIOC
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC);
#endif
#ifdef GPIOD
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOD);
#endif
#ifdef GPIOE
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOE);
#endif
#ifdef GPIOF
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOF);
#endif
#ifdef GPIOG
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOG);
#endif
#ifdef GPIOH
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOH);
#endif
#ifdef GPIOI
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOI);
#endif
#ifdef GPIOJ
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOJ);
#endif
#ifdef GPIOK
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOK);
#endif

#elif defined(SOC_SERIES_APM32F0)
#ifdef GPIOA
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOA);
#endif
#ifdef GPIOB
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOB);
#endif
#ifdef GPIOC
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOC);
#endif
#ifdef GPIOD
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOD);
#endif
#ifdef GPIOE
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOE);
#endif
#ifdef GPIOF
    RCM_EnableAHBPeriphClock(RCM_AHB_PERIPH_GPIOF);
#endif

#endif /* SOC_SERIES_APM32F0 */

    return rt_device_pin_register("pin", &apm32_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */

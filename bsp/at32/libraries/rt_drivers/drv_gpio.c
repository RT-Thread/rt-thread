/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2022-05-16     shelton       first version
 * 2023-01-31     shelton       add support f421/f425
 * 2023-04-08     shelton       add support f423
 */

#include "drv_common.h"
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no)               (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin)                   ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin)                     ((uint8_t)((pin) & 0xFu))

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F423)
#define PIN_ATPORTSOURCE(pin)           (scfg_port_source_type)((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_ATPINSOURCE(pin)            (scfg_pins_source_type)((uint8_t)((pin) & 0xFu))
#else
#define PIN_ATPORTSOURCE(pin)           (gpio_port_source_type)((uint8_t)(((pin) & 0xF0u) >> 4))
#define PIN_ATPINSOURCE(pin)            (gpio_pins_source_type)((uint8_t)((pin) & 0xFu))
#endif

#define PIN_ATPORT(pin)                 ((gpio_type *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))
#define PIN_ATPIN(pin)                  ((uint16_t)(1u << PIN_NO(pin)))

#if defined(GPIOZ)
    #define __AT32_PORT_MAX 12u
#elif defined(GPIOK)
    #define __AT32_PORT_MAX 11u
#elif defined(GPIOJ)
    #define __AT32_PORT_MAX 10u
#elif defined(GPIOI)
    #define __AT32_PORT_MAX 9u
#elif defined(GPIOH)
    #define __AT32_PORT_MAX 8u
#elif defined(GPIOG)
    #define __AT32_PORT_MAX 7u
#elif defined(GPIOF)
    #define __AT32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __AT32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __AT32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __AT32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __AT32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __AT32_PORT_MAX 1u
#else
    #define __AT32_PORT_MAX 0u
    #error Unsupported AT32 GPIO peripheral.
#endif

#define PIN_ATPORT_MAX __AT32_PORT_MAX

#if defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425)
static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PINS_0,  EXINT_LINE_0,  EXINT1_0_IRQn},
    {GPIO_PINS_1,  EXINT_LINE_1,  EXINT1_0_IRQn},
    {GPIO_PINS_2,  EXINT_LINE_2,  EXINT3_2_IRQn},
    {GPIO_PINS_3,  EXINT_LINE_3,  EXINT3_2_IRQn},
    {GPIO_PINS_4,  EXINT_LINE_4,  EXINT15_4_IRQn},
    {GPIO_PINS_5,  EXINT_LINE_5,  EXINT15_4_IRQn},
    {GPIO_PINS_6,  EXINT_LINE_6,  EXINT15_4_IRQn},
    {GPIO_PINS_7,  EXINT_LINE_7,  EXINT15_4_IRQn},
    {GPIO_PINS_8,  EXINT_LINE_8,  EXINT15_4_IRQn},
    {GPIO_PINS_9,  EXINT_LINE_9,  EXINT15_4_IRQn},
    {GPIO_PINS_10, EXINT_LINE_10, EXINT15_4_IRQn},
    {GPIO_PINS_11, EXINT_LINE_11, EXINT15_4_IRQn},
    {GPIO_PINS_12, EXINT_LINE_12, EXINT15_4_IRQn},
    {GPIO_PINS_13, EXINT_LINE_13, EXINT15_4_IRQn},
    {GPIO_PINS_14, EXINT_LINE_14, EXINT15_4_IRQn},
    {GPIO_PINS_15, EXINT_LINE_15, EXINT15_4_IRQn},
};
#else
static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PINS_0,  EXINT_LINE_0,  EXINT0_IRQn},
    {GPIO_PINS_1,  EXINT_LINE_1,  EXINT1_IRQn},
    {GPIO_PINS_2,  EXINT_LINE_2,  EXINT2_IRQn},
    {GPIO_PINS_3,  EXINT_LINE_3,  EXINT3_IRQn},
    {GPIO_PINS_4,  EXINT_LINE_4,  EXINT4_IRQn},
    {GPIO_PINS_5,  EXINT_LINE_5,  EXINT9_5_IRQn},
    {GPIO_PINS_6,  EXINT_LINE_6,  EXINT9_5_IRQn},
    {GPIO_PINS_7,  EXINT_LINE_7,  EXINT9_5_IRQn},
    {GPIO_PINS_8,  EXINT_LINE_8,  EXINT9_5_IRQn},
    {GPIO_PINS_9,  EXINT_LINE_9,  EXINT9_5_IRQn},
    {GPIO_PINS_10, EXINT_LINE_10, EXINT15_10_IRQn},
    {GPIO_PINS_11, EXINT_LINE_11, EXINT15_10_IRQn},
    {GPIO_PINS_12, EXINT_LINE_12, EXINT15_10_IRQn},
    {GPIO_PINS_13, EXINT_LINE_13, EXINT15_10_IRQn},
    {GPIO_PINS_14, EXINT_LINE_14, EXINT15_10_IRQn},
    {GPIO_PINS_15, EXINT_LINE_15, EXINT15_10_IRQn},
};
#endif

static struct rt_pin_irq_hdr pin_irq_handler_tab[] =
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

static rt_base_t at32_pin_get(const char *name)
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

static void at32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    gpio_type *gpio_port;

    uint16_t gpio_pin;
    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return;
    }
    gpio_bits_write(gpio_port, gpio_pin, (confirm_state)value);
}

static rt_int8_t at32_pin_read(rt_device_t dev, rt_base_t pin)
{
    gpio_type *gpio_port;
    uint16_t gpio_pin;
    int value;

    value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
        value = gpio_input_data_bit_read(gpio_port, gpio_pin);
    }
    return value;
}

static void at32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    gpio_init_type gpio_init_struct;
    gpio_type *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return;
    }

    /* configure gpio_init_struct */
    gpio_default_para_init(&gpio_init_struct);
    gpio_init_struct.gpio_pins = gpio_pin;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
        gpio_init_struct.gpio_pull = GPIO_PULL_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
        gpio_init_struct.gpio_out_type = GPIO_OUTPUT_OPEN_DRAIN;
    }

    gpio_init(gpio_port, &gpio_init_struct);
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_int32_t i;
    for (i = 0; i < 32; i++)
    {
        if (((rt_uint32_t)0x01 << i) == bit)
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

static rt_err_t at32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_pin = PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_handler_tab[irqindex].pin == pin &&
        pin_irq_handler_tab[irqindex].hdr == hdr &&
        pin_irq_handler_tab[irqindex].mode == mode &&
        pin_irq_handler_tab[irqindex].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_handler_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    pin_irq_handler_tab[irqindex].pin = pin;
    pin_irq_handler_tab[irqindex].hdr = hdr;
    pin_irq_handler_tab[irqindex].mode = mode;
    pin_irq_handler_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t at32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    uint16_t gpio_pin;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }
    irqindex = bit2bitno(gpio_pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_handler_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_handler_tab[irqindex].pin = -1;
    pin_irq_handler_tab[irqindex].hdr = RT_NULL;
    pin_irq_handler_tab[irqindex].mode = 0;
    pin_irq_handler_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t at32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t enabled)
{
    gpio_init_type gpio_init_struct;
    exint_init_type exint_init_struct;
    gpio_type *gpio_port;
    IRQn_Type irqn;
    uint16_t gpio_pin;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) < PIN_ATPORT_MAX)
    {
        gpio_port    =  PIN_ATPORT(pin);
        gpio_pin     =  PIN_ATPIN(pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(gpio_pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_handler_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        irqmap = &pin_irq_map[irqindex];

        /* configure gpio_init_struct */
        gpio_default_para_init(&gpio_init_struct);
        exint_default_para_init(&exint_init_struct);

        gpio_init_struct.gpio_pins = irqmap->pinbit;
        gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
        exint_init_struct.line_select = irqmap->pinbit;
        exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
        exint_init_struct.line_enable = TRUE;
        switch (pin_irq_handler_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
            break;
        case PIN_IRQ_MODE_FALLING:
            exint_init_struct.line_polarity = EXINT_TRIGGER_FALLING_EDGE;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
            break;
        }
        gpio_init(gpio_port, &gpio_init_struct);

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F423)
        scfg_exint_line_config(PIN_ATPORTSOURCE(pin), PIN_ATPINSOURCE(pin));
#else
        gpio_exint_line_config(PIN_ATPORTSOURCE(pin), PIN_ATPINSOURCE(pin));
#endif
        exint_init(&exint_init_struct);

        nvic_irq_enable(irqmap->irqno, 5, 0);
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(gpio_pin);
        if (irqmap == RT_NULL)
        {
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;


        if ((irqmap->pinbit >= GPIO_PINS_5) && (irqmap->pinbit <= GPIO_PINS_9))
        {
            if (!(pin_irq_enable_mask & (GPIO_PINS_5 | GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8 | GPIO_PINS_9)))
            {
                irqn = irqmap->irqno;
            }
        }
        else if ((irqmap->pinbit >= GPIO_PINS_10) && (irqmap->pinbit <= GPIO_PINS_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_PINS_10 | GPIO_PINS_11 | GPIO_PINS_12 | GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15)))
            {
                irqn = irqmap->irqno;
            }
        }
        else
        {
            irqn = irqmap->irqno;
        }
        nvic_irq_disable(irqn);
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

const static struct rt_pin_ops _at32_pin_ops =
{
    at32_pin_mode,
    at32_pin_write,
    at32_pin_read,
    at32_pin_attach_irq,
    at32_pin_dettach_irq,
    at32_pin_irq_enable,
    at32_pin_get,
};

rt_inline void pin_irq_handler(int irqno)
{
    exint_flag_clear(pin_irq_map[irqno].lineno);
    if (pin_irq_handler_tab[irqno].hdr)
    {
        pin_irq_handler_tab[irqno].hdr(pin_irq_handler_tab[irqno].args);
    }
}

void gpio_exint_handler(uint16_t GPIO_Pin)
{
    pin_irq_handler(bit2bitno(GPIO_Pin));
}

#if defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425)
void EXINT1_0_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != exint_flag_get(EXINT_LINE_0))
    {
        gpio_exint_handler(GPIO_PINS_0);
    }
    if (RESET != exint_flag_get(EXINT_LINE_1))
    {
        gpio_exint_handler(GPIO_PINS_1);
    }
    rt_interrupt_leave();
}

void EXINT3_2_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != exint_flag_get(EXINT_LINE_2))
    {
        gpio_exint_handler(GPIO_PINS_2);
    }
    if (RESET != exint_flag_get(EXINT_LINE_3))
    {
        gpio_exint_handler(GPIO_PINS_3);
    }
    rt_interrupt_leave();
}

void EXINT15_4_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != exint_flag_get(EXINT_LINE_4))
    {
        gpio_exint_handler(GPIO_PINS_4);
    }
    if (RESET != exint_flag_get(EXINT_LINE_5))
    {
        gpio_exint_handler(GPIO_PINS_5);
    }
    if (RESET != exint_flag_get(EXINT_LINE_6))
    {
        gpio_exint_handler(GPIO_PINS_6);
    }
    if (RESET != exint_flag_get(EXINT_LINE_7))
    {
        gpio_exint_handler(GPIO_PINS_7);
    }
    if (RESET != exint_flag_get(EXINT_LINE_8))
    {
        gpio_exint_handler(GPIO_PINS_8);
    }
    if (RESET != exint_flag_get(EXINT_LINE_9))
    {
        gpio_exint_handler(GPIO_PINS_9);
    }
    if (RESET != exint_flag_get(EXINT_LINE_10))
    {
        gpio_exint_handler(GPIO_PINS_10);
    }
    if (RESET != exint_flag_get(EXINT_LINE_11))
    {
        gpio_exint_handler(GPIO_PINS_11);
    }
    if (RESET != exint_flag_get(EXINT_LINE_12))
    {
        gpio_exint_handler(GPIO_PINS_12);
    }
    if (RESET != exint_flag_get(EXINT_LINE_13))
    {
        gpio_exint_handler(GPIO_PINS_13);
    }
    if (RESET != exint_flag_get(EXINT_LINE_14))
    {
        gpio_exint_handler(GPIO_PINS_14);
    }
    if (RESET != exint_flag_get(EXINT_LINE_15))
    {
        gpio_exint_handler(GPIO_PINS_15);
    }
    rt_interrupt_leave();
}
#else
void EXINT0_IRQHandler(void)
{
    rt_interrupt_enter();
    gpio_exint_handler(GPIO_PINS_0);
    rt_interrupt_leave();
}

void EXINT1_IRQHandler(void)
{
    rt_interrupt_enter();
    gpio_exint_handler(GPIO_PINS_1);
    rt_interrupt_leave();
}

void EXINT2_IRQHandler(void)
{
    rt_interrupt_enter();
    gpio_exint_handler(GPIO_PINS_2);
    rt_interrupt_leave();
}

void EXINT3_IRQHandler(void)
{
    rt_interrupt_enter();
    gpio_exint_handler(GPIO_PINS_3);
    rt_interrupt_leave();
}

void EXINT4_IRQHandler(void)
{
    rt_interrupt_enter();
    gpio_exint_handler(GPIO_PINS_4);
    rt_interrupt_leave();
}

void EXINT9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != exint_flag_get(EXINT_LINE_5))
    {
        gpio_exint_handler(GPIO_PINS_5);
    }
    if (RESET != exint_flag_get(EXINT_LINE_6))
    {
        gpio_exint_handler(GPIO_PINS_6);
    }
    if (RESET != exint_flag_get(EXINT_LINE_7))
    {
        gpio_exint_handler(GPIO_PINS_7);
    }
    if (RESET != exint_flag_get(EXINT_LINE_8))
    {
        gpio_exint_handler(GPIO_PINS_8);
    }
    if (RESET != exint_flag_get(EXINT_LINE_9))
    {
        gpio_exint_handler(GPIO_PINS_9);
    }
    rt_interrupt_leave();
}

void EXINT15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    if (RESET != exint_flag_get(EXINT_LINE_10))
    {
        gpio_exint_handler(GPIO_PINS_10);
    }
    if (RESET != exint_flag_get(EXINT_LINE_11))
    {
        gpio_exint_handler(GPIO_PINS_11);
    }
    if (RESET != exint_flag_get(EXINT_LINE_12))
    {
        gpio_exint_handler(GPIO_PINS_12);
    }
    if (RESET != exint_flag_get(EXINT_LINE_13))
    {
        gpio_exint_handler(GPIO_PINS_13);
    }
    if (RESET != exint_flag_get(EXINT_LINE_14))
    {
        gpio_exint_handler(GPIO_PINS_14);
    }
    if (RESET != exint_flag_get(EXINT_LINE_15))
    {
        gpio_exint_handler(GPIO_PINS_15);
    }
    rt_interrupt_leave();
}
#endif

int rt_hw_pin_init(void)
{

#ifdef GPIOA
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOB
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOC
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOD
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOE
    crm_periph_clock_enable(CRM_GPIOE_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOF
    crm_periph_clock_enable(CRM_GPIOF_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOG
    crm_periph_clock_enable(CRM_GPIOG_PERIPH_CLOCK, TRUE);
#endif
#ifdef GPIOH
    crm_periph_clock_enable(CRM_GPIOH_PERIPH_CLOCK, TRUE);
#endif

#if defined (SOC_SERIES_AT32F435) || defined (SOC_SERIES_AT32F437) || \
    defined (SOC_SERIES_AT32F421) || defined (SOC_SERIES_AT32F425) || \
    defined (SOC_SERIES_AT32F423)
    crm_periph_clock_enable(CRM_SCFG_PERIPH_CLOCK, TRUE);
#else
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
#endif

    return rt_device_pin_register("pin", &_at32_pin_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */

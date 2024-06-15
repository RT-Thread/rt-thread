/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-20     BruceOu           the first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include <rtconfig.h>

#ifdef RT_USING_PIN

#include "drv_gpio.h"

static const struct pin_index pins[] =
{
#ifdef GPIOA
    GD32_PIN(0,  A, 0),
    GD32_PIN(1,  A, 1),
    GD32_PIN(2,  A, 2),
    GD32_PIN(3,  A, 3),
    GD32_PIN(4,  A, 4),
    GD32_PIN(5,  A, 5),
    GD32_PIN(6,  A, 6),
    GD32_PIN(7,  A, 7),
    GD32_PIN(8,  A, 8),
    GD32_PIN(9,  A, 9),
    GD32_PIN(10, A, 10),
    GD32_PIN(11, A, 11),
    GD32_PIN(12, A, 12),
    GD32_PIN(13, A, 13),
    GD32_PIN(14, A, 14),
    GD32_PIN(15, A, 15),
#endif
#ifdef GPIOB
    GD32_PIN(16, B, 0),
    GD32_PIN(17, B, 1),
    GD32_PIN(18, B, 2),
    GD32_PIN(19, B, 3),
    GD32_PIN(20, B, 4),
    GD32_PIN(21, B, 5),
    GD32_PIN(22, B, 6),
    GD32_PIN(23, B, 7),
    GD32_PIN(24, B, 8),
    GD32_PIN(25, B, 9),
    GD32_PIN(26, B, 10),
    GD32_PIN(27, B, 11),
    GD32_PIN(28, B, 12),
    GD32_PIN(39, B, 13),
    GD32_PIN(30, B, 14),
    GD32_PIN(31, B, 15),
#endif
#ifdef GPIOC
    GD32_PIN(32, C, 0),
    GD32_PIN(33, C, 1),
    GD32_PIN(34, C, 2),
    GD32_PIN(35, C, 3),
    GD32_PIN(36, C, 4),
    GD32_PIN(37, C, 5),
    GD32_PIN(38, C, 6),
    GD32_PIN(39, C, 7),
    GD32_PIN(40, C, 8),
    GD32_PIN(41, C, 9),
    GD32_PIN(42, C, 10),
    GD32_PIN(43, C, 11),
    GD32_PIN(44, C, 12),
    GD32_PIN(45, C, 13),
    GD32_PIN(46, C, 14),
    GD32_PIN(47, C, 15),
#endif
#ifdef GPIOD
    GD32_PIN(48, D, 0),
    GD32_PIN(49, D, 1),
    GD32_PIN(50, D, 2),
    GD32_PIN(51, D, 3),
    GD32_PIN(52, D, 4),
    GD32_PIN(53, D, 5),
    GD32_PIN(54, D, 6),
    GD32_PIN(55, D, 7),
    GD32_PIN(56, D, 8),
    GD32_PIN(57, D, 9),
    GD32_PIN(58, D, 10),
    GD32_PIN(59, D, 11),
    GD32_PIN(60, D, 12),
    GD32_PIN(61, D, 13),
    GD32_PIN(62, D, 14),
    GD32_PIN(63, D, 15),
#endif
#ifdef GPIOE
    GD32_PIN(64, E, 0),
    GD32_PIN(65, E, 1),
    GD32_PIN(66, E, 2),
    GD32_PIN(67, E, 3),
    GD32_PIN(68, E, 4),
    GD32_PIN(69, E, 5),
    GD32_PIN(70, E, 6),
    GD32_PIN(71, E, 7),
    GD32_PIN(72, E, 8),
    GD32_PIN(73, E, 9),
    GD32_PIN(74, E, 10),
    GD32_PIN(75, E, 11),
    GD32_PIN(76, E, 12),
    GD32_PIN(77, E, 13),
    GD32_PIN(78, E, 14),
    GD32_PIN(79, E, 15),
#endif
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0,  EXTI0_IRQn},
    {GPIO_PIN_1,  EXTI1_IRQn},
    {GPIO_PIN_2,  EXTI2_IRQn},
    {GPIO_PIN_3,  EXTI3_IRQn},
    {GPIO_PIN_4,  EXTI4_IRQn},
    {GPIO_PIN_5,  EXTI5_9_IRQn},
    {GPIO_PIN_6,  EXTI5_9_IRQn},
    {GPIO_PIN_7,  EXTI5_9_IRQn},
    {GPIO_PIN_8,  EXTI5_9_IRQn},
    {GPIO_PIN_9,  EXTI5_9_IRQn},
    {GPIO_PIN_10, EXTI10_15_IRQn},
    {GPIO_PIN_11, EXTI10_15_IRQn},
    {GPIO_PIN_12, EXTI10_15_IRQn},
    {GPIO_PIN_13, EXTI10_15_IRQn},
    {GPIO_PIN_14, EXTI10_15_IRQn},
    {GPIO_PIN_15, EXTI10_15_IRQn},
};

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
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

/**
  * @brief  get pin
  * @param  pin
  * @retval None
  */
const struct pin_index *get_pin(rt_uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
        index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
}

/**
  * @brief  set pin mode
  * @param  dev, pin, mode
  * @retval None
  */
static void gd32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index = RT_NULL;
    rt_uint32_t pin_mode = 0;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* GPIO Periph clock enable */
    rcu_periph_clock_enable(index->clk);

    pin_mode = GPIO_MODE_OUT_PP;

    switch(mode)
    {
    case PIN_MODE_OUTPUT:
        /* output setting */
        pin_mode = GPIO_MODE_OUT_PP;
        break;
    case PIN_MODE_OUTPUT_OD:
        /* output setting: od. */
        pin_mode = GPIO_MODE_OUT_OD;
        break;
    case PIN_MODE_INPUT:
        /* input setting: not pull. */
        pin_mode = GPIO_MODE_IN_FLOATING;
        break;
    case PIN_MODE_INPUT_PULLUP:
        /* input setting: pull up. */
        pin_mode = GPIO_MODE_IPU;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        /* input setting: pull down. */
        pin_mode = GPIO_MODE_IPD;
        break;
    default:
            break;
    }

    gpio_init(index->gpio_periph, pin_mode, GPIO_OSPEED_50MHZ, index->pin);
}

/**
  * @brief  pin write
  * @param  dev, pin, valuie
  * @retval None
  */
static void gd32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index = RT_NULL;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    gpio_bit_write(index->gpio_periph, index->pin, (bit_status)value);
}

/**
  * @brief  pin read
  * @param  dev, pin
  * @retval None
  */
static rt_ssize_t gd32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_ssize_t value = PIN_LOW;
    const struct pin_index *index = RT_NULL;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }

    value = gpio_input_bit_get(index->gpio_periph, index->pin);
    return value;
}

/**
  * @brief  bit2bitno
  * @param  bit
  * @retval None
  */
rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    rt_uint8_t i;
    for (i = 0; i < 32; i++)
    {
        if ((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}

/**
  * @brief  pin write
  * @param  pinbit
  * @retval None
  */
rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint32_t pinbit)
{
    rt_int32_t map_index = bit2bitno(pinbit);
    if (map_index < 0 || map_index >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[map_index];
}

/**
  * @brief  pin irq attach
  * @param  device, pin, mode
  * @retval None
  */
static rt_err_t gd32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                              rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index = RT_NULL;
    rt_base_t level;
    rt_int32_t hdr_index = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }

    hdr_index = bit2bitno(index->pin);
    if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[hdr_index].pin == pin &&
        pin_irq_hdr_tab[hdr_index].hdr == hdr &&
        pin_irq_hdr_tab[hdr_index].mode == mode &&
        pin_irq_hdr_tab[hdr_index].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[hdr_index].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EFULL;
    }
    pin_irq_hdr_tab[hdr_index].pin = pin;
    pin_irq_hdr_tab[hdr_index].hdr = hdr;
    pin_irq_hdr_tab[hdr_index].mode = mode;
    pin_irq_hdr_tab[hdr_index].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
  * @brief  pin irq detach
  * @param  device, pin
  * @retval None
  */
static rt_err_t gd32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index = RT_NULL;
    rt_base_t level;
    rt_int32_t hdr_index = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }

    hdr_index = bit2bitno(index->pin);
    if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[hdr_index].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[hdr_index].pin = -1;
    pin_irq_hdr_tab[hdr_index].hdr = RT_NULL;
    pin_irq_hdr_tab[hdr_index].mode = 0;
    pin_irq_hdr_tab[hdr_index].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
  * @brief  pin irq enable
  * @param  device, pin, enabled
  * @retval None
  */
static rt_err_t gd32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t hdr_index = -1;
    exti_trig_type_enum trigger_mode;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        hdr_index = bit2bitno(index->pin);
        if (hdr_index < 0 || hdr_index >= ITEM_NUM(pin_irq_map))
        {
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[hdr_index].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_EINVAL;
        }

        irqmap = &pin_irq_map[hdr_index];

        switch (pin_irq_hdr_tab[hdr_index].mode)
        {
            case PIN_IRQ_MODE_RISING:
                trigger_mode = EXTI_TRIG_RISING;
                break;
            case PIN_IRQ_MODE_FALLING:
                trigger_mode = EXTI_TRIG_FALLING;
                break;
            case PIN_IRQ_MODE_RISING_FALLING:
                trigger_mode = EXTI_TRIG_BOTH;
                break;
            default:
                rt_hw_interrupt_enable(level);
                return -RT_EINVAL;
        }

        rcu_periph_clock_enable(RCU_AF);

        /* enable and set interrupt priority */
        eclic_irq_enable(irqmap->irqno, 5U, 0U);

        /* connect EXTI line to  GPIO pin */
        gpio_exti_source_select(index->port_src, index->pin_src);

        /* configure EXTI line */
        exti_init((exti_line_enum)(index->pin), EXTI_INTERRUPT, trigger_mode);
        exti_interrupt_flag_clear((exti_line_enum)(index->pin));

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_EINVAL;
        }
        eclic_irq_disable(irqmap->irqno);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

const static struct rt_pin_ops gd32_pin_ops =
{
    .pin_mode = gd32_pin_mode,
    .pin_write = gd32_pin_write,
    .pin_read = gd32_pin_read,
    .pin_attach_irq = gd32_pin_attach_irq,
    .pin_detach_irq= gd32_pin_detach_irq,
    .pin_irq_enable = gd32_pin_irq_enable,
    RT_NULL,
};

/**
  * @brief  pin write
  * @param  irqno
  * @retval None
  */
rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

/**
  * @brief  gd32 exit interrupt
  * @param  exti_line
  * @retval None
  */
void GD32_GPIO_EXTI_IRQHandler(rt_int8_t exti_line)
{
    if(RESET != exti_interrupt_flag_get((exti_line_enum)(1 << exti_line)))
    {
        pin_irq_hdr(exti_line);
        exti_interrupt_flag_clear((exti_line_enum)(1 << exti_line));
    }
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(4);
    rt_interrupt_leave();
}

void EXTI5_9_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(5);
    GD32_GPIO_EXTI_IRQHandler(6);
    GD32_GPIO_EXTI_IRQHandler(7);
    GD32_GPIO_EXTI_IRQHandler(8);
    GD32_GPIO_EXTI_IRQHandler(9);
    rt_interrupt_leave();
}

void EXTI10_15_IRQHandler(void)
{
    rt_interrupt_enter();
    GD32_GPIO_EXTI_IRQHandler(10);
    GD32_GPIO_EXTI_IRQHandler(11);
    GD32_GPIO_EXTI_IRQHandler(12);
    GD32_GPIO_EXTI_IRQHandler(13);
    GD32_GPIO_EXTI_IRQHandler(14);
    GD32_GPIO_EXTI_IRQHandler(15);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &gd32_pin_ops, RT_NULL);

    return result;
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif

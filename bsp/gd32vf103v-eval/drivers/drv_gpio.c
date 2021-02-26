/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-27     BalanceTWK        first version
 */

#include "drv_gpio.h"
#include <rthw.h>

#ifdef RT_USING_PIN

#define EXTI_(x)  BIT(x)

static const struct pin_index pins[] = 
{
#if defined(GPIOA)
    __GD32VF_PIN(0 ,  A, 0 ),
    __GD32VF_PIN(1 ,  A, 1 ),
    __GD32VF_PIN(2 ,  A, 2 ),
    __GD32VF_PIN(3 ,  A, 3 ),
    __GD32VF_PIN(4 ,  A, 4 ),
    __GD32VF_PIN(5 ,  A, 5 ),
    __GD32VF_PIN(6 ,  A, 6 ),
    __GD32VF_PIN(7 ,  A, 7 ),
    __GD32VF_PIN(8 ,  A, 8 ),
    __GD32VF_PIN(9 ,  A, 9 ),
    __GD32VF_PIN(10,  A, 10),
    __GD32VF_PIN(11,  A, 11),
    __GD32VF_PIN(12,  A, 12),
    __GD32VF_PIN(13,  A, 13),
    __GD32VF_PIN(14,  A, 14),
    __GD32VF_PIN(15,  A, 15),
#if defined(GPIOB)
    __GD32VF_PIN(16,  B, 0),
    __GD32VF_PIN(17,  B, 1),
    __GD32VF_PIN(18,  B, 2),
    __GD32VF_PIN(19,  B, 3),
    __GD32VF_PIN(20,  B, 4),
    __GD32VF_PIN(21,  B, 5),
    __GD32VF_PIN(22,  B, 6),
    __GD32VF_PIN(23,  B, 7),
    __GD32VF_PIN(24,  B, 8),
    __GD32VF_PIN(25,  B, 9),
    __GD32VF_PIN(26,  B, 10),
    __GD32VF_PIN(27,  B, 11),
    __GD32VF_PIN(28,  B, 12),
    __GD32VF_PIN(29,  B, 13),
    __GD32VF_PIN(30,  B, 14),
    __GD32VF_PIN(31,  B, 15),
#if defined(GPIOC)
    __GD32VF_PIN(32,  C, 0),
    __GD32VF_PIN(33,  C, 1),
    __GD32VF_PIN(34,  C, 2),
    __GD32VF_PIN(35,  C, 3),
    __GD32VF_PIN(36,  C, 4),
    __GD32VF_PIN(37,  C, 5),
    __GD32VF_PIN(38,  C, 6),
    __GD32VF_PIN(39,  C, 7),
    __GD32VF_PIN(40,  C, 8),
    __GD32VF_PIN(41,  C, 9),
    __GD32VF_PIN(42,  C, 10),
    __GD32VF_PIN(43,  C, 11),
    __GD32VF_PIN(44,  C, 12),
    __GD32VF_PIN(45,  C, 13),
    __GD32VF_PIN(46,  C, 14),
    __GD32VF_PIN(47,  C, 15),
#if defined(GPIOD)
    __GD32VF_PIN(48,  D, 0),
    __GD32VF_PIN(49,  D, 1),
    __GD32VF_PIN(50,  D, 2),
    __GD32VF_PIN(51,  D, 3),
    __GD32VF_PIN(52,  D, 4),
    __GD32VF_PIN(53,  D, 5),
    __GD32VF_PIN(54,  D, 6),
    __GD32VF_PIN(55,  D, 7),
    __GD32VF_PIN(56,  D, 8),
    __GD32VF_PIN(57,  D, 9),
    __GD32VF_PIN(58,  D, 10),
    __GD32VF_PIN(59,  D, 11),
    __GD32VF_PIN(60,  D, 12),
    __GD32VF_PIN(61,  D, 13),
    __GD32VF_PIN(62,  D, 14),
    __GD32VF_PIN(63,  D, 15),
#if defined(GPIOE)
    __GD32VF_PIN(64,  E, 0),
    __GD32VF_PIN(65,  E, 1),
    __GD32VF_PIN(66,  E, 2),
    __GD32VF_PIN(67,  E, 3),
    __GD32VF_PIN(68,  E, 4),
    __GD32VF_PIN(69,  E, 5),
    __GD32VF_PIN(70,  E, 6),
    __GD32VF_PIN(71,  E, 7),
    __GD32VF_PIN(72,  E, 8),
    __GD32VF_PIN(73,  E, 9),
    __GD32VF_PIN(74,  E, 10),
    __GD32VF_PIN(75,  E, 11),
    __GD32VF_PIN(76,  E, 12),
    __GD32VF_PIN(77,  E, 13),
    __GD32VF_PIN(78,  E, 14),
    __GD32VF_PIN(79,  E, 15),
#endif /* defined(GPIOE) */
#endif /* defined(GPIOD) */
#endif /* defined(GPIOC) */
#endif /* defined(GPIOB) */
#endif /* defined(GPIOA) */
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
static uint32_t pin_irq_enable_mask=0;

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
static const struct pin_index *get_pin(uint8_t pin)
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
};

static void gd32vf_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    gpio_bit_write(index->gpio_periph, index->pin, (bit_status)value);
}

static int gd32vf_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return PIN_LOW;
    }

    value = gpio_input_bit_get(index->gpio_periph, index->pin);
    return value;
}

static void gd32vf_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpio_init(index->gpio_periph, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, index->pin);
        gpio_bit_reset(index->gpio_periph, index->pin);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpio_init(index->gpio_periph, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, index->pin);
        gpio_bit_reset(index->gpio_periph, index->pin);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpio_init(index->gpio_periph, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, index->pin);
        gpio_bit_reset(index->gpio_periph, index->pin);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpio_init(index->gpio_periph, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, index->pin);
        gpio_bit_reset(index->gpio_periph, index->pin);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpio_init(index->gpio_periph, GPIO_MODE_OUT_OD, GPIO_OSPEED_50MHZ, index->pin);
        gpio_bit_reset(index->gpio_periph, index->pin);
    }
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

static rt_err_t gd32vf_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                     rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
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
        return RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t gd32vf_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
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

static rt_err_t gd32vf_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

        /* configure pin as input */
    gpio_init(index->gpio_periph, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, index->pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
        if (irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
        {
            return RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
        }

        irqmap = &pin_irq_map[irqindex];

        /* enable and set EXTI interrupt to the lowest priority */
        eclic_irq_enable(irqmap->irqno, 1, 1);
        gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA, GPIO_PIN_SOURCE_0);
        /* Configure GPIO_InitStructure */
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            exti_init(EXTI_(irqindex), EXTI_INTERRUPT, EXTI_TRIG_RISING);
            break;
        case PIN_IRQ_MODE_FALLING:
            exti_init(EXTI_(irqindex), EXTI_INTERRUPT, EXTI_TRIG_FALLING);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            exti_init(EXTI_(irqindex), EXTI_INTERRUPT, EXTI_TRIG_BOTH);
            break;
        }

        pin_irq_enable_mask |= irqmap->pinbit;

        exti_interrupt_flag_clear(EXTI_(index->pin));

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        gpio_bit_reset(index->gpio_periph, index->pin);

        pin_irq_enable_mask &= ~irqmap->pinbit;
 
        eclic_irq_disable(irqmap->irqno);
        exti_interrupt_flag_clear(EXTI_(index->pin));
         
        rt_hw_interrupt_enable(level);  
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _gd32vf_pin_ops =
{
    gd32vf_pin_mode,
    gd32vf_pin_write,
    gd32vf_pin_read,
    gd32vf_pin_attach_irq,
    gd32vf_pin_dettach_irq,
    gd32vf_pin_irq_enable,
    RT_NULL,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

/* IRQHandler start */
void EXTI0_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_0)
    {
        exti_interrupt_flag_clear(EXTI_0);
        pin_irq_hdr(bit2bitno(GPIO_PIN_0));
    }
}
void EXTI1_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_1)
    {
        exti_interrupt_flag_clear(EXTI_1);
        pin_irq_hdr(bit2bitno(GPIO_PIN_1));
    }
}
void EXTI2_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_2)
    {
        exti_interrupt_flag_clear(EXTI_2);
        pin_irq_hdr(bit2bitno(GPIO_PIN_2));
    }
}
void EXTI3_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_3)
    {
        exti_interrupt_flag_clear(EXTI_3);
        pin_irq_hdr(bit2bitno(GPIO_PIN_3));
    }
}
void EXTI4_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_4)
    {
        exti_interrupt_flag_clear(EXTI_4);
        pin_irq_hdr(bit2bitno(GPIO_PIN_4));
    }
}
void EXTI5_9_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_5)
    {
        exti_interrupt_flag_clear(EXTI_5);
        pin_irq_hdr(bit2bitno(GPIO_PIN_5));
    }

    if(EXTI_PD & (uint32_t) EXTI_6)
    {
        exti_interrupt_flag_clear(EXTI_6);
        pin_irq_hdr(bit2bitno(GPIO_PIN_6));
    }

    if(EXTI_PD & (uint32_t) EXTI_7)
    {
        exti_interrupt_flag_clear(EXTI_7);
        pin_irq_hdr(bit2bitno(GPIO_PIN_7));
    }

    if(EXTI_PD & (uint32_t) EXTI_8)
    {
        exti_interrupt_flag_clear(EXTI_8);
        pin_irq_hdr(bit2bitno(GPIO_PIN_8));
    }

    if(EXTI_PD & (uint32_t) EXTI_9)
    {
        exti_interrupt_flag_clear(EXTI_9);
        pin_irq_hdr(bit2bitno(GPIO_PIN_9));
    }
}
void EXTI10_15_IRQHandler(void)
{
    if(EXTI_PD & (uint32_t) EXTI_10)
    {
        exti_interrupt_flag_clear(EXTI_10);
        pin_irq_hdr(bit2bitno(GPIO_PIN_10));
    }

    if(EXTI_PD & (uint32_t) EXTI_11)
    {
        exti_interrupt_flag_clear(EXTI_11);
        pin_irq_hdr(bit2bitno(GPIO_PIN_11));
    }

    if(EXTI_PD & (uint32_t) EXTI_12)
    {
        exti_interrupt_flag_clear(EXTI_12);
        pin_irq_hdr(bit2bitno(GPIO_PIN_12));
    }

    if(EXTI_PD & (uint32_t) EXTI_13)
    {
        exti_interrupt_flag_clear(EXTI_13);
        pin_irq_hdr(bit2bitno(GPIO_PIN_13));
    }

    if(EXTI_PD & (uint32_t) EXTI_14)
    {
        exti_interrupt_flag_clear(EXTI_14);
        pin_irq_hdr(bit2bitno(GPIO_PIN_14));
    }

    if(EXTI_PD & (uint32_t) EXTI_15)
    {
        exti_interrupt_flag_clear(EXTI_15);
        pin_irq_hdr(bit2bitno(GPIO_PIN_15));
    }
}
/* IRQHandler end */

int rt_hw_pin_init(void)
{
    /* enable the global interrupt */
    eclic_global_interrupt_enable();
    eclic_priority_group_set(ECLIC_PRIGROUP_LEVEL3_PRIO1);

    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);

    rcu_periph_clock_enable(RCU_AF);
    return rt_device_pin_register("pin", &_gd32vf_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */

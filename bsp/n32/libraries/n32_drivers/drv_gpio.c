/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "drv_gpio.h"

#ifdef RT_USING_PIN

static const struct pin_index pins[] =
{
#if defined(GPIOA)
    __N32_PIN(0 ,  GPIOA, GPIO_PIN_0 ),
    __N32_PIN(1 ,  GPIOA, GPIO_PIN_1 ),
    __N32_PIN(2 ,  GPIOA, GPIO_PIN_2 ),
    __N32_PIN(3 ,  GPIOA, GPIO_PIN_3 ),
    __N32_PIN(4 ,  GPIOA, GPIO_PIN_4 ),
    __N32_PIN(5 ,  GPIOA, GPIO_PIN_5 ),
    __N32_PIN(6 ,  GPIOA, GPIO_PIN_6 ),
    __N32_PIN(7 ,  GPIOA, GPIO_PIN_7 ),
    __N32_PIN(8 ,  GPIOA, GPIO_PIN_8 ),
    __N32_PIN(9 ,  GPIOA, GPIO_PIN_9 ),
    __N32_PIN(10,  GPIOA, GPIO_PIN_10),
    __N32_PIN(11,  GPIOA, GPIO_PIN_11),
    __N32_PIN(12,  GPIOA, GPIO_PIN_12),
    __N32_PIN(13,  GPIOA, GPIO_PIN_13),
    __N32_PIN(14,  GPIOA, GPIO_PIN_14),
    __N32_PIN(15,  GPIOA, GPIO_PIN_15),
#if defined(GPIOB)
    __N32_PIN(16,  GPIOB, GPIO_PIN_0),
    __N32_PIN(17,  GPIOB, GPIO_PIN_1),
    __N32_PIN(18,  GPIOB, GPIO_PIN_2),
    __N32_PIN(19,  GPIOB, GPIO_PIN_3),
    __N32_PIN(20,  GPIOB, GPIO_PIN_4),
    __N32_PIN(21,  GPIOB, GPIO_PIN_5),
    __N32_PIN(22,  GPIOB, GPIO_PIN_6),
    __N32_PIN(23,  GPIOB, GPIO_PIN_7),
    __N32_PIN(24,  GPIOB, GPIO_PIN_8),
    __N32_PIN(25,  GPIOB, GPIO_PIN_9),
    __N32_PIN(26,  GPIOB, GPIO_PIN_10),
    __N32_PIN(27,  GPIOB, GPIO_PIN_11),
    __N32_PIN(28,  GPIOB, GPIO_PIN_12),
    __N32_PIN(29,  GPIOB, GPIO_PIN_13),
    __N32_PIN(30,  GPIOB, GPIO_PIN_14),
    __N32_PIN(31,  GPIOB, GPIO_PIN_15),
#if defined(GPIOC)
    __N32_PIN(32,  GPIOC, GPIO_PIN_0),
    __N32_PIN(33,  GPIOC, GPIO_PIN_1),
    __N32_PIN(34,  GPIOC, GPIO_PIN_2),
    __N32_PIN(35,  GPIOC, GPIO_PIN_3),
    __N32_PIN(36,  GPIOC, GPIO_PIN_4),
    __N32_PIN(37,  GPIOC, GPIO_PIN_5),
    __N32_PIN(38,  GPIOC, GPIO_PIN_6),
    __N32_PIN(39,  GPIOC, GPIO_PIN_7),
    __N32_PIN(40,  GPIOC, GPIO_PIN_8),
    __N32_PIN(41,  GPIOC, GPIO_PIN_9),
    __N32_PIN(42,  GPIOC, GPIO_PIN_10),
    __N32_PIN(43,  GPIOC, GPIO_PIN_11),
    __N32_PIN(44,  GPIOC, GPIO_PIN_12),
    __N32_PIN(45,  GPIOC, GPIO_PIN_13),
    __N32_PIN(46,  GPIOC, GPIO_PIN_14),
    __N32_PIN(47,  GPIOC, GPIO_PIN_15),
#if defined(GPIOD)
    __N32_PIN(48,  GPIOD, GPIO_PIN_0),
    __N32_PIN(49,  GPIOD, GPIO_PIN_1),
    __N32_PIN(50,  GPIOD, GPIO_PIN_2),
    __N32_PIN(51,  GPIOD, GPIO_PIN_3),
    __N32_PIN(52,  GPIOD, GPIO_PIN_4),
    __N32_PIN(53,  GPIOD, GPIO_PIN_5),
    __N32_PIN(54,  GPIOD, GPIO_PIN_6),
    __N32_PIN(55,  GPIOD, GPIO_PIN_7),
    __N32_PIN(56,  GPIOD, GPIO_PIN_8),
    __N32_PIN(57,  GPIOD, GPIO_PIN_9),
    __N32_PIN(58,  GPIOD, GPIO_PIN_10),
    __N32_PIN(59,  GPIOD, GPIO_PIN_11),
    __N32_PIN(60,  GPIOD, GPIO_PIN_12),
    __N32_PIN(61,  GPIOD, GPIO_PIN_13),
    __N32_PIN(62,  GPIOD, GPIO_PIN_14),
    __N32_PIN(63,  GPIOD, GPIO_PIN_15),
#if defined(GPIOE)
    __N32_PIN(64,  GPIOE, GPIO_PIN_0),
    __N32_PIN(65,  GPIOE, GPIO_PIN_1),
    __N32_PIN(66,  GPIOE, GPIO_PIN_2),
    __N32_PIN(67,  GPIOE, GPIO_PIN_3),
    __N32_PIN(68,  GPIOE, GPIO_PIN_4),
    __N32_PIN(69,  GPIOE, GPIO_PIN_5),
    __N32_PIN(70,  GPIOE, GPIO_PIN_6),
    __N32_PIN(71,  GPIOE, GPIO_PIN_7),
    __N32_PIN(72,  GPIOE, GPIO_PIN_8),
    __N32_PIN(73,  GPIOE, GPIO_PIN_9),
    __N32_PIN(74,  GPIOE, GPIO_PIN_10),
    __N32_PIN(75,  GPIOE, GPIO_PIN_11),
    __N32_PIN(76,  GPIOE, GPIO_PIN_12),
    __N32_PIN(77,  GPIOE, GPIO_PIN_13),
    __N32_PIN(78,  GPIOE, GPIO_PIN_14),
    __N32_PIN(79,  GPIOE, GPIO_PIN_15),
#if defined(GPIOF)
    __N32_PIN(80,  GPIOF, GPIO_PIN_0),
    __N32_PIN(81,  GPIOF, GPIO_PIN_1),
    __N32_PIN(82,  GPIOF, GPIO_PIN_2),
    __N32_PIN(83,  GPIOF, GPIO_PIN_3),
    __N32_PIN(84,  GPIOF, GPIO_PIN_4),
    __N32_PIN(85,  GPIOF, GPIO_PIN_5),
    __N32_PIN(86,  GPIOF, GPIO_PIN_6),
    __N32_PIN(87,  GPIOF, GPIO_PIN_7),
    __N32_PIN(88,  GPIOF, GPIO_PIN_8),
    __N32_PIN(89,  GPIOF, GPIO_PIN_9),
    __N32_PIN(90,  GPIOF, GPIO_PIN_10),
    __N32_PIN(91,  GPIOF, GPIO_PIN_11),
    __N32_PIN(92,  GPIOF, GPIO_PIN_12),
    __N32_PIN(93,  GPIOF, GPIO_PIN_13),
    __N32_PIN(94,  GPIOF, GPIO_PIN_14),
    __N32_PIN(95,  GPIOF, GPIO_PIN_15),
#if defined(GPIOG)
    __N32_PIN(96,  GPIOG, GPIO_PIN_0),
    __N32_PIN(97,  GPIOG, GPIO_PIN_1),
    __N32_PIN(98,  GPIOG, GPIO_PIN_2),
    __N32_PIN(99,  GPIOG, GPIO_PIN_3),
    __N32_PIN(100, GPIOG, GPIO_PIN_4),
    __N32_PIN(101, GPIOG, GPIO_PIN_5),
    __N32_PIN(102, GPIOG, GPIO_PIN_6),
    __N32_PIN(103, GPIOG, GPIO_PIN_7),
    __N32_PIN(104, GPIOG, GPIO_PIN_8),
    __N32_PIN(105, GPIOG, GPIO_PIN_9),
    __N32_PIN(106, GPIOG, GPIO_PIN_10),
    __N32_PIN(107, GPIOG, GPIO_PIN_11),
    __N32_PIN(108, GPIOG, GPIO_PIN_12),
    __N32_PIN(109, GPIOG, GPIO_PIN_13),
    __N32_PIN(110, GPIOG, GPIO_PIN_14),
    __N32_PIN(111, GPIOG, GPIO_PIN_15),

#endif /* defined(GPIOG) */
#endif /* defined(GPIOF) */
#endif /* defined(GPIOE) */
#endif /* defined(GPIOD) */
#endif /* defined(GPIOC) */
#endif /* defined(GPIOB) */
#endif /* defined(GPIOA) */
};

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn},
    {GPIO_PIN_1, EXTI1_IRQn},
    {GPIO_PIN_2, EXTI2_IRQn},
    {GPIO_PIN_3, EXTI3_IRQn},
    {GPIO_PIN_4, EXTI4_IRQn},
    {GPIO_PIN_5, EXTI9_5_IRQn},
    {GPIO_PIN_6, EXTI9_5_IRQn},
    {GPIO_PIN_7, EXTI9_5_IRQn},
    {GPIO_PIN_8, EXTI9_5_IRQn},
    {GPIO_PIN_9, EXTI9_5_IRQn},
    {GPIO_PIN_10, EXTI15_10_IRQn},
    {GPIO_PIN_11, EXTI15_10_IRQn},
    {GPIO_PIN_12, EXTI15_10_IRQn},
    {GPIO_PIN_13, EXTI15_10_IRQn},
    {GPIO_PIN_14, EXTI15_10_IRQn},
    {GPIO_PIN_15, EXTI15_10_IRQn},
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

static void n32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    GPIO_WriteBit(index->gpio, index->pin, (Bit_OperateType)value);
}

static rt_int8_t n32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_int8_t value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    value = GPIO_ReadInputDataBit(index->gpio, index->pin);

    return value;
}

static void n32_gpio_clock_enable(GPIO_Module* GPIOx)
{
    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOE, ENABLE);
    }
#endif
#ifdef SOC_N32G45X
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOF, ENABLE);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOG, ENABLE);
    }
#endif /* SOC_N32G45X */
    else
    {
        rt_kprintf("The GPIO port number is incorrect. No GPIO port exists\n");
    }
}

static void n32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    const struct pin_index *index;
    GPIO_InitType GPIO_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Enable the GPIO Clock */
    n32_gpio_clock_enable(index->gpio);

    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.Pin = index->pin;

#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#endif

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
        GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
#endif
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
        GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
#endif
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
        GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Down;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
#endif
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    GPIO_InitPeripheral(index->gpio, &GPIO_InitStructure);
#elif defined(SOC_N32L43X) || defined(SOC_N32L40X) || defined(SOC_N32G43X)
    GPIO_InitPeripheral(index->gpio, &GPIO_InitStructure);
#endif

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

rt_inline rt_int32_t port2portsource(GPIO_Module* module)
{
    if (module == GPIOA)
    {
        return GPIOA_PORT_SOURCE;
    }
    else if (module == GPIOB)
    {
        return GPIOB_PORT_SOURCE;
    }
    else if (module == GPIOC)
    {
        return GPIOC_PORT_SOURCE;
    }
    else if (module == GPIOD)
    {
        return GPIOD_PORT_SOURCE;
    }
#if defined(SOC_N32G45X) || defined(SOC_N32WB452) || defined(SOC_N32G4FR)
    else if (module == GPIOE)
    {
        return GPIOE_PORT_SOURCE;
    }
#endif
#ifdef SOC_N32G45X
    else if (module == GPIOF)
    {
        return GPIOF_PORT_SOURCE;
    }
    else if (module == GPIOG)
    {
        return GPIOG_PORT_SOURCE;
    }
#endif /* SOC_N32G45X */
    else
    {
        rt_kprintf("The GPIO port number is incorrect. No GPIO port exists\n");
        return -RT_ERROR;
    }
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

static rt_err_t n32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
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

static rt_err_t n32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
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

static rt_err_t n32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    EXTI_InitType EXTI_InitStructure;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(index->pin);
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

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
            case PIN_IRQ_MODE_RISING:
                EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
                break;

            case PIN_IRQ_MODE_FALLING:
                EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
                break;

            case PIN_IRQ_MODE_RISING_FALLING:
                EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
                break;

            default:
                return -RT_ERROR;
        }

        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
        /* configure EXTI line */
        GPIO_ConfigEXTILine(port2portsource(index->gpio), irqindex);

        /*Configure key EXTI line*/
        EXTI_InitStructure.EXTI_Line    = index->pin;
        EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitPeripheral(&EXTI_InitStructure);

        EXTI_ClrITPendBit(index->pin);

                /* enable and set interrupt priority */
        NVIC_SetPriority(irqmap->irqno, 5);
        NVIC_EnableIRQ(irqmap->irqno);

        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        pin_irq_enable_mask &= ~irqmap->pinbit;
        if (( irqmap->pinbit>=GPIO_PIN_5 )&&( irqmap->pinbit<=GPIO_PIN_9 ))
        {
            if (!(pin_irq_enable_mask&(GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if (( irqmap->pinbit>=GPIO_PIN_10 )&&( irqmap->pinbit<=GPIO_PIN_15 ))
        {
            if (!(pin_irq_enable_mask&(GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQ(irqmap->irqno);
        }

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _n32_pin_ops =
{
    n32_pin_mode,
    n32_pin_write,
    n32_pin_read,
    n32_pin_attach_irq,
    n32_pin_dettach_irq,
    n32_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_n32_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void N32_GPIO_EXTI_IRQHandler(rt_int8_t exti_line)
{
    if (RESET != EXTI_GetITStatus(1 << exti_line))
    {
        pin_irq_hdr(exti_line);
        EXTI_ClrITPendBit(1 << exti_line);
    }
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(0);
    rt_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(1);
    rt_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(2);
    rt_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(3);
    rt_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(4);
    rt_interrupt_leave();
}
void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(5);
    N32_GPIO_EXTI_IRQHandler(6);
    N32_GPIO_EXTI_IRQHandler(7);
    N32_GPIO_EXTI_IRQHandler(8);
    N32_GPIO_EXTI_IRQHandler(9);
    rt_interrupt_leave();
}
void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_IRQHandler(10);
    N32_GPIO_EXTI_IRQHandler(11);
    N32_GPIO_EXTI_IRQHandler(12);
    N32_GPIO_EXTI_IRQHandler(13);
    N32_GPIO_EXTI_IRQHandler(14);
    N32_GPIO_EXTI_IRQHandler(15);
    rt_interrupt_leave();
}

#endif /* RT_USING_PIN */

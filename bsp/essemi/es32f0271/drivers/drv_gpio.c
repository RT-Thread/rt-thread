/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define __ES32F0_PIN(index, gpio, gpio_index) {index, GPIO##gpio, gpio_index}
#define __ES32F0_PIN_DEFAULT {-1, 0, 0}

/* ES32F0 GPIO driver */
struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(2, C, 13),
    __ES32F0_PIN(3, C, 14),
    __ES32F0_PIN(4, C, 15),
    __ES32F0_PIN(5, D, 14),
    __ES32F0_PIN(6, D, 15),
    __ES32F0_PIN(7, D, 13),
    __ES32F0_PIN(8, C, 0),
    __ES32F0_PIN(9, C, 1),
    __ES32F0_PIN(10, C, 2),
    __ES32F0_PIN(11, C, 3),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(14, A, 0),
    __ES32F0_PIN(15, A, 1),
    __ES32F0_PIN(16, A, 2),
    __ES32F0_PIN(17, A, 3),
    __ES32F0_PIN(18, D, 0),
    __ES32F0_PIN(19, D, 1),
    __ES32F0_PIN(20, A, 4),
    __ES32F0_PIN(21, A, 5),
    __ES32F0_PIN(22, A, 6),
    __ES32F0_PIN(23, A, 7),
    __ES32F0_PIN(24, C, 4),
    __ES32F0_PIN(25, C, 5),
    __ES32F0_PIN(26, B, 0),
    __ES32F0_PIN(27, B, 1),
    __ES32F0_PIN(28, B, 2),
    __ES32F0_PIN(29, B, 10),
    __ES32F0_PIN(30, B, 11),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(33, B, 12),
    __ES32F0_PIN(34, B, 13),
    __ES32F0_PIN(35, B, 14),
    __ES32F0_PIN(36, B, 15),
    __ES32F0_PIN(37, C, 6),
    __ES32F0_PIN(38, C, 7),
    __ES32F0_PIN(39, C, 8),
    __ES32F0_PIN(40, C, 9),
    __ES32F0_PIN(41, A, 8),
    __ES32F0_PIN(42, A, 9),
    __ES32F0_PIN(43, A, 10),
    __ES32F0_PIN(44, A, 11),
    __ES32F0_PIN(45, A, 12),
    __ES32F0_PIN(46, A, 13),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN(49, A, 14),
    __ES32F0_PIN(50, A, 15),
    __ES32F0_PIN(51, C, 10),
    __ES32F0_PIN(52, C, 11),
    __ES32F0_PIN(53, C, 12),
    __ES32F0_PIN(54, D, 2),
    __ES32F0_PIN(55, B, 3),
    __ES32F0_PIN(56, B, 4),
    __ES32F0_PIN(57, B, 5),
    __ES32F0_PIN(58, B, 6),
    __ES32F0_PIN(59, B, 7),
    __ES32F0_PIN(60, D, 3),
    __ES32F0_PIN(61, B, 8),
    __ES32F0_PIN(62, B, 9),
    __ES32F0_PIN_DEFAULT,
    __ES32F0_PIN_DEFAULT,
};

struct pin_irq_map
{
    rt_uint16_t pinbit;
    IRQn_Type irqno;
};
static const struct pin_irq_map pin_irq_map[] =
{
    {0, EXTI_0to1_IRQn},
    {1, EXTI_0to1_IRQn},
    {2, EXTI_2to3_IRQn},
    {3, EXTI_2to3_IRQn},
    {4, EXTI_4to15_IRQn},
    {5, EXTI_4to15_IRQn},
    {6, EXTI_4to15_IRQn},
    {7, EXTI_4to15_IRQn},
    {8, EXTI_4to15_IRQn},
    {9, EXTI_4to15_IRQn},
    {10, EXTI_4to15_IRQn},
    {11, EXTI_4to15_IRQn},
    {12, EXTI_4to15_IRQn},
    {13, EXTI_4to15_IRQn},
    {14, EXTI_4to15_IRQn},
    {15, EXTI_4to15_IRQn},
};

struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
    { -1, 0, RT_NULL, RT_NULL},
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
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

void es32f0_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Write GPIO */
    if (value == 0)
        SET_BIT(index->gpio->BSBR, 0x1<<(index->pin+16));
    else
        SET_BIT(index->gpio->BSBR, 0x1<<index->pin);
}

int es32f0_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;
    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    /* Read the GPIO value with the spcified index */
    value = (index->gpio->IDATA & (0x1<<index->pin)) != 0;

    return value;
}

void es32f0_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_TypeDef *gpiox;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Get the IO port */
    gpiox = index->gpio;

    /* Config GPIO */
    switch(mode)
    {
        case PIN_MODE_OUTPUT:
        {
            /* pushpull & output & 16mA */
            MODIFY_REG(gpiox->MOD, (0x3<<(index->pin*2)), (0x1<<(index->pin*2)));
            CLEAR_BIT(gpiox->OT, (0x1<<index->pin));
            CLEAR_BIT(gpiox->DS, (0x1<<index->pin));
            break;
        }
        case PIN_MODE_OUTPUT_OD:
        {
            /* opendrain & output & 16mA */
            MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x1<<index->pin));
            SET_BIT(gpiox->OT, (0x1<<index->pin));
            CLEAR_BIT(gpiox->DS, (0x1<<index->pin));
            break;
        }
        case PIN_MODE_INPUT:
        {
            /* input & no pull & CMOS & filter */
            MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x0<<index->pin));
            MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x0<<index->pin));
            SET_BIT(gpiox->IST, (0x1<<index->pin));
            SET_BIT(gpiox->FIR, (0x1<<index->pin));
            break;
        }
        case PIN_MODE_INPUT_PULLUP:
        {
            /* input & pull up & CMOS & filter */
            MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x0<<index->pin));
            MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x1<<index->pin));
            SET_BIT(gpiox->IST, (0x1<<index->pin));
            SET_BIT(gpiox->FIR, (0x1<<index->pin));
            break;
        }
        case PIN_MODE_INPUT_PULLDOWN:
        {
            /* input & pull down & CMOS & filter */
            MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x0<<index->pin));
            MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x2<<index->pin));
            SET_BIT(gpiox->IST, (0x1<<index->pin));
            SET_BIT(gpiox->FIR, (0x1<<index->pin));
            break;
        }
        default:
        {
            /* output */
            MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x1<<index->pin));
        }
    }
}

rt_inline const struct pin_irq_map *get_pin_irq_map(rt_uint16_t gpio_pin)
{
    rt_int32_t mapindex = gpio_pin & 0x00FF;
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

rt_err_t es32f0_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                               rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    /* pin no. convert to dec no. */
    for (irqindex = 0; irqindex < 16; irqindex++)
    {
        if ((0x01 << irqindex) == index->pin)
        {
            break;
        }
    }
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

rt_err_t es32f0_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = index->pin & 0x00FF;
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

rt_err_t es32f0_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                               rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct pin_irq_map *irqmap;
    GPIO_TypeDef *gpiox;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

    /* Get the IO port */
    gpiox = index->gpio;

    if (enabled == PIN_IRQ_ENABLE)
    {
        /* pin no. convert to dec no. */
        for (irqindex = 0; irqindex < 16; irqindex++)
        {
            if ((0x01 << irqindex) == index->pin)
            {
                break;
            }
        }
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

        /* Config EXTI */
        MODIFY_REG(gpiox->MOD, (0x3<<index->pin), (0x0<<index->pin));
        SET_BIT(gpiox->FIR, index->pin);
        SET_BIT(gpiox->IST, index->pin);
        MODIFY_REG(((uint32_t *)(&EXTI->ICFG1))[index->pin/8],
                    0xF<<(index->pin%8),
                    (((uint32_t)(index->gpio) - AHB2_BASE)/0x400)<<(index->pin%8));
        SET_BIT(EXTI->DB, 0x1<<index->pin);
        
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
            case PIN_IRQ_MODE_RISING:
            {
                /* pull down the pin */
                MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x2<<index->pin));
                /* Enable EXTI rising interrupt and disable falling interrupt */
                SET_BIT(EXTI->RTS, (0x1<<index->pin));
                CLEAR_BIT(EXTI->FTS, (0x1<<index->pin));
                break;
            }
            case PIN_IRQ_MODE_FALLING:
            {
                /* pull up the pin */
                MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x1<<index->pin));
                /* Enable EXTI falling interrupt and disable rising interrupt */
                CLEAR_BIT(EXTI->RTS, (0x1<<index->pin));
                SET_BIT(EXTI->FTS, (0x1<<index->pin));
                break;
            }
            case PIN_IRQ_MODE_RISING_FALLING:
            {
                /* pull up the pin */
                MODIFY_REG(gpiox->PUD, (0x3<<index->pin), (0x1<<index->pin));
                /* Enable EXTI falling interrupt and enable rising interrupt */
                SET_BIT(EXTI->RTS, (0x1<<index->pin));
                SET_BIT(EXTI->FTS, (0x1<<index->pin));
                break;
            }
        }

        /* Enable EXTI interrupt */
        SET_BIT(EXTI->IER, (0x1<<index->pin));
        NVIC_EnableIRQ(irqmap->irqno);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(index->pin);
        if (irqmap == RT_NULL)
        {
            return RT_ENOSYS;
        }
        NVIC_DisableIRQ(irqmap->irqno);
    }
    else
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _es32f0_pin_ops =
{
    es32f0_pin_mode,
    es32f0_pin_write,
    es32f0_pin_read,
    es32f0_pin_attach_irq,
    es32f0_pin_detach_irq,
    es32f0_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;
    
    /* Open IO clock */
    SET_BIT(RCU->AHBEN, RCU_AHBEN_GPDEN_MSK|RCU_AHBEN_GPCEN_MSK            \
                                |RCU_AHBEN_GPBEN_MSK|RCU_AHBEN_GPAEN_MSK);

    /* register IO device */
    result = rt_device_pin_register("pin", &_es32f0_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(uint16_t GPIO_Pin)
{
    uint16_t irqno;
    /* pin no. convert to dec no. */
    for (irqno = 0; irqno < 16; irqno++)
    {
        if ((0x01 << irqno) == GPIO_Pin)
        {
            break;
        }
    }
    if (irqno == 16)
        return;
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* Read the exti interrupt then clear the flag */
    if ((EXTI->RIF & (0x1<<GPIO_Pin)) != RESET)
    {
        SET_BIT(EXTI->ICR, 0x1<<GPIO_Pin);
        pin_irq_hdr(GPIO_Pin);
    }
}

void EXTI0_1_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(0);
    GPIO_EXTI_Callback(1);
    rt_interrupt_leave();
}

void EXTI2_3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(2);
    GPIO_EXTI_Callback(3);
    rt_interrupt_leave();
}

void EXTI4_15_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(4);
    GPIO_EXTI_Callback(5);
    GPIO_EXTI_Callback(6);
    GPIO_EXTI_Callback(7);
    GPIO_EXTI_Callback(8);
    GPIO_EXTI_Callback(9);
    GPIO_EXTI_Callback(10);
    GPIO_EXTI_Callback(11);
    GPIO_EXTI_Callback(12);
    GPIO_EXTI_Callback(13);
    GPIO_EXTI_Callback(14);
    GPIO_EXTI_Callback(15);
    rt_interrupt_leave();
}

#endif

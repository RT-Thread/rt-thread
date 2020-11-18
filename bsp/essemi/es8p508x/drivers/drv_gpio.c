/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-07-11     wangyq        the first version
 */

#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"
#include <lib_scu.h>
#include <lib_gpio.h>

#ifdef RT_USING_PIN

#define __ES8P_PIN(index, gpio, gpio_index) {index, GPIO##gpio, GPIO_Pin_##gpio_index}
#define __ES8P_PIN_DEFAULT {-1, GPIOA, GPIO_Pin_0}

/* es8p GPIO driver */
struct pin_index
{
    int index;
    GPIO_TYPE gpio;
    GPIO_TYPE_PIN pin;
};

static const struct pin_index pins[] =
{
    __ES8P_PIN_DEFAULT,
    __ES8P_PIN(1, B, 0),
    __ES8P_PIN(2, B, 1),
    __ES8P_PIN(3, B, 2),
    __ES8P_PIN(4, B, 3),
    __ES8P_PIN(5, B, 4),
    __ES8P_PIN(6, B, 5),
    __ES8P_PIN(7, B, 6),
    __ES8P_PIN(8, B, 7),
    __ES8P_PIN(9, B, 8),
    __ES8P_PIN(10, B, 9),
    __ES8P_PIN(11, B, 10),
    __ES8P_PIN(12, B, 11),
    __ES8P_PIN(13, B, 12),
    __ES8P_PIN(14, B, 13),
    __ES8P_PIN(15, A, 0),
    __ES8P_PIN(16, A, 1),
    __ES8P_PIN(17, A, 2),
    __ES8P_PIN(18, A, 3),
    __ES8P_PIN(19, A, 4),
    __ES8P_PIN(20, A, 5),
    __ES8P_PIN(21, A, 6),
    __ES8P_PIN(22, A, 7),
    __ES8P_PIN(23, A, 8),
    __ES8P_PIN(24, A, 9),
    __ES8P_PIN(25, A, 10),
    __ES8P_PIN(26, A, 11),
    __ES8P_PIN(27, A, 12),
    __ES8P_PIN(28, A, 13),
    __ES8P_PIN(29, A, 14),
    __ES8P_PIN(30, A, 15),
    __ES8P_PIN(31, A, 16),
    __ES8P_PIN_DEFAULT,
    __ES8P_PIN_DEFAULT,
    __ES8P_PIN(34, A, 17),
    __ES8P_PIN(35, A, 18),
    __ES8P_PIN_DEFAULT,
    __ES8P_PIN(37, A, 20),
    __ES8P_PIN(38, A, 21),
    __ES8P_PIN(39, A, 22),
    __ES8P_PIN(40, A, 23),
    __ES8P_PIN(41, A, 24),
    __ES8P_PIN(42, A, 25),
    __ES8P_PIN(43, A, 26),
    __ES8P_PIN(44, A, 27),
    __ES8P_PIN(45, A, 28),
    __ES8P_PIN(46, A, 29),
    __ES8P_PIN(47, A, 30),
    __ES8P_PIN(48, A, 31),
};

struct irq_map
{
    PINT_TYPE pinno;
    IRQn_Type irqno;
};
static const struct irq_map irq_map[] =
{
    {PINT0, PINT0_IRQn},
    {PINT1, PINT1_IRQn},
    {PINT2, PINT2_IRQn},
    {PINT3, PINT3_IRQn},
    {PINT4, PINT4_IRQn},
    {PINT5, PINT5_IRQn},
    {PINT6, PINT6_IRQn},
    {PINT7, PINT7_IRQn},
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

void es8p_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    if (value == 0)
    {
        if (index->gpio == GPIOA)
            GPIOA_ResetBit(index->pin);
        else if (index->gpio == GPIOB)
            GPIOB_ResetBit(index->pin);
    }
    else
    {
        if (index->gpio == GPIOA)
            GPIOA_SetBit(index->pin);
        else if (index->gpio == GPIOB)
            GPIOB_SetBit(index->pin);
    }
}

int es8p_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;
    value = PIN_LOW;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }
    value = GPIO_ReadBit(index->gpio, index->pin);
    return value;
}

void es8p_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    GPIO_InitStruType gpio_initstruct;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    gpio_initstruct.GPIO_Signal = GPIO_Pin_Signal_Digital;
    gpio_initstruct.GPIO_Func = GPIO_Func_0;
    gpio_initstruct.GPIO_OD = GPIO_ODE_Output_Disable;
    gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Disable;
    gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Disable;
    gpio_initstruct.GPIO_DS = GPIO_DS_Output_Normal;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
        gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Enable;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
        gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Enable;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        gpio_initstruct.GPIO_Direction = GPIO_Dir_Out;
        gpio_initstruct.GPIO_OD = GPIO_ODE_Output_Enable;
    }
    GPIO_Init(index->gpio, index->pin, &gpio_initstruct);
}

rt_inline const struct irq_map *get_pin_irq_map(rt_uint16_t gpio_pin)
{
    rt_int32_t mapindex = gpio_pin & 0x00FF;
    if (mapindex < 0 || mapindex >= 32)
    {
        return RT_NULL;
    }
    return &irq_map[mapindex % 8];
};

rt_err_t es8p_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
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

    irqindex = index->pin % 8;
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

rt_err_t es8p_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    irqindex = index->pin % 8;
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

rt_err_t es8p_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                             rt_uint32_t enabled)
{
    const struct pin_index *index;
    const struct irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    /* Configure GPIO_InitStructure */
    GPIO_InitStruType gpio_initstruct;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = pin % 8;
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
        }
        irqmap = &irq_map[irqindex];

        /* Configure GPIO_InitStructure */
        gpio_initstruct.GPIO_Signal = GPIO_Pin_Signal_Digital;
        gpio_initstruct.GPIO_Func = GPIO_Func_0;
        gpio_initstruct.GPIO_Direction = GPIO_Dir_In;
        gpio_initstruct.GPIO_OD = GPIO_ODE_Output_Disable;
        gpio_initstruct.GPIO_DS = GPIO_DS_Output_Normal;

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Disable;
            gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Enable;
            if (index->gpio == GPIOA)
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)(pin >> 3), PINT_Trig_Rise);
            else
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)((pin >> 3) + 4), PINT_Trig_Rise);
            break;

        case PIN_IRQ_MODE_FALLING:
            gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Enable;
            gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Disable;
            if (index->gpio == GPIOA)
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)(pin >> 3), PINT_Trig_Fall);
            else
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)((pin >> 3) + 4), PINT_Trig_Fall);
            break;

        case PIN_IRQ_MODE_RISING_FALLING:
            gpio_initstruct.GPIO_PUEN = GPIO_PUE_Input_Disable;
            gpio_initstruct.GPIO_PDEN = GPIO_PDE_Input_Disable;
            if (index->gpio == GPIOA)
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)(pin >> 3), PINT_Trig_Change);
            else
                PINT_Config(irqmap->pinno, (PINT_TYPE_SEL)((pin >> 3) + 4), PINT_Trig_Change);
            break;

        default:
            break;
        }
        GPIO_Init(index->gpio, index->pin, &gpio_initstruct);
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

const static struct rt_pin_ops _es8p_pin_ops =
{
    es8p_pin_mode,
    es8p_pin_write,
    es8p_pin_read,
    es8p_pin_attach_irq,
    es8p_pin_detach_irq,
    es8p_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;
    SCU_GPIOCLK_Enable();
    result = rt_device_pin_register("pin", &_es8p_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

rt_inline void pin_irq_hdr(PINT_TYPE_IT GPIO_Pin)
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
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

rt_inline void GPIO_EXTI_Callback(PINT_TYPE_IT GPIO_Pin)
{
    if (PINT_GetIFStatus(GPIO_Pin) != RESET)
    {
        PINT_ClearITPendingBit(GPIO_Pin);
        pin_irq_hdr(GPIO_Pin);
    }
}

void PINT0_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT0);
    rt_interrupt_leave();
}

void PINT1_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT1);
    rt_interrupt_leave();
}

void PINT2_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT2);
    rt_interrupt_leave();
}

void PINT3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT3);
    rt_interrupt_leave();
}

void PINT4_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT4);
    rt_interrupt_leave();
}

void PINT5_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT5);
    rt_interrupt_leave();
}

void PINT6_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT6);
    rt_interrupt_leave();
}

void PINT7_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_Callback(PINT_IT_PINT7);
    rt_interrupt_leave();
}

#endif

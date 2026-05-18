/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#include "drv_gpio.h"

#ifdef BSP_USING_GPIO

#define PIN_NUM(port, no) (((((port) & 0xFU) << 4U) | ((no) & 0xFU)))
#define PIN_PORT(pin)     ((uint8_t)(((pin) >> 4U) & 0xFU))
#define PIN_NO(pin)       ((uint8_t)((pin) & 0xFU))

#define PIN_STPORT(pin)   ((GPIO_Module *)(GPIOA_BASE + (0x400U * PIN_PORT(pin))))
#define PIN_STPIN(pin)    ((uint16_t)(1U << PIN_NO(pin)))

#define ITEM_NUM(items)   (sizeof(items) / sizeof((items)[0]))

static uint32_t pin_irq_enable_mask = 0;

#if defined(GPIOK)
    #define __N32_PORT_MAX 8u
#elif defined(GPIOJ)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOI)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOH)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOG)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOF)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOE)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOD)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOC)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOB)
    #define __N32_PORT_MAX 16u
#elif defined(GPIOA)
    #define __N32_PORT_MAX 16u
#else
    #define __N32_PORT_MAX 0u
    #error Unsupported N32 GPIO peripheral.
#endif

#define PIN_STPORT_MAX __N32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0,  EXTI_LINE0, EXTI0_IRQn},
    {GPIO_PIN_1,  EXTI_LINE1, EXTI1_IRQn},
    {GPIO_PIN_2,  EXTI_LINE2, EXTI2_IRQn},
    {GPIO_PIN_3,  EXTI_LINE3, EXTI3_IRQn},
    {GPIO_PIN_4,  EXTI_LINE4, EXTI4_IRQn},
    {GPIO_PIN_5,  EXTI_LINE5, EXTI9_5_IRQn},
    {GPIO_PIN_6,  EXTI_LINE6, EXTI9_5_IRQn},
    {GPIO_PIN_7,  EXTI_LINE7, EXTI9_5_IRQn},
    {GPIO_PIN_8,  EXTI_LINE8, EXTI9_5_IRQn},
    {GPIO_PIN_9,  EXTI_LINE9, EXTI9_5_IRQn},
    {GPIO_PIN_10, EXTI_LINE10, EXTI15_10_IRQn},
    {GPIO_PIN_11, EXTI_LINE11, EXTI15_10_IRQn},
    {GPIO_PIN_12, EXTI_LINE12, EXTI15_10_IRQn},
    {GPIO_PIN_13, EXTI_LINE13, EXTI15_10_IRQn},
    {GPIO_PIN_14, EXTI_LINE14, EXTI15_10_IRQn},
    {GPIO_PIN_15, EXTI_LINE15, EXTI15_10_IRQn},
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

/* e.g. PA.0 */
static rt_base_t n32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4U) || (name_len >= 6U))
    {
        goto out;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        goto out;
    }

    if ((name[1] >= 'A') && (name[1] <= 'Z'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else
    {
        goto out;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);

    return pin;

out:
    rt_kprintf("Px.y  x:A~Z  y:0-15, e.g. PA.0\n");
    return -RT_EINVAL;
}

static void n32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_Module *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);

        if (value != 0)
        {
            gpio_port->PBSC = gpio_pin;
        }
        else
        {
            gpio_port->PBC = gpio_pin;
        }
    }
}

static rt_ssize_t n32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_Module *gpio_port;
    uint16_t gpio_pin;
    Bit_OperateType state = Bit_RESET;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);

        if ((gpio_port->PID & gpio_pin) != Bit_RESET)
        {
            state = Bit_SET;
        }
        else
        {
            state = Bit_RESET;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    return (state == Bit_RESET) ? PIN_LOW : PIN_HIGH;
}

static void n32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitType GPIO_InitStructure;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return;
    }

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure GPIO_InitStructure */
    GPIO_InitStructure.Pin = PIN_STPIN(pin);

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
        GPIO_InitStructure.GPIO_Pull = GPIO_PULL_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
    }

    GPIO_InitPeripheral(PIN_STPORT(pin), &GPIO_InitStructure);
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
    if (mapindex < 0 || mapindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};


static rt_err_t n32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
    if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_STPIN(pin));
        if (irqindex < 0 || irqindex >= (rt_int32_t)ITEM_NUM(pin_irq_map))
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

        /* EXTI Line Config */
        GPIO_ConfigEXTILine(irqmap->exti_line, (PIN_NO(pin) * 11 + PIN_PORT(pin)));

        GPIO_InitStruct(&GPIO_InitStructure);
        /* Configure GPIO_InitStructure */
        GPIO_InitStructure.Pin = PIN_STPIN(pin);
        GPIO_InitStructure.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
            GPIO_InitStructure.GPIO_Pull = GPIO_PULL_DOWN;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
            GPIO_InitStructure.GPIO_Pull = GPIO_PULL_DOWN;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
            GPIO_InitStructure.GPIO_Pull = GPIO_NO_PULL;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        GPIO_InitPeripheral(PIN_STPORT(pin), &GPIO_InitStructure);

        EXTI_InitStructure.EXTI_Line = irqmap->exti_line;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitPeripheral(&EXTI_InitStructure);

        NVIC_SetPriority(irqmap->irqno, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
        NVIC_EnableIRQ(irqmap->irqno);
        pin_irq_enable_mask |= irqmap->pinbit;

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

        pin_irq_enable_mask &= ~irqmap->pinbit;

        if ((irqmap->pinbit >= GPIO_PIN_5) && (irqmap->pinbit <= GPIO_PIN_9))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_PIN_10) && (irqmap->pinbit <= GPIO_PIN_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)))
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

static const struct rt_pin_ops _n32_pin_ops =
{
    n32_pin_mode,
    n32_pin_write,
    n32_pin_read,
    n32_pin_attach_irq,
    n32_pin_dettach_irq,
    n32_pin_irq_enable,
    n32_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void N32_GPIO_EXTI_Callback(uint16_t line_num)
{
    if (pin_irq_hdr_tab[line_num].pin != -1 && EXTI_GetITStatus(line_num) != RESET)
    {
        /* Clear EXTI line pending bit */
        EXTI_ClrITPendBit(line_num);

        pin_irq_hdr(line_num);
    }
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE4);
    rt_interrupt_leave();
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE5);
    N32_GPIO_EXTI_Callback(EXTI_LINE6);
    N32_GPIO_EXTI_Callback(EXTI_LINE7);
    N32_GPIO_EXTI_Callback(EXTI_LINE8);
    N32_GPIO_EXTI_Callback(EXTI_LINE9);
    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    N32_GPIO_EXTI_Callback(EXTI_LINE10);
    N32_GPIO_EXTI_Callback(EXTI_LINE11);
    N32_GPIO_EXTI_Callback(EXTI_LINE12);
    N32_GPIO_EXTI_Callback(EXTI_LINE13);
    N32_GPIO_EXTI_Callback(EXTI_LINE14);
    N32_GPIO_EXTI_Callback(EXTI_LINE15);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
#if defined(SOC_SERIES_N32H7xx)
#if defined(AFIO)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_AFIO, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(EXTI)
    RCC_EnableAPB5PeriphClk2(RCC_APB5_PERIPHEN_EXTI, ENABLE);
#endif

#if defined(GPIOA)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOA, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOA, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOB)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOB, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOB, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOC)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOC, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOC, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOD)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOD, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOD, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOE)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOE, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOE, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOF)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOF, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOF, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOG)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOG, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOG, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOH)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M7_GPIOH, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk1(RCC_AHB5_PERIPHEN_M4_GPIOH, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOI)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOI, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_GPIOI, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOJ)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOJ, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_GPIOJ, ENABLE);
#endif /* SOC_N32H78X */
#endif

#if defined(GPIOK)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_GPIOK, ENABLE);
#if defined(SOC_N32H78X)
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_GPIOK, ENABLE);
#endif /* SOC_N32H78X */
#endif
#endif /* defined(SOC_SERIES_N32H7xx) */

    return rt_device_pin_register("pin", &_n32_pin_ops, RT_NULL);
}

#endif /* BSP_USING_GPIO */


/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-02     FMD-AE       first version
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_FTPORT(pin) ((GPIO_TypeDef *)(GPIOA_BASE +(0x400u * PIN_PORT(pin))))
#define PIN_FTPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))

#if defined(GPIOF)
    #define __FT32_PORT_MAX 6u
#elif defined(GPIOE)
    #define __FT32_PORT_MAX 5u
#elif defined(GPIOD)
    #define __FT32_PORT_MAX 4u
#elif defined(GPIOC)
    #define __FT32_PORT_MAX 3u
#elif defined(GPIOB)
    #define __FT32_PORT_MAX 2u
#elif defined(GPIOA)
    #define __FT32_PORT_MAX 1u
#else
    #define __FT32_PORT_MAX 0u
    #error Unsupported FT32 GPIO peripheral.
#endif

#define PIN_STPORT_MAX __FT32_PORT_MAX

static const struct pin_irq_map pin_irq_map[] =
{
#if defined(SOC_SERIES_FT32F0)
    {GPIO_Pin_0, EXTI0_1_IRQn},
    {GPIO_Pin_1, EXTI0_1_IRQn},
    {GPIO_Pin_2, EXTI2_3_IRQn},
    {GPIO_Pin_3, EXTI2_3_IRQn},
    {GPIO_Pin_4, EXTI4_15_IRQn},
    {GPIO_Pin_5, EXTI4_15_IRQn},
    {GPIO_Pin_6, EXTI4_15_IRQn},
    {GPIO_Pin_7, EXTI4_15_IRQn},
    {GPIO_Pin_8, EXTI4_15_IRQn},
    {GPIO_Pin_9, EXTI4_15_IRQn},
    {GPIO_Pin_10, EXTI4_15_IRQn},
    {GPIO_Pin_11, EXTI4_15_IRQn},
    {GPIO_Pin_12, EXTI4_15_IRQn},
    {GPIO_Pin_13, EXTI4_15_IRQn},
    {GPIO_Pin_14, EXTI4_15_IRQn},
    {GPIO_Pin_15, EXTI4_15_IRQn},
#endif
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

static rt_base_t ft32_pin_get(const char *name)
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

static void ft32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_FTPORT(pin);
        gpio_pin = PIN_FTPIN(pin);

        GPIO_WriteBit(gpio_port, gpio_pin, (BitAction)value);
    }
}

static rt_ssize_t ft32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    rt_ssize_t value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_FTPORT(pin);
        gpio_pin = PIN_FTPIN(pin);
        value = GPIO_ReadInputDataBit(gpio_port, gpio_pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    return value;
}

static void ft32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin = PIN_FTPIN(pin);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
    }

    GPIO_Init(PIN_FTPORT(pin), &GPIO_InitStruct);
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

static rt_err_t ft32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_FTPIN(pin));
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

static rt_err_t ft32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_FTPIN(pin));
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

static void rt_gpio_deinit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
    uint32_t position = 0x00u;
    uint32_t iocurrent;
    uint32_t tmp;

    /* Configure the port pins */
    while ((GPIO_Pin >> position) != 0x00u)
    {
        /* Get current io position */
        iocurrent = (GPIO_Pin) & (1uL << position);

        if (iocurrent != 0x00u)
        {
            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */

            tmp = SYSCFG->EXTICR[position >> 2u];
            tmp &= (0x0FuL << (4u * (position & 0x03u)));
            if (tmp == (GPIO_GET_INDEX(GPIOx) << (4u * (position & 0x03u))))
            {
                /* Clear EXTI line configuration */
                EXTI->IMR &= ~((uint32_t)iocurrent);
                EXTI->EMR &= ~((uint32_t)iocurrent);

                /* Clear Rising Falling edge configuration */
                EXTI->RTSR &= ~((uint32_t)iocurrent);
                EXTI->FTSR &= ~((uint32_t)iocurrent);

                /* Configure the External Interrupt or event for the current IO */
                tmp = 0x0FuL << (4u * (position & 0x03u));
                SYSCFG->EXTICR[position >> 2u] &= ~tmp;
            }

            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Input Floating Mode */
            GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (position * 2u));

            /* Configure the default Alternate Function in current IO */
            GPIOx->AFR[position >> 3u] &= ~(0xFu << ((uint32_t)(position & 0x07u) * 4u)) ;

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (position * 2u));

            /* Configure the default value IO Output Type */
            GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT_0 << position) ;

            /* Configure the default value for IO Speed */
            GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2u));

        }

        position++;
    }

}


static rt_err_t ft32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef   EXTI_InitStructure;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_FTPIN(pin));
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

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
        SYSCFG_EXTILineConfig(PIN_PORT(pin), PIN_NO(pin));

        GPIO_InitStruct.GPIO_Pin = PIN_FTPIN(pin);
        GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;
        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
            EXTI_InitStructure.EXTI_Line = PIN_FTPIN(pin);
            EXTI_InitStructure.EXTI_LineCmd = ENABLE;
            EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
            EXTI_InitStructure.EXTI_Line = PIN_FTPIN(pin);
            EXTI_InitStructure.EXTI_LineCmd = ENABLE;
            EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
            EXTI_InitStructure.EXTI_Line = PIN_FTPIN(pin);
            EXTI_InitStructure.EXTI_LineCmd = ENABLE;
            EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
            EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
            break;
        }
        GPIO_Init(PIN_FTPORT(pin), &GPIO_InitStruct);
        EXTI_Init(&EXTI_InitStructure);

        NVIC_SetPriority(irqmap->irqno, 5);
        NVIC_EnableIRQ(irqmap->irqno);
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        irqmap = get_pin_irq_map(PIN_FTPIN(pin));
        if (irqmap == RT_NULL)
        {
            return -RT_ENOSYS;
        }

        level = rt_hw_interrupt_disable();

        rt_gpio_deinit(PIN_FTPORT(pin), PIN_FTPIN(pin));

        pin_irq_enable_mask &= ~irqmap->pinbit;


#if defined(SOC_SERIES_FT32F0)
        if ((irqmap->pinbit >= GPIO_Pin_0) && (irqmap->pinbit <= GPIO_Pin_1))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_0 | GPIO_Pin_1)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_Pin_2) && (irqmap->pinbit <= GPIO_Pin_3))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_2 | GPIO_Pin_3)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else if ((irqmap->pinbit >= GPIO_Pin_4) && (irqmap->pinbit <= GPIO_Pin_15))
        {
            if (!(pin_irq_enable_mask & (GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |
                                         GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
            {
                NVIC_DisableIRQ(irqmap->irqno);
            }
        }
        else
        {
            NVIC_DisableIRQ(irqmap->irqno);
        }

#endif
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}
const static struct rt_pin_ops _ft32_pin_ops =
{
    ft32_pin_mode,
    ft32_pin_write,
    ft32_pin_read,
    ft32_pin_attach_irq,
    ft32_pin_dettach_irq,
    ft32_pin_irq_enable,
    ft32_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}


void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}

void GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
    /* EXTI line interrupt detected */
    if (__GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)
    {
        __GPIO_EXTI_CLEAR_IT(GPIO_Pin);
        GPIO_EXTI_Callback(GPIO_Pin);
    }
}

#if defined(SOC_SERIES_FT32F0)
void EXTI0_1_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pin_0);
    GPIO_EXTI_IRQHandler(GPIO_Pin_1);
    rt_interrupt_leave();
}

void EXTI2_3_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pin_2);
    GPIO_EXTI_IRQHandler(GPIO_Pin_3);
    rt_interrupt_leave();
}
void EXTI4_15_IRQHandler(void)
{
    rt_interrupt_enter();
    GPIO_EXTI_IRQHandler(GPIO_Pin_4);
    GPIO_EXTI_IRQHandler(GPIO_Pin_5);
    GPIO_EXTI_IRQHandler(GPIO_Pin_6);
    GPIO_EXTI_IRQHandler(GPIO_Pin_7);
    GPIO_EXTI_IRQHandler(GPIO_Pin_8);
    GPIO_EXTI_IRQHandler(GPIO_Pin_9);
    GPIO_EXTI_IRQHandler(GPIO_Pin_10);
    GPIO_EXTI_IRQHandler(GPIO_Pin_11);
    GPIO_EXTI_IRQHandler(GPIO_Pin_12);
    GPIO_EXTI_IRQHandler(GPIO_Pin_13);
    GPIO_EXTI_IRQHandler(GPIO_Pin_14);
    GPIO_EXTI_IRQHandler(GPIO_Pin_15);
    rt_interrupt_leave();
}
#endif

int rt_hw_pin_init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);
    return rt_device_pin_register("pin", &_ft32_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */

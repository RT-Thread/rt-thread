/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-12-27     iysheng           first version
 * 2021-01-01     iysheng           support exti interrupt
 * 2021-09-07     FuC               Suit for Vango V85xx
 * 2021-09-09     ZhuXW             Add GPIO interrupt
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#if defined(GPIOF)
#define __V85XX_PORT_MAX 6u
#elif defined(GPIOE)
#define __V85XX_PORT_MAX 5u
#elif defined(GPIOD)
#define __V85XX_PORT_MAX 4u
#elif defined(GPIOC)
#define __V85XX_PORT_MAX 3u
#elif defined(GPIOB)
#define __V85XX_PORT_MAX 2u
#elif defined(GPIOA)
#define __V85XX_PORT_MAX 1u
#else
#define __V85XX_PORT_MAX 0u
#error Unsupported V85XX GPIO peripheral.
#endif

#define PIN_V85XXPORT_MAX __V85XX_PORT_MAX
#define PIN_V85XXPORT_A   0u

static const struct pin_irq_map pin_irq_map[] =
{
#if defined(SOC_SERIES_V85XX)
    {GPIO_Pin_0,  PMU_IRQn},
    {GPIO_Pin_1,  PMU_IRQn},
    {GPIO_Pin_2,  PMU_IRQn},
    {GPIO_Pin_3,  PMU_IRQn},
    {GPIO_Pin_4,  PMU_IRQn},
    {GPIO_Pin_5,  PMU_IRQn},
    {GPIO_Pin_6,  PMU_IRQn},
    {GPIO_Pin_7,  PMU_IRQn},
    {GPIO_Pin_8,  PMU_IRQn},
    {GPIO_Pin_9,  PMU_IRQn},
    {GPIO_Pin_10, PMU_IRQn},
    {GPIO_Pin_11, PMU_IRQn},
    {GPIO_Pin_12, PMU_IRQn},
    {GPIO_Pin_13, PMU_IRQn},
    {GPIO_Pin_14, PMU_IRQn},
    {GPIO_Pin_15, PMU_IRQn},
#else
#error "Unsupported soc series"
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

static rt_base_t v85xx_pin_get(const char *name)
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

    if ((name[1] >= 'A') && (name[1] <= 'F'))
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

static void v85xx_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) == PIN_V85XXPORT_A)
    {
        gpio_pin = PIN_V85XXPIN(pin);

        GPIOA_WriteBit(GPIOA, gpio_pin, (BitState)value);
    }
    else if (PIN_PORT(pin) < PIN_V85XXPORT_MAX)
    {
        gpio_port = PIN_V85XXPORT(pin);
        gpio_pin = PIN_V85XXPIN(pin);

        GPIOBToF_WriteBit(gpio_port, gpio_pin, (BitState)value);
    }
}

static rt_ssize_t v85xx_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    rt_ssize_t value = PIN_LOW;

    if (PIN_PORT(pin) == PIN_V85XXPORT_A)
    {
        gpio_pin = PIN_V85XXPIN(pin);
        value = GPIOA_ReadInputDataBit(GPIOA, gpio_pin);
    }
    else if (PIN_PORT(pin) < PIN_V85XXPORT_MAX)
    {
        gpio_port = PIN_V85XXPORT(pin);
        gpio_pin = PIN_V85XXPIN(pin);
        value = GPIOBToF_ReadInputDataBit(gpio_port, gpio_pin);
    }
    else
    {
        return -RT_EINVAL;
    }

    return value;
}

static void v85xx_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_InitType GPIO_InitStruct = {0};

    if (PIN_PORT(pin) >= PIN_V85XXPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin  = PIN_V85XXPIN(pin);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUTPUT_CMOS;
            break;
        case PIN_MODE_INPUT:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
            break;
        case PIN_MODE_INPUT_PULLUP:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_CMOS;
            break;
        case PIN_MODE_INPUT_PULLDOWN:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_OD;
            break;
        case PIN_MODE_OUTPUT_OD:
            GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INOUT_OD;
            break;
        default:
            break;
    }

    if (PIN_PORT(pin) == PIN_V85XXPORT_A)
    {
        GPIOA_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (PIN_PORT(pin) < PIN_V85XXPORT_MAX)
    {
        GPIOBToF_Init(PIN_V85XXPORT(pin), &GPIO_InitStruct);
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


static rt_err_t v85xx_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) > PIN_V85XXPORT_A)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_V85XXPIN(pin));
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
static rt_err_t v85xx_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) > PIN_V85XXPORT_A)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_V85XXPIN(pin));
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
static rt_err_t v85xx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_InitType GPIO_InitStruct = {0};

    if (PIN_PORT(pin) > PIN_V85XXPORT_A)
    {
        return -RT_ENOSYS;
    }

    GPIO_InitStruct.GPIO_Pin = PIN_V85XXPIN(pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_V85XXPIN(pin));
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

        GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
        GPIO_InitStruct.GPIO_Pin  = PIN_V85XXPIN(pin);
        GPIOA_Init(GPIOA, &GPIO_InitStruct);

        irqmap = &pin_irq_map[irqindex];

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            PMU_WakeUpPinConfig(PIN_V85XXPIN(pin), IOA_RISING);
            break;
        case PIN_IRQ_MODE_FALLING:
            PMU_WakeUpPinConfig(PIN_V85XXPIN(pin), IOA_FALLING);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            PMU_WakeUpPinConfig(PIN_V85XXPIN(pin), IOA_EDGEBOTH);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            PMU_WakeUpPinConfig(PIN_V85XXPIN(pin), IOA_HIGH);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            PMU_WakeUpPinConfig(PIN_V85XXPIN(pin), IOA_LOW);
            break;
        default:
            break;
        }
        PMU_INTConfig(PMU_INT_IOAEN, ENABLE);

        NVIC_SetPriority(irqmap->irqno, 0);
        NVIC_EnableIRQ(irqmap->irqno);
        pin_irq_enable_mask |= irqmap->pinbit;

        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {

        level = rt_hw_interrupt_disable();

        PMU_INTConfig(PMU_INT_IOAEN, DISABLE);

        NVIC_DisableIRQ(irqmap->irqno);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }
    return RT_EOK;
}



const static struct rt_pin_ops _v85xx_pin_ops =
{
    v85xx_pin_mode,
    v85xx_pin_write,
    v85xx_pin_read,
    v85xx_pin_attach_irq,
    v85xx_pin_detach_irq,
    v85xx_pin_irq_enable,
    v85xx_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}


void v85xx_pin_exti_irqhandler()
{
    rt_base_t intsts=0;
    int i=0;

    intsts = PMU_GetIOAAllINTStatus();
    for(i=0; i<16; i++)
    {
        if((1<<i) & intsts)
        {
            PMU_ClearIOAINTStatus(1<<i);
            pin_irq_hdr(bit2bitno(1<<i));
            return;
        }
    }
}

void PMU_IRQHandler()
{
    rt_interrupt_enter();
    v85xx_pin_exti_irqhandler();
    rt_interrupt_leave();
}


int rt_hw_pin_init(void)
{
  GPIO_InitType GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;

#if defined(GPIOF)
    GPIOBToF_Init(GPIOF, &GPIO_InitStruct);
#endif
#if defined(GPIOE)
    GPIOBToF_Init(GPIOE, &GPIO_InitStruct);
#endif
#if defined(GPIOD)
    GPIOBToF_Init(GPIOD, &GPIO_InitStruct);
#endif
#if defined(GPIOC)
    GPIOBToF_Init(GPIOC, &GPIO_InitStruct);
#endif
#if defined(GPIOB)
    GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
#endif
#if defined(GPIOA)
    GPIOA_Init(GPIOA, &GPIO_InitStruct);
#endif

    return rt_device_pin_register("pin", &_v85xx_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);
#endif /* RT_USING_PIN */

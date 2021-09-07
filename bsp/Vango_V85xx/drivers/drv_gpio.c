/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-12-27     iysheng           first version
 * 2021-01-01     iysheng           support exti interrupt
 * 2021-09-07     FuC               Suit for Vango V85xx
 */

#include <board.h>
#include "drv_gpio.h"

#ifdef RT_USING_PIN

#if defined(GPIOG)
#define __GD32_PORT_MAX 7u
#elif defined(GPIOF)
#define __GD32_PORT_MAX 6u
#elif defined(GPIOE)
#define __GD32_PORT_MAX 5u
#elif defined(GPIOD)
#define __GD32_PORT_MAX 4u
#elif defined(GPIOC)
#define __GD32_PORT_MAX 3u
#elif defined(GPIOB)
#define __GD32_PORT_MAX 2u
#elif defined(GPIOA)
#define __GD32_PORT_MAX 1u
#else
#define __GD32_PORT_MAX 0u
#error Unsupported GD32 GPIO peripheral.
#endif

#define PIN_GDPORT_MAX __GD32_PORT_MAX

// static const struct pin_irq_map pin_irq_map[] =
// {
// #if defined(SOC_SERIES_GD32F1)
//     {GPIO_Pin_0, EXTI0_IRQn},
//     {GPIO_Pin_1, EXTI1_IRQn},
//     {GPIO_Pin_2, EXTI2_IRQn},
//     {GPIO_Pin_3, EXTI3_IRQn},
//     {GPIO_Pin_4, EXTI4_IRQn},
//     {GPIO_Pin_5, EXTI9_5_IRQn},
//     {GPIO_Pin_6, EXTI9_5_IRQn},
//     {GPIO_Pin_7, EXTI9_5_IRQn},
//     {GPIO_Pin_8, EXTI9_5_IRQn},
//     {GPIO_Pin_9, EXTI9_5_IRQn},
//     {GPIO_Pin_10, EXTI15_10_IRQn},
//     {GPIO_Pin_11, EXTI15_10_IRQn},
//     {GPIO_Pin_12, EXTI15_10_IRQn},
//     {GPIO_Pin_13, EXTI15_10_IRQn},
//     {GPIO_Pin_14, EXTI15_10_IRQn},
//     {GPIO_Pin_15, EXTI15_10_IRQn},
// #else
// #error "Unsupported soc series"
// #endif
// };

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

static void v85xx_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_GDPORT_MAX)
    {
        gpio_port = PIN_GDPORT(pin);
        gpio_pin = PIN_GDPIN(pin);

        GPIOBToF_WriteBit(gpio_port, gpio_pin, (BitState)value);//GPIOA ignored
    }
}

static int v85xx_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    int value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_GDPORT_MAX)
    {
        gpio_port = PIN_GDPORT(pin);
        gpio_pin = PIN_GDPIN(pin);
        value = GPIOBToF_ReadInputDataBit(gpio_port, gpio_pin);//GPIOA ignored
    }

    return value;
}

static void v85xx_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    GPIO_InitType GPIO_InitStruct = {0};

    if (PIN_PORT(pin) >= PIN_GDPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.GPIO_Pin  = PIN_GDPIN(pin);
    // GPIO_InitStruct.GPIO_Speed = GPIO_SPEED_2MHZ;
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

    GPIOBToF_Init(PIN_GDPORT(pin), &GPIO_InitStruct);//ignore GPIOA
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

const static struct rt_pin_ops _v85xx_pin_ops =
{
    v85xx_pin_mode,
    v85xx_pin_write,
    v85xx_pin_read,
    v85xx_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

// /**
//   * @brief  This function handles EXTI interrupt request.
//   * @param  gpio_pin: Specifies the pins connected EXTI line
//   * @retval none
//   */
// void v85xx_pin_exti_irqhandler(uint16_t gpio_pin)
// {
//     if (SET == EXTI_GetIntBitState(gpio_pin))
//     {
//         EXTI_ClearIntBitState(gpio_pin);
//         pin_irq_hdr(bit2bitno(gpio_pin));
//     }
// }

// void EXTI0_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_0);
//     rt_interrupt_leave();
// }

// void EXTI1_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_1);
//     rt_interrupt_leave();
// }

// void EXTI2_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_2);
//     rt_interrupt_leave();
// }

// void EXTI3_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_3);
//     rt_interrupt_leave();
// }

// void EXTI4_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_4);
//     rt_interrupt_leave();
// }

// void EXTI5_9_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_5);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_6);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_7);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_8);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_9);
//     rt_interrupt_leave();
// }

// void EXTI10_15_IRQHandler(void)
// {
//     rt_interrupt_enter();
//     v85xx_pin_exti_irqhandler(GPIO_Pin_10);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_11);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_12);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_13);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_14);
//     v85xx_pin_exti_irqhandler(GPIO_Pin_15);
//     rt_interrupt_leave();
// }

int rt_hw_pin_init(void)
{
  GPIO_InitType GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_INPUT;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
#if defined(GPIOG)
    GPIOBToF_Init(GPIOG, &GPIO_InitStruct);
#endif
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
    GPIOBToF_Init(GPIOB, &GPIO_InitStruct);
    return rt_device_pin_register("pin", &_v85xx_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);
#endif /* RT_USING_PIN */


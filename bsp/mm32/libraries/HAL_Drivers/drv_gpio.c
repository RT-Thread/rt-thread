/*
 * Copyright (c) 2020-2022, CQ 100ask Development Team
 *
 * Change Logs:
 *   Date           Author          Notes
 * 2022-05-29        Alen       first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

#define PIN_NUM(port, no) (((((port) & 0xFu) << 4) | ((no) & 0xFu)))
#define PIN_PORT(pin) ((uint8_t)(((pin) >> 4) & 0xFu))
#define PIN_NO(pin) ((uint8_t)((pin) & 0xFu))

#define PIN_STPORT(pin) ((GPIO_Type *)(GPIOA_BASE + (0x400u * PIN_PORT(pin))))

#define PIN_STPIN(pin) ((uint16_t)(1u << PIN_NO(pin)))


#if defined(GPIOF)
#define __MM32_PORT_MAX 6u
#elif defined(GPIOE)
#define __MM32_PORT_MAX 5u
#elif defined(GPIOD)
#define __MM32_PORT_MAX 4u
#elif defined(GPIOC)
#define __MM32_PORT_MAX 3u
#elif defined(GPIOB)
#define __MM32_PORT_MAX 2u
#elif defined(GPIOA)
#define __MM32_PORT_MAX 1u
#else
#define __MM32_PORT_MAX 0u
#error Unsupported MM32 GPIO peripheral.
#endif

#define PIN_STPORT_MAX __MM32_PORT_MAX

#define GET_EXTI_PORT(PORT)

static const struct pin_irq_map pin_irq_map[] =
{
    {GPIO_PIN_0, EXTI0_IRQn, EXTI_LINE_0, SYSCFG_EXTILine_0},
    {GPIO_PIN_1, EXTI1_IRQn, EXTI_LINE_1, SYSCFG_EXTILine_1},
    {GPIO_PIN_2, EXTI2_IRQn, EXTI_LINE_2, SYSCFG_EXTILine_2},
    {GPIO_PIN_3, EXTI3_IRQn, EXTI_LINE_3, SYSCFG_EXTILine_3},
    {GPIO_PIN_4, EXTI4_IRQn, EXTI_LINE_4, SYSCFG_EXTILine_4},
    {GPIO_PIN_5, EXTI9_5_IRQn, EXTI_LINE_5,SYSCFG_EXTILine_5},
    {GPIO_PIN_6, EXTI9_5_IRQn, EXTI_LINE_6, SYSCFG_EXTILine_6},
    {GPIO_PIN_7, EXTI9_5_IRQn, EXTI_LINE_7, SYSCFG_EXTILine_7},
    {GPIO_PIN_8, EXTI9_5_IRQn, EXTI_LINE_8, SYSCFG_EXTILine_8},
    {GPIO_PIN_9, EXTI9_5_IRQn, EXTI_LINE_9, SYSCFG_EXTILine_9},
    {GPIO_PIN_10, EXTI15_10_IRQn, EXTI_LINE_10, SYSCFG_EXTILine_10},
    {GPIO_PIN_11, EXTI15_10_IRQn, EXTI_LINE_11, SYSCFG_EXTILine_11},
    {GPIO_PIN_12, EXTI15_10_IRQn, EXTI_LINE_12, SYSCFG_EXTILine_12},
    {GPIO_PIN_13, EXTI15_10_IRQn, EXTI_LINE_13, SYSCFG_EXTILine_13},
    {GPIO_PIN_14, EXTI15_10_IRQn, EXTI_LINE_14, SYSCFG_EXTILine_14},
    {GPIO_PIN_15, EXTI15_10_IRQn, EXTI_LINE_15, SYSCFG_EXTILine_15},
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

static rt_base_t mm32_pin_get(const char *name)
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

static void mm32_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);

        GPIO_WriteBit(gpio_port, gpio_pin, (rt_uint16_t)value);
    }
}

static rt_int8_t mm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    GPIO_Type *gpio_port;
    uint16_t gpio_pin;
    rt_int8_t value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_STPORT_MAX)
    {
        gpio_port = PIN_STPORT(pin);
        gpio_pin = PIN_STPIN(pin);
        value = GPIO_ReadInDataBit(gpio_port, gpio_pin);
    }

    return value;
}

static void mm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_Init_Type GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return;
    }

    /* Configure GPIO_InitStructure */
    GPIO_InitStruct.Pins = PIN_STPIN(pin);
    GPIO_InitStruct.PinMode = GPIO_PinMode_Out_PushPull;
    GPIO_InitStruct.Speed = GPIO_Speed_50MHz;

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        GPIO_InitStruct.PinMode = GPIO_PinMode_Out_PushPull;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        GPIO_InitStruct.PinMode = GPIO_PinMode_In_Floating;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        GPIO_InitStruct.PinMode = GPIO_PinMode_In_PullUp;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        GPIO_InitStruct.PinMode = GPIO_PinMode_In_PullDown;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        GPIO_InitStruct.PinMode = GPIO_PinMode_Out_OpenDrain;
    }

    GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);
}

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

rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if (mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};

static rt_err_t mm32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
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

static rt_err_t mm32_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = bit2bitno(PIN_STPIN(pin));
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

static rt_err_t mm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    GPIO_Init_Type GPIO_InitStruct;

    if (PIN_PORT(pin) >= PIN_STPORT_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        irqindex = bit2bitno(PIN_STPIN(pin));
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

        /* Configure GPIO_InitStructure */
        GPIO_InitStruct.Pins = PIN_STPIN(pin);
        GPIO_InitStruct.Speed = GPIO_Speed_50MHz;
        GPIO_InitStruct.PinMode = GPIO_PinMode_In_PullUp;
        GPIO_Init(PIN_STPORT(pin), &GPIO_InitStruct);

        SYSCFG_SetExtIntMux(SYSCFG_EXTIPort_GPIOA + (0 == (rt_uint32_t)PIN_PORT(pin)?0: PIN_PORT(pin)/GPIOB_BASE), irqmap->syscfg_extiline);
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_RisingEdge);
            break;
        case PIN_IRQ_MODE_FALLING:
            EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_FallingEdge);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            EXTI_SetTriggerIn(EXTI, irqmap->extiline, EXTI_TriggerIn_BothEdges);
            break;
        }
        EXTI_EnableLineInterrupt(EXTI, irqmap->extiline, true);

        NVIC_SetPriority(irqmap->irqno, NVIC_EncodePriority(4, 5, 0));
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
const static struct rt_pin_ops _mm32_pin_ops =
{
    mm32_pin_mode,
    mm32_pin_write,
    mm32_pin_read,
    mm32_pin_attach_irq,
    mm32_pin_dettach_irq,
    mm32_pin_irq_enable,
    mm32_pin_get,
};

rt_inline void pin_irq_hdr(int irqno)
{
    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pin_irq_hdr(bit2bitno(GPIO_Pin));
}

#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Callback(GPIO_Pin);
  }
}

void EXTI0_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    rt_interrupt_leave();
}

void EXTI1_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    rt_interrupt_leave();
}

void EXTI2_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
    rt_interrupt_leave();
}

void EXTI3_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    rt_interrupt_leave();
}

void EXTI4_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
    rt_interrupt_leave();
}

void EXTI9_5_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
    rt_interrupt_leave();
}

void EXTI15_10_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
#if defined(RCC_AHB1_PERIPH_GPIOA)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOA, true);
#endif

#if defined(RCC_AHB1_PERIPH_GPIOB)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOB, true);
#endif

#if defined(RCC_AHB1_PERIPH_GPIOC)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOC, true);
#endif

#if defined(RCC_AHB1_PERIPH_GPIOD)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOD, true);
#endif

#if defined(RCC_AHB1_PERIPH_GPIOE)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOE, true);
#endif

#if defined(RCC_AHB1_PERIPH_GPIOF)
    RCC_EnableAHB1Periphs(RCC_AHB1_PERIPH_GPIOF, true);
#endif

#if defined(RCC_APB2_PERIPH_SYSCFG)
    RCC_EnableAPB2Periphs(RCC_APB2_PERIPH_SYSCFG, true);
#endif

    return rt_device_pin_register("pin", &_mm32_pin_ops, RT_NULL);
}

#endif /* RT_USING_PIN */

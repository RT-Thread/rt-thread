/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */

#include <rtthread.h>
#include "rthw.h"

#ifdef RT_USING_PIN
#include "drv_gpio.h"
#include "drv_irq.h"

#define GPIO_PCR_INTE               (0x1000U)
#define PIN_EXINT_OFF               (0U)
#define PIN_EXINT_ON                (GPIO_PCR_INTE)

#define GPIO_PIN_INDEX(pin)             ((en_pin_t)((pin) & 0x0F))
#define GPIO_PORT(pin)                  ((en_port_t)(((pin) >> 4) & 0x0F))
#define GPIO_PIN(pin)                   ((en_pin_t)(0x01U << GPIO_PIN_INDEX(pin)))

#define PIN_NUM(port, pin)              (((((port) & 0x0F) << 4) | ((pin) & 0x0F)))
#define PIN_MAX_NUM                     ((PortH * 16) + (__CLZ(__RBIT(Pin13))) + 1)

#define ITEM_NUM(items)                 sizeof(items) / sizeof(items[0])

static void exint0_irq_handler(void);
static void exint1_irq_handler(void);
static void exint2_irq_handler(void);
static void exint3_irq_handler(void);
static void exint4_irq_handler(void);
static void exint5_irq_handler(void);
static void exint6_irq_handler(void);
static void exint7_irq_handler(void);
static void exint8_irq_handler(void);
static void exint9_irq_handler(void);
static void exint10_irq_handler(void);
static void exint11_irq_handler(void);
static void exint12_irq_handler(void);
static void exint13_irq_handler(void);
static void exint14_irq_handler(void);
static void exint15_irq_handler(void);

struct hc32_pin_irq_map
{
    rt_uint16_t            pinbit;
    struct hc32_irq_config irq_config;
    func_ptr_t             irq_callback;
};

#ifndef HC32_PIN_CONFIG
#define HC32_PIN_CONFIG(pin, irq, src, irq_info)                               \
    {                                                                          \
        .pinbit             = pin,                                             \
        .irq_callback       = irq,                                             \
        .irq_config         = irq_info,                                        \
        .irq_config.int_src = src,                                             \
    }
#endif /* HC32_PIN_CONFIG */

static struct hc32_pin_irq_map pin_irq_map[] =
{
    HC32_PIN_CONFIG(Pin00, exint0_irq_handler,  INT_PORT_EIRQ0,  EXINT0_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin01, exint1_irq_handler,  INT_PORT_EIRQ1,  EXINT1_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin02, exint2_irq_handler,  INT_PORT_EIRQ2,  EXINT2_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin03, exint3_irq_handler,  INT_PORT_EIRQ3,  EXINT3_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin04, exint4_irq_handler,  INT_PORT_EIRQ4,  EXINT4_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin05, exint5_irq_handler,  INT_PORT_EIRQ5,  EXINT5_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin06, exint6_irq_handler,  INT_PORT_EIRQ6,  EXINT6_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin07, exint7_irq_handler,  INT_PORT_EIRQ7,  EXINT7_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin08, exint8_irq_handler,  INT_PORT_EIRQ8,  EXINT8_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin09, exint9_irq_handler,  INT_PORT_EIRQ9,  EXINT9_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin10, exint10_irq_handler, INT_PORT_EIRQ10, EXINT10_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin11, exint11_irq_handler, INT_PORT_EIRQ11, EXINT11_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin12, exint12_irq_handler, INT_PORT_EIRQ12, EXINT12_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin13, exint13_irq_handler, INT_PORT_EIRQ13, EXINT13_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin14, exint14_irq_handler, INT_PORT_EIRQ14, EXINT14_IRQ_CONFIG),
    HC32_PIN_CONFIG(Pin15, exint15_irq_handler, INT_PORT_EIRQ15, EXINT15_IRQ_CONFIG),
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

static void pin_irq_handler(rt_uint16_t pinbit)
{
    rt_int32_t irqindex = -1;

    if (Set == EXINT_GetExIntSrc(pinbit))
    {
        EXINT_ClrExIntSrc(pinbit);
        irqindex = __CLZ(__RBIT(pinbit));
        if (pin_irq_hdr_tab[irqindex].hdr)
        {
            pin_irq_hdr_tab[irqindex].hdr(pin_irq_hdr_tab[irqindex].args);
        }
    }
}

static void exint0_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[0].pinbit);
    rt_interrupt_leave();
}

static void exint1_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[1].pinbit);
    rt_interrupt_leave();
}

static void exint2_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[2].pinbit);
    rt_interrupt_leave();
}

static void exint3_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[3].pinbit);
    rt_interrupt_leave();
}

static void exint4_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[4].pinbit);
    rt_interrupt_leave();
}

static void exint5_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[5].pinbit);
    rt_interrupt_leave();
}

static void exint6_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[6].pinbit);
    rt_interrupt_leave();
}

static void exint7_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[7].pinbit);
    rt_interrupt_leave();
}

static void exint8_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[8].pinbit);
    rt_interrupt_leave();
}

static void exint9_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[9].pinbit);
    rt_interrupt_leave();
}

static void exint10_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[10].pinbit);
    rt_interrupt_leave();
}

static void exint11_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[11].pinbit);
    rt_interrupt_leave();
}

static void exint12_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[12].pinbit);
    rt_interrupt_leave();
}

static void exint13_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[13].pinbit);
    rt_interrupt_leave();
}

static void exint14_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[14].pinbit);
    rt_interrupt_leave();
}

static void exint15_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[15].pinbit);
    rt_interrupt_leave();
}

static void hc32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    en_port_t  gpio_port;
    en_pin_t gpio_pin;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (PIN_LOW == value)
        {
            PORT_ResetBits(gpio_port, gpio_pin);
        }
        else
        {
            PORT_SetBits(gpio_port, gpio_pin);
        }
    }
}

static int hc32_pin_read(rt_device_t dev, rt_base_t pin)
{
    en_port_t  gpio_port;
    en_pin_t gpio_pin;
    int value = PIN_LOW;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (Reset == PORT_GetBit(gpio_port, gpio_pin))
        {
            value = PIN_LOW;
        }
        else
        {
            value = PIN_HIGH;
        }
    }

    return value;
}

static void hc32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    en_port_t  gpio_port;
    en_pin_t gpio_pin;
    stc_port_init_t stcGpioInit;

    if (pin >= PIN_MAX_NUM)
    {
        return;
    }

    MEM_ZERO_STRUCT(stcGpioInit);
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        stcGpioInit.enPinMode   = Pin_Mode_Out;
        stcGpioInit.enPinOType = Pin_OType_Cmos;
        break;
    case PIN_MODE_INPUT:
        stcGpioInit.enPinMode = Pin_Mode_In;
        break;
    case PIN_MODE_INPUT_PULLUP:
        stcGpioInit.enPinMode = Pin_Mode_In;
        stcGpioInit.enPullUp = Enable;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        stcGpioInit.enPinMode = Pin_Mode_In;
        stcGpioInit.enPullUp = Disable;
        break;
    case PIN_MODE_OUTPUT_OD:
        stcGpioInit.enPinMode   = Pin_Mode_Out;
        stcGpioInit.enPinOType = Pin_OType_Od;
        break;
    default:
        break;
    }

    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);
    PORT_Init(gpio_port, gpio_pin, &stcGpioInit);
}

static void gpio_irq_config(uint8_t u8Port, uint16_t u16Pin, uint16_t u16ExInt)
{
    __IO uint16_t *PCRx;
    uint16_t pin_num;
    pin_num = __CLZ(__RBIT(u16Pin));
    PCRx = (__IO uint16_t *)((uint32_t)(&M4_PORT->PCRA0) + ((uint32_t)u8Port * 0x40UL) + (pin_num * 4UL));

    PORT_Unlock();
    MODIFY_REG16(*PCRx, GPIO_PCR_INTE, u16ExInt);
    PORT_Lock();
}
static rt_err_t hc32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    irqindex = GPIO_PIN_INDEX(pin);
    if (irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin  == pin  &&
            pin_irq_hdr_tab[irqindex].hdr  == hdr  &&
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
    pin_irq_hdr_tab[irqindex].pin  = pin;
    pin_irq_hdr_tab[irqindex].hdr  = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hc32_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    irqindex = GPIO_PIN_INDEX(pin);
    if (irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin  = -1;
    pin_irq_hdr_tab[irqindex].hdr  = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hc32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)

{
    struct hc32_pin_irq_map *irq_map;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    en_pin_t gpio_pin;
    stc_exint_config_t stcExintInit;

    if ((pin >= PIN_MAX_NUM) || ((PIN_IRQ_ENABLE != enabled) && (PIN_IRQ_DISABLE != enabled)))
    {
        return -RT_ENOSYS;
    }

    irqindex = GPIO_PIN_INDEX(pin);
    if (irqindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_ENOSYS;
    }

    irq_map  = &pin_irq_map[irqindex];
    gpio_pin = GPIO_PIN(pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_ENOSYS;
        }

        /* Exint config */
        MEM_ZERO_STRUCT(stcExintInit);
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            stcExintInit.enExtiLvl = ExIntRisingEdge;
            break;
        case PIN_IRQ_MODE_FALLING:
            stcExintInit.enExtiLvl = ExIntFallingEdge;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            stcExintInit.enExtiLvl = ExIntBothEdge;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            stcExintInit.enExtiLvl = ExIntLowLevel;
            break;
        }
        stcExintInit.enExitCh    = (en_exti_ch_t)irqindex;//gpio_pin;
        stcExintInit.enFilterEn   = Enable;
        stcExintInit.enFltClk = Pclk3Div8;
        EXINT_Init(&stcExintInit);
        /* IRQ sign-in */
        hc32_install_irq_handler(&irq_map->irq_config, irq_map->irq_callback, RT_FALSE);
        NVIC_EnableIRQ(irq_map->irq_config.irq);
        gpio_irq_config(GPIO_PORT(pin), gpio_pin, PIN_EXINT_ON);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        level = rt_hw_interrupt_disable();
        gpio_irq_config(GPIO_PORT(pin), gpio_pin, PIN_EXINT_OFF);
        NVIC_DisableIRQ(irq_map->irq_config.irq);

        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

static const struct rt_pin_ops pin_ops =
{
    hc32_pin_mode,
    hc32_pin_write,
    hc32_pin_read,
    hc32_pin_attach_irq,
    hc32_pin_detach_irq,
    hc32_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif  /* RT_USING_PIN */



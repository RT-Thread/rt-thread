/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2023-10-09     CDT          support HC32F448
 */

#include <rtthread.h>
#include <rthw.h>
#include "drv_gpio.h"
#include "board_config.h"

#if defined(RT_USING_PIN)

#if defined(BSP_USING_GPIO)

#define GPIO_PIN_INDEX(pin)             ((uint8_t)((pin) & 0x0F))
#define PIN_NUM(port, pin)              (((((port) & 0x0F) << 4) | ((pin) & 0x0F)))
#define GPIO_PORT(pin)                  ((uint8_t)(((pin) >> 4) & 0x0F))
#define GPIO_PIN(pin)                   ((uint16_t)(0x01U << GPIO_PIN_INDEX(pin)))

#if defined (HC32F4A0)
    #define PIN_MAX_NUM                     ((GPIO_PORT_I * 16) + (__CLZ(__RBIT(GPIO_PIN_13))) + 1)
#elif defined (HC32F460)
    #define PIN_MAX_NUM                     ((GPIO_PORT_H * 16) + (__CLZ(__RBIT(GPIO_PIN_02))) + 1)
#elif defined (HC32F448)
    #define PIN_MAX_NUM                     ((GPIO_PORT_H * 16) + (__CLZ(__RBIT(GPIO_PIN_02))) + 1)
#elif defined (HC32F472)
    #define PIN_MAX_NUM                     ((GPIO_PORT_F * 16) + (__CLZ(__RBIT(GPIO_PIN_08))) + 1)
#endif

#define ITEM_NUM(items)                 sizeof(items) / sizeof(items[0])

#ifndef HC32_PIN_CONFIG
#define HC32_PIN_CONFIG(pin, callback, config)                                 \
    {                                                                          \
        .pinbit             = pin,                                             \
        .irq_callback       = callback,                                        \
        .irq_config         = config,                                          \
    }
#endif /* HC32_PIN_CONFIG */

static void extint0_irq_handler(void);
static void extint1_irq_handler(void);
static void extint2_irq_handler(void);
static void extint3_irq_handler(void);
static void extint4_irq_handler(void);
static void extint5_irq_handler(void);
static void extint6_irq_handler(void);
static void extint7_irq_handler(void);
static void extint8_irq_handler(void);
static void extint9_irq_handler(void);
static void extint10_irq_handler(void);
static void extint11_irq_handler(void);
static void extint12_irq_handler(void);
static void extint13_irq_handler(void);
static void extint14_irq_handler(void);
static void extint15_irq_handler(void);

static struct hc32_pin_irq_map pin_irq_map[] =
{
    HC32_PIN_CONFIG(GPIO_PIN_00, extint0_irq_handler,  EXTINT0_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_01, extint1_irq_handler,  EXTINT1_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_02, extint2_irq_handler,  EXTINT2_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_03, extint3_irq_handler,  EXTINT3_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_04, extint4_irq_handler,  EXTINT4_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_05, extint5_irq_handler,  EXTINT5_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_06, extint6_irq_handler,  EXTINT6_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_07, extint7_irq_handler,  EXTINT7_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_08, extint8_irq_handler,  EXTINT8_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_09, extint9_irq_handler,  EXTINT9_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_10, extint10_irq_handler, EXTINT10_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_11, extint11_irq_handler, EXTINT11_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_12, extint12_irq_handler, EXTINT12_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_13, extint13_irq_handler, EXTINT13_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_14, extint14_irq_handler, EXTINT14_IRQ_CONFIG),
    HC32_PIN_CONFIG(GPIO_PIN_15, extint15_irq_handler, EXTINT15_IRQ_CONFIG),
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

    if (SET == EXTINT_GetExtIntStatus(pinbit))
    {
        EXTINT_ClearExtIntStatus(pinbit);
        irqindex = __CLZ(__RBIT(pinbit));
        if (pin_irq_hdr_tab[irqindex].hdr)
        {
            pin_irq_hdr_tab[irqindex].hdr(pin_irq_hdr_tab[irqindex].args);
        }
    }
}

static void extint0_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[0].pinbit);
    rt_interrupt_leave();
}

static void extint1_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[1].pinbit);
    rt_interrupt_leave();
}

static void extint2_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[2].pinbit);
    rt_interrupt_leave();
}

static void extint3_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[3].pinbit);
    rt_interrupt_leave();
}

static void extint4_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[4].pinbit);
    rt_interrupt_leave();
}

static void extint5_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[5].pinbit);
    rt_interrupt_leave();
}

static void extint6_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[6].pinbit);
    rt_interrupt_leave();
}

static void extint7_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[7].pinbit);
    rt_interrupt_leave();
}

static void extint8_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[8].pinbit);
    rt_interrupt_leave();
}

static void extint9_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[9].pinbit);
    rt_interrupt_leave();
}

static void extint10_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[10].pinbit);
    rt_interrupt_leave();
}

static void extint11_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[11].pinbit);
    rt_interrupt_leave();
}

static void extint12_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[12].pinbit);
    rt_interrupt_leave();
}

static void extint13_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[13].pinbit);
    rt_interrupt_leave();
}

static void extint14_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[14].pinbit);
    rt_interrupt_leave();
}

static void extint15_irq_handler(void)
{
    rt_interrupt_enter();
    pin_irq_handler(pin_irq_map[15].pinbit);
    rt_interrupt_leave();
}

static void hc32_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    stc_gpio_init_t stcGpioInit;

    if (pin >= PIN_MAX_NUM)
    {
        return;
    }

    GPIO_StructInit(&stcGpioInit);
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        stcGpioInit.u16PinDir        = PIN_DIR_OUT;
        stcGpioInit.u16PinOutputType = PIN_OUT_TYPE_CMOS;
        break;
    case PIN_MODE_INPUT:
        stcGpioInit.u16PinDir   = PIN_DIR_IN;
        break;
    case PIN_MODE_INPUT_PULLUP:
        stcGpioInit.u16PinDir   = PIN_DIR_IN;
        stcGpioInit.u16PullUp   = PIN_PU_ON;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        stcGpioInit.u16PinDir   = PIN_DIR_IN;
        stcGpioInit.u16PullUp   = PIN_PU_OFF;
#if defined (HC32F448) || defined (HC32F472)
        stcGpioInit.u16PullDown = PIN_PD_ON;
#endif
        break;
    case PIN_MODE_OUTPUT_OD:
        stcGpioInit.u16PinDir        = PIN_DIR_OUT;
        stcGpioInit.u16PinOutputType = PIN_OUT_TYPE_NMOS;
        break;
    default:
        break;
    }
    GPIO_Init(GPIO_PORT(pin), GPIO_PIN(pin), &stcGpioInit);
}

static void hc32_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    uint8_t  gpio_port;
    uint16_t gpio_pin;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (PIN_LOW == value)
        {
            GPIO_ResetPins(gpio_port, gpio_pin);
        }
        else
        {
            GPIO_SetPins(gpio_port, gpio_pin);
        }
    }
}

static rt_ssize_t hc32_pin_read(struct rt_device *device, rt_base_t pin)
{
    uint8_t  gpio_port;
    uint16_t gpio_pin;
    int value = PIN_LOW;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (PIN_RESET == GPIO_ReadInputPins(gpio_port, gpio_pin))
        {
            value = PIN_LOW;
        }
        else
        {
            value = PIN_HIGH;
        }
    }
    else
    {
        return -RT_EINVAL;
    }

    return value;
}

static rt_err_t hc32_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
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
        return -RT_ENOSYS;
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
        return -RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin  = pin;
    pin_irq_hdr_tab[irqindex].hdr  = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hc32_pin_detach_irq(struct rt_device *device, rt_base_t pin)
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
        return -RT_ENOSYS;
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

static void gpio_irq_config(uint8_t u8Port, uint16_t u16Pin, uint16_t u16ExInt)
{
    __IO uint16_t *PCRx;
    uint16_t pin_num;

    pin_num = __CLZ(__RBIT(u16Pin));
    PCRx = (__IO uint16_t *)((uint32_t)(&CM_GPIO->PCRA0) + ((uint32_t)u8Port * 0x40UL) + (pin_num * 4UL));
    MODIFY_REG16(*PCRx, GPIO_PCR_INTE, u16ExInt);
}

static rt_err_t hc32_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    struct hc32_pin_irq_map *irq_map;
    rt_base_t level;
    rt_int32_t irqindex = -1;
    stc_extint_init_t stcExtIntInit;
    uint8_t  gpio_port;
    uint16_t gpio_pin;

    if ((pin >= PIN_MAX_NUM) || ((PIN_IRQ_ENABLE != enabled) && (PIN_IRQ_DISABLE != enabled)))
    {
        return -RT_ENOSYS;
    }
    irqindex = GPIO_PIN_INDEX(pin);
    if (irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    irq_map  = &pin_irq_map[irqindex];
    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        /* Exint config */
        EXTINT_StructInit(&stcExtIntInit);
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            stcExtIntInit.u32Edge = EXTINT_TRIG_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            stcExtIntInit.u32Edge = EXTINT_TRIG_FALLING;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            stcExtIntInit.u32Edge = EXTINT_TRIG_BOTH;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            stcExtIntInit.u32Edge = EXTINT_TRIG_LOW;
            break;
        }
        EXTINT_Init(gpio_pin, &stcExtIntInit);
        NVIC_EnableIRQ(irq_map->irq_config.irq_num);
        gpio_irq_config(gpio_port, gpio_pin, PIN_EXTINT_ON);
    }
    else
    {
        level = rt_hw_interrupt_disable();
        gpio_irq_config(gpio_port, gpio_pin, PIN_EXTINT_OFF);
        NVIC_DisableIRQ(irq_map->irq_config.irq_num);
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_base_t hc32_pin_get(const char *name)
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

static const struct rt_pin_ops hc32_pin_ops =
{
    hc32_pin_mode,
    hc32_pin_write,
    hc32_pin_read,
    hc32_pin_attach_irq,
    hc32_pin_detach_irq,
    hc32_pin_irq_enable,
    hc32_pin_get,
};

int rt_hw_pin_init(void)
{
    uint8_t u32MaxExtInt;

    /* register extint */
    u32MaxExtInt = ITEM_NUM(pin_irq_map);
    for (uint8_t i = 0; i < u32MaxExtInt; i++)
    {
        hc32_install_irq_handler(&pin_irq_map[i].irq_config, pin_irq_map[i].irq_callback, RT_FALSE);
    }

    return rt_device_pin_register("pin", &hc32_pin_ops, RT_NULL);
}

#endif

#endif  /* RT_USING_PIN */

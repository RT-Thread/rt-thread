/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */

#include <rtthread.h>
#include "rthw.h"

#ifdef RT_USING_PIN
#include "gpio.h"
#include "drv_gpio.h"
#include "interrupts_hc32l136.h"

#define GPIO_PIN_INDEX(pin)             ((uint8_t)((pin) & 0x0F))
#define GPIO_PORT(pin)                  ((uint8_t)(((pin) >> 4) * 0x40u))
#define GPIO_PIN(pin)                   ((uint16_t)(GPIO_PIN_INDEX(pin)))

#define PIN_NUM(port, pin)              (((((port) / 0x40u) << 4) | ((pin) & 0x0F)))
#define PIN_MAX_NUM                     ((GpioPortD / 0x40u * 16) + (GpioPin15 + 1))

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

static void pin_irq_handler(en_gpio_port_t port, en_gpio_pin_t pin)
{
    rt_int32_t irqindex = -1;

    irqindex = PIN_NUM(port, pin);
    if (pin_irq_hdr_tab[irqindex].hdr)
    {
        pin_irq_hdr_tab[irqindex].hdr(pin_irq_hdr_tab[irqindex].args);
    }
}

void Gpio_IRQHandler(uint8_t u8Param)
{
    en_gpio_pin_t i;
    en_gpio_port_t enPort;

    enPort = (en_gpio_port_t)(GpioPortA + (GpioPortB - GpioPortA) * u8Param);
    rt_interrupt_enter();
    for (i=GpioPin0; i<=GpioPin15; i++)
    {
        if(TRUE == Gpio_GetIrqStatus(enPort, i))
        {
            Gpio_ClearIrq(enPort, i);
            pin_irq_handler(enPort, i);
        }

    }
    rt_interrupt_leave();
}

static void _pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    uint8_t  gpio_port;
    uint16_t gpio_pin;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (PIN_LOW == value)
        {
            Gpio_WriteOutputIO((en_gpio_port_t)gpio_port, (en_gpio_pin_t)gpio_pin, FALSE);
        }
        else
        {
            Gpio_WriteOutputIO((en_gpio_port_t)gpio_port, (en_gpio_pin_t)gpio_pin, TRUE);
        }
    }
}

static rt_ssize_t _pin_read(rt_device_t dev, rt_base_t pin)
{
    uint8_t  gpio_port;
    uint16_t gpio_pin;
    rt_ssize_t value = PIN_LOW;

    if (pin < PIN_MAX_NUM)
    {
        gpio_port = GPIO_PORT(pin);
        gpio_pin  = GPIO_PIN(pin);
        if (FALSE == Gpio_GetInputIO((en_gpio_port_t)gpio_port, (en_gpio_pin_t)gpio_pin))
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
        value = -RT_EINVAL;
    }

    return value;
}

static void _pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    uint8_t  gpio_port;
    uint16_t gpio_pin;
    stc_gpio_config_t pstcGpioCfg;

    memset(&pstcGpioCfg, 0, sizeof(pstcGpioCfg));
    if (pin >= PIN_MAX_NUM)
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        pstcGpioCfg.enDir = GpioDirOut;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        break;
    case PIN_MODE_INPUT:
        pstcGpioCfg.enDir = GpioDirIn;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enPuPd = GpioPu;
        pstcGpioCfg.enOD = GpioOdDisable;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        break;
    case PIN_MODE_INPUT_PULLUP:
        pstcGpioCfg.enDir = GpioDirIn;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enPuPd = GpioPu;
        pstcGpioCfg.enOD = GpioOdDisable;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        pstcGpioCfg.enDir = GpioDirIn;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enPuPd = GpioPd;
        pstcGpioCfg.enOD = GpioOdDisable;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        break;
    case PIN_MODE_OUTPUT_OD:
        pstcGpioCfg.enDir = GpioDirOut;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enOD = GpioOdEnable;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        break;
    default:
        break;
    }
    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);
    Gpio_Init((en_gpio_port_t)gpio_port, (en_gpio_pin_t)gpio_pin, &pstcGpioCfg);
}

static rt_err_t _pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                    rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    irqindex = pin;
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

static rt_err_t _pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    irqindex = pin;
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

static rt_err_t _pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_base_t level;
    en_gpio_port_t gpio_port;
    en_gpio_pin_t gpio_pin;
    rt_int32_t irqindex;
    stc_gpio_config_t pstcGpioCfg;

    if ((pin >= PIN_MAX_NUM) || ((PIN_IRQ_ENABLE != enabled) && (PIN_IRQ_DISABLE != enabled)))
    {
        return -RT_ENOSYS;
    }

    irqindex = pin;
    gpio_port = (en_gpio_port_t)GPIO_PORT(pin);
    gpio_pin  = (en_gpio_pin_t)GPIO_PIN(pin);
    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        /* Exint config */
        pstcGpioCfg.enDir = GpioDirIn;
        pstcGpioCfg.enDrv = GpioDrvL;
        pstcGpioCfg.enPuPd = GpioPu;
        pstcGpioCfg.enOD = GpioOdDisable;
        pstcGpioCfg.enCtrlMode = GpioAHB;
        Gpio_Init(gpio_port, gpio_pin, &pstcGpioCfg);
        Gpio_ClearIrq(gpio_port, gpio_pin);

        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqRising);
            break;
        case PIN_IRQ_MODE_FALLING:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqHigh);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqLow);
            break;
        }
        EnableNvic((IRQn_Type)(pin / 16), IrqLevel3, TRUE);

        rt_hw_interrupt_enable(level);
    }
    else
    {
        level = rt_hw_interrupt_disable();
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqRising);
            break;
        case PIN_IRQ_MODE_FALLING:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:

            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqLow);
            break;
        }
        rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

static const struct rt_pin_ops _pin_ops =
{
    _pin_mode,
    _pin_write,
    _pin_read,
    _pin_attach_irq,
    _pin_detach_irq,
    _pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

    return rt_device_pin_register("pin", &_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif  /* RT_USING_PIN */

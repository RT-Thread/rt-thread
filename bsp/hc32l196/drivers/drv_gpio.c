/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-05     DongBowen    first version
 */

#include <rtthread.h>
#include "rthw.h"

#include "drv_gpio.h"
#include "hc32l196_sysctrl.h"

#ifdef RT_USING_PIN
#ifdef BSP_USING_GPIO

#define __GPIO_PORT(pin)                (((pin) & 0xf0) * 4)
#define __GPIO_PORT_L(pin)              (__GPIO_PORT(pin))
#define __GPIO_PORT_H(pin)              ((__GPIO_PORT(pin) & 0xff) + 0x1000)
#define PE0_PIN                         (4 * 15)
#define GPIO_PORT(pin)                  (en_gpio_port_t)((pin) < PE0_PIN ? __GPIO_PORT_L((pin)) : __GPIO_PORT_H((pin)))
#define GPIO_PIN(pin)                   (en_gpio_pin_t)((pin) & 0x0f)

/* Port: PA-PF, Pin: 0-15 */
#define PIN_MAX_NUM                     (6 * 16)

#define ITEM_NUM(items)                 sizeof(items) / sizeof(items[0])

static struct rt_pin_irq_hdr pin_irq_hdr_tab[PIN_MAX_NUM];

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static void _pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    en_gpio_port_t gpio_port;
    en_gpio_pin_t gpio_pin;
    stc_gpio_cfg_t gpio_cfg;

    if (pin >= PIN_MAX_NUM)
    {
        return;
    }

    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);

    gpio_cfg.bOutputVal = 0;
    gpio_cfg.enDrv = GpioDrvH;
    gpio_cfg.enPu = GpioPuDisable;
    gpio_cfg.enPd = GpioPdDisable;
    gpio_cfg.enOD = GpioOdDisable;
    gpio_cfg.enCtrlMode = GpioAHB;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_cfg.enDir = GpioDirOut;
        break;
    case PIN_MODE_INPUT:
        gpio_cfg.enDir = GpioDirIn;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_cfg.enDir = GpioDirIn;
        gpio_cfg.enPu = GpioPuEnable;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_cfg.enDir = GpioDirIn;
        gpio_cfg.enPd = GpioPdEnable;
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_cfg.enDir = GpioDirOut;
        gpio_cfg.enOD = GpioOdEnable;
        break;
    default:
        break;
    }

    Gpio_Init(gpio_port, gpio_pin, &gpio_cfg);
}

static void _pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    en_gpio_port_t gpio_port;
    en_gpio_pin_t gpio_pin;

    if (pin >= PIN_MAX_NUM)
    {
        return;
    }

    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);

    if (PIN_LOW == value)
    {
        Gpio_ClrIO(gpio_port, gpio_pin);
    }
    else
    {
        Gpio_SetIO(gpio_port, gpio_pin);
    }
}

static rt_int8_t _pin_read(rt_device_t dev, rt_base_t pin)
{
    en_gpio_port_t gpio_port;
    en_gpio_pin_t gpio_pin;

    if (pin >= PIN_MAX_NUM)
    {
        return PIN_LOW;
    }

    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);

    return Gpio_GetInputIO(gpio_port, gpio_pin) ? PIN_HIGH : PIN_LOW;
}

static rt_err_t _pin_attach_irq(struct rt_device *device,
                                    rt_base_t pin,
                                    rt_uint8_t mode,
                                    void (*hdr)(void *args),
                                    void *args)
{
    rt_base_t level;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[pin].pin == pin &&
            pin_irq_hdr_tab[pin].mode == mode &&
            pin_irq_hdr_tab[pin].hdr == hdr &&
            pin_irq_hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[pin].pin = pin;
    pin_irq_hdr_tab[pin].mode = mode;
    pin_irq_hdr_tab[pin].hdr = hdr;
    pin_irq_hdr_tab[pin].args = args;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static rt_err_t _pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[pin].mode = 0;
    pin_irq_hdr_tab[pin].hdr = RT_NULL;
    pin_irq_hdr_tab[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static IRQn_Type get_irqn(rt_base_t pin)
{
    en_gpio_port_t gpio_port;
    IRQn_Type irqn = (IRQn_Type)0xff;

    if (pin >= PIN_MAX_NUM)
    {
        return irqn;
    }

    gpio_port = GPIO_PORT(pin);
    switch (gpio_port)
    {
    case GpioPortA:
        irqn = PORTA_IRQn;
        break;
    case GpioPortB:
        irqn = PORTB_IRQn;
        break;
    case GpioPortC:
    case GpioPortE:
        irqn = PORTC_E_IRQn;
        break;
    case GpioPortD:
    case GpioPortF:
        irqn = PORTD_F_IRQn;
        break;
    }

    return irqn;
}

static rt_err_t _pin_irq_enable(struct rt_device *device,
                                    rt_base_t pin,
                                    rt_uint8_t enabled)
{
    rt_base_t level = 0;
    en_gpio_port_t gpio_port;
    en_gpio_pin_t gpio_pin;
    IRQn_Type irqn;

    if (pin >= PIN_MAX_NUM)
    {
        return -RT_ENOSYS;
    }

    gpio_port = GPIO_PORT(pin);
    gpio_pin  = GPIO_PIN(pin);
    irqn = get_irqn(pin);

    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (pin_irq_hdr_tab[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqRising);
            break;
        case PIN_IRQ_MODE_FALLING:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqRising);
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqHigh);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            Gpio_EnableIrq(gpio_port, gpio_pin, GpioIrqLow);
            break;
        default:
            return -RT_EINVAL;
        }

        level = rt_hw_interrupt_disable();
        NVIC_ClearPendingIRQ(irqn);
        NVIC_EnableIRQ(irqn);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        switch (pin_irq_hdr_tab[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqRising);
            break;
        case PIN_IRQ_MODE_FALLING:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqRising);
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqFalling);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqHigh);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            Gpio_DisableIrq(gpio_port, gpio_pin, GpioIrqLow);
            break;
        default:
            break;
        }

        level = rt_hw_interrupt_disable();
        NVIC_ClearPendingIRQ(irqn);
        NVIC_DisableIRQ(irqn);
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _pin_ops =
{
    .pin_mode = _pin_mode,
    .pin_write = _pin_write,
    .pin_read = _pin_read,
    .pin_attach_irq = _pin_attach_irq,
    .pin_detach_irq = _pin_detach_irq,
    .pin_irq_enable = _pin_irq_enable,
};

static void pin_isr(en_gpio_port_t gpio_port)
{
    en_gpio_pin_t gpio_pin = GpioPin0;
    int pin = __GET_PIN(gpio_port, 0);

    for (; gpio_pin <= GpioPin15; gpio_pin++, pin++)
    {
        if (Gpio_GetIrqStatus(gpio_port, gpio_pin))
        {
            if (pin_irq_hdr_tab[pin].hdr)
            {
                pin_irq_hdr_tab[pin].hdr(pin_irq_hdr_tab[pin].args);
            }
            Gpio_ClearIrq(gpio_port, gpio_pin);
        }
    }
}

void PortA_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortA);
    rt_interrupt_leave();
}

void PortB_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortB);
    rt_interrupt_leave();
}

void PortC_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortC);
    rt_interrupt_leave();
}

void PortD_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortD);
    rt_interrupt_leave();
}

void PortE_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortE);
    rt_interrupt_leave();
}

void PortF_IRQHandler(void)
{
    rt_interrupt_enter();
    pin_isr(GpioPortF);
    rt_interrupt_leave();
}

int rt_hw_pin_init(void)
{
    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
    return rt_device_pin_register("pin", &_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
#endif /* RT_USING_PIN */

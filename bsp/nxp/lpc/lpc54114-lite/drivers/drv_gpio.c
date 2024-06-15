/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-30     yangjie      The first version for LPC54114
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "fsl_gpio.h"
#include "LPC54114_cm4.h"
#include "core_cm4.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"
#include "fsl_iocon.h"

#ifdef RT_USING_PIN

#define get_port(x)      (x / 32)
#define get_pin(x)       (x % 32)
#define PIN_MAX_VAL            63
#define IRQ_MAX_VAL             8

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

static rt_base_t lpc_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len = 1;
    int mul = 1;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= '0') && (name[1] <= '9'))
    {
        hw_port_num = (int)(name[1] - '0');
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = name_len - 1; i > 2; i--)
    {
        hw_pin_num += ((int)(name[i] - '0') * mul);
        mul = mul * 10;
    }

    pin = 32 * hw_port_num + hw_pin_num;

    if ((pin > PIN_MAX_VAL) || (pin < 0))
    {
        return -RT_EINVAL;
    }
    return pin;
}

/* Configure pin mode. pin 0~63 means PIO0_0 ~ PIO1_31 */
static void lpc_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    int portx, piny, dir;
    uint32_t pin_cfg;

    if(pin > PIN_MAX_VAL)
        return;

    portx = get_port(pin);
    piny  = get_pin(pin);

    switch(mode)
    {
    case PIN_MODE_OUTPUT:
        dir = kGPIO_DigitalOutput;
        pin_cfg = IOCON_FUNC0 | IOCON_DIGITAL_EN;
        break;
    case PIN_MODE_OUTPUT_OD:
        dir = kGPIO_DigitalOutput;
        pin_cfg = IOCON_FUNC0 | IOCON_OPENDRAIN_EN | IOCON_DIGITAL_EN;
        break;

    case PIN_MODE_INPUT:
        dir = kGPIO_DigitalInput;
        pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN;
        break;
    case PIN_MODE_INPUT_PULLUP:
        dir = kGPIO_DigitalInput;
        pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN | IOCON_MODE_PULLUP;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        dir = kGPIO_DigitalInput;
        pin_cfg = IOCON_FUNC0 | IOCON_INPFILT_OFF | IOCON_DIGITAL_EN | IOCON_MODE_PULLDOWN;
        break;
    default: break;
    }

    CLOCK_EnableClock(kCLOCK_Iocon);

    IOCON_PinMuxSet(IOCON, portx, piny, pin_cfg);
    GPIO_PortInit(GPIO, portx);

    gpio_pin_config_t pin_config = {(gpio_pin_direction_t)dir, 0};
    GPIO_PinInit(GPIO, portx, piny, &pin_config);

    CLOCK_DisableClock(kCLOCK_Iocon);
}

static void lpc_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    int portx, piny;
    portx = get_port(pin);
    piny  = get_pin(pin);

    if(pin > PIN_MAX_VAL)
       return;

    GPIO_PinWrite(GPIO, portx, piny, value);
}

static rt_ssize_t lpc_pin_read(rt_device_t dev, rt_base_t pin)
{
    int  portx, piny;
    rt_ssize_t value;

    if(pin > PIN_MAX_VAL)
    {
        return -RT_EINVAL;
    }

    portx = get_port(pin);
    piny  = get_pin(pin);

    value = (rt_ssize_t)(GPIO_PinRead(GPIO, portx, piny));

    return value;
}

static void pin_irq_hdr(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    int irqno = 0;
    for(irqno = 0; irqno < IRQ_MAX_VAL; irqno ++)
    {
        if((irqno) == pintr)
        {
            break;
        }
    }

    if(irqno >= IRQ_MAX_VAL)
        return;

    if (pin_irq_hdr_tab[irqno].hdr)
    {
        pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}

void callback(pint_pin_int_t pintr, uint32_t pmatch_status)
{
    pin_irq_hdr(pintr, pmatch_status);
}

static rt_err_t lpc_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    int portx, piny, trigger_mode, pin_initx, pintsel, pin_cfg, i;

    if(pin > PIN_MAX_VAL)
        return -RT_ERROR;

    portx = get_port(pin);
    piny  = get_pin(pin);

    switch (mode)
        {
        case PIN_IRQ_MODE_RISING:
            trigger_mode = kPINT_PinIntEnableRiseEdge;
            break;
        case PIN_IRQ_MODE_FALLING:
            trigger_mode = kPINT_PinIntEnableFallEdge;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            trigger_mode = kPINT_PinIntEnableBothEdges;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            trigger_mode = kPINT_PinIntEnableHighLevel;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            trigger_mode = kPINT_PinIntEnableLowLevel;
            break;
        }

    /* Get inputmux_connection_t */
    pintsel = (pin + (0xC0U << 20));

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == -1)
        {
            pin_initx = kPINT_PinInt0 + i;
            pin_irq_hdr_tab[i].pin = pin;
            pin_irq_hdr_tab[i].mode = trigger_mode;
            pin_irq_hdr_tab[i].hdr = hdr;
            pin_irq_hdr_tab[i].args = args;
            break;
        }
    }

    if(i >= IRQ_MAX_VAL)
        return -RT_ERROR;

    /* open clk */
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Iocon);

    /* AttachSignal */
    INPUTMUX_AttachSignal(INPUTMUX, i, (inputmux_connection_t)pintsel);
    pin_cfg = ((IOCON->PIO[portx][piny] &
              (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_FILTEROFF_MASK))) /* Mask bits to zero which are setting */
              | IOCON_PIO_FUNC(0)                /* Selects pin function.: PORT18 (pin 28) is configured as PIO1_8 */
              | IOCON_PIO_DIGIMODE(1)            /* Select Analog/Digital mode.: Digital mode. */
              | IOCON_PIO_FILTEROFF(0));         /* Controls input glitch filter.: Filter enabled. Noise pulses below approximately 10 ns are filtered out. */

    IOCON_PinMuxSet(IOCON, portx, piny, pin_cfg);

    /* PINT_PinInterruptConfig */
    PINT_PinInterruptConfig(PINT, (pint_pin_int_t)pin_initx, (pint_pin_enable_t)(pin_irq_hdr_tab[i].mode), callback);

    CLOCK_DisableClock(kCLOCK_InputMux);
    CLOCK_DisableClock(kCLOCK_Iocon);

    return RT_EOK;
}

static rt_err_t lpc_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    int i;

    if(pin > PIN_MAX_VAL)
        return -RT_ERROR;

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            pin_irq_hdr_tab[i].pin = -1;
            pin_irq_hdr_tab[i].hdr = RT_NULL;
            pin_irq_hdr_tab[i].mode = 0;
            pin_irq_hdr_tab[i].args = RT_NULL;
            break;
        }
    }
    return RT_EOK;
}

static rt_err_t lpc_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                   rt_uint8_t enabled)
{
    int irqn_type, i;

    if(pin > PIN_MAX_VAL)
        return -RT_ERROR;

    for(i = 0; i < IRQ_MAX_VAL; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            switch(i)
            {
                case 0: irqn_type = PIN_INT0_IRQn; break;
                case 1: irqn_type = PIN_INT1_IRQn; break;
                case 2: irqn_type = PIN_INT2_IRQn; break;
                case 3: irqn_type = PIN_INT3_IRQn; break;
                case 4: irqn_type = PIN_INT4_IRQn; break;
                case 5: irqn_type = PIN_INT5_IRQn; break;
                case 6: irqn_type = PIN_INT6_IRQn; break;
                case 7: irqn_type = PIN_INT7_IRQn; break;
                default:break;
            }
            if(enabled)
            {
                /* PINT_EnableCallback */
                PINT_PinInterruptClrStatusAll(PINT);
                NVIC_ClearPendingIRQ((IRQn_Type)irqn_type);
                PINT_PinInterruptClrStatus(PINT, (pint_pin_int_t)(kPINT_PinInt0 + i));
                EnableIRQ((IRQn_Type)irqn_type);
            }
            else
            {
                /* PINT_DisableCallback */
                DisableIRQ((IRQn_Type)irqn_type);
                PINT_PinInterruptClrStatus(PINT, (pint_pin_int_t)(kPINT_PinInt0 + i));
                NVIC_ClearPendingIRQ((IRQn_Type)irqn_type);
            }
            break;
        }
    }

    if(i >= IRQ_MAX_VAL)
        return -RT_ERROR;

      return RT_EOK;
}

const static struct rt_pin_ops _lpc_pin_ops =
{
    lpc_pin_mode,
    lpc_pin_write,
    lpc_pin_read,
    lpc_pin_attach_irq,
    lpc_pin_detach_irq,
    lpc_pin_irq_enable,
    lpc_pin_get,
};

int rt_hw_pin_init(void)
{
    int result;
    PINT_Init(PINT);
    result = rt_device_pin_register("pin", &_lpc_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif

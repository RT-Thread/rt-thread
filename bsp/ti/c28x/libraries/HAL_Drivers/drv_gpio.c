/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-28     qiyu     first version
 */
#include <rthw.h>
#include "drv_gpio.h"
#include "F2837xD_device.h"
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#ifdef RT_USING_PIN

// the gpio pin number for each port is 32, while it is 16 for ARM
#define PIN_NUM(port, no) (((((port) & 0xFu) << 5) | ((no) & 0x1F)))
#define PIN_PORT(pin) ((rt_uint16_t)(((pin) >> 5) & 0xFu))
#define PIN_NO(pin) ((rt_uint16_t)((pin) & 0x1Fu))

#define PIN_c28x_PORT(pin) (volatile Uint32 *)&GpioDataRegs + (PIN_PORT(pin))*GPY_DATA_OFFSET
#define PIN_c28x_PIN(pin) ((rt_uint32_t)(1u << PIN_NO(pin)))

#define PIN_c28x_PORT_MAX 6 /* gpioA to GPIOF in total*/
#define PIN_IRQ_MAX 5   /* XINT1 to XINT5 in total */

static rt_err_t c28x_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args);
static rt_err_t c28x_pin_dettach_irq(struct rt_device *device, rt_base_t pin);
static rt_err_t c28x_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled);

static rt_base_t c28x_pin_get(const char *name)
{
    int hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 3) || (name_len >= 7))
    {
        return -RT_EINVAL;
    }
    /*
     * PX.y
     */
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }
    return hw_pin_num;
}

static void c28x_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    volatile Uint32 *gpioDataReg;
    Uint32 pinMask;
    if (PIN_PORT(pin) < PIN_c28x_PORT_MAX)
    {
        gpioDataReg = PIN_c28x_PORT(pin);
        pinMask = 1UL << (PIN_NO(pin));
        if (value == 0)
        {
            gpioDataReg[GPYCLEAR] = pinMask;
        }
        else
        {
            gpioDataReg[GPYSET] = pinMask;
        }
    }
}

static rt_ssize_t c28x_pin_read(rt_device_t dev, rt_base_t pin)
{
    volatile Uint32 *gpioDataReg;
    rt_ssize_t value = PIN_LOW;

    if (PIN_PORT(pin) < PIN_c28x_PORT_MAX)
    {
        gpioDataReg = PIN_c28x_PORT(pin);
        value = (gpioDataReg[GPYDAT] >> PIN_NO(pin)) & 0x1;
    }

    return value;
}

static void c28x_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    volatile Uint32 *gpioBaseAddr;
    volatile Uint32 *dir, *pud, *odr;
    if (PIN_PORT(pin) >= PIN_c28x_PORT_MAX)
    {
        return;
    }
    rt_uint32_t pinMask;
    pinMask = 1UL << PIN_NO(pin);
    gpioBaseAddr = (Uint32 *)&GpioCtrlRegs + (PIN_PORT(pin))*GPY_CTRL_OFFSET;

    dir = gpioBaseAddr + GPYDIR;
    pud = gpioBaseAddr + GPYPUD;
    odr = gpioBaseAddr + GPYODR;

    EALLOW;
    if (mode == PIN_MODE_OUTPUT)
    {
        *dir |= pinMask;
    }
    else if (mode == PIN_MODE_INPUT)
    {
        *dir &= ~pinMask;
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        *dir &= ~pinMask;
        *pud &= ~pinMask;
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        *dir &= ~pinMask;
        *pud |= pinMask;
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        *dir |= pinMask;
        *odr |= pinMask;
    }
    EDIS;
}

const static struct rt_pin_ops _c28x_pin_ops =
{
    c28x_pin_mode,
    c28x_pin_write,
    c28x_pin_read,
    c28x_pin_attach_irq,
    c28x_pin_dettach_irq,
    c28x_pin_irq_enable,
    c28x_pin_get,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_c28x_pin_ops, RT_NULL);
}

static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

static rt_int16_t pin_irq_xint_tab[] =
{
    BSP_XINT1_PIN,
    BSP_XINT2_PIN,
    BSP_XINT3_PIN,
    BSP_XINT4_PIN,
    BSP_XINT5_PIN
};
rt_inline rt_int32_t get_irq_index(rt_uint32_t pin)
{
    int i;
    for(i = 0 ; i < PIN_IRQ_MAX ; i++)
    {
        if(pin_irq_xint_tab[i] == pin)
        {
            return i;
        }
    }
    return -1;
}

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static rt_err_t c28x_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;

    if (PIN_PORT(pin) >= PIN_c28x_PORT_MAX)
    {
        return -RT_ENOSYS;
    }
    irqindex = get_irq_index(pin);
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

static rt_err_t c28x_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;
    rt_uint16_t i;
    if (PIN_PORT(pin) >= PIN_c28x_PORT_MAX)
    {
        return -RT_ENOSYS;
    }

    for(i = 0 ; i < PIN_IRQ_MAX ; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            irqindex = i;
            break;
        }
    }
    if (irqindex == -1)
    {
        return -RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t c28x_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    rt_base_t level;
    rt_int32_t irqindex = -1;
    rt_uint16_t channel;
    rt_uint16_t edge_mode,pin_mode;

    if (PIN_PORT(pin) >= PIN_c28x_PORT_MAX)
    {
        return -RT_ENOSYS;
    }

    irqindex = get_irq_index(pin);

    /* irqindex+1 = channel*/
    if (irqindex < 0 || irqindex >= PIN_IRQ_MAX)
    {
        return -RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        level = rt_hw_interrupt_disable();

        if (pin_irq_hdr_tab[irqindex].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return -RT_ENOSYS;
        }

        /*
         * 1. set the edge mode of interrupt triggering
         * 2. set the GPIO mode
         * 3. enable XINT channel and set the input source
        */
        channel = irqindex+1;
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            edge_mode = 1;
            pin_mode = PIN_MODE_INPUT_PULLDOWN;
            break;
        case PIN_IRQ_MODE_FALLING:
            edge_mode = 0;
            pin_mode = PIN_MODE_INPUT_PULLUP;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            edge_mode = 3;
            pin_mode = PIN_MODE_INPUT;
            break;
        }
        if(channel == 1)
        {
            XintRegs.XINT1CR.bit.ENABLE = 1;        // Enable XINT1
            EALLOW;
            InputXbarRegs.INPUT4SELECT = pin;       //Set XINT1 source to GPIO-pin
            EDIS;
            XintRegs.XINT1CR.bit.POLARITY = edge_mode;      // Falling edge interrupt
        }
        else if(channel == 2)
        {
            XintRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2
            EALLOW;
            InputXbarRegs.INPUT5SELECT = pin;       //Set XINT1 source to GPIO-pin
            EDIS;
            XintRegs.XINT2CR.bit.POLARITY = edge_mode;      // Falling edge interrupt
        }
        else if(channel == 3)
        {
            XintRegs.XINT3CR.bit.ENABLE = 1;        // Enable XINT2
            EALLOW;
            InputXbarRegs.INPUT6SELECT = pin;       //Set XINT1 source to GPIO-pin
            EDIS;
            XintRegs.XINT3CR.bit.POLARITY = edge_mode;      // Falling edge interrupt
        }
        else if(channel == 4)
        {
            XintRegs.XINT4CR.bit.ENABLE = 1;        // Enable XINT2
            EALLOW;
            InputXbarRegs.INPUT13SELECT = pin;       //Set XINT1 source to GPIO-pin
            EDIS;
            XintRegs.XINT4CR.bit.POLARITY = edge_mode;      // Falling edge interrupt
        }
        else if(channel == 5)
        {
            XintRegs.XINT5CR.bit.ENABLE = 1;        // Enable XINT2
            EALLOW;
            InputXbarRegs.INPUT14SELECT = pin;       //Set XINT1 source to GPIO-pin
            EDIS;
            XintRegs.XINT5CR.bit.POLARITY = edge_mode;      // Falling edge interrupt
        }

        c28x_pin_mode(device, pin, pin_mode);
        rt_hw_interrupt_enable(level);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        level = rt_hw_interrupt_disable();
        channel = irqindex+1;
        /*
         * TODO modify this simpler
         */
        if(channel == 1)
        {
            XintRegs.XINT1CR.bit.ENABLE = 0;        // Disable XINT1
        }
        else if(channel == 2)
        {
            XintRegs.XINT2CR.bit.ENABLE = 0;        // Disable XINT2
        }
        else if(channel == 3)
        {
            XintRegs.XINT3CR.bit.ENABLE = 0;        // Disable XINT2
        }
        else if(channel == 4)
        {
            XintRegs.XINT4CR.bit.ENABLE = 0;        // Disable XINT2
        }
        else if(channel == 5)
        {
            XintRegs.XINT5CR.bit.ENABLE = 0;        // Disable XINT2
        }
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

void GPIO_XINT_Callback(rt_int16_t XINT_number);

interrupt void XINT1_Handler(void)
{
    rt_interrupt_enter();
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    GPIO_XINT_Callback(1);
    rt_interrupt_leave();
}

interrupt void XINT2_Handler(void)
{
    rt_interrupt_enter();
    GPIO_XINT_Callback(2);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    rt_interrupt_leave();
}

interrupt void XINT3_Handler(void)
{
    rt_interrupt_enter();
    GPIO_XINT_Callback(3);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    rt_interrupt_leave();
}

interrupt void XINT4_Handler(void)
{
    rt_interrupt_enter();
    GPIO_XINT_Callback(4);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    rt_interrupt_leave();
}

interrupt void XINT5_Handler(void)
{
    rt_interrupt_enter();
    GPIO_XINT_Callback(5);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
    rt_interrupt_leave();
}

void GPIO_XINT_Callback(rt_int16_t XINT_number)
{
    rt_int32_t irqindex = XINT_number - 1;
    if(pin_irq_hdr_tab[irqindex].hdr)
    {
        pin_irq_hdr_tab[irqindex].hdr(pin_irq_hdr_tab[irqindex].args);
    }
}

#endif /* RT_USING_PIN */




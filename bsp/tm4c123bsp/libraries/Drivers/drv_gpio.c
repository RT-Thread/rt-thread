/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#include "drv_gpio.h"
#include <rthw.h>
#include <rtdevice.h>
#include "drv_gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#ifdef RT_USING_PIN

static const struct pin_index pins[] =
{
    _TM4C_PIN(0, F, 0),
    _TM4C_PIN(1, F, 1),
    _TM4C_PIN(2, F, 2),
    _TM4C_PIN(3, F, 3),
    _TM4C_PIN(4, F, 4)
};

/* this is pin_irq map, reserved for update */
static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
};

static uint32_t pin_irq_enable_mask = 0;

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

static const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }
    return index;
};

static void tm4c123_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    if (mode == PIN_MODE_INPUT)
    {
        GPIOPinTypeGPIOInput(index ->gpioBaseAddress, index->pin);
    }
    else if (mode == PIN_MODE_OUTPUT)
    {
        GPIOPinTypeGPIOOutput(index->gpioBaseAddress, index->pin);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
        GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_IN);
        GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIOPadConfigSet(index->gpioBaseAddress, index->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
        GPIODirModeSet(index->gpioBaseAddress, index->pin, GPIO_DIR_MODE_OUT);
    }

}

static void tm4c123_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t ui8Val)
{
    const struct pin_index *index;
    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }
    if (ui8Val)
    {
        GPIOPinWrite(index ->gpioBaseAddress, index->pin, index->pin);
    }
    else
    {
        GPIOPinWrite(index ->gpioBaseAddress, index->pin, 0);
    }
}

static rt_ssize_t tm4c123_pin_read(rt_device_t dev, rt_base_t pin)
{
    const struct pin_index *index;
    rt_ssize_t value = 0;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_EINVAL;
    }
    value = GPIOPinRead(index ->gpioBaseAddress, index ->pin);

    return value;
}

static rt_err_t tm4c123_pin_attach_irq(rt_device_t device, rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    /* this is interface for pin_irq, reserved for update. */
    return RT_EOK;
}

static rt_err_t tm4c123_pin_dettach_irq(rt_device_t device, rt_int32_t pin)
{
    /* this is interface for pin_irq, reserved for update. */
    return RT_EOK;
}

static rt_err_t tm4c123_pin_irq_enable(rt_device_t device, rt_base_t pin,
                                       rt_uint32_t enabled)
{
    /* this is interface for pin_irq_enable, reserved for update. */
    return RT_EOK;
}


const static struct rt_pin_ops _tm4c123_pin_ops =
{
    tm4c123_pin_mode,
    tm4c123_pin_write,
    tm4c123_pin_read,
    tm4c123_pin_attach_irq,
    tm4c123_pin_dettach_irq,
    tm4c123_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    return rt_device_pin_register("pin", &_tm4c123_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif   /*RT_USING_PIN*/

/************************** end of file ******************/

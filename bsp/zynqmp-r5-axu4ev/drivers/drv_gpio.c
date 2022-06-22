/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-27     WangHuachen  the first version
 */

#include <rtdevice.h>
#include <rthw.h>
#include "drv_gpio.h"
#include "xgpiops.h"

#define DBG_TAG "drv.gpio"
#define DBG_LVL DBG_INFO
#include "rtdbg.h"

#define GPIO_DEVICE_ID XPAR_XGPIOPS_0_DEVICE_ID
static XGpioPs Gpio; /* The driver instance for GPIO Device. */

void xgpiops_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    switch (mode)
    {
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
        XGpioPs_SetDirectionPin(&Gpio, pin, 1);
        XGpioPs_SetOutputEnablePin(&Gpio, pin, 1);
        break;
    case PIN_MODE_INPUT:
    case PIN_MODE_INPUT_PULLUP:
    case PIN_MODE_INPUT_PULLDOWN:
        XGpioPs_SetDirectionPin(&Gpio, pin, 0);
        break;
    default:
        break;
    }
}

void xgpiops_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    if (pin >= Gpio.MaxPinNum)
        return;

    XGpioPs_WritePin(&Gpio, pin, (value == PIN_HIGH)?1:0);
}

int xgpiops_pin_read(rt_device_t dev, rt_base_t pin)
{
    if (pin >= Gpio.MaxPinNum)
        return 0;

    int DataRead = XGpioPs_ReadPin(&Gpio, pin);
    return DataRead?PIN_HIGH:PIN_LOW;
}

const static struct rt_pin_ops _xgpiops_pin_ops =
    {
        xgpiops_pin_mode,
        xgpiops_pin_write,
        xgpiops_pin_read,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL,
};

int rt_hw_pin_init(void)
{
    int result;
    XGpioPs_Config *ConfigPtr;
    /* Initialize the GPIO driver. */
    ConfigPtr = XGpioPs_LookupConfig(GPIO_DEVICE_ID);

    if (XGpioPs_CfgInitialize(&Gpio, ConfigPtr,
                              ConfigPtr->BaseAddr) == XST_SUCCESS)
    {
        result = rt_device_pin_register("pin", &_xgpiops_pin_ops, RT_NULL);
        return result;
    }
    return -RT_ERROR;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

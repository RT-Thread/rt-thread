/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-21     SummerGift   add port file
 */

#include <rtthread.h>
#include "pcf8574.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.pcf8574_port"
#include <drv_log.h>

#define ETH_RESET_IO    7                //PHY RESET PIN
#define I2C_BUS_NAME	"i2c1"
#define PCF8574_ADDR 	0x20

/* pcf8574 hardware init */
pcf8574_device_t pcf8574_hw_init(char * dev_name, int addr)
{
    static pcf8574_device_t dev;

    if (dev == RT_NULL)
    {
        dev = pcf8574_init(dev_name, addr);
        if (dev == RT_NULL)
        {
            LOG_E("i2c_bus %s for PCF8574 not found!", dev_name);
            return RT_NULL;
        } else {
            return dev;
        }
    } else
    {
        return dev;
    }
}

/* phy reset */
void phy_reset(void)
{
    pcf8574_device_t dev = pcf8574_hw_init(I2C_BUS_NAME, PCF8574_ADDR);
    if (dev == RT_NULL)
    {
        LOG_E("can't get pcf8574 device");
        return;
    }

    pcf8574_pin_write(dev, ETH_RESET_IO, 1);
    rt_thread_mdelay(100);
    pcf8574_pin_write(dev, ETH_RESET_IO, 0);
    rt_thread_mdelay(100);
}


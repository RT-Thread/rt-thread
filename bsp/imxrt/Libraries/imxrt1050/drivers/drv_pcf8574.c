/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-12     zylx     the first version.
 */
#include "drv_pcf8574.h"

#define PCF8574_I2CBUS_NAME  "i2c1"
static struct rt_i2c_bus_device *pcf8574_i2c_bus;

int pcf8574_Init(void)
{
    rt_uint8_t value = 0x01;

    pcf8574_i2c_bus = rt_i2c_bus_device_find(PCF8574_I2CBUS_NAME);

    if (pcf8574_i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find i2c device\r\n");
        return -RT_ERROR;
    }

    if (!rt_i2c_master_send(pcf8574_i2c_bus, PCF8574_ADDR, 0, &value, 1))
    {
        rt_kprintf("can't find pcf8574\r\n");
        return -RT_ERROR;
    }

    return 0;
}
INIT_COMPONENT_EXPORT(pcf8574_Init);

rt_uint8_t pcf8574_read_byte(void)
{
    rt_uint8_t temp = 0;
    rt_i2c_master_recv(pcf8574_i2c_bus, PCF8574_ADDR, 0, &temp, 1);
    return temp;
}

void pcf8574_write_byte(rt_uint8_t data)
{
    rt_i2c_master_send(pcf8574_i2c_bus, PCF8574_ADDR, 0, &data, 1);
}

void pcf8574_write_bit(rt_uint8_t bit, rt_uint8_t sta)
{
    rt_uint8_t data;
    data = pcf8574_read_byte();
    if (sta == 0)data &= ~(1 << bit);
    else data |= 1 << bit;
    pcf8574_write_byte(data);
}

rt_uint8_t pcf8574_read_bit(rt_uint8_t bit)
{
    rt_uint8_t data;
    data = pcf8574_read_byte();
    if (data & (1 << bit))return 1;
    else return 0;
}


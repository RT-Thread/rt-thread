/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-31     tyustli      the first version
 *
 */
#include "board.h"
#include "drv_lcd_spi.h"

#define DBG_TAG "drv_lcd_spi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct intf_spi_device
{
    struct rt_lcd_intf intf;
    struct rt_spi_device *spi_dev_lcd;
};
static struct intf_spi_device lcd_intf;

static rt_err_t _lcd_intf_write_data(struct rt_lcd_intf *device, void *data, rt_size_t len)
{
    rt_size_t writed_len;
    struct intf_spi_device *lcd;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(data != RT_NULL);

    lcd = (struct intf_spi_device*)device->parent.user_data;
    RT_ASSERT(lcd != RT_NULL);

    writed_len = rt_spi_send(lcd->spi_dev_lcd, data, len);
    if (len != writed_len)
    {
        LOG_I("lcd_write_data error. %d", len);
        return -RT_ERROR;
    }
    else
    {
        return RT_EOK;
    }
}

static rt_err_t _lcd_intf_config(struct rt_lcd_intf *device, void *args)
{
    struct rt_spi_configuration *config_spi;
    struct intf_spi_device *lcd;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(args != RT_NULL);

    lcd = (struct intf_spi_device*)device->parent.user_data;
    RT_ASSERT(lcd != RT_NULL);
    config_spi = (struct rt_spi_configuration *)args;

    return rt_spi_configure(lcd->spi_dev_lcd, config_spi);
}

static struct rt_lcd_intf_ops _lcd_intf_ops =
{
    RT_NULL,
    _lcd_intf_write_data,
    RT_NULL,
    RT_NULL,
    _lcd_intf_config,
};

int rt_lcd_intf_init(const char *name)
{
    rt_err_t result;
    
    result = RT_EOK;
    lcd_intf.spi_dev_lcd = (struct rt_spi_device *)rt_device_find(name);
    RT_ASSERT(lcd_intf.spi_dev_lcd != RT_NULL);

    result = rt_lcd_intf_register(&lcd_intf.intf, "lcd_intf", &_lcd_intf_ops, &lcd_intf);
    if (result != RT_EOK)
    {
        LOG_E("register lcd interface device failed error code = %d\n", result);
    }

    return result;
}

/****************** end of file *******************/

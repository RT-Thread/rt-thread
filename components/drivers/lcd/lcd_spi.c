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
#include <rtdevice.h>

#ifdef RT_USING_LCD_SPI

#define DBG_TAG "lcd_spi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct lcd_spi_device
{
    struct rt_lcd_mcu bus;
    struct rt_spi_device *spi_dev_lcd;
};
static struct lcd_spi_device lcd_spi;

static rt_err_t _lcd_spi_write_data(struct rt_lcd_mcu *device, void *data, rt_size_t len)
{
    rt_size_t writed_len;
    struct lcd_spi_device *lcd;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(data != RT_NULL);

    lcd = (struct lcd_spi_device*)device->parent.user_data;
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

static rt_err_t _lcd_spi_config(struct rt_lcd_mcu *device, void *args)
{
    struct rt_spi_configuration *config_spi;
    struct lcd_spi_device *lcd;
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(args != RT_NULL);

    lcd = (struct lcd_spi_device*)device->parent.user_data;
    RT_ASSERT(lcd != RT_NULL);
    config_spi = (struct rt_spi_configuration *)args;

    return rt_spi_configure(lcd->spi_dev_lcd, config_spi);
}

static struct rt_lcd_mcu_ops _lcd_spi_ops =
{
    RT_NULL,
    _lcd_spi_write_data,
    RT_NULL,
    RT_NULL,
    _lcd_spi_config,
};

int rt_lcd_spi_init(const char *name)
{
    rt_err_t result;
    result = RT_EOK;

    lcd_spi.spi_dev_lcd = (struct rt_spi_device *)rt_device_find(name);
    RT_ASSERT(lcd_spi.spi_dev_lcd != RT_NULL);

    result = rt_lcd_mcu_register(&lcd_spi.bus, "lcd_spi", &_lcd_spi_ops, &lcd_spi);
    if (result != RT_EOK)
    {
        LOG_E("register lcd interface device failed error code = %d\n", result);
    }

    return result;
}

#endif /* RT_USING_LCD_SPI */

/****************** end of file *******************/


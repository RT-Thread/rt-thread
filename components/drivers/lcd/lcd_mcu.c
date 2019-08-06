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

#ifdef RT_USING_LCD_MCU

#define DBG_TAG "lcd_mcu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops rt_lcd_mcu_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};
#endif

rt_err_t rt_lcd_mcu_register(struct rt_lcd_mcu *device, const char *name, struct rt_lcd_mcu_ops *ops, void *user_data)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(ops != RT_NULL && device != RT_NULL);

    device->parent.type = RT_Device_Class_Miscellaneous;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops         = &rt_lcd_mcu_ops;
#else
    device->parent.init        = RT_NULL;
    device->parent.open        = RT_NULL;
    device->parent.close       = RT_NULL;
    device->parent.read        = RT_NULL;
    device->parent.write       = RT_NULL;
    device->parent.control     = RT_NULL;
#endif

    device->ops = ops;
    device->parent.user_data = (void *)user_data;
    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

rt_err_t rt_lcd_write_cmd(struct rt_lcd_mcu *device, void *cmd, rt_size_t len)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(device);
    if (device->ops->write_cmd != RT_NULL)
    {
        result = device->ops->write_cmd(device, cmd, len);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_err_t rt_lcd_write_data(struct rt_lcd_mcu *device, void *data, rt_size_t len)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(device);
    if (device->ops->write_data != RT_NULL)
    {
        result = device->ops->write_data(device, data, len);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_uint32_t rt_lcd_read_data(struct rt_lcd_mcu *device, rt_uint32_t reg)
{
    rt_uint32_t value;

    RT_ASSERT(device);
    device->ops->read_data(device, reg, &value);

    return value;
}

rt_err_t rt_lcd_write_reg(struct rt_lcd_mcu *device, rt_uint32_t reg, rt_uint32_t data)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(device);
    if (device->ops->write_reg != RT_NULL)
    {
        result = device->ops->write_reg(device, reg, data);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

rt_err_t rt_lcd_mcu_config(struct rt_lcd_mcu *device, void *config)
{
    rt_err_t result;

    result = RT_EOK;
    RT_ASSERT(device);
    if (device->ops->config != RT_NULL)
    {
        result = device->ops->config(device, config);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

#endif /* RT_USING_LCD_MCU */

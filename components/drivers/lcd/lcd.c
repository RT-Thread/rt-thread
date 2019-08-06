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

#ifdef RT_USING_LCD

#define DBG_TAG "lcd"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_err_t _lcd_control(rt_device_t device, int cmd, void *args)
{
    struct rt_lcd_device *lcd;

    lcd = (struct rt_lcd_device *)device;
    RT_ASSERT(lcd);
    if (lcd->ops->control)
    {
        return lcd->ops->control(lcd, cmd, args);
    }
    else
    {
        return -RT_ENOSYS;
    }
}

static rt_err_t _lcd_init(rt_device_t device)
{
    struct rt_lcd_device *lcd;

    lcd = (struct rt_lcd_device *)device;
    RT_ASSERT(lcd);
    if (lcd->ops->init)
    {
        return lcd->ops->init(lcd);
    }
    else
    {
        return -RT_ENOSYS;
    }
}

#ifdef RT_USING_DEVICE_OPS
static struct rt_device_ops rt_lcd_ops =
{
    _lcd_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _lcd_control,
};
#endif

rt_err_t rt_lcd_device_register(struct rt_lcd_device *device, const char *name, struct rt_lcd_ops *ops, void *user_data)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(ops != RT_NULL && device != RT_NULL);

    device->parent.type         = RT_Device_Class_Graphic;
    device->parent.rx_indicate = RT_NULL;
    device->parent.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    device->parent.ops = &rt_lcd_ops;
#else
    device->parent.init = _lcd_init;
    device->parent.open = RT_NULL;
    device->parent.close = RT_NULL;
    device->parent.read  = RT_NULL;
    device->parent.write = RT_NULL;
    device->parent.control = _lcd_control;
#endif /* RT_USING_DEVICE_OPS */

    device->ops                 = ops;
    device->parent.user_data    = user_data;
    result = rt_device_register(&device->parent, name, RT_DEVICE_FLAG_RDWR);

    return result;
}

/*
 * the following API is for pixel device to draw a point/picture
 */

/* set a point pixel*/
rt_err_t rt_set_pixel(struct rt_lcd_device *device, const char *pixel, int x, int y)
{
    rt_err_t result;
    struct rt_device_graphic_ops *lcd;

    RT_ASSERT(device);
    result = RT_EOK;
    lcd = (struct rt_device_graphic_ops *)device->parent.user_data;
    if (lcd != RT_NULL)
    {
        lcd->set_pixel(pixel, x, y);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

/* get a point pixel*/
rt_err_t rt_get_pixel(struct rt_lcd_device *device, char *pixel, int x, int y)
{
    rt_err_t result;
    struct rt_device_graphic_ops *graphic_ops;

    RT_ASSERT(device);
    result = RT_EOK;
    graphic_ops = (struct rt_device_graphic_ops *)device->parent.user_data;
    if (graphic_ops != RT_NULL)
    {
        graphic_ops->get_pixel(pixel, x, y);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

/* draw a horizonal line */
rt_err_t rt_draw_hline(struct rt_lcd_device *device, const char *pixel, int x1, int x2, int y)
{
    rt_err_t result;
    struct rt_device_graphic_ops *graphic_ops;

    RT_ASSERT(device);
    result = RT_EOK;
    graphic_ops = (struct rt_device_graphic_ops *)device->parent.user_data;

    if (graphic_ops != RT_NULL)
    {
        graphic_ops->draw_hline(pixel, x1, x2, y);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

/* draw a vertical */
rt_err_t rt_draw_vline(struct rt_lcd_device *device, const char *pixel, int x, int y1, int y2)
{
    rt_err_t result;
    struct rt_device_graphic_ops *graphic_ops;

    RT_ASSERT(device);
    result = RT_EOK;
    graphic_ops = (struct rt_device_graphic_ops *)device->parent.user_data;
    if (graphic_ops != RT_NULL)
    {
        graphic_ops->draw_vline(pixel, x, y1, y2);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

/* draw a blit line */
rt_err_t rt_blit_line(struct rt_lcd_device *device, const char *pixel, int x, int y, rt_size_t size)
{
    rt_err_t result;
    struct rt_device_graphic_ops *graphic_ops;

    RT_ASSERT(device);
    result = RT_EOK;
    graphic_ops = (struct rt_device_graphic_ops *)device->parent.user_data;
    if (graphic_ops != RT_NULL)
    {
        graphic_ops->blit_line(pixel, x, y, size);
    }
    else
    {
        result = -RT_ENOSYS;
    }

    return result;
}

#endif /* RT_USING_LCD */

/*************** end of file ********/

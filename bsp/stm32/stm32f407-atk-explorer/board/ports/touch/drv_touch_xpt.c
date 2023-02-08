/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-27      solar        first version
 */

#include <drv_touch_xpt.h>
#include <drv_soft_spi.h>
#include <drv_spi.h>
#include <drv_gpio.h>

#define LOG_TAG "drv.xpt2046"
#include <drv_log.h>

#ifdef BSP_USING_TOUCH_RES

static const rt_uint8_t xpt2046_tx_data[21] = {0xD0, 0, 0xD0, 0, 0xD0, 0, 0xD0, 0, 0xD0, 0, 0x90, 0, 0x90, 0, 0x90, 0, 0x90, 0, 0x90, 0, 0};

/* Please calibrate the resistive touch screen before use, it is best to store the calibrated data */
rt_err_t xpt2046_calibration(const char *lcd_name,const char *touch_name)
{
    /* Find the TFT LCD device */
    rt_device_t lcd = rt_device_find(lcd_name);
    if (lcd == RT_NULL)
    {
        LOG_E(LOG_TAG " cannot find lcd device named %s", lcd_name);
        return -RT_ERROR;
    }
    if (rt_device_open(lcd, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        LOG_E(LOG_TAG " cannot open lcd device named %s", lcd_name);
        return 0;
    }

    /* Find the Touch device */
    rt_xpt2046_t touch = (rt_xpt2046_t)rt_device_find(touch_name);
    if (touch == RT_NULL)
    {
        LOG_E(LOG_TAG " cannot find touch device named %s", touch_name);
        return -RT_ERROR;
    }

    /* Get TFT LCD screen information */
    struct rt_device_graphic_info lcd_info;
    rt_device_control(lcd, RTGRAPHIC_CTRL_GET_INFO, &lcd_info);

    /* clear screen */
    for (rt_uint32_t y = 0; y < lcd_info.height; ++y)
    {
        const uint32_t white = 0xFFFFFFFF;
        rt_graphix_ops(lcd)->draw_hline((const char *)(&white), 0, lcd_info.width, y);
    }
    /* Set the information for the four points used for calibration */
    rt_uint32_t cross_size = (lcd_info.width > lcd_info.height ? lcd_info.height : lcd_info.width) / 10;
    rt_uint32_t x0 = cross_size;
    rt_uint32_t y0 = cross_size;
    rt_uint32_t x1 = lcd_info.width - cross_size;
    rt_uint32_t y1 = cross_size;
    rt_uint32_t x2 = lcd_info.width - cross_size;
    rt_uint32_t y2 = lcd_info.height - cross_size;
    rt_uint32_t x3 = cross_size;
    rt_uint32_t y3 = lcd_info.height - cross_size;
    const rt_uint32_t black = 0x0;
    /* Upper left cross */
    rt_graphix_ops(lcd)->draw_hline((const char *)(&black), 0, x0 + cross_size, y0);
    rt_graphix_ops(lcd)->draw_vline((const char *)(&black), x0, 0, y0 + cross_size);

    touch->min_raw_x = 0;
    touch->min_raw_y = 0;
    touch->max_raw_x = 4096;
    touch->max_raw_y = 4096;
    touch->parent.info.range_x = 4096;
    touch->parent.info.range_y = 4096;

    rt_uint16_t x_raw[4];
    rt_uint16_t y_raw[4];
    rt_uint8_t raw_idx = 0;
    rt_memset(x_raw, 0, sizeof(x_raw));
    rt_memset(y_raw, 0, sizeof(y_raw));
    while (1)
    {
        struct rt_touch_data read_data;
        rt_memset(&read_data, 0, sizeof(struct rt_touch_data));
        if (rt_device_read((rt_device_t)touch, 0, &read_data, 1) == 1)
        {
            x_raw[raw_idx] = read_data.x_coordinate;
            y_raw[raw_idx++] = read_data.y_coordinate;
            LOG_I(" %d point capture", raw_idx - 1);
            /* After processing a point, proceed to clear the screen */
            for (rt_uint32_t y = 0; y < lcd_info.height; ++y)
            {
                const uint32_t white = 0xFFFFFFFF;
                rt_graphix_ops(lcd)->draw_hline((const char *)(&white), 0, lcd_info.width, y);
            }
            rt_thread_mdelay(400);
            if (raw_idx >= 4)
            {
                break;
            }
            switch (raw_idx)
            {
            case 1:
                /* Upper right cross */
                rt_graphix_ops(lcd)->draw_hline((const char *)(&black), x1 - cross_size, lcd_info.width, y1);
                rt_graphix_ops(lcd)->draw_vline((const char *)(&black), x1, 0, y1 + cross_size);
                break;
            case 2:
                /* lower right cross */
                rt_graphix_ops(lcd)->draw_hline((const char *)(&black), x2 - cross_size, lcd_info.width, y2);
                rt_graphix_ops(lcd)->draw_vline((const char *)(&black), x2, y2 - cross_size, lcd_info.height);
                break;
            case 3:
                /* lower left cross */
                rt_graphix_ops(lcd)->draw_hline((const char *)(&black), 0, x3 + cross_size, y3);
                rt_graphix_ops(lcd)->draw_vline((const char *)(&black), x3, y3 - cross_size, lcd_info.height);
                break;
            default:
                break;
            }
        }
        rt_thread_mdelay(10);
    }
    rt_uint16_t min_x = (x_raw[0] + x_raw[3]) / 2;
    rt_uint16_t max_x = (x_raw[1] + x_raw[2]) / 2;
    rt_uint16_t min_y = (y_raw[0] + y_raw[1]) / 2;
    rt_uint16_t max_y = (y_raw[2] + y_raw[3]) / 2;

    rt_int32_t x_raw_cnt_per_pixel = (max_x - min_x) / (x1 - x0);
    rt_int32_t y_raw_cnt_per_pixel = (max_y - min_y) / (y2 - y1);

    min_x -= cross_size * x_raw_cnt_per_pixel;
    max_x += cross_size * x_raw_cnt_per_pixel;
    min_y -= cross_size * y_raw_cnt_per_pixel;
    max_y += cross_size * y_raw_cnt_per_pixel;

    touch->min_raw_x = min_x;
    touch->min_raw_y = min_y;
    touch->max_raw_x = max_x;
    touch->max_raw_y = max_y;
    touch->parent.info.range_x = lcd_info.width;
    touch->parent.info.range_y = lcd_info.height;

    LOG_I(" Calibration result, min_x:%d, min_y:%d, max_x:%d, max_y:%d", min_x, min_y, max_x, max_y);

    rt_device_close(lcd);

    return RT_EOK;
}

static rt_ssize_t xpt2046_touch_readpoint(struct rt_touch_device *touch, void *buf, rt_size_t touch_num)
{
    if (touch_num != 0)
    {
        struct rt_touch_data *result = (struct rt_touch_data *)buf;
        rt_xpt2046_t dev = (rt_xpt2046_t)touch;
#ifdef RT_TOUCH_PIN_IRQ
        if (rt_pin_read(dev->parent.config.irq_pin.pin))
        {
            result->event = RT_TOUCH_EVENT_NONE;
            return 0;
        }
#endif /* RT_TOUCH_PIN_IRQ */
        rt_uint8_t rx_data[21];
        rt_spi_transfer(dev->spi, xpt2046_tx_data, rx_data, 21);
        rt_uint8_t x_count = 0;
        rt_uint8_t y_count = 0;
        rt_uint32_t x_cum = 0;
        rt_uint32_t y_cum = 0;
        for (rt_uint8_t i = 1; i < 11; i += 2)
        {
            rt_uint16_t temp = (rx_data[i] << 8 | rx_data[i + 1]) >> 4;
            if (temp >= dev->min_raw_x && temp <= dev->max_raw_x)
            {
                ++x_count;
                x_cum += temp;
            }
            temp = (rx_data[i + 10] << 8 | rx_data[i + 11]) >> 4;
            if (temp >= dev->min_raw_y && temp <= dev->max_raw_y)
            {
                ++y_count;
                y_cum += temp;
            }
        }
        if (!x_count || !y_count)
        {
            result->event = RT_TOUCH_EVENT_NONE;
            return 0;
        }
        result->event = RT_TOUCH_EVENT_DOWN;
        result->x_coordinate = ((float)x_cum / x_count - dev->min_raw_x) / (dev->max_raw_x - dev->min_raw_x) * dev->parent.info.range_x;
        result->y_coordinate = ((float)y_cum / y_count - dev->min_raw_y) / (dev->max_raw_y - dev->min_raw_y) * dev->parent.info.range_y;
        return touch_num;
    }
    else
    {
        return 0;
    }
}

static rt_err_t xpt2046_touch_control(struct rt_touch_device *touch, int cmd, void *arg)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(touch != RT_NULL);

    /* If necessary, please implement this control function yourself */

    return result;
}

static struct rt_touch_ops xpt2046_ops =
{
    .touch_readpoint = xpt2046_touch_readpoint,
    .touch_control = xpt2046_touch_control,
};

static int xpt2046_hw_init(void)
{
    rt_xpt2046_t dev_obj = rt_malloc(sizeof(struct rt_xpt2046));
    if (dev_obj != RT_NULL)
    {
        rt_memset(dev_obj, 0x0, sizeof(struct rt_xpt2046));
        dev_obj->min_raw_x = BSP_XPT2046_MIN_RAW_X;
        dev_obj->min_raw_y = BSP_XPT2046_MIN_RAW_Y;
        dev_obj->max_raw_x = BSP_XPT2046_MAX_RAW_X;
        dev_obj->max_raw_y = BSP_XPT2046_MAX_RAW_Y;
        /* spi mount and config is implemented by the user */
        dev_obj->spi = RT_NULL;

        dev_obj->parent.info.type = RT_TOUCH_TYPE_RESISTANCE;
        dev_obj->parent.info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
        dev_obj->parent.info.point_num = 1;
        dev_obj->parent.info.range_x = BSP_XPT2046_RANGE_X;
        dev_obj->parent.info.range_y = BSP_XPT2046_RANGE_Y;
#ifdef RT_TOUCH_PIN_IRQ
        dev_obj->parent.config.irq_pin.pin = rt_pin_get(BSP_XPT2046_IRQ_PIN);
        dev_obj->parent.config.irq_pin.mode = PIN_MODE_INPUT_PULLUP;
#endif /* RT_TOUCH_PIN_IRQ */
        dev_obj->parent.ops = &xpt2046_ops;

        rt_uint8_t dev_num = 0;
        char dev_name[RT_NAME_MAX];
        do
        {
            rt_sprintf(dev_name, "xpt%d", dev_num++);
            if (dev_num == 255)
            {
                rt_device_destroy((rt_device_t) & (dev_obj->parent));
                return RT_NULL;
            }
        } while (rt_device_find(dev_name));
        rt_hw_touch_register(&(dev_obj->parent), dev_name, RT_DEVICE_FLAG_INT_RX, RT_NULL);
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

INIT_DEVICE_EXPORT(xpt2046_hw_init);

#endif /* BSP_USING_TOUCH_RES */

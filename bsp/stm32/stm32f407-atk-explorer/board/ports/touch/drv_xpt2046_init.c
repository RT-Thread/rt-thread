/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-27      solar        first version
 */

#include <rtdevice.h>
#include "drv_touch_xpt.h"
#include "drv_soft_spi.h"

#ifdef PKG_USING_GUIENGINE
#include <rtgui/event.h>
#include <rtgui/rtgui_server.h>
#elif defined(PKG_USING_LITTLEVGL2RTT)
#include <littlevgl2rtt.h>
#elif defined(PKG_USING_LVGL)
#include <lvgl.h>
extern void lv_port_indev_input(rt_int16_t x, rt_int16_t y, lv_indev_state_t state);
static rt_bool_t touch_down = RT_FALSE;
#endif /* PKG_USING_GUIENGINE */

#ifdef BSP_USING_TOUCH_RES

/* If calibration is not required, please manually modify the contents of
 * the drv_touch_xpt.h file,and set BSP_TOUCH_CALIBRATE to RT_FALSE */
#define BSP_TOUCH_CALIBRATE RT_TRUE

#define BSP_XPT2046_SPI_BUS "sspi1"
#define TOUCH_DEVICE_NAME   "xpt0"
#define TFTLCD_DEVICE_NAME  "lcd"

void xpt2046_init_hw(void)
{
    /* Find the touch device */
    rt_device_t touch = rt_device_find(TOUCH_DEVICE_NAME);
    if (touch == RT_NULL)
    {
        rt_kprintf("can't find touch device:%s\n", TOUCH_DEVICE_NAME);
        return;
    }
    if (rt_device_open(touch, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("can't open touch device:%s\n", TOUCH_DEVICE_NAME);
        return;
    }

    rt_uint8_t dev_num = 0;
    char dev_name[RT_NAME_MAX];
    do
    {
        rt_sprintf(dev_name, "%s%d", BSP_XPT2046_SPI_BUS, dev_num++);
        if (dev_num == 255)
        {
            return;
        }
    } while (rt_device_find(dev_name));

    /* Mount the spi device to the spi bus, here is the soft spi,
     * if you use other spi, please modify the following */
    rt_hw_softspi_device_attach(BSP_XPT2046_SPI_BUS, dev_name, rt_pin_get(BSP_XPT2046_CS_PIN));

    /* configure spi device */
    rt_xpt2046_t tc = (rt_xpt2046_t)touch;
    tc->spi = (struct rt_spi_device *)rt_device_find(dev_name);
    struct rt_spi_configuration spi_config;
    spi_config.data_width = 8;
    spi_config.mode = RT_SPI_MASTER | RT_SPI_MODE_0 | RT_SPI_MSB;
    /* Max freq of XPT2046 is 2MHz */
    spi_config.max_hz = 2000000;
    rt_spi_configure(tc->spi, &spi_config);

#if (BSP_TOUCH_CALIBRATE == RT_TRUE)
    /* Calibrate touch */
    xpt2046_calibration(TFTLCD_DEVICE_NAME,TOUCH_DEVICE_NAME);
#endif /* BSP_TOUCH_CALIBRATE == RT_TRUE */

    /* init the TFT LCD */
    rt_device_t lcd = RT_NULL;

    lcd = rt_device_find("lcd");
    rt_device_init(lcd);
}

void xpt2046_entry(void *parameter)
{
    /* Find the touch device */
    rt_device_t touch = rt_device_find(TOUCH_DEVICE_NAME);
    if (touch == RT_NULL)
    {
        rt_kprintf("can't find touch device:%s\n", TOUCH_DEVICE_NAME);
        return;
    }
#ifndef PKG_USING_LVGL
    rt_device_t lcd = rt_device_find(TFTLCD_DEVICE_NAME);
    if (lcd == RT_NULL)
    {
       rt_kprintf("can't find display device:%s\n", TFTLCD_DEVICE_NAME);
       return;
    }
#endif /* PKG_USING_LVGL */
    while (1)
    {
        /* Prepare variable to read out the touch data */
        struct rt_touch_data read_data;
        rt_memset(&read_data, 0, sizeof(struct rt_touch_data));
        if (rt_device_read(touch, 0, &read_data, 1) == 1)
        {
#ifdef PKG_USING_LVGL
            lv_port_indev_input(read_data.x_coordinate, read_data.y_coordinate,
                                ((read_data.event = RT_TOUCH_EVENT_DOWN) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL));
#else /* PKG_USING_LVGL */
            const rt_uint32_t black = 0x0;
            rt_graphix_ops(lcd)->set_pixel((const char *)(&black),
                                        read_data.x_coordinate,
                                         read_data.y_coordinate);
#endif /* PKG_USING_LVGL */
        }
        rt_thread_mdelay(1);
    }
}

static int touch_xpt2046_init(void)
{
    xpt2046_init_hw();
    rt_thread_t tid = rt_thread_create("xpt2046", xpt2046_entry, RT_NULL, 1024, 8, 20);
    RT_ASSERT(tid != RT_NULL);
    rt_thread_startup(tid);
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(touch_xpt2046_init);

#endif /* BSP_USING_TOUCH_RES */

/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-27      solar        first version
 * 2026-01-12     LinuxMint-User fix touch event bug with LVGL
 * 2026-01-13     LinuxMint-User improve the touch sliding experience of resistive screens
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
    #endif

    static bool is_touching = false;
    static int no_touch_count = 0;
    static int touch_hold_count = 0;
    static int last_x = 0, last_y = 0;
    static int stable_x = 0, stable_y = 0;

    #define HISTORY_SIZE 5
    static int history_x[HISTORY_SIZE] = {0};
    static int history_y[HISTORY_SIZE] = {0};
    static int history_index = 0;
    static int history_count = 0;

    static const int DEBOUNCE_COUNT = 2;
    static const int RELEASE_DEBOUNCE_COUNT = 5;
    static const int MIN_MOVE_DISTANCE = 3;
    static const int SMOOTHING_FACTOR = 2;

    rt_memset(history_x, 0, sizeof(history_x));
    rt_memset(history_y, 0, sizeof(history_y));

    while (1)
    {
        struct rt_touch_data read_data;
        rt_memset(&read_data, 0, sizeof(struct rt_touch_data));

        if (rt_device_read(touch, 0, &read_data, 1) == 1)
        {
            int current_x = read_data.x_coordinate;
            int current_y = read_data.y_coordinate;

            history_x[history_index] = current_x;
            history_y[history_index] = current_y;
            history_index = (history_index + 1) % HISTORY_SIZE;
            if (history_count < HISTORY_SIZE) history_count++;

            int avg_x = 0, avg_y = 0;
            if (history_count > 0)
            {
                for (int i = 0; i < history_count; i++)
                {
                    avg_x += history_x[i];
                    avg_y += history_y[i];
                }
                avg_x /= history_count;
                avg_y /= history_count;
            }
            else
            {
                avg_x = current_x;
                avg_y = current_y;
            }

            no_touch_count = 0;

            #ifdef PKG_USING_LVGL
            if (!is_touching)
            {
                touch_hold_count++;

                if (touch_hold_count >= DEBOUNCE_COUNT)
                {
                    is_touching = true;
                    stable_x = avg_x;
                    stable_y = avg_y;
                    touch_hold_count = 0;

                    lv_port_indev_input(stable_x, stable_y, LV_INDEV_STATE_PR);

                    last_x = stable_x;
                    last_y = stable_y;
                }
            }
            else
            {
                touch_hold_count = 0;

                int dx = avg_x - last_x;
                int dy = avg_y - last_y;
                int distance = dx * dx + dy * dy;

                if (distance >= MIN_MOVE_DISTANCE * MIN_MOVE_DISTANCE)
                {
                    int smooth_x = last_x + (avg_x - last_x) / SMOOTHING_FACTOR;
                    int smooth_y = last_y + (avg_y - last_y) / SMOOTHING_FACTOR;

                    lv_port_indev_input(smooth_x, smooth_y, LV_INDEV_STATE_PR);

                    last_x = smooth_x;
                    last_y = smooth_y;
                    stable_x = smooth_x;
                    stable_y = smooth_y;
                }
                else
                {
                    lv_port_indev_input(stable_x, stable_y, LV_INDEV_STATE_PR);
                }
            }

            #else
            const rt_uint32_t black = 0x0;
            rt_graphix_ops(lcd)->set_pixel((const char *)(&black), avg_x, avg_y);
            #endif
        }
        else
        {
            no_touch_count++;
            touch_hold_count = 0;

            if (is_touching)
            {
                if (no_touch_count >= RELEASE_DEBOUNCE_COUNT)
                {
                    #ifdef PKG_USING_LVGL
                    lv_port_indev_input(stable_x, stable_y, LV_INDEV_STATE_REL);
                    #endif

                    is_touching = false;
                    no_touch_count = 0;

                    history_count = 0;
                    history_index = 0;
                    rt_memset(history_x, 0, sizeof(history_x));
                    rt_memset(history_y, 0, sizeof(history_y));
                }
                else
                {
                    #ifdef PKG_USING_LVGL
                    lv_port_indev_input(stable_x, stable_y, LV_INDEV_STATE_PR);
                    #endif
                }
            }
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


/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-25     Wayne        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "ili.h"

#define THREAD_PRIORITY   5
#define THREAD_STACK_SIZE 2048
#define THREAD_TIMESLICE  5

static rt_sem_t  tpc_sem = RT_NULL;

rt_weak void nu_touch_inputevent_cb(rt_int16_t x, rt_int16_t y, rt_uint8_t state)
{
    rt_kprintf("[%d] %d %d\n", state, x, y);
}

static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
{
    return rt_sem_release(tpc_sem);
}

static void tpc_entry(void *parameter)
{
    struct rt_touch_data *read_data;
    struct rt_touch_info info;
    rt_device_t  dev = RT_NULL;

    const char *name = "ili_tpc";
    rt_uint32_t x_range = BSP_LCD_WIDTH;
    rt_uint32_t y_range = BSP_LCD_HEIGHT;

    dev = rt_device_find(name);
    if (dev == RT_NULL)
    {
        rt_kprintf("can't find device:%s\n", name);
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return;
    }
    rt_kprintf("[%s] x: %d, y: %d\n", __func__, x_range, y_range);

    rt_device_control(dev, RT_TOUCH_CTRL_SET_X_RANGE, &x_range);  /* if possible you can set your x y coordinate*/
    rt_device_control(dev, RT_TOUCH_CTRL_SET_Y_RANGE, &y_range);

    tpc_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_FIFO);
    if (tpc_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return;
    }

    rt_device_set_rx_indicate(dev, rx_callback);

    rt_device_control(dev, RT_TOUCH_CTRL_GET_INFO, &info);
    rt_kprintf("range_x = %d \n",   info.range_x);
    rt_kprintf("range_y = %d \n",   info.range_y);
    rt_kprintf("point_num = %d \n", info.point_num);

    read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data) * info.point_num);
    RT_ASSERT(read_data);

    rt_memset(read_data, 0, sizeof(struct rt_touch_data) * info.point_num);

    while (1)
    {
        rt_sem_take(tpc_sem, RT_WAITING_FOREVER);
        rt_device_control(dev, RT_TOUCH_CTRL_DISABLE_INT, RT_NULL);

        if (rt_device_read(dev, 0, read_data, info.point_num) == info.point_num)
        {
            for (rt_uint8_t i = 0; i < 1; i++) // Only report one point.
            {
                if (read_data[i].event == RT_TOUCH_EVENT_DOWN
                        || read_data[i].event == RT_TOUCH_EVENT_UP
                        || read_data[i].event == RT_TOUCH_EVENT_MOVE)
                {
                    //rt_kprintf("[%d] %d %d\n", read_data[i].event, read_data[i].x_coordinate, read_data[i].y_coordinate);

                    nu_touch_inputevent_cb(read_data[i].x_coordinate, read_data[i].y_coordinate, read_data[i].event);
                }
            }
        }
        rt_device_control(dev, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL);
    }
}


/* Test function */
int tpc_sample(void)
{
    rt_thread_t  tpc_thread;
    tpc_thread = rt_thread_create("tpc",
                                  tpc_entry,
                                  RT_NULL,
                                  THREAD_STACK_SIZE,
                                  THREAD_PRIORITY,
                                  THREAD_TIMESLICE);

    if (tpc_thread != RT_NULL)
        rt_thread_startup(tpc_thread);

    return 0;
}
INIT_APP_EXPORT(tpc_sample);

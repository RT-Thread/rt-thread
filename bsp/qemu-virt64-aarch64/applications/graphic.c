/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-11     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <virtio_gpu.h>
#include <virtio_input.h>

#define GRAPHIC_THREAD_PRIORITY     25
#define GRAPHIC_THREAD_STACK_SIZE   4096
#define GRAPHIC_THREAD_TIMESLICE    5

static rt_uint32_t cur_min[2];
static rt_uint32_t cur_max[2];
static rt_uint32_t cur_range[2];
static rt_uint32_t cur_points[2];
static rt_uint32_t cur_last_points[2];
static rt_bool_t cur_event_sync;
static rt_uint32_t color[2] = { 0xff0000, 0x0000ff };
static rt_uint8_t cursor[VIRTIO_GPU_CURSOR_IMG_SIZE] rt_align(VIRTIO_PAGE_SIZE);

void tablet_event_handler(struct virtio_input_event event)
{
    static rt_bool_t cur_btn_down = RT_FALSE;

    if (event.type == EV_ABS)
    {
        if (event.code == 0)
        {
            cur_points[0] = (cur_max[0] * (event.value - cur_min[0]) + cur_range[0] / 2) / cur_range[0];
        }
        else if (event.code == 1)
        {
            cur_points[1] = (cur_max[1] * (event.value - cur_min[1]) + cur_range[1] / 2) / cur_range[1];
        }
    }
    else if (event.type == EV_KEY)
    {
        if (event.code == BTN_LEFT)
        {
            if (cur_btn_down && event.value == 0)
            {
                color[0] ^= color[1];
                color[1] ^= color[0];
                color[0] ^= color[1];
                cur_btn_down = RT_FALSE;
                cur_event_sync = RT_TRUE;
            }
            else
            {
                cur_btn_down = RT_TRUE;
            }
        }
    }
    else if (event.type == EV_SYN)
    {
        cur_event_sync = RT_TRUE;
    }
}

void graphic_thread(void *param)
{
    int i;
    char dev_name[RT_NAME_MAX];
    rt_device_t device = RT_NULL;

    rt_device_t tablet_dev = RT_NULL;
    struct virtio_input_config tablet_config;

    rt_uint32_t white = 0xffffff;
    rt_device_t gpu_dev = RT_NULL;
    struct rt_device_rect_info rect_info;
    struct rt_device_graphic_info graphic_info;
    struct rt_device_graphic_ops *virtio_gpu_graphic_ops;

    /* GPU */
    device = rt_device_find("virtio-gpu0");

    if (device != RT_NULL && rt_device_open(device, 0) == RT_EOK)
    {
        virtio_gpu_graphic_ops = rt_graphix_ops(device);

        rt_memset(&rect_info, 0, sizeof(rect_info));
        rt_memset(&graphic_info, 0, sizeof(graphic_info));

        rt_device_control(device, VIRTIO_DEVICE_CTRL_GPU_SET_PRIMARY, RT_NULL);
        rt_device_control(device, VIRTIO_DEVICE_CTRL_GPU_CREATE_2D, (void *)RTGRAPHIC_PIXEL_FORMAT_RGB888);
        rt_device_control(device, RTGRAPHIC_CTRL_GET_INFO, &graphic_info);

        rect_info.x = 0;
        rect_info.y = 0;
        rect_info.width = graphic_info.width;
        rect_info.height = graphic_info.height;

        if (graphic_info.framebuffer != RT_NULL)
        {
            int i = 0;

            rt_memset(graphic_info.framebuffer, 0xff, graphic_info.pitch * graphic_info.height);

            cur_last_points[0] = graphic_info.width / 2;
            cur_last_points[1] = graphic_info.height / 2;

            virtio_gpu_graphic_ops->draw_hline((char *)&color[0], 0, graphic_info.width, cur_last_points[1]);
            virtio_gpu_graphic_ops->draw_vline((char *)&color[1], cur_last_points[0], 0, graphic_info.height);

            rt_device_control(device, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);

            while (i < sizeof(cursor) / 4)
            {
                /* R: 0x4c G: 0xaf B: 0x50 A: 0.8 */
                ((rt_uint32_t *)cursor)[i] = 0xcc4caf50;
                ++i;
            }

            rt_device_control(device, VIRTIO_DEVICE_CTRL_CURSOR_SETUP, cursor);
            rt_device_control(device, VIRTIO_DEVICE_CTRL_CURSOR_MOVE, (rt_uint32_t[]){0, 0});

            gpu_dev = device;
        }
    }

    /* Keyboard, Mouse, Tablet */
    for (i = 0; i < 3; ++i)
    {
        rt_snprintf(dev_name, RT_NAME_MAX, "virtio-input%d", i);

        device = rt_device_find(dev_name);

        if (device != RT_NULL && rt_device_open(device, 0) == RT_EOK)
        {
            enum virtio_input_type type;
            rt_device_control(device, VIRTIO_DEVICE_CTRL_INPUT_GET_TYPE, &type);

            if (type == VIRTIO_INPUT_TYPE_TABLET)
            {
                tablet_dev = device;
            }
            else
            {
                rt_device_close(device);
            }
        }
    }

    if (tablet_dev == RT_NULL || gpu_dev == RT_NULL)
    {
        goto _graphic_fail;
    }

    cur_max[0] = graphic_info.width;
    cur_max[1] = graphic_info.height;

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_X_INFO, &tablet_config);

    cur_min[0] = tablet_config.abs.min;
    cur_range[0] = tablet_config.abs.max - cur_min[0];

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_GET_ABS_Y_INFO, &tablet_config);

    cur_min[1] = tablet_config.abs.min;
    cur_range[1] = tablet_config.abs.max - cur_min[1];

    cur_event_sync = RT_FALSE;

    rt_device_control(tablet_dev, VIRTIO_DEVICE_CTRL_INPUT_BIND_BSCT_HANDLER, tablet_event_handler);

    for (;;)
    {
        while (cur_event_sync)
        {
            virtio_gpu_graphic_ops->draw_hline((char *)&white, 0, graphic_info.width, cur_last_points[1]);
            virtio_gpu_graphic_ops->draw_vline((char *)&white, cur_last_points[0], 0, graphic_info.height);

            cur_last_points[0] = cur_points[0];
            cur_last_points[1] = cur_points[1];

            virtio_gpu_graphic_ops->draw_hline((char *)&color[0], 0, graphic_info.width, cur_last_points[1]);
            virtio_gpu_graphic_ops->draw_vline((char *)&color[1], cur_last_points[0], 0, graphic_info.height);

            rt_device_control(gpu_dev, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);

            cur_event_sync = RT_FALSE;

            rt_thread_mdelay(1);
        }
    }

_graphic_fail:

    if (gpu_dev != RT_NULL)
    {
        rt_device_close(gpu_dev);
    }

    if (tablet_dev != RT_NULL)
    {
        rt_device_close(tablet_dev);
    }
}

int graphic_test(void)
{
    rt_thread_t graphic_tid = rt_thread_create("graphic work", graphic_thread, RT_NULL,
            GRAPHIC_THREAD_STACK_SIZE, GRAPHIC_THREAD_PRIORITY, GRAPHIC_THREAD_TIMESLICE);

    if (graphic_tid != RT_NULL)
    {
        rt_thread_startup(graphic_tid);

        return RT_EOK;
    }

    return -RT_ERROR;
}
MSH_CMD_EXPORT(graphic_test, Graphic test);

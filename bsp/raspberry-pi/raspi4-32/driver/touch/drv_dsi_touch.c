/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-11-26     bigmagic       first version
 */
#include <rtthread.h>
#include <rtdevice.h>

#include "mbox.h"
#include "drv_dsi_touch.h"

#define DBG_TAG "dsi_touch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_touch_t touch_device = RT_NULL;
static struct rt_semaphore dsi_touch_ack;

static rt_uint32_t touch_x;
static rt_uint32_t touch_y;
static rt_uint32_t touch_state;

static rt_thread_t dsi_touch_tid = RT_NULL;
#define DSI_TOUCH_THREAD_STACK_SIZE     (4096)
#define DSI_TOUCH_THREAD_PRIORITY       (25)
#define DSI_TOUCH_THREAD_TIMESLICE      (10)

#define MAXIMUM_SUPPORTED_POINTS        (10)

struct touch_regs
{
    uint8_t device_mode;
    uint8_t gesture_id;
    uint8_t num_points;
    struct touch
    {
        uint8_t xh;
        uint8_t xl;
        uint8_t yh;
        uint8_t yl;
        uint8_t res1;
        uint8_t res2;
    } point[MAXIMUM_SUPPORTED_POINTS];
};

static void dsi_touch_thread_entry(void *param)
{
    static volatile uint32_t touchbuf;
    touchbuf = bcm271x_mbox_get_touch(); //0x0f436000

    if(touchbuf == RT_NULL)
    {
        rt_kprintf("init dsi touch err!\n");
        return;
    }

    while (1)
    {
        struct touch_regs *regs = (struct touch_regs *)touchbuf;
        if ((regs->num_points > 0) && (regs->num_points < MAXIMUM_SUPPORTED_POINTS))
        {
            //only one touch point
            touch_x = (((int)regs->point[0].xh & 0xf) << 8) + regs->point[0].xl;
            touch_y = (((int)regs->point[0].yh & 0xf) << 8) + regs->point[0].yl;
            touch_state = 1;
        }
        else
        {
            touch_state = 0;
        }
        rt_thread_mdelay(50);
    }
}

static rt_ssize_t dsi_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
    rt_uint16_t* touchxy = (rt_uint16_t *)buf;
    if((read_num != 0) && (touch_state == 1))
    {
        touchxy[0] = touch_x;
        touchxy[1] = touch_y;
        touch_state = 0;
        return read_num;
    }
    else
    {
        return 0;
    }
}

static rt_err_t dsi_control(struct rt_touch_device *device, int cmd, void *data)
{
    return RT_EOK;
}

static struct rt_touch_ops dsi_touch_ops =
{
    .touch_readpoint = dsi_read_point,
    .touch_control = dsi_control,
};

static int hw_dsi_touch_init(void)
{
    //touch sem
    rt_sem_init(&dsi_touch_ack, "dsi_touch_ack", 0, RT_IPC_FLAG_FIFO);

    dsi_touch_tid = rt_thread_create("dsi_touch",
                            dsi_touch_thread_entry, RT_NULL,
                            DSI_TOUCH_THREAD_STACK_SIZE,
                            DSI_TOUCH_THREAD_PRIORITY, DSI_TOUCH_THREAD_TIMESLICE);
    if (dsi_touch_tid != RT_NULL)
        rt_thread_startup(dsi_touch_tid);

    touch_device = (rt_touch_t)rt_calloc(1, sizeof(struct rt_touch_device));

    if (touch_device == RT_NULL)
        return -RT_ERROR;

    /* register touch device */
    touch_device->info.type = RT_TOUCH_TYPE_RESISTANCE;
    touch_device->info.vendor = RT_TOUCH_VENDOR_UNKNOWN;
    //rt_memcpy(&touch_device->config, cfg, sizeof(struct rt_touch_config));
    touch_device->ops = &dsi_touch_ops;
    rt_hw_touch_register(touch_device, "dsi_touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
    return 0;
}
INIT_DEVICE_EXPORT(hw_dsi_touch_init);

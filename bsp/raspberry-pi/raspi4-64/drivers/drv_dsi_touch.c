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
#include <drivers/touch.h>
#include <ioremap.h>
#include <mmu.h>

#ifdef RT_USING_SMART
#include <lwp.h>
#include <lwp_user_mm.h>
#endif

#include <hypercall.h>

#ifdef BSP_USING_TOUCH

#include "mbox.h"
#include "drv_dsi_touch.h"

#define DBG_TAG "dsi_touch"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_touch_t touch_device = RT_NULL;
static struct rt_semaphore dsi_touch_ack;

static rt_uint32_t touch_x;
static rt_uint32_t touch_y;
static rt_uint32_t touch_state = 0;

static rt_thread_t dsi_touch_tid = RT_NULL;
#define DSI_TOUCH_THREAD_STACK_SIZE (4096)
#define DSI_TOUCH_THREAD_PRIORITY   (25)
#define DSI_TOUCH_THREAD_TIMESLICE  (10)

#define MAXIMUM_SUPPORTED_POINTS    (10)

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

struct drv_mouse_device
{
    struct rt_device parent;
    struct rt_touch_data touchdata;
    int channel;
};

struct drv_mouse_device _mouse;

static void post_event(rt_uint16_t x, rt_uint16_t y, rt_uint8_t event)
{
    struct rt_touch_data *minfo = &_mouse.touchdata;
    struct rt_channel_msg ch_msg;

    LOG_D("event:%d, x:%d, y:%d\n", event, x, y);

    minfo->x_coordinate = x;
    minfo->y_coordinate = y;
    minfo->event = event;
    ch_msg.type = RT_CHANNEL_RAW;
    ch_msg.u.d = (void *)(size_t)event;
    rt_channel_send(_mouse.channel, &ch_msg);
}

static void dsi_touch_thread_entry(void *param)
{
    static volatile unsigned long touchbuf;
    touchbuf = bcm271x_mbox_get_touch();

    if (touchbuf == RT_NULL)
    {
        rt_kprintf("init dsi touch err!\n");
        return;
    }

#ifdef BSP_USING_VM_MODE
    if (rt_hv_stage2_map((unsigned long)touchbuf, 0x1000))
    {
        rt_kprintf("alloc mmio from hyper fail!\n");
        return;
    }
#endif

    touchbuf = (unsigned long)rt_ioremap((void *)touchbuf, 0x1000);

    while (1)
    {
        struct touch_regs *regs = (struct touch_regs *)touchbuf;
        if ((regs->num_points > 0) && (regs->num_points < MAXIMUM_SUPPORTED_POINTS))
        {
            /* only one touch point */
            touch_x = (((int)regs->point[0].xh & 0xf) << 8) + regs->point[0].xl;
            touch_y = (((int)regs->point[0].yh & 0xf) << 8) + regs->point[0].yl;
            if (!touch_state)
            {
                post_event(touch_x, touch_y, RT_TOUCH_EVENT_DOWN);
            }
            else
            {
                post_event(touch_x, touch_y, RT_TOUCH_EVENT_MOVE);
            }
            touch_state = 1;
        }
        else
        {
            if (touch_state)
            {
                post_event(touch_x, touch_y, RT_TOUCH_EVENT_UP);
            }
            touch_state = 0;
        }
        rt_thread_mdelay(1);
    }
}

static rt_size_t dsi_read_point(struct rt_touch_device *touch, void *buf, rt_size_t read_num)
{
    rt_uint16_t* touchxy = (rt_uint16_t *)buf;

    if ((read_num != 0) && (touch_state == 1))
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

static rt_err_t drv_mouse_init(struct rt_device *device)
{
    struct drv_mouse_device *mouse = (struct drv_mouse_device*)device;

    return RT_EOK;
}

static rt_err_t drv_mouse_control(struct rt_device *device, int cmd, void *args)
{
    switch (cmd)
    {
#define CMD_MOUSE_SET_NOTIFY 0 /* arg is shmid, in the shm, a sem point is given */
    case CMD_MOUSE_SET_NOTIFY:
        *(unsigned long *)args = (rt_uint32_t)(unsigned long)lwp_map_user_phy(lwp_self(), RT_NULL, (uint32_t*)((size_t)&_mouse.touchdata + PV_OFFSET), sizeof(struct rt_touch_data), 1);
        break;
    default:
            break;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops _mouse_ops =
{
    drv_mouse_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    drv_mouse_control
};
#endif

static int hw_dsi_touch_init(void)
{
    struct rt_device *device = &_mouse.parent;

#ifdef RT_USING_DEVICE_OPS
    device->ops     = &_mouse_ops;
#else
    device->init    = drv_mouse_init;
    device->open    = RT_NULL;
    device->close   = RT_NULL;
    device->read    = RT_NULL;
    device->write   = RT_NULL;
    device->control = drv_mouse_control;
#endif
    rt_device_register(device, "mouse", RT_DEVICE_FLAG_RDWR);
    _mouse.channel = rt_channel_open("mouse", O_CREAT);

    /* touch sem */
    rt_sem_init(&dsi_touch_ack, "dsi_touch_ack", 0, RT_IPC_FLAG_FIFO);

    dsi_touch_tid = rt_thread_create("dsi_touch",
                            dsi_touch_thread_entry, RT_NULL,
                            DSI_TOUCH_THREAD_STACK_SIZE,
                            DSI_TOUCH_THREAD_PRIORITY, DSI_TOUCH_THREAD_TIMESLICE);
    if (dsi_touch_tid != RT_NULL)
    {
        rt_thread_startup(dsi_touch_tid);
    }

    touch_device = (rt_touch_t)rt_malloc(sizeof(struct rt_touch_device));

    if (touch_device == RT_NULL)
    {
        return -RT_ERROR;
    }

    /* register touch device */
    touch_device->info.type = RT_TOUCH_TYPE_RESISTANCE;
    touch_device->info.vendor = RT_TOUCH_VENDOR_UNKNOWN;

    touch_device->ops = &dsi_touch_ops;
    rt_hw_touch_register(touch_device, "dsi_touch", RT_DEVICE_FLAG_INT_RX, RT_NULL);
    return 0;
}
INIT_APP_EXPORT(hw_dsi_touch_init);
#endif /* BSP_USING_TOUCH */

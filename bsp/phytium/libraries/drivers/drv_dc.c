/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-11-07     wangzongqiang     first version
 *
 */
#include <string.h>
#include "rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#define LOG_TAG      "dc_drv"
#include "drv_log.h"
#include "drv_dc.h"
#include "mm_aspace.h"
#include "fparameters.h"
#include "fdcdp.h"
#include "fdc.h"
#include "fdp_hw.h"


#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif
static  rt_uint8_t _rt_framebuffer[1024 * 768 * 4] __aligned(128) = {0};

static struct  rt_device_graphic_info _dc_info;

typedef struct
{
    u32 bit_depth;
    u32 bpc;
    u32 color_depth;
    u32 clock_mode;
    u32 color_rep;
    u32 width;
    u32 height;
} FuserCfg;

static const FuserCfg user_cfg = {
    .bit_depth = 8,
    .bpc = 8,
    .color_depth = 32,
    .clock_mode = 1,
    .color_rep = 0,
    .width = 640,
    .height = 480
};

void rt_hw_dc_register(struct phytium_dc_bus *dc_control_bus, const char *name, rt_uint32_t flag, void *data);

static rt_err_t dc_config(struct phytium_dc_bus *dc_control_bus)
{
    RT_ASSERT(dc_control_bus);
    rt_uint32_t chan = dc_control_bus->fdc_id;
    FDcDp *instance_p = &dc_control_bus->dc_handle;

    return RT_EOK;
}

static rt_err_t rt_dc_init(struct phytium_dc_bus  *device)
{
    RT_ASSERT(device != RT_NULL);
    rt_err_t ret;
    FDcDp *instance_p = &device->dc_handle;
    rt_uint32_t chan = device->fdc_id;

    FDcDpCfgInitialize(instance_p, chan);
    instance_p->dc_instance_p[chan].config = *FDcLookupConfig(chan);
    instance_p->dp_instance_p[chan].config = *FDpLookupConfig(chan);
    instance_p->dc_instance_p[chan].crtc.bpc = user_cfg.bpc;
    instance_p->dc_instance_p[chan].color_depth = user_cfg.color_depth;
    instance_p->dc_instance_p[chan].channel = chan;
    instance_p->dc_instance_p[chan].fb_addr = (uintptr)_rt_framebuffer;/*当前例程虚拟地址和物理地址一致，实际需要根据需要进行映射*/
    instance_p->dc_instance_p[chan].fb_virtual = (uintptr)_rt_framebuffer;
    instance_p->dp_instance_p[chan].trans_config.clock_mode = user_cfg.clock_mode;
    instance_p->dp_instance_p[chan].trans_config.color_rep_format = user_cfg.color_rep;
    instance_p->dp_instance_p[chan].trans_config.bit_depth = user_cfg.bit_depth;

    FDcDpGeneralCfgInitial(instance_p, chan);
    _dc_info.framebuffer = (rt_uint8_t *)instance_p->dc_instance_p[chan].fb_addr;
    _dc_info.bits_per_pixel = DISPLAY_COLOR_DEPTH;
    _dc_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
    _dc_info.width = FB_XSIZE;
    _dc_info.height = FB_YSIZE;
    rt_hw_dc_register(device, device->name, RT_DEVICE_FLAG_RDWR, NULL);
    dc_config(device);
    ret = FDcDpInitial(instance_p, device->fdc_id, user_cfg.width, user_cfg.height);
    if (ret != RT_EOK)
    {
        LOG_E("Init dc failed, ret: 0x%x", ret);
        return -RT_ERROR;;
    }
    return RT_EOK;
}

static rt_err_t rt_dc_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev);
    struct phytium_dc_bus *dc_bus;
    dc_bus = (struct phytium_dc_bus *)(dev);

    switch (cmd)
    {
        case RTGRAPHIC_CTRL_RECT_UPDATE:
            break;
        case RTGRAPHIC_CTRL_POWERON:
            break;
        case RTGRAPHIC_CTRL_POWEROFF:
            break;
        case RTGRAPHIC_CTRL_GET_INFO:
            rt_memcpy(args, &_dc_info, sizeof(_dc_info));
            break;
        case RTGRAPHIC_CTRL_SET_MODE:
            break;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops dc_ops =
{
    rt_dc_init,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_dc_control
};
#endif

void rt_hw_dc_register(struct phytium_dc_bus *dc_control_bus, const char *name, rt_uint32_t flag, void *data)
{
    RT_ASSERT(dc_control_bus != RT_NULL);
    struct rt_device *dc;
    dc = &(dc_control_bus->parent);
    dc->type = RT_Device_Class_Graphic;
#ifdef RT_USING_DEVICE_OPS
    dc->ops = &dc_ops;
#else
    dc->init = rt_dc_init;
    dc->control = rt_dc_control;
#endif
    dc->user_data = data;
    /* register Display Controller device to RT-Thread */
    rt_device_register(dc, name, RT_DEVICE_FLAG_RDWR);
}

#if defined(RT_USING_DC_CHANNEL0)
    static struct phytium_dc_bus  dev_dc0;
#endif
#if defined(RT_USING_DC_CHANNEL1)
    static struct phytium_dc_bus  dev_dc1;
#endif

int rt_hw_dc_init(void)
{
#if defined(RT_USING_DC_CHANNEL0)
    dev_dc0.name = "DC0";
    dev_dc0.fdc_id = FDCDP_ID0;
    rt_dc_init(&dev_dc0);
#endif
#if defined(RT_USING_DC_CHANNEL1)
    dev_dc1.name = "DC1";
    dev_dc1.fdc_id = FDCDP_ID1;
    rt_dc_init(&dev_dc1);
#endif
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_dc_init);

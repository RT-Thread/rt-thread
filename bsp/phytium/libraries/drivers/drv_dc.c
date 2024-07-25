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
#include "mm_aspace.h"
#include "drv_log.h"
#include "drv_dc.h"
#include "fparameters.h"
#include "fdcdp.h"
#include "fdc.h"
#include "fdp_hw.h"
#include "fdc_common_hw.h"

#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif
static  rt_uint16_t _rt_framebuffer[1024 * 768 * 4] __aligned(128);

static struct  rt_device_graphic_info _dc_info;

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
    FDcDpCfgInitialize(instance_p);
    rt_uint32_t chan = device->fdc_id;
    instance_p->user_config[chan].color_depth = DISPLAY_COLOR_DEPTH;
    instance_p->user_config[chan].width = FB_XSIZE;
    instance_p->user_config[chan].height = FB_YSIZE;
    instance_p->user_config[chan].refresh_rate = DISPLAY_REFRESH_RATE_60;
    instance_p->user_config[chan].multi_mode = 0;
    instance_p->user_config[chan].fb_phy = _rt_framebuffer;
    instance_p->user_config[chan].fb_virtual = _rt_framebuffer;
    instance_p->dc_instance_p[chan].config = *FDcLookupConfig(chan);
    instance_p->dp_instance_p[chan].config = *FDpLookupConfig(chan);
#ifdef RT_USING_SMART
    instance_p->user_config[chan].fb_phy = instance_p->user_config[chan].fb_phy +  PV_OFFSET;/*the FB addr iomap length is x_size * y_size * 4 */
    instance_p->dc_instance_p[chan].config.dcch_baseaddr = (uintptr)rt_ioremap((void *)instance_p->dc_instance_p[chan].config.dcch_baseaddr, 0x1000);/*the dc channel addr iomap length is 0x1000*/
    instance_p->dc_instance_p[chan].config.dcctrl_baseaddr = (uintptr)rt_ioremap((void *)instance_p->dc_instance_p[chan].config.dcctrl_baseaddr, 0x4000);/*the dc control addr iomap length is 0x4000*/
    instance_p->dp_instance_p[chan].config.dp_channe_base_addr = (uintptr)rt_ioremap((void *)instance_p->dp_instance_p[chan].config.dp_channe_base_addr, 0x4000); /*the dc control addr iomap length is 0x4000*/
    instance_p->dp_instance_p[chan].config.dp_phy_base_addr = (size_t)rt_ioremap((void *) instance_p->dp_instance_p[chan].config.dp_phy_base_addr,  0x100000);/*the dc control addr iomap length is 0x100000*/
#endif
    _dc_info.bits_per_pixel = DISPLAY_COLOR_DEPTH;
    _dc_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
    _dc_info.framebuffer = (rt_uint8_t *)instance_p->user_config[chan].fb_virtual;
    _dc_info.width = FB_XSIZE;
    _dc_info.height = FB_YSIZE;
    rt_hw_dc_register(device, device->name, RT_DEVICE_FLAG_RDWR, NULL);
    dc_config(device);

    ret = FDcDpInitialize(instance_p, device->fdc_id);
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

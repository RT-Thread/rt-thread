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

static  rt_uint16_t _rt_framebuffer[1024*768*4] __aligned(128);
struct phytium_dc_bus
{
    struct rt_device parent;
    FDcDp  dc_handle;/* data */
    const char *name;
    rt_uint32_t fdc_id;
};

static struct  rt_device_graphic_info _dc_info;
static struct phytium_dc_bus  dev_dc;

static rt_err_t dc_config(struct phytium_dc_bus *dc_control_bus)
{
    RT_ASSERT(dc_control_bus);
    rt_uint32_t chan = dc_control_bus->fdc_id;
    FDcDp *instance_p = &dc_control_bus->dc_handle;

    return RT_EOK;
}

static rt_err_t rt_dc_init(struct rt_device *dev)
{
    RT_ASSERT(dev != RT_NULL);
    rt_err_t ret;
    struct phytium_dc_bus  *device;
    device = (struct phytium_dc_bus *)dev;
    FDcDp *instance_p = &device->dc_handle;
    int chan = device->fdc_id;
    dc_config(device);

    ret = FDcDpInitialize(instance_p, chan);
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
static void rt_hw_dc_register(struct phytium_dc_bus *dc_control_bus, const char *name, rt_uint32_t flag, void *data)
{
    RT_ASSERT(dc_control_bus != RT_NULL);
    struct rt_device *dc;
    dc = &(dc_control_bus->parent);
    dc->type = RT_Device_Class_Graphic;
    dc->init = rt_dc_init;
    dc->open = RT_NULL;
    dc->close = RT_NULL;
    dc->control = rt_dc_control;
    dc->user_data = data;
    /* register Display Controller device to RT-Thread */
    rt_device_register(dc, "dc", RT_DEVICE_FLAG_RDWR);
}

int rt_hw_dc_init(void)
{
#if defined(RT_USING_DC_CHANNEL0)
    dev_dc.name = "DC0";
    dev_dc.fdc_id = FDCDP_ID0;
#elif defined(RT_USING_DC_CHANNEL1)
    dev_dc.name = "DC1";
    dev_dc.fdc_id = FDCDP_ID1;
#elif defined(RT_USING_DOUBLE)
    dev_dc.name = "DC0 + DC1";
    dev_dc.fdc_id = FDCDP_INSTANCE_NUM;
#endif
    FDcDpCfgInitialize(&dev_dc.dc_handle);

    dev_dc.dc_handle.user_config[dev_dc.fdc_id].color_depth = DISPLAY_COLOR_DEPTH;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].width = FB_XSIZE;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].height = FB_YSIZE;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].refresh_rate = DISPLAY_REFRESH_RATE_60;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].multi_mode = 0;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].fb_phy = _rt_framebuffer;
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].fb_virtual = _rt_framebuffer;
    dev_dc.dc_handle.dc_instance_p[dev_dc.fdc_id].config = *FDcLookupConfig(dev_dc.fdc_id);
    dev_dc.dc_handle.dp_instance_p[dev_dc.fdc_id].config = *FDpLookupConfig(dev_dc.fdc_id);
#ifdef RT_USING_SMART
    dev_dc.dc_handle.user_config[dev_dc.fdc_id].fb_phy = dev_dc.dc_handle.user_config[dev_dc.fdc_id].fb_phy +  PV_OFFSET;/*the FB addr iomap length is x_size * y_size * 4 */
    dev_dc.dc_handle.dc_instance_p[dev_dc.fdc_id].config.dcch_baseaddr = (uintptr)rt_ioremap((void *)dev_dc.dc_handle.dc_instance_p[dev_dc.fdc_id].config.dcch_baseaddr, 0x1000);/*the dc channel addr iomap length is 0x1000*/
    dev_dc.dc_handle.dc_instance_p[dev_dc.fdc_id].config.dcctrl_baseaddr = (uintptr)rt_ioremap((void *)dev_dc.dc_handle.dc_instance_p[dev_dc.fdc_id].config.dcctrl_baseaddr, 0x4000);/*the dc control addr iomap length is 0x4000*/
    dev_dc.dc_handle.dp_instance_p[dev_dc.fdc_id].config.dp_channe_base_addr = (uintptr)rt_ioremap((void *)dev_dc.dc_handle.dp_instance_p[dev_dc.fdc_id].config.dp_channe_base_addr, 0x4000); /*the dc control addr iomap length is 0x4000*/
    dev_dc.dc_handle.dp_instance_p[dev_dc.fdc_id].config.dp_phy_base_addr = (size_t)rt_ioremap((void *) dev_dc.dc_handle.dp_instance_p[dev_dc.fdc_id].config.dp_phy_base_addr,  0x100000);/*the dc control addr iomap length is 0x100000*/
#endif
    _dc_info.bits_per_pixel = DISPLAY_COLOR_DEPTH;
    _dc_info.pixel_format = RTGRAPHIC_PIXEL_FORMAT_RGB565P;
    _dc_info.framebuffer = (rt_uint8_t *)dev_dc.dc_handle.user_config[dev_dc.fdc_id].fb_virtual;
    _dc_info.width = FB_XSIZE;
    _dc_info.height = FB_YSIZE;
    rt_hw_dc_register(&dev_dc,"dc",RT_DEVICE_FLAG_RDWR,NULL);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_dc_init);


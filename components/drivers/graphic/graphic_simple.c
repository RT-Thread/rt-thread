/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "graphic.simple"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static rt_uint32_t edid_dpi_to_mm(rt_uint32_t dpi, rt_uint32_t res)
{
    return res * 254 / 10 / dpi;
}

static void edid_checksum(rt_uint8_t *edid, rt_size_t len)
{
    rt_uint32_t sum = 0;

    for (int i = 0; i < len; ++i)
    {
        sum += edid[i];
    }

    sum &= 0xff;

    if (sum)
    {
        edid[len] = 0x100 - sum;
    }
}

static void fill_edid(struct rt_graphic_device *gdev,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t refresh_hz)
{
    union
    {
        rt_uint32_t u32;
        rt_uint16_t u16;
    } value;
    int dt_idx = 0;
    int width_mm, height_mm;
    rt_uint64_t clock;
    rt_uint32_t xfront, xsync, xblank, yfront, ysync, yblank;
    struct edid *edid = &gdev->edid;
    struct detailed_timing *dt;
    struct detailed_pixel_timing *dpt;
    struct detailed_non_pixel *dnp;

    refresh_hz = refresh_hz ? : 75000;
    width_mm = edid_dpi_to_mm(100, width);
    height_mm = edid_dpi_to_mm(100, height);

    /* EDID: timings */
    xfront = width * 25 / 100;
    xsync = width * 3 / 100;
    xblank = width * 35 / 100;
    yfront = height * 5 / 1000;
    ysync = height * 5 / 1000;
    yblank = height * 35 / 1000;
    clock = ((rt_uint64_t)refresh_hz * (width + xblank) * (height + yblank)) / 10000000;

    if (width >= 4096 || height >= 4096 || clock >= 65536)
    {
        LOG_E("%s: Large screen %ux%u@%uHz is not supported in simple",
                rt_dm_dev_get_name(&gdev->parent), width, height, clock);

        RT_ASSERT(0);
    }

    /* EDID: extensions */

    /* EDID: header information */
    edid->header[0] = 0x00;
    edid->header[1] = 0xff;
    edid->header[2] = 0xff;
    edid->header[3] = 0xff;
    edid->header[4] = 0xff;
    edid->header[5] = 0xff;
    edid->header[6] = 0xff;
    edid->header[7] = 0x00;

    /* Vendor id */
    value.u16 = rt_cpu_to_be16(
            ((('R' - '@') & 0x1f) << 10) |
            ((('T' - '@') & 0x1f) <<  5) |
            ((('T' - '@') & 0x1f) <<  0));
    rt_memcpy(edid->mfg_id, &value.u16, sizeof(edid->mfg_id));

    /* Product code */
    value.u16 = rt_cpu_to_le16(0x1234);
    rt_memcpy(edid->prod_code, &value.u16, sizeof(edid->prod_code));

    /* Serial number */
    edid->serial = rt_cpu_to_le32(0);

    /* Manufacture week and year */
    edid->mfg_week = 42;
    edid->mfg_year = 2014 - 1990;

    /* Version */
    edid->version = 1;
    edid->revision = 4;

    /* EDID: basic display parameters */

    /* Video input: digital, 8bpc, displayport */
    edid->input = 0xa5;

    /* Screen size */
    edid->width_cm = width_mm / 10;
    edid->height_cm = height_mm / 10;

    /* Gamma: 2.2 */
    edid->gamma = 220 - 100;

    /* Features: STD sRGB, preferred timing */
    edid->features = 0x06;

    /* EDID: chromaticity coordinates */

    /*
     * STD sRGB colorspace:
     *                      X       Y
     *      red:            0.6400, 0.3300
     *      green:          0.3000, 0.6000
     *      blue:           0.1500, 0.0600
     *      white point:    0.3127, 0.3290
     *
     *  value = (uint32_t)(value * 1024 + 0.5)
     *
     *      red_x   = 0.6400 * 1024 + 0.5 = 655.86      => 655
     *      red_y   = 0.3300 * 1024 + 0.5 = 338.42      => 338
     *      green_x = 0.3000 * 1024 + 0.5 = 307.7       => 307
     *      green_y = 0.6000 * 1024 + 0.5 = 614.9       => 614
     *      blue_x  = 0.1500 * 1024 + 0.5 = 154.1       => 154
     *      blue_y  = 0.0600 * 1024 + 0.5 = 61.94       => 61
     *      white_x = 0.3127 * 1024 + 0.5 = 320.7048    => 320
     *      white_y = 0.3290 * 1024 + 0.5 = 337.396     => 337
     */
    edid->red_green_lo = (((655 & 0x03) << 6) |     /* red_x */
                          ((338 & 0x03) << 4) |     /* red_y */
                          ((307 & 0x03) << 2) |     /* green_x */
                          ((614 & 0x03) << 0));     /* green_y */
    edid->black_white_lo = (((154 & 0x03) << 6) |   /* blue_x */
                            ((154 & 0x03) << 4) |   /* blue_y */
                            ((320 & 0x03) << 2) |   /* white_x */
                            ((337 & 0x03) << 0));   /* white_y */
    edid->red_x = 655 >> 2;                         /* red_x */
    edid->red_y = 338 >> 2;                         /* red_y */
    edid->green_x = 307 >> 2;                       /* green_x */
    edid->green_y = 614 >> 2;                       /* green_y */
    edid->blue_x = 154 >> 2;                        /* blue_x */
    edid->blue_y = 154 >> 2;                        /* blue_y */
    edid->white_x = 320 >> 2;                       /* white_x */
    edid->white_y = 337 >> 2;                       /* white_y */

    /* EDID: established timing bitmap */
    /* EDID: standard timing information */

    /* EDID: descriptor blocks */
    dt = &edid->detailed_timings[dt_idx++];
    dpt = &dt->data.pixel_data;

    dt->pixel_clock = rt_cpu_to_le16(clock);
    dpt->hactive_lo = width & 0xff;
    dpt->hblank_lo = xblank & 0xff;
    dpt->hactive_hblank_hi = (((width & 0xf00) >> 4) | ((xblank & 0xf00) >> 8));

    dpt->vactive_lo = height & 0xff;
    dpt->vblank_lo = yblank & 0xff;
    dpt->vactive_vblank_hi = (((height & 0xf00) >> 4) | ((yblank & 0xf00) >> 8));

    dpt->hsync_offset_lo = xfront & 0xff;
    dpt->hsync_pulse_width_lo = xsync  & 0xff;

    dpt->vsync_offset_pulse_width_lo = (((yfront & 0x00f) << 4) |
                                        ((ysync & 0x00f) << 0));
    dpt->hsync_vsync_offset_pulse_width_hi = (((xfront & 0x300) >> 2) |
                                              ((xsync  & 0x300) >> 4) |
                                              ((yfront & 0x030) >> 2) |
                                              ((ysync  & 0x030) >> 4));

    dpt->width_mm_lo = width_mm & 0xff;
    dpt->height_mm_lo = height_mm & 0xff;
    dpt->width_height_mm_hi = (((width_mm & 0xf00) >> 4) |
                               ((height_mm & 0xf00) >> 8));

    dpt->misc = 0x18;

    /* XTRA3 STD */
    dt = &edid->detailed_timings[dt_idx++];
    dnp = &dt->data.other_data;
    dnp->type = EDID_DETAIL_EST_TIMINGS;
    dnp->data.timings[0].hsize = 10;

    /* Ranges */
    dt = &edid->detailed_timings[dt_idx++];
    dnp = &dt->data.other_data;
    dnp->type = EDID_DETAIL_MONITOR_RANGE;
    dnp->data.range.min_vfreq = 50;
    dnp->data.range.max_vfreq = 125;
    dnp->data.range.min_hfreq_khz =  30;
    dnp->data.range.max_hfreq_khz = 160;
    dnp->data.range.pixel_clock_mhz = 2550 / 10;
    dnp->data.range.flags = 0x01;
    rt_memcpy(&dnp->data.range.flags + 1, "\n      ", 7);

    while (dt_idx < RT_ARRAY_SIZE(edid->detailed_timings))
    {
        /* Dummy */
        dt = &edid->detailed_timings[dt_idx++];
        dnp = &dt->data.other_data;
        dnp->type = 0x10;
    }

    /* EDID: display id extensions */

    /* EDID: checksum */
    edid_checksum((void *)edid, 127);
}

rt_err_t rt_graphic_device_simple_edid(struct rt_graphic_device *gdev,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t refresh_hz)
{
    if (!gdev || !width || !height)
    {
        return -RT_EINVAL;
    }

    fill_edid(gdev, width, height, refresh_hz);

    return RT_EOK;
}

static const struct rt_graphic_device_ops graphic_device_simple_ops =
{
};

rt_err_t rt_graphic_device_simple_register(struct rt_graphic_device *gdev,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t refresh_hz,
        const struct rt_graphic_plane_ops *plane_ops,
        const rt_uint32_t *modes, rt_uint32_t modes_nr)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    if (!gdev || !width || !height || !plane_ops || !modes || !modes_nr)
    {
        return -RT_EINVAL;
    }

    if (!gdev->ops)
    {
        gdev->ops = &graphic_device_simple_ops;
    }

    plane = rt_graphic_device_alloc_plane(gdev, 0, plane_ops, modes, modes_nr,
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);

    if (!plane)
    {
        return -RT_EINVAL;
    }

    if ((err = rt_graphic_device_add_plane(gdev, plane)))
    {
        goto _free_plane;
    }

    rt_graphic_device_simple_edid(gdev, width, height, refresh_hz);

    err = rt_graphic_device_register(gdev);

_free_plane:
    if (err)
    {
        rt_free(plane);
    }

    return err;
}

rt_err_t rt_graphic_device_simple_unregister(struct rt_graphic_device *gdev)
{
    return rt_graphic_device_unregister(gdev);
}

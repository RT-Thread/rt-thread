/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __GRAPHIC_DM_H__
#define __GRAPHIC_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <drivers/lcd.h>
#include <drivers/core/dm.h>
#include <drivers/byteorder.h>
#include <drivers/classes/graphic.h>

#undef rt_graphix_ops
#define rt_graphix_ops(dev) \
    rt_graphic_device_switch_primary(rt_container_of(dev, struct rt_graphic_device, parent))

rt_packed(struct est_timings
{
    rt_uint8_t t1;
    rt_uint8_t t2;
    rt_uint8_t mfg_rsvd;
});

rt_packed(struct std_timing
{
    /* Need to multiply by 8 then add 248 */
    rt_uint8_t hsize;
    rt_uint8_t vfreq_aspect;
});

rt_packed(struct detailed_pixel_timing
{
    rt_uint8_t hactive_lo;
    rt_uint8_t hblank_lo;
    rt_uint8_t hactive_hblank_hi;
    rt_uint8_t vactive_lo;
    rt_uint8_t vblank_lo;
    rt_uint8_t vactive_vblank_hi;
    rt_uint8_t hsync_offset_lo;
    rt_uint8_t hsync_pulse_width_lo;
    rt_uint8_t vsync_offset_pulse_width_lo;
    rt_uint8_t hsync_vsync_offset_pulse_width_hi;
    rt_uint8_t width_mm_lo;
    rt_uint8_t height_mm_lo;
    rt_uint8_t width_height_mm_hi;
    rt_uint8_t hborder;
    rt_uint8_t vborder;
    rt_uint8_t misc;
});

rt_packed(struct detailed_data_string
{
    rt_uint8_t str[13];
});

rt_packed(struct detailed_data_monitor_range
{
    rt_uint8_t min_vfreq;
    rt_uint8_t max_vfreq;
    rt_uint8_t min_hfreq_khz;
    rt_uint8_t max_hfreq_khz;
    /* Need to multiply by 10 */
    rt_uint8_t pixel_clock_mhz;
    rt_uint8_t flags;

    union
    {
        rt_packed(struct
        {
            rt_uint8_t reserved;
            /* Need to multiply by 2 */
            rt_uint8_t hfreq_start_khz;
            /* Need to divide by 2 */
            rt_uint8_t c;
            rt_le16_t m;
            rt_uint8_t k;
            /* Need to divide by 2 */
            rt_uint8_t j;
        }) gtf2;
        rt_packed(struct
        {
            rt_uint8_t version;
            /* High 6 bits: extra clock resolution */
            rt_uint8_t data1;
            /* Plus low 2 of above: max hactive */
            rt_uint8_t data2;
            rt_uint8_t supported_aspects;
            /* Preferred aspect and blanking support */
            rt_uint8_t flags;
            rt_uint8_t supported_scalings;
            rt_uint8_t preferred_refresh;
        }) cvt;
    } formula;
});

rt_packed(struct detailed_data_wpindex
{
    /* Lower 2 bits each */
    rt_uint8_t white_yx_lo;
    rt_uint8_t white_x_hi;
    rt_uint8_t white_y_hi;
    /* Need to divide by 100 then add 1 */
    rt_uint8_t gamma;
});

rt_packed(struct cvt_timing
{
    rt_uint8_t code[3];
});

rt_packed(struct detailed_non_pixel
{
    rt_uint8_t pad1;
#define EDID_DETAIL_EST_TIMINGS     0xf7
#define EDID_DETAIL_CVT_3BYTE       0xf8
#define EDID_DETAIL_COLOR_MGMT_DATA 0xf9
#define EDID_DETAIL_STD_MODES       0xfa
#define EDID_DETAIL_MONITOR_CPDATA  0xfb
#define EDID_DETAIL_MONITOR_NAME    0xfc
#define EDID_DETAIL_MONITOR_RANGE   0xfd
#define EDID_DETAIL_MONITOR_STRING  0xfe
#define EDID_DETAIL_MONITOR_SERIAL  0xff
    rt_uint8_t type;
    rt_uint8_t pad2;
    union
    {
        struct detailed_data_string str;
        struct detailed_data_monitor_range range;
        struct detailed_data_wpindex color;
        struct std_timing timings[6];
        struct cvt_timing cvt[4];
    } data;
});

rt_packed(struct detailed_timing
{
    /* Need to multiply by 10 KHz */
    rt_le16_t pixel_clock;

    union
    {
        struct detailed_pixel_timing pixel_data;
        struct detailed_non_pixel other_data;
    } data;
});

rt_packed(struct edid
{
    rt_uint8_t header[8];

    /* Vendor & product info */
    rt_uint8_t mfg_id[2];
    rt_uint8_t prod_code[2];
    rt_le32_t serial;
    rt_uint8_t mfg_week;
    rt_uint8_t mfg_year;

    /* EDID version */
    rt_uint8_t version;
    rt_uint8_t revision;

    /* Display info */
    rt_uint8_t input;
    rt_uint8_t width_cm;
    rt_uint8_t height_cm;
    rt_uint8_t gamma;
    rt_uint8_t features;

    /* Color characteristics */
    rt_uint8_t red_green_lo;
    rt_uint8_t black_white_lo;
    rt_uint8_t red_x;
    rt_uint8_t red_y;
    rt_uint8_t green_x;
    rt_uint8_t green_y;
    rt_uint8_t blue_x;
    rt_uint8_t blue_y;
    rt_uint8_t white_x;
    rt_uint8_t white_y;

    /* Est. timings and mfg rsvd timings */
    struct est_timings established_timings;

    /* Standard timings 1-8 */
    struct std_timing standard_timings[8];

    /* Detailing timings 1-4, 18 * 4 = 72 bytes */
    struct detailed_timing detailed_timings[4];

    /* Number of 128 byte ext. blocks */
    rt_uint8_t extensions;

    /* Checksum */
    rt_uint8_t checksum;
});

struct rt_graphic_device;
struct rt_graphic_device_ops;
struct rt_graphic_plane_ops;

enum rt_graphic_plane_prop
{
    RT_GRAPHIC_PLANE_PROP_Z = 0,
    RT_GRAPHIC_PLANE_PROP_ROTATE,
    RT_GRAPHIC_PLANE_PROP_ALPHA,

    RT_GRAPHIC_PLANE_PROP_MAX,
};

struct rt_graphic_plane
{
    rt_list_t list;
    char name[RT_NAME_MAX];

    int id;
#define RT_GRAPHIC_PLANE_TYPE_OVERLAY   0
#define RT_GRAPHIC_PLANE_TYPE_PRIMARY   1   /* Only one, add before register */
#define RT_GRAPHIC_PLANE_TYPE_CURSOR    2   /* Only one */
    rt_uint8_t type;

    rt_uint32_t x;
    rt_uint32_t y;
    rt_uint32_t z;
    rt_uint32_t width;
    rt_uint32_t height;
#define RT_GRAPHIC_PLANE_ROTATE_0       0   /*   +0 degrees */
#define RT_GRAPHIC_PLANE_ROTATE_90      1   /*  +90 degrees */
#define RT_GRAPHIC_PLANE_ROTATE_180     2   /* +180 degrees */
#define RT_GRAPHIC_PLANE_ROTATE_270     3   /* +270 degrees */
    rt_uint8_t rotate;
    rt_uint8_t alpha;                       /* 0 ~ 100 */

    rt_uint32_t line_length;
    rt_uint32_t bits_per_pixel;

    /* Support color modes: RTGRAPHIC_PIXEL_FORMAT_* */
    rt_uint32_t mode;
    rt_uint32_t modes_nr;
    const rt_uint32_t *modes;

    /* fb count = framebuffer_len / screen_len */
    void *framebuffer;
    rt_size_t screen_len;
    rt_size_t framebuffer_len;

    struct rt_graphic_device *graphic;
    const struct rt_graphic_plane_ops *ops;

    rt_uint8_t priv[0];
};

struct rt_graphic_plane_ops
{
    rt_err_t (*update)(struct rt_graphic_plane *plane, struct rt_device_rect_info *rect);
    rt_err_t (*fb_remap)(struct rt_graphic_plane *plane, rt_uint32_t mode, struct rt_device_rect_info *rect);
    rt_err_t (*fb_pan_display)(struct rt_graphic_plane *plane, struct rt_device_rect_info *rect);
    rt_err_t (*fb_cleanup)(struct rt_graphic_plane *plane);
    rt_err_t (*prop_set)(struct rt_graphic_plane *plane, enum rt_graphic_plane_prop prop, void *value);
};

struct rt_graphic_device
{
    struct rt_device parent;

    const struct rt_graphic_device_ops *ops;

    /* Display Power Manage System */
#define RT_GRAPHIC_DPMS_ON        0
#define RT_GRAPHIC_DPMS_STANDBY   1
#define RT_GRAPHIC_DPMS_SUSPEND   2
#define RT_GRAPHIC_DPMS_OFF       3
    rt_uint32_t dpms;

    rt_list_t overlay_nodes;
    struct rt_graphic_plane *primary_plane;
    struct rt_graphic_plane *cursor_plane;
    struct rt_dm_ida plane_ida;

    /* Display information */
    struct edid edid;

#ifdef RT_GRAPHIC_BACKLIGHT
    struct rt_backlight_device *backlight;
#endif
#define RT_GRAPHIC_UPDATE_MS 16
    struct rt_timer *update_timer;

    rt_atomic_t event_notifying;
    struct rt_device_notify event_notify;

    struct rt_spinlock lock;
};

struct rt_graphic_device_ops
{
    rt_err_t (*dpms_switch)(struct rt_graphic_device *gdev, rt_uint32_t dpms);

    rt_err_t (*set_brightness)(struct rt_graphic_device *gdev, rt_uint32_t brightness);
    rt_err_t (*get_brightness)(struct rt_graphic_device *gdev, rt_uint32_t *out_brightness);

    rt_err_t (*get_status)(struct rt_graphic_device *gdev, rt_uint32_t *out_status);

    rt_err_t (*wait_vsync)(struct rt_graphic_device *gdev);

    rt_err_t (*control)(struct rt_graphic_device *gdev, int cmd, void *args);

    /* Switching planes supported by device driver */
    struct rt_graphic_plane *(*current_plane)(struct rt_graphic_device *gdev);
};

rt_err_t rt_graphic_device_register(struct rt_graphic_device *gdev);
rt_err_t rt_graphic_device_unregister(struct rt_graphic_device *gdev);

struct rt_graphic_plane *rt_graphic_device_alloc_plane(struct rt_graphic_device *gdev,
        rt_size_t priv_size, const struct rt_graphic_plane_ops *ops,
        const rt_uint32_t *modes, rt_uint32_t modes_nr, rt_uint8_t type);
void rt_graphic_device_free_plane(struct rt_graphic_plane *plane);

rt_err_t rt_graphic_device_add_plane(struct rt_graphic_device *gdev,
        struct rt_graphic_plane *plane);
rt_err_t rt_graphic_device_del_plane(struct rt_graphic_device *gdev,
        struct rt_graphic_plane *plane);

void rt_graphic_device_hotplug_event(struct rt_graphic_device *gdev);

rt_err_t rt_graphic_device_update_auto(struct rt_graphic_device *gdev, rt_uint32_t update_ms);

void rt_graphic_device_enter(struct rt_graphic_device *gdev);
void rt_graphic_device_leave(struct rt_graphic_device *gdev);

rt_uint32_t rt_graphic_mode_bpp(rt_uint32_t mode);

struct rt_device_graphic_ops *rt_graphic_device_switch_primary(struct rt_graphic_device *gdev);

rt_err_t rt_graphic_device_simple_edid(struct rt_graphic_device *gdev,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t refresh_hz);

rt_err_t rt_graphic_device_simple_register(struct rt_graphic_device *gdev,
        rt_uint32_t width, rt_uint32_t height, rt_uint32_t refresh_hz,
        const struct rt_graphic_plane_ops *plane_ops,
        const rt_uint32_t *modes, rt_uint32_t modes_nr);
rt_err_t rt_graphic_device_simple_unregister(struct rt_graphic_device *gdev);

#ifdef RT_GRAPHIC_LOGO
rt_err_t rt_graphic_logo_change(void *data, int width, int height, int color_max);
rt_err_t rt_graphic_logo_render(struct rt_graphic_device *gdev);
#else
rt_inline rt_err_t rt_graphic_logo_change(void *data, int width, int height, int color_max)
{
    return RT_EOK;
}

rt_inline rt_err_t rt_graphic_logo_render(struct rt_graphic_device *gdev)
{
    return RT_EOK;
}
#endif /* RT_GRAPHIC_LOGO */

#endif /* __GRAPHIC_DM_H__ */

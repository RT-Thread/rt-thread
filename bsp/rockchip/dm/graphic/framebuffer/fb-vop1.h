/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __FB_VOP1_H__
#define __FB_VOP1_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define VOP1FB_CURSOR_W                 64
#define VOP1FB_CURSOR_H                 64
#define VOP1FB_OVERLAY_MAX              2

enum vop1fb_arch
{
    VOP1FB_ARCH_LITE = 0,
    VOP1FB_ARCH_BIG,
};

enum vop1fb_hw_format
{
    VOP1FB_FMT_ARGB8888 = 0,
    VOP1FB_FMT_RGB888,
    VOP1FB_FMT_RGB565,
};

struct vop1fb_win_regs
{
    rt_uint32_t ctrl0;
    rt_uint32_t vir;
    rt_uint32_t yrgb_mst;
    rt_uint32_t act_info;
    rt_uint32_t dsp_info;
    rt_uint32_t dsp_st;
    rt_uint32_t alpha;
};

struct vop1fb_win_desc
{
    const char *name;
    const struct vop1fb_win_regs *regs;
    rt_uint8_t z_order;
};

struct vop1fb_soc_data
{
    enum vop1fb_arch arch;
    const char *version;
    rt_size_t reg_size;
    rt_uint32_t cfg_done;
    const struct vop1fb_win_desc *primary;
    const struct vop1fb_win_desc *cursor;
    const struct vop1fb_win_desc *overlays;
    rt_size_t overlay_count;
};

struct vop1fb_plane_priv
{
    const struct vop1fb_win_desc *desc;
    rt_ubase_t dma_handle;
    rt_uint32_t pan_offset;
    rt_bool_t enabled;
};

struct vop1fb
{
    struct rt_graphic_device parent;

    const struct vop1fb_soc_data *soc;

    void *regs;
    rt_uint32_t display_w;
    rt_uint32_t display_h;

    rt_bool_t clk_enabled;
    struct rt_clk_array *clks;

    int irq;
    rt_atomic_t vsync;
    struct rt_semaphore vsync_sem;

    struct rt_graphic_plane *primary;
    struct rt_graphic_plane *cursor;
    struct rt_graphic_plane *overlays[VOP1FB_OVERLAY_MAX];
    rt_size_t overlay_count;

    rt_bool_t powered;
};

rt_uint32_t vop1fb_mode_to_hw(rt_uint32_t mode);
rt_uint32_t vop1fb_hw_to_bpp(rt_uint32_t hw_fmt);

#endif /* __FB_VOP1_H__ */

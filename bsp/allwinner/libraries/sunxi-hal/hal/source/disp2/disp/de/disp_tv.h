/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */


#ifndef __DISP_TV_H__
#define __DISP_TV_H__

#include "disp_private.h"

s32 disp_init_tv(void);     /* call by disp_display */
s32 disp_tv_set_func(struct disp_device *ptv, struct disp_tv_func *func);
s32 disp_tv_set_hpd(struct disp_device *ptv, u32 state);

struct disp_device_private_data {
    u32 enabled;
    bool suspended;

    enum disp_tv_mode tv_mode;

    struct disp_tv_func tv_func;

    struct disp_video_timings *video_info;

    struct disp_clk_info lcd_clk;

    struct clk *clk;

    struct clk *clk_parent;

    u32 irq_no;

    u32 frame_per_sec;
    u32 usec_per_line;
    u32 judge_line;
};

s32 disp_tv_suspend(struct disp_device *ptv);
s32 disp_tv_resume(struct disp_device *ptv);

#endif

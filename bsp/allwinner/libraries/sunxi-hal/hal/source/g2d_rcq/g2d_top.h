/*
 * g2d_top/g2d_top.h
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef _G2D_TOP_H
#define _G2D_TOP_H
#include <typedef.h>


void g2d_top_set_base(unsigned long base);
__u32 g2d_top_get_rcq_frame_cnt(void);
__s32 g2d_top_rcq_cfg_irq_query(void);
__s32 g2d_top_rcq_task_irq_query(void);
__s32 g2d_bsp_reset(void);
void g2d_top_rcq_update_en(__u32 en);
void g2d_top_rcq_irq_en(__u32 en);
__s32 g2d_top_mixer_sclk_div(__u32 div);
__s32 g2d_top_rot_sclk_div(__u32 div);
__s32 g2d_top_rot_reset(void);
__s32 g2d_top_mixer_reset(void);
void g2d_top_set_rcq_head(u64 addr, __u32 len);
__s32 g2d_bsp_open(void);
__s32 g2d_bsp_close(void);
void g2d_mixer_scan_order_fun(__u32 scan_order);
__s32 g2d_mixer_irq_query(void);
void g2d_mixer_irq_en(__u32 en);
void g2d_mixer_start(__u32 start);

#endif /*End of file*/

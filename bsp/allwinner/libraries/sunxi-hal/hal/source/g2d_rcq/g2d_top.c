/*
 * g2d_top/g2d_top.c
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

#include "g2d_driver_i.h"
#include "g2d_top.h"
#include "g2d_top_type.h"

static volatile struct g2d_top_reg *g2d_top;
static volatile struct g2d_mixer_glb_reg *mixer_glb;

void g2d_top_set_base(unsigned long base)
{
	g2d_top = (struct g2d_top_reg *)(base);
	mixer_glb = (struct g2d_mixer_glb_reg *)(base + 0x0100);
}

void g2d_mixer_scan_order_fun(__u32 scan_order)
{
	mixer_glb->mixer_ctrl.bits.scan_order = scan_order;
}

void g2d_mixer_start(__u32 start)
{
	mixer_glb->mixer_ctrl.bits.start = start;
}

void g2d_mixer_irq_en(__u32 en)
{
	mixer_glb->mixer_interrupt.bits.finish_irq_en = en;
}

__s32 g2d_mixer_irq_query(void)
{
	if (mixer_glb->mixer_interrupt.bits.mixer_irq & 0x1) {
		mixer_glb->mixer_interrupt.bits.mixer_irq = 1;
		return 1;
	}
	return 0;
}

__s32 g2d_bsp_open(void)
{
	g2d_top->sclk_gate.bits.mixer_sclk_gate = 1;
	g2d_top->sclk_gate.bits.rot_sclk_gate = 1;
	g2d_top->hclk_gate.bits.mixer_hclk_gate = 1;
	g2d_top->hclk_gate.bits.rot_hclk_gate = 1;
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 1;
	g2d_top->ahb_rst.bits.rot_ahb_rst = 1;
	return 0;
}

__s32 g2d_bsp_close(void)
{
	g2d_top->sclk_gate.bits.mixer_sclk_gate = 0;
	g2d_top->sclk_gate.bits.rot_sclk_gate = 0;
	g2d_top->hclk_gate.bits.mixer_hclk_gate = 0;
	g2d_top->hclk_gate.bits.rot_hclk_gate = 0;
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 0;
	g2d_top->ahb_rst.bits.rot_ahb_rst = 0;
	return 0;
}

__s32 g2d_bsp_reset(void)
{
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 0;
	g2d_top->ahb_rst.bits.rot_ahb_rst = 0;
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 1;
	g2d_top->ahb_rst.bits.rot_ahb_rst = 1;
	return 0;
}

__s32 g2d_top_mixer_reset(void)
{
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 0;
	g2d_top->ahb_rst.bits.mixer_ahb_rst = 1;
	return 0;
}

__s32 g2d_top_rot_reset(void)
{
	g2d_top->ahb_rst.bits.rot_ahb_rst = 0;
	g2d_top->ahb_rst.bits.rot_ahb_rst = 1;
	return 0;
}


__s32 g2d_top_mixer_sclk_div(__u32 div)
{
	g2d_top->sclk_div.bits.mixer_sclk_div = div;
	return 0;
}

__s32 g2d_top_rot_sclk_div(__u32 div)
{
	g2d_top->sclk_div.bits.rot_sclk_div = div;
	return 0;
}

void g2d_top_rcq_irq_en(__u32 en)
{
	g2d_top->rcq_irq_ctl.bits.task_end_irq_en = en;
	/*g2d_top->rcq_irq_ctl.bits.rcq_cfg_finish_irq_en = en;*/
}

void g2d_top_rcq_update_en(__u32 en)
{
	g2d_top->rcq_ctrl.bits.update = en;
}

__s32 g2d_top_rcq_task_irq_query(void)
{
	if (g2d_top->rcq_status.bits.task_end_irq & 0x1) {
		g2d_top->rcq_status.bits.task_end_irq = 1;
		return 1;
	}
	return 0;
}

__s32 g2d_top_rcq_cfg_irq_query(void)
{
	if (g2d_top->rcq_status.bits.cfg_finish_irq & 0x1) {
		g2d_top->rcq_status.bits.cfg_finish_irq = 1;
		return 1;
	}
	return 0;
}

__u32 g2d_top_get_rcq_frame_cnt(void)
{
	return g2d_top->rcq_status.bits.frame_cnt;
}


void g2d_top_set_rcq_head(u64 addr, __u32 len)
{
	__u32 haddr = (__u32)(addr >> 32);

	g2d_top->rcq_header_low_addr = addr;
	g2d_top->rcq_header_high_addr = haddr;
	g2d_top->rcq_header_len.bits.rcq_header_len = len;
}


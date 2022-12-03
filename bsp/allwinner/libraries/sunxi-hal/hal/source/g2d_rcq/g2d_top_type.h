/*
 * g2d_top_type/g2d_top_type.h
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
#ifndef _G2D_TOP_TYPE_H
#define _G2D_TOP_TYPE_H


union g2d_sclk_gate {
	unsigned int dwval;
	struct {
		unsigned int mixer_sclk_gate:1;
		unsigned int rot_sclk_gate:1;
		unsigned int res0:30;
	} bits;
};

union g2d_hclk_gate {
	unsigned int dwval;
	struct {
		unsigned int mixer_hclk_gate:1;
		unsigned int rot_hclk_gate:1;
		unsigned int res0:30;
	} bits;
};

union g2d_ahb_reset {
	unsigned int dwval;
	struct {
		unsigned int mixer_ahb_rst:1;
		unsigned int rot_ahb_rst:1;
		unsigned int res0:30;
	} bits;
};

union g2d_sclk_div {
	unsigned int dwval;
	struct {
		unsigned int mixer_sclk_div:4;
		unsigned int rot_sclk_div:4;
		unsigned int res0:24;
	} bits;
};

union g2d_version {
	unsigned int dwval;
	struct {
		unsigned int gsu_no:2;
		unsigned int vsu_no:2;
		unsigned int rtmx_no:1;
		unsigned int res0:3;
		unsigned int rot_no:1;
		unsigned int res1:7;
		unsigned int ip_version:16;
	} bits;
};

union g2d_rcq_irq_ctl {
	unsigned int dwval;
	struct {
		unsigned int rcq_sel:1;
		unsigned int res0:3;
		unsigned int task_end_irq_en:1;
		unsigned int res1:1;
		unsigned int rcq_cfg_finish_irq_en:1;
		unsigned int res2:25;
	} bits;
};

union g2d_rcq_status {
	unsigned int dwval;
	struct {
		unsigned int task_end_irq:1;
		unsigned int res0:1;
		unsigned int cfg_finish_irq:1;
		unsigned int res1:5;
		unsigned int frame_cnt:8;
		unsigned int res2:16;
	} bits;
};

union g2d_rcq_ctrl {
	unsigned int dwval;
	struct {
		unsigned int update:1;
		unsigned int res0:31;
	} bits;
};

union g2d_rcq_header_len {
	unsigned int dwval;
	struct {
		unsigned int rcq_header_len:16;
		unsigned int res0:16;
	} bits;
};


struct g2d_top_reg {
	/*0x00*/
	union g2d_sclk_gate sclk_gate;
	union g2d_hclk_gate hclk_gate;
	union g2d_ahb_reset ahb_rst;
	union g2d_sclk_div sclk_div;
	/*0x10*/
	union g2d_version version;
	unsigned int res0[3];
	/*0x20*/
	union g2d_rcq_irq_ctl rcq_irq_ctl;
	union g2d_rcq_status rcq_status;
	union g2d_rcq_ctrl rcq_ctrl;
	unsigned int rcq_header_low_addr;
	/*0x30*/
	unsigned int rcq_header_high_addr;
	union g2d_rcq_header_len rcq_header_len;
};

/*mixer global register define start*/
union g2d_mxier_ctrl {
	unsigned int dwval;
	struct {
		unsigned int res0:4;
		unsigned int scan_order:2;
		unsigned int res1:2;
		unsigned int bist_en:1;
		unsigned int res2:22;
		unsigned int start:1;
	} bits;
};

union g2d_mixer_interrupt {
	unsigned int dwval;
	struct {
		unsigned int mixer_irq:1;
		unsigned int res0:3;
		unsigned int finish_irq_en:1;
		unsigned int res1:27;
	} bits;
};

struct g2d_mixer_glb_reg {
	union g2d_mxier_ctrl mixer_ctrl;
	union g2d_mixer_interrupt mixer_interrupt;
};
/*mixer global register define end*/

#endif /*End of file*/

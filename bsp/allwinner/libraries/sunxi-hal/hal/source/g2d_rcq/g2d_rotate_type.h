/*
 * g2d_rotate_type/g2d_rotate_type.h
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
#ifndef _G2D_ROTATE_TYPE_H
#define _G2D_ROTATE_TYPE_H

union g2d_rot_ctrl {
	unsigned int dwval;
	struct {
		unsigned int mode_sel:2;
		unsigned int res0:2;
		unsigned int degreee:2;
		unsigned int vflip_en:1;
		unsigned int hflip_en:1;
		unsigned int res1:22;
		unsigned int bist_en:1;
		unsigned int start:1;
	} bits;
};

union g2d_rot_interrupt {
	unsigned int dwval;
	struct {
		unsigned int rot_irq:1;
		unsigned int res0:15;
		unsigned int finish_irq:1;
		unsigned int res1:15;
	} bits;
};

union g2d_rot_time_ctrl {
	unsigned int dwval;
	struct {
		unsigned int timeout_st:1;
		unsigned int res0:29;
		unsigned int timeout_rst_en:1;
		unsigned int timeout_rst:1;
	} bits;
};

union g2d_rot_in_fmt {
	unsigned int dwval;
	struct {
		unsigned int fmt:6;
		unsigned int res0:26;
	} bits;
};

union g2d_rot_size {
	unsigned int dwval;
	struct {
		unsigned int width:13;
		unsigned int res0:3;
		unsigned int height:13;
		unsigned int res1:3;
	} bits;
};

union g2d_rot_rand_ctrl {
	unsigned int dwval;
	struct {
		unsigned int rand_en:1;
		unsigned int res0:3;
		unsigned int mode:2;
		unsigned int res1:2;
		unsigned int seed:24;
	} bits;
};

union g2d_rot_rand_clk {
	unsigned int dwval;
	struct {
		unsigned int neg_num:16;
		unsigned int pos_num:16;
	};
};


struct g2d_rot_reg {
	/*0x00*/
	union g2d_rot_ctrl rot_ctrl;
	union g2d_rot_interrupt rot_int;
	union g2d_rot_time_ctrl time_ctrl;
	unsigned int res0[5];
	/*0x20*/
	union g2d_rot_in_fmt infmt;
	union g2d_rot_size insize;
	unsigned int res1[2];
	/*0x30*/
	unsigned int pitch0;
	unsigned int pitch1;
	unsigned int pitch2;
	unsigned int res2;
	/*0x40*/
	unsigned int laddr0;
	unsigned int haddr0;
	unsigned int laddr1;
	unsigned int haddr1;
	/*0x50*/
	unsigned int laddr2;
	unsigned int haddr2;
	unsigned int res3[11];
	/*0x84*/
	union g2d_rot_size outsize;
	unsigned int res4[2];
	/*0x90*/
	unsigned int out_pitch0;
	unsigned int out_pitch1;
	unsigned int out_pitch2;
	unsigned int res5;
	/*0xa0*/
	unsigned int out_laddr0;
	unsigned int out_haddr0;
	unsigned int out_laddr1;
	unsigned int out_haddr1;
	/*0xb0*/
	unsigned int out_laddr2;
	unsigned int out_haddr2;
	union g2d_rot_rand_ctrl rand_in_ctrl;
	union g2d_rot_rand_clk rand_in_clk;
	/*0xc0*/
	union g2d_rot_rand_ctrl rand_out_ctrl;
	union g2d_rot_rand_clk rand_out_clk;
};

#endif /*End of file*/

/*
 * g2d_ovl_v.h
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
#ifndef _G2D_OVL_H
#define _G2D_OVL_H
#include "g2d_rcq.h"
#include "g2d_mixer_type.h"
#include "g2d_mixer.h"

struct g2d_mixer_frame;
struct ovl_v_submodule {
	struct g2d_reg_block *reg_blks;
	__u32 reg_blk_num;
	struct g2d_reg_mem_info *reg_info;
	__s32 (*destory)(struct ovl_v_submodule *p_ovl_v);
	__s32 (*apply)(struct ovl_v_submodule *p_ovl_v, g2d_image_enh *p_image);
	int (*rcq_setup)(struct ovl_v_submodule *p_ovl_v, u8 *base,
			   struct g2d_rcq_mem_info *p_rcq_info);
	__u32 (*get_reg_block_num)(struct ovl_v_submodule *p_ovl_v);
	__u32 (*get_rcq_mem_size)(struct ovl_v_submodule *p_ovl_v);
	__s32 (*get_reg_block)(struct ovl_v_submodule *p_ovl_v, struct g2d_reg_block **blks);
	struct g2d_mixer_ovl_v_reg  *(*get_reg)(struct ovl_v_submodule *p_ovl_v);
	void (*set_block_dirty)(struct ovl_v_submodule *p_ovl_v, __u32 blk_id, __u32 dirty);
};
__s32 g2d_ovl_v_fc_set(struct ovl_v_submodule *p_ovl_v, __u32 color_value);
__s32 g2d_vlayer_set(struct ovl_v_submodule *p_ovl_v, __u32 sel,
		     g2d_image_enh *p_image, u8 evasion_flag);

__s32 g2d_vlayer_overlay_set(struct ovl_v_submodule *p_ovl_v, __u32 sel,
					g2d_coor *coor,  __u32 w, __u32 h);
struct ovl_v_submodule *
g2d_ovl_v_submodule_setup(struct g2d_mixer_frame *p_frame);
__s32 g2d_ovl_v_calc_coarse(struct ovl_v_submodule *p_ovl_v, __u32 format, __u32 inw,
		      __u32 inh, __u32 outw, __u32 outh, __u32 *midw,
		      __u32 *midh);

#endif /*End of file*/

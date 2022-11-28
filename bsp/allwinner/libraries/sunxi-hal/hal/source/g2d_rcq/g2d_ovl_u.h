/*
 * g2d_ovl_u/g2d_ovl_u.h
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
#ifndef _G2D_OVL_U_H
#define _G2D_OVL_U_H

#include "g2d_rcq.h"
#include "g2d_mixer_type.h"
#include "g2d_mixer.h"

struct g2d_mixer_frame;
struct ovl_u_submodule {
	struct g2d_reg_block *reg_blks;
	__u32 reg_blk_num;
	struct g2d_reg_mem_info *reg_info;
	__s32 (*destory)(struct ovl_u_submodule *p_ovl_u);
	int (*rcq_setup)(struct ovl_u_submodule *p_ovl_u, u8 *base,
			   struct g2d_rcq_mem_info *p_rcq_info);
	__u32 (*get_reg_block_num)(struct ovl_u_submodule *p_ovl_u);
	__u32 (*get_rcq_mem_size)(struct ovl_u_submodule *p_ovl_u);
	__s32 (*get_reg_block)(struct ovl_u_submodule *p_ovl_u, struct g2d_reg_block **blks);
	struct g2d_mixer_ovl_u_reg  *(*get_reg)(struct ovl_u_submodule *p_ovl_u, __u32 sel);
	void (*set_block_dirty)(struct ovl_u_submodule *p_ovl_u, __u32 blk_id, __u32 dirty);
};

__s32 g2d_ovl_u_fc_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
		       __u32 color_value);
__s32 g2d_uilayer_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
		      g2d_image_enh *img);

__s32 g2d_uilayer_overlay_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
					g2d_coor *coor,  __u32 w, __u32 h);

struct ovl_u_submodule *
g2d_ovl_u_submodule_setup(struct g2d_mixer_frame *p_frame);

#endif /*End of file*/

/*
 * g2d_wb/g2d_wb.h
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
#ifndef _G2D_WB_H
#define _G2D_WB_H
#include "g2d_rcq.h"
#include "g2d_mixer_type.h"
#include "g2d_mixer.h"

struct g2d_mixer_frame;

struct wb_submodule {
	struct g2d_reg_block *reg_blks;
	__u32 reg_blk_num;
	struct g2d_reg_mem_info *reg_info;
	__s32 (*destory)(struct wb_submodule *p_wb);
	__s32 (*apply)(struct wb_submodule *p_wb, g2d_image_enh *p_image);
	int (*rcq_setup)(struct wb_submodule *p_wb, u8 *base,
			struct g2d_rcq_mem_info *p_rcq_info);
	__u32 (*get_reg_block_num)(struct wb_submodule *p_wb);
	__u32 (*get_rcq_mem_size)(struct wb_submodule *p_wb);
	__s32 (*get_reg_block)(struct wb_submodule *p_wb, struct g2d_reg_block **blks);
	struct g2d_mixer_write_back_reg  *(*get_reg)(struct wb_submodule *p_wb);
	void (*set_block_dirty)(struct wb_submodule *p_wb, __u32 blk_id, __u32 dirty);
};
struct wb_submodule *g2d_wb_submodule_setup(struct g2d_mixer_frame *p_frame);
__s32 g2d_wb_set(struct wb_submodule *p_wb, g2d_image_enh *p_image);

#endif

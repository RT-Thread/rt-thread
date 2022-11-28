/*
 * g2d_scal.h
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
#ifndef _G2D_SCAL_H
#define _G2D_SCAL_H
#include "g2d_rcq.h"
#include "g2d_mixer_type.h"
#include "g2d_mixer.h"

struct g2d_mixer_frame;
struct scaler_submodule {
	struct g2d_reg_block *reg_blks;
	__u32 reg_blk_num;
	struct g2d_reg_mem_info *reg_info;
	__s32 (*destory)(struct scaler_submodule *p_scal);
	int (*rcq_setup)(struct scaler_submodule *p_scal, u8  *base,
			  struct g2d_rcq_mem_info *p_rcq_info);
	__u32 (*get_reg_block_num)(struct scaler_submodule *p_scal);
	__s32 (*apply)(struct scaler_submodule *p_scal, g2d_image_enh *p_image);
	__u32 (*get_rcq_mem_size)(struct scaler_submodule *p_scal);
	__s32 (*get_reg_block)(struct scaler_submodule *p_scal, struct g2d_reg_block **blks);
	struct g2d_mixer_video_scaler_reg  *(*get_reg)(struct scaler_submodule *p_scal);
	void (*set_block_dirty)(struct scaler_submodule *p_scal, __u32 blk_id, __u32 dirty);
};

__s32 g2d_vsu_para_set(struct scaler_submodule *p_scal, __u32 fmt, __u32 in_w,
		       __u32 in_h, __u32 out_w, __u32 out_h, __u8 alpha);
struct scaler_submodule *g2d_scaler_submodule_setup(struct g2d_mixer_frame *p_frame);

#endif /*End of file*/

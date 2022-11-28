/*
 * g2d_mixer/g2d_mixer.h
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
#ifndef _G2D_MIXER_H
#define _G2D_MIXER_H

#include "g2d_driver_i.h"
#include "g2d_ovl_v.h"
#include "g2d_ovl_u.h"
#include "g2d_wb.h"
#include "g2d_bld.h"
#include "g2d_scal.h"
#include "g2d_top.h"

struct g2d_mixer_task;

/**
 * mixer frame
 */
struct g2d_mixer_frame {
	struct ovl_v_submodule *ovl_v;
	struct ovl_u_submodule *ovl_u;
	struct blender_submodule *bld;
	struct scaler_submodule *scal;
	struct wb_submodule *wb;
	__u32 frame_id;
	u8 *g2d_base;
	struct dmabuf_item *src_item;
	struct dmabuf_item *dst_item;
	struct dmabuf_item *ptn_item;
	struct dmabuf_item *mask_item;
	__s32 (*destory)(struct g2d_mixer_frame *p_frame);
	__s32 (*apply)(struct g2d_mixer_frame *p_frame,
		     struct mixer_para *p_para);
	__s32 (*frame_mem_setup)(struct g2d_mixer_frame *p_frame,
				 struct mixer_para *p_para,
				 struct g2d_mixer_task *p_task);
	__u32 (*frame_get_reg_block_num)(struct g2d_mixer_frame *p_frame);
	__u32 (*frame_get_rcq_mem_size)(struct g2d_mixer_frame *p_frame);
};

/**
 * mixer task
 */
struct g2d_mixer_task {
	struct g2d_mixer_task *next;
	int task_id;
	__u32 frame_cnt;
	bool en_split_mem;
	struct g2d_mixer_frame *frame;
	struct g2d_rcq_mem_info *p_rcq_info;
	struct mixer_para *p_para;
	__g2d_info_t *p_g2d_info;
	__s32 (*mixer_mem_setup)(struct g2d_mixer_task *p_task,
				 struct mixer_para *p_para);
	__s32 (*apply)(struct g2d_mixer_task *p_task,
		     struct mixer_para *p_para);
	__s32 (*destory)(struct g2d_mixer_task *p_task);
};


/**
 * @name       :mixer_task_process
 * @brief      :mixer task process
 * @param[IN]  :p_g2d_info:pointer of hardware resource
 * @param[IN]  :p_para:mixer task parameter
 * @param[IN]  :frame_len:number of frame
 * @return     :0 if success, -1 else
 */
__s32 mixer_task_process(__g2d_info_t *p_g2d_info, struct mixer_para *p_para,
			 unsigned int frame_len);

/**
 * @name       :create_mixer_task
 * @brief      :create mixer task instance include memory allocate
 * @param[IN]  :p_g2d_info:pointer of hardware resource
 * @param[IN]  :p_para:mixer task parameter
 * @param[IN]  :frame_len:number of frame
 * @return     :task_id >= 1, else fail
 */
int create_mixer_task(__g2d_info_t *p_g2d_info, struct mixer_para *p_para,
			 unsigned int frame_len);

/**
 * @name       :g2d_mixer_get_inst
 * @brief      :get task instance of specified task id
 * @param[IN]  :id: task id
 * @return     :pointer of mixer task or NULL if fail
 */
struct g2d_mixer_task *g2d_mixer_get_inst(int id);
int g2d_mixer_idr_init(void);
int g2d_mixer_idr_remove(void);



#endif /*End of file*/

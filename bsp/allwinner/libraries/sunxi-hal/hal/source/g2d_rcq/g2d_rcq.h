/*
 * g2d_rcq/g2d_rcq.h
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

#include <stdlib.h>
#include <string.h>
#ifndef _G2D_RCQ_H
#define _G2D_RCQ_H

#include "g2d_bsp.h"

/*32 byte align required by rcq*/
#define G2D_RCQ_BYTE_ALIGN(x) (((x + (32 - 1)) >> 5) << 5)
/* 2 align */
#define G2D_RCQ_HEADER_ALIGN(x) (((x + 1) >> 1) << 1)


#define G2D_MIXER_RCQ_USED 1

union rcq_hd_dw0 {
	__u32 dwval;
	struct {
		__u32 len:24;
		__u32 high_addr:8;
	} bits;
};

union rcq_hd_dirty {
	__u32 dwval;
	struct {
		__u32 dirty:1;
		__u32 res0:15;
		__u32 n_header_len : 16; /*next frame header length*/
	} bits;
};

struct g2d_rcq_head {
	__u32 low_addr; /* 32 bytes align */
	union rcq_hd_dw0 dw0;
	union rcq_hd_dirty dirty;
	__u32 reg_offset; /* offset_addr based on g2d_reg_base */
};

/*
* @phy_addr: must be 32 bytes align, can not be accessed by cpu.
* @vir_addr: for cpu access.
* @size: unit: byte. must be 2 bytes align.
* @reg_addr: reg base addr of this block.
* @dirty: this block need be updated to hw reg if @dirty is true.
* @rcq_hd: pointer to rcq head of this dma_reg block at rcq mode.
* @block_id: unique id for current block
*/
struct g2d_reg_block {
	u8 *phy_addr;
	u8 *vir_addr;
	__u32 size;
	u8  *reg_addr;
	__u32 dirty;
	struct g2d_rcq_head *rcq_hd;
	__u32 block_id;
};

struct g2d_reg_mem_info {
	u8 *phy_addr; /* it is non-null at rcq mode */
	u8 *vir_addr;
	__u32 size;
};

struct g2d_rcq_mem_info {
	u8 *phy_addr;
	struct g2d_rcq_head *vir_addr;
	struct g2d_reg_block **reg_blk;
	__u32 alloc_num;
	__u32 cur_num;
	__u32 block_num_per_frame;
	__u32 alloc_num_per_frame;
	__u32 rcq_header_len;
	__u32 rcq_byte_used;
	__u32 rcq_reg_mem_size;
};
__s32 g2d_top_mem_pool_alloc(struct g2d_rcq_mem_info *p_rcq_info);
void *g2d_top_reg_memory_alloc(__u32 size, void *phy_addr,
			       struct g2d_rcq_mem_info *p_rcq_info);
void g2d_top_mem_pool_free(struct g2d_rcq_mem_info *p_rcq_info);

#endif /*End of file*/

/*
 * g2d_wb/g2d_wb.c
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
#include "g2d_wb.h"

static int wb_rcq_setup(struct wb_submodule *p_wb, u8 *base,
			struct g2d_rcq_mem_info *p_rcq_info)
{
	u8 *reg_base = base + G2D_WB;
	int ret = -1;

	if (!p_wb) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	p_wb->reg_info->size = sizeof(struct g2d_mixer_write_back_reg);
	p_wb->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_wb->reg_info->size, (void *)&(p_wb->reg_info->phy_addr),
	    p_rcq_info);

	if (!p_wb->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc writeback reg rcq memory fail!\n");
		goto OUT;
	}

	p_wb->reg_blks->vir_addr = p_wb->reg_info->vir_addr;
	p_wb->reg_blks->phy_addr = p_wb->reg_info->phy_addr;
	p_wb->reg_blks->size = p_wb->reg_info->size;
	p_wb->reg_blks->reg_addr = reg_base;
	ret = 0;

OUT:
	return ret;
}

static __u32 wb_get_reg_block_num(struct wb_submodule *p_wb)
{
	if (p_wb)
		return p_wb->reg_blk_num;
	return 0;
}

static __s32 wb_get_reg_block(struct wb_submodule *p_wb,
			    struct g2d_reg_block **blks)
{
	__s32 i = 0, ret = -1;

	if (p_wb) {
		for (i = 0; i < p_wb->reg_blk_num; ++i)
			blks[i] = p_wb->reg_blks + i;
		ret = 0;
	}

	return ret;
}

static struct g2d_mixer_write_back_reg *wb_get_reg(struct wb_submodule *p_wb)
{
#if G2D_MIXER_RCQ_USED == 1
	return (struct g2d_mixer_write_back_reg *)(p_wb->reg_blks
						   ->vir_addr);
#else
	return (struct g2d_mixer_write_back_reg *)(p_wb->reg_blks
						   ->reg_addr);
#endif
	return NULL;
}


static void wb_set_block_dirty(struct wb_submodule *p_wb, __u32 blk_id, __u32 dirty)
{
#if G2D_MIXER_RCQ_USED == 1
	if (p_wb && p_wb->reg_blks->rcq_hd)
		p_wb->reg_blks->rcq_hd->dirty.bits.dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#else

	if (p_wb)
		p_wb->reg_blks->dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#endif
}

__s32 g2d_wb_set(struct wb_submodule *p_wb, g2d_image_enh *p_image)
{
	struct g2d_mixer_write_back_reg *p_reg = NULL;
	__u64 addr0, addr1, addr2;
	__u32 ycnt, ucnt, vcnt;
	__u32 pitch0, pitch1, pitch2;
	__u32 ch, cw, cy, cx;
	__s32 ret = -1;

	if (p_wb && p_image) {
		p_reg = p_wb->get_reg(p_wb);
		if (!p_reg)
			goto OUT;
		p_reg->wb_attr.bits.fmt = p_image->format;
		p_reg->data_size.bits.height =
		    (!p_image->clip_rect.h) ? 0 : p_image->clip_rect.h - 1;
		p_reg->data_size.bits.width =
		    (!p_image->clip_rect.w) ? 0 : p_image->clip_rect.w - 1;

		if ((p_image->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0) &&
		    (p_image->format <= G2D_FORMAT_YUV422_PLANAR)) {
			cw = p_image->width >> 1;
			ch = p_image->height;
			cx = p_image->clip_rect.x >> 1;
			cy = p_image->clip_rect.y;
		} else if ((p_image->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0) &&
			   (p_image->format <= G2D_FORMAT_YUV420_PLANAR)) {
			cw = p_image->width >> 1;
			ch = p_image->height >> 1;
			cx = p_image->clip_rect.x >> 1;
			cy = p_image->clip_rect.y >> 1;
		} else if ((p_image->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0) &&
			   (p_image->format <= G2D_FORMAT_YUV411_PLANAR)) {
			cw = p_image->width >> 2;
			ch = p_image->height;
			cx = p_image->clip_rect.x >> 2;
			cy = p_image->clip_rect.y;
		} else {
			cw = 0;
			ch = 0;
			cx = 0;
			cy = 0;
		}

		g2d_byte_cal(p_image->format, &ycnt, &ucnt, &vcnt);
		pitch0 = cal_align(ycnt * p_image->width, p_image->align[0]);
		p_reg->pitch0 = pitch0;
		pitch1 = cal_align(ucnt * cw, p_image->align[1]);
		p_reg->pitch1 = pitch1;
		pitch2 = cal_align(vcnt * cw, p_image->align[2]);
		p_reg->pitch2 = pitch2;

		addr0 = p_image->laddr[0] + ((__u64)p_image->haddr[0] << 32) +
			pitch0 * p_image->clip_rect.y +
			ycnt * p_image->clip_rect.x;
		p_reg->laddr0 = addr0 & 0xffffffff;
		p_reg->haddr0 = (addr0 >> 32) & 0xff;
		addr1 = p_image->laddr[1] + ((__u64)p_image->haddr[1] << 32) +
			pitch1 * cy + ucnt * cx;
		p_reg->laddr1 = addr1 & 0xffffffff;
		p_reg->haddr1 = (addr1 >> 32) & 0xff;
		addr2 = p_image->laddr[2] + ((__u64)p_image->haddr[2] << 32) +
			pitch2 * cy + vcnt * cx;
		p_reg->laddr2 = addr2 & 0xffffffff;
		p_reg->haddr2 = (addr1 >> 32) & 0xff;
		p_wb->set_block_dirty(p_wb, 0, 1);
	}

OUT:
	return ret;
}

static __u32 wb_get_rcq_mem_size(struct wb_submodule *p_wb)
{
	return G2D_RCQ_BYTE_ALIGN(sizeof(struct g2d_mixer_write_back_reg));
}

static __s32 wb_destory(struct wb_submodule *p_wb)
{
	__s32 ret = -1;

	if (p_wb) {
		free(p_wb->reg_blks);
		p_wb->reg_blks = NULL;

		free(p_wb->reg_info);
		p_wb->reg_info = NULL;
		ret = 0;
		free(p_wb);
	}

	return ret;
}

struct wb_submodule *g2d_wb_submodule_setup(struct g2d_mixer_frame *p_frame)
{
	struct wb_submodule *p_wb = NULL;

	p_wb = hal_malloc(sizeof(struct wb_submodule));

	if (!p_wb) {
		G2D_ERR_MSG("malloc wb submodule fail!\n");
		return NULL;
	}
	memset(p_wb, 0, sizeof(struct wb_submodule));
	p_wb->rcq_setup = wb_rcq_setup;
	p_wb->reg_blk_num = 1;
	p_wb->get_reg_block_num = wb_get_reg_block_num;
	p_wb->get_reg_block = wb_get_reg_block;
	p_wb->get_reg = wb_get_reg;
	p_wb->set_block_dirty = wb_set_block_dirty;
	p_wb->get_rcq_mem_size = wb_get_rcq_mem_size;
	p_wb->destory = wb_destory;

	p_wb->reg_blks =
	    hal_malloc(sizeof(struct g2d_reg_block) * p_wb->reg_blk_num);
	p_wb->reg_info =
	    hal_malloc(sizeof(struct g2d_reg_mem_info));

	if (!p_wb->reg_blks || !p_wb->reg_info) {
		G2D_ERR_MSG("Kmalloc wb reg info fail!\n");
		goto FREE_WB;
	}
	memset(p_wb->reg_blks, 0, sizeof(struct g2d_reg_block) * p_wb->reg_blk_num);
	memset(p_wb->reg_info, 0, sizeof(struct g2d_reg_mem_info));

	return p_wb;
FREE_WB:
	free(p_wb->reg_blks);
	free(p_wb->reg_info);
	free(p_wb);

	return NULL;
}

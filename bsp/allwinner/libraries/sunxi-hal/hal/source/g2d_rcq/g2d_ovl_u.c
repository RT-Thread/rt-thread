/*
 * g2d_ovl_u.c
 *
 * Copyright (c) 2007-2019 Allwinnertech Co., Ltd.
 * Author: zhengxiaobin <zhengxiaobin@allwinnertech.com>
 *
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

#include "g2d_ovl_u.h"

__s32 g2d_ovl_u_fc_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
		       __u32 color_value)
{
	__s32 ret = -1;
	struct g2d_mixer_ovl_u_reg *p_reg = p_ovl_u->get_reg(p_ovl_u, sel);

	if (!p_reg)
		goto OUT;

	p_reg->ovl_attr.bits.lay_fillcolor_en = 1;
	p_reg->ovl_fill_color = color_value;

	p_ovl_u->set_block_dirty(p_ovl_u, sel, 1);

	ret = 0;
OUT:
	return ret;
}

__s32 g2d_uilayer_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
		      g2d_image_enh *p_img)
{
	__u64 addr0;
	__u32 ycnt, ucnt, vcnt;
	__u32 pitch0;
	__s32 ret = -1;
	struct g2d_mixer_ovl_u_reg *p_reg = p_ovl_u->get_reg(p_ovl_u, sel);

	if (!p_reg)
		goto OUT;

	p_reg->ovl_attr.bits.lay_glbalpha = p_img->alpha & 0xff;
	if (p_img->bpremul)
		p_reg->ovl_attr.bits.lay_premul_ctl = 1;
	p_reg->ovl_attr.bits.lay_fbfmt = p_img->format;
	p_reg->ovl_attr.bits.alpha_mode = p_img->mode;
	p_reg->ovl_attr.bits.lay_en = 1;

	p_reg->ovl_mem.bits.lay_width =
	    (p_img->clip_rect.w == 0 ? 0 : p_img->clip_rect.w - 1) & 0x1fff;
	p_reg->ovl_mem.bits.lay_height =
	    (p_img->clip_rect.h == 0 ? 0 : p_img->clip_rect.h - 1) & 0x1fff;
	p_reg->ovl_winsize.bits.width =
	    (p_img->clip_rect.w == 0 ? 0 : p_img->clip_rect.w - 1) & 0x1fff;
	p_reg->ovl_winsize.bits.height =
	    (p_img->clip_rect.h == 0 ? 0 : p_img->clip_rect.h - 1) & 0x1fff;

	p_reg->ovl_mem_coor.dwval = 0;
	g2d_byte_cal(p_img->format, &ycnt, &ucnt, &vcnt);
	pitch0 = cal_align(ycnt * p_img->width, p_img->align[0]);
	p_reg->ovl_mem_pitch0 = pitch0;

	addr0 =
	    p_img->laddr[0] + ((__u64) p_img->haddr[0] << 32) +
	    pitch0 * p_img->clip_rect.y + ycnt * p_img->clip_rect.x;
	p_reg->ovl_mem_low_addr0 = addr0 & 0xffffffff;
	p_reg->ovl_mem_high_addr = (addr0 >> 32) & 0xff;

	if (p_img->bbuff == 0)
		g2d_ovl_u_fc_set(p_ovl_u, sel, p_img->color);

	p_ovl_u->set_block_dirty(p_ovl_u, sel, 1);
	ret = 0;
OUT:
	return ret;
}

__s32 g2d_uilayer_overlay_set(struct ovl_u_submodule *p_ovl_u, __u32 sel,
					g2d_coor *coor,  __u32 w, __u32 h)
{
	__s32 ret = -1;
	struct g2d_mixer_ovl_u_reg *p_reg = p_ovl_u->get_reg(p_ovl_u, sel);

	if (!p_reg)
		goto OUT;

	p_reg->ovl_winsize.bits.width = (w - 1) & 0x1fff;
	p_reg->ovl_winsize.bits.height = (h - 1) & 0x1fff;

	p_reg->ovl_mem_coor.bits.lay_xcoor = coor->x;
	p_reg->ovl_mem_coor.bits.lay_ycoor = coor->y;
	ret = 0;
OUT:
	return ret;
}

static int ovl_u_rcq_setup(struct ovl_u_submodule *p_ovl_u, u8 *base,
			   struct g2d_rcq_mem_info *p_rcq_info)
{
	u8 *reg_base = base + G2D_UI0;
	__s32 ret = -1;

	if (!p_ovl_u) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	p_ovl_u->reg_info->size = sizeof(struct g2d_mixer_ovl_v_reg);
	p_ovl_u->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_ovl_u->reg_info->size,
	    (void *)&(p_ovl_u->reg_info->phy_addr), p_rcq_info);

	if (!p_ovl_u->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc writeback reg rcq memory fail!\n");
		goto OUT;
	}
	p_ovl_u->reg_blks[0].vir_addr = p_ovl_u->reg_info->vir_addr;
	p_ovl_u->reg_blks[0].phy_addr = p_ovl_u->reg_info->phy_addr;
	p_ovl_u->reg_blks[0].size = p_ovl_u->reg_info->size;
	p_ovl_u->reg_blks[0].reg_addr = reg_base;

	p_ovl_u->reg_info->size = sizeof(struct g2d_mixer_ovl_v_reg);
	p_ovl_u->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_ovl_u->reg_info->size,
	    (void *)&(p_ovl_u->reg_info->phy_addr), p_rcq_info);

	if (!p_ovl_u->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc writeback reg rcq memory fail!\n");
		goto OUT;
	}
	p_ovl_u->reg_blks[1].vir_addr = p_ovl_u->reg_info->vir_addr;
	p_ovl_u->reg_blks[1].phy_addr = p_ovl_u->reg_info->phy_addr;
	p_ovl_u->reg_blks[1].size = p_ovl_u->reg_info->size;
	p_ovl_u->reg_blks[1].reg_addr = base + G2D_UI1;

	p_ovl_u->reg_info->size = sizeof(struct g2d_mixer_ovl_v_reg);
	p_ovl_u->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_ovl_u->reg_info->size,
	    (void *)&(p_ovl_u->reg_info->phy_addr), p_rcq_info);

	if (!p_ovl_u->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc writeback reg rcq memory fail!\n");
		goto OUT;
	}
	p_ovl_u->reg_blks[2].vir_addr = p_ovl_u->reg_info->vir_addr;
	p_ovl_u->reg_blks[2].phy_addr = p_ovl_u->reg_info->phy_addr;
	p_ovl_u->reg_blks[2].size = p_ovl_u->reg_info->size;
	p_ovl_u->reg_blks[2].reg_addr = base + G2D_UI2;
	ret = 0;

OUT:
	return ret;
}

static __u32 ovl_v_get_reg_block_num(struct ovl_u_submodule *p_ovl_u)
{
	if (p_ovl_u)
		return p_ovl_u->reg_blk_num;
	return 0;
}

static __s32 ovl_v_get_reg_block(struct ovl_u_submodule *p_ovl_u,
			    struct g2d_reg_block **blks)
{
	__s32 i = 0, ret = -1;

	if (p_ovl_u) {
		for (i = 0; i < p_ovl_u->reg_blk_num; ++i)
			blks[i] = p_ovl_u->reg_blks + i;
		ret = 0;
	}

	return ret;
}

static struct g2d_mixer_ovl_u_reg *ovl_v_get_reg(struct ovl_u_submodule *p_ovl_u, __u32 sel)
{
	if (sel > p_ovl_u->reg_blk_num - 1)
		goto OUT;

#if G2D_MIXER_RCQ_USED == 1
	return (struct g2d_mixer_ovl_u_reg *)(p_ovl_u->reg_blks[sel]
						   .vir_addr);
#else
	return (struct g2d_mixer_ovl_u_reg *)(p_ovl_u->reg_blks[sel]
						   .reg_addr);
#endif
OUT:
	return NULL;
}


static void ovl_v_set_block_dirty(struct ovl_u_submodule *p_ovl_u, __u32 blk_id, __u32 dirty)
{

	if (blk_id > p_ovl_u->reg_blk_num - 1)
		return;

#if G2D_MIXER_RCQ_USED == 1
	if (p_ovl_u && p_ovl_u->reg_blks->rcq_hd)
		p_ovl_u->reg_blks[blk_id].rcq_hd->dirty.bits.dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#else

	if (p_ovl_u)
		p_ovl_u->reg_blks[blk_id].dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#endif
}

static __u32 ovl_v_get_rcq_mem_size(struct ovl_u_submodule *p_ovl_u)
{
	return G2D_RCQ_BYTE_ALIGN(sizeof(struct g2d_mixer_ovl_v_reg)) *
	       p_ovl_u->reg_blk_num;
}

static __s32 ovl_u_destory(struct ovl_u_submodule *p_ovl_u)
{
	__s32 ret = -1;

	if (p_ovl_u) {
		free(p_ovl_u->reg_blks);
		p_ovl_u->reg_blks = NULL;

		free(p_ovl_u->reg_info);
		p_ovl_u->reg_info = NULL;
		ret = 0;
		free(p_ovl_u);
	}

	return ret;
}

struct ovl_u_submodule *
g2d_ovl_u_submodule_setup(struct g2d_mixer_frame *p_frame)
{
	struct ovl_u_submodule *p_ovl_u = NULL;

	p_ovl_u = hal_malloc(sizeof(struct ovl_u_submodule));

	if (!p_ovl_u) {
		G2D_ERR_MSG("malloc wb submodule fail!\n");
		return NULL;
	}
	memset(p_ovl_u, 0, sizeof(struct ovl_u_submodule));
	p_ovl_u->rcq_setup = ovl_u_rcq_setup;
	p_ovl_u->reg_blk_num = UI_LAYER_NUMBER;
	p_ovl_u->get_reg_block_num = ovl_v_get_reg_block_num;
	p_ovl_u->get_reg_block = ovl_v_get_reg_block;
	p_ovl_u->get_reg = ovl_v_get_reg;
	p_ovl_u->set_block_dirty = ovl_v_set_block_dirty;
	p_ovl_u->get_rcq_mem_size = ovl_v_get_rcq_mem_size;
	p_ovl_u->destory = ovl_u_destory;

	p_ovl_u->reg_blks =
	    hal_malloc(sizeof(struct g2d_reg_block) * p_ovl_u->reg_blk_num);
	p_ovl_u->reg_info =
	    hal_malloc(sizeof(struct g2d_reg_mem_info));

	if (!p_ovl_u->reg_blks || !p_ovl_u->reg_info) {
		G2D_ERR_MSG("malloc wb reg info fail!\n");
		goto FREE_WB;
	}
	memset(p_ovl_u->reg_blks, 0, sizeof(struct g2d_reg_block) * p_ovl_u->reg_blk_num);
	memset(p_ovl_u->reg_info, 0, sizeof(struct g2d_reg_mem_info));

	return p_ovl_u;
FREE_WB:
	free(p_ovl_u->reg_blks);
	free(p_ovl_u->reg_info);
	free(p_ovl_u);

	return NULL;
}

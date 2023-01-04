/*
 * g2d_ovl_v.c
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
#include "g2d_ovl_v.h"

__s32 g2d_ovl_v_calc_coarse(struct ovl_v_submodule *p_ovl_v, __u32 format, __u32 inw,
		      __u32 inh, __u32 outw, __u32 outh, __u32 *midw,
		      __u32 *midh)
{
	__u32 tmp;
	__s32 ret = -1;
	struct g2d_mixer_ovl_v_reg *p_reg = p_ovl_v->get_reg(p_ovl_v);

	if (!p_reg)
		goto OUT;

	switch (format) {
	case G2D_FORMAT_IYUV422_V0Y1U0Y0:
	case G2D_FORMAT_IYUV422_Y1V0Y0U0:
	case G2D_FORMAT_IYUV422_U0Y1V0Y0:
	case G2D_FORMAT_IYUV422_Y1U0Y0V0: {
		/* interleaved YUV422 format */
		*midw = inw;
		*midh = inh;
		break;
	}
	case G2D_FORMAT_YUV422UVC_V1U1V0U0:
	case G2D_FORMAT_YUV422UVC_U1V1U0V0:
	case G2D_FORMAT_YUV422_PLANAR: {
		if (inw >= (outw << 3)) {
			*midw = outw << 3;
			tmp = (*midw << 16) | inw;
			p_reg->hor_down_sample0.dwval = tmp;
			tmp = (*midw << 15) | ((inw + 1) >> 1);
			p_reg->hor_down_sample1.dwval = tmp;
		} else
			*midw = inw;
		if (inh >= (outh << 2)) {
			*midh = (outh << 2);
			tmp = (*midh << 16) | inh;
			p_reg->ver_down_sample0.dwval = tmp;
			p_reg->ver_down_sample1.dwval = tmp;
		} else
			*midh = inh;
		break;
	}
	case G2D_FORMAT_Y8:
	case G2D_FORMAT_YUV420_PLANAR:
	case G2D_FORMAT_YUV420UVC_V1U1V0U0:
	case G2D_FORMAT_YUV420UVC_U1V1U0V0: {
		if (inw >= (outw << 3)) {
			*midw = outw << 3;
			tmp = (*midw << 16) | inw;
			p_reg->hor_down_sample0.dwval = tmp;
			tmp = (*midw << 15) | ((inw + 1) >> 1);
			p_reg->hor_down_sample1.dwval = tmp;
		} else
			*midw = inw;
		if (inh >= (outh << 2)) {
			*midh = (outh << 2);
			tmp = (*midh << 16) | inh;
			p_reg->ver_down_sample0.dwval = tmp;
			tmp = (*midh << 15) | ((inh + 1) >> 1);
			p_reg->ver_down_sample1.dwval = tmp;
		} else
			*midh = inh;
		break;
	}
	case G2D_FORMAT_YUV411_PLANAR:
	case G2D_FORMAT_YUV411UVC_V1U1V0U0:
	case G2D_FORMAT_YUV411UVC_U1V1U0V0: {
		if (inw >= (outw << 3)) {
			*midw = outw << 3;
			tmp = ((*midw) << 16) | inw;
			p_reg->hor_down_sample0.dwval = tmp;
			tmp = ((*midw) << 14) | ((inw + 3) >> 2);
			p_reg->hor_down_sample1.dwval = tmp;
		} else
			*midw = inw;
		if (inh >= (outh << 2)) {
			*midh = (outh << 2);
			tmp = ((*midh) << 16) | inh;
			p_reg->ver_down_sample0.dwval = tmp;
			p_reg->ver_down_sample1.dwval = tmp;
		} else
			*midh = inh;
		break;
	}
	default:
		if (inw >= (outw << 3)) {
			*midw = outw << 3;
			tmp = ((*midw) << 16) | inw;
			p_reg->hor_down_sample0.dwval = tmp;
			p_reg->hor_down_sample1.dwval = tmp;
		} else
			*midw = inw;
		if (inh >= (outh << 2)) {
			*midh = (outh << 2);
			tmp = ((*midh) << 16) | inh;
			p_reg->ver_down_sample0.dwval = tmp;
			p_reg->ver_down_sample1.dwval = tmp;
		} else
			*midh = inh;
		break;
	}
	p_ovl_v->set_block_dirty(p_ovl_v, 0, 1);
	ret = 0;
OUT:
	return ret;
}

/**
 * fillcolor set
 * @color_value:fill color value
 */
__s32 g2d_ovl_v_fc_set(struct ovl_v_submodule *p_ovl_v, __u32 color_value)
{
	__s32 ret = -1;
	struct g2d_mixer_ovl_v_reg *p_reg = p_ovl_v->get_reg(p_ovl_v);
	if (!p_reg)
		goto OUT;

	p_reg->ovl_attr.bits.lay_fillcolor_en = 1;
	p_reg->ovl_fill_color = color_value;
	p_ovl_v->set_block_dirty(p_ovl_v, 0, 1);
	ret = 0;

OUT:
	return ret;
}

/**
 * @sel:layer no.
 * @para avoid_flag is a sign of whether or not to avoid the black point bug cause by g2d
 */
__s32 g2d_vlayer_set(struct ovl_v_submodule *p_ovl_v, __u32 sel, g2d_image_enh *p_image, u8 avoid_flag)
{
	unsigned long long addr0, addr1, addr2;
	__u32 tmp;
	__u32 ycnt, ucnt, vcnt;
	__u32 pitch0, pitch1, pitch2;
	__u32 ch, cw, cy, cx;
	__s32 ret = -1;
	struct g2d_mixer_ovl_v_reg *p_reg = p_ovl_v->get_reg(p_ovl_v);

	if (!p_reg)
		goto OUT;

	p_reg->ovl_attr.bits.lay_fbfmt = p_image->format;
	p_reg->ovl_attr.bits.alpha_mode = p_image->mode;

	/**
	 * except for the scaler function, bpremul is equal to 0,
	 * the code under if is only used by the scaler function
	 */
	if (p_image->bpremul)
		p_reg->ovl_attr.bits.lay_premul_ctl = 1;
	if (avoid_flag)
		p_reg->ovl_attr.bits.lay_premul_ctl = 0;
	p_reg->ovl_attr.bits.lay_glbalpha = p_image->alpha & 0xff;
	p_reg->ovl_attr.bits.lay_en = 1;

	p_reg->ovl_mem.bits.lay_width =
	    (p_image->clip_rect.w == 0 ? 0 : p_image->clip_rect.w - 1) & 0x1fff;
	p_reg->ovl_mem.bits.lay_height =
	    (p_image->clip_rect.h == 0 ? 0 : p_image->clip_rect.h - 1) & 0x1fff;

	p_reg->ovl_winsize.bits.width =
	    (p_image->clip_rect.w == 0 ? 0 : p_image->clip_rect.w - 1) & 0x1fff;
	p_reg->ovl_winsize.bits.height =
	    (p_image->clip_rect.h == 0 ? 0 : p_image->clip_rect.h - 1) & 0x1fff;

	/* offset is set to 0, ovl size is set to layer size */
	p_reg->ovl_mem_coor.dwval = 0;
	if ((p_image->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0)
	      && (p_image->format <= G2D_FORMAT_YUV422_PLANAR)) {
		cw = p_image->width >> 1;
		ch = p_image->height;
		cx = p_image->clip_rect.x >> 1;
		cy = p_image->clip_rect.y;
	}

	else if ((p_image->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0)
		 && (p_image->format <= G2D_FORMAT_YUV420_PLANAR)) {
		cw = p_image->width >> 1;
		ch = p_image->height >> 1;
		cx = p_image->clip_rect.x >> 1;
		cy = p_image->clip_rect.y >> 1;
	}

	else if ((p_image->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0)
		 && (p_image->format <= G2D_FORMAT_YUV411_PLANAR)) {
		cw = p_image->width >> 2;
		ch = p_image->height;
		cx = p_image->clip_rect.x >> 2;
		cy = p_image->clip_rect.y;
	}

	else {
		cw = 0;
		ch = 0;
		cx = 0;
		cy = 0;
	}
	g2d_byte_cal(p_image->format, &ycnt, &ucnt, &vcnt);
	pitch0 = cal_align(ycnt * p_image->width, p_image->align[0]);
	p_reg->ovl_mem_pitch0 = pitch0;
	pitch1 = cal_align(ucnt * cw, p_image->align[1]);
	p_reg->ovl_mem_pitch1 = pitch1;
	pitch2 = cal_align(vcnt * cw, p_image->align[2]);
	p_reg->ovl_mem_pitch2 = pitch2;
	addr0 =
	    p_image->laddr[0] + ((__u64) p_image->haddr[0] << 32) +
	    pitch0 * p_image->clip_rect.y + ycnt * p_image->clip_rect.x;
	p_reg->ovl_mem_low_addr0 = addr0 & 0xffffffff;
	addr1 =
	    p_image->laddr[1] + ((__u64) p_image->haddr[1] << 32) + pitch1 * cy +
	    ucnt * cx;
	p_reg->ovl_mem_low_addr1 = addr1 & 0xffffffff;
	addr2 =
	    p_image->laddr[2] + ((__u64) p_image->haddr[2] << 32) + pitch2 * cy +
	    vcnt * cx;
	p_reg->ovl_mem_low_addr2 = addr2 & 0xffffffff;
	tmp = ((addr0 >> 32) & 0xff) | ((addr1 >> 32) & 0xff) << 8 |
	    ((addr2 >> 32) & 0xff) << 16;
	p_reg->ovl_mem_high_addr.dwval = tmp;
	if (p_image->bbuff == 0)
		g2d_ovl_v_fc_set(p_ovl_v, p_image->color);
	p_ovl_v->set_block_dirty(p_ovl_v, 0, 1);
	ret = 0;
OUT:
	return ret;
}

__s32 g2d_vlayer_overlay_set(struct ovl_v_submodule *p_ovl_v, __u32 sel,
					g2d_coor *coor,  __u32 w, __u32 h)
{
	__s32 ret = -1;
	struct g2d_mixer_ovl_v_reg *p_reg = p_ovl_v->get_reg(p_ovl_v);

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

static int ovl_v_rcq_setup(struct ovl_v_submodule *p_ovl_v, u8 *base,
			   struct g2d_rcq_mem_info *p_rcq_info)
{
	u8 *reg_base = base + G2D_V0;
	int ret = -1;

	if (!p_ovl_v) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	p_ovl_v->reg_info->size = sizeof(struct g2d_mixer_ovl_v_reg);
	p_ovl_v->reg_info->vir_addr = (u8 *)g2d_top_reg_memory_alloc(
	    p_ovl_v->reg_info->size, (void *)&(p_ovl_v->reg_info->phy_addr),
	    p_rcq_info);

	if (!p_ovl_v->reg_info->vir_addr) {
		G2D_ERR_MSG("Malloc writeback reg rcq memory fail!\n");
		goto OUT;
	}

	p_ovl_v->reg_blks->vir_addr = p_ovl_v->reg_info->vir_addr;
	p_ovl_v->reg_blks->phy_addr = p_ovl_v->reg_info->phy_addr;
	p_ovl_v->reg_blks->size = p_ovl_v->reg_info->size;
	p_ovl_v->reg_blks->reg_addr = reg_base;
	ret = 0;

OUT:
	return ret;
}

static __u32 ovl_v_get_reg_block_num(struct ovl_v_submodule *p_ovl_v)
{
	if (p_ovl_v)
		return p_ovl_v->reg_blk_num;
	return 0;
}

static __s32 ovl_v_get_reg_block(struct ovl_v_submodule *p_ovl_v,
			    struct g2d_reg_block **blks)
{
	int i = 0;
	if (p_ovl_v) {
		for (i = 0; i < p_ovl_v->reg_blk_num; ++i)
			blks[i] = p_ovl_v->reg_blks + i;
	}
	return 0;
}

static struct g2d_mixer_ovl_v_reg *ovl_v_get_reg(struct ovl_v_submodule *p_ovl_v)
{
#if G2D_MIXER_RCQ_USED == 1
	return (struct g2d_mixer_ovl_v_reg *)(p_ovl_v->reg_blks
						   ->vir_addr);
#else
	return (struct g2d_mixer_ovl_v_reg *)(p_ovl_v->reg_blks
						   ->reg_addr);
#endif
	return NULL;
}

static void ovl_v_set_block_dirty(struct ovl_v_submodule *p_ovl_v, __u32 blk_id, __u32 dirty)
{
#if G2D_MIXER_RCQ_USED == 1
	if (p_ovl_v && p_ovl_v->reg_blks->rcq_hd)
		p_ovl_v->reg_blks->rcq_hd->dirty.bits.dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#else

	if (p_ovl_v)
		p_ovl_v->reg_blks->dirty = dirty;
	else
		G2D_ERR_MSG("Null pointer!\n");
#endif
}


static __u32 ovl_v_get_rcq_mem_size(struct ovl_v_submodule *p_ovl_v)
{
	return G2D_RCQ_BYTE_ALIGN(sizeof(struct g2d_mixer_ovl_v_reg));
}

static __s32 ovl_v_destory(struct ovl_v_submodule *p_ovl_v)
{
	if (p_ovl_v) {
		free(p_ovl_v->reg_blks);
		p_ovl_v->reg_blks = NULL;

		free(p_ovl_v->reg_info);
		p_ovl_v->reg_info = NULL;
		free(p_ovl_v);
	}

	return 0;
}

struct ovl_v_submodule *
g2d_ovl_v_submodule_setup(struct g2d_mixer_frame *p_frame)
{
	struct ovl_v_submodule *p_ovl_v = NULL;

	p_ovl_v = hal_malloc(sizeof(struct ovl_v_submodule));

	if (!p_ovl_v) {
		G2D_ERR_MSG("malloc wb submodule fail!\n");
		return NULL;
	}
	memset(p_ovl_v, 0, sizeof(struct ovl_v_submodule));
	p_ovl_v->rcq_setup = ovl_v_rcq_setup;
	p_ovl_v->reg_blk_num = VI_LAYER_NUMBER;
	p_ovl_v->get_reg_block_num = ovl_v_get_reg_block_num;
	p_ovl_v->get_reg_block = ovl_v_get_reg_block;
	p_ovl_v->get_reg = ovl_v_get_reg;
	p_ovl_v->set_block_dirty = ovl_v_set_block_dirty;
	p_ovl_v->get_rcq_mem_size = ovl_v_get_rcq_mem_size;
	p_ovl_v->destory = ovl_v_destory;

	p_ovl_v->reg_blks =
	    hal_malloc(sizeof(struct g2d_reg_block) * p_ovl_v->reg_blk_num);
	p_ovl_v->reg_info =
	    hal_malloc(sizeof(struct g2d_reg_mem_info));

	if (!p_ovl_v->reg_blks || !p_ovl_v->reg_info) {
		G2D_ERR_MSG("malloc wb reg info fail!\n");
		goto FREE_WB;
	}
	memset(p_ovl_v->reg_blks, 0, sizeof(struct g2d_reg_block) * p_ovl_v->reg_blk_num);
	memset(p_ovl_v->reg_info, 0, sizeof(struct g2d_reg_mem_info));

	return p_ovl_v;
FREE_WB:
	free(p_ovl_v->reg_blks);
	free(p_ovl_v->reg_info);
	free(p_ovl_v);

	return NULL;
}

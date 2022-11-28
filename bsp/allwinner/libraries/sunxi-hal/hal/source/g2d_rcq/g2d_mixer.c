/*
 * g2d_mixer/g2d_mixer.c
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
#include <hal_cache.h>
#include <stdio.h>
#include "g2d_mixer.h"
#include <stdlib.h>
#include <string.h>
#include "simple_idr.h"

/**
 * when image includes the alpha of pixel equal 0, using AVOID_PREMUL
 */
#define AVOID_PREMUL 1
#define NOT_AVOID_PREMUL 0

static struct g2d_mixer_task *g2d_task_list = NULL;

static struct id_dir* idr;

int g2d_mixer_idr_init(void)
{
	idr = id_creat();
	if (idr == NULL){
		hal_log_err("err alloc idr\n");
		return -1;
	}
	return 0;
}

int g2d_mixer_idr_remove(void)
{
	if(idr != NULL)
		id_destroyed(idr);
	return 0;
}

static void g2d_list_add_tail(struct g2d_mixer_task *node, struct g2d_mixer_task *head)
{
	struct g2d_mixer_task *temp = g2d_task_list;
	if(g2d_task_list == NULL)
		g2d_task_list = node;
	else {
		while(temp != NULL){
			temp = temp->next;
		}
		temp = node;
	}
	node->next = NULL;

}
static void g2d_list_del(struct g2d_mixer_task *node)
{
	struct g2d_mixer_task *temp = g2d_task_list;
	struct g2d_mixer_task *pre_temp = NULL;
	while(temp != node){
			pre_temp = temp;
			temp = temp->next;
		}
	if(pre_temp != NULL)
		pre_temp->next = node->next;
	node->next = NULL;
	if(temp == g2d_task_list)
		g2d_task_list = NULL;
}

static __s32 g2d_bsp_maskblt(struct g2d_mixer_frame *p_frame,
			     g2d_image_enh *src, g2d_image_enh *ptn,
			     g2d_image_enh *mask, g2d_image_enh *dst,
			     __u32 back_flag, __u32 fore_flag)
{
	g2d_rect rect0;
	__s32 ret = -1;

	if (!dst) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	if (dst->format > G2D_FORMAT_BGRA1010102) {
		G2D_ERR_MSG("Un support out format:%d\n", dst->format);
		goto OUT;
	}
	g2d_vlayer_set(p_frame->ovl_v, 0, dst, NOT_AVOID_PREMUL);

	if (src) {
		src->clip_rect.w = dst->clip_rect.w;
		src->clip_rect.h = dst->clip_rect.h;
		g2d_uilayer_set(p_frame->ovl_u, 0, src);
	}
	if (ptn) {
		ptn->clip_rect.w = dst->clip_rect.w;
		ptn->clip_rect.h = dst->clip_rect.h;
		g2d_uilayer_set(p_frame->ovl_u, 1, ptn);
	}

	if (mask != NULL) {
		mask->clip_rect.w = dst->clip_rect.w;
		mask->clip_rect.h = dst->clip_rect.h;
		g2d_uilayer_set(p_frame->ovl_u, 2, mask);

		/* set the ROP4 */
		bld_set_rop_ctrl(p_frame->bld, 0x1);
		bld_rop3_set(p_frame->bld, 0, back_flag & 0xff);
		bld_rop3_set(p_frame->bld, 1, fore_flag & 0xff);
	} else {
		bld_set_rop_ctrl(p_frame->bld, 0x0);
		bld_rop3_set(p_frame->bld, 0, back_flag);
	}

	rect0.x = 0;
	rect0.y = 0;
	rect0.w = dst->clip_rect.w;
	rect0.h = dst->clip_rect.h;
	bld_in_set(p_frame->bld, 0, rect0, dst->bpremul);
	bld_out_setting(p_frame->bld, dst);
	g2d_wb_set(p_frame->wb, dst);
	ret = 0;
OUT:
	return ret;

}

static __s32 g2d_fillrectangle(struct g2d_mixer_frame *p_frame,
				   g2d_image_enh *dst, __u32 color_value)
{
	g2d_rect rect0;
	__s32 ret = -1;

	if (!dst || !p_frame) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	/* set the input layer */
	g2d_vlayer_set(p_frame->ovl_v, 0, dst, NOT_AVOID_PREMUL);
	/* set the fill color value */
	g2d_ovl_v_fc_set(p_frame->ovl_v, color_value);

	if (dst->format >= G2D_FORMAT_IYUV422_V0Y1U0Y0) {
		g2d_vsu_para_set(p_frame->scal, dst->format, dst->clip_rect.w,
				  dst->clip_rect.h, dst->clip_rect.w,
				  dst->clip_rect.h, 0xff);
		bld_csc_reg_set(p_frame->bld, 1, G2D_RGB2YUV_709);
	}

	/* for interleaved test */
	if ((dst->format >= G2D_FORMAT_IYUV422_V0Y1U0Y0)
			&& (dst->format <= G2D_FORMAT_IYUV422_Y1U0Y0V0)) {
		bld_csc_reg_set(p_frame->bld, 0, G2D_RGB2YUV_709);
		bld_csc_reg_set(p_frame->bld, 1, G2D_RGB2YUV_709);
		bld_csc_reg_set(p_frame->bld, 2, G2D_RGB2YUV_709);

		bld_bk_set(p_frame->bld, 0xff123456);
		bld_porter_duff(p_frame->bld, G2D_BLD_SRCOVER);

		g2d_ovl_u_fc_set(p_frame->ovl_u, 0, 0xffffffff);
		g2d_ovl_u_fc_set(p_frame->ovl_u, 1, 0xffffffff);
	}

	rect0.x = 0;
	rect0.y = 0;
	rect0.w = dst->clip_rect.w;
	rect0.h = dst->clip_rect.h;
	bld_in_set(p_frame->bld, 0, rect0, dst->bpremul);
	bld_cs_set(p_frame->bld, dst->format);

	/* ROP sel ch0 pass */
	bld_set_rop_ctrl(p_frame->bld, 0xf0);
	bld_out_setting(p_frame->bld, dst);
	g2d_wb_set(p_frame->wb, dst);

	ret = 0;
OUT:
	return ret;
}

/* fix add */
static bool g2d_bld_check_coor(g2d_image_enh *src,
		g2d_image_enh *src2, g2d_image_enh *dst)
{
	if (dst->width < src->clip_rect.w || dst->width < src2->clip_rect.w
			|| dst->height < src->clip_rect.h ||
			dst->height < src2->clip_rect.h)
		return false;

	return true;
}

static __s32 g2d_bsp_bld(struct g2d_mixer_frame *p_frame, g2d_image_enh *src,
				g2d_image_enh *src2, g2d_image_enh *dst,
				__u32 flag, g2d_ck *ck_para)
{
	g2d_rect rect0, rect1;
	__s32 ret = -1;
	__u32 midw, midh;

	if (!dst || !src || !p_frame || !ck_para) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	if (g2d_bld_check_coor(src, src2, dst) == false){
		pr_err("[BLD] size is not suitable!");
		goto OUT;
	}

	g2d_vlayer_set(p_frame->ovl_v, 0, src, NOT_AVOID_PREMUL);
	g2d_vlayer_overlay_set(p_frame->ovl_v, 0, &src->coor,
			dst->clip_rect.w, dst->clip_rect.h);

	g2d_uilayer_set(p_frame->ovl_u, 2, src2);
	g2d_uilayer_overlay_set(p_frame->ovl_u, 2, &src2->coor,
			dst->clip_rect.w, dst->clip_rect.h);

	if (src->format > G2D_FORMAT_BGRA1010102) {
		if (src2->format > G2D_FORMAT_BGRA1010102) {
			pr_err("[BLD] not support two yuv layer!\n");
			goto OUT;
		} else {
			/* YUV_XXX->YUV444->RGB overlay size */
			g2d_ovl_v_calc_coarse(p_frame->ovl_v, src->format, dst->clip_rect.w,
						dst->clip_rect.h, dst->clip_rect.w,
						dst->clip_rect.h, &midw, &midh);
			g2d_vsu_para_set(p_frame->scal, src->format, midw, midh,
					dst->clip_rect.w, dst->clip_rect.h, dst->alpha);

			if (src->clip_rect.w <= 1280 && src->clip_rect.h <= 720) {
				bld_csc_reg_set(p_frame->bld, 0, G2D_YUV2RGB_601);
			} else
				bld_csc_reg_set(p_frame->bld, 0, G2D_YUV2RGB_709);

		}
	} else {
		if (src2->format > G2D_FORMAT_BGRA1010102) {
			pr_err("[BLD] please use ch0(src0) to set YUV layer!\n");
			goto OUT;
		}
	}

	if (dst->format > G2D_FORMAT_BGRA1010102) {
		if (dst->clip_rect.w <= 1280 && dst->clip_rect.h <= 720) {
			bld_csc_reg_set(p_frame->bld, 2, G2D_RGB2YUV_601);
		} else
			bld_csc_reg_set(p_frame->bld, 2, G2D_RGB2YUV_709);
	}

	bld_set_rop_ctrl(p_frame->bld, 0xf0);

	rect0.x = 0;
	rect0.y = 0;
	rect0.w = dst->clip_rect.w;/* overlay size */
	rect0.h = dst->clip_rect.h;

	rect1.x = 0;
	rect1.y = 0;
	rect1.w = dst->clip_rect.w;
	rect1.h = dst->clip_rect.h;

	bld_in_set(p_frame->bld, 0, rect0, src->bpremul);
	bld_in_set(p_frame->bld, 1, rect1, src2->bpremul);

	if (flag == 0) {
		/* flag not set use default */
		flag = G2D_BLD_SRCOVER;
	}

	bld_porter_duff(p_frame->bld, flag & 0xFFF);

	bld_ck_para_set(p_frame->bld, ck_para, flag);

	bld_cs_set(p_frame->bld, dst->format);
	bld_out_setting(p_frame->bld, dst);
	g2d_wb_set(p_frame->wb, dst);

	ret = 0;
OUT:
	return ret;
}

static __s32 g2d_bsp_bitblt(struct g2d_mixer_frame *p_frame, g2d_image_enh *src,
			   g2d_image_enh *dst, __u32 flag)
{
	g2d_rect rect0, rect1;
	bool bpre;
	__u32 midw, midh;
	__s32 ret = -1;

	if (!p_frame || !src || !dst)
		goto OUT;

	if ((flag & 0x0fffffff) == G2D_BLT_NONE) {
		g2d_vlayer_set(p_frame->ovl_v, 0, src, AVOID_PREMUL);
		/* need abp process */
		if (src->mode)
			g2d_uilayer_set(p_frame->ovl_u, 2,
					dst);
		if ((src->format >= G2D_FORMAT_IYUV422_V0Y1U0Y0) ||
		    (src->clip_rect.w != dst->clip_rect.w) ||
		    (src->clip_rect.h != dst->clip_rect.h)) {
			g2d_ovl_v_calc_coarse(
			    p_frame->ovl_v, src->format, src->clip_rect.w,
			    src->clip_rect.h, dst->clip_rect.w,
			    dst->clip_rect.h, &midw, &midh);
			g2d_vsu_para_set(p_frame->scal, src->format, midw, midh,
					 dst->clip_rect.w, dst->clip_rect.h,
					 0xff);
		}
		bld_porter_duff(p_frame->bld, G2D_BLD_SRCOVER);
		/*Default value*/
		bld_set_rop_ctrl(p_frame->bld, 0xf0);
		rect0.x = 0;
		rect0.y = 0;
		rect0.w = dst->clip_rect.w;
		rect0.h = dst->clip_rect.h;
		bld_in_set(p_frame->bld, 0, rect0, dst->bpremul);
		bld_cs_set(p_frame->bld, src->format);
		if (src->mode) {
			/* need abp process */
			rect1.x = 0;
			rect1.y = 0;
			rect1.w = dst->clip_rect.w;
			rect1.h = dst->clip_rect.h;
			bld_in_set(p_frame->bld, 1, rect1, dst->bpremul);
		}
		if ((src->format <= G2D_FORMAT_BGRA1010102) &&
		      (dst->format > G2D_FORMAT_BGRA1010102)) {
			bld_csc_reg_set(p_frame->bld, 2, G2D_RGB2YUV_709);
		}
		if ((src->format > G2D_FORMAT_BGRA1010102) &&
		      (dst->format <= G2D_FORMAT_BGRA1010102)) {
			bld_csc_reg_set(p_frame->bld, 2, G2D_YUV2RGB_709);
		}
		bld_out_setting(p_frame->bld, dst);
		g2d_wb_set(p_frame->wb, dst);
	} else if (flag & 0xff) {
		if ((src->format > G2D_FORMAT_BGRA1010102) |
		    (dst->format > G2D_FORMAT_BGRA1010102)) {
			G2D_ERR_MSG("Only support rgb format!\n");
			goto OUT;
		}
		g2d_uilayer_set(p_frame->ovl_u, 0, dst);
		g2d_vlayer_set(p_frame->ovl_v, 0, src, AVOID_PREMUL);
		bpre = false;
		if (src->bpremul || dst->bpremul)
			bpre = true;
		if ((src->clip_rect.w != dst->clip_rect.w)
		    || (src->clip_rect.h != dst->clip_rect.h)) {
			g2d_ovl_v_calc_coarse(
			    p_frame->ovl_v, src->format, src->clip_rect.w,
			    src->clip_rect.h, dst->clip_rect.w,
			    dst->clip_rect.h, &midw, &midh);
			g2d_vsu_para_set(p_frame->scal, src->format, midw, midh,
					 dst->clip_rect.w, dst->clip_rect.h,
					 0xff);
		}
		/*Default value*/
		bld_porter_duff(p_frame->bld, G2D_BLD_SRCOVER);
		bld_set_rop_ctrl(p_frame->bld, 0x00);
		bld_rop2_set(p_frame->bld, flag & 0xff);

		/*set bld para */
		rect0.x = 0;
		rect0.y = 0;
		rect0.w = dst->clip_rect.w;
		rect0.h = dst->clip_rect.h;
		bld_in_set(p_frame->bld, 0, rect0, bpre);
		bld_out_setting(p_frame->bld, dst);
		g2d_wb_set(p_frame->wb, dst);
	}

	ret = 0;
OUT:
	return ret;

}

/**
 * @name       :g2d_split_mem
 * @brief      :split memory from a big memory, only support y8
 * @param[IN]  :
 * @param[IN]  :
 * @return     :0 if success, -1 else
 */
static __s32 g2d_split_mem(struct g2d_mixer_task *p_task,
				 struct mixer_para *p_para)
{

	__s32 ret = 0, i = 0;
	__u32 src_addr = 0, dst_addr = 0;

	if (p_para[0].op_flag & OP_SPLIT_MEM) {
		p_task->en_split_mem = 1;
		/*ret = g2d_set_image_addr(&p_task->frame[0].dst_item, &p_para[0].dst_image_h);
		if (ret)
			goto OUT;*/
		dst_addr = p_para[0].dst_image_h.laddr[0];

		/*ret = g2d_set_image_addr(&p_task->frame[0].src_item,
					 &p_para[0].src_image_h);*/
		if (ret)
			goto OUT;
		src_addr = p_para[0].src_image_h.laddr[0];

		for (i = 0; i < p_task->frame_cnt; ++i) {
			p_para[i].src_image_h.laddr[0] = src_addr;
			p_para[i].dst_image_h.laddr[0] = dst_addr;
			src_addr += p_para[i].src_image_h.width * p_para[i].src_image_h.height;
			dst_addr += p_para[i].dst_image_h.width * p_para[i].dst_image_h.height;
		}
	}

OUT:
	return ret;
}

static __s32 g2d_mixer_mem_setup(struct g2d_mixer_task *p_task,
				 struct mixer_para *p_para)
{
	__u32 i = 0, frame_index = 0;
	__u32 rcq_reg_mem_size = 0;
	__s32 ret = -1;
	struct g2d_reg_block **p_reg_blks;
	struct g2d_rcq_head *rcq_hd = NULL;

	if (!p_task->p_rcq_info)
		goto OUT;

	p_task->p_rcq_info->block_num_per_frame =
	    p_task->frame[0].frame_get_reg_block_num(&p_task->frame[0]);

	p_task->p_rcq_info->alloc_num_per_frame =
	    G2D_RCQ_HEADER_ALIGN(p_task->p_rcq_info->block_num_per_frame);
	/*header length after 32 BYTE algin*/

	p_task->p_rcq_info->rcq_header_len =
	    p_task->p_rcq_info->alloc_num_per_frame *
	    sizeof(*(p_task->p_rcq_info->vir_addr));

	/*real block num*/
	p_task->p_rcq_info->cur_num =
	    p_task->p_rcq_info->block_num_per_frame * p_task->frame_cnt;

	/*block num that need to be alloced*/
	p_task->p_rcq_info->alloc_num =
	    p_task->p_rcq_info->alloc_num_per_frame * p_task->frame_cnt;

	/*regblocks + rcq header*/
	rcq_reg_mem_size =
	    p_task->frame[0].frame_get_rcq_mem_size(&p_task->frame[0]) *
	    p_task->frame_cnt;

	rcq_reg_mem_size += sizeof(*(p_task->p_rcq_info->vir_addr)) *
			    p_task->p_rcq_info->alloc_num;

	p_task->p_rcq_info->rcq_reg_mem_size = rcq_reg_mem_size;
	if (g2d_top_mem_pool_alloc(p_task->p_rcq_info)) {
		G2D_ERR_MSG("g2d_top_mem_pool_alloc fail!\n");
		goto OUT;
	}

	/*malloc memory for rcq queue*/

	if (!p_task->p_rcq_info->vir_addr) {
		G2D_ERR_MSG("Malloc rcq queue memory fail!\n");
		goto OUT;
	}

	p_task->p_rcq_info->reg_blk =
	    hal_malloc(sizeof(*(p_task->p_rcq_info->reg_blk)) *
			p_task->p_rcq_info->cur_num);

	if (p_task->p_rcq_info->reg_blk == NULL) {
		G2D_ERR_MSG("kalloc for g2d_reg_block failed\n");
		goto OUT;
	}
	memset(p_task->p_rcq_info->reg_blk, 0, sizeof(*(p_task->p_rcq_info->reg_blk)) *
			p_task->p_rcq_info->cur_num);
	p_reg_blks = p_task->p_rcq_info->reg_blk;

	g2d_split_mem(p_task, p_para);

	for (i = 0; i < p_task->frame_cnt; ++i) {

		if (p_task->frame[i].frame_mem_setup(
			&p_task->frame[i], &p_para[i], p_task)) {
			G2D_ERR_MSG("Frame:%ld setupt fail!\n", i);
			goto OUT;
		}
		/*overlay video*/
		p_task->frame[i].ovl_v->get_reg_block(p_task->frame[i].ovl_v,
						      p_reg_blks);
		p_reg_blks += p_task->frame[i].ovl_v->get_reg_block_num(
		    p_task->frame[i].ovl_v);

		/*overlay ui*/
		p_task->frame[i].ovl_u->get_reg_block(p_task->frame[i].ovl_u,
						      p_reg_blks);

		p_reg_blks += p_task->frame[i].ovl_u->get_reg_block_num(
		    p_task->frame[i].ovl_u);

		/*scaler*/
		p_task->frame[i].scal->get_reg_block(p_task->frame[i].scal,
						     p_reg_blks);
		p_reg_blks += p_task->frame[i].scal->get_reg_block_num(
		    p_task->frame[i].scal);

		/*blender*/
		p_task->frame[i].bld->get_reg_block(p_task->frame[i].bld,
						    p_reg_blks);
		p_reg_blks += p_task->frame[i].bld->get_reg_block_num(
		    p_task->frame[i].bld);

		/*write back*/
		p_task->frame[i].wb->get_reg_block(p_task->frame[i].wb,
						   p_reg_blks);
		p_reg_blks +=
		    p_task->frame[i].wb->get_reg_block_num(p_task->frame[i].wb);
	}

	p_reg_blks = p_task->p_rcq_info->reg_blk;
	rcq_hd = p_task->p_rcq_info->vir_addr;

	for (frame_index = 0; frame_index < p_task->frame_cnt; ++frame_index) {
		for (i = 0; i < p_task->p_rcq_info->alloc_num_per_frame; ++i) {
			struct g2d_reg_block *reg_blk = *p_reg_blks;

			if (p_task->p_rcq_info->alloc_num_per_frame >
				p_task->p_rcq_info->block_num_per_frame &&
			    i == p_task->p_rcq_info->block_num_per_frame) {
				if (frame_index == p_task->frame_cnt - 1)
					rcq_hd->dirty.bits.n_header_len = 0;
				else
					rcq_hd->dirty.bits.n_header_len =
					    p_task->p_rcq_info->rcq_header_len;
				++rcq_hd;
			} else {
				rcq_hd->low_addr =
				    (__u32)((unsigned long)(reg_blk->phy_addr));
#if defined(CONFIG_ARM64)
				rcq_hd->dw0.bits.high_addr =
				    (u8)((__u64)(reg_blk->phy_addr) >> 32);
#else
				rcq_hd->dw0.bits.high_addr =
				    (u8)((__u64)(unsigned long)(reg_blk->phy_addr) >> 32);
#endif
				rcq_hd->dw0.bits.len = reg_blk->size;
				rcq_hd->dirty.bits.dirty = reg_blk->dirty;
				rcq_hd->reg_offset = (__u32)(__u64)(
				    reg_blk->reg_addr -
				    (u8 *)(unsigned long)p_task->p_g2d_info->io);
				reg_blk->rcq_hd = rcq_hd;

				/*last frame's next frame len should be zero*/
				if (frame_index == p_task->frame_cnt - 1)
					rcq_hd->dirty.bits.n_header_len = 0;
				else
					rcq_hd->dirty.bits.n_header_len =
					    p_task->p_rcq_info->rcq_header_len;

				++rcq_hd;
				++p_reg_blks;
			}
		}
	}

	ret = 0;
OUT:
	return ret;
}

static __u32 frame_get_rcq_mem_size(struct g2d_mixer_frame *p_frame)
{
	int rcq_mem_size = 0;

	rcq_mem_size += p_frame->wb->get_rcq_mem_size(p_frame->wb);
	rcq_mem_size += p_frame->ovl_v->get_rcq_mem_size(p_frame->ovl_v);
	rcq_mem_size += p_frame->ovl_u->get_rcq_mem_size(p_frame->ovl_u);
	rcq_mem_size += p_frame->scal->get_rcq_mem_size(p_frame->scal);
	rcq_mem_size += p_frame->bld->get_rcq_mem_size(p_frame->bld);

	return rcq_mem_size;
}


static __s32 frame_mem_setup(struct g2d_mixer_frame *p_frame,
				 struct mixer_para *p_para,
				 struct g2d_mixer_task *p_task)
{
	__s32 ret = -1;

	ret = p_frame->wb->rcq_setup(p_frame->wb, p_frame->g2d_base,
				     p_task->p_rcq_info);
	if (ret)
		goto OUT;
	ret = p_frame->ovl_v->rcq_setup(p_frame->ovl_v, p_frame->g2d_base,
					p_task->p_rcq_info);
	if (ret)
		goto OUT;
	ret = p_frame->ovl_u->rcq_setup(p_frame->ovl_u, p_frame->g2d_base,
					p_task->p_rcq_info);
	if (ret)
		goto OUT;
	ret = p_frame->bld->rcq_setup(p_frame->bld, p_frame->g2d_base,
				      p_task->p_rcq_info);
	if (ret)
		goto OUT;
	ret = p_frame->scal->rcq_setup(p_frame->scal, p_frame->g2d_base,
				      p_task->p_rcq_info);
	if (ret)
		goto OUT;

	if (p_task->en_split_mem)
		goto OUT;

OUT:
	return ret;
}

/**
 * @rong This function is to use black spot avoidance scheme
 * @para g2d_image_enh *p_dst_image, g2d_image_enh *p_src_image
 */
static void modify_premul(g2d_image_enh *p_dst_image, g2d_image_enh *p_src_image)
{
	p_dst_image->bpremul = 1;
	p_src_image->bpremul = 1;
}

__s32 g2d_mixer_frame_apply(struct g2d_mixer_frame *p_frame,
			    struct mixer_para *p_para)
{
	__s32 ret = -1;

	if (g2d_image_check(&p_para->dst_image_h))
		goto OUT;
	if ((p_para->op_flag & OP_BITBLT) || (p_para->op_flag & OP_BLEND)) {
		if (g2d_image_check(&p_para->src_image_h))
			goto OUT;
		if (p_para->op_flag & OP_BLEND) {
			/* actually is use as src2 */
			if (g2d_image_check(&p_para->ptn_image_h))
				goto OUT;
		}
	} else if ((p_para->op_flag & OP_MASK)) {
		p_para->dst_image_h.bbuff = 1;
		p_para->dst_image_h.gamut = G2D_BT709;
		p_para->src_image_h.bbuff = 1;
		p_para->src_image_h.gamut = G2D_BT709;
		p_para->ptn_image_h.bbuff = 1;
		p_para->ptn_image_h.gamut = G2D_BT709;
		p_para->mask_image_h.bbuff = 1;
		p_para->mask_image_h.gamut = G2D_BT709;
	}


	ret = 0;
	if (p_para->op_flag & OP_BITBLT) {
		modify_premul(&p_para->dst_image_h, &p_para->src_image_h);
		ret = g2d_bsp_bitblt(p_frame, &p_para->src_image_h,
				     &p_para->dst_image_h, p_para->flag_h);
	} else if (p_para->op_flag & OP_BLEND) {
		ret = g2d_bsp_bld(p_frame, &p_para->src_image_h, &p_para->ptn_image_h,
				  &p_para->dst_image_h, p_para->bld_cmd,
				  &p_para->ck_para);
	} else if (p_para->op_flag & OP_FILLRECT) {
		ret = g2d_fillrectangle(p_frame, &p_para->dst_image_h,
					p_para->dst_image_h.color);
	} else if (p_para->op_flag & OP_MASK) {
		ret = g2d_bsp_maskblt(
		    p_frame, &p_para->src_image_h, &p_para->ptn_image_h,
		    &p_para->mask_image_h, &p_para->dst_image_h,
		    p_para->back_flag, p_para->fore_flag);
	}

OUT:
	return ret;
}

static __s32 g2d_mixer_frame_destory(struct g2d_mixer_frame *p_frame)
{
	__s32 ret = 0;
	ret += p_frame->wb->destory(p_frame->wb);
	ret += p_frame->ovl_v->destory(p_frame->ovl_v);
	ret += p_frame->ovl_u->destory(p_frame->ovl_u);
	ret += p_frame->bld->destory(p_frame->bld);
	ret += p_frame->scal->destory(p_frame->scal);

	return ret;
}

static __u32 frame_get_reg_block_num(struct g2d_mixer_frame *p_frame)
{
	__u32 block_num = 0;

	block_num += p_frame->ovl_u->get_reg_block_num(p_frame->ovl_u);
	block_num += p_frame->ovl_v->get_reg_block_num(p_frame->ovl_v);
	block_num += p_frame->scal->get_reg_block_num(p_frame->scal);
	block_num += p_frame->bld->get_reg_block_num(p_frame->bld);
	block_num += p_frame->wb->get_reg_block_num(p_frame->wb);
	return block_num;
}

static int g2d_mixer_frame_setup(struct g2d_mixer_frame *p_frame, unsigned int index)
{
	int ret = -1;

	if (!p_frame) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	p_frame->apply = g2d_mixer_frame_apply;
	p_frame->frame_id = index;
	p_frame->destory = g2d_mixer_frame_destory;
	p_frame->frame_get_reg_block_num = frame_get_reg_block_num;
	p_frame->frame_mem_setup = frame_mem_setup;
	p_frame->frame_get_rcq_mem_size = frame_get_rcq_mem_size;

	p_frame->wb = g2d_wb_submodule_setup(p_frame);
	if (!p_frame->wb) {
		G2D_ERR_MSG("Write back submodule setup fail!\n");
		goto FREE;
	}

	p_frame->ovl_v = g2d_ovl_v_submodule_setup(p_frame);
	if (!p_frame->ovl_v) {
		G2D_ERR_MSG("ovl v submodule setup fail!\n");
		goto FREE;
	}

	p_frame->ovl_u = g2d_ovl_u_submodule_setup(p_frame);
	if (!p_frame->ovl_u) {
		G2D_ERR_MSG("ovl u submodule setup fail!\n");
		goto FREE;
	}

	p_frame->bld = g2d_bld_submodule_setup(p_frame);
	if (!p_frame->bld) {
		G2D_ERR_MSG("bld submodule setup fail!\n");
		goto FREE;
	}

	p_frame->scal = g2d_scaler_submodule_setup(p_frame);
	if (!p_frame->scal) {
		G2D_ERR_MSG("scaler submodule setup fail!\n");
		goto FREE;
	}

	ret = 0;
	goto OUT;

FREE:
	free(p_frame->wb);
	free(p_frame->ovl_v);
	free(p_frame->ovl_u);
	free(p_frame->bld);
	free(p_frame->scal);
OUT:
	return ret;
}

static __s32 g2d_mixer_apply(struct g2d_mixer_task *p_task,
			   struct mixer_para *p_para)
{
	__u32 i = 0, ret = -1;

#if G2D_MIXER_RCQ_USED == 1
	g2d_top_rcq_update_en(0);
	g2d_top_rcq_irq_en(0);
#if defined(CONFIG_ARM64)
	g2d_top_set_rcq_head((__u64)p_task->p_rcq_info->phy_addr,
			     p_task->p_rcq_info->rcq_header_len);
#else
	g2d_top_set_rcq_head((__u64)(unsigned long)p_task->p_rcq_info->phy_addr,
			     p_task->p_rcq_info->rcq_header_len);
#endif
#else
	g2d_mixer_irq_en(0);
	g2d_mixer_start(0);
#endif

	isb();

	for (i = 0; i < p_task->frame_cnt; ++i) {
		ret = p_task->frame[i].apply(&p_task->frame[i],
						 &p_para[i]);
		if (ret)
			G2D_ERR_MSG("Frame%ld apply fail!\n", i);
	}
	hal_dcache_clean((unsigned long)p_task->p_rcq_info->vir_addr,p_task->p_rcq_info->rcq_reg_mem_size);
	isb();

#if G2D_MIXER_RCQ_USED == 1
	g2d_top_rcq_irq_en(1);
	g2d_top_rcq_update_en(1);
#else
	g2d_mixer_irq_en(1);
	g2d_mixer_start(1);
#endif
	isb();

	ret = g2d_wait_cmd_finish(WAIT_CMD_TIME_MS*p_task->frame_cnt);
	memcpy(p_task->p_para, p_para,
	       sizeof(struct mixer_para) * p_task->frame_cnt);

	return ret;
}

static __s32 g2d_mixer_task_destory(struct g2d_mixer_task *p_task)
{
	__u32 i = 0;

	for (i = 0; i < p_task->frame_cnt; ++i) {
		if (p_task->frame[i].destory(&p_task->frame[i]))
			G2D_ERR_MSG("Frame:%ld destory fail!\n", i);
	}
	g2d_top_mem_pool_free(p_task->p_rcq_info);

	if (p_task->p_rcq_info) {
		free(p_task->p_rcq_info->reg_blk);
		free(p_task->p_rcq_info);
	}

	if (p_task->p_para)
		free(p_task->p_para);

	g2d_list_del(p_task);

	id_free(idr, p_task->task_id);
	free(p_task->frame);
	free(p_task);

	return 0;
}

/**
 * @name       :create_mixer_task
 * @brief      :create mixer task instance include memory allocate
 * @param[IN]  :p_g2d_info:pointer of hardware resource
 * @param[IN]  :p_para:mixer task parameter
 * @param[IN]  :frame_len:number of frame
 * @return     :task_id >= 1, else fail
 */
int create_mixer_task(__g2d_info_t *p_g2d_info, struct mixer_para *p_para,
			 unsigned int frame_len)
{
	__u32 i = 0;
	struct g2d_mixer_task *task = NULL;

	if (!p_g2d_info || !frame_len) {
		G2D_ERR_MSG("Null pointer!\n");
		goto OUT;
	}

	task = hal_malloc(sizeof(struct g2d_mixer_task));
	if (!task) {
		G2D_ERR_MSG("kmalloc g2d_mixer_task fail!\n");
		goto OUT;
	}
	memset(task, 0, sizeof(struct g2d_mixer_task));
	task->frame_cnt = frame_len;
	task->frame = hal_malloc(frame_len*sizeof(struct g2d_mixer_frame));

	task->p_rcq_info =
	    hal_malloc(sizeof(struct g2d_rcq_mem_info));

	if (!task->frame || !task->p_rcq_info) {
		G2D_ERR_MSG("Kmalloc fail!\n");
		goto FREE;
	}
	memset(task->frame, 0, frame_len*sizeof(struct g2d_mixer_frame));
	memset(task->p_rcq_info, 0, sizeof(struct g2d_rcq_mem_info));

	task->destory = g2d_mixer_task_destory;
	task->apply = g2d_mixer_apply;
	task->mixer_mem_setup = g2d_mixer_mem_setup;
	task->p_g2d_info = p_g2d_info;
	task->task_id = id_alloc(idr, NULL);
	if (task->task_id == NO_ID) {
		goto FREE;
	}

	for (i = 0; i < frame_len; ++i) {
		if (g2d_mixer_frame_setup(&task->frame[i], i)) {
			G2D_ERR_MSG("frame %ld g2d_mixer_frame_setup fail\n", i);
			goto FREE;
		}
		task->frame[i].g2d_base = (u8 *)(unsigned long)p_g2d_info->io;
	}

	if (task->mixer_mem_setup(task, p_para)) {
		task->destory(task);
		goto OUT;
	}
	task->p_para = hal_malloc(sizeof(struct mixer_para) * task->frame_cnt);
	if (!task->p_para) {
		task->destory(task);
		goto OUT;
	}
	memcpy(task->p_para, p_para, sizeof(struct mixer_para) * task->frame_cnt);


	g2d_list_add_tail(task, g2d_task_list);

	return task->task_id;
IDA_REMOVE:

	id_free(idr,  task->task_id);
FREE:
	free(task->frame);
	free(task->p_rcq_info);
	free(task);
OUT:
	return 0;
}

/**
 * @name       :g2d_mixer_get_inst
 * @brief      :get task instance of specified task id
 * @param[IN]  :id: task id
 * @return     :pointer of mixer task or NULL if fail
 */
struct g2d_mixer_task *g2d_mixer_get_inst(int id)
{

	struct g2d_mixer_task *find = g2d_task_list;


	while(find->task_id != id &&find !=NULL)
		find = find->next;
	return find;
}

__s32 mixer_task_process(__g2d_info_t *p_g2d_info, struct mixer_para *p_para,
			 unsigned int frame_len)
{
	__s32 ret = -1;
	struct g2d_mixer_task *p_task = NULL;
	int id = 0;

	id = create_mixer_task(p_g2d_info, p_para, frame_len);
	p_task = g2d_mixer_get_inst(id);
	if (!p_task)
		goto OUT;

	ret = p_task->apply(p_task, p_para);

	p_task->destory(p_task);

OUT:
	return ret;
}

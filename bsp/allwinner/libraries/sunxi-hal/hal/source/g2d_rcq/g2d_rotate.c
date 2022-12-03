/*
 * drivers/char/sunxi_g2d/g2d_rcq/g2d_rotate.c
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
#include "g2d_rotate.h"
#include "g2d_top.h"
#include "g2d_driver_i.h"
#include <hal_mem.h>

/* Rotate register */
#define G2D_ROT        (0x28000)
#define ROT_CTL            (0x00 + G2D_ROT)
#define ROT_INT            (0x04 + G2D_ROT)
#define ROT_TIMEOUT        (0x08 + G2D_ROT)
#define ROT_IFMT           (0x20 + G2D_ROT)
#define ROT_ISIZE          (0x24 + G2D_ROT)
#define ROT_IPITCH0        (0x30 + G2D_ROT)
#define ROT_IPITCH1        (0x34 + G2D_ROT)
#define ROT_IPITCH2        (0x38 + G2D_ROT)
#define ROT_ILADD0         (0x40 + G2D_ROT)
#define ROT_IHADD0         (0x44 + G2D_ROT)
#define ROT_ILADD1         (0x48 + G2D_ROT)
#define ROT_IHADD1         (0x4C + G2D_ROT)
#define ROT_ILADD2         (0x50 + G2D_ROT)
#define ROT_IHADD2         (0x54 + G2D_ROT)
#define ROT_OSIZE          (0x84 + G2D_ROT)
#define ROT_OPITCH0        (0x90 + G2D_ROT)
#define ROT_OPITCH1        (0x94 + G2D_ROT)
#define ROT_OPITCH2        (0x98 + G2D_ROT)
#define ROT_OLADD0         (0xA0 + G2D_ROT)
#define ROT_OHADD0         (0xA4 + G2D_ROT)
#define ROT_OLADD1         (0xA8 + G2D_ROT)
#define ROT_OHADD1         (0xAC + G2D_ROT)
#define ROT_OLADD2         (0xB0 + G2D_ROT)
#define ROT_OHADD2         (0xB4 + G2D_ROT)
#define LBC_ENC_CTL	   (0xC8 + G2D_ROT)
#define LBC_CTL		   (0xCC + G2D_ROT)
#define LBC_DEC_CTL	   (0xD0 + G2D_ROT)
#define G2D_AHB_RESET  (0x08)

static unsigned long base_addr;
/* #define write_wvalue(addr, data) m_usbwordwrite32(  addr, data ) */
/* #define write_wvalue(addr, v) put_wvalue(addr, v) */
/* #define read_wvalue(addr) get_wvalue(addr) */

/* byte input */
#define get_bvalue(n)	(*(volatile uint8_t  *)(n))
/* byte output */
#define put_bvalue(n, c)	(*(volatile uint8_t  *)(n) = c)
/* half word input */
#define get_hvalue(n)	(*(volatile uint16_t *)(n))
/* half word output */
#define put_hvalue(n, c)	(*(volatile uint16_t *)(n) = (c))
/* word input */
#define get_wvalue(n)	(*(volatile uint32_t *)(n))
/* word output */
#define put_wvalue(n, c)	(*(volatile uint32_t *)(n) = (c))

/* byte input */
#define read_bvalue(offset)		get_bvalue(base_addr + offset)
/* byte output */
#define write_bvalue(offset, value)	put_bvalue(base_addr + offset, value)
/* half word input */
#define read_hvalue(offset)		get_hvalue(base_addr + offset)
/* half word output */
#define write_hvalue(offset, value)	put_hvalue(base_addr + offset, value)
/* word input */
#define read_wvalue(offset)		get_wvalue(base_addr + offset)
/* word output */
#define write_wvalue(offset, value)	put_wvalue(base_addr + offset, value)

void g2d_rot_set_base(unsigned long base)
{
	base_addr = base;
}

/**
 * G2D IRQ query funct
 * if the mission finish IRQ flag was set to 1, then clear the flag
 * and return 1
 * if the IRQ was set to 0, then return 0
 */
__s32 g2d_rot_irq_query(void)
{
	__u32 tmp;

	tmp = read_wvalue(ROT_INT);
	if (tmp & 0x1) {
		write_wvalue(ROT_INT, tmp);
		return 1;
	}
	return 0;
}

__s32 g2d_rotate_set_para(g2d_image_enh *src, g2d_image_enh *dst, __u32 flag)
{
	__u32 tmp;
	__u32 ch, cw, cy, cx;
	__u32 ycnt, ucnt, vcnt;
	__s32 ret = -1;
	__u32 pitch0, pitch1, pitch2;
	__u64 addr0, addr1, addr2;

	// write_wvalue(G2D_AHB_RESET, 0x0);



	if (!dst || g2d_image_check(dst))
		goto OUT;
	if (!src || g2d_image_check(src))
		goto OUT;

	// write_wvalue(G2D_AHB_RESET, 0x3);

	tmp = 1;
	if (flag & G2D_ROT_H)
		tmp |= 0x1 << 7;
	if (flag & G2D_ROT_V)
		tmp |= 0x1 << 6;
	if ((flag & 0xf00) == G2D_ROT_90)
		tmp |= 0x1 << 4;
	if ((flag & 0xf00) == G2D_ROT_180)
		tmp |= 0x2 << 4;
	if ((flag & 0xf00) == G2D_ROT_270)
		tmp |= 0x3 << 4;
	if ((flag & 0xf00) == G2D_ROT_0)
		tmp |= 0x0 << 4;

	write_wvalue(ROT_CTL, tmp);
	write_wvalue(ROT_IFMT, src->format & 0x3F);
	write_wvalue(ROT_ISIZE, ((((src->clip_rect.h - 1) & 0x1fff) << 16)) |
				    ((src->clip_rect.w - 1) & 0x1fff));

	if ((src->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0) &&
	    (src->format <= G2D_FORMAT_YUV422_PLANAR)) {
		cw = src->width >> 1;
		ch = src->height;
		cx = src->clip_rect.x >> 1;
		cy = src->clip_rect.y;
	}

	else if ((src->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0) &&
		 (src->format <= G2D_FORMAT_YUV420_PLANAR)) {
		cw = src->width >> 1;
		ch = src->height >> 1;
		cx = src->clip_rect.x >> 1;
		cy = src->clip_rect.y >> 1;
	}

	else if ((src->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0) &&
		 (src->format <= G2D_FORMAT_YUV411_PLANAR)) {
		cw = src->width >> 2;
		ch = src->height;
		cx = src->clip_rect.x >> 2;
		cy = src->clip_rect.y;
	}

	else {
		cw = 0;
		ch = 0;
		cx = 0;
		cy = 0;
	}

	g2d_byte_cal(src->format, &ycnt, &ucnt, &vcnt);
	pitch0 = cal_align(ycnt * src->width, src->align[0]);
	write_wvalue(ROT_IPITCH0, pitch0);
	pitch1 = cal_align(ucnt * cw, src->align[1]);
	write_wvalue(ROT_IPITCH1, pitch1);
	pitch2 = cal_align(vcnt * cw, src->align[2]);
	write_wvalue(ROT_IPITCH2, pitch2);

	addr0 = src->laddr[0] + ((__u64)src->haddr[0] << 32) +
		pitch0 * src->clip_rect.y + ycnt * src->clip_rect.x;
	write_wvalue(ROT_ILADD0, addr0 & 0xffffffff);
	write_wvalue(ROT_IHADD0, (addr0 >> 32) & 0xff);
	addr1 = src->laddr[1] + ((__u64)src->haddr[1] << 32) + pitch1 * cy +
		ucnt * cx;
	write_wvalue(ROT_ILADD1, addr1 & 0xffffffff);
	write_wvalue(ROT_IHADD1, (addr1 >> 32) & 0xff);
	addr2 = src->laddr[2] + ((__u64)src->haddr[2] << 32) + pitch2 * cy +
		vcnt * cx;
	write_wvalue(ROT_ILADD2, addr2 & 0xffffffff);
	write_wvalue(ROT_IHADD2, (addr2 >> 32) & 0xff);

	if (((flag & 0xf00) == G2D_ROT_90) | ((flag & 0xf00) == G2D_ROT_270)) {
		dst->clip_rect.w = src->clip_rect.h;
		dst->clip_rect.h = src->clip_rect.w;
	}

	else {
		dst->clip_rect.w = src->clip_rect.w;
		dst->clip_rect.h = src->clip_rect.h;
	}
	write_wvalue(ROT_OSIZE, ((((dst->clip_rect.h - 1) & 0x1fff) << 16)) |
				    ((dst->clip_rect.w - 1) & 0x1fff));
	/* YUV output fmt only support 420 */
	if (src->format == G2D_FORMAT_YUV422UVC_V1U1V0U0)
		dst->format = G2D_FORMAT_YUV420UVC_V1U1V0U0;
	else if (src->format == G2D_FORMAT_YUV422UVC_U1V1U0V0)
		dst->format = G2D_FORMAT_YUV420UVC_U1V1U0V0;
	else if (src->format == G2D_FORMAT_YUV422_PLANAR)
		dst->format = G2D_FORMAT_YUV420_PLANAR;
	else
		dst->format = src->format;

	if ((dst->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0) &&
	    (dst->format <= G2D_FORMAT_YUV422_PLANAR)) {
		cw = dst->width >> 1;
		ch = dst->height;
		cx = dst->clip_rect.x >> 1;
		cy = dst->clip_rect.y;
	}

	else if ((dst->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0) &&
		 (dst->format <= G2D_FORMAT_YUV420_PLANAR)) {
		cw = dst->width >> 1;
		ch = dst->height >> 1;
		cx = dst->clip_rect.x >> 1;
		cy = dst->clip_rect.y >> 1;
	}

	else if ((dst->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0) &&
		 (dst->format <= G2D_FORMAT_YUV411_PLANAR)) {
		cw = dst->width >> 2;
		ch = dst->height;
		cx = dst->clip_rect.x >> 2;
		cy = dst->clip_rect.y;
	}

	else {
		cw = 0;
		ch = 0;
		cx = 0;
		cy = 0;
	}

	g2d_byte_cal(dst->format, &ycnt, &ucnt, &vcnt);

	pitch0 = cal_align(ycnt * dst->width, dst->align[0]);
	write_wvalue(ROT_OPITCH0, pitch0);
	pitch1 = cal_align(ucnt * cw, dst->align[1]);
	write_wvalue(ROT_OPITCH1, pitch1);
	pitch2 = cal_align(vcnt * cw, dst->align[2]);
	write_wvalue(ROT_OPITCH2, pitch2);

	addr0 = dst->laddr[0] + ((__u64)dst->haddr[0] << 32) +
		pitch0 * dst->clip_rect.y + ycnt * dst->clip_rect.x;
	write_wvalue(ROT_OLADD0, addr0 & 0xffffffff);
	write_wvalue(ROT_OHADD0, (addr0 >> 32) & 0xff);
	addr1 = dst->laddr[1] + ((__u64)dst->haddr[1] << 32) + pitch1 * cy +
		ucnt * cx;
	write_wvalue(ROT_OLADD1, addr1 & 0xffffffff);
	write_wvalue(ROT_OHADD1, (addr1 >> 32) & 0xff);
	addr2 = dst->laddr[2] + ((__u64)dst->haddr[2] << 32) + pitch2 * cy +
		vcnt * cx;
	write_wvalue(ROT_OLADD2, addr2 & 0xffffffff);
	write_wvalue(ROT_OHADD2, (addr2 >> 32) & 0xff);

	/* start the module */
	write_wvalue(ROT_INT, 0x10000);
	tmp = read_wvalue(ROT_CTL);
	tmp |= (0x1 << 31);
	write_wvalue(ROT_CTL, tmp);

	ret = g2d_wait_cmd_finish(WAIT_CMD_TIME_MS);

OUT:
	return ret;
}

__s32 g2d_lbc_calc_ctrl(u32 flag, u32 frm_width, u32 frm_height,
			u32 cmp_ratio, u32 enc_is_lossy, u32 dec_is_lossy)
{
	u32 tmp = 0;
	u32 seg_width = 16, seg_height = 4;
	u32 bit_depth = 8;
	u32 enc_c_ratio = 333;
	u32 ALIGN = 128;
	u32 seg_tar_bits, seg_tar_bits_y, seg_tar_bits_c, dec_segline_tar_bits, enc_segline_tar_bits;
	u32 y_mode_bits, c_mode_bits, y_data_bits, c_data_bits;

	if (enc_is_lossy) {
		seg_tar_bits = ((seg_width * seg_height * bit_depth * cmp_ratio * 3 / 2000) / ALIGN) * ALIGN;
		seg_tar_bits_y = seg_tar_bits * (1024 - enc_c_ratio) / 1024;
		seg_tar_bits_c = seg_tar_bits - seg_tar_bits_y;
		dec_segline_tar_bits = ((frm_width + seg_width - 1) / seg_width) * seg_tar_bits;
		if (((flag & 0xf00) == G2D_ROT_90) || ((flag & 0xf00) == G2D_ROT_270))
			enc_segline_tar_bits = ((frm_height + seg_width - 1) / seg_width) * seg_tar_bits;
		else
			enc_segline_tar_bits = dec_segline_tar_bits;
	} else {
		y_mode_bits = seg_width / 8 * (3 * 2 + 2);
		c_mode_bits = 2 * (seg_width / 2 / 8 * 2);
		y_data_bits = seg_width * seg_height * bit_depth;
		c_data_bits = seg_width * seg_height * bit_depth / 2 + 2 * (seg_width / 2 / 8) * 4;
		seg_tar_bits = (y_data_bits + c_data_bits + y_mode_bits + c_mode_bits + ALIGN - 1) / ALIGN * ALIGN;
		seg_tar_bits_y = seg_tar_bits;
		seg_tar_bits_c = 0;
		dec_segline_tar_bits = ((frm_width + seg_width - 1) / seg_width) * seg_tar_bits;
		if (((flag & 0xf00) == G2D_ROT_90) || ((flag & 0xf00) == G2D_ROT_270))
			enc_segline_tar_bits = ((frm_height + seg_width - 1) / seg_width) * seg_tar_bits;
		else
			enc_segline_tar_bits = dec_segline_tar_bits;
	}
	tmp |= (enc_is_lossy << 31);
	/*tmp |= (0x1 << 30);*///fix me
	tmp |= (0x1 << 29);/*only 1 frame not care use even */
	tmp |= ((enc_c_ratio & 0x3ff) << 19);
	tmp |= ((enc_segline_tar_bits & 0x1ffff) << 2);
	tmp |= (0x1 << 1);
	write_wvalue(LBC_ENC_CTL, tmp);

	tmp = read_wvalue(LBC_CTL);
	tmp |= ((seg_tar_bits_y & 0x7ff) << 21);
	tmp |= ((seg_tar_bits_c & 0x7ff) << 10);
	write_wvalue(LBC_CTL, tmp);

	tmp = 0;
	tmp |= ((dec_segline_tar_bits & 0x1ffff) << 2);
	tmp |= (dec_is_lossy << 31);
	write_wvalue(LBC_DEC_CTL, tmp);

	return 0;
}
__s32 g2d_lbc_rot_set_para(g2d_lbc_rot *para)
{
	__u32 tmp = 0;
	__u32 lbc = 0;
	__u32 ch, cw, cy, cx;
	__u32 ycnt, ucnt, vcnt;
	__s32 ret = -1;
	__u32 pitch0, pitch1, pitch2;
	__u64 addr0, addr1, addr2;
	struct dmabuf_item *src_item = NULL;
	struct dmabuf_item *dst_item = NULL;
	/* lbc para */
	u32 frm_width = 0, frm_height = 0;
	u32 cmp_ratio = 500;
	u32 enc_is_lossy = 1, dec_is_lossy = 1;

	__u32 flag = para->blt.flag_h;
	g2d_image_enh *src = &para->blt.src_image_h;
	g2d_image_enh *dst = &para->blt.dst_image_h;

	// write_wvalue(G2D_AHB_RESET, 0x0);

	if (!dst || g2d_image_check(dst))
		goto OUT;
	if (!src || g2d_image_check(src))
		goto OUT;

	if ((src->format != G2D_FORMAT_YUV420_PLANAR) ||
			(dst->format != G2D_FORMAT_YUV420_PLANAR)) {
		G2D_ERR_MSG("LBC only support YUV420 plannar fmt!\n");
		goto OUT;
	}

	if (((flag & 0xf00) == G2D_ROT_180) || ((flag & 0xf000) == G2D_ROT_V)) {
		G2D_ERR_MSG("LBC not support 180 and V flip!\n");
		goto OUT;
	}
/*
	if (!src->use_phy_addr || !dst->use_phy_addr) {
		src_item = hal_malloc(sizeof(struct dmabuf_item));
		if (src_item == NULL) {
			G2D_ERR_MSG("malloc memory of size %u fail!\n",
				    (unsigned int)sizeof(struct dmabuf_item));
			goto OUT;
		}
		dst_item = hal_malloc(sizeof(struct dmabuf_item));
		if (dst_item == NULL) {
			G2D_ERR_MSG("malloc memory of size %u fail!\n",
				    (unsigned int)sizeof(struct dmabuf_item));
			goto FREE_SRC;
		}*/
/*		ret = g2d_dma_map(src->fd, src_item);
		if (ret != 0) {
			G2D_ERR_MSG("map src_item fail!\n");
			goto FREE_DST;
		}
		g2d_set_info(src, src_item);

		ret = g2d_dma_map(dst->fd, dst_item);
		if (ret != 0) {
			G2D_ERR_MSG("map dst_item fail!\n");
			goto SRC_DMA_UNMAP;
		}
		g2d_set_info(dst, dst_item);
	}*/
	// write_wvalue(G2D_AHB_RESET, 0x3);

	/* rotate use same format */
	dst->format = src->format;

	tmp = 1;
	write_wvalue(ROT_CTL, tmp);

	if ((flag & 0xf00) == G2D_ROT_0)
		lbc |= 0x0 << 7;
	if ((flag & 0xf00) == G2D_ROT_90)
		lbc |= 0x1 << 7;
	if ((flag & 0xf00) == G2D_ROT_270)
		lbc |= 0x2 << 7;
	if (flag & G2D_ROT_H)
		lbc |= 0x3 << 7;
	write_wvalue(LBC_CTL, lbc);

	write_wvalue(ROT_IFMT, src->format & 0x3F);
	write_wvalue(ROT_ISIZE, ((((src->clip_rect.h - 1) & 0x1fff) << 16)) |
				    ((src->clip_rect.w - 1) & 0x1fff));

	if ((src->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0) &&
	    (src->format <= G2D_FORMAT_YUV422_PLANAR)) {
		cw = src->width >> 1;
		ch = src->height;
		cx = src->clip_rect.x >> 1;
		cy = src->clip_rect.y;
	}

	else if ((src->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0) &&
		 (src->format <= G2D_FORMAT_YUV420_PLANAR)) {
		cw = src->width >> 1;
		ch = src->height >> 1;
		cx = src->clip_rect.x >> 1;
		cy = src->clip_rect.y >> 1;
	}

	else if ((src->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0) &&
		 (src->format <= G2D_FORMAT_YUV411_PLANAR)) {
		cw = src->width >> 2;
		ch = src->height;
		cx = src->clip_rect.x >> 2;
		cy = src->clip_rect.y;
	}

	else {
		cw = 0;
		ch = 0;
		cx = 0;
		cy = 0;
	}

	g2d_byte_cal(src->format, &ycnt, &ucnt, &vcnt);
	pitch0 = cal_align(ycnt * src->width, src->align[0]);
	write_wvalue(ROT_IPITCH0, pitch0);
	pitch1 = cal_align(ucnt * cw, src->align[1]);
	write_wvalue(ROT_IPITCH1, pitch1);
	pitch2 = cal_align(vcnt * cw, src->align[2]);
	write_wvalue(ROT_IPITCH2, pitch2);

	addr0 = src->laddr[0] + ((__u64)src->haddr[0] << 32) +
		pitch0 * src->clip_rect.y + ycnt * src->clip_rect.x;
	write_wvalue(ROT_ILADD0, addr0 & 0xffffffff);
	write_wvalue(ROT_IHADD0, (addr0 >> 32) & 0xff);
	addr1 = src->laddr[1] + ((__u64)src->haddr[1] << 32) + pitch1 * cy +
		ucnt * cx;
	write_wvalue(ROT_ILADD1, addr1 & 0xffffffff);
	write_wvalue(ROT_IHADD1, (addr1 >> 32) & 0xff);
	addr2 = src->laddr[2] + ((__u64)src->haddr[2] << 32) + pitch2 * cy +
		vcnt * cx;
	write_wvalue(ROT_ILADD2, addr2 & 0xffffffff);
	write_wvalue(ROT_IHADD2, (addr2 >> 32) & 0xff);

	if (((flag & 0xf00) == G2D_ROT_90) || ((flag & 0xf00) == G2D_ROT_270)) {
		dst->clip_rect.w = src->clip_rect.h;
		dst->clip_rect.h = src->clip_rect.w;
	}

	else {
		dst->clip_rect.w = src->clip_rect.w;
		dst->clip_rect.h = src->clip_rect.h;
	}
	write_wvalue(ROT_OSIZE, ((((dst->clip_rect.h - 1) & 0x1fff) << 16)) |
				    ((dst->clip_rect.w - 1) & 0x1fff));


	if ((dst->format >= G2D_FORMAT_YUV422UVC_V1U1V0U0) &&
	    (dst->format <= G2D_FORMAT_YUV422_PLANAR)) {
		cw = dst->width >> 1;
		ch = dst->height;
		cx = dst->clip_rect.x >> 1;
		cy = dst->clip_rect.y;
	}

	else if ((dst->format >= G2D_FORMAT_YUV420UVC_V1U1V0U0) &&
		 (dst->format <= G2D_FORMAT_YUV420_PLANAR)) {
		cw = dst->width >> 1;
		ch = dst->height >> 1;
		cx = dst->clip_rect.x >> 1;
		cy = dst->clip_rect.y >> 1;
	}

	else if ((dst->format >= G2D_FORMAT_YUV411UVC_V1U1V0U0) &&
		 (dst->format <= G2D_FORMAT_YUV411_PLANAR)) {
		cw = dst->width >> 2;
		ch = dst->height;
		cx = dst->clip_rect.x >> 2;
		cy = dst->clip_rect.y;
	}

	else {
		cw = 0;
		ch = 0;
		cx = 0;
		cy = 0;
	}

	g2d_byte_cal(dst->format, &ycnt, &ucnt, &vcnt);

	pitch0 = cal_align(ycnt * dst->width, dst->align[0]);
	write_wvalue(ROT_OPITCH0, pitch0);
	pitch1 = cal_align(ucnt * cw, dst->align[1]);
	write_wvalue(ROT_OPITCH1, pitch1);
	pitch2 = cal_align(vcnt * cw, dst->align[2]);
	write_wvalue(ROT_OPITCH2, pitch2);

	addr0 = dst->laddr[0] + ((__u64)dst->haddr[0] << 32) +
		pitch0 * dst->clip_rect.y + ycnt * dst->clip_rect.x;
	write_wvalue(ROT_OLADD0, addr0 & 0xffffffff);
	write_wvalue(ROT_OHADD0, (addr0 >> 32) & 0xff);
	addr1 = dst->laddr[1] + ((__u64)dst->haddr[1] << 32) + pitch1 * cy +
		ucnt * cx;
	write_wvalue(ROT_OLADD1, addr1 & 0xffffffff);
	write_wvalue(ROT_OHADD1, (addr1 >> 32) & 0xff);
	addr2 = dst->laddr[2] + ((__u64)dst->haddr[2] << 32) + pitch2 * cy +
		vcnt * cx;
	write_wvalue(ROT_OLADD2, addr2 & 0xffffffff);
	write_wvalue(ROT_OHADD2, (addr2 >> 32) & 0xff);


	/* lbc */

	frm_width = src->width;
	frm_height = src->height;
	cmp_ratio = para->lbc_cmp_ratio;
	enc_is_lossy = para->enc_is_lossy;
	dec_is_lossy = para->dec_is_lossy;
	g2d_lbc_calc_ctrl(flag, frm_width, frm_height, cmp_ratio, enc_is_lossy, dec_is_lossy);

	/* start the module */
	write_wvalue(ROT_INT, 0x10000);
	tmp = read_wvalue(ROT_CTL);
	tmp |= (0x1 << 31);
	write_wvalue(ROT_CTL, tmp);

	ret = g2d_wait_cmd_finish(WAIT_CMD_TIME_MS);

/*	if (!src->use_phy_addr || !dst->use_phy_addr)
		g2d_dma_unmap(dst_item);
SRC_DMA_UNMAP:
	if (!src->use_phy_addr || !dst->use_phy_addr)
		g2d_dma_unmap(src_item);*/
FREE_DST:
	free(dst_item);
FREE_SRC:
	free(src_item);
OUT:
	return ret;
}

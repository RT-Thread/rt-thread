/*
 * Copyright (c) 2026 Yuzuki Tsuru
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

/*
 * Turns a g2d_op into the register images of the hardware.
 *
 * Two engines exist. The mixer is a small pipeline:
 *
 *   V0 (scalable, YUV)  -> [video scaler] -+
 *                                          +-> blender -> write back
 *   UI2 (RGB)  -----------------------------+
 *
 * Fill, copy/convert/scale and blend all run through it; they differ in
 * which overlays are enabled. The rotate engine is a separate DMA to DMA
 * path for rotation and flipping without any scaling.
 */

#include <errno.h>
#include <string.h>

#define DBG_TAG "g2d"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <rtthread.h>

#include "g2d_sunxi_hw.h"
#include "g2d_sunxi_regs.h"


#define OVL_ALPHA_PIXEL		0
#define OVL_ALPHA_GLOBAL	1
#define OVL_ALPHA_MIXED		2

/* mixer overlay used for the background of a blend */
#define BLEND_UI		2

/* a single layer in pipe 0, passed through unchanged */
#define BLD_PIPE0_ONLY		0x03010301
#define BLD_ROP_BYPASS		0xf0
#define BLD_ROP_INDEX0_DEFAULT	0x41000
#define BLD_FILL_YUV_BLACK	0x00108080

#define VSU_FRAC_BITS		19
#define VSU_COARSE_MAX_W	2048

#define ROT_MODE_NORMAL		1

/*
 * Blender factors { pfs, pfd, afs, afd }, packed as the register wants them.
 *
 * In the equations of the hardware, pipe 1 is the "source" and pipe 0 the
 * "destination" (measured: with the vendor's SRCOVER value the pipe 1 layer
 * is drawn over pipe 0). The foreground of a blend sits in pipe 0, the V0
 * overlay that can scale and take YUV, so each mode of the API uses the
 * vendor value of its mirror image.
 */
static const uint32_t bld_factors[] = {
	[G2D_BLEND_CLEAR] = 0x00000000,
	[G2D_BLEND_SRC] = 0x01000100,
	[G2D_BLEND_DST] = 0x00010001,
	[G2D_BLEND_SRC_OVER] = 0x01030103,
	[G2D_BLEND_DST_OVER] = 0x03010301,
	[G2D_BLEND_SRC_IN] = 0x02000200,
	[G2D_BLEND_DST_IN] = 0x00020002,
	[G2D_BLEND_SRC_OUT] = 0x03000300,
	[G2D_BLEND_DST_OUT] = 0x00030003,
	[G2D_BLEND_SRC_ATOP] = 0x02030203,
	[G2D_BLEND_DST_ATOP] = 0x03020302,
	[G2D_BLEND_XOR] = 0x03030303,
};

struct mixer {
	struct g2d_cmdlist *cl;
	uint32_t *core;
	uint32_t *wb;
	uint32_t *v0;
	uint32_t *ui[3];
	uint32_t *bld;
};

static inline void reg_set(uint32_t *blk, uint32_t off, uint32_t val)
{
	blk[off / 4] = val;
}

static inline void reg_or(uint32_t *blk, uint32_t off, uint32_t val)
{
	blk[off / 4] |= val;
}

static uint32_t alpha_mode_hw(enum g2d_alpha_mode mode)
{
	switch (mode) {
	case G2D_ALPHA_GLOBAL:
		return OVL_ALPHA_GLOBAL;
	case G2D_ALPHA_MIXED:
		return OVL_ALPHA_MIXED;
	default:
		return OVL_ALPHA_PIXEL;
	}
}

/* the size registers hold size - 1 */
static uint32_t size_reg(uint32_t w, uint32_t h)
{
	return G2D_SIZE(w, h);
}

/* ---- mixer building blocks ---------------------------------------------- */

static int mixer_begin(struct mixer *m, struct g2d_cmdlist *cl)
{
	unsigned int i;

	m->cl = cl;
	m->core = g2d_cmdlist_block(cl, G2D_CORE_CTRL, G2D_CORE_CTRL_SIZE);
	m->wb = g2d_cmdlist_block(cl, G2D_WB, G2D_WB_SIZE);
	m->v0 = g2d_cmdlist_block(cl, G2D_V0, G2D_V0_SIZE);
	for (i = 0; i < RT_ARRAY_SIZE(m->ui); i++) {
		m->ui[i] = g2d_cmdlist_block(cl, G2D_UI(i), G2D_UI_SIZE);
	}
	m->bld = g2d_cmdlist_block(cl, G2D_BLD, G2D_BLD_SIZE);
	if (!m->core || !m->wb || !m->v0 || !m->ui[0] || !m->ui[1] ||
		!m->ui[2] || !m->bld) {
		return -ENOMEM;
	}

	reg_set(m->core, 0, G2D_CORE_CTRL_MIXER);
	/* the blender passes the blend result through, no raster operation */
	reg_set(m->bld, G2D_BLD_ROP_CTRL, BLD_ROP_BYPASS);
	reg_set(m->bld, G2D_BLD_ROP_INDEX0, BLD_ROP_INDEX0_DEFAULT);
	return 0;
}

static uint32_t ovl_attr(const struct g2d_hw_buf *b, uint32_t alpha_mode, uint8_t alpha,
			 bool premul)
{
	return G2D_OVL_ATTR_EN | RT_FIELD_PREP(G2D_OVL_ATTR_ALPHA_MODE_MASK, alpha_mode) |
	       RT_FIELD_PREP(G2D_OVL_ATTR_FORMAT_MASK, b->fmt->hw) |
	       (premul ? G2D_OVL_ATTR_PREMUL : 0) | RT_FIELD_PREP(G2D_OVL_ATTR_ALPHA_MASK, alpha);
}

static void v0_setup(struct mixer *m, const struct g2d_hw_buf *b, uint32_t alpha_mode,
		     uint8_t alpha, bool premul)
{
	unsigned int p;

	reg_set(m->v0, G2D_OVL_ATTR, ovl_attr(b, alpha_mode, alpha, premul));
	reg_set(m->v0, G2D_OVL_MEM_SIZE, size_reg(b->width, b->height));
	reg_set(m->v0, G2D_V0_WIN_SIZE, size_reg(b->width, b->height));
	reg_set(m->v0, G2D_OVL_PITCH0, b->pitch[0]);
	reg_set(m->v0, G2D_V0_PITCH1, b->pitch[1]);
	reg_set(m->v0, G2D_V0_PITCH2, b->pitch[2]);
	for (p = 0; p < G2D_MAX_PLANES; p++) {
		reg_set(m->v0, G2D_V0_ADDR(p), b->addr[p]);
	}
}

static void ui_setup(struct mixer *m, unsigned int n, const struct g2d_hw_buf *b,
		     uint32_t alpha_mode, uint8_t alpha, bool premul)
{
	reg_set(m->ui[n], G2D_OVL_ATTR, ovl_attr(b, alpha_mode, alpha, premul));
	reg_set(m->ui[n], G2D_OVL_MEM_SIZE, size_reg(b->width, b->height));
	reg_set(m->ui[n], G2D_UI_WIN_SIZE, size_reg(b->width, b->height));
	reg_set(m->ui[n], G2D_OVL_PITCH0, b->pitch[0]);
	reg_set(m->ui[n], G2D_UI_ADDR, b->addr[0]);
}

static void bld_pipe(struct mixer *m, unsigned int pipe, uint32_t w, uint32_t h, bool premul)
{
	if (pipe == 0) {
		/* pipe 0 is the bottom layer of the blender: it also fills the area */
		reg_or(m->bld, G2D_BLD_EN, G2D_BLD_EN_P0 | G2D_BLD_EN_P0_FILL);
	} else {
		reg_or(m->bld, G2D_BLD_EN, G2D_BLD_EN_P1);
	}
	reg_set(m->bld, G2D_BLD_PIPE_SIZE(pipe), size_reg(w, h));
	reg_set(m->bld, G2D_BLD_PIPE_COOR(pipe), 0);
	if (premul) {
		reg_or(m->bld, G2D_BLD_PREMUL, RT_BIT(pipe));
	}
}

static void bld_output(struct mixer *m, uint32_t w, uint32_t h, bool premul, bool yuv_domain)
{
	reg_set(m->bld, G2D_BLD_OUT_SIZE, size_reg(w, h));
	reg_set(m->bld, G2D_BLD_OUT_COLOR,
		(premul ? G2D_BLD_OUT_PREMUL : 0) | (yuv_domain ? G2D_BLD_OUT_YUV : 0));
}

/* colour space converter @p n takes YCbCr from a pipe/output and produces RGB */
static void bld_csc_yuv2rgb(struct mixer *m, unsigned int n, uint32_t flags)
{
	const uint32_t (*tab)[G2D_CSC_WORDS] =
		(flags & G2D_FLAG_YUV_BT709) ? g2d_csc_yuv2rgb_709 : g2d_csc_yuv2rgb_601;
	const uint32_t *matrix = tab[(flags & G2D_FLAG_YUV_FULL_RANGE) ? 1 : 0];

	reg_or(m->bld, G2D_BLD_CSC_CTRL, G2D_BLD_CSC_EN(n));
	reg_set(m->bld, G2D_BLD_FILL_COLOR(0), BLD_FILL_YUV_BLACK);
	reg_set(m->bld, G2D_BLD_FILL_COLOR(1), BLD_FILL_YUV_BLACK);
	memcpy(&m->bld[G2D_BLD_CSC(n) / 4], matrix, G2D_CSC_WORDS * sizeof(uint32_t));
}

static void wb_setup(struct mixer *m, const struct g2d_hw_buf *d)
{
	reg_set(m->wb, G2D_WB_ATTR, RT_FIELD_PREP(G2D_WB_ATTR_FORMAT_MASK, d->fmt->hw));
	reg_set(m->wb, G2D_WB_DATA_SIZE, size_reg(d->width, d->height));
	reg_set(m->wb, G2D_WB_PITCH(0), d->pitch[0]);
	reg_set(m->wb, G2D_WB_ADDR(0), d->addr[0]);
}

/*
 * Coarse down sampling in front of the scaler: the scaler itself handles up
 * to 8x horizontally and 4x vertically, larger reductions are pre-reduced by
 * the overlay. Returns the size the scaler sees.
 */
static void v0_coarse(struct mixer *m, const struct g2d_fmt_info *fmt, uint32_t in_w, uint32_t in_h,
		      uint32_t out_w, uint32_t out_h, uint32_t *mid_w, uint32_t *mid_h)
{
	/* chroma planes of the subsampled formats are reduced by the same factor */
	unsigned int hs = fmt->planes > 1 ? fmt->hshift[1] : 0;
	unsigned int vs = fmt->planes > 1 ? fmt->vshift[1] : 0;
	bool hor = false, ver = false;

	*mid_w = in_w;
	*mid_h = in_h;

	if (fmt->planes == 1 && fmt->yuv) {
		/* packed YUV: no coarse stage */
		return;
	}
	if (in_w >= (out_w << 3)) {
        *mid_w = rt_min_t(rt_uint32_t, out_w << 3, VSU_COARSE_MAX_W);
		hor = true;
	} else if (in_w > VSU_COARSE_MAX_W) {
		*mid_w = VSU_COARSE_MAX_W;
		hor = true;
	}
	if (in_h >= (out_h << 2)) {
		*mid_h = out_h << 2;
		ver = true;
	}

	if (hor) {
		reg_set(m->v0, G2D_V0_HDS0, (*mid_w << 16) | in_w);
		reg_set(m->v0, G2D_V0_HDS1,
			((*mid_w >> hs) << 16) | ((in_w + RT_BIT(hs) - 1) >> hs));
	}
	if (ver) {
		reg_set(m->v0, G2D_V0_VDS0, (*mid_h << 16) | in_h);
		reg_set(m->v0, G2D_V0_VDS1,
			((*mid_h >> vs) << 16) | ((in_h + RT_BIT(vs) - 1) >> vs));
	}
}

/* coefficient set for a scale step (1/8 resolution of the ratio) */
static unsigned int vsu_coef_set(uint32_t step)
{
	uint32_t ratio = step >> (VSU_FRAC_BITS - 3);
	uint32_t ip = ratio >> 3;
	uint32_t fp = ratio & 7;

	switch (ip) {
	case 0:
		return 0;
	case 1:
		return 1 + fp;
	case 2:
		return 9 + (fp >> 1);
	case 3:
		return 13;
	case 4:
		return 14;
	default:
		return 15;
	}
}

static void vsu_load_coef(uint32_t *vsu, uint32_t off, const uint32_t *coef)
{
	memcpy(&vsu[off / 4], coef, G2D_VSU_PHASES * sizeof(uint32_t));
}

/* enable the video scaler for the V0 overlay: in (after the coarse stage) -> out */
static int vsu_enable(struct mixer *m, const struct g2d_fmt_info *fmt, uint32_t in_w, uint32_t in_h,
		      uint32_t out_w, uint32_t out_h, uint8_t alpha)
{
	uint32_t *vsu = g2d_cmdlist_block(m->cl, G2D_VSU, G2D_VSU_SIZE);
	uint32_t hstep, vstep, cw, ch;
	bool planar420 = fmt->planes > 1;
	bool packed422 = fmt->yuv && fmt->planes == 1;

	if (vsu == NULL) {
		return -ENOMEM;
	}

	hstep = ((uint64_t)in_w << VSU_FRAC_BITS) / out_w;
	vstep = ((uint64_t)in_h << VSU_FRAC_BITS) / out_h;

	reg_set(vsu, G2D_VSU_CTRL,
		G2D_VSU_CTRL_EN | G2D_VSU_CTRL_COEF_ACCESS |
			(planar420 ? G2D_VSU_CTRL_FILTER_PLANAR : 0));
	reg_set(vsu, G2D_VSU_OUT_SIZE, size_reg(out_w, out_h));
	reg_set(vsu, G2D_VSU_GLB_ALPHA, alpha);
	reg_set(vsu, G2D_VSU_Y_SIZE, size_reg(in_w, in_h));
	/* the step registers have a reserved bit 0 */
	reg_set(vsu, G2D_VSU_Y_HSTEP, hstep << 1);
	reg_set(vsu, G2D_VSU_Y_VSTEP, vstep << 1);
	vsu_load_coef(vsu, G2D_VSU_Y_HCOEF, g2d_vsu_coef_lanczos[vsu_coef_set(hstep)]);

	if (planar420) {
		/* 4:2:0: chroma has half the luma resolution in both directions */
		cw = (in_w + 1) >> 1;
		ch = (in_h + 1) >> 1;
		reg_set(vsu, G2D_VSU_C_SIZE, size_reg(cw, ch));
		reg_set(vsu, G2D_VSU_C_HSTEP, hstep);
		reg_set(vsu, G2D_VSU_C_VSTEP, vstep);
		reg_set(vsu, G2D_VSU_C_HPHASE, 0xfffc0000);
		reg_set(vsu, G2D_VSU_C_VPHASE, 0xfffc0000);
		vsu_load_coef(vsu, G2D_VSU_C_HCOEF, g2d_vsu_coef_lanczos[vsu_coef_set(hstep >> 1)]);
		vsu_load_coef(vsu, G2D_VSU_Y_VCOEF, g2d_vsu_coef_lanczos[vsu_coef_set(vstep)]);
	} else if (packed422) {
		/* 4:2:2: half the horizontal resolution only */
		cw = (in_w + 1) >> 1;
		reg_set(vsu, G2D_VSU_C_SIZE, size_reg(cw, in_h));
		reg_set(vsu, G2D_VSU_C_HSTEP, hstep);
		reg_set(vsu, G2D_VSU_C_VSTEP, vstep << 1);
		vsu_load_coef(vsu, G2D_VSU_C_HCOEF, g2d_vsu_coef_lanczos[vsu_coef_set(hstep >> 1)]);
		vsu_load_coef(vsu, G2D_VSU_Y_VCOEF, g2d_vsu_coef_linear);
	} else {
		/* RGB: the "chroma" path carries the same samples */
		reg_set(vsu, G2D_VSU_C_SIZE, size_reg(in_w, in_h));
		reg_set(vsu, G2D_VSU_C_HSTEP, hstep << 1);
		reg_set(vsu, G2D_VSU_C_VSTEP, vstep << 1);
		vsu_load_coef(vsu, G2D_VSU_C_HCOEF, g2d_vsu_coef_lanczos[vsu_coef_set(hstep)]);
		vsu_load_coef(vsu, G2D_VSU_Y_VCOEF, g2d_vsu_coef_linear);
	}
	return 0;
}

/* Keep the VSU block in the command list even when scaling is disabled. */
static int vsu_disable(struct mixer *m)
{
	uint32_t *vsu = g2d_cmdlist_block(m->cl, G2D_VSU, sizeof(uint32_t));

	return vsu ? 0 : -ENOMEM;
}

/* ---- operations ---------------------------------------------------------- */

static int compose_fill(struct g2d_cmdlist *cl, const struct g2d_op *op)
{
	struct g2d_hw_buf d;
	struct mixer m;
	int ret;

	ret = g2d_hw_buf_init(&d, &op->dst, &op->dst_rect);
	if (ret) {
		return ret;
	}
	ret = mixer_begin(&m, cl);
	if (ret) {
		return ret;
	}

	/* V0 supplies a constant colour; the dst rectangle only sizes the output */
	v0_setup(&m, &d, OVL_ALPHA_PIXEL, 0xff, false);
	reg_or(m.v0, G2D_OVL_ATTR, G2D_OVL_ATTR_FILL_EN);
	reg_set(m.v0, G2D_V0_FILL, op->color);

	bld_pipe(&m, 0, d.width, d.height, false);
	reg_set(m.bld, G2D_BLD_CTRL, BLD_PIPE0_ONLY);
	bld_output(&m, d.width, d.height, op->flags & G2D_FLAG_DST_PREMULTIPLIED, false);
	wb_setup(&m, &d);

	return vsu_disable(&m);
}

static int compose_blit(struct g2d_cmdlist *cl, const struct g2d_op *op)
{
	struct g2d_hw_buf s, d;
	struct mixer m;
	bool scaled;
	int ret;

	ret = g2d_hw_buf_init(&s, &op->src, &op->src_rect);
	if (ret == 0) {
		ret = g2d_hw_buf_init(&d, &op->dst, &op->dst_rect);
	}
	if (ret) {
		return ret;
	}
	ret = mixer_begin(&m, cl);
	if (ret) {
		return ret;
	}

	v0_setup(&m, &s, OVL_ALPHA_PIXEL, 0xff, op->flags & G2D_FLAG_SRC_PREMULTIPLIED);

	scaled = s.fmt->yuv || s.width != d.width || s.height != d.height;
	if (scaled) {
		uint32_t mid_w, mid_h;

		v0_coarse(&m, s.fmt, s.width, s.height, d.width, d.height, &mid_w, &mid_h);
		ret = vsu_enable(&m, s.fmt, mid_w, mid_h, d.width, d.height, 0xff);
	} else {
		ret = vsu_disable(&m);
	}
	if (ret) {
		return ret;
	}

	bld_pipe(&m, 0, d.width, d.height, op->flags & G2D_FLAG_SRC_PREMULTIPLIED);
	reg_set(m.bld, G2D_BLD_CTRL, BLD_PIPE0_ONLY);
	/* YCbCr stays in its colour space through the blender, converted at the output */
	bld_output(&m, d.width, d.height, op->flags & G2D_FLAG_DST_PREMULTIPLIED, s.fmt->yuv);
	if (s.fmt->yuv) {
		bld_csc_yuv2rgb(&m, 2, op->flags);
	}
	wb_setup(&m, &d);
	return 0;
}

static int compose_blend(struct g2d_cmdlist *cl, const struct g2d_op *op)
{
	const struct g2d_blend *bl = &op->blend;
	struct g2d_hw_buf f, b, d;
	struct mixer m;
	bool scaled;
	int ret;

	if ((unsigned int)bl->mode >= RT_ARRAY_SIZE(bld_factors)) {
		return -EINVAL;
	}
	ret = g2d_hw_buf_init(&f, &op->src, &op->src_rect);
	if (ret == 0) {
		ret = g2d_hw_buf_init(&b, &op->bg, &op->bg_rect);
	}
	if (ret == 0) {
		ret = g2d_hw_buf_init(&d, &op->dst, &op->dst_rect);
	}
	if (ret) {
		return ret;
	}
	/* the background is not scaled and the UI overlay takes RGB only */
	if (b.fmt->yuv || b.width != d.width || b.height != d.height) {
		LOG_D("background must be RGB and as big as the destination");
		return -EINVAL;
	}
	ret = mixer_begin(&m, cl);
	if (ret) {
		return ret;
	}

	v0_setup(&m, &f, alpha_mode_hw(bl->fg_alpha_mode), bl->fg_alpha,
		 op->flags & G2D_FLAG_SRC_PREMULTIPLIED);
	ui_setup(&m, BLEND_UI, &b, alpha_mode_hw(bl->bg_alpha_mode), bl->bg_alpha,
		 op->flags & G2D_FLAG_DST_PREMULTIPLIED);

	scaled = f.fmt->yuv || f.width != d.width || f.height != d.height;
	if (scaled) {
		uint32_t mid_w, mid_h;

		v0_coarse(&m, f.fmt, f.width, f.height, d.width, d.height, &mid_w, &mid_h);
		ret = vsu_enable(&m, f.fmt, mid_w, mid_h, d.width, d.height,
				 f.fmt->yuv ? 0xff : bl->fg_alpha);
	} else {
		ret = vsu_disable(&m);
	}
	if (ret) {
		return ret;
	}
	if (f.fmt->yuv) {
		/* convert the foreground to RGB before it enters the blender */
		bld_csc_yuv2rgb(&m, 0, op->flags);
	}

	bld_pipe(&m, 0, d.width, d.height, op->flags & G2D_FLAG_SRC_PREMULTIPLIED);
	bld_pipe(&m, 1, d.width, d.height, op->flags & G2D_FLAG_DST_PREMULTIPLIED);
	reg_set(m.bld, G2D_BLD_CTRL, bld_factors[bl->mode]);
	if (bl->color_key) {
		reg_set(m.bld, G2D_BLD_CK_CFG, 0);
		reg_set(m.bld, G2D_BLD_CK_MAX, bl->color_key_max & 0x00ffffff);
		reg_set(m.bld, G2D_BLD_CK_MIN, bl->color_key_min & 0x00ffffff);
		/* match direction 1: the key is compared with the other (background) layer */
		reg_set(m.bld, G2D_BLD_CK, G2D_BLD_CK_EN | RT_FIELD_PREP(G2D_BLD_CK_DIR_MASK, 1));
	}
	bld_output(&m, d.width, d.height, op->flags & G2D_FLAG_DST_PREMULTIPLIED, false);
	wb_setup(&m, &d);
	return 0;
}

static int compose_rotate(struct g2d_cmdlist *cl, const struct g2d_op *op)
{
	static const uint8_t degree[] = {
		[G2D_ROTATE_0] = 0,
		[G2D_ROTATE_90] = 1,
		[G2D_ROTATE_180] = 2,
		[G2D_ROTATE_270] = 3,
	};
	bool swap = op->rotation == G2D_ROTATE_90 || op->rotation == G2D_ROTATE_270;
	struct g2d_hw_buf s, d;
	uint32_t *core, *rot;
	unsigned int p;
	int ret;

	if ((unsigned int)op->rotation >= RT_ARRAY_SIZE(degree)) {
		return -EINVAL;
	}
	ret = g2d_hw_buf_init(&s, &op->src, &op->src_rect);
	if (ret == 0) {
		ret = g2d_hw_buf_init(&d, &op->dst, &op->dst_rect);
	}
	if (ret) {
		return ret;
	}
	/* a pure move: same format, no scaling */
	if (s.fmt != d.fmt || d.width != (swap ? s.height : s.width) ||
	    d.height != (swap ? s.width : s.height)) {
		LOG_D("rotation needs the same format and the rotated size");
		return -EINVAL;
	}
	for (p = 0; p < s.fmt->planes; p++) {
		if ((s.addr[p] | d.addr[p]) & 3U || d.pitch[p] & 7U) {
			LOG_D("rotation needs 4 byte addresses and 8 byte destination pitch");
			return -EINVAL;
		}
	}

	core = g2d_cmdlist_block(cl, G2D_CORE_CTRL, G2D_CORE_CTRL_SIZE);
	rot = g2d_cmdlist_block(cl, G2D_ROT, G2D_ROT_SIZE);
	if (!core || !rot) {
		return -ENOMEM;
	}

	reg_set(core, 0, G2D_CORE_CTRL_ROTATE);
	reg_set(rot, G2D_ROT_CTRL,
		RT_FIELD_PREP(G2D_ROT_CTRL_MODE_MASK, ROT_MODE_NORMAL) |
			RT_FIELD_PREP(G2D_ROT_CTRL_DEGREE_MASK, degree[op->rotation]) |
			((op->flags & G2D_FLIP_V) ? G2D_ROT_CTRL_VFLIP : 0) |
			((op->flags & G2D_FLIP_H) ? G2D_ROT_CTRL_HFLIP : 0));
	reg_set(rot, G2D_ROT_IN_FORMAT, s.fmt->hw);
	reg_set(rot, G2D_ROT_IN_SIZE, size_reg(s.width, s.height));
	reg_set(rot, G2D_ROT_OUT_SIZE, size_reg(d.width, d.height));
	for (p = 0; p < s.fmt->planes; p++) {
		reg_set(rot, G2D_ROT_IN_PITCH(p), s.pitch[p]);
		reg_set(rot, G2D_ROT_IN_ADDR(p), s.addr[p]);
		reg_set(rot, G2D_ROT_OUT_PITCH(p), d.pitch[p]);
		reg_set(rot, G2D_ROT_OUT_ADDR(p), d.addr[p]);
	}
	return 0;
}

int g2d_compose(struct g2d_cmdlist *cl, const struct g2d_op *op)
{
	const struct g2d_fmt_info *dst_fmt = g2d_fmt_get(op->dst.format);

	/* the write back path produces RGB only */
	if (dst_fmt == NULL || dst_fmt->yuv) {
		LOG_D("destination format %d cannot be written", op->dst.format);
		return -EINVAL;
	}

	switch (op->type) {
	case G2D_OP_FILL:
		return compose_fill(cl, op);
	case G2D_OP_BLIT:
		if (op->rotation == G2D_ROTATE_0 && !(op->flags & (G2D_FLIP_H | G2D_FLIP_V))) {
			return compose_blit(cl, op);
		}
		return compose_rotate(cl, op);
	case G2D_OP_BLEND:
		return compose_blend(cl, op);
	default:
		return -EINVAL;
	}
}

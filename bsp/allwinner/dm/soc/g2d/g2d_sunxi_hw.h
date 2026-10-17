/*
 * Copyright (c) 2026 Yuzuki Tsuru
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

/* Internal interface of the Allwinner G2D driver: formats, command lists, compose */

#ifndef G2D_SUNXI_HW_H_
#define G2D_SUNXI_HW_H_

#include <stdbool.h>
#include <stdint.h>

#include "g2d.h"

#define G2D_MAX_PLANES		3
#define G2D_VSU_PHASES		32
#define G2D_VSU_COEF_SETS	16
#define G2D_CSC_WORDS		12

/* ---- pixel formats ------------------------------------------------------ */

struct g2d_fmt_info {
	/** value of the format fields of the overlay, write back and rotate registers */
	uint8_t hw;
	uint8_t planes;
	bool yuv;
	/** bytes per sample of each plane (one UV pair counts as one sample) */
	uint8_t bytes[G2D_MAX_PLANES];
	/** log2 of the horizontal and vertical subsampling of each plane */
	uint8_t hshift[G2D_MAX_PLANES];
	uint8_t vshift[G2D_MAX_PLANES];
};

const struct g2d_fmt_info *g2d_fmt_get(enum g2d_format format);

/** A rectangle of a surface as seen by the DMA engines */
struct g2d_hw_buf {
	const struct g2d_fmt_info *fmt;
	/** address of the top-left sample of each plane */
	uint32_t addr[G2D_MAX_PLANES];
	uint32_t pitch[G2D_MAX_PLANES];
	uint16_t width;
	uint16_t height;
};

/** Validate @p rect in @p s and describe it. Returns 0 or -EINVAL. */
int g2d_hw_buf_init(struct g2d_hw_buf *buf, const struct g2d_surface *s,
		    const struct g2d_rect *rect);

/** Whole lines of plane @p p that cover @p rect, for cache maintenance */
int g2d_surface_rect_span(const struct g2d_surface *s, const struct g2d_rect *rect,
			  unsigned int p, void **start, size_t *len);

/* ---- register command list --------------------------------------------- */

/** Memory the hardware reads its commands from: headers first, then the register images */
struct g2d_cmdlist {
	uint8_t *mem;
	size_t size;
	size_t used;
	unsigned int blocks;
};

#define G2D_CMDLIST_MAX_BLOCKS	12
#define G2D_CMDLIST_ALIGN	32

void g2d_cmdlist_init(struct g2d_cmdlist *cl, void *mem, size_t size);

/** Reserve a zeroed register image written to registers @p offset.. by the hardware */
uint32_t *g2d_cmdlist_block(struct g2d_cmdlist *cl, uint32_t offset, size_t bytes);

/** Close the list; returns the length of the header area, 0 when empty */
size_t g2d_cmdlist_finish(struct g2d_cmdlist *cl);

/* ---- compose: operations -> register images ----------------------------- */

/** Which engine runs the command list */
enum g2d_engine {
	G2D_ENGINE_MIXER,
	G2D_ENGINE_ROTATE,
};

/**
 * Build the command list of @p op. Returns 0 or a negative errno when the
 * hardware cannot do it.
 */
int g2d_compose(struct g2d_cmdlist *cl, const struct g2d_op *op);

/* ---- constant tables ---------------------------------------------------- */

extern const uint32_t g2d_vsu_coef_lanczos[G2D_VSU_COEF_SETS][G2D_VSU_PHASES];
extern const uint32_t g2d_vsu_coef_linear[G2D_VSU_PHASES];
extern const uint32_t g2d_csc_yuv2rgb_601[2][G2D_CSC_WORDS];
extern const uint32_t g2d_csc_yuv2rgb_709[2][G2D_CSC_WORDS];

#endif /* G2D_SUNXI_HW_H_ */

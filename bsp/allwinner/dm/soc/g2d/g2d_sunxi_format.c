/*
 * Copyright (c) 2026 Yuzuki Tsuru
 *
 * SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#include <errno.h>
#include <string.h>

#define DBG_TAG "g2d"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>
#include <rtthread.h>

#include "g2d_sunxi_hw.h"


#define MAX_SIZE	8192

#define RGB(_hw, _bytes) \
	{ .hw = (_hw), .planes = 1, .bytes = { (_bytes) } }

static const struct g2d_fmt_info g2d_formats[G2D_PIXFMT_MAX] = {
	[G2D_PIXFMT_ARGB8888] = RGB(0x00, 4),
	[G2D_PIXFMT_ABGR8888] = RGB(0x01, 4),
	[G2D_PIXFMT_RGBA8888] = RGB(0x02, 4),
	[G2D_PIXFMT_BGRA8888] = RGB(0x03, 4),
	[G2D_PIXFMT_XRGB8888] = RGB(0x04, 4),
	[G2D_PIXFMT_XBGR8888] = RGB(0x05, 4),
	[G2D_PIXFMT_RGB888] = RGB(0x08, 3),
	[G2D_PIXFMT_BGR888] = RGB(0x09, 3),
	[G2D_PIXFMT_RGB565] = RGB(0x0a, 2),
	[G2D_PIXFMT_BGR565] = RGB(0x0b, 2),
	[G2D_PIXFMT_ARGB4444] = RGB(0x0c, 2),
	[G2D_PIXFMT_ARGB1555] = RGB(0x10, 2),
	[G2D_PIXFMT_NV12] = {
		.hw = 0x28, .planes = 2, .yuv = true,
		.bytes = { 1, 2 },
		.hshift = { 0, 1 },
		.vshift = { 0, 1 },
	},
	[G2D_PIXFMT_NV21] = {
		.hw = 0x29, .planes = 2, .yuv = true,
		.bytes = { 1, 2 },
		.hshift = { 0, 1 },
		.vshift = { 0, 1 },
	},
	[G2D_PIXFMT_I420] = {
		.hw = 0x2a, .planes = 3, .yuv = true,
		.bytes = { 1, 1, 1 },
		.hshift = { 0, 1, 1 },
		.vshift = { 0, 1, 1 },
	},
	[G2D_PIXFMT_YUYV] = {
		.hw = 0x20, .planes = 1, .yuv = true,
		.bytes = { 2 },
	},
};

const struct g2d_fmt_info *g2d_fmt_get(enum g2d_format format)
{
	if ((unsigned int)format >= G2D_PIXFMT_MAX) {
		return NULL;
	}
	return &g2d_formats[format];
}

/* bytes of one line of plane @p p holding @p width luma pixels */
static uint32_t plane_line_bytes(const struct g2d_fmt_info *fmt, unsigned int p, uint32_t width)
{
	uint32_t samples = (width + RT_BIT(fmt->hshift[p]) - 1) >> fmt->hshift[p];

	return samples * fmt->bytes[p];
}

static uint32_t plane_pitch(const struct g2d_surface *s, const struct g2d_fmt_info *fmt,
			    unsigned int p)
{
	return s->pitch[p] ? s->pitch[p] : plane_line_bytes(fmt, p, s->width);
}

int g2d_hw_buf_init(struct g2d_hw_buf *buf, const struct g2d_surface *s,
		    const struct g2d_rect *rect)
{
	const struct g2d_fmt_info *fmt = g2d_fmt_get(s->format);
	unsigned int p;

	if (fmt == NULL || s->width == 0 || s->height == 0 || s->width > MAX_SIZE ||
	    s->height > MAX_SIZE) {
		LOG_D("bad surface: format %d, %ux%u", s->format, s->width, s->height);
		return -EINVAL;
	}
	if (rect->width == 0 || rect->height == 0 || rect->x + rect->width > s->width ||
	    rect->y + rect->height > s->height) {
		LOG_D("rect %u,%u %ux%u outside the %ux%u surface", rect->x, rect->y, rect->width,
			rect->height, s->width, s->height);
		return -EINVAL;
	}
	/* subsampled chroma: the rectangle must not split a chroma sample */
	if ((fmt->yuv && ((rect->x | rect->width) & 1U)) ||
	    (fmt->vshift[1] && ((rect->y | rect->height) & 1U))) {
		LOG_D("rect splits a chroma sample");
		return -EINVAL;
	}

	buf->fmt = fmt;
	buf->width = rect->width;
	buf->height = rect->height;
	memset(buf->addr, 0, sizeof(buf->addr));
	memset(buf->pitch, 0, sizeof(buf->pitch));

	for (p = 0; p < fmt->planes; p++) {
		uint32_t pitch = plane_pitch(s, fmt, p);

		if (s->plane[p] == NULL || pitch < plane_line_bytes(fmt, p, s->width)) {
			LOG_D("plane %u: address %p, pitch %u", p, s->plane[p], pitch);
			return -EINVAL;
		}
		buf->pitch[p] = pitch;
		buf->addr[p] = (uint32_t)(uintptr_t)s->plane[p] +
			       (rect->y >> fmt->vshift[p]) * pitch +
			       (rect->x >> fmt->hshift[p]) * fmt->bytes[p];
	}
	return 0;
}

int g2d_surface_rect_span(const struct g2d_surface *s, const struct g2d_rect *rect,
			  unsigned int p, void **start, size_t *len)
{
	const struct g2d_fmt_info *fmt = g2d_fmt_get(s->format);
	uint32_t pitch, first, last;

	if (fmt == NULL || p >= fmt->planes || s->plane[p] == NULL) {
		return -EINVAL;
	}
	pitch = plane_pitch(s, fmt, p);
	first = rect->y >> fmt->vshift[p];
	last = (rect->y + rect->height + RT_BIT(fmt->vshift[p]) - 1) >> fmt->vshift[p];
	*start = (uint8_t *)s->plane[p] + (size_t)first * pitch;
	*len = (size_t)(last - first) * pitch;
	return 0;
}

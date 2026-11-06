/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API of 2D graphics accelerators (G2D)
 *
 * The G2D moves and combines rectangles of pixels between memory
 * buffers without the CPU: solid fills, copies with pixel format
 * conversion, scaling, rotation and flipping, and alpha blending of two
 * surfaces. Operations are queued, run asynchronously and complete in
 * submission order.
 *
 * The caller owns the buffers. The driver cleans the data cache of the
 * source buffers before an operation and invalidates the destination
 * afterwards, unless @ref G2D_FLAG_NO_CACHE_OPS is set.
 */

#ifndef __G2D_H__
#define __G2D_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <rtthread.h>
#include <drivers/misc.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief G2D interface
 * @defgroup g2d_interface G2D interface
 * @ingroup io_interfaces
 * @{
 */

/** Pixel formats. Names list the components from the MSB, as stored in a LE word. */
enum g2d_format {
	G2D_PIXFMT_ARGB8888,
	G2D_PIXFMT_ABGR8888,
	G2D_PIXFMT_RGBA8888,
	G2D_PIXFMT_BGRA8888,
	G2D_PIXFMT_XRGB8888,
	G2D_PIXFMT_XBGR8888,
	G2D_PIXFMT_RGB888,
	G2D_PIXFMT_BGR888,
	G2D_PIXFMT_RGB565,
	G2D_PIXFMT_BGR565,
	G2D_PIXFMT_ARGB4444,
	G2D_PIXFMT_ARGB1555,
	/** YUV 4:2:0, plane 0 Y, plane 1 interleaved UV. Source only. */
	G2D_PIXFMT_NV12,
	/** YUV 4:2:0, plane 0 Y, plane 1 interleaved VU. Source only. */
	G2D_PIXFMT_NV21,
	/** YUV 4:2:0, three planes Y, U, V. Source only. */
	G2D_PIXFMT_I420,
	/** YUV 4:2:2 packed Y0 U Y1 V. Source only. */
	G2D_PIXFMT_YUYV,
	G2D_PIXFMT_MAX,
};

/** Rotation, applied before the flips of @ref G2D_FLIP_H / @ref G2D_FLIP_V. */
enum g2d_rotation {
	G2D_ROTATE_0,
	G2D_ROTATE_90,
	G2D_ROTATE_180,
	G2D_ROTATE_270,
};

/** Porter-Duff composition. "Source" is the foreground, "destination" the background. */
enum g2d_blend_mode {
	G2D_BLEND_CLEAR,
	G2D_BLEND_SRC,
	G2D_BLEND_DST,
	G2D_BLEND_SRC_OVER,
	G2D_BLEND_DST_OVER,
	G2D_BLEND_SRC_IN,
	G2D_BLEND_DST_IN,
	G2D_BLEND_SRC_OUT,
	G2D_BLEND_DST_OUT,
	G2D_BLEND_SRC_ATOP,
	G2D_BLEND_DST_ATOP,
	G2D_BLEND_XOR,
};

/** How the alpha of a layer is taken. */
enum g2d_alpha_mode {
	/** use the alpha channel of the pixels */
	G2D_ALPHA_PIXEL,
	/** use the layer alpha only */
	G2D_ALPHA_GLOBAL,
	/** pixel alpha multiplied by the layer alpha */
	G2D_ALPHA_MIXED,
};

/** @name Operation flags
 * @{
 */
/** Flip horizontally (after the rotation) */
#define G2D_FLIP_H		RT_BIT(0)
/** Flip vertically (after the rotation) */
#define G2D_FLIP_V		RT_BIT(1)
/** The pixels of the source are premultiplied by their alpha */
#define G2D_FLAG_SRC_PREMULTIPLIED	RT_BIT(2)
/** The pixels of the destination are premultiplied by their alpha */
#define G2D_FLAG_DST_PREMULTIPLIED	RT_BIT(3)
/** Do not clean/invalidate the data cache around the operation */
#define G2D_FLAG_NO_CACHE_OPS	RT_BIT(4)
/** YCbCr sources use the full 0..255 range (default: limited, 16..235) */
#define G2D_FLAG_YUV_FULL_RANGE	RT_BIT(5)
/** YCbCr sources use the BT.709 matrix (default: BT.601) */
#define G2D_FLAG_YUV_BT709	RT_BIT(6)
/** @} */

/** Rectangle in pixels */
struct g2d_rect {
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
};

/** A memory buffer holding pixels */
struct g2d_surface {
	enum g2d_format format;
	/** size of the buffer in pixels */
	uint16_t width;
	uint16_t height;
	/** plane base addresses; planar and semi-planar YUV use more than one */
	void *plane[3];
	/** line pitch of each plane in bytes (0: tightly packed) */
	uint32_t pitch[3];
};

struct g2d_op;

/**
 * @brief Completion callback
 *
 * Called from the driver thread once the hardware finished the operation or
 * it failed. Do not block in it.
 *
 * @param op The operation that completed
 * @param status 0 on success, a negative errno otherwise
 * @param user_data @ref g2d_op::user_data
 */
typedef void (*g2d_callback_t)(const struct g2d_op *op, int status, void *user_data);

/** Operation types */
enum g2d_op_type {
	/** fill @ref g2d_op::dst_rect with @ref g2d_op::color */
	G2D_OP_FILL,
	/**
	 * copy @ref g2d_op::src_rect of src to dst_rect of dst; converts the pixel format,
	 * scales when the rectangle sizes differ, and rotates/flips
	 */
	G2D_OP_BLIT,
	/**
	 * compose src_rect of src (foreground, scaled to the size of dst_rect when
	 * they differ) with bg_rect of bg (background, same size as dst_rect) and
	 * write the result to dst_rect of dst; dst may be bg
	 */
	G2D_OP_BLEND,
};

/** Blend parameters of @ref G2D_OP_BLEND */
struct g2d_blend {
	enum g2d_blend_mode mode;
	enum g2d_alpha_mode fg_alpha_mode;
	/** foreground layer alpha (0..255), used by the global and mixed modes */
	uint8_t fg_alpha;
	enum g2d_alpha_mode bg_alpha_mode;
	uint8_t bg_alpha;
	/** compare the destination (bg) pixels with the colour key range, in ARGB8888 */
	bool color_key;
	uint32_t color_key_min;
	uint32_t color_key_max;
};

/** One queued operation */
struct g2d_op {
	enum g2d_op_type type;
	uint32_t flags;
	/** @ref G2D_OP_FILL colour in ARGB8888 */
	uint32_t color;
	struct g2d_surface dst;
	struct g2d_rect dst_rect;
	/** @ref G2D_OP_BLIT and @ref G2D_OP_BLEND source (foreground) */
	struct g2d_surface src;
	struct g2d_rect src_rect;
	/** @ref G2D_OP_BLIT: rotation and flips */
	enum g2d_rotation rotation;
	/** @ref G2D_OP_BLEND background, same size as dst_rect */
	struct g2d_surface bg;
	struct g2d_rect bg_rect;
	struct g2d_blend blend;
	/** optional, called when the operation is done */
	g2d_callback_t callback;
	void *user_data;
};

/** Capabilities of a G2D device */
struct g2d_capabilities {
	/** bit mask of RT_BIT(enum g2d_format) the device reads */
	uint32_t src_formats;
	/** bit mask of RT_BIT(enum g2d_format) the device writes */
	uint32_t dst_formats;
	/** bit mask of RT_BIT(enum g2d_op_type) */
	uint32_t ops;
	uint16_t max_width;
	uint16_t max_height;
	/** the rotate engine needs this alignment of the plane addresses and pitches */
	uint8_t rotate_addr_align;
	uint8_t rotate_pitch_align;
	/** operations that can wait in the queue */
	uint8_t queue_depth;
};

/** @brief Queue an operation (copied); -EINVAL unsupported, -ENOMEM queue full */
int g2d_submit(const struct g2d_op *op);

/** @brief Get the capabilities of the device */
int g2d_get_capabilities(struct g2d_capabilities *caps);

/** @brief Whether the G2D is initialised */
rt_bool_t g2d_ready(void);

/**
 * @brief Run an operation and wait for it
 *
 * Wraps @ref g2d_submit. Any callback of @p op is called as well.
 *
 * @param timeout ticks to wait for the operation to complete (RT_WAITING_FOREVER: no limit)
 * @retval 0 done
 * @retval -EAGAIN not done in time (the operation may still run)
 * @retval negative errno from the submission or from the hardware
 */
int g2d_run(const struct g2d_op *op, rt_int32_t timeout);

/** @brief Fill a rectangle with an ARGB8888 colour, synchronously */
int g2d_fill(const struct g2d_surface *dst,
	     const struct g2d_rect *dst_rect, uint32_t color);

/**
 * @brief Copy, convert, scale and rotate a rectangle, synchronously
 *
 * The rectangle sizes of @p src_rect and @p dst_rect select the scaling; for a
 * 90/270 degree rotation the destination size is the rotated source size.
 */
int g2d_blit(const struct g2d_surface *src,
	     const struct g2d_rect *src_rect, const struct g2d_surface *dst,
	     const struct g2d_rect *dst_rect, enum g2d_rotation rotation, uint32_t flags);

/** @brief Compose @p fg over @p bg into @p dst, synchronously */
int g2d_blend(const struct g2d_surface *fg,
	      const struct g2d_rect *fg_rect, const struct g2d_surface *bg,
	      const struct g2d_rect *bg_rect, const struct g2d_surface *dst,
	      const struct g2d_rect *dst_rect, const struct g2d_blend *blend, uint32_t flags);

/** @brief Hardware time of the last operation in 1/100 us: command list start to end interrupt, no cache or scheduling time */
uint32_t g2d_last_hw_time_x100us(void);

/** @brief Bandwidth limit inside the G2D (0: off); the memory bus has its own per master limit */
void g2d_set_ddr_limit(uint32_t level);
uint32_t g2d_get_ddr_limit(void);

/** @brief Module clock of the G2D: set a rate (returns the rate set, 0 on failure) and read it */
uint32_t g2d_set_clock_rate(uint32_t hz);
uint32_t g2d_get_clock_rate(void);

/** @brief Bytes per pixel of the first plane of a format (0: planar/unsupported) */
static inline unsigned int g2d_format_bytes_per_pixel(enum g2d_format format)
{
	switch (format) {
	case G2D_PIXFMT_ARGB8888:
	case G2D_PIXFMT_ABGR8888:
	case G2D_PIXFMT_RGBA8888:
	case G2D_PIXFMT_BGRA8888:
	case G2D_PIXFMT_XRGB8888:
	case G2D_PIXFMT_XBGR8888:
		return 4;
	case G2D_PIXFMT_RGB888:
	case G2D_PIXFMT_BGR888:
		return 3;
	case G2D_PIXFMT_RGB565:
	case G2D_PIXFMT_BGR565:
	case G2D_PIXFMT_ARGB4444:
	case G2D_PIXFMT_ARGB1555:
	case G2D_PIXFMT_YUYV:
		return 2;
	default:
		return 0;
	}
}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __G2D_H__ */

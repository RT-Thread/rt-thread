/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_DISPLAY_COMMON_H
#define HPM_DISPLAY_COMMON_H

#include "hpm_common.h"

/**
 * @brief Display_common driver APIs
 * @defgroup Display_common_interface Display_common driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief display alphablend mode
 */
typedef enum display_alphablend_mode {
    display_alphablend_mode_clear = 0,
    display_alphablend_mode_src = 1,
    display_alphablend_mode_dst = 2,
    display_alphablend_mode_src_over = 3,
    display_alphablend_mode_dst_over = 4,
    display_alphablend_mode_src_in = 5,
    display_alphablend_mode_dst_in = 6,
    display_alphablend_mode_src_out = 7,
    display_alphablend_mode_dst_out = 8,
    display_alphablend_mode_src_at_top = 9,
    display_alphablend_mode_dst_at_top = 10,
    display_alphablend_mode_xor = 11,
    display_alphablend_mode_plus = 12,
    display_alphablend_mode_modulate = 13,
    display_alphablend_mode_src_org = 14,
    display_alphablend_mode_dst_org = 15,
} display_alphablend_mode_t;

/**
 * @brief display pixel format
 */
typedef enum display_pixel_format {
    display_pixel_format_argb8888,
    display_pixel_format_rgb565,
    display_pixel_format_rgb555,
    display_pixel_format_rgb444,
    display_pixel_format_gbr422,
    display_pixel_format_yuv422,
    display_pixel_format_ycbcr422,
    display_pixel_format_y8,
    display_pixel_format_raw8,
} display_pixel_format_t;

/**
 * @brief display data byte order
 */
typedef enum display_byteorder {
    display_byteorder_a3a2a1a0 = 0,
    display_byteorder_a2a3a0a1 = 1,
    display_byteorder_a1a0a3a2 = 2,
    display_byteorder_a0a1a2a3 = 3,
} display_byteorder_t;

/**
 * @brief display yuv format
 */
typedef enum display_yuv_format {
    display_yuv_mode_422_u1y1v1y2 = 0,
    display_yuv_mode_422_v1y1u1y2,
    display_yuv_mode_422_y1u1y2v1,
    display_yuv_mode_422_y1v1y2u1,
} display_yuv_format_t;

/**
 * @brief display data 32 bits argb
 */
typedef union display_color_32b {
    uint32_t u;
    struct {
        uint8_t b;
        uint8_t g;
        uint8_t r;
        uint8_t alpha;
    };
} display_color_32b_t;

/**
 * @brief display data alpha value usage option
 */
typedef enum display_alpha_op {
    display_alpha_op_invalid = 0,
    display_alpha_op_override = 1,
    display_alpha_op_scale = 2,
} display_alpha_op_t;

/**
 * @brief display data alphablend option
 */
typedef struct dispaly_alphablend_option {
    uint8_t dst_alpha;
    uint8_t src_alpha;
    display_alpha_op_t dst_alpha_op;
    display_alpha_op_t src_alpha_op;
    display_alphablend_mode_t mode;
} display_alphablend_option_t;

/**
 * @brief display yuv to rgb format conversion coefficient
 */
typedef struct dispaly_yuv2rgb_coef {
    uint16_t c0;
    uint16_t c1;
    uint16_t c2;
    uint16_t c3;
    uint16_t c4;
    uint16_t uv_offset;
    uint16_t y_offset;
} display_yuv2rgb_coef_t;

/**
 * @brief display yuv to rgb format conversion config
 */
typedef struct display_yuv2rgb_config {
    bool enable;
    bool ycbcr_mode;
    display_yuv2rgb_coef_t yuv2rgb_coef;
} display_yuv2rgb_config_t;

/**
 * @brief display rgb to yuv format conversion config
 */
typedef struct display_rgb2yuv_config {
    bool enable;
    bool ycbcr_mode;
    uint16_t c0;
    uint16_t c1;
    uint16_t c2;
    uint16_t c3;
    uint16_t c4;
    uint16_t c5;
    uint16_t c6;
    uint16_t c7;
    uint16_t c8;
    uint16_t uv_offset;
    uint16_t y_offset;
} display_rgb2yuv_config_t;

typedef enum display_buf_format {
    display_buf_format_argb8888, /*!< memory layout in byte(low->high): b0[7:0], g0[7:0], r0[7:0], a0[7:0], b1[7:1], g1[7:1], r1[7:0], a1[7:0], ... */
    display_buf_format_bgra8888, /*!< memory layout in byte(low->high): a0[7:0], r0[7:0], g0[7:0], b0[7:0], a1[7:1], r1[7:1], g1[7:0], b1[7:0], ... */
    display_buf_format_rgb565, /*!< memory layout in byte(low->high): g0[2:0]:b0[4:0], r0[4:0]:g0[5:3], g1[2:0]:b1[4:0], r1[4:0]:g1[5:3], ... */
    display_buf_format_rgb565_swap, /*!< memory layout in byte(low->high): r0[4:0]:g0[5:3], g0[2:0]:b0[4:0], r2[4:0]:g2[5:3], g1[2:0]:b1[4:0],  ... */
    display_buf_format_yuyv, /*!< memory layout in byte(low->high): y0, u0, y1, v0, y2, u2, y3, v2, ... */
    display_buf_format_uyvy, /*!< memory layout in byte(low->high): u0, y0, v0, y1, u2, y2, v2, y3, ... */
    display_buf_format_y8, /*!< memory layout in byte(low->high): y0, y1, y2, y3, y4, y5, ... */
    display_buf_format_max,
} display_buf_format_t;

typedef struct display_buf {
    void *buf; /*!< point pixel memory */
    uint16_t width; /*!< width in pixel */
    uint16_t height; /*!< height in pixel */
    uint32_t stride; /*!< stride each line, in byte */
    display_buf_format_t format;
    struct {
        display_alpha_op_t op;
        uint8_t val;
    } alpha;
} display_buf_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Display get pixel size in bit
 *
 * @param [in] format display_pixel_format_t
 *
 * @retval pixel size in bit
 */
static inline
    uint8_t display_get_pixel_size_in_bit(display_pixel_format_t format)
{
    switch (format) {
    case display_pixel_format_argb8888:
        return 32;
    case display_pixel_format_rgb565:
        return 16;
    case display_pixel_format_yuv422:
        return 16;
    case display_pixel_format_ycbcr422:
        return 16;
    case display_pixel_format_y8:
        return 8;
    case display_pixel_format_raw8:
        return 8;
    default:
        return 0;
    }
}

/**
 * @brief Check whether the pixel data is yuv format
 *
 * @param [in] format display_pixel_format_t
 *
 * @retval bool: true or false
 */
static inline bool display_pixel_format_is_yuv_format(display_pixel_format_t format)
{
    switch (format) {
    case display_pixel_format_yuv422:
        return true;
    case display_pixel_format_ycbcr422:
        return true;
    default:
        return false;
    }
}

/**
 * @brief Display get pixel size in byte
 *
 * @param [in] format display_pixel_format_t
 *
 * @retval pixel size in byte
 */
static inline
    uint8_t display_get_pixel_size_in_byte(display_pixel_format_t format)
{
    return display_get_pixel_size_in_bit(format) >> 3;
}

/**
 * @brief Display get pitch length in byte
 *
 * @param [in] format display_pixel_format_t
 * @param [in] width_in_pixel pixel width
 *
 * @retval pitch length in byte
 */
static inline
    uint32_t display_get_pitch_length_in_byte(display_pixel_format_t format,
                                            uint32_t width_in_pixel)
{
    return width_in_pixel * (display_get_pixel_size_in_bit(format) >> 3);
}

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif
#endif /* HPM_DISPLAY_COMMON_H */

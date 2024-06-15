/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_pdma_drv.h"

#define PDMA_SCALE_FRAC_BITS 12
/* x_offset might need to be adjusted when scaling YUV format */
#define PDMA_YUV_SCALE_DEFAULT_X_OFFSET (0x800)

void pdma_set_block_size(PDMA_Type *ptr, pdma_blocksize_t size)
{
    ptr->CTRL = (ptr->CTRL & ~PDMA_CTRL_BS16_MASK)
        | ((size == pdma_blocksize_16x16) ? PDMA_CTRL_BS16_MASK : 0);
}

void pdma_enable_plane(PDMA_Type *ptr, pdma_plane_t enable_plane, bool enable)
{
    uint32_t mask;
    switch (enable_plane) {
    case pdma_plane_both:
        mask = (PDMA_CTRL_P0_EN_MASK | PDMA_CTRL_P1_EN_MASK);
        break;
    case pdma_plane_src:
        mask = PDMA_CTRL_P0_EN_MASK;
        break;
    case pdma_plane_dst:
        mask = PDMA_CTRL_P1_EN_MASK;
        break;
    default:
        mask = 0;
        break;
    }
    if (!mask) {
        return;
    }
    if (enable) {
        ptr->CTRL |= mask;
    } else {
        ptr->CTRL &= ~mask;
    }
}

void pdma_enable_irq(PDMA_Type *ptr, uint32_t mask, bool enable)
{
    mask &= PDMA_CTRL_AXIERR_IRQ_EN_MASK | PDMA_CTRL_PDMA_DONE_IRQ_EN_MASK;
    if (enable) {
        ptr->CTRL |= mask | PDMA_CTRL_IRQ_EN_MASK;
    } else {
        ptr->CTRL &= ~mask;
    }
}

void pdma_get_default_config(PDMA_Type *ptr, pdma_config_t *config, display_pixel_format_t pixel_format)
{
    (void) ptr;
    config->block_size = pdma_blocksize_16x16;
    config->enable_plane = pdma_plane_src;

    if (display_pixel_format_is_yuv_format(pixel_format)) {
        if (pixel_format == display_pixel_format_ycbcr422) {
            config->byteorder = display_byteorder_a2a3a0a1;
        } else {
            config->byteorder = display_byteorder_a0a1a2a3;
        }
    } else {
        config->byteorder = display_byteorder_a3a2a1a0;
    }
}

void pdma_get_default_plane_config(PDMA_Type *ptr, pdma_plane_config_t *config, display_pixel_format_t pixel_format)
{
    (void) ptr;
    config->swap_byte3_byte1 = false;
    config->byteorder = display_byteorder_a3a2a1a0;
    config->use_background_as_clear = true;
    config->flip = pdma_flip_none;
    config->rotate = pdma_rotate_0_degree;
    config->x_dec = pdma_decimation_by_1;
    config->y_dec = pdma_decimation_by_1;
    config->byte_swap = false;
    config->pixel_format = pixel_format;
    config->buffer = 0;
    config->background = 0xFFFFFFFF;
    config->x_scale = PDMA_MAKE_SCALE_SET(1, 0);
    config->y_scale = PDMA_MAKE_SCALE_SET(1, 0);
    config->x_offset = 0;
    config->y_offset = 0;
    config->colorkey_high = 0;
    config->colorkey_low = 0xFFFFFF;
    config->width = 0;
    config->height = 0;
    config->pitch = 0;

    switch (pixel_format) {
    case display_pixel_format_yuv422:
        config->ycbcr_mode = false;
        config->bypass_colorspace_conversion = false;
        break;
    case display_pixel_format_ycbcr422:
        config->ycbcr_mode = true;
        config->bypass_colorspace_conversion = false;
        break;
    default:
        config->ycbcr_mode = false;
        config->bypass_colorspace_conversion = true;
        break;
    }
}

void pdma_get_default_yuv2rgb_coef_config(PDMA_Type *ptr, display_yuv2rgb_coef_t *yuv2rgb_coef, display_pixel_format_t source_format)
{
    (void) ptr;
    /* Two plane share one YUV2RGB_COEF, not support one plane format is yuv422 and another is ycbcr422 */

    switch (source_format) {
    case display_pixel_format_yuv422:
        yuv2rgb_coef->c0 = 0x100;
        yuv2rgb_coef->uv_offset = 0;
        yuv2rgb_coef->y_offset = 0;
        yuv2rgb_coef->c1 = 0x123;
        yuv2rgb_coef->c2 = 0x76B;
        yuv2rgb_coef->c3 = 0x79C;
        yuv2rgb_coef->c4 = 0x208;
        break;
    case display_pixel_format_ycbcr422:
        yuv2rgb_coef->c0 = 0x12A;
        yuv2rgb_coef->uv_offset = 0x180;
        yuv2rgb_coef->y_offset = 0x1F0;
        yuv2rgb_coef->c1 = 0x198;
        yuv2rgb_coef->c2 = 0x730;
        yuv2rgb_coef->c3 = 0x79C;
        yuv2rgb_coef->c4 = 0x204;
        break;
    default:
        yuv2rgb_coef->c0 = 0;
        yuv2rgb_coef->uv_offset = 0;
        yuv2rgb_coef->y_offset = 0;
        yuv2rgb_coef->c1 = 0;
        yuv2rgb_coef->c2 = 0;
        yuv2rgb_coef->c3 = 0;
        yuv2rgb_coef->c4 = 0;
        break;
    }
}

void pdma_get_default_output_config(PDMA_Type *ptr, pdma_output_config_t *config, display_pixel_format_t pixel_format)
{
    (void) ptr;
    uint8_t i;
    config->alphablend.dst_alpha = 0x0;
    config->alphablend.src_alpha = 0x0;
    config->alphablend.src_alpha_op = display_alpha_op_invalid;
    config->alphablend.dst_alpha_op = display_alpha_op_invalid;
    config->alphablend.mode = display_alphablend_mode_plus;
    config->pixel_format = pixel_format;
    config->buffer = 0;
    for (i = 0; i < PDMA_SOC_PS_MAX_COUNT; i++) {
        config->plane[i].x = 0;
        config->plane[i].y = 0;
        config->plane[i].width = 0;
        config->plane[i].height = 0;
    }
    config->width = 0;
    config->height = 0;
    config->pitch = 0;

    switch (pixel_format) {
    case display_pixel_format_yuv422:
        config->rgb2yuv_config.enable = true;
        config->rgb2yuv_config.ycbcr_mode = false;
        config->rgb2yuv_config.c0 = 0x4D;
        config->rgb2yuv_config.uv_offset = 0;
        config->rgb2yuv_config.y_offset = 0;
        config->rgb2yuv_config.c1 = 0x96;
        config->rgb2yuv_config.c2 = 0x1D;
        config->rgb2yuv_config.c3 = 0x7DA;
        config->rgb2yuv_config.c4 = 0x7B6;
        config->rgb2yuv_config.c5 = 0x70;
        config->rgb2yuv_config.c6 = 0x9D;
        config->rgb2yuv_config.c7 = 0x77C;
        config->rgb2yuv_config.c8 = 0x7E6;
        break;
    case display_pixel_format_ycbcr422:
        config->rgb2yuv_config.enable = true;
        config->rgb2yuv_config.ycbcr_mode = true;
        config->rgb2yuv_config.c0 = 0x42;
        config->rgb2yuv_config.uv_offset = 0x80;
        config->rgb2yuv_config.y_offset = 0x10;
        config->rgb2yuv_config.c1 = 0x81;
        config->rgb2yuv_config.c2 = 0x19;
        config->rgb2yuv_config.c3 = 0x7DA;
        config->rgb2yuv_config.c4 = 0x7B5;
        config->rgb2yuv_config.c5 = 0x70;
        config->rgb2yuv_config.c6 = 0x70;
        config->rgb2yuv_config.c7 = 0x7A2;
        config->rgb2yuv_config.c8 = 0x7EE;
        break;
    default:
        config->rgb2yuv_config.enable = false;
        config->rgb2yuv_config.ycbcr_mode = false;
        config->rgb2yuv_config.c0 = 0;
        config->rgb2yuv_config.uv_offset = 0;
        config->rgb2yuv_config.y_offset = 0;
        config->rgb2yuv_config.c1 = 0;
        config->rgb2yuv_config.c2 = 0;
        config->rgb2yuv_config.c3 = 0;
        config->rgb2yuv_config.c4 = 0;
        config->rgb2yuv_config.c5 = 0;
        config->rgb2yuv_config.c6 = 0;
        config->rgb2yuv_config.c7 = 0;
        config->rgb2yuv_config.c8 = 0;
        break;
    }
}

void pdma_stop(PDMA_Type *ptr)
{
    ptr->CTRL &= ~PDMA_CTRL_PDMA_EN_MASK;
    pdma_software_reset(ptr);
    ptr->STAT = 0x21F;
}

void pdma_init(PDMA_Type *ptr, pdma_config_t *config)
{
    uint32_t mask;
    pdma_stop(ptr);
    switch (config->enable_plane) {
    case pdma_plane_both:
        mask = (PDMA_CTRL_P0_EN_MASK | PDMA_CTRL_P1_EN_MASK);
        break;
    case pdma_plane_dst:
        mask = PDMA_CTRL_P1_EN_MASK;
        break;
    case pdma_plane_src:
        mask = PDMA_CTRL_P0_EN_MASK;
        break;
    default:
        mask = 0;
        break;
    }
#if defined(PDMA_SOC_SUPPORT_BS16) && (PDMA_SOC_SUPPORT_BS16 == 1)
    if (config->block_size == pdma_blocksize_16x16) {
        mask |= PDMA_CTRL_BS16_MASK;
    }
#endif

    ptr->CTRL = PDMA_CTRL_PACK_DIR_SET(config->byteorder) | mask;
}

static uint32_t pdma_pixel_format(display_pixel_format_t display_format, bool is_out_plane)
{
    switch (display_format) {
    case display_pixel_format_rgb565:
        return 0xE;
    case display_pixel_format_argb8888:
        return 0;
    case display_pixel_format_yuv422:
        return 0x13;
    case display_pixel_format_ycbcr422:
        return is_out_plane ? 0x12 : 0x13;
    default:
        return 0;
    }
}

void pdma_config_planes(PDMA_Type *ptr, void *plane_src_config, void *plane_dst_config, void *yuv2rgb_coef)
{
    uint32_t pitch;
    uint32_t format;

    assert((plane_src_config != NULL) || (plane_dst_config != NULL));

    pdma_plane_config_t *plane_src = (pdma_plane_config_t *)plane_src_config;
    pdma_plane_config_t *plane_dst = (pdma_plane_config_t *)plane_dst_config;
    display_yuv2rgb_coef_t *yuv2rgb = (display_yuv2rgb_coef_t *)yuv2rgb_coef;

    if (plane_src != NULL) {
        assert((plane_src->bypass_colorspace_conversion) || (yuv2rgb != NULL));
    }
    if (plane_dst != NULL) {
        assert((plane_dst->bypass_colorspace_conversion) || (yuv2rgb != NULL));
    }
    if ((plane_src != NULL) && (plane_dst != NULL)) {
        assert(!(display_pixel_format_is_yuv_format(plane_src->pixel_format) && display_pixel_format_is_yuv_format(plane_dst->pixel_format))
                || (plane_src->pixel_format == plane_dst->pixel_format));
    }

    if (plane_src != NULL) {
        if (plane_src->pitch == 0) {
            pitch = display_get_pitch_length_in_byte(plane_src->pixel_format, plane_src->width);
        } else {
            pitch = plane_src->pitch;
        }
        format = pdma_pixel_format(plane_src->pixel_format, false);
        ptr->PS[pdma_plane_src].BUF = PDMA_PS_BUF_ADDR_SET((uint32_t) plane_src->buffer);
        ptr->PS[pdma_plane_src].PITCH = PDMA_PS_PITCH_BYTELEN_SET(pitch);
        ptr->PS[pdma_plane_src].BKGD = PDMA_PS_BKGD_COLOR_SET(plane_src->background);
        ptr->PS[pdma_plane_src].SCALE = PDMA_PS_SCALE_X_SET(plane_src->x_scale)
            | PDMA_PS_SCALE_Y_SET(plane_src->y_scale);
        ptr->PS[pdma_plane_src].OFFSET = PDMA_PS_OFFSET_X_SET(plane_src->x_offset)
            | PDMA_PS_OFFSET_Y_SET(plane_src->y_offset);
        ptr->PS[pdma_plane_src].CLRKEY_LOW = PDMA_PS_CLRKEY_LOW_LIMIT_SET(plane_src->colorkey_low);
        ptr->PS[pdma_plane_src].CLRKEY_HIGH = PDMA_PS_CLRKEY_HIGH_LIMIT_SET(plane_src->colorkey_high);
        ptr->PS[pdma_plane_src].ORG = PDMA_PS_ORG_HIGHT_SET(plane_src->height)
            | PDMA_PS_ORG_WIDTH_SET(plane_src->width);
        ptr->PS[pdma_plane_src].CTRL = PDMA_PS_CTRL_INB13_SWAP_SET(plane_src->swap_byte3_byte1)
            | PDMA_PS_CTRL_PACK_DIR_SET(plane_src->byteorder)
            | PDMA_PS_CTRL_BKGCL4CLR_SET(plane_src->use_background_as_clear)
            | PDMA_PS_CTRL_YCBCR_MODE_SET(plane_src->ycbcr_mode)
            | PDMA_PS_CTRL_BYPASS_SET(plane_src->bypass_colorspace_conversion)
            | ((plane_src->flip << PDMA_PS_CTRL_HFLIP_SHIFT)
                    & (PDMA_PS_CTRL_VFLIP_MASK | PDMA_PS_CTRL_HFLIP_MASK))
            | PDMA_PS_CTRL_ROTATE_SET(plane_src->rotate)
            | PDMA_PS_CTRL_DECY_SET(plane_src->y_dec)
            | PDMA_PS_CTRL_DECX_SET(plane_src->x_dec)
            | PDMA_PS_CTRL_HW_BYTE_SWAP_SET(plane_src->byte_swap)
            | PDMA_PS_CTRL_FORMAT_SET(format);
    }

    if (plane_dst != NULL) {
        if (plane_dst->pitch == 0) {
            pitch = display_get_pitch_length_in_byte(plane_src->pixel_format, plane_src->width);
        } else {
            pitch = plane_dst->pitch;
        }
        format = pdma_pixel_format(plane_dst->pixel_format, false);
        ptr->PS[pdma_plane_dst].BUF = PDMA_PS_BUF_ADDR_SET((uint32_t) plane_dst->buffer);
        ptr->PS[pdma_plane_dst].PITCH = PDMA_PS_PITCH_BYTELEN_SET(pitch);
        ptr->PS[pdma_plane_dst].BKGD = PDMA_PS_BKGD_COLOR_SET(plane_dst->background);
        ptr->PS[pdma_plane_dst].SCALE = PDMA_PS_SCALE_X_SET(plane_dst->x_scale)
            | PDMA_PS_SCALE_Y_SET(plane_dst->y_scale);
        ptr->PS[pdma_plane_dst].OFFSET = PDMA_PS_OFFSET_X_SET(plane_dst->x_offset)
            | PDMA_PS_OFFSET_Y_SET(plane_dst->y_offset);
        ptr->PS[pdma_plane_dst].CLRKEY_LOW = PDMA_PS_CLRKEY_LOW_LIMIT_SET(plane_dst->colorkey_low);
        ptr->PS[pdma_plane_dst].CLRKEY_HIGH = PDMA_PS_CLRKEY_HIGH_LIMIT_SET(plane_dst->colorkey_high);
        ptr->PS[pdma_plane_dst].ORG = PDMA_PS_ORG_HIGHT_SET(plane_dst->height)
            | PDMA_PS_ORG_WIDTH_SET(plane_dst->width);
        ptr->PS[pdma_plane_dst].CTRL = PDMA_PS_CTRL_INB13_SWAP_SET(plane_dst->swap_byte3_byte1)
            | PDMA_PS_CTRL_PACK_DIR_SET(plane_dst->byteorder)
            | PDMA_PS_CTRL_BKGCL4CLR_SET(plane_dst->use_background_as_clear)
            | PDMA_PS_CTRL_YCBCR_MODE_SET(plane_dst->ycbcr_mode)
            | PDMA_PS_CTRL_BYPASS_SET(plane_dst->bypass_colorspace_conversion)
            | ((plane_dst->flip << PDMA_PS_CTRL_HFLIP_SHIFT)
                    & (PDMA_PS_CTRL_VFLIP_MASK | PDMA_PS_CTRL_HFLIP_MASK))
            | PDMA_PS_CTRL_ROTATE_SET(plane_dst->rotate)
            | PDMA_PS_CTRL_DECY_SET(plane_dst->y_dec)
            | PDMA_PS_CTRL_DECX_SET(plane_dst->x_dec)
            | PDMA_PS_CTRL_HW_BYTE_SWAP_SET(plane_dst->byte_swap)
            | PDMA_PS_CTRL_FORMAT_SET(format);
    }

    if (yuv2rgb != NULL) {
        ptr->YUV2RGB_COEF0 = PDMA_YUV2RGB_COEF0_C0_SET(yuv2rgb->c0)
            | PDMA_YUV2RGB_COEF0_UV_OFFSET_SET(yuv2rgb->uv_offset)
            | PDMA_YUV2RGB_COEF0_Y_OFFSET_SET(yuv2rgb->y_offset);
        ptr->YUV2RGB_COEF1 = PDMA_YUV2RGB_COEF1_C1_SET(yuv2rgb->c1)
            | PDMA_YUV2RGB_COEF1_C4_SET(yuv2rgb->c4);
        ptr->YUV2RGB_COEF2 = PDMA_YUV2RGB_COEF2_C2_SET(yuv2rgb->c2)
            | PDMA_YUV2RGB_COEF2_C3_SET(yuv2rgb->c3);
    }
}

void pdma_config_output(PDMA_Type *ptr, pdma_output_config_t *config)
{
    uint32_t pitch;
    uint32_t format;

    if (config->pitch == 0) {
        pitch = display_get_pitch_length_in_byte(config->pixel_format,
                                                    config->width);
    } else {
        pitch = config->pitch;
    }
    format = pdma_pixel_format(config->pixel_format, true);
    ptr->OUT_BUF = PDMA_OUT_BUF_ADDR_SET((uint32_t) config->buffer);
    ptr->OUT_PITCH = PDMA_OUT_PITCH_BYTELEN_SET(pitch);
    ptr->OUT_LRC = PDMA_OUT_LRC_X_SET(config->width)
        | PDMA_OUT_LRC_Y_SET(config->height);
    ptr->OUT_PS[0].ULC = PDMA_OUT_PS_ULC_X_SET(config->plane[0].x)
        | PDMA_OUT_PS_ULC_Y_SET(config->plane[0].y);
    ptr->OUT_PS[0].LRC = PDMA_OUT_PS_LRC_X_SET(config->plane[0].x + config->plane[0].width - 1)
        | PDMA_OUT_PS_LRC_Y_SET(config->plane[0].y + config->plane[0].height - 1);
    ptr->OUT_PS[1].ULC = PDMA_OUT_PS_ULC_X_SET(config->plane[1].x)
        | PDMA_OUT_PS_ULC_Y_SET(config->plane[1].y);
    ptr->OUT_PS[1].LRC = PDMA_OUT_PS_LRC_X_SET(config->plane[1].x + config->plane[1].width - 1)
        | PDMA_OUT_PS_LRC_Y_SET(config->plane[1].y + config->plane[1].height - 1);
    ptr->OUT_CTRL = PDMA_OUT_CTRL_DSTALPHA_SET(config->alphablend.dst_alpha)
        | PDMA_OUT_CTRL_SRCALPHA_SET(config->alphablend.src_alpha)
        | PDMA_OUT_CTRL_DSTALPHA_OP_SET(config->alphablend.dst_alpha_op)
        | PDMA_OUT_CTRL_SRCALPHA_OP_SET(config->alphablend.src_alpha_op)
        | PDMA_OUT_CTRL_ABLEND_MODE_SET(config->alphablend.mode)
        | PDMA_OUT_CTRL_FORMAT_SET(format);

    ptr->RGB2YUV_COEF0 = PDMA_RGB2YUV_COEF0_ENABLE_SET(config->rgb2yuv_config.enable)
        | PDMA_RGB2YUV_COEF0_YCBCR_MODE_SET(config->rgb2yuv_config.ycbcr_mode)
        | PDMA_RGB2YUV_COEF0_C0_SET(config->rgb2yuv_config.c0)
        | PDMA_RGB2YUV_COEF0_UV_OFFSET_SET(config->rgb2yuv_config.uv_offset)
        | PDMA_RGB2YUV_COEF0_Y_OFFSET_SET(config->rgb2yuv_config.y_offset);
    ptr->RGB2YUV_COEF1 = PDMA_RGB2YUV_COEF1_C1_SET(config->rgb2yuv_config.c1)
        | PDMA_RGB2YUV_COEF1_C4_SET(config->rgb2yuv_config.c4);
    ptr->RGB2YUV_COEF2 = PDMA_RGB2YUV_COEF2_C2_SET(config->rgb2yuv_config.c2)
        | PDMA_RGB2YUV_COEF2_C3_SET(config->rgb2yuv_config.c3);
    ptr->RGB2YUV_COEF3 = PDMA_RGB2YUV_COEF3_C6_SET(config->rgb2yuv_config.c6)
        | PDMA_RGB2YUV_COEF3_C5_SET(config->rgb2yuv_config.c5);
    ptr->RGB2YUV_COEF4 = PDMA_RGB2YUV_COEF4_C8_SET(config->rgb2yuv_config.c8)
        | PDMA_RGB2YUV_COEF4_C7_SET(config->rgb2yuv_config.c7);
}

#define PDMA_ERROR_STATUS_MASK (PDMA_STAT_AXI_0_WRITE_ERR_MASK \
                              | PDMA_STAT_AXI_1_READ_ERR_MASK \
                              | PDMA_STAT_AXI_0_READ_ERR_MASK)
#define PDMA_BUSY_STATUS_MASK (PDMA_STAT_BLOCKY_MASK \
                              | PDMA_STAT_BLOCKX_MASK)

hpm_stat_t pdma_check_status(PDMA_Type *ptr, uint32_t *status)
{
    uint32_t stat = ptr->STAT;
    if (stat & PDMA_BUSY_STATUS_MASK) {
        if (status) {
            *status = stat;
        }
        return status_pdma_busy;
    }
    if (stat & PDMA_ERROR_STATUS_MASK) {
        if (status) {
            *status = stat;
        }
        ptr->STAT = PDMA_ERROR_STATUS_MASK;
        return status_pdma_error;
    }
    if ((stat & PDMA_STAT_PDMA_DONE_MASK) == PDMA_STAT_PDMA_DONE_MASK) {
        return status_pdma_done;
    }
    return status_pdma_idle;
}

hpm_stat_t pdma_fill_color(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                           uint32_t width, uint32_t height,
                           uint32_t color, uint8_t alpha,
                           display_pixel_format_t format,
                           bool wait, uint32_t *status)
{
    pdma_config_t config;
    pdma_plane_config_t plane_src;
    pdma_plane_config_t plane_dst;
    display_yuv2rgb_coef_t yuv2rgb_coef;
    pdma_output_config_t output;

    if (((display_pixel_format_is_yuv_format(format)) && (width & 1))
        || !(width > 8 || height > 8)) {
        return status_invalid_argument;
    }

    pdma_get_default_config(ptr, &config, format);
    pdma_get_default_plane_config(ptr, &plane_src, format);
    pdma_get_default_plane_config(ptr, &plane_dst, format);
    pdma_get_default_yuv2rgb_coef_config(ptr, &yuv2rgb_coef, format);
    pdma_get_default_output_config(ptr, &output, format);

    config.enable_plane = pdma_plane_both;
    if (width <= 16) {
        config.block_size = pdma_blocksize_8x8;
    } else {
        config.block_size = pdma_blocksize_16x16;
    }
    pdma_init(ptr, &config);

    plane_src.buffer = dst;
    plane_src.width = 1;
    plane_src.height = 1;
    plane_src.background = 0;

    plane_dst.buffer = dst;
    plane_dst.width = 1;
    plane_dst.height = 1;
    plane_dst.background = (alpha << 24) | (color & ~(0xFF << 24));
    pdma_config_planes(ptr, &plane_src, &plane_dst, &yuv2rgb_coef);

    output.buffer = dst;
    output.plane[pdma_plane_dst].x = 0;
    output.plane[pdma_plane_dst].y = 0;
    output.plane[pdma_plane_dst].width = width;
    output.plane[pdma_plane_dst].height = height;
    output.pitch = display_get_pitch_length_in_byte(format, dst_width);

    output.alphablend.mode = display_alphablend_mode_clear;

    output.width = width;
    output.height = height;

    pdma_config_output(ptr, &output);
    pdma_start(ptr);
    if (wait) {
        hpm_stat_t stat;
        do {
            stat = pdma_check_status(ptr, status);
        } while ((stat != status_pdma_done) && (stat != status_pdma_error));
        pdma_stop(ptr);
        return stat;
    }
    return status_success;
}

hpm_stat_t pdma_flip_rotate(PDMA_Type *ptr, uint32_t dst, uint32_t dst_width,
                    uint32_t src, uint32_t src_width, uint32_t x, uint32_t y,
                    uint32_t width, uint32_t height,
                    pdma_flip_t flip, pdma_rotate_t rotate, uint8_t alpha,
                    display_pixel_format_t format,
                    bool wait, uint32_t *status)
{
    pdma_config_t config;
    pdma_plane_config_t plane_src;
    pdma_plane_config_t plane_dst;
    display_yuv2rgb_coef_t yuv2rgb_coef;
    pdma_output_config_t output;

    if ((width + x > dst_width)
        /* YUV422 requires width to be 2-pixel aligned */
        || ((display_pixel_format_is_yuv_format(format)) && (width & 1))
        || !(width > 8 || height > 8)) {
        return status_invalid_argument;
    }

    pdma_get_default_config(ptr, &config, format);
    pdma_get_default_plane_config(ptr, &plane_src, format);
    pdma_get_default_plane_config(ptr, &plane_dst, format);
    pdma_get_default_yuv2rgb_coef_config(ptr, &yuv2rgb_coef, format);
    pdma_get_default_output_config(ptr, &output, format);

    config.enable_plane = pdma_plane_both;
    if (width <= 16) {
        config.block_size = pdma_blocksize_8x8;
    } else {
        config.block_size = pdma_blocksize_16x16;
    }
    pdma_init(ptr, &config);

    plane_src.buffer = src;
    plane_src.height = height;
    plane_src.width = width;
    plane_src.pitch = display_get_pitch_length_in_byte(format, src_width);
    plane_src.flip = flip;
    plane_src.rotate = rotate;

    plane_dst.buffer = src;
    plane_dst.height = 1;
    plane_dst.width = 1;
    plane_dst.pitch = display_get_pitch_length_in_byte(format, dst_width);
    plane_dst.flip = pdma_flip_none;
    plane_dst.rotate = pdma_rotate_0_degree;
    pdma_config_planes(ptr, &plane_src, &plane_dst, &yuv2rgb_coef);

    output.buffer = dst + (y * dst_width + x) * display_get_pixel_size_in_byte(format);

    output.alphablend.src_alpha = alpha;
    output.alphablend.src_alpha_op = display_alpha_op_override;
    output.alphablend.mode = display_alphablend_mode_src_over;

    output.plane[pdma_plane_src].x = 0;
    output.plane[pdma_plane_src].y = 0;
    output.pitch = display_get_pitch_length_in_byte(format, dst_width);

    if ((rotate == pdma_rotate_90_degree)
            || (rotate == pdma_rotate_270_degree)) {
        output.width = height;
        output.height = width;
        output.plane[pdma_plane_src].width = height;
        output.plane[pdma_plane_src].height = width;
    } else {
        output.plane[pdma_plane_src].width = width;
        output.plane[pdma_plane_src].height = height;
        output.width = width;
        output.height = height;
    }

    pdma_config_output(ptr, &output);
    pdma_start(ptr);
    if (wait) {
        hpm_stat_t stat;
        do {
            stat = pdma_check_status(ptr, status);
        } while ((stat != status_pdma_done) && (stat != status_pdma_error));
        pdma_stop(ptr);
        return stat;
    }
    return status_success;
}

hpm_stat_t pdma_blit(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status)
{
    pdma_config_t config;
    pdma_plane_config_t plane_src;
    pdma_plane_config_t plane_dst;
    display_yuv2rgb_coef_t yuv2rgb_coef;
    pdma_output_config_t output;

    if ((width + x > dst_width)
        /* YUV422 requires width to be 2-pixel aligned */
        || ((display_pixel_format_is_yuv_format(format)) && (width & 1))
        || !(width > 8 || height > 8)) {
        return status_invalid_argument;
    }

    pdma_get_default_config(ptr, &config, format);
    pdma_get_default_plane_config(ptr, &plane_src, format);
    pdma_get_default_plane_config(ptr, &plane_dst, format);
    pdma_get_default_yuv2rgb_coef_config(ptr, &yuv2rgb_coef, format);
    pdma_get_default_output_config(ptr, &output, format);

    config.enable_plane = pdma_plane_both;
    if (width <= 16) {
        config.block_size = pdma_blocksize_8x8;
    } else {
        config.block_size = pdma_blocksize_16x16;
    }
    pdma_init(ptr, &config);

    plane_src.buffer = src;
    plane_src.width = width;
    plane_src.height = height;
    plane_src.pitch = display_get_pitch_length_in_byte(format, src_width);
    plane_src.background = 0x00FFFFFF;

    plane_dst.buffer = dst + (y * dst_width + x) * display_get_pixel_size_in_byte(format);
    plane_dst.width = width;
    plane_dst.height = height;
    plane_dst.pitch = display_get_pitch_length_in_byte(format, dst_width);
    pdma_config_planes(ptr, &plane_src, &plane_dst, &yuv2rgb_coef);

    output.buffer = dst + (y * dst_width + x) * display_get_pixel_size_in_byte(format);

    output.plane[pdma_plane_src].x = 0;
    output.plane[pdma_plane_src].y = 0;
    output.plane[pdma_plane_src].width = width;
    output.plane[pdma_plane_src].height = height;

    output.plane[pdma_plane_dst].x = 0;
    output.plane[pdma_plane_dst].y = 0;
    output.plane[pdma_plane_dst].width = width;
    output.plane[pdma_plane_dst].height = height;

    output.alphablend.src_alpha = alpha;
    output.alphablend.src_alpha_op = display_alpha_op_override;
    output.alphablend.mode = display_alphablend_mode_src_over;

    output.width = width;
    output.height = height;
    output.pitch = display_get_pitch_length_in_byte(format, dst_width);

    pdma_config_output(ptr, &output);
    pdma_start(ptr);
    if (wait) {
        hpm_stat_t stat;
        do {
            stat = pdma_check_status(ptr, status);
        } while ((stat != status_pdma_done) && (stat != status_pdma_error));
        pdma_stop(ptr);
        return stat;
    }
    return status_success;
}

static void pdma_calculate_scale(uint32_t t, uint32_t target_t,
                                pdma_decimation_t *dec, uint32_t *scale)
{
    uint32_t tmp;
    tmp = ((t << PDMA_SCALE_FRAC_BITS) / target_t) >> PDMA_SCALE_FRAC_BITS;
    if (tmp >= 16) {
        *dec = pdma_decimation_by_8;
        *scale = 2U << PDMA_SCALE_FRAC_BITS;
        return;
    }
    if (tmp > 8) {
        *dec = pdma_decimation_by_8;
    } else if (tmp > 4) {
        *dec = pdma_decimation_by_4;
    } else if (tmp > 2) {
        *dec = pdma_decimation_by_2;
    } else {
        *dec = pdma_decimation_by_1;
    }

    *scale = (((t >> *dec) << PDMA_SCALE_FRAC_BITS) / target_t);
    return;
}

hpm_stat_t pdma_scale(PDMA_Type *ptr,
                     uint32_t dst, uint32_t dst_width,
                     uint32_t src, uint32_t src_width,
                     uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                     uint32_t target_width, uint32_t target_height,
                     uint8_t alpha,
                     display_pixel_format_t format,
                     bool wait, uint32_t *status)
{
    uint32_t scale;
    pdma_decimation_t dec;

    pdma_config_t config;
    pdma_plane_config_t plane_src;
    pdma_plane_config_t plane_dst;
    display_yuv2rgb_coef_t yuv2rgb_coef;
    pdma_output_config_t output;

    if ((target_width + x > dst_width)
        /* YUV422 requires width to be 2-pixel aligned */
        || ((display_pixel_format_is_yuv_format(format)) && (width & 1))
        || !(width > 8 || height > 8)) {
        return status_invalid_argument;
    }

    pdma_get_default_config(ptr, &config, format);
    pdma_get_default_plane_config(ptr, &plane_src, format);
    pdma_get_default_plane_config(ptr, &plane_dst, format);
    pdma_get_default_yuv2rgb_coef_config(ptr, &yuv2rgb_coef, format);
    pdma_get_default_output_config(ptr, &output, format);

    config.enable_plane = pdma_plane_both;
    if (width <= 16) {
        config.block_size = pdma_blocksize_8x8;
    } else {
        config.block_size = pdma_blocksize_16x16;
    }
    pdma_init(ptr, &config);

    plane_src.buffer = src;
    plane_src.width = width;
    plane_src.height = height;
    plane_src.pitch = display_get_pitch_length_in_byte(format, src_width);

    pdma_calculate_scale(width, target_width, &dec, &scale);
    plane_src.x_scale = scale;
    plane_src.x_dec = dec;
    pdma_calculate_scale(height, target_height, &dec, &scale);
    plane_src.y_scale = scale;
    plane_src.y_dec = dec;
    plane_src.background = 0x00FFFFFF;

    if (display_pixel_format_is_yuv_format(format)) {
        plane_src.x_offset = PDMA_YUV_SCALE_DEFAULT_X_OFFSET;
    }

    plane_dst.buffer = dst + (y * dst_width + x) * display_get_pixel_size_in_byte(format);
    plane_dst.width = width;
    plane_dst.height = height;
    plane_dst.pitch = display_get_pitch_length_in_byte(format, dst_width);
    pdma_config_planes(ptr, &plane_src, &plane_dst, &yuv2rgb_coef);

    output.buffer = dst + (y * dst_width + x) * display_get_pixel_size_in_byte(format);

    output.plane[pdma_plane_src].x = 0;
    output.plane[pdma_plane_src].y = 0;
    output.plane[pdma_plane_src].width = target_width;
    output.plane[pdma_plane_src].height = target_height;

    output.plane[pdma_plane_dst].x = 0;
    output.plane[pdma_plane_dst].y = 0;
    output.plane[pdma_plane_dst].width = target_width;
    output.plane[pdma_plane_dst].height = target_height;

    output.alphablend.src_alpha = alpha;
    output.alphablend.src_alpha_op = display_alpha_op_override;
    output.alphablend.mode = display_alphablend_mode_src_over;

    output.width = target_width;
    output.height = target_height;
    output.pitch = display_get_pitch_length_in_byte(format, dst_width);

    pdma_config_output(ptr, &output);
    pdma_start(ptr);
    if (wait) {
        hpm_stat_t stat;
        do {
            stat = pdma_check_status(ptr, status);
        } while ((stat != status_pdma_done) && (stat != status_pdma_error));
        pdma_stop(ptr);
        return stat;
    }
    return status_success;

}

typedef struct pdma_buf2plane_format {
    display_pixel_format_t format;
    display_byteorder_t byteorder;
} pdma_buf2plane_format_t;

static const pdma_buf2plane_format_t plane_format_tab[display_buf_format_max] = {
    [display_buf_format_argb8888] = {display_pixel_format_argb8888, display_byteorder_a3a2a1a0},
    [display_buf_format_bgra8888] = {display_pixel_format_argb8888, display_byteorder_a0a1a2a3},
    [display_buf_format_rgb565] = {display_pixel_format_rgb565, display_byteorder_a3a2a1a0},
    [display_buf_format_rgb565_swap] = {display_pixel_format_rgb565, display_byteorder_a2a3a0a1},
    [display_buf_format_yuyv] = {display_pixel_format_ycbcr422, display_byteorder_a3a2a1a0},
    [display_buf_format_uyvy] = {display_pixel_format_ycbcr422, display_byteorder_a2a3a0a1},
    [display_buf_format_y8] = {display_pixel_format_y8, display_byteorder_a3a2a1a0},
};

static const pdma_buf2plane_format_t out_format_tab[display_buf_format_max] = {
    [display_buf_format_argb8888] = {display_pixel_format_argb8888, display_byteorder_a3a2a1a0},
    [display_buf_format_bgra8888] = {display_pixel_format_argb8888, display_byteorder_a0a1a2a3},
    [display_buf_format_rgb565] = {display_pixel_format_rgb565, display_byteorder_a3a2a1a0},
    [display_buf_format_rgb565_swap] = {display_pixel_format_rgb565, display_byteorder_a2a3a0a1},
    [display_buf_format_yuyv] = {display_pixel_format_ycbcr422, display_byteorder_a2a3a0a1},
    [display_buf_format_uyvy] = {display_pixel_format_ycbcr422, display_byteorder_a3a2a1a0},
    [display_buf_format_y8] = {display_pixel_format_y8, display_byteorder_a3a2a1a0},
};

void pdma_get_default_blit_option(pdma_blit_option_t *op)
{
    op->blend = display_alphablend_mode_src_over;
    op->flip = pdma_flip_none;
    op->rotate = pdma_rotate_0_degree;
    op->scale.x = 1.0;
    op->scale.y = 1.0;
    op->translate.x = 0;
    op->translate.y = 0;
}

hpm_stat_t pdma_blit_ex(PDMA_Type *ptr,
                     display_buf_t *dst,
                     display_buf_t *src,
                     pdma_blit_option_t *op,
                     bool wait, uint32_t *status)
{
    if ((!dst) || (!src) || (!src->buf) || (!dst->buf) ||
        (op->scale.x > 4096) || (op->scale.y > 4096) ||
        /* YUV422 requires width to be 2-pixel aligned */
        ((display_pixel_format_is_yuv_format(plane_format_tab[src->format].format)) && (src->width & 1)) ||
        ((display_pixel_format_is_yuv_format(plane_format_tab[dst->format].format)) && (dst->width & 1))) {
        return status_invalid_argument;
    }

    pdma_decimation_t x_dec;
    pdma_decimation_t y_dec;
    uint32_t x_scale;
    uint32_t y_scale;

    pdma_config_t config;
    pdma_plane_config_t plane_src;
    pdma_plane_config_t plane_dst;
    display_yuv2rgb_coef_t yuv2rgb_coef;
    pdma_output_config_t output;

    pdma_calculate_scale(65536, (uint32_t)(65536 * op->scale.x), &x_dec, &x_scale);
    pdma_calculate_scale(65536, (uint32_t)(65536 * op->scale.y), &y_dec, &y_scale);

    pdma_get_default_plane_config(ptr, &plane_src, plane_format_tab[src->format].format);
    pdma_get_default_plane_config(ptr, &plane_dst, plane_format_tab[dst->format].format);
    pdma_get_default_yuv2rgb_coef_config(ptr, &yuv2rgb_coef, plane_format_tab[src->format].format);
    pdma_get_default_output_config(ptr, &output, out_format_tab[dst->format].format);

    config.enable_plane = pdma_plane_both;
    config.block_size = pdma_blocksize_8x8;
    config.byteorder = out_format_tab[dst->format].byteorder;
    pdma_init(ptr, &config);

    plane_src.buffer = (uint32_t)src->buf;
    plane_src.byteorder = plane_format_tab[src->format].byteorder;
    plane_src.width = src->width;
    plane_src.height = src->height;
    plane_src.pitch = src->stride;
    plane_src.x_scale = x_scale;
    plane_src.x_dec = x_dec;
    plane_src.y_scale = y_scale;
    plane_src.y_dec = y_dec;
    plane_src.background = 0x00000000; /* alpha must be 0 */
    plane_src.x_offset = PDMA_YUV_SCALE_DEFAULT_X_OFFSET;
    plane_src.flip = op->flip;
    plane_src.rotate = op->rotate;

    plane_dst.buffer = (uint32_t)dst->buf;
    plane_dst.byteorder = plane_format_tab[dst->format].byteorder;
    plane_dst.width = dst->width;
    plane_dst.height = dst->height;
    plane_dst.pitch = dst->stride;
    pdma_config_planes(ptr, &plane_src, &plane_dst, &yuv2rgb_coef);

    output.buffer = plane_dst.buffer;
    output.plane[pdma_plane_src].x = op->translate.x;
    output.plane[pdma_plane_src].y = op->translate.y;

    /*
     * aligned to lower right of dst window and non-overlapping area is filled by background of src.
     * so alpha that background of src must be 0.
     */
    output.plane[pdma_plane_src].width = dst->width - op->translate.x;
    output.plane[pdma_plane_src].height = dst->height - op->translate.y;

    output.plane[pdma_plane_dst].x = 0;
    output.plane[pdma_plane_dst].y = 0;
    output.plane[pdma_plane_dst].width = plane_dst.width;
    output.plane[pdma_plane_dst].height = plane_dst.height;

    output.alphablend.src_alpha = src->alpha.val;
    output.alphablend.src_alpha_op = src->alpha.op;
    output.alphablend.dst_alpha = dst->alpha.val;
    output.alphablend.dst_alpha_op = dst->alpha.op;
    output.alphablend.mode = op->blend;

    output.width = plane_dst.width;
    output.height = plane_dst.height;
    output.pitch = plane_dst.pitch;

    pdma_config_output(ptr, &output);
    pdma_start(ptr);
    if (wait) {
        hpm_stat_t stat;
        do {
            stat = pdma_check_status(ptr, status);
        } while ((stat != status_pdma_done) && (stat != status_pdma_error));
        pdma_stop(ptr);
        return stat;
    }
    return status_success;
}
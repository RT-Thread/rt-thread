/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_lcdc_drv.h"

#define LCDC_FIFO_THRESHOLD (0x70)

static uint32_t lcdc_pixel_format(display_pixel_format_t format)
{
    switch (format) {
    case display_pixel_format_argb8888:
        return 9;
    case display_pixel_format_rgb565:
        return 4;
    case display_pixel_format_yuv422:
        return 7;
    case display_pixel_format_ycbcr422:
        return 7;
    case display_pixel_format_y8:
        return 0xb;
    case display_pixel_format_raw8:
        return 0xb;
    default:
        return 9;
    }
}

/*!
 * @brief Get LCDC byteorder value.
 *
 * @param byteorder Dispaly byteorder value.
 * @return LCDC byteorder value.
 */
static uint8_t lcdc_byteorder(display_byteorder_t byteorder)
{
    switch (byteorder) {
    case display_byteorder_a3a2a1a0: /* LSB */
        return 0;
    case display_byteorder_a0a1a2a3: /* MSB */
        return 1;
    default:
        return 0;
    }
}

void lcdc_get_default_layer_config(LCDC_Type *ptr, lcdc_layer_config_t *layer, display_pixel_format_t pixel_format, uint8_t layer_index)
{
    layer->max_bytes = lcdc_layer_max_bytes_64;
    /* different layer has different max_ot configuration */
    if (layer_index < LCDC_SOC_MAX_CSC_LAYER_COUNT) {
        layer->max_ot = 0;
    } else {
        layer->max_ot = 2;
    }
    layer->byteorder = display_byteorder_a3a2a1a0;
    if (display_pixel_format_is_yuv_format(pixel_format)) {
        layer->yuv = display_yuv_mode_422_y1u1y2v1; /* If YUV format, change byte sequence to YUYV */
    } else {
        layer->yuv = display_yuv_mode_422_u1y1v1y2; /* Not change byte sequence */
    }
    layer->pixel_format = pixel_format;

    layer->alphablend.src_alpha = 0;
    layer->alphablend.dst_alpha = 0;
    layer->alphablend.src_alpha_op = display_alpha_op_invalid;
    layer->alphablend.dst_alpha_op = display_alpha_op_invalid;
    layer->alphablend.mode = display_alphablend_mode_clear;

    switch (pixel_format) {
    case display_pixel_format_yuv422:
        layer->csc_config.enable = true;
        layer->csc_config.ycbcr_mode = false;
        layer->csc_config.yuv2rgb_coef.c0 = 0x100;
        layer->csc_config.yuv2rgb_coef.uv_offset = 0;
        layer->csc_config.yuv2rgb_coef.y_offset = 0;
        layer->csc_config.yuv2rgb_coef.c1 = 0x123;
        layer->csc_config.yuv2rgb_coef.c2 = 0x76B;
        layer->csc_config.yuv2rgb_coef.c3 = 0x79C;
        layer->csc_config.yuv2rgb_coef.c4 = 0x208;
        break;
    case display_pixel_format_ycbcr422:
        layer->csc_config.enable = true;
        layer->csc_config.ycbcr_mode = true;
        layer->csc_config.yuv2rgb_coef.c0 = 0x12A;
        layer->csc_config.yuv2rgb_coef.uv_offset = 0x180;
        layer->csc_config.yuv2rgb_coef.y_offset = 0x1F0;
        layer->csc_config.yuv2rgb_coef.c1 = 0x198;
        layer->csc_config.yuv2rgb_coef.c2 = 0x730;
        layer->csc_config.yuv2rgb_coef.c3 = 0x79C;
        layer->csc_config.yuv2rgb_coef.c4 = 0x204;
        break;
    default:
        layer->csc_config.enable = false;
        layer->csc_config.ycbcr_mode = false;
        layer->csc_config.yuv2rgb_coef.c0 = 0;
        layer->csc_config.yuv2rgb_coef.uv_offset = 0;
        layer->csc_config.yuv2rgb_coef.y_offset = 0;
        layer->csc_config.yuv2rgb_coef.c1 = 0;
        layer->csc_config.yuv2rgb_coef.c2 = 0;
        layer->csc_config.yuv2rgb_coef.c3 = 0;
        layer->csc_config.yuv2rgb_coef.c4 = 0;
        break;
    }
}

void lcdc_get_default_config(LCDC_Type *ptr, lcdc_config_t *config)
{
    config->resolution_x = 480;
    config->resolution_y = 272;
    config->hsync.front_porch_pulse = 40;
    config->hsync.back_porch_pulse = 50;
    config->hsync.pulse_width = 30;
    config->vsync.front_porch_pulse = 20;
    config->vsync.back_porch_pulse = 20;
    config->vsync.pulse_width = 10;
    config->background.u = 0x0;

    config->control.display_mode = lcdc_display_mode_normal;
    config->control.line_pattern = lcdc_line_pattern_rgb;
    config->control.invert_pixel_clock = false;
    config->control.invert_pixel_data = false;
    config->control.invert_href = false;
    config->control.invert_vsync = false;
    config->control.invert_hsync = false;
}

void lcdc_reset_register_values(LCDC_Type *ptr)
{
    uint8_t i = 0;

    lcdc_turn_off_display(ptr);

    ptr->DISP_WN_SIZE = 0;
    ptr->INT_EN = 0;
    ptr->ST = 0xFFFFFFFFU;
    ptr->DMA_ST = 0xFFFFFFFFU;
    ptr->VSYNC_PARA = 0x00C01803U;
    ptr->HSYNC_PARA = 0x00C01803U;

    for (i = 0; i < LCDC_SOC_MAX_LAYER_COUNT; i++) {
        ptr->LAYER[i].LAYCTRL = 0;
        ptr->LAYER[i].ALPHAS = 0;
        ptr->LAYER[i].LAYSIZE = 0;
        ptr->LAYER[i].LAYPOS = 0;
        ptr->LAYER[i].START0 = 0;
        ptr->LAYER[i].LINECFG = 0;
        ptr->LAYER[i].BG_CL = 0;
    }

    for (i = 0; i < LCDC_SOC_MAX_CSC_LAYER_COUNT; i++) {
        ptr->LAYER[i].CSC_COEF0 = 0;
        ptr->LAYER[i].CSC_COEF1 = 0;
        ptr->LAYER[i].CSC_COEF2 = 0;
    }
}

void lcdc_init(LCDC_Type *ptr, lcdc_config_t *config)
{
    lcdc_reset_register_values(ptr);

    ptr->DISP_WN_SIZE = LCDC_DISP_WN_SIZE_X_SET(config->resolution_x) |
                    LCDC_DISP_WN_SIZE_Y_SET(config->resolution_y);
    ptr->HSYNC_PARA =
        LCDC_HSYNC_PARA_FP_SET(config->hsync.front_porch_pulse)
      | LCDC_HSYNC_PARA_BP_SET(config->hsync.back_porch_pulse)
      | LCDC_HSYNC_PARA_PW_SET(config->hsync.pulse_width);
    ptr->BGND_CL = LCDC_BGND_CL_B_SET(config->background.b)
        | LCDC_BGND_CL_G_SET(config->background.g)
        | LCDC_BGND_CL_R_SET(config->background.r);
    ptr->VSYNC_PARA =
        LCDC_VSYNC_PARA_FP_SET(config->vsync.front_porch_pulse)
      | LCDC_VSYNC_PARA_BP_SET(config->vsync.back_porch_pulse)
      | LCDC_VSYNC_PARA_PW_SET(config->vsync.pulse_width);
    ptr->TXFIFO = LCDC_TXFIFO_THRSH_SET(LCDC_FIFO_THRESHOLD);
    ptr->CTRL = LCDC_CTRL_DISP_MODE_SET(config->control.display_mode)
        | LCDC_CTRL_LINE_PATTERN_SET(config->control.line_pattern)
        | LCDC_CTRL_INV_PXDATA_SET(config->control.invert_pixel_data)
        | LCDC_CTRL_INV_PXCLK_SET(config->control.invert_pixel_clock)
        | LCDC_CTRL_INV_HREF_SET(config->control.invert_href)
        | LCDC_CTRL_INV_VSYNC_SET(config->control.invert_vsync)
        | LCDC_CTRL_INV_HSYNC_SET(config->control.invert_hsync);
}

hpm_stat_t lcdc_config_layer(LCDC_Type *ptr,
                       uint8_t layer_index,
                       lcdc_layer_config_t *layer,
                       bool enable_layer)
{
    uint8_t byteorder;
    uint32_t pitch;
    uint32_t format;
    uint32_t ctrl = ptr->LAYER[layer_index].LAYCTRL;

    if ((!LCDC_SOC_LAYER_SUPPORTS_CSC(layer_index) && layer->csc_config.enable)
         || (!LCDC_SOC_LAYER_SUPPORTS_YUV(layer_index)
             && (display_pixel_format_is_yuv_format(layer->pixel_format)))) {
        return status_lcdc_layer_not_supported;
    }

    ptr->LAYER[layer_index].LAYSIZE =
        LCDC_LAYER_LAYSIZE_HEIGHT_SET(layer->height)
      | LCDC_LAYER_LAYSIZE_WIDTH_SET(layer->width);
    ptr->LAYER[layer_index].LAYPOS =
        LCDC_LAYER_LAYPOS_X_SET(layer->position_x)
      | LCDC_LAYER_LAYPOS_Y_SET(layer->position_y);
    ptr->LAYER[layer_index].START0 = LCDC_LAYER_START0_ADDR0_SET((uint32_t)layer->buffer);
    ptr->LAYER[layer_index].ALPHAS = LCDC_LAYER_ALPHAS_LOCD_SET(layer->alphablend.src_alpha)
        | LCDC_LAYER_ALPHAS_IND_SET(layer->alphablend.dst_alpha);

    pitch = display_get_pitch_length_in_byte(layer->pixel_format, layer->width);
    ptr->LAYER[layer_index].LINECFG = LCDC_LAYER_LINECFG_MPT_SIZE_SET(layer->max_bytes)
        | LCDC_LAYER_LINECFG_MAX_OT_SET(layer->max_ot)
        | LCDC_LAYER_LINECFG_PITCH_SET(pitch);
    ptr->LAYER[layer_index].BG_CL = LCDC_LAYER_BG_CL_ARGB_SET(layer->background.u);

    ptr->LAYER[layer_index].CSC_COEF0 =
        LCDC_LAYER_CSC_COEF0_ENABLE_SET(layer->csc_config.enable)
        | LCDC_LAYER_CSC_COEF0_YCBCR_MODE_SET(layer->csc_config.ycbcr_mode)
        | LCDC_LAYER_CSC_COEF0_C0_SET(layer->csc_config.yuv2rgb_coef.c0)
        | LCDC_LAYER_CSC_COEF0_UV_OFFSET_SET(layer->csc_config.yuv2rgb_coef.uv_offset)
        | LCDC_LAYER_CSC_COEF0_Y_OFFSET_SET(layer->csc_config.yuv2rgb_coef.y_offset);
    ptr->LAYER[layer_index].CSC_COEF1 =
        LCDC_LAYER_CSC_COEF1_C1_SET(layer->csc_config.yuv2rgb_coef.c1)
        | LCDC_LAYER_CSC_COEF1_C4_SET(layer->csc_config.yuv2rgb_coef.c4);
    ptr->LAYER[layer_index].CSC_COEF2 =
        LCDC_LAYER_CSC_COEF2_C2_SET(layer->csc_config.yuv2rgb_coef.c2)
        | LCDC_LAYER_CSC_COEF2_C3_SET(layer->csc_config.yuv2rgb_coef.c3);

    /* bit18 is reserved but has to be set to 1 */
    ctrl |= 1 << 18;

    byteorder = lcdc_byteorder(layer->byteorder);
    format = lcdc_pixel_format(layer->pixel_format);
    ctrl = (ctrl & ~(LCDC_LAYER_LAYCTRL_PIXFORMAT_MASK
                | LCDC_LAYER_LAYCTRL_AB_MODE_MASK
                | LCDC_LAYER_LAYCTRL_LOCALPHA_OP_MASK
                | LCDC_LAYER_LAYCTRL_INALPHA_OP_MASK
                | LCDC_LAYER_LAYCTRL_YUV_FORMAT_MASK))
        | LCDC_LAYER_LAYCTRL_PACK_DIR_SET(byteorder)
        | LCDC_LAYER_LAYCTRL_PIXFORMAT_SET(format)
        | LCDC_LAYER_LAYCTRL_AB_MODE_SET(layer->alphablend.mode)
        | LCDC_LAYER_LAYCTRL_LOCALPHA_OP_SET(layer->alphablend.src_alpha_op)
        | LCDC_LAYER_LAYCTRL_INALPHA_OP_SET(layer->alphablend.dst_alpha_op)
        | LCDC_LAYER_LAYCTRL_YUV_FORMAT_SET(layer->yuv);

    if (enable_layer) {
        ctrl |= LCDC_LAYER_LAYCTRL_EN_MASK;
    }
    ptr->LAYER[layer_index].LAYCTRL = ctrl | LCDC_LAYER_LAYCTRL_SHADOW_LOAD_EN_MASK;
    return status_success;
}

void lcdc_turn_off_display(LCDC_Type *ptr)
{
    if (ptr->CTRL & LCDC_CTRL_DISP_ON_MASK) {
        ptr->INT_EN = 0;

        /* 1. wait for current frame end */
        ptr->ST = 0xFFFFFFFF;
        while ((ptr->ST & LCDC_ST_VS_BLANK_MASK) == 0) {
        }

        /* 2. issue display off */
        ptr->ST = 0xFFFFFFFF;
        lcdc_software_reset(ptr);
        ptr->CTRL &= ~LCDC_CTRL_DISP_ON_MASK;
        while ((ptr->ST & LCDC_ST_VS_BLANK_MASK) == 0) {
        }
    }
    return;
}

void lcdc_turn_on_display(LCDC_Type *ptr)
{
    if (!(ptr->CTRL & LCDC_CTRL_DISP_ON_MASK)) {
        ptr->CTRL |= LCDC_CTRL_DISP_ON_MASK;
    }
}

void lcdc_layer_update_pixel_format(LCDC_Type *ptr, uint8_t layer_index,
                                    uint8_t pixel_format)
{
    uint32_t pitch;
    uint32_t width = (ptr->LAYER[layer_index].LAYSIZE & LCDC_LAYER_LAYSIZE_WIDTH_MASK)
                    >> LCDC_LAYER_LAYSIZE_WIDTH_SHIFT;
    pitch = display_get_pitch_length_in_byte(pixel_format, width);
    ptr->LAYER[layer_index].LINECFG = (ptr->LAYER[layer_index].LINECFG & ~LCDC_LAYER_LINECFG_PITCH_MASK)
        | LCDC_LAYER_LINECFG_PITCH_SET(pitch);
}

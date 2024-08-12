/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_cam_drv.h"

#define CAM_RX_FIFO_THRESHOLD (6U)

void cam_get_default_config(CAM_Type *ptr, cam_config_t *config, display_pixel_format_t pixel_format)
{
    (void) ptr;
    config->width = 320;
    config->height = 240;
    config->buffer1 = -1;
    config->buffer2 = -1;
    config->pixclk_sampling_falling = false;
    config->hsync_active_low = false;
    config->vsync_active_low = false;
#if defined(HPM_IP_FEATURE_CAM_INV_DEN) && (HPM_IP_FEATURE_CAM_INV_DEN == 1)
    config->de_active_low = false;
#endif
    config->color_ext = false;
    config->data_pack_msb = false;
    config->data_store_mode = CAM_DATA_STORE_MODE_NORMAL;
    config->color_format = pixel_format;
    config->sensor_bitwidth = CAM_SENSOR_BITWIDTH_10BITS;

    switch (pixel_format) {
    case display_pixel_format_yuv422:
        config->csc_config.enable = true;
        config->csc_config.ycbcr_mode = false;
        config->csc_config.yuv2rgb_coef.c0 = 0x100;
        config->csc_config.yuv2rgb_coef.uv_offset = 0;
        config->csc_config.yuv2rgb_coef.y_offset = 0;
        config->csc_config.yuv2rgb_coef.c1 = 0x123;
        config->csc_config.yuv2rgb_coef.c2 = 0x76B;
        config->csc_config.yuv2rgb_coef.c3 = 0x79C;
        config->csc_config.yuv2rgb_coef.c4 = 0x208;
        break;
    case display_pixel_format_ycbcr422:
        config->csc_config.enable = true;
        config->csc_config.ycbcr_mode = true;
        config->csc_config.yuv2rgb_coef.c0 = 0x12A;
        config->csc_config.yuv2rgb_coef.uv_offset = 0x180;
        config->csc_config.yuv2rgb_coef.y_offset = 0x1F0;
        config->csc_config.yuv2rgb_coef.c1 = 0x198;
        config->csc_config.yuv2rgb_coef.c2 = 0x730;
        config->csc_config.yuv2rgb_coef.c3 = 0x79C;
        config->csc_config.yuv2rgb_coef.c4 = 0x204;
        break;
    default:
        config->csc_config.enable = false;
        config->csc_config.ycbcr_mode = false;
        config->csc_config.yuv2rgb_coef.c0 = 0;
        config->csc_config.yuv2rgb_coef.uv_offset = 0;
        config->csc_config.yuv2rgb_coef.y_offset = 0;
        config->csc_config.yuv2rgb_coef.c1 = 0;
        config->csc_config.yuv2rgb_coef.c2 = 0;
        config->csc_config.yuv2rgb_coef.c3 = 0;
        config->csc_config.yuv2rgb_coef.c4 = 0;
        break;
    }
}

void cam_reset(CAM_Type *ptr)
{
    cam_stop(ptr);
    ptr->CR1 = CAM_CR1_ASYNC_RXFIFO_CLR_MASK;
    ptr->INT_EN = 0;
    ptr->CR2 = CAM_CR2_FRMCNT_RST_MASK;
    ptr->STA = 0xFFFFFFFF;
    ptr->CR20 = 0;
}

hpm_stat_t cam_init(CAM_Type *ptr, cam_config_t *config)
{
    hpm_stat_t stat = status_success;
    uint32_t pixel_format, width;

    pixel_format = config->color_format;
    width = config->width;

    if ((int)config->buffer1 < 0) {
        return status_invalid_argument;
    }

    if (pixel_format == CAM_COLOR_FORMAT_RAW8) {
        if ((width % 2) != 0) {
            return status_invalid_argument;
        }
        /* use rgb565 format to receive raw8 data and adjust the width to half */
        pixel_format = CAM_COLOR_FORMAT_RGB565;
        width /= 2;
    }

    cam_reset(ptr);

    /*
     * In DVP mode, de_active_low and hsync_active_low are same.
     */
#if defined(HPM_IP_FEATURE_CAM_INV_DEN) && (HPM_IP_FEATURE_CAM_INV_DEN == 1)
    if (config->sensor_bitwidth != CAM_SENSOR_BITWIDTH_24BITS) {
        config->de_active_low = config->hsync_active_low;
    }
#endif

    ptr->CR1 = CAM_CR1_INV_PIXCLK_SET(config->pixclk_sampling_falling)
        | CAM_CR1_INV_HSYNC_SET(config->hsync_active_low)
        | CAM_CR1_INV_VSYNC_SET(config->vsync_active_low)
#if defined(HPM_IP_FEATURE_CAM_INV_DEN) && (HPM_IP_FEATURE_CAM_INV_DEN == 1)
        | CAM_CR1_INV_DEN_SET(config->de_active_low)
#endif
        | CAM_CR1_RESTART_BUSPTR_MASK
        | CAM_CR1_COLOR_EXT_SET(config->color_ext)
        | CAM_CR1_PACK_DIR_SET(config->data_pack_msb)
        | config->data_store_mode
        | pixel_format
        | config->sensor_bitwidth;

    ptr->IDEAL_WN_SIZE = CAM_IDEAL_WN_SIZE_HEIGHT_SET(config->height)
        | CAM_IDEAL_WN_SIZE_WIDTH_SET(width);

    ptr->CR2 = CAM_CR2_DMA_REQ_EN_RFF_MASK
        | CAM_CR2_RXFF_LEVEL_SET(CAM_RX_FIFO_THRESHOLD);
    ptr->DMASA_FB1 = config->buffer1;
    if ((int)config->buffer2 < 0) {
        ptr->DMASA_FB2 = config->buffer1;
    } else {
        ptr->DMASA_FB2 = config->buffer2;
    }

    ptr->CSC_COEF0 = CAM_CSC_COEF0_ENABLE_SET(config->csc_config.enable)
                    | CAM_CSC_COEF0_YCBCR_MODE_SET(config->csc_config.ycbcr_mode)
                    | CAM_CSC_COEF0_C0_SET(config->csc_config.yuv2rgb_coef.c0)
                    | CAM_CSC_COEF0_UV_OFFSET_SET(config->csc_config.yuv2rgb_coef.uv_offset)
                    | CAM_CSC_COEF0_Y_OFFSET_SET(config->csc_config.yuv2rgb_coef.y_offset);
    ptr->CSC_COEF1 = CAM_CSC_COEF1_C1_SET(config->csc_config.yuv2rgb_coef.c1)
                    | CAM_CSC_COEF1_C4_SET(config->csc_config.yuv2rgb_coef.c4);
    ptr->CSC_COEF2 = CAM_CSC_COEF2_C2_SET(config->csc_config.yuv2rgb_coef.c2)
                    | CAM_CSC_COEF2_C3_SET(config->csc_config.yuv2rgb_coef.c3);

    return stat;
}

void cam_stop(CAM_Type *ptr)
{
    ptr->CR18 &= ~CAM_CR18_CAM_ENABLE_MASK;
}

void cam_start(CAM_Type *ptr)
{
    ptr->CR18 |= CAM_CR18_CAM_ENABLE_MASK;
}

void cam_stop_safely(CAM_Type *ptr)
{
    /*
    * waiting for capture frame to complete
    */
    cam_clear_status(ptr, cam_status_end_of_frame);
    while (cam_check_status(ptr, cam_status_end_of_frame) == false) {
    }
    cam_stop(ptr);
}

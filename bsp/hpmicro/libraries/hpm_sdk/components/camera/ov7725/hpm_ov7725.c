/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ov7725.h"

static const uint8_t ov7725_default_regs[][2] = {
    {COM4,          0x41}, /* bypass PLL */

    /*
     * VGA Window Size
     */
    {HSTART,        0x22},
    {HSIZE,         0xa4},
    {VSTART,        0x07},
    {VSIZE,         0xf0},
    {HREF,          0x00},

    /*
     * Scale down to VGA Resolution
     */
    {HOUTSIZE,      0xA0},
    {VOUTSIZE,      0xF0},

    {COM12,         0x03},
    {EXHCH,         0x00},
    {TGT_B,         0x7F},
    {FIXGAIN,       0x09},
    {AWB_CTRL0,     0xE0},
    {DSP_CTRL1,     0xFF},
    {DSP_CTRL2,     0x20},
    {DSP_CTRL3,     0x00},
    {DSP_CTRL4,     0x00},

    {COM8,          0xF8},
    {COM6,          0xC5},
    {COM9,          0x11},
    {COM10,         COM10_VSYNC_NEG | COM10_PCLK_MASK}, /* Invert VSYNC and MASK PCLK */
    {BDBASE,        0x7F},
    {DBSTEP,        0x03},
    {AEW,           0x70},
    {AEB,           0x43},
    {VPT,           0xA1},
    {EXHCL,         0x00},
    {AWB_CTRL3,     0xAA},
    {COM8,          0xFF},

    /*
     * Gamma
     */
    {GAM1,          0x0C},
    {GAM2,          0x16},
    {GAM3,          0x2A},
    {GAM4,          0x4E},
    {GAM5,          0x61},
    {GAM6,          0x6F},
    {GAM7,          0x7B},
    {GAM8,          0x86},
    {GAM9,          0x8E},
    {GAM10,         0x97},
    {GAM11,         0xA4},
    {GAM12,         0xAF},
    {GAM13,         0xC5},
    {GAM14,         0xD7},
    {GAM15,         0xE8},

    {SLOP,          0x20},
    {EDGE1,         0x05},
    {EDGE2,         0x03},
    {EDGE3,         0x00},
    {DNSOFF,        0x01},

    {MTX1,          0xB0},
    {MTX2,          0x9D},
    {MTX3,          0x13},
    {MTX4,          0x16},
    {MTX5,          0x7B},
    {MTX6,          0x91},
    {MTX_CTRL,      0x1E},

    {BRIGHTNESS,    0x08},
    {CONTRAST,      0x20},
    {UVADJ0,        0x81},
    {SDE,           (SDE_CONT_BRIGHT_EN | SDE_SATURATION_EN)},

    /*
     * For 30 fps/60Hz
     */
    {DM_LNL,        0x00},
    {DM_LNH,        0x00},
    {BDBASE,        0x7F},
    {DBSTEP,        0x03},

    /*
     * Lens Correction, should be tuned with real camera module
     */
    {LC_RADI,       0x10},
    {LC_COEF,       0x10},
    {LC_COEFB,      0x14},
    {LC_COEFR,      0x17},
    {LC_CTR,        0x05},
    {COM5,          0x65},
};


static const uint8_t ov7725_default_yuv_regs[][2] = {
    {COM12,       0x03},
    {HSTART,      0x22},
    {HSIZE,       0xa4},
    {VSTART,      0x07},
    {VSIZE,       0xf0},
    {HREF,        0x00},
    {HOUTSIZE,    0xa0},
    {VOUTSIZE,    0xf0},
    {EXHCH,       0x00},
    {CLKRC,       0x01},
    {TGT_B,       0x7f},
    {FIXGAIN,     0x09},
    {AWB_CTRL0,   0xe0},
    {DSP_CTRL1,   0xff},
    {DSP_CTRL2,   0x20},
    {DSP_CTRL3,   0x00},
    {DSP_CTRL4,   0x48},
    {COM8,        0xf0},
    {COM4,        0x41}, /*           0x51/          0x61/          0x71 for different AEC/AGC window */
    {COM6,        0xc5},
    {COM9,        0x11},
    {BDBASE,      0x7f},
    {DBSTEP,      0x03},
    {AEW,         0x40},
    {AEB,         0x30},
    {VPT,         0xa1},
    {EXHCL,       0x00},
    {AWB_CTRL3,   0xaa},
    {COM8,        0xff},
    {EDGE1,       0x05},
    {DNSOFF,      0x01},
    {EDGE2,       0x03},
    {EDGE3,       0x00},
    {MTX1,        0xb0},
    {MTX2,        0x9d},
    {MTX3,        0x13},
    {MTX4,        0x16},
    {MTX5,        0x7b},
    {MTX6,        0x91},
    {MTX_CTRL,    0x1e},
    {BRIGHTNESS,  0x08},
    {CONTRAST,    0x20},
    {UVADJ0,      0x81},
    {SDE,         0x06},
    /* Gamma */
    {GAM1,        0x0c},
    {GAM2,        0x16},
    {GAM3,        0x2a},
    {GAM4,        0x4e},
    {GAM5,        0x61},
    {GAM6,        0x6f},
    {GAM7,        0x7b},
    {GAM8,        0x86},
    {GAM9,        0x8e},
    {GAM10,       0x97},
    {GAM11,       0xa4},
    {GAM12,       0xaf},
    {GAM13,       0xc5},
    {GAM14,       0xd7},
    {GAM15,       0xe8},
    {SLOP,        0x20},
    /* for 30 fps,0Hz */
    {DM_LNL,      0x00},
    {BDBASE,      0x7f},
    {DBSTEP,      0x03},

    /* Lens Correcon, should be tuned with real camera module */
    {LC_RADI,     0x10},
    {LC_COEF,     0x10},
    {LC_COEFB,    0x14},
    {LC_COEFR,    0x17},
    {LC_CTR,      0x05},
    {COM5,        0x65},
};

hpm_stat_t ov7725_read_register(camera_context_t *context, uint8_t reg, uint8_t *buf)
{
    hpm_stat_t stat = i2c_master_write(context->ptr, context->i2c_device_addr, &reg, 1);
    if (stat != status_success) {
        return stat;
    }
    return i2c_master_read(context->ptr, context->i2c_device_addr, buf, 1);

}

hpm_stat_t ov7725_write_register(camera_context_t *context, uint8_t reg, uint8_t val)
{
    return i2c_master_address_write(context->ptr, context->i2c_device_addr, &reg, 1, &val, 1);
}

hpm_stat_t ov7725_load_settings(camera_context_t *context, uint8_t *reg_values, uint32_t count)
{
    hpm_stat_t stat = status_success;
    for (uint32_t i = 0, j = 0; i < count; i++, j += 2) {
        stat = ov7725_write_register(context, reg_values[j], reg_values[j+1]);
        if (stat != status_success) {
            break;
        }
    }
    return stat;
}

hpm_stat_t ov7725_software_reset(camera_context_t *context)
{
    hpm_stat_t stat = status_success;

    stat = ov7725_write_register(context, COM7, COM7_RESET);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

hpm_stat_t ov7725_check_chip_id(camera_context_t *context)
{
    hpm_stat_t stat = status_success;
    uint8_t val_h = 0;
    uint8_t val_l = 0;

    HPM_CHECK_RET(ov7725_read_register(context, OV7725_CHIP_ID_HIGH_BYTE_ADDR, &val_h));
    HPM_CHECK_RET(ov7725_read_register(context, OV7725_CHIP_ID_LOW_BYTE_ADDR, &val_l));

    if (val_h != OV7725_CHIP_ID_HIGH_BYTE_VALUE) {
        return status_fail;
    }

    if (val_l != OV7725_CHIP_ID_LOW_BYTE_VALUE) {
        return status_fail;
    }

    return stat;
}

static hpm_stat_t ov7725_set_framesize(camera_context_t *context, uint16_t width, uint16_t height)
{
    hpm_stat_t stat = status_success;
    uint32_t hstart = 0x22U << 2;
    uint32_t vstart = 0x7U << 1;
    uint32_t hsize = width + 16;

    stat |= ov7725_write_register(context, HSTART, hstart >> 2);
    stat |= ov7725_write_register(context, HSIZE, hsize >> 2);
    stat |= ov7725_write_register(context, VSTART, vstart >> 1);
    stat |= ov7725_write_register(context, VSIZE, height >> 1);

    stat |= ov7725_write_register(context, HOUTSIZE, width >> 2);
    stat |= ov7725_write_register(context, VOUTSIZE, height >> 1);

    stat |= ov7725_write_register(context, HREF,
            ((vstart & 1) << 6) | ((hstart & 3) << 4) | ((height & 1) << 2) | ((hsize & 3) << 0));

    stat = ov7725_write_register(context, EXHCH, ((height & 0x1) << 2) | (width & 0x3));
    if (stat != status_success) {
        return stat;
    }
    return stat;
}

hpm_stat_t ov7725_set_pixel_format(camera_context_t *context, display_pixel_format_t pixel_format)
{
    hpm_stat_t stat = status_success;
    uint8_t val = 0;

    stat |= ov7725_read_register(context, COM7, &val);
    val &= ~0x1F;
    switch (pixel_format) {
    case display_pixel_format_rgb565:
        val |= COM7_FMT_RGB565;
        break;
    case display_pixel_format_rgb444:
        val |= COM7_FMT_RGB444;
        break;
    case display_pixel_format_yuv422:
    case display_pixel_format_y8:
        val |= COM7_FMT_YUV;
        break;
    case display_pixel_format_raw8:
        stat |= ov7725_write_register(context, DSP_CTRL4, DSP_CTRL4_RAW8);
        val |= COM7_FMT_R_BAYER;
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    if (stat != status_success) {
        return stat;
    }

    stat |= ov7725_write_register(context, COM7, val);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}

hpm_stat_t ov7725_init(camera_context_t *context, camera_config_t *ov_config)
{
    hpm_stat_t stat = status_success;

    switch (ov_config->pixel_format) {
    case display_pixel_format_yuv422:
    case display_pixel_format_y8:
        ov7725_load_settings(context, (uint8_t *) ov7725_default_yuv_regs, ARRAY_SIZE(ov7725_default_yuv_regs));
        break;
    default:
        ov7725_load_settings(context, (uint8_t *) ov7725_default_regs, ARRAY_SIZE(ov7725_default_regs));
        stat |= ov7725_write_register(context, COM7, COM7_RES_VGA | COM7_FMT_RGB565);
        stat |= ov7725_write_register(context, COM10, 0);
        stat |= ov7725_write_register(context, COM3, 0);
        break;
    }

    stat |= ov7725_write_register(context, CLKRC, 0x2);
    stat |= ov7725_write_register(context, COM4, 0x41);

    stat |= ov7725_set_framesize(context, ov_config->width, ov_config->height);
    stat |= ov7725_set_pixel_format(context, ov_config->pixel_format);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

void ov7725_power_up(camera_context_t *context)
{
    assert(context->delay_ms != NULL);

    if (context->write_rst) {
        context->write_rst(OV7725_RST_ACTIVE);
    }
    if (context->write_pwdn) {
        context->write_pwdn(OV7725_PWDN_ACTIVE);
    }
    context->delay_ms(5);
    if (context->write_pwdn) {
        context->write_pwdn(OV7725_PWDN_INACTIVE);
    }
    context->delay_ms(2);
    if (context->write_rst) {
        context->write_rst(OV7725_RST_INACTIVE);
    }
    context->delay_ms(20);
}

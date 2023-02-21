/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ov7725.h"

static const uint8_t ov7725_default_regs[][2] = {
    {COM3,          COM3_SWAP_YUV},
    {COM7,          COM7_RES_VGA | COM7_FMT_RGB565},

    {COM4,          0x01}, /* bypass PLL */
    {CLKRC,         0xC0}, /* Res/Bypass pre-scalar */

    /*
     * VGA Window Size
     */
    {HSTART,        0x23},
    {HSIZE,         0xA0},
    {VSTART,        0x07},
    {VSIZE,         0xF0},
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

    {DSP_CTRL2,     DSP_CTRL2_VDCW_EN | DSP_CTRL2_HDCW_EN | DSP_CTRL2_HZOOM_EN | DSP_CTRL2_VZOOM_EN},

    {DSP_CTRL3,     0x00},
    {DSP_CTRL4,     0x00},
    {DSPAUTO,       0xFF},

    {COM8,          0xF0},
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
    {CONTRAST,      0x30},
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
    {COM5,          0xF5},
};

hpm_stat_t ov7725_read_register(camera_context_t *context, uint8_t reg, uint8_t *buf)
{
    return i2c_master_address_read(context->ptr, OV7725_I2C_ADDR, &reg, 1, buf, 1);
}

hpm_stat_t ov7725_write_register(camera_context_t *context, uint8_t reg, uint8_t val)
{
    return i2c_master_address_write(context->ptr, OV7725_I2C_ADDR, &reg, 1, &val, 1);
}

void ov7725_restore_default_values(camera_context_t *context)
{
    uint32_t i;
    for (i = 0; i < (ARRAY_SIZE(ov7725_default_regs)); i++)
    {
        ov7725_write_register(context, ov7725_default_regs[i][0], ov7725_default_regs[i][1]);
    }
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

    ov7725_restore_default_values(context);

    stat |= ov7725_write_register(context, CLKRC, 0x2);
    stat |= ov7725_write_register(context, COM4, 0x41);
    stat |= ov7725_write_register(context, EXHCL, 0);
    stat |= ov7725_write_register(context, DM_LNL, 0);
    stat |= ov7725_write_register(context, DM_LNH, 0);
    stat |= ov7725_write_register(context, ADVFL, 0);
    stat |= ov7725_write_register(context, ADVFH, 0);
    stat |= ov7725_write_register(context, COM5, 0x65);
    stat |= ov7725_write_register(context, COM10, 0);
    stat |= ov7725_write_register(context, COM3, 0);
    stat |= ov7725_write_register(context, COM2, 0x3);
    stat |= ov7725_set_framesize(context, ov_config->width, ov_config->height);
    stat |= ov7725_set_pixel_format(context, ov_config->pixel_format);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

void ov7725_power_up(camera_context_t *context)
{
    assert((context->delay_ms != NULL) && (context->write_rst != NULL) && (context->write_pwdn != NULL));

    context->write_rst(OV7725_RST_ACTIVE);
    context->write_pwdn(OV7725_PWDN_ACTIVE);
    context->delay_ms(5);
    context->write_pwdn(OV7725_PWDN_INACTIVE);
    context->delay_ms(2);
    context->write_rst(OV7725_RST_INACTIVE);
    context->delay_ms(20);
}

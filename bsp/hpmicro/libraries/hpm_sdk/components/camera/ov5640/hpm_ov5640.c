/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ov5640.h"

static const ov5640_reg_val_t ov5640_init_param[] = {
    /* system setting */
    {0x3008, 0x42}, /* software power down, bit[6] */
    {0x3103, 0x03}, /*  system clock from PLL, bit[1] */
    {0x3037, 0x13}, /*  PLL root divider, bit[4], PLL pre-divider, bit[3:0] */
    {0x3108, 0x01}, /*  PCLK root divider, bit[5:4], SCLK2x root divider, bit[3:2], SCLK root divider, bit[1:0] */

    {0x3630, 0x36},
    {0x3631, 0x0e},
    {0x3632, 0xe2},
    {0x3633, 0x12},
    {0x3621, 0xe0},
    {0x3704, 0xa0},
    {0x3703, 0x5a},

    {0x302c, 0xc2}, /* pad control */
    {0x4004, 0x02}, /* BLC 2 lines */
    {0x3002, 0x1c}, /* reset JFIFO, SFIFO, JPEG */
    {0x3006, 0xc3}, /* disable clock of JPEG2x, JPEG */
    {0x4713, 0x03}, /* JPEG mode 3 */
    {0x4407, 0x04}, /* Quantization scale */
    {0x460b, 0x35},
    {0x5001, 0xa3}, /* SDE on, scale on, UV average off, color matrix on, AWB on */
    {0x3503, 0x00}, /* AEC/AGC on */
    {0x3c07, 0x08}, /* light meter 1 threshold [7:0] */
    {0x3820, 0x41}, /* Sensor flip off, ISP flip on */
    {0x3821, 0x07}, /* Sensor mirror on, ISP mirror on, H binning on */
    {0x3618, 0x00},
    {0x3612, 0x29},
    {0x3709, 0x52},
    {0x370c, 0x03},

    {0x3715, 0x78},
    {0x3717, 0x01},
    {0x370b, 0x60},
    {0x3705, 0x1a},
    {0x3905, 0x02},
    {0x3906, 0x10},
    {0x3901, 0x0a},
    {0x3731, 0x12},
    {0x3600, 0x08}, /* VCM control */
    {0x3601, 0x33}, /* VCM control */
    {0x302d, 0x60}, /* system control */
    {0x3620, 0x52},
    {0x371b, 0x20},
    {0x471c, 0x50},
    {0x3a13, 0x43}, /* pre-gain = 1.047x */
    {0x3a18, 0x00}, /* gain ceiling */
    {0x3a19, 0xf8}, /* gain ceiling = 15.5x */
    {0x3635, 0x13},
    {0x3636, 0x03},
    {0x3634, 0x40},
    {0x3622, 0x01},
    /* 50/60Hz detection */
    {0x3a02, 0x0b}, /* 60Hz max exposure, night mode 5fps */
    {0x3a03, 0x88}, /* 60Hz max exposure */
    {0x3a14, 0x0b}, /* 50Hz max exposure, night mode 5fps */
    {0x3a15, 0x88}, /* 50Hz max exposure */
    {0x3c01, 0x34}, /* Band auto, bit[7] */
    {0x3c04, 0x28}, /* threshold low sum */
    {0x3c05, 0x98}, /* threshold high sum */
    {0x3c06, 0x00}, /* light meter 1 threshold[15:8] */
    {0x3c07, 0x08}, /* light meter 1 threshold[7:0] */
    {0x3c08, 0x00}, /* light meter 2 threshold[15:8] */
    {0x3c09, 0x1c}, /* light meter 2 threshold[7:0] */
    {0x3c0a, 0x9c}, /* sample number[15:8] */
    {0x3c0b, 0x40}, /* sample number[7:0] */
    {0x3708, 0x64},
    {0x4001, 0x02}, /* BLC start from line 2 */
    {0x4005, 0x1a}, /* BLC always update */
    {0x3000, 0x00}, /* enable blocks */
    {0x3004, 0xff}, /* enable clocks */
    {0x302e, 0x00},
    {0x440e, 0x00},
    {0x5000, 0xa7}, /* Lenc on, raw gamma on, BPC on, WPC on, CIP on */
    /* AEC target */
    {0x3a0f, 0x30}, /* stable range in high */
    {0x3a10, 0x28}, /* stable range in low */
    {0x3a1b, 0x30}, /* stable range out high */
    {0x3a1e, 0x26}, /* stable range out low */
    {0x3a11, 0x60}, /* fast zone high */
    {0x3a1f, 0x14}, /* fast zone low */
    /* Lens correction */
    {0x5800, 0x23},
    {0x5801, 0x14},
    {0x5802, 0x0f},
    {0x5803, 0x0f},
    {0x5804, 0x12},
    {0x5805, 0x26},
    {0x5806, 0x0c},
    {0x5807, 0x08},
    {0x5808, 0x05},
    {0x5809, 0x05},
    {0x580a, 0x08},
    {0x580b, 0x0d},
    {0x580c, 0x08},
    {0x580d, 0x03},
    {0x580e, 0x00},
    {0x580f, 0x00},
    {0x5810, 0x03},
    {0x5811, 0x09},
    {0x5812, 0x07},
    {0x5813, 0x03},
    {0x5814, 0x00},
    {0x5815, 0x01},
    {0x5816, 0x03},
    {0x5817, 0x08},
    {0x5818, 0x0d},
    {0x5819, 0x08},
    {0x581a, 0x05},
    {0x581b, 0x06},
    {0x581c, 0x08},
    {0x581d, 0x0e},
    {0x581e, 0x29},
    {0x581f, 0x17},
    {0x5820, 0x11},
    {0x5821, 0x11},
    {0x5822, 0x15},
    {0x5823, 0x28},
    {0x5824, 0x46},
    {0x5825, 0x26},
    {0x5826, 0x08},
    {0x5827, 0x26},
    {0x5828, 0x64},
    {0x5829, 0x26},
    {0x582a, 0x24},
    {0x582b, 0x22},
    {0x582c, 0x24},
    {0x582d, 0x24},
    {0x582e, 0x06},
    {0x582f, 0x22},
    {0x5830, 0x40},
    {0x5831, 0x42},
    {0x5832, 0x24},
    {0x5833, 0x26},
    {0x5834, 0x24},
    {0x5835, 0x22},
    {0x5836, 0x22},
    {0x5837, 0x26},
    {0x5838, 0x44},
    {0x5839, 0x24},
    {0x583a, 0x26},
    {0x583b, 0x28},
    {0x583c, 0x42},
    {0x583d, 0xce}, /* lenc BR offset */
    /* AWB */
    {0x5180, 0xff}, /* AWB B block */
    {0x5181, 0xf2}, /* AWB control */
    {0x5182, 0x00}, /* [7:4] max local counter, [3:0] max fast counter */
    {0x5183, 0x14}, /* AWB advanced */
    {0x5184, 0x25},
    {0x5185, 0x24},
    {0x5186, 0x09},
    {0x5187, 0x09},
    {0x5188, 0x09},
    {0x5189, 0x75},
    {0x518a, 0x54},
    {0x518b, 0xe0},
    {0x518c, 0xb2},
    {0x518d, 0x42},
    {0x518e, 0x3d},
    {0x518f, 0x56},
    {0x5190, 0x46},
    {0x5191, 0xf8}, /* AWB top limit */
    {0x5192, 0x04}, /* AWB bottom limit */
    {0x5193, 0x70}, /* red limit */
    {0x5194, 0xf0}, /* green limit */
    {0x5195, 0xf0}, /* blue limit */
    {0x5196, 0x03}, /* AWB control */
    {0x5197, 0x01}, /* local limit */
    {0x5198, 0x04},
    {0x5199, 0x12},
    {0x519a, 0x04},
    {0x519b, 0x00},
    {0x519c, 0x06},
    {0x519d, 0x82},
    {0x519e, 0x38}, /* AWB control */

    /* Gamma */
    {0x5480, 0x01}, /* Gamma bias plus on, bit[0] */
    {0x5481, 0x08},
    {0x5482, 0x14},
    {0x5483, 0x28},
    {0x5484, 0x51},
    {0x5485, 0x65},
    {0x5486, 0x71},
    {0x5487, 0x7d},
    {0x5488, 0x87},
    {0x5489, 0x91},
    {0x548a, 0x9a},
    {0x548b, 0xaa},
    {0x548c, 0xb8},
    {0x548d, 0xcd},
    {0x548e, 0xdd},
    {0x548f, 0xea},
    {0x5490, 0x1d},
    /* color matrix */
    {0x5381, 0x1e}, /* CMX1 for Y */
    {0x5382, 0x5b}, /* CMX2 for Y */
    {0x5383, 0x08}, /* CMX3 for Y */
    {0x5384, 0x0a}, /* CMX4 for U */
    {0x5385, 0x7e}, /* CMX5 for U */
    {0x5386, 0x88}, /* CMX6 for U */
    {0x5387, 0x7c}, /* CMX7 for V */
    {0x5388, 0x6c}, /* CMX8 for V */
    {0x5389, 0x10}, /* CMX9 for V */
    {0x538a, 0x01}, /* sign[9] */
    {0x538b, 0x98}, /* sign[8:1] */
    /* UV adjust */
    {0x5580, 0x06}, /* saturation on, bit[1] */
    {0x5583, 0x40},
    {0x5584, 0x10},
    {0x5003, 0x08},
    {0x5589, 0x10},
    {0x558a, 0x00},
    {0x558b, 0xf8},
    {0x501d, 0x40}, /* enable manual offset of contrast */
    /* CIP */
    {0x5300, 0x08}, /* CIP sharpen MT threshold 1 */
    {0x5301, 0x30}, /* CIP sharpen MT threshold 2 */
    {0x5302, 0x10}, /* CIP sharpen MT offset 1 */
    {0x5303, 0x00}, /* CIP sharpen MT offset 2 */
    {0x5304, 0x08}, /* CIP DNS threshold 1 */
    {0x5305, 0x30}, /* CIP DNS threshold 2 */
    {0x5306, 0x08}, /* CIP DNS offset 1 */
    {0x5307, 0x16}, /* CIP DNS offset 2 */
    {0x5309, 0x08}, /* CIP sharpen TH threshold 1 */
    {0x530a, 0x30}, /* CIP sharpen TH threshold 2 */
    {0x530b, 0x04}, /* CIP sharpen TH offset 1 */
    {0x530c, 0x06}, /* CIP sharpen TH offset 2 */
    {0x5025, 0x00},
    {0x3008, 0x02}, /* wake up from standby, bit[6] */
};

/* Resolution configuration */
static const ov5640_reg_val_t ov5640_resolution_800_480_param[] = {
    {0x3800, 0x00}, {0x3801, 0x00},  {0x3802, 0x00},  {0x3803, 0x04},
    {0x3804, 0x0a}, {0x3805, 0x3f},  {0x3806, 0x07},  {0x3807, 0x9b},
    {0x3808, 0x03}, {0x3809, 0x20},  {0x380A, 0x01},  {0x380B, 0xe0},
    {0x380C, 0x07}, {0x380D, 0x68},  {0x380E, 0x03},  {0x380F, 0xd8},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x06}, {0x3814, 0x31},  {0x3815, 0x31},
};

static const ov5640_reg_val_t ov5640_resolution_vga_param[] = {
    {0x3800, 0x00}, {0x3801, 0x00},  {0x3802, 0x00},  {0x3803, 0x04},
    {0x3804, 0x0a}, {0x3805, 0x3f},  {0x3806, 0x07},  {0x3807, 0x9b},
    {0x3808, 0x02}, {0x3809, 0x80},  {0x380A, 0x01},  {0x380B, 0xe0},
    {0x380C, 0x07}, {0x380D, 0x68},  {0x380E, 0x03},  {0x380F, 0xd8},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x06}, {0x3814, 0x31},  {0x3815, 0x31},
};

static const ov5640_reg_val_t ov5640_resolution_qvga_param[] = {
    {0x3800, 0x00}, {0x3801, 0x00},  {0x3802, 0x00},  {0x3803, 0x04},
    {0x3804, 0x0a}, {0x3805, 0x3f},  {0x3806, 0x07},  {0x3807, 0x9b},
    {0x3808, 0x01}, {0x3809, 0x40},  {0x380A, 0x00},  {0x380B, 0xf0},
    {0x380C, 0x07}, {0x380D, 0x68},  {0x380E, 0x03},  {0x380F, 0xd8},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x06}, {0x3814, 0x31},  {0x3815, 0x31},
};

static const ov5640_reg_val_t ov5640_resolution_480_272_param[] = {
    {0x3800, 0x00}, {0x3801, 0x00},  {0x3802, 0x00},  {0x3803, 0xfa},
    {0x3804, 0x0a}, {0x3805, 0x3f},  {0x3806, 0x06},  {0x3807, 0xa9},
    {0x3808, 0x01}, {0x3809, 0xE0},  {0x380A, 0x01},  {0x380B, 0x10},
    {0x380C, 0x07}, {0x380D, 0x64},  {0x380E, 0x02},  {0x380F, 0xe4},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x04}, {0x3814, 0x31},  {0x3815, 0x31},
};

static const ov5640_reg_val_t ov5640_resolution_720p_param[] = {
    {0x3800, 0x00}, {0x3801, 0x00},  {0x3802, 0x00},  {0x3803, 0xfa},
    {0x3804, 0x0a}, {0x3805, 0x3f},  {0x3806, 0x06},  {0x3807, 0xa9},
    {0x3808, 0x05}, {0x3809, 0x00},  {0x380A, 0x02},  {0x380B, 0xd0},
    {0x380C, 0x07}, {0x380D, 0x64},  {0x380E, 0x02},  {0x380F, 0xe4},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x04}, {0x3814, 0x31},  {0x3815, 0x31},
};

static const ov5640_reg_val_t ov5640_resolution_1080p_param[] = {
    {0x3800, 0x01}, {0x3801, 0x50},  {0x3802, 0x01},  {0x3803, 0xb2},
    {0x3804, 0x08}, {0x3805, 0xef},  {0x3806, 0x05},  {0x3807, 0xf1},
    {0x3808, 0x07}, {0x3809, 0x80},  {0x380A, 0x04},  {0x380B, 0x38},
    {0x380C, 0x09}, {0x380D, 0xc4},  {0x380E, 0x04},  {0x380F, 0x60},
    {0x3810, 0x00}, {0x3811, 0x10},  {0x3812, 0x00},  {0x3813, 0x04}, {0x3814, 0x11},  {0x3815, 0x11},
};

/* DVP clock */
static const ov5640_clock_config_t ov5640_dvp_clock_configs[] = {
    {
        .resolution  = (uint32_t)video_resolution_800_480,
        .pllctrl1    = 0x11,
        .pllctrl2    = 0x46,
        .vfifoctrl0c = 0x22,
        .pclkdiv     = 0x02,
        .pclkperiod  = 0x22,
    },
    {
        .resolution  = (uint32_t)video_resolution_vga,
        .pllctrl1    = 0x11,
        .pllctrl2    = 0x46,
        .vfifoctrl0c = 0x22,
        .pclkdiv     = 0x02,
        .pclkperiod  = 0x22,
    },
    {
        .resolution  = (uint32_t)video_resolution_qvga,
        .pllctrl1    = 0x11,
        .pllctrl2    = 0x46,
        .vfifoctrl0c = 0x22,
        .pclkdiv     = 0x02,
        .pclkperiod  = 0x22,
    },
    {
        .resolution  = (uint32_t)video_resolution_480_272,
        .pllctrl1    = 0x21,
        .pllctrl2    = 0x69,
        .vfifoctrl0c = 0x20,
        .pclkdiv     = 0x04,
        .pclkperiod  = 0x16,
    },
    {
        .resolution  = (uint32_t)video_resolution_720p,
        .pllctrl1    = 0x21,
        .pllctrl2    = 0x69,
        .vfifoctrl0c = 0x20,
        .pclkdiv     = 0x04,
        .pclkperiod  = 0x16,
    },
    {
        .resolution  = (uint32_t)video_resolution_1080p,
        .pllctrl1    = 0x21,
        .pllctrl2    = 0x69,
        .vfifoctrl0c = 0x20,
        .pclkdiv     = 0x04,
        .pclkperiod  = 0x16,
    },
};

static const ov5640_light_mode_config_t ov5640_light_mode_configs[] = {
    /* Auto. */
    {
        .lightmode = camera_light_mode_auto,
        .awbctrl   = 0x00,
        .awbr_h    = 0x04,
        .awbr_l    = 0x00,
        .awbg_h    = 0x04,
        .awbg_l    = 0x00,
        .awbb_h    = 0x04,
        .awbb_l    = 0x00,
    },
    /* Sunny. */
    {
        .lightmode = camera_light_mode_sunny,
        .awbctrl   = 0x01,
        .awbr_h    = 0x06,
        .awbr_l    = 0x1c,
        .awbg_h    = 0x04,
        .awbg_l    = 0x00,
        .awbb_h    = 0x04,
        .awbb_l    = 0xf3,
    },
    /* Office. */
    {
        .lightmode = camera_light_mode_office,
        .awbctrl   = 0x01,
        .awbr_h    = 0x05,
        .awbr_l    = 0x48,
        .awbg_h    = 0x04,
        .awbg_l    = 0x00,
        .awbb_h    = 0x07,
        .awbb_l    = 0xcf,
    },
    /* Cloudy. */
    {
        .lightmode = camera_light_mode_cloudy,
        .awbctrl   = 0x01,
        .awbr_h    = 0x06,
        .awbr_l    = 0x48,
        .awbg_h    = 0x04,
        .awbg_l    = 0x00,
        .awbb_h    = 0x04,
        .awbb_l    = 0xd3,
    },
    /* Home. */
    {
        .lightmode = camera_light_mode_home,
        .awbctrl   = 0x01,
        .awbr_h    = 0x04,
        .awbr_l    = 0x10,
        .awbg_h    = 0x04,
        .awbg_l    = 0x00,
        .awbb_h    = 0x08,
        .awbb_l    = 0x40,
    },
};

static const ov5640_special_effect_config_t ov5640_special_effect_configs[] = {
    /* Normal. */
    {
        .effect   = camera_special_effect_normal,
        .sdectrl0 = 0x06,
        .sdectrl3 = 0x40,
        .sdectrl4 = 0x10,
    },
    /* Bluish. */
    {
        .effect   = camera_special_effect_bluish,
        .sdectrl0 = 0x1e,
        .sdectrl3 = 0xa0,
        .sdectrl4 = 0x40,
    },
    /* Redish. */
    {
        .effect   = camera_special_effect_redish,
        .sdectrl0 = 0x1e,
        .sdectrl3 = 0x80,
        .sdectrl4 = 0xc0,
    },
    /* B & W */
    {
        .effect   = camera_special_effect_bw,
        .sdectrl0 = 0x1e,
        .sdectrl3 = 0x80,
        .sdectrl4 = 0x80,
    },
    /* Sepia. */
    {
        .effect   = camera_special_effect_sepia,
        .sdectrl0 = 0x1e,
        .sdectrl3 = 0x40,
        .sdectrl4 = 0xa0,
    },
    /* Negtive. */
    {
        .effect   = camera_special_effect_negtive,
        .sdectrl0 = 0x40,
        .sdectrl3 = 0x40,
        .sdectrl4 = 0x10,
    },
    /* Greenish. */
    {
        .effect   = camera_special_effect_greenish,
        .sdectrl0 = 0x1e,
        .sdectrl3 = 0x60,
        .sdectrl4 = 0x60,
    },
};

static const ov5640_clock_config_t *ov5640_get_clock_config(const camera_config_t *config)
{
    uint32_t i;

    if (camera_interface_dvp == config->interface) {
        for (i = 0; i < ARRAY_SIZE(ov5640_dvp_clock_configs); i++) {
            if (HPM_CAMERA_RESOLUTION(config->width, config->height) == ov5640_dvp_clock_configs[i].resolution) {
                return &ov5640_dvp_clock_configs[i];
            }
        }
    }

    return NULL;
}

hpm_stat_t ov5640_read_register(camera_context_t *context, uint16_t reg, uint8_t *buf)
{
    uint8_t r[2];
    r[0] = reg >> 8;
    r[1] = reg & 0xFF;

    hpm_stat_t stat = i2c_master_write(context->ptr, context->i2c_device_addr, r, 2);
    if (stat != status_success) {
        return stat;
    }
    return i2c_master_read(context->ptr, context->i2c_device_addr, buf, 1);
}

hpm_stat_t ov5640_write_register(camera_context_t *context, uint16_t reg, uint8_t val)
{
    uint8_t r[2];
    r[0] = reg >> 8;
    r[1] = reg & 0xFF;
    return i2c_master_address_write(context->ptr, context->i2c_device_addr, r, sizeof(r), &val, 1);
}

hpm_stat_t ov5640_write_multi_registers(camera_context_t *context, const ov5640_reg_val_t regval[], uint32_t len)
{
    uint32_t i;
    hpm_stat_t stat = status_success;

    for (i = 0; i < len; i++) {
        HPM_CHECK_RET(ov5640_write_register(context, regval[i].regaddr, regval[i].regval));
    }

    return stat;
}

hpm_stat_t ov5640_software_reset(camera_context_t *context)
{
    hpm_stat_t stat = status_success;

    HPM_CHECK_RET(ov5640_write_register(context, 0x3103, 0x11));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3008, 0x82));

    return stat;
}

hpm_stat_t ov5640_set_pixel_format(camera_context_t *context, display_pixel_format_t pixel_format)
{
    hpm_stat_t stat = status_success;

    switch (pixel_format) {
    case display_pixel_format_y8:
    case display_pixel_format_yuv422:
        HPM_CHECK_RET(ov5640_write_register(context, 0x4300, 0x30));
        HPM_CHECK_RET(ov5640_write_register(context, 0x501f, 0x00));
        break;
    case display_pixel_format_rgb565:
        HPM_CHECK_RET(ov5640_write_register(context, 0x4300, 0x6F));
        HPM_CHECK_RET(ov5640_write_register(context, 0x501f, 0x01));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }

    return stat;
}

hpm_stat_t ov5640_check_chip_id(camera_context_t *context)
{
    hpm_stat_t stat = status_success;
    uint8_t val_h = 0;
    uint8_t val_l = 0;

    HPM_CHECK_RET(ov5640_read_register(context, OV5640_CHIP_ID_HIGH_BYTE_ADDR, &val_h));
    HPM_CHECK_RET(ov5640_read_register(context, OV5640_CHIP_ID_LOW_BYTE_ADDR, &val_l));

    if (val_h != OV5640_CHIP_ID_HIGH_BYTE_VALUE) {
        return status_fail;
    }

    if (val_l != OV5640_CHIP_ID_LOW_BYTE_VALUE) {
        return status_fail;
    }

    return stat;
}

hpm_stat_t ov5640_set_image_size(camera_context_t *context, camera_config_t *ov_config)
{
    hpm_stat_t stat = status_success;

    switch (HPM_CAMERA_RESOLUTION(ov_config->width, ov_config->height)) {
    case video_resolution_800_480:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_800_480_param, ARRAY_SIZE(ov5640_resolution_800_480_param));
        break;
    case video_resolution_vga:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_vga_param, ARRAY_SIZE(ov5640_resolution_vga_param));
        break;
    case video_resolution_qvga:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_qvga_param, ARRAY_SIZE(ov5640_resolution_qvga_param));
        break;
    case video_resolution_480_272:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_480_272_param, ARRAY_SIZE(ov5640_resolution_480_272_param));
        break;
    case video_resolution_720p:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_720p_param, ARRAY_SIZE(ov5640_resolution_720p_param));
        break;
    case video_resolution_1080p:
        stat = ov5640_write_multi_registers(context, ov5640_resolution_1080p_param, ARRAY_SIZE(ov5640_resolution_1080p_param));
        break;
    default:
        stat = status_invalid_argument;
        break;
    }

    return stat;
}

hpm_stat_t ov5640_set_clock_config(camera_context_t *context, camera_config_t *ov_config)
{
    hpm_stat_t stat = status_success;
    const ov5640_clock_config_t *clock_config = ov5640_get_clock_config(ov_config);

    if (NULL == clock_config) {
        return status_invalid_argument;
    }

    HPM_CHECK_RET(ov5640_write_register(context, 0x3035, clock_config->pllctrl1));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3036, clock_config->pllctrl2));
    HPM_CHECK_RET(ov5640_write_register(context, 0x460c, clock_config->vfifoctrl0c));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3824, clock_config->pclkdiv));
    HPM_CHECK_RET(ov5640_write_register(context, 0x4837, clock_config->pclkperiod));

    return stat;
}

hpm_stat_t ov5640_set_interface(camera_context_t *context, camera_config_t *ov_config)
{
    hpm_stat_t stat = status_success;

    if (camera_interface_dvp == ov_config->interface) {
        HPM_CHECK_RET(ov5640_write_register(context, 0x3034, 0x1a));

        /* Set Frex, Vsync, Href, PCLK, data, GPIO to output. */
        HPM_CHECK_RET(ov5640_write_register(context, 0x3017, 0xFF));
        HPM_CHECK_RET(ov5640_write_register(context, 0x3018, 0xFF));

        /* DVP mode */
        HPM_CHECK_RET(ov5640_write_register(context, 0x300e, 0x58));
    }

    return stat;
}

hpm_stat_t ov5640_start(camera_context_t *context)
{
    return ov5640_write_register(context, 0x3008, 0x02);
}

hpm_stat_t ov5640_stop(camera_context_t *context)
{
    return ov5640_write_register(context, 0x3008, 0x42);
}

hpm_stat_t ov5640_flip(camera_context_t *context)
{
    hpm_stat_t stat = status_success;
    HPM_CHECK_RET(ov5640_write_register(context, 0x3821, 1));
    return stat;
}


hpm_stat_t ov5640_set_brightness(camera_context_t *context, int32_t brightness)
{
     hpm_stat_t stat = status_success;

    if ((brightness < -4) || (brightness > 4)) {
        return status_invalid_argument;
    }

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x03));
    if (brightness >= 0) {
        HPM_CHECK_RET(ov5640_write_register(context, 0x5588, 0x01));
    } else {
        brightness = -brightness;
        HPM_CHECK_RET(ov5640_write_register(context, 0x5588, 0x09));
    }

    HPM_CHECK_RET(ov5640_write_register(context, 0x5587, ((uint8_t)brightness) << 4U));

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x13));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0xa3));

    return stat;
}

hpm_stat_t ov5640_set_contrast(camera_context_t *context, int32_t contrast)
{
    hpm_stat_t stat = status_success;
    uint8_t regval;

    if ((-4 > contrast) || (4 < contrast)) {
        return status_invalid_argument;
    }

    contrast = 0x20 + contrast * 0x04;
    regval   = (uint8_t)contrast;

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x03));

    HPM_CHECK_RET(ov5640_write_register(context, 0x5580, 0x04));
    HPM_CHECK_RET(ov5640_write_register(context, 0x5585, regval));
    HPM_CHECK_RET(ov5640_write_register(context, 0x5586, regval));

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x13));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0xa3));

    return stat;
}

hpm_stat_t ov5640_set_saturation(camera_context_t *context, int32_t saturation)
{
    hpm_stat_t stat = status_success;
    uint8_t regval;

    if ((-4 > saturation) || (4 < saturation)) {
        return status_invalid_argument;
    }

    saturation = 0x40 + saturation * 0x10;
    regval     = (uint8_t)saturation;

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x03));

    HPM_CHECK_RET(ov5640_write_register(context, 0x5580, 0x02));
    HPM_CHECK_RET(ov5640_write_register(context, 0x5583, regval));
    HPM_CHECK_RET(ov5640_write_register(context, 0x5584, regval));
    HPM_CHECK_RET(ov5640_write_register(context, 0x5588, 0x41));

    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x13));
    HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0xa3));

    return stat;
}

hpm_stat_t ov5640_set_light_mode(camera_context_t *context, int32_t lightmode)
{
    hpm_stat_t stat = status_success;
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(ov5640_light_mode_configs); i++) {
        if (lightmode == (int32_t)ov5640_light_mode_configs[i].lightmode) {
            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x03));

            HPM_CHECK_RET(ov5640_write_register(context, 0x3406, ov5640_light_mode_configs[i].awbctrl));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3400, ov5640_light_mode_configs[i].awbr_h));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3401, ov5640_light_mode_configs[i].awbr_l));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3402, ov5640_light_mode_configs[i].awbg_h));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3403, ov5640_light_mode_configs[i].awbg_l));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3404, ov5640_light_mode_configs[i].awbb_h));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3405, ov5640_light_mode_configs[i].awbb_l));

            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x13));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0xa3));

            return stat;
        }
    }

    /* No configuration found. */
    return status_invalid_argument;
}

hpm_stat_t ov5640_set_special_effect(camera_context_t *context, int32_t effect)
{
    hpm_stat_t stat = status_success;
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(ov5640_special_effect_configs); i++) {
        if (effect == (int32_t)ov5640_special_effect_configs[i].effect) {
            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x03));

            HPM_CHECK_RET(ov5640_write_register(context, 0x5580, ov5640_special_effect_configs[i].sdectrl0));
            HPM_CHECK_RET(ov5640_write_register(context, 0x5583, ov5640_special_effect_configs[i].sdectrl3));
            HPM_CHECK_RET(ov5640_write_register(context, 0x5584, ov5640_special_effect_configs[i].sdectrl4));

            HPM_CHECK_RET(ov5640_write_register(context, 0x5003, 0x08));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0x13));
            HPM_CHECK_RET(ov5640_write_register(context, 0x3212, 0xa3));

            return stat;
        }
    }

    /* No configuration found. */
    return status_invalid_argument;
}

hpm_stat_t ov5640_init(camera_context_t *context, camera_config_t *ov_config)
{
    hpm_stat_t stat = status_success;

    /* check the chip id */
    HPM_CHECK_RET(ov5640_check_chip_id(context));

    /* Initialize: load registers value */
    HPM_CHECK_RET(ov5640_write_multi_registers(context, ov5640_init_param, ARRAY_SIZE(ov5640_init_param)));

    /* configure image windowing */
    HPM_CHECK_RET(ov5640_set_image_size(context, ov_config));

    HPM_CHECK_RET(ov5640_flip(context));

    /* configure Pixel format */
    HPM_CHECK_RET(ov5640_set_pixel_format(context, ov_config->pixel_format));

    /* configure PCLK clock */
    HPM_CHECK_RET(ov5640_set_clock_config(context, ov_config));

    /* configure interface */
    HPM_CHECK_RET(ov5640_set_interface(context, ov_config));

    /* configure contrast */
    HPM_CHECK_RET(ov5640_set_contrast(context, 2));

    /* camera start */
    HPM_CHECK_RET(ov5640_write_register(context, 0x3008, 0x02));

    return stat;
}

void ov5640_power_up(camera_context_t *context)
{
    assert((context->delay_ms != NULL) && (context->write_rst != NULL) && (context->write_pwdn != NULL));

    context->write_rst(OV5640_RST_ACTIVE);
    context->write_pwdn(OV5640_PWDN_ACTIVE);
    context->delay_ms(5);
    context->write_pwdn(OV5640_PWDN_INACTIVE);
    context->delay_ms(2);
    context->write_rst(OV5640_RST_INACTIVE);
    context->delay_ms(20);
}

/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_ov5640.c
 * @brief This file provides firmware functions of the camera ov5640 driver
 *        library for the board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-09-30       CDT             Optimize comments
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ov5640.h"
#include "ev_hc32f4a0_lqfp176_ov5640.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_OV5640 EV_HC32F4A0_LQFP176 OV5640
 * @{
 */

#if ((BSP_OV5640_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup EV_HC32F4A0_LQFP176_OV5640_Local_Functions
 * @{
 */
static void CAM_Port_Init(void);

static void BSP_OV5640_I2C_Delay(uint32_t u32Delay);
static void BSP_OV5640_I2C_Init(void);
static void BSP_OV5640_I2C_Write(const uint8_t au8Reg[], uint8_t u8RegLen, const uint8_t au8Buf[], uint32_t u32Len);
static void BSP_OV5640_I2C_Read(const uint8_t au8Reg[], uint8_t u8RegLen, uint8_t au8Buf[], uint32_t u32Len);
/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/**
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Local_Variables EV_HC32F4A0_LQFP176 OV5640 Local Variables
 * @{
 */
const static stc_ov5640_ll_t m_stcOv5640LL = {
    .Delay         = BSP_OV5640_I2C_Delay,
    .Init          = BSP_OV5640_I2C_Init,
    .Write         = BSP_OV5640_I2C_Write,
    .Read          = BSP_OV5640_I2C_Read,
};

static const stc_ov5640_reg_value_t m_astcOv5640InitRegTable[] = {
    /* input clock: 24Mhz, PCLK: 11.4Mhz */
    {0x3008, 0x42}, /* b7:software reset <> b6:software power down <> b5~b0:reserved */
    {0x3017, 0xFF}, /* b7:FREX <> b6:VSYNC <> b5:HREF <> b4:PCLK <> b3~0:D[9:6] output enable */
    {0x3018, 0xFF}, /* b7~2:D[5:0] <> b1~0:GPIO[1:0] output enable */
    {0x3034, 0x1A}, /* b7:reserved <> b6~b4:PLL charge pump control <> b3~b0:MIPI bit mode */
    {0x3037, 0x13}, /* b7~b5:reserved <> b4:PLL root bypass or divider/2
                       b3~b0:PLL pre-divider 1\1\2\3\4\1.5\6\2.5\8\1\1\1\1\1\1\1 */

    /* SCCB control */
    {0x3103, 0x03}, /* b1:system clock from PAD or PLL <> b7~b2&&b0:reserved */
    {0x3108, 0x01}, /* b7~b6:reserved <> b5~b4:PCLK <> b3~b2:SCLK2x <> b1~b0:SCLK root divider 1/2/4/8 */

    {0x3630, 0x36},
    {0x3631, 0x0E},
    {0x3632, 0xE2},
    {0x3633, 0x12},
    {0x3621, 0xE0},
    {0x3704, 0xA0},
    {0x3703, 0x5A},
    {0x3715, 0x78},
    {0x3717, 0x01},
    {0x370B, 0x60},
    {0x3705, 0x1A},
    {0x3905, 0x02},
    {0x3906, 0x10},
    {0x3901, 0x0A},
    {0x3731, 0x12},
    {0x3600, 0x08}, /* VCM control */
    {0x3601, 0x33}, /* VCM control */
    {0x302D, 0x60}, /* system control */
    {0x3620, 0x52},
    {0x371B, 0x20},
    {0x471C, 0x50},

    /* auto gain control(AGC) */
    {0x3A13, 0x43}, /* b7:reserved <> b6:pre-gain enable <> b5~b0:pre-gain value=1.047x */
    {0x3A18, 0x00}, /* b7~b2:reserved <> b1~b0:gain ceiling[9:8] */
    {0x3A19, 0xF8}, /* b7~b0:gain ceiling[7:0]=15.5x */

    {0x3635, 0x13},
    {0x3636, 0x03},
    {0x3634, 0x40},
    {0x3622, 0x01},

    /* 50/60Hz detection */
    {0x3C01, 0x34}, /* b7:band manual or auto <> b6:band begin reset <> b5:sum auto mode <>
                       b4:band count enable <> b3~b0:band counter threshold */
    {0x3C04, 0x28}, /* b7~b0:threshold low sum */
    {0x3C05, 0x98}, /* b7~b0:threshold high sum */
    {0x3C06, 0x00}, /* b7~b0:light meter 1 threshold[15:8] */
    {0x3C07, 0x08}, /* b7~b0:light meter 1 threshold[7:0] */
    {0x3C08, 0x00}, /* b7~b0:light meter 2 threshold[15:8] */
    {0x3C09, 0x1C}, /* b7~b0:light meter 2 threshold[7:0] */
    {0x3C0A, 0x9C}, /* b7~b0:sample number[15:8] */
    {0x3C0B, 0x40}, /* b7~b0:sample number[7:0] */

    /* image windowing */
    {0x3810, 0x00}, /* b7~b4:reserved <> b3~b0:Timing Hoffset[11:8] */
    {0x3811, 0x10}, /* b7~b0:Timing Hoffset[7:0] */
    {0x3812, 0x00}, /* b7~b3:reserved <> b2~b0:Timing Voffset[10:8] */
    {0x3708, 0x64},

    /* black level calibration(BLC) */
    {0x4001, 0x02}, /* b7~b6:reserved <> b5~b0:BLC start line */
    {0x4005, 0x1A}, /* b7~b2:reserved <> b1:BLC update always or normal freeze <> b0:reserved */

    /* system control:DVP enable */
    {0x3000, 0x00}, /* b7~b0:blocks reset control reset or enable */
    {0x3004, 0xFF}, /* b7~b0:blocks clock control enable or disable */
    {0x300E, 0x58}, /* b7~b3:MIPI about(MIPI power down) <> b2:MIPI/DVP select <> b1~b0:reserved */
    {0x302E, 0x00},

    /* format control */
    {0x4300, 0x30}, /* YUV422,YUYV */
    {0x501F, 0x00}, /* YUV 422 */
    {0x440E, 0x00}, /* JPEG control */

    /* image sensor processor (ISP) */
    {0x5000, 0xA7}, /* b7:lenc on <> b5:raw gamma on <> b2:BPC on <> b1:WPC on <> b0:CIP on */

    /* auto exposure control (AEC) */
    {0x3A0F, 0x30}, /* b7~b0:stable range in high */
    {0x3A10, 0x28}, /* b7~b0:stable range in low */
    {0x3A1B, 0x30}, /* b7~b0:stable range out high */
    {0x3A1E, 0x26}, /* b7~b0:stable range out low */
    {0x3A11, 0x60}, /* b7~b0:fast zone high */
    {0x3A1F, 0x14}, /* b7~b0:fast zone low */

    /* lens correction (LENC) */
    {0x5800, 0x23}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5801, 0x14}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5802, 0x0F}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5803, 0x0F}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5804, 0x12}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5805, 0x26}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5806, 0x0C}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5807, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5808, 0x05}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5809, 0x05}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580A, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580B, 0x0D}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580C, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580D, 0x03}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580E, 0x00}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x580F, 0x00}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5810, 0x03}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5811, 0x09}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5812, 0x07}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5813, 0x03}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5814, 0x00}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5815, 0x01}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5816, 0x03}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5817, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5818, 0x0D}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5819, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581A, 0x05}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581B, 0x06}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581C, 0x08}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581D, 0x0E}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581E, 0x29}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x581F, 0x17}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5820, 0x11}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5821, 0x11}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5822, 0x15}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5823, 0x28}, /* b7~b6:reserved <> b5~b0:green matrix */
    {0x5824, 0x46}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5825, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5826, 0x08}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5827, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5828, 0x64}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5829, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582A, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582B, 0x22}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582C, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582D, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582E, 0x06}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x582F, 0x22}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5830, 0x40}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5831, 0x42}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5832, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5833, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5834, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5835, 0x22}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5836, 0x22}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5837, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5838, 0x44}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x5839, 0x24}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x583A, 0x26}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x583B, 0x28}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x583C, 0x42}, /* b7~b4:blue matrix <> b3~b0:red matrix */
    {0x583D, 0xCE}, /* b7~b4:lenc b offset <> b3~b0:lenc r offset */

    /* auto white balance(AWB) */
    {0x5180, 0xFF}, /* b7~b0:AWB B block */
    {0x5181, 0xF2}, /* b7~b6:step local <> b5~b4:step fast <> b3:slop 8x <> b2:slop 4x <> b1:one zone <> b0:AVG all */
    {0x5182, 0x00}, /* b7~b4:max local counter <> b3~b0:max fast counter */
    {0x5183, 0x14}, /* b7:AWB simple or advanced <> b6:YUV enable <> b5:AWB preset <> b4:AWB SIMF <> b3~b2:AWB win */
    {0x5184, 0x25}, /* b7~b6:count area <> b5:G enable <> b4~b2:count limit <> b1~b0:count threshold */
    {0x5185, 0x24}, /* b7~b4:stable range unstable <> b3~b0:stable range stable */
    {0x5186, 0x09}, /* about advance */
    {0x5187, 0x09}, /* about advance */
    {0x5188, 0x09}, /* about advance */
    {0x5189, 0x75}, /* about advance */
    {0x518A, 0x54}, /* about advance */
    {0x518C, 0xE0}, /* about advance */
    {0x518C, 0xB2}, /* about advance */
    {0x518D, 0x42}, /* about advance */
    {0x518E, 0x3D}, /* about advance */
    {0x518F, 0x56}, /* about advance */
    {0x5190, 0x46}, /* about advance */
    {0x5191, 0xF8}, /* b7~b0:AWB top limit */
    {0x5192, 0x04}, /* b7~b0:AWB bottom limit */
    {0x5193, 0x70}, /* b7~b0:red limit */
    {0x5194, 0xF0}, /* b7~b0:green limit */
    {0x5195, 0xF0}, /* b7~b0:blue limit */
    {0x5196, 0x03}, /* b7~b6:reserved <> b5:AWB freeze <> b4:reserved <>
                       b3~b2:simple select <> b1:fast enable <> b0:AWB bias stat */
    {0x5197, 0x01}, /* b7~b0:local limit */
    {0x5198, 0x04},
    {0x5199, 0x12},
    {0x519A, 0x04},
    {0x519B, 0x00},
    {0x519C, 0x06},
    {0x519D, 0x82},
    {0x519E, 0x38}, /* b7~b4:reserved <> b3:local limit select <> b2:simple stable select <> b1~b0:reserved */

    /* raw gamma(GMA) */
    {0x5480, 0x01}, /* b7~b2:reserved <> b1:YSLP15 manual enable <> b0:gamma bias plus on */
    {0x5481, 0x08}, /* b7~b0:Y yst */
    {0x5482, 0x14}, /* b7~b0:Y yst */
    {0x5483, 0x28}, /* b7~b0:Y yst */
    {0x5484, 0x51}, /* b7~b0:Y yst */
    {0x5485, 0x65}, /* b7~b0:Y yst */
    {0x5486, 0x71}, /* b7~b0:Y yst */
    {0x5487, 0x7D}, /* b7~b0:Y yst */
    {0x5488, 0x87}, /* b7~b0:Y yst */
    {0x5489, 0x91}, /* b7~b0:Y yst */
    {0x548A, 0x9A}, /* b7~b0:Y yst */
    {0x548B, 0xAA}, /* b7~b0:Y yst */
    {0x548C, 0xB8}, /* b7~b0:Y yst */
    {0x548D, 0xCD}, /* b7~b0:Y yst */
    {0x548E, 0xDD}, /* b7~b0:Y yst */
    {0x548F, 0xEA}, /* b7~b0:Y yst */
    {0x5490, 0x1D}, /* b7~b0:Y yst */

    /* color matrix(CMX) */
    {0x5381, 0x1E}, /* b7~b0:CMX1 for Y */
    {0x5382, 0x5B}, /* b7~b0:CMX2 for Y */
    {0x5383, 0x08}, /* b7~b0:CMX3 for Y */
    {0x5384, 0x0A}, /* b7~b0:CMX4 for U */
    {0x5385, 0x7E}, /* b7~b0:CMX5 for U */
    {0x5386, 0x88}, /* b7~b0:CMX6 for U */
    {0x5387, 0x7C}, /* b7~b0:CMX7 for V */
    {0x5388, 0x6C}, /* b7~b0:CMX8 for V */
    {0x5389, 0x10}, /* b7~b0:CMX9 for V */
    {0x538A, 0x01}, /* b7~b1:reserved <> b0:CMX9 sign */
    {0x538B, 0x98}, /* b7~b0:CMX8~1 sign */

    /* special digital effects (SDE):(UV adjust) */
    {0x5580, 0x06}, /* b7:fixed Y enable <> b6:negative enable <> b5:gray enable <> b4:dixed V enable
                       b3:fixed U enable <> b2:contrast enable <> b1:saturation enable <> b0:hue enable */
    {0x5583, 0x40}, /* b7~b0:max value for UV adjust */
    {0x5584, 0x10}, /* b7~b0:min value for UV adjust */
    {0x5589, 0x10}, /* b7~b0:UV adjust threshold 1 valid */
    {0x558A, 0x00}, /* b7~b1:reserved <> b0:UV adjust threshold 2 valid */
    {0x558B, 0xF8}, /* b7~b0:UV adjust threshold 2 valid */
    {0x501D, 0x40}, /* enable manual offset of contrast */

    /* color interpolation (CIP) */
    {0x5300, 0x08}, /* b7~b0:CIP sharpen MT threshold 1 */
    {0x5301, 0x30}, /* b7~b0:CIP sharpen MT threshold 2 */
    {0x5302, 0x10}, /* b7~b0:CIP sharpen MT offset 1 */
    {0x5303, 0x00}, /* b7~b0:CIP sharpen MT offset 2 */
    {0x5304, 0x08}, /* b7~b0:CIP DNS threshold 1 */
    {0x5305, 0x30}, /* b7~b0:CIP DNS threshold 2 */
    {0x5306, 0x08}, /* b7~b0:CIP DNS offset 1 */
    {0x5307, 0x16}, /* b7~b0:CIP DNS offset 2 */

    {0x5309, 0x08}, /* b7~b0:CIP sharpen TH threshold 1 */
    {0x530A, 0x30}, /* b7~b0:CIP sharpen TH threshold 2 */
    {0x530B, 0x04}, /* b7~b0:CIP sharpen TH offset 1 */
    {0x530D, 0x06}, /* b7~b0:CIP sharpen TH offset 2 */
    {0x5025, 0x00},

    /* system control:wake up from standby */
    {0x3008, 0x02}, /* b7:software reset <> b6:software power down <> b5~b0:reserved */

    /* DVP control */
    {0x4740, 0x21}, /* b7~b6:reserved <> b5:PCLK polarity H/L <> b4:reserved <> b3:gate PCLK under VSYNC <>
                       b2:gate PCLK under HREF <> b1:HREF polarity H/L <> b0:VSYNC polarity H/L */

    {0x4740, 0x21},
};

/* RGB565 mode: frame-rate 8fps, max-out: 1528*900 */
static const stc_ov5640_reg_value_t m_astcOv5640Rgb565RegTable[] = {
    {0x4300, 0x6F},
    {0x501F, 0x01},
    /* input clock: 24Mhz, PCLK: 11.4Mhz */
    {0x3035, 0x41}, /* b7~b4:system clock divider slow down all clocks
                       b3~b0:scale divider for MIPI PCLK/SERCLK can be slowed down */

    {0x3036, 0x39}, /* b7~b0:PLL multiplier
                       a0: 64M NG
                       9c: 62M OK
                       98: 60M OK
                       90: 58M OK */
    {0x3C07, 0x07}, /* lightmeter 1 threshold[7:0] */

    /* timing control */
    {0x3820, 0x46}, /* b7~b3:reserved <> b2:ISP vflip <> b1:sensor vflip <> b0:reserved */
    {0x3821, 0x00}, /* b7~b6:reserved <> b5:JPEG enable <> b4~b3:reserved <>
                       b2:ISP mirror <> b1:sensor mirror <> b0:horizontal binning enable */
    {0x3814, 0x31}, /* b7~b4:horizontal odd subsample increment <> b3~b0:even */
    {0x3815, 0x31}, /* b7~b4:vertical odd subsample increment <> b3~b0:even */
    {0x3800, 0x00}, /* b7~b4:reserved <> b3~b0:X address start[11:8] */
    {0x3801, 0x00}, /* b7~b0:X address start[7:0] */
    {0x3802, 0x00}, /* b7~b4:reserved <> b3~b0:Y address start[11:8] */
    {0x3803, 0x00}, /* b7~b0:Y address start[7:0] */
    {0x3804, 0x0A}, /* b7~b4:reserved <> b3~b0:X address end[11:8] */
    {0x3805, 0x3F}, /* b7~b0:X address end[7:0] */
    {0x3806, 0x06}, /* b7~b3:reserved <> b2~b0:Y address end[10:8] */
    {0x3807, 0xA9}, /* b7~b0:Y address end[7:0] */
    {0x3808, 0x05}, /* DVPHO */
    {0x3809, 0x00}, /* DVPHO */
    {0x380A, 0x02}, /* DVPVO */
    {0x380B, 0xD0}, /* DVPVO */
    {0x380C, 0x05}, /* HTS */
    {0x380D, 0xF8}, /* HTS */
    {0x380E, 0x03}, /* VTS */
    {0x380F, 0x84}, /* VTS */
    {0x3813, 0x04}, /* timing V offset */
    {0x3618, 0x00},
    {0x3612, 0x29},
    {0x3709, 0x52},
    {0x370C, 0x03},
    {0x3A02, 0x02}, /* 60Hz max exposure */
    {0x3A03, 0xE0}, /* 60Hz max exposure */

    {0x3A14, 0x02}, /* 50Hz max exposure */
    {0x3A15, 0xE0}, /* 50Hz max exposure */
    {0x4004, 0x02}, /* BLC line number */
    {0x3002, 0x1C}, /* reset JFIFO, SFIFO, JPG */
    {0x3006, 0xC3}, /* disable clock of JPEG2x, JPEG */
    {0x4713, 0x03}, /* JPEG mode 3 */
    {0x4407, 0x04}, /* Quantization scale */
    {0x460B, 0x37},
    {0x460C, 0x20},
    {0x4837, 0x16}, /* MIPI global timing */
    {0x3824, 0x04}, /* PCLK manual divider */
    {0x5001, 0xA3}, /* SDE on, scale on, UV average off, color matrix on, AWB on */
    {0x3503, 0x00}, /* AEC/AGC on */
};

/**
 * @}
 */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Local_Functions EV_HC32F4A0_LQFP176 OV5640 Local Functions
 * @{
 */

/**
 * @brief  Initializes Camera gpio.
 * @param  None
 * @retval None
 */
static void CAM_Port_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinInputType = PIN_IN_TYPE_CMOS;

    /* DVP_PIXCLK */
    (void)GPIO_Init(BSP_OV5640_DVP_PIXCLK_PORT, BSP_OV5640_DVP_PIXCLK_PIN, &stcGpioInit);

    /* DVP_HSYNC */
    (void)GPIO_Init(BSP_OV5640_DVP_HSYNC_PORT, BSP_OV5640_DVP_HSYNC_PIN, &stcGpioInit);

    /* DVP_VSYNC */
    (void)GPIO_Init(BSP_OV5640_DVP_VSYNC_PORT, BSP_OV5640_DVP_VSYNC_PIN, &stcGpioInit);

    /* DVP_DATA[0:7] */
    (void)GPIO_Init(BSP_OV5640_DVP_DATA0_PORT, BSP_OV5640_DVP_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA1_PORT, BSP_OV5640_DVP_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA2_PORT, BSP_OV5640_DVP_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA3_PORT, BSP_OV5640_DVP_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA4_PORT, BSP_OV5640_DVP_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA5_PORT, BSP_OV5640_DVP_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA6_PORT, BSP_OV5640_DVP_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_DVP_DATA7_PORT, BSP_OV5640_DVP_DATA7_PIN, &stcGpioInit);

    /* DVP_DATA[0:7] */
    GPIO_SetFunc(BSP_OV5640_DVP_DATA0_PORT, BSP_OV5640_DVP_DATA0_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA1_PORT, BSP_OV5640_DVP_DATA1_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA2_PORT, BSP_OV5640_DVP_DATA2_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA3_PORT, BSP_OV5640_DVP_DATA3_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA4_PORT, BSP_OV5640_DVP_DATA4_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA5_PORT, BSP_OV5640_DVP_DATA5_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA6_PORT, BSP_OV5640_DVP_DATA6_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_DATA7_PORT, BSP_OV5640_DVP_DATA7_PIN, GPIO_FUNC_13);

    GPIO_SetFunc(BSP_OV5640_DVP_PIXCLK_PORT, BSP_OV5640_DVP_PIXCLK_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_HSYNC_PORT, BSP_OV5640_DVP_HSYNC_PIN, GPIO_FUNC_13);
    GPIO_SetFunc(BSP_OV5640_DVP_VSYNC_PORT, BSP_OV5640_DVP_VSYNC_PIN, GPIO_FUNC_13);
}

/**
 * @brief Delay function, delay ms approximately
 * @param [in] u32Delay                 ms
 * @retval None
 */
static void BSP_OV5640_I2C_Delay(uint32_t u32Delay)
{
    DDL_DelayMS(u32Delay);
}

/**
 * @brief  Initializes I2C for OV5640.
 * @param  None
 * @retval None
 */
static void BSP_OV5640_I2C_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* Configuration I2C GPIO */
    (void)GPIO_StructInit(&stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_I2C_SCL_PORT, BSP_OV5640_I2C_SCL_PIN, &stcGpioInit);
    (void)GPIO_Init(BSP_OV5640_I2C_SCL_PORT, BSP_OV5640_I2C_SCL_PIN, &stcGpioInit);

    /* Initialize I2C port*/
    GPIO_SetFunc(BSP_OV5640_I2C_SCL_PORT, BSP_OV5640_I2C_SCL_PIN, BSP_OV5640_I2C_SCL_FUNC);
    GPIO_SetFunc(BSP_OV5640_I2C_SDA_PORT, BSP_OV5640_I2C_SDA_PIN, BSP_OV5640_I2C_SDA_FUNC);

    /* Enable I2C Peripheral*/
    FCG_Fcg0PeriphClockCmd(BSP_OV5640_I2C_FCG, ENABLE);

    (void)BSP_I2C_Init(BSP_OV5640_I2C_UNIT);
}

/**
 * @brief  BSP OV5640 I2C write.
 * @param  [in] au8Reg:                 Pointer to the register address.
 * @param  [in] u8RegLen:               Length of register address.
 * @param  [in] au8Buf:                 The pointer to the buffer contains the data to be read.
 * @param  [in] u32Len:                 Buffer size in byte.
 * @retval None
 */
static void BSP_OV5640_I2C_Write(const uint8_t au8Reg[], uint8_t u8RegLen, const uint8_t au8Buf[], uint32_t u32Len)
{
    (void)BSP_I2C_Write(BSP_OV5640_I2C_UNIT, BSP_OV5640_I2C_ADDR, au8Reg, u8RegLen, au8Buf, u32Len);
}

/**
 * @brief  BSP OV5640 I2C read.
 * @param  [in]  au8Reg:                Pointer to the register address.
 * @param  [in]  u8RegLen:              Length of register address.
 * @param  [out] au8Buf:                The pointer to the buffer contains the data to be read.
 * @param  [in]  u32Len:                Buffer size in byte.
 * @retval None
 */
static void BSP_OV5640_I2C_Read(const uint8_t au8Reg[], uint8_t u8RegLen, uint8_t au8Buf[], uint32_t u32Len)
{
    (void)BSP_I2C_Read(BSP_OV5640_I2C_UNIT, BSP_OV5640_I2C_ADDR, au8Reg, u8RegLen, au8Buf, u32Len);
}

/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_OV5640_Global_Functions EV_HC32F4A0_LQFP176 OV5640 Global Functions
 * @{
 */

/**
 * @brief  Initialize OV5640.
 * @param  None
 * @retval None
 */
void BSP_OV5640_Init(void)
{
    CAM_Port_Init();

    (void)OV5640_Init(&m_stcOv5640LL, m_astcOv5640InitRegTable, ARRAY_SZ(m_astcOv5640InitRegTable));
}

/**
 * @brief  Set OV5640 RGB565 mode.
 * @param  None
 * @retval None.
 */
void BSP_OV5640_RGB565_Mode(void)
{
    (void)OV5640_RGB565_Mode(&m_stcOv5640LL, m_astcOv5640Rgb565RegTable, ARRAY_SZ(m_astcOv5640Rgb565RegTable));
}

/**
 * @brief  Read OV5640 ID.
 * @param  None
 * @retval OV5640 ID.
 */
uint16_t BSP_OV5640_ReadID(void)
{
    return OV5640_ReadID(&m_stcOv5640LL);
}

/**
 * @brief  Control OV5640 light.
 * @param  [in] u8Switch                Light on/off
 *         This parameter can be one of the following values:
 *           @arg OV5640_LIGHT_ON:      Light on
 *           @arg OV5640_LIGHT_OFF:     Light off
 * @retval None
 */
void BSP_OV5640_LightControl(uint8_t u8Switch)
{
    (void)OV5640_LightControl(&m_stcOv5640LL, u8Switch);
}

/**
 * @brief  Set OV5640 out size.
 * @param  [in] u16X:                   Window X offset
 * @param  [in] u16Y                    Window Y offset
 * @param  [in] u16Width                Window width
 * @param  [in] u16Height               Window height
 * @retval None
 */
void BSP_OV5640_SetOutSize(uint16_t u16X, uint16_t u16Y, uint16_t u16Width, uint16_t u16Height)
{
    (void)OV5640_SetOutSize(&m_stcOv5640LL, u16X, u16Y, u16Width, u16Height);
}

/**
 * @brief  Set OV5640 test pattern.
 * @param  [in]  u8Mode:                Test mode
 * @retval None
 */
void BSP_OV5640_TestPattern(uint8_t u8Mode)
{
    (void)OV5640_TestPattern(&m_stcOv5640LL, u8Mode);
}
/**
 * @}
 */

#endif /* BSP_OV5640_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/

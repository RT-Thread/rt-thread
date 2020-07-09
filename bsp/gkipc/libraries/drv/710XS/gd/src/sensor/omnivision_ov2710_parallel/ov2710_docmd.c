/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/omnivision_ov2710_parallel/ov2710_docmd.c
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include "gtypes.h"
#include <string.h>
#include "gd_sensor.h"
#include "ov2710_pri.h"
#include "gd_gpio.h"
#include "gd_i2c.h"
#include "gm_lib\gm_debug.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define OV2710_DEFAULT_VIDEO_INDEX      (0)
#define OV2710_VIDEO_MODE_TABLE_AUTO    GD_VIDEO_MODE_1080P_PAL

#define OV2710_SHARE_REG_SIZE           (sizeof(ov2710_share_regs)/sizeof(ov2710_reg_table))
#define OV2710_VIDEO_INFO_TABLE_SIZE    (sizeof(ov2710_video_info_table)/sizeof(ov2710_video_info))
#define OV2710_VIDEO_MODE_TABLE_SIZE    (sizeof(ov2710_video_mode_table)/sizeof(gd_video_mode_s))



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************
//static U32 G_shutter_time = 0;
static ov2710_reg_table ov2710_share_regs[] =
{
    // Select clock source
    { OV2710_PLL_CLOCK_SELECT,      0x93},//0x3103        // Clock from pre-divider

    // OV2710 software reset
    { OV2710_SYSTEM_CONTROL00,      0x82},//0x3008
    { OV2710_SYSTEM_CONTROL00,      0x42},    //sleep mode

    // MIPI setting OFF
    { OV2710_MIPI_CTRL00,           0x18},//0x300E        // I set 1A

    // PLL setting: 27Mhz (/1.5 pre-div) (*36 multiplier) (/8 post-div) = 81Mhz
    //{ OV2710_PLL_CTRL00,            0x88},//0x300F        // Charge pump & PLL SELD5(bypass) setting
    //{ OV2710_PLL_CTRL01,            0x00},//0x3010        // PLL DIVS divider & PLL DIVM divider (def = 0x00)
    //{ OV2710_PLL_CTRL02,            0x24},
    //{ OV2710_PLL_PREDIVEDER,        0x01},//0x3012        // PLL pre-divider = 2

    //{ 0x3011,                       0x28},
    //{ OV2710_PLL_PREDIVEDER,        0x01},//0x3012        // PLL pre-divider = 2

    // IO control
    { OV2710_PAD_OUTPUT_ENABLE00,   0x00},//0x3016
    { OV2710_PAD_OUTPUT_ENABLE01,   0x7F},//0x3017
    { OV2710_PAD_OUTPUT_ENABLE02,   0xFC},//0x3018
    { OV2710_PAD_OUTPUT_SELECT00,   0x00},//0x301C        // def = 0x00
    { OV2710_PAD_OUTPUT_SELECT01,   0x00},//0x301D        // def = 0x00
    { OV2710_PAD_OUTPUT_SELECT02,   0x00},//0x301E        // def = 0x00
    { OV2710_PAD_OUTPUT_DRIVE_CAPABILITY,    0x02},//0x302C        // Output drive capability selection (def = 0x02)

    { OV2710_DVP_CTRL00,            0x04},//use HSYNC instead of HREF
    { OV2710_DVP_CTRL02,            0x03},

    // ISP control
    { OV2710_ISP_CONTROL0,          0x00},//0x5000        // [7] LENC on, [2] Black pixel correct en, [1] white pixel correct en
    { OV2710_ISP_CONTROL1,          0x00},//0x5001        // [0] AWB en
    //{ 0x5002,                       0x00},//0x5002        // [2] VAP en    (CAN'T DISABLE !!!!!!!!!!!!)
    //{ 0x503D,                       0x80},
    // Manual AEC/AGC
    { OV2710_AEC_PK_MANUAL,         0x07},//0x3503        // [2] VTS manual en, [1] AGC manual en, [0] AEC manual en
    { OV2710_AEC_PK_VTS_H,          0x00},//0x350C
    { OV2710_AEC_PK_VTS_L,          0x00},//0x350D

    // Black level calibration
    { OV2710_BLC_CONTROL_00,        0x05},//0x4000        // BLC control
    { 0x4006,                       0x00},//0x4006        // Black level target [9:8]
    { 0x4007,                       0x00},//0x4007        // Black level target [7:0]
    // Reserved registers
    { 0x302D,                       0x90},//0x302D
    { 0x3600,                       0x04},//0x3600
    { 0x3603,                       0xA7},//0x3603
    { 0x3604,                       0x60},//0x3604
    { 0x3605,                       0x05},//0x3605
    { 0x3606,                       0x12},//0x3606
    { 0x3621,                       0x04},//0x3621        // [7] Horizontal binning, [6] Horizontal skipping
    { 0x3630,                       0x6D},//0x3630
    { 0x3631,                       0x26},//0x3631
    { 0x3702,                       0x9E},//0x3702
    { 0x3703,                       0x74},//0x3703
    { 0x3704,                       0x10},//0x3704
    { 0x3706,                       0x61},//0x3706
    { 0x370B,                       0x40},//0x370B
    { 0x370D,                       0x07},//0x370D
    { 0x3710,                       0x9E},//0x3710
    { 0x3712,                       0x0C},//0x3712
    { 0x3713,                       0x8B},//0x3713
    { 0x3714,                       0x74},//0x3714
    { 0x381a,                       0x1a},//0x381a
    { 0x382e,                       0x0f},//0x382e

    { 0x4301,                       0xFF},//0x4301
    { 0x4303,                       0x00},//0x4303
    { 0x3A1A,                       0x06},//0x3A1A        // AVG REG (to be removed?)
    { 0x5688,                       0x03},//0x5688        // AVG REG (to be removed?)

    /*********** mirror and flip here,for our new board */
    { OV2710_ANA_ARRAY_01,          0x14},//0x3621
    { OV2710_TIMING_CONTROL_VS_LOWBYTE, 0x09},//0x3803
    { OV2710_TIMING_CONTROL18,      0xE0},//0x3818 //0xE0,0xB0, 0xA0,0x80

    //{ OV2710_DVP_CTRL01, 0x02},//VSYNC2 mode enable
};

/*
 *  1.rember to update OV2710_VIDEO_PLL_REG_TABLE_SIZE if you add/remove the regs
 *     2.see rct.h for pixclk/extclk value
    OV2710_PLL_PREDIVEDER:000=1, 001=1.5, 010=2, 011=2.5, 100=3, 101=4, 110=6, 111=8
    3. pixclk = ((extclk / 8) / OV2710_PLL_PREDIVEDER) * OV2710_PLL_CTRL02

 */
static ov2710_pll_reg_table ov2710_pll_tbl[] =
{
    //[0] =
    {
        81000000,//.pixclk = 81000000,
        PLL_CLK_27MHZ,//.extclk = PLL_CLK_27MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x18},          // 24
            {OV2710_PLL_PREDIVEDER, 0x00},      // 1/1
        }
    },
    //[1] =
    {
        80919080,//.pixclk = 80919080,
        PLL_CLK_27D1001MHZ,//.extclk = PLL_CLK_27D1001MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x18},          // 24
            {OV2710_PLL_PREDIVEDER, 0x00},      // 1/1
        }
    },
    //[2] =
    {
        40500000,//.pixclk = 40500000,
        PLL_CLK_27MHZ,//.extclk = PLL_CLK_27MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x12},          // 18
            {OV2710_PLL_PREDIVEDER, 0x01},      // 3/2
        }
    },
    //[3] =
    {
        PLL_CLK_54MHZ,//.pixclk = PLL_CLK_54MHZ,
        PLL_CLK_27MHZ,//.extclk = PLL_CLK_27MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x18},          // 24
            {OV2710_PLL_PREDIVEDER, 0x01},      // 3/2
        }
    },
    //[4] =
    {
        PLL_CLK_74_25MHZ,//.pixclk = PLL_CLK_74_25MHZ,
        PLL_CLK_27MHZ,//.extclk = PLL_CLK_27MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x16},          // 22
            {OV2710_PLL_PREDIVEDER, 0x00},      // 1
        }
    },
    //[5] =
    {
        PLL_CLK_90MHZ,//.pixclk = 90000000,
        PLL_CLK_27MHZ,//.extclk = PLL_CLK_27MHZ,
        //.regs =
        {
            {OV2710_PLL_CTRL00, 0x88},          // 1/2
            {OV2710_PLL_CTRL01, 0x00},          // 1
            {OV2710_PLL_CTRL02, 0x28},          // 40
            {OV2710_PLL_PREDIVEDER, 0x01},      // 3/2
        }
    },
    /* << add pll config here if necessary >> */
};
/* the table is used to provide video info to application */
static ov2710_video_info ov2710_video_info_table[] = {
    //[0] = GD_VIDEO_MODE_VGA
    {//for a2s use
       0,//.format_index        = 0,      /* select ov2710_video_format_tbl */
       320,//.def_start_x       = 320,    /* tell amba soc the capture x start offset */
       120,//.def_start_y       = 120,    /* tell amba soc the capture y start offset */
       640,//.def_width         = 640,
       480,//.def_height        = 480,
       0,//.sync_start          = 0,
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[1] = GD_VIDEO_MODE_720P
    {
       1,//.format_index        = 1,
       0,//.def_start_x         = 0,
       0,//.def_start_y         = 0,
       1280,//.def_width        = 1280,
       720,//.def_height        = 720,
       (0 + 0),//.sync_start    = (0 + 0),
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[2] = GD_VIDEO_MODE_AUTO / GD_VIDEO_MODE_1080P_PAL
    {
       2,//.format_index        = 2,
       0,//.def_start_x         = 0,
       0,//.def_start_y         = 0,
       1920,//.def_width        = 1920,
       1080,//.def_height       = 1080,
       (0 + 0),//.sync_start    = (0 + 0),
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[3] = GD_VIDEO_MODE_WVGA
    {//for a2s use
       0,//.format_index        = 0,
       500,//.def_start_x       = 500,
       20,//.def_start_y        = 20,
       800,//.def_width         = 800,
       480,//.def_height        = 480,
       0,//.sync_start          = 0,
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[4] = GD_VIDEO_MODE_720P_PAL
    {
        3,//.format_index    = 3,
        0,//.def_start_x     = 0,
        0,//.def_start_y     = 0,
        1280,//.def_width       = 1280,
        720,//.def_height      = 720,
        (0 + 0),//.sync_start      = (0 + 0),
        0,//.type_ext =??
        GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[5] = GD_VIDEO_MODE_AUTO / GD_VIDEO_MODE_1080P
    {
       4,//.format_index        = 2,
       0,//.def_start_x         = 0,
       0,//.def_start_y         = 0,
       1920,//.def_width        = 1920,
       1080,//.def_height       = 1080,
       (0 + 0),//.sync_start    = (0 + 0),
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },
};

static gd_video_mode_s ov2710_video_mode_table[] =
{
    {
        GD_VIDEO_MODE_AUTO,
        2, /* select the index from above info table ov2710_video_info_table*/
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        2, /* select the index from above info table */
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },

    {
        GD_VIDEO_MODE_720P,
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_720P_PAL,//@50P
        4,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        4,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_1080P,
        5,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        5,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_1080P_PAL,//@50P
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_VGA,
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_WVGA,
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
};

/*   < rember to update OV2710_VIDEO_FORMAT_REG_TABLE_SIZE, once you add or remove table items */
/*   < rember to update OV2710_VIDEO_FORMAT_REG_NUM, once you add or remove register here*/
static ov2710_video_format_reg_table ov2710_video_format_tbl =
{
    //.reg =
    {
        OV2710_TIMING_CONTROL_HS_HIGHBYTE,    //0x3800
        OV2710_TIMING_CONTROL_HS_LOWBYTE,     //0x3801
        OV2710_TIMING_CONTROL_VS_HIGHBYTE,    //0x3802
        OV2710_TIMING_CONTROL_VS_LOWBYTE,     //0x3803
        OV2710_TIMING_CONTROL_HW_HIGH_BYTE,   //0x3804
        OV2710_TIMING_CONTROL_HW_LOW_BYTE,    //0x3805
        OV2710_TIMING_CONTROL_VW_HIGH_BYTE,   //0x3806
        OV2710_TIMING_CONTROL_VW_LOW_BYTE,    //0x3807
        OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH, //0x3808
        OV2710_TIMING_CONTROL_DVP_HSIZE_LOW,  //0x3809
        OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH, //0x380A
        OV2710_TIMING_CONTROL_DVP_VSIZE_LOW,  //0x380B
        OV2710_TIMING_CONTROL_HTS_HIGHBYTE,   //0x380C
        OV2710_TIMING_CONTROL_HTS_LOWBYTE,    //0x380D
        OV2710_TIMING_CONTROL_VTS_HIGHBYTE,   //0x380E
        OV2710_TIMING_CONTROL_VTS_LOWBYTE,    //0x380F
        0x3811,
        0x381C,
        0x381D,
        0x381E,
        0x381F,
        0x3820,
        0x3821,
        0x3620,
        0x3623,
    },
    {
        //VGA
        //.table[0] = GD_VIDEO_MODE_VGA / GD_VIDEO_MODE_WVGA
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,//0x3800 OV2710_TIMING_CONTROL_HS_HIGHBYTE HREF horizontal start [11:8]
                0xC4,//0x3801 OV2710_TIMING_CONTROL_HS_LOWBYTE HREF horizontal start [7:0]
                0x00,//0x3802 OV2710_TIMING_CONTROL_VS_HIGHBYTE HREF vertical start [11:8]
                0x0A,//0x3803 OV2710_TIMING_CONTROL_VS_LOWBYTE HREF vertical start [7:0]
                0x05,//0x3804 OV2710_TIMING_CONTROL_HW_HIGH_BYTE HREF horizontal width [11:8]
                0x00,//0x3805 OV2710_TIMING_CONTROL_HW_LOW_BYTE HREF horizontal width [7:0]
                0x02,//0x3806 OV2710_TIMING_CONTROL_VW_HIGH_BYTE HREF vertical height [11:8]
                0xD0,//0x3807 OV2710_TIMING_CONTROL_VW_LOW_BYTE HREF vertical height [7:0]
                0x05,//0x3808 OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH
                0x00,//0x3809 OV2710_TIMING_CONTROL_DVP_HSIZE_LOW
                0x02,//0x380A OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH
                0xD0,//0x380B OV2710_TIMING_CONTROL_DVP_VSIZE_LOW
                0x07,//0x380C OV2710_TIMING_CONTROL_HTS_HIGHBYTE
                0x00,//0x380D OV2710_TIMING_CONTROL_HTS_LOWBYTE
                0x02,//0x380E OV2710_TIMING_CONTROL_VTS_HIGHBYTE
                0xF1,//0x380F OV2710_TIMING_CONTROL_VTS_LOWBYTE
                0x00,//0x3811
                0x10,//0x381C
                0xB8,//0x381D
                0x02,//0x381E
                0xDC,//0x381F
                0x0A,//0x3820
                0x29,//0x3821
                0x07,//0x3620
                0x40,//0x3623
            },
            NULL,//.fps_table = NULL,
            1280,//.width = 1280,
            720,//.height = 720,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_4_3,//.ratio = GD_VIDEO_RATIO_4_3,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_60,//.max_fps = GD_VIDEO_FPS_60,
            GD_VIDEO_FPS_59_94,//.auto_fps = GD_VIDEO_FPS_59_94,
        },
        //.table[1] = GD_VIDEO_MODE_720P
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,//0x3800 OV2710_TIMING_CONTROL_HS_HIGHBYTE HREF horizontal start [11:8]
                0xC4,//0x3801 OV2710_TIMING_CONTROL_HS_LOWBYTE HREF horizontal start [7:0]
                0x00,//0x3802 OV2710_TIMING_CONTROL_VS_HIGHBYTE HREF vertical start [11:8]
                0x0A,//0x3803 OV2710_TIMING_CONTROL_VS_LOWBYTE HREF vertical start [7:0]
                0x05,//0x3804 OV2710_TIMING_CONTROL_HW_HIGH_BYTE HREF horizontal width [11:8]
                0x00,//0x3805 OV2710_TIMING_CONTROL_HW_LOW_BYTE HREF horizontal width [7:0]
                0x02,//0x3806 OV2710_TIMING_CONTROL_VW_HIGH_BYTE HREF vertical height [11:8]
                0xD0,//0x3807 OV2710_TIMING_CONTROL_VW_LOW_BYTE HREF vertical height [7:0]
                0x05,//0x3808 OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH
                0x00,//0x3809 OV2710_TIMING_CONTROL_DVP_HSIZE_LOW
                0x02,//0x380A OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH
                0xD0,//0x380B OV2710_TIMING_CONTROL_DVP_VSIZE_LOW
                0x07,//0x380C OV2710_TIMING_CONTROL_HTS_HIGHBYTE
                0x00,//0x380D OV2710_TIMING_CONTROL_HTS_LOWBYTE
                0x02,//0x380E OV2710_TIMING_CONTROL_VTS_HIGHBYTE
                0xF1,//0x380F OV2710_TIMING_CONTROL_VTS_LOWBYTE
                0x00,//0x3811
                0x10,//0x381C
                0xB8,//0x381D
                0x02,//0x381E
                0xDC,//0x381F
                0x0A,//0x3820
                0x29,//0x3821
                0x07,//0x3620
                0x40,//0x3623
            },
            NULL,//.fps_table = NULL,
            1280,//.width = 1280,
            720,//.height = 720,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_60,//.max_fps = GD_VIDEO_FPS_60,
            GD_VIDEO_FPS_59_94,//.auto_fps = GD_VIDEO_FPS_59_94,
        },
        //.table[2] = GD_VIDEO_MODE_1080P_PAL / GD_VIDEO_MODE_AUTO
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,//0x3800 OV2710_TIMING_CONTROL_HS_HIGHBYTE HREF horizontal start [11:8]    //452
                0xC4,//0x3801 OV2710_TIMING_CONTROL_HS_LOWBYTE HREF horizontal start [7:0]
                0x00,//0x3802 OV2710_TIMING_CONTROL_VS_HIGHBYTE HREF vertical start [11:8]      //10
                0x0A,//0x3803 OV2710_TIMING_CONTROL_VS_LOWBYTE HREF vertical start [7:0]
                0x07,//0x3804 OV2710_TIMING_CONTROL_HW_HIGH_BYTE HREF horizontal width [11:8]   //1920
                0x80,//0x3805 OV2710_TIMING_CONTROL_HW_LOW_BYTE HREF horizontal width [7:0]
                0x04,//0x3806 OV2710_TIMING_CONTROL_VW_HIGH_BYTE HREF vertical height [11:8]    //1080
                0x38,//0x3807 OV2710_TIMING_CONTROL_VW_LOW_BYTE HREF vertical height [7:0]
                0x07,//0x3808 OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH    //1920
                0x80,//0x3809 OV2710_TIMING_CONTROL_DVP_HSIZE_LOW
                0x04,//0x380A OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH    //1080
                0x38,//0x380B OV2710_TIMING_CONTROL_DVP_VSIZE_LOW
                0x0A,//0x380C OV2710_TIMING_CONTROL_HTS_HIGHBYTE      //2640
                0x50,//0x380D OV2710_TIMING_CONTROL_HTS_LOWBYTE
                0x04,//0x380E OV2710_TIMING_CONTROL_VTS_HIGHBYTE      //1125
                0x65,//0x380F OV2710_TIMING_CONTROL_VTS_LOWBYTE
                0x02,//0x3811
                0x21,//0x381C
                0x50,//0x381D
                0x01,//0x381E
                0x20,//0x381F
                0x00,//0x3820
                0x00,//0x3821
                0x37,//0x3620
                0x00,//0x3623
            },
            NULL,//.fps_table = NULL,
            1920,//.width = 1920,
            1080,//.height = 1080,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            4,//.pll_index = 0,
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_30,
            GD_VIDEO_FPS_25,//.auto_fps = GD_VIDEO_FPS_29_97,
        },
        //.table[3] = GD_VIDEO_MODE_720P_PAL
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,//0x3800 OV2710_TIMING_CONTROL_HS_HIGHBYTE HREF horizontal start [11:8]      //452
                0xC4,//0x3801 OV2710_TIMING_CONTROL_HS_LOWBYTE HREF horizontal start [7:0]
                0x00,//0x3802 OV2710_TIMING_CONTROL_VS_HIGHBYTE HREF vertical start [11:8]        //10
                0x02,//0x3803 OV2710_TIMING_CONTROL_VS_LOWBYTE HREF vertical start [7:0]
                0x05,//0x3804 OV2710_TIMING_CONTROL_HW_HIGH_BYTE HREF horizontal width [11:8]      //1280
                0x00,//0x3805 OV2710_TIMING_CONTROL_HW_LOW_BYTE HREF horizontal width [7:0]
                0x02,//0x3806 OV2710_TIMING_CONTROL_VW_HIGH_BYTE HREF vertical height [11:8]       //720
                0xD0,//0x3807 OV2710_TIMING_CONTROL_VW_LOW_BYTE HREF vertical height [7:0]
                0x05,//0x3808 OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH    //1280
                0x00,//0x3809 OV2710_TIMING_CONTROL_DVP_HSIZE_LOW
                0x02,//0x380A OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH    //720
                0xD0,//0x380B OV2710_TIMING_CONTROL_DVP_VSIZE_LOW
                0x07,//0x380C OV2710_TIMING_CONTROL_HTS_HIGHBYTE      //1980
                0xBC,//0x380D OV2710_TIMING_CONTROL_HTS_LOWBYTE
                0x02,//0x380E OV2710_TIMING_CONTROL_VTS_HIGHBYTE      //750
                0xEE,//0x380F OV2710_TIMING_CONTROL_VTS_LOWBYTE
                0x00,//0x3811
                0x10,//0x381C
                0xB8,//0x381D
                0x02,//0x381E
                0xDC,//0x381F
                0x0A,//0x3820
                0x29,//0x3821
                0x07,//0x3620
                0x40,//0x3623
            },
            NULL,//.fps_table = NULL,
            1280,//.width = 1280,
            720,//.height = 720,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            4,//.pll_index = 0,
            GD_VIDEO_FPS_60,//.max_fps = GD_VIDEO_FPS_60,
            GD_VIDEO_FPS_50,//.auto_fps = GD_VIDEO_FPS_50,
        },
        //.table[4] = GD_VIDEO_MODE_1080P
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,//0x3800 OV2710_TIMING_CONTROL_HS_HIGHBYTE HREF horizontal start [11:8]    //452
                0xC4,//0x3801 OV2710_TIMING_CONTROL_HS_LOWBYTE HREF horizontal start [7:0]
                0x00,//0x3802 OV2710_TIMING_CONTROL_VS_HIGHBYTE HREF vertical start [11:8]      //10
                0x0A,//0x3803 OV2710_TIMING_CONTROL_VS_LOWBYTE HREF vertical start [7:0]
                0x07,//0x3804 OV2710_TIMING_CONTROL_HW_HIGH_BYTE HREF horizontal width [11:8]   //1920
                0x80,//0x3805 OV2710_TIMING_CONTROL_HW_LOW_BYTE HREF horizontal width [7:0]
                0x04,//0x3806 OV2710_TIMING_CONTROL_VW_HIGH_BYTE HREF vertical height [11:8]    //1080
                0x38,//0x3807 OV2710_TIMING_CONTROL_VW_LOW_BYTE HREF vertical height [7:0]
                0x07,//0x3808 OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH    //1920
                0x80,//0x3809 OV2710_TIMING_CONTROL_DVP_HSIZE_LOW
                0x04,//0x380A OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH    //1080
                0x38,//0x380B OV2710_TIMING_CONTROL_DVP_VSIZE_LOW
                0x09,//0x380C OV2710_TIMING_CONTROL_HTS_HIGHBYTE      //2420
                0xAB,//0x380D OV2710_TIMING_CONTROL_HTS_LOWBYTE
                0x04,//0x380E OV2710_TIMING_CONTROL_VTS_HIGHBYTE      //1116
                0x44,//0x380F OV2710_TIMING_CONTROL_VTS_LOWBYTE
                0x02,//0x3811
                0x21,//0x381C
                0x50,//0x381D
                0x01,//0x381E
                0x20,//0x381F
                0x00,//0x3820
                0x00,//0x3821
                0x37,//0x3620
                0x00,//0x3623
            },
            NULL,//.fps_table = NULL,
            1920,//.width = 1920,
            1080,//.height = 1080,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_30,
            GD_VIDEO_FPS_29_97,//.auto_fps = GD_VIDEO_FPS_29_97,
        },
        /* add video format table here, if necessary */
    },
};

/* This is 32-step gain table, OV2710_GAIN_ROWS = 162, OV2710_GAIN_COLS = 3 */
static S16 OV2710_GAIN_TABLE[OV2710_GAIN_ROWS][OV2710_GAIN_COLS] =
{
    {0x4000, 6144, 0x01, 0xFF},    /* index   0, gain = 36.123599 dB, actual gain = 35.847834 dB */
    {0x3D49, 6080, 0x01, 0xFE},    /* index   1, gain = 35.747312 dB, actual gain = 35.847834 dB */
    {0x3AB0, 6016, 0x01, 0xFD},    /* index   2, gain = 35.371024 dB, actual gain = 35.268560 dB */
    {0x3833, 5952, 0x01, 0xFC},    /* index   3, gain = 34.994737 dB, actual gain = 34.963761 dB */
    {0x35D1, 5888, 0x01, 0xFB},    /* index   4, gain = 34.618450 dB, actual gain = 34.647875 dB */
    {0x3389, 5824, 0x01, 0xFA},    /* index   5, gain = 34.242162 dB, actual gain = 34.320067 dB */
    {0x315A, 5760, 0x01, 0xF9},    /* index   6, gain = 33.865875 dB, actual gain = 33.979400 dB */
    {0x2F42, 5696, 0x01, 0xF8},    /* index   7, gain = 33.489587 dB, actual gain = 33.624825 dB */
    {0x2D41, 5632, 0x01, 0xF7},    /* index   8, gain = 33.113300 dB, actual gain = 33.255157 dB */
    {0x2B56, 5568, 0x01, 0xF6},    /* index   9, gain = 32.737012 dB, actual gain = 32.869054 dB */
    {0x2980, 5504, 0x01, 0xF5},    /* index  10, gain = 32.360725 dB, actual gain = 32.464986 dB */
    {0x27BD, 5440, 0x01, 0xF4},    /* index  11, gain = 31.984437 dB, actual gain = 32.041200 dB */
    {0x260E, 5376, 0x01, 0xF3},    /* index  12, gain = 31.608150 dB, actual gain = 31.595672 dB */
    {0x2471, 5312, 0x01, 0xF2},    /* index  13, gain = 31.231862 dB, actual gain = 31.126050 dB */
    {0x22E5, 5248, 0x01, 0xF1},    /* index  14, gain = 30.855575 dB, actual gain = 30.629578 dB */
    {0x216B, 5184, 0x01, 0xF1},    /* index  15, gain = 30.479287 dB, actual gain = 30.629578 dB */
    {0x2000, 5120, 0x00, 0xFF},    /* index  16, gain = 30.103000 dB, actual gain = 29.827234 dB */
    {0x1EA5, 5056, 0x00, 0xFE},    /* index  17, gain = 29.726712 dB, actual gain = 29.827234 dB */
    {0x1D58, 4992, 0x00, 0xFD},    /* index  18, gain = 29.350425 dB, actual gain = 29.247960 dB */
    {0x1C1A, 4928, 0x00, 0xFC},    /* index  19, gain = 28.974137 dB, actual gain = 28.943161 dB */
    {0x1AE9, 4864, 0x00, 0xFB},    /* index  20, gain = 28.597850 dB, actual gain = 28.627275 dB */
    {0x19C5, 4800, 0x00, 0xFA},    /* index  21, gain = 28.221562 dB, actual gain = 28.299467 dB */
    {0x18AD, 4736, 0x00, 0xF9},    /* index  22, gain = 27.845275 dB, actual gain = 27.958800 dB */
    {0x17A1, 4672, 0x00, 0xF8},    /* index  23, gain = 27.468987 dB, actual gain = 27.604225 dB */
    {0x16A1, 4608, 0x00, 0xF7},    /* index  24, gain = 27.092700 dB, actual gain = 27.234557 dB */
    {0x15AB, 4544, 0x00, 0xF6},    /* index  25, gain = 26.716412 dB, actual gain = 26.848454 dB */
    {0x14C0, 4480, 0x00, 0xF5},    /* index  26, gain = 26.340125 dB, actual gain = 26.444386 dB */
    {0x13DF, 4416, 0x00, 0xF4},    /* index  27, gain = 25.963837 dB, actual gain = 26.020600 dB */
    {0x1307, 4352, 0x00, 0xF3},    /* index  28, gain = 25.587550 dB, actual gain = 25.575072 dB */
    {0x1238, 4288, 0x00, 0xF2},    /* index  29, gain = 25.211262 dB, actual gain = 25.105450 dB */
    {0x1173, 4224, 0x00, 0xF1},    /* index  30, gain = 24.834975 dB, actual gain = 24.608978 dB */
    {0x10B5, 4160, 0x00, 0xF1},    /* index  31, gain = 24.458687 dB, actual gain = 24.608978 dB */
    {0x1000, 4096, 0x00, 0x7F},    /* index  32, gain = 24.082400 dB, actual gain = 23.806634 dB */
    {0x0F52, 4032, 0x00, 0x7E},    /* index  33, gain = 23.706112 dB, actual gain = 23.806634 dB */
    {0x0EAC, 3968, 0x00, 0x7D},    /* index  34, gain = 23.329825 dB, actual gain = 23.227360 dB */
    {0x0E0D, 3904, 0x00, 0x7C},    /* index  35, gain = 22.953537 dB, actual gain = 22.922561 dB */
    {0x0D74, 3840, 0x00, 0x7B},    /* index  36, gain = 22.577250 dB, actual gain = 22.606675 dB */
    {0x0CE2, 3776, 0x00, 0x7A},    /* index  37, gain = 22.200962 dB, actual gain = 22.278867 dB */
    {0x0C56, 3712, 0x00, 0x79},    /* index  38, gain = 21.824675 dB, actual gain = 21.938200 dB */
    {0x0BD1, 3648, 0x00, 0x78},    /* index  39, gain = 21.448387 dB, actual gain = 21.583625 dB */
    {0x0B50, 3584, 0x00, 0x77},    /* index  40, gain = 21.072100 dB, actual gain = 21.213957 dB */
    {0x0AD6, 3520, 0x00, 0x76},    /* index  41, gain = 20.695812 dB, actual gain = 20.827854 dB */
    {0x0A60, 3456, 0x00, 0x75},    /* index  42, gain = 20.319525 dB, actual gain = 20.423786 dB */
    {0x09EF, 3392, 0x00, 0x74},    /* index  43, gain = 19.943237 dB, actual gain = 20.000000 dB */
    {0x0983, 3328, 0x00, 0x73},    /* index  44, gain = 19.566950 dB, actual gain = 19.554472 dB */
    {0x091C, 3264, 0x00, 0x72},    /* index  45, gain = 19.190662 dB, actual gain = 19.084850 dB */
    {0x08B9, 3200, 0x00, 0x71},    /* index  46, gain = 18.814375 dB, actual gain = 18.588379 dB */
    {0x085B, 3136, 0x00, 0x71},    /* index  47, gain = 18.438087 dB, actual gain = 18.588379 dB */
    {0x0800, 3072, 0x00, 0x3F},    /* index  48, gain = 18.061800 dB, actual gain = 17.786034 dB */
    {0x07A9, 3008, 0x00, 0x3E},    /* index  49, gain = 17.685512 dB, actual gain = 17.786034 dB */
    {0x0756, 2944, 0x00, 0x3D},    /* index  50, gain = 17.309225 dB, actual gain = 17.206760 dB */
    {0x0706, 2880, 0x00, 0x3C},    /* index  51, gain = 16.932937 dB, actual gain = 16.901961 dB */
    {0x06BA, 2816, 0x00, 0x3B},    /* index  52, gain = 16.556650 dB, actual gain = 16.586075 dB */
    {0x0671, 2752, 0x00, 0x3A},    /* index  53, gain = 16.180362 dB, actual gain = 16.258267 dB */
    {0x062B, 2688, 0x00, 0x39},    /* index  54, gain = 15.804075 dB, actual gain = 15.917600 dB */
    {0x05E8, 2624, 0x00, 0x38},    /* index  55, gain = 15.427787 dB, actual gain = 15.563025 dB */
    {0x05A8, 2560, 0x00, 0x37},    /* index  56, gain = 15.051500 dB, actual gain = 15.193357 dB */
    {0x056B, 2496, 0x00, 0x36},    /* index  57, gain = 14.675212 dB, actual gain = 14.807254 dB */
    {0x0530, 2432, 0x00, 0x35},    /* index  58, gain = 14.298925 dB, actual gain = 14.403186 dB */
    {0x04F8, 2368, 0x00, 0x34},    /* index  59, gain = 13.922637 dB, actual gain = 13.979400 dB */
    {0x04C2, 2304, 0x00, 0x33},    /* index  60, gain = 13.546350 dB, actual gain = 13.533872 dB */
    {0x048E, 2240, 0x00, 0x32},    /* index  61, gain = 13.170062 dB, actual gain = 13.064250 dB */
    {0x045D, 2176, 0x00, 0x31},    /* index  62, gain = 12.793775 dB, actual gain = 12.567779 dB */
    {0x042D, 2112, 0x00, 0x31},    /* index  63, gain = 12.417487 dB, actual gain = 12.567779 dB */
    {0x0400, 2048, 0x00, 0x1F},    /* index  64, gain = 12.041200 dB, actual gain = 11.765434 dB */
    {0x03D5, 1984, 0x00, 0x1E},    /* index  65, gain = 11.664912 dB, actual gain = 11.765434 dB */
    {0x03AB, 1920, 0x00, 0x1D},    /* index  66, gain = 11.288625 dB, actual gain = 11.186160 dB */
    {0x0383, 1856, 0x00, 0x1C},    /* index  67, gain = 10.912337 dB, actual gain = 10.881361 dB */
    {0x035D, 1792, 0x00, 0x1B},    /* index  68, gain = 10.536050 dB, actual gain = 10.565476 dB */
    {0x0339, 1728, 0x00, 0x1A},    /* index  69, gain = 10.159762 dB, actual gain = 10.237667 dB */
    {0x0316, 1664, 0x00, 0x19},    /* index  70, gain =  9.783475 dB, actual gain =  9.897000 dB */
    {0x02F4, 1600, 0x00, 0x18},    /* index  71, gain =  9.407187 dB, actual gain =  9.542425 dB */
    {0x02D4, 1536, 0x00, 0x17},    /* index  72, gain =  9.030900 dB, actual gain =  9.172757 dB */
    {0x02B5, 1472, 0x00, 0x16},    /* index  73, gain =  8.654612 dB, actual gain =  8.786654 dB */
    {0x0298, 1408, 0x00, 0x15},    /* index  74, gain =  8.278325 dB, actual gain =  8.382586 dB */
    {0x027C, 1344, 0x00, 0x14},    /* index  75, gain =  7.902037 dB, actual gain =  7.958800 dB */
    {0x0261, 1280, 0x00, 0x13},    /* index  76, gain =  7.525750 dB, actual gain =  7.513272 dB */
    {0x0247, 1216, 0x00, 0x12},    /* index  77, gain =  7.149462 dB, actual gain =  7.043650 dB */
    {0x022E, 1152, 0x00, 0x11},    /* index  78, gain =  6.773175 dB, actual gain =  6.547179 dB */
    {0x0217, 1088, 0x00, 0x11},    /* index  79, gain =  6.396887 dB, actual gain =  6.547179 dB */
    {0x0200, 1024, 0x00, 0x0F},    /* index  80, gain =  6.020600 dB, actual gain =  5.744834 dB */
    {0x01EA,  960, 0x00, 0x0E},    /* index  81, gain =  5.644312 dB, actual gain =  5.744834 dB */
    {0x01D6,  896, 0x00, 0x0D},    /* index  82, gain =  5.268025 dB, actual gain =  5.165560 dB */
    {0x01C2,  832, 0x00, 0x0C},    /* index  83, gain =  4.891737 dB, actual gain =  4.860761 dB */
    {0x01AF,  768, 0x00, 0x0B},    /* index  84, gain =  4.515450 dB, actual gain =  4.544876 dB */
    {0x019C,  704, 0x00, 0x0A},    /* index  85, gain =  4.139162 dB, actual gain =  4.217067 dB */
    {0x018B,  640, 0x00, 0x09},    /* index  86, gain =  3.762875 dB, actual gain =  3.876401 dB */
    {0x017A,  576, 0x00, 0x08},    /* index  87, gain =  3.386587 dB, actual gain =  3.521825 dB */
    {0x016A,  512, 0x00, 0x07},    /* index  88, gain =  3.010300 dB, actual gain =  3.152157 dB */
    {0x015B,  448, 0x00, 0x06},    /* index  89, gain =  2.634012 dB, actual gain =  2.766054 dB */
    {0x014C,  384, 0x00, 0x05},    /* index  90, gain =  2.257725 dB, actual gain =  2.361986 dB */
    {0x013E,  320, 0x00, 0x04},    /* index  91, gain =  1.881437 dB, actual gain =  1.938200 dB */
    {0x0130,  256, 0x00, 0x03},    /* index  92, gain =  1.505150 dB, actual gain =  1.492672 dB */
    {0x0124,  192, 0x00, 0x02},    /* index  93, gain =  1.128862 dB, actual gain =  1.023050 dB */
    {0x0117,  128, 0x00, 0x01},    /* index  94, gain =  0.752575 dB, actual gain =  0.526579 dB */
    {0x010B,   64, 0x00, 0x01},    /* index  95, gain =  0.376287 dB, actual gain =  0.526579 dB */
    {0x0100,    0, 0x00, 0x00},    /* index  96, gain =  0.000000 dB, actual gain =  0.000000 dB */
};

static GD_SENSOR_REG_S reg2710_dump[] =
{
    {"OV2710_SYSTEM_CONTROL00"                  , OV2710_SYSTEM_CONTROL00},
    {"OV2710_PIDH"                              , OV2710_PIDH},
    {"OV2710_PIDL"                              , OV2710_PIDL},
    {"OV2710_MIPI_CTRL00"                       , OV2710_MIPI_CTRL00},
    {"OV2710_PLL_CTRL00"                        , OV2710_PLL_CTRL00},
    {"OV2710_PLL_CTRL01"                        , OV2710_PLL_CTRL01},
    {"OV2710_PLL_CTRL02"                        , OV2710_PLL_CTRL02},
    {"OV2710_PLL_PREDIVEDER"                    , OV2710_PLL_PREDIVEDER},
    {"OV2710_PAD_OUTPUT_ENABLE00"               , OV2710_PAD_OUTPUT_ENABLE00},
    {"OV2710_PAD_OUTPUT_ENABLE01"               , OV2710_PAD_OUTPUT_ENABLE01},
    {"OV2710_PAD_OUTPUT_ENABLE02"               , OV2710_PAD_OUTPUT_ENABLE02},
    {"OV2710_PAD_OUTPUT_VALUE00"                , OV2710_PAD_OUTPUT_VALUE00},
    {"OV2710_PAD_OUTPUT_VALUE01"                , OV2710_PAD_OUTPUT_VALUE01},
    {"OV2710_PAD_OUTPUT_VALUE02"                , OV2710_PAD_OUTPUT_VALUE02},
    {"OV2710_PAD_OUTPUT_SELECT00"               , OV2710_PAD_OUTPUT_SELECT00},
    {"OV2710_PAD_OUTPUT_SELECT01"               , OV2710_PAD_OUTPUT_SELECT01},
    {"OV2710_PAD_OUTPUT_SELECT02"               , OV2710_PAD_OUTPUT_SELECT02},
    {"OV2710_PAD_OUTPUT_DRIVE_CAPABILITY"       , OV2710_PAD_OUTPUT_DRIVE_CAPABILITY},
    {"0x302D"                                   , 0x302D},
    {"OV2710_PAD_INPUT_VALUE00"                 , OV2710_PAD_INPUT_VALUE00},
    {"OV2710_PAD_INPUT_VALUE01"                 , OV2710_PAD_INPUT_VALUE01},
    {"OV2710_PAD_INPUT_VALUE02"                 , OV2710_PAD_INPUT_VALUE02},
    {"OV2710_SCCB_ID"                           , OV2710_SCCB_ID},
    {"OV2710_PLL_CLOCK_SELECT"                  , OV2710_PLL_CLOCK_SELECT},
    {"OV2710_SCCB_PAD_CLOCK_DIVIDER"            , OV2710_SCCB_PAD_CLOCK_DIVIDER},
    {"OV2710_GROUP_ADDR0"                       , OV2710_GROUP_ADDR0},
    {"OV2710_GROUP_ADDR1"                       , OV2710_GROUP_ADDR1},
    {"OV2710_GROUP_ADDR2"                       , OV2710_GROUP_ADDR2},
    {"OV2710_GROUP_ADDR3"                       , OV2710_GROUP_ADDR3},
    {"OV2710_GROUP_ACCESS"                      , OV2710_GROUP_ACCESS},
    {"OV2710_AWB_GAIN_PK_RED_GAIN_H"            , OV2710_AWB_GAIN_PK_RED_GAIN_H},
    {"OV2710_AWB_GAIN_PK_RED_GAIN_L"            , OV2710_AWB_GAIN_PK_RED_GAIN_L},
    {"OV2710_AWB_GAIN_PK_GREEN_GAIN_H"          , OV2710_AWB_GAIN_PK_GREEN_GAIN_H},
    {"OV2710_AWB_GAIN_PK_GREEN_GAIN_L"          , OV2710_AWB_GAIN_PK_GREEN_GAIN_L},
    {"OV2710_AWB_GAIN_PK_BLUE_GAIN_H"           , OV2710_AWB_GAIN_PK_BLUE_GAIN_H},
    {"OV2710_AWB_GAIN_PK_BLUE_GAIN_L"           , OV2710_AWB_GAIN_PK_BLUE_GAIN_L},
    {"OV2710_AWB_GAIN_PK_AWB_MAN_CTRL"          , OV2710_AWB_GAIN_PK_AWB_MAN_CTRL},
    {"OV2710_AEC_PK_EXPO_H"                     , OV2710_AEC_PK_EXPO_H},
    {"OV2710_AEC_PK_EXPO_M"                     , OV2710_AEC_PK_EXPO_M},
    {"OV2710_AEC_PK_EXPO_L"                     , OV2710_AEC_PK_EXPO_L},
    {"OV2710_AEC_PK_MANUAL"                     , OV2710_AEC_PK_MANUAL},
    {"OV2710_AEC_AGC_ADJ_H"                     , OV2710_AEC_AGC_ADJ_H},
    {"OV2710_AEC_AGC_ADJ_L"                     , OV2710_AEC_AGC_ADJ_L},
    {"OV2710_AEC_PK_VTS_H"                      , OV2710_AEC_PK_VTS_H},
    {"OV2710_AEC_PK_VTS_L"                      , OV2710_AEC_PK_VTS_L},
    {"0x3600"                                   , 0x3600},
    {"0x3603"                                   , 0x3603},
    {"0x3604"                                   , 0x3604},
    {"0x3605"                                   , 0x3605},
    {"0x3606"                                   , 0x3606},
    {"0x3620"                                   , 0x3620},
    {"OV2710_ANA_ARRAY_01"                      , OV2710_ANA_ARRAY_01},
    {"0x3623"                                   , 0x3623},
    {"0x3630"                                   , 0x3630},
    {"0x3631"                                   , 0x3631},
    {"0x3702"                                   , 0x3702},
    {"0x3703"                                   , 0x3703},
    {"0x3704"                                   , 0x3704},
    {"0x3706"                                   , 0x3706},
    {"0x370B"                                   , 0x370B},
    {"OV2710_SENSOR_REG0D"                      , OV2710_SENSOR_REG0D},
    {"0x3710"                                   , 0x3710},
    {"0x3712"                                   , 0x3712},
    {"0x3713"                                   , 0x3713},
    {"0x3714"                                   , 0x3714},
    {"OV2710_TIMING_CONTROL_HS_HIGHBYTE"        , OV2710_TIMING_CONTROL_HS_HIGHBYTE},
    {"OV2710_TIMING_CONTROL_HS_LOWBYTE"         , OV2710_TIMING_CONTROL_HS_LOWBYTE},
    {"OV2710_TIMING_CONTROL_VS_HIGHBYTE"        , OV2710_TIMING_CONTROL_VS_HIGHBYTE},
    {"OV2710_TIMING_CONTROL_VS_LOWBYTE"         , OV2710_TIMING_CONTROL_VS_LOWBYTE},
    {"OV2710_TIMING_CONTROL_HW_HIGH_BYTE"       , OV2710_TIMING_CONTROL_HW_HIGH_BYTE},
    {"OV2710_TIMING_CONTROL_HW_LOW_BYTE"        , OV2710_TIMING_CONTROL_HW_LOW_BYTE},
    {"OV2710_TIMING_CONTROL_VW_HIGH_BYTE"       , OV2710_TIMING_CONTROL_VW_HIGH_BYTE},
    {"OV2710_TIMING_CONTROL_VW_LOW_BYTE"        , OV2710_TIMING_CONTROL_VW_LOW_BYTE},
    {"OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH"     , OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH},
    {"OV2710_TIMING_CONTROL_DVP_HSIZE_LOW"      , OV2710_TIMING_CONTROL_DVP_HSIZE_LOW},
    {"OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH"     , OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH},
    {"OV2710_TIMING_CONTROL_DVP_VSIZE_LOW"      , OV2710_TIMING_CONTROL_DVP_VSIZE_LOW},
    {"OV2710_TIMING_CONTROL_HTS_HIGHBYTE"       , OV2710_TIMING_CONTROL_HTS_HIGHBYTE},
    {"OV2710_TIMING_CONTROL_HTS_LOWBYTE"        , OV2710_TIMING_CONTROL_HTS_LOWBYTE},
    {"OV2710_TIMING_CONTROL_VTS_HIGHBYTE"       , OV2710_TIMING_CONTROL_VTS_HIGHBYTE},
    {"OV2710_TIMING_CONTROL_VTS_LOWBYTE"        , OV2710_TIMING_CONTROL_VTS_LOWBYTE},
    {"OV2710_TIMING_CONTROL_HV_OFFSET"          , OV2710_TIMING_CONTROL_HV_OFFSET},
    {"0x3811"                                   , 0x3811},
    {"0x381C"                                   , 0x381C},
    {"0x381D"                                   , 0x381D},
    {"0x381E"                                   , 0x381E},
    {"0x381F"                                   , 0x381F},
    {"0x3820"                                   , 0x3820},
    {"0x3821"                                   , 0x3821},
    {"OV2710_TIMING_CONTROL18"                  , OV2710_TIMING_CONTROL18},
    {"0x381A"                                   , 0x381A},
    {"0x382E"                                   , 0x382E},
    {"OV2710_AEC_CONTROL0"                      , OV2710_AEC_CONTROL0},
    {"OV2710_AEC_CONTROL1"                      , OV2710_AEC_CONTROL1},
    {"OV2710_AEC_MAX_EXPO_60_H"                 , OV2710_AEC_MAX_EXPO_60_H},
    {"OV2710_AEC_MAX_EXPO_60_M"                 , OV2710_AEC_MAX_EXPO_60_M},
    {"OV2710_AEC_MAX_EXPO_60_L"                 , OV2710_AEC_MAX_EXPO_60_L},
    {"OV2710_AEC_B50_STEP_H"                    , OV2710_AEC_B50_STEP_H},
    {"OV2710_AEC_B50_STEP_L"                    , OV2710_AEC_B50_STEP_L},
    {"OV2710_AEC_B60_STEP_H"                    , OV2710_AEC_B60_STEP_H},
    {"OV2710_AEC_B60_STEP_L"                    , OV2710_AEC_B60_STEP_L},
    {"OV2710_AEC_CONTROLD"                      , OV2710_AEC_CONTROLD},
    {"OV2710_AEC_CONTROLE"                      , OV2710_AEC_CONTROLE},
    {"OV2710_AEC_CONTROLF"                      , OV2710_AEC_CONTROLF},
    {"OV2710_AEC_CONTROL10"                     , OV2710_AEC_CONTROL10},
    {"OV2710_AEC_CONTROL11"                     , OV2710_AEC_CONTROL11},
    {"OV2710_AEC_CONTROL12"                     , OV2710_AEC_CONTROL12},
    {"OV2710_AEC_CONTROL13"                     , OV2710_AEC_CONTROL13},
    {"OV2710_AEC_MAX_EXPO_50_H"                 , OV2710_AEC_MAX_EXPO_50_H},
    {"OV2710_AEC_MAX_EXPO_50_M"                 , OV2710_AEC_MAX_EXPO_50_M},
    {"OV2710_AEC_MAX_EXPO_50_L"                 , OV2710_AEC_MAX_EXPO_50_L},
    {"OV2710_AEC_CONTROL17"                     , OV2710_AEC_CONTROL17},
    {"OV2710_AEC_G_CEIL_H"                      , OV2710_AEC_G_CEIL_H},
    {"OV2710_AEC_G_CEIL_L"                      , OV2710_AEC_G_CEIL_L},
    {"0x3A1A"                                   , 0x3A1A},
    {"OV2710_AEC_CONTROL1B"                     , OV2710_AEC_CONTROL1B},
    {"OV2710_AEC_LED_ADD_ROW_H"                 , OV2710_AEC_LED_ADD_ROW_H},
    {"OV2710_AEC_LED_ADD_ROW_L"                 , OV2710_AEC_LED_ADD_ROW_L},
    {"OV2710_AEC_CONTROL1E"                     , OV2710_AEC_CONTROL1E},
    {"OV2710_AEC_CONTROL1F"                     , OV2710_AEC_CONTROL1F},
    {"OV2710_AEC_CONTROL20"                     , OV2710_AEC_CONTROL20},
    {"OV2710_OTP_DATA_0"                        , OV2710_OTP_DATA_0},
    {"OV2710_OTP_DATA_1"                        , OV2710_OTP_DATA_1},
    {"OV2710_OTP_DATA_2"                        , OV2710_OTP_DATA_2},
    {"OV2710_OTP_DATA_3"                        , OV2710_OTP_DATA_3},
    {"OV2710_OTP_DATA_4"                        , OV2710_OTP_DATA_4},
    {"OV2710_OTP_DATA_5"                        , OV2710_OTP_DATA_5},
    {"OV2710_OTP_DATA_6"                        , OV2710_OTP_DATA_6},
    {"OV2710_OTP_DATA_7"                        , OV2710_OTP_DATA_7},
    {"OV2710_OTP_DATA_8"                        , OV2710_OTP_DATA_8},
    {"OV2710_OTP_DATA_9"                        , OV2710_OTP_DATA_9},
    {"OV2710_OTP_DATA_A"                        , OV2710_OTP_DATA_A},
    {"OV2710_OTP_DATA_B"                        , OV2710_OTP_DATA_B},
    {"OV2710_OPT_DATA_C"                        , OV2710_OTP_DATA_C},
    {"OV2710_OPT_DATA_D"                        , OV2710_OTP_DATA_D},
    {"OV2710_OPT_DATA_E"                        , OV2710_OTP_DATA_E},
    {"OV2710_OPT_DATA_F"                        , OV2710_OTP_DATA_F},
    {"OV2710_OTP_CONTROL"                       , OV2710_OTP_CONTROL},
    {"OV2710_BIST_CTRL07"                       , OV2710_BIST_CTRL07},
    {"OV2710_BIST_CTRL12"                       , OV2710_BIST_CTRL12},
    {"OV2710_BIST_RESULT"                       , OV2710_BIST_RESULT},
    {"OV2710_BIST_DONE"                         , OV2710_BIST_DONE},
    {"OV2710_BLC_CONTROL_00"                    , OV2710_BLC_CONTROL_00},
    {"OV2710_BLC_CONTROL_01"                    , OV2710_BLC_CONTROL_01},
    {"OV2710_BLC_CONTROL_02"                    , OV2710_BLC_CONTROL_02},
    {"0x4006"                                   , 0x4006},
    {"0x4007"                                   , 0x4007},
    {"OV2710_BLC_FRAME_CONTROL"                 , OV2710_BLC_FRAME_CONTROL},
    {"OV2710_FRAME_CTRL00"                      , OV2710_FRAME_CTRL00},
    {"OV2710_FRAME_CTRL01"                      , OV2710_FRAME_CTRL01},
    {"0x4301"                                   , 0x4301},
    {"0x4303"                                   , 0x4303},
    {"OV2710_DVP_CTRL00"                        , OV2710_DVP_CTRL00},
    {"OV2710_DVP_CTRL01"                        , OV2710_DVP_CTRL01},
    {"OV2710_DVP_CTRL02"                        , OV2710_DVP_CTRL02},
    {"OV2710_DVP_CTRL03"                        , OV2710_DVP_CTRL03},
    {"OV2710_MIPI_CTRL_00"                      , OV2710_MIPI_CTRL_00},
    {"OV2710_MIPI_CTRL_01"                      , OV2710_MIPI_CTRL_01},
    {"OV2710_MIPI_CTRL_03"                      , OV2710_MIPI_CTRL_03},
    {"OV2710_MIPI_CTRL_04"                      , OV2710_MIPI_CTRL_04},
    {"OV2710_MIPI_CTRL_05"                      , OV2710_MIPI_CTRL_05},
    {"OV2710_MAX_FCNT_H"                        , OV2710_MAX_FCNT_H},
    {"OV2710_MAX_FCNT_L"                        , OV2710_MAX_FCNT_L},
    {"OV2710_MIN_SPKT_WC_REG_H"                 , OV2710_MIN_SPKT_WC_REG_H},
    {"OV2710_MIN_SPKT_WC_REG_L"                 , OV2710_MIN_SPKT_WC_REG_L},
    {"OV2710_MIPI_CTRL_14"                      , OV2710_MIPI_CTRL_14},
    {"OV2710_MIPI_SPKT_DT"                      , OV2710_MIPI_SPKT_DT},
    {"OV2710_MIN_HS_ZERO_H"                     , OV2710_MIN_HS_ZERO_H},
    {"OV2710_MIN_HS_ZERO_L"                     , OV2710_MIN_HS_ZERO_L},
    {"OV2710_MIN_MIPI_HS_TRAIL_H"               , OV2710_MIN_MIPI_HS_TRAIL_H},
    {"OV2710_MIN_MIPI_HS_TRAIL_L"               , OV2710_MIN_MIPI_HS_TRAIL_L},
    {"OV2710_MIN_MIPI_CLK_ZERO_H"               , OV2710_MIN_MIPI_CLK_ZERO_H},
    {"OV2710_MIN_MIPI_CLK_ZERO_L"               , OV2710_MIN_MIPI_CLK_ZERO_L},
    {"OV2710_MIN_MIPI_CLK_PREPARE_H"            , OV2710_MIN_MIPI_CLK_PREPARE_H},
    {"OV2710_MIN_MIPI_CLK_PREPARE_L"            , OV2710_MIN_MIPI_CLK_PREPARE_L},
    {"OV2710_MIN_CLK_POST_H"                    , OV2710_MIN_CLK_POST_H},
    {"OV2710_MIN_CLK_POST_L"                    , OV2710_MIN_CLK_POST_L},
    {"OV2710_MIN_CLK_TRAIL_H"                   , OV2710_MIN_CLK_TRAIL_H},
    {"OV2710_MIN_CLK_TRAIL_L"                   , OV2710_MIN_CLK_TRAIL_L},
    {"OV2710_MIN_LPX_PCLK_H"                    , OV2710_MIN_LPX_PCLK_H},
    {"OV2710_MIN_LPX_PCLK_L"                    , OV2710_MIN_LPX_PCLK_L},
    {"OV2710_MIN_HS_PREPARE_H"                  , OV2710_MIN_HS_PREPARE_H},
    {"OV2710_MIN_HS_PREPARE_L"                  , OV2710_MIN_HS_PREPARE_L},
    {"OV2710_MIN_HS_EXIT_H"                     , OV2710_MIN_HS_EXIT_H},
    {"OV2710_MIN_HS_EXIT_L"                     , OV2710_MIN_HS_EXIT_L},
    {"OV2710_MIN_HS_ZERO_UI"                    , OV2710_MIN_HS_ZERO_UI},
    {"OV2710_MIN_HS_TRAIL_UI"                   , OV2710_MIN_HS_TRAIL_UI},
    {"OV2710_MIN_CLK_ZERO_UI"                   , OV2710_MIN_CLK_ZERO_UI},
    {"OV2710_MIN_CLK_PREPARE_UI"                , OV2710_MIN_CLK_PREPARE_UI},
    {"OV2710_MIN_CLK_POST_UI"                   , OV2710_MIN_CLK_POST_UI},
    {"OV2710_MIN_CLK_TRAIL_UI"                  , OV2710_MIN_CLK_TRAIL_UI},
    {"OV2710_MIN_LPX_PCLK_UI"                   , OV2710_MIN_LPX_PCLK_UI},
    {"OV2710_MIN_HS_PREPARE_UI"                 , OV2710_MIN_HS_PREPARE_UI},
    {"OV2710_MIN_HS_EXIT_UI"                    , OV2710_MIN_HS_EXIT_UI},
    {"OV2710_ISP_CONTROL0"                      , OV2710_ISP_CONTROL0},
    {"OV2710_ISP_CONTROL1"                      , OV2710_ISP_CONTROL1},
    {"OV2710_ISP_CONTROL2"                      , OV2710_ISP_CONTROL2},
    {"OV2710_ISP_CONTROL5"                      , OV2710_ISP_CONTROL5},
    {"OV2710_ISP_CONTROL31"                     , OV2710_ISP_CONTROL31},
    {"OV2710_ISP_TEST"                          , OV2710_ISP_TEST},
    {"OV2710_ISP_SENSOR_BIAS_READOUT"           , OV2710_ISP_SENSOR_BIAS_READOUT},
    {"OV2710_ISP_SENSOR_GAIN_READOUT"           , OV2710_ISP_SENSOR_GAIN_READOUT},
    {"OV2710_AWB_CONTROL_00"                    , OV2710_AWB_CONTROL_00},
    {"OV2710_AWB_CONTROL_01"                    , OV2710_AWB_CONTROL_01},
    {"OV2710_AWB_CONTROL_02"                    , OV2710_AWB_CONTROL_02},
    {"OV2710_STABLE_RANGE_WIDE"                 , OV2710_STABLE_RANGE_WIDE},
    {"OV2710_RED_GAIN_LIMIT"                    , OV2710_RED_GAIN_LIMIT},
    {"OV2710_GREEN_GAIN_LIMIT"                  , OV2710_GREEN_GAIN_LIMIT},
    {"OV2710_BLUE_GAIN_LIMIT"                   , OV2710_BLUE_GAIN_LIMIT},
    {"OV2710_AWB_FRAME_COUNTER"                 , OV2710_AWB_FRAME_COUNTER},
    {"OV2710_RED_BEFORE_GAIN_AVERAGE"           , OV2710_RED_BEFORE_GAIN_AVERAGE},
    {"OV2710_GREEN_BEFORE_GAIN_AVERAGE"         , OV2710_GREEN_BEFORE_GAIN_AVERAGE},
    {"OV2710_BLUE_BEFORE_GAIN_AVERAGE"          , OV2710_BLUE_BEFORE_GAIN_AVERAGE},
    {"OV2710_RED_AFTER_GAIN_AVERAGE_H"          , OV2710_RED_AFTER_GAIN_AVERAGE_H},
    {"OV2710_RED_AFTER_GAIN_AVERAGE_L"          , OV2710_RED_AFTER_GAIN_AVERAGE_L},
    {"OV2710_GREEN_AFTER_GAIN_AVERAGE_H"        , OV2710_GREEN_AFTER_GAIN_AVERAGE_H},
    {"OV2710_GREEN_AFTER_GAIN_AVERAGE_L"        , OV2710_GREEN_AFTER_GAIN_AVERAGE_L},
    {"OV2710_BLUE_AFTER_GAIN_AVERAGE_H"         , OV2710_BLUE_AFTER_GAIN_AVERAGE_H},
    {"OV2710_BLUE_AFTER_GAIN_AVERAGE_L"         , OV2710_BLUE_AFTER_GAIN_AVERAGE_L},
    {"OV2710_AVG_START_POSITION_AT_HORIZONTAL_H", OV2710_AVG_START_POSITION_AT_HORIZONTAL_H},
    {"OV2710_AVG_START_POSITION_AT_HORIZONTAL_L", OV2710_AVG_START_POSITION_AT_HORIZONTAL_L},
    {"OV2710_AVG_END_POSITION_AT_HORIZONTAL_H"  , OV2710_AVG_END_POSITION_AT_HORIZONTAL_H},
    {"OV2710_AVG_END_POSITION_AT_HORIZONTAL_L"  , OV2710_AVG_END_POSITION_AT_HORIZONTAL_L},
    {"OV2710_AVG_START_POSITION_AT_VERTICAL_H"  , OV2710_AVG_START_POSITION_AT_VERTICAL_H},
    {"OV2710_AVG_START_POSITION_AT_VERTICAL_L"  , OV2710_AVG_START_POSITION_AT_VERTICAL_L},
    {"OV2710_AVG_END_POSITION_AT_VERTICAL_H"    , OV2710_AVG_END_POSITION_AT_VERTICAL_H},
    {"OV2710_AVG_END_POSITION_AT_VERTICAL_L"    , OV2710_AVG_END_POSITION_AT_VERTICAL_L},
    {"0x5688"                                   , 0x5688},
    {"OV2710_AVG_R10"                           , OV2710_AVG_R10},
    {"OV2710_DPC_CTRL00"                        , OV2710_DPC_CTRL00},
    {"OV2710_WHITE_THRESHOLD_LIST0"             , OV2710_WHITE_THRESHOLD_LIST0},
    {"OV2710_WHITE_THRESHOLD_LIST1"             , OV2710_WHITE_THRESHOLD_LIST1},
    {"OV2710_WHITE_THRESHOLD_LIST2"             , OV2710_WHITE_THRESHOLD_LIST2},
    {"OV2710_WHITE_THRESHOLD_LIST3"             , OV2710_WHITE_THRESHOLD_LIST3},
    {"OV2710_BLACK_THRESHOLD_LIST0"             , OV2710_BLACK_THRESHOLD_LIST0},
    {"OV2710_BLACK_THRESHOLD_LIST1"             , OV2710_BLACK_THRESHOLD_LIST1},
    {"OV2710_BLACK_THRESHOLD_LIST2"             , OV2710_BLACK_THRESHOLD_LIST2},
    {"OV2710_BLACK_THRESHOLD_LIST3"             , OV2710_BLACK_THRESHOLD_LIST3},
    {"OV2710_GAIN_LIST1"                        , OV2710_GAIN_LIST1},
    {"OV2710_GAIN_LIST2"                        , OV2710_GAIN_LIST2},
    {"OV2710_DPC_CTRL01"                        , OV2710_DPC_CTRL01},
    {"OV2710_DPC_SATURATE"                      , OV2710_DPC_SATURATE},
    {"OV2710_PATTERN_THRESHOLD_LIST0H"          , OV2710_PATTERN_THRESHOLD_LIST0H},
    {"OV2710_PATTERN_THRESHOLD_LIST0L"          , OV2710_PATTERN_THRESHOLD_LIST0L},
    {"OV2710_PATTERN_THRESHOLD_LIST1H"          , OV2710_PATTERN_THRESHOLD_LIST1H},
    {"OV2710_PATTERN_THRESHOLD_LIST1L"          , OV2710_PATTERN_THRESHOLD_LIST1L},
    {"OV2710_PATTERN_THRESHOLD_LIST2H"          , OV2710_PATTERN_THRESHOLD_LIST2H},
    {"OV2710_PATTERN_THRESHOLD_LIST2L"          , OV2710_PATTERN_THRESHOLD_LIST2L},
    {"OV2710_PATTERN_THRESHOLD_H"               , OV2710_PATTERN_THRESHOLD_H},
    {"OV2710_PATTERN_THRESHOLD_L"               , OV2710_PATTERN_THRESHOLD_L},
    {"OV2710_LENC_RED_X0_H"                     , OV2710_LENC_RED_X0_H},
    {"OV2710_LENC_RED_X0_L"                     , OV2710_LENC_RED_X0_L},
    {"OV2710_LENC_RED_Y0_H"                     , OV2710_LENC_RED_Y0_H},
    {"OV2710_LENC_RED_Y0_L"                     , OV2710_LENC_RED_Y0_L},
    {"OV2710_LENC_RED_A1"                       , OV2710_LENC_RED_A1},
    {"OV2710_LENC_RED_A2"                       , OV2710_LENC_RED_A2},
    {"OV2710_LENC_RED_B1"                       , OV2710_LENC_RED_B1},
    {"OV2710_LENC_RED_B2"                       , OV2710_LENC_RED_B2},
    {"OV2710_LENC_GRN_X0_H"                     , OV2710_LENC_GRN_X0_H},
    {"OV2710_LENC_GRN_X0_L"                     , OV2710_LENC_GRN_X0_L},
    {"OV2710_LENC_GRN_Y0_H"                     , OV2710_LENC_GRN_Y0_H},
    {"OV2710_LENC_GRN_Y0_L"                     , OV2710_LENC_GRN_Y0_L},
    {"OV2710_LENC_GRN_A0_H"                     , OV2710_LENC_GRN_A0_H},
    {"OV2710_LENC_GRN_A0_L"                     , OV2710_LENC_GRN_A0_L},
    {"OV2710_LENC_GRN_B1"                       , OV2710_LENC_GRN_B1},
    {"OV2710_LENC_GRN_B2"                       , OV2710_LENC_GRN_B2},
    {"OV2710_LENC_BLU_X0_H"                     , OV2710_LENC_BLU_X0_H},
    {"OV2710_LENC_BLU_X0_L"                     , OV2710_LENC_BLU_X0_L},
    {"OV2710_LENC_BLU_Y0_H"                     , OV2710_LENC_BLU_Y0_H},
    {"OV2710_LENC_BLU_Y0_L"                     , OV2710_LENC_BLU_Y0_L},
    {"OV2710_LENC_BLU_A1"                       , OV2710_LENC_BLU_A1},
    {"OV2710_LENC_BLU_A2"                       , OV2710_LENC_BLU_A2},
    {"OV2710_LENC_BLU_B1"                       , OV2710_LENC_BLU_B1},
    {"OV2710_LENC_BLU_B2"                       , OV2710_LENC_BLU_B2},
    {"OV2710_LENC_CTRL00"                       , OV2710_LENC_CTRL00},
    {"OV2710_LENC_COEF_TH"                      , OV2710_LENC_COEF_TH},
    {"OV2710_LENC_GAIN_THRE1"                   , OV2710_LENC_GAIN_THRE1},
    {"OV2710_LENC_GAIN_THRE2"                   , OV2710_LENC_GAIN_THRE2},
    {"OV2710_LENC_COEF_MAN"                     , OV2710_LENC_COEF_MAN},
    {"OV2710_AFC_CTRL00"                        , OV2710_AFC_CTRL00},
    {"OV2710_AFC_CTRL01"                        , OV2710_AFC_CTRL01},
    {"OV2710_AFC_CTRL02"                        , OV2710_AFC_CTRL02},
    {"OV2710_AFC_CTRL03"                        , OV2710_AFC_CTRL03},
    {"OV2710_AFC_CTRL04"                        , OV2710_AFC_CTRL04},
    {"OV2710_AFC_CTRL05"                        , OV2710_AFC_CTRL05},
    {"OV2710_AFC_CTRL06"                        , OV2710_AFC_CTRL06},
    {"OV2710_AFC_CTRL07"                        , OV2710_AFC_CTRL07},
    {"OV2710_AFC_CTRL08"                        , OV2710_AFC_CTRL08},
    {"OV2710_AFC_CTRL09"                        , OV2710_AFC_CTRL09},
    {"OV2710_AFC_CTRL10"                        , OV2710_AFC_CTRL10},
    {"OV2710_AFC_CTRL11"                        , OV2710_AFC_CTRL11},
    {"OV2710_AFC_CTRL12"                        , OV2710_AFC_CTRL12},
    {"OV2710_AFC_CTRL13"                        , OV2710_AFC_CTRL13},
    {"OV2710_AFC_CTRL14"                        , OV2710_AFC_CTRL14},
    {"OV2710_AFC_CTRL15"                        , OV2710_AFC_CTRL15},
    {"OV2710_AFC_CTRL16"                        , OV2710_AFC_CTRL16},
    {"OV2710_AFC_CTRL17"                        , OV2710_AFC_CTRL17},
    {"OV2710_AFC_CTRL18"                        , OV2710_AFC_CTRL18},
    {"OV2710_AFC_CTRL19"                        , OV2710_AFC_CTRL19},
    {"OV2710_AFC_CTRL20"                        , OV2710_AFC_CTRL20},
};

//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************
static GERR ov2710_write_reg( GD_HANDLE* pHandle, U16 subaddr, U8 data)
{
    U8 pbuf[3];
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if (device->handleI2C == NULL)
    {
        return GD_ERR_I2C_NOT_OPEN;
    }

    pbuf[0] = (subaddr >> 0x08) & 0xff;
    pbuf[1] = (subaddr & 0xff);
    pbuf[2] = data;
    return GD_I2C_Write(&device->handleI2C, device->i2cAddrSensor, pbuf, 3);
}

static GERR ov2710_read_reg( GD_HANDLE* pHandle, U16 subaddr, U8 *pdata)
{
    U8 pbuf0[2];
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if (device->handleI2C == NULL)
    {
        return GD_ERR_I2C_NOT_OPEN;
    }

    pbuf0[0] = (subaddr >> 0x08) & 0xff;
    pbuf0[1] = (subaddr & 0xff);

    return GD_I2C_Read(&device->handleI2C, device->i2cAddrSensor, pbuf0, 2, pdata, 1);
}

static void ov2710_dump_reg(GD_HANDLE* pHandle)
{
    U32 nCount,i;
    U8 reg_data;

    nCount = sizeof(reg2710_dump)/sizeof(GD_SENSOR_REG_S);
    GM_Printf("Addr(04x)  Data(02x) name\n");
    for(i=0;i<nCount;i++)
    {
        if(ov2710_read_reg(pHandle, reg2710_dump[i].regAddr, &reg_data) == GD_OK)
        {
            GM_Printf("0x%04x  0x%02x  %s\n", reg2710_dump[i].regAddr, reg_data, reg2710_dump[i].name);
        }
        else
        {
            GM_Printf("GD_SENSOR_DoCmd I2C failed!\n");
        }
    }
}

static void ov2710_fill_video_format_regs(GD_HANDLE* pHandle)
{
    int i;
    U32 index;
    U32 format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov2710_fill_video_format_regs \n");
#endif
    index = pinfo->current_video_index;
    format_index = ov2710_video_info_table[index].format_index;

    for (i = 0; i < OV2710_VIDEO_FORMAT_REG_NUM; i++)
    {
        if (ov2710_video_format_tbl.reg[i] == 0)
            break;

        ov2710_write_reg(pHandle,
                  ov2710_video_format_tbl.reg[i],
                  ov2710_video_format_tbl.table[format_index].data[i]);
    }

    if (ov2710_video_format_tbl.table[format_index].ext_reg_fill)
        ov2710_video_format_tbl.table[format_index].ext_reg_fill(pHandle);

}

static void ov2710_fill_share_regs(GD_HANDLE* pHandle)
{
    int i;
    for (i = 0; i < OV2710_SHARE_REG_SIZE; i++)
    {
        ov2710_write_reg(pHandle, ov2710_share_regs[i].reg, ov2710_share_regs[i].data);
        if (ov2710_share_regs[i].reg == OV2710_SYSTEM_CONTROL00)
        {
            GD_SENSOR_Sleep(10);
        }
    }
}

static void ov2710_fill_pll_regs(GD_HANDLE* pHandle)
{
    int i;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov2710_fill_pll_regs\n");
#endif

    for (i = 0; i < OV2710_VIDEO_PLL_REG_TABLE_SIZE; i++)
    {
        ov2710_write_reg(pHandle, ov2710_pll_tbl[pinfo->pll_index].regs[i].reg,
            ov2710_pll_tbl[pinfo->pll_index].regs[i].data);
    }
    GD_SENSOR_Sleep(2);
}

static void ov2710_set_streaming(GD_HANDLE* pHandle)
{
    U8 data;
    ov2710_read_reg(pHandle, OV2710_SYSTEM_CONTROL00, &data);
    ov2710_write_reg(pHandle, OV2710_SYSTEM_CONTROL00, (data & 0xBF));
}

static GERR ov2710_sw_reset(GD_HANDLE* pHandle)
{
    U8   data;
    GERR gerr;

    gerr = ov2710_read_reg(pHandle, OV2710_SYSTEM_CONTROL00, &data);
    if(gerr != GD_OK)
    {
        return gerr;
    }
    gerr = ov2710_write_reg(pHandle, OV2710_SYSTEM_CONTROL00, (data | 0x80));
    GD_SENSOR_Sleep(10);
    return gerr;
}

static GERR ov2710_reset(GD_HANDLE* pHandle)
{
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if(device->powerGPIO)
    {
        GD_GPIO_Write(device->resetGPIO, 1);
        GD_SENSOR_Sleep(10);
    }
    if(device->resetGPIO)
    {
        GD_GPIO_Write(device->resetGPIO, 0);
        GD_SENSOR_Sleep(10);
    }
    if(device->powerGPIO)
    {
        GD_GPIO_Write(device->resetGPIO, 0);
        GD_SENSOR_Sleep(10);
    }
    if(device->resetGPIO)
    {
        GD_GPIO_Write(device->resetGPIO, 1);
        GD_SENSOR_Sleep(10);
    }
    return ov2710_sw_reset(pHandle);
}

static GERR ov2710_get_video_mode(GD_HANDLE* pHandle, GD_VIDEO_MODE_E *p_mode)
{
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_mode = pinfo->current_vin_mode;

    return GD_OK;
}

static GERR ov2710_get_video_info(GD_HANDLE* pHandle, GD_SENSOR_VIDEO_INFO_S* p_video_info)
{
    GERR    errCode = GD_OK;
    U32     index;
    U32     format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;

    if (index >= OV2710_VIDEO_INFO_TABLE_SIZE)
    {
        p_video_info->width     = 0;
        p_video_info->height    = 0;
        p_video_info->fps       = 0;
        p_video_info->format    = 0;
        p_video_info->type      = 0;
        p_video_info->bits      = 0;
        p_video_info->ratio     = 0;
        p_video_info->system    = 0;
        p_video_info->rev       = 0;

        //errCode = -EPERM;
        errCode = GD_ERR_BAD_PARAMETER;
    }
    else
    {
        format_index = ov2710_video_info_table[index].format_index;

        p_video_info->width     = ov2710_video_info_table[index].def_width;
        p_video_info->height    = ov2710_video_info_table[index].def_height;
        p_video_info->fps       = pinfo->frame_rate;
        p_video_info->format    = ov2710_video_format_tbl.table[format_index].format;
        p_video_info->type      = ov2710_video_format_tbl.table[format_index].type;
        p_video_info->bits      = ov2710_video_format_tbl.table[format_index].bits;
        p_video_info->ratio     = ov2710_video_format_tbl.table[format_index].ratio;
        p_video_info->system    = GD_VIDEO_SYSTEM_AUTO;
        p_video_info->rev       = 0;
    }

    return errCode;
}

static GERR ov2710_get_agc_info(GD_HANDLE* pHandle, GD_SENSOR_AGC_INFO_S * p_agc_info)
{
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_agc_info = pinfo->agc_info;

    return GD_OK;
}

static GERR ov2710_get_shutter_info(GD_HANDLE* pHandle, GD_SENSOR_SHUTTER_INFO_S * pshutter_info)
{
    memset(pshutter_info, 0x00, sizeof(GD_SENSOR_SHUTTER_INFO_S));

    return GD_OK;
}

#if 0
static GERR ov2710_check_video_mode(GD_HANDLE* pHandle, amba_vin_source_mode_info* p_mode_info)
{
    GERR errCode = GD_OK;
    int  i;
    U32  index;
    U32  format_index;

    p_mode_info->is_supported = 0;
    memset(p_mode_info->fps_table, 0, p_mode_info->fps_table_size);
    memset(&p_mode_info->video_info, 0, sizeof (p_mode_info->video_info));

    for (i = 0; i < OV2710_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (ov2710_video_mode_table[i].mode == p_mode_info->mode)
        {
            if (p_mode_info->mode == GD_VIDEO_MODE_AUTO)
                p_mode_info->mode = OV2710_VIDEO_MODE_TABLE_AUTO;
            p_mode_info->is_supported = 1;

            index = ov2710_video_mode_table[i].still_index;
            format_index = ov2710_video_info_table[index].format_index;

            p_mode_info->video_info.width   = ov2710_video_info_table[index].def_width;
            p_mode_info->video_info.height  = ov2710_video_info_table[index].def_height;
            p_mode_info->video_info.fps     = ov2710_video_format_tbl.table[format_index].max_fps;
            p_mode_info->video_info.format  = ov2710_video_format_tbl.table[format_index].format;
            p_mode_info->video_info.type    = ov2710_video_format_tbl.table[format_index].type;
            p_mode_info->video_info.bits    = ov2710_video_format_tbl.table[format_index].bits;
            p_mode_info->video_info.ratio   = ov2710_video_format_tbl.table[format_index].ratio;
            p_mode_info->video_info.system  = GD_VIDEO_SYSTEM_AUTO;
            p_mode_info->video_info.rev     = 0;

            break;
        }
    }

    return errCode;
}
#endif
static GERR ov2710_query_sensor_id(GD_HANDLE* pHandle, U16 * ss_id)
{
    GERR errCode = GD_OK;
    U8   id_h, id_l;

    errCode = ov2710_read_reg(pHandle, OV2710_PIDH, &id_h);
    errCode = ov2710_read_reg(pHandle, OV2710_PIDL, &id_l);
    *ss_id = (id_h<<8)|id_l;

    return errCode;

}
static GERR ov2710_set_still_mode(GD_HANDLE* pHandle, gd_vin_src_still_info_s *p_info)
{
    return GD_OK;
}

static GERR ov2710_set_low_light_agc(GD_HANDLE* pHandle, U32 agc_index)
{
    return GD_OK;
}

static GERR ov2710_set_shutter_time(GD_HANDLE* pHandle, U32 shutter_time)
{
    GERR    errCode = 0;
    U64     exposure_time_q9;
    U32     line_length, frame_length_lines;
    int     shutter_width;
    U8      data_l, data_h;

    ov2710_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov2710_set_shutter: 0x%x\n", shutter_time);
#endif

    pll_table = &ov2710_pll_tbl[pinfo->pll_index];

    exposure_time_q9 = shutter_time;

    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_HTS_HIGHBYTE, &data_h);
    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_HTS_LOWBYTE, &data_l);
    line_length = (data_h<<8) + data_l;
    if(!line_length)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("line length is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_VTS_HIGHBYTE, &data_h);
    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_VTS_LOWBYTE, &data_l);
    frame_length_lines = (data_h<<8) + data_l;
    // frame_length_lines = 0x45D
    // exposure_time_q9 = 0, 8533333
    // pll_table->pixclk = 81000000
    // line_length = 0x974
    exposure_time_q9 = exposure_time_q9 * (U64)pll_table->pixclk;

    //DO_DIV_ROUND(exposure_time_q9, line_length);
    //DO_DIV_ROUND(exposure_time_q9, 512000000);
    exposure_time_q9 = (exposure_time_q9 + line_length/2) / line_length;
    exposure_time_q9 = (exposure_time_q9 + 512000000/2) / 512000000;

    // exposure_time_q9 = 0, 0x22E
    shutter_width = (U32)exposure_time_q9;

    /* FIXME: shutter width: 1 ~ (Frame format(V) - 3) */
    if(shutter_width < 1)
    {
        shutter_width = 1;
    }
    else if(shutter_width  > (frame_length_lines - 3))
    {
        shutter_width = frame_length_lines - 3;
    }
    // shutter_width = 1,
#ifdef SENSOR_DEBUG
    GM_Printf("V:%d, shutter_width: %d\n", frame_length_lines, shutter_width);
#endif
    shutter_width <<= 4; //the register value should be exposure time * 16

    errCode |= ov2710_write_reg(pHandle, OV2710_AEC_PK_EXPO_H, (U8)((shutter_width & 0x0F0000) >> 16) );
    errCode |= ov2710_write_reg(pHandle, OV2710_AEC_PK_EXPO_M, (U8)((shutter_width & 0x00FF00) >> 8 ) );
    errCode |= ov2710_write_reg(pHandle, OV2710_AEC_PK_EXPO_L, (U8)((shutter_width & 0x0000FF) >> 0 ) );

    pinfo->current_shutter_time = shutter_time;
    //G_shutter_time = shutter_time;
    return errCode;
}

static GERR ov2710_set_agc_db(GD_HANDLE* pHandle, S32 agc_db)
{
    U32 gain_index;
    S32 db_max;
    S32 db_step;

    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov2710_set_agc: 0x%x\n", agc_db);
#endif

    db_max = pinfo->agc_info.db_max;
    db_step = pinfo->agc_info.db_step;
    gain_index = (db_max - agc_db) / db_step;

    if (gain_index > OV2710_GAIN_0DB)
        gain_index = OV2710_GAIN_0DB;
    if ((gain_index >= pinfo->min_agc_index) && (gain_index <= pinfo->max_agc_index))
    {

        ov2710_write_reg(pHandle, OV2710_GROUP_ACCESS, 0x00);

        ov2710_write_reg(pHandle, OV2710_AEC_AGC_ADJ_H, (U8)OV2710_GAIN_TABLE[gain_index][OV2710_GAIN_COL_REG300A]);
        ov2710_write_reg(pHandle, OV2710_AEC_AGC_ADJ_L, OV2710_GAIN_TABLE[gain_index][OV2710_GAIN_COL_REG300B]);

        ov2710_write_reg(pHandle, OV2710_GROUP_ACCESS, 0x10);
        ov2710_write_reg(pHandle, OV2710_GROUP_ACCESS, 0xA0);

        pinfo->current_gain_db = agc_db;

        return GD_OK;
    }
    else
    {
        return GD_ERR_BAD_PARAMETER;
        //return -1;
    }
}

static GERR ov2710_set_mirror_mode(GD_HANDLE* pHandle, GD_SENSOR_MIRROR_MODE_S *mirror_mode)
{
    GERR    errCode = GD_OK;
    U32     readmode;
    U8      tmp_reg;
    U8      ana_reg;
    U8      vstart_reg;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    switch (mirror_mode->pattern)
    {
    case GD_VIN_SRC_MIRROR_HORRIZONTALLY_VERTICALLY:
        readmode    = OV2710_MIRROR_ROW + OV2710_MIRROR_COLUMN;
        ana_reg     = 0x14;
        vstart_reg  = 0x09;
        break;
    case GD_VIN_SRC_MIRROR_HORRIZONTALLY:
        readmode    = OV2710_MIRROR_ROW;
        ana_reg     = 0x14;
        vstart_reg  = 0x0a;
        break;
    case GD_VIN_SRC_MIRROR_VERTICALLY:
        readmode    = OV2710_MIRROR_COLUMN;
        ana_reg     = 0x04;
        vstart_reg  = 0x09;
        break;
    case GD_VIN_SRC_MIRROR_NONE:
        readmode    = 0;
        ana_reg     = 0x04;
        vstart_reg  = 0x0a;
        break;
    default:
#ifdef SENSOR_DEBUG
        GM_Printf("do not support cmd mirror mode\n");
#endif
        return GD_ERR_BAD_PARAMETER;
        //return -EINVAL;
        //break;
    }
    pinfo->bayer_pattern = mirror_mode->bayer_pattern;
    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL18, &tmp_reg);
    tmp_reg &= (~OV2710_MIRROR_MASK);
    tmp_reg |= readmode;
    errCode |= ov2710_write_reg(pHandle, OV2710_TIMING_CONTROL18, tmp_reg);
    errCode |= ov2710_write_reg(pHandle, OV2710_ANA_ARRAY_01, ana_reg);
    errCode |= ov2710_write_reg(pHandle, OV2710_TIMING_CONTROL_VS_LOWBYTE, vstart_reg);

    return errCode;
}

static GERR ov2710_set_anti_flicker(GD_HANDLE* pHandle, S32 anti_option)
{
    GERR errCode = GD_OK;
        /* >> TODO, for YUV output sensor only << */
    return errCode;
}

static GERR ov2710_set_fps(GD_HANDLE* pHandle, U32 fps)
{
    GERR        errCode = GD_OK;
    U32         frame_time = 0;
    U32         index;
    U32         format_index;
    U64         frame_time_pclk;
    int         vertical_lines = 0;
    U32         line_length;
    U8          data_l, data_h;
    // LindengYu
    //amba_vin_irq_fix vin_irq_fix;
    ov2710_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;
    // index = 2
    format_index = ov2710_video_info_table[index].format_index;
    // format_index = 2
    // pinfo->pll_index = 0
    pll_table = &ov2710_pll_tbl[pinfo->pll_index];

    if (fps == GD_VIDEO_FPS_AUTO)
    {
        fps = ov2710_video_format_tbl.table[format_index].auto_fps;
        // fps = GD_VIDEO_FPS_29_97
    }
    if(fps < ov2710_video_format_tbl.table[format_index].max_fps)
    {
        // LindengYu
#ifdef SENSOR_DEBUG
        //GM_Printf("The max supported fps is %d\n",
        //    DIV_ROUND(512000000, ov2710_video_format_tbl.table[format_index].max_fps));
#endif
        return GD_ERR_BAD_PARAMETER;//-EPERM;
    }

    frame_time = fps;

    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_HTS_HIGHBYTE, &data_h);
    errCode |= ov2710_read_reg(pHandle, OV2710_TIMING_CONTROL_HTS_LOWBYTE, &data_l);
    line_length = (data_h<<8) + data_l;
    // line_length = 0x974;
    if(!line_length)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("line length is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    // pll_table->pixclk = 81000000;
    // frame_time = GD_VIDEO_FPS_29_97
    frame_time_pclk = frame_time * (U64)pll_table->pixclk;

    // frame_time_pclk = (frame_time_pclk + line_length/2) / line_length;
    //DO_DIV_ROUND(frame_time_pclk, line_length);
    //DO_DIV_ROUND(frame_time_pclk, 512000000);
    frame_time_pclk = (frame_time_pclk + line_length/2) / line_length;
    frame_time_pclk = (frame_time_pclk + 512000000/2) / 512000000;
    // frame_time_pclk = 0x45d

#ifdef SENSOR_DEBUG
    GM_Printf("frame_time %d, line_length 0x%x, vertical_lines 0x%llx\n", frame_time, line_length, frame_time_pclk);
#endif

    vertical_lines = frame_time_pclk;
    // GD_VIDEO_FPS_AUTO == 0x045D
    errCode |= ov2710_write_reg(pHandle, OV2710_TIMING_CONTROL_VTS_HIGHBYTE, (U8)((vertical_lines & 0x00FF00) >>8));
    errCode |= ov2710_write_reg(pHandle, OV2710_TIMING_CONTROL_VTS_LOWBYTE, (U8)(vertical_lines & 0x0000FF));

#ifdef SENSOR_DEBUG
    GM_Printf("set fps change line_length %d, vertical_lines %d, fps = %d \n", line_length, vertical_lines, fps);
#endif
    // pinfo->current_shutter_time = 0
    ov2710_set_shutter_time(pHandle, pinfo->current_shutter_time);
    pinfo->frame_rate = fps;

    //set vblank time
    // LindengYu
    //vin_irq_fix.mode = GD_VIN_VSYNC_IRQ_IDSP;
    //vin_irq_fix.delay = 0;
    //errCode |= amba_vin_adapter_cmd(pHandle->adapid,
    //    GD_VIN_ADAP_FIX_ARCH_VSYNC, &vin_irq_fix);
    return errCode;
}

static GERR ov2710_set_video_index(GD_HANDLE* pHandle, U32 index)
{
    GERR errCode = GD_OK;
    U32 format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    if (index >= OV2710_VIDEO_INFO_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("ov2710_set_video_index do not support mode %d!\n", index);
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    // LindengYu
    //errCode |= ov2710_pre_set_vin_mode(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;
    pinfo->current_video_index = index;
    format_index            = ov2710_video_info_table[index].format_index;

    pinfo->cap_start_x      = ov2710_video_info_table[index].def_start_x;
    pinfo->cap_start_y      = ov2710_video_info_table[index].def_start_y;
    pinfo->cap_cap_w        = ov2710_video_info_table[index].def_width;
    pinfo->cap_cap_h        = ov2710_video_info_table[index].def_height;
    pinfo->bayer_pattern    = ov2710_video_info_table[index].bayer_pattern;
    //set the specified PLL index for each sensor_mode.
    pinfo->pll_index        = ov2710_video_format_tbl.table[format_index].pll_index;
    // LindengYu
    //ov2710_print_info(pHandle);

    //set clk_si
    // LindengYu
    //errCode |= ov2710_init_vin_clock(pHandle, &ov2710_pll_tbl[pinfo->pll_index]);

    ov2710_fill_share_regs(pHandle);
    ov2710_fill_pll_regs(pHandle);
    ov2710_fill_video_format_regs(pHandle);
    ov2710_set_fps(pHandle, GD_VIDEO_FPS_AUTO);

    ov2710_set_shutter_time(pHandle, GD_VIDEO_FPS_60);
    ov2710_set_agc_db(pHandle, 0);
    ov2710_set_streaming(pHandle);    //start streaming

    // LindengYu
    //errCode |= ov2710_set_vin_mode(pHandle);

    // LindengYu
    //errCode |= ov2710_post_set_vin_mode(pHandle);

    if (!errCode)
        pinfo->mode_type = GD_VIN_SRC_ENABLED_FOR_VIDEO;

    return errCode;
}

static GERR ov2710_set_video_mode(GD_HANDLE* pHandle, GD_VIDEO_MODE_E mode)
{
    GERR errCode = GD_OK;
    int i;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    // LindengYu
    //errCode = ov2710_init_vin_clock(pHandle, &ov2710_pll_tbl[0]);
    //if (errCode != GD_OK)
    //    return errCode;
    GD_SENSOR_Sleep(10);
    ov2710_reset(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;

    for (i = 0; i < OV2710_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (ov2710_video_mode_table[i].mode == mode)
        {
            errCode = ov2710_set_video_index(pHandle, ov2710_video_mode_table[i].preview_index);
            pinfo->mode_index = i;
            break;
        }
    }
    if (i >= OV2710_VIDEO_MODE_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("ov2710_set_video_mode do not support %d, %d!\n", mode, i);
#endif
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
    }

    if (errCode == GD_OK)
    {
        pinfo->current_vin_mode = ov2710_video_mode_table[i].mode;
        pinfo->mode_type        = ov2710_video_mode_table[i].preview_mode_type;
    }
    return errCode;
}

static GERR ov2710_init_hw(GD_HANDLE* pHandle)
{
    GERR    errCode = GD_OK;
    U16     sen_id  = 0;

    // LindengYu
    //errCode = ov2710_init_vin_clock(pHandle, &ov2710_pll_tbl[0]);
    //if (errCode != GD_OK)
    //    return errCode;
    GD_SENSOR_Sleep(10);
    ov2710_reset(pHandle);

    errCode = ov2710_query_sensor_id(pHandle, &sen_id);
    if (errCode == GD_OK)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("OV2710 sensor ID is 0x%x\n", sen_id);
#endif
    }
    return errCode;
}


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR ov2710_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    GERR errCode = GD_OK;
    GERR gerr;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }
    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if (device == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("\t\t---->cmd is %d\n", cmd);
#endif
    switch (cmd)
    {
    case GD_VIN_SRC_RESET:
        errCode = ov2710_reset(pHandle);
        break;

    case GD_VIN_SRC_SET_POWER:
        errCode = GD_GPIO_Write(device->powerGPIO, (U8)((U32)args));
        break;

    case GD_VIN_SRC_SUSPEND:
        gerr = GD_GPIO_Write(device->resetGPIO, 1);
        if(gerr != GD_OK)
        {
            return gerr;
        }
        errCode = GD_GPIO_Write(device->powerGPIO, 0);
        break;

    case GD_VIN_SRC_RESUME:
        errCode = ov2710_init_hw(pHandle);
        break;

#if 0
    case GD_VIN_SRC_GET_INFO:
        {
            amba_vin_source_info *pub_src;

            pub_src                     = (amba_vin_source_info *) args;
            pub_src->id                 = pHandle->id;
            pub_src->adapter_id         = adapter_id;
            pub_src->dev_type           = pHandle->dev_type;
            strlcpy(pub_src->name, pHandle->name, sizeof (pub_src->name));
            pub_src->sensor_id          = SENSOR_OV2710;
            pub_src->default_mode       = OV2710_VIDEO_MODE_TABLE_AUTO;
            pub_src->total_channel_num  = pHandle->total_channel_num;
            pub_src->active_channel_id  = pHandle->active_channel_id;
            pub_src->source_type.decoder = GD_VIN_CMOS_CHANNEL_TYPE_AUTO;
        }
        break;

    case GD_VIN_SRC_CHECK_VIDEO_MODE:
        errCode = ov2710_check_video_mode(pHandle, (amba_vin_source_mode_info *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_INFO:
        errCode = ov2710_get_video_info(pHandle, (GD_SENSOR_VIDEO_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_AGC_INFO:
        errCode = ov2710_get_agc_info(pHandle, (GD_SENSOR_AGC_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_INFO:
        errCode = ov2710_get_shutter_info(pHandle, (GD_SENSOR_SHUTTER_INFO_S *) args);
        break;
#if 0

    case GD_VIN_SRC_GET_CAPABILITY:
        errCode = ov2710_get_capability(pHandle, (amba_vin_src_capability *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_MODE:
        errCode = ov2710_get_video_mode(pHandle, (GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_SET_VIDEO_MODE:
        errCode = ov2710_set_video_mode(pHandle, *(GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_GET_STILL_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_STILL_MODE:
        errCode = ov2710_set_still_mode(pHandle, (gd_vin_src_still_info_s *) args);
        break;

#if 0
    case GD_VIN_SRC_GET_BLC:
        errCode = amba_vin_adapter_cmd(pHandle->adapid, GD_VIN_ADAP_GET_SW_BLC, (void *) args);
        memcpy(&(pinfo->current_sw_blc), (void *) args, sizeof (pinfo->current_sw_blc));
        break;

    case GD_VIN_SRC_SET_BLC:
        memcpy(&(pinfo->current_sw_blc), (void *) args, sizeof (pinfo->current_sw_blc));
        errCode = amba_vin_adapter_cmd(pHandle->adapid, GD_VIN_ADAP_SET_SW_BLC, (void *) args);
        break;
#endif
    case GD_VIN_SRC_GET_FRAME_RATE:
        *(U32 *)args = pinfo->frame_rate;
        break;

    case GD_VIN_SRC_SET_FRAME_RATE:
        errCode = ov2710_set_fps(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_TIME:
        *(U32 *)args = pinfo->current_shutter_time;
        break;

    case GD_VIN_SRC_SET_SHUTTER_TIME:
        errCode = ov2710_set_shutter_time(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_GAIN_DB:
        *(S32 *)args = pinfo->current_gain_db;
        break;

    case GD_VIN_SRC_SET_GAIN_DB:
        errCode = ov2710_set_agc_db(pHandle, *(S32 *) args);
        break;

    case GD_VIN_SRC_GET_LOW_LIGHT_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_LOW_LIGHT_MODE:
        errCode = ov2710_set_low_light_agc(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_SET_MIRROR_MODE:
        errCode = ov2710_set_mirror_mode(pHandle, (GD_SENSOR_MIRROR_MODE_S *) args);
        break;

    case GD_VIN_SRC_SET_ANTI_FLICKER:
        errCode = ov2710_set_anti_flicker(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_TEST_DUMP_REG:
        ov2710_dump_reg(pHandle);
        break;

    case GD_VIN_SRC_TEST_GET_DEV_ID:
        {
            U16 sen_id  = 0;
            U16 sen_ver = 0;
            U32 *pdata  = (U32 *) args;

            errCode = ov2710_query_sensor_id(pHandle, &sen_id);
            if (errCode == GD_OK)
            {
                *pdata = (sen_id << 16) | sen_ver;
            }
        }
        break;

    case GD_VIN_SRC_TEST_GET_REG_DATA:
        {
            GD_SENSOR_REG_DATA_S *reg_data;
            U16 subaddr;
            U8 data;

            reg_data    = (GD_SENSOR_REG_DATA_S*) args;
            subaddr     = reg_data->reg;

            errCode     = ov2710_read_reg(pHandle, subaddr, &data);

            reg_data->data = data;
        }
        break;

    case GD_VIN_SRC_TEST_SET_REG_DATA:
        {
            GD_SENSOR_REG_DATA_S *reg_data;
            U16 subaddr;
            U8 data;

            reg_data    = (GD_SENSOR_REG_DATA_S *) args;
            subaddr     = reg_data->reg;
            data        = reg_data->data;

            errCode     = ov2710_write_reg(pHandle, subaddr, data);
        }
        break;

    case GD_VIN_SRC_SET_TRIGGER_MODE:
        break;

    case GD_VIN_SRC_SET_CAPTURE_MODE:
        break;

    default:
#ifdef SENSOR_DEBUG
        GM_Printf("%s-%d do not support cmd %d!\n", device->name, device->i2cAddrSensor, cmd);
#endif
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;
    }

    return errCode;
}

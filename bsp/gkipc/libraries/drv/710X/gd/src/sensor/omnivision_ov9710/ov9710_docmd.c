/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/omnivision_ov9710/ov9710_docmd.c
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
#include "ov9710_pri.h"
#include "gd_gpio.h"
#include "gd_i2c.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define OV9710_DEFAULT_VIDEO_INDEX      (0)
#define OV9710_VIDEO_MODE_TABLE_AUTO    GD_VIDEO_MODE_720P

#define OV9710_SHARE_REG_SIZE           (sizeof(ov9710_share_regs)/sizeof(ov9710_reg_table))
#define OV9710_VIDEO_INFO_TABLE_SIZE    (sizeof(ov9710_video_info_table)/sizeof(ov9710_video_info))
#define OV9710_VIDEO_MODE_TABLE_SIZE    (sizeof(ov9710_video_mode_table)/sizeof(gd_video_mode_s))
//#define OV9710_STILL_MODE_TABLE_SIZE    (sizeof(ov9710_still_mode_table)/sizeof(gd_video_mode_s))

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

static ov9710_reg_table ov9710_share_regs[] =
{
    {OV9710_COM7,           0x80},
    {OV9710_COM11,          0x07},
    {OV9710_REG5F,          0x18},
    {OV9710_REG69,          0x04},
    {OV9710_REG65,          0x2a},
    {OV9710_REG68,          0x0a},
    {OV9710_REG39,          0x28},
    {OV9710_RSVD4D,         0x90},
    {OV9710_YAVG_CTRL_4,    0x80},

    {OV9710_DSP_CTRL_0,     0x01},        //karst
    {OV9710_WBC_CTRL_0,     0x68},
    //{OV9710_COM7,           0x00},
    //{OV9710_REG3B,          0x00},
    {OV9710_DSP_CTRL_1,     0x80},
    {OV9710_COM24,          0x02},
    {OV9710_COM25,          0x10},
    {OV9710_REG4E,          0x55},
    {OV9710_REG4F,          0x55},
    {OV9710_REG50,          0x55},
    {OV9710_REG51,          0x55},
    {OV9710_WPT,            0x55},
    {OV9710_BPT,            0x40},
    {OV9710_VPT,            0xa1},

    {OV9710_REG5C,          0x59},
    {OV9710_REG5D,          0x00},
    {OV9710_CLK,            0x01},

    {OV9710_COM8,           0x80},
    {OV9710_COM9,           0x60},
    {OV9710_DVP_CTRL_00,    0x41},

    {OV9710_DVP_CTRL_09,    0x32},
    //{OV9710_DVP_CTRL_09,    0xb6},               // consistent with DV code
    {OV9710_DVP_CTRL_01,    0x21},
    {OV9710_REG41,          0x80},
    {OV9710_REG6D,          0x02},    // added for FPN optimum

};

static ov9710_pll_reg_table ov9710_pll_tbl[] =
{
    //[0] =
    {//for 29.97fps
        41962436,//.pixclk = 41962436,
        23978535,//.extclk = 23978535,
        //.regs =
        {
            {OV9710_REG5C, 0x59},
            {OV9710_REG5D, 0x00},
            {OV9710_CLK,   0x00},
        }
    },
    //[1] =
    {//for 59.94fps(640x400)
        41887990,//.pixclk = 41887990,
        23935994,//.extclk = 23935994,
        //.regs =
        {
            {OV9710_REG5C, 0x59},
            {OV9710_REG5D, 0x00},
            {OV9710_CLK,   0x00},
        }
    },
    //[2] =
    {//for 30fps
        42004440,//.pixclk = 42004440,
        24002537,//.extclk = 24002537,
        //.regs =
        {
            {OV9710_REG5C, 0x59},
            {OV9710_REG5D, 0x00},
            {OV9710_CLK,   0x00},
        }
    },
    //[3] =
    {//for 60fps(640x400)
        41929920,//.pixclk = 41929920,
        23959954,//.extclk = 23959954,
        //.regs =
        {
            {OV9710_REG5C, 0x59},
            {OV9710_REG5D, 0x00},
            {OV9710_CLK,   0x00},
        }
    },
};

static ov9710_video_info ov9710_video_info_table[] =
{
    //[0] =
    {
       0,//.format_index= 0,
       0,//.def_start_x    = 0,
       40,//.def_start_y    = 40,
       1280,//.def_width    = 1280,
       720,//.def_height    = 720,
       (0 + 5),//.sync_start    = (0 + 5),
       GD_VIN_SRC_BAYER_PATTERN_BG,//.bayer_pattern    = GD_VIN_SRC_BAYER_PATTERN_BG,
    },

    //[1] =
    {
       1,//.format_index= 1,
       0,//.def_start_x    = 0,
       0,//.def_start_y    = 0,
       640,//.def_width    = 640,
       400,//.def_height    = 400,
       (0 + 5),//.sync_start    = (0 + 5),
       GD_VIN_SRC_BAYER_PATTERN_BG,//.bayer_pattern    = GD_VIN_SRC_BAYER_PATTERN_BG,
    },

    //[2] =
    {
        0,//.format_index    = 0,
        128,//.def_start_x    = 128,
        16,//.def_start_y    = 16,
        1024,//.def_width    = 1024,
        768,//.def_height    = 768,
        (0 + 5),//.sync_start    = (0 + 5),
        GD_VIN_SRC_BAYER_PATTERN_BG,//.bayer_pattern    = GD_VIN_SRC_BAYER_PATTERN_BG,
    },

    //[3] =
    {
        0,//.format_index    = 0,
        0,//.def_start_x    = 0,
        0,//.def_start_y    = 0,
        1280,//.def_width    = 1280,
        800,//.def_height    = 800,
        (0 + 5),//.sync_start    = (0 + 5),
        GD_VIN_SRC_BAYER_PATTERN_BG,//.bayer_pattern    = GD_VIN_SRC_BAYER_PATTERN_BG,
    },
};

static gd_video_mode_s ov9710_video_mode_table[] =
{
    {
        GD_VIDEO_MODE_AUTO,
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
        },

    {
        GD_VIDEO_MODE_720P,
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        0,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },

    {
        GD_VIDEO_MODE_640_400,
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },

    {
        GD_VIDEO_MODE_XGA,
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },

    {
        GD_VIDEO_MODE_WXGA,
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
};

/* ========================================================================== */
static ov9710_video_format_reg_table ov9710_video_format_tbl =
{
    //.reg =
    {
        OV9710_HSTART,
        OV9710_AHSIZE,
        OV9710_VSTART,
        OV9710_AVSIZE,
        OV9710_REG03,
        OV9710_REG32,
        OV9710_DSP_CTRL_2,
        OV9710_DSP_CTRL_3,
        OV9710_DSP_CTRL_4,
        OV9710_REG57,
        OV9710_REG58,
        OV9710_REG59,
        OV9710_RSVD4C,
        OV9710_RSVD4B,
        OV9710_RENDL,
        OV9710_RENDH,
        OV9710_YAVG_CTRL_0,
        OV9710_YAVG_CTRL_1,
        OV9710_COM7,
        OV9710_REG3B,
        OV9710_REG2A,
        OV9710_REG2B,
    },
    {
        //.table[0] =
        {        //1280x800
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x25,    //OV9710_HSTART,
                0xA2,    //OV9710_AHSIZE,
                0x01,    //OV9710_VSTART,
                0xCA,    //OV9710_AVSIZE,
                0x0A,    //OV9710_REG03,
                0x07,    //OV9710_REG32,
                0x00,    //OV9710_DSP_CTRL_2,
                0x00,    //OV9710_DSP_CTRL_3,
                0x00,    //OV9710_DSP_CTRL_4,
                0x00,    //OV9710_REG57,
                0xC8,    //OV9710_REG58,
                0xA0,    //OV9710_REG59,
                0x13,    //OV9710_RSVD4C,
                0x36,    //OV9710_RSVD4B,
                0x3C,    //OV9710_RENDL,
                0x03,    //OV9710_RENDH,
                0xA0,    //OV9710_YAVG_CTRL_0,
                0xC8,    //OV9710_YAVG_CTRL_1,
                0x00,    //OV9710_COM7
                0x00,    //OV9710_REG3B
                0x9B,   //OV9710_REG2A
                0x06,   //OV9710_REG2B
            },
            NULL,//.fps_table = NULL,
            1280,//.width = 1280,
            800,//.height = 800,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            2,//.pll_index    = 2,
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_30,
        },
        //.table[1] =
        {        //VGA
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x25,    //OV9710_HSTART,
                0xA2,    //OV9710_AHSIZE,
                0x01,    //OV9710_VSTART,
                0x64,    //OV9710_AVSIZE,
                0x02,    //OV9710_REG03,
                0x07,    //OV9710_REG32,
                0x00,    //OV9710_DSP_CTRL_2,
                0x00,    //OV9710_DSP_CTRL_3,
                0x00,    //OV9710_DSP_CTRL_4,
                0x00,    //OV9710_REG57,
                0x64,    //OV9710_REG58,
                0x50,    //OV9710_REG59,
                0x09,    //OV9710_RSVD4C,
                0x9A,    //OV9710_RSVD4B,
                0x9E,    //OV9710_RENDL,
                0x01,    //OV9710_RENDH,
                0x50,    //OV9710_YAVG_CTRL_0,
                0x64,    //OV9710_YAVG_CTRL_1,
                0x40,    //OV9710_COM7
                0x01,    //OV9710_REG3B
                0x98,   //OV9710_REG2A
                0x06,   //OV9710_REG2B
            },
            NULL,//.fps_table = NULL,
            640,//.width = 640,
            400,//.height = 400,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_10,//.bits = GD_VIDEO_BITS_10,
            GD_VIDEO_RATIO_4_3,//.ratio = GD_VIDEO_RATIO_4_3,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            3,//.pll_index    = 3,
            GD_VIDEO_FPS_60,//.max_fps = GD_VIDEO_FPS_60,
        },
    },
};

#ifdef USE_32_STEP_GAIN_TABLE
/* This is 32-step gain table, OV9710_GAIN_ROWS = 162, OV9710_GAIN_COLS = 3 */
const S16 OV9710_GAIN_TABLE[OV9710_GAIN_ROWS][OV9710_GAIN_COLS] =
{
    /* gain_value*256,  log2(gain)*1000,  register */
    /* error */
    {0x8000, 7000, 0x397f},    /* index 0   -0.002121     : 42dB */
    {0x7d41, 6968, 0x387f},    /* index 1   0.051357      */
    {0x7a92, 6937, 0x367f},    /* index 2   -0.036266     */
    {0x77f2, 6906, 0x357f},    /* index 3   0.010639      */
    {0x7560, 6875, 0x347f},    /* index 4   0.055210      */
    {0x72dc, 6843, 0x327f},    /* index 5   -0.051109     */
    {0x7066, 6812, 0x317f},    /* index 6   -0.014027     */
    {0x6dfd, 6781, 0x307f},    /* index 7   0.020378      */
    {0x6ba2, 6750, 0x2f7f},    /* index 8   0.052017      */
    {0x6954, 6718, 0x2e7f},    /* index 9   0.080780      */
    {0x6712, 6687, 0x2c7f},    /* index 10  -0.058884     */
    {0x64dc, 6656, 0x2b7f},    /* index 11  -0.039406     */
    {0x62b3, 6625, 0x2a7f},    /* index 12  -0.023262     */
    {0x6096, 6593, 0x297f},    /* index 13  -0.010597     */
    {0x5e84, 6562, 0x287f},    /* index 14  -0.001549     */
    {0x5c7d, 6531, 0x277f},    /* index 15  0.003723      */
    {0x5a82, 6500, 0x267f},    /* index 16  0.005066      */
    {0x5891, 6468, 0x257f},    /* index 17  0.002308      */
    {0x56ac, 6437, 0x247f},    /* index 18  -0.004745     */
    {0x54d0, 6406, 0x237f},    /* index 19  -0.016289     */
    {0x52ff, 6375, 0x227f},    /* index 20  -0.032528     */
    {0x5138, 6343, 0x217f},    /* index 21  -0.053692     */
    {0x4f7a, 6312, 0x207f},    /* index 22  -0.080025     */
    {0x4dc6, 6281, 0x207f},    /* index 23  0.108116      */
    {0x4c1b, 6250, 0x1f7f},    /* index 24  0.076355      */
    {0x4a7a, 6218, 0x1e7f},    /* index 25  0.038879      */
    {0x48e1, 6187, 0x1d7f},    /* index 26  -0.004616     */
    {0x4752, 6156, 0x1c7f},    /* index 27  -0.054459     */
    {0x45ca, 6125, 0x1b7f},    /* index 28  -0.111004     */
    {0x444c, 6093, 0x1b7f},    /* index 29  0.077141      */
    {0x42d5, 6062, 0x1a7f},    /* index 30  0.013504      */
    {0x4166, 6031, 0x197f},    /* index 31  -0.057655     */
    {0x4000, 6000, 0x197f},    /* index 32  0.130489     : 36dB */
    {0x3ea0, 5968, 0x187f},    /* index 33  0.051353      */
    {0x3d49, 5937, 0x177f},    /* index 34  -0.036266     */
    {0x3bf9, 5906, 0x167f},    /* index 35  -0.132935     */
    {0x3ab0, 5875, 0x167f},    /* index 36  0.055210      */
    {0x396e, 5843, 0x157f},    /* index 37  -0.051109     */
    {0x3833, 5812, 0x157f},    /* index 38  0.137035      */
    {0x36fe, 5781, 0x147f},    /* index 39  0.020378      */
    {0x35d1, 5750, 0x137f},    /* index 40  -0.107365     */
    {0x34aa, 5718, 0x137f},    /* index 41  0.080780      */
    {0x3389, 5687, 0x127f},    /* index 42  -0.058884     */
    {0x326e, 5656, 0x127f},    /* index 43  0.129257      */
    {0x3159, 5625, 0x117f},    /* index 44  -0.023266     */
    {0x304b, 5593, 0x117f},    /* index 45  0.164879      */
    {0x2f42, 5562, 0x107f},    /* index 46  -0.001549     */
    {0x2e3e, 5531, 0x0f7f},    /* index 47  -0.183079     */
    {0x2d41, 5500, 0x0f7f},    /* index 48  0.005066      */
    {0x2c48, 5468, 0x0e7f},    /* index 49  -0.192890     */
    {0x2b56, 5437, 0x0e7f},    /* index 50  -0.004745     */
    {0x2a68, 5406, 0x0e7f},    /* index 51  0.183395      */
    {0x297f, 5375, 0x0d7f},    /* index 52  -0.032528     */
    {0x289c, 5343, 0x0d7f},    /* index 53  0.155617      */
    {0x27bd, 5312, 0x0c7f},    /* index 54  -0.080027     */
    {0x26e3, 5281, 0x0c7f},    /* index 55  0.108118      */
    {0x260d, 5250, 0x0b7f},    /* index 56  -0.149267     */
    {0x253d, 5218, 0x0b7f},    /* index 57  0.038877      */
    {0x2470, 5187, 0x0b7f},    /* index 58  0.227022      */
    {0x23a9, 5156, 0x0a7f},    /* index 59  -0.054457     */
    {0x22e5, 5125, 0x0a7f},    /* index 60  0.133688      */
    {0x2226, 5093, 0x097f},    /* index 61  -0.174641     */
    {0x216a, 5062, 0x097f},    /* index 62  0.013504      */
    {0x20b3, 5031, 0x097f},    /* index 63  0.201647      */
    {0x2000, 5000, 0x087f},    /* index 64  -0.136789    : 30dB */
    {0x1f50, 4968, 0x087f},    /* index 65  0.051353      */
    {0x1ea4, 4937, 0x087f},    /* index 66  0.239498      */
    {0x1dfc, 4906, 0x077f},    /* index 67  -0.132933     */
    {0x1d58, 4875, 0x077f},    /* index 68  0.055212      */
    {0x1cb7, 4843, 0x077f},    /* index 69  0.243355      */
    {0x1c19, 4812, 0x067f},    /* index 70  -0.167765     */
    {0x1b7f, 4781, 0x067f},    /* index 71  0.020378      */
    {0x1ae8, 4750, 0x067f},    /* index 72  0.208523      */
    {0x1a55, 4718, 0x057f},    /* index 73  -0.247028     */
    {0x19c4, 4687, 0x057f},    /* index 74  -0.058884     */
    {0x1937, 4656, 0x057f},    /* index 75  0.129259      */
    {0x18ac, 4625, 0x057f},    /* index 76  0.317404      */
    {0x1825, 4593, 0x047f},    /* index 77  -0.189695     */
    {0x17a1, 4562, 0x047f},    /* index 78  -0.001551     */
    {0x171f, 4531, 0x047f},    /* index 79  0.186592      */
    {0x16a0, 4500, 0x047f},    /* index 80  0.374737      */
    {0x1624, 4468, 0x037f},    /* index 81  -0.192892     */
    {0x15ab, 4437, 0x037f},    /* index 82  -0.004747     */
    {0x1534, 4406, 0x037f},    /* index 83  0.183395      */
    {0x14bf, 4375, 0x037f},    /* index 84  0.371540      */
    {0x144e, 4343, 0x027f},    /* index 85  -0.268171     */
    {0x13de, 4312, 0x027f},    /* index 86  -0.080027     */
    {0x1371, 4281, 0x027f},    /* index 87  0.108116      */
    {0x1306, 4250, 0x027f},    /* index 88  0.296261      */
    {0x129e, 4218, 0x017f},    /* index 89  -0.430746     */
    {0x1238, 4187, 0x017f},    /* index 90  -0.242601     */
    {0x11d4, 4156, 0x017f},    /* index 91  -0.054459     */
    {0x1172, 4125, 0x017f},    /* index 92  0.133686      */
    {0x1113, 4093, 0x017f},    /* index 93  0.321829      */
    {0x10b5, 4062, 0x017f},    /* index 94  0.509974      */
    {0x1059, 4031, 0x007f},    /* index 95  -0.324934     */
    {0x1000, 4000, 0x0860},    /* index 96  0.000000     : 24dB */
    {0x0fa8, 3968, 0x007f},    /* index 97  0.051353      */
    {0x0f52, 3937, 0x007d},    /* index 98  -0.040716     */
    {0x0efe, 3906, 0x007c},    /* index 99  0.003855      */
    {0x0eac, 3875, 0x007b},    /* index 100 0.046015      */
    {0x0e5b, 3843, 0x0079},    /* index 101 -0.065386     */
    {0x0e0c, 3812, 0x0078},    /* index 102 -0.030977     */
    {0x0dbf, 3781, 0x0077},    /* index 103 0.000660      */
    {0x0d74, 3750, 0x0076},    /* index 104 0.029425      */
    {0x0d2a, 3718, 0x0075},    /* index 105 0.055210      */
    {0x0ce2, 3687, 0x0074},    /* index 106 0.077904      */
    {0x0c9b, 3656, 0x0072},    /* index 107 -0.074619     */
    {0x0c56, 3625, 0x0071},    /* index 108 -0.061953     */
    {0x0c12, 3593, 0x0070},    /* index 109 -0.052906     */
    {0x0bd0, 3562, 0x006f},    /* index 110 -0.047630     */
    {0x0b8f, 3531, 0x006e},    /* index 111 -0.046288     */
    {0x0b50, 3500, 0x006d},    /* index 112 -0.049049     */
    {0x0b12, 3468, 0x006c},    /* index 113 -0.056101     */
    {0x0ad5, 3437, 0x006b},    /* index 114 -0.067642     */
    {0x0a9a, 3406, 0x006a},    /* index 115 -0.083881     */
    {0x0a5f, 3375, 0x006a},    /* index 116 0.104261      */
    {0x0a27, 3343, 0x0069},    /* index 117 0.083097      */
    {0x09ef, 3312, 0x0068},    /* index 118 0.056763      */
    {0x09b8, 3281, 0x0067},    /* index 119 0.025000      */
    {0x0983, 3250, 0x0066},    /* index 120 -0.012478     */
    {0x094f, 3218, 0x0065},    /* index 121 -0.055971     */
    {0x091c, 3187, 0x0064},    /* index 122 -0.105812     */
    {0x08ea, 3156, 0x0064},    /* index 123 0.082333      */
    {0x08b9, 3125, 0x0063},    /* index 124 0.025785      */
    {0x0889, 3093, 0x0062},    /* index 125 -0.037851     */
    {0x085a, 3062, 0x0061},    /* index 126 -0.109009     */
    {0x082c, 3031, 0x0061},    /* index 127 0.079136      */
    {0x0800, 3000, 0x0060},    /* index 128 0.000000      : 18dB */
    {0x07d4, 2968, 0x003f},    /* index 129 0.051355      */
    {0x07a9, 2937, 0x003d},    /* index 130 -0.040716     */
    {0x077f, 2906, 0x003c},    /* index 131 0.003857      */
    {0x0756, 2875, 0x003b},    /* index 132 0.046015      */
    {0x072d, 2843, 0x0039},    /* index 133 -0.065384     */
    {0x0706, 2812, 0x0038},    /* index 134 -0.030977     */
    {0x06df, 2781, 0x0037},    /* index 135 0.000662      */
    {0x06ba, 2750, 0x0036},    /* index 136 0.029425      */
    {0x0695, 2718, 0x0035},    /* index 137 0.055212      */
    {0x0671, 2687, 0x0034},    /* index 138 0.077904      */
    {0x064d, 2656, 0x0032},    /* index 139 -0.074618     */
    {0x062b, 2625, 0x0031},    /* index 140 -0.061954     */
    {0x0609, 2593, 0x0030},    /* index 141 -0.052905     */
    {0x05e8, 2562, 0x002f},    /* index 142 -0.047629     */
    {0x05c7, 2531, 0x002e},    /* index 143 -0.046287     */
    {0x05a8, 2500, 0x002d},    /* index 144 -0.049048     */
    {0x0589, 2468, 0x002c},    /* index 145 -0.056102     */
    {0x056a, 2437, 0x002b},    /* index 146 -0.067642     */
    {0x054d, 2406, 0x002a},    /* index 147 -0.083882     */
    {0x052f, 2375, 0x002a},    /* index 148 0.104261      */
    {0x0513, 2343, 0x0029},    /* index 149 0.083097      */
    {0x04f7, 2312, 0x0028},    /* index 150 0.056763      */
    {0x04dc, 2281, 0x0027},    /* index 151 0.025000      */
    {0x04c1, 2250, 0x0026},    /* index 152 -0.012477     */
    {0x04a7, 2218, 0x0025},    /* index 153 -0.055971     */
    {0x048e, 2187, 0x0024},    /* index 154 -0.105812     */
    {0x0475, 2156, 0x0024},    /* index 155 0.082332      */
    {0x045c, 2125, 0x0023},    /* index 156 0.025786      */
    {0x0444, 2093, 0x0022},    /* index 157 -0.037852     */
    {0x042d, 2062, 0x0021},    /* index 158 -0.109008     */
    {0x0416, 2031, 0x0021},    /* index 159 0.079136      */
    {0x0400, 2000, 0x0020},    /* index 160 0.000000     : 12dB */
    {0x03ea, 1968, 0x0219},    /* index 161 -0.017856     */
    {0x03d4, 1937, 0x0513},    /* index 162 0.065427      */
    {0x03bf, 1906, 0x001e},    /* index 163 0.003857      */
    {0x03ab, 1875, 0x011a},    /* index 164 -0.027907     */
    {0x0396, 1843, 0x0217},    /* index 165 0.010476      */
    {0x0383, 1812, 0x0119},    /* index 166 0.007713      */
    {0x036f, 1781, 0x0216},    /* index 167 0.000660      */
    {0x035d, 1750, 0x001b},    /* index 168 0.029426      */
    {0x034a, 1718, 0x0215},    /* index 169 -0.027120     */
    {0x0338, 1687, 0x0117},    /* index 170 0.036045      */
    {0x0326, 1656, 0x0019},    /* index 171 -0.074618     */
    {0x0315, 1625, 0x0116},    /* index 172 0.026229      */
    {0x0304, 1593, 0x0018},    /* index 173 -0.052906     */
    {0x02f4, 1562, 0x0115},    /* index 174 -0.001551     */
    {0x02e3, 1531, 0x0017},    /* index 175 -0.046287     */
    {0x02d4, 1500, 0x050e},    /* index 176 0.046928      */
    {0x02c4, 1468, 0x0016},    /* index 177 -0.056103     */
    {0x02b5, 1437, 0x0113},    /* index 178 -0.118290     */
    {0x02a6, 1406, 0x0945},    /* index 179 0.018909      */
    {0x0297, 1375, 0x030f},    /* index 180 -0.052246     */
    {0x0289, 1343, 0x0112},    /* index 181 -0.023480     */
    {0x027b, 1312, 0x0845},    /* index 182 0.056762      */
    {0x026e, 1281, 0x040d},    /* index 183 0.024999      */
    {0x0260, 1250, 0x0013},    /* index 184 -0.012477     */
    {0x0253, 1218, 0x0745},    /* index 185 0.060619      */
    {0x0247, 1187, 0x0d07},    /* index 186 0.073286      */
    {0x023a, 1156, 0x030d},    /* index 187 0.021802      */
    {0x022e, 1125, 0x0247},    /* index 188 0.025786      */
    {0x0222, 1093, 0x0011},    /* index 189 -0.037852     */
    {0x0216, 1062, 0x0b07},    /* index 190 -0.043454     */
    {0x020b, 1031, 0x020d},    /* index 191 -0.053476     */
    {0x0200, 1000, 0x0010},    /* index 192 0.000000      : 6dB */
    {0x01f5,  968, 0x0a07},    /* index 193 0.051355      */
    {0x01ea,  937, 0x030b},    /* index 194 -0.112205     */
    {0x01df,  906, 0x0445},    /* index 195 0.003856      */
    {0x01d5,  875, 0x010d},    /* index 196 -0.027907     */
    {0x01cb,  843, 0x0f05},    /* index 197 0.010476      */
    {0x01c1,  812, 0x000e},    /* index 198 -0.030976     */
    {0x01b7,  781, 0x0e05},    /* index 199 0.000660      */
    {0x01ae,  750, 0x0a06},    /* index 200 0.029425      */
    {0x01a5,  718, 0x0d05},    /* index 201 -0.027120     */
    {0x019c,  687, 0x000d},    /* index 202 0.077905      */
    {0x0193,  656, 0x020a},    /* index 203 -0.074618     */
    {0x018a,  625, 0x010b},    /* index 204 0.026230      */
    {0x0182,  593, 0x000c},    /* index 205 -0.052906     */
    {0x017a,  562, 0x0b05},    /* index 206 0.044285      */
    {0x0171,  531, 0x0f04},    /* index 207 -0.046286     */
    {0x016a,  500, 0x0507},    /* index 208 0.046928      */
    {0x0162,  468, 0x000b},    /* index 209 -0.056102     */
    {0x015a,  437, 0x0e04},    /* index 210 0.132041      */
    {0x0153,  406, 0x0905},    /* index 211 0.018910      */
    {0x014b,  375, 0x0407},    /* index 212 0.104261      */
    {0x0144,  343, 0x0109},    /* index 213 -0.023480     */
    {0x013d,  312, 0x0805},    /* index 214 0.056763      */
    {0x0137,  281, 0x0506},    /* index 215 0.024999      */
    {0x0130,  250, 0x0b04},    /* index 216 -0.012478     */
    {0x0129,  218, 0x0705},    /* index 217 0.060619      */
    {0x0123,  187, 0x0009},    /* index 218 -0.105812     */
    {0x011d,  156, 0x0406},    /* index 219 0.082332      */
    {0x0117,  125, 0x0207},    /* index 220 0.025786      */
    {0x0111,   93, 0x0904},    /* index 221 -0.037852     */
    {0x010b,   62, 0x0306},    /* index 222 -0.109008     */
    {0x0105,   31, 0x0505},    /* index 223 -0.053476     */
    {0x0100,    0, 0x0008},    /* index 224 0.000000      : 0dB */
    {0x00fa,  -31, 0x0107},    /* index 225  0.051355    */
    {0x00f5,  -62, 0x0206},    /* index 226  -0.184287   */
    {0x00ef,  -93, 0x0405},    /* index 227  0.003856    */
    {0x00ea, -125, 0x0405},    /* index 228  0.192000    */
    {0x00e5, -156, 0x0604},    /* index 229  -0.219120   */
    {0x00e0, -187, 0x0604},    /* index 230 -0.030976    */
    {0x00db, -218, 0x0305},    /* index 231 0.000660     */
    {0x00d7, -250, 0x0106},    /* index 232 0.029426     */
    {0x00d2, -281, 0x0504},    /* index 233 -0.110239    */
    {0x00ce, -312, 0x0504},    /* index 234 0.077905     */
    {0x00c9, -343, 0x0205},    /* index 235 -0.074618    */
    {0x00c5, -375, 0x0205},    /* index 236 0.113525     */
    {0x00c1, -406, 0x0006},    /* index 237 -0.052906    */
    {0x00bd, -437, 0x0006},    /* index 238 0.135238     */
    {0x00b8, -468, 0x0105},    /* index 239 -0.237193    */
    {0x00b5, -500, 0x0105},    /* index 240 -0.049050    :-3dB */
    {0x00b1, -531, 0x0304},    /* index 241 -0.056102    */
    {0x00ad, -562, 0x0304},    /* index 242 0.132041     */
    {0x00a9, -593, 0x0304},    /* index 243 0.320185     */
    {0x00a5, -625, 0x0204},    /* index 244 -0.319525    */
    {0x00a2, -656, 0x0204},    /* index 245 -0.131381    */
    {0x009e, -687, 0x0005},    /* index 246 0.056763     */
    {0x009b, -718, 0x0005},    /* index 247 0.244906     */
    {0x0098, -750, 0x0005},    /* index 248 0.433050     */
    {0x0094, -781, 0x0104},    /* index 249 -0.293956    */
    {0x0091, -812, 0x0104},    /* index 250 -0.105812    */
    {0x008e, -843, 0x0104},    /* index 251 0.082332     */
    {0x008b, -875, 0x0104},    /* index 252 0.270475     */
    {0x0088, -906, 0x0104},    /* index 253 0.458619     */
    {0x0085, -937, 0x0004},    /* index 254  -0.376287   */
    {0x0082, -968, 0x0004}    /* index 255  -0.188144   */

};

#else
/* This is 16-step gain table, OV9710_GAIN_ROWS = 162, OV9710_GAIN_COLS = 3 */

const S16 OV9710_GAIN_TABLE[OV9710_GAIN_ROWS][OV9710_GAIN_COLS] =
{
    /* gain_value*256,  log2(gain)*1000,  register */
    /* error */
    {0x2000, 5000, 0xff},    /* index 0   0.000000   : 30dB */
    {0x1ea4, 4937, 0xff},    /* index 1   0.356695   */
    {0x1d58, 4875, 0xfe},    /* index 2   -0.344130  */
    {0x1c19, 4812, 0xfd},    /* index 3   -0.100035  */
    {0x1ae8, 4750, 0xfc},    /* index 4   0.091314   */
    {0x19c4, 4687, 0xfb},    /* index 5   0.232155   */
    {0x18ac, 4625, 0xfa},    /* index 6   0.324627   */
    {0x17a1, 4562, 0xf9},    /* index 7   0.370781   */
    {0x16a0, 4500, 0xf8},    /* index 8   0.372583   */
    {0x15ab, 4437, 0xf7},    /* index 9   0.331911   */
    {0x14bf, 4375, 0xf6},    /* index 10  0.250566   */
    {0x13de, 4312, 0xf5},    /* index 11  0.130276   */
    {0x1306, 4250, 0xf4},    /* index 12  -0.027313  */
    {0x1238, 4187, 0xf3},    /* index 13  -0.220617  */
    {0x1172, 4125, 0xf2},    /* index 14  -0.448124  */
    {0x10b5, 4062, 0xf1},    /* index 15  0.291620   */
    {0x1000, 4000, 0xf0},    /* index 16  0.000000   : 24dB */
    {0x0f52, 3937, 0x7f},    /* index 17  -0.321652  */
    {0x0eac, 3875, 0x7e},    /* index 18  0.327935   */
    {0x0e0c, 3812, 0x7d},    /* index 19  -0.050017  */
    {0x0d74, 3750, 0x7c},    /* index 20  -0.454343  */
    {0x0ce2, 3687, 0x7b},    /* index 21  0.116077   */
    {0x0c56, 3625, 0x7a},    /* index 22  -0.337687  */
    {0x0bd0, 3562, 0x79},    /* index 23  0.185390   */
    {0x0b50, 3500, 0x78},    /* index 24  -0.313708  */
    {0x0ad5, 3437, 0x77},    /* index 25  0.165956   */
    {0x0a5f, 3375, 0x76},    /* index 26  -0.374717  */
    {0x09ef, 3312, 0x75},    /* index 27  0.065138   */
    {0x0983, 3250, 0x74},    /* index 28  0.486343   */
    {0x091c, 3187, 0x73},    /* index 29  -0.110309  */
    {0x08b9, 3125, 0x72},    /* index 30  0.275938   */
    {0x085a, 3062, 0x71},    /* index 31  -0.354190  */
    {0x0800, 3000, 0x70},    /* index 32  0.000000   : 18dB */
    {0x07a9, 2937, 0x3f},    /* index 33  0.356695   */
    {0x0756, 2875, 0x3e},    /* index 34  -0.344130  */
    {0x0706, 2812, 0x3d},    /* index 35  -0.100035  */
    {0x06ba, 2750, 0x3c},    /* index 36  0.091314   */
    {0x0671, 2687, 0x3b},    /* index 37  0.232155   */
    {0x062b, 2625, 0x3a},    /* index 38  0.324627   */
    {0x05e8, 2562, 0x39},    /* index 39  0.370781   */
    {0x05a8, 2500, 0x38},    /* index 40  0.372583   */
    {0x056a, 2437, 0x37},    /* index 41  0.331911   */
    {0x052f, 2375, 0x36},    /* index 42  0.250566   */
    {0x04f7, 2312, 0x35},    /* index 43  0.130276   */
    {0x04c1, 2250, 0x34},    /* index 44  -0.027313  */
    {0x048e, 2187, 0x33},    /* index 45  -0.220617  */
    {0x045c, 2125, 0x32},    /* index 46  -0.448124  */
    {0x042d, 2062, 0x31},    /* index 47  0.291620   */
    {0x0400, 2000, 0x30},    /* index 48  0.000000   : 12dB */
    {0x03d4, 1937, 0x1f},    /* index 49  0.356695   */
    {0x03ab, 1875, 0x1e},    /* index 50  -0.344130  */
    {0x0383, 1812, 0x1d},    /* index 51  -0.100035  */
    {0x035d, 1750, 0x1c},    /* index 52  0.091314   */
    {0x0338, 1687, 0x1b},    /* index 53  0.232155   */
    {0x0315, 1625, 0x1a},    /* index 54  0.324627   */
    {0x02f4, 1562, 0x19},    /* index 55  0.370781   */
    {0x02d4, 1500, 0x18},    /* index 56  0.372583   */
    {0x02b5, 1437, 0x17},    /* index 57  0.331911   */
    {0x0297, 1375, 0x16},    /* index 58  0.250566   */
    {0x027b, 1312, 0x15},    /* index 59  0.130276   */
    {0x0260, 1250, 0x14},    /* index 60  -0.027313  */
    {0x0247, 1187, 0x13},    /* index 61  -0.220617  */
    {0x022e, 1125, 0x12},    /* index 62  -0.448124  */
    {0x0216, 1062, 0x11},    /* index 63  0.291620   */
    {0x0200, 1000, 0x10},    /* index 64  0.000000   : 6dB */
    {0x01ea,  937, 0x0f},    /* index 65  -0.321652  */
    {0x01d5,  875, 0x0e},    /* index 66  0.327935   */
    {0x01c1,  812, 0x0d},    /* index 67  -0.050017  */
    {0x01ae,  750, 0x0c},    /* index 68  -0.454343  */
    {0x019c,  687, 0x0b},    /* index 69  0.116077   */
    {0x018a,  625, 0x0a},    /* index 70  -0.337687  */
    {0x017a,  562, 0x09},    /* index 71  0.185390   */
    {0x016a,  500, 0x08},    /* index 72  -0.313708  */
    {0x015a,  437, 0x07},    /* index 73  0.165956   */
    {0x014b,  375, 0x06},    /* index 74  -0.374717  */
    {0x013d,  312, 0x05},    /* index 75  0.065138   */
    {0x0130,  250, 0x04},    /* index 76  0.486343   */
    {0x0123,  187, 0x03},    /* index 77  -0.110309  */
    {0x0117,  125, 0x02},    /* index 78  0.275938   */
    {0x010b,   62, 0x01},    /* index 79  -0.354190  */
    {0x0100,    0, 0x00},    /* index 80  0.000000   : 0dB */

};
#endif /* USE_32_STEP_GAIN_TABLE */

#if 0
static gd_video_mode_s ov9710_still_mode_table[] =
{
    {GD_VIDEO_MODE_VGA,     7},
    {GD_VIDEO_MODE_720P,    0},
    {GD_VIDEO_MODE_1080P,   6},
    {GD_VIDEO_MODE_3M_16_9, 5},
    {GD_VIDEO_MODE_5M_4_3,  4},
};
#endif

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
static GERR ov9710_write_reg( GD_HANDLE* pHandle, U8 subaddr, U8 data)
{
    U8 pbuf[3];
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);

    if (device->handleI2C == NULL)
    {
        return GD_ERR_I2C_NOT_OPEN;
    }

    pbuf[0] = subaddr;
    pbuf[1] = data;
    return GD_I2C_Write(&device->handleI2C, device->i2cAddrSensor, pbuf, 2);
}

static GERR ov9710_read_reg( GD_HANDLE* pHandle, U8 subaddr, U8 *pdata)
{
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);

    if (device->handleI2C == NULL)
    {
        return GD_ERR_I2C_NOT_OPEN;
    }

    return GD_I2C_Read(&device->handleI2C, device->i2cAddrSensor, &subaddr, 1, pdata, 1);
}

static void ov9710_dump_reg(GD_HANDLE *pHandle)
{
    int i;
    U8 data;

    for (i = 0; i < 172; i++)
    {
        ov9710_read_reg(pHandle, i, &data);
#ifdef SENSOR_DEBUG
        GM_Printf("0x%x=0x%x \n", i, data);
#endif
    }
}

static void ov9710_fill_video_format_regs(GD_HANDLE* pHandle)
{
    int i;
    U32 index;
    U32 format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov9710_fill_video_format_regs \n");
#endif
    index = pinfo->current_video_index;
    format_index = ov9710_video_info_table[index].format_index;

    for (i = 0; i < OV9710_VIDEO_FORMAT_REG_NUM; i++)
    {
        if (ov9710_video_format_tbl.reg[i] == 0)
            break;

        ov9710_write_reg(pHandle,
                  ov9710_video_format_tbl.reg[i],
                  ov9710_video_format_tbl.table[format_index].data[i]);
    }

    if (ov9710_video_format_tbl.table[format_index].ext_reg_fill)
        ov9710_video_format_tbl.table[format_index].ext_reg_fill(pHandle);

}

static void ov9710_fill_share_regs(GD_HANDLE *pHandle)
{
    int i;

    for (i = 0; i < OV9710_SHARE_REG_SIZE; i++)
    {
        ov9710_write_reg(pHandle, ov9710_share_regs[i].reg, ov9710_share_regs[i].data);
        if (ov9710_share_regs[i].reg == OV9710_COM7)
        {
            GD_SENSOR_Sleep(10);
        }
    }
}

static void ov9710_fill_pll_regs(GD_HANDLE* pHandle)
{
    int i;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov9710_fill_pll_regs\n");
#endif

    for (i = 0; i < OV9710_VIDEO_PLL_REG_TABLE_SIZE; i++)
    {
        ov9710_write_reg(pHandle, ov9710_pll_tbl[pinfo->pll_index].regs[i].reg,
            ov9710_pll_tbl[pinfo->pll_index].regs[i].data);
    }
}

static GERR ov9710_sw_reset(GD_HANDLE* pHandle)
{
    return GD_OK;
}

static GERR ov9710_reset(GD_HANDLE* pHandle)
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
    return ov9710_sw_reset(pHandle);
}

static GERR ov9710_get_video_mode(GD_HANDLE* pHandle, GD_VIDEO_MODE_E *p_mode)
{
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_mode = pinfo->current_vin_mode;

    return GD_OK;
}

static GERR ov9710_get_video_info(GD_HANDLE* pHandle, GD_SENSOR_VIDEO_INFO_S* p_video_info)
{
    GERR    errCode = GD_OK;
    U32     index;
    U32     format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;

    if (index >= OV9710_VIDEO_INFO_TABLE_SIZE)
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
        format_index = ov9710_video_info_table[index].format_index;

        p_video_info->width     = ov9710_video_info_table[index].def_width;
        p_video_info->height    = ov9710_video_info_table[index].def_height;
        p_video_info->fps       = pinfo->frame_rate;
        p_video_info->format    = ov9710_video_format_tbl.table[format_index].format;
        p_video_info->type      = ov9710_video_format_tbl.table[format_index].type;
        p_video_info->bits      = ov9710_video_format_tbl.table[format_index].bits;
        p_video_info->ratio     = ov9710_video_format_tbl.table[format_index].ratio;
        p_video_info->system    = GD_VIDEO_SYSTEM_AUTO;
        p_video_info->rev       = 0;
    }

    return errCode;
}

static GERR ov9710_get_agc_info(GD_HANDLE* pHandle, GD_SENSOR_AGC_INFO_S * p_agc_info)
{
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_agc_info = pinfo->agc_info;

    return GD_OK;
}
static GERR ov9710_get_shutter_info(GD_HANDLE* pHandle, GD_SENSOR_SHUTTER_INFO_S * pshutter_info)
{
    memset(pshutter_info, 0x00, sizeof(GD_SENSOR_SHUTTER_INFO_S));

    return GD_OK;
}
#if 0

static GERR ov9710_check_video_mode(GD_HANDLE* pHandle, amba_vin_source_mode_info* p_mode_info)
{
    GERR errCode = GD_OK;
    int  i;
    U32  index;
    U32  format_index;

    p_mode_info->is_supported = 0;
    memset(p_mode_info->fps_table, 0, p_mode_info->fps_table_size);
    memset(&p_mode_info->video_info, 0, sizeof (p_mode_info->video_info));

    for (i = 0; i < OV9710_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (ov9710_video_mode_table[i].mode == p_mode_info->mode)
        {
            if (p_mode_info->mode == GD_VIDEO_MODE_AUTO)
                p_mode_info->mode = OV9710_VIDEO_MODE_TABLE_AUTO;
            p_mode_info->is_supported = 1;

            index = ov9710_video_mode_table[i].still_index;
            format_index = ov9710_video_info_table[index].format_index;

            p_mode_info->video_info.width   = ov9710_video_info_table[index].def_width;
            p_mode_info->video_info.height  = ov9710_video_info_table[index].def_height;
            p_mode_info->video_info.fps     = ov9710_video_format_tbl.table[format_index].max_fps;
            p_mode_info->video_info.format  = ov9710_video_format_tbl.table[format_index].format;
            p_mode_info->video_info.type    = ov9710_video_format_tbl.table[format_index].type;
            p_mode_info->video_info.bits    = ov9710_video_format_tbl.table[format_index].bits;
            p_mode_info->video_info.ratio   = ov9710_video_format_tbl.table[format_index].ratio;
            p_mode_info->video_info.system  = GD_VIDEO_SYSTEM_AUTO;
            p_mode_info->video_info.rev     = 0;

            break;
        }
    }

    return errCode;
}
#endif

static GERR ov9710_query_sensor_id(GD_HANDLE* pHandle, U16 * ss_id)
{
    GERR errCode = GD_OK;
    U8   pidh = 0, pidl = 0;

    errCode = ov9710_read_reg(pHandle, OV9710_PIDH, &pidh);
    errCode = ov9710_read_reg(pHandle, OV9710_PIDL, &pidl);
    *ss_id = (U16) ((pidh << 8) | pidl);

    return errCode;

}

static GERR ov9710_query_snesor_version(GD_HANDLE* pHandle, U16 * ver)
{
#ifdef SENSOR_DEBUG
    GM_Printf("No version register in ov9710!\n");
#endif
    return GD_OK;
}

static GERR ov9710_set_still_mode(GD_HANDLE* pHandle, gd_vin_src_still_info_s *p_info)
{
    return GD_OK;
}

static GERR ov9710_set_shutter_time(GD_HANDLE* pHandle, U32 shutter_time)
{
    GERR    errCode = 0;
    U64     exposure_time_q9;
    U32     line_length, frame_length_lines;
    int     shutter_width;
    U8      data_l, data_h;

    ov9710_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov9710_set_shutter: 0x%x\n", shutter_time);
#endif

    pll_table = &ov9710_pll_tbl[pinfo->pll_index];

    exposure_time_q9 = shutter_time;

    errCode |= ov9710_read_reg(pHandle, OV9710_REG2B, &data_h);
    errCode |= ov9710_read_reg(pHandle, OV9710_REG2A, &data_l);
    line_length = (data_h<<8) + data_l;
    if(!line_length)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("line length is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    errCode |= ov9710_read_reg(pHandle, OV9710_RENDH, &data_h);
    errCode |= ov9710_read_reg(pHandle, OV9710_RENDL, &data_l);
    frame_length_lines = (data_h<<8) + data_l;

    exposure_time_q9 = exposure_time_q9 * (U64)pll_table->pixclk;

    //DO_DIV_ROUND(exposure_time_q9, line_length);
    //DO_DIV_ROUND(exposure_time_q9, 512000000);
    exposure_time_q9 = (exposure_time_q9 + line_length/2) / line_length;
    exposure_time_q9 = (exposure_time_q9 + 512000000/2) / 512000000;

    shutter_width = (U32)exposure_time_q9;

    /* FIXME: shutter width: 1 ~ (Frame format(V) - 2) */
    if(shutter_width < 1)
    {
        shutter_width = 1;
    }
    else if(shutter_width  > frame_length_lines - 2)
    {
        shutter_width = frame_length_lines - 2;
    }

#ifdef SENSOR_DEBUG
    GM_Printf("shutter_width: 0x%x\n", shutter_width);
#endif
    errCode |= ov9710_write_reg(pHandle, OV9710_AECH, (U8)((shutter_width & 0x00FF00) >> 8 ) );
    errCode |= ov9710_write_reg(pHandle, OV9710_AEC, (U8)((shutter_width & 0x0000FF) >> 0 ) );

    pinfo->current_shutter_time = shutter_time;
    //G_shutter_time = shutter_time;
    return errCode;
}

static GERR ov9710_set_slowshutter_mode(GD_HANDLE* pHandle, int mode)
{
    GERR errCode = GD_OK;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    if (mode == 1)
    {                                   /* 25fps -> 12.5fps */
        ov9710_write_reg(pHandle, OV9710_RENDH, 0x07);
        ov9710_write_reg(pHandle, OV9710_RENDL, 0xc4);
    }
    else if (mode == 2)
    {                            /* 30fps -> 15fps */
        ov9710_write_reg(pHandle, OV9710_RENDH, 0x06);
        ov9710_write_reg(pHandle, OV9710_RENDL, 0x79);
    }
    else
    {                                            /* return 30fps */
        ov9710_write_reg(pHandle, OV9710_RENDH, 0x03);
        ov9710_write_reg(pHandle, OV9710_RENDL, 0x3C);
    }

    pinfo->current_slowshutter_mode = mode;

    return errCode;
}

static GERR ov9710_set_agc_db(GD_HANDLE* pHandle, S32 agc_db)
{
    U16 idc_reg;
    U32 gain_index;
    S32 db_max;
    S32 db_step;

    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("ov9710_set_agc: 0x%x\n", agc_db);
#endif

    db_max = pinfo->agc_info.db_max;
    db_step = pinfo->agc_info.db_step;
    gain_index = (db_max - agc_db) / db_step;

    if (gain_index >= OV9710_GAIN_ROWS)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("index of gain table out of range!\n");
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    idc_reg = OV9710_GAIN_TABLE[gain_index][OV9710_GAIN_COL_REG];
    ov9710_write_reg(pHandle, OV9710_GAIN, idc_reg);

    pinfo->current_gain_db = agc_db;

    return GD_OK;
}

static GERR ov9710_set_low_light_agc(GD_HANDLE* pHandle, U32 agc_index)
{
    return GD_OK;
}

static GERR ov9710_set_mirror_mode(GD_HANDLE* pHandle, GD_SENSOR_MIRROR_MODE_S *mirror_mode)
{
    GERR    errCode = GD_OK;
    U32     readmode;
    U32     target_bayer_pattern;
    U8      tmp_reg0, tmp_reg1;
    U8      vstartLSBs;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    switch (mirror_mode->bayer_pattern)
    {
    case GD_VIN_SRC_BAYER_PATTERN_AUTO:
        break;

    case GD_VIN_SRC_BAYER_PATTERN_RG:
    case GD_VIN_SRC_BAYER_PATTERN_BG:
    case GD_VIN_SRC_BAYER_PATTERN_GR:
    case GD_VIN_SRC_BAYER_PATTERN_GB:
        pinfo->bayer_pattern = mirror_mode->bayer_pattern;
        break;

    default:
#ifdef SENSOR_DEBUG
        GM_Printf("do not support bayer pattern: %d\n", mirror_mode->bayer_pattern);
#endif
        return GD_ERR_BAD_PARAMETER;
        //return -EINVAL;
    }

    switch (mirror_mode->pattern)
    {
    case GD_VIN_SRC_MIRROR_AUTO:
        return 0;

    case GD_VIN_SRC_MIRROR_VERTICALLY:
        readmode    = OV9710_REG4_MIRROR_COLUMN;
        vstartLSBs  = 0x01;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_BG;
        break;

    case GD_VIN_SRC_MIRROR_NONE:
        readmode    = 0;
        vstartLSBs  = 0x0A;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_BG;
        break;

    case GD_VIN_SRC_MIRROR_HORRIZONTALLY_VERTICALLY:
        readmode    = OV9710_REG4_MIRROR_ROW + OV9710_REG4_MIRROR_COLUMN;
        vstartLSBs  = 0x01;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_BG;
        break;

    case GD_VIN_SRC_MIRROR_HORRIZONTALLY:
        readmode    = OV9710_REG4_MIRROR_ROW;
        vstartLSBs  = 0x00;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_BG;
        break;
    default:
#ifdef SENSOR_DEBUG
        GM_Printf("do not support cmd mirror mode\n");
#endif
        return GD_ERR_BAD_PARAMETER;
        //return -EINVAL;
    }

    errCode     |= ov9710_read_reg(pHandle, OV9710_REG04, &tmp_reg0);
    tmp_reg0    |= 0x01;//group latch enable
    errCode     |= ov9710_write_reg(pHandle, OV9710_REG04, tmp_reg0);
    tmp_reg0    &= (~OV9710_MIRROR_MASK);
    tmp_reg0    |= readmode;

    errCode     |= ov9710_read_reg(pHandle, OV9710_REG03, &tmp_reg1);
    tmp_reg1    &= (~0x0F);
    tmp_reg1    |= vstartLSBs;

    errCode     |= ov9710_write_reg(pHandle, OV9710_REG04, tmp_reg0);
    errCode     |= ov9710_write_reg(pHandle, OV9710_REG03, tmp_reg1);
    ov9710_write_reg(pHandle, 0xC3, 0x21);//restart to output frame
    errCode     |= ov9710_write_reg(pHandle, 0xFF, 0xFF);//latch trigger

    //LindengYu
    // msleep(1000/DIV_ROUND(512000000, pinfo->frame_rate));//delay 1 frame to cancel group

    ov9710_read_reg(pHandle, OV9710_REG04, &tmp_reg0);
    tmp_reg0 &= 0xFE;//group latch disable
    ov9710_write_reg(pHandle, OV9710_REG04, tmp_reg0);
    ov9710_write_reg(pHandle, 0xC3, 0x21);//restart to output frame
    ov9710_write_reg(pHandle, 0xFF, 0xFF);//latch trigger

    if (mirror_mode->bayer_pattern == GD_VIN_SRC_BAYER_PATTERN_AUTO)
    {
        pinfo->bayer_pattern = target_bayer_pattern;
    }

    return errCode;
}

static GERR ov9710_set_fps(GD_HANDLE* pHandle, U32 fps)
{
    GERR        errCode = GD_OK;
    U32         frame_time = 0;
    U32         index;
    U32         format_index;
    U64         frame_time_pclk;
    int         vertical_lines = 0;
    U32         line_length;
    U8          data_l, data_h;
    U8          current_pll_index = 0;
    // LindengYu
    //amba_vin_irq_fix        vin_irq_fix;

    ov9710_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;

    if (index >= OV9710_VIDEO_INFO_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("ov9710_set_fps index = %d!\n", index);
#endif
        errCode = GD_ERR_BAD_PARAMETER;//-EPERM;
        return errCode;
    }

    format_index = ov9710_video_info_table[index].format_index;

    if (fps == GD_VIDEO_FPS_AUTO)
        fps = GD_VIDEO_FPS_29_97;
    if(fps < ov9710_video_format_tbl.table[format_index].max_fps)
    {
        // LindengYu
#ifdef SENSOR_DEBUG
        //GM_Printf("The max supported fps is %d\n",
        //    DIV_ROUND(512000000, ov9710_video_format_tbl.table[format_index].max_fps));
#endif
        return GD_ERR_BAD_PARAMETER;//-EPERM;
    }

    frame_time = fps;

    /* ToDo: Add specified PLL index*/
    switch(fps)
    {
    case GD_VIDEO_FPS_29_97:
        switch(format_index)
        {
        case 0://1280x800
            current_pll_index = 0;
            break;
        case 1://640x400
            current_pll_index = 1;
            break;
        }
        break;
    case GD_VIDEO_FPS_30:
        switch(format_index)
        {
        case 0://1280x800
            current_pll_index = 2;
            break;
        case 1://640x400
            current_pll_index = 3;
            break;
        }
        break;
    case GD_VIDEO_FPS_59_94:
        current_pll_index = 1;
        break;
    case GD_VIDEO_FPS_60:
        current_pll_index = 3;
        break;
    default:
        current_pll_index = ov9710_video_format_tbl.table[format_index].pll_index;
        break;
    }

    if(pinfo->pll_index != current_pll_index)
    {
        pinfo->pll_index = current_pll_index;
        ov9710_fill_pll_regs(pHandle);
        //errCode = ov9710_init_vin_clock(pHandle, &ov9710_pll_tbl[pinfo->pll_index]);
        //if (errCode != GD_OK)
        //    return errCode;
    }

    pll_table = &ov9710_pll_tbl[pinfo->pll_index];

    errCode |= ov9710_read_reg(pHandle, OV9710_REG2B, &data_h);
    errCode |= ov9710_read_reg(pHandle, OV9710_REG2A, &data_l);
    line_length = (data_h << 8) + data_l;
    if(!line_length)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("line length is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    frame_time_pclk = frame_time * (U64)pll_table->pixclk;

    // frame_time_pclk = (frame_time_pclk + line_length/2) / line_length;
    //DO_DIV_ROUND(frame_time_pclk, line_length);
    //DO_DIV_ROUND(frame_time_pclk, 512000000);
    frame_time_pclk = (frame_time_pclk + line_length/2) / line_length;
    frame_time_pclk = (frame_time_pclk + 512000000/2) / 512000000;
#ifdef SENSOR_DEBUG
    GM_Printf("frame_time %d, line_length 0x%x, vertical_lines 0x%llx\n", frame_time, line_length, frame_time_pclk);
#endif

    vertical_lines = frame_time_pclk;

    errCode |= ov9710_write_reg(pHandle, OV9710_RENDH, (U8)((vertical_lines & 0x00FF00) >>8));
    errCode |= ov9710_write_reg(pHandle, OV9710_RENDL, (U8)(vertical_lines & 0x0000FF));

#ifdef SENSOR_DEBUG
    GM_Printf("set fps change line_length %d, vertical_lines %d, fps = %d \n", line_length, vertical_lines, fps);
#endif

    ov9710_set_shutter_time(pHandle, pinfo->current_shutter_time);
    pinfo->frame_rate = fps;

    //set vblank time
    // LindengYu
    //vin_irq_fix.mode = GD_VIN_VSYNC_IRQ_IDSP;
    //vin_irq_fix.delay = 0;
    //errCode |= amba_vin_adapter_cmd(pHandle->adapid,
    //    GD_VIN_ADAP_FIX_ARCH_VSYNC, &vin_irq_fix);
    return errCode;
}

static GERR ov9710_set_video_index(GD_HANDLE* pHandle, U32 index)
{
    GERR errCode = GD_OK;
    U32 format_index;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    if (index >= OV9710_VIDEO_INFO_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("ov9710_set_video_index do not support mode %d!\n", index);
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    // LindengYu
    //errCode |= ov9710_pre_set_vin_mode(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;
    pinfo->current_video_index = index;
    format_index            = ov9710_video_info_table[index].format_index;

    pinfo->cap_start_x      = ov9710_video_info_table[index].def_start_x;
    pinfo->cap_start_y      = ov9710_video_info_table[index].def_start_y;
    pinfo->cap_cap_w        = ov9710_video_info_table[index].def_width;
    pinfo->cap_cap_h        = ov9710_video_info_table[index].def_height;
    pinfo->bayer_pattern    = ov9710_video_info_table[index].bayer_pattern;
    //set the specified PLL index for each sensor_mode.
    pinfo->pll_index        = ov9710_video_format_tbl.table[format_index].pll_index;
    // LindengYu
    //ov9710_print_info(pHandle);

    // LindengYu
    //errCode |= ov9710_set_vin_mode(pHandle);

    ov9710_fill_pll_regs(pHandle);
    ov9710_fill_share_regs(pHandle);
    ov9710_fill_video_format_regs(pHandle);

    ov9710_set_fps(pHandle, GD_VIDEO_FPS_AUTO);
    ov9710_set_shutter_time(pHandle, GD_VIDEO_FPS_60);
    ov9710_set_agc_db(pHandle, 0);

    // LindengYu
    //errCode |= ov9710_post_set_vin_mode(pHandle);

    if (!errCode)
        pinfo->mode_type = GD_VIN_SRC_ENABLED_FOR_VIDEO;

    return errCode;
}

static GERR ov9710_set_video_mode(GD_HANDLE *pHandle, GD_VIDEO_MODE_E mode)
{
    GERR errCode = GD_OK;
    int i;
    GD_SENSOR_INFO_S*             pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    GD_SENSOR_Sleep(10);
    ov9710_reset(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;

    for (i = 0; i < OV9710_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (ov9710_video_mode_table[i].mode == mode)
        {
            errCode = ov9710_set_video_index(pHandle, ov9710_video_mode_table[i].preview_index);
            pinfo->mode_index = i;
            break;
        }
    }
    if (i >= OV9710_VIDEO_MODE_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("ov9710_set_video_mode do not support %d, %d!\n", mode, i);
#endif
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
    }

    if (errCode == GD_OK)
    {
        pinfo->current_vin_mode = ov9710_video_mode_table[i].mode;
        pinfo->mode_type        = ov9710_video_mode_table[i].preview_mode_type;
    }

    return errCode;
}


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR ov9710_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    GERR errCode = GD_OK;
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

    pinfo = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("\t\t---->cmd is %d\n", cmd);
#endif
    switch (cmd)
    {
    case GD_VIN_SRC_RESET:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_POWER:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
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
            pub_src->sensor_id          = SENSOR_OV9710;
            pub_src->default_mode       = OV9710_VIDEO_MODE_TABLE_AUTO;
            pub_src->total_channel_num  = pHandle->total_channel_num;
            pub_src->active_channel_id  = pHandle->active_channel_id;
            pub_src->source_type.decoder = GD_VIN_CMOS_CHANNEL_TYPE_AUTO;
        }
        break;

    case GD_VIN_SRC_CHECK_VIDEO_MODE:
        errCode = ov9710_check_video_mode(pHandle, (amba_vin_source_mode_info *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_INFO:
        errCode = ov9710_get_video_info(pHandle, (GD_SENSOR_VIDEO_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_AGC_INFO:
        errCode = ov9710_get_agc_info(pHandle, (GD_SENSOR_AGC_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_INFO:
        errCode = ov9710_get_shutter_info(pHandle, (GD_SENSOR_SHUTTER_INFO_S *) args);
        break;

#if 0
    case GD_VIN_SRC_GET_CAPABILITY:
        errCode = ov9710_get_capability(pHandle, (amba_vin_src_capability *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_MODE:
        errCode = ov9710_get_video_mode(pHandle, (GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_SET_VIDEO_MODE:
        errCode = ov9710_set_video_mode(pHandle, *(GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_GET_STILL_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_STILL_MODE:
        errCode = ov9710_set_still_mode(pHandle, (gd_vin_src_still_info_s *) args);
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
        errCode = ov9710_set_fps(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_TIME:
        *(U32 *)args = pinfo->current_shutter_time;
        break;

    case GD_VIN_SRC_SET_SHUTTER_TIME:
        errCode = ov9710_set_shutter_time(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_GAIN_DB:
        *(S32 *)args = pinfo->current_gain_db;
        break;

    case GD_VIN_SRC_SET_GAIN_DB:
        errCode = ov9710_set_agc_db(pHandle, *(S32 *) args);
        break;

    case GD_VIN_SRC_GET_LOW_LIGHT_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_LOW_LIGHT_MODE:
        errCode = ov9710_set_low_light_agc(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_SET_MIRROR_MODE:
        errCode = ov9710_set_mirror_mode(pHandle, (GD_SENSOR_MIRROR_MODE_S *) args);
        break;

    case GD_VIN_SRC_TEST_DUMP_REG:
        ov9710_dump_reg(pHandle);
        break;

    case GD_VIN_SRC_TEST_GET_DEV_ID:
        {
            U16 sen_id  = 0;
            U16 sen_ver = 0;
            U32 *pdata  = (U32 *) args;

            errCode = ov9710_query_sensor_id(pHandle, &sen_id);
            if (errCode != GD_OK)
            {
                return errCode;
            }
            errCode = ov9710_query_snesor_version(pHandle, &sen_ver);
            if (errCode != GD_OK)
            {
                return errCode;
            }
            *pdata = (sen_id << 16) | sen_ver;
        }
        break;

    case GD_VIN_SRC_TEST_GET_REG_DATA:
        {
            GD_SENSOR_REG_DATA_S *reg_data;
            U8 subaddr;
            U8 data;

            reg_data    = (GD_SENSOR_REG_DATA_S*) args;
            subaddr     = reg_data->reg;

            errCode     = ov9710_read_reg(pHandle, subaddr, &data);

            reg_data->data = data;
        }
        break;

    case GD_VIN_SRC_TEST_SET_REG_DATA:
        {
            GD_SENSOR_REG_DATA_S *reg_data;
            U8 subaddr;
            U8 data;

            reg_data    = (GD_SENSOR_REG_DATA_S *) args;
            subaddr     = reg_data->reg;
            data        = reg_data->data;

            errCode     = ov9710_write_reg(pHandle, subaddr, data);
        }
        break;

    case GD_VIN_SRC_SET_TRIGGER_MODE:
        break;

    case GD_VIN_SRC_SET_CAPTURE_MODE:
        break;

    case GD_VIN_SRC_SET_SLOWSHUTTER_MODE:
        errCode = ov9710_set_slowshutter_mode(pHandle, *(int *) args);
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

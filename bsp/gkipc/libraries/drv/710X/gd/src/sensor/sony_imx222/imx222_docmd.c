/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/sony_imx222/imx222_docmd.c
**
** \version     $Id: imx222_docmd.c 334 2014-12-08 09:03:17Z yulindeng $
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
#include "imx222_pri.h"
#include "gd_gpio.h"
#include "gd_spi.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************
#define IMX222_DEFAULT_VIDEO_INDEX          (0)
#define IMX222_VIDEO_MODE_TABLE_AUTO        GD_VIDEO_MODE_1080P_PAL

#define IMX222_SHARE_3M_CLASS_REG_SIZE      (sizeof(imx222_3M_class_regs)/sizeof(imx222_reg_table))
#define IMX222_SHARE_1080P_CLASS_REG_SIZE   (sizeof(imx222_1080p_class_regs)/sizeof(imx222_reg_table))
#define IMX222_SHARE_REG_SIZE               (sizeof(imx222_share_regs)/sizeof(imx222_reg_table))
#define IMX222_VIDEO_INFO_TABLE_SIZE        (sizeof(imx222_video_info_table)/sizeof(gd_video_mode_s))
#define IMX222_VIDEO_MODE_TABLE_SIZE        (sizeof(imx222_video_mode_table)/sizeof(gd_video_mode_s))

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

/*
 * As imx222 need to feed 0x3XX area with different mysterious binary for 3M and 1080p class,
 * the share regs is only useful for the same 3M class or 1080p class mode, for example:
 * 1920x1080p and 1024x768 share the same imx222_1080p_class_regs,
 */
static imx222_reg_table imx222_3M_class_regs[] =
{
    {IMX222_BLC_LSB, 0x00},         //0x0220
    {0x0225, 0x47},                 //TODO: 1080p should be 43 for LVDS but it is 47
    {0x022A, 0x22},                 //TODO: 1080p should 0 or by pass, but write 0x22? , 0x0, 0x20, 0x02 all three stall, 0x26 stall for no preview
    {IMX222_DCKDLY_BITSEL, 0x08},   //0x022D TODO: use 0x08...? slave mode
    {0x025E, 0xFF},
    {0x025F, 0x02},
    {0x0273, 0xB1},
    {0x0274, 0x01},
    {0x0276, 0x60},
    {0x029D, 0x00},
    {0x02D4, 0x00},
    {0x02D6, 0x40},
    {0x02D8, 0x66},
    {0x02D9, 0x0E},
    {0x02DB, 0x06},
    {0x02DC, 0x06},
    {0x02DD, 0x0C},
    {0x02E0, 0x7C},
/*------Section 3, can't be read----------*/
    {0x0301, 0x50},
    {0x0302, 0x1c},
    {0x0304, 0xF0}, // 1080p 0x20 vs 3M 0xf0
    {0x0305, 0x01}, // 1080p 0x00 vs 3M 0x01
    {0x0306, 0x93},
    {0x0307, 0xd0},
    {0x0308, 0x09},
    {0x0309, 0xe3},
    {0x030A, 0xb1},
    {0x030B, 0x1f},
    {0x030C, 0xc5},
    {0x030D, 0x31},
    {0x030E, 0x21},
    {0x030F, 0x2b},
    {0x0310, 0x02}, // 1080p 0x04 vs 3M 0x02
    {0x0311, 0x59},
    {0x0312, 0x15},
    {0x0313, 0x59},
    {0x0314, 0x15},
    {0x0315, 0x71},
    {0x0316, 0x1d},
    {0x0317, 0x59},
    {0x0318, 0x15},
    {0x0319, 0x00},
    {0x031B, 0x00},
    {0x031F, 0x9c},
    {0x0320, 0xf0},
    {0x0321, 0x09},
    {0x0323, 0xb0}, // 1080p 0x60 vs 3M b0
    {0x0324, 0x22}, // 1080P 0x44 vs 3M 0x22
    {0x0325, 0xc5},
    {0x0326, 0x31},
    {0x0327, 0x21},
    {0x0329, 0x30},
    {0x032A, 0x21},
    {0x032B, 0xc5},
    {0x032C, 0x31},
    {0x032D, 0x21},
    {0x032E, 0x2c},
    {0x032F, 0x62},
    {0x0330, 0x1c},
    {0x0332, 0xf0}, // 1080p 0xd0 vs 3M 0xf0
    {0x0335, 0x40}, // 1080p 0x10 vs 3M 0x40
    {0x0337, 0xc5},
    {0x0338, 0x11}, // 1080p 0x13 vs 3M 0x11
    {0x033A, 0xc5},
    {0x033B, 0x11}, // 1080p 0x13 vs 3M 0x11
    {0x033E, 0x90},
    {0x0343, 0x91},
    {0x0344, 0x20},
    {0x0345, 0x09},
    {0x0346, 0x2f},
    {0x034B, 0x35},
    {0x034D, 0x3f},
    {0x034F, 0x3f},
    {0x0351, 0xad},
    {0x0352, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x0353, 0xad},
    {0x0354, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x0357, 0x46},
    {0x0359, 0x12}, // 1080p 0x0f vs 3M 0x12
    {0x035B, 0xc5},
    {0x035C, 0x01}, // 1080p 0x03 vs 3M 0x01
    {0x035D, 0x11}, // 1080p 0x0e vs 3M 0x11
    {0x035F, 0x97},
    {0x1223, 0xc4},
    {0x1224, 0x01}, // 1080p 0x03 vs 3M 0x01
    {0x1229, 0x44},
    {0x122B, 0x3a},
    {0x122D, 0xa0},
    {0x122F, 0x9d},
    {0x0373, 0x3a},
    {0x0374, 0x00},//TODO: co, but the initial value is 0 already
    {0x0379, 0x3c},
    {0x037B, 0x3a},
    {0x037D, 0x9f},
    {0x037F, 0x9d},
    {0x0383, 0x9d},
    {0x0398, 0x9e},
    {0x039A, 0xa7},
    {0x039B, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x039C, 0x07}, // 1080p 0x06 vs 3M 0x07
    {0x039E, 0x11}, // 1080p 0x0e vs 3M 0x11
    {0x03AC, 0x1b}, // 1080p 0x16 vs 3M 0x1b
    {0x03AE, 0x08}, // 1080p 0x07 vs 3M 0x08
    {0x03B0, 0x1b}, // 1080p 0x16 vs 3M 0x1b
    {0x03B2, 0x08}, // 1080p 0x07 vs 3M 0x08
    {0x03B4, 0x11}, // 1080p 0x0e vs 3M 0x11
    {0x03B6, 0xa7},
    {0x03B7, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03B8, 0xa7},
    {0x03B9, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03BA, 0x11}, // 1080p 0x0e vs 3M 0x11
    {0x03BC, 0x11}, // 1080p 0x0e vs 3M 0x11
    {0x03BE, 0xa7},
    {0x03BF, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03C0, 0xa9},
    {0x03C1, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03C2, 0xab},
    {0x03C3, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03C4, 0x16}, // 1080p 0x12 vs 3M 0x16
    {0x03C6, 0x1b}, // 1080p 0x16 vs 3M 0x1b
    {0x03C8, 0x9e},
    {0x03C9, 0xb0},
    {0x03CA, 0x0a}, // 1080p 0x11 vs 3M 0x0a (12 bit mode)
    {0x03CB, 0x07}, // 1080p 0x06 vs 3M 0x07
    {0x03CC, 0xb0}, // 1080p 0x60 vs 3M 0xb0
    {0x03CE, 0x46},
    {0x03D0, 0x92},
    {0x03D1, 0x80},
    {0x03D2, 0x0b}, // 1080p 0x13 vs 3M 0x0b
    {0x03D3, 0x81},
    {0x03D4, 0x01}, // 1080p 0x03 vs 3M 0x01
    {0x03D5, 0x17}, // 1080p 0x24 vs 3M 0x17 (LVDS)
    {0x03D6, 0x02}, // 1080p 0x04 vs 3M 0x02 (LVDS)
    {0x03D7, 0x1b}, // 1080p 0x28 vs 3M 0x1b (LVDS)
    {0x03D8, 0x02}, // 1080p 0x04 vs 3M 0x02 (LVDS)
    {0x03DD, 0x53},
    {0x03DF, 0x91},
    {0x03E1, 0xbc},
    {0x03E2, 0x00}, // 1080p 0x01 vs 3M 0x00
    {0x03E3, 0x80},
    {0x03E4, 0x01}, // 1080p 0x03 vs 3M 0x01
};


static imx222_reg_table imx222_1080p_class_regs[] =
{
    {IMX222_REG27,      0x20},  //0x0227
    {IMX222_SYSCCODE,   0xe0},  //0x023b
/*------Section 3, can't be read----------*/
    {0x0300, 0x01},
    {0x0317, 0x0d},
};


static imx222_reg_table imx222_share_regs[] =
{
    {IMX222_DCKDLY_BITSEL, 0x48},   //0x022D 10-bit output 2-bit shift(right justified)
};

/*
*  1.rember to update IMX222_VIDEO_PLL_REG_TABLE_SIZE if you add/remove the regs
*     2.see rct.h for pixclk/extclk value
IMX222_PLL_PREDIVEDER:000=1, 001=1.5, 010=2, 011=2.5, 100=3, 101=4, 110=6, 111=8
3. pixclk = ((extclk / 8) / IMX222_PLL_PREDIVEDER) * IMX222_PLL_CTRL02

*/
static imx222_pll_reg_table imx222_pll_tbl[] =
{
    //[0] =
    {//for 30/60fps
        PLL_CLK_74_25MHZ,   //.pixclk = PLL_CLK_74_25MHZ,
        PLL_CLK_37_125MHZ,  //.extclk = PLL_CLK_37_125MHZ,
        //.regs =
        {
            {0, 0},          // 1/2
        }
    },
    //[1] =
    {//for 29.97/59.94fps
        74175750,   //.pixclk = 74175750,
        37087875,   //.extclk = 37087875,
        //.regs =
        {
            {0, 0},          // 1/2
        }
    },
    /* << add pll config here if necessary >> */
};

/* the table is used to provide video info to application */
static imx222_video_info imx222_video_info_table[] =
{
    //[0] = GD_VIDEO_MODE_720P
    {
        0,//.format_index
        (4 + 4 + 36 +8 +8+16) + 64,//.def_start_x
        6+1+4+6+2+4,//.def_start_y
        1280,//.def_width
        720,//.def_height
        (0 + 0),//.sync_start
        0,//.type_ext
        GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[1] = GD_VIDEO_MODE_720P_PAL
    {
        1,//.format_index
        (4 + 4 + 36 +8 +8+16) + 64,//.def_start_x
        6+1+4+6+2+4,//.def_start_y
        1280,//.def_width
        720,//.def_height
        (0 + 0),//.sync_start
        0,//.type_ext
        GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[2] = GD_VIDEO_MODE_1080P
    {
        2,//.format_index
        (4 + 4 + 36 +8 +8+16) + 64,//.def_start_x
        (12 + 1 + 4 + 8 +2 +6),//.def_start_y         = 0,
        1920,//.def_width        = 1920,
        1080,//.def_height       = 1080,
        (0 + 0),//.sync_start    = (0 + 0),
        0,//.type_ext =??
        GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[3] = GD_VIDEO_MODE_AUTO / GD_VIDEO_MODE_1080P_PAL
    {
       3,//.format_index        = 2,
       (4 + 4 + 36 +8 +8+16) + 64,//.def_start_x
       (12 + 1 + 4 + 8 +2 +6),//.def_start_y         = 0,
       1920,//.def_width        = 1920,
       1080,//.def_height       = 1080,
       (0 + 0),//.sync_start    = (0 + 0),
       0,//.type_ext =??
       GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },

    //[4] = GD_VIDEO_MODE_OFF
    {//do what?
        4,//.format_index    = 3,
        0,//.def_start_x     = 0,
        0,//.def_start_y     = 0,
        1280,//.def_width       = 1280,
        720,//.def_height      = 720,
        (0 + 0),//.sync_start      = (0 + 0),
        0,//.type_ext =??
        GD_VIN_SRC_BAYER_PATTERN_GR,//.bayer_pattern     = GD_VIN_SRC_BAYER_PATTERN_GR,
    },
};

static gd_video_mode_s imx222_video_mode_table[] =
{
    {
        GD_VIDEO_MODE_AUTO, // GD_VIDEO_MODE_1080P_PAL,//@50P
        3, /* select the index from above info table imx222_video_info_table*/
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        3, /* select the index from above info table */
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
        GD_VIDEO_MODE_720P_PAL,//@50P
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        1,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_1080P,
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        2,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_1080P_PAL,//@50P
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        3,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
    {
        GD_VIDEO_MODE_OFF,
        4,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL),
        4,
        (GD_VIN_SRC_ENABLED_FOR_VIDEO | GD_VIN_SRC_ENABLED_FOR_STILL)
    },
};

/*   < rember to update IMX222_VIDEO_FORMAT_REG_TABLE_SIZE, once you add or remove table items */
/*   < rember to update IMX222_VIDEO_FORMAT_REG_NUM, once you add or remove register here*/
static imx222_video_format_reg_table imx222_video_format_tbl =
{
    //.reg =
    {
        IMX222_MODE,        //0x0202,
        IMX222_HMAX_LSB,    //0x0203,
        IMX222_HMAX_MSB,    //0x0204,
        IMX222_VMAX_LSB,    //0x0205,
        IMX222_VMAX_MSB,    //0x0206,
        IMX222_FRSEL,       //0x0211,// FRSEL/OPORTSEL/M12BEN
        IMX222_SSBRK,       //0x0212 // ADRES
        IMX222_WINPH_LSB,   //0x0214,
        IMX222_WINPH_MSB,   //0x0215,
        IMX222_WINPV_LSB,   //0x0216,
        IMX222_WINPV_MSB,   //0x0217,
        IMX222_WINWH_LSB,   //0x0218,
        IMX222_WINWH_MSB,   //0x0219,
        IMX222_WINWV_LSB,   //0x021A,
        IMX222_WINWV_MSB,   //0x021B,
        IMX222_BLC_LSB,     //0x0220,// BLKLEVEL
        IMX222_BLC_MSB,     //0x0221,// 10BITA
        IMX222_XVSLNG,      //0x0222,// 720PMODE
        IMX222_10BITB,      //0x027A,//
        IMX222_10BITC,      //0x027B,//
        IMX222_10B1080P_LSB,//0x0298,//
        IMX222_10B1080P_MSB,//0x0299,//
        IMX222_12B1080P_LSB,//0x029A,//
        IMX222_12B1080P_MSB,//0x029B,//
        IMX222_PRES,        //0x02CE,//
        IMX222_DRES_LSB,    //0x02CF,//
        IMX222_DRES_MSB,    //0x02D0,//
        IMX222_XMSTA,       //0x022C,// MASTER
        IMX222_CONTROL,     //0x0200,// STANDBY
    },
    {
        //.table[0] = GD_VIDEO_MODE_720P@60
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,// 0x0202 IMX222_MODE
                0x39,// 0x0203 IMX222_HMAX_LSB          825
                0x03,// 0x0204 IMX222_HMAX_MSB
                0xEE,// 0x0205 IMX222_VMAX_LSB          750
                0x02,// 0x0206 IMX222_VMAX_MSB
                0x00,// 0x0211 IMX222_FRSEL FRSEL/OPORTSEL/M12BEN
                0x80,// 0x0212 IMX222_SSBRK ADRES
                0x40,// 0x0214 IMX222_WINPH_LSB         320
                0x01,// 0x0215 IMX222_WINPH_MSB
                0xF0,// 0x0216 IMX222_WINPV_LSB         240
                0x00,// 0x0217 IMX222_WINPV_MSB
                0x40,// 0x0218 IMX222_WINWH_LSB         1344
                0x05,// 0x0219 IMX222_WINWH_MSB
                0xE9,// 0x021A IMX222_WINWV_LSB         745
                0x02,// 0x021B IMX222_WINWV_MSB
                0x3C,// 0x0220 IMX222_BLC_LSB BLKLEVEL
                0x00,// 0x0221 IMX222_BLC_MSB 10BITA
                0x80,// 0x0222 IMX222_XVSLNG  720PMODE
                0x00,// 0x027A IMX222_10BITB
                0x00,// 0x027B IMX222_10BITC
                0x26,// 0x0298 IMX222_10B1080P_LSB      550
                0x02,// 0x0299 IMX222_10B1080P_MSB
                0x4C,// 0x029A IMX222_12B1080P_LSB      1100
                0x04,// 0x029B IMX222_12B1080P_MSB
                0x00,// 0x02CE IMX222_PRES
                0x00,// 0x02CF IMX222_DRES_LSB
                0x00,// 0x02D0 IMX222_DRES_MSB
                0x00,// 0x022C IMX222_XMSTA
                0x30,// 0x0200 IMX222_CONTROL STANDBY
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
            GD_VIDEO_FPS_60,//.auto_fps = GD_VIDEO_FPS_29_97,
        },
        //.table[1] = GD_VIDEO_MODE_720P_PAL@50
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x01,// 0x0202 IMX222_MODE
                0x72,// 0x0203 IMX222_HMAX_LSB          1650
                0x06,// 0x0204 IMX222_HMAX_MSB
                0xEE,// 0x0205 IMX222_VMAX_LSB          750
                0x02,// 0x0206 IMX222_VMAX_MSB
                0x01,// 0x0211 IMX222_FRSEL FRSEL/OPORTSEL/M12BEN
                0x80,// 0x0212 IMX222_SSBRK ADRES
                0x40,// 0x0214 IMX222_WINPH_LSB         320
                0x01,// 0x0215 IMX222_WINPH_MSB
                0xF0,// 0x0216 IMX222_WINPV_LSB         240
                0x00,// 0x0217 IMX222_WINPV_MSB
                0x40,// 0x0218 IMX222_WINWH_LSB         1344
                0x05,// 0x0219 IMX222_WINWH_MSB
                0xE9,// 0x021A IMX222_WINWV_LSB         745
                0x02,// 0x021B IMX222_WINWV_MSB
                0x3C,// 0x0220 IMX222_BLC_LSB BLKLEVEL
                0x01,// 0x0221 IMX222_BLC_MSB 10BITA
                0x80,// 0x0222 IMX222_XVSLNG  720PMODE
                0x40,// 0x027A IMX222_10BITB
                0x02,// 0x027B IMX222_10BITC
                0x26,// 0x0298 IMX222_10B1080P_LSB      550
                0x02,// 0x0299 IMX222_10B1080P_MSB
                0x4C,// 0x029A IMX222_12B1080P_LSB      1100
                0x04,// 0x029B IMX222_12B1080P_MSB
                0x00,// 0x02CE IMX222_PRES
                0x00,// 0x02CF IMX222_DRES_LSB
                0x00,// 0x02D0 IMX222_DRES_MSB
                0x00,// 0x022C IMX222_XMSTA
                0x30,// 0x0200 IMX222_CONTROL STANDBY
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
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_60,
            GD_VIDEO_FPS_30,//.auto_fps = GD_VIDEO_FPS_25,
        },
        //.table[2] = GD_VIDEO_MODE_1080P@30P
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x0F,// 0x0202 IMX222_MODE
                0x4C,// 0x0203 IMX222_HMAX_LSB          1100
                0x04,// 0x0204 IMX222_HMAX_MSB
                0x65,// 0x0205 IMX222_VMAX_LSB          1125
                0x04,// 0x0206 IMX222_VMAX_MSB
                0x00,// 0x0211 IMX222_FRSEL FRSEL/OPORTSEL/M12BEN
                0x82,// 0x0212 IMX222_SSBRK ADRES
                0x00,// 0x0214 IMX222_WINPH_LSB         0
                0x00,// 0x0215 IMX222_WINPH_MSB
                0x3C,// 0x0216 IMX222_WINPV_LSB         60
                0x00,// 0x0217 IMX222_WINPV_MSB
                0xC0,// 0x0218 IMX222_WINWH_LSB         1984
                0x07,// 0x0219 IMX222_WINWH_MSB
                0x51,// 0x021A IMX222_WINWV_LSB         1105
                0x04,// 0x021B IMX222_WINWV_MSB
                0xF0,// 0x0220 IMX222_BLC_LSB BLKLEVEL  240
                0x00,// 0x0221 IMX222_BLC_MSB 10BITA
                0x00,// 0x0222 IMX222_XVSLNG  720PMODE
                0x00,// 0x027A IMX222_10BITB
                0x00,// 0x027B IMX222_10BITC
                0x26,// 0x0298 IMX222_10B1080P_LSB      550
                0x02,// 0x0299 IMX222_10B1080P_MSB
                0x26,// 0x029A IMX222_12B1080P_LSB      550
                0x02,// 0x029B IMX222_12B1080P_MSB
                0x16,// 0x02CE IMX222_PRES
                0x82,// 0x02CF IMX222_DRES_LSB          130
                0x00,// 0x02D0 IMX222_DRES_MSB
                0x00,// 0x022C IMX222_XMSTA
                0x30,// 0x0200 IMX222_CONTROL STANDBY
            },
            NULL,//.fps_table = NULL,
            1920,//.width = 1920,
            1080,//.height = 1080,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_12,//.bits = GD_VIDEO_BITS_12,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_30,
            GD_VIDEO_FPS_30,//.auto_fps = GD_VIDEO_FPS_29_97,
        },
        //.table[3] = GD_VIDEO_MODE_1080P_PAL@25P / GD_VIDEO_MODE_AUTO
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x0F,// 0x0202 IMX222_MODE
                0x28,// 0x0203 IMX222_HMAX_LSB          1320
                0x05,// 0x0204 IMX222_HMAX_MSB
                0x65,// 0x0205 IMX222_VMAX_LSB          1125
                0x04,// 0x0206 IMX222_VMAX_MSB
                0x00,// 0x0211 IMX222_FRSEL FRSEL/OPORTSEL/M12BEN
                0x82,// 0x0212 IMX222_SSBRK ADRES
                0x00,// 0x0214 IMX222_WINPH_LSB         0
                0x00,// 0x0215 IMX222_WINPH_MSB
                0x3C,// 0x0216 IMX222_WINPV_LSB         60
                0x00,// 0x0217 IMX222_WINPV_MSB
                0xC0,// 0x0218 IMX222_WINWH_LSB         1984
                0x07,// 0x0219 IMX222_WINWH_MSB
                0x51,// 0x021A IMX222_WINWV_LSB         1105
                0x04,// 0x021B IMX222_WINWV_MSB
                0xF0,// 0x0220 IMX222_BLC_LSB BLKLEVEL  240
                0x00,// 0x0221 IMX222_BLC_MSB 10BITA
                0x00,// 0x0222 IMX222_XVSLNG  720PMODE
                0x00,// 0x027A IMX222_10BITB
                0x00,// 0x027B IMX222_10BITC
                0x26,// 0x0298 IMX222_10B1080P_LSB      550
                0x02,// 0x0299 IMX222_10B1080P_MSB
                0x26,// 0x029A IMX222_12B1080P_LSB      550
                0x02,// 0x029B IMX222_12B1080P_MSB
                0x16,// 0x02CE IMX222_PRES
                0x82,// 0x02CF IMX222_DRES_LSB          130
                0x00,// 0x02D0 IMX222_DRES_MSB
                0x00,// 0x022C IMX222_XMSTA
                0x30,// 0x0200 IMX222_CONTROL STANDBY
            },
            NULL,//.fps_table = NULL,
            1920,//.width = 1920,
            1080,//.height = 1080,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_12,//.bits = GD_VIDEO_BITS_12,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_25,//.max_fps = GD_VIDEO_FPS_30,
            GD_VIDEO_FPS_25,//.auto_fps = GD_VIDEO_FPS_25,
        },
        //.table[4] = GD_VIDEO_MODE_OFF
        {
            NULL,//.ext_reg_fill = NULL,
            //.data =
            {
                0x0F,// 0x0202 IMX222_MODE
                0x4C,// 0x0203 IMX222_HMAX_LSB
                0x04,// 0x0204 IMX222_HMAX_MSB
                0x65,// 0x0205 IMX222_VMAX_LSB
                0x04,// 0x0206 IMX222_VMAX_MSB
                0x00,// 0x0211 IMX222_FRSEL FRSEL/OPORTS
                0x82,// 0x0212 IMX222_SSBRK ADRES
                0x00,// 0x0214 IMX222_WINPH_LSB
                0x00,// 0x0215 IMX222_WINPH_MSB
                0x3C,// 0x0216 IMX222_WINPV_LSB
                0x00,// 0x0217 IMX222_WINPV_MSB
                0xC0,// 0x0218 IMX222_WINWH_LSB
                0x07,// 0x0219 IMX222_WINWH_MSB
                0x51,// 0x021A IMX222_WINWV_LSB
                0x04,// 0x021B IMX222_WINWV_MSB
                0xF0,// 0x0220 IMX222_BLC_LSB BLKLEVEL
                0x00,// 0x0221 IMX222_BLC_MSB 10BITA
                0x00,// 0x0222 IMX222_XVSLNG  720PMODE
                0x00,// 0x027A IMX222_10BITB
                0x00,// 0x027B IMX222_10BITC
                0x26,// 0x0298 IMX222_10B1080P_LSB
                0x02,// 0x0299 IMX222_10B1080P_MSB
                0x26,// 0x029A IMX222_12B1080P_LSB
                0x02,// 0x029B IMX222_12B1080P_MSB
                0x16,// 0x02CE IMX222_PRES
                0x82,// 0x02CF IMX222_DRES_LSB
                0x00,// 0x02D0 IMX222_DRES_MSB
                0x00,// 0x022C IMX222_XMSTA
                0x30,// 0x0200 IMX222_CONTROL STANDBY
            },
            NULL,//.fps_table = NULL,
            1920,//.width = 1920,
            1080,//.height = 1080,
            GD_VIDEO_FORMAT_PROGRESSIVE,//.format = GD_VIDEO_FORMAT_PROGRESSIVE,
            GD_VIDEO_TYPE_RGB_RAW,//.type = GD_VIDEO_TYPE_RGB_RAW,
            GD_VIDEO_BITS_12,//.bits = GD_VIDEO_BITS_12,
            GD_VIDEO_RATIO_16_9,//.ratio = GD_VIDEO_RATIO_16_9,
            0,//.srm = 0,
            0xFFFFFFFF,//.sw_limit = -1,
            0,//.pll_index = 0,
            GD_VIDEO_FPS_30,//.max_fps = GD_VIDEO_FPS_30,
            GD_VIDEO_FPS_25,//.auto_fps = GD_VIDEO_FPS_25,
        },
        /* add video format table here, if necessary */
    },
};

static GD_SENSOR_REG_S regimx222_dump[] =
{
    {"IMX222_CONTROL"        , IMX222_CONTROL},
    {"IMX222_VREVERSE"       , IMX222_VREVERSE},
    {"IMX222_MODE"           , IMX222_MODE},
    {"IMX222_HMAX_LSB"       , IMX222_HMAX_LSB},
    {"IMX222_HMAX_MSB"       , IMX222_HMAX_MSB},
    {"IMX222_VMAX_LSB"       , IMX222_VMAX_LSB},
    {"IMX222_VMAX_MSB"       , IMX222_VMAX_MSB},
    {"IMX222_REG07"          , IMX222_REG07},
    {"IMX222_SHS1_LSB"       , IMX222_SHS1_LSB},
    {"IMX222_SHS1_MSB"       , IMX222_SHS1_MSB},
    {"IMX222_REG0A"          , IMX222_REG0A},
    {"IMX222_REG0B"          , IMX222_REG0B},
    {"IMX222_REG0C"          , IMX222_REG0C},
    {"IMX222_SPL_LSB"        , IMX222_SPL_LSB},
    {"IMX222_SPL_MSB"        , IMX222_SPL_MSB},
    {"IMX222_SVS_LSB"        , IMX222_SVS_LSB},
    {"IMX222_SVS_MSB"        , IMX222_SVS_MSB},
    {"IMX222_FRSEL"          , IMX222_FRSEL},
    {"IMX222_SSBRK"          , IMX222_SSBRK},
    {"IMX222_REG13"          , IMX222_REG13},
    {"IMX222_WINPH_LSB"      , IMX222_WINPH_LSB},
    {"IMX222_WINPH_MSB"      , IMX222_WINPH_MSB},
    {"IMX222_WINPV_LSB"      , IMX222_WINPV_LSB},
    {"IMX222_WINPV_MSB"      , IMX222_WINPV_MSB},
    {"IMX222_WINWH_LSB"      , IMX222_WINWH_LSB},
    {"IMX222_WINWH_MSB"      , IMX222_WINWH_MSB},
    {"IMX222_WINWV_LSB"      , IMX222_WINWV_LSB},
    {"IMX222_WINWV_MSB"      , IMX222_WINWV_MSB},
    {"IMX222_REG1C"          , IMX222_REG1C},
    {"IMX222_REG1D"          , IMX222_REG1D},
    {"IMX222_REG_GAIN"       , IMX222_REG_GAIN},
    {"IMX222_REG1F"          , IMX222_REG1F},
    {"IMX222_BLC_LSB"        , IMX222_BLC_LSB},
    {"IMX222_BLC_MSB"        , IMX222_BLC_MSB},
    {"IMX222_XVSLNG"         , IMX222_XVSLNG},
    {"0x0225"                , 0x0225},
    {"IMX222_REG27"          , IMX222_REG27},
    {"0x022A"                , 0x022A},
    {"IMX222_XMSTA"          , IMX222_XMSTA},
    {"IMX222_DCKDLY_BITSEL"  , IMX222_DCKDLY_BITSEL},
    {"IMX222_SYSCCODE"       , IMX222_SYSCCODE},
    {"0x025E"                , 0x025E},
    {"0x025F"                , 0x025F},
    {"0x0273"                , 0x0273},
    {"0x0274"                , 0x0274},
    {"0x0276"                , 0x0276},
    {"IMX222_10BITB"         , IMX222_10BITB},
    {"IMX222_10BITC"         , IMX222_10BITC},
    {"IMX222_10B1080P_LSB"   , IMX222_10B1080P_LSB},
    {"IMX222_10B1080P_MSB"   , IMX222_10B1080P_MSB},
    {"IMX222_12B1080P_LSB"   , IMX222_12B1080P_LSB},
    {"IMX222_12B1080P_MSB"   , IMX222_12B1080P_MSB},
    {"0x029D"                , 0x029D},
    {"IMX222_WIN_PIX_ST_LSB" , IMX222_WIN_PIX_ST_LSB},
    {"IMX222_WIN_PIX_ST_MSB" , IMX222_WIN_PIX_ST_MSB},
    {"IMX222_WIN_PIX_END_LSB", IMX222_WIN_PIX_END_LSB},
    {"IMX222_WIN_PIX_END_MSB", IMX222_WIN_PIX_END_MSB},
    {"IMX222_WIN_OB_END"     , IMX222_WIN_OB_END},
    {"IMX222_WIN_OB_ST"      , IMX222_WIN_OB_ST},
    {"IMX222_PRES"           , IMX222_PRES},
    {"IMX222_DRES_LSB"       , IMX222_DRES_LSB},
    {"IMX222_DRES_MSB"       , IMX222_DRES_MSB},
    {"0x02D4"                , 0x02D4},
    {"0x02D6"                , 0x02D6},
    {"0x02D8"                , 0x02D8},
    {"0x02D9"                , 0x02D9},
    {"0x02DB"                , 0x02DB},
    {"0x02DC"                , 0x02DC},
    {"0x02DD"                , 0x02DD},
    {"0x02E0"                , 0x02E0},
};

#if 0
/* This is analog gain table, IMX222_ANALOG_GAIN_ROWS = 61, The step is 0.3dB */
/* For digital gain, the step is 6dB, Max = 18dB */
const u16 IMX222_ANALOG_GAIN_TABLE[IMX222_ANALOG_GAIN_0DB + 1][2] =
{
    {0x037F,    /*18.0dB   */0x3f},
    {0x037B,    /*17.7dB   */0x3f},
    {0x0376,    /*17.4dB   */0x3f},
    {0x0371,    /*17.1dB   */0x3f},
    {0x122C,    /*16.8dB   */0x3f},
    {0x1227,    /*16.5dB   */0x3f},
    {0x1221,    /*16.2dB   */0x3f},
    {0x035C,    /*15.9dB   */0x3f},
    {0x0356,    /*15.6dB   */0x3f},
    {0x0350,    /*15.3dB   */0x3f},
    {0x034A,    /*15.0dB   */0x3f},
    {0x0344,    /*14.7dB   */0x3f},
    {0x033D,    /*14.4dB   */0x3f},
    {0x032F,    /*13.8dB   */0x3f},
    {0x0328,    /*13.5dB   */0x3f},
    {0x0320,    /*13.2dB   */0x3f},
    {0x0318,    /*12.9dB   */0x3f},
    {0x0310,    /*12.6dB   */0x3f},
    {0x0308,    /*12.3dB   */0x3f},
    {0x02FF,    /*12.0dB   */0x3f},
    {0x02F6,    /*11.7dB   */0x3f},
    {0x02EC,    /*11.4dB   */0x3f},
    {0x02E3,    /*11.1dB   */0x3f},
    {0x02D9,    /*10.8dB   */0x3f},
    {0x02CE,    /*10.5dB   */0x3f},
    {0x02C4,    /*10.2dB   */0x3f},
    {0x02B8,    /*9.9dB   */0x3f},
    {0x02AD,    /*9.6dB   */0x3f},
    {0x02A1,    /*9.3dB   */0x3f},
    {0x0295,    /*9.0dB   */0x3f},
    {0x0288,    /*8.7dB   */0x3f},
    {0x027B,    /*8.4dB   */0x3f},
    {0x026D,    /*8.1dB   */0x3f},
    {0x025F,    /*7.8dB   */0x3f},
    {0x0250,    /*7.5dB   */0x3f},
    {0x0241,    /*7.2dB   */0x3f},
    {0x0231,    /*6.9dB   */0x3f},
    {0x0221,    /*6.6dB   */0x3f},
    {0x0210,    /*6.3dB   */0x3f},
    {0x01FF,    /*6.0dB   */0x3f},
    {0x01ED,    /*5.7dB   */0x3f},
    {0x01DA,    /*5.4dB   */0x3f},
    {0x01C7,    /*5.1dB   */0x3f},
    {0x01B3,    /*4.8dB   */0x3f},
    {0x019E,    /*4.5dB   */0x3f},
    {0x0189,    /*4.2dB   */0x3f},
    {0x0172,    /*3.9dB   */0x3f},
    {0x015B,    /*3.6dB   */0x3f},
    {0x0144,    /*3.3dB   */0x3f},
    {0x012B,    /*3.0dB   */0x3f},
    {0x0112,    /*2.7dB   */0x3f},
    {0x00F7,    /*2.4dB   */0x3f},
    {0x00DC,    /*2.1dB   */0x3f},
    {0x00C0,    /*1.8dB   */0x3f},
    {0x00A2,    /*1.5dB   */0x3f},
    {0x0084,    /*1.2dB   */0x3f},
    {0x0065,    /*0.9dB   */0x3f},
    {0x0044,    /*0.6dB   */0x3f},
    {0x0023,    /*0.3dB   */0x3f},
    {0x0000,    /*0.0dB   */0x3f},

    {0x01ED,    /*5.7dB   */0x2a},
    {0x01DA,    /*5.4dB   */0x2a},
    {0x01C7,    /*5.1dB   */0x2a},
    {0x01B3,    /*4.8dB   */0x2a},
    {0x019E,    /*4.5dB   */0x2a},
    {0x0189,    /*4.2dB   */0x2a},
    {0x0172,    /*3.9dB   */0x2a},
    {0x015B,    /*3.6dB   */0x2a},
    {0x0144,    /*3.3dB   */0x2a},
    {0x012B,    /*3.0dB   */0x2a},
    {0x0112,    /*2.7dB   */0x2a},
    {0x00F7,    /*2.4dB   */0x2a},
    {0x00DC,    /*2.1dB   */0x2a},
    {0x00C0,    /*1.8dB   */0x2a},
    {0x00A2,    /*1.5dB   */0x2a},
    {0x0084,    /*1.2dB   */0x2a},
    {0x0065,    /*0.9dB   */0x2a},
    {0x0044,    /*0.6dB   */0x2a},
    {0x0023,    /*0.3dB   */0x2a},
    {0x0000,    /*0.0dB   */0x2a},

    {0x01ED,    /*5.7dB   */0x15},
    {0x01DA,    /*5.4dB   */0x15},
    {0x01C7,    /*5.1dB   */0x15},
    {0x01B3,    /*4.8dB   */0x15},
    {0x019E,    /*4.5dB   */0x15},
    {0x0189,    /*4.2dB   */0x15},
    {0x0172,    /*3.9dB   */0x15},
    {0x015B,    /*3.6dB   */0x15},
    {0x0144,    /*3.3dB   */0x15},
    {0x012B,    /*3.0dB   */0x15},
    {0x0112,    /*2.7dB   */0x15},
    {0x00F7,    /*2.4dB   */0x15},
    {0x00DC,    /*2.1dB   */0x15},
    {0x00C0,    /*1.8dB   */0x15},
    {0x00A2,    /*1.5dB   */0x15},
    {0x0084,    /*1.2dB   */0x15},
    {0x0065,    /*0.9dB   */0x15},
    {0x0044,    /*0.6dB   */0x15},
    {0x0023,    /*0.3dB   */0x15},
    {0x0000,    /*0.0dB   */0x15},

    {0x01ED,    /*5.7dB   */0x00},
    {0x01DA,    /*5.4dB   */0x00},
    {0x01C7,    /*5.1dB   */0x00},
    {0x01B3,    /*4.8dB   */0x00},
    {0x019E,    /*4.5dB   */0x00},
    {0x0189,    /*4.2dB   */0x00},
    {0x0172,    /*3.9dB   */0x00},
    {0x015B,    /*3.6dB   */0x00},
    {0x0144,    /*3.3dB   */0x00},
    {0x012B,    /*3.0dB   */0x00},
    {0x0112,    /*2.7dB   */0x00},
    {0x00F7,    /*2.4dB   */0x00},
    {0x00DC,    /*2.1dB   */0x00},
    {0x00C0,    /*1.8dB   */0x00},
    {0x00A2,    /*1.5dB   */0x00},
    {0x0084,    /*1.2dB   */0x00},
    {0x0065,    /*0.9dB   */0x00},
    {0x0044,    /*0.6dB   */0x00},
    {0x0023,    /*0.3dB   */0x00},
    {0x0000,    /*0.0dB   */0x00},
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
static U8 byte_rev_table[256] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

U8 bitrev8(U8 byte)
{
    return byte_rev_table[byte];
}

static GERR imx222_write_reg( GD_HANDLE* pHandle, U16 subaddr, U8 data)
{
    U8 pbuf[3];
    U32 i;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if (device->handleSPI == NULL)
    {
        return GD_ERR_SPI_NOT_OPEN;
    }

    pbuf[0] = (subaddr >> 0x08) & 0xff;
    pbuf[1] = (subaddr & 0xff);
    pbuf[2] = data;
    //reverse the bit, LSB first
    //GM_Printf("W:0x%04x  0x%02x\n", subaddr, data);
#ifdef SENSOR_DEBUG
    GM_Printf("W:0x%04x  0x%02x\n", subaddr, data);
#endif
    for(i = 0; i < 3; i++)
    {
        pbuf[i] = bitrev8(pbuf[i]);
    }
    GD_SPI_WriteBytes(device->handleSPI, pbuf, 3);
    return GD_OK;
}

static GERR imx222_read_reg( GD_HANDLE* pHandle, U16 subaddr, U8 *pdata)
{
    U8 pbuf[2];
    U8 pbufr[3];
    U32 i;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    if (device->handleSPI == NULL)
    {
        return GD_ERR_SPI_NOT_OPEN;
    }

    pbuf[0] = ((subaddr >> 8) & 0xff) | 0x80;
    pbuf[1] = (subaddr & 0xff);

    //reverse the bit, LSB first
    for(i = 0; i < 2; i++)
    {
        pbuf[i] = bitrev8(pbuf[i]);
    }
    GD_SPI_WriteThenReadBytes(device->handleSPI, pbuf, 2, pbufr, 1);
    *pdata = bitrev8(pbufr[0]);
    //GM_Printf("R:0x%04x  0x%02x\n", subaddr, *pdata);
#ifdef SENSOR_DEBUG
    GM_Printf("R:0x%04x  0x%02x\n", subaddr, *pdata);
#endif
    return GD_OK;
}

static void imx222_dump_reg(GD_HANDLE* pHandle)
{
    U32 nCount,i;
    U8 reg_data;

    nCount = sizeof(regimx222_dump)/sizeof(GD_SENSOR_REG_S);
    GM_Printf("Addr(04x)  Data(02x) name\n");
    for(i=0;i<nCount;i++)
    {
        if(imx222_read_reg(pHandle, regimx222_dump[i].regAddr, &reg_data) == GD_OK)
        {
            GM_Printf("0x%04x  0x%02x  %s\n", regimx222_dump[i].regAddr, reg_data, regimx222_dump[i].name);
        }
        else
        {
            GM_Printf("imx222_read_reg failed!\n");
        }
    }
}

static void imx222_fill_video_format_regs(GD_HANDLE* pHandle)
{
    int i;
    U32 index;
    U32 format_index;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;
    U8            video_mode;    //read from reg200h

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("imx222_fill_video_format_regs \n");
#endif
    index = pinfo->current_video_index;
    format_index = imx222_video_info_table[index].format_index;

    for (i = 0; i < IMX222_VIDEO_FORMAT_REG_NUM; i++)
    {
        if (imx222_video_format_tbl.reg[i] == 0)
            break;

        imx222_write_reg(pHandle,
                  imx222_video_format_tbl.reg[i],
                  imx222_video_format_tbl.table[format_index].data[i]);
    }

    imx222_read_reg(pHandle, IMX222_CONTROL, &video_mode);

    if((video_mode & 0x30) == 0x30)
    {
        // readout 1080pHD
        for(i = 0; i < IMX222_SHARE_1080P_CLASS_REG_SIZE; i ++)
        {
            imx222_write_reg(pHandle, imx222_1080p_class_regs[i].reg, imx222_1080p_class_regs[i].data);
        }
    }
    else
    {
        // readout all pixel
        for(i = 0; i < IMX222_SHARE_3M_CLASS_REG_SIZE; i ++)
        {
            imx222_write_reg(pHandle, imx222_3M_class_regs[i].reg, imx222_3M_class_regs[i].data);
        }
    }

    if (imx222_video_format_tbl.table[format_index].ext_reg_fill)
        imx222_video_format_tbl.table[format_index].ext_reg_fill(pHandle);
}

static void imx222_fill_share_regs(GD_HANDLE* pHandle)
{
    int i;
    for (i = 0; i < IMX222_SHARE_REG_SIZE; i++)
    {
        imx222_write_reg(pHandle, imx222_share_regs[i].reg, imx222_share_regs[i].data);
    }
}

static void imx222_fill_pll_regs(GD_HANDLE* pHandle)
{
    int i;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("imx222_fill_pll_regs\n");
#endif

    for (i = 0; i < IMX222_VIDEO_PLL_REG_TABLE_SIZE; i++)
    {
        imx222_write_reg(pHandle, imx222_pll_tbl[pinfo->pll_index].regs[i].reg,
            imx222_pll_tbl[pinfo->pll_index].regs[i].data);
    }
    GD_SENSOR_Sleep(2);
}

static GERR imx222_sw_reset(GD_HANDLE* pHandle)
{
    //imx222_write_reg(pHandle, IMX222_CONTROL, 0x00);
    GD_SENSOR_Sleep(10);
    return GD_OK;
}

static GERR imx222_reset(GD_HANDLE* pHandle)
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
    return imx222_sw_reset(pHandle);
}

static GERR imx222_get_video_mode(GD_HANDLE* pHandle, GD_VIDEO_MODE_E *p_mode)
{
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_mode = pinfo->current_vin_mode;

    return GD_OK;
}

static GERR imx222_get_video_info(GD_HANDLE* pHandle, GD_SENSOR_VIDEO_INFO_S* p_video_info)
{
    GERR    errCode = GD_OK;
    U32     index;
    U32     format_index;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;

    if (index >= IMX222_VIDEO_INFO_TABLE_SIZE)
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
        format_index = imx222_video_info_table[index].format_index;

        p_video_info->width     = imx222_video_info_table[index].def_width;
        p_video_info->height    = imx222_video_info_table[index].def_height;
        p_video_info->fps       = pinfo->frame_rate;
        p_video_info->format    = imx222_video_format_tbl.table[format_index].format;
        p_video_info->type      = imx222_video_format_tbl.table[format_index].type;
        p_video_info->bits      = imx222_video_format_tbl.table[format_index].bits;
        p_video_info->ratio     = imx222_video_format_tbl.table[format_index].ratio;
        p_video_info->system    = GD_VIDEO_SYSTEM_AUTO;
        p_video_info->rev       = 0;
    }

    return errCode;
}

static GERR imx222_get_agc_info(GD_HANDLE* pHandle, GD_SENSOR_AGC_INFO_S * p_agc_info)
{
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    *p_agc_info = pinfo->agc_info;

    return GD_OK;
}

static GERR imx222_get_shutter_info(GD_HANDLE* pHandle, GD_SENSOR_SHUTTER_INFO_S * pshutter_info)
{
    memset(pshutter_info, 0x00, sizeof(GD_SENSOR_SHUTTER_INFO_S));

    return GD_OK;
}

#if 0
static GERR imx222_check_video_mode(GD_HANDLE* pHandle, gd_vin_source_mode_info* p_mode_info)
{
    GERR errCode = GD_OK;
    int  i;
    U32  index;
    U32  format_index;

    p_mode_info->is_supported = 0;
    memset(p_mode_info->fps_table, 0, p_mode_info->fps_table_size);
    memset(&p_mode_info->video_info, 0, sizeof (p_mode_info->video_info));

    for (i = 0; i < IMX222_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (imx222_video_mode_table[i].mode == p_mode_info->mode)
        {
            if (p_mode_info->mode == GD_VIDEO_MODE_AUTO)
                p_mode_info->mode = IMX222_VIDEO_MODE_TABLE_AUTO;
            p_mode_info->is_supported = 1;

            index = imx222_video_mode_table[i].still_index;
            format_index = imx222_video_info_table[index].format_index;

            p_mode_info->video_info.width   = imx222_video_info_table[index].def_width;
            p_mode_info->video_info.height  = imx222_video_info_table[index].def_height;
            p_mode_info->video_info.fps     = imx222_video_format_tbl.table[format_index].max_fps;
            p_mode_info->video_info.format  = imx222_video_format_tbl.table[format_index].format;
            p_mode_info->video_info.type    = imx222_video_format_tbl.table[format_index].type;
            p_mode_info->video_info.bits    = imx222_video_format_tbl.table[format_index].bits;
            p_mode_info->video_info.ratio   = imx222_video_format_tbl.table[format_index].ratio;
            p_mode_info->video_info.system  = GD_VIDEO_SYSTEM_AUTO;
            p_mode_info->video_info.rev     = 0;

            break;
        }
    }

    return errCode;
}
#endif

static GERR imx222_set_still_mode(GD_HANDLE* pHandle, gd_vin_src_still_info_s *p_info)
{
    return GD_OK;
}

static GERR imx222_set_low_light_agc(GD_HANDLE* pHandle, U32 agc_index)
{
    return GD_OK;
}

static GERR imx222_set_shutter_time(GD_HANDLE* pHandle, U32 shutter_time)
{
    GERR    errCode = 0;
    U64     exposure_time_q9;
    U32     line_length, frame_length_lines;
    int     shutter_width;
    U8      data_l, data_h;

    imx222_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("imx222_set_shutter: 0x%x\n", shutter_time);
#endif

    pll_table = &imx222_pll_tbl[pinfo->pll_index];

    exposure_time_q9 = shutter_time;

    errCode |= imx222_read_reg(pHandle, IMX222_VMAX_MSB, &data_h);
    errCode |= imx222_read_reg(pHandle, IMX222_VMAX_LSB, &data_l);
    frame_length_lines = (data_h<<8) + data_l;
    if(!frame_length_lines)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("frame length lines is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    errCode |= imx222_read_reg(pHandle, IMX222_HMAX_MSB, &data_h);
    errCode |= imx222_read_reg(pHandle, IMX222_HMAX_LSB, &data_l);
    line_length = ((data_h&0x3F)<<8) + data_l;
    if(!line_length)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("line length is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }
    // frame_length_lines = 0x465
    // exposure_time_q9 = 0, 8533333
    // pll_table->extclk = 37125000
    // line_length = 0x44C
    //s:0x00823555  f:0x00000465  l:0x0000044c  e:0x02367b88
    //b:0x00000233  9:0x00000232
    exposure_time_q9 = exposure_time_q9 * (U64)pll_table->extclk;

    //DO_DIV_ROUND(exposure_time_q9, line_length);
    //DO_DIV_ROUND(exposure_time_q9, 512000000);
    exposure_time_q9 = (exposure_time_q9 + line_length/2) / line_length;
    exposure_time_q9 = (exposure_time_q9 + 512000000/2) / 512000000;

    // get the shutter sweep time
    shutter_width = frame_length_lines - (U16)exposure_time_q9;

    // FIXME: shutter width: 0 ~
    if(shutter_width < 0)
    {
        shutter_width = 0;
    }
#ifdef SENSOR_DEBUG
    GM_Printf("frame_length:%d, sweep lines: %d\n", frame_length_lines, shutter_width);
#endif

    errCode |= imx222_write_reg(pHandle, IMX222_SHS1_MSB, (shutter_width >> 8) & 0xff);// SHS1 is for sweep time, should we reverse it for AEC?
    errCode |= imx222_write_reg(pHandle, IMX222_SHS1_LSB, shutter_width & 0xff);

    pinfo->current_shutter_time = shutter_time;
    //G_shutter_time = shutter_time;
    return errCode;
}

static GERR imx222_set_agc_db(GD_HANDLE* pHandle, S32 agc_db)
{
    U16 gain_index;
    S32 db_max;
    S32 db_step;
    GERR errCode = GD_OK;

    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

#ifdef SENSOR_DEBUG
    GM_Printf("imx222_set_agc: 0x%x\n", agc_db);
#endif

    db_max = pinfo->agc_info.db_max;
    db_step = pinfo->agc_info.db_step;
    if (agc_db > db_max)
        agc_db = db_max;

    gain_index = agc_db / db_step;
    errCode = imx222_write_reg(pHandle, IMX222_REG_GAIN, gain_index&0xFF);
    if(errCode == GD_OK)
        pinfo->current_gain_db = agc_db;

    return errCode;
}

static GERR imx222_set_mirror_mode(GD_HANDLE* pHandle, GD_SENSOR_MIRROR_MODE_S *mirror_mode)
{
    GERR    errCode = GD_OK;
    U32     readmode;
    U32        target_bayer_pattern;
    U8      tmp_reg;
    GD_SENSOR_INFO_S*        pinfo;
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
        //break;
    }
    switch (mirror_mode->pattern)
    {
    case GD_VIN_SRC_MIRROR_AUTO:
        return 0;

    case GD_VIN_SRC_MIRROR_VERTICALLY:
        readmode = IMX222_V_FLIP;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_GB;
        break;

    case GD_VIN_SRC_MIRROR_NONE:
        readmode = 0;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_GB;
        break;

    case GD_VIN_SRC_MIRROR_HORRIZONTALLY_VERTICALLY:
        readmode = IMX222_H_MIRROR | IMX222_V_FLIP;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_GB;
        break;

    case GD_VIN_SRC_MIRROR_HORRIZONTALLY:
        readmode = IMX222_H_MIRROR;
        target_bayer_pattern = GD_VIN_SRC_BAYER_PATTERN_GB;
        break;

    default:
#ifdef SENSOR_DEBUG
        GM_Printf("do not support cmd mirror mode\n");
#endif
        return GD_ERR_BAD_PARAMETER;
        //return -EINVAL;
        //break;
    }

    errCode |= imx222_read_reg(pHandle, IMX222_VREVERSE, (U8 *)&tmp_reg);
    tmp_reg &= ~(IMX222_H_MIRROR | IMX222_V_FLIP);
    tmp_reg |= readmode;
    errCode |= imx222_write_reg(pHandle, IMX222_VREVERSE, tmp_reg);

    if (mirror_mode->bayer_pattern == GD_VIN_SRC_BAYER_PATTERN_AUTO)
    {
        pinfo->bayer_pattern = target_bayer_pattern;
    }

    return errCode;
}

static GERR imx222_set_fps(GD_HANDLE* pHandle, U32 fps)
{
    GERR        errCode = GD_OK;
    U32         frame_time = 0;
    U32         index;
    U32         format_index;
    U64         frame_time_pclk;
    int         vertical_lines;
    U32         line_length;
    U32         shs1;
    U32         storage_time;
    U8          data_l, data_h;
    U8          current_pll_index = 0;

    // LindengYu
    //amba_vin_irq_fix vin_irq_fix;
    imx222_pll_reg_table*    pll_table;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    index = pinfo->current_video_index;

    if (index >= IMX222_VIDEO_INFO_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("imx222_set_fps index = %d!\n", index);
#endif
        return GD_ERR_BAD_PARAMETER;//-EPERM;
    }

    // index = 2
    format_index = imx222_video_info_table[index].format_index;
    // format_index = 2

    if (fps == GD_VIDEO_FPS_AUTO)
    {
        fps = imx222_video_format_tbl.table[format_index].auto_fps;
        // fps = GD_VIDEO_FPS_29_97
    }
    if(fps < imx222_video_format_tbl.table[format_index].max_fps)
    {
        // LindengYu
#ifdef SENSOR_DEBUG
        //GM_Printf("The max supported fps is %d\n",
        //    DIV_ROUND(512000000, imx222_video_format_tbl.table[format_index].max_fps));
#endif
        return GD_ERR_BAD_PARAMETER;//-EPERM;
    }

    frame_time = fps;

    /* ToDo: Add specified PLL index*/
    switch(fps)
    {
    case GD_VIDEO_FPS_29_97:
    case GD_VIDEO_FPS_59_94:
        current_pll_index = 1;
        break;
    default:
        current_pll_index = 0;
        break;
    }

    if(pinfo->pll_index != current_pll_index)
    {
        pinfo->pll_index = current_pll_index;
        imx222_fill_pll_regs(pHandle);
        //errCode = imx222_init_vin_clock(pHandle, &imx222_pll_tbl[pinfo->pll_index]);
        //if (errCode != GD_OK)
        //    return errCode;
    }

    pll_table = &imx222_pll_tbl[pinfo->pll_index];

    errCode |= imx222_read_reg(pHandle, IMX222_VMAX_MSB, &data_h);
    errCode |= imx222_read_reg(pHandle, IMX222_VMAX_LSB, &data_l);
    vertical_lines = (data_h<<8) + data_l;
    // vertical_lines = 0x974;
    if(!vertical_lines)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("vertical lines is 0!\n");
#endif
        return GD_ERR_BAD_PARAMETER;//-EIO;
    }

    errCode |= imx222_read_reg(pHandle, IMX222_SHS1_MSB, &data_h);
    errCode |= imx222_read_reg(pHandle, IMX222_SHS1_LSB, &data_l);
    shs1 = (data_h<<8) + data_l;

    storage_time = vertical_lines - shs1;    //FIXME: ignore the toffset

    errCode |= imx222_read_reg(pHandle, IMX222_HMAX_MSB, &data_h);
    errCode |= imx222_read_reg(pHandle, IMX222_HMAX_LSB, &data_l);
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
    //DO_DIV_ROUND(frame_time_pclk, line_length*2);
    //DO_DIV_ROUND(frame_time_pclk, 512000000);
    frame_time_pclk = (frame_time_pclk + line_length) / (line_length*2);
    frame_time_pclk = (frame_time_pclk + 512000000/2) / 512000000;
    // frame_time_pclk = 0x45d

#ifdef SENSOR_DEBUG
    GM_Printf("frame_time %d, line_length 0x%x, vertical_lines 0x%llx\n", frame_time, line_length, frame_time_pclk);
#endif

    vertical_lines = frame_time_pclk;
    shs1 = vertical_lines - storage_time;        //to keep the same shutter time.
    // GD_VIDEO_FPS_AUTO == 0x045D
    errCode |= imx222_write_reg(pHandle, IMX222_VMAX_MSB, (U8)((vertical_lines & 0x00FF00) >>8));
    errCode |= imx222_write_reg(pHandle, IMX222_VMAX_LSB, (U8)(vertical_lines & 0x0000FF));

    errCode |= imx222_write_reg(pHandle, IMX222_SHS1_MSB, (U8)((shs1 & 0x00FF00) >> 8));
    errCode |= imx222_write_reg(pHandle, IMX222_SHS1_LSB, (U8)(shs1 & 0x0000FF));

#ifdef SENSOR_DEBUG
    GM_Printf("set fps change line_length %d, vertical_lines %d, fps = %d \n", line_length, vertical_lines, fps);
#endif

    pinfo->frame_rate = fps;

    //set vblank time
    // LindengYu
    //vin_irq_fix.mode = GD_VIN_VSYNC_IRQ_IDSP;
    //vin_irq_fix.delay = 0;// change to zero for all non Aptina Hi-SPI sensors (for A5s/A7/S2)
    //errCode |= gd_vin_adapter_cmd(pHandle->adapid,
    //    GD_VIN_ADAP_FIX_ARCH_VSYNC, &vin_irq_fix);
    return errCode;
}

static GERR imx222_set_video_index(GD_HANDLE* pHandle, U32 index)
{
    GERR errCode = GD_OK;
    U32 format_index;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    if (index >= IMX222_VIDEO_INFO_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("imx222_set_video_index do not support mode %d!\n", index);
#endif
        return GD_ERR_BAD_PARAMETER;
    }

    // LindengYu
    //errCode |= imx222_pre_set_vin_mode(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;
    pinfo->current_video_index = index;
    format_index            = imx222_video_info_table[index].format_index;

    pinfo->cap_start_x      = imx222_video_info_table[index].def_start_x;
    pinfo->cap_start_y      = imx222_video_info_table[index].def_start_y;
    pinfo->cap_cap_w        = imx222_video_info_table[index].def_width;
    pinfo->cap_cap_h        = imx222_video_info_table[index].def_height;
    pinfo->bayer_pattern    = imx222_video_info_table[index].bayer_pattern;
    //set the specified PLL index for each sensor_mode.
    pinfo->pll_index        = imx222_video_format_tbl.table[format_index].pll_index;
    // LindengYu
    //imx222_print_info(pHandle);

    //set clk_si
    // LindengYu
    //errCode |= imx222_init_vin_clock(pHandle, &imx222_pll_tbl[pinfo->pll_index]);

    //errCode |= imx222_set_vin_mode(pHandle);

    imx222_fill_pll_regs(pHandle);
    imx222_fill_share_regs(pHandle);
    imx222_fill_video_format_regs(pHandle);
    imx222_set_fps(pHandle, GD_VIDEO_FPS_AUTO);

    imx222_set_shutter_time(pHandle, GD_VIDEO_FPS_60);
    imx222_set_agc_db(pHandle, 0);

    // LindengYu
    //errCode |= imx222_set_vin_mode(pHandle);

    // LindengYu
    //errCode |= imx222_post_set_vin_mode(pHandle);

    if (!errCode)
        pinfo->mode_type = GD_VIN_SRC_ENABLED_FOR_VIDEO;

    return errCode;
}

static GERR imx222_set_video_mode(GD_HANDLE* pHandle, GD_VIDEO_MODE_E mode)
{
    GERR errCode = GD_OK;
    int i;
    GD_SENSOR_INFO_S*        pinfo;
    GD_SENSOR_DEVICE_DATA_S* device;

    device  = (GD_SENSOR_DEVICE_DATA_S*)(*pHandle);
    pinfo   = (GD_SENSOR_INFO_S*) device->pinfo;

    //if(mode == GD_VIDEO_MODE_OFF)
    //{
    //    GD_VIN_HW_POWEROFF();
    //    return 0;
    //}
    //else
    //{
    //    GD_VIN_HW_POWERON();
    //}

    /* Hardware Initialization */
    //if (first_set_video_mode)
    //{
        //provide a temporary clk_si for sensor reset at first time called
        //errCode = imx222_init_vin_clock(pHandle, &imx222_pll_tbl[pinfo->pll_index]);
        //first_set_video_mode = 0;
        //if (errCode != GD_OK)
        //    return errCode;
    //}

    imx222_reset(pHandle);

    pinfo->mode_type = GD_VIN_SRC_DISABLED;

    if (mode == GD_VIDEO_MODE_AUTO)
    {
        mode = IMX222_VIDEO_MODE_TABLE_AUTO;
    }

    for (i = 0; i < IMX222_VIDEO_MODE_TABLE_SIZE; i++)
    {
        if (imx222_video_mode_table[i].mode == mode)
        {
            errCode = imx222_set_video_index(pHandle, imx222_video_mode_table[i].preview_index);
            pinfo->mode_index = i;
            break;
        }
    }
    if (i >= IMX222_VIDEO_MODE_TABLE_SIZE)
    {
#ifdef SENSOR_DEBUG
        GM_Printf("imx222_set_video_mode do not support %d, %d!\n", mode, i);
#endif
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
    }

    if (errCode == GD_OK)
    {
        pinfo->current_vin_mode = imx222_video_mode_table[i].mode;
        pinfo->mode_type        = imx222_video_mode_table[i].preview_mode_type;
    }
    return errCode;
}

static GERR imx222_init_hw(GD_HANDLE* pHandle)
{
    GERR    errCode = GD_OK;

    // LindengYu
    //errCode = imx222_init_vin_clock(pHandle, &imx222_pll_tbl[pinfo->pll_index]);
    //if (errCode != GD_OK)
    //    return errCode;
    imx222_reset(pHandle);
    GD_SENSOR_Sleep(10);

    return errCode;
}


//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************
GERR imx222_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args)
{
    GERR errCode = GD_OK;
    GERR gerr;
    GD_SENSOR_INFO_S*        pinfo;
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
        errCode = imx222_reset(pHandle);
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
        errCode = imx222_init_hw(pHandle);
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
            pub_src->sensor_id          = SENSOR_IMX222;
            pub_src->default_mode       = IMX222_VIDEO_MODE_TABLE_AUTO;
            pub_src->total_channel_num  = pHandle->total_channel_num;
            pub_src->active_channel_id  = pHandle->active_channel_id;
            pub_src->source_type.decoder = GD_VIN_CMOS_CHANNEL_TYPE_AUTO;
        }
        break;

    case GD_VIN_SRC_CHECK_VIDEO_MODE:
        errCode = imx222_check_video_mode(pHandle, (amba_vin_source_mode_info *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_INFO:
        errCode = imx222_get_video_info(pHandle, (GD_SENSOR_VIDEO_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_AGC_INFO:
        errCode = imx222_get_agc_info(pHandle, (GD_SENSOR_AGC_INFO_S *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_INFO:
        errCode = imx222_get_shutter_info(pHandle, (GD_SENSOR_SHUTTER_INFO_S *) args);
        break;
#if 0

    case GD_VIN_SRC_GET_CAPABILITY:
        errCode = imx222_get_capability(pHandle, (amba_vin_src_capability *) args);
        break;
#endif

    case GD_VIN_SRC_GET_VIDEO_MODE:
        errCode = imx222_get_video_mode(pHandle, (GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_SET_VIDEO_MODE:
        errCode = imx222_set_video_mode(pHandle, *(GD_VIDEO_MODE_E *) args);
        break;

    case GD_VIN_SRC_GET_STILL_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_STILL_MODE:
        errCode = imx222_set_still_mode(pHandle, (gd_vin_src_still_info_s *) args);
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
        errCode = imx222_set_fps(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_SHUTTER_TIME:
        *(U32 *)args = pinfo->current_shutter_time;
        break;

    case GD_VIN_SRC_SET_SHUTTER_TIME:
        errCode = imx222_set_shutter_time(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_GET_GAIN_DB:
        *(S32 *)args = pinfo->current_gain_db;
        break;

    case GD_VIN_SRC_SET_GAIN_DB:
        errCode = imx222_set_agc_db(pHandle, *(S32 *) args);
        break;

    case GD_VIN_SRC_GET_LOW_LIGHT_MODE:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_SET_LOW_LIGHT_MODE:
        errCode = imx222_set_low_light_agc(pHandle, *(U32 *) args);
        break;

    case GD_VIN_SRC_SET_MIRROR_MODE:
        errCode = imx222_set_mirror_mode(pHandle, (GD_SENSOR_MIRROR_MODE_S *) args);
        break;

    case GD_VIN_SRC_TEST_DUMP_REG:
        imx222_dump_reg(pHandle);
        break;

    case GD_VIN_SRC_TEST_GET_DEV_ID:
        errCode = GD_ERR_FUNC_NOT_SUPPORTED;
        break;

    case GD_VIN_SRC_TEST_GET_REG_DATA:
        {
            GD_SENSOR_REG_DATA_S *reg_data;
            U16 subaddr;
            U8 data;

            reg_data    = (GD_SENSOR_REG_DATA_S*) args;
            subaddr     = reg_data->reg;

            errCode     = imx222_read_reg(pHandle, subaddr, &data);

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

            errCode     = imx222_write_reg(pHandle, subaddr, data);
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


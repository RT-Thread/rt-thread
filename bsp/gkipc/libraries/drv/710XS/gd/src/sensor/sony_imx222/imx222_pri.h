/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/sony_imx222/imx222_pri.h
**
** \version     $Id: imx222_pri.h 323 2014-11-28 07:11:01Z yulindeng $
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************/
#ifndef _IMX222_PRI_H_
#define _IMX222_PRI_H_

#include "gd_sensor.h"
#include "..\sensor_pri.h"




//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
//      NAME            Address     Bit     Symbol      Description                Default value   Reflection timing
#define IMX222_CONTROL          0x0200
                                // bit[0]     STANDBY           Standy 0: Operation 1:Standby       1       immediately
                                // bit[3:1]        b010
                                // bit[5:4] ZPLTD    0:Other than 1080p HD mode 1:1080p HD mode    0  immediately
                                // bit[7:6]        b01
#define IMX222_VREVERSE         0x0201
                                // bit[0]     Vertical readout inversion control 0:Normal    1:Inversed    0  V
                                // bit[3:1]    0
                                // bit[6:4]   0        V
#define IMX222_MODE             0x0202
                                // bit[5:0] MODE[5:0]    Addition readout drive mode
                                // 00h:All pixel scan
                                // 0Fh:HD1080p mode
                                // other: invalid    V
#define IMX222_HMAX_LSB         0x0203  // bit[7:0] HMAX[7:0]  line length setting
#define IMX222_HMAX_MSB         0x0204  // bit[5:0] HMAX[13:8]  line length setting
#define IMX222_VMAX_LSB         0x0205  // VMAX[7:0]
#define IMX222_VMAX_MSB         0x0206  // VMAX[15:8]
#define IMX222_REG07            0x0207  // bit[7:0] 0
#define IMX222_SHS1_LSB         0x0208  // SHS1[7:0]
#define IMX222_SHS1_MSB         0x0209  // SHS1[15:8]
#define IMX222_REG0A            0x020A  // bit[7:0] 0
#define IMX222_REG0B            0x020B  // bit[7:0] 0
#define IMX222_REG0C            0x020C  // bit[7:0] 0
#define IMX222_SPL_LSB          0x020D  // bit[7:0] SPL[7:0]    low speed shutter storage time adjust
#define IMX222_SPL_MSB          0x020E  // bit[1:0] SPL[9:8]    low speed shutter storage time adjust
                                        // bit[7:2] Fix to "00h"
#define IMX222_SVS_LSB          0x020F  // bit[7:0] SVS[7:0]
#define IMX222_SVS_MSB          0x0210  // bit[1:0] SVS[9:8]
                                        // bit[7:2] Fix to "00h"
#define IMX222_FRSEL            0x0211
                                // bit[2:0] FRSEL[2:0] output data rate
                                // bit[4:3] output system
                                // bit[7:5] 0
#define IMX222_SSBRK            0x0212
                                // bit[1] AD gradation setting bits 0:10bit 1:12bit 0
                                // bit[0] SSBRK
#define IMX222_REG13            0x0213  // bit[7:0] 0x40
#define IMX222_WINPH_LSB        0x0214  // bit[7:0] WINPH[7:0]    low speed shutter storage time adjust
#define IMX222_WINPH_MSB        0x0215  // bit[3:0] WINPH[11:8]    low speed shutter storage time adjust
                                        // bit[7:4] Fix to "00h"
#define IMX222_WINPV_LSB        0x0216  // bit[7:0] WINPV[7:0]    low speed shutter storage time adjust
#define IMX222_WINPV_MSB        0x0217  // bit[3:0] WINPV[11:8]    low speed shutter storage time adjust
                                        // bit[7:4] Fix to "00h"
#define IMX222_WINWH_LSB        0x0218  // bit[7:0] WINWH[7:0]    low speed shutter storage time adjust
#define IMX222_WINWH_MSB        0x0219  // bit[3:0] WINWH[11:8]    low speed shutter storage time adjust
                                        // bit[7:4] Fix to "00h"
#define IMX222_WINWV_LSB        0x021A  // bit[7:0] WINWV[7:0]    low speed shutter storage time adjust
#define IMX222_WINWV_MSB        0x021B  // bit[3:0] WINWV[11:8]    low speed shutter storage time adjust
                                        // bit[7:4] Fix to "00h"
#define IMX222_REG1C            0x021C  // bit[7:0] 0x50
#define IMX222_REG1D            0x021D  // bit[7:0] 0x00
#define IMX222_REG_GAIN         0x021E  // bit[7:0] Gain setting
#define IMX222_REG1F            0x021F  // bit[7:0] 0x31
#define IMX222_BLC_LSB          0x0220  // bit[7:0] BLKLEVEL[7:0] black level setting
#define IMX222_BLC_MSB          0x0221  // bit[0] BLKLEVEL[8] black level setting
                                        // bit[5:4] XHSLNG[1:0] 1:6clk 1:12clk 2:22clk 3:128clk
                                        // bit[7] Setting registers for 10bit A
#define IMX222_XVSLNG           0x0222  // bit[2:0] XVSLNG[2:0] 0:1 line 1:2 line 2:4 line 3:8 line others: invalid
                                        // bit[6:3]  Fix to 1000
                                        // bit[7] 720PMODE 1 for 720P mode
// 0x0223~0x0226 do not communicate
#define IMX222_REG27            0x0227  // bit[7:0] 0x20
// 0x0228~0x022B do not communicate
#define IMX222_XMSTA            0x022C  // bit[0] XMSTA[0] 0:master mode operation start 1:trigger standby
                                        // bit[7:1]  Fix to 0x00
#define IMX222_DCKDLY_BITSEL    0x022D  // bit[1] DCKDLY[0] dck phase delay for SDR 0: 0 1: 180; for DDR : 0 1: 90
                                        // bit[3] BITSEL[0] 10 bit output shift 0:Left justified 1:Right justified
                                        // bit[...]  Fix to 0x00
// 0x022E~0x023A do not communicate
#define IMX222_SYSCCODE         0x023B  // sync code setting
// 0x023C~0x0279 do not communicate
#define IMX222_10BITB           0x027A  // Setting registers for 10bit B
#define IMX222_10BITC           0x027B  // Setting registers for 10bit C
// 0x027C~0x0297 do not communicate
#define IMX222_10B1080P_LSB     0x0298  // Adjustment registers for each operation mode
#define IMX222_10B1080P_MSB     0x0299  // bit[3:0] Adjustment registers for each operation mode
                                        // bit[7:4] Fix to 0
#define IMX222_12B1080P_LSB     0x029A  // Adjustment registers for each operation mode
#define IMX222_12B1080P_MSB     0x029B  // bit[3:0] Adjustment registers for each operation mode
                                        // bit[7:4] Fix to 0
// 0x029C~0x02CD do not communicate
#define IMX222_WIN_PIX_ST_LSB   0x02A6
#define IMX222_WIN_PIX_ST_MSB   0x02A7
#define IMX222_WIN_PIX_END_LSB  0x02A8
#define IMX222_WIN_PIX_END_MSB  0x02A9
#define IMX222_WIN_OB_END       0x02A5
#define IMX222_WIN_OB_ST        0x02A4

#define IMX222_PRES             0x02CE  // bit[6:0] Adjustment registers for each operation mode
                                        // bit[7] Fix to 0
#define IMX222_DRES_LSB         0x02CF  // bit[7:0] Adjustment registers for each operation mode
#define IMX222_DRES_MSB         0x02D0  // bit[0] Adjustment registers for each operation mode
                                        // bit[7:1] Fix to 0

#define IMX222_V_FLIP           (1<<0)
#define IMX222_H_MIRROR         (1<<1)

#define IMX222_VIDEO_FORMAT_REG_NUM         (29)
#define IMX222_VIDEO_FORMAT_REG_TABLE_SIZE  (5)
#define IMX222_VIDEO_PLL_REG_TABLE_SIZE     (0)

/* IMX222 global gain table row size */
#define IMX222_GAIN_ROWS        121
#define IMX222_GAIN_COLS        2
#define IMX222_GAIN_DOUBLE      20
#define IMX222_GAIN_0DB         120

#define IMX222_ANALOG_GAIN_0DB  120
#define IMX222_ANALOG_GAIN_18DB 120


//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
/* ========================================================================== */
typedef struct
{
    U16 reg;
    U8 data;
}imx222_reg_table;

typedef struct
{
    U32 pixclk;
    U32 extclk;
    imx222_reg_table regs[IMX222_VIDEO_PLL_REG_TABLE_SIZE+1];
}imx222_pll_reg_table;

typedef struct
{
    U16 reg[IMX222_VIDEO_FORMAT_REG_NUM];
    struct
    {
        void (*ext_reg_fill)(GD_HANDLE* pHandle);
        U8 data[IMX222_VIDEO_FORMAT_REG_NUM];
        void *fps_table;
        U16 width;
        U16 height;
        U8 format;
        U8 type;
        U8 bits;
        U8 ratio;
        U32 srm;
        U32 sw_limit;
        U32 pll_index;
        U32 max_fps;
        U32 auto_fps;
    } table[IMX222_VIDEO_FORMAT_REG_TABLE_SIZE];
}imx222_video_format_reg_table;

typedef struct
{
    U32 format_index;
    U16 def_start_x;
    U16 def_start_y;
    U16 def_width;
    U16 def_height;
    U16 sync_start;
    U8  type_ext;
    U8  bayer_pattern;
}imx222_video_info;


//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif

GERR imx222_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

#ifdef __cplusplus
}
#endif



#endif /* _IMX222_PRI_H_ */


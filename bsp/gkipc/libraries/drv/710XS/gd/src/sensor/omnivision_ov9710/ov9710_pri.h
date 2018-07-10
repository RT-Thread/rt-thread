/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/sensor/omnivision_ov9710/ov9710_pri.h
**
** \version     $Id$
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
#ifndef _OV9710_PRI_H_
#define _OV9710_PRI_H_

#include "gd_sensor.h"
#include "..\sensor_pri.h"




//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
/*
For VGA <-> QVGA, need to modify HOutSize, VOutSize and DSP_Ctrl2
For QVGA <-> QQVGA<->QCIF<->CIF, need to modify HOutSiz, VOutSize
For YCbCr<->RGB565, need to modify COM7
For Raw8 <-> Raw10, need to modify DSP_Ctrl4
*/

/*      Name                Reg#    Description (8-bit content)*/
#define OV9710_GAIN         0x00    /**< AGC gain control
                                        bit[7] Digital gain 0:apply digital only if gain>=2x 1:only if gain >=4x
                                        bit[6:0] Analog gain */
#define OV9710_BLUE         0x01    /**< B channel offset MSBs for AWB */
#define OV9710_RED          0x02    /**< R channel offset MSBs for AWB */
#define OV9710_REG03        0x03    /**< bit[7:5] VAEC ceiling, 000:1frame 010:2frames 011:3frames 1xx:7frames
                                         bit[3:2] sensor vertical output size LSBs
                                         bit[1:0] vstart LSBs */
#define OV9710_REG04        0x04    /**< bit[7] mirror,
                                         bit[6] vertical flip,
                                         bit[0] group latch enable */
#define OV9710_GREEN        0x05    /**< G channel offset MSBs for AWB */
#define OV9710_BRL          0x06    /**< bit[7:4] B, bit[3:0] R channel offset LSBs for AWB */
#define OV9710_GL           0x07    /**< bit[7:4] G channel offset LSBs for AWB */
#define OV9710_REG08        0x08    /**< bit[7:4] H and bit[3:0] V window size offset between sensor output and DSP output */
#define OV9710_COM2         0x09    /**< bit[4] Chip sleep mode. bit[3] Reset sensor timing when mode changes */
#define OV9710_PIDH         0x0A    /**< Product ID MSBS */
#define OV9710_PIDL         0x0B    /**< Product ID LSBs */
#define OV9710_COM3         0x0C    /**< bit[0] Single frame outputs */
#define OV9710_COM4         0x0D    /**< bit[6] Freeze AEC.
                                         bit[5] Initiate BLC calculation manually,
                                         bit[1] Mannual mode for tp level exposure,
                                         bit[0] AEC step control 0: AEC max increasing step less than vertical black, 1: no limit*/
#define OV9710_COM5         0x0E    /**< bit[6] BLC line selection 0: electrical BLC, 1: optical BLC
                                         bit[3] VAEC ON/OFF
                                         bit[0] AEC/AGC algorithm 0: average-based, 1: histogram-based */
#define OV9710_COM6         0x0F    /**< Reserved */
#define OV9710_AEC          0x10    /**< AEC control LSBs */
#define OV9710_CLK          0x11    /**< bit[5:0] clock divider Sysclk = CLK3/((clk[5:0]+1)x2) */
#define OV9710_COM7         0x12    /**< bit[7] SRST 1: initiates soft reset. All regs are set to default values after which the chip resumes normal operation
                                         bit[6] VT2-down sample mode vertical timing
                                         bit[1] Array color bar enable
                                         bit[0] HT2- down sample mode horizontal timing */
#define OV9710_COM8         0x13    /**< bit[7] AEC speed selection 0: normal, 1: faster AEC adjustment
                                         bit[6] AEC step selection
                                         bit[5] Banding filter ON/ OFF
                                         bit[3] LAEC ON/OFF
                                         bit[2] AGC auto/manual control selection
                                         bit[0] Exposure control selection 0: manual, 1: auto */
#define OV9710_COM9         0x14    /**< bit[7:5]: AGC gain ceiling
                                                000: 2x analog gain
                                                001: 4x analog gain
                                                010: 8x analog gain
                                                011: 16x analog gain
                                                100: 16x analog gain plus 2x digital gain
                                         bit[3] Enable AEC below banding value
                                                0: limit the minimus exposure time to 1/100 or 1/120 second under any light conditions when banding filter is enabled
                                                0: allow exposure time to be less than 1/100 or 1/120 second under strong light conditions when banding filter is enabled
                                         bit[1] Enable frame drop function */
#define OV9710_COM10        0x15    /**< bit[7] HSYNC swap 0:HSYNC, 1:HREF
                                         bit[6] HREF pin output swap 0:HREF, 1:HSYNC
                                         bit[3] HREF polarity 0:output positive HREF, 1:output negative HREF for valid data
                                         bit[1] VSYNC polarity 0:positive, 1:negative
                                         bit[0] HSYNC polarity 0:positive, 1:negative */
#define OV9710_AECH         0x16    /**< AEC control MSBs */
#define OV9710_HSTART       0x17    /**< Sensor horizontal output start point MSBs */
#define OV9710_AHSIZE       0x18    /**< Sensor horizontal output size MSBs */
#define OV9710_VSTART       0x19    /**< Sensor vertical output start point MSBs */
#define OV9710_AVSIZE       0x1A    /**< Sensor vertical output size MSBs bit[9:2] */
#define OV9710_PSHIFT       0x1B    /**< Pixel shift */
#define OV9710_MIDH         0x1C    /**< manufacturer ID High */
#define OV9710_MIDL         0x1D    /**< manufacturer ID low */
#define OV9710_COM11        0x1E    /**< Reserved */
#define OV9710_REG1F        0x1F    /**< LSBs for Tp level exposure control when exposure is less than one line */
#define OV9710_COM12        0x20    /**< Reserved */
#define OV9710_COM13        0x21    /**< bit[5:4]  automatically trigger VACE when gain is greater than
                                            00: 2x
                                            01: 4x
                                            10: 8x
                                            11: 16x */
#define OV9710_COM14        0x22    /**< bit[5:0] maximum smooth banding steps in terms of row exposure */
#define OV9710_COM15        0x23    /**< Reserved */
#define OV9710_WPT          0x24    /**< Luma signal high range for AEC/AGC operation */
#define OV9710_BPT          0x25    /**< Luma signal low for AEC/AGC operation */
#define OV9710_VPT          0x26    /**< Fast mode large stop range thresholds - effective only in AEC/AGC fast mode */
#define OV9710_COM16        0x27    /**< Reserved */
#define OV9710_COM17        0x28    /**< Reserved */
#define OV9710_COM18        0x29    /**< Reserved */
#define OV9710_REG2A        0x2A    /**< Horizontal Tp Counter LSBs */
#define OV9710_REG2B        0x2B    /**< Horizontal Tp Counter MSBs */
#define OV9710_COM19        0x2C    /**< Reserved */
#define OV9710_REG2D        0x2D    /**< Dummy lines LSBs */
#define OV9710_REG2E        0x2E    /**< Dummy lines MSBs */
#define OV9710_YAVG         0x2F    /**< Luminance Average Value */
#define OV9710_REG30        0x30    /**< HSYNC start point */
#define OV9710_REG31        0x31    /**< HSYNC stop point */
#define OV9710_REG32        0x32    /**< bit[5:3] sensor horizontal output size length LSBs
                                         bit[2:0] sensor horizontal output start points LSBs */
/* 0x33~0x36 reserved */
#define OV9710_COM24        0x37    /**< bit[3] Trigger BLC manually for 64 frames
                                         bit[2] 0: BLC triggered by gain change, 1: BLC is always ON, meaning BLC offsets are adjusted every frame */
#define OV9710_COM25        0x38    /**< bit[4] AWB_gain write options 0: ISP controls white balance function, 1: manual white balance control */
/* 0x39~0x3B reserved */
#define OV9710_REG39        0x39
#define OV9710_REG3B        0x3B    /**<Reserved */
#define OV9710_COM28        0x3C    /**< MSBs for Tp level exposure control when exposure is less than one line */
#define OV9710_RENDL        0x3D    /**< Row counter end point LSBs */
#define OV9710_RENDH        0x3E    /**< Row counter end point MSBs */
/* 0x3F~0x40 reserved */
#define OV9710_REG41        0x41    /**< bit[7] BLC window enable  bit[3:0] BLC target base */
#define OV9710_REG42        0x42    /**< Reserved */
#define OV9710_REG43        0x43    /**< bit[7:6] BLC line selection
                                            00: not used
                                            01: only selects red line as BLC line
                                            10: only selects blue line as BLC line
                                            11: only selects both blue and red line as BLC line */
#define OV9710_ROFFS        0x44    /**< LSBs for BLC offset of R channel */
#define OV9710_BOFFS        0x45    /**< LSBs for BLC offset of B channel */
#define OV9710_GROFFS       0x46    /**< LSBs for BLC offset of Gr channel */
#define OV9710_GBOFFS       0x47    /**< LSBs for BLC offset of Gb channel */
#define OV9710_HOFFS        0x48    /**< bit[7:6] MSBs for BLC offset of Gb channel
                                         bit[5:4] MSBs for BLC offset of Gr channel
                                         bit[3:2] MSBs for BLC offset of B channel
                                         bit[1:0] MSBs for BLC offset of R channel */
#define OV9710_REG49        0x49    /**< Banding step LSBs */
#define OV9710_REG4A        0x4A    /**< bit[1:0] Banding step MSBs */
#define OV9710_RSVD4B       0x4B    /**< Resvered */
#define OV9710_RSVD4C       0x4C    /**< Resvered */
#define OV9710_RSVD4D       0x4D    /**< Resvered */
#define OV9710_REG4E        0x4E    /**< 16-zone Y averaged select
                                         bit[7:6] Zone 4, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[5:4] Zone 3, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[3:2] Zone 2, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[1:0] Zone 1, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4 */
#define OV9710_REG4F        0x4F    /**< 16-zone Y averaged select
                                         bit[7:6] Zone 8, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[5:4] Zone 7, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[3:2] Zone 6, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[1:0] Zone 5, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4 */
#define OV9710_REG50        0x50    /**< 16-zone Y averaged select
                                         bit[7:6] Zone 12, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[5:4] Zone 11, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[3:2] Zone 10, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[1:0] Zone 09, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4 */
#define OV9710_REG51        0x51    /**< 16-zone Y averaged select
                                         bit[7:6] Zone 16, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[5:4] Zone 15, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[3:2] Zone 14, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4
                                         bit[1:0] Zone 13, 00: not select , 01: weight x 1, 10: weight x 2, 11: weight x 4 */
/* 0x52~0x54 reserved */
#define OV9710_REG55        0x55    /**< data pins in/out control, Y7-Y0 */
#define OV9710_REG56        0x56    /**< bit[4] HREF,
                                         bit[3] VSYNC
                                         bit[2] PCLK
                                         bit[1] Y9
                                         bit[0] Y8 */
#define OV9710_REG57        0x57    /**< bit[4:2] DSP output horizontal size LSBs
                                         bit[1:0] DSP output vertical size LSBs */
#define OV9710_REG58        0x58    /**< DSP output vertical size MSBs */
#define OV9710_REG59        0x59    /**< DSP output horizontal size MSBs */
/* 0x5A~0x5B reserved */
#define OV9710_REG5C        0x5C    /**< bit[6:5] PLL pre-divider 0x: /1, 10: /2, 11: /4
                                         bit[4:0] PLL_d - PLL multiplier CLK2 = CLK1 x (32 - PLL_d) */
#define OV9710_REG5D        0x5D    /**< bit[6] Bypass PLL
                                         bit[5:4] Output drive capability control 00:1x, 01:2x, 10:3x, 11:4x
                                         bit[3:2] PLL_sel - PLLdivider control CLK3 = CLK2/(PLL_sel + 1) */
/* 0x5E~0x71 reserved */
#define OV9710_REG5E        0x5E
#define OV9710_REG5F        0x5F
#define OV9710_REG65        0x65
#define OV9710_REG68        0x68
#define OV9710_REG69        0x69
#define OV9710_REG6D        0x6D

#define OV9710_REG72        0x72    /**< Upper limit of luma level for B pixels */
#define OV9710_REG73        0x73    /**< Lower limit of luma level for W pixels */
#define OV9710_REG74        0x74    /**< Lower limit of probability for B pixels to trigger Auto AEC/AGC. if B pixel probability > REG74, AEC/AGC will increase automatically */
#define OV9710_REG75        0x75    /**< Lower limit of probability for W pixels to trigger Auto AEC/AGC. if W pixel probability > REG75, AEC/AGC will increase automatically */
#define OV9710_REG76        0x76    /**< upper limit of luma level for VB pixels */
#define OV9710_REG77        0x77    /**< lower limit of luma level for VW pixels */
#define OV9710_REG78        0x78    /**< Lower limit of probability for B pixels to trigger fast AEC/AGC. if B pixel probability > REG78, AEC/AGC will increase in fast mode */
#define OV9710_REG79        0x79    /**< Lower limit of probability for W pixels to trigger fast AEC/AGC. if W pixel probability > REG79, AEC/AGC will increase in fast mode */
/* 0x7A~0x95 reserved */
#define OV9710_DSP_CTRL_0   0x96    /**< bit[7]: black_en - enable black pixel removal function.
                                         bit[6]: white_en - enable white pixel removal function.
                                         bit[5]: awbg_en - AWB gain function adjusts image gain according to AWB function result
                                         bit[4]: awb_en - AWB function scans image color temperature and determines how to set white balance
                                         bit[3]: lenc_en -  enable LENC module
                                         bit[2]: lenc_det_en -  enable LENC gain coef module
                                         bit[0]: isp_en -  enable/disable the ISP */
#define OV9710_DSP_CTRL_1   0x97    /**< bit[7]: enable computation of mean value
                                         bit[3]: enable color bar output
                                         bit[2]: enable delay of data HREF/valid clock
                                         bit[1:0]: select type of color bar to output */
#define OV9710_DSP_CTRL_2   0x98    /**< horizontal offset of the pre_win output MSBs */
#define OV9710_DSP_CTRL_3   0x99    /**< vertical offset of the pre_win output MSBs */
#define OV9710_DSP_CTRL_4   0x9A    /**< bit[5:4] vertical offset of the pre_win output LSBs
                                         bit[2:0] horizontal offset of the pre_win output LSBs */
#define OV9710_DSP_CTRL_5   0x9B    /**< bit[7:4] padding the column number in pre_winc
                                         bit[3:0] padding the row number in pre_win */
#define OV9710_DSP_CTRL_6   0x9C    /**< black threshold used in YAVG */
#define OV9710_DSP_CTRL_7   0x9D    /**< white threshold used in YAVG */
#define OV9710_LENC_CTRL_0  0x9E    /**< manual value of the LENC gain coef */
#define OV9710_LENC_CTRL_1  0x9F    /**< lenc_coef_th */
#define OV9710_LENC_CTRL_2  0xA0    /**< bit[7:4] high threshold of the LENC gain MSBs
                                         bit[3:0] low threshold of the LENC gain MSBs */
#define OV9710_LENC_CTRL_3  0xA1    /**< bit[4] manually selects  center of R,G,B circle
                                         bit[3] signal indicating if the result is rounded off
                                         bit[2] enable manual mode of the LENC gain coef
                                         bit[1] high threshold of the LENC gain LSBs
                                         bit[0] low threshold of the LENC gain LSBs */
#define OV9710_LENC_CTRL_4  0xA2    /**< black levlel manual setting for LENC. Range from 0 to 255 */
#define OV9710_LENC_CTRL_5  0xA3    /**< LSBs of horizontal center position in red color channels. It should be fixed as the horizontal position of the image which comes from the midele of the lens, so it is usually set as the horizontal position of the middle pixel of each image. Range from 0 to 1297 */
#define OV9710_LENC_CTRL_6  0xA4    /**< LSBs of vertical center position in red color channels. It should be fixed as the vertical position of the image which comes from the midele of the lens, so it is usually set as the vertical position of the middle pixel of each image. Range from 0 to 800. */
#define OV9710_LENC_CTRL_7  0xA5    /**< bit[5:4] MSBs of vertical center position in red color channels.
                                         bit[2:0] MSBs of horizontal center position in red color channels. */
#define OV9710_LENC_CTRL_8  0xA6    /**< bit[6:0] composed of the first group of factors used in the LENC correction of the red color channels */
#define OV9710_LENC_CTRL_9  0xA7    /**< composed of the second group of factors used in the LENC correction of the red color channels */
#define OV9710_LENC_CTRL_10 0xA8
#define OV9710_LENC_CTRL_11 0xA9
#define OV9710_LENC_CTRL_12 0xAA
#define OV9710_LENC_CTRL_13 0xAB
#define OV9710_LENC_CTRL_14 0xAC
#define OV9710_LENC_CTRL_15 0xAD
#define OV9710_LENC_CTRL_16 0xAE
#define OV9710_LENC_CTRL_17 0xAF
#define OV9710_LENC_CTRL_18 0xB0
#define OV9710_LENC_CTRL_19 0xB1
#define OV9710_LENC_CTRL_20 0xB2
#define OV9710_LENC_CTRL_21 0xB3
#define OV9710_LENC_CTRL_22 0xB4
#define OV9710_LENC_CTRL_23 0xB5
#define OV9710_AWB_CTRL_0   0xB6    /**< bit[3] 0: from sensor_bias, 1: from AWB_off_man
                                         bit[2] AWB in fast mode
                                         bit[1] enable the AWB bias
                                         bit[0] this signal decides if the AWB_bias is added back when the AWB_gain is finished */
#define OV9710_AWB_CTRL_1   0xB7    /**< manual value of the AWB_bias */
#define OV9710_AWB_CTRL_2   0xB8
#define OV9710_AWB_CTRL_3   0xB9
#define OV9710_AWB_CTRL_4   0xBA
#define OV9710_AWB_CTRL_5   0xBB
#define OV9710_WBC_CTRL_0   0xBC
#define OV9710_YAVG_CTRL_0  0xBD
#define OV9710_YAVG_CTRL_1  0xBE
#define OV9710_YAVG_CTRL_2  0xBF
#define OV9710_YAVG_CTRL_3  0xC0
#define OV9710_YAVG_CTRL_4  0xC1
#define OV9710_DVP_CTRL_00  0xC2
#define OV9710_DVP_CTRL_01  0xC3
#define OV9710_DVP_CTRL_02  0xC4
#define OV9710_DVP_CTRL_03  0xC5
#define OV9710_DVP_CTRL_04  0xC6
#define OV9710_DVP_CTRL_05  0xC7
#define OV9710_DVP_CTRL_06  0xC8
#define OV9710_DVP_CTRL_07  0xC9
#define OV9710_DVP_CTRL_08  0xCA
#define OV9710_DVP_CTRL_09  0xCB
#define OV9710_DVP_CTRL_0A  0xCC
#define OV9710_DVP_CTRL_0B  0xCD
#define OV9710_DVP_CTRL_0C  0xCE
#define OV9710_DVP_CTRL_0D  0xCF
#define OV9710_DVP_CTRL_0E  0xD0
#define OV9710_DVP_CTRL_0F  0xD1
#define OV9710_DVP_CTRL_10  0xD2
#define OV9710_DVP_CTRL_11  0xD3
#define OV9710_DVP_CTRL_12  0xD4
/* 0xD5 resever */
#define OV9710_SC_CTRL_0    0xD6
/* 0xD7~0xFF resever */



/* Chip versions */
#define OV9710_CHIP_VER_PART_ID        0x18

/** Window control */
#define OV9710_HORI             0    /**< Column-wise */
#define OV9710_VERT             1    /**< Row-wise */


/** Configuration of the STROBE signal at the snapshot modes */
/* STROBE signal phases */
#define STROBE_NORM_HIGH                        1
#define STROBE_NORM_LOW                         0

/* Timepoints of the starting and ending */
#define STROBE_FIRST_TRIGGER                    0
#define STROBE_SIMULTANEOUS_EXPOSURE            1
#define STROBE_SHUTTER_WIDTH                    2
#define STROBE_SECOND_TRIGGER                   3

/** Configuration of the row and column readout mode */
#define READOUT_NORMAL                          0
#define READOUT_MIRROR                          1

#if defined (USE_32_STEP_GAIN_TABLE)
#define OV9710_GAIN_ROWS        256
#define OV9710_GAIN_COLS        3
#define OV9710_GAIN_DOUBLE      32
#define OV9710_GAIN_0DB         224
#else
#define OV9710_GAIN_ROWS        81
#define OV9710_GAIN_COLS        3
#define OV9710_GAIN_DOUBLE      16
#define OV9710_GAIN_0DB         80
#endif /* defined (USE_32_STEP_GAIN_TABLE) */

#define OV9710_GAIN_COL_AGC    0
#define OV9710_GAIN_COL_FAGC   1
#define OV9710_GAIN_COL_REG    2


/** OV9710 CMOS sensor clock    */
#define OV9710_SENSOR_CLK               96      /* MHz */
#define OV9710_CLKIN                    27      /* MHz */

#define OV9710_VIDEO_PLL_REG_TABLE_SIZE (3)

/** OV9710 mirror mode*/
#define OV9710_REG4_MIRROR_ROW          (0x01 << 7)
#define OV9710_REG4_MIRROR_COLUMN       (0x01 << 6)
#define OV9710_MIRROR_MASK              (OV9710_REG4_MIRROR_ROW + OV9710_REG4_MIRROR_COLUMN)

#define OV9710_VIN_MAX_FPS_TABLE_SIZE   (256)

#define OV9710_CHIP_ENABLE              (0x01 << 1)
#define OV9710_SYNCHRONIZE_CHANGES      (0x01 << 0)

#define OV9710_USE_PLL_REG_BIT          (0x01 << 1)
#define OV9710_POWER_PLL_REG_BIT        (0x01 << 0)

#define OV9710_TRIGGER                  (0x01 << 2)
#define OV9710_PAUSE_RESTART            (0x01 << 1)
#define OV9710_RESTART_FRAME            (0x01 << 0)

#define OV9710_INVERT_TRIGGER           (0x01 << 9)
#define OV9710_SNAPSHOT                 (0x01 << 8)
#define OV9710_GLOBAL_RESET             (0x01 << 7)
#define OV9710_BULB_EXPOSURE            (0x01 << 6)
#define OV9710_STROBE_ENABLE            (0x01 << 4)

#define OV9710_VIDEO_FPS_REG_NUM            (6)
#define OV9710_VIDEO_FORMAT_REG_NUM         (22)
#define OV9710_VIDEO_FORMAT_REG_TABLE_SIZE  (16)



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
    U8 reg;
    U8 data;
}ov9710_reg_table;

typedef struct
{
    U32 pixclk;
    U32 extclk;
    ov9710_reg_table regs[OV9710_VIDEO_PLL_REG_TABLE_SIZE];
}ov9710_pll_reg_table;

typedef struct
{
    U16 reg[OV9710_VIDEO_FPS_REG_NUM];
    struct
    {
        ov9710_pll_reg_table *pll_reg_table;
        U32     fps;
        U8      system;
        U16     data[OV9710_VIDEO_FPS_REG_NUM];
    } table[OV9710_VIN_MAX_FPS_TABLE_SIZE];
}ov9710_video_fps_reg_table;

typedef struct
{
    U16     reg[OV9710_VIDEO_FORMAT_REG_NUM];
    struct
    {
        void (*ext_reg_fill)(GD_HANDLE* pHandle);
        U8      data[OV9710_VIDEO_FORMAT_REG_NUM];
        ov9710_video_fps_reg_table *fps_table;
        U16     width;
        U16     height;
        U8      format;
        U8      type;
        U8      bits;
        U8      ratio;
        U32     srm;
        U32     sw_limit;
        U32     pll_index;
        U32     max_fps;
    } table[OV9710_VIDEO_FORMAT_REG_TABLE_SIZE];
}ov9710_video_format_reg_table;

typedef struct
{
    U32     format_index;
    U16     def_start_x;
    U16     def_start_y;
    U16     def_width;
    U16     def_height;
    U16     sync_start;
    U8      bayer_pattern;
}ov9710_video_info;


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

GERR ov9710_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

#ifdef __cplusplus
}
#endif



#endif /* _OV9710_PRI_H_ */


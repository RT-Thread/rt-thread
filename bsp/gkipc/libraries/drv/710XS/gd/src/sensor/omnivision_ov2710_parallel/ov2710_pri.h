/*
 * Filename : ov2710_pri.h
 *
 * History:
 *    2009/06/19 - [Qiao Wang] Create
 *
 * Copyright (C) 2004-2009, Ambarella, Inc.
 *
 * All rights reserved. No Part of this file may be reproduced, stored
 * in a retrieval system, or transmitted, in any form, or by any means,
 * electronic, mechanical, photocopying, recording, or otherwise,
 * without the prior consent of Ambarella, Inc.
 *
 * This file is produced by perl.
 */
#ifndef _OV2710_PRI_H_
#define _OV2710_PRI_H_

#include "gd_sensor.h"
#include "..\sensor_pri.h"

//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
/*         register name            address  default value  R/W  description  */
#define OV2710_SYSTEM_CONTROL00     0x3008      /*0x02 RW System Control*/
                                                /* Bit[7]:System software reset 0:Normal work mode 1:Software reset mode*/
                                                /* Bit[6]:System sleep mode 0:Normal work mode 1:Software sleep power down mode*/
                                                /* Bit[4]:MIPI high speed power down control 0:Not used 1:Power down MIPI PHY LP RX module*/
                                                /* Bit[2]:MIPI enable 0:DVP enable 1:MIPI enable*/
                                                /* Bit[1]:MIPI system suspend control 0:Not used 1:MIPI suspend*/
                                                /* Bit[0]:Not used*/
#define OV2710_PIDH                 0x300A      /*0x27 R Product ID High Byte MSBs*/
#define OV2710_PIDL                 0x300B      /*0x10 R Product ID Low Byte LSBs*/
#define OV2710_MIPI_CTRL00          0x300E      /*0x00 RW*/
                                                /* Bit[7:5]: Not used*/
                                                /* Bit[4]: MIPI high speed power down control 0: 1: power down mipi phy HS TX module*/
                                                /* Bit[3]:MIPI low power, power-down control 0:Enable MIPI PHY HS RX module 1:Power down MIPI PHY LP RX module*/
                                                /* Bit[2]:MIPI enable 0:DVP enable 1:MIPI enable*/
                                                /* Bit[1]:MIPI system suspend control 0:MIPI power ON 1:MIPI suspend*/
#define OV2710_PLL_CTRL00           0x300F      /*0x8A RW*/
                                                /* Bit[7:6]: Not used*/
                                                /* Bit[5:3]: Charge pump control*/
                                                /* Bit[2]:Not used*/
                                                /* Bit[1:0]: PLL SELD5 divider*/
                                                /* 0x: Bypass*/
                                                /* 10: Divided by 4 when in 8-bit mode*/
                                                /* 11: Divided by 5 when in 10-bit mode*/
#define OV2710_PLL_CTRL01           0x3010      /*0x00 RW*/
                                                /* Bit[7:4]: PLL DIVS divider System divider ratio*/
                                                /* Bit[3:0]: PLL DIVM divider MIPI divider ratio*/
#define OV2710_PLL_CTRL02           0x3011      /*0x0A RW*/
                                                /* Bit[7]:PLL bypass*/
                                                /* Bit[5:0]: PLL DIVP*/
#define OV2710_PLL_PREDIVEDER       0x3012      /*0x00 RW*/
                                                /* Bit[7:3]: Not used*/
                                                /* Bit[2:0]: PLL1 pre-divider ratio 000: 1 001: 1.5 010: 2 011: 2.5 100: 3 101: 4 110: 6 111: 8*/
#define OV2710_PAD_OUTPUT_ENABLE00  0x3016      /*0x00 RW Input/Output Control (0: input; 1: output)*/
                                                /* Bit[7:2]: Not used*/
                                                /* Bit[1]:Strobe OEN*/
                                                /* Bit[0]:SDA OEN*/
#define OV2710_PAD_OUTPUT_ENABLE01  0x3017      /*0x00 RW Input/Output Control (0: input; 1: output)*/
                                                /* Bit[7]:Not used*/
                                                /* Bit[6]:VSYNC OEN*/
                                                /* Bit[5]:HREF OEN*/
                                                /* Bit[4]:PCLK OEN*/
                                                /* Bit[3:0]: D OEN[9:6]*/
#define OV2710_PAD_OUTPUT_ENABLE02  0x3018      /*0x00 RW Input/Output Control (0: input; 1: output) Bit[7:2] D OEN[5:0]*/
#define OV2710_PAD_OUTPUT_VALUE00   0x3019      /*0x00  RW GPIO Output Value*/
                                                /* Bit[7:2]: Not used*/
                                                /* Bit[1]:Strobe*/
                                                /* Bit[0]:SDA*/
#define OV2710_PAD_OUTPUT_VALUE01   0x301A      /*0x00 RW GPIO Output Value*/
                                                /* Bit[7]:Not used*/
                                                /* Bit[6]:VSYNC*/
                                                /* Bit[5]:HREF*/
                                                /* Bit[4]:PCLK*/
                                                /* Bit[3:0]: D output[9:6]*/
#define OV2710_PAD_OUTPUT_VALUE02   0x301B      /*0x00 RW GPIO Output Value*/
                                                /* Bit[7:2]: D output[5:0]*/
                                                /* Bit[1:0]: Not used*/
#define OV2710_PAD_OUTPUT_SELECT00  0x301C      /*0x00 RW Output Selection for GPIO (0: normal data path, 1: register controlled GPIO)*/
                                                /* Bit[7:2]: Not used*/
                                                /* Bit[1]:Strobe select*/
                                                /* Bit[0]:SDA select*/
#define OV2710_PAD_OUTPUT_SELECT01  0x301D      /*0x00 RW Output Selection for GPIO (0: normal data path, 1: register controlled GPIO)*/
                                                /* Bit[7]:Not used*/
                                                /* Bit[6]:VSYNC select*/
                                                /* Bit[5]:HREF select*/
                                                /* Bit[4]:PCLK select*/
                                                /* Bit[3:0]: D select[9:6]*/
#define OV2710_PAD_OUTPUT_SELECT02  0x301E      /*0x00 RW Output Selection for GPIO (0: normal data path, 1: register controlled GPIO)*/
                                                /* Bit[7:2]: D select[5:0]*/
                                                /* Bit[1:0]: Not used*/
#define OV2710_PAD_OUTPUT_DRIVE_CAPABILITY  0x302C  /*0x02 RW Bit[7:6]: Output drive capability 00: 1x 01: 2x 10: 3x 11: 4x*/
#define OV2710_PAD_INPUT_VALUE00    0x3040      /* R Pad Input Status*/
                                                /* Bit[7:6]: Not used*/
                                                /* Bit[5]:TM*/
                                                /* Bit[4]:Not used*/
                                                /* Bit[3]:PWDN*/
                                                /* Bit[2]:PWUP*/
                                                /* Bit[1]:SCL*/
                                                /* Bit[0]:SDA*/
#define OV2710_PAD_INPUT_VALUE01    0x3041      /* R Pad Input Status*/
                                                /* Bit[7]:OTP*/
                                                /* Bit[6]:VSYNC*/
                                                /* Bit[5]:HREF*/
                                                /* BIt[4]:PCLK*/
                                                /* Bit[3:0]: D input[9:6]*/
#define OV2710_PAD_INPUT_VALUE02    0x3042      /* R Pad Input Status*/
                                                /* Bit[7:2]: D input[5:0]*/
                                                /* Bit[1:0]: Not used*/
#define OV2710_SCCB_ID              0x3100      /*0x6C RW SCCB Slave ID*/
#define OV2710_PLL_CLOCK_SELECT     0x3103      /*0x01 RW*/
                                                /* Bit[7:2]: Not used*/
                                                /* Bit[1]:Select PLL input clock*/
                                                /* 0:From pad clock*/
                                                /* 1:From pre divider (clock modulator)*/
#define OV2710_SCCB_PAD_CLOCK_DIVIDER   0x3104  /*0x01 RW Pad Clock Divider for SCCB Clock*/
#define OV2710_GROUP_ADDR0          0x3200      /*0x40 RW Start Address for Group0 {group_addr0[7:0], 4¡¯h0}*/
#define OV2710_GROUP_ADDR1          0x3201      /*0x4A RW Start Address for Group1 {group_addr1[7:0], 4¡¯h0}*/
#define OV2710_GROUP_ADDR2          0x3202      /*0x54 RW Start Address for Group2 {group_addr2[7:0], 4¡¯h0}*/
#define OV2710_GROUP_ADDR3          0x3203      /*0x5E RW Start Address for Group3 {group_addr3[7:0], 4¡¯h0}*/
#define OV2710_GROUP_ACCESS         0x3212      /*0x00 RW*/
                                                /* Bit[7]: group_launch_en*/
                                                /* Bit[6]: Debug mode(must be 0)*/
                                                /* Bit[5]: group_launch*/
                                                /* Bit[4]: group_hold_end*/
                                                /* Bit[3:0]: group_id 00~11: ID of the group to hold register*/
#define OV2710_AWB_GAIN_PK_RED_GAIN_H   0x3400  /*0x04 RW Bit[7:4]: Not used Bit[3:0]: AWB R GAIN[11:8]*/
#define OV2710_AWB_GAIN_PK_RED_GAIN_L   0x3401  /*0x00 RW Bit[7:0]: AWB R GAIN[7:0]*/
#define OV2710_AWB_GAIN_PK_GREEN_GAIN_H 0x3402  /*0x04 RW Bit[7:4]: Not used Bit[3:0]: AWB G GAIN[11:8]*/
#define OV2710_AWB_GAIN_PK_GREEN_GAIN_L 0x3403  /*0x00 RW Bit[7:0]: AWB G GAIN[7:0]*/
#define OV2710_AWB_GAIN_PK_BLUE_GAIN_H  0x3404  /*0x04 RW Bit[7:4]: Not used Bit[3:0]: AWB B GAIN[11:8] */
#define OV2710_AWB_GAIN_PK_BLUE_GAIN_L  0x3405  /*0x00 RW Bit[7:0]: AWB B GAIN[7:0]*/
#define OV2710_AWB_GAIN_PK_AWB_MAN_CTRL 0x3406  /*0x00 RW Bit[0]: AWB manual control 0: automatically 1: manual*/
#define OV2710_AEC_PK_EXPO_H    0x3500          /*0x00 RW Bit[7:4]: Not used Bit[3:0]: AEC exposure[19:16]*/
#define OV2710_AEC_PK_EXPO_M    0x3501          /*0x00 RW Bit[7:0]: AEC exposure[15:8]*/
#define OV2710_AEC_PK_EXPO_L    0x3502          /*0x20 RW Bit[7:0]: AEC exposure[7:0]*/
#define OV2710_AEC_PK_MANUAL    0x3503          /*0x00 RW*/
                                                /* Bit[7:4]: Not used*/
                                                /* Bit[2]:VTS manual enable*/
                                                /* Bit[1]:AGC manual enable*/
                                                /* Bit[0]:AEC manual enable*/
#define OV2710_AEC_AGC_ADJ_H    0x350A          /*0x00 RW Gain Output to Sensor*/
                                                /* Bit[7:1]: Not used*/
                                                /* Bit[0]:Gain high bit*/
                                                /* Gain = (0x350A[0]+1) ¡Á (0x350B[7]+1) ¡Á (0x350B[6]+1)¡Á(0x350B[5]+1) ¡Á (0x350B[4]+1)¡Á(0x350B[3:0]/16+1)*/
#define OV2710_AEC_AGC_ADJ_L    0x350B          /*0x00 RW Gain Output to Sensor*/
                                                /* Bit[7:0]: Gain low bits*/
                                                /* Gain = (0x350A[0]+1) ¡Á (0x350B[7]+1) ¡Á (0x350B[6]+1)¡Á(0x350B[5]+1) ¡Á (0x350B[4]+1)¡Á(0x350B[3:0]/16+1)*/
#define OV2710_AEC_PK_VTS_H     0x350C          /*0x00 RW Bit[7:0]: AEC VTS[15:8]*/
#define OV2710_AEC_PK_VTS_L     0x350D          /*0x00 RW Bit[7:0]: AEC VTS[7:0]*/
#define OV2710_ANA_ARRAY_01     0x3621          /*0x10 RW Array Control Bit[7]:Horizontal binning Bit[6]:Horizontal skip*/
#define OV2710_SENSOR_REG0D     0x370D          /*0x0C RW*/
                                                /* Bit[7]:Debug mode*/
                                                /* Bit[6]:Vertical binning*/
                                                /* Bit[5:0]: Debug mode*/
#define OV2710_TIMING_CONTROL_HS_HIGHBYTE       0x3800      /*0x01 RW Bit[3:0]: HREF horizontal start point[11:8]*/
#define OV2710_TIMING_CONTROL_HS_LOWBYTE        0x3801      /*0x08 RW Bit[7:0]: HREF horizontal start point[7:0]*/
#define OV2710_TIMING_CONTROL_VS_HIGHBYTE       0x3802      /*0x00 RW Bit[3:0]: HREF vertical start point[11:8]*/
#define OV2710_TIMING_CONTROL_VS_LOWBYTE        0x3803      /*0x0A RW Bit[7:0]: HREF vertical start point[7:0]*/
#define OV2710_TIMING_CONTROL_HW_HIGH_BYTE      0x3804      /*0x08 RW Bit[3:0]: HREF horizontal width[11:8]*/
#define OV2710_TIMING_CONTROL_HW_LOW_BYTE       0x3805      /*0x00 RW Bit[7:0]: HREF horizontal width[7:0]*/
#define OV2710_TIMING_CONTROL_VW_HIGH_BYTE      0x3806      /*0x06 RW Bit[3:0]: HREF vertical height[11:8]*/
#define OV2710_TIMING_CONTROL_VW_LOW_BYTE       0x3807      /*0x00 RW Bit[7:0]: HREF vertical height[7:0]*/
#define OV2710_TIMING_CONTROL_DVP_HSIZE_HIGH    0x3808      /*0x08 RW Bit[3:0]: DVP output horizontal*/
#define OV2710_TIMING_CONTROL_DVP_HSIZE_LOW     0x3809      /*0x00 RW Bit[7:0]: DVP output horizontal*/
#define OV2710_TIMING_CONTROL_DVP_VSIZE_HIGH    0x380A      /*0x06 RW Bit[3:0]: DVP output vertical height[11:8]*/
#define OV2710_TIMING_CONTROL_DVP_VSIZE_LOW     0x380B      /*0x00 RW Bit[7:0]: DVP output vertical height[7:0]*/
#define OV2710_TIMING_CONTROL_HTS_HIGHBYTE      0x380C      /*0x09 RW Bit[3:0]: Total horizontal size[11:8]*/
#define OV2710_TIMING_CONTROL_HTS_LOWBYTE       0x380D      /*0x48 RW Bit[7:0]: Total horizontal size[7:0]*/
#define OV2710_TIMING_CONTROL_VTS_HIGHBYTE      0x380E      /*0x06 RW Bit[3:0]: Total vertical size[11:8]*/
#define OV2710_TIMING_CONTROL_VTS_LOWBYTE       0x380F      /*0x18 RW Bit[7:0]: Total vertical size[7:0]*/
#define OV2710_TIMING_CONTROL_HV_OFFSET         0x3810      /*0xC2 RW Bit[7:4]: Horizontal offset Bit[3:0]: Vertical offset*/
#define OV2710_TIMING_CONTROL18                 0x3818      /*0x80 RW*/
                                                            /* Bit[7]:Not used*/
                                                            /* Bit[6]:Horizontal mirror*/
                                                            /* Bit[5]:Vertical flip*/
                                                            /* Bit[4:2]: Not used*/
                                                            /* Bit[1]:Vertical subsample /4*/
                                                            /* Bit[0]:Vertical subsample /2*/
#define OV2710_AEC_CONTROL0     0x3A00          /*0x7C RW*/
                                                /* Bit[7]:Not used*/
                                                /* Bit[6]:Less 1 line enable 0:Less 1 line function disable 1:Less 1 line function enable*/
                                                /* Bit[5]:Band enable 0:Band function disable 1:Band function enable*/
                                                /* Bit[4]:Auto band enable 0:Exposure can not be less than 1 band 1:Exposure can be less than 1 band*/
                                                /* Bit[3]:Line complete 0:Fractional line enable*/
                                                /* Bit[1]:Not used*/
                                                /* Bit[0]:Freeze 0:Freeze disable 1:Freeze enable*/
#define OV2710_AEC_CONTROL1         0x3A01      /*0x04 RW Bit[7:0]: Minimum exposure*/
#define OV2710_AEC_MAX_EXPO_60_H    0x3A02      /*0x02 RW Bit[3:0]: AEC maximum exposure for 60Hz[19:16]*/
#define OV2710_AEC_MAX_EXPO_60_M    0x3A03      /*0x28 RW Bit[7:0]: AEC maximum exposure for 60Hz[15:8]*/
#define OV2710_AEC_MAX_EXPO_60_L    0x3A04      /*0x00 RW Bit[7:0]: AEC maximum exposure for 60Hz[7:0]*/
#define OV2710_AEC_B50_STEP_H       0x3A08      /*0x11 RW Bit[5:0]: AEC Band50 step[13:8]*/
#define OV2710_AEC_B50_STEP_L       0x3A09      /*0x40 RW Bit[7:0]: AEC Band50 step[7:0]*/
#define OV2710_AEC_B60_STEP_H       0x3A0A      /*0x11 RW Bit[5:0]: AEC Band60 step[13:8]*/
#define OV2710_AEC_B60_STEP_L       0x3A0B      /*0x40 RW Bit[7:0]: AEC Band60 step[7:0]*/
#define OV2710_AEC_CONTROLD         0x3A0D      /*0x04 RW Bit[5:0]: Band60 max[5:0]*/
#define OV2710_AEC_CONTROLE         0x3A0E      /*0x03 RW Bit[5:0]: Band50 max[5:0]*/
#define OV2710_AEC_CONTROLF         0x3A0F      /*0x78 RW Bit[7:0]: Stable range high threshold 1*/
#define OV2710_AEC_CONTROL10        0x3A10      /*0x68 RW Bit[7:0]: Stable range low threshold 1*/
#define OV2710_AEC_CONTROL11        0x3A11      /*0xD0 RW Bit[7:0]: Fast zone high threshold*/
#define OV2710_AEC_CONTROL12        0x3A12      /*0x00 RW Bit[7:0]: Manual average setting*/
#define OV2710_AEC_CONTROL13        0x3A13      /*0x50 RW Bit[7:6]: Not used Bit[5]:Pre gain enable Bit[4:0]: Pre gain*/
#define OV2710_AEC_MAX_EXPO_50_H    0x3A14      /*0x02 RW Bit[3:0]: AEC maximum exposure for 50Hz[19:16]*/
#define OV2710_AEC_MAX_EXPO_50_M    0x3A15      /*0x28 RW Bit[7:0]: AEC maximum exposure for 50Hz[15:8]*/
#define OV2710_AEC_MAX_EXPO_50_L    0x3A16      /*0x00 RW Bit[7:0]: AEC maximum exposure for 50Hz[7:0]*/
#define OV2710_AEC_CONTROL17        0x3A17      /*0x89 RW */
                                                /* Bit[1:0]: Gain night threshold[1:0]*/
                                                /* 00: Night mode gain threshold as 1x*/
                                                /* 01: Night mode gain threshold as 2x*/
                                                /* 10: Night mode gain threshold as 4x*/
                                                /* 11: Not used*/
#define OV2710_AEC_G_CEIL_H         0x3A18      /*0x03 RW Bit[0]:AEC gain ceiling*/
#define OV2710_AEC_G_CEIL_L         0x3A19      /*0xE0 RW Bit[7:0]: AEC gain ceiling*/
#define OV2710_AEC_CONTROL1B        0x3A1B      /*0x78 RW Bit[7:0]: Stable range high threshold 2*/
#define OV2710_AEC_LED_ADD_ROW_H    0x3A1C      /*0x06 RW Bit[7:0]: Row adding number[15:8] in AEC LED mode*/
#define OV2710_AEC_LED_ADD_ROW_L    0x3A1D      /*0x18 RW Bit[7:0]: Row adding number[7:0] in AEC LED mode*/
#define OV2710_AEC_CONTROL1E        0x3A1E      /*0x68 RW Bit[7:0]: Stable range low threshold 2*/
#define OV2710_AEC_CONTROL1F        0x3A1F      /*0x40 RW Bit[7:0]: Fast zone low threshold*/
#define OV2710_AEC_CONTROL20        0x3A20      /*0x20 RW*/
                                                /* Bit[7:3]: Not used*/
                                                /* Bit[2]:Strobe option*/
                                                /* Bit[1]:Manual average enable 0:Average data manual set disable 1:Average data manual set enable*/
                                                /* Bit[0]:Not used*/
#define OV2710_OTP_DATA_0       0x3D00          /*0x00 RW OTP Dump/Load Data 0*/
#define OV2710_OTP_DATA_1       0x3D01          /*0x00 RW OTP Dump/Load Data 1*/
#define OV2710_OTP_DATA_2       0x3D02          /*0x00 RW OTP Dump/Load Data 2*/
#define OV2710_OTP_DATA_3       0x3D03          /*0x00 RW OTP Dump/Load Data 3*/
#define OV2710_OTP_DATA_4       0x3D04          /*0x00 RW OTP Dump/Load Data 4*/
#define OV2710_OTP_DATA_5       0x3D05          /*0x00 RW OTP Dump/Load Data 5*/
#define OV2710_OTP_DATA_6       0x3D06          /*0x00 RW OTP Dump/Load Data 6*/
#define OV2710_OTP_DATA_7       0x3D07          /*0x00 RW OTP Dump/Load Data 7*/
#define OV2710_OTP_DATA_8       0x3D08          /*0x00 RW OTP Dump/Load Data 8*/
#define OV2710_OTP_DATA_9       0x3D09          /*0x00 RW OTP Dump/Load Data 9*/
#define OV2710_OTP_DATA_A       0x3D0A          /*0x00 RW OTP Dump/Load Data A*/
#define OV2710_OTP_DATA_B       0x3D0B          /*0x00 RW OTP Dump/Load Data B*/
#define OV2710_OTP_DATA_C       0x3D0C          /*0x00 RW OTP Dump/Load Data C*/
#define OV2710_OTP_DATA_D       0x3D0D          /*0x00 RW OTP Dump/Load Data D*/
#define OV2710_OTP_DATA_E       0x3D0E          /*0x00 RW OTP Dump/Load Data E*/
#define OV2710_OTP_DATA_F       0x3D0F          /*0x00 RW OTP Dump/Load Data F*/
#define OV2710_OTP_CONTROL      0x3D10          /*0x00 RW Bit[2]:OTP load option 0:Fast 1: Bit[1:0]: OTP mode 00: OTP off 10: Write/program OTP 11: OTP off*/
#define OV2710_BIST_CTRL07      0x3E07          /*0x20 RW*/
                                                /* Bit[7] Specifies BIST start. It should first be high, */
                                                /* Bit[5] Specifies BIST test mode 0:Manual mode 1:Auto mode*/
                                                /* Bit[4:0]: Not used*/
#define OV2710_BIST_CTRL12      0x3E0C          /*0x00 RW*/
                                                /* Bit[4]:BIST busy Specifies BIST busy status*/
                                                /* Bit[2:0]: BIST error byte Specifies BIST error type*/
#define OV2710_BIST_RESULT      0x3E0F          /*0x00 RW BIST Test Result01 (0: BIST pass; 1: BIST error)*/
                                                /* Bit[7:4]: Not used*/
                                                /* Bit[2]:ISP DPC*/
                                                /* Bit[2]:VFIFO*/
                                                /* Bit[1:0]: SRM*/
#define OV2710_BIST_DONE        0x3E14          /* R BIST Done Signal When Bit[0] is changed to 1, the signal is cleared*/
#define OV2710_BLC_CONTROL_00   0x4000          /*0x01 RW*/
                                                /* Bit[3]:AVG frame enable 0:BLC is the calculating value 1:BLC will be the average of the calculating value and the original BLC*/
                                                /* Bit[2]:Not used*/
                                                /* Bit[1]:Freeze enable 0:BLC will be updated in some cases 1:BLC will be keep original value*/
                                                /* Bit[0]:BLC enable 0:Disable */
#define OV2710_BLC_CONTROL_01       0x4001      /*0x00 RW Bit[4:0] Start statistic black line Range from 0 to 31*/
#define OV2710_BLC_CONTROL_02       0x4002      /*0x00 RW Bit[6]:Manual offset enable*/
#define OV2710_BLC_FRAME_CONTROL    0x401D      /*0x22 RW */
                                                /* Bit[5:4]: BLC enable mode 00: Always update 10: Update when gain changes x1: No update*/
                                                /* Bit[3:2]: Not used*/
                                                /* Bit[1]:Format change enable*/
                                                /* Bit[0]:Not used*/
#define OV2710_FRAME_CTRL00     0x4201          /* 0x00 RW Bit[3:0]: Frame on number. Control passed frame nubmer. When both ON and OFF numbers are set to 0x00.frame control is in bypass mode.*/
#define OV2710_FRAME_CTRL01     0x4202          /* 0x00 RW Bit[3:0]: Frame off number Control masked frame number When both ON and OFF numbers are set_to 0x00. frame control is in bypass mode.*/
#define OV2710_DVP_CTRL00       0x4700          /*0x04 RW*/
                                                /* Bit[3]:CCIR656 v select*/
                                                /* Bit[2]:CCIR656 f value*/
                                                /* Bit[1]:CCIR656 mode enable*/
                                                /* Bit[0]:HSYNC mode enable*/
#define OV2710_DVP_CTRL01       0x4704          /*0x00 RW*/
                                                /* Bit[7:4]: Not used*/
                                                /* Bit[3:2]: VSYNC output mode select*/
                                                /* Bit[1]:VSYNC3 mode enable VSYNC generated by EOF, unset by first 1 i, long VSYNC turns to 0x00 when first 1 i set*/
                                                /* Bit[0]:VSYNC2 mode enable VSYNC generated by EOF, width controlled by regiser default VYSNC1 mode enable. VSYNC generated by SOF,width controlled by register*/
#define OV2710_DVP_CTRL02       0x4708          /*0x01 RW*/
                                                /* Bit[7]:CLK DDR mode enable*/
                                                /* Bit[6]:Not used*/
                                                /* Bit[5]:VSYNC gate CLK enable*/
                                                /* Bit[4]:HREF gate CLK enable*/
                                                /* Bit[3]:Not used*/
                                                /* Bit[2]:HREF polarity*/
                                                /* Bit[1]:VSYNC polarity*/
                                                /* Bit[0]:PCLK gate low enable*/
#define OV2710_DVP_CTRL03       0x4709          /*0x00 RW*/
                                                /* Bit[7]:Video FIFO bypass mode*/
                                                /* Bit[6:4]: Data bit swap*/
                                                /* 000: Output data is the same order */
                                                /* 001: Output data is reversed, [0:9]*/
                                                /* 010: Output data is reordered as {[2:9], [1:0]}*/
                                                /* 011: Output data is reordered as {[7:0], [9:8]}*/
                                                /* 100: Output data is reordered as {[9:8], [0:7]}*/
                                                /* 101: Output data is reordered as {[9], [0:8]}*/
                                                /* 110: Output data is reordered as {[1:9], [0]}*/
                                                /* 111:Output data is reordered as {[8:0], [9]}*/
#define OV2710_MIPI_CTRL_00     0x4800          /*0x04 RW*/
                                                /* Bit[7:6]: Not used*/
                                                /* Bit[5]:Clock lane gate enable 0:Enable 1:Disable*/
                                                /* Bit[4]:Line sync enable 0:Do not send line short packet for each line 1:Send line short packet for each line*/
                                                /* Bit[3]:Lane select 0:Use lane1 as default data lane 1:Use lane2 as default data lane*/
                                                /* Bit[2]:Idle status LP11 when no packet is transmitted*/
                                                /* Bit[1:0]: Not used*/
#define OV2710_MIPI_CTRL_01     0x4801          /*0x04 RW*/
                                                /* Bit[7]:Long packet data type 0: use mipi data type. 1: use manual data type*/
                                                /* Bit[6]:Short packet data type manual enable 0:Use auto value 1:Use manual value as short packet data*/
                                                /* Bit[5]:Short packet WORD COUNTER manual enable 0:Use frame counter or line counter 1:Select manual value */
                                                /* Bit[4]:PH bit order for ECC 0:{DI[7:0],WC[7:0], WC[15:8]} 1:{DI[0:7],WC[0:7], WC[8:15]}*/
                                                /* Bit[3]:PH byte order for ECC 0:{DI,WC_l,WC_h} 1:{DI,WC_h,WC_l}*/
                                                /* Bit[2]:PH byte order2 for ECC 0:{DI,WC} 1:{WC,DI}*/
                                                /* Bit[1]:MARK1 enable for data lane1 0:Disable MARK1 1:When resume, lane1 should send MARK1*/
                                                /* Bit[0]:MARK1 enable for data lane2 0:Disable MARK1 1:When resume, lane2 should send MARK1*/
#define OV2710_MIPI_CTRL_03     0x4803          /*0x5F RW*/
                                                /* Bit[7:4]: Not used*/
                                                /* Bit[3]:Enable LP CD when HS TX for lane1 0:Disable 1:Enable*/
                                                /* Bit[2]:Enable LP CD when HS TX for lane2 0:Disable 1:Enable*/
                                                /* Bit[1]:Enable LP CD when LP TX for lane2 0:Disable 1:Enable*/
                                                /* Bit[0]:Enable LP CD when LP TX for lane1 0:Disable 1:Enable*/
#define OV2710_MIPI_CTRL_04     0x4804          /*0x8C RW*/
                                                /* Bit[4]:Enable MIPI LP RX to read/write regitsers 0:Disable, RX LP data will write to VFIFO 1:Enable */
                                                /* Bit[3]:Address read/write register will auto add 1 0:Disable 1:Enable*/
                                                /* Bit[2]:LP TX lane select 0:Select lane1 to transmit LP data 1:Select lane2 to transmit LP data*/
                                                /* Bit[1:0]: Not used*/
#define OV2710_MIPI_CTRL_05     0x4805          /*0x10 RW*/
                                                /* Bit[7]:MIPI lane2 disable 0:enable lane2. 1: disable mipi data lane1,lane1 will be LP00*/
                                                /* Bit[6]:MIPI lane1 disable 0:enable lane1. 1:Disable MIPI data lane1, lane1 will be LP00*/
                                                /* Bit[5]:LPX Global timing select 0:Auto calculate T LPX in PCLK2X domain, unit CLK2X 1:Use lp_p_min[7:0]*/
                                                /* Bit[4:3]: Not used*/
                                                /* Bit[2]:MIPI read/write registers disable 0:Enable MIPI access SRB 1:Disable MIPI access SRB*/
                                                /* Bit[1:0]: Not used */
#define OV2710_MAX_FCNT_H               0x4810  /*0xFF RW High Byte of Max Frame Counter of Frame Sync Short PKT*/
#define OV2710_MAX_FCNT_L               0x4811  /*0xFF RW Low Byte of Max Frame Counter of Frame Sync Short Packet*/
#define OV2710_MIN_SPKT_WC_REG_H        0x4812  /*0x00 RW High Byte of Manual Short Packet Word Counter*/
#define OV2710_MIN_SPKT_WC_REG_L        0x4813  /*0x00 RW Low Byte of Manual Short Packet Word Counter*/
#define OV2710_MIPI_CTRL_14             0x4814  /*0x2A RW Bit[7:6]:Virtual channel of MIPI packet Bit[5:0]:Data type manual*/
#define OV2710_MIPI_SPKT_DT             0x4815  /*0x00 RW Manual Data type for short packet*/
#define OV2710_MIN_HS_ZERO_H            0x4818  /*0x00 RW High Byte of Minimum Value of hs_zero, unit ns*/
#define OV2710_MIN_HS_ZERO_L            0x4819  /*0x96 RW Low Byte of Minimum Value of hs_zero hs_zero_real = hs_zero_min_o + tui¡Á ui_hs_zero_min_o*/
#define OV2710_MIN_MIPI_HS_TRAIL_H      0x481A  /*0x00 RW High Byte of Minimum Value of hs_trail, unit ns*/
#define OV2710_MIN_MIPI_HS_TRAIL_L      0x481B  /*0x3C RW Low Byte of Minimum Value of hs_trail hs_trail_real = hs_trail_min_o + tui¡Á ui_hs_trail_min_o*/
#define OV2710_MIN_MIPI_CLK_ZERO_H      0x481C  /*0x01 RW High Byte of Minimum Value of clk_zero, unit ns*/
#define OV2710_MIN_MIPI_CLK_ZERO_L      0x481D  /*0x86 RW Low Byte of Minimum Value of clk_zero clk_zero_real = clk_zero_min_o + tui¡Á ui_clk_zero_min_o*/
#define OV2710_MIN_MIPI_CLK_PREPARE_H   0x481E  /*0x00 RW High Byte of Minimum Value of clk_prepare, unit ns*/
#define OV2710_MIN_MIPI_CLK_PREPARE_L   0x481F  /*0x3C RW Low Byte of Minimum Value of clk_prepare clk_prepare_real = clk_prepare_min_o + tui¡Á ui_clk_prepare_min_o*/
#define OV2710_MIN_CLK_POST_H           0x4820  /*0x00 RW  High Byte of Minimum Value of clk_post, unit ns*/
#define OV2710_MIN_CLK_POST_L           0x4821  /*0x56 RW Low Byte of Minimum Value of clk_post clk_post_real = clk_post_min_o + tui¡Á ui_clk_post_min_o*/
#define OV2710_MIN_CLK_TRAIL_H          0x4822  /*0x00 RW High Byte of Minimum Value of clk_trail, unit ns*/
#define OV2710_MIN_CLK_TRAIL_L          0x4823  /*0x3C RW Low Byte of Minimum Value of clk_trail clk_trail_real = clk_trail_min_o + tui¡Á ui_clk_trail_min_o*/
#define OV2710_MIN_LPX_PCLK_H           0x4824  /*0x00 RW High Byte of Minimum Value of lpx_p, unit ns*/
#define OV2710_MIN_LPX_PCLK_L           0x4825  /*0x32 RW Low Byte of Minimum Value of lpx_p lpx_p_real = lpx_p_min_o + tui¡Á ui_lpx_p_min_o*/
#define OV2710_MIN_HS_PREPARE_H         0x4826  /*0x00 RW High Byte of Minimum Value of hs_prepare, unit ns*/
#define OV2710_MIN_HS_PREPARE_L         0x4827  /*0x32 RW Low Byte of Minimum Value of hs_prepare hs_prepare_real = hs_prepare_min_o + tui¡Á ui_hs_prepare_min_o*/
#define OV2710_MIN_HS_EXIT_H            0x4828  /*0x00 RW High Byte of Minimum Value of hs_exit, unit ns*/
#define OV2710_MIN_HS_EXIT_L            0x4829  /*0x64 RW Low Byte of Minimum Value of hs_exit hs_exit_real = hs_exit_min_o + tui¡Á ui_hs_exit_min_o*/
#define OV2710_MIN_HS_ZERO_UI           0x482A  /*0x05 RW Minimum UI Value of hs_zero, unit UI*/
#define OV2710_MIN_HS_TRAIL_UI          0x482B  /*0x04 RW Minimum UI Value of hs_trail, unit UI*/
#define OV2710_MIN_CLK_ZERO_UI          0x482C  /*0x00 RW Minimum UI Value of clk_zero, unit UI*/
#define OV2710_MIN_CLK_PREPARE_UI       0x482D  /*0x00 RW Minimum UI Value of clk_prepare, unit UI*/
#define OV2710_MIN_CLK_POST_UI          0x482E  /*0x34 RW Minimum UI Value of clk_post, unit UI*/
#define OV2710_MIN_CLK_TRAIL_UI         0x482F  /*0x00 RW Minimum UI Value of clk_trail, unit UI*/
#define OV2710_MIN_LPX_PCLK_UI          0x4830  /*0x00 RW Minimum UI Value of lpx_p (pclk2x domain), unit UI*/
#define OV2710_MIN_HS_PREPARE_UI        0x4831  /*0x04 RW Minimum UI Value of hs_prepare, unit UI*/
#define OV2710_MIN_HS_EXIT_UI           0x4832  /*0x00 RW Minimum UI Value of hs_exit, unit UI*/
#define OV2710_ISP_CONTROL0             0x5000  /*0xDF RW*/
                                                /* Bit[7]:LENC enable 0:Disable 1:Enable*/
                                                /* Bit[6:3]: Not used*/
                                                /* Bit[2]:Black pixel cancellation enable 0:Disable 1:Enable*/
                                                /* Bit[1]:White pixel cancellation enable 0:Disable 1:Enable*/
                                                /* Bit[0]:Not used*/
#define OV2710_ISP_CONTROL1             0x5001  /*0x4F RW Bit[0]:AWB enable 0:Disable 1:Enable*/
#define OV2710_ISP_CONTROL2             0x5002  /*0xE0 RW Bit[2]:VAP enable 0:Disable 1:Enable*/
#define OV2710_ISP_CONTROL5             0x5005  /*0xDC RW Bit[4]:AWB bias on*/
#define OV2710_ISP_CONTROL31            0x501F  /*0x03 RW Bit[2:0]: Format select 011: ISP RAW 100: INT CIF RAW*/
#define OV2710_ISP_TEST                 0x503D  /*0x00 RW*/
                                                /* Bit[7]: 0: off; 1:Color bar enable*/
                                                /* Bit[5:4]: Color bar pattern select 10: Color bar pattern*/
                                                /* Bit[2]:Color bar rolling enable*/
#define OV2710_ISP_SENSOR_BIAS_READOUT  0x503E  /* R ISP Sensor Bias Readout*/
#define OV2710_ISP_SENSOR_GAIN_READOUT  0x503F  /* R ISP Sensor Gain Readout*/
#define OV2710_AWB_CONTROL_00           0x5180  /*0x40 RW Bit[6]:fast_awb Bit[5]:freeze_gain_en Bit[4]:freeze_sum_en Bit[2]:start_sel*/
#define OV2710_AWB_CONTROL_01           0x5181  /*0x02 RW Bit[7:0]: Delta*/
#define OV2710_AWB_CONTROL_02           0x5182  /*0x04 RW Bit[7:0]: Stable range*/
#define OV2710_STABLE_RANGE_WIDE        0x5183  /*0x08 RW Bit[7:0]: Stable range to determine whether it is in stable status when it is already in stable status*/
#define OV2710_RED_GAIN_LIMIT           0x518C  /*0xF0 RW*/
                                                /* Bit[7:4]: Red gain up limit Maximum red gain is: red gain up limit *256 + 0xFF*/
                                                /* Bit[3:0]: Red gain down limit Minimum red gain is: red gain down limit *256 + 0*/
#define OV2710_GREEN_GAIN_LIMIT         0x518D  /*0xF0  RW*/
                                                /* Bit[7:4]: Green gain up Maximum green gain is: green gain up limit*256 + 0xFF*/
                                                /* Bit[3:0]: Green gain down Minimum green gain is: green gain down limit*256 + 0*/
#define OV2710_BLUE_GAIN_LIMIT          0x518E  /*0xF0 RW*/
                                                /* Bit[7:4]: Blue gain up limit Maximum blue gain is: blue gain up limit*256 + 0xFF*/
                                                /* Bit[3:0]: Blue gain down limit Minimum blue gain is: blue gain down limit*256 + 0*/
#define OV2710_AWB_FRAME_COUNTER            0x518F      /*0x04 RW Bit[3:0]: Number of frames to do AWB when AWB is in stable mode*/
#define OV2710_RED_BEFORE_GAIN_AVERAGE      0x5196      /* R Bit[7:0]: Before AWB gain's red data average*/
#define OV2710_GREEN_BEFORE_GAIN_AVERAGE    0x5197      /* R Bit[7:0]: Before AWB gain's green data average*/
#define OV2710_BLUE_BEFORE_GAIN_AVERAGE     0x5198      /* R Bit[7:0]: Before AWB gain's blue data average*/
#define OV2710_RED_AFTER_GAIN_AVERAGE_H     0x5199      /* R Bit[7:0]: After AWB gain's red data average high byte*/
#define OV2710_RED_AFTER_GAIN_AVERAGE_L     0x519A      /* R Bit[7:0]: After AWB gain's red data average low byte*/
#define OV2710_GREEN_AFTER_GAIN_AVERAGE_H   0x519B      /* R Bit[7:0]: After AWB gain's green data average high byte*/
#define OV2710_GREEN_AFTER_GAIN_AVERAGE_L   0x519C      /* R Bit[7:0]: After AWB gain's green data average low byte*/
#define OV2710_BLUE_AFTER_GAIN_AVERAGE_H    0x519D      /* R Bit[7:0]: After AWB gain's blue data average high byte*/
#define OV2710_BLUE_AFTER_GAIN_AVERAGE_L    0x519E      /* R Bit[7:0]: After AWB gain's blue average low byte*/
#define OV2710_AVG_START_POSITION_AT_HORIZONTAL_H   0x5680      /*0x00 RW Bit[3:0]: AVG start position[11:8] at horizontal*/
#define OV2710_AVG_START_POSITION_AT_HORIZONTAL_L   0x5681      /*0x00 RW Bit[7:0]: AVG start position[7:0] at horizontal*/
#define OV2710_AVG_END_POSITION_AT_HORIZONTAL_H     0x5682      /*0x08 RW Bit[3:0]: AVG end position[11:8] at horizontal*/
#define OV2710_AVG_END_POSITION_AT_HORIZONTAL_L     0x5683      /*0x00 RW Bit[7:0]: AVG end position[7:0] at horizontal*/
#define OV2710_AVG_START_POSITION_AT_VERTICAL_H     0x5684      /*0x00 RW Bit[2:0]: AVG start position[10:8] at vertical*/
#define OV2710_AVG_START_POSITION_AT_VERTICAL_L     0x5685      /*0x80 RW Bit[7:0]: AVG start position[7:0] at vertical*/
#define OV2710_AVG_END_POSITION_AT_VERTICAL_H       0x5686      /*0x00 RW Bit[2:0]: AVG end position[10:8] at vertical*/
#define OV2710_AVG_END_POSITION_AT_VERTICAL_L       0x5687      /*0x00 RW Bit[7:0]: AVG end position[7:0] at vertical*/
#define OV2710_AVG_R10                      0x5690      /* R Bit[7:0]: Average of raw image[9:2]*/
#define OV2710_DPC_CTRL00                   0x5780      /*0x7F RW*/
                                                        /* Bit[7]:Not used*/
                                                        /* Bit[6]: Keep vertical channel 0: 1:*/
                                                        /* Bit[5]: connected 0:Disable removing the same channel connected defected pixels 1:Enable removing the same channel connected defected pixels*/
                                                        /* Bit[4]:Enable different channel connected 0:Disable removing the different channel connected defected pixels. 1: Enable removing the different channel connected defected pixels*/
                                                        /* Bit[3:2]: Matching index selection */
                                                        /* 00: No matching point check */
                                                        /* 01: Check the before and after pixels from the third to fourth pixels*/
                                                        /* 10: Check the before and after pixels from the third to fifth pixels*/
                                                        /* 11: Check the before and after pixels from the third to sixth pixels*/
                                                        /* Bit[1:0]: Not used*/
#define OV2710_WHITE_THRESHOLD_LIST0        0x5781      /*0x20 RW Bit[6:0]: White pixel threshold list 0*/
#define OV2710_WHITE_THRESHOLD_LIST1        0x5782      /*0x18 RW Bit[6:0]: White pixel threshold list 1*/
#define OV2710_WHITE_THRESHOLD_LIST2        0x5783      /*0x08 RW Bit[6:0]: White pixel threshold list 2*/
#define OV2710_WHITE_THRESHOLD_LIST3        0x5784      /*0x04 RW Bit[6:0]: White pixel threshold list 3*/
#define OV2710_BLACK_THRESHOLD_LIST0        0x5785      /*0x40 RW Bit[7:0]: Black pixel threshold list 0 */
#define OV2710_BLACK_THRESHOLD_LIST1        0x5786      /*0x18 RW Bit[7:0]: Black pixel threshold list 1*/
#define OV2710_BLACK_THRESHOLD_LIST2        0x5787      /*0x08 RW Bit[7:0]: Black pixel threshold list 2*/
#define OV2710_BLACK_THRESHOLD_LIST3        0x5788      /*0x04 RW Bit[7:0]: Black pixel threshold list 3*/
#define OV2710_GAIN_LIST1                   0x5789      /*0x08 RW Bit[6:0]: Gain list 1*/
#define OV2710_GAIN_LIST2                   0x578A      /*0x20 RW Bit[6:0]: Gain list 2*/
#define OV2710_DPC_CTRL01                   0x578B      /*0x07 RW*/
                                                        /* Bit[3]:Mode 1 enable 0:Disable 1:Enable only remove cluster*/
                                                        /* Bit[2]:Mode 2 enable 0:Disable 1:Enable*/
#define OV2710_DPC_SATURATE                 0x578C      /*0x00 RW Saturate Value Set for Cross Cluster*/
#define OV2710_PATTERN_THRESHOLD_LIST0H     0x5790      /*0x00 RW Bit[1:0]: Pattern threshold list 0[9:8]*/
#define OV2710_PATTERN_THRESHOLD_LIST0L     0x5791      /*0x08 RW Bit[7:0]: Pattern threshold list 0[7:0]*/
#define OV2710_PATTERN_THRESHOLD_LIST1H     0x5792      /*0x00 RW Bit[1:0]: Pattern threshold list 1[9:8]*/
#define OV2710_PATTERN_THRESHOLD_LIST1L     0x5793      /*0x18 RW Bit[7:0]: Pattern threshold list 1[7:0]*/
#define OV2710_PATTERN_THRESHOLD_LIST2H     0x5794      /*0x00 RW Bit[1:0]: Pattern threshold list 2[9:8]*/
#define OV2710_PATTERN_THRESHOLD_LIST2L     0x5795      /*0x80 RW Bit[7:0]: Pattern threshold list 2[7:0]*/
#define OV2710_PATTERN_THRESHOLD_H          0x5796      /*0x01 RW Bit[1:0]: Pattern threshold list 3[9:8]*/
#define OV2710_PATTERN_THRESHOLD_L          0x5797      /*0x00 RW Bit[7:0]: Pattern threshold list 3[7:0]*/
#define OV2710_LENC_RED_X0_H                0x5800      /*0x00 RW Bit[7:0]: Red center horizontal position (x0) high bits*/
#define OV2710_LENC_RED_X0_L                0x5801      /*0x0C RW Bit[7:0]: Red center horizontal position*/
#define OV2710_LENC_RED_Y0_H                0x5802      /*0x00 RW Bit[7:0]: Red center vertical position (y0) high bits*/
#define OV2710_LENC_RED_Y0_L                0x5803      /*0x06 RW Bit[7:0]: Red center vertical position (y0) low eight bits*/
#define OV2710_LENC_RED_A1                  0x5804      /*0x22 RW Bit[7:0]: Red parameter a1 a1 and a2 are used to generate the a parameter*/
#define OV2710_LENC_RED_A2                  0x5805      /*0x07 RW Bit[7:0]: Red parameter a2 a1 and a2 are used to generate the parameter a*/
#define OV2710_LENC_RED_B1                  0x5806      /*0xC2 RW*/
                                                        /* Bit[7]: Sign bit 0: b1 is positive 1:b1 is negative*/
                                                        /* Bit[6:0]: Red parameter b1. b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_RED_B2          0x5807      /*0x08 RW Bit[3:0]: Red parameter b2 b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_GRN_X0_H        0x5808      /*0x00 RW Bit[7:0]: Green center horizontal position (x0) high bits*/
#define OV2710_LENC_GRN_X0_L        0x5809      /*0x0C RW Bit[7:0]: Green center horizontal position (x0) low eight bits*/
#define OV2710_LENC_GRN_Y0_H        0x580A      /*0x00 RW Bit[7:0]: Green center vertical position (y0) high bits*/
#define OV2710_LENC_GRN_Y0_L        0x580B      /*0x06 RW Bit[7:0]: Green center vertical position (y0) low eight bits*/
#define OV2710_LENC_GRN_A0_H        0x580C      /*0x22 RW Bit[7:0]: Green parameter a1 a1 and a2 are used to generate the parameter a*/
#define OV2710_LENC_GRN_A0_L        0x580D      /*0x07 RW Bit[7:0]: Green parameter a2 a1 and a2 are used to generate the parameter a*/
#define OV2710_LENC_GRN_B1          0x580E      /*0xC2 RW */
                                                /* Bit[7]:Sign bit 0:b1 is positive 1:b1 is negative*/
                                                /* Bit[6:0]: Green parameter b1 b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_GRN_B2          0x580F      /*0x08 RW Bit[3:0]: Green parameter b2 b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_BLU_X0_H        0x5810      /*0x00 RW Bit[7:0]: Blue center horizontal position (x0) high bits*/
#define OV2710_LENC_BLU_X0_L        0x5811      /*0x0C RW Bit[7:0]: Blue center horizontal position (x0) low eight bits*/
#define OV2710_LENC_BLU_Y0_H        0x5812      /*0x00 RW Bit[7:0]: Blue center vertical position (y0)high eight bits*/
#define OV2710_LENC_BLU_Y0_L        0x5813      /*0x06 RW Bit[7:0]: Blue center vertical position (y0)low eight bits*/
#define OV2710_LENC_BLU_A1          0x5814      /*0x22 RW Bit[7:0]: Blue parameter a1.  a1 and a2 are used to generate the parameter a*/
#define OV2710_LENC_BLU_A2          0x5815      /*0x07 RW Bit[7:0]: Blue parameter a2 a1 and a2 are used to generate the parameter a*/
#define OV2710_LENC_BLU_B1          0x5816      /*0xC2 RW*/
                                                /* Bit[7:0]: Sign bit 0:b1 is positive 1:b1 is negative*/
                                                /* Bit[6:0]: blue parameter b1 b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_BLU_B2          0x5817      /*0x08 RW Bit[3:0]: Blue parameter b2 b1 and b2 are used to generate the parameter b*/
#define OV2710_LENC_CTRL00          0x5818      /*0x04 RW*/
                                                /* Bit[2]:Round enable*/
                                                /* Bit[1]: 0:Disable coefficient manual mode 1:Enable coefficient manual mode, use auto mode to calculate the coefficient*/
                                                /* Bit[0]:gain coefficient enable 0:Use the gain = 128 to calculate the coefficient 1:Use the sensor gain to calculate the coefficient*/
#define OV2710_LENC_COEF_TH         0x5819      /*0x80 RW Bit[7:0]: LENC coefficient threshold*/
#define OV2710_LENC_GAIN_THRE1      0x581A      /*0x00 RW Bit[7:0]: LENC gain low threshold (t1)*/
#define OV2710_LENC_GAIN_THRE2      0x581B      /*0x00 RW Bit[7:0]: LENC gain high threshold (t2)*/
#define OV2710_LENC_COEF_MAN        0x581C      /*0x80 RW Bit[7:0]: Coefficient manual input*/
#define OV2710_AFC_CTRL00           0x6000      /*0x1F RW*/
                                                /* Bit[7:5]: Not used*/
                                                /* Bit[4]:Edge filter enable 0:afc_edge module will not update 1:afc_edge module will update*/
                                                /* Bit[3]:Edge filter b select 0:DGE selects b2 1:Edge selects b1*/
                                                /* Bit[2:0]: Edge filter a select*/
                                                /* 000: Edge selects a1*/
                                                /* 001: Edge selects a2*/
                                                /* 010: Edge selects a3*/
                                                /* 100: Edge selects a4*/
                                                /* 101: Edge selects a5*/
#define OV2710_AFC_CTRL01           0x6001      /*0x01 RW Bit[7:0]: Edge window0 left coordinate*/
#define OV2710_AFC_CTRL02           0x6002      /*0x00 RW Bit[7:0]: Edge window0 top coordinate*/
#define OV2710_AFC_CTRL03           0x6003      /*0x76 RW Bit[7:0]: Edge window0 right coordinate*/
#define OV2710_AFC_CTRL04           0x6004      /*0x42 RW Bit[7:0]: Edge window0 bottom coordinate This bottom must be larger than any other*/
#define OV2710_AFC_CTRL05           0x6005      /*0x01 RW Bit[7:0]: Edge window1 left coordinate*/
#define OV2710_AFC_CTRL06           0x6006      /*0x00 RW Bit[7:0]: Edge window1 top coordinate*/
#define OV2710_AFC_CTRL07           0x6007      /*0x76 RW Bit[7:0]: Edge window1 right coordinate*/
#define OV2710_AFC_CTRL08           0x6008      /*0x42 RW Bit[7:0]: Edge window1 bottom coordinate*/
#define OV2710_AFC_CTRL09           0x6009      /*0x01 RW Bit[7:0]: Edge window2 left coordinate*/
#define OV2710_AFC_CTRL10           0x600A      /*0x00 RW*/
#define OV2710_AFC_CTRL11           0x600B      /*0x76 RW*/
#define OV2710_AFC_CTRL12           0x600C      /*0x42 RW Bit[7:0]: Edge window2 bottom coordinate*/
#define OV2710_AFC_CTRL13           0x600D      /*0x01 RW Bit[7:0]: Edge window3 left coordinate*/
#define OV2710_AFC_CTRL14           0x600E      /*0x00 RW Bit[7:0]: Edge window3 top coordinate*/
#define OV2710_AFC_CTRL15           0x600F      /*0x76 RW Bit[7:0]: Edge window3 right coordinate*/
#define OV2710_AFC_CTRL16           0x6010      /*0x42 RW Bit[7:0]: Edge window3 bottom coordinate*/
#define OV2710_AFC_CTRL17           0x6011      /*0x01 RW Bit[7:0]: Edge window4 left coordinate*/
#define OV2710_AFC_CTRL18           0x6012      /*0x00 RW Bit[7:0]: Edge window4 top coordinate*/
#define OV2710_AFC_CTRL19           0x6013      /*0x76 RW Bit[7:0]: Edge window4 right coordinate*/
#define OV2710_AFC_CTRL20           0x6014      /*0x42 RW Bit[7:0]: Edge window4 bottom coordinate*/


#define OV2710_VIDEO_FPS_REG_NUM            (8)
#define OV2710_VIDEO_FORMAT_REG_NUM         (25)
#define OV2710_VIDEO_FORMAT_REG_TABLE_SIZE  (5)
#define OV2710_VIDEO_PLL_REG_TABLE_SIZE     (4)

#define OV2710_VIN_MAX_FPS_TABLE_SIZE       (256)


/** OV9710 mirror mode*/
#define OV2710_MIRROR_ROW       (0x01 << 6)
#define OV2710_MIRROR_COLUMN    (0x01 << 5)
#define OV2710_MIRROR_MASK      (OV2710_MIRROR_ROW + OV2710_MIRROR_COLUMN)


/* OV2710 global gain table row size */
#define OV2710_GAIN_ROWS        (97)
#define OV2710_GAIN_COLS        (4)
#define OV2710_GAIN_DOUBLE      (16)
#define OV2710_GAIN_0DB         (96)

#define OV2710_GAIN_COL_AGC     (0)
#define OV2710_GAIN_COL_FAGC    (1)
#define OV2710_GAIN_COL_REG300A (2)
#define OV2710_GAIN_COL_REG300B (3)


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
typedef struct
{
    U16 reg;
    U8  data;
}ov2710_reg_table;

typedef struct
{
    U32 pixclk;
    U32 extclk;
    ov2710_reg_table regs[OV2710_VIDEO_PLL_REG_TABLE_SIZE];
}ov2710_pll_reg_table;

typedef struct
{
    U16 reg[OV2710_VIDEO_FPS_REG_NUM];
    struct
    {
        ov2710_pll_reg_table *pll_reg_table;
        U32     fps;
        U8      system;
        U16     data[OV2710_VIDEO_FPS_REG_NUM];
    } table[OV2710_VIN_MAX_FPS_TABLE_SIZE];
}ov2710_video_fps_reg_table;

typedef struct
{
    U16     reg[OV2710_VIDEO_FORMAT_REG_NUM];
    struct
    {
        void (*ext_reg_fill)(GD_HANDLE* pHandle);
        U8      data[OV2710_VIDEO_FORMAT_REG_NUM];
        ov2710_video_fps_reg_table *fps_table;
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
        U32     auto_fps;
    } table[OV2710_VIDEO_FORMAT_REG_TABLE_SIZE];
}ov2710_video_format_reg_table;

typedef struct
{
    U32     format_index;
    U16     def_start_x;
    U16     def_start_y;
    U16     def_width;
    U16     def_height;
    U16     sync_start;
    U8      type_ext;
    U8      bayer_pattern;
}ov2710_video_info;

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

GERR ov2710_docmd(GD_HANDLE* pHandle, GD_SENSOR_CMD_E cmd, void *args);

#ifdef __cplusplus
}
#endif


#endif /* _OV2710_PRI_H_ */


/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fdp_hw.h
 * Date: 2022-09-08 14:53:42
 * LastEditTime: 2022-09-08 14:53:42
 * Description:  This file is for providing some hardware register and function definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDP_HW_H
#define FDP_HW_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fio.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/
/**
* This macro writes the given register.
* @param    base_addr is the base address of the device.
* @param    reg_offset is the register offset to be written.
* @param    data is the 32-bit value to write to the register.
* @return   None.
* @note     None.
*****************************************************************************/
#define FDP_READ_REG32(addr, reg_offset) FtIn32((addr) + (u32)(reg_offset))

#define FDP_WRITE_REG32(addr, reg_value) FtOut32(addr, (u32)(reg_value))

#define FDC_PHY_ALIGN(data, Offset) ((data + Offset - 1) & ~(Offset - 1))

#define FDP_SETBIT(base_addr, reg_offset, data)      FtSetBit32((base_addr) + (u32)(reg_offset), (u32)(data))

#define FDP_CLEARBIT(base_addr, reg_offset, data)     FtClearBit32((base_addr) + (u32)(reg_offset), (u32)(data))

/*
 TX Registers
*/
#define FDPTX_LINK_BW_SET 0x0000
#define FDP_TX_LANE_COUNT_SET  0x0004
#define FDP_TX_ENHANCED_FRAME_EN 0x0008
#define FDP_TX_TRAINING_PATTERN_SET 0x000c

#define FDP_TX_LINK_QUAL_PATTERN_SET 0x0010
#define FDP_TX_SCRAMBLING_DISABLE 0x0014
#define FDP_TX_DOWNSPREAD_CTRL 0x0018
#define FDP_TX_ALT_SCRAMBLER_RESET 0x001c
#define FDP_TX_HBR2_SCRAMBLER_RESET 0x0020
#define FDP_TX_DISPLAYPORT_VERSION 0x0024
#define FDP_TX_LANE_REMAP 0x002C

#define FDP_TX_ENABLE 0x0080
#define FDP_TX_ENABLE_MAIN_STREAM 0x0084
#define FDP_TX_ENABLE_SEC_STREAM 0x0088
#define FDP_TX_SEC_DATA_WINDOW 0x008C
#define FDP_TX_LINK_SOFT_RESET 0x0090
#define FDP_TR_INPUT_COURCE_ENABLE 0x0094

#define FDP_TX_FORCE_SCRAMBLER_RESET 0x00C0
#define FDP_TX_SOURCE_CONTROL_STATUS 0x00C4
#define FDP_TX_DATA_CONTROL 0x00C8

#define FDP_TX_CORE_CAPABILITY 0x00F8
#define FDP_TX_CORE_ID 0x00FC

#define FDP_TX_CMD_REG 0x0100
#define FDP_TX_FIFO 0x0104
#define FDP_TX_ADDRESS_REG 0x0108
#define FDP_TX_CLK_DIVIDER 0x010C
#define FDP_TX_AUX_REPLY_TIMEOUT_INTERVAL 0x0110
#define FDP_TX_SINK_HPD_STATE 0x0128
#define FDP_TX_STATUS 0x0130
#define FDP_TX_RCV_FIFO 0x0134
#define FDP_TX_RCV_REPLY_REG 0x0138
#define FDP_TX_RCV_REPLY_COUNT 0x013C

#define FDP_TX_INTERRUPT 0x0140
#define FDP_TX_INTERRUPT_MASK 0x0144
#define FDP_TX_RCV_DATA_COUNT 0x0148
#define FDP_TX_AUX_TRANSACTION_STATUS 0x014C
#define FDP_TX_TIMER 0x0158

/*FDPTX_MAIN_LINK_MISC0*/
#define FDPTX_MAIN_LINK_MISC0_CLOCK_MODE   BIT(0)
#define FDPTX_MAIN_LINK_MISC0_COLOR_FORMAT GENMASK(2,1)
#define FDPTX_MAIN_LINK_MISC0_BIT_DEPTH    GENMASK(7,5)

/*
 Main Link registers
*/
#define FDPTX_MAIN_LINK_HTOTAL 0x0180
#define FDPTX_MAIN_LINK_VTOTAL 0x0184
#define FDPTX_MAIN_LINK_POLARITY 0x0188
#define FDPTX_MAIN_LINK_HSWIDTH 0x018C
#define FDPTX_MAIN_LINK_VSWIDTH 0x0190
#define FDPTX_MAIN_LINK_HRES 0x0194
#define FDPTX_MAIN_LINK_VRES 0x0198
#define FDPTX_MAIN_LINK_HSTART 0x019C
#define FDPTX_MAIN_LINK_VSTART 0x01A0
#define FDPTX_MAIN_LINK_MISC0 0x01A4
#define FDPTX_MAIN_LINK_MISC1 0x01A8
#define FDPTX_M_VID 0x01AC
#define FDPTX_TRANSFER_UNIT_SIZE 0x01B0
#define FDPTX_N_VID 0x01B4
#define FDPTX_USER_PIXEL_WIDTH 0x01B8
#define FDPTX_DATA_PER_LANE 0x01BC
#define FDPTX_INTERLACED 0x01C0
#define FDPTX_USER_POLARITY 0x01C4
#define FDPTX_USER_CONTROL 0x01C8

#define FDP_TX_AUX_ERROR_MASK BIT(6) //AUX reply error
#define FDP_TX_GP_TIME_MASK BIT(4) // 通用定时器中断
#define FDP_TX_AUX_TIMEOUT_MASK BIT(3) //因等待 AUX reply 超时发起中断
#define FDP_TX_AUX_RECEIVED_MASK BIT(2) //接收到 AUX reply 发起中断
#define FDP_TX_HPD_INTR_MASK BIT(1) //hpd irq 中断
#define FDP_TX_HPD_EVENT_MASK BIT(0)//HPD 连接或断开事件 中断

#define FDP_TX_STATUS_AUX_ERROR BIT(6)
#define FDP_TX_STATUS_GP_TIME BIT(4)
#define FDP_TX_STATUS_AUX_TIMEOUT BIT(3)
#define FDP_TX_STATUS_AUX_RECEIVED BIT(2)
#define FDP_TX_STATUS_HPD_INTR BIT(1)
#define FDP_TX_STATUS_HPD_EVENT BIT(0)

/*
  eDP CRC registers
*/
#define FDPTX_EDP_CRC_ENABLE 0x01D0
#define FDPTX_EDP_CRC_RED 0x01D4
#define FDPTX_EDP_CRC_GREEN 0x01D8
#define FDPTX_EDP_CRC_BLUE 0x01DC

/* FDCDP AUDIO*/
#define FDP_AUDIO_ENABLE   0x300
#define FDP_AUDIO_SEC_INPUT_SOURCE   0x304
#define FDP_AUDIO_CHANNEL_COUNT   0x308
#define FDP_AUDIO_DIRECT_CLKDIV   0x30C
#define FDP_AUDIO_INFOFRAME_ENABLE   0x310
#define FDP_AUDIO_INFOFRAME_RATE   0x314
#define FDP_AUDIO_MAUD   0x318
#define FDP_AUDIO_NAUD   0x31C
#define FDP_AUDIO_CLOCK_MODE   0x320
#define FDP_AUDIO_3D_VSC_DATA   0x324
#define FDP_AUDIO_INPUT_FIFO   0x328
#define FDP_AUDIO_INPUT_FIFO_DEPTH   0x32C
#define FDP_AUDIO_INPUT_FIFO_READY   0x330
#define FDP_AUDIO_INFOFRAME_SELECT   0x334
#define FDP_AUDIO_INFOFRAME_DATA   0x338
#define FDP_AUDIO_TIMESTAMP_INTERVAL  0x33C
#define FDP_AUDIO_CS_SOURCE_FORMAT  0x340
#define FDP_AUDIO_CATEGORY_CODE  0x344
#define FDP_AUDIO_CS_LENGTH_ORIG_FREQ  0x348
#define FDP_AUDIO_CS_FREQ_CLOCK_ACCURACY 0x34C
#define FDP_AUDIO_CS_COPYRIGHT 0x350
#define FDP_AUDIO_GTC_COUNT_CONFIG 0x354
#define FDP_AUDIO_GTC_COMMAND_EDGE 0x358
#define FDP_AUDIO_CHANNEL_MAP 0x35C
#define FDP_AUDIO_DB_LANE_SELECT 0x3E0
#define FDP_AUDIO_DB_WRITE_INDEX 0x3E4
#define FDP_AUDIO_DB_DATA_COUNT 0x3E8
#define FDP_AUDIO_DB_DATA 0x3EC
#define FDP_AUDIO_DB_READY 0x3F0
#define FDP_AUDIO_DB_BUSY 0x3F4
#define FDP_AUDIO_DB_ENABLE 0x3F8

#define FDP_AUDIO_CLOCK_MODE_MASK BIT(0)
#define FDP_TX_ENABLE_SEC_STREAM_MASK BIT(0)

#define FDP_AUDIO_ENABLE_MUTE BIT(1)
#define FDP_AUDIO_ENABLE_MASK BIT(0)

#define ORIG_FREQ_32000                 0xc
#define ORIG_FREQ_44100                 0xf
#define ORIG_FREQ_48000                 0xd
#define ORIG_FREQ_88200                 0x7
#define ORIG_FREQ_96000                 0x5
#define ORIG_FREQ_176400                0x3
#define ORIG_FREQ_192000                0x1
#define ORIG_FREQ_MASK                  0xf
#define ORIG_FREQ_SHIFT                 0

#define WORD_LENGTH_16                  0x4
#define WORD_LENGTH_18                  0x2
#define WORD_LENGTH_20                  0xc
#define WORD_LENGTH_24                  0xd
#define WORD_LENGTH_MASK                0xf
#define WORD_LENGTH_SHIFT               4

#define SAMPLING_FREQ_32000             0xc
#define SAMPLING_FREQ_44100             0x0
#define SAMPLING_FREQ_48000             0x4
#define SAMPLING_FREQ_88200             0x1
#define SAMPLING_FREQ_96000             0x5
#define SAMPLING_FREQ_176400            0x3
#define SAMPLING_FREQ_192000            0x7
#define SAMPLING_FREQ_MASK              0xf
#define SAMPLING_FREQ_SHIFT             4

#define AUDIO_INFOFRAME_VENDOR_SPECIFIC   0x0
#define AUDIO_INFOFRAME_AUX_VIDEO         0x1
#define AUDIO_INFOFRAME_SOURCE_PRODUCT    0x2
#define AUDIO_INFOFRAME_AUDIO_DESCRIPTION 0x3
#define AUDIO_INFOFRAME_NTSC_VBI          0x4
/************************** Function Prototypes ******************************/

/* write the data to the channel of dp */
void FDpChannelRegWrite(uintptr addr,  uintptr offset, u32 data);

/* read the data from the channel of dp */
FError FDpChannelRegRead(uintptr addr, uintptr offset);

/* write FdpPhy control register */
void FDpPhyRegWrite(uintptr addr, uintptr offset, u32 data);

/* read FdpPhy control register */
FError FDpPhyRegRead(uintptr addr,  uintptr offset);

/*dump the dp info*/
void FDpDump(uintptr address);

#ifdef __cplusplus
}
#endif

#endif

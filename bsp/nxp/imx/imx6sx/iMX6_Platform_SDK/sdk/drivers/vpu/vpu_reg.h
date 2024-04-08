/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006, Chips & Media.  All rights reserved.
 */

/*!
 * @file vpu_reg.h
 *
 * @brief header file for codec registers in VPU
 *
 * @ingroup diag_vpu
 */

#ifndef __VPU__REG__H
#define __VPU_REG__H

//! @addtogroup diag_vpu
//! @{

////////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

#define GDMA_BASE	0x1000
#define NPT_BASE        0x3000

#define BIT_CODE_RUN			0x000
#define BIT_CODE_DOWN			0x004
#define BIT_INT_REQ			0x008
#define BIT_INT_CLEAR			0x00C
#define	BIT_INT_STS			0x010   // Not prsent
#define	BIT_CODE_RESET			0x014
#define BIT_CUR_PC			0x018
#define BIT_SW_RESET                   0x024
#define BIT_SW_RESET_STATUS            0x034

/*---------------------------------------------------------------------------
 *  GLOBAL REGISTER
 *---------------------------------------------------------------------------*/
#define BIT_CODE_BUF_ADDR		0x100
#define BIT_WORK_BUF_ADDR		0x104
#define BIT_PARA_BUF_ADDR		0x108
#define BIT_BIT_STREAM_CTRL		0x10C
#define BIT_FRAME_MEM_CTRL		0x110
#define CMD_DEC_DISPLAY_REORDER		0x114
#define BIT_BIT_STREAM_PARAM		0x114
#define BIT_TEMP_BUF_ADDR		0x118
#define	BIT_RESET_CTRL			0x11C

#define BIT_RD_PTR			0x120
#define BIT_WR_PTR			0x124

#define BIT_AXI_SRAM_USE                0x140
#define BIT_SEARCH_RAM_BASE_ADDR        0x144
#define BIT_SEARCH_RAM_SIZE             0x148
#define BIT_FRAME_CYCLE             0x14C

#define BIT_FRM_DIS_FLG                 0x150

#define CMD_SET_FRAME_AXI_BIT_ADDR      0x190
#define CMD_SET_FRAME_AXI_IPACDC_ADDR   0x194
#define CMD_SET_FRAME_AXI_DBKY_ADDR     0x198
#define CMD_SET_FRAME_AXI_DBKC_ADDR     0x19C
#define CMD_SET_FRAME_AXI_OVL_ADDR      0x1A0
#define BIT_BYTE_POS_FRAME_START	0x144
#define BIT_BYTE_POS_FRAME_END		0x148

#define BIT_BUSY_FLAG			0x160
#define BIT_RUN_COMMAND			0x164
#define BIT_RUN_INDEX			0x168
#define BIT_RUN_COD_STD			0x16C
#define BIT_INT_ENABLE			0x170
#define BIT_INT_REASON			0x174
#define BIT_RUN_AUX_STD                 0x178

#define BIT_MSG_0			0x1F0
#define BIT_MSG_1			0x1F4

#define BIT_RTC_HOST_CTRL		0x1FC

/*---------------------------------------------------------------------------
 * [DEC SEQ INIT] COMMAND
 *-------------------------------------------------------------------------*/
#define CMD_DEC_SEQ_BB_START		0x180
#define CMD_DEC_SEQ_BB_SIZE		0x184
#define CMD_DEC_SEQ_OPTION		0x188
#define CMD_DEC_SEQ_SRC_SIZE		0x18C
#define CMD_DEC_SEQ_START_BYTE		0x190
#define CMD_DEC_SEQ_PS_BB_START     	0x194   /* dummy for mx6q */
#define CMD_DEC_SEQ_PS_BB_SIZE      	0x198   /* dummy for mx6q */
#define CMD_DEC_SEQ_JPG_THUMB_EN        0x19C
#define CMD_DEC_SEQ_MP4_ASP_CLASS	0x19C
#define CMD_DEC_SEQ_VC1_STREAM_FMT	0x19C
#define CMD_DEC_SEQ_X264_MV_EN		0x19C
#define CMD_DEC_SEQ_SPP_CHUNK_SIZE	0x1A0

#define CMD_DEC_SEQ_INIT_ESCAPE		0x114

#define RET_DEC_SEQ_BIT_RATE            0x1B4   /* MX6Q platform */

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define RET_DEC_SEQ_ASPECT              0x1C8
#else
#define RET_DEC_SEQ_ASPECT              0x1B0
#endif
/* dummy for mx6q */
#define RET_DEC_SEQ_SRC_F_RATE          0x1C8
/* end to here */
#define RET_DEC_SEQ_SUCCESS		0x1C0
#define RET_DEC_SEQ_SRC_FMT		0x1C4
#define RET_DEC_SEQ_SRC_SIZE		0x1C4
#define RET_DEC_SEQ_FRAME_NEED		0x1CC
#define RET_DEC_SEQ_FRAME_DELAY		0x1D0
#define RET_DEC_SEQ_INFO		0x1D4
#define RET_DEC_SEQ_VP8_SCALE_INFO	0x1D4
#define RET_DEC_SEQ_CROP_LEFT_RIGHT	0x1D8
#define RET_DEC_SEQ_CROP_TOP_BOTTOM	0x1DC
#define RET_DEC_SEQ_ERR_REASON		0x1E0
#define RET_DEC_SEQ_FRATE_NR		0x1E4
#define RET_DEC_SEQ_FRATE_DR		0x1E8

#define	RET_DEC_SEQ_JPG_PARA		0x1E4
#define RET_DEC_SEQ_JPG_THUMB_IND	0x1E8
#define RET_DEC_SEQ_HEADER_REPORT	0x1EC

#define RET_DEC_SEQ_NEXT_FRAME_NUM	0x1E0

/*--------------------------------------------------------------------------
 * [ENC SEQ INIT] COMMAND
 *-------------------------------------------------------------------------*/
#define CMD_ENC_SEQ_BB_START		0x180
#define CMD_ENC_SEQ_BB_SIZE		0x184
#define CMD_ENC_SEQ_OPTION		0x188

#define CMD_ENC_SEQ_COD_STD		0x18C
#define CMD_ENC_SEQ_SRC_SIZE		0x190
#define CMD_ENC_SEQ_SRC_F_RATE		0x194
#define CMD_ENC_SEQ_MP4_PARA		0x198
#define CMD_ENC_SEQ_263_PARA		0x19C
#define CMD_ENC_SEQ_264_PARA		0x1A0
#define CMD_ENC_SEQ_SLICE_MODE		0x1A4
#define CMD_ENC_SEQ_GOP_NUM		0x1A8
#define CMD_ENC_SEQ_RC_PARA		0x1AC
#define CMD_ENC_SEQ_RC_BUF_SIZE		0x1B0
#define CMD_ENC_SEQ_INTRA_REFRESH	0x1B4
#define CMD_ENC_SEARCH_BASE		0x1B8
#define CMD_ENC_SEARCH_SIZE		0x1BC

#define CMD_ENC_SEQ_FMO			0x1B8
#define CMD_ENC_SEQ_INTRA_QP		0x1C4

#define CMD_ENC_SEQ_RC_QP_MIN_MAX	0x1C8
#define CMD_ENC_SEQ_RC_GAMMA		0x1CC
#define CMD_ENC_SEQ_RC_INTERVAL_MODE	0x1D0   /* MbInterval[32:2], RcIntervalMode[1:0] */
#define CMD_ENC_SEQ_INTRA_WEIGHT	0x1D4
#define CMD_ENC_SEQ_ME_OPTION		0x1D8

#define CMD_ENC_SEQ_JPG_PARA	        0x198
#define CMD_ENC_SEQ_JPG_RST_INTERVAL	0x19C
#define CMD_ENC_SEQ_JPG_THUMB_EN	0x1A0
#define CMD_ENC_SEQ_JPG_THUMB_SIZE	0x1A4
#define CMD_ENC_SEQ_JPG_THUMB_OFFSET	0x1A8

#define RET_ENC_SEQ_ENC_SUCCESS		0x1C0

/*--------------------------------------------------------------------------
 * [ENC PARA CHANGE] COMMAND :
 *------------------------------------------------------------------------*/
#define CMD_ENC_SEQ_PARA_CHANGE_ENABLE	0x180
#define CMD_ENC_SEQ_PARA_RC_GOP		0x184
#define CMD_ENC_SEQ_PARA_RC_INTRA_QP	0x188
#define CMD_ENC_SEQ_PARA_RC_BITRATE     0x18C
#define CMD_ENC_SEQ_PARA_RC_FRAME_RATE  0x190
#define	CMD_ENC_SEQ_PARA_INTRA_MB_NUM	0x194
#define CMD_ENC_SEQ_PARA_SLICE_MODE	0x198
#define CMD_ENC_SEQ_PARA_HEC_MODE	0x19C

#define RET_ENC_SEQ_PARA_CHANGE_SUCCESS	0x1C0

/*---------------------------------------------------------------------------
 *  [DEC SEQ END] COMMAND
 *-------------------------------------------------------------------------*/
#define RET_DEC_SEQ_END_SUCCESS     (BIT_BASE + 0x1C0)

/*---------------------------------------------------------------------------
 * [DEC PIC RUN] COMMAND
 *-------------------------------------------------------------------------*/
#define CMD_DEC_PIC_ROT_INDEX           0x184   /* MX6Q */
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define CMD_DEC_PIC_ROT_MODE            0x180
#define CMD_DEC_PIC_ROT_ADDR_Y          0x188
#define CMD_DEC_PIC_ROT_ADDR_CB         0x18C
#define CMD_DEC_PIC_ROT_ADDR_CR         0x190
#define CMD_DEC_PIC_ROT_STRIDE          0x1B8
#else
#define CMD_DEC_PIC_ROT_MODE		0x180
#define CMD_DEC_PIC_ROT_ADDR_Y		0x184
#define CMD_DEC_PIC_ROT_ADDR_CB		0x188
#define CMD_DEC_PIC_ROT_ADDR_CR		0x18C
#define CMD_DEC_PIC_ROT_STRIDE          0x190
#endif

#define CMD_DEC_PIC_OPTION		0x194
#define CMD_DEC_PIC_SKIP_NUM		0x198
#define CMD_DEC_PIC_CHUNK_SIZE		0x19C
#define CMD_DEC_PIC_BB_START		0x1A0
#define CMD_DEC_PIC_START_BYTE		0x1A4   /* dummy for mx6q */
#define CMD_DEC_PIC_PARA_BASE_ADDR      0x1A8   /* dummy for mx6q */
#define CMD_DEC_SEQ_USER_DATA_OPTION	0x194
#define CMD_DEC_PIC_USER_DATA_BASE_ADDR 0x1AC
#define CMD_DEC_PIC_USER_DATA_BUF_SIZE  0x1B0
#define CMD_DEC_PIC_DBK_OFFSET		0x1B4

#define CMD_DEC_PIC_THO_PIC_PARA	0x198
#define CMD_DEC_PIC_THO_QMAT_ADDR	0x1A0
#define CMD_DEC_PIC_THO_MB_PARA_ADDR	0x1A4

#define RET_DEC_PIC_AVC_FPA_SEI0	0x19C
#define RET_DEC_PIC_AVC_FPA_SEI1	0x1A0
#define RET_DEC_PIC_AVC_FPA_SEI2	0x1A4

#define RET_DEC_PIC_SIZE		0x1BC
#define RET_DEC_PIC_FRAME_NUM		0x1C0
#define RET_DEC_PIC_FRAME_IDX		0x1C4
#define RET_DEC_PIC_ERR_MB		0x1C8
#define RET_DEC_PIC_TYPE		0x1CC

#define RET_DEC_PIC_POST		0x1D0
#define RET_DEC_PIC_MVC_REPORT		0x1D0

#define RET_DEC_PIC_OPTION		0x1D4
#define RET_DEC_PIC_SUCCESS		0x1D8

#define RET_DEC_PIC_CUR_IDX		0x1DC
#define RET_DEC_PIC_FRAME_NEED		0x1EC

#define RET_DEC_PIC_CROP_LEFT_RIGHT	0x1E0
#define RET_DEC_PIC_CROP_TOP_BOTTOM	0x1E4
#define RET_DEC_PIC_VP8_PIC_REPORT	0x1E8
#define RET_DEC_PIC_ASPECT		0x1F0
#define RET_DEC_PIC_VP8_SCALE_INFO	0x1F0
#define RET_DEC_PIC_FRATE_NR		0x1F4
#define RET_DEC_PIC_FRATE_DR		0x1F8

//------------------------------------------------------------------------------
// [ENC SEQ END] COMMAND
//------------------------------------------------------------------------------
#define RET_ENC_SEQ_END_SUCCESS		0x1C0

/*---------------------------------------------------------------------------
 * [ENC PIC RUN] COMMAND
 *--------------------------------------------------------------------------*/

#define CMD_ENC_PIC_SRC_INDEX           0x180   /* MX6Q */
#define CMD_ENC_PIC_SRC_STRIDE          0x184   /* MX6Q */
#define CMD_ENC_PIC_SUB_FRAME_SYNC      0x1A4   /* MX6Q */
#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define CMD_ENC_PIC_SRC_ADDR_Y          0x1A8
#define CMD_ENC_PIC_SRC_ADDR_CB         0x1AC
#define CMD_ENC_PIC_SRC_ADDR_CR         0x1B0
#else
#define CMD_ENC_PIC_SRC_ADDR_Y          0x180
#define CMD_ENC_PIC_SRC_ADDR_CB         0x184
#define CMD_ENC_PIC_SRC_ADDR_CR         0x188
#endif

#define CMD_ENC_PIC_QS			0x18C
#define CMD_ENC_PIC_ROT_MODE		0x190
#define CMD_ENC_PIC_OPTION		0x194
#define CMD_ENC_PIC_BB_START		0x198
#define CMD_ENC_PIC_BB_SIZE		0x19C
#define CMD_ENC_PIC_PARA_BASE_ADDR	0x1A0

#define RET_ENC_PIC_FRAME_NUM		0x1C0
#define RET_ENC_PIC_TYPE		0x1C4
#define RET_ENC_PIC_FRAME_IDX		0x1C8
#define RET_ENC_PIC_SLICE_NUM		0x1CC
#define RET_ENC_PIC_FLAG		0x1D0
#define RET_ENC_PIC_SUCCESS		0x1D8

#define CMD_SET_FRAME_BUF_NUM		0x180
#define CMD_SET_FRAME_BUF_STRIDE	0x184
#define CMD_SET_FRAME_SLICE_BB_START    0x188
#define CMD_SET_FRAME_SLICE_BB_SIZE     0x18C

#define CMD_SET_FRAME_AXI_BIT_ADDR      0x190
#define CMD_SET_FRAME_AXI_IPACDC_ADDR   0x194
#define CMD_SET_FRAME_AXI_DBKY_ADDR     0x198
#define CMD_SET_FRAME_AXI_DBKC_ADDR     0x19C
#define CMD_SET_FRAME_AXI_OVL_ADDR      0x1A0

/* MX6Q used, others dummy */
#define CMD_SET_FRAME_AXI_BTP_ADDR	0x1A4
#define CMD_SET_FRAME_CACHE_SIZE	0x1A8
#define CMD_SET_FRAME_CACHE_CONFIG	0x1AC
#define CMD_SET_FRAME_MB_BUF_BASE	0x1B0
/* End */

/* MX5X used, others dummy */
#define CMD_SET_FRAME_MAX_DEC_SIZE      0x1A4
#define CMD_SET_FRAME_SOURCE_BUF_STRIDE 0x1A8
/* End */

#define RET_SET_FRAME_SUCCESS		0x1C0

// Magellan ENCODER ONLY
#define CMD_SET_FRAME_SUBSAMP_A		0x188
#define CMD_SET_FRAME_SUBSAMP_B		0x18C
#define CMD_SET_FRAME_DP_BUF_BASE	0x1B0
#define CMD_SET_FRAME_DP_BUF_SIZE	0x1B4
#define CMD_SET_FRAME_SUBSAMP_A_MVC	0x1B0
#define CMD_SET_FRAME_SUBSAMP_B_MVC	0x1B4

/*---------------------------------------------------------------------------
 * [ENC HEADER] COMMAND
 *-------------------------------------------------------------------------*/
#define CMD_ENC_HEADER_CODE		0x180
#define CMD_ENC_HEADER_BB_START		0x184
#define CMD_ENC_HEADER_BB_SIZE		0x188
#define CMD_ENC_HEADER_FRAME_CROP_H	0x18C
#define CMD_ENC_HEADER_FRAME_CROP_V	0x190

#define RET_ENC_HEADER_SUCCESS		0x1C0

/*----------------------------------------------------------------------------
 * [DEC_PARA_SET] COMMAND
 *---------------------------------------------------------------------------*/
#define CMD_DEC_PARA_SET_TYPE		0x180
#define CMD_DEC_PARA_SET_SIZE		0x184
#define RET_DEC_PARA_SET_SUCCESS	0x1C0

/*----------------------------------------------------------------------------
 * [DEC_BUF_FLUSH] COMMAND
 *---------------------------------------------------------------------------*/
#define RET_DEC_BUF_FLUSH_SUCCESS	0x1C0

/*----------------------------------------------------------------------------
 * [ENC_PARA_SET] COMMAND
 *--------------------------------------------------------------------------*/
#define CMD_ENC_PARA_SET_TYPE		0x180
#define RET_ENC_PARA_SET_SIZE		0x1C0
#define RET_ENC_PARA_SET_SUCCESS        0x1C4

/*---------------------------------------------------------------------------
 * [FIRMWARE VERSION] COMMAND
 * [32:16] project number =>
 * [16:0]  version => xxxx.xxxx.xxxxxxxx
 *-------------------------------------------------------------------------*/
#define RET_VER_NUM			0x1C0
#define RET_FW_CODE_REV			0x1C4

#if defined(CHIP_MX6DQ) || defined(CHIP_MX6SDL)
#define CODE_BUF_SIZE                   (240 * 1024)    /* define max is 240k byte currently */
#define FMO_SLICE_SAVE_BUF_SIZE         (32)
#define TEMP_BUF_SIZE                   (200 * 1024)
#define PARA_BUF2_SIZE                  (2 * 1024)
#define PARA_BUF_SIZE                   (10 * 1024)
#else
#error  you must define PLATFORM properly
#endif

/*----------------------------------------------------------------------------
 *---------------------------------------------------------------------------*/
#define BIT_SEL_BE                      0
#define BIT_SEL_64BITS_ENDIAN           1
#define BIT_BUF_CHECK_DIS               2
#define BIT_BUF_PIC_FLUSH               3
#define BIT_BUF_PIC_RESET               4
#define BIT_ENC_DYN_BUFALLOC_EN         5
#define BITS_STREAMCTRL_MASK            0x03F
#define BIT_PIC_WIDTH_OFFSET            16

#define GDI_PRI_RD_PRIO_L           (GDMA_BASE + 0x000)
#define GDI_PRI_RD_PRIO_H           (GDMA_BASE + 0x004)
#define GDI_PRI_WR_PRIO_L           (GDMA_BASE + 0x008)
#define GDI_PRI_WR_PRIO_H           (GDMA_BASE + 0x00c)
#define GDI_PRI_RD_LOCK_CNT         (GDMA_BASE + 0x010)
#define GDI_PRI_WR_LOCK_CNT         (GDMA_BASE + 0x014)
#define GDI_SEC_RD_PRIO_L           (GDMA_BASE + 0x018)
#define GDI_SEC_RD_PRIO_H           (GDMA_BASE + 0x01c)
#define GDI_SEC_WR_PRIO_L           (GDMA_BASE + 0x020)
#define GDI_SEC_WR_PRIO_H           (GDMA_BASE + 0x024)
#define GDI_SEC_RD_LOCK_CNT         (GDMA_BASE + 0x028)
#define GDI_SEC_WR_LOCK_CNT         (GDMA_BASE + 0x02c)
#define GDI_SEC_CLIENT_EN           (GDMA_BASE + 0x030)
#define GDI_CONTROL                 (GDMA_BASE + 0x034)
#define GDI_PIC_INIT_HOST           (GDMA_BASE + 0x038)

#define GDI_PINFO_REQ               (GDMA_BASE + 0x060)
#define GDI_PINFO_ACK               (GDMA_BASE + 0x064)
#define GDI_PINFO_ADDR              (GDMA_BASE + 0x068)
#define GDI_PINFO_DATA              (GDMA_BASE + 0x06c)
#define GDI_BWB_ENABLE              (GDMA_BASE + 0x070)
#define GDI_BWB_SIZE                (GDMA_BASE + 0x074)
#define GDI_BWB_STD_STRUCT          (GDMA_BASE + 0x078)
#define GDI_BWB_STATUS              (GDMA_BASE + 0x07c)

#define GDI_STATUS                  (GDMA_BASE + 0x080)

#define GDI_DEBUG_0                 (GDMA_BASE + 0x084)
#define GDI_DEBUG_1                 (GDMA_BASE + 0x088)
#define GDI_DEBUG_2                 (GDMA_BASE + 0x08c)
#define GDI_DEBUG_3                 (GDMA_BASE + 0x090)
#define GDI_DEBUG_PROBE_ADDR        (GDMA_BASE + 0x094)
#define GDI_DEBUG_PROBE_DATA        (GDMA_BASE + 0x098)

// write protect
#define GDI_WPROT_ERR_CLR	    (GDMA_BASE + 0x0A0)
#define GDI_WPROT_ERR_RSN	    (GDMA_BASE + 0x0A4)
#define GDI_WPROT_ERR_ADR	    (GDMA_BASE + 0x0A8)
#define GDI_WPROT_RGN_EN	    (GDMA_BASE + 0x0AC)
#define GDI_WPROT_RGN0_STA	    (GDMA_BASE + 0x0B0)
#define GDI_WPROT_RGN0_END	    (GDMA_BASE + 0x0B4)
#define GDI_WPROT_RGN1_STA	    (GDMA_BASE + 0x0B8)
#define GDI_WPROT_RGN1_END	    (GDMA_BASE + 0x0BC)
#define GDI_WPROT_RGN2_STA	    (GDMA_BASE + 0x0C0)
#define GDI_WPROT_RGN2_END	    (GDMA_BASE + 0x0C4)
#define GDI_WPROT_RGN3_STA	    (GDMA_BASE + 0x0C8)
#define GDI_WPROT_RGN3_END	    (GDMA_BASE + 0x0CC)
#define GDI_WPROT_RGN4_STA	    (GDMA_BASE + 0x0D0)
#define GDI_WPROT_RGN4_END	    (GDMA_BASE + 0x0D4)
#define GDI_WPROT_RGN5_STA	    (GDMA_BASE + 0x0D8)
#define GDI_WPROT_RGN5_END	    (GDMA_BASE + 0x0DC)

#define GDI_BUS_CTRL                (GDMA_BASE + 0x0F0)
#define GDI_BUS_STATUS              (GDMA_BASE + 0x0F4)

#define GDI_SIZE_ERR_FLAG           (GDMA_BASE + 0x0E0)
#define GDI_INFO_CONTROL            (GDMA_BASE + 0x400)
#define GDI_INFO_PIC_SIZE           (GDMA_BASE + 0x404)
#define GDI_INFO_BASE_Y             (GDMA_BASE + 0x408)
#define GDI_INFO_BASE_CB            (GDMA_BASE + 0x40C)
#define GDI_INFO_BASE_CR            (GDMA_BASE + 0x410)

#define GDI_XY2_CAS_0               (GDMA_BASE + 0x800)
#define GDI_XY2_CAS_F               (GDMA_BASE + 0x83C)

#define GDI_XY2_BA_0                (GDMA_BASE + 0x840)
#define GDI_XY2_BA_1                (GDMA_BASE + 0x844)
#define GDI_XY2_BA_2                (GDMA_BASE + 0x848)
#define GDI_XY2_BA_3                (GDMA_BASE + 0x84C)

#define GDI_XY2_RAS_0               (GDMA_BASE + 0x850)
#define GDI_XY2_RAS_F               (GDMA_BASE + 0x88C)

#define GDI_XY2_RBC_CONFIG          (GDMA_BASE + 0x890)
#define GDI_RBC2_AXI_0              (GDMA_BASE + 0x8A0)
#define GDI_RBC2_AXI_1F             (GDMA_BASE + 0x91C)
#define GDI_TILEDBUF_BASE           (GDMA_BASE + 0x920)

/*--------------------------------------------------------------------
NIEUPORT REGISTERS
--------------------------------------------------------------------*/
// MBC
#define MJPEG_PIC_START_REG	 (NPT_BASE + 0x000) // [0] - pic start
#define MJPEG_PIC_STATUS_REG	 (NPT_BASE + 0x004) // [3] - overflow, [2] - bbc interrupt, [1] - error, [0] - done
#define MJPEG_PIC_ERRMB_REG	 (NPT_BASE + 0x008) // [27:24] - error restart idx, [23:12] - error MCU pos X, [11:0] - error MCU pos Y
#define MJPEG_PIC_SETMB_REG	 (NPT_BASE + 0x00C) // [27:16] - MCU pos X, [11:0] - MCU pos Y

#define MJPEG_PIC_CTRL_REG	 (NPT_BASE + 0x010) // [6] - user huffman en, [4] - TC direction, [3] - encoder enable, [1:0] - operation mode
#define MJPEG_PIC_SIZE_REG	 (NPT_BASE + 0x014)
#define MJPEG_MCU_INFO_REG	 (NPT_BASE + 0x018)
#define MJPEG_ROT_INFO_REG	 (NPT_BASE + 0x01C) // [4] - rot-mir enable, [3:0] - rot-mir mode

#define MJPEG_SCL_INFO_REG	 (NPT_BASE + 0x020)
#define MJPEG_IF_INFO_REG	 (NPT_BASE + 0x024) // [1] - sensor interface clear, [0] - display interface clear
#define MJPEG_OP_INFO_REG	 (NPT_BASE + 0x02C) // [31:16] - # of line in 1 partial buffer, [5:3] - # of partial buffers [2:0] - # of request

#define MJPEG_DPB_CONFIG_REG     (NPT_BASE + 0x030)
#define MJPEG_WRESP_CHECK_REG    (NPT_BASE + 0x034)

#define MJPEG_DPB_BASE00_REG	 (NPT_BASE + 0x040)
#define MJPEG_DPB_BASE10_REG	 (NPT_BASE + 0x044)
#define MJPEG_DPB_BASE20_REG	 (NPT_BASE + 0x048)
#define MJPEG_DPB_BASE30_REG	 (NPT_BASE + 0x04C)

#define MJPEG_HUFF_CTRL_REG	 (NPT_BASE + 0x080)
#define MJPEG_HUFF_ADDR_REG	 (NPT_BASE + 0x084)
#define MJPEG_HUFF_DATA_REG	 (NPT_BASE + 0x088)

#define MJPEG_QMAT_CTRL_REG	 (NPT_BASE + 0x090)
#define MJPEG_QMAT_ADDR_REG	 (NPT_BASE + 0x094)
#define MJPEG_QMAT_DATA_REG	 (NPT_BASE + 0x098)

#define MJPEG_COEF_CTRL_REG	 (NPT_BASE + 0x0A0)
#define MJPEG_COEF_ADDR_REG	 (NPT_BASE + 0x0A4)
#define MJPEG_COEF_DATA_REG	 (NPT_BASE + 0x0A8)

#define MJPEG_RST_INTVAL_REG	 (NPT_BASE + 0x0B0)
#define MJPEG_RST_INDEX_REG	 (NPT_BASE + 0x0B4)
#define MJPEG_RST_COUNT_REG	 (NPT_BASE + 0x0B8)

#define	MJPEG_INTR_MASK_REG	 (NPT_BASE + 0x0C0)
#define MJPEG_CYCLE_INFO_REG	 (NPT_BASE + 0x0C8)

#define MJPEG_DPCM_DIFF_Y_REG	 (NPT_BASE + 0x0F0)
#define MJPEG_DPCM_DIFF_CB_REG	 (NPT_BASE + 0x0F4)
#define MJPEG_DPCM_DIFF_CR_REG	 (NPT_BASE + 0x0F8)

// GBU
#define MJPEG_GBU_CTRL_REG	 (NPT_BASE + 0x100)

#define MJPEG_GBU_BT_PTR_REG	 (NPT_BASE + 0x110)
#define MJPEG_GBU_WD_PTR_REG	 (NPT_BASE + 0x114)
#define MJPEG_GBU_TT_CNT_REG	 (NPT_BASE + 0x118)
//#define MJPEG_GBU_TT_CNT_REG+4    (NPT_BASE + 0x11C)

#define MJPEG_GBU_BBSR_REG	 (NPT_BASE + 0x140)
#define MJPEG_GBU_BBER_REG	 (NPT_BASE + 0x144)
#define MJPEG_GBU_BBIR_REG	 (NPT_BASE + 0x148)
#define MJPEG_GBU_BBHR_REG	 (NPT_BASE + 0x14C)

#define MJPEG_GBU_BCNT_REG	 (NPT_BASE + 0x158)

#define MJPEG_GBU_FF_RPTR_REG	 (NPT_BASE + 0x160)
#define MJPEG_GBU_FF_WPTR_REG	 (NPT_BASE + 0x164)

// BBC
#define MJPEG_BBC_END_ADDR_REG	 (NPT_BASE + 0x208)
#define MJPEG_BBC_WR_PTR_REG	 (NPT_BASE + 0x20C)
#define MJPEG_BBC_RD_PTR_REG	 (NPT_BASE + 0x210)

#define MJPEG_BBC_EXT_ADDR_REG	 (NPT_BASE + 0x214)
#define MJPEG_BBC_INT_ADDR_REG	 (NPT_BASE + 0x218)
#define MJPEG_BBC_DATA_CNT_REG	 (NPT_BASE + 0x21C)
#define MJPEG_BBC_COMMAND_REG	 (NPT_BASE + 0x220)
#define MJPEG_BBC_BUSY_REG	 (NPT_BASE + 0x224)

#define MJPEG_BBC_CTRL_REG	 (NPT_BASE + 0x228)
#define MJPEG_BBC_CUR_POS_REG	 (NPT_BASE + 0x22C)

#define MJPEG_BBC_BAS_ADDR_REG	 (NPT_BASE + 0x230)
#define MJPEG_BBC_STRM_CTRL_REG	 (NPT_BASE + 0x234)

//! @}

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////#define MJPEG_BBC_FLUSH_CMD_REG  (NPT_BASE + 0x238)

/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MIPI_DSI_H
#define HPM_MIPI_DSI_H

typedef struct {
    __R  uint32_t VERSION;                     /* 0x0: version */
    __RW uint32_t PWR_UP;                      /* 0x4: power up */
    __RW uint32_t CLKMGR_CFG;                  /* 0x8: divide lanebyteclk for timeout */
    __RW uint32_t DPI_VCID;                    /* 0xC: virtual channel ID for DPI traffic */
    __RW uint32_t DPI_COLOR_CODING;            /* 0x10: dpi color coding */
    __RW uint32_t DPI_CFG_POL;                 /* 0x14: the polarity of DPI signals */
    __RW uint32_t DPI_LP_CMD_TIM;              /* 0x18: the timing for low-power commands sent while in video mode */
    __R  uint8_t  RESERVED0[16];               /* 0x1C - 0x2B: Reserved */
    __RW uint32_t PCKHDL_CFG;                  /* 0x2C: configures how EoTp, BTA, CRC and ECC to be used */
    __RW uint32_t GEN_VCID;                    /* 0x30: configures the virtual channel ID of read response to store and return to generic interface */
    __RW uint32_t MODE_CFG;                    /* 0x34: configures the mode of operation between video or command mode */
    __RW uint32_t VID_MODE_CFG;                /* 0x38: several aspect of video mode operation */
    __RW uint32_t VID_PKT_SIZE;                /* 0x3C: configures the video packet size */
    __RW uint32_t VID_NUM_CHUNKS;              /* 0x40: configures the number of chunks to use */
    __RW uint32_t VID_NULL_SIZE;               /* 0x44: configures the size of null packets */
    __RW uint32_t VID_HSA_TIME;                /* 0x48: configures the video HAS time */
    __RW uint32_t VID_HBP_TIME;                /* 0x4C: configure the video HBP time */
    __RW uint32_t VID_HLINE_TIME;              /* 0x50: configures the overall time for each video line */
    __RW uint32_t VID_VSA_LINES;               /* 0x54: configures the vsa period */
    __RW uint32_t VID_VBP_LINES;               /* 0x58: configures the vbp period */
    __RW uint32_t VID_VFP_LINES;               /* 0x5C: configures the vfp period */
    __RW uint32_t VID_VACTIVE_LINES;           /* 0x60: configures the vertical resolution of video */
    __R  uint8_t  RESERVED1[4];                /* 0x64 - 0x67: Reserved */
    __RW uint32_t CMD_MODE_CFG;                /* 0x68: This register configures several aspect of command mode operation, tearing effect, acknowledge for each packet and the speed mode to transmit each Data Type related to commands. */
    __RW uint32_t GEN_HDR;                     /* 0x6C: sets the header for new packets sent using the generic interface */
    __RW uint32_t GEN_PLD_DATA;                /* 0x70: sets the payload for packets sent using the generic interface */
    __R  uint32_t CMD_PKT_STATUS;              /* 0x74: information about the status of FIFOs related to DBI and Generic interface */
    __RW uint32_t TO_CNT_CFG;                  /* 0x78: configures the trigger timeout errors */
    __RW uint32_t HS_RD_TO_CNT;                /* 0x7C: configures the peripheral response timeout after high speed read operations */
    __RW uint32_t LP_RD_TO_CNT;                /* 0x80: configures the peripheral response timeout after low-power read operation */
    __RW uint32_t HS_WR_TO_CNT;                /* 0x84: configures the peripheral response timeout after high speed write operations */
    __RW uint32_t LP_WR_TO_CNT;                /* 0x88: configures the peripheral response timeout after low power write operations */
    __RW uint32_t BTA_TO_CNT;                  /* 0x8C: configures the periphera response timeout after bus turnaround */
    __RW uint32_t SDF_3D;                      /* 0x90: sotres 3d control information for vss packets in video mode */
    __RW uint32_t LPCLK_CTRL;                  /* 0x94: configures the possibility for using non continuous clock in the clock lane */
    __RW uint32_t PHY_TMR_LPCLK_CFG;           /* 0x98: sets the time that dsi host assumes in calculations for the clock lane to switch between high-speed and low-power */
    __RW uint32_t PHY_TMR_CFG;                 /* 0x9C: sets the time that dsi host assumes in calculations for data lanes to switch between hs to lp */
    __RW uint32_t PHY_RSTZ;                    /* 0xA0: controls resets and the pll of d-phy */
    __RW uint32_t PHY_IF_CFG;                  /* 0xA4: configures the number of active lanes */
    __RW uint32_t PHY_ULPS_CTRL;               /* 0xA8: configures entering and leaving ulps */
    __RW uint32_t PHY_TX_TRIGGERS;             /* 0xAC: configures the pins that activate triggers in the d-phy */
    __R  uint32_t PHY_STATUS;                  /* 0xB0: contains information about the status of the d-phy */
    __RW uint32_t PHY_TST_CTRL0;               /* 0xB4: controls clock and clear pins of the d-phy vendor specific interface */
    __RW uint32_t PHY_TST_CTRL1;               /* 0xB8: controls data and enable pins of the d-phy */
    __R  uint32_t INT_ST0;                     /* 0xBC: controls the status of interrupt */
    __R  uint32_t INT_ST1;                     /* 0xC0: the interrupt source related to timeout etc */
    __RW uint32_t INT_MSK0;                    /* 0xC4: configures masks for the sources of interrupt that affec int_st0 */
    __RW uint32_t INT_MSK1;                    /* 0xC8: configures masks for int_st1 */
    __RW uint32_t PHY_CAL;                     /* 0xCC: controls the skew calibration of D-phy */
    __R  uint8_t  RESERVED2[8];                /* 0xD0 - 0xD7: Reserved */
    __RW uint32_t INT_FORCE0;                  /* 0xD8: forces that affect the int_st0 register */
    __RW uint32_t INT_FORCE1;                  /* 0xDC: forces interrupts that affect the int_st1 register */
    __R  uint8_t  RESERVED3[20];               /* 0xE0 - 0xF3: Reserved */
    __RW uint32_t PHY_TMR_RD;                  /* 0xF4: configures times related to PHY to perform some operations in lane byte clock cycle */
    __RW uint32_t AUTO_ULPS_MIN_TIME;          /* 0xF8: configures the minimum time required by phy between ulpsactivenot and ulpsexitreq for clock and data lane */
    __RW uint32_t PHY_MODE;                    /* 0xFC: select phy mode */
    __RW uint32_t VID_SHADOW_CTRL;             /* 0x100: controls dpi shadow feature */
    __R  uint8_t  RESERVED4[8];                /* 0x104 - 0x10B: Reserved */
    __R  uint32_t DPI_VCID_ACT;                /* 0x10C: holds the value that controller is using for DPI_VCID */
    __R  uint32_t DPI_COLOR_CODING_ACT;        /* 0x110: holds the value that controller is using for DPI_COLOR_CODING */
    __R  uint8_t  RESERVED5[4];                /* 0x114 - 0x117: Reserved */
    __R  uint32_t DPI_LP_CMD_TIM_ACT;          /* 0x118: holds value that controller is using for dpi_lp_cmd_time */
    __R  uint8_t  RESERVED6[28];               /* 0x11C - 0x137: Reserved */
    __R  uint32_t VID_MODE_CFG_ACT;            /* 0x138: holds value that controller is using for vid_mode_cfg */
    __R  uint32_t VID_PKT_SIZE_ACT;            /* 0x13C: holds value that controller is using for vid_pkt_size */
    __R  uint32_t VID_NUM_CHUNKS_ACT;          /* 0x140: holds value that controller is using for vid_num_chunks */
    __R  uint32_t VID_NULL_SIZE_ACT;           /* 0x144: holds the value that controller is using for vid_null_size */
    __R  uint32_t VID_HSA_TIME_ACT;            /* 0x148: the value of vid_hsa_time */
    __R  uint32_t VID_HBP_TIME_ACT;            /* 0x14C: the value that controller is using for vid_hbp_time */
    __R  uint32_t VID_HLINE_TIME_ACT;          /* 0x150: the value for vid_hline_time */
    __R  uint32_t VID_VSA_LINES_ACT;           /* 0x154: value for vid_vsa_lines */
    __R  uint32_t VID_VBP_LINES_ACT;           /* 0x158: value for vid_vbp_lines */
    __R  uint32_t VID_VFP_LINES_ACT;           /* 0x15C: value for vid_vfp_lines */
    __R  uint32_t VID_VACTIVE_LINES_ACT;       /* 0x160: value for vid_vactive_lines */
    __R  uint8_t  RESERVED7[4];                /* 0x164 - 0x167: Reserved */
    __R  uint32_t VID_PKT_STATUS;              /* 0x168: status of fifo related to dpi */
    __R  uint8_t  RESERVED8[36];               /* 0x16C - 0x18F: Reserved */
    __R  uint32_t SDF_3D_ACT;                  /* 0x190: value for sdf_3d */
} MIPI_DSI_Type;


/* Bitfield definition for register: VERSION */
/*
 * VERSION (RO)
 *
 * version of DSI
 */
#define MIPI_DSI_VERSION_VERSION_MASK (0xFFFFFFFFUL)
#define MIPI_DSI_VERSION_VERSION_SHIFT (0U)
#define MIPI_DSI_VERSION_VERSION_GET(x) (((uint32_t)(x) & MIPI_DSI_VERSION_VERSION_MASK) >> MIPI_DSI_VERSION_VERSION_SHIFT)

/* Bitfield definition for register: PWR_UP */
/*
 * SHUTDOWNZ (RW)
 *
 * 0x0: reset the core
 * 0x1: power up the core
 */
#define MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK (0x1U)
#define MIPI_DSI_PWR_UP_SHUTDOWNZ_SHIFT (0U)
#define MIPI_DSI_PWR_UP_SHUTDOWNZ_SET(x) (((uint32_t)(x) << MIPI_DSI_PWR_UP_SHUTDOWNZ_SHIFT) & MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK)
#define MIPI_DSI_PWR_UP_SHUTDOWNZ_GET(x) (((uint32_t)(x) & MIPI_DSI_PWR_UP_SHUTDOWNZ_MASK) >> MIPI_DSI_PWR_UP_SHUTDOWNZ_SHIFT)

/* Bitfield definition for register: CLKMGR_CFG */
/*
 * TO_CLK_DIVISION (RW)
 *
 * the timeout clock division factor for HS to LP and LP to HS transition error
 */
#define MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_MASK (0xFF00U)
#define MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_SHIFT (8U)
#define MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_SET(x) (((uint32_t)(x) << MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_SHIFT) & MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_MASK)
#define MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_GET(x) (((uint32_t)(x) & MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_MASK) >> MIPI_DSI_CLKMGR_CFG_TO_CLK_DIVISION_SHIFT)

/*
 * TX_ESC_CLK_DIVISION (RW)
 *
 * the division factor for the TX Escape clock source lanebyteclk
 */
#define MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_MASK (0xFFU)
#define MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SHIFT (0U)
#define MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SET(x) (((uint32_t)(x) << MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SHIFT) & MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_MASK)
#define MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_GET(x) (((uint32_t)(x) & MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_MASK) >> MIPI_DSI_CLKMGR_CFG_TX_ESC_CLK_DIVISION_SHIFT)

/* Bitfield definition for register: DPI_VCID */
/*
 * DPI_VCID (RW)
 *
 * the DPI virtual channel id to the video mode packets
 */
#define MIPI_DSI_DPI_VCID_DPI_VCID_MASK (0x3U)
#define MIPI_DSI_DPI_VCID_DPI_VCID_SHIFT (0U)
#define MIPI_DSI_DPI_VCID_DPI_VCID_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_VCID_DPI_VCID_SHIFT) & MIPI_DSI_DPI_VCID_DPI_VCID_MASK)
#define MIPI_DSI_DPI_VCID_DPI_VCID_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_VCID_DPI_VCID_MASK) >> MIPI_DSI_DPI_VCID_DPI_VCID_SHIFT)

/* Bitfield definition for register: DPI_COLOR_CODING */
/*
 * LOOSELY18_EN (RW)
 *
 * when set to 1, this bit activates loosely packed variant to 18-bit configurations
 */
#define MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_MASK (0x100U)
#define MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_SHIFT (8U)
#define MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_SHIFT) & MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_MASK)
#define MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_MASK) >> MIPI_DSI_DPI_COLOR_CODING_LOOSELY18_EN_SHIFT)

/*
 * DPI_COLOR_CODING (RW)
 *
 * configures the DPI color for video mode
 */
#define MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_MASK (0xFU)
#define MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SHIFT (0U)
#define MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SHIFT) & MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_MASK)
#define MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_MASK) >> MIPI_DSI_DPI_COLOR_CODING_DPI_COLOR_CODING_SHIFT)

/* Bitfield definition for register: DPI_CFG_POL */
/*
 * COLORM_ACTIVE_LOW (RW)
 *
 * configures the color mode pin as active low
 */
#define MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_MASK (0x10U)
#define MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SHIFT (4U)
#define MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SHIFT) & MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_MASK)
#define MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_MASK) >> MIPI_DSI_DPI_CFG_POL_COLORM_ACTIVE_LOW_SHIFT)

/*
 * SHUTD_ACTIVE_LOW (RW)
 *
 * configures the shutdown pin as active low
 */
#define MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_MASK (0x8U)
#define MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SHIFT (3U)
#define MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SHIFT) & MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_MASK)
#define MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_MASK) >> MIPI_DSI_DPI_CFG_POL_SHUTD_ACTIVE_LOW_SHIFT)

/*
 * HSYNC_ACTIVE_LOW (RW)
 *
 * configures the horizontal synchronism pin as active low
 */
#define MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_MASK (0x4U)
#define MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SHIFT (2U)
#define MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SHIFT) & MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_MASK)
#define MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_MASK) >> MIPI_DSI_DPI_CFG_POL_HSYNC_ACTIVE_LOW_SHIFT)

/*
 * VSYNC_ACTIVE_LOW (RW)
 *
 * configures the vertical synchronism pin as active low
 */
#define MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_MASK (0x2U)
#define MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SHIFT (1U)
#define MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SHIFT) & MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_MASK)
#define MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_MASK) >> MIPI_DSI_DPI_CFG_POL_VSYNC_ACTIVE_LOW_SHIFT)

/*
 * DATAEN_ACTIVE_LOW (RW)
 *
 * configures the data enable pin active low
 */
#define MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_MASK (0x1U)
#define MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SHIFT (0U)
#define MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SHIFT) & MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_MASK)
#define MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_MASK) >> MIPI_DSI_DPI_CFG_POL_DATAEN_ACTIVE_LOW_SHIFT)

/* Bitfield definition for register: DPI_LP_CMD_TIM */
/*
 * OUTVACT_LPCMD_TIME (RW)
 *
 * transmission of commands in low-power mode, defines the size in bytes of the largest pachet that can fit in a line during the VSA VBP and VFP;
 */
#define MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_MASK (0xFF0000UL)
#define MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SHIFT (16U)
#define MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SHIFT) & MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_MASK)
#define MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_MASK) >> MIPI_DSI_DPI_LP_CMD_TIM_OUTVACT_LPCMD_TIME_SHIFT)

/*
 * INVACT_LPCMD_TIME (RW)
 *
 * transmission of commands in low-power mode, defines the size in bytes of the largest packet that can fit in a line during the VACT region.
 */
#define MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_MASK (0xFFU)
#define MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SHIFT (0U)
#define MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SHIFT) & MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_MASK)
#define MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_MASK) >> MIPI_DSI_DPI_LP_CMD_TIM_INVACT_LPCMD_TIME_SHIFT)

/* Bitfield definition for register: PCKHDL_CFG */
/*
 * EOTP_TX_LP_EN (RW)
 *
 * enable the EoTp transmission in low-power
 */
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_MASK (0x20U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_SHIFT (5U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_EOTP_TX_LP_EN_SHIFT)

/*
 * CRC_RX_EN (RW)
 *
 * enable the crc reception and error reporting
 */
#define MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_MASK (0x10U)
#define MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_SHIFT (4U)
#define MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_CRC_RX_EN_SHIFT)

/*
 * ECC_RX_EN (RW)
 *
 * enable the ecc reception error correction and reporting
 */
#define MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_MASK (0x8U)
#define MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_SHIFT (3U)
#define MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_ECC_RX_EN_SHIFT)

/*
 * BTA_EN (RW)
 *
 * enable the bus turn-around request
 */
#define MIPI_DSI_PCKHDL_CFG_BTA_EN_MASK (0x4U)
#define MIPI_DSI_PCKHDL_CFG_BTA_EN_SHIFT (2U)
#define MIPI_DSI_PCKHDL_CFG_BTA_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_BTA_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_BTA_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_BTA_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_BTA_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_BTA_EN_SHIFT)

/*
 * EOTP_RX_EN (RW)
 *
 * enable the EoTp reception
 */
#define MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_MASK (0x2U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_SHIFT (1U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_EOTP_RX_EN_SHIFT)

/*
 * EOTP_TX_EN (RW)
 *
 * enable the EoTp transmission in high-speed
 */
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_MASK (0x1U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_SHIFT (0U)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_SHIFT) & MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_MASK)
#define MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_MASK) >> MIPI_DSI_PCKHDL_CFG_EOTP_TX_EN_SHIFT)

/* Bitfield definition for register: GEN_VCID */
/*
 * GEN_VCID_TX_AUTO (RW)
 *
 * indicates the generic interface virtual channel identification where generic packet is automatically generated and transmitted
 */
#define MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_MASK (0x30000UL)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_SHIFT (16U)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_SHIFT) & MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_MASK)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_MASK) >> MIPI_DSI_GEN_VCID_GEN_VCID_TX_AUTO_SHIFT)

/*
 * GEN_VCID_TEAR_AUTO (RW)
 *
 * indicates the virtual channel identification for tear effect by hardware
 */
#define MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_MASK (0x300U)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_SHIFT (8U)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_SHIFT) & MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_MASK)
#define MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_MASK) >> MIPI_DSI_GEN_VCID_GEN_VCID_TEAR_AUTO_SHIFT)

/*
 * GEN_VCID_RX (RW)
 *
 * indicates the generic interface read-back virtual channel identication
 */
#define MIPI_DSI_GEN_VCID_GEN_VCID_RX_MASK (0x3U)
#define MIPI_DSI_GEN_VCID_GEN_VCID_RX_SHIFT (0U)
#define MIPI_DSI_GEN_VCID_GEN_VCID_RX_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_VCID_GEN_VCID_RX_SHIFT) & MIPI_DSI_GEN_VCID_GEN_VCID_RX_MASK)
#define MIPI_DSI_GEN_VCID_GEN_VCID_RX_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_VCID_GEN_VCID_RX_MASK) >> MIPI_DSI_GEN_VCID_GEN_VCID_RX_SHIFT)

/* Bitfield definition for register: MODE_CFG */
/*
 * CMD_VIDEO_MODE (RW)
 *
 * 0x0: video mode
 * 0x1: command mode
 */
#define MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_MASK (0x1U)
#define MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SHIFT (0U)
#define MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SET(x) (((uint32_t)(x) << MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SHIFT) & MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_MASK)
#define MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_GET(x) (((uint32_t)(x) & MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_MASK) >> MIPI_DSI_MODE_CFG_CMD_VIDEO_MODE_SHIFT)

/* Bitfield definition for register: VID_MODE_CFG */
/*
 * VPG_ORIENTATION (RW)
 *
 * indicates the color bar orientation :
 * 0x0: vertical mode
 * 0x1: horizontal mode
 */
#define MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_MASK (0x1000000UL)
#define MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_SHIFT (24U)
#define MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_SHIFT) & MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_MASK)
#define MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_MASK) >> MIPI_DSI_VID_MODE_CFG_VPG_ORIENTATION_SHIFT)

/*
 * VPG_MODE (RW)
 *
 * 0x0: colorbar
 * 0x1: berpattern, vertical only
 */
#define MIPI_DSI_VID_MODE_CFG_VPG_MODE_MASK (0x100000UL)
#define MIPI_DSI_VID_MODE_CFG_VPG_MODE_SHIFT (20U)
#define MIPI_DSI_VID_MODE_CFG_VPG_MODE_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_VPG_MODE_SHIFT) & MIPI_DSI_VID_MODE_CFG_VPG_MODE_MASK)
#define MIPI_DSI_VID_MODE_CFG_VPG_MODE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_VPG_MODE_MASK) >> MIPI_DSI_VID_MODE_CFG_VPG_MODE_SHIFT)

/*
 * VPG_EN (RW)
 *
 * enable video mode pattern generator
 */
#define MIPI_DSI_VID_MODE_CFG_VPG_EN_MASK (0x10000UL)
#define MIPI_DSI_VID_MODE_CFG_VPG_EN_SHIFT (16U)
#define MIPI_DSI_VID_MODE_CFG_VPG_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_VPG_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_VPG_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_VPG_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_VPG_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_VPG_EN_SHIFT)

/*
 * LP_CMD_EN (RW)
 *
 * enable command transmission only in low-power mode
 */
#define MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_MASK (0x8000U)
#define MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_SHIFT (15U)
#define MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_CMD_EN_SHIFT)

/*
 * FRAME_BTA_ACK_EN (RW)
 *
 * enable the request for an acknowledge response at the end of a frame
 */
#define MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_MASK (0x4000U)
#define MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SHIFT (14U)
#define MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_FRAME_BTA_ACK_EN_SHIFT)

/*
 * LP_HFP_EN (RW)
 *
 * enable the return to low-power inside the HFP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_MASK (0x2000U)
#define MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_SHIFT (13U)
#define MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_HFP_EN_SHIFT)

/*
 * LP_HBP_EN (RW)
 *
 * enable the return to low-power inside the HBP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_MASK (0x1000U)
#define MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_SHIFT (12U)
#define MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_HBP_EN_SHIFT)

/*
 * LP_VACT_EN (RW)
 *
 * enable the return to low-power inside the VACT period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_MASK (0x800U)
#define MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_SHIFT (11U)
#define MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_VACT_EN_SHIFT)

/*
 * LP_VFP_EN (RW)
 *
 * enable the return to low-power inside the VFP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_MASK (0x400U)
#define MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_SHIFT (10U)
#define MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_VFP_EN_SHIFT)

/*
 * LP_VBP_EN (RW)
 *
 * enable the return to low-power inside the VBP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_MASK (0x200U)
#define MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_SHIFT (9U)
#define MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_VBP_EN_SHIFT)

/*
 * LP_VSA_EN (RW)
 *
 * enable the return to low-power inside the VSA period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_MASK (0x100U)
#define MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_SHIFT (8U)
#define MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_SHIFT) & MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_MASK)
#define MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_LP_VSA_EN_SHIFT)

/*
 * VID_MODE_TYPE (RW)
 *
 * indicates the video mode transmission type
 */
#define MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_MASK (0x3U)
#define MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_SHIFT (0U)
#define MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_SHIFT) & MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_MASK)
#define MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_MASK) >> MIPI_DSI_VID_MODE_CFG_VID_MODE_TYPE_SHIFT)

/* Bitfield definition for register: VID_PKT_SIZE */
/*
 * VID_PKT_SIZE (RW)
 *
 * configures the number of pixels in a single video packet
 */
#define MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_MASK (0x3FFFU)
#define MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_SHIFT (0U)
#define MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_SHIFT) & MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_MASK)
#define MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_MASK) >> MIPI_DSI_VID_PKT_SIZE_VID_PKT_SIZE_SHIFT)

/* Bitfield definition for register: VID_NUM_CHUNKS */
/*
 * VID_NUM_CHUNKS (RW)
 *
 * configures the number of chunks to be transmitted a line period
 */
#define MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_MASK (0x1FFFU)
#define MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SHIFT (0U)
#define MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SHIFT) & MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_MASK)
#define MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_MASK) >> MIPI_DSI_VID_NUM_CHUNKS_VID_NUM_CHUNKS_SHIFT)

/* Bitfield definition for register: VID_NULL_SIZE */
/*
 * VID_NULL_SIZE (RW)
 *
 * configures the number of bytes inside a null packet
 */
#define MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_MASK (0x1FFFU)
#define MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_SHIFT (0U)
#define MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_SHIFT) & MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_MASK)
#define MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_MASK) >> MIPI_DSI_VID_NULL_SIZE_VID_NULL_SIZE_SHIFT)

/* Bitfield definition for register: VID_HSA_TIME */
/*
 * VID_HSA_TIME (RW)
 *
 * configure the Horizontal synchronism active period in lane byte clock cycles
 */
#define MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_MASK (0xFFFU)
#define MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_SHIFT) & MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_MASK)
#define MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_MASK) >> MIPI_DSI_VID_HSA_TIME_VID_HSA_TIME_SHIFT)

/* Bitfield definition for register: VID_HBP_TIME */
/*
 * VID_HPB_TIME (RW)
 *
 * configures the Horizontal back porch period in lane byte clock cycles
 */
#define MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_MASK (0xFFFU)
#define MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_SHIFT) & MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_MASK)
#define MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_MASK) >> MIPI_DSI_VID_HBP_TIME_VID_HPB_TIME_SHIFT)

/* Bitfield definition for register: VID_HLINE_TIME */
/*
 * VID_HLINE_TIME (RW)
 *
 * configures the size of the total line time in lane byte clock cycles
 */
#define MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_MASK (0x7FFFU)
#define MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_SHIFT) & MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_MASK)
#define MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_MASK) >> MIPI_DSI_VID_HLINE_TIME_VID_HLINE_TIME_SHIFT)

/* Bitfield definition for register: VID_VSA_LINES */
/*
 * VSA_LINES (RW)
 *
 * configures the verical synchronism active period measured in number of horizontal lines
 */
#define MIPI_DSI_VID_VSA_LINES_VSA_LINES_MASK (0x3FFU)
#define MIPI_DSI_VID_VSA_LINES_VSA_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VSA_LINES_VSA_LINES_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_VSA_LINES_VSA_LINES_SHIFT) & MIPI_DSI_VID_VSA_LINES_VSA_LINES_MASK)
#define MIPI_DSI_VID_VSA_LINES_VSA_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VSA_LINES_VSA_LINES_MASK) >> MIPI_DSI_VID_VSA_LINES_VSA_LINES_SHIFT)

/* Bitfield definition for register: VID_VBP_LINES */
/*
 * VBP_LINES (RW)
 *
 * configures the vertical back porch period measured in number of horizontal lines
 */
#define MIPI_DSI_VID_VBP_LINES_VBP_LINES_MASK (0x3FFU)
#define MIPI_DSI_VID_VBP_LINES_VBP_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VBP_LINES_VBP_LINES_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_VBP_LINES_VBP_LINES_SHIFT) & MIPI_DSI_VID_VBP_LINES_VBP_LINES_MASK)
#define MIPI_DSI_VID_VBP_LINES_VBP_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VBP_LINES_VBP_LINES_MASK) >> MIPI_DSI_VID_VBP_LINES_VBP_LINES_SHIFT)

/* Bitfield definition for register: VID_VFP_LINES */
/*
 * VFP_LINIES (RW)
 *
 * configures the vertical front porch period measured in number of horizontal lines
 */
#define MIPI_DSI_VID_VFP_LINES_VFP_LINIES_MASK (0x3FFU)
#define MIPI_DSI_VID_VFP_LINES_VFP_LINIES_SHIFT (0U)
#define MIPI_DSI_VID_VFP_LINES_VFP_LINIES_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_VFP_LINES_VFP_LINIES_SHIFT) & MIPI_DSI_VID_VFP_LINES_VFP_LINIES_MASK)
#define MIPI_DSI_VID_VFP_LINES_VFP_LINIES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VFP_LINES_VFP_LINIES_MASK) >> MIPI_DSI_VID_VFP_LINES_VFP_LINIES_SHIFT)

/* Bitfield definition for register: VID_VACTIVE_LINES */
/*
 * V_ACTIVE_LINES (RW)
 *
 * configures the vertical active period measured in number of horizontal lines
 */
#define MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_MASK (0x3FFFU)
#define MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SHIFT) & MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_MASK)
#define MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_MASK) >> MIPI_DSI_VID_VACTIVE_LINES_V_ACTIVE_LINES_SHIFT)

/* Bitfield definition for register: CMD_MODE_CFG */
/*
 * MAX_RD_PKT_SIZE (RW)
 *
 * This bit configures the maximum read packet size command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_MASK (0x1000000UL)
#define MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SHIFT (24U)
#define MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SHIFT) & MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_MASK)
#define MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_MASK) >> MIPI_DSI_CMD_MODE_CFG_MAX_RD_PKT_SIZE_SHIFT)

/*
 * DCS_LW_TX (RW)
 *
 * This bit configures the DCS long write packet command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_MASK (0x80000UL)
#define MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_SHIFT (19U)
#define MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_DCS_LW_TX_SHIFT)

/*
 * DCS_SR_0P_TX (RW)
 *
 * This bit configures the DCS short read packet with zero parameter command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_MASK (0x40000UL)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SHIFT (18U)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_DCS_SR_0P_TX_SHIFT)

/*
 * DCS_SW_1P_TX (RW)
 *
 * This bit configures the DCS short write packet with one parameter command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_MASK (0x20000UL)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SHIFT (17U)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_DCS_SW_1P_TX_SHIFT)

/*
 * DCS_SW_0P_TX (RW)
 *
 * This bit configures the DCS short write packet with zero parameter command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_MASK (0x10000UL)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SHIFT (16U)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_DCS_SW_0P_TX_SHIFT)

/*
 * GEN_LW_TX (RW)
 *
 * This bit configures the Generic long write packet command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_MASK (0x4000U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_SHIFT (14U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_LW_TX_SHIFT)

/*
 * GEN_SR_2P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_MASK (0x2000U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SHIFT (13U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SR_2P_TX_SHIFT)

/*
 * GEN_SR_1P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_MASK (0x1000U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SHIFT (12U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SR_1P_TX_SHIFT)

/*
 * GEN_SR_0P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_MASK (0x800U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SHIFT (11U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SR_0P_TX_SHIFT)

/*
 * GEN_SW_2P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_MASK (0x400U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SHIFT (10U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SW_2P_TX_SHIFT)

/*
 * GEN_SW_1P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_MASK (0x200U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SHIFT (9U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SW_1P_TX_SHIFT)

/*
 * GEN_SW_0P_TX (RW)
 *
 * This bit configures the Generic short read packet with two parameters command transmission type:
 * 0x0 (HIGHSPEED): Transition type is High Speed
 * 0x1 (LOWPOWER): Transition type is Low Power
 */
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_MASK (0x100U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SHIFT (8U)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SHIFT) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_MASK)
#define MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_MASK) >> MIPI_DSI_CMD_MODE_CFG_GEN_SW_0P_TX_SHIFT)

/*
 * ACK_RQST_EN (RW)
 *
 * When set to 1, this bit enables the acknowledge request after each packet transmission.
 */
#define MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_MASK (0x2U)
#define MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_SHIFT (1U)
#define MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_SHIFT) & MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_MASK)
#define MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_MASK) >> MIPI_DSI_CMD_MODE_CFG_ACK_RQST_EN_SHIFT)

/*
 * TEAR_FX_EN (RW)
 *
 * When set to 1, this bit enables the tearing effect acknowledge request.
 */
#define MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_MASK (0x1U)
#define MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_SHIFT (0U)
#define MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_SHIFT) & MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_MASK)
#define MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_MASK) >> MIPI_DSI_CMD_MODE_CFG_TEAR_FX_EN_SHIFT)

/* Bitfield definition for register: GEN_HDR */
/*
 * GEN_WC_MSBYTE (RW)
 *
 * configures the most significant byte of the header packet's word count for long packets or data 1 for shout packets
 */
#define MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_MASK (0xFF0000UL)
#define MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_SHIFT (16U)
#define MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_SHIFT) & MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_MASK)
#define MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_MASK) >> MIPI_DSI_GEN_HDR_GEN_WC_MSBYTE_SHIFT)

/*
 * GEN_WC_LSBYTE (RW)
 *
 * configures the least significant byte of the header packet's word count for long packets or data0 for short packets
 */
#define MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_MASK (0xFF00U)
#define MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_SHIFT (8U)
#define MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_SHIFT) & MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_MASK)
#define MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_MASK) >> MIPI_DSI_GEN_HDR_GEN_WC_LSBYTE_SHIFT)

/*
 * GEN_VC (RW)
 *
 * configures the virtual channel ID of the header packet
 */
#define MIPI_DSI_GEN_HDR_GEN_VC_MASK (0xC0U)
#define MIPI_DSI_GEN_HDR_GEN_VC_SHIFT (6U)
#define MIPI_DSI_GEN_HDR_GEN_VC_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_HDR_GEN_VC_SHIFT) & MIPI_DSI_GEN_HDR_GEN_VC_MASK)
#define MIPI_DSI_GEN_HDR_GEN_VC_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_HDR_GEN_VC_MASK) >> MIPI_DSI_GEN_HDR_GEN_VC_SHIFT)

/*
 * GEN_DT (RW)
 *
 * configures the packet data type of the header packet
 */
#define MIPI_DSI_GEN_HDR_GEN_DT_MASK (0x3FU)
#define MIPI_DSI_GEN_HDR_GEN_DT_SHIFT (0U)
#define MIPI_DSI_GEN_HDR_GEN_DT_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_HDR_GEN_DT_SHIFT) & MIPI_DSI_GEN_HDR_GEN_DT_MASK)
#define MIPI_DSI_GEN_HDR_GEN_DT_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_HDR_GEN_DT_MASK) >> MIPI_DSI_GEN_HDR_GEN_DT_SHIFT)

/* Bitfield definition for register: GEN_PLD_DATA */
/*
 * GEN_PLD_B4 (RW)
 *
 * indicates byte4 of the packet payload
 */
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_MASK (0xFF000000UL)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_SHIFT (24U)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_SHIFT) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_MASK)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_MASK) >> MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B4_SHIFT)

/*
 * GEN_PLD_B3 (RW)
 *
 * indicates byte3 of the packet payload
 */
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_MASK (0xFF0000UL)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_SHIFT (16U)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_SHIFT) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_MASK)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_MASK) >> MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B3_SHIFT)

/*
 * GEN_PLD_B2 (RW)
 *
 * indicates byte2 of the packet payload
 */
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_MASK (0xFF00U)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_SHIFT (8U)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_SHIFT) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_MASK)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_MASK) >> MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B2_SHIFT)

/*
 * GEN_PLD_B1 (RW)
 *
 * indicates byte1 of the packet payload
 */
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_MASK (0xFFU)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_SHIFT (0U)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_SET(x) (((uint32_t)(x) << MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_SHIFT) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_MASK)
#define MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_GET(x) (((uint32_t)(x) & MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_MASK) >> MIPI_DSI_GEN_PLD_DATA_GEN_PLD_B1_SHIFT)

/* Bitfield definition for register: CMD_PKT_STATUS */
/*
 * GEN_BUFF_PLD_FULL (R)
 *
 * the full status of the generic payload internal buffer
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_FULL_MASK (0x80000UL)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_FULL_SHIFT (19U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_FULL_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_FULL_SHIFT)

/*
 * GEN_BUFF_PLD_EMPTY (R)
 *
 * the empty status of the generic payload internal buffer
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_EMPTY_MASK (0x40000UL)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_EMPTY_SHIFT (18U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_EMPTY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_PLD_EMPTY_SHIFT)

/*
 * GEN_BUFF_CMD_FULL (R)
 *
 * the full status of the generic command internal buffer
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_FULL_MASK (0x20000UL)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_FULL_SHIFT (17U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_FULL_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_FULL_SHIFT)

/*
 * GEN_BUFF_CMD_EMPTY (R)
 *
 * the empty status of the generic command internal buffer
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_EMPTY_MASK (0x10000UL)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_EMPTY_SHIFT (16U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_EMPTY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_BUFF_CMD_EMPTY_SHIFT)

/*
 * GEN_RD_CMD_BUSY (R)
 *
 * indicates a read command is issued and the entire response is not sotred in the FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_MASK (0x40U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_SHIFT (6U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_RD_CMD_BUSY_SHIFT)

/*
 * GEN_PLD_R_FULL (R)
 *
 * indicates the full status of the generic read payoad FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_MASK (0x20U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_SHIFT (5U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_FULL_SHIFT)

/*
 * GEN_PLD_R_EMPTY (R)
 *
 * indicates the empty status of the generic read payload FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_MASK (0x10U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_SHIFT (4U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_R_EMPTY_SHIFT)

/*
 * GEN_PLD_W_FULL (R)
 *
 * indicates the full status of the generic write payload FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_MASK (0x8U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_SHIFT (3U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_FULL_SHIFT)

/*
 * GEN_PLD_W_EMPTY (R)
 *
 * indicates the empty status of the generic write payload FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_MASK (0x4U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_SHIFT (2U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_PLD_W_EMPTY_SHIFT)

/*
 * GEN_CMD_FULL (R)
 *
 * indicates the full status of the generic command FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_MASK (0x2U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_SHIFT (1U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_FULL_SHIFT)

/*
 * GEN_CMD_EMPTY (R)
 *
 * indicates the empty status of the generic command FIFO
 */
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_MASK (0x1U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_SHIFT (0U)
#define MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_MASK) >> MIPI_DSI_CMD_PKT_STATUS_GEN_CMD_EMPTY_SHIFT)

/* Bitfield definition for register: TO_CNT_CFG */
/*
 * HSTX_TO_CNT (RW)
 *
 * configures the timeout counter that triggers a high speed transmission timeout contention detection
 */
#define MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_MASK (0xFFFF0000UL)
#define MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_SHIFT (16U)
#define MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_SHIFT) & MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_MASK)
#define MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_MASK) >> MIPI_DSI_TO_CNT_CFG_HSTX_TO_CNT_SHIFT)

/*
 * LPRX_TO_CNT (RW)
 *
 * configures the timeout counter that triggers a low power reception timeout contention detection
 */
#define MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_SHIFT (0U)
#define MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_SHIFT) & MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_MASK)
#define MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_MASK) >> MIPI_DSI_TO_CNT_CFG_LPRX_TO_CNT_SHIFT)

/* Bitfield definition for register: HS_RD_TO_CNT */
/*
 * HS_RD_TO_CNT (RW)
 *
 * sets a period for which DWC_mipi_dsi_host keeps the link still after sending a high speed read operation;
 */
#define MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SHIFT (0U)
#define MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SHIFT) & MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_MASK)
#define MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_MASK) >> MIPI_DSI_HS_RD_TO_CNT_HS_RD_TO_CNT_SHIFT)

/* Bitfield definition for register: LP_RD_TO_CNT */
/*
 * LP_RD_TO_CNT (RW)
 *
 * sets a period for which dwc_mipi_dsi_host keeps the link still after sending a low power read operation
 */
#define MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SHIFT (0U)
#define MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SHIFT) & MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_MASK)
#define MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_MASK) >> MIPI_DSI_LP_RD_TO_CNT_LP_RD_TO_CNT_SHIFT)

/* Bitfield definition for register: HS_WR_TO_CNT */
/*
 * HS_WR_TO_CNT (RW)
 *
 * sets the period for which dwc_mipi_dsi_host keeps the link still after sending a high speed write operation
 */
#define MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SHIFT (0U)
#define MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SHIFT) & MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_MASK)
#define MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_MASK) >> MIPI_DSI_HS_WR_TO_CNT_HS_WR_TO_CNT_SHIFT)

/* Bitfield definition for register: LP_WR_TO_CNT */
/*
 * LP_WR_TO_CNT (RW)
 *
 * sets the period for which dsi host keeps the link still after sending a low power write operation
 */
#define MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SHIFT (0U)
#define MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SHIFT) & MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_MASK)
#define MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_MASK) >> MIPI_DSI_LP_WR_TO_CNT_LP_WR_TO_CNT_SHIFT)

/* Bitfield definition for register: BTA_TO_CNT */
/*
 * BTA_TO_CNT (RW)
 *
 * sets the period for which dsi host keeps the link still after completing a bus turnaround.
 */
#define MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_MASK (0xFFFFU)
#define MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_SHIFT (0U)
#define MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_SET(x) (((uint32_t)(x) << MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_SHIFT) & MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_MASK)
#define MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_GET(x) (((uint32_t)(x) & MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_MASK) >> MIPI_DSI_BTA_TO_CNT_BTA_TO_CNT_SHIFT)

/* Bitfield definition for register: SDF_3D */
/*
 * SEND_3D_CFG (RW)
 *
 * set the next vss packet to include 3d control payload in every vss packet
 */
#define MIPI_DSI_SDF_3D_SEND_3D_CFG_MASK (0x10000UL)
#define MIPI_DSI_SDF_3D_SEND_3D_CFG_SHIFT (16U)
#define MIPI_DSI_SDF_3D_SEND_3D_CFG_SET(x) (((uint32_t)(x) << MIPI_DSI_SDF_3D_SEND_3D_CFG_SHIFT) & MIPI_DSI_SDF_3D_SEND_3D_CFG_MASK)
#define MIPI_DSI_SDF_3D_SEND_3D_CFG_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_SEND_3D_CFG_MASK) >> MIPI_DSI_SDF_3D_SEND_3D_CFG_SHIFT)

/*
 * RIGHT_FIRST (RW)
 *
 * 0x0: left eye is sent first
 * 0x1:right eye is sent first
 */
#define MIPI_DSI_SDF_3D_RIGHT_FIRST_MASK (0x20U)
#define MIPI_DSI_SDF_3D_RIGHT_FIRST_SHIFT (5U)
#define MIPI_DSI_SDF_3D_RIGHT_FIRST_SET(x) (((uint32_t)(x) << MIPI_DSI_SDF_3D_RIGHT_FIRST_SHIFT) & MIPI_DSI_SDF_3D_RIGHT_FIRST_MASK)
#define MIPI_DSI_SDF_3D_RIGHT_FIRST_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_RIGHT_FIRST_MASK) >> MIPI_DSI_SDF_3D_RIGHT_FIRST_SHIFT)

/*
 * SECOND_VSYNC (RW)
 *
 * defines whether there is a second VSYNC pulse
 */
#define MIPI_DSI_SDF_3D_SECOND_VSYNC_MASK (0x10U)
#define MIPI_DSI_SDF_3D_SECOND_VSYNC_SHIFT (4U)
#define MIPI_DSI_SDF_3D_SECOND_VSYNC_SET(x) (((uint32_t)(x) << MIPI_DSI_SDF_3D_SECOND_VSYNC_SHIFT) & MIPI_DSI_SDF_3D_SECOND_VSYNC_MASK)
#define MIPI_DSI_SDF_3D_SECOND_VSYNC_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_SECOND_VSYNC_MASK) >> MIPI_DSI_SDF_3D_SECOND_VSYNC_SHIFT)

/*
 * FORMAT_3D (RW)
 *
 * defines 3D image format
 */
#define MIPI_DSI_SDF_3D_FORMAT_3D_MASK (0xCU)
#define MIPI_DSI_SDF_3D_FORMAT_3D_SHIFT (2U)
#define MIPI_DSI_SDF_3D_FORMAT_3D_SET(x) (((uint32_t)(x) << MIPI_DSI_SDF_3D_FORMAT_3D_SHIFT) & MIPI_DSI_SDF_3D_FORMAT_3D_MASK)
#define MIPI_DSI_SDF_3D_FORMAT_3D_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_FORMAT_3D_MASK) >> MIPI_DSI_SDF_3D_FORMAT_3D_SHIFT)

/*
 * MODE_3D (RW)
 *
 * defines 3D mode on/off
 */
#define MIPI_DSI_SDF_3D_MODE_3D_MASK (0x3U)
#define MIPI_DSI_SDF_3D_MODE_3D_SHIFT (0U)
#define MIPI_DSI_SDF_3D_MODE_3D_SET(x) (((uint32_t)(x) << MIPI_DSI_SDF_3D_MODE_3D_SHIFT) & MIPI_DSI_SDF_3D_MODE_3D_MASK)
#define MIPI_DSI_SDF_3D_MODE_3D_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_MODE_3D_MASK) >> MIPI_DSI_SDF_3D_MODE_3D_SHIFT)

/* Bitfield definition for register: LPCLK_CTRL */
/*
 * AUTO_CLKLANE_CTRL (RW)
 *
 * enables the automatic mechanism to stop providing clock in the clock lane
 */
#define MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_MASK (0x2U)
#define MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SHIFT (1U)
#define MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SET(x) (((uint32_t)(x) << MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SHIFT) & MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_MASK)
#define MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_GET(x) (((uint32_t)(x) & MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_MASK) >> MIPI_DSI_LPCLK_CTRL_AUTO_CLKLANE_CTRL_SHIFT)

/*
 * PHY_TXREQUESTCLKHS (RW)
 *
 * controls the D-PHY PPI txrequestclkhs signal
 */
#define MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK (0x1U)
#define MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SHIFT (0U)
#define MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SET(x) (((uint32_t)(x) << MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SHIFT) & MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK)
#define MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_GET(x) (((uint32_t)(x) & MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_MASK) >> MIPI_DSI_LPCLK_CTRL_PHY_TXREQUESTCLKHS_SHIFT)

/* Bitfield definition for register: PHY_TMR_LPCLK_CFG */
/*
 * PHY_CLKHS2LP_TIME (RW)
 *
 * configures the maximum time that the d-phy clock lane takes to go from high-speed to low-power transmission
 */
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_MASK (0x3FF0000UL)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SHIFT (16U)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SHIFT) & MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_MASK)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_MASK) >> MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKHS2LP_TIME_SHIFT)

/*
 * PHY_CLKLP2HS_TIME (RW)
 *
 * configures the maximum time that the d-phy clock lane takes to go from low-power to high-speed transmission
 */
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_MASK (0x3FFU)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SHIFT (0U)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SHIFT) & MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_MASK)
#define MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_MASK) >> MIPI_DSI_PHY_TMR_LPCLK_CFG_PHY_CLKLP2HS_TIME_SHIFT)

/* Bitfield definition for register: PHY_TMR_CFG */
/*
 * PHY_HS2LP_TIME (RW)
 *
 * This field configures the maximum time that the D-PHY data
 * lanes take to go from high-speed to low-power transmission
 * measured in lane byte clock cycles
 */
#define MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_MASK (0x3FF0000UL)
#define MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SHIFT (16U)
#define MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SHIFT) & MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_MASK)
#define MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_MASK) >> MIPI_DSI_PHY_TMR_CFG_PHY_HS2LP_TIME_SHIFT)

/*
 * PHY_LP2HS_TIME (RW)
 *
 * This field configures the maximum time that the D-PHY data
 * lanes take to go from low-power to high-speed transmission
 * measured in lane byte clock cycles.
 */
#define MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_MASK (0x3FFU)
#define MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SHIFT (0U)
#define MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SHIFT) & MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_MASK)
#define MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_MASK) >> MIPI_DSI_PHY_TMR_CFG_PHY_LP2HS_TIME_SHIFT)

/* Bitfield definition for register: PHY_RSTZ */
/*
 * PHY_FORCEPLL (RW)
 *
 * when the d-phy is in ulps, enable the d-phy pll
 */
#define MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_MASK (0x8U)
#define MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_SHIFT (3U)
#define MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_SHIFT) & MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_MASK)
#define MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_MASK) >> MIPI_DSI_PHY_RSTZ_PHY_FORCEPLL_SHIFT)

/*
 * PHY_ENABLECLK (RW)
 *
 * enable dphy clock lane
 */
#define MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_MASK (0x4U)
#define MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_SHIFT (2U)
#define MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_SHIFT) & MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_MASK)
#define MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_MASK) >> MIPI_DSI_PHY_RSTZ_PHY_ENABLECLK_SHIFT)

/*
 * PHY_RSTZ (RW)
 *
 * make the dphy in reset state when set to 0
 */
#define MIPI_DSI_PHY_RSTZ_PHY_RSTZ_MASK (0x2U)
#define MIPI_DSI_PHY_RSTZ_PHY_RSTZ_SHIFT (1U)
#define MIPI_DSI_PHY_RSTZ_PHY_RSTZ_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RSTZ_PHY_RSTZ_SHIFT) & MIPI_DSI_PHY_RSTZ_PHY_RSTZ_MASK)
#define MIPI_DSI_PHY_RSTZ_PHY_RSTZ_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RSTZ_PHY_RSTZ_MASK) >> MIPI_DSI_PHY_RSTZ_PHY_RSTZ_SHIFT)

/*
 * PHY_SHUTDOWNZ (RW)
 *
 * places the dphy macro in power down mode when set to 0
 */
#define MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK (0x1U)
#define MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SHIFT (0U)
#define MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SHIFT) & MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK)
#define MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_MASK) >> MIPI_DSI_PHY_RSTZ_PHY_SHUTDOWNZ_SHIFT)

/* Bitfield definition for register: PHY_IF_CFG */
/*
 * PHY_STOP_WAIT_TIME (RW)
 *
 * configures the minimum time phy needs to stay in stopstate before requesting an highspeed transmission
 */
#define MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_MASK (0xFF00U)
#define MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SHIFT (8U)
#define MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SHIFT) & MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_MASK)
#define MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_MASK) >> MIPI_DSI_PHY_IF_CFG_PHY_STOP_WAIT_TIME_SHIFT)

/*
 * N_LANES (RW)
 *
 * configures the number of active data lanes
 */
#define MIPI_DSI_PHY_IF_CFG_N_LANES_MASK (0x3U)
#define MIPI_DSI_PHY_IF_CFG_N_LANES_SHIFT (0U)
#define MIPI_DSI_PHY_IF_CFG_N_LANES_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_IF_CFG_N_LANES_SHIFT) & MIPI_DSI_PHY_IF_CFG_N_LANES_MASK)
#define MIPI_DSI_PHY_IF_CFG_N_LANES_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_IF_CFG_N_LANES_MASK) >> MIPI_DSI_PHY_IF_CFG_N_LANES_SHIFT)

/* Bitfield definition for register: PHY_ULPS_CTRL */
/*
 * PHY_TXEXITULPSLAN (RW)
 *
 * ulps mode exit on all active data lanes
 */
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_MASK (0x8U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_SHIFT (3U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_SHIFT) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_MASK)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_MASK) >> MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN_SHIFT)

/*
 * PHY_TXREQULPSLAN (RW)
 *
 * ulps mode request on all active data lanes
 */
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_MASK (0x4U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_SHIFT (2U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_SHIFT) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_MASK)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_MASK) >> MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSLAN_SHIFT)

/*
 * PHY_TXEXITULPSCLK (RW)
 *
 * ulps mode exit on clock lane
 */
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_MASK (0x2U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_SHIFT (1U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_SHIFT) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_MASK)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_MASK) >> MIPI_DSI_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK_SHIFT)

/*
 * PHY_TXREQULPSCLK (RW)
 *
 * ulps mode request on clock lane
 */
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_MASK (0x1U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_SHIFT (0U)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_SHIFT) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_MASK)
#define MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_MASK) >> MIPI_DSI_PHY_ULPS_CTRL_PHY_TXREQULPSCLK_SHIFT)

/* Bitfield definition for register: PHY_TX_TRIGGERS */
/*
 * PHY_TX_TRIGGERS (RW)
 *
 * controls the trigger transmissions
 */
#define MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_MASK (0xFU)
#define MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_SHIFT (0U)
#define MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_SHIFT) & MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_MASK)
#define MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_MASK) >> MIPI_DSI_PHY_TX_TRIGGERS_PHY_TX_TRIGGERS_SHIFT)

/* Bitfield definition for register: PHY_STATUS */
/*
 * PHY_ULPSACTIVENOT3LANE (R)
 *
 * indicates the status of ulpsactivenot3lane d-phy signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_MASK (0x1000U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_SHIFT (12U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT3LANE_SHIFT)

/*
 * PHY_STOPSTATE3LANE (R)
 *
 * This bit indicates the status of phystopstate3lane D-PHY
 * signal.
 */
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE3LANE_MASK (0x800U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE3LANE_SHIFT (11U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE3LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_STOPSTATE3LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_STOPSTATE3LANE_SHIFT)

/*
 * PHY_ULPSACTIVENOT2LANE (R)
 *
 * This bit indicates the status of ulpsactivenot2lane D-PHY
 * signa
 */
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_MASK (0x400U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_SHIFT (10U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT2LANE_SHIFT)

/*
 * PHY_STOPSTATE2LANE (R)
 *
 * This bit indicates the status of phystopstate2lane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE2LANE_MASK (0x200U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE2LANE_SHIFT (9U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE2LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_STOPSTATE2LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_STOPSTATE2LANE_SHIFT)

/*
 * PHY_ULPSACTIVENOT1LANE (R)
 *
 * This bit indicates the status of ulpsactivenot1lane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_MASK (0x100U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_SHIFT (8U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT1LANE_SHIFT)

/*
 * PHY_STOPSTATE1LANE (R)
 *
 * This bit indicates the status of phystopstate1lane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE1LANE_MASK (0x80U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE1LANE_SHIFT (7U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE1LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_STOPSTATE1LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_STOPSTATE1LANE_SHIFT)

/*
 * PHY_RXULPSESC0LANE (R)
 *
 * This bit indicates the status of rxulpsesc0lane D-PHY signa
 */
#define MIPI_DSI_PHY_STATUS_PHY_RXULPSESC0LANE_MASK (0x40U)
#define MIPI_DSI_PHY_STATUS_PHY_RXULPSESC0LANE_SHIFT (6U)
#define MIPI_DSI_PHY_STATUS_PHY_RXULPSESC0LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_RXULPSESC0LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_RXULPSESC0LANE_SHIFT)

/*
 * PHY_ULPSACTIVENOT0LANE (R)
 *
 * This bit indicates the status of ulpsactivenot0lane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_MASK (0x20U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_SHIFT (5U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOT0LANE_SHIFT)

/*
 * PHY_STOPSTATE0LANE (R)
 *
 * This bit indicates the status of phystopstate0lane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE0LANE_MASK (0x10U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE0LANE_SHIFT (4U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATE0LANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_STOPSTATE0LANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_STOPSTATE0LANE_SHIFT)

/*
 * PHY_ULPSACTIVENOTCLK (R)
 *
 * This bit indicates the status of phyulpsactivenotclk D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_MASK (0x8U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_SHIFT (3U)
#define MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_MASK) >> MIPI_DSI_PHY_STATUS_PHY_ULPSACTIVENOTCLK_SHIFT)

/*
 * PHY_STOPSTATECLKLANE (R)
 *
 * This bit indicates the status of phystopstateclklane D-PHY
 * signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATECLKLANE_MASK (0x4U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATECLKLANE_SHIFT (2U)
#define MIPI_DSI_PHY_STATUS_PHY_STOPSTATECLKLANE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_STOPSTATECLKLANE_MASK) >> MIPI_DSI_PHY_STATUS_PHY_STOPSTATECLKLANE_SHIFT)

/*
 * PHY_DIRECTION (R)
 *
 * This bit indicates the status of phydirection D-PHY signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_DIRECTION_MASK (0x2U)
#define MIPI_DSI_PHY_STATUS_PHY_DIRECTION_SHIFT (1U)
#define MIPI_DSI_PHY_STATUS_PHY_DIRECTION_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_DIRECTION_MASK) >> MIPI_DSI_PHY_STATUS_PHY_DIRECTION_SHIFT)

/*
 * PHY_LOCK (R)
 *
 * This bit indicates the status of phylock D-PHY signal
 */
#define MIPI_DSI_PHY_STATUS_PHY_LOCK_MASK (0x1U)
#define MIPI_DSI_PHY_STATUS_PHY_LOCK_SHIFT (0U)
#define MIPI_DSI_PHY_STATUS_PHY_LOCK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_STATUS_PHY_LOCK_MASK) >> MIPI_DSI_PHY_STATUS_PHY_LOCK_SHIFT)

/* Bitfield definition for register: PHY_TST_CTRL0 */
/*
 * PHY_TESTCLK (RW)
 *
 * reserve
 */
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_MASK (0x2U)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_SHIFT (1U)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_SHIFT) & MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_MASK)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_MASK) >> MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLK_SHIFT)

/*
 * PHY_TESTCLR (RW)
 *
 * reserve
 */
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_MASK (0x1U)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_SHIFT (0U)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_SHIFT) & MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_MASK)
#define MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_MASK) >> MIPI_DSI_PHY_TST_CTRL0_PHY_TESTCLR_SHIFT)

/* Bitfield definition for register: PHY_TST_CTRL1 */
/*
 * PHY_TESTEN (RW)
 *
 * reserve
 */
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_MASK (0x10000UL)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_SHIFT (16U)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_SHIFT) & MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_MASK)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_MASK) >> MIPI_DSI_PHY_TST_CTRL1_PHY_TESTEN_SHIFT)

/*
 * PHY_TESTDOUT (R)
 *
 * reserve
 */
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDOUT_MASK (0xFF00U)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDOUT_SHIFT (8U)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDOUT_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDOUT_MASK) >> MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDOUT_SHIFT)

/*
 * PHY_TESTDIN (RW)
 *
 * reserve
 */
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_MASK (0xFFU)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_SHIFT (0U)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_SHIFT) & MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_MASK)
#define MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_MASK) >> MIPI_DSI_PHY_TST_CTRL1_PHY_TESTDIN_SHIFT)

/* Bitfield definition for register: INT_ST0 */
/*
 * DPHY_ERRORS_4 (R)
 *
 * indicates LP1 contention error ErrContentionLP1 from lane0
 */
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_4_MASK (0x100000UL)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_4_SHIFT (20U)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_DPHY_ERRORS_4_MASK) >> MIPI_DSI_INT_ST0_DPHY_ERRORS_4_SHIFT)

/*
 * DPHY_ERRORS_3 (R)
 *
 * indicates LP0 contention error ErrContentionLP0 from lane0
 */
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_3_MASK (0x80000UL)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_3_SHIFT (19U)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_DPHY_ERRORS_3_MASK) >> MIPI_DSI_INT_ST0_DPHY_ERRORS_3_SHIFT)

/*
 * DPHY_ERRORS_2 (R)
 *
 * indicates control error ErrControl from lane0
 */
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_2_MASK (0x40000UL)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_2_SHIFT (18U)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_DPHY_ERRORS_2_MASK) >> MIPI_DSI_INT_ST0_DPHY_ERRORS_2_SHIFT)

/*
 * DPHY_ERRORS_1 (R)
 *
 * indicates ErrSyncEsc low-power data transmission synchronization error from lane 0
 */
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_1_MASK (0x20000UL)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_1_SHIFT (17U)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_DPHY_ERRORS_1_MASK) >> MIPI_DSI_INT_ST0_DPHY_ERRORS_1_SHIFT)

/*
 * DPHY_ERRORS_0 (R)
 *
 * indicates ErrEsc escape entry error from lane0
 */
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_0_MASK (0x10000UL)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_0_SHIFT (16U)
#define MIPI_DSI_INT_ST0_DPHY_ERRORS_0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_DPHY_ERRORS_0_MASK) >> MIPI_DSI_INT_ST0_DPHY_ERRORS_0_SHIFT)

/*
 * ACK_WITH_ERR_15 (R)
 *
 * retrives the DSI protocal violation from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_15_MASK (0x8000U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_15_SHIFT (15U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_15_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_15_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_15_SHIFT)

/*
 * ACK_WITH_ERR_14 (R)
 *
 * retrives the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_14_MASK (0x4000U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_14_SHIFT (14U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_14_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_14_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_14_SHIFT)

/*
 * ACK_WITH_ERR_13 (R)
 *
 * retrives the invalid transmission length from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_13_MASK (0x2000U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_13_SHIFT (13U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_13_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_13_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_13_SHIFT)

/*
 * ACK_WITH_ERR_12 (R)
 *
 * retrieves the dsi vc id invalid from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_12_MASK (0x1000U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_12_SHIFT (12U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_12_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_12_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_12_SHIFT)

/*
 * ACK_WITH_ERR_11 (R)
 *
 * retrives the not recongnized dsi data type from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_11_MASK (0x800U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_11_SHIFT (11U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_11_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_11_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_11_SHIFT)

/*
 * ACK_WITH_ERR_10 (R)
 *
 * retrives the checksum error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_10_MASK (0x400U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_10_SHIFT (10U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_10_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_10_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_10_SHIFT)

/*
 * ACK_WITH_ERR_9 (R)
 *
 * retrives the ECC error multi-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_9_MASK (0x200U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_9_SHIFT (9U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR_9_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR_9_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR_9_SHIFT)

/*
 * ACK_WITH_ERR8 (R)
 *
 * retrives the ecc error sigle-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR8_MASK (0x100U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR8_SHIFT (8U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR8_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR8_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR8_SHIFT)

/*
 * ACK_WITH_ERR7 (R)
 *
 * retrieves the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR7_MASK (0x80U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR7_SHIFT (7U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR7_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR7_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR7_SHIFT)

/*
 * ACK_WITH_ERR6 (R)
 *
 * retrieves the false control error fro the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR6_MASK (0x40U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR6_SHIFT (6U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR6_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR6_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR6_SHIFT)

/*
 * ACK_WITH_ERR5 (R)
 *
 * retrives the peripheral timeout error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR5_MASK (0x20U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR5_SHIFT (5U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR5_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR5_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR5_SHIFT)

/*
 * ACK_WITH_ERR4 (R)
 *
 * retrives the LP transmit sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR4_MASK (0x10U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR4_SHIFT (4U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR4_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR4_SHIFT)

/*
 * ACK_WITH_ERR3 (R)
 *
 * retrives the Escap mode entry command error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR3_MASK (0x8U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR3_SHIFT (3U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR3_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR3_SHIFT)

/*
 * ACK_WITH_ERR2 (R)
 *
 * retrives the EoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR2_MASK (0x4U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR2_SHIFT (2U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR2_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR2_SHIFT)

/*
 * ACK_WITH_ERR1 (R)
 *
 * retrives the SoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR1_MASK (0x2U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR1_SHIFT (1U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR1_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR1_SHIFT)

/*
 * ACK_WITH_ERR0 (R)
 *
 * retrives the SoT serror from the acknowledge error report
 */
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR0_MASK (0x1U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR0_SHIFT (0U)
#define MIPI_DSI_INT_ST0_ACK_WITH_ERR0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST0_ACK_WITH_ERR0_MASK) >> MIPI_DSI_INT_ST0_ACK_WITH_ERR0_SHIFT)

/* Bitfield definition for register: INT_ST1 */
/*
 * TEAR_REQUEST_ERR (R)
 *
 * indicates tear_request has occurred but tear effect is not active in dsi host and device
 */
#define MIPI_DSI_INT_ST1_TEAR_REQUEST_ERR_MASK (0x100000UL)
#define MIPI_DSI_INT_ST1_TEAR_REQUEST_ERR_SHIFT (20U)
#define MIPI_DSI_INT_ST1_TEAR_REQUEST_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_TEAR_REQUEST_ERR_MASK) >> MIPI_DSI_INT_ST1_TEAR_REQUEST_ERR_SHIFT)

/*
 * DPI_BUFF_PLD_UNDER (R)
 *
 * indicates an underflow when reading payload to build dsi packet for video mode
 */
#define MIPI_DSI_INT_ST1_DPI_BUFF_PLD_UNDER_MASK (0x80000UL)
#define MIPI_DSI_INT_ST1_DPI_BUFF_PLD_UNDER_SHIFT (19U)
#define MIPI_DSI_INT_ST1_DPI_BUFF_PLD_UNDER_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_DPI_BUFF_PLD_UNDER_MASK) >> MIPI_DSI_INT_ST1_DPI_BUFF_PLD_UNDER_SHIFT)

/*
 * GEN_PLD_RECEV_ERR (R)
 *
 * indicates that during a generic interface packet read back, the payload FIFO full
 */
#define MIPI_DSI_INT_ST1_GEN_PLD_RECEV_ERR_MASK (0x1000U)
#define MIPI_DSI_INT_ST1_GEN_PLD_RECEV_ERR_SHIFT (12U)
#define MIPI_DSI_INT_ST1_GEN_PLD_RECEV_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_GEN_PLD_RECEV_ERR_MASK) >> MIPI_DSI_INT_ST1_GEN_PLD_RECEV_ERR_SHIFT)

/*
 * GEN_PLD_RD_ERR (R)
 *
 * indicates that during a DCS read data, the payload FIFO becomes empty
 */
#define MIPI_DSI_INT_ST1_GEN_PLD_RD_ERR_MASK (0x800U)
#define MIPI_DSI_INT_ST1_GEN_PLD_RD_ERR_SHIFT (11U)
#define MIPI_DSI_INT_ST1_GEN_PLD_RD_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_GEN_PLD_RD_ERR_MASK) >> MIPI_DSI_INT_ST1_GEN_PLD_RD_ERR_SHIFT)

/*
 * GEN_PLD_SEND_ERR (R)
 *
 * indicates the payload FIFO become empty when packet build
 */
#define MIPI_DSI_INT_ST1_GEN_PLD_SEND_ERR_MASK (0x400U)
#define MIPI_DSI_INT_ST1_GEN_PLD_SEND_ERR_SHIFT (10U)
#define MIPI_DSI_INT_ST1_GEN_PLD_SEND_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_GEN_PLD_SEND_ERR_MASK) >> MIPI_DSI_INT_ST1_GEN_PLD_SEND_ERR_SHIFT)

/*
 * GEN_PLD_WR_ERR (R)
 *
 * indicates the system tried to write a payload and FIFO is full
 */
#define MIPI_DSI_INT_ST1_GEN_PLD_WR_ERR_MASK (0x200U)
#define MIPI_DSI_INT_ST1_GEN_PLD_WR_ERR_SHIFT (9U)
#define MIPI_DSI_INT_ST1_GEN_PLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_GEN_PLD_WR_ERR_MASK) >> MIPI_DSI_INT_ST1_GEN_PLD_WR_ERR_SHIFT)

/*
 * GEN_CMD_WR_ERR (R)
 *
 * indicates the system tried to write a command and FIFO is full
 */
#define MIPI_DSI_INT_ST1_GEN_CMD_WR_ERR_MASK (0x100U)
#define MIPI_DSI_INT_ST1_GEN_CMD_WR_ERR_SHIFT (8U)
#define MIPI_DSI_INT_ST1_GEN_CMD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_GEN_CMD_WR_ERR_MASK) >> MIPI_DSI_INT_ST1_GEN_CMD_WR_ERR_SHIFT)

/*
 * DPI_BPLD_WR_ERR (R)
 *
 * indicates the payload FIFO is full during a DPI pixel line storage
 */
#define MIPI_DSI_INT_ST1_DPI_BPLD_WR_ERR_MASK (0x80U)
#define MIPI_DSI_INT_ST1_DPI_BPLD_WR_ERR_SHIFT (7U)
#define MIPI_DSI_INT_ST1_DPI_BPLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_DPI_BPLD_WR_ERR_MASK) >> MIPI_DSI_INT_ST1_DPI_BPLD_WR_ERR_SHIFT)

/*
 * EOPT_ERR (R)
 *
 * indicates that the EoTp packet has not been received at the end of the incoming peripheral transmission
 */
#define MIPI_DSI_INT_ST1_EOPT_ERR_MASK (0x40U)
#define MIPI_DSI_INT_ST1_EOPT_ERR_SHIFT (6U)
#define MIPI_DSI_INT_ST1_EOPT_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_EOPT_ERR_MASK) >> MIPI_DSI_INT_ST1_EOPT_ERR_SHIFT)

/*
 * PKT_SIZE_ERR (R)
 *
 * indicates that the packet size error has been detected during the packet reception
 */
#define MIPI_DSI_INT_ST1_PKT_SIZE_ERR_MASK (0x20U)
#define MIPI_DSI_INT_ST1_PKT_SIZE_ERR_SHIFT (5U)
#define MIPI_DSI_INT_ST1_PKT_SIZE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_PKT_SIZE_ERR_MASK) >> MIPI_DSI_INT_ST1_PKT_SIZE_ERR_SHIFT)

/*
 * CRC_ERR (R)
 *
 * indicates that the CRC error has been detected in the reveived packet payload
 */
#define MIPI_DSI_INT_ST1_CRC_ERR_MASK (0x10U)
#define MIPI_DSI_INT_ST1_CRC_ERR_SHIFT (4U)
#define MIPI_DSI_INT_ST1_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_CRC_ERR_MASK) >> MIPI_DSI_INT_ST1_CRC_ERR_SHIFT)

/*
 * ECC_MULTI_ERR (R)
 *
 * indicates that the ECC multiple error has been detected in a revieved packet
 */
#define MIPI_DSI_INT_ST1_ECC_MULTI_ERR_MASK (0x8U)
#define MIPI_DSI_INT_ST1_ECC_MULTI_ERR_SHIFT (3U)
#define MIPI_DSI_INT_ST1_ECC_MULTI_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_ECC_MULTI_ERR_MASK) >> MIPI_DSI_INT_ST1_ECC_MULTI_ERR_SHIFT)

/*
 * ECC_SIGLE_ERR (R)
 *
 * indicates that the ECC single error has been detected and corrected in a reveived packet
 */
#define MIPI_DSI_INT_ST1_ECC_SIGLE_ERR_MASK (0x4U)
#define MIPI_DSI_INT_ST1_ECC_SIGLE_ERR_SHIFT (2U)
#define MIPI_DSI_INT_ST1_ECC_SIGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_ECC_SIGLE_ERR_MASK) >> MIPI_DSI_INT_ST1_ECC_SIGLE_ERR_SHIFT)

/*
 * TO_LP_TX (R)
 *
 * indicates that the low-power reception timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_ST1_TO_LP_TX_MASK (0x2U)
#define MIPI_DSI_INT_ST1_TO_LP_TX_SHIFT (1U)
#define MIPI_DSI_INT_ST1_TO_LP_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_TO_LP_TX_MASK) >> MIPI_DSI_INT_ST1_TO_LP_TX_SHIFT)

/*
 * TO_HS_TX (R)
 *
 * indicates that the high-speed transmission timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_ST1_TO_HS_TX_MASK (0x1U)
#define MIPI_DSI_INT_ST1_TO_HS_TX_SHIFT (0U)
#define MIPI_DSI_INT_ST1_TO_HS_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_ST1_TO_HS_TX_MASK) >> MIPI_DSI_INT_ST1_TO_HS_TX_SHIFT)

/* Bitfield definition for register: INT_MSK0 */
/*
 * MASK_DPHY_ERRORS_4 (RW)
 *
 * disable LP1 contention error ErrContentionLP1 from lane0
 */
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_MASK (0x100000UL)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_SHIFT (20U)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_SHIFT) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_MASK)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_MASK) >> MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_4_SHIFT)

/*
 * MASK_DPHY_ERRORS_3 (RW)
 *
 * disable LP0 contention error ErrContentionLP0 from lane0
 */
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_MASK (0x80000UL)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_SHIFT (19U)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_SHIFT) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_MASK)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_MASK) >> MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_3_SHIFT)

/*
 * MASK_DPHY_ERRORS_2 (RW)
 *
 * disable control error ErrControl from lane0
 */
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_MASK (0x40000UL)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_SHIFT (18U)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_SHIFT) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_MASK)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_MASK) >> MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_2_SHIFT)

/*
 * MASK_DPHY_ERRORS_1 (RW)
 *
 * disable ErrSyncEsc low-power data transmission synchronization error from lane 0
 */
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_MASK (0x20000UL)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_SHIFT (17U)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_SHIFT) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_MASK)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_MASK) >> MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_1_SHIFT)

/*
 * MASK_DPHY_ERRORS_0 (RW)
 *
 * disable ErrEsc escape entry error from lane0
 */
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_MASK (0x10000UL)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_SHIFT (16U)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_SHIFT) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_MASK)
#define MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_MASK) >> MIPI_DSI_INT_MSK0_MASK_DPHY_ERRORS_0_SHIFT)

/*
 * MASK_ACK_WITH_ERR_15 (RW)
 *
 * disable the DSI protocal violation from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_MASK (0x8000U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_SHIFT (15U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_15_SHIFT)

/*
 * MASK_ACK_WITH_ERR_14 (RW)
 *
 * disable the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_MASK (0x4000U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_SHIFT (14U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_14_SHIFT)

/*
 * MASK_ACK_WITH_ERR_13 (RW)
 *
 * disable the invalid transmission length from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_MASK (0x2000U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_SHIFT (13U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_13_SHIFT)

/*
 * MASK_ACK_WITH_ERR_12 (RW)
 *
 * disable the dsi vc id invalid from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_MASK (0x1000U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_SHIFT (12U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_12_SHIFT)

/*
 * MASK_ACK_WITH_ERR_11 (RW)
 *
 * disable the not recongnized dsi data type from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_MASK (0x800U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_SHIFT (11U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_11_SHIFT)

/*
 * MASK_ACK_WITH_ERR_10 (RW)
 *
 * disable the checksum error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_MASK (0x400U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_SHIFT (10U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_10_SHIFT)

/*
 * MASK_ACK_WITH_ERR_9 (RW)
 *
 * disable the ECC error multi-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_MASK (0x200U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_SHIFT (9U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR_9_SHIFT)

/*
 * MASK_ACK_WITH_ERR8 (RW)
 *
 * disable the ecc error sigle-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_MASK (0x100U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_SHIFT (8U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR8_SHIFT)

/*
 * MASK_ACK_WITH_ERR7 (RW)
 *
 * disable the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_MASK (0x80U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_SHIFT (7U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR7_SHIFT)

/*
 * MASK_ACK_WITH_ERR6 (RW)
 *
 * disable the false control error fro the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_MASK (0x40U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_SHIFT (6U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR6_SHIFT)

/*
 * MASK_ACK_WITH_ERR5 (RW)
 *
 * disable the peripheral timeout error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_MASK (0x20U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_SHIFT (5U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR5_SHIFT)

/*
 * MASK_ACK_WITH_ERR4 (RW)
 *
 * disable the LP transmit sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_MASK (0x10U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_SHIFT (4U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR4_SHIFT)

/*
 * MASK_ACK_WITH_ERR3 (RW)
 *
 * disable the Escap mode entry command error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_MASK (0x8U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_SHIFT (3U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR3_SHIFT)

/*
 * MASK_ACK_WITH_ERR2 (RW)
 *
 * disable the EoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_MASK (0x4U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_SHIFT (2U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR2_SHIFT)

/*
 * MASK_ACK_WITH_ERR1 (RW)
 *
 * disable the SoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_MASK (0x2U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_SHIFT (1U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR1_SHIFT)

/*
 * MASK_ACK_WITH_ERR0 (RW)
 *
 * disable the SoT serror from the acknowledge error report
 */
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_MASK (0x1U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_SHIFT (0U)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_SHIFT) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_MASK)
#define MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_MASK) >> MIPI_DSI_INT_MSK0_MASK_ACK_WITH_ERR0_SHIFT)

/* Bitfield definition for register: INT_MSK1 */
/*
 * MASK_TEAR_REQUEST_ERR (RW)
 *
 * disable tear_request has occurred but tear effect is not active in dsi host and device
 */
#define MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_MASK (0x100000UL)
#define MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_SHIFT (20U)
#define MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_TEAR_REQUEST_ERR_SHIFT)

/*
 * MASK_DPI_BUFF_PLD_UNDER (RW)
 *
 * disable an underflow when reading payload to build dsi packet for video mode
 */
#define MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_MASK (0x80000UL)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_SHIFT (19U)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_SHIFT) & MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_MASK)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_MASK) >> MIPI_DSI_INT_MSK1_MASK_DPI_BUFF_PLD_UNDER_SHIFT)

/*
 * MASK_GEN_PLD_RECEV_ERR (RW)
 *
 * disable that during a generic interface packet read back, the payload FIFO full
 */
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_MASK (0x1000U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_SHIFT (12U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RECEV_ERR_SHIFT)

/*
 * MASK_GEN_PLD_RD_ERR (RW)
 *
 * disable that during a DCS read data, the payload FIFO becomes empty
 */
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_MASK (0x800U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_SHIFT (11U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_GEN_PLD_RD_ERR_SHIFT)

/*
 * MASK_GEN_PLD_SEND_ERR (RW)
 *
 * disable the payload FIFO become empty when packet build
 */
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_MASK (0x400U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_SHIFT (10U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_GEN_PLD_SEND_ERR_SHIFT)

/*
 * MASK_GEN_PLD_WR_ERR (RW)
 *
 * disable the system tried to write a payload and FIFO is full
 */
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_MASK (0x200U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_SHIFT (9U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_GEN_PLD_WR_ERR_SHIFT)

/*
 * MASK_GEN_CMD_WR_ERR (RW)
 *
 * disable the system tried to write a command and FIFO is full
 */
#define MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_MASK (0x100U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_SHIFT (8U)
#define MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_GEN_CMD_WR_ERR_SHIFT)

/*
 * MASK_DPI_BPLD_WR_ERR (RW)
 *
 * disable the payload FIFO is full during a DPI pixel line storage
 */
#define MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_MASK (0x80U)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_SHIFT (7U)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_DPI_BPLD_WR_ERR_SHIFT)

/*
 * MASK_EOPT_ERR (RW)
 *
 * disable that the EoTp packet has not been received at the end of the incoming peripheral transmission
 */
#define MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_MASK (0x40U)
#define MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_SHIFT (6U)
#define MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_EOPT_ERR_SHIFT)

/*
 * MASK_PKT_SIZE_ERR (RW)
 *
 * disable that the packet size error has been detected during the packet reception
 */
#define MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_MASK (0x20U)
#define MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_SHIFT (5U)
#define MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_PKT_SIZE_ERR_SHIFT)

/*
 * MASK_CRC_ERR (RW)
 *
 * disable that the CRC error has been detected in the reveived packet payload
 */
#define MIPI_DSI_INT_MSK1_MASK_CRC_ERR_MASK (0x10U)
#define MIPI_DSI_INT_MSK1_MASK_CRC_ERR_SHIFT (4U)
#define MIPI_DSI_INT_MSK1_MASK_CRC_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_CRC_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_CRC_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_CRC_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_CRC_ERR_SHIFT)

/*
 * MASK_ECC_MULTI_ERR (RW)
 *
 * disable that the ECC multiple error has been detected in a revieved packet
 */
#define MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_MASK (0x8U)
#define MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_SHIFT (3U)
#define MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_ECC_MULTI_ERR_SHIFT)

/*
 * MASK_ECC_SIGLE_ERR (RW)
 *
 * disable that the ECC single error has been detected and corrected in a reveived packet
 */
#define MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_MASK (0x4U)
#define MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_SHIFT (2U)
#define MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_SHIFT) & MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_MASK)
#define MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_MASK) >> MIPI_DSI_INT_MSK1_MASK_ECC_SIGLE_ERR_SHIFT)

/*
 * MASK_TO_LP_TX (RW)
 *
 * disable that the low-power reception timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_MASK (0x2U)
#define MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_SHIFT (1U)
#define MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_SHIFT) & MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_MASK)
#define MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_MASK) >> MIPI_DSI_INT_MSK1_MASK_TO_LP_TX_SHIFT)

/*
 * MASK_TO_HS_TX (RW)
 *
 * disable that the high-speed transmission timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_MASK (0x1U)
#define MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_SHIFT (0U)
#define MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_SHIFT) & MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_MASK)
#define MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_MASK) >> MIPI_DSI_INT_MSK1_MASK_TO_HS_TX_SHIFT)

/* Bitfield definition for register: PHY_CAL */
/*
 * TXSKEWCALHS (RW)
 *
 * High-speed skew calibration is started when txskewcalhs is
 * set high (assuming that PHY is in Stop state)
 */
#define MIPI_DSI_PHY_CAL_TXSKEWCALHS_MASK (0x1U)
#define MIPI_DSI_PHY_CAL_TXSKEWCALHS_SHIFT (0U)
#define MIPI_DSI_PHY_CAL_TXSKEWCALHS_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_CAL_TXSKEWCALHS_SHIFT) & MIPI_DSI_PHY_CAL_TXSKEWCALHS_MASK)
#define MIPI_DSI_PHY_CAL_TXSKEWCALHS_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_CAL_TXSKEWCALHS_MASK) >> MIPI_DSI_PHY_CAL_TXSKEWCALHS_SHIFT)

/* Bitfield definition for register: INT_FORCE0 */
/*
 * FORCE_DPHY_ERRORS_4 (RW)
 *
 * force LP1 contention error ErrContentionLP1 from lane0
 */
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_MASK (0x100000UL)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_SHIFT (20U)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_4_SHIFT)

/*
 * FORCE_DPHY_ERRORS_3 (RW)
 *
 * force LP0 contention error ErrContentionLP0 from lane0
 */
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_MASK (0x80000UL)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_SHIFT (19U)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_3_SHIFT)

/*
 * FORCE_DPHY_ERRORS_2 (RW)
 *
 * force control error ErrControl from lane0
 */
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_MASK (0x40000UL)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_SHIFT (18U)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_2_SHIFT)

/*
 * FORCE_DPHY_ERRORS_1 (RW)
 *
 * force ErrSyncEsc low-power data transmission synchronization error from lane 0
 */
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_MASK (0x20000UL)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_SHIFT (17U)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_1_SHIFT)

/*
 * FORCE_DPHY_ERRORS_0 (RW)
 *
 * force ErrEsc escape entry error from lane0
 */
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_MASK (0x10000UL)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_SHIFT (16U)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_DPHY_ERRORS_0_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_15 (RW)
 *
 * force the DSI protocal violation from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_MASK (0x8000U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_SHIFT (15U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_15_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_14 (RW)
 *
 * force the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_MASK (0x4000U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_SHIFT (14U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_14_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_13 (RW)
 *
 * force the invalid transmission length from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_MASK (0x2000U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_SHIFT (13U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_13_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_12 (RW)
 *
 * force the dsi vc id invalid from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_MASK (0x1000U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_SHIFT (12U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_12_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_11 (RW)
 *
 * force the not recongnized dsi data type from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_MASK (0x800U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_SHIFT (11U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_11_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_10 (RW)
 *
 * force the checksum error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_MASK (0x400U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_SHIFT (10U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_10_SHIFT)

/*
 * FORCE_ACK_WITH_ERR_9 (RW)
 *
 * force the ECC error multi-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_MASK (0x200U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_SHIFT (9U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR_9_SHIFT)

/*
 * FORCE_ACK_WITH_ERR8 (RW)
 *
 * force the ecc error sigle-bit from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_MASK (0x100U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_SHIFT (8U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR8_SHIFT)

/*
 * FORCE_ACK_WITH_ERR7 (RW)
 *
 * force the reserved from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_MASK (0x80U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_SHIFT (7U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR7_SHIFT)

/*
 * FORCE_ACK_WITH_ERR6 (RW)
 *
 * force the false control error fro the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_MASK (0x40U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_SHIFT (6U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR6_SHIFT)

/*
 * FORCE_ACK_WITH_ERR5 (RW)
 *
 * force the peripheral timeout error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_MASK (0x20U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_SHIFT (5U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR5_SHIFT)

/*
 * FORCE_ACK_WITH_ERR4 (RW)
 *
 * force the LP transmit sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_MASK (0x10U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_SHIFT (4U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR4_SHIFT)

/*
 * FORCE_ACK_WITH_ERR3 (RW)
 *
 * force the Escap mode entry command error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_MASK (0x8U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_SHIFT (3U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR3_SHIFT)

/*
 * FORCE_ACK_WITH_ERR2 (RW)
 *
 * force the EoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_MASK (0x4U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_SHIFT (2U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR2_SHIFT)

/*
 * FORCE_ACK_WITH_ERR1 (RW)
 *
 * force the SoT sync error from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_MASK (0x2U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_SHIFT (1U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR1_SHIFT)

/*
 * FORCE_ACK_WITH_ERR0 (RW)
 *
 * force the SoT serror from the acknowledge error report
 */
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_MASK (0x1U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_SHIFT (0U)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_SHIFT) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_MASK)
#define MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_MASK) >> MIPI_DSI_INT_FORCE0_FORCE_ACK_WITH_ERR0_SHIFT)

/* Bitfield definition for register: INT_FORCE1 */
/*
 * FORCE_TEAR_REQUEST_ERR (RW)
 *
 * force tear_request has occurred but tear effect is not active in dsi host and device
 */
#define MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_MASK (0x100000UL)
#define MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_SHIFT (20U)
#define MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_TEAR_REQUEST_ERR_SHIFT)

/*
 * FORCE_DPI_BUFF_PLD_UNDER (RW)
 *
 * force an underflow when reading payload to build dsi packet for video mode
 */
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_MASK (0x80000UL)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_SHIFT (19U)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_DPI_BUFF_PLD_UNDER_SHIFT)

/*
 * FORCE_GEN_PLD_RECEV_ERR (RW)
 *
 * force that during a generic interface packet read back, the payload FIFO full
 */
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_MASK (0x1000U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_SHIFT (12U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RECEV_ERR_SHIFT)

/*
 * FORCE_GEN_PLD_RD_ERR (RW)
 *
 * force that during a DCS read data, the payload FIFO becomes empty
 */
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_MASK (0x800U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_SHIFT (11U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_RD_ERR_SHIFT)

/*
 * FORCE_GEN_PLD_SEND_ERR (RW)
 *
 * force the payload FIFO become empty when packet build
 */
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_MASK (0x400U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_SHIFT (10U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_SEND_ERR_SHIFT)

/*
 * FORCE_GEN_PLD_WR_ERR (RW)
 *
 * force the system tried to write a payload and FIFO is full
 */
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_MASK (0x200U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_SHIFT (9U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_GEN_PLD_WR_ERR_SHIFT)

/*
 * FORCE_GEN_CMD_WR_ERR (RW)
 *
 * force the system tried to write a command and FIFO is full
 */
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_MASK (0x100U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_SHIFT (8U)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_GEN_CMD_WR_ERR_SHIFT)

/*
 * FORCE_DPI_BPLD_WR_ERR (RW)
 *
 * force the payload FIFO is full during a DPI pixel line storage
 */
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_MASK (0x80U)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_SHIFT (7U)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_DPI_BPLD_WR_ERR_SHIFT)

/*
 * FORCE_EOPT_ERR (RW)
 *
 * force that the EoTp packet has not been received at the end of the incoming peripheral transmission
 */
#define MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_MASK (0x40U)
#define MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_SHIFT (6U)
#define MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_EOPT_ERR_SHIFT)

/*
 * FORCE_PKT_SIZE_ERR (RW)
 *
 * force that the packet size error has been detected during the packet reception
 */
#define MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_MASK (0x20U)
#define MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_SHIFT (5U)
#define MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_PKT_SIZE_ERR_SHIFT)

/*
 * FORCE_CRC_ERR (RW)
 *
 * force that the CRC error has been detected in the reveived packet payload
 */
#define MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_MASK (0x10U)
#define MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_SHIFT (4U)
#define MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_CRC_ERR_SHIFT)

/*
 * FORCE_ECC_MULTI_ERR (RW)
 *
 * force that the ECC multiple error has been detected in a revieved packet
 */
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_MASK (0x8U)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_SHIFT (3U)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_ECC_MULTI_ERR_SHIFT)

/*
 * FORCE_ECC_SIGLE_ERR (RW)
 *
 * force that the ECC single error has been detected and corrected in a reveived packet
 */
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_MASK (0x4U)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_SHIFT (2U)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_ECC_SIGLE_ERR_SHIFT)

/*
 * FORCE_TO_LP_TX (RW)
 *
 * force that the low-power reception timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_MASK (0x2U)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_SHIFT (1U)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_TO_LP_TX_SHIFT)

/*
 * FORCE_TO_HS_TX (RW)
 *
 * force that the high-speed transmission timeout counter reached the end and contention has been detected
 */
#define MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_MASK (0x1U)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_SHIFT (0U)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_SET(x) (((uint32_t)(x) << MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_SHIFT) & MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_MASK)
#define MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_GET(x) (((uint32_t)(x) & MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_MASK) >> MIPI_DSI_INT_FORCE1_FORCE_TO_HS_TX_SHIFT)

/* Bitfield definition for register: PHY_TMR_RD */
/*
 * MAX_RD_TIME (RW)
 *
 * the maximum time required to perform a read command in lane byte clock cycles.
 */
#define MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_MASK (0x7FFFU)
#define MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_SHIFT (0U)
#define MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_SHIFT) & MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_MASK)
#define MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_MASK) >> MIPI_DSI_PHY_TMR_RD_MAX_RD_TIME_SHIFT)

/* Bitfield definition for register: AUTO_ULPS_MIN_TIME */
/*
 * ULPS_MIN_TIME (RW)
 *
 * configures the minimum time required by phy between ulpsactivenot and ulpsexitreq for clock and data lane
 */
#define MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_MASK (0xFFFU)
#define MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_SHIFT (0U)
#define MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_SET(x) (((uint32_t)(x) << MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_SHIFT) & MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_MASK)
#define MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_MASK) >> MIPI_DSI_AUTO_ULPS_MIN_TIME_ULPS_MIN_TIME_SHIFT)

/* Bitfield definition for register: PHY_MODE */
/*
 * PHY_MODE (RW)
 *
 * sel DPHY or CPHY
 */
#define MIPI_DSI_PHY_MODE_PHY_MODE_MASK (0x1U)
#define MIPI_DSI_PHY_MODE_PHY_MODE_SHIFT (0U)
#define MIPI_DSI_PHY_MODE_PHY_MODE_SET(x) (((uint32_t)(x) << MIPI_DSI_PHY_MODE_PHY_MODE_SHIFT) & MIPI_DSI_PHY_MODE_PHY_MODE_MASK)
#define MIPI_DSI_PHY_MODE_PHY_MODE_GET(x) (((uint32_t)(x) & MIPI_DSI_PHY_MODE_PHY_MODE_MASK) >> MIPI_DSI_PHY_MODE_PHY_MODE_SHIFT)

/* Bitfield definition for register: VID_SHADOW_CTRL */
/*
 * VID_SHADOW_PIN_REQ (RW)
 *
 * when set to 1, the video request is done by external pin
 */
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_MASK (0x10000UL)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SHIFT (16U)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SHIFT) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_MASK)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_MASK) >> MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_PIN_REQ_SHIFT)

/*
 * VID_SHADOW_REQ (RW)
 *
 * when set to 1, request that the dpi register from regbank are copied to the auxiliary registers
 */
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_MASK (0x100U)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SHIFT (8U)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SHIFT) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_MASK)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_MASK) >> MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_REQ_SHIFT)

/*
 * VID_SHADOW_EN (RW)
 *
 * when set to 1, DPI receives the active configuration from the auxiliary register
 */
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_MASK (0x1U)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SHIFT (0U)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SET(x) (((uint32_t)(x) << MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SHIFT) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_MASK)
#define MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_MASK) >> MIPI_DSI_VID_SHADOW_CTRL_VID_SHADOW_EN_SHIFT)

/* Bitfield definition for register: DPI_VCID_ACT */
/*
 * DPI_VCID (R)
 *
 * specifies the DPI virtual channel id that is indexed to the video mode packets
 */
#define MIPI_DSI_DPI_VCID_ACT_DPI_VCID_MASK (0x3U)
#define MIPI_DSI_DPI_VCID_ACT_DPI_VCID_SHIFT (0U)
#define MIPI_DSI_DPI_VCID_ACT_DPI_VCID_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_VCID_ACT_DPI_VCID_MASK) >> MIPI_DSI_DPI_VCID_ACT_DPI_VCID_SHIFT)

/* Bitfield definition for register: DPI_COLOR_CODING_ACT */
/*
 * LOOSELY18_EN (R)
 *
 * avtivates loosely packed variant to 18-bit configuration
 */
#define MIPI_DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_MASK (0x100U)
#define MIPI_DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_SHIFT (8U)
#define MIPI_DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_MASK) >> MIPI_DSI_DPI_COLOR_CODING_ACT_LOOSELY18_EN_SHIFT)

/*
 * DIP_COLOR_CODING (R)
 *
 * configures the DPI color for video mode
 */
#define MIPI_DSI_DPI_COLOR_CODING_ACT_DIP_COLOR_CODING_MASK (0xFU)
#define MIPI_DSI_DPI_COLOR_CODING_ACT_DIP_COLOR_CODING_SHIFT (0U)
#define MIPI_DSI_DPI_COLOR_CODING_ACT_DIP_COLOR_CODING_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_COLOR_CODING_ACT_DIP_COLOR_CODING_MASK) >> MIPI_DSI_DPI_COLOR_CODING_ACT_DIP_COLOR_CODING_SHIFT)

/* Bitfield definition for register: DPI_LP_CMD_TIM_ACT */
/*
 * OUTVACT_LPCMD_TIME (R)
 *
 * transmission of commands in low-power mode, it specifies the size in bytes of the lagest packet that can fit in a line during the VSA VBP and VFP regions.
 */
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_MASK (0xFF0000UL)
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_SHIFT (16U)
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_MASK) >> MIPI_DSI_DPI_LP_CMD_TIM_ACT_OUTVACT_LPCMD_TIME_SHIFT)

/*
 * INVACT_LPCMD_TIME (R)
 *
 * transmission of commands in low-power mode, it specifies the size in bytes of the lagest packet that can fit in a line during the vact regions.
 */
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_MASK (0xFFU)
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_SHIFT (0U)
#define MIPI_DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_MASK) >> MIPI_DSI_DPI_LP_CMD_TIM_ACT_INVACT_LPCMD_TIME_SHIFT)

/* Bitfield definition for register: VID_MODE_CFG_ACT */
/*
 * LP_CMD_EN (R)
 *
 * enable the command transmission only in low-power mode
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_CMD_EN_MASK (0x200U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_CMD_EN_SHIFT (9U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_CMD_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_CMD_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_CMD_EN_SHIFT)

/*
 * FRAME_BTA_ACK_EN (R)
 *
 * enable the request for an acknowledge response at the end of a frame
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_MASK (0x100U)
#define MIPI_DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_SHIFT (8U)
#define MIPI_DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_FRAME_BTA_ACK_EN_SHIFT)

/*
 * LP_HFP_EN (R)
 *
 * enable the returne to low-power inside the HFP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HFP_EN_MASK (0x80U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HFP_EN_SHIFT (7U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HFP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_HFP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_HFP_EN_SHIFT)

/*
 * LP_HBP_EN (R)
 *
 * enable the returne to low-power inside the HBP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HBP_EN_MASK (0x40U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HBP_EN_SHIFT (6U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_HBP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_HBP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_HBP_EN_SHIFT)

/*
 * LP_VACT_EN (R)
 *
 * enable the returne to low-power inside the VACT period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VACT_EN_MASK (0x20U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VACT_EN_SHIFT (5U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VACT_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_VACT_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_VACT_EN_SHIFT)

/*
 * LP_VFP_EN (R)
 *
 * enable the returne to low-power inside the VFP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VFP_EN_MASK (0x10U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VFP_EN_SHIFT (4U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VFP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_VFP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_VFP_EN_SHIFT)

/*
 * LP_VBP_EN (R)
 *
 * enable the returne to low-power inside the VBP period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VBP_EN_MASK (0x8U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VBP_EN_SHIFT (3U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VBP_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_VBP_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_VBP_EN_SHIFT)

/*
 * LP_VSA_EN (R)
 *
 * enable the returne to low-power inside the VSA period when timing allows
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VSA_EN_MASK (0x4U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VSA_EN_SHIFT (2U)
#define MIPI_DSI_VID_MODE_CFG_ACT_LP_VSA_EN_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_LP_VSA_EN_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_LP_VSA_EN_SHIFT)

/*
 * VID_MODE_TYPE (R)
 *
 * specifies the video mode transmission type
 */
#define MIPI_DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_MASK (0x3U)
#define MIPI_DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_SHIFT (0U)
#define MIPI_DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_MASK) >> MIPI_DSI_VID_MODE_CFG_ACT_VID_MODE_TYPE_SHIFT)

/* Bitfield definition for register: VID_PKT_SIZE_ACT */
/*
 * VID_PKT_SIZE (R)
 *
 * the number of pixels in a single video packet
 */
#define MIPI_DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_MASK (0x3FFFU)
#define MIPI_DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_SHIFT (0U)
#define MIPI_DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_MASK) >> MIPI_DSI_VID_PKT_SIZE_ACT_VID_PKT_SIZE_SHIFT)

/* Bitfield definition for register: VID_NUM_CHUNKS_ACT */
/*
 * VID_NUM_CHUNKS (R)
 *
 * the number of chunks to be transmitted during a line period
 */
#define MIPI_DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_MASK (0x1FFFU)
#define MIPI_DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_SHIFT (0U)
#define MIPI_DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_MASK) >> MIPI_DSI_VID_NUM_CHUNKS_ACT_VID_NUM_CHUNKS_SHIFT)

/* Bitfield definition for register: VID_NULL_SIZE_ACT */
/*
 * VID_NULL_SIZE (R)
 *
 * the number of bytes in side a null packet
 */
#define MIPI_DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_MASK (0x1FFFU)
#define MIPI_DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_SHIFT (0U)
#define MIPI_DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_MASK) >> MIPI_DSI_VID_NULL_SIZE_ACT_VID_NULL_SIZE_SHIFT)

/* Bitfield definition for register: VID_HSA_TIME_ACT */
/*
 * VID_HSA_TIME (R)
 *
 * the horizontal synchronism active period in lane byte clock cycles
 */
#define MIPI_DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_MASK (0xFFFU)
#define MIPI_DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_MASK) >> MIPI_DSI_VID_HSA_TIME_ACT_VID_HSA_TIME_SHIFT)

/* Bitfield definition for register: VID_HBP_TIME_ACT */
/*
 * VID_HBP_TIME (R)
 *
 * the horizontal back porch period in lane byte clock cycles
 */
#define MIPI_DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_MASK (0xFFFU)
#define MIPI_DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_MASK) >> MIPI_DSI_VID_HBP_TIME_ACT_VID_HBP_TIME_SHIFT)

/* Bitfield definition for register: VID_HLINE_TIME_ACT */
/*
 * VID_HLINE_TIME (R)
 *
 * the size of total line: hsa+hbp+hact+hfp
 */
#define MIPI_DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_MASK (0x7FFFU)
#define MIPI_DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_SHIFT (0U)
#define MIPI_DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_MASK) >> MIPI_DSI_VID_HLINE_TIME_ACT_VID_HLINE_TIME_SHIFT)

/* Bitfield definition for register: VID_VSA_LINES_ACT */
/*
 * VSA_LINES (R)
 *
 * vertical synchronism active period
 */
#define MIPI_DSI_VID_VSA_LINES_ACT_VSA_LINES_MASK (0x3FFU)
#define MIPI_DSI_VID_VSA_LINES_ACT_VSA_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VSA_LINES_ACT_VSA_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VSA_LINES_ACT_VSA_LINES_MASK) >> MIPI_DSI_VID_VSA_LINES_ACT_VSA_LINES_SHIFT)

/* Bitfield definition for register: VID_VBP_LINES_ACT */
/*
 * VBP_LINES (R)
 *
 * vertical back porch period
 */
#define MIPI_DSI_VID_VBP_LINES_ACT_VBP_LINES_MASK (0x3FFU)
#define MIPI_DSI_VID_VBP_LINES_ACT_VBP_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VBP_LINES_ACT_VBP_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VBP_LINES_ACT_VBP_LINES_MASK) >> MIPI_DSI_VID_VBP_LINES_ACT_VBP_LINES_SHIFT)

/* Bitfield definition for register: VID_VFP_LINES_ACT */
/*
 * VFP_LINES (R)
 *
 * vertical porch period
 */
#define MIPI_DSI_VID_VFP_LINES_ACT_VFP_LINES_MASK (0x3FFU)
#define MIPI_DSI_VID_VFP_LINES_ACT_VFP_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VFP_LINES_ACT_VFP_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VFP_LINES_ACT_VFP_LINES_MASK) >> MIPI_DSI_VID_VFP_LINES_ACT_VFP_LINES_SHIFT)

/* Bitfield definition for register: VID_VACTIVE_LINES_ACT */
/*
 * V_ACTIVE_LINES (R)
 *
 * vertical active period
 */
#define MIPI_DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_MASK (0x3FFFU)
#define MIPI_DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_SHIFT (0U)
#define MIPI_DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_MASK) >> MIPI_DSI_VID_VACTIVE_LINES_ACT_V_ACTIVE_LINES_SHIFT)

/* Bitfield definition for register: VID_PKT_STATUS */
/*
 * DPI_BUFF_PLD_FULL (R)
 *
 * This bit indicates the full status of the payload internal buffer
 * for video Mode. This bit is set to 0 for command Mode
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_FULL_MASK (0x20000UL)
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_FULL_SHIFT (17U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_FULL_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_FULL_SHIFT)

/*
 * DPI_BUFF_PLD_EMPTY (R)
 *
 * This bit indicates the empty status of the payload internal
 * buffer for video Mode. This bit is set to 0 for command Mod
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_EMPTY_MASK (0x10000UL)
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_EMPTY_SHIFT (16U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_EMPTY_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_BUFF_PLD_EMPTY_SHIFT)

/*
 * DPI_PLD_W_FULL (R)
 *
 * This bit indicates the full status of write payload FIFO for
 * video Mode. This bit is set to 0 for command Mode
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_FULL_MASK (0x8U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_FULL_SHIFT (3U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_FULL_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_FULL_SHIFT)

/*
 * DPI_PLD_W_EMPTY (R)
 *
 * This bit indicates the empty status of write payload FIFO for
 * video Mode. This bit is set to 0 for command Mode
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_EMPTY_MASK (0x4U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_EMPTY_SHIFT (2U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_EMPTY_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_PLD_W_EMPTY_SHIFT)

/*
 * DPI_CMD_W_FULL (R)
 *
 * This bit indicates the full status of write command FIFO for
 * video Mode. This bit is set to 0 for command Mode
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_FULL_MASK (0x2U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_FULL_SHIFT (1U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_FULL_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_FULL_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_FULL_SHIFT)

/*
 * DPI_CMD_W_EMPTY (R)
 *
 * This bit indicates the empty status of write command FIFO
 * for video Mode. This bit is set to 0 for command Mode
 */
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_EMPTY_MASK (0x1U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_EMPTY_SHIFT (0U)
#define MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_EMPTY_GET(x) (((uint32_t)(x) & MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_EMPTY_MASK) >> MIPI_DSI_VID_PKT_STATUS_DPI_CMD_W_EMPTY_SHIFT)

/* Bitfield definition for register: SDF_3D_ACT */
/*
 * SEND_3D_CFG (R)
 *
 * When set, causes the next VSS packet to include 3D control
 * payload in every VSS packet.
 */
#define MIPI_DSI_SDF_3D_ACT_SEND_3D_CFG_MASK (0x10000UL)
#define MIPI_DSI_SDF_3D_ACT_SEND_3D_CFG_SHIFT (16U)
#define MIPI_DSI_SDF_3D_ACT_SEND_3D_CFG_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_ACT_SEND_3D_CFG_MASK) >> MIPI_DSI_SDF_3D_ACT_SEND_3D_CFG_SHIFT)

/*
 * RIGHT_FIRST (R)
 *
 * This bit specifies the left/right order
 */
#define MIPI_DSI_SDF_3D_ACT_RIGHT_FIRST_MASK (0x20U)
#define MIPI_DSI_SDF_3D_ACT_RIGHT_FIRST_SHIFT (5U)
#define MIPI_DSI_SDF_3D_ACT_RIGHT_FIRST_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_ACT_RIGHT_FIRST_MASK) >> MIPI_DSI_SDF_3D_ACT_RIGHT_FIRST_SHIFT)

/*
 * SECOND_VSYNC (R)
 *
 * This field specifies whether there is a second VSYNC pulse
 * between Left and Right Images, when 3D Image Format is
 * Frame-based
 */
#define MIPI_DSI_SDF_3D_ACT_SECOND_VSYNC_MASK (0x10U)
#define MIPI_DSI_SDF_3D_ACT_SECOND_VSYNC_SHIFT (4U)
#define MIPI_DSI_SDF_3D_ACT_SECOND_VSYNC_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_ACT_SECOND_VSYNC_MASK) >> MIPI_DSI_SDF_3D_ACT_SECOND_VSYNC_SHIFT)

/*
 * FORMAT_3D (R)
 *
 * This field specifies 3D Image Format
 */
#define MIPI_DSI_SDF_3D_ACT_FORMAT_3D_MASK (0xCU)
#define MIPI_DSI_SDF_3D_ACT_FORMAT_3D_SHIFT (2U)
#define MIPI_DSI_SDF_3D_ACT_FORMAT_3D_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_ACT_FORMAT_3D_MASK) >> MIPI_DSI_SDF_3D_ACT_FORMAT_3D_SHIFT)

/*
 * MODE_3D (R)
 *
 * This field specifies 3D Mode On/Off and Display Orientation
 */
#define MIPI_DSI_SDF_3D_ACT_MODE_3D_MASK (0x3U)
#define MIPI_DSI_SDF_3D_ACT_MODE_3D_SHIFT (0U)
#define MIPI_DSI_SDF_3D_ACT_MODE_3D_GET(x) (((uint32_t)(x) & MIPI_DSI_SDF_3D_ACT_MODE_3D_MASK) >> MIPI_DSI_SDF_3D_ACT_MODE_3D_SHIFT)




#endif /* HPM_MIPI_DSI_H */

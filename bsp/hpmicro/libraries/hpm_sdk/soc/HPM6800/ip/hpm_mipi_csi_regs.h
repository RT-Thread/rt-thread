/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_MIPI_CSI_H
#define HPM_MIPI_CSI_H

typedef struct {
    __R  uint32_t VERSION;                     /* 0x0: version code */
    __RW uint32_t N_LANES;                     /* 0x4: the number of active lanes */
    __RW uint32_t CSI2_RESETN;                 /* 0x8: the internal logic of the controller goes into the reset state when active */
    __R  uint32_t INT_ST_MAIN;                 /* 0xC: contains the stateus of individual interrupt sources */
    __RW uint32_t DATA_IDS_1;                  /* 0x10: programs data type fields for data ID monitors */
    __RW uint32_t DATA_IDS_2;                  /* 0x14: programs data type fields for data ID monitors */
    __R  uint8_t  RESERVED0[20];               /* 0x18 - 0x2B: Reserved */
    __R  uint32_t INT_ST_AP_MAIN;              /* 0x2C: contains the status of individual interrupt sources */
    __R  uint8_t  RESERVED1[16];               /* 0x30 - 0x3F: Reserved */
    __RW uint32_t PHY_SHUTDOWNZ;               /* 0x40: controls the phy shutdown mode */
    __RW uint32_t DPHY_RSTZ;                   /* 0x44: controls the phy reset mode */
    __R  uint32_t PHY_RX;                      /* 0x48: contains the status of rx-related signals from phy */
    __R  uint32_t PHY_STOPSTATE;               /* 0x4C: contains the stopstate signal status from phy */
    __R  uint8_t  RESERVED2[48];               /* 0x50 - 0x7F: Reserved */
    __RW uint32_t IPI_MODE;                    /* 0x80: selects how the ipi interface generates the video frame */
    __RW uint32_t IPI_VCID;                    /* 0x84: selects the vritual channel processed by ipi */
    __RW uint32_t IPI_DATA_TYPE;               /* 0x88: selects the data type processed by ipi */
    __RW uint32_t IPI_MEM_FLASH;               /* 0x8C: control the flush of ipi memory */
    __RW uint32_t IPI_HSA_TIME;                /* 0x90: configures the video horizontal synchronism active time */
    __RW uint32_t IPI_HBP_TIME;                /* 0x94: configures the video horizontal synchronism back porch time */
    __RW uint32_t IPI_HSD_TIME;                /* 0x98: configures the vedeo Horizontal Sync Delay time */
    __RW uint32_t IPI_HLINE_TIME;              /* 0x9C: configures the overall tiem for each video line */
    __RW uint32_t IPI_SOFTRSTN;                /* 0xA0: congtrols the ipi logic reset state */
    __R  uint8_t  RESERVED3[8];                /* 0xA4 - 0xAB: Reserved */
    __RW uint32_t IPI_ADV_FEATURES;            /* 0xAC: configures advanced features for ipi mode */
    __RW uint32_t IPI_VSA_LINES;               /* 0xB0: configures the vertical synchronism active period */
    __RW uint32_t IPI_VBP_LINES;               /* 0xB4: configures the verticall back porch period */
    __RW uint32_t IPI_VFP_LINES;               /* 0xB8: configures the vertical front porch period */
    __RW uint32_t IPI_VACTIVE_LINES;           /* 0xBC: configures the vertical resolution of video */
    __R  uint8_t  RESERVED4[8];                /* 0xC0 - 0xC7: Reserved */
    __RW uint32_t VC_EXTENSION;                /* 0xC8: active extra bits for virtual channel */
    __R  uint32_t PHY_CAL;                     /* 0xCC: contains the calibration signal status from synopsys d-phy */
    __R  uint8_t  RESERVED5[16];               /* 0xD0 - 0xDF: Reserved */
    __R  uint32_t INT_ST_PHY_FATAL;            /* 0xE0: groups the phy interruptions caused by phy packets discarded */
    __RW uint32_t INT_MSK_PHY_FATAL;           /* 0xE4: interrupt mask for int_st_phy_fatal */
    __RW uint32_t INT_FORCE_PHY_FATAL;         /* 0xE8: interrupt force register for test purposes */
    __R  uint8_t  RESERVED6[4];                /* 0xEC - 0xEF: Reserved */
    __R  uint32_t INT_ST_PKT_FATAL;            /* 0xF0: groups the fatal interruption related with packet construction */
    __RW uint32_t INT_MSK_PKT_FATAL;           /* 0xF4: interrupt mask for int_st_pkt_fatal */
    __RW uint32_t INT_FORCE_PKT_FATAL;         /* 0xF8: interrupt force register is used for test purpos */
    __R  uint8_t  RESERVED7[20];               /* 0xFC - 0x10F: Reserved */
    __R  uint32_t INT_ST_PHY;                  /* 0x110: interruption caused by phy */
    __RW uint32_t INT_MSK_PHY;                 /* 0x114: interrupt mask for int_st_phy */
    __RW uint32_t INT_FORCE_PHY;               /* 0x118: interrupt force register */
    __R  uint8_t  RESERVED8[36];               /* 0x11C - 0x13F: Reserved */
    __R  uint32_t INT_ST_IPI_FATAL;            /* 0x140: fatal interruption caused by ipi interface */
    __RW uint32_t INT_MSK_IPI_FATAL;           /* 0x144: interrupt mask for int_st_ipi_fatal */
    __RW uint32_t INT_FORCE_IPI_FATAL;         /* 0x148: interrupt force register */
    __R  uint8_t  RESERVED9[52];               /* 0x14C - 0x17F: Reserved */
    __R  uint32_t INT_ST_AP_GENERIC;           /* 0x180: groups and notifies which interruption bits caused the interruption */
    __RW uint32_t INT_MSK_AP_GENERIC;          /* 0x184: interrupt mask for int_st_ap_generic */
    __RW uint32_t INT_FORCE_AP_GENERIC;        /* 0x188: interrupt force register used for test purposes */
    __R  uint8_t  RESERVED10[4];               /* 0x18C - 0x18F: Reserved */
    __R  uint32_t INT_ST_AP_IPI_FATAL;         /* 0x190: groups and notifies which interruption bits */
    __R  uint32_t INT_MSK_AP_IPI_FATAL;        /* 0x194: interrupt mask for int_st_ap_ipi_fatal controls */
    __R  uint32_t INT_FORCE_AP_IPI_FATAL;      /* 0x198: interrupt force register */
    __R  uint8_t  RESERVED11[228];             /* 0x19C - 0x27F: Reserved */
    __R  uint32_t INT_ST_BNDRY_FRAME_FATAL;    /* 0x280: fatal interruption related with matching frame start with frame end for a specific virtual channel */
    __RW uint32_t INT_MSK_BNDRY_FRAME_FATAL;   /* 0x284: interrupt mask for int_st_bndry_frame_fatal */
    __RW uint32_t INT_FORCE_BNDRY_FRAME_FATAL; /* 0x288: interrupt force register is used for test purposes */
    __R  uint8_t  RESERVED12[4];               /* 0x28C - 0x28F: Reserved */
    __R  uint32_t INT_ST_SEQ_FRAME_FATAL;      /* 0x290: fatal interruption related with matching frame start with frame end for a specific virtual channel */
    __RW uint32_t INT_MSK_SEQ_FRAME_FATAL;     /* 0x294: interrupt mask for int_st_seq_frame_fatal */
    __RW uint32_t INT_FORCE_SEQ_FRAME_FATAL;   /* 0x298: interrupt force register is used for test purposes */
    __R  uint8_t  RESERVED13[4];               /* 0x29C - 0x29F: Reserved */
    __R  uint32_t INT_ST_CRC_FRAME_FATAL;      /* 0x2A0: fatal interruption related with matching frame start with frame end for a specific virtual channel */
    __RW uint32_t INT_MSK_CRC_FRAME_FATAL;     /* 0x2A4: interrupt mask for int_st_crc_frame_fatal */
    __RW uint32_t INT_FORCE_CRC_FRAME_FATAL;   /* 0x2A8: interrupt force register is used for test purposes */
    __R  uint8_t  RESERVED14[4];               /* 0x2AC - 0x2AF: Reserved */
    __R  uint32_t INT_ST_PLD_CRC_FRAME_FATAL;  /* 0x2B0: fatal interruption related with matching frame start with frame end for a specific virtual channel */
    __RW uint32_t INT_MSK_PLD_CRC_FRAME_FATAL; /* 0x2B4: interrupt mask for int_st_crc_frame_fatal */
    __RW uint32_t INT_FORCE_PLD_CRC_FRAME_FATAL; /* 0x2B8: interrupt force register is used for test purposes */
} MIPI_CSI_Type;


/* Bitfield definition for register: VERSION */
/*
 * VERSION (RO)
 *
 * version code
 */
#define MIPI_CSI_VERSION_VERSION_MASK (0xFFFFFFFFUL)
#define MIPI_CSI_VERSION_VERSION_SHIFT (0U)
#define MIPI_CSI_VERSION_VERSION_GET(x) (((uint32_t)(x) & MIPI_CSI_VERSION_VERSION_MASK) >> MIPI_CSI_VERSION_VERSION_SHIFT)

/* Bitfield definition for register: N_LANES */
/*
 * N_LANES (RW)
 *
 * number of active data lanes
 */
#define MIPI_CSI_N_LANES_N_LANES_MASK (0x7U)
#define MIPI_CSI_N_LANES_N_LANES_SHIFT (0U)
#define MIPI_CSI_N_LANES_N_LANES_SET(x) (((uint32_t)(x) << MIPI_CSI_N_LANES_N_LANES_SHIFT) & MIPI_CSI_N_LANES_N_LANES_MASK)
#define MIPI_CSI_N_LANES_N_LANES_GET(x) (((uint32_t)(x) & MIPI_CSI_N_LANES_N_LANES_MASK) >> MIPI_CSI_N_LANES_N_LANES_SHIFT)

/* Bitfield definition for register: CSI2_RESETN */
/*
 * CSI2_RESETN (RW)
 *
 * DWC_mipi_csi2_host reset output, active low
 */
#define MIPI_CSI_CSI2_RESETN_CSI2_RESETN_MASK (0x1U)
#define MIPI_CSI_CSI2_RESETN_CSI2_RESETN_SHIFT (0U)
#define MIPI_CSI_CSI2_RESETN_CSI2_RESETN_SET(x) (((uint32_t)(x) << MIPI_CSI_CSI2_RESETN_CSI2_RESETN_SHIFT) & MIPI_CSI_CSI2_RESETN_CSI2_RESETN_MASK)
#define MIPI_CSI_CSI2_RESETN_CSI2_RESETN_GET(x) (((uint32_t)(x) & MIPI_CSI_CSI2_RESETN_CSI2_RESETN_MASK) >> MIPI_CSI_CSI2_RESETN_CSI2_RESETN_SHIFT)

/* Bitfield definition for register: INT_ST_MAIN */
/*
 * STATUS_INT_IPI4_FATAL (RC)
 *
 * status of int_st_ipi_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_IPI4_FATAL_MASK (0x40000UL)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_IPI4_FATAL_SHIFT (18U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_IPI4_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_IPI4_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_IPI4_FATAL_SHIFT)

/*
 * STATUS_INT_LINE (RC)
 *
 * status of int_st_line
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_LINE_MASK (0x20000UL)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_LINE_SHIFT (17U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_LINE_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_LINE_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_LINE_SHIFT)

/*
 * STATUS_INT_PHY (RC)
 *
 * status of int_st_phy
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_MASK (0x10000UL)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_SHIFT (16U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_SHIFT)

/*
 * STATUS_INT_ECC_CORRECTED (RC)
 *
 * status of status_int_ecc_corrected
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_ECC_CORRECTED_MASK (0x80U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_ECC_CORRECTED_SHIFT (7U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_ECC_CORRECTED_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_ECC_CORRECTED_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_ECC_CORRECTED_SHIFT)

/*
 * STATUS_INT_DATA_ID (RC)
 *
 * status of status_int_data_id
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_DATA_ID_MASK (0x40U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_DATA_ID_SHIFT (6U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_DATA_ID_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_DATA_ID_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_DATA_ID_SHIFT)

/*
 * STATUS_INT_PLD_CRC_FATAL (RC)
 *
 * status of status_int_pld_crc_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PLD_CRC_FATAL_MASK (0x20U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PLD_CRC_FATAL_SHIFT (5U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PLD_CRC_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_PLD_CRC_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_PLD_CRC_FATAL_SHIFT)

/*
 * STATUS_INT_CRC_FRAME_FATAL (RC)
 *
 * status of status_int_crc_frame_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_CRC_FRAME_FATAL_MASK (0x10U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_CRC_FRAME_FATAL_SHIFT (4U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_CRC_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_CRC_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_CRC_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_SEQ_FRAME_FATAL (RC)
 *
 * status of status_int_seq_frame_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_SEQ_FRAME_FATAL_MASK (0x8U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_SEQ_FRAME_FATAL_SHIFT (3U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_SEQ_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_SEQ_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_SEQ_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_BNDRY_FRAME_FATAL (RC)
 *
 * status of int_st_bndry_frame_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_MASK (0x4U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_SHIFT (2U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_PKT_FATAL (RC)
 *
 * status of int_st_pkt_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PKT_FATAL_MASK (0x2U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PKT_FATAL_SHIFT (1U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PKT_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_PKT_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_PKT_FATAL_SHIFT)

/*
 * STATUS_INT_PHY_FATAL (RC)
 *
 * status of int_st_phy_fatal
 */
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_FATAL_MASK (0x1U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_FATAL_SHIFT (0U)
#define MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_FATAL_MASK) >> MIPI_CSI_INT_ST_MAIN_STATUS_INT_PHY_FATAL_SHIFT)

/* Bitfield definition for register: DATA_IDS_1 */
/*
 * DI3_DT (RW)
 *
 * data type for programmed data ID 3
 */
#define MIPI_CSI_DATA_IDS_1_DI3_DT_MASK (0x3F000000UL)
#define MIPI_CSI_DATA_IDS_1_DI3_DT_SHIFT (24U)
#define MIPI_CSI_DATA_IDS_1_DI3_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_1_DI3_DT_SHIFT) & MIPI_CSI_DATA_IDS_1_DI3_DT_MASK)
#define MIPI_CSI_DATA_IDS_1_DI3_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_1_DI3_DT_MASK) >> MIPI_CSI_DATA_IDS_1_DI3_DT_SHIFT)

/*
 * DI2_DT (RW)
 *
 * data type for programmed data ID 2
 */
#define MIPI_CSI_DATA_IDS_1_DI2_DT_MASK (0x3F0000UL)
#define MIPI_CSI_DATA_IDS_1_DI2_DT_SHIFT (16U)
#define MIPI_CSI_DATA_IDS_1_DI2_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_1_DI2_DT_SHIFT) & MIPI_CSI_DATA_IDS_1_DI2_DT_MASK)
#define MIPI_CSI_DATA_IDS_1_DI2_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_1_DI2_DT_MASK) >> MIPI_CSI_DATA_IDS_1_DI2_DT_SHIFT)

/*
 * DI1_DT (RW)
 *
 * data type for programmed data ID 1
 */
#define MIPI_CSI_DATA_IDS_1_DI1_DT_MASK (0x3F00U)
#define MIPI_CSI_DATA_IDS_1_DI1_DT_SHIFT (8U)
#define MIPI_CSI_DATA_IDS_1_DI1_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_1_DI1_DT_SHIFT) & MIPI_CSI_DATA_IDS_1_DI1_DT_MASK)
#define MIPI_CSI_DATA_IDS_1_DI1_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_1_DI1_DT_MASK) >> MIPI_CSI_DATA_IDS_1_DI1_DT_SHIFT)

/*
 * DI0_DT (RW)
 *
 * data type for programmed data ID 0
 */
#define MIPI_CSI_DATA_IDS_1_DI0_DT_MASK (0x3FU)
#define MIPI_CSI_DATA_IDS_1_DI0_DT_SHIFT (0U)
#define MIPI_CSI_DATA_IDS_1_DI0_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_1_DI0_DT_SHIFT) & MIPI_CSI_DATA_IDS_1_DI0_DT_MASK)
#define MIPI_CSI_DATA_IDS_1_DI0_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_1_DI0_DT_MASK) >> MIPI_CSI_DATA_IDS_1_DI0_DT_SHIFT)

/* Bitfield definition for register: DATA_IDS_2 */
/*
 * DI7_DT (RW)
 *
 * data type for programmed data ID 7
 */
#define MIPI_CSI_DATA_IDS_2_DI7_DT_MASK (0x3F000000UL)
#define MIPI_CSI_DATA_IDS_2_DI7_DT_SHIFT (24U)
#define MIPI_CSI_DATA_IDS_2_DI7_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_2_DI7_DT_SHIFT) & MIPI_CSI_DATA_IDS_2_DI7_DT_MASK)
#define MIPI_CSI_DATA_IDS_2_DI7_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_2_DI7_DT_MASK) >> MIPI_CSI_DATA_IDS_2_DI7_DT_SHIFT)

/*
 * DI6_DT (RW)
 *
 * data type for programmed data ID 6
 */
#define MIPI_CSI_DATA_IDS_2_DI6_DT_MASK (0x3F0000UL)
#define MIPI_CSI_DATA_IDS_2_DI6_DT_SHIFT (16U)
#define MIPI_CSI_DATA_IDS_2_DI6_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_2_DI6_DT_SHIFT) & MIPI_CSI_DATA_IDS_2_DI6_DT_MASK)
#define MIPI_CSI_DATA_IDS_2_DI6_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_2_DI6_DT_MASK) >> MIPI_CSI_DATA_IDS_2_DI6_DT_SHIFT)

/*
 * DI5_DT (RW)
 *
 * data type for programmed data ID 5
 */
#define MIPI_CSI_DATA_IDS_2_DI5_DT_MASK (0x3F00U)
#define MIPI_CSI_DATA_IDS_2_DI5_DT_SHIFT (8U)
#define MIPI_CSI_DATA_IDS_2_DI5_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_2_DI5_DT_SHIFT) & MIPI_CSI_DATA_IDS_2_DI5_DT_MASK)
#define MIPI_CSI_DATA_IDS_2_DI5_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_2_DI5_DT_MASK) >> MIPI_CSI_DATA_IDS_2_DI5_DT_SHIFT)

/*
 * DI4_DT (RW)
 *
 * data type for programmed data ID 4
 */
#define MIPI_CSI_DATA_IDS_2_DI4_DT_MASK (0x3FU)
#define MIPI_CSI_DATA_IDS_2_DI4_DT_SHIFT (0U)
#define MIPI_CSI_DATA_IDS_2_DI4_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_DATA_IDS_2_DI4_DT_SHIFT) & MIPI_CSI_DATA_IDS_2_DI4_DT_MASK)
#define MIPI_CSI_DATA_IDS_2_DI4_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_DATA_IDS_2_DI4_DT_MASK) >> MIPI_CSI_DATA_IDS_2_DI4_DT_SHIFT)

/* Bitfield definition for register: INT_ST_AP_MAIN */
/*
 * STATUS_INT_IPI_FATAL (RC)
 *
 * status of int_st_ipi_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_IPI_FATAL_MASK (0x1000U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_IPI_FATAL_SHIFT (12U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_IPI_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_IPI_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_IPI_FATAL_SHIFT)

/*
 * STATUS_INT_ST_AP_IPI_FATAL (RC)
 *
 * status of int_st_ap_ipi_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_IPI_FATAL_MASK (0x800U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_IPI_FATAL_SHIFT (11U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_IPI_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_IPI_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_IPI_FATAL_SHIFT)

/*
 * STATUS_INT_LINE (RC)
 *
 * status of int_st_line
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_LINE_MASK (0x400U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_LINE_SHIFT (10U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_LINE_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_LINE_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_LINE_SHIFT)

/*
 * STATUS_INT_ECC_CORRECTED (RC)
 *
 * status of status_int_ecc_corrected
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ECC_CORRECTED_MASK (0x200U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ECC_CORRECTED_SHIFT (9U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ECC_CORRECTED_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ECC_CORRECTED_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ECC_CORRECTED_SHIFT)

/*
 * STATUS_INT_DATA_ID (RC)
 *
 * status of status_int_data_id
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_DATA_ID_MASK (0x100U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_DATA_ID_SHIFT (8U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_DATA_ID_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_DATA_ID_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_DATA_ID_SHIFT)

/*
 * STATUS_INT_PLD_CRC_FATAL (RC)
 *
 * status of status_int_pld_crc_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PLD_CRC_FATAL_MASK (0x80U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PLD_CRC_FATAL_SHIFT (7U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PLD_CRC_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PLD_CRC_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PLD_CRC_FATAL_SHIFT)

/*
 * STATUS_INT_PHY (RC)
 *
 * status of int_st_phy
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_MASK (0x40U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_SHIFT (6U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_SHIFT)

/*
 * STATUS_INT_CRC_FRAME_FATAL (RC)
 *
 * status of status_int_crc_frame_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_CRC_FRAME_FATAL_MASK (0x20U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_CRC_FRAME_FATAL_SHIFT (5U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_CRC_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_CRC_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_CRC_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_SEQ_FRAME_FATAL (RC)
 *
 * status of status_int_seq_frame_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_SEQ_FRAME_FATAL_MASK (0x10U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_SEQ_FRAME_FATAL_SHIFT (4U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_SEQ_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_SEQ_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_SEQ_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_BNDRY_FRAME_FATAL (RC)
 *
 * status of int_st_bndry_frame_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_MASK (0x8U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_SHIFT (3U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_BNDRY_FRAME_FATAL_SHIFT)

/*
 * STATUS_INT_PKT_FATAL (RC)
 *
 * status of int_st_pkt_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PKT_FATAL_MASK (0x4U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PKT_FATAL_SHIFT (2U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PKT_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PKT_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PKT_FATAL_SHIFT)

/*
 * STATUS_INT_PHY_FATAL (RC)
 *
 * status of int_st_phy_fatal
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_FATAL_MASK (0x2U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_FATAL_SHIFT (1U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_FATAL_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_FATAL_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_PHY_FATAL_SHIFT)

/*
 * STATUS_INT_ST_AP_GENERIC (RC)
 *
 * status of int_st_ap_generic
 */
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_GENERIC_MASK (0x1U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_GENERIC_SHIFT (0U)
#define MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_GENERIC_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_GENERIC_MASK) >> MIPI_CSI_INT_ST_AP_MAIN_STATUS_INT_ST_AP_GENERIC_SHIFT)

/* Bitfield definition for register: PHY_SHUTDOWNZ */
/*
 * PHY_SHUTDOWNZ (RW)
 *
 * shutdown input,active low
 */
#define MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_MASK (0x1U)
#define MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_SHIFT (0U)
#define MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_SET(x) (((uint32_t)(x) << MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_SHIFT) & MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_MASK)
#define MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_MASK) >> MIPI_CSI_PHY_SHUTDOWNZ_PHY_SHUTDOWNZ_SHIFT)

/* Bitfield definition for register: DPHY_RSTZ */
/*
 * DPHY_RSTZ (RW)
 *
 * phy reset output, active low
 */
#define MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_MASK (0x1U)
#define MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_SHIFT (0U)
#define MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_SET(x) (((uint32_t)(x) << MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_SHIFT) & MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_MASK)
#define MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_GET(x) (((uint32_t)(x) & MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_MASK) >> MIPI_CSI_DPHY_RSTZ_DPHY_RSTZ_SHIFT)

/* Bitfield definition for register: PHY_RX */
/*
 * PHY_RXCLKACTIVEHS (RO)
 *
 * indicates the d-phy clock lane is actively receiving a ddr clock
 */
#define MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_MASK (0x20000UL)
#define MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_SHIFT (17U)
#define MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_MASK) >> MIPI_CSI_PHY_RX_PHY_RXCLKACTIVEHS_SHIFT)

/*
 * PHY_RXULPSCLKNOT (RO)
 *
 * active low. Indicates the d-phy clock lane module has entered the Ultra low power state
 */
#define MIPI_CSI_PHY_RX_PHY_RXULPSCLKNOT_MASK (0x10000UL)
#define MIPI_CSI_PHY_RX_PHY_RXULPSCLKNOT_SHIFT (16U)
#define MIPI_CSI_PHY_RX_PHY_RXULPSCLKNOT_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_RX_PHY_RXULPSCLKNOT_MASK) >> MIPI_CSI_PHY_RX_PHY_RXULPSCLKNOT_SHIFT)

/*
 * PHY_RXULLPSESC_1 (RO)
 *
 * lane module 1 has entered the ultra low power mode
 */
#define MIPI_CSI_PHY_RX_PHY_RXULLPSESC_1_MASK (0x2U)
#define MIPI_CSI_PHY_RX_PHY_RXULLPSESC_1_SHIFT (1U)
#define MIPI_CSI_PHY_RX_PHY_RXULLPSESC_1_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_RX_PHY_RXULLPSESC_1_MASK) >> MIPI_CSI_PHY_RX_PHY_RXULLPSESC_1_SHIFT)

/*
 * PHY_RXULPSESC_0 (RO)
 *
 * lane module 0 has entered the ultra low power mode
 */
#define MIPI_CSI_PHY_RX_PHY_RXULPSESC_0_MASK (0x1U)
#define MIPI_CSI_PHY_RX_PHY_RXULPSESC_0_SHIFT (0U)
#define MIPI_CSI_PHY_RX_PHY_RXULPSESC_0_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_RX_PHY_RXULPSESC_0_MASK) >> MIPI_CSI_PHY_RX_PHY_RXULPSESC_0_SHIFT)

/* Bitfield definition for register: PHY_STOPSTATE */
/*
 * PHY_STOPSTATECLK (RO)
 *
 * d-phy clock lane in stop state
 */
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATECLK_MASK (0x10000UL)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATECLK_SHIFT (16U)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATECLK_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATECLK_MASK) >> MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATECLK_SHIFT)

/*
 * PHY_STOPSTATEDATA_1 (RO)
 *
 * data lane 1 in stop state
 */
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_1_MASK (0x2U)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_1_SHIFT (1U)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_1_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_1_MASK) >> MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_1_SHIFT)

/*
 * PHY_STOPSTATEDATA_0 (RO)
 *
 * data lane 0 in stop state
 */
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_0_MASK (0x1U)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_0_SHIFT (0U)
#define MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_0_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_0_MASK) >> MIPI_CSI_PHY_STOPSTATE_PHY_STOPSTATEDATA_0_SHIFT)

/* Bitfield definition for register: IPI_MODE */
/*
 * IPI_ENABLE (RW)
 *
 * enables the interface
 */
#define MIPI_CSI_IPI_MODE_IPI_ENABLE_MASK (0x1000000UL)
#define MIPI_CSI_IPI_MODE_IPI_ENABLE_SHIFT (24U)
#define MIPI_CSI_IPI_MODE_IPI_ENABLE_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MODE_IPI_ENABLE_SHIFT) & MIPI_CSI_IPI_MODE_IPI_ENABLE_MASK)
#define MIPI_CSI_IPI_MODE_IPI_ENABLE_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MODE_IPI_ENABLE_MASK) >> MIPI_CSI_IPI_MODE_IPI_ENABLE_SHIFT)

/*
 * IPI_CUT_THROUGH (RW)
 *
 * cut-through mode state active when high
 */
#define MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_MASK (0x10000UL)
#define MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_SHIFT (16U)
#define MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_SHIFT) & MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_MASK)
#define MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_MASK) >> MIPI_CSI_IPI_MODE_IPI_CUT_THROUGH_SHIFT)

/*
 * IPI_COLOR_COM (RW)
 *
 * if color mode components are deliverd as follows: 0x0 48bit intercase  0x1: 16bit interface
 */
#define MIPI_CSI_IPI_MODE_IPI_COLOR_COM_MASK (0x100U)
#define MIPI_CSI_IPI_MODE_IPI_COLOR_COM_SHIFT (8U)
#define MIPI_CSI_IPI_MODE_IPI_COLOR_COM_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MODE_IPI_COLOR_COM_SHIFT) & MIPI_CSI_IPI_MODE_IPI_COLOR_COM_MASK)
#define MIPI_CSI_IPI_MODE_IPI_COLOR_COM_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MODE_IPI_COLOR_COM_MASK) >> MIPI_CSI_IPI_MODE_IPI_COLOR_COM_SHIFT)

/*
 * IPI_MODE (RW)
 *
 * indicates the video mode transmission type 0x0: camera timing 0x1:controller timing
 */
#define MIPI_CSI_IPI_MODE_IPI_MODE_MASK (0x1U)
#define MIPI_CSI_IPI_MODE_IPI_MODE_SHIFT (0U)
#define MIPI_CSI_IPI_MODE_IPI_MODE_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MODE_IPI_MODE_SHIFT) & MIPI_CSI_IPI_MODE_IPI_MODE_MASK)
#define MIPI_CSI_IPI_MODE_IPI_MODE_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MODE_IPI_MODE_MASK) >> MIPI_CSI_IPI_MODE_IPI_MODE_SHIFT)

/* Bitfield definition for register: IPI_VCID */
/*
 * IPI_VCX_0_1 (RW)
 *
 * virtual channel extension of data to be processed by pixel interface
 */
#define MIPI_CSI_IPI_VCID_IPI_VCX_0_1_MASK (0xCU)
#define MIPI_CSI_IPI_VCID_IPI_VCX_0_1_SHIFT (2U)
#define MIPI_CSI_IPI_VCID_IPI_VCX_0_1_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VCID_IPI_VCX_0_1_SHIFT) & MIPI_CSI_IPI_VCID_IPI_VCX_0_1_MASK)
#define MIPI_CSI_IPI_VCID_IPI_VCX_0_1_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VCID_IPI_VCX_0_1_MASK) >> MIPI_CSI_IPI_VCID_IPI_VCX_0_1_SHIFT)

/*
 * IP_VCID (RW)
 *
 * virtual channel of data to be processed by pixel interface
 */
#define MIPI_CSI_IPI_VCID_IP_VCID_MASK (0x3U)
#define MIPI_CSI_IPI_VCID_IP_VCID_SHIFT (0U)
#define MIPI_CSI_IPI_VCID_IP_VCID_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VCID_IP_VCID_SHIFT) & MIPI_CSI_IPI_VCID_IP_VCID_MASK)
#define MIPI_CSI_IPI_VCID_IP_VCID_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VCID_IP_VCID_MASK) >> MIPI_CSI_IPI_VCID_IP_VCID_SHIFT)

/* Bitfield definition for register: IPI_DATA_TYPE */
/*
 * EMBENDED_DATA (RW)
 *
 * enable embedded data processing on ipi interface
 */
#define MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_MASK (0x100U)
#define MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_SHIFT (8U)
#define MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_SHIFT) & MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_MASK)
#define MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_MASK) >> MIPI_CSI_IPI_DATA_TYPE_EMBENDED_DATA_SHIFT)

/*
 * IPI_DATA_TYPE (RW)
 *
 * data type of data to be processed by pixel interface
 */
#define MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_MASK (0x3FU)
#define MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_SHIFT (0U)
#define MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_SHIFT) & MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_MASK)
#define MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_MASK) >> MIPI_CSI_IPI_DATA_TYPE_IPI_DATA_TYPE_SHIFT)

/* Bitfield definition for register: IPI_MEM_FLASH */
/*
 * IPI_AUTO_FLUSH (RW)
 *
 * memory is automatically flashed at each vsync
 */
#define MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_MASK (0x100U)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_SHIFT (8U)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_SHIFT) & MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_MASK)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_MASK) >> MIPI_CSI_IPI_MEM_FLASH_IPI_AUTO_FLUSH_SHIFT)

/*
 * IPI_FLUSH (RW)
 *
 * flush ipi memory, this bit is auto clear
 */
#define MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_MASK (0x1U)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_SHIFT (0U)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_SHIFT) & MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_MASK)
#define MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_MASK) >> MIPI_CSI_IPI_MEM_FLASH_IPI_FLUSH_SHIFT)

/* Bitfield definition for register: IPI_HSA_TIME */
/*
 * IPI_HSA_TIME (RW)
 *
 * configures the Horizontal Synchronism Active period in pixclk cycles
 */
#define MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_MASK (0xFFFU)
#define MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_SHIFT (0U)
#define MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_SHIFT) & MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_MASK)
#define MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_MASK) >> MIPI_CSI_IPI_HSA_TIME_IPI_HSA_TIME_SHIFT)

/* Bitfield definition for register: IPI_HBP_TIME */
/*
 * IPI_HBP_TIME (RW)
 *
 * configures the Horizontal Synchronism back porch period in pixclk cycles
 */
#define MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_MASK (0xFFFU)
#define MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_SHIFT (0U)
#define MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_SHIFT) & MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_MASK)
#define MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_MASK) >> MIPI_CSI_IPI_HBP_TIME_IPI_HBP_TIME_SHIFT)

/* Bitfield definition for register: IPI_HSD_TIME */
/*
 * IPI_HSD_TIME (RW)
 *
 * configures the Horizontal Sync Porch delay period in pixclk cycles
 */
#define MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_MASK (0xFFFU)
#define MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_SHIFT (0U)
#define MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_SHIFT) & MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_MASK)
#define MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_MASK) >> MIPI_CSI_IPI_HSD_TIME_IPI_HSD_TIME_SHIFT)

/* Bitfield definition for register: IPI_HLINE_TIME */
/*
 * IPI_HLIN_TIME (RW)
 *
 * configures the size of the line time counted in pixclk cycles
 */
#define MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_MASK (0x7FFFU)
#define MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_SHIFT (0U)
#define MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_SHIFT) & MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_MASK)
#define MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_MASK) >> MIPI_CSI_IPI_HLINE_TIME_IPI_HLIN_TIME_SHIFT)

/* Bitfield definition for register: IPI_SOFTRSTN */
/*
 * IPI_SOFTRSTN (RW)
 *
 * resets ipi one, active low
 */
#define MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_MASK (0x1U)
#define MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_SHIFT (0U)
#define MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_SHIFT) & MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_MASK)
#define MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_MASK) >> MIPI_CSI_IPI_SOFTRSTN_IPI_SOFTRSTN_SHIFT)

/* Bitfield definition for register: IPI_ADV_FEATURES */
/*
 * IPI_SYNC_EVENT_MODE (RW)
 *
 * for camera mode: 0x0- frame start do not trigger any sync event
 */
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_MASK (0x1000000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_SHIFT (24U)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_IPI_SYNC_EVENT_MODE_SHIFT)

/*
 * EN_EMBEDDED (RW)
 *
 * allows the use of embendded packets for ipi synchronization events
 */
#define MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_MASK (0x200000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_SHIFT (21U)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_EN_EMBEDDED_SHIFT)

/*
 * EN_BLANKING (RW)
 *
 * allows the use of blankong packets for IPI synchronization events
 */
#define MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_MASK (0x100000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_SHIFT (20U)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_EN_BLANKING_SHIFT)

/*
 * EN_NULL (RW)
 *
 * allows the use of null packets for IPI synchronization events
 */
#define MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_MASK (0x80000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_SHIFT (19U)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_EN_NULL_SHIFT)

/*
 * EN_LINE_START (RW)
 *
 * allows the use of line start packets for ipi synchronization events
 */
#define MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_MASK (0x40000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_SHIFT (18U)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_EN_LINE_START_SHIFT)

/*
 * EN_VIDEO (RW)
 *
 * allows the use of video packets for ipi synchronization events
 */
#define MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_MASK (0x20000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_SHIFT (17U)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_EN_VIDEO_SHIFT)

/*
 * LINE_EVENT_SELECTION (RW)
 *
 * for camero mode, allows manual selection of the packet fo line delimiter as follows: 0x0-controller seletc it automaticlly 0x1-select packets from list programmed in 17:21
 */
#define MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_MASK (0x10000UL)
#define MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_SHIFT (16U)
#define MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_LINE_EVENT_SELECTION_SHIFT)

/*
 * IPI_DT (RW)
 *
 * datatype to overwrite
 */
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_MASK (0x3F00U)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_SHIFT (8U)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_SHIFT)

/*
 * IPI_DT_OVERWRITE (RW)
 *
 * ignore datatype of the header using the programmed datatype for decoding
 */
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_MASK (0x1U)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_SHIFT (0U)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_SHIFT) & MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_MASK)
#define MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_MASK) >> MIPI_CSI_IPI_ADV_FEATURES_IPI_DT_OVERWRITE_SHIFT)

/* Bitfield definition for register: IPI_VSA_LINES */
/*
 * IPI_VSA_LINES (RW)
 *
 * configures the vertical synchronism active period measured in number of horizontal lines
 */
#define MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_MASK (0x3FFU)
#define MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_SHIFT (0U)
#define MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_SHIFT) & MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_MASK)
#define MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_MASK) >> MIPI_CSI_IPI_VSA_LINES_IPI_VSA_LINES_SHIFT)

/* Bitfield definition for register: IPI_VBP_LINES */
/*
 * IPI_VBP_LINES (RW)
 *
 * configuress the vertical back porch period measured in number of horizontal lines
 */
#define MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_MASK (0x3FFU)
#define MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_SHIFT (0U)
#define MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_SHIFT) & MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_MASK)
#define MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_MASK) >> MIPI_CSI_IPI_VBP_LINES_IPI_VBP_LINES_SHIFT)

/* Bitfield definition for register: IPI_VFP_LINES */
/*
 * IPI_VFP_LINES (RW)
 *
 * configures the vertical front porch period measured in number of horizontall lines
 */
#define MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_MASK (0x3FFU)
#define MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_SHIFT (0U)
#define MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_SHIFT) & MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_MASK)
#define MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_MASK) >> MIPI_CSI_IPI_VFP_LINES_IPI_VFP_LINES_SHIFT)

/* Bitfield definition for register: IPI_VACTIVE_LINES */
/*
 * IPI_VACTIVE_LINES (RW)
 *
 * configures the vertical active period measured in bumber of horizontal lines
 */
#define MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_MASK (0x3FFFU)
#define MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_SHIFT (0U)
#define MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_SET(x) (((uint32_t)(x) << MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_SHIFT) & MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_MASK)
#define MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_GET(x) (((uint32_t)(x) & MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_MASK) >> MIPI_CSI_IPI_VACTIVE_LINES_IPI_VACTIVE_LINES_SHIFT)

/* Bitfield definition for register: VC_EXTENSION */
/*
 * VCX (RW)
 *
 * indicates status of virtual channel extension: 0-virtual channel extension is enable  1-legacy mode
 */
#define MIPI_CSI_VC_EXTENSION_VCX_MASK (0x1U)
#define MIPI_CSI_VC_EXTENSION_VCX_SHIFT (0U)
#define MIPI_CSI_VC_EXTENSION_VCX_SET(x) (((uint32_t)(x) << MIPI_CSI_VC_EXTENSION_VCX_SHIFT) & MIPI_CSI_VC_EXTENSION_VCX_MASK)
#define MIPI_CSI_VC_EXTENSION_VCX_GET(x) (((uint32_t)(x) & MIPI_CSI_VC_EXTENSION_VCX_MASK) >> MIPI_CSI_VC_EXTENSION_VCX_SHIFT)

/* Bitfield definition for register: PHY_CAL */
/*
 * RXSKEWCALHS (RC)
 *
 * a low-to-high transition on rxskewcalhs signal means the the phy has  initiated the de-skew calibration
 */
#define MIPI_CSI_PHY_CAL_RXSKEWCALHS_MASK (0x1U)
#define MIPI_CSI_PHY_CAL_RXSKEWCALHS_SHIFT (0U)
#define MIPI_CSI_PHY_CAL_RXSKEWCALHS_GET(x) (((uint32_t)(x) & MIPI_CSI_PHY_CAL_RXSKEWCALHS_MASK) >> MIPI_CSI_PHY_CAL_RXSKEWCALHS_SHIFT)

/* Bitfield definition for register: INT_ST_PHY_FATAL */
/*
 * ERR_DESKEW (RC)
 *
 * reports whenever data is lost due to an existent skew between lanes greater than 2 rxwordclkhs
 */
#define MIPI_CSI_INT_ST_PHY_FATAL_ERR_DESKEW_MASK (0x100U)
#define MIPI_CSI_INT_ST_PHY_FATAL_ERR_DESKEW_SHIFT (8U)
#define MIPI_CSI_INT_ST_PHY_FATAL_ERR_DESKEW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_FATAL_ERR_DESKEW_MASK) >> MIPI_CSI_INT_ST_PHY_FATAL_ERR_DESKEW_SHIFT)

/*
 * PHY_ERRSOTSYNCHS_1 (RC)
 *
 * start of transmission error on data lane1
 */
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_1_MASK (0x2U)
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_1_SHIFT (1U)
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_1_MASK) >> MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_1_SHIFT)

/*
 * PHY_ERRSOTSYNCHS_0 (RC)
 *
 * start of transmission error on data lane0
 */
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_0_MASK (0x1U)
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_0_SHIFT (0U)
#define MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_0_MASK) >> MIPI_CSI_INT_ST_PHY_FATAL_PHY_ERRSOTSYNCHS_0_SHIFT)

/* Bitfield definition for register: INT_MSK_PHY_FATAL */
/*
 * ERR_DESKEW (RW)
 *
 * mask for err_deskew
 */
#define MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_MASK (0x100U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_SHIFT (8U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_SHIFT) & MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_MASK)
#define MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_MASK) >> MIPI_CSI_INT_MSK_PHY_FATAL_ERR_DESKEW_SHIFT)

/*
 * MASK_PHY_ERRSOTSYNCHS_1 (RW)
 *
 * mask for phy_errsotsynchs_1
 */
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_SHIFT) & MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_MASK)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_MASK) >> MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_1_SHIFT)

/*
 * MASK_PHY_ERRSOTSYNCHS_0 (RW)
 *
 * mask for phy_errsotsynchs_0
 */
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_SHIFT) & MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_MASK)
#define MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_MASK) >> MIPI_CSI_INT_MSK_PHY_FATAL_MASK_PHY_ERRSOTSYNCHS_0_SHIFT)

/* Bitfield definition for register: INT_FORCE_PHY_FATAL */
/*
 * ERR_DESKEW (RW)
 *
 * force err_deskew
 */
#define MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_MASK (0x100U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_MASK) >> MIPI_CSI_INT_FORCE_PHY_FATAL_ERR_DESKEW_SHIFT)

/*
 * FORCE_PHY_ERRSOTSYNCHS_1 (RW)
 *
 * force phy_errsotsynchs_1
 */
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_MASK) >> MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_1_SHIFT)

/*
 * FORCE_PHY_ERRSOTSYNCHS_0 (RW)
 *
 * force phy_errsotsynchs_0
 */
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_MASK) >> MIPI_CSI_INT_FORCE_PHY_FATAL_FORCE_PHY_ERRSOTSYNCHS_0_SHIFT)

/* Bitfield definition for register: INT_ST_PKT_FATAL */
/*
 * ERR_ECC_DOUBLE (RC)
 *
 * header ecc contains at least 2 errors
 */
#define MIPI_CSI_INT_ST_PKT_FATAL_ERR_ECC_DOUBLE_MASK (0x1U)
#define MIPI_CSI_INT_ST_PKT_FATAL_ERR_ECC_DOUBLE_SHIFT (0U)
#define MIPI_CSI_INT_ST_PKT_FATAL_ERR_ECC_DOUBLE_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PKT_FATAL_ERR_ECC_DOUBLE_MASK) >> MIPI_CSI_INT_ST_PKT_FATAL_ERR_ECC_DOUBLE_SHIFT)

/* Bitfield definition for register: INT_MSK_PKT_FATAL */
/*
 * MASK_ERR_ECC_DOUBLE (RW)
 *
 * mask for err_ecc_double
 */
#define MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_MASK (0x1U)
#define MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_SHIFT (0U)
#define MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_SHIFT) & MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_MASK)
#define MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_MASK) >> MIPI_CSI_INT_MSK_PKT_FATAL_MASK_ERR_ECC_DOUBLE_SHIFT)

/* Bitfield definition for register: INT_FORCE_PKT_FATAL */
/*
 * FORCE_ERR_ECC_DOUBLE (RW)
 *
 * force err_ecc_double
 */
#define MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_SHIFT) & MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_MASK)
#define MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_MASK) >> MIPI_CSI_INT_FORCE_PKT_FATAL_FORCE_ERR_ECC_DOUBLE_SHIFT)

/* Bitfield definition for register: INT_ST_PHY */
/*
 * PHY_ERRESC_1 (RC)
 *
 * start of transmission error on data lane 1
 */
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_1_MASK (0x20000UL)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_1_SHIFT (17U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_PHY_ERRESC_1_MASK) >> MIPI_CSI_INT_ST_PHY_PHY_ERRESC_1_SHIFT)

/*
 * PHY_ERRESC_0 (RC)
 *
 * start of transmission error on data lane 0
 */
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_0_MASK (0x10000UL)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_0_SHIFT (16U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRESC_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_PHY_ERRESC_0_MASK) >> MIPI_CSI_INT_ST_PHY_PHY_ERRESC_0_SHIFT)

/*
 * PHY_ERRSOTHS_1 (RC)
 *
 * start of transmission error on data lane 1
 */
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_1_MASK (0x2U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_1_SHIFT (1U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_1_MASK) >> MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_1_SHIFT)

/*
 * PHY_ERRSOTHS_0 (RC)
 *
 * start of transmission error on data lane 0
 */
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_0_MASK (0x1U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_0_SHIFT (0U)
#define MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_0_MASK) >> MIPI_CSI_INT_ST_PHY_PHY_ERRSOTHS_0_SHIFT)

/* Bitfield definition for register: INT_MSK_PHY */
/*
 * MASK_PHY_ERRESC_1 (RW)
 *
 * mask for phy_erresc_1
 */
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_MASK (0x20000UL)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_SHIFT (17U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_SHIFT) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_MASK)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_MASK) >> MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_1_SHIFT)

/*
 * MASK_PHY_ERRESC_0 (RW)
 *
 * mask for phy_erresc_0
 */
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_MASK (0x10000UL)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_SHIFT (16U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_SHIFT) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_MASK)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_MASK) >> MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRESC_0_SHIFT)

/*
 * MASK_PHY_ERRSOTHS_1 (RW)
 *
 * mask for phy_errsoths_1
 */
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_SHIFT) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_MASK)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_MASK) >> MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_1_SHIFT)

/*
 * MASK_PHY_ERRSOTHS_0 (RW)
 *
 * mask for phy_errsoths_0
 */
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_SHIFT) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_MASK)
#define MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_MASK) >> MIPI_CSI_INT_MSK_PHY_MASK_PHY_ERRSOTHS_0_SHIFT)

/* Bitfield definition for register: INT_FORCE_PHY */
/*
 * FORCE_PHY_ERRESC_1 (RW)
 *
 * force phy_erresc_1
 */
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_MASK (0x20000UL)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_SHIFT (17U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_MASK) >> MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_1_SHIFT)

/*
 * FORCE_PHY_ERRESC_0 (RW)
 *
 * force phy_erresc_0
 */
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_MASK (0x10000UL)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_SHIFT (16U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_MASK) >> MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRESC_0_SHIFT)

/*
 * FORCE_PHY_ERRSOTHS_1 (RW)
 *
 * force phy_errsoths_1
 */
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_MASK) >> MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_1_SHIFT)

/*
 * FORCE_PHY_ERRSOTHS_0 (RW)
 *
 * force phy_errsoths_0
 */
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_SHIFT) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_MASK)
#define MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_MASK) >> MIPI_CSI_INT_FORCE_PHY_FORCE_PHY_ERRSOTHS_0_SHIFT)

/* Bitfield definition for register: INT_ST_IPI_FATAL */
/*
 * INT_EVENT_FIFO_OVERFLOW (RC)
 *
 * reporting internal fifo overflow
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_INT_EVENT_FIFO_OVERFLOW_MASK (0x20U)
#define MIPI_CSI_INT_ST_IPI_FATAL_INT_EVENT_FIFO_OVERFLOW_SHIFT (5U)
#define MIPI_CSI_INT_ST_IPI_FATAL_INT_EVENT_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_INT_EVENT_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_INT_EVENT_FIFO_OVERFLOW_SHIFT)

/*
 * PIXEL_IF_HLINE_ERR (RC)
 *
 * horizontal line time error
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_HLINE_ERR_MASK (0x10U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_HLINE_ERR_SHIFT (4U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_HLINE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_HLINE_ERR_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_HLINE_ERR_SHIFT)

/*
 * PIXEL_IF_FIFO_NEMPTY_FS (RC)
 *
 * the fifo of pixel interface is not empty at the starat of a new frame
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_NEMPTY_FS_MASK (0x8U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT (3U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_NEMPTY_FS_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_NEMPTY_FS_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT)

/*
 * PIXEL_IF_FRAME_SYNC_ERR (RC)
 *
 * whenever in controller mode, notifies if a new frame is received but previous has not been completed
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FRAME_SYNC_ERR_MASK (0x4U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FRAME_SYNC_ERR_SHIFT (2U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FRAME_SYNC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FRAME_SYNC_ERR_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FRAME_SYNC_ERR_SHIFT)

/*
 * PIXEL_IF_FIFO_OVERFLOW (RC)
 *
 * the fifo of pixel interface has lost information because some data arrived and fifo is already full
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_OVERFLOW_MASK (0x2U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_OVERFLOW_SHIFT (1U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_OVERFLOW_SHIFT)

/*
 * PIXEL_IF_FIFO_UNDERFLOW (RC)
 *
 * the fifo has become empty before the expected bumber of pixels could be extracted to the pixel intefcese
 */
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_UNDERFLOW_MASK (0x1U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_UNDERFLOW_SHIFT (0U)
#define MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_UNDERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_UNDERFLOW_MASK) >> MIPI_CSI_INT_ST_IPI_FATAL_PIXEL_IF_FIFO_UNDERFLOW_SHIFT)

/* Bitfield definition for register: INT_MSK_IPI_FATAL */
/*
 * MSK_INT_EVENT_FIFO_OVERFLOW (RW)
 *
 * mask int_event_fifo_overflow
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_MASK (0x20U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_SHIFT (5U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_INT_EVENT_FIFO_OVERFLOW_SHIFT)

/*
 * MSK_PIXEL_IF_HLINE_ERR (RW)
 *
 * mask pixel_if_hline_err
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_MASK (0x10U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_SHIFT (4U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_HLINE_ERR_SHIFT)

/*
 * MSK_PIXEL_IF_FIFO_NEMPTY_FS (RW)
 *
 * mask pixel_if_fifo_nempty_fs
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_MASK (0x8U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT (3U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT)

/*
 * MSK_FRAME_SYNC_ERR (RW)
 *
 * mask for pixel_if_frame_sync_err
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_MASK (0x4U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_SHIFT (2U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_FRAME_SYNC_ERR_SHIFT)

/*
 * MSK_PIXEL_IF_FIFO_OVERFLOW (RW)
 *
 * mask for pixel_if_fifo_overflow
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_MASK (0x2U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_SHIFT (1U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_OVERFLOW_SHIFT)

/*
 * MSK_PIXEL_IF_FIFO_UNDERFLOW (RW)
 *
 * mask for pixel_if_fifo_unterflow
 */
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_MASK (0x1U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_SHIFT (0U)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_SHIFT) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_MASK)
#define MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_MASK) >> MIPI_CSI_INT_MSK_IPI_FATAL_MSK_PIXEL_IF_FIFO_UNDERFLOW_SHIFT)

/* Bitfield definition for register: INT_FORCE_IPI_FATAL */
/*
 * FORCE_INT_EVENT_FIFO_OVERFLOW (RW)
 *
 * force int_event_fifo_overflow
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_INT_EVENT_FIFO_OVERFLOW_SHIFT)

/*
 * FORCE_PIXEL_IF_HLINE_ERR (RW)
 *
 * force pixel_if_hline_err
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_HLINE_ERR_SHIFT)

/*
 * FORCE_PIXEL_IF_FIFO_NEMPTY_FS (RW)
 *
 * force pixel_if_fifo_nempty_fs
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_NEMPTY_FS_SHIFT)

/*
 * FORCE_FRAME_SYNC_ERR (RW)
 *
 * force for frame_sync_err
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_FRAME_SYNC_ERR_SHIFT)

/*
 * FORCE_PIXEL_IF_FIFO_OVERFLOW (RW)
 *
 * force for pixel_if_fifo_overflow
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_OVERFLOW_SHIFT)

/*
 * FORCE_PIXEL_IF_FIFO_UNDERFLOW (RW)
 *
 * force for pixel_if_fifo_underflow
 */
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_SHIFT) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_MASK)
#define MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_MASK) >> MIPI_CSI_INT_FORCE_IPI_FATAL_FORCE_PIXEL_IF_FIFO_UNDERFLOW_SHIFT)

/* Bitfield definition for register: INT_ST_AP_GENERIC */
/*
 * SYNCHRONIZER_PIXCLK_AP_ERR (RC)
 *
 * ap error in synchronizer block for pixclk domain
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_PIXCLK_AP_ERR_MASK (0x10000UL)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT (16U)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_PIXCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_PIXCLK_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT)

/*
 * SYNCHRONIZER_RXBYTECLKHS_AP_ERR (RC)
 *
 * ap error in synchronizer block for rxbyteclkhs domain
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK (0x8000U)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT (15U)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT)

/*
 * SYNCHRONIZER_FPCLK_AP_ERR (RC)
 *
 * ap error in synchronizer block for fpclk domain
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_FPCLK_AP_ERR_MASK (0x4000U)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT (14U)
#define MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_FPCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_FPCLK_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT)

/*
 * ERR_HANDLE_AP_ERR (RC)
 *
 * ap error in error handler block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_HANDLE_AP_ERR_MASK (0x2000U)
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_HANDLE_AP_ERR_SHIFT (13U)
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_HANDLE_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_ERR_HANDLE_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_ERR_HANDLE_AP_ERR_SHIFT)

/*
 * ERR_MSGR_AP_ERR (RC)
 *
 * ap error in err msgr block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_MSGR_AP_ERR_MASK (0x1000U)
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_MSGR_AP_ERR_SHIFT (12U)
#define MIPI_CSI_INT_ST_AP_GENERIC_ERR_MSGR_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_ERR_MSGR_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_ERR_MSGR_AP_ERR_SHIFT)

/*
 * PREP_OUTS_AP_ERR (RC)
 *
 * ap error in prepare outs block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_PREP_OUTS_AP_ERR_MASK (0xC00U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PREP_OUTS_AP_ERR_SHIFT (10U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PREP_OUTS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_PREP_OUTS_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_PREP_OUTS_AP_ERR_SHIFT)

/*
 * PACKET_ANALYZER_AP_ERR (RC)
 *
 * ap error in packet analyzer block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_PACKET_ANALYZER_AP_ERR_MASK (0x300U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PACKET_ANALYZER_AP_ERR_SHIFT (8U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PACKET_ANALYZER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_PACKET_ANALYZER_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_PACKET_ANALYZER_AP_ERR_SHIFT)

/*
 * PHY_ADAPTER_AP_ERR (RC)
 *
 * ap error in phy adapter block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_PHY_ADAPTER_AP_ERR_MASK (0x80U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PHY_ADAPTER_AP_ERR_SHIFT (7U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PHY_ADAPTER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_PHY_ADAPTER_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_PHY_ADAPTER_AP_ERR_SHIFT)

/*
 * DESCRAMBLER_AP_ERR (RC)
 *
 * ap error in descrambler block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_DESCRAMBLER_AP_ERR_MASK (0x40U)
#define MIPI_CSI_INT_ST_AP_GENERIC_DESCRAMBLER_AP_ERR_SHIFT (6U)
#define MIPI_CSI_INT_ST_AP_GENERIC_DESCRAMBLER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_DESCRAMBLER_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_DESCRAMBLER_AP_ERR_SHIFT)

/*
 * PIPELINE_DELAY_AP_ERR (RC)
 *
 * ap error in pipeline delay block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_PIPELINE_DELAY_AP_ERR_MASK (0x20U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PIPELINE_DELAY_AP_ERR_SHIFT (5U)
#define MIPI_CSI_INT_ST_AP_GENERIC_PIPELINE_DELAY_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_PIPELINE_DELAY_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_PIPELINE_DELAY_AP_ERR_SHIFT)

/*
 * DE_SKEW_AP_ERR (RC)
 *
 * ap error in de-skew block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_DE_SKEW_AP_ERR_MASK (0x10U)
#define MIPI_CSI_INT_ST_AP_GENERIC_DE_SKEW_AP_ERR_SHIFT (4U)
#define MIPI_CSI_INT_ST_AP_GENERIC_DE_SKEW_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_DE_SKEW_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_DE_SKEW_AP_ERR_SHIFT)

/*
 * REG_BANK_AP_ERR (RC)
 *
 * ap error in register bank block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_REG_BANK_AP_ERR_MASK (0xCU)
#define MIPI_CSI_INT_ST_AP_GENERIC_REG_BANK_AP_ERR_SHIFT (2U)
#define MIPI_CSI_INT_ST_AP_GENERIC_REG_BANK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_REG_BANK_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_REG_BANK_AP_ERR_SHIFT)

/*
 * APB_AP_ERR (RC)
 *
 * ap error in apb block
 */
#define MIPI_CSI_INT_ST_AP_GENERIC_APB_AP_ERR_MASK (0x3U)
#define MIPI_CSI_INT_ST_AP_GENERIC_APB_AP_ERR_SHIFT (0U)
#define MIPI_CSI_INT_ST_AP_GENERIC_APB_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_GENERIC_APB_AP_ERR_MASK) >> MIPI_CSI_INT_ST_AP_GENERIC_APB_AP_ERR_SHIFT)

/* Bitfield definition for register: INT_MSK_AP_GENERIC */
/*
 * MSK_SYNCHRONIZER_PIXCLK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_MASK (0x10000UL)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT (16U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT)

/*
 * MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK (0x8000U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT (15U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT)

/*
 * MSK_SYNCHRONIZER_FPCLK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_MASK (0x4000U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT (14U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT)

/*
 * MSK_ERR_HANDLE_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_MASK (0x2000U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_SHIFT (13U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_HANDLE_AP_ERR_SHIFT)

/*
 * MSK_ERR_MSGR_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_MASK (0x1000U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_SHIFT (12U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_ERR_MSGR_AP_ERR_SHIFT)

/*
 * MSK_PREP_OUTS_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_MASK (0xC00U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_SHIFT (10U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PREP_OUTS_AP_ERR_SHIFT)

/*
 * MSK_PACKET_ANALYZER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_MASK (0x300U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_SHIFT (8U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PACKET_ANALYZER_AP_ERR_SHIFT)

/*
 * MSK_PHY_ADAPTER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_MASK (0x80U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_SHIFT (7U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PHY_ADAPTER_AP_ERR_SHIFT)

/*
 * MSK_DESCRAMBLER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_MASK (0x40U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_SHIFT (6U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DESCRAMBLER_AP_ERR_SHIFT)

/*
 * MSK_PIPELINE_DELAY_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_MASK (0x20U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_SHIFT (5U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_PIPELINE_DELAY_AP_ERR_SHIFT)

/*
 * MSK_DE_SKEW_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_MASK (0x10U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_SHIFT (4U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_DE_SKEW_AP_ERR_SHIFT)

/*
 * MSK_REG_BANK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_MASK (0xCU)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_SHIFT (2U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_REG_BANK_AP_ERR_SHIFT)

/*
 * MSK_APB_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_MASK (0x3U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_SHIFT (0U)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_SHIFT) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_MASK)
#define MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_GENERIC_MSK_APB_AP_ERR_SHIFT)

/* Bitfield definition for register: INT_FORCE_AP_GENERIC */
/*
 * FORCE_SYNCHRONIZER_PIXCLK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_MASK (0x10000UL)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT (16U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_PIXCLK_AP_ERR_SHIFT)

/*
 * FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK (0x8000U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT (15U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_RXBYTECLKHS_AP_ERR_SHIFT)

/*
 * FORCE_SYNCHRONIZER_FPCLK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_MASK (0x4000U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT (14U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_SYNCHRONIZER_FPCLK_AP_ERR_SHIFT)

/*
 * FORCE_ERR_HANDLE_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_MASK (0x2000U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_SHIFT (13U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_HANDLE_AP_ERR_SHIFT)

/*
 * FORCE_ERR_MSGR_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_MASK (0x1000U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_SHIFT (12U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_ERR_MSGR_AP_ERR_SHIFT)

/*
 * FORCE_PREP_OUTS_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_MASK (0xC00U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_SHIFT (10U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PREP_OUTS_AP_ERR_SHIFT)

/*
 * FORCE_PACKET_ANALYZER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_MASK (0x300U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PACKET_ANALYZER_AP_ERR_SHIFT)

/*
 * FORCE_PHY_ADAPTER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_MASK (0x80U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_SHIFT (7U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PHY_ADAPTER_AP_ERR_SHIFT)

/*
 * FORCE_DESCRAMBLER_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_MASK (0x40U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_SHIFT (6U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DESCRAMBLER_AP_ERR_SHIFT)

/*
 * FORCE_PIPELINE_DELAY_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_PIPELINE_DELAY_AP_ERR_SHIFT)

/*
 * FORCE_DE_SKEW_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_DE_SKEW_AP_ERR_SHIFT)

/*
 * FORCE_REG_BANK_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_MASK (0xCU)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_REG_BANK_AP_ERR_SHIFT)

/*
 * FORCE_APB_AP_ERR (RW)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_MASK (0x3U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_SHIFT) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_MASK)
#define MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_GENERIC_FORCE_APB_AP_ERR_SHIFT)

/* Bitfield definition for register: INT_ST_AP_IPI_FATAL */
/*
 * REDUNDANCY_ERR (RC)
 *
 * ap redundancy error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_REDUNDANCY_ERR_MASK (0x20U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_REDUNDANCY_ERR_SHIFT (5U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_REDUNDANCY_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_REDUNDANCY_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_REDUNDANCY_ERR_SHIFT)

/*
 * CRC_ERR (RC)
 *
 * ap crc error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_CRC_ERR_MASK (0x10U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_CRC_ERR_SHIFT (4U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_CRC_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_CRC_ERR_SHIFT)

/*
 * ECC_MULTIPLE_ERR (RC)
 *
 * ap ecc multiple error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_MULTIPLE_ERR_MASK (0x8U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_MULTIPLE_ERR_SHIFT (3U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_MULTIPLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_MULTIPLE_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_MULTIPLE_ERR_SHIFT)

/*
 * ECC_SINGLE_ERR (RC)
 *
 * ap ecc sigle error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_SINGLE_ERR_MASK (0x4U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_SINGLE_ERR_SHIFT (2U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_SINGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_SINGLE_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_ECC_SINGLE_ERR_SHIFT)

/*
 * PARITY_RX_ERR (RC)
 *
 * ap parity rx error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_RX_ERR_MASK (0x2U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_RX_ERR_SHIFT (1U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_RX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_RX_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_RX_ERR_SHIFT)

/*
 * PARITY_TX_ERR (RC)
 *
 * ap parity tx error in ipi1
 */
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_TX_ERR_MASK (0x1U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_TX_ERR_SHIFT (0U)
#define MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_TX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_TX_ERR_MASK) >> MIPI_CSI_INT_ST_AP_IPI_FATAL_PARITY_TX_ERR_SHIFT)

/* Bitfield definition for register: INT_MSK_AP_IPI_FATAL */
/*
 * MASK_REDUNDANCY_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_REDUNDANCY_ERR_MASK (0x20U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_REDUNDANCY_ERR_SHIFT (5U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_REDUNDANCY_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_REDUNDANCY_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_REDUNDANCY_ERR_SHIFT)

/*
 * MASK_CRC_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_CRC_ERR_MASK (0x10U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_CRC_ERR_SHIFT (4U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_CRC_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_CRC_ERR_SHIFT)

/*
 * MASK_ECC_MULTIPLE_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_MULTIPLE_ERR_MASK (0x8U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_MULTIPLE_ERR_SHIFT (3U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_MULTIPLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_MULTIPLE_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_MULTIPLE_ERR_SHIFT)

/*
 * MASK_ECC_SINGLE_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_SINGLE_ERR_MASK (0x4U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_SINGLE_ERR_SHIFT (2U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_SINGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_SINGLE_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_ECC_SINGLE_ERR_SHIFT)

/*
 * MASK_PARITY_RX_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_RX_ERR_MASK (0x2U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_RX_ERR_SHIFT (1U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_RX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_RX_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_RX_ERR_SHIFT)

/*
 * MASK_PARITY_TX_ERR (RC)
 *
 */
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_TX_ERR_MASK (0x1U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_TX_ERR_SHIFT (0U)
#define MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_TX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_TX_ERR_MASK) >> MIPI_CSI_INT_MSK_AP_IPI_FATAL_MASK_PARITY_TX_ERR_SHIFT)

/* Bitfield definition for register: INT_FORCE_AP_IPI_FATAL */
/*
 * FORCE_REDUNDANCY_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_REDUNDANCY_ERR_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_REDUNDANCY_ERR_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_REDUNDANCY_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_REDUNDANCY_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_REDUNDANCY_ERR_SHIFT)

/*
 * FORCE_CRC_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_CRC_ERR_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_CRC_ERR_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_CRC_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_CRC_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_CRC_ERR_SHIFT)

/*
 * FORCE_ECC_MULTIPLE_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_MULTIPLE_ERR_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_MULTIPLE_ERR_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_MULTIPLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_MULTIPLE_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_MULTIPLE_ERR_SHIFT)

/*
 * FORCE_ECC_SINGLE_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_SINGLE_ERR_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_SINGLE_ERR_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_SINGLE_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_SINGLE_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_ECC_SINGLE_ERR_SHIFT)

/*
 * FORCE_PARITY_RX_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_RX_ERR_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_RX_ERR_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_RX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_RX_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_RX_ERR_SHIFT)

/*
 * FORCE_PARITY_TX_ERR (RC)
 *
 */
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_TX_ERR_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_TX_ERR_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_TX_ERR_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_TX_ERR_MASK) >> MIPI_CSI_INT_FORCE_AP_IPI_FATAL_FORCE_PARITY_TX_ERR_SHIFT)

/* Bitfield definition for register: INT_ST_BNDRY_FRAME_FATAL */
/*
 * ERR_F_BNDRY_MATCH_VC15 (RC)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC15_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC15_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC14 (RC)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC14_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC14_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC13 (RC)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC13_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC13_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC12 (RC)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC12_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC12_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC11 (RC)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC11_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC11_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC10 (RC)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC10_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC10_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC9 (RC)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC9_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC9_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC8 (RC)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC8_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC8_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC7 (RC)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC7_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC7_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC6 (RC)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC6_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC6_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC5 (RC)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC5_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC5_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC4 (RC)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC4_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC4_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC3 (RC)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC3_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC3_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC2 (RC)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC2_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC2_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC1 (RC)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC1_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC1_SHIFT)

/*
 * ERR_F_BNDRY_MATCH_VC0 (RC)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC0_MASK) >> MIPI_CSI_INT_ST_BNDRY_FRAME_FATAL_ERR_F_BNDRY_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_MSK_BNDRY_FRAME_FATAL */
/*
 * MSK_ERR_F_BNDRY_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC15_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC14_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC13_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC12_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC11_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC10_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC9_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC8_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC7_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC6_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC5_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC4_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC3_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC2_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC1_SHIFT)

/*
 * MSK_ERR_F_BNDRY_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_SHIFT) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_MASK)
#define MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_MASK) >> MIPI_CSI_INT_MSK_BNDRY_FRAME_FATAL_MSK_ERR_F_BNDRY_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_FORCE_BNDRY_FRAME_FATAL */
/*
 * FORCE_ERR_F_BNDRY_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC15_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC14_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC13_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC12_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC11_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC10_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC9_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC8_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC7_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC6_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC5_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC4_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC3_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC2_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC1_SHIFT)

/*
 * FORCE_ERR_F_BNDRY_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_SHIFT) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_MASK)
#define MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_MASK) >> MIPI_CSI_INT_FORCE_BNDRY_FRAME_FATAL_FORCE_ERR_F_BNDRY_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_ST_SEQ_FRAME_FATAL */
/*
 * ERR_F_SEQ_MATCH_VC15 (RC)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC15_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC15_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC14 (RC)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC14_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC14_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC13 (RC)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC13_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC13_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC12 (RC)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC12_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC12_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC11 (RC)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC11_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC11_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC10 (RC)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC10_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC10_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC9 (RC)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC9_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC9_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC8 (RC)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC8_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC8_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC7 (RC)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC7_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC7_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC6 (RC)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC6_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC6_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC5 (RC)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC5_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC5_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC4 (RC)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC4_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC4_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC3 (RC)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC3_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC3_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC2 (RC)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC2_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC2_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC1 (RC)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC1_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC1_SHIFT)

/*
 * ERR_F_SEQ_MATCH_VC0 (RC)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC0_MASK) >> MIPI_CSI_INT_ST_SEQ_FRAME_FATAL_ERR_F_SEQ_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_MSK_SEQ_FRAME_FATAL */
/*
 * MSK_ERR_F_SEQ_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC15_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC14_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC13_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC12_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC11_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC10_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC9_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC8_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC7_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC6_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC5_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC4_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC3_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC2_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC1_SHIFT)

/*
 * MSK_ERR_F_SEQ_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_SHIFT) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_MASK)
#define MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_MASK) >> MIPI_CSI_INT_MSK_SEQ_FRAME_FATAL_MSK_ERR_F_SEQ_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_FORCE_SEQ_FRAME_FATAL */
/*
 * FORCE_ERR_F_SEQ_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC15_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC14_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC13_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC12_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC11_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC10_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC9_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC8_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC7_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC6_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC5_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC4_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC3_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC2_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC1_SHIFT)

/*
 * FORCE_ERR_F_SEQ_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_SHIFT) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_MASK)
#define MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_MASK) >> MIPI_CSI_INT_FORCE_SEQ_FRAME_FATAL_FORCE_ERR_F_SEQ_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_ST_CRC_FRAME_FATAL */
/*
 * ERR_F_CRC_MATCH_VC15 (RC)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC15_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC14 (RC)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC14_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC13 (RC)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC13_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC12 (RC)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC12_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC11 (RC)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC11_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC10 (RC)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC10_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC9 (RC)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC9_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC8 (RC)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC8_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC7 (RC)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC7_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC6 (RC)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC6_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC5 (RC)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC5_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC4 (RC)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC4_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC3 (RC)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC3_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC2 (RC)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC2_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC1 (RC)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC1_SHIFT)

/*
 * ERR_F_CRC_MATCH_VC0 (RC)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_ST_CRC_FRAME_FATAL_ERR_F_CRC_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_MSK_CRC_FRAME_FATAL */
/*
 * MSK_ERR_F_CRC_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC15_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC14_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC13_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC12_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC11_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC10_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC9_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC8_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC7_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC6_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC5_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC4_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC3_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC2_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC1_SHIFT)

/*
 * MSK_ERR_F_CRC_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_SHIFT) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_MASK)
#define MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_MSK_CRC_FRAME_FATAL_MSK_ERR_F_CRC_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_FORCE_CRC_FRAME_FATAL */
/*
 * FORCE_ERR_F_CRC_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC15_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC14_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC13_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC12_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC11_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC10_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC9_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC8_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC7_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC6_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC5_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC4_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC3_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC2_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC1_SHIFT)

/*
 * FORCE_ERR_F_CRC_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_SHIFT) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_MASK)
#define MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_FORCE_CRC_FRAME_FATAL_FORCE_ERR_F_CRC_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_ST_PLD_CRC_FRAME_FATAL */
/*
 * ERR_CRC_MATCH_VC15 (RC)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC15_SHIFT)

/*
 * ERR_CRC_MATCH_VC14 (RC)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC14_SHIFT)

/*
 * ERR_CRC_MATCH_VC13 (RC)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC13_SHIFT)

/*
 * ERR_CRC_MATCH_VC12 (RC)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC12_SHIFT)

/*
 * ERR_CRC_MATCH_VC11 (RC)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC11_SHIFT)

/*
 * ERR_CRC_MATCH_VC10 (RC)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC10_SHIFT)

/*
 * ERR_CRC_MATCH_VC9 (RC)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC9_SHIFT)

/*
 * ERR_CRC_MATCH_VC8 (RC)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC8_SHIFT)

/*
 * ERR_CRC_MATCH_VC7 (RC)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC7_SHIFT)

/*
 * ERR_CRC_MATCH_VC6 (RC)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC6_SHIFT)

/*
 * ERR_CRC_MATCH_VC5 (RC)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC5_SHIFT)

/*
 * ERR_CRC_MATCH_VC4 (RC)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC4_SHIFT)

/*
 * ERR_CRC_MATCH_VC3 (RC)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC3_SHIFT)

/*
 * ERR_CRC_MATCH_VC2 (RC)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC2_SHIFT)

/*
 * ERR_CRC_MATCH_VC1 (RC)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC1_SHIFT)

/*
 * ERR_CRC_MATCH_VC0 (RC)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_ST_PLD_CRC_FRAME_FATAL_ERR_CRC_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_MSK_PLD_CRC_FRAME_FATAL */
/*
 * MSK_ERR_CRC_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC15_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC14_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC13_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC12_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC11_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC10_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC9_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC8_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC7_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC6_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC5_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC4_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC3_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC2_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC1_SHIFT)

/*
 * MSK_ERR_CRC_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_SHIFT) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_MASK)
#define MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_MSK_PLD_CRC_FRAME_FATAL_MSK_ERR_CRC_MATCH_VC0_SHIFT)

/* Bitfield definition for register: INT_FORCE_PLD_CRC_FRAME_FATAL */
/*
 * FORCE_ERR_CRC_MATCH_VC15 (RW)
 *
 * error matching frame start with frame end for virtual channel 15
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_MASK (0x8000U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_SHIFT (15U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC15_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC14 (RW)
 *
 * error matching frame start with frame end for virtual channel 14
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_MASK (0x4000U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_SHIFT (14U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC14_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC13 (RW)
 *
 * error matching frame start with frame end for virtual channel 13
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_MASK (0x2000U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_SHIFT (13U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC13_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC12 (RW)
 *
 * error matching frame start with frame end for virtual channel 12
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_MASK (0x1000U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_SHIFT (12U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC12_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC11 (RW)
 *
 * error matching frame start with frame end for virtual channel 11
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_MASK (0x800U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_SHIFT (11U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC11_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC10 (RW)
 *
 * error matching frame start with frame end for virtual channel 10
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_MASK (0x400U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_SHIFT (10U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC10_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC9 (RW)
 *
 * error matching frame start with frame end for virtual channel 9
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_MASK (0x200U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_SHIFT (9U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC9_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC8 (RW)
 *
 * error matching frame start with frame end for virtual channel 8
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_MASK (0x100U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_SHIFT (8U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC8_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC7 (RW)
 *
 * error matching frame start with frame end for virtual channel 7
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_MASK (0x80U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_SHIFT (7U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC7_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC6 (RW)
 *
 * error matching frame start with frame end for virtual channel 6
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_MASK (0x40U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_SHIFT (6U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC6_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC5 (RW)
 *
 * error matching frame start with frame end for virtual channel 5
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_MASK (0x20U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_SHIFT (5U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC5_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC4 (RW)
 *
 * error matching frame start with frame end for virtual channel 4
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_MASK (0x10U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_SHIFT (4U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC4_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC3 (RW)
 *
 * error matching frame start with frame end for virtual channel 3
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_MASK (0x8U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_SHIFT (3U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC3_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC2 (RW)
 *
 * error matching frame start with frame end for virtual channel 2
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_MASK (0x4U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_SHIFT (2U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC2_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC1 (RW)
 *
 * error matching frame start with frame end for virtual channel 1
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_MASK (0x2U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_SHIFT (1U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC1_SHIFT)

/*
 * FORCE_ERR_CRC_MATCH_VC0 (RW)
 *
 * error matching frame start with frame end for virtual channel 0
 */
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_MASK (0x1U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_SHIFT (0U)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_SET(x) (((uint32_t)(x) << MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_SHIFT) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_MASK)
#define MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_GET(x) (((uint32_t)(x) & MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_MASK) >> MIPI_CSI_INT_FORCE_PLD_CRC_FRAME_FATAL_FORCE_ERR_CRC_MATCH_VC0_SHIFT)




#endif /* HPM_MIPI_CSI_H */

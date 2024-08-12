/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DDRCTL_H
#define HPM_DDRCTL_H

typedef struct {
    __RW uint32_t MSTR;                        /* 0x0: Description: Master Register */
    __R  uint32_t STAT;                        /* 0x4: Description: Operating Mode Status Register */
    __R  uint8_t  RESERVED0[8];                /* 0x8 - 0xF: Reserved */
    __RW uint32_t MRCTRL0;                     /* 0x10: Description: Mode Register Read/Write Control Register 0 */
    __RW uint32_t MRCTRL1;                     /* 0x14: Description: Mode Register Read/Write Control Register 1 */
    __R  uint32_t MRSTAT;                      /* 0x18: Description: Mode Register Read/Write Status Register */
    __R  uint8_t  RESERVED1[20];               /* 0x1C - 0x2F: Reserved */
    __RW uint32_t PWRCTL;                      /* 0x30: Description: Low Power Control Register */
    __RW uint32_t PWRTMG;                      /* 0x34: Description: Low Power Timing Register */
    __RW uint32_t HWLPCTL;                     /* 0x38: Description: Hardware Low Power Control Register */
    __R  uint8_t  RESERVED2[20];               /* 0x3C - 0x4F: Reserved */
    __RW uint32_t RFSHCTL0;                    /* 0x50: Description: Refresh Control Register 0 */
    __RW uint32_t RFSHCTL1;                    /* 0x54: Description: Refresh Control Register 1 */
    __R  uint8_t  RESERVED3[8];                /* 0x58 - 0x5F: Reserved */
    __RW uint32_t RFSHCTL3;                    /* 0x60: Description: Refresh Control Register 0 */
    __RW uint32_t RFSHTMG;                     /* 0x64: Description: Refresh Timing Register */
    __R  uint8_t  RESERVED4[60];               /* 0x68 - 0xA3: Reserved */
    __R  uint32_t ECCUADDR0;                   /* 0xA4: Description: ECC Uncorrected Error Address Register 0 */
    __R  uint8_t  RESERVED5[24];               /* 0xA8 - 0xBF: Reserved */
    __RW uint32_t CRCPARCTL0;                  /* 0xC0: Description: CRC Parity Control Register0 */
    __R  uint8_t  RESERVED6[8];                /* 0xC4 - 0xCB: Reserved */
    __R  uint32_t CRCPARSTAT;                  /* 0xCC: Description: CRC Parity Status Register */
    __RW uint32_t INIT0;                       /* 0xD0: Description: SDRAM Initialization Register 0 */
    __RW uint32_t INIT1;                       /* 0xD4: Description: SDRAM Initialization Register 1 */
    __R  uint8_t  RESERVED7[4];                /* 0xD8 - 0xDB: Reserved */
    __RW uint32_t INIT3;                       /* 0xDC: Description: SDRAM Initialization Register 3 */
    __RW uint32_t INIT4;                       /* 0xE0: Description: SDRAM Initialization Register 4 */
    __RW uint32_t INIT5;                       /* 0xE4: Description: SDRAM Initialization Register 5 */
    __R  uint8_t  RESERVED8[8];                /* 0xE8 - 0xEF: Reserved */
    __RW uint32_t DIMMCTL;                     /* 0xF0: Description: DIMM Control Register */
    __RW uint32_t RANKCTL;                     /* 0xF4: Description: Rank Control Register */
    __R  uint8_t  RESERVED9[8];                /* 0xF8 - 0xFF: Reserved */
    __RW uint32_t DRAMTMG0;                    /* 0x100: Description: SDRAM Timing Register 0 */
    __RW uint32_t DRAMTMG1;                    /* 0x104: Description: SDRAM Timing Register 1 */
    __RW uint32_t DRAMTMG2;                    /* 0x108: Description: SDRAM Timing Register 2 */
    __RW uint32_t DRAMTMG3;                    /* 0x10C: Description: SDRAM Timing Register 3 */
    __RW uint32_t DRAMTMG4;                    /* 0x110: Description: SDRAM Timing Register 4 */
    __RW uint32_t DRAMTMG5;                    /* 0x114: Description: SDRAM Timing Register 5 */
    __R  uint8_t  RESERVED10[8];               /* 0x118 - 0x11F: Reserved */
    __RW uint32_t DRAMTMG8;                    /* 0x120: Description: SDRAM Timing Register 8 */
    __R  uint8_t  RESERVED11[92];              /* 0x124 - 0x17F: Reserved */
    __RW uint32_t ZQCTL0;                      /* 0x180: Description: ZQ Control Register 0 */
    __RW uint32_t ZQCTL1;                      /* 0x184: Description: ZQ Control Register 1 */
    __R  uint8_t  RESERVED12[4];               /* 0x188 - 0x18B: Reserved */
    __R  uint32_t ZQSTAT;                      /* 0x18C: Description: ZQ Status Register */
    __RW uint32_t DFITMG0;                     /* 0x190: Description: DFI Timing Register 0 */
    __RW uint32_t DFITMG1;                     /* 0x194: Description: DFI Timing Register 1 */
    __RW uint32_t DFILPCFG0;                   /* 0x198: Description: DFI Low Power Configuration Register 0 */
    __R  uint8_t  RESERVED13[4];               /* 0x19C - 0x19F: Reserved */
    __RW uint32_t DFIUPD0;                     /* 0x1A0: Description: DFI Update Register 0 */
    __RW uint32_t DFIUPD1;                     /* 0x1A4: Description: DFI Update Register 1 */
    __RW uint32_t DFIUPD2;                     /* 0x1A8: Description: DFI Update Register 2 */
    __RW uint32_t DFIUPD3;                     /* 0x1AC: Description: DFI Update Register 3 */
    __RW uint32_t DFIMISC;                     /* 0x1B0: Description: DFI Miscellaneous Control Register */
    __RW uint32_t DFITMG2;                     /* 0x1B4: Description: DFI Timing Register 2 */
    __R  uint8_t  RESERVED14[72];              /* 0x1B8 - 0x1FF: Reserved */
    __RW uint32_t ADDRMAP0;                    /* 0x200: Description: Address Map Register 0 */
    __RW uint32_t ADDRMAP1;                    /* 0x204: Description: Address Map Register 1 */
    __RW uint32_t ADDRMAP2;                    /* 0x208: Description: Address Map Register 2 */
    __RW uint32_t ADDRMAP3;                    /* 0x20C: Description: Address Map Register 3 */
    __RW uint32_t ADDRMAP4;                    /* 0x210: Description: Address Map Register 4 */
    __RW uint32_t ADDRMAP5;                    /* 0x214: Description: Address Map Register 5 */
    __RW uint32_t ADDRMAP6;                    /* 0x218: Description: Address Map Register 6 */
    __R  uint8_t  RESERVED15[36];              /* 0x21C - 0x23F: Reserved */
    __RW uint32_t ODTCFG;                      /* 0x240: Description: ODT Configuration Register */
    __RW uint32_t ODTMAP;                      /* 0x244: Description: ODT/Rank Map Register */
    __R  uint8_t  RESERVED16[8];               /* 0x248 - 0x24F: Reserved */
    __RW uint32_t SCHED;                       /* 0x250: Description: Scheduler Control Register */
    __RW uint32_t SCHED1;                      /* 0x254: Description: Scheduler Control Register 1 */
    __R  uint8_t  RESERVED17[4];               /* 0x258 - 0x25B: Reserved */
    __RW uint32_t PERFHPR1;                    /* 0x25C: Description: High Priority Read CAM Register 1 */
    __R  uint8_t  RESERVED18[4];               /* 0x260 - 0x263: Reserved */
    __RW uint32_t PERFLPR1;                    /* 0x264: Description: Low Priority Read CAM Register 1 */
    __R  uint8_t  RESERVED19[4];               /* 0x268 - 0x26B: Reserved */
    __RW uint32_t PERFWR1;                     /* 0x26C: Description: Write CAM Register 1 */
    __R  uint8_t  RESERVED20[4];               /* 0x270 - 0x273: Reserved */
    __RW uint32_t PERFVPR1;                    /* 0x274: Description: Variable Priority Read CAM Register 1 */
    __RW uint32_t PERFVPW1;                    /* 0x278: Description: Variable Priority Write CAM Register 1 */
    __R  uint8_t  RESERVED21[132];             /* 0x27C - 0x2FF: Reserved */
    __RW uint32_t DBG0;                        /* 0x300: Description: Debug Register 0 */
    __RW uint32_t DBG1;                        /* 0x304: Description: Debug Register 1 */
    __R  uint32_t DBGCAM;                      /* 0x308: Description: CAM Debug Register */
    __RW uint32_t DBGCMD;                      /* 0x30C: Description: Command Debug Register */
    __R  uint32_t DBGSTAT;                     /* 0x310: Description: Status Debug Register */
    __R  uint8_t  RESERVED22[232];             /* 0x314 - 0x3FB: Reserved */
    __R  uint32_t PSTAT;                       /* 0x3FC: Description: Port Status Register */
    __RW uint32_t PCCFG;                       /* 0x400: Description: Port Common Configuration Register */
    struct {
        __RW uint32_t R;                       /* 0x404: Description: Port n Configuration Read Register */
        __RW uint32_t W;                       /* 0x408: Description: Port n Configuration Write Register */
        __RW uint32_t C;                       /* 0x40C: Description: Port n Common Configuration Register */
        struct {
            __RW uint32_t MASKCH;              /* 0x410: Description: Port n Channel m Configuration ID Mask Register */
            __RW uint32_t VALUECH;             /* 0x414: Description: Port n Channel m Configuration ID Value Register */
        } ID[16];
        __RW uint32_t CTRL;                    /* 0x490: Description: Port n Control Register */
        __RW uint32_t QOS0;                    /* 0x494: Description: Port n Read QoS Configuration Register 0 */
        __RW uint32_t QOS1;                    /* 0x498: Description: Port n Read QoS Configuration Register 1 */
        __RW uint32_t WQOS0;                   /* 0x49C: Description: Port n Write QoS Configuration Register 0 */
        __RW uint32_t WQOS1;                   /* 0x4A0: Description: Port n Write QoS Configuration Register 1 */
        __R  uint8_t  RESERVED0[16];           /* 0x4A4 - 0x4B3: Reserved */
    } PCFG[16];
    struct {
        __RW uint32_t BASE;                    /* 0xF04: Description: SAR Base Address Register n */
        __RW uint32_t SIZE;                    /* 0xF08: Description: SAR Size Register n */
    } SAR[4];
    __RW uint32_t SBRCTL;                      /* 0xF24: Description: Scrubber Control Register */
    __R  uint32_t SBRSTAT;                     /* 0xF28: Description: Scrubber Status Register */
    __RW uint32_t SBRWDATA0;                   /* 0xF2C: Description: Scrubber Write Data Pattern0 */
    __R  uint8_t  RESERVED23[4];               /* 0xF30 - 0xF33: Reserved */
} DDRCTL_Type;


/* Bitfield definition for register: MSTR */
/*
 * ACTIVE_RANKS (R/W)
 *
 * Description: Only present for multi-rank configurations. Each bit represents one rank. For two-rank configurations, only bits[25:24] are present.
 * 1 - populated
 * 0 - unpopulated
 * LSB is the lowest rank number.
 * For 2 ranks following combinations are legal:
 * 01 - One rank
 * 11 - Two ranks
 * Others - Reserved.
 * For 4 ranks following combinations are legal:
 * 0001 - One rank
 * 0011 - Two ranks
 * 1111 - Four ranks
 * Value After Reset: "(MEMC_NUM_RANKS==4) ? 0xF
 * :((MEMC_NUM_RANKS==2) ? 0x3 : 0x1)"
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_MSTR_ACTIVE_RANKS_MASK (0xF000000UL)
#define DDRCTL_MSTR_ACTIVE_RANKS_SHIFT (24U)
#define DDRCTL_MSTR_ACTIVE_RANKS_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_ACTIVE_RANKS_SHIFT) & DDRCTL_MSTR_ACTIVE_RANKS_MASK)
#define DDRCTL_MSTR_ACTIVE_RANKS_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_ACTIVE_RANKS_MASK) >> DDRCTL_MSTR_ACTIVE_RANKS_SHIFT)

/*
 * BURST_RDWR (R/W)
 *
 * Description: SDRAM burst length used:
 * 0001 - Burst length of 2 (only supported for mDDR)
 * 0010 - Burst length of 4
 * 0100 - Burst length of 8
 * 1000 - Burst length of 16 (only supported for mDDR and LPDDR2)
 * All other values are reserved.
 * This controls the burst size used to access the SDRAM. This must match the burst length mode register setting in the SDRAM. Burst length of 2 is not supported with AXI ports when MEMC_BURST_LENGTH is 8.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_MSTR_BURST_RDWR_MASK (0xF0000UL)
#define DDRCTL_MSTR_BURST_RDWR_SHIFT (16U)
#define DDRCTL_MSTR_BURST_RDWR_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_BURST_RDWR_SHIFT) & DDRCTL_MSTR_BURST_RDWR_MASK)
#define DDRCTL_MSTR_BURST_RDWR_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_BURST_RDWR_MASK) >> DDRCTL_MSTR_BURST_RDWR_SHIFT)

/*
 * DLL_OFF_MODE (R/W)
 *
 * Description: Set to 1 when uMCTL2 and DRAM has to be put in DLL-off mode for low frequency operation.
 * Set to 0 to put uMCTL2 and DRAM in DLL-on mode for normal frequency operation.
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3_OR_4==1
 */
#define DDRCTL_MSTR_DLL_OFF_MODE_MASK (0x8000U)
#define DDRCTL_MSTR_DLL_OFF_MODE_SHIFT (15U)
#define DDRCTL_MSTR_DLL_OFF_MODE_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_DLL_OFF_MODE_SHIFT) & DDRCTL_MSTR_DLL_OFF_MODE_MASK)
#define DDRCTL_MSTR_DLL_OFF_MODE_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_DLL_OFF_MODE_MASK) >> DDRCTL_MSTR_DLL_OFF_MODE_SHIFT)

/*
 * DATA_BUS_WIDTH (R/W)
 *
 * Description: Selects proportion of DQ bus width that is used by the SDRAM
 * 00 - Full DQ bus width to SDRAM
 * 01 - Half DQ bus width to SDRAM
 * 10 - Quarter DQ bus width to SDRAM
 * 11 - Reserved.
 * Note that half bus width mode is only supported when the SDRAM bus width is a multiple of 16, and quarter bus width mode is only supported when the SDRAM bus width is a multiple of 32 and the configuration parameter MEMC_QBUS_SUPPORT is set. Bus width refers to DQ bus width (excluding any ECC width).
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_MSTR_DATA_BUS_WIDTH_MASK (0x3000U)
#define DDRCTL_MSTR_DATA_BUS_WIDTH_SHIFT (12U)
#define DDRCTL_MSTR_DATA_BUS_WIDTH_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_DATA_BUS_WIDTH_SHIFT) & DDRCTL_MSTR_DATA_BUS_WIDTH_MASK)
#define DDRCTL_MSTR_DATA_BUS_WIDTH_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_DATA_BUS_WIDTH_MASK) >> DDRCTL_MSTR_DATA_BUS_WIDTH_SHIFT)

/*
 * EN_2T_TIMING_MODE (R/W)
 *
 * Description: If 1, then uMCTL2 uses 2T timing. Otherwise, uses 1T timing. In 2T timing, all command signals (except chip select) are held for 2 clocks on the SDRAM bus. Chip select is asserted on the second cycle of the command
 * Note: 2T timing is not supported in LPDDR2/LPDDR3 mode Note: 2T timing is not supported if the configuration parameter MEMC_CMD_RTN2IDLE is set
 * Note: 2T timing is not supported in DDR4 geardown mode.
 * Value After Reset: 0x0
 * Exists: MEMC_CMD_RTN2IDLE==0
 */
#define DDRCTL_MSTR_EN_2T_TIMING_MODE_MASK (0x400U)
#define DDRCTL_MSTR_EN_2T_TIMING_MODE_SHIFT (10U)
#define DDRCTL_MSTR_EN_2T_TIMING_MODE_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_EN_2T_TIMING_MODE_SHIFT) & DDRCTL_MSTR_EN_2T_TIMING_MODE_MASK)
#define DDRCTL_MSTR_EN_2T_TIMING_MODE_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_EN_2T_TIMING_MODE_MASK) >> DDRCTL_MSTR_EN_2T_TIMING_MODE_SHIFT)

/*
 * BURSTCHOP (R/W)
 *
 * Description: When set, enable burst-chop in DDR3/DDR4. This is only supported in full bus width mode (MSTR.data_bus_width = 00). If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable = 1), burst chop is not supported, and this bit must be set to '0'
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1
 */
#define DDRCTL_MSTR_BURSTCHOP_MASK (0x200U)
#define DDRCTL_MSTR_BURSTCHOP_SHIFT (9U)
#define DDRCTL_MSTR_BURSTCHOP_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_BURSTCHOP_SHIFT) & DDRCTL_MSTR_BURSTCHOP_MASK)
#define DDRCTL_MSTR_BURSTCHOP_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_BURSTCHOP_MASK) >> DDRCTL_MSTR_BURSTCHOP_SHIFT)

/*
 * DDR3 (R/W)
 *
 * Description: Select DDR3 SDRAM
 * 1 - DDR3 SDRAM device in use
 * 0 - non-DDR3 SDRAM device in use Only present in designs that support DDR3.
 * Value After Reset: "(MEMC_DDR3_EN==1) ? 0x1 : 0x0"
 * Exists: MEMC_DDR3==1
 */
#define DDRCTL_MSTR_DDR3_MASK (0x1U)
#define DDRCTL_MSTR_DDR3_SHIFT (0U)
#define DDRCTL_MSTR_DDR3_SET(x) (((uint32_t)(x) << DDRCTL_MSTR_DDR3_SHIFT) & DDRCTL_MSTR_DDR3_MASK)
#define DDRCTL_MSTR_DDR3_GET(x) (((uint32_t)(x) & DDRCTL_MSTR_DDR3_MASK) >> DDRCTL_MSTR_DDR3_SHIFT)

/* Bitfield definition for register: STAT */
/*
 * SELFREF_TYPE (R)
 *
 * Description: Flags if Self Refresh is entered and if it was under Automatic Self Refresh control only or not.
 * 00 - SDRAM is not in Self Refresh
 * 11 - SDRAM is in Self Refresh and Self Refresh was caused by Automatic Self Refresh only
 * 10 - SDRAM is in Self Refresh and Self Refresh was not caused solely under Automatic Self Refresh control. It could have been caused by Hardware Low Power Interface and/or Software (reg_ddrc_selfref_sw).
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_STAT_SELFREF_TYPE_MASK (0x30U)
#define DDRCTL_STAT_SELFREF_TYPE_SHIFT (4U)
#define DDRCTL_STAT_SELFREF_TYPE_GET(x) (((uint32_t)(x) & DDRCTL_STAT_SELFREF_TYPE_MASK) >> DDRCTL_STAT_SELFREF_TYPE_SHIFT)

/*
 * OPERATING_MODE (R)
 *
 * Description: Operating mode. This is 3-bits wide in configurations with mDDR/LPDDR2/LPDDR3/DDR4 support and 2-bits in all other configurations.
 * non-mDDR/LPDDR2/LPDDR3 and non-DDR4 designs:
 * 00 - Init
 * 01 - Normal
 * 10 - Power-down
 * 11 - Self refresh
 * mDDR/LPDDR2/LPDDR3 or DDR4 designs:
 * 000 - Init
 * 001 - Normal
 * 010 - Power-down
 * 011 - Self refresh
 * 1XX - Deep power-down / Maximum Power Saving Mode
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_STAT_OPERATING_MODE_MASK (0x7U)
#define DDRCTL_STAT_OPERATING_MODE_SHIFT (0U)
#define DDRCTL_STAT_OPERATING_MODE_GET(x) (((uint32_t)(x) & DDRCTL_STAT_OPERATING_MODE_MASK) >> DDRCTL_STAT_OPERATING_MODE_SHIFT)

/* Bitfield definition for register: MRCTRL0 */
/*
 * MR_WR (R/W)
 *
 * Description: Setting this register bit to 1 triggers a mode register read or write operation. When the MR operation is complete, the uMCTL2 automatically clears this bit. The other register fields of this register must be written in a separate APB transaction, before setting this mr_wr bit. It is recommended NOT to set this signal if in Init, Deep power- down or MPSM operating modes.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_MRCTRL0_MR_WR_MASK (0x80000000UL)
#define DDRCTL_MRCTRL0_MR_WR_SHIFT (31U)
#define DDRCTL_MRCTRL0_MR_WR_SET(x) (((uint32_t)(x) << DDRCTL_MRCTRL0_MR_WR_SHIFT) & DDRCTL_MRCTRL0_MR_WR_MASK)
#define DDRCTL_MRCTRL0_MR_WR_GET(x) (((uint32_t)(x) & DDRCTL_MRCTRL0_MR_WR_MASK) >> DDRCTL_MRCTRL0_MR_WR_SHIFT)

/*
 * MR_ADDR (R/W)
 *
 * Description: Address of the mode register that is to be written to.
 * 0000 - MR0
 * 0001 - MR1
 * 0010 - MR2
 * 0011 - MR3
 * 0100 - MR4
 * 0101 - MR5
 * 0110 - MR6
 * 0111 - MR7
 * Don't Care for LPDDR2/LPDDR3 (see MRCTRL1.mr_data for mode register addressing in LPDDR2/LPDDR3)
 * This signal is also used for writing to control words of RDIMMs. In that case, it corresponds to the bank address bits sent to the RDIMM
 * In case of DDR4, the bit[3:2] corresponds to the bank group bits. Therefore, the bit[3] as well as the bit[2:0] must be set to an appropriate value which is considered both the Address Mirroring of UDIMMs/RDIMMs and the Output Inversion of RDIMMs.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_MRCTRL0_MR_ADDR_MASK (0xF000U)
#define DDRCTL_MRCTRL0_MR_ADDR_SHIFT (12U)
#define DDRCTL_MRCTRL0_MR_ADDR_SET(x) (((uint32_t)(x) << DDRCTL_MRCTRL0_MR_ADDR_SHIFT) & DDRCTL_MRCTRL0_MR_ADDR_MASK)
#define DDRCTL_MRCTRL0_MR_ADDR_GET(x) (((uint32_t)(x) & DDRCTL_MRCTRL0_MR_ADDR_MASK) >> DDRCTL_MRCTRL0_MR_ADDR_SHIFT)

/*
 * MR_RANK (R/W)
 *
 * Description: Controls which rank is accessed by MRCTRL0.mr_wr. Normally, it is desired to access all ranks, so all bits should be set to 1. However, for multi-rank UDIMMs/RDIMMs which implement address mirroring, it may be necessary to access ranks individually.
 * Examples (assume uMCTL2 is configured for 4 ranks):
 * 0x1 - select rank 0 only
 * 0x2 - select rank 1 only
 * 0x5 - select ranks 0 and 2
 * 0xA - select ranks 1 and 3
 * 0xF - select ranks 0, 1, 2 and 3
 * Value After Reset: "(MEMC_NUM_RANKS==4) ? 0xF
 * :((MEMC_NUM_RANKS==2) ? 0x3 : 0x1)"
 * Exists: Always
 */
#define DDRCTL_MRCTRL0_MR_RANK_MASK (0xF0U)
#define DDRCTL_MRCTRL0_MR_RANK_SHIFT (4U)
#define DDRCTL_MRCTRL0_MR_RANK_SET(x) (((uint32_t)(x) << DDRCTL_MRCTRL0_MR_RANK_SHIFT) & DDRCTL_MRCTRL0_MR_RANK_MASK)
#define DDRCTL_MRCTRL0_MR_RANK_GET(x) (((uint32_t)(x) & DDRCTL_MRCTRL0_MR_RANK_MASK) >> DDRCTL_MRCTRL0_MR_RANK_SHIFT)

/* Bitfield definition for register: MRCTRL1 */
/*
 * MR_DATA (R/W)
 *
 * Description: Mode register write data for all non- LPDDR2/non-LPDDR3 modes.
 * For LPDDR2/LPDDR3, MRCTRL1[15:0] are interpreted as [15:8] MR Address and [7:0] MR data for writes, don't care for reads. This is 18-bits wide in configurations with DDR4 support and 16-bits in all other configurations.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_MRCTRL1_MR_DATA_MASK (0x3FFFFUL)
#define DDRCTL_MRCTRL1_MR_DATA_SHIFT (0U)
#define DDRCTL_MRCTRL1_MR_DATA_SET(x) (((uint32_t)(x) << DDRCTL_MRCTRL1_MR_DATA_SHIFT) & DDRCTL_MRCTRL1_MR_DATA_MASK)
#define DDRCTL_MRCTRL1_MR_DATA_GET(x) (((uint32_t)(x) & DDRCTL_MRCTRL1_MR_DATA_MASK) >> DDRCTL_MRCTRL1_MR_DATA_SHIFT)

/* Bitfield definition for register: MRSTAT */
/*
 * MR_WR_BUSY (R)
 *
 * Description: The SoC core may initiate a MR write operation only if this signal is low. This signal goes high in the clock after the uMCTL2 accepts the MRW/MRR request. It goes low when the MRW/MRR command is issued to the SDRAM. It is recommended not to perform MRW/MRR commands when 'MRSTAT.mr_wr_busy' is high.
 * 0 - Indicates that the SoC core can initiate a mode register write operation
 * 1 - Indicates that mode register write operation is in progress
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_MRSTAT_MR_WR_BUSY_MASK (0x1U)
#define DDRCTL_MRSTAT_MR_WR_BUSY_SHIFT (0U)
#define DDRCTL_MRSTAT_MR_WR_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_MRSTAT_MR_WR_BUSY_MASK) >> DDRCTL_MRSTAT_MR_WR_BUSY_SHIFT)

/* Bitfield definition for register: PWRCTL */
/*
 * SELFREF_SW (R/W)
 *
 * Description: A value of 1 to this register causes system to move to Self Refresh state immediately, as long as it is not in INIT or DPD/MPSM operating_mode. This is referred to as Software Entry/Exit to Self Refresh.
 * 1 - Software Entry to Self Refresh
 * 0 - Software Exit from Self Refresh
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PWRCTL_SELFREF_SW_MASK (0x20U)
#define DDRCTL_PWRCTL_SELFREF_SW_SHIFT (5U)
#define DDRCTL_PWRCTL_SELFREF_SW_SET(x) (((uint32_t)(x) << DDRCTL_PWRCTL_SELFREF_SW_SHIFT) & DDRCTL_PWRCTL_SELFREF_SW_MASK)
#define DDRCTL_PWRCTL_SELFREF_SW_GET(x) (((uint32_t)(x) & DDRCTL_PWRCTL_SELFREF_SW_MASK) >> DDRCTL_PWRCTL_SELFREF_SW_SHIFT)

/*
 * EN_DFI_DRAM_CLK_DISABLE (R/W)
 *
 * Description: Enable the assertion of dfi_dram_clk_disable whenever a clock is not required by the SDRAM.
 * If set to 0, dfi_dram_clk_disable is never asserted. Assertion of dfi_dram_clk_disable is as follows:
 * In DDR2/DDR3, can only be asserted in Self Refresh. In DDR4, can be asserted in following:
 * in Self Refresh.
 * in Maximum Power Saving Mode
 * In mDDR/LPDDR2/LPDDR3, can be asserted in following:
 * in Self Refresh
 * in Power Down
 * in Deep Power Down
 * during Normal operation (Clock Stop)
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_MASK (0x8U)
#define DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_SHIFT (3U)
#define DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_SET(x) (((uint32_t)(x) << DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_SHIFT) & DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_MASK)
#define DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_GET(x) (((uint32_t)(x) & DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_MASK) >> DDRCTL_PWRCTL_EN_DFI_DRAM_CLK_DISABLE_SHIFT)

/*
 * POWERDOWN_EN (R/W)
 *
 * Description: If true then the uMCTL2 goes into power-down after a programmable number of cycles "maximum idle clocks before power down" (PWRTMG.powerdown_to_x32).
 * This register bit may be re-programmed during the course of normal operation.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PWRCTL_POWERDOWN_EN_MASK (0x2U)
#define DDRCTL_PWRCTL_POWERDOWN_EN_SHIFT (1U)
#define DDRCTL_PWRCTL_POWERDOWN_EN_SET(x) (((uint32_t)(x) << DDRCTL_PWRCTL_POWERDOWN_EN_SHIFT) & DDRCTL_PWRCTL_POWERDOWN_EN_MASK)
#define DDRCTL_PWRCTL_POWERDOWN_EN_GET(x) (((uint32_t)(x) & DDRCTL_PWRCTL_POWERDOWN_EN_MASK) >> DDRCTL_PWRCTL_POWERDOWN_EN_SHIFT)

/*
 * SELFREF_EN (R/W)
 *
 * Description: If true then the uMCTL2 puts the SDRAM into Self Refresh after a programmable number of cycles "maximum idle clocks before Self Refresh (PWRTMG.selfref_to_x32)". This register bit may be re- programmed during the course of normal operation.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PWRCTL_SELFREF_EN_MASK (0x1U)
#define DDRCTL_PWRCTL_SELFREF_EN_SHIFT (0U)
#define DDRCTL_PWRCTL_SELFREF_EN_SET(x) (((uint32_t)(x) << DDRCTL_PWRCTL_SELFREF_EN_SHIFT) & DDRCTL_PWRCTL_SELFREF_EN_MASK)
#define DDRCTL_PWRCTL_SELFREF_EN_GET(x) (((uint32_t)(x) & DDRCTL_PWRCTL_SELFREF_EN_MASK) >> DDRCTL_PWRCTL_SELFREF_EN_SHIFT)

/* Bitfield definition for register: PWRTMG */
/*
 * SELFREF_TO_X32 (R/W)
 *
 * Description: After this many clocks of NOP or deselect the uMCTL2 automatically puts the SDRAM into Self Refresh. This must be enabled in the PWRCTL.selfref_en.
 * Unit: Multiples of 32 clocks. FOR PERFORMANCE ONLY.
 * Value After Reset: 0x40
 * Exists: Always
 */
#define DDRCTL_PWRTMG_SELFREF_TO_X32_MASK (0xFF0000UL)
#define DDRCTL_PWRTMG_SELFREF_TO_X32_SHIFT (16U)
#define DDRCTL_PWRTMG_SELFREF_TO_X32_SET(x) (((uint32_t)(x) << DDRCTL_PWRTMG_SELFREF_TO_X32_SHIFT) & DDRCTL_PWRTMG_SELFREF_TO_X32_MASK)
#define DDRCTL_PWRTMG_SELFREF_TO_X32_GET(x) (((uint32_t)(x) & DDRCTL_PWRTMG_SELFREF_TO_X32_MASK) >> DDRCTL_PWRTMG_SELFREF_TO_X32_SHIFT)

/*
 * POWERDOWN_TO_X32 (R/W)
 *
 * Description: After this many clocks of NOP or deselect the uMCTL2 automatically puts the SDRAM into power-down. This must be enabled in the PWRCTL.powerdown_en.
 * Unit: Multiples of 32 clocks FOR PERFORMANCE ONLY.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_PWRTMG_POWERDOWN_TO_X32_MASK (0x1FU)
#define DDRCTL_PWRTMG_POWERDOWN_TO_X32_SHIFT (0U)
#define DDRCTL_PWRTMG_POWERDOWN_TO_X32_SET(x) (((uint32_t)(x) << DDRCTL_PWRTMG_POWERDOWN_TO_X32_SHIFT) & DDRCTL_PWRTMG_POWERDOWN_TO_X32_MASK)
#define DDRCTL_PWRTMG_POWERDOWN_TO_X32_GET(x) (((uint32_t)(x) & DDRCTL_PWRTMG_POWERDOWN_TO_X32_MASK) >> DDRCTL_PWRTMG_POWERDOWN_TO_X32_SHIFT)

/* Bitfield definition for register: HWLPCTL */
/*
 * HW_LP_IDLE_X32 (R/W)
 *
 * Description: Hardware idle period. The cactive_ddrc output is driven low if the system is idle for hw_lp_idle * 32 cycles if not in INIT or DPD/MPSM operating_mode. The hardware idle function is disabled when hw_lp_idle_x32=0.
 * Unit: Multiples of 32 clocks. FOR PERFORMANCE ONLY.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_HWLPCTL_HW_LP_IDLE_X32_MASK (0xFFF0000UL)
#define DDRCTL_HWLPCTL_HW_LP_IDLE_X32_SHIFT (16U)
#define DDRCTL_HWLPCTL_HW_LP_IDLE_X32_SET(x) (((uint32_t)(x) << DDRCTL_HWLPCTL_HW_LP_IDLE_X32_SHIFT) & DDRCTL_HWLPCTL_HW_LP_IDLE_X32_MASK)
#define DDRCTL_HWLPCTL_HW_LP_IDLE_X32_GET(x) (((uint32_t)(x) & DDRCTL_HWLPCTL_HW_LP_IDLE_X32_MASK) >> DDRCTL_HWLPCTL_HW_LP_IDLE_X32_SHIFT)

/*
 * HW_LP_EXIT_IDLE_EN (R/W)
 *
 * Description: When this bit is programmed to 1 the cactive_in_ddrc pin of the DDRC can be used to exit from the automatic clock stop, automatic power down or automatic self-refresh modes. Note, it will not cause exit of Self-Refresh that was caused by Hardware Low Power Interface and/or Software (PWRCTL.selfref_sw).
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_MASK (0x2U)
#define DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_SHIFT (1U)
#define DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_SET(x) (((uint32_t)(x) << DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_SHIFT) & DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_MASK)
#define DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_GET(x) (((uint32_t)(x) & DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_MASK) >> DDRCTL_HWLPCTL_HW_LP_EXIT_IDLE_EN_SHIFT)

/*
 * HW_LP_EN (R/W)
 *
 * Description: Enable for Hardware Low Power Interface.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_HWLPCTL_HW_LP_EN_MASK (0x1U)
#define DDRCTL_HWLPCTL_HW_LP_EN_SHIFT (0U)
#define DDRCTL_HWLPCTL_HW_LP_EN_SET(x) (((uint32_t)(x) << DDRCTL_HWLPCTL_HW_LP_EN_SHIFT) & DDRCTL_HWLPCTL_HW_LP_EN_MASK)
#define DDRCTL_HWLPCTL_HW_LP_EN_GET(x) (((uint32_t)(x) & DDRCTL_HWLPCTL_HW_LP_EN_MASK) >> DDRCTL_HWLPCTL_HW_LP_EN_SHIFT)

/* Bitfield definition for register: RFSHCTL0 */
/*
 * REFRESH_MARGIN (R/W)
 *
 * Description: Threshold value in number of clock cycles before the critical refresh or page timer expires. A critical refresh is to be issued before this threshold is reached. It is recommended that this not be changed from the default value, currently shown as 0x2. It must always be less than internally used t_rfc_nom_x32. Note that, in LPDDR2/LPDDR3, internally used t_rfc_nom_x32 may be equal to RFSHTMG.t_rfc_nom_x32>>2 if derating is enabled (DERATEEN.derate_enable=1). Otherwise, internally used t_rfc_nom_x32 will be equal to RFSHTMG.t_rfc_nom_x32.
 * Unit: Multiples of 32 clocks. Value After Reset: 0x2 Exists: Always
 */
#define DDRCTL_RFSHCTL0_REFRESH_MARGIN_MASK (0xF00000UL)
#define DDRCTL_RFSHCTL0_REFRESH_MARGIN_SHIFT (20U)
#define DDRCTL_RFSHCTL0_REFRESH_MARGIN_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL0_REFRESH_MARGIN_SHIFT) & DDRCTL_RFSHCTL0_REFRESH_MARGIN_MASK)
#define DDRCTL_RFSHCTL0_REFRESH_MARGIN_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL0_REFRESH_MARGIN_MASK) >> DDRCTL_RFSHCTL0_REFRESH_MARGIN_SHIFT)

/*
 * REFRESH_TO_X32 (R/W)
 *
 * Description: If the refresh timer (tRFCnom, also known as tREFI) has expired at least once, but it has not expired (RFSHCTL0.refresh_burst+1) times yet, then a speculative refresh may be performed. A speculative refresh is a refresh performed at a time when refresh would be useful, but before it is absolutely required. When the SDRAM bus is idle for a period of time determined by this RFSHCTL0.refresh_to_x32 and the refresh timer has expired at least once since the last refresh, then a speculative refresh is performed. Speculative refreshes continues successively until there are no refreshes pending or until new reads or writes are issued to the uMCTL2.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_RFSHCTL0_REFRESH_TO_X32_MASK (0x1F000UL)
#define DDRCTL_RFSHCTL0_REFRESH_TO_X32_SHIFT (12U)
#define DDRCTL_RFSHCTL0_REFRESH_TO_X32_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL0_REFRESH_TO_X32_SHIFT) & DDRCTL_RFSHCTL0_REFRESH_TO_X32_MASK)
#define DDRCTL_RFSHCTL0_REFRESH_TO_X32_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL0_REFRESH_TO_X32_MASK) >> DDRCTL_RFSHCTL0_REFRESH_TO_X32_SHIFT)

/*
 * REFRESH_BURST (R/W)
 *
 * Description: The programmed value + 1 is the number of refresh timeouts that is allowed to accumulate before traffic is blocked and the refreshes are forced to execute. Closing pages to perform a refresh is a one-time penalty that must be paid for each group of refreshes. Therefore, performing refreshes in a burst reduces the per-refresh penalty of these page closings. Higher numbers for RFSHCTL.refresh_burst slightly increases utilization; lower numbers decreases the worst-case latency associated with refreshes.
 * 0 - single refresh
 * 1 - burst-of-2 refresh
 * 7 - burst-of-8 refresh
 * For information on burst refresh feature refer to section 3.9 of DDR2 JEDEC specification - JESD79-2F.pdf.
 * For DDR2/3, the refresh is always per-rank and not per- bank. The rank refresh can be accumulated over 8*tREFI cycles using the burst refresh feature. In DDR4 mode, according to Fine Granuarity feature, 8 refreshes can be postponed in 1X mode, 16 refreshes in 2X mode and 32 refreshes in 4X mode. If using PHY-initiated updates, care must be taken in the setting of RFSHCTL0.refresh_burst, to ensure that tRFCmax is not violated due to a PHY-initiated update occurring shortly before a refresh burst was due. In this situation, the refresh burst will be delayed until the PHY- initiated update is complete.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_RFSHCTL0_REFRESH_BURST_MASK (0x1F0U)
#define DDRCTL_RFSHCTL0_REFRESH_BURST_SHIFT (4U)
#define DDRCTL_RFSHCTL0_REFRESH_BURST_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL0_REFRESH_BURST_SHIFT) & DDRCTL_RFSHCTL0_REFRESH_BURST_MASK)
#define DDRCTL_RFSHCTL0_REFRESH_BURST_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL0_REFRESH_BURST_MASK) >> DDRCTL_RFSHCTL0_REFRESH_BURST_SHIFT)

/* Bitfield definition for register: RFSHCTL1 */
/*
 * REFRESH_TIMER1_START_VALUE_X32 (R/W)
 *
 * Description: Refresh timer start for rank 1 (only present in multi-rank configurations). This is useful in staggering the refreshes to multiple ranks to help traffic to proceed. This is explained in Refresh Controls section of architecture chapter.
 * Unit: Multiples of 32 clocks. FOR PERFORMANCE ONLY.
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_MASK (0xFFF0000UL)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_SHIFT (16U)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_SHIFT) & DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_MASK)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_MASK) >> DDRCTL_RFSHCTL1_REFRESH_TIMER1_START_VALUE_X32_SHIFT)

/*
 * REFRESH_TIMER0_START_VALUE_X32 (R/W)
 *
 * Description: Refresh timer start for rank 0 (only present in multi-rank configurations). This is useful in staggering the refreshes to multiple ranks to help traffic to proceed. This is explained in Refresh Controls section of architecture chapter.
 * Unit: Multiples of 32 clocks. FOR PERFORMANCE ONLY.
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_MASK (0xFFFU)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_SHIFT (0U)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_SHIFT) & DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_MASK)
#define DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_MASK) >> DDRCTL_RFSHCTL1_REFRESH_TIMER0_START_VALUE_X32_SHIFT)

/* Bitfield definition for register: RFSHCTL3 */
/*
 * REFRESH_UPDATE_LEVEL (R/W)
 *
 * Description: Toggle this signal (either from 0 to 1 or from 1 to 0) to indicate that the refresh register(s) have been updated.
 * The value is automatically updated when exiting soft reset, so it does not need to be toggled initially.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_MASK (0x2U)
#define DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_SHIFT (1U)
#define DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_SHIFT) & DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_MASK)
#define DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_MASK) >> DDRCTL_RFSHCTL3_REFRESH_UPDATE_LEVEL_SHIFT)

/*
 * DIS_AUTO_REFRESH (R/W)
 *
 * Description: When '1', disable auto-refresh generated by the uMCTL2. When auto-refresh is disabled, the SoC core must generate refreshes using the registers reg_ddrc_rank0_refresh, reg_ddrc_rank1_refresh, reg_ddrc_rank2_refresh and reg_ddrc_rank3_refresh.
 * When dis_auto_refresh transitions from 0 to 1, any pending refreshes are immediately scheduled by the uMCTL2.
 * If DDR4 CRC/parity retry is enabled (CRCPARCTL1.crc_parity_retry_enable = 1), disable auto- refresh is not supported, and this bit must be set to '0'.
 * This register field is changeable on the fly.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_MASK (0x1U)
#define DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_SHIFT (0U)
#define DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_SET(x) (((uint32_t)(x) << DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_SHIFT) & DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_MASK)
#define DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_GET(x) (((uint32_t)(x) & DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_MASK) >> DDRCTL_RFSHCTL3_DIS_AUTO_REFRESH_SHIFT)

/* Bitfield definition for register: RFSHTMG */
/*
 * T_RFC_NOM_X32 (R/W)
 *
 * Description: tREFI: Average time interval between refreshes per rank (specification: 7.8us for DDR2, DDR3 and DDR4. See JEDEC specification for mDDR, LPDDR2 and LPDDR3).
 * For LPDDR2/LPDDR3:
 * if using all-bank refreshes (RFSHCTL0.per_bank_refresh
 * = 0), this register should be set to tREFIab
 * if using per-bank refreshes (RFSHCTL0.per_bank_refresh = 1), this register should be set to tREFIpb
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tREFI/2), no rounding up.
 * In DDR4 mode, tREFI value is different depending on the refresh mode. The user should program the appropriate value from the spec based on the value programmed in the refresh mode register.
 * Note that RFSHTMG.t_rfc_nom_x32 * 32 must be greater than RFSHTMG.t_rfc_min. Unit: Multiples of 32 clocks.
 * Value After Reset: 0x62
 * Exists: Always
 */
#define DDRCTL_RFSHTMG_T_RFC_NOM_X32_MASK (0xFFF0000UL)
#define DDRCTL_RFSHTMG_T_RFC_NOM_X32_SHIFT (16U)
#define DDRCTL_RFSHTMG_T_RFC_NOM_X32_SET(x) (((uint32_t)(x) << DDRCTL_RFSHTMG_T_RFC_NOM_X32_SHIFT) & DDRCTL_RFSHTMG_T_RFC_NOM_X32_MASK)
#define DDRCTL_RFSHTMG_T_RFC_NOM_X32_GET(x) (((uint32_t)(x) & DDRCTL_RFSHTMG_T_RFC_NOM_X32_MASK) >> DDRCTL_RFSHTMG_T_RFC_NOM_X32_SHIFT)

/*
 * T_RFC_MIN (R/W)
 *
 * Description: tRFC (min): Minimum time from refresh to refresh or activate.
 * For LPDDR2/LPDDR3:
 * if using all-bank refreshes (RFSHCTL0.per_bank_refresh
 * = 0), this register should be set to tRFCab
 * if using per-bank refreshes (RFSHCTL0.per_bank_refresh = 1), this register should be set to tRFCpb
 * For configurations with MEMC_FREQ_RATIO=2, program this to tRFC(min)/2 and round up to next integer value.
 * In DDR4 mode, tRFC(min) value is different depending on the refresh mode (fixed 1X,2X,4X) and the device density. The user should program the appropriate value from the spec based on the 'refresh_mode' and the device density that is used.
 * Unit: Clocks.
 * Value After Reset: 0x8c
 * Exists: Always
 */
#define DDRCTL_RFSHTMG_T_RFC_MIN_MASK (0x1FFU)
#define DDRCTL_RFSHTMG_T_RFC_MIN_SHIFT (0U)
#define DDRCTL_RFSHTMG_T_RFC_MIN_SET(x) (((uint32_t)(x) << DDRCTL_RFSHTMG_T_RFC_MIN_SHIFT) & DDRCTL_RFSHTMG_T_RFC_MIN_MASK)
#define DDRCTL_RFSHTMG_T_RFC_MIN_GET(x) (((uint32_t)(x) & DDRCTL_RFSHTMG_T_RFC_MIN_MASK) >> DDRCTL_RFSHTMG_T_RFC_MIN_SHIFT)

/* Bitfield definition for register: ECCUADDR0 */
/*
 * ECC_UNCORR_RANK (R)
 *
 * Description: Rank number of a read resulting in an uncorrected ECC error
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_ECCUADDR0_ECC_UNCORR_RANK_MASK (0x3000000UL)
#define DDRCTL_ECCUADDR0_ECC_UNCORR_RANK_SHIFT (24U)
#define DDRCTL_ECCUADDR0_ECC_UNCORR_RANK_GET(x) (((uint32_t)(x) & DDRCTL_ECCUADDR0_ECC_UNCORR_RANK_MASK) >> DDRCTL_ECCUADDR0_ECC_UNCORR_RANK_SHIFT)

/*
 * ECC_UNCORR_ROW (R)
 *
 * Description: Page/row number of a read resulting in an uncorrected ECC error. This is 18-bits wide in configurations with DDR4 support and 16-bits in all other configurations.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ECCUADDR0_ECC_UNCORR_ROW_MASK (0x3FFFFUL)
#define DDRCTL_ECCUADDR0_ECC_UNCORR_ROW_SHIFT (0U)
#define DDRCTL_ECCUADDR0_ECC_UNCORR_ROW_GET(x) (((uint32_t)(x) & DDRCTL_ECCUADDR0_ECC_UNCORR_ROW_MASK) >> DDRCTL_ECCUADDR0_ECC_UNCORR_ROW_SHIFT)

/* Bitfield definition for register: CRCPARCTL0 */
/*
 * DFI_ALERT_ERR_CNT_CLR (R/W1C)
 *
 * Description: DFI alert error count clear. Clear bit for DFI alert error counter. Asserting this bit will clear the DFI alert error counter, CRCPARSTAT.dfi_alert_err_cnt. When the clear operation is complete, the uMCTL2 automatically clears this bit.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_MASK (0x4U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_SHIFT (2U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_SET(x) (((uint32_t)(x) << DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_SHIFT) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_MASK)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_GET(x) (((uint32_t)(x) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_MASK) >> DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_CNT_CLR_SHIFT)

/*
 * DFI_ALERT_ERR_INT_CLR (R/W1C)
 *
 * Description: Interrupt clear bit for DFI alert error. If this bit is set, the alert error interrupt on CRCPARSTAT.dfi_alert_err_int will be cleared. When the clear operation is complete, the uMCTL2 automatically clears this bit.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_MASK (0x2U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_SHIFT (1U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_SET(x) (((uint32_t)(x) << DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_SHIFT) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_MASK)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_GET(x) (((uint32_t)(x) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_MASK) >> DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_CLR_SHIFT)

/*
 * DFI_ALERT_ERR_INT_EN (R/W)
 *
 * Description: Interrupt enable bit for DFI alert error. If this bit is set, any parity/CRC error detected on the dfi_alert_n input will result in an interrupt being set on CRCPARSTAT.dfi_alert_err_int.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_MASK (0x1U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_SHIFT (0U)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_SET(x) (((uint32_t)(x) << DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_SHIFT) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_MASK)
#define DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_GET(x) (((uint32_t)(x) & DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_MASK) >> DDRCTL_CRCPARCTL0_DFI_ALERT_ERR_INT_EN_SHIFT)

/* Bitfield definition for register: CRCPARSTAT */
/*
 * DFI_ALERT_ERR_INT (R)
 *
 * Description: DFI alert error interrupt.
 * If a parity/CRC error is detected on dfi_alert_n, and the interrupt is enabled by CRCPARCTL0.dfi_alert_err_int_en, this interrupt bit will be set. It will remain set until cleared by CRCPARCTL0.dfi_alert_err_int_clr
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_INT_MASK (0x10000UL)
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_INT_SHIFT (16U)
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_INT_GET(x) (((uint32_t)(x) & DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_INT_MASK) >> DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_INT_SHIFT)

/*
 * DFI_ALERT_ERR_CNT (R)
 *
 * Description: DFI alert error count.
 * If a parity/CRC error is detected on dfi_alert_n, this counter be incremented. This is independent of the setting of CRCPARCTL0.dfi_alert_err_int_en. It will saturate at 0xFFFF, and can be cleared by asserting CRCPARCTL0.dfi_alert_err_cnt_clr.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_CNT_MASK (0xFFFFU)
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_CNT_SHIFT (0U)
#define DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_CNT_GET(x) (((uint32_t)(x) & DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_CNT_MASK) >> DDRCTL_CRCPARSTAT_DFI_ALERT_ERR_CNT_SHIFT)

/* Bitfield definition for register: INIT0 */
/*
 * SKIP_DRAM_INIT (R/W)
 *
 * Description: If lower bit is enabled the SDRAM initialization routine is skipped. The upper bit decides what state the controller starts up in when reset is removed
 * 00 - SDRAM Initialization routine is run after power-up
 * 01 - SDRAM Initialization routine is skipped after power- up. Controller starts up in Normal Mode
 * 11 - SDRAM Initialization routine is skipped after power- up. Controller starts up in Self-refresh Mode
 * 10 - SDRAM Initialization routine is run after power-up.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT0_SKIP_DRAM_INIT_MASK (0xC0000000UL)
#define DDRCTL_INIT0_SKIP_DRAM_INIT_SHIFT (30U)
#define DDRCTL_INIT0_SKIP_DRAM_INIT_SET(x) (((uint32_t)(x) << DDRCTL_INIT0_SKIP_DRAM_INIT_SHIFT) & DDRCTL_INIT0_SKIP_DRAM_INIT_MASK)
#define DDRCTL_INIT0_SKIP_DRAM_INIT_GET(x) (((uint32_t)(x) & DDRCTL_INIT0_SKIP_DRAM_INIT_MASK) >> DDRCTL_INIT0_SKIP_DRAM_INIT_SHIFT)

/*
 * POST_CKE_X1024 (R/W)
 *
 * Description: Cycles to wait after driving CKE high to start the SDRAM initialization sequence.
 * Unit: 1024 clocks.
 * DDR2 typically requires a 400 ns delay, requiring this value to be programmed to 2 at all clock speeds.
 * LPDDR2/LPDDR3 typically requires this to be programmed for a delay of 200 us.
 * For configurations with MEMC_FREQ_RATIO=2, program this to JEDEC spec value divided by 2, and round it up to next integer value.
 * Value After Reset: 0x2
 * Exists: Always
 */
#define DDRCTL_INIT0_POST_CKE_X1024_MASK (0x3FF0000UL)
#define DDRCTL_INIT0_POST_CKE_X1024_SHIFT (16U)
#define DDRCTL_INIT0_POST_CKE_X1024_SET(x) (((uint32_t)(x) << DDRCTL_INIT0_POST_CKE_X1024_SHIFT) & DDRCTL_INIT0_POST_CKE_X1024_MASK)
#define DDRCTL_INIT0_POST_CKE_X1024_GET(x) (((uint32_t)(x) & DDRCTL_INIT0_POST_CKE_X1024_MASK) >> DDRCTL_INIT0_POST_CKE_X1024_SHIFT)

/*
 * PRE_CKE_X1024 (R/W)
 *
 * Description: Cycles to wait after reset before driving CKE high to start the SDRAM initialization sequence.
 * Unit: 1024 clock cycles.
 * DDR2 specifications typically require this to be programmed for a delay of >= 200 us.
 * LPDDR2/LPDDR3: tINIT1 of 100 ns (min)
 * For configurations with MEMC_FREQ_RATIO=2, program this to JEDEC spec value divided by 2, and round it up to next integer value.
 * Value After Reset: 0x4e
 * Exists: Always
 */
#define DDRCTL_INIT0_PRE_CKE_X1024_MASK (0x3FFU)
#define DDRCTL_INIT0_PRE_CKE_X1024_SHIFT (0U)
#define DDRCTL_INIT0_PRE_CKE_X1024_SET(x) (((uint32_t)(x) << DDRCTL_INIT0_PRE_CKE_X1024_SHIFT) & DDRCTL_INIT0_PRE_CKE_X1024_MASK)
#define DDRCTL_INIT0_PRE_CKE_X1024_GET(x) (((uint32_t)(x) & DDRCTL_INIT0_PRE_CKE_X1024_MASK) >> DDRCTL_INIT0_PRE_CKE_X1024_SHIFT)

/* Bitfield definition for register: INIT1 */
/*
 * DRAM_RSTN_X1024 (R/W)
 *
 * Description: Number of cycles to assert SDRAM reset signal during init sequence.
 * This is only present for designs supporting DDR3/DDR4 devices. For use with a Synopsys DDR PHY, this should be set to a minimum of 1
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1
 */
#define DDRCTL_INIT1_DRAM_RSTN_X1024_MASK (0xFF0000UL)
#define DDRCTL_INIT1_DRAM_RSTN_X1024_SHIFT (16U)
#define DDRCTL_INIT1_DRAM_RSTN_X1024_SET(x) (((uint32_t)(x) << DDRCTL_INIT1_DRAM_RSTN_X1024_SHIFT) & DDRCTL_INIT1_DRAM_RSTN_X1024_MASK)
#define DDRCTL_INIT1_DRAM_RSTN_X1024_GET(x) (((uint32_t)(x) & DDRCTL_INIT1_DRAM_RSTN_X1024_MASK) >> DDRCTL_INIT1_DRAM_RSTN_X1024_SHIFT)

/*
 * FINAL_WAIT_X32 (R/W)
 *
 * Description: Cycles to wait after completing the SDRAM initialization sequence before starting the dynamic scheduler.
 * Unit: Counts of a global timer that pulses every 32 clock cycles.
 * There is no known specific requirement for this; it may be set to zero.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT1_FINAL_WAIT_X32_MASK (0x7F00U)
#define DDRCTL_INIT1_FINAL_WAIT_X32_SHIFT (8U)
#define DDRCTL_INIT1_FINAL_WAIT_X32_SET(x) (((uint32_t)(x) << DDRCTL_INIT1_FINAL_WAIT_X32_SHIFT) & DDRCTL_INIT1_FINAL_WAIT_X32_MASK)
#define DDRCTL_INIT1_FINAL_WAIT_X32_GET(x) (((uint32_t)(x) & DDRCTL_INIT1_FINAL_WAIT_X32_MASK) >> DDRCTL_INIT1_FINAL_WAIT_X32_SHIFT)

/*
 * PRE_OCD_X32 (R/W)
 *
 * Description: Wait period before driving the OCD complete command to SDRAM.
 * Unit: Counts of a global timer that pulses every 32 clock cycles.
 * There is no known specific requirement for this; it may be set to zero.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT1_PRE_OCD_X32_MASK (0xFU)
#define DDRCTL_INIT1_PRE_OCD_X32_SHIFT (0U)
#define DDRCTL_INIT1_PRE_OCD_X32_SET(x) (((uint32_t)(x) << DDRCTL_INIT1_PRE_OCD_X32_SHIFT) & DDRCTL_INIT1_PRE_OCD_X32_MASK)
#define DDRCTL_INIT1_PRE_OCD_X32_GET(x) (((uint32_t)(x) & DDRCTL_INIT1_PRE_OCD_X32_MASK) >> DDRCTL_INIT1_PRE_OCD_X32_SHIFT)

/* Bitfield definition for register: INIT3 */
/*
 * MR (R/W)
 *
 * Description: DDR2: Value to write to MR register. Bit 8 is for DLL and the setting here is ignored. The uMCTL2 sets this bit appropriately.
 * DDR3/DDR4: Value loaded into MR0 register. mDDR: Value to write to MR register.
 * LPDDR2/LPDDR3 - Value to write to MR1 register
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT3_MR_MASK (0xFFFF0000UL)
#define DDRCTL_INIT3_MR_SHIFT (16U)
#define DDRCTL_INIT3_MR_SET(x) (((uint32_t)(x) << DDRCTL_INIT3_MR_SHIFT) & DDRCTL_INIT3_MR_MASK)
#define DDRCTL_INIT3_MR_GET(x) (((uint32_t)(x) & DDRCTL_INIT3_MR_MASK) >> DDRCTL_INIT3_MR_SHIFT)

/*
 * EMR (R/W)
 *
 * Description: DDR2: Value to write to EMR register. Bits 9:7 are for OCD and the setting in this register is ignored. The uMCTL2 sets those bits appropriately.
 * DDR3/DDR4: Value to write to MR1 register Set bit 7 to 0. If PHY-evaluation mode training is enabled, this bit is set appropriately by the uMCTL2 during write leveling.
 * mDDR: Value to write to EMR register. LPDDR2/LPDDR3 - Value to write to MR2 register Value After Reset: 0x510
 * Exists: Always
 */
#define DDRCTL_INIT3_EMR_MASK (0xFFFFU)
#define DDRCTL_INIT3_EMR_SHIFT (0U)
#define DDRCTL_INIT3_EMR_SET(x) (((uint32_t)(x) << DDRCTL_INIT3_EMR_SHIFT) & DDRCTL_INIT3_EMR_MASK)
#define DDRCTL_INIT3_EMR_GET(x) (((uint32_t)(x) & DDRCTL_INIT3_EMR_MASK) >> DDRCTL_INIT3_EMR_SHIFT)

/* Bitfield definition for register: INIT4 */
/*
 * EMR2 (R/W)
 *
 * Description: DDR2: Value to write to EMR2 register. DDR3/DDR4: Value to write to MR2 register LPDDR2/LPDDR3: Value to write to MR3 register mDDR: Unused
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT4_EMR2_MASK (0xFFFF0000UL)
#define DDRCTL_INIT4_EMR2_SHIFT (16U)
#define DDRCTL_INIT4_EMR2_SET(x) (((uint32_t)(x) << DDRCTL_INIT4_EMR2_SHIFT) & DDRCTL_INIT4_EMR2_MASK)
#define DDRCTL_INIT4_EMR2_GET(x) (((uint32_t)(x) & DDRCTL_INIT4_EMR2_MASK) >> DDRCTL_INIT4_EMR2_SHIFT)

/*
 * EMR3 (R/W)
 *
 * Description: DDR2: Value to write to EMR3 register. DDR3/DDR4: Value to write to MR3 register mDDR/LPDDR2/LPDDR3: Unused
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_INIT4_EMR3_MASK (0xFFFFU)
#define DDRCTL_INIT4_EMR3_SHIFT (0U)
#define DDRCTL_INIT4_EMR3_SET(x) (((uint32_t)(x) << DDRCTL_INIT4_EMR3_SHIFT) & DDRCTL_INIT4_EMR3_MASK)
#define DDRCTL_INIT4_EMR3_GET(x) (((uint32_t)(x) & DDRCTL_INIT4_EMR3_MASK) >> DDRCTL_INIT4_EMR3_SHIFT)

/* Bitfield definition for register: INIT5 */
/*
 * DEV_ZQINIT_X32 (R/W)
 *
 * Description: ZQ initial calibration, tZQINIT. Present only in designs configured to support DDR3 or DDR4 or LPDDR2/LPDDR3.
 * Unit: 32 clock cycles.
 * DDR3 typically requires 512 clocks. DDR4 requires 1024 clocks.
 * LPDDR2/LPDDR3 requires 1 us.
 * Value After Reset: 0x10
 * Exists: MEMC_DDR3==1 || MEMC_DDR4 == 1 || MEMC_LPDDR2==1
 */
#define DDRCTL_INIT5_DEV_ZQINIT_X32_MASK (0xFF0000UL)
#define DDRCTL_INIT5_DEV_ZQINIT_X32_SHIFT (16U)
#define DDRCTL_INIT5_DEV_ZQINIT_X32_SET(x) (((uint32_t)(x) << DDRCTL_INIT5_DEV_ZQINIT_X32_SHIFT) & DDRCTL_INIT5_DEV_ZQINIT_X32_MASK)
#define DDRCTL_INIT5_DEV_ZQINIT_X32_GET(x) (((uint32_t)(x) & DDRCTL_INIT5_DEV_ZQINIT_X32_MASK) >> DDRCTL_INIT5_DEV_ZQINIT_X32_SHIFT)

/* Bitfield definition for register: DIMMCTL */
/*
 * DIMM_ADDR_MIRR_EN (R/W)
 *
 * Description: Address Mirroring Enable (for multi-rank UDIMM implementations and multi-rank DDR4 RDIMM implementations).
 * Some UDIMMs and DDR4 RDIMMs implement address mirroring for odd ranks, which means that the following address, bank address and bank group bits are swapped: (A3, A4), (A5, A6), (A7, A8), (BA0, BA1) and also (A11, A13),
 * (BG0, BG1) for the DDR4. Setting this bit ensures that, for mode register accesses during the automatic initialization routine, these bits are swapped within the uMCTL2 to compensate for this UDIMM/RDIMM swapping. In addition to the automatic initialization routine, in case of DDR4 UDIMM/RDIMM, they are swapped during the automatic MRS access to enable/disable of a particular DDR4 feature.
 * Note: This has no effect on the address of any other memory accesses, or of software-driven mode register accesses.
 * This is not supported for mDDR, LPDDR2 or LPDDR3 SDRAMs.
 * Note: In case of x16 DDR4 DIMMs, BG1 output of MRS for the odd ranks is same as BG0 because BG1 is invalid, hence dimm_dis_bg_mirroring register must be set to 1.
 * 1 - For odd ranks, implement address mirroring for MRS commands to during initialization and for any automatic DDR4 MRS commands (to be used if UDIMM/RDIMM implements address mirroring)
 * 0 - Do not implement address mirroring
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_MASK (0x2U)
#define DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_SHIFT (1U)
#define DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_SET(x) (((uint32_t)(x) << DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_SHIFT) & DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_MASK)
#define DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_GET(x) (((uint32_t)(x) & DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_MASK) >> DDRCTL_DIMMCTL_DIMM_ADDR_MIRR_EN_SHIFT)

/*
 * DIMM_STAGGER_CS_EN (R/W)
 *
 * Description: Staggering enable for multi-rank accesses (for multi-rank UDIMM and RDIMM implementations only). This is not supported for DDR4, mDDR, LPDDR2 or LPDDR3 SDRAMs.
 * 1 - Stagger accesses to even and odd ranks
 * 0 - Do not stagger accesses
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_MASK (0x1U)
#define DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_SHIFT (0U)
#define DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_SET(x) (((uint32_t)(x) << DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_SHIFT) & DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_MASK)
#define DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_GET(x) (((uint32_t)(x) & DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_MASK) >> DDRCTL_DIMMCTL_DIMM_STAGGER_CS_EN_SHIFT)

/* Bitfield definition for register: RANKCTL */
/*
 * DIFF_RANK_WR_GAP (R/W)
 *
 * Description: Only present for multi-rank configurations. Indicates the number of clocks of gap in data responses when performing consecutive writes to different ranks.
 * This is used to switch the delays in the PHY to match the rank requirements.
 * The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during writes.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (N/2) and round it up to the next integer value. N is value required by PHY, in terms of PHY clocks.
 * Value After Reset: 0x6
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_MASK (0xF00U)
#define DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_SHIFT (8U)
#define DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_SET(x) (((uint32_t)(x) << DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_SHIFT) & DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_MASK)
#define DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_GET(x) (((uint32_t)(x) & DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_MASK) >> DDRCTL_RANKCTL_DIFF_RANK_WR_GAP_SHIFT)

/*
 * DIFF_RANK_RD_GAP (R/W)
 *
 * Description: Only present for multi-rank configurations. Indicates the number of clocks of gap in data responses when performing consecutive reads to different ranks.
 * This is used to switch the delays in the PHY to match the rank requirements.
 * The value programmed in this register takes care of the ODT switch off timing requirement when switching ranks during reads.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (N/2) and round it up to the next integer value. N is value required by PHY, in terms of PHY clocks.
 * Value After Reset: 0x6
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_MASK (0xF0U)
#define DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_SHIFT (4U)
#define DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_SET(x) (((uint32_t)(x) << DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_SHIFT) & DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_MASK)
#define DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_GET(x) (((uint32_t)(x) & DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_MASK) >> DDRCTL_RANKCTL_DIFF_RANK_RD_GAP_SHIFT)

/*
 * MAX_RANK_RD (R/W)
 *
 * Description: Only present for multi-rank configurations. Background: Reads to the same rank can be performed back-to-back. Reads to different ranks require additional gap
 * dictated by the register RANKCTL.diff_rank_rd_gap. This is
 * to avoid possible data bus contention as well as to give PHY enough time to switch the delay when changing ranks. The uMCTL2 arbitrates for bus access on a cycle-by-cycle basis; therefore after a read is scheduled, there are few clock cycles (determined by the value on diff_rank_rd_gap register) in which only reads from the same rank are eligible to be scheduled. This prevents reads from other ranks from having fair access to the data bus.
 * This parameter represents the maximum number of reads that can be scheduled consecutively to the same rank. After this number is reached, a delay equal to RANKCTL.diff_rank_rd_gap is inserted by the scheduler to allow all ranks a fair opportunity to be scheduled. Higher numbers increase bandwidth utilization, lower numbers increase fairness.
 * This feature can be DISABLED by setting this register to 0. When set to 0, the Controller will stay on the same rank as long as commands are available for it.
 * Minimum programmable value is 0 (feature disabled) and maximum programmable value is 0xF.
 * Feature limitation: max_rank_rd feature works as described only in the mode in which one command at the DDRC input results in one DFI command at the output. An example of this mode is: BL8 hardware configuration (MEMC_BURST_LENGTH=8) and Full bus width mode (MSTR.data_bus_width=2'b00) and BL8 mode of operation (MSTR.burst_rdwr=4'b0100). In modes where single HIF command results in multiple DFI commands (eg: Half Bus Width, BL4 etc.), the same rank commands would be serviced for as long as they are available, which is equivalent to this feature being disabled.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0xf
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_RANKCTL_MAX_RANK_RD_MASK (0xFU)
#define DDRCTL_RANKCTL_MAX_RANK_RD_SHIFT (0U)
#define DDRCTL_RANKCTL_MAX_RANK_RD_SET(x) (((uint32_t)(x) << DDRCTL_RANKCTL_MAX_RANK_RD_SHIFT) & DDRCTL_RANKCTL_MAX_RANK_RD_MASK)
#define DDRCTL_RANKCTL_MAX_RANK_RD_GET(x) (((uint32_t)(x) & DDRCTL_RANKCTL_MAX_RANK_RD_MASK) >> DDRCTL_RANKCTL_MAX_RANK_RD_SHIFT)

/* Bitfield definition for register: DRAMTMG0 */
/*
 * WR2PRE (R/W)
 *
 * Description: Minimum time between write and precharge to same bank.
 * Unit: Clocks
 * Specifications: WL + BL/2 + tWR = approximately 8 cycles + 15 ns = 14 clocks @400MHz and less for lower frequencies where:
 * WL = write latency
 * BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM. BST (burst terminate) is not supported at present.
 * tWR = Write recovery time. This comes directly from the SDRAM specification.
 * Add one extra cycle for LPDDR2/LPDDR3 for this parameter. For configurations with MEMC_FREQ_RATIO=2, 1T mode, divide the above value by 2. No rounding up.
 * For configurations with MEMC_FREQ_RATIO=2, 2T mode, divide the above value by 2 and add 1. No rounding up.
 * Value After Reset: 0xf
 * Exists: Always
 */
#define DDRCTL_DRAMTMG0_WR2PRE_MASK (0x7F000000UL)
#define DDRCTL_DRAMTMG0_WR2PRE_SHIFT (24U)
#define DDRCTL_DRAMTMG0_WR2PRE_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG0_WR2PRE_SHIFT) & DDRCTL_DRAMTMG0_WR2PRE_MASK)
#define DDRCTL_DRAMTMG0_WR2PRE_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG0_WR2PRE_MASK) >> DDRCTL_DRAMTMG0_WR2PRE_SHIFT)

/*
 * T_FAW (R/W)
 *
 * Description: tFAW Valid only when 8 or more banks(or banks x bank groups) are present.
 * In 8-bank design, at most 4 banks must be activated in a rolling window of tFAW cycles.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tFAW/2) and round up to next integer value.
 * In a 4-bank design, set this register to 0x1 independent of the MEMC_FREQ_RATIO configuration.
 * Unit: Clocks
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_DRAMTMG0_T_FAW_MASK (0x3F0000UL)
#define DDRCTL_DRAMTMG0_T_FAW_SHIFT (16U)
#define DDRCTL_DRAMTMG0_T_FAW_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG0_T_FAW_SHIFT) & DDRCTL_DRAMTMG0_T_FAW_MASK)
#define DDRCTL_DRAMTMG0_T_FAW_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG0_T_FAW_MASK) >> DDRCTL_DRAMTMG0_T_FAW_SHIFT)

/*
 * T_RAS_MAX (R/W)
 *
 * Description: tRAS(max): Maximum time between activate and precharge to same bank. This is the maximum time that a page can be kept open
 * Minimum value of this register is 1. Zero is invalid.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tRAS(max)-1)/2. No rounding up.
 * Unit: Multiples of 1024 clocks. Value After Reset: 0x1b Exists: Always
 */
#define DDRCTL_DRAMTMG0_T_RAS_MAX_MASK (0x7F00U)
#define DDRCTL_DRAMTMG0_T_RAS_MAX_SHIFT (8U)
#define DDRCTL_DRAMTMG0_T_RAS_MAX_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG0_T_RAS_MAX_SHIFT) & DDRCTL_DRAMTMG0_T_RAS_MAX_MASK)
#define DDRCTL_DRAMTMG0_T_RAS_MAX_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG0_T_RAS_MAX_MASK) >> DDRCTL_DRAMTMG0_T_RAS_MAX_SHIFT)

/*
 * T_RAS_MIN (R/W)
 *
 * Description: tRAS(min): Minimum time between activate and precharge to the same bank.
 * For configurations with MEMC_FREQ_RATIO=2, 1T mode, program this to tRAS(min)/2. No rounding up.
 * For configurations with MEMC_FREQ_RATIO=2, 2T mode, program this to (tRAS(min)/2 + 1). No rounding up of the division operation.
 * Unit: Clocks
 * Value After Reset: 0xf
 * Exists: Always
 */
#define DDRCTL_DRAMTMG0_T_RAS_MIN_MASK (0x3FU)
#define DDRCTL_DRAMTMG0_T_RAS_MIN_SHIFT (0U)
#define DDRCTL_DRAMTMG0_T_RAS_MIN_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG0_T_RAS_MIN_SHIFT) & DDRCTL_DRAMTMG0_T_RAS_MIN_MASK)
#define DDRCTL_DRAMTMG0_T_RAS_MIN_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG0_T_RAS_MIN_MASK) >> DDRCTL_DRAMTMG0_T_RAS_MIN_SHIFT)

/* Bitfield definition for register: DRAMTMG1 */
/*
 * T_XP (R/W)
 *
 * Description: tXP: Minimum time after power-down exit to any operation. For DDR3, this should be programmed to tXPDLL if slow powerdown exit is selected in MR0[12].
 * If C/A parity for DDR4 is used, set to (tXP+PL) instead. For configurations with MEMC_FREQ_RATIO=2, program this to (tXP/2) and round it up to the next integer value.
 * Units: Clocks
 * Value After Reset: 0x8
 * Exists: Always
 */
#define DDRCTL_DRAMTMG1_T_XP_MASK (0x1F0000UL)
#define DDRCTL_DRAMTMG1_T_XP_SHIFT (16U)
#define DDRCTL_DRAMTMG1_T_XP_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG1_T_XP_SHIFT) & DDRCTL_DRAMTMG1_T_XP_MASK)
#define DDRCTL_DRAMTMG1_T_XP_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG1_T_XP_MASK) >> DDRCTL_DRAMTMG1_T_XP_SHIFT)

/*
 * RD2PRE (R/W)
 *
 * Description: tRTP: Minimum time from read to precharge of same bank.
 * DDR2: tAL + BL/2 + max(tRTP, 2) - 2
 * DDR3: tAL + max (tRTP, 4)
 * DDR4: Max of following two equations:	tAL + max (tRTP, 4) or,	RL + BL/2 - tRP.
 * mDDR: BL/2
 * LPDDR2: Depends on if it's LPDDR2-S2 or LPDDR2-S4: LPDDR2-S2: BL/2 + tRTP - 1.	LPDDR2-S4: BL/2 + max(tRTP,2) - 2.
 * LPDDR3: BL/2 + max(tRTP,4) - 4
 * For configurations with MEMC_FREQ_RATIO=2, 1T mode, divide the above value by 2. No rounding up.
 * For configurations with MEMC_FREQ_RATIO=2, 2T mode, divide the above value by 2 and add 1. No rounding up of division operation.
 * Unit: Clocks.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DRAMTMG1_RD2PRE_MASK (0x1F00U)
#define DDRCTL_DRAMTMG1_RD2PRE_SHIFT (8U)
#define DDRCTL_DRAMTMG1_RD2PRE_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG1_RD2PRE_SHIFT) & DDRCTL_DRAMTMG1_RD2PRE_MASK)
#define DDRCTL_DRAMTMG1_RD2PRE_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG1_RD2PRE_MASK) >> DDRCTL_DRAMTMG1_RD2PRE_SHIFT)

/*
 * T_RC (R/W)
 *
 * Description: tRC: Minimum time between activates to same bank.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tRC/2) and round up to next integer value.
 * Unit: Clocks.
 * Value After Reset: 0x14
 * Exists: Always
 */
#define DDRCTL_DRAMTMG1_T_RC_MASK (0x7FU)
#define DDRCTL_DRAMTMG1_T_RC_SHIFT (0U)
#define DDRCTL_DRAMTMG1_T_RC_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG1_T_RC_SHIFT) & DDRCTL_DRAMTMG1_T_RC_MASK)
#define DDRCTL_DRAMTMG1_T_RC_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG1_T_RC_MASK) >> DDRCTL_DRAMTMG1_T_RC_SHIFT)

/* Bitfield definition for register: DRAMTMG2 */
/*
 * RD2WR (R/W)
 *
 * Description: DDR2/3/mDDR: RL + BL/2 + 2 - WL DDR4: RL + BL/2 + 1 + WR_PREAMBLE - WL
 * LPDDR2/LPDDR3: RL + BL/2 + RU(tDQSCKmax/tCK) + 1 - WL.
 * Minimum time from read command to write command. Include time for bus turnaround and all per-bank, per-rank, and global constraints.
 * Unit: Clocks. Where:
 * WL = write latency
 * BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM
 * RL = read latency = CAS latency
 * WR_PREAMBLE = write preamble. This is unique to DDR4.
 * For configurations with MEMC_FREQ_RATIO=2, divide the value calculated using the above equation by 2, and round it up to next integer.
 * Value After Reset: 0x6
 * Exists: Always
 */
#define DDRCTL_DRAMTMG2_RD2WR_MASK (0x1F00U)
#define DDRCTL_DRAMTMG2_RD2WR_SHIFT (8U)
#define DDRCTL_DRAMTMG2_RD2WR_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG2_RD2WR_SHIFT) & DDRCTL_DRAMTMG2_RD2WR_MASK)
#define DDRCTL_DRAMTMG2_RD2WR_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG2_RD2WR_MASK) >> DDRCTL_DRAMTMG2_RD2WR_SHIFT)

/*
 * WR2RD (R/W)
 *
 * Description: DDR4: WL + BL/2 + tWTR_L Others: WL + BL/2 + tWTR
 * In DDR4, minimum time from write command to read command for same bank group. In others, minimum time from write command to read command. Includes time for bus turnaround, recovery times, and all per-bank, per-rank, and global constraints.
 * Unit: Clocks. Where:
 * WL = write latency
 * BL = burst length. This must match the value programmed in the BL bit of the mode register to the SDRAM
 * tWTR_L = internal write to read command delay for same bank group. This comes directly from the SDRAM specification.
 * tWTR = internal write to read command delay. This comes directly from the SDRAM specification.
 * Add one extra cycle for LPDDR2/LPDDR3 operation.
 * For configurations with MEMC_FREQ_RATIO=2, divide the value calculated using the above equation by 2, and round it up to next integer.
 * Value After Reset: 0xd
 * Exists: Always
 */
#define DDRCTL_DRAMTMG2_WR2RD_MASK (0x3FU)
#define DDRCTL_DRAMTMG2_WR2RD_SHIFT (0U)
#define DDRCTL_DRAMTMG2_WR2RD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG2_WR2RD_SHIFT) & DDRCTL_DRAMTMG2_WR2RD_MASK)
#define DDRCTL_DRAMTMG2_WR2RD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG2_WR2RD_MASK) >> DDRCTL_DRAMTMG2_WR2RD_SHIFT)

/* Bitfield definition for register: DRAMTMG3 */
/*
 * T_MRD (R/W)
 *
 * Description: tMRD: Cycles between load mode commands. If MEMC_DDR3_OR_4 = 0, this parameter is also used to define the cycles between load mode command and following non-load mode command.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tMRD/2) and round it up to the next integer value.
 * If C/A parity for DDR4 is used, set to tMRD_PAR(tMOD+PL) instead
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DRAMTMG3_T_MRD_MASK (0x3F000UL)
#define DDRCTL_DRAMTMG3_T_MRD_SHIFT (12U)
#define DDRCTL_DRAMTMG3_T_MRD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG3_T_MRD_SHIFT) & DDRCTL_DRAMTMG3_T_MRD_MASK)
#define DDRCTL_DRAMTMG3_T_MRD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG3_T_MRD_MASK) >> DDRCTL_DRAMTMG3_T_MRD_SHIFT)

/*
 * T_MOD (R/W)
 *
 * Description: tMOD: Present if MEMC_DDR3_OR_4 = 1. Cycles between load mode command and following non-load mode command. This is required to be programmed even when a design that supports DDR3/4 is running in DDR2 mode.
 * If C/A parity for DDR4 is used, set to tMOD_PAR(tMOD+PL) instead
 * Set to tMOD if MEMC_FREQ_RATIO=1, or tMOD/2 (rounded up to next integer) if MEMC_FREQ_RATIO=2. Note that if using RDIMM, depending on the PHY, it may be necessary to use a value of tMOD + 1 or (tMOD + 1)/2 to compensate for the extra cycle of latency applied to mode register writes by the RDIMM chip
 * Value After Reset: "(MEMC_DDR3_EN==1 || MEMC_DDR4_EN==1 ) ? 0xc : 0x0"
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1
 */
#define DDRCTL_DRAMTMG3_T_MOD_MASK (0x3FFU)
#define DDRCTL_DRAMTMG3_T_MOD_SHIFT (0U)
#define DDRCTL_DRAMTMG3_T_MOD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG3_T_MOD_SHIFT) & DDRCTL_DRAMTMG3_T_MOD_MASK)
#define DDRCTL_DRAMTMG3_T_MOD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG3_T_MOD_MASK) >> DDRCTL_DRAMTMG3_T_MOD_SHIFT)

/* Bitfield definition for register: DRAMTMG4 */
/*
 * T_RCD (R/W)
 *
 * Description: tRCD - tAL: Minimum time from activate to read or write command to same bank.
 * For configurations with MEMC_FREQ_RATIO=2, program this to ((tRCD - tAL)/2) and round it up to the next integer value.
 * Minimum value allowed for this register is 1, which implies minimum (tRCD - tAL) value to be 2 in configurations with MEMC_FREQ_RATIO=2.
 * Unit: Clocks.
 * Value After Reset: 0x5
 * Exists: Always
 */
#define DDRCTL_DRAMTMG4_T_RCD_MASK (0x1F000000UL)
#define DDRCTL_DRAMTMG4_T_RCD_SHIFT (24U)
#define DDRCTL_DRAMTMG4_T_RCD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG4_T_RCD_SHIFT) & DDRCTL_DRAMTMG4_T_RCD_MASK)
#define DDRCTL_DRAMTMG4_T_RCD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG4_T_RCD_MASK) >> DDRCTL_DRAMTMG4_T_RCD_SHIFT)

/*
 * T_CCD (R/W)
 *
 * Description: DDR4: tCCD_L: This is the minimum time between two reads or two writes for same bank group. Others: tCCD: This is the minimum time between two reads
 * or two writes.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tCCD_L/2 or tCCD/2) and round it up to the next integer value.
 * Unit: clocks.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DRAMTMG4_T_CCD_MASK (0x70000UL)
#define DDRCTL_DRAMTMG4_T_CCD_SHIFT (16U)
#define DDRCTL_DRAMTMG4_T_CCD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG4_T_CCD_SHIFT) & DDRCTL_DRAMTMG4_T_CCD_MASK)
#define DDRCTL_DRAMTMG4_T_CCD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG4_T_CCD_MASK) >> DDRCTL_DRAMTMG4_T_CCD_SHIFT)

/*
 * T_RRD (R/W)
 *
 * Description: DDR4: tRRD_L: Minimum time between activates from bank "a" to bank "b" for same bank group. Others: tRRD: Minimum time between activates from bank
 * "a" to bank "b"
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tRRD_L/2 or tRRD/2) and round it up to the next integer value.
 * Unit: Clocks.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DRAMTMG4_T_RRD_MASK (0xF00U)
#define DDRCTL_DRAMTMG4_T_RRD_SHIFT (8U)
#define DDRCTL_DRAMTMG4_T_RRD_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG4_T_RRD_SHIFT) & DDRCTL_DRAMTMG4_T_RRD_MASK)
#define DDRCTL_DRAMTMG4_T_RRD_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG4_T_RRD_MASK) >> DDRCTL_DRAMTMG4_T_RRD_SHIFT)

/*
 * T_RP (R/W)
 *
 * Description: tRP: Minimum time from precharge to activate of same bank.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (tRP/2 + 1). No round up of the fraction.
 * Unit: Clocks.
 * Value After Reset: 0x5
 * Exists: Always
 */
#define DDRCTL_DRAMTMG4_T_RP_MASK (0x1FU)
#define DDRCTL_DRAMTMG4_T_RP_SHIFT (0U)
#define DDRCTL_DRAMTMG4_T_RP_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG4_T_RP_SHIFT) & DDRCTL_DRAMTMG4_T_RP_MASK)
#define DDRCTL_DRAMTMG4_T_RP_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG4_T_RP_MASK) >> DDRCTL_DRAMTMG4_T_RP_SHIFT)

/* Bitfield definition for register: DRAMTMG5 */
/*
 * T_CKSRX (R/W)
 *
 * Description: This is the time before Self Refresh Exit that CK is maintained as a valid clock before issuing SRX. Specifies the clock stable time before SRX.
 * Recommended settings:
 * mDDR: 1
 * LPDDR2: 2
 * LPDDR3: 2
 * DDR2: 1
 * DDR3: tCKSRX
 * DDR4: tCKSRX
 * For configurations with MEMC_FREQ_RATIO=2, program this to recommended value divided by two and round it up to next integer.
 * Value After Reset: 0x5
 * Exists: Always
 */
#define DDRCTL_DRAMTMG5_T_CKSRX_MASK (0xF000000UL)
#define DDRCTL_DRAMTMG5_T_CKSRX_SHIFT (24U)
#define DDRCTL_DRAMTMG5_T_CKSRX_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG5_T_CKSRX_SHIFT) & DDRCTL_DRAMTMG5_T_CKSRX_MASK)
#define DDRCTL_DRAMTMG5_T_CKSRX_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG5_T_CKSRX_MASK) >> DDRCTL_DRAMTMG5_T_CKSRX_SHIFT)

/*
 * T_CKSRE (R/W)
 *
 * Description: This is the time after Self Refresh Down Entry that CK is maintained as a valid clock. Specifies the clock disable delay after SRE.
 * Recommended settings:
 * mDDR: 0
 * LPDDR2: 2
 * LPDDR3: 2
 * DDR2: 1
 * DDR3: max (10 ns, 5 tCK)
 * DDR4: max (10 ns, 5 tCK)
 * For configurations with MEMC_FREQ_RATIO=2, program this to recommended value divided by two and round it up to next integer.
 * Value After Reset: 0x5
 * Exists: Always
 */
#define DDRCTL_DRAMTMG5_T_CKSRE_MASK (0xF0000UL)
#define DDRCTL_DRAMTMG5_T_CKSRE_SHIFT (16U)
#define DDRCTL_DRAMTMG5_T_CKSRE_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG5_T_CKSRE_SHIFT) & DDRCTL_DRAMTMG5_T_CKSRE_MASK)
#define DDRCTL_DRAMTMG5_T_CKSRE_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG5_T_CKSRE_MASK) >> DDRCTL_DRAMTMG5_T_CKSRE_SHIFT)

/*
 * T_CKESR (R/W)
 *
 * Description: Minimum CKE low width for Self refresh entry to exit timing im memory clock cycles.
 * Recommended settings:
 * mDDR: tRFC
 * LPDDR2: tCKESR
 * LPDDR3: tCKESR
 * DDR2: tCKE
 * DDR3: tCKE + 1
 * DDR4: tCKE + 1
 * For configurations with MEMC_FREQ_RATIO=2, program this to recommended value divided by two and round it up to next integer.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DRAMTMG5_T_CKESR_MASK (0x3F00U)
#define DDRCTL_DRAMTMG5_T_CKESR_SHIFT (8U)
#define DDRCTL_DRAMTMG5_T_CKESR_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG5_T_CKESR_SHIFT) & DDRCTL_DRAMTMG5_T_CKESR_MASK)
#define DDRCTL_DRAMTMG5_T_CKESR_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG5_T_CKESR_MASK) >> DDRCTL_DRAMTMG5_T_CKESR_SHIFT)

/*
 * T_CKE (R/W)
 *
 * Description: Minimum number of cycles of CKE HIGH/LOW during power-down and self refresh.
 * LPDDR2/LPDDR3 mode: Set this to the larger of tCKE or tCKESR
 * Non-LPDDR2/non-LPDDR3 designs: Set this to tCKE value.
 * For configurations with MEMC_FREQ_RATIO=2, program this to (value described above)/2 and round it up to the next integer value.
 * Unit: Clocks.
 * Value After Reset: 0x3
 * Exists: Always
 */
#define DDRCTL_DRAMTMG5_T_CKE_MASK (0x1FU)
#define DDRCTL_DRAMTMG5_T_CKE_SHIFT (0U)
#define DDRCTL_DRAMTMG5_T_CKE_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG5_T_CKE_SHIFT) & DDRCTL_DRAMTMG5_T_CKE_MASK)
#define DDRCTL_DRAMTMG5_T_CKE_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG5_T_CKE_MASK) >> DDRCTL_DRAMTMG5_T_CKE_SHIFT)

/* Bitfield definition for register: DRAMTMG8 */
/*
 * T_XS_DLL_X32 (R/W)
 *
 * Description: tXSDLL: Exit Self Refresh to commands requiring a locked DLL.
 * For configurations with MEMC_FREQ_RATIO=2, program this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: In LPDDR2/LPDDR3/Mobile DDR mode, t_xs_x32 and t_xs_dll_x32 must be set the same values derived from tXSR.
 * Value After Reset: 0x44
 * Exists: Always
 */
#define DDRCTL_DRAMTMG8_T_XS_DLL_X32_MASK (0x7F00U)
#define DDRCTL_DRAMTMG8_T_XS_DLL_X32_SHIFT (8U)
#define DDRCTL_DRAMTMG8_T_XS_DLL_X32_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG8_T_XS_DLL_X32_SHIFT) & DDRCTL_DRAMTMG8_T_XS_DLL_X32_MASK)
#define DDRCTL_DRAMTMG8_T_XS_DLL_X32_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG8_T_XS_DLL_X32_MASK) >> DDRCTL_DRAMTMG8_T_XS_DLL_X32_SHIFT)

/*
 * T_XS_X32 (R/W)
 *
 * Description: tXS: Exit Self Refresh to commands not requiring a locked DLL.
 * For configurations with MEMC_FREQ_RATIO=2, program this to the above value divided by 2 and round up to next integer value.
 * Unit: Multiples of 32 clocks.
 * Note: In LPDDR2/LPDDR3/Mobile DDR mode, t_xs_x32 and t_xs_dll_x32 must be set the same values derived from tXSR.
 * Value After Reset: 0x5
 * Exists: Always
 */
#define DDRCTL_DRAMTMG8_T_XS_X32_MASK (0x7FU)
#define DDRCTL_DRAMTMG8_T_XS_X32_SHIFT (0U)
#define DDRCTL_DRAMTMG8_T_XS_X32_SET(x) (((uint32_t)(x) << DDRCTL_DRAMTMG8_T_XS_X32_SHIFT) & DDRCTL_DRAMTMG8_T_XS_X32_MASK)
#define DDRCTL_DRAMTMG8_T_XS_X32_GET(x) (((uint32_t)(x) & DDRCTL_DRAMTMG8_T_XS_X32_MASK) >> DDRCTL_DRAMTMG8_T_XS_X32_SHIFT)

/* Bitfield definition for register: ZQCTL0 */
/*
 * DIS_AUTO_ZQ (R/W)
 *
 * Description:
 * 1 - Disable uMCTL2 generation of ZQCS command. Register reg_ddrc_zq_calib_short can be used instead to control ZQ calibration commands.
 * 0 - Internally generate ZQCS commands based on ZQCTL1.t_zq_short_interval_x1024.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL0_DIS_AUTO_ZQ_MASK (0x80000000UL)
#define DDRCTL_ZQCTL0_DIS_AUTO_ZQ_SHIFT (31U)
#define DDRCTL_ZQCTL0_DIS_AUTO_ZQ_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL0_DIS_AUTO_ZQ_SHIFT) & DDRCTL_ZQCTL0_DIS_AUTO_ZQ_MASK)
#define DDRCTL_ZQCTL0_DIS_AUTO_ZQ_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL0_DIS_AUTO_ZQ_MASK) >> DDRCTL_ZQCTL0_DIS_AUTO_ZQ_SHIFT)

/*
 * DIS_SRX_ZQCL (R/W)
 *
 * Description:
 * 1 - Disable issuing of ZQCL command at Self-Refresh exit. Only applicable when run in DDR3 or DDR4 or LPDDR2 or LPDDR3 mode.
 * 0 - Enable issuing of ZQCL command at Self-Refresh exit. Only applicable when run in DDR3 or DDR4 or LPDDR2 or LPDDR3 mode.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL0_DIS_SRX_ZQCL_MASK (0x40000000UL)
#define DDRCTL_ZQCTL0_DIS_SRX_ZQCL_SHIFT (30U)
#define DDRCTL_ZQCTL0_DIS_SRX_ZQCL_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL0_DIS_SRX_ZQCL_SHIFT) & DDRCTL_ZQCTL0_DIS_SRX_ZQCL_MASK)
#define DDRCTL_ZQCTL0_DIS_SRX_ZQCL_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL0_DIS_SRX_ZQCL_MASK) >> DDRCTL_ZQCTL0_DIS_SRX_ZQCL_SHIFT)

/*
 * ZQ_RESISTOR_SHARED (R/W)
 *
 * Description:
 * 1 - Denotes that ZQ resistor is shared between ranks. Means ZQinit/ZQCL/ZQCS commands are sent to one rank at a time with tZQinit/tZQCL/tZQCS timing met between commands so that commands to different ranks do not overlap.
 * 0 - ZQ resistor is not shared.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_MASK (0x20000000UL)
#define DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_SHIFT (29U)
#define DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_SHIFT) & DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_MASK)
#define DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_MASK) >> DDRCTL_ZQCTL0_ZQ_RESISTOR_SHARED_SHIFT)

/*
 * T_ZQ_LONG_NOP (R/W)
 *
 * Description: tZQoper for DDR3/DDR4, tZQCL for LPDDR2/LPDDR3: Number of cycles of NOP required after a ZQCL (ZQ calibration long) command is issued to SDRAM.
 * For configurations with MEMC_FREQ_RATIO=2: DDR3/DDR4: program this to tZQoper/2 and round it up to the next integer value.
 * LPDDR2/LPDDR3: program this to tZQCL/2 and round it up to the next integer value.
 * Unit: Clock cycles.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x200
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_MASK (0x3FF0000UL)
#define DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_SHIFT (16U)
#define DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_SHIFT) & DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_MASK)
#define DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_MASK) >> DDRCTL_ZQCTL0_T_ZQ_LONG_NOP_SHIFT)

/*
 * T_ZQ_SHORT_NOP (R/W)
 *
 * Description: tZQCS: Number of cycles of NOP required after a ZQCS (ZQ calibration short) command is issued to SDRAM.
 * For configurations with MEMC_FREQ_RATIO=2, program this to tZQCS/2 and round it up to the next integer value. Unit: Clock cycles.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x40
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_MASK (0x3FFU)
#define DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_SHIFT (0U)
#define DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_SHIFT) & DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_MASK)
#define DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_MASK) >> DDRCTL_ZQCTL0_T_ZQ_SHORT_NOP_SHIFT)

/* Bitfield definition for register: ZQCTL1 */
/*
 * T_ZQ_SHORT_INTERVAL_X1024 (R/W)
 *
 * Description: Average interval to wait between automatically issuing ZQCS (ZQ calibration short) commands to DDR3/DDR4/LPDDR2/LPDDR3 devices.
 * Meaningless, if ZQCTL0.dis_auto_zq=1. Unit: 1024 clock cycles.
 * This is only present for designs supporting DDR3/DDR4 or LPDDR2/LPDDR3 devices.
 * Value After Reset: 0x100
 * Exists: MEMC_DDR3==1 || MEMC_DDR4==1 || MEMC_LPDDR2==1
 */
#define DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_MASK (0xFFFFFUL)
#define DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_SHIFT (0U)
#define DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_SET(x) (((uint32_t)(x) << DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_SHIFT) & DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_MASK)
#define DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_GET(x) (((uint32_t)(x) & DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_MASK) >> DDRCTL_ZQCTL1_T_ZQ_SHORT_INTERVAL_X1024_SHIFT)

/* Bitfield definition for register: ZQSTAT */
/*
 * ZQ_RESET_BUSY (R)
 *
 * Description: SoC core may initiate a ZQ Reset operation only if this signal is low. This signal goes high in the clock after the uMCTL2 accepts the ZQ Reset request. It goes low when the ZQ Reset command is issued to the SDRAM and the associated NOP period is over. It is recommended not to perform ZQ Reset commands when this signal is high.
 * 0 - Indicates that the SoC core can initiate a ZQ Reset operation
 * 1 - Indicates that ZQ Reset operation is in progress
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ZQSTAT_ZQ_RESET_BUSY_MASK (0x1U)
#define DDRCTL_ZQSTAT_ZQ_RESET_BUSY_SHIFT (0U)
#define DDRCTL_ZQSTAT_ZQ_RESET_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_ZQSTAT_ZQ_RESET_BUSY_MASK) >> DDRCTL_ZQSTAT_ZQ_RESET_BUSY_SHIFT)

/* Bitfield definition for register: DFITMG0 */
/*
 * DFI_T_CTRL_DELAY (R/W)
 *
 * Description: Specifies the number of DFI clock cycles after an assertion or de-assertion of the DFI control signals that the control signals at the PHY-DRAM interface reflect the assertion or de-assertion. If the DFI clock and the memory clock are not phase-aligned, this timing parameter should be rounded up to the next integer value. Note that if using RDIMM, depending on the PHY, it may be necessary to increment this parameter by 1. This is to compensate for the extra cycle of latency through the RDIMM
 * Value After Reset: 0x7
 * Exists: Always
 */
#define DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_MASK (0x1F000000UL)
#define DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_SHIFT (24U)
#define DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_SHIFT) & DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_MASK)
#define DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_MASK) >> DDRCTL_DFITMG0_DFI_T_CTRL_DELAY_SHIFT)

/*
 * DFI_RDDATA_USE_SDR (R/W)
 *
 * Description: Defines whether dfi_rddata_en/dfi_rddata/dfi_rddata_valid is generated using HDR or SDR values Selects whether value in DFITMG0.dfi_t_rddata_en is in terms of SDR or HDR clock cycles:
 * 0 in terms of HDR clock cycles
 * 1 in terms of SDR clock cycles
 * Refer to PHY specification for correct value.
 * Value After Reset: 0x0
 * Exists: MEMC_FREQ_RATIO==2
 */
#define DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_MASK (0x800000UL)
#define DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_SHIFT (23U)
#define DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_SHIFT) & DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_MASK)
#define DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_MASK) >> DDRCTL_DFITMG0_DFI_RDDATA_USE_SDR_SHIFT)

/*
 * DFI_T_RDDATA_EN (R/W)
 *
 * Description: Time from the assertion of a read command on the DFI interface to the assertion of the dfi_rddata_en signal. Refer to PHY specification for correct value.
 * This corresponds to the DFI parameter trddata_en. Note that, depending on the PHY, if using RDIMM, it may be necessary to use the value (CL + 1) in the calculation of trddata_en. This is to compensate for the extra cycle of latency through the RDIMM.
 * Unit: Clocks
 * Value After Reset: 0x2
 * Exists: Always
 */
#define DDRCTL_DFITMG0_DFI_T_RDDATA_EN_MASK (0x3F0000UL)
#define DDRCTL_DFITMG0_DFI_T_RDDATA_EN_SHIFT (16U)
#define DDRCTL_DFITMG0_DFI_T_RDDATA_EN_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_T_RDDATA_EN_SHIFT) & DDRCTL_DFITMG0_DFI_T_RDDATA_EN_MASK)
#define DDRCTL_DFITMG0_DFI_T_RDDATA_EN_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_T_RDDATA_EN_MASK) >> DDRCTL_DFITMG0_DFI_T_RDDATA_EN_SHIFT)

/*
 * DFI_WRDATA_USE_SDR (R/W)
 *
 * Description: Defines whether dfi_wrdata_en/dfi_wrdata/dfi_wrdata_mask is generated using HDR or SDR values Selects whether value in DFITMG0.dfi_tphy_wrlat is in terms of SDR or HDR clock cycles Selects whether value in DFITMG0.dfi_tphy_wrdata is in terms of SDR or HDR clock cycles
 * 0 in terms of HDR clock cycles
 * 1 in terms of SDR clock cycles
 * Refer to PHY specification for correct value.
 * Value After Reset: 0x0
 * Exists: MEMC_FREQ_RATIO==2
 */
#define DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_MASK (0x8000U)
#define DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_SHIFT (15U)
#define DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_SHIFT) & DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_MASK)
#define DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_MASK) >> DDRCTL_DFITMG0_DFI_WRDATA_USE_SDR_SHIFT)

/*
 * DFI_TPHY_WRDATA (R/W)
 *
 * Description: Specifies the number of clock cycles between when dfi_wrdata_en is asserted to when the associated write data is driven on the dfi_wrdata signal. This corresponds to the DFI timing parameter tphy_wrdata. Refer to PHY specification for correct value. Note, max supported value is 8.
 * Unit: Clocks
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFITMG0_DFI_TPHY_WRDATA_MASK (0x3F00U)
#define DDRCTL_DFITMG0_DFI_TPHY_WRDATA_SHIFT (8U)
#define DDRCTL_DFITMG0_DFI_TPHY_WRDATA_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_TPHY_WRDATA_SHIFT) & DDRCTL_DFITMG0_DFI_TPHY_WRDATA_MASK)
#define DDRCTL_DFITMG0_DFI_TPHY_WRDATA_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_TPHY_WRDATA_MASK) >> DDRCTL_DFITMG0_DFI_TPHY_WRDATA_SHIFT)

/*
 * DFI_TPHY_WRLAT (R/W)
 *
 * Description: Write latency
 * Number of clocks from the write command to write data enable (dfi_wrdata_en). This corresponds to the DFI timing parameter tphy_wrlat. The minimum supported value is as follows:
 * 0 for configurations with MEMC_WL0 = 1
 * 1 for configurations with MEMC_WL0 = 0
 * Refer to PHY specification for correct value.Note that, depending on the PHY, if using RDIMM, it may be necessary to use the value (CL + 1) in the calculation of tphy_wrlat. This is to compensate for the extra cycle of latency through the RDIMM.
 * Value After Reset: 0x2
 * Exists: Always
 */
#define DDRCTL_DFITMG0_DFI_TPHY_WRLAT_MASK (0x3FU)
#define DDRCTL_DFITMG0_DFI_TPHY_WRLAT_SHIFT (0U)
#define DDRCTL_DFITMG0_DFI_TPHY_WRLAT_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG0_DFI_TPHY_WRLAT_SHIFT) & DDRCTL_DFITMG0_DFI_TPHY_WRLAT_MASK)
#define DDRCTL_DFITMG0_DFI_TPHY_WRLAT_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG0_DFI_TPHY_WRLAT_MASK) >> DDRCTL_DFITMG0_DFI_TPHY_WRLAT_SHIFT)

/* Bitfield definition for register: DFITMG1 */
/*
 * DFI_T_WRDATA_DELAY (R/W)
 *
 * Description: Specifies the number of DFI clocks between when the dfi_wrdata_en signal is asserted and when the corresponding write data transfer is completed on the DRAM bus. This corresponds to the DFI timing parameter twrdata_delay. Refer to PHY specification for correct value. For DFI 3.0 PHY, set to twrdata_delay, a new timing parameter introduced in DFI 3.0. For DFI 2.1 PHY, set to tphy_wrdata + (delay of DFI write data to the DRAM). Value to be programmed is in terms of DFI clocks, not PHY clocks. In FREQ_RATIO=2, divide PHY's value by 2 and round up to next integer. If using DFITMG0.dfi_wrdata_use_sdr=1, add 1 to the value.
 * Unit: Clocks
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_MASK (0x1F0000UL)
#define DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_SHIFT (16U)
#define DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_SHIFT) & DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_MASK)
#define DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_MASK) >> DDRCTL_DFITMG1_DFI_T_WRDATA_DELAY_SHIFT)

/*
 * DFI_T_DRAM_CLK_DISABLE (R/W)
 *
 * Description: Specifies the number of DFI clock cycles from the assertion of the dfi_dram_clk_disable signal on the DFI until the clock to the DRAM memory devices, at the PHY- DRAM boundary, maintains a low value. If the DFI clock and the memory clock are not phase aligned, this timing parameter should be rounded up to the next integer value.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_MASK (0xF00U)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_SHIFT (8U)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_SHIFT) & DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_MASK)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_MASK) >> DDRCTL_DFITMG1_DFI_T_DRAM_CLK_DISABLE_SHIFT)

/*
 * DFI_T_DRAM_CLK_ENABLE (R/W)
 *
 * Description: Specifies the number of DFI clock cycles from the de-assertion of the dfi_dram_clk_disable signal on the DFI until the first valid rising edge of the clock to the DRAM memory devices, at the PHY-DRAM boundary. If the DFI clock and the memory clock are not phase aligned, this timing parameter should be rounded up to the next integer value.
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_MASK (0xFU)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_SHIFT (0U)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_SHIFT) & DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_MASK)
#define DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_MASK) >> DDRCTL_DFITMG1_DFI_T_DRAM_CLK_ENABLE_SHIFT)

/* Bitfield definition for register: DFILPCFG0 */
/*
 * DFI_TLP_RESP (R/W)
 *
 * Description: Setting for DFI's tlp_resp time.
 * Same value is used for both Power Down, Self Refresh, Deep Power Down and Maximum Power Saving modes. DFI 2.1 specification onwards, recommends using a fixed
 * value of 7 always.
 * Value After Reset: 0x7
 * Exists: Always
 */
#define DDRCTL_DFILPCFG0_DFI_TLP_RESP_MASK (0xF000000UL)
#define DDRCTL_DFILPCFG0_DFI_TLP_RESP_SHIFT (24U)
#define DDRCTL_DFILPCFG0_DFI_TLP_RESP_SET(x) (((uint32_t)(x) << DDRCTL_DFILPCFG0_DFI_TLP_RESP_SHIFT) & DDRCTL_DFILPCFG0_DFI_TLP_RESP_MASK)
#define DDRCTL_DFILPCFG0_DFI_TLP_RESP_GET(x) (((uint32_t)(x) & DDRCTL_DFILPCFG0_DFI_TLP_RESP_MASK) >> DDRCTL_DFILPCFG0_DFI_TLP_RESP_SHIFT)

/*
 * DFI_LP_WAKEUP_SR (R/W)
 *
 * Description: Value to drive on dfi_lp_wakeup signal when Self Refresh mode is entered.
 * Determines the DFI's tlp_wakeup time:
 * 0x0 - 16 cycles
 * 0x1 - 32 cycles
 * 0x2 - 64 cycles
 * 0x3 - 128 cycles
 * 0x4 - 256 cycles
 * 0x5 - 512 cycles
 * 0x6 - 1024 cycles
 * 0x7 - 2048 cycles
 * 0x8 - 4096 cycles
 * 0x9 - 8192 cycles
 * 0xA - 16384 cycles
 * 0xB - 32768 cycles
 * 0xC - 65536 cycles
 * 0xD - 131072 cycles
 * 0xE - 262144 cycles
 * 0xF - Unlimited Value After Reset: 0x0 Exists: Always
 */
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_MASK (0xF000U)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_SHIFT (12U)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_SET(x) (((uint32_t)(x) << DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_SHIFT) & DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_MASK)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_GET(x) (((uint32_t)(x) & DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_MASK) >> DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_SR_SHIFT)

/*
 * DFI_LP_EN_SR (R/W)
 *
 * Description: Enables DFI Low Power interface handshaking during Self Refresh Entry/Exit.
 * 0 - Disabled
 * 1 - Enabled
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFILPCFG0_DFI_LP_EN_SR_MASK (0x100U)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_SR_SHIFT (8U)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_SR_SET(x) (((uint32_t)(x) << DDRCTL_DFILPCFG0_DFI_LP_EN_SR_SHIFT) & DDRCTL_DFILPCFG0_DFI_LP_EN_SR_MASK)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_SR_GET(x) (((uint32_t)(x) & DDRCTL_DFILPCFG0_DFI_LP_EN_SR_MASK) >> DDRCTL_DFILPCFG0_DFI_LP_EN_SR_SHIFT)

/*
 * DFI_LP_WAKEUP_PD (R/W)
 *
 * Description: Value to drive on dfi_lp_wakeup signal when Power Down mode is entered.
 * Determines the DFI's tlp_wakeup time:
 * 0x0 - 16 cycles
 * 0x1 - 32 cycles
 * 0x2 - 64 cycles
 * 0x3 - 128 cycles
 * 0x4 - 256 cycles
 * 0x5 - 512 cycles
 * 0x6 - 1024 cycles
 * 0x7 - 2048 cycles
 * 0x8 - 4096 cycles
 * 0x9 - 8192 cycles
 * 0xA - 16384 cycles
 * 0xB - 32768 cycles
 * 0xC - 65536 cycles
 * 0xD - 131072 cycles
 * 0xE - 262144 cycles
 * 0xF - Unlimited Value After Reset: 0x0 Exists: Always
 */
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_MASK (0xF0U)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_SHIFT (4U)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_SET(x) (((uint32_t)(x) << DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_SHIFT) & DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_MASK)
#define DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_GET(x) (((uint32_t)(x) & DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_MASK) >> DDRCTL_DFILPCFG0_DFI_LP_WAKEUP_PD_SHIFT)

/*
 * DFI_LP_EN_PD (R/W)
 *
 * Description: Enables DFI Low Power interface handshaking during Power Down Entry/Exit.
 * 0 - Disabled
 * 1 - Enabled
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFILPCFG0_DFI_LP_EN_PD_MASK (0x1U)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_PD_SHIFT (0U)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_PD_SET(x) (((uint32_t)(x) << DDRCTL_DFILPCFG0_DFI_LP_EN_PD_SHIFT) & DDRCTL_DFILPCFG0_DFI_LP_EN_PD_MASK)
#define DDRCTL_DFILPCFG0_DFI_LP_EN_PD_GET(x) (((uint32_t)(x) & DDRCTL_DFILPCFG0_DFI_LP_EN_PD_MASK) >> DDRCTL_DFILPCFG0_DFI_LP_EN_PD_SHIFT)

/* Bitfield definition for register: DFIUPD0 */
/*
 * DIS_AUTO_CTRLUPD (R/W)
 *
 * Description: When '1', disable the automatic dfi_ctrlupd_req generation by the uMCTL2. The core must issue the dfi_ctrlupd_req signal using register reg_ddrc_ctrlupd. This register field is changeable on the fly.
 * When '0', uMCTL2 issues dfi_ctrlupd_req periodically.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_MASK (0x80000000UL)
#define DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_SHIFT (31U)
#define DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_SHIFT) & DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_MASK)
#define DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_MASK) >> DDRCTL_DFIUPD0_DIS_AUTO_CTRLUPD_SHIFT)

/*
 * DFI_T_CTRLUP_MAX (R/W)
 *
 * Description: Specifies the maximum number of clock cycles that the dfi_ctrlupd_req signal can assert. Lowest value to assign to this variable is 0x40.
 * Unit: Clocks
 * Value After Reset: 0x40
 * Exists: Always
 */
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_MASK (0x3FF0000UL)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_SHIFT (16U)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_SHIFT) & DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_MASK)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_MASK) >> DDRCTL_DFIUPD0_DFI_T_CTRLUP_MAX_SHIFT)

/*
 * DFI_T_CTRLUP_MIN (R/W)
 *
 * Description: Specifies the minimum number of clock cycles that the dfi_ctrlupd_req signal must be asserted. The uMCTL2 expects the PHY to respond within this time. If the PHY does not respond, the uMCTL2 will de-assert dfi_ctrlupd_req after dfi_t_ctrlup_min + 2 cycles. Lowest value to assign to this variable is 0x3.
 * Unit: Clocks
 * Value After Reset: 0x3
 * Exists: Always
 */
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_MASK (0x3FFU)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_SHIFT (0U)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_SHIFT) & DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_MASK)
#define DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_MASK) >> DDRCTL_DFIUPD0_DFI_T_CTRLUP_MIN_SHIFT)

/* Bitfield definition for register: DFIUPD1 */
/*
 * DFI_T_CTRLUPD_INTERVAL_MIN_X1024 (R/W)
 *
 * Description: This is the minimum amount of time between uMCTL2 initiated DFI update requests (which is executed whenever the uMCTL2 is idle). Set this number higher to reduce the frequency of update requests, which can have a small impact on the latency of the first read request when the uMCTL2 is idle.
 * Unit: 1024 clocks Value After Reset: 0x0
 *  Exists: Always
 */
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_MASK (0xFF0000UL)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_SHIFT (16U)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_SHIFT) & DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_MASK)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_MASK) >> DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MIN_X1024_SHIFT)

/*
 * DFI_T_CTRLUPD_INTERVAL_MAX_X1024 (R/W)
 *
 * Description: This is the maximum amount of time between uMCTL2 initiated DFI update requests. This timer resets with each update request; when the timer expires dfi_ctrlupd_req is sent and traffic is blocked until the dfi_ctrlupd_ackx is received. PHY can use this idle time to recalibrate the delay lines to the DLLs. The DFI controller update is also used to reset PHY FIFO pointers in case of data capture errors.
 * Updates are required to maintain calibration over PVT, but frequent updates may impact performance.
 * Note: Value programmed for DFIUPD1.dfi_t_ctrlupd_interval_max_x1024 must be greater than DFIUPD1.dfi_t_ctrlupd_interval_min_x1024.
 * Unit: 1024 clocks Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_MASK (0xFFU)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_SHIFT (0U)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_SHIFT) & DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_MASK)
#define DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_MASK) >> DDRCTL_DFIUPD1_DFI_T_CTRLUPD_INTERVAL_MAX_X1024_SHIFT)

/* Bitfield definition for register: DFIUPD2 */
/*
 * DFI_PHYUPD_EN (R/W)
 *
 * Description: Enables the support for acknowledging PHY- initiated updates:
 * 0 - Disabled
 * 1 - Enabled
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_DFIUPD2_DFI_PHYUPD_EN_MASK (0x80000000UL)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_EN_SHIFT (31U)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_EN_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD2_DFI_PHYUPD_EN_SHIFT) & DDRCTL_DFIUPD2_DFI_PHYUPD_EN_MASK)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_EN_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD2_DFI_PHYUPD_EN_MASK) >> DDRCTL_DFIUPD2_DFI_PHYUPD_EN_SHIFT)

/*
 * DFI_PHYUPD_TYPE1 (R/W)
 *
 * Description: Specifies the maximum number of DFI clock cycles that the dfi_phyupd_req signal may remain asserted after the assertion of the dfi_phyupd_ack signal for dfi_phyupd_type = 2'b01. The dfi_phyupd_req signal may de-assert at any cycle after the assertion of the dfi_phyupd_ack signal.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_MASK (0xFFF0000UL)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_SHIFT (16U)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_SHIFT) & DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_MASK)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_MASK) >> DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE1_SHIFT)

/*
 * DFI_PHYUPD_TYPE0 (R/W)
 *
 * Description: Specifies the maximum number of DFI clock cycles that the dfi_phyupd_req signal may remain asserted after the assertion of the dfi_phyupd_ack signal for dfi_phyupd_type = 2'b00. The dfi_phyupd_req signal may de-assert at any cycle after the assertion of the dfi_phyupd_ack signal.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_MASK (0xFFFU)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_SHIFT (0U)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_SHIFT) & DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_MASK)
#define DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_MASK) >> DDRCTL_DFIUPD2_DFI_PHYUPD_TYPE0_SHIFT)

/* Bitfield definition for register: DFIUPD3 */
/*
 * DFI_PHYUPD_TYPE3 (R/W)
 *
 * Description: Specifies the maximum number of DFI clock cycles that the dfi_phyupd_req signal may remain asserted after the assertion of the dfi_phyupd_ack signal for dfi_phyupd_type = 2'b11. The dfi_phyupd_req signal may de-assert at any cycle after the assertion of the dfi_phyupd_ack signal.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_MASK (0xFFF0000UL)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_SHIFT (16U)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_SHIFT) & DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_MASK)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_MASK) >> DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE3_SHIFT)

/*
 * DFI_PHYUPD_TYPE2 (R/W)
 *
 * Description: Specifies the maximum number of DFI clock cycles that the dfi_phyupd_req signal may remain asserted after the assertion of the dfi_phyupd_ack signal for dfi_phyupd_type = 2'b10. The dfi_phyupd_req signal may de-assert at any cycle after the assertion of the dfi_phyupd_ack signal.
 * Value After Reset: 0x10
 * Exists: Always
 */
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_MASK (0xFFFU)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_SHIFT (0U)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_SET(x) (((uint32_t)(x) << DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_SHIFT) & DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_MASK)
#define DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_GET(x) (((uint32_t)(x) & DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_MASK) >> DDRCTL_DFIUPD3_DFI_PHYUPD_TYPE2_SHIFT)

/* Bitfield definition for register: DFIMISC */
/*
 * DFI_INIT_COMPLETE_EN (R/W)
 *
 * Description: PHY initialization complete enable signal. When asserted the dfi_init_complete signal can be used to trigger SDRAM initialisation
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_MASK (0x1U)
#define DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_SHIFT (0U)
#define DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_SET(x) (((uint32_t)(x) << DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_SHIFT) & DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_MASK)
#define DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_GET(x) (((uint32_t)(x) & DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_MASK) >> DDRCTL_DFIMISC_DFI_INIT_COMPLETE_EN_SHIFT)

/* Bitfield definition for register: DFITMG2 */
/*
 * DFI_TPHY_RDCSLAT (R/W)
 *
 * Description: Number of clocks between when a read command is sent on the DFI control interface and when the associated dfi_rddata_cs_n signal is asserted. This corresponds to the DFI timing parameter tphy_rdcslat. Refer to PHY specification for correct value.
 * Value After Reset: 0x2
 * Exists: Always
 */
#define DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_MASK (0x3F00U)
#define DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_SHIFT (8U)
#define DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_SHIFT) & DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_MASK)
#define DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_MASK) >> DDRCTL_DFITMG2_DFI_TPHY_RDCSLAT_SHIFT)

/*
 * DFI_TPHY_WRCSLAT (R/W)
 *
 * Description: Number of clocks between when a write command is sent on the DFI control interface and when the associated dfi_wrdata_cs_n signal is asserted. This corresponds to the DFI timing parameter tphy_wrcslat. The minimum supported value is as follows:
 * 0 for configurations with MEMC_WL0 = 1
 * 1 for configurations with MEMC_WL0 = 0 Refer to PHY specification for correct value. Value After Reset: 0x2
 * Exists: Always
 */
#define DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_MASK (0x3FU)
#define DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_SHIFT (0U)
#define DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_SET(x) (((uint32_t)(x) << DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_SHIFT) & DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_MASK)
#define DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_GET(x) (((uint32_t)(x) & DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_MASK) >> DDRCTL_DFITMG2_DFI_TPHY_WRCSLAT_SHIFT)

/* Bitfield definition for register: ADDRMAP0 */
/*
 * ADDRMAP_CS_BIT0 (R/W)
 *
 * Description: Selects the HIF address bit used as rank address bit 0.
 * Valid Range: 0 to 27, and 31
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 31, rank address bit 0 is set to 0.
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_MASK (0x1FU)
#define DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_SHIFT (0U)
#define DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_SHIFT) & DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_MASK)
#define DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_MASK) >> DDRCTL_ADDRMAP0_ADDRMAP_CS_BIT0_SHIFT)

/* Bitfield definition for register: ADDRMAP1 */
/*
 * ADDRMAP_BANK_B2 (R/W)
 *
 * Description: Selects the HIF address bit used as bank address bit 2.
 * Valid Range: 0 to 29 and 31
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 31, bank address bit 2 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_MASK (0x1F0000UL)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_SHIFT (16U)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_SHIFT) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_MASK)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_MASK) >> DDRCTL_ADDRMAP1_ADDRMAP_BANK_B2_SHIFT)

/*
 * ADDRMAP_BANK_B1 (R/W)
 *
 * Description: Selects the HIF address bits used as bank address bit 1.
 * Valid Range: 0 to 30
 * Internal Base: 3
 * The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_MASK (0x1F00U)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_SHIFT (8U)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_SHIFT) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_MASK)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_MASK) >> DDRCTL_ADDRMAP1_ADDRMAP_BANK_B1_SHIFT)

/*
 * ADDRMAP_BANK_B0 (R/W)
 *
 * Description: Selects the HIF address bits used as bank address bit 0.
 * Valid Range: 0 to 30
 * Internal Base: 2
 * The selected HIF address bit for each of the bank address bits is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_MASK (0x1FU)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_SHIFT (0U)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_SHIFT) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_MASK)
#define DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_MASK) >> DDRCTL_ADDRMAP1_ADDRMAP_BANK_B0_SHIFT)

/* Bitfield definition for register: ADDRMAP2 */
/*
 * ADDRMAP_COL_B5 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 5 (if MEMC_BURST_LENGTH = 4) or 6 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 6 (if MEMC_BURST_LENGTH = 4) or 7 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 7 (if MEMC_BURST_LENGTH = 4) or 8 (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 5
 * The selected HIF address bit is determined by adding the internal base to the value of this field. If set to 15, this column address bit is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_MASK (0xF000000UL)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_SHIFT (24U)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_SHIFT) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_MASK)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_MASK) >> DDRCTL_ADDRMAP2_ADDRMAP_COL_B5_SHIFT)

/*
 * ADDRMAP_COL_B4 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 4 (if MEMC_BURST_LENGTH = 4) or 5 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 5 (if MEMC_BURST_LENGTH = 4) or 6 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 6 (if MEMC_BURST_LENGTH = 4) or 7 (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 4
 * The selected HIF address bit is determined by adding the internal base to the value of this field. If set to 15, this column address bit is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_MASK (0xF0000UL)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_SHIFT (16U)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_SHIFT) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_MASK)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_MASK) >> DDRCTL_ADDRMAP2_ADDRMAP_COL_B4_SHIFT)

/*
 * ADDRMAP_COL_B3 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 3 (if MEMC_BURST_LENGTH = 4) or 4 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 4 (if MEMC_BURST_LENGTH = 4) or 5 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 5 (if MEMC_BURST_LENGTH = 4) or 6 (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7
 * Internal Base: 3
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_MASK (0xF00U)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_SHIFT (8U)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_SHIFT) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_MASK)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_MASK) >> DDRCTL_ADDRMAP2_ADDRMAP_COL_B3_SHIFT)

/*
 * ADDRMAP_COL_B2 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 2 (if MEMC_BURST_LENGTH = 4) or 3 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 3 (if MEMC_BURST_LENGTH = 4) or 4 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 4 (if MEMC_BURST_LENGTH = 4) or 5 (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7
 * Internal Base: 2
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_MASK (0xFU)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_SHIFT (0U)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_SHIFT) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_MASK)
#define DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_MASK) >> DDRCTL_ADDRMAP2_ADDRMAP_COL_B2_SHIFT)

/* Bitfield definition for register: ADDRMAP3 */
/*
 * ADDRMAP_COL_B9 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 9 (if MEMC_BURST_LENGTH = 4) or 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8)
 * Half bus width mode: Selects the HIF address bit used as column address bit 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 4) or 13 (11 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8).
 * (Column address bit 11 in LPDDR2/LPDDR3 mode) Quarter bus width mode: Selects the HIF address bit used as column address bit 13 (11 in LPDDR2/LPDDR3 mode) (if
 * MEMC_BURST_LENGTH = 4) or UNUSED (if
 * MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 9
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto- precharge in the CA bus and hence column bit 10 is used. Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_MASK (0xF000000UL)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_SHIFT (24U)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_SHIFT) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_MASK)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_MASK) >> DDRCTL_ADDRMAP3_ADDRMAP_COL_B9_SHIFT)

/*
 * ADDRMAP_COL_B8 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 8 (if MEMC_BURST_LENGTH = 4) or 9 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 9 (if MEMC_BURST_LENGTH = 4) or 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 4) or 13 (11 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 8
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto- precharge in the CA bus and hence column bit 10 is used. Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_MASK (0xF0000UL)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_SHIFT (16U)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_SHIFT) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_MASK)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_MASK) >> DDRCTL_ADDRMAP3_ADDRMAP_COL_B8_SHIFT)

/*
 * ADDRMAP_COL_B7 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 7 (if MEMC_BURST_LENGTH = 4) or 8 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 8 (if MEMC_BURST_LENGTH = 4) or 9 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 9 (if MEMC_BURST_LENGTH = 4) or 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 7
 * The selected HIF address bit is determined by adding the internal base to the value of this field. If set to 15, this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is reserved for indicating auto-precharge and hence no source address bit can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto- precharge in the CA bus and hence column bit 10 is used. Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_MASK (0xF00U)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_SHIFT (8U)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_SHIFT) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_MASK)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_MASK) >> DDRCTL_ADDRMAP3_ADDRMAP_COL_B7_SHIFT)

/*
 * ADDRMAP_COL_B6 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 6 (if MEMC_BURST_LENGTH = 4) or 7 (if
 * MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 7 (if MEMC_BURST_LENGTH = 4) or 8 (if MEMC_BURST_LENGTH = 8).
 * Quarter bus width mode: Selects the HIF address bit used as column address bit 8 (if MEMC_BURST_LENGTH = 4) or 9 (if MEMC_BURST_LENGTH = 8).
 * Valid Range: 0 to 7, and 15
 * Internal Base: 6
 * The selected HIF address bit is determined by adding the internal base to the value of this field. If set to 15, this column address bit is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_MASK (0xFU)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_SHIFT (0U)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_SHIFT) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_MASK)
#define DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_MASK) >> DDRCTL_ADDRMAP3_ADDRMAP_COL_B6_SHIFT)

/* Bitfield definition for register: ADDRMAP4 */
/*
 * ADDRMAP_COL_B11 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 13 (11 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 4) or UNUSED (if MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Unused. To make it unused, this should be tied to 4'hF.
 * Quarter bus width mode: Unused. To make it unused, this must be tied to 4'hF.
 * Valid Range: 0 to 7, and 15
 * Internal Base: 11
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto- precharge in the CA bus and hence column bit 10 is used. Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_MASK (0xF00U)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_SHIFT (8U)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_SHIFT) & DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_MASK)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_MASK) >> DDRCTL_ADDRMAP4_ADDRMAP_COL_B11_SHIFT)

/*
 * ADDRMAP_COL_B10 (R/W)
 *
 * Description: Full bus width mode: Selects the HIF address bit used as column address bit 11 (10 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 4) or 13 (11 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 8).
 * Half bus width mode: Selects the HIF address bit used as column address bit 13 (11 in LPDDR2/LPDDR3 mode) (if MEMC_BURST_LENGTH = 4) or UNUSED (if MEMC_BURST_LENGTH = 8)
 * Quarter bus width mode: UNUSED. To make it unused, this must be tied to 4'hF.
 * Valid Range: 0 to 7, and 15
 * Internal Base: 10
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, this column address bit is set to 0.
 * Note: Per JEDEC DDR2/3/mDDR specification, column address bit 10 is reserved for indicating auto-precharge, and hence no source address bit can be mapped to column address bit 10.
 * In LPDDR2/LPDDR3, there is a dedicated bit for auto- precharge in the CA bus and hence column bit 10 is used. Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_MASK (0xFU)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_SHIFT (0U)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_SHIFT) & DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_MASK)
#define DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_MASK) >> DDRCTL_ADDRMAP4_ADDRMAP_COL_B10_SHIFT)

/* Bitfield definition for register: ADDRMAP5 */
/*
 * ADDRMAP_ROW_B11 (R/W)
 *
 * Description: Selects the HIF address bit used as row address bit 11.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 17
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, row address bit 11 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_MASK (0xF000000UL)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_SHIFT (24U)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_SHIFT) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_MASK)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_MASK) >> DDRCTL_ADDRMAP5_ADDRMAP_ROW_B11_SHIFT)

/*
 * ADDRMAP_ROW_B2_10 (R/W)
 *
 * Description: Selects the HIF address bits used as row address bits 2 to 10.
 * Valid Range: 0 to 11
 * Internal Base: 8 (for row address bit 2), 9 (for row address bit 3), 10 (for row address bit 4) etc increasing to 16 (for row
 * address bit 10)
 * The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_MASK (0xF0000UL)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_SHIFT (16U)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_SHIFT) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_MASK)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_MASK) >> DDRCTL_ADDRMAP5_ADDRMAP_ROW_B2_10_SHIFT)

/*
 * ADDRMAP_ROW_B1 (R/W)
 *
 * Description: Selects the HIF address bits used as row address bit 1.
 * Valid Range: 0 to 11
 * Internal Base: 7
 * The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_MASK (0xF00U)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_SHIFT (8U)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_SHIFT) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_MASK)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_MASK) >> DDRCTL_ADDRMAP5_ADDRMAP_ROW_B1_SHIFT)

/*
 * ADDRMAP_ROW_B0 (R/W)
 *
 * Description: Selects the HIF address bits used as row address bit 0.
 * Valid Range: 0 to 11
 * Internal Base: 6
 * The selected HIF address bit for each of the row address bits is determined by adding the internal base to the value of this field.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_MASK (0xFU)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_SHIFT (0U)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_SHIFT) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_MASK)
#define DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_MASK) >> DDRCTL_ADDRMAP5_ADDRMAP_ROW_B0_SHIFT)

/* Bitfield definition for register: ADDRMAP6 */
/*
 * ADDRMAP_ROW_B15 (R/W)
 *
 * Description: Selects the HIF address bit used as row address bit 15.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 21
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, row address bit 15 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_MASK (0xF000000UL)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_SHIFT (24U)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_SHIFT) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_MASK)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_MASK) >> DDRCTL_ADDRMAP6_ADDRMAP_ROW_B15_SHIFT)

/*
 * ADDRMAP_ROW_B14 (R/W)
 *
 * Description: Selects the HIF address bit used as row address bit 14.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 20
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, row address bit 14 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_MASK (0xF0000UL)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_SHIFT (16U)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_SHIFT) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_MASK)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_MASK) >> DDRCTL_ADDRMAP6_ADDRMAP_ROW_B14_SHIFT)

/*
 * ADDRMAP_ROW_B13 (R/W)
 *
 * Description: Selects the HIF address bit used as row address bit 13.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 19
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, row address bit 13 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_MASK (0xF00U)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_SHIFT (8U)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_SHIFT) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_MASK)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_MASK) >> DDRCTL_ADDRMAP6_ADDRMAP_ROW_B13_SHIFT)

/*
 * ADDRMAP_ROW_B12 (R/W)
 *
 * Description: Selects the HIF address bit used as row address bit 12.
 * Valid Range: 0 to 11, and 15
 * Internal Base: 18
 * The selected HIF address bit is determined by adding the internal base to the value of this field.
 * If set to 15, row address bit 12 is set to 0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_MASK (0xFU)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_SHIFT (0U)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_SET(x) (((uint32_t)(x) << DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_SHIFT) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_MASK)
#define DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_GET(x) (((uint32_t)(x) & DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_MASK) >> DDRCTL_ADDRMAP6_ADDRMAP_ROW_B12_SHIFT)

/* Bitfield definition for register: ODTCFG */
/*
 * WR_ODT_HOLD (R/W)
 *
 * Description: Cycles to hold ODT for a write command. The minimum supported value is 2. DDR2/DDR3/DDR4
 * BL8 - 0x6
 * BL4 - 0x4
 * LPDDR3 - RU(tDQSSmax/tCK) + 4
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_ODTCFG_WR_ODT_HOLD_MASK (0xF000000UL)
#define DDRCTL_ODTCFG_WR_ODT_HOLD_SHIFT (24U)
#define DDRCTL_ODTCFG_WR_ODT_HOLD_SET(x) (((uint32_t)(x) << DDRCTL_ODTCFG_WR_ODT_HOLD_SHIFT) & DDRCTL_ODTCFG_WR_ODT_HOLD_MASK)
#define DDRCTL_ODTCFG_WR_ODT_HOLD_GET(x) (((uint32_t)(x) & DDRCTL_ODTCFG_WR_ODT_HOLD_MASK) >> DDRCTL_ODTCFG_WR_ODT_HOLD_SHIFT)

/*
 * WR_ODT_DELAY (R/W)
 *
 * Description: The delay, in clock cycles, from issuing a write command to setting ODT values associated with that command. ODT setting must remain constant for the entire time that DQS is driven by the uMCTL2. ODT is used only in DDR2, DDR3, DDR4 and LPDDR3 designs.
 * Recommended values:
 * DDR2
 * If (CWL + AL < 3), then 0.
 * If (CWL + AL >= 3), then (CWL + AL - 3) DDR3 - 0
 * DDR4 - DFITMG1.dfi_t_cmd_lat (to adjust for CAL mode)
 * LPDDR3 - (CWL - RU(tODToffmax/tCK))
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_ODTCFG_WR_ODT_DELAY_MASK (0x1F0000UL)
#define DDRCTL_ODTCFG_WR_ODT_DELAY_SHIFT (16U)
#define DDRCTL_ODTCFG_WR_ODT_DELAY_SET(x) (((uint32_t)(x) << DDRCTL_ODTCFG_WR_ODT_DELAY_SHIFT) & DDRCTL_ODTCFG_WR_ODT_DELAY_MASK)
#define DDRCTL_ODTCFG_WR_ODT_DELAY_GET(x) (((uint32_t)(x) & DDRCTL_ODTCFG_WR_ODT_DELAY_MASK) >> DDRCTL_ODTCFG_WR_ODT_DELAY_SHIFT)

/*
 * RD_ODT_HOLD (R/W)
 *
 * Description: Cycles to hold ODT for a read command. The minimum supported value is 2. Recommended values: DDR2/DDR3
 * BL8 - 0x6
 * BL4 - 0x4
 * DDR4 - 0x6, but needs to be reduced to 0x5 in CAL mode to avoid overlap of read and write ODT LPDDR3 - RU(tDQSCKmax/tCK) + 4 + 1
 * Value After Reset: 0x4
 * Exists: Always
 */
#define DDRCTL_ODTCFG_RD_ODT_HOLD_MASK (0xF00U)
#define DDRCTL_ODTCFG_RD_ODT_HOLD_SHIFT (8U)
#define DDRCTL_ODTCFG_RD_ODT_HOLD_SET(x) (((uint32_t)(x) << DDRCTL_ODTCFG_RD_ODT_HOLD_SHIFT) & DDRCTL_ODTCFG_RD_ODT_HOLD_MASK)
#define DDRCTL_ODTCFG_RD_ODT_HOLD_GET(x) (((uint32_t)(x) & DDRCTL_ODTCFG_RD_ODT_HOLD_MASK) >> DDRCTL_ODTCFG_RD_ODT_HOLD_SHIFT)

/*
 * RD_ODT_DELAY (R/W)
 *
 * Description: The delay, in clock cycles, from issuing a read command to setting ODT values associated with that command. ODT setting must remain constant for the entire time that DQS is driven by the uMCTL2. ODT is used only in DDR2, DDR3, DDR4 and LPDDR3 designs.
 * Recommended values:
 * DDR2
 * If (CL + AL < 4), then 0.
 * If (CL + AL >= 4), then (CL + AL - 4) DDR3
 * (CL - CWL) DDR4
 * If CAL mode is enabled, CL - CWL + DFITMG1.dfi_t_cmd_lat
 * If CAL mode is not enabled, CL - CWL -1, or 0 if CL - CWL < 1
 * LPDDR3, MEMC_FREQ_RATIO=2
 * CL - RU(tODToffmax/tCK)) Value After Reset: 0x0 Exists: Always
 */
#define DDRCTL_ODTCFG_RD_ODT_DELAY_MASK (0x7CU)
#define DDRCTL_ODTCFG_RD_ODT_DELAY_SHIFT (2U)
#define DDRCTL_ODTCFG_RD_ODT_DELAY_SET(x) (((uint32_t)(x) << DDRCTL_ODTCFG_RD_ODT_DELAY_SHIFT) & DDRCTL_ODTCFG_RD_ODT_DELAY_MASK)
#define DDRCTL_ODTCFG_RD_ODT_DELAY_GET(x) (((uint32_t)(x) & DDRCTL_ODTCFG_RD_ODT_DELAY_MASK) >> DDRCTL_ODTCFG_RD_ODT_DELAY_SHIFT)

/* Bitfield definition for register: ODTMAP */
/*
 * RANK1_RD_ODT (R/W)
 *
 * Description: Indicates which remote ODTs must be turned on during a read from rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks Value After Reset: "(MEMC_NUM_RANKS>1) ? 0x2 : 0x0" Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_ODTMAP_RANK1_RD_ODT_MASK (0xF000U)
#define DDRCTL_ODTMAP_RANK1_RD_ODT_SHIFT (12U)
#define DDRCTL_ODTMAP_RANK1_RD_ODT_SET(x) (((uint32_t)(x) << DDRCTL_ODTMAP_RANK1_RD_ODT_SHIFT) & DDRCTL_ODTMAP_RANK1_RD_ODT_MASK)
#define DDRCTL_ODTMAP_RANK1_RD_ODT_GET(x) (((uint32_t)(x) & DDRCTL_ODTMAP_RANK1_RD_ODT_MASK) >> DDRCTL_ODTMAP_RANK1_RD_ODT_SHIFT)

/*
 * RANK1_WR_ODT (R/W)
 *
 * Description: Indicates which remote ODTs must be turned on during a write to rank 1.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Present only in configurations that have 2 or more ranks Value After Reset: "(MEMC_NUM_RANKS>1) ? 0x2 : 0x0" Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_ODTMAP_RANK1_WR_ODT_MASK (0xF00U)
#define DDRCTL_ODTMAP_RANK1_WR_ODT_SHIFT (8U)
#define DDRCTL_ODTMAP_RANK1_WR_ODT_SET(x) (((uint32_t)(x) << DDRCTL_ODTMAP_RANK1_WR_ODT_SHIFT) & DDRCTL_ODTMAP_RANK1_WR_ODT_MASK)
#define DDRCTL_ODTMAP_RANK1_WR_ODT_GET(x) (((uint32_t)(x) & DDRCTL_ODTMAP_RANK1_WR_ODT_MASK) >> DDRCTL_ODTMAP_RANK1_WR_ODT_SHIFT)

/*
 * RANK0_RD_ODT (R/W)
 *
 * Description: Indicates which remote ODTs must be turned on during a read from rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_ODTMAP_RANK0_RD_ODT_MASK (0xF0U)
#define DDRCTL_ODTMAP_RANK0_RD_ODT_SHIFT (4U)
#define DDRCTL_ODTMAP_RANK0_RD_ODT_SET(x) (((uint32_t)(x) << DDRCTL_ODTMAP_RANK0_RD_ODT_SHIFT) & DDRCTL_ODTMAP_RANK0_RD_ODT_MASK)
#define DDRCTL_ODTMAP_RANK0_RD_ODT_GET(x) (((uint32_t)(x) & DDRCTL_ODTMAP_RANK0_RD_ODT_MASK) >> DDRCTL_ODTMAP_RANK0_RD_ODT_SHIFT)

/*
 * RANK0_WR_ODT (R/W)
 *
 * Description: Indicates which remote ODTs must be turned on during a write to rank 0.
 * Each rank has a remote ODT (in the SDRAM) which can be turned on by setting the appropriate bit here.
 * Rank 0 is controlled by the LSB; rank 1 is controlled by bit next to the LSB, etc.
 * For each rank, set its bit to 1 to enable its ODT.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_ODTMAP_RANK0_WR_ODT_MASK (0xFU)
#define DDRCTL_ODTMAP_RANK0_WR_ODT_SHIFT (0U)
#define DDRCTL_ODTMAP_RANK0_WR_ODT_SET(x) (((uint32_t)(x) << DDRCTL_ODTMAP_RANK0_WR_ODT_SHIFT) & DDRCTL_ODTMAP_RANK0_WR_ODT_MASK)
#define DDRCTL_ODTMAP_RANK0_WR_ODT_GET(x) (((uint32_t)(x) & DDRCTL_ODTMAP_RANK0_WR_ODT_MASK) >> DDRCTL_ODTMAP_RANK0_WR_ODT_SHIFT)

/* Bitfield definition for register: SCHED */
/*
 * RDWR_IDLE_GAP (R/W)
 *
 * Description: When the preferred transaction store is empty for these many clock cycles, switch to the alternate transaction store if it is non-empty.
 * The read transaction store (both high and low priority) is the default preferred transaction store and the write transaction store is the alternative store.
 * When prefer write over read is set this is reversed.
 * 0x0 is a legal value for this register. When set to 0x0, the transaction store switching will happen immediately when the switching conditions become true.
 * FOR PERFORMANCE ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_SCHED_RDWR_IDLE_GAP_MASK (0x7F000000UL)
#define DDRCTL_SCHED_RDWR_IDLE_GAP_SHIFT (24U)
#define DDRCTL_SCHED_RDWR_IDLE_GAP_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_RDWR_IDLE_GAP_SHIFT) & DDRCTL_SCHED_RDWR_IDLE_GAP_MASK)
#define DDRCTL_SCHED_RDWR_IDLE_GAP_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_RDWR_IDLE_GAP_MASK) >> DDRCTL_SCHED_RDWR_IDLE_GAP_SHIFT)

/*
 * GO2CRITICAL_HYSTERESIS (R/W)
 *
 * Description: UNUSED Value After Reset: 0x0 Exists: Always
 */
#define DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_MASK (0xFF0000UL)
#define DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_SHIFT (16U)
#define DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_SHIFT) & DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_MASK)
#define DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_MASK) >> DDRCTL_SCHED_GO2CRITICAL_HYSTERESIS_SHIFT)

/*
 * LPR_NUM_ENTRIES (R/W)
 *
 * Description: Number of entries in the low priority transaction store is this value + 1.
 * (MEMC_NO_OF_ENTRY - (SCHED.lpr_num_entries + 1)) is the number of entries available for the high priority transaction store.
 * Setting this to maximum value allocates all entries to low priority transaction store.
 * Setting this to 0 allocates 1 entry to low priority transaction store and the rest to high priority transaction store.
 * Note: In ECC configurations, the numbers of write and low priority read credits issued is one less than in the non-ECC case. One entry each is reserved in the write and low- priority read CAMs for storing the RMW requests arising out of single bit error correction RMW operation.
 * Value After Reset: "MEMC_NO_OF_ENTRY/2"
 * Exists: Always
 */
#define DDRCTL_SCHED_LPR_NUM_ENTRIES_MASK (0x3F00U)
#define DDRCTL_SCHED_LPR_NUM_ENTRIES_SHIFT (8U)
#define DDRCTL_SCHED_LPR_NUM_ENTRIES_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_LPR_NUM_ENTRIES_SHIFT) & DDRCTL_SCHED_LPR_NUM_ENTRIES_MASK)
#define DDRCTL_SCHED_LPR_NUM_ENTRIES_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_LPR_NUM_ENTRIES_MASK) >> DDRCTL_SCHED_LPR_NUM_ENTRIES_SHIFT)

/*
 * PAGECLOSE (R/W)
 *
 * Description: If true, bank is kept open only until there are page hit transactions available in the CAM to that bank. The last read or write command in the CAM with a bank and page hit will be executed with auto-precharge if SCHED1.pageclose_timer=0. Even if this register set to 1 and SCHED1.pageclose_timer is set to 0, explicit precharge (and not auto-precharge) may be issued in some cases where there is a mode switch between Write and Read or between LPR and HPR. The Read and Write commands that are executed as part of the ECC scrub requests are also executed without auto-precharge. If false, the bank remains open until there is a need to close it (to open a different page, or for page timeout or refresh timeout) - also known as open page policy. The open page policy can be overridden by setting the per-command-autopre bit on the HIF interface (co_ih_rxcmd_autopre).
 * The pageclose feature provids a midway between Open and Close page policies.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_SCHED_PAGECLOSE_MASK (0x4U)
#define DDRCTL_SCHED_PAGECLOSE_SHIFT (2U)
#define DDRCTL_SCHED_PAGECLOSE_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_PAGECLOSE_SHIFT) & DDRCTL_SCHED_PAGECLOSE_MASK)
#define DDRCTL_SCHED_PAGECLOSE_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_PAGECLOSE_MASK) >> DDRCTL_SCHED_PAGECLOSE_SHIFT)

/*
 * PREFER_WRITE (R/W)
 *
 * Description: If set then the bank selector prefers writes over reads.
 * FOR DEBUG ONLY.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_SCHED_PREFER_WRITE_MASK (0x2U)
#define DDRCTL_SCHED_PREFER_WRITE_SHIFT (1U)
#define DDRCTL_SCHED_PREFER_WRITE_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_PREFER_WRITE_SHIFT) & DDRCTL_SCHED_PREFER_WRITE_MASK)
#define DDRCTL_SCHED_PREFER_WRITE_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_PREFER_WRITE_MASK) >> DDRCTL_SCHED_PREFER_WRITE_SHIFT)

/*
 * FORCE_LOW_PRI_N (R/W)
 *
 * Description: Active low signal. When asserted ('0'), all incoming transactions are forced to low priority. This implies that all High Priority Read (HPR) and Variable Priority Read commands (VPR) will be treated as Low Priority Read (LPR) commands. On the write side, all Variable Priority Write (VPW) commands will be treated as Normal Priority Write (NPW) commands. Forcing the incoming transactions to low priority implicitly turns off Bypass path for read commands.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_SCHED_FORCE_LOW_PRI_N_MASK (0x1U)
#define DDRCTL_SCHED_FORCE_LOW_PRI_N_SHIFT (0U)
#define DDRCTL_SCHED_FORCE_LOW_PRI_N_SET(x) (((uint32_t)(x) << DDRCTL_SCHED_FORCE_LOW_PRI_N_SHIFT) & DDRCTL_SCHED_FORCE_LOW_PRI_N_MASK)
#define DDRCTL_SCHED_FORCE_LOW_PRI_N_GET(x) (((uint32_t)(x) & DDRCTL_SCHED_FORCE_LOW_PRI_N_MASK) >> DDRCTL_SCHED_FORCE_LOW_PRI_N_SHIFT)

/* Bitfield definition for register: SCHED1 */
/*
 * PAGECLOSE_TIMER (R/W)
 *
 * Description: This field works in conjunction with SCHED.pageclose. It only has meaning if SCHED.pageclose==1.
 * If SCHED.pageclose==1 and pageclose_timer==0, then an auto-precharge may be scheduled for last read or write command in the CAM with a bank and page hit. Note, sometimes an explicit precharge is scheduled instead of the auto-precharge. See SCHED.pageclose for details of when this may happen.
 * If SCHED.pageclose==1 and pageclose_timer>0, then an auto-precharge is not scheduled for last read or write command in the CAM with a bank and page hit. Instead, a timer is started, with pageclose_timer as the initial value. There is a timer on a per bank basis. The timer decrements unless the next read or write in the CAM to a bank is a page hit. It gets reset to pageclose_timer value if the next read or write in the CAM to a bank is a page hit. Once the timer has reached zero, an explcit precharge will be attempted to be scheduled.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_SCHED1_PAGECLOSE_TIMER_MASK (0xFFU)
#define DDRCTL_SCHED1_PAGECLOSE_TIMER_SHIFT (0U)
#define DDRCTL_SCHED1_PAGECLOSE_TIMER_SET(x) (((uint32_t)(x) << DDRCTL_SCHED1_PAGECLOSE_TIMER_SHIFT) & DDRCTL_SCHED1_PAGECLOSE_TIMER_MASK)
#define DDRCTL_SCHED1_PAGECLOSE_TIMER_GET(x) (((uint32_t)(x) & DDRCTL_SCHED1_PAGECLOSE_TIMER_MASK) >> DDRCTL_SCHED1_PAGECLOSE_TIMER_SHIFT)

/* Bitfield definition for register: PERFHPR1 */
/*
 * HPR_XACT_RUN_LENGTH (R/W)
 *
 * Description: Number of transactions that are serviced once the HPR queue goes critical is the smaller of:
 * This number
 * Number of transactions available Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0xf
 * Exists: Always
 */
#define DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_MASK (0xFF000000UL)
#define DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_SHIFT (24U)
#define DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_SET(x) (((uint32_t)(x) << DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_SHIFT) & DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_MASK)
#define DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_GET(x) (((uint32_t)(x) & DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_MASK) >> DDRCTL_PERFHPR1_HPR_XACT_RUN_LENGTH_SHIFT)

/*
 * HPR_MAX_STARVE (R/W)
 *
 * Description: Number of clocks that the HPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function should not be disabled as it will cause excessive latencies.
 * Unit: Clock cycles.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_PERFHPR1_HPR_MAX_STARVE_MASK (0xFFFFU)
#define DDRCTL_PERFHPR1_HPR_MAX_STARVE_SHIFT (0U)
#define DDRCTL_PERFHPR1_HPR_MAX_STARVE_SET(x) (((uint32_t)(x) << DDRCTL_PERFHPR1_HPR_MAX_STARVE_SHIFT) & DDRCTL_PERFHPR1_HPR_MAX_STARVE_MASK)
#define DDRCTL_PERFHPR1_HPR_MAX_STARVE_GET(x) (((uint32_t)(x) & DDRCTL_PERFHPR1_HPR_MAX_STARVE_MASK) >> DDRCTL_PERFHPR1_HPR_MAX_STARVE_SHIFT)

/* Bitfield definition for register: PERFLPR1 */
/*
 * LPR_XACT_RUN_LENGTH (R/W)
 *
 * Description: Number of transactions that are serviced once the LPR queue goes critical is the smaller of:
 * This number
 * Number of transactions available. Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0xf
 * Exists: Always
 */
#define DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_MASK (0xFF000000UL)
#define DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_SHIFT (24U)
#define DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_SET(x) (((uint32_t)(x) << DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_SHIFT) & DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_MASK)
#define DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_GET(x) (((uint32_t)(x) & DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_MASK) >> DDRCTL_PERFLPR1_LPR_XACT_RUN_LENGTH_SHIFT)

/*
 * LPR_MAX_STARVE (R/W)
 *
 * Description: Number of clocks that the LPR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function should not be disabled as it will cause excessive latencies.
 * Unit: Clock cycles.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x7f
 * Exists: Always
 */
#define DDRCTL_PERFLPR1_LPR_MAX_STARVE_MASK (0xFFFFU)
#define DDRCTL_PERFLPR1_LPR_MAX_STARVE_SHIFT (0U)
#define DDRCTL_PERFLPR1_LPR_MAX_STARVE_SET(x) (((uint32_t)(x) << DDRCTL_PERFLPR1_LPR_MAX_STARVE_SHIFT) & DDRCTL_PERFLPR1_LPR_MAX_STARVE_MASK)
#define DDRCTL_PERFLPR1_LPR_MAX_STARVE_GET(x) (((uint32_t)(x) & DDRCTL_PERFLPR1_LPR_MAX_STARVE_MASK) >> DDRCTL_PERFLPR1_LPR_MAX_STARVE_SHIFT)

/* Bitfield definition for register: PERFWR1 */
/*
 * W_XACT_RUN_LENGTH (R/W)
 *
 * Description: Number of transactions that are serviced once the WR queue goes critical is the smaller of:
 * This number
 * Number of transactions available. Unit: Transaction.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0xf
 * Exists: Always
 */
#define DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_MASK (0xFF000000UL)
#define DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_SHIFT (24U)
#define DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_SET(x) (((uint32_t)(x) << DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_SHIFT) & DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_MASK)
#define DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_GET(x) (((uint32_t)(x) & DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_MASK) >> DDRCTL_PERFWR1_W_XACT_RUN_LENGTH_SHIFT)

/*
 * W_MAX_STARVE (R/W)
 *
 * Description: Number of clocks that the WR queue can be starved before it goes critical. The minimum valid functional value for this register is 0x1. Programming it to 0x0 will disable the starvation functionality; during normal operation, this function should not be disabled as it will cause excessive latencies.
 * Unit: Clock cycles.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x7f
 * Exists: Always
 */
#define DDRCTL_PERFWR1_W_MAX_STARVE_MASK (0xFFFFU)
#define DDRCTL_PERFWR1_W_MAX_STARVE_SHIFT (0U)
#define DDRCTL_PERFWR1_W_MAX_STARVE_SET(x) (((uint32_t)(x) << DDRCTL_PERFWR1_W_MAX_STARVE_SHIFT) & DDRCTL_PERFWR1_W_MAX_STARVE_MASK)
#define DDRCTL_PERFWR1_W_MAX_STARVE_GET(x) (((uint32_t)(x) & DDRCTL_PERFWR1_W_MAX_STARVE_MASK) >> DDRCTL_PERFWR1_W_MAX_STARVE_SHIFT)

/* Bitfield definition for register: PERFVPR1 */
/*
 * VPR_TIMEOUT_RANGE (R/W)
 *
 * Description: Indicates the range of the timeout value that is used for grouping the expired VPR commands in the CAM in DDRC. For example, if the register value is set to 0xF, then the priorities of all the VPR commands whose timeout counters are 15 or below will be considered as expired-VPR commands when the timeout value of any of the VPR commands reach 0. The expired-VPR commands, when present, are given higher priority than HPR commands. The VPR commands are expected to consist of largely page hit traffic and by grouping them together the bus utilization is expected to increase. This register applies to transactions inside the DDRC only.
 * The Max value for this register is 0x7FF and the Min value is 0x0.
 * When programmed to the Max value of 0x7FF, all the VPR commands that come in to DDRC will time-out right-away and will be considered as expired-VPR.
 * When programmed to the Min value of 0x0, the timer of each command would have to reach a value of 0 before it will be considered as expired-VPR.
 * Unit: Clock cycles.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x0
 * Exists: UMCTL2_VPR_EN==1
 */
#define DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_MASK (0x7FFU)
#define DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_SHIFT (0U)
#define DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_SET(x) (((uint32_t)(x) << DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_SHIFT) & DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_MASK)
#define DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_GET(x) (((uint32_t)(x) & DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_MASK) >> DDRCTL_PERFVPR1_VPR_TIMEOUT_RANGE_SHIFT)

/* Bitfield definition for register: PERFVPW1 */
/*
 * VPW_TIMEOUT_RANGE (R/W)
 *
 * Description: Indicates the range of the timeout value that is used for grouping the expired VPW commands in the CAM in DDRC. For example, if the register value is set to 0xF, then the priorities of all the VPW commands whose timeout counters are 15 or below will be considered as expired-VPW commands when the timeout value of any of the VPW commands reach 0. The expired-VPW commands, when present, are given higher priority than normal Write commands. The VPW commands are expected to consist of largely page hit traffic and by grouping them together the bus utilization is expected to increase. This register applies to transactions inside the DDRC only.
 * The Max value for this register is 0x7FF and the Min value is 0x0.
 * When programmed to the Max value of 0x7FF, all the VPW commands that come in to DDRC will time-out right-away and will be considered as expired-VPW.
 * When programmed to the Min value of 0x0, the timer of each command would have to reach a value of 0 before it will be considered as expired-VPW.
 * Unit: Clock cycles.
 * FOR PERFORMANCE ONLY.
 * Value After Reset: 0x0
 * Exists: UMCTL2_VPW_EN==1
 */
#define DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_MASK (0x7FFU)
#define DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_SHIFT (0U)
#define DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_SET(x) (((uint32_t)(x) << DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_SHIFT) & DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_MASK)
#define DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_GET(x) (((uint32_t)(x) & DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_MASK) >> DDRCTL_PERFVPW1_VPW_TIMEOUT_RANGE_SHIFT)

/* Bitfield definition for register: DBG0 */
/*
 * DIS_COLLISION_PAGE_OPT (R/W)
 *
 * Description: When this is set to '0', auto-precharge is disabled for the flushed command in a collision case. Collision cases are write followed by read to same address, read followed by write to same address, or write followed by write to same address with DBG0.dis_wc bit = 1 (where same address comparisons exclude the two address bits representing critical word).
 * FOR DEBUG ONLY.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_MASK (0x10U)
#define DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_SHIFT (4U)
#define DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_SET(x) (((uint32_t)(x) << DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_SHIFT) & DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_MASK)
#define DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_GET(x) (((uint32_t)(x) & DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_MASK) >> DDRCTL_DBG0_DIS_COLLISION_PAGE_OPT_SHIFT)

/*
 * DIS_ACT_BYPASS (R/W)
 *
 * Description: Only present in designs supporting activate bypass.
 * When 1, disable bypass path for high priority read activates FOR DEBUG ONLY.
 * Value After Reset: 0x0
 * Exists: MEMC_BYPASS==1
 */
#define DDRCTL_DBG0_DIS_ACT_BYPASS_MASK (0x4U)
#define DDRCTL_DBG0_DIS_ACT_BYPASS_SHIFT (2U)
#define DDRCTL_DBG0_DIS_ACT_BYPASS_SET(x) (((uint32_t)(x) << DDRCTL_DBG0_DIS_ACT_BYPASS_SHIFT) & DDRCTL_DBG0_DIS_ACT_BYPASS_MASK)
#define DDRCTL_DBG0_DIS_ACT_BYPASS_GET(x) (((uint32_t)(x) & DDRCTL_DBG0_DIS_ACT_BYPASS_MASK) >> DDRCTL_DBG0_DIS_ACT_BYPASS_SHIFT)

/*
 * DIS_RD_BYPASS (R/W)
 *
 * Description: Only present in designs supporting read bypass.
 * When 1, disable bypass path for high priority read page hits FOR DEBUG ONLY.
 * Value After Reset: 0x0
 * Exists: MEMC_BYPASS==1
 */
#define DDRCTL_DBG0_DIS_RD_BYPASS_MASK (0x2U)
#define DDRCTL_DBG0_DIS_RD_BYPASS_SHIFT (1U)
#define DDRCTL_DBG0_DIS_RD_BYPASS_SET(x) (((uint32_t)(x) << DDRCTL_DBG0_DIS_RD_BYPASS_SHIFT) & DDRCTL_DBG0_DIS_RD_BYPASS_MASK)
#define DDRCTL_DBG0_DIS_RD_BYPASS_GET(x) (((uint32_t)(x) & DDRCTL_DBG0_DIS_RD_BYPASS_MASK) >> DDRCTL_DBG0_DIS_RD_BYPASS_SHIFT)

/*
 * DIS_WC (R/W)
 *
 * Description: When 1, disable write combine. FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBG0_DIS_WC_MASK (0x1U)
#define DDRCTL_DBG0_DIS_WC_SHIFT (0U)
#define DDRCTL_DBG0_DIS_WC_SET(x) (((uint32_t)(x) << DDRCTL_DBG0_DIS_WC_SHIFT) & DDRCTL_DBG0_DIS_WC_MASK)
#define DDRCTL_DBG0_DIS_WC_GET(x) (((uint32_t)(x) & DDRCTL_DBG0_DIS_WC_MASK) >> DDRCTL_DBG0_DIS_WC_SHIFT)

/* Bitfield definition for register: DBG1 */
/*
 * DIS_HIF (R/W)
 *
 * Description: When 1, uMCTL2 asserts the HIF command ih_co_stall. uMCTL2 will ignore the co_ih_rxcmd_valid and all other associated request signals.
 * This bit is intended to be switched on-the-fly.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBG1_DIS_HIF_MASK (0x2U)
#define DDRCTL_DBG1_DIS_HIF_SHIFT (1U)
#define DDRCTL_DBG1_DIS_HIF_SET(x) (((uint32_t)(x) << DDRCTL_DBG1_DIS_HIF_SHIFT) & DDRCTL_DBG1_DIS_HIF_MASK)
#define DDRCTL_DBG1_DIS_HIF_GET(x) (((uint32_t)(x) & DDRCTL_DBG1_DIS_HIF_MASK) >> DDRCTL_DBG1_DIS_HIF_SHIFT)

/*
 * DIS_DQ (R/W)
 *
 * Description: When 1, uMCTL2 will not de-queue any transactions from the CAM. Bypass is also disabled. All transactions are queued in the CAM. No reads or writes are issued to SDRAM as long as this is asserted.
 * This bit may be used to prevent reads or writes being issued by the uMCTL2, which makes it safe to modify certain register fields associated with reads and writes (see User Guide for details). After setting this bit, it is strongly recommended to poll DBGCAM.wr_data_pipeline_empty and DBGCAM.rd_data_pipeline_empty, before making changes to any registers which affect reads and writes. This will ensure that the relevant logic in the DDRC is idle.
 * This bit is intended to be switched on-the-fly.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBG1_DIS_DQ_MASK (0x1U)
#define DDRCTL_DBG1_DIS_DQ_SHIFT (0U)
#define DDRCTL_DBG1_DIS_DQ_SET(x) (((uint32_t)(x) << DDRCTL_DBG1_DIS_DQ_SHIFT) & DDRCTL_DBG1_DIS_DQ_MASK)
#define DDRCTL_DBG1_DIS_DQ_GET(x) (((uint32_t)(x) & DDRCTL_DBG1_DIS_DQ_MASK) >> DDRCTL_DBG1_DIS_DQ_SHIFT)

/* Bitfield definition for register: DBGCAM */
/*
 * WR_DATA_PIPELINE_EMPTY (R)
 *
 * Description: This bit indicates that the write data pipeline on the DFI interface is empty. This register is intended to be polled after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_WR_DATA_PIPELINE_EMPTY_MASK (0x20000000UL)
#define DDRCTL_DBGCAM_WR_DATA_PIPELINE_EMPTY_SHIFT (29U)
#define DDRCTL_DBGCAM_WR_DATA_PIPELINE_EMPTY_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_WR_DATA_PIPELINE_EMPTY_MASK) >> DDRCTL_DBGCAM_WR_DATA_PIPELINE_EMPTY_SHIFT)

/*
 * RD_DATA_PIPELINE_EMPTY (R)
 *
 * Description: This bit indicates that the read data pipeline on the DFI interface is empty. This register is intended to be polled after setting DBG1.dis_dq, to ensure that all remaining commands/data have completed.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_RD_DATA_PIPELINE_EMPTY_MASK (0x10000000UL)
#define DDRCTL_DBGCAM_RD_DATA_PIPELINE_EMPTY_SHIFT (28U)
#define DDRCTL_DBGCAM_RD_DATA_PIPELINE_EMPTY_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_RD_DATA_PIPELINE_EMPTY_MASK) >> DDRCTL_DBGCAM_RD_DATA_PIPELINE_EMPTY_SHIFT)

/*
 * DBG_WR_Q_EMPTY (R)
 *
 * Description: When 1, all the Write command queues and Write data buffers inside DDRC are empty. This register is to be used for debug purpose.
 * An example use-case scenario: When Controller enters Self- Refresh using the Low-Power entry sequence, Controller is expected to have executed all the commands in its queues and the write and read data drained. Hence this register should be 1 at that time.
 * FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_WR_Q_EMPTY_MASK (0x4000000UL)
#define DDRCTL_DBGCAM_DBG_WR_Q_EMPTY_SHIFT (26U)
#define DDRCTL_DBGCAM_DBG_WR_Q_EMPTY_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_WR_Q_EMPTY_MASK) >> DDRCTL_DBGCAM_DBG_WR_Q_EMPTY_SHIFT)

/*
 * DBG_RD_Q_EMPTY (R)
 *
 * Description: When 1, all the Read command queues and Read data buffers inside DDRC are empty. This register is to be used for debug purpose.
 * An example use-case scenario: When Controller enters Self- Refresh using the Low-Power entry sequence, Controller is expected to have executed all the commands in its queues and the write and read data drained. Hence this register should be 1 at that time.
 * FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_RD_Q_EMPTY_MASK (0x2000000UL)
#define DDRCTL_DBGCAM_DBG_RD_Q_EMPTY_SHIFT (25U)
#define DDRCTL_DBGCAM_DBG_RD_Q_EMPTY_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_RD_Q_EMPTY_MASK) >> DDRCTL_DBGCAM_DBG_RD_Q_EMPTY_SHIFT)

/*
 * DBG_STALL (R)
 *
 * Description: Stall FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_STALL_MASK (0x1000000UL)
#define DDRCTL_DBGCAM_DBG_STALL_SHIFT (24U)
#define DDRCTL_DBGCAM_DBG_STALL_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_STALL_MASK) >> DDRCTL_DBGCAM_DBG_STALL_SHIFT)

/*
 * DBG_W_Q_DEPTH (R)
 *
 * Description: Write queue depth
 * Note: The width of this field is dependent on log(MEMC_NO_OF_ENTRY+1). For example, if CAM depth
 * = 32, then register width is 6 bits and bit 22 is reserved. FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_W_Q_DEPTH_MASK (0x7F0000UL)
#define DDRCTL_DBGCAM_DBG_W_Q_DEPTH_SHIFT (16U)
#define DDRCTL_DBGCAM_DBG_W_Q_DEPTH_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_W_Q_DEPTH_MASK) >> DDRCTL_DBGCAM_DBG_W_Q_DEPTH_SHIFT)

/*
 * DBG_LPR_Q_DEPTH (R)
 *
 * Description: Low priority read queue depth Note: The width of this field is dependent on
 * log(MEMC_NO_OF_ENTRY+1). For example, if CAM depth
 * = 32, then register width is 6 bits and bit 14 is reserved FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_LPR_Q_DEPTH_MASK (0x7F00U)
#define DDRCTL_DBGCAM_DBG_LPR_Q_DEPTH_SHIFT (8U)
#define DDRCTL_DBGCAM_DBG_LPR_Q_DEPTH_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_LPR_Q_DEPTH_MASK) >> DDRCTL_DBGCAM_DBG_LPR_Q_DEPTH_SHIFT)

/*
 * DBG_HPR_Q_DEPTH (R)
 *
 * Description: High priority read queue depth Note: The width of this field is dependent on
 * log(MEMC_NO_OF_ENTRY+1). For example, if CAM depth
 * = 32, then register width is 6 bits and bit 6 is reserved FOR DEBUG ONLY
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCAM_DBG_HPR_Q_DEPTH_MASK (0x7FU)
#define DDRCTL_DBGCAM_DBG_HPR_Q_DEPTH_SHIFT (0U)
#define DDRCTL_DBGCAM_DBG_HPR_Q_DEPTH_GET(x) (((uint32_t)(x) & DDRCTL_DBGCAM_DBG_HPR_Q_DEPTH_MASK) >> DDRCTL_DBGCAM_DBG_HPR_Q_DEPTH_SHIFT)

/* Bitfield definition for register: DBGCMD */
/*
 * CTRLUPD (R/WSC)
 *
 * Description: Setting this register bit to 1 indicates to the uMCTL2 to issue a dfi_ctrlupd_req to the PHY. When this request is stored in uMCTL2, the bit is automatically cleared. This operation must only be performed when DFIUPD0.dis_auto_ctrlupd=1.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCMD_CTRLUPD_MASK (0x20U)
#define DDRCTL_DBGCMD_CTRLUPD_SHIFT (5U)
#define DDRCTL_DBGCMD_CTRLUPD_SET(x) (((uint32_t)(x) << DDRCTL_DBGCMD_CTRLUPD_SHIFT) & DDRCTL_DBGCMD_CTRLUPD_MASK)
#define DDRCTL_DBGCMD_CTRLUPD_GET(x) (((uint32_t)(x) & DDRCTL_DBGCMD_CTRLUPD_MASK) >> DDRCTL_DBGCMD_CTRLUPD_SHIFT)

/*
 * ZQ_CALIB_SHORT (R/WSC)
 *
 * Description: Setting this register bit to 1 indicates to the uMCTL2 to issue a ZQCS (ZQ calibration short) command to the SDRAM. When this request is stored in uMCTL2, the bit is automatically cleared. This operation can be performed only when ZQCTL0.dis_auto_zq=1. It is recommended NOT to set this register bit if in Init operating mode. This register bit is ignored when in Self-Refresh and Deep power-down operating modes.
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3_OR_4_OR_LPDDR2==1
 */
#define DDRCTL_DBGCMD_ZQ_CALIB_SHORT_MASK (0x10U)
#define DDRCTL_DBGCMD_ZQ_CALIB_SHORT_SHIFT (4U)
#define DDRCTL_DBGCMD_ZQ_CALIB_SHORT_SET(x) (((uint32_t)(x) << DDRCTL_DBGCMD_ZQ_CALIB_SHORT_SHIFT) & DDRCTL_DBGCMD_ZQ_CALIB_SHORT_MASK)
#define DDRCTL_DBGCMD_ZQ_CALIB_SHORT_GET(x) (((uint32_t)(x) & DDRCTL_DBGCMD_ZQ_CALIB_SHORT_MASK) >> DDRCTL_DBGCMD_ZQ_CALIB_SHORT_SHIFT)

/*
 * RANK1_REFRESH (R/WSC)
 *
 * Description: Setting this register bit to 1 indicates to the uMCTL2 to issue a refresh to rank 1. When this request is stored in uMCTL2, the bit is automatically cleared. This operation can be performed only when RFSHCTL3.dis_auto_refresh=1. It is recommended NOT to set this register bit if in Init or Deep power-down operating modes or Maximum Power Saving Mode.
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_DBGCMD_RANK1_REFRESH_MASK (0x2U)
#define DDRCTL_DBGCMD_RANK1_REFRESH_SHIFT (1U)
#define DDRCTL_DBGCMD_RANK1_REFRESH_SET(x) (((uint32_t)(x) << DDRCTL_DBGCMD_RANK1_REFRESH_SHIFT) & DDRCTL_DBGCMD_RANK1_REFRESH_MASK)
#define DDRCTL_DBGCMD_RANK1_REFRESH_GET(x) (((uint32_t)(x) & DDRCTL_DBGCMD_RANK1_REFRESH_MASK) >> DDRCTL_DBGCMD_RANK1_REFRESH_SHIFT)

/*
 * RANK0_REFRESH (R/WSC)
 *
 * Description: Setting this register bit to 1 indicates to the uMCTL2 to issue a refresh to rank 0. When this request is stored in uMCTL2, the bit is automatically cleared. This operation can be performed only when RFSHCTL3.dis_auto_refresh=1. It is recommended NOT to set this register bit if in Init or Deep power-down operating modes or Maximum Power Saving Mode.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGCMD_RANK0_REFRESH_MASK (0x1U)
#define DDRCTL_DBGCMD_RANK0_REFRESH_SHIFT (0U)
#define DDRCTL_DBGCMD_RANK0_REFRESH_SET(x) (((uint32_t)(x) << DDRCTL_DBGCMD_RANK0_REFRESH_SHIFT) & DDRCTL_DBGCMD_RANK0_REFRESH_MASK)
#define DDRCTL_DBGCMD_RANK0_REFRESH_GET(x) (((uint32_t)(x) & DDRCTL_DBGCMD_RANK0_REFRESH_MASK) >> DDRCTL_DBGCMD_RANK0_REFRESH_SHIFT)

/* Bitfield definition for register: DBGSTAT */
/*
 * CTRLUPD_BUSY (R)
 *
 * Description: SoC core may initiate a ctrlupd operation only if this signal is low. This signal goes high in the clock after the uMCTL2 accepts the ctrlupd request. It goes low when the ctrlupd operation is initiated in uMCTL2. It is recommended not to perform ctrlupd operations when this signal is high.
 * 0 - Indicates that the SoC core can initiate a ctrlupd operation
 * 1 - Indicates that ctrlupd operation has not been initiated yet in uMCTL2
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGSTAT_CTRLUPD_BUSY_MASK (0x20U)
#define DDRCTL_DBGSTAT_CTRLUPD_BUSY_SHIFT (5U)
#define DDRCTL_DBGSTAT_CTRLUPD_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_DBGSTAT_CTRLUPD_BUSY_MASK) >> DDRCTL_DBGSTAT_CTRLUPD_BUSY_SHIFT)

/*
 * ZQ_CALIB_SHORT_BUSY (R)
 *
 * Description: SoC core may initiate a ZQCS (ZQ calibration short) operation only if this signal is low. This signal goes high in the clock after the uMCTL2 accepts the ZQCS request. It goes low when the ZQCS operation is initiated in uMCTL2. It is recommended not to perform ZQCS operations when this signal is high.
 * 0 - Indicates that the SoC core can initiate a ZQCS operation
 * 1 - Indicates that ZQCS operation has not been initiated yet in uMCTL2
 * Value After Reset: 0x0
 * Exists: MEMC_DDR3_OR_4_OR_LPDDR2==1
 */
#define DDRCTL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_MASK (0x10U)
#define DDRCTL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_SHIFT (4U)
#define DDRCTL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_MASK) >> DDRCTL_DBGSTAT_ZQ_CALIB_SHORT_BUSY_SHIFT)

/*
 * RANK1_REFRESH_BUSY (R)
 *
 * Description: SoC core may initiate a rank1_refresh operation (refresh operation to rank 1) only if this signal is low. This signal goes high in the clock after DBGCMD.rank1_refresh is set to one. It goes low when the rank1_refresh operation is stored in uMCTL2. It is recommended not to perform rank1_refresh operations when this signal is high.
 * 0 - Indicates that the SoC core can initiate a rank1_refresh operation
 * 1 - Indicates that rank1_refresh operation has not been stored yet in uMCTL2
 * Value After Reset: 0x0
 * Exists: MEMC_NUM_RANKS>1
 */
#define DDRCTL_DBGSTAT_RANK1_REFRESH_BUSY_MASK (0x2U)
#define DDRCTL_DBGSTAT_RANK1_REFRESH_BUSY_SHIFT (1U)
#define DDRCTL_DBGSTAT_RANK1_REFRESH_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_DBGSTAT_RANK1_REFRESH_BUSY_MASK) >> DDRCTL_DBGSTAT_RANK1_REFRESH_BUSY_SHIFT)

/*
 * RANK0_REFRESH_BUSY (R)
 *
 * Description: SoC core may initiate a rank0_refresh operation (refresh operation to rank 0) only if this signal is low. This signal goes high in the clock after DBGCMD.rank0_refresh is set to one. It goes low when the rank0_refresh operation is stored in uMCTL2. It is recommended not to perform rank0_refresh operations when this signal is high.
 * 0 - Indicates that the SoC core can initiate a rank0_refresh operation
 * 1 - Indicates that rank0_refresh operation has not been stored yet in uMCTL2
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_DBGSTAT_RANK0_REFRESH_BUSY_MASK (0x1U)
#define DDRCTL_DBGSTAT_RANK0_REFRESH_BUSY_SHIFT (0U)
#define DDRCTL_DBGSTAT_RANK0_REFRESH_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_DBGSTAT_RANK0_REFRESH_BUSY_MASK) >> DDRCTL_DBGSTAT_RANK0_REFRESH_BUSY_SHIFT)

/* Bitfield definition for register: PSTAT */
/*
 * WR_PORT_BUSY_15 (R)
 *
 * Description: Indicates if there are outstanding writes for port 15.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_15==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_15_MASK (0x80000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_15_SHIFT (31U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_15_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_15_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_15_SHIFT)

/*
 * WR_PORT_BUSY_14 (R)
 *
 * Description: Indicates if there are outstanding writes for port 14.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_14==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_14_MASK (0x40000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_14_SHIFT (30U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_14_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_14_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_14_SHIFT)

/*
 * WR_PORT_BUSY_13 (R)
 *
 * Description: Indicates if there are outstanding writes for port 13.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_13==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_13_MASK (0x20000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_13_SHIFT (29U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_13_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_13_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_13_SHIFT)

/*
 * WR_PORT_BUSY_12 (R)
 *
 * Description: Indicates if there are outstanding writes for port 12.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_12==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_12_MASK (0x10000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_12_SHIFT (28U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_12_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_12_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_12_SHIFT)

/*
 * WR_PORT_BUSY_11 (R)
 *
 * Description: Indicates if there are outstanding writes for port 11.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_11==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_11_MASK (0x8000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_11_SHIFT (27U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_11_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_11_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_11_SHIFT)

/*
 * WR_PORT_BUSY_10 (R)
 *
 * Description: Indicates if there are outstanding writes for port 10.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_10==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_10_MASK (0x4000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_10_SHIFT (26U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_10_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_10_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_10_SHIFT)

/*
 * WR_PORT_BUSY_9 (R)
 *
 * Description: Indicates if there are outstanding writes for port 9.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_9==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_9_MASK (0x2000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_9_SHIFT (25U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_9_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_9_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_9_SHIFT)

/*
 * WR_PORT_BUSY_8 (R)
 *
 * Description: Indicates if there are outstanding writes for port 8.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_8==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_8_MASK (0x1000000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_8_SHIFT (24U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_8_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_8_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_8_SHIFT)

/*
 * WR_PORT_BUSY_7 (R)
 *
 * Description: Indicates if there are outstanding writes for port 7.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_7==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_7_MASK (0x800000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_7_SHIFT (23U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_7_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_7_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_7_SHIFT)

/*
 * WR_PORT_BUSY_6 (R)
 *
 * Description: Indicates if there are outstanding writes for port 6.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_6==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_6_MASK (0x400000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_6_SHIFT (22U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_6_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_6_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_6_SHIFT)

/*
 * WR_PORT_BUSY_5 (R)
 *
 * Description: Indicates if there are outstanding writes for port 5.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_5==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_5_MASK (0x200000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_5_SHIFT (21U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_5_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_5_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_5_SHIFT)

/*
 * WR_PORT_BUSY_4 (R)
 *
 * Description: Indicates if there are outstanding writes for port 4.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_4==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_4_MASK (0x100000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_4_SHIFT (20U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_4_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_4_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_4_SHIFT)

/*
 * WR_PORT_BUSY_3 (R)
 *
 * Description: Indicates if there are outstanding writes for port 3.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_3==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_3_MASK (0x80000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_3_SHIFT (19U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_3_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_3_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_3_SHIFT)

/*
 * WR_PORT_BUSY_2 (R)
 *
 * Description: Indicates if there are outstanding writes for port 2.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_2==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_2_MASK (0x40000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_2_SHIFT (18U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_2_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_2_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_2_SHIFT)

/*
 * WR_PORT_BUSY_1 (R)
 *
 * Description: Indicates if there are outstanding writes for port 1.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_1==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_1_MASK (0x20000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_1_SHIFT (17U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_1_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_1_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_1_SHIFT)

/*
 * WR_PORT_BUSY_0 (R)
 *
 * Description: Indicates if there are outstanding writes for port 0.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_0==1
 */
#define DDRCTL_PSTAT_WR_PORT_BUSY_0_MASK (0x10000UL)
#define DDRCTL_PSTAT_WR_PORT_BUSY_0_SHIFT (16U)
#define DDRCTL_PSTAT_WR_PORT_BUSY_0_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_WR_PORT_BUSY_0_MASK) >> DDRCTL_PSTAT_WR_PORT_BUSY_0_SHIFT)

/*
 * RD_PORT_BUSY_15 (R)
 *
 * Description: Indicates if there are outstanding reads for port 15.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_15==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_15_MASK (0x8000U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_15_SHIFT (15U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_15_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_15_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_15_SHIFT)

/*
 * RD_PORT_BUSY_14 (R)
 *
 * Description: Indicates if there are outstanding reads for port 14.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_14==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_14_MASK (0x4000U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_14_SHIFT (14U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_14_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_14_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_14_SHIFT)

/*
 * RD_PORT_BUSY_13 (R)
 *
 * Description: Indicates if there are outstanding reads for port 13.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_13==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_13_MASK (0x2000U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_13_SHIFT (13U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_13_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_13_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_13_SHIFT)

/*
 * RD_PORT_BUSY_12 (R)
 *
 * Description: Indicates if there are outstanding reads for port 12.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_12==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_12_MASK (0x1000U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_12_SHIFT (12U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_12_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_12_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_12_SHIFT)

/*
 * RD_PORT_BUSY_11 (R)
 *
 * Description: Indicates if there are outstanding reads for port 11.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_11==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_11_MASK (0x800U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_11_SHIFT (11U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_11_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_11_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_11_SHIFT)

/*
 * RD_PORT_BUSY_10 (R)
 *
 * Description: Indicates if there are outstanding reads for port 10.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_10==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_10_MASK (0x400U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_10_SHIFT (10U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_10_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_10_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_10_SHIFT)

/*
 * RD_PORT_BUSY_9 (R)
 *
 * Description: Indicates if there are outstanding reads for port 9.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_9==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_9_MASK (0x200U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_9_SHIFT (9U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_9_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_9_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_9_SHIFT)

/*
 * RD_PORT_BUSY_8 (R)
 *
 * Description: Indicates if there are outstanding reads for port 8.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_8==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_8_MASK (0x100U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_8_SHIFT (8U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_8_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_8_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_8_SHIFT)

/*
 * RD_PORT_BUSY_7 (R)
 *
 * Description: Indicates if there are outstanding reads for port 7.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_7==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_7_MASK (0x80U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_7_SHIFT (7U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_7_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_7_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_7_SHIFT)

/*
 * RD_PORT_BUSY_6 (R)
 *
 * Description: Indicates if there are outstanding reads for port 6.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_6==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_6_MASK (0x40U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_6_SHIFT (6U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_6_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_6_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_6_SHIFT)

/*
 * RD_PORT_BUSY_5 (R)
 *
 * Description: Indicates if there are outstanding reads for port 5.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_5==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_5_MASK (0x20U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_5_SHIFT (5U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_5_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_5_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_5_SHIFT)

/*
 * RD_PORT_BUSY_4 (R)
 *
 * Description: Indicates if there are outstanding reads for port 4.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_4==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_4_MASK (0x10U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_4_SHIFT (4U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_4_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_4_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_4_SHIFT)

/*
 * RD_PORT_BUSY_3 (R)
 *
 * Description: Indicates if there are outstanding reads for port 3.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_3==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_3_MASK (0x8U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_3_SHIFT (3U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_3_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_3_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_3_SHIFT)

/*
 * RD_PORT_BUSY_2 (R)
 *
 * Description: Indicates if there are outstanding reads for port 2.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_2==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_2_MASK (0x4U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_2_SHIFT (2U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_2_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_2_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_2_SHIFT)

/*
 * RD_PORT_BUSY_1 (R)
 *
 * Description: Indicates if there are outstanding reads for port 1.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_1==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_1_MASK (0x2U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_1_SHIFT (1U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_1_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_1_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_1_SHIFT)

/*
 * RD_PORT_BUSY_0 (R)
 *
 * Description: Indicates if there are outstanding reads for port 0.
 * Value After Reset: 0x0
 * Exists: UMCTL2_PORT_0==1
 */
#define DDRCTL_PSTAT_RD_PORT_BUSY_0_MASK (0x1U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_0_SHIFT (0U)
#define DDRCTL_PSTAT_RD_PORT_BUSY_0_GET(x) (((uint32_t)(x) & DDRCTL_PSTAT_RD_PORT_BUSY_0_MASK) >> DDRCTL_PSTAT_RD_PORT_BUSY_0_SHIFT)

/* Bitfield definition for register: PCCFG */
/*
 * PAGEMATCH_LIMIT (R/W)
 *
 * Description: Page match four limit. If set to 1, limits the number of consecutive same page DDRC transactions that can be granted by the Port Arbiter to four when Page Match feature is enabled.	If set to 0, there is no limit imposed on number of consecutive same page DDRC transactions.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCCFG_PAGEMATCH_LIMIT_MASK (0x10U)
#define DDRCTL_PCCFG_PAGEMATCH_LIMIT_SHIFT (4U)
#define DDRCTL_PCCFG_PAGEMATCH_LIMIT_SET(x) (((uint32_t)(x) << DDRCTL_PCCFG_PAGEMATCH_LIMIT_SHIFT) & DDRCTL_PCCFG_PAGEMATCH_LIMIT_MASK)
#define DDRCTL_PCCFG_PAGEMATCH_LIMIT_GET(x) (((uint32_t)(x) & DDRCTL_PCCFG_PAGEMATCH_LIMIT_MASK) >> DDRCTL_PCCFG_PAGEMATCH_LIMIT_SHIFT)

/*
 * GO2CRITICAL_EN (R/W)
 *
 * Description: If set to 1 (enabled), sets co_gs_go2critical_wr and co_gs_go2critical_rd signals going to DDRC based on urgent input (awurgent, arurgent) coming from AXI master. If set to 0 (disabled), co_gs_go2critical_wr and co_gs_go2critical_rd signals at DDRC are driven to 1b'0.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCCFG_GO2CRITICAL_EN_MASK (0x1U)
#define DDRCTL_PCCFG_GO2CRITICAL_EN_SHIFT (0U)
#define DDRCTL_PCCFG_GO2CRITICAL_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCCFG_GO2CRITICAL_EN_SHIFT) & DDRCTL_PCCFG_GO2CRITICAL_EN_MASK)
#define DDRCTL_PCCFG_GO2CRITICAL_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCCFG_GO2CRITICAL_EN_MASK) >> DDRCTL_PCCFG_GO2CRITICAL_EN_SHIFT)

/* Bitfield definition for register of struct array PCFG: R */
/*
 * RD_PORT_PAGEMATCH_EN (R/W)
 *
 * Description: If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (i.e. same bank and same row). See also related PCCFG.pagematch_limit register.
 * Value After Reset: "(MEMC_DDR4_EN==1) ? 0x0 : 0x1"
 * Exists: Always
 */
#define DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_MASK (0x4000U)
#define DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_SHIFT (14U)
#define DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_SHIFT) & DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_MASK)
#define DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_MASK) >> DDRCTL_PCFG_R_RD_PORT_PAGEMATCH_EN_SHIFT)

/*
 * RD_PORT_URGENT_EN (R/W)
 *
 * Description: If set to 1, enables the AXI urgent sideband signal (arurgent). When enabled and arurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_rd signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that arurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_R_RD_PORT_URGENT_EN_MASK (0x2000U)
#define DDRCTL_PCFG_R_RD_PORT_URGENT_EN_SHIFT (13U)
#define DDRCTL_PCFG_R_RD_PORT_URGENT_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_R_RD_PORT_URGENT_EN_SHIFT) & DDRCTL_PCFG_R_RD_PORT_URGENT_EN_MASK)
#define DDRCTL_PCFG_R_RD_PORT_URGENT_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_R_RD_PORT_URGENT_EN_MASK) >> DDRCTL_PCFG_R_RD_PORT_URGENT_EN_SHIFT)

/*
 * RD_PORT_AGING_EN (R/W)
 *
 * Description: If set to 1, enables aging function for the read channel of the port.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_R_RD_PORT_AGING_EN_MASK (0x1000U)
#define DDRCTL_PCFG_R_RD_PORT_AGING_EN_SHIFT (12U)
#define DDRCTL_PCFG_R_RD_PORT_AGING_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_R_RD_PORT_AGING_EN_SHIFT) & DDRCTL_PCFG_R_RD_PORT_AGING_EN_MASK)
#define DDRCTL_PCFG_R_RD_PORT_AGING_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_R_RD_PORT_AGING_EN_MASK) >> DDRCTL_PCFG_R_RD_PORT_AGING_EN_SHIFT)

/*
 * RD_PORT_PRIORITY (R/W)
 *
 * Description: Determines the initial load value of read aging counters. These counters will be parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the read aging counter sets the priority of the	read channel of a given port. Port's priority will increase as the higher significant 5-bits of the counter starts to decrease.
 * When the aging counter becomes 0, the corresponding port channel will have the highest priority level (timeout condition
 * - Priority0). For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (arqos) are enabled (timeout is still applicable). For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. In this case, external dynamic priority input, arqos (for reads only) can still be used to set the DDRC read priority (2 priority levels: low priority read - LPR, high priority read - HPR) on a command by command basis. Note: The two LSBs of this register field are tied internally to 2'b00.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_R_RD_PORT_PRIORITY_MASK (0x3FFU)
#define DDRCTL_PCFG_R_RD_PORT_PRIORITY_SHIFT (0U)
#define DDRCTL_PCFG_R_RD_PORT_PRIORITY_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_R_RD_PORT_PRIORITY_SHIFT) & DDRCTL_PCFG_R_RD_PORT_PRIORITY_MASK)
#define DDRCTL_PCFG_R_RD_PORT_PRIORITY_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_R_RD_PORT_PRIORITY_MASK) >> DDRCTL_PCFG_R_RD_PORT_PRIORITY_SHIFT)

/* Bitfield definition for register of struct array PCFG: W */
/*
 * WR_PORT_PAGEMATCH_EN (R/W)
 *
 * Description: If set to 1, enables the Page Match feature. If enabled, once a requesting port is granted, the port is continued to be granted if the following immediate commands are to the same memory page (i.e. same bank and same row). See also related PCCFG.pagematch_limit register.
 * Value After Reset: 0x1
 * Exists: Always
 */
#define DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_MASK (0x4000U)
#define DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_SHIFT (14U)
#define DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_SHIFT) & DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_MASK)
#define DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_MASK) >> DDRCTL_PCFG_W_WR_PORT_PAGEMATCH_EN_SHIFT)

/*
 * WR_PORT_URGENT_EN (R/W)
 *
 * Description: If set to 1, enables the AXI urgent sideband signal (awurgent). When enabled and awurgent is asserted by the master, that port becomes the highest priority and co_gs_go2critical_wr signal to DDRC is asserted if enabled in PCCFG.go2critical_en register. Note that awurgent signal can be asserted anytime and as long as required which is independent of address handshaking (it is not associated with any particular command).
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_W_WR_PORT_URGENT_EN_MASK (0x2000U)
#define DDRCTL_PCFG_W_WR_PORT_URGENT_EN_SHIFT (13U)
#define DDRCTL_PCFG_W_WR_PORT_URGENT_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_W_WR_PORT_URGENT_EN_SHIFT) & DDRCTL_PCFG_W_WR_PORT_URGENT_EN_MASK)
#define DDRCTL_PCFG_W_WR_PORT_URGENT_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_W_WR_PORT_URGENT_EN_MASK) >> DDRCTL_PCFG_W_WR_PORT_URGENT_EN_SHIFT)

/*
 * WR_PORT_AGING_EN (R/W)
 *
 * Description: If set to 1, enables aging function for the write channel of the port.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_W_WR_PORT_AGING_EN_MASK (0x1000U)
#define DDRCTL_PCFG_W_WR_PORT_AGING_EN_SHIFT (12U)
#define DDRCTL_PCFG_W_WR_PORT_AGING_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_W_WR_PORT_AGING_EN_SHIFT) & DDRCTL_PCFG_W_WR_PORT_AGING_EN_MASK)
#define DDRCTL_PCFG_W_WR_PORT_AGING_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_W_WR_PORT_AGING_EN_MASK) >> DDRCTL_PCFG_W_WR_PORT_AGING_EN_SHIFT)

/*
 * WR_PORT_PRIORITY (R/W)
 *
 * Description: Determines the initial load value of write aging counters. These counters will be parallel loaded after reset, or after each grant to the corresponding port. The aging counters down-count every clock cycle where the port is requesting but not granted. The higher significant 5-bits of the write aging counter sets the initial priority of the
 * write channel of a given port. Port's priority will increase as the higher significant 5-bits of the counter starts to decrease. When the aging counter becomes 0, the corresponding port channel will have the highest priority level. For multi-port configurations, the aging counters cannot be used to set port priorities when external dynamic priority inputs (awqos) are enabled (timeout is still applicable). For single port configurations, the aging counters are only used when they timeout (become 0) to force read-write direction switching. Note: The two LSBs of this register field are tied internally to 2'b00.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_W_WR_PORT_PRIORITY_MASK (0x3FFU)
#define DDRCTL_PCFG_W_WR_PORT_PRIORITY_SHIFT (0U)
#define DDRCTL_PCFG_W_WR_PORT_PRIORITY_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_W_WR_PORT_PRIORITY_SHIFT) & DDRCTL_PCFG_W_WR_PORT_PRIORITY_MASK)
#define DDRCTL_PCFG_W_WR_PORT_PRIORITY_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_W_WR_PORT_PRIORITY_MASK) >> DDRCTL_PCFG_W_WR_PORT_PRIORITY_SHIFT)

/* Bitfield definition for register of struct array PCFG: C */
/*
 * AHB_ENDIANNESS (R/W)
 *
 * Description: If set to 0, enables support for little endian on the AHB port. If set to 1, enables support for big endian (BE- 32) on the AHB port. If set to 2, enables support for big endian (BE-A) on the AHB port.
 * Value After Reset: 0x0
 * Exists: UMCTL2_A_AHB_n==1
 */
#define DDRCTL_PCFG_C_AHB_ENDIANNESS_MASK (0x3U)
#define DDRCTL_PCFG_C_AHB_ENDIANNESS_SHIFT (0U)
#define DDRCTL_PCFG_C_AHB_ENDIANNESS_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_C_AHB_ENDIANNESS_SHIFT) & DDRCTL_PCFG_C_AHB_ENDIANNESS_MASK)
#define DDRCTL_PCFG_C_AHB_ENDIANNESS_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_C_AHB_ENDIANNESS_MASK) >> DDRCTL_PCFG_C_AHB_ENDIANNESS_SHIFT)

/* Bitfield definition for register of struct array PCFG: MASKCH */
/*
 * ID_MASK (R/W)
 *
 * Description: Determines the mask used in the ID mapping function for virtual channel m.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_ID_MASKCH_ID_MASK_MASK (0xFFFFFFFFUL)
#define DDRCTL_PCFG_ID_MASKCH_ID_MASK_SHIFT (0U)
#define DDRCTL_PCFG_ID_MASKCH_ID_MASK_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_ID_MASKCH_ID_MASK_SHIFT) & DDRCTL_PCFG_ID_MASKCH_ID_MASK_MASK)
#define DDRCTL_PCFG_ID_MASKCH_ID_MASK_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_ID_MASKCH_ID_MASK_MASK) >> DDRCTL_PCFG_ID_MASKCH_ID_MASK_SHIFT)

/* Bitfield definition for register of struct array PCFG: VALUECH */
/*
 * ID_VALUE (R/W)
 *
 * Description: Determines the value used in the ID mapping function for virtual channel m.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_ID_VALUECH_ID_VALUE_MASK (0xFFFFFFFFUL)
#define DDRCTL_PCFG_ID_VALUECH_ID_VALUE_SHIFT (0U)
#define DDRCTL_PCFG_ID_VALUECH_ID_VALUE_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_ID_VALUECH_ID_VALUE_SHIFT) & DDRCTL_PCFG_ID_VALUECH_ID_VALUE_MASK)
#define DDRCTL_PCFG_ID_VALUECH_ID_VALUE_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_ID_VALUECH_ID_VALUE_MASK) >> DDRCTL_PCFG_ID_VALUECH_ID_VALUE_SHIFT)

/* Bitfield definition for register of struct array PCFG: CTRL */
/*
 * PORT_EN (R/W)
 *
 * Description: Enables port n.
 * Value After Reset: "UMCTL2_PORT_EN_RESET_VALUE"
 * Exists: Always
 */
#define DDRCTL_PCFG_CTRL_PORT_EN_MASK (0x1U)
#define DDRCTL_PCFG_CTRL_PORT_EN_SHIFT (0U)
#define DDRCTL_PCFG_CTRL_PORT_EN_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_CTRL_PORT_EN_SHIFT) & DDRCTL_PCFG_CTRL_PORT_EN_MASK)
#define DDRCTL_PCFG_CTRL_PORT_EN_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_CTRL_PORT_EN_MASK) >> DDRCTL_PCFG_CTRL_PORT_EN_SHIFT)

/* Bitfield definition for register of struct array PCFG: QOS0 */
/*
 * RQOS_MAP_REGION1 (R/W)
 *
 * Description: This bitfield indicates the traffic class of region
 * 1.	Valid values are:	0: LPR, 1: VPR, 2: HPR. For dual address queue configurations, region1 maps to the blue address queue. In this case, valid values are 0: LPR and 1: VPR only.	When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region 1 is set to 1 (VPR) then VPR traffic is aliased to LPR traffic.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_MASK (0x300000UL)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_SHIFT (20U)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_SHIFT) & DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_MASK)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_MASK) >> DDRCTL_PCFG_QOS0_RQOS_MAP_REGION1_SHIFT)

/*
 * RQOS_MAP_REGION0 (R/W)
 *
 * Description: This bitfield indicates the traffic class of region
 * 0. Valid values are: 0: LPR, 1: VPR, 2: HPR. For dual address queue configurations, region 0 maps to the blue address queue. In this case, valid values are 0: LPR and 1: VPR only.	When VPR support is disabled (UMCTL2_VPR_EN = 0) and traffic class of region0 is set to 1 (VPR) then VPR traffic is aliased to LPR traffic.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_MASK (0x30000UL)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_SHIFT (16U)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_SHIFT) & DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_MASK)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_MASK) >> DDRCTL_PCFG_QOS0_RQOS_MAP_REGION0_SHIFT)

/*
 * RQOS_MAP_LEVEL1 (R/W)
 *
 * Description: Separation level1 indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 13(for dual RAQ) or 0 to 14(for single RAQ) which corresponds to arqos.	Note that for PA, arqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.	All of the map_level* registers must be set to distinct values.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_MASK (0xFU)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_SHIFT (0U)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_SHIFT) & DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_MASK)
#define DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_MASK) >> DDRCTL_PCFG_QOS0_RQOS_MAP_LEVEL1_SHIFT)

/* Bitfield definition for register of struct array PCFG: QOS1 */
/*
 * RQOS_MAP_TIMEOUTR (R/W)
 *
 * Description: Specifies the timeout value for transactions mapped to the red address queue.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_MASK (0x7FF0000UL)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_SHIFT (16U)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_SHIFT) & DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_MASK)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_MASK) >> DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTR_SHIFT)

/*
 * RQOS_MAP_TIMEOUTB (R/W)
 *
 * Description: Specifies the timeout value for transactions mapped to the blue address queue.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_MASK (0x7FFU)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_SHIFT (0U)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_SHIFT) & DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_MASK)
#define DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_MASK) >> DDRCTL_PCFG_QOS1_RQOS_MAP_TIMEOUTB_SHIFT)

/* Bitfield definition for register of struct array PCFG: WQOS0 */
/*
 * WQOS_MAP_REGION1 (R/W)
 *
 * Description: This bitfield indicates the traffic class of region
 * 1. Valid values are:
 * 0: NPW
 * 1: VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region 1 is set to 1 (VPW) then VPW traffic is aliased to NPW traffic.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_MASK (0x300000UL)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_SHIFT (20U)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_SHIFT) & DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_MASK)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_MASK) >> DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION1_SHIFT)

/*
 * WQOS_MAP_REGION0 (R/W)
 *
 * Description: This bitfield indicates the traffic class of region
 * 0. Valid values are:
 * 0: NPW
 * 1: VPW
 * When VPW support is disabled (UMCTL2_VPW_EN = 0) and traffic class of region0 is set to 1 (VPW) then VPW traffic is aliased to NPW traffic.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_MASK (0x30000UL)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_SHIFT (16U)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_SHIFT) & DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_MASK)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_MASK) >> DDRCTL_PCFG_WQOS0_WQOS_MAP_REGION0_SHIFT)

/*
 * WQOS_MAP_LEVEL (R/W)
 *
 * Description: Separation level indicating the end of region0 mapping; start of region0 is 0. Possible values for level1 are 0 to 14 which corresponds to awqos.	Note that for PA, awqos values are used directly as port priorities, where the higher the value corresponds to higher port priority.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_MASK (0xFU)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_SHIFT (0U)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_SHIFT) & DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_MASK)
#define DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_MASK) >> DDRCTL_PCFG_WQOS0_WQOS_MAP_LEVEL_SHIFT)

/* Bitfield definition for register of struct array PCFG: WQOS1 */
/*
 * WQOS_MAP_TIMEOUT (R/W)
 *
 * Description: Specifies the timeout value for write transactions.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_MASK (0x7FFU)
#define DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_SHIFT (0U)
#define DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_SET(x) (((uint32_t)(x) << DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_SHIFT) & DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_MASK)
#define DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_GET(x) (((uint32_t)(x) & DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_MASK) >> DDRCTL_PCFG_WQOS1_WQOS_MAP_TIMEOUT_SHIFT)

/* Bitfield definition for register of struct array SAR: BASE */
/*
 * BASE_ADDR (R/W)
 *
 * Description: Base address for address region n specified as awaddr[UMCTL2_A_ADDRW-1:x] and araddr[UMCTL2_A_ADDRW-1:x] where x is determined by the minimum block size parameter UMCTL2_SARMINSIZE: (x=log2(block size)).
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_SAR_BASE_BASE_ADDR_MASK (0xFFFFFFFFUL)
#define DDRCTL_SAR_BASE_BASE_ADDR_SHIFT (0U)
#define DDRCTL_SAR_BASE_BASE_ADDR_SET(x) (((uint32_t)(x) << DDRCTL_SAR_BASE_BASE_ADDR_SHIFT) & DDRCTL_SAR_BASE_BASE_ADDR_MASK)
#define DDRCTL_SAR_BASE_BASE_ADDR_GET(x) (((uint32_t)(x) & DDRCTL_SAR_BASE_BASE_ADDR_MASK) >> DDRCTL_SAR_BASE_BASE_ADDR_SHIFT)

/* Bitfield definition for register of struct array SAR: SIZE */
/*
 * NBLOCKS (R/W)
 *
 * Description: Number of blocks for address region n. This register determines the total size of the region in multiples of minimum block size as specified by the hardware parameter UMCTL2_SARMINSIZE. The register value is encoded as number of blocks = nblocks + 1.
 * Value After Reset: 0x0
 * Exists: Always
 */
#define DDRCTL_SAR_SIZE_NBLOCKS_MASK (0xFFU)
#define DDRCTL_SAR_SIZE_NBLOCKS_SHIFT (0U)
#define DDRCTL_SAR_SIZE_NBLOCKS_SET(x) (((uint32_t)(x) << DDRCTL_SAR_SIZE_NBLOCKS_SHIFT) & DDRCTL_SAR_SIZE_NBLOCKS_MASK)
#define DDRCTL_SAR_SIZE_NBLOCKS_GET(x) (((uint32_t)(x) & DDRCTL_SAR_SIZE_NBLOCKS_MASK) >> DDRCTL_SAR_SIZE_NBLOCKS_SHIFT)

/* Bitfield definition for register: SBRCTL */
/*
 * SCRUB_INTERVAL (R/W)
 *
 * Description: Scrub interval. (512 x scrub_interval) number of clock cycles between two scrub read commands. If set to 0,	scrub commands are issued back-to-back. This mode of operation (scrub_interval=0) can typically be used for scrubbing the full range of memory at once	before or after SW controlled low power operations. After completing the full range of scrub while scrub_interval=0, scrub_done register is set and	sbr_done_intr interrupt signal is asserted.
 * Value After Reset: 0xff
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRCTL_SCRUB_INTERVAL_MASK (0x1FFF00UL)
#define DDRCTL_SBRCTL_SCRUB_INTERVAL_SHIFT (8U)
#define DDRCTL_SBRCTL_SCRUB_INTERVAL_SET(x) (((uint32_t)(x) << DDRCTL_SBRCTL_SCRUB_INTERVAL_SHIFT) & DDRCTL_SBRCTL_SCRUB_INTERVAL_MASK)
#define DDRCTL_SBRCTL_SCRUB_INTERVAL_GET(x) (((uint32_t)(x) & DDRCTL_SBRCTL_SCRUB_INTERVAL_MASK) >> DDRCTL_SBRCTL_SCRUB_INTERVAL_SHIFT)

/*
 * SCRUB_BURST (R/W)
 *
 * Description: Scrub burst count. Determines the number of back-to-back scrub read commands that can be issued together		when the controller is in one of the HW controlled low power modes. During low power, the period of the scrub burst	becomes \"scrub_burst*scrub_interval\" cycles.
 * During normal operation mode of the controller (ie. not in power-down	or self refresh), scrub_burst is ignored and only one scrub command is generated.	Valid values are: 1: 1 read, 2: 4 reads, 3: 16 reads, 4: 64 reads, 5: 256 reads,
 * 6: 1024 reads.
 * Value After Reset: 0x1
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRCTL_SCRUB_BURST_MASK (0x70U)
#define DDRCTL_SBRCTL_SCRUB_BURST_SHIFT (4U)
#define DDRCTL_SBRCTL_SCRUB_BURST_SET(x) (((uint32_t)(x) << DDRCTL_SBRCTL_SCRUB_BURST_SHIFT) & DDRCTL_SBRCTL_SCRUB_BURST_MASK)
#define DDRCTL_SBRCTL_SCRUB_BURST_GET(x) (((uint32_t)(x) & DDRCTL_SBRCTL_SCRUB_BURST_MASK) >> DDRCTL_SBRCTL_SCRUB_BURST_SHIFT)

/*
 * SCRUB_MODE (R/W)
 *
 * Description: scrub_mode:0 ECC scrubber will perform reads	scrub_mode:1 ECC scrubber will perform writes Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRCTL_SCRUB_MODE_MASK (0x4U)
#define DDRCTL_SBRCTL_SCRUB_MODE_SHIFT (2U)
#define DDRCTL_SBRCTL_SCRUB_MODE_SET(x) (((uint32_t)(x) << DDRCTL_SBRCTL_SCRUB_MODE_SHIFT) & DDRCTL_SBRCTL_SCRUB_MODE_MASK)
#define DDRCTL_SBRCTL_SCRUB_MODE_GET(x) (((uint32_t)(x) & DDRCTL_SBRCTL_SCRUB_MODE_MASK) >> DDRCTL_SBRCTL_SCRUB_MODE_SHIFT)

/*
 * SCRUB_DURING_LOWPOWER (R/W)
 *
 * Description: Continue scrubbing during low power. If set to 1, burst of scrubs will be issued	in HW controlled low power modes. There are two such modes: automatically initiated		by idleness or initiated by HW low-power (LP) interface. If set to 0, the scrubber		will not attempt to send commands while the DDRC is in HW controlled low power modes.	In this case, the scrubber will remember the last address issued and will automatically continue	from there when the DDRC exits the LP mode.
 * Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_MASK (0x2U)
#define DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_SHIFT (1U)
#define DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_SET(x) (((uint32_t)(x) << DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_SHIFT) & DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_MASK)
#define DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_GET(x) (((uint32_t)(x) & DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_MASK) >> DDRCTL_SBRCTL_SCRUB_DURING_LOWPOWER_SHIFT)

/*
 * SCRUB_EN (R/W)
 *
 * Description: Enable ECC scrubber. If set to 1, enables the scrubber to generate background	read commands after the memories are initialized. If set to 0, disables the scrubber, resets the address generator to 0	and clears the scrubber status. This bitfield must be accessed separately from the other bitfields in this register.
 * Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRCTL_SCRUB_EN_MASK (0x1U)
#define DDRCTL_SBRCTL_SCRUB_EN_SHIFT (0U)
#define DDRCTL_SBRCTL_SCRUB_EN_SET(x) (((uint32_t)(x) << DDRCTL_SBRCTL_SCRUB_EN_SHIFT) & DDRCTL_SBRCTL_SCRUB_EN_MASK)
#define DDRCTL_SBRCTL_SCRUB_EN_GET(x) (((uint32_t)(x) & DDRCTL_SBRCTL_SCRUB_EN_MASK) >> DDRCTL_SBRCTL_SCRUB_EN_SHIFT)

/* Bitfield definition for register: SBRSTAT */
/*
 * SCRUB_DONE (R)
 *
 * Description: Scrubber done. Controller sets this bit to 1, after full range of addresses are scrubbed once while scrub_interval is set to 0.	Cleared if scrub_en is set to 0 (scrubber disabled) or scrub_interval is set to a non-zero value for normal scrub operation.	The interrupt signal, sbr_done_intr, is equivalent to this status bitfield.
 * Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRSTAT_SCRUB_DONE_MASK (0x2U)
#define DDRCTL_SBRSTAT_SCRUB_DONE_SHIFT (1U)
#define DDRCTL_SBRSTAT_SCRUB_DONE_GET(x) (((uint32_t)(x) & DDRCTL_SBRSTAT_SCRUB_DONE_MASK) >> DDRCTL_SBRSTAT_SCRUB_DONE_SHIFT)

/*
 * SCRUB_BUSY (R)
 *
 * Description: Scrubber busy. Controller sets this bit to 1 when the scrubber logic has outstanding read commands being executed.	Cleared when there are no active outstanding scrub reads in the system.
 * Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRSTAT_SCRUB_BUSY_MASK (0x1U)
#define DDRCTL_SBRSTAT_SCRUB_BUSY_SHIFT (0U)
#define DDRCTL_SBRSTAT_SCRUB_BUSY_GET(x) (((uint32_t)(x) & DDRCTL_SBRSTAT_SCRUB_BUSY_MASK) >> DDRCTL_SBRSTAT_SCRUB_BUSY_SHIFT)

/* Bitfield definition for register: SBRWDATA0 */
/*
 * SCRUB_PATTERN0 (R/W)
 *
 * Description: ECC Scrubber write data pattern for data bus[31:0]
 * Value After Reset: 0x0
 * Exists: UMCTL2_SBR_EN_1==1
 */
#define DDRCTL_SBRWDATA0_SCRUB_PATTERN0_MASK (0xFFFFFFFFUL)
#define DDRCTL_SBRWDATA0_SCRUB_PATTERN0_SHIFT (0U)
#define DDRCTL_SBRWDATA0_SCRUB_PATTERN0_SET(x) (((uint32_t)(x) << DDRCTL_SBRWDATA0_SCRUB_PATTERN0_SHIFT) & DDRCTL_SBRWDATA0_SCRUB_PATTERN0_MASK)
#define DDRCTL_SBRWDATA0_SCRUB_PATTERN0_GET(x) (((uint32_t)(x) & DDRCTL_SBRWDATA0_SCRUB_PATTERN0_MASK) >> DDRCTL_SBRWDATA0_SCRUB_PATTERN0_SHIFT)



/* ID register group index macro definition */
#define DDRCTL_ID_0 (0UL)
#define DDRCTL_ID_1 (1UL)
#define DDRCTL_ID_2 (2UL)
#define DDRCTL_ID_3 (3UL)
#define DDRCTL_ID_4 (4UL)
#define DDRCTL_ID_5 (5UL)
#define DDRCTL_ID_6 (6UL)
#define DDRCTL_ID_7 (7UL)
#define DDRCTL_ID_8 (8UL)
#define DDRCTL_ID_9 (9UL)
#define DDRCTL_ID_10 (10UL)
#define DDRCTL_ID_11 (11UL)
#define DDRCTL_ID_12 (12UL)
#define DDRCTL_ID_13 (13UL)
#define DDRCTL_ID_14 (14UL)
#define DDRCTL_ID_15 (15UL)

/* PCFG register group index macro definition */
#define DDRCTL_PCFG_0 (0UL)
#define DDRCTL_PCFG_1 (1UL)
#define DDRCTL_PCFG_2 (2UL)
#define DDRCTL_PCFG_3 (3UL)
#define DDRCTL_PCFG_4 (4UL)
#define DDRCTL_PCFG_5 (5UL)
#define DDRCTL_PCFG_6 (6UL)
#define DDRCTL_PCFG_7 (7UL)
#define DDRCTL_PCFG_8 (8UL)
#define DDRCTL_PCFG_9 (9UL)
#define DDRCTL_PCFG_10 (10UL)
#define DDRCTL_PCFG_11 (11UL)
#define DDRCTL_PCFG_12 (12UL)
#define DDRCTL_PCFG_13 (13UL)
#define DDRCTL_PCFG_14 (14UL)
#define DDRCTL_PCFG_15 (15UL)

/* SAR register group index macro definition */
#define DDRCTL_SAR_0 (0UL)
#define DDRCTL_SAR_1 (1UL)
#define DDRCTL_SAR_2 (2UL)
#define DDRCTL_SAR_3 (3UL)


#endif /* HPM_DDRCTL_H */

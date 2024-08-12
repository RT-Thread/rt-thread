/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ESC_H
#define HPM_ESC_H

typedef struct {
    __R  uint8_t  TYPE;                        /* 0x0: Type of EtherCAT controller */
    __R  uint8_t  REVISION;                    /* 0x1: Revision of EtherCAT controller */
    __R  uint16_t BUILD;                       /* 0x2: Build of EtherCAT controller */
    __R  uint8_t  FMMU_NUM;                    /* 0x4: FMMU supported */
    __R  uint8_t  SYNCM_NUM;                   /* 0x5: SyncManagers supported */
    __R  uint8_t  RAM_SIZE;                    /* 0x6: RAM Size */
    __R  uint8_t  PORT_DESC;                   /* 0x7: Port Descriptor */
    __R  uint16_t FEATURE;                     /* 0x8: ESC Feature supported */
    __R  uint8_t  RESERVED0[6];                /* 0xA - 0xF: Reserved */
    __R  uint16_t STATION_ADDR;                /* 0x10: Configured Station Address */
    __RW uint16_t STATION_ALS;                 /* 0x12: Configured Station Alias */
    __R  uint8_t  RESERVED1[12];               /* 0x14 - 0x1F: Reserved */
    __R  uint8_t  REG_WEN;                     /* 0x20: Register Write Enable */
    __R  uint8_t  REG_WP;                      /* 0x21: Register Write Protection */
    __R  uint8_t  RESERVED2[14];               /* 0x22 - 0x2F: Reserved */
    __R  uint8_t  ESC_WEN;                     /* 0x30: ESC Write Enable */
    __R  uint8_t  ESC_WP;                      /* 0x31: ESC Write Protection */
    __R  uint8_t  RESERVED3[14];               /* 0x32 - 0x3F: Reserved */
    __R  uint8_t  ESC_RST_ECAT;                /* 0x40: ESC Reset ECAT */
    __RW uint8_t  ESC_RST_PDI;                 /* 0x41: ESC Reset PDI */
    __R  uint8_t  RESERVED4[190];              /* 0x42 - 0xFF: Reserved */
    __R  uint32_t ESC_DL_CTRL;                 /* 0x100: ESC DL Control */
    __R  uint8_t  RESERVED5[4];                /* 0x104 - 0x107: Reserved */
    __R  uint16_t PHYSICAL_RW_OFFSET;          /* 0x108: Physical Read/Write Offset */
    __R  uint8_t  RESERVED6[6];                /* 0x10A - 0x10F: Reserved */
    __R  uint16_t ESC_DL_STAT;                 /* 0x110: ESC DL Status */
    __R  uint8_t  RESERVED7[14];               /* 0x112 - 0x11F: Reserved */
    __RW uint16_t AL_CTRL;                     /* 0x120: AL Control */
    __R  uint8_t  RESERVED8[14];               /* 0x122 - 0x12F: Reserved */
    __RW uint16_t AL_STAT;                     /* 0x130: AL Status */
    __R  uint8_t  RESERVED9[2];                /* 0x132 - 0x133: Reserved */
    __RW uint16_t AL_STAT_CODE;                /* 0x134: AL Status Code */
    __R  uint8_t  RESERVED10[2];               /* 0x136 - 0x137: Reserved */
    __RW uint8_t  RUN_LED_OVRD;                /* 0x138: RUN LED Override */
    __RW uint8_t  ERR_LED_OVRD;                /* 0x139: ERR LED Override */
    __R  uint8_t  RESERVED11[6];               /* 0x13A - 0x13F: Reserved */
    __R  uint8_t  PDI_CTRL;                    /* 0x140: PDI Control */
    __R  uint8_t  ESC_CFG;                     /* 0x141: ESC Configuration */
    __R  uint8_t  RESERVED12[12];              /* 0x142 - 0x14D: Reserved */
    __R  uint16_t PDI_INFO;                    /* 0x14E: PDI Information */
    __R  uint8_t  PDI_CFG;                     /* 0x150: PDI Configuration */
    __R  uint8_t  PDI_SL_CFG;                  /* 0x151: PDI Sync/Latch[1:0] Configuration */
    __RW uint16_t PDI_EXT_CFG;                 /* 0x152: PDI Extended Configuration */
    __R  uint8_t  RESERVED13[172];             /* 0x154 - 0x1FF: Reserved */
    __R  uint16_t ECAT_EVT_MSK;                /* 0x200: ECAT Event Mask */
    __R  uint8_t  RESERVED14[2];               /* 0x202 - 0x203: Reserved */
    __RW uint32_t PDI_AL_EVT_MSK;              /* 0x204: PDI AL Event Mask */
    __R  uint8_t  RESERVED15[8];               /* 0x208 - 0x20F: Reserved */
    __R  uint16_t ECAT_EVT_REQ;                /* 0x210: ECAT Event Request */
    __R  uint8_t  RESERVED16[14];              /* 0x212 - 0x21F: Reserved */
    __R  uint32_t AL_EVT_REQ;                  /* 0x220: AL Event Request */
    __R  uint8_t  RESERVED17[220];             /* 0x224 - 0x2FF: Reserved */
    __R  uint16_t RX_ERR_CNT[4];               /* 0x300 - 0x306: RX Error Counter */
    __R  uint8_t  FWD_RX_ERR_CNT[4];           /* 0x308 - 0x30B: Forwarded RX Error Counter */
    __R  uint8_t  ECAT_PU_ERR_CNT;             /* 0x30C: ECAT Processing Unit Error Counter */
    __R  uint8_t  PDI_ERR_CNT;                 /* 0x30D: PDI Error Counter */
    __R  uint8_t  RESERVED18[2];               /* 0x30E - 0x30F: Reserved */
    __R  uint8_t  LOST_LINK_CNT[4];            /* 0x310 - 0x313: Lost Link Counter */
    __R  uint8_t  RESERVED19[236];             /* 0x314 - 0x3FF: Reserved */
    __R  uint16_t WDG_DIV;                     /* 0x400: Watchdog Divider */
    __R  uint8_t  RESERVED20[14];              /* 0x402 - 0x40F: Reserved */
    __R  uint16_t WDG_TIME_PDI;                /* 0x410: Watchdog Time PDI */
    __R  uint8_t  RESERVED21[14];              /* 0x412 - 0x41F: Reserved */
    __R  uint16_t WDG_TIME_PDAT;               /* 0x420: Watchdog Time Process Data */
    __R  uint8_t  RESERVED22[30];              /* 0x422 - 0x43F: Reserved */
    __RW uint16_t WDG_STAT_PDAT;               /* 0x440: Watchdog Status Process Data */
    __R  uint8_t  WDG_CNT_PDAT;                /* 0x442: Watchdog Counter Process Data */
    __R  uint8_t  WDG_CNT_PDI;                 /* 0x443: Watchdog Counter PDI */
    __R  uint8_t  RESERVED23[188];             /* 0x444 - 0x4FF: Reserved */
    __R  uint8_t  EEPROM_CFG;                  /* 0x500: EEPROM Configuration */
    __RW uint8_t  EEPROM_PDI_ACC_STAT;         /* 0x501: EEPROM PDI Access State */
    __RW uint16_t EEPROM_CTRL_STAT;            /* 0x502: EEPROM Control/Status */
    __RW uint32_t EEPROM_ADDR;                 /* 0x504: EEPROM Address */
    __RW uint64_t EEPROM_DATA;                 /* 0x508: EEPROM Data */
    __RW uint16_t MII_MNG_CS;                  /* 0x510: MII Management Control/Status */
    __RW uint8_t  PHY_ADDR;                    /* 0x512: PHY Address */
    __RW uint8_t  PHY_REG_ADDR;                /* 0x513: PHY Register Address */
    __RW uint16_t PHY_DATA;                    /* 0x514: PHY Data */
    __R  uint8_t  MIIM_ECAT_ACC_STAT;          /* 0x516: MII Management ECAT Access State */
    __RW uint8_t  MIIM_PDI_ACC_STAT;           /* 0x517: MII Management PDI Access State */
    __RW uint8_t  PHY_STAT[4];                 /* 0x518 - 0x51B: PHY Port */
    __R  uint8_t  RESERVED24[228];             /* 0x51C - 0x5FF: Reserved */
    struct {
        __R  uint32_t LOGIC_START_ADDR;        /* 0x600: Logical Start Address */
        __R  uint16_t LENGTH;                  /* 0x604: Length */
        __R  uint8_t  LOGIC_START_BIT;         /* 0x606: Logical Start Bit */
        __R  uint8_t  LOGIC_STOP_BIT;          /* 0x607: Logical Stop Bit */
        __R  uint16_t PHYSICAL_START_ADDR;     /* 0x608: Physical Start Address */
        __R  uint8_t  PHYSICAL_START_BIT;      /* 0x60A: Physical Start Bit */
        __R  uint8_t  TYPE;                    /* 0x60B: Type */
        __R  uint8_t  ACTIVATE;                /* 0x60C: Activate */
        __R  uint8_t  RESERVED0[3];            /* 0x60D - 0x60F: Reserved */
    } FMMU[8];
    __R  uint8_t  RESERVED25[384];             /* 0x680 - 0x7FF: Reserved */
    struct {
        __R  uint16_t PHYSICAL_START_ADDR;     /* 0x800: Physical Start Address */
        __R  uint16_t LENGTH;                  /* 0x802: Length */
        __R  uint8_t  CONTROL;                 /* 0x804: Control */
        __R  uint8_t  STATUS;                  /* 0x805: Status */
        __RW uint8_t  ACTIVATE;                /* 0x806: Activate */
        __RW uint8_t  PDI_CTRL;                /* 0x807: PDI Control */
    } SYNCM[8];
    __R  uint8_t  RESERVED26[192];             /* 0x840 - 0x8FF: Reserved */
    __R  uint32_t RCV_TIME[4];                 /* 0x900 - 0x90C: Receive Time */
    __RW uint64_t SYS_TIME;                    /* 0x910: System Time */
    __R  uint64_t RCVT_ECAT_PU;                /* 0x918: Receive Time ECAT Processing Unit */
    __RW uint64_t SYS_TIME_OFFSET;             /* 0x920: System Time Offset */
    __RW uint32_t SYS_TIME_DELAY;              /* 0x928: System Time Delay */
    __R  uint32_t SYS_TIME_DIFF;               /* 0x92C: System Time Difference */
    __RW uint16_t SPD_CNT_START;               /* 0x930: Speed Counter Start */
    __R  uint16_t SPD_CNT_DIFF;                /* 0x932: Speed Counter Diff */
    __RW uint8_t  SYS_TIME_DIFF_FD;            /* 0x934: System Time Difference Filter Depth */
    __RW uint8_t  SPD_CNT_FD;                  /* 0x935: Speed Counter Filter Depth */
    __R  uint8_t  RCV_TIME_LM;                 /* 0x936: Receive Time Latch Mode */
    __R  uint8_t  RESERVED27[73];              /* 0x937 - 0x97F: Reserved */
    __R  uint8_t  CYC_UNIT_CTRL;               /* 0x980: Cyclic Unit Control */
    __RW uint8_t  SYNCO_ACT;                   /* 0x981: SYNC Out Unit Activation */
    __R  uint16_t PULSE_LEN;                   /* 0x982: Pulse Length of SyncSignals */
    __R  uint8_t  ACT_STAT;                    /* 0x984: Activation Status */
    __R  uint8_t  RESERVED28[9];               /* 0x985 - 0x98D: Reserved */
    __RW uint8_t  SYNC0_STAT;                  /* 0x98E: SYNC0 Status */
    __RW uint8_t  SYNC1_STAT;                  /* 0x98F: SYNC1 Status */
    __RW uint64_t START_TIME_CO;               /* 0x990: Start Time Cyclic Operation */
    __R  uint64_t NXT_SYNC1_PULSE;             /* 0x998: Next SYNC1 Pulse */
    __RW uint32_t SYNC0_CYC_TIME;              /* 0x9A0: SYNC0 Cycle Time */
    __RW uint32_t SYNC1_CYC_TIME;              /* 0x9A4: SYNC1 Cycle Time */
    __RW uint8_t  LATCH0_CTRL;                 /* 0x9A8: Latch0 Control */
    __RW uint8_t  LATCH1_CTRL;                 /* 0x9A9: Latch1 Control */
    __R  uint8_t  RESERVED29[4];               /* 0x9AA - 0x9AD: Reserved */
    __R  uint8_t  LATCH0_STAT;                 /* 0x9AE: Latch0 Status */
    __R  uint8_t  LATCH1_STAT;                 /* 0x9AF: Latch1 Status */
    __RW uint64_t LATCH0_TIME_PE;              /* 0x9B0: Latch0 Time Positive Edge */
    __RW uint64_t LATCH0_TIME_NE;              /* 0x9B8: Latch0 Time Negative Edge */
    __RW uint64_t LATCH1_TIME_PE;              /* 0x9C0: Latch1 Time Positive Edge */
    __RW uint64_t LATCH1_TIME_NE;              /* 0x9C8: Latch1 Time Negative Edge */
    __R  uint8_t  RESERVED30[32];              /* 0x9D0 - 0x9EF: Reserved */
    __R  uint32_t ECAT_BUF_CET;                /* 0x9F0: EtherCAT Buffer Change Event Time */
    __R  uint8_t  RESERVED31[4];               /* 0x9F4 - 0x9F7: Reserved */
    __R  uint32_t PDI_BUF_SET;                 /* 0x9F8: PDI Buffer Start Event Time */
    __R  uint32_t PDI_BUF_CET;                 /* 0x9FC: PDI Buffer Change Event Time */
    __R  uint8_t  RESERVED32[1024];            /* 0xA00 - 0xDFF: Reserved */
    __R  uint64_t PID;                         /* 0xE00: Product ID */
    __R  uint64_t VID;                         /* 0xE08: Vendor ID */
    __R  uint8_t  RESERVED33[240];             /* 0xE10 - 0xEFF: Reserved */
    __R  uint32_t DIO_OUT_DATA;                /* 0xF00: Digital I/O Output Data */
    __R  uint8_t  RESERVED34[12];              /* 0xF04 - 0xF0F: Reserved */
    __RW uint64_t GPO;                         /* 0xF10: General Purpose Outputs */
    __R  uint64_t GPI;                         /* 0xF18: General Purpose Inputs */
    __R  uint8_t  RESERVED35[96];              /* 0xF20 - 0xF7F: Reserved */
    __RW uint8_t  USER_RAM_BYTE0;              /* 0xF80: User Ram Byte 0 */
    __RW uint8_t  USER_RAM_BYTE1;              /* 0xF81: User Ram Byte 1 */
    __RW uint8_t  USER_RAM_BYTE2;              /* 0xF82: User Ram Byte 2 */
    __RW uint8_t  USER_RAM_BYTE3;              /* 0xF83: User Ram Byte 3 */
    __RW uint8_t  USER_RAM_BYTE4;              /* 0xF84: User Ram Byte 4 */
    __RW uint8_t  USER_RAM_BYTE5;              /* 0xF85: User Ram Byte 5 */
    __RW uint8_t  USER_RAM_BYTE6;              /* 0xF86: User Ram Byte 6 */
    __RW uint8_t  USER_RAM_BYTE7;              /* 0xF87: User Ram Byte 7 */
    __RW uint8_t  USER_RAM_BYTE8;              /* 0xF88: User Ram Byte 8 */
    __RW uint8_t  USER_RAM_BYTE9;              /* 0xF89: User Ram Byte 9 */
    __RW uint8_t  USER_RAM_BYTE10;             /* 0xF8A: User Ram Byte 10 */
    __RW uint8_t  USER_RAM_BYTE11;             /* 0xF8B: User Ram Byte 11 */
    __R  uint8_t  RESERVED36[2];               /* 0xF8C - 0xF8D: Reserved */
    __RW uint8_t  USER_RAM_BYTE14;             /* 0xF8E: User Ram Byte 14 */
    __RW uint8_t  USER_RAM_BYTE15;             /* 0xF8F: User Ram Byte 15 */
    __R  uint8_t  RESERVED37[3];               /* 0xF90 - 0xF92: Reserved */
    __RW uint8_t  USER_RAM_BYTE19;             /* 0xF93: User Ram Byte 19 */
    __R  uint8_t  RESERVED38[108];             /* 0xF94 - 0xFFF: Reserved */
    __RW uint32_t PDRAM;                       /* 0x1000: Process Data Ram */
    __R  uint8_t  RESERVED39[61436];           /* 0x1004 - 0xFFFF: Reserved */
    __RW uint32_t PDRAM_ALS;                   /* 0x10000: Process Data Ram Alias */
    __R  uint8_t  RESERVED40[61436];           /* 0x10004 - 0x1EFFF: Reserved */
    __RW uint32_t GPR_CFG0;                    /* 0x1F000: General Purpose Configure 0 */
    __RW uint32_t GPR_CFG1;                    /* 0x1F004: General Purpose Configure 1 */
    __RW uint32_t GPR_CFG2;                    /* 0x1F008: General Purpose Configure 2 */
    __R  uint8_t  RESERVED41[4];               /* 0x1F00C - 0x1F00F: Reserved */
    __RW uint32_t PHY_CFG0;                    /* 0x1F010: PHY Configure 0 */
    __RW uint32_t PHY_CFG1;                    /* 0x1F014: PHY Configure 1 */
    __R  uint8_t  RESERVED42[8];               /* 0x1F018 - 0x1F01F: Reserved */
    __RW uint32_t GPIO_CTRL;                   /* 0x1F020: GPIO Output Enable */
    __R  uint8_t  RESERVED43[12];              /* 0x1F024 - 0x1F02F: Reserved */
    __RW uint32_t GPI_OVERRIDE0;               /* 0x1F030: GPI low word Override value */
    __RW uint32_t GPI_OVERRIDE1;               /* 0x1F034: GPI high word Override value */
    __R  uint32_t GPO_REG0;                    /* 0x1F038: GPO low word read value */
    __R  uint32_t GPO_REG1;                    /* 0x1F03C: GPO high word read value */
    __R  uint32_t GPI_REG0;                    /* 0x1F040: GPI low word read value */
    __R  uint32_t GPI_REG1;                    /* 0x1F044: GPI high word read value */
    __R  uint8_t  RESERVED44[24];              /* 0x1F048 - 0x1F05F: Reserved */
    __R  uint32_t GPR_STATUS;                  /* 0x1F060: global status register */
    __R  uint8_t  RESERVED45[28];              /* 0x1F064 - 0x1F07F: Reserved */
    __RW uint32_t IO_CFG[9];                   /* 0x1F080 - 0x1F0A0: CTR IO Configure */
} ESC_Type;


/* Bitfield definition for register: TYPE */
/*
 * TYPE (RO)
 *
 * Controller type
 */
#define ESC_TYPE_TYPE_MASK (0xFFU)
#define ESC_TYPE_TYPE_SHIFT (0U)
#define ESC_TYPE_TYPE_GET(x) (((uint8_t)(x) & ESC_TYPE_TYPE_MASK) >> ESC_TYPE_TYPE_SHIFT)

/* Bitfield definition for register: REVISION */
/*
 * X (RO)
 *
 * major version X
 */
#define ESC_REVISION_X_MASK (0xFFU)
#define ESC_REVISION_X_SHIFT (0U)
#define ESC_REVISION_X_GET(x) (((uint8_t)(x) & ESC_REVISION_X_MASK) >> ESC_REVISION_X_SHIFT)

/* Bitfield definition for register: BUILD */
/*
 * BUILD (RO)
 *
 */
#define ESC_BUILD_BUILD_MASK (0xFF00U)
#define ESC_BUILD_BUILD_SHIFT (8U)
#define ESC_BUILD_BUILD_GET(x) (((uint16_t)(x) & ESC_BUILD_BUILD_MASK) >> ESC_BUILD_BUILD_SHIFT)

/*
 * Y (RO)
 *
 * minor version Y
 */
#define ESC_BUILD_Y_MASK (0xF0U)
#define ESC_BUILD_Y_SHIFT (4U)
#define ESC_BUILD_Y_GET(x) (((uint16_t)(x) & ESC_BUILD_Y_MASK) >> ESC_BUILD_Y_SHIFT)

/*
 * Z (RO)
 *
 * maintenance version Z
 */
#define ESC_BUILD_Z_MASK (0xFU)
#define ESC_BUILD_Z_SHIFT (0U)
#define ESC_BUILD_Z_GET(x) (((uint16_t)(x) & ESC_BUILD_Z_MASK) >> ESC_BUILD_Z_SHIFT)

/* Bitfield definition for register: FMMU_NUM */
/*
 * NUM (RO)
 *
 * Number of supported FMMU channels (or entities)
 */
#define ESC_FMMU_NUM_NUM_MASK (0xFFU)
#define ESC_FMMU_NUM_NUM_SHIFT (0U)
#define ESC_FMMU_NUM_NUM_GET(x) (((uint8_t)(x) & ESC_FMMU_NUM_NUM_MASK) >> ESC_FMMU_NUM_NUM_SHIFT)

/* Bitfield definition for register: SYNCM_NUM */
/*
 * NUM (RO)
 *
 * Number of supported SyncManager channels (or entities)
 */
#define ESC_SYNCM_NUM_NUM_MASK (0xFFU)
#define ESC_SYNCM_NUM_NUM_SHIFT (0U)
#define ESC_SYNCM_NUM_NUM_GET(x) (((uint8_t)(x) & ESC_SYNCM_NUM_NUM_MASK) >> ESC_SYNCM_NUM_NUM_SHIFT)

/* Bitfield definition for register: RAM_SIZE */
/*
 * SIZE (RO)
 *
 * Process Data RAM size supported in KByte
 */
#define ESC_RAM_SIZE_SIZE_MASK (0xFFU)
#define ESC_RAM_SIZE_SIZE_SHIFT (0U)
#define ESC_RAM_SIZE_SIZE_GET(x) (((uint8_t)(x) & ESC_RAM_SIZE_SIZE_MASK) >> ESC_RAM_SIZE_SIZE_SHIFT)

/* Bitfield definition for register: PORT_DESC */
/*
 * PORT3 (RO)
 *
 * Port configuration:
 * 00:Not implemented
 * 01:Not configured (SII EEPROM)
 * 10:EBUS
 * 11:MII/RMII/RGMII
 */
#define ESC_PORT_DESC_PORT3_MASK (0xC0U)
#define ESC_PORT_DESC_PORT3_SHIFT (6U)
#define ESC_PORT_DESC_PORT3_GET(x) (((uint8_t)(x) & ESC_PORT_DESC_PORT3_MASK) >> ESC_PORT_DESC_PORT3_SHIFT)

/*
 * PORT2 (RO)
 *
 * Port configuration:
 * 00:Not implemented
 * 01:Not configured (SII EEPROM)
 * 10:EBUS
 * 11:MII/RMII/RGMII
 */
#define ESC_PORT_DESC_PORT2_MASK (0x30U)
#define ESC_PORT_DESC_PORT2_SHIFT (4U)
#define ESC_PORT_DESC_PORT2_GET(x) (((uint8_t)(x) & ESC_PORT_DESC_PORT2_MASK) >> ESC_PORT_DESC_PORT2_SHIFT)

/*
 * PORT1 (RO)
 *
 * Port configuration:
 * 00:Not implemented
 * 01:Not configured (SII EEPROM)
 * 10:EBUS
 * 11:MII/RMII/RGMII
 */
#define ESC_PORT_DESC_PORT1_MASK (0xCU)
#define ESC_PORT_DESC_PORT1_SHIFT (2U)
#define ESC_PORT_DESC_PORT1_GET(x) (((uint8_t)(x) & ESC_PORT_DESC_PORT1_MASK) >> ESC_PORT_DESC_PORT1_SHIFT)

/*
 * PORT0 (RO)
 *
 * Port configuration:
 * 00:Not implemented
 * 01:Not configured (SII EEPROM)
 * 10:EBUS
 * 11:MII/RMII/RGMII
 */
#define ESC_PORT_DESC_PORT0_MASK (0x3U)
#define ESC_PORT_DESC_PORT0_SHIFT (0U)
#define ESC_PORT_DESC_PORT0_GET(x) (((uint8_t)(x) & ESC_PORT_DESC_PORT0_MASK) >> ESC_PORT_DESC_PORT0_SHIFT)

/* Bitfield definition for register: FEATURE */
/*
 * FFSC (RO)
 *
 * Fixed FMMU/SyncManager configuration:
 * 0:Variable configuration
 * 1:Fixed configuration (refer to documentation of supporting ESCs)
 */
#define ESC_FEATURE_FFSC_MASK (0x800U)
#define ESC_FEATURE_FFSC_SHIFT (11U)
#define ESC_FEATURE_FFSC_GET(x) (((uint16_t)(x) & ESC_FEATURE_FFSC_MASK) >> ESC_FEATURE_FFSC_SHIFT)

/*
 * RWC (RO)
 *
 * EtherCAT read/write command support(BRW,APRW,FPRW):
 * 0:Supported
 * 1:Not supported
 */
#define ESC_FEATURE_RWC_MASK (0x400U)
#define ESC_FEATURE_RWC_SHIFT (10U)
#define ESC_FEATURE_RWC_GET(x) (((uint16_t)(x) & ESC_FEATURE_RWC_MASK) >> ESC_FEATURE_RWC_SHIFT)

/*
 * LRW (RO)
 *
 * EtherCAT LRW command support:
 * 0:Supported
 * 1:Not supported
 */
#define ESC_FEATURE_LRW_MASK (0x200U)
#define ESC_FEATURE_LRW_SHIFT (9U)
#define ESC_FEATURE_LRW_GET(x) (((uint16_t)(x) & ESC_FEATURE_LRW_MASK) >> ESC_FEATURE_LRW_SHIFT)

/*
 * EDSA (RO)
 *
 * Enhanced DC SYNC Activation:
 * 0:Not available
 * 1:Available
 * Note:This feature refers to registers 0x981[7:3] and 0x0984
 */
#define ESC_FEATURE_EDSA_MASK (0x100U)
#define ESC_FEATURE_EDSA_SHIFT (8U)
#define ESC_FEATURE_EDSA_GET(x) (((uint16_t)(x) & ESC_FEATURE_EDSA_MASK) >> ESC_FEATURE_EDSA_SHIFT)

/*
 * SHFE (RO)
 *
 * Seperate Handling of FCS Errors:
 * 0:Not supported
 * 1:Supported, frames with wrong FCS and additional nibble will be counted separately in Forwarded RX Error Counter
 */
#define ESC_FEATURE_SHFE_MASK (0x80U)
#define ESC_FEATURE_SHFE_SHIFT (7U)
#define ESC_FEATURE_SHFE_GET(x) (((uint16_t)(x) & ESC_FEATURE_SHFE_MASK) >> ESC_FEATURE_SHFE_SHIFT)

/*
 * ELDM (RO)
 *
 * Enhanced Link Detection MII:
 * 0:Not available
 * 1:Available
 */
#define ESC_FEATURE_ELDM_MASK (0x40U)
#define ESC_FEATURE_ELDM_SHIFT (6U)
#define ESC_FEATURE_ELDM_GET(x) (((uint16_t)(x) & ESC_FEATURE_ELDM_MASK) >> ESC_FEATURE_ELDM_SHIFT)

/*
 * DCW (RO)
 *
 * Distributed Clocks width:
 * 0:32 bit
 * 1:64 bit
 */
#define ESC_FEATURE_DCW_MASK (0x8U)
#define ESC_FEATURE_DCW_SHIFT (3U)
#define ESC_FEATURE_DCW_GET(x) (((uint16_t)(x) & ESC_FEATURE_DCW_MASK) >> ESC_FEATURE_DCW_SHIFT)

/*
 * DC (RO)
 *
 * Distributed Clocks:
 * 0:Not available
 * 1:Available
 */
#define ESC_FEATURE_DC_MASK (0x4U)
#define ESC_FEATURE_DC_SHIFT (2U)
#define ESC_FEATURE_DC_GET(x) (((uint16_t)(x) & ESC_FEATURE_DC_MASK) >> ESC_FEATURE_DC_SHIFT)

/*
 * FMMU (RO)
 *
 * FMMU Operation:
 * 0:Bit oriented
 * 1:Byte oriented
 */
#define ESC_FEATURE_FMMU_MASK (0x1U)
#define ESC_FEATURE_FMMU_SHIFT (0U)
#define ESC_FEATURE_FMMU_GET(x) (((uint16_t)(x) & ESC_FEATURE_FMMU_MASK) >> ESC_FEATURE_FMMU_SHIFT)

/* Bitfield definition for register: STATION_ADDR */
/*
 * ADDR (RO)
 *
 * Address used for node addressing
 * (FPRD/FPWR/FPRW/FRMW commands)
 */
#define ESC_STATION_ADDR_ADDR_MASK (0xFFFFU)
#define ESC_STATION_ADDR_ADDR_SHIFT (0U)
#define ESC_STATION_ADDR_ADDR_GET(x) (((uint16_t)(x) & ESC_STATION_ADDR_ADDR_MASK) >> ESC_STATION_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: STATION_ALS */
/*
 * ADDR (RW)
 *
 * Alias Address used for node addressing
 * (FPRD/FPWR/FPRW/FRMW commands).
 * The use of this alias is activated by Register
 * DL Control Bit 0x0100[24].
 * NOTE:EEPROM value is only transferred into this
 * register at first EEPROM load after power-on or
 * reset.
 * ESC20 exception:EEPROM value is transferred
 * into this register after each EEPROM reload
 * command.
 */
#define ESC_STATION_ALS_ADDR_MASK (0xFFFFU)
#define ESC_STATION_ALS_ADDR_SHIFT (0U)
#define ESC_STATION_ALS_ADDR_SET(x) (((uint16_t)(x) << ESC_STATION_ALS_ADDR_SHIFT) & ESC_STATION_ALS_ADDR_MASK)
#define ESC_STATION_ALS_ADDR_GET(x) (((uint16_t)(x) & ESC_STATION_ALS_ADDR_MASK) >> ESC_STATION_ALS_ADDR_SHIFT)

/* Bitfield definition for register: REG_WEN */
/*
 * EN (RO)
 *
 * If register write protection is enabled, this
 * register has to be written in the same
 * Ethernet frame (value does not matter)
 * before other writes to this station are allowed.
 * This bit is self-clearing at the beginning of the
 * next frame (SOF), or if Register Write
 * Protection is disabled.
 */
#define ESC_REG_WEN_EN_MASK (0x1U)
#define ESC_REG_WEN_EN_SHIFT (0U)
#define ESC_REG_WEN_EN_GET(x) (((uint8_t)(x) & ESC_REG_WEN_EN_MASK) >> ESC_REG_WEN_EN_SHIFT)

/* Bitfield definition for register: REG_WP */
/*
 * WP (RO)
 *
 * Register write protection:
 * 0:Protection disabled
 * 1:Protection enabled
 * Registers 0x0000:0x0F7F are write-protected,
 * except for 0x0020 and 0x0030
 */
#define ESC_REG_WP_WP_MASK (0x1U)
#define ESC_REG_WP_WP_SHIFT (0U)
#define ESC_REG_WP_WP_GET(x) (((uint8_t)(x) & ESC_REG_WP_WP_MASK) >> ESC_REG_WP_WP_SHIFT)

/* Bitfield definition for register: ESC_WEN */
/*
 * EN (RO)
 *
 * If ESC write protection is enabled, this
 * register has to be written in the same
 * Ethernet frame (value does not matter)
 * before other writes to this station are allowed.
 * This bit is self-clearing at the beginning of the
 * next frame (SOF), or if ESC Write Protection
 * is disabled.
 */
#define ESC_ESC_WEN_EN_MASK (0x1U)
#define ESC_ESC_WEN_EN_SHIFT (0U)
#define ESC_ESC_WEN_EN_GET(x) (((uint8_t)(x) & ESC_ESC_WEN_EN_MASK) >> ESC_ESC_WEN_EN_SHIFT)

/* Bitfield definition for register: ESC_WP */
/*
 * WP (RO)
 *
 * Write protect:
 * 0:Protection disabled
 * 1:Protection enabled
 * All areas are write-protected, except for 0x0030.
 */
#define ESC_ESC_WP_WP_MASK (0x1U)
#define ESC_ESC_WP_WP_SHIFT (0U)
#define ESC_ESC_WP_WP_GET(x) (((uint8_t)(x) & ESC_ESC_WP_WP_MASK) >> ESC_ESC_WP_WP_SHIFT)

/* Bitfield definition for register: ESC_RST_ECAT */
/*
 * PR (RO)
 *
 * Progress of the reset procedure:
 * 00:initial/reset state
 * 01:after writing 0x52 ('R'), when previous
 * state was 00
 * 10:after writing 0x45 ('E'), when previous
 * state was 01
 * 11:after writing 0x53 ('S'), when previous
 * state was 10.
 * This value must not be observed
 * because the ESC enters reset when this
 * state is reached, resulting in state 00
 */
#define ESC_ESC_RST_ECAT_PR_MASK (0x3U)
#define ESC_ESC_RST_ECAT_PR_SHIFT (0U)
#define ESC_ESC_RST_ECAT_PR_GET(x) (((uint8_t)(x) & ESC_ESC_RST_ECAT_PR_MASK) >> ESC_ESC_RST_ECAT_PR_SHIFT)

/* Bitfield definition for register: ESC_RST_PDI */
/*
 * RST (RW)
 *
 * A reset is asserted after writing the reset
 * sequence 0x52 ('R'), 0x45 ('E') and 0x53 ('S')
 * in this register with 3 consecutive commands.
 * Any other command which does not continue
 * the sequence by writing the next expected
 * value will cancel the reset procedure
 */
#define ESC_ESC_RST_PDI_RST_MASK (0xFFU)
#define ESC_ESC_RST_PDI_RST_SHIFT (0U)
#define ESC_ESC_RST_PDI_RST_SET(x) (((uint8_t)(x) << ESC_ESC_RST_PDI_RST_SHIFT) & ESC_ESC_RST_PDI_RST_MASK)
#define ESC_ESC_RST_PDI_RST_GET(x) (((uint8_t)(x) & ESC_ESC_RST_PDI_RST_MASK) >> ESC_ESC_RST_PDI_RST_SHIFT)

/* Bitfield definition for register: ESC_DL_CTRL */
/*
 * SA (RO)
 *
 * Station alias:
 * 0:Ignore Station Alias
 * 1:Alias can be used for all configured
 * address comm
 */
#define ESC_ESC_DL_CTRL_SA_MASK (0x1000000UL)
#define ESC_ESC_DL_CTRL_SA_SHIFT (24U)
#define ESC_ESC_DL_CTRL_SA_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_SA_MASK) >> ESC_ESC_DL_CTRL_SA_SHIFT)

/*
 * RFS (RO)
 *
 * RX FIFO Size (ESC delays start of
 * forwarding until FIFO is at least half full).
 * RX FIFO Size/RX delay reduction** :
 * Value:EBUS:MII:
 * 0:-50 ns -40 ns (-80 ns***)
 * 1:-40 ns -40 ns (-80 ns***)
 * 2:-30 ns -40 ns
 * 3:-20 ns -40 ns
 * 4:-10 ns no change
 * 5:no change no change
 * 6:no change no change
 * 7:default default
 * NOTE:EEPROM value is only taken over at first
 * EEPROM load after power-on or reset
 */
#define ESC_ESC_DL_CTRL_RFS_MASK (0x70000UL)
#define ESC_ESC_DL_CTRL_RFS_SHIFT (16U)
#define ESC_ESC_DL_CTRL_RFS_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_RFS_MASK) >> ESC_ESC_DL_CTRL_RFS_SHIFT)

/*
 * LP3 (RO)
 *
 * Loop Port 3:
 * 00:Auto
 * 01:Auto Close
 * 10:Open
 * 11:Closed
 */
#define ESC_ESC_DL_CTRL_LP3_MASK (0xC000U)
#define ESC_ESC_DL_CTRL_LP3_SHIFT (14U)
#define ESC_ESC_DL_CTRL_LP3_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_LP3_MASK) >> ESC_ESC_DL_CTRL_LP3_SHIFT)

/*
 * LP2 (RO)
 *
 * Loop Port 2:
 * 00:Auto
 * 01:Auto Close
 * 10:Open
 * 11:Closed
 */
#define ESC_ESC_DL_CTRL_LP2_MASK (0x3000U)
#define ESC_ESC_DL_CTRL_LP2_SHIFT (12U)
#define ESC_ESC_DL_CTRL_LP2_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_LP2_MASK) >> ESC_ESC_DL_CTRL_LP2_SHIFT)

/*
 * LP1 (RO)
 *
 * Loop Port 1:
 * 00:Auto
 * 01:Auto Close
 * 10:Open
 * 11:Closed
 */
#define ESC_ESC_DL_CTRL_LP1_MASK (0xC00U)
#define ESC_ESC_DL_CTRL_LP1_SHIFT (10U)
#define ESC_ESC_DL_CTRL_LP1_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_LP1_MASK) >> ESC_ESC_DL_CTRL_LP1_SHIFT)

/*
 * LP0 (RO)
 *
 * Loop Port 0:
 * 00:Auto
 * 01:Auto Close
 * 10:Open
 * 11:Closed
 * NOTE:
 * Loop open means sending/receiving over this port
 * is enabled, loop closed means sending/receiving
 * is disabled and frames are forwarded to the next
 * open port internally.
 * Auto:loop closed at link down, opened at link up
 * Auto Close:loop closed at link down, opened with
 * writing 01 again after link up (or receiving a valid
 * Ethernet frame at the closed port)
 * Open:loop open regardless of link state
 * Closed:loop closed regardless of link state
 */
#define ESC_ESC_DL_CTRL_LP0_MASK (0x300U)
#define ESC_ESC_DL_CTRL_LP0_SHIFT (8U)
#define ESC_ESC_DL_CTRL_LP0_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_LP0_MASK) >> ESC_ESC_DL_CTRL_LP0_SHIFT)

/*
 * TU (RO)
 *
 * Temporary use of settings in
 * 0x0100:0x0103[8:15]:
 * 0:permanent use
 * 1:use for about 1 second, then revert to
 * previous settings
 */
#define ESC_ESC_DL_CTRL_TU_MASK (0x2U)
#define ESC_ESC_DL_CTRL_TU_SHIFT (1U)
#define ESC_ESC_DL_CTRL_TU_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_TU_MASK) >> ESC_ESC_DL_CTRL_TU_SHIFT)

/*
 * FR (RO)
 *
 * Forwarding rule:
 * 0:Forward non-EtherCAT frames:
 * EtherCAT frames are processed,
 * non-EtherCAT frames are forwarded
 * without processing or modification.
 * The source MAC address is not
 * changed for any frame.
 * 1:Destroy non-EtherCAT frames:
 * EtherCAT frames are processed, non-EtherCAT frames are destroyed.
 * The source MAC address is changed by
 * the Processing Unit for every frame
 * (SOURCE_MAC[1] is set
 */
#define ESC_ESC_DL_CTRL_FR_MASK (0x1U)
#define ESC_ESC_DL_CTRL_FR_SHIFT (0U)
#define ESC_ESC_DL_CTRL_FR_GET(x) (((uint32_t)(x) & ESC_ESC_DL_CTRL_FR_MASK) >> ESC_ESC_DL_CTRL_FR_SHIFT)

/* Bitfield definition for register: PHYSICAL_RW_OFFSET */
/*
 * OFFSET (RO)
 *
 * This register is used for ReadWrite
 * commands in Device Addressing mode
 * (FPRW, APRW, BRW).
 * The internal read address is directly taken
 * from the offset address field of the EtherCAT
 * datagram header, while the internal write
 * address is calculated by adding the Physical
 * Read/Write Offset value to the offset address
 * field.
 * Internal read address = ADR,
 * internal write address = ADR + R/W-Offset
 */
#define ESC_PHYSICAL_RW_OFFSET_OFFSET_MASK (0xFFFFU)
#define ESC_PHYSICAL_RW_OFFSET_OFFSET_SHIFT (0U)
#define ESC_PHYSICAL_RW_OFFSET_OFFSET_GET(x) (((uint16_t)(x) & ESC_PHYSICAL_RW_OFFSET_OFFSET_MASK) >> ESC_PHYSICAL_RW_OFFSET_OFFSET_SHIFT)

/* Bitfield definition for register: ESC_DL_STAT */
/*
 * CP3 (RO)
 *
 * Communication on Port 3:
 * 0:No stable communication
 * 1:Communication established
 */
#define ESC_ESC_DL_STAT_CP3_MASK (0x8000U)
#define ESC_ESC_DL_STAT_CP3_SHIFT (15U)
#define ESC_ESC_DL_STAT_CP3_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_CP3_MASK) >> ESC_ESC_DL_STAT_CP3_SHIFT)

/*
 * LP3 (RO)
 *
 * Loop Port 3:
 * 0:Open
 * 1:Closed
 */
#define ESC_ESC_DL_STAT_LP3_MASK (0x4000U)
#define ESC_ESC_DL_STAT_LP3_SHIFT (14U)
#define ESC_ESC_DL_STAT_LP3_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_LP3_MASK) >> ESC_ESC_DL_STAT_LP3_SHIFT)

/*
 * CP2 (RO)
 *
 * Communication on Port 2:
 * 0:No stable communication
 * 1:Communication established
 */
#define ESC_ESC_DL_STAT_CP2_MASK (0x2000U)
#define ESC_ESC_DL_STAT_CP2_SHIFT (13U)
#define ESC_ESC_DL_STAT_CP2_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_CP2_MASK) >> ESC_ESC_DL_STAT_CP2_SHIFT)

/*
 * LP2 (RO)
 *
 * Loop Port 2:
 * 0:Open
 * 1:Closed
 */
#define ESC_ESC_DL_STAT_LP2_MASK (0x1000U)
#define ESC_ESC_DL_STAT_LP2_SHIFT (12U)
#define ESC_ESC_DL_STAT_LP2_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_LP2_MASK) >> ESC_ESC_DL_STAT_LP2_SHIFT)

/*
 * CP1 (RO)
 *
 * Communication on Port 1:
 * 0:No stable communication
 * 1:Communication established
 */
#define ESC_ESC_DL_STAT_CP1_MASK (0x800U)
#define ESC_ESC_DL_STAT_CP1_SHIFT (11U)
#define ESC_ESC_DL_STAT_CP1_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_CP1_MASK) >> ESC_ESC_DL_STAT_CP1_SHIFT)

/*
 * LP1 (RO)
 *
 * Loop Port 1:
 * 0:Open
 * 1:Closed
 */
#define ESC_ESC_DL_STAT_LP1_MASK (0x400U)
#define ESC_ESC_DL_STAT_LP1_SHIFT (10U)
#define ESC_ESC_DL_STAT_LP1_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_LP1_MASK) >> ESC_ESC_DL_STAT_LP1_SHIFT)

/*
 * CP0 (RO)
 *
 * Communication on Port 0:
 * 0:No stable communication
 * 1:Communication established
 */
#define ESC_ESC_DL_STAT_CP0_MASK (0x200U)
#define ESC_ESC_DL_STAT_CP0_SHIFT (9U)
#define ESC_ESC_DL_STAT_CP0_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_CP0_MASK) >> ESC_ESC_DL_STAT_CP0_SHIFT)

/*
 * LP0 (RO)
 *
 * Loop Port 0:
 * 0:Open
 * 1:Closed
 */
#define ESC_ESC_DL_STAT_LP0_MASK (0x100U)
#define ESC_ESC_DL_STAT_LP0_SHIFT (8U)
#define ESC_ESC_DL_STAT_LP0_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_LP0_MASK) >> ESC_ESC_DL_STAT_LP0_SHIFT)

/*
 * PLP3 (RO)
 *
 * Physical link on Port 3:
 * 0:No link
 * 1:Link detected
 */
#define ESC_ESC_DL_STAT_PLP3_MASK (0x80U)
#define ESC_ESC_DL_STAT_PLP3_SHIFT (7U)
#define ESC_ESC_DL_STAT_PLP3_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_PLP3_MASK) >> ESC_ESC_DL_STAT_PLP3_SHIFT)

/*
 * PLP2 (RO)
 *
 * Physical link on Port 2:
 * 0:No link
 * 1:Link detected
 */
#define ESC_ESC_DL_STAT_PLP2_MASK (0x40U)
#define ESC_ESC_DL_STAT_PLP2_SHIFT (6U)
#define ESC_ESC_DL_STAT_PLP2_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_PLP2_MASK) >> ESC_ESC_DL_STAT_PLP2_SHIFT)

/*
 * PLP1 (RO)
 *
 * Physical link on Port 1:
 * 0:No link
 * 1:Link detected
 */
#define ESC_ESC_DL_STAT_PLP1_MASK (0x20U)
#define ESC_ESC_DL_STAT_PLP1_SHIFT (5U)
#define ESC_ESC_DL_STAT_PLP1_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_PLP1_MASK) >> ESC_ESC_DL_STAT_PLP1_SHIFT)

/*
 * PLP0 (RO)
 *
 * Physical link on Port 0:
 * 0:No link
 * 1:Link detected
 */
#define ESC_ESC_DL_STAT_PLP0_MASK (0x10U)
#define ESC_ESC_DL_STAT_PLP0_SHIFT (4U)
#define ESC_ESC_DL_STAT_PLP0_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_PLP0_MASK) >> ESC_ESC_DL_STAT_PLP0_SHIFT)

/*
 * ELD (RO)
 *
 * Enhanced Link detection:
 * 0:Deactivated for all ports
 * 1:Activated for at least one port
 * NOTE:EEPROM value is only transferred into this
 * register at first EEPROM load after power-on or
 * reset
 */
#define ESC_ESC_DL_STAT_ELD_MASK (0x4U)
#define ESC_ESC_DL_STAT_ELD_SHIFT (2U)
#define ESC_ESC_DL_STAT_ELD_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_ELD_MASK) >> ESC_ESC_DL_STAT_ELD_SHIFT)

/*
 * WDS (RO)
 *
 * PDI Watchdog Status:
 * 0:Watchdog expired
 * 1:Watchdog reloaded
 */
#define ESC_ESC_DL_STAT_WDS_MASK (0x2U)
#define ESC_ESC_DL_STAT_WDS_SHIFT (1U)
#define ESC_ESC_DL_STAT_WDS_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_WDS_MASK) >> ESC_ESC_DL_STAT_WDS_SHIFT)

/*
 * EPLC (RO)
 *
 * PDI operational/EEPROM loaded correctly:
 * 0:EEPROM not loaded, PDI not
 * operational (no access to Process Data
 * RAM)
 * 1:EEPROM loaded correctly, PDI
 * operational (access to Process Data
 * RAM)
 */
#define ESC_ESC_DL_STAT_EPLC_MASK (0x1U)
#define ESC_ESC_DL_STAT_EPLC_SHIFT (0U)
#define ESC_ESC_DL_STAT_EPLC_GET(x) (((uint16_t)(x) & ESC_ESC_DL_STAT_EPLC_MASK) >> ESC_ESC_DL_STAT_EPLC_SHIFT)

/* Bitfield definition for register: AL_CTRL */
/*
 * DI (RW)
 *
 * Device Identification:
 * 0:No request
 * 1:Device Identification request
 */
#define ESC_AL_CTRL_DI_MASK (0x20U)
#define ESC_AL_CTRL_DI_SHIFT (5U)
#define ESC_AL_CTRL_DI_SET(x) (((uint16_t)(x) << ESC_AL_CTRL_DI_SHIFT) & ESC_AL_CTRL_DI_MASK)
#define ESC_AL_CTRL_DI_GET(x) (((uint16_t)(x) & ESC_AL_CTRL_DI_MASK) >> ESC_AL_CTRL_DI_SHIFT)

/*
 * EIA (RW)
 *
 * Error Ind Ack:
 * 0:No Ack of Error Ind in AL status register
 * 1:Ack of Error Ind in AL status register
 */
#define ESC_AL_CTRL_EIA_MASK (0x10U)
#define ESC_AL_CTRL_EIA_SHIFT (4U)
#define ESC_AL_CTRL_EIA_SET(x) (((uint16_t)(x) << ESC_AL_CTRL_EIA_SHIFT) & ESC_AL_CTRL_EIA_MASK)
#define ESC_AL_CTRL_EIA_GET(x) (((uint16_t)(x) & ESC_AL_CTRL_EIA_MASK) >> ESC_AL_CTRL_EIA_SHIFT)

/*
 * IST (RW)
 *
 * Initiate State Transition of the Device State
 * Machine:
 * 1:Request Init State
 * 3:Request Bootstrap State
 * 2:Request Pre-Operational State
 * 4:Request Safe-Operational State
 * 8:Request Operational State
 */
#define ESC_AL_CTRL_IST_MASK (0xFU)
#define ESC_AL_CTRL_IST_SHIFT (0U)
#define ESC_AL_CTRL_IST_SET(x) (((uint16_t)(x) << ESC_AL_CTRL_IST_SHIFT) & ESC_AL_CTRL_IST_MASK)
#define ESC_AL_CTRL_IST_GET(x) (((uint16_t)(x) & ESC_AL_CTRL_IST_MASK) >> ESC_AL_CTRL_IST_SHIFT)

/* Bitfield definition for register: AL_STAT */
/*
 * DI (RW)
 *
 * Device Identification:
 * 0:Device Identification not valid
 * 1:Device Identification loaded
 */
#define ESC_AL_STAT_DI_MASK (0x20U)
#define ESC_AL_STAT_DI_SHIFT (5U)
#define ESC_AL_STAT_DI_SET(x) (((uint16_t)(x) << ESC_AL_STAT_DI_SHIFT) & ESC_AL_STAT_DI_MASK)
#define ESC_AL_STAT_DI_GET(x) (((uint16_t)(x) & ESC_AL_STAT_DI_MASK) >> ESC_AL_STAT_DI_SHIFT)

/*
 * EI (RW)
 *
 * Error Ind:
 * 0:Device is in State as requested or Flag
 * cleared by command
 * 1:Device has not entered requested State
 * or changed State as result of a local
 * action
 */
#define ESC_AL_STAT_EI_MASK (0x10U)
#define ESC_AL_STAT_EI_SHIFT (4U)
#define ESC_AL_STAT_EI_SET(x) (((uint16_t)(x) << ESC_AL_STAT_EI_SHIFT) & ESC_AL_STAT_EI_MASK)
#define ESC_AL_STAT_EI_GET(x) (((uint16_t)(x) & ESC_AL_STAT_EI_MASK) >> ESC_AL_STAT_EI_SHIFT)

/*
 * AS (RW)
 *
 * Actual State of the Device State Machine:
 * 1:Init State
 * 3:Bootstrap State
 * 2:Pre-Operational State
 * 4:Safe-Operational State
 * 8:Operational State
 */
#define ESC_AL_STAT_AS_MASK (0xFU)
#define ESC_AL_STAT_AS_SHIFT (0U)
#define ESC_AL_STAT_AS_SET(x) (((uint16_t)(x) << ESC_AL_STAT_AS_SHIFT) & ESC_AL_STAT_AS_MASK)
#define ESC_AL_STAT_AS_GET(x) (((uint16_t)(x) & ESC_AL_STAT_AS_MASK) >> ESC_AL_STAT_AS_SHIFT)

/* Bitfield definition for register: AL_STAT_CODE */
/*
 * CODE (RW)
 *
 * AL Status Code
 */
#define ESC_AL_STAT_CODE_CODE_MASK (0xFFFFU)
#define ESC_AL_STAT_CODE_CODE_SHIFT (0U)
#define ESC_AL_STAT_CODE_CODE_SET(x) (((uint16_t)(x) << ESC_AL_STAT_CODE_CODE_SHIFT) & ESC_AL_STAT_CODE_CODE_MASK)
#define ESC_AL_STAT_CODE_CODE_GET(x) (((uint16_t)(x) & ESC_AL_STAT_CODE_CODE_MASK) >> ESC_AL_STAT_CODE_CODE_SHIFT)

/* Bitfield definition for register: RUN_LED_OVRD */
/*
 * EN_OVRD (RW)
 *
 * Enable Override:
 * 0:Override disabled
 * 1:Override enabled
 */
#define ESC_RUN_LED_OVRD_EN_OVRD_MASK (0x10U)
#define ESC_RUN_LED_OVRD_EN_OVRD_SHIFT (4U)
#define ESC_RUN_LED_OVRD_EN_OVRD_SET(x) (((uint8_t)(x) << ESC_RUN_LED_OVRD_EN_OVRD_SHIFT) & ESC_RUN_LED_OVRD_EN_OVRD_MASK)
#define ESC_RUN_LED_OVRD_EN_OVRD_GET(x) (((uint8_t)(x) & ESC_RUN_LED_OVRD_EN_OVRD_MASK) >> ESC_RUN_LED_OVRD_EN_OVRD_SHIFT)

/*
 * LED_CODE (RW)
 *
 * LED code:
 * 0x0:Off
 * 0x1:Flash 1x
 * 0x2-0xC:Flash 2x – 12x
 * 0xD:Blinking
 * 0xE:Flickering
 * 0xF:On
 */
#define ESC_RUN_LED_OVRD_LED_CODE_MASK (0xFU)
#define ESC_RUN_LED_OVRD_LED_CODE_SHIFT (0U)
#define ESC_RUN_LED_OVRD_LED_CODE_SET(x) (((uint8_t)(x) << ESC_RUN_LED_OVRD_LED_CODE_SHIFT) & ESC_RUN_LED_OVRD_LED_CODE_MASK)
#define ESC_RUN_LED_OVRD_LED_CODE_GET(x) (((uint8_t)(x) & ESC_RUN_LED_OVRD_LED_CODE_MASK) >> ESC_RUN_LED_OVRD_LED_CODE_SHIFT)

/* Bitfield definition for register: ERR_LED_OVRD */
/*
 * EN_OVRD (RW)
 *
 * Enable Override:
 * 0:Override disabled
 * 1:Override enabled
 */
#define ESC_ERR_LED_OVRD_EN_OVRD_MASK (0x10U)
#define ESC_ERR_LED_OVRD_EN_OVRD_SHIFT (4U)
#define ESC_ERR_LED_OVRD_EN_OVRD_SET(x) (((uint8_t)(x) << ESC_ERR_LED_OVRD_EN_OVRD_SHIFT) & ESC_ERR_LED_OVRD_EN_OVRD_MASK)
#define ESC_ERR_LED_OVRD_EN_OVRD_GET(x) (((uint8_t)(x) & ESC_ERR_LED_OVRD_EN_OVRD_MASK) >> ESC_ERR_LED_OVRD_EN_OVRD_SHIFT)

/*
 * LED_CODE (RW)
 *
 * LED code:
 * 0x0:Off
 * 0x1-0xC:Flash 1x – 12x
 * 0xD:Blinking
 * 0xE:Flickering
 * 0xF:On
 */
#define ESC_ERR_LED_OVRD_LED_CODE_MASK (0xFU)
#define ESC_ERR_LED_OVRD_LED_CODE_SHIFT (0U)
#define ESC_ERR_LED_OVRD_LED_CODE_SET(x) (((uint8_t)(x) << ESC_ERR_LED_OVRD_LED_CODE_SHIFT) & ESC_ERR_LED_OVRD_LED_CODE_MASK)
#define ESC_ERR_LED_OVRD_LED_CODE_GET(x) (((uint8_t)(x) & ESC_ERR_LED_OVRD_LED_CODE_MASK) >> ESC_ERR_LED_OVRD_LED_CODE_SHIFT)

/* Bitfield definition for register: PDI_CTRL */
/*
 * PDI (RO)
 *
 * Process data interface:
 * 0x00:Interface deactivated (no PDI)
 * 0x01:4 Digital Input
 * 0x02:4 Digital Output
 * 0x03:2 Digital Input and 2 Digital Output
 * 0x04:Digital I/O
 * 0x05:SPI Slave
 * 0x06:Oversampling I/O
 * 0x07:EtherCAT Bridge (port 3)
 * 0x08:16 Bit asynchronous Microcontroller
 * interface
 * 0x09:8 Bit asynchronous Microcontroller
 * interface
 * 0x0A:16 Bit synchronous Microcontroller
 * interface
 * 0x0B:8 Bit synchronous Microcontroller
 * interface
 * 0x10:32 Digital Input and 0 Digital Output
 * 0x11:24 Digital Input and 8 Digital Output
 * 0x12:16 Digital Input and 16 Digital Output
 * 0x13:8 Digital Input and 24 Digital Output
 * 0x14:0 Digital Input and 32 Digital Output
 * 0x80:On-chip bus
 * Others:Reserved
 */
#define ESC_PDI_CTRL_PDI_MASK (0xFFU)
#define ESC_PDI_CTRL_PDI_SHIFT (0U)
#define ESC_PDI_CTRL_PDI_GET(x) (((uint8_t)(x) & ESC_PDI_CTRL_PDI_MASK) >> ESC_PDI_CTRL_PDI_SHIFT)

/* Bitfield definition for register: ESC_CFG */
/*
 * ELP3 (RO)
 *
 * Enhanced Link port 3:
 * 0:disabled (if bit 1=0)
 * 1:enabled
 */
#define ESC_ESC_CFG_ELP3_MASK (0x80U)
#define ESC_ESC_CFG_ELP3_SHIFT (7U)
#define ESC_ESC_CFG_ELP3_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_ELP3_MASK) >> ESC_ESC_CFG_ELP3_SHIFT)

/*
 * ELP2 (RO)
 *
 * Enhanced Link port 2:
 * 0:disabled (if bit 1=0)
 * 1:enabled
 */
#define ESC_ESC_CFG_ELP2_MASK (0x40U)
#define ESC_ESC_CFG_ELP2_SHIFT (6U)
#define ESC_ESC_CFG_ELP2_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_ELP2_MASK) >> ESC_ESC_CFG_ELP2_SHIFT)

/*
 * ELP1 (RO)
 *
 * Enhanced Link port 1:
 * 0:disabled (if bit 1=0)
 * 1:enabled
 */
#define ESC_ESC_CFG_ELP1_MASK (0x20U)
#define ESC_ESC_CFG_ELP1_SHIFT (5U)
#define ESC_ESC_CFG_ELP1_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_ELP1_MASK) >> ESC_ESC_CFG_ELP1_SHIFT)

/*
 * ELP0 (RO)
 *
 * Enhanced Link port 0:
 * 0:disabled (if bit 1=0)
 * 1:enabled
 */
#define ESC_ESC_CFG_ELP0_MASK (0x10U)
#define ESC_ESC_CFG_ELP0_SHIFT (4U)
#define ESC_ESC_CFG_ELP0_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_ELP0_MASK) >> ESC_ESC_CFG_ELP0_SHIFT)

/*
 * CDLIU (RO)
 *
 * Distributed Clocks Latch In Unit:
 * 0:disabled (power saving)
 * 1:enabled
 */
#define ESC_ESC_CFG_CDLIU_MASK (0x8U)
#define ESC_ESC_CFG_CDLIU_SHIFT (3U)
#define ESC_ESC_CFG_CDLIU_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_CDLIU_MASK) >> ESC_ESC_CFG_CDLIU_SHIFT)

/*
 * DCSOU (RO)
 *
 * Distributed Clocks SYNC Out Unit:
 * 0:disabled (power saving)
 * 1:enabled
 */
#define ESC_ESC_CFG_DCSOU_MASK (0x4U)
#define ESC_ESC_CFG_DCSOU_SHIFT (2U)
#define ESC_ESC_CFG_DCSOU_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_DCSOU_MASK) >> ESC_ESC_CFG_DCSOU_SHIFT)

/*
 * ELDAP (RO)
 *
 * Enhanced Link detection all ports:
 * 0:disabled (if bits [7:4]=0)
 * 1:enabled at all ports (overrides bits [7:4])
 */
#define ESC_ESC_CFG_ELDAP_MASK (0x2U)
#define ESC_ESC_CFG_ELDAP_SHIFT (1U)
#define ESC_ESC_CFG_ELDAP_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_ELDAP_MASK) >> ESC_ESC_CFG_ELDAP_SHIFT)

/*
 * DEV_EMU (RO)
 *
 * Device emulation (control of AL status):
 * 0:AL status register has to be set by PDI
 * 1:AL status register will be set to value
 * written to AL control register
 */
#define ESC_ESC_CFG_DEV_EMU_MASK (0x1U)
#define ESC_ESC_CFG_DEV_EMU_SHIFT (0U)
#define ESC_ESC_CFG_DEV_EMU_GET(x) (((uint8_t)(x) & ESC_ESC_CFG_DEV_EMU_MASK) >> ESC_ESC_CFG_DEV_EMU_SHIFT)

/* Bitfield definition for register: PDI_INFO */
/*
 * PDICN (RO)
 *
 * PDI configuration invalid:
 * 0:PDI configuration ok
 * 1:PDI configuration invalid
 */
#define ESC_PDI_INFO_PDICN_MASK (0x8U)
#define ESC_PDI_INFO_PDICN_SHIFT (3U)
#define ESC_PDI_INFO_PDICN_GET(x) (((uint16_t)(x) & ESC_PDI_INFO_PDICN_MASK) >> ESC_PDI_INFO_PDICN_SHIFT)

/*
 * PDIA (RO)
 *
 * PDI active:
 * 0:PDI not active
 * 1:PDI active
 */
#define ESC_PDI_INFO_PDIA_MASK (0x4U)
#define ESC_PDI_INFO_PDIA_SHIFT (2U)
#define ESC_PDI_INFO_PDIA_GET(x) (((uint16_t)(x) & ESC_PDI_INFO_PDIA_MASK) >> ESC_PDI_INFO_PDIA_SHIFT)

/*
 * ECLFE (RO)
 *
 * ESC configuration area loaded from
 * EEPROM:
 * 0:not loaded
 * 1:loaded
 */
#define ESC_PDI_INFO_ECLFE_MASK (0x2U)
#define ESC_PDI_INFO_ECLFE_SHIFT (1U)
#define ESC_PDI_INFO_ECLFE_GET(x) (((uint16_t)(x) & ESC_PDI_INFO_ECLFE_MASK) >> ESC_PDI_INFO_ECLFE_SHIFT)

/*
 * PFABW (RO)
 *
 * DI function acknowledge by write:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_PDI_INFO_PFABW_MASK (0x1U)
#define ESC_PDI_INFO_PFABW_SHIFT (0U)
#define ESC_PDI_INFO_PFABW_GET(x) (((uint16_t)(x) & ESC_PDI_INFO_PFABW_MASK) >> ESC_PDI_INFO_PFABW_SHIFT)

/* Bitfield definition for register: PDI_CFG */
/*
 * BUS (RO)
 *
 * On-chip bus:
 * 000:Intel® Avalon®
 * 001:AXI®
 * 010:Xilinx® PLB v4.6
 * 100:Xilinx OPB
 * others:reserved
 */
#define ESC_PDI_CFG_BUS_MASK (0xE0U)
#define ESC_PDI_CFG_BUS_SHIFT (5U)
#define ESC_PDI_CFG_BUS_GET(x) (((uint8_t)(x) & ESC_PDI_CFG_BUS_MASK) >> ESC_PDI_CFG_BUS_SHIFT)

/*
 * CLK (RO)
 *
 * On-chip bus clock:
 * 0:asynchronous
 * 1-31:synchronous multiplication factor
 * (N * 25 MHz)
 */
#define ESC_PDI_CFG_CLK_MASK (0x1FU)
#define ESC_PDI_CFG_CLK_SHIFT (0U)
#define ESC_PDI_CFG_CLK_GET(x) (((uint8_t)(x) & ESC_PDI_CFG_CLK_MASK) >> ESC_PDI_CFG_CLK_SHIFT)

/* Bitfield definition for register: PDI_SL_CFG */
/*
 * SYNC1_MAER (RO)
 *
 * SYNC1 mapped to AL Event Request
 * register 0x0220[3]:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_PDI_SL_CFG_SYNC1_MAER_MASK (0x80U)
#define ESC_PDI_SL_CFG_SYNC1_MAER_SHIFT (7U)
#define ESC_PDI_SL_CFG_SYNC1_MAER_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC1_MAER_MASK) >> ESC_PDI_SL_CFG_SYNC1_MAER_SHIFT)

/*
 * SYNC1_CFG (RO)
 *
 * SYNC1/LATCH1 configuration*:
 * 0:LATCH1 input
 * 1:SYNC1 output
 */
#define ESC_PDI_SL_CFG_SYNC1_CFG_MASK (0x40U)
#define ESC_PDI_SL_CFG_SYNC1_CFG_SHIFT (6U)
#define ESC_PDI_SL_CFG_SYNC1_CFG_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC1_CFG_MASK) >> ESC_PDI_SL_CFG_SYNC1_CFG_SHIFT)

/*
 * SYNC1_ODP (RO)
 *
 * SYNC1 output driver/polarity:
 * 00:Push-Pull active low
 * 01:Open Drain (active low)
 * 10:Push-Pull active high
 * 11:Open Source (active high)
 */
#define ESC_PDI_SL_CFG_SYNC1_ODP_MASK (0x30U)
#define ESC_PDI_SL_CFG_SYNC1_ODP_SHIFT (4U)
#define ESC_PDI_SL_CFG_SYNC1_ODP_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC1_ODP_MASK) >> ESC_PDI_SL_CFG_SYNC1_ODP_SHIFT)

/*
 * SYNC0_MAER (RO)
 *
 * SYNC0 mapped to AL Event Request
 * register 0x0220[2]:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_PDI_SL_CFG_SYNC0_MAER_MASK (0x8U)
#define ESC_PDI_SL_CFG_SYNC0_MAER_SHIFT (3U)
#define ESC_PDI_SL_CFG_SYNC0_MAER_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC0_MAER_MASK) >> ESC_PDI_SL_CFG_SYNC0_MAER_SHIFT)

/*
 * SYNC0_CFG (RO)
 *
 * SYNC0/LATCH0 configuration*:
 * 0:LATCH0 Input
 * 1:SYNC0 Output
 */
#define ESC_PDI_SL_CFG_SYNC0_CFG_MASK (0x4U)
#define ESC_PDI_SL_CFG_SYNC0_CFG_SHIFT (2U)
#define ESC_PDI_SL_CFG_SYNC0_CFG_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC0_CFG_MASK) >> ESC_PDI_SL_CFG_SYNC0_CFG_SHIFT)

/*
 * SYNC0_ODP (RO)
 *
 * SYNC0 output driver/polarity:
 * 00:Push-Pull active low
 * 01:Open Drain (active low)
 * 10:Push-Pull active high
 * 11:Open Source (active high)
 */
#define ESC_PDI_SL_CFG_SYNC0_ODP_MASK (0x3U)
#define ESC_PDI_SL_CFG_SYNC0_ODP_SHIFT (0U)
#define ESC_PDI_SL_CFG_SYNC0_ODP_GET(x) (((uint8_t)(x) & ESC_PDI_SL_CFG_SYNC0_ODP_MASK) >> ESC_PDI_SL_CFG_SYNC0_ODP_SHIFT)

/* Bitfield definition for register: PDI_EXT_CFG */
/*
 * OCBST (RW)
 *
 * On-chip bus sub-type for AXI:
 * 000:AXI3
 * 001:AXI4
 * 010:AXI4 LITE
 * others:reserved
 */
#define ESC_PDI_EXT_CFG_OCBST_MASK (0x700U)
#define ESC_PDI_EXT_CFG_OCBST_SHIFT (8U)
#define ESC_PDI_EXT_CFG_OCBST_SET(x) (((uint16_t)(x) << ESC_PDI_EXT_CFG_OCBST_SHIFT) & ESC_PDI_EXT_CFG_OCBST_MASK)
#define ESC_PDI_EXT_CFG_OCBST_GET(x) (((uint16_t)(x) & ESC_PDI_EXT_CFG_OCBST_MASK) >> ESC_PDI_EXT_CFG_OCBST_SHIFT)

/*
 * RPS (RO)
 *
 * Read prefetch size (in cycles of PDI width):
 * 0:4 cycles
 * 1:1 cycle (typical)
 * 2:2 cycles
 * 3:Reserved
 */
#define ESC_PDI_EXT_CFG_RPS_MASK (0x3U)
#define ESC_PDI_EXT_CFG_RPS_SHIFT (0U)
#define ESC_PDI_EXT_CFG_RPS_GET(x) (((uint16_t)(x) & ESC_PDI_EXT_CFG_RPS_MASK) >> ESC_PDI_EXT_CFG_RPS_SHIFT)

/* Bitfield definition for register: ECAT_EVT_MSK */
/*
 * MASK (RO)
 *
 * ECAT Event masking of the ECAT Event
 * Request Events for mapping into ECAT event
 * field of EtherCAT frames:
 * 0:Corresponding ECAT Event Request
 * register bit is not mapped
 * 1:Corresponding ECAT Event Request
 * register bit is mapped
 */
#define ESC_ECAT_EVT_MSK_MASK_MASK (0xFFFFU)
#define ESC_ECAT_EVT_MSK_MASK_SHIFT (0U)
#define ESC_ECAT_EVT_MSK_MASK_GET(x) (((uint16_t)(x) & ESC_ECAT_EVT_MSK_MASK_MASK) >> ESC_ECAT_EVT_MSK_MASK_SHIFT)

/* Bitfield definition for register: PDI_AL_EVT_MSK */
/*
 * MASK (RW)
 *
 * AL Event masking of the AL Event Request
 * register Events for mapping to PDI IRQ
 * signal:
 * 0:Corresponding AL Event Request
 * register bit is not mapped
 * 1:Corresponding AL Event Request
 * register bit is mapped
 */
#define ESC_PDI_AL_EVT_MSK_MASK_MASK (0xFFFFFFFFUL)
#define ESC_PDI_AL_EVT_MSK_MASK_SHIFT (0U)
#define ESC_PDI_AL_EVT_MSK_MASK_SET(x) (((uint32_t)(x) << ESC_PDI_AL_EVT_MSK_MASK_SHIFT) & ESC_PDI_AL_EVT_MSK_MASK_MASK)
#define ESC_PDI_AL_EVT_MSK_MASK_GET(x) (((uint32_t)(x) & ESC_PDI_AL_EVT_MSK_MASK_MASK) >> ESC_PDI_AL_EVT_MSK_MASK_SHIFT)

/* Bitfield definition for register: ECAT_EVT_REQ */
/*
 * MV (RO)
 *
 * Mirrors values of each SyncManager Status:
 * 0:No Sync Channel 0 event
 * 1:Sync Channel 0 event pending
 * 0:No Sync Channel 1 event
 * 1:Sync Channel 1 event pending
 * …
 * 0:No Sync Channel 7 event
 * 1:Sync Channel 7 event pending
 */
#define ESC_ECAT_EVT_REQ_MV_MASK (0xFF0U)
#define ESC_ECAT_EVT_REQ_MV_SHIFT (4U)
#define ESC_ECAT_EVT_REQ_MV_GET(x) (((uint16_t)(x) & ESC_ECAT_EVT_REQ_MV_MASK) >> ESC_ECAT_EVT_REQ_MV_SHIFT)

/*
 * ALS_EVT (RO)
 *
 * AL Status event:
 * 0:No change in AL Status
 * 1:AL Status change
 * (Bit is cleared by reading out AL Status
 * 0x0130:0x0131 from ECAT)
 */
#define ESC_ECAT_EVT_REQ_ALS_EVT_MASK (0x8U)
#define ESC_ECAT_EVT_REQ_ALS_EVT_SHIFT (3U)
#define ESC_ECAT_EVT_REQ_ALS_EVT_GET(x) (((uint16_t)(x) & ESC_ECAT_EVT_REQ_ALS_EVT_MASK) >> ESC_ECAT_EVT_REQ_ALS_EVT_SHIFT)

/*
 * DLS_EVT (RO)
 *
 * DL Status event:
 * 0:No change in DL Status
 * 1:DL Status change
 * (Bit is cleared by reading out DL Status
 * 0x0110:0x0111 from ECAT)
 */
#define ESC_ECAT_EVT_REQ_DLS_EVT_MASK (0x4U)
#define ESC_ECAT_EVT_REQ_DLS_EVT_SHIFT (2U)
#define ESC_ECAT_EVT_REQ_DLS_EVT_GET(x) (((uint16_t)(x) & ESC_ECAT_EVT_REQ_DLS_EVT_MASK) >> ESC_ECAT_EVT_REQ_DLS_EVT_SHIFT)

/*
 * DCL_EVT (RO)
 *
 * DC Latch event:
 * 0:No change on DC Latch Inputs
 * 1:At least one change on DC Latch Inputs
 * (Bit is cleared by reading DC Latch event
 * times from ECAT for ECAT-controlled Latch
 * Units, so that Latch 0/1 Status
 * 0x09AE:0x09AF indicates no event)
 */
#define ESC_ECAT_EVT_REQ_DCL_EVT_MASK (0x1U)
#define ESC_ECAT_EVT_REQ_DCL_EVT_SHIFT (0U)
#define ESC_ECAT_EVT_REQ_DCL_EVT_GET(x) (((uint16_t)(x) & ESC_ECAT_EVT_REQ_DCL_EVT_MASK) >> ESC_ECAT_EVT_REQ_DCL_EVT_SHIFT)

/* Bitfield definition for register: AL_EVT_REQ */
/*
 * SM_INT (RO)
 *
 * SyncManager interrupts (SyncManager
 * register offset 0x5, bit [0] or [1]):
 * 0:No SyncManager 0 interrupt
 * 1:SyncManager 0 interrupt pending
 * 0:No SyncManager 1 interrupt
 * 1:SyncManager 1 interrupt pending
 * …
 * 0:No SyncManager 15 interrupt
 * 1:SyncManager 15 interrupt pending
 */
#define ESC_AL_EVT_REQ_SM_INT_MASK (0xFFFF00UL)
#define ESC_AL_EVT_REQ_SM_INT_SHIFT (8U)
#define ESC_AL_EVT_REQ_SM_INT_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_SM_INT_MASK) >> ESC_AL_EVT_REQ_SM_INT_SHIFT)

/*
 * WDG_PD (RO)
 *
 * Watchdog Process Data:
 * 0:Has not expired
 * 1:Has expired
 * (Bit is cleared by reading Watchdog Status
 * Process Data 0x0440 from PDI)
 */
#define ESC_AL_EVT_REQ_WDG_PD_MASK (0x40U)
#define ESC_AL_EVT_REQ_WDG_PD_SHIFT (6U)
#define ESC_AL_EVT_REQ_WDG_PD_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_WDG_PD_MASK) >> ESC_AL_EVT_REQ_WDG_PD_SHIFT)

/*
 * EE_EMU (RO)
 *
 * EEPROM Emulation:
 * 0:No command pending
 * 1:EEPROM command pending
 * (Bit is cleared by acknowledging the
 * command in EEPROM Control/Status
 * register 0x0502:0x0503[10:8] from PDI)
 */
#define ESC_AL_EVT_REQ_EE_EMU_MASK (0x20U)
#define ESC_AL_EVT_REQ_EE_EMU_SHIFT (5U)
#define ESC_AL_EVT_REQ_EE_EMU_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_EE_EMU_MASK) >> ESC_AL_EVT_REQ_EE_EMU_SHIFT)

/*
 * SM_ACT (RO)
 *
 * SyncManager activation register
 * (SyncManager register offset 0x6) changed:
 * 0:No change in any SyncManager
 * 1:At least one SyncManager changed
 * (Bit is cleared by reading SyncManager
 * Activation registers 0x0806 etc. from PDI)
 */
#define ESC_AL_EVT_REQ_SM_ACT_MASK (0x10U)
#define ESC_AL_EVT_REQ_SM_ACT_SHIFT (4U)
#define ESC_AL_EVT_REQ_SM_ACT_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_SM_ACT_MASK) >> ESC_AL_EVT_REQ_SM_ACT_SHIFT)

/*
 * ST_DC_SYNC1 (RO)
 *
 * State of DC SYNC1 (if register
 * 0x0151[7]=1):
 * (Bit is cleared by reading of SYNC1 status
 * 0x098F from PDI, use only in Acknowledge
 * mode)
 */
#define ESC_AL_EVT_REQ_ST_DC_SYNC1_MASK (0x8U)
#define ESC_AL_EVT_REQ_ST_DC_SYNC1_SHIFT (3U)
#define ESC_AL_EVT_REQ_ST_DC_SYNC1_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_ST_DC_SYNC1_MASK) >> ESC_AL_EVT_REQ_ST_DC_SYNC1_SHIFT)

/*
 * ST_DC_SYNC0 (RO)
 *
 * State of DC SYNC0 (if register
 * 0x0151[3]=1):
 * (Bit is cleared by reading SYNC0 status
 * 0x098E from PDI, use only in Acknowledge
 * mode)
 */
#define ESC_AL_EVT_REQ_ST_DC_SYNC0_MASK (0x4U)
#define ESC_AL_EVT_REQ_ST_DC_SYNC0_SHIFT (2U)
#define ESC_AL_EVT_REQ_ST_DC_SYNC0_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_ST_DC_SYNC0_MASK) >> ESC_AL_EVT_REQ_ST_DC_SYNC0_SHIFT)

/*
 * DCL_EVT (RO)
 *
 * DC Latch event:
 * 0:No change on DC Latch Inputs
 * 1:At least one change on DC Latch Inputs
 * (Bit is cleared by reading DC Latch event
 * times from PDI, so that Latch 0/1 Status
 * 0x09AE:0x09AF indicates no event. Available
 * if Latch Unit is PDI-controlled)
 */
#define ESC_AL_EVT_REQ_DCL_EVT_MASK (0x2U)
#define ESC_AL_EVT_REQ_DCL_EVT_SHIFT (1U)
#define ESC_AL_EVT_REQ_DCL_EVT_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_DCL_EVT_MASK) >> ESC_AL_EVT_REQ_DCL_EVT_SHIFT)

/*
 * ALC_EVT (RO)
 *
 * AL Control event:
 * 0:No AL Control Register change
 * 1:AL Control Register has been written3
 * (Bit is cleared by reading AL Control register
 * 0x0120:0x0121 from PDI)
 */
#define ESC_AL_EVT_REQ_ALC_EVT_MASK (0x1U)
#define ESC_AL_EVT_REQ_ALC_EVT_SHIFT (0U)
#define ESC_AL_EVT_REQ_ALC_EVT_GET(x) (((uint32_t)(x) & ESC_AL_EVT_REQ_ALC_EVT_MASK) >> ESC_AL_EVT_REQ_ALC_EVT_SHIFT)

/* Bitfield definition for register array: RX_ERR_CNT */
/*
 * RX_ERR (RO)
 *
 * RX Error counter of Port y (counting is
 * stopped when 0xFF is reached).
 */
#define ESC_RX_ERR_CNT_RX_ERR_MASK (0xFF00U)
#define ESC_RX_ERR_CNT_RX_ERR_SHIFT (8U)
#define ESC_RX_ERR_CNT_RX_ERR_GET(x) (((uint16_t)(x) & ESC_RX_ERR_CNT_RX_ERR_MASK) >> ESC_RX_ERR_CNT_RX_ERR_SHIFT)

/*
 * IVD_FRM (RO)
 *
 * Invalid frame counter of Port y (counting is
 * stopped when 0xFF is reached).
 */
#define ESC_RX_ERR_CNT_IVD_FRM_MASK (0xFFU)
#define ESC_RX_ERR_CNT_IVD_FRM_SHIFT (0U)
#define ESC_RX_ERR_CNT_IVD_FRM_GET(x) (((uint16_t)(x) & ESC_RX_ERR_CNT_IVD_FRM_MASK) >> ESC_RX_ERR_CNT_IVD_FRM_SHIFT)

/* Bitfield definition for register array: FWD_RX_ERR_CNT */
/*
 * ERR_CNT (RO)
 *
 * Forwarded error counter of Port y (counting is
 * stopped when 0xFF is reached).
 */
#define ESC_FWD_RX_ERR_CNT_ERR_CNT_MASK (0xFFU)
#define ESC_FWD_RX_ERR_CNT_ERR_CNT_SHIFT (0U)
#define ESC_FWD_RX_ERR_CNT_ERR_CNT_GET(x) (((uint8_t)(x) & ESC_FWD_RX_ERR_CNT_ERR_CNT_MASK) >> ESC_FWD_RX_ERR_CNT_ERR_CNT_SHIFT)

/* Bitfield definition for register: ECAT_PU_ERR_CNT */
/*
 * CNT (RO)
 *
 * ECAT Processing Unit error counter
 * (counting is stopped when 0xFF is reached).
 * Counts errors of frames passing the
 * Processing Unit.
 */
#define ESC_ECAT_PU_ERR_CNT_CNT_MASK (0xFFU)
#define ESC_ECAT_PU_ERR_CNT_CNT_SHIFT (0U)
#define ESC_ECAT_PU_ERR_CNT_CNT_GET(x) (((uint8_t)(x) & ESC_ECAT_PU_ERR_CNT_CNT_MASK) >> ESC_ECAT_PU_ERR_CNT_CNT_SHIFT)

/* Bitfield definition for register: PDI_ERR_CNT */
/*
 * CNT (RO)
 *
 * PDI Error counter (counting is stopped when
 * 0xFF is reached). Counts if a PDI access has
 * an interface error.
 */
#define ESC_PDI_ERR_CNT_CNT_MASK (0xFFU)
#define ESC_PDI_ERR_CNT_CNT_SHIFT (0U)
#define ESC_PDI_ERR_CNT_CNT_GET(x) (((uint8_t)(x) & ESC_PDI_ERR_CNT_CNT_MASK) >> ESC_PDI_ERR_CNT_CNT_SHIFT)

/* Bitfield definition for register array: LOST_LINK_CNT */
/*
 * CNT (RO)
 *
 * Lost Link counter of Port y (counting is
 * stopped when 0xff is reached). Counts only if
 * port is open and loop is Auto.
 */
#define ESC_LOST_LINK_CNT_CNT_MASK (0xFFU)
#define ESC_LOST_LINK_CNT_CNT_SHIFT (0U)
#define ESC_LOST_LINK_CNT_CNT_GET(x) (((uint8_t)(x) & ESC_LOST_LINK_CNT_CNT_MASK) >> ESC_LOST_LINK_CNT_CNT_SHIFT)

/* Bitfield definition for register: WDG_DIV */
/*
 * DIV (RO)
 *
 * Watchdog divider:Number of 25 MHz tics
 * (minus 2) that represent the basic watchdog
 * increment. (Default value is 100µs = 2498)
 */
#define ESC_WDG_DIV_DIV_MASK (0xFFFFU)
#define ESC_WDG_DIV_DIV_SHIFT (0U)
#define ESC_WDG_DIV_DIV_GET(x) (((uint16_t)(x) & ESC_WDG_DIV_DIV_MASK) >> ESC_WDG_DIV_DIV_SHIFT)

/* Bitfield definition for register: WDG_TIME_PDI */
/*
 * TIME (RO)
 *
 * Watchdog Time PDI:number of basic
 * watchdog increments
 * (Default value with Watchdog divider 100µs
 * means 100ms Watchdog)
 */
#define ESC_WDG_TIME_PDI_TIME_MASK (0xFFFFU)
#define ESC_WDG_TIME_PDI_TIME_SHIFT (0U)
#define ESC_WDG_TIME_PDI_TIME_GET(x) (((uint16_t)(x) & ESC_WDG_TIME_PDI_TIME_MASK) >> ESC_WDG_TIME_PDI_TIME_SHIFT)

/* Bitfield definition for register: WDG_TIME_PDAT */
/*
 * TIME (RO)
 *
 * Watchdog Time Process Data:number of
 * basic watchdog increments
 * (Default value with Watchdog divider 100µs
 * means 100ms Watchdog)
 */
#define ESC_WDG_TIME_PDAT_TIME_MASK (0xFFFFU)
#define ESC_WDG_TIME_PDAT_TIME_SHIFT (0U)
#define ESC_WDG_TIME_PDAT_TIME_GET(x) (((uint16_t)(x) & ESC_WDG_TIME_PDAT_TIME_MASK) >> ESC_WDG_TIME_PDAT_TIME_SHIFT)

/* Bitfield definition for register: WDG_STAT_PDAT */
/*
 * ST (RW)
 *
 * Watchdog Status of Process Data (triggered
 * by SyncManagers)
 * 0:Watchdog Process Data expired
 * 1:Watchdog Process Data is active or
 * disabled
 */
#define ESC_WDG_STAT_PDAT_ST_MASK (0x1U)
#define ESC_WDG_STAT_PDAT_ST_SHIFT (0U)
#define ESC_WDG_STAT_PDAT_ST_SET(x) (((uint16_t)(x) << ESC_WDG_STAT_PDAT_ST_SHIFT) & ESC_WDG_STAT_PDAT_ST_MASK)
#define ESC_WDG_STAT_PDAT_ST_GET(x) (((uint16_t)(x) & ESC_WDG_STAT_PDAT_ST_MASK) >> ESC_WDG_STAT_PDAT_ST_SHIFT)

/* Bitfield definition for register: WDG_CNT_PDAT */
/*
 * CNT (RO)
 *
 * Watchdog Counter Process Data (counting is
 * stopped when 0xFF is reached). Counts if
 * Process Data Watchdog expires.
 */
#define ESC_WDG_CNT_PDAT_CNT_MASK (0xFFU)
#define ESC_WDG_CNT_PDAT_CNT_SHIFT (0U)
#define ESC_WDG_CNT_PDAT_CNT_GET(x) (((uint8_t)(x) & ESC_WDG_CNT_PDAT_CNT_MASK) >> ESC_WDG_CNT_PDAT_CNT_SHIFT)

/* Bitfield definition for register: WDG_CNT_PDI */
/*
 * CNT (RO)
 *
 * Watchdog PDI counter (counting is stopped
 * when 0xFF is reached). Counts if PDI
 * Watchdog expires.
 */
#define ESC_WDG_CNT_PDI_CNT_MASK (0xFFU)
#define ESC_WDG_CNT_PDI_CNT_SHIFT (0U)
#define ESC_WDG_CNT_PDI_CNT_GET(x) (((uint8_t)(x) & ESC_WDG_CNT_PDI_CNT_MASK) >> ESC_WDG_CNT_PDI_CNT_SHIFT)

/* Bitfield definition for register: EEPROM_CFG */
/*
 * FORCE_ECAT (RO)
 *
 * Force ECAT access:
 * 0:Do not change Bit 0x0501[0]
 * 1:Reset Bit 0x0501[0] to 0
 */
#define ESC_EEPROM_CFG_FORCE_ECAT_MASK (0x2U)
#define ESC_EEPROM_CFG_FORCE_ECAT_SHIFT (1U)
#define ESC_EEPROM_CFG_FORCE_ECAT_GET(x) (((uint8_t)(x) & ESC_EEPROM_CFG_FORCE_ECAT_MASK) >> ESC_EEPROM_CFG_FORCE_ECAT_SHIFT)

/*
 * PDI (RO)
 *
 * EEPROM control is offered to PDI:
 * 0:no
 * 1:yes (PDI has EEPROM control)
 */
#define ESC_EEPROM_CFG_PDI_MASK (0x1U)
#define ESC_EEPROM_CFG_PDI_SHIFT (0U)
#define ESC_EEPROM_CFG_PDI_GET(x) (((uint8_t)(x) & ESC_EEPROM_CFG_PDI_MASK) >> ESC_EEPROM_CFG_PDI_SHIFT)

/* Bitfield definition for register: EEPROM_PDI_ACC_STAT */
/*
 * ACCESS (RW)
 *
 * Access to EEPROM:
 * 0:PDI releases EEPROM access
 * 1:PDI takes EEPROM access (PDI has
 * EEPROM control)
 */
#define ESC_EEPROM_PDI_ACC_STAT_ACCESS_MASK (0x1U)
#define ESC_EEPROM_PDI_ACC_STAT_ACCESS_SHIFT (0U)
#define ESC_EEPROM_PDI_ACC_STAT_ACCESS_SET(x) (((uint8_t)(x) << ESC_EEPROM_PDI_ACC_STAT_ACCESS_SHIFT) & ESC_EEPROM_PDI_ACC_STAT_ACCESS_MASK)
#define ESC_EEPROM_PDI_ACC_STAT_ACCESS_GET(x) (((uint8_t)(x) & ESC_EEPROM_PDI_ACC_STAT_ACCESS_MASK) >> ESC_EEPROM_PDI_ACC_STAT_ACCESS_SHIFT)

/* Bitfield definition for register: EEPROM_CTRL_STAT */
/*
 * BUSY (RO)
 *
 * Busy:
 * 0:EEPROM Interface is idle
 * 1:EEPROM Interface is busy
 */
#define ESC_EEPROM_CTRL_STAT_BUSY_MASK (0x8000U)
#define ESC_EEPROM_CTRL_STAT_BUSY_SHIFT (15U)
#define ESC_EEPROM_CTRL_STAT_BUSY_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_BUSY_MASK) >> ESC_EEPROM_CTRL_STAT_BUSY_SHIFT)

/*
 * ERR_WEN (RO)
 *
 * Error Write Enable*3
 * :
 * 0:No error
 * 1:Write Command without Write enable
 */
#define ESC_EEPROM_CTRL_STAT_ERR_WEN_MASK (0x4000U)
#define ESC_EEPROM_CTRL_STAT_ERR_WEN_SHIFT (14U)
#define ESC_EEPROM_CTRL_STAT_ERR_WEN_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_ERR_WEN_MASK) >> ESC_EEPROM_CTRL_STAT_ERR_WEN_SHIFT)

/*
 * ERR_ACK_CMD (RW)
 *
 * Error Acknowledge/Command*3
 * :
 * 0:No error
 * 1:Missing EEPROM acknowledge or invalid
 * command
 * EEPROM emulation only:PDI writes 1 if a temporary
 * failure has occurred.
 */
#define ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK (0x2000U)
#define ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_SHIFT (13U)
#define ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_SET(x) (((uint16_t)(x) << ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_SHIFT) & ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK)
#define ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_MASK) >> ESC_EEPROM_CTRL_STAT_ERR_ACK_CMD_SHIFT)

/*
 * EE_LDS (RO)
 *
 * EEPROM loading status:
 * 0:EEPROM loaded, device information ok
 * 1:EEPROM not loaded, device information not
 * available (EEPROM loading in progress or
 * finished with a failure)
 */
#define ESC_EEPROM_CTRL_STAT_EE_LDS_MASK (0x1000U)
#define ESC_EEPROM_CTRL_STAT_EE_LDS_SHIFT (12U)
#define ESC_EEPROM_CTRL_STAT_EE_LDS_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_EE_LDS_MASK) >> ESC_EEPROM_CTRL_STAT_EE_LDS_SHIFT)

/*
 * CKSM_ERR (RW)
 *
 * Checksum Error in ESC Configuration Area:
 * 0:Checksum ok
 * 1:Checksum error
 * EEPROM emulation for IP Core only:PDI writes 1 if a
 * CRC failure has occurred for a reload command.
 */
#define ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK (0x800U)
#define ESC_EEPROM_CTRL_STAT_CKSM_ERR_SHIFT (11U)
#define ESC_EEPROM_CTRL_STAT_CKSM_ERR_SET(x) (((uint16_t)(x) << ESC_EEPROM_CTRL_STAT_CKSM_ERR_SHIFT) & ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK)
#define ESC_EEPROM_CTRL_STAT_CKSM_ERR_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_CKSM_ERR_MASK) >> ESC_EEPROM_CTRL_STAT_CKSM_ERR_SHIFT)

/*
 * CMD (RW)
 *
 * Command register*2:
 * Write:Initiate command.
 * Read:Currently executed command
 * Commands:
 * 000:No command/EEPROM idle (clear error bits)
 * 001:Read
 * 010:Write
 * 100:Reload
 * Others:Reserved/invalid commands (do not issue)
 * EEPROM emulation only:after execution, PDI writes
 * command value to indicate operation is ready.
 */
#define ESC_EEPROM_CTRL_STAT_CMD_MASK (0x700U)
#define ESC_EEPROM_CTRL_STAT_CMD_SHIFT (8U)
#define ESC_EEPROM_CTRL_STAT_CMD_SET(x) (((uint16_t)(x) << ESC_EEPROM_CTRL_STAT_CMD_SHIFT) & ESC_EEPROM_CTRL_STAT_CMD_MASK)
#define ESC_EEPROM_CTRL_STAT_CMD_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_CMD_MASK) >> ESC_EEPROM_CTRL_STAT_CMD_SHIFT)

/*
 * EE_ALGM (RO)
 *
 * Selected EEPROM Algorithm:
 * 0:1 address byte (1Kbit – 16Kbit EEPROMs)
 * 1:2 address bytes (32Kbit – 4 Mbit EEPROMs)
 */
#define ESC_EEPROM_CTRL_STAT_EE_ALGM_MASK (0x80U)
#define ESC_EEPROM_CTRL_STAT_EE_ALGM_SHIFT (7U)
#define ESC_EEPROM_CTRL_STAT_EE_ALGM_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_EE_ALGM_MASK) >> ESC_EEPROM_CTRL_STAT_EE_ALGM_SHIFT)

/*
 * NUM_RD_BYTE (RO)
 *
 * Supported number of EEPROM read bytes:
 * 0:4 Bytes
 * 1:8 Bytes
 */
#define ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_MASK (0x40U)
#define ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_SHIFT (6U)
#define ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_MASK) >> ESC_EEPROM_CTRL_STAT_NUM_RD_BYTE_SHIFT)

/*
 * EE_EMU (RO)
 *
 * EPROM emulation:
 * 0:Normal operation (I²C interface used)
 * 1:PDI emulates EEPROM (I²C not used)
 */
#define ESC_EEPROM_CTRL_STAT_EE_EMU_MASK (0x20U)
#define ESC_EEPROM_CTRL_STAT_EE_EMU_SHIFT (5U)
#define ESC_EEPROM_CTRL_STAT_EE_EMU_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_EE_EMU_MASK) >> ESC_EEPROM_CTRL_STAT_EE_EMU_SHIFT)

/*
 * ECAT_WEN (RO)
 *
 * ECAT write enable*2
 * :
 * 0:Write requests are disabled
 * 1:Write requests are enabled
 * This bit is always 1 if PDI has EEPROM control.
 */
#define ESC_EEPROM_CTRL_STAT_ECAT_WEN_MASK (0x1U)
#define ESC_EEPROM_CTRL_STAT_ECAT_WEN_SHIFT (0U)
#define ESC_EEPROM_CTRL_STAT_ECAT_WEN_GET(x) (((uint16_t)(x) & ESC_EEPROM_CTRL_STAT_ECAT_WEN_MASK) >> ESC_EEPROM_CTRL_STAT_ECAT_WEN_SHIFT)

/* Bitfield definition for register: EEPROM_ADDR */
/*
 * ADDR (RW)
 *
 * EEPROM Address
 * 0:First word (= 16 bit)
 * 1:Second word
 * …
 * Actually used EEPROM Address bits:
 * [9-0] : EEPROM size up to 16 Kbit
 * [17-0] : EEPROM size 32 Kbit – 4 Mbit
 * [31-0] : EEPROM Emulation
 */
#define ESC_EEPROM_ADDR_ADDR_MASK (0xFFFFFFFFUL)
#define ESC_EEPROM_ADDR_ADDR_SHIFT (0U)
#define ESC_EEPROM_ADDR_ADDR_SET(x) (((uint32_t)(x) << ESC_EEPROM_ADDR_ADDR_SHIFT) & ESC_EEPROM_ADDR_ADDR_MASK)
#define ESC_EEPROM_ADDR_ADDR_GET(x) (((uint32_t)(x) & ESC_EEPROM_ADDR_ADDR_MASK) >> ESC_EEPROM_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: EEPROM_DATA */
/*
 * HI (RW)
 *
 * EEPROM Read data (data read from
 * EEPROM, higher bytes)
 */
#define ESC_EEPROM_DATA_HI_MASK (0xFFFFFFFFFFFF0000ULL)
#define ESC_EEPROM_DATA_HI_SHIFT (16U)
#define ESC_EEPROM_DATA_HI_SET(x) (((uint64_t)(x) << ESC_EEPROM_DATA_HI_SHIFT) & ESC_EEPROM_DATA_HI_MASK)
#define ESC_EEPROM_DATA_HI_GET(x) (((uint64_t)(x) & ESC_EEPROM_DATA_HI_MASK) >> ESC_EEPROM_DATA_HI_SHIFT)

/*
 * LO (RW)
 *
 * EEPROM Write data (data to be written to
 * EEPROM) or
 * EEPROM Read data (data read from
 * EEPROM, lower bytes)
 */
#define ESC_EEPROM_DATA_LO_MASK (0xFFFFU)
#define ESC_EEPROM_DATA_LO_SHIFT (0U)
#define ESC_EEPROM_DATA_LO_SET(x) (((uint64_t)(x) << ESC_EEPROM_DATA_LO_SHIFT) & ESC_EEPROM_DATA_LO_MASK)
#define ESC_EEPROM_DATA_LO_GET(x) (((uint64_t)(x) & ESC_EEPROM_DATA_LO_MASK) >> ESC_EEPROM_DATA_LO_SHIFT)

/* Bitfield definition for register: MII_MNG_CS */
/*
 * BUSY (RO)
 *
 * Busy:
 * 0:MII Management Interface is idle
 * 1:MII Management Interface is busy
 */
#define ESC_MII_MNG_CS_BUSY_MASK (0x8000U)
#define ESC_MII_MNG_CS_BUSY_SHIFT (15U)
#define ESC_MII_MNG_CS_BUSY_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_BUSY_MASK) >> ESC_MII_MNG_CS_BUSY_SHIFT)

/*
 * CMD_ERR (RO)
 *
 * Command error:
 * 0:Last Command was successful
 * 1:Invalid command or write command
 * without Write Enable
 * Cleared by executing a valid command or by
 * writing “00” to Command register bits [9:8].
 */
#define ESC_MII_MNG_CS_CMD_ERR_MASK (0x4000U)
#define ESC_MII_MNG_CS_CMD_ERR_SHIFT (14U)
#define ESC_MII_MNG_CS_CMD_ERR_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_CMD_ERR_MASK) >> ESC_MII_MNG_CS_CMD_ERR_SHIFT)

/*
 * RD_ERR (RO)
 *
 * Read error:
 * 0:No read error
 * 1:Read error occurred (PHY or register
 * not available)
 * Cleared by writing to register 0x0511
 */
#define ESC_MII_MNG_CS_RD_ERR_MASK (0x2000U)
#define ESC_MII_MNG_CS_RD_ERR_SHIFT (13U)
#define ESC_MII_MNG_CS_RD_ERR_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_RD_ERR_MASK) >> ESC_MII_MNG_CS_RD_ERR_SHIFT)

/*
 * CMD (RW)
 *
 * Command register*:
 * Write:Initiate command.
 * Read:Currently executed command
 * 00:No command/MI idle (clear error bits)
 * 01:Read
 * 10:Write
 * Others:Reserved/invalid command (do not
 * issue)
 */
#define ESC_MII_MNG_CS_CMD_MASK (0x300U)
#define ESC_MII_MNG_CS_CMD_SHIFT (8U)
#define ESC_MII_MNG_CS_CMD_SET(x) (((uint16_t)(x) << ESC_MII_MNG_CS_CMD_SHIFT) & ESC_MII_MNG_CS_CMD_MASK)
#define ESC_MII_MNG_CS_CMD_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_CMD_MASK) >> ESC_MII_MNG_CS_CMD_SHIFT)

/*
 * PHY_ADDR (RO)
 *
 * PHY address of port 0
 * (this is equal to the PHY address offset, if the
 * PHY addresses are consecutive)
 * IP Core since V3.0.0/3.00c:
 * Translation 0x0512[7]=0:
 * Register 0x0510[7:3] shows PHY address of
 * port 0
 * Translation 0x0512[7]=1:
 * Register 0x0510[7:3] shows the PHY address
 * which will be used for port 0-3 as requested
 * by 0x0512[4:0] (valid values 0-3)
 */
#define ESC_MII_MNG_CS_PHY_ADDR_MASK (0xF8U)
#define ESC_MII_MNG_CS_PHY_ADDR_SHIFT (3U)
#define ESC_MII_MNG_CS_PHY_ADDR_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_PHY_ADDR_MASK) >> ESC_MII_MNG_CS_PHY_ADDR_SHIFT)

/*
 * LINK_DC (RO)
 *
 * MI link detection and configuration:
 * 0:Disabled for all ports
 * 1:Enabled for at least one MII port, refer
 * to PHY Port Status (0x0518 ff.) for
 * details
 */
#define ESC_MII_MNG_CS_LINK_DC_MASK (0x4U)
#define ESC_MII_MNG_CS_LINK_DC_SHIFT (2U)
#define ESC_MII_MNG_CS_LINK_DC_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_LINK_DC_MASK) >> ESC_MII_MNG_CS_LINK_DC_SHIFT)

/*
 * PDI (RO)
 *
 * Management Interface can be controlled by
 * PDI (registers 0x0516-0x0517):
 * 0:Only ECAT control
 * 1:PDI control possible
 */
#define ESC_MII_MNG_CS_PDI_MASK (0x2U)
#define ESC_MII_MNG_CS_PDI_SHIFT (1U)
#define ESC_MII_MNG_CS_PDI_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_PDI_MASK) >> ESC_MII_MNG_CS_PDI_SHIFT)

/*
 * WEN (RO)
 *
 * Write enable*:
 * 0:Write disabled
 * 1:Write enabled
 * This bit is always 1 if PDI has MI control.
 * ET1100-0000/-0001 exception:
 * Bit is not always 1 if PDI has MI control, and
 * bit is writable by PDI.
 */
#define ESC_MII_MNG_CS_WEN_MASK (0x1U)
#define ESC_MII_MNG_CS_WEN_SHIFT (0U)
#define ESC_MII_MNG_CS_WEN_GET(x) (((uint16_t)(x) & ESC_MII_MNG_CS_WEN_MASK) >> ESC_MII_MNG_CS_WEN_SHIFT)

/* Bitfield definition for register: PHY_ADDR */
/*
 * SHOW (RW)
 *
 * Target PHY Address translation:
 * 0:Enabled
 * 1:Disabled
 * Refer to 0x0512[4:0] and 0x0510[7:3] for
 * details.
 */
#define ESC_PHY_ADDR_SHOW_MASK (0x80U)
#define ESC_PHY_ADDR_SHOW_SHIFT (7U)
#define ESC_PHY_ADDR_SHOW_SET(x) (((uint8_t)(x) << ESC_PHY_ADDR_SHOW_SHIFT) & ESC_PHY_ADDR_SHOW_MASK)
#define ESC_PHY_ADDR_SHOW_GET(x) (((uint8_t)(x) & ESC_PHY_ADDR_SHOW_MASK) >> ESC_PHY_ADDR_SHOW_SHIFT)

/*
 * ADDR (RW)
 *
 * Target PHY Address
 * Translation 0x0512[7]=0:
 * 0-3:Target PHY Addresses 0-3 are used
 * to access the PHYs at port 0-3, when
 * the PHY addresses are properly
 * configured
 * 4-31:The configured PHY address of port 0
 * (PHY address offset) is added to the
 * Target PHY Address values 4-31
 * when accessing a PHY
 * Translation 0x0512[7]=1:
 * 0-31:Target PHY Addresses is used when
 * accessing a PHY without translation
 */
#define ESC_PHY_ADDR_ADDR_MASK (0x1FU)
#define ESC_PHY_ADDR_ADDR_SHIFT (0U)
#define ESC_PHY_ADDR_ADDR_SET(x) (((uint8_t)(x) << ESC_PHY_ADDR_ADDR_SHIFT) & ESC_PHY_ADDR_ADDR_MASK)
#define ESC_PHY_ADDR_ADDR_GET(x) (((uint8_t)(x) & ESC_PHY_ADDR_ADDR_MASK) >> ESC_PHY_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: PHY_REG_ADDR */
/*
 * ADDR (RW)
 *
 * Address of PHY Register that shall be
 * read/written
 */
#define ESC_PHY_REG_ADDR_ADDR_MASK (0x1FU)
#define ESC_PHY_REG_ADDR_ADDR_SHIFT (0U)
#define ESC_PHY_REG_ADDR_ADDR_SET(x) (((uint8_t)(x) << ESC_PHY_REG_ADDR_ADDR_SHIFT) & ESC_PHY_REG_ADDR_ADDR_MASK)
#define ESC_PHY_REG_ADDR_ADDR_GET(x) (((uint8_t)(x) & ESC_PHY_REG_ADDR_ADDR_MASK) >> ESC_PHY_REG_ADDR_ADDR_SHIFT)

/* Bitfield definition for register: PHY_DATA */
/*
 * DATA (RW)
 *
 * PHY Read/Write Data
 */
#define ESC_PHY_DATA_DATA_MASK (0xFFFFU)
#define ESC_PHY_DATA_DATA_SHIFT (0U)
#define ESC_PHY_DATA_DATA_SET(x) (((uint16_t)(x) << ESC_PHY_DATA_DATA_SHIFT) & ESC_PHY_DATA_DATA_MASK)
#define ESC_PHY_DATA_DATA_GET(x) (((uint16_t)(x) & ESC_PHY_DATA_DATA_MASK) >> ESC_PHY_DATA_DATA_SHIFT)

/* Bitfield definition for register: MIIM_ECAT_ACC_STAT */
/*
 * ACC (RO)
 *
 * Access to MII management:
 * 0:ECAT enables PDI takeover of MII
 * management interface
 * 1:ECAT claims exclusive access to MII
 * management interface
 */
#define ESC_MIIM_ECAT_ACC_STAT_ACC_MASK (0x1U)
#define ESC_MIIM_ECAT_ACC_STAT_ACC_SHIFT (0U)
#define ESC_MIIM_ECAT_ACC_STAT_ACC_GET(x) (((uint8_t)(x) & ESC_MIIM_ECAT_ACC_STAT_ACC_MASK) >> ESC_MIIM_ECAT_ACC_STAT_ACC_SHIFT)

/* Bitfield definition for register: MIIM_PDI_ACC_STAT */
/*
 * FORCE (RO)
 *
 * Force PDI Access State:
 * 0:Do not change Bit 0x0517[0]
 * 1:Reset Bit 0x0517[0] to 0
 */
#define ESC_MIIM_PDI_ACC_STAT_FORCE_MASK (0x2U)
#define ESC_MIIM_PDI_ACC_STAT_FORCE_SHIFT (1U)
#define ESC_MIIM_PDI_ACC_STAT_FORCE_GET(x) (((uint8_t)(x) & ESC_MIIM_PDI_ACC_STAT_FORCE_MASK) >> ESC_MIIM_PDI_ACC_STAT_FORCE_SHIFT)

/*
 * ACC (RW)
 *
 * Access to MII management:
 * 0:ECAT has access to MII management
 * 1:PDI has access to MII management
 */
#define ESC_MIIM_PDI_ACC_STAT_ACC_MASK (0x1U)
#define ESC_MIIM_PDI_ACC_STAT_ACC_SHIFT (0U)
#define ESC_MIIM_PDI_ACC_STAT_ACC_SET(x) (((uint8_t)(x) << ESC_MIIM_PDI_ACC_STAT_ACC_SHIFT) & ESC_MIIM_PDI_ACC_STAT_ACC_MASK)
#define ESC_MIIM_PDI_ACC_STAT_ACC_GET(x) (((uint8_t)(x) & ESC_MIIM_PDI_ACC_STAT_ACC_MASK) >> ESC_MIIM_PDI_ACC_STAT_ACC_SHIFT)

/* Bitfield definition for register array: PHY_STAT */
/*
 * PCU (RW)
 *
 * PHY configuration updated:
 * 0:No update
 * 1:PHY configuration was updated
 * Cleared by writing any value to at least one
 * of the PHY Port y Status registers.
 */
#define ESC_PHY_STAT_PCU_MASK (0x20U)
#define ESC_PHY_STAT_PCU_SHIFT (5U)
#define ESC_PHY_STAT_PCU_SET(x) (((uint8_t)(x) << ESC_PHY_STAT_PCU_SHIFT) & ESC_PHY_STAT_PCU_MASK)
#define ESC_PHY_STAT_PCU_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_PCU_MASK) >> ESC_PHY_STAT_PCU_SHIFT)

/*
 * LPE (RO)
 *
 * Link partner error:
 * 0:No error detected
 * 1:Link partner error
 */
#define ESC_PHY_STAT_LPE_MASK (0x10U)
#define ESC_PHY_STAT_LPE_SHIFT (4U)
#define ESC_PHY_STAT_LPE_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_LPE_MASK) >> ESC_PHY_STAT_LPE_SHIFT)

/*
 * RE (RW)
 *
 * Read error:
 * 0:No read error occurred
 * 1:A read error has occurred
 * Cleared by writing any value to at least one
 * of the PHY Port y Status registers.
 */
#define ESC_PHY_STAT_RE_MASK (0x8U)
#define ESC_PHY_STAT_RE_SHIFT (3U)
#define ESC_PHY_STAT_RE_SET(x) (((uint8_t)(x) << ESC_PHY_STAT_RE_SHIFT) & ESC_PHY_STAT_RE_MASK)
#define ESC_PHY_STAT_RE_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_RE_MASK) >> ESC_PHY_STAT_RE_SHIFT)

/*
 * LSE (RO)
 *
 * Link status error:
 * 0:No error
 * 1:Link error, link inhibited
 */
#define ESC_PHY_STAT_LSE_MASK (0x4U)
#define ESC_PHY_STAT_LSE_SHIFT (2U)
#define ESC_PHY_STAT_LSE_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_LSE_MASK) >> ESC_PHY_STAT_LSE_SHIFT)

/*
 * LS (RO)
 *
 * Link status (100 Mbit/s, Full Duplex, Auto
 * negotiation):
 * 0:No link
 * 1:Link detected
 */
#define ESC_PHY_STAT_LS_MASK (0x2U)
#define ESC_PHY_STAT_LS_SHIFT (1U)
#define ESC_PHY_STAT_LS_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_LS_MASK) >> ESC_PHY_STAT_LS_SHIFT)

/*
 * PLS (RO)
 *
 * Physical link status (PHY status register 1.2):
 * 0:No physical link
 * 1:Physical link detected
 */
#define ESC_PHY_STAT_PLS_MASK (0x1U)
#define ESC_PHY_STAT_PLS_SHIFT (0U)
#define ESC_PHY_STAT_PLS_GET(x) (((uint8_t)(x) & ESC_PHY_STAT_PLS_MASK) >> ESC_PHY_STAT_PLS_SHIFT)

/* Bitfield definition for register of struct array FMMU: LOGIC_START_ADDR */
/*
 * ADDR (RO)
 *
 * Logical start address within the EtherCAT
 * Address Space.
 */
#define ESC_FMMU_LOGIC_START_ADDR_ADDR_MASK (0xFFFFFFFFUL)
#define ESC_FMMU_LOGIC_START_ADDR_ADDR_SHIFT (0U)
#define ESC_FMMU_LOGIC_START_ADDR_ADDR_GET(x) (((uint32_t)(x) & ESC_FMMU_LOGIC_START_ADDR_ADDR_MASK) >> ESC_FMMU_LOGIC_START_ADDR_ADDR_SHIFT)

/* Bitfield definition for register of struct array FMMU: LENGTH */
/*
 * OFFSET (RO)
 *
 * Offset from the first logical FMMU byte to the
 * last FMMU byte + 1 (e.g., if two bytes are
 * used, then this parameter shall contain 2)
 */
#define ESC_FMMU_LENGTH_OFFSET_MASK (0xFFFFU)
#define ESC_FMMU_LENGTH_OFFSET_SHIFT (0U)
#define ESC_FMMU_LENGTH_OFFSET_GET(x) (((uint16_t)(x) & ESC_FMMU_LENGTH_OFFSET_MASK) >> ESC_FMMU_LENGTH_OFFSET_SHIFT)

/* Bitfield definition for register of struct array FMMU: LOGIC_START_BIT */
/*
 * START (RO)
 *
 * Logical starting bit that shall be mapped (bits
 * are counted from least significant bit 0 to
 * most significant bit 7)
 */
#define ESC_FMMU_LOGIC_START_BIT_START_MASK (0x7U)
#define ESC_FMMU_LOGIC_START_BIT_START_SHIFT (0U)
#define ESC_FMMU_LOGIC_START_BIT_START_GET(x) (((uint8_t)(x) & ESC_FMMU_LOGIC_START_BIT_START_MASK) >> ESC_FMMU_LOGIC_START_BIT_START_SHIFT)

/* Bitfield definition for register of struct array FMMU: LOGIC_STOP_BIT */
/*
 * STOP (RO)
 *
 * Last logical bit that shall be mapped (bits are
 * counted from least significant bit 0 to most
 * significant bit 7)
 */
#define ESC_FMMU_LOGIC_STOP_BIT_STOP_MASK (0x7U)
#define ESC_FMMU_LOGIC_STOP_BIT_STOP_SHIFT (0U)
#define ESC_FMMU_LOGIC_STOP_BIT_STOP_GET(x) (((uint8_t)(x) & ESC_FMMU_LOGIC_STOP_BIT_STOP_MASK) >> ESC_FMMU_LOGIC_STOP_BIT_STOP_SHIFT)

/* Bitfield definition for register of struct array FMMU: PHYSICAL_START_ADDR */
/*
 * ADDR (RO)
 *
 * Physical Start Address (mapped to logical
 * Start address)
 */
#define ESC_FMMU_PHYSICAL_START_ADDR_ADDR_MASK (0xFFFFU)
#define ESC_FMMU_PHYSICAL_START_ADDR_ADDR_SHIFT (0U)
#define ESC_FMMU_PHYSICAL_START_ADDR_ADDR_GET(x) (((uint16_t)(x) & ESC_FMMU_PHYSICAL_START_ADDR_ADDR_MASK) >> ESC_FMMU_PHYSICAL_START_ADDR_ADDR_SHIFT)

/* Bitfield definition for register of struct array FMMU: PHYSICAL_START_BIT */
/*
 * START (RO)
 *
 * Physical starting bit as target of logical start
 * bit mapping (bits are counted from least
 * significant bit 0 to most significant bit 7)
 */
#define ESC_FMMU_PHYSICAL_START_BIT_START_MASK (0x7U)
#define ESC_FMMU_PHYSICAL_START_BIT_START_SHIFT (0U)
#define ESC_FMMU_PHYSICAL_START_BIT_START_GET(x) (((uint8_t)(x) & ESC_FMMU_PHYSICAL_START_BIT_START_MASK) >> ESC_FMMU_PHYSICAL_START_BIT_START_SHIFT)

/* Bitfield definition for register of struct array FMMU: TYPE */
/*
 * MAP_WR (RO)
 *
 * 0:Ignore mapping for write accesses
 * 1:Use mapping for write accesses
 */
#define ESC_FMMU_TYPE_MAP_WR_MASK (0x2U)
#define ESC_FMMU_TYPE_MAP_WR_SHIFT (1U)
#define ESC_FMMU_TYPE_MAP_WR_GET(x) (((uint8_t)(x) & ESC_FMMU_TYPE_MAP_WR_MASK) >> ESC_FMMU_TYPE_MAP_WR_SHIFT)

/*
 * MAP_RD (RO)
 *
 * 0:Ignore mapping for read accesses
 * 1:Use mapping for read accesses
 */
#define ESC_FMMU_TYPE_MAP_RD_MASK (0x1U)
#define ESC_FMMU_TYPE_MAP_RD_SHIFT (0U)
#define ESC_FMMU_TYPE_MAP_RD_GET(x) (((uint8_t)(x) & ESC_FMMU_TYPE_MAP_RD_MASK) >> ESC_FMMU_TYPE_MAP_RD_SHIFT)

/* Bitfield definition for register of struct array FMMU: ACTIVATE */
/*
 * ACT (RO)
 *
 * 0:FMMU deactivated
 * 1:FMMU activated. FMMU checks
 * logically addressed blocks to be
 * mapped according to configured
 * mapping
 */
#define ESC_FMMU_ACTIVATE_ACT_MASK (0x1U)
#define ESC_FMMU_ACTIVATE_ACT_SHIFT (0U)
#define ESC_FMMU_ACTIVATE_ACT_GET(x) (((uint8_t)(x) & ESC_FMMU_ACTIVATE_ACT_MASK) >> ESC_FMMU_ACTIVATE_ACT_SHIFT)

/* Bitfield definition for register of struct array SYNCM: PHYSICAL_START_ADDR */
/*
 * ADDR (RO)
 *
 * First byte that will be handled by
 * SyncManager
 */
#define ESC_SYNCM_PHYSICAL_START_ADDR_ADDR_MASK (0xFFFFU)
#define ESC_SYNCM_PHYSICAL_START_ADDR_ADDR_SHIFT (0U)
#define ESC_SYNCM_PHYSICAL_START_ADDR_ADDR_GET(x) (((uint16_t)(x) & ESC_SYNCM_PHYSICAL_START_ADDR_ADDR_MASK) >> ESC_SYNCM_PHYSICAL_START_ADDR_ADDR_SHIFT)

/* Bitfield definition for register of struct array SYNCM: LENGTH */
/*
 * LEN (RO)
 *
 * Number of bytes assigned to SyncManager
 * (shall be greater than 1, otherwise
 * SyncManager is not activated. If set to 1, only
 * Watchdog Trigger is generated if configured)
 */
#define ESC_SYNCM_LENGTH_LEN_MASK (0xFFFFU)
#define ESC_SYNCM_LENGTH_LEN_SHIFT (0U)
#define ESC_SYNCM_LENGTH_LEN_GET(x) (((uint16_t)(x) & ESC_SYNCM_LENGTH_LEN_MASK) >> ESC_SYNCM_LENGTH_LEN_SHIFT)

/* Bitfield definition for register of struct array SYNCM: CONTROL */
/*
 * WDG_TRG_EN (RO)
 *
 * Watchdog Trigger Enable:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_SYNCM_CONTROL_WDG_TRG_EN_MASK (0x40U)
#define ESC_SYNCM_CONTROL_WDG_TRG_EN_SHIFT (6U)
#define ESC_SYNCM_CONTROL_WDG_TRG_EN_GET(x) (((uint8_t)(x) & ESC_SYNCM_CONTROL_WDG_TRG_EN_MASK) >> ESC_SYNCM_CONTROL_WDG_TRG_EN_SHIFT)

/*
 * INT_AL (RO)
 *
 * Interrupt in AL Event Request Register:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_SYNCM_CONTROL_INT_AL_MASK (0x20U)
#define ESC_SYNCM_CONTROL_INT_AL_SHIFT (5U)
#define ESC_SYNCM_CONTROL_INT_AL_GET(x) (((uint8_t)(x) & ESC_SYNCM_CONTROL_INT_AL_MASK) >> ESC_SYNCM_CONTROL_INT_AL_SHIFT)

/*
 * INT_ECAT (RO)
 *
 * Interrupt in ECAT Event Request Register:
 * 0:Disabled
 * 1:Enabled
 */
#define ESC_SYNCM_CONTROL_INT_ECAT_MASK (0x10U)
#define ESC_SYNCM_CONTROL_INT_ECAT_SHIFT (4U)
#define ESC_SYNCM_CONTROL_INT_ECAT_GET(x) (((uint8_t)(x) & ESC_SYNCM_CONTROL_INT_ECAT_MASK) >> ESC_SYNCM_CONTROL_INT_ECAT_SHIFT)

/*
 * DIR (RO)
 *
 * Direction:
 * 00:Read:ECAT read access, PDI write
 * access.
 * 01:Write:ECAT write access, PDI read
 * access.
 * 10:Reserved
 * 11:Reserved
 */
#define ESC_SYNCM_CONTROL_DIR_MASK (0xCU)
#define ESC_SYNCM_CONTROL_DIR_SHIFT (2U)
#define ESC_SYNCM_CONTROL_DIR_GET(x) (((uint8_t)(x) & ESC_SYNCM_CONTROL_DIR_MASK) >> ESC_SYNCM_CONTROL_DIR_SHIFT)

/*
 * OP_MODE (RO)
 *
 * Operation Mode:
 * 00:Buffered (3 buffer mode)
 * 01:Reserved
 * 10:Mailbox (Single buffer mode)
 * 11:Reserved
 */
#define ESC_SYNCM_CONTROL_OP_MODE_MASK (0x3U)
#define ESC_SYNCM_CONTROL_OP_MODE_SHIFT (0U)
#define ESC_SYNCM_CONTROL_OP_MODE_GET(x) (((uint8_t)(x) & ESC_SYNCM_CONTROL_OP_MODE_MASK) >> ESC_SYNCM_CONTROL_OP_MODE_SHIFT)

/* Bitfield definition for register of struct array SYNCM: STATUS */
/*
 * WB_INUSE (RO)
 *
 * Write buffer in use (opened)
 */
#define ESC_SYNCM_STATUS_WB_INUSE_MASK (0x80U)
#define ESC_SYNCM_STATUS_WB_INUSE_SHIFT (7U)
#define ESC_SYNCM_STATUS_WB_INUSE_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_WB_INUSE_MASK) >> ESC_SYNCM_STATUS_WB_INUSE_SHIFT)

/*
 * RB_INUSE (RO)
 *
 * Read buffer in use (opened)
 */
#define ESC_SYNCM_STATUS_RB_INUSE_MASK (0x40U)
#define ESC_SYNCM_STATUS_RB_INUSE_SHIFT (6U)
#define ESC_SYNCM_STATUS_RB_INUSE_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_RB_INUSE_MASK) >> ESC_SYNCM_STATUS_RB_INUSE_SHIFT)

/*
 * BUF_MODE (RO)
 *
 * Buffered mode:buffer status (last written
 * buffer):
 * 00:1
 * st buffer
 * 01:2
 * nd buffer
 * 10:3
 * rd buffer
 * 11:(no buffer written)
 * Mailbox mode:reserved
 */
#define ESC_SYNCM_STATUS_BUF_MODE_MASK (0x30U)
#define ESC_SYNCM_STATUS_BUF_MODE_SHIFT (4U)
#define ESC_SYNCM_STATUS_BUF_MODE_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_BUF_MODE_MASK) >> ESC_SYNCM_STATUS_BUF_MODE_SHIFT)

/*
 * MBX_MODE (RO)
 *
 * Mailbox mode:mailbox status:
 * 0:Mailbox empty
 * 1:Mailbox full
 * Buffered mode:reserved
 */
#define ESC_SYNCM_STATUS_MBX_MODE_MASK (0x8U)
#define ESC_SYNCM_STATUS_MBX_MODE_SHIFT (3U)
#define ESC_SYNCM_STATUS_MBX_MODE_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_MBX_MODE_MASK) >> ESC_SYNCM_STATUS_MBX_MODE_SHIFT)

/*
 * INT_RD (RO)
 *
 * Interrupt Read:
 * 1:Interrupt after buffer was completely and
 * successfully read
 * 0:Interrupt cleared after first byte of buffer
 * was written
 * NOTE:This interrupt is signalled to the writing
 * side if enabled in the SM Control register
 */
#define ESC_SYNCM_STATUS_INT_RD_MASK (0x2U)
#define ESC_SYNCM_STATUS_INT_RD_SHIFT (1U)
#define ESC_SYNCM_STATUS_INT_RD_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_INT_RD_MASK) >> ESC_SYNCM_STATUS_INT_RD_SHIFT)

/*
 * INT_WR (RO)
 *
 * Interrupt Write:
 * 1:Interrupt after buffer was completely and
 * successfully written
 * 0:Interrupt cleared after first byte of buffer
 * was read
 * NOTE:This interrupt is signalled to the reading
 * side if enabled in the SM Control register
 */
#define ESC_SYNCM_STATUS_INT_WR_MASK (0x1U)
#define ESC_SYNCM_STATUS_INT_WR_SHIFT (0U)
#define ESC_SYNCM_STATUS_INT_WR_GET(x) (((uint8_t)(x) & ESC_SYNCM_STATUS_INT_WR_MASK) >> ESC_SYNCM_STATUS_INT_WR_SHIFT)

/* Bitfield definition for register of struct array SYNCM: ACTIVATE */
/*
 * LATCH_PDI (RO)
 *
 * Latch Event PDI:
 * 0:No
 * 1:Generate Latch events when PDI issues
 * a buffer exchange or when PDI
 * accesses buffer start address
 */
#define ESC_SYNCM_ACTIVATE_LATCH_PDI_MASK (0x80U)
#define ESC_SYNCM_ACTIVATE_LATCH_PDI_SHIFT (7U)
#define ESC_SYNCM_ACTIVATE_LATCH_PDI_GET(x) (((uint8_t)(x) & ESC_SYNCM_ACTIVATE_LATCH_PDI_MASK) >> ESC_SYNCM_ACTIVATE_LATCH_PDI_SHIFT)

/*
 * LATCH_ECAT (RO)
 *
 * Latch Event ECAT:
 * 0:No
 * 1:Generate Latch event when EtherCAT
 * master issues a buffer exchange
 */
#define ESC_SYNCM_ACTIVATE_LATCH_ECAT_MASK (0x40U)
#define ESC_SYNCM_ACTIVATE_LATCH_ECAT_SHIFT (6U)
#define ESC_SYNCM_ACTIVATE_LATCH_ECAT_GET(x) (((uint8_t)(x) & ESC_SYNCM_ACTIVATE_LATCH_ECAT_MASK) >> ESC_SYNCM_ACTIVATE_LATCH_ECAT_SHIFT)

/*
 * REPEAT (RO)
 *
 * Repeat Request:
 * A toggle of Repeat Request means that a
 * mailbox retry is needed (primarily used in
 * conjunction with ECAT Read Mailbox)
 */
#define ESC_SYNCM_ACTIVATE_REPEAT_MASK (0x2U)
#define ESC_SYNCM_ACTIVATE_REPEAT_SHIFT (1U)
#define ESC_SYNCM_ACTIVATE_REPEAT_GET(x) (((uint8_t)(x) & ESC_SYNCM_ACTIVATE_REPEAT_MASK) >> ESC_SYNCM_ACTIVATE_REPEAT_SHIFT)

/*
 * EN (RW)
 *
 * SyncManager Enable/Disable:
 * 0:Disable:Access to Memory without
 * SyncManager control
 * 1:Enable:SyncManager is active and
 * controls Memory area set in
 * configuration
 */
#define ESC_SYNCM_ACTIVATE_EN_MASK (0x1U)
#define ESC_SYNCM_ACTIVATE_EN_SHIFT (0U)
#define ESC_SYNCM_ACTIVATE_EN_SET(x) (((uint8_t)(x) << ESC_SYNCM_ACTIVATE_EN_SHIFT) & ESC_SYNCM_ACTIVATE_EN_MASK)
#define ESC_SYNCM_ACTIVATE_EN_GET(x) (((uint8_t)(x) & ESC_SYNCM_ACTIVATE_EN_MASK) >> ESC_SYNCM_ACTIVATE_EN_SHIFT)

/* Bitfield definition for register of struct array SYNCM: PDI_CTRL */
/*
 * REPEAT_ACK (RW)
 *
 * Repeat Ack:
 * If this is set to the same value as that set by
 * Repeat Request, the PDI acknowledges the
 * execution of a previous set Repeat request.
 */
#define ESC_SYNCM_PDI_CTRL_REPEAT_ACK_MASK (0x2U)
#define ESC_SYNCM_PDI_CTRL_REPEAT_ACK_SHIFT (1U)
#define ESC_SYNCM_PDI_CTRL_REPEAT_ACK_SET(x) (((uint8_t)(x) << ESC_SYNCM_PDI_CTRL_REPEAT_ACK_SHIFT) & ESC_SYNCM_PDI_CTRL_REPEAT_ACK_MASK)
#define ESC_SYNCM_PDI_CTRL_REPEAT_ACK_GET(x) (((uint8_t)(x) & ESC_SYNCM_PDI_CTRL_REPEAT_ACK_MASK) >> ESC_SYNCM_PDI_CTRL_REPEAT_ACK_SHIFT)

/*
 * DEACT (RW)
 *
 * Deactivate SyncManager:
 * Read:
 * 0:Normal operation, SyncManager
 * activated.
 * 1:SyncManager deactivated and reset.
 * SyncManager locks access to Memory
 * area.
 * Write:
 * 0:Activate SyncManager
 * 1:Request SyncManager deactivation
 * NOTE:Writing 1 is delayed until the end of the
 * frame, which is currently processed.
 */
#define ESC_SYNCM_PDI_CTRL_DEACT_MASK (0x1U)
#define ESC_SYNCM_PDI_CTRL_DEACT_SHIFT (0U)
#define ESC_SYNCM_PDI_CTRL_DEACT_SET(x) (((uint8_t)(x) << ESC_SYNCM_PDI_CTRL_DEACT_SHIFT) & ESC_SYNCM_PDI_CTRL_DEACT_MASK)
#define ESC_SYNCM_PDI_CTRL_DEACT_GET(x) (((uint8_t)(x) & ESC_SYNCM_PDI_CTRL_DEACT_MASK) >> ESC_SYNCM_PDI_CTRL_DEACT_SHIFT)

/* Bitfield definition for register array: RCV_TIME */
/*
 * LT (RO)
 *
 * Local time at the beginning of the last receive
 * frame containing a write access to register
 * 0x0900.
 */
#define ESC_RCV_TIME_LT_MASK (0xFFFFFF00UL)
#define ESC_RCV_TIME_LT_SHIFT (8U)
#define ESC_RCV_TIME_LT_GET(x) (((uint32_t)(x) & ESC_RCV_TIME_LT_MASK) >> ESC_RCV_TIME_LT_SHIFT)

/*
 * REQ (RO)
 *
 * Write:
 * A write access to register 0x0900 with
 * BWR or FPWR latches the local time at
 * the beginning of the receive frame (start
 * first bit of preamble) at each port.
 * Write (ESC20, ET1200 exception):
 * A write access latches the local time at
 * the beginning of the receive frame at
 * port 0. It enables the time stamping at
 * the other ports.
 * Read:
 * Local time at the beginning of the last
 * receive frame containing a write access
 * to this register.
 * NOTE:FPWR requires an address match for
 * accessing this register like any FPWR command.
 * All write commands with address match will
 * increment the working counter (e.g., APWR), but
 * they will not trigger receive time latching.
 */
#define ESC_RCV_TIME_REQ_MASK (0xFFU)
#define ESC_RCV_TIME_REQ_SHIFT (0U)
#define ESC_RCV_TIME_REQ_GET(x) (((uint32_t)(x) & ESC_RCV_TIME_REQ_MASK) >> ESC_RCV_TIME_REQ_SHIFT)

/* Bitfield definition for register: SYS_TIME */
/*
 * ST (RW)
 *
 */
#define ESC_SYS_TIME_ST_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_SYS_TIME_ST_SHIFT (0U)
#define ESC_SYS_TIME_ST_SET(x) (((uint64_t)(x) << ESC_SYS_TIME_ST_SHIFT) & ESC_SYS_TIME_ST_MASK)
#define ESC_SYS_TIME_ST_GET(x) (((uint64_t)(x) & ESC_SYS_TIME_ST_MASK) >> ESC_SYS_TIME_ST_SHIFT)

/* Bitfield definition for register: RCVT_ECAT_PU */
/*
 * LT (RO)
 *
 * Local time at the beginning of a frame (start
 * first bit of preamble) received at the ECAT
 * Processing Unit containing a write access to
 * register 0x0900
 * NOTE:E.g., if port 0 is open, this register reflects
 * the Receive Time Port 0 as a 64 Bit value.
 * Any valid EtherCAT write access to register
 * 0x0900 triggers latching, not only BWR/FPWR
 * commands as with register 0x0900.
 */
#define ESC_RCVT_ECAT_PU_LT_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_RCVT_ECAT_PU_LT_SHIFT (0U)
#define ESC_RCVT_ECAT_PU_LT_GET(x) (((uint64_t)(x) & ESC_RCVT_ECAT_PU_LT_MASK) >> ESC_RCVT_ECAT_PU_LT_SHIFT)

/* Bitfield definition for register: SYS_TIME_OFFSET */
/*
 * OFFSET (RW)
 *
 * Difference between local time and System
 * Time. Offset is added to the local time.
 */
#define ESC_SYS_TIME_OFFSET_OFFSET_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_SYS_TIME_OFFSET_OFFSET_SHIFT (0U)
#define ESC_SYS_TIME_OFFSET_OFFSET_SET(x) (((uint64_t)(x) << ESC_SYS_TIME_OFFSET_OFFSET_SHIFT) & ESC_SYS_TIME_OFFSET_OFFSET_MASK)
#define ESC_SYS_TIME_OFFSET_OFFSET_GET(x) (((uint64_t)(x) & ESC_SYS_TIME_OFFSET_OFFSET_MASK) >> ESC_SYS_TIME_OFFSET_OFFSET_SHIFT)

/* Bitfield definition for register: SYS_TIME_DELAY */
/*
 * DLY (RW)
 *
 * Delay between Reference Clock and the
 * ESC
 */
#define ESC_SYS_TIME_DELAY_DLY_MASK (0xFFFFFFFFUL)
#define ESC_SYS_TIME_DELAY_DLY_SHIFT (0U)
#define ESC_SYS_TIME_DELAY_DLY_SET(x) (((uint32_t)(x) << ESC_SYS_TIME_DELAY_DLY_SHIFT) & ESC_SYS_TIME_DELAY_DLY_MASK)
#define ESC_SYS_TIME_DELAY_DLY_GET(x) (((uint32_t)(x) & ESC_SYS_TIME_DELAY_DLY_MASK) >> ESC_SYS_TIME_DELAY_DLY_SHIFT)

/* Bitfield definition for register: SYS_TIME_DIFF */
/*
 * DIFF (RO)
 *
 * 0:Local copy of System Time less than
 * received System Time
 * 1:Local copy of System Time greater than
 * or equal to received System Time
 */
#define ESC_SYS_TIME_DIFF_DIFF_MASK (0x80000000UL)
#define ESC_SYS_TIME_DIFF_DIFF_SHIFT (31U)
#define ESC_SYS_TIME_DIFF_DIFF_GET(x) (((uint32_t)(x) & ESC_SYS_TIME_DIFF_DIFF_MASK) >> ESC_SYS_TIME_DIFF_DIFF_SHIFT)

/*
 * NUM (RO)
 *
 * Mean difference between local copy of
 * System Time and received System Time
 * values
 * Difference = Received System Time –
 * local copy of System Time
 */
#define ESC_SYS_TIME_DIFF_NUM_MASK (0x7FFFFFFFUL)
#define ESC_SYS_TIME_DIFF_NUM_SHIFT (0U)
#define ESC_SYS_TIME_DIFF_NUM_GET(x) (((uint32_t)(x) & ESC_SYS_TIME_DIFF_NUM_MASK) >> ESC_SYS_TIME_DIFF_NUM_SHIFT)

/* Bitfield definition for register: SPD_CNT_START */
/*
 * BW (RW)
 *
 * Bandwidth for adjustment of local copy of
 * System Time (larger values → smaller
 * bandwidth and smoother adjustment)
 * A write access resets System Time
 * Difference (0x092C:0x092F) and Speed
 * Counter Diff (0x0932:0x0933).
 * Valid values:0x0080 to 0x3FFF
 */
#define ESC_SPD_CNT_START_BW_MASK (0x7FFFU)
#define ESC_SPD_CNT_START_BW_SHIFT (0U)
#define ESC_SPD_CNT_START_BW_SET(x) (((uint16_t)(x) << ESC_SPD_CNT_START_BW_SHIFT) & ESC_SPD_CNT_START_BW_MASK)
#define ESC_SPD_CNT_START_BW_GET(x) (((uint16_t)(x) & ESC_SPD_CNT_START_BW_MASK) >> ESC_SPD_CNT_START_BW_SHIFT)

/* Bitfield definition for register: SPD_CNT_DIFF */
/*
 * DIFF (RO)
 *
 * Representation of the deviation between
 * local clock period and Reference Clock's
 * clock period (representation:two's
 * complement)
 * Range:±(Speed Counter Start – 0x7F)
 */
#define ESC_SPD_CNT_DIFF_DIFF_MASK (0xFFFFU)
#define ESC_SPD_CNT_DIFF_DIFF_SHIFT (0U)
#define ESC_SPD_CNT_DIFF_DIFF_GET(x) (((uint16_t)(x) & ESC_SPD_CNT_DIFF_DIFF_MASK) >> ESC_SPD_CNT_DIFF_DIFF_SHIFT)

/* Bitfield definition for register: SYS_TIME_DIFF_FD */
/*
 * DEPTH (RW)
 *
 * Filter depth for averaging the received
 * System Time deviation
 * IP Core since V2.2.0/V2.02a:
 * A write access resets System Time
 * Difference (0x092C:0x092F)
 */
#define ESC_SYS_TIME_DIFF_FD_DEPTH_MASK (0xFU)
#define ESC_SYS_TIME_DIFF_FD_DEPTH_SHIFT (0U)
#define ESC_SYS_TIME_DIFF_FD_DEPTH_SET(x) (((uint8_t)(x) << ESC_SYS_TIME_DIFF_FD_DEPTH_SHIFT) & ESC_SYS_TIME_DIFF_FD_DEPTH_MASK)
#define ESC_SYS_TIME_DIFF_FD_DEPTH_GET(x) (((uint8_t)(x) & ESC_SYS_TIME_DIFF_FD_DEPTH_MASK) >> ESC_SYS_TIME_DIFF_FD_DEPTH_SHIFT)

/* Bitfield definition for register: SPD_CNT_FD */
/*
 * DEPTH (RW)
 *
 * Filter depth for averaging the clock period
 * deviation
 * IP Core since V2.2.0/V2.02a:
 * A write access resets the internal speed
 * counter filter
 */
#define ESC_SPD_CNT_FD_DEPTH_MASK (0xFU)
#define ESC_SPD_CNT_FD_DEPTH_SHIFT (0U)
#define ESC_SPD_CNT_FD_DEPTH_SET(x) (((uint8_t)(x) << ESC_SPD_CNT_FD_DEPTH_SHIFT) & ESC_SPD_CNT_FD_DEPTH_MASK)
#define ESC_SPD_CNT_FD_DEPTH_GET(x) (((uint8_t)(x) & ESC_SPD_CNT_FD_DEPTH_MASK) >> ESC_SPD_CNT_FD_DEPTH_SHIFT)

/* Bitfield definition for register: RCV_TIME_LM */
/*
 * LATCH_MODE (RO)
 *
 * Receive Time Latch Mode:
 * 0:Forwarding mode (used if frames are
 * entering the ESC at port 0 first):
 * Receive time stamps of ports 1-3 are
 * enabled after the write access to
 * 0x0900, so the following frame at ports
 * 1-3 will be time stamped (this is typically
 * the write frame to 0x0900 coming back
 * from the network behind the ESC).
 * 1:Reverse mode (used if frames are
 * entering ESC at port 1-3 first):
 * Receive time stamps of ports 1-3 are
 * immediately taken over from the internal
 * hidden time stamp registers, so the
 * previous frame entering the ESC at
 * ports 1-3 will be time stamped when the
 * write frame to 0x0900 enters port 0 (the
 * previous frame at ports 1-3 is typically
 * the write frame to 0x0900 coming from
 * the master, which will enable time
 * stamp
 */
#define ESC_RCV_TIME_LM_LATCH_MODE_MASK (0x1U)
#define ESC_RCV_TIME_LM_LATCH_MODE_SHIFT (0U)
#define ESC_RCV_TIME_LM_LATCH_MODE_GET(x) (((uint8_t)(x) & ESC_RCV_TIME_LM_LATCH_MODE_MASK) >> ESC_RCV_TIME_LM_LATCH_MODE_SHIFT)

/* Bitfield definition for register: CYC_UNIT_CTRL */
/*
 * LATCHI1 (RO)
 *
 * Latch In unit 1:
 * 0:ECAT-controlled
 * 1:PDI-controlled
 * NOTE:Latch interrupt is routed to ECAT/PDI
 * depending on this setting
 */
#define ESC_CYC_UNIT_CTRL_LATCHI1_MASK (0x20U)
#define ESC_CYC_UNIT_CTRL_LATCHI1_SHIFT (5U)
#define ESC_CYC_UNIT_CTRL_LATCHI1_GET(x) (((uint8_t)(x) & ESC_CYC_UNIT_CTRL_LATCHI1_MASK) >> ESC_CYC_UNIT_CTRL_LATCHI1_SHIFT)

/*
 * LATCHI0 (RO)
 *
 * Latch In unit 0:
 * 0:ECAT-controlled
 * 1:PDI-controlled
 * NOTE:Latch interrupt is routed to ECAT/PDI
 * depending on this setting.
 * Always 1 (PDI-controlled) if System Time is PDIcontrolled.
 */
#define ESC_CYC_UNIT_CTRL_LATCHI0_MASK (0x10U)
#define ESC_CYC_UNIT_CTRL_LATCHI0_SHIFT (4U)
#define ESC_CYC_UNIT_CTRL_LATCHI0_GET(x) (((uint8_t)(x) & ESC_CYC_UNIT_CTRL_LATCHI0_MASK) >> ESC_CYC_UNIT_CTRL_LATCHI0_SHIFT)

/*
 * SYNCO (RO)
 *
 * Cyclic Unit and SYNC0 out unit control:
 * 0:ECAT-controlled
 * 1:PDI-controlled
 */
#define ESC_CYC_UNIT_CTRL_SYNCO_MASK (0x1U)
#define ESC_CYC_UNIT_CTRL_SYNCO_SHIFT (0U)
#define ESC_CYC_UNIT_CTRL_SYNCO_GET(x) (((uint8_t)(x) & ESC_CYC_UNIT_CTRL_SYNCO_MASK) >> ESC_CYC_UNIT_CTRL_SYNCO_SHIFT)

/* Bitfield definition for register: SYNCO_ACT */
/*
 * SSDP (RW)
 *
 * SyncSignal debug pulse (Vasily bit):
 * 0:Deactivated
 * 1:Immediately generate one ping only on
 * SYNC0-1 according to 0x0981[2:1 for
 * debugging
 * This bit is self-clearing, always read 0.
 * All pulses are generated at the same time,
 * the cycle time is ignored. The configured
 * pulse length is used.
 */
#define ESC_SYNCO_ACT_SSDP_MASK (0x80U)
#define ESC_SYNCO_ACT_SSDP_SHIFT (7U)
#define ESC_SYNCO_ACT_SSDP_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_SSDP_SHIFT) & ESC_SYNCO_ACT_SSDP_MASK)
#define ESC_SYNCO_ACT_SSDP_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_SSDP_MASK) >> ESC_SYNCO_ACT_SSDP_SHIFT)

/*
 * NFC (RW)
 *
 * Near future configuration (approx.):
 * 0:½ DC width future (231 ns or 263 ns)
 * 1:~2.1 sec. future (231 ns)
 */
#define ESC_SYNCO_ACT_NFC_MASK (0x40U)
#define ESC_SYNCO_ACT_NFC_SHIFT (6U)
#define ESC_SYNCO_ACT_NFC_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_NFC_SHIFT) & ESC_SYNCO_ACT_NFC_MASK)
#define ESC_SYNCO_ACT_NFC_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_NFC_MASK) >> ESC_SYNCO_ACT_NFC_SHIFT)

/*
 * STPC (RW)
 *
 * Start Time plausibility check:
 * 0:Disabled. SyncSignal generation if Start
 * Time is reached.
 * 1:Immediate SyncSignal generation if
 * Start Time is outside near future (see
 * 0x0981[6])
 */
#define ESC_SYNCO_ACT_STPC_MASK (0x20U)
#define ESC_SYNCO_ACT_STPC_SHIFT (5U)
#define ESC_SYNCO_ACT_STPC_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_STPC_SHIFT) & ESC_SYNCO_ACT_STPC_MASK)
#define ESC_SYNCO_ACT_STPC_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_STPC_MASK) >> ESC_SYNCO_ACT_STPC_SHIFT)

/*
 * EXT (RW)
 *
 * Extension of Start Time Cyclic Operation
 * (0x0990:0x0993):
 * 0:No extension
 * 1:Extend 32 bit written Start Time to 64 bit
 */
#define ESC_SYNCO_ACT_EXT_MASK (0x10U)
#define ESC_SYNCO_ACT_EXT_SHIFT (4U)
#define ESC_SYNCO_ACT_EXT_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_EXT_SHIFT) & ESC_SYNCO_ACT_EXT_MASK)
#define ESC_SYNCO_ACT_EXT_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_EXT_MASK) >> ESC_SYNCO_ACT_EXT_SHIFT)

/*
 * AC (RW)
 *
 * Auto-activation by writing Start Time Cyclic
 * Operation (0x0990:0x0997):
 * 0:Disabled
 * 1:Auto-activation enabled. 0x0981[0] is
 * set automatically after Start Time is
 * written.
 */
#define ESC_SYNCO_ACT_AC_MASK (0x8U)
#define ESC_SYNCO_ACT_AC_SHIFT (3U)
#define ESC_SYNCO_ACT_AC_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_AC_SHIFT) & ESC_SYNCO_ACT_AC_MASK)
#define ESC_SYNCO_ACT_AC_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_AC_MASK) >> ESC_SYNCO_ACT_AC_SHIFT)

/*
 * SYNC1_GEN (RW)
 *
 * SYNC1 generation:
 * 0:Deactivated
 * 1:SYNC1 pulse is generated
 */
#define ESC_SYNCO_ACT_SYNC1_GEN_MASK (0x4U)
#define ESC_SYNCO_ACT_SYNC1_GEN_SHIFT (2U)
#define ESC_SYNCO_ACT_SYNC1_GEN_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_SYNC1_GEN_SHIFT) & ESC_SYNCO_ACT_SYNC1_GEN_MASK)
#define ESC_SYNCO_ACT_SYNC1_GEN_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_SYNC1_GEN_MASK) >> ESC_SYNCO_ACT_SYNC1_GEN_SHIFT)

/*
 * SYNC0_GEN (RW)
 *
 * SYNC0 generation:
 * 0:Deactivated
 * 1:SYNC0 pulse is generated
 */
#define ESC_SYNCO_ACT_SYNC0_GEN_MASK (0x2U)
#define ESC_SYNCO_ACT_SYNC0_GEN_SHIFT (1U)
#define ESC_SYNCO_ACT_SYNC0_GEN_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_SYNC0_GEN_SHIFT) & ESC_SYNCO_ACT_SYNC0_GEN_MASK)
#define ESC_SYNCO_ACT_SYNC0_GEN_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_SYNC0_GEN_MASK) >> ESC_SYNCO_ACT_SYNC0_GEN_SHIFT)

/*
 * SOUA (RW)
 *
 * Sync Out Unit activation:
 * 0:Deactivated
 * 1:Activated
 */
#define ESC_SYNCO_ACT_SOUA_MASK (0x1U)
#define ESC_SYNCO_ACT_SOUA_SHIFT (0U)
#define ESC_SYNCO_ACT_SOUA_SET(x) (((uint8_t)(x) << ESC_SYNCO_ACT_SOUA_SHIFT) & ESC_SYNCO_ACT_SOUA_MASK)
#define ESC_SYNCO_ACT_SOUA_GET(x) (((uint8_t)(x) & ESC_SYNCO_ACT_SOUA_MASK) >> ESC_SYNCO_ACT_SOUA_SHIFT)

/* Bitfield definition for register: PULSE_LEN */
/*
 * LEN (RO)
 *
 * Pulse length of SyncSignals (in Units of
 * 10ns)
 * 0:Acknowledge mode:SyncSignal will be
 * cleared by reading SYNC[1:0] Status
 * register
 */
#define ESC_PULSE_LEN_LEN_MASK (0xFFFFU)
#define ESC_PULSE_LEN_LEN_SHIFT (0U)
#define ESC_PULSE_LEN_LEN_GET(x) (((uint16_t)(x) & ESC_PULSE_LEN_LEN_MASK) >> ESC_PULSE_LEN_LEN_SHIFT)

/* Bitfield definition for register: ACT_STAT */
/*
 * CHK_RSLT (RO)
 *
 * Start Time Cyclic Operation (0x0990:0x0997)
 * plausibility check result when Sync Out Unit
 * was activated:
 * 0:Start Time was within near future
 * 1:Start Time was out of near future
 * (0x0981[6])
 */
#define ESC_ACT_STAT_CHK_RSLT_MASK (0x4U)
#define ESC_ACT_STAT_CHK_RSLT_SHIFT (2U)
#define ESC_ACT_STAT_CHK_RSLT_GET(x) (((uint8_t)(x) & ESC_ACT_STAT_CHK_RSLT_MASK) >> ESC_ACT_STAT_CHK_RSLT_SHIFT)

/*
 * SYNC1 (RO)
 *
 * SYNC1 activation state:
 * 0:First SYNC1 pulse is not pending
 * 1:First SYNC1 pulse is pending
 */
#define ESC_ACT_STAT_SYNC1_MASK (0x2U)
#define ESC_ACT_STAT_SYNC1_SHIFT (1U)
#define ESC_ACT_STAT_SYNC1_GET(x) (((uint8_t)(x) & ESC_ACT_STAT_SYNC1_MASK) >> ESC_ACT_STAT_SYNC1_SHIFT)

/*
 * SYNC0 (RO)
 *
 * SYNC0 activation state:
 * 0:First SYNC0 pulse is not pending
 * 1:First SYNC0 pulse is pending
 */
#define ESC_ACT_STAT_SYNC0_MASK (0x1U)
#define ESC_ACT_STAT_SYNC0_SHIFT (0U)
#define ESC_ACT_STAT_SYNC0_GET(x) (((uint8_t)(x) & ESC_ACT_STAT_SYNC0_MASK) >> ESC_ACT_STAT_SYNC0_SHIFT)

/* Bitfield definition for register: SYNC0_STAT */
/*
 * ACK (RW)
 *
 * SYNC0 state for Acknowledge mode.
 * SYNC0 in Acknowledge mode is cleared by
 * reading this register from PDI, use only in
 * Acknowledge mode
 */
#define ESC_SYNC0_STAT_ACK_MASK (0x1U)
#define ESC_SYNC0_STAT_ACK_SHIFT (0U)
#define ESC_SYNC0_STAT_ACK_SET(x) (((uint8_t)(x) << ESC_SYNC0_STAT_ACK_SHIFT) & ESC_SYNC0_STAT_ACK_MASK)
#define ESC_SYNC0_STAT_ACK_GET(x) (((uint8_t)(x) & ESC_SYNC0_STAT_ACK_MASK) >> ESC_SYNC0_STAT_ACK_SHIFT)

/* Bitfield definition for register: SYNC1_STAT */
/*
 * ACK (RW)
 *
 * SYNC1 state for Acknowledge mode.
 * SYNC1 in Acknowledge mode is cleared by
 * reading this register from PDI, use only in
 * Acknowledge mode
 */
#define ESC_SYNC1_STAT_ACK_MASK (0x1U)
#define ESC_SYNC1_STAT_ACK_SHIFT (0U)
#define ESC_SYNC1_STAT_ACK_SET(x) (((uint8_t)(x) << ESC_SYNC1_STAT_ACK_SHIFT) & ESC_SYNC1_STAT_ACK_MASK)
#define ESC_SYNC1_STAT_ACK_GET(x) (((uint8_t)(x) & ESC_SYNC1_STAT_ACK_MASK) >> ESC_SYNC1_STAT_ACK_SHIFT)

/* Bitfield definition for register: START_TIME_CO */
/*
 * ST (RW)
 *
 * Write:Start time (System time) of cyclic
 * operation in ns
 * Read:System time of next SYNC0 pulse in
 * ns
 */
#define ESC_START_TIME_CO_ST_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_START_TIME_CO_ST_SHIFT (0U)
#define ESC_START_TIME_CO_ST_SET(x) (((uint64_t)(x) << ESC_START_TIME_CO_ST_SHIFT) & ESC_START_TIME_CO_ST_MASK)
#define ESC_START_TIME_CO_ST_GET(x) (((uint64_t)(x) & ESC_START_TIME_CO_ST_MASK) >> ESC_START_TIME_CO_ST_SHIFT)

/* Bitfield definition for register: NXT_SYNC1_PULSE */
/*
 * TIME (RO)
 *
 * System time of next SYNC1 pulse in ns
 */
#define ESC_NXT_SYNC1_PULSE_TIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_NXT_SYNC1_PULSE_TIME_SHIFT (0U)
#define ESC_NXT_SYNC1_PULSE_TIME_GET(x) (((uint64_t)(x) & ESC_NXT_SYNC1_PULSE_TIME_MASK) >> ESC_NXT_SYNC1_PULSE_TIME_SHIFT)

/* Bitfield definition for register: SYNC0_CYC_TIME */
/*
 * CYC (RW)
 *
 * Time between two consecutive SYNC0
 * pulses in ns.
 * 0:Single shot mode, generate only one
 * SYNC0 pulse.
 */
#define ESC_SYNC0_CYC_TIME_CYC_MASK (0xFFFFFFFFUL)
#define ESC_SYNC0_CYC_TIME_CYC_SHIFT (0U)
#define ESC_SYNC0_CYC_TIME_CYC_SET(x) (((uint32_t)(x) << ESC_SYNC0_CYC_TIME_CYC_SHIFT) & ESC_SYNC0_CYC_TIME_CYC_MASK)
#define ESC_SYNC0_CYC_TIME_CYC_GET(x) (((uint32_t)(x) & ESC_SYNC0_CYC_TIME_CYC_MASK) >> ESC_SYNC0_CYC_TIME_CYC_SHIFT)

/* Bitfield definition for register: SYNC1_CYC_TIME */
/*
 * CYC (RW)
 *
 * Time between SYNC0 pulse and SYNC1
 * pulse in ns
 */
#define ESC_SYNC1_CYC_TIME_CYC_MASK (0xFFFFFFFFUL)
#define ESC_SYNC1_CYC_TIME_CYC_SHIFT (0U)
#define ESC_SYNC1_CYC_TIME_CYC_SET(x) (((uint32_t)(x) << ESC_SYNC1_CYC_TIME_CYC_SHIFT) & ESC_SYNC1_CYC_TIME_CYC_MASK)
#define ESC_SYNC1_CYC_TIME_CYC_GET(x) (((uint32_t)(x) & ESC_SYNC1_CYC_TIME_CYC_MASK) >> ESC_SYNC1_CYC_TIME_CYC_SHIFT)

/* Bitfield definition for register: LATCH0_CTRL */
/*
 * NEG_EDGE (RW)
 *
 * Latch0 negative edge:
 * 0:Continuous Latch active
 * 1:Single event (only first event active)
 */
#define ESC_LATCH0_CTRL_NEG_EDGE_MASK (0x2U)
#define ESC_LATCH0_CTRL_NEG_EDGE_SHIFT (1U)
#define ESC_LATCH0_CTRL_NEG_EDGE_SET(x) (((uint8_t)(x) << ESC_LATCH0_CTRL_NEG_EDGE_SHIFT) & ESC_LATCH0_CTRL_NEG_EDGE_MASK)
#define ESC_LATCH0_CTRL_NEG_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH0_CTRL_NEG_EDGE_MASK) >> ESC_LATCH0_CTRL_NEG_EDGE_SHIFT)

/*
 * POS_EDGE (RW)
 *
 * Latch0 positive edge:
 * 0:Continuous Latch active
 * 1:Single event (only first event active)
 */
#define ESC_LATCH0_CTRL_POS_EDGE_MASK (0x1U)
#define ESC_LATCH0_CTRL_POS_EDGE_SHIFT (0U)
#define ESC_LATCH0_CTRL_POS_EDGE_SET(x) (((uint8_t)(x) << ESC_LATCH0_CTRL_POS_EDGE_SHIFT) & ESC_LATCH0_CTRL_POS_EDGE_MASK)
#define ESC_LATCH0_CTRL_POS_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH0_CTRL_POS_EDGE_MASK) >> ESC_LATCH0_CTRL_POS_EDGE_SHIFT)

/* Bitfield definition for register: LATCH1_CTRL */
/*
 * NEG_EDGE (RW)
 *
 * Latch1 negative edge:
 * 0:Continuous Latch active
 * 1:Single event (only first event active)
 */
#define ESC_LATCH1_CTRL_NEG_EDGE_MASK (0x2U)
#define ESC_LATCH1_CTRL_NEG_EDGE_SHIFT (1U)
#define ESC_LATCH1_CTRL_NEG_EDGE_SET(x) (((uint8_t)(x) << ESC_LATCH1_CTRL_NEG_EDGE_SHIFT) & ESC_LATCH1_CTRL_NEG_EDGE_MASK)
#define ESC_LATCH1_CTRL_NEG_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH1_CTRL_NEG_EDGE_MASK) >> ESC_LATCH1_CTRL_NEG_EDGE_SHIFT)

/*
 * POS_EDGE (RW)
 *
 * Latch1 positive edge:
 * 0:Continuous Latch active
 * 1:Single event (only first event active)
 */
#define ESC_LATCH1_CTRL_POS_EDGE_MASK (0x1U)
#define ESC_LATCH1_CTRL_POS_EDGE_SHIFT (0U)
#define ESC_LATCH1_CTRL_POS_EDGE_SET(x) (((uint8_t)(x) << ESC_LATCH1_CTRL_POS_EDGE_SHIFT) & ESC_LATCH1_CTRL_POS_EDGE_MASK)
#define ESC_LATCH1_CTRL_POS_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH1_CTRL_POS_EDGE_MASK) >> ESC_LATCH1_CTRL_POS_EDGE_SHIFT)

/* Bitfield definition for register: LATCH0_STAT */
/*
 * PIN_STAT (RO)
 *
 * Latch0 pin state
 */
#define ESC_LATCH0_STAT_PIN_STAT_MASK (0x4U)
#define ESC_LATCH0_STAT_PIN_STAT_SHIFT (2U)
#define ESC_LATCH0_STAT_PIN_STAT_GET(x) (((uint8_t)(x) & ESC_LATCH0_STAT_PIN_STAT_MASK) >> ESC_LATCH0_STAT_PIN_STAT_SHIFT)

/*
 * NEG_EDGE (RO)
 *
 * Event Latch0 negative edge.
 * 0:Negative edge not detected or
 * continuous mode
 * 1:Negative edge detected in single event
 * mode only.
 * Flag cleared by reading out Latch0 Time
 * Negative Edge.
 */
#define ESC_LATCH0_STAT_NEG_EDGE_MASK (0x2U)
#define ESC_LATCH0_STAT_NEG_EDGE_SHIFT (1U)
#define ESC_LATCH0_STAT_NEG_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH0_STAT_NEG_EDGE_MASK) >> ESC_LATCH0_STAT_NEG_EDGE_SHIFT)

/*
 * POS_EDGE (RO)
 *
 * Event Latch0 positive edge.
 * 0:Positive edge not detected or
 * continuous mode
 * 1:Positive edge detected in single event
 * mode only.
 * Flag cleared by reading out Latch0 Time
 * Positive Edge.
 */
#define ESC_LATCH0_STAT_POS_EDGE_MASK (0x1U)
#define ESC_LATCH0_STAT_POS_EDGE_SHIFT (0U)
#define ESC_LATCH0_STAT_POS_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH0_STAT_POS_EDGE_MASK) >> ESC_LATCH0_STAT_POS_EDGE_SHIFT)

/* Bitfield definition for register: LATCH1_STAT */
/*
 * PIN_STAT (RO)
 *
 * Latch1 pin state
 */
#define ESC_LATCH1_STAT_PIN_STAT_MASK (0x4U)
#define ESC_LATCH1_STAT_PIN_STAT_SHIFT (2U)
#define ESC_LATCH1_STAT_PIN_STAT_GET(x) (((uint8_t)(x) & ESC_LATCH1_STAT_PIN_STAT_MASK) >> ESC_LATCH1_STAT_PIN_STAT_SHIFT)

/*
 * NEG_EDGE (RO)
 *
 * Event Latch1 negative edge.
 * 0:Negative edge not detected or
 * continuous mode
 * 1:Negative edge detected in single event
 * mode only.
 * Flag cleared by reading out Latch1 Time
 * Negative Edge.
 */
#define ESC_LATCH1_STAT_NEG_EDGE_MASK (0x2U)
#define ESC_LATCH1_STAT_NEG_EDGE_SHIFT (1U)
#define ESC_LATCH1_STAT_NEG_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH1_STAT_NEG_EDGE_MASK) >> ESC_LATCH1_STAT_NEG_EDGE_SHIFT)

/*
 * POS_EDGE (RO)
 *
 * Event Latch1 positive edge.
 * 0:Positive edge not detected or
 * continuous mode
 * 1:Positive edge detected in single event
 * mode only.
 * Flag cleared by reading out Latch1 Time
 * Positive Edge.
 */
#define ESC_LATCH1_STAT_POS_EDGE_MASK (0x1U)
#define ESC_LATCH1_STAT_POS_EDGE_SHIFT (0U)
#define ESC_LATCH1_STAT_POS_EDGE_GET(x) (((uint8_t)(x) & ESC_LATCH1_STAT_POS_EDGE_MASK) >> ESC_LATCH1_STAT_POS_EDGE_SHIFT)

/* Bitfield definition for register: LATCH0_TIME_PE */
/*
 * TIME (RW)
 *
 * System time at the positive edge of the
 * Latch0 signal.
 */
#define ESC_LATCH0_TIME_PE_TIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_LATCH0_TIME_PE_TIME_SHIFT (0U)
#define ESC_LATCH0_TIME_PE_TIME_SET(x) (((uint64_t)(x) << ESC_LATCH0_TIME_PE_TIME_SHIFT) & ESC_LATCH0_TIME_PE_TIME_MASK)
#define ESC_LATCH0_TIME_PE_TIME_GET(x) (((uint64_t)(x) & ESC_LATCH0_TIME_PE_TIME_MASK) >> ESC_LATCH0_TIME_PE_TIME_SHIFT)

/* Bitfield definition for register: LATCH0_TIME_NE */
/*
 * TIME (RW)
 *
 * System time at the negative edge of the
 * Latch0 signal.
 */
#define ESC_LATCH0_TIME_NE_TIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_LATCH0_TIME_NE_TIME_SHIFT (0U)
#define ESC_LATCH0_TIME_NE_TIME_SET(x) (((uint64_t)(x) << ESC_LATCH0_TIME_NE_TIME_SHIFT) & ESC_LATCH0_TIME_NE_TIME_MASK)
#define ESC_LATCH0_TIME_NE_TIME_GET(x) (((uint64_t)(x) & ESC_LATCH0_TIME_NE_TIME_MASK) >> ESC_LATCH0_TIME_NE_TIME_SHIFT)

/* Bitfield definition for register: LATCH1_TIME_PE */
/*
 * TIME (RW)
 *
 * System time at the positive edge of the
 * Latch1 signal.
 */
#define ESC_LATCH1_TIME_PE_TIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_LATCH1_TIME_PE_TIME_SHIFT (0U)
#define ESC_LATCH1_TIME_PE_TIME_SET(x) (((uint64_t)(x) << ESC_LATCH1_TIME_PE_TIME_SHIFT) & ESC_LATCH1_TIME_PE_TIME_MASK)
#define ESC_LATCH1_TIME_PE_TIME_GET(x) (((uint64_t)(x) & ESC_LATCH1_TIME_PE_TIME_MASK) >> ESC_LATCH1_TIME_PE_TIME_SHIFT)

/* Bitfield definition for register: LATCH1_TIME_NE */
/*
 * TIME (RW)
 *
 * System time at the negative edge of the
 * Latch1 signal.
 */
#define ESC_LATCH1_TIME_NE_TIME_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_LATCH1_TIME_NE_TIME_SHIFT (0U)
#define ESC_LATCH1_TIME_NE_TIME_SET(x) (((uint64_t)(x) << ESC_LATCH1_TIME_NE_TIME_SHIFT) & ESC_LATCH1_TIME_NE_TIME_MASK)
#define ESC_LATCH1_TIME_NE_TIME_GET(x) (((uint64_t)(x) & ESC_LATCH1_TIME_NE_TIME_MASK) >> ESC_LATCH1_TIME_NE_TIME_SHIFT)

/* Bitfield definition for register: ECAT_BUF_CET */
/*
 * TIME (RO)
 *
 * Local time at the beginning of the frame
 * which causes at least one SyncManager to
 * assert an ECAT event
 */
#define ESC_ECAT_BUF_CET_TIME_MASK (0xFFFFFFFFUL)
#define ESC_ECAT_BUF_CET_TIME_SHIFT (0U)
#define ESC_ECAT_BUF_CET_TIME_GET(x) (((uint32_t)(x) & ESC_ECAT_BUF_CET_TIME_MASK) >> ESC_ECAT_BUF_CET_TIME_SHIFT)

/* Bitfield definition for register: PDI_BUF_SET */
/*
 * TIME (RO)
 *
 * Local time when at least one SyncManager
 * asserts a PDI buffer start event
 */
#define ESC_PDI_BUF_SET_TIME_MASK (0xFFFFFFFFUL)
#define ESC_PDI_BUF_SET_TIME_SHIFT (0U)
#define ESC_PDI_BUF_SET_TIME_GET(x) (((uint32_t)(x) & ESC_PDI_BUF_SET_TIME_MASK) >> ESC_PDI_BUF_SET_TIME_SHIFT)

/* Bitfield definition for register: PDI_BUF_CET */
/*
 * TIME (RO)
 *
 * Local time when at least one SyncManager
 * asserts a PDI buffer change event
 */
#define ESC_PDI_BUF_CET_TIME_MASK (0xFFFFFFFFUL)
#define ESC_PDI_BUF_CET_TIME_SHIFT (0U)
#define ESC_PDI_BUF_CET_TIME_GET(x) (((uint32_t)(x) & ESC_PDI_BUF_CET_TIME_MASK) >> ESC_PDI_BUF_CET_TIME_SHIFT)

/* Bitfield definition for register: PID */
/*
 * PID (RO)
 *
 * Product ID
 */
#define ESC_PID_PID_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_PID_PID_SHIFT (0U)
#define ESC_PID_PID_GET(x) (((uint64_t)(x) & ESC_PID_PID_MASK) >> ESC_PID_PID_SHIFT)

/* Bitfield definition for register: VID */
/*
 * VID (RO)
 *
 * Vendor ID:
 * [23-0] Company
 * [31-24] Department
 * NOTE:Test Vendor IDs have [31:28]=0xE
 */
#define ESC_VID_VID_MASK (0xFFFFFFFFUL)
#define ESC_VID_VID_SHIFT (0U)
#define ESC_VID_VID_GET(x) (((uint64_t)(x) & ESC_VID_VID_MASK) >> ESC_VID_VID_SHIFT)

/* Bitfield definition for register: DIO_OUT_DATA */
/*
 * OD (RO)
 *
 * Output Data
 */
#define ESC_DIO_OUT_DATA_OD_MASK (0xFFFFFFFFUL)
#define ESC_DIO_OUT_DATA_OD_SHIFT (0U)
#define ESC_DIO_OUT_DATA_OD_GET(x) (((uint32_t)(x) & ESC_DIO_OUT_DATA_OD_MASK) >> ESC_DIO_OUT_DATA_OD_SHIFT)

/* Bitfield definition for register: GPO */
/*
 * GPOD (RW)
 *
 * General Purpose Output Data
 */
#define ESC_GPO_GPOD_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_GPO_GPOD_SHIFT (0U)
#define ESC_GPO_GPOD_SET(x) (((uint64_t)(x) << ESC_GPO_GPOD_SHIFT) & ESC_GPO_GPOD_MASK)
#define ESC_GPO_GPOD_GET(x) (((uint64_t)(x) & ESC_GPO_GPOD_MASK) >> ESC_GPO_GPOD_SHIFT)

/* Bitfield definition for register: GPI */
/*
 * GPID (RO)
 *
 * General Purpose Input Data
 */
#define ESC_GPI_GPID_MASK (0xFFFFFFFFFFFFFFFFULL)
#define ESC_GPI_GPID_SHIFT (0U)
#define ESC_GPI_GPID_GET(x) (((uint64_t)(x) & ESC_GPI_GPID_MASK) >> ESC_GPI_GPID_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE0 */
/*
 * EXTF (RW)
 *
 * Number of extended feature bits
 */
#define ESC_USER_RAM_BYTE0_EXTF_MASK (0xFFU)
#define ESC_USER_RAM_BYTE0_EXTF_SHIFT (0U)
#define ESC_USER_RAM_BYTE0_EXTF_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE0_EXTF_SHIFT) & ESC_USER_RAM_BYTE0_EXTF_MASK)
#define ESC_USER_RAM_BYTE0_EXTF_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE0_EXTF_MASK) >> ESC_USER_RAM_BYTE0_EXTF_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE1 */
/*
 * PRWO (RW)
 *
 * Physical Read/Write Offset (0x0108:0x0109)
 */
#define ESC_USER_RAM_BYTE1_PRWO_MASK (0x80U)
#define ESC_USER_RAM_BYTE1_PRWO_SHIFT (7U)
#define ESC_USER_RAM_BYTE1_PRWO_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_PRWO_SHIFT) & ESC_USER_RAM_BYTE1_PRWO_MASK)
#define ESC_USER_RAM_BYTE1_PRWO_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_PRWO_MASK) >> ESC_USER_RAM_BYTE1_PRWO_SHIFT)

/*
 * AEMW (RW)
 *
 * AL Event Mask writable (0x0204:0x0207)
 */
#define ESC_USER_RAM_BYTE1_AEMW_MASK (0x40U)
#define ESC_USER_RAM_BYTE1_AEMW_SHIFT (6U)
#define ESC_USER_RAM_BYTE1_AEMW_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_AEMW_SHIFT) & ESC_USER_RAM_BYTE1_AEMW_MASK)
#define ESC_USER_RAM_BYTE1_AEMW_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_AEMW_MASK) >> ESC_USER_RAM_BYTE1_AEMW_SHIFT)

/*
 * GPO (RW)
 *
 * General Purpose Outputs (0x0F10:0x0F17)
 */
#define ESC_USER_RAM_BYTE1_GPO_MASK (0x20U)
#define ESC_USER_RAM_BYTE1_GPO_SHIFT (5U)
#define ESC_USER_RAM_BYTE1_GPO_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_GPO_SHIFT) & ESC_USER_RAM_BYTE1_GPO_MASK)
#define ESC_USER_RAM_BYTE1_GPO_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_GPO_MASK) >> ESC_USER_RAM_BYTE1_GPO_SHIFT)

/*
 * GPI (RW)
 *
 * General Purpose Inputs (0x0F18:0x0F1F)
 */
#define ESC_USER_RAM_BYTE1_GPI_MASK (0x10U)
#define ESC_USER_RAM_BYTE1_GPI_SHIFT (4U)
#define ESC_USER_RAM_BYTE1_GPI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_GPI_SHIFT) & ESC_USER_RAM_BYTE1_GPI_MASK)
#define ESC_USER_RAM_BYTE1_GPI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_GPI_MASK) >> ESC_USER_RAM_BYTE1_GPI_SHIFT)

/*
 * CSA (RW)
 *
 * Configured Station Alias (0x0012:0x0013)
 */
#define ESC_USER_RAM_BYTE1_CSA_MASK (0x8U)
#define ESC_USER_RAM_BYTE1_CSA_SHIFT (3U)
#define ESC_USER_RAM_BYTE1_CSA_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_CSA_SHIFT) & ESC_USER_RAM_BYTE1_CSA_MASK)
#define ESC_USER_RAM_BYTE1_CSA_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_CSA_MASK) >> ESC_USER_RAM_BYTE1_CSA_SHIFT)

/*
 * EIM (RW)
 *
 * ECAT Interrupt Mask (0x0200:0x0201)
 */
#define ESC_USER_RAM_BYTE1_EIM_MASK (0x4U)
#define ESC_USER_RAM_BYTE1_EIM_SHIFT (2U)
#define ESC_USER_RAM_BYTE1_EIM_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_EIM_SHIFT) & ESC_USER_RAM_BYTE1_EIM_MASK)
#define ESC_USER_RAM_BYTE1_EIM_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_EIM_MASK) >> ESC_USER_RAM_BYTE1_EIM_SHIFT)

/*
 * ALSCR (RW)
 *
 * AL Status Code Register (0x0134:0x0135)
 */
#define ESC_USER_RAM_BYTE1_ALSCR_MASK (0x2U)
#define ESC_USER_RAM_BYTE1_ALSCR_SHIFT (1U)
#define ESC_USER_RAM_BYTE1_ALSCR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_ALSCR_SHIFT) & ESC_USER_RAM_BYTE1_ALSCR_MASK)
#define ESC_USER_RAM_BYTE1_ALSCR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_ALSCR_MASK) >> ESC_USER_RAM_BYTE1_ALSCR_SHIFT)

/*
 * EDLCR (RW)
 *
 * Extended DL Control Register (0x0102:0x0103)
 */
#define ESC_USER_RAM_BYTE1_EDLCR_MASK (0x1U)
#define ESC_USER_RAM_BYTE1_EDLCR_SHIFT (0U)
#define ESC_USER_RAM_BYTE1_EDLCR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE1_EDLCR_SHIFT) & ESC_USER_RAM_BYTE1_EDLCR_MASK)
#define ESC_USER_RAM_BYTE1_EDLCR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE1_EDLCR_MASK) >> ESC_USER_RAM_BYTE1_EDLCR_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE2 */
/*
 * ESCFG (RW)
 *
 * EEPROM Size configurable (0x0502[7]):
 * 0:EEPROM Size fixed to sizes up to 16 Kbit
 * 1:EEPROM Size configurable
 */
#define ESC_USER_RAM_BYTE2_ESCFG_MASK (0x80U)
#define ESC_USER_RAM_BYTE2_ESCFG_SHIFT (7U)
#define ESC_USER_RAM_BYTE2_ESCFG_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_ESCFG_SHIFT) & ESC_USER_RAM_BYTE2_ESCFG_MASK)
#define ESC_USER_RAM_BYTE2_ESCFG_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_ESCFG_MASK) >> ESC_USER_RAM_BYTE2_ESCFG_SHIFT)

/*
 * EPUPEC (RW)
 *
 * ECAT Processing Unit/PDI Error Counter
 * (0x030C:0x030D)
 */
#define ESC_USER_RAM_BYTE2_EPUPEC_MASK (0x40U)
#define ESC_USER_RAM_BYTE2_EPUPEC_SHIFT (6U)
#define ESC_USER_RAM_BYTE2_EPUPEC_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_EPUPEC_SHIFT) & ESC_USER_RAM_BYTE2_EPUPEC_MASK)
#define ESC_USER_RAM_BYTE2_EPUPEC_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_EPUPEC_MASK) >> ESC_USER_RAM_BYTE2_EPUPEC_SHIFT)

/*
 * DCSMET (RW)
 *
 * DC SyncManager Event Times (0x09F0:0x09FF)
 */
#define ESC_USER_RAM_BYTE2_DCSMET_MASK (0x20U)
#define ESC_USER_RAM_BYTE2_DCSMET_SHIFT (5U)
#define ESC_USER_RAM_BYTE2_DCSMET_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_DCSMET_SHIFT) & ESC_USER_RAM_BYTE2_DCSMET_MASK)
#define ESC_USER_RAM_BYTE2_DCSMET_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_DCSMET_MASK) >> ESC_USER_RAM_BYTE2_DCSMET_SHIFT)

/*
 * RESET (RW)
 *
 * Reset (0x0040:0x0041)
 */
#define ESC_USER_RAM_BYTE2_RESET_MASK (0x8U)
#define ESC_USER_RAM_BYTE2_RESET_SHIFT (3U)
#define ESC_USER_RAM_BYTE2_RESET_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_RESET_SHIFT) & ESC_USER_RAM_BYTE2_RESET_MASK)
#define ESC_USER_RAM_BYTE2_RESET_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_RESET_MASK) >> ESC_USER_RAM_BYTE2_RESET_SHIFT)

/*
 * WP (RW)
 *
 * Write Protection (0x0020:0x0031)
 */
#define ESC_USER_RAM_BYTE2_WP_MASK (0x4U)
#define ESC_USER_RAM_BYTE2_WP_SHIFT (2U)
#define ESC_USER_RAM_BYTE2_WP_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_WP_SHIFT) & ESC_USER_RAM_BYTE2_WP_MASK)
#define ESC_USER_RAM_BYTE2_WP_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_WP_MASK) >> ESC_USER_RAM_BYTE2_WP_SHIFT)

/*
 * WDGCNT (RW)
 *
 * Watchdog counters (0x0442:0x0443)
 */
#define ESC_USER_RAM_BYTE2_WDGCNT_MASK (0x2U)
#define ESC_USER_RAM_BYTE2_WDGCNT_SHIFT (1U)
#define ESC_USER_RAM_BYTE2_WDGCNT_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_WDGCNT_SHIFT) & ESC_USER_RAM_BYTE2_WDGCNT_MASK)
#define ESC_USER_RAM_BYTE2_WDGCNT_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_WDGCNT_MASK) >> ESC_USER_RAM_BYTE2_WDGCNT_SHIFT)

/*
 * WDW (RW)
 *
 * Watchdog divider writable (0x0400:0x0401) and
 * Watchdog PDI (0x0410:0x0411)
 */
#define ESC_USER_RAM_BYTE2_WDW_MASK (0x1U)
#define ESC_USER_RAM_BYTE2_WDW_SHIFT (0U)
#define ESC_USER_RAM_BYTE2_WDW_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE2_WDW_SHIFT) & ESC_USER_RAM_BYTE2_WDW_MASK)
#define ESC_USER_RAM_BYTE2_WDW_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE2_WDW_MASK) >> ESC_USER_RAM_BYTE2_WDW_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE3 */
/*
 * RLED (RW)
 *
 * Run LED (DEV_STATE LED)
 */
#define ESC_USER_RAM_BYTE3_RLED_MASK (0x80U)
#define ESC_USER_RAM_BYTE3_RLED_SHIFT (7U)
#define ESC_USER_RAM_BYTE3_RLED_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE3_RLED_SHIFT) & ESC_USER_RAM_BYTE3_RLED_MASK)
#define ESC_USER_RAM_BYTE3_RLED_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE3_RLED_MASK) >> ESC_USER_RAM_BYTE3_RLED_SHIFT)

/*
 * ELDE (RW)
 *
 * Enhanced Link Detection EBUS
 */
#define ESC_USER_RAM_BYTE3_ELDE_MASK (0x40U)
#define ESC_USER_RAM_BYTE3_ELDE_SHIFT (6U)
#define ESC_USER_RAM_BYTE3_ELDE_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE3_ELDE_SHIFT) & ESC_USER_RAM_BYTE3_ELDE_MASK)
#define ESC_USER_RAM_BYTE3_ELDE_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE3_ELDE_MASK) >> ESC_USER_RAM_BYTE3_ELDE_SHIFT)

/*
 * ELDM (RW)
 *
 * Enhanced Link Detection MII
 */
#define ESC_USER_RAM_BYTE3_ELDM_MASK (0x20U)
#define ESC_USER_RAM_BYTE3_ELDM_SHIFT (5U)
#define ESC_USER_RAM_BYTE3_ELDM_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE3_ELDM_SHIFT) & ESC_USER_RAM_BYTE3_ELDM_MASK)
#define ESC_USER_RAM_BYTE3_ELDM_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE3_ELDM_MASK) >> ESC_USER_RAM_BYTE3_ELDM_SHIFT)

/*
 * MMI (RW)
 *
 * MII Management Interface (0x0510:0x0515)
 */
#define ESC_USER_RAM_BYTE3_MMI_MASK (0x10U)
#define ESC_USER_RAM_BYTE3_MMI_SHIFT (4U)
#define ESC_USER_RAM_BYTE3_MMI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE3_MMI_SHIFT) & ESC_USER_RAM_BYTE3_MMI_MASK)
#define ESC_USER_RAM_BYTE3_MMI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE3_MMI_MASK) >> ESC_USER_RAM_BYTE3_MMI_SHIFT)

/*
 * LLC (RW)
 *
 * Lost Link Counter (0x0310:0x0313)
 */
#define ESC_USER_RAM_BYTE3_LLC_MASK (0x8U)
#define ESC_USER_RAM_BYTE3_LLC_SHIFT (3U)
#define ESC_USER_RAM_BYTE3_LLC_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE3_LLC_SHIFT) & ESC_USER_RAM_BYTE3_LLC_MASK)
#define ESC_USER_RAM_BYTE3_LLC_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE3_LLC_MASK) >> ESC_USER_RAM_BYTE3_LLC_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE4 */
/*
 * LDCM (RW)
 *
 * Link detection and configuration by MI
 */
#define ESC_USER_RAM_BYTE4_LDCM_MASK (0x80U)
#define ESC_USER_RAM_BYTE4_LDCM_SHIFT (7U)
#define ESC_USER_RAM_BYTE4_LDCM_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE4_LDCM_SHIFT) & ESC_USER_RAM_BYTE4_LDCM_MASK)
#define ESC_USER_RAM_BYTE4_LDCM_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE4_LDCM_MASK) >> ESC_USER_RAM_BYTE4_LDCM_SHIFT)

/*
 * DTLC (RW)
 *
 * DC Time loop control assigned to PDI
 */
#define ESC_USER_RAM_BYTE4_DTLC_MASK (0x40U)
#define ESC_USER_RAM_BYTE4_DTLC_SHIFT (6U)
#define ESC_USER_RAM_BYTE4_DTLC_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE4_DTLC_SHIFT) & ESC_USER_RAM_BYTE4_DTLC_MASK)
#define ESC_USER_RAM_BYTE4_DTLC_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE4_DTLC_MASK) >> ESC_USER_RAM_BYTE4_DTLC_SHIFT)

/*
 * DSOU (RW)
 *
 * DC Sync Out Unit
 */
#define ESC_USER_RAM_BYTE4_DSOU_MASK (0x20U)
#define ESC_USER_RAM_BYTE4_DSOU_SHIFT (5U)
#define ESC_USER_RAM_BYTE4_DSOU_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE4_DSOU_SHIFT) & ESC_USER_RAM_BYTE4_DSOU_MASK)
#define ESC_USER_RAM_BYTE4_DSOU_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE4_DSOU_MASK) >> ESC_USER_RAM_BYTE4_DSOU_SHIFT)

/*
 * DLIU (RW)
 *
 * DC Latch In Unit
 */
#define ESC_USER_RAM_BYTE4_DLIU_MASK (0x8U)
#define ESC_USER_RAM_BYTE4_DLIU_SHIFT (3U)
#define ESC_USER_RAM_BYTE4_DLIU_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE4_DLIU_SHIFT) & ESC_USER_RAM_BYTE4_DLIU_MASK)
#define ESC_USER_RAM_BYTE4_DLIU_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE4_DLIU_MASK) >> ESC_USER_RAM_BYTE4_DLIU_SHIFT)

/*
 * LALED (RW)
 *
 * Link/Activity LED
 */
#define ESC_USER_RAM_BYTE4_LALED_MASK (0x1U)
#define ESC_USER_RAM_BYTE4_LALED_SHIFT (0U)
#define ESC_USER_RAM_BYTE4_LALED_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE4_LALED_SHIFT) & ESC_USER_RAM_BYTE4_LALED_MASK)
#define ESC_USER_RAM_BYTE4_LALED_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE4_LALED_MASK) >> ESC_USER_RAM_BYTE4_LALED_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE5 */
/*
 * DDIOR (RW)
 *
 * Disable Digital I/O register (0x0F00:0x0F03)
 */
#define ESC_USER_RAM_BYTE5_DDIOR_MASK (0x20U)
#define ESC_USER_RAM_BYTE5_DDIOR_SHIFT (5U)
#define ESC_USER_RAM_BYTE5_DDIOR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE5_DDIOR_SHIFT) & ESC_USER_RAM_BYTE5_DDIOR_MASK)
#define ESC_USER_RAM_BYTE5_DDIOR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE5_DDIOR_MASK) >> ESC_USER_RAM_BYTE5_DDIOR_SHIFT)

/*
 * EEU (RW)
 *
 * EEPROM emulation by µController
 */
#define ESC_USER_RAM_BYTE5_EEU_MASK (0x4U)
#define ESC_USER_RAM_BYTE5_EEU_SHIFT (2U)
#define ESC_USER_RAM_BYTE5_EEU_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE5_EEU_SHIFT) & ESC_USER_RAM_BYTE5_EEU_MASK)
#define ESC_USER_RAM_BYTE5_EEU_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE5_EEU_MASK) >> ESC_USER_RAM_BYTE5_EEU_SHIFT)

/*
 * ATS (RW)
 *
 * Automatic TX shift
 */
#define ESC_USER_RAM_BYTE5_ATS_MASK (0x2U)
#define ESC_USER_RAM_BYTE5_ATS_SHIFT (1U)
#define ESC_USER_RAM_BYTE5_ATS_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE5_ATS_SHIFT) & ESC_USER_RAM_BYTE5_ATS_MASK)
#define ESC_USER_RAM_BYTE5_ATS_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE5_ATS_MASK) >> ESC_USER_RAM_BYTE5_ATS_SHIFT)

/*
 * MCPP (RW)
 *
 * MI control by PDI possible
 */
#define ESC_USER_RAM_BYTE5_MCPP_MASK (0x1U)
#define ESC_USER_RAM_BYTE5_MCPP_SHIFT (0U)
#define ESC_USER_RAM_BYTE5_MCPP_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE5_MCPP_SHIFT) & ESC_USER_RAM_BYTE5_MCPP_MASK)
#define ESC_USER_RAM_BYTE5_MCPP_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE5_MCPP_MASK) >> ESC_USER_RAM_BYTE5_MCPP_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE6 */
/*
 * RELEDOR (RW)
 *
 * RUN/ERR LED Override (0x0138:0x0139)
 */
#define ESC_USER_RAM_BYTE6_RELEDOR_MASK (0x4U)
#define ESC_USER_RAM_BYTE6_RELEDOR_SHIFT (2U)
#define ESC_USER_RAM_BYTE6_RELEDOR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE6_RELEDOR_SHIFT) & ESC_USER_RAM_BYTE6_RELEDOR_MASK)
#define ESC_USER_RAM_BYTE6_RELEDOR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE6_RELEDOR_MASK) >> ESC_USER_RAM_BYTE6_RELEDOR_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE7 */
/*
 * DCST (RW)
 *
 * DC System Time (0x0910:0x0936)
 */
#define ESC_USER_RAM_BYTE7_DCST_MASK (0x80U)
#define ESC_USER_RAM_BYTE7_DCST_SHIFT (7U)
#define ESC_USER_RAM_BYTE7_DCST_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE7_DCST_SHIFT) & ESC_USER_RAM_BYTE7_DCST_MASK)
#define ESC_USER_RAM_BYTE7_DCST_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE7_DCST_MASK) >> ESC_USER_RAM_BYTE7_DCST_SHIFT)

/*
 * DCRT (RW)
 *
 * DC Receive Times (0x0900:0x090F)
 */
#define ESC_USER_RAM_BYTE7_DCRT_MASK (0x40U)
#define ESC_USER_RAM_BYTE7_DCRT_SHIFT (6U)
#define ESC_USER_RAM_BYTE7_DCRT_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE7_DCRT_SHIFT) & ESC_USER_RAM_BYTE7_DCRT_MASK)
#define ESC_USER_RAM_BYTE7_DCRT_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE7_DCRT_MASK) >> ESC_USER_RAM_BYTE7_DCRT_SHIFT)

/*
 * DCS1D (RW)
 *
 * DC Sync1 disable
 */
#define ESC_USER_RAM_BYTE7_DCS1D_MASK (0x8U)
#define ESC_USER_RAM_BYTE7_DCS1D_SHIFT (3U)
#define ESC_USER_RAM_BYTE7_DCS1D_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE7_DCS1D_SHIFT) & ESC_USER_RAM_BYTE7_DCS1D_MASK)
#define ESC_USER_RAM_BYTE7_DCS1D_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE7_DCS1D_MASK) >> ESC_USER_RAM_BYTE7_DCS1D_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE8 */
/*
 * PPDI (RW)
 *
 * PLB PDI
 */
#define ESC_USER_RAM_BYTE8_PPDI_MASK (0x20U)
#define ESC_USER_RAM_BYTE8_PPDI_SHIFT (5U)
#define ESC_USER_RAM_BYTE8_PPDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE8_PPDI_SHIFT) & ESC_USER_RAM_BYTE8_PPDI_MASK)
#define ESC_USER_RAM_BYTE8_PPDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE8_PPDI_MASK) >> ESC_USER_RAM_BYTE8_PPDI_SHIFT)

/*
 * OPDI (RW)
 *
 * OPB PDI
 */
#define ESC_USER_RAM_BYTE8_OPDI_MASK (0x10U)
#define ESC_USER_RAM_BYTE8_OPDI_SHIFT (4U)
#define ESC_USER_RAM_BYTE8_OPDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE8_OPDI_SHIFT) & ESC_USER_RAM_BYTE8_OPDI_MASK)
#define ESC_USER_RAM_BYTE8_OPDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE8_OPDI_MASK) >> ESC_USER_RAM_BYTE8_OPDI_SHIFT)

/*
 * APDI (RW)
 *
 * Avalon PDI
 */
#define ESC_USER_RAM_BYTE8_APDI_MASK (0x8U)
#define ESC_USER_RAM_BYTE8_APDI_SHIFT (3U)
#define ESC_USER_RAM_BYTE8_APDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE8_APDI_SHIFT) & ESC_USER_RAM_BYTE8_APDI_MASK)
#define ESC_USER_RAM_BYTE8_APDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE8_APDI_MASK) >> ESC_USER_RAM_BYTE8_APDI_SHIFT)

/*
 * PDICEC (RW)
 *
 * PDI clears error counter
 */
#define ESC_USER_RAM_BYTE8_PDICEC_MASK (0x4U)
#define ESC_USER_RAM_BYTE8_PDICEC_SHIFT (2U)
#define ESC_USER_RAM_BYTE8_PDICEC_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE8_PDICEC_SHIFT) & ESC_USER_RAM_BYTE8_PDICEC_MASK)
#define ESC_USER_RAM_BYTE8_PDICEC_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE8_PDICEC_MASK) >> ESC_USER_RAM_BYTE8_PDICEC_SHIFT)

/*
 * DC64 (RW)
 *
 * DC 64 bit
 */
#define ESC_USER_RAM_BYTE8_DC64_MASK (0x1U)
#define ESC_USER_RAM_BYTE8_DC64_SHIFT (0U)
#define ESC_USER_RAM_BYTE8_DC64_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE8_DC64_SHIFT) & ESC_USER_RAM_BYTE8_DC64_MASK)
#define ESC_USER_RAM_BYTE8_DC64_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE8_DC64_MASK) >> ESC_USER_RAM_BYTE8_DC64_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE9 */
/*
 * DR (RW)
 *
 * Direct RESET
 */
#define ESC_USER_RAM_BYTE9_DR_MASK (0x80U)
#define ESC_USER_RAM_BYTE9_DR_SHIFT (7U)
#define ESC_USER_RAM_BYTE9_DR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE9_DR_SHIFT) & ESC_USER_RAM_BYTE9_DR_MASK)
#define ESC_USER_RAM_BYTE9_DR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE9_DR_MASK) >> ESC_USER_RAM_BYTE9_DR_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE10 */
/*
 * PDIIR (RW)
 *
 * PDI Information register (0x014E:0x014F)
 */
#define ESC_USER_RAM_BYTE10_PDIIR_MASK (0x80U)
#define ESC_USER_RAM_BYTE10_PDIIR_SHIFT (7U)
#define ESC_USER_RAM_BYTE10_PDIIR_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE10_PDIIR_SHIFT) & ESC_USER_RAM_BYTE10_PDIIR_MASK)
#define ESC_USER_RAM_BYTE10_PDIIR_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE10_PDIIR_MASK) >> ESC_USER_RAM_BYTE10_PDIIR_SHIFT)

/*
 * PDIFA (RW)
 *
 * PDI function acknowledge by PDI write
 */
#define ESC_USER_RAM_BYTE10_PDIFA_MASK (0x40U)
#define ESC_USER_RAM_BYTE10_PDIFA_SHIFT (6U)
#define ESC_USER_RAM_BYTE10_PDIFA_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE10_PDIFA_SHIFT) & ESC_USER_RAM_BYTE10_PDIFA_MASK)
#define ESC_USER_RAM_BYTE10_PDIFA_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE10_PDIFA_MASK) >> ESC_USER_RAM_BYTE10_PDIFA_SHIFT)

/*
 * APDI (RW)
 *
 * AXI PDI
 */
#define ESC_USER_RAM_BYTE10_APDI_MASK (0x8U)
#define ESC_USER_RAM_BYTE10_APDI_SHIFT (3U)
#define ESC_USER_RAM_BYTE10_APDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE10_APDI_SHIFT) & ESC_USER_RAM_BYTE10_APDI_MASK)
#define ESC_USER_RAM_BYTE10_APDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE10_APDI_MASK) >> ESC_USER_RAM_BYTE10_APDI_SHIFT)

/*
 * DCL1D (RW)
 *
 * DC Latch1 disable
 */
#define ESC_USER_RAM_BYTE10_DCL1D_MASK (0x4U)
#define ESC_USER_RAM_BYTE10_DCL1D_SHIFT (2U)
#define ESC_USER_RAM_BYTE10_DCL1D_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE10_DCL1D_SHIFT) & ESC_USER_RAM_BYTE10_DCL1D_MASK)
#define ESC_USER_RAM_BYTE10_DCL1D_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE10_DCL1D_MASK) >> ESC_USER_RAM_BYTE10_DCL1D_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE11 */
/*
 * LEDTST (RW)
 *
 * LED test
 */
#define ESC_USER_RAM_BYTE11_LEDTST_MASK (0x8U)
#define ESC_USER_RAM_BYTE11_LEDTST_SHIFT (3U)
#define ESC_USER_RAM_BYTE11_LEDTST_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE11_LEDTST_SHIFT) & ESC_USER_RAM_BYTE11_LEDTST_MASK)
#define ESC_USER_RAM_BYTE11_LEDTST_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE11_LEDTST_MASK) >> ESC_USER_RAM_BYTE11_LEDTST_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE14 */
/*
 * DIOBS (RW)
 *
 * Digital I/O PDI byte size
 */
#define ESC_USER_RAM_BYTE14_DIOBS_MASK (0xC0U)
#define ESC_USER_RAM_BYTE14_DIOBS_SHIFT (6U)
#define ESC_USER_RAM_BYTE14_DIOBS_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE14_DIOBS_SHIFT) & ESC_USER_RAM_BYTE14_DIOBS_MASK)
#define ESC_USER_RAM_BYTE14_DIOBS_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE14_DIOBS_MASK) >> ESC_USER_RAM_BYTE14_DIOBS_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE15 */
/*
 * AUCPDI (RW)
 *
 * Asynchronous µC PDI
 */
#define ESC_USER_RAM_BYTE15_AUCPDI_MASK (0x10U)
#define ESC_USER_RAM_BYTE15_AUCPDI_SHIFT (4U)
#define ESC_USER_RAM_BYTE15_AUCPDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE15_AUCPDI_SHIFT) & ESC_USER_RAM_BYTE15_AUCPDI_MASK)
#define ESC_USER_RAM_BYTE15_AUCPDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE15_AUCPDI_MASK) >> ESC_USER_RAM_BYTE15_AUCPDI_SHIFT)

/*
 * SSPDI (RW)
 *
 * SPI Slave PDI
 */
#define ESC_USER_RAM_BYTE15_SSPDI_MASK (0x8U)
#define ESC_USER_RAM_BYTE15_SSPDI_SHIFT (3U)
#define ESC_USER_RAM_BYTE15_SSPDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE15_SSPDI_SHIFT) & ESC_USER_RAM_BYTE15_SSPDI_MASK)
#define ESC_USER_RAM_BYTE15_SSPDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE15_SSPDI_MASK) >> ESC_USER_RAM_BYTE15_SSPDI_SHIFT)

/*
 * DIOPDI (RW)
 *
 * Digital I/O PDI
 */
#define ESC_USER_RAM_BYTE15_DIOPDI_MASK (0x4U)
#define ESC_USER_RAM_BYTE15_DIOPDI_SHIFT (2U)
#define ESC_USER_RAM_BYTE15_DIOPDI_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE15_DIOPDI_SHIFT) & ESC_USER_RAM_BYTE15_DIOPDI_MASK)
#define ESC_USER_RAM_BYTE15_DIOPDI_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE15_DIOPDI_MASK) >> ESC_USER_RAM_BYTE15_DIOPDI_SHIFT)

/* Bitfield definition for register: USER_RAM_BYTE19 */
/*
 * SCP (RW)
 *
 * Security CPLD protection
 */
#define ESC_USER_RAM_BYTE19_SCP_MASK (0x40U)
#define ESC_USER_RAM_BYTE19_SCP_SHIFT (6U)
#define ESC_USER_RAM_BYTE19_SCP_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_SCP_SHIFT) & ESC_USER_RAM_BYTE19_SCP_MASK)
#define ESC_USER_RAM_BYTE19_SCP_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_SCP_MASK) >> ESC_USER_RAM_BYTE19_SCP_SHIFT)

/*
 * RMII (RW)
 *
 * RMII
 */
#define ESC_USER_RAM_BYTE19_RMII_MASK (0x20U)
#define ESC_USER_RAM_BYTE19_RMII_SHIFT (5U)
#define ESC_USER_RAM_BYTE19_RMII_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_RMII_SHIFT) & ESC_USER_RAM_BYTE19_RMII_MASK)
#define ESC_USER_RAM_BYTE19_RMII_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_RMII_MASK) >> ESC_USER_RAM_BYTE19_RMII_SHIFT)

/*
 * URGP (RW)
 *
 * Use RGMII GTX_CLK phase shifted clock input
 */
#define ESC_USER_RAM_BYTE19_URGP_MASK (0x10U)
#define ESC_USER_RAM_BYTE19_URGP_SHIFT (4U)
#define ESC_USER_RAM_BYTE19_URGP_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_URGP_SHIFT) & ESC_USER_RAM_BYTE19_URGP_MASK)
#define ESC_USER_RAM_BYTE19_URGP_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_URGP_MASK) >> ESC_USER_RAM_BYTE19_URGP_SHIFT)

/*
 * CIA (RW)
 *
 * CLK_PDI_EXT is asynchronous
 */
#define ESC_USER_RAM_BYTE19_CIA_MASK (0x4U)
#define ESC_USER_RAM_BYTE19_CIA_SHIFT (2U)
#define ESC_USER_RAM_BYTE19_CIA_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_CIA_SHIFT) & ESC_USER_RAM_BYTE19_CIA_MASK)
#define ESC_USER_RAM_BYTE19_CIA_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_CIA_MASK) >> ESC_USER_RAM_BYTE19_CIA_SHIFT)

/*
 * IPARO (RW)
 *
 * Individual PHY address read out (0x0510[7:3])
 */
#define ESC_USER_RAM_BYTE19_IPARO_MASK (0x2U)
#define ESC_USER_RAM_BYTE19_IPARO_SHIFT (1U)
#define ESC_USER_RAM_BYTE19_IPARO_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_IPARO_SHIFT) & ESC_USER_RAM_BYTE19_IPARO_MASK)
#define ESC_USER_RAM_BYTE19_IPARO_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_IPARO_MASK) >> ESC_USER_RAM_BYTE19_IPARO_SHIFT)

/*
 * RGMII (RW)
 *
 * RGMII
 */
#define ESC_USER_RAM_BYTE19_RGMII_MASK (0x1U)
#define ESC_USER_RAM_BYTE19_RGMII_SHIFT (0U)
#define ESC_USER_RAM_BYTE19_RGMII_SET(x) (((uint8_t)(x) << ESC_USER_RAM_BYTE19_RGMII_SHIFT) & ESC_USER_RAM_BYTE19_RGMII_MASK)
#define ESC_USER_RAM_BYTE19_RGMII_GET(x) (((uint8_t)(x) & ESC_USER_RAM_BYTE19_RGMII_MASK) >> ESC_USER_RAM_BYTE19_RGMII_SHIFT)

/* Bitfield definition for register: PDRAM */
/*
 * DATA (RW)
 *
 * Input Data
 */
#define ESC_PDRAM_DATA_MASK (0xFFFFFFFFUL)
#define ESC_PDRAM_DATA_SHIFT (0U)
#define ESC_PDRAM_DATA_SET(x) (((uint32_t)(x) << ESC_PDRAM_DATA_SHIFT) & ESC_PDRAM_DATA_MASK)
#define ESC_PDRAM_DATA_GET(x) (((uint32_t)(x) & ESC_PDRAM_DATA_MASK) >> ESC_PDRAM_DATA_SHIFT)

/* Bitfield definition for register: PDRAM_ALS */
/*
 * DATA (RW)
 *
 */
#define ESC_PDRAM_ALS_DATA_MASK (0xFFFFFFFFUL)
#define ESC_PDRAM_ALS_DATA_SHIFT (0U)
#define ESC_PDRAM_ALS_DATA_SET(x) (((uint32_t)(x) << ESC_PDRAM_ALS_DATA_SHIFT) & ESC_PDRAM_ALS_DATA_MASK)
#define ESC_PDRAM_ALS_DATA_GET(x) (((uint32_t)(x) & ESC_PDRAM_ALS_DATA_MASK) >> ESC_PDRAM_ALS_DATA_SHIFT)

/* Bitfield definition for register: GPR_CFG0 */
/*
 * CLK100_EN (RW)
 *
 */
#define ESC_GPR_CFG0_CLK100_EN_MASK (0x2000U)
#define ESC_GPR_CFG0_CLK100_EN_SHIFT (13U)
#define ESC_GPR_CFG0_CLK100_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG0_CLK100_EN_SHIFT) & ESC_GPR_CFG0_CLK100_EN_MASK)
#define ESC_GPR_CFG0_CLK100_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG0_CLK100_EN_MASK) >> ESC_GPR_CFG0_CLK100_EN_SHIFT)

/*
 * EEPROM_EMU (RW)
 *
 * 1 is EEPROM emulation mode (default)
 */
#define ESC_GPR_CFG0_EEPROM_EMU_MASK (0x1000U)
#define ESC_GPR_CFG0_EEPROM_EMU_SHIFT (12U)
#define ESC_GPR_CFG0_EEPROM_EMU_SET(x) (((uint32_t)(x) << ESC_GPR_CFG0_EEPROM_EMU_SHIFT) & ESC_GPR_CFG0_EEPROM_EMU_MASK)
#define ESC_GPR_CFG0_EEPROM_EMU_GET(x) (((uint32_t)(x) & ESC_GPR_CFG0_EEPROM_EMU_MASK) >> ESC_GPR_CFG0_EEPROM_EMU_SHIFT)

/*
 * I2C_SCLK_EN (RW)
 *
 */
#define ESC_GPR_CFG0_I2C_SCLK_EN_MASK (0x8U)
#define ESC_GPR_CFG0_I2C_SCLK_EN_SHIFT (3U)
#define ESC_GPR_CFG0_I2C_SCLK_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG0_I2C_SCLK_EN_SHIFT) & ESC_GPR_CFG0_I2C_SCLK_EN_MASK)
#define ESC_GPR_CFG0_I2C_SCLK_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG0_I2C_SCLK_EN_MASK) >> ESC_GPR_CFG0_I2C_SCLK_EN_SHIFT)

/*
 * PROM_SIZE (RW)
 *
 * Sets EEPROM size:
 * 0:up to 16 kbit EEPROM
 * 1:32 kbit-4Mbit EEPROM
 */
#define ESC_GPR_CFG0_PROM_SIZE_MASK (0x1U)
#define ESC_GPR_CFG0_PROM_SIZE_SHIFT (0U)
#define ESC_GPR_CFG0_PROM_SIZE_SET(x) (((uint32_t)(x) << ESC_GPR_CFG0_PROM_SIZE_SHIFT) & ESC_GPR_CFG0_PROM_SIZE_MASK)
#define ESC_GPR_CFG0_PROM_SIZE_GET(x) (((uint32_t)(x) & ESC_GPR_CFG0_PROM_SIZE_MASK) >> ESC_GPR_CFG0_PROM_SIZE_SHIFT)

/* Bitfield definition for register: GPR_CFG1 */
/*
 * SYNC1_IRQ_EN (RW)
 *
 */
#define ESC_GPR_CFG1_SYNC1_IRQ_EN_MASK (0x80000000UL)
#define ESC_GPR_CFG1_SYNC1_IRQ_EN_SHIFT (31U)
#define ESC_GPR_CFG1_SYNC1_IRQ_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_SYNC1_IRQ_EN_SHIFT) & ESC_GPR_CFG1_SYNC1_IRQ_EN_MASK)
#define ESC_GPR_CFG1_SYNC1_IRQ_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_SYNC1_IRQ_EN_MASK) >> ESC_GPR_CFG1_SYNC1_IRQ_EN_SHIFT)

/*
 * SYNC0_IRQ_EN (RW)
 *
 */
#define ESC_GPR_CFG1_SYNC0_IRQ_EN_MASK (0x40000000UL)
#define ESC_GPR_CFG1_SYNC0_IRQ_EN_SHIFT (30U)
#define ESC_GPR_CFG1_SYNC0_IRQ_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_SYNC0_IRQ_EN_SHIFT) & ESC_GPR_CFG1_SYNC0_IRQ_EN_MASK)
#define ESC_GPR_CFG1_SYNC0_IRQ_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_SYNC0_IRQ_EN_MASK) >> ESC_GPR_CFG1_SYNC0_IRQ_EN_SHIFT)

/*
 * RSTO_IRQ_EN (RW)
 *
 */
#define ESC_GPR_CFG1_RSTO_IRQ_EN_MASK (0x20000000UL)
#define ESC_GPR_CFG1_RSTO_IRQ_EN_SHIFT (29U)
#define ESC_GPR_CFG1_RSTO_IRQ_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_RSTO_IRQ_EN_SHIFT) & ESC_GPR_CFG1_RSTO_IRQ_EN_MASK)
#define ESC_GPR_CFG1_RSTO_IRQ_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_RSTO_IRQ_EN_MASK) >> ESC_GPR_CFG1_RSTO_IRQ_EN_SHIFT)

/*
 * SYNC1_DMA_EN (RW)
 *
 */
#define ESC_GPR_CFG1_SYNC1_DMA_EN_MASK (0x2000U)
#define ESC_GPR_CFG1_SYNC1_DMA_EN_SHIFT (13U)
#define ESC_GPR_CFG1_SYNC1_DMA_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_SYNC1_DMA_EN_SHIFT) & ESC_GPR_CFG1_SYNC1_DMA_EN_MASK)
#define ESC_GPR_CFG1_SYNC1_DMA_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_SYNC1_DMA_EN_MASK) >> ESC_GPR_CFG1_SYNC1_DMA_EN_SHIFT)

/*
 * SYNC0_DMA_EN (RW)
 *
 */
#define ESC_GPR_CFG1_SYNC0_DMA_EN_MASK (0x1000U)
#define ESC_GPR_CFG1_SYNC0_DMA_EN_SHIFT (12U)
#define ESC_GPR_CFG1_SYNC0_DMA_EN_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_SYNC0_DMA_EN_SHIFT) & ESC_GPR_CFG1_SYNC0_DMA_EN_MASK)
#define ESC_GPR_CFG1_SYNC0_DMA_EN_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_SYNC0_DMA_EN_MASK) >> ESC_GPR_CFG1_SYNC0_DMA_EN_SHIFT)

/*
 * LATCH1_FROM_IO (RW)
 *
 * 0:from NTM
 */
#define ESC_GPR_CFG1_LATCH1_FROM_IO_MASK (0x200U)
#define ESC_GPR_CFG1_LATCH1_FROM_IO_SHIFT (9U)
#define ESC_GPR_CFG1_LATCH1_FROM_IO_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_LATCH1_FROM_IO_SHIFT) & ESC_GPR_CFG1_LATCH1_FROM_IO_MASK)
#define ESC_GPR_CFG1_LATCH1_FROM_IO_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_LATCH1_FROM_IO_MASK) >> ESC_GPR_CFG1_LATCH1_FROM_IO_SHIFT)

/*
 * LATCH0_FROM_IO (RW)
 *
 * 0:from TRIGGER_MUX
 */
#define ESC_GPR_CFG1_LATCH0_FROM_IO_MASK (0x100U)
#define ESC_GPR_CFG1_LATCH0_FROM_IO_SHIFT (8U)
#define ESC_GPR_CFG1_LATCH0_FROM_IO_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_LATCH0_FROM_IO_SHIFT) & ESC_GPR_CFG1_LATCH0_FROM_IO_MASK)
#define ESC_GPR_CFG1_LATCH0_FROM_IO_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_LATCH0_FROM_IO_MASK) >> ESC_GPR_CFG1_LATCH0_FROM_IO_SHIFT)

/*
 * RSTO_OVRD (RW)
 *
 */
#define ESC_GPR_CFG1_RSTO_OVRD_MASK (0x80U)
#define ESC_GPR_CFG1_RSTO_OVRD_SHIFT (7U)
#define ESC_GPR_CFG1_RSTO_OVRD_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_RSTO_OVRD_SHIFT) & ESC_GPR_CFG1_RSTO_OVRD_MASK)
#define ESC_GPR_CFG1_RSTO_OVRD_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_RSTO_OVRD_MASK) >> ESC_GPR_CFG1_RSTO_OVRD_SHIFT)

/*
 * RSTO_OVRD_ENJ (RW)
 *
 */
#define ESC_GPR_CFG1_RSTO_OVRD_ENJ_MASK (0x40U)
#define ESC_GPR_CFG1_RSTO_OVRD_ENJ_SHIFT (6U)
#define ESC_GPR_CFG1_RSTO_OVRD_ENJ_SET(x) (((uint32_t)(x) << ESC_GPR_CFG1_RSTO_OVRD_ENJ_SHIFT) & ESC_GPR_CFG1_RSTO_OVRD_ENJ_MASK)
#define ESC_GPR_CFG1_RSTO_OVRD_ENJ_GET(x) (((uint32_t)(x) & ESC_GPR_CFG1_RSTO_OVRD_ENJ_MASK) >> ESC_GPR_CFG1_RSTO_OVRD_ENJ_SHIFT)

/* Bitfield definition for register: GPR_CFG2 */
/*
 * NMII_LINK2_FROM_IO (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK2_FROM_IO_MASK (0x20000000UL)
#define ESC_GPR_CFG2_NMII_LINK2_FROM_IO_SHIFT (29U)
#define ESC_GPR_CFG2_NMII_LINK2_FROM_IO_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK2_FROM_IO_SHIFT) & ESC_GPR_CFG2_NMII_LINK2_FROM_IO_MASK)
#define ESC_GPR_CFG2_NMII_LINK2_FROM_IO_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK2_FROM_IO_MASK) >> ESC_GPR_CFG2_NMII_LINK2_FROM_IO_SHIFT)

/*
 * NMII_LINK2_GPR (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK2_GPR_MASK (0x10000000UL)
#define ESC_GPR_CFG2_NMII_LINK2_GPR_SHIFT (28U)
#define ESC_GPR_CFG2_NMII_LINK2_GPR_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK2_GPR_SHIFT) & ESC_GPR_CFG2_NMII_LINK2_GPR_MASK)
#define ESC_GPR_CFG2_NMII_LINK2_GPR_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK2_GPR_MASK) >> ESC_GPR_CFG2_NMII_LINK2_GPR_SHIFT)

/*
 * NMII_LINK1_FROM_IO (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK1_FROM_IO_MASK (0x2000000UL)
#define ESC_GPR_CFG2_NMII_LINK1_FROM_IO_SHIFT (25U)
#define ESC_GPR_CFG2_NMII_LINK1_FROM_IO_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK1_FROM_IO_SHIFT) & ESC_GPR_CFG2_NMII_LINK1_FROM_IO_MASK)
#define ESC_GPR_CFG2_NMII_LINK1_FROM_IO_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK1_FROM_IO_MASK) >> ESC_GPR_CFG2_NMII_LINK1_FROM_IO_SHIFT)

/*
 * NMII_LINK1_GPR (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK1_GPR_MASK (0x1000000UL)
#define ESC_GPR_CFG2_NMII_LINK1_GPR_SHIFT (24U)
#define ESC_GPR_CFG2_NMII_LINK1_GPR_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK1_GPR_SHIFT) & ESC_GPR_CFG2_NMII_LINK1_GPR_MASK)
#define ESC_GPR_CFG2_NMII_LINK1_GPR_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK1_GPR_MASK) >> ESC_GPR_CFG2_NMII_LINK1_GPR_SHIFT)

/*
 * NMII_LINK0_FROM_IO (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK0_FROM_IO_MASK (0x200000UL)
#define ESC_GPR_CFG2_NMII_LINK0_FROM_IO_SHIFT (21U)
#define ESC_GPR_CFG2_NMII_LINK0_FROM_IO_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK0_FROM_IO_SHIFT) & ESC_GPR_CFG2_NMII_LINK0_FROM_IO_MASK)
#define ESC_GPR_CFG2_NMII_LINK0_FROM_IO_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK0_FROM_IO_MASK) >> ESC_GPR_CFG2_NMII_LINK0_FROM_IO_SHIFT)

/*
 * NMII_LINK0_GPR (RW)
 *
 */
#define ESC_GPR_CFG2_NMII_LINK0_GPR_MASK (0x100000UL)
#define ESC_GPR_CFG2_NMII_LINK0_GPR_SHIFT (20U)
#define ESC_GPR_CFG2_NMII_LINK0_GPR_SET(x) (((uint32_t)(x) << ESC_GPR_CFG2_NMII_LINK0_GPR_SHIFT) & ESC_GPR_CFG2_NMII_LINK0_GPR_MASK)
#define ESC_GPR_CFG2_NMII_LINK0_GPR_GET(x) (((uint32_t)(x) & ESC_GPR_CFG2_NMII_LINK0_GPR_MASK) >> ESC_GPR_CFG2_NMII_LINK0_GPR_SHIFT)

/* Bitfield definition for register: PHY_CFG0 */
/*
 * MAC_SPEED (RW)
 *
 * 1:100M
 */
#define ESC_PHY_CFG0_MAC_SPEED_MASK (0x40000000UL)
#define ESC_PHY_CFG0_MAC_SPEED_SHIFT (30U)
#define ESC_PHY_CFG0_MAC_SPEED_SET(x) (((uint32_t)(x) << ESC_PHY_CFG0_MAC_SPEED_SHIFT) & ESC_PHY_CFG0_MAC_SPEED_MASK)
#define ESC_PHY_CFG0_MAC_SPEED_GET(x) (((uint32_t)(x) & ESC_PHY_CFG0_MAC_SPEED_MASK) >> ESC_PHY_CFG0_MAC_SPEED_SHIFT)

/*
 * PORT2_RMII_EN (RW)
 *
 */
#define ESC_PHY_CFG0_PORT2_RMII_EN_MASK (0x800000UL)
#define ESC_PHY_CFG0_PORT2_RMII_EN_SHIFT (23U)
#define ESC_PHY_CFG0_PORT2_RMII_EN_SET(x) (((uint32_t)(x) << ESC_PHY_CFG0_PORT2_RMII_EN_SHIFT) & ESC_PHY_CFG0_PORT2_RMII_EN_MASK)
#define ESC_PHY_CFG0_PORT2_RMII_EN_GET(x) (((uint32_t)(x) & ESC_PHY_CFG0_PORT2_RMII_EN_MASK) >> ESC_PHY_CFG0_PORT2_RMII_EN_SHIFT)

/*
 * PORT1_RMII_EN (RW)
 *
 */
#define ESC_PHY_CFG0_PORT1_RMII_EN_MASK (0x8000U)
#define ESC_PHY_CFG0_PORT1_RMII_EN_SHIFT (15U)
#define ESC_PHY_CFG0_PORT1_RMII_EN_SET(x) (((uint32_t)(x) << ESC_PHY_CFG0_PORT1_RMII_EN_SHIFT) & ESC_PHY_CFG0_PORT1_RMII_EN_MASK)
#define ESC_PHY_CFG0_PORT1_RMII_EN_GET(x) (((uint32_t)(x) & ESC_PHY_CFG0_PORT1_RMII_EN_MASK) >> ESC_PHY_CFG0_PORT1_RMII_EN_SHIFT)

/*
 * PORT0_RMII_EN (RW)
 *
 */
#define ESC_PHY_CFG0_PORT0_RMII_EN_MASK (0x80U)
#define ESC_PHY_CFG0_PORT0_RMII_EN_SHIFT (7U)
#define ESC_PHY_CFG0_PORT0_RMII_EN_SET(x) (((uint32_t)(x) << ESC_PHY_CFG0_PORT0_RMII_EN_SHIFT) & ESC_PHY_CFG0_PORT0_RMII_EN_MASK)
#define ESC_PHY_CFG0_PORT0_RMII_EN_GET(x) (((uint32_t)(x) & ESC_PHY_CFG0_PORT0_RMII_EN_MASK) >> ESC_PHY_CFG0_PORT0_RMII_EN_SHIFT)

/* Bitfield definition for register: PHY_CFG1 */
/*
 * RMII_REFCLK_SEL (RW)
 *
 * 0:use RXCK as 50M refclk. 1:use TXCK as 50M refclk
 */
#define ESC_PHY_CFG1_RMII_REFCLK_SEL_MASK (0x700U)
#define ESC_PHY_CFG1_RMII_REFCLK_SEL_SHIFT (8U)
#define ESC_PHY_CFG1_RMII_REFCLK_SEL_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_REFCLK_SEL_SHIFT) & ESC_PHY_CFG1_RMII_REFCLK_SEL_MASK)
#define ESC_PHY_CFG1_RMII_REFCLK_SEL_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_REFCLK_SEL_MASK) >> ESC_PHY_CFG1_RMII_REFCLK_SEL_SHIFT)

/*
 * REFCK_25M_INV (RW)
 *
 */
#define ESC_PHY_CFG1_REFCK_25M_INV_MASK (0x80U)
#define ESC_PHY_CFG1_REFCK_25M_INV_SHIFT (7U)
#define ESC_PHY_CFG1_REFCK_25M_INV_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_REFCK_25M_INV_SHIFT) & ESC_PHY_CFG1_REFCK_25M_INV_MASK)
#define ESC_PHY_CFG1_REFCK_25M_INV_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_REFCK_25M_INV_MASK) >> ESC_PHY_CFG1_REFCK_25M_INV_SHIFT)

/*
 * RMII_P2_RXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_MASK (0x40U)
#define ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_SHIFT (6U)
#define ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P2_RXCK_REFCLK_OE_SHIFT)

/*
 * RMII_P1_RXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_MASK (0x20U)
#define ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_SHIFT (5U)
#define ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P1_RXCK_REFCLK_OE_SHIFT)

/*
 * RMII_P0_RXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_MASK (0x10U)
#define ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_SHIFT (4U)
#define ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P0_RXCK_REFCLK_OE_SHIFT)

/*
 * REFCK_25M_OE (RW)
 *
 */
#define ESC_PHY_CFG1_REFCK_25M_OE_MASK (0x8U)
#define ESC_PHY_CFG1_REFCK_25M_OE_SHIFT (3U)
#define ESC_PHY_CFG1_REFCK_25M_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_REFCK_25M_OE_SHIFT) & ESC_PHY_CFG1_REFCK_25M_OE_MASK)
#define ESC_PHY_CFG1_REFCK_25M_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_REFCK_25M_OE_MASK) >> ESC_PHY_CFG1_REFCK_25M_OE_SHIFT)

/*
 * RMII_P2_TXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_MASK (0x4U)
#define ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_SHIFT (2U)
#define ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P2_TXCK_REFCLK_OE_SHIFT)

/*
 * RMII_P1_TXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_MASK (0x2U)
#define ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_SHIFT (1U)
#define ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P1_TXCK_REFCLK_OE_SHIFT)

/*
 * RMII_P0_TXCK_REFCLK_OE (RW)
 *
 */
#define ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_MASK (0x1U)
#define ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_SHIFT (0U)
#define ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_SET(x) (((uint32_t)(x) << ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_SHIFT) & ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_MASK)
#define ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_GET(x) (((uint32_t)(x) & ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_MASK) >> ESC_PHY_CFG1_RMII_P0_TXCK_REFCLK_OE_SHIFT)

/* Bitfield definition for register: GPIO_CTRL */
/*
 * SW_LATCH_GPI (WO)
 *
 * if gpi_trig_sel is set to 4'b1001, setting this bit will latch GPI to gpi_reg0/1
 */
#define ESC_GPIO_CTRL_SW_LATCH_GPI_MASK (0x80000000UL)
#define ESC_GPIO_CTRL_SW_LATCH_GPI_SHIFT (31U)
#define ESC_GPIO_CTRL_SW_LATCH_GPI_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_SW_LATCH_GPI_SHIFT) & ESC_GPIO_CTRL_SW_LATCH_GPI_MASK)
#define ESC_GPIO_CTRL_SW_LATCH_GPI_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_SW_LATCH_GPI_MASK) >> ESC_GPIO_CTRL_SW_LATCH_GPI_SHIFT)

/*
 * SW_LATCH_GPO (WO)
 *
 * if gpo_trig_sel is set to 4'b1001, setting this bit will latch GPO to gpo_reg0/1
 */
#define ESC_GPIO_CTRL_SW_LATCH_GPO_MASK (0x40000000UL)
#define ESC_GPIO_CTRL_SW_LATCH_GPO_SHIFT (30U)
#define ESC_GPIO_CTRL_SW_LATCH_GPO_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_SW_LATCH_GPO_SHIFT) & ESC_GPIO_CTRL_SW_LATCH_GPO_MASK)
#define ESC_GPIO_CTRL_SW_LATCH_GPO_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_SW_LATCH_GPO_MASK) >> ESC_GPIO_CTRL_SW_LATCH_GPO_SHIFT)

/*
 * GPI_OVERRIDE_EN (RW)
 *
 * set this bit will use GPI from the software register gpi_override0/1
 * clr to use GPI from pad directly
 */
#define ESC_GPIO_CTRL_GPI_OVERRIDE_EN_MASK (0x2000U)
#define ESC_GPIO_CTRL_GPI_OVERRIDE_EN_SHIFT (13U)
#define ESC_GPIO_CTRL_GPI_OVERRIDE_EN_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_GPI_OVERRIDE_EN_SHIFT) & ESC_GPIO_CTRL_GPI_OVERRIDE_EN_MASK)
#define ESC_GPIO_CTRL_GPI_OVERRIDE_EN_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_GPI_OVERRIDE_EN_MASK) >> ESC_GPIO_CTRL_GPI_OVERRIDE_EN_SHIFT)

/*
 * GPI_TRIG_EN (RW)
 *
 * use gpi_trig_sel can select the trigger event to latch GPI signal(from reg or pad)
 * set to use triggered signal;
 * clr to use signals direclty(from reg or pad)
 * assign pdi_gpi = gpi_trig_en ? gpi_reg :
 *                (gpi_override_en ? gpi_override :pad_di_ecat_gpi);
 */
#define ESC_GPIO_CTRL_GPI_TRIG_EN_MASK (0x1000U)
#define ESC_GPIO_CTRL_GPI_TRIG_EN_SHIFT (12U)
#define ESC_GPIO_CTRL_GPI_TRIG_EN_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_GPI_TRIG_EN_SHIFT) & ESC_GPIO_CTRL_GPI_TRIG_EN_MASK)
#define ESC_GPIO_CTRL_GPI_TRIG_EN_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_GPI_TRIG_EN_MASK) >> ESC_GPIO_CTRL_GPI_TRIG_EN_SHIFT)

/*
 * GPI_TRIG_SEL (RW)
 *
 * select the trigger signal to latch GPI.
 * 0000: SOF;  0001: EOF;  0010: pos of  SYNC0;  0011: pos of SYNC1;
 * 0100: pos of LATCH0;   0101: pos of LATCH1;   0110: neg of LATCH0;   0111: neg of LATCH1
 * 1000: wdog trigger;   1001: sw set gpio_ctrl[31];   others no trigger
 */
#define ESC_GPIO_CTRL_GPI_TRIG_SEL_MASK (0xF00U)
#define ESC_GPIO_CTRL_GPI_TRIG_SEL_SHIFT (8U)
#define ESC_GPIO_CTRL_GPI_TRIG_SEL_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_GPI_TRIG_SEL_SHIFT) & ESC_GPIO_CTRL_GPI_TRIG_SEL_MASK)
#define ESC_GPIO_CTRL_GPI_TRIG_SEL_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_GPI_TRIG_SEL_MASK) >> ESC_GPIO_CTRL_GPI_TRIG_SEL_SHIFT)

/*
 * GPO_TRIG_EN (RW)
 *
 * use gpo_trig_sel can select the trigger event to latch GPO signal(from core)
 * set to use triggered signal;
 * clr to use GPO signals direclty(from reg or pad)
 */
#define ESC_GPIO_CTRL_GPO_TRIG_EN_MASK (0x10U)
#define ESC_GPIO_CTRL_GPO_TRIG_EN_SHIFT (4U)
#define ESC_GPIO_CTRL_GPO_TRIG_EN_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_GPO_TRIG_EN_SHIFT) & ESC_GPIO_CTRL_GPO_TRIG_EN_MASK)
#define ESC_GPIO_CTRL_GPO_TRIG_EN_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_GPO_TRIG_EN_MASK) >> ESC_GPIO_CTRL_GPO_TRIG_EN_SHIFT)

/*
 * GPO_TRIG_SEL (RW)
 *
 * select the trigger signal to latch GPO.
 * 0000: SOF;  0001: EOF;  0010: pos of  SYNC0;  0011: pos of SYNC1;
 * 0100: pos of LATCH0;   0101: pos of LATCH1;   0110: neg of LATCH0;   0111: neg of LATCH1
 * 1000: wdog trigger;   1001: sw set gpio_ctrl[30];   others no trigger
 */
#define ESC_GPIO_CTRL_GPO_TRIG_SEL_MASK (0xFU)
#define ESC_GPIO_CTRL_GPO_TRIG_SEL_SHIFT (0U)
#define ESC_GPIO_CTRL_GPO_TRIG_SEL_SET(x) (((uint32_t)(x) << ESC_GPIO_CTRL_GPO_TRIG_SEL_SHIFT) & ESC_GPIO_CTRL_GPO_TRIG_SEL_MASK)
#define ESC_GPIO_CTRL_GPO_TRIG_SEL_GET(x) (((uint32_t)(x) & ESC_GPIO_CTRL_GPO_TRIG_SEL_MASK) >> ESC_GPIO_CTRL_GPO_TRIG_SEL_SHIFT)

/* Bitfield definition for register: GPI_OVERRIDE0 */
/*
 * GPR_OVERRIDE_LOW (RW)
 *
 */
#define ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_MASK (0xFFFFFFFFUL)
#define ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_SHIFT (0U)
#define ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_SET(x) (((uint32_t)(x) << ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_SHIFT) & ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_MASK)
#define ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_GET(x) (((uint32_t)(x) & ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_MASK) >> ESC_GPI_OVERRIDE0_GPR_OVERRIDE_LOW_SHIFT)

/* Bitfield definition for register: GPI_OVERRIDE1 */
/*
 * GPR_OVERRIDE_HIGH (RW)
 *
 */
#define ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_MASK (0xFFFFFFFFUL)
#define ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_SHIFT (0U)
#define ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_SET(x) (((uint32_t)(x) << ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_SHIFT) & ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_MASK)
#define ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_GET(x) (((uint32_t)(x) & ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_MASK) >> ESC_GPI_OVERRIDE1_GPR_OVERRIDE_HIGH_SHIFT)

/* Bitfield definition for register: GPO_REG0 */
/*
 * VALUE (RO)
 *
 */
#define ESC_GPO_REG0_VALUE_MASK (0xFFFFFFFFUL)
#define ESC_GPO_REG0_VALUE_SHIFT (0U)
#define ESC_GPO_REG0_VALUE_GET(x) (((uint32_t)(x) & ESC_GPO_REG0_VALUE_MASK) >> ESC_GPO_REG0_VALUE_SHIFT)

/* Bitfield definition for register: GPO_REG1 */
/*
 * VALUE (RO)
 *
 */
#define ESC_GPO_REG1_VALUE_MASK (0xFFFFFFFFUL)
#define ESC_GPO_REG1_VALUE_SHIFT (0U)
#define ESC_GPO_REG1_VALUE_GET(x) (((uint32_t)(x) & ESC_GPO_REG1_VALUE_MASK) >> ESC_GPO_REG1_VALUE_SHIFT)

/* Bitfield definition for register: GPI_REG0 */
/*
 * VALUE (RO)
 *
 */
#define ESC_GPI_REG0_VALUE_MASK (0xFFFFFFFFUL)
#define ESC_GPI_REG0_VALUE_SHIFT (0U)
#define ESC_GPI_REG0_VALUE_GET(x) (((uint32_t)(x) & ESC_GPI_REG0_VALUE_MASK) >> ESC_GPI_REG0_VALUE_SHIFT)

/* Bitfield definition for register: GPI_REG1 */
/*
 * VALUE (RO)
 *
 */
#define ESC_GPI_REG1_VALUE_MASK (0xFFFFFFFFUL)
#define ESC_GPI_REG1_VALUE_SHIFT (0U)
#define ESC_GPI_REG1_VALUE_GET(x) (((uint32_t)(x) & ESC_GPI_REG1_VALUE_MASK) >> ESC_GPI_REG1_VALUE_SHIFT)

/* Bitfield definition for register: GPR_STATUS */
/*
 * NLINK2_PADSEL (RO)
 *
 */
#define ESC_GPR_STATUS_NLINK2_PADSEL_MASK (0xF0000000UL)
#define ESC_GPR_STATUS_NLINK2_PADSEL_SHIFT (28U)
#define ESC_GPR_STATUS_NLINK2_PADSEL_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_NLINK2_PADSEL_MASK) >> ESC_GPR_STATUS_NLINK2_PADSEL_SHIFT)

/*
 * NLINK1_PADSEL (RO)
 *
 */
#define ESC_GPR_STATUS_NLINK1_PADSEL_MASK (0xF000000UL)
#define ESC_GPR_STATUS_NLINK1_PADSEL_SHIFT (24U)
#define ESC_GPR_STATUS_NLINK1_PADSEL_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_NLINK1_PADSEL_MASK) >> ESC_GPR_STATUS_NLINK1_PADSEL_SHIFT)

/*
 * NLINK0_PADSEL (RO)
 *
 */
#define ESC_GPR_STATUS_NLINK0_PADSEL_MASK (0xF00000UL)
#define ESC_GPR_STATUS_NLINK0_PADSEL_SHIFT (20U)
#define ESC_GPR_STATUS_NLINK0_PADSEL_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_NLINK0_PADSEL_MASK) >> ESC_GPR_STATUS_NLINK0_PADSEL_SHIFT)

/*
 * PDI_SOF (RO)
 *
 */
#define ESC_GPR_STATUS_PDI_SOF_MASK (0x80000UL)
#define ESC_GPR_STATUS_PDI_SOF_SHIFT (19U)
#define ESC_GPR_STATUS_PDI_SOF_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_PDI_SOF_MASK) >> ESC_GPR_STATUS_PDI_SOF_SHIFT)

/*
 * PDI_EOF (RO)
 *
 */
#define ESC_GPR_STATUS_PDI_EOF_MASK (0x40000UL)
#define ESC_GPR_STATUS_PDI_EOF_SHIFT (18U)
#define ESC_GPR_STATUS_PDI_EOF_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_PDI_EOF_MASK) >> ESC_GPR_STATUS_PDI_EOF_SHIFT)

/*
 * PDI_WD_TRIGGER (RO)
 *
 */
#define ESC_GPR_STATUS_PDI_WD_TRIGGER_MASK (0x20000UL)
#define ESC_GPR_STATUS_PDI_WD_TRIGGER_SHIFT (17U)
#define ESC_GPR_STATUS_PDI_WD_TRIGGER_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_PDI_WD_TRIGGER_MASK) >> ESC_GPR_STATUS_PDI_WD_TRIGGER_SHIFT)

/*
 * PDI_WD_STATE (RO)
 *
 */
#define ESC_GPR_STATUS_PDI_WD_STATE_MASK (0x10000UL)
#define ESC_GPR_STATUS_PDI_WD_STATE_SHIFT (16U)
#define ESC_GPR_STATUS_PDI_WD_STATE_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_PDI_WD_STATE_MASK) >> ESC_GPR_STATUS_PDI_WD_STATE_SHIFT)

/*
 * SYNC_OUT1 (RO)
 *
 */
#define ESC_GPR_STATUS_SYNC_OUT1_MASK (0x200U)
#define ESC_GPR_STATUS_SYNC_OUT1_SHIFT (9U)
#define ESC_GPR_STATUS_SYNC_OUT1_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_SYNC_OUT1_MASK) >> ESC_GPR_STATUS_SYNC_OUT1_SHIFT)

/*
 * SYNC_OUT0 (RO)
 *
 */
#define ESC_GPR_STATUS_SYNC_OUT0_MASK (0x100U)
#define ESC_GPR_STATUS_SYNC_OUT0_SHIFT (8U)
#define ESC_GPR_STATUS_SYNC_OUT0_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_SYNC_OUT0_MASK) >> ESC_GPR_STATUS_SYNC_OUT0_SHIFT)

/*
 * LED_STATE_RUN (RO)
 *
 */
#define ESC_GPR_STATUS_LED_STATE_RUN_MASK (0x40U)
#define ESC_GPR_STATUS_LED_STATE_RUN_SHIFT (6U)
#define ESC_GPR_STATUS_LED_STATE_RUN_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_LED_STATE_RUN_MASK) >> ESC_GPR_STATUS_LED_STATE_RUN_SHIFT)

/*
 * LED_ERR (RO)
 *
 */
#define ESC_GPR_STATUS_LED_ERR_MASK (0x20U)
#define ESC_GPR_STATUS_LED_ERR_SHIFT (5U)
#define ESC_GPR_STATUS_LED_ERR_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_LED_ERR_MASK) >> ESC_GPR_STATUS_LED_ERR_SHIFT)

/*
 * LED_RUN (RO)
 *
 */
#define ESC_GPR_STATUS_LED_RUN_MASK (0x10U)
#define ESC_GPR_STATUS_LED_RUN_SHIFT (4U)
#define ESC_GPR_STATUS_LED_RUN_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_LED_RUN_MASK) >> ESC_GPR_STATUS_LED_RUN_SHIFT)

/*
 * DEV_STATE (RO)
 *
 */
#define ESC_GPR_STATUS_DEV_STATE_MASK (0x8U)
#define ESC_GPR_STATUS_DEV_STATE_SHIFT (3U)
#define ESC_GPR_STATUS_DEV_STATE_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_DEV_STATE_MASK) >> ESC_GPR_STATUS_DEV_STATE_SHIFT)

/*
 * LINK_ACT (RO)
 *
 */
#define ESC_GPR_STATUS_LINK_ACT_MASK (0x7U)
#define ESC_GPR_STATUS_LINK_ACT_SHIFT (0U)
#define ESC_GPR_STATUS_LINK_ACT_GET(x) (((uint32_t)(x) & ESC_GPR_STATUS_LINK_ACT_MASK) >> ESC_GPR_STATUS_LINK_ACT_SHIFT)

/* Bitfield definition for register array: IO_CFG */
/*
 * INVERT (RW)
 *
 * 1:invert the IO
 */
#define ESC_IO_CFG_INVERT_MASK (0x10U)
#define ESC_IO_CFG_INVERT_SHIFT (4U)
#define ESC_IO_CFG_INVERT_SET(x) (((uint32_t)(x) << ESC_IO_CFG_INVERT_SHIFT) & ESC_IO_CFG_INVERT_MASK)
#define ESC_IO_CFG_INVERT_GET(x) (((uint32_t)(x) & ESC_IO_CFG_INVERT_MASK) >> ESC_IO_CFG_INVERT_SHIFT)

/*
 * FUNC_ALT (RW)
 *
 * IO usage:
 * 0:NMII_LINK0
 * 1:NMII_LINK1
 * 2:NMII_LINK2
 * 3:LINK_ACT0
 * 4:LINK_ACT1
 * 5:LINK_ACT2
 * 6:LED_RUN
 * 7:LED_ERR
 * 8:RESET_OUT
 */
#define ESC_IO_CFG_FUNC_ALT_MASK (0xFU)
#define ESC_IO_CFG_FUNC_ALT_SHIFT (0U)
#define ESC_IO_CFG_FUNC_ALT_SET(x) (((uint32_t)(x) << ESC_IO_CFG_FUNC_ALT_SHIFT) & ESC_IO_CFG_FUNC_ALT_MASK)
#define ESC_IO_CFG_FUNC_ALT_GET(x) (((uint32_t)(x) & ESC_IO_CFG_FUNC_ALT_MASK) >> ESC_IO_CFG_FUNC_ALT_SHIFT)



/* RX_ERR_CNT register group index macro definition */
#define ESC_RX_ERR_CNT_PORT0 (0UL)
#define ESC_RX_ERR_CNT_PORT1 (1UL)
#define ESC_RX_ERR_CNT_PORT2 (2UL)
#define ESC_RX_ERR_CNT_PORT3 (3UL)

/* FWD_RX_ERR_CNT register group index macro definition */
#define ESC_FWD_RX_ERR_CNT_PORT0 (0UL)
#define ESC_FWD_RX_ERR_CNT_PORT1 (1UL)
#define ESC_FWD_RX_ERR_CNT_PORT2 (2UL)
#define ESC_FWD_RX_ERR_CNT_PORT3 (3UL)

/* LOST_LINK_CNT register group index macro definition */
#define ESC_LOST_LINK_CNT_PORT0 (0UL)
#define ESC_LOST_LINK_CNT_PORT1 (1UL)
#define ESC_LOST_LINK_CNT_PORT2 (2UL)
#define ESC_LOST_LINK_CNT_PORT3 (3UL)

/* PHY_STAT register group index macro definition */
#define ESC_PHY_STAT_PORT0 (0UL)
#define ESC_PHY_STAT_PORT1 (1UL)
#define ESC_PHY_STAT_PORT2 (2UL)
#define ESC_PHY_STAT_PORT3 (3UL)

/* FMMU register group index macro definition */
#define ESC_FMMU_0 (0UL)
#define ESC_FMMU_1 (1UL)
#define ESC_FMMU_2 (2UL)
#define ESC_FMMU_3 (3UL)
#define ESC_FMMU_4 (4UL)
#define ESC_FMMU_5 (5UL)
#define ESC_FMMU_6 (6UL)
#define ESC_FMMU_7 (7UL)

/* SYNCM register group index macro definition */
#define ESC_SYNCM_0 (0UL)
#define ESC_SYNCM_1 (1UL)
#define ESC_SYNCM_2 (2UL)
#define ESC_SYNCM_3 (3UL)
#define ESC_SYNCM_4 (4UL)
#define ESC_SYNCM_5 (5UL)
#define ESC_SYNCM_6 (6UL)
#define ESC_SYNCM_7 (7UL)

/* RCV_TIME register group index macro definition */
#define ESC_RCV_TIME_PORT0 (0UL)
#define ESC_RCV_TIME_PORT1 (1UL)
#define ESC_RCV_TIME_PORT2 (2UL)
#define ESC_RCV_TIME_PORT3 (3UL)

/* IO_CFG register group index macro definition */
#define ESC_IO_CFG_CTR0 (0UL)
#define ESC_IO_CFG_CTR1 (1UL)
#define ESC_IO_CFG_CTR2 (2UL)
#define ESC_IO_CFG_CTR3 (3UL)
#define ESC_IO_CFG_CTR4 (4UL)
#define ESC_IO_CFG_CTR5 (5UL)
#define ESC_IO_CFG_CTR6 (6UL)
#define ESC_IO_CFG_CTR7 (7UL)
#define ESC_IO_CFG_CTR8 (8UL)


#endif /* HPM_ESC_H */

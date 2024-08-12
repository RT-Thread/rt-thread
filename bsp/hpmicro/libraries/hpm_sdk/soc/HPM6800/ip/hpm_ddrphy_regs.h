/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_DDRPHY_H
#define HPM_DDRPHY_H

typedef struct {
    __R  uint32_t RIDR;                        /* 0x0: Revision Identification Register */
    __RW uint32_t PIR;                         /* 0x4: PHY Initialization Register (PIR) */
    __RW uint32_t PGCR0;                       /* 0x8: PHY General Configuration Registers 0-1 (PGCR0- 1) */
    __RW uint32_t PGCR1;                       /* 0xC: PHY General Configuration Registers 0-1 (PGCR0- 1) */
    __R  uint32_t PGSR0;                       /* 0x10: “PHY General Status Registers 0-1 (PGSR0-1)” on page 89 */
    __R  uint32_t PGSR1;                       /* 0x14: “PHY General Status Registers 0-1 (PGSR0-1)” on page 89 */
    __RW uint32_t PLLCR;                       /* 0x18: “PLL Control Register (PLLCR)” on page 91 */
    __RW uint32_t PTR0;                        /* 0x1C: PHY Timing Registers 0-4 (PTR0-4) */
    __RW uint32_t PTR1;                        /* 0x20: PHY Timing Registers 0-4 (PTR0-4) */
    __RW uint32_t PTR2;                        /* 0x24: PHY Timing Registers 0-4 (PTR0-4) */
    __RW uint32_t PTR3;                        /* 0x28: PHY Timing Registers 0-4 (PTR0-4) */
    __RW uint32_t PTR4;                        /* 0x2C: PHY Timing Registers 0-4 (PTR0-4) */
    __RW uint32_t ACMDLR;                      /* 0x30: “AC Master Delay Line Register (ACMDLR)” on page 96 */
    __RW uint32_t ACBDLR;                      /* 0x34: “AC Bit Delay Line Register (ACBDLR)” on page 96 */
    __RW uint32_t ACIOCR;                      /* 0x38: “AC I/O Configuration Register (ACIOCR)” on page 97 */
    __RW uint32_t DXCCR;                       /* 0x3C: “DATX8 Common Configuration Register (DXCCR)” on page 99 */
    __RW uint32_t DSGCR;                       /* 0x40: “DDR System General Configuration Register (DSGCR)” on page 101 */
    __RW uint32_t DCR;                         /* 0x44: “DRAM Configuration Register (DCR)” on page 103 */
    __RW uint32_t DTPR0;                       /* 0x48: DRAM Timing Parameters Register 0-2 (DTPR0-2) */
    __RW uint32_t DTPR1;                       /* 0x4C: DRAM Timing Parameters Register 0-2 (DTPR0-2) */
    __RW uint32_t DTPR2;                       /* 0x50: DRAM Timing Parameters Register 0-2 (DTPR0-2) */
    union {
        __RW uint32_t MR0;                     /* 0x54: “Mode Register 0 (MR0)” on page 108 */
        __RW uint32_t MR;                      /* 0x54:  */
    };
    union {
        __RW uint32_t MR1;                     /* 0x58: “Mode Register 1 (MR1)” on page 111 */
        __RW uint32_t EMR;                     /* 0x58:  */
    };
    union {
        __RW uint32_t MR2;                     /* 0x5C: “Mode Register 2/Extended Mode Register 2 (MR2/EMR2)” on page 114 */
        __RW uint32_t EMR2;                    /* 0x5C:  */
    };
    union {
        __RW uint32_t MR3;                     /* 0x60: “Mode Register 3 (MR3)” on page 116 */
        __RW uint32_t EMR3;                    /* 0x60:  */
    };
    __RW uint32_t ODTCR;                       /* 0x64: “ODT Configuration Register (ODTCR)” on page 117 */
    __RW uint32_t DTCR;                        /* 0x68: “Data Training Configuration Register (DTCR)” on page 118 */
    __RW uint32_t DTAR0;                       /* 0x6C: Data Training Address Register 0-3 (DTAR0-3) */
    __RW uint32_t DTAR1;                       /* 0x70: Data Training Address Register 0-3 (DTAR0-3) */
    __RW uint32_t DTAR2;                       /* 0x74: Data Training Address Register 0-3 (DTAR0-3) */
    __RW uint32_t DTAR3;                       /* 0x78: Data Training Address Register 0-3 (DTAR0-3) */
    __RW uint32_t DTDR0;                       /* 0x7C: Data Training Eye Data Register 0-1 (DTEDR0-1) */
    __RW uint32_t DTDR1;                       /* 0x80: Data Training Eye Data Register 0-1 (DTEDR0-1) */
    __R  uint32_t DTEDR0;                      /* 0x84: Data Training Eye Data Register 0-1 (DTEDR0-1) */
    __R  uint32_t DTEDR1;                      /* 0x88: Data Training Eye Data Register 0-1 (DTEDR0-1) */
    __RW uint32_t PGCR2;                       /* 0x8C: “PHY General Configuration Register 2 (PGCR2)” on page 87 */
    __R  uint8_t  RESERVED0[32];               /* 0x90 - 0xAF: Reserved */
    __R  uint32_t RDIMMGCR0;                   /* 0xB0: RDIMM General Configuration Register 0-1 (RDIMMGCR0-1) */
    __R  uint32_t RDIMMGCR1;                   /* 0xB4: RDIMM General Configuration Register 0-1 (RDIMMGCR0-1) */
    __R  uint32_t RDIMMCR0;                    /* 0xB8: RDIMM Control Register 0-1 (RDIMMCR0-1) */
    __R  uint32_t RDIMMCR1;                    /* 0xBC: RDIMM Control Register 0-1 (RDIMMCR0-1) */
    __RW uint32_t DCUAR;                       /* 0xC0: “DCU Address Register (DCUAR)” on page 129 */
    __RW uint32_t DCUDR;                       /* 0xC4: “DCU Data Register (DCUDR)” on page 130 */
    __RW uint32_t DCURR;                       /* 0xC8: “DCU Run Register (DCURR)” on page 130 */
    __RW uint32_t DCULR;                       /* 0xCC: “DCU Loop Register (DCULR)” on page 131 */
    __RW uint32_t DCUGCR;                      /* 0xD0: “DCU General Configuration Register (DCUGCR)” on page 132 */
    __RW uint32_t DCUTPR;                      /* 0xD4: “DCU Timing Parameter Register (DCUTPR)” on page 132 */
    __R  uint32_t DCUSR0;                      /* 0xD8: DCU Status Register 0-1 (DCUSR0-1) */
    __R  uint32_t DCUSR1;                      /* 0xDC: DCU Status Register 0-1 (DCUSR0-1) */
    __R  uint8_t  RESERVED1[32];               /* 0xE0 - 0xFF: Reserved */
    __RW uint32_t BISTRR;                      /* 0x100: “BIST Run Register (BISTRR)” on page 133 */
    __RW uint32_t BISTWCR;                     /* 0x104: “BIST Word Count Register (BISTWCR)” on page 136 */
    __RW uint32_t BISTMSKR0;                   /* 0x108: BIST Mask Register 0-2 (BISTMSKR0-2) */
    __RW uint32_t BISTMSKR1;                   /* 0x10C: BIST Mask Register 0-2 (BISTMSKR0-2) */
    __RW uint32_t BISTMSKR2;                   /* 0x110: BIST Mask Register 0-2 (BISTMSKR0-2) */
    __RW uint32_t BISTLSR;                     /* 0x114: “BIST LFSR Seed Register (BISTLSR)” on page 137 */
    __RW uint32_t BISTAR0;                     /* 0x118: BIST Address Register 0-2 (BISTAR0-2) */
    __RW uint32_t BISTAR1;                     /* 0x11C: BIST Address Register 0-2 (BISTAR0-2) */
    __RW uint32_t BISTAR2;                     /* 0x120: BIST Address Register 0-2 (BISTAR0-2) */
    __RW uint32_t BISTUDPR;                    /* 0x124: “BIST User Data Pattern Register (BISTUDPR)” on page 138 */
    __R  uint32_t BISTGSR;                     /* 0x128: “BIST General Status Register (BISTGSR)” on page 139 */
    __R  uint32_t BISTWER;                     /* 0x12C: “BIST Word Error Register (BISTWER)” on page 139 */
    __R  uint32_t BISTBER0;                    /* 0x130: BIST Bit Error Register 0-3 (BISTBER0-3) */
    __R  uint32_t BISTBER1;                    /* 0x134: BIST Bit Error Register 0-3 (BISTBER0-3) */
    __R  uint32_t BISTBER2;                    /* 0x138: BIST Bit Error Register 0-3 (BISTBER0-3) */
    __R  uint32_t BISTBER3;                    /* 0x13C: BIST Bit Error Register 0-3 (BISTBER0-3) */
    __R  uint32_t BISTWCSR;                    /* 0x140: “BIST Word Count Status Register (BISTWCSR)” on page 141 */
    __R  uint32_t BISTFWR0;                    /* 0x144: BIST Fail Word Register 0-2 (BISTFWR0-2) */
    __R  uint32_t BISTFWR1;                    /* 0x148: BIST Fail Word Register 0-2 (BISTFWR0-2) */
    __R  uint32_t BISTFWR2;                    /* 0x14C: BIST Fail Word Register 0-2 (BISTFWR0-2) */
    __R  uint8_t  RESERVED2[36];               /* 0x150 - 0x173: Reserved */
    __RW uint32_t AACR;                        /* 0x174: “Anti-Aging Control Register (AACR)” on page 143 */
    __RW uint32_t GPR0;                        /* 0x178: General Purpose Register 0-1 (GPR0-1) */
    __RW uint32_t GPR1;                        /* 0x17C: General Purpose Register 0-1 (GPR0-1) */
    struct {
        __RW uint32_t CR0;                     /* 0x180: Impedance Control Register 0-1 (ZQnCR0-1) */
        __RW uint32_t CR1;                     /* 0x184: Impedance Control Register 0-1 (ZQnCR0-1) */
        __R  uint32_t SR0;                     /* 0x188: Impedance Status Register 0-1 (ZQnSR0-1) */
        __R  uint32_t SR1;                     /* 0x18C: Impedance Status Register 0-1 (ZQnSR0-1) */
    } ZQ[4];
    struct {
        __RW uint32_t GCR;                     /* 0x1C0: “DATX8 General Configuration Register (DXnGCR)” on page 148 */
        __R  uint32_t GSR0;                    /* 0x1C4: DATX8 General Status Registers 0-2 (DXnGSR0-2) */
        __R  uint32_t GSR1;                    /* 0x1C8: DATX8 General Status Registers 0-2 (DXnGSR0-2) */
        __RW uint32_t BDLR0;                   /* 0x1CC: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t BDLR1;                   /* 0x1D0: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t BDLR2;                   /* 0x1D4: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t BDLR3;                   /* 0x1D8: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t BDLR4;                   /* 0x1DC: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t LCDLR0;                  /* 0x1E0: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t LCDLR1;                  /* 0x1E4: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t LCDLR2;                  /* 0x1E8: DATX8 Bit Delay Line Register 0-4 (DXnBDLR0-4) */
        __RW uint32_t MDLR;                    /* 0x1EC: “DATX8 Master Delay Line Register (DXnMDLR)” on page 157 */
        __RW uint32_t GTR;                     /* 0x1F0: “DATX8 General Timing Register (DXnGTR)” on page 159 */
        __RW uint32_t GSR2;                    /* 0x1F4: “DATX8 General Status Register 2 (DXnGSR2)” on page 152 */
        __R  uint8_t  RESERVED0[8];            /* 0x1F8 - 0x1FF: Reserved */
    } DX[9];
} DDRPHY_Type;


/* Bitfield definition for register: RIDR */
/*
 * UDRID (R)
 *
 * User-Defined Revision ID: General purpose revision identification set by the user.
 */
#define DDRPHY_RIDR_UDRID_MASK (0xFF000000UL)
#define DDRPHY_RIDR_UDRID_SHIFT (24U)
#define DDRPHY_RIDR_UDRID_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_UDRID_MASK) >> DDRPHY_RIDR_UDRID_SHIFT)

/*
 * PHYMJR (R)
 *
 * PHY Major Revision: Indicates major revision of the PHY such addition of the features that make the new version not compatible with previous versions.
 */
#define DDRPHY_RIDR_PHYMJR_MASK (0xF00000UL)
#define DDRPHY_RIDR_PHYMJR_SHIFT (20U)
#define DDRPHY_RIDR_PHYMJR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PHYMJR_MASK) >> DDRPHY_RIDR_PHYMJR_SHIFT)

/*
 * PHYMDR (R)
 *
 * PHY Moderate Revision: Indicates moderate revision of the PHY such as addition of new features. Normally the new version is still compatible with previous versions.
 */
#define DDRPHY_RIDR_PHYMDR_MASK (0xF0000UL)
#define DDRPHY_RIDR_PHYMDR_SHIFT (16U)
#define DDRPHY_RIDR_PHYMDR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PHYMDR_MASK) >> DDRPHY_RIDR_PHYMDR_SHIFT)

/*
 * PHYMNR (R)
 *
 * PHY Minor Revision: Indicates minor update of the PHY such as bug fixes. Normally no new features are included.
 */
#define DDRPHY_RIDR_PHYMNR_MASK (0xF000U)
#define DDRPHY_RIDR_PHYMNR_SHIFT (12U)
#define DDRPHY_RIDR_PHYMNR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PHYMNR_MASK) >> DDRPHY_RIDR_PHYMNR_SHIFT)

/*
 * PUBMJR (R)
 *
 * PUB Major Revision: Indicates major revision of the PUB such addition of the features that make the new version not compatible with previous versions.
 */
#define DDRPHY_RIDR_PUBMJR_MASK (0xF00U)
#define DDRPHY_RIDR_PUBMJR_SHIFT (8U)
#define DDRPHY_RIDR_PUBMJR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PUBMJR_MASK) >> DDRPHY_RIDR_PUBMJR_SHIFT)

/*
 * PUBMDR (R)
 *
 * PUB Moderate Revision: Indicates moderate revision of the PUB such as addition of new features. Normally the new version is still compatible with previous versions.
 */
#define DDRPHY_RIDR_PUBMDR_MASK (0xF0U)
#define DDRPHY_RIDR_PUBMDR_SHIFT (4U)
#define DDRPHY_RIDR_PUBMDR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PUBMDR_MASK) >> DDRPHY_RIDR_PUBMDR_SHIFT)

/*
 * PUBMNR (R)
 *
 * PUB Minor Revision: Indicates minor update of the PUB such as bug fixes. Normally no new features are included.
 */
#define DDRPHY_RIDR_PUBMNR_MASK (0xFU)
#define DDRPHY_RIDR_PUBMNR_SHIFT (0U)
#define DDRPHY_RIDR_PUBMNR_GET(x) (((uint32_t)(x) & DDRPHY_RIDR_PUBMNR_MASK) >> DDRPHY_RIDR_PUBMNR_SHIFT)

/* Bitfield definition for register: PIR */
/*
 * INITBYP (R/W)
 *
 * Initialization Bypass: Bypasses or stops, if set, all initialization routines currently running, including PHY initialization, DRAM initialization, and PHY training.
 * Initialization may be triggered manually using INIT and the other relevant bits of the PIR register. This bit is self-clearing.
 */
#define DDRPHY_PIR_INITBYP_MASK (0x80000000UL)
#define DDRPHY_PIR_INITBYP_SHIFT (31U)
#define DDRPHY_PIR_INITBYP_SET(x) (((uint32_t)(x) << DDRPHY_PIR_INITBYP_SHIFT) & DDRPHY_PIR_INITBYP_MASK)
#define DDRPHY_PIR_INITBYP_GET(x) (((uint32_t)(x) & DDRPHY_PIR_INITBYP_MASK) >> DDRPHY_PIR_INITBYP_SHIFT)

/*
 * ZCALBYP (R/W)
 *
 * Impedance Calibration Bypass: Bypasses or stops, if set, impedance calibration of all ZQ control blocks that automatically triggers after reset. Impedance calibration may be triggered manually using INIT and ZCAL bits of the PIR register. This bit is self-clearing.
 */
#define DDRPHY_PIR_ZCALBYP_MASK (0x40000000UL)
#define DDRPHY_PIR_ZCALBYP_SHIFT (30U)
#define DDRPHY_PIR_ZCALBYP_SET(x) (((uint32_t)(x) << DDRPHY_PIR_ZCALBYP_SHIFT) & DDRPHY_PIR_ZCALBYP_MASK)
#define DDRPHY_PIR_ZCALBYP_GET(x) (((uint32_t)(x) & DDRPHY_PIR_ZCALBYP_MASK) >> DDRPHY_PIR_ZCALBYP_SHIFT)

/*
 * DCALBYP (R/W)
 *
 * Digital Delay Line (DDL) Calibration Bypass: Bypasses or stops, if set, DDL calibration that automatically triggers after reset. DDL calibration may be triggered manually using INIT and DCAL bits of the PIR register. This bit is self- clearing.
 */
#define DDRPHY_PIR_DCALBYP_MASK (0x20000000UL)
#define DDRPHY_PIR_DCALBYP_SHIFT (29U)
#define DDRPHY_PIR_DCALBYP_SET(x) (((uint32_t)(x) << DDRPHY_PIR_DCALBYP_SHIFT) & DDRPHY_PIR_DCALBYP_MASK)
#define DDRPHY_PIR_DCALBYP_GET(x) (((uint32_t)(x) & DDRPHY_PIR_DCALBYP_MASK) >> DDRPHY_PIR_DCALBYP_SHIFT)

/*
 * LOCKBYP (R/W)
 *
 * PLL Lock Bypass: Bypasses or stops, if set, the waiting of PLLs to lock. PLL lock wait is automatically triggered after reset. PLL lock wait may be triggered manually using INIT and PLLINIT bits of the PIR register. This bit is self-clearing.
 */
#define DDRPHY_PIR_LOCKBYP_MASK (0x10000000UL)
#define DDRPHY_PIR_LOCKBYP_SHIFT (28U)
#define DDRPHY_PIR_LOCKBYP_SET(x) (((uint32_t)(x) << DDRPHY_PIR_LOCKBYP_SHIFT) & DDRPHY_PIR_LOCKBYP_MASK)
#define DDRPHY_PIR_LOCKBYP_GET(x) (((uint32_t)(x) & DDRPHY_PIR_LOCKBYP_MASK) >> DDRPHY_PIR_LOCKBYP_SHIFT)

/*
 * CLRSR (R/W)
 *
 * Clear Status Registers: Writing 1 to this bit clears (reset to 0) select status bits in register PGSR0.
 * This bit is primarily for debug purposes and is typically not needed during normal functional operation. It can be used when PGSR.IDONE=1, to manually clear a selection of the PGSR status bits, although starting a new initialization process (PIR[0].INIT = 1’b1) automatically clears the PGSR status bits associated with the initialization steps enabled.
 * The following list describes which bits within the PGSR0 register are cleared when CLRSR is set to 1’b1 and which bits are not cleared:
 * The following bits are not cleared by PIR[27] (CLRSR):
 * PGSR0[31] (APLOCK)
 * PGSR0[29:28] (PLDONE_CHN)
 * PGSR0[23] (WLAERR)
 * PGSR0[21] (WLERR)
 * PGSR0[4] (DIDONE)
 * PGSR0[2] (DCDONE)
 * PGSR0[1] (PLDONE)
 * PGSR0[0] (IDONE)
 * The following bits are always zero:
 * PGSR0[30] (reserved)
 * PGSR0[19:12] (reserved)
 * The following bits are cleared unconditionally by PIR[27] (CLRSR):
 * PGSR0[27] (WEERR)
 * PGSR0[26] (REERR)
 * PGSR0[25] (WDERR)
 * PGSR0[24] (RDERR)
 * - PGSR0[22] (QSGERR)
 * - PGSR0[20] (ZCERR)
 * - PGSR0[11] (WEDONE)
 * - PGSR0[10] (REDONE)
 * - PGSR0[9] (WDDONE)
 * - PGSR0[8] (RDDONE)
 * - PGSR0[7] (WLADONE)
 * - PGSR0[6] (QSGDONE)
 * - PGSR0[5] (WLDONE)
 * - PGSR0[3] (ZCDONE)
 */
#define DDRPHY_PIR_CLRSR_MASK (0x8000000UL)
#define DDRPHY_PIR_CLRSR_SHIFT (27U)
#define DDRPHY_PIR_CLRSR_SET(x) (((uint32_t)(x) << DDRPHY_PIR_CLRSR_SHIFT) & DDRPHY_PIR_CLRSR_MASK)
#define DDRPHY_PIR_CLRSR_GET(x) (((uint32_t)(x) & DDRPHY_PIR_CLRSR_MASK) >> DDRPHY_PIR_CLRSR_SHIFT)

/*
 * RDIMMINIT (R/W)
 *
 * RDIMM Initialization: Executes the RDIMM buffer chip initialization before executing DRAM initialization. The RDIMM buffer chip initialization is run after the DRAM is reset and CKE have been driven high by the DRAM initialization sequence.
 */
#define DDRPHY_PIR_RDIMMINIT_MASK (0x80000UL)
#define DDRPHY_PIR_RDIMMINIT_SHIFT (19U)
#define DDRPHY_PIR_RDIMMINIT_SET(x) (((uint32_t)(x) << DDRPHY_PIR_RDIMMINIT_SHIFT) & DDRPHY_PIR_RDIMMINIT_MASK)
#define DDRPHY_PIR_RDIMMINIT_GET(x) (((uint32_t)(x) & DDRPHY_PIR_RDIMMINIT_MASK) >> DDRPHY_PIR_RDIMMINIT_SHIFT)

/*
 * CTLDINIT (R/W)
 *
 * Controller DRAM Initialization: Indicates, if set, that DRAM initialization will be performed by the controller. Otherwise if not set it indicates that DRAM initialization will be performed using the built-in initialization sequence or using software through the configuration port.
 */
#define DDRPHY_PIR_CTLDINIT_MASK (0x40000UL)
#define DDRPHY_PIR_CTLDINIT_SHIFT (18U)
#define DDRPHY_PIR_CTLDINIT_SET(x) (((uint32_t)(x) << DDRPHY_PIR_CTLDINIT_SHIFT) & DDRPHY_PIR_CTLDINIT_MASK)
#define DDRPHY_PIR_CTLDINIT_GET(x) (((uint32_t)(x) & DDRPHY_PIR_CTLDINIT_MASK) >> DDRPHY_PIR_CTLDINIT_SHIFT)

/*
 * PLLBYP (R/W)
 *
 * PLL Bypass: A setting of 1 on this bit will put all PHY PLLs in bypass mode.
 */
#define DDRPHY_PIR_PLLBYP_MASK (0x20000UL)
#define DDRPHY_PIR_PLLBYP_SHIFT (17U)
#define DDRPHY_PIR_PLLBYP_SET(x) (((uint32_t)(x) << DDRPHY_PIR_PLLBYP_SHIFT) & DDRPHY_PIR_PLLBYP_MASK)
#define DDRPHY_PIR_PLLBYP_GET(x) (((uint32_t)(x) & DDRPHY_PIR_PLLBYP_MASK) >> DDRPHY_PIR_PLLBYP_SHIFT)

/*
 * ICPC (R/W)
 *
 * Initialization Complete Pin Configuration: Specifies how the DFI initialization complete output pin (dfi_init_complete) should be used to indicate the status of initialization. Valid value are:
 * 0 = Asserted after PHY initialization (DLL locking and impedance calibration) is complete.
 * 1 = Asserted after PHY initialization is complete and the triggered the PUB initialization (DRAM initialization, data training, or initialization trigger with no selected initialization) is complete.
 */
#define DDRPHY_PIR_ICPC_MASK (0x10000UL)
#define DDRPHY_PIR_ICPC_SHIFT (16U)
#define DDRPHY_PIR_ICPC_SET(x) (((uint32_t)(x) << DDRPHY_PIR_ICPC_SHIFT) & DDRPHY_PIR_ICPC_MASK)
#define DDRPHY_PIR_ICPC_GET(x) (((uint32_t)(x) & DDRPHY_PIR_ICPC_MASK) >> DDRPHY_PIR_ICPC_SHIFT)

/*
 * WREYE (R/W)
 *
 * Write Data Eye Training: Executes a PUB training routine to maximize the write data eye.
 */
#define DDRPHY_PIR_WREYE_MASK (0x8000U)
#define DDRPHY_PIR_WREYE_SHIFT (15U)
#define DDRPHY_PIR_WREYE_SET(x) (((uint32_t)(x) << DDRPHY_PIR_WREYE_SHIFT) & DDRPHY_PIR_WREYE_MASK)
#define DDRPHY_PIR_WREYE_GET(x) (((uint32_t)(x) & DDRPHY_PIR_WREYE_MASK) >> DDRPHY_PIR_WREYE_SHIFT)

/*
 * RDEYE (R/W)
 *
 * Read Data Eye Training: Executes a PUB training routine to maximize the read data eye.
 */
#define DDRPHY_PIR_RDEYE_MASK (0x4000U)
#define DDRPHY_PIR_RDEYE_SHIFT (14U)
#define DDRPHY_PIR_RDEYE_SET(x) (((uint32_t)(x) << DDRPHY_PIR_RDEYE_SHIFT) & DDRPHY_PIR_RDEYE_MASK)
#define DDRPHY_PIR_RDEYE_GET(x) (((uint32_t)(x) & DDRPHY_PIR_RDEYE_MASK) >> DDRPHY_PIR_RDEYE_SHIFT)

/*
 * WRDSKW (R/W)
 *
 * Write Data Bit Deskew: Executes a PUB training routine to deskew the DQ bits during write.
 */
#define DDRPHY_PIR_WRDSKW_MASK (0x2000U)
#define DDRPHY_PIR_WRDSKW_SHIFT (13U)
#define DDRPHY_PIR_WRDSKW_SET(x) (((uint32_t)(x) << DDRPHY_PIR_WRDSKW_SHIFT) & DDRPHY_PIR_WRDSKW_MASK)
#define DDRPHY_PIR_WRDSKW_GET(x) (((uint32_t)(x) & DDRPHY_PIR_WRDSKW_MASK) >> DDRPHY_PIR_WRDSKW_SHIFT)

/*
 * RDDSKW (R/W)
 *
 * Read Data Bit Deskew: Executes a PUB training routine to deskew the DQ bits during read.
 */
#define DDRPHY_PIR_RDDSKW_MASK (0x1000U)
#define DDRPHY_PIR_RDDSKW_SHIFT (12U)
#define DDRPHY_PIR_RDDSKW_SET(x) (((uint32_t)(x) << DDRPHY_PIR_RDDSKW_SHIFT) & DDRPHY_PIR_RDDSKW_MASK)
#define DDRPHY_PIR_RDDSKW_GET(x) (((uint32_t)(x) & DDRPHY_PIR_RDDSKW_MASK) >> DDRPHY_PIR_RDDSKW_SHIFT)

/*
 * WLADJ (R/W)
 *
 * Write Leveling Adjust (DDR3 Only): Executes a PUB training routine that re- adjusts the write latency used during write in case the write leveling routine changed the expected latency.
 * Note: Ensure that the DCU command cache is cleared prior to running WLADJ.
 */
#define DDRPHY_PIR_WLADJ_MASK (0x800U)
#define DDRPHY_PIR_WLADJ_SHIFT (11U)
#define DDRPHY_PIR_WLADJ_SET(x) (((uint32_t)(x) << DDRPHY_PIR_WLADJ_SHIFT) & DDRPHY_PIR_WLADJ_MASK)
#define DDRPHY_PIR_WLADJ_GET(x) (((uint32_t)(x) & DDRPHY_PIR_WLADJ_MASK) >> DDRPHY_PIR_WLADJ_SHIFT)

/*
 * QSGATE (R/W)
 *
 * Read DQS Gate Training: Executes a PUB training routine to determine the optimum position of the read data DQS strobe for maximum system timing margins.
 */
#define DDRPHY_PIR_QSGATE_MASK (0x400U)
#define DDRPHY_PIR_QSGATE_SHIFT (10U)
#define DDRPHY_PIR_QSGATE_SET(x) (((uint32_t)(x) << DDRPHY_PIR_QSGATE_SHIFT) & DDRPHY_PIR_QSGATE_MASK)
#define DDRPHY_PIR_QSGATE_GET(x) (((uint32_t)(x) & DDRPHY_PIR_QSGATE_MASK) >> DDRPHY_PIR_QSGATE_SHIFT)

/*
 * WL (R/W)
 *
 * Write Leveling (DDR3 Only): Executes a PUB write leveling routine.
 */
#define DDRPHY_PIR_WL_MASK (0x200U)
#define DDRPHY_PIR_WL_SHIFT (9U)
#define DDRPHY_PIR_WL_SET(x) (((uint32_t)(x) << DDRPHY_PIR_WL_SHIFT) & DDRPHY_PIR_WL_MASK)
#define DDRPHY_PIR_WL_GET(x) (((uint32_t)(x) & DDRPHY_PIR_WL_MASK) >> DDRPHY_PIR_WL_SHIFT)

/*
 * DRAMINIT (R/W)
 *
 * DRAM Initialization: Executes the DRAM initialization sequence.
 */
#define DDRPHY_PIR_DRAMINIT_MASK (0x100U)
#define DDRPHY_PIR_DRAMINIT_SHIFT (8U)
#define DDRPHY_PIR_DRAMINIT_SET(x) (((uint32_t)(x) << DDRPHY_PIR_DRAMINIT_SHIFT) & DDRPHY_PIR_DRAMINIT_MASK)
#define DDRPHY_PIR_DRAMINIT_GET(x) (((uint32_t)(x) & DDRPHY_PIR_DRAMINIT_MASK) >> DDRPHY_PIR_DRAMINIT_SHIFT)

/*
 * DRAMRST (R/W)
 *
 * DRAM Reset (DDR3 Only): Issues a reset to the DRAM (by driving the DRAM reset pin low) and wait 200us. This can be triggered in isolation or with the full DRAM initialization (DRAMINIT). For the later case, the reset is issued and 200us is waited before starting the full initialization sequence.
 */
#define DDRPHY_PIR_DRAMRST_MASK (0x80U)
#define DDRPHY_PIR_DRAMRST_SHIFT (7U)
#define DDRPHY_PIR_DRAMRST_SET(x) (((uint32_t)(x) << DDRPHY_PIR_DRAMRST_SHIFT) & DDRPHY_PIR_DRAMRST_MASK)
#define DDRPHY_PIR_DRAMRST_GET(x) (((uint32_t)(x) & DDRPHY_PIR_DRAMRST_MASK) >> DDRPHY_PIR_DRAMRST_SHIFT)

/*
 * PHYRST (R/W)
 *
 * PHY Reset: Resets the AC and DATX8 modules by asserting the AC/DATX8 reset pin.
 */
#define DDRPHY_PIR_PHYRST_MASK (0x40U)
#define DDRPHY_PIR_PHYRST_SHIFT (6U)
#define DDRPHY_PIR_PHYRST_SET(x) (((uint32_t)(x) << DDRPHY_PIR_PHYRST_SHIFT) & DDRPHY_PIR_PHYRST_MASK)
#define DDRPHY_PIR_PHYRST_GET(x) (((uint32_t)(x) & DDRPHY_PIR_PHYRST_MASK) >> DDRPHY_PIR_PHYRST_SHIFT)

/*
 * DCAL (R/W)
 *
 * Digital Delay Line (DDL) Calibration: Performs PHY delay line calibration.
 */
#define DDRPHY_PIR_DCAL_MASK (0x20U)
#define DDRPHY_PIR_DCAL_SHIFT (5U)
#define DDRPHY_PIR_DCAL_SET(x) (((uint32_t)(x) << DDRPHY_PIR_DCAL_SHIFT) & DDRPHY_PIR_DCAL_MASK)
#define DDRPHY_PIR_DCAL_GET(x) (((uint32_t)(x) & DDRPHY_PIR_DCAL_MASK) >> DDRPHY_PIR_DCAL_SHIFT)

/*
 * PLLINIT (R/W)
 *
 * PLL Initialization: Executes the PLL initialization sequence which includes correct driving of PLL power-down, reset and gear shift pins, and then waiting for the PHY PLLs to lock.
 */
#define DDRPHY_PIR_PLLINIT_MASK (0x10U)
#define DDRPHY_PIR_PLLINIT_SHIFT (4U)
#define DDRPHY_PIR_PLLINIT_SET(x) (((uint32_t)(x) << DDRPHY_PIR_PLLINIT_SHIFT) & DDRPHY_PIR_PLLINIT_MASK)
#define DDRPHY_PIR_PLLINIT_GET(x) (((uint32_t)(x) & DDRPHY_PIR_PLLINIT_MASK) >> DDRPHY_PIR_PLLINIT_SHIFT)

/*
 * ZCAL (R/W)
 *
 * Impedance Calibration: Performs PHY impedance calibration. When set the impedance calibration will be performed in parallel with PHY initialization (PLL initialization + DDL calibration + PHY reset).
 */
#define DDRPHY_PIR_ZCAL_MASK (0x2U)
#define DDRPHY_PIR_ZCAL_SHIFT (1U)
#define DDRPHY_PIR_ZCAL_SET(x) (((uint32_t)(x) << DDRPHY_PIR_ZCAL_SHIFT) & DDRPHY_PIR_ZCAL_MASK)
#define DDRPHY_PIR_ZCAL_GET(x) (((uint32_t)(x) & DDRPHY_PIR_ZCAL_MASK) >> DDRPHY_PIR_ZCAL_SHIFT)

/*
 * INIT (R/W)
 *
 * Initialization Trigger: A write of '1' to this bit triggers the DDR system initialization, including PHY initialization, DRAM initialization, and PHY training. The exact initialization steps to be executed are specified in bits 1 to 15 of this register. A bit setting of 1 means the step will be executed as part of the initialization sequence, while a setting of ‘0’ means the step will be bypassed. The initialization trigger bit is self-clearing.
 */
#define DDRPHY_PIR_INIT_MASK (0x1U)
#define DDRPHY_PIR_INIT_SHIFT (0U)
#define DDRPHY_PIR_INIT_SET(x) (((uint32_t)(x) << DDRPHY_PIR_INIT_SHIFT) & DDRPHY_PIR_INIT_MASK)
#define DDRPHY_PIR_INIT_GET(x) (((uint32_t)(x) & DDRPHY_PIR_INIT_MASK) >> DDRPHY_PIR_INIT_SHIFT)

/* Bitfield definition for register: PGCR0 */
/*
 * CKEN (R/W)
 *
 * CK Enable: Controls whether the CK going to the SDRAM is enabled (toggling) or disabled (static value) and whether the CK is inverted. Two bits for each of the up to three CK pairs. Valid values for the two bits are:
 * 00 = CK disabled (Driven to constant 0) 01 = CK toggling with inverted polarity
 * 10 = CK toggling with normal polarity (This should be the default setting) 11 = CK disabled (Driven to constant 1)
 */
#define DDRPHY_PGCR0_CKEN_MASK (0xFC000000UL)
#define DDRPHY_PGCR0_CKEN_SHIFT (26U)
#define DDRPHY_PGCR0_CKEN_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_CKEN_SHIFT) & DDRPHY_PGCR0_CKEN_MASK)
#define DDRPHY_PGCR0_CKEN_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_CKEN_MASK) >> DDRPHY_PGCR0_CKEN_SHIFT)

/*
 * PUBMODE (R/W)
 *
 * Enables, if set, the PUB to control the interface to the PHY and SDRAM. In this mode the DFI commands from the controller are ignored. The bit must be set to 0 after the system determines it is convenient to pass control of the DFI bus to the controller. When set to 0 the DFI interface has control of the PHY and SDRAM interface except when triggering pub operations such as BIST, DCU or data training.
 */
#define DDRPHY_PGCR0_PUBMODE_MASK (0x2000000UL)
#define DDRPHY_PGCR0_PUBMODE_SHIFT (25U)
#define DDRPHY_PGCR0_PUBMODE_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_PUBMODE_SHIFT) & DDRPHY_PGCR0_PUBMODE_MASK)
#define DDRPHY_PGCR0_PUBMODE_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_PUBMODE_MASK) >> DDRPHY_PGCR0_PUBMODE_SHIFT)

/*
 * DTOSEL (R/W)
 *
 * Digital Test Output Select: Selects the PHY digital test output that is driven onto PHY digital test output (phy_dto) pin: Valid values are:
 * 00000 = DATX8 0 PLL digital test output 00001 = DATX8 1 PLL digital test output 00010 = DATX8 2 PLL digital test output 00011 = DATX8 3 PLL digital test output 00100 = DATX8 4 PLL digital test output 00101 = DATX8 5 PLL digital test output 00110 = DATX8 6 PLL digital test output 00111 = DATX8 7 PLL digital test output 01000 = DATX8 8 PLL digital test output 01001 = AC PLL digital test output 01010 – 01111 = Reserved
 * 10000 = DATX8 0 delay line digital test output 10001 = DATX8 1 delay line digital test output 10010 = DATX8 2 delay line digital test output 10011 = DATX8 3 delay line digital test output 10100 = DATX8 4 delay line digital test output 10101 = DATX8 5 delay line digital test output 10110 = DATX8 6 delay line digital test output 10111 = DATX8 7 delay line digital test output 11000 = DATX8 8 delay line digital test output 11001 = AC delay line digital test output 11010 – 11111 = Reserved
 */
#define DDRPHY_PGCR0_DTOSEL_MASK (0x7C000UL)
#define DDRPHY_PGCR0_DTOSEL_SHIFT (14U)
#define DDRPHY_PGCR0_DTOSEL_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_DTOSEL_SHIFT) & DDRPHY_PGCR0_DTOSEL_MASK)
#define DDRPHY_PGCR0_DTOSEL_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_DTOSEL_MASK) >> DDRPHY_PGCR0_DTOSEL_SHIFT)

/*
 * OSCWDL (R/W)
 *
 * Oscillator Mode Write-Leveling Delay Line Select: Selects which of the two write leveling LCDLs is active. The delay select value of the inactive LCDL is set to zero while the delay select value of the active LCDL can be varied by the input write leveling delay select pin. Valid values are:
 * 00 = No WL LCDL is active 01 = DDR WL LCDL is active 10 = SDR WL LCDL is active 11 = Both LCDLs are active
 */
#define DDRPHY_PGCR0_OSCWDL_MASK (0x3000U)
#define DDRPHY_PGCR0_OSCWDL_SHIFT (12U)
#define DDRPHY_PGCR0_OSCWDL_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_OSCWDL_SHIFT) & DDRPHY_PGCR0_OSCWDL_MASK)
#define DDRPHY_PGCR0_OSCWDL_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_OSCWDL_MASK) >> DDRPHY_PGCR0_OSCWDL_SHIFT)

/*
 * OSCDIV (R/W)
 *
 * Oscillator Mode Division: Specifies the factor by which the delay line oscillator mode output is divided down before it is output on the delay line digital test output pin dl_dto. Valid values are:
 * 000 = Divide by 1
 * 001 = Divide by 256
 * 010 = Divide by 512
 * 011 = Divide by 1024
 * 100 = Divide by 2048
 * 101 = Divide by 4096
 * 110 = Divide by 8192
 * 111 = Divide by 65536
 */
#define DDRPHY_PGCR0_OSCDIV_MASK (0xE00U)
#define DDRPHY_PGCR0_OSCDIV_SHIFT (9U)
#define DDRPHY_PGCR0_OSCDIV_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_OSCDIV_SHIFT) & DDRPHY_PGCR0_OSCDIV_MASK)
#define DDRPHY_PGCR0_OSCDIV_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_OSCDIV_MASK) >> DDRPHY_PGCR0_OSCDIV_SHIFT)

/*
 * OSCEN (R/W)
 *
 * Oscillator Enable: Enables, if set, the delay line oscillation.
 */
#define DDRPHY_PGCR0_OSCEN_MASK (0x100U)
#define DDRPHY_PGCR0_OSCEN_SHIFT (8U)
#define DDRPHY_PGCR0_OSCEN_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_OSCEN_SHIFT) & DDRPHY_PGCR0_OSCEN_MASK)
#define DDRPHY_PGCR0_OSCEN_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_OSCEN_MASK) >> DDRPHY_PGCR0_OSCEN_SHIFT)

/*
 * DLTST (R/W)
 *
 * Delay Line Test Start: A write of '1' to this bit will trigger delay line oscillator mode period measurement. This bit is not self clearing and needs to be reset to '0' before the measurement can be re-triggered.
 */
#define DDRPHY_PGCR0_DLTST_MASK (0x80U)
#define DDRPHY_PGCR0_DLTST_SHIFT (7U)
#define DDRPHY_PGCR0_DLTST_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_DLTST_SHIFT) & DDRPHY_PGCR0_DLTST_MASK)
#define DDRPHY_PGCR0_DLTST_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_DLTST_MASK) >> DDRPHY_PGCR0_DLTST_SHIFT)

/*
 * DLTMODE (R/W)
 *
 * Delay Line Test Mode: Selects, if set, the delay line oscillator test mode. Setting this bit also clears all delay line register values. For DL oscillator testing, first set this bit, then apply desired non-zero LCDL and BDL register programmings.
 */
#define DDRPHY_PGCR0_DLTMODE_MASK (0x40U)
#define DDRPHY_PGCR0_DLTMODE_SHIFT (6U)
#define DDRPHY_PGCR0_DLTMODE_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_DLTMODE_SHIFT) & DDRPHY_PGCR0_DLTMODE_MASK)
#define DDRPHY_PGCR0_DLTMODE_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_DLTMODE_MASK) >> DDRPHY_PGCR0_DLTMODE_SHIFT)

/*
 * RDBVT (R/W)
 *
 * Read Data BDL VT Compensation: Enables, if set, the VT drift compensation of the read data bit delay lines.
 */
#define DDRPHY_PGCR0_RDBVT_MASK (0x20U)
#define DDRPHY_PGCR0_RDBVT_SHIFT (5U)
#define DDRPHY_PGCR0_RDBVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_RDBVT_SHIFT) & DDRPHY_PGCR0_RDBVT_MASK)
#define DDRPHY_PGCR0_RDBVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_RDBVT_MASK) >> DDRPHY_PGCR0_RDBVT_SHIFT)

/*
 * WDBVT (R/W)
 *
 * Write Data BDL VT Compensation: Enables, if set, the VT drift compensation of the write data bit delay lines.
 */
#define DDRPHY_PGCR0_WDBVT_MASK (0x10U)
#define DDRPHY_PGCR0_WDBVT_SHIFT (4U)
#define DDRPHY_PGCR0_WDBVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_WDBVT_SHIFT) & DDRPHY_PGCR0_WDBVT_MASK)
#define DDRPHY_PGCR0_WDBVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_WDBVT_MASK) >> DDRPHY_PGCR0_WDBVT_SHIFT)

/*
 * RGLVT (R/W)
 *
 * Read DQS Gating LCDL Delay VT Compensation: Enables, if set, the VT drift compensation of the read DQS gating LCDL.
 */
#define DDRPHY_PGCR0_RGLVT_MASK (0x8U)
#define DDRPHY_PGCR0_RGLVT_SHIFT (3U)
#define DDRPHY_PGCR0_RGLVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_RGLVT_SHIFT) & DDRPHY_PGCR0_RGLVT_MASK)
#define DDRPHY_PGCR0_RGLVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_RGLVT_MASK) >> DDRPHY_PGCR0_RGLVT_SHIFT)

/*
 * RDLVT (R/W)
 *
 * Read DQS LCDL Delay VT Compensation: Enables, if set, the VT drift compensation of the read DQS LCDL.
 */
#define DDRPHY_PGCR0_RDLVT_MASK (0x4U)
#define DDRPHY_PGCR0_RDLVT_SHIFT (2U)
#define DDRPHY_PGCR0_RDLVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_RDLVT_SHIFT) & DDRPHY_PGCR0_RDLVT_MASK)
#define DDRPHY_PGCR0_RDLVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_RDLVT_MASK) >> DDRPHY_PGCR0_RDLVT_SHIFT)

/*
 * WDLVT (R/W)
 *
 * Write DQ LCDL Delay VT Compensation: Enables, if set, the VT drift compensation of the write DQ LCDL.
 */
#define DDRPHY_PGCR0_WDLVT_MASK (0x2U)
#define DDRPHY_PGCR0_WDLVT_SHIFT (1U)
#define DDRPHY_PGCR0_WDLVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_WDLVT_SHIFT) & DDRPHY_PGCR0_WDLVT_MASK)
#define DDRPHY_PGCR0_WDLVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_WDLVT_MASK) >> DDRPHY_PGCR0_WDLVT_SHIFT)

/*
 * WLLVT (R/W)
 *
 * Write Leveling LCDL Delay VT Compensation: Enables, if set, the VT drift compensation of the write leveling LCDL.
 */
#define DDRPHY_PGCR0_WLLVT_MASK (0x1U)
#define DDRPHY_PGCR0_WLLVT_SHIFT (0U)
#define DDRPHY_PGCR0_WLLVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR0_WLLVT_SHIFT) & DDRPHY_PGCR0_WLLVT_MASK)
#define DDRPHY_PGCR0_WLLVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR0_WLLVT_MASK) >> DDRPHY_PGCR0_WLLVT_SHIFT)

/* Bitfield definition for register: PGCR1 */
/*
 * LBMODE (R/W)
 *
 * Loopback Mode: Indicates, if set, that the PHY/PUB is in loopback mode.
 */
#define DDRPHY_PGCR1_LBMODE_MASK (0x80000000UL)
#define DDRPHY_PGCR1_LBMODE_SHIFT (31U)
#define DDRPHY_PGCR1_LBMODE_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_LBMODE_SHIFT) & DDRPHY_PGCR1_LBMODE_MASK)
#define DDRPHY_PGCR1_LBMODE_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_LBMODE_MASK) >> DDRPHY_PGCR1_LBMODE_SHIFT)

/*
 * LBGDQS (R/W)
 *
 * Loopback DQS Gating: Selects the DQS gating mode that should be used when the PHY is in loopback mode, including BIST loopback mode. Valid values are:
 * 00 = DQS gate is always on
 * 01 = DQS gate training will be triggered on the PUB 10 = DQS gate is set manually using software
 * 11 = Reserved
 */
#define DDRPHY_PGCR1_LBGDQS_MASK (0x60000000UL)
#define DDRPHY_PGCR1_LBGDQS_SHIFT (29U)
#define DDRPHY_PGCR1_LBGDQS_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_LBGDQS_SHIFT) & DDRPHY_PGCR1_LBGDQS_MASK)
#define DDRPHY_PGCR1_LBGDQS_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_LBGDQS_MASK) >> DDRPHY_PGCR1_LBGDQS_SHIFT)

/*
 * LBDQSS (R/W)
 *
 * Loopback DQS Shift: Selects how the read DQS is shifted during loopback to ensure that the read DQS is centered into the read data eye. Valid values are:
 * 1b0 = PUB sets the read DQS LCDL to 0 (internally). DQS is already shifted 90 degrees by write path
 * 1b1 = The read DQS shift is set manually through software
 */
#define DDRPHY_PGCR1_LBDQSS_MASK (0x10000000UL)
#define DDRPHY_PGCR1_LBDQSS_SHIFT (28U)
#define DDRPHY_PGCR1_LBDQSS_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_LBDQSS_SHIFT) & DDRPHY_PGCR1_LBDQSS_MASK)
#define DDRPHY_PGCR1_LBDQSS_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_LBDQSS_MASK) >> DDRPHY_PGCR1_LBDQSS_SHIFT)

/*
 * IOLB (R/W)
 *
 * I/O Loop-Back Select: Selects where inside the I/O the loop-back of signals happens. Valid values are:
 * 0 = Loopback is after output buffer; output enable must be asserted 1 = Loopback is before output buffer; output enable is don’t care
 */
#define DDRPHY_PGCR1_IOLB_MASK (0x8000000UL)
#define DDRPHY_PGCR1_IOLB_SHIFT (27U)
#define DDRPHY_PGCR1_IOLB_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_IOLB_SHIFT) & DDRPHY_PGCR1_IOLB_MASK)
#define DDRPHY_PGCR1_IOLB_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_IOLB_MASK) >> DDRPHY_PGCR1_IOLB_SHIFT)

/*
 * INHVT (R/W)
 *
 * VT Calculation Inhibit: Inhibits calculation of the next VT compensated delay line values. A value of 1 will inhibit the VT calculation. This bit should be set to 1 during writes to the delay line registers.
 */
#define DDRPHY_PGCR1_INHVT_MASK (0x4000000UL)
#define DDRPHY_PGCR1_INHVT_SHIFT (26U)
#define DDRPHY_PGCR1_INHVT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_INHVT_SHIFT) & DDRPHY_PGCR1_INHVT_MASK)
#define DDRPHY_PGCR1_INHVT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_INHVT_MASK) >> DDRPHY_PGCR1_INHVT_SHIFT)

/*
 * DXHRST (R/W)
 *
 * DX PHY High-Speed Reset: a Write of '0' to this bit resets the DX macro without resetting the PUB RTL logic. This bit is not self-clearing and a '1' must be written to de-assert the reset.
 */
#define DDRPHY_PGCR1_DXHRST_MASK (0x2000000UL)
#define DDRPHY_PGCR1_DXHRST_SHIFT (25U)
#define DDRPHY_PGCR1_DXHRST_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_DXHRST_SHIFT) & DDRPHY_PGCR1_DXHRST_MASK)
#define DDRPHY_PGCR1_DXHRST_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_DXHRST_MASK) >> DDRPHY_PGCR1_DXHRST_SHIFT)

/*
 * ZCKSEL (R/W)
 *
 * Impedance Clock Divider Select: Selects the divide ratio for the clock used by the impedance control logic relative to the clock used by the memory controller and SDRAM.
 * Valid values are:
 * 00 = Divide by 2
 * 01 = Divide by 8
 * 10 = Divide by 32
 * 11 = Divide by 64
 * For more information, refer to “Impedance Calibration” on page 174.
 */
#define DDRPHY_PGCR1_ZCKSEL_MASK (0x1800000UL)
#define DDRPHY_PGCR1_ZCKSEL_SHIFT (23U)
#define DDRPHY_PGCR1_ZCKSEL_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_ZCKSEL_SHIFT) & DDRPHY_PGCR1_ZCKSEL_MASK)
#define DDRPHY_PGCR1_ZCKSEL_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_ZCKSEL_MASK) >> DDRPHY_PGCR1_ZCKSEL_SHIFT)

/*
 * DLDLMT (R/W)
 *
 * Delay Line VT Drift Limit: Specifies the minimum change in the delay line VT drift in one direction which should result in the assertion of the delay line VT drift status signal (vt_drift). The limit is specified in terms of delay select values. A value of 0 disables the assertion of delay line VT drift status signal.
 */
#define DDRPHY_PGCR1_DLDLMT_MASK (0x7F8000UL)
#define DDRPHY_PGCR1_DLDLMT_SHIFT (15U)
#define DDRPHY_PGCR1_DLDLMT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_DLDLMT_SHIFT) & DDRPHY_PGCR1_DLDLMT_MASK)
#define DDRPHY_PGCR1_DLDLMT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_DLDLMT_MASK) >> DDRPHY_PGCR1_DLDLMT_SHIFT)

/*
 * FDEPTH (R/W)
 *
 * Filter Depth: Specifies the number of measurements over which all AC and DATX8 initial period measurements, that happen after reset or when calibration is manually triggered, are averaged. Valid values are:
 * 00 = 2
 * 01 = 4
 * 10 = 8
 * 11 = 16
 */
#define DDRPHY_PGCR1_FDEPTH_MASK (0x6000U)
#define DDRPHY_PGCR1_FDEPTH_SHIFT (13U)
#define DDRPHY_PGCR1_FDEPTH_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_FDEPTH_SHIFT) & DDRPHY_PGCR1_FDEPTH_MASK)
#define DDRPHY_PGCR1_FDEPTH_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_FDEPTH_MASK) >> DDRPHY_PGCR1_FDEPTH_SHIFT)

/*
 * LPFDEPTH (R/W)
 *
 * Low-Pass Filter Depth: Specifies the number of measurements over which MDL period measurements are filtered. This determines the time constant of the low pass filter. Valid values are:
 * 00 = 2
 * 01 = 4
 * 10 = 8
 * 11 = 16
 */
#define DDRPHY_PGCR1_LPFDEPTH_MASK (0x1800U)
#define DDRPHY_PGCR1_LPFDEPTH_SHIFT (11U)
#define DDRPHY_PGCR1_LPFDEPTH_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_LPFDEPTH_SHIFT) & DDRPHY_PGCR1_LPFDEPTH_MASK)
#define DDRPHY_PGCR1_LPFDEPTH_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_LPFDEPTH_MASK) >> DDRPHY_PGCR1_LPFDEPTH_SHIFT)

/*
 * LPFEN (R/W)
 *
 * Low-Pass Filter Enable: Enables, if set, the low pass filtering of MDL period measurements.
 */
#define DDRPHY_PGCR1_LPFEN_MASK (0x400U)
#define DDRPHY_PGCR1_LPFEN_SHIFT (10U)
#define DDRPHY_PGCR1_LPFEN_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_LPFEN_SHIFT) & DDRPHY_PGCR1_LPFEN_MASK)
#define DDRPHY_PGCR1_LPFEN_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_LPFEN_MASK) >> DDRPHY_PGCR1_LPFEN_SHIFT)

/*
 * MDLEN (R/W)
 *
 * Master Delay Line Enable: Enables, if set, the AC master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or on when calibration is manually triggered. These additional measurements are accumulated and filtered as long as this bit remains high.
 */
#define DDRPHY_PGCR1_MDLEN_MASK (0x200U)
#define DDRPHY_PGCR1_MDLEN_SHIFT (9U)
#define DDRPHY_PGCR1_MDLEN_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_MDLEN_SHIFT) & DDRPHY_PGCR1_MDLEN_MASK)
#define DDRPHY_PGCR1_MDLEN_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_MDLEN_MASK) >> DDRPHY_PGCR1_MDLEN_SHIFT)

/*
 * IODDRM (R/W)
 *
 * I/O DDR Mode (D3F I/O Only): Selects the DDR mode for the I/Os. These bits connect to bits [2:1] of the IOM pin of the SSTL I/O. For more information, refer to the SSTL I/O chapter in the DWC DDR PHY Databook.
 */
#define DDRPHY_PGCR1_IODDRM_MASK (0x180U)
#define DDRPHY_PGCR1_IODDRM_SHIFT (7U)
#define DDRPHY_PGCR1_IODDRM_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_IODDRM_SHIFT) & DDRPHY_PGCR1_IODDRM_MASK)
#define DDRPHY_PGCR1_IODDRM_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_IODDRM_MASK) >> DDRPHY_PGCR1_IODDRM_SHIFT)

/*
 * WLSELT (R/W)
 *
 * Write Leveling Select Type: Selects the encoding type for the write leveling select signal depending on the desired setup/hold margins for the internal pipelines. Refer to the DDR PHY Databook for details of how the select type is used. Valid values are:
 * 0 = Type 1: Setup margin of 90 degrees and hold margin of 90 degrees 1 = Type 2: Setup margin of 135 degrees and hold margin of 45 degrees
 */
#define DDRPHY_PGCR1_WLSELT_MASK (0x40U)
#define DDRPHY_PGCR1_WLSELT_SHIFT (6U)
#define DDRPHY_PGCR1_WLSELT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_WLSELT_SHIFT) & DDRPHY_PGCR1_WLSELT_MASK)
#define DDRPHY_PGCR1_WLSELT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_WLSELT_MASK) >> DDRPHY_PGCR1_WLSELT_SHIFT)

/*
 * ACHRST (R/W)
 *
 * AC PHY High-Speed Reset: a Write of '0' to this bit resets the AC macro without resetting the PUB RTL logic. This bit is not self-clearing and a '1' must be written to de-assert the reset.
 */
#define DDRPHY_PGCR1_ACHRST_MASK (0x20U)
#define DDRPHY_PGCR1_ACHRST_SHIFT (5U)
#define DDRPHY_PGCR1_ACHRST_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_ACHRST_SHIFT) & DDRPHY_PGCR1_ACHRST_MASK)
#define DDRPHY_PGCR1_ACHRST_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_ACHRST_MASK) >> DDRPHY_PGCR1_ACHRST_SHIFT)

/*
 * WSLOPT (R/W)
 *
 * Write System Latency Optimization: controls the insertion of a pipeline stage on the AC signals from the DFI interface to the PHY to cater for a negative write system latency (WSL) value (only -1 possible).
 * 0x0 = A pipeline stage is inserted only if WL2 training results in a WSL of -1 for any rank
 * 0x1 = Inserts a pipeline stage
 */
#define DDRPHY_PGCR1_WSLOPT_MASK (0x10U)
#define DDRPHY_PGCR1_WSLOPT_SHIFT (4U)
#define DDRPHY_PGCR1_WSLOPT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_WSLOPT_SHIFT) & DDRPHY_PGCR1_WSLOPT_MASK)
#define DDRPHY_PGCR1_WSLOPT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_WSLOPT_MASK) >> DDRPHY_PGCR1_WSLOPT_SHIFT)

/*
 * WLSTEP (R/W)
 *
 * Write Leveling Step: Specifies the number of delay step-size increments during each step of write leveling. Valid values are:
 * 0 = computed to be 1/2 of the associated lane's DXnGSR0.WLPRD value 1 = 1 step size
 */
#define DDRPHY_PGCR1_WLSTEP_MASK (0x4U)
#define DDRPHY_PGCR1_WLSTEP_SHIFT (2U)
#define DDRPHY_PGCR1_WLSTEP_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_WLSTEP_SHIFT) & DDRPHY_PGCR1_WLSTEP_MASK)
#define DDRPHY_PGCR1_WLSTEP_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_WLSTEP_MASK) >> DDRPHY_PGCR1_WLSTEP_SHIFT)

/*
 * WLMODE (R/W)
 *
 * Write Leveling (Software) Mode: Indicates, if set, that the PUB is in software write leveling mode in which software executes single steps of DQS pulsing by writing '1' to PIR.WL. The write leveling DQ status from the DRAM is captured in DXnGSR0.WLDQ.
 */
#define DDRPHY_PGCR1_WLMODE_MASK (0x2U)
#define DDRPHY_PGCR1_WLMODE_SHIFT (1U)
#define DDRPHY_PGCR1_WLMODE_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_WLMODE_SHIFT) & DDRPHY_PGCR1_WLMODE_MASK)
#define DDRPHY_PGCR1_WLMODE_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_WLMODE_MASK) >> DDRPHY_PGCR1_WLMODE_SHIFT)

/*
 * PDDISDX (R/W)
 *
 * Power Down Disabled Byte: Indicates, if set, that the PLL and I/Os of a disabled byte should be powered down.
 */
#define DDRPHY_PGCR1_PDDISDX_MASK (0x1U)
#define DDRPHY_PGCR1_PDDISDX_SHIFT (0U)
#define DDRPHY_PGCR1_PDDISDX_SET(x) (((uint32_t)(x) << DDRPHY_PGCR1_PDDISDX_SHIFT) & DDRPHY_PGCR1_PDDISDX_MASK)
#define DDRPHY_PGCR1_PDDISDX_GET(x) (((uint32_t)(x) & DDRPHY_PGCR1_PDDISDX_MASK) >> DDRPHY_PGCR1_PDDISDX_SHIFT)

/* Bitfield definition for register: PGSR0 */
/*
 * APLOCK (R)
 *
 * AC PLL Lock: Indicates, if set, that AC PLL has locked. This is a direct status of the AC PLL lock pin.
 */
#define DDRPHY_PGSR0_APLOCK_MASK (0x80000000UL)
#define DDRPHY_PGSR0_APLOCK_SHIFT (31U)
#define DDRPHY_PGSR0_APLOCK_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_APLOCK_MASK) >> DDRPHY_PGSR0_APLOCK_SHIFT)

/*
 * PLDONE_CHN (R)
 *
 * PLL Lock Done per Channel: Indicates PLL locking has completed for each underlying channel. Bit 28 represents channel 0 while bit 29 represents channel 1.
 */
#define DDRPHY_PGSR0_PLDONE_CHN_MASK (0x30000000UL)
#define DDRPHY_PGSR0_PLDONE_CHN_SHIFT (28U)
#define DDRPHY_PGSR0_PLDONE_CHN_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_PLDONE_CHN_MASK) >> DDRPHY_PGSR0_PLDONE_CHN_SHIFT)

/*
 * WEERR (R)
 *
 * Write Eye Training Error: Indicates, if set, that there is an error in write eye training.
 */
#define DDRPHY_PGSR0_WEERR_MASK (0x8000000UL)
#define DDRPHY_PGSR0_WEERR_SHIFT (27U)
#define DDRPHY_PGSR0_WEERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WEERR_MASK) >> DDRPHY_PGSR0_WEERR_SHIFT)

/*
 * REERR (R)
 *
 * Read Data Eye Training Error: Indicates, if set, that there is an error in read eye training.
 */
#define DDRPHY_PGSR0_REERR_MASK (0x4000000UL)
#define DDRPHY_PGSR0_REERR_SHIFT (26U)
#define DDRPHY_PGSR0_REERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_REERR_MASK) >> DDRPHY_PGSR0_REERR_SHIFT)

/*
 * WDERR (R)
 *
 * Write Data Bit Deskew Error: Indicates, if set, that there is an error in write bit deskew.
 */
#define DDRPHY_PGSR0_WDERR_MASK (0x2000000UL)
#define DDRPHY_PGSR0_WDERR_SHIFT (25U)
#define DDRPHY_PGSR0_WDERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WDERR_MASK) >> DDRPHY_PGSR0_WDERR_SHIFT)

/*
 * RDERR (R)
 *
 * Read Data Bit Deskew Error: Indicates, if set, that there is an error in read bit deskew.
 */
#define DDRPHY_PGSR0_RDERR_MASK (0x1000000UL)
#define DDRPHY_PGSR0_RDERR_SHIFT (24U)
#define DDRPHY_PGSR0_RDERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_RDERR_MASK) >> DDRPHY_PGSR0_RDERR_SHIFT)

/*
 * WLAERR (R)
 *
 * Write Data Leveling Adjustment Error: Indicates, if set, that there is an error in write leveling adjustment.
 */
#define DDRPHY_PGSR0_WLAERR_MASK (0x800000UL)
#define DDRPHY_PGSR0_WLAERR_SHIFT (23U)
#define DDRPHY_PGSR0_WLAERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WLAERR_MASK) >> DDRPHY_PGSR0_WLAERR_SHIFT)

/*
 * QSGERR (R)
 *
 * Read DQS Gate Training Error: Indicates, if set, that there is an error in DQS gate training.
 */
#define DDRPHY_PGSR0_QSGERR_MASK (0x400000UL)
#define DDRPHY_PGSR0_QSGERR_SHIFT (22U)
#define DDRPHY_PGSR0_QSGERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_QSGERR_MASK) >> DDRPHY_PGSR0_QSGERR_SHIFT)

/*
 * WLERR (R)
 *
 * Write Leveling Error: Indicates, if set, that there is an error in write leveling.
 */
#define DDRPHY_PGSR0_WLERR_MASK (0x200000UL)
#define DDRPHY_PGSR0_WLERR_SHIFT (21U)
#define DDRPHY_PGSR0_WLERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WLERR_MASK) >> DDRPHY_PGSR0_WLERR_SHIFT)

/*
 * ZCERR (R)
 *
 * Impedance Calibration Error: Indicates, if set, that there is an error in impedance calibration.
 */
#define DDRPHY_PGSR0_ZCERR_MASK (0x100000UL)
#define DDRPHY_PGSR0_ZCERR_SHIFT (20U)
#define DDRPHY_PGSR0_ZCERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_ZCERR_MASK) >> DDRPHY_PGSR0_ZCERR_SHIFT)

/*
 * WEDONE (R)
 *
 * Write Data Eye Training Done: Indicates, if set, that write eye training has completed.
 */
#define DDRPHY_PGSR0_WEDONE_MASK (0x800U)
#define DDRPHY_PGSR0_WEDONE_SHIFT (11U)
#define DDRPHY_PGSR0_WEDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WEDONE_MASK) >> DDRPHY_PGSR0_WEDONE_SHIFT)

/*
 * REDONE (R)
 *
 * Read Data Eye Training Done: Indicates, if set, that read eye training has completed.
 */
#define DDRPHY_PGSR0_REDONE_MASK (0x400U)
#define DDRPHY_PGSR0_REDONE_SHIFT (10U)
#define DDRPHY_PGSR0_REDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_REDONE_MASK) >> DDRPHY_PGSR0_REDONE_SHIFT)

/*
 * WDDONE (R)
 *
 * Write Data Bit Deskew Done: Indicates, if set, that write bit deskew has completed.
 */
#define DDRPHY_PGSR0_WDDONE_MASK (0x200U)
#define DDRPHY_PGSR0_WDDONE_SHIFT (9U)
#define DDRPHY_PGSR0_WDDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WDDONE_MASK) >> DDRPHY_PGSR0_WDDONE_SHIFT)

/*
 * RDDONE (R)
 *
 * Read Data Bit Deskew Done: Indicates, if set, that read bit deskew has completed.
 */
#define DDRPHY_PGSR0_RDDONE_MASK (0x100U)
#define DDRPHY_PGSR0_RDDONE_SHIFT (8U)
#define DDRPHY_PGSR0_RDDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_RDDONE_MASK) >> DDRPHY_PGSR0_RDDONE_SHIFT)

/*
 * WLADONE (R)
 *
 * Write Leveling Adjustment Done: Indicates, if set, that write leveling adjustment has completed.
 */
#define DDRPHY_PGSR0_WLADONE_MASK (0x80U)
#define DDRPHY_PGSR0_WLADONE_SHIFT (7U)
#define DDRPHY_PGSR0_WLADONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WLADONE_MASK) >> DDRPHY_PGSR0_WLADONE_SHIFT)

/*
 * QSGDONE (R)
 *
 * Read DQS Gate Training Done: Indicates, if set, that DQS gate training has completed.
 */
#define DDRPHY_PGSR0_QSGDONE_MASK (0x40U)
#define DDRPHY_PGSR0_QSGDONE_SHIFT (6U)
#define DDRPHY_PGSR0_QSGDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_QSGDONE_MASK) >> DDRPHY_PGSR0_QSGDONE_SHIFT)

/*
 * WLDONE (R)
 *
 * Write Leveling Done: Indicates, if set, that write leveling has completed.
 */
#define DDRPHY_PGSR0_WLDONE_MASK (0x20U)
#define DDRPHY_PGSR0_WLDONE_SHIFT (5U)
#define DDRPHY_PGSR0_WLDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_WLDONE_MASK) >> DDRPHY_PGSR0_WLDONE_SHIFT)

/*
 * DIDONE (R)
 *
 * DRAM Initialization Done: Indicates, if set, that DRAM initialization has completed.
 */
#define DDRPHY_PGSR0_DIDONE_MASK (0x10U)
#define DDRPHY_PGSR0_DIDONE_SHIFT (4U)
#define DDRPHY_PGSR0_DIDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_DIDONE_MASK) >> DDRPHY_PGSR0_DIDONE_SHIFT)

/*
 * ZCDONE (R)
 *
 * Impedance Calibration Done: Indicates, if set, that impedance calibration has completed.
 */
#define DDRPHY_PGSR0_ZCDONE_MASK (0x8U)
#define DDRPHY_PGSR0_ZCDONE_SHIFT (3U)
#define DDRPHY_PGSR0_ZCDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_ZCDONE_MASK) >> DDRPHY_PGSR0_ZCDONE_SHIFT)

/*
 * DCDONE (R)
 *
 * Digital Delay Line (DDL) Calibration Done: Indicates, if set, that DDL calibration has completed.
 */
#define DDRPHY_PGSR0_DCDONE_MASK (0x4U)
#define DDRPHY_PGSR0_DCDONE_SHIFT (2U)
#define DDRPHY_PGSR0_DCDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_DCDONE_MASK) >> DDRPHY_PGSR0_DCDONE_SHIFT)

/*
 * PLDONE (R)
 *
 * PLL Lock Done: Indicates, if set, that PLL locking has completed.
 */
#define DDRPHY_PGSR0_PLDONE_MASK (0x2U)
#define DDRPHY_PGSR0_PLDONE_SHIFT (1U)
#define DDRPHY_PGSR0_PLDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_PLDONE_MASK) >> DDRPHY_PGSR0_PLDONE_SHIFT)

/*
 * IDONE (R)
 *
 * Initialization Done: Indicates, if set, that the DDR system initialization has completed. This bit is set after all the selected initialization routines in PIR register have completed.
 */
#define DDRPHY_PGSR0_IDONE_MASK (0x1U)
#define DDRPHY_PGSR0_IDONE_SHIFT (0U)
#define DDRPHY_PGSR0_IDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR0_IDONE_MASK) >> DDRPHY_PGSR0_IDONE_SHIFT)

/* Bitfield definition for register: PGSR1 */
/*
 * PARERR (R)
 *
 * RDIMM Parity Error: Indicates, if set, that there was a parity error (i.e. err_out_n was sampled low) during one of the transactions to the RDIMM buffer chip. This bit remains asserted until cleared by the PIR.CLRSR.
 */
#define DDRPHY_PGSR1_PARERR_MASK (0x80000000UL)
#define DDRPHY_PGSR1_PARERR_SHIFT (31U)
#define DDRPHY_PGSR1_PARERR_GET(x) (((uint32_t)(x) & DDRPHY_PGSR1_PARERR_MASK) >> DDRPHY_PGSR1_PARERR_SHIFT)

/*
 * VTSTOP (R)
 *
 * VT Stop: Indicates, if set, that the VT calculation logic has stopped computing the next values for the VT compensated delay line values. After assertion of the PGCR.INHVT, the VTSTOP bit should be read to ensure all VT compensation logic has stopped computations before writing to the delay line registers.
 */
#define DDRPHY_PGSR1_VTSTOP_MASK (0x40000000UL)
#define DDRPHY_PGSR1_VTSTOP_SHIFT (30U)
#define DDRPHY_PGSR1_VTSTOP_GET(x) (((uint32_t)(x) & DDRPHY_PGSR1_VTSTOP_MASK) >> DDRPHY_PGSR1_VTSTOP_SHIFT)

/*
 * DLTCODE (R)
 *
 * Delay Line Test Code: Returns the code measured by the PHY control block that corresponds to the period of the AC delay line digital test output.
 */
#define DDRPHY_PGSR1_DLTCODE_MASK (0x1FFFFFEUL)
#define DDRPHY_PGSR1_DLTCODE_SHIFT (1U)
#define DDRPHY_PGSR1_DLTCODE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR1_DLTCODE_MASK) >> DDRPHY_PGSR1_DLTCODE_SHIFT)

/*
 * DLTDONE (R)
 *
 * Delay Line Test Done: Indicates, if set, that the PHY control block has finished doing period measurement of the AC delay line digital test output.
 */
#define DDRPHY_PGSR1_DLTDONE_MASK (0x1U)
#define DDRPHY_PGSR1_DLTDONE_SHIFT (0U)
#define DDRPHY_PGSR1_DLTDONE_GET(x) (((uint32_t)(x) & DDRPHY_PGSR1_DLTDONE_MASK) >> DDRPHY_PGSR1_DLTDONE_SHIFT)

/* Bitfield definition for register: PLLCR */
/*
 * BYP (R/W)
 *
 * PLL Bypass: Bypasses the PLL, if set, to 1.
 */
#define DDRPHY_PLLCR_BYP_MASK (0x80000000UL)
#define DDRPHY_PLLCR_BYP_SHIFT (31U)
#define DDRPHY_PLLCR_BYP_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_BYP_SHIFT) & DDRPHY_PLLCR_BYP_MASK)
#define DDRPHY_PLLCR_BYP_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_BYP_MASK) >> DDRPHY_PLLCR_BYP_SHIFT)

/*
 * PLLRST (R/W)
 *
 * PLL Rest: Resets the PLLs by driving the PLL reset pin. This bit is not self-clearing and a ‘0’ must be written to de-assert the reset.
 */
#define DDRPHY_PLLCR_PLLRST_MASK (0x40000000UL)
#define DDRPHY_PLLCR_PLLRST_SHIFT (30U)
#define DDRPHY_PLLCR_PLLRST_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_PLLRST_SHIFT) & DDRPHY_PLLCR_PLLRST_MASK)
#define DDRPHY_PLLCR_PLLRST_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_PLLRST_MASK) >> DDRPHY_PLLCR_PLLRST_SHIFT)

/*
 * PLLPD (R/W)
 *
 * PLL Power Down: Puts the PLLs in power down mode by driving the PLL power down pin. This bit is not self-clearing and a ‘0’ must be written to de-assert the power-down.
 */
#define DDRPHY_PLLCR_PLLPD_MASK (0x20000000UL)
#define DDRPHY_PLLCR_PLLPD_SHIFT (29U)
#define DDRPHY_PLLCR_PLLPD_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_PLLPD_SHIFT) & DDRPHY_PLLCR_PLLPD_MASK)
#define DDRPHY_PLLCR_PLLPD_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_PLLPD_MASK) >> DDRPHY_PLLCR_PLLPD_SHIFT)

/*
 * FRQSEL (R/W)
 *
 * PLL Frequency Select: Selects the operating range of the PLL. Valid values for PHYs that go up to 2133 Mbps are:
 * 00 = PLL reference clock (ctl_clk/REF_CLK) ranges from 335MHz to 533MHz 01 = PLL reference clock (ctl_clk/REF_CLK) ranges from 225MHz to 385MHz 10 = Reserved
 * 11 = PLL reference clock (ctl_clk/REF_CLK) ranges from 166MHz to 275MHz
 * Valid values for PHYs that don’t go up to 2133 Mbps are:
 * 00 = PLL reference clock (ctl_clk/REF_CLK) ranges from 250MHz to 400MHz 01 = PLL reference clock (ctl_clk/REF_CLK) ranges from 166MHz to 300MHz 10 = Reserved
 * 11 = Reserved
 */
#define DDRPHY_PLLCR_FRQSEL_MASK (0xC0000UL)
#define DDRPHY_PLLCR_FRQSEL_SHIFT (18U)
#define DDRPHY_PLLCR_FRQSEL_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_FRQSEL_SHIFT) & DDRPHY_PLLCR_FRQSEL_MASK)
#define DDRPHY_PLLCR_FRQSEL_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_FRQSEL_MASK) >> DDRPHY_PLLCR_FRQSEL_SHIFT)

/*
 * QPMODE (R/W)
 *
 * PLL Quadrature Phase Mode: Enables, if set, the quadrature phase clock outputs. This mode is not used in this version of the PHY.
 */
#define DDRPHY_PLLCR_QPMODE_MASK (0x20000UL)
#define DDRPHY_PLLCR_QPMODE_SHIFT (17U)
#define DDRPHY_PLLCR_QPMODE_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_QPMODE_SHIFT) & DDRPHY_PLLCR_QPMODE_MASK)
#define DDRPHY_PLLCR_QPMODE_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_QPMODE_MASK) >> DDRPHY_PLLCR_QPMODE_SHIFT)

/*
 * CPPC (R/W)
 *
 * Charge Pump Proportional Current Control
 */
#define DDRPHY_PLLCR_CPPC_MASK (0x1E000UL)
#define DDRPHY_PLLCR_CPPC_SHIFT (13U)
#define DDRPHY_PLLCR_CPPC_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_CPPC_SHIFT) & DDRPHY_PLLCR_CPPC_MASK)
#define DDRPHY_PLLCR_CPPC_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_CPPC_MASK) >> DDRPHY_PLLCR_CPPC_SHIFT)

/*
 * CPIC (R/W)
 *
 * Charge Pump Integrating Current Control
 */
#define DDRPHY_PLLCR_CPIC_MASK (0x1800U)
#define DDRPHY_PLLCR_CPIC_SHIFT (11U)
#define DDRPHY_PLLCR_CPIC_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_CPIC_SHIFT) & DDRPHY_PLLCR_CPIC_MASK)
#define DDRPHY_PLLCR_CPIC_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_CPIC_MASK) >> DDRPHY_PLLCR_CPIC_SHIFT)

/*
 * GSHIFT (R/W)
 *
 * Gear Shift: Enables, if set, rapid locking mode.
 */
#define DDRPHY_PLLCR_GSHIFT_MASK (0x400U)
#define DDRPHY_PLLCR_GSHIFT_SHIFT (10U)
#define DDRPHY_PLLCR_GSHIFT_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_GSHIFT_SHIFT) & DDRPHY_PLLCR_GSHIFT_MASK)
#define DDRPHY_PLLCR_GSHIFT_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_GSHIFT_MASK) >> DDRPHY_PLLCR_GSHIFT_SHIFT)

/*
 * ATOEN (R/W)
 *
 * Analog Test Enable (ATOEN): Selects the analog test signal that is driven on the analog test output pin. Otherwise the analog test output is tri-stated. This allows analog test output pins from multiple PLLs to be connected together. Valid values are:
 * 0000 = All PLL analog test signals are tri-stated 0001 = AC PLL analog test signal is driven out
 * 0010 = DATX8 0 PLL analog test signal is driven out 0011 = DATX8 1 PLL analog test signal is driven out 0100 = DATX8 2 PLL analog test signal is driven out 0101 = DATX8 3 PLL analog test signal is driven out 0110 = DATX8 4 PLL analog test signal is driven out 0111 = DATX8 5 PLL analog test signal is driven out 1000 = DATX8 6 PLL analog test signal is driven out 1001 = DATX8 7 PLL analog test signal is driven out 1010 = DATX8 8 PLL analog test signal is driven out 1011 – 1111 = Reserved
 */
#define DDRPHY_PLLCR_ATOEN_MASK (0x3C0U)
#define DDRPHY_PLLCR_ATOEN_SHIFT (6U)
#define DDRPHY_PLLCR_ATOEN_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_ATOEN_SHIFT) & DDRPHY_PLLCR_ATOEN_MASK)
#define DDRPHY_PLLCR_ATOEN_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_ATOEN_MASK) >> DDRPHY_PLLCR_ATOEN_SHIFT)

/*
 * ATC (R/W)
 *
 * Analog Test Control: Selects various PLL analog test signals to be brought out via PLL analog test output pin (pll_ato). Valid values are:
 * 0000 = Reserved
 * 0001 = vdd_ckin
 * 0010 = vrfbf
 * 0011 = vdd_cko
 * 0100 = vp_cp
 * 0101 = vpfil(vp)
 * 0110 = Reserved
 * 0111 = gd
 * 1000 = vcntrl_atb
 * 1001 = vref_atb
 * 1010 = vpsf_atb
 * 1011 – 1111 = Reserved
 */
#define DDRPHY_PLLCR_ATC_MASK (0x3CU)
#define DDRPHY_PLLCR_ATC_SHIFT (2U)
#define DDRPHY_PLLCR_ATC_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_ATC_SHIFT) & DDRPHY_PLLCR_ATC_MASK)
#define DDRPHY_PLLCR_ATC_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_ATC_MASK) >> DDRPHY_PLLCR_ATC_SHIFT)

/*
 * DTC (R/W)
 *
 * Digital Test Control: Selects various PLL digital test signals and other test mode signals to be brought out via bit [1] of the PLL digital test output (pll_dto[1]). Valid values are:
 * 00 = ‘0’ (Test output is disabled) 01 = PLL x1 clock (X1)
 * 10 = PLL reference (input) clock (REF_CLK) 11 = PLL feedback clock (FB_X1)
 */
#define DDRPHY_PLLCR_DTC_MASK (0x3U)
#define DDRPHY_PLLCR_DTC_SHIFT (0U)
#define DDRPHY_PLLCR_DTC_SET(x) (((uint32_t)(x) << DDRPHY_PLLCR_DTC_SHIFT) & DDRPHY_PLLCR_DTC_MASK)
#define DDRPHY_PLLCR_DTC_GET(x) (((uint32_t)(x) & DDRPHY_PLLCR_DTC_MASK) >> DDRPHY_PLLCR_DTC_SHIFT)

/* Bitfield definition for register: PTR0 */
/*
 * TPLLPD (R/W)
 *
 * PLL Power-Down Time: Number of configuration or APB clock cycles that the PLL must remain in power-down mode, i.e. number of clock cycles from when PLL power-down pin is asserted to when PLL power-down pin is de-asserted. This must correspond to a value that is equal to or more than 1us. Default value corresponds to 1us.
 */
#define DDRPHY_PTR0_TPLLPD_MASK (0xFFE00000UL)
#define DDRPHY_PTR0_TPLLPD_SHIFT (21U)
#define DDRPHY_PTR0_TPLLPD_SET(x) (((uint32_t)(x) << DDRPHY_PTR0_TPLLPD_SHIFT) & DDRPHY_PTR0_TPLLPD_MASK)
#define DDRPHY_PTR0_TPLLPD_GET(x) (((uint32_t)(x) & DDRPHY_PTR0_TPLLPD_MASK) >> DDRPHY_PTR0_TPLLPD_SHIFT)

/*
 * TPLLGS (R/W)
 *
 * PLL Gear Shift Time: Number of configuration or APB clock cycles from when the PLL reset pin is de-asserted to when the PLL gear shift pin is de-asserted. This must correspond to a value that is equal to or more than 4us. Default value corresponds to 4us.
 */
#define DDRPHY_PTR0_TPLLGS_MASK (0x1FFFC0UL)
#define DDRPHY_PTR0_TPLLGS_SHIFT (6U)
#define DDRPHY_PTR0_TPLLGS_SET(x) (((uint32_t)(x) << DDRPHY_PTR0_TPLLGS_SHIFT) & DDRPHY_PTR0_TPLLGS_MASK)
#define DDRPHY_PTR0_TPLLGS_GET(x) (((uint32_t)(x) & DDRPHY_PTR0_TPLLGS_MASK) >> DDRPHY_PTR0_TPLLGS_SHIFT)

/*
 * TPHYRST (R/W)
 *
 * PHY Reset Time: Number of configuration or APB clock cycles that the PHY reset must remain asserted after PHY calibration is done before the reset to the PHY is de-asserted. This is used to extend the reset to the PHY so that the reset is asserted for some clock cycles after the clocks are stable. Valid values are from 1 to 63 (the value must be non-zero).
 */
#define DDRPHY_PTR0_TPHYRST_MASK (0x3FU)
#define DDRPHY_PTR0_TPHYRST_SHIFT (0U)
#define DDRPHY_PTR0_TPHYRST_SET(x) (((uint32_t)(x) << DDRPHY_PTR0_TPHYRST_SHIFT) & DDRPHY_PTR0_TPHYRST_MASK)
#define DDRPHY_PTR0_TPHYRST_GET(x) (((uint32_t)(x) & DDRPHY_PTR0_TPHYRST_MASK) >> DDRPHY_PTR0_TPHYRST_SHIFT)

/* Bitfield definition for register: PTR1 */
/*
 * TPLLLOCK (R/W)
 *
 * PLL Lock Time: Number of configuration or APB clock cycles for the PLL to stabilize and lock, i.e. number of clock cycles from when the PLL reset pin is de-asserted to when the PLL has lock and is ready for use. This must correspond to a value that is equal to or more than 100us. Default value corresponds to 100us.
 */
#define DDRPHY_PTR1_TPLLLOCK_MASK (0xFFFF0000UL)
#define DDRPHY_PTR1_TPLLLOCK_SHIFT (16U)
#define DDRPHY_PTR1_TPLLLOCK_SET(x) (((uint32_t)(x) << DDRPHY_PTR1_TPLLLOCK_SHIFT) & DDRPHY_PTR1_TPLLLOCK_MASK)
#define DDRPHY_PTR1_TPLLLOCK_GET(x) (((uint32_t)(x) & DDRPHY_PTR1_TPLLLOCK_MASK) >> DDRPHY_PTR1_TPLLLOCK_SHIFT)

/*
 * TPLLRST (R/W)
 *
 * PLL Reset Time: Number of configuration or APB clock cycles that the PLL must remain in reset mode, i.e. number of clock cycles from when PLL power-down pin is de-asserted and PLL reset pin is asserted to when PLL reset pin is de-asserted.
 * The setting must correspond to a value that is equal to, or greater than, 3us.
 */
#define DDRPHY_PTR1_TPLLRST_MASK (0x1FFFU)
#define DDRPHY_PTR1_TPLLRST_SHIFT (0U)
#define DDRPHY_PTR1_TPLLRST_SET(x) (((uint32_t)(x) << DDRPHY_PTR1_TPLLRST_SHIFT) & DDRPHY_PTR1_TPLLRST_MASK)
#define DDRPHY_PTR1_TPLLRST_GET(x) (((uint32_t)(x) & DDRPHY_PTR1_TPLLRST_MASK) >> DDRPHY_PTR1_TPLLRST_SHIFT)

/* Bitfield definition for register: PTR2 */
/*
 * TWLDLYS (R/W)
 *
 * Write Leveling Delay Settling Time: Number of controller clock cycles from when a new value of the write leveling delay is applies to the LCDL to when to DQS high is driven high. This allows the delay to settle.
 */
#define DDRPHY_PTR2_TWLDLYS_MASK (0xF8000UL)
#define DDRPHY_PTR2_TWLDLYS_SHIFT (15U)
#define DDRPHY_PTR2_TWLDLYS_SET(x) (((uint32_t)(x) << DDRPHY_PTR2_TWLDLYS_SHIFT) & DDRPHY_PTR2_TWLDLYS_MASK)
#define DDRPHY_PTR2_TWLDLYS_GET(x) (((uint32_t)(x) & DDRPHY_PTR2_TWLDLYS_MASK) >> DDRPHY_PTR2_TWLDLYS_SHIFT)

/*
 * TCALH (R/W)
 *
 * Calibration Hold Time: Number of controller clock cycles from when the clock was disabled (cal_clk_en deasserted) to when calibration is enable (cal_en asserted).
 */
#define DDRPHY_PTR2_TCALH_MASK (0x7C00U)
#define DDRPHY_PTR2_TCALH_SHIFT (10U)
#define DDRPHY_PTR2_TCALH_SET(x) (((uint32_t)(x) << DDRPHY_PTR2_TCALH_SHIFT) & DDRPHY_PTR2_TCALH_MASK)
#define DDRPHY_PTR2_TCALH_GET(x) (((uint32_t)(x) & DDRPHY_PTR2_TCALH_MASK) >> DDRPHY_PTR2_TCALH_SHIFT)

/*
 * TCALS (R/W)
 *
 * Calibration Setup Time: Number of controller clock cycles from when calibration is enabled (cal_en asserted) to when the calibration clock is asserted again (cal_clk_en asserted).
 */
#define DDRPHY_PTR2_TCALS_MASK (0x3E0U)
#define DDRPHY_PTR2_TCALS_SHIFT (5U)
#define DDRPHY_PTR2_TCALS_SET(x) (((uint32_t)(x) << DDRPHY_PTR2_TCALS_SHIFT) & DDRPHY_PTR2_TCALS_MASK)
#define DDRPHY_PTR2_TCALS_GET(x) (((uint32_t)(x) & DDRPHY_PTR2_TCALS_MASK) >> DDRPHY_PTR2_TCALS_SHIFT)

/*
 * TCALON (R/W)
 *
 * Calibration On Time: Number of clock cycles that the calibration clock is enabled (cal_clk_en asserted).
 */
#define DDRPHY_PTR2_TCALON_MASK (0x1FU)
#define DDRPHY_PTR2_TCALON_SHIFT (0U)
#define DDRPHY_PTR2_TCALON_SET(x) (((uint32_t)(x) << DDRPHY_PTR2_TCALON_SHIFT) & DDRPHY_PTR2_TCALON_MASK)
#define DDRPHY_PTR2_TCALON_GET(x) (((uint32_t)(x) & DDRPHY_PTR2_TCALON_MASK) >> DDRPHY_PTR2_TCALON_SHIFT)

/* Bitfield definition for register: PTR3 */
/*
 * TDINIT1 (R/W)
 *
 * DRAM Initialization Time 1: DRAM initialization time in DRAM clock cycles corresponding to the following:
 * DDR3 = CKE high time to first command (tRFC + 10 ns or 5 tCK, whichever is bigger) DDR2 = CKE high time to first command (400 ns)
 * Default value corresponds to DDR3 tRFC of 360ns at 1066 MHz.
 */
#define DDRPHY_PTR3_TDINIT1_MASK (0x1FF00000UL)
#define DDRPHY_PTR3_TDINIT1_SHIFT (20U)
#define DDRPHY_PTR3_TDINIT1_SET(x) (((uint32_t)(x) << DDRPHY_PTR3_TDINIT1_SHIFT) & DDRPHY_PTR3_TDINIT1_MASK)
#define DDRPHY_PTR3_TDINIT1_GET(x) (((uint32_t)(x) & DDRPHY_PTR3_TDINIT1_MASK) >> DDRPHY_PTR3_TDINIT1_SHIFT)

/*
 * TDINIT0 (R/W)
 *
 * DRAM Initialization Time 0: DRAM initialization time in DRAM clock cycles corresponding to the following:
 * DDR3 = CKE low time with power and clock stable (500 us) DDR2 = CKE low time with power and clock stable (200 us) Default value corresponds to DDR3 500 us at 1066 MHz.
 * During Verilog simulations, it is recommended that this value is changed to a much smaller value in order to avoid long simulation times. However, this may cause a memory model error, due to a violation of the CKE setup sequence. This violation is expected if this value is not programmed to the required SDRAM CKE low time, but memory models should be able to tolerate this violation without malfunction of the model.
 */
#define DDRPHY_PTR3_TDINIT0_MASK (0xFFFFFUL)
#define DDRPHY_PTR3_TDINIT0_SHIFT (0U)
#define DDRPHY_PTR3_TDINIT0_SET(x) (((uint32_t)(x) << DDRPHY_PTR3_TDINIT0_SHIFT) & DDRPHY_PTR3_TDINIT0_MASK)
#define DDRPHY_PTR3_TDINIT0_GET(x) (((uint32_t)(x) & DDRPHY_PTR3_TDINIT0_MASK) >> DDRPHY_PTR3_TDINIT0_SHIFT)

/* Bitfield definition for register: PTR4 */
/*
 * TDINIT3 (R/W)
 *
 * DRAM Initialization Time 3: DRAM initialization time in DRAM clock cycles corresponding to the following:
 * DDR3 = Time from ZQ initialization command to first command (1 us) Default value corresponds to the DDR3 640ns at 1066 MHz.
 */
#define DDRPHY_PTR4_TDINIT3_MASK (0xFFC0000UL)
#define DDRPHY_PTR4_TDINIT3_SHIFT (18U)
#define DDRPHY_PTR4_TDINIT3_SET(x) (((uint32_t)(x) << DDRPHY_PTR4_TDINIT3_SHIFT) & DDRPHY_PTR4_TDINIT3_MASK)
#define DDRPHY_PTR4_TDINIT3_GET(x) (((uint32_t)(x) & DDRPHY_PTR4_TDINIT3_MASK) >> DDRPHY_PTR4_TDINIT3_SHIFT)

/*
 * TDINIT2 (R/W)
 *
 * DRAM Initialization Time 2: DRAM initialization time in DRAM clock cycles corresponding to the following:
 * DDR3 = Reset low time (200 us on power-up or 100 ns after power-up) Default value corresponds to DDR3 200 us at 1066 MHz.
 */
#define DDRPHY_PTR4_TDINIT2_MASK (0x3FFFFUL)
#define DDRPHY_PTR4_TDINIT2_SHIFT (0U)
#define DDRPHY_PTR4_TDINIT2_SET(x) (((uint32_t)(x) << DDRPHY_PTR4_TDINIT2_SHIFT) & DDRPHY_PTR4_TDINIT2_MASK)
#define DDRPHY_PTR4_TDINIT2_GET(x) (((uint32_t)(x) & DDRPHY_PTR4_TDINIT2_MASK) >> DDRPHY_PTR4_TDINIT2_SHIFT)

/* Bitfield definition for register: ACMDLR */
/*
 * MDLD (R/W)
 *
 * MDL Delay: Delay select for the LCDL for the Master Delay Line.
 */
#define DDRPHY_ACMDLR_MDLD_MASK (0xFF0000UL)
#define DDRPHY_ACMDLR_MDLD_SHIFT (16U)
#define DDRPHY_ACMDLR_MDLD_SET(x) (((uint32_t)(x) << DDRPHY_ACMDLR_MDLD_SHIFT) & DDRPHY_ACMDLR_MDLD_MASK)
#define DDRPHY_ACMDLR_MDLD_GET(x) (((uint32_t)(x) & DDRPHY_ACMDLR_MDLD_MASK) >> DDRPHY_ACMDLR_MDLD_SHIFT)

/*
 * TPRD (R/W)
 *
 * Target Period: Target period measured by the master delay line calibration for VT drift compensation. This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
 */
#define DDRPHY_ACMDLR_TPRD_MASK (0xFF00U)
#define DDRPHY_ACMDLR_TPRD_SHIFT (8U)
#define DDRPHY_ACMDLR_TPRD_SET(x) (((uint32_t)(x) << DDRPHY_ACMDLR_TPRD_SHIFT) & DDRPHY_ACMDLR_TPRD_MASK)
#define DDRPHY_ACMDLR_TPRD_GET(x) (((uint32_t)(x) & DDRPHY_ACMDLR_TPRD_MASK) >> DDRPHY_ACMDLR_TPRD_SHIFT)

/*
 * IPRD (R/W)
 *
 * Initial Period: Initial period measured by the master delay line calibration for VT drift compensation. This value is used as the denominator when calculating the ratios of updates during VT compensation.
 */
#define DDRPHY_ACMDLR_IPRD_MASK (0xFFU)
#define DDRPHY_ACMDLR_IPRD_SHIFT (0U)
#define DDRPHY_ACMDLR_IPRD_SET(x) (((uint32_t)(x) << DDRPHY_ACMDLR_IPRD_SHIFT) & DDRPHY_ACMDLR_IPRD_MASK)
#define DDRPHY_ACMDLR_IPRD_GET(x) (((uint32_t)(x) & DDRPHY_ACMDLR_IPRD_MASK) >> DDRPHY_ACMDLR_IPRD_SHIFT)

/* Bitfield definition for register: ACBDLR */
/*
 * ACBD (R/W)
 *
 * Address/Command Bit Delay: Delay select for the BDLs on address and command signals.
 */
#define DDRPHY_ACBDLR_ACBD_MASK (0xFC0000UL)
#define DDRPHY_ACBDLR_ACBD_SHIFT (18U)
#define DDRPHY_ACBDLR_ACBD_SET(x) (((uint32_t)(x) << DDRPHY_ACBDLR_ACBD_SHIFT) & DDRPHY_ACBDLR_ACBD_MASK)
#define DDRPHY_ACBDLR_ACBD_GET(x) (((uint32_t)(x) & DDRPHY_ACBDLR_ACBD_MASK) >> DDRPHY_ACBDLR_ACBD_SHIFT)

/*
 * CK2BD (R/W)
 *
 * CK2 Bit Delay: Delay select for the BDL on CK2.
 */
#define DDRPHY_ACBDLR_CK2BD_MASK (0x3F000UL)
#define DDRPHY_ACBDLR_CK2BD_SHIFT (12U)
#define DDRPHY_ACBDLR_CK2BD_SET(x) (((uint32_t)(x) << DDRPHY_ACBDLR_CK2BD_SHIFT) & DDRPHY_ACBDLR_CK2BD_MASK)
#define DDRPHY_ACBDLR_CK2BD_GET(x) (((uint32_t)(x) & DDRPHY_ACBDLR_CK2BD_MASK) >> DDRPHY_ACBDLR_CK2BD_SHIFT)

/*
 * CK1BD (R/W)
 *
 * CK1 Bit Delay: Delay select for the BDL on CK1.
 */
#define DDRPHY_ACBDLR_CK1BD_MASK (0xFC0U)
#define DDRPHY_ACBDLR_CK1BD_SHIFT (6U)
#define DDRPHY_ACBDLR_CK1BD_SET(x) (((uint32_t)(x) << DDRPHY_ACBDLR_CK1BD_SHIFT) & DDRPHY_ACBDLR_CK1BD_MASK)
#define DDRPHY_ACBDLR_CK1BD_GET(x) (((uint32_t)(x) & DDRPHY_ACBDLR_CK1BD_MASK) >> DDRPHY_ACBDLR_CK1BD_SHIFT)

/*
 * CK0BD (R/W)
 *
 * CK0 Bit Delay: Delay select for the BDL on CK0.
 */
#define DDRPHY_ACBDLR_CK0BD_MASK (0x3FU)
#define DDRPHY_ACBDLR_CK0BD_SHIFT (0U)
#define DDRPHY_ACBDLR_CK0BD_SET(x) (((uint32_t)(x) << DDRPHY_ACBDLR_CK0BD_SHIFT) & DDRPHY_ACBDLR_CK0BD_MASK)
#define DDRPHY_ACBDLR_CK0BD_GET(x) (((uint32_t)(x) & DDRPHY_ACBDLR_CK0BD_MASK) >> DDRPHY_ACBDLR_CK0BD_SHIFT)

/* Bitfield definition for register: ACIOCR */
/*
 * ACSR (R/W)
 *
 * Address/Command Slew Rate (D3F I/O Only): Selects slew rate of the I/O for all address and command pins.
 */
#define DDRPHY_ACIOCR_ACSR_MASK (0xC0000000UL)
#define DDRPHY_ACIOCR_ACSR_SHIFT (30U)
#define DDRPHY_ACIOCR_ACSR_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACSR_SHIFT) & DDRPHY_ACIOCR_ACSR_MASK)
#define DDRPHY_ACIOCR_ACSR_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACSR_MASK) >> DDRPHY_ACIOCR_ACSR_SHIFT)

/*
 * RSTIOM (R/W)
 *
 * SDRAM Reset I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for SDRAM Reset.
 */
#define DDRPHY_ACIOCR_RSTIOM_MASK (0x20000000UL)
#define DDRPHY_ACIOCR_RSTIOM_SHIFT (29U)
#define DDRPHY_ACIOCR_RSTIOM_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RSTIOM_SHIFT) & DDRPHY_ACIOCR_RSTIOM_MASK)
#define DDRPHY_ACIOCR_RSTIOM_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RSTIOM_MASK) >> DDRPHY_ACIOCR_RSTIOM_SHIFT)

/*
 * RSTPDR (R/W)
 *
 * SDRAM Reset Power Down Receiver: Powers down, when set, the input receiver on the I/O for SDRAM RST# pin.
 */
#define DDRPHY_ACIOCR_RSTPDR_MASK (0x10000000UL)
#define DDRPHY_ACIOCR_RSTPDR_SHIFT (28U)
#define DDRPHY_ACIOCR_RSTPDR_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RSTPDR_SHIFT) & DDRPHY_ACIOCR_RSTPDR_MASK)
#define DDRPHY_ACIOCR_RSTPDR_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RSTPDR_MASK) >> DDRPHY_ACIOCR_RSTPDR_SHIFT)

/*
 * RSTPDD1 (R/W)
 *
 * SDRAM Reset Power Down Driver: Powers down, when set, the output driver on the I/O for SDRAM RST# pin.
 */
#define DDRPHY_ACIOCR_RSTPDD1_MASK (0x8000000UL)
#define DDRPHY_ACIOCR_RSTPDD1_SHIFT (27U)
#define DDRPHY_ACIOCR_RSTPDD1_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RSTPDD1_SHIFT) & DDRPHY_ACIOCR_RSTPDD1_MASK)
#define DDRPHY_ACIOCR_RSTPDD1_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RSTPDD1_MASK) >> DDRPHY_ACIOCR_RSTPDD1_SHIFT)

/*
 * RSTODT (R/W)
 *
 * SDRAM Reset On-Die Termination: Enables, when set, the on-die termination on the I/O for SDRAM RST# pin.
 */
#define DDRPHY_ACIOCR_RSTODT_MASK (0x4000000UL)
#define DDRPHY_ACIOCR_RSTODT_SHIFT (26U)
#define DDRPHY_ACIOCR_RSTODT_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RSTODT_SHIFT) & DDRPHY_ACIOCR_RSTODT_MASK)
#define DDRPHY_ACIOCR_RSTODT_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RSTODT_MASK) >> DDRPHY_ACIOCR_RSTODT_SHIFT)

/*
 * RANKPDR (R/W)
 *
 * Rank Power Down Receiver: Powers down, when set, the input receiver on the I/O CKE[3:0], ODT[3:0], and CS#[3:0] pins. RANKPDR[0] controls the power down for CKE[0], ODT[0], and CS#[0], RANKPDR[1] controls the power down for CKE[1], ODT[1], and CS#[1], and so on.
 */
#define DDRPHY_ACIOCR_RANKPDR_MASK (0x3C00000UL)
#define DDRPHY_ACIOCR_RANKPDR_SHIFT (22U)
#define DDRPHY_ACIOCR_RANKPDR_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RANKPDR_SHIFT) & DDRPHY_ACIOCR_RANKPDR_MASK)
#define DDRPHY_ACIOCR_RANKPDR_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RANKPDR_MASK) >> DDRPHY_ACIOCR_RANKPDR_SHIFT)

/*
 * CSPDD1 (R/W)
 *
 * CS# Power Down Driver: Powers down, when set, the output driver on the I/O for CS#[3:0] pins. CSPDD[0] controls the power down for CS#[0], CSPDD[1] controls the power down for CS#[1], and so on. CKE and ODT driver power down is controlled by DSGCR register.
 */
#define DDRPHY_ACIOCR_CSPDD1_MASK (0x3C0000UL)
#define DDRPHY_ACIOCR_CSPDD1_SHIFT (18U)
#define DDRPHY_ACIOCR_CSPDD1_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_CSPDD1_SHIFT) & DDRPHY_ACIOCR_CSPDD1_MASK)
#define DDRPHY_ACIOCR_CSPDD1_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_CSPDD1_MASK) >> DDRPHY_ACIOCR_CSPDD1_SHIFT)

/*
 * RANKODT (R/W)
 *
 * Rank On-Die Termination: Enables, when set, the on-die termination on the I/O for CKE[3:0], ODT[3:0], and CS#[3:0] pins. RANKODT[0] controls the on-die termination for CKE[0], ODT[0], and CS#[0], RANKODT[1] controls the on-die termination for CKE[1], ODT[1], and CS#[1], and so on.
 */
#define DDRPHY_ACIOCR_RANKODT_MASK (0x3C000UL)
#define DDRPHY_ACIOCR_RANKODT_SHIFT (14U)
#define DDRPHY_ACIOCR_RANKODT_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_RANKODT_SHIFT) & DDRPHY_ACIOCR_RANKODT_MASK)
#define DDRPHY_ACIOCR_RANKODT_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_RANKODT_MASK) >> DDRPHY_ACIOCR_RANKODT_SHIFT)

/*
 * CKPDR (R/W)
 *
 * CK Power Down Receiver: Powers down, when set, the input receiver on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
 */
#define DDRPHY_ACIOCR_CKPDR_MASK (0x3800U)
#define DDRPHY_ACIOCR_CKPDR_SHIFT (11U)
#define DDRPHY_ACIOCR_CKPDR_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_CKPDR_SHIFT) & DDRPHY_ACIOCR_CKPDR_MASK)
#define DDRPHY_ACIOCR_CKPDR_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_CKPDR_MASK) >> DDRPHY_ACIOCR_CKPDR_SHIFT)

/*
 * CKPDD1 (R/W)
 *
 * CK Power Down Driver: Powers down, when set, the output driver on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
 */
#define DDRPHY_ACIOCR_CKPDD1_MASK (0x700U)
#define DDRPHY_ACIOCR_CKPDD1_SHIFT (8U)
#define DDRPHY_ACIOCR_CKPDD1_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_CKPDD1_SHIFT) & DDRPHY_ACIOCR_CKPDD1_MASK)
#define DDRPHY_ACIOCR_CKPDD1_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_CKPDD1_MASK) >> DDRPHY_ACIOCR_CKPDD1_SHIFT)

/*
 * CKODT (R/W)
 *
 * CK On-Die Termination: Enables, when set, the on-die termination on the I/O for CK[0], CK[1], and CK[2] pins, respectively.
 */
#define DDRPHY_ACIOCR_CKODT_MASK (0xE0U)
#define DDRPHY_ACIOCR_CKODT_SHIFT (5U)
#define DDRPHY_ACIOCR_CKODT_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_CKODT_SHIFT) & DDRPHY_ACIOCR_CKODT_MASK)
#define DDRPHY_ACIOCR_CKODT_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_CKODT_MASK) >> DDRPHY_ACIOCR_CKODT_SHIFT)

/*
 * ACPDR (R/W)
 *
 * AC Power Down Receiver: Powers down, when set, the input receiver on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 */
#define DDRPHY_ACIOCR_ACPDR_MASK (0x10U)
#define DDRPHY_ACIOCR_ACPDR_SHIFT (4U)
#define DDRPHY_ACIOCR_ACPDR_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACPDR_SHIFT) & DDRPHY_ACIOCR_ACPDR_MASK)
#define DDRPHY_ACIOCR_ACPDR_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACPDR_MASK) >> DDRPHY_ACIOCR_ACPDR_SHIFT)

/*
 * ACPDD1 (R/W)
 *
 * AC Power Down Driver: Powers down, when set, the output driver on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 */
#define DDRPHY_ACIOCR_ACPDD1_MASK (0x8U)
#define DDRPHY_ACIOCR_ACPDD1_SHIFT (3U)
#define DDRPHY_ACIOCR_ACPDD1_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACPDD1_SHIFT) & DDRPHY_ACIOCR_ACPDD1_MASK)
#define DDRPHY_ACIOCR_ACPDD1_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACPDD1_MASK) >> DDRPHY_ACIOCR_ACPDD1_SHIFT)

/*
 * ACODT (R/W)
 *
 * Address/Command On-Die Termination: Enables, when set, the on-die termination on the I/O for RAS#, CAS#, WE#, BA[2:0], and A[15:0] pins.
 */
#define DDRPHY_ACIOCR_ACODT_MASK (0x4U)
#define DDRPHY_ACIOCR_ACODT_SHIFT (2U)
#define DDRPHY_ACIOCR_ACODT_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACODT_SHIFT) & DDRPHY_ACIOCR_ACODT_MASK)
#define DDRPHY_ACIOCR_ACODT_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACODT_MASK) >> DDRPHY_ACIOCR_ACODT_SHIFT)

/*
 * ACOE (R/W)
 *
 * Address/Command Output Enable: Enables, when set, the output driver on the I/O for all address and command pins.
 */
#define DDRPHY_ACIOCR_ACOE_MASK (0x2U)
#define DDRPHY_ACIOCR_ACOE_SHIFT (1U)
#define DDRPHY_ACIOCR_ACOE_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACOE_SHIFT) & DDRPHY_ACIOCR_ACOE_MASK)
#define DDRPHY_ACIOCR_ACOE_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACOE_MASK) >> DDRPHY_ACIOCR_ACOE_SHIFT)

/*
 * ACIOM (R/W)
 *
 * Address/Command I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for all address and command pins. This bit connects to bit
 * [0] of the IOM pin on the D3F I/Os, and for other I/O libraries, it connects to the IOM pin of the I/O.
 */
#define DDRPHY_ACIOCR_ACIOM_MASK (0x1U)
#define DDRPHY_ACIOCR_ACIOM_SHIFT (0U)
#define DDRPHY_ACIOCR_ACIOM_SET(x) (((uint32_t)(x) << DDRPHY_ACIOCR_ACIOM_SHIFT) & DDRPHY_ACIOCR_ACIOM_MASK)
#define DDRPHY_ACIOCR_ACIOM_GET(x) (((uint32_t)(x) & DDRPHY_ACIOCR_ACIOM_MASK) >> DDRPHY_ACIOCR_ACIOM_SHIFT)

/* Bitfield definition for register: DXCCR */
/*
 * DDPDRCDO (R/W)
 *
 * Dynamic Data Power Down Receiver Count Down Offset: Offset applied in calculating window of time where receiver is powered up
 */
#define DDRPHY_DXCCR_DDPDRCDO_MASK (0xF0000000UL)
#define DDRPHY_DXCCR_DDPDRCDO_SHIFT (28U)
#define DDRPHY_DXCCR_DDPDRCDO_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DDPDRCDO_SHIFT) & DDRPHY_DXCCR_DDPDRCDO_MASK)
#define DDRPHY_DXCCR_DDPDRCDO_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DDPDRCDO_MASK) >> DDRPHY_DXCCR_DDPDRCDO_SHIFT)

/*
 * DDPDDCDO (R/W)
 *
 * Dynamic Data Power Down Driver Count Down Offset: Offset applied in calculating window of time where driver is powered up
 */
#define DDRPHY_DXCCR_DDPDDCDO_MASK (0xF000000UL)
#define DDRPHY_DXCCR_DDPDDCDO_SHIFT (24U)
#define DDRPHY_DXCCR_DDPDDCDO_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DDPDDCDO_SHIFT) & DDRPHY_DXCCR_DDPDDCDO_MASK)
#define DDRPHY_DXCCR_DDPDDCDO_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DDPDDCDO_MASK) >> DDRPHY_DXCCR_DDPDDCDO_SHIFT)

/*
 * DYNDXPDR (R/W)
 *
 * Data Power Down Receiver: Dynamically powers down, when set, the input receiver on I/O for the DQ pins of the active DATX8 macros. Applies only when DXPDR and DXnGCR.DXPDR are not set to 1. Receiver is powered-up on a DFI READ command and powered-down (trddata_en + fixed_read_latency + n) HDR cycles after the last DFI READ command. Note that n is defined by the register bit field DXCCR[31:28] (DDPDRCDO).
 */
#define DDRPHY_DXCCR_DYNDXPDR_MASK (0x800000UL)
#define DDRPHY_DXCCR_DYNDXPDR_SHIFT (23U)
#define DDRPHY_DXCCR_DYNDXPDR_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DYNDXPDR_SHIFT) & DDRPHY_DXCCR_DYNDXPDR_MASK)
#define DDRPHY_DXCCR_DYNDXPDR_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DYNDXPDR_MASK) >> DDRPHY_DXCCR_DYNDXPDR_SHIFT)

/*
 * DYNDXPDD1 (R/W)
 *
 * Dynamic Data Power Down Driver: Dynamically powers down, when set, the output driver on I/O for the DQ pins of the active DATX8 macros. Applies only when DXPDD and DXnGCR.DXPDD are not set to 1. Driver is powered-up on a DFI WRITE command and powered-down (twrlat + WL/2 + n) HDR cycles after the last DFI WRITE command. Note that n is defined by the register bit field DXCCR[27:24] (DDPDDCDO).
 */
#define DDRPHY_DXCCR_DYNDXPDD1_MASK (0x400000UL)
#define DDRPHY_DXCCR_DYNDXPDD1_SHIFT (22U)
#define DDRPHY_DXCCR_DYNDXPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DYNDXPDD1_SHIFT) & DDRPHY_DXCCR_DYNDXPDD1_MASK)
#define DDRPHY_DXCCR_DYNDXPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DYNDXPDD1_MASK) >> DDRPHY_DXCCR_DYNDXPDD1_SHIFT)

/*
 * UDQIOM (R/W)
 *
 * Unused DQ I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for unused DQ pins.
 */
#define DDRPHY_DXCCR_UDQIOM_MASK (0x200000UL)
#define DDRPHY_DXCCR_UDQIOM_SHIFT (21U)
#define DDRPHY_DXCCR_UDQIOM_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_UDQIOM_SHIFT) & DDRPHY_DXCCR_UDQIOM_MASK)
#define DDRPHY_DXCCR_UDQIOM_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_UDQIOM_MASK) >> DDRPHY_DXCCR_UDQIOM_SHIFT)

/*
 * UDQPDR (R/W)
 *
 * Unused DQ Power Down Receiver: Powers down, when set, the input receiver on the I/O for unused DQ pins.
 */
#define DDRPHY_DXCCR_UDQPDR_MASK (0x100000UL)
#define DDRPHY_DXCCR_UDQPDR_SHIFT (20U)
#define DDRPHY_DXCCR_UDQPDR_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_UDQPDR_SHIFT) & DDRPHY_DXCCR_UDQPDR_MASK)
#define DDRPHY_DXCCR_UDQPDR_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_UDQPDR_MASK) >> DDRPHY_DXCCR_UDQPDR_SHIFT)

/*
 * UDQPDD1 (R/W)
 *
 * Unused DQ Power Down Driver: Powers down, when set, the output driver on the I/O for unused DQ pins.
 */
#define DDRPHY_DXCCR_UDQPDD1_MASK (0x80000UL)
#define DDRPHY_DXCCR_UDQPDD1_SHIFT (19U)
#define DDRPHY_DXCCR_UDQPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_UDQPDD1_SHIFT) & DDRPHY_DXCCR_UDQPDD1_MASK)
#define DDRPHY_DXCCR_UDQPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_UDQPDD1_MASK) >> DDRPHY_DXCCR_UDQPDD1_SHIFT)

/*
 * UDQODT (R/W)
 *
 * Unused DQ On-Die Termination: Enables, when set, the on-die termination on the I/O for unused DQ pins.
 */
#define DDRPHY_DXCCR_UDQODT_MASK (0x40000UL)
#define DDRPHY_DXCCR_UDQODT_SHIFT (18U)
#define DDRPHY_DXCCR_UDQODT_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_UDQODT_SHIFT) & DDRPHY_DXCCR_UDQODT_MASK)
#define DDRPHY_DXCCR_UDQODT_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_UDQODT_MASK) >> DDRPHY_DXCCR_UDQODT_SHIFT)

/*
 * MSBUDQ (R/W)
 *
 * Most Significant Byte Unused DQs: Specifies the number of DQ bits that are not used in the most significant byte. The used (valid) bits for this byte are [8-MSBDQ- 1:0]. To disable the whole byte, use the DXnGCR.DXEN register.
 */
#define DDRPHY_DXCCR_MSBUDQ_MASK (0x38000UL)
#define DDRPHY_DXCCR_MSBUDQ_SHIFT (15U)
#define DDRPHY_DXCCR_MSBUDQ_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_MSBUDQ_SHIFT) & DDRPHY_DXCCR_MSBUDQ_MASK)
#define DDRPHY_DXCCR_MSBUDQ_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_MSBUDQ_MASK) >> DDRPHY_DXCCR_MSBUDQ_SHIFT)

/*
 * DXSR (R/W)
 *
 * Data Slew Rate (D3F I/O Only): Selects slew rate of the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros.
 */
#define DDRPHY_DXCCR_DXSR_MASK (0x6000U)
#define DDRPHY_DXCCR_DXSR_SHIFT (13U)
#define DDRPHY_DXCCR_DXSR_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DXSR_SHIFT) & DDRPHY_DXCCR_DXSR_MASK)
#define DDRPHY_DXCCR_DXSR_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DXSR_MASK) >> DDRPHY_DXCCR_DXSR_SHIFT)

/*
 * DQSNRES (R/W)
 *
 * DQS# Resistor: Selects the on-die pull-up/pull-down resistor for DQS# pins. Same encoding as DQSRES.
 * Refer PHY databook for pull-down/pull-up resistor values (RA_SEL/RB_SEL) for DQS/DQS_b.
 */
#define DDRPHY_DXCCR_DQSNRES_MASK (0x1E00U)
#define DDRPHY_DXCCR_DQSNRES_SHIFT (9U)
#define DDRPHY_DXCCR_DQSNRES_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DQSNRES_SHIFT) & DDRPHY_DXCCR_DQSNRES_MASK)
#define DDRPHY_DXCCR_DQSNRES_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DQSNRES_MASK) >> DDRPHY_DXCCR_DQSNRES_SHIFT)

/*
 * DQSRES (R/W)
 *
 * DQS Resistor: Selects the on-die pull-down/pull-up resistor for DQS pins. DQSRES[3] selects pull-down (when set to 0) or pull-up (when set to 1). DQSRES[2:0] selects the resistor value.
 * Refer PHY databook for pull-down/pull-up resistor values (RA_SEL/RB_SEL) for DQS/DQS_b.
 */
#define DDRPHY_DXCCR_DQSRES_MASK (0x1E0U)
#define DDRPHY_DXCCR_DQSRES_SHIFT (5U)
#define DDRPHY_DXCCR_DQSRES_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DQSRES_SHIFT) & DDRPHY_DXCCR_DQSRES_MASK)
#define DDRPHY_DXCCR_DQSRES_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DQSRES_MASK) >> DDRPHY_DXCCR_DQSRES_SHIFT)

/*
 * DXPDR (R/W)
 *
 * Data Power Down Receiver: Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed with the PDR configuration bit of the individual DATX8.
 */
#define DDRPHY_DXCCR_DXPDR_MASK (0x10U)
#define DDRPHY_DXCCR_DXPDR_SHIFT (4U)
#define DDRPHY_DXCCR_DXPDR_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DXPDR_SHIFT) & DDRPHY_DXCCR_DXPDR_MASK)
#define DDRPHY_DXCCR_DXPDR_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DXPDR_MASK) >> DDRPHY_DXCCR_DXPDR_SHIFT)

/*
 * DXPDD1 (R/W)
 *
 * Data Power Down Driver: Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed with the PDD configuration bit of the individual DATX8.
 */
#define DDRPHY_DXCCR_DXPDD1_MASK (0x8U)
#define DDRPHY_DXCCR_DXPDD1_SHIFT (3U)
#define DDRPHY_DXCCR_DXPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DXPDD1_SHIFT) & DDRPHY_DXCCR_DXPDD1_MASK)
#define DDRPHY_DXCCR_DXPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DXPDD1_MASK) >> DDRPHY_DXCCR_DXPDD1_SHIFT)

/*
 * MDLEN (R/W)
 *
 * Master Delay Line Enable: Enables, if set, all DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or on when calibration is manually triggered. These additional measurements are accumulated and filtered as long as this bit remains high. This bit is ANDed with the MDLEN bit in the individual DATX8.
 */
#define DDRPHY_DXCCR_MDLEN_MASK (0x4U)
#define DDRPHY_DXCCR_MDLEN_SHIFT (2U)
#define DDRPHY_DXCCR_MDLEN_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_MDLEN_SHIFT) & DDRPHY_DXCCR_MDLEN_MASK)
#define DDRPHY_DXCCR_MDLEN_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_MDLEN_MASK) >> DDRPHY_DXCCR_MDLEN_SHIFT)

/*
 * DXIOM (R/W)
 *
 * Data I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed with the IOM configuration bit of the individual DATX8.
 */
#define DDRPHY_DXCCR_DXIOM_MASK (0x2U)
#define DDRPHY_DXCCR_DXIOM_SHIFT (1U)
#define DDRPHY_DXCCR_DXIOM_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DXIOM_SHIFT) & DDRPHY_DXCCR_DXIOM_MASK)
#define DDRPHY_DXCCR_DXIOM_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DXIOM_MASK) >> DDRPHY_DXCCR_DXIOM_SHIFT)

/*
 * DXODT (R/W)
 *
 * Data On-Die Termination: Enables, when set, the on-die termination on the I/O for DQ, DM, and DQS/DQS# pins of all DATX8 macros. This bit is ORed with the ODT configuration bit of the individual DATX8 (“DATX8 General Configuration Register (DXnGCR)” on page 148)
 */
#define DDRPHY_DXCCR_DXODT_MASK (0x1U)
#define DDRPHY_DXCCR_DXODT_SHIFT (0U)
#define DDRPHY_DXCCR_DXODT_SET(x) (((uint32_t)(x) << DDRPHY_DXCCR_DXODT_SHIFT) & DDRPHY_DXCCR_DXODT_MASK)
#define DDRPHY_DXCCR_DXODT_GET(x) (((uint32_t)(x) & DDRPHY_DXCCR_DXODT_MASK) >> DDRPHY_DXCCR_DXODT_SHIFT)

/* Bitfield definition for register: DSGCR */
/*
 * CKEOE (R/W)
 *
 * SDRAM CKE Output Enable: Enables, when set, the output driver on the I/O for SDRAM CKE pins.
 */
#define DDRPHY_DSGCR_CKEOE_MASK (0x80000000UL)
#define DDRPHY_DSGCR_CKEOE_SHIFT (31U)
#define DDRPHY_DSGCR_CKEOE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_CKEOE_SHIFT) & DDRPHY_DSGCR_CKEOE_MASK)
#define DDRPHY_DSGCR_CKEOE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_CKEOE_MASK) >> DDRPHY_DSGCR_CKEOE_SHIFT)

/*
 * RSTOE (R/W)
 *
 * SDRAM Reset Output Enable: Enables, when set, the output driver on the I/O for SDRAM RST# pin.
 */
#define DDRPHY_DSGCR_RSTOE_MASK (0x40000000UL)
#define DDRPHY_DSGCR_RSTOE_SHIFT (30U)
#define DDRPHY_DSGCR_RSTOE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_RSTOE_SHIFT) & DDRPHY_DSGCR_RSTOE_MASK)
#define DDRPHY_DSGCR_RSTOE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_RSTOE_MASK) >> DDRPHY_DSGCR_RSTOE_SHIFT)

/*
 * ODTOE (R/W)
 *
 * SDRAM ODT Output Enable: Enables, when set, the output driver on the I/O for SDRAM ODT pins.
 */
#define DDRPHY_DSGCR_ODTOE_MASK (0x20000000UL)
#define DDRPHY_DSGCR_ODTOE_SHIFT (29U)
#define DDRPHY_DSGCR_ODTOE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_ODTOE_SHIFT) & DDRPHY_DSGCR_ODTOE_MASK)
#define DDRPHY_DSGCR_ODTOE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_ODTOE_MASK) >> DDRPHY_DSGCR_ODTOE_SHIFT)

/*
 * CKOE (R/W)
 *
 * SDRAM CK Output Enable: Enables, when set, the output driver on the I/O for SDRAM CK/CK# pins.
 */
#define DDRPHY_DSGCR_CKOE_MASK (0x10000000UL)
#define DDRPHY_DSGCR_CKOE_SHIFT (28U)
#define DDRPHY_DSGCR_CKOE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_CKOE_SHIFT) & DDRPHY_DSGCR_CKOE_MASK)
#define DDRPHY_DSGCR_CKOE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_CKOE_MASK) >> DDRPHY_DSGCR_CKOE_SHIFT)

/*
 * ODTPDD1 (R/W)
 *
 * ODT Power Down Driver: Powers down, when set, the output driver on the I/O for ODT[3:0] pins. ODTPDD[0] controls the power down for ODT[0], ODTPDD[1] controls the power down for ODT[1], and so on.
 */
#define DDRPHY_DSGCR_ODTPDD1_MASK (0xF000000UL)
#define DDRPHY_DSGCR_ODTPDD1_SHIFT (24U)
#define DDRPHY_DSGCR_ODTPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_ODTPDD1_SHIFT) & DDRPHY_DSGCR_ODTPDD1_MASK)
#define DDRPHY_DSGCR_ODTPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_ODTPDD1_MASK) >> DDRPHY_DSGCR_ODTPDD1_SHIFT)

/*
 * CKEPDD1 (R/W)
 *
 * CKE Power Down Driver: Powers down, when set, the output driver on the I/O for CKE[3:0] pins. CKEPDD[0] controls the power down for CKE[0], CKEPDD[1] controls the power down for CKE[1], and so on.
 */
#define DDRPHY_DSGCR_CKEPDD1_MASK (0xF00000UL)
#define DDRPHY_DSGCR_CKEPDD1_SHIFT (20U)
#define DDRPHY_DSGCR_CKEPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_CKEPDD1_SHIFT) & DDRPHY_DSGCR_CKEPDD1_MASK)
#define DDRPHY_DSGCR_CKEPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_CKEPDD1_MASK) >> DDRPHY_DSGCR_CKEPDD1_SHIFT)

/*
 * SDRMODE (R/W)
 *
 * Single Data Rate Mode: Indicates, if set, that the external controller is configured to run in single data rate (SDR) mode. Otherwise if not set the controller is running in half data rate (HDR) mode. This bit not supported in the current version of the PUB.
 */
#define DDRPHY_DSGCR_SDRMODE_MASK (0x80000UL)
#define DDRPHY_DSGCR_SDRMODE_SHIFT (19U)
#define DDRPHY_DSGCR_SDRMODE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_SDRMODE_SHIFT) & DDRPHY_DSGCR_SDRMODE_MASK)
#define DDRPHY_DSGCR_SDRMODE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_SDRMODE_MASK) >> DDRPHY_DSGCR_SDRMODE_SHIFT)

/*
 * RRMODE (R/W)
 *
 * Rise-to-Rise Mode: Indicates, if set, that the PHY mission mode is configured to run in rise-to-rise mode. Otherwise if not set the PHY mission mode is running in rise-to- fall mode.
 */
#define DDRPHY_DSGCR_RRMODE_MASK (0x40000UL)
#define DDRPHY_DSGCR_RRMODE_SHIFT (18U)
#define DDRPHY_DSGCR_RRMODE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_RRMODE_SHIFT) & DDRPHY_DSGCR_RRMODE_MASK)
#define DDRPHY_DSGCR_RRMODE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_RRMODE_MASK) >> DDRPHY_DSGCR_RRMODE_SHIFT)

/*
 * ATOAE (R/W)
 *
 * ATO Analog Test Enable: Enables, if set, the analog test output (ATO) I/O.
 */
#define DDRPHY_DSGCR_ATOAE_MASK (0x20000UL)
#define DDRPHY_DSGCR_ATOAE_SHIFT (17U)
#define DDRPHY_DSGCR_ATOAE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_ATOAE_SHIFT) & DDRPHY_DSGCR_ATOAE_MASK)
#define DDRPHY_DSGCR_ATOAE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_ATOAE_MASK) >> DDRPHY_DSGCR_ATOAE_SHIFT)

/*
 * DTOOE (R/W)
 *
 * DTO Output Enable: Enables, when set, the output driver on the I/O for DTO pins.
 */
#define DDRPHY_DSGCR_DTOOE_MASK (0x10000UL)
#define DDRPHY_DSGCR_DTOOE_SHIFT (16U)
#define DDRPHY_DSGCR_DTOOE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DTOOE_SHIFT) & DDRPHY_DSGCR_DTOOE_MASK)
#define DDRPHY_DSGCR_DTOOE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DTOOE_MASK) >> DDRPHY_DSGCR_DTOOE_SHIFT)

/*
 * DTOIOM (R/W)
 *
 * DTO I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DTO pins.
 */
#define DDRPHY_DSGCR_DTOIOM_MASK (0x8000U)
#define DDRPHY_DSGCR_DTOIOM_SHIFT (15U)
#define DDRPHY_DSGCR_DTOIOM_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DTOIOM_SHIFT) & DDRPHY_DSGCR_DTOIOM_MASK)
#define DDRPHY_DSGCR_DTOIOM_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DTOIOM_MASK) >> DDRPHY_DSGCR_DTOIOM_SHIFT)

/*
 * DTOPDR (R/W)
 *
 * DTO Power Down Receiver: Powers down, when set, the input receiver on the I/O for DTO pins.
 */
#define DDRPHY_DSGCR_DTOPDR_MASK (0x4000U)
#define DDRPHY_DSGCR_DTOPDR_SHIFT (14U)
#define DDRPHY_DSGCR_DTOPDR_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DTOPDR_SHIFT) & DDRPHY_DSGCR_DTOPDR_MASK)
#define DDRPHY_DSGCR_DTOPDR_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DTOPDR_MASK) >> DDRPHY_DSGCR_DTOPDR_SHIFT)

/*
 * DTOPDD1 (R/W)
 *
 * DTO Power Down Driver: Powers down, when set, the output driver on the I/O for DTO pins.
 */
#define DDRPHY_DSGCR_DTOPDD1_MASK (0x2000U)
#define DDRPHY_DSGCR_DTOPDD1_SHIFT (13U)
#define DDRPHY_DSGCR_DTOPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DTOPDD1_SHIFT) & DDRPHY_DSGCR_DTOPDD1_MASK)
#define DDRPHY_DSGCR_DTOPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DTOPDD1_MASK) >> DDRPHY_DSGCR_DTOPDD1_SHIFT)

/*
 * DTOODT (R/W)
 *
 * DTO On-Die Termination: Enables, when set, the on-die termination on the I/O for DTO pins.
 */
#define DDRPHY_DSGCR_DTOODT_MASK (0x1000U)
#define DDRPHY_DSGCR_DTOODT_SHIFT (12U)
#define DDRPHY_DSGCR_DTOODT_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DTOODT_SHIFT) & DDRPHY_DSGCR_DTOODT_MASK)
#define DDRPHY_DSGCR_DTOODT_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DTOODT_MASK) >> DDRPHY_DSGCR_DTOODT_SHIFT)

/*
 * PUAD (R/W)
 *
 * PHY Update Acknowledge Delay: Specifies the number of clock cycles that the indication for the completion of PHY update from the PHY to the controller should be delayed. This essentially delays, by this many clock cycles, the de-assertion of dfi_ctrlup_ack and dfi_phyupd_req signals relative to the time when the delay lines or I/Os are updated.
 */
#define DDRPHY_DSGCR_PUAD_MASK (0xF00U)
#define DDRPHY_DSGCR_PUAD_SHIFT (8U)
#define DDRPHY_DSGCR_PUAD_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_PUAD_SHIFT) & DDRPHY_DSGCR_PUAD_MASK)
#define DDRPHY_DSGCR_PUAD_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_PUAD_MASK) >> DDRPHY_DSGCR_PUAD_SHIFT)

/*
 * BRRMODE (R/W)
 *
 * Bypass Rise-to-Rise Mode: Indicates, if set, that the PHY bypass mode is configured to run in rise-to-rise mode. Otherwise if not set the PHY bypass mode is running in rise-to-fall mode.
 */
#define DDRPHY_DSGCR_BRRMODE_MASK (0x80U)
#define DDRPHY_DSGCR_BRRMODE_SHIFT (7U)
#define DDRPHY_DSGCR_BRRMODE_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_BRRMODE_SHIFT) & DDRPHY_DSGCR_BRRMODE_MASK)
#define DDRPHY_DSGCR_BRRMODE_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_BRRMODE_MASK) >> DDRPHY_DSGCR_BRRMODE_SHIFT)

/*
 * DQSGX (R/W)
 *
 * DQS Gate Extension: Specifies, if set, that the DQS gating must be extended by two DRAM clock cycles and then re-centered, i.e. one clock cycle extension on either side.
 */
#define DDRPHY_DSGCR_DQSGX_MASK (0x40U)
#define DDRPHY_DSGCR_DQSGX_SHIFT (6U)
#define DDRPHY_DSGCR_DQSGX_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_DQSGX_SHIFT) & DDRPHY_DSGCR_DQSGX_MASK)
#define DDRPHY_DSGCR_DQSGX_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_DQSGX_MASK) >> DDRPHY_DSGCR_DQSGX_SHIFT)

/*
 * CUAEN (R/W)
 *
 * Controller Update Acknowledge Enable: Specifies, if set, that the PHY should issue controller update acknowledge when the DFI controller update request is asserted. By default the PHY does not acknowledge controller initiated update requests but simply does an update whenever there is a controller update request. This speeds up the update.
 */
#define DDRPHY_DSGCR_CUAEN_MASK (0x20U)
#define DDRPHY_DSGCR_CUAEN_SHIFT (5U)
#define DDRPHY_DSGCR_CUAEN_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_CUAEN_SHIFT) & DDRPHY_DSGCR_CUAEN_MASK)
#define DDRPHY_DSGCR_CUAEN_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_CUAEN_MASK) >> DDRPHY_DSGCR_CUAEN_SHIFT)

/*
 * LPPLLPD (R/W)
 *
 * Low Power PLL Power Down: Specifies, if set, that the PHY should respond to the DFI low power opportunity request and power down the PLL of the byte if the wakeup time request satisfies the PLL lock time.
 */
#define DDRPHY_DSGCR_LPPLLPD_MASK (0x10U)
#define DDRPHY_DSGCR_LPPLLPD_SHIFT (4U)
#define DDRPHY_DSGCR_LPPLLPD_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_LPPLLPD_SHIFT) & DDRPHY_DSGCR_LPPLLPD_MASK)
#define DDRPHY_DSGCR_LPPLLPD_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_LPPLLPD_MASK) >> DDRPHY_DSGCR_LPPLLPD_SHIFT)

/*
 * LPIOPD (R/W)
 *
 * Low Power I/O Power Down: Specifies, if set, that the PHY should respond to the DFI low power opportunity request and power down the I/Os of the byte.
 */
#define DDRPHY_DSGCR_LPIOPD_MASK (0x8U)
#define DDRPHY_DSGCR_LPIOPD_SHIFT (3U)
#define DDRPHY_DSGCR_LPIOPD_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_LPIOPD_SHIFT) & DDRPHY_DSGCR_LPIOPD_MASK)
#define DDRPHY_DSGCR_LPIOPD_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_LPIOPD_MASK) >> DDRPHY_DSGCR_LPIOPD_SHIFT)

/*
 * ZUEN (R/W)
 *
 * Impedance Update Enable: Specifies, if set, that in addition to DDL VT update, the PHY could also perform impedance calibration (update).
 * Refer to the “Impedance Control Register 0-1 (ZQnCR0-1)” on page 145 bit fields DFICU0, DFICU1 and DFICCU bits to control if an impedance calibration is performed (update) with a DFI controller update request.
 * Refer to the “Impedance Control Register 0-1 (ZQnCR0-1)” on page 145 bit fields DFIPU0 and DFIPU1 bits to control if an impedance calibration is performed (update) with a DFI PHY update request.
 */
#define DDRPHY_DSGCR_ZUEN_MASK (0x4U)
#define DDRPHY_DSGCR_ZUEN_SHIFT (2U)
#define DDRPHY_DSGCR_ZUEN_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_ZUEN_SHIFT) & DDRPHY_DSGCR_ZUEN_MASK)
#define DDRPHY_DSGCR_ZUEN_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_ZUEN_MASK) >> DDRPHY_DSGCR_ZUEN_SHIFT)

/*
 * BDISEN (R/W)
 *
 * Byte Disable Enable: Specifies, if set, that the PHY should respond to DFI byte disable request. Otherwise the byte disable from the DFI is ignored in which case bytes can only be disabled using the DXnGCR register.
 */
#define DDRPHY_DSGCR_BDISEN_MASK (0x2U)
#define DDRPHY_DSGCR_BDISEN_SHIFT (1U)
#define DDRPHY_DSGCR_BDISEN_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_BDISEN_SHIFT) & DDRPHY_DSGCR_BDISEN_MASK)
#define DDRPHY_DSGCR_BDISEN_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_BDISEN_MASK) >> DDRPHY_DSGCR_BDISEN_SHIFT)

/*
 * PUREN (R/W)
 *
 * PHY Update Request Enable: Specifies if set, that the PHY should issue PHY- initiated update request when there is DDL VT drift.
 */
#define DDRPHY_DSGCR_PUREN_MASK (0x1U)
#define DDRPHY_DSGCR_PUREN_SHIFT (0U)
#define DDRPHY_DSGCR_PUREN_SET(x) (((uint32_t)(x) << DDRPHY_DSGCR_PUREN_SHIFT) & DDRPHY_DSGCR_PUREN_MASK)
#define DDRPHY_DSGCR_PUREN_GET(x) (((uint32_t)(x) & DDRPHY_DSGCR_PUREN_MASK) >> DDRPHY_DSGCR_PUREN_SHIFT)

/* Bitfield definition for register: DCR */
/*
 * UDIMM (R/W)
 *
 * Un-buffered DIMM Address Mirroring: Indicates, if set, that there is address mirroring on the second rank of an un-buffered DIMM (the rank connected to CS#[1]). In this case, the PUB re-scrambles the bank and address when sending mode register commands to the second rank. This only applies to PUB internal SDRAM transactions. Transactions generated by the controller must make its own adjustments when using an un-buffered DIMM. DCR[NOSRA] must be set if address mirroring is enabled.
 */
#define DDRPHY_DCR_UDIMM_MASK (0x20000000UL)
#define DDRPHY_DCR_UDIMM_SHIFT (29U)
#define DDRPHY_DCR_UDIMM_SET(x) (((uint32_t)(x) << DDRPHY_DCR_UDIMM_SHIFT) & DDRPHY_DCR_UDIMM_MASK)
#define DDRPHY_DCR_UDIMM_GET(x) (((uint32_t)(x) & DDRPHY_DCR_UDIMM_MASK) >> DDRPHY_DCR_UDIMM_SHIFT)

/*
 * DDR2T (R/W)
 *
 * DDR 2T Timing: Indicates, if set, that 2T timing should be used by PUB internally generated SDRAM transactions.
 */
#define DDRPHY_DCR_DDR2T_MASK (0x10000000UL)
#define DDRPHY_DCR_DDR2T_SHIFT (28U)
#define DDRPHY_DCR_DDR2T_SET(x) (((uint32_t)(x) << DDRPHY_DCR_DDR2T_SHIFT) & DDRPHY_DCR_DDR2T_MASK)
#define DDRPHY_DCR_DDR2T_GET(x) (((uint32_t)(x) & DDRPHY_DCR_DDR2T_MASK) >> DDRPHY_DCR_DDR2T_SHIFT)

/*
 * NOSRA (R/W)
 *
 * No Simultaneous Rank Access: Specifies, if set, that simultaneous rank access on the same clock cycle is not allowed. This means that multiple chip select signals should not be asserted at the same time. This may be required on some DIMM systems.
 */
#define DDRPHY_DCR_NOSRA_MASK (0x8000000UL)
#define DDRPHY_DCR_NOSRA_SHIFT (27U)
#define DDRPHY_DCR_NOSRA_SET(x) (((uint32_t)(x) << DDRPHY_DCR_NOSRA_SHIFT) & DDRPHY_DCR_NOSRA_MASK)
#define DDRPHY_DCR_NOSRA_GET(x) (((uint32_t)(x) & DDRPHY_DCR_NOSRA_MASK) >> DDRPHY_DCR_NOSRA_SHIFT)

/*
 * BYTEMASK (R/W)
 *
 * Byte Mask: Mask applied to all beats of read data on all bytes lanes during read DQS gate training. This allows training to be conducted based on selected bit(s) from the byte lanes.
 * Valid values for each bit are:
 * 0 = Disable compare for that bit 1 = Enable compare for that bit
 * Note that this mask applies in DDR3 MPR operation mode as well and must be in keeping with the PDQ field setting.
 */
#define DDRPHY_DCR_BYTEMASK_MASK (0x3FC00UL)
#define DDRPHY_DCR_BYTEMASK_SHIFT (10U)
#define DDRPHY_DCR_BYTEMASK_SET(x) (((uint32_t)(x) << DDRPHY_DCR_BYTEMASK_SHIFT) & DDRPHY_DCR_BYTEMASK_MASK)
#define DDRPHY_DCR_BYTEMASK_GET(x) (((uint32_t)(x) & DDRPHY_DCR_BYTEMASK_MASK) >> DDRPHY_DCR_BYTEMASK_SHIFT)

/*
 * MPRDQ (R/W)
 *
 * Multi-Purpose Register (MPR) DQ (DDR3 Only): Specifies the value that is driven on non-primary DQ pins during MPR reads. Valid values are:
 * 0 = Primary DQ drives out the data from MPR (0-1-0-1); non-primary DQs drive ‘0’ 1 = Primary DQ and non-primary DQs all drive the same data from MPR (0-1-0-1)
 */
#define DDRPHY_DCR_MPRDQ_MASK (0x80U)
#define DDRPHY_DCR_MPRDQ_SHIFT (7U)
#define DDRPHY_DCR_MPRDQ_SET(x) (((uint32_t)(x) << DDRPHY_DCR_MPRDQ_SHIFT) & DDRPHY_DCR_MPRDQ_MASK)
#define DDRPHY_DCR_MPRDQ_GET(x) (((uint32_t)(x) & DDRPHY_DCR_MPRDQ_MASK) >> DDRPHY_DCR_MPRDQ_SHIFT)

/*
 * PDQ (R/W)
 *
 * Primary DQ (DDR3 Only): Specifies the DQ pin in a byte that is designated as a primary pin for Multi-Purpose Register (MPR) reads. Valid values are 0 to 7 for DQ[0] to DQ[7], respectively.
 */
#define DDRPHY_DCR_PDQ_MASK (0x70U)
#define DDRPHY_DCR_PDQ_SHIFT (4U)
#define DDRPHY_DCR_PDQ_SET(x) (((uint32_t)(x) << DDRPHY_DCR_PDQ_SHIFT) & DDRPHY_DCR_PDQ_MASK)
#define DDRPHY_DCR_PDQ_GET(x) (((uint32_t)(x) & DDRPHY_DCR_PDQ_MASK) >> DDRPHY_DCR_PDQ_SHIFT)

/*
 * DDR8BNK (R/W)
 *
 * DDR 8-Bank: Indicates, if set, that the SDRAM used has 8 banks. tRPA = tRP+1 and tFAW are used for 8-bank DRAMs, otherwise tRPA = tRP and no tFAW is used.
 * Note that a setting of 1 for DRAMs that have fewer than 8 banks results in correct functionality, but less tight DRAM command spacing for the parameters.
 */
#define DDRPHY_DCR_DDR8BNK_MASK (0x8U)
#define DDRPHY_DCR_DDR8BNK_SHIFT (3U)
#define DDRPHY_DCR_DDR8BNK_SET(x) (((uint32_t)(x) << DDRPHY_DCR_DDR8BNK_SHIFT) & DDRPHY_DCR_DDR8BNK_MASK)
#define DDRPHY_DCR_DDR8BNK_GET(x) (((uint32_t)(x) & DDRPHY_DCR_DDR8BNK_MASK) >> DDRPHY_DCR_DDR8BNK_SHIFT)

/*
 * DDRMD (R/W)
 *
 * DDR Mode: SDRAM DDR mode. Valid values are: 000 = Reserved
 * 001 = Reserved
 * 010 = DDR2
 * 011 = DDR3
 * 100 – 111 = Reserved
 */
#define DDRPHY_DCR_DDRMD_MASK (0x7U)
#define DDRPHY_DCR_DDRMD_SHIFT (0U)
#define DDRPHY_DCR_DDRMD_SET(x) (((uint32_t)(x) << DDRPHY_DCR_DDRMD_SHIFT) & DDRPHY_DCR_DDRMD_MASK)
#define DDRPHY_DCR_DDRMD_GET(x) (((uint32_t)(x) & DDRPHY_DCR_DDRMD_MASK) >> DDRPHY_DCR_DDRMD_SHIFT)

/* Bitfield definition for register: DTPR0 */
/*
 * TRC (R/W)
 *
 * Activate to activate command delay (same bank). Valid values are 2 to 63.
 */
#define DDRPHY_DTPR0_TRC_MASK (0xFC000000UL)
#define DDRPHY_DTPR0_TRC_SHIFT (26U)
#define DDRPHY_DTPR0_TRC_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRC_SHIFT) & DDRPHY_DTPR0_TRC_MASK)
#define DDRPHY_DTPR0_TRC_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRC_MASK) >> DDRPHY_DTPR0_TRC_SHIFT)

/*
 * TRRD (R/W)
 *
 * Activate to activate command delay (different banks). Valid values are 1 to 15.
 */
#define DDRPHY_DTPR0_TRRD_MASK (0x3C00000UL)
#define DDRPHY_DTPR0_TRRD_SHIFT (22U)
#define DDRPHY_DTPR0_TRRD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRRD_SHIFT) & DDRPHY_DTPR0_TRRD_MASK)
#define DDRPHY_DTPR0_TRRD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRRD_MASK) >> DDRPHY_DTPR0_TRRD_SHIFT)

/*
 * TRAS (R/W)
 *
 * Activate to precharge command delay. Valid values are 2 to 63.
 */
#define DDRPHY_DTPR0_TRAS_MASK (0x3F0000UL)
#define DDRPHY_DTPR0_TRAS_SHIFT (16U)
#define DDRPHY_DTPR0_TRAS_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRAS_SHIFT) & DDRPHY_DTPR0_TRAS_MASK)
#define DDRPHY_DTPR0_TRAS_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRAS_MASK) >> DDRPHY_DTPR0_TRAS_SHIFT)

/*
 * TRCD (R/W)
 *
 * Activate to read or write delay. Minimum time from when an activate command is issued to when a read or write to the activated row can be issued. Valid values are 2 to 15.
 */
#define DDRPHY_DTPR0_TRCD_MASK (0xF000U)
#define DDRPHY_DTPR0_TRCD_SHIFT (12U)
#define DDRPHY_DTPR0_TRCD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRCD_SHIFT) & DDRPHY_DTPR0_TRCD_MASK)
#define DDRPHY_DTPR0_TRCD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRCD_MASK) >> DDRPHY_DTPR0_TRCD_SHIFT)

/*
 * TRP (R/W)
 *
 * Precharge command period: The minimum time between a precharge command and any other command. Note that the Controller automatically derives tRPA for 8- bank DDR2 devices by adding 1 to tRP. Valid values are 2 to 15.
 */
#define DDRPHY_DTPR0_TRP_MASK (0xF00U)
#define DDRPHY_DTPR0_TRP_SHIFT (8U)
#define DDRPHY_DTPR0_TRP_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRP_SHIFT) & DDRPHY_DTPR0_TRP_MASK)
#define DDRPHY_DTPR0_TRP_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRP_MASK) >> DDRPHY_DTPR0_TRP_SHIFT)

/*
 * TWTR (R/W)
 *
 * Internal write to read command delay. Valid values are 1 to 15.
 */
#define DDRPHY_DTPR0_TWTR_MASK (0xF0U)
#define DDRPHY_DTPR0_TWTR_SHIFT (4U)
#define DDRPHY_DTPR0_TWTR_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TWTR_SHIFT) & DDRPHY_DTPR0_TWTR_MASK)
#define DDRPHY_DTPR0_TWTR_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TWTR_MASK) >> DDRPHY_DTPR0_TWTR_SHIFT)

/*
 * TRTP (R/W)
 *
 * Internal read to precharge command delay. Valid values are 2 to 15.
 */
#define DDRPHY_DTPR0_TRTP_MASK (0xFU)
#define DDRPHY_DTPR0_TRTP_SHIFT (0U)
#define DDRPHY_DTPR0_TRTP_SET(x) (((uint32_t)(x) << DDRPHY_DTPR0_TRTP_SHIFT) & DDRPHY_DTPR0_TRTP_MASK)
#define DDRPHY_DTPR0_TRTP_GET(x) (((uint32_t)(x) & DDRPHY_DTPR0_TRTP_MASK) >> DDRPHY_DTPR0_TRTP_SHIFT)

/* Bitfield definition for register: DTPR1 */
/*
 * TAOND_TAOFD (R/W)
 *
 * ODT turn-on/turn-off delays (DDR2 only). Valid values are: 00 = 2/2.5
 * 01 = 3/3.5
 * 10 = 4/4.5
 * 11 = 5/5.5
 * Most DDR2 devices utilize a fixed value of 2/2.5. For non-standard SDRAMs, the user must ensure that the operational Write Latency is always greater than or equal to the ODT turn-on delay. For example, a DDR2 SDRAM with CAS latency set to 3 and CAS additive latency set to 0 has a Write Latency of 2. Thus 2/2.5 can be used, but not 3/3.5 or higher.
 */
#define DDRPHY_DTPR1_TAOND_TAOFD_MASK (0xC0000000UL)
#define DDRPHY_DTPR1_TAOND_TAOFD_SHIFT (30U)
#define DDRPHY_DTPR1_TAOND_TAOFD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TAOND_TAOFD_SHIFT) & DDRPHY_DTPR1_TAOND_TAOFD_MASK)
#define DDRPHY_DTPR1_TAOND_TAOFD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TAOND_TAOFD_MASK) >> DDRPHY_DTPR1_TAOND_TAOFD_SHIFT)

/*
 * TWLO (R/W)
 *
 * Write leveling output delay: Number of clock cycles from when write leveling DQS is driven high by the control block to when the results from the SDRAM on DQ is sampled by the control block. This must include the SDRAM tWLO timing parameter plus the round trip delay from control block to SDRAM back to control block.
 */
#define DDRPHY_DTPR1_TWLO_MASK (0x3C000000UL)
#define DDRPHY_DTPR1_TWLO_SHIFT (26U)
#define DDRPHY_DTPR1_TWLO_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TWLO_SHIFT) & DDRPHY_DTPR1_TWLO_MASK)
#define DDRPHY_DTPR1_TWLO_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TWLO_MASK) >> DDRPHY_DTPR1_TWLO_SHIFT)

/*
 * TWLMRD (R/W)
 *
 * Minimum delay from when write leveling mode is programmed to the first DQS/DQS# rising edge.
 */
#define DDRPHY_DTPR1_TWLMRD_MASK (0x3F00000UL)
#define DDRPHY_DTPR1_TWLMRD_SHIFT (20U)
#define DDRPHY_DTPR1_TWLMRD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TWLMRD_SHIFT) & DDRPHY_DTPR1_TWLMRD_MASK)
#define DDRPHY_DTPR1_TWLMRD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TWLMRD_MASK) >> DDRPHY_DTPR1_TWLMRD_SHIFT)

/*
 * TRFC (R/W)
 *
 * Refresh-to-Refresh: Indicates the minimum time between two refresh commands or between a refresh and an active command. This is derived from the minimum refresh interval from the datasheet, tRFC(min), divided by the clock cycle time. The default number of clock cycles is for the largest JEDEC tRFC(min parameter value supported.
 */
#define DDRPHY_DTPR1_TRFC_MASK (0xFF800UL)
#define DDRPHY_DTPR1_TRFC_SHIFT (11U)
#define DDRPHY_DTPR1_TRFC_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TRFC_SHIFT) & DDRPHY_DTPR1_TRFC_MASK)
#define DDRPHY_DTPR1_TRFC_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TRFC_MASK) >> DDRPHY_DTPR1_TRFC_SHIFT)

/*
 * TFAW (R/W)
 *
 * 4-bank activate period. No more than 4-bank activate commands may be issued in a given tFAW period. Only applies to 8-bank devices. Valid values are 2 to 63.
 */
#define DDRPHY_DTPR1_TFAW_MASK (0x7E0U)
#define DDRPHY_DTPR1_TFAW_SHIFT (5U)
#define DDRPHY_DTPR1_TFAW_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TFAW_SHIFT) & DDRPHY_DTPR1_TFAW_MASK)
#define DDRPHY_DTPR1_TFAW_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TFAW_MASK) >> DDRPHY_DTPR1_TFAW_SHIFT)

/*
 * TMOD (R/W)
 *
 * Load mode update delay (DDR3 only). The minimum time between a load mode register command and a non-load mode register command. Valid values are: 000 = 12
 * 001 = 13
 * 010 = 14
 * 011 = 15
 * 100 = 16
 * 101 = 17
 * 110 – 111 = Reserved
 */
#define DDRPHY_DTPR1_TMOD_MASK (0x1CU)
#define DDRPHY_DTPR1_TMOD_SHIFT (2U)
#define DDRPHY_DTPR1_TMOD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TMOD_SHIFT) & DDRPHY_DTPR1_TMOD_MASK)
#define DDRPHY_DTPR1_TMOD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TMOD_MASK) >> DDRPHY_DTPR1_TMOD_SHIFT)

/*
 * TMRD (R/W)
 *
 * Load mode cycle time: The minimum time between a load mode register command and any other command. For DDR3 this is the minimum time between two load mode register commands. Valid values for DDR2 are 2 to 3. For DDR3, the value used for tMRD is 4 plus the value programmed in these bits, i.e. tMRD value for DDR3 ranges from 4 to 7.
 */
#define DDRPHY_DTPR1_TMRD_MASK (0x3U)
#define DDRPHY_DTPR1_TMRD_SHIFT (0U)
#define DDRPHY_DTPR1_TMRD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR1_TMRD_SHIFT) & DDRPHY_DTPR1_TMRD_MASK)
#define DDRPHY_DTPR1_TMRD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR1_TMRD_MASK) >> DDRPHY_DTPR1_TMRD_SHIFT)

/* Bitfield definition for register: DTPR2 */
/*
 * TCCD (R/W)
 *
 * Read to read and write to write command delay. Valid values are: 0 = BL/2 for DDR2 and 4 for DDR3
 * 1 = BL/2 + 1 for DDR2 and 5 for DDR3
 */
#define DDRPHY_DTPR2_TCCD_MASK (0x80000000UL)
#define DDRPHY_DTPR2_TCCD_SHIFT (31U)
#define DDRPHY_DTPR2_TCCD_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TCCD_SHIFT) & DDRPHY_DTPR2_TCCD_MASK)
#define DDRPHY_DTPR2_TCCD_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TCCD_MASK) >> DDRPHY_DTPR2_TCCD_SHIFT)

/*
 * TRTW (R/W)
 *
 * Read to Write command delay. Valid values are:
 * 0 = standard bus turn around delay
 * 1 = add 1 clock to standard bus turn around delay
 * This parameter allows the user to increase the delay between issuing Write commands to the SDRAM when preceded by Read commands. This provides an option to increase bus turn-around margin for high frequency systems.
 */
#define DDRPHY_DTPR2_TRTW_MASK (0x40000000UL)
#define DDRPHY_DTPR2_TRTW_SHIFT (30U)
#define DDRPHY_DTPR2_TRTW_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TRTW_SHIFT) & DDRPHY_DTPR2_TRTW_MASK)
#define DDRPHY_DTPR2_TRTW_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TRTW_MASK) >> DDRPHY_DTPR2_TRTW_SHIFT)

/*
 * TRTODT (R/W)
 *
 * Read to ODT delay (DDR3 only). Specifies whether ODT can be enabled immediately after the read post-amble or one clock delay has to be added. Valid values are:
 * 0 = ODT may be turned on immediately after read post-amble
 * 1 = ODT may not be turned on until one clock after the read post-amble
 * If tRTODT is set to 1, then the read-to-write latency is increased by 1 if ODT is enabled.
 */
#define DDRPHY_DTPR2_TRTODT_MASK (0x20000000UL)
#define DDRPHY_DTPR2_TRTODT_SHIFT (29U)
#define DDRPHY_DTPR2_TRTODT_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TRTODT_SHIFT) & DDRPHY_DTPR2_TRTODT_MASK)
#define DDRPHY_DTPR2_TRTODT_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TRTODT_MASK) >> DDRPHY_DTPR2_TRTODT_SHIFT)

/*
 * TDLLK (R/W)
 *
 * DLL locking time. Valid values are 2 to 1023.
 */
#define DDRPHY_DTPR2_TDLLK_MASK (0x1FF80000UL)
#define DDRPHY_DTPR2_TDLLK_SHIFT (19U)
#define DDRPHY_DTPR2_TDLLK_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TDLLK_SHIFT) & DDRPHY_DTPR2_TDLLK_MASK)
#define DDRPHY_DTPR2_TDLLK_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TDLLK_MASK) >> DDRPHY_DTPR2_TDLLK_SHIFT)

/*
 * TCKE (R/W)
 *
 * CKE minimum pulse width. Also specifies the minimum time that the SDRAM must remain in power down or self refresh mode. For DDR3 this parameter must be set to the value of tCKESR which is usually bigger than the value of tCKE. Valid values are 2 to 15.
 */
#define DDRPHY_DTPR2_TCKE_MASK (0x78000UL)
#define DDRPHY_DTPR2_TCKE_SHIFT (15U)
#define DDRPHY_DTPR2_TCKE_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TCKE_SHIFT) & DDRPHY_DTPR2_TCKE_MASK)
#define DDRPHY_DTPR2_TCKE_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TCKE_MASK) >> DDRPHY_DTPR2_TCKE_SHIFT)

/*
 * TXP (R/W)
 *
 * Power down exit delay. The minimum time between a power down exit command and any other command. This parameter must be set to the maximum of the various minimum power down exit delay parameters specified in the SDRAM datasheet, i.e. max(tXP, tXARD, tXARDS) for DDR2 and max(tXP, tXPDLL) for DDR3. Valid values are 2 to 31.
 */
#define DDRPHY_DTPR2_TXP_MASK (0x7C00U)
#define DDRPHY_DTPR2_TXP_SHIFT (10U)
#define DDRPHY_DTPR2_TXP_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TXP_SHIFT) & DDRPHY_DTPR2_TXP_MASK)
#define DDRPHY_DTPR2_TXP_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TXP_MASK) >> DDRPHY_DTPR2_TXP_SHIFT)

/*
 * TXS (R/W)
 *
 * Self refresh exit delay. The minimum time between a self refresh exit command and any other command. This parameter must be set to the maximum of the various minimum self refresh exit delay parameters specified in the SDRAM datasheet, i.e. max(tXSNR, tXSRD) for DDR2 and max(tXS, tXSDLL) for DDR3. Valid values are 2 to 1023.
 */
#define DDRPHY_DTPR2_TXS_MASK (0x3FFU)
#define DDRPHY_DTPR2_TXS_SHIFT (0U)
#define DDRPHY_DTPR2_TXS_SET(x) (((uint32_t)(x) << DDRPHY_DTPR2_TXS_SHIFT) & DDRPHY_DTPR2_TXS_MASK)
#define DDRPHY_DTPR2_TXS_GET(x) (((uint32_t)(x) & DDRPHY_DTPR2_TXS_MASK) >> DDRPHY_DTPR2_TXS_SHIFT)

/* Bitfield definition for register: MR0 */
/*
 * PD (R/W)
 *
 * Power-Down Control: Controls the exit time for power-down modes. Refer to the SDRAM datasheet for details on power-down modes. Valid values are:
 * 0 = Slow exit (DLL off) 1 = Fast exit (DLL on)
 */
#define DDRPHY_MR0_PD_MASK (0x1000U)
#define DDRPHY_MR0_PD_SHIFT (12U)
#define DDRPHY_MR0_PD_SET(x) (((uint32_t)(x) << DDRPHY_MR0_PD_SHIFT) & DDRPHY_MR0_PD_MASK)
#define DDRPHY_MR0_PD_GET(x) (((uint32_t)(x) & DDRPHY_MR0_PD_MASK) >> DDRPHY_MR0_PD_SHIFT)

/*
 * WR (R/W)
 *
 * Write Recovery: This is the value of the write recovery. It is calculated by dividing the datasheet write recovery time, tWR (ns) by the datasheet clock cycle time, tCK (ns) and rounding up a non-integer value to the next integer. Valid values are:
 * 000 = 16
 * 001 = 5
 * 010 = 6
 * 011 = 7
 * 100 = 8
 * 101 = 10
 * 110 = 12
 * 111 = 14
 * All other settings are reserved and should not be used.
 * NOTE: tWR (ns) is the time from the first SDRAM positive clock edge after the last data-in pair of a write command, to when a precharge of the same bank can be issued.
 */
#define DDRPHY_MR0_WR_MASK (0xE00U)
#define DDRPHY_MR0_WR_SHIFT (9U)
#define DDRPHY_MR0_WR_SET(x) (((uint32_t)(x) << DDRPHY_MR0_WR_SHIFT) & DDRPHY_MR0_WR_MASK)
#define DDRPHY_MR0_WR_GET(x) (((uint32_t)(x) & DDRPHY_MR0_WR_MASK) >> DDRPHY_MR0_WR_SHIFT)

/*
 * DR (R/W)
 *
 * DLL Reset: Writing a ‘1’ to this bit will reset the SDRAM DLL. This bit is self- clearing, i.e. it returns back to ‘0’ after the DLL reset has been issued.
 */
#define DDRPHY_MR0_DR_MASK (0x100U)
#define DDRPHY_MR0_DR_SHIFT (8U)
#define DDRPHY_MR0_DR_SET(x) (((uint32_t)(x) << DDRPHY_MR0_DR_SHIFT) & DDRPHY_MR0_DR_MASK)
#define DDRPHY_MR0_DR_GET(x) (((uint32_t)(x) & DDRPHY_MR0_DR_MASK) >> DDRPHY_MR0_DR_SHIFT)

/*
 * TM (R/W)
 *
 * Operating Mode: Selects either normal operating mode (0) or test mode (1). Test mode is reserved for the manufacturer and should not be used.
 */
#define DDRPHY_MR0_TM_MASK (0x80U)
#define DDRPHY_MR0_TM_SHIFT (7U)
#define DDRPHY_MR0_TM_SET(x) (((uint32_t)(x) << DDRPHY_MR0_TM_SHIFT) & DDRPHY_MR0_TM_MASK)
#define DDRPHY_MR0_TM_GET(x) (((uint32_t)(x) & DDRPHY_MR0_TM_MASK) >> DDRPHY_MR0_TM_SHIFT)

/*
 * CLH (R/W)
 *
 * CAS Latency: The delay between when the SDRAM registers a read command to when data is available. Valid values are:
 * 0010 = 5
 * 0100 = 6
 * 0110 = 7
 * 1000 = 8
 * 1010 = 9
 * 1100 = 10
 * 1110 = 11
 * 0001 = 12
 * 0011 = 13
 * 0101 = 14
 * All other settings are reserved and should not be used.
 */
#define DDRPHY_MR0_CLH_MASK (0x70U)
#define DDRPHY_MR0_CLH_SHIFT (4U)
#define DDRPHY_MR0_CLH_SET(x) (((uint32_t)(x) << DDRPHY_MR0_CLH_SHIFT) & DDRPHY_MR0_CLH_MASK)
#define DDRPHY_MR0_CLH_GET(x) (((uint32_t)(x) & DDRPHY_MR0_CLH_MASK) >> DDRPHY_MR0_CLH_SHIFT)

/*
 * BT (R/W)
 *
 * Burst Type: Indicates whether a burst is sequential (0) or interleaved (1).
 */
#define DDRPHY_MR0_BT_MASK (0x8U)
#define DDRPHY_MR0_BT_SHIFT (3U)
#define DDRPHY_MR0_BT_SET(x) (((uint32_t)(x) << DDRPHY_MR0_BT_SHIFT) & DDRPHY_MR0_BT_MASK)
#define DDRPHY_MR0_BT_GET(x) (((uint32_t)(x) & DDRPHY_MR0_BT_MASK) >> DDRPHY_MR0_BT_SHIFT)

/*
 * CLL (R/W)
 *
 * CAS Latency low bit
 */
#define DDRPHY_MR0_CLL_MASK (0x4U)
#define DDRPHY_MR0_CLL_SHIFT (2U)
#define DDRPHY_MR0_CLL_SET(x) (((uint32_t)(x) << DDRPHY_MR0_CLL_SHIFT) & DDRPHY_MR0_CLL_MASK)
#define DDRPHY_MR0_CLL_GET(x) (((uint32_t)(x) & DDRPHY_MR0_CLL_MASK) >> DDRPHY_MR0_CLL_SHIFT)

/*
 * BL (R/W)
 *
 * Burst Length: Determines the maximum number of column locations that can be accessed during a given read or write command. Valid values are:
 * Valid values for DDR3 are: 00 = 8 (Fixed)
 * 01 = 4 or 8 (On the fly)
 * 10 = 4 (Fixed)
 * 11 = Reserved
 */
#define DDRPHY_MR0_BL_MASK (0x3U)
#define DDRPHY_MR0_BL_SHIFT (0U)
#define DDRPHY_MR0_BL_SET(x) (((uint32_t)(x) << DDRPHY_MR0_BL_SHIFT) & DDRPHY_MR0_BL_MASK)
#define DDRPHY_MR0_BL_GET(x) (((uint32_t)(x) & DDRPHY_MR0_BL_MASK) >> DDRPHY_MR0_BL_SHIFT)

/* Bitfield definition for register: MR */
/*
 * PD (R/W)
 *
 * Power-Down Control: Controls the exit time for power-down modes. Refer to the SDRAM datasheet for details on power-down modes. Valid values are:
 * 0 = Fast exit 1 = Slow exit
 */
#define DDRPHY_MR_PD_MASK (0x1000U)
#define DDRPHY_MR_PD_SHIFT (12U)
#define DDRPHY_MR_PD_SET(x) (((uint32_t)(x) << DDRPHY_MR_PD_SHIFT) & DDRPHY_MR_PD_MASK)
#define DDRPHY_MR_PD_GET(x) (((uint32_t)(x) & DDRPHY_MR_PD_MASK) >> DDRPHY_MR_PD_SHIFT)

/*
 * WR (R/W)
 *
 * Write Recovery: This is the value of the write recovery. It is calculated by dividing the datasheet write recovery time, tWR (ns) by the datasheet clock cycle time, tCK (ns) and rounding up a non-integer value to the next integer. Valid values are:
 * 001 = 2
 * 010 = 3
 * 011 = 4
 * 100 = 5
 * 101 = 6
 * All other settings are reserved and should not be used.
 * NOTE: tWR (ns) is the time from the first SDRAM positive clock edge after the last data-in pair of a write command, to when a precharge of the same bank can be issued.
 */
#define DDRPHY_MR_WR_MASK (0xE00U)
#define DDRPHY_MR_WR_SHIFT (9U)
#define DDRPHY_MR_WR_SET(x) (((uint32_t)(x) << DDRPHY_MR_WR_SHIFT) & DDRPHY_MR_WR_MASK)
#define DDRPHY_MR_WR_GET(x) (((uint32_t)(x) & DDRPHY_MR_WR_MASK) >> DDRPHY_MR_WR_SHIFT)

/*
 * DR (R/W)
 *
 * DLL Reset: Writing a ‘1’ to this bit will reset the SDRAM DLL. This bit is self- clearing, i.e. it returns back to ‘0’ after the DLL reset has been issued.
 */
#define DDRPHY_MR_DR_MASK (0x100U)
#define DDRPHY_MR_DR_SHIFT (8U)
#define DDRPHY_MR_DR_SET(x) (((uint32_t)(x) << DDRPHY_MR_DR_SHIFT) & DDRPHY_MR_DR_MASK)
#define DDRPHY_MR_DR_GET(x) (((uint32_t)(x) & DDRPHY_MR_DR_MASK) >> DDRPHY_MR_DR_SHIFT)

/*
 * TM (R/W)
 *
 * Operating Mode: Selects either normal operating mode (0) or test mode (1). Test mode is reserved for the manufacturer and should not be used.
 */
#define DDRPHY_MR_TM_MASK (0x80U)
#define DDRPHY_MR_TM_SHIFT (7U)
#define DDRPHY_MR_TM_SET(x) (((uint32_t)(x) << DDRPHY_MR_TM_SHIFT) & DDRPHY_MR_TM_MASK)
#define DDRPHY_MR_TM_GET(x) (((uint32_t)(x) & DDRPHY_MR_TM_MASK) >> DDRPHY_MR_TM_SHIFT)

/*
 * CL (R/W)
 *
 * CAS Latency: The delay between when the SDRAM registers a read command to when data is available. Valid values are:
 * 010 = 2
 * 011 = 3
 * 100 = 4
 * 101 = 5
 * 110 = 6
 * 111 = 7
 * All other settings are reserved and should not be used.
 */
#define DDRPHY_MR_CL_MASK (0x70U)
#define DDRPHY_MR_CL_SHIFT (4U)
#define DDRPHY_MR_CL_SET(x) (((uint32_t)(x) << DDRPHY_MR_CL_SHIFT) & DDRPHY_MR_CL_MASK)
#define DDRPHY_MR_CL_GET(x) (((uint32_t)(x) & DDRPHY_MR_CL_MASK) >> DDRPHY_MR_CL_SHIFT)

/*
 * BT (R/W)
 *
 * Burst Type: Indicates whether a burst is sequential (0) or interleaved (1).
 */
#define DDRPHY_MR_BT_MASK (0x8U)
#define DDRPHY_MR_BT_SHIFT (3U)
#define DDRPHY_MR_BT_SET(x) (((uint32_t)(x) << DDRPHY_MR_BT_SHIFT) & DDRPHY_MR_BT_MASK)
#define DDRPHY_MR_BT_GET(x) (((uint32_t)(x) & DDRPHY_MR_BT_MASK) >> DDRPHY_MR_BT_SHIFT)

/*
 * BL (R/W)
 *
 * Burst Length: Determines the maximum number of column locations that can be accessed during a given read or write command. Valid values are:
 * 010 = 4
 * 011 = 8
 * All other settings are reserved and should not be used.
 */
#define DDRPHY_MR_BL_MASK (0x7U)
#define DDRPHY_MR_BL_SHIFT (0U)
#define DDRPHY_MR_BL_SET(x) (((uint32_t)(x) << DDRPHY_MR_BL_SHIFT) & DDRPHY_MR_BL_MASK)
#define DDRPHY_MR_BL_GET(x) (((uint32_t)(x) & DDRPHY_MR_BL_MASK) >> DDRPHY_MR_BL_SHIFT)

/* Bitfield definition for register: MR1 */
/*
 * QOFF (R/W)
 *
 * Output Enable/Disable: When ‘0’, all outputs function normal; when ‘1’ all SDRAM outputs are disabled removing output buffer current. This feature is intended to be used for IDD characterization of read current and should not be used in normal operation.
 */
#define DDRPHY_MR1_QOFF_MASK (0x1000U)
#define DDRPHY_MR1_QOFF_SHIFT (12U)
#define DDRPHY_MR1_QOFF_SET(x) (((uint32_t)(x) << DDRPHY_MR1_QOFF_SHIFT) & DDRPHY_MR1_QOFF_MASK)
#define DDRPHY_MR1_QOFF_GET(x) (((uint32_t)(x) & DDRPHY_MR1_QOFF_MASK) >> DDRPHY_MR1_QOFF_SHIFT)

/*
 * TDQS (R/W)
 *
 * Termination Data Strobe: When enabled (‘1’) TDQS provides additional termination resistance outputs that may be useful in some system configurations. Refer to the SDRAM datasheet for details.
 */
#define DDRPHY_MR1_TDQS_MASK (0x800U)
#define DDRPHY_MR1_TDQS_SHIFT (11U)
#define DDRPHY_MR1_TDQS_SET(x) (((uint32_t)(x) << DDRPHY_MR1_TDQS_SHIFT) & DDRPHY_MR1_TDQS_MASK)
#define DDRPHY_MR1_TDQS_GET(x) (((uint32_t)(x) & DDRPHY_MR1_TDQS_MASK) >> DDRPHY_MR1_TDQS_SHIFT)

/*
 * RTTH (R/W)
 *
 * On Die Termination high bit
 */
#define DDRPHY_MR1_RTTH_MASK (0x200U)
#define DDRPHY_MR1_RTTH_SHIFT (9U)
#define DDRPHY_MR1_RTTH_SET(x) (((uint32_t)(x) << DDRPHY_MR1_RTTH_SHIFT) & DDRPHY_MR1_RTTH_MASK)
#define DDRPHY_MR1_RTTH_GET(x) (((uint32_t)(x) & DDRPHY_MR1_RTTH_MASK) >> DDRPHY_MR1_RTTH_SHIFT)

/*
 * LEVEL (R/W)
 *
 * Write Leveling Enable: Enables write-leveling when set.
 */
#define DDRPHY_MR1_LEVEL_MASK (0x80U)
#define DDRPHY_MR1_LEVEL_SHIFT (7U)
#define DDRPHY_MR1_LEVEL_SET(x) (((uint32_t)(x) << DDRPHY_MR1_LEVEL_SHIFT) & DDRPHY_MR1_LEVEL_MASK)
#define DDRPHY_MR1_LEVEL_GET(x) (((uint32_t)(x) & DDRPHY_MR1_LEVEL_MASK) >> DDRPHY_MR1_LEVEL_SHIFT)

/*
 * RTTM (R/W)
 *
 * On Die Termination mid bit:
 * Selects the effective resistance for SDRAM on die termination. Valid values are:
 * 000 = ODT disabled 001 = RZQ/4
 * 010 = RZQ/2
 * 011 = RZQ/6
 * 100 = RZQ/12
 * 101 = RZQ/8
 * All other settings are reserved and should not be used.
 * Bit on [9, 6,2]
 */
#define DDRPHY_MR1_RTTM_MASK (0x40U)
#define DDRPHY_MR1_RTTM_SHIFT (6U)
#define DDRPHY_MR1_RTTM_SET(x) (((uint32_t)(x) << DDRPHY_MR1_RTTM_SHIFT) & DDRPHY_MR1_RTTM_MASK)
#define DDRPHY_MR1_RTTM_GET(x) (((uint32_t)(x) & DDRPHY_MR1_RTTM_MASK) >> DDRPHY_MR1_RTTM_SHIFT)

/*
 * DICH (R/W)
 *
 * Output Driver Impedance Control high bit:
 * Controls the output drive strength. Valid values are:
 * 00 = RZQ/6
 * 01 = RZQ7
 * 10 = Reserved
 * 11 = Reserved
 */
#define DDRPHY_MR1_DICH_MASK (0x20U)
#define DDRPHY_MR1_DICH_SHIFT (5U)
#define DDRPHY_MR1_DICH_SET(x) (((uint32_t)(x) << DDRPHY_MR1_DICH_SHIFT) & DDRPHY_MR1_DICH_MASK)
#define DDRPHY_MR1_DICH_GET(x) (((uint32_t)(x) & DDRPHY_MR1_DICH_MASK) >> DDRPHY_MR1_DICH_SHIFT)

/*
 * AL (R/W)
 *
 * Posted CAS Additive Latency: Setting additive latency that allows read and write commands to be issued to the SDRAM earlier than normal (refer to the SDRAM datasheet for details). Valid values are:
 * 00 = 0 (AL disabled)
 * 01 = CL - 1
 * 10 = CL - 2
 * 11 = Reserved
 */
#define DDRPHY_MR1_AL_MASK (0x18U)
#define DDRPHY_MR1_AL_SHIFT (3U)
#define DDRPHY_MR1_AL_SET(x) (((uint32_t)(x) << DDRPHY_MR1_AL_SHIFT) & DDRPHY_MR1_AL_MASK)
#define DDRPHY_MR1_AL_GET(x) (((uint32_t)(x) & DDRPHY_MR1_AL_MASK) >> DDRPHY_MR1_AL_SHIFT)

/*
 * RTTL (R/W)
 *
 * On Die Termination low bit
 */
#define DDRPHY_MR1_RTTL_MASK (0x4U)
#define DDRPHY_MR1_RTTL_SHIFT (2U)
#define DDRPHY_MR1_RTTL_SET(x) (((uint32_t)(x) << DDRPHY_MR1_RTTL_SHIFT) & DDRPHY_MR1_RTTL_MASK)
#define DDRPHY_MR1_RTTL_GET(x) (((uint32_t)(x) & DDRPHY_MR1_RTTL_MASK) >> DDRPHY_MR1_RTTL_SHIFT)

/*
 * DICL (R/W)
 *
 * Output Driver Impedance Control low bit
 */
#define DDRPHY_MR1_DICL_MASK (0x2U)
#define DDRPHY_MR1_DICL_SHIFT (1U)
#define DDRPHY_MR1_DICL_SET(x) (((uint32_t)(x) << DDRPHY_MR1_DICL_SHIFT) & DDRPHY_MR1_DICL_MASK)
#define DDRPHY_MR1_DICL_GET(x) (((uint32_t)(x) & DDRPHY_MR1_DICL_MASK) >> DDRPHY_MR1_DICL_SHIFT)

/*
 * DE (R/W)
 *
 * DLL Enable/Disable: Enable (0) or disable (1) the DLL. DLL must be enabled for normal operation.
 * Note: SDRAM DLL off mode is not supported
 */
#define DDRPHY_MR1_DE_MASK (0x1U)
#define DDRPHY_MR1_DE_SHIFT (0U)
#define DDRPHY_MR1_DE_SET(x) (((uint32_t)(x) << DDRPHY_MR1_DE_SHIFT) & DDRPHY_MR1_DE_MASK)
#define DDRPHY_MR1_DE_GET(x) (((uint32_t)(x) & DDRPHY_MR1_DE_MASK) >> DDRPHY_MR1_DE_SHIFT)

/* Bitfield definition for register: EMR */
/*
 * QOFF (R/W)
 *
 * Output Enable/Disable: When ‘0’, all outputs function normal; when ‘1’ all SDRAM outputs are disabled removing output buffer current. This feature is intended to be
 * used for IDD characterization of read current and should not be used in normal operation.
 */
#define DDRPHY_EMR_QOFF_MASK (0x1000U)
#define DDRPHY_EMR_QOFF_SHIFT (12U)
#define DDRPHY_EMR_QOFF_SET(x) (((uint32_t)(x) << DDRPHY_EMR_QOFF_SHIFT) & DDRPHY_EMR_QOFF_MASK)
#define DDRPHY_EMR_QOFF_GET(x) (((uint32_t)(x) & DDRPHY_EMR_QOFF_MASK) >> DDRPHY_EMR_QOFF_SHIFT)

/*
 * RDQS (R/W)
 *
 * RDQS Enable/Disable: When enabled (‘1’), RDQS is identical in function and timing to data strobe DQS during a read, and ignored during a write. A ‘0’ disables the SDRAM from driving RDQS. The Controller does not allow the user to change this bit.
 */
#define DDRPHY_EMR_RDQS_MASK (0x800U)
#define DDRPHY_EMR_RDQS_SHIFT (11U)
#define DDRPHY_EMR_RDQS_SET(x) (((uint32_t)(x) << DDRPHY_EMR_RDQS_SHIFT) & DDRPHY_EMR_RDQS_MASK)
#define DDRPHY_EMR_RDQS_GET(x) (((uint32_t)(x) & DDRPHY_EMR_RDQS_MASK) >> DDRPHY_EMR_RDQS_SHIFT)

/*
 * DQS (R/W)
 *
 * DQS_b Enable/Disable: When ‘0’, DQS_b is the complement of the differential data strobe pair DQS/DQS_b. When ‘1’, DQS is used in a single-ended mode and the DQS_b pin is disabled. Also used to similarly enable/disable RDQS_b if RDQS is enabled. The Controller does not allow the user to change this bit.
 */
#define DDRPHY_EMR_DQS_MASK (0x400U)
#define DDRPHY_EMR_DQS_SHIFT (10U)
#define DDRPHY_EMR_DQS_SET(x) (((uint32_t)(x) << DDRPHY_EMR_DQS_SHIFT) & DDRPHY_EMR_DQS_MASK)
#define DDRPHY_EMR_DQS_GET(x) (((uint32_t)(x) & DDRPHY_EMR_DQS_MASK) >> DDRPHY_EMR_DQS_SHIFT)

/*
 * OCD (R/W)
 *
 * Off-Chip Driver (OCD) Impedance Calibration: Used to calibrate and match pull-up to pull- down impedance to 18  nominal (refer to the SDRAM datasheet for details). Valid values are:
 * 000 = OCD calibration mode exit 001 = Drive (1) pull-up
 * 010 = Drive (0) pull-down
 * 100 = OCD enter adjust mode 111 = OCD calibration default
 * All other settings are reserved and should not be used. Note that OCD is not supported by all vendors. Refer to the SDRAM datasheet for details on the recommended OCD settings.
 */
#define DDRPHY_EMR_OCD_MASK (0x380U)
#define DDRPHY_EMR_OCD_SHIFT (7U)
#define DDRPHY_EMR_OCD_SET(x) (((uint32_t)(x) << DDRPHY_EMR_OCD_SHIFT) & DDRPHY_EMR_OCD_MASK)
#define DDRPHY_EMR_OCD_GET(x) (((uint32_t)(x) & DDRPHY_EMR_OCD_MASK) >> DDRPHY_EMR_OCD_SHIFT)

/*
 * RTTH (R/W)
 *
 * On Die Termination high bit:
 * Selects the effective resistance for SDRAM on die termination. Valid values are:
 * 00 = ODT disabled 01 = 75
 * 10 = 150
 * 11 = 50 (some vendors)
 */
#define DDRPHY_EMR_RTTH_MASK (0x40U)
#define DDRPHY_EMR_RTTH_SHIFT (6U)
#define DDRPHY_EMR_RTTH_SET(x) (((uint32_t)(x) << DDRPHY_EMR_RTTH_SHIFT) & DDRPHY_EMR_RTTH_MASK)
#define DDRPHY_EMR_RTTH_GET(x) (((uint32_t)(x) & DDRPHY_EMR_RTTH_MASK) >> DDRPHY_EMR_RTTH_SHIFT)

/*
 * AL (R/W)
 *
 * Posted CAS Additive Latency: Setting additive latency that allows read and write commands to be issued to the SDRAM earlier than normal (refer to the SDRAM datasheet for details). Valid values are:
 * 000 = 0
 * 001 = 1
 * 010 = 2
 * 011 = 3
 * 100 = 4
 * 101 = 5
 * All other settings are reserved and should not be used. The maximum allowed value of AL is tRCD-1.
 */
#define DDRPHY_EMR_AL_MASK (0x38U)
#define DDRPHY_EMR_AL_SHIFT (3U)
#define DDRPHY_EMR_AL_SET(x) (((uint32_t)(x) << DDRPHY_EMR_AL_SHIFT) & DDRPHY_EMR_AL_MASK)
#define DDRPHY_EMR_AL_GET(x) (((uint32_t)(x) & DDRPHY_EMR_AL_MASK) >> DDRPHY_EMR_AL_SHIFT)

/*
 * RTTL (R/W)
 *
 * On Die Termination low bit:
 */
#define DDRPHY_EMR_RTTL_MASK (0x4U)
#define DDRPHY_EMR_RTTL_SHIFT (2U)
#define DDRPHY_EMR_RTTL_SET(x) (((uint32_t)(x) << DDRPHY_EMR_RTTL_SHIFT) & DDRPHY_EMR_RTTL_MASK)
#define DDRPHY_EMR_RTTL_GET(x) (((uint32_t)(x) & DDRPHY_EMR_RTTL_MASK) >> DDRPHY_EMR_RTTL_SHIFT)

/*
 * DIC (R/W)
 *
 * Output Driver Impedance Control: Controls the output drive strength. Valid values are:
 * 0 = Full strength
 * 1 = Reduced strength
 */
#define DDRPHY_EMR_DIC_MASK (0x2U)
#define DDRPHY_EMR_DIC_SHIFT (1U)
#define DDRPHY_EMR_DIC_SET(x) (((uint32_t)(x) << DDRPHY_EMR_DIC_SHIFT) & DDRPHY_EMR_DIC_MASK)
#define DDRPHY_EMR_DIC_GET(x) (((uint32_t)(x) & DDRPHY_EMR_DIC_MASK) >> DDRPHY_EMR_DIC_SHIFT)

/*
 * DE (R/W)
 *
 * DLL Enable/Disable: Enable (0) or disable (1) the DLL. DLL must be enabled for normal operation.
 */
#define DDRPHY_EMR_DE_MASK (0x1U)
#define DDRPHY_EMR_DE_SHIFT (0U)
#define DDRPHY_EMR_DE_SET(x) (((uint32_t)(x) << DDRPHY_EMR_DE_SHIFT) & DDRPHY_EMR_DE_MASK)
#define DDRPHY_EMR_DE_GET(x) (((uint32_t)(x) & DDRPHY_EMR_DE_MASK) >> DDRPHY_EMR_DE_SHIFT)

/* Bitfield definition for register: MR2 */
/*
 * RTTWR (R/W)
 *
 * Dynamic ODT: Selects RTT for dynamic ODT. Valid values are: 00 = Dynamic ODT off
 * 01 = RZQ/4
 * 10 = RZQ/2
 * 11 = Reserved
 */
#define DDRPHY_MR2_RTTWR_MASK (0x600U)
#define DDRPHY_MR2_RTTWR_SHIFT (9U)
#define DDRPHY_MR2_RTTWR_SET(x) (((uint32_t)(x) << DDRPHY_MR2_RTTWR_SHIFT) & DDRPHY_MR2_RTTWR_MASK)
#define DDRPHY_MR2_RTTWR_GET(x) (((uint32_t)(x) & DDRPHY_MR2_RTTWR_MASK) >> DDRPHY_MR2_RTTWR_SHIFT)

/*
 * SRT (R/W)
 *
 * Self-Refresh Temperature Range: Selects either normal (‘0’) or extended (‘1’) operating temperature range during self-refresh.
 */
#define DDRPHY_MR2_SRT_MASK (0x80U)
#define DDRPHY_MR2_SRT_SHIFT (7U)
#define DDRPHY_MR2_SRT_SET(x) (((uint32_t)(x) << DDRPHY_MR2_SRT_SHIFT) & DDRPHY_MR2_SRT_MASK)
#define DDRPHY_MR2_SRT_GET(x) (((uint32_t)(x) & DDRPHY_MR2_SRT_MASK) >> DDRPHY_MR2_SRT_SHIFT)

/*
 * ASR (R/W)
 *
 * Auto Self-Refresh: When enabled (‘1’), SDRAM automatically provides self-refresh power management functions for all supported operating temperature values.
 * Otherwise the SRT bit must be programmed to indicate the temperature range.
 */
#define DDRPHY_MR2_ASR_MASK (0x40U)
#define DDRPHY_MR2_ASR_SHIFT (6U)
#define DDRPHY_MR2_ASR_SET(x) (((uint32_t)(x) << DDRPHY_MR2_ASR_SHIFT) & DDRPHY_MR2_ASR_MASK)
#define DDRPHY_MR2_ASR_GET(x) (((uint32_t)(x) & DDRPHY_MR2_ASR_MASK) >> DDRPHY_MR2_ASR_SHIFT)

/*
 * CWL (R/W)
 *
 * CAS Write Latency: The delay between when the SDRAM registers a write command to when write data is available. Valid values are:
 * 000 = 5 (tCK > 2.5ns)
 * 001 = 6 (2.5ns > tCK > 1.875ns)
 * 010 = 7 (1.875ns > tCK> 1.5ns)
 * 011 = 8 (1.5ns > tCK > 1.25ns)
 * 100 = 9 (1.25ns > tCK > 1.07ns)
 * 101 = 10 (1.07ns > tCK > 0.935ns)
 * 110 = 11 (0.935ns > tCK > 0.833ns)
 * 111 = 12 (0.833ns > tCK > 0.75ns)
 * All other settings are reserved and should not be used.
 */
#define DDRPHY_MR2_CWL_MASK (0x38U)
#define DDRPHY_MR2_CWL_SHIFT (3U)
#define DDRPHY_MR2_CWL_SET(x) (((uint32_t)(x) << DDRPHY_MR2_CWL_SHIFT) & DDRPHY_MR2_CWL_MASK)
#define DDRPHY_MR2_CWL_GET(x) (((uint32_t)(x) & DDRPHY_MR2_CWL_MASK) >> DDRPHY_MR2_CWL_SHIFT)

/*
 * PASR (R/W)
 *
 * Partial Array Self Refresh: Specifies that data located in areas of the array beyond the specified location will be lost if self refresh is entered.
 * Valid settings for 4 banks are:
 * 000 = Full Array
 * 001 = Half Array (BA[1:0] = 00 & 01)
 * 010 = Quarter Array (BA[1:0] = 00) 011 = Not defined
 * 100 = 3/4 Array (BA[1:0] = 01, 10, & 11)
 * 101 = Half Array (BA[1:0] = 10 & 11)
 * 110 = Quarter Array (BA[1:0] = 11) 111 = Not defined
 * Valid settings for 8 banks are:
 * 000 = Full Array
 * 001 = Half Array (BA[2:0] = 000, 001, 010 & 011)
 * 010 = Quarter Array (BA[2:0] = 000, 001) 011 = 1/8 Array (BA[2:0] = 000)
 * 100 = 3/4 Array (BA[2:0] = 010, 011, 100, 101, 110 & 111)
 * 101 = Half Array (BA[2:0] = 100, 101, 110 & 111)
 * 110 = Quarter Array (BA[2:0] = 110 & 111)
 * 111 = 1/8 Array (BA[2:0] 111)
 */
#define DDRPHY_MR2_PASR_MASK (0x7U)
#define DDRPHY_MR2_PASR_SHIFT (0U)
#define DDRPHY_MR2_PASR_SET(x) (((uint32_t)(x) << DDRPHY_MR2_PASR_SHIFT) & DDRPHY_MR2_PASR_MASK)
#define DDRPHY_MR2_PASR_GET(x) (((uint32_t)(x) & DDRPHY_MR2_PASR_MASK) >> DDRPHY_MR2_PASR_SHIFT)

/* Bitfield definition for register: EMR2 */
/*
 * SRF (R/W)
 *
 * Self Refresh Rate: Enables, if set, high temperature self refresh rate.
 */
#define DDRPHY_EMR2_SRF_MASK (0x80U)
#define DDRPHY_EMR2_SRF_SHIFT (7U)
#define DDRPHY_EMR2_SRF_SET(x) (((uint32_t)(x) << DDRPHY_EMR2_SRF_SHIFT) & DDRPHY_EMR2_SRF_MASK)
#define DDRPHY_EMR2_SRF_GET(x) (((uint32_t)(x) & DDRPHY_EMR2_SRF_MASK) >> DDRPHY_EMR2_SRF_SHIFT)

/*
 * DCC (R/W)
 *
 * Duty Cycle Corrector: Enables, if set, duty cycle correction within SDRAM.
 */
#define DDRPHY_EMR2_DCC_MASK (0x8U)
#define DDRPHY_EMR2_DCC_SHIFT (3U)
#define DDRPHY_EMR2_DCC_SET(x) (((uint32_t)(x) << DDRPHY_EMR2_DCC_SHIFT) & DDRPHY_EMR2_DCC_MASK)
#define DDRPHY_EMR2_DCC_GET(x) (((uint32_t)(x) & DDRPHY_EMR2_DCC_MASK) >> DDRPHY_EMR2_DCC_SHIFT)

/*
 * PASR (R/W)
 *
 * Partial Array Self Refresh: Specifies that data located in areas of the array beyond the specified location will be lost if self refresh is entered.
 * Valid settings for 4 banks are:
 * 000 = Full Array
 * 001 = Half Array (BA[1:0] = 00 & 01)
 * 010 = Quarter Array (BA[1:0] = 00) 011 = Not defined
 * 100 = 3/4 Array (BA[1:0] = 01, 10, & 11)
 * 101 = Half Array (BA[1:0] = 10 & 11)
 * 110 = Quarter Array (BA[1:0] = 11) 111 = Not defined
 * Valid settings for 8 banks are:
 * 000 = Full Array
 * 001 = Half Array (BA[2:0] = 000, 001, 010 & 011)
 * 010 = Quarter Array (BA[2:0] = 000, 001) 011 = 1/8 Array (BA[2:0] = 000)
 * 100 = 3/4 Array (BA[2:0] = 010, 011, 100, 101, 110 & 111)
 * 101 = Half Array (BA[2:0] = 100, 101, 110 & 111)
 * 110 = Quarter Array (BA[2:0] = 110 & 111)
 * 111 = 1/8 Array (BA[2:0] 111)
 */
#define DDRPHY_EMR2_PASR_MASK (0x7U)
#define DDRPHY_EMR2_PASR_SHIFT (0U)
#define DDRPHY_EMR2_PASR_SET(x) (((uint32_t)(x) << DDRPHY_EMR2_PASR_SHIFT) & DDRPHY_EMR2_PASR_MASK)
#define DDRPHY_EMR2_PASR_GET(x) (((uint32_t)(x) & DDRPHY_EMR2_PASR_MASK) >> DDRPHY_EMR2_PASR_SHIFT)

/* Bitfield definition for register: MR3 */
/*
 * MPR (R/W)
 *
 * Multi-Purpose Register Enable: Enables, if set, that read data should come from the Multi-Purpose Register. Otherwise read data come from the DRAM array.
 */
#define DDRPHY_MR3_MPR_MASK (0x4U)
#define DDRPHY_MR3_MPR_SHIFT (2U)
#define DDRPHY_MR3_MPR_SET(x) (((uint32_t)(x) << DDRPHY_MR3_MPR_SHIFT) & DDRPHY_MR3_MPR_MASK)
#define DDRPHY_MR3_MPR_GET(x) (((uint32_t)(x) & DDRPHY_MR3_MPR_MASK) >> DDRPHY_MR3_MPR_SHIFT)

/*
 * MPRLOC (R/W)
 *
 * Multi-Purpose Register (MPR) Location: Selects MPR data location: Valid value are: 00 = Predefined pattern for system calibration
 * All other settings are reserved and should not be used.
 */
#define DDRPHY_MR3_MPRLOC_MASK (0x3U)
#define DDRPHY_MR3_MPRLOC_SHIFT (0U)
#define DDRPHY_MR3_MPRLOC_SET(x) (((uint32_t)(x) << DDRPHY_MR3_MPRLOC_SHIFT) & DDRPHY_MR3_MPRLOC_MASK)
#define DDRPHY_MR3_MPRLOC_GET(x) (((uint32_t)(x) & DDRPHY_MR3_MPRLOC_MASK) >> DDRPHY_MR3_MPRLOC_SHIFT)

/* Bitfield definition for register: EMR3 */
/* Bitfield definition for register: ODTCR */
/*
 * WRODT3 (R/W)
 *
 */
#define DDRPHY_ODTCR_WRODT3_MASK (0xF0000000UL)
#define DDRPHY_ODTCR_WRODT3_SHIFT (28U)
#define DDRPHY_ODTCR_WRODT3_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_WRODT3_SHIFT) & DDRPHY_ODTCR_WRODT3_MASK)
#define DDRPHY_ODTCR_WRODT3_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_WRODT3_MASK) >> DDRPHY_ODTCR_WRODT3_SHIFT)

/*
 * WRODT2 (R/W)
 *
 */
#define DDRPHY_ODTCR_WRODT2_MASK (0xF000000UL)
#define DDRPHY_ODTCR_WRODT2_SHIFT (24U)
#define DDRPHY_ODTCR_WRODT2_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_WRODT2_SHIFT) & DDRPHY_ODTCR_WRODT2_MASK)
#define DDRPHY_ODTCR_WRODT2_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_WRODT2_MASK) >> DDRPHY_ODTCR_WRODT2_SHIFT)

/*
 * WRODT1 (R/W)
 *
 */
#define DDRPHY_ODTCR_WRODT1_MASK (0xF00000UL)
#define DDRPHY_ODTCR_WRODT1_SHIFT (20U)
#define DDRPHY_ODTCR_WRODT1_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_WRODT1_SHIFT) & DDRPHY_ODTCR_WRODT1_MASK)
#define DDRPHY_ODTCR_WRODT1_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_WRODT1_MASK) >> DDRPHY_ODTCR_WRODT1_SHIFT)

/*
 * WRODT0 (R/W)
 *
 * Write ODT: Specifies whether ODT should be enabled (‘1’) or disabled (‘0’) on each of the up to four ranks when a write command is sent to rank n. WRODT0, WRODT1, WRODT2, and WRODT3 specify ODT settings when a write is to rank 0, rank 1, rank 2, and rank 3, respectively. The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3. Default is to enable ODT only on rank being written to.
 */
#define DDRPHY_ODTCR_WRODT0_MASK (0xF0000UL)
#define DDRPHY_ODTCR_WRODT0_SHIFT (16U)
#define DDRPHY_ODTCR_WRODT0_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_WRODT0_SHIFT) & DDRPHY_ODTCR_WRODT0_MASK)
#define DDRPHY_ODTCR_WRODT0_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_WRODT0_MASK) >> DDRPHY_ODTCR_WRODT0_SHIFT)

/*
 * RDODT3 (R/W)
 *
 */
#define DDRPHY_ODTCR_RDODT3_MASK (0xF000U)
#define DDRPHY_ODTCR_RDODT3_SHIFT (12U)
#define DDRPHY_ODTCR_RDODT3_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_RDODT3_SHIFT) & DDRPHY_ODTCR_RDODT3_MASK)
#define DDRPHY_ODTCR_RDODT3_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_RDODT3_MASK) >> DDRPHY_ODTCR_RDODT3_SHIFT)

/*
 * RDODT2 (R/W)
 *
 */
#define DDRPHY_ODTCR_RDODT2_MASK (0xF00U)
#define DDRPHY_ODTCR_RDODT2_SHIFT (8U)
#define DDRPHY_ODTCR_RDODT2_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_RDODT2_SHIFT) & DDRPHY_ODTCR_RDODT2_MASK)
#define DDRPHY_ODTCR_RDODT2_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_RDODT2_MASK) >> DDRPHY_ODTCR_RDODT2_SHIFT)

/*
 * RDODT1 (R/W)
 *
 */
#define DDRPHY_ODTCR_RDODT1_MASK (0xF0U)
#define DDRPHY_ODTCR_RDODT1_SHIFT (4U)
#define DDRPHY_ODTCR_RDODT1_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_RDODT1_SHIFT) & DDRPHY_ODTCR_RDODT1_MASK)
#define DDRPHY_ODTCR_RDODT1_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_RDODT1_MASK) >> DDRPHY_ODTCR_RDODT1_SHIFT)

/*
 * RDODT0 (R/W)
 *
 * Read ODT: Specifies whether ODT should be enabled (‘1’) or disabled (‘0’) on each of the up to four ranks when a read command is sent to rank n. RDODT0, RDODT1, RDODT2, and RDODT3 specify ODT settings when a read is to rank 0, rank 1, rank 2, and rank 3, respectively. The four bits of each field each represent a rank, the LSB being rank 0 and the MSB being rank 3. Default is to disable ODT during reads.
 */
#define DDRPHY_ODTCR_RDODT0_MASK (0xFU)
#define DDRPHY_ODTCR_RDODT0_SHIFT (0U)
#define DDRPHY_ODTCR_RDODT0_SET(x) (((uint32_t)(x) << DDRPHY_ODTCR_RDODT0_SHIFT) & DDRPHY_ODTCR_RDODT0_MASK)
#define DDRPHY_ODTCR_RDODT0_GET(x) (((uint32_t)(x) & DDRPHY_ODTCR_RDODT0_MASK) >> DDRPHY_ODTCR_RDODT0_SHIFT)

/* Bitfield definition for register: DTCR */
/*
 * RFSHDT (R/W)
 *
 * Refresh During Training: A non-zero value specifies that a burst of refreshes equal to the number specified in this field should be sent to the SDRAM after training each rank except the last rank.
 */
#define DDRPHY_DTCR_RFSHDT_MASK (0xF0000000UL)
#define DDRPHY_DTCR_RFSHDT_SHIFT (28U)
#define DDRPHY_DTCR_RFSHDT_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_RFSHDT_SHIFT) & DDRPHY_DTCR_RFSHDT_MASK)
#define DDRPHY_DTCR_RFSHDT_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_RFSHDT_MASK) >> DDRPHY_DTCR_RFSHDT_SHIFT)

/*
 * RANKEN (R/W)
 *
 * Rank Enable: Specifies the ranks that are enabled for data-training. Bit 0 controls rank 0, bit 1 controls rank 1, bit 2 controls rank 2, and bit 3 controls rank 3. Setting the bit to ‘1’ enables the rank, and setting it to ‘0’ disables the rank.
 */
#define DDRPHY_DTCR_RANKEN_MASK (0xF000000UL)
#define DDRPHY_DTCR_RANKEN_SHIFT (24U)
#define DDRPHY_DTCR_RANKEN_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_RANKEN_SHIFT) & DDRPHY_DTCR_RANKEN_MASK)
#define DDRPHY_DTCR_RANKEN_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_RANKEN_MASK) >> DDRPHY_DTCR_RANKEN_SHIFT)

/*
 * DTEXD (R/W)
 *
 * Data Training Extended Write DQS: Enables, if set, an extended write DQS whereby two additional pulses of DQS are added as post-amble to a burst of writes.
 * Generally this should only be enabled when running read bit deskew with the intention of performing read eye deskew prior to running write leveling adjustment.
 */
#define DDRPHY_DTCR_DTEXD_MASK (0x400000UL)
#define DDRPHY_DTCR_DTEXD_SHIFT (22U)
#define DDRPHY_DTCR_DTEXD_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTEXD_SHIFT) & DDRPHY_DTCR_DTEXD_MASK)
#define DDRPHY_DTCR_DTEXD_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTEXD_MASK) >> DDRPHY_DTCR_DTEXD_SHIFT)

/*
 * DTDSTP (R/W)
 *
 * Data Training Debug Step: A write of 1 to this bit steps the data training algorithm through a single step. This bit is used to initiate one step of the data training algorithm in question.
 * This bit is self-clearing. To trigger the next step, this bit must be written to again. Note: The training steps must be repeated in order to get new data in the “Data Training Eye Data Register 0-1 (DTEDR0-1)” on page 122. For example, to see the
 * training results for a different lane, select that lane and repeat the training steps to
 * populate DTEDR0 and DTEDR1 with the correct data.
 */
#define DDRPHY_DTCR_DTDSTP_MASK (0x200000UL)
#define DDRPHY_DTCR_DTDSTP_SHIFT (21U)
#define DDRPHY_DTCR_DTDSTP_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTDSTP_SHIFT) & DDRPHY_DTCR_DTDSTP_MASK)
#define DDRPHY_DTCR_DTDSTP_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTDSTP_MASK) >> DDRPHY_DTCR_DTDSTP_SHIFT)

/*
 * DTDEN (R/W)
 *
 * Data Training Debug Enable: Enables, if set, the data training single step debug mode.
 */
#define DDRPHY_DTCR_DTDEN_MASK (0x100000UL)
#define DDRPHY_DTCR_DTDEN_SHIFT (20U)
#define DDRPHY_DTCR_DTDEN_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTDEN_SHIFT) & DDRPHY_DTCR_DTDEN_MASK)
#define DDRPHY_DTCR_DTDEN_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTDEN_MASK) >> DDRPHY_DTCR_DTDEN_SHIFT)

/*
 * DTDBS (R/W)
 *
 * Data Training Debug Byte Select: Selects the byte during data training single step debug mode.
 * Note: DTDEN is not used to enable this feature.
 */
#define DDRPHY_DTCR_DTDBS_MASK (0xF0000UL)
#define DDRPHY_DTCR_DTDBS_SHIFT (16U)
#define DDRPHY_DTCR_DTDBS_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTDBS_SHIFT) & DDRPHY_DTCR_DTDBS_MASK)
#define DDRPHY_DTCR_DTDBS_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTDBS_MASK) >> DDRPHY_DTCR_DTDBS_SHIFT)

/*
 * DTWDQMO (R/W)
 *
 * Data Training WDQ Margin Override: If set, the Training WDQ Margin value specified in DTCR[11:8] (DTWDQM) is used during data training. Otherwise the value is computed as ¼ of the ddr_clk period measurement found during calibration of the WDQ LCDL.
 */
#define DDRPHY_DTCR_DTWDQMO_MASK (0x4000U)
#define DDRPHY_DTCR_DTWDQMO_SHIFT (14U)
#define DDRPHY_DTCR_DTWDQMO_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTWDQMO_SHIFT) & DDRPHY_DTCR_DTWDQMO_MASK)
#define DDRPHY_DTCR_DTWDQMO_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTWDQMO_MASK) >> DDRPHY_DTCR_DTWDQMO_SHIFT)

/*
 * DTBDC (R/W)
 *
 * Data Training Bit Deskew Centering: Enables, if set, eye centering capability during write and read bit deskew training.
 */
#define DDRPHY_DTCR_DTBDC_MASK (0x2000U)
#define DDRPHY_DTCR_DTBDC_SHIFT (13U)
#define DDRPHY_DTCR_DTBDC_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTBDC_SHIFT) & DDRPHY_DTCR_DTBDC_MASK)
#define DDRPHY_DTCR_DTBDC_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTBDC_MASK) >> DDRPHY_DTCR_DTBDC_SHIFT)

/*
 * DTWBDDM (R/W)
 *
 * Data Training Write Bit Deskew Data Mask, if set, it enables write bit deskew of the data mask
 */
#define DDRPHY_DTCR_DTWBDDM_MASK (0x1000U)
#define DDRPHY_DTCR_DTWBDDM_SHIFT (12U)
#define DDRPHY_DTCR_DTWBDDM_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTWBDDM_SHIFT) & DDRPHY_DTCR_DTWBDDM_MASK)
#define DDRPHY_DTCR_DTWBDDM_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTWBDDM_MASK) >> DDRPHY_DTCR_DTWBDDM_SHIFT)

/*
 * DTWDQM (R/W)
 *
 * Training WDQ Margin: Defines how close to 0 or how close to 2*(wdq calibration_value) the WDQ LCDL can be moved during training. Basically defines how much timing margin.
 */
#define DDRPHY_DTCR_DTWDQM_MASK (0xF00U)
#define DDRPHY_DTCR_DTWDQM_SHIFT (8U)
#define DDRPHY_DTCR_DTWDQM_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTWDQM_SHIFT) & DDRPHY_DTCR_DTWDQM_MASK)
#define DDRPHY_DTCR_DTWDQM_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTWDQM_MASK) >> DDRPHY_DTCR_DTWDQM_SHIFT)

/*
 * DTCMPD (R/W)
 *
 * Read Data Training Compare Data: Specifies, if set, that DQS gate training should also check if the returning read data is correct. Otherwise data-training only checks if the correct number of DQS edges were returned.
 */
#define DDRPHY_DTCR_DTCMPD_MASK (0x80U)
#define DDRPHY_DTCR_DTCMPD_SHIFT (7U)
#define DDRPHY_DTCR_DTCMPD_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTCMPD_SHIFT) & DDRPHY_DTCR_DTCMPD_MASK)
#define DDRPHY_DTCR_DTCMPD_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTCMPD_MASK) >> DDRPHY_DTCR_DTCMPD_SHIFT)

/*
 * DTMPR (R/W)
 *
 * Read Data Training Using MPR (DDR3 Only): Specifies, if set, that DQS gate training should use the SDRAM Multi-Purpose Register (MPR) register. Otherwise data-training is performed by first writing to some locations in the SDRAM and then reading them back.
 */
#define DDRPHY_DTCR_DTMPR_MASK (0x40U)
#define DDRPHY_DTCR_DTMPR_SHIFT (6U)
#define DDRPHY_DTCR_DTMPR_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTMPR_SHIFT) & DDRPHY_DTCR_DTMPR_MASK)
#define DDRPHY_DTCR_DTMPR_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTMPR_MASK) >> DDRPHY_DTCR_DTMPR_SHIFT)

/*
 * DTRANK (R/W)
 *
 * Data Training Rank: Select the SDRAM rank to be used during Read DQS gate training, Read/Write Data Bit Deskew, Read/Write Eye Training.
 */
#define DDRPHY_DTCR_DTRANK_MASK (0x30U)
#define DDRPHY_DTCR_DTRANK_SHIFT (4U)
#define DDRPHY_DTCR_DTRANK_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTRANK_SHIFT) & DDRPHY_DTCR_DTRANK_MASK)
#define DDRPHY_DTCR_DTRANK_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTRANK_MASK) >> DDRPHY_DTCR_DTRANK_SHIFT)

/*
 * DTRPTN (R/W)
 *
 * Data Training Repeat Number: Repeat number used to confirm stability of DDR write or read.
 * Note: The minimum value should be 0x4 and the maximum value should be 0x14.
 */
#define DDRPHY_DTCR_DTRPTN_MASK (0xFU)
#define DDRPHY_DTCR_DTRPTN_SHIFT (0U)
#define DDRPHY_DTCR_DTRPTN_SET(x) (((uint32_t)(x) << DDRPHY_DTCR_DTRPTN_SHIFT) & DDRPHY_DTCR_DTRPTN_MASK)
#define DDRPHY_DTCR_DTRPTN_GET(x) (((uint32_t)(x) & DDRPHY_DTCR_DTRPTN_MASK) >> DDRPHY_DTCR_DTRPTN_SHIFT)

/* Bitfield definition for register: DTAR0 */
/*
 * DTBANK (R/W)
 *
 * Data Training Bank Address: Selects the SDRAM bank address to be used during data training.
 */
#define DDRPHY_DTAR0_DTBANK_MASK (0x70000000UL)
#define DDRPHY_DTAR0_DTBANK_SHIFT (28U)
#define DDRPHY_DTAR0_DTBANK_SET(x) (((uint32_t)(x) << DDRPHY_DTAR0_DTBANK_SHIFT) & DDRPHY_DTAR0_DTBANK_MASK)
#define DDRPHY_DTAR0_DTBANK_GET(x) (((uint32_t)(x) & DDRPHY_DTAR0_DTBANK_MASK) >> DDRPHY_DTAR0_DTBANK_SHIFT)

/*
 * DTROW (R/W)
 *
 * Data Training Row Address: Selects the SDRAM row address to be used during data training.
 */
#define DDRPHY_DTAR0_DTROW_MASK (0xFFFF000UL)
#define DDRPHY_DTAR0_DTROW_SHIFT (12U)
#define DDRPHY_DTAR0_DTROW_SET(x) (((uint32_t)(x) << DDRPHY_DTAR0_DTROW_SHIFT) & DDRPHY_DTAR0_DTROW_MASK)
#define DDRPHY_DTAR0_DTROW_GET(x) (((uint32_t)(x) & DDRPHY_DTAR0_DTROW_MASK) >> DDRPHY_DTAR0_DTROW_SHIFT)

/*
 * DTCOL (R/W)
 *
 * Data Training Column Address: Selects the SDRAM column address to be used during data training. The lower four bits of this address must always be “000”.
 */
#define DDRPHY_DTAR0_DTCOL_MASK (0xFFFU)
#define DDRPHY_DTAR0_DTCOL_SHIFT (0U)
#define DDRPHY_DTAR0_DTCOL_SET(x) (((uint32_t)(x) << DDRPHY_DTAR0_DTCOL_SHIFT) & DDRPHY_DTAR0_DTCOL_MASK)
#define DDRPHY_DTAR0_DTCOL_GET(x) (((uint32_t)(x) & DDRPHY_DTAR0_DTCOL_MASK) >> DDRPHY_DTAR0_DTCOL_SHIFT)

/* Bitfield definition for register: DTAR1 */
/*
 * DTBANK (R/W)
 *
 * Data Training Bank Address: Selects the SDRAM bank address to be used during data training.
 */
#define DDRPHY_DTAR1_DTBANK_MASK (0x70000000UL)
#define DDRPHY_DTAR1_DTBANK_SHIFT (28U)
#define DDRPHY_DTAR1_DTBANK_SET(x) (((uint32_t)(x) << DDRPHY_DTAR1_DTBANK_SHIFT) & DDRPHY_DTAR1_DTBANK_MASK)
#define DDRPHY_DTAR1_DTBANK_GET(x) (((uint32_t)(x) & DDRPHY_DTAR1_DTBANK_MASK) >> DDRPHY_DTAR1_DTBANK_SHIFT)

/*
 * DTROW (R/W)
 *
 * Data Training Row Address: Selects the SDRAM row address to be used during data training.
 */
#define DDRPHY_DTAR1_DTROW_MASK (0xFFFF000UL)
#define DDRPHY_DTAR1_DTROW_SHIFT (12U)
#define DDRPHY_DTAR1_DTROW_SET(x) (((uint32_t)(x) << DDRPHY_DTAR1_DTROW_SHIFT) & DDRPHY_DTAR1_DTROW_MASK)
#define DDRPHY_DTAR1_DTROW_GET(x) (((uint32_t)(x) & DDRPHY_DTAR1_DTROW_MASK) >> DDRPHY_DTAR1_DTROW_SHIFT)

/*
 * DTCOL (R/W)
 *
 * Data Training Column Address: Selects the SDRAM column address to be used during data training. The lower four bits of this address must always be “000”.
 */
#define DDRPHY_DTAR1_DTCOL_MASK (0xFFFU)
#define DDRPHY_DTAR1_DTCOL_SHIFT (0U)
#define DDRPHY_DTAR1_DTCOL_SET(x) (((uint32_t)(x) << DDRPHY_DTAR1_DTCOL_SHIFT) & DDRPHY_DTAR1_DTCOL_MASK)
#define DDRPHY_DTAR1_DTCOL_GET(x) (((uint32_t)(x) & DDRPHY_DTAR1_DTCOL_MASK) >> DDRPHY_DTAR1_DTCOL_SHIFT)

/* Bitfield definition for register: DTAR2 */
/*
 * DTBANK (R/W)
 *
 * Data Training Bank Address: Selects the SDRAM bank address to be used during data training.
 */
#define DDRPHY_DTAR2_DTBANK_MASK (0x70000000UL)
#define DDRPHY_DTAR2_DTBANK_SHIFT (28U)
#define DDRPHY_DTAR2_DTBANK_SET(x) (((uint32_t)(x) << DDRPHY_DTAR2_DTBANK_SHIFT) & DDRPHY_DTAR2_DTBANK_MASK)
#define DDRPHY_DTAR2_DTBANK_GET(x) (((uint32_t)(x) & DDRPHY_DTAR2_DTBANK_MASK) >> DDRPHY_DTAR2_DTBANK_SHIFT)

/*
 * DTROW (R/W)
 *
 * Data Training Row Address: Selects the SDRAM row address to be used during data training.
 */
#define DDRPHY_DTAR2_DTROW_MASK (0xFFFF000UL)
#define DDRPHY_DTAR2_DTROW_SHIFT (12U)
#define DDRPHY_DTAR2_DTROW_SET(x) (((uint32_t)(x) << DDRPHY_DTAR2_DTROW_SHIFT) & DDRPHY_DTAR2_DTROW_MASK)
#define DDRPHY_DTAR2_DTROW_GET(x) (((uint32_t)(x) & DDRPHY_DTAR2_DTROW_MASK) >> DDRPHY_DTAR2_DTROW_SHIFT)

/*
 * DTCOL (R/W)
 *
 * Data Training Column Address: Selects the SDRAM column address to be used during data training. The lower four bits of this address must always be “000”.
 */
#define DDRPHY_DTAR2_DTCOL_MASK (0xFFFU)
#define DDRPHY_DTAR2_DTCOL_SHIFT (0U)
#define DDRPHY_DTAR2_DTCOL_SET(x) (((uint32_t)(x) << DDRPHY_DTAR2_DTCOL_SHIFT) & DDRPHY_DTAR2_DTCOL_MASK)
#define DDRPHY_DTAR2_DTCOL_GET(x) (((uint32_t)(x) & DDRPHY_DTAR2_DTCOL_MASK) >> DDRPHY_DTAR2_DTCOL_SHIFT)

/* Bitfield definition for register: DTAR3 */
/*
 * DTBANK (R/W)
 *
 * Data Training Bank Address: Selects the SDRAM bank address to be used during data training.
 */
#define DDRPHY_DTAR3_DTBANK_MASK (0x70000000UL)
#define DDRPHY_DTAR3_DTBANK_SHIFT (28U)
#define DDRPHY_DTAR3_DTBANK_SET(x) (((uint32_t)(x) << DDRPHY_DTAR3_DTBANK_SHIFT) & DDRPHY_DTAR3_DTBANK_MASK)
#define DDRPHY_DTAR3_DTBANK_GET(x) (((uint32_t)(x) & DDRPHY_DTAR3_DTBANK_MASK) >> DDRPHY_DTAR3_DTBANK_SHIFT)

/*
 * DTROW (R/W)
 *
 * Data Training Row Address: Selects the SDRAM row address to be used during data training.
 */
#define DDRPHY_DTAR3_DTROW_MASK (0xFFFF000UL)
#define DDRPHY_DTAR3_DTROW_SHIFT (12U)
#define DDRPHY_DTAR3_DTROW_SET(x) (((uint32_t)(x) << DDRPHY_DTAR3_DTROW_SHIFT) & DDRPHY_DTAR3_DTROW_MASK)
#define DDRPHY_DTAR3_DTROW_GET(x) (((uint32_t)(x) & DDRPHY_DTAR3_DTROW_MASK) >> DDRPHY_DTAR3_DTROW_SHIFT)

/*
 * DTCOL (R/W)
 *
 * Data Training Column Address: Selects the SDRAM column address to be used during data training. The lower four bits of this address must always be “000”.
 */
#define DDRPHY_DTAR3_DTCOL_MASK (0xFFFU)
#define DDRPHY_DTAR3_DTCOL_SHIFT (0U)
#define DDRPHY_DTAR3_DTCOL_SET(x) (((uint32_t)(x) << DDRPHY_DTAR3_DTCOL_SHIFT) & DDRPHY_DTAR3_DTCOL_MASK)
#define DDRPHY_DTAR3_DTCOL_GET(x) (((uint32_t)(x) & DDRPHY_DTAR3_DTCOL_MASK) >> DDRPHY_DTAR3_DTCOL_SHIFT)

/* Bitfield definition for register: DTDR0 */
/*
 * DTBYTE3 (R/W)
 *
 */
#define DDRPHY_DTDR0_DTBYTE3_MASK (0xFF000000UL)
#define DDRPHY_DTDR0_DTBYTE3_SHIFT (24U)
#define DDRPHY_DTDR0_DTBYTE3_SET(x) (((uint32_t)(x) << DDRPHY_DTDR0_DTBYTE3_SHIFT) & DDRPHY_DTDR0_DTBYTE3_MASK)
#define DDRPHY_DTDR0_DTBYTE3_GET(x) (((uint32_t)(x) & DDRPHY_DTDR0_DTBYTE3_MASK) >> DDRPHY_DTDR0_DTBYTE3_SHIFT)

/*
 * DTBYTE2 (R/W)
 *
 */
#define DDRPHY_DTDR0_DTBYTE2_MASK (0xFF0000UL)
#define DDRPHY_DTDR0_DTBYTE2_SHIFT (16U)
#define DDRPHY_DTDR0_DTBYTE2_SET(x) (((uint32_t)(x) << DDRPHY_DTDR0_DTBYTE2_SHIFT) & DDRPHY_DTDR0_DTBYTE2_MASK)
#define DDRPHY_DTDR0_DTBYTE2_GET(x) (((uint32_t)(x) & DDRPHY_DTDR0_DTBYTE2_MASK) >> DDRPHY_DTDR0_DTBYTE2_SHIFT)

/*
 * DTBYTE1 (R/W)
 *
 */
#define DDRPHY_DTDR0_DTBYTE1_MASK (0xFF00U)
#define DDRPHY_DTDR0_DTBYTE1_SHIFT (8U)
#define DDRPHY_DTDR0_DTBYTE1_SET(x) (((uint32_t)(x) << DDRPHY_DTDR0_DTBYTE1_SHIFT) & DDRPHY_DTDR0_DTBYTE1_MASK)
#define DDRPHY_DTDR0_DTBYTE1_GET(x) (((uint32_t)(x) & DDRPHY_DTDR0_DTBYTE1_MASK) >> DDRPHY_DTDR0_DTBYTE1_SHIFT)

/*
 * DTBYTE0 (R/W)
 *
 * Data Training Data: The first 4 bytes of data used during data training. This same data byte is used for each Byte Lane. Default sequence is a walking 1 while toggling data every data cycle.
 */
#define DDRPHY_DTDR0_DTBYTE0_MASK (0xFFU)
#define DDRPHY_DTDR0_DTBYTE0_SHIFT (0U)
#define DDRPHY_DTDR0_DTBYTE0_SET(x) (((uint32_t)(x) << DDRPHY_DTDR0_DTBYTE0_SHIFT) & DDRPHY_DTDR0_DTBYTE0_MASK)
#define DDRPHY_DTDR0_DTBYTE0_GET(x) (((uint32_t)(x) & DDRPHY_DTDR0_DTBYTE0_MASK) >> DDRPHY_DTDR0_DTBYTE0_SHIFT)

/* Bitfield definition for register: DTDR1 */
/*
 * DTBYTE7 (R/W)
 *
 */
#define DDRPHY_DTDR1_DTBYTE7_MASK (0xFF000000UL)
#define DDRPHY_DTDR1_DTBYTE7_SHIFT (24U)
#define DDRPHY_DTDR1_DTBYTE7_SET(x) (((uint32_t)(x) << DDRPHY_DTDR1_DTBYTE7_SHIFT) & DDRPHY_DTDR1_DTBYTE7_MASK)
#define DDRPHY_DTDR1_DTBYTE7_GET(x) (((uint32_t)(x) & DDRPHY_DTDR1_DTBYTE7_MASK) >> DDRPHY_DTDR1_DTBYTE7_SHIFT)

/*
 * DTBYTE6 (R/W)
 *
 */
#define DDRPHY_DTDR1_DTBYTE6_MASK (0xFF0000UL)
#define DDRPHY_DTDR1_DTBYTE6_SHIFT (16U)
#define DDRPHY_DTDR1_DTBYTE6_SET(x) (((uint32_t)(x) << DDRPHY_DTDR1_DTBYTE6_SHIFT) & DDRPHY_DTDR1_DTBYTE6_MASK)
#define DDRPHY_DTDR1_DTBYTE6_GET(x) (((uint32_t)(x) & DDRPHY_DTDR1_DTBYTE6_MASK) >> DDRPHY_DTDR1_DTBYTE6_SHIFT)

/*
 * DTBYTE5 (R/W)
 *
 */
#define DDRPHY_DTDR1_DTBYTE5_MASK (0xFF00U)
#define DDRPHY_DTDR1_DTBYTE5_SHIFT (8U)
#define DDRPHY_DTDR1_DTBYTE5_SET(x) (((uint32_t)(x) << DDRPHY_DTDR1_DTBYTE5_SHIFT) & DDRPHY_DTDR1_DTBYTE5_MASK)
#define DDRPHY_DTDR1_DTBYTE5_GET(x) (((uint32_t)(x) & DDRPHY_DTDR1_DTBYTE5_MASK) >> DDRPHY_DTDR1_DTBYTE5_SHIFT)

/*
 * DTBYTE4 (R/W)
 *
 * Data Training Data: The second 4 bytes of data used during data training. This same data byte is used for each Byte Lane. Default sequence is a walking 1 while toggling data every data cycle.
 */
#define DDRPHY_DTDR1_DTBYTE4_MASK (0xFFU)
#define DDRPHY_DTDR1_DTBYTE4_SHIFT (0U)
#define DDRPHY_DTDR1_DTBYTE4_SET(x) (((uint32_t)(x) << DDRPHY_DTDR1_DTBYTE4_SHIFT) & DDRPHY_DTDR1_DTBYTE4_MASK)
#define DDRPHY_DTDR1_DTBYTE4_GET(x) (((uint32_t)(x) & DDRPHY_DTDR1_DTBYTE4_MASK) >> DDRPHY_DTDR1_DTBYTE4_SHIFT)

/* Bitfield definition for register: DTEDR0 */
/*
 * DTWBMX (R)
 *
 * Data Training Write BDL Shift Maximum.
 */
#define DDRPHY_DTEDR0_DTWBMX_MASK (0xFF000000UL)
#define DDRPHY_DTEDR0_DTWBMX_SHIFT (24U)
#define DDRPHY_DTEDR0_DTWBMX_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR0_DTWBMX_MASK) >> DDRPHY_DTEDR0_DTWBMX_SHIFT)

/*
 * DTWBMN (R)
 *
 * Data Training Write BDL Shift Minimum.
 */
#define DDRPHY_DTEDR0_DTWBMN_MASK (0xFF0000UL)
#define DDRPHY_DTEDR0_DTWBMN_SHIFT (16U)
#define DDRPHY_DTEDR0_DTWBMN_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR0_DTWBMN_MASK) >> DDRPHY_DTEDR0_DTWBMN_SHIFT)

/*
 * DTWLMX (R)
 *
 * Data Training WDQ LCDL Maximum.
 */
#define DDRPHY_DTEDR0_DTWLMX_MASK (0xFF00U)
#define DDRPHY_DTEDR0_DTWLMX_SHIFT (8U)
#define DDRPHY_DTEDR0_DTWLMX_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR0_DTWLMX_MASK) >> DDRPHY_DTEDR0_DTWLMX_SHIFT)

/*
 * DTWLMN (R)
 *
 * Data Training WDQ LCDL Minimum.
 */
#define DDRPHY_DTEDR0_DTWLMN_MASK (0xFFU)
#define DDRPHY_DTEDR0_DTWLMN_SHIFT (0U)
#define DDRPHY_DTEDR0_DTWLMN_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR0_DTWLMN_MASK) >> DDRPHY_DTEDR0_DTWLMN_SHIFT)

/* Bitfield definition for register: DTEDR1 */
/*
 * DTRBMX (R)
 *
 * Data Training Read BDL Shift Maximum.
 */
#define DDRPHY_DTEDR1_DTRBMX_MASK (0xFF000000UL)
#define DDRPHY_DTEDR1_DTRBMX_SHIFT (24U)
#define DDRPHY_DTEDR1_DTRBMX_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR1_DTRBMX_MASK) >> DDRPHY_DTEDR1_DTRBMX_SHIFT)

/*
 * DTRBMN (R)
 *
 * Data Training Read BDL Shift Minimum.
 */
#define DDRPHY_DTEDR1_DTRBMN_MASK (0xFF0000UL)
#define DDRPHY_DTEDR1_DTRBMN_SHIFT (16U)
#define DDRPHY_DTEDR1_DTRBMN_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR1_DTRBMN_MASK) >> DDRPHY_DTEDR1_DTRBMN_SHIFT)

/*
 * DTRLMX (R)
 *
 * Data Training RDQS LCDL Maximum.
 */
#define DDRPHY_DTEDR1_DTRLMX_MASK (0xFF00U)
#define DDRPHY_DTEDR1_DTRLMX_SHIFT (8U)
#define DDRPHY_DTEDR1_DTRLMX_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR1_DTRLMX_MASK) >> DDRPHY_DTEDR1_DTRLMX_SHIFT)

/*
 * DTRLMN (R)
 *
 * Data Training RDQS LCDL Minimum.
 */
#define DDRPHY_DTEDR1_DTRLMN_MASK (0xFFU)
#define DDRPHY_DTEDR1_DTRLMN_SHIFT (0U)
#define DDRPHY_DTEDR1_DTRLMN_GET(x) (((uint32_t)(x) & DDRPHY_DTEDR1_DTRLMN_MASK) >> DDRPHY_DTEDR1_DTRLMN_SHIFT)

/* Bitfield definition for register: PGCR2 */
/*
 * DYNACPDD1 (R/W)
 *
 * Dynamic AC Power Down Driver: Powers down, when set, the output driver on I/O for ADDR and BA. This bit is ORed with bit ACIOCR[3] (ACPDD).
 */
#define DDRPHY_PGCR2_DYNACPDD1_MASK (0x80000000UL)
#define DDRPHY_PGCR2_DYNACPDD1_SHIFT (31U)
#define DDRPHY_PGCR2_DYNACPDD1_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_DYNACPDD1_SHIFT) & DDRPHY_PGCR2_DYNACPDD1_MASK)
#define DDRPHY_PGCR2_DYNACPDD1_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_DYNACPDD1_MASK) >> DDRPHY_PGCR2_DYNACPDD1_SHIFT)

/*
 * LPMSTRC0 (R/W)
 *
 * Low-Power Master Channel 0: set to 1 to have channel 0 act as master to drive channel 1 low-power functions simultaneously. Only valid in shared-AC mode.
 */
#define DDRPHY_PGCR2_LPMSTRC0_MASK (0x40000000UL)
#define DDRPHY_PGCR2_LPMSTRC0_SHIFT (30U)
#define DDRPHY_PGCR2_LPMSTRC0_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_LPMSTRC0_SHIFT) & DDRPHY_PGCR2_LPMSTRC0_MASK)
#define DDRPHY_PGCR2_LPMSTRC0_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_LPMSTRC0_MASK) >> DDRPHY_PGCR2_LPMSTRC0_SHIFT)

/*
 * ACPDDC (R/W)
 *
 * AC Power-Down with Dual Channels: Set to 1 to power-down address/command lane when both data channels are powered-down. Only valid in shared-AC mode.
 */
#define DDRPHY_PGCR2_ACPDDC_MASK (0x20000000UL)
#define DDRPHY_PGCR2_ACPDDC_SHIFT (29U)
#define DDRPHY_PGCR2_ACPDDC_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_ACPDDC_SHIFT) & DDRPHY_PGCR2_ACPDDC_MASK)
#define DDRPHY_PGCR2_ACPDDC_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_ACPDDC_MASK) >> DDRPHY_PGCR2_ACPDDC_SHIFT)

/*
 * SHRAC (R/W)
 *
 * Shared-AC mode: set to 1 to enable shared address/command mode with two independent data channels – available only if shared address/command mode support is compiled in.
 */
#define DDRPHY_PGCR2_SHRAC_MASK (0x10000000UL)
#define DDRPHY_PGCR2_SHRAC_SHIFT (28U)
#define DDRPHY_PGCR2_SHRAC_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_SHRAC_SHIFT) & DDRPHY_PGCR2_SHRAC_MASK)
#define DDRPHY_PGCR2_SHRAC_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_SHRAC_MASK) >> DDRPHY_PGCR2_SHRAC_SHIFT)

/*
 * DTPMXTMR (R/W)
 *
 * Data Training PUB Mode Timer Exit: Specifies the number of controller clocks to wait when entering and exiting pub mode data training. The default value ensures controller refreshes do not cause memory model errors when entering and exiting data training. The value should be increased if controller initiated SDRAM ZQ short or long operation may occur just before or just after the execution of data training.
 */
#define DDRPHY_PGCR2_DTPMXTMR_MASK (0xFF00000UL)
#define DDRPHY_PGCR2_DTPMXTMR_SHIFT (20U)
#define DDRPHY_PGCR2_DTPMXTMR_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_DTPMXTMR_SHIFT) & DDRPHY_PGCR2_DTPMXTMR_MASK)
#define DDRPHY_PGCR2_DTPMXTMR_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_DTPMXTMR_MASK) >> DDRPHY_PGCR2_DTPMXTMR_SHIFT)

/*
 * FXDLAT (R/W)
 *
 * Fixed Latency: Specified whether all reads should be returned to the controller with a fixed read latency. Enabling fixed read latency increases the read latency. Valid values are:
 * 0 = Disable fixed read latency 1 = Enable fixed read latency
 * Fixed read latency is calculated as (12 + (maximum DXnGTR.RxDGSL)/2) HDR clock cycles
 */
#define DDRPHY_PGCR2_FXDLAT_MASK (0x80000UL)
#define DDRPHY_PGCR2_FXDLAT_SHIFT (19U)
#define DDRPHY_PGCR2_FXDLAT_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_FXDLAT_SHIFT) & DDRPHY_PGCR2_FXDLAT_MASK)
#define DDRPHY_PGCR2_FXDLAT_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_FXDLAT_MASK) >> DDRPHY_PGCR2_FXDLAT_SHIFT)

/*
 * NOBUB (R/W)
 *
 * No Bubbles: Specified whether reads should be returned to the controller with no bubbles. Enabling no-bubble reads increases the read latency. Valid values are: 0 = Bubbles are allowed during reads
 * 1 = Bubbles are not allowed during reads
 */
#define DDRPHY_PGCR2_NOBUB_MASK (0x40000UL)
#define DDRPHY_PGCR2_NOBUB_SHIFT (18U)
#define DDRPHY_PGCR2_NOBUB_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_NOBUB_SHIFT) & DDRPHY_PGCR2_NOBUB_MASK)
#define DDRPHY_PGCR2_NOBUB_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_NOBUB_MASK) >> DDRPHY_PGCR2_NOBUB_SHIFT)

/*
 * TREFPRD (R/W)
 *
 * Refresh Period: Indicates the period, after which the PUB has to issue a refresh command to the SDRAM. This is derived from the maximum refresh interval from the datasheet, tRFC(max) or REFI, divided by the clock cycle time. A further 400 clocks must be subtracted from the derived number to account for command flow and missed slots of refreshes in the internal PUB blocks. The default corresponds to DDR3 9*7.8us at 1066MHz when a burst of 9 refreshes are issued at every refresh interval.
 */
#define DDRPHY_PGCR2_TREFPRD_MASK (0x3FFFFUL)
#define DDRPHY_PGCR2_TREFPRD_SHIFT (0U)
#define DDRPHY_PGCR2_TREFPRD_SET(x) (((uint32_t)(x) << DDRPHY_PGCR2_TREFPRD_SHIFT) & DDRPHY_PGCR2_TREFPRD_MASK)
#define DDRPHY_PGCR2_TREFPRD_GET(x) (((uint32_t)(x) & DDRPHY_PGCR2_TREFPRD_MASK) >> DDRPHY_PGCR2_TREFPRD_SHIFT)

/* Bitfield definition for register: RDIMMGCR0 */
/*
 * MIRROR (R)
 *
 * RDIMM Mirror: Selects between two different ballouts of the RDIMM buffer chip for front or back operation. This register bit controls the buffer chip MIRROR signal.
 */
#define DDRPHY_RDIMMGCR0_MIRROR_MASK (0x80000000UL)
#define DDRPHY_RDIMMGCR0_MIRROR_SHIFT (31U)
#define DDRPHY_RDIMMGCR0_MIRROR_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_MIRROR_MASK) >> DDRPHY_RDIMMGCR0_MIRROR_SHIFT)

/*
 * QCSEN (R)
 *
 * RDMIMM Quad CS Enable: Enables, if set, the Quad CS mode for the RDIMM registering buffer chip. This register bit controls the buffer chip QCSEN# signal.
 */
#define DDRPHY_RDIMMGCR0_QCSEN_MASK (0x40000000UL)
#define DDRPHY_RDIMMGCR0_QCSEN_SHIFT (30U)
#define DDRPHY_RDIMMGCR0_QCSEN_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_QCSEN_MASK) >> DDRPHY_RDIMMGCR0_QCSEN_SHIFT)

/*
 * MIRROROE (R)
 *
 * MIRROR Output Enable: Enables, when set, the output driver on the I/O for MIRROR pin.
 */
#define DDRPHY_RDIMMGCR0_MIRROROE_MASK (0x20000000UL)
#define DDRPHY_RDIMMGCR0_MIRROROE_SHIFT (29U)
#define DDRPHY_RDIMMGCR0_MIRROROE_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_MIRROROE_MASK) >> DDRPHY_RDIMMGCR0_MIRROROE_SHIFT)

/*
 * QCSENOE (R)
 *
 * QCSEN# Output Enable: Enables, when set, the output driver on the I/O for QCSEN# pin.
 */
#define DDRPHY_RDIMMGCR0_QCSENOE_MASK (0x10000000UL)
#define DDRPHY_RDIMMGCR0_QCSENOE_SHIFT (28U)
#define DDRPHY_RDIMMGCR0_QCSENOE_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_QCSENOE_MASK) >> DDRPHY_RDIMMGCR0_QCSENOE_SHIFT)

/*
 * RDIMMIOM (R)
 *
 * RDIMM Outputs I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for QCSEN# and MIRROR pins.
 */
#define DDRPHY_RDIMMGCR0_RDIMMIOM_MASK (0x8000000UL)
#define DDRPHY_RDIMMGCR0_RDIMMIOM_SHIFT (27U)
#define DDRPHY_RDIMMGCR0_RDIMMIOM_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_RDIMMIOM_MASK) >> DDRPHY_RDIMMGCR0_RDIMMIOM_SHIFT)

/*
 * RDIMMPDR (R)
 *
 * RDIMM Outputs Power Down Receiver: Powers down, when set, the input receiver on the I/O for QCSEN# and MIRROR pins.
 */
#define DDRPHY_RDIMMGCR0_RDIMMPDR_MASK (0x4000000UL)
#define DDRPHY_RDIMMGCR0_RDIMMPDR_SHIFT (26U)
#define DDRPHY_RDIMMGCR0_RDIMMPDR_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_RDIMMPDR_MASK) >> DDRPHY_RDIMMGCR0_RDIMMPDR_SHIFT)

/*
 * RDIMMPDD (R)
 *
 * RDIMM Outputs Power Down Driver: Powers down, when set, the output driver on the I/O for QCSEN# and MIRROR pins.
 */
#define DDRPHY_RDIMMGCR0_RDIMMPDD_MASK (0x2000000UL)
#define DDRPHY_RDIMMGCR0_RDIMMPDD_SHIFT (25U)
#define DDRPHY_RDIMMGCR0_RDIMMPDD_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_RDIMMPDD_MASK) >> DDRPHY_RDIMMGCR0_RDIMMPDD_SHIFT)

/*
 * RDIMMODT (R)
 *
 * RDIMM Outputs On-Die Termination: Enables, when set, the on-die termination on the I/O for QCSEN# and MIRROR pins.
 */
#define DDRPHY_RDIMMGCR0_RDIMMODT_MASK (0x1000000UL)
#define DDRPHY_RDIMMGCR0_RDIMMODT_SHIFT (24U)
#define DDRPHY_RDIMMGCR0_RDIMMODT_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_RDIMMODT_MASK) >> DDRPHY_RDIMMGCR0_RDIMMODT_SHIFT)

/*
 * ERROUTOE (R)
 *
 * ERROUT# Output Enable: Enables, when set, the output driver on the I/O for ERROUT# pin.
 */
#define DDRPHY_RDIMMGCR0_ERROUTOE_MASK (0x800000UL)
#define DDRPHY_RDIMMGCR0_ERROUTOE_SHIFT (23U)
#define DDRPHY_RDIMMGCR0_ERROUTOE_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERROUTOE_MASK) >> DDRPHY_RDIMMGCR0_ERROUTOE_SHIFT)

/*
 * ERROUTIOM (R)
 *
 * ERROUT# I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for ERROUT# pin.
 */
#define DDRPHY_RDIMMGCR0_ERROUTIOM_MASK (0x400000UL)
#define DDRPHY_RDIMMGCR0_ERROUTIOM_SHIFT (22U)
#define DDRPHY_RDIMMGCR0_ERROUTIOM_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERROUTIOM_MASK) >> DDRPHY_RDIMMGCR0_ERROUTIOM_SHIFT)

/*
 * ERROUTPDR (R)
 *
 * ERROUT# Power Down Receiver: Powers down, when set, the input receiver on the I/O for ERROUT# pin.
 */
#define DDRPHY_RDIMMGCR0_ERROUTPDR_MASK (0x200000UL)
#define DDRPHY_RDIMMGCR0_ERROUTPDR_SHIFT (21U)
#define DDRPHY_RDIMMGCR0_ERROUTPDR_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERROUTPDR_MASK) >> DDRPHY_RDIMMGCR0_ERROUTPDR_SHIFT)

/*
 * ERROUTPDD (R)
 *
 * ERROUT# Power Down Driver: Powers down, when set, the output driver on the I/O for ERROUT# pin.
 */
#define DDRPHY_RDIMMGCR0_ERROUTPDD_MASK (0x100000UL)
#define DDRPHY_RDIMMGCR0_ERROUTPDD_SHIFT (20U)
#define DDRPHY_RDIMMGCR0_ERROUTPDD_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERROUTPDD_MASK) >> DDRPHY_RDIMMGCR0_ERROUTPDD_SHIFT)

/*
 * ERROUTODT (R)
 *
 * ERROUT# On-Die Termination: Enables, when set, the on-die termination on the I/O for ERROUT# pin.
 */
#define DDRPHY_RDIMMGCR0_ERROUTODT_MASK (0x80000UL)
#define DDRPHY_RDIMMGCR0_ERROUTODT_SHIFT (19U)
#define DDRPHY_RDIMMGCR0_ERROUTODT_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERROUTODT_MASK) >> DDRPHY_RDIMMGCR0_ERROUTODT_SHIFT)

/*
 * PARINOE (R)
 *
 * PAR_IN Output Enable: Enables, when set, the output driver on the I/O for PAR_IN pin.
 */
#define DDRPHY_RDIMMGCR0_PARINOE_MASK (0x40000UL)
#define DDRPHY_RDIMMGCR0_PARINOE_SHIFT (18U)
#define DDRPHY_RDIMMGCR0_PARINOE_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_PARINOE_MASK) >> DDRPHY_RDIMMGCR0_PARINOE_SHIFT)

/*
 * PARINIOM (R)
 *
 * PAR_IN I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for PAR_IN pin.
 */
#define DDRPHY_RDIMMGCR0_PARINIOM_MASK (0x20000UL)
#define DDRPHY_RDIMMGCR0_PARINIOM_SHIFT (17U)
#define DDRPHY_RDIMMGCR0_PARINIOM_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_PARINIOM_MASK) >> DDRPHY_RDIMMGCR0_PARINIOM_SHIFT)

/*
 * PARINPDR (R)
 *
 * PAR_IN Power Down Receiver: Powers down, when set, the input receiver on the I/O for PAR_IN pin.
 */
#define DDRPHY_RDIMMGCR0_PARINPDR_MASK (0x10000UL)
#define DDRPHY_RDIMMGCR0_PARINPDR_SHIFT (16U)
#define DDRPHY_RDIMMGCR0_PARINPDR_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_PARINPDR_MASK) >> DDRPHY_RDIMMGCR0_PARINPDR_SHIFT)

/*
 * PARINPDD (R)
 *
 * PAR_IN Power Down Driver: Powers down, when set, the output driver on the I/O for PAR_IN pin.
 */
#define DDRPHY_RDIMMGCR0_PARINPDD_MASK (0x8000U)
#define DDRPHY_RDIMMGCR0_PARINPDD_SHIFT (15U)
#define DDRPHY_RDIMMGCR0_PARINPDD_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_PARINPDD_MASK) >> DDRPHY_RDIMMGCR0_PARINPDD_SHIFT)

/*
 * PARINODT (R)
 *
 * PAR_IN On-Die Termination: Enables, when set, the on-die termination on the I/O for PAR_IN pin.
 */
#define DDRPHY_RDIMMGCR0_PARINODT_MASK (0x4000U)
#define DDRPHY_RDIMMGCR0_PARINODT_SHIFT (14U)
#define DDRPHY_RDIMMGCR0_PARINODT_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_PARINODT_MASK) >> DDRPHY_RDIMMGCR0_PARINODT_SHIFT)

/*
 * SOPERR (R)
 *
 * Stop On Parity Error: Indicates, if set, that the PUB is to stop driving commands to the DRAM upon encountering a parity error. Transactions can resume only after status is cleared via PIR.CLRSR.
 */
#define DDRPHY_RDIMMGCR0_SOPERR_MASK (0x4U)
#define DDRPHY_RDIMMGCR0_SOPERR_SHIFT (2U)
#define DDRPHY_RDIMMGCR0_SOPERR_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_SOPERR_MASK) >> DDRPHY_RDIMMGCR0_SOPERR_SHIFT)

/*
 * ERRNOREG (R)
 *
 * Parity Error No Registering: Indicates, if set, that parity error signal from the RDIMM should be passed to the DFI controller without any synchronization or registering. Otherwise, the error signal is synchronized as shown in Figure 4-30 on page 262.
 */
#define DDRPHY_RDIMMGCR0_ERRNOREG_MASK (0x2U)
#define DDRPHY_RDIMMGCR0_ERRNOREG_SHIFT (1U)
#define DDRPHY_RDIMMGCR0_ERRNOREG_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_ERRNOREG_MASK) >> DDRPHY_RDIMMGCR0_ERRNOREG_SHIFT)

/*
 * RDIMM (R)
 *
 * Registered DIMM: Indicates, if set, that a registered DIMM is used. In this case, the PUB increases the SDRAM write and read latencies (WL/RL) by 1 and also enforces that accesses adhere to RDIMM buffer chip. This only applies to PUB internal SDRAM transactions. Transactions generated by the controller must make its own adjustments to WL/RL when using a registered DIMM. The DCR.NOSRA register bit must be set to ‘1’ if using the standard RDIMM buffer chip so that normal DRAM accesses do not assert multiple chip select bits at the same time.
 */
#define DDRPHY_RDIMMGCR0_RDIMM_MASK (0x1U)
#define DDRPHY_RDIMMGCR0_RDIMM_SHIFT (0U)
#define DDRPHY_RDIMMGCR0_RDIMM_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR0_RDIMM_MASK) >> DDRPHY_RDIMMGCR0_RDIMM_SHIFT)

/* Bitfield definition for register: RDIMMGCR1 */
/*
 * CRINIT (R)
 *
 * Control Registers Initialization Enable: Indicates which RDIMM buffer chip control registers (RC0 to RC15) should be initialized (written) when the PUB is triggered to initialize the buffer chip. A setting of ‘1’ on CRINIT[n] bit means that CRn should be written during initialization.
 */
#define DDRPHY_RDIMMGCR1_CRINIT_MASK (0xFFFF0000UL)
#define DDRPHY_RDIMMGCR1_CRINIT_SHIFT (16U)
#define DDRPHY_RDIMMGCR1_CRINIT_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR1_CRINIT_MASK) >> DDRPHY_RDIMMGCR1_CRINIT_SHIFT)

/*
 * TBCMRD (R)
 *
 * Command word to command word programming delay: Number of DRAM clock cycles between two RDIMM buffer chip command programming accesses. The value used for tBCMRD is 8 plus the value programmed in these bits, i.e. tBCMRD value ranges from 8 to 15. This parameter corresponds to the buffer chip tMRD parameter.
 */
#define DDRPHY_RDIMMGCR1_TBCMRD_MASK (0x7000U)
#define DDRPHY_RDIMMGCR1_TBCMRD_SHIFT (12U)
#define DDRPHY_RDIMMGCR1_TBCMRD_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR1_TBCMRD_MASK) >> DDRPHY_RDIMMGCR1_TBCMRD_SHIFT)

/*
 * TBCSTAB (R)
 *
 * Stabilization time: Number of DRAM clock cycles for the RDIMM buffer chip to stabilize. This parameter corresponds to the buffer chip tSTAB parameter. Default value is in decimal format and corresponds to 6us at 533MHz.
 */
#define DDRPHY_RDIMMGCR1_TBCSTAB_MASK (0xFFFU)
#define DDRPHY_RDIMMGCR1_TBCSTAB_SHIFT (0U)
#define DDRPHY_RDIMMGCR1_TBCSTAB_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMGCR1_TBCSTAB_MASK) >> DDRPHY_RDIMMGCR1_TBCSTAB_SHIFT)

/* Bitfield definition for register: RDIMMCR0 */
/*
 * RC7 (R)
 *
 * Control Word 7: Reserved, free to use by vendor.
 */
#define DDRPHY_RDIMMCR0_RC7_MASK (0xF0000000UL)
#define DDRPHY_RDIMMCR0_RC7_SHIFT (28U)
#define DDRPHY_RDIMMCR0_RC7_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC7_MASK) >> DDRPHY_RDIMMCR0_RC7_SHIFT)

/*
 * RC6 (R)
 *
 * Control Word 6: Reserved, free to use by vendor.
 */
#define DDRPHY_RDIMMCR0_RC6_MASK (0xF000000UL)
#define DDRPHY_RDIMMCR0_RC6_SHIFT (24U)
#define DDRPHY_RDIMMCR0_RC6_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC6_MASK) >> DDRPHY_RDIMMCR0_RC6_SHIFT)

/*
 * RC5 (R)
 *
 * Control Word 5 (CK Driver Characteristics Control Word): RC5[1:0] is driver settings for clock Y1, Y1#, Y3, and Y3# outputs, and RC5[3:2] is driver settings for clock Y0, Y0#, Y2, and Y2# outputs. Bit definitions are:
 * 00 = Light drive (4 or 5 DRAM loads)
 * 01 = Moderate drive (8 or 10 DRAM loads)
 * 10 = Strong drive (16 or 20 DRAM loads)
 * 11 = Reserved
 */
#define DDRPHY_RDIMMCR0_RC5_MASK (0xF00000UL)
#define DDRPHY_RDIMMCR0_RC5_SHIFT (20U)
#define DDRPHY_RDIMMCR0_RC5_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC5_MASK) >> DDRPHY_RDIMMCR0_RC5_SHIFT)

/*
 * RC4 (R)
 *
 * Control Word 4 (Control Signals Driver Characteristics Control Word): RC4[1:0] is driver settings for control A outputs, and RC4[3:2] is driver settings for control B outputs. Bit definitions are:
 * 00 = Light drive (4 or 5 DRAM loads)
 * 01 = Moderate drive (8 or 10 DRAM loads)
 * 10 = Reserved
 * 11 = Reserved
 */
#define DDRPHY_RDIMMCR0_RC4_MASK (0xF0000UL)
#define DDRPHY_RDIMMCR0_RC4_SHIFT (16U)
#define DDRPHY_RDIMMCR0_RC4_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC4_MASK) >> DDRPHY_RDIMMCR0_RC4_SHIFT)

/*
 * RC3 (R)
 *
 * Control Word 3 (Command/Address Signals Driver Characteristics Control Word): RC3[1:0] is driver settings for command/address A outputs, and RC3[3:2] is driver settings for command/address B outputs. Bit definitions are:
 * 00 = Light drive (4 or 5 DRAM loads)
 * 01 = Moderate drive (8 or 10 DRAM loads)
 * 10 = Strong drive (16 or 20 DRAM loads)
 * 11 = Reserved
 */
#define DDRPHY_RDIMMCR0_RC3_MASK (0xF000U)
#define DDRPHY_RDIMMCR0_RC3_SHIFT (12U)
#define DDRPHY_RDIMMCR0_RC3_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC3_MASK) >> DDRPHY_RDIMMCR0_RC3_SHIFT)

/*
 * RC2 (R)
 *
 * Control Word 2 (Timing Control Word): Bit definitions are:
 * RC2[0]: 0 = Standard (1/2 clock) pre-launch, 1 = Prelaunch controlled by RC12. RC2[1]: 0 = Reserved.
 * RC2[2]: 0 = 100 Ohm input bus termination, 1 = 150 Ohm input bus termination. RC2[3]: 0 = Operation frequency band 1, 1 = Test mode frequency band 2.
 */
#define DDRPHY_RDIMMCR0_RC2_MASK (0xF00U)
#define DDRPHY_RDIMMCR0_RC2_SHIFT (8U)
#define DDRPHY_RDIMMCR0_RC2_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC2_MASK) >> DDRPHY_RDIMMCR0_RC2_SHIFT)

/*
 * RC1 (R)
 *
 * Control Word 1 (Clock Driver Enable Control Word): Bit definitions are: RC1[0]: 0 = Y0/Y0# clock enabled, 1 = Y0/Y0# clock disabled.
 * RC1[1]: 0 = Y1/Y1# clock enabled, 1 = Y1/Y1# clock disabled. RC1[2]: 0 = Y2/Y2# clock enabled, 1 = Y2/Y2# clock disabled. RC1[3]: 0 = Y3/Y3# clock enabled, 1 = Y3/Y3# clock disabled.
 */
#define DDRPHY_RDIMMCR0_RC1_MASK (0xF0U)
#define DDRPHY_RDIMMCR0_RC1_SHIFT (4U)
#define DDRPHY_RDIMMCR0_RC1_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC1_MASK) >> DDRPHY_RDIMMCR0_RC1_SHIFT)

/*
 * RC0 (R)
 *
 * Control Word 0 (Global Features Control Word): Bit definitions are: RC0[0]: 0 = Output inversion enabled, 1 = Output inversion disabled. RC0[1]: 0 = Floating outputs disabled, 1 = Floating outputs enabled. RC0[2]: 0 = A outputs enabled, 1 = A outputs disabled.
 * RC0[3]: 0 = B outputs enabled, 1 = B outputs disabled.
 */
#define DDRPHY_RDIMMCR0_RC0_MASK (0xFU)
#define DDRPHY_RDIMMCR0_RC0_SHIFT (0U)
#define DDRPHY_RDIMMCR0_RC0_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR0_RC0_MASK) >> DDRPHY_RDIMMCR0_RC0_SHIFT)

/* Bitfield definition for register: RDIMMCR1 */
/*
 * RC15 (R)
 *
 * Control Word 15: Reserved for future use.
 */
#define DDRPHY_RDIMMCR1_RC15_MASK (0xF0000000UL)
#define DDRPHY_RDIMMCR1_RC15_SHIFT (28U)
#define DDRPHY_RDIMMCR1_RC15_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC15_MASK) >> DDRPHY_RDIMMCR1_RC15_SHIFT)

/*
 * RC14 (R)
 *
 * Control Word 14: Reserved for future use.
 */
#define DDRPHY_RDIMMCR1_RC14_MASK (0xF000000UL)
#define DDRPHY_RDIMMCR1_RC14_SHIFT (24U)
#define DDRPHY_RDIMMCR1_RC14_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC14_MASK) >> DDRPHY_RDIMMCR1_RC14_SHIFT)

/*
 * RC13 (R)
 *
 * Control Word 13: Reserved for future use.
 */
#define DDRPHY_RDIMMCR1_RC13_MASK (0xF00000UL)
#define DDRPHY_RDIMMCR1_RC13_SHIFT (20U)
#define DDRPHY_RDIMMCR1_RC13_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC13_MASK) >> DDRPHY_RDIMMCR1_RC13_SHIFT)

/*
 * RC12 (R)
 *
 * Control Word 12: Reserved for future use.
 */
#define DDRPHY_RDIMMCR1_RC12_MASK (0xF0000UL)
#define DDRPHY_RDIMMCR1_RC12_SHIFT (16U)
#define DDRPHY_RDIMMCR1_RC12_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC12_MASK) >> DDRPHY_RDIMMCR1_RC12_SHIFT)

/*
 * RC11 (R)
 *
 * Control Word 11 (Operating Voltage VDD Control Word): RC10[1:0] is VDD operating voltage setting as follows: 00 = DDR3 1.5V mode
 * 01 = DDR3L 1.35V mode
 * 10 = Reserved
 * 11 = Reserved RC10[3:2]: Reserved.
 */
#define DDRPHY_RDIMMCR1_RC11_MASK (0xF000U)
#define DDRPHY_RDIMMCR1_RC11_SHIFT (12U)
#define DDRPHY_RDIMMCR1_RC11_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC11_MASK) >> DDRPHY_RDIMMCR1_RC11_SHIFT)

/*
 * RC10 (R)
 *
 * Control Word 10 (RDIMM Operating Speed Control Word): RC10[2:0] is RDIMM operating speed setting as follows: 000 = DDR3/DDR3L-800
 * 001 = DDR3/DDR3L-1066
 * 010 = DDR3/DDR3L-1333
 * 011 = DDR3/DDR3L-1600
 * 100 = Reserved
 * 101 = Reserved
 * 110 = Reserved
 * 111 = Reserved RC10[3]: Don’t care.
 */
#define DDRPHY_RDIMMCR1_RC10_MASK (0xF00U)
#define DDRPHY_RDIMMCR1_RC10_SHIFT (8U)
#define DDRPHY_RDIMMCR1_RC10_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC10_MASK) >> DDRPHY_RDIMMCR1_RC10_SHIFT)

/*
 * RC9 (R)
 *
 * Control Word 9 (Power Saving Settings Control Word): Bit definitions are: RC9[0]: 0 = Floating outputs as defined in RC0, 1 = Weak drive enabled. RC9[1]: 0 = Reserved.
 * RC9[2]: 0 = CKE power down with IBT ON, QxODT is a function of DxODT, 1 = CKE power down with IBT off, QxODT held LOW. RC9[2] is valid only when RC9[3] is 1.
 * RC9[3]: 0 = CKE power down mode disabled, 1 = CKE power down mode enabled.
 */
#define DDRPHY_RDIMMCR1_RC9_MASK (0xF0U)
#define DDRPHY_RDIMMCR1_RC9_SHIFT (4U)
#define DDRPHY_RDIMMCR1_RC9_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC9_MASK) >> DDRPHY_RDIMMCR1_RC9_SHIFT)

/*
 * RC8 (R)
 *
 * Control Word 8 (Additional Input Bus Termination Setting Control Word): RC8[2:0] is Input Bus Termination (IBT) setting as follows:
 * 000 = IBT as defined in RC2. 001 = Reserved
 * 010 = 200 Ohm
 * 011 = Reserved
 * 100 = 300 Ohm
 * 101 = Reserved
 * 110 = Reserved
 * 111 = Off
 * RC8[3]: 0 = IBT off when MIRROR is HIGH, 1 = IBT on when MIRROR is high
 */
#define DDRPHY_RDIMMCR1_RC8_MASK (0xFU)
#define DDRPHY_RDIMMCR1_RC8_SHIFT (0U)
#define DDRPHY_RDIMMCR1_RC8_GET(x) (((uint32_t)(x) & DDRPHY_RDIMMCR1_RC8_MASK) >> DDRPHY_RDIMMCR1_RC8_SHIFT)

/* Bitfield definition for register: DCUAR */
/*
 * ATYPE (R/W)
 *
 * Access Type: Specifies the type of access to be performed using this address. Valid values are:
 * 0 = Write access 1 = Read access
 */
#define DDRPHY_DCUAR_ATYPE_MASK (0x800U)
#define DDRPHY_DCUAR_ATYPE_SHIFT (11U)
#define DDRPHY_DCUAR_ATYPE_SET(x) (((uint32_t)(x) << DDRPHY_DCUAR_ATYPE_SHIFT) & DDRPHY_DCUAR_ATYPE_MASK)
#define DDRPHY_DCUAR_ATYPE_GET(x) (((uint32_t)(x) & DDRPHY_DCUAR_ATYPE_MASK) >> DDRPHY_DCUAR_ATYPE_SHIFT)

/*
 * INCA (R/W)
 *
 * Increment Address: Specifies, if set, that the cache address specified in WADDR and SADDR should be automatically incremented after each access of the cache. The increment happens in such a way that all the slices of a selected word are first accessed before going to the next word.
 */
#define DDRPHY_DCUAR_INCA_MASK (0x400U)
#define DDRPHY_DCUAR_INCA_SHIFT (10U)
#define DDRPHY_DCUAR_INCA_SET(x) (((uint32_t)(x) << DDRPHY_DCUAR_INCA_SHIFT) & DDRPHY_DCUAR_INCA_MASK)
#define DDRPHY_DCUAR_INCA_GET(x) (((uint32_t)(x) & DDRPHY_DCUAR_INCA_MASK) >> DDRPHY_DCUAR_INCA_SHIFT)

/*
 * CSEL (R/W)
 *
 * Cache Select: Selects the cache to be accessed. Valid values are: 00 = Command cache
 * 01 = Expected data cache 10 = Read data cache
 * 11 = Reserved
 */
#define DDRPHY_DCUAR_CSEL_MASK (0x300U)
#define DDRPHY_DCUAR_CSEL_SHIFT (8U)
#define DDRPHY_DCUAR_CSEL_SET(x) (((uint32_t)(x) << DDRPHY_DCUAR_CSEL_SHIFT) & DDRPHY_DCUAR_CSEL_MASK)
#define DDRPHY_DCUAR_CSEL_GET(x) (((uint32_t)(x) & DDRPHY_DCUAR_CSEL_MASK) >> DDRPHY_DCUAR_CSEL_SHIFT)

/*
 * CSADDR (R/W)
 *
 * Cache Slice Address: Address of the cache slice to be accessed.
 */
#define DDRPHY_DCUAR_CSADDR_MASK (0xF0U)
#define DDRPHY_DCUAR_CSADDR_SHIFT (4U)
#define DDRPHY_DCUAR_CSADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCUAR_CSADDR_SHIFT) & DDRPHY_DCUAR_CSADDR_MASK)
#define DDRPHY_DCUAR_CSADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCUAR_CSADDR_MASK) >> DDRPHY_DCUAR_CSADDR_SHIFT)

/*
 * CWADDR (R/W)
 *
 * Cache Word Address: Address of the cache word to be accessed.
 */
#define DDRPHY_DCUAR_CWADDR_MASK (0xFU)
#define DDRPHY_DCUAR_CWADDR_SHIFT (0U)
#define DDRPHY_DCUAR_CWADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCUAR_CWADDR_SHIFT) & DDRPHY_DCUAR_CWADDR_MASK)
#define DDRPHY_DCUAR_CWADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCUAR_CWADDR_MASK) >> DDRPHY_DCUAR_CWADDR_SHIFT)

/* Bitfield definition for register: DCUDR */
/*
 * CDATA (R/W)
 *
 * Cache Data: Data to be written to or read from a cache. This data corresponds to the cache word slice specified by the DCU Address Register.
 */
#define DDRPHY_DCUDR_CDATA_MASK (0xFFFFFFFFUL)
#define DDRPHY_DCUDR_CDATA_SHIFT (0U)
#define DDRPHY_DCUDR_CDATA_SET(x) (((uint32_t)(x) << DDRPHY_DCUDR_CDATA_SHIFT) & DDRPHY_DCUDR_CDATA_MASK)
#define DDRPHY_DCUDR_CDATA_GET(x) (((uint32_t)(x) & DDRPHY_DCUDR_CDATA_MASK) >> DDRPHY_DCUDR_CDATA_SHIFT)

/* Bitfield definition for register: DCURR */
/*
 * XCEN (R/W)
 *
 * Expected Compare Enable: Indicates, if set, that read data coming back from the SDRAM should be should be compared with the expected data.
 */
#define DDRPHY_DCURR_XCEN_MASK (0x800000UL)
#define DDRPHY_DCURR_XCEN_SHIFT (23U)
#define DDRPHY_DCURR_XCEN_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_XCEN_SHIFT) & DDRPHY_DCURR_XCEN_MASK)
#define DDRPHY_DCURR_XCEN_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_XCEN_MASK) >> DDRPHY_DCURR_XCEN_SHIFT)

/*
 * RCEN (R/W)
 *
 * Read Capture Enable: Indicates, if set, that read data coming back from the SDRAM should be captured into the read data cache.
 */
#define DDRPHY_DCURR_RCEN_MASK (0x400000UL)
#define DDRPHY_DCURR_RCEN_SHIFT (22U)
#define DDRPHY_DCURR_RCEN_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_RCEN_SHIFT) & DDRPHY_DCURR_RCEN_MASK)
#define DDRPHY_DCURR_RCEN_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_RCEN_MASK) >> DDRPHY_DCURR_RCEN_SHIFT)

/*
 * SCOF (R/W)
 *
 * Stop Capture On Full: Specifies, if set, that the capture of read data should stop when the capture cache is full.
 */
#define DDRPHY_DCURR_SCOF_MASK (0x200000UL)
#define DDRPHY_DCURR_SCOF_SHIFT (21U)
#define DDRPHY_DCURR_SCOF_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_SCOF_SHIFT) & DDRPHY_DCURR_SCOF_MASK)
#define DDRPHY_DCURR_SCOF_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_SCOF_MASK) >> DDRPHY_DCURR_SCOF_SHIFT)

/*
 * SONF (R/W)
 *
 * Stop On Nth Fail: Specifies, if set, that the execution of commands and the capture of read data should stop when there are N read data failures. The number of failures is specified by NFAIL. Otherwise commands execute until the end of the program or until manually stopped using a STOP command.
 */
#define DDRPHY_DCURR_SONF_MASK (0x100000UL)
#define DDRPHY_DCURR_SONF_SHIFT (20U)
#define DDRPHY_DCURR_SONF_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_SONF_SHIFT) & DDRPHY_DCURR_SONF_MASK)
#define DDRPHY_DCURR_SONF_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_SONF_MASK) >> DDRPHY_DCURR_SONF_SHIFT)

/*
 * NFAIL (R/W)
 *
 * Number of Failures: Specifies the number of failures after which the execution of commands and the capture of read data should stop if SONF bit of this register is set. Execution of commands and the capture of read data will stop after (NFAIL+1) failures if SONF is set.
 * Valid values are from 0 to 254.
 */
#define DDRPHY_DCURR_NFAIL_MASK (0xFF000UL)
#define DDRPHY_DCURR_NFAIL_SHIFT (12U)
#define DDRPHY_DCURR_NFAIL_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_NFAIL_SHIFT) & DDRPHY_DCURR_NFAIL_MASK)
#define DDRPHY_DCURR_NFAIL_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_NFAIL_MASK) >> DDRPHY_DCURR_NFAIL_SHIFT)

/*
 * EADDR (R/W)
 *
 * End Address: Cache word address where the execution of command should end.
 */
#define DDRPHY_DCURR_EADDR_MASK (0xF00U)
#define DDRPHY_DCURR_EADDR_SHIFT (8U)
#define DDRPHY_DCURR_EADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_EADDR_SHIFT) & DDRPHY_DCURR_EADDR_MASK)
#define DDRPHY_DCURR_EADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_EADDR_MASK) >> DDRPHY_DCURR_EADDR_SHIFT)

/*
 * SADDR (R/W)
 *
 * Start Address: Cache word address where the execution of commands should begin.
 */
#define DDRPHY_DCURR_SADDR_MASK (0xF0U)
#define DDRPHY_DCURR_SADDR_SHIFT (4U)
#define DDRPHY_DCURR_SADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_SADDR_SHIFT) & DDRPHY_DCURR_SADDR_MASK)
#define DDRPHY_DCURR_SADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_SADDR_MASK) >> DDRPHY_DCURR_SADDR_SHIFT)

/*
 * DINST (R/W)
 *
 * DCU Instruction: Selects the DCU command to be executed: Valid values are: 0000 = NOP: No operation
 * 0001 = Run: Triggers the execution of commands in the command cache. 0010 = Stop: Stops the execution of commands in the command cache.
 * 0011 = Stop Loop: Stops the execution of an infinite loop in the command cache. 0100 = Reset: Resets all DCU run time registers. See “DCU Status” on page 255 for details.
 * 0101 – 1111 Reserved
 */
#define DDRPHY_DCURR_DINST_MASK (0xFU)
#define DDRPHY_DCURR_DINST_SHIFT (0U)
#define DDRPHY_DCURR_DINST_SET(x) (((uint32_t)(x) << DDRPHY_DCURR_DINST_SHIFT) & DDRPHY_DCURR_DINST_MASK)
#define DDRPHY_DCURR_DINST_GET(x) (((uint32_t)(x) & DDRPHY_DCURR_DINST_MASK) >> DDRPHY_DCURR_DINST_SHIFT)

/* Bitfield definition for register: DCULR */
/*
 * XLEADDR (R/W)
 *
 * Expected Data Loop End Address: The last expected data cache word address that contains valid expected data. Expected data should looped between 0 and this address.
 * XLEADDR field uses only the following bits based on the cache depth:
 * DCU expected data cache = 4, XLEADDR[1:0]
 * DCU expected data cache = 8, XLEADDR[2:0]
 * DCU expected data cache = 16, XLEADDR[3:0]
 */
#define DDRPHY_DCULR_XLEADDR_MASK (0xF0000000UL)
#define DDRPHY_DCULR_XLEADDR_SHIFT (28U)
#define DDRPHY_DCULR_XLEADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_XLEADDR_SHIFT) & DDRPHY_DCULR_XLEADDR_MASK)
#define DDRPHY_DCULR_XLEADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_XLEADDR_MASK) >> DDRPHY_DCULR_XLEADDR_SHIFT)

/*
 * IDA (R/W)
 *
 * Increment DRAM Address: Indicates, if set, that DRAM addresses should be incremented every time a DRAM read/write command inside the loop is executed.
 */
#define DDRPHY_DCULR_IDA_MASK (0x20000UL)
#define DDRPHY_DCULR_IDA_SHIFT (17U)
#define DDRPHY_DCULR_IDA_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_IDA_SHIFT) & DDRPHY_DCULR_IDA_MASK)
#define DDRPHY_DCULR_IDA_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_IDA_MASK) >> DDRPHY_DCULR_IDA_SHIFT)

/*
 * LINF (R/W)
 *
 * Loop Infinite: Indicates, if set, that the loop should be executed indefinitely until stopped by the STOP command. Otherwise the loop is execute LCNT times.
 */
#define DDRPHY_DCULR_LINF_MASK (0x10000UL)
#define DDRPHY_DCULR_LINF_SHIFT (16U)
#define DDRPHY_DCULR_LINF_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_LINF_SHIFT) & DDRPHY_DCULR_LINF_MASK)
#define DDRPHY_DCULR_LINF_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_LINF_MASK) >> DDRPHY_DCULR_LINF_SHIFT)

/*
 * LCNT (R/W)
 *
 * Loop Count: The number of times that the loop should be executed if LINF is not set.
 */
#define DDRPHY_DCULR_LCNT_MASK (0xFF00U)
#define DDRPHY_DCULR_LCNT_SHIFT (8U)
#define DDRPHY_DCULR_LCNT_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_LCNT_SHIFT) & DDRPHY_DCULR_LCNT_MASK)
#define DDRPHY_DCULR_LCNT_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_LCNT_MASK) >> DDRPHY_DCULR_LCNT_SHIFT)

/*
 * LEADDR (R/W)
 *
 * Loop End Address: Command cache word address where the loop should end.
 */
#define DDRPHY_DCULR_LEADDR_MASK (0xF0U)
#define DDRPHY_DCULR_LEADDR_SHIFT (4U)
#define DDRPHY_DCULR_LEADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_LEADDR_SHIFT) & DDRPHY_DCULR_LEADDR_MASK)
#define DDRPHY_DCULR_LEADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_LEADDR_MASK) >> DDRPHY_DCULR_LEADDR_SHIFT)

/*
 * LSADDR (R/W)
 *
 * Loop Start Address: Command cache word address where the loop should start.
 */
#define DDRPHY_DCULR_LSADDR_MASK (0xFU)
#define DDRPHY_DCULR_LSADDR_SHIFT (0U)
#define DDRPHY_DCULR_LSADDR_SET(x) (((uint32_t)(x) << DDRPHY_DCULR_LSADDR_SHIFT) & DDRPHY_DCULR_LSADDR_MASK)
#define DDRPHY_DCULR_LSADDR_GET(x) (((uint32_t)(x) & DDRPHY_DCULR_LSADDR_MASK) >> DDRPHY_DCULR_LSADDR_SHIFT)

/* Bitfield definition for register: DCUGCR */
/*
 * RCSW (R/W)
 *
 * Read Capture Start Word: The capture and compare of read data should start after Nth word. For example setting this value to 12 will skip the first 12 read data.
 */
#define DDRPHY_DCUGCR_RCSW_MASK (0xFFFFU)
#define DDRPHY_DCUGCR_RCSW_SHIFT (0U)
#define DDRPHY_DCUGCR_RCSW_SET(x) (((uint32_t)(x) << DDRPHY_DCUGCR_RCSW_SHIFT) & DDRPHY_DCUGCR_RCSW_MASK)
#define DDRPHY_DCUGCR_RCSW_GET(x) (((uint32_t)(x) & DDRPHY_DCUGCR_RCSW_MASK) >> DDRPHY_DCUGCR_RCSW_SHIFT)

/* Bitfield definition for register: DCUTPR */
/*
 * TDCUT3 (R/W)
 *
 * DCU Generic Timing Parameter 3
 */
#define DDRPHY_DCUTPR_TDCUT3_MASK (0xFF000000UL)
#define DDRPHY_DCUTPR_TDCUT3_SHIFT (24U)
#define DDRPHY_DCUTPR_TDCUT3_SET(x) (((uint32_t)(x) << DDRPHY_DCUTPR_TDCUT3_SHIFT) & DDRPHY_DCUTPR_TDCUT3_MASK)
#define DDRPHY_DCUTPR_TDCUT3_GET(x) (((uint32_t)(x) & DDRPHY_DCUTPR_TDCUT3_MASK) >> DDRPHY_DCUTPR_TDCUT3_SHIFT)

/*
 * TDCUT2 (R/W)
 *
 * DCU Generic Timing Parameter 2
 */
#define DDRPHY_DCUTPR_TDCUT2_MASK (0xFF0000UL)
#define DDRPHY_DCUTPR_TDCUT2_SHIFT (16U)
#define DDRPHY_DCUTPR_TDCUT2_SET(x) (((uint32_t)(x) << DDRPHY_DCUTPR_TDCUT2_SHIFT) & DDRPHY_DCUTPR_TDCUT2_MASK)
#define DDRPHY_DCUTPR_TDCUT2_GET(x) (((uint32_t)(x) & DDRPHY_DCUTPR_TDCUT2_MASK) >> DDRPHY_DCUTPR_TDCUT2_SHIFT)

/*
 * TDCUT1 (R/W)
 *
 * DCU Generic Timing Parameter 1
 */
#define DDRPHY_DCUTPR_TDCUT1_MASK (0xFF00U)
#define DDRPHY_DCUTPR_TDCUT1_SHIFT (8U)
#define DDRPHY_DCUTPR_TDCUT1_SET(x) (((uint32_t)(x) << DDRPHY_DCUTPR_TDCUT1_SHIFT) & DDRPHY_DCUTPR_TDCUT1_MASK)
#define DDRPHY_DCUTPR_TDCUT1_GET(x) (((uint32_t)(x) & DDRPHY_DCUTPR_TDCUT1_MASK) >> DDRPHY_DCUTPR_TDCUT1_SHIFT)

/*
 * TDCUT0 (R/W)
 *
 * DCU Generic Timing Parameter 0
 */
#define DDRPHY_DCUTPR_TDCUT0_MASK (0xFFU)
#define DDRPHY_DCUTPR_TDCUT0_SHIFT (0U)
#define DDRPHY_DCUTPR_TDCUT0_SET(x) (((uint32_t)(x) << DDRPHY_DCUTPR_TDCUT0_SHIFT) & DDRPHY_DCUTPR_TDCUT0_MASK)
#define DDRPHY_DCUTPR_TDCUT0_GET(x) (((uint32_t)(x) & DDRPHY_DCUTPR_TDCUT0_MASK) >> DDRPHY_DCUTPR_TDCUT0_SHIFT)

/* Bitfield definition for register: DCUSR0 */
/*
 * CFULL (R)
 *
 * Capture Full: Indicates, if set, that the capture cache is full.
 */
#define DDRPHY_DCUSR0_CFULL_MASK (0x4U)
#define DDRPHY_DCUSR0_CFULL_SHIFT (2U)
#define DDRPHY_DCUSR0_CFULL_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR0_CFULL_MASK) >> DDRPHY_DCUSR0_CFULL_SHIFT)

/*
 * CFAIL (R)
 *
 * Capture Fail: Indicates, if set, that at least one read data word has failed.
 */
#define DDRPHY_DCUSR0_CFAIL_MASK (0x2U)
#define DDRPHY_DCUSR0_CFAIL_SHIFT (1U)
#define DDRPHY_DCUSR0_CFAIL_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR0_CFAIL_MASK) >> DDRPHY_DCUSR0_CFAIL_SHIFT)

/*
 * RDONE (R)
 *
 * Run Done: Indicates, if set, that the DCU has finished executing the commands in the command cache. This bit is also set to indicate that a STOP command has successfully been executed and command execution has stopped.
 */
#define DDRPHY_DCUSR0_RDONE_MASK (0x1U)
#define DDRPHY_DCUSR0_RDONE_SHIFT (0U)
#define DDRPHY_DCUSR0_RDONE_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR0_RDONE_MASK) >> DDRPHY_DCUSR0_RDONE_SHIFT)

/* Bitfield definition for register: DCUSR1 */
/*
 * LPCNT (R)
 *
 * Loop Count: Indicates the value of the loop count. This is useful when the program has stopped because of failures to assess how many reads were executed before first fail.
 */
#define DDRPHY_DCUSR1_LPCNT_MASK (0xFF000000UL)
#define DDRPHY_DCUSR1_LPCNT_SHIFT (24U)
#define DDRPHY_DCUSR1_LPCNT_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR1_LPCNT_MASK) >> DDRPHY_DCUSR1_LPCNT_SHIFT)

/*
 * FLCNT (R)
 *
 * Fail Count: Number of read words that have failed.
 */
#define DDRPHY_DCUSR1_FLCNT_MASK (0xFF0000UL)
#define DDRPHY_DCUSR1_FLCNT_SHIFT (16U)
#define DDRPHY_DCUSR1_FLCNT_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR1_FLCNT_MASK) >> DDRPHY_DCUSR1_FLCNT_SHIFT)

/*
 * RDCNT (R)
 *
 * Read Count: Number of read words returned from the SDRAM.
 */
#define DDRPHY_DCUSR1_RDCNT_MASK (0xFFFFU)
#define DDRPHY_DCUSR1_RDCNT_SHIFT (0U)
#define DDRPHY_DCUSR1_RDCNT_GET(x) (((uint32_t)(x) & DDRPHY_DCUSR1_RDCNT_MASK) >> DDRPHY_DCUSR1_RDCNT_SHIFT)

/* Bitfield definition for register: BISTRR */
/*
 * BCCSEL (R/W)
 *
 * BIST Clock Cycle Select: Selects the clock numbers on which the AC loopback data is written into the FIFO. Data is written into the loopback FIFO once every four clock cycles. Valid values are:
 * 00 = Clock cycle 0, 4, 8, 12, etc.
 * 01 = Clock cycle 1, 5, 9, 13, etc.
 * 10 = Clock cycle 2, 6, 10, 14, etc.
 * 11 = Clock cycle 3, 7, 11, 15, etc.
 */
#define DDRPHY_BISTRR_BCCSEL_MASK (0x6000000UL)
#define DDRPHY_BISTRR_BCCSEL_SHIFT (25U)
#define DDRPHY_BISTRR_BCCSEL_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BCCSEL_SHIFT) & DDRPHY_BISTRR_BCCSEL_MASK)
#define DDRPHY_BISTRR_BCCSEL_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BCCSEL_MASK) >> DDRPHY_BISTRR_BCCSEL_SHIFT)

/*
 * BCKSEL (R/W)
 *
 * BIST CK Select: Selects the CK that should be used to register the AC loopback signals from the I/Os. Valid values are:
 * 00 = CK[0]
 * 01 = CK[1]
 * 10 = CK[2]
 * 11 = Reserved
 */
#define DDRPHY_BISTRR_BCKSEL_MASK (0x1800000UL)
#define DDRPHY_BISTRR_BCKSEL_SHIFT (23U)
#define DDRPHY_BISTRR_BCKSEL_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BCKSEL_SHIFT) & DDRPHY_BISTRR_BCKSEL_MASK)
#define DDRPHY_BISTRR_BCKSEL_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BCKSEL_MASK) >> DDRPHY_BISTRR_BCKSEL_SHIFT)

/*
 * BDXSEL (R/W)
 *
 * BIST DATX8 Select: Select the byte lane for comparison of loopback/read data. Valid values are 0 to 8.
 */
#define DDRPHY_BISTRR_BDXSEL_MASK (0x780000UL)
#define DDRPHY_BISTRR_BDXSEL_SHIFT (19U)
#define DDRPHY_BISTRR_BDXSEL_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BDXSEL_SHIFT) & DDRPHY_BISTRR_BDXSEL_MASK)
#define DDRPHY_BISTRR_BDXSEL_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BDXSEL_MASK) >> DDRPHY_BISTRR_BDXSEL_SHIFT)

/*
 * BDPAT (R/W)
 *
 * BIST Data Pattern: Selects the data pattern used during BIST. Valid values are: 00 = Walking 0
 * 01 = Walking 1
 * 10 = LFSR-based pseudo-random
 * 11 = User programmable (Not valid for AC loopback).
 */
#define DDRPHY_BISTRR_BDPAT_MASK (0x60000UL)
#define DDRPHY_BISTRR_BDPAT_SHIFT (17U)
#define DDRPHY_BISTRR_BDPAT_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BDPAT_SHIFT) & DDRPHY_BISTRR_BDPAT_MASK)
#define DDRPHY_BISTRR_BDPAT_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BDPAT_MASK) >> DDRPHY_BISTRR_BDPAT_SHIFT)

/*
 * BDMEN (R/W)
 *
 * BIST Data Mask Enable: Enables, if set, that the data mask BIST should be included in the BIST run, i.e. data pattern generated and loopback data compared. This is valid only for loopback mode.
 */
#define DDRPHY_BISTRR_BDMEN_MASK (0x10000UL)
#define DDRPHY_BISTRR_BDMEN_SHIFT (16U)
#define DDRPHY_BISTRR_BDMEN_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BDMEN_SHIFT) & DDRPHY_BISTRR_BDMEN_MASK)
#define DDRPHY_BISTRR_BDMEN_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BDMEN_MASK) >> DDRPHY_BISTRR_BDMEN_SHIFT)

/*
 * BACEN (R/W)
 *
 * BIST AC Enable: Enables the running of BIST on the address/command lane PHY. This bit is exclusive with BDXEN, i.e. both cannot be set to ‘1’ at the same time.
 */
#define DDRPHY_BISTRR_BACEN_MASK (0x8000U)
#define DDRPHY_BISTRR_BACEN_SHIFT (15U)
#define DDRPHY_BISTRR_BACEN_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BACEN_SHIFT) & DDRPHY_BISTRR_BACEN_MASK)
#define DDRPHY_BISTRR_BACEN_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BACEN_MASK) >> DDRPHY_BISTRR_BACEN_SHIFT)

/*
 * BDXEN (R/W)
 *
 * BIST DATX8 Enable: Enables the running of BIST on the data byte lane PHYs. This bit is exclusive with BACEN, i.e. both cannot be set to ‘1’ at the same time.
 */
#define DDRPHY_BISTRR_BDXEN_MASK (0x4000U)
#define DDRPHY_BISTRR_BDXEN_SHIFT (14U)
#define DDRPHY_BISTRR_BDXEN_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BDXEN_SHIFT) & DDRPHY_BISTRR_BDXEN_MASK)
#define DDRPHY_BISTRR_BDXEN_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BDXEN_MASK) >> DDRPHY_BISTRR_BDXEN_SHIFT)

/*
 * BSONF (R/W)
 *
 * BIST Stop On Nth Fail: Specifies, if set, that the BIST should stop when an nth data word or address/command comparison error has been encountered.
 */
#define DDRPHY_BISTRR_BSONF_MASK (0x2000U)
#define DDRPHY_BISTRR_BSONF_SHIFT (13U)
#define DDRPHY_BISTRR_BSONF_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BSONF_SHIFT) & DDRPHY_BISTRR_BSONF_MASK)
#define DDRPHY_BISTRR_BSONF_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BSONF_MASK) >> DDRPHY_BISTRR_BSONF_SHIFT)

/*
 * NFAIL (R/W)
 *
 * Number of Failures: Specifies the number of failures after which the execution of commands and the capture of read data should stop if BSONF bit of this register is set. Execution of commands and the capture of read data will stop after (NFAIL+1) failures if BSONF is set.
 */
#define DDRPHY_BISTRR_NFAIL_MASK (0x1FE0U)
#define DDRPHY_BISTRR_NFAIL_SHIFT (5U)
#define DDRPHY_BISTRR_NFAIL_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_NFAIL_SHIFT) & DDRPHY_BISTRR_NFAIL_MASK)
#define DDRPHY_BISTRR_NFAIL_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_NFAIL_MASK) >> DDRPHY_BISTRR_NFAIL_SHIFT)

/*
 * BINF (R/W)
 *
 * BIST Infinite Run: Specifies, if set, that the BIST should be run indefinitely until when it is either stopped or a failure has been encountered. Otherwise BIST is run until number of BIST words specified in the BISTWCR register has been generated.
 */
#define DDRPHY_BISTRR_BINF_MASK (0x10U)
#define DDRPHY_BISTRR_BINF_SHIFT (4U)
#define DDRPHY_BISTRR_BINF_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BINF_SHIFT) & DDRPHY_BISTRR_BINF_MASK)
#define DDRPHY_BISTRR_BINF_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BINF_MASK) >> DDRPHY_BISTRR_BINF_SHIFT)

/*
 * BMODE (R/W)
 *
 * BIST Mode: Selects the mode in which BIST is run. Valid values are:
 * 0 = Loopback mode: Address, commands and data loop back at the PHY I/Os.
 * 1 = DRAM mode: Address, commands and data go to DRAM for normal memory accesses.
 */
#define DDRPHY_BISTRR_BMODE_MASK (0x8U)
#define DDRPHY_BISTRR_BMODE_SHIFT (3U)
#define DDRPHY_BISTRR_BMODE_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BMODE_SHIFT) & DDRPHY_BISTRR_BMODE_MASK)
#define DDRPHY_BISTRR_BMODE_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BMODE_MASK) >> DDRPHY_BISTRR_BMODE_SHIFT)

/*
 * BINST (R/W)
 *
 * BIST Instruction: Selects the BIST instruction to be executed: Valid values are: 000 = NOP: No operation
 * 001 = Run: Triggers the running of the BIST. 010 = Stop: Stops the running of the BIST.
 * 011 = Reset: Resets all BIST run-time registers, such as error counters. 100 – 111 Reserved
 */
#define DDRPHY_BISTRR_BINST_MASK (0x7U)
#define DDRPHY_BISTRR_BINST_SHIFT (0U)
#define DDRPHY_BISTRR_BINST_SET(x) (((uint32_t)(x) << DDRPHY_BISTRR_BINST_SHIFT) & DDRPHY_BISTRR_BINST_MASK)
#define DDRPHY_BISTRR_BINST_GET(x) (((uint32_t)(x) & DDRPHY_BISTRR_BINST_MASK) >> DDRPHY_BISTRR_BINST_SHIFT)

/* Bitfield definition for register: BISTWCR */
/*
 * BWCNT (R/W)
 *
 * BIST Word Count: Indicates the number of words to generate during BIST. This must be a multiple of DRAM burst length (BL) divided by 2, e.g. for BL=8, valid values are 4, 8, 12, 16, and so on.
 */
#define DDRPHY_BISTWCR_BWCNT_MASK (0xFFFFU)
#define DDRPHY_BISTWCR_BWCNT_SHIFT (0U)
#define DDRPHY_BISTWCR_BWCNT_SET(x) (((uint32_t)(x) << DDRPHY_BISTWCR_BWCNT_SHIFT) & DDRPHY_BISTWCR_BWCNT_MASK)
#define DDRPHY_BISTWCR_BWCNT_GET(x) (((uint32_t)(x) & DDRPHY_BISTWCR_BWCNT_MASK) >> DDRPHY_BISTWCR_BWCNT_SHIFT)

/* Bitfield definition for register: BISTMSKR0 */
/*
 * ODTMSK (R/W)
 *
 * Mask bit for each of the up to 4 ODT bits.
 */
#define DDRPHY_BISTMSKR0_ODTMSK_MASK (0xF0000000UL)
#define DDRPHY_BISTMSKR0_ODTMSK_SHIFT (28U)
#define DDRPHY_BISTMSKR0_ODTMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_ODTMSK_SHIFT) & DDRPHY_BISTMSKR0_ODTMSK_MASK)
#define DDRPHY_BISTMSKR0_ODTMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_ODTMSK_MASK) >> DDRPHY_BISTMSKR0_ODTMSK_SHIFT)

/*
 * CSMSK (R/W)
 *
 * Mask bit for each of the up to 4 CS# bits.
 */
#define DDRPHY_BISTMSKR0_CSMSK_MASK (0xF000000UL)
#define DDRPHY_BISTMSKR0_CSMSK_SHIFT (24U)
#define DDRPHY_BISTMSKR0_CSMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_CSMSK_SHIFT) & DDRPHY_BISTMSKR0_CSMSK_MASK)
#define DDRPHY_BISTMSKR0_CSMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_CSMSK_MASK) >> DDRPHY_BISTMSKR0_CSMSK_SHIFT)

/*
 * CKEMSK (R/W)
 *
 * Mask bit for each of the up to 4 CKE bits.
 */
#define DDRPHY_BISTMSKR0_CKEMSK_MASK (0xF00000UL)
#define DDRPHY_BISTMSKR0_CKEMSK_SHIFT (20U)
#define DDRPHY_BISTMSKR0_CKEMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_CKEMSK_SHIFT) & DDRPHY_BISTMSKR0_CKEMSK_MASK)
#define DDRPHY_BISTMSKR0_CKEMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_CKEMSK_MASK) >> DDRPHY_BISTMSKR0_CKEMSK_SHIFT)

/*
 * WEMSK (R/W)
 *
 * Mask bit for the WE#.
 */
#define DDRPHY_BISTMSKR0_WEMSK_MASK (0x80000UL)
#define DDRPHY_BISTMSKR0_WEMSK_SHIFT (19U)
#define DDRPHY_BISTMSKR0_WEMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_WEMSK_SHIFT) & DDRPHY_BISTMSKR0_WEMSK_MASK)
#define DDRPHY_BISTMSKR0_WEMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_WEMSK_MASK) >> DDRPHY_BISTMSKR0_WEMSK_SHIFT)

/*
 * BAMSK (R/W)
 *
 * Mask bit for each of the up to 3 bank address bits.
 */
#define DDRPHY_BISTMSKR0_BAMSK_MASK (0x70000UL)
#define DDRPHY_BISTMSKR0_BAMSK_SHIFT (16U)
#define DDRPHY_BISTMSKR0_BAMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_BAMSK_SHIFT) & DDRPHY_BISTMSKR0_BAMSK_MASK)
#define DDRPHY_BISTMSKR0_BAMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_BAMSK_MASK) >> DDRPHY_BISTMSKR0_BAMSK_SHIFT)

/*
 * AMSK (R/W)
 *
 * Mask bit for each of the up to 16 address bits.
 */
#define DDRPHY_BISTMSKR0_AMSK_MASK (0xFFFFU)
#define DDRPHY_BISTMSKR0_AMSK_SHIFT (0U)
#define DDRPHY_BISTMSKR0_AMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR0_AMSK_SHIFT) & DDRPHY_BISTMSKR0_AMSK_MASK)
#define DDRPHY_BISTMSKR0_AMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR0_AMSK_MASK) >> DDRPHY_BISTMSKR0_AMSK_SHIFT)

/* Bitfield definition for register: BISTMSKR1 */
/*
 * DMMSK (R/W)
 *
 * Mask bit for the data mask (DM) bit.
 */
#define DDRPHY_BISTMSKR1_DMMSK_MASK (0xF0000000UL)
#define DDRPHY_BISTMSKR1_DMMSK_SHIFT (28U)
#define DDRPHY_BISTMSKR1_DMMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR1_DMMSK_SHIFT) & DDRPHY_BISTMSKR1_DMMSK_MASK)
#define DDRPHY_BISTMSKR1_DMMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR1_DMMSK_MASK) >> DDRPHY_BISTMSKR1_DMMSK_SHIFT)

/*
 * PARMSK (R/W)
 *
 * Mask bit for the PAR_IN. Only for DIMM parity support and only if the design is compiled for less than 3 ranks.
 */
#define DDRPHY_BISTMSKR1_PARMSK_MASK (0x8000000UL)
#define DDRPHY_BISTMSKR1_PARMSK_SHIFT (27U)
#define DDRPHY_BISTMSKR1_PARMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR1_PARMSK_SHIFT) & DDRPHY_BISTMSKR1_PARMSK_MASK)
#define DDRPHY_BISTMSKR1_PARMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR1_PARMSK_MASK) >> DDRPHY_BISTMSKR1_PARMSK_SHIFT)

/*
 * CASMSK (R/W)
 *
 * Mask bit for the CAS.
 */
#define DDRPHY_BISTMSKR1_CASMSK_MASK (0x2U)
#define DDRPHY_BISTMSKR1_CASMSK_SHIFT (1U)
#define DDRPHY_BISTMSKR1_CASMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR1_CASMSK_SHIFT) & DDRPHY_BISTMSKR1_CASMSK_MASK)
#define DDRPHY_BISTMSKR1_CASMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR1_CASMSK_MASK) >> DDRPHY_BISTMSKR1_CASMSK_SHIFT)

/*
 * RASMSK (R/W)
 *
 * Mask bit for the RAS.
 */
#define DDRPHY_BISTMSKR1_RASMSK_MASK (0x1U)
#define DDRPHY_BISTMSKR1_RASMSK_SHIFT (0U)
#define DDRPHY_BISTMSKR1_RASMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR1_RASMSK_SHIFT) & DDRPHY_BISTMSKR1_RASMSK_MASK)
#define DDRPHY_BISTMSKR1_RASMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR1_RASMSK_MASK) >> DDRPHY_BISTMSKR1_RASMSK_SHIFT)

/* Bitfield definition for register: BISTMSKR2 */
/*
 * DQMSK (R/W)
 *
 * Mask bit for each of the 8 data (DQ) bits.
 */
#define DDRPHY_BISTMSKR2_DQMSK_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTMSKR2_DQMSK_SHIFT (0U)
#define DDRPHY_BISTMSKR2_DQMSK_SET(x) (((uint32_t)(x) << DDRPHY_BISTMSKR2_DQMSK_SHIFT) & DDRPHY_BISTMSKR2_DQMSK_MASK)
#define DDRPHY_BISTMSKR2_DQMSK_GET(x) (((uint32_t)(x) & DDRPHY_BISTMSKR2_DQMSK_MASK) >> DDRPHY_BISTMSKR2_DQMSK_SHIFT)

/* Bitfield definition for register: BISTLSR */
/*
 * SEED (R/W)
 *
 * LFSR seed for pseudo-random BIST patterns.
 */
#define DDRPHY_BISTLSR_SEED_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTLSR_SEED_SHIFT (0U)
#define DDRPHY_BISTLSR_SEED_SET(x) (((uint32_t)(x) << DDRPHY_BISTLSR_SEED_SHIFT) & DDRPHY_BISTLSR_SEED_MASK)
#define DDRPHY_BISTLSR_SEED_GET(x) (((uint32_t)(x) & DDRPHY_BISTLSR_SEED_MASK) >> DDRPHY_BISTLSR_SEED_SHIFT)

/* Bitfield definition for register: BISTAR0 */
/*
 * BBANK (R/W)
 *
 * BIST Bank Address: Selects the SDRAM bank address to be used during BIST.
 */
#define DDRPHY_BISTAR0_BBANK_MASK (0x70000000UL)
#define DDRPHY_BISTAR0_BBANK_SHIFT (28U)
#define DDRPHY_BISTAR0_BBANK_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR0_BBANK_SHIFT) & DDRPHY_BISTAR0_BBANK_MASK)
#define DDRPHY_BISTAR0_BBANK_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR0_BBANK_MASK) >> DDRPHY_BISTAR0_BBANK_SHIFT)

/*
 * BROW (R/W)
 *
 * BIST Row Address: Selects the SDRAM row address to be used during BIST.
 */
#define DDRPHY_BISTAR0_BROW_MASK (0xFFFF000UL)
#define DDRPHY_BISTAR0_BROW_SHIFT (12U)
#define DDRPHY_BISTAR0_BROW_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR0_BROW_SHIFT) & DDRPHY_BISTAR0_BROW_MASK)
#define DDRPHY_BISTAR0_BROW_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR0_BROW_MASK) >> DDRPHY_BISTAR0_BROW_SHIFT)

/*
 * BCOL (R/W)
 *
 * BIST Column Address: Selects the SDRAM column address to be used during BIST. The lower bits of this address must be “0000” for BL16, “000” for BL8, “00” for BL4 and “0” for BL2.
 */
#define DDRPHY_BISTAR0_BCOL_MASK (0xFFFU)
#define DDRPHY_BISTAR0_BCOL_SHIFT (0U)
#define DDRPHY_BISTAR0_BCOL_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR0_BCOL_SHIFT) & DDRPHY_BISTAR0_BCOL_MASK)
#define DDRPHY_BISTAR0_BCOL_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR0_BCOL_MASK) >> DDRPHY_BISTAR0_BCOL_SHIFT)

/* Bitfield definition for register: BISTAR1 */
/*
 * BAINC (R/W)
 *
 * BIST Address Increment: Selects the value by which the SDRAM address is incremented for each write/read access. This value must be at the beginning of a burst boundary, i.e. the lower bits must be “0000” for BL16, “000” for BL8, “00” for BL4 and “0” for BL2.
 */
#define DDRPHY_BISTAR1_BAINC_MASK (0xFFF0U)
#define DDRPHY_BISTAR1_BAINC_SHIFT (4U)
#define DDRPHY_BISTAR1_BAINC_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR1_BAINC_SHIFT) & DDRPHY_BISTAR1_BAINC_MASK)
#define DDRPHY_BISTAR1_BAINC_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR1_BAINC_MASK) >> DDRPHY_BISTAR1_BAINC_SHIFT)

/*
 * BMRANK (R/W)
 *
 * BIST Maximum Rank: Specifies the maximum SDRAM rank to be used during BIST. The default value is set to maximum ranks minus 1. Example default shown here is for a 4-rank system
 */
#define DDRPHY_BISTAR1_BMRANK_MASK (0xCU)
#define DDRPHY_BISTAR1_BMRANK_SHIFT (2U)
#define DDRPHY_BISTAR1_BMRANK_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR1_BMRANK_SHIFT) & DDRPHY_BISTAR1_BMRANK_MASK)
#define DDRPHY_BISTAR1_BMRANK_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR1_BMRANK_MASK) >> DDRPHY_BISTAR1_BMRANK_SHIFT)

/*
 * BRANK (R/W)
 *
 * BIST Rank: Selects the SDRAM rank to be used during BIST. Valid values range from 0 to maximum ranks minus 1.
 */
#define DDRPHY_BISTAR1_BRANK_MASK (0x3U)
#define DDRPHY_BISTAR1_BRANK_SHIFT (0U)
#define DDRPHY_BISTAR1_BRANK_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR1_BRANK_SHIFT) & DDRPHY_BISTAR1_BRANK_MASK)
#define DDRPHY_BISTAR1_BRANK_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR1_BRANK_MASK) >> DDRPHY_BISTAR1_BRANK_SHIFT)

/* Bitfield definition for register: BISTAR2 */
/*
 * BMBANK (R/W)
 *
 * BIST Maximum Bank Address: Specifies the maximum SDRAM bank address to be used during BIST before the address increments to the next rank.
 */
#define DDRPHY_BISTAR2_BMBANK_MASK (0x70000000UL)
#define DDRPHY_BISTAR2_BMBANK_SHIFT (28U)
#define DDRPHY_BISTAR2_BMBANK_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR2_BMBANK_SHIFT) & DDRPHY_BISTAR2_BMBANK_MASK)
#define DDRPHY_BISTAR2_BMBANK_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR2_BMBANK_MASK) >> DDRPHY_BISTAR2_BMBANK_SHIFT)

/*
 * BMROW (R/W)
 *
 * BIST Maximum Row Address: Specifies the maximum SDRAM row address to be used during BIST before the address increments to the next bank.
 */
#define DDRPHY_BISTAR2_BMROW_MASK (0xFFFF000UL)
#define DDRPHY_BISTAR2_BMROW_SHIFT (12U)
#define DDRPHY_BISTAR2_BMROW_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR2_BMROW_SHIFT) & DDRPHY_BISTAR2_BMROW_MASK)
#define DDRPHY_BISTAR2_BMROW_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR2_BMROW_MASK) >> DDRPHY_BISTAR2_BMROW_SHIFT)

/*
 * BMCOL (R/W)
 *
 * BIST Maximum Column Address: Specifies the maximum SDRAM column address to be used during BIST before the address increments to the next row.
 */
#define DDRPHY_BISTAR2_BMCOL_MASK (0xFFFU)
#define DDRPHY_BISTAR2_BMCOL_SHIFT (0U)
#define DDRPHY_BISTAR2_BMCOL_SET(x) (((uint32_t)(x) << DDRPHY_BISTAR2_BMCOL_SHIFT) & DDRPHY_BISTAR2_BMCOL_MASK)
#define DDRPHY_BISTAR2_BMCOL_GET(x) (((uint32_t)(x) & DDRPHY_BISTAR2_BMCOL_MASK) >> DDRPHY_BISTAR2_BMCOL_SHIFT)

/* Bitfield definition for register: BISTUDPR */
/*
 * BUDP1 (R/W)
 *
 * BIST User Data Pattern 1: Data to be applied on odd DQ pins during BIST.
 */
#define DDRPHY_BISTUDPR_BUDP1_MASK (0xFFFF0000UL)
#define DDRPHY_BISTUDPR_BUDP1_SHIFT (16U)
#define DDRPHY_BISTUDPR_BUDP1_SET(x) (((uint32_t)(x) << DDRPHY_BISTUDPR_BUDP1_SHIFT) & DDRPHY_BISTUDPR_BUDP1_MASK)
#define DDRPHY_BISTUDPR_BUDP1_GET(x) (((uint32_t)(x) & DDRPHY_BISTUDPR_BUDP1_MASK) >> DDRPHY_BISTUDPR_BUDP1_SHIFT)

/*
 * BUDP0 (R/W)
 *
 * BIST User Data Pattern 0: Data to be applied on even DQ pins during BIST.
 */
#define DDRPHY_BISTUDPR_BUDP0_MASK (0xFFFFU)
#define DDRPHY_BISTUDPR_BUDP0_SHIFT (0U)
#define DDRPHY_BISTUDPR_BUDP0_SET(x) (((uint32_t)(x) << DDRPHY_BISTUDPR_BUDP0_SHIFT) & DDRPHY_BISTUDPR_BUDP0_MASK)
#define DDRPHY_BISTUDPR_BUDP0_GET(x) (((uint32_t)(x) & DDRPHY_BISTUDPR_BUDP0_MASK) >> DDRPHY_BISTUDPR_BUDP0_SHIFT)

/* Bitfield definition for register: BISTGSR */
/*
 * CASBER (R)
 *
 * CAS Bit Error: Indicates the number of bit errors on CAS.
 */
#define DDRPHY_BISTGSR_CASBER_MASK (0xC0000000UL)
#define DDRPHY_BISTGSR_CASBER_SHIFT (30U)
#define DDRPHY_BISTGSR_CASBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_CASBER_MASK) >> DDRPHY_BISTGSR_CASBER_SHIFT)

/*
 * RASBER (R)
 *
 * RAS Bit Error: Indicates the number of bit errors on RAS.
 */
#define DDRPHY_BISTGSR_RASBER_MASK (0x30000000UL)
#define DDRPHY_BISTGSR_RASBER_SHIFT (28U)
#define DDRPHY_BISTGSR_RASBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_RASBER_MASK) >> DDRPHY_BISTGSR_RASBER_SHIFT)

/*
 * DMBER (R)
 *
 * DM Bit Error: Indicates the number of bit errors on data mask (DM) bit. DMBER[1:0] are for even DQS cycles first DM beat, and DMBER[3:2] are for even DQS cycles second DM beat. Similarly, DMBER[5:4] are for odd DQS cycles first DM beat, and DMBER[7:6] are for odd DQS cycles second DM beat.
 */
#define DDRPHY_BISTGSR_DMBER_MASK (0xFF00000UL)
#define DDRPHY_BISTGSR_DMBER_SHIFT (20U)
#define DDRPHY_BISTGSR_DMBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_DMBER_MASK) >> DDRPHY_BISTGSR_DMBER_SHIFT)

/*
 * PARBER (R)
 *
 * PAR_IN Bit Error (DIMM Only): Indicates the number of bit errors on PAR_IN
 */
#define DDRPHY_BISTGSR_PARBER_MASK (0x30000UL)
#define DDRPHY_BISTGSR_PARBER_SHIFT (16U)
#define DDRPHY_BISTGSR_PARBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_PARBER_MASK) >> DDRPHY_BISTGSR_PARBER_SHIFT)

/*
 * BDXERR (R)
 *
 * BIST Data Error: indicates, if set, that there is a data comparison error in the byte lane.
 */
#define DDRPHY_BISTGSR_BDXERR_MASK (0x4U)
#define DDRPHY_BISTGSR_BDXERR_SHIFT (2U)
#define DDRPHY_BISTGSR_BDXERR_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_BDXERR_MASK) >> DDRPHY_BISTGSR_BDXERR_SHIFT)

/*
 * BACERR (R)
 *
 * BIST Address/Command Error: indicates, if set, that there is a data comparison error in the address/command lane.
 */
#define DDRPHY_BISTGSR_BACERR_MASK (0x2U)
#define DDRPHY_BISTGSR_BACERR_SHIFT (1U)
#define DDRPHY_BISTGSR_BACERR_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_BACERR_MASK) >> DDRPHY_BISTGSR_BACERR_SHIFT)

/*
 * BDONE (R)
 *
 * BIST Done: Indicates, if set, that the BIST has finished executing. This bit is reset to zero when BIST is triggered.
 */
#define DDRPHY_BISTGSR_BDONE_MASK (0x1U)
#define DDRPHY_BISTGSR_BDONE_SHIFT (0U)
#define DDRPHY_BISTGSR_BDONE_GET(x) (((uint32_t)(x) & DDRPHY_BISTGSR_BDONE_MASK) >> DDRPHY_BISTGSR_BDONE_SHIFT)

/* Bitfield definition for register: BISTWER */
/*
 * DXWER (R)
 *
 * Byte Word Error: Indicates the number of word errors on the byte lane. An error on any bit of the data bus including the data mask bit increments the error count.
 */
#define DDRPHY_BISTWER_DXWER_MASK (0xFFFF0000UL)
#define DDRPHY_BISTWER_DXWER_SHIFT (16U)
#define DDRPHY_BISTWER_DXWER_GET(x) (((uint32_t)(x) & DDRPHY_BISTWER_DXWER_MASK) >> DDRPHY_BISTWER_DXWER_SHIFT)

/*
 * ACWER (R)
 *
 * Address/Command Word Error: Indicates the number of word errors on the address/command lane. An error on any bit of the address/command bus increments the error count.
 */
#define DDRPHY_BISTWER_ACWER_MASK (0xFFFFU)
#define DDRPHY_BISTWER_ACWER_SHIFT (0U)
#define DDRPHY_BISTWER_ACWER_GET(x) (((uint32_t)(x) & DDRPHY_BISTWER_ACWER_MASK) >> DDRPHY_BISTWER_ACWER_SHIFT)

/* Bitfield definition for register: BISTBER0 */
/*
 * ABER (R)
 *
 * Address Bit Error: Each group of two bits indicate the bit error count on each of the
 */
#define DDRPHY_BISTBER0_ABER_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTBER0_ABER_SHIFT (0U)
#define DDRPHY_BISTBER0_ABER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER0_ABER_MASK) >> DDRPHY_BISTBER0_ABER_SHIFT)

/* Bitfield definition for register: BISTBER1 */
/*
 * ODTBER (R)
 *
 * ODT Bit Error: Each group of two bits indicates the bit error count on each of the up to 4 ODT bits. [1:0] is the error count for ODT[0], [3:2] for ODT[1], and so on.
 */
#define DDRPHY_BISTBER1_ODTBER_MASK (0xFF000000UL)
#define DDRPHY_BISTBER1_ODTBER_SHIFT (24U)
#define DDRPHY_BISTBER1_ODTBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER1_ODTBER_MASK) >> DDRPHY_BISTBER1_ODTBER_SHIFT)

/*
 * CSBER (R)
 *
 * CS# Bit Error: Each group of two bits indicate the bit error count on each of the up to 4 CS# bits. [1:0] is the error count for CS#[0], [3:2] for CS#[1], and so on.
 */
#define DDRPHY_BISTBER1_CSBER_MASK (0xFF0000UL)
#define DDRPHY_BISTBER1_CSBER_SHIFT (16U)
#define DDRPHY_BISTBER1_CSBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER1_CSBER_MASK) >> DDRPHY_BISTBER1_CSBER_SHIFT)

/*
 * CKEBER (R)
 *
 * CKE Bit Error: Each group of two bits indicate the bit error count on each of the up to 4 CKE bits. [1:0] is the error count for CKE[0], [3:2] for CKE[1], and so on.
 */
#define DDRPHY_BISTBER1_CKEBER_MASK (0xFF00U)
#define DDRPHY_BISTBER1_CKEBER_SHIFT (8U)
#define DDRPHY_BISTBER1_CKEBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER1_CKEBER_MASK) >> DDRPHY_BISTBER1_CKEBER_SHIFT)

/*
 * WEBER (R)
 *
 * WE# Bit Error: Indicates the number of bit errors on WE#.
 */
#define DDRPHY_BISTBER1_WEBER_MASK (0xC0U)
#define DDRPHY_BISTBER1_WEBER_SHIFT (6U)
#define DDRPHY_BISTBER1_WEBER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER1_WEBER_MASK) >> DDRPHY_BISTBER1_WEBER_SHIFT)

/*
 * BABER (R)
 *
 * Bank Address Bit Error: Each group of two bits indicate the bit error count on each of the up to 3 bank address bits. [1:0] is the error count for BA[0], [3:2] for BA[1], and so on.
 */
#define DDRPHY_BISTBER1_BABER_MASK (0x3FU)
#define DDRPHY_BISTBER1_BABER_SHIFT (0U)
#define DDRPHY_BISTBER1_BABER_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER1_BABER_MASK) >> DDRPHY_BISTBER1_BABER_SHIFT)

/* Bitfield definition for register: BISTBER2 */
/*
 * DQBER0 (R)
 *
 * Data Bit Error: The error count for even DQS cycles. The first 16 bits indicate the error count for the first data beat (i.e. the data driven out on DQ[7:0] on the rising edge of DQS). The second 16 bits indicate the error on the second data beat (i.e. the error count of the data driven out on DQ[7:0] on the falling edge of DQS). For each of the 16-bit group, the first 2 bits are for DQ[0], the second for DQ[1], and so on.
 */
#define DDRPHY_BISTBER2_DQBER0_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTBER2_DQBER0_SHIFT (0U)
#define DDRPHY_BISTBER2_DQBER0_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER2_DQBER0_MASK) >> DDRPHY_BISTBER2_DQBER0_SHIFT)

/* Bitfield definition for register: BISTBER3 */
/*
 * DQBER1 (R)
 *
 * Data Bit Error: The error count for odd DQS cycles. The first 16 bits indicate the error count for the first data beat (i.e. the data driven out on DQ[7:0] on the rising edge of DQS). The second 16 bits indicate the error on the second data beat (i.e. the error count of the data driven out on DQ[7:0] on the falling edge of DQS). For each of the 16-bit group, the first 2 bits are for DQ[0], the second for DQ[1], and so on.
 */
#define DDRPHY_BISTBER3_DQBER1_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTBER3_DQBER1_SHIFT (0U)
#define DDRPHY_BISTBER3_DQBER1_GET(x) (((uint32_t)(x) & DDRPHY_BISTBER3_DQBER1_MASK) >> DDRPHY_BISTBER3_DQBER1_SHIFT)

/* Bitfield definition for register: BISTWCSR */
/*
 * DXWCNT (R)
 *
 * Byte Word Count: Indicates the number of words received from the byte lane.
 */
#define DDRPHY_BISTWCSR_DXWCNT_MASK (0xFFFF0000UL)
#define DDRPHY_BISTWCSR_DXWCNT_SHIFT (16U)
#define DDRPHY_BISTWCSR_DXWCNT_GET(x) (((uint32_t)(x) & DDRPHY_BISTWCSR_DXWCNT_MASK) >> DDRPHY_BISTWCSR_DXWCNT_SHIFT)

/*
 * ACWCNT (R)
 *
 * Address/Command Word Count: Indicates the number of words received from the address/command lane.
 */
#define DDRPHY_BISTWCSR_ACWCNT_MASK (0xFFFFU)
#define DDRPHY_BISTWCSR_ACWCNT_SHIFT (0U)
#define DDRPHY_BISTWCSR_ACWCNT_GET(x) (((uint32_t)(x) & DDRPHY_BISTWCSR_ACWCNT_MASK) >> DDRPHY_BISTWCSR_ACWCNT_SHIFT)

/* Bitfield definition for register: BISTFWR0 */
/*
 * ODTWEBS (R)
 *
 * Bit status during a word error for each of the up to 4 ODT bits.
 */
#define DDRPHY_BISTFWR0_ODTWEBS_MASK (0xF0000000UL)
#define DDRPHY_BISTFWR0_ODTWEBS_SHIFT (28U)
#define DDRPHY_BISTFWR0_ODTWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_ODTWEBS_MASK) >> DDRPHY_BISTFWR0_ODTWEBS_SHIFT)

/*
 * CSWEBS (R)
 *
 * Bit status during a word error for each of the up to 4 CS# bits.
 */
#define DDRPHY_BISTFWR0_CSWEBS_MASK (0xF000000UL)
#define DDRPHY_BISTFWR0_CSWEBS_SHIFT (24U)
#define DDRPHY_BISTFWR0_CSWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_CSWEBS_MASK) >> DDRPHY_BISTFWR0_CSWEBS_SHIFT)

/*
 * CKEWEBS (R)
 *
 * Bit status during a word error for each of the up to 4 CKE bits.
 */
#define DDRPHY_BISTFWR0_CKEWEBS_MASK (0xF00000UL)
#define DDRPHY_BISTFWR0_CKEWEBS_SHIFT (20U)
#define DDRPHY_BISTFWR0_CKEWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_CKEWEBS_MASK) >> DDRPHY_BISTFWR0_CKEWEBS_SHIFT)

/*
 * WEWEBS (R)
 *
 * Bit status during a word error for the WE#.
 */
#define DDRPHY_BISTFWR0_WEWEBS_MASK (0x80000UL)
#define DDRPHY_BISTFWR0_WEWEBS_SHIFT (19U)
#define DDRPHY_BISTFWR0_WEWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_WEWEBS_MASK) >> DDRPHY_BISTFWR0_WEWEBS_SHIFT)

/*
 * BAWEBS (R)
 *
 * Bit status during a word error for each of the up to 3 bank address bits.
 */
#define DDRPHY_BISTFWR0_BAWEBS_MASK (0x70000UL)
#define DDRPHY_BISTFWR0_BAWEBS_SHIFT (16U)
#define DDRPHY_BISTFWR0_BAWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_BAWEBS_MASK) >> DDRPHY_BISTFWR0_BAWEBS_SHIFT)

/*
 * AWEBS (R)
 *
 * Bit status during a word error for each of the up to 16 address bits.
 */
#define DDRPHY_BISTFWR0_AWEBS_MASK (0xFFFFU)
#define DDRPHY_BISTFWR0_AWEBS_SHIFT (0U)
#define DDRPHY_BISTFWR0_AWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR0_AWEBS_MASK) >> DDRPHY_BISTFWR0_AWEBS_SHIFT)

/* Bitfield definition for register: BISTFWR1 */
/*
 * DMWEBS (R)
 *
 * Bit status during a word error for the data mask (DM) bit. DMWEBS [0] is for the first DM beat, DMWEBS [1] is for the second DM beat, and so on.
 */
#define DDRPHY_BISTFWR1_DMWEBS_MASK (0xF0000000UL)
#define DDRPHY_BISTFWR1_DMWEBS_SHIFT (28U)
#define DDRPHY_BISTFWR1_DMWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR1_DMWEBS_MASK) >> DDRPHY_BISTFWR1_DMWEBS_SHIFT)

/*
 * PARWEBS (R)
 *
 * Bit status during a word error for the PAR_IN. Only for DIMM parity support
 */
#define DDRPHY_BISTFWR1_PARWEBS_MASK (0x4000000UL)
#define DDRPHY_BISTFWR1_PARWEBS_SHIFT (26U)
#define DDRPHY_BISTFWR1_PARWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR1_PARWEBS_MASK) >> DDRPHY_BISTFWR1_PARWEBS_SHIFT)

/*
 * CASWEBS (R)
 *
 * Bit status during a word error for the CAS.
 */
#define DDRPHY_BISTFWR1_CASWEBS_MASK (0x2U)
#define DDRPHY_BISTFWR1_CASWEBS_SHIFT (1U)
#define DDRPHY_BISTFWR1_CASWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR1_CASWEBS_MASK) >> DDRPHY_BISTFWR1_CASWEBS_SHIFT)

/*
 * RASWEBS (R)
 *
 * Bit status during a word error for the RAS.
 */
#define DDRPHY_BISTFWR1_RASWEBS_MASK (0x1U)
#define DDRPHY_BISTFWR1_RASWEBS_SHIFT (0U)
#define DDRPHY_BISTFWR1_RASWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR1_RASWEBS_MASK) >> DDRPHY_BISTFWR1_RASWEBS_SHIFT)

/* Bitfield definition for register: BISTFWR2 */
/*
 * DQWEBS (R)
 *
 * Bit status during a word error for each of the 8 data (DQ) bits. The first 8 bits indicate the status of the first data beat (i.e. the status of the data driven out on DQ[7:0] on the rising edge of DQS). The second 8 bits indicate the status of the second data beat (i.e. the status of the data driven out on DQ[7:0] on the falling edge of DQS), and so on. For each of the 8-bit group, the first bit is for DQ[0], the second bit is for DQ[1], and so on.
 */
#define DDRPHY_BISTFWR2_DQWEBS_MASK (0xFFFFFFFFUL)
#define DDRPHY_BISTFWR2_DQWEBS_SHIFT (0U)
#define DDRPHY_BISTFWR2_DQWEBS_GET(x) (((uint32_t)(x) & DDRPHY_BISTFWR2_DQWEBS_MASK) >> DDRPHY_BISTFWR2_DQWEBS_SHIFT)

/* Bitfield definition for register: AACR */
/*
 * AAOENC (R/W)
 *
 * Anti-Aging PAD Output Enable Control: Enables, if set, anti-aging toggling on the pad output enable signal “ctl_oe_n” going into the DATX8s. This will increase power consumption for the anti-aging feature.
 */
#define DDRPHY_AACR_AAOENC_MASK (0x80000000UL)
#define DDRPHY_AACR_AAOENC_SHIFT (31U)
#define DDRPHY_AACR_AAOENC_SET(x) (((uint32_t)(x) << DDRPHY_AACR_AAOENC_SHIFT) & DDRPHY_AACR_AAOENC_MASK)
#define DDRPHY_AACR_AAOENC_GET(x) (((uint32_t)(x) & DDRPHY_AACR_AAOENC_MASK) >> DDRPHY_AACR_AAOENC_SHIFT)

/*
 * AAENC (R/W)
 *
 * Anti-Aging Enable Control: Enables, if set, the automatic toggling of the data going to the DATX8 when the data channel from the controller/PUB to DATX8 is idle for programmable number of clock cycles.
 */
#define DDRPHY_AACR_AAENC_MASK (0x40000000UL)
#define DDRPHY_AACR_AAENC_SHIFT (30U)
#define DDRPHY_AACR_AAENC_SET(x) (((uint32_t)(x) << DDRPHY_AACR_AAENC_SHIFT) & DDRPHY_AACR_AAENC_MASK)
#define DDRPHY_AACR_AAENC_GET(x) (((uint32_t)(x) & DDRPHY_AACR_AAENC_MASK) >> DDRPHY_AACR_AAENC_SHIFT)

/*
 * AATR (R/W)
 *
 * Anti-Aging Toggle Rate: Defines the number of controller clock (ctl_clk) cycles after which the PUB will toggle the data going to DATX8 if the data channel between the controller/PUB and DATX8 has been idle for this long.
 * The default value correspond to a toggling count of 4096 ctl_clk cycles. For a ctl_clk running at 533MHz the toggle rate will be approximately 7.68us.
 * The default value may also be overridden by the macro DWC_AACR_AATR_DFLT.
 */
#define DDRPHY_AACR_AATR_MASK (0x3FFFFFFFUL)
#define DDRPHY_AACR_AATR_SHIFT (0U)
#define DDRPHY_AACR_AATR_SET(x) (((uint32_t)(x) << DDRPHY_AACR_AATR_SHIFT) & DDRPHY_AACR_AATR_MASK)
#define DDRPHY_AACR_AATR_GET(x) (((uint32_t)(x) & DDRPHY_AACR_AATR_MASK) >> DDRPHY_AACR_AATR_SHIFT)

/* Bitfield definition for register: GPR0 */
/*
 * GPR0 (R/W)
 *
 * General Purpose Register 0: General purpose register bits.
 */
#define DDRPHY_GPR0_GPR0_MASK (0xFFFFFFFFUL)
#define DDRPHY_GPR0_GPR0_SHIFT (0U)
#define DDRPHY_GPR0_GPR0_SET(x) (((uint32_t)(x) << DDRPHY_GPR0_GPR0_SHIFT) & DDRPHY_GPR0_GPR0_MASK)
#define DDRPHY_GPR0_GPR0_GET(x) (((uint32_t)(x) & DDRPHY_GPR0_GPR0_MASK) >> DDRPHY_GPR0_GPR0_SHIFT)

/* Bitfield definition for register: GPR1 */
/*
 * GPR1 (R/W)
 *
 * General Purpose Register 1: General purpose register bits.
 */
#define DDRPHY_GPR1_GPR1_MASK (0xFFFFFFFFUL)
#define DDRPHY_GPR1_GPR1_SHIFT (0U)
#define DDRPHY_GPR1_GPR1_SET(x) (((uint32_t)(x) << DDRPHY_GPR1_GPR1_SHIFT) & DDRPHY_GPR1_GPR1_MASK)
#define DDRPHY_GPR1_GPR1_GET(x) (((uint32_t)(x) & DDRPHY_GPR1_GPR1_MASK) >> DDRPHY_GPR1_GPR1_SHIFT)

/* Bitfield definition for register of struct array ZQ: CR0 */
/*
 * ZQPD (R/W)
 *
 * ZQ Power Down: Powers down, if set, the PZQ cell.
 */
#define DDRPHY_ZQ_CR0_ZQPD_MASK (0x80000000UL)
#define DDRPHY_ZQ_CR0_ZQPD_SHIFT (31U)
#define DDRPHY_ZQ_CR0_ZQPD_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR0_ZQPD_SHIFT) & DDRPHY_ZQ_CR0_ZQPD_MASK)
#define DDRPHY_ZQ_CR0_ZQPD_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR0_ZQPD_MASK) >> DDRPHY_ZQ_CR0_ZQPD_SHIFT)

/*
 * ZCALEN (R/W)
 *
 * Impedance Calibration Enable: Enables, if set, the impedance calibration of this ZQ control block when impedance calibration is triggered using either the ZCAL bit of PIR register or the DFI update interface.
 */
#define DDRPHY_ZQ_CR0_ZCALEN_MASK (0x40000000UL)
#define DDRPHY_ZQ_CR0_ZCALEN_SHIFT (30U)
#define DDRPHY_ZQ_CR0_ZCALEN_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR0_ZCALEN_SHIFT) & DDRPHY_ZQ_CR0_ZCALEN_MASK)
#define DDRPHY_ZQ_CR0_ZCALEN_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR0_ZCALEN_MASK) >> DDRPHY_ZQ_CR0_ZCALEN_SHIFT)

/*
 * ZCALBYP (R/W)
 *
 * Impedance Calibration Bypass: Bypasses, if set, impedance calibration of this ZQ control block when impedance calibration is already in progress. Impedance calibration can be disabled prior to trigger by using the ZCALEN bit.
 */
#define DDRPHY_ZQ_CR0_ZCALBYP_MASK (0x20000000UL)
#define DDRPHY_ZQ_CR0_ZCALBYP_SHIFT (29U)
#define DDRPHY_ZQ_CR0_ZCALBYP_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR0_ZCALBYP_SHIFT) & DDRPHY_ZQ_CR0_ZCALBYP_MASK)
#define DDRPHY_ZQ_CR0_ZCALBYP_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR0_ZCALBYP_MASK) >> DDRPHY_ZQ_CR0_ZCALBYP_SHIFT)

/*
 * ZDEN (R/W)
 *
 * Impedance Over-ride Enable: When this bit is set, it allows users to directly drive the impedance control using the data programmed in the ZDATA field. Otherwise, the control is generated automatically by the impedance control logic.
 */
#define DDRPHY_ZQ_CR0_ZDEN_MASK (0x10000000UL)
#define DDRPHY_ZQ_CR0_ZDEN_SHIFT (28U)
#define DDRPHY_ZQ_CR0_ZDEN_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR0_ZDEN_SHIFT) & DDRPHY_ZQ_CR0_ZDEN_MASK)
#define DDRPHY_ZQ_CR0_ZDEN_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR0_ZDEN_MASK) >> DDRPHY_ZQ_CR0_ZDEN_SHIFT)

/*
 * ZDATA (R/W)
 *
 * Impedance Over-Ride Data: Data used to directly drive the impedance control.
 * ZDATA field mapping for D3F I/Os is as follows:
 * ZDATA[27:21] is used to select the pull-up on-die termination impedance ZDATA[20:14] is used to select the pull-down on-die termination impedance ZDATA[13:7] is used to select the pull-up output impedance
 * ZDATA[6:0] is used to select the pull-down output impedance
 * ZDATA field mapping for D3A/B/R I/Os is as follows: ZDATA[27:20] is reserved and returns zeros on reads
 * ZDATA[19:15] is used to select the pull-up on-die termination impedance ZDATA[14:10] is used to select the pull-down on-die termination impedance ZDATA[9:5] is used to select the pull-up output impedance
 * ZDATA[4:0] is used to select the pull-down output impedance
 * The default value is 0x000014A for I/O type D3C/R and 0x0001830 for I/O type D3F.
 */
#define DDRPHY_ZQ_CR0_ZDATA_MASK (0xFFFFFFFUL)
#define DDRPHY_ZQ_CR0_ZDATA_SHIFT (0U)
#define DDRPHY_ZQ_CR0_ZDATA_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR0_ZDATA_SHIFT) & DDRPHY_ZQ_CR0_ZDATA_MASK)
#define DDRPHY_ZQ_CR0_ZDATA_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR0_ZDATA_MASK) >> DDRPHY_ZQ_CR0_ZDATA_SHIFT)

/* Bitfield definition for register of struct array ZQ: CR1 */
/*
 * DFIPU1 (R/W)
 *
 * DFI Update Interface 1: Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 1 (channel 1) requests an update. Only valid in shared-AC mode.
 */
#define DDRPHY_ZQ_CR1_DFIPU1_MASK (0x20000UL)
#define DDRPHY_ZQ_CR1_DFIPU1_SHIFT (17U)
#define DDRPHY_ZQ_CR1_DFIPU1_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_DFIPU1_SHIFT) & DDRPHY_ZQ_CR1_DFIPU1_MASK)
#define DDRPHY_ZQ_CR1_DFIPU1_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_DFIPU1_MASK) >> DDRPHY_ZQ_CR1_DFIPU1_SHIFT)

/*
 * DFIPU0 (R/W)
 *
 * DFI Update Interface 0: Sets this impedance controller to be enabled for calibration when the DFI PHY update interface 0 (channel 0) requests an update.
 */
#define DDRPHY_ZQ_CR1_DFIPU0_MASK (0x10000UL)
#define DDRPHY_ZQ_CR1_DFIPU0_SHIFT (16U)
#define DDRPHY_ZQ_CR1_DFIPU0_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_DFIPU0_SHIFT) & DDRPHY_ZQ_CR1_DFIPU0_MASK)
#define DDRPHY_ZQ_CR1_DFIPU0_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_DFIPU0_MASK) >> DDRPHY_ZQ_CR1_DFIPU0_SHIFT)

/*
 * DFICCU (R/W)
 *
 * DFI Concurrent Controller Update Interface: Sets this impedance controller to be enabled for calibration when both of the DFI controller update interfaces request an update on the same clock. This provides the ability to enable impedance calibration updates for the Address/Command lane. Only valid in shared-AC mode.
 */
#define DDRPHY_ZQ_CR1_DFICCU_MASK (0x4000U)
#define DDRPHY_ZQ_CR1_DFICCU_SHIFT (14U)
#define DDRPHY_ZQ_CR1_DFICCU_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_DFICCU_SHIFT) & DDRPHY_ZQ_CR1_DFICCU_MASK)
#define DDRPHY_ZQ_CR1_DFICCU_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_DFICCU_MASK) >> DDRPHY_ZQ_CR1_DFICCU_SHIFT)

/*
 * DFICU1 (R/W)
 *
 * DFI Controller Update Interface 1: Sets this impedance controller to be enabled for calibration when the DFI controller update interface 1 (channel 1) requests an update. Only valid in shared-AC mode.
 */
#define DDRPHY_ZQ_CR1_DFICU1_MASK (0x2000U)
#define DDRPHY_ZQ_CR1_DFICU1_SHIFT (13U)
#define DDRPHY_ZQ_CR1_DFICU1_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_DFICU1_SHIFT) & DDRPHY_ZQ_CR1_DFICU1_MASK)
#define DDRPHY_ZQ_CR1_DFICU1_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_DFICU1_MASK) >> DDRPHY_ZQ_CR1_DFICU1_SHIFT)

/*
 * DFICU0 (R/W)
 *
 * DFI Controller Update Interface 0: Sets this impedance controller to be enabled for calibration when the DFI controller update interface 0 (channel 0) requests an update.
 */
#define DDRPHY_ZQ_CR1_DFICU0_MASK (0x1000U)
#define DDRPHY_ZQ_CR1_DFICU0_SHIFT (12U)
#define DDRPHY_ZQ_CR1_DFICU0_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_DFICU0_SHIFT) & DDRPHY_ZQ_CR1_DFICU0_MASK)
#define DDRPHY_ZQ_CR1_DFICU0_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_DFICU0_MASK) >> DDRPHY_ZQ_CR1_DFICU0_SHIFT)

/*
 * ZPROG (R/W)
 *
 * Impedance Divide Ratio: Selects the external resistor divide ratio to be used to set the output impedance and the on-die termination as follows:
 * ZPROG[7:4] = On-die termination divide select ZPROG[3:0] = Output impedance divide select
 */
#define DDRPHY_ZQ_CR1_ZPROG_MASK (0xFFU)
#define DDRPHY_ZQ_CR1_ZPROG_SHIFT (0U)
#define DDRPHY_ZQ_CR1_ZPROG_SET(x) (((uint32_t)(x) << DDRPHY_ZQ_CR1_ZPROG_SHIFT) & DDRPHY_ZQ_CR1_ZPROG_MASK)
#define DDRPHY_ZQ_CR1_ZPROG_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_CR1_ZPROG_MASK) >> DDRPHY_ZQ_CR1_ZPROG_SHIFT)

/* Bitfield definition for register of struct array ZQ: SR0 */
/*
 * ZDONE (R)
 *
 * Impedance Calibration Done: Indicates that impedance calibration has completed.
 */
#define DDRPHY_ZQ_SR0_ZDONE_MASK (0x80000000UL)
#define DDRPHY_ZQ_SR0_ZDONE_SHIFT (31U)
#define DDRPHY_ZQ_SR0_ZDONE_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR0_ZDONE_MASK) >> DDRPHY_ZQ_SR0_ZDONE_SHIFT)

/*
 * ZERR (R)
 *
 * Impedance Calibration Error: If set, indicates that there was an error during impedance calibration.
 */
#define DDRPHY_ZQ_SR0_ZERR_MASK (0x40000000UL)
#define DDRPHY_ZQ_SR0_ZERR_SHIFT (30U)
#define DDRPHY_ZQ_SR0_ZERR_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR0_ZERR_MASK) >> DDRPHY_ZQ_SR0_ZERR_SHIFT)

/*
 * ZCTRL (R)
 *
 * Impedance Control: Current value of impedance control. ZCTRL field mapping for D3F I/Os is as follows:
 * ZCTRL[27:21] is used to select the pull-up on-die termination impedance ZCTRL[20:14] is used to select the pull-down on-die termination impedance ZCTRL[13:7] is used to select the pull-up output impedance
 * ZCTRL[6:0] is used to select the pull-down output impedance
 * ZCTRL field mapping for D3A/B/R I/Os is as follows: ZCTRL[27:20] is reserved and returns zeros on reads
 * ZCTRL[19:15] is used to select the pull-up on-die termination impedance ZCTRL[14:10] is used to select the pull-down on-die termination impedance ZCTRL[9:5] is used to select the pull-up output impedance
 * ZCTRL[4:0] is used to select the pull-down output impedance
 * Note: The default value is 0x000014A for I/O type D3C/D3R and 0x0001839 for I/O type D3F.
 */
#define DDRPHY_ZQ_SR0_ZCTRL_MASK (0xFFFFFFFUL)
#define DDRPHY_ZQ_SR0_ZCTRL_SHIFT (0U)
#define DDRPHY_ZQ_SR0_ZCTRL_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR0_ZCTRL_MASK) >> DDRPHY_ZQ_SR0_ZCTRL_SHIFT)

/* Bitfield definition for register of struct array ZQ: SR1 */
/*
 * OPU (R)
 *
 * On-die termination (ODT) pull-up calibration status. Similar status encodings as ZPD.
 */
#define DDRPHY_ZQ_SR1_OPU_MASK (0xC0U)
#define DDRPHY_ZQ_SR1_OPU_SHIFT (6U)
#define DDRPHY_ZQ_SR1_OPU_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR1_OPU_MASK) >> DDRPHY_ZQ_SR1_OPU_SHIFT)

/*
 * OPD (R)
 *
 * On-die termination (ODT) pull-down calibration status. Similar status encodings as ZPD.
 */
#define DDRPHY_ZQ_SR1_OPD_MASK (0x30U)
#define DDRPHY_ZQ_SR1_OPD_SHIFT (4U)
#define DDRPHY_ZQ_SR1_OPD_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR1_OPD_MASK) >> DDRPHY_ZQ_SR1_OPD_SHIFT)

/*
 * ZPU (R)
 *
 * Output impedance pull-up calibration status. Similar status encodings as ZPD.
 */
#define DDRPHY_ZQ_SR1_ZPU_MASK (0xCU)
#define DDRPHY_ZQ_SR1_ZPU_SHIFT (2U)
#define DDRPHY_ZQ_SR1_ZPU_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR1_ZPU_MASK) >> DDRPHY_ZQ_SR1_ZPU_SHIFT)

/*
 * ZPD (R)
 *
 * Output impedance pull-down calibration status. Valid status encodings are: 00 = Completed with no errors
 * 01 = Overflow error 10 = Underflow error
 * 11 = Calibration in progress
 */
#define DDRPHY_ZQ_SR1_ZPD_MASK (0x3U)
#define DDRPHY_ZQ_SR1_ZPD_SHIFT (0U)
#define DDRPHY_ZQ_SR1_ZPD_GET(x) (((uint32_t)(x) & DDRPHY_ZQ_SR1_ZPD_MASK) >> DDRPHY_ZQ_SR1_ZPD_SHIFT)

/* Bitfield definition for register of struct array DX: GCR */
/*
 * CALBYP (R/W)
 *
 * Calibration Bypass: Prevents, if set, period measurement calibration from automatically triggering after PHY initialization.
 */
#define DDRPHY_DX_GCR_CALBYP_MASK (0x80000000UL)
#define DDRPHY_DX_GCR_CALBYP_SHIFT (31U)
#define DDRPHY_DX_GCR_CALBYP_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_CALBYP_SHIFT) & DDRPHY_DX_GCR_CALBYP_MASK)
#define DDRPHY_DX_GCR_CALBYP_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_CALBYP_MASK) >> DDRPHY_DX_GCR_CALBYP_SHIFT)

/*
 * MDLEN (R/W)
 *
 * Master Delay Line Enable: Enables, if set, the DATX8 master delay line calibration to perform subsequent period measurements following the initial period measurements that are performed after reset or when calibration is manually triggered. These additional measurements are accumulated and filtered as long as this bit remains high. This bit is ANDed with the common DATX8 MDL enable bit.
 */
#define DDRPHY_DX_GCR_MDLEN_MASK (0x40000000UL)
#define DDRPHY_DX_GCR_MDLEN_SHIFT (30U)
#define DDRPHY_DX_GCR_MDLEN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_MDLEN_SHIFT) & DDRPHY_DX_GCR_MDLEN_MASK)
#define DDRPHY_DX_GCR_MDLEN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_MDLEN_MASK) >> DDRPHY_DX_GCR_MDLEN_SHIFT)

/*
 * WLRKEN (R/W)
 *
 * Write Level Rank Enable: Specifies the ranks that should be write leveled for this byte. Write leveling responses from ranks that are not enabled for write leveling for a particular byte are ignored and write leveling is flagged as done for these ranks.
 * WLRKEN[0] enables rank 0, [1] enables rank 1, [2] enables rank 2, and [3] enables
 * rank 3.
 */
#define DDRPHY_DX_GCR_WLRKEN_MASK (0x3C000000UL)
#define DDRPHY_DX_GCR_WLRKEN_SHIFT (26U)
#define DDRPHY_DX_GCR_WLRKEN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_WLRKEN_SHIFT) & DDRPHY_DX_GCR_WLRKEN_MASK)
#define DDRPHY_DX_GCR_WLRKEN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_WLRKEN_MASK) >> DDRPHY_DX_GCR_WLRKEN_SHIFT)

/*
 * PLLBYP (R/W)
 *
 * PLL Bypass: Puts the byte PLL in bypass mode by driving the PLL bypass pin. This bit is not self-clearing and a '0' must be written to de-assert the bypass. This bit is ORed with the global BYP configuration bit (see Table 3-10 on page 91).
 */
#define DDRPHY_DX_GCR_PLLBYP_MASK (0x80000UL)
#define DDRPHY_DX_GCR_PLLBYP_SHIFT (19U)
#define DDRPHY_DX_GCR_PLLBYP_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_PLLBYP_SHIFT) & DDRPHY_DX_GCR_PLLBYP_MASK)
#define DDRPHY_DX_GCR_PLLBYP_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_PLLBYP_MASK) >> DDRPHY_DX_GCR_PLLBYP_SHIFT)

/*
 * GSHIFT (R/W)
 *
 * Gear Shift: Enables, if set, rapid locking mode on the byte PLL. This bit is ORed with the global GSHIFT configuration bit (see Table 3-10 on page 91).
 */
#define DDRPHY_DX_GCR_GSHIFT_MASK (0x40000UL)
#define DDRPHY_DX_GCR_GSHIFT_SHIFT (18U)
#define DDRPHY_DX_GCR_GSHIFT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_GSHIFT_SHIFT) & DDRPHY_DX_GCR_GSHIFT_MASK)
#define DDRPHY_DX_GCR_GSHIFT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_GSHIFT_MASK) >> DDRPHY_DX_GCR_GSHIFT_SHIFT)

/*
 * PLLPD (R/W)
 *
 * PLL Power Down: Puts the byte PLL in power down mode by driving the PLL power down pin. This bit is not self-clearing and a '0' must be written to de-assert the power-down. This bit is ORed with the global PLLPD configuration bit (see
 * Table 3-10 on page 91).
 */
#define DDRPHY_DX_GCR_PLLPD_MASK (0x20000UL)
#define DDRPHY_DX_GCR_PLLPD_SHIFT (17U)
#define DDRPHY_DX_GCR_PLLPD_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_PLLPD_SHIFT) & DDRPHY_DX_GCR_PLLPD_MASK)
#define DDRPHY_DX_GCR_PLLPD_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_PLLPD_MASK) >> DDRPHY_DX_GCR_PLLPD_SHIFT)

/*
 * PLLRST (R/W)
 *
 * PLL Rest: Resets the byte PLL by driving the PLL reset pin. This bit is not self- clearing and a '0' must be written to de-assert the reset. This bit is ORed with the global PLLRST configuration bit (see Table 3-10 on page 91).
 */
#define DDRPHY_DX_GCR_PLLRST_MASK (0x10000UL)
#define DDRPHY_DX_GCR_PLLRST_SHIFT (16U)
#define DDRPHY_DX_GCR_PLLRST_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_PLLRST_SHIFT) & DDRPHY_DX_GCR_PLLRST_MASK)
#define DDRPHY_DX_GCR_PLLRST_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_PLLRST_MASK) >> DDRPHY_DX_GCR_PLLRST_SHIFT)

/*
 * DXOEO (R/W)
 *
 * Data Byte Output Enable Override: Specifies whether the output I/O output enable for the byte lane should be set to a fixed value. Valid values are:
 * 00 = No override. Output enable is controlled by DFI transactions 01 = output enable is asserted (I/O is forced to output mode).
 * 10 = Output enable is de-asserted (I/O is forced to input mode) 11 = Reserved
 */
#define DDRPHY_DX_GCR_DXOEO_MASK (0xC000U)
#define DDRPHY_DX_GCR_DXOEO_SHIFT (14U)
#define DDRPHY_DX_GCR_DXOEO_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DXOEO_SHIFT) & DDRPHY_DX_GCR_DXOEO_MASK)
#define DDRPHY_DX_GCR_DXOEO_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DXOEO_MASK) >> DDRPHY_DX_GCR_DXOEO_SHIFT)

/*
 * RTTOAL (R/W)
 *
 * RTT On Additive Latency: Indicates when the ODT control of DQ/DQS SSTL I/Os is set to the value in DQODT/DQSODT during read cycles. Valid values are:
 * 0 = ODT control is set to DQSODT/DQODT almost two cycles before read data preamble
 * 1 = ODT control is set to DQSODT/DQODT almost one cycle before read data preamble
 */
#define DDRPHY_DX_GCR_RTTOAL_MASK (0x2000U)
#define DDRPHY_DX_GCR_RTTOAL_SHIFT (13U)
#define DDRPHY_DX_GCR_RTTOAL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_RTTOAL_SHIFT) & DDRPHY_DX_GCR_RTTOAL_MASK)
#define DDRPHY_DX_GCR_RTTOAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_RTTOAL_MASK) >> DDRPHY_DX_GCR_RTTOAL_SHIFT)

/*
 * RTTOH (R/W)
 *
 * RTT Output Hold: Indicates the number of clock cycles (from 0 to 3) after the read data postamble for which ODT control should remain set to DQSODT for DQS or DQODT for DQ/DM before disabling it (setting it to ‘0’) when using dynamic ODT control. ODT is disabled almost RTTOH clock cycles after the read postamble.
 */
#define DDRPHY_DX_GCR_RTTOH_MASK (0x1800U)
#define DDRPHY_DX_GCR_RTTOH_SHIFT (11U)
#define DDRPHY_DX_GCR_RTTOH_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_RTTOH_SHIFT) & DDRPHY_DX_GCR_RTTOH_MASK)
#define DDRPHY_DX_GCR_RTTOH_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_RTTOH_MASK) >> DDRPHY_DX_GCR_RTTOH_SHIFT)

/*
 * DQRTT (R/W)
 *
 * DQ Dynamic RTT Control: If set, the on die termination (ODT) control of the DQ/DM SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise. By setting this bit to '0' the dynamic ODT feature is disabled. To control ODT statically this bit must be set to '0' and DXnGCR0[2] (DQODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
 */
#define DDRPHY_DX_GCR_DQRTT_MASK (0x400U)
#define DDRPHY_DX_GCR_DQRTT_SHIFT (10U)
#define DDRPHY_DX_GCR_DQRTT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DQRTT_SHIFT) & DDRPHY_DX_GCR_DQRTT_MASK)
#define DDRPHY_DX_GCR_DQRTT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DQRTT_MASK) >> DDRPHY_DX_GCR_DQRTT_SHIFT)

/*
 * DQSRTT (R/W)
 *
 * DQS Dynamic RTT Control: If set, the on die termination (ODT) control of the DQS/DQS# SSTL I/O is dynamically generated to enable the ODT during read operation and disabled otherwise. By setting this bit to '0' the dynamic ODT feature is disabled. To control ODT statically this bit must be set to '0' and DXnGCR0[1] (DQSODT) is used to enable ODT (when set to '1') or disable ODT(when set to '0').
 */
#define DDRPHY_DX_GCR_DQSRTT_MASK (0x200U)
#define DDRPHY_DX_GCR_DQSRTT_SHIFT (9U)
#define DDRPHY_DX_GCR_DQSRTT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DQSRTT_SHIFT) & DDRPHY_DX_GCR_DQSRTT_MASK)
#define DDRPHY_DX_GCR_DQSRTT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DQSRTT_MASK) >> DDRPHY_DX_GCR_DQSRTT_SHIFT)

/*
 * DSEN (R/W)
 *
 * Write DQS Enable: Controls whether the write DQS going to the SDRAM is enabled (toggling) or disabled (static value) and whether the DQS is inverted. DQS# is always the inversion of DQS. These values are valid only when DQS/DQS# output enable is on, otherwise the DQS/DQS# is tristated. Valid settings are:
 * 00 = Reserved
 * 01 = DQS toggling with normal polarity (This should be the default setting) 10 = Reserved
 * 11 = Reserved
 */
#define DDRPHY_DX_GCR_DSEN_MASK (0x180U)
#define DDRPHY_DX_GCR_DSEN_SHIFT (7U)
#define DDRPHY_DX_GCR_DSEN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DSEN_SHIFT) & DDRPHY_DX_GCR_DSEN_MASK)
#define DDRPHY_DX_GCR_DSEN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DSEN_MASK) >> DDRPHY_DX_GCR_DSEN_SHIFT)

/*
 * DQSRPD (R/W)
 *
 * DQSR Power Down: Powers down, if set, the PDQSR cell. This bit is ORed with the common PDR configuration bit (see “DATX8 Common Configuration Register (DXCCR)” on page 99)
 */
#define DDRPHY_DX_GCR_DQSRPD_MASK (0x40U)
#define DDRPHY_DX_GCR_DQSRPD_SHIFT (6U)
#define DDRPHY_DX_GCR_DQSRPD_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DQSRPD_SHIFT) & DDRPHY_DX_GCR_DQSRPD_MASK)
#define DDRPHY_DX_GCR_DQSRPD_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DQSRPD_MASK) >> DDRPHY_DX_GCR_DQSRPD_SHIFT)

/*
 * DXPDR (R/W)
 *
 * Data Power Down Receiver: Powers down, when set, the input receiver on I/O for DQ, DM, and DQS/DQS# pins of the byte. This bit is ORed with the common PDR configuration bit (see “DATX8 Common Configuration Register (DXCCR)” on page 99).
 */
#define DDRPHY_DX_GCR_DXPDR_MASK (0x20U)
#define DDRPHY_DX_GCR_DXPDR_SHIFT (5U)
#define DDRPHY_DX_GCR_DXPDR_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DXPDR_SHIFT) & DDRPHY_DX_GCR_DXPDR_MASK)
#define DDRPHY_DX_GCR_DXPDR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DXPDR_MASK) >> DDRPHY_DX_GCR_DXPDR_SHIFT)

/*
 * DXPDD1 (R/W)
 *
 * Data Power Down Driver: Powers down, when set, the output driver on I/O for DQ, DM, and DQS/DQS# pins of the byte. This bit is ORed with the common PDD configuration bit (see “DATX8 Common Configuration Register (DXCCR)” on page 99).
 */
#define DDRPHY_DX_GCR_DXPDD1_MASK (0x10U)
#define DDRPHY_DX_GCR_DXPDD1_SHIFT (4U)
#define DDRPHY_DX_GCR_DXPDD1_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DXPDD1_SHIFT) & DDRPHY_DX_GCR_DXPDD1_MASK)
#define DDRPHY_DX_GCR_DXPDD1_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DXPDD1_MASK) >> DDRPHY_DX_GCR_DXPDD1_SHIFT)

/*
 * DXIOM (R/W)
 *
 * Data I/O Mode: Selects SSTL mode (when set to 0) or CMOS mode (when set to 1) of the I/O for DQ, DM, and DQS/DQS# pins of the byte. This bit is ORed with the IOM configuration bit of the individual DATX8(see “DATX8 Common Configuration Register (DXCCR)” on page 99).
 */
#define DDRPHY_DX_GCR_DXIOM_MASK (0x8U)
#define DDRPHY_DX_GCR_DXIOM_SHIFT (3U)
#define DDRPHY_DX_GCR_DXIOM_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DXIOM_SHIFT) & DDRPHY_DX_GCR_DXIOM_MASK)
#define DDRPHY_DX_GCR_DXIOM_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DXIOM_MASK) >> DDRPHY_DX_GCR_DXIOM_SHIFT)

/*
 * DQODT (R/W)
 *
 * Data On-Die Termination: Enables, when set, the on-die termination on the I/O for DQ and DM pins of the byte. This bit is ORed with the common DATX8 ODT configuration bit (see “DATX8 Common Configuration Register (DXCCR)” on page 99).
 * Note: This bit is only valid when DXnGCR0[10] is '0'.
 */
#define DDRPHY_DX_GCR_DQODT_MASK (0x4U)
#define DDRPHY_DX_GCR_DQODT_SHIFT (2U)
#define DDRPHY_DX_GCR_DQODT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DQODT_SHIFT) & DDRPHY_DX_GCR_DQODT_MASK)
#define DDRPHY_DX_GCR_DQODT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DQODT_MASK) >> DDRPHY_DX_GCR_DQODT_SHIFT)

/*
 * DQSODT (R/W)
 *
 * DQS On-Die Termination: Enables, when set, the on-die termination on the I/O for DQS/DQS# pin of the byte. This bit is ORed with the common DATX8 ODT configuration bit (see “DATX8 Common Configuration Register (DXCCR)” on page 99).
 * Note: This bit is only valid when DXnGCR0[9] is '0'.
 */
#define DDRPHY_DX_GCR_DQSODT_MASK (0x2U)
#define DDRPHY_DX_GCR_DQSODT_SHIFT (1U)
#define DDRPHY_DX_GCR_DQSODT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DQSODT_SHIFT) & DDRPHY_DX_GCR_DQSODT_MASK)
#define DDRPHY_DX_GCR_DQSODT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DQSODT_MASK) >> DDRPHY_DX_GCR_DQSODT_SHIFT)

/*
 * DXEN (R/W)
 *
 * Data Byte Enable: Enables, if set, the data byte. Setting this bit to '0' disables the byte, i.e. the byte is not used in PHY initialization or training and is ignored during SDRAM read/write operations.
 */
#define DDRPHY_DX_GCR_DXEN_MASK (0x1U)
#define DDRPHY_DX_GCR_DXEN_SHIFT (0U)
#define DDRPHY_DX_GCR_DXEN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GCR_DXEN_SHIFT) & DDRPHY_DX_GCR_DXEN_MASK)
#define DDRPHY_DX_GCR_DXEN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GCR_DXEN_MASK) >> DDRPHY_DX_GCR_DXEN_SHIFT)

/* Bitfield definition for register of struct array DX: GSR0 */
/*
 * WLDQ (R)
 *
 * Write Leveling DQ Status: Captures the write leveling DQ status from the DRAM during software write leveling.
 */
#define DDRPHY_DX_GSR0_WLDQ_MASK (0x10000000UL)
#define DDRPHY_DX_GSR0_WLDQ_SHIFT (28U)
#define DDRPHY_DX_GSR0_WLDQ_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WLDQ_MASK) >> DDRPHY_DX_GSR0_WLDQ_SHIFT)

/*
 * QSGERR (R)
 *
 * DQS Gate Training Error: Indicates, if set, that there is an error in DQS gate training. One bit for each of the up to 4 ranks.
 */
#define DDRPHY_DX_GSR0_QSGERR_MASK (0xF000000UL)
#define DDRPHY_DX_GSR0_QSGERR_SHIFT (24U)
#define DDRPHY_DX_GSR0_QSGERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_QSGERR_MASK) >> DDRPHY_DX_GSR0_QSGERR_SHIFT)

/*
 * GDQSPRD (R)
 *
 * Read DQS gating Period: Returns the DDR clock period measured by the read DQS gating LCDL during calibration. This value is PVT compensated.
 */
#define DDRPHY_DX_GSR0_GDQSPRD_MASK (0xFF0000UL)
#define DDRPHY_DX_GSR0_GDQSPRD_SHIFT (16U)
#define DDRPHY_DX_GSR0_GDQSPRD_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_GDQSPRD_MASK) >> DDRPHY_DX_GSR0_GDQSPRD_SHIFT)

/*
 * DPLOCK (R)
 *
 * DATX8 PLL Lock: Indicates, if set, that the DATX8 PLL has locked. This is a direct status of the DATX8 PLL lock pin.
 */
#define DDRPHY_DX_GSR0_DPLOCK_MASK (0x8000U)
#define DDRPHY_DX_GSR0_DPLOCK_SHIFT (15U)
#define DDRPHY_DX_GSR0_DPLOCK_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_DPLOCK_MASK) >> DDRPHY_DX_GSR0_DPLOCK_SHIFT)

/*
 * WLPRD (R)
 *
 * Write Leveling Period: Returns the DDR clock period measured by the write leveling LCDL during calibration. The measured period is used to generate the control of the write leveling pipeline which is a function of the write-leveling delay and the clock period. This value is PVT compensated.
 */
#define DDRPHY_DX_GSR0_WLPRD_MASK (0x7F80U)
#define DDRPHY_DX_GSR0_WLPRD_SHIFT (7U)
#define DDRPHY_DX_GSR0_WLPRD_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WLPRD_MASK) >> DDRPHY_DX_GSR0_WLPRD_SHIFT)

/*
 * WLERR (R)
 *
 * Write Leveling Error: Indicates, if set, that there is a write leveling error in the DATX8.
 */
#define DDRPHY_DX_GSR0_WLERR_MASK (0x40U)
#define DDRPHY_DX_GSR0_WLERR_SHIFT (6U)
#define DDRPHY_DX_GSR0_WLERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WLERR_MASK) >> DDRPHY_DX_GSR0_WLERR_SHIFT)

/*
 * WLDONE (R)
 *
 * Write Leveling Done: Indicates, if set, that the DATX8 has completed write leveling.
 */
#define DDRPHY_DX_GSR0_WLDONE_MASK (0x20U)
#define DDRPHY_DX_GSR0_WLDONE_SHIFT (5U)
#define DDRPHY_DX_GSR0_WLDONE_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WLDONE_MASK) >> DDRPHY_DX_GSR0_WLDONE_SHIFT)

/*
 * WLCAL (R)
 *
 * Write Leveling Calibration: Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write leveling slave delay line.
 */
#define DDRPHY_DX_GSR0_WLCAL_MASK (0x10U)
#define DDRPHY_DX_GSR0_WLCAL_SHIFT (4U)
#define DDRPHY_DX_GSR0_WLCAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WLCAL_MASK) >> DDRPHY_DX_GSR0_WLCAL_SHIFT)

/*
 * GDQSCAL (R)
 *
 * Read DQS gating Calibration: Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS gating LCDL.
 */
#define DDRPHY_DX_GSR0_GDQSCAL_MASK (0x8U)
#define DDRPHY_DX_GSR0_GDQSCAL_SHIFT (3U)
#define DDRPHY_DX_GSR0_GDQSCAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_GDQSCAL_MASK) >> DDRPHY_DX_GSR0_GDQSCAL_SHIFT)

/*
 * RDQSNCAL (R)
 *
 * Read DQS# Calibration (Type B/B1 PHY Only): Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS# LCDL.
 */
#define DDRPHY_DX_GSR0_RDQSNCAL_MASK (0x4U)
#define DDRPHY_DX_GSR0_RDQSNCAL_SHIFT (2U)
#define DDRPHY_DX_GSR0_RDQSNCAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_RDQSNCAL_MASK) >> DDRPHY_DX_GSR0_RDQSNCAL_SHIFT)

/*
 * RDQSCAL (R)
 *
 * Read DQS Calibration: Indicates, if set, that the DATX8 has finished doing period measurement calibration for the read DQS LCDL.
 */
#define DDRPHY_DX_GSR0_RDQSCAL_MASK (0x2U)
#define DDRPHY_DX_GSR0_RDQSCAL_SHIFT (1U)
#define DDRPHY_DX_GSR0_RDQSCAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_RDQSCAL_MASK) >> DDRPHY_DX_GSR0_RDQSCAL_SHIFT)

/*
 * WDQCAL (R)
 *
 * Write DQ Calibration: Indicates, if set, that the DATX8 has finished doing period measurement calibration for the write DQ LCDL.
 */
#define DDRPHY_DX_GSR0_WDQCAL_MASK (0x1U)
#define DDRPHY_DX_GSR0_WDQCAL_SHIFT (0U)
#define DDRPHY_DX_GSR0_WDQCAL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR0_WDQCAL_MASK) >> DDRPHY_DX_GSR0_WDQCAL_SHIFT)

/* Bitfield definition for register of struct array DX: GSR1 */
/*
 * DLTCODE (R)
 *
 * Delay Line Test Code: Returns the code measured by the PHY control block that corresponds to the period of the DATX8 delay line digital test output.
 */
#define DDRPHY_DX_GSR1_DLTCODE_MASK (0x1FFFFFEUL)
#define DDRPHY_DX_GSR1_DLTCODE_SHIFT (1U)
#define DDRPHY_DX_GSR1_DLTCODE_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR1_DLTCODE_MASK) >> DDRPHY_DX_GSR1_DLTCODE_SHIFT)

/*
 * DLTDONE (R)
 *
 * Delay Line Test Done: Indicates, if set, that the PHY control block has finished doing period measurement of the DATX8 delay line digital test output.
 */
#define DDRPHY_DX_GSR1_DLTDONE_MASK (0x1U)
#define DDRPHY_DX_GSR1_DLTDONE_SHIFT (0U)
#define DDRPHY_DX_GSR1_DLTDONE_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR1_DLTDONE_MASK) >> DDRPHY_DX_GSR1_DLTDONE_SHIFT)

/* Bitfield definition for register of struct array DX: BDLR0 */
/*
 * DQ4WBD (R/W)
 *
 * DQ4 Write Bit Delay: Delay select for the BDL on DQ4 write path.
 */
#define DDRPHY_DX_BDLR0_DQ4WBD_MASK (0x3F000000UL)
#define DDRPHY_DX_BDLR0_DQ4WBD_SHIFT (24U)
#define DDRPHY_DX_BDLR0_DQ4WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR0_DQ4WBD_SHIFT) & DDRPHY_DX_BDLR0_DQ4WBD_MASK)
#define DDRPHY_DX_BDLR0_DQ4WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR0_DQ4WBD_MASK) >> DDRPHY_DX_BDLR0_DQ4WBD_SHIFT)

/*
 * DQ3WBD (R/W)
 *
 * DQ3 Write Bit Delay: Delay select for the BDL on DQ3 write path
 */
#define DDRPHY_DX_BDLR0_DQ3WBD_MASK (0xFC0000UL)
#define DDRPHY_DX_BDLR0_DQ3WBD_SHIFT (18U)
#define DDRPHY_DX_BDLR0_DQ3WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR0_DQ3WBD_SHIFT) & DDRPHY_DX_BDLR0_DQ3WBD_MASK)
#define DDRPHY_DX_BDLR0_DQ3WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR0_DQ3WBD_MASK) >> DDRPHY_DX_BDLR0_DQ3WBD_SHIFT)

/*
 * DQ2WBD (R/W)
 *
 * DQ2 Write Bit Delay: Delay select for the BDL on DQ2 write path.
 */
#define DDRPHY_DX_BDLR0_DQ2WBD_MASK (0x3F000UL)
#define DDRPHY_DX_BDLR0_DQ2WBD_SHIFT (12U)
#define DDRPHY_DX_BDLR0_DQ2WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR0_DQ2WBD_SHIFT) & DDRPHY_DX_BDLR0_DQ2WBD_MASK)
#define DDRPHY_DX_BDLR0_DQ2WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR0_DQ2WBD_MASK) >> DDRPHY_DX_BDLR0_DQ2WBD_SHIFT)

/*
 * DQ1WBD (R/W)
 *
 * DQ1 Write Bit Delay: Delay select for the BDL on DQ1 write path.
 */
#define DDRPHY_DX_BDLR0_DQ1WBD_MASK (0xFC0U)
#define DDRPHY_DX_BDLR0_DQ1WBD_SHIFT (6U)
#define DDRPHY_DX_BDLR0_DQ1WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR0_DQ1WBD_SHIFT) & DDRPHY_DX_BDLR0_DQ1WBD_MASK)
#define DDRPHY_DX_BDLR0_DQ1WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR0_DQ1WBD_MASK) >> DDRPHY_DX_BDLR0_DQ1WBD_SHIFT)

/*
 * DQ0WBD (R/W)
 *
 * DQ0 Write Bit Delay: Delay select for the BDL on DQ0 write path.
 */
#define DDRPHY_DX_BDLR0_DQ0WBD_MASK (0x3FU)
#define DDRPHY_DX_BDLR0_DQ0WBD_SHIFT (0U)
#define DDRPHY_DX_BDLR0_DQ0WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR0_DQ0WBD_SHIFT) & DDRPHY_DX_BDLR0_DQ0WBD_MASK)
#define DDRPHY_DX_BDLR0_DQ0WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR0_DQ0WBD_MASK) >> DDRPHY_DX_BDLR0_DQ0WBD_SHIFT)

/* Bitfield definition for register of struct array DX: BDLR1 */
/*
 * DSWBD (R/W)
 *
 * DQS Write Bit Delay: Delay select for the BDL on DQS write path
 */
#define DDRPHY_DX_BDLR1_DSWBD_MASK (0x3F000000UL)
#define DDRPHY_DX_BDLR1_DSWBD_SHIFT (24U)
#define DDRPHY_DX_BDLR1_DSWBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR1_DSWBD_SHIFT) & DDRPHY_DX_BDLR1_DSWBD_MASK)
#define DDRPHY_DX_BDLR1_DSWBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR1_DSWBD_MASK) >> DDRPHY_DX_BDLR1_DSWBD_SHIFT)

/*
 * DMWBD (R/W)
 *
 * DM Write Bit Delay: Delay select for the BDL on DM write path.
 */
#define DDRPHY_DX_BDLR1_DMWBD_MASK (0xFC0000UL)
#define DDRPHY_DX_BDLR1_DMWBD_SHIFT (18U)
#define DDRPHY_DX_BDLR1_DMWBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR1_DMWBD_SHIFT) & DDRPHY_DX_BDLR1_DMWBD_MASK)
#define DDRPHY_DX_BDLR1_DMWBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR1_DMWBD_MASK) >> DDRPHY_DX_BDLR1_DMWBD_SHIFT)

/*
 * DQ7WBD (R/W)
 *
 * DQ7 Write Bit Delay: Delay select for the BDL on DQ7 write path.
 */
#define DDRPHY_DX_BDLR1_DQ7WBD_MASK (0x3F000UL)
#define DDRPHY_DX_BDLR1_DQ7WBD_SHIFT (12U)
#define DDRPHY_DX_BDLR1_DQ7WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR1_DQ7WBD_SHIFT) & DDRPHY_DX_BDLR1_DQ7WBD_MASK)
#define DDRPHY_DX_BDLR1_DQ7WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR1_DQ7WBD_MASK) >> DDRPHY_DX_BDLR1_DQ7WBD_SHIFT)

/*
 * DQ6WBD (R/W)
 *
 * DQ6 Write Bit Delay: Delay select for the BDL on DQ6 write path.
 */
#define DDRPHY_DX_BDLR1_DQ6WBD_MASK (0xFC0U)
#define DDRPHY_DX_BDLR1_DQ6WBD_SHIFT (6U)
#define DDRPHY_DX_BDLR1_DQ6WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR1_DQ6WBD_SHIFT) & DDRPHY_DX_BDLR1_DQ6WBD_MASK)
#define DDRPHY_DX_BDLR1_DQ6WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR1_DQ6WBD_MASK) >> DDRPHY_DX_BDLR1_DQ6WBD_SHIFT)

/*
 * DQ5WBD (R/W)
 *
 * DQ5 Write Bit Delay: Delay select for the BDL on DQ5 write path.
 */
#define DDRPHY_DX_BDLR1_DQ5WBD_MASK (0x3FU)
#define DDRPHY_DX_BDLR1_DQ5WBD_SHIFT (0U)
#define DDRPHY_DX_BDLR1_DQ5WBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR1_DQ5WBD_SHIFT) & DDRPHY_DX_BDLR1_DQ5WBD_MASK)
#define DDRPHY_DX_BDLR1_DQ5WBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR1_DQ5WBD_MASK) >> DDRPHY_DX_BDLR1_DQ5WBD_SHIFT)

/* Bitfield definition for register of struct array DX: BDLR2 */
/*
 * DSNRBD (R/W)
 *
 * DQSN Read Bit Delay (Type B/B1 PHY Only): Delay select for the BDL on DQSN read path
 */
#define DDRPHY_DX_BDLR2_DSNRBD_MASK (0xFC0000UL)
#define DDRPHY_DX_BDLR2_DSNRBD_SHIFT (18U)
#define DDRPHY_DX_BDLR2_DSNRBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR2_DSNRBD_SHIFT) & DDRPHY_DX_BDLR2_DSNRBD_MASK)
#define DDRPHY_DX_BDLR2_DSNRBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR2_DSNRBD_MASK) >> DDRPHY_DX_BDLR2_DSNRBD_SHIFT)

/*
 * DSRBD (R/W)
 *
 * DQS Read Bit Delay: Delay select for the BDL on DQS read path
 */
#define DDRPHY_DX_BDLR2_DSRBD_MASK (0x3F000UL)
#define DDRPHY_DX_BDLR2_DSRBD_SHIFT (12U)
#define DDRPHY_DX_BDLR2_DSRBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR2_DSRBD_SHIFT) & DDRPHY_DX_BDLR2_DSRBD_MASK)
#define DDRPHY_DX_BDLR2_DSRBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR2_DSRBD_MASK) >> DDRPHY_DX_BDLR2_DSRBD_SHIFT)

/*
 * DQOEBD (R/W)
 *
 * DQ Output Enable Bit Delay: Delay select for the BDL on DQ/DM output enable path.
 */
#define DDRPHY_DX_BDLR2_DQOEBD_MASK (0xFC0U)
#define DDRPHY_DX_BDLR2_DQOEBD_SHIFT (6U)
#define DDRPHY_DX_BDLR2_DQOEBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR2_DQOEBD_SHIFT) & DDRPHY_DX_BDLR2_DQOEBD_MASK)
#define DDRPHY_DX_BDLR2_DQOEBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR2_DQOEBD_MASK) >> DDRPHY_DX_BDLR2_DQOEBD_SHIFT)

/*
 * DSOEBD (R/W)
 *
 * DQS Output Enable Bit Delay: Delay select for the BDL on DQS output enable path
 */
#define DDRPHY_DX_BDLR2_DSOEBD_MASK (0x3FU)
#define DDRPHY_DX_BDLR2_DSOEBD_SHIFT (0U)
#define DDRPHY_DX_BDLR2_DSOEBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR2_DSOEBD_SHIFT) & DDRPHY_DX_BDLR2_DSOEBD_MASK)
#define DDRPHY_DX_BDLR2_DSOEBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR2_DSOEBD_MASK) >> DDRPHY_DX_BDLR2_DSOEBD_SHIFT)

/* Bitfield definition for register of struct array DX: BDLR3 */
/*
 * DQ4RBD (R/W)
 *
 * DQ4 Read Bit Delay: Delay select for the BDL on DQ4 read path.
 */
#define DDRPHY_DX_BDLR3_DQ4RBD_MASK (0x3F000000UL)
#define DDRPHY_DX_BDLR3_DQ4RBD_SHIFT (24U)
#define DDRPHY_DX_BDLR3_DQ4RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR3_DQ4RBD_SHIFT) & DDRPHY_DX_BDLR3_DQ4RBD_MASK)
#define DDRPHY_DX_BDLR3_DQ4RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR3_DQ4RBD_MASK) >> DDRPHY_DX_BDLR3_DQ4RBD_SHIFT)

/*
 * DQ3RBD (R/W)
 *
 * DQ3 Read Bit Delay: Delay select for the BDL on DQ3 read path
 */
#define DDRPHY_DX_BDLR3_DQ3RBD_MASK (0xFC0000UL)
#define DDRPHY_DX_BDLR3_DQ3RBD_SHIFT (18U)
#define DDRPHY_DX_BDLR3_DQ3RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR3_DQ3RBD_SHIFT) & DDRPHY_DX_BDLR3_DQ3RBD_MASK)
#define DDRPHY_DX_BDLR3_DQ3RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR3_DQ3RBD_MASK) >> DDRPHY_DX_BDLR3_DQ3RBD_SHIFT)

/*
 * DQ2RBD (R/W)
 *
 * DQ2 Read Bit Delay: Delay select for the BDL on DQ2 read path.
 */
#define DDRPHY_DX_BDLR3_DQ2RBD_MASK (0x3F000UL)
#define DDRPHY_DX_BDLR3_DQ2RBD_SHIFT (12U)
#define DDRPHY_DX_BDLR3_DQ2RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR3_DQ2RBD_SHIFT) & DDRPHY_DX_BDLR3_DQ2RBD_MASK)
#define DDRPHY_DX_BDLR3_DQ2RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR3_DQ2RBD_MASK) >> DDRPHY_DX_BDLR3_DQ2RBD_SHIFT)

/*
 * DQ1RBD (R/W)
 *
 * DQ1 Read Bit Delay: Delay select for the BDL on DQ1 read path.
 */
#define DDRPHY_DX_BDLR3_DQ1RBD_MASK (0xFC0U)
#define DDRPHY_DX_BDLR3_DQ1RBD_SHIFT (6U)
#define DDRPHY_DX_BDLR3_DQ1RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR3_DQ1RBD_SHIFT) & DDRPHY_DX_BDLR3_DQ1RBD_MASK)
#define DDRPHY_DX_BDLR3_DQ1RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR3_DQ1RBD_MASK) >> DDRPHY_DX_BDLR3_DQ1RBD_SHIFT)

/*
 * DQ0RBD (R/W)
 *
 * DQ0 Read Bit Delay: Delay select for the BDL on DQ0 read path.
 */
#define DDRPHY_DX_BDLR3_DQ0RBD_MASK (0x3FU)
#define DDRPHY_DX_BDLR3_DQ0RBD_SHIFT (0U)
#define DDRPHY_DX_BDLR3_DQ0RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR3_DQ0RBD_SHIFT) & DDRPHY_DX_BDLR3_DQ0RBD_MASK)
#define DDRPHY_DX_BDLR3_DQ0RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR3_DQ0RBD_MASK) >> DDRPHY_DX_BDLR3_DQ0RBD_SHIFT)

/* Bitfield definition for register of struct array DX: BDLR4 */
/*
 * DMRBD (R/W)
 *
 * DM Read Bit Delay: Delay select for the BDL on DM read path.
 */
#define DDRPHY_DX_BDLR4_DMRBD_MASK (0xFC0000UL)
#define DDRPHY_DX_BDLR4_DMRBD_SHIFT (18U)
#define DDRPHY_DX_BDLR4_DMRBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR4_DMRBD_SHIFT) & DDRPHY_DX_BDLR4_DMRBD_MASK)
#define DDRPHY_DX_BDLR4_DMRBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR4_DMRBD_MASK) >> DDRPHY_DX_BDLR4_DMRBD_SHIFT)

/*
 * DQ7RBD (R/W)
 *
 * DQ7 Read Bit Delay: Delay select for the BDL on DQ7 read path.
 */
#define DDRPHY_DX_BDLR4_DQ7RBD_MASK (0x3F000UL)
#define DDRPHY_DX_BDLR4_DQ7RBD_SHIFT (12U)
#define DDRPHY_DX_BDLR4_DQ7RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR4_DQ7RBD_SHIFT) & DDRPHY_DX_BDLR4_DQ7RBD_MASK)
#define DDRPHY_DX_BDLR4_DQ7RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR4_DQ7RBD_MASK) >> DDRPHY_DX_BDLR4_DQ7RBD_SHIFT)

/*
 * DQ6RBD (R/W)
 *
 * DQ6 Read Bit Delay: Delay select for the BDL on DQ6 read path.
 */
#define DDRPHY_DX_BDLR4_DQ6RBD_MASK (0xFC0U)
#define DDRPHY_DX_BDLR4_DQ6RBD_SHIFT (6U)
#define DDRPHY_DX_BDLR4_DQ6RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR4_DQ6RBD_SHIFT) & DDRPHY_DX_BDLR4_DQ6RBD_MASK)
#define DDRPHY_DX_BDLR4_DQ6RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR4_DQ6RBD_MASK) >> DDRPHY_DX_BDLR4_DQ6RBD_SHIFT)

/*
 * DQ5RBD (R/W)
 *
 * DQ5 Read Bit Delay: Delay select for the BDL on DQ5 read path.
 */
#define DDRPHY_DX_BDLR4_DQ5RBD_MASK (0x3FU)
#define DDRPHY_DX_BDLR4_DQ5RBD_SHIFT (0U)
#define DDRPHY_DX_BDLR4_DQ5RBD_SET(x) (((uint32_t)(x) << DDRPHY_DX_BDLR4_DQ5RBD_SHIFT) & DDRPHY_DX_BDLR4_DQ5RBD_MASK)
#define DDRPHY_DX_BDLR4_DQ5RBD_GET(x) (((uint32_t)(x) & DDRPHY_DX_BDLR4_DQ5RBD_MASK) >> DDRPHY_DX_BDLR4_DQ5RBD_SHIFT)

/* Bitfield definition for register of struct array DX: LCDLR0 */
/*
 * R3WLD (R/W)
 *
 * Rank 3 Write Leveling Delay: Rank 3 delay select for the write leveling (WL) LCDL
 */
#define DDRPHY_DX_LCDLR0_R3WLD_MASK (0xFF000000UL)
#define DDRPHY_DX_LCDLR0_R3WLD_SHIFT (24U)
#define DDRPHY_DX_LCDLR0_R3WLD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR0_R3WLD_SHIFT) & DDRPHY_DX_LCDLR0_R3WLD_MASK)
#define DDRPHY_DX_LCDLR0_R3WLD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR0_R3WLD_MASK) >> DDRPHY_DX_LCDLR0_R3WLD_SHIFT)

/*
 * R2WLD (R/W)
 *
 * Rank 2 Write Leveling Delay: Rank 2 delay select for the write leveling (WL) LCDL
 */
#define DDRPHY_DX_LCDLR0_R2WLD_MASK (0xFF0000UL)
#define DDRPHY_DX_LCDLR0_R2WLD_SHIFT (16U)
#define DDRPHY_DX_LCDLR0_R2WLD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR0_R2WLD_SHIFT) & DDRPHY_DX_LCDLR0_R2WLD_MASK)
#define DDRPHY_DX_LCDLR0_R2WLD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR0_R2WLD_MASK) >> DDRPHY_DX_LCDLR0_R2WLD_SHIFT)

/*
 * R1WLD (R/W)
 *
 * Rank 1 Write Leveling Delay: Rank 1 delay select for the write leveling (WL) LCDL
 */
#define DDRPHY_DX_LCDLR0_R1WLD_MASK (0xFF00U)
#define DDRPHY_DX_LCDLR0_R1WLD_SHIFT (8U)
#define DDRPHY_DX_LCDLR0_R1WLD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR0_R1WLD_SHIFT) & DDRPHY_DX_LCDLR0_R1WLD_MASK)
#define DDRPHY_DX_LCDLR0_R1WLD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR0_R1WLD_MASK) >> DDRPHY_DX_LCDLR0_R1WLD_SHIFT)

/*
 * R0WLD (R/W)
 *
 * Rank 0 Write Leveling Delay: Rank 0 delay select for the write leveling (WL) LCDL
 */
#define DDRPHY_DX_LCDLR0_R0WLD_MASK (0xFFU)
#define DDRPHY_DX_LCDLR0_R0WLD_SHIFT (0U)
#define DDRPHY_DX_LCDLR0_R0WLD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR0_R0WLD_SHIFT) & DDRPHY_DX_LCDLR0_R0WLD_MASK)
#define DDRPHY_DX_LCDLR0_R0WLD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR0_R0WLD_MASK) >> DDRPHY_DX_LCDLR0_R0WLD_SHIFT)

/* Bitfield definition for register of struct array DX: LCDLR1 */
/*
 * RDQSND (R/W)
 *
 * Read DQSN Delay (Type B/B1 PHY Only): Delay select for the read DQSN (RDQS) LCDL
 */
#define DDRPHY_DX_LCDLR1_RDQSND_MASK (0xFF0000UL)
#define DDRPHY_DX_LCDLR1_RDQSND_SHIFT (16U)
#define DDRPHY_DX_LCDLR1_RDQSND_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR1_RDQSND_SHIFT) & DDRPHY_DX_LCDLR1_RDQSND_MASK)
#define DDRPHY_DX_LCDLR1_RDQSND_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR1_RDQSND_MASK) >> DDRPHY_DX_LCDLR1_RDQSND_SHIFT)

/*
 * RDQSD (R/W)
 *
 * Read DQS Delay: Delay select for the read DQS (RDQS) LCDL
 */
#define DDRPHY_DX_LCDLR1_RDQSD_MASK (0xFF00U)
#define DDRPHY_DX_LCDLR1_RDQSD_SHIFT (8U)
#define DDRPHY_DX_LCDLR1_RDQSD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR1_RDQSD_SHIFT) & DDRPHY_DX_LCDLR1_RDQSD_MASK)
#define DDRPHY_DX_LCDLR1_RDQSD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR1_RDQSD_MASK) >> DDRPHY_DX_LCDLR1_RDQSD_SHIFT)

/*
 * WDQD (R/W)
 *
 * Write Data Delay: Delay select for the write data (WDQ) LCDL
 */
#define DDRPHY_DX_LCDLR1_WDQD_MASK (0xFFU)
#define DDRPHY_DX_LCDLR1_WDQD_SHIFT (0U)
#define DDRPHY_DX_LCDLR1_WDQD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR1_WDQD_SHIFT) & DDRPHY_DX_LCDLR1_WDQD_MASK)
#define DDRPHY_DX_LCDLR1_WDQD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR1_WDQD_MASK) >> DDRPHY_DX_LCDLR1_WDQD_SHIFT)

/* Bitfield definition for register of struct array DX: LCDLR2 */
/*
 * R3DQSGD (R/W)
 *
 * Rank 3 Read DQS Gating Delay: Rank 3 delay select for the read DQS gating (DQSG) LCDL
 */
#define DDRPHY_DX_LCDLR2_R3DQSGD_MASK (0xFF000000UL)
#define DDRPHY_DX_LCDLR2_R3DQSGD_SHIFT (24U)
#define DDRPHY_DX_LCDLR2_R3DQSGD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR2_R3DQSGD_SHIFT) & DDRPHY_DX_LCDLR2_R3DQSGD_MASK)
#define DDRPHY_DX_LCDLR2_R3DQSGD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR2_R3DQSGD_MASK) >> DDRPHY_DX_LCDLR2_R3DQSGD_SHIFT)

/*
 * R2DQSGD (R/W)
 *
 * Rank 2 Read DQS Gating Delay: Rank 2 delay select for the read DQS gating (DQSG) LCDL
 */
#define DDRPHY_DX_LCDLR2_R2DQSGD_MASK (0xFF0000UL)
#define DDRPHY_DX_LCDLR2_R2DQSGD_SHIFT (16U)
#define DDRPHY_DX_LCDLR2_R2DQSGD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR2_R2DQSGD_SHIFT) & DDRPHY_DX_LCDLR2_R2DQSGD_MASK)
#define DDRPHY_DX_LCDLR2_R2DQSGD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR2_R2DQSGD_MASK) >> DDRPHY_DX_LCDLR2_R2DQSGD_SHIFT)

/*
 * R1DQSGD (R/W)
 *
 * Rank 1 Read DQS Gating Delay: Rank 1 delay select for the read DQS gating (DQSG) LCDL
 */
#define DDRPHY_DX_LCDLR2_R1DQSGD_MASK (0xFF00U)
#define DDRPHY_DX_LCDLR2_R1DQSGD_SHIFT (8U)
#define DDRPHY_DX_LCDLR2_R1DQSGD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR2_R1DQSGD_SHIFT) & DDRPHY_DX_LCDLR2_R1DQSGD_MASK)
#define DDRPHY_DX_LCDLR2_R1DQSGD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR2_R1DQSGD_MASK) >> DDRPHY_DX_LCDLR2_R1DQSGD_SHIFT)

/*
 * R0DQSGD (R/W)
 *
 * Rank 0 Read DQS Gating Delay: Rank 0 delay select for the read DQS gating (DQSG) LCDL
 */
#define DDRPHY_DX_LCDLR2_R0DQSGD_MASK (0xFFU)
#define DDRPHY_DX_LCDLR2_R0DQSGD_SHIFT (0U)
#define DDRPHY_DX_LCDLR2_R0DQSGD_SET(x) (((uint32_t)(x) << DDRPHY_DX_LCDLR2_R0DQSGD_SHIFT) & DDRPHY_DX_LCDLR2_R0DQSGD_MASK)
#define DDRPHY_DX_LCDLR2_R0DQSGD_GET(x) (((uint32_t)(x) & DDRPHY_DX_LCDLR2_R0DQSGD_MASK) >> DDRPHY_DX_LCDLR2_R0DQSGD_SHIFT)

/* Bitfield definition for register of struct array DX: MDLR */
/*
 * MDLD (R/W)
 *
 * MDL Delay: Delay select for the LCDL for the Master Delay Line.
 */
#define DDRPHY_DX_MDLR_MDLD_MASK (0xFF0000UL)
#define DDRPHY_DX_MDLR_MDLD_SHIFT (16U)
#define DDRPHY_DX_MDLR_MDLD_SET(x) (((uint32_t)(x) << DDRPHY_DX_MDLR_MDLD_SHIFT) & DDRPHY_DX_MDLR_MDLD_MASK)
#define DDRPHY_DX_MDLR_MDLD_GET(x) (((uint32_t)(x) & DDRPHY_DX_MDLR_MDLD_MASK) >> DDRPHY_DX_MDLR_MDLD_SHIFT)

/*
 * TPRD (R/W)
 *
 * Target Period: Target period measured by the master delay line calibration for VT drift compensation. This is the current measured value of the period and is continuously updated if the MDL is enabled to do so.
 */
#define DDRPHY_DX_MDLR_TPRD_MASK (0xFF00U)
#define DDRPHY_DX_MDLR_TPRD_SHIFT (8U)
#define DDRPHY_DX_MDLR_TPRD_SET(x) (((uint32_t)(x) << DDRPHY_DX_MDLR_TPRD_SHIFT) & DDRPHY_DX_MDLR_TPRD_MASK)
#define DDRPHY_DX_MDLR_TPRD_GET(x) (((uint32_t)(x) & DDRPHY_DX_MDLR_TPRD_MASK) >> DDRPHY_DX_MDLR_TPRD_SHIFT)

/*
 * IPRD (R/W)
 *
 * Initial Period: Initial period measured by the master delay line calibration for VT drift compensation. This value is used as the denominator when calculating the ratios of updates during VT compensation.
 */
#define DDRPHY_DX_MDLR_IPRD_MASK (0xFFU)
#define DDRPHY_DX_MDLR_IPRD_SHIFT (0U)
#define DDRPHY_DX_MDLR_IPRD_SET(x) (((uint32_t)(x) << DDRPHY_DX_MDLR_IPRD_SHIFT) & DDRPHY_DX_MDLR_IPRD_MASK)
#define DDRPHY_DX_MDLR_IPRD_GET(x) (((uint32_t)(x) & DDRPHY_DX_MDLR_IPRD_MASK) >> DDRPHY_DX_MDLR_IPRD_SHIFT)

/* Bitfield definition for register of struct array DX: GTR */
/*
 * R3WLSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R3WLSL_MASK (0xC0000UL)
#define DDRPHY_DX_GTR_R3WLSL_SHIFT (18U)
#define DDRPHY_DX_GTR_R3WLSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R3WLSL_SHIFT) & DDRPHY_DX_GTR_R3WLSL_MASK)
#define DDRPHY_DX_GTR_R3WLSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R3WLSL_MASK) >> DDRPHY_DX_GTR_R3WLSL_SHIFT)

/*
 * R2WLSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R2WLSL_MASK (0x30000UL)
#define DDRPHY_DX_GTR_R2WLSL_SHIFT (16U)
#define DDRPHY_DX_GTR_R2WLSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R2WLSL_SHIFT) & DDRPHY_DX_GTR_R2WLSL_MASK)
#define DDRPHY_DX_GTR_R2WLSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R2WLSL_MASK) >> DDRPHY_DX_GTR_R2WLSL_SHIFT)

/*
 * R1WLSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R1WLSL_MASK (0xC000U)
#define DDRPHY_DX_GTR_R1WLSL_SHIFT (14U)
#define DDRPHY_DX_GTR_R1WLSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R1WLSL_SHIFT) & DDRPHY_DX_GTR_R1WLSL_MASK)
#define DDRPHY_DX_GTR_R1WLSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R1WLSL_MASK) >> DDRPHY_DX_GTR_R1WLSL_SHIFT)

/*
 * R0WLSL (R/W)
 *
 * Rank n Write Leveling System Latency: This is used to adjust the write latency after write leveling. Power-up default is 01 (i.e. no extra clock cycles required). The SL fields are initially set by the PUB during automatic write leveling but these values can be overwritten by a direct write to this register. Every two bits of this register control the latency of each of the (up to) four ranks. R0WLSL controls the latency of rank 0, R1WLSL controls rank 1, and so on. Valid values:
 * 00 = Write latency = WL - 1 01 = Write latency = WL
 * 10 = Write latency = WL + 1 11 = Reserved
 */
#define DDRPHY_DX_GTR_R0WLSL_MASK (0x3000U)
#define DDRPHY_DX_GTR_R0WLSL_SHIFT (12U)
#define DDRPHY_DX_GTR_R0WLSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R0WLSL_SHIFT) & DDRPHY_DX_GTR_R0WLSL_MASK)
#define DDRPHY_DX_GTR_R0WLSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R0WLSL_MASK) >> DDRPHY_DX_GTR_R0WLSL_SHIFT)

/*
 * R3DGSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R3DGSL_MASK (0xE00U)
#define DDRPHY_DX_GTR_R3DGSL_SHIFT (9U)
#define DDRPHY_DX_GTR_R3DGSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R3DGSL_SHIFT) & DDRPHY_DX_GTR_R3DGSL_MASK)
#define DDRPHY_DX_GTR_R3DGSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R3DGSL_MASK) >> DDRPHY_DX_GTR_R3DGSL_SHIFT)

/*
 * R2DGSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R2DGSL_MASK (0x1C0U)
#define DDRPHY_DX_GTR_R2DGSL_SHIFT (6U)
#define DDRPHY_DX_GTR_R2DGSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R2DGSL_SHIFT) & DDRPHY_DX_GTR_R2DGSL_MASK)
#define DDRPHY_DX_GTR_R2DGSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R2DGSL_MASK) >> DDRPHY_DX_GTR_R2DGSL_SHIFT)

/*
 * R1DGSL (R/W)
 *
 */
#define DDRPHY_DX_GTR_R1DGSL_MASK (0x38U)
#define DDRPHY_DX_GTR_R1DGSL_SHIFT (3U)
#define DDRPHY_DX_GTR_R1DGSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R1DGSL_SHIFT) & DDRPHY_DX_GTR_R1DGSL_MASK)
#define DDRPHY_DX_GTR_R1DGSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R1DGSL_MASK) >> DDRPHY_DX_GTR_R1DGSL_SHIFT)

/*
 * R0DGSL (R/W)
 *
 * Rank n DQS Gating System Latency: This is used to increase the number of clock cycles needed to expect valid DDR read data by up to seven extra clock cycles.
 * This is used to compensate for board delays and other system delays. Power-up default is 000 (i.e. no extra clock cycles required). The SL fields are initially set by the PUB during automatic DQS data training but these values can be overwritten by a direct write to this register. Every three bits of this register control the latency of each of the (up to) four ranks. R0DGSL controls the latency of rank 0, R1DGSL controls rank 1, and so on. Valid values are 0 to 7:
 */
#define DDRPHY_DX_GTR_R0DGSL_MASK (0x7U)
#define DDRPHY_DX_GTR_R0DGSL_SHIFT (0U)
#define DDRPHY_DX_GTR_R0DGSL_SET(x) (((uint32_t)(x) << DDRPHY_DX_GTR_R0DGSL_SHIFT) & DDRPHY_DX_GTR_R0DGSL_MASK)
#define DDRPHY_DX_GTR_R0DGSL_GET(x) (((uint32_t)(x) & DDRPHY_DX_GTR_R0DGSL_MASK) >> DDRPHY_DX_GTR_R0DGSL_SHIFT)

/* Bitfield definition for register of struct array DX: GSR2 */
/*
 * ESTAT (R/W)
 *
 * Error Status: If an error occurred for this lane as indicated by RDERR, WDERR, REERR or WEERR the error status code can provide additional information regard when the error occurred during the algorithm execution.
 */
#define DDRPHY_DX_GSR2_ESTAT_MASK (0xF00U)
#define DDRPHY_DX_GSR2_ESTAT_SHIFT (8U)
#define DDRPHY_DX_GSR2_ESTAT_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_ESTAT_SHIFT) & DDRPHY_DX_GSR2_ESTAT_MASK)
#define DDRPHY_DX_GSR2_ESTAT_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_ESTAT_MASK) >> DDRPHY_DX_GSR2_ESTAT_SHIFT)

/*
 * WEWN (R/W)
 *
 * Write Data Eye Training Warning: Indicates, if set, that the DATX8 has encountered a warning during execution of the write data eye training.
 */
#define DDRPHY_DX_GSR2_WEWN_MASK (0x80U)
#define DDRPHY_DX_GSR2_WEWN_SHIFT (7U)
#define DDRPHY_DX_GSR2_WEWN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_WEWN_SHIFT) & DDRPHY_DX_GSR2_WEWN_MASK)
#define DDRPHY_DX_GSR2_WEWN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_WEWN_MASK) >> DDRPHY_DX_GSR2_WEWN_SHIFT)

/*
 * WEERR (R/W)
 *
 * Write Data Eye Training Error: Indicates, if set, that the DATX8 has encountered an error during execution of the write data eye training.
 */
#define DDRPHY_DX_GSR2_WEERR_MASK (0x40U)
#define DDRPHY_DX_GSR2_WEERR_SHIFT (6U)
#define DDRPHY_DX_GSR2_WEERR_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_WEERR_SHIFT) & DDRPHY_DX_GSR2_WEERR_MASK)
#define DDRPHY_DX_GSR2_WEERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_WEERR_MASK) >> DDRPHY_DX_GSR2_WEERR_SHIFT)

/*
 * REWN (R/W)
 *
 * Read Data Eye Training Warning: Indicates, if set, that the DATX8 has encountered a warning during execution of the read data eye training.
 */
#define DDRPHY_DX_GSR2_REWN_MASK (0x20U)
#define DDRPHY_DX_GSR2_REWN_SHIFT (5U)
#define DDRPHY_DX_GSR2_REWN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_REWN_SHIFT) & DDRPHY_DX_GSR2_REWN_MASK)
#define DDRPHY_DX_GSR2_REWN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_REWN_MASK) >> DDRPHY_DX_GSR2_REWN_SHIFT)

/*
 * REERR (R/W)
 *
 * Read Data Eye Training Error: Indicates, if set, that the DATX8 has encountered an error during execution of the read data eye training.
 */
#define DDRPHY_DX_GSR2_REERR_MASK (0x10U)
#define DDRPHY_DX_GSR2_REERR_SHIFT (4U)
#define DDRPHY_DX_GSR2_REERR_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_REERR_SHIFT) & DDRPHY_DX_GSR2_REERR_MASK)
#define DDRPHY_DX_GSR2_REERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_REERR_MASK) >> DDRPHY_DX_GSR2_REERR_SHIFT)

/*
 * WDWN (R/W)
 *
 * Write Bit Deskew Warning: Indicates, if set, that the DATX8 has encountered a warning during execution of the write bit deskew training.
 */
#define DDRPHY_DX_GSR2_WDWN_MASK (0x8U)
#define DDRPHY_DX_GSR2_WDWN_SHIFT (3U)
#define DDRPHY_DX_GSR2_WDWN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_WDWN_SHIFT) & DDRPHY_DX_GSR2_WDWN_MASK)
#define DDRPHY_DX_GSR2_WDWN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_WDWN_MASK) >> DDRPHY_DX_GSR2_WDWN_SHIFT)

/*
 * WDERR (R/W)
 *
 * Write Bit Deskew Error: Indicates, if set, that the DATX8 has encountered an error during execution of the write bit deskew training.
 */
#define DDRPHY_DX_GSR2_WDERR_MASK (0x4U)
#define DDRPHY_DX_GSR2_WDERR_SHIFT (2U)
#define DDRPHY_DX_GSR2_WDERR_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_WDERR_SHIFT) & DDRPHY_DX_GSR2_WDERR_MASK)
#define DDRPHY_DX_GSR2_WDERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_WDERR_MASK) >> DDRPHY_DX_GSR2_WDERR_SHIFT)

/*
 * RDWN (R/W)
 *
 * Read Bit Deskew Warning: Indicates, if set, that the DATX8 has encountered a warning during execution of the read bit deskew training.
 */
#define DDRPHY_DX_GSR2_RDWN_MASK (0x2U)
#define DDRPHY_DX_GSR2_RDWN_SHIFT (1U)
#define DDRPHY_DX_GSR2_RDWN_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_RDWN_SHIFT) & DDRPHY_DX_GSR2_RDWN_MASK)
#define DDRPHY_DX_GSR2_RDWN_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_RDWN_MASK) >> DDRPHY_DX_GSR2_RDWN_SHIFT)

/*
 * RDERR (R/W)
 *
 * Read Bit Deskew Error: Indicates, if set, that the DATX8 has encountered an error during execution of the read bit deskew training.
 */
#define DDRPHY_DX_GSR2_RDERR_MASK (0x1U)
#define DDRPHY_DX_GSR2_RDERR_SHIFT (0U)
#define DDRPHY_DX_GSR2_RDERR_SET(x) (((uint32_t)(x) << DDRPHY_DX_GSR2_RDERR_SHIFT) & DDRPHY_DX_GSR2_RDERR_MASK)
#define DDRPHY_DX_GSR2_RDERR_GET(x) (((uint32_t)(x) & DDRPHY_DX_GSR2_RDERR_MASK) >> DDRPHY_DX_GSR2_RDERR_SHIFT)



/* ZQ register group index macro definition */
#define DDRPHY_ZQ_0 (0UL)
#define DDRPHY_ZQ_1 (1UL)
#define DDRPHY_ZQ_2 (2UL)
#define DDRPHY_ZQ_3 (3UL)

/* DX register group index macro definition */
#define DDRPHY_DX_0 (0UL)
#define DDRPHY_DX_1 (1UL)
#define DDRPHY_DX_2 (2UL)
#define DDRPHY_DX_3 (3UL)
#define DDRPHY_DX_4 (4UL)
#define DDRPHY_DX_5 (5UL)
#define DDRPHY_DX_6 (6UL)
#define DDRPHY_DX_7 (7UL)
#define DDRPHY_DX_8 (8UL)


#endif /* HPM_DDRPHY_H */

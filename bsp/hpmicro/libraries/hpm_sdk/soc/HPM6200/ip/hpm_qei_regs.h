/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_QEI_H
#define HPM_QEI_H

typedef struct {
    __RW uint32_t CR;                          /* 0x0: Control register */
    __RW uint32_t PHCFG;                       /* 0x4: Phase configure register */
    __RW uint32_t WDGCFG;                      /* 0x8: Watchdog configure register */
    __RW uint32_t PHIDX;                       /* 0xC: Phase index register */
    __RW uint32_t TRGOEN;                      /* 0x10: Tigger output enable register */
    __RW uint32_t READEN;                      /* 0x14: Read event enable register */
    __RW uint32_t ZCMP;                        /* 0x18: Z comparator */
    __RW uint32_t PHCMP;                       /* 0x1C: Phase comparator */
    __RW uint32_t SPDCMP;                      /* 0x20: Speed comparator */
    __RW uint32_t DMAEN;                       /* 0x24: DMA request enable register */
    __RW uint32_t SR;                          /* 0x28: Status register */
    __RW uint32_t IRQEN;                       /* 0x2C: Interrupt request register */
    struct {
        __RW uint32_t Z;                       /* 0x30: Z counter */
        __R  uint32_t PH;                      /* 0x34: Phase counter */
        __RW uint32_t SPD;                     /* 0x38: Speed counter */
        __R  uint32_t TMR;                     /* 0x3C: Timer counter */
    } COUNT[4];
    __R  uint32_t SPDHIS[4];                   /* 0x70 - 0x7C: Speed history */
} QEI_Type;


/* Bitfield definition for register: CR */
/*
 * READ (WO)
 *
 * 1- load phcnt, zcnt, spdcnt and tmrcnt into their read registers. Hardware auto-clear; read as 0
 */
#define QEI_CR_READ_MASK (0x80000000UL)
#define QEI_CR_READ_SHIFT (31U)
#define QEI_CR_READ_SET(x) (((uint32_t)(x) << QEI_CR_READ_SHIFT) & QEI_CR_READ_MASK)
#define QEI_CR_READ_GET(x) (((uint32_t)(x) & QEI_CR_READ_MASK) >> QEI_CR_READ_SHIFT)

/*
 * HRSTSPD (RW)
 *
 * 1- reset spdcnt when H assert
 */
#define QEI_CR_HRSTSPD_MASK (0x40000UL)
#define QEI_CR_HRSTSPD_SHIFT (18U)
#define QEI_CR_HRSTSPD_SET(x) (((uint32_t)(x) << QEI_CR_HRSTSPD_SHIFT) & QEI_CR_HRSTSPD_MASK)
#define QEI_CR_HRSTSPD_GET(x) (((uint32_t)(x) & QEI_CR_HRSTSPD_MASK) >> QEI_CR_HRSTSPD_SHIFT)

/*
 * HRSTPH (RW)
 *
 * 1- reset phcnt when H assert
 */
#define QEI_CR_HRSTPH_MASK (0x20000UL)
#define QEI_CR_HRSTPH_SHIFT (17U)
#define QEI_CR_HRSTPH_SET(x) (((uint32_t)(x) << QEI_CR_HRSTPH_SHIFT) & QEI_CR_HRSTPH_MASK)
#define QEI_CR_HRSTPH_GET(x) (((uint32_t)(x) & QEI_CR_HRSTPH_MASK) >> QEI_CR_HRSTPH_SHIFT)

/*
 * HRSTZ (RW)
 *
 * 1- reset zcnt when H assert
 */
#define QEI_CR_HRSTZ_MASK (0x10000UL)
#define QEI_CR_HRSTZ_SHIFT (16U)
#define QEI_CR_HRSTZ_SET(x) (((uint32_t)(x) << QEI_CR_HRSTZ_SHIFT) & QEI_CR_HRSTZ_MASK)
#define QEI_CR_HRSTZ_GET(x) (((uint32_t)(x) & QEI_CR_HRSTZ_MASK) >> QEI_CR_HRSTZ_SHIFT)

/*
 * PAUSESPD (RW)
 *
 * 1- pause spdcnt when PAUSE assert
 */
#define QEI_CR_PAUSESPD_MASK (0x4000U)
#define QEI_CR_PAUSESPD_SHIFT (14U)
#define QEI_CR_PAUSESPD_SET(x) (((uint32_t)(x) << QEI_CR_PAUSESPD_SHIFT) & QEI_CR_PAUSESPD_MASK)
#define QEI_CR_PAUSESPD_GET(x) (((uint32_t)(x) & QEI_CR_PAUSESPD_MASK) >> QEI_CR_PAUSESPD_SHIFT)

/*
 * PAUSEPH (RW)
 *
 * 1- pause phcnt when PAUSE assert
 */
#define QEI_CR_PAUSEPH_MASK (0x2000U)
#define QEI_CR_PAUSEPH_SHIFT (13U)
#define QEI_CR_PAUSEPH_SET(x) (((uint32_t)(x) << QEI_CR_PAUSEPH_SHIFT) & QEI_CR_PAUSEPH_MASK)
#define QEI_CR_PAUSEPH_GET(x) (((uint32_t)(x) & QEI_CR_PAUSEPH_MASK) >> QEI_CR_PAUSEPH_SHIFT)

/*
 * PAUSEZ (RW)
 *
 * 1- pause zcnt when PAUSE assert
 */
#define QEI_CR_PAUSEZ_MASK (0x1000U)
#define QEI_CR_PAUSEZ_SHIFT (12U)
#define QEI_CR_PAUSEZ_SET(x) (((uint32_t)(x) << QEI_CR_PAUSEZ_SHIFT) & QEI_CR_PAUSEZ_MASK)
#define QEI_CR_PAUSEZ_GET(x) (((uint32_t)(x) & QEI_CR_PAUSEZ_MASK) >> QEI_CR_PAUSEZ_SHIFT)

/*
 * HRDIR1 (RW)
 *
 * 1- HOMEF will set at H rising edge when dir == 1 (negative rotation direction)
 */
#define QEI_CR_HRDIR1_MASK (0x800U)
#define QEI_CR_HRDIR1_SHIFT (11U)
#define QEI_CR_HRDIR1_SET(x) (((uint32_t)(x) << QEI_CR_HRDIR1_SHIFT) & QEI_CR_HRDIR1_MASK)
#define QEI_CR_HRDIR1_GET(x) (((uint32_t)(x) & QEI_CR_HRDIR1_MASK) >> QEI_CR_HRDIR1_SHIFT)

/*
 * HRDIR0 (RW)
 *
 * 1- HOMEF will set at H rising edge when dir == 0 (positive rotation direction)
 */
#define QEI_CR_HRDIR0_MASK (0x400U)
#define QEI_CR_HRDIR0_SHIFT (10U)
#define QEI_CR_HRDIR0_SET(x) (((uint32_t)(x) << QEI_CR_HRDIR0_SHIFT) & QEI_CR_HRDIR0_MASK)
#define QEI_CR_HRDIR0_GET(x) (((uint32_t)(x) & QEI_CR_HRDIR0_MASK) >> QEI_CR_HRDIR0_SHIFT)

/*
 * HFDIR1 (RW)
 *
 * 1- HOMEF will set at H falling edge when dir == 1 (negative rotation direction)
 */
#define QEI_CR_HFDIR1_MASK (0x200U)
#define QEI_CR_HFDIR1_SHIFT (9U)
#define QEI_CR_HFDIR1_SET(x) (((uint32_t)(x) << QEI_CR_HFDIR1_SHIFT) & QEI_CR_HFDIR1_MASK)
#define QEI_CR_HFDIR1_GET(x) (((uint32_t)(x) & QEI_CR_HFDIR1_MASK) >> QEI_CR_HFDIR1_SHIFT)

/*
 * HFDIR0 (RW)
 *
 * 1- HOMEF will set at H falling edge when dir == 1 (positive rotation direction)
 */
#define QEI_CR_HFDIR0_MASK (0x100U)
#define QEI_CR_HFDIR0_SHIFT (8U)
#define QEI_CR_HFDIR0_SET(x) (((uint32_t)(x) << QEI_CR_HFDIR0_SHIFT) & QEI_CR_HFDIR0_MASK)
#define QEI_CR_HFDIR0_GET(x) (((uint32_t)(x) & QEI_CR_HFDIR0_MASK) >> QEI_CR_HFDIR0_SHIFT)

/*
 * SNAPEN (RW)
 *
 * 1- load phcnt, zcnt, spdcnt and tmrcnt into their snap registers when snapi input assert
 */
#define QEI_CR_SNAPEN_MASK (0x20U)
#define QEI_CR_SNAPEN_SHIFT (5U)
#define QEI_CR_SNAPEN_SET(x) (((uint32_t)(x) << QEI_CR_SNAPEN_SHIFT) & QEI_CR_SNAPEN_MASK)
#define QEI_CR_SNAPEN_GET(x) (((uint32_t)(x) & QEI_CR_SNAPEN_MASK) >> QEI_CR_SNAPEN_SHIFT)

/*
 * RSTCNT (RW)
 *
 * 1- reset zcnt, spdcnt and tmrcnt to 0. reset phcnt to phidx
 */
#define QEI_CR_RSTCNT_MASK (0x10U)
#define QEI_CR_RSTCNT_SHIFT (4U)
#define QEI_CR_RSTCNT_SET(x) (((uint32_t)(x) << QEI_CR_RSTCNT_SHIFT) & QEI_CR_RSTCNT_MASK)
#define QEI_CR_RSTCNT_GET(x) (((uint32_t)(x) & QEI_CR_RSTCNT_MASK) >> QEI_CR_RSTCNT_SHIFT)

/*
 * ENCTYP (RW)
 *
 * 00-abz; 01-pd; 10-ud; 11-reserved
 */
#define QEI_CR_ENCTYP_MASK (0x3U)
#define QEI_CR_ENCTYP_SHIFT (0U)
#define QEI_CR_ENCTYP_SET(x) (((uint32_t)(x) << QEI_CR_ENCTYP_SHIFT) & QEI_CR_ENCTYP_MASK)
#define QEI_CR_ENCTYP_GET(x) (((uint32_t)(x) & QEI_CR_ENCTYP_MASK) >> QEI_CR_ENCTYP_SHIFT)

/* Bitfield definition for register: PHCFG */
/*
 * ZCNTCFG (RW)
 *
 * 1- zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0
 * 0- zcnt will increment or decrement when Z input assert
 */
#define QEI_PHCFG_ZCNTCFG_MASK (0x400000UL)
#define QEI_PHCFG_ZCNTCFG_SHIFT (22U)
#define QEI_PHCFG_ZCNTCFG_SET(x) (((uint32_t)(x) << QEI_PHCFG_ZCNTCFG_SHIFT) & QEI_PHCFG_ZCNTCFG_MASK)
#define QEI_PHCFG_ZCNTCFG_GET(x) (((uint32_t)(x) & QEI_PHCFG_ZCNTCFG_MASK) >> QEI_PHCFG_ZCNTCFG_SHIFT)

/*
 * PHCALIZ (RW)
 *
 * 1- phcnt will set to phidx when Z input assert
 */
#define QEI_PHCFG_PHCALIZ_MASK (0x200000UL)
#define QEI_PHCFG_PHCALIZ_SHIFT (21U)
#define QEI_PHCFG_PHCALIZ_SET(x) (((uint32_t)(x) << QEI_PHCFG_PHCALIZ_SHIFT) & QEI_PHCFG_PHCALIZ_MASK)
#define QEI_PHCFG_PHCALIZ_GET(x) (((uint32_t)(x) & QEI_PHCFG_PHCALIZ_MASK) >> QEI_PHCFG_PHCALIZ_SHIFT)

/*
 * PHMAX (RW)
 *
 * maximum phcnt number, phcnt will rollover to 0 when it upcount to phmax
 */
#define QEI_PHCFG_PHMAX_MASK (0x1FFFFFUL)
#define QEI_PHCFG_PHMAX_SHIFT (0U)
#define QEI_PHCFG_PHMAX_SET(x) (((uint32_t)(x) << QEI_PHCFG_PHMAX_SHIFT) & QEI_PHCFG_PHMAX_MASK)
#define QEI_PHCFG_PHMAX_GET(x) (((uint32_t)(x) & QEI_PHCFG_PHMAX_MASK) >> QEI_PHCFG_PHMAX_SHIFT)

/* Bitfield definition for register: WDGCFG */
/*
 * WDGEN (RW)
 *
 * 1- enable wdog counter
 */
#define QEI_WDGCFG_WDGEN_MASK (0x80000000UL)
#define QEI_WDGCFG_WDGEN_SHIFT (31U)
#define QEI_WDGCFG_WDGEN_SET(x) (((uint32_t)(x) << QEI_WDGCFG_WDGEN_SHIFT) & QEI_WDGCFG_WDGEN_MASK)
#define QEI_WDGCFG_WDGEN_GET(x) (((uint32_t)(x) & QEI_WDGCFG_WDGEN_MASK) >> QEI_WDGCFG_WDGEN_SHIFT)

/*
 * WDGTO (RW)
 *
 * watch dog timeout value
 */
#define QEI_WDGCFG_WDGTO_MASK (0x7FFFFFFFUL)
#define QEI_WDGCFG_WDGTO_SHIFT (0U)
#define QEI_WDGCFG_WDGTO_SET(x) (((uint32_t)(x) << QEI_WDGCFG_WDGTO_SHIFT) & QEI_WDGCFG_WDGTO_MASK)
#define QEI_WDGCFG_WDGTO_GET(x) (((uint32_t)(x) & QEI_WDGCFG_WDGTO_MASK) >> QEI_WDGCFG_WDGTO_SHIFT)

/* Bitfield definition for register: PHIDX */
/*
 * PHIDX (RW)
 *
 * phcnt reset value, phcnt will reset to phidx when phcaliz set to 1
 */
#define QEI_PHIDX_PHIDX_MASK (0x1FFFFFUL)
#define QEI_PHIDX_PHIDX_SHIFT (0U)
#define QEI_PHIDX_PHIDX_SET(x) (((uint32_t)(x) << QEI_PHIDX_PHIDX_SHIFT) & QEI_PHIDX_PHIDX_MASK)
#define QEI_PHIDX_PHIDX_GET(x) (((uint32_t)(x) & QEI_PHIDX_PHIDX_MASK) >> QEI_PHIDX_PHIDX_SHIFT)

/* Bitfield definition for register: TRGOEN */
/*
 * WDGFEN (RW)
 *
 * 1- enable trigger output when wdg flag set
 */
#define QEI_TRGOEN_WDGFEN_MASK (0x80000000UL)
#define QEI_TRGOEN_WDGFEN_SHIFT (31U)
#define QEI_TRGOEN_WDGFEN_SET(x) (((uint32_t)(x) << QEI_TRGOEN_WDGFEN_SHIFT) & QEI_TRGOEN_WDGFEN_MASK)
#define QEI_TRGOEN_WDGFEN_GET(x) (((uint32_t)(x) & QEI_TRGOEN_WDGFEN_MASK) >> QEI_TRGOEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- enable trigger output when homef flag set
 */
#define QEI_TRGOEN_HOMEFEN_MASK (0x40000000UL)
#define QEI_TRGOEN_HOMEFEN_SHIFT (30U)
#define QEI_TRGOEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEI_TRGOEN_HOMEFEN_SHIFT) & QEI_TRGOEN_HOMEFEN_MASK)
#define QEI_TRGOEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEI_TRGOEN_HOMEFEN_MASK) >> QEI_TRGOEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- enable trigger output when poscmpf flag set
 */
#define QEI_TRGOEN_POSCMPFEN_MASK (0x20000000UL)
#define QEI_TRGOEN_POSCMPFEN_SHIFT (29U)
#define QEI_TRGOEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEI_TRGOEN_POSCMPFEN_SHIFT) & QEI_TRGOEN_POSCMPFEN_MASK)
#define QEI_TRGOEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEI_TRGOEN_POSCMPFEN_MASK) >> QEI_TRGOEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- enable trigger output when zphf flag set
 */
#define QEI_TRGOEN_ZPHFEN_MASK (0x10000000UL)
#define QEI_TRGOEN_ZPHFEN_SHIFT (28U)
#define QEI_TRGOEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEI_TRGOEN_ZPHFEN_SHIFT) & QEI_TRGOEN_ZPHFEN_MASK)
#define QEI_TRGOEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEI_TRGOEN_ZPHFEN_MASK) >> QEI_TRGOEN_ZPHFEN_SHIFT)

/* Bitfield definition for register: READEN */
/*
 * WDGFEN (RW)
 *
 * 1- load counters to their read registers when wdg flag set
 */
#define QEI_READEN_WDGFEN_MASK (0x80000000UL)
#define QEI_READEN_WDGFEN_SHIFT (31U)
#define QEI_READEN_WDGFEN_SET(x) (((uint32_t)(x) << QEI_READEN_WDGFEN_SHIFT) & QEI_READEN_WDGFEN_MASK)
#define QEI_READEN_WDGFEN_GET(x) (((uint32_t)(x) & QEI_READEN_WDGFEN_MASK) >> QEI_READEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- load counters to their read registers when homef flag set
 */
#define QEI_READEN_HOMEFEN_MASK (0x40000000UL)
#define QEI_READEN_HOMEFEN_SHIFT (30U)
#define QEI_READEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEI_READEN_HOMEFEN_SHIFT) & QEI_READEN_HOMEFEN_MASK)
#define QEI_READEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEI_READEN_HOMEFEN_MASK) >> QEI_READEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- load counters to their read registers when poscmpf flag set
 */
#define QEI_READEN_POSCMPFEN_MASK (0x20000000UL)
#define QEI_READEN_POSCMPFEN_SHIFT (29U)
#define QEI_READEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEI_READEN_POSCMPFEN_SHIFT) & QEI_READEN_POSCMPFEN_MASK)
#define QEI_READEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEI_READEN_POSCMPFEN_MASK) >> QEI_READEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- load counters to their read registers when zphf flag set
 */
#define QEI_READEN_ZPHFEN_MASK (0x10000000UL)
#define QEI_READEN_ZPHFEN_SHIFT (28U)
#define QEI_READEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEI_READEN_ZPHFEN_SHIFT) & QEI_READEN_ZPHFEN_MASK)
#define QEI_READEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEI_READEN_ZPHFEN_MASK) >> QEI_READEN_ZPHFEN_SHIFT)

/* Bitfield definition for register: ZCMP */
/*
 * ZCMP (RW)
 *
 * zcnt postion compare value
 */
#define QEI_ZCMP_ZCMP_MASK (0xFFFFFFFFUL)
#define QEI_ZCMP_ZCMP_SHIFT (0U)
#define QEI_ZCMP_ZCMP_SET(x) (((uint32_t)(x) << QEI_ZCMP_ZCMP_SHIFT) & QEI_ZCMP_ZCMP_MASK)
#define QEI_ZCMP_ZCMP_GET(x) (((uint32_t)(x) & QEI_ZCMP_ZCMP_MASK) >> QEI_ZCMP_ZCMP_SHIFT)

/* Bitfield definition for register: PHCMP */
/*
 * ZCMPDIS (RW)
 *
 * 1- postion compare not include zcnt
 */
#define QEI_PHCMP_ZCMPDIS_MASK (0x80000000UL)
#define QEI_PHCMP_ZCMPDIS_SHIFT (31U)
#define QEI_PHCMP_ZCMPDIS_SET(x) (((uint32_t)(x) << QEI_PHCMP_ZCMPDIS_SHIFT) & QEI_PHCMP_ZCMPDIS_MASK)
#define QEI_PHCMP_ZCMPDIS_GET(x) (((uint32_t)(x) & QEI_PHCMP_ZCMPDIS_MASK) >> QEI_PHCMP_ZCMPDIS_SHIFT)

/*
 * DIRCMPDIS (RW)
 *
 * 1- postion compare not include rotation direction
 */
#define QEI_PHCMP_DIRCMPDIS_MASK (0x40000000UL)
#define QEI_PHCMP_DIRCMPDIS_SHIFT (30U)
#define QEI_PHCMP_DIRCMPDIS_SET(x) (((uint32_t)(x) << QEI_PHCMP_DIRCMPDIS_SHIFT) & QEI_PHCMP_DIRCMPDIS_MASK)
#define QEI_PHCMP_DIRCMPDIS_GET(x) (((uint32_t)(x) & QEI_PHCMP_DIRCMPDIS_MASK) >> QEI_PHCMP_DIRCMPDIS_SHIFT)

/*
 * DIRCMP (RW)
 *
 * 0- position compare need positive rotation
 * 1- position compare need negative rotation
 */
#define QEI_PHCMP_DIRCMP_MASK (0x20000000UL)
#define QEI_PHCMP_DIRCMP_SHIFT (29U)
#define QEI_PHCMP_DIRCMP_SET(x) (((uint32_t)(x) << QEI_PHCMP_DIRCMP_SHIFT) & QEI_PHCMP_DIRCMP_MASK)
#define QEI_PHCMP_DIRCMP_GET(x) (((uint32_t)(x) & QEI_PHCMP_DIRCMP_MASK) >> QEI_PHCMP_DIRCMP_SHIFT)

/*
 * PHCMP (RW)
 *
 * phcnt position compare value
 */
#define QEI_PHCMP_PHCMP_MASK (0x1FFFFFUL)
#define QEI_PHCMP_PHCMP_SHIFT (0U)
#define QEI_PHCMP_PHCMP_SET(x) (((uint32_t)(x) << QEI_PHCMP_PHCMP_SHIFT) & QEI_PHCMP_PHCMP_MASK)
#define QEI_PHCMP_PHCMP_GET(x) (((uint32_t)(x) & QEI_PHCMP_PHCMP_MASK) >> QEI_PHCMP_PHCMP_SHIFT)

/* Bitfield definition for register: SPDCMP */
/*
 * SPDCMP (RW)
 *
 * spdcnt position compare value
 */
#define QEI_SPDCMP_SPDCMP_MASK (0xFFFFFFFFUL)
#define QEI_SPDCMP_SPDCMP_SHIFT (0U)
#define QEI_SPDCMP_SPDCMP_SET(x) (((uint32_t)(x) << QEI_SPDCMP_SPDCMP_SHIFT) & QEI_SPDCMP_SPDCMP_MASK)
#define QEI_SPDCMP_SPDCMP_GET(x) (((uint32_t)(x) & QEI_SPDCMP_SPDCMP_MASK) >> QEI_SPDCMP_SPDCMP_SHIFT)

/* Bitfield definition for register: DMAEN */
/*
 * WDGFEN (RW)
 *
 * 1- generate dma request when wdg flag set
 */
#define QEI_DMAEN_WDGFEN_MASK (0x80000000UL)
#define QEI_DMAEN_WDGFEN_SHIFT (31U)
#define QEI_DMAEN_WDGFEN_SET(x) (((uint32_t)(x) << QEI_DMAEN_WDGFEN_SHIFT) & QEI_DMAEN_WDGFEN_MASK)
#define QEI_DMAEN_WDGFEN_GET(x) (((uint32_t)(x) & QEI_DMAEN_WDGFEN_MASK) >> QEI_DMAEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- generate dma request when homef flag set
 */
#define QEI_DMAEN_HOMEFEN_MASK (0x40000000UL)
#define QEI_DMAEN_HOMEFEN_SHIFT (30U)
#define QEI_DMAEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEI_DMAEN_HOMEFEN_SHIFT) & QEI_DMAEN_HOMEFEN_MASK)
#define QEI_DMAEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEI_DMAEN_HOMEFEN_MASK) >> QEI_DMAEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- generate dma request when poscmpf flag set
 */
#define QEI_DMAEN_POSCMPFEN_MASK (0x20000000UL)
#define QEI_DMAEN_POSCMPFEN_SHIFT (29U)
#define QEI_DMAEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEI_DMAEN_POSCMPFEN_SHIFT) & QEI_DMAEN_POSCMPFEN_MASK)
#define QEI_DMAEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEI_DMAEN_POSCMPFEN_MASK) >> QEI_DMAEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- generate dma request when zphf flag set
 */
#define QEI_DMAEN_ZPHFEN_MASK (0x10000000UL)
#define QEI_DMAEN_ZPHFEN_SHIFT (28U)
#define QEI_DMAEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEI_DMAEN_ZPHFEN_SHIFT) & QEI_DMAEN_ZPHFEN_MASK)
#define QEI_DMAEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEI_DMAEN_ZPHFEN_MASK) >> QEI_DMAEN_ZPHFEN_SHIFT)

/* Bitfield definition for register: SR */
/*
 * WDGF (RW)
 *
 * watchdog flag
 */
#define QEI_SR_WDGF_MASK (0x80000000UL)
#define QEI_SR_WDGF_SHIFT (31U)
#define QEI_SR_WDGF_SET(x) (((uint32_t)(x) << QEI_SR_WDGF_SHIFT) & QEI_SR_WDGF_MASK)
#define QEI_SR_WDGF_GET(x) (((uint32_t)(x) & QEI_SR_WDGF_MASK) >> QEI_SR_WDGF_SHIFT)

/*
 * HOMEF (RW)
 *
 * home flag
 */
#define QEI_SR_HOMEF_MASK (0x40000000UL)
#define QEI_SR_HOMEF_SHIFT (30U)
#define QEI_SR_HOMEF_SET(x) (((uint32_t)(x) << QEI_SR_HOMEF_SHIFT) & QEI_SR_HOMEF_MASK)
#define QEI_SR_HOMEF_GET(x) (((uint32_t)(x) & QEI_SR_HOMEF_MASK) >> QEI_SR_HOMEF_SHIFT)

/*
 * POSCMPF (RW)
 *
 * postion compare match flag
 */
#define QEI_SR_POSCMPF_MASK (0x20000000UL)
#define QEI_SR_POSCMPF_SHIFT (29U)
#define QEI_SR_POSCMPF_SET(x) (((uint32_t)(x) << QEI_SR_POSCMPF_SHIFT) & QEI_SR_POSCMPF_MASK)
#define QEI_SR_POSCMPF_GET(x) (((uint32_t)(x) & QEI_SR_POSCMPF_MASK) >> QEI_SR_POSCMPF_SHIFT)

/*
 * ZPHF (RW)
 *
 * z input flag
 */
#define QEI_SR_ZPHF_MASK (0x10000000UL)
#define QEI_SR_ZPHF_SHIFT (28U)
#define QEI_SR_ZPHF_SET(x) (((uint32_t)(x) << QEI_SR_ZPHF_SHIFT) & QEI_SR_ZPHF_MASK)
#define QEI_SR_ZPHF_GET(x) (((uint32_t)(x) & QEI_SR_ZPHF_MASK) >> QEI_SR_ZPHF_SHIFT)

/* Bitfield definition for register: IRQEN */
/*
 * WDGIE (RW)
 *
 * 1- generate interrupt when wdg flag set
 */
#define QEI_IRQEN_WDGIE_MASK (0x80000000UL)
#define QEI_IRQEN_WDGIE_SHIFT (31U)
#define QEI_IRQEN_WDGIE_SET(x) (((uint32_t)(x) << QEI_IRQEN_WDGIE_SHIFT) & QEI_IRQEN_WDGIE_MASK)
#define QEI_IRQEN_WDGIE_GET(x) (((uint32_t)(x) & QEI_IRQEN_WDGIE_MASK) >> QEI_IRQEN_WDGIE_SHIFT)

/*
 * HOMEIE (RW)
 *
 * 1- generate interrupt when homef flag set
 */
#define QEI_IRQEN_HOMEIE_MASK (0x40000000UL)
#define QEI_IRQEN_HOMEIE_SHIFT (30U)
#define QEI_IRQEN_HOMEIE_SET(x) (((uint32_t)(x) << QEI_IRQEN_HOMEIE_SHIFT) & QEI_IRQEN_HOMEIE_MASK)
#define QEI_IRQEN_HOMEIE_GET(x) (((uint32_t)(x) & QEI_IRQEN_HOMEIE_MASK) >> QEI_IRQEN_HOMEIE_SHIFT)

/*
 * POSCMPIE (RW)
 *
 * 1- generate interrupt when poscmpf flag set
 */
#define QEI_IRQEN_POSCMPIE_MASK (0x20000000UL)
#define QEI_IRQEN_POSCMPIE_SHIFT (29U)
#define QEI_IRQEN_POSCMPIE_SET(x) (((uint32_t)(x) << QEI_IRQEN_POSCMPIE_SHIFT) & QEI_IRQEN_POSCMPIE_MASK)
#define QEI_IRQEN_POSCMPIE_GET(x) (((uint32_t)(x) & QEI_IRQEN_POSCMPIE_MASK) >> QEI_IRQEN_POSCMPIE_SHIFT)

/*
 * ZPHIE (RW)
 *
 * 1- generate interrupt when zphf flag set
 */
#define QEI_IRQEN_ZPHIE_MASK (0x10000000UL)
#define QEI_IRQEN_ZPHIE_SHIFT (28U)
#define QEI_IRQEN_ZPHIE_SET(x) (((uint32_t)(x) << QEI_IRQEN_ZPHIE_SHIFT) & QEI_IRQEN_ZPHIE_MASK)
#define QEI_IRQEN_ZPHIE_GET(x) (((uint32_t)(x) & QEI_IRQEN_ZPHIE_MASK) >> QEI_IRQEN_ZPHIE_SHIFT)

/* Bitfield definition for register of struct array COUNT: Z */
/*
 * ZCNT (RW)
 *
 * zcnt value
 */
#define QEI_COUNT_Z_ZCNT_MASK (0xFFFFFFFFUL)
#define QEI_COUNT_Z_ZCNT_SHIFT (0U)
#define QEI_COUNT_Z_ZCNT_SET(x) (((uint32_t)(x) << QEI_COUNT_Z_ZCNT_SHIFT) & QEI_COUNT_Z_ZCNT_MASK)
#define QEI_COUNT_Z_ZCNT_GET(x) (((uint32_t)(x) & QEI_COUNT_Z_ZCNT_MASK) >> QEI_COUNT_Z_ZCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: PH */
/*
 * DIR (RO)
 *
 * 1- reverse rotation
 * 0- forward rotation
 */
#define QEI_COUNT_PH_DIR_MASK (0x40000000UL)
#define QEI_COUNT_PH_DIR_SHIFT (30U)
#define QEI_COUNT_PH_DIR_GET(x) (((uint32_t)(x) & QEI_COUNT_PH_DIR_MASK) >> QEI_COUNT_PH_DIR_SHIFT)

/*
 * ASTAT (RO)
 *
 * 1- a input is high
 * 0- a input is low
 */
#define QEI_COUNT_PH_ASTAT_MASK (0x4000000UL)
#define QEI_COUNT_PH_ASTAT_SHIFT (26U)
#define QEI_COUNT_PH_ASTAT_GET(x) (((uint32_t)(x) & QEI_COUNT_PH_ASTAT_MASK) >> QEI_COUNT_PH_ASTAT_SHIFT)

/*
 * BSTAT (RO)
 *
 * 1- b input is high
 * 0- b input is low
 */
#define QEI_COUNT_PH_BSTAT_MASK (0x2000000UL)
#define QEI_COUNT_PH_BSTAT_SHIFT (25U)
#define QEI_COUNT_PH_BSTAT_GET(x) (((uint32_t)(x) & QEI_COUNT_PH_BSTAT_MASK) >> QEI_COUNT_PH_BSTAT_SHIFT)

/*
 * PHCNT (RO)
 *
 * phcnt value
 */
#define QEI_COUNT_PH_PHCNT_MASK (0x1FFFFFUL)
#define QEI_COUNT_PH_PHCNT_SHIFT (0U)
#define QEI_COUNT_PH_PHCNT_GET(x) (((uint32_t)(x) & QEI_COUNT_PH_PHCNT_MASK) >> QEI_COUNT_PH_PHCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: SPD */
/*
 * DIR (RO)
 *
 * 1- reverse rotation
 * 0- forward rotation
 */
#define QEI_COUNT_SPD_DIR_MASK (0x80000000UL)
#define QEI_COUNT_SPD_DIR_SHIFT (31U)
#define QEI_COUNT_SPD_DIR_GET(x) (((uint32_t)(x) & QEI_COUNT_SPD_DIR_MASK) >> QEI_COUNT_SPD_DIR_SHIFT)

/*
 * ASTAT (RO)
 *
 * 1- a input is high
 * 0- a input is low
 */
#define QEI_COUNT_SPD_ASTAT_MASK (0x40000000UL)
#define QEI_COUNT_SPD_ASTAT_SHIFT (30U)
#define QEI_COUNT_SPD_ASTAT_GET(x) (((uint32_t)(x) & QEI_COUNT_SPD_ASTAT_MASK) >> QEI_COUNT_SPD_ASTAT_SHIFT)

/*
 * BSTAT (RW)
 *
 * 1- b input is high
 * 0- b input is low
 */
#define QEI_COUNT_SPD_BSTAT_MASK (0x20000000UL)
#define QEI_COUNT_SPD_BSTAT_SHIFT (29U)
#define QEI_COUNT_SPD_BSTAT_SET(x) (((uint32_t)(x) << QEI_COUNT_SPD_BSTAT_SHIFT) & QEI_COUNT_SPD_BSTAT_MASK)
#define QEI_COUNT_SPD_BSTAT_GET(x) (((uint32_t)(x) & QEI_COUNT_SPD_BSTAT_MASK) >> QEI_COUNT_SPD_BSTAT_SHIFT)

/*
 * SPDCNT (RO)
 *
 * spdcnt value
 */
#define QEI_COUNT_SPD_SPDCNT_MASK (0xFFFFFFFUL)
#define QEI_COUNT_SPD_SPDCNT_SHIFT (0U)
#define QEI_COUNT_SPD_SPDCNT_GET(x) (((uint32_t)(x) & QEI_COUNT_SPD_SPDCNT_MASK) >> QEI_COUNT_SPD_SPDCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: TMR */
/*
 * TMRCNT (RO)
 *
 * 32 bit free run timer
 */
#define QEI_COUNT_TMR_TMRCNT_MASK (0xFFFFFFFFUL)
#define QEI_COUNT_TMR_TMRCNT_SHIFT (0U)
#define QEI_COUNT_TMR_TMRCNT_GET(x) (((uint32_t)(x) & QEI_COUNT_TMR_TMRCNT_MASK) >> QEI_COUNT_TMR_TMRCNT_SHIFT)

/* Bitfield definition for register array: SPDHIS */
/*
 * SPDHIS0 (RO)
 *
 * copy of spdcnt, load from spdcnt after any transition from a = low, b = low
 */
#define QEI_SPDHIS_SPDHIS0_MASK (0xFFFFFFFFUL)
#define QEI_SPDHIS_SPDHIS0_SHIFT (0U)
#define QEI_SPDHIS_SPDHIS0_GET(x) (((uint32_t)(x) & QEI_SPDHIS_SPDHIS0_MASK) >> QEI_SPDHIS_SPDHIS0_SHIFT)



/* COUNT register group index macro definition */
#define QEI_COUNT_CURRENT (0UL)
#define QEI_COUNT_READ (1UL)
#define QEI_COUNT_SNAP0 (2UL)
#define QEI_COUNT_SNAP1 (3UL)

/* SPDHIS register group index macro definition */
#define QEI_SPDHIS_SPDHIS0 (0UL)
#define QEI_SPDHIS_SPDHIS1 (1UL)
#define QEI_SPDHIS_SPDHIS2 (2UL)
#define QEI_SPDHIS_SPDHIS3 (3UL)


#endif /* HPM_QEI_H */

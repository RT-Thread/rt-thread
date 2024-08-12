/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_QEIV2_H
#define HPM_QEIV2_H

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
    __R  uint8_t  RESERVED0[16];               /* 0x70 - 0x7F: Reserved */
    __RW uint32_t ZCMP2;                       /* 0x80: Z comparator */
    __RW uint32_t PHCMP2;                      /* 0x84: Phase comparator */
    __RW uint32_t SPDCMP2;                     /* 0x88: Speed comparator */
    __RW uint32_t MATCH_CFG;                   /* 0x8C:  */
    __RW uint32_t FILT_CFG[6];                 /* 0x90 - 0xA4: A signal filter config */
    __R  uint8_t  RESERVED1[88];               /* 0xA8 - 0xFF: Reserved */
    __RW uint32_t QEI_CFG;                     /* 0x100: qei config register */
    __R  uint8_t  RESERVED2[12];               /* 0x104 - 0x10F: Reserved */
    __RW uint32_t PULSE0_NUM;                  /* 0x110: pulse0_num */
    __RW uint32_t PULSE1_NUM;                  /* 0x114: pulse1_num */
    __R  uint32_t CYCLE0_CNT;                  /* 0x118: cycle0_cnt */
    __R  uint32_t CYCLE0PULSE_CNT;             /* 0x11C: cycle0pulse_cnt */
    __R  uint32_t CYCLE1_CNT;                  /* 0x120: cycle1_cnt */
    __R  uint32_t CYCLE1PULSE_CNT;             /* 0x124: cycle1pulse_cnt */
    __R  uint32_t CYCLE0_SNAP0;                /* 0x128: cycle0_snap0 */
    __R  uint32_t CYCLE0_SNAP1;                /* 0x12C: cycle0_snap1 */
    __R  uint32_t CYCLE1_SNAP0;                /* 0x130: cycle1_snap0 */
    __R  uint32_t CYCLE1_SNAP1;                /* 0x134: cycle1_snap1 */
    __R  uint8_t  RESERVED3[8];                /* 0x138 - 0x13F: Reserved */
    __RW uint32_t CYCLE0_NUM;                  /* 0x140: cycle0_num */
    __RW uint32_t CYCLE1_NUM;                  /* 0x144: cycle1_num */
    __R  uint32_t PULSE0_CNT;                  /* 0x148: pulse0_cnt */
    __R  uint32_t PULSE0CYCLE_CNT;             /* 0x14C: pulse0cycle_cnt */
    __R  uint32_t PULSE1_CNT;                  /* 0x150: pulse1_cnt */
    __R  uint32_t PULSE1CYCLE_CNT;             /* 0x154: pulse1cycle_cnt */
    __R  uint32_t PULSE0_SNAP0;                /* 0x158: pulse0_snap0 */
    __R  uint32_t PULSE0CYCLE_SNAP0;           /* 0x15C: pulse0cycle_snap0 */
    __R  uint32_t PULSE0_SNAP1;                /* 0x160: pulse0_snap1 */
    __R  uint32_t PULSE0CYCLE_SNAP1;           /* 0x164: pulse0cycle_snap1 */
    __R  uint32_t PULSE1_SNAP0;                /* 0x168: pulse1_snap0 */
    __R  uint32_t PULSE1CYCLE_SNAP0;           /* 0x16C: pulse1cycle_snap0 */
    __R  uint32_t PULSE1_SNAP1;                /* 0x170: pulse1_snap1 */
    __R  uint32_t PULSE1CYCLE_SNAP1;           /* 0x174: pulse1cycle_snap1 */
    __R  uint8_t  RESERVED4[136];              /* 0x178 - 0x1FF: Reserved */
    __RW uint32_t ADCX_CFG0;                   /* 0x200: adcx_cfg0 */
    __RW uint32_t ADCX_CFG1;                   /* 0x204: adcx_cfg1 */
    __RW uint32_t ADCX_CFG2;                   /* 0x208: adcx_cfg2 */
    __R  uint8_t  RESERVED5[4];                /* 0x20C - 0x20F: Reserved */
    __RW uint32_t ADCY_CFG0;                   /* 0x210: adcy_cfg0 */
    __RW uint32_t ADCY_CFG1;                   /* 0x214: adcy_cfg1 */
    __RW uint32_t ADCY_CFG2;                   /* 0x218: adcy_cfg2 */
    __R  uint8_t  RESERVED6[4];                /* 0x21C - 0x21F: Reserved */
    __RW uint32_t CAL_CFG;                     /* 0x220: cal_cfg */
    __R  uint8_t  RESERVED7[12];               /* 0x224 - 0x22F: Reserved */
    __RW uint32_t PHASE_PARAM;                 /* 0x230: phase_param */
    __R  uint8_t  RESERVED8[4];                /* 0x234 - 0x237: Reserved */
    __RW uint32_t POS_THRESHOLD;               /* 0x238: pos_threshold */
    __R  uint8_t  RESERVED9[4];                /* 0x23C - 0x23F: Reserved */
    __RW uint32_t UVW_POS[6];                  /* 0x240 - 0x254: uvw_pos0 */
    __RW uint32_t UVW_POS_CFG[6];              /* 0x258 - 0x26C: uvw_pos0_cfg */
    __R  uint8_t  RESERVED10[16];              /* 0x270 - 0x27F: Reserved */
    __RW uint32_t PHASE_CNT;                   /* 0x280: phase_cnt */
    __W  uint32_t PHASE_UPDATE;                /* 0x284: phase_update */
    __RW uint32_t POSITION;                    /* 0x288: position */
    __W  uint32_t POSITION_UPDATE;             /* 0x28C: position_update */
    __R  uint32_t ANGLE;                       /* 0x290:  */
    __RW uint32_t POS_TIMEOUT;                 /* 0x294: pos_timeout */
} QEIV2_Type;


/* Bitfield definition for register: CR */
/*
 * READ (WO)
 *
 * 1- load phcnt, zcnt, spdcnt and tmrcnt into their read registers. Hardware auto-clear; read as 0
 */
#define QEIV2_CR_READ_MASK (0x80000000UL)
#define QEIV2_CR_READ_SHIFT (31U)
#define QEIV2_CR_READ_SET(x) (((uint32_t)(x) << QEIV2_CR_READ_SHIFT) & QEIV2_CR_READ_MASK)
#define QEIV2_CR_READ_GET(x) (((uint32_t)(x) & QEIV2_CR_READ_MASK) >> QEIV2_CR_READ_SHIFT)

/*
 * ZCNTCFG (RW)
 *
 * 1- zcnt will increment when phcnt upcount to phmax, decrement when phcnt downcount to 0
 * 0- zcnt will increment or decrement when Z input assert
 */
#define QEIV2_CR_ZCNTCFG_MASK (0x400000UL)
#define QEIV2_CR_ZCNTCFG_SHIFT (22U)
#define QEIV2_CR_ZCNTCFG_SET(x) (((uint32_t)(x) << QEIV2_CR_ZCNTCFG_SHIFT) & QEIV2_CR_ZCNTCFG_MASK)
#define QEIV2_CR_ZCNTCFG_GET(x) (((uint32_t)(x) & QEIV2_CR_ZCNTCFG_MASK) >> QEIV2_CR_ZCNTCFG_SHIFT)

/*
 * PHCALIZ (RW)
 *
 * 1- phcnt will set to phidx when Z input assert(for abz digital signsl)
 */
#define QEIV2_CR_PHCALIZ_MASK (0x200000UL)
#define QEIV2_CR_PHCALIZ_SHIFT (21U)
#define QEIV2_CR_PHCALIZ_SET(x) (((uint32_t)(x) << QEIV2_CR_PHCALIZ_SHIFT) & QEIV2_CR_PHCALIZ_MASK)
#define QEIV2_CR_PHCALIZ_GET(x) (((uint32_t)(x) & QEIV2_CR_PHCALIZ_MASK) >> QEIV2_CR_PHCALIZ_SHIFT)

/*
 * Z_ONLY_EN (RW)
 *
 * 1- phcnt will set to phidx when Z input assert(for xy analog signal and digital z, also need set phcaliz)
 */
#define QEIV2_CR_Z_ONLY_EN_MASK (0x100000UL)
#define QEIV2_CR_Z_ONLY_EN_SHIFT (20U)
#define QEIV2_CR_Z_ONLY_EN_SET(x) (((uint32_t)(x) << QEIV2_CR_Z_ONLY_EN_SHIFT) & QEIV2_CR_Z_ONLY_EN_MASK)
#define QEIV2_CR_Z_ONLY_EN_GET(x) (((uint32_t)(x) & QEIV2_CR_Z_ONLY_EN_MASK) >> QEIV2_CR_Z_ONLY_EN_SHIFT)

/*
 * H2FDIR0 (RW)
 *
 */
#define QEIV2_CR_H2FDIR0_MASK (0x80000UL)
#define QEIV2_CR_H2FDIR0_SHIFT (19U)
#define QEIV2_CR_H2FDIR0_SET(x) (((uint32_t)(x) << QEIV2_CR_H2FDIR0_SHIFT) & QEIV2_CR_H2FDIR0_MASK)
#define QEIV2_CR_H2FDIR0_GET(x) (((uint32_t)(x) & QEIV2_CR_H2FDIR0_MASK) >> QEIV2_CR_H2FDIR0_SHIFT)

/*
 * H2FDIR1 (RW)
 *
 */
#define QEIV2_CR_H2FDIR1_MASK (0x40000UL)
#define QEIV2_CR_H2FDIR1_SHIFT (18U)
#define QEIV2_CR_H2FDIR1_SET(x) (((uint32_t)(x) << QEIV2_CR_H2FDIR1_SHIFT) & QEIV2_CR_H2FDIR1_MASK)
#define QEIV2_CR_H2FDIR1_GET(x) (((uint32_t)(x) & QEIV2_CR_H2FDIR1_MASK) >> QEIV2_CR_H2FDIR1_SHIFT)

/*
 * H2RDIR0 (RW)
 *
 */
#define QEIV2_CR_H2RDIR0_MASK (0x20000UL)
#define QEIV2_CR_H2RDIR0_SHIFT (17U)
#define QEIV2_CR_H2RDIR0_SET(x) (((uint32_t)(x) << QEIV2_CR_H2RDIR0_SHIFT) & QEIV2_CR_H2RDIR0_MASK)
#define QEIV2_CR_H2RDIR0_GET(x) (((uint32_t)(x) & QEIV2_CR_H2RDIR0_MASK) >> QEIV2_CR_H2RDIR0_SHIFT)

/*
 * H2RDIR1 (RW)
 *
 */
#define QEIV2_CR_H2RDIR1_MASK (0x10000UL)
#define QEIV2_CR_H2RDIR1_SHIFT (16U)
#define QEIV2_CR_H2RDIR1_SET(x) (((uint32_t)(x) << QEIV2_CR_H2RDIR1_SHIFT) & QEIV2_CR_H2RDIR1_MASK)
#define QEIV2_CR_H2RDIR1_GET(x) (((uint32_t)(x) & QEIV2_CR_H2RDIR1_MASK) >> QEIV2_CR_H2RDIR1_SHIFT)

/*
 * PAUSEPOS (RW)
 *
 * 1- pause position output valid when PAUSE assert
 */
#define QEIV2_CR_PAUSEPOS_MASK (0x8000U)
#define QEIV2_CR_PAUSEPOS_SHIFT (15U)
#define QEIV2_CR_PAUSEPOS_SET(x) (((uint32_t)(x) << QEIV2_CR_PAUSEPOS_SHIFT) & QEIV2_CR_PAUSEPOS_MASK)
#define QEIV2_CR_PAUSEPOS_GET(x) (((uint32_t)(x) & QEIV2_CR_PAUSEPOS_MASK) >> QEIV2_CR_PAUSEPOS_SHIFT)

/*
 * PAUSESPD (RW)
 *
 * 1- pause spdcnt when PAUSE assert
 */
#define QEIV2_CR_PAUSESPD_MASK (0x4000U)
#define QEIV2_CR_PAUSESPD_SHIFT (14U)
#define QEIV2_CR_PAUSESPD_SET(x) (((uint32_t)(x) << QEIV2_CR_PAUSESPD_SHIFT) & QEIV2_CR_PAUSESPD_MASK)
#define QEIV2_CR_PAUSESPD_GET(x) (((uint32_t)(x) & QEIV2_CR_PAUSESPD_MASK) >> QEIV2_CR_PAUSESPD_SHIFT)

/*
 * PAUSEPH (RW)
 *
 * 1- pause phcnt when PAUSE assert
 */
#define QEIV2_CR_PAUSEPH_MASK (0x2000U)
#define QEIV2_CR_PAUSEPH_SHIFT (13U)
#define QEIV2_CR_PAUSEPH_SET(x) (((uint32_t)(x) << QEIV2_CR_PAUSEPH_SHIFT) & QEIV2_CR_PAUSEPH_MASK)
#define QEIV2_CR_PAUSEPH_GET(x) (((uint32_t)(x) & QEIV2_CR_PAUSEPH_MASK) >> QEIV2_CR_PAUSEPH_SHIFT)

/*
 * PAUSEZ (RW)
 *
 * 1- pause zcnt when PAUSE assert
 */
#define QEIV2_CR_PAUSEZ_MASK (0x1000U)
#define QEIV2_CR_PAUSEZ_SHIFT (12U)
#define QEIV2_CR_PAUSEZ_SET(x) (((uint32_t)(x) << QEIV2_CR_PAUSEZ_SHIFT) & QEIV2_CR_PAUSEZ_MASK)
#define QEIV2_CR_PAUSEZ_GET(x) (((uint32_t)(x) & QEIV2_CR_PAUSEZ_MASK) >> QEIV2_CR_PAUSEZ_SHIFT)

/*
 * HFDIR0 (RW)
 *
 * 1- HOMEF will set at H rising edge when dir == 1 (negative rotation direction)
 */
#define QEIV2_CR_HFDIR0_MASK (0x800U)
#define QEIV2_CR_HFDIR0_SHIFT (11U)
#define QEIV2_CR_HFDIR0_SET(x) (((uint32_t)(x) << QEIV2_CR_HFDIR0_SHIFT) & QEIV2_CR_HFDIR0_MASK)
#define QEIV2_CR_HFDIR0_GET(x) (((uint32_t)(x) & QEIV2_CR_HFDIR0_MASK) >> QEIV2_CR_HFDIR0_SHIFT)

/*
 * HFDIR1 (RW)
 *
 * 1- HOMEF will set at H rising edge when dir == 0 (positive rotation direction)
 */
#define QEIV2_CR_HFDIR1_MASK (0x400U)
#define QEIV2_CR_HFDIR1_SHIFT (10U)
#define QEIV2_CR_HFDIR1_SET(x) (((uint32_t)(x) << QEIV2_CR_HFDIR1_SHIFT) & QEIV2_CR_HFDIR1_MASK)
#define QEIV2_CR_HFDIR1_GET(x) (((uint32_t)(x) & QEIV2_CR_HFDIR1_MASK) >> QEIV2_CR_HFDIR1_SHIFT)

/*
 * HRDIR0 (RW)
 *
 * 1- HOMEF will set at H falling edge when dir == 1 (negative rotation direction)
 */
#define QEIV2_CR_HRDIR0_MASK (0x200U)
#define QEIV2_CR_HRDIR0_SHIFT (9U)
#define QEIV2_CR_HRDIR0_SET(x) (((uint32_t)(x) << QEIV2_CR_HRDIR0_SHIFT) & QEIV2_CR_HRDIR0_MASK)
#define QEIV2_CR_HRDIR0_GET(x) (((uint32_t)(x) & QEIV2_CR_HRDIR0_MASK) >> QEIV2_CR_HRDIR0_SHIFT)

/*
 * HRDIR1 (RW)
 *
 * 1- HOMEF will set at H falling edge when dir == 1 (positive rotation direction)
 */
#define QEIV2_CR_HRDIR1_MASK (0x100U)
#define QEIV2_CR_HRDIR1_SHIFT (8U)
#define QEIV2_CR_HRDIR1_SET(x) (((uint32_t)(x) << QEIV2_CR_HRDIR1_SHIFT) & QEIV2_CR_HRDIR1_MASK)
#define QEIV2_CR_HRDIR1_GET(x) (((uint32_t)(x) & QEIV2_CR_HRDIR1_MASK) >> QEIV2_CR_HRDIR1_SHIFT)

/*
 * FAULTPOS (RW)
 *
 */
#define QEIV2_CR_FAULTPOS_MASK (0x40U)
#define QEIV2_CR_FAULTPOS_SHIFT (6U)
#define QEIV2_CR_FAULTPOS_SET(x) (((uint32_t)(x) << QEIV2_CR_FAULTPOS_SHIFT) & QEIV2_CR_FAULTPOS_MASK)
#define QEIV2_CR_FAULTPOS_GET(x) (((uint32_t)(x) & QEIV2_CR_FAULTPOS_MASK) >> QEIV2_CR_FAULTPOS_SHIFT)

/*
 * SNAPEN (RW)
 *
 * 1- load phcnt, zcnt, spdcnt and tmrcnt into their snap registers when snapi input assert
 */
#define QEIV2_CR_SNAPEN_MASK (0x20U)
#define QEIV2_CR_SNAPEN_SHIFT (5U)
#define QEIV2_CR_SNAPEN_SET(x) (((uint32_t)(x) << QEIV2_CR_SNAPEN_SHIFT) & QEIV2_CR_SNAPEN_MASK)
#define QEIV2_CR_SNAPEN_GET(x) (((uint32_t)(x) & QEIV2_CR_SNAPEN_MASK) >> QEIV2_CR_SNAPEN_SHIFT)

/*
 * RSTCNT (RW)
 *
 * 1- reset zcnt, spdcnt and tmrcnt to 0. reset phcnt to phidx
 */
#define QEIV2_CR_RSTCNT_MASK (0x10U)
#define QEIV2_CR_RSTCNT_SHIFT (4U)
#define QEIV2_CR_RSTCNT_SET(x) (((uint32_t)(x) << QEIV2_CR_RSTCNT_SHIFT) & QEIV2_CR_RSTCNT_MASK)
#define QEIV2_CR_RSTCNT_GET(x) (((uint32_t)(x) & QEIV2_CR_RSTCNT_MASK) >> QEIV2_CR_RSTCNT_SHIFT)

/*
 * RD_SEL (RW)
 *
 * define the width/counter value(affect width_match, width_match2, width_cur, timer_cur, width_read, timer_read,
 * width_snap0,width_snap1, timer_snap0, timer_snap1)
 * 0 : same as hpm1000/500/500s;
 * 1: use width for position; use timer for angle
 */
#define QEIV2_CR_RD_SEL_MASK (0x8U)
#define QEIV2_CR_RD_SEL_SHIFT (3U)
#define QEIV2_CR_RD_SEL_SET(x) (((uint32_t)(x) << QEIV2_CR_RD_SEL_SHIFT) & QEIV2_CR_RD_SEL_MASK)
#define QEIV2_CR_RD_SEL_GET(x) (((uint32_t)(x) & QEIV2_CR_RD_SEL_MASK) >> QEIV2_CR_RD_SEL_SHIFT)

/*
 * ENCTYP (RW)
 *
 * 000-abz; 001-pd; 010-ud; 011-UVW(hal)
 * 100-single A; 101-single sin;  110: sin&cos
 */
#define QEIV2_CR_ENCTYP_MASK (0x7U)
#define QEIV2_CR_ENCTYP_SHIFT (0U)
#define QEIV2_CR_ENCTYP_SET(x) (((uint32_t)(x) << QEIV2_CR_ENCTYP_SHIFT) & QEIV2_CR_ENCTYP_MASK)
#define QEIV2_CR_ENCTYP_GET(x) (((uint32_t)(x) & QEIV2_CR_ENCTYP_MASK) >> QEIV2_CR_ENCTYP_SHIFT)

/* Bitfield definition for register: PHCFG */
/*
 * PHMAX (RW)
 *
 * maximum phcnt number, phcnt will rollover to 0 when it upcount to phmax
 */
#define QEIV2_PHCFG_PHMAX_MASK (0xFFFFFFFFUL)
#define QEIV2_PHCFG_PHMAX_SHIFT (0U)
#define QEIV2_PHCFG_PHMAX_SET(x) (((uint32_t)(x) << QEIV2_PHCFG_PHMAX_SHIFT) & QEIV2_PHCFG_PHMAX_MASK)
#define QEIV2_PHCFG_PHMAX_GET(x) (((uint32_t)(x) & QEIV2_PHCFG_PHMAX_MASK) >> QEIV2_PHCFG_PHMAX_SHIFT)

/* Bitfield definition for register: WDGCFG */
/*
 * WDGEN (RW)
 *
 * 1- enable wdog counter
 */
#define QEIV2_WDGCFG_WDGEN_MASK (0x80000000UL)
#define QEIV2_WDGCFG_WDGEN_SHIFT (31U)
#define QEIV2_WDGCFG_WDGEN_SET(x) (((uint32_t)(x) << QEIV2_WDGCFG_WDGEN_SHIFT) & QEIV2_WDGCFG_WDGEN_MASK)
#define QEIV2_WDGCFG_WDGEN_GET(x) (((uint32_t)(x) & QEIV2_WDGCFG_WDGEN_MASK) >> QEIV2_WDGCFG_WDGEN_SHIFT)

/*
 * WDOG_CFG (RW)
 *
 * define as stop if phase_cnt change is less than it
 * if 0, then each change of phase_cnt will clear wdog counter;
 * if 2, then phase_cnt change larger than 2 will clear wdog counter
 */
#define QEIV2_WDGCFG_WDOG_CFG_MASK (0x70000000UL)
#define QEIV2_WDGCFG_WDOG_CFG_SHIFT (28U)
#define QEIV2_WDGCFG_WDOG_CFG_SET(x) (((uint32_t)(x) << QEIV2_WDGCFG_WDOG_CFG_SHIFT) & QEIV2_WDGCFG_WDOG_CFG_MASK)
#define QEIV2_WDGCFG_WDOG_CFG_GET(x) (((uint32_t)(x) & QEIV2_WDGCFG_WDOG_CFG_MASK) >> QEIV2_WDGCFG_WDOG_CFG_SHIFT)

/*
 * WDGTO (RW)
 *
 * watch dog timeout value
 */
#define QEIV2_WDGCFG_WDGTO_MASK (0xFFFFFFFUL)
#define QEIV2_WDGCFG_WDGTO_SHIFT (0U)
#define QEIV2_WDGCFG_WDGTO_SET(x) (((uint32_t)(x) << QEIV2_WDGCFG_WDGTO_SHIFT) & QEIV2_WDGCFG_WDGTO_MASK)
#define QEIV2_WDGCFG_WDGTO_GET(x) (((uint32_t)(x) & QEIV2_WDGCFG_WDGTO_MASK) >> QEIV2_WDGCFG_WDGTO_SHIFT)

/* Bitfield definition for register: PHIDX */
/*
 * PHIDX (RW)
 *
 * phcnt reset value, phcnt will reset to phidx when phcaliz set to 1
 */
#define QEIV2_PHIDX_PHIDX_MASK (0xFFFFFFFFUL)
#define QEIV2_PHIDX_PHIDX_SHIFT (0U)
#define QEIV2_PHIDX_PHIDX_SET(x) (((uint32_t)(x) << QEIV2_PHIDX_PHIDX_SHIFT) & QEIV2_PHIDX_PHIDX_MASK)
#define QEIV2_PHIDX_PHIDX_GET(x) (((uint32_t)(x) & QEIV2_PHIDX_PHIDX_MASK) >> QEIV2_PHIDX_PHIDX_SHIFT)

/* Bitfield definition for register: TRGOEN */
/*
 * WDGFEN (RW)
 *
 * 1- enable trigger output when wdg flag set
 */
#define QEIV2_TRGOEN_WDGFEN_MASK (0x80000000UL)
#define QEIV2_TRGOEN_WDGFEN_SHIFT (31U)
#define QEIV2_TRGOEN_WDGFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_WDGFEN_SHIFT) & QEIV2_TRGOEN_WDGFEN_MASK)
#define QEIV2_TRGOEN_WDGFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_WDGFEN_MASK) >> QEIV2_TRGOEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- enable trigger output when homef flag set
 */
#define QEIV2_TRGOEN_HOMEFEN_MASK (0x40000000UL)
#define QEIV2_TRGOEN_HOMEFEN_SHIFT (30U)
#define QEIV2_TRGOEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_HOMEFEN_SHIFT) & QEIV2_TRGOEN_HOMEFEN_MASK)
#define QEIV2_TRGOEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_HOMEFEN_MASK) >> QEIV2_TRGOEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- enable trigger output when poscmpf flag set
 */
#define QEIV2_TRGOEN_POSCMPFEN_MASK (0x20000000UL)
#define QEIV2_TRGOEN_POSCMPFEN_SHIFT (29U)
#define QEIV2_TRGOEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_POSCMPFEN_SHIFT) & QEIV2_TRGOEN_POSCMPFEN_MASK)
#define QEIV2_TRGOEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_POSCMPFEN_MASK) >> QEIV2_TRGOEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- enable trigger output when zphf flag set
 */
#define QEIV2_TRGOEN_ZPHFEN_MASK (0x10000000UL)
#define QEIV2_TRGOEN_ZPHFEN_SHIFT (28U)
#define QEIV2_TRGOEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_ZPHFEN_SHIFT) & QEIV2_TRGOEN_ZPHFEN_MASK)
#define QEIV2_TRGOEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_ZPHFEN_MASK) >> QEIV2_TRGOEN_ZPHFEN_SHIFT)

/*
 * ZMISSFEN (RW)
 *
 */
#define QEIV2_TRGOEN_ZMISSFEN_MASK (0x8000000UL)
#define QEIV2_TRGOEN_ZMISSFEN_SHIFT (27U)
#define QEIV2_TRGOEN_ZMISSFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_ZMISSFEN_SHIFT) & QEIV2_TRGOEN_ZMISSFEN_MASK)
#define QEIV2_TRGOEN_ZMISSFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_ZMISSFEN_MASK) >> QEIV2_TRGOEN_ZMISSFEN_SHIFT)

/*
 * WIDTHTMFEN (RW)
 *
 */
#define QEIV2_TRGOEN_WIDTHTMFEN_MASK (0x4000000UL)
#define QEIV2_TRGOEN_WIDTHTMFEN_SHIFT (26U)
#define QEIV2_TRGOEN_WIDTHTMFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_WIDTHTMFEN_SHIFT) & QEIV2_TRGOEN_WIDTHTMFEN_MASK)
#define QEIV2_TRGOEN_WIDTHTMFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_WIDTHTMFEN_MASK) >> QEIV2_TRGOEN_WIDTHTMFEN_SHIFT)

/*
 * POS2CMPFEN (RW)
 *
 */
#define QEIV2_TRGOEN_POS2CMPFEN_MASK (0x2000000UL)
#define QEIV2_TRGOEN_POS2CMPFEN_SHIFT (25U)
#define QEIV2_TRGOEN_POS2CMPFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_POS2CMPFEN_SHIFT) & QEIV2_TRGOEN_POS2CMPFEN_MASK)
#define QEIV2_TRGOEN_POS2CMPFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_POS2CMPFEN_MASK) >> QEIV2_TRGOEN_POS2CMPFEN_SHIFT)

/*
 * DIRCHGFEN (RW)
 *
 */
#define QEIV2_TRGOEN_DIRCHGFEN_MASK (0x1000000UL)
#define QEIV2_TRGOEN_DIRCHGFEN_SHIFT (24U)
#define QEIV2_TRGOEN_DIRCHGFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_DIRCHGFEN_SHIFT) & QEIV2_TRGOEN_DIRCHGFEN_MASK)
#define QEIV2_TRGOEN_DIRCHGFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_DIRCHGFEN_MASK) >> QEIV2_TRGOEN_DIRCHGFEN_SHIFT)

/*
 * CYCLE0FEN (RW)
 *
 */
#define QEIV2_TRGOEN_CYCLE0FEN_MASK (0x800000UL)
#define QEIV2_TRGOEN_CYCLE0FEN_SHIFT (23U)
#define QEIV2_TRGOEN_CYCLE0FEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_CYCLE0FEN_SHIFT) & QEIV2_TRGOEN_CYCLE0FEN_MASK)
#define QEIV2_TRGOEN_CYCLE0FEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_CYCLE0FEN_MASK) >> QEIV2_TRGOEN_CYCLE0FEN_SHIFT)

/*
 * CYCLE1FEN (RW)
 *
 */
#define QEIV2_TRGOEN_CYCLE1FEN_MASK (0x400000UL)
#define QEIV2_TRGOEN_CYCLE1FEN_SHIFT (22U)
#define QEIV2_TRGOEN_CYCLE1FEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_CYCLE1FEN_SHIFT) & QEIV2_TRGOEN_CYCLE1FEN_MASK)
#define QEIV2_TRGOEN_CYCLE1FEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_CYCLE1FEN_MASK) >> QEIV2_TRGOEN_CYCLE1FEN_SHIFT)

/*
 * PULSE0FEN (RW)
 *
 */
#define QEIV2_TRGOEN_PULSE0FEN_MASK (0x200000UL)
#define QEIV2_TRGOEN_PULSE0FEN_SHIFT (21U)
#define QEIV2_TRGOEN_PULSE0FEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_PULSE0FEN_SHIFT) & QEIV2_TRGOEN_PULSE0FEN_MASK)
#define QEIV2_TRGOEN_PULSE0FEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_PULSE0FEN_MASK) >> QEIV2_TRGOEN_PULSE0FEN_SHIFT)

/*
 * PULSE1FEN (RW)
 *
 */
#define QEIV2_TRGOEN_PULSE1FEN_MASK (0x100000UL)
#define QEIV2_TRGOEN_PULSE1FEN_SHIFT (20U)
#define QEIV2_TRGOEN_PULSE1FEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_PULSE1FEN_SHIFT) & QEIV2_TRGOEN_PULSE1FEN_MASK)
#define QEIV2_TRGOEN_PULSE1FEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_PULSE1FEN_MASK) >> QEIV2_TRGOEN_PULSE1FEN_SHIFT)

/*
 * HOME2FEN (RW)
 *
 */
#define QEIV2_TRGOEN_HOME2FEN_MASK (0x80000UL)
#define QEIV2_TRGOEN_HOME2FEN_SHIFT (19U)
#define QEIV2_TRGOEN_HOME2FEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_HOME2FEN_SHIFT) & QEIV2_TRGOEN_HOME2FEN_MASK)
#define QEIV2_TRGOEN_HOME2FEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_HOME2FEN_MASK) >> QEIV2_TRGOEN_HOME2FEN_SHIFT)

/*
 * FAULTFEN (RW)
 *
 */
#define QEIV2_TRGOEN_FAULTFEN_MASK (0x40000UL)
#define QEIV2_TRGOEN_FAULTFEN_SHIFT (18U)
#define QEIV2_TRGOEN_FAULTFEN_SET(x) (((uint32_t)(x) << QEIV2_TRGOEN_FAULTFEN_SHIFT) & QEIV2_TRGOEN_FAULTFEN_MASK)
#define QEIV2_TRGOEN_FAULTFEN_GET(x) (((uint32_t)(x) & QEIV2_TRGOEN_FAULTFEN_MASK) >> QEIV2_TRGOEN_FAULTFEN_SHIFT)

/* Bitfield definition for register: READEN */
/*
 * WDGFEN (RW)
 *
 * 1- load counters to their read registers when wdg flag set
 */
#define QEIV2_READEN_WDGFEN_MASK (0x80000000UL)
#define QEIV2_READEN_WDGFEN_SHIFT (31U)
#define QEIV2_READEN_WDGFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_WDGFEN_SHIFT) & QEIV2_READEN_WDGFEN_MASK)
#define QEIV2_READEN_WDGFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_WDGFEN_MASK) >> QEIV2_READEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- load counters to their read registers when homef flag set
 */
#define QEIV2_READEN_HOMEFEN_MASK (0x40000000UL)
#define QEIV2_READEN_HOMEFEN_SHIFT (30U)
#define QEIV2_READEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_HOMEFEN_SHIFT) & QEIV2_READEN_HOMEFEN_MASK)
#define QEIV2_READEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_HOMEFEN_MASK) >> QEIV2_READEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- load counters to their read registers when poscmpf flag set
 */
#define QEIV2_READEN_POSCMPFEN_MASK (0x20000000UL)
#define QEIV2_READEN_POSCMPFEN_SHIFT (29U)
#define QEIV2_READEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_POSCMPFEN_SHIFT) & QEIV2_READEN_POSCMPFEN_MASK)
#define QEIV2_READEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_POSCMPFEN_MASK) >> QEIV2_READEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- load counters to their read registers when zphf flag set
 */
#define QEIV2_READEN_ZPHFEN_MASK (0x10000000UL)
#define QEIV2_READEN_ZPHFEN_SHIFT (28U)
#define QEIV2_READEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_ZPHFEN_SHIFT) & QEIV2_READEN_ZPHFEN_MASK)
#define QEIV2_READEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_ZPHFEN_MASK) >> QEIV2_READEN_ZPHFEN_SHIFT)

/*
 * ZMISSFEN (RW)
 *
 */
#define QEIV2_READEN_ZMISSFEN_MASK (0x8000000UL)
#define QEIV2_READEN_ZMISSFEN_SHIFT (27U)
#define QEIV2_READEN_ZMISSFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_ZMISSFEN_SHIFT) & QEIV2_READEN_ZMISSFEN_MASK)
#define QEIV2_READEN_ZMISSFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_ZMISSFEN_MASK) >> QEIV2_READEN_ZMISSFEN_SHIFT)

/*
 * WIDTHTMFEN (RW)
 *
 */
#define QEIV2_READEN_WIDTHTMFEN_MASK (0x4000000UL)
#define QEIV2_READEN_WIDTHTMFEN_SHIFT (26U)
#define QEIV2_READEN_WIDTHTMFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_WIDTHTMFEN_SHIFT) & QEIV2_READEN_WIDTHTMFEN_MASK)
#define QEIV2_READEN_WIDTHTMFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_WIDTHTMFEN_MASK) >> QEIV2_READEN_WIDTHTMFEN_SHIFT)

/*
 * POS2CMPFEN (RW)
 *
 */
#define QEIV2_READEN_POS2CMPFEN_MASK (0x2000000UL)
#define QEIV2_READEN_POS2CMPFEN_SHIFT (25U)
#define QEIV2_READEN_POS2CMPFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_POS2CMPFEN_SHIFT) & QEIV2_READEN_POS2CMPFEN_MASK)
#define QEIV2_READEN_POS2CMPFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_POS2CMPFEN_MASK) >> QEIV2_READEN_POS2CMPFEN_SHIFT)

/*
 * DIRCHGFEN (RW)
 *
 */
#define QEIV2_READEN_DIRCHGFEN_MASK (0x1000000UL)
#define QEIV2_READEN_DIRCHGFEN_SHIFT (24U)
#define QEIV2_READEN_DIRCHGFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_DIRCHGFEN_SHIFT) & QEIV2_READEN_DIRCHGFEN_MASK)
#define QEIV2_READEN_DIRCHGFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_DIRCHGFEN_MASK) >> QEIV2_READEN_DIRCHGFEN_SHIFT)

/*
 * CYCLE0FEN (RW)
 *
 */
#define QEIV2_READEN_CYCLE0FEN_MASK (0x800000UL)
#define QEIV2_READEN_CYCLE0FEN_SHIFT (23U)
#define QEIV2_READEN_CYCLE0FEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_CYCLE0FEN_SHIFT) & QEIV2_READEN_CYCLE0FEN_MASK)
#define QEIV2_READEN_CYCLE0FEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_CYCLE0FEN_MASK) >> QEIV2_READEN_CYCLE0FEN_SHIFT)

/*
 * CYCLE1FEN (RW)
 *
 */
#define QEIV2_READEN_CYCLE1FEN_MASK (0x400000UL)
#define QEIV2_READEN_CYCLE1FEN_SHIFT (22U)
#define QEIV2_READEN_CYCLE1FEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_CYCLE1FEN_SHIFT) & QEIV2_READEN_CYCLE1FEN_MASK)
#define QEIV2_READEN_CYCLE1FEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_CYCLE1FEN_MASK) >> QEIV2_READEN_CYCLE1FEN_SHIFT)

/*
 * PULSE0FEN (RW)
 *
 */
#define QEIV2_READEN_PULSE0FEN_MASK (0x200000UL)
#define QEIV2_READEN_PULSE0FEN_SHIFT (21U)
#define QEIV2_READEN_PULSE0FEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_PULSE0FEN_SHIFT) & QEIV2_READEN_PULSE0FEN_MASK)
#define QEIV2_READEN_PULSE0FEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_PULSE0FEN_MASK) >> QEIV2_READEN_PULSE0FEN_SHIFT)

/*
 * PULSE1FEN (RW)
 *
 */
#define QEIV2_READEN_PULSE1FEN_MASK (0x100000UL)
#define QEIV2_READEN_PULSE1FEN_SHIFT (20U)
#define QEIV2_READEN_PULSE1FEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_PULSE1FEN_SHIFT) & QEIV2_READEN_PULSE1FEN_MASK)
#define QEIV2_READEN_PULSE1FEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_PULSE1FEN_MASK) >> QEIV2_READEN_PULSE1FEN_SHIFT)

/*
 * HOME2FEN (RW)
 *
 */
#define QEIV2_READEN_HOME2FEN_MASK (0x80000UL)
#define QEIV2_READEN_HOME2FEN_SHIFT (19U)
#define QEIV2_READEN_HOME2FEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_HOME2FEN_SHIFT) & QEIV2_READEN_HOME2FEN_MASK)
#define QEIV2_READEN_HOME2FEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_HOME2FEN_MASK) >> QEIV2_READEN_HOME2FEN_SHIFT)

/*
 * FAULTFEN (RW)
 *
 */
#define QEIV2_READEN_FAULTFEN_MASK (0x40000UL)
#define QEIV2_READEN_FAULTFEN_SHIFT (18U)
#define QEIV2_READEN_FAULTFEN_SET(x) (((uint32_t)(x) << QEIV2_READEN_FAULTFEN_SHIFT) & QEIV2_READEN_FAULTFEN_MASK)
#define QEIV2_READEN_FAULTFEN_GET(x) (((uint32_t)(x) & QEIV2_READEN_FAULTFEN_MASK) >> QEIV2_READEN_FAULTFEN_SHIFT)

/* Bitfield definition for register: ZCMP */
/*
 * ZCMP (RW)
 *
 * zcnt postion compare value
 */
#define QEIV2_ZCMP_ZCMP_MASK (0xFFFFFFFFUL)
#define QEIV2_ZCMP_ZCMP_SHIFT (0U)
#define QEIV2_ZCMP_ZCMP_SET(x) (((uint32_t)(x) << QEIV2_ZCMP_ZCMP_SHIFT) & QEIV2_ZCMP_ZCMP_MASK)
#define QEIV2_ZCMP_ZCMP_GET(x) (((uint32_t)(x) & QEIV2_ZCMP_ZCMP_MASK) >> QEIV2_ZCMP_ZCMP_SHIFT)

/* Bitfield definition for register: PHCMP */
/*
 * PHCMP (RW)
 *
 * phcnt position compare value
 */
#define QEIV2_PHCMP_PHCMP_MASK (0xFFFFFFFFUL)
#define QEIV2_PHCMP_PHCMP_SHIFT (0U)
#define QEIV2_PHCMP_PHCMP_SET(x) (((uint32_t)(x) << QEIV2_PHCMP_PHCMP_SHIFT) & QEIV2_PHCMP_PHCMP_MASK)
#define QEIV2_PHCMP_PHCMP_GET(x) (((uint32_t)(x) & QEIV2_PHCMP_PHCMP_MASK) >> QEIV2_PHCMP_PHCMP_SHIFT)

/* Bitfield definition for register: SPDCMP */
/*
 * SPDCMP (RW)
 *
 * spdcnt position compare value
 */
#define QEIV2_SPDCMP_SPDCMP_MASK (0xFFFFFFFFUL)
#define QEIV2_SPDCMP_SPDCMP_SHIFT (0U)
#define QEIV2_SPDCMP_SPDCMP_SET(x) (((uint32_t)(x) << QEIV2_SPDCMP_SPDCMP_SHIFT) & QEIV2_SPDCMP_SPDCMP_MASK)
#define QEIV2_SPDCMP_SPDCMP_GET(x) (((uint32_t)(x) & QEIV2_SPDCMP_SPDCMP_MASK) >> QEIV2_SPDCMP_SPDCMP_SHIFT)

/* Bitfield definition for register: DMAEN */
/*
 * WDGFEN (RW)
 *
 * 1- generate dma request when wdg flag set
 */
#define QEIV2_DMAEN_WDGFEN_MASK (0x80000000UL)
#define QEIV2_DMAEN_WDGFEN_SHIFT (31U)
#define QEIV2_DMAEN_WDGFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_WDGFEN_SHIFT) & QEIV2_DMAEN_WDGFEN_MASK)
#define QEIV2_DMAEN_WDGFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_WDGFEN_MASK) >> QEIV2_DMAEN_WDGFEN_SHIFT)

/*
 * HOMEFEN (RW)
 *
 * 1- generate dma request when homef flag set
 */
#define QEIV2_DMAEN_HOMEFEN_MASK (0x40000000UL)
#define QEIV2_DMAEN_HOMEFEN_SHIFT (30U)
#define QEIV2_DMAEN_HOMEFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_HOMEFEN_SHIFT) & QEIV2_DMAEN_HOMEFEN_MASK)
#define QEIV2_DMAEN_HOMEFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_HOMEFEN_MASK) >> QEIV2_DMAEN_HOMEFEN_SHIFT)

/*
 * POSCMPFEN (RW)
 *
 * 1- generate dma request when poscmpf flag set
 */
#define QEIV2_DMAEN_POSCMPFEN_MASK (0x20000000UL)
#define QEIV2_DMAEN_POSCMPFEN_SHIFT (29U)
#define QEIV2_DMAEN_POSCMPFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_POSCMPFEN_SHIFT) & QEIV2_DMAEN_POSCMPFEN_MASK)
#define QEIV2_DMAEN_POSCMPFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_POSCMPFEN_MASK) >> QEIV2_DMAEN_POSCMPFEN_SHIFT)

/*
 * ZPHFEN (RW)
 *
 * 1- generate dma request when zphf flag set
 */
#define QEIV2_DMAEN_ZPHFEN_MASK (0x10000000UL)
#define QEIV2_DMAEN_ZPHFEN_SHIFT (28U)
#define QEIV2_DMAEN_ZPHFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_ZPHFEN_SHIFT) & QEIV2_DMAEN_ZPHFEN_MASK)
#define QEIV2_DMAEN_ZPHFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_ZPHFEN_MASK) >> QEIV2_DMAEN_ZPHFEN_SHIFT)

/*
 * ZMISSFEN (RW)
 *
 */
#define QEIV2_DMAEN_ZMISSFEN_MASK (0x8000000UL)
#define QEIV2_DMAEN_ZMISSFEN_SHIFT (27U)
#define QEIV2_DMAEN_ZMISSFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_ZMISSFEN_SHIFT) & QEIV2_DMAEN_ZMISSFEN_MASK)
#define QEIV2_DMAEN_ZMISSFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_ZMISSFEN_MASK) >> QEIV2_DMAEN_ZMISSFEN_SHIFT)

/*
 * WIDTHTMFEN (RW)
 *
 */
#define QEIV2_DMAEN_WIDTHTMFEN_MASK (0x4000000UL)
#define QEIV2_DMAEN_WIDTHTMFEN_SHIFT (26U)
#define QEIV2_DMAEN_WIDTHTMFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_WIDTHTMFEN_SHIFT) & QEIV2_DMAEN_WIDTHTMFEN_MASK)
#define QEIV2_DMAEN_WIDTHTMFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_WIDTHTMFEN_MASK) >> QEIV2_DMAEN_WIDTHTMFEN_SHIFT)

/*
 * POS2CMPFEN (RW)
 *
 */
#define QEIV2_DMAEN_POS2CMPFEN_MASK (0x2000000UL)
#define QEIV2_DMAEN_POS2CMPFEN_SHIFT (25U)
#define QEIV2_DMAEN_POS2CMPFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_POS2CMPFEN_SHIFT) & QEIV2_DMAEN_POS2CMPFEN_MASK)
#define QEIV2_DMAEN_POS2CMPFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_POS2CMPFEN_MASK) >> QEIV2_DMAEN_POS2CMPFEN_SHIFT)

/*
 * DIRCHGFEN (RW)
 *
 */
#define QEIV2_DMAEN_DIRCHGFEN_MASK (0x1000000UL)
#define QEIV2_DMAEN_DIRCHGFEN_SHIFT (24U)
#define QEIV2_DMAEN_DIRCHGFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_DIRCHGFEN_SHIFT) & QEIV2_DMAEN_DIRCHGFEN_MASK)
#define QEIV2_DMAEN_DIRCHGFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_DIRCHGFEN_MASK) >> QEIV2_DMAEN_DIRCHGFEN_SHIFT)

/*
 * CYCLE0FEN (RW)
 *
 */
#define QEIV2_DMAEN_CYCLE0FEN_MASK (0x800000UL)
#define QEIV2_DMAEN_CYCLE0FEN_SHIFT (23U)
#define QEIV2_DMAEN_CYCLE0FEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_CYCLE0FEN_SHIFT) & QEIV2_DMAEN_CYCLE0FEN_MASK)
#define QEIV2_DMAEN_CYCLE0FEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_CYCLE0FEN_MASK) >> QEIV2_DMAEN_CYCLE0FEN_SHIFT)

/*
 * CYCLE1FEN (RW)
 *
 */
#define QEIV2_DMAEN_CYCLE1FEN_MASK (0x400000UL)
#define QEIV2_DMAEN_CYCLE1FEN_SHIFT (22U)
#define QEIV2_DMAEN_CYCLE1FEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_CYCLE1FEN_SHIFT) & QEIV2_DMAEN_CYCLE1FEN_MASK)
#define QEIV2_DMAEN_CYCLE1FEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_CYCLE1FEN_MASK) >> QEIV2_DMAEN_CYCLE1FEN_SHIFT)

/*
 * PULSE0FEN (RW)
 *
 */
#define QEIV2_DMAEN_PULSE0FEN_MASK (0x200000UL)
#define QEIV2_DMAEN_PULSE0FEN_SHIFT (21U)
#define QEIV2_DMAEN_PULSE0FEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_PULSE0FEN_SHIFT) & QEIV2_DMAEN_PULSE0FEN_MASK)
#define QEIV2_DMAEN_PULSE0FEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_PULSE0FEN_MASK) >> QEIV2_DMAEN_PULSE0FEN_SHIFT)

/*
 * PULSE1FEN (RW)
 *
 */
#define QEIV2_DMAEN_PULSE1FEN_MASK (0x100000UL)
#define QEIV2_DMAEN_PULSE1FEN_SHIFT (20U)
#define QEIV2_DMAEN_PULSE1FEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_PULSE1FEN_SHIFT) & QEIV2_DMAEN_PULSE1FEN_MASK)
#define QEIV2_DMAEN_PULSE1FEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_PULSE1FEN_MASK) >> QEIV2_DMAEN_PULSE1FEN_SHIFT)

/*
 * HOME2FEN (RW)
 *
 */
#define QEIV2_DMAEN_HOME2FEN_MASK (0x80000UL)
#define QEIV2_DMAEN_HOME2FEN_SHIFT (19U)
#define QEIV2_DMAEN_HOME2FEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_HOME2FEN_SHIFT) & QEIV2_DMAEN_HOME2FEN_MASK)
#define QEIV2_DMAEN_HOME2FEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_HOME2FEN_MASK) >> QEIV2_DMAEN_HOME2FEN_SHIFT)

/*
 * FAULTFEN (RW)
 *
 */
#define QEIV2_DMAEN_FAULTFEN_MASK (0x40000UL)
#define QEIV2_DMAEN_FAULTFEN_SHIFT (18U)
#define QEIV2_DMAEN_FAULTFEN_SET(x) (((uint32_t)(x) << QEIV2_DMAEN_FAULTFEN_SHIFT) & QEIV2_DMAEN_FAULTFEN_MASK)
#define QEIV2_DMAEN_FAULTFEN_GET(x) (((uint32_t)(x) & QEIV2_DMAEN_FAULTFEN_MASK) >> QEIV2_DMAEN_FAULTFEN_SHIFT)

/* Bitfield definition for register: SR */
/*
 * WDGF (RW)
 *
 * watchdog flag
 */
#define QEIV2_SR_WDGF_MASK (0x80000000UL)
#define QEIV2_SR_WDGF_SHIFT (31U)
#define QEIV2_SR_WDGF_SET(x) (((uint32_t)(x) << QEIV2_SR_WDGF_SHIFT) & QEIV2_SR_WDGF_MASK)
#define QEIV2_SR_WDGF_GET(x) (((uint32_t)(x) & QEIV2_SR_WDGF_MASK) >> QEIV2_SR_WDGF_SHIFT)

/*
 * HOMEF (RW)
 *
 * home flag
 */
#define QEIV2_SR_HOMEF_MASK (0x40000000UL)
#define QEIV2_SR_HOMEF_SHIFT (30U)
#define QEIV2_SR_HOMEF_SET(x) (((uint32_t)(x) << QEIV2_SR_HOMEF_SHIFT) & QEIV2_SR_HOMEF_MASK)
#define QEIV2_SR_HOMEF_GET(x) (((uint32_t)(x) & QEIV2_SR_HOMEF_MASK) >> QEIV2_SR_HOMEF_SHIFT)

/*
 * POSCMPF (RW)
 *
 * postion compare match flag
 */
#define QEIV2_SR_POSCMPF_MASK (0x20000000UL)
#define QEIV2_SR_POSCMPF_SHIFT (29U)
#define QEIV2_SR_POSCMPF_SET(x) (((uint32_t)(x) << QEIV2_SR_POSCMPF_SHIFT) & QEIV2_SR_POSCMPF_MASK)
#define QEIV2_SR_POSCMPF_GET(x) (((uint32_t)(x) & QEIV2_SR_POSCMPF_MASK) >> QEIV2_SR_POSCMPF_SHIFT)

/*
 * ZPHF (RW)
 *
 * z input flag
 */
#define QEIV2_SR_ZPHF_MASK (0x10000000UL)
#define QEIV2_SR_ZPHF_SHIFT (28U)
#define QEIV2_SR_ZPHF_SET(x) (((uint32_t)(x) << QEIV2_SR_ZPHF_SHIFT) & QEIV2_SR_ZPHF_MASK)
#define QEIV2_SR_ZPHF_GET(x) (((uint32_t)(x) & QEIV2_SR_ZPHF_MASK) >> QEIV2_SR_ZPHF_SHIFT)

/*
 * ZMISSF (RW)
 *
 */
#define QEIV2_SR_ZMISSF_MASK (0x8000000UL)
#define QEIV2_SR_ZMISSF_SHIFT (27U)
#define QEIV2_SR_ZMISSF_SET(x) (((uint32_t)(x) << QEIV2_SR_ZMISSF_SHIFT) & QEIV2_SR_ZMISSF_MASK)
#define QEIV2_SR_ZMISSF_GET(x) (((uint32_t)(x) & QEIV2_SR_ZMISSF_MASK) >> QEIV2_SR_ZMISSF_SHIFT)

/*
 * WIDTHTMF (RW)
 *
 */
#define QEIV2_SR_WIDTHTMF_MASK (0x4000000UL)
#define QEIV2_SR_WIDTHTMF_SHIFT (26U)
#define QEIV2_SR_WIDTHTMF_SET(x) (((uint32_t)(x) << QEIV2_SR_WIDTHTMF_SHIFT) & QEIV2_SR_WIDTHTMF_MASK)
#define QEIV2_SR_WIDTHTMF_GET(x) (((uint32_t)(x) & QEIV2_SR_WIDTHTMF_MASK) >> QEIV2_SR_WIDTHTMF_SHIFT)

/*
 * POS2CMPF (RW)
 *
 */
#define QEIV2_SR_POS2CMPF_MASK (0x2000000UL)
#define QEIV2_SR_POS2CMPF_SHIFT (25U)
#define QEIV2_SR_POS2CMPF_SET(x) (((uint32_t)(x) << QEIV2_SR_POS2CMPF_SHIFT) & QEIV2_SR_POS2CMPF_MASK)
#define QEIV2_SR_POS2CMPF_GET(x) (((uint32_t)(x) & QEIV2_SR_POS2CMPF_MASK) >> QEIV2_SR_POS2CMPF_SHIFT)

/*
 * DIRCHGF (RW)
 *
 */
#define QEIV2_SR_DIRCHGF_MASK (0x1000000UL)
#define QEIV2_SR_DIRCHGF_SHIFT (24U)
#define QEIV2_SR_DIRCHGF_SET(x) (((uint32_t)(x) << QEIV2_SR_DIRCHGF_SHIFT) & QEIV2_SR_DIRCHGF_MASK)
#define QEIV2_SR_DIRCHGF_GET(x) (((uint32_t)(x) & QEIV2_SR_DIRCHGF_MASK) >> QEIV2_SR_DIRCHGF_SHIFT)

/*
 * CYCLE0F (RW)
 *
 */
#define QEIV2_SR_CYCLE0F_MASK (0x800000UL)
#define QEIV2_SR_CYCLE0F_SHIFT (23U)
#define QEIV2_SR_CYCLE0F_SET(x) (((uint32_t)(x) << QEIV2_SR_CYCLE0F_SHIFT) & QEIV2_SR_CYCLE0F_MASK)
#define QEIV2_SR_CYCLE0F_GET(x) (((uint32_t)(x) & QEIV2_SR_CYCLE0F_MASK) >> QEIV2_SR_CYCLE0F_SHIFT)

/*
 * CYCLE1F (RW)
 *
 */
#define QEIV2_SR_CYCLE1F_MASK (0x400000UL)
#define QEIV2_SR_CYCLE1F_SHIFT (22U)
#define QEIV2_SR_CYCLE1F_SET(x) (((uint32_t)(x) << QEIV2_SR_CYCLE1F_SHIFT) & QEIV2_SR_CYCLE1F_MASK)
#define QEIV2_SR_CYCLE1F_GET(x) (((uint32_t)(x) & QEIV2_SR_CYCLE1F_MASK) >> QEIV2_SR_CYCLE1F_SHIFT)

/*
 * PULSE0F (RW)
 *
 */
#define QEIV2_SR_PULSE0F_MASK (0x200000UL)
#define QEIV2_SR_PULSE0F_SHIFT (21U)
#define QEIV2_SR_PULSE0F_SET(x) (((uint32_t)(x) << QEIV2_SR_PULSE0F_SHIFT) & QEIV2_SR_PULSE0F_MASK)
#define QEIV2_SR_PULSE0F_GET(x) (((uint32_t)(x) & QEIV2_SR_PULSE0F_MASK) >> QEIV2_SR_PULSE0F_SHIFT)

/*
 * PULSE1F (RW)
 *
 */
#define QEIV2_SR_PULSE1F_MASK (0x100000UL)
#define QEIV2_SR_PULSE1F_SHIFT (20U)
#define QEIV2_SR_PULSE1F_SET(x) (((uint32_t)(x) << QEIV2_SR_PULSE1F_SHIFT) & QEIV2_SR_PULSE1F_MASK)
#define QEIV2_SR_PULSE1F_GET(x) (((uint32_t)(x) & QEIV2_SR_PULSE1F_MASK) >> QEIV2_SR_PULSE1F_SHIFT)

/*
 * HOME2F (RW)
 *
 */
#define QEIV2_SR_HOME2F_MASK (0x80000UL)
#define QEIV2_SR_HOME2F_SHIFT (19U)
#define QEIV2_SR_HOME2F_SET(x) (((uint32_t)(x) << QEIV2_SR_HOME2F_SHIFT) & QEIV2_SR_HOME2F_MASK)
#define QEIV2_SR_HOME2F_GET(x) (((uint32_t)(x) & QEIV2_SR_HOME2F_MASK) >> QEIV2_SR_HOME2F_SHIFT)

/*
 * FAULTF (RW)
 *
 */
#define QEIV2_SR_FAULTF_MASK (0x40000UL)
#define QEIV2_SR_FAULTF_SHIFT (18U)
#define QEIV2_SR_FAULTF_SET(x) (((uint32_t)(x) << QEIV2_SR_FAULTF_SHIFT) & QEIV2_SR_FAULTF_MASK)
#define QEIV2_SR_FAULTF_GET(x) (((uint32_t)(x) & QEIV2_SR_FAULTF_MASK) >> QEIV2_SR_FAULTF_SHIFT)

/* Bitfield definition for register: IRQEN */
/*
 * WDGIE (RW)
 *
 * 1- generate interrupt when wdg flag set
 */
#define QEIV2_IRQEN_WDGIE_MASK (0x80000000UL)
#define QEIV2_IRQEN_WDGIE_SHIFT (31U)
#define QEIV2_IRQEN_WDGIE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_WDGIE_SHIFT) & QEIV2_IRQEN_WDGIE_MASK)
#define QEIV2_IRQEN_WDGIE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_WDGIE_MASK) >> QEIV2_IRQEN_WDGIE_SHIFT)

/*
 * HOMEIE (RW)
 *
 * 1- generate interrupt when homef flag set
 */
#define QEIV2_IRQEN_HOMEIE_MASK (0x40000000UL)
#define QEIV2_IRQEN_HOMEIE_SHIFT (30U)
#define QEIV2_IRQEN_HOMEIE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_HOMEIE_SHIFT) & QEIV2_IRQEN_HOMEIE_MASK)
#define QEIV2_IRQEN_HOMEIE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_HOMEIE_MASK) >> QEIV2_IRQEN_HOMEIE_SHIFT)

/*
 * POSCMPIE (RW)
 *
 * 1- generate interrupt when poscmpf flag set
 */
#define QEIV2_IRQEN_POSCMPIE_MASK (0x20000000UL)
#define QEIV2_IRQEN_POSCMPIE_SHIFT (29U)
#define QEIV2_IRQEN_POSCMPIE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_POSCMPIE_SHIFT) & QEIV2_IRQEN_POSCMPIE_MASK)
#define QEIV2_IRQEN_POSCMPIE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_POSCMPIE_MASK) >> QEIV2_IRQEN_POSCMPIE_SHIFT)

/*
 * ZPHIE (RW)
 *
 * 1- generate interrupt when zphf flag set
 */
#define QEIV2_IRQEN_ZPHIE_MASK (0x10000000UL)
#define QEIV2_IRQEN_ZPHIE_SHIFT (28U)
#define QEIV2_IRQEN_ZPHIE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_ZPHIE_SHIFT) & QEIV2_IRQEN_ZPHIE_MASK)
#define QEIV2_IRQEN_ZPHIE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_ZPHIE_MASK) >> QEIV2_IRQEN_ZPHIE_SHIFT)

/*
 * ZMISSE (RW)
 *
 */
#define QEIV2_IRQEN_ZMISSE_MASK (0x8000000UL)
#define QEIV2_IRQEN_ZMISSE_SHIFT (27U)
#define QEIV2_IRQEN_ZMISSE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_ZMISSE_SHIFT) & QEIV2_IRQEN_ZMISSE_MASK)
#define QEIV2_IRQEN_ZMISSE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_ZMISSE_MASK) >> QEIV2_IRQEN_ZMISSE_SHIFT)

/*
 * WIDTHTME (RW)
 *
 */
#define QEIV2_IRQEN_WIDTHTME_MASK (0x4000000UL)
#define QEIV2_IRQEN_WIDTHTME_SHIFT (26U)
#define QEIV2_IRQEN_WIDTHTME_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_WIDTHTME_SHIFT) & QEIV2_IRQEN_WIDTHTME_MASK)
#define QEIV2_IRQEN_WIDTHTME_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_WIDTHTME_MASK) >> QEIV2_IRQEN_WIDTHTME_SHIFT)

/*
 * POS2CMPE (RW)
 *
 */
#define QEIV2_IRQEN_POS2CMPE_MASK (0x2000000UL)
#define QEIV2_IRQEN_POS2CMPE_SHIFT (25U)
#define QEIV2_IRQEN_POS2CMPE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_POS2CMPE_SHIFT) & QEIV2_IRQEN_POS2CMPE_MASK)
#define QEIV2_IRQEN_POS2CMPE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_POS2CMPE_MASK) >> QEIV2_IRQEN_POS2CMPE_SHIFT)

/*
 * DIRCHGE (RW)
 *
 */
#define QEIV2_IRQEN_DIRCHGE_MASK (0x1000000UL)
#define QEIV2_IRQEN_DIRCHGE_SHIFT (24U)
#define QEIV2_IRQEN_DIRCHGE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_DIRCHGE_SHIFT) & QEIV2_IRQEN_DIRCHGE_MASK)
#define QEIV2_IRQEN_DIRCHGE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_DIRCHGE_MASK) >> QEIV2_IRQEN_DIRCHGE_SHIFT)

/*
 * CYCLE0E (RW)
 *
 */
#define QEIV2_IRQEN_CYCLE0E_MASK (0x800000UL)
#define QEIV2_IRQEN_CYCLE0E_SHIFT (23U)
#define QEIV2_IRQEN_CYCLE0E_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_CYCLE0E_SHIFT) & QEIV2_IRQEN_CYCLE0E_MASK)
#define QEIV2_IRQEN_CYCLE0E_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_CYCLE0E_MASK) >> QEIV2_IRQEN_CYCLE0E_SHIFT)

/*
 * CYCLE1E (RW)
 *
 */
#define QEIV2_IRQEN_CYCLE1E_MASK (0x400000UL)
#define QEIV2_IRQEN_CYCLE1E_SHIFT (22U)
#define QEIV2_IRQEN_CYCLE1E_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_CYCLE1E_SHIFT) & QEIV2_IRQEN_CYCLE1E_MASK)
#define QEIV2_IRQEN_CYCLE1E_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_CYCLE1E_MASK) >> QEIV2_IRQEN_CYCLE1E_SHIFT)

/*
 * PULSE0E (RW)
 *
 */
#define QEIV2_IRQEN_PULSE0E_MASK (0x200000UL)
#define QEIV2_IRQEN_PULSE0E_SHIFT (21U)
#define QEIV2_IRQEN_PULSE0E_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_PULSE0E_SHIFT) & QEIV2_IRQEN_PULSE0E_MASK)
#define QEIV2_IRQEN_PULSE0E_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_PULSE0E_MASK) >> QEIV2_IRQEN_PULSE0E_SHIFT)

/*
 * PULSE1E (RW)
 *
 */
#define QEIV2_IRQEN_PULSE1E_MASK (0x100000UL)
#define QEIV2_IRQEN_PULSE1E_SHIFT (20U)
#define QEIV2_IRQEN_PULSE1E_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_PULSE1E_SHIFT) & QEIV2_IRQEN_PULSE1E_MASK)
#define QEIV2_IRQEN_PULSE1E_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_PULSE1E_MASK) >> QEIV2_IRQEN_PULSE1E_SHIFT)

/*
 * HOME2E (RW)
 *
 */
#define QEIV2_IRQEN_HOME2E_MASK (0x80000UL)
#define QEIV2_IRQEN_HOME2E_SHIFT (19U)
#define QEIV2_IRQEN_HOME2E_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_HOME2E_SHIFT) & QEIV2_IRQEN_HOME2E_MASK)
#define QEIV2_IRQEN_HOME2E_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_HOME2E_MASK) >> QEIV2_IRQEN_HOME2E_SHIFT)

/*
 * FAULTE (RW)
 *
 */
#define QEIV2_IRQEN_FAULTE_MASK (0x40000UL)
#define QEIV2_IRQEN_FAULTE_SHIFT (18U)
#define QEIV2_IRQEN_FAULTE_SET(x) (((uint32_t)(x) << QEIV2_IRQEN_FAULTE_SHIFT) & QEIV2_IRQEN_FAULTE_MASK)
#define QEIV2_IRQEN_FAULTE_GET(x) (((uint32_t)(x) & QEIV2_IRQEN_FAULTE_MASK) >> QEIV2_IRQEN_FAULTE_SHIFT)

/* Bitfield definition for register of struct array COUNT: Z */
/*
 * ZCNT (RW)
 *
 * zcnt value
 */
#define QEIV2_COUNT_Z_ZCNT_MASK (0xFFFFFFFFUL)
#define QEIV2_COUNT_Z_ZCNT_SHIFT (0U)
#define QEIV2_COUNT_Z_ZCNT_SET(x) (((uint32_t)(x) << QEIV2_COUNT_Z_ZCNT_SHIFT) & QEIV2_COUNT_Z_ZCNT_MASK)
#define QEIV2_COUNT_Z_ZCNT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_Z_ZCNT_MASK) >> QEIV2_COUNT_Z_ZCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: PH */
/*
 * DIR (RO)
 *
 * 1- reverse rotation
 * 0- forward rotation
 */
#define QEIV2_COUNT_PH_DIR_MASK (0x40000000UL)
#define QEIV2_COUNT_PH_DIR_SHIFT (30U)
#define QEIV2_COUNT_PH_DIR_GET(x) (((uint32_t)(x) & QEIV2_COUNT_PH_DIR_MASK) >> QEIV2_COUNT_PH_DIR_SHIFT)

/*
 * ASTAT (RO)
 *
 * 1- a input is high
 * 0- a input is low
 */
#define QEIV2_COUNT_PH_ASTAT_MASK (0x4000000UL)
#define QEIV2_COUNT_PH_ASTAT_SHIFT (26U)
#define QEIV2_COUNT_PH_ASTAT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_PH_ASTAT_MASK) >> QEIV2_COUNT_PH_ASTAT_SHIFT)

/*
 * BSTAT (RO)
 *
 * 1- b input is high
 * 0- b input is low
 */
#define QEIV2_COUNT_PH_BSTAT_MASK (0x2000000UL)
#define QEIV2_COUNT_PH_BSTAT_SHIFT (25U)
#define QEIV2_COUNT_PH_BSTAT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_PH_BSTAT_MASK) >> QEIV2_COUNT_PH_BSTAT_SHIFT)

/*
 * PHCNT (RO)
 *
 * phcnt value
 */
#define QEIV2_COUNT_PH_PHCNT_MASK (0x1FFFFFUL)
#define QEIV2_COUNT_PH_PHCNT_SHIFT (0U)
#define QEIV2_COUNT_PH_PHCNT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_PH_PHCNT_MASK) >> QEIV2_COUNT_PH_PHCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: SPD */
/*
 * DIR (RO)
 *
 * 1- reverse rotation
 * 0- forward rotation
 */
#define QEIV2_COUNT_SPD_DIR_MASK (0x80000000UL)
#define QEIV2_COUNT_SPD_DIR_SHIFT (31U)
#define QEIV2_COUNT_SPD_DIR_GET(x) (((uint32_t)(x) & QEIV2_COUNT_SPD_DIR_MASK) >> QEIV2_COUNT_SPD_DIR_SHIFT)

/*
 * ASTAT (RO)
 *
 * 1- a input is high
 * 0- a input is low
 */
#define QEIV2_COUNT_SPD_ASTAT_MASK (0x40000000UL)
#define QEIV2_COUNT_SPD_ASTAT_SHIFT (30U)
#define QEIV2_COUNT_SPD_ASTAT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_SPD_ASTAT_MASK) >> QEIV2_COUNT_SPD_ASTAT_SHIFT)

/*
 * BSTAT (RW)
 *
 * 1- b input is high
 * 0- b input is low
 */
#define QEIV2_COUNT_SPD_BSTAT_MASK (0x20000000UL)
#define QEIV2_COUNT_SPD_BSTAT_SHIFT (29U)
#define QEIV2_COUNT_SPD_BSTAT_SET(x) (((uint32_t)(x) << QEIV2_COUNT_SPD_BSTAT_SHIFT) & QEIV2_COUNT_SPD_BSTAT_MASK)
#define QEIV2_COUNT_SPD_BSTAT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_SPD_BSTAT_MASK) >> QEIV2_COUNT_SPD_BSTAT_SHIFT)

/*
 * SPDCNT (RO)
 *
 * spdcnt value
 */
#define QEIV2_COUNT_SPD_SPDCNT_MASK (0xFFFFFFFUL)
#define QEIV2_COUNT_SPD_SPDCNT_SHIFT (0U)
#define QEIV2_COUNT_SPD_SPDCNT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_SPD_SPDCNT_MASK) >> QEIV2_COUNT_SPD_SPDCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: TMR */
/*
 * TMRCNT (RO)
 *
 * 32 bit free run timer
 */
#define QEIV2_COUNT_TMR_TMRCNT_MASK (0xFFFFFFFFUL)
#define QEIV2_COUNT_TMR_TMRCNT_SHIFT (0U)
#define QEIV2_COUNT_TMR_TMRCNT_GET(x) (((uint32_t)(x) & QEIV2_COUNT_TMR_TMRCNT_MASK) >> QEIV2_COUNT_TMR_TMRCNT_SHIFT)

/* Bitfield definition for register: ZCMP2 */
/*
 * ZCMP2 (RW)
 *
 */
#define QEIV2_ZCMP2_ZCMP2_MASK (0xFFFFFFFFUL)
#define QEIV2_ZCMP2_ZCMP2_SHIFT (0U)
#define QEIV2_ZCMP2_ZCMP2_SET(x) (((uint32_t)(x) << QEIV2_ZCMP2_ZCMP2_SHIFT) & QEIV2_ZCMP2_ZCMP2_MASK)
#define QEIV2_ZCMP2_ZCMP2_GET(x) (((uint32_t)(x) & QEIV2_ZCMP2_ZCMP2_MASK) >> QEIV2_ZCMP2_ZCMP2_SHIFT)

/* Bitfield definition for register: PHCMP2 */
/*
 * PHCMP2 (RW)
 *
 */
#define QEIV2_PHCMP2_PHCMP2_MASK (0xFFFFFFFFUL)
#define QEIV2_PHCMP2_PHCMP2_SHIFT (0U)
#define QEIV2_PHCMP2_PHCMP2_SET(x) (((uint32_t)(x) << QEIV2_PHCMP2_PHCMP2_SHIFT) & QEIV2_PHCMP2_PHCMP2_MASK)
#define QEIV2_PHCMP2_PHCMP2_GET(x) (((uint32_t)(x) & QEIV2_PHCMP2_PHCMP2_MASK) >> QEIV2_PHCMP2_PHCMP2_SHIFT)

/* Bitfield definition for register: SPDCMP2 */
/*
 * SPDCMP2 (RW)
 *
 */
#define QEIV2_SPDCMP2_SPDCMP2_MASK (0xFFFFFFFFUL)
#define QEIV2_SPDCMP2_SPDCMP2_SHIFT (0U)
#define QEIV2_SPDCMP2_SPDCMP2_SET(x) (((uint32_t)(x) << QEIV2_SPDCMP2_SPDCMP2_SHIFT) & QEIV2_SPDCMP2_SPDCMP2_MASK)
#define QEIV2_SPDCMP2_SPDCMP2_GET(x) (((uint32_t)(x) & QEIV2_SPDCMP2_SPDCMP2_MASK) >> QEIV2_SPDCMP2_SPDCMP2_SHIFT)

/* Bitfield definition for register: MATCH_CFG */
/*
 * ZCMPDIS (RW)
 *
 * 1- postion compare not include zcnt
 */
#define QEIV2_MATCH_CFG_ZCMPDIS_MASK (0x80000000UL)
#define QEIV2_MATCH_CFG_ZCMPDIS_SHIFT (31U)
#define QEIV2_MATCH_CFG_ZCMPDIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_ZCMPDIS_SHIFT) & QEIV2_MATCH_CFG_ZCMPDIS_MASK)
#define QEIV2_MATCH_CFG_ZCMPDIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_ZCMPDIS_MASK) >> QEIV2_MATCH_CFG_ZCMPDIS_SHIFT)

/*
 * DIRCMPDIS (RW)
 *
 * 1- postion compare not include rotation direction
 */
#define QEIV2_MATCH_CFG_DIRCMPDIS_MASK (0x40000000UL)
#define QEIV2_MATCH_CFG_DIRCMPDIS_SHIFT (30U)
#define QEIV2_MATCH_CFG_DIRCMPDIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_DIRCMPDIS_SHIFT) & QEIV2_MATCH_CFG_DIRCMPDIS_MASK)
#define QEIV2_MATCH_CFG_DIRCMPDIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_DIRCMPDIS_MASK) >> QEIV2_MATCH_CFG_DIRCMPDIS_SHIFT)

/*
 * DIRCMP (RW)
 *
 * 0- position compare need positive rotation
 * 1- position compare need negative rotation
 */
#define QEIV2_MATCH_CFG_DIRCMP_MASK (0x20000000UL)
#define QEIV2_MATCH_CFG_DIRCMP_SHIFT (29U)
#define QEIV2_MATCH_CFG_DIRCMP_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_DIRCMP_SHIFT) & QEIV2_MATCH_CFG_DIRCMP_MASK)
#define QEIV2_MATCH_CFG_DIRCMP_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_DIRCMP_MASK) >> QEIV2_MATCH_CFG_DIRCMP_SHIFT)

/*
 * SPDCMPDIS (RW)
 *
 */
#define QEIV2_MATCH_CFG_SPDCMPDIS_MASK (0x10000000UL)
#define QEIV2_MATCH_CFG_SPDCMPDIS_SHIFT (28U)
#define QEIV2_MATCH_CFG_SPDCMPDIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_SPDCMPDIS_SHIFT) & QEIV2_MATCH_CFG_SPDCMPDIS_MASK)
#define QEIV2_MATCH_CFG_SPDCMPDIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_SPDCMPDIS_MASK) >> QEIV2_MATCH_CFG_SPDCMPDIS_SHIFT)

/*
 * PHASE_MATCH_DIS (RW)
 *
 */
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS_MASK (0x8000000UL)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS_SHIFT (27U)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_PHASE_MATCH_DIS_SHIFT) & QEIV2_MATCH_CFG_PHASE_MATCH_DIS_MASK)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_PHASE_MATCH_DIS_MASK) >> QEIV2_MATCH_CFG_PHASE_MATCH_DIS_SHIFT)

/*
 * POS_MATCH_DIR (RW)
 *
 */
#define QEIV2_MATCH_CFG_POS_MATCH_DIR_MASK (0x4000000UL)
#define QEIV2_MATCH_CFG_POS_MATCH_DIR_SHIFT (26U)
#define QEIV2_MATCH_CFG_POS_MATCH_DIR_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_POS_MATCH_DIR_SHIFT) & QEIV2_MATCH_CFG_POS_MATCH_DIR_MASK)
#define QEIV2_MATCH_CFG_POS_MATCH_DIR_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_POS_MATCH_DIR_MASK) >> QEIV2_MATCH_CFG_POS_MATCH_DIR_SHIFT)

/*
 * POS_MATCH_OPT (RW)
 *
 */
#define QEIV2_MATCH_CFG_POS_MATCH_OPT_MASK (0x2000000UL)
#define QEIV2_MATCH_CFG_POS_MATCH_OPT_SHIFT (25U)
#define QEIV2_MATCH_CFG_POS_MATCH_OPT_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_POS_MATCH_OPT_SHIFT) & QEIV2_MATCH_CFG_POS_MATCH_OPT_MASK)
#define QEIV2_MATCH_CFG_POS_MATCH_OPT_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_POS_MATCH_OPT_MASK) >> QEIV2_MATCH_CFG_POS_MATCH_OPT_SHIFT)

/*
 * ZCMP2DIS (RW)
 *
 */
#define QEIV2_MATCH_CFG_ZCMP2DIS_MASK (0x8000U)
#define QEIV2_MATCH_CFG_ZCMP2DIS_SHIFT (15U)
#define QEIV2_MATCH_CFG_ZCMP2DIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_ZCMP2DIS_SHIFT) & QEIV2_MATCH_CFG_ZCMP2DIS_MASK)
#define QEIV2_MATCH_CFG_ZCMP2DIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_ZCMP2DIS_MASK) >> QEIV2_MATCH_CFG_ZCMP2DIS_SHIFT)

/*
 * DIRCMP2DIS (RW)
 *
 */
#define QEIV2_MATCH_CFG_DIRCMP2DIS_MASK (0x4000U)
#define QEIV2_MATCH_CFG_DIRCMP2DIS_SHIFT (14U)
#define QEIV2_MATCH_CFG_DIRCMP2DIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_DIRCMP2DIS_SHIFT) & QEIV2_MATCH_CFG_DIRCMP2DIS_MASK)
#define QEIV2_MATCH_CFG_DIRCMP2DIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_DIRCMP2DIS_MASK) >> QEIV2_MATCH_CFG_DIRCMP2DIS_SHIFT)

/*
 * DIRCMP2 (RW)
 *
 */
#define QEIV2_MATCH_CFG_DIRCMP2_MASK (0x2000U)
#define QEIV2_MATCH_CFG_DIRCMP2_SHIFT (13U)
#define QEIV2_MATCH_CFG_DIRCMP2_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_DIRCMP2_SHIFT) & QEIV2_MATCH_CFG_DIRCMP2_MASK)
#define QEIV2_MATCH_CFG_DIRCMP2_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_DIRCMP2_MASK) >> QEIV2_MATCH_CFG_DIRCMP2_SHIFT)

/*
 * SPDCMP2DIS (RW)
 *
 */
#define QEIV2_MATCH_CFG_SPDCMP2DIS_MASK (0x1000U)
#define QEIV2_MATCH_CFG_SPDCMP2DIS_SHIFT (12U)
#define QEIV2_MATCH_CFG_SPDCMP2DIS_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_SPDCMP2DIS_SHIFT) & QEIV2_MATCH_CFG_SPDCMP2DIS_MASK)
#define QEIV2_MATCH_CFG_SPDCMP2DIS_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_SPDCMP2DIS_MASK) >> QEIV2_MATCH_CFG_SPDCMP2DIS_SHIFT)

/*
 * PHASE_MATCH_DIS2 (RW)
 *
 */
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_MASK (0x800U)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_SHIFT (11U)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_SHIFT) & QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_MASK)
#define QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_MASK) >> QEIV2_MATCH_CFG_PHASE_MATCH_DIS2_SHIFT)

/*
 * POS_MATCH2_DIR (RW)
 *
 */
#define QEIV2_MATCH_CFG_POS_MATCH2_DIR_MASK (0x400U)
#define QEIV2_MATCH_CFG_POS_MATCH2_DIR_SHIFT (10U)
#define QEIV2_MATCH_CFG_POS_MATCH2_DIR_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_POS_MATCH2_DIR_SHIFT) & QEIV2_MATCH_CFG_POS_MATCH2_DIR_MASK)
#define QEIV2_MATCH_CFG_POS_MATCH2_DIR_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_POS_MATCH2_DIR_MASK) >> QEIV2_MATCH_CFG_POS_MATCH2_DIR_SHIFT)

/*
 * POS_MATCH2_OPT (RW)
 *
 */
#define QEIV2_MATCH_CFG_POS_MATCH2_OPT_MASK (0x200U)
#define QEIV2_MATCH_CFG_POS_MATCH2_OPT_SHIFT (9U)
#define QEIV2_MATCH_CFG_POS_MATCH2_OPT_SET(x) (((uint32_t)(x) << QEIV2_MATCH_CFG_POS_MATCH2_OPT_SHIFT) & QEIV2_MATCH_CFG_POS_MATCH2_OPT_MASK)
#define QEIV2_MATCH_CFG_POS_MATCH2_OPT_GET(x) (((uint32_t)(x) & QEIV2_MATCH_CFG_POS_MATCH2_OPT_MASK) >> QEIV2_MATCH_CFG_POS_MATCH2_OPT_SHIFT)

/* Bitfield definition for register array: FILT_CFG */
/*
 * OUTINV (RW)
 *
 * 1- Filter will invert the output
 * 0- Filter will not invert the output
 */
#define QEIV2_FILT_CFG_OUTINV_MASK (0x10000UL)
#define QEIV2_FILT_CFG_OUTINV_SHIFT (16U)
#define QEIV2_FILT_CFG_OUTINV_SET(x) (((uint32_t)(x) << QEIV2_FILT_CFG_OUTINV_SHIFT) & QEIV2_FILT_CFG_OUTINV_MASK)
#define QEIV2_FILT_CFG_OUTINV_GET(x) (((uint32_t)(x) & QEIV2_FILT_CFG_OUTINV_MASK) >> QEIV2_FILT_CFG_OUTINV_SHIFT)

/*
 * MODE (RW)
 *
 * This bitfields defines the filter mode
 * 000-bypass;
 * 100-rapid change mode;
 * 101-delay filter mode;
 * 110-stable low mode;
 * 111-stable high mode
 */
#define QEIV2_FILT_CFG_MODE_MASK (0xE000U)
#define QEIV2_FILT_CFG_MODE_SHIFT (13U)
#define QEIV2_FILT_CFG_MODE_SET(x) (((uint32_t)(x) << QEIV2_FILT_CFG_MODE_SHIFT) & QEIV2_FILT_CFG_MODE_MASK)
#define QEIV2_FILT_CFG_MODE_GET(x) (((uint32_t)(x) & QEIV2_FILT_CFG_MODE_MASK) >> QEIV2_FILT_CFG_MODE_SHIFT)

/*
 * SYNCEN (RW)
 *
 * set to enable sychronization input signal with TRGM clock
 */
#define QEIV2_FILT_CFG_SYNCEN_MASK (0x1000U)
#define QEIV2_FILT_CFG_SYNCEN_SHIFT (12U)
#define QEIV2_FILT_CFG_SYNCEN_SET(x) (((uint32_t)(x) << QEIV2_FILT_CFG_SYNCEN_SHIFT) & QEIV2_FILT_CFG_SYNCEN_MASK)
#define QEIV2_FILT_CFG_SYNCEN_GET(x) (((uint32_t)(x) & QEIV2_FILT_CFG_SYNCEN_MASK) >> QEIV2_FILT_CFG_SYNCEN_SHIFT)

/*
 * FILTLEN (RW)
 *
 * This bitfields defines the filter counter length.
 */
#define QEIV2_FILT_CFG_FILTLEN_MASK (0xFFFU)
#define QEIV2_FILT_CFG_FILTLEN_SHIFT (0U)
#define QEIV2_FILT_CFG_FILTLEN_SET(x) (((uint32_t)(x) << QEIV2_FILT_CFG_FILTLEN_SHIFT) & QEIV2_FILT_CFG_FILTLEN_MASK)
#define QEIV2_FILT_CFG_FILTLEN_GET(x) (((uint32_t)(x) & QEIV2_FILT_CFG_FILTLEN_MASK) >> QEIV2_FILT_CFG_FILTLEN_SHIFT)

/* Bitfield definition for register: QEI_CFG */
/*
 * SPEED_DIR_CHG_EN (RW)
 *
 * clear counter if detect direction change
 */
#define QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_MASK (0x1000U)
#define QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_SHIFT (12U)
#define QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_SHIFT) & QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_MASK)
#define QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_MASK) >> QEIV2_QEI_CFG_SPEED_DIR_CHG_EN_SHIFT)

/*
 * UVW_POS_OPT0 (RW)
 *
 * set to output next area position for QEO use;
 * clr to output exact point position for MMC use
 */
#define QEIV2_QEI_CFG_UVW_POS_OPT0_MASK (0x20U)
#define QEIV2_QEI_CFG_UVW_POS_OPT0_SHIFT (5U)
#define QEIV2_QEI_CFG_UVW_POS_OPT0_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_UVW_POS_OPT0_SHIFT) & QEIV2_QEI_CFG_UVW_POS_OPT0_MASK)
#define QEIV2_QEI_CFG_UVW_POS_OPT0_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_UVW_POS_OPT0_MASK) >> QEIV2_QEI_CFG_UVW_POS_OPT0_SHIFT)

/*
 * NEGEDGE_EN (RW)
 *
 * bit4:  negedge enable
 * bit3:  posedge enable
 * bit2:  W in hal enable
 * bit1:  signal b(or V in hal) enable
 * bit0:  signal a(or U in hal) enable
 * such as:
 * 01001:  use posedge A
 * 11010:  use both edge of signal B
 * 11111:  use both edge of all HAL siganls
 */
#define QEIV2_QEI_CFG_NEGEDGE_EN_MASK (0x10U)
#define QEIV2_QEI_CFG_NEGEDGE_EN_SHIFT (4U)
#define QEIV2_QEI_CFG_NEGEDGE_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_NEGEDGE_EN_SHIFT) & QEIV2_QEI_CFG_NEGEDGE_EN_MASK)
#define QEIV2_QEI_CFG_NEGEDGE_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_NEGEDGE_EN_MASK) >> QEIV2_QEI_CFG_NEGEDGE_EN_SHIFT)

/*
 * POSIDGE_EN (RW)
 *
 */
#define QEIV2_QEI_CFG_POSIDGE_EN_MASK (0x8U)
#define QEIV2_QEI_CFG_POSIDGE_EN_SHIFT (3U)
#define QEIV2_QEI_CFG_POSIDGE_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_POSIDGE_EN_SHIFT) & QEIV2_QEI_CFG_POSIDGE_EN_MASK)
#define QEIV2_QEI_CFG_POSIDGE_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_POSIDGE_EN_MASK) >> QEIV2_QEI_CFG_POSIDGE_EN_SHIFT)

/*
 * SIGZ_EN (RW)
 *
 */
#define QEIV2_QEI_CFG_SIGZ_EN_MASK (0x4U)
#define QEIV2_QEI_CFG_SIGZ_EN_SHIFT (2U)
#define QEIV2_QEI_CFG_SIGZ_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_SIGZ_EN_SHIFT) & QEIV2_QEI_CFG_SIGZ_EN_MASK)
#define QEIV2_QEI_CFG_SIGZ_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_SIGZ_EN_MASK) >> QEIV2_QEI_CFG_SIGZ_EN_SHIFT)

/*
 * SIGB_EN (RW)
 *
 */
#define QEIV2_QEI_CFG_SIGB_EN_MASK (0x2U)
#define QEIV2_QEI_CFG_SIGB_EN_SHIFT (1U)
#define QEIV2_QEI_CFG_SIGB_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_SIGB_EN_SHIFT) & QEIV2_QEI_CFG_SIGB_EN_MASK)
#define QEIV2_QEI_CFG_SIGB_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_SIGB_EN_MASK) >> QEIV2_QEI_CFG_SIGB_EN_SHIFT)

/*
 * SIGA_EN (RW)
 *
 */
#define QEIV2_QEI_CFG_SIGA_EN_MASK (0x1U)
#define QEIV2_QEI_CFG_SIGA_EN_SHIFT (0U)
#define QEIV2_QEI_CFG_SIGA_EN_SET(x) (((uint32_t)(x) << QEIV2_QEI_CFG_SIGA_EN_SHIFT) & QEIV2_QEI_CFG_SIGA_EN_MASK)
#define QEIV2_QEI_CFG_SIGA_EN_GET(x) (((uint32_t)(x) & QEIV2_QEI_CFG_SIGA_EN_MASK) >> QEIV2_QEI_CFG_SIGA_EN_SHIFT)

/* Bitfield definition for register: PULSE0_NUM */
/*
 * PULSE0_NUM (RW)
 *
 * for speed detection, will count the cycle number for configed pulse_num
 */
#define QEIV2_PULSE0_NUM_PULSE0_NUM_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0_NUM_PULSE0_NUM_SHIFT (0U)
#define QEIV2_PULSE0_NUM_PULSE0_NUM_SET(x) (((uint32_t)(x) << QEIV2_PULSE0_NUM_PULSE0_NUM_SHIFT) & QEIV2_PULSE0_NUM_PULSE0_NUM_MASK)
#define QEIV2_PULSE0_NUM_PULSE0_NUM_GET(x) (((uint32_t)(x) & QEIV2_PULSE0_NUM_PULSE0_NUM_MASK) >> QEIV2_PULSE0_NUM_PULSE0_NUM_SHIFT)

/* Bitfield definition for register: PULSE1_NUM */
/*
 * PULSE1_NUM (RW)
 *
 */
#define QEIV2_PULSE1_NUM_PULSE1_NUM_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1_NUM_PULSE1_NUM_SHIFT (0U)
#define QEIV2_PULSE1_NUM_PULSE1_NUM_SET(x) (((uint32_t)(x) << QEIV2_PULSE1_NUM_PULSE1_NUM_SHIFT) & QEIV2_PULSE1_NUM_PULSE1_NUM_MASK)
#define QEIV2_PULSE1_NUM_PULSE1_NUM_GET(x) (((uint32_t)(x) & QEIV2_PULSE1_NUM_PULSE1_NUM_MASK) >> QEIV2_PULSE1_NUM_PULSE1_NUM_SHIFT)

/* Bitfield definition for register: CYCLE0_CNT */
/*
 * CYCLE0_CNT (RO)
 *
 */
#define QEIV2_CYCLE0_CNT_CYCLE0_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE0_CNT_CYCLE0_CNT_SHIFT (0U)
#define QEIV2_CYCLE0_CNT_CYCLE0_CNT_GET(x) (((uint32_t)(x) & QEIV2_CYCLE0_CNT_CYCLE0_CNT_MASK) >> QEIV2_CYCLE0_CNT_CYCLE0_CNT_SHIFT)

/* Bitfield definition for register: CYCLE0PULSE_CNT */
/*
 * CYCLE0PULSE_CNT (RO)
 *
 */
#define QEIV2_CYCLE0PULSE_CNT_CYCLE0PULSE_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE0PULSE_CNT_CYCLE0PULSE_CNT_SHIFT (0U)
#define QEIV2_CYCLE0PULSE_CNT_CYCLE0PULSE_CNT_GET(x) (((uint32_t)(x) & QEIV2_CYCLE0PULSE_CNT_CYCLE0PULSE_CNT_MASK) >> QEIV2_CYCLE0PULSE_CNT_CYCLE0PULSE_CNT_SHIFT)

/* Bitfield definition for register: CYCLE1_CNT */
/*
 * CYCLE1_CNT (RO)
 *
 */
#define QEIV2_CYCLE1_CNT_CYCLE1_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE1_CNT_CYCLE1_CNT_SHIFT (0U)
#define QEIV2_CYCLE1_CNT_CYCLE1_CNT_GET(x) (((uint32_t)(x) & QEIV2_CYCLE1_CNT_CYCLE1_CNT_MASK) >> QEIV2_CYCLE1_CNT_CYCLE1_CNT_SHIFT)

/* Bitfield definition for register: CYCLE1PULSE_CNT */
/*
 * CYCLE1PULSE_CNT (RO)
 *
 */
#define QEIV2_CYCLE1PULSE_CNT_CYCLE1PULSE_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE1PULSE_CNT_CYCLE1PULSE_CNT_SHIFT (0U)
#define QEIV2_CYCLE1PULSE_CNT_CYCLE1PULSE_CNT_GET(x) (((uint32_t)(x) & QEIV2_CYCLE1PULSE_CNT_CYCLE1PULSE_CNT_MASK) >> QEIV2_CYCLE1PULSE_CNT_CYCLE1PULSE_CNT_SHIFT)

/* Bitfield definition for register: CYCLE0_SNAP0 */
/*
 * CYCLE0_SNAP0 (RO)
 *
 */
#define QEIV2_CYCLE0_SNAP0_CYCLE0_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE0_SNAP0_CYCLE0_SNAP0_SHIFT (0U)
#define QEIV2_CYCLE0_SNAP0_CYCLE0_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_CYCLE0_SNAP0_CYCLE0_SNAP0_MASK) >> QEIV2_CYCLE0_SNAP0_CYCLE0_SNAP0_SHIFT)

/* Bitfield definition for register: CYCLE0_SNAP1 */
/*
 * CYCLE0_SNAP1 (RO)
 *
 */
#define QEIV2_CYCLE0_SNAP1_CYCLE0_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE0_SNAP1_CYCLE0_SNAP1_SHIFT (0U)
#define QEIV2_CYCLE0_SNAP1_CYCLE0_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_CYCLE0_SNAP1_CYCLE0_SNAP1_MASK) >> QEIV2_CYCLE0_SNAP1_CYCLE0_SNAP1_SHIFT)

/* Bitfield definition for register: CYCLE1_SNAP0 */
/*
 * CYCLE1_SNAP0 (RO)
 *
 */
#define QEIV2_CYCLE1_SNAP0_CYCLE1_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE1_SNAP0_CYCLE1_SNAP0_SHIFT (0U)
#define QEIV2_CYCLE1_SNAP0_CYCLE1_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_CYCLE1_SNAP0_CYCLE1_SNAP0_MASK) >> QEIV2_CYCLE1_SNAP0_CYCLE1_SNAP0_SHIFT)

/* Bitfield definition for register: CYCLE1_SNAP1 */
/*
 * CYCLE1_SNAP1 (RO)
 *
 */
#define QEIV2_CYCLE1_SNAP1_CYCLE1_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE1_SNAP1_CYCLE1_SNAP1_SHIFT (0U)
#define QEIV2_CYCLE1_SNAP1_CYCLE1_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_CYCLE1_SNAP1_CYCLE1_SNAP1_MASK) >> QEIV2_CYCLE1_SNAP1_CYCLE1_SNAP1_SHIFT)

/* Bitfield definition for register: CYCLE0_NUM */
/*
 * CYCLE0_NUM (RW)
 *
 */
#define QEIV2_CYCLE0_NUM_CYCLE0_NUM_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE0_NUM_CYCLE0_NUM_SHIFT (0U)
#define QEIV2_CYCLE0_NUM_CYCLE0_NUM_SET(x) (((uint32_t)(x) << QEIV2_CYCLE0_NUM_CYCLE0_NUM_SHIFT) & QEIV2_CYCLE0_NUM_CYCLE0_NUM_MASK)
#define QEIV2_CYCLE0_NUM_CYCLE0_NUM_GET(x) (((uint32_t)(x) & QEIV2_CYCLE0_NUM_CYCLE0_NUM_MASK) >> QEIV2_CYCLE0_NUM_CYCLE0_NUM_SHIFT)

/* Bitfield definition for register: CYCLE1_NUM */
/*
 * CYCLE1_NUM (RW)
 *
 */
#define QEIV2_CYCLE1_NUM_CYCLE1_NUM_MASK (0xFFFFFFFFUL)
#define QEIV2_CYCLE1_NUM_CYCLE1_NUM_SHIFT (0U)
#define QEIV2_CYCLE1_NUM_CYCLE1_NUM_SET(x) (((uint32_t)(x) << QEIV2_CYCLE1_NUM_CYCLE1_NUM_SHIFT) & QEIV2_CYCLE1_NUM_CYCLE1_NUM_MASK)
#define QEIV2_CYCLE1_NUM_CYCLE1_NUM_GET(x) (((uint32_t)(x) & QEIV2_CYCLE1_NUM_CYCLE1_NUM_MASK) >> QEIV2_CYCLE1_NUM_CYCLE1_NUM_SHIFT)

/* Bitfield definition for register: PULSE0_CNT */
/*
 * PULSE0_CNT (RO)
 *
 */
#define QEIV2_PULSE0_CNT_PULSE0_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0_CNT_PULSE0_CNT_SHIFT (0U)
#define QEIV2_PULSE0_CNT_PULSE0_CNT_GET(x) (((uint32_t)(x) & QEIV2_PULSE0_CNT_PULSE0_CNT_MASK) >> QEIV2_PULSE0_CNT_PULSE0_CNT_SHIFT)

/* Bitfield definition for register: PULSE0CYCLE_CNT */
/*
 * PULSE0CYCLE_CNT (RO)
 *
 */
#define QEIV2_PULSE0CYCLE_CNT_PULSE0CYCLE_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0CYCLE_CNT_PULSE0CYCLE_CNT_SHIFT (0U)
#define QEIV2_PULSE0CYCLE_CNT_PULSE0CYCLE_CNT_GET(x) (((uint32_t)(x) & QEIV2_PULSE0CYCLE_CNT_PULSE0CYCLE_CNT_MASK) >> QEIV2_PULSE0CYCLE_CNT_PULSE0CYCLE_CNT_SHIFT)

/* Bitfield definition for register: PULSE1_CNT */
/*
 * PULSE1_CNT (RO)
 *
 */
#define QEIV2_PULSE1_CNT_PULSE1_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1_CNT_PULSE1_CNT_SHIFT (0U)
#define QEIV2_PULSE1_CNT_PULSE1_CNT_GET(x) (((uint32_t)(x) & QEIV2_PULSE1_CNT_PULSE1_CNT_MASK) >> QEIV2_PULSE1_CNT_PULSE1_CNT_SHIFT)

/* Bitfield definition for register: PULSE1CYCLE_CNT */
/*
 * PULSE1CYCLE_CNT (RO)
 *
 */
#define QEIV2_PULSE1CYCLE_CNT_PULSE1CYCLE_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1CYCLE_CNT_PULSE1CYCLE_CNT_SHIFT (0U)
#define QEIV2_PULSE1CYCLE_CNT_PULSE1CYCLE_CNT_GET(x) (((uint32_t)(x) & QEIV2_PULSE1CYCLE_CNT_PULSE1CYCLE_CNT_MASK) >> QEIV2_PULSE1CYCLE_CNT_PULSE1CYCLE_CNT_SHIFT)

/* Bitfield definition for register: PULSE0_SNAP0 */
/*
 * PULSE0_SNAP0 (RO)
 *
 */
#define QEIV2_PULSE0_SNAP0_PULSE0_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0_SNAP0_PULSE0_SNAP0_SHIFT (0U)
#define QEIV2_PULSE0_SNAP0_PULSE0_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_PULSE0_SNAP0_PULSE0_SNAP0_MASK) >> QEIV2_PULSE0_SNAP0_PULSE0_SNAP0_SHIFT)

/* Bitfield definition for register: PULSE0CYCLE_SNAP0 */
/*
 * PULSE0CYCLE_SNAP0 (RO)
 *
 */
#define QEIV2_PULSE0CYCLE_SNAP0_PULSE0CYCLE_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0CYCLE_SNAP0_PULSE0CYCLE_SNAP0_SHIFT (0U)
#define QEIV2_PULSE0CYCLE_SNAP0_PULSE0CYCLE_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_PULSE0CYCLE_SNAP0_PULSE0CYCLE_SNAP0_MASK) >> QEIV2_PULSE0CYCLE_SNAP0_PULSE0CYCLE_SNAP0_SHIFT)

/* Bitfield definition for register: PULSE0_SNAP1 */
/*
 * PULSE0_SNAP1 (RO)
 *
 */
#define QEIV2_PULSE0_SNAP1_PULSE0_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0_SNAP1_PULSE0_SNAP1_SHIFT (0U)
#define QEIV2_PULSE0_SNAP1_PULSE0_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_PULSE0_SNAP1_PULSE0_SNAP1_MASK) >> QEIV2_PULSE0_SNAP1_PULSE0_SNAP1_SHIFT)

/* Bitfield definition for register: PULSE0CYCLE_SNAP1 */
/*
 * PULSE0CYCLE_SNAP1 (RO)
 *
 */
#define QEIV2_PULSE0CYCLE_SNAP1_PULSE0CYCLE_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE0CYCLE_SNAP1_PULSE0CYCLE_SNAP1_SHIFT (0U)
#define QEIV2_PULSE0CYCLE_SNAP1_PULSE0CYCLE_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_PULSE0CYCLE_SNAP1_PULSE0CYCLE_SNAP1_MASK) >> QEIV2_PULSE0CYCLE_SNAP1_PULSE0CYCLE_SNAP1_SHIFT)

/* Bitfield definition for register: PULSE1_SNAP0 */
/*
 * PULSE1_SNAP0 (RO)
 *
 */
#define QEIV2_PULSE1_SNAP0_PULSE1_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1_SNAP0_PULSE1_SNAP0_SHIFT (0U)
#define QEIV2_PULSE1_SNAP0_PULSE1_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_PULSE1_SNAP0_PULSE1_SNAP0_MASK) >> QEIV2_PULSE1_SNAP0_PULSE1_SNAP0_SHIFT)

/* Bitfield definition for register: PULSE1CYCLE_SNAP0 */
/*
 * PULSE1CYCLE_SNAP0 (RO)
 *
 */
#define QEIV2_PULSE1CYCLE_SNAP0_PULSE1CYCLE_SNAP0_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1CYCLE_SNAP0_PULSE1CYCLE_SNAP0_SHIFT (0U)
#define QEIV2_PULSE1CYCLE_SNAP0_PULSE1CYCLE_SNAP0_GET(x) (((uint32_t)(x) & QEIV2_PULSE1CYCLE_SNAP0_PULSE1CYCLE_SNAP0_MASK) >> QEIV2_PULSE1CYCLE_SNAP0_PULSE1CYCLE_SNAP0_SHIFT)

/* Bitfield definition for register: PULSE1_SNAP1 */
/*
 * PULSE1_SNAP1 (RO)
 *
 */
#define QEIV2_PULSE1_SNAP1_PULSE1_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1_SNAP1_PULSE1_SNAP1_SHIFT (0U)
#define QEIV2_PULSE1_SNAP1_PULSE1_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_PULSE1_SNAP1_PULSE1_SNAP1_MASK) >> QEIV2_PULSE1_SNAP1_PULSE1_SNAP1_SHIFT)

/* Bitfield definition for register: PULSE1CYCLE_SNAP1 */
/*
 * PULSE1CYCLE_SNAP1 (RO)
 *
 */
#define QEIV2_PULSE1CYCLE_SNAP1_PULSE1CYCLE_SNAP1_MASK (0xFFFFFFFFUL)
#define QEIV2_PULSE1CYCLE_SNAP1_PULSE1CYCLE_SNAP1_SHIFT (0U)
#define QEIV2_PULSE1CYCLE_SNAP1_PULSE1CYCLE_SNAP1_GET(x) (((uint32_t)(x) & QEIV2_PULSE1CYCLE_SNAP1_PULSE1CYCLE_SNAP1_MASK) >> QEIV2_PULSE1CYCLE_SNAP1_PULSE1CYCLE_SNAP1_SHIFT)

/* Bitfield definition for register: ADCX_CFG0 */
/*
 * X_ADCSEL (RW)
 *
 */
#define QEIV2_ADCX_CFG0_X_ADCSEL_MASK (0x100U)
#define QEIV2_ADCX_CFG0_X_ADCSEL_SHIFT (8U)
#define QEIV2_ADCX_CFG0_X_ADCSEL_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG0_X_ADCSEL_SHIFT) & QEIV2_ADCX_CFG0_X_ADCSEL_MASK)
#define QEIV2_ADCX_CFG0_X_ADCSEL_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG0_X_ADCSEL_MASK) >> QEIV2_ADCX_CFG0_X_ADCSEL_SHIFT)

/*
 * X_ADC_ENABLE (RW)
 *
 */
#define QEIV2_ADCX_CFG0_X_ADC_ENABLE_MASK (0x80U)
#define QEIV2_ADCX_CFG0_X_ADC_ENABLE_SHIFT (7U)
#define QEIV2_ADCX_CFG0_X_ADC_ENABLE_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG0_X_ADC_ENABLE_SHIFT) & QEIV2_ADCX_CFG0_X_ADC_ENABLE_MASK)
#define QEIV2_ADCX_CFG0_X_ADC_ENABLE_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG0_X_ADC_ENABLE_MASK) >> QEIV2_ADCX_CFG0_X_ADC_ENABLE_SHIFT)

/*
 * X_CHAN (RW)
 *
 */
#define QEIV2_ADCX_CFG0_X_CHAN_MASK (0x1FU)
#define QEIV2_ADCX_CFG0_X_CHAN_SHIFT (0U)
#define QEIV2_ADCX_CFG0_X_CHAN_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG0_X_CHAN_SHIFT) & QEIV2_ADCX_CFG0_X_CHAN_MASK)
#define QEIV2_ADCX_CFG0_X_CHAN_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG0_X_CHAN_MASK) >> QEIV2_ADCX_CFG0_X_CHAN_SHIFT)

/* Bitfield definition for register: ADCX_CFG1 */
/*
 * X_PARAM1 (RW)
 *
 */
#define QEIV2_ADCX_CFG1_X_PARAM1_MASK (0xFFFF0000UL)
#define QEIV2_ADCX_CFG1_X_PARAM1_SHIFT (16U)
#define QEIV2_ADCX_CFG1_X_PARAM1_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG1_X_PARAM1_SHIFT) & QEIV2_ADCX_CFG1_X_PARAM1_MASK)
#define QEIV2_ADCX_CFG1_X_PARAM1_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG1_X_PARAM1_MASK) >> QEIV2_ADCX_CFG1_X_PARAM1_SHIFT)

/*
 * X_PARAM0 (RW)
 *
 */
#define QEIV2_ADCX_CFG1_X_PARAM0_MASK (0xFFFFU)
#define QEIV2_ADCX_CFG1_X_PARAM0_SHIFT (0U)
#define QEIV2_ADCX_CFG1_X_PARAM0_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG1_X_PARAM0_SHIFT) & QEIV2_ADCX_CFG1_X_PARAM0_MASK)
#define QEIV2_ADCX_CFG1_X_PARAM0_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG1_X_PARAM0_MASK) >> QEIV2_ADCX_CFG1_X_PARAM0_SHIFT)

/* Bitfield definition for register: ADCX_CFG2 */
/*
 * X_OFFSET (RW)
 *
 */
#define QEIV2_ADCX_CFG2_X_OFFSET_MASK (0xFFFFFFFFUL)
#define QEIV2_ADCX_CFG2_X_OFFSET_SHIFT (0U)
#define QEIV2_ADCX_CFG2_X_OFFSET_SET(x) (((uint32_t)(x) << QEIV2_ADCX_CFG2_X_OFFSET_SHIFT) & QEIV2_ADCX_CFG2_X_OFFSET_MASK)
#define QEIV2_ADCX_CFG2_X_OFFSET_GET(x) (((uint32_t)(x) & QEIV2_ADCX_CFG2_X_OFFSET_MASK) >> QEIV2_ADCX_CFG2_X_OFFSET_SHIFT)

/* Bitfield definition for register: ADCY_CFG0 */
/*
 * Y_ADCSEL (RW)
 *
 */
#define QEIV2_ADCY_CFG0_Y_ADCSEL_MASK (0x100U)
#define QEIV2_ADCY_CFG0_Y_ADCSEL_SHIFT (8U)
#define QEIV2_ADCY_CFG0_Y_ADCSEL_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG0_Y_ADCSEL_SHIFT) & QEIV2_ADCY_CFG0_Y_ADCSEL_MASK)
#define QEIV2_ADCY_CFG0_Y_ADCSEL_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG0_Y_ADCSEL_MASK) >> QEIV2_ADCY_CFG0_Y_ADCSEL_SHIFT)

/*
 * Y_ADC_ENABLE (RW)
 *
 */
#define QEIV2_ADCY_CFG0_Y_ADC_ENABLE_MASK (0x80U)
#define QEIV2_ADCY_CFG0_Y_ADC_ENABLE_SHIFT (7U)
#define QEIV2_ADCY_CFG0_Y_ADC_ENABLE_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG0_Y_ADC_ENABLE_SHIFT) & QEIV2_ADCY_CFG0_Y_ADC_ENABLE_MASK)
#define QEIV2_ADCY_CFG0_Y_ADC_ENABLE_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG0_Y_ADC_ENABLE_MASK) >> QEIV2_ADCY_CFG0_Y_ADC_ENABLE_SHIFT)

/*
 * Y_CHAN (RW)
 *
 */
#define QEIV2_ADCY_CFG0_Y_CHAN_MASK (0x1FU)
#define QEIV2_ADCY_CFG0_Y_CHAN_SHIFT (0U)
#define QEIV2_ADCY_CFG0_Y_CHAN_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG0_Y_CHAN_SHIFT) & QEIV2_ADCY_CFG0_Y_CHAN_MASK)
#define QEIV2_ADCY_CFG0_Y_CHAN_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG0_Y_CHAN_MASK) >> QEIV2_ADCY_CFG0_Y_CHAN_SHIFT)

/* Bitfield definition for register: ADCY_CFG1 */
/*
 * Y_PARAM1 (RW)
 *
 */
#define QEIV2_ADCY_CFG1_Y_PARAM1_MASK (0xFFFF0000UL)
#define QEIV2_ADCY_CFG1_Y_PARAM1_SHIFT (16U)
#define QEIV2_ADCY_CFG1_Y_PARAM1_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG1_Y_PARAM1_SHIFT) & QEIV2_ADCY_CFG1_Y_PARAM1_MASK)
#define QEIV2_ADCY_CFG1_Y_PARAM1_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG1_Y_PARAM1_MASK) >> QEIV2_ADCY_CFG1_Y_PARAM1_SHIFT)

/*
 * Y_PARAM0 (RW)
 *
 */
#define QEIV2_ADCY_CFG1_Y_PARAM0_MASK (0xFFFFU)
#define QEIV2_ADCY_CFG1_Y_PARAM0_SHIFT (0U)
#define QEIV2_ADCY_CFG1_Y_PARAM0_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG1_Y_PARAM0_SHIFT) & QEIV2_ADCY_CFG1_Y_PARAM0_MASK)
#define QEIV2_ADCY_CFG1_Y_PARAM0_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG1_Y_PARAM0_MASK) >> QEIV2_ADCY_CFG1_Y_PARAM0_SHIFT)

/* Bitfield definition for register: ADCY_CFG2 */
/*
 * Y_OFFSET (RW)
 *
 */
#define QEIV2_ADCY_CFG2_Y_OFFSET_MASK (0xFFFFFFFFUL)
#define QEIV2_ADCY_CFG2_Y_OFFSET_SHIFT (0U)
#define QEIV2_ADCY_CFG2_Y_OFFSET_SET(x) (((uint32_t)(x) << QEIV2_ADCY_CFG2_Y_OFFSET_SHIFT) & QEIV2_ADCY_CFG2_Y_OFFSET_MASK)
#define QEIV2_ADCY_CFG2_Y_OFFSET_GET(x) (((uint32_t)(x) & QEIV2_ADCY_CFG2_Y_OFFSET_MASK) >> QEIV2_ADCY_CFG2_Y_OFFSET_SHIFT)

/* Bitfield definition for register: CAL_CFG */
/*
 * XY_DELAY (RW)
 *
 * valid x/y delay, larger than this delay will be treated as invalid data.
 * Default 1.25us@200MHz;   max 80ms;
 */
#define QEIV2_CAL_CFG_XY_DELAY_MASK (0xFFFFFFUL)
#define QEIV2_CAL_CFG_XY_DELAY_SHIFT (0U)
#define QEIV2_CAL_CFG_XY_DELAY_SET(x) (((uint32_t)(x) << QEIV2_CAL_CFG_XY_DELAY_SHIFT) & QEIV2_CAL_CFG_XY_DELAY_MASK)
#define QEIV2_CAL_CFG_XY_DELAY_GET(x) (((uint32_t)(x) & QEIV2_CAL_CFG_XY_DELAY_MASK) >> QEIV2_CAL_CFG_XY_DELAY_SHIFT)

/* Bitfield definition for register: PHASE_PARAM */
/*
 * PHASE_PARAM (RW)
 *
 */
#define QEIV2_PHASE_PARAM_PHASE_PARAM_MASK (0xFFFFFFFFUL)
#define QEIV2_PHASE_PARAM_PHASE_PARAM_SHIFT (0U)
#define QEIV2_PHASE_PARAM_PHASE_PARAM_SET(x) (((uint32_t)(x) << QEIV2_PHASE_PARAM_PHASE_PARAM_SHIFT) & QEIV2_PHASE_PARAM_PHASE_PARAM_MASK)
#define QEIV2_PHASE_PARAM_PHASE_PARAM_GET(x) (((uint32_t)(x) & QEIV2_PHASE_PARAM_PHASE_PARAM_MASK) >> QEIV2_PHASE_PARAM_PHASE_PARAM_SHIFT)

/* Bitfield definition for register: POS_THRESHOLD */
/*
 * POS_THRESHOLD (RW)
 *
 */
#define QEIV2_POS_THRESHOLD_POS_THRESHOLD_MASK (0xFFFFFFFFUL)
#define QEIV2_POS_THRESHOLD_POS_THRESHOLD_SHIFT (0U)
#define QEIV2_POS_THRESHOLD_POS_THRESHOLD_SET(x) (((uint32_t)(x) << QEIV2_POS_THRESHOLD_POS_THRESHOLD_SHIFT) & QEIV2_POS_THRESHOLD_POS_THRESHOLD_MASK)
#define QEIV2_POS_THRESHOLD_POS_THRESHOLD_GET(x) (((uint32_t)(x) & QEIV2_POS_THRESHOLD_POS_THRESHOLD_MASK) >> QEIV2_POS_THRESHOLD_POS_THRESHOLD_SHIFT)

/* Bitfield definition for register array: UVW_POS */
/*
 * UVW_POS0 (RW)
 *
 */
#define QEIV2_UVW_POS_UVW_POS0_MASK (0xFFFFFFFFUL)
#define QEIV2_UVW_POS_UVW_POS0_SHIFT (0U)
#define QEIV2_UVW_POS_UVW_POS0_SET(x) (((uint32_t)(x) << QEIV2_UVW_POS_UVW_POS0_SHIFT) & QEIV2_UVW_POS_UVW_POS0_MASK)
#define QEIV2_UVW_POS_UVW_POS0_GET(x) (((uint32_t)(x) & QEIV2_UVW_POS_UVW_POS0_MASK) >> QEIV2_UVW_POS_UVW_POS0_SHIFT)

/* Bitfield definition for register array: UVW_POS_CFG */
/*
 * POS_EN (RW)
 *
 */
#define QEIV2_UVW_POS_CFG_POS_EN_MASK (0x40U)
#define QEIV2_UVW_POS_CFG_POS_EN_SHIFT (6U)
#define QEIV2_UVW_POS_CFG_POS_EN_SET(x) (((uint32_t)(x) << QEIV2_UVW_POS_CFG_POS_EN_SHIFT) & QEIV2_UVW_POS_CFG_POS_EN_MASK)
#define QEIV2_UVW_POS_CFG_POS_EN_GET(x) (((uint32_t)(x) & QEIV2_UVW_POS_CFG_POS_EN_MASK) >> QEIV2_UVW_POS_CFG_POS_EN_SHIFT)

/*
 * U_POS_SEL (RW)
 *
 */
#define QEIV2_UVW_POS_CFG_U_POS_SEL_MASK (0x30U)
#define QEIV2_UVW_POS_CFG_U_POS_SEL_SHIFT (4U)
#define QEIV2_UVW_POS_CFG_U_POS_SEL_SET(x) (((uint32_t)(x) << QEIV2_UVW_POS_CFG_U_POS_SEL_SHIFT) & QEIV2_UVW_POS_CFG_U_POS_SEL_MASK)
#define QEIV2_UVW_POS_CFG_U_POS_SEL_GET(x) (((uint32_t)(x) & QEIV2_UVW_POS_CFG_U_POS_SEL_MASK) >> QEIV2_UVW_POS_CFG_U_POS_SEL_SHIFT)

/*
 * V_POS_SEL (RW)
 *
 */
#define QEIV2_UVW_POS_CFG_V_POS_SEL_MASK (0xCU)
#define QEIV2_UVW_POS_CFG_V_POS_SEL_SHIFT (2U)
#define QEIV2_UVW_POS_CFG_V_POS_SEL_SET(x) (((uint32_t)(x) << QEIV2_UVW_POS_CFG_V_POS_SEL_SHIFT) & QEIV2_UVW_POS_CFG_V_POS_SEL_MASK)
#define QEIV2_UVW_POS_CFG_V_POS_SEL_GET(x) (((uint32_t)(x) & QEIV2_UVW_POS_CFG_V_POS_SEL_MASK) >> QEIV2_UVW_POS_CFG_V_POS_SEL_SHIFT)

/*
 * W_POS_SEL (RW)
 *
 */
#define QEIV2_UVW_POS_CFG_W_POS_SEL_MASK (0x3U)
#define QEIV2_UVW_POS_CFG_W_POS_SEL_SHIFT (0U)
#define QEIV2_UVW_POS_CFG_W_POS_SEL_SET(x) (((uint32_t)(x) << QEIV2_UVW_POS_CFG_W_POS_SEL_SHIFT) & QEIV2_UVW_POS_CFG_W_POS_SEL_MASK)
#define QEIV2_UVW_POS_CFG_W_POS_SEL_GET(x) (((uint32_t)(x) & QEIV2_UVW_POS_CFG_W_POS_SEL_MASK) >> QEIV2_UVW_POS_CFG_W_POS_SEL_SHIFT)

/* Bitfield definition for register: PHASE_CNT */
/*
 * PHASE_CNT (RW)
 *
 */
#define QEIV2_PHASE_CNT_PHASE_CNT_MASK (0xFFFFFFFFUL)
#define QEIV2_PHASE_CNT_PHASE_CNT_SHIFT (0U)
#define QEIV2_PHASE_CNT_PHASE_CNT_SET(x) (((uint32_t)(x) << QEIV2_PHASE_CNT_PHASE_CNT_SHIFT) & QEIV2_PHASE_CNT_PHASE_CNT_MASK)
#define QEIV2_PHASE_CNT_PHASE_CNT_GET(x) (((uint32_t)(x) & QEIV2_PHASE_CNT_PHASE_CNT_MASK) >> QEIV2_PHASE_CNT_PHASE_CNT_SHIFT)

/* Bitfield definition for register: PHASE_UPDATE */
/*
 * INC (WO)
 *
 * set to add value to phase_cnt
 */
#define QEIV2_PHASE_UPDATE_INC_MASK (0x80000000UL)
#define QEIV2_PHASE_UPDATE_INC_SHIFT (31U)
#define QEIV2_PHASE_UPDATE_INC_SET(x) (((uint32_t)(x) << QEIV2_PHASE_UPDATE_INC_SHIFT) & QEIV2_PHASE_UPDATE_INC_MASK)
#define QEIV2_PHASE_UPDATE_INC_GET(x) (((uint32_t)(x) & QEIV2_PHASE_UPDATE_INC_MASK) >> QEIV2_PHASE_UPDATE_INC_SHIFT)

/*
 * DEC (WO)
 *
 * set to minus value from phase_cnt(set inc and dec same time willl act inc)
 */
#define QEIV2_PHASE_UPDATE_DEC_MASK (0x40000000UL)
#define QEIV2_PHASE_UPDATE_DEC_SHIFT (30U)
#define QEIV2_PHASE_UPDATE_DEC_SET(x) (((uint32_t)(x) << QEIV2_PHASE_UPDATE_DEC_SHIFT) & QEIV2_PHASE_UPDATE_DEC_MASK)
#define QEIV2_PHASE_UPDATE_DEC_GET(x) (((uint32_t)(x) & QEIV2_PHASE_UPDATE_DEC_MASK) >> QEIV2_PHASE_UPDATE_DEC_SHIFT)

/*
 * VALUE (WO)
 *
 * value to be added or minus from phase_cnt. only valid when inc or dec is set in one 32bit write operation
 */
#define QEIV2_PHASE_UPDATE_VALUE_MASK (0x3FFFFFFFUL)
#define QEIV2_PHASE_UPDATE_VALUE_SHIFT (0U)
#define QEIV2_PHASE_UPDATE_VALUE_SET(x) (((uint32_t)(x) << QEIV2_PHASE_UPDATE_VALUE_SHIFT) & QEIV2_PHASE_UPDATE_VALUE_MASK)
#define QEIV2_PHASE_UPDATE_VALUE_GET(x) (((uint32_t)(x) & QEIV2_PHASE_UPDATE_VALUE_MASK) >> QEIV2_PHASE_UPDATE_VALUE_SHIFT)

/* Bitfield definition for register: POSITION */
/*
 * POSITION (RW)
 *
 */
#define QEIV2_POSITION_POSITION_MASK (0xFFFFFFFFUL)
#define QEIV2_POSITION_POSITION_SHIFT (0U)
#define QEIV2_POSITION_POSITION_SET(x) (((uint32_t)(x) << QEIV2_POSITION_POSITION_SHIFT) & QEIV2_POSITION_POSITION_MASK)
#define QEIV2_POSITION_POSITION_GET(x) (((uint32_t)(x) & QEIV2_POSITION_POSITION_MASK) >> QEIV2_POSITION_POSITION_SHIFT)

/* Bitfield definition for register: POSITION_UPDATE */
/*
 * INC (WO)
 *
 * set to add value to position
 */
#define QEIV2_POSITION_UPDATE_INC_MASK (0x80000000UL)
#define QEIV2_POSITION_UPDATE_INC_SHIFT (31U)
#define QEIV2_POSITION_UPDATE_INC_SET(x) (((uint32_t)(x) << QEIV2_POSITION_UPDATE_INC_SHIFT) & QEIV2_POSITION_UPDATE_INC_MASK)
#define QEIV2_POSITION_UPDATE_INC_GET(x) (((uint32_t)(x) & QEIV2_POSITION_UPDATE_INC_MASK) >> QEIV2_POSITION_UPDATE_INC_SHIFT)

/*
 * DEC (WO)
 *
 * set to minus value from position(set inc and dec same time willl act inc)
 */
#define QEIV2_POSITION_UPDATE_DEC_MASK (0x40000000UL)
#define QEIV2_POSITION_UPDATE_DEC_SHIFT (30U)
#define QEIV2_POSITION_UPDATE_DEC_SET(x) (((uint32_t)(x) << QEIV2_POSITION_UPDATE_DEC_SHIFT) & QEIV2_POSITION_UPDATE_DEC_MASK)
#define QEIV2_POSITION_UPDATE_DEC_GET(x) (((uint32_t)(x) & QEIV2_POSITION_UPDATE_DEC_MASK) >> QEIV2_POSITION_UPDATE_DEC_SHIFT)

/*
 * VALUE (WO)
 *
 * value to be added or minus from position. only valid when inc or dec is set in one 32bit write operation
 */
#define QEIV2_POSITION_UPDATE_VALUE_MASK (0x3FFFFFFFUL)
#define QEIV2_POSITION_UPDATE_VALUE_SHIFT (0U)
#define QEIV2_POSITION_UPDATE_VALUE_SET(x) (((uint32_t)(x) << QEIV2_POSITION_UPDATE_VALUE_SHIFT) & QEIV2_POSITION_UPDATE_VALUE_MASK)
#define QEIV2_POSITION_UPDATE_VALUE_GET(x) (((uint32_t)(x) & QEIV2_POSITION_UPDATE_VALUE_MASK) >> QEIV2_POSITION_UPDATE_VALUE_SHIFT)

/* Bitfield definition for register: ANGLE */
/*
 * ANGLE (RO)
 *
 */
#define QEIV2_ANGLE_ANGLE_MASK (0xFFFFFFFFUL)
#define QEIV2_ANGLE_ANGLE_SHIFT (0U)
#define QEIV2_ANGLE_ANGLE_GET(x) (((uint32_t)(x) & QEIV2_ANGLE_ANGLE_MASK) >> QEIV2_ANGLE_ANGLE_SHIFT)

/* Bitfield definition for register: POS_TIMEOUT */
/*
 * ENABLE (RW)
 *
 * enable position timeout feature, if timeout, send valid again
 */
#define QEIV2_POS_TIMEOUT_ENABLE_MASK (0x80000000UL)
#define QEIV2_POS_TIMEOUT_ENABLE_SHIFT (31U)
#define QEIV2_POS_TIMEOUT_ENABLE_SET(x) (((uint32_t)(x) << QEIV2_POS_TIMEOUT_ENABLE_SHIFT) & QEIV2_POS_TIMEOUT_ENABLE_MASK)
#define QEIV2_POS_TIMEOUT_ENABLE_GET(x) (((uint32_t)(x) & QEIV2_POS_TIMEOUT_ENABLE_MASK) >> QEIV2_POS_TIMEOUT_ENABLE_SHIFT)

/*
 * TIMEOUT (RW)
 *
 * postion timeout value
 */
#define QEIV2_POS_TIMEOUT_TIMEOUT_MASK (0x7FFFFFFFUL)
#define QEIV2_POS_TIMEOUT_TIMEOUT_SHIFT (0U)
#define QEIV2_POS_TIMEOUT_TIMEOUT_SET(x) (((uint32_t)(x) << QEIV2_POS_TIMEOUT_TIMEOUT_SHIFT) & QEIV2_POS_TIMEOUT_TIMEOUT_MASK)
#define QEIV2_POS_TIMEOUT_TIMEOUT_GET(x) (((uint32_t)(x) & QEIV2_POS_TIMEOUT_TIMEOUT_MASK) >> QEIV2_POS_TIMEOUT_TIMEOUT_SHIFT)



/* COUNT register group index macro definition */
#define QEIV2_COUNT_CURRENT (0UL)
#define QEIV2_COUNT_READ (1UL)
#define QEIV2_COUNT_SNAP0 (2UL)
#define QEIV2_COUNT_SNAP1 (3UL)

/* FILT_CFG register group index macro definition */
#define QEIV2_FILT_CFG_FILT_CFG_A (0UL)
#define QEIV2_FILT_CFG_FILT_CFG_B (1UL)
#define QEIV2_FILT_CFG_FILT_CFG_Z (2UL)
#define QEIV2_FILT_CFG_FILT_CFG_H (3UL)
#define QEIV2_FILT_CFG_FILT_CFG_H2 (4UL)
#define QEIV2_FILT_CFG_FILT_CFG_F (5UL)

/* UVW_POS register group index macro definition */
#define QEIV2_UVW_POS_UVW_POS0 (0UL)
#define QEIV2_UVW_POS_UVW_POS1 (1UL)
#define QEIV2_UVW_POS_UVW_POS2 (2UL)
#define QEIV2_UVW_POS_UVW_POS3 (3UL)
#define QEIV2_UVW_POS_UVW_POS4 (4UL)
#define QEIV2_UVW_POS_UVW_POS5 (5UL)

/* UVW_POS_CFG register group index macro definition */
#define QEIV2_UVW_POS_CFG_UVW_POS0_CFG (0UL)
#define QEIV2_UVW_POS_CFG_UVW_POS1_CFG (1UL)
#define QEIV2_UVW_POS_CFG_UVW_POS2_CFG (2UL)
#define QEIV2_UVW_POS_CFG_UVW_POS3_CFG (3UL)
#define QEIV2_UVW_POS_CFG_UVW_POS4_CFG (4UL)
#define QEIV2_UVW_POS_CFG_UVW_POS5_CFG (5UL)


#endif /* HPM_QEIV2_H */

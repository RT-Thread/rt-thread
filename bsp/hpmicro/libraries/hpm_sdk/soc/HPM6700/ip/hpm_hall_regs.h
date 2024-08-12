/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_HALL_H
#define HPM_HALL_H

typedef struct {
    __RW uint32_t CR;                          /* 0x0: Control Register */
    __RW uint32_t PHCFG;                       /* 0x4: Phase configure register */
    __RW uint32_t WDGCFG;                      /* 0x8: Watchdog configure register */
    __RW uint32_t UVWCFG;                      /* 0xC: U,V,W configure register */
    __RW uint32_t TRGOEN;                      /* 0x10: Trigger output enable register */
    __RW uint32_t READEN;                      /* 0x14: Read event enable register */
    __R  uint8_t  RESERVED0[12];               /* 0x18 - 0x23: Reserved */
    __RW uint32_t DMAEN;                       /* 0x24: DMA enable register */
    __RW uint32_t SR;                          /* 0x28: Status register */
    __RW uint32_t IRQEN;                       /* 0x2C: Interrupt request enable register */
    struct {
        __R  uint32_t W;                       /* 0x30: W counter */
        __R  uint32_t V;                       /* 0x34: V counter */
        __R  uint32_t U;                       /* 0x38: U counter */
        __R  uint32_t TMR;                     /* 0x3C: Timer counter */
    } COUNT[4];
    struct {
        __R  uint32_t HIS0;                    /* 0x70: history register 0 */
        __R  uint32_t HIS1;                    /* 0x74: history register 1 */
    } HIS[3];
} HALL_Type;


/* Bitfield definition for register: CR */
/*
 * READ (WO)
 *
 * 1- load ucnt, vcnt, wcnt and tmrcnt into their read registers. Hardware auto-clear; read as 0
 */
#define HALL_CR_READ_MASK (0x80000000UL)
#define HALL_CR_READ_SHIFT (31U)
#define HALL_CR_READ_SET(x) (((uint32_t)(x) << HALL_CR_READ_SHIFT) & HALL_CR_READ_MASK)
#define HALL_CR_READ_GET(x) (((uint32_t)(x) & HALL_CR_READ_MASK) >> HALL_CR_READ_SHIFT)

/*
 * SNAPEN (RW)
 *
 * 1- load ucnt, vcnt, wcnt and tmrcnt into their snap registers when snapi input assert
 */
#define HALL_CR_SNAPEN_MASK (0x800U)
#define HALL_CR_SNAPEN_SHIFT (11U)
#define HALL_CR_SNAPEN_SET(x) (((uint32_t)(x) << HALL_CR_SNAPEN_SHIFT) & HALL_CR_SNAPEN_MASK)
#define HALL_CR_SNAPEN_GET(x) (((uint32_t)(x) & HALL_CR_SNAPEN_MASK) >> HALL_CR_SNAPEN_SHIFT)

/*
 * RSTCNT (RW)
 *
 * set to reset all counter and related snapshots
 */
#define HALL_CR_RSTCNT_MASK (0x10U)
#define HALL_CR_RSTCNT_SHIFT (4U)
#define HALL_CR_RSTCNT_SET(x) (((uint32_t)(x) << HALL_CR_RSTCNT_SHIFT) & HALL_CR_RSTCNT_MASK)
#define HALL_CR_RSTCNT_GET(x) (((uint32_t)(x) & HALL_CR_RSTCNT_MASK) >> HALL_CR_RSTCNT_SHIFT)

/* Bitfield definition for register: PHCFG */
/*
 * DLYSEL (RW)
 *
 * This bit select delay start time:
 * 1- start counting delay after pre-trigger
 * 0- start counting delay after u,v,w toggle
 */
#define HALL_PHCFG_DLYSEL_MASK (0x80000000UL)
#define HALL_PHCFG_DLYSEL_SHIFT (31U)
#define HALL_PHCFG_DLYSEL_SET(x) (((uint32_t)(x) << HALL_PHCFG_DLYSEL_SHIFT) & HALL_PHCFG_DLYSEL_MASK)
#define HALL_PHCFG_DLYSEL_GET(x) (((uint32_t)(x) & HALL_PHCFG_DLYSEL_MASK) >> HALL_PHCFG_DLYSEL_SHIFT)

/*
 * DLYCNT (RW)
 *
 * delay clock cycles number
 */
#define HALL_PHCFG_DLYCNT_MASK (0xFFFFFFUL)
#define HALL_PHCFG_DLYCNT_SHIFT (0U)
#define HALL_PHCFG_DLYCNT_SET(x) (((uint32_t)(x) << HALL_PHCFG_DLYCNT_SHIFT) & HALL_PHCFG_DLYCNT_MASK)
#define HALL_PHCFG_DLYCNT_GET(x) (((uint32_t)(x) & HALL_PHCFG_DLYCNT_MASK) >> HALL_PHCFG_DLYCNT_SHIFT)

/* Bitfield definition for register: WDGCFG */
/*
 * WDGEN (RW)
 *
 * 1- enable wdog counter
 */
#define HALL_WDGCFG_WDGEN_MASK (0x80000000UL)
#define HALL_WDGCFG_WDGEN_SHIFT (31U)
#define HALL_WDGCFG_WDGEN_SET(x) (((uint32_t)(x) << HALL_WDGCFG_WDGEN_SHIFT) & HALL_WDGCFG_WDGEN_MASK)
#define HALL_WDGCFG_WDGEN_GET(x) (((uint32_t)(x) & HALL_WDGCFG_WDGEN_MASK) >> HALL_WDGCFG_WDGEN_SHIFT)

/*
 * WDGTO (RW)
 *
 * watch dog timeout value
 */
#define HALL_WDGCFG_WDGTO_MASK (0x7FFFFFFFUL)
#define HALL_WDGCFG_WDGTO_SHIFT (0U)
#define HALL_WDGCFG_WDGTO_SET(x) (((uint32_t)(x) << HALL_WDGCFG_WDGTO_SHIFT) & HALL_WDGCFG_WDGTO_MASK)
#define HALL_WDGCFG_WDGTO_GET(x) (((uint32_t)(x) & HALL_WDGCFG_WDGTO_MASK) >> HALL_WDGCFG_WDGTO_SHIFT)

/* Bitfield definition for register: UVWCFG */
/*
 * PRECNT (RW)
 *
 * the clock cycle number which the pre flag will set before the next uvw transition
 */
#define HALL_UVWCFG_PRECNT_MASK (0xFFFFFFUL)
#define HALL_UVWCFG_PRECNT_SHIFT (0U)
#define HALL_UVWCFG_PRECNT_SET(x) (((uint32_t)(x) << HALL_UVWCFG_PRECNT_SHIFT) & HALL_UVWCFG_PRECNT_MASK)
#define HALL_UVWCFG_PRECNT_GET(x) (((uint32_t)(x) & HALL_UVWCFG_PRECNT_MASK) >> HALL_UVWCFG_PRECNT_SHIFT)

/* Bitfield definition for register: TRGOEN */
/*
 * WDGEN (RW)
 *
 * 1- enable trigger output when wdg flag set
 */
#define HALL_TRGOEN_WDGEN_MASK (0x80000000UL)
#define HALL_TRGOEN_WDGEN_SHIFT (31U)
#define HALL_TRGOEN_WDGEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_WDGEN_SHIFT) & HALL_TRGOEN_WDGEN_MASK)
#define HALL_TRGOEN_WDGEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_WDGEN_MASK) >> HALL_TRGOEN_WDGEN_SHIFT)

/*
 * PHUPTEN (RW)
 *
 * 1- enable trigger output when phupt flag set
 */
#define HALL_TRGOEN_PHUPTEN_MASK (0x40000000UL)
#define HALL_TRGOEN_PHUPTEN_SHIFT (30U)
#define HALL_TRGOEN_PHUPTEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_PHUPTEN_SHIFT) & HALL_TRGOEN_PHUPTEN_MASK)
#define HALL_TRGOEN_PHUPTEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_PHUPTEN_MASK) >> HALL_TRGOEN_PHUPTEN_SHIFT)

/*
 * PHPREEN (RW)
 *
 * 1- enable trigger output when phpre flag set
 */
#define HALL_TRGOEN_PHPREEN_MASK (0x20000000UL)
#define HALL_TRGOEN_PHPREEN_SHIFT (29U)
#define HALL_TRGOEN_PHPREEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_PHPREEN_SHIFT) & HALL_TRGOEN_PHPREEN_MASK)
#define HALL_TRGOEN_PHPREEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_PHPREEN_MASK) >> HALL_TRGOEN_PHPREEN_SHIFT)

/*
 * PHDLYEN (RW)
 *
 * 1- enable trigger output when phdly flag set
 */
#define HALL_TRGOEN_PHDLYEN_MASK (0x10000000UL)
#define HALL_TRGOEN_PHDLYEN_SHIFT (28U)
#define HALL_TRGOEN_PHDLYEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_PHDLYEN_SHIFT) & HALL_TRGOEN_PHDLYEN_MASK)
#define HALL_TRGOEN_PHDLYEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_PHDLYEN_MASK) >> HALL_TRGOEN_PHDLYEN_SHIFT)

/*
 * UFEN (RW)
 *
 * 1- enable trigger output when u flag set
 */
#define HALL_TRGOEN_UFEN_MASK (0x800000UL)
#define HALL_TRGOEN_UFEN_SHIFT (23U)
#define HALL_TRGOEN_UFEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_UFEN_SHIFT) & HALL_TRGOEN_UFEN_MASK)
#define HALL_TRGOEN_UFEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_UFEN_MASK) >> HALL_TRGOEN_UFEN_SHIFT)

/*
 * VFEN (RW)
 *
 * 1- enable trigger output when v flag set
 */
#define HALL_TRGOEN_VFEN_MASK (0x400000UL)
#define HALL_TRGOEN_VFEN_SHIFT (22U)
#define HALL_TRGOEN_VFEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_VFEN_SHIFT) & HALL_TRGOEN_VFEN_MASK)
#define HALL_TRGOEN_VFEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_VFEN_MASK) >> HALL_TRGOEN_VFEN_SHIFT)

/*
 * WFEN (RW)
 *
 * 1- enable trigger output when w flag set
 */
#define HALL_TRGOEN_WFEN_MASK (0x200000UL)
#define HALL_TRGOEN_WFEN_SHIFT (21U)
#define HALL_TRGOEN_WFEN_SET(x) (((uint32_t)(x) << HALL_TRGOEN_WFEN_SHIFT) & HALL_TRGOEN_WFEN_MASK)
#define HALL_TRGOEN_WFEN_GET(x) (((uint32_t)(x) & HALL_TRGOEN_WFEN_MASK) >> HALL_TRGOEN_WFEN_SHIFT)

/* Bitfield definition for register: READEN */
/*
 * WDGEN (RW)
 *
 * 1-  load counters to their read registers when wdg flag set
 */
#define HALL_READEN_WDGEN_MASK (0x80000000UL)
#define HALL_READEN_WDGEN_SHIFT (31U)
#define HALL_READEN_WDGEN_SET(x) (((uint32_t)(x) << HALL_READEN_WDGEN_SHIFT) & HALL_READEN_WDGEN_MASK)
#define HALL_READEN_WDGEN_GET(x) (((uint32_t)(x) & HALL_READEN_WDGEN_MASK) >> HALL_READEN_WDGEN_SHIFT)

/*
 * PHUPTEN (RW)
 *
 * 1-  load counters to their read registers when phupt flag set
 */
#define HALL_READEN_PHUPTEN_MASK (0x40000000UL)
#define HALL_READEN_PHUPTEN_SHIFT (30U)
#define HALL_READEN_PHUPTEN_SET(x) (((uint32_t)(x) << HALL_READEN_PHUPTEN_SHIFT) & HALL_READEN_PHUPTEN_MASK)
#define HALL_READEN_PHUPTEN_GET(x) (((uint32_t)(x) & HALL_READEN_PHUPTEN_MASK) >> HALL_READEN_PHUPTEN_SHIFT)

/*
 * PHPREEN (RW)
 *
 * 1-  load counters to their read registers when phpre flag set
 */
#define HALL_READEN_PHPREEN_MASK (0x20000000UL)
#define HALL_READEN_PHPREEN_SHIFT (29U)
#define HALL_READEN_PHPREEN_SET(x) (((uint32_t)(x) << HALL_READEN_PHPREEN_SHIFT) & HALL_READEN_PHPREEN_MASK)
#define HALL_READEN_PHPREEN_GET(x) (((uint32_t)(x) & HALL_READEN_PHPREEN_MASK) >> HALL_READEN_PHPREEN_SHIFT)

/*
 * PHDLYEN (RW)
 *
 * 1-  load counters to their read registers when phdly flag set
 */
#define HALL_READEN_PHDLYEN_MASK (0x10000000UL)
#define HALL_READEN_PHDLYEN_SHIFT (28U)
#define HALL_READEN_PHDLYEN_SET(x) (((uint32_t)(x) << HALL_READEN_PHDLYEN_SHIFT) & HALL_READEN_PHDLYEN_MASK)
#define HALL_READEN_PHDLYEN_GET(x) (((uint32_t)(x) & HALL_READEN_PHDLYEN_MASK) >> HALL_READEN_PHDLYEN_SHIFT)

/*
 * UFEN (RW)
 *
 * 1-  load counters to their read registers when u flag set
 */
#define HALL_READEN_UFEN_MASK (0x800000UL)
#define HALL_READEN_UFEN_SHIFT (23U)
#define HALL_READEN_UFEN_SET(x) (((uint32_t)(x) << HALL_READEN_UFEN_SHIFT) & HALL_READEN_UFEN_MASK)
#define HALL_READEN_UFEN_GET(x) (((uint32_t)(x) & HALL_READEN_UFEN_MASK) >> HALL_READEN_UFEN_SHIFT)

/*
 * VFEN (RW)
 *
 * 1-  load counters to their read registers when v flag set
 */
#define HALL_READEN_VFEN_MASK (0x400000UL)
#define HALL_READEN_VFEN_SHIFT (22U)
#define HALL_READEN_VFEN_SET(x) (((uint32_t)(x) << HALL_READEN_VFEN_SHIFT) & HALL_READEN_VFEN_MASK)
#define HALL_READEN_VFEN_GET(x) (((uint32_t)(x) & HALL_READEN_VFEN_MASK) >> HALL_READEN_VFEN_SHIFT)

/*
 * WFEN (RW)
 *
 * 1-  load counters to their read registers when w flag set
 */
#define HALL_READEN_WFEN_MASK (0x200000UL)
#define HALL_READEN_WFEN_SHIFT (21U)
#define HALL_READEN_WFEN_SET(x) (((uint32_t)(x) << HALL_READEN_WFEN_SHIFT) & HALL_READEN_WFEN_MASK)
#define HALL_READEN_WFEN_GET(x) (((uint32_t)(x) & HALL_READEN_WFEN_MASK) >> HALL_READEN_WFEN_SHIFT)

/* Bitfield definition for register: DMAEN */
/*
 * WDGEN (RW)
 *
 * 1-  generate dma request when wdg flag set
 */
#define HALL_DMAEN_WDGEN_MASK (0x80000000UL)
#define HALL_DMAEN_WDGEN_SHIFT (31U)
#define HALL_DMAEN_WDGEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_WDGEN_SHIFT) & HALL_DMAEN_WDGEN_MASK)
#define HALL_DMAEN_WDGEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_WDGEN_MASK) >> HALL_DMAEN_WDGEN_SHIFT)

/*
 * PHUPTEN (RW)
 *
 * 1-  generate dma request when phupt flag set
 */
#define HALL_DMAEN_PHUPTEN_MASK (0x40000000UL)
#define HALL_DMAEN_PHUPTEN_SHIFT (30U)
#define HALL_DMAEN_PHUPTEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_PHUPTEN_SHIFT) & HALL_DMAEN_PHUPTEN_MASK)
#define HALL_DMAEN_PHUPTEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_PHUPTEN_MASK) >> HALL_DMAEN_PHUPTEN_SHIFT)

/*
 * PHPREEN (RW)
 *
 * 1-  generate dma request when phpre flag set
 */
#define HALL_DMAEN_PHPREEN_MASK (0x20000000UL)
#define HALL_DMAEN_PHPREEN_SHIFT (29U)
#define HALL_DMAEN_PHPREEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_PHPREEN_SHIFT) & HALL_DMAEN_PHPREEN_MASK)
#define HALL_DMAEN_PHPREEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_PHPREEN_MASK) >> HALL_DMAEN_PHPREEN_SHIFT)

/*
 * PHDLYEN (RW)
 *
 * 1-  generate dma request when phdly flag set
 */
#define HALL_DMAEN_PHDLYEN_MASK (0x10000000UL)
#define HALL_DMAEN_PHDLYEN_SHIFT (28U)
#define HALL_DMAEN_PHDLYEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_PHDLYEN_SHIFT) & HALL_DMAEN_PHDLYEN_MASK)
#define HALL_DMAEN_PHDLYEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_PHDLYEN_MASK) >> HALL_DMAEN_PHDLYEN_SHIFT)

/*
 * UFEN (RW)
 *
 * 1-  generate dma request when u flag set
 */
#define HALL_DMAEN_UFEN_MASK (0x800000UL)
#define HALL_DMAEN_UFEN_SHIFT (23U)
#define HALL_DMAEN_UFEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_UFEN_SHIFT) & HALL_DMAEN_UFEN_MASK)
#define HALL_DMAEN_UFEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_UFEN_MASK) >> HALL_DMAEN_UFEN_SHIFT)

/*
 * VFEN (RW)
 *
 * 1-  generate dma request when v flag set
 */
#define HALL_DMAEN_VFEN_MASK (0x400000UL)
#define HALL_DMAEN_VFEN_SHIFT (22U)
#define HALL_DMAEN_VFEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_VFEN_SHIFT) & HALL_DMAEN_VFEN_MASK)
#define HALL_DMAEN_VFEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_VFEN_MASK) >> HALL_DMAEN_VFEN_SHIFT)

/*
 * WFEN (RW)
 *
 * 1-  generate dma request when w flag set
 */
#define HALL_DMAEN_WFEN_MASK (0x200000UL)
#define HALL_DMAEN_WFEN_SHIFT (21U)
#define HALL_DMAEN_WFEN_SET(x) (((uint32_t)(x) << HALL_DMAEN_WFEN_SHIFT) & HALL_DMAEN_WFEN_MASK)
#define HALL_DMAEN_WFEN_GET(x) (((uint32_t)(x) & HALL_DMAEN_WFEN_MASK) >> HALL_DMAEN_WFEN_SHIFT)

/* Bitfield definition for register: SR */
/*
 * WDGF (RW)
 *
 * watchdog count timeout flag
 */
#define HALL_SR_WDGF_MASK (0x80000000UL)
#define HALL_SR_WDGF_SHIFT (31U)
#define HALL_SR_WDGF_SET(x) (((uint32_t)(x) << HALL_SR_WDGF_SHIFT) & HALL_SR_WDGF_MASK)
#define HALL_SR_WDGF_GET(x) (((uint32_t)(x) & HALL_SR_WDGF_MASK) >> HALL_SR_WDGF_SHIFT)

/*
 * PHUPTF (RW)
 *
 * phase update flag, will set when any of u, v, w signal toggle
 */
#define HALL_SR_PHUPTF_MASK (0x40000000UL)
#define HALL_SR_PHUPTF_SHIFT (30U)
#define HALL_SR_PHUPTF_SET(x) (((uint32_t)(x) << HALL_SR_PHUPTF_SHIFT) & HALL_SR_PHUPTF_MASK)
#define HALL_SR_PHUPTF_GET(x) (((uint32_t)(x) & HALL_SR_PHUPTF_MASK) >> HALL_SR_PHUPTF_SHIFT)

/*
 * PHPREF (RW)
 *
 * phase update pre flag, will set PRECNT cycles before any of u, v, w signal toggle
 */
#define HALL_SR_PHPREF_MASK (0x20000000UL)
#define HALL_SR_PHPREF_SHIFT (29U)
#define HALL_SR_PHPREF_SET(x) (((uint32_t)(x) << HALL_SR_PHPREF_SHIFT) & HALL_SR_PHPREF_MASK)
#define HALL_SR_PHPREF_GET(x) (((uint32_t)(x) & HALL_SR_PHPREF_MASK) >> HALL_SR_PHPREF_SHIFT)

/*
 * PHDLYF (RW)
 *
 * phase update delay flag, will set DLYCNT cycles after any of u, v, w signal toggle or after the phpre flag depands on DLYSEL setting
 */
#define HALL_SR_PHDLYF_MASK (0x10000000UL)
#define HALL_SR_PHDLYF_SHIFT (28U)
#define HALL_SR_PHDLYF_SET(x) (((uint32_t)(x) << HALL_SR_PHDLYF_SHIFT) & HALL_SR_PHDLYF_MASK)
#define HALL_SR_PHDLYF_GET(x) (((uint32_t)(x) & HALL_SR_PHDLYF_MASK) >> HALL_SR_PHDLYF_SHIFT)

/*
 * UF (RW)
 *
 * u flag, will set when u signal toggle
 */
#define HALL_SR_UF_MASK (0x800000UL)
#define HALL_SR_UF_SHIFT (23U)
#define HALL_SR_UF_SET(x) (((uint32_t)(x) << HALL_SR_UF_SHIFT) & HALL_SR_UF_MASK)
#define HALL_SR_UF_GET(x) (((uint32_t)(x) & HALL_SR_UF_MASK) >> HALL_SR_UF_SHIFT)

/*
 * VF (RW)
 *
 * v flag, will set when v signal toggle
 */
#define HALL_SR_VF_MASK (0x400000UL)
#define HALL_SR_VF_SHIFT (22U)
#define HALL_SR_VF_SET(x) (((uint32_t)(x) << HALL_SR_VF_SHIFT) & HALL_SR_VF_MASK)
#define HALL_SR_VF_GET(x) (((uint32_t)(x) & HALL_SR_VF_MASK) >> HALL_SR_VF_SHIFT)

/*
 * WF (RW)
 *
 * w flag, will set when w signal toggle
 */
#define HALL_SR_WF_MASK (0x200000UL)
#define HALL_SR_WF_SHIFT (21U)
#define HALL_SR_WF_SET(x) (((uint32_t)(x) << HALL_SR_WF_SHIFT) & HALL_SR_WF_MASK)
#define HALL_SR_WF_GET(x) (((uint32_t)(x) & HALL_SR_WF_MASK) >> HALL_SR_WF_SHIFT)

/* Bitfield definition for register: IRQEN */
/*
 * WDGIE (RW)
 *
 * 1-  generate interrupt request when wdg flag set
 */
#define HALL_IRQEN_WDGIE_MASK (0x80000000UL)
#define HALL_IRQEN_WDGIE_SHIFT (31U)
#define HALL_IRQEN_WDGIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_WDGIE_SHIFT) & HALL_IRQEN_WDGIE_MASK)
#define HALL_IRQEN_WDGIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_WDGIE_MASK) >> HALL_IRQEN_WDGIE_SHIFT)

/*
 * PHUPTIE (RW)
 *
 * 1-  generate interrupt request when phupt flag set
 */
#define HALL_IRQEN_PHUPTIE_MASK (0x40000000UL)
#define HALL_IRQEN_PHUPTIE_SHIFT (30U)
#define HALL_IRQEN_PHUPTIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_PHUPTIE_SHIFT) & HALL_IRQEN_PHUPTIE_MASK)
#define HALL_IRQEN_PHUPTIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_PHUPTIE_MASK) >> HALL_IRQEN_PHUPTIE_SHIFT)

/*
 * PHPREIE (RW)
 *
 * 1-  generate interrupt request when phpre flag set
 */
#define HALL_IRQEN_PHPREIE_MASK (0x20000000UL)
#define HALL_IRQEN_PHPREIE_SHIFT (29U)
#define HALL_IRQEN_PHPREIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_PHPREIE_SHIFT) & HALL_IRQEN_PHPREIE_MASK)
#define HALL_IRQEN_PHPREIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_PHPREIE_MASK) >> HALL_IRQEN_PHPREIE_SHIFT)

/*
 * PHDLYIE (RW)
 *
 * 1-  generate interrupt request when phdly flag set
 */
#define HALL_IRQEN_PHDLYIE_MASK (0x10000000UL)
#define HALL_IRQEN_PHDLYIE_SHIFT (28U)
#define HALL_IRQEN_PHDLYIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_PHDLYIE_SHIFT) & HALL_IRQEN_PHDLYIE_MASK)
#define HALL_IRQEN_PHDLYIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_PHDLYIE_MASK) >> HALL_IRQEN_PHDLYIE_SHIFT)

/*
 * UFIE (RW)
 *
 * 1-  generate interrupt request when u flag set
 */
#define HALL_IRQEN_UFIE_MASK (0x800000UL)
#define HALL_IRQEN_UFIE_SHIFT (23U)
#define HALL_IRQEN_UFIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_UFIE_SHIFT) & HALL_IRQEN_UFIE_MASK)
#define HALL_IRQEN_UFIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_UFIE_MASK) >> HALL_IRQEN_UFIE_SHIFT)

/*
 * VFIE (RW)
 *
 * 1-  generate interrupt request when v flag set
 */
#define HALL_IRQEN_VFIE_MASK (0x400000UL)
#define HALL_IRQEN_VFIE_SHIFT (22U)
#define HALL_IRQEN_VFIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_VFIE_SHIFT) & HALL_IRQEN_VFIE_MASK)
#define HALL_IRQEN_VFIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_VFIE_MASK) >> HALL_IRQEN_VFIE_SHIFT)

/*
 * WFIE (RW)
 *
 * 1-  generate interrupt request when w flag set
 */
#define HALL_IRQEN_WFIE_MASK (0x200000UL)
#define HALL_IRQEN_WFIE_SHIFT (21U)
#define HALL_IRQEN_WFIE_SET(x) (((uint32_t)(x) << HALL_IRQEN_WFIE_SHIFT) & HALL_IRQEN_WFIE_MASK)
#define HALL_IRQEN_WFIE_GET(x) (((uint32_t)(x) & HALL_IRQEN_WFIE_MASK) >> HALL_IRQEN_WFIE_SHIFT)

/* Bitfield definition for register of struct array COUNT: W */
/*
 * WCNT (RO)
 *
 * wcnt counter
 */
#define HALL_COUNT_W_WCNT_MASK (0xFFFFFFFUL)
#define HALL_COUNT_W_WCNT_SHIFT (0U)
#define HALL_COUNT_W_WCNT_GET(x) (((uint32_t)(x) & HALL_COUNT_W_WCNT_MASK) >> HALL_COUNT_W_WCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: V */
/*
 * VCNT (RO)
 *
 * vcnt counter
 */
#define HALL_COUNT_V_VCNT_MASK (0xFFFFFFFUL)
#define HALL_COUNT_V_VCNT_SHIFT (0U)
#define HALL_COUNT_V_VCNT_GET(x) (((uint32_t)(x) & HALL_COUNT_V_VCNT_MASK) >> HALL_COUNT_V_VCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: U */
/*
 * DIR (RO)
 *
 * 1- reverse rotation
 * 0- forward rotation
 */
#define HALL_COUNT_U_DIR_MASK (0x80000000UL)
#define HALL_COUNT_U_DIR_SHIFT (31U)
#define HALL_COUNT_U_DIR_GET(x) (((uint32_t)(x) & HALL_COUNT_U_DIR_MASK) >> HALL_COUNT_U_DIR_SHIFT)

/*
 * USTAT (RO)
 *
 * this bit indicate U state
 */
#define HALL_COUNT_U_USTAT_MASK (0x40000000UL)
#define HALL_COUNT_U_USTAT_SHIFT (30U)
#define HALL_COUNT_U_USTAT_GET(x) (((uint32_t)(x) & HALL_COUNT_U_USTAT_MASK) >> HALL_COUNT_U_USTAT_SHIFT)

/*
 * VSTAT (RO)
 *
 * this bit indicate V state
 */
#define HALL_COUNT_U_VSTAT_MASK (0x20000000UL)
#define HALL_COUNT_U_VSTAT_SHIFT (29U)
#define HALL_COUNT_U_VSTAT_GET(x) (((uint32_t)(x) & HALL_COUNT_U_VSTAT_MASK) >> HALL_COUNT_U_VSTAT_SHIFT)

/*
 * WSTAT (RO)
 *
 * this bit indicate W state
 */
#define HALL_COUNT_U_WSTAT_MASK (0x10000000UL)
#define HALL_COUNT_U_WSTAT_SHIFT (28U)
#define HALL_COUNT_U_WSTAT_GET(x) (((uint32_t)(x) & HALL_COUNT_U_WSTAT_MASK) >> HALL_COUNT_U_WSTAT_SHIFT)

/*
 * UCNT (RO)
 *
 * ucnt counter
 */
#define HALL_COUNT_U_UCNT_MASK (0xFFFFFFFUL)
#define HALL_COUNT_U_UCNT_SHIFT (0U)
#define HALL_COUNT_U_UCNT_GET(x) (((uint32_t)(x) & HALL_COUNT_U_UCNT_MASK) >> HALL_COUNT_U_UCNT_SHIFT)

/* Bitfield definition for register of struct array COUNT: TMR */
/*
 * TIMER (RO)
 *
 * 32 bit free run timer
 */
#define HALL_COUNT_TMR_TIMER_MASK (0xFFFFFFFFUL)
#define HALL_COUNT_TMR_TIMER_SHIFT (0U)
#define HALL_COUNT_TMR_TIMER_GET(x) (((uint32_t)(x) & HALL_COUNT_TMR_TIMER_MASK) >> HALL_COUNT_TMR_TIMER_SHIFT)

/* Bitfield definition for register of struct array HIS: HIS0 */
/*
 * UHIS0 (RO)
 *
 * copy of ucnt when u signal transition from 0 to 1
 */
#define HALL_HIS_HIS0_UHIS0_MASK (0xFFFFFFFFUL)
#define HALL_HIS_HIS0_UHIS0_SHIFT (0U)
#define HALL_HIS_HIS0_UHIS0_GET(x) (((uint32_t)(x) & HALL_HIS_HIS0_UHIS0_MASK) >> HALL_HIS_HIS0_UHIS0_SHIFT)

/* Bitfield definition for register of struct array HIS: HIS1 */
/*
 * UHIS1 (RO)
 *
 * copy of ucnt when u signal transition from 1 to 0
 */
#define HALL_HIS_HIS1_UHIS1_MASK (0xFFFFFFFFUL)
#define HALL_HIS_HIS1_UHIS1_SHIFT (0U)
#define HALL_HIS_HIS1_UHIS1_GET(x) (((uint32_t)(x) & HALL_HIS_HIS1_UHIS1_MASK) >> HALL_HIS_HIS1_UHIS1_SHIFT)



/* COUNT register group index macro definition */
#define HALL_COUNT_CURRENT (0UL)
#define HALL_COUNT_READ (1UL)
#define HALL_COUNT_SNAP0 (2UL)
#define HALL_COUNT_SNAP1 (3UL)

/* HIS register group index macro definition */
#define HALL_HIS_U (0UL)
#define HALL_HIS_V (1UL)
#define HALL_HIS_W (2UL)


#endif /* HPM_HALL_H */

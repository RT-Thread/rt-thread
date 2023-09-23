/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_ACMP_H
#define HPM_ACMP_H

typedef struct {
    struct {
        __RW uint32_t CFG;                     /* 0x0: Configure Register */
        __RW uint32_t DACCFG;                  /* 0x4: DAC configure register */
        __R  uint8_t  RESERVED0[8];            /* 0x8 - 0xF: Reserved */
        __RW uint32_t SR;                      /* 0x10: Status register */
        __RW uint32_t IRQEN;                   /* 0x14: Interrupt request enable register */
        __RW uint32_t DMAEN;                   /* 0x18: DMA request enable register */
        __R  uint8_t  RESERVED1[4];            /* 0x1C - 0x1F: Reserved */
    } CHANNEL[4];
} ACMP_Type;


/* Bitfield definition for register of struct array CHANNEL: CFG */
/*
 * HYST (RW)
 *
 * This bitfield configure the comparator hysteresis.
 * 00: Hysteresis level 0
 * 01: Hysteresis level 1
 * 10: Hysteresis level 2
 * 11: Hysteresis level 3
 */
#define ACMP_CHANNEL_CFG_HYST_MASK (0xC0000000UL)
#define ACMP_CHANNEL_CFG_HYST_SHIFT (30U)
#define ACMP_CHANNEL_CFG_HYST_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_HYST_SHIFT) & ACMP_CHANNEL_CFG_HYST_MASK)
#define ACMP_CHANNEL_CFG_HYST_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_HYST_MASK) >> ACMP_CHANNEL_CFG_HYST_SHIFT)

/*
 * DACEN (RW)
 *
 * This bit enable the comparator internal DAC
 * 0: DAC disabled
 * 1: DAC enabled
 */
#define ACMP_CHANNEL_CFG_DACEN_MASK (0x20000000UL)
#define ACMP_CHANNEL_CFG_DACEN_SHIFT (29U)
#define ACMP_CHANNEL_CFG_DACEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_DACEN_SHIFT) & ACMP_CHANNEL_CFG_DACEN_MASK)
#define ACMP_CHANNEL_CFG_DACEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_DACEN_MASK) >> ACMP_CHANNEL_CFG_DACEN_SHIFT)

/*
 * HPMODE (RW)
 *
 * This bit enable the comparator high performance mode.
 * 0: HP mode disabled
 * 1: HP mode enabled
 */
#define ACMP_CHANNEL_CFG_HPMODE_MASK (0x10000000UL)
#define ACMP_CHANNEL_CFG_HPMODE_SHIFT (28U)
#define ACMP_CHANNEL_CFG_HPMODE_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_HPMODE_SHIFT) & ACMP_CHANNEL_CFG_HPMODE_MASK)
#define ACMP_CHANNEL_CFG_HPMODE_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_HPMODE_MASK) >> ACMP_CHANNEL_CFG_HPMODE_SHIFT)

/*
 * CMPEN (RW)
 *
 * This bit enable the comparator.
 * 0: ACMP disabled
 * 1: ACMP enabled
 */
#define ACMP_CHANNEL_CFG_CMPEN_MASK (0x8000000UL)
#define ACMP_CHANNEL_CFG_CMPEN_SHIFT (27U)
#define ACMP_CHANNEL_CFG_CMPEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_CMPEN_SHIFT) & ACMP_CHANNEL_CFG_CMPEN_MASK)
#define ACMP_CHANNEL_CFG_CMPEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_CMPEN_MASK) >> ACMP_CHANNEL_CFG_CMPEN_SHIFT)

/*
 * MINSEL (RW)
 *
 * PIN select, from pad_ai_acmp[7:1] and dac_out
 */
#define ACMP_CHANNEL_CFG_MINSEL_MASK (0x7000000UL)
#define ACMP_CHANNEL_CFG_MINSEL_SHIFT (24U)
#define ACMP_CHANNEL_CFG_MINSEL_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_MINSEL_SHIFT) & ACMP_CHANNEL_CFG_MINSEL_MASK)
#define ACMP_CHANNEL_CFG_MINSEL_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_MINSEL_MASK) >> ACMP_CHANNEL_CFG_MINSEL_SHIFT)

/*
 * PINSEL (RW)
 *
 * MIN select, from pad_ai_acmp[7:1] and dac_out
 */
#define ACMP_CHANNEL_CFG_PINSEL_MASK (0x700000UL)
#define ACMP_CHANNEL_CFG_PINSEL_SHIFT (20U)
#define ACMP_CHANNEL_CFG_PINSEL_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_PINSEL_SHIFT) & ACMP_CHANNEL_CFG_PINSEL_MASK)
#define ACMP_CHANNEL_CFG_PINSEL_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_PINSEL_MASK) >> ACMP_CHANNEL_CFG_PINSEL_SHIFT)

/*
 * CMPOEN (RW)
 *
 * This bit enable the comparator output on pad.
 * 0: ACMP output disabled
 * 1: ACMP output enabled
 */
#define ACMP_CHANNEL_CFG_CMPOEN_MASK (0x80000UL)
#define ACMP_CHANNEL_CFG_CMPOEN_SHIFT (19U)
#define ACMP_CHANNEL_CFG_CMPOEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_CMPOEN_SHIFT) & ACMP_CHANNEL_CFG_CMPOEN_MASK)
#define ACMP_CHANNEL_CFG_CMPOEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_CMPOEN_MASK) >> ACMP_CHANNEL_CFG_CMPOEN_SHIFT)

/*
 * FLTBYPS (RW)
 *
 * This bit bypass the comparator output digital filter.
 * 0: The ACMP output need pass digital filter
 * 1: The ACMP output digital filter is bypassed.
 */
#define ACMP_CHANNEL_CFG_FLTBYPS_MASK (0x40000UL)
#define ACMP_CHANNEL_CFG_FLTBYPS_SHIFT (18U)
#define ACMP_CHANNEL_CFG_FLTBYPS_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_FLTBYPS_SHIFT) & ACMP_CHANNEL_CFG_FLTBYPS_MASK)
#define ACMP_CHANNEL_CFG_FLTBYPS_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_FLTBYPS_MASK) >> ACMP_CHANNEL_CFG_FLTBYPS_SHIFT)

/*
 * WINEN (RW)
 *
 * This bit enable the comparator window mode.
 * 0: Window mode is disabled
 * 1: Window mode is enabled
 */
#define ACMP_CHANNEL_CFG_WINEN_MASK (0x20000UL)
#define ACMP_CHANNEL_CFG_WINEN_SHIFT (17U)
#define ACMP_CHANNEL_CFG_WINEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_WINEN_SHIFT) & ACMP_CHANNEL_CFG_WINEN_MASK)
#define ACMP_CHANNEL_CFG_WINEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_WINEN_MASK) >> ACMP_CHANNEL_CFG_WINEN_SHIFT)

/*
 * OPOL (RW)
 *
 * The output polarity control bit.
 * 0: The ACMP output remain un-changed.
 * 1: The ACMP output is inverted.
 */
#define ACMP_CHANNEL_CFG_OPOL_MASK (0x10000UL)
#define ACMP_CHANNEL_CFG_OPOL_SHIFT (16U)
#define ACMP_CHANNEL_CFG_OPOL_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_OPOL_SHIFT) & ACMP_CHANNEL_CFG_OPOL_MASK)
#define ACMP_CHANNEL_CFG_OPOL_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_OPOL_MASK) >> ACMP_CHANNEL_CFG_OPOL_SHIFT)

/*
 * FLTMODE (RW)
 *
 * This bitfield define the ACMP output digital filter mode:
 * 000-bypass
 * 100-change immediately;
 * 101-change after filter;
 * 110-stalbe low;
 * 111-stable high
 */
#define ACMP_CHANNEL_CFG_FLTMODE_MASK (0xE000U)
#define ACMP_CHANNEL_CFG_FLTMODE_SHIFT (13U)
#define ACMP_CHANNEL_CFG_FLTMODE_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_FLTMODE_SHIFT) & ACMP_CHANNEL_CFG_FLTMODE_MASK)
#define ACMP_CHANNEL_CFG_FLTMODE_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_FLTMODE_MASK) >> ACMP_CHANNEL_CFG_FLTMODE_SHIFT)

/*
 * SYNCEN (RW)
 *
 * This bit enable the comparator output synchronization.
 * 0: ACMP output not synchronized with ACMP clock.
 * 1: ACMP output synchronized with ACMP clock.
 */
#define ACMP_CHANNEL_CFG_SYNCEN_MASK (0x1000U)
#define ACMP_CHANNEL_CFG_SYNCEN_SHIFT (12U)
#define ACMP_CHANNEL_CFG_SYNCEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_SYNCEN_SHIFT) & ACMP_CHANNEL_CFG_SYNCEN_MASK)
#define ACMP_CHANNEL_CFG_SYNCEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_SYNCEN_MASK) >> ACMP_CHANNEL_CFG_SYNCEN_SHIFT)

/*
 * FLTLEN (RW)
 *
 * This bitfield define the ACMP output digital filter length. The unit is ACMP clock cycle.
 */
#define ACMP_CHANNEL_CFG_FLTLEN_MASK (0xFFFU)
#define ACMP_CHANNEL_CFG_FLTLEN_SHIFT (0U)
#define ACMP_CHANNEL_CFG_FLTLEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_CFG_FLTLEN_SHIFT) & ACMP_CHANNEL_CFG_FLTLEN_MASK)
#define ACMP_CHANNEL_CFG_FLTLEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_CFG_FLTLEN_MASK) >> ACMP_CHANNEL_CFG_FLTLEN_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: DACCFG */
/*
 * DACCFG (RW)
 *
 * 8bit DAC digital value
 */
#define ACMP_CHANNEL_DACCFG_DACCFG_MASK (0xFFU)
#define ACMP_CHANNEL_DACCFG_DACCFG_SHIFT (0U)
#define ACMP_CHANNEL_DACCFG_DACCFG_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_DACCFG_DACCFG_SHIFT) & ACMP_CHANNEL_DACCFG_DACCFG_MASK)
#define ACMP_CHANNEL_DACCFG_DACCFG_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_DACCFG_DACCFG_MASK) >> ACMP_CHANNEL_DACCFG_DACCFG_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: SR */
/*
 * FEDGF (RW)
 *
 * Output falling edge flag. Write 1 to clear this flag.
 */
#define ACMP_CHANNEL_SR_FEDGF_MASK (0x2U)
#define ACMP_CHANNEL_SR_FEDGF_SHIFT (1U)
#define ACMP_CHANNEL_SR_FEDGF_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_SR_FEDGF_SHIFT) & ACMP_CHANNEL_SR_FEDGF_MASK)
#define ACMP_CHANNEL_SR_FEDGF_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_SR_FEDGF_MASK) >> ACMP_CHANNEL_SR_FEDGF_SHIFT)

/*
 * REDGF (RW)
 *
 * Output rising edge flag. Write 1 to clear this flag.
 */
#define ACMP_CHANNEL_SR_REDGF_MASK (0x1U)
#define ACMP_CHANNEL_SR_REDGF_SHIFT (0U)
#define ACMP_CHANNEL_SR_REDGF_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_SR_REDGF_SHIFT) & ACMP_CHANNEL_SR_REDGF_MASK)
#define ACMP_CHANNEL_SR_REDGF_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_SR_REDGF_MASK) >> ACMP_CHANNEL_SR_REDGF_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: IRQEN */
/*
 * FEDGEN (RW)
 *
 * Output falling edge flag interrupt enable bit.
 */
#define ACMP_CHANNEL_IRQEN_FEDGEN_MASK (0x2U)
#define ACMP_CHANNEL_IRQEN_FEDGEN_SHIFT (1U)
#define ACMP_CHANNEL_IRQEN_FEDGEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_IRQEN_FEDGEN_SHIFT) & ACMP_CHANNEL_IRQEN_FEDGEN_MASK)
#define ACMP_CHANNEL_IRQEN_FEDGEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_IRQEN_FEDGEN_MASK) >> ACMP_CHANNEL_IRQEN_FEDGEN_SHIFT)

/*
 * REDGEN (RW)
 *
 * Output rising edge flag interrupt enable bit.
 */
#define ACMP_CHANNEL_IRQEN_REDGEN_MASK (0x1U)
#define ACMP_CHANNEL_IRQEN_REDGEN_SHIFT (0U)
#define ACMP_CHANNEL_IRQEN_REDGEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_IRQEN_REDGEN_SHIFT) & ACMP_CHANNEL_IRQEN_REDGEN_MASK)
#define ACMP_CHANNEL_IRQEN_REDGEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_IRQEN_REDGEN_MASK) >> ACMP_CHANNEL_IRQEN_REDGEN_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: DMAEN */
/*
 * FEDGEN (RW)
 *
 * Output falling edge flag DMA request enable bit.
 */
#define ACMP_CHANNEL_DMAEN_FEDGEN_MASK (0x2U)
#define ACMP_CHANNEL_DMAEN_FEDGEN_SHIFT (1U)
#define ACMP_CHANNEL_DMAEN_FEDGEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_DMAEN_FEDGEN_SHIFT) & ACMP_CHANNEL_DMAEN_FEDGEN_MASK)
#define ACMP_CHANNEL_DMAEN_FEDGEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_DMAEN_FEDGEN_MASK) >> ACMP_CHANNEL_DMAEN_FEDGEN_SHIFT)

/*
 * REDGEN (RW)
 *
 * Output rising edge flag DMA request enable bit.
 */
#define ACMP_CHANNEL_DMAEN_REDGEN_MASK (0x1U)
#define ACMP_CHANNEL_DMAEN_REDGEN_SHIFT (0U)
#define ACMP_CHANNEL_DMAEN_REDGEN_SET(x) (((uint32_t)(x) << ACMP_CHANNEL_DMAEN_REDGEN_SHIFT) & ACMP_CHANNEL_DMAEN_REDGEN_MASK)
#define ACMP_CHANNEL_DMAEN_REDGEN_GET(x) (((uint32_t)(x) & ACMP_CHANNEL_DMAEN_REDGEN_MASK) >> ACMP_CHANNEL_DMAEN_REDGEN_SHIFT)



/* CHANNEL register group index macro definition */
#define ACMP_CHANNEL_CHN0 (0UL)
#define ACMP_CHANNEL_CHN1 (1UL)
#define ACMP_CHANNEL_CHN2 (2UL)
#define ACMP_CHANNEL_CHN3 (3UL)


#endif /* HPM_ACMP_H */

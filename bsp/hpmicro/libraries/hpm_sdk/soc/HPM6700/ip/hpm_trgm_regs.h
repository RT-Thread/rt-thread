/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_TRGM_H
#define HPM_TRGM_H

typedef struct {
    __RW uint32_t FILTCFG[20];                 /* 0x0 - 0x4C: Filter configure register */
    __R  uint8_t  RESERVED0[176];              /* 0x50 - 0xFF: Reserved */
    __RW uint32_t TRGOCFG[64];                 /* 0x100 - 0x1FC: Trigger manager output configure register */
    __RW uint32_t DMACFG[4];                   /* 0x200 - 0x20C: DMA request configure register */
    __R  uint8_t  RESERVED1[496];              /* 0x210 - 0x3FF: Reserved */
    __RW uint32_t GCR;                         /* 0x400: General Control Register */
} TRGM_Type;


/* Bitfield definition for register array: FILTCFG */
/*
 * OUTINV (RW)
 *
 * 1- Filter will invert the output
 * 0- Filter will not invert the output
 */
#define TRGM_FILTCFG_OUTINV_MASK (0x10000UL)
#define TRGM_FILTCFG_OUTINV_SHIFT (16U)
#define TRGM_FILTCFG_OUTINV_SET(x) (((uint32_t)(x) << TRGM_FILTCFG_OUTINV_SHIFT) & TRGM_FILTCFG_OUTINV_MASK)
#define TRGM_FILTCFG_OUTINV_GET(x) (((uint32_t)(x) & TRGM_FILTCFG_OUTINV_MASK) >> TRGM_FILTCFG_OUTINV_SHIFT)

/*
 * MODE (RW)
 *
 * This bitfields defines the filter mode
 * 000-bypass;
 * 100-rapid change mode;
 * 101-delay filter mode;
 * 110-stalbe low mode;
 * 111-stable high mode
 */
#define TRGM_FILTCFG_MODE_MASK (0xE000U)
#define TRGM_FILTCFG_MODE_SHIFT (13U)
#define TRGM_FILTCFG_MODE_SET(x) (((uint32_t)(x) << TRGM_FILTCFG_MODE_SHIFT) & TRGM_FILTCFG_MODE_MASK)
#define TRGM_FILTCFG_MODE_GET(x) (((uint32_t)(x) & TRGM_FILTCFG_MODE_MASK) >> TRGM_FILTCFG_MODE_SHIFT)

/*
 * SYNCEN (RW)
 *
 * set to enable sychronization input signal with TRGM clock
 */
#define TRGM_FILTCFG_SYNCEN_MASK (0x1000U)
#define TRGM_FILTCFG_SYNCEN_SHIFT (12U)
#define TRGM_FILTCFG_SYNCEN_SET(x) (((uint32_t)(x) << TRGM_FILTCFG_SYNCEN_SHIFT) & TRGM_FILTCFG_SYNCEN_MASK)
#define TRGM_FILTCFG_SYNCEN_GET(x) (((uint32_t)(x) & TRGM_FILTCFG_SYNCEN_MASK) >> TRGM_FILTCFG_SYNCEN_SHIFT)

/*
 * FILTLEN (RW)
 *
 * This bitfields defines the filter counter length.
 */
#define TRGM_FILTCFG_FILTLEN_MASK (0xFFFU)
#define TRGM_FILTCFG_FILTLEN_SHIFT (0U)
#define TRGM_FILTCFG_FILTLEN_SET(x) (((uint32_t)(x) << TRGM_FILTCFG_FILTLEN_SHIFT) & TRGM_FILTCFG_FILTLEN_MASK)
#define TRGM_FILTCFG_FILTLEN_GET(x) (((uint32_t)(x) & TRGM_FILTCFG_FILTLEN_MASK) >> TRGM_FILTCFG_FILTLEN_SHIFT)

/* Bitfield definition for register array: TRGOCFG */
/*
 * OUTINV (RW)
 *
 * 1- Invert the output
 */
#define TRGM_TRGOCFG_OUTINV_MASK (0x100U)
#define TRGM_TRGOCFG_OUTINV_SHIFT (8U)
#define TRGM_TRGOCFG_OUTINV_SET(x) (((uint32_t)(x) << TRGM_TRGOCFG_OUTINV_SHIFT) & TRGM_TRGOCFG_OUTINV_MASK)
#define TRGM_TRGOCFG_OUTINV_GET(x) (((uint32_t)(x) & TRGM_TRGOCFG_OUTINV_MASK) >> TRGM_TRGOCFG_OUTINV_SHIFT)

/*
 * FEDG2PEN (RW)
 *
 * 1- The selected input signal falling edge will be convert to an pulse on output.
 */
#define TRGM_TRGOCFG_FEDG2PEN_MASK (0x80U)
#define TRGM_TRGOCFG_FEDG2PEN_SHIFT (7U)
#define TRGM_TRGOCFG_FEDG2PEN_SET(x) (((uint32_t)(x) << TRGM_TRGOCFG_FEDG2PEN_SHIFT) & TRGM_TRGOCFG_FEDG2PEN_MASK)
#define TRGM_TRGOCFG_FEDG2PEN_GET(x) (((uint32_t)(x) & TRGM_TRGOCFG_FEDG2PEN_MASK) >> TRGM_TRGOCFG_FEDG2PEN_SHIFT)

/*
 * REDG2PEN (RW)
 *
 * 1- The selected input signal rising edge will be convert to an pulse on output.
 */
#define TRGM_TRGOCFG_REDG2PEN_MASK (0x40U)
#define TRGM_TRGOCFG_REDG2PEN_SHIFT (6U)
#define TRGM_TRGOCFG_REDG2PEN_SET(x) (((uint32_t)(x) << TRGM_TRGOCFG_REDG2PEN_SHIFT) & TRGM_TRGOCFG_REDG2PEN_MASK)
#define TRGM_TRGOCFG_REDG2PEN_GET(x) (((uint32_t)(x) & TRGM_TRGOCFG_REDG2PEN_MASK) >> TRGM_TRGOCFG_REDG2PEN_SHIFT)

/*
 * TRIGOSEL (RW)
 *
 * This bitfield selects one of the TRGM inputs as output.
 */
#define TRGM_TRGOCFG_TRIGOSEL_MASK (0x3FU)
#define TRGM_TRGOCFG_TRIGOSEL_SHIFT (0U)
#define TRGM_TRGOCFG_TRIGOSEL_SET(x) (((uint32_t)(x) << TRGM_TRGOCFG_TRIGOSEL_SHIFT) & TRGM_TRGOCFG_TRIGOSEL_MASK)
#define TRGM_TRGOCFG_TRIGOSEL_GET(x) (((uint32_t)(x) & TRGM_TRGOCFG_TRIGOSEL_MASK) >> TRGM_TRGOCFG_TRIGOSEL_SHIFT)

/* Bitfield definition for register array: DMACFG */
/*
 * DMASRCSEL (RW)
 *
 * This field selects one of the DMA requests as the DMA request output.
 */
#define TRGM_DMACFG_DMASRCSEL_MASK (0x1FU)
#define TRGM_DMACFG_DMASRCSEL_SHIFT (0U)
#define TRGM_DMACFG_DMASRCSEL_SET(x) (((uint32_t)(x) << TRGM_DMACFG_DMASRCSEL_SHIFT) & TRGM_DMACFG_DMASRCSEL_MASK)
#define TRGM_DMACFG_DMASRCSEL_GET(x) (((uint32_t)(x) & TRGM_DMACFG_DMASRCSEL_MASK) >> TRGM_DMACFG_DMASRCSEL_SHIFT)

/* Bitfield definition for register: GCR */
/*
 * TRGOPEN (RW)
 *
 * The bitfield enable the TRGM outputs.
 */
#define TRGM_GCR_TRGOPEN_MASK (0xFFFU)
#define TRGM_GCR_TRGOPEN_SHIFT (0U)
#define TRGM_GCR_TRGOPEN_SET(x) (((uint32_t)(x) << TRGM_GCR_TRGOPEN_SHIFT) & TRGM_GCR_TRGOPEN_MASK)
#define TRGM_GCR_TRGOPEN_GET(x) (((uint32_t)(x) & TRGM_GCR_TRGOPEN_MASK) >> TRGM_GCR_TRGOPEN_SHIFT)



/* FILTCFG register group index macro definition */
#define TRGM_FILTCFG_PWM_IN0 (0UL)
#define TRGM_FILTCFG_PWM_IN1 (1UL)
#define TRGM_FILTCFG_PWM_IN2 (2UL)
#define TRGM_FILTCFG_PWM_IN3 (3UL)
#define TRGM_FILTCFG_PWM_IN4 (4UL)
#define TRGM_FILTCFG_PWM_IN5 (5UL)
#define TRGM_FILTCFG_PWM_IN6 (6UL)
#define TRGM_FILTCFG_PWM_IN7 (7UL)
#define TRGM_FILTCFG_TRGM_IN0 (8UL)
#define TRGM_FILTCFG_TRGM_IN1 (9UL)
#define TRGM_FILTCFG_TRGM_IN2 (10UL)
#define TRGM_FILTCFG_TRGM_IN3 (11UL)
#define TRGM_FILTCFG_TRGM_IN4 (12UL)
#define TRGM_FILTCFG_TRGM_IN5 (13UL)
#define TRGM_FILTCFG_TRGM_IN6 (14UL)
#define TRGM_FILTCFG_TRGM_IN7 (15UL)
#define TRGM_FILTCFG_TRGM_IN8 (16UL)
#define TRGM_FILTCFG_TRGM_IN9 (17UL)
#define TRGM_FILTCFG_TRGM_IN10 (18UL)
#define TRGM_FILTCFG_TRGM_IN11 (19UL)

/* TRGOCFG register group index macro definition */
#define TRGM_TRGOCFG_TRGM_OUT0 (0UL)
#define TRGM_TRGOCFG_TRGM_OUT1 (1UL)
#define TRGM_TRGOCFG_TRGM_OUT2 (2UL)
#define TRGM_TRGOCFG_TRGM_OUT3 (3UL)
#define TRGM_TRGOCFG_TRGM_OUT4 (4UL)
#define TRGM_TRGOCFG_TRGM_OUT5 (5UL)
#define TRGM_TRGOCFG_TRGM_OUT6 (6UL)
#define TRGM_TRGOCFG_TRGM_OUT7 (7UL)
#define TRGM_TRGOCFG_TRGM_OUT8 (8UL)
#define TRGM_TRGOCFG_TRGM_OUT9 (9UL)
#define TRGM_TRGOCFG_TRGM_OUT10 (10UL)
#define TRGM_TRGOCFG_TRGM_OUT11 (11UL)
#define TRGM_TRGOCFG_TRGM_OUTX0 (12UL)
#define TRGM_TRGOCFG_TRGM_OUTX1 (13UL)
#define TRGM_TRGOCFG_PWM_SYNCI (14UL)
#define TRGM_TRGOCFG_PWM_FRCI (15UL)
#define TRGM_TRGOCFG_PWM_FRCSYNCI (16UL)
#define TRGM_TRGOCFG_PWM_SHRLDSYNCI (17UL)
#define TRGM_TRGOCFG_PWM_FAULTI0 (18UL)
#define TRGM_TRGOCFG_PWM_FAULTI1 (19UL)
#define TRGM_TRGOCFG_PWM_FAULTI2 (20UL)
#define TRGM_TRGOCFG_PWM_FAULTI3 (21UL)
#define TRGM_TRGOCFG_PWM_IN8 (22UL)
#define TRGM_TRGOCFG_PWM_IN9 (23UL)
#define TRGM_TRGOCFG_PWM_IN10 (24UL)
#define TRGM_TRGOCFG_PWM_IN11 (25UL)
#define TRGM_TRGOCFG_PWM_IN12 (26UL)
#define TRGM_TRGOCFG_PWM_IN13 (27UL)
#define TRGM_TRGOCFG_PWM_IN14 (28UL)
#define TRGM_TRGOCFG_PWM_IN15 (29UL)
#define TRGM_TRGOCFG_PWM_IN16 (30UL)
#define TRGM_TRGOCFG_PWM_IN17 (31UL)
#define TRGM_TRGOCFG_PWM_IN18 (32UL)
#define TRGM_TRGOCFG_PWM_IN19 (33UL)
#define TRGM_TRGOCFG_PWM_IN20 (34UL)
#define TRGM_TRGOCFG_PWM_IN21 (35UL)
#define TRGM_TRGOCFG_PWM_IN22 (36UL)
#define TRGM_TRGOCFG_PWM_IN23 (37UL)
#define TRGM_TRGOCFG_QEI_A (38UL)
#define TRGM_TRGOCFG_QEI_B (39UL)
#define TRGM_TRGOCFG_QEI_Z (40UL)
#define TRGM_TRGOCFG_QEI_H (41UL)
#define TRGM_TRGOCFG_QEI_PAUSE (42UL)
#define TRGM_TRGOCFG_QEI_SNAPI (43UL)
#define TRGM_TRGOCFG_HALL_U (44UL)
#define TRGM_TRGOCFG_HALL_V (45UL)
#define TRGM_TRGOCFG_HALL_W (46UL)
#define TRGM_TRGOCFG_HALL_SNAPI (47UL)
#define TRGM_TRGOCFG_ADC0_STRGI (48UL)
#define TRGM_TRGOCFG_ADC1_STRGI (49UL)
#define TRGM_TRGOCFG_ADC2_STRGI (50UL)
#define TRGM_TRGOCFG_ADC3_STRGI (51UL)
#define TRGM_TRGOCFG_ADCX_PTRGI0A (52UL)
#define TRGM_TRGOCFG_ADCX_PTRGI0B (53UL)
#define TRGM_TRGOCFG_ADCX_PTRGI0C (54UL)
#define TRGM_TRGOCFG_GPTMRA_SYNCI (55UL)
#define TRGM_TRGOCFG_GPTMRA_IN2 (56UL)
#define TRGM_TRGOCFG_GPTMRA_IN3 (57UL)
#define TRGM_TRGOCFG_GPTMRB_SYNCI (58UL)
#define TRGM_TRGOCFG_GPTMRB_IN2 (59UL)
#define TRGM_TRGOCFG_GPTMRB_IN3 (60UL)
#define TRGM_TRGOCFG_CMPX_WIN (61UL)
#define TRGM_TRGOCFG_CAN_PTPC0_CAP (62UL)
#define TRGM_TRGOCFG_CAN_PTPC1_CAP (63UL)

/* DMACFG register group index macro definition */
#define TRGM_DMACFG_0 (0UL)
#define TRGM_DMACFG_1 (1UL)
#define TRGM_DMACFG_2 (2UL)
#define TRGM_DMACFG_3 (3UL)


#endif /* HPM_TRGM_H */

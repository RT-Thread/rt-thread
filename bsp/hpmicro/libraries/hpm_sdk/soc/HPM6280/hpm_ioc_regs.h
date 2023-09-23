/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_IOC_H
#define HPM_IOC_H

typedef struct {
    struct {
        __RW uint32_t FUNC_CTL;                /* 0x0: ALT SELECT */
        __RW uint32_t PAD_CTL;                 /* 0x4: PAD SETTINGS */
    } PAD[488];
} IOC_Type;


/* Bitfield definition for register of struct array PAD: FUNC_CTL */
/*
 * LOOP_BACK (RW)
 *
 * force input on
 * 0: disable
 * 1: enable
 */
#define IOC_PAD_FUNC_CTL_LOOP_BACK_MASK (0x10000UL)
#define IOC_PAD_FUNC_CTL_LOOP_BACK_SHIFT (16U)
#define IOC_PAD_FUNC_CTL_LOOP_BACK_SET(x) (((uint32_t)(x) << IOC_PAD_FUNC_CTL_LOOP_BACK_SHIFT) & IOC_PAD_FUNC_CTL_LOOP_BACK_MASK)
#define IOC_PAD_FUNC_CTL_LOOP_BACK_GET(x) (((uint32_t)(x) & IOC_PAD_FUNC_CTL_LOOP_BACK_MASK) >> IOC_PAD_FUNC_CTL_LOOP_BACK_SHIFT)

/*
 * ANALOG (RW)
 *
 * select analog pin in pad
 * 0: disable
 * 1: enable
 */
#define IOC_PAD_FUNC_CTL_ANALOG_MASK (0x100U)
#define IOC_PAD_FUNC_CTL_ANALOG_SHIFT (8U)
#define IOC_PAD_FUNC_CTL_ANALOG_SET(x) (((uint32_t)(x) << IOC_PAD_FUNC_CTL_ANALOG_SHIFT) & IOC_PAD_FUNC_CTL_ANALOG_MASK)
#define IOC_PAD_FUNC_CTL_ANALOG_GET(x) (((uint32_t)(x) & IOC_PAD_FUNC_CTL_ANALOG_MASK) >> IOC_PAD_FUNC_CTL_ANALOG_SHIFT)

/*
 * ALT_SELECT (RW)
 *
 * alt select
 * 0: ALT0
 * 1: ALT1
 * …
 * 31:ALT31
 */
#define IOC_PAD_FUNC_CTL_ALT_SELECT_MASK (0x1FU)
#define IOC_PAD_FUNC_CTL_ALT_SELECT_SHIFT (0U)
#define IOC_PAD_FUNC_CTL_ALT_SELECT_SET(x) (((uint32_t)(x) << IOC_PAD_FUNC_CTL_ALT_SELECT_SHIFT) & IOC_PAD_FUNC_CTL_ALT_SELECT_MASK)
#define IOC_PAD_FUNC_CTL_ALT_SELECT_GET(x) (((uint32_t)(x) & IOC_PAD_FUNC_CTL_ALT_SELECT_MASK) >> IOC_PAD_FUNC_CTL_ALT_SELECT_SHIFT)

/* Bitfield definition for register of struct array PAD: PAD_CTL */
/*
 * HYS (RW)
 *
 * schmitt trigger enable
 * 0: disable
 * 1: enable
 */
#define IOC_PAD_PAD_CTL_HYS_MASK (0x1000000UL)
#define IOC_PAD_PAD_CTL_HYS_SHIFT (24U)
#define IOC_PAD_PAD_CTL_HYS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_HYS_SHIFT) & IOC_PAD_PAD_CTL_HYS_MASK)
#define IOC_PAD_PAD_CTL_HYS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_HYS_MASK) >> IOC_PAD_PAD_CTL_HYS_SHIFT)

/*
 * PRS (RW)
 *
 * select pull up/down internal resistance strength:
 * For pull down, only have 100 Kohm resistance
 * For pull up:
 * 00: 100 KOhm
 * 01: 47 KOhm
 * 10: 22 KOhm
 * 11: 22 KOhm
 */
#define IOC_PAD_PAD_CTL_PRS_MASK (0x300000UL)
#define IOC_PAD_PAD_CTL_PRS_SHIFT (20U)
#define IOC_PAD_PAD_CTL_PRS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_PRS_SHIFT) & IOC_PAD_PAD_CTL_PRS_MASK)
#define IOC_PAD_PAD_CTL_PRS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_PRS_MASK) >> IOC_PAD_PAD_CTL_PRS_SHIFT)

/*
 * PS (RW)
 *
 * pull select
 * 0: pull down
 * 1: pull up
 */
#define IOC_PAD_PAD_CTL_PS_MASK (0x40000UL)
#define IOC_PAD_PAD_CTL_PS_SHIFT (18U)
#define IOC_PAD_PAD_CTL_PS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_PS_SHIFT) & IOC_PAD_PAD_CTL_PS_MASK)
#define IOC_PAD_PAD_CTL_PS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_PS_MASK) >> IOC_PAD_PAD_CTL_PS_SHIFT)

/*
 * PE (RW)
 *
 * pull enable
 * 0: pull disable
 * 1: pull enable
 */
#define IOC_PAD_PAD_CTL_PE_MASK (0x20000UL)
#define IOC_PAD_PAD_CTL_PE_SHIFT (17U)
#define IOC_PAD_PAD_CTL_PE_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_PE_SHIFT) & IOC_PAD_PAD_CTL_PE_MASK)
#define IOC_PAD_PAD_CTL_PE_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_PE_MASK) >> IOC_PAD_PAD_CTL_PE_SHIFT)

/*
 * KE (RW)
 *
 * keeper capability enable
 * 0: keeper disable
 * 1: keeper enable
 */
#define IOC_PAD_PAD_CTL_KE_MASK (0x10000UL)
#define IOC_PAD_PAD_CTL_KE_SHIFT (16U)
#define IOC_PAD_PAD_CTL_KE_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_KE_SHIFT) & IOC_PAD_PAD_CTL_KE_MASK)
#define IOC_PAD_PAD_CTL_KE_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_KE_MASK) >> IOC_PAD_PAD_CTL_KE_SHIFT)

/*
 * OD (RW)
 *
 * open drain
 * 0: open drain disable
 * 1: open drain enable
 */
#define IOC_PAD_PAD_CTL_OD_MASK (0x100U)
#define IOC_PAD_PAD_CTL_OD_SHIFT (8U)
#define IOC_PAD_PAD_CTL_OD_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_OD_SHIFT) & IOC_PAD_PAD_CTL_OD_MASK)
#define IOC_PAD_PAD_CTL_OD_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_OD_MASK) >> IOC_PAD_PAD_CTL_OD_SHIFT)

/*
 * SR (RW)
 *
 * slew rate
 * 0: Slow slew rate
 * 1: Fast slew rate
 */
#define IOC_PAD_PAD_CTL_SR_MASK (0x40U)
#define IOC_PAD_PAD_CTL_SR_SHIFT (6U)
#define IOC_PAD_PAD_CTL_SR_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_SR_SHIFT) & IOC_PAD_PAD_CTL_SR_MASK)
#define IOC_PAD_PAD_CTL_SR_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_SR_MASK) >> IOC_PAD_PAD_CTL_SR_SHIFT)

/*
 * SPD (RW)
 *
 * additional 2-bit slew rate to select IO cell operation frequency range with reduced switching noise
 * 00: Slow frequency slew rate(50Mhz)
 * 01: Medium frequency slew rate(100 Mhz)
 * 10: Fast frequency slew rate(150 Mhz)
 * 11: Max frequency slew rate(200Mhz)
 */
#define IOC_PAD_PAD_CTL_SPD_MASK (0x30U)
#define IOC_PAD_PAD_CTL_SPD_SHIFT (4U)
#define IOC_PAD_PAD_CTL_SPD_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_SPD_SHIFT) & IOC_PAD_PAD_CTL_SPD_MASK)
#define IOC_PAD_PAD_CTL_SPD_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_SPD_MASK) >> IOC_PAD_PAD_CTL_SPD_SHIFT)

/*
 * DS (RW)
 *
 * drive strength
 * 1.8V Mode:
 * 000: 260 Ohm
 * 001: 260 Ohm
 * 010: 130 Ohm
 * 011: 88 Ohm
 * 100: 65 Ohm
 * 101: 52 Ohm
 * 110: 43 Ohm
 * 111: 37 Ohm
 * 3.3V Mode:
 * 000: 157 Ohm
 * 001: 157 Ohm
 * 010: 78 Ohm
 * 011: 53 Ohm
 * 100: 39 Ohm
 * 101: 32 Ohm
 * 110: 26 Ohm
 * 111: 23 Ohm
 */
#define IOC_PAD_PAD_CTL_DS_MASK (0x7U)
#define IOC_PAD_PAD_CTL_DS_SHIFT (0U)
#define IOC_PAD_PAD_CTL_DS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_DS_SHIFT) & IOC_PAD_PAD_CTL_DS_MASK)
#define IOC_PAD_PAD_CTL_DS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_DS_MASK) >> IOC_PAD_PAD_CTL_DS_SHIFT)



/* PAD register group index macro definition */
#define IOC_PAD_PA00 (0UL)
#define IOC_PAD_PA01 (1UL)
#define IOC_PAD_PA02 (2UL)
#define IOC_PAD_PA03 (3UL)
#define IOC_PAD_PA04 (4UL)
#define IOC_PAD_PA05 (5UL)
#define IOC_PAD_PA06 (6UL)
#define IOC_PAD_PA07 (7UL)
#define IOC_PAD_PA08 (8UL)
#define IOC_PAD_PA09 (9UL)
#define IOC_PAD_PA10 (10UL)
#define IOC_PAD_PA11 (11UL)
#define IOC_PAD_PA12 (12UL)
#define IOC_PAD_PA13 (13UL)
#define IOC_PAD_PA14 (14UL)
#define IOC_PAD_PA15 (15UL)
#define IOC_PAD_PA16 (16UL)
#define IOC_PAD_PA17 (17UL)
#define IOC_PAD_PA18 (18UL)
#define IOC_PAD_PA19 (19UL)
#define IOC_PAD_PA20 (20UL)
#define IOC_PAD_PA21 (21UL)
#define IOC_PAD_PA22 (22UL)
#define IOC_PAD_PA23 (23UL)
#define IOC_PAD_PA24 (24UL)
#define IOC_PAD_PA25 (25UL)
#define IOC_PAD_PA26 (26UL)
#define IOC_PAD_PA27 (27UL)
#define IOC_PAD_PA28 (28UL)
#define IOC_PAD_PA29 (29UL)
#define IOC_PAD_PA30 (30UL)
#define IOC_PAD_PA31 (31UL)
#define IOC_PAD_PB00 (32UL)
#define IOC_PAD_PB01 (33UL)
#define IOC_PAD_PB02 (34UL)
#define IOC_PAD_PB03 (35UL)
#define IOC_PAD_PB04 (36UL)
#define IOC_PAD_PB05 (37UL)
#define IOC_PAD_PB06 (38UL)
#define IOC_PAD_PB07 (39UL)
#define IOC_PAD_PB08 (40UL)
#define IOC_PAD_PB09 (41UL)
#define IOC_PAD_PB10 (42UL)
#define IOC_PAD_PB11 (43UL)
#define IOC_PAD_PB12 (44UL)
#define IOC_PAD_PB13 (45UL)
#define IOC_PAD_PB14 (46UL)
#define IOC_PAD_PB15 (47UL)
#define IOC_PAD_PB16 (48UL)
#define IOC_PAD_PB17 (49UL)
#define IOC_PAD_PB18 (50UL)
#define IOC_PAD_PB19 (51UL)
#define IOC_PAD_PB20 (52UL)
#define IOC_PAD_PB21 (53UL)
#define IOC_PAD_PB22 (54UL)
#define IOC_PAD_PB23 (55UL)
#define IOC_PAD_PB24 (56UL)
#define IOC_PAD_PB25 (57UL)
#define IOC_PAD_PB26 (58UL)
#define IOC_PAD_PB27 (59UL)
#define IOC_PAD_PB28 (60UL)
#define IOC_PAD_PB29 (61UL)
#define IOC_PAD_PB30 (62UL)
#define IOC_PAD_PB31 (63UL)
#define IOC_PAD_PC00 (64UL)
#define IOC_PAD_PC01 (65UL)
#define IOC_PAD_PC02 (66UL)
#define IOC_PAD_PC03 (67UL)
#define IOC_PAD_PC04 (68UL)
#define IOC_PAD_PC05 (69UL)
#define IOC_PAD_PC06 (70UL)
#define IOC_PAD_PC07 (71UL)
#define IOC_PAD_PC08 (72UL)
#define IOC_PAD_PC09 (73UL)
#define IOC_PAD_PC10 (74UL)
#define IOC_PAD_PC11 (75UL)
#define IOC_PAD_PC12 (76UL)
#define IOC_PAD_PC13 (77UL)
#define IOC_PAD_PC14 (78UL)
#define IOC_PAD_PC15 (79UL)
#define IOC_PAD_PC16 (80UL)
#define IOC_PAD_PC17 (81UL)
#define IOC_PAD_PC18 (82UL)
#define IOC_PAD_PC19 (83UL)
#define IOC_PAD_PC20 (84UL)
#define IOC_PAD_PC21 (85UL)
#define IOC_PAD_PC22 (86UL)
#define IOC_PAD_PC23 (87UL)
#define IOC_PAD_PC24 (88UL)
#define IOC_PAD_PC25 (89UL)
#define IOC_PAD_PC26 (90UL)
#define IOC_PAD_PC27 (91UL)
#define IOC_PAD_PX00 (416UL)
#define IOC_PAD_PX01 (417UL)
#define IOC_PAD_PX02 (418UL)
#define IOC_PAD_PX03 (419UL)
#define IOC_PAD_PX04 (420UL)
#define IOC_PAD_PX05 (421UL)
#define IOC_PAD_PX06 (422UL)
#define IOC_PAD_PX07 (423UL)
#define IOC_PAD_PY00 (448UL)
#define IOC_PAD_PY01 (449UL)
#define IOC_PAD_PY02 (450UL)
#define IOC_PAD_PY03 (451UL)
#define IOC_PAD_PY04 (452UL)
#define IOC_PAD_PY05 (453UL)
#define IOC_PAD_PY06 (454UL)
#define IOC_PAD_PY07 (455UL)
#define IOC_PAD_PZ00 (480UL)
#define IOC_PAD_PZ01 (481UL)
#define IOC_PAD_PZ02 (482UL)
#define IOC_PAD_PZ03 (483UL)
#define IOC_PAD_PZ04 (484UL)
#define IOC_PAD_PZ05 (485UL)
#define IOC_PAD_PZ06 (486UL)
#define IOC_PAD_PZ07 (487UL)


#endif /* HPM_IOC_H */

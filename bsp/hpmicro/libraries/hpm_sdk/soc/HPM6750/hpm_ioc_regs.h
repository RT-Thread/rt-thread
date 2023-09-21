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
    } PAD[492];
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
 * MS (RW)
 *
 * pin voltage select, only available in high-speed IO
 * 0: 3.3V
 * 1: 1.8V
 */
#define IOC_PAD_PAD_CTL_MS_MASK (0x4000U)
#define IOC_PAD_PAD_CTL_MS_SHIFT (14U)
#define IOC_PAD_PAD_CTL_MS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_MS_SHIFT) & IOC_PAD_PAD_CTL_MS_MASK)
#define IOC_PAD_PAD_CTL_MS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_MS_MASK) >> IOC_PAD_PAD_CTL_MS_SHIFT)

/*
 * OD (RW)
 *
 * open drain
 * 0: open drain disable
 * 1: open drain enable
 */
#define IOC_PAD_PAD_CTL_OD_MASK (0x2000U)
#define IOC_PAD_PAD_CTL_OD_SHIFT (13U)
#define IOC_PAD_PAD_CTL_OD_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_OD_SHIFT) & IOC_PAD_PAD_CTL_OD_MASK)
#define IOC_PAD_PAD_CTL_OD_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_OD_MASK) >> IOC_PAD_PAD_CTL_OD_SHIFT)

/*
 * SMT (RW)
 *
 * schmitt trigger enable, only avaiable in high-speed IO
 * 0: disable
 * 1: enable
 */
#define IOC_PAD_PAD_CTL_SMT_MASK (0x1000U)
#define IOC_PAD_PAD_CTL_SMT_SHIFT (12U)
#define IOC_PAD_PAD_CTL_SMT_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_SMT_SHIFT) & IOC_PAD_PAD_CTL_SMT_MASK)
#define IOC_PAD_PAD_CTL_SMT_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_SMT_MASK) >> IOC_PAD_PAD_CTL_SMT_SHIFT)

/*
 * PS (RW)
 *
 * pull select
 * 0: pull down
 * 1: pull up
 */
#define IOC_PAD_PAD_CTL_PS_MASK (0x800U)
#define IOC_PAD_PAD_CTL_PS_SHIFT (11U)
#define IOC_PAD_PAD_CTL_PS_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_PS_SHIFT) & IOC_PAD_PAD_CTL_PS_MASK)
#define IOC_PAD_PAD_CTL_PS_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_PS_MASK) >> IOC_PAD_PAD_CTL_PS_SHIFT)

/*
 * PE (RW)
 *
 * pull enable
 * 0: pull disable
 * 1: pull enable
 */
#define IOC_PAD_PAD_CTL_PE_MASK (0x10U)
#define IOC_PAD_PAD_CTL_PE_SHIFT (4U)
#define IOC_PAD_PAD_CTL_PE_SET(x) (((uint32_t)(x) << IOC_PAD_PAD_CTL_PE_SHIFT) & IOC_PAD_PAD_CTL_PE_MASK)
#define IOC_PAD_PAD_CTL_PE_GET(x) (((uint32_t)(x) & IOC_PAD_PAD_CTL_PE_MASK) >> IOC_PAD_PAD_CTL_PE_SHIFT)

/*
 * DS (RW)
 *
 * drive strength
 * for high-speed IO 3.3V:
 * 000: 85.61Ohm
 * 001: 61.2  Ohm
 * 010: 42.88Ohm
 * 011: 35.76Ohm
 * 111: 30.67Ohm
 * for high-speed IO 1.8V:
 * 000: 84.07Ohm
 * 001: 60.14Ohm
 * 010: 42.15Ohm
 * 011: 35.19Ohm
 * 111: 30.2  Ohm
 * for general IO:
 * 00: 4mA
 * 01: 8mA
 * 11: 12mA
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
#define IOC_PAD_PC28 (92UL)
#define IOC_PAD_PC29 (93UL)
#define IOC_PAD_PC30 (94UL)
#define IOC_PAD_PC31 (95UL)
#define IOC_PAD_PD00 (96UL)
#define IOC_PAD_PD01 (97UL)
#define IOC_PAD_PD02 (98UL)
#define IOC_PAD_PD03 (99UL)
#define IOC_PAD_PD04 (100UL)
#define IOC_PAD_PD05 (101UL)
#define IOC_PAD_PD06 (102UL)
#define IOC_PAD_PD07 (103UL)
#define IOC_PAD_PD08 (104UL)
#define IOC_PAD_PD09 (105UL)
#define IOC_PAD_PD10 (106UL)
#define IOC_PAD_PD11 (107UL)
#define IOC_PAD_PD12 (108UL)
#define IOC_PAD_PD13 (109UL)
#define IOC_PAD_PD14 (110UL)
#define IOC_PAD_PD15 (111UL)
#define IOC_PAD_PD16 (112UL)
#define IOC_PAD_PD17 (113UL)
#define IOC_PAD_PD18 (114UL)
#define IOC_PAD_PD19 (115UL)
#define IOC_PAD_PD20 (116UL)
#define IOC_PAD_PD21 (117UL)
#define IOC_PAD_PD22 (118UL)
#define IOC_PAD_PD23 (119UL)
#define IOC_PAD_PD24 (120UL)
#define IOC_PAD_PD25 (121UL)
#define IOC_PAD_PD26 (122UL)
#define IOC_PAD_PD27 (123UL)
#define IOC_PAD_PD28 (124UL)
#define IOC_PAD_PD29 (125UL)
#define IOC_PAD_PD30 (126UL)
#define IOC_PAD_PD31 (127UL)
#define IOC_PAD_PE00 (128UL)
#define IOC_PAD_PE01 (129UL)
#define IOC_PAD_PE02 (130UL)
#define IOC_PAD_PE03 (131UL)
#define IOC_PAD_PE04 (132UL)
#define IOC_PAD_PE05 (133UL)
#define IOC_PAD_PE06 (134UL)
#define IOC_PAD_PE07 (135UL)
#define IOC_PAD_PE08 (136UL)
#define IOC_PAD_PE09 (137UL)
#define IOC_PAD_PE10 (138UL)
#define IOC_PAD_PE11 (139UL)
#define IOC_PAD_PE12 (140UL)
#define IOC_PAD_PE13 (141UL)
#define IOC_PAD_PE14 (142UL)
#define IOC_PAD_PE15 (143UL)
#define IOC_PAD_PE16 (144UL)
#define IOC_PAD_PE17 (145UL)
#define IOC_PAD_PE18 (146UL)
#define IOC_PAD_PE19 (147UL)
#define IOC_PAD_PE20 (148UL)
#define IOC_PAD_PE21 (149UL)
#define IOC_PAD_PE22 (150UL)
#define IOC_PAD_PE23 (151UL)
#define IOC_PAD_PE24 (152UL)
#define IOC_PAD_PE25 (153UL)
#define IOC_PAD_PE26 (154UL)
#define IOC_PAD_PE27 (155UL)
#define IOC_PAD_PE28 (156UL)
#define IOC_PAD_PE29 (157UL)
#define IOC_PAD_PE30 (158UL)
#define IOC_PAD_PE31 (159UL)
#define IOC_PAD_PF00 (160UL)
#define IOC_PAD_PF01 (161UL)
#define IOC_PAD_PF02 (162UL)
#define IOC_PAD_PF03 (163UL)
#define IOC_PAD_PF04 (164UL)
#define IOC_PAD_PF05 (165UL)
#define IOC_PAD_PF06 (166UL)
#define IOC_PAD_PF07 (167UL)
#define IOC_PAD_PF08 (168UL)
#define IOC_PAD_PF09 (169UL)
#define IOC_PAD_PF10 (170UL)
#define IOC_PAD_PX00 (416UL)
#define IOC_PAD_PX01 (417UL)
#define IOC_PAD_PX02 (418UL)
#define IOC_PAD_PX03 (419UL)
#define IOC_PAD_PX04 (420UL)
#define IOC_PAD_PX05 (421UL)
#define IOC_PAD_PX06 (422UL)
#define IOC_PAD_PX07 (423UL)
#define IOC_PAD_PX08 (424UL)
#define IOC_PAD_PX09 (425UL)
#define IOC_PAD_PX10 (426UL)
#define IOC_PAD_PX11 (427UL)
#define IOC_PAD_PY00 (448UL)
#define IOC_PAD_PY01 (449UL)
#define IOC_PAD_PY02 (450UL)
#define IOC_PAD_PY03 (451UL)
#define IOC_PAD_PY04 (452UL)
#define IOC_PAD_PY05 (453UL)
#define IOC_PAD_PY06 (454UL)
#define IOC_PAD_PY07 (455UL)
#define IOC_PAD_PY08 (456UL)
#define IOC_PAD_PY09 (457UL)
#define IOC_PAD_PY10 (458UL)
#define IOC_PAD_PY11 (459UL)
#define IOC_PAD_PZ00 (480UL)
#define IOC_PAD_PZ01 (481UL)
#define IOC_PAD_PZ02 (482UL)
#define IOC_PAD_PZ03 (483UL)
#define IOC_PAD_PZ04 (484UL)
#define IOC_PAD_PZ05 (485UL)
#define IOC_PAD_PZ06 (486UL)
#define IOC_PAD_PZ07 (487UL)
#define IOC_PAD_PZ08 (488UL)
#define IOC_PAD_PZ09 (489UL)
#define IOC_PAD_PZ10 (490UL)
#define IOC_PAD_PZ11 (491UL)


#endif /* HPM_IOC_H */

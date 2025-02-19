/***********************************************************************************************************************
 * Copyright [2020-2024] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RZN2L
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_rzn2l
{
    ELC_EVENT_INTCPU0        = (0),    // Software interrupt 0
    ELC_EVENT_INTCPU1        = (1),    // Software interrupt 1
    ELC_EVENT_INTCPU2        = (2),    // Software interrupt 2
    ELC_EVENT_INTCPU3        = (3),    // Software interrupt 3
    ELC_EVENT_INTCPU4        = (4),    // Software interrupt 4
    ELC_EVENT_INTCPU5        = (5),    // Software interrupt 5
    ELC_EVENT_IRQ0           = (6),    // External pin interrupt 0
    ELC_EVENT_IRQ1           = (7),    // External pin interrupt 1
    ELC_EVENT_IRQ2           = (8),    // External pin interrupt 2
    ELC_EVENT_IRQ3           = (9),    // External pin interrupt 3
    ELC_EVENT_IRQ4           = (10),   // External pin interrupt 4
    ELC_EVENT_IRQ5           = (11),   // External pin interrupt 5
    ELC_EVENT_IRQ6           = (12),   // External pin interrupt 6
    ELC_EVENT_IRQ7           = (13),   // External pin interrupt 7
    ELC_EVENT_IRQ8           = (14),   // External pin interrupt 8
    ELC_EVENT_IRQ9           = (15),   // External pin interrupt 9
    ELC_EVENT_IRQ10          = (16),   // External pin interrupt 10
    ELC_EVENT_IRQ11          = (17),   // External pin interrupt 11
    ELC_EVENT_IRQ12          = (18),   // External pin interrupt 12
    ELC_EVENT_IRQ13          = (19),   // External pin interrupt 13
    ELC_EVENT_BSC_CMI        = (20),   // Refresh compare match interrupt
    ELC_EVENT_DMAC0_INT0     = (21),   // DMAC0 transfer completion 0
    ELC_EVENT_DMAC0_INT1     = (22),   // DMAC0 transfer completion 1
    ELC_EVENT_DMAC0_INT2     = (23),   // DMAC0 transfer completion 2
    ELC_EVENT_DMAC0_INT3     = (24),   // DMAC0 transfer completion 3
    ELC_EVENT_DMAC0_INT4     = (25),   // DMAC0 transfer completion 4
    ELC_EVENT_DMAC0_INT5     = (26),   // DMAC0 transfer completion 5
    ELC_EVENT_DMAC0_INT6     = (27),   // DMAC0 transfer completion 6
    ELC_EVENT_DMAC0_INT7     = (28),   // DMAC0 transfer completion 7
    ELC_EVENT_DMAC1_INT0     = (37),   // DMAC1 transfer completion 0
    ELC_EVENT_DMAC1_INT1     = (38),   // DMAC1 transfer completion 1
    ELC_EVENT_DMAC1_INT2     = (39),   // DMAC1 transfer completion 2
    ELC_EVENT_DMAC1_INT3     = (40),   // DMAC1 transfer completion 3
    ELC_EVENT_DMAC1_INT4     = (41),   // DMAC1 transfer completion 4
    ELC_EVENT_DMAC1_INT5     = (42),   // DMAC1 transfer completion 5
    ELC_EVENT_DMAC1_INT6     = (43),   // DMAC1 transfer completion 6
    ELC_EVENT_DMAC1_INT7     = (44),   // DMAC1 transfer completion 7
    ELC_EVENT_CMT0_CMI       = (53),   // CMT0 Compare match
    ELC_EVENT_CMT1_CMI       = (54),   // CMT1 Compare match
    ELC_EVENT_CMT2_CMI       = (55),   // CMT2 Compare match
    ELC_EVENT_CMT3_CMI       = (56),   // CMT3 Compare match
    ELC_EVENT_CMT4_CMI       = (57),   // CMT4 Compare match
    ELC_EVENT_CMT5_CMI       = (58),   // CMT5 Compare match
    ELC_EVENT_CMTW0_CMWI     = (59),   // CMTW0 Compare match
    ELC_EVENT_CMTW0_IC0I     = (60),   // CMTW0 Input capture of register 0
    ELC_EVENT_CMTW0_IC1I     = (61),   // CMTW0 Input capture of register 1
    ELC_EVENT_CMTW0_OC0I     = (62),   // CMTW0 Output compare of register 0
    ELC_EVENT_CMTW0_OC1I     = (63),   // CMTW0 Output compare of register 1
    ELC_EVENT_CMTW1_CMWI     = (64),   // CMTW1 Compare match
    ELC_EVENT_CMTW1_IC0I     = (65),   // CMTW1 Input capture of register 0
    ELC_EVENT_CMTW1_IC1I     = (66),   // CMTW1 Input capture of register 1
    ELC_EVENT_CMTW1_OC0I     = (67),   // CMTW1 Output compare of register 0
    ELC_EVENT_CMTW1_OC1I     = (68),   // CMTW1 Output compare of register 1
    ELC_EVENT_TGIA0          = (69),   // MTU0.TGRA input capture/compare match
    ELC_EVENT_TGIB0          = (70),   // MTU0.TGRB input capture/compare match
    ELC_EVENT_TGIC0          = (71),   // MTU0.TGRC input capture/compare match
    ELC_EVENT_TGID0          = (72),   // MTU0.TGRD input capture/compare match
    ELC_EVENT_TCIV0          = (73),   // MTU0.TCNT overflow
    ELC_EVENT_TGIE0          = (74),   // MTU0.TGRE compare match
    ELC_EVENT_TGIF0          = (75),   // MTU0.TGRF compare match
    ELC_EVENT_TGIA1          = (76),   // MTU1.TGRA input capture/compare match
    ELC_EVENT_TGIB1          = (77),   // MTU1.TGRB input capture/compare match
    ELC_EVENT_TCIV1          = (78),   // MTU1.TCNT overflow
    ELC_EVENT_TCIU1          = (79),   // MTU1.TCNT underflow
    ELC_EVENT_TGIA2          = (80),   // MTU2.TGRA input capture/compare match
    ELC_EVENT_TGIB2          = (81),   // MTU2.TGRB input capture/compare match
    ELC_EVENT_TCIV2          = (82),   // MTU2.TCNT overflow
    ELC_EVENT_TCIU2          = (83),   // MTU2.TCNT underflow
    ELC_EVENT_TGIA3          = (84),   // MTU3.TGRA input capture/compare match
    ELC_EVENT_TGIB3          = (85),   // MTU3.TGRB input capture/compare match
    ELC_EVENT_TGIC3          = (86),   // MTU3.TGRC input capture/compare match
    ELC_EVENT_TGID3          = (87),   // MTU3.TGRD input capture/compare match
    ELC_EVENT_TCIV3          = (88),   // MTU3.TCNT overflow
    ELC_EVENT_TGIA4          = (89),   // MTU4.TGRA input capture/compare match
    ELC_EVENT_TGIB4          = (90),   // MTU4.TGRB input capture/compare match
    ELC_EVENT_TGIC4          = (91),   // MTU4.TGRC input capture/compare match
    ELC_EVENT_TGID4          = (92),   // MTU4.TGRD input capture/compare match
    ELC_EVENT_TCIV4          = (93),   // MTU4.TCNT overflow/underflow
    ELC_EVENT_TGIU5          = (94),   // MTU5.TGRU input capture/compare match
    ELC_EVENT_TGIV5          = (95),   // MTU5.TGRV input capture/compare match
    ELC_EVENT_TGIW5          = (96),   // MTU5.TGRW input capture/compare match
    ELC_EVENT_TGIA6          = (97),   // MTU6.TGRA input capture/compare match
    ELC_EVENT_TGIB6          = (98),   // MTU6.TGRB input capture/compare match
    ELC_EVENT_TGIC6          = (99),   // MTU6.TGRC input capture/compare match
    ELC_EVENT_TGID6          = (100),  // MTU6.TGRD input capture/compare match
    ELC_EVENT_TCIV6          = (101),  // MTU6.TCNT overflow
    ELC_EVENT_TGIA7          = (102),  // MTU7.TGRA input capture/compare match
    ELC_EVENT_TGIB7          = (103),  // MTU7.TGRB input capture/compare match
    ELC_EVENT_TGIC7          = (104),  // MTU7.TGRC input capture/compare match
    ELC_EVENT_TGID7          = (105),  // MTU7.TGRD input capture/compare match
    ELC_EVENT_TCIV7          = (106),  // MTU7.TCNT overflow/underflow
    ELC_EVENT_TGIA8          = (107),  // MTU8.TGRA input capture/compare match
    ELC_EVENT_TGIB8          = (108),  // MTU8.TGRB input capture/compare match
    ELC_EVENT_TGIC8          = (109),  // MTU8.TGRC input capture/compare match
    ELC_EVENT_TGID8          = (110),  // MTU8.TGRD input capture/compare match
    ELC_EVENT_TCIV8          = (111),  // MTU8.TCNT overflow
    ELC_EVENT_OEI1           = (112),  // Output enable interrupt 1
    ELC_EVENT_OEI2           = (113),  // Output enable interrupt 2
    ELC_EVENT_OEI3           = (114),  // Output enable interrupt 3
    ELC_EVENT_OEI4           = (115),  // Output enable interrupt 4
    ELC_EVENT_GPT0_CCMPA     = (116),  // GPT0 GTCCRA input capture/compare match
    ELC_EVENT_GPT0_CCMPB     = (117),  // GPT0 GTCCRB input capture/compare match
    ELC_EVENT_GPT0_CMPC      = (118),  // GPT0 GTCCRC compare match
    ELC_EVENT_GPT0_CMPD      = (119),  // GPT0 GTCCRD compare match
    ELC_EVENT_GPT0_CMPE      = (120),  // GPT0 GTCCRE compare match
    ELC_EVENT_GPT0_CMPF      = (121),  // GPT0 GTCCRF compare match
    ELC_EVENT_GPT0_OVF       = (122),  // GPT0 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT0_UDF       = (123),  // GPT0 GTCNT underflow
    ELC_EVENT_GPT0_DTE       = (124),  // GPT0 Dead time error
    ELC_EVENT_GPT1_CCMPA     = (125),  // GPT1 GTCCRA input capture/compare match
    ELC_EVENT_GPT1_CCMPB     = (126),  // GPT1 GTCCRB input capture/compare match
    ELC_EVENT_GPT1_CMPC      = (127),  // GPT1 GTCCRC compare match
    ELC_EVENT_GPT1_CMPD      = (128),  // GPT1 GTCCRD compare match
    ELC_EVENT_GPT1_CMPE      = (129),  // GPT1 GTCCRE compare match
    ELC_EVENT_GPT1_CMPF      = (130),  // GPT1 GTCCRF compare match
    ELC_EVENT_GPT1_OVF       = (131),  // GPT1 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT1_UDF       = (132),  // GPT1 GTCNT underflow
    ELC_EVENT_GPT1_DTE       = (133),  // GPT1 Dead time error
    ELC_EVENT_GPT2_CCMPA     = (134),  // GPT2 GTCCRA input capture/compare match
    ELC_EVENT_GPT2_CCMPB     = (135),  // GPT2 GTCCRB input capture/compare match
    ELC_EVENT_GPT2_CMPC      = (136),  // GPT2 GTCCRC compare match
    ELC_EVENT_GPT2_CMPD      = (137),  // GPT2 GTCCRD compare match
    ELC_EVENT_GPT2_CMPE      = (138),  // GPT2 GTCCRE compare match
    ELC_EVENT_GPT2_CMPF      = (139),  // GPT2 GTCCRF compare match
    ELC_EVENT_GPT2_OVF       = (140),  // GPT2 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT2_UDF       = (141),  // GPT2 GTCNT underflow
    ELC_EVENT_GPT2_DTE       = (142),  // GPT2 Dead time error
    ELC_EVENT_GPT3_CCMPA     = (143),  // GPT3 GTCCRA input capture/compare match
    ELC_EVENT_GPT3_CCMPB     = (144),  // GPT3 GTCCRB input capture/compare match
    ELC_EVENT_GPT3_CMPC      = (145),  // GPT3 GTCCRC compare match
    ELC_EVENT_GPT3_CMPD      = (146),  // GPT3 GTCCRD compare match
    ELC_EVENT_GPT3_CMPE      = (147),  // GPT3 GTCCRE compare match
    ELC_EVENT_GPT3_CMPF      = (148),  // GPT3 GTCCRF compare match
    ELC_EVENT_GPT3_OVF       = (149),  // GPT3 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT3_UDF       = (150),  // GPT3 GTCNT underflow
    ELC_EVENT_GPT3_DTE       = (151),  // GPT3 Dead time error
    ELC_EVENT_GPT4_CCMPA     = (152),  // GPT4 GTCCRA input capture/compare match
    ELC_EVENT_GPT4_CCMPB     = (153),  // GPT4 GTCCRB input capture/compare match
    ELC_EVENT_GPT4_CMPC      = (154),  // GPT4 GTCCRC compare match
    ELC_EVENT_GPT4_CMPD      = (155),  // GPT4 GTCCRD compare match
    ELC_EVENT_GPT4_CMPE      = (156),  // GPT4 GTCCRE compare match
    ELC_EVENT_GPT4_CMPF      = (157),  // GPT4 GTCCRF compare match
    ELC_EVENT_GPT4_OVF       = (158),  // GPT4 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT4_UDF       = (159),  // GPT4 GTCNT underflow
    ELC_EVENT_GPT4_DTE       = (160),  // GPT4 Dead time error
    ELC_EVENT_GPT5_CCMPA     = (161),  // GPT5 GTCCRA input capture/compare match
    ELC_EVENT_GPT5_CCMPB     = (162),  // GPT5 GTCCRB input capture/compare match
    ELC_EVENT_GPT5_CMPC      = (163),  // GPT5 GTCCRC compare match
    ELC_EVENT_GPT5_CMPD      = (164),  // GPT5 GTCCRD compare match
    ELC_EVENT_GPT5_CMPE      = (165),  // GPT5 GTCCRE compare match
    ELC_EVENT_GPT5_CMPF      = (166),  // GPT5 GTCCRF compare match
    ELC_EVENT_GPT5_OVF       = (167),  // GPT5 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT5_UDF       = (168),  // GPT5 GTCNT underflow
    ELC_EVENT_GPT5_DTE       = (169),  // GPT5 Dead time error
    ELC_EVENT_GPT6_CCMPA     = (170),  // GPT6 GTCCRA input capture/compare match
    ELC_EVENT_GPT6_CCMPB     = (171),  // GPT6 GTCCRB input capture/compare match
    ELC_EVENT_GPT6_CMPC      = (172),  // GPT6 GTCCRC compare match
    ELC_EVENT_GPT6_CMPD      = (173),  // GPT6 GTCCRD compare match
    ELC_EVENT_GPT6_CMPE      = (174),  // GPT6 GTCCRE compare match
    ELC_EVENT_GPT6_CMPF      = (175),  // GPT6 GTCCRF compare match
    ELC_EVENT_GPT6_OVF       = (176),  // GPT6 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT6_UDF       = (177),  // GPT6 GTCNT underflow
    ELC_EVENT_GPT6_DTE       = (178),  // GPT6 Dead time error
    ELC_EVENT_GPT7_CCMPA     = (179),  // GPT7 GTCCRA input capture/compare match
    ELC_EVENT_GPT7_CCMPB     = (180),  // GPT7 GTCCRB input capture/compare match
    ELC_EVENT_GPT7_CMPC      = (181),  // GPT7 GTCCRC compare match
    ELC_EVENT_GPT7_CMPD      = (182),  // GPT7 GTCCRD compare match
    ELC_EVENT_GPT7_CMPE      = (183),  // GPT7 GTCCRE compare match
    ELC_EVENT_GPT7_CMPF      = (184),  // GPT7 GTCCRF compare match
    ELC_EVENT_GPT7_OVF       = (185),  // GPT7 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT7_UDF       = (186),  // GPT7 GTCNT underflow
    ELC_EVENT_GPT7_DTE       = (187),  // GPT7 Dead time error
    ELC_EVENT_GPT8_CCMPA     = (188),  // GPT8 GTCCRA input capture/compare match
    ELC_EVENT_GPT8_CCMPB     = (189),  // GPT8 GTCCRB input capture/compare match
    ELC_EVENT_GPT8_CMPC      = (190),  // GPT8 GTCCRC compare match
    ELC_EVENT_GPT8_CMPD      = (191),  // GPT8 GTCCRD compare match
    ELC_EVENT_GPT8_CMPE      = (192),  // GPT8 GTCCRE compare match
    ELC_EVENT_GPT8_CMPF      = (193),  // GPT8 GTCCRF compare match
    ELC_EVENT_GPT8_OVF       = (194),  // GPT8 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT8_UDF       = (195),  // GPT8 GTCNT underflow
    ELC_EVENT_GPT8_DTE       = (196),  // GPT8 Dead time error
    ELC_EVENT_GPT9_CCMPA     = (197),  // GPT9 GTCCRA input capture/compare match
    ELC_EVENT_GPT9_CCMPB     = (198),  // GPT9 GTCCRB input capture/compare match
    ELC_EVENT_GPT9_CMPC      = (199),  // GPT9 GTCCRC compare match
    ELC_EVENT_GPT9_CMPD      = (200),  // GPT9 GTCCRD compare match
    ELC_EVENT_GPT9_CMPE      = (201),  // GPT9 GTCCRE compare match
    ELC_EVENT_GPT9_CMPF      = (202),  // GPT9 GTCCRF compare match
    ELC_EVENT_GPT9_OVF       = (203),  // GPT9 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT9_UDF       = (204),  // GPT9 GTCNT underflow
    ELC_EVENT_GPT9_DTE       = (205),  // GPT9 Dead time error
    ELC_EVENT_GPT10_CCMPA    = (206),  // GPT10 GTCCRA input capture/compare match
    ELC_EVENT_GPT10_CCMPB    = (207),  // GPT10 GTCCRB input capture/compare match
    ELC_EVENT_GPT10_CMPC     = (208),  // GPT10 GTCCRC compare match
    ELC_EVENT_GPT10_CMPD     = (209),  // GPT10 GTCCRD compare match
    ELC_EVENT_GPT10_CMPE     = (210),  // GPT10 GTCCRE compare match
    ELC_EVENT_GPT10_CMPF     = (211),  // GPT10 GTCCRF compare match
    ELC_EVENT_GPT10_OVF      = (212),  // GPT10 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT10_UDF      = (213),  // GPT10 GTCNT underflow
    ELC_EVENT_GPT10_DTE      = (214),  // GPT10 Dead time error
    ELC_EVENT_GPT11_CCMPA    = (215),  // GPT11 GTCCRA input capture/compare match
    ELC_EVENT_GPT11_CCMPB    = (216),  // GPT11 GTCCRB input capture/compare match
    ELC_EVENT_GPT11_CMPC     = (217),  // GPT11 GTCCRC compare match
    ELC_EVENT_GPT11_CMPD     = (218),  // GPT11 GTCCRD compare match
    ELC_EVENT_GPT11_CMPE     = (219),  // GPT11 GTCCRE compare match
    ELC_EVENT_GPT11_CMPF     = (220),  // GPT11 GTCCRF compare match
    ELC_EVENT_GPT11_OVF      = (221),  // GPT11 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT11_UDF      = (222),  // GPT11 GTCNT underflow
    ELC_EVENT_GPT11_DTE      = (223),  // GPT11 Dead time error
    ELC_EVENT_GPT12_CCMPA    = (224),  // GPT12 GTCCRA input capture/compare match
    ELC_EVENT_GPT12_CCMPB    = (225),  // GPT12 GTCCRB input capture/compare match
    ELC_EVENT_GPT12_CMPC     = (226),  // GPT12 GTCCRC compare match
    ELC_EVENT_GPT12_CMPD     = (227),  // GPT12 GTCCRD compare match
    ELC_EVENT_GPT12_CMPE     = (228),  // GPT12 GTCCRE compare match
    ELC_EVENT_GPT12_CMPF     = (229),  // GPT12 GTCCRF compare match
    ELC_EVENT_GPT12_OVF      = (230),  // GPT12 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT12_UDF      = (231),  // GPT12 GTCNT underflow
    ELC_EVENT_GPT12_DTE      = (232),  // GPT12 Dead time error
    ELC_EVENT_GPT13_CCMPA    = (233),  // GPT13 GTCCRA input capture/compare match
    ELC_EVENT_GPT13_CCMPB    = (234),  // GPT13 GTCCRB input capture/compare match
    ELC_EVENT_GPT13_CMPC     = (235),  // GPT13 GTCCRC compare match
    ELC_EVENT_GPT13_CMPD     = (236),  // GPT13 GTCCRD compare match
    ELC_EVENT_GPT13_CMPE     = (237),  // GPT13 GTCCRE compare match
    ELC_EVENT_GPT13_CMPF     = (238),  // GPT13 GTCCRF compare match
    ELC_EVENT_GPT13_OVF      = (239),  // GPT13 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT13_UDF      = (240),  // GPT13 GTCNT underflow
    ELC_EVENT_GPT13_DTE      = (241),  // GPT13 Dead time error
    ELC_EVENT_POEG0_GROUP0   = (242),  // POEG group A interrupt for channels in LLPP
    ELC_EVENT_POEG0_GROUP1   = (243),  // POEG group B interrupt for channels in LLPP
    ELC_EVENT_POEG0_GROUP2   = (244),  // POEG group C interrupt for channels in LLPP
    ELC_EVENT_POEG0_GROUP3   = (245),  // POEG group D interrupt for channels in LLPP
    ELC_EVENT_POEG1_GROUP0   = (246),  // POEG group A interrupt for channels in NONSAFETY
    ELC_EVENT_POEG1_GROUP1   = (247),  // POEG group B interrupt for channels in NONSAFETY
    ELC_EVENT_POEG1_GROUP2   = (248),  // POEG group C interrupt for channels in NONSAFETY
    ELC_EVENT_POEG1_GROUP3   = (249),  // POEG group D interrupt for channels in NONSAFETY
    ELC_EVENT_GMAC_LPI       = (250),  // GMAC1 energy efficient
    ELC_EVENT_GMAC_PMT       = (251),  // GMAC1 power management
    ELC_EVENT_GMAC_SBD       = (252),  // GMAC1 general interrupt
    ELC_EVENT_ETHSW_INTR     = (253),  // Ethernet Switch interrupt
    ELC_EVENT_ETHSW_DLR      = (254),  // Ethernet Switch DLR interrupt
    ELC_EVENT_ETHSW_PRP      = (255),  // Ethernet Switch PRP interrupt
    ELC_EVENT_ETHSW_IHUB     = (256),  // Ethernet Switch Integrated Hub interrupt
    ELC_EVENT_ETHSW_PTRN0    = (257),  // Ethernet Switch RX Pattern Matcher interrupt 0
    ELC_EVENT_ETHSW_PTRN1    = (258),  // Ethernet Switch RX Pattern Matcher interrupt 1
    ELC_EVENT_ETHSW_PTRN2    = (259),  // Ethernet Switch RX Pattern Matcher interrupt 2
    ELC_EVENT_ETHSW_PTRN3    = (260),  // Ethernet Switch RX Pattern Matcher interrupt 3
    ELC_EVENT_ETHSW_PTRN4    = (261),  // Ethernet Switch RX Pattern Matcher interrupt 4
    ELC_EVENT_ETHSW_PTRN5    = (262),  // Ethernet Switch RX Pattern Matcher interrupt 5
    ELC_EVENT_ETHSW_PTRN6    = (263),  // Ethernet Switch RX Pattern Matcher interrupt 6
    ELC_EVENT_ETHSW_PTRN7    = (264),  // Ethernet Switch RX Pattern Matcher interrupt 7
    ELC_EVENT_ETHSW_PTRN8    = (265),  // Ethernet Switch RX Pattern Matcher interrupt 8
    ELC_EVENT_ETHSW_PTRN9    = (266),  // Ethernet Switch RX Pattern Matcher interrupt 9
    ELC_EVENT_ETHSW_PTRN10   = (267),  // Ethernet Switch RX Pattern Matcher interrupt 10
    ELC_EVENT_ETHSW_PTRN11   = (268),  // Ethernet Switch RX Pattern Matcher interrupt 11
    ELC_EVENT_ETHSW_PTPOUT0  = (269),  // Ethernet switch timer pulse output 0
    ELC_EVENT_ETHSW_PTPOUT1  = (270),  // Ethernet switch timer pulse output 1
    ELC_EVENT_ETHSW_PTPOUT2  = (271),  // Ethernet switch timer pulse output 2
    ELC_EVENT_ETHSW_PTPOUT3  = (272),  // Ethernet switch timer pulse output 3
    ELC_EVENT_ETHSW_TDMAOUT0 = (273),  // Ethernet Switch TDMA timer output 0
    ELC_EVENT_ETHSW_TDMAOUT1 = (274),  // Ethernet Switch TDMA timer output 1
    ELC_EVENT_ETHSW_TDMAOUT2 = (275),  // Ethernet Switch TDMA timer output 2
    ELC_EVENT_ETHSW_TDMAOUT3 = (276),  // Ethernet Switch TDMA timer output 3
    ELC_EVENT_ESC_SYNC0      = (277),  // EtherCAT Sync0 interrupt
    ELC_EVENT_ESC_SYNC1      = (278),  // EtherCAT Sync1 interrupt
    ELC_EVENT_ESC_CAT        = (279),  // EtherCAT interrupt
    ELC_EVENT_ESC_SOF        = (280),  // EtherCAT SOF interrupt
    ELC_EVENT_ESC_EOF        = (281),  // EtherCAT EOF interrupt
    ELC_EVENT_ESC_WDT        = (282),  // EtherCAT WDT interrupt
    ELC_EVENT_ESC_RST        = (283),  // EtherCAT RESET interrupt
    ELC_EVENT_USB_HI         = (284),  // USB (Host) interrupt
    ELC_EVENT_USB_FI         = (285),  // USB (Function) interrupt
    ELC_EVENT_USB_FDMA0      = (286),  // USB (Function) DMA 0 transmit completion
    ELC_EVENT_USB_FDMA1      = (287),  // USB (Function) DMA 1 transmit completion
    ELC_EVENT_SCI0_ERI       = (288),  // SCI0 Receive error
    ELC_EVENT_SCI0_RXI       = (289),  // SCI0 Receive data full
    ELC_EVENT_SCI0_TXI       = (290),  // SCI0 Transmit data empty
    ELC_EVENT_SCI0_TEI       = (291),  // SCI0 Transmit end
    ELC_EVENT_SCI1_ERI       = (292),  // SCI1 Receive error
    ELC_EVENT_SCI1_RXI       = (293),  // SCI1 Receive data full
    ELC_EVENT_SCI1_TXI       = (294),  // SCI1 Transmit data empty
    ELC_EVENT_SCI1_TEI       = (295),  // SCI1 Transmit end
    ELC_EVENT_SCI2_ERI       = (296),  // SCI2 Receive error
    ELC_EVENT_SCI2_RXI       = (297),  // SCI2 Receive data full
    ELC_EVENT_SCI2_TXI       = (298),  // SCI2 Transmit data empty
    ELC_EVENT_SCI2_TEI       = (299),  // SCI2 Transmit end
    ELC_EVENT_SCI3_ERI       = (300),  // SCI3 Receive error
    ELC_EVENT_SCI3_RXI       = (301),  // SCI3 Receive data full
    ELC_EVENT_SCI3_TXI       = (302),  // SCI3 Transmit data empty
    ELC_EVENT_SCI3_TEI       = (303),  // SCI3 Transmit end
    ELC_EVENT_SCI4_ERI       = (304),  // SCI4 Receive error
    ELC_EVENT_SCI4_RXI       = (305),  // SCI4 Receive data full
    ELC_EVENT_SCI4_TXI       = (306),  // SCI4 Transmit data empty
    ELC_EVENT_SCI4_TEI       = (307),  // SCI4 Transmit end
    ELC_EVENT_IIC0_EEI       = (308),  // IIC0 Transfer error or event generation
    ELC_EVENT_IIC0_RXI       = (309),  // IIC0 Receive data full
    ELC_EVENT_IIC0_TXI       = (310),  // IIC0 Transmit data empty
    ELC_EVENT_IIC0_TEI       = (311),  // IIC0 Transmit end
    ELC_EVENT_IIC1_EEI       = (312),  // IIC1 Transfer error or event generation
    ELC_EVENT_IIC1_RXI       = (313),  // IIC1 Receive data full
    ELC_EVENT_IIC1_TXI       = (314),  // IIC1 Transmit data empty
    ELC_EVENT_IIC1_TEI       = (315),  // IIC1 Transmit end
    ELC_EVENT_CAN_RXF        = (316),  // CANFD RX FIFO interrupt
    ELC_EVENT_CAN_GLERR      = (317),  // CANFD Global error interrupt
    ELC_EVENT_CAN0_TX        = (318),  // CAFND0 Channel TX interrupt
    ELC_EVENT_CAN0_CHERR     = (319),  // CAFND0 Channel CAN error interrupt
    ELC_EVENT_CAN0_COMFRX    = (320),  // CAFND0 Common RX FIFO or TXQ interrupt
    ELC_EVENT_CAN1_TX        = (321),  // CAFND1 Channel TX interrupt
    ELC_EVENT_CAN1_CHERR     = (322),  // CAFND1 Channel CAN error interrupt
    ELC_EVENT_CAN1_COMFRX    = (323),  // CAFND1 Common RX FIFO or TXQ interrupt
    ELC_EVENT_SPI0_SPRI      = (324),  // SPI0 Reception buffer full
    ELC_EVENT_SPI0_SPTI      = (325),  // SPI0 Transmit buffer empty
    ELC_EVENT_SPI0_SPII      = (326),  // SPI0 SPI idle
    ELC_EVENT_SPI0_SPEI      = (327),  // SPI0 errors
    ELC_EVENT_SPI0_SPCEND    = (328),  // SPI0 Communication complete
    ELC_EVENT_SPI1_SPRI      = (329),  // SPI1 Reception buffer full
    ELC_EVENT_SPI1_SPTI      = (330),  // SPI1 Transmit buffer empty
    ELC_EVENT_SPI1_SPII      = (331),  // SPI1 SPI idle
    ELC_EVENT_SPI1_SPEI      = (332),  // SPI1 errors
    ELC_EVENT_SPI1_SPCEND    = (333),  // SPI1 Communication complete
    ELC_EVENT_SPI2_SPRI      = (334),  // SPI2 Reception buffer full
    ELC_EVENT_SPI2_SPTI      = (335),  // SPI2 Transmit buffer empty
    ELC_EVENT_SPI2_SPII      = (336),  // SPI2 SPI idle
    ELC_EVENT_SPI2_SPEI      = (337),  // SPI2 errors
    ELC_EVENT_SPI2_SPCEND    = (338),  // SPI2 Communication complete
    ELC_EVENT_XSPI0_INT      = (339),  // xSPI0 Interrupt
    ELC_EVENT_XSPI0_INTERR   = (340),  // xSPI0 Error interrupt
    ELC_EVENT_XSPI1_INT      = (341),  // xSPI1 Interrupt
    ELC_EVENT_XSPI1_INTERR   = (342),  // xSPI1 Error interrupt
    ELC_EVENT_DSMIF0_CDRUI   = (343),  // DSMIF0 current data register update (ORed ch0 to ch2)
    ELC_EVENT_DSMIF1_CDRUI   = (344),  // DSMIF1 current data register update (ORed ch3 to ch5)
    ELC_EVENT_ADC0_ADI       = (345),  // ADC0 A/D scan end interrupt
    ELC_EVENT_ADC0_GBADI     = (346),  // ADC0 A/D scan end interrupt for Group B
    ELC_EVENT_ADC0_GCADI     = (347),  // ADC0 A/D scan end interrupt for Group C
    ELC_EVENT_ADC0_CMPAI     = (348),  // ADC0 Window A compare match
    ELC_EVENT_ADC0_CMPBI     = (349),  // ADC0 Window B compare match
    ELC_EVENT_ADC1_ADI       = (350),  // ADC1 A/D scan end interrupt
    ELC_EVENT_ADC1_GBADI     = (351),  // ADC1 A/D scan end interrupt for Group B
    ELC_EVENT_ADC1_GCADI     = (352),  // ADC1 A/D scan end interrupt for Group C
    ELC_EVENT_ADC1_CMPAI     = (353),  // ADC1 Window A compare match
    ELC_EVENT_ADC1_CMPBI     = (354),  // ADC1 Window B compare match
    ELC_EVENT_MBX_INT0       = (372),  // Mailbox (Host CPU to Cortex-R52) interrupt 0
    ELC_EVENT_MBX_INT1       = (373),  // Mailbox (Host CPU to Cortex-R52) interrupt 1
    ELC_EVENT_MBX_INT2       = (374),  // Mailbox (Host CPU to Cortex-R52) interrupt 2
    ELC_EVENT_MBX_INT3       = (375),  // Mailbox (Host CPU to Cortex-R52) interrupt 3
    ELC_EVENT_CPU0_ERR0      = (384),  // Cortex-R52 CPU0 error event 0
    ELC_EVENT_CPU0_ERR1      = (385),  // Cortex-R52 CPU0 error event 1
    ELC_EVENT_PERI_ERR0      = (388),  // Peripherals error event 0
    ELC_EVENT_PERI_ERR1      = (389),  // Peripherals error event 1
    ELC_EVENT_SHOST_INT      = (390),  // SHOSTIF interrupt
    ELC_EVENT_PHOST_INT      = (391),  // PHOSTIF interrupt
    ELC_EVENT_INTCPU6        = (392),  // Software interrupt 6
    ELC_EVENT_INTCPU7        = (393),  // Software interrupt 7
    ELC_EVENT_IRQ14          = (394),  // External pin interrupt 14
    ELC_EVENT_IRQ15          = (395),  // External pin interrupt 15
    ELC_EVENT_GPT14_CCMPA    = (396),  // GPT14 GTCCRA input capture/compare match
    ELC_EVENT_GPT14_CCMPB    = (397),  // GPT14 GTCCRB input capture/compare match
    ELC_EVENT_GPT14_CMPC     = (398),  // GPT14 GTCCRC compare match
    ELC_EVENT_GPT14_CMPD     = (399),  // GPT14 GTCCRD compare match
    ELC_EVENT_GPT14_CMPE     = (400),  // GPT14 GTCCRE compare match
    ELC_EVENT_GPT14_CMPF     = (401),  // GPT14 GTCCRF compare match
    ELC_EVENT_GPT14_OVF      = (402),  // GPT14 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT14_UDF      = (403),  // GPT14 GTCNT underflow
    ELC_EVENT_GPT15_CCMPA    = (404),  // GPT15 GTCCRA input capture/compare match
    ELC_EVENT_GPT15_CCMPB    = (405),  // GPT15 GTCCRB input capture/compare match
    ELC_EVENT_GPT15_CMPC     = (406),  // GPT15 GTCCRC compare match
    ELC_EVENT_GPT15_CMPD     = (407),  // GPT15 GTCCRD compare match
    ELC_EVENT_GPT15_CMPE     = (408),  // GPT15 GTCCRE compare match
    ELC_EVENT_GPT15_CMPF     = (409),  // GPT15 GTCCRF compare match
    ELC_EVENT_GPT15_OVF      = (410),  // GPT15 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT15_UDF      = (411),  // GPT15 GTCNT underflow
    ELC_EVENT_GPT16_CCMPA    = (412),  // GPT16 GTCCRA input capture/compare match
    ELC_EVENT_GPT16_CCMPB    = (413),  // GPT16 GTCCRB input capture/compare match
    ELC_EVENT_GPT16_CMPC     = (414),  // GPT16 GTCCRC compare match
    ELC_EVENT_GPT16_CMPD     = (415),  // GPT16 GTCCRD compare match
    ELC_EVENT_GPT16_CMPE     = (416),  // GPT16 GTCCRE compare match
    ELC_EVENT_GPT16_CMPF     = (417),  // GPT16 GTCCRF compare match
    ELC_EVENT_GPT16_OVF      = (418),  // GPT16 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT16_UDF      = (419),  // GPT16 GTCNT underflow
    ELC_EVENT_GPT17_CCMPA    = (420),  // GPT17 GTCCRA input capture/compare match
    ELC_EVENT_GPT17_CCMPB    = (421),  // GPT17 GTCCRB input capture/compare match
    ELC_EVENT_GPT17_CMPC     = (422),  // GPT17 GTCCRC compare match
    ELC_EVENT_GPT17_CMPD     = (423),  // GPT17 GTCCRD compare match
    ELC_EVENT_GPT17_CMPE     = (424),  // GPT17 GTCCRE compare match
    ELC_EVENT_GPT17_CMPF     = (425),  // GPT17 GTCCRF compare match
    ELC_EVENT_GPT17_OVF      = (426),  // GPT17 GTCNT overflow (GTPR compare match)
    ELC_EVENT_GPT17_UDF      = (427),  // GPT17 GTCNT underflow
    ELC_EVENT_POEG2_GROUP0   = (428),  // POEG group A interrupt for channels in SAFETY
    ELC_EVENT_POEG2_GROUP1   = (429),  // POEG group B interrupt for channels in SAFETY
    ELC_EVENT_POEG2_GROUP2   = (430),  // POEG group C interrupt for channels in SAFETY
    ELC_EVENT_POEG2_GROUP3   = (431),  // POEG group D interrupt for channels in SAFETY
    ELC_EVENT_RTC_ALM        = (432),  // Alarm interrupt
    ELC_EVENT_RTC_1S         = (433),  // 1 second interrupt
    ELC_EVENT_RTC_PRD        = (434),  // Fixed interval interrupt
    ELC_EVENT_SCI5_ERI       = (435),  // SCI5 Receive error
    ELC_EVENT_SCI5_RXI       = (436),  // SCI5 Receive data full
    ELC_EVENT_SCI5_TXI       = (437),  // SCI5 Transmit data empty
    ELC_EVENT_SCI5_TEI       = (438),  // SCI5 Transmit end
    ELC_EVENT_IIC2_EEI       = (439),  // IIC2 Transfer error or event generation
    ELC_EVENT_IIC2_RXI       = (440),  // IIC2 Receive data full
    ELC_EVENT_IIC2_TXI       = (441),  // IIC2 Transmit data empty
    ELC_EVENT_IIC2_TEI       = (442),  // IIC2 Transmit end
    ELC_EVENT_SPI3_SPRI      = (443),  // SPI3 Reception buffer full
    ELC_EVENT_SPI3_SPTI      = (444),  // SPI3 Transmit buffer empty
    ELC_EVENT_SPI3_SPII      = (445),  // SPI3 SPI idle
    ELC_EVENT_SPI3_SPEI      = (446),  // SPI3 errors
    ELC_EVENT_SPI3_SPCEND    = (447),  // SPI3 Communication complete
    ELC_EVENT_DREQ           = (448),  // External DMA request
    ELC_EVENT_CAN_RF_DMAREQ0 = (449),  // CAFND RX FIFO 0 DMA request
    ELC_EVENT_CAN_RF_DMAREQ1 = (450),  // CAFND RX FIFO 1 DMA request
    ELC_EVENT_CAN_RF_DMAREQ2 = (451),  // CAFND RX FIFO 2 DMA request
    ELC_EVENT_CAN_RF_DMAREQ3 = (452),  // CAFND RX FIFO 3 DMA request
    ELC_EVENT_CAN_RF_DMAREQ4 = (453),  // CAFND RX FIFO 4 DMA request
    ELC_EVENT_CAN_RF_DMAREQ5 = (454),  // CAFND RX FIFO 5 DMA request
    ELC_EVENT_CAN_RF_DMAREQ6 = (455),  // CAFND RX FIFO 6 DMA request
    ELC_EVENT_CAN_RF_DMAREQ7 = (456),  // CAFND RX FIFO 7 DMA request
    ELC_EVENT_CAN0_CF_DMAREQ = (457),  // CAFND0 First common FIFO DMA request
    ELC_EVENT_CAN1_CF_DMAREQ = (458),  // CAFND1 First common FIFO DMA request
    ELC_EVENT_ADC0_WCMPM     = (459),  // ADC0 compare match
    ELC_EVENT_ADC0_WCMPUM    = (460),  // ADC0 compare mismatch
    ELC_EVENT_ADC1_WCMPM     = (461),  // ADC1 compare match
    ELC_EVENT_ADC1_WCMPUM    = (462),  // ADC1 compare mismatch
    ELC_EVENT_TCIV4_OF       = (463),  // MTU4.TCNT overflow
    ELC_EVENT_TCIV4_UF       = (464),  // MTU4.TCNT underflow
    ELC_EVENT_TCIV7_OF       = (465),  // MTU7.TCNT overflow
    ELC_EVENT_TCIV7_UF       = (466),  // MTU7.TCNT underflow
    ELC_EVENT_IOPORT_GROUP1  = (467),  // Input edge detection of input port group 1
    ELC_EVENT_IOPORT_GROUP2  = (468),  // Input edge detection of input port group 2
    ELC_EVENT_IOPORT_SINGLE0 = (469),  // Input edge detection of single input port 0
    ELC_EVENT_IOPORT_SINGLE1 = (470),  // Input edge detection of single input port 1
    ELC_EVENT_IOPORT_SINGLE2 = (471),  // Input edge detection of single input port 2
    ELC_EVENT_IOPORT_SINGLE3 = (472),  // Input edge detection of single input port 3
    ELC_EVENT_GPT0_ADTRGA    = (473),  // GPT0 GTADTRA compare match
    ELC_EVENT_GPT0_ADTRGB    = (474),  // GPT0 GTADTRB compare match
    ELC_EVENT_GPT1_ADTRGA    = (475),  // GPT1 GTADTRA compare match
    ELC_EVENT_GPT1_ADTRGB    = (476),  // GPT1 GTADTRB compare match
    ELC_EVENT_GPT2_ADTRGA    = (477),  // GPT2 GTADTRA compare match
    ELC_EVENT_GPT2_ADTRGB    = (478),  // GPT2 GTADTRB compare match
    ELC_EVENT_GPT3_ADTRGA    = (479),  // GPT3 GTADTRA compare match
    ELC_EVENT_GPT3_ADTRGB    = (480),  // GPT3 GTADTRB compare match
    ELC_EVENT_GPT4_ADTRGA    = (481),  // GPT4 GTADTRA compare match
    ELC_EVENT_GPT4_ADTRGB    = (482),  // GPT4 GTADTRB compare match
    ELC_EVENT_GPT5_ADTRGA    = (483),  // GPT5 GTADTRA compare match
    ELC_EVENT_GPT5_ADTRGB    = (484),  // GPT5 GTADTRB compare match
    ELC_EVENT_GPT6_ADTRGA    = (485),  // GPT6 GTADTRA compare match
    ELC_EVENT_GPT6_ADTRGB    = (486),  // GPT6 GTADTRB compare match
    ELC_EVENT_GPT7_ADTRGA    = (487),  // GPT7 GTADTRA compare match
    ELC_EVENT_GPT7_ADTRGB    = (488),  // GPT7 GTADTRB compare match
    ELC_EVENT_GPT8_ADTRGA    = (489),  // GPT8 GTADTRA compare match
    ELC_EVENT_GPT8_ADTRGB    = (490),  // GPT8 GTADTRB compare match
    ELC_EVENT_GPT9_ADTRGA    = (491),  // GPT9 GTADTRA compare match
    ELC_EVENT_GPT9_ADTRGB    = (492),  // GPT9 GTADTRB compare match
    ELC_EVENT_GPT10_ADTRGA   = (493),  // GPT10 GTADTRA compare match
    ELC_EVENT_GPT10_ADTRGB   = (494),  // GPT10 GTADTRB compare match
    ELC_EVENT_GPT11_ADTRGA   = (495),  // GPT11 GTADTRA compare match
    ELC_EVENT_GPT11_ADTRGB   = (496),  // GPT11 GTADTRB compare match
    ELC_EVENT_GPT12_ADTRGA   = (497),  // GPT12 GTADTRA compare match
    ELC_EVENT_GPT12_ADTRGB   = (498),  // GPT12 GTADTRB compare match
    ELC_EVENT_GPT13_ADTRGA   = (499),  // GPT13 GTADTRA compare match
    ELC_EVENT_GPT13_ADTRGB   = (500),  // GPT13 GTADTRB compare match
    ELC_EVENT_NONE
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RZN2L) */

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif

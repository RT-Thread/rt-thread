/***********************************************************************************************************************
 * Copyright [2020-2021] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

#ifndef BSP_ELC_H
#define BSP_ELC_H

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA6M3
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra6m3
{
    ELC_EVENT_NONE                      = (0),   // Link disabled
    ELC_EVENT_ICU_IRQ0                  = (1),   // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                  = (2),   // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                  = (3),   // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                  = (4),   // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                  = (5),   // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                  = (6),   // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                  = (7),   // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                  = (8),   // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8                  = (9),   // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9                  = (10),  // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10                 = (11),  // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11                 = (12),  // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12                 = (13),  // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13                 = (14),  // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14                 = (15),  // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15                 = (16),  // External pin interrupt 15
    ELC_EVENT_DMAC0_INT                 = (32),  // DMAC transfer end 0
    ELC_EVENT_DMAC1_INT                 = (33),  // DMAC transfer end 1
    ELC_EVENT_DMAC2_INT                 = (34),  // DMAC transfer end 2
    ELC_EVENT_DMAC3_INT                 = (35),  // DMAC transfer end 3
    ELC_EVENT_DMAC4_INT                 = (36),  // DMAC transfer end 4
    ELC_EVENT_DMAC5_INT                 = (37),  // DMAC transfer end 5
    ELC_EVENT_DMAC6_INT                 = (38),  // DMAC transfer end 6
    ELC_EVENT_DMAC7_INT                 = (39),  // DMAC transfer end 7
    ELC_EVENT_DTC_COMPLETE              = (41),  // DTC last transfer
    ELC_EVENT_DTC_END                   = (42),  // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL         = (45),  // Canceling from Snooze mode
    ELC_EVENT_FCU_FIFERR                = (48),  // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI                 = (49),  // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                  = (56),  // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                  = (57),  // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP             = (59),  // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST        = (60),  // Snooze entry
    ELC_EVENT_AGT0_INT                  = (64),  // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A            = (65),  // Compare match A
    ELC_EVENT_AGT0_COMPARE_B            = (66),  // Compare match B
    ELC_EVENT_AGT1_INT                  = (67),  // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A            = (68),  // Compare match A
    ELC_EVENT_AGT1_COMPARE_B            = (69),  // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW            = (70),  // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW             = (71),  // WDT underflow
    ELC_EVENT_RTC_ALARM                 = (72),  // Alarm interrupt
    ELC_EVENT_RTC_PERIOD                = (73),  // Periodic interrupt
    ELC_EVENT_RTC_CARRY                 = (74),  // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END             = (75),  // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B           = (76),  // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A             = (77),  // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B             = (78),  // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH        = (79),  // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH     = (80),  // Compare mismatch
    ELC_EVENT_ADC1_SCAN_END             = (81),  // A/D scan end interrupt
    ELC_EVENT_ADC1_SCAN_END_B           = (82),  // A/D scan end interrupt for group B
    ELC_EVENT_ADC1_WINDOW_A             = (83),  // Window A Compare match
    ELC_EVENT_ADC1_WINDOW_B             = (84),  // Window B Compare match
    ELC_EVENT_ADC1_COMPARE_MATCH        = (85),  // Compare match
    ELC_EVENT_ADC1_COMPARE_MISMATCH     = (86),  // Compare mismatch
    ELC_EVENT_ACMPHS0_INT               = (87),  // Comparator interrupt 0
    ELC_EVENT_ACMPHS1_INT               = (88),  // Comparator interrupt 1
    ELC_EVENT_ACMPHS2_INT               = (89),  // Comparator interrupt 2
    ELC_EVENT_ACMPHS3_INT               = (90),  // Comparator interrupt 3
    ELC_EVENT_ACMPHS4_INT               = (91),  // Comparator interrupt 4
    ELC_EVENT_ACMPHS5_INT               = (92),  // Comparator interrupt 5
    ELC_EVENT_USBFS_FIFO_0              = (95),  // DMA transfer request 0
    ELC_EVENT_USBFS_FIFO_1              = (96),  // DMA transfer request 1
    ELC_EVENT_USBFS_INT                 = (97),  // USBFS interrupt
    ELC_EVENT_USBFS_RESUME              = (98),  // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI                  = (99),  // Receive data full
    ELC_EVENT_IIC0_TXI                  = (100), // Transmit data empty
    ELC_EVENT_IIC0_TEI                  = (101), // Transmit end
    ELC_EVENT_IIC0_ERI                  = (102), // Transfer error
    ELC_EVENT_IIC0_WUI                  = (103), // Slave address match
    ELC_EVENT_IIC1_RXI                  = (104), // Receive data full
    ELC_EVENT_IIC1_TXI                  = (105), // Transmit data empty
    ELC_EVENT_IIC1_TEI                  = (106), // Transmit end
    ELC_EVENT_IIC1_ERI                  = (107), // Transfer error
    ELC_EVENT_IIC2_RXI                  = (109), // Receive data full
    ELC_EVENT_IIC2_TXI                  = (110), // Transmit data empty
    ELC_EVENT_IIC2_TEI                  = (111), // Transmit end
    ELC_EVENT_IIC2_ERI                  = (112), // Transfer error
    ELC_EVENT_SSI0_TXI                  = (114), // Transmit data empty
    ELC_EVENT_SSI0_RXI                  = (115), // Receive data full
    ELC_EVENT_SSI0_INT                  = (117), // Error interrupt
    ELC_EVENT_SSI1_TXI_RXI              = (120), // Receive data full/Transmit data empty
    ELC_EVENT_SSI1_INT                  = (121), // Error interrupt
    ELC_EVENT_SRC_INPUT_FIFO_EMPTY      = (122), // Input FIFO empty
    ELC_EVENT_SRC_OUTPUT_FIFO_FULL      = (123), // Output FIFO full
    ELC_EVENT_SRC_OUTPUT_FIFO_OVERFLOW  = (124), // Output FIFO overflow
    ELC_EVENT_SRC_OUTPUT_FIFO_UNDERFLOW = (125), // Output FIFO underflow
    ELC_EVENT_SRC_CONVERSION_END        = (126), // Conversion end
    ELC_EVENT_PDC_RECEIVE_DATA_READY    = (127), // Receive data ready interrupt
    ELC_EVENT_PDC_FRAME_END             = (128), // Frame end interrupt
    ELC_EVENT_PDC_INT                   = (129), // Error interrupt
    ELC_EVENT_CTSU_WRITE                = (130), // Write request interrupt
    ELC_EVENT_CTSU_READ                 = (131), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END                  = (132), // Measurement end interrupt
    ELC_EVENT_KEY_INT                   = (133), // Key interrupt
    ELC_EVENT_DOC_INT                   = (134), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR       = (135), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END       = (136), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW              = (137), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR                = (138), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX              = (139), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX              = (140), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX           = (141), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX           = (142), // Transmission complete interrupt
    ELC_EVENT_CAN1_ERROR                = (143), // Error interrupt
    ELC_EVENT_CAN1_FIFO_RX              = (144), // Receive FIFO interrupt
    ELC_EVENT_CAN1_FIFO_TX              = (145), // Transmit FIFO interrupt
    ELC_EVENT_CAN1_MAILBOX_RX           = (146), // Reception complete interrupt
    ELC_EVENT_CAN1_MAILBOX_TX           = (147), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1            = (148), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2            = (149), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3            = (150), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4            = (151), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0      = (152), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1      = (153), // Software event 1
    ELC_EVENT_POEG0_EVENT               = (154), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT               = (155), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT               = (156), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT               = (157), // Port Output disable interrupt D
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A    = (176), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B    = (177), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C            = (178), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D            = (179), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E            = (180), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F            = (181), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW     = (182), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW    = (183), // Underflow
    ELC_EVENT_GPT0_AD_TRIG_A            = (184), // A/D converter start request A
    ELC_EVENT_GPT0_AD_TRIG_B            = (185), // A/D converter start request B
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A    = (186), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B    = (187), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C            = (188), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D            = (189), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E            = (190), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F            = (191), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW     = (192), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW    = (193), // Underflow
    ELC_EVENT_GPT1_AD_TRIG_A            = (194), // A/D converter start request A
    ELC_EVENT_GPT1_AD_TRIG_B            = (195), // A/D converter start request B
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A    = (196), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B    = (197), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C            = (198), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D            = (199), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E            = (200), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F            = (201), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW     = (202), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW    = (203), // Underflow
    ELC_EVENT_GPT2_AD_TRIG_A            = (204), // A/D converter start request A
    ELC_EVENT_GPT2_AD_TRIG_B            = (205), // A/D converter start request B
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A    = (206), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B    = (207), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C            = (208), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D            = (209), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E            = (210), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F            = (211), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW     = (212), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW    = (213), // Underflow
    ELC_EVENT_GPT3_AD_TRIG_A            = (214), // A/D converter start request A
    ELC_EVENT_GPT3_AD_TRIG_B            = (215), // A/D converter start request B
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A    = (216), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B    = (217), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C            = (218), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D            = (219), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E            = (220), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F            = (221), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW     = (222), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW    = (223), // Underflow
    ELC_EVENT_GPT4_AD_TRIG_A            = (224), // A/D converter start request A
    ELC_EVENT_GPT4_AD_TRIG_B            = (225), // A/D converter start request B
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A    = (226), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B    = (227), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C            = (228), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D            = (229), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E            = (230), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F            = (231), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW     = (232), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW    = (233), // Underflow
    ELC_EVENT_GPT5_AD_TRIG_A            = (234), // A/D converter start request A
    ELC_EVENT_GPT5_AD_TRIG_B            = (235), // A/D converter start request B
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A    = (236), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B    = (237), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C            = (238), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D            = (239), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E            = (240), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F            = (241), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW     = (242), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW    = (243), // Underflow
    ELC_EVENT_GPT6_AD_TRIG_A            = (244), // A/D converter start request A
    ELC_EVENT_GPT6_AD_TRIG_B            = (245), // A/D converter start request B
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A    = (246), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B    = (247), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C            = (248), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D            = (249), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E            = (250), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F            = (251), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW     = (252), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW    = (253), // Underflow
    ELC_EVENT_GPT7_AD_TRIG_A            = (254), // A/D converter start request A
    ELC_EVENT_GPT7_AD_TRIG_B            = (255), // A/D converter start request B
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A    = (256), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B    = (257), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C            = (258), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D            = (259), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E            = (260), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F            = (261), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW     = (262), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW    = (263), // Underflow
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A    = (266), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B    = (267), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C            = (268), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D            = (269), // Compare match D
    ELC_EVENT_GPT9_COMPARE_E            = (270), // Compare match E
    ELC_EVENT_GPT9_COMPARE_F            = (271), // Compare match F
    ELC_EVENT_GPT9_COUNTER_OVERFLOW     = (272), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW    = (273), // Underflow
    ELC_EVENT_GPT10_CAPTURE_COMPARE_A   = (276), // Compare match A
    ELC_EVENT_GPT10_CAPTURE_COMPARE_B   = (277), // Compare match B
    ELC_EVENT_GPT10_COMPARE_C           = (278), // Compare match C
    ELC_EVENT_GPT10_COMPARE_D           = (279), // Compare match D
    ELC_EVENT_GPT10_COMPARE_E           = (280), // Compare match E
    ELC_EVENT_GPT10_COMPARE_F           = (281), // Compare match F
    ELC_EVENT_GPT10_COUNTER_OVERFLOW    = (282), // Overflow
    ELC_EVENT_GPT10_COUNTER_UNDERFLOW   = (283), // Underflow
    ELC_EVENT_GPT11_CAPTURE_COMPARE_A   = (286), // Compare match A
    ELC_EVENT_GPT11_CAPTURE_COMPARE_B   = (287), // Compare match B
    ELC_EVENT_GPT11_COMPARE_C           = (288), // Compare match C
    ELC_EVENT_GPT11_COMPARE_D           = (289), // Compare match D
    ELC_EVENT_GPT11_COMPARE_E           = (290), // Compare match E
    ELC_EVENT_GPT11_COMPARE_F           = (291), // Compare match F
    ELC_EVENT_GPT11_COUNTER_OVERFLOW    = (292), // Overflow
    ELC_EVENT_GPT11_COUNTER_UNDERFLOW   = (293), // Underflow
    ELC_EVENT_GPT12_CAPTURE_COMPARE_A   = (296), // Compare match A
    ELC_EVENT_GPT12_CAPTURE_COMPARE_B   = (297), // Compare match B
    ELC_EVENT_GPT12_COMPARE_C           = (298), // Compare match C
    ELC_EVENT_GPT12_COMPARE_D           = (299), // Compare match D
    ELC_EVENT_GPT12_COMPARE_E           = (300), // Compare match E
    ELC_EVENT_GPT12_COMPARE_F           = (301), // Compare match F
    ELC_EVENT_GPT12_COUNTER_OVERFLOW    = (302), // Overflow
    ELC_EVENT_GPT12_COUNTER_UNDERFLOW   = (303), // Underflow
    ELC_EVENT_GPT13_CAPTURE_COMPARE_A   = (306), // Compare match A
    ELC_EVENT_GPT13_CAPTURE_COMPARE_B   = (307), // Compare match B
    ELC_EVENT_GPT13_COMPARE_C           = (308), // Compare match C
    ELC_EVENT_GPT13_COMPARE_D           = (309), // Compare match D
    ELC_EVENT_GPT13_COMPARE_E           = (310), // Compare match E
    ELC_EVENT_GPT13_COMPARE_F           = (311), // Compare match F
    ELC_EVENT_GPT13_COUNTER_OVERFLOW    = (312), // Overflow
    ELC_EVENT_GPT13_COUNTER_UNDERFLOW   = (313), // Underflow
    ELC_EVENT_OPS_UVW_EDGE              = (336), // UVW edge event
    ELC_EVENT_EPTPC_IPLS                = (352), // STCA interrupt
    ELC_EVENT_EPTPC_MINT                = (353), // SYNFP0/1 interrupt
    ELC_EVENT_EPTPC_PINT                = (354), // PTPEDMAC interrupt
    ELC_EVENT_EDMAC0_EINT               = (355), // EDMAC 0 interrupt
    ELC_EVENT_EPTPC_TIMER0_RISE         = (357), // Pulse output timer 0 rising edge detection
    ELC_EVENT_EPTPC_TIMER1_RISE         = (358), // Pulse output timer 1 rising edge detection
    ELC_EVENT_EPTPC_TIMER2_RISE         = (359), // Pulse output timer 2 rising edge detection
    ELC_EVENT_EPTPC_TIMER3_RISE         = (360), // Pulse output timer 3 rising edge detection
    ELC_EVENT_EPTPC_TIMER4_RISE         = (361), // Pulse output timer 4 rising edge detection
    ELC_EVENT_EPTPC_TIMER5_RISE         = (362), // Pulse output timer 5 rising edge detection
    ELC_EVENT_EPTPC_TIMER0_FALL         = (363), // Pulse output timer 0 falling edge detection
    ELC_EVENT_EPTPC_TIMER1_FALL         = (364), // Pulse output timer 1 falling edge detection
    ELC_EVENT_EPTPC_TIMER2_FALL         = (365), // Pulse output timer 2 falling edge detection
    ELC_EVENT_EPTPC_TIMER3_FALL         = (366), // Pulse output timer 3 falling edge detection
    ELC_EVENT_EPTPC_TIMER4_FALL         = (367), // Pulse output timer 4 falling edge detection
    ELC_EVENT_EPTPC_TIMER5_FALL         = (368), // Pulse output timer 5 falling edge detection
    ELC_EVENT_USBHS_FIFO_0              = (369), // DMA transfer request 0
    ELC_EVENT_USBHS_FIFO_1              = (370), // DMA transfer request 1
    ELC_EVENT_USBHS_USB_INT_RESUME      = (371), // USBHS interrupt
    ELC_EVENT_SCI0_RXI                  = (372), // Receive data full
    ELC_EVENT_SCI0_TXI                  = (373), // Transmit data empty
    ELC_EVENT_SCI0_TEI                  = (374), // Transmit end
    ELC_EVENT_SCI0_ERI                  = (375), // Receive error
    ELC_EVENT_SCI0_AM                   = (376), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI           = (377), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI                  = (378), // Received data full
    ELC_EVENT_SCI1_TXI                  = (379), // Transmit data empty
    ELC_EVENT_SCI1_TEI                  = (380), // Transmit end
    ELC_EVENT_SCI1_ERI                  = (381), // Receive error
    ELC_EVENT_SCI1_AM                   = (382), // Address match event
    ELC_EVENT_SCI2_RXI                  = (384), // Received data full
    ELC_EVENT_SCI2_TXI                  = (385), // Transmit data empty
    ELC_EVENT_SCI2_TEI                  = (386), // Transmit end
    ELC_EVENT_SCI2_ERI                  = (387), // Receive error
    ELC_EVENT_SCI2_AM                   = (388), // Address match event
    ELC_EVENT_SCI3_RXI                  = (390), // Received data full
    ELC_EVENT_SCI3_TXI                  = (391), // Transmit data empty
    ELC_EVENT_SCI3_TEI                  = (392), // Transmit end
    ELC_EVENT_SCI3_ERI                  = (393), // Receive error
    ELC_EVENT_SCI3_AM                   = (394), // Address match event
    ELC_EVENT_SCI4_RXI                  = (396), // Received data full
    ELC_EVENT_SCI4_TXI                  = (397), // Transmit data empty
    ELC_EVENT_SCI4_TEI                  = (398), // Transmit end
    ELC_EVENT_SCI4_ERI                  = (399), // Receive error
    ELC_EVENT_SCI4_AM                   = (400), // Address match event
    ELC_EVENT_SCI5_RXI                  = (402), // Received data full
    ELC_EVENT_SCI5_TXI                  = (403), // Transmit data empty
    ELC_EVENT_SCI5_TEI                  = (404), // Transmit end
    ELC_EVENT_SCI5_ERI                  = (405), // Receive error
    ELC_EVENT_SCI5_AM                   = (406), // Address match event
    ELC_EVENT_SCI6_RXI                  = (408), // Received data full
    ELC_EVENT_SCI6_TXI                  = (409), // Transmit data empty
    ELC_EVENT_SCI6_TEI                  = (410), // Transmit end
    ELC_EVENT_SCI6_ERI                  = (411), // Receive error
    ELC_EVENT_SCI6_AM                   = (412), // Address match event
    ELC_EVENT_SCI7_RXI                  = (414), // Received data full
    ELC_EVENT_SCI7_TXI                  = (415), // Transmit data empty
    ELC_EVENT_SCI7_TEI                  = (416), // Transmit end
    ELC_EVENT_SCI7_ERI                  = (417), // Receive error
    ELC_EVENT_SCI7_AM                   = (418), // Address match event
    ELC_EVENT_SCI8_RXI                  = (420), // Received data full
    ELC_EVENT_SCI8_TXI                  = (421), // Transmit data empty
    ELC_EVENT_SCI8_TEI                  = (422), // Transmit end
    ELC_EVENT_SCI8_ERI                  = (423), // Receive error
    ELC_EVENT_SCI8_AM                   = (424), // Address match event
    ELC_EVENT_SCI9_RXI                  = (426), // Received data full
    ELC_EVENT_SCI9_TXI                  = (427), // Transmit data empty
    ELC_EVENT_SCI9_TEI                  = (428), // Transmit end
    ELC_EVENT_SCI9_ERI                  = (429), // Receive error
    ELC_EVENT_SCI9_AM                   = (430), // Address match event
    ELC_EVENT_SPI0_RXI                  = (444), // Receive buffer full
    ELC_EVENT_SPI0_TXI                  = (445), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE                 = (446), // Idle
    ELC_EVENT_SPI0_ERI                  = (447), // Error
    ELC_EVENT_SPI0_TEI                  = (448), // Transmission complete event
    ELC_EVENT_SPI1_RXI                  = (449), // Receive buffer full
    ELC_EVENT_SPI1_TXI                  = (450), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE                 = (451), // Idle
    ELC_EVENT_SPI1_ERI                  = (452), // Error
    ELC_EVENT_SPI1_TEI                  = (453), // Transmission complete event
    ELC_EVENT_QSPI_INT                  = (454), // Error
    ELC_EVENT_SDHIMMC0_ACCS             = (455), // Card access
    ELC_EVENT_SDHIMMC0_SDIO             = (456), // SDIO access
    ELC_EVENT_SDHIMMC0_CARD             = (457), // Card detect
    ELC_EVENT_SDHIMMC0_DMA_REQ          = (458), // DMA transfer request
    ELC_EVENT_SDHIMMC1_ACCS             = (459), // Card access
    ELC_EVENT_SDHIMMC1_SDIO             = (460), // SDIO access
    ELC_EVENT_SDHIMMC1_CARD             = (461), // Card detect
    ELC_EVENT_SDHIMMC1_DMA_REQ          = (462), // DMA transfer request
    ELC_EVENT_SCE_PROC_BUSY             = (481),
    ELC_EVENT_SCE_ROMOK                 = (482),
    ELC_EVENT_SCE_LONG_PLG              = (483),
    ELC_EVENT_SCE_TEST_BUSY             = (484),
    ELC_EVENT_SCE_WRRDY_0               = (485),
    ELC_EVENT_SCE_WRRDY_1               = (486),
    ELC_EVENT_SCE_WRRDY_4               = (487),
    ELC_EVENT_SCE_RDRDY_0               = (488),
    ELC_EVENT_SCE_RDRDY_1               = (489),
    ELC_EVENT_SCE_INTEGRATE_WRRDY       = (490),
    ELC_EVENT_SCE_INTEGRATE_RDRDY       = (491),
    ELC_EVENT_GLCDC_LINE_DETECT         = (506), // Specified line
    ELC_EVENT_GLCDC_UNDERFLOW_1         = (507), // Graphic 1 underflow
    ELC_EVENT_GLCDC_UNDERFLOW_2         = (508), // Graphic 2 underflow
    ELC_EVENT_DRW_INT                   = (509), // DRW interrupt
    ELC_EVENT_JPEG_JEDI                 = (510), // Compression/decompression process interrupt
    ELC_EVENT_JPEG_JDTI                 = (511), // Data transfer interrupt
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA6M3) */

#endif

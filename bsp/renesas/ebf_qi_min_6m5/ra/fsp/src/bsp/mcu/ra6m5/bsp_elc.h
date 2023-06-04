/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************
 * @addtogroup BSP_MCU_RA6M5
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra6m5
{
    ELC_EVENT_NONE                   = (0),     // Link disabled
    ELC_EVENT_ICU_IRQ0               = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5               = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6               = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8               = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9               = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10              = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11              = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12              = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13              = (0x00E), // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14              = (0x00F), // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15              = (0x010), // External pin interrupt 15
    ELC_EVENT_DMAC0_INT              = (0x020), // DMAC transfer end 0
    ELC_EVENT_DMAC1_INT              = (0x021), // DMAC transfer end 1
    ELC_EVENT_DMAC2_INT              = (0x022), // DMAC transfer end 2
    ELC_EVENT_DMAC3_INT              = (0x023), // DMAC transfer end 3
    ELC_EVENT_DMAC4_INT              = (0x024), // DMAC transfer end 4
    ELC_EVENT_DMAC5_INT              = (0x025), // DMAC transfer end 5
    ELC_EVENT_DMAC6_INT              = (0x026), // DMAC transfer end 6
    ELC_EVENT_DMAC7_INT              = (0x027), // DMAC transfer end 7
    ELC_EVENT_DTC_COMPLETE           = (0x029), // DTC transfer complete
    ELC_EVENT_DTC_END                = (0x02A), // DTC transfer end
    ELC_EVENT_DMA_TRANSERR           = (0x02B), // DTC transfer error
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (0x02D), // Canceling from Snooze mode
    ELC_EVENT_FCU_FIFERR             = (0x030), // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI              = (0x031), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (0x038), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (0x039), // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP          = (0x03B), // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (0x03C), // Snooze entry
    ELC_EVENT_AGT0_INT               = (0x040), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (0x041), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (0x042), // Compare match B
    ELC_EVENT_AGT1_INT               = (0x043), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (0x044), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (0x045), // Compare match B
    ELC_EVENT_AGT2_INT               = (0x046), // AGT interrupt
    ELC_EVENT_AGT2_COMPARE_A         = (0x047), // Compare match A
    ELC_EVENT_AGT2_COMPARE_B         = (0x048), // Compare match B
    ELC_EVENT_AGT3_INT               = (0x049), // AGT interrupt
    ELC_EVENT_AGT3_COMPARE_A         = (0x04A), // Compare match A
    ELC_EVENT_AGT3_COMPARE_B         = (0x04B), // Compare match B
    ELC_EVENT_AGT4_INT               = (0x04C), // AGT interrupt
    ELC_EVENT_AGT4_COMPARE_A         = (0x04D), // Compare match A
    ELC_EVENT_AGT4_COMPARE_B         = (0x04E), // Compare match B
    ELC_EVENT_AGT5_INT               = (0x04F), // AGT interrupt
    ELC_EVENT_AGT5_COMPARE_A         = (0x050), // Compare match A
    ELC_EVENT_AGT5_COMPARE_B         = (0x051), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (0x052), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (0x053), // WDT underflow
    ELC_EVENT_RTC_ALARM              = (0x054), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD             = (0x055), // Periodic interrupt
    ELC_EVENT_RTC_CARRY              = (0x056), // Carry interrupt
    ELC_EVENT_CAN_RXF                = (0x059), // Global recieve FIFO interrupt
    ELC_EVENT_CAN_GLERR              = (0x05A), // Global error
    ELC_EVENT_CAN_DMAREQ0            = (0x05B), // DMA 0 request
    ELC_EVENT_CAN_DMAREQ1            = (0x05C), // DMA 1 request
    ELC_EVENT_CAN_DMAREQ2            = (0x05D), // DMA 2 request
    ELC_EVENT_CAN_DMAREQ3            = (0x05E), // DMA 3 request
    ELC_EVENT_CAN_DMAREQ4            = (0x05F), // DMA 4 request
    ELC_EVENT_CAN_DMAREQ5            = (0x060), // DMA 5 request
    ELC_EVENT_CAN_DMAREQ6            = (0x061), // DMA 6 request
    ELC_EVENT_CAN_DMAREQ7            = (0x062), // DMA 7 request
    ELC_EVENT_CAN0_TX                = (0x063), // Transmit interrupt
    ELC_EVENT_CAN0_CHERR             = (0x064), // Channel error
    ELC_EVENT_CAN0_COMFRX            = (0x065), // Common FIFO recieve interrupt
    ELC_EVENT_CAN0_CF_DMAREQ         = (0x066), // Channel DMA request
    ELC_EVENT_CAN1_TX                = (0x067), // Transmit interrupt
    ELC_EVENT_CAN1_CHERR             = (0x068), // Channel error
    ELC_EVENT_CAN1_COMFRX            = (0x069), // Common FIFO recieve
    ELC_EVENT_CAN1_CF_DMAREQ         = (0x06A), // Channel DMA request
    ELC_EVENT_USBFS_FIFO_0           = (0x06B), // DMA transfer request 0
    ELC_EVENT_USBFS_FIFO_1           = (0x06C), // DMA transfer request 1
    ELC_EVENT_USBFS_INT              = (0x06D), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME           = (0x06E), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI               = (0x073), // Receive data full
    ELC_EVENT_IIC0_TXI               = (0x074), // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (0x075), // Transmit end
    ELC_EVENT_IIC0_ERI               = (0x076), // Transfer error
    ELC_EVENT_IIC0_WUI               = (0x077), // Slave address match
    ELC_EVENT_IIC1_RXI               = (0x078), // Receive data full
    ELC_EVENT_IIC1_TXI               = (0x079), // Transmit data empty
    ELC_EVENT_IIC1_TEI               = (0x07A), // Transmit end
    ELC_EVENT_IIC1_ERI               = (0x07B), // Transfer error
    ELC_EVENT_IIC2_RXI               = (0x07D), // Receive data full
    ELC_EVENT_IIC2_TXI               = (0x07E), // Transmit data empty
    ELC_EVENT_IIC2_TEI               = (0x07F), // Transmit end
    ELC_EVENT_IIC2_ERI               = (0x080), // Transfer error
    ELC_EVENT_SDHIMMC0_ACCS          = (0x082), // Card access
    ELC_EVENT_SDHIMMC0_SDIO          = (0x083), // SDIO access
    ELC_EVENT_SDHIMMC0_CARD          = (0x084), // Card detect
    ELC_EVENT_SDHIMMC0_DMA_REQ       = (0x085), // DMA transfer request
    ELC_EVENT_SSI0_TXI               = (0x08A), // Transmit data empty
    ELC_EVENT_SSI0_RXI               = (0x08B), // Receive data full
    ELC_EVENT_SSI0_INT               = (0x08D), // Error interrupt
    ELC_EVENT_CTSU_WRITE             = (0x09A), // Write request interrupt
    ELC_EVENT_CTSU_READ              = (0x09B), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END               = (0x09C), // Measurement end interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (0x09E), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (0x09F), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (0x0A0), // Overflow interrupt
    ELC_EVENT_CEC_INTDA              = (0x0AB), // Data interrupt
    ELC_EVENT_CEC_INTCE              = (0x0AC), // Communication complete interrupt
    ELC_EVENT_CEC_INTERR             = (0x0AD), // Error interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (0x0B1), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (0x0B2), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3         = (0x0B3), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4         = (0x0B4), // Port 4 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (0x0B5), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (0x0B6), // Software event 1
    ELC_EVENT_POEG0_EVENT            = (0x0B7), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (0x0B8), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT            = (0x0B9), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT            = (0x0BA), // Port Output disable interrupt D
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (0x0C0), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (0x0C1), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (0x0C2), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (0x0C3), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E         = (0x0C4), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F         = (0x0C5), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (0x0C6), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (0x0C7), // Underflow
    ELC_EVENT_GPT0_PC                = (0x0C8), // Period count function finish
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (0x0C9), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (0x0CA), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (0x0CB), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (0x0CC), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E         = (0x0CD), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F         = (0x0CE), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (0x0CF), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (0x0D0), // Underflow
    ELC_EVENT_GPT1_PC                = (0x0D1), // Period count function finish
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (0x0D2), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (0x0D3), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (0x0D4), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (0x0D5), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E         = (0x0D6), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F         = (0x0D7), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (0x0D8), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (0x0D9), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (0x0DB), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (0x0DC), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (0x0DD), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (0x0DE), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E         = (0x0DF), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F         = (0x0E0), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (0x0E1), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (0x0E2), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (0x0E4), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (0x0E5), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (0x0E6), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (0x0E7), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E         = (0x0E8), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F         = (0x0E9), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (0x0EA), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (0x0EB), // Underflow
    ELC_EVENT_GPT4_PC                = (0x0EC), // Period count function finish
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (0x0ED), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (0x0EE), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (0x0EF), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (0x0F0), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E         = (0x0F1), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F         = (0x0F2), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (0x0F3), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (0x0F4), // Underflow
    ELC_EVENT_GPT5_PC                = (0x0F5), // Period count function finish
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A = (0x0F6), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B = (0x0F7), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C         = (0x0F8), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D         = (0x0F9), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E         = (0x0FA), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F         = (0x0FB), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW  = (0x0FC), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW = (0x0FD), // Underflow
    ELC_EVENT_GPT6_PC                = (0x0FE), // Period count function finish
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A = (0x0FF), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B = (0x100), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C         = (0x101), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D         = (0x102), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E         = (0x103), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F         = (0x104), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW  = (0x105), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW = (0x106), // Underflow
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A = (0x108), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B = (0x109), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C         = (0x10A), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D         = (0x10B), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E         = (0x10C), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F         = (0x10D), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW  = (0x10E), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW = (0x10F), // Underflow
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A = (0x111), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B = (0x112), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C         = (0x113), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D         = (0x114), // Compare match D
    ELC_EVENT_GPT9_COMPARE_E         = (0x115), // Compare match E
    ELC_EVENT_GPT9_COMPARE_F         = (0x116), // Compare match F
    ELC_EVENT_GPT9_COUNTER_OVERFLOW  = (0x117), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW = (0x118), // Underflow
    ELC_EVENT_OPS_UVW_EDGE           = (0x150), // UVW edge event
    ELC_EVENT_ADC0_SCAN_END          = (0x160), // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B        = (0x161), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (0x162), // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B          = (0x163), // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH     = (0x164), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (0x165), // Compare mismatch
    ELC_EVENT_ADC1_SCAN_END          = (0x166), // A/D scan end interrupt
    ELC_EVENT_ADC1_SCAN_END_B        = (0x167), // A/D scan end interrupt for group B
    ELC_EVENT_ADC1_WINDOW_A          = (0x168), // Window A Compare match
    ELC_EVENT_ADC1_WINDOW_B          = (0x169), // Window B Compare match
    ELC_EVENT_ADC1_COMPARE_MATCH     = (0x16A), // Compare match
    ELC_EVENT_ADC1_COMPARE_MISMATCH  = (0x16B), // Compare mismatch
    ELC_EVENT_EDMAC0_EINT            = (0x16F), // EDMAC 0 interrupt
    ELC_EVENT_USBHS_FIFO_0           = (0x17D), // DMA transfer request 0
    ELC_EVENT_USBHS_FIFO_1           = (0x17E), // DMA transfer request 1
    ELC_EVENT_USBHS_USB_INT_RESUME   = (0x17F), // USBHS interrupt
    ELC_EVENT_SCI0_RXI               = (0x180), // Receive data full
    ELC_EVENT_SCI0_TXI               = (0x181), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (0x182), // Transmit end
    ELC_EVENT_SCI0_ERI               = (0x183), // Receive error
    ELC_EVENT_SCI0_AM                = (0x184), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (0x185), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI               = (0x186), // Received data full
    ELC_EVENT_SCI1_TXI               = (0x187), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (0x188), // Transmit end
    ELC_EVENT_SCI1_ERI               = (0x189), // Receive error
    ELC_EVENT_SCI2_RXI               = (0x18C), // Received data full
    ELC_EVENT_SCI2_TXI               = (0x18D), // Transmit data empty
    ELC_EVENT_SCI2_TEI               = (0x18E), // Transmit end
    ELC_EVENT_SCI2_ERI               = (0x18F), // Receive error
    ELC_EVENT_SCI3_RXI               = (0x192), // Received data full
    ELC_EVENT_SCI3_TXI               = (0x193), // Transmit data empty
    ELC_EVENT_SCI3_TEI               = (0x194), // Transmit end
    ELC_EVENT_SCI3_ERI               = (0x195), // Receive error
    ELC_EVENT_SCI3_AM                = (0x196), // Address match event
    ELC_EVENT_SCI4_RXI               = (0x198), // Received data full
    ELC_EVENT_SCI4_TXI               = (0x199), // Transmit data empty
    ELC_EVENT_SCI4_TEI               = (0x19A), // Transmit end
    ELC_EVENT_SCI4_ERI               = (0x19B), // Receive error
    ELC_EVENT_SCI4_AM                = (0x19C), // Address match event
    ELC_EVENT_SCI5_RXI               = (0x19E), // Received data full
    ELC_EVENT_SCI5_TXI               = (0x19F), // Transmit data empty
    ELC_EVENT_SCI5_TEI               = (0x1A0), // Transmit end
    ELC_EVENT_SCI5_ERI               = (0x1A1), // Receive error
    ELC_EVENT_SCI5_AM                = (0x1A2), // Address match event
    ELC_EVENT_SCI6_RXI               = (0x1A4), // Received data full
    ELC_EVENT_SCI6_TXI               = (0x1A5), // Transmit data empty
    ELC_EVENT_SCI6_TEI               = (0x1A6), // Transmit end
    ELC_EVENT_SCI6_ERI               = (0x1A7), // Receive error
    ELC_EVENT_SCI6_AM                = (0x1A8), // Address match event
    ELC_EVENT_SCI7_RXI               = (0x1AA), // Received data full
    ELC_EVENT_SCI7_TXI               = (0x1AB), // Transmit data empty
    ELC_EVENT_SCI7_TEI               = (0x1AC), // Transmit end
    ELC_EVENT_SCI7_ERI               = (0x1AD), // Receive error
    ELC_EVENT_SCI7_AM                = (0x1AE), // Address match event
    ELC_EVENT_SCI8_RXI               = (0x1B0), // Received data full
    ELC_EVENT_SCI8_TXI               = (0x1B1), // Transmit data empty
    ELC_EVENT_SCI8_TEI               = (0x1B2), // Transmit end
    ELC_EVENT_SCI8_ERI               = (0x1B3), // Receive error
    ELC_EVENT_SCI8_AM                = (0x1B4), // Address match event
    ELC_EVENT_SCI9_RXI               = (0x1B6), // Received data full
    ELC_EVENT_SCI9_TXI               = (0x1B7), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (0x1B8), // Transmit end
    ELC_EVENT_SCI9_ERI               = (0x1B9), // Receive error
    ELC_EVENT_SCI9_AM                = (0x1BA), // Address match event
    ELC_EVENT_SCIX0_SCIX0            = (0x1BC), // SCI1 extended serial mode event 0
    ELC_EVENT_SCIX0_SCIX1            = (0x1BD), // SCI1 extended serial mode event 1
    ELC_EVENT_SCIX0_SCIX2            = (0x1BE), // SCI1 extended serial mode event 2
    ELC_EVENT_SCIX0_SCIX3            = (0x1BF), // SCI1 extended serial mode event 3
    ELC_EVENT_SCIX1_SCIX0            = (0x1C0), // SCI2 extended serial mode event 0
    ELC_EVENT_SCIX1_SCIX1            = (0x1C1), // SCI2 extended serial mode event 1
    ELC_EVENT_SCIX1_SCIX2            = (0x1C2), // SCI2 extended serial mode event 2
    ELC_EVENT_SCIX1_SCIX3            = (0x1C3), // SCI2 extended serial mode event 3
    ELC_EVENT_SPI0_RXI               = (0x1C4), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (0x1C5), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (0x1C6), // Idle
    ELC_EVENT_SPI0_ERI               = (0x1C7), // Error
    ELC_EVENT_SPI0_TEI               = (0x1C8), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (0x1C9), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (0x1CA), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (0x1CB), // Idle
    ELC_EVENT_SPI1_ERI               = (0x1CC), // Error
    ELC_EVENT_SPI1_TEI               = (0x1CD), // Transmission complete event
    ELC_CAN_AFLRAM0_ERI              = (0x1CE), // ECC error
    ELC_CAN_AFLRAM1_ERI              = (0x1CF), // ECC error
    ELC_CAN_MRAM_ERI                 = (0x1D0), // ECC error
    ELC_EVENT_OSPI_INT               = (0x1D9), // OSPI interrupt
    ELC_EVENT_QSPI_INT               = (0x1DA), // QSPI interrupt
    ELC_EVENT_DOC_INT                = (0x1DB), // Data operation circuit interrupt
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA6M5) */

#endif

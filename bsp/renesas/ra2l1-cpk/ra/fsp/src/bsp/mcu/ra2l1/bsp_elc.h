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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA2L1
 * @{
 **********************************************************************************************************************/

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

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra2l1
{
    ELC_EVENT_NONE                   = (0x0),  // Link disabled
    ELC_EVENT_ICU_IRQ0               = (0x1),  // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1               = (0x2),  // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2               = (0x3),  // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3               = (0x4),  // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4               = (0x5),  // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5               = (0x6),  // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6               = (0x7),  // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7               = (0x8),  // External pin interrupt 7
    ELC_EVENT_DTC_COMPLETE           = (0x9),  // DTC last transfer
    ELC_EVENT_DTC_END                = (0xA),  // DTC transfer end
    ELC_EVENT_ICU_SNOOZE_CANCEL      = (0xB),  // Canceling from Snooze mode
    ELC_EVENT_FCU_FRDYI              = (0xC),  // Flash ready interrupt
    ELC_EVENT_LVD_LVD1               = (0xD),  // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2               = (0xE),  // Voltage monitor 2 interrupt
    ELC_EVENT_CGC_MOSC_STOP          = (0xF),  // Main Clock oscillation stop
    ELC_EVENT_LPM_SNOOZE_REQUEST     = (0x10), // Snooze entry
    ELC_EVENT_AGT0_INT               = (0x11), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A         = (0x12), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B         = (0x13), // Compare match B
    ELC_EVENT_AGT1_INT               = (0x14), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A         = (0x15), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B         = (0x16), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW         = (0x17), // IWDT underflow
    ELC_EVENT_WDT_UNDERFLOW          = (0x18), // WDT underflow
    ELC_EVENT_RTC_ALARM              = (0x19), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD             = (0x1A), // Periodic interrupt
    ELC_EVENT_RTC_CARRY              = (0x1B), // Carry interrupt
    ELC_EVENT_ADC0_SCAN_END          = (0x1C), // A/D scan end interrupt
    ELC_EVENT_ADC0_SCAN_END_B        = (0x1D), // A/D scan end interrupt for group B
    ELC_EVENT_ADC0_WINDOW_A          = (0x1E), // Window A Compare match
    ELC_EVENT_ADC0_WINDOW_B          = (0x1F), // Window B Compare match
    ELC_EVENT_ADC0_COMPARE_MATCH     = (0x20), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH  = (0x21), // Compare mismatch
    ELC_EVENT_ACMPLP0_INT            = (0x23), // Analog Comparator Channel 0 interrupt
    ELC_EVENT_ACMPLP1_INT            = (0x24), // Analog Comparator Channel 1 interrupt=
    ELC_EVENT_IIC0_RXI               = (0x27), // Receive data full
    ELC_EVENT_IIC0_TXI               = (0x28), // Transmit data empty
    ELC_EVENT_IIC0_TEI               = (0x29), // Transmit end
    ELC_EVENT_IIC0_ERI               = (0x2A), // Transfer error
    ELC_EVENT_IIC0_WUI               = (0x2B), // Slave address match
    ELC_EVENT_IIC1_RXI               = (0x2C), // Receive data full
    ELC_EVENT_IIC1_TXI               = (0x2D), // Transmit data empty
    ELC_EVENT_IIC1_TEI               = (0x2E), // Transmit end
    ELC_EVENT_IIC1_ERI               = (0x2F), // Transfer error
    ELC_EVENT_CTSU_WRITE             = (0x30), // Write request interrupt
    ELC_EVENT_CTSU_READ              = (0x31), // Measurement data transfer request interrupt
    ELC_EVENT_CTSU_END               = (0x32), // Measurement end interrupt
    ELC_EVENT_KEY_INT                = (0x33), // Key interrupt
    ELC_EVENT_DOC_INT                = (0x34), // Data operation circuit interrupt
    ELC_EVENT_CAC_FREQUENCY_ERROR    = (0x35), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END    = (0x36), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW           = (0x37), // Overflow interrupt
    ELC_EVENT_CAN0_ERROR             = (0x38), // Error interrupt
    ELC_EVENT_CAN0_FIFO_RX           = (0x39), // Receive FIFO interrupt
    ELC_EVENT_CAN0_FIFO_TX           = (0x3A), // Transmit FIFO interrupt
    ELC_EVENT_CAN0_MAILBOX_RX        = (0x3B), // Reception complete interrupt
    ELC_EVENT_CAN0_MAILBOX_TX        = (0x3C), // Transmission complete interrupt
    ELC_EVENT_IOPORT_EVENT_1         = (0x3D), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2         = (0x3E), // Port 2 event
    ELC_EVENT_ELC_SOFTWARE_EVENT_0   = (0x3F), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1   = (0x40), // Software event 1
    ELC_EVENT_POEG0_EVENT            = (0x41), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT            = (0x42), // Port Output disable interrupt B
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A = (0x46), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B = (0x47), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C         = (0x48), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D         = (0x49), // Compare match D
    ELC_EVENT_GPT0_COUNTER_OVERFLOW  = (0x4A), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW = (0x4B), // Underflow
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A = (0x4C), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B = (0x4D), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C         = (0x4E), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D         = (0x4F), // Compare match D
    ELC_EVENT_GPT1_COUNTER_OVERFLOW  = (0x50), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW = (0x51), // Underflow
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A = (0x52), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B = (0x53), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C         = (0x54), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D         = (0x55), // Compare match D
    ELC_EVENT_GPT2_COUNTER_OVERFLOW  = (0x56), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW = (0x57), // Underflow
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A = (0x58), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B = (0x59), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C         = (0x5A), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D         = (0x5B), // Compare match D
    ELC_EVENT_GPT3_COUNTER_OVERFLOW  = (0x5C), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW = (0x5D), // Underflow
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A = (0x5E), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B = (0x5F), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C         = (0x60), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D         = (0x61), // Compare match D
    ELC_EVENT_GPT4_COUNTER_OVERFLOW  = (0x62), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW = (0x63), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A = (0x64), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B = (0x65), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C         = (0x66), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D         = (0x67), // Compare match D
    ELC_EVENT_GPT5_COUNTER_OVERFLOW  = (0x68), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW = (0x69), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A = (0x6A), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B = (0x6B), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C         = (0x6C), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D         = (0x6D), // Compare match D
    ELC_EVENT_GPT6_COUNTER_OVERFLOW  = (0x6E), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW = (0x6F), // Underflow
    ELC_EVENT_OPS_UVW_EDGE           = (0x70), // UVW edge event
    ELC_EVENT_SCI0_RXI               = (0x71), // Receive data full
    ELC_EVENT_SCI0_TXI               = (0x72), // Transmit data empty
    ELC_EVENT_SCI0_TEI               = (0x73), // Transmit end
    ELC_EVENT_SCI0_ERI               = (0x74), // Receive error
    ELC_EVENT_SCI0_AM                = (0x75), // Address match event
    ELC_EVENT_SCI0_RXI_OR_ERI        = (0x76), // Receive data full/Receive
    ELC_EVENT_SCI1_RXI               = (0x77), // Received data full
    ELC_EVENT_SCI1_TXI               = (0x78), // Transmit data empty
    ELC_EVENT_SCI1_TEI               = (0x79), // Transmit end
    ELC_EVENT_SCI1_ERI               = (0x7A), // Receive error
    ELC_EVENT_SCI1_AM                = (0x7B), // Address match event
    ELC_EVENT_SCI9_RXI               = (0x7C), // Received data full
    ELC_EVENT_SCI9_TXI               = (0x7D), // Transmit data empty
    ELC_EVENT_SCI9_TEI               = (0x7E), // Transmit end
    ELC_EVENT_SCI9_ERI               = (0x7F), // Receive error
    ELC_EVENT_SCI9_AM                = (0x80), // Address match event
    ELC_EVENT_SPI0_RXI               = (0x81), // Receive buffer full
    ELC_EVENT_SPI0_TXI               = (0x82), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE              = (0x83), // Idle
    ELC_EVENT_SPI0_ERI               = (0x84), // Error
    ELC_EVENT_SPI0_TEI               = (0x85), // Transmission complete event
    ELC_EVENT_SPI1_RXI               = (0x86), // Receive buffer full
    ELC_EVENT_SPI1_TXI               = (0x87), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE              = (0x88), // Idle
    ELC_EVENT_SPI1_ERI               = (0x89), // Error
    ELC_EVENT_SPI1_TEI               = (0x8A), // Transmission complete event
    ELC_EVENT_AES_WRREQ              = (0x8B),
    ELC_EVENT_AES_RDREQ              = (0x8C),
    ELC_EVENT_TRNG_RDREQ             = (0x8D),
    ELC_EVENT_SCI2_RXI               = (0x8E), // Receive data full
    ELC_EVENT_SCI2_TXI               = (0x8F), // Transmit data empty
    ELC_EVENT_SCI2_TEI               = (0x90), // Transmit end
    ELC_EVENT_SCI2_ERI               = (0x91), // Receive error
    ELC_EVENT_SCI2_AM                = (0x92), // Address match event
    ELC_EVENT_SCI3_RXI               = (0x93), // Receive data full
    ELC_EVENT_SCI3_TXI               = (0x94), // Transmit data empty
    ELC_EVENT_SCI3_TEI               = (0x95), // Transmit end
    ELC_EVENT_SCI3_ERI               = (0x96), // Receive error
    ELC_EVENT_SCI3_AM                = (0x97), // Address match event
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A = (0x98), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B = (0x99), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C         = (0x9A), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D         = (0x9B), // Compare match D
    ELC_EVENT_GPT7_COUNTER_OVERFLOW  = (0x9C), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW = (0x9D), // Underflow
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A = (0x9E), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B = (0x9F), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C         = (0xA0), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D         = (0xA1), // Compare match D
    ELC_EVENT_GPT8_COUNTER_OVERFLOW  = (0xA2), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW = (0xA3), // Underflow
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A = (0xA4), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B = (0xA5), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C         = (0xA6), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D         = (0xA7), // Compare match D
    ELC_EVENT_GPT9_COUNTER_OVERFLOW  = (0xA8), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW = (0xA9), // Underflow
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA2L1) */

#endif

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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8M1
 * @{
 **********************************************************************************************************************/

/** Sources of event signals to be linked to other peripherals or the CPU
 * @note This list may change based on based on the device.
 * */
typedef enum e_elc_event_ra8m1
{
    ELC_EVENT_NONE                    = (0),     // Link disabled
    ELC_EVENT_ICU_IRQ0                = (0x001), // External pin interrupt 0
    ELC_EVENT_ICU_IRQ1                = (0x002), // External pin interrupt 1
    ELC_EVENT_ICU_IRQ2                = (0x003), // External pin interrupt 2
    ELC_EVENT_ICU_IRQ3                = (0x004), // External pin interrupt 3
    ELC_EVENT_ICU_IRQ4                = (0x005), // External pin interrupt 4
    ELC_EVENT_ICU_IRQ5                = (0x006), // External pin interrupt 5
    ELC_EVENT_ICU_IRQ6                = (0x007), // External pin interrupt 6
    ELC_EVENT_ICU_IRQ7                = (0x008), // External pin interrupt 7
    ELC_EVENT_ICU_IRQ8                = (0x009), // External pin interrupt 8
    ELC_EVENT_ICU_IRQ9                = (0x00A), // External pin interrupt 9
    ELC_EVENT_ICU_IRQ10               = (0x00B), // External pin interrupt 10
    ELC_EVENT_ICU_IRQ11               = (0x00C), // External pin interrupt 11
    ELC_EVENT_ICU_IRQ12               = (0x00D), // External pin interrupt 12
    ELC_EVENT_ICU_IRQ13               = (0x00E), // External pin interrupt 13
    ELC_EVENT_ICU_IRQ14               = (0x00F), // External pin interrupt 14
    ELC_EVENT_ICU_IRQ15               = (0x010), // External pin interrupt 15
    ELC_EVENT_DMAC0_INT               = (0x011), // DMAC0 transfer end 0
    ELC_EVENT_DMAC1_INT               = (0x012), // DMAC0 transfer end 1
    ELC_EVENT_DMAC2_INT               = (0x013), // DMAC0 transfer end 2
    ELC_EVENT_DMAC3_INT               = (0x014), // DMAC0 transfer end 3
    ELC_EVENT_DMAC4_INT               = (0x015), // DMAC0 transfer end 4
    ELC_EVENT_DMAC5_INT               = (0x016), // DMAC0 transfer end 5
    ELC_EVENT_DMAC6_INT               = (0x017), // DMAC0 transfer end 6
    ELC_EVENT_DMAC7_INT               = (0x018), // DMAC0 transfer end 7
    ELC_EVENT_DTC_END                 = (0x021), // DTC transfer end
    ELC_EVENT_DTC_COMPLETE            = (0x022), // DTC transfer complete
    ELC_EVENT_DMA_TRANSERR            = (0x027), // DMA transfer error
    ELC_EVENT_FCU_FIFERR              = (0x030), // Flash access error interrupt
    ELC_EVENT_FCU_FRDYI               = (0x031), // Flash ready interrupt
    ELC_EVENT_LVD_LVD1                = (0x038), // Voltage monitor 1 interrupt
    ELC_EVENT_LVD_LVD2                = (0x039), // Voltage monitor 2 interrupt
    ELC_EVENT_LVD_VBATT               = (0x03D), // VBATT low voltage detect
    ELC_EVENT_CGC_MOSC_STOP           = (0x03E), // Main Clock oscillation stop
    ELC_EVENT_ULPT0_INT               = (0x040), // ULPT0 Underflow
    ELC_EVENT_ULPT0_COMPARE_A         = (0x041), // ULPT0 Compare match A
    ELC_EVENT_ULPT0_COMPARE_B         = (0x042), // ULPT0 Compare match B
    ELC_EVENT_ULPT1_INT               = (0x043), // ULPT1 Underflow
    ELC_EVENT_ULPT1_COMPARE_A         = (0x044), // ULPT1 Compare match A
    ELC_EVENT_ULPT1_COMPARE_B         = (0x045), // ULPT1 Compare match B
    ELC_EVENT_AGT0_INT                = (0x046), // AGT interrupt
    ELC_EVENT_AGT0_COMPARE_A          = (0x047), // Compare match A
    ELC_EVENT_AGT0_COMPARE_B          = (0x048), // Compare match B
    ELC_EVENT_AGT1_INT                = (0x049), // AGT interrupt
    ELC_EVENT_AGT1_COMPARE_A          = (0x04A), // Compare match A
    ELC_EVENT_AGT1_COMPARE_B          = (0x04B), // Compare match B
    ELC_EVENT_IWDT_UNDERFLOW          = (0x052), // IWDT underflow
    ELC_EVENT_WDT0_UNDERFLOW          = (0x053), // WDT0 underflow
    ELC_EVENT_RTC_ALARM               = (0x055), // Alarm interrupt
    ELC_EVENT_RTC_PERIOD              = (0x056), // Periodic interrupt
    ELC_EVENT_RTC_CARRY               = (0x057), // Carry interrupt
    ELC_EVENT_USBFS_FIFO_0            = (0x058), // DMA transfer request 0
    ELC_EVENT_USBFS_FIFO_1            = (0x059), // DMA transfer request 1
    ELC_EVENT_USBFS_INT               = (0x05A), // USBFS interrupt
    ELC_EVENT_USBFS_RESUME            = (0x05B), // USBFS resume interrupt
    ELC_EVENT_IIC0_RXI                = (0x05C), // Receive data full
    ELC_EVENT_IIC0_TXI                = (0x05D), // Transmit data empty
    ELC_EVENT_IIC0_TEI                = (0x05E), // Transmit end
    ELC_EVENT_IIC0_ERI                = (0x05F), // Transfer error
    ELC_EVENT_IIC0_WUI                = (0x060), // Wakeup interrupt
    ELC_EVENT_IIC1_RXI                = (0x061), // Receive data full
    ELC_EVENT_IIC1_TXI                = (0x062), // Transmit data empty
    ELC_EVENT_IIC1_TEI                = (0x063), // Transmit end
    ELC_EVENT_IIC1_ERI                = (0x064), // Transfer error
    ELC_EVENT_SDHIMMC0_ACCS           = (0x06B), // Card access
    ELC_EVENT_SDHIMMC0_SDIO           = (0x06C), // SDIO access
    ELC_EVENT_SDHIMMC0_CARD           = (0x06D), // Card detect
    ELC_EVENT_SDHIMMC0_DMA_REQ        = (0x06E), // DMA transfer request
    ELC_EVENT_SDHIMMC1_ACCS           = (0x06F), // Card access
    ELC_EVENT_SDHIMMC1_SDIO           = (0x070), // SDIO access
    ELC_EVENT_SDHIMMC1_CARD           = (0x071), // Card detect
    ELC_EVENT_SDHIMMC1_DMA_REQ        = (0x072), // DMA transfer request
    ELC_EVENT_SSI0_TXI                = (0x073), // Transmit data empty
    ELC_EVENT_SSI0_RXI                = (0x074), // Receive data full
    ELC_EVENT_SSI0_INT                = (0x076), // Error interrupt
    ELC_EVENT_SSI1_TXI_RXI            = (0x079), // Receive data full/Transmit data empty
    ELC_EVENT_SSI1_INT                = (0x07A), // Error interrupt
    ELC_EVENT_ACMPHS0_INT             = (0x07B), // Comparator interrupt 0
    ELC_EVENT_ACMPHS1_INT             = (0x07C), // Comparator interrupt 1
    ELC_EVENT_ELC_SOFTWARE_EVENT_0    = (0x083), // Software event 0
    ELC_EVENT_ELC_SOFTWARE_EVENT_1    = (0x084), // Software event 1
    ELC_EVENT_IOPORT_EVENT_1          = (0x088), // Port 1 event
    ELC_EVENT_IOPORT_EVENT_2          = (0x089), // Port 2 event
    ELC_EVENT_IOPORT_EVENT_3          = (0x08A), // Port 3 event
    ELC_EVENT_IOPORT_EVENT_4          = (0x08B), // Port 4 event
    ELC_EVENT_CAC_FREQUENCY_ERROR     = (0x08C), // Frequency error interrupt
    ELC_EVENT_CAC_MEASUREMENT_END     = (0x08D), // Measurement end interrupt
    ELC_EVENT_CAC_OVERFLOW            = (0x08E), // Overflow interrupt
    ELC_EVENT_POEG0_EVENT             = (0x08F), // Port Output disable interrupt A
    ELC_EVENT_POEG1_EVENT             = (0x090), // Port Output disable interrupt B
    ELC_EVENT_POEG2_EVENT             = (0x091), // Port Output disable interrupt C
    ELC_EVENT_POEG3_EVENT             = (0x092), // Port Output disable interrupt D
    ELC_EVENT_OPS_UVW_EDGE            = (0x0A0), // UVW edge event
    ELC_EVENT_GPT0_CAPTURE_COMPARE_A  = (0x0A1), // Compare match A
    ELC_EVENT_GPT0_CAPTURE_COMPARE_B  = (0x0A2), // Compare match B
    ELC_EVENT_GPT0_COMPARE_C          = (0x0A3), // Compare match C
    ELC_EVENT_GPT0_COMPARE_D          = (0x0A4), // Compare match D
    ELC_EVENT_GPT0_COMPARE_E          = (0x0A5), // Compare match E
    ELC_EVENT_GPT0_COMPARE_F          = (0x0A6), // Compare match F
    ELC_EVENT_GPT0_COUNTER_OVERFLOW   = (0x0A7), // Overflow
    ELC_EVENT_GPT0_COUNTER_UNDERFLOW  = (0x0A8), // Underflow
    ELC_EVENT_GPT0_PC                 = (0x0A9), // Period count function finish
    ELC_EVENT_GPT1_CAPTURE_COMPARE_A  = (0x0AA), // Compare match A
    ELC_EVENT_GPT1_CAPTURE_COMPARE_B  = (0x0Ab), // Compare match B
    ELC_EVENT_GPT1_COMPARE_C          = (0x0AC), // Compare match C
    ELC_EVENT_GPT1_COMPARE_D          = (0x0AD), // Compare match D
    ELC_EVENT_GPT1_COMPARE_E          = (0x0AE), // Compare match E
    ELC_EVENT_GPT1_COMPARE_F          = (0x0AF), // Compare match F
    ELC_EVENT_GPT1_COUNTER_OVERFLOW   = (0x0B0), // Overflow
    ELC_EVENT_GPT1_COUNTER_UNDERFLOW  = (0x0B1), // Underflow
    ELC_EVENT_GPT1_PC                 = (0x0B2), // Period count function finish
    ELC_EVENT_GPT2_CAPTURE_COMPARE_A  = (0x0B3), // Compare match A
    ELC_EVENT_GPT2_CAPTURE_COMPARE_B  = (0x0B4), // Compare match B
    ELC_EVENT_GPT2_COMPARE_C          = (0x0B5), // Compare match C
    ELC_EVENT_GPT2_COMPARE_D          = (0x0B6), // Compare match D
    ELC_EVENT_GPT2_COMPARE_E          = (0x0B7), // Compare match E
    ELC_EVENT_GPT2_COMPARE_F          = (0x0B8), // Compare match F
    ELC_EVENT_GPT2_COUNTER_OVERFLOW   = (0x0B9), // Overflow
    ELC_EVENT_GPT2_COUNTER_UNDERFLOW  = (0x0BA), // Underflow
    ELC_EVENT_GPT2_PC                 = (0x0BB), // Period count function finish
    ELC_EVENT_GPT3_CAPTURE_COMPARE_A  = (0x0BC), // Compare match A
    ELC_EVENT_GPT3_CAPTURE_COMPARE_B  = (0x0BD), // Compare match B
    ELC_EVENT_GPT3_COMPARE_C          = (0x0BE), // Compare match C
    ELC_EVENT_GPT3_COMPARE_D          = (0x0BF), // Compare match D
    ELC_EVENT_GPT3_COMPARE_E          = (0x0C0), // Compare match E
    ELC_EVENT_GPT3_COMPARE_F          = (0x0C1), // Compare match F
    ELC_EVENT_GPT3_COUNTER_OVERFLOW   = (0x0C2), // Overflow
    ELC_EVENT_GPT3_COUNTER_UNDERFLOW  = (0x0C3), // Underflow
    ELC_EVENT_GPT3_PC                 = (0x0C4), // Period count function finish
    ELC_EVENT_GPT4_CAPTURE_COMPARE_A  = (0x0C5), // Compare match A
    ELC_EVENT_GPT4_CAPTURE_COMPARE_B  = (0x0C6), // Compare match B
    ELC_EVENT_GPT4_COMPARE_C          = (0x0C7), // Compare match C
    ELC_EVENT_GPT4_COMPARE_D          = (0x0C8), // Compare match D
    ELC_EVENT_GPT4_COMPARE_E          = (0x0C9), // Compare match E
    ELC_EVENT_GPT4_COMPARE_F          = (0x0CA), // Compare match F
    ELC_EVENT_GPT4_COUNTER_OVERFLOW   = (0x0CB), // Overflow
    ELC_EVENT_GPT4_COUNTER_UNDERFLOW  = (0x0CC), // Underflow
    ELC_EVENT_GPT5_CAPTURE_COMPARE_A  = (0x0CE), // Compare match A
    ELC_EVENT_GPT5_CAPTURE_COMPARE_B  = (0x0CF), // Compare match B
    ELC_EVENT_GPT5_COMPARE_C          = (0x0D0), // Compare match C
    ELC_EVENT_GPT5_COMPARE_D          = (0x0D1), // Compare match D
    ELC_EVENT_GPT5_COMPARE_E          = (0x0D2), // Compare match E
    ELC_EVENT_GPT5_COMPARE_F          = (0x0D3), // Compare match F
    ELC_EVENT_GPT5_COUNTER_OVERFLOW   = (0x0D4), // Overflow
    ELC_EVENT_GPT5_COUNTER_UNDERFLOW  = (0x0D5), // Underflow
    ELC_EVENT_GPT6_CAPTURE_COMPARE_A  = (0x0D7), // Compare match A
    ELC_EVENT_GPT6_CAPTURE_COMPARE_B  = (0x0D8), // Compare match B
    ELC_EVENT_GPT6_COMPARE_C          = (0x0D9), // Compare match C
    ELC_EVENT_GPT6_COMPARE_D          = (0x0DA), // Compare match D
    ELC_EVENT_GPT6_COMPARE_E          = (0x0DB), // Compare match E
    ELC_EVENT_GPT6_COMPARE_F          = (0x0DC), // Compare match F
    ELC_EVENT_GPT6_COUNTER_OVERFLOW   = (0x0DD), // Overflow
    ELC_EVENT_GPT6_COUNTER_UNDERFLOW  = (0x0DE), // Underflow
    ELC_EVENT_GPT7_CAPTURE_COMPARE_A  = (0x0E0), // Compare match A
    ELC_EVENT_GPT7_CAPTURE_COMPARE_B  = (0x0E1), // Compare match B
    ELC_EVENT_GPT7_COMPARE_C          = (0x0E2), // Compare match C
    ELC_EVENT_GPT7_COMPARE_D          = (0x0E3), // Compare match D
    ELC_EVENT_GPT7_COMPARE_E          = (0x0E4), // Compare match E
    ELC_EVENT_GPT7_COMPARE_F          = (0x0E5), // Compare match F
    ELC_EVENT_GPT7_COUNTER_OVERFLOW   = (0x0E6), // Overflow
    ELC_EVENT_GPT7_COUNTER_UNDERFLOW  = (0x0E7), // Underflow
    ELC_EVENT_GPT8_CAPTURE_COMPARE_A  = (0x0E9), // Compare match A
    ELC_EVENT_GPT8_CAPTURE_COMPARE_B  = (0x0EA), // Compare match B
    ELC_EVENT_GPT8_COMPARE_C          = (0x0EB), // Compare match C
    ELC_EVENT_GPT8_COMPARE_D          = (0x0EC), // Compare match D
    ELC_EVENT_GPT8_COMPARE_E          = (0x0ED), // Compare match E
    ELC_EVENT_GPT8_COMPARE_F          = (0x0EE), // Compare match F
    ELC_EVENT_GPT8_COUNTER_OVERFLOW   = (0x0EF), // Overflow
    ELC_EVENT_GPT8_COUNTER_UNDERFLOW  = (0x0F0), // Underflow
    ELC_EVENT_GPT8_PC                 = (0x0F1), // Period count function finish
    ELC_EVENT_GPT9_CAPTURE_COMPARE_A  = (0x0F2), // Compare match A
    ELC_EVENT_GPT9_CAPTURE_COMPARE_B  = (0x0F3), // Compare match B
    ELC_EVENT_GPT9_COMPARE_C          = (0x0F4), // Compare match C
    ELC_EVENT_GPT9_COMPARE_D          = (0x0F5), // Compare match D
    ELC_EVENT_GPT9_COMPARE_E          = (0x0F6), // Compare match E
    ELC_EVENT_GPT9_COMPARE_F          = (0x0F7), // Compare match F
    ELC_EVENT_GPT9_COUNTER_OVERFLOW   = (0x0F8), // Overflow
    ELC_EVENT_GPT9_COUNTER_UNDERFLOW  = (0x0F9), // Underflow
    ELC_EVENT_GPT9_PC                 = (0x0FA), // Period count function finish
    ELC_EVENT_GPT10_CAPTURE_COMPARE_A = (0x0FB), // Compare match A
    ELC_EVENT_GPT10_CAPTURE_COMPARE_B = (0x0FC), // Compare match B
    ELC_EVENT_GPT10_COMPARE_C         = (0x0FD), // Compare match C
    ELC_EVENT_GPT10_COMPARE_D         = (0x0FE), // Compare match D
    ELC_EVENT_GPT10_COMPARE_E         = (0x0FF), // Compare match E
    ELC_EVENT_GPT10_COMPARE_F         = (0x100), // Compare match F
    ELC_EVENT_GPT10_COUNTER_OVERFLOW  = (0x101), // Overflow
    ELC_EVENT_GPT10_COUNTER_UNDERFLOW = (0x102), // Underflow
    ELC_EVENT_GPT10_PC                = (0x103), // Period count function finish
    ELC_EVENT_GPT11_CAPTURE_COMPARE_A = (0x104), // Compare match A
    ELC_EVENT_GPT11_CAPTURE_COMPARE_B = (0x105), // Compare match B
    ELC_EVENT_GPT11_COMPARE_C         = (0x106), // Compare match C
    ELC_EVENT_GPT11_COMPARE_D         = (0x107), // Compare match D
    ELC_EVENT_GPT11_COMPARE_E         = (0x108), // Compare match E
    ELC_EVENT_GPT11_COMPARE_F         = (0x109), // Compare match F
    ELC_EVENT_GPT11_COUNTER_OVERFLOW  = (0x10A), // Overflow
    ELC_EVENT_GPT11_COUNTER_UNDERFLOW = (0x10B), // Underflow
    ELC_EVENT_GPT12_CAPTURE_COMPARE_A = (0x10D), // Compare match A
    ELC_EVENT_GPT12_CAPTURE_COMPARE_B = (0x10E), // Compare match B
    ELC_EVENT_GPT12_COMPARE_C         = (0x10F), // Compare match C
    ELC_EVENT_GPT12_COMPARE_D         = (0x110), // Compare match D
    ELC_EVENT_GPT12_COMPARE_E         = (0x111), // Compare match E
    ELC_EVENT_GPT12_COMPARE_F         = (0x112), // Compare match F
    ELC_EVENT_GPT12_COUNTER_OVERFLOW  = (0x113), // Overflow
    ELC_EVENT_GPT12_COUNTER_UNDERFLOW = (0x114), // Underflow
    ELC_EVENT_GPT13_CAPTURE_COMPARE_A = (0x116), // Compare match A
    ELC_EVENT_GPT13_CAPTURE_COMPARE_B = (0x117), // Compare match B
    ELC_EVENT_GPT13_COMPARE_C         = (0x118), // Compare match C
    ELC_EVENT_GPT13_COMPARE_D         = (0x119), // Compare match D
    ELC_EVENT_GPT13_COMPARE_E         = (0x11A), // Compare match E
    ELC_EVENT_GPT13_COMPARE_F         = (0x11B), // Compare match F
    ELC_EVENT_GPT13_COUNTER_OVERFLOW  = (0x11C), // Overflow
    ELC_EVENT_GPT13_COUNTER_UNDERFLOW = (0x11D), // Underflow
    ELC_EVENT_EDMAC0_EINT             = (0x120), // EDMAC 0 interrupt
    ELC_EVENT_USBHS_FIFO_0            = (0x121), // DMA transfer request 0
    ELC_EVENT_USBHS_FIFO_1            = (0x122), // DMA transfer request 1
    ELC_EVENT_USBHS_USB_INT_RESUME    = (0x123), // USBHS interr
    ELC_EVENT_SCI0_RXI                = (0x124), // Receive data full
    ELC_EVENT_SCI0_TXI                = (0x125), // Transmit data empty
    ELC_EVENT_SCI0_TEI                = (0x126), // Transmit end
    ELC_EVENT_SCI0_ERI                = (0x127), // Receive error
    ELC_EVENT_SCI0_AED                = (0x128), // Active edge detection
    ELC_EVENT_SCI0_BFD                = (0x129), // Break field detection
    ELC_EVENT_SCI0_AM                 = (0x12A), // Address match event
    ELC_EVENT_SCI1_RXI                = (0x12B), // Receive data full
    ELC_EVENT_SCI1_TXI                = (0x12C), // Transmit data empty
    ELC_EVENT_SCI1_TEI                = (0x12D), // Transmit end
    ELC_EVENT_SCI1_ERI                = (0x12E), // Receive error
    ELC_EVENT_SCI1_AED                = (0x12F), // Active edge detection
    ELC_EVENT_SCI1_BFD                = (0x130), // Break field detection
    ELC_EVENT_SCI1_AM                 = (0x131), // Address match event
    ELC_EVENT_SCI2_RXI                = (0x132), // Receive data full
    ELC_EVENT_SCI2_TXI                = (0x133), // Transmit data empty
    ELC_EVENT_SCI2_TEI                = (0x134), // Transmit end
    ELC_EVENT_SCI2_ERI                = (0x135), // Receive error
    ELC_EVENT_SCI2_AM                 = (0x138), // Address match event
    ELC_EVENT_SCI3_RXI                = (0x139), // Receive data full
    ELC_EVENT_SCI3_TXI                = (0x13A), // Transmit data empty
    ELC_EVENT_SCI3_TEI                = (0x13B), // Transmit end
    ELC_EVENT_SCI3_ERI                = (0x13C), // Receive error
    ELC_EVENT_SCI3_AM                 = (0x13F), // Address match event
    ELC_EVENT_SCI4_RXI                = (0x140), // Receive data full
    ELC_EVENT_SCI4_TXI                = (0x141), // Transmit data empty
    ELC_EVENT_SCI4_TEI                = (0x142), // Transmit end
    ELC_EVENT_SCI4_ERI                = (0x143), // Receive error
    ELC_EVENT_SCI4_AM                 = (0x146), // Address match event
    ELC_EVENT_SCI9_RXI                = (0x163), // Receive data full
    ELC_EVENT_SCI9_TXI                = (0x164), // Transmit data empty
    ELC_EVENT_SCI9_TEI                = (0x165), // Transmit end
    ELC_EVENT_SCI9_ERI                = (0x166), // Receive error
    ELC_EVENT_SCI9_AM                 = (0x169), // Address match event
    ELC_EVENT_SPI0_RXI                = (0x178), // Receive buffer full
    ELC_EVENT_SPI0_TXI                = (0x179), // Transmit buffer empty
    ELC_EVENT_SPI0_IDLE               = (0x17A), // Idle
    ELC_EVENT_SPI0_ERI                = (0x17B), // Error
    ELC_EVENT_SPI0_TEI                = (0x17C), // Transmission complete event
    ELC_EVENT_SPI1_RXI                = (0x17D), // Receive buffer full
    ELC_EVENT_SPI1_TXI                = (0x17E), // Transmit buffer empty
    ELC_EVENT_SPI1_IDLE               = (0x17F), // Idle
    ELC_EVENT_SPI1_ERI                = (0x180), // Error
    ELC_EVENT_SPI1_TEI                = (0x181), // Transmission complete event
    ELC_EVENT_XSPI_ERR                = (0x182), // xSPI Error
    ELC_EVENT_XSPI_CMP                = (0x183), // xSPI Complete
    ELC_EVENT_CAN_RXF                 = (0x185), // Global recieve FIFO interrupt
    ELC_EVENT_CAN_GLERR               = (0x186), // Global error
    ELC_EVENT_CAN0_DMAREQ0            = (0x187), // Channel rx fifio DMA request
    ELC_EVENT_CAN0_DMAREQ1            = (0x188), // Channel rx fifio DMA request
    ELC_EVENT_CAN1_DMAREQ0            = (0x18B), // Channel rx fifio DMA request
    ELC_EVENT_CAN1_DMAREQ1            = (0x18C), // Channel rx fifio DMA request
    ELC_EVENT_CAN0_TX                 = (0x18F), // Transmit interrupt
    ELC_EVENT_CAN0_CHERR              = (0x190), // Channel error
    ELC_EVENT_CAN0_COMFRX             = (0x191), // Common FIFO recieve interrupt
    ELC_EVENT_CAN0_CF_DMAREQ          = (0x192), // Channel DMA request
    ELC_EVENT_CAN0_RXMB               = (0x193), // RXMB interrupt lines
    ELC_EVENT_CAN1_TX                 = (0x194), // Transmit interrupt
    ELC_EVENT_CAN1_CHERR              = (0x195), // Channel error
    ELC_EVENT_CAN1_COMFRX             = (0x196), // Common FIFO recieve
    ELC_EVENT_CAN1_CF_DMAREQ          = (0x197), // Channel DMA req
    ELC_EVENT_CAN1_RXMB               = (0x198), // RXMB interrupt lines
    ELC_EVENT_CAN0_MRAM_ERI           = (0x19B), // CANFD0 ECC error
    ELC_EVENT_CAN1_MRAM_ERI           = (0x19C), // CANFD1 ECC error
    ELC_EVENT_I3C0_RESPONSE           = (0x19D), // Response status buffer full
    ELC_EVENT_I3C0_COMMAND            = (0x19E), // Command buffer empty
    ELC_EVENT_I3C0_IBI                = (0x19F), // IBI status buffer full
    ELC_EVENT_I3C0_RX                 = (0x1A0), // Receive
    ELC_EVENT_I3C0_TX                 = (0x1A1), // Transmit
    ELC_EVENT_I3C0_RCV_STATUS         = (0x1A2), // Receive status buffer full
    ELC_EVENT_I3C0_HRESP              = (0x1A3), // High priority response queue full
    ELC_EVENT_I3C0_HCMD               = (0x1A4), // High priority command queue empty
    ELC_EVENT_I3C0_HRX                = (0x1A5), // High priority rx data buffer full
    ELC_EVENT_I3C0_HTX                = (0x1A6), // High priority tx data buffer empty
    ELC_EVENT_I3C0_TEND               = (0x1A7), // Transmit end
    ELC_EVENT_I3C0_EEI                = (0x1A8), // Error
    ELC_EVENT_I3C0_STEV               = (0x1A9), // Synchronous Timing
    ELC_EVENT_I3C0_MREFOVF            = (0x1AA), // MREF counter overflow
    ELC_EVENT_I3C0_MREFCPT            = (0x1AB), // MREF capture
    ELC_EVENT_I3C0_AMEV               = (0x1AC), // Additional master-initiated bus event
    ELC_EVENT_I3C0_WU                 = (0x1AD), // Wake-up Condition Detection interrupt
    ELC_EVENT_ADC0_SCAN_END           = (0x1AE), // End of A/D scanning operation
    ELC_EVENT_ADC0_SCAN_END_B         = (0x1AF), // End of A/D scanning operation for Group B
    ELC_EVENT_ADC0_WINDOW_A           = (0x1B0), // Window A Compare match interrupt
    ELC_EVENT_ADC0_WINDOW_B           = (0x1B1), // Window B Compare match interrupt
    ELC_EVENT_ADC0_COMPARE_MATCH      = (0x1B2), // Compare match
    ELC_EVENT_ADC0_COMPARE_MISMATCH   = (0x1B3), // Compare mismatch
    ELC_EVENT_ADC1_SCAN_END           = (0x1B4), // End of A/D scanning operation
    ELC_EVENT_ADC1_SCAN_END_B         = (0x1B5), // End of A/D scanning operation for Group B
    ELC_EVENT_ADC1_WINDOW_A           = (0x1B6), // Window A Compare match interrupt
    ELC_EVENT_ADC1_WINDOW_B           = (0x1B7), // Window B Compare match interrupt
    ELC_EVENT_ADC1_COMPARE_MATCH      = (0x1B8), // Compare match
    ELC_EVENT_ADC1_COMPARE_MISMATCH   = (0x1B9), // Compare mismatch
    ELC_EVENT_DOC_INT                 = (0x1BA), // Data operation circuit interrupt
    ELC_EVENT_CEU_CEUI                = (0x1DA), // CEU interrupt
} elc_event_t;

/** @} (end addtogroup BSP_MCU_RA8M1) */

#endif

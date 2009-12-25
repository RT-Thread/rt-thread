//*****************************************************************************
//
// hw_ssi.h - Macros used when accessing the SSI hardware.
//
// Copyright (c) 2005-2009 Luminary Micro, Inc.  All rights reserved.
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  You may not combine
// this software with "viral" open-source software in order to form a larger
// program.  Any use in violation of the foregoing restrictions may subject
// the user to criminal sanctions under applicable laws, as well as to civil
// liability for the breach of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 4694 of the Stellaris Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_SSI_H__
#define __HW_SSI_H__

//*****************************************************************************
//
// The following are defines for the SSI register offsets.
//
//*****************************************************************************
#define SSI_O_CR0               0x00000000  // Control register 0
#define SSI_O_CR1               0x00000004  // Control register 1
#define SSI_O_DR                0x00000008  // Data register
#define SSI_O_SR                0x0000000C  // Status register
#define SSI_O_CPSR              0x00000010  // Clock prescale register
#define SSI_O_IM                0x00000014  // Int mask set and clear register
#define SSI_O_RIS               0x00000018  // Raw interrupt register
#define SSI_O_MIS               0x0000001C  // Masked interrupt register
#define SSI_O_ICR               0x00000020  // Interrupt clear register
#define SSI_O_DMACTL            0x00000024  // SSI DMA Control

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI Control register 0.
//
//*****************************************************************************
#define SSI_CR0_SCR_M           0x0000FF00  // SSI Serial Clock Rate.
#define SSI_CR0_SPH             0x00000080  // SSPCLKOUT phase
#define SSI_CR0_SPO             0x00000040  // SSPCLKOUT polarity
#define SSI_CR0_FRF_M           0x00000030  // Frame format mask
#define SSI_CR0_FRF_MOTO        0x00000000  // Motorola SPI frame format
#define SSI_CR0_FRF_TI          0x00000010  // TI sync serial frame format
#define SSI_CR0_FRF_NMW         0x00000020  // National Microwire frame format
#define SSI_CR0_DSS_M           0x0000000F  // SSI Data Size Select.
#define SSI_CR0_DSS_4           0x00000003  // 4 bit data
#define SSI_CR0_DSS_5           0x00000004  // 5 bit data
#define SSI_CR0_DSS_6           0x00000005  // 6 bit data
#define SSI_CR0_DSS_7           0x00000006  // 7 bit data
#define SSI_CR0_DSS_8           0x00000007  // 8 bit data
#define SSI_CR0_DSS_9           0x00000008  // 9 bit data
#define SSI_CR0_DSS_10          0x00000009  // 10 bit data
#define SSI_CR0_DSS_11          0x0000000A  // 11 bit data
#define SSI_CR0_DSS_12          0x0000000B  // 12 bit data
#define SSI_CR0_DSS_13          0x0000000C  // 13 bit data
#define SSI_CR0_DSS_14          0x0000000D  // 14 bit data
#define SSI_CR0_DSS_15          0x0000000E  // 15 bit data
#define SSI_CR0_DSS_16          0x0000000F  // 16 bit data
#define SSI_CR0_SCR_S           8

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI Control register 1.
//
//*****************************************************************************
#define SSI_CR1_EOT             0x00000010  // End of Transmission.
#define SSI_CR1_SOD             0x00000008  // Slave mode output disable
#define SSI_CR1_MS              0x00000004  // Master or slave mode select
#define SSI_CR1_SSE             0x00000002  // Sync serial port enable
#define SSI_CR1_LBM             0x00000001  // Loopback mode

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI Status register.
//
//*****************************************************************************
#define SSI_SR_BSY              0x00000010  // SSI busy
#define SSI_SR_RFF              0x00000008  // RX FIFO full
#define SSI_SR_RNE              0x00000004  // RX FIFO not empty
#define SSI_SR_TNF              0x00000002  // TX FIFO not full
#define SSI_SR_TFE              0x00000001  // TX FIFO empty

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI clock prescale
// register.
//
//*****************************************************************************
#define SSI_CPSR_CPSDVSR_M      0x000000FF  // SSI Clock Prescale Divisor.
#define SSI_CPSR_CPSDVSR_S      0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_DR register.
//
//*****************************************************************************
#define SSI_DR_DATA_M           0x0000FFFF  // SSI Receive/Transmit Data.
#define SSI_DR_DATA_S           0

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_IM register.
//
//*****************************************************************************
#define SSI_IM_TXIM             0x00000008  // SSI Transmit FIFO Interrupt
                                            // Mask.
#define SSI_IM_RXIM             0x00000004  // SSI Receive FIFO Interrupt Mask.
#define SSI_IM_RTIM             0x00000002  // SSI Receive Time-Out Interrupt
                                            // Mask.
#define SSI_IM_RORIM            0x00000001  // SSI Receive Overrun Interrupt
                                            // Mask.

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_RIS register.
//
//*****************************************************************************
#define SSI_RIS_TXRIS           0x00000008  // SSI Transmit FIFO Raw Interrupt
                                            // Status.
#define SSI_RIS_RXRIS           0x00000004  // SSI Receive FIFO Raw Interrupt
                                            // Status.
#define SSI_RIS_RTRIS           0x00000002  // SSI Receive Time-Out Raw
                                            // Interrupt Status.
#define SSI_RIS_RORRIS          0x00000001  // SSI Receive Overrun Raw
                                            // Interrupt Status.

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_MIS register.
//
//*****************************************************************************
#define SSI_MIS_TXMIS           0x00000008  // SSI Transmit FIFO Masked
                                            // Interrupt Status.
#define SSI_MIS_RXMIS           0x00000004  // SSI Receive FIFO Masked
                                            // Interrupt Status.
#define SSI_MIS_RTMIS           0x00000002  // SSI Receive Time-Out Masked
                                            // Interrupt Status.
#define SSI_MIS_RORMIS          0x00000001  // SSI Receive Overrun Masked
                                            // Interrupt Status.

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_ICR register.
//
//*****************************************************************************
#define SSI_ICR_RTIC            0x00000002  // SSI Receive Time-Out Interrupt
                                            // Clear.
#define SSI_ICR_RORIC           0x00000001  // SSI Receive Overrun Interrupt
                                            // Clear.

//*****************************************************************************
//
// The following are defines for the bit fields in the SSI_O_DMACTL register.
//
//*****************************************************************************
#define SSI_DMACTL_TXDMAE       0x00000002  // Transmit DMA Enable.
#define SSI_DMACTL_RXDMAE       0x00000001  // Receive DMA Enable.

//*****************************************************************************
//
// The following definitions are deprecated.
//
//*****************************************************************************
#ifndef DEPRECATED

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the SSI Control
// register 0.
//
//*****************************************************************************
#define SSI_CR0_SCR             0x0000FF00  // Serial clock rate
#define SSI_CR0_FRF_MASK        0x00000030  // Frame format mask
#define SSI_CR0_DSS             0x0000000F  // Data size select

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the SSI clock
// prescale register.
//
//*****************************************************************************
#define SSI_CPSR_CPSDVSR_MASK   0x000000FF  // Clock prescale

//*****************************************************************************
//
// The following are deprecated defines for the SSI controller's FIFO size.
//
//*****************************************************************************
#define TX_FIFO_SIZE            (8)         // Number of entries in the TX FIFO
#define RX_FIFO_SIZE            (8)         // Number of entries in the RX FIFO

//*****************************************************************************
//
// The following are deprecated defines for the bit fields in the interrupt
// mask set and clear, raw interrupt, masked interrupt, and interrupt clear
// registers.
//
//*****************************************************************************
#define SSI_INT_TXFF            0x00000008  // TX FIFO interrupt
#define SSI_INT_RXFF            0x00000004  // RX FIFO interrupt
#define SSI_INT_RXTO            0x00000002  // RX timeout interrupt
#define SSI_INT_RXOR            0x00000001  // RX overrun interrupt

#endif

#endif // __HW_SSI_H__

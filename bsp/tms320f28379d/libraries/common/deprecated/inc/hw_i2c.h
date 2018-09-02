//###########################################################################
//
// FILE:    hw_i2c.h
//
// TITLE:   Definitions for the C28x I2C registers.
//
//###########################################################################
// $TI Release: F2837xD Support Library v3.05.00.00 $
// $Release Date: Tue Jun 26 03:15:23 CDT 2018 $
// $Copyright:
// Copyright (C) 2013-2018 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef __HW_I2C_H__
#define __HW_I2C_H__

//*****************************************************************************
//
// The following are defines for the I2C register offsets
//
//*****************************************************************************
#define I2C_O_OAR                 0x0         // I2C Own address
#define I2C_O_IER                 0x1         // I2C Interrupt Enable
#define I2C_O_STR                 0x2         // I2C Status
#define I2C_O_CLKL                0x3         // I2C Clock low-time divider
#define I2C_O_CLKH                0x4         // I2C Clock high-time divider
#define I2C_O_CNT                 0x5         // I2C Data count
#define I2C_O_DRR                 0x6         // I2C Data receive
#define I2C_O_SAR                 0x7         // I2C Slave address
#define I2C_O_DXR                 0x8         // I2C Data Transmit
#define I2C_O_MDR                 0x9         // I2C Mode
#define I2C_O_ISRC                0xA         // I2C Interrupt Source
#define I2C_O_EMDR                0xB         // I2C Extended Mode
#define I2C_O_PSC                 0xC         // I2C Prescaler
#define I2C_O_FFTX                0x20        // I2C FIFO Transmit
#define I2C_O_FFRX                0x21        // I2C FIFO Receive

//*****************************************************************************
//
// The following are defines for the bit fields in the I2COAR register
//
//*****************************************************************************
#define I2C_OAR_OAR_S             0
#define I2C_OAR_OAR_M             0x3FF       // I2C Own address

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CIER register
//
//*****************************************************************************
#define I2C_IER_ARBL              0x1         // Arbitration-lost interrupt
                                              // enable
#define I2C_IER_NACK              0x2         // No-acknowledgment interrupt
                                              // enable
#define I2C_IER_ARDY              0x4         // Register-access-ready interrupt
                                              // enable
#define I2C_IER_RRDY              0x8         // Receive-data-ready interrupt
                                              // enable
#define I2C_IER_XRDY              0x10        // Transmit-data-ready interrupt
                                              // enable
#define I2C_IER_SCD               0x20        // Stop condition detected
                                              // interrupt enable
#define I2C_IER_AAS               0x40        // Addressed as slave interrupt
                                              // enable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CSTR register
//
//*****************************************************************************
#define I2C_STR_ARBL              0x1         // Arbitration-lost interrupt flag
                                              // bit
#define I2C_STR_NACK              0x2         // No-acknowledgment interrupt
                                              // flag bit.
#define I2C_STR_ARDY              0x4         // Register-access-ready interrupt
                                              // flag bit
#define I2C_STR_RRDY              0x8         // Receive-data-ready interrupt
                                              // flag bit.
#define I2C_STR_XRDY              0x10        // Transmit-data-ready interrupt
                                              // flag bit.
#define I2C_STR_SCD               0x20        // Stop condition detected bit.
#define I2C_STR_AD0               0x100       // Address 0 bits
#define I2C_STR_AAS               0x200       // Addressed-as-slave bit
#define I2C_STR_XSMT              0x400       // Transmit shift register empty
                                              // bit.
#define I2C_STR_RSFULL            0x800       // Receive shift register full
                                              // bit.
#define I2C_STR_BB                0x1000      // Bus busy bit.
#define I2C_STR_NACKSNT           0x2000      // NACK sent bit.
#define I2C_STR_SDIR              0x4000      // Slave direction bit

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CCLKL register
//
//*****************************************************************************
#define I2C_CLKL_I2CCLKL_S        0
#define I2C_CLKL_I2CCLKL_M        0xFFFF      // Clock low-time divide-down
                                              // value.

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CCLKH register
//
//*****************************************************************************
#define I2C_CLKH_I2CCLKH_S        0
#define I2C_CLKH_I2CCLKH_M        0xFFFF      // Clock high-time divide-down
                                              // value.

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CCNT register
//
//*****************************************************************************
#define I2C_CNT_I2CCNT_S          0
#define I2C_CNT_I2CCNT_M          0xFFFF      // Data count value.

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CDRR register
//
//*****************************************************************************
#define I2C_DRR_DATA_S            0
#define I2C_DRR_DATA_M            0xFF        // Receive data

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CSAR register
//
//*****************************************************************************
#define I2C_SAR_SAR_S             0
#define I2C_SAR_SAR_M             0x3FF       // Slave Address

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CDXR register
//
//*****************************************************************************
#define I2C_DXR_DATA_S            0
#define I2C_DXR_DATA_M            0xFF        // Transmit data

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CMDR register
//
//*****************************************************************************
#define I2C_MDR_BC_S              0
#define I2C_MDR_BC_M              0x7         // Bit count bits.
#define I2C_MDR_FDF               0x8         // Free Data Format
#define I2C_MDR_STB               0x10        // START Byte Mode
#define I2C_MDR_IRS               0x20        // I2C Module Reset
#define I2C_MDR_DLB               0x40        // Digital Loopback Mode
#define I2C_MDR_RM                0x80        // Repeat Mode
#define I2C_MDR_XA                0x100       // Expanded Address Mode
#define I2C_MDR_TRX               0x200       // Transmitter Mode
#define I2C_MDR_MST               0x400       // Master Mode
#define I2C_MDR_STP               0x800       // STOP Condition
#define I2C_MDR_STT               0x2000      // START condition bit
#define I2C_MDR_FREE              0x4000      // Debug Action
#define I2C_MDR_NACKMOD           0x8000      // NACK mode bit

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CISRC register
//
//*****************************************************************************
#define I2C_ISRC_INTCODE_S        0
#define I2C_ISRC_INTCODE_M        0x7         // Interrupt code bits.

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CEMDR register
//
//*****************************************************************************
#define I2C_EMDR_BC               0x1         // Backwards compatibility mode

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CPSC register
//
//*****************************************************************************
#define I2C_PSC_IPSC_S            0
#define I2C_PSC_IPSC_M            0xFF        // I2C Prescaler Divide Down

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CFFTX register
//
//*****************************************************************************
#define I2C_FFTX_TXFFIL_S         0
#define I2C_FFTX_TXFFIL_M         0x1F        // Transmit FIFO Interrupt Level
#define I2C_FFTX_TXFFIENA         0x20        // Transmit FIFO Interrupt Enable
#define I2C_FFTX_TXFFINTCLR       0x40        // Transmit FIFO Interrupt Flag
                                              // Clear
#define I2C_FFTX_TXFFINT          0x80        // Transmit FIFO Interrupt Flag
#define I2C_FFTX_TXFFST_S         8
#define I2C_FFTX_TXFFST_M         0x1F00      // Transmit FIFO Status
#define I2C_FFTX_TXFFRST          0x2000      // Transmit FIFO Reset
#define I2C_FFTX_I2CFFEN          0x4000      // Transmit FIFO Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2CFFRX register
//
//*****************************************************************************
#define I2C_FFRX_RXFFIL_S         0
#define I2C_FFRX_RXFFIL_M         0x1F        // Receive FIFO Interrupt Level
#define I2C_FFRX_RXFFIENA         0x20        // Receive FIFO Interrupt Enable
#define I2C_FFRX_RXFFINTCLR       0x40        // Receive FIFO Interrupt Flag
                                              // Clear
#define I2C_FFRX_RXFFINT          0x80        // Receive FIFO Interrupt Flag
#define I2C_FFRX_RXFFST_S         8
#define I2C_FFRX_RXFFST_M         0x1F00      // Receive FIFO Status
#define I2C_FFRX_RXFFRST          0x2000      // Receive FIFO Reset
#endif

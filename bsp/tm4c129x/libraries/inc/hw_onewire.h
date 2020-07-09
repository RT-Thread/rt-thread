//*****************************************************************************
//
// hw_onewire.h - Macros used when accessing the One wire hardware.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
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
// 
// This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_ONEWIRE_H__
#define __HW_ONEWIRE_H__

//*****************************************************************************
//
// The following are defines for the One wire register offsets.
//
//*****************************************************************************
#define ONEWIRE_O_CS            0x00000000  // 1-Wire Control and Status
#define ONEWIRE_O_TIM           0x00000004  // 1-Wire Timing Override
#define ONEWIRE_O_DATW          0x00000008  // 1-Wire Data Write
#define ONEWIRE_O_DATR          0x0000000C  // 1-Wire Data Read
#define ONEWIRE_O_IM            0x00000100  // 1-Wire Interrupt Mask
#define ONEWIRE_O_RIS           0x00000104  // 1-Wire Raw Interrupt Status
#define ONEWIRE_O_MIS           0x00000108  // 1-Wire Masked Interrupt Status
#define ONEWIRE_O_ICR           0x0000010C  // 1-Wire Interrupt Clear
#define ONEWIRE_O_DMA           0x00000120  // 1-Wire uDMA Control
#define ONEWIRE_O_PP            0x00000FC0  // 1-Wire Peripheral Properties

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_CS register.
//
//*****************************************************************************
#define ONEWIRE_CS_USEALT       0x80000000  // Two Wire Enable
#define ONEWIRE_CS_ALTP         0x40000000  // Alternate Polarity Enable
#define ONEWIRE_CS_BSIZE_M      0x00070000  // Last Byte Size
#define ONEWIRE_CS_BSIZE_8      0x00000000  // 8 bits (1 byte)
#define ONEWIRE_CS_BSIZE_1      0x00010000  // 1 bit
#define ONEWIRE_CS_BSIZE_2      0x00020000  // 2 bits
#define ONEWIRE_CS_BSIZE_3      0x00030000  // 3 bits
#define ONEWIRE_CS_BSIZE_4      0x00040000  // 4 bits
#define ONEWIRE_CS_BSIZE_5      0x00050000  // 5 bits
#define ONEWIRE_CS_BSIZE_6      0x00060000  // 6 bits
#define ONEWIRE_CS_BSIZE_7      0x00070000  // 7 bits
#define ONEWIRE_CS_STUCK        0x00000400  // STUCK Status
#define ONEWIRE_CS_NOATR        0x00000200  // Answer-to-Reset Status
#define ONEWIRE_CS_BUSY         0x00000100  // Busy Status
#define ONEWIRE_CS_SKATR        0x00000080  // Skip Answer-to-Reset Enable
#define ONEWIRE_CS_LSAM         0x00000040  // Late Sample Enable
#define ONEWIRE_CS_ODRV         0x00000020  // Overdrive Enable
#define ONEWIRE_CS_SZ_M         0x00000018  // Data Operation Size
#define ONEWIRE_CS_OP_M         0x00000006  // Operation Request
#define ONEWIRE_CS_OP_NONE      0x00000000  // No operation
#define ONEWIRE_CS_OP_RD        0x00000002  // Read
#define ONEWIRE_CS_OP_WR        0x00000004  // Write
#define ONEWIRE_CS_OP_WRRD      0x00000006  // Write/Read
#define ONEWIRE_CS_RST          0x00000001  // Reset Request
#define ONEWIRE_CS_SZ_S         3

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_TIM register.
//
//*****************************************************************************
#define ONEWIRE_TIM_W1TIM_M     0xF0000000  // Value '1' Timing
#define ONEWIRE_TIM_W0TIM_M     0x0F800000  // Value '0' Timing
#define ONEWIRE_TIM_W0REST_M    0x00780000  // Rest Time
#define ONEWIRE_TIM_W1SAM_M     0x00078000  // Sample Time
#define ONEWIRE_TIM_ATRSAM_M    0x00007800  // Answer-to-Reset Sample
#define ONEWIRE_TIM_ATRTIM_M    0x000007C0  // Answer-to-Reset/Rest Period
#define ONEWIRE_TIM_RSTTIM_M    0x0000003F  // Reset Low Time
#define ONEWIRE_TIM_W1TIM_S     28
#define ONEWIRE_TIM_W0TIM_S     23
#define ONEWIRE_TIM_W0REST_S    19
#define ONEWIRE_TIM_W1SAM_S     15
#define ONEWIRE_TIM_ATRSAM_S    11
#define ONEWIRE_TIM_ATRTIM_S    6
#define ONEWIRE_TIM_RSTTIM_S    0

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_DATW register.
//
//*****************************************************************************
#define ONEWIRE_DATW_B3_M       0xFF000000  // Upper Data Byte
#define ONEWIRE_DATW_B2_M       0x00FF0000  // Upper Middle Data Byte
#define ONEWIRE_DATW_B1_M       0x0000FF00  // Lower Middle Data Byte
#define ONEWIRE_DATW_B0_M       0x000000FF  // Lowest Data Byte
#define ONEWIRE_DATW_B3_S       24
#define ONEWIRE_DATW_B2_S       16
#define ONEWIRE_DATW_B1_S       8
#define ONEWIRE_DATW_B0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_DATR register.
//
//*****************************************************************************
#define ONEWIRE_DATR_B3_M       0xFF000000  // Upper Data Byte
#define ONEWIRE_DATR_B2_M       0x00FF0000  // Upper Middle Data Byte
#define ONEWIRE_DATR_B1_M       0x0000FF00  // Lower Middle Data Byte
#define ONEWIRE_DATR_B0_M       0x000000FF  // Lowest Data Byte
#define ONEWIRE_DATR_B3_S       24
#define ONEWIRE_DATR_B2_S       16
#define ONEWIRE_DATR_B1_S       8
#define ONEWIRE_DATR_B0_S       0

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_IM register.
//
//*****************************************************************************
#define ONEWIRE_IM_DMA          0x00000010  // DMA Done Interrupt Mask
#define ONEWIRE_IM_STUCK        0x00000008  // Stuck Status Interrupt Mask
#define ONEWIRE_IM_NOATR        0x00000004  // No Answer-to-Reset Interrupt
                                            // Mask
#define ONEWIRE_IM_OPC          0x00000002  // Operation Complete Interrupt
                                            // Mask
#define ONEWIRE_IM_RST          0x00000001  // Reset Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_RIS register.
//
//*****************************************************************************
#define ONEWIRE_RIS_DMA         0x00000010  // DMA Done Raw Interrupt Status
#define ONEWIRE_RIS_STUCK       0x00000008  // Stuck Status Raw Interrupt
                                            // Status
#define ONEWIRE_RIS_NOATR       0x00000004  // No Answer-to-Reset Raw Interrupt
                                            // Status
#define ONEWIRE_RIS_OPC         0x00000002  // Operation Complete Raw Interrupt
                                            // Status
#define ONEWIRE_RIS_RST         0x00000001  // Reset Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_MIS register.
//
//*****************************************************************************
#define ONEWIRE_MIS_DMA         0x00000010  // DMA Done Masked Interrupt Status
#define ONEWIRE_MIS_STUCK       0x00000008  // Stuck Status Masked Interrupt
                                            // Status
#define ONEWIRE_MIS_NOATR       0x00000004  // No Answer-to-Reset Masked
                                            // Interrupt Status
#define ONEWIRE_MIS_OPC         0x00000002  // Operation Complete Masked
                                            // Interrupt Status
#define ONEWIRE_MIS_RST         0x00000001  // Reset Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_ICR register.
//
//*****************************************************************************
#define ONEWIRE_ICR_DMA         0x00000010  // DMA Done Interrupt Clear
#define ONEWIRE_ICR_STUCK       0x00000008  // Stuck Status Interrupt Clear
#define ONEWIRE_ICR_NOATR       0x00000004  // No Answer-to-Reset Interrupt
                                            // Clear
#define ONEWIRE_ICR_OPC         0x00000002  // Operation Complete Interrupt
                                            // Clear
#define ONEWIRE_ICR_RST         0x00000001  // Reset Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_DMA register.
//
//*****************************************************************************
#define ONEWIRE_DMA_SG          0x00000008  // Scatter-Gather Enable
#define ONEWIRE_DMA_DMAOP_M     0x00000006  // uDMA Operation
#define ONEWIRE_DMA_DMAOP_DIS   0x00000000  // uDMA disabled
#define ONEWIRE_DMA_DMAOP_RDSNG 0x00000002  // uDMA single read: 1-Wire
                                            // requests uDMA to read
                                            // ONEWIREDATR register after each
                                            // read transaction
#define ONEWIRE_DMA_DMAOP_WRMUL 0x00000004  // uDMA multiple write: 1-Wire
                                            // requests uDMA to load whenever
                                            // the ONEWIREDATW register is
                                            // empty
#define ONEWIRE_DMA_DMAOP_RDMUL 0x00000006  // uDMA multiple read: An initial
                                            // read occurs and subsequent reads
                                            // start after uDMA has read the
                                            // ONEWIREDATR register
#define ONEWIRE_DMA_RST         0x00000001  // uDMA Reset

//*****************************************************************************
//
// The following are defines for the bit fields in the ONEWIRE_O_PP register.
//
//*****************************************************************************
#define ONEWIRE_PP_DMAP         0x00000010  // uDMA Present
#define ONEWIRE_PP_CNT_M        0x00000003  // 1-Wire Bus Count
#define ONEWIRE_PP_CNT_S        0

#endif // __HW_ONEWIRE_H__

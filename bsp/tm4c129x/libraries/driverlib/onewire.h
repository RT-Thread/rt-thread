//*****************************************************************************
//
// onewire.h - Prototypes for the OneWire Driver.
//
// Copyright (c) 2012-2014 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.1.0.12573 of the Tiva Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __DRIVERLIB_ONEWIRE_H__
#define __DRIVERLIB_ONEWIRE_H__

//*****************************************************************************
//
//! \addtogroup onewire_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// Defines used in the OneWireInit() function call.
//
//*****************************************************************************

//
// This define is used in initialization to request standard speed bus
// timings.  This is the default.
//
#define ONEWIRE_INIT_SPD_STD    0x00000000

//
// This define is used in initialization to request overdrive speed bus
// timings.
//
#define ONEWIRE_INIT_SPD_OD     0x00000020

//
// This define is used in initialization to request standard read sampling
// timing (2us for ONEWIRE_INIT_SPD_OD and 16us for ONEWIRE_INIT_SPD_STD).
// This is the default.
//
#define ONEWIRE_INIT_READ_STD   0x00000000

//
// This define is used in initialization to request late read sampling
// timing (7us for ONEWIRE_INIT_SPD_OD and 50us for ONEWIRE_INIT_SPD_STD).
//
#define ONEWIRE_INIT_READ_LATE  0x00000040

//
// This define is used in initialization to request a standard
// Answer-to-Reset (presence detect) monitor.  This is the default.
//
#define ONEWIRE_INIT_ATR        0x00000000

//
// This define is used in initialization to request no Answer-to-Reset
// (presence detect) monitor.  The module will delay operations after a bus
// reset for the expected presence detect period in this case.
//
#define ONEWIRE_INIT_NO_ATR     0x00000080

//
// This define is used in initialization to request standard signal polarity
// on the 1-Wire bus (pin is driven low to drive bus low).  This is the
// default.
//
#define ONEWIRE_INIT_STD_POL    0x00000000

//
// This define is used in initialization to request alternate signal polarity
// on the 1-Wire bus (pin is driven high to drive bus low).
//
#define ONEWIRE_INIT_ALT_POL    0x40000000

//
// This define is used in initialization to request normal 1-Wire operational
// mode.  This is the default.
//
#define ONEWIRE_INIT_1_WIRE_CFG 0x00000000

//
// This define is used in initialization to request a 2 pin operational
// mode where one pin is used exclusively for TX operations and the other
// for RX.
//
#define ONEWIRE_INIT_2_WIRE_CFG 0x80000000

//*****************************************************************************
//
// Defines for bus status conditions.  These values can be returned by
// OneWireBusStatus().
//
//*****************************************************************************

//
// This will be set if the bus is busy handling a Read, Write or
// Reset activity.
//
#define ONEWIRE_BUS_STATUS_BUSY 0x00000100

//
// This will be set if the module did not detect any slave presence pulses
// after a bus reset.
//
#define ONEWIRE_BUS_STATUS_NO_SLAVE                                           \
                                0x00000200

//
// This will be set if the bus is being held low outside of a normal Read,
// Write or Reset activity.
//
#define ONEWIRE_BUS_STATUS_STUCK                                              \
                                0x00000400

//*****************************************************************************
//
// OneWire operation modes used with OneWireTransaction().
//
//*****************************************************************************

//
// This mode flag indicates a single reset should be issued prior to a write
// and/or read operation.
//
#define ONEWIRE_OP_RESET        0x00000001

//
// This mode flag indicates a read operation.
//
#define ONEWIRE_OP_READ         0x00000002

//
// This mode flag indicates a write operation.
//
#define ONEWIRE_OP_WRITE        0x00000004

//*****************************************************************************
//
// OneWire DMA used with OneWireDMAEnable().
//
//*****************************************************************************

//
// This indicates the DMA should issue a 1-Wire bus reset before starting.
//
#define ONEWIRE_DMA_BUS_RESET   0x00000001

//
// The DMA operation will be a single Read after each module transaction.
//
#define ONEWIRE_DMA_OP_READ     0x00000002

//
// The DMA will write values to the 1-Wire interface as each previous DMA
// write operation completes.
//
#define ONEWIRE_DMA_OP_MULTI_WRITE                                            \
                                0x00000004

//
// The DMA will read values from the 1-Wire interface as each previous DMA
// read operation completes.
//
#define ONEWIRE_DMA_OP_MULTI_READ                                             \
                                0x00000006

//
// This Scatter Gather DMA mode is paired with ONEWIRE_DMA_OP_READ to instruct
// the 1-Wire DMA to initiate an operation at the start of and then on each
// transition completion thereafter.
//
#define ONEWIRE_DMA_MODE_SG     0x00000008

//
// DMA expects a Read/Write bus operation size of 8 bits.  This should match
// the uDMA channel setup.
//
#define ONEWIRE_DMA_OP_SZ_8     0x00000000

//
// DMA expects a Read/Write bus operation size of 16 bits.  This should match
// the uDMA channel setup.
//
#define ONEWIRE_DMA_OP_SZ_16    0x00000800

//
// DMA expects a Read/Write bus operation size of 32 bits.  This should match
// the uDMA channel setup.
//
#define ONEWIRE_DMA_OP_SZ_32    0x00001800

//*****************************************************************************
//
// OneWire interrupt defines.  Use in calls to OneWireIntEnable(),
// OneWireIntDisable(), OneWireIntClear() and returned by OneWireIntStatus().
//
//*****************************************************************************

//
// This interrupt indicates a bus reset has just completed.
//
#define ONEWIRE_INT_RESET_DONE  0x00000001

//
// The interrupt indicates a Read or Write master initiated operation
// has just completed.
//
#define ONEWIRE_INT_OP_DONE     0x00000002

//
// This interrupt indicates that no presence detect was signaled by a slave
// on the bus after a reset.
//
#define ONEWIRE_INT_NO_SLAVE    0x00000004

//
// This interrupt indicates the bus is being held low outside of normal
// operations.
//
#define ONEWIRE_INT_STUCK       0x00000008

//
// This interrupt indicates a OneWire DMA operation has completed.
//
#define ONEWIRE_INT_DMA_DONE    0x00000010

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern void OneWireBusReset(uint32_t ui32Base);
extern uint32_t OneWireBusStatus(uint32_t ui32Base);
extern void OneWireDataGet(uint32_t u3i2Base, uint32_t *pui32Data);
extern bool OneWireDataGetNonBlocking(uint32_t ui32Base, uint32_t *pui32Data);
extern void OneWireDMADisable(uint32_t ui32Base, uint32_t ui32DMAFlags);
extern void OneWireDMAEnable(uint32_t ui32Base, uint32_t ui32DMAFlags);
extern void OneWireInit(uint32_t ui32Base, uint32_t ui32InitFlags);
extern void OneWireIntClear(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void OneWireIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void OneWireIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags);
extern void OneWireIntRegister(uint32_t ui32Base, void (*pfnHandler)(void));
extern void OneWireIntUnregister(uint32_t ui32Base);
extern uint32_t OneWireIntStatus(uint32_t ui32Base, bool bMasked);
extern void OneWireTransaction(uint32_t ui32Base, uint32_t ui32OpFlags,
                               uint32_t ui32Data, uint32_t ui32BitCnt);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_ONEWIRE_H__

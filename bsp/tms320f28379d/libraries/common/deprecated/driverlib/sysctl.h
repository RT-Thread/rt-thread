//###########################################################################
//
// FILE:   sysctl.h
//
// TITLE:  Stellaris style wrapper driver for F2837x system control.
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

#ifndef __SYSCTL_H__
#define __SYSCTL_H__

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
//! \addtogroup sysctl_api
//! @{
//
//*****************************************************************************
#include "inc/hw_types.h"
//*****************************************************************************
//
//! Defined system clock oscillator source speed.  Adjust this to reflect your
//! actual clock speed.
//
//*****************************************************************************
#if defined(_LAUNCHXL_F28379D) || defined(_LAUNCHXL_F28377S)
#define SYSTEM_CLOCK_SPEED      10000000
#else
#define SYSTEM_CLOCK_SPEED      20000000
#endif

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlClockSet() API as
// the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_SYSDIV_M         0x00001F80
#define SYSCTL_SYSDIV_S         0x00000007
// Only 1 or even values up to 126 are allowed
#define SYSCTL_SYSDIV(x)        ((((x == 1) ? 0 : (x / 2)) << SYSCTL_SYSDIV_S) & SYSCTL_SYSDIV_M)

#define SYSCTL_IMULT_M          0x0000007F
#define SYSCTL_IMULT_S          0x00000000
#define SYSCTL_IMULT(x)         (((x) << SYSCTL_IMULT_S) & SYSCTL_IMULT_M)

#define SYSCTL_FMULT_M          0x00006000
#define SYSCTL_FMULT_S          0x0000000D
#define SYSCTL_FMULT_0          0x00000000
#define SYSCTL_FMULT_1_4        0x00002000
#define SYSCTL_FMULT_1_2        0x00004000
#define SYSCTL_FMULT_3_4        0x00006000

#define SYSCTL_OSCSRC_M         0x00030000
#define SYSCTL_OSCSRC_S         0x00000010
#define SYSCTL_OSCSRC_OSC2      0x00000000
#define SYSCTL_OSCSRC_XTAL      0x00010000
#define SYSCTL_OSCSRC_OSC1      0x00020000

#define SYSCTL_LSDIV_M          0x00700000
#define SYSCTL_LSDIV_S          0x00000014
// Only 1 or even values up to 14 are allowed
#define SYSCTL_LSDIV(x)         (((x == 1) ? 0 : (x / 2)) << SYSCTL_LSDIV_S) & SYSCTL_LSDIV_M)

#define SYSCTL_PLL_ENABLE       0x80000000
#define SYSCTL_PLL_DISABLE      0x00000000

//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
// SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
// ui32Peripheral parameter.  The peripherals in the fourth group (upper nibble
// is 3) can only be used with the SysCtlPeripheralPresent() API.
//
//*****************************************************************************
#define SYSCTL_PERIPH_REG_M             0x0000001F
#define SYSCTL_PERIPH_REG_S             0x00000000

#define SYSCTL_PERIPH_BIT_M             0x003F0000
#define SYSCTL_PERIPH_BIT_S             0x00000010

//PCLKCR0
#define SYSCTL_PERIPH_CLA1              0x00000000
#define SYSCTL_PERIPH_DMA               0x00020000
#define SYSCTL_PERIPH_TIMER0            0x00030000
#define SYSCTL_PERIPH_TIMER1            0x00040000
#define SYSCTL_PERIPH_TIMER2            0x00050000
#define SYSCTL_PERIPH_HRPWM             0x00100000
#define SYSCTL_PERIPH_TBCLKSYNC         0x00120000
#define SYSCTL_PERIPH_GTBCLKSYNC        0x00130000

//PCLKCR1
#define SYSCTL_PERIPH_EMIF1             0x00000001
#define SYSCTL_PERIPH_EMIF2             0x00010001

//PCLKCR2
#define SYSCTL_PERIPH_EPWM1             0x00000002
#define SYSCTL_PERIPH_EPWM2             0x00010002
#define SYSCTL_PERIPH_EPWM3             0x00020002
#define SYSCTL_PERIPH_EPWM4             0x00030002
#define SYSCTL_PERIPH_EPWM5             0x00040002
#define SYSCTL_PERIPH_EPWM6             0x00050002
#define SYSCTL_PERIPH_EPWM7             0x00060002
#define SYSCTL_PERIPH_EPWM8             0x00070002
#define SYSCTL_PERIPH_EPWM9             0x00080002
#define SYSCTL_PERIPH_EPWM10            0x00090002
#define SYSCTL_PERIPH_EPWM11            0x000A0002
#define SYSCTL_PERIPH_EPWM12            0x000B0002

//PCLKCR3
#define SYSCTL_PERIPH_ECAP1             0x00000003
#define SYSCTL_PERIPH_ECAP2             0x00010003
#define SYSCTL_PERIPH_ECAP3             0x00020003
#define SYSCTL_PERIPH_ECAP4             0x00030003
#define SYSCTL_PERIPH_ECAP5             0x00040003
#define SYSCTL_PERIPH_ECAP6             0x00050003

//PCLKCR4
#define SYSCTL_PERIPH_EQEP1             0x00000004
#define SYSCTL_PERIPH_EQEP2             0x00010004
#define SYSCTL_PERIPH_EQEP3             0x00020004

//PCLKCR5
//Reserved

//PCLKCR6
#define SYSCTL_PERIPH_SD1               0x00000006
#define SYSCTL_PERIPH_SD2               0x00010006

//PCLKCR7
#define SYSCTL_PERIPH_SCI1              0x00000007
#define SYSCTL_PERIPH_SCI2              0x00010007
#define SYSCTL_PERIPH_SCI3              0x00020007
#define SYSCTL_PERIPH_SCI4              0x00030007

//PCLKCR8
#define SYSCTL_PERIPH_SPI1              0x00000008
#define SYSCTL_PERIPH_SPI2              0x00010008
#define SYSCTL_PERIPH_SPI3              0x00020008

//PCLKCR9
#define SYSCTL_PERIPH_I2C1              0x00000009
#define SYSCTL_PERIPH_I2C2              0x00010009

//PCLKCR10
#define SYSCTL_PERIPH_CAN1              0x0000000A
#define SYSCTL_PERIPH_CAN2              0x0001000A

//PCLKCR11
#define SYSCTL_PERIPH_MCBSP1            0x0000000B
#define SYSCTL_PERIPH_MCBSP2            0x0001000B
#define SYSCTL_PERIPH_USB0              0x0010000B

//PCLKCR12
#define SYSCTL_PERIPH_UPP1              0x0000000C

//PCLKCR13
#define SYSCTL_PERIPH_ADC1              0x0000000D
#define SYSCTL_PERIPH_ADC2              0x0001000D
#define SYSCTL_PERIPH_ADC3              0x0002000D
#define SYSCTL_PERIPH_ADC4              0x0003000D

//PCLKCR14
#define SYSCTL_PERIPH_CMPSS1            0x0000000E
#define SYSCTL_PERIPH_CMPSS2            0x0001000E
#define SYSCTL_PERIPH_CMPSS3            0x0002000E
#define SYSCTL_PERIPH_CMPSS4            0x0003000E
#define SYSCTL_PERIPH_CMPSS5            0x0004000E
#define SYSCTL_PERIPH_CMPSS6            0x0005000E
#define SYSCTL_PERIPH_CMPSS7            0x0006000E
#define SYSCTL_PERIPH_CMPSS8            0x0007000E

//PCLKCR15
//Reserved

//PCLKCR16
#define SYSCTL_PERIPH_BUFFDAC1          0x00000010
#define SYSCTL_PERIPH_BUFFDAC2          0x00010010
#define SYSCTL_PERIPH_BUFFDAC3          0x00020010


//old
//#define SYSCTL_PERIPH_UART_A     0x1  // SCI A
//#define SYSCTL_PERIPH_UART_B     0x2  // SCI B
//#define SYSCTL_PERIPH_UART_C     0x3  // SCI C
//#define SYSCTL_PERIPH_UART_D     0x4  // SCI D
//
//#define SYSCTL_PERIPH_SPI_A      0x5  // SPI A
//#define SYSCTL_PERIPH_SPI_B      0x6  // SPI B
//#define SYSCTL_PERIPH_SPI_C      0x7  // SPI C
//
//#define SYSCTL_PERIPH_MCBSP_A    0x8  // McBSP A
//#define SYSCTL_PERIPH_MCBSP_B    0x9  // McBSP B
//
//#define SYSCTL_PERIPH_DMA        0xA  // DMA
//
//#define SYSCTL_PERIPH_USB0       0xB  // USBA

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

extern uint32_t SysCtlSRAMSizeGet(void);
extern uint32_t SysCtlFlashSizeGet(void);
extern void SysCtlPeripheralReset(uint32_t ui32Peripheral);
extern void SysCtlPeripheralEnable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralDisable(uint32_t ui32Peripheral);
extern bool SysCtlPeripheralPresent(uint32_t ui32Peripheral);
extern void SysCtlDelay(uint32_t ulCount);
extern uint32_t SysCtlClockGet(uint32_t u32ClockIn);
extern void SysCtlClockSet(uint32_t ui32Config);
extern void SysCtlAuxClockSet(uint32_t ui32Config);
extern uint32_t SysCtlLowSpeedClockGet(uint32_t u32ClockIn);
extern void SysCtlUSBPLLEnable(void);
extern void SysCtlUSBPLLDisable(void);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __SYSCTL_H__



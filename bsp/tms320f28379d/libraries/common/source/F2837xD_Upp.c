//###########################################################################
//
// FILE:   F2837xD_Upp.c
//
// TITLE:  F2837xD Upp Initialization & Support Functions.
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

//
// Included Files
//
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

//
// InitUpp1Gpio - Initialize UPP1 GPIOs
//
void InitUpp1Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO10 = 1; // Disable pull-up on GPIO10 (uPP_WAIT)
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1; // Disable pull-up on GPIO11 (uPP_START)
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1; // Disable pull-up on GPIO12 (uPP_ENA)
    GpioCtrlRegs.GPAPUD.bit.GPIO13 = 1; // Disable pull-up on GPIO13 (uPP_D7)
    GpioCtrlRegs.GPAPUD.bit.GPIO14 = 1; // Disable pull-up on GPIO14 (uPP_D6)
    GpioCtrlRegs.GPAPUD.bit.GPIO15 = 1; // Disable pull-up on GPIO15 (uPP_D5)
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 1; // Disable pull-up on GPIO16 (uPP_D4)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 1; // Disable pull-up on GPIO17 (uPP_D3)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 1; // Disable pull-up on GPIO18 (uPP_D2)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 1; // Disable pull-up on GPIO19 (uPP_D1)
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1; // Disable pull-up on GPIO20 (uPP_D0)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1; // Disable pull-up on GPIO21 (uPP_CLK)

    //
    // Disable QUAL for selected pins (ASYNC Input)
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = 3; // Disable pull-up on GPIO10 (uPP_WAIT)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3; // Disable pull-up on GPIO11 (uPP_START)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // Disable pull-up on GPIO12 (uPP_ENA)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // Disable pull-up on GPIO13 (uPP_D7)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // Disable pull-up on GPIO14 (uPP_D6)
    GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // Disable pull-up on GPIO15 (uPP_D5)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Disable pull-up on GPIO16 (uPP_D4)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Disable pull-up on GPIO17 (uPP_D3)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Disable pull-up on GPIO18 (uPP_D2)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Disable pull-up on GPIO19 (uPP_D1)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 3; // Disable pull-up on GPIO20 (uPP_D0)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3; // Disable pull-up on GPIO21 (uPP_CLK)

    //
    // Configure uPP-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM1 functional
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 3;   // Configure GPIO10 as uPP_WAIT
    GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 3;   // Configure GPIO11 as uPP_START
    GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = 3;   // Configure GPIO12 as uPP_ENA
    GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = 3;   // Configure GPIO13 as uPP_D7
    GpioCtrlRegs.GPAGMUX1.bit.GPIO14 = 3;   // Configure GPIO14 as uPP_D6
    GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = 3;   // Configure GPIO15 as uPP_D5
    GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 3;   // Configure GPIO16 as uPP_D4
    GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = 3;   // Configure GPIO17 as uPP_D3
    GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 3;   // Configure GPIO18 as uPP_D2
    GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 3;   // Configure GPIO19 as uPP_D1
    GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = 3;   // Configure GPIO20 as uPP_D0
    GpioCtrlRegs.GPAGMUX2.bit.GPIO21 = 3;   // Configure GPIO21 as uPP_CLK

    GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 3;   // Configure GPIO10 as uPP_WAIT
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;   // Configure GPIO11 as uPP_START
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 3;   // Configure GPIO12 as uPP_ENA
    GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 3;   // Configure GPIO13 as uPP_D7
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 3;   // Configure GPIO14 as uPP_D6
    GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 3;   // Configure GPIO15 as uPP_D5
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;   // Configure GPIO16 as uPP_D4
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;   // Configure GPIO17 as uPP_D3
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;   // Configure GPIO18 as uPP_D2
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;   // Configure GPIO19 as uPP_D1
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;   // Configure GPIO20 as uPP_D0
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;   // Configure GPIO21 as uPP_CLK

    EDIS;
}

//
// SoftResetUpp - Trigger an internal uPP reset
//
void SoftResetUpp(void)
{
    UppRegs.PERCTL.bit.SOFTRST = 1;  // Issue uPP Internal Reset.
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    asm("          NOP");
    UppRegs.PERCTL.bit.SOFTRST = 0;  // Release uPP Internal Reset.
}

//
// End of file
//

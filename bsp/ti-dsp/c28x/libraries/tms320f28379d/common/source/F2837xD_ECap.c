//###########################################################################
//
// FILE:   F2837xD_ECap.c
//
// TITLE:  F2837xD eCAP Initialization & Support Functions.
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
// InitECap - This function initializes the eCAP(s) to a known state.
//
void InitECap(void)
{
    // Initialize eCAP1/2/3/4/5/6

    //tbd...
}

//
// InitECapGpio - This function initializes GPIO pins to function as ECAP pins
//                Each GPIO pin can be configured as a GPIO pin or up to 3
//                different peripheral functional pins. By default all pins
//                come up as GPIO inputs after reset.
//                Caution:
//                For each eCAP peripheral
//                Only one GPIO pin should be enabled for ECAP operation.
//                Comment out other unwanted lines.
//
void InitECapGpio()
{
}

//
// InitECap1Gpio - Initialize ECAP1 GPIOs
//
void InitECap1Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT7SELECT = pin;         // Set eCAP1 source to GPIO-pin
    EDIS;
}

//
// InitECap2Gpio - Initialize ECAP2 GPIOs
//
void InitECap2Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT8SELECT = pin;         // Set eCAP2 source to GPIO-pin
    EDIS;
}

//
// InitECap3Gpio - Initialize ECAP3 GPIOs
//
void InitECap3Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT9SELECT = pin;         // Set eCAP3 source to GPIO-pin
    EDIS;
}

//
// InitECap4Gpio - Initialize ECAP4 GPIOs
//
void InitECap4Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT10SELECT = pin;         // Set eCAP4 source to GPIO-pin
    EDIS;
}

//
// InitECap5Gpio - Initialize ECAP5 GPIOs
//
void InitECap5Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT11SELECT = pin;         // Set eCAP5 source to GPIO-pin
    EDIS;
}

//
// InitECap6Gpio - Initialize ECAP6 GPIOs
//
void InitECap6Gpio(Uint16 pin)
{
    EALLOW;
    InputXbarRegs.INPUT12SELECT = pin;         // Set eCAP6 source to GPIO-pin
    EDIS;
}

//
// InitAPwm1Gpio - Initialize EPWM1 GPIOs
//
void InitAPwm1Gpio()
{
    EALLOW;
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX0 = 3; // Select ECAP1.OUT on Mux0
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX0 = 1;  // Enable MUX0 for ECAP1.OUT
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;    // Select OUTPUTXBAR3 on GPIO5
    EDIS;
}

//
// End of file
//

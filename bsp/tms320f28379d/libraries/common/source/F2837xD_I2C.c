//###########################################################################
//
// FILE:   F2837xD_I2C.c
//
// TITLE:  F2837xD I2C Initialization & Support Functions.
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
//---------------------------------------------------------------------------
// Example: I2cAGpioConfig(), I2cBGpioConfig()
//---------------------------------------------------------------------------
// These functions configures GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

#ifdef CPU1
//
// I2cAGpioConfig - Configure I2CA GPIOs
//                  'I2caDataClkPin' should be assign with one of the
//                   possible I2C_A SDA - SDL GPIO pin Use defined Macros from
//                   "F2837xD_I2c_defines.h" for  assignment
//
void I2cAGpioConfig(Uint16 I2caDataClkPin)
{
    EALLOW;

    switch(I2caDataClkPin)
    {
        case I2C_A_GPIO0_GPIO1:

            //
            // Enable internal pull-up for the selected I2C pins
            // Enable pull-up for GPIO0 (SDAA)
            // Enable pull-up for GPIO1 (SDLA)
            //
            GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
            GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;

            //
            // Set qualification for the selected I2C pins
            // Async/no qualification (I/ps sync to SYSCLKOUT by default)
            //
            GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 3;
            GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 3;

            //
            // Configure which of the possible GPIO pins will be I2C_A pins
            // using GPIO regs
            // Configure GPIO0 for SDAA operation
            // Configure GPIO0 for SDAA operation
            //
            GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 2;

            //
            // Configure GPIO1 for SDLA operation
            // Configure GPIO1 for SDLA operation
            //
            GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 2;

            break;

        case I2C_A_GPIO32_GPIO33:
            //
            // Enable internal pull-up for the selected I2C pins
            //
            GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;
            GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;

            //
            // Set qualification for the selected I2C pins
            //
            GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;
            GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;

            //
            // Configure which of the possible GPIO pins will be I2C_A pins
            // using GPIO regs
            //
            GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;
            GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;

            break;

        case I2C_A_GPIO42_GPIO43:
            //
            // Enable internal pull-up for the selected I2C pins
            //

            //
            // Set qualification for the selected I2C pins
            //

            //
            // Configure which of the possible GPIO pins will be I2C_A pins
            // using GPIO regs
            //
            break;

        case I2C_A_GPIO91_GPIO92:
            //
            // Enable internal pull-up for the selected I2C pins
            //
            GpioCtrlRegs.GPCPUD.bit.GPIO91 = 0;
            GpioCtrlRegs.GPCPUD.bit.GPIO92 = 0;

            //
            // Set qualification for the selected I2C pins
            //
               GpioCtrlRegs.GPCQSEL2.bit.GPIO91 = 3;
               GpioCtrlRegs.GPCQSEL2.bit.GPIO92 = 3;

            //
            // Configure which of the possible GPIO pins will be I2C_A pins
            // using GPIO regs
            //
               GpioCtrlRegs.GPCGMUX2.bit.GPIO91 = 1;
            GpioCtrlRegs.GPCMUX2.bit.GPIO91 = 2;
               GpioCtrlRegs.GPCGMUX2.bit.GPIO92 = 1;
            GpioCtrlRegs.GPCMUX2.bit.GPIO92 = 2;
            break;

        case I2C_A_GPIO63104_GPIO105:
            //
            // Enable internal pull-up for the selected I2C pins
            //

            //
            // Set qualification for the selected I2C pins
            //

            //
            // Configure which of the possible GPIO pins will be I2C_A pins
            // using GPIO regs
            //
            break;

        default:

            break;

    } // End of Switch
    EDIS;
}

//
// I2cBGpioConfig - Configure I2CB GPIOs
//                  'I2cbDataClkPin' should be assign with one of the possible
//                  I2C_B SDA - SDL GPIO pin Use defined Macros from
//                  "F2837xD_I2c_defines.h" for assignment
//
void I2cBGpioConfig(Uint16 I2cbDataClkPin)
{
    EALLOW;

    switch(I2cbDataClkPin)
    {
        case I2C_B_GPIO2_GPIO3:
            //
            // Enable internal pull-up for the selected I2C pins
            // Enable pull-up for GPIO2 (SDAB)
            // Enable pull-up for GPIO3 (SDLB)
            //
            GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
            GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;

            //
            // Set qualification for the selected I2C pins
            // Async/no qualification (I/ps sync to SYSCLKOUT by default)
            //
            GpioCtrlRegs.GPAQSEL1.bit.GPIO2 = 3;
            GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;

            //
            // Configure which of the possible GPIO pins will be I2C_B pins
            // using GPIO regs
            // Configure GPIO2 for SDAB operation
            // Configure GPIO3 for SDAB operation
            // Configure GPIO1 for SDLB operation
            // Configure GPIO1 for SDLB operation
            //
            GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 2;

            GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 1;
            GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 2;

            break;

        case I2C_B_GPIO134_GPIO35:
            //
            // Enable internal pull-up for the selected I2C pins
            //

            //
            // Set qualification for the selected I2C pins
            //

            //
            // Configure which of the possible GPIO pins will be I2C_B pins
            // using GPIO regs
            //
            break;

        case I2C_B_GPIO40_GPIO41:
            //
            // Enable internal pull-up for the selected I2C pins
            //

            //
            // Set qualification for the selected I2C pins
            //

            //
            // Configure which of the possible GPIO pins will be I2C_B pins
            // using GPIO regs
            //
            break;

        case I2C_B_GPIO66_GPIO69:
            //
            // Enable internal pull-up for the selected I2C pins
            //
            GpioCtrlRegs.GPCPUD.bit.GPIO66 = 0;    //SDAB
            GpioCtrlRegs.GPCPUD.bit.GPIO69 = 0;    //SCLB

            //
            // Set qualification for the selected I2C pins
            //
            GpioCtrlRegs.GPCQSEL1.bit.GPIO66 = 3;
            GpioCtrlRegs.GPCQSEL1.bit.GPIO69 = 3;

            //
            // Configure which of the possible GPIO pins will be I2C_B pins
            // using GPIO regs
            //
            GpioCtrlRegs.GPCGMUX1.bit.GPIO66 = 1;    //0x6
            GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 2;

            GpioCtrlRegs.GPCGMUX1.bit.GPIO69 = 1;    //0x6
            GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 2;
            break;

        default:
            break;

    }
    EDIS;
}

#endif


//
// End of file
//

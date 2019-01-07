//###########################################################################
//
// FILE:   usb_hal.c
//
// TITLE:  Wrapper for interrupt functions and USB support pins.
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

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_usb.h"
#include "usb_hal.h"
#include "usb.h"
#include "include/usblib.h"
#include "include/usblibpriv.h"
#include "include/device/usbdevice.h"
#include "include/host/usbhost.h"
#include "include/host/usbhostpriv.h"
#include "include/usblibpriv.h"

//*****************************************************************************
//
//! \addtogroup c2000_specific
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Enables USB related GPIOs to perform their USB function.
//
//*****************************************************************************
void USBGPIOEnable(void)
{
    EALLOW;
    GpioCtrlRegs.GPBLOCK.all = 0x00000000;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO42 = 1;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO43 = 1;

    //VBUS
    GpioCtrlRegs.GPBDIR.bit.GPIO46 = 0;
    //ID
    GpioCtrlRegs.GPBDIR.bit.GPIO47 = 0;

    GpioCtrlRegs.GPDGMUX2.bit.GPIO120 = 3;
    GpioCtrlRegs.GPDMUX2.bit.GPIO120 = 3;
    GpioCtrlRegs.GPDGMUX2.bit.GPIO121 = 3;
    GpioCtrlRegs.GPDMUX2.bit.GPIO121 = 3;
    EDIS;
}

//*****************************************************************************
//
//! Disables USB related GPIOs from performing their USB function.
//
//*****************************************************************************
void USBGPIODisable(void)
{
    EALLOW;
    GpioCtrlRegs.GPBLOCK.all = 0x00000000;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO42 = 0;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO43 = 0;

    GpioCtrlRegs.GPDGMUX2.bit.GPIO120 = 0;
    GpioCtrlRegs.GPDMUX2.bit.GPIO120 = 0;
    GpioCtrlRegs.GPDGMUX2.bit.GPIO121 = 0;
    GpioCtrlRegs.GPDMUX2.bit.GPIO121 = 0;
    EDIS;
}


//*****************************************************************************
//
//! Wrapper function to implement mS based delay for USB functions
//
//*****************************************************************************
void USBDelay(uint32_t ui32Delay)
{
    DELAY_US(ui32Delay*1000);
}

//*****************************************************************************
//
//! Device interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//*****************************************************************************

__interrupt void
f28x_USB0DeviceIntHandler(void)
{
    USB0DeviceIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x0100;
}
//*****************************************************************************
//
//! Host interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//*****************************************************************************
__interrupt void
f28x_USB0HostIntHandler(void)
{
    USB0HostIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x0100;
}

//*****************************************************************************
//
//! Dual mode interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//*****************************************************************************
__interrupt void
f28x_USB0DualModeIntHandler(void)
{
    USB0DualModeIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x0100;
}

//*****************************************************************************
//
// Close the c2000_specific Doxygen group.
//! @}
//
//*****************************************************************************


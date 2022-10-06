/** ============================================================================
 *   \file  hw_usbphyGS70.h
 *
 *   \brief This file contains the bit field values to use with the USB phy register
 *
 *  ============================================================================
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __HW_USBPHY_GS70_H__
#define __HW_USBPHY_GS70_H__

#if defined(c6a811x)
#include "hw_control_C6A811x.h"
#endif

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

/******************************************************************************
**                      PHY REGISTER ADDRESS
*******************************************************************************/
#if defined(am335x)
#define CFGCHIP2_USBPHYCTRL     (0x44E10620)
#define CFGCHIP2_USB1PHYCTRL    (0x44E10628)
#elif defined(c6a811x)
#define CFGCHIP2_USBPHYCTRL     (SOC_CONTROL_REGS + CONTROL_USB_CTRL(0))
#define CFGCHIP2_USB1PHYCTRL    (SOC_CONTROL_REGS + CONTROL_USB_CTRL(1))
#endif


/******************************************************************************
**                      BIT FIELDS TO USE WITH PHY REGISTER
*******************************************************************************/
#define    USBPHY_CM_PWRDN              (1 << 0)
#define    USBPHY_OTG_PWRDN             (1 << 1)
#define    USBPHY_OTGVDET_EN            (1 << 19)
#define    USBPHY_OTGSESSEND_EN         (1 << 20)

void UsbPhyOn(unsigned int ulIndex);
void UsbPhyOff(unsigned int ulIndex);

#ifdef __cplusplus
}
#endif

#endif // __HW_USBPHY_GS70_H__

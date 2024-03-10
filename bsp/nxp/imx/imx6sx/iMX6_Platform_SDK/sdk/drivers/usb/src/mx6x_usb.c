/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file mx6x_usb.c
 * @brief i.MX6x specific USB routines.
 *
 * The functions in this file are implementation specific routines, like USB transceiver, PLL, clocks etc.\n
 * Each supported i.MX device has a dedicated set of routines.\n
 * The routines are referenced in the usb_module structure.
 * 
 * @ingroup diag_usb
 */

#include "sdk.h"
#include "registers/regsccm.h"
#include "registers/regsccmanalog.h"
#include "registers/regsusbphy.h"
#include "usb/usb.h"

/*!
 * This function enables the clocks needed for USB operation.
 * @param port
 * @return
 */
int usbEnableClocks(usb_module_t * port)
{
    /*!
     * Enable the USB clock for the controller
     */

    HW_CCM_CCGR6.B.CG0 = 3;

    /*!
     * Enable the PLL\n
     * OTG, Host2 and Host3 controllers use USB_PLL0
     * Host1 controller uses USB_PLL1
     */

    switch (port->controllerID) {
    case OTG:                  // OTG, Host2 and Host3 use the same PLL
    case Host2:
    case Host3:
    case OTG1:		// MX6SL first OTG controller.
	HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_POWER);	//! - Turn PLL power on.
	HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_EN_USB_CLKS); //!Powers the 9-phase PLL outputs for USBPHY0
        while(!(HW_CCM_ANALOG_PLL_USB1_RD() & BM_CCM_ANALOG_PLL_USB1_LOCK));//! - Wait for PLL to lock
	HW_CCM_ANALOG_PLL_USB1_CLR(BM_CCM_ANALOG_PLL_USB1_BYPASS);	//! - Clear bypass
	HW_CCM_ANALOG_PLL_USB1_SET(BM_CCM_ANALOG_PLL_USB1_ENABLE); 	//! - Enable PLL clock output for the PHY
        break;
    case Host1:
    case OTG2:
	HW_CCM_ANALOG_PLL_USB2_SET(BM_CCM_ANALOG_PLL_USB2_POWER);
	HW_CCM_ANALOG_PLL_USB2_SET(BM_CCM_ANALOG_PLL_USB2_EN_USB_CLKS);
        while(!(HW_CCM_ANALOG_PLL_USB2_RD() & BM_CCM_ANALOG_PLL_USB2_LOCK));
	HW_CCM_ANALOG_PLL_USB2_CLR(BM_CCM_ANALOG_PLL_USB2_BYPASS);
	HW_CCM_ANALOG_PLL_USB2_SET(BM_CCM_ANALOG_PLL_USB2_ENABLE);
        break;
    default:
        return (-1);
    }

    return (0);
}

/*!
 * Enable USB transceiver\n
 * This function enables the USB transceiver for the selected USB port.
 *
 * @param port      USB module to initialize
 */
int usbEnableTransceiver(usb_module_t * port)
{
    uint32_t instance;

    switch (port->controllerID) {
    case OTG:
    case OTG1:	
	instance = HW_USBPHY1;;
        break;
    case Host1:
    case OTG2:	
	instance = HW_USBPHY2;
        break;
    default:
        return -1;
    }
    //! NOTE !! CLKGATE must be cleared before clearing power down
    HW_USBPHY_CTRL_CLR(instance, BM_USBPHY_CTRL_SFTRST);	//! - clear SFTRST
    HW_USBPHY_CTRL_CLR(instance, BM_USBPHY_CTRL_CLKGATE);	//! - clear CLKGATE
    HW_USBPHY_PWD_WR(instance, 0);	//! - clear all power down bits
    HW_USBPHY_CTRL_SET(instance, BM_USBPHY_CTRL_ENUTMILEVEL2 | BM_USBPHY_CTRL_ENUTMILEVEL3 | BM_USBPHY_CTRL_ENHOSTDISCONDETECT);    

    //! disable the charger detector. This must be off during normal operation
    {
        // this register is not documented. Will be updated in the next release
        uint32_t *ChargerDetectControl;
        ChargerDetectControl = (uint32_t *) 0x020c81b0;
        *ChargerDetectControl |= 1 << 20;   // disable detector
    }

    //! Check if all power down bits are clear
    if (HW_USBPHY_PWD_RD(instance) != 0)
        return -1;              // Phy still in power-down mode. Check if all clocks are running.
    else
        return 0;
}

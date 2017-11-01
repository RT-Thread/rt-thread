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

#include "sdk.h"
#include "usb/usb.h"
#include "registers/regsiomuxc.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Enables Vbus for the given USB port.
 *
 * The procedure to enable Vbus depends on both the Chip and board hardware.
 *
 * @param port      USB module to initialize
 *
 * @todo Need to implement for MX6SL EVK.
 */
void usbEnableVbus(usb_module_t * port)
{
    switch (port->controllerID)
    {
    case OTG:
    case OTG1:		// MX6SL first OTG controller.
#if defined(BOARD_EVK)
        BW_USBNC_USB_OTG1_CTRL_PWR_POL(1);
        HW_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_WR(
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_SION_V(DISABLED) |
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_MUX_MODE_V(ALT6));
#endif

        break;
        
    case Host1:
    case OTG2:		// MX6SL second OTG controller
#if defined(BOARD_EVK)
        BW_USBNC_USB_OTG2_CTRL_PWR_POL(1);
        HW_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_WR(
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_SION_V(DISABLED) |
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_MUX_MODE_V(ALT6));
#endif

        break;
        
    case Host2:
        break;
        
    case Host3:
        // Nothing to be done here.
        break;
        
    default:
        // no such controller
        break;
    }
}

/*!
 * @brief Disables Vbus for the given USB port
 *
 * The procedure to enable Vbus depends on both the Chip and board hardware.
 *
 * @param port      USB module to initialize
 *
 * @todo Need to implement for MX6SL EVK.
 */
void usbDisableVbus(usb_module_t * port)
{
    switch (port->controllerID)
    {
    case OTG:
    case OTG1:		// MX6SL first OTG controller.
#if defined(BOARD_EVK)
        BW_USBNC_USB_OTG1_CTRL_PWR_POL(0);
        HW_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_WR(
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_SION_V(DISABLED) |
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL4_MUX_MODE_V(ALT6));
#endif
        break;
        
    case Host1:
    case OTG2:		// MX6SL first OTG controller.
#if defined(BOARD_EVK)
        BW_USBNC_USB_OTG2_CTRL_PWR_POL(0);
        HW_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_WR(
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_SION_V(DISABLED) |
                BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL5_MUX_MODE_V(ALT6));
#endif
	
	break;
    case Host2:
        break;
        
    case Host3:
        // Nothing to be done here.
        break;
        
    default:
        // no such controller
        break;
    }
}

/*!
 * USB HUB reset function
 */
void reset_usb_hub(void)
{
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////

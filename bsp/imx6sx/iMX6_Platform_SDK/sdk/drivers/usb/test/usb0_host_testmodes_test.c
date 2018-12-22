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
 * @file usb0_host_testmodes_test.c
 * @brief Enabled EHCI test modes in host contoller
 *
 * This test allows for setting the EHCI test modes in any of the host controllers,\n
 * including the OTG controllers.\n
 * Tests and Controller can be selected via a terminal connected to the serial port.
 */

#include "usb/usb.h"
#include "soc_memory_map.h"
#include "registers.h"
#include "sdk.h"
#include <stdio.h>

int get_menu_item(char *menu_table[]);


void usb0_host_testmodes_test (usb_module_t	*usbPort)
{
	uint32_t core = (uint32_t)usbPort->controllerID;

    static char *ehci_test_menu[] = {
        "normal mode",
        "Test_J",
        "Test_K",
        "Test_SE0/NAK",
        "Test_packet",
        "Suspend",
        "Resume",
        "Reset",
        "Exit EHCI test",
        ""                      /* Empty string is end of menu table */
    };

    int test_mode;

	//! Initialize the USB host controller.
	usbh_init(usbPort);

    while (1) {
        /* request test mode */
        printf("Select EHCI test mode for measurement:\n\n");
        test_mode = get_menu_item(ehci_test_menu);

        if (test_mode == 8)
            return;				// exit test

        if (test_mode < 5) {
            //! Set EHCI test mode in PORTSC register
            printf(("\nSetting test mode %s\n"), ehci_test_menu[test_mode]);
		HW_USBC_PORTSC1_WR(core, (HW_USBC_PORTSC1_RD(core) & (~BM_USBC_UH1_PORTSC1_PTC)) 
					| BF_USBC_UH1_PORTSC1_PTC(test_mode));
        } else {
            //! The following are not EHCI test modes, but useful for compliance measurements.
            switch (test_mode) {
            case 5:            //! - Suspend
		HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | BM_USBC_UH1_PORTSC1_SUSP);
                break;
            case 6:            //! - Resume
		HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | BM_USBC_UH1_PORTSC1_FPR);
                break;
            case 7:            //! - reset
		HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | BM_USBC_UH1_PORTSC1_PR);
                break;
            }
        }
    }
}



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
 * @file usb_test.c
 * @brief USB test.
 *
 * @ingroup diag_usb
 */

#include "sdk.h"
#include "usb/usb.h"
#include <stdio.h>

extern void usb0_host_test(usb_module_t *port);
extern void usb0_host_testmodes_test(usb_module_t *port);
extern void usb0_device_mouse_test(usb_module_t *port);

void usb_test(void) {
	int controller = -1, test = -1;
	usb_module_t usbModuleInfo, *usbPort;

	static char *ehci_controller_menu[] = {
#ifdef CHIP_MX6SL
			"OTG controller1",
			"OTG controller2",
#else
			"OTG controller",
			"Host1 controller",
#endif
			"Exit USB test",
			""
	};

	static char *select_test_menu[] = {
			"usb_host_test",
			"usb_host_testmode_test",
			"usb_device_mouse_test",
			"Exit to upper menu",
			"" };

	usbPort = &usbModuleInfo;

	while (1) {
		controller = get_menu_item(ehci_controller_menu);
		if(0 == controller) {
#ifdef CHIP_MX6SL
			usbPort->moduleName = "OTG controller1";
			usbPort->controllerID = OTG1;
#else
			usbPort->moduleName = "OTG controller";
			usbPort->controllerID = OTG;
#endif
			usbPort->phyType = Utmi;
		}else if(1 == controller){
#ifdef CHIP_MX6SL
			usbPort->moduleName = "OTG controller2";
			usbPort->controllerID = OTG2;
#else
			usbPort->moduleName = "Host1 controller";
			usbPort->controllerID = Host1;
#endif
			usbPort->phyType = Utmi;
		}else{
			printf("Invalid controller selection\n"); // should never get to this point
			controller = -1;
			break;
		}

		while (1) {
			test = get_menu_item(select_test_menu);
			if(0 == test) {
				printf("Running usb_host_test on %s\n", usbPort->moduleName);
				usb0_host_test(usbPort);
			}else if(1 == test){
				printf("Running usb_host_testmode_test on %s\n",
						usbPort->moduleName);
				usb0_host_testmodes_test(usbPort);
			}else if(2 == test){
#ifndef CHIP_MX6SL
				if (usbPort->controllerID == OTG) {
#else
				if ((usbPort->controllerID == OTG1) || (usbPort->controllerID == OTG2)) {
#endif
					printf("Running usb_device_mouse_test on %s\n",
							usbPort->moduleName);
					usb0_device_mouse_test(usbPort);
				} else {
					printf(
							"Invalid controller selection.\nOnly OTG controller can operate in device mode\n");
				}
			}else{
				break;
			}
		}
	}
}

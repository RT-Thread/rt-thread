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
 * @file usb0_device_mouse_test.c
 * @brief Emulate a USB mouse
 *
 * This test code demonstrates the use of control and interrupt endpoints.
 * The mouse data (X/Y movement) is transferred in an interrupt transfer
 */
#include "usb/usb.h"
#include "soc_memory_map.h"

#include <math.h>
#include <float.h>
#include <stdio.h>

// X, Y displacement info
#define MAX_DISP	300
#define DISPLACE	2

void hid_device_enum(usb_module_t *port,
		usbdEndpointPair_t *endpointListAddress,
		usbDeviceDescriptor_t *DeviceDescriptor,
		usbConfigurationDescriptor_t *ConfigDescriptor,
		uint8_t *fullConfigBuffer, uint8_t *ReportDescriptor);

//! Allocate memory for endpoint list
// Hardware supports 8 IN and 8 OUT endpoints, including Endpoint 0
// For non-control endpoints, In and OUT are completely independent.

usbdEndpointPair_t endpointList[8] __attribute__ ((aligned (4096))); // 4K aligned memory for 16 queue heads

/*!
 * @file usb0_device_mouse_test.c
 * @brief Demo code to illustrate the programming of the OTG controller in device mode
 *
 */

uint8_t qf_Descriptor[] = {
	0x0A,	//USB_DEV_QUALIFIER_DESC_LEN,
	0x06,   //USB_DEV_QUALIFIER_DESC_TYPE,
	0x00,   //USB_DEV_DESC_SPEC_LB,
	0x02,   //USB_DEV_DESC_SPEC_HB,
	0x00,   //USB_DEV_DESC_DEV_CLASS,
	0x00,   //USB_DEV_DESC_DEV_SUBCLASS,
	0x00,   //USB_DEV_DESC_DEV_PROTOCOL,
	0x40,   //USB_DEV_DESC_EP0_MAXPACKETSIZE,
	0x01,   //USB_DEV_DESC_NUM_OT_SPEED_CONF,
	0		//USB_DEV_DESC_RESERVED
};

/*!
 * Main program loop.
 */
void usb0_device_mouse_test(usb_module_t *port) 
{
	uint32_t core = (uint32_t)port->controllerID;
	usbdEndpointDtd_t *usbDtd1, *usbDtd2, *usbDtd3, *usbDtd4;
	usbdEndpointDtd_t *head; // Pointer to the head of the current dTD list
	uint32_t mouseData[8];
	usbdEndpointPair_t *endpointListAddress =
			(usbdEndpointPair_t *) &endpointList[0];

	// declarations for HID device descriptors
	usbDeviceDescriptor_t mouseDeviceDescriptor;
	usbConfigurationDescriptor_t mouseConfigDescriptor;
	usbInterfaceDescriptor_t mouseInterfaceDescriptor;
	usbEndpointDescriptor_t mouseEndpointDescriptor;
	usbHidDescriptor_t mouseHidDescriptor;

	uint8_t* mouseReportDescriptor;

	mouseReportDescriptor = (uint8_t*) malloc(MAX_USB_DESC_SIZE); // This is a variable length descriptor

	//! initialize the descriptors for our device:

	//! - Device descriptor
	mouseDeviceDescriptor.bLength = 0x12; // length of this descriptor
	mouseDeviceDescriptor.bDescriptorType = 0x01; // Device descriptor
	mouseDeviceDescriptor.bcdUSB = 0x0200; // USB version 2.0
	mouseDeviceDescriptor.bDeviceClass = 0x00; // Device class (specified in interface descriptor)
	mouseDeviceDescriptor.bDeviceSubClass = 0x00; // Device Subclass (specified in interface descriptor)
	mouseDeviceDescriptor.bDeviceProtocol = 0x00; // Device Protocol (specified in interface descriptor)
	mouseDeviceDescriptor.bMaxPacketSize = 0x40; // Max packet size for control endpoint
	mouseDeviceDescriptor.idVendor = 0x15a2; // Freescale Vendor ID. -- DO NOT USE IN A PRODUCT
	mouseDeviceDescriptor.idProduct = 0x0001; // Decvice ID -- DO NOT USE IN A PRODUCT
	mouseDeviceDescriptor.bcdDevice = 0x0000; // Device revsion
	mouseDeviceDescriptor.iManufacturer = 0x00; // Index of  Manufacturer string descriptor
	mouseDeviceDescriptor.iProduct = 0x00; // Index of Product string descriptor
	mouseDeviceDescriptor.iSerialNumber = 0x00; // Index of serial number string descriptor
	mouseDeviceDescriptor.bNumConfigurations = 0x01; // Number of configurations

	//! - Config descriptor
	mouseConfigDescriptor.bLength = 0x09; //
	mouseConfigDescriptor.bDescriptorType = 0x02; // Configuration descriptor
	mouseConfigDescriptor.wTotalLength = 0x22; // Total length of data, includes interface, HID and endpoint
	mouseConfigDescriptor.bNumInterfaces = 0x01; // Number of interfaces
	mouseConfigDescriptor.bConfigurationValue = 0x01; // Number to select for this configuration
	mouseConfigDescriptor.iConfiguration = 0x00; // No string descriptor
	mouseConfigDescriptor.bmAttributes = 0xC0; // Self powered, No remote wakeup
	mouseConfigDescriptor.MaxPower = 10; // 20 mA Vbus power

	//! - Interface descriptor
	mouseInterfaceDescriptor.bLength = 0x09;
	mouseInterfaceDescriptor.bDescriptorType = 0x04; // Interface descriptor
	mouseInterfaceDescriptor.bInterfaceNumber = 0x00; // This interface = #0
	mouseInterfaceDescriptor.bAlternateSetting = 0x00; // Alternate setting
	mouseInterfaceDescriptor.bNumEndpoints = 0x01; // Number of endpoints for this interface
	mouseInterfaceDescriptor.bInterfaceClass = 0x03; // HID class interface
	mouseInterfaceDescriptor.bInterfaceSubClass = 0x01; // Boot interface Subclass
	mouseInterfaceDescriptor.bInterfaceProtocol = 0x02; // Mouse protocol
	mouseInterfaceDescriptor.iInterface = 0; // No string descriptor

	//! - Endpoint descriptor for endpoint 1 (interrupt endpoint)
	mouseEndpointDescriptor.bLength = 0x07;
	mouseEndpointDescriptor.bDescriptorType = 0x05; // Endpoint descriptor
	mouseEndpointDescriptor.bEndpointAddress = 0x81; // Endpoint 1 IN
	mouseEndpointDescriptor.bmAttributes = 0x3; // interrupt endpoint
	mouseEndpointDescriptor.wMaxPacketSize = 0x0200; // max 6 bytes (for high_speed)
	mouseEndpointDescriptor.bInterval = 0x0A; // 10 ms interval

	//! - HID descriptor
	mouseHidDescriptor.bLength = 0x09; //
	mouseHidDescriptor.bDescriptorType = 0x21; // HID descriptor
	mouseHidDescriptor.bcdHID = 0x0101; // HID Class spec 1.01
	mouseHidDescriptor.bCountryCode = 0x00; //
	mouseHidDescriptor.bNumDescriptors = 0x01; // 1 HID class descriptor to follow (report)
	mouseHidDescriptor.bReportDescriptorType = 0x22; // Report descriptor follows
	mouseHidDescriptor.wDescriptorLength[0] = 0x34; // Length of report descriptor byte 1
	mouseHidDescriptor.wDescriptorLength[1] = 0x00; // Length of report descriptor byte 2

	// allocate a buffer for the data and copy the descriptors to the buffer

	uint8_t *mouseConfigBuffer = (uint8_t *) malloc(
			mouseConfigDescriptor.wTotalLength);
	uint8_t *bufferPointer = mouseConfigBuffer;

	memcpy(bufferPointer, &mouseConfigDescriptor,
			mouseConfigDescriptor.bLength); // copy Configuration descriptor
	bufferPointer += mouseConfigDescriptor.bLength;

	memcpy(bufferPointer, &mouseInterfaceDescriptor,
			mouseInterfaceDescriptor.bLength); // copy Interface descriptor
	bufferPointer += mouseInterfaceDescriptor.bLength;

	memcpy(bufferPointer, &mouseHidDescriptor, mouseHidDescriptor.bLength); // copy HID descriptor
	bufferPointer += mouseHidDescriptor.bLength;

	memcpy(bufferPointer, &mouseEndpointDescriptor,
			mouseEndpointDescriptor.bLength); // copy Endpoint descriptor

	//! Initialize the report descriptor
	mouseReportDescriptor[0] = 0x05;
	mouseReportDescriptor[1] = 0x01;
	mouseReportDescriptor[2] = 0x09;
	mouseReportDescriptor[3] = 0x02;
	mouseReportDescriptor[4] = 0xA1;
	mouseReportDescriptor[5] = 0x01;
	mouseReportDescriptor[6] = 0x09;
	mouseReportDescriptor[7] = 0x01;
	mouseReportDescriptor[8] = 0xA1;
	mouseReportDescriptor[9] = 0x00;
	mouseReportDescriptor[10] = 0x05;
	mouseReportDescriptor[11] = 0x09;
	mouseReportDescriptor[12] = 0x19;
	mouseReportDescriptor[13] = 0x01;
	mouseReportDescriptor[14] = 0x29;
	mouseReportDescriptor[15] = 0x05;
	mouseReportDescriptor[16] = 0x15;
	mouseReportDescriptor[17] = 0x00;
	mouseReportDescriptor[18] = 0x25;
	mouseReportDescriptor[19] = 0x01;
	mouseReportDescriptor[20] = 0x95;
	mouseReportDescriptor[21] = 0x05;
	mouseReportDescriptor[22] = 0x75;
	mouseReportDescriptor[23] = 0x01;
	mouseReportDescriptor[24] = 0x81;
	mouseReportDescriptor[25] = 0x02;
	mouseReportDescriptor[26] = 0x95;
	mouseReportDescriptor[27] = 0x01;
	mouseReportDescriptor[28] = 0x75;
	mouseReportDescriptor[29] = 0x03;
	mouseReportDescriptor[30] = 0x81;
	mouseReportDescriptor[31] = 0x01;
	mouseReportDescriptor[32] = 0x05;
	mouseReportDescriptor[33] = 0x01;
	mouseReportDescriptor[34] = 0x09;
	mouseReportDescriptor[35] = 0x30;
	mouseReportDescriptor[36] = 0x09;
	mouseReportDescriptor[37] = 0x31;
	mouseReportDescriptor[38] = 0x09;
	mouseReportDescriptor[39] = 0x38;
	mouseReportDescriptor[40] = 0x15;
	mouseReportDescriptor[41] = 0x81;
	mouseReportDescriptor[42] = 0x25;
	mouseReportDescriptor[43] = 0x7F;
	mouseReportDescriptor[44] = 0x75;
	mouseReportDescriptor[45] = 0x08;
	mouseReportDescriptor[46] = 0x95;
	mouseReportDescriptor[47] = 0x03;
	mouseReportDescriptor[48] = 0x81;
	mouseReportDescriptor[49] = 0x06;
	mouseReportDescriptor[50] = 0xC0;
	mouseReportDescriptor[51] = 0xC0;

	//! Setup and start the controller.
	//! Perform basic device initialization including setting up EP0.
	usbd_device_init(port, endpointListAddress);

	//! Perform enumeration.
	hid_device_enum(port, endpointListAddress, &mouseDeviceDescriptor,
			&mouseConfigDescriptor, mouseConfigBuffer, mouseReportDescriptor);

	//! Setup our interrupt endpoint.
	//! - Enable endpoint 1 for status polling
	HW_USBC_ENDPTCTRL1_WR(core, USB_ENDPTCTRL_TXE
                        | USB_ENDPTCTRL_TXT_INT | USB_ENDPTCTRL_RXT_BULK);

	//! - Initialize IN endpoint queue head for endpoint 1
	usbdEndpointInfo_t endpoint1Info;
	endpoint1Info.endpointNumber = 1;
	endpoint1Info.endpointDirection = IN;
	endpoint1Info.interruptOnSetup = FALSE;
	endpoint1Info.maxPacketLength = usb_get_port_speed(port) == usbSpeedFull ? 64 : 512;
	endpoint1Info.mult = 0;

	//! - Initialize the queue head
	//  Invalidate Next_dtd pointer for now.
	usbd_endpoint_qh_init(endpointListAddress, &endpoint1Info, 0xDEAD0001);

	/*!
	 *  - Initialize dTDs for sending mouse data.
	 *
	 *  We  calculate four mouse positions at a time
	 *  Each position takes 1 transfer descriptor that transfers 4 bytes (1 position)
	 *  so there are four corresponding dTDs. We link the dTDs via the nextDtd pointer
	 *  so the controller can respond to 4 requests without CPU intervention.
	 *  The last dTD has it's "Interrupt_On_Completion" bit set so we get an interrupt when the last dTD is consumed.
	 */
	//! - Create the transfer descriptors
	usbDtd1 = usbd_dtd_init(0x4, 0, 0, &mouseData[0]);
	usbDtd2 = usbd_dtd_init(0x4, 0, 0, &mouseData[1]);
	usbDtd3 = usbd_dtd_init(0x4, 0, 0, &mouseData[2]);
	usbDtd4 = usbd_dtd_init(0x4, 1, 0, &mouseData[3]); // Note: we set IOC on this dTD to get an interrupt when completed

	//! - Link the transfer descriptors
	//! The controller will automatically move to the next dTD when one completes
	usbDtd1->nextDtd = (uint32_t) usbDtd2;
	usbDtd2->nextDtd = (uint32_t) usbDtd3;
	usbDtd3->nextDtd = (uint32_t) usbDtd4;

	head = usbDtd1; // first transfer descriptor on the endpoint

	//! Send the data:
	uint32_t i;
	for (i = 0; i < 4; i++){
		fillBuffer(&mouseData[i]); //! Calculate mouse data and put in data buffers
	}

	//! - Add the transfer descriptors to the queue head
	endpointList[1].in.nextDtd = (uint32_t) usbDtd1;

	//! - Prime the endpoint.
	//! -- The controller is now ready to respond to an IN request from the host.
	HW_USBC_ENDPTPRIME_WR(core, HW_USBC_ENDPTPRIME_RD(core) | USB_ENDPTPRIME_PETB(2));

	/*!
	 * We now have 4 descriptors on the list. The host will poll the endpoint every 10 ms
	 * so in 40 ms, these descriptors will all be used.
	 */

	//! Continuously loop, adding 4 new descriptors to the list and wait for completion of the previous

	printf("You should see the mouse cursor moving in a cricle, press 'x' to exit.\n");

	i = 4;						// index for data buffer. we constantly re-use the buffers to keep it simple
	usbdEndpointDtd_t *usbDtdTop;		// First dTD of the list of 4 to be added
	usbdEndpointDtd_t *usbDtdPointer;	//
	while (1){
		if (getchar() == 'x') {
			printf("USB device test exits.\n");
    			//! Stop controller
   			HW_USBC_USBCMD_WR(core, HW_USBC_USBCMD_RD(core) & (!BM_USBC_UH1_USBCMD_RS));

			return ;
		}

		i = i % 8;					// Modulo 8 to loop through our 8 buffers

		// Create first descriptor
		usbDtdTop = usbd_dtd_init(0x4, 0, 0, &mouseData[i]);	// create transfer descriptor
		// fill data buffer
		fillBuffer(&mouseData[i++]);

		// Create and link next 3 descriptors
		usbDtdPointer = usbDtdTop;

		usbDtdPointer->nextDtd = (uint32_t)usbd_dtd_init(0x4, 0, 0, &mouseData[i]);
		usbDtdPointer = (usbdEndpointDtd_t *)usbDtdPointer->nextDtd;
		fillBuffer(&mouseData[i++]);

		usbDtdPointer->nextDtd = (uint32_t)usbd_dtd_init(0x4, 0, 0, &mouseData[i]);
		usbDtdPointer = (usbdEndpointDtd_t *)usbDtdPointer->nextDtd;
		fillBuffer(&mouseData[i++]);

		usbDtdPointer->nextDtd = (uint32_t)usbd_dtd_init(0x4, 1, 0, &mouseData[i]);  // IOC bit set on 4th descriptor
		usbDtdPointer = (usbdEndpointDtd_t *)usbDtdPointer->nextDtd;
		fillBuffer(&mouseData[i++]);

		usbd_add_dtd(port, endpointListAddress, &endpoint1Info, usbDtdTop); // Add the dTD's to the endpoint

		//! wait for previous dTDs to complete
		while(!(HW_USBC_USBSTS_RD(core) & BM_USBC_UH1_USBSTS_UI));
		//! Clear Interrupt bit
		HW_USBC_USBSTS_WR(core, HW_USBC_USBSTS_RD(core) | BM_USBC_UH1_USBSTS_UI);

		//! reclaim used descriptors
		head = usbd_reclaim_dtd(port, endpointListAddress, &endpoint1Info, head);
	}
}


/*!
 * Enumerate device
 *
 * @brief This function processes the setup transfers for the enumeration of the device
 *
 * @param	port				The USB controller to use
 * @param	endpointListAddress	The address of the endpoint list
 * @param	deviceDescriptor	Device descriptor to send
 * @param	configDescriptor	Configuration descriptor of the device
 * @param	fullConfigBuffer	Configuration descriptor of the device, including Interface, Hid and Endpoint descriptors
 * @param	reportDescriptor	Report descriptor of the HID device
 *
 */
void hid_device_enum(usb_module_t *port,
		usbdEndpointPair_t *endpointListAddress,
		usbDeviceDescriptor_t *deviceDescriptor,
		usbConfigurationDescriptor_t *configDescriptor,
		uint8_t *fullConfigBuffer, uint8_t *reportDescriptor)
{
	uint32_t core = (uint32_t)port->controllerID;
	uint32_t request;
	uint32_t transferSize;
	uint32_t deviceAddress;
	uint32_t testMode;

	printf("\nWaiting for reset to start enumeration.\n");
	//! Wait for bus reset
        while(!(HW_USBC_USBSTS_RD(core) & BM_USBC_UH1_USBSTS_URI));

	//! Handle USB bus reset
	usbd_bus_reset(port);

	/* Allocate space to store the setup packet information. */
	usbdSetupPacket_t setupPacket;

	//! Process all control transfers for enumeration.
	int done = 0;
	while (!done) {
		//! Get SETUP packet
		usbd_get_setup_packet(port, endpointListAddress, &setupPacket);
		request = setupPacket.bRequestType << 8 | setupPacket.bRequest;

		switch (request) {
		case GET_DESCRIPTOR:
			if (setupPacket.wValue == 0x100) { //! - send device descriptor.
				// Send partial descriptor when less bytes than full descriptor are requested.
				transferSize =
						setupPacket.wLength > 0x12 ? 0x12 : setupPacket.wLength;
				usbd_device_send_control_packet(port, endpointListAddress,
						(uint8_t *) deviceDescriptor, transferSize);
			} else if (setupPacket.wValue == 0x0200) { //! - send configuration descriptor.
				// Send partial descriptor if less bytes than the descriptor size are requested
				transferSize =
						setupPacket.wLength > configDescriptor->wTotalLength ?
								configDescriptor->wTotalLength :
								setupPacket.wLength;
				usbd_device_send_control_packet(port, endpointListAddress,
						fullConfigBuffer, transferSize);
			}else if (setupPacket.wValue == 0x0600) {	// send qualifier descriptor
				 transferSize = setupPacket.wLength > sizeof(qf_Descriptor)?
					sizeof(qf_Descriptor): setupPacket.wLength;
				usbd_device_send_control_packet(port, endpointListAddress,
						qf_Descriptor,
						 transferSize
						);
			}
			else {
				// Stall the endpoint
				HW_USBC_ENDPTCTRL0_WR(core, HW_USBC_ENDPTCTRL0_RD(core) | USB_ENDPTCTRL_TXS);
				printf("Unsupported descriptor request received\n");
				printf("wValue: 0x%x\n",setupPacket.wValue);
				printf("length: 0x%x\n",setupPacket.wLength);
			}
			break;

		case SET_CONFIGURATION:
			/*
			 * For a USB mouse there is only one configuration, so this function
			 * doesn't do anything with the configuration values sent by the host.
			 * Just Acknowledge the request.
			 */
			usbd_device_send_zero_len_packet(port, endpointListAddress, 0);
			break;

		case SET_IDLE:
			/*
			 * HID class request
			 */
			usbd_device_send_zero_len_packet(port, endpointListAddress, 0);
			break;

		case GET_HID_CLASS_DESCRIPTOR:
			if (setupPacket.wValue == 0x2200) { //! - Send report descriptor.
				transferSize =
						setupPacket.wLength > 52 ? 52 : setupPacket.wLength;
				usbd_device_send_control_packet(port, endpointListAddress,
						(uint8_t *) reportDescriptor, transferSize);

				/*
				 * The report descriptor should always be the last thing sent, so
				 * at this point we are done with the enumeration.
				 */
				done = 1;
			}
			break;
		case SET_FEATURE:
			if (setupPacket.wValue == 0x0002) { //! process set test mode
				// This supports the USBHSET tool to set the controller in test mode
				usbd_device_send_zero_len_packet(port, endpointListAddress, 0);

				// - Set the requested test mode in PORTSC and wait for power cycle
				testMode = setupPacket.wIndex & 0xFF00 << 8;
				HW_USBC_PORTSC1_WR(core, HW_USBC_PORTSC1_RD(core) | testMode); 

				printf("Port set to test mode %d\n", setupPacket.wIndex >> 8);
				while (1)
					; // - Wait here for power cycle / board reset
			}
			break;

		default:
			//! perform set address handling

			// Check if command is a SET ADDRESS
			if (setupPacket.bRequestType == 0x00
					&& setupPacket.bRequest == 0x05) {
				deviceAddress = (setupPacket.wValue) << 25;
				deviceAddress |= 1 << 24; //! - Set ADRA bit to stage the new address

				//! - Set the new device address;
				//! -- the new address will become effective after an IN transaction is acknowledged
 				HW_USBC_DEVICEADDR_WR(core, deviceAddress);

				//! - Send zero-length packet to acknowledge.
				usbd_device_send_zero_len_packet(port, endpointListAddress, 0);

				break;
			} else
				printf("ERR!!! Unsupported command.\n\n");
			break;

		} /* end switch */
	} /* end while */

	return;
}

void fillBuffer(uint32_t *buffer) {

	static int init=1;
	static float angle, angle_disp;
	const float PI = 3.1415926535897932384626433832795f;

	static int x, x_1;
	static int y, y_1;
	char x_disp, y_disp;

	if(init == 1){					// if this is the first time we call this routine
		angle = 0;
		x_1 = x = MAX_DISP / 2;
		y_1 = y = 0;
		angle_disp = PI / 180;
		init = 0;
	}

	//! - Put the data in the transfer descriptor buffers
	// Calculate pointer positions to make the cursor move in a circle
	//! Calculate the  mouse displacement values to fill the buffer
	x = (int) (cosf(angle) * MAX_DISP / 2);
	y = (int) (sinf(angle) * MAX_DISP / 2);

	x_disp = x - x_1;
	y_disp = y - y_1;

	x_1 = x;
	y_1 = y;

	angle = angle + angle_disp;
	if (angle > 2 * PI) {
		angle -= 2 * PI;
	}

	//! Put the data in the buffer
	*buffer = (0 | ((x_disp & 0xFF) << 16) | ((y_disp & 0xFF) << 8));
}
/********************************************************************/

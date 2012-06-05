/*
 * File      : core.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#ifndef __USB_SPEC_H__
#define __USB_SPEC_H__

#include <rtthread.h>

struct usb_descriptor
{
	rt_uint8_t bLength;
	rt_uint8_t type;
};
typedef struct usb_descriptor* udesc_t;

struct udevice_descriptor 
{
	rt_uint8_t bLength;
	rt_uint8_t type;
	rt_uint16_t bcdUSB;
	rt_uint8_t bDeviceClass;
	rt_uint8_t bDeviceSubClass;
	rt_uint8_t bDeviceProtocol;
	rt_uint8_t bMaxPacketSize0;
	rt_uint16_t idVendor;
	rt_uint16_t idProduct;
	rt_uint16_t bcdDevice;
	rt_uint8_t iManufacturer;
	rt_uint8_t iProduct;
	rt_uint8_t iSerialNumber;
	rt_uint8_t bNumConfigurations;
};
typedef struct udevice_descriptor* udev_desc_t;

struct uconfig_descriptor 
{
	rt_uint8_t bLength;
	rt_uint8_t type;
	rt_uint16_t wTotalLength;
	rt_uint8_t bNumInterfaces;
	rt_uint8_t bConfigurationValue;
	rt_uint8_t iConfiguration;
	rt_uint8_t bmAttributes;
	rt_uint8_t MaxPower;
};
typedef struct uconfig_descriptor* ucfg_desc_t;

struct uinterface_descriptor 
{
	rt_uint8_t bLength;
	rt_uint8_t type;
	rt_uint8_t bInterfaceNumber;
	rt_uint8_t bAlternateSetting;
	rt_uint8_t bNumEndpoints;
	rt_uint8_t bInterfaceClass;
	rt_uint8_t bInterfaceSubClass;
	rt_uint8_t bInterfaceProtocol;
	rt_uint8_t iInterface;
};
typedef struct uinterface_descriptor* uintf_desc_t;

struct uendpoint_descriptor 
{
	rt_uint8_t bLength;
	rt_uint8_t type;
	rt_uint8_t bEndpointAddress;
	rt_uint8_t bmAttributes;
	rt_uint16_t wMaxPacketSize;
	rt_uint8_t bInterval;
};
typedef struct uendpoint_descriptor* uep_desc_t;

struct ustring_descriptor 
{
	rt_uint8_t bLength;
	rt_uint8_t type;
	rt_uint8_t* String;
};
typedef struct ustring_descriptor* ustr_desc_t;

struct uhub_descriptor 
{
	rt_uint8_t length;
	rt_uint8_t type;
	rt_uint8_t num_ports;
	rt_uint16_t characteristics;	
	rt_uint8_t pwron_to_good;		/* power on to power good */
	rt_uint8_t current;	
	rt_uint8_t removable[8];
	rt_uint8_t pwr_ctl[8];
};
typedef struct uhub_descriptor* uhub_desc_t;

struct ureqest
{
	rt_uint8_t request_type;
	rt_uint8_t request;
	rt_uint16_t value;
	rt_uint16_t index;	
	rt_uint16_t length;
};
typedef struct ureqest* ureq_t;

#define uswap_32(x) \
	((((x) & 0xff000000) >> 24) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x000000ff) << 24))

#define USB_CLASS_DEVICE  				0x00
#define USB_CLASS_AUDIO					0x01
#define USB_CLASS_CDC  					0x02
#define USB_CLASS_HID 		 			0x03
#define USB_CLASS_PHYSICAL				0x05
#define USB_CLASS_IMAGE					0x06
#define USB_CLASS_PRINTER 				0x07
#define USB_CLASS_MASS_STORAGE  		0x08
#define USB_CLASS_HUB  					0x09
#define USB_CLASS_CDC_DATA				0x0a
#define USB_CLASS_SMART_CARD 			0x0b
#define USB_CLASS_SECURITY				0x0d
#define USB_CLASS_VIDEO					0x0e
#define USB_CLASS_HEALTHCARE 			0x0f
#define USB_CLASS_DIAG_DEVICE			0xdc
#define USB_CLASS_WIRELESS				0xe0
#define USB_CLASS_MISC 					0xef
#define USB_CLASS_APP_SPECIFIC  		0xfe
#define USB_CLASS_VEND_SPECIFIC 		0xff

#define USB_DESC_TYPE_DEVICE			0x01
#define USB_DESC_TYPE_CONFIGURATION		0x02
#define USB_DESC_TYPE_STRING			0x03
#define USB_DESC_TYPE_INTERFACE			0x04
#define USB_DESC_TYPE_ENDPOINT			0x05
#define USB_DESC_TYPE_DEVICEQUALIFIER	0x06
#define USB_DESC_TYPE_OTHERSPEED		0x07
#define USB_DESC_TYPE_HID 				0x21
#define USB_DESC_TYPE_REPORT 			0x22
#define USB_DESC_TYPE_PHYSICAL  		0x23
#define USB_DESC_TYPE_HUB  				0x29

#define USB_REQ_TYPE_STANDARD			0x00
#define USB_REQ_TYPE_CLASS				0x20
#define USB_REQ_TYPE_VENDOR  			0x40
#define USB_REQ_TYPE_TYPE_MASK			0x60

#define USB_REQ_TYPE_DIR_OUT			0x00
#define USB_REQ_TYPE_DIR_IN				0x80

#define USB_REQ_TYPE_DEVICE  			0x00
#define USB_REQ_TYPE_INTERFACE  		0x01
#define USB_REQ_TYPE_ENDPOINT			0x02
#define USB_REQ_TYPE_OTHER				0x03
#define USB_REQ_TYPE_RECIPIENT_MASK		0x1f

#define USB_FEATURE_ENDPOINT_HALT		0x00
#define USB_FEATURE_DEV_REMOTE_WAKEUP	0x01
#define USB_FEATURE_TEST_MODE			0x02

#define USB_REQ_GET_STATUS				0x00
#define USB_REQ_CLEAR_FEATURE			0x01
#define USB_REQ_SET_FEATURE				0x03
#define USB_REQ_SET_ADDRESS				0x05
#define USB_REQ_GET_DESCRIPTOR			0x06
#define USB_REQ_SET_DESCRIPTOR			0x07
#define USB_REQ_GET_CONFIGURATION		0x08
#define USB_REQ_SET_CONFIGURATION		0x09
#define USB_REQ_GET_INTERFACE			0x0A
#define USB_REQ_SET_INTERFACE			0x0B
#define USB_REQ_SYNCH_FRAME				0x0C
#define USB_REQ_SET_ENCRYPTION			0x0D
#define USB_REQ_GET_ENCRYPTION			0x0E
#define USB_REQ_RPIPE_ABORT				0x0E
#define USB_REQ_SET_HANDSHAKE			0x0F
#define USB_REQ_RPIPE_RESET				0x0F
#define USB_REQ_GET_HANDSHAKE			0x10
#define USB_REQ_SET_CONNECTION			0x11
#define USB_REQ_SET_SECURITY_DATA		0x12
#define USB_REQ_GET_SECURITY_DATA		0x13
#define USB_REQ_SET_WUSB_DATA			0x14
#define USB_REQ_LOOPBACK_DATA_WRITE		0x15
#define USB_REQ_LOOPBACK_DATA_READ		0x16
#define USB_REQ_SET_INTERFACE_DS		0x17

#define USB_PID_OUT  					0x01
#define USB_PID_ACK  					0x02
#define USB_PID_DATA0					0x03
#define USB_PID_SOF  					0x05
#define USB_PID_IN						0x09
#define USB_PID_NACK 					0x0A
#define USB_PID_DATA1					0x0B
#define USB_PID_PRE  					0x0C
#define USB_PID_SETUP					0x0D
#define USB_PID_STALL					0x0E

#define USB_EP_DESC_OUT					0x00
#define USB_EP_DESC_IN					0x80
#define USB_EP_DESC_NUM_MASK			0x0f

#define USB_EP_ATTR_CONTROL				0x00
#define USB_EP_ATTR_ISOC				0x01
#define USB_EP_ATTR_BULK				0x02
#define USB_EP_ATTR_INT					0x03
#define USB_EP_ATTR_TYPE_MASK			0x03

#define USB_EPNO_MASK 					0x7f
#define USB_DIR_OUT 					0x00
#define USB_DIR_IN 						0x80
#define USB_DIR_MASK  					0x80

#define USB_EP_ATTR(attr) 				(attr & USB_EP_ATTR_TYPE_MASK)
#define USB_EP_DESC_NUM(addr)			(addr & USB_EP_DESC_NUM_MASK)

#endif

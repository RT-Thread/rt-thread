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

#ifndef __CORE_H__
#define __CORE_H__

#include <rtthread.h>
#include "usbspec.h"
#include "usbhost.h"

#define USB_MAX_DEVICE			32
#define USB_MAX_INTERFACE		8
#define PORT_NUM				4

#define SIZEOF_USB_REQUEST		8

struct uhcd;
struct uifinst;
struct uhubinst;
typedef void (*func_callback)(void *context);

enum umsg_type
{
	USB_MSG_CONNECT_CHANGE,
	USB_MSG_CALLBACK,
};
typedef enum umsg_type umsg_type;

#define UINST_STATUS_IDLE		0
#define UINST_STATUS_BUSY		1
#define UINST_STATUS_ERROR		2

struct uinstance
{
	struct udevice_descriptor dev_desc;
	ucfg_desc_t cfg_desc;
	struct uhcd *hcd;

	rt_uint8_t status;
	rt_uint8_t type;
	rt_uint8_t index;
	rt_uint8_t address;	
	rt_uint8_t speed;
	rt_uint8_t max_packet_size;	
	rt_uint8_t port;

	struct uhubinst* parent;
	struct uifinst* ifinst[USB_MAX_INTERFACE];		
};
typedef struct uinstance* uinst_t;

struct uifinst
{
	uinst_t uinst;
	uintf_desc_t intf_desc;

	ucd_t drv;
	void *user_data;
};
typedef struct uifinst* uifinst_t;

#define UPIPE_STATUS_OK			0
#define UPIPE_STATUS_STALL		1
#define UPIPE_STATUS_ERROR		2

struct upipe
{
	rt_uint32_t status;
	struct uendpoint_descriptor ep;
	uifinst_t ifinst;
	func_callback callback;
	void* user_data;
};
typedef struct upipe* upipe_t;

struct umsg
{
	umsg_type type; 
	union
	{
		struct uhubinst* uhub;
		struct 
		{
			func_callback function;
			void *context;
		}cb;
	}content;
};
typedef struct umsg* umsg_t;

uinst_t rt_usb_alloc_instance(void);
rt_err_t rt_usb_attatch_instance(uinst_t uinst);
rt_err_t rt_usb_detach_instance(uinst_t uinst);
rt_err_t rt_usb_get_descriptor(uinst_t uinst, rt_uint8_t type, void* buffer, 
	int nbytes);
rt_err_t rt_usb_set_configure(uinst_t uinst, int config);
rt_err_t rt_usb_set_address(uinst_t uinst);
rt_err_t rt_usb_set_interface(uinst_t uinst, int intf);
rt_err_t rt_usb_clear_feature(uinst_t uinst, int endpoint, int feature);
rt_err_t rt_usb_get_interface_descriptor(ucfg_desc_t cfg_desc, int num, 
	uintf_desc_t* intf_desc);
rt_err_t rt_usb_get_endpoint_descriptor(uintf_desc_t intf_desc, int num, 
	uep_desc_t* ep_desc);

#endif

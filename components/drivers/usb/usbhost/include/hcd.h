/*
 * File      : hcd.h
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

#ifndef __HCD_H__
#define __HCD_H__

#include <rtthread.h>
#include "usbspec.h"

struct uhcd_ops
{
	int (*ctl_xfer)(uinst_t inst, ureq_t setup, void* buffer, int nbytes, 
		int timeout);
	int (*bulk_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
	int (*int_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
	int (*iso_xfer)(upipe_t pipe, void* buffer, int nbytes, int timeout);
	
	rt_err_t (*alloc_pipe)(struct upipe** pipe, uifinst_t ifinst, uep_desc_t ep, 
		func_callback callback);
	rt_err_t (*free_pipe)(upipe_t pipe);	
	rt_err_t (*hub_ctrl)(rt_uint16_t port, rt_uint8_t cmd, void *args);	
};

struct uhcd
{
	struct rt_device parent;

	struct uhcd_ops* ops;
};
typedef struct uhcd* uhcd_t;

rt_inline rt_err_t rt_usb_hcd_alloc_pipe(uhcd_t hcd, upipe_t* pipe, 
	uifinst_t ifinst, uep_desc_t ep, func_callback callback)
{
	if(ifinst == RT_NULL) return -RT_EIO;

	/* parameter check */
	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);	
	RT_ASSERT(hcd->ops->alloc_pipe!= RT_NULL);

	return hcd->ops->alloc_pipe(pipe, ifinst, ep, callback);
}

rt_inline rt_err_t rt_usb_hcd_free_pipe(uhcd_t hcd, upipe_t pipe)
{
	RT_ASSERT(pipe != RT_NULL);
	
	/* parameter check */
	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);	
	RT_ASSERT(hcd->ops->free_pipe!= RT_NULL);

	return hcd->ops->free_pipe(pipe);
}

rt_inline int rt_usb_hcd_bulk_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, 
	int nbytes, int timeout)
{
	if(pipe == RT_NULL) return -1;
	if(pipe->ifinst == RT_NULL) return -1;
	if(pipe->ifinst->uinst == RT_NULL) return -1;	
	if(pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
		return -1;

	/* parameter check */
	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);	
	RT_ASSERT(hcd->ops->bulk_xfer!= RT_NULL);

	return hcd->ops->bulk_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_control_xfer(uhcd_t hcd, uinst_t uinst, ureq_t setup, 
	void* buffer, int nbytes, int timeout)
{
	if(uinst->status == UINST_STATUS_IDLE) return -1;

	/* parameter check */
	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);	
	RT_ASSERT(hcd->ops->ctl_xfer!= RT_NULL);		

	return hcd->ops->ctl_xfer(uinst, setup, buffer, nbytes, timeout);
}

rt_inline int rt_usb_hcd_int_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, 
	int nbytes, int timeout)
{	
	if(pipe == RT_NULL) return -1;
	if(pipe->ifinst == RT_NULL) return -1;
	if(pipe->ifinst->uinst == RT_NULL) return -1;	
	if(pipe->ifinst->uinst->status == UINST_STATUS_IDLE) 
		return -1;

	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);	
	RT_ASSERT(hcd->ops->int_xfer!= RT_NULL);

	return hcd->ops->int_xfer(pipe, buffer, nbytes, timeout);
}

rt_inline rt_err_t rt_usb_hcd_hub_control(uhcd_t hcd, rt_uint16_t port, 
	rt_uint8_t cmd, void *args)
{	
	RT_ASSERT(hcd != RT_NULL);
	RT_ASSERT(hcd->ops != RT_NULL);
	RT_ASSERT(hcd->ops->hub_ctrl != RT_NULL);

	return hcd->ops->hub_ctrl(port, cmd, args);
}

#endif

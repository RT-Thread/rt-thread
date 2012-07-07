/*
 * File      : adk.c
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

#include <rtthread.h>
#include <drivers/usb_host.h>
#include "adk.h"

#ifdef RT_USB_CLASS_ADK

static struct uclass_driver adk_driver;

rt_err_t rt_usb_adk_read(uifinst_t ifinst, rt_uint8_t *buffer, 
	rt_size_t size)
{
	uadkinst_t adkinst;
	rt_size_t length;

	RT_ASSERT(buffer != RT_NULL);	

	if(ifinst == RT_NULL)
	{
		rt_kprintf("the interface is not available\n");
		return -RT_EIO;
	}
	
	/* get storage instance from the interface instance */	
	adkinst = (uadkinst_t)ifinst->user_data;

	/* send the cbw */
	length = rt_usb_hcd_bulk_xfer(ifinst->uinst->hcd, adkinst->pipe_in, 
		buffer, size, 300);
	
	return length;
}

rt_err_t rt_usb_adk_write(uifinst_t ifinst, rt_uint8_t *buffer, 
	rt_size_t size)
{
	uadkinst_t adkinst;
	rt_size_t length;

	RT_ASSERT(buffer != RT_NULL);	

	if(ifinst == RT_NULL)
	{
		rt_kprintf("the interface is not available\n");
		return -RT_EIO;
	}
	
	/* get storage instance from the interface instance */	
	adkinst = (uadkinst_t)ifinst->user_data;

	/* send the cbw */
	length = rt_usb_hcd_bulk_xfer(ifinst->uinst->hcd, adkinst->pipe_out, 
		buffer, size, 300);
	
	return length;
}

/**
 * This function will run adk class driver when usb device is detected and identified
 *  as a adk class device, it will continue the enumulate process.
 *
 * @param arg the argument.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usb_adk_run(void* arg)
{
	int i = 0;
	uadkinst_t adkinst;
	uifinst_t ifinst = (uifinst_t)arg;
	rt_err_t ret;
	
	/* parameter check */
	if(ifinst == RT_NULL)
	{
		rt_kprintf("the interface is not available\n");
		return -RT_EIO;
	}

	RT_DEBUG_LOG(RT_DEBUG_USB,("rt_usb_adk_run\n"));
	
	adkinst = rt_malloc(sizeof(struct uadkinst));
	RT_ASSERT(adkinst != RT_NULL);

	/* initilize the data structure */
	rt_memset(adkinst, 0, sizeof(struct uadkinst));	
	ifinst->user_data = (void*)adkinst;

	for(i=0; i<ifinst->intf_desc->bNumEndpoints; i++)
	{		
		uep_desc_t ep_desc;
		
		/* get endpoint descriptor from interface descriptor */
		rt_usb_get_endpoint_descriptor(ifinst->intf_desc, i, &ep_desc);
		if(ep_desc == RT_NULL)
		{
			rt_kprintf("rt_usb_get_endpoint_descriptor error\n");
			return -RT_ERROR;
		}
		
		/* the endpoint type of adk class should be BULK */	
		if((ep_desc->bmAttributes & USB_EP_ATTR_TYPE_MASK) != USB_EP_ATTR_BULK)
			continue;
		
		/* allocate pipes according to the endpoint type */
		if(ep_desc->bEndpointAddress & USB_DIR_IN)
		{
			/* allocate an in pipe for the adk instance */
			ret = rt_usb_hcd_alloc_pipe(ifinst->uinst->hcd, &adkinst->pipe_in, 
				ifinst, ep_desc, RT_NULL);
			if(ret != RT_EOK) return ret;
		}
		else
		{		
			/* allocate an output pipe for the adk instance */
			ret = rt_usb_hcd_alloc_pipe(ifinst->uinst->hcd, &adkinst->pipe_out, 
				ifinst, ep_desc, RT_NULL);			
			if(ret != RT_EOK) return ret;
		}
	}

	/* check pipes infomation */
	if(adkinst->pipe_in == RT_NULL || adkinst->pipe_out == RT_NULL)
	{
		rt_kprintf("pipe error, unsupported device\n");
		return -RT_ERROR;
	}	

	return RT_EOK;
}

/**
 * This function will be invoked when usb device plug out is detected and it would clean 
 * and release all hub class related resources.
 *
 * @param arg the argument.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usb_adk_stop(void* arg)
{
	uadkinst_t adkinst;
	uifinst_t ifinst = (uifinst_t)arg;

	RT_ASSERT(ifinst != RT_NULL);

	RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usb_adk_stop\n"));

	adkinst = (uadkinst_t)ifinst->user_data;

	if(adkinst->pipe_in != RT_NULL)
		rt_usb_hcd_free_pipe(ifinst->uinst->hcd, adkinst->pipe_in);

	/* free adk instance */
	if(adkinst != RT_NULL) rt_free(adkinst);
	
	/* free interface instance */
	if(ifinst != RT_NULL) rt_free(ifinst);

	return RT_EOK;
}

/**
 * This function will register adk class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 * 
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usb_class_driver_adk(void)
{
	adk_driver.class_code = USB_CLASS_ADK;
	
	adk_driver.run = rt_usb_adk_run;
	adk_driver.stop = rt_usb_adk_stop;

	return &adk_driver;
}

#endif


/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <drivers/usb_host.h>
#include "mass.h"

#ifdef RT_USBH_MSTORAGE

extern rt_err_t rt_udisk_run(struct uhintf* intf);
extern rt_err_t rt_udisk_stop(struct uhintf* intf);

static struct uclass_driver storage_driver;

/**
 * This function will do USBREQ_GET_MAX_LUN request for the usb interface instance.
 *
 * @param intf the interface instance.
 * @param max_lun the buffer to save max_lun.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t _pipe_check(struct uhintf* intf, upipe_t pipe)
{
    struct uinstance* device;
    rt_err_t ret;
    ustor_t stor;
    int size = 0;
    struct ustorage_csw csw;

    if(intf == RT_NULL || pipe == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    /* get usb device instance from the interface instance */
    device = intf->device;

    /* get storage instance from the interface instance */
    stor = (ustor_t)intf->user_data;

    /* check pipe status */
    if(pipe->status == UPIPE_STATUS_OK) return RT_EOK;

    if(pipe->status == UPIPE_STATUS_ERROR)
    {
        rt_kprintf("pipe status error\n");
        return -RT_EIO;
    }
    if(pipe->status == UPIPE_STATUS_STALL)
    {
        /* clear the pipe stall status */
        ret = rt_usbh_clear_feature(device, pipe->ep.bEndpointAddress,
            USB_FEATURE_ENDPOINT_HALT);
        if(ret != RT_EOK) return ret;
    }


    rt_thread_delay(50);

    rt_kprintf("pipes1 0x%x, 0x%x\n", stor->pipe_in, stor->pipe_out);

    stor->pipe_in->status = UPIPE_STATUS_OK;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("clean storage in pipe stall\n"));

    /* it should receive csw after clear the stall feature */
    size = rt_usb_hcd_pipe_xfer(stor->pipe_in->inst->hcd,
        stor->pipe_in, &csw, SIZEOF_CSW, 100);
    if(size != SIZEOF_CSW)
    {
        rt_kprintf("receive the csw after stall failed\n");
        return -RT_EIO;
    }

    return -RT_ERROR;
}

/**
 * This function will do USBREQ_GET_MAX_LUN request for the usb interface instance.
 *
 * @param intf the interface instance.
 * @param max_lun the buffer to save max_lun.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usb_bulk_only_xfer(struct uhintf* intf,
    ustorage_cbw_t cmd, rt_uint8_t* buffer, int timeout)
{
    rt_size_t size;
    rt_err_t ret;
    upipe_t pipe;
    struct ustorage_csw csw;
    ustor_t stor;

    RT_ASSERT(cmd != RT_NULL);

    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    /* get storage instance from the interface instance */
    stor = (ustor_t)intf->user_data;

    do
    {
        /* send the cbw */
        size = rt_usb_hcd_pipe_xfer(stor->pipe_out->inst->hcd, stor->pipe_out,
            cmd, SIZEOF_CBW, timeout);
        if(size != SIZEOF_CBW)
        {
            rt_kprintf("CBW size error\n");
            return -RT_EIO;
        }
        if(cmd->xfer_len != 0)
        {
            pipe = (cmd->dflags == CBWFLAGS_DIR_IN) ? stor->pipe_in :
                stor->pipe_out;
            size = rt_usb_hcd_pipe_xfer(pipe->inst->hcd, pipe, (void*)buffer,
                cmd->xfer_len, timeout);
            if(size != cmd->xfer_len)
            {
                rt_kprintf("request size %d, transfer size %d\n",
                    cmd->xfer_len, size);
                break;
            }
        }

        /* receive the csw */
        size = rt_usb_hcd_pipe_xfer(stor->pipe_in->inst->hcd, stor->pipe_in,
            &csw, SIZEOF_CSW, timeout);
        if(size != SIZEOF_CSW)
        {
            rt_kprintf("csw size error\n");
            return -RT_EIO;
        }
    }while(0);

    /* check in pipes status */
    ret = _pipe_check(intf, stor->pipe_in);
    if(ret != RT_EOK)
    {
        rt_kprintf("in pipe error\n");
        return ret;
    }

    /* check out pipes status */
    ret = _pipe_check(intf, stor->pipe_out);
    if(ret != RT_EOK)
    {
        rt_kprintf("out pipe error\n");
        return ret;
    }

    /* check csw status */
    if(csw.signature != CSW_SIGNATURE || csw.tag != CBW_TAG_VALUE)
    {
        rt_kprintf("csw signature error\n");
        return -RT_EIO;
    }

    if(csw.status != 0)
    {
        //rt_kprintf("csw status error:%d\n",csw.status);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * This function will do USBREQ_GET_MAX_LUN request for the usb interface instance.
 *
 * @param intf the interface instance.
 * @param max_lun the buffer to save max_lun.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_get_max_lun(struct uhintf* intf, rt_uint8_t* max_lun)
{
    struct uinstance* device;
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;

    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    /* parameter check */
    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_get_max_lun\n"));

    /* get usb device instance from the interface instance */
    device = intf->device;

    /* construct the request */
    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USBREQ_GET_MAX_LUN;
    setup.wValue = intf->intf_desc->bInterfaceNumber;
    setup.wIndex = 0;
    setup.wLength = 1;

    /* do control transfer request */
    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return -RT_EIO;
    }
    if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, max_lun, 1, timeout) != 1)
    {
        return -RT_EIO;
    }
    if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_out, RT_NULL, 0, timeout) != 0)
    {
        return -RT_EIO;
    }
    return RT_EOK;
}

/**
 * This function will do USBREQ_MASS_STORAGE_RESET request for the usb interface instance.
 *
 * @param intf the interface instance.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_reset(struct uhintf* intf)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_reset\n"));

    /* get usb device instance from the interface instance */
    device = intf->device;

    /* construct the request */
    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USBREQ_MASS_STORAGE_RESET;
    setup.wIndex = intf->intf_desc->bInterfaceNumber;
    setup.wLength = 0;
    setup.wValue = 0;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return -RT_EIO;
    }
    if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, RT_NULL, 0, timeout) != 0)
    {
        return -RT_EIO;
    }
    return RT_EOK;
}

/**
 * This function will execute SCSI_READ_10 command to read data from the usb device.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save read data
 * @param sector the start sector address to read.
 * @param sector the sector count to read.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_read10(struct uhintf* intf, rt_uint8_t *buffer,
    rt_uint32_t sector, rt_size_t count, int timeout)
{
    struct ustorage_cbw cmd;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_read10\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = SECTOR_SIZE * count;
    cmd.dflags = CBWFLAGS_DIR_IN;
    cmd.lun = 0;
    cmd.cb_len = 10;
    cmd.cb[0] = SCSI_READ_10;
    cmd.cb[1] = 0;
    cmd.cb[2] = (rt_uint8_t)(sector >> 24);
    cmd.cb[3] = (rt_uint8_t)(sector >> 16);
    cmd.cb[4] = (rt_uint8_t)(sector >> 8);
    cmd.cb[5] = (rt_uint8_t)sector;
    cmd.cb[6] = 0;
    cmd.cb[7] = (count & 0xff00) >> 8;
    cmd.cb[8] = (rt_uint8_t) count & 0xff;

    return rt_usb_bulk_only_xfer(intf, &cmd, buffer, timeout);
}

/**
 * This function will execute SCSI_WRITE_10 command to write data to the usb device.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save write data
 * @param sector the start sector address to write.
 * @param sector the sector count to write.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_write10(struct uhintf* intf, rt_uint8_t *buffer,
    rt_uint32_t sector, rt_size_t count, int timeout)
{
    struct ustorage_cbw cmd;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_write10\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = SECTOR_SIZE * count;
    cmd.dflags = CBWFLAGS_DIR_OUT;
    cmd.lun = 0;
    cmd.cb_len = 10;
    cmd.cb[0] = SCSI_WRITE_10;
    cmd.cb[1] = 0;
    cmd.cb[2] = (rt_uint8_t)(sector >> 24);
    cmd.cb[3] = (rt_uint8_t)(sector >> 16);
    cmd.cb[4] = (rt_uint8_t)(sector >> 8);
    cmd.cb[5] = (rt_uint8_t)sector;
    cmd.cb[6] = 0;
    cmd.cb[7] = (count & 0xff00) >> 8;
    cmd.cb[8] = (rt_uint8_t) count & 0xff;

    return rt_usb_bulk_only_xfer(intf, &cmd, buffer, timeout);
}

/**
 * This function will execute SCSI_REQUEST_SENSE command to get sense data.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save sense data
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_request_sense(struct uhintf* intf, rt_uint8_t* buffer)
{
    struct ustorage_cbw cmd;
    int timeout = USB_TIMEOUT_LONG;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_request_sense\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = 18;
    cmd.dflags = CBWFLAGS_DIR_IN;
    cmd.lun = 0;
    cmd.cb_len = 6;
    cmd.cb[0] = SCSI_REQUEST_SENSE;
    cmd.cb[4] = 18;

    return rt_usb_bulk_only_xfer(intf, &cmd, buffer, timeout);
}

/**
 * This function will execute SCSI_TEST_UNIT_READY command to get unit ready status.
 *
 * @param intf the interface instance.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_test_unit_ready(struct uhintf* intf)
{
    struct ustorage_cbw cmd;
    int timeout = USB_TIMEOUT_LONG;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_test_unit_ready\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = 0;
    cmd.dflags = CBWFLAGS_DIR_OUT;
    cmd.lun = 0;
    cmd.cb_len = 12;
    cmd.cb[0] = SCSI_TEST_UNIT_READY;

    return rt_usb_bulk_only_xfer(intf, &cmd, RT_NULL, timeout);
}

/**
 * This function will execute SCSI_INQUIRY_CMD command to get inquiry data.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save inquiry data
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_inquiry(struct uhintf* intf, rt_uint8_t* buffer)
{
    struct ustorage_cbw cmd;
    int timeout = USB_TIMEOUT_LONG;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_inquiry\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = 36;
    cmd.dflags = CBWFLAGS_DIR_IN;
    cmd.lun = 0;
    cmd.cb_len = 6;//12
    cmd.cb[0] = SCSI_INQUIRY_CMD;
    cmd.cb[4] = 36;

    return rt_usb_bulk_only_xfer(intf, &cmd, buffer, timeout);
}

/**
 * This function will execute SCSI_READ_CAPACITY command to get capacity data.
 *
 * @param intf the interface instance.
 * @param buffer the data buffer to save capacity data
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_storage_get_capacity(struct uhintf* intf, rt_uint8_t* buffer)
{
    struct ustorage_cbw cmd;
    int timeout = USB_TIMEOUT_LONG;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_ASSERT(intf->device != RT_NULL);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_get_capacity\n"));

    /* construct the command block wrapper */
    rt_memset(&cmd, 0, sizeof(struct ustorage_cbw));
    cmd.signature = CBW_SIGNATURE;
    cmd.tag = CBW_TAG_VALUE;
    cmd.xfer_len = 8;
    cmd.dflags = CBWFLAGS_DIR_IN;
    cmd.lun = 0;
    cmd.cb_len = 12;
    cmd.cb[0] = SCSI_READ_CAPACITY;

    return rt_usb_bulk_only_xfer(intf, &cmd, buffer, timeout);
}

/**
 * This function will run mass storage class driver when usb device is detected
 * and identified as a mass storage class device, it will continue to do the enumulate
 * process.
 *
 * @param arg the argument.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_storage_enable(void* arg)
{
    int i = 0;
    rt_err_t ret;
    ustor_t stor;
    struct uhintf* intf = (struct uhintf*)arg;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    RT_DEBUG_LOG(RT_DEBUG_USB, ("subclass %d, protocal %d\n",
        intf->intf_desc->bInterfaceSubClass,
        intf->intf_desc->bInterfaceProtocol));

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_run\n"));

    /* only support SCSI subclass and bulk only protocal */

    stor = rt_malloc(sizeof(struct ustor));
    RT_ASSERT(stor != RT_NULL);

    /* initilize the data structure */
    rt_memset(stor, 0, sizeof(struct ustor));
    intf->user_data = (void*)stor;

    for(i=0; i<intf->intf_desc->bNumEndpoints; i++)
    {
        uep_desc_t ep_desc;

        /* get endpoint descriptor from interface descriptor */
        rt_usbh_get_endpoint_descriptor(intf->intf_desc, i, &ep_desc);
        if(ep_desc == RT_NULL)
        {
            rt_kprintf("rt_usb_get_endpoint_descriptor error\n");
            return -RT_ERROR;
        }

        /* the endpoint type of mass storage class should be BULK */
        if((ep_desc->bmAttributes & USB_EP_ATTR_TYPE_MASK) != USB_EP_ATTR_BULK)
            continue;

        /* allocate pipes according to the endpoint type */
        if(ep_desc->bEndpointAddress & USB_DIR_IN)
        {
            /* alloc an in pipe for the storage instance */
            stor->pipe_in = rt_usb_instance_find_pipe(intf->device,ep_desc->bEndpointAddress);
        }
        else
        {
            /* alloc an output pipe for the storage instance */
            stor->pipe_out = rt_usb_instance_find_pipe(intf->device,ep_desc->bEndpointAddress);
        }
    }

    /* check pipes infomation */
    if(stor->pipe_in == RT_NULL || stor->pipe_out == RT_NULL)
    {
        rt_kprintf("pipe error, unsupported device\n");
        return -RT_ERROR;
    }

    /* should implement as callback */
    ret = rt_udisk_run(intf);
    if(ret != RT_EOK) return ret;

    return RT_EOK;
}

/**
 * This function will be invoked when usb device plug out is detected and it would clean
 * and release all mass storage class related resources.
 *
 * @param arg the argument.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_storage_disable(void* arg)
{
    ustor_t stor;
    struct uhintf* intf = (struct uhintf*)arg;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->user_data != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_storage_stop\n"));

    /* get storage instance from interface instance */
    stor = (ustor_t)intf->user_data;

    rt_udisk_stop(intf);


    /* free storage instance */
    if(stor != RT_NULL) rt_free(stor);
    return RT_EOK;
}

/**
 * This function will register mass storage class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 *
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usbh_class_driver_storage(void)
{
    storage_driver.class_code = USB_CLASS_MASS_STORAGE;

    storage_driver.enable = rt_usbh_storage_enable;
    storage_driver.disable = rt_usbh_storage_disable;

    return &storage_driver;
}

#endif


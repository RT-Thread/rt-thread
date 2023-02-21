/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.07.xx
*
* Description :
*
* History :
*******************************************************************************
*/

//#include "usb_host_config.h"

//#include "usb_os_platform.h"
//#include "usb_host_base_types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <log.h>
#include <usb_list.h>

#include <usb_host_common.h>
#include "usb_core_base.h"
#include "usb_gen_hub.h"
#include "usb_msg.h"
#include "usb_gen_hub.h"
#include "usb_virt_bus.h"
#include "usb_msg_base.h"



/**
 *  usb_control_msg - Builds a control urb, sends it off and waits for completion
 *  @dev: pointer to the usb device to send the message to
 *  @pipe: endpoint "pipe" to send the message to
 *  @request: USB message request value
 *  @requesttype: USB message request type value
 *  @value: USB message value
 *  @index: USB message index value
 *  @data: pointer to the data to send
 *  @size: length in bytes of the data to send
 *  @timeout: time in msecs to wait for the message to complete before
 *      timing out (if 0 the wait is forever)
 *  Context: !in_interrupt ()
 *
 *  This function sends a simple control message to a specified endpoint
 *  and waits for the message to complete, or timeout.
 *
 *  If successful, it returns the number of bytes transferred, otherwise a negative error number.
 *
 *  Don't use this function from within an interrupt context, like a
 *  bottom half handler.  If you need an asynchronous message, or need to send
 *  a message from within interrupt context, use usb_submit_urb()
 *      If a thread in your driver uses this call, make sure your disconnect()
 *      method can wait for it to complete.  Since you don't have a handle on
 *      the URB used, you can't cancel the request.
 */
int usb_control_msg(struct usb_host_virt_dev *dev, u32 pipe, u8 request, u8 requesttype,
                    u16 value, u16 index, void *data, u16 size, s32 timeout)
{
    int ret  = 0;
    struct usb_ctrlrequest *dr = NULL;
    dr = malloc(sizeof(struct usb_ctrlrequest));

    if (!dr)
    {
        hal_log_err("ERR: malloc failed");
        return -ENOMEM;
    }

    memset(dr, 0, sizeof(struct usb_ctrlrequest));
    dr->bRequestType    = requesttype;
    dr->bRequest        = request;
    //dr->wValue          = cpu_to_le16(value);
    //dr->wIndex          = cpu_to_le16(index);
    //dr->wLength         = cpu_to_le16(size);
    dr->wValue          = value;
    dr->wIndex          = index;
    dr->wLength         = size;
    ret = _usb_internal_ctrll_msg(dev, pipe, dr, data, size, timeout);

    if (dr)
    {
        free((void *)dr);
        dr = NULL;
    }
    else
    {
       hal_log_err("ERR: parameter is NULL, can't free");
    }

    return ret;
}

/**
 *  usb_bulk_msg - Builds a bulk urb, sends it off and waits for completion
 *  @usb_dev: pointer to the usb device to send the message to
 *  @pipe: endpoint "pipe" to send the message to
 *  @data: pointer to the data to send
 *  @len: length in bytes of the data to send
 *  @actual_length: pointer to a location to put the actual length transferred in bytes,实际收发的长度
 *  @timeout: time in msecs to wait for the message to complete before
 *      timing out (if 0 the wait is forever)
 *  Context: !in_interrupt ()
 *
 *  This function sends a simple bulk message to a specified endpoint
 *  and waits for the message to complete, or timeout.
 *
 *  If successful, it returns 0, otherwise a negative error number.
 *  The number of actual bytes transferred will be stored in the
 *  actual_length paramater.
 *
 *  Don't use this function from within an interrupt context, like a
 *  bottom half handler.  If you need an asynchronous message, or need to
 *  send a message from within interrupt context, use usb_submit_urb()
 *      If a thread in your driver uses this call, make sure your disconnect()
 *      method can wait for it to complete.  Since you don't have a handle on
 *      the URB used, you can't cancel the request.
 */
int usb_bulk_msg(struct usb_host_virt_dev *usb_dev, unsigned int pipe,
                 void *data, int len, int *actual_length, int timeout)
{
    if (usb_dev == NULL || data == NULL || len < 0)
    {
        return -EINVAL;
    }

    return _usb_internal_bulk_msg(usb_dev,
                                  pipe,
                                  data,
                                  len,
                                  actual_length,
                                  timeout);
}

/**
 * usb_get_descriptor - issues a generic GET_DESCRIPTOR request
 * @dev: the device whose descriptor is being retrieved
 * @type: the descriptor type (USB_DT_*)
 * @index: the number of the descriptor
 * @buf: where to put the descriptor
 * @size: how big is "buf"?
 * Context: !in_interrupt ()
 *
 * Gets a USB descriptor.  Convenience functions exist to simplify
 * getting some types of descriptors.  Use
 * usb_get_string() or usb_string() for USB_DT_STRING.
 * Device (USB_DT_DEVICE) and configuration descriptors (USB_DT_CONFIG)
 * are part of the device structure.
 * In addition to a number of USB-standard descriptors, some
 * devices also use class-specific or vendor-specific descriptors.
 *
 * This call is synchronous, and may not be used in an interrupt context.
 *
 * Returns the number of bytes received on success, or else the status code
 * returned by the underlying usb_control_msg() call.
 */
/* 带重试的ctrl传输，的desc */
s32 usb_get_descriptor(struct usb_host_virt_dev *dev, u8 type, u8 index, void *buf, s32 size)
{
    int i = 0;
    int result = 0;
    memset(buf, 0, size); // Make sure we parse really received data

    for (i = 0; i < 3; ++i)
    {
        /* retry on length 0 or stall; some devices are flakey */
        result = usb_control_msg(dev,
                                 usb_rcvctrlpipe(dev, 0),
                                 USB_REQ_GET_DESCRIPTOR,
                                 USB_DIR_IN,
                                 (type << 8) + index,
                                 0,
                                 buf,
                                 size,
                                 USB_CTRL_GET_TIMEOUT);

        if (result == 0 || result == -EPIPE)
        {
            hal_log_err("get_descriptor faile 1");
            continue;
        }

        if (result > 1 && ((u8 *)buf)[1] != type)
        {
            hal_log_err("get_descriptor faile 2");
            result = -EPROTO;
            continue;
        }

        break;
    }

    return result;
}

/*
*******************************************************************************
*                     usb_get_extra_descriptor
*
* Description:
*     在已得到的全部描述符里找到想要的描述符。
*
* Parameters:
*     buffer  :  input. 已经得到的全部描述符
*     size    :  input. 全部描述符的长度
*     type    :  input. 想要的描述符类型
*     ptr     :  input. 想要的描述符的起始位置
*
* Return value:
*
*
* note:
*    无
*
*******************************************************************************
*/
int __usb_get_extra_descriptor(unsigned char *buffer,
                               unsigned size,
                               unsigned char type,
                               void **ptr)
{
    struct usb_descriptor_header *header;

    while (size >= sizeof(struct usb_descriptor_header))
    {
        header = (struct usb_descriptor_header *)buffer;

        if (header->bLength < 2)
        {
            __err("bogus descriptor, type %d length %d",
                       header->bDescriptorType,
                       header->bLength);
            return -1;
        }

        if (header->bDescriptorType == type)
        {
            *ptr = header;
            return 0;
        }

        buffer += header->bLength;
        size -= header->bLength;
    }

    return -1;
}


/**
 * usb_string - returns ISO 8859-1 version of a string descriptor
 * @dev: the device whose string descriptor is being retrieved
 * @index: the number of the descriptor
 * @buf: where to put the string
 * @size: how big is "buf"?
 * Context: !in_interrupt ()
 *
 * This converts the UTF-16LE encoded strings returned by devices, from
 * usb_get_string_descriptor(), to null-terminated ISO-8859-1 encoded ones
 * that are more usable in most kernel contexts.  Note that all characters
 * in the chosen descriptor that can't be encoded using ISO-8859-1
 * are converted to the question mark ("?") character, and this function
 * chooses strings in the first language supported by the device.
 *
 * The ASCII (or, redundantly, "US-ASCII") character set is the seven-bit
 * subset of ISO 8859-1. ISO-8859-1 is the eight-bit subset of Unicode,
 * and is appropriate for use many uses of English and several other
 * Western European languages.  (But it doesn't include the "Euro" symbol.)
 *
 * This call is synchronous, and may not be used in an interrupt context.
 *
 * Returns length of the string (>= 0) or usb_control_msg status (< 0).
 */
int usb_string(struct usb_host_virt_dev *dev, int index, char *buf, u32 size)
{
    unsigned char *tbuf = NULL;
    s32 err = 0;
    u32 u = 0, idx = 0;

    if (dev->state == USB_STATE_SUSPENDED)
    {
        __err("ERR: usb_string, status is invalid");
        return -EHOSTUNREACH;
    }

    if (((s32)size) <= 0 || !buf || !index)
    {
        __err("ERR: usb_string, input error");
        return -EINVAL;
    }

    buf[0] = 0;
    tbuf = malloc(256);

    if (!tbuf)
    {
        __err("ERR: usb_string, malloc failed");
        return -ENOMEM;
    }

    memset(tbuf, 0, 256);

    // get langid for strings if it's not yet known //
    if (!dev->have_langid)
    {
        err = _usb_string_sub(dev, 0, 0, tbuf);

        if (err < 0)
        {
            __err("PANIC : string descriptor 0 read error: %d", err);
            goto errout;
        }
        else if (err < 4)
        {
            __err("PANIC : string descriptor 0 too short");
            err = -EINVAL;
            goto errout;
        }
        else
        {
            dev->have_langid = -1;
            dev->string_langid = tbuf[2] | (tbuf[3] << 8);
        }
    }

    err = _usb_string_sub(dev, dev->string_langid, index, tbuf);

    if (err < 0)
    {
        goto errout;
    }

    //leave room for trailing NULL char in output buffer//
    size--;

    for (idx = 0, u = 2; u < err; u += 2)
    {
        if (idx >= size)
        {
            break;
        }

        if (tbuf[u + 1])        //high byte
        {
            buf[idx++] = '?';  // non ISO-8859-1 character //
        }
        else
        {
            buf[idx++] = tbuf[u];
        }
    }

    buf[idx] = 0;
    err = idx;

    if (tbuf[1] != USB_DT_STRING)
    {
        __inf("wrong descriptor type %02x for string %d (\"%s\")", tbuf[1], index, buf);
    }

errout:

    if (tbuf)
    {
        free(tbuf);
        tbuf = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    return err;
}





/*
 * usb_enable_endpoint - Enable an endpoint for USB communications
 * @dev: the device whose interface is being enabled
 * @ep: the endpoint
 *
 * Resets the endpoint toggle, and sets dev->ep_{in,out} pointers.
 * For control endpoints, both the input and output sides are handled.
 */
static void usb_enable_endpoint(struct usb_host_virt_dev *dev, struct usb_host_virt_endpoint *ep)
{
    unsigned int epaddr = ep->desc.bEndpointAddress;
    unsigned int epnum = epaddr & USB_ENDPOINT_NUMBER_MASK;
    int is_control = 0;
    is_control = ((ep->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_CONTROL);

    if (usb_endpoint_out(epaddr) || is_control)
    {
        usb_settoggle(dev, epnum, 1, 0);
        dev->ep_out[epnum] = ep;
    }

    if (!usb_endpoint_out(epaddr) || is_control)
    {
        usb_settoggle(dev, epnum, 0, 0);
        dev->ep_in[epnum] = ep;
    }

    return;
}



/*
 * usb_enable_interface - Enable all the endpoints for an interface
 * @dev: the device whose interface is being enabled
 * @intf: pointer to the interface descriptor
 *
 * Enables all the endpoints for the interface's current altsetting.
 */
static void usb_enable_interface(struct usb_host_virt_dev *dev,
                                 struct usb_interface *intf)
{
    struct usb_host_virt_interface *alt = intf->cur_altsetting;
    int i;

    for (i = 0; i < alt->desc.bNumEndpoints; ++i)
    {
        usb_enable_endpoint(dev, &alt->endpoint[i]);
    }
}



/*
 * usb_set_configuration - Makes a particular device setting be current
 * @dev: the device whose configuration is being updated
 * @configuration: the configuration being chosen.
 * Context: !in_interrupt(), caller owns the device lock
 *
 * This is used to enable non-default device modes.  Not all devices
 * use this kind of configurability; many devices only have one
 * configuration.
 *
 * USB device configurations may affect Linux interoperability,
 * power consumption and the functionality available.  For example,
 * the default configuration is limited to using 100mA of bus power,
 * so that when certain device functionality requires more power,
 * and the device is bus powered, that functionality should be in some
 * non-default device configuration.  Other device modes may also be
 * reflected as configuration options, such as whether two ISDN
 * channels are available independently; and choosing between open
 * standard device protocols (like CDC) or proprietary ones.
 *
 * Note that USB has an additional level of device configurability,
 * associated with interfaces.  That configurability is accessed using
 * usb_set_interface().
 *
 * This call is synchronous. The calling context must be able to sleep,
 * must own the device lock, and must not hold the driver model's USB
 * bus rwsem; usb device driver probe() methods cannot use this routine.
 *
 * Returns zero on success, or else the status code returned by the
 * underlying call that failed.  On successful completion, each interface
 * in the original device configuration has been destroyed, and each one
 * in the new configuration has been probed by all relevant usb device
 * drivers currently known to the kernel.
 */


//virt_father_dev   :   与物理设备对应的
//configuration :   要设置的config的index
s32 usb_set_configuration(struct usb_host_virt_dev *virt_father_dev, s32 configuration)
{
    int i = 0, ret = 0;
    struct usb_host_virt_config *virt_confg = NULL;
    struct usb_interface **new_interfaces = NULL;       //记录分配的usb_interface的地址
    s32 n = 0;
    s32 nintf = 0;      //该config的interface数目

    //--<1>--根据具体的config index,获得其virt_config结构
    for (i = 0; i < virt_father_dev->descriptor.bNumConfigurations; i++)
    {
        if (virt_father_dev->config[i].desc.bConfigurationValue == configuration)
        {
            virt_confg = &virt_father_dev->config[i];
            break;
        }
    }

    if ((!virt_confg && configuration != 0))
    {
        __err("ERR : set config fail");
        return -EINVAL;
    }

    /* The USB spec says configuration 0 means unconfigured.
     * But if a device includes a configuration numbered 0,
     * we will accept it as a correctly configured state.
     */
    if (virt_confg && configuration == 0)
    {
        __err("ERR : config 0 descriptor??");
    }

    if (virt_father_dev->state == USB_STATE_SUSPENDED)
    {
        __err("ERR: usb_set_configuration: device is suspended");
        return -EHOSTUNREACH;
    }

    //--<2>--创建cp->desc.bNumInterfaces个usb_interface结构
    /* Allocate memory for new interfaces before doing anything else,
     * so that if we run out then nothing will have changed. */
    n = nintf = 0;

    if (virt_confg)
    {
        nintf = virt_confg->desc.bNumInterfaces;

        if (nintf > USB_MAX_VIRT_SUB_DEV_NR)
        {
            __err("PANIC : Set_Conifg : too many interface,now we only support %d interfaces", USB_MAX_VIRT_SUB_DEV_NR);
            return -EINVAL;
        }

        new_interfaces = malloc(nintf * (sizeof(struct usb_interface *)));

        if (!new_interfaces)
        {
            __err("PANIC : Out of memory");
            return -ENOMEM;
        }

        memset(new_interfaces, 0, nintf * (sizeof(struct usb_interface *)));

        for (; n < nintf; ++n)
        {
            new_interfaces[n] = malloc(sizeof(struct usb_interface));

            if (!new_interfaces[n])
            {
                __err("PANIC : Out of memory");
                ret = -ENOMEM;
free_interfaces:

                while (--n >= 0)
                {
                    if (new_interfaces[n])
                    {
                        free(new_interfaces[n]);
                        new_interfaces[n] = NULL;
                    }
                    else
                    {
                        __err("ERR: parameter is NULL, can't free");
                    }
                }

                if (new_interfaces)
                {
                    free(new_interfaces);
                    new_interfaces = NULL;
                }
                else
                {
                    __err("ERR: parameter is NULL, can't free");
                }

                return ret;
            }

            memset(new_interfaces[n], 0, sizeof(struct usb_interface));
        }
    }

    /* if it's already configured, clear out old state first.
     * getting rid of old interfaces means unbinding their drivers.
     */
    if (virt_father_dev->state != USB_STATE_ADDRESS)
    {
        usb_disable_device(virt_father_dev, 1);     // Skip ep0
    }

    //--<3>--发送set config
    if ((ret = usb_control_msg(virt_father_dev, usb_sndctrlpipe(virt_father_dev, 0),
                               USB_REQ_SET_CONFIGURATION, 0, configuration, 0,
                               NULL, 0, USB_CTRL_SET_TIMEOUT)) < 0)
    {
        goto free_interfaces;
    }

    //--<4>--记录当前active的ep
    virt_father_dev->actconfig = virt_confg;

    //--<5>--配置该config旗下的 interface
    if (!virt_confg)
    {
        usb_set_device_state(virt_father_dev, USB_STATE_ADDRESS);
    }
    else
    {
        usb_set_device_state(virt_father_dev, USB_STATE_CONFIGURED);

        /* Initialize the new interface structures and the
         * hc/hcd/usbcore interface/endpoint state.
         */
        for (i = 0; i < nintf; ++i)
        {
            struct usb_interface_cache *intf_cache;
            struct usb_interface *intf;
            struct usb_host_virt_interface *alt;
            //从interface cache中获取，并初始化usb_interface
            virt_confg->interfac[i] = intf = new_interfaces[i];
            memset(intf, 0, sizeof(struct usb_interface));
            intf_cache = virt_confg->intf_cache[i];
            intf->altsetting = intf_cache->altsetting_array;
            intf->num_altsetting = intf_cache->num_altsetting;
            alt = usb_altnum_to_altsetting(intf, 0);

            /* No altsetting 0?  We'll assume the first altsetting.
             * We could use a GetInterface call, but if a device is
             * so non-compliant that it doesn't have altsetting 0
             * then I wouldn't trust its reply anyway.
             */
            if (!alt)
            {
                alt = &intf->altsetting[0];
            }

            intf->cur_altsetting = alt;
            usb_enable_interface(virt_father_dev, intf);
            //完成virt_dev,virt_sub_dev,intf互相指
            intf->virt_sub_dev = &(virt_father_dev->virt_sub_dev_array[i]);
            intf->virt_sub_dev->father_dev = virt_father_dev;   //指向父亲
            intf->virt_sub_dev->sub_dev_interface = intf;
        }

        if (new_interfaces)
        {
            free(new_interfaces);
            new_interfaces = NULL;
        }
        else
        {
            __err("ERR: parameter is NULL, can't free");
        }

        if ((virt_confg->desc.iConfiguration) && (virt_confg->string == NULL))
        {
            virt_confg->string = malloc(256);

            if (virt_confg->string)
            {
                memset(virt_confg->string, 0, 256);
                usb_string(virt_father_dev, virt_confg->desc.iConfiguration, virt_confg->string, 256);
            }
        }

        /* Now that all the interfaces are set up, register them
         * to trigger binding of drivers to interfaces.  probe()
         * routines may install different altsettings and may
         * claim() any interfaces not yet bound.  Many class drivers
         * need that: CDC, audio, video, etc.
         */
        //--<5_2>--将创建的usb_host_virt_sub_dev添加到bus
        for (i = 0; i < nintf; ++i)
        {
            struct usb_interface *intf = virt_confg->interfac[i];
            __inf("[usbh core]: adding sub dev  (config #%d, interface %d)", configuration, intf->altsetting [0].desc.bInterfaceNumber);

            /* msc在扫描盘符的时候,这里发get_interface, 两个urb会造成suni的hcd混乱,
              因此, 这里只识别device的第一个interface */
            if (!i)
            {
                if ((intf->cur_altsetting->desc.iInterface) && (intf->cur_altsetting->string == NULL))
                {
                    intf->cur_altsetting->string = malloc(256);

                    if (intf->cur_altsetting->string)
                    {
                        memset(intf->cur_altsetting->string, 0, 256);
                        usb_string(virt_father_dev,
                                   intf->cur_altsetting->desc.iInterface,
                                   intf->cur_altsetting->string,
                                   256);
                    }
                    else
                    {
                        __err("ERR: malloc failed");
                    }
                }
            }

            ret = usb_virt_bus_dev_add(intf->virt_sub_dev);

            if (ret != 0)
            {
                __err("PANIC : usb_virt_bus_dev_add() fail ret = %d", ret);

                if (intf->cur_altsetting->string)
                {
                    free(intf->cur_altsetting->string);
                    intf->cur_altsetting->string = NULL;
                }
                else
                {
                    __err("ERR: parameter is NULL, can't free");
                }

                continue;
            }
        }
    }

    return 0;
}




/*
 * usb_get_device_descriptor - (re)reads the device descriptor (usbcore)
 * @dev: the device whose device descriptor is being updated
 * @size: how much of the descriptor to read
 * Context: !in_interrupt ()
 *
 * Updates the copy of the device descriptor stored in the device structure,
 * which dedicates space for this purpose.  Note that several fields are
 * converted to the host CPU's byte order:  the USB version (bcdUSB), and
 * vendors product and version fields (idVendor, idProduct, and bcdDevice).
 * That lets device drivers compare against non-byteswapped constants.
 *
 * Not exported, only for use by the core.  If drivers really want to read
 * the device descriptor directly, they can call usb_get_descriptor() with
 * type = USB_DT_DEVICE and index = 0.
 *
 * This call is synchronous, and may not be used in an interrupt context.
 *
 * Returns the number of bytes received on success, or else the status code
 * returned by the underlying usb_control_msg() call.
 */
/* 获得设备desc,会自动拷贝到usb_host_virt_dev->设备描述符中 */
#if 0
s32 usb_get_device_descriptor(struct usb_host_virt_dev *dev, u32 size)
{
    struct usb_device_descriptor *desc = NULL;
    s32 ret = 0;

    if (size > sizeof(struct usb_device_descriptor))
    {
        return -EINVAL;
    }

    desc = malloc(sizeof(struct usb_device_descriptor), USB_MEM_FILE_TRIGGER, USB_MEM_LINE_TRIGGER);

    if (!desc)
    {
        __err("ERR: malloc failed");
        return -ENOMEM;
    }

    memset(desc, 0, sizeof(struct usb_device_descriptor));
    ret = usb_get_descriptor(dev, USB_DT_DEVICE, 0, (void *)desc, size);

    if (ret >= 0)
    {
        USB_OS_MEMCPY((void *)(&dev->descriptor), (void *)desc, size);
    }

    if (desc)
    {
        free((void *)desc);
        desc = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    return ret;
}
#else
s32 usb_get_device_descriptor(struct usb_host_virt_dev *dev, u32 size)
{
    struct usb_device_descriptor desc __attribute__((aligned(4)));
    s32 ret = 0;
    hal_log_info("---usb_get_device_descriptor---1--\n");
    if (size > sizeof(struct usb_device_descriptor))
    {
        return -EINVAL;
    }

    memset(&desc, 0, sizeof(struct usb_device_descriptor));
    hal_log_info("---usb_get_device_descriptor---2--\n");
    ret = usb_get_descriptor(dev, USB_DT_DEVICE, 0, (void *)&desc, size);

    hal_log_info("---usb_get_device_descriptor---3--\n");
    if (ret >= 0)
    {
        memcpy((void *)(&dev->descriptor), (void *)&desc, size);
    }

    return ret;
}
#endif


/**
 * usb_get_status - issues a GET_STATUS call
 * @dev: the device whose status is being checked
 * @type: USB_RECIP_*; for device, interface, or endpoint
 * @target: zero (for device), else interface or endpoint number
 * @data: pointer to two bytes of bitmap data
 * Context: !in_interrupt ()
 *
 * Returns device, interface, or endpoint status.  Normally only of
 * interest to see if the device is self powered, or has enabled the
 * remote wakeup facility; or whether a bulk or interrupt endpoint
 * is halted ("stalled").
 *
 * Bits in these status bitmaps are set using the SET_FEATURE request,
 * and cleared using the CLEAR_FEATURE request.  The usb_clear_halt()
 * function should be used to clear halt ("stall") status.
 *
 * This call is synchronous, and may not be used in an interrupt context.
 *
 * Returns the number of bytes received on success, or else the status code
 * returned by the underlying usb_control_msg() call.
 */
/* 发送到hub的get status的ctrl传输 */
int usb_get_status(struct usb_host_virt_dev *dev, s32 type, s32 target, void *data)
{
    s32 ret = 0;
    u16 *status = malloc(sizeof(*status));

    if (!status)
    {
        __err("ERR:　usb_get_status, malloc failed");
        return -ENOMEM;
    }

    memset(status, 0, sizeof(*status));
    ret = usb_control_msg(dev,
                          usb_rcvctrlpipe(dev, 0),
                          USB_REQ_GET_STATUS, USB_DIR_IN | type,
                          0,
                          target,
                          status,
                          sizeof(*status), USB_CTRL_GET_TIMEOUT);
    *(u16 *)data = *status;

    if (status)
    {
        free(status);
        status = NULL;
    }
    else
    {
        __err("ERR: parameter is NULL, can't free");
    }

    return ret;
}

/**
 * usb_clear_halt - tells device to clear endpoint halt/stall condition
 * @dev: device whose endpoint is halted
 * @pipe: endpoint "pipe" being cleared
 * Context: !in_interrupt ()
 *
 * This is used to clear halt conditions for bulk and interrupt endpoints,
 * as reported by URB completion status.  Endpoints that are halted are
 * sometimes referred to as being "stalled".  Such endpoints are unable
 * to transmit or receive data until the halt status is cleared.  Any URBs
 * queued for such an endpoint should normally be unlinked by the driver
 * before clearing the halt condition, as described in sections 5.7.5
 * and 5.8.5 of the USB 2.0 spec.
 *
 * Note that control and isochronous endpoints don't halt, although control
 * endpoints report "protocol stall" (for unsupported requests) using the
 * same status code used to report a true stall.
 *
 * This call is synchronous, and may not be used in an interrupt context.
 *
 * Returns zero on success, or else the status code returned by the
 * underlying usb_control_msg() call.
 */
int usb_clear_halt(struct usb_host_virt_dev *dev, int pipe)
{
    int result;
    int endp = usb_pipeendpoint(pipe);

    if (usb_pipein(pipe))
    {
        endp |= USB_DIR_IN;
    }

    /* we don't care if it wasn't halted first. in fact some devices
     * (like some ibmcam model 1 units) seem to expect hosts to make
     * this request for iso endpoints, which can't halt!
     */
    result = usb_control_msg(dev,
                             usb_sndctrlpipe(dev, 0),
                             USB_REQ_CLEAR_FEATURE,
                             USB_RECIP_ENDPOINT,
                             USB_ENDPOINT_HALT,
                             endp,
                             NULL,
                             0,
                             USB_CTRL_SET_TIMEOUT);

    /* don't un-halt or force to DATA0 except on success */
    if (result < 0)
    {
        return result;
    }

    /* NOTE:  seems like Microsoft and Apple don't bother verifying
     * the clear "took", so some devices could lock up if you check...
     * such as the Hagiwara FlashGate DUAL.  So we won't bother.
     *
     * NOTE:  make sure the logic here doesn't diverge much from
     * the copy in usb-storage, for as long as we need two copies.
     */
    /* toggle was reset by the clear */
    usb_settoggle(dev, usb_pipeendpoint(pipe), usb_pipeout(pipe), 0);
    return 0;
}



/**
 * usb_set_interface - Makes a particular alternate setting be current
 * @dev: the device whose interface is being updated
 * @interface: the interface being updated
 * @alternate: the setting being chosen.
 * Context: !in_interrupt ()
 *
 * This is used to enable data transfers on interfaces that may not
 * be enabled by default.  Not all devices support such configurability.
 * Only the driver bound to an interface may change its setting.
 *
 * Within any given configuration, each interface may have several
 * alternative settings.  These are often used to control levels of
 * bandwidth consumption.  For example, the default setting for a high
 * speed interrupt endpoint may not send more than 64 bytes per microframe,
 * while interrupt transfers of up to 3KBytes per microframe are legal.
 * Also, isochronous endpoints may never be part of an
 * interface's default setting.  To access such bandwidth, alternate
 * interface settings must be made current.
 *
 * Note that in the Linux USB subsystem, bandwidth associated with
 * an endpoint in a given alternate setting is not reserved until an URB
 * is submitted that needs that bandwidth.  Some other operating systems
 * allocate bandwidth early, when a configuration is chosen.
 *
 * This call is synchronous, and may not be used in an interrupt context.
 * Also, drivers must not change altsettings while urbs are scheduled for
 * endpoints in that interface; all such urbs must first be completed
 * (perhaps forced by unlinking).
 *
 * Returns zero on success, or else the status code returned by the
 * underlying usb_control_msg() call.
 */
int usb_set_interface(struct usb_host_virt_dev  *dev, int interface, int alternate)
{
    struct usb_interface *iface;
    struct usb_host_virt_interface *alt;
    int ret;
    int manual = 0;

    if (dev == NULL)
    {
        __err("ERR: invalid argment");
        return -1;
    }

    if (dev->state == USB_STATE_SUSPENDED)
    {
        return -EHOSTUNREACH;
    }

    iface = usb_ifnum_to_if(dev, interface);

    if (!iface)
    {
        __err("selecting invalid interface %d", interface);
        return -EINVAL;
    }

    alt = usb_altnum_to_altsetting(iface, alternate);

    if (!alt)
    {
        __err("selecting invalid altsetting %d", alternate);
        return -EINVAL;
    }

    ret = usb_control_msg(dev,
                          usb_sndctrlpipe(dev, 0),
                          USB_REQ_SET_INTERFACE,
                          USB_RECIP_INTERFACE,
                          alternate,
                          interface,
                          NULL,
                          0,
                          5000);

    /* 9.4.10 says devices don't need this and are free to STALL the
     * request if the interface only has one alternate setting.
     */
    if (ret == -EPIPE && iface->num_altsetting == 1)
    {
        __err("manual set_interface for iface %d, alt %d", interface, alternate);
        manual = 1;
    }
    else if (ret < 0)
    {
        return ret;
    }

    /* FIXME drivers shouldn't need to replicate/bugfix the logic here
     * when they implement async or easily-killable versions of this or
     * other "should-be-internal" functions (like clear_halt).
     * should hcd+usbcore postprocess control requests?
     */
    /* prevent submissions using previous endpoint settings */
    usb_disable_interface(dev, iface);
    iface->cur_altsetting = alt;

    /* If the interface only has one altsetting and the device didn't
     * accept the request, we attempt to carry out the equivalent action
     * by manually clearing the HALT feature for each endpoint in the
     * new altsetting.
     */
    if (manual)
    {
        int i = 0;

        for (i = 0; i < alt->desc.bNumEndpoints; i++)
        {
            u32 epaddr = alt->endpoint[i].desc.bEndpointAddress;
            u32 pipe = __create_pipe(dev, USB_ENDPOINT_NUMBER_MASK & epaddr) | (usb_endpoint_out(epaddr) ? USB_DIR_OUT : USB_DIR_IN);
            usb_clear_halt(dev, pipe);
        }
    }

    /* 9.1.1.5: reset toggles for all endpoints in the new altsetting
     *
     * Note:
     * Despite EP0 is always present in all interfaces/AS, the list of
     * endpoints from the descriptor does not contain EP0. Due to its
     * omnipresence one might expect EP0 being considered "affected" by
     * any SetInterface request and hence assume toggles need to be reset.
     * However, EP0 toggles are re-synced for every individual transfer
     * during the SETUP stage - hence EP0 toggles are "don't care" here.
     * (Likewise, EP0 never "halts" on well designed devices.)
     */
    usb_enable_interface(dev, iface);
    return 0;
}


/**
 * usb_disable_interface -- Disable all endpoints for an interface
 * @dev: the device whose interface is being disabled
 * @intf: pointer to the interface descriptor
 *
 * Disables all the endpoints for the interface's current altsetting.
 */
void usb_disable_interface(struct usb_host_virt_dev *dev, struct usb_interface *intf)
{
    struct usb_host_virt_interface *alt = intf->cur_altsetting;
    int i;

    for (i = 0; i < alt->desc.bNumEndpoints; ++i)
    {
        usb_disable_endpoint(dev, alt->endpoint[i].desc.bEndpointAddress);
    }
}



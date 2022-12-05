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
* Date : 2008.05.xx
*
* Description :
*           gen hcd的root hub部分
* History :
********************************************************************************************************************
*/



//#include "usb_host_config.h"

//#include "usb_host_base_types.h"
//#include "usb_os_platform.h"

#include <string.h>
#include <usb_host_common.h>

#include <usb_list.h>
#include <usb_host_hub.h>
#include <usb_utils_find_zero_bit.h>
#include "usb_core_base.h"
#include "usb_msg.h"

#include <sunxi_hal_common.h>

#include "usb_virt_bus.h"
#include <usb_gen_dev_mod.h>
#include "usb_gen_hcd.h"
#include "usb_gen_hub.h"
#include "usb_core_config.h"
#include "urb.h"

#include "usb_gen_hub.h"
#include "usb_core_interface.h"

#include <log.h>
//#include <util.h>

static hal_spinlock_t lock;

/* usb 2.0 root hub device descriptor */
static const u8 usb2_rh_dev_descriptor [18] =
{
    0x12,       /*  __u8  bLength; */
    0x01,       /*  __u8  bDescriptorType; Device */
    0x00, 0x02, /*  __le16 bcdUSB; v2.0 */

    0x09,       /*  __u8  bDeviceClass; HUB_CLASSCODE */
    0x00,       /*  __u8  bDeviceSubClass; */
    0x01,       /*  __u8  bDeviceProtocol; [ usb 2.0 single TT ]*/
    0x08,       /*  __u8  bMaxPacketSize0; 8 Bytes */

    0x00, 0x00, /*  __le16 idVendor; */
    0x00, 0x00, /*  __le16 idProduct; */
    0x00, 0x00, /*  __le16 bcdDevice */

    0x03,       /*  __u8  iManufacturer; */
    0x02,       /*  __u8  iProduct; */
    0x01,       /*  __u8  iSerialNumber; */
    0x01        /*  __u8  bNumConfigurations; */
};

/* no usb 2.0 root hub "device qualifier" descriptor: one speed only */

/* usb 1.1 root hub device descriptor */
static const u8 usb11_rh_dev_descriptor [18] =
{
    0x12,       /*  __u8  bLength; */
    0x01,       /*  __u8  bDescriptorType; Device */
    0x10, 0x01, /*  __le16 bcdUSB; v1.1 */

    0x09,       /*  __u8  bDeviceClass; HUB_CLASSCODE */
    0x00,       /*  __u8  bDeviceSubClass; */
    0x00,       /*  __u8  bDeviceProtocol; [ low/full speeds only ] */
    0x08,       /*  __u8  bMaxPacketSize0; 8 Bytes */

    0x00, 0x00, /*  __le16 idVendor; */
    0x00, 0x00, /*  __le16 idProduct; */
    0x00, 0x00, /*  __le16 bcdDevice */

    0x03,       /*  __u8  iManufacturer; */
    0x02,       /*  __u8  iProduct; */
    0x01,       /*  __u8  iSerialNumber; */
    0x01        /*  __u8  bNumConfigurations; */
};


/* Configuration descriptors for our root hubs */

static const u8 fs_rh_config_descriptor [] =
{

    /* one configuration */
    0x09,       /*  __u8  bLength; */
    0x02,       /*  __u8  bDescriptorType; Configuration */
    0x19, 0x00, /*  __le16 wTotalLength; */
    0x01,       /*  __u8  bNumInterfaces; (1) */
    0x01,       /*  __u8  bConfigurationValue; */
    0x00,       /*  __u8  iConfiguration; */
    0xc0,       /*  __u8  bmAttributes;
                 Bit 7: must be set,
                     6: Self-powered,
                     5: Remote wakeup,
                     4..0: resvd */
    0x00,       /*  __u8  MaxPower; */

    /* USB 1.1:
     * USB 2.0, single TT organization (mandatory):
     *  one interface, protocol 0
     *
     * USB 2.0, multiple TT organization (optional):
     *  two interfaces, protocols 1 (like single TT)
     *  and 2 (multiple TT mode) ... config is
     *  sometimes settable
     *  NOT IMPLEMENTED
     */

    /* one interface */
    0x09,       /*  __u8  if_bLength; */
    0x04,       /*  __u8  if_bDescriptorType; Interface */
    0x00,       /*  __u8  if_bInterfaceNumber; */
    0x00,       /*  __u8  if_bAlternateSetting; */
    0x01,       /*  __u8  if_bNumEndpoints; */
    0x09,       /*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
    0x00,       /*  __u8  if_bInterfaceSubClass; */
    0x00,       /*  __u8  if_bInterfaceProtocol; [usb1.1 or single tt] */
    0x00,       /*  __u8  if_iInterface; */

    /* one endpoint (status change endpoint) */
    0x07,       /*  __u8  ep_bLength; */
    0x05,       /*  __u8  ep_bDescriptorType; Endpoint */
    0x81,       /*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
    0x03,       /*  __u8  ep_bmAttributes; Interrupt */
    0x02, 0x00, /*  __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8) */
    0xff        /*  __u8  ep_bInterval; (255ms -- usb 2.0 spec) */
};

static const u8 hs_rh_config_descriptor [] =
{

    /* one configuration */
    0x09,       /*  __u8  bLength; */
    0x02,       /*  __u8  bDescriptorType; Configuration */
    0x19, 0x00, /*  __le16 wTotalLength; */
    0x01,       /*  __u8  bNumInterfaces; (1) */
    0x01,       /*  __u8  bConfigurationValue; */
    0x00,       /*  __u8  iConfiguration; */
    0xc0,       /*  __u8  bmAttributes;
                 Bit 7: must be set,
                     6: Self-powered,
                     5: Remote wakeup,
                     4..0: resvd */
    0x00,       /*  __u8  MaxPower; */

    /* USB 1.1:
     * USB 2.0, single TT organization (mandatory):
     *  one interface, protocol 0
     *
     * USB 2.0, multiple TT organization (optional):
     *  two interfaces, protocols 1 (like single TT)
     *  and 2 (multiple TT mode) ... config is
     *  sometimes settable
     *  NOT IMPLEMENTED
     */

    /* one interface */
    0x09,       /*  __u8  if_bLength; */
    0x04,       /*  __u8  if_bDescriptorType; Interface */
    0x00,       /*  __u8  if_bInterfaceNumber; */
    0x00,       /*  __u8  if_bAlternateSetting; */
    0x01,       /*  __u8  if_bNumEndpoints; */
    0x09,       /*  __u8  if_bInterfaceClass; HUB_CLASSCODE */
    0x00,       /*  __u8  if_bInterfaceSubClass; */
    0x00,       /*  __u8  if_bInterfaceProtocol; [usb1.1 or single tt] */
    0x00,       /*  __u8  if_iInterface; */

    /* one endpoint (status change endpoint) */
    0x07,       /*  __u8  ep_bLength; */
    0x05,       /*  __u8  ep_bDescriptorType; Endpoint */
    0x81,       /*  __u8  ep_bEndpointAddress; IN Endpoint 1 */
    0x03,       /*  __u8  ep_bmAttributes; Interrupt */
    0x02, 0x00, /*  __le16 ep_wMaxPacketSize; 1 + (MAX_ROOT_PORTS / 8) */
    0x0c        /*  __u8  ep_bInterval; (256ms -- usb 2.0 spec) */
};

/* timer到时处理函数,其实就是直接调用hc_driver的hub_status_data() */
void rh_timer_func(void *timer_para_hcd)
{
    usb_hcd_poll_rh_status((struct hc_gen_dev *) timer_para_hcd);
}

/*
 * Root Hub interrupt transfers are polled using a timer if the
 * driver requests it; otherwise the driver is responsible for
 * calling usb_hcd_poll_rh_status() when an event occurs.
 *
 * Completions are called in_interrupt(), but they may or may not
 * be in_irq().
 */
/*
********************************************************************************
*                     usb_hcd_poll_rh_status
* Description:
*     可以被如下几个用户调用:
*         1，rh hub的timer到时间
*         2，具体的hcd，发现有事件发生
* Arguments:
*     hcd  : input.
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
void usb_hcd_poll_rh_status(struct hc_gen_dev *hcd)
{
    struct urb  *urb;
    int length;
    uint32_t cpu_sr;
    u8  buffer[4];      // Any root hubs with > 31 ports

    if (!hcd->uses_new_polling && !hcd->status_urb)
    {
        hal_log_err("usb_hcd_poll_rh_status() hcd->uses_new_polling = %d ,hcd->status_urb= %d",
                   hcd->uses_new_polling, hcd->status_urb);
        return;
    }

    //--<1>--获得低层hub端口的状态
    length = hcd->driver->hub_status_data(hcd, buffer);

    if (length > 0)
    {
        /* try to complete the status urb */
        cpu_sr = hal_spin_lock_irqsave(&lock);
        urb = hcd->status_urb;

        if (urb)
        {
            if (urb->status == -EINPROGRESS)
            {
                hcd->poll_pending   = 0;
                hcd->status_urb     = NULL;
                urb->status         = 0;
                urb->hcpriv         = NULL;
                urb->actual_length  = length;
                memcpy(urb->transfer_buffer, buffer, length);
            }
            else        // urb has been unlinked
            {
                length = 0;
            }
        }
        else
        {
            length = 0;
        }

        // local irqs are always blocked in completions
        if (length > 0)
        {
            usb_hcd_giveback_urb(hcd, urb);
        }
        else
        {
            hcd->poll_pending = 1;
        }

        hal_spin_unlock_irqrestore(&lock, cpu_sr);
    }

#if 0

    /* The USB 2.0 spec says 256 ms.  This is close enough and won't
     * exceed that limit if HZ is 100. */
    if (hcd->uses_new_polling ? hcd->poll_rh :
        (length == 0 && hcd->status_urb != NULL))
    {
        mod_timer(&hcd->rh_timer, jiffies + msecs_to_jiffies(250));
    }

#endif
}

/*
 * rh_string - provides manufacturer, product and serial strings for root hub
 * @id: the string ID number (1: serial number, 2: product, 3: vendor)
 * @hcd: the host controller for this root hub
 * @type: string describing our driver
 * @data: return packet in UTF-16 LE
 * @len: length of the return packet
 *
 * Produces either a manufacturer, product or serial number string for the
 * virtual root hub device.
 */
static int rh_string(int id, struct hc_gen_dev *hcd, u8 *data, int len)
{
    char buf [100];
    buf[0] = 4;
    buf[1] = 3; /* 4 bytes string data */
    buf[2] = 0x09;
    buf[3] = 0x04;  /* MSFT-speak for "en-us" */
    len = min(len, 4);
    memcpy(data, buf, len);
    return len;
#if 0

    // language ids
    if (id == 0)
    {
        buf[0] = 4;
        buf[1] = 3;  /* 4 bytes string data */
        buf[2] = 0x09;
        buf[3] = 0x04;   /* MSFT-speak for "en-us" */
        len = min(len, 4);
        memcpy(data, buf, len);
        return len;
        // serial number
    }
    else if (id == 1)
    {
        strlcpy(buf, hcd->self.bus_name, sizeof buf);
        // product description
    }
    else if (id == 2)
    {
        strlcpy(buf, hcd->product_desc, sizeof buf);
        // id 3 == vendor description
    }
    else if (id == 3)
    {
        snprintf(buf, sizeof buf, "%s %s %s", system_utsname.sysname,
                 system_utsname.release, hcd->driver->description);
        // unsupported IDs --> "protocol stall"
    }
    else
    {
        return -EPIPE;
    }

    switch (len)        /* All cases fall through */
    {
        default:
            len = 2 + ascii2utf(buf, data + 2, len - 2);

        case 2:
            data [1] = 3;   /* type == string */

        case 1:
            data [0] = 2 * (strlen(buf) + 1);

        case 0:
            ;       /* Compiler wants a statement here */
    }

    return len;
#endif
}

/* 查询rh的status，是通过timer实现，所以这里只mod_timer
   timer到时处理函数rh_timer_func(): */
static int rh_queue_status(struct hc_gen_dev *hcd, struct urb *urb)
{
    int     retval;
    uint32_t cpu_sr;
    int     len = 1 + (urb->dev->maxchild / 8);
    cpu_sr = hal_spin_lock_irqsave(&lock);

    if (urb->status != -EINPROGRESS)    /* already unlinked */
    {
        retval = urb->status;
    }
    else if (hcd->status_urb || urb->transfer_buffer_length < len)
    {
        hal_log_err("not queuing rh status urb\n");
        retval = -EINVAL;
    }
    else
    {
        hcd->status_urb = urb;
        urb->hcpriv = hcd;  /* indicate it's queued */
#if 0

        if (!hcd->uses_new_polling)
        {
            mod_timer(&hcd->rh_timer, jiffies +
                      msecs_to_jiffies(250));
            /* If a status change has already occurred, report it ASAP */
        }
        else if (hcd->poll_pending)
        {
            mod_timer(&hcd->rh_timer, jiffies);
        }

#endif
        retval = 0;
    }

    hal_spin_unlock_irqrestore(&lock, cpu_sr);
    return retval;
}

/* Root hub control transfers execute synchronously */
/* rh的控制 请求，其实直接调用hcd driver->hub_control */
static int rh_call_control(struct hc_gen_dev *hcd, struct urb *urb)
{
    struct usb_ctrlrequest *cmd = NULL;
    u16 typeReq = 0, wValue = 0, wIndex = 0, wLength = 0;
    u8 *ubuf = urb->transfer_buffer;
    u8 tbuf[sizeof(struct usb_hub_descriptor)] __attribute__((aligned(4)));
    const u8 *bufp = tbuf;
    u32 len = 0;
    // u32 patch_wakeup = 0;
    u32 flags = 0;
    uint32_t cpu_sr;
    s32 status = 0;
    s32 n = 0;
    cmd = (struct usb_ctrlrequest *) urb->setup_packet;
    typeReq  = (cmd->bRequestType << 8) | cmd->bRequest;
    wValue   = le16_to_cpu(cmd->wValue);
    wIndex   = le16_to_cpu(cmd->wIndex);
    wLength  = le16_to_cpu(cmd->wLength);

    if (wLength > urb->transfer_buffer_length)
    {
        goto error;
    }

    urb->actual_length = 0;

    switch (typeReq)
    {
        case DeviceRequest | USB_REQ_GET_STATUS:
            tbuf [0] = (hcd->remote_wakeup << USB_DEVICE_REMOTE_WAKEUP) | (1 << USB_DEVICE_SELF_POWERED);
            tbuf [1] = 0;
            len      = 2;
            break;

        case DeviceOutRequest | USB_REQ_CLEAR_FEATURE:
            if (wValue == USB_DEVICE_REMOTE_WAKEUP)
            {
                hcd->remote_wakeup = 0;
            }
            else
            {
                goto error;
            }

            break;

        case DeviceOutRequest | USB_REQ_SET_FEATURE:
            if (hcd->can_wakeup && wValue == USB_DEVICE_REMOTE_WAKEUP)
            {
                hcd->remote_wakeup = 1;
            }
            else
            {
                goto error;
            }

            break;

        case DeviceRequest | USB_REQ_GET_CONFIGURATION:
            tbuf [0] = 1;
            len = 1;
            break;

        case DeviceOutRequest | USB_REQ_SET_CONFIGURATION:
            break;

        case DeviceRequest | USB_REQ_GET_DESCRIPTOR:
            switch (wValue & 0xff00)
            {
                case USB_DT_DEVICE << 8:
                    if (hcd->driver->flags & HC_DRIVER_FLAG_HCD_USB2)
                    {
                        bufp = usb2_rh_dev_descriptor;
                    }
                    else if (hcd->driver->flags & HC_DRIVER_FLAG_HCD_USB11)
                    {
                        bufp = usb11_rh_dev_descriptor;
                    }
                    else
                    {
                        goto error;
                    }

                    len = 18;
                    break;

                case USB_DT_CONFIG << 8:
                    if (hcd->driver->flags & HC_DRIVER_FLAG_HCD_USB2)
                    {
                        bufp = hs_rh_config_descriptor;
                        len = sizeof hs_rh_config_descriptor;
                    }
                    else
                    {
                        bufp = fs_rh_config_descriptor;
                        len = sizeof fs_rh_config_descriptor;
                    }

                    //if (hcd->can_wakeup)
                    //patch_wakeup = 1;
                    break;

                case USB_DT_STRING << 8:
                    n = rh_string(wValue & 0xff, hcd, ubuf, wLength);

                    if (n < 0)
                    {
                        goto error;
                    }

                    urb->actual_length = n;
                    break;

                default:
                    goto error;
            }

            break;

        case DeviceRequest | USB_REQ_GET_INTERFACE:
            tbuf [0] = 0;
            len = 1;
            break;

        /* FALLTHROUGH */
        case DeviceOutRequest | USB_REQ_SET_INTERFACE:
            break;

        case DeviceOutRequest | USB_REQ_SET_ADDRESS:
            // wValue == urb->dev->devaddr
            break;

        /* INTERFACE REQUESTS (no defined feature/status flags) */
        /* ENDPOINT REQUESTS */
        case EndpointRequest | USB_REQ_GET_STATUS:
            // ENDPOINT_HALT flag
            tbuf [0] = 0;
            tbuf [1] = 0;
            len = 2;
            hal_log_info("no endpoint features yet\n");
            break;

        case EndpointOutRequest | USB_REQ_CLEAR_FEATURE:
        case EndpointOutRequest | USB_REQ_SET_FEATURE:
            hal_log_info("no endpoint features yet\n");
            break;

        /* CLASS REQUESTS (and errors) */
        default:

            /* non-generic request */
            if (HC_GEN_DEV_IS_SUSPENDED(hcd->state))
            {
                status = -EAGAIN;
            }
            else
            {
                switch (typeReq)
                {
                    case GetHubStatus:
                    case GetPortStatus:
                        len = 4;
                        break;

                    case GetHubDescriptor:
                        len = sizeof(struct usb_hub_descriptor);
                        break;
                }

                //直接调用具体的hub驱动
        //hal_log_info("-----rh_call_control---1\n");
                status = hcd->driver->hub_control(hcd,
                                                  typeReq,
                                                  wValue,
                                                  wIndex,
                                                  (u8 *)tbuf,
                                                  wLength);
            }

            break;
error:
            /* "protocol stall" on error */
            status = -EPIPE;
    }

    if (status)
    {
        len = 0;

        if (status != -EPIPE)
        {
            hal_log_err("CTRL: TypeReq=0x%x val=0x%x "
                       "idx=0x%x len=%d ==> %d\n",
                       typeReq, wValue, wIndex,
                       wLength, urb->status);
        }
    }

    if (len)
    {
        if (urb->transfer_buffer_length < len)
        {
            len = urb->transfer_buffer_length;
        }

        urb->actual_length = len;
        // always USB_DIR_IN, toward host
        memcpy(ubuf, bufp, len);
        /* report whether RH hardware supports remote wakeup */
#if 0

        if (patch_wakeup &&
            len > offsetof(struct usb_config_descriptor,
                           bmAttributes))
            ((struct usb_config_descriptor *)ubuf)->bmAttributes
            |= USB_CONFIG_ATT_WAKEUP;

#endif
    }

    /* any errors get returned through the urb completion */
    cpu_sr = hal_spin_lock_irqsave(&lock);

    if (urb->status == -EINPROGRESS)
    {
        urb->status = status;
    }

    usb_hcd_giveback_urb(hcd, urb);
    hal_spin_unlock_irqrestore(&lock, cpu_sr);
    return 0;
}

/* root hub的urb enqueue特殊通道, 都是被指向hc_driver的两个rh操作 */
int rh_urb_enqueue(struct hc_gen_dev *hcd, struct urb *urb)
{
    /* 查询rh的status，其实就是开启timer直接查询hc_driver的
       hub_status_data(),获得root_hub的当前状态 */
    //hal_log_info("----rh_urb_ehqueue\n");
    if (usb_pipeint(urb->pipe))
    {
    //hal_log_info("----rh_urb_ehqueue--1\n");
        return rh_queue_status(hcd, urb);
    //hal_log_info("----rh_urb_ehqueue--2\n");
    }

    if (usb_pipecontrol(urb->pipe))
    {
    //hal_log_info("----rh_urb_ehqueue---3\n");
        return rh_call_control(hcd, urb);
    //hal_log_info("----rh_urb_ehqueue--4\n");
    }

    return -EINVAL;
}


/* Asynchronous unlinks of root-hub control URBs are legal, but they
 * don't do anything.  Status URB unlinks must be made in process context
 * with interrupts enabled.
 */
int rh_urb_dequeue(struct hc_gen_dev *hcd, struct urb *urb)
{
    uint32_t sr;
    int     rc;

    rc = usb_hcd_check_unlink_urb(hcd, urb);
    if (rc)
        goto done;

    if (usb_pipeendpoint(urb->pipe) == 0)   /* Control URB */
    {
        /*
                if (in_interrupt())
                    return 0;       //nothing to do
        */
        sr = hal_spin_lock_irqsave(&urb->lock_urb);
        ++urb->reject;
        hal_spin_unlock_irqrestore(&urb->lock_urb, sr);
        /*
                wait_event(usb_kill_urb_queue,
                        atomic_read(&urb->use_count) == 0);
        */
        sr = hal_spin_lock_irqsave(&urb->lock_urb);
        --urb->reject;
        hal_spin_unlock_irqrestore(&urb->lock_urb, sr);
    }
    else                    /* Status URB */
    {
        //      if (!hcd->uses_new_polling){
        //          del_timer_sync (&hcd->rh_timer);
        //      }
        sr = hal_spin_lock_irqsave(&lock);

        if (urb == hcd->status_urb)
        {
            hcd->status_urb = NULL;
            urb->hcpriv = NULL;
        }
        else
        {
            urb = NULL;     /* wasn't fully queued */
        }

        if (urb)
        {
            usb_hcd_giveback_urb(hcd, urb);
        }

        hal_spin_unlock_irqrestore(&lock, sr);
    }

done:
    return rc;
}

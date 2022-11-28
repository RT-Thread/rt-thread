/*
*******************************************************************************
*                                              usb host module                                           *
*                                                                                                                                          *
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.                       *
*                               All Rights Reserved
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
*       usb request block的相关操作，包括分配/释放，发送/撤回
* History :
*******************************************************************************
*/

#include <string.h>

//#include "usb_host_config.h"
#include <usb_os_platform.h>
#include <usb_host_common.h>
//#include "usb_host_base_types.h"
#include <usb_list.h>

#include "usb_gen_hcd.h"

#include <hal_osal.h>

static u32 urb_sn_now = 0;  //

void usb_kill_urb(struct urb *urb);




//用来打印msc_info结构
void _debug_print_urb(struct urb *urb_input)
{
    //__inf(" = %x",urb_input-> );
    __inf("==print_urb=========================");
    __inf("urb addr         = %x", urb_input);
    __inf("lock_urb         = %x", urb_input->lock_urb);
    __inf("wait_urb_timer   = %x", urb_input->wait_urb_timer);
    __inf("hcpriv           = %x", urb_input->hcpriv);
    __inf("bandwidth        = %x", urb_input->bandwidth);
    __inf("use_count        = %x", urb_input->use_count);
    __inf("reject           = %x", urb_input->reject);
    __inf("dev              = %x", urb_input->dev);
    __inf("pipe             = %x", urb_input->pipe);
    __inf("status           = %x", urb_input->status);
    __inf("transfer_flags   = %x", urb_input->transfer_flags);
    __inf("transfer_buffer  = %x", urb_input->transfer_buffer);
    __inf("transfer_dma     = %x", urb_input->transfer_dma);
    __inf("transfer_buffer_length = %x", urb_input->transfer_buffer_length);
    __inf("actual_length    = %x", urb_input->actual_length);
    __inf("setup_packet     = %x", urb_input->setup_packet);
    __inf("setup_dma        = %x", urb_input->setup_dma);
    __inf("start_frame      = %x", urb_input->start_frame);
    __inf("number_of_packets = %x", urb_input->number_of_packets);
    __inf("interval         = %x", urb_input->interval);
    __inf("error_count      = %x", urb_input->error_count);
    __inf("context          = %x", urb_input->context);
    __inf("complete         = %x", urb_input->complete);
    // __inf("wrapper_urb      = %x", urb_input->wrapper_urb);
    __inf("===========================");
}

/*
***********************************************************
*
* Description   :
*               初始化urb
* Arguments  :
*   @urb        :
* Returns       :
*               无
* Notes         :
*
***********************************************************
*/
void usb_init_urb(struct urb *urb)
{
    if (urb == NULL)
    {
        hal_log_err("ERR: urb is NULL");
        return;
    }

    memset(urb, 0, sizeof(struct urb));
}

/*
***********************************************************
*
* Description   :
*               分配urb，并初始化urb
* Arguments  :
*   @urb        :
* Returns       :
*
* Notes         :
*
***********************************************************
*/
struct urb *usb_alloc_urb(int iso_packets)
{
    struct urb *urb;
    urb = (struct urb *)hal_malloc(sizeof(struct urb) + iso_packets * sizeof(struct usb_iso_packet_descriptor));

    if (!urb)
    {
        hal_log_err("alloc_urb: kmalloc failed");
        return NULL;
    }

    usb_init_urb(urb);
    return urb;
}

/*
***********************************************************
*
* Description   :
*               释放urb
* Arguments  :
*   @urb        :
* Returns       :
*
* Notes         :
*
***********************************************************
*/
void usb_free_urb(struct urb *urb)
{
    if (urb)
    {
        hal_free(urb);
        // urb = NULL;
    }
    else
    {
        hal_log_err("ERR: usb_free_urb: urb = NULL");
    }
}

/*
*************************************************************************************
*                     usb_submit_urb
*
* Description:
*     发送urb
*
* Arguments:
*     urb        :  input.  待提交的urb
*     mem_flags  :  input.
*
* Returns:
*     返回命令的执行结果
* note:
*
*************************************************************************************
*/
int usb_submit_urb(struct urb *urb, unsigned mem_flags)
{
    int pipe, temp, max;
    struct usb_host_virt_dev *dev;
    //struct usb_operations *op;
    int is_out;

    //--<1>--check input
    if (!urb)
    {
        hal_log_err("ERR: usb_submit_urb: invalid argment");
        return -EINVAL;
    }

    if (urb->hcpriv || !urb->complete)
    {
        hal_log_err("ERR: usb_submit_urb: urb->hcpriv = 0x%x ,urb->complete = 0x%x input error ",
                   urb->hcpriv, urb->complete);
        return -EINVAL;
    }

    //--<2>--check dev
    dev = urb->dev;

    if (!dev || (dev->state < USB_STATE_DEFAULT) || (!dev->bus) || (dev->devnum < 0))
    {
        hal_log_err("ERR: usb_submit_urb: dev had ben destroied");
        return -ENODEV;
    }

    if (dev->state == USB_STATE_SUSPENDED)
    {
        hal_log_err("ERR: usb_submit_urb: dev had ben destroied");
        return -EHOSTUNREACH;
    }

    //--<3>--构造URB
    urb_sn_now ++;
    urb->urb_sn        = urb_sn_now;
    urb->status        = -EINPROGRESS;
    urb->actual_length = 0;
    urb->bandwidth     = 0;
    /* Lots of sanity checks, so HCDs can rely on clean data
     * and don't need to duplicate tests
     */
    pipe   = urb->pipe;
    temp   = usb_pipetype(pipe);
    is_out = usb_pipeout(pipe);

    if (!usb_pipecontrol(pipe) && dev->state < USB_STATE_CONFIGURED)
    {
        hal_log_err("ERR: usb_submit_urb: USB_STATE_CONFIGURED");
        return -ENODEV;
    }

    /* FIXME there should be a sharable lock protecting us against
     * config/altsetting changes and disconnects, kicking in here.
     * (here == before maxpacket, and eventually endpoint type,
     * checks get made.)
     */
    max = usb_maxpacket(dev, pipe, is_out);

    if (max <= 0)
    {
        hal_log_err("bogus endpoint ep%d%s  (bad maxpacket %d)",
                   usb_pipeendpoint(pipe), is_out ? "out" : "in",
                   max);
        return -EMSGSIZE;
    }

#if 0

    /* periodic transfers limit size per frame/uframe,
     * but drivers only control those sizes for ISO.
     * while we're checking, initialize return status.
     */
    if (temp == PIPE_ISOCHRONOUS)
    {
        int n, len;

        /* "high bandwidth" mode, 1-3 packets/uframe? */
        if (dev->speed == USB_SPEED_HIGH)
        {
            int mult = 1 + ((max >> 11) & 0x03);
            max &= 0x07ff;
            max *= mult;
        }

        if (urb->number_of_packets <= 0)
        {
            return -EINVAL;
        }

        for (n = 0; n < urb->number_of_packets; n++)
        {
            len = urb->iso_frame_desc [n].length;

            if (len < 0 || len > max)
            {
                return -EMSGSIZE;
            }

            urb->iso_frame_desc [n].status = -EXDEV;
            urb->iso_frame_desc [n].actual_length = 0;
        }
    }

#endif

    /* the I/O buffer must be mapped/unmapped, except when length=0 */
    if (urb->transfer_buffer_length < 0)
    {
        hal_log_err("ERR: urb->transfer_buffer_length must not be negative");
        return -EMSGSIZE;
    }

#ifdef DEBUG
    /* stuff that drivers shouldn't do, but which shouldn't
     * cause problems in HCDs if they get it wrong.
     */
    {
        unsigned int    orig_flags = urb->transfer_flags;
        unsigned int    allowed;
        /* enforce simple/standard policy */
        allowed = URB_ASYNC_UNLINK; // affects later unlinks
        allowed |= (URB_NO_TRANSFER_DMA_MAP | URB_NO_SETUP_DMA_MAP);
        allowed |= URB_NO_INTERRUPT;

        switch (temp)
        {
            case PIPE_BULK:
                if (is_out)
                {
                    allowed |= URB_ZERO_PACKET;
                }

            /* FALLTHROUGH */
            case PIPE_CONTROL:
                allowed |= URB_NO_FSBR; /* only affects UHCI */

            /* FALLTHROUGH */
            default:            /* all non-iso endpoints */
                if (!is_out)
                {
                    allowed |= URB_SHORT_NOT_OK;
                }

                break;

            case PIPE_ISOCHRONOUS:
                allowed |= URB_ISO_ASAP;
                break;
        }

        urb->transfer_flags &= allowed;

        /* fail if submitter gave bogus flags */
        if (urb->transfer_flags != orig_flags)
        {
            hal_log_err("PANIC : BOGUS urb flags, %x --> %x",
                       orig_flags, urb->transfer_flags);
            return -EINVAL;
        }
    }
#endif

    /*
     * Force periodic transfer intervals to be legal values that are
     * a power of two (so HCDs don't need to).
     *
     * FIXME want bus->{intr,iso}_sched_horizon values here.  Each HC
     * supports different values... this uses EHCI/UHCI defaults (and
     * EHCI can use smaller non-default values).
     */
    switch (temp)
    {
        case PIPE_ISOCHRONOUS:
        case PIPE_INTERRUPT:

            /* too small? */
            if (urb->interval <= 0)
            {
                hal_log_err("ERR: urb->interval ERROR");
                return -EINVAL;
            }

            /* too big? */
            switch (dev->speed)
            {
                case USB_SPEED_HIGH:    /* units are microframes */

                    // NOTE usb handles 2^15
                    if (urb->interval > (1024 * 8))
                    {
                        urb->interval = 1024 * 8;
                    }

                    temp = 1024 * 8;
                    break;

                case USB_SPEED_FULL:    /* units are frames/msec */
                case USB_SPEED_LOW:
                    if (temp == PIPE_INTERRUPT)
                    {
                        if (urb->interval > 255)
                        {
                            return -EINVAL;
                        }

                        // NOTE ohci only handles up to 32
                        temp = 128;
                    }
                    else
                    {
                        if (urb->interval > 1024)
                        {
                            urb->interval = 1024;
                        }

                        // NOTE usb and ohci handle up to 2^15
                        temp = 1024;
                    }

                    break;

                default:
                    return -EINVAL;
            }

            /* power of two? */
            while (temp > urb->interval)
            {
                temp >>= 1;
            }

            urb->interval = temp;
    }

    return hcd_ops_submit_urb(urb, mem_flags);
}

/*
***********************************************************
*
* Description   :
*               撤回urb
* Arguments  :
*   @urb        :
* Returns       :
*
* Notes         :
*
***********************************************************
*/
int usb_unlink_urb(struct urb *urb)
{
    if (!urb)
    {
        hal_log_err("ERR: usb_unlink_urb: input = NULL");
        return -EINVAL;
    }

    if (!(urb->transfer_flags & URB_ASYNC_UNLINK))
    {
        hal_log_err("ERR: usb_unlink_urb: URB_ASYNC_UNLINK");
        usb_kill_urb(urb);
        return 0;
    }

    return hcd_ops_unlink_urb(urb, -ECONNRESET);
}

/*
***********************************************************
*
* Description   :
*
* Arguments  :
*   @urb        :
* Returns       :
*
* Notes         :
*
***********************************************************
*/
/* 和usb_unlink_urb()的区别 */
void usb_kill_urb(struct urb *urb)
{
    uint32_t flags;

    if (urb == NULL)
    {
        hal_log_err("ERR: usb_kill_urb: input error");
        return;
    }

    flags = hal_spin_lock_irqsave(&urb->lock_urb);
    ++urb->reject;
    hal_spin_unlock_irqrestore(&urb->lock_urb, flags);
    hcd_ops_unlink_urb(urb, -ENOENT);
    flags = hal_spin_lock_irqsave(&urb->lock_urb);
    --urb->reject;
    hal_spin_unlock_irqrestore(&urb->lock_urb, flags);
}


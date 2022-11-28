/*
*******************************************************************************
*                                            sun project ---- usb host module
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
*
* History :
********************************************************************************************************************
*/



//#include "usb_host_config.h"

//#include "usb_host_base_types.h"
//#include "usb_os_platform.h"

#include <string.h>
//#include <usb/usb_list.h>
#include <usb_host_hub.h>
#include <usb_utils_find_zero_bit.h>
#include "usb_core_base.h"
#include "usb_msg.h"
#include <usb_gen_dev_mod.h>

#include "usb_virt_bus.h"
#include "usb_gen_hcd.h"
#include "usb_gen_hub.h"
#include "usb_core_config.h"
#include "urb.h"

#include "usb_gen_hub.h"
#include "usb_core_interface.h"
#include "usb_gen_hcd_rh.h"
#include "aw_list.h"

#include <usb.h>
//#include <atomic.h>
#include <hal_osal.h>

hal_spinlock_t gen_hcd_lock;
//static USB_OS_KERNEL_EVENT *usb_bus_list_lock;  //用来保护usb virt bus的，虽然目前用不到
hal_sem_t   usb_bus_list_lock;  //用来保护usb virt bus的，虽然目前用不到
//但是当我们支持多个物理hcd的时候必须用

/*
 * usb_hcd_start_port_resume - a root-hub port is sending a resume signal
 */
void usb_hcd_start_port_resume(struct usb_virt_bus *bus, int portnum)
{
    unsigned bit = 1 << portnum;

    if (!(bus->resuming_ports & bit)) {
        bus->resuming_ports |= bit;
        //pm_runtime_get_noresume(&bus->root_hub->dev);
    }
}

/*
 * usb_hcd_end_port_resume - a root-hub port has stop sending a resume signal
 */
void usb_hcd_end_port_resume(struct usb_virt_bus *bus, int portnum)
{
    unsigned bit = 1 << portnum;

    if (bus->resuming_ports & bit) {
        bus->resuming_ports &= ~bit;
        //pm_runtime_put_noidle(&bus->root_hub->dev);
    }
}

/**
 * usb_release_bandwidth - reverses effect of usb_claim_bandwidth()
 * @dev: source/target of request
 * @urb: request (urb->dev == dev)
 * @isoc: true iff the request is isochronous
 *
 * This records that previously allocated bandwidth has been released.
 * Bandwidth is released when endpoints are removed from the host controller's
 * periodic schedule.
 */
/*
********************************************************************************
*                     usb_release_bandwidth
* Description:
*     释放带宽
* Arguments:
*     hcd       : input.
*     hep       : input.
*     urb       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void usb_release_bandwidth(struct usb_host_virt_dev *dev, struct urb *urb, int isoc)
{
    dev->bus->bandwidth_allocated -= urb->bandwidth;

    if (isoc)
    {
        dev->bus->bandwidth_isoc_reqs--;
    }
    else
    {
        dev->bus->bandwidth_int_reqs--;
    }

    urb->bandwidth = 0;
}

/*
********************************************************************************
*                     usb_release_bandwidth
* Description:
*     把urb 从list中摘出来, 但是没有callback
* Arguments:
*     hcd       : input.
*     hep       : input.
*     urb       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
static void urb_unlink(struct urb *urb)
{
    uint32_t sr = 0;

    /* Release any periodic transfer bandwidth */
    if (urb->bandwidth)
    {
        usb_release_bandwidth(urb->dev, urb, usb_pipeisoc(urb->pipe));
    }

    /* clear all state linking urb to this dev (and hcd) */
    sr = hal_spin_lock_irqsave(&gen_hcd_lock);
    list_del_init(&(urb->urb_list));
    hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
    return;
}

/*-------------------------------------------------------------------------*/

/**
 * usb_hcd_giveback_urb - return URB from HCD to device driver
 * @hcd: host controller returning the URB
 * @urb: urb being returned to the USB device driver.
 * @regs: pt_regs, passed down to the URB completion handler
 * Context: in_interrupt()
 *
 * This hands the URB from HCD to its USB device driver, using its
 * completion function.  The HCD has freed all per-urb resources
 * (and is done using urb->hcpriv).  It also released all HCD locks;
 * the device driver won't cause problems if it frees, modifies,
 * or resubmits this URB.
 */
/*
********************************************************************************
*                     usb_hcd_giveback_urb
* Description:
*     urb callback函数, 这里只是把urb从list里面摘出来,并且callback, 后面的事交给
* device driver处理
* Arguments:
*     hcd       : input. host controller
*     urb       : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void usb_hcd_giveback_urb(struct hc_gen_dev *hcd, struct urb *urb)
{
    if (likely(!urb->unlinked))
        urb->unlinked = urb->status;

    //int at_root_hub;
    //at_root_hub = (urb->dev == hcd->self.root_hub);
    urb_unlink(urb);
    /* lower level hcd code should use *_dma exclusively
    if (hcd->self.controller->dma_mask && !at_root_hub) {
        if (usb_pipecontrol (urb->pipe)
            && !(urb->transfer_flags & URB_NO_SETUP_DMA_MAP))
            dma_unmap_single (hcd->self.controller, urb->setup_dma,
                    sizeof (struct usb_ctrlrequest),
                    DMA_TO_DEVICE);
        if (urb->transfer_buffer_length != 0
            && !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP))
            dma_unmap_single (hcd->self.controller,
                    urb->transfer_dma,
                    urb->transfer_buffer_length,
                    usb_pipein (urb->pipe)
                        ? DMA_FROM_DEVICE
                        : DMA_TO_DEVICE);
    }
    */
    urb->complete(urb); //如果是rh 的status urb ,这个时候的use_count = 2
    //见hub_status_req_complete()
    // _urb_done_complete_callback

    usb_dec32((&urb->use_count));

    if (urb->reject)
    {
        hal_log_err("PANIC : usb_hcd_giveback_urb: submissions will fail");
        //wake_up (&usb_kill_urb_queue);
    }

    /*不能在这里就将urb了解了 ，
    //这么做非常不明智，所以由urb的申请者去处理它的归宿:)
        //当没有人使用的时候才
        if(urb->use_count == 0){
            usb_free_urb (urb);
        }else{
            hal_log_err("=====usb_hcd_giveback_urb()...urb->use_count = %d != 0,maybe roothub status urb",urb->use_count);
        }
    */
    return;
}

/*
********************************************************************************
*                     usb_bus_init
* Description:
*     内部函数--只是初始化usb_bus结构
* Arguments:
*     hcd       : input.
*     hep       : input.
*     urb       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
static void usb_bus_init(struct usb_virt_bus *bus)
{
    memset(&bus->devmap, 0, sizeof(struct usb_devmap));

    bus->devnum_next            = 1;
    bus->root_hub               = NULL;
    bus->hcpriv                 = NULL;
    bus->busnum                 = -1;
    bus->bandwidth_allocated    = 0;
    bus->bandwidth_int_reqs     = 0;
    bus->bandwidth_isoc_reqs    = 0;
    //INIT_LIST_HEAD (&bus->bus_list);
}


/* this makes the hcd giveback() the urb more quickly, by kicking it
 * off hardware queues (which may take a while) and returning it as
 * soon as practical.  we've already set up the urb's return status,
 * but we can't know if the callback completed already.
 */
/*
********************************************************************************
*                     unlink1
* Description:
*     快速删除urb, 并且callback
* Arguments:
*     hcd       : input. host controller device
*     urb       : input. 请求被删除的urb
* Return value:
*     void
* note:
*
*********************************************************************************
*/
static int unlink1(struct hc_gen_dev *hcd, struct urb *urb)
{
    int     value;

    //--<1>--roothub的urb就让roothub自己处理
    if (urb->dev == hcd->self.root_hub)
    {
        value = rh_urb_dequeue(hcd, urb);
    }
    else
    {
        //--<2>--其他的urb就dequeue
        /* The only reason an HCD might fail this call is if
         * it has not yet fully queued the urb to begin with.
         * Such failures should be harmless. */
        value = hcd->driver->urb_dequeue(hcd, urb);
    }

    if (value != 0)
    {
        hal_log_err("dequeue failed, %p --> %d", urb, value);
    }

    return value;
}


/*
********************************************************************************
*                     usb_hc_died
* Description:
*
* Arguments:
*     hcd       : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void usb_hc_died(struct hc_gen_dev *hcd)
{
    uint32_t sr = 0;
    int ret = 0;
    hal_log_err("PANIC : hc_gen_dev died; cleaning up");
    sr = hal_spin_lock_irqsave(&gen_hcd_lock);

    if (hcd->rh_registered)
    {
        hcd->poll_rh = 0;
        //ret = USB_esKRNL_TmrStop(hcd->rh_timer);
        ret = osal_timer_stop(hcd->rh_timer);

        if (ret)
        {
            hal_log_err("PANIC : usb_hc_died, timer stop error code = %x", ret);
            return ;
        }

        ret = osal_timer_delete(hcd->rh_timer);

        if (ret)
        {
            hal_log_err("PANIC : usb_hc_died, timer delete error code = %x", ret);
            return ;
        }

        /* make khubd clean up old urbs and devices */
        usb_set_device_state(hcd->self.root_hub, USB_STATE_NOTATTACHED);
        hal_log_err("PANIC : need to modify,");
        //      usb_kick_khubd (hcd->self.root_hub);
        //      kick_khubd
    }

    hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
}

/**
 * register_root_hub - called by usb_add_hcd() to register a root hub
 * @usb_dev: the usb root hub device to be registered.
 * @hcd: host controller for this root hub
 *
 * This function registers the root hub with the USB subsystem.  It sets up
 * the device properly in the device tree and stores the root_hub pointer
 * in the bus structure, then calls usb_new_device() to register the usb
 * device.  It also assigns the root hub's USB address (always 1).
 */
/*
********************************************************************************
*                     register_root_hub
* Description:
*     注册root hub dev, root hub's USB address (always 1).
* Arguments:
*     hcd      : input.
*     usb_dev  : input.
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
static int _register_root_hub(struct usb_host_virt_dev *usb_dev,
                              struct hc_gen_dev  *hcd)
{
    uint32_t sr = 0;
    u8 err = 0;
    const int devnum = 1;
    int retval = 0;
    //--<1>--初始化virt_dev
    usb_dev->devnum = devnum;
    usb_dev->bus->devnum_next = devnum + 1;
    memset(&usb_dev->bus->devmap.devicemap, 0, sizeof(struct usb_devmap));
    usb_set_bit(devnum, usb_dev->bus->devmap.devicemap);
    usb_set_device_state(usb_dev, USB_STATE_ADDRESS);

    hal_sem_wait(usb_bus_list_lock);
    usb_dev->bus->root_hub = usb_dev;
    usb_dev->ep0.desc.wMaxPacketSize = 64;
    //--<2>--获得rh设备描述符
    retval = usb_get_device_descriptor(usb_dev, USB_DT_DEVICE_SIZE);

    if (retval != sizeof usb_dev->descriptor)
    {
        usb_dev->bus->root_hub = NULL;
        //used when update list of hcds
        hal_sem_post(usb_bus_list_lock);
        hal_log_err("can't read %s device descriptor %d", usb_dev->bus->bus_name, retval);
        return (retval < 0) ? retval : -EMSGSIZE;
    }

    //--<3>--创建新设备
    usb_lock_device(usb_dev);
    retval = usb_new_device(usb_dev);
    usb_unlock_device(usb_dev);

    if (retval)
    {
        usb_dev->bus->root_hub = NULL;
        hal_log_err("PANIC : can't register root hub for %s, %d",
            usb_dev->bus->bus_name, retval);
    }

    hal_sem_post(usb_bus_list_lock);

    if (retval == 0)
    {
        sr = hal_spin_lock_irqsave(&gen_hcd_lock);
        hcd->rh_registered = 1;
        hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);

        /* Did the HC die before the root hub was registered? */
        if (hcd->state == HC_GEN_DEV_STATE_HALT)
        {
            usb_hc_died(hcd);    /* This time clean up */
        }
    }

    return retval;
}

/*
********************************************************************************
*                     usb_create_hc_gen_dev
* Description:
*     创建，并初始化usb_hcd
* Arguments:
*     driver    : input.
*     bus_name  : input.
* Return value:
*     void
* note:
*     void
*********************************************************************************
*/
struct hc_gen_dev *usb_create_hc_gen_dev(const struct hc_driver *driver, const char *bus_name)
{
    struct hc_gen_dev *hcd;
    u8 ret = 0;

    //--<1>--初始化host controller device
    //hcd = kzalloc(sizeof(*hcd) + driver->hcd_priv_size, GFP_KERNEL);
    hcd = malloc(sizeof(*hcd) + driver->hcd_priv_size);
    if (!hcd)
    {
        hal_log_err("usb_create_hc_gen_dev alloc failed");
        return NULL;
    }

    memset(hcd, 0, sizeof(*hcd) + driver->hcd_priv_size);
    usb_bus_init(&hcd->self);
    hcd->self.hcpriv        = hcd;
    hcd->self.bus_name      = bus_name;
    hcd->self.point_gen_hcd = hcd;
    //*****************************
    //创建root hub poll的timer
    //*****************************
    //--<2>--create and start timer
    //USB_HOST_RH_TIMEROUT = 10000, 5s
    //hcd->rh_timer = OS_TimerCreate(USB_HOST_RH_TIMEROUT,
    //              USB_TIMER_PERIOD_MORE,
    //              (USB_TIMER_CALLBACK)rh_timer_func,
    //              (void *)hcd);
    /*500ms*/
    //OS_TimerCreate(hcd->rh_timer, OS_TIMER_PERIODIC, rh_timer_func, hcd, 500);
    hcd->rh_timer = osal_timer_create("hcd_timer", rh_timer_func, (void*)hcd,
                    500, OSAL_TIMER_FLAG_PERIODIC);

    if (hcd->rh_timer == NULL)
    {
        hal_log_err("PANIC : create timer fail");
        return NULL;
    }

    ret = osal_timer_start(hcd->rh_timer);

    if (ret)
    {
        // it need to add
        hal_log_err("PANIC : start timer failI.\n");
        osal_timer_delete(hcd->rh_timer);
        return NULL;
    }

    //--<3>--匹配hcd设备的驱动
    hcd->driver         = driver;
    hcd->product_desc   = (driver->product_desc) ? driver->product_desc : "USB Host Controller";
    return hcd;
}

/*
********************************************************************************
*                     usb_add_hc_gen_dev
* Description:
*     添加一个新设备到总线上, 分配buff,并向usb总线注册rh
* Arguments:
*     hcd       : input.
*     irqnum    : input.
*     irqflags  : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
s32 usb_add_hc_gen_dev(struct hc_gen_dev *hcd, u32  irqnum, u32 irqflags)
{
    int retval = 0;
    struct usb_host_virt_dev  *rh_dev = NULL;
    hal_log_info("[usbh core]: add gen_dev %s\n", hcd->product_desc);

    //call drv reset
    if (hcd->driver->reset && (retval = hcd->driver->reset(hcd)) < 0)
    {
        hal_log_err("PANIC : usb_add_hc_gen_dev() :  can't reset");
        return retval;
    }
    hal_log_info("----2--usb_add_hc_gen_dev\n");

    /*version 1, we consider only one host*/

    //--<1>--为rh 创建一个usb_device结构
    rh_dev = usb_host_alloc_virt_dev(NULL, &hcd->self, 0);
    if (rh_dev == NULL)
    {
        hal_log_err("PANIC : usb_add_hc_gen_dev() : unable to allocate root hub");
        retval = -ENOMEM;
        return retval;
    }

    hal_log_info("----3--usb_add_hc_gen_dev\n");
    //--<2>--此hcd设备支持的速度
    rh_dev->speed = (hcd->driver->flags & HC_DRIVER_FLAG_HCD_USB2) ? USB_SPEED_HIGH : USB_SPEED_FULL;

    //--<3>--start这个设备
    if ((retval = hcd->driver->start(hcd)) < 0)
    {
        hal_log_err("PANIC : usb_add_hc_gen_dev() :startup error %d", retval);
        goto err_hcd_driver_start;
    }

    hal_log_info("----4--usb_add_hc_gen_dev\n");
    /* hcd->driver->start() reported can_wakeup, probably with
     * assistance from board's boot firmware.
     * NOTE:  normal devices won't enable wakeup by default.
     */
    if (hcd->can_wakeup)
    {
        hal_log_info("supports USB remote wakeup");
    }

    hcd->remote_wakeup = hcd->can_wakeup;

    hal_log_info("hcd->remote_wakeup=%d\n", hcd->remote_wakeup);

    hal_log_info("----5--usb_add_hc_gen_dev\n");
    //--<4>--注册root hub, 即添加一个usb_host_virt_dev
    //linux-4.9 register_root_hub(hcd)
    if ((retval = _register_root_hub(rh_dev, hcd)) != 0)
    {
        hal_log_err("PANIC : can not register root hub :(");
        goto err_register_root_hub;
    }

    //--<5>--
    if (hcd->uses_new_polling && hcd->poll_rh)
    {
        usb_hcd_poll_rh_status(hcd);
    }

    hal_log_info("----6--usb_add_hc_gen_dev\n");
    return retval;
err_register_root_hub:
    hcd->driver->stop(hcd);
err_hcd_driver_start:
    usb_host_free_virt_dev(rh_dev);
    rh_dev = NULL;
    return retval;
}

/**
 * usb_remove_hcd - shutdown processing for generic HCDs
 * @hcd: the usb_hcd structure to remove
 * Context: !in_interrupt()
 *
 * Disconnects the root hub, then reverses the effects of usb_add_hcd(),
 * invoking the HCD's stop() method.
 */
/*
********************************************************************************
*                     usb_remove_hc_gen_dev
* Description:
*     删除hcd设备
* Arguments:
*     hcd       : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void usb_remove_hc_gen_dev(struct hc_gen_dev *hcd)
{
    uint32_t sr = 0;
    s32 ret = 0;

    if (hcd == NULL)
    {
        hal_log_err("ERR: invalid argment");
        return ;
    }

    if (HC_GEN_DEV_IS_RUNNING(hcd->state))
    {
        hcd->state = HC_GEN_DEV_STATE_QUIESCING;
    }

    sr = hal_spin_lock_irqsave(&gen_hcd_lock);
    hcd->rh_registered = 0;
    hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
    //--<1>--断开这个设备
    usb_disconnect(&hcd->self.root_hub);
    hcd->poll_rh = 0;
    //--<2>--停止并且删除timer
    sr =  hal_spin_lock_irqsave(&gen_hcd_lock);
    ret = osal_timer_stop(hcd->rh_timer);

    if (ret)
    {
        hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
        hal_log_err("PANIC : usb_hc_died, timer stop error code = %x\n", ret);
        return ;
    }

    ret = osal_timer_delete(hcd->rh_timer);

    if (ret)
    {
        hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
        hal_log_err("PANIC : usb_hc_died, timer del error code = %x\n", ret);
        return ;
    }

    hal_spin_unlock_irqrestore(&gen_hcd_lock, sr);
    //--<3>--停止hcd设备
    hcd->driver->stop(hcd);
    hcd->state = HC_GEN_DEV_STATE_HALT;

    //--<4>--释放这个设备所有的资源
    if (hcd->self.root_hub)
    {
        usb_host_free_virt_dev(hcd->self.root_hub);
        hcd->self.root_hub = NULL;
    }

    //free self
    free(hcd);
    // hcd = NULL;
    return ;
}

/*
********************************************************************************
*                     usb_remove_hc_gen_dev
* Description:
*     hcd的抽象ops
* Arguments:
*     hcd       : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
int hcd_ops_get_frame_number(struct usb_host_virt_dev *udev)
{
    struct hc_gen_dev   *hcd = (struct hc_gen_dev *)udev->bus->hcpriv;

    if (!HC_GEN_DEV_IS_RUNNING(hcd->state))
    {
        return -ESHUTDOWN;
    }

    return hcd->driver->get_frame_number(hcd);
}

/* may be called in any context with a valid urb->dev usecount
 * caller surrenders "ownership" of urb
 * expects usb_submit_urb() to have sanity checked and conditioned all
 * inputs in the urb
 */
/*
********************************************************************************
*                     hcd_ops_submit_urb
* Description:
*     提交urb, hcd的抽象ops。其实就是为了区分发往的目的地:
*                         1，rh，则走特殊通道
*                         2，物理device,走正规渠道
* Arguments:
*     urb       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
int hcd_ops_submit_urb(struct urb *urb, unsigned mem_flags)
{
    struct hc_gen_dev *hcd = NULL;
    struct usb_host_virt_endpoint *ep = NULL;
    uint32_t cpu_sr = 0;
    int status = 0;

    if (!urb || !urb->dev || !urb->dev->bus || !urb->dev->bus->hcpriv)
    {
        hal_log_err("PANIC : hcd_ops_submit_urb() : input NULL");
        return -ENODEV;
    }

    //--<1>--通过urb找到hcd
    hcd = urb->dev->bus->hcpriv;
    /*
     * Atomically queue the urb,  first to our records, then to the HCD.
     * Access to urb->status is controlled by urb->lock ... changes on
     * i/o completion (normal or fault) or unlinking.
     */
    // FIXME:  verify that quiescing hc works right (RH cleans up)
    //--<2>--通过urb找到ep
    cpu_sr = hal_spin_lock_irqsave(&gen_hcd_lock);
    ep = (usb_pipein(urb->pipe) ? urb->dev->ep_in : urb->dev->ep_out)[usb_pipeendpoint(urb->pipe)];

    if (!ep)
    {
        hal_log_err("ERR: ep = NULL");
        status = -ENOENT;
    }
    else if (urb->reject)
    {
        hal_log_err("ERR: urb->reject must be zero");
        status = -EPERM;
    }
    else
    {
        switch (hcd->state)
        {
            case HC_GEN_DEV_STATE_RUNNING:
            case HC_GEN_DEV_STATE_RESUMING:
            {
                //--<3>--添加到urb_list
                INIT_LIST_HEAD(&(urb->urb_list));
                urb->unlinked = 0;
                list_add_tail(&(urb->urb_list), &(ep->urb_list));

                status = 0;
            }
            break;

            default:
                hal_log_err("ERR: unkown hcd->state(0x%x)", hcd->state);
                status = -ESHUTDOWN;
                break;
        }
    }

    hal_spin_unlock_irqrestore(&gen_hcd_lock, cpu_sr);

    if (status)
    {
        hal_log_err("ERR: status failed");
        INIT_LIST_HEAD(&(urb->urb_list));
        //usbmon_urb_submit_error(&hcd->self, urb, status);
        return status;
    }

    /* increment urb's reference count as part of giving it to the HCD
     * (which now controls it).  HCD guarantees that it either returns
     * an error or calls giveback(), but not both.
     */
    usb_inc32(&urb->use_count);

    urb->ep = ep;

    //--<4>--目标设备为rh
    if (urb->dev == hcd->self.root_hub)
    {
        /* NOTE:  requirement on hub callers (usbfs and the hub
         * driver, for now) that URBs' urb->transfer_buffer be
         * valid and usb_buffer_{sync,unmap}() not be needed, since
         * they could clobber root hub response data.
         */
        status = rh_urb_enqueue(hcd, urb);
        goto done;
    }

    /* lower level hcd code should use *_dma exclusively,
     * unless it uses pio or talks to another transport.
     */

    if (usb_pipecontrol(urb->pipe)
                && !(urb->transfer_flags & URB_NO_SETUP_DMA_MAP))
            urb->setup_dma = __va_to_pa((unsigned long)urb->setup_packet);

    if (urb->transfer_buffer_length != 0
                && !(urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP))
            urb->transfer_dma = __va_to_pa((unsigned long)urb->transfer_buffer);

    //--<5>--物理外设
    //status = hcd->driver->urb_enqueue(hcd, ep, urb, mem_flags);
    status = hcd->driver->urb_enqueue(hcd, urb, mem_flags);
done:

    if (status)
    {
        hal_log_err("PANIC : [ gen hcd ] hcd_ops_submit_urb()...2...call real hcd fail");
        urb_unlink(urb);
        usb_dec32(&urb->use_count);
#if 0

        if (urb->reject)
        {
            wake_up(&usb_kill_urb_queue);
        }

#endif
        //这个做法不合理，不能释放，这个urb是别人的。
        //usb_free_urb (urb);
    }

    return status;
}


/*
 * called in any context
 *
 * caller guarantees urb won't be recycled till both unlink()
 * and the urb's completion function return
 */
/*
********************************************************************************
*                     hcd_ops_unlink_urb
* Description:
*     hcd的抽象ops
* Arguments:
*     urb       : input.
*     status    : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
int hcd_ops_unlink_urb(struct urb *urb, int status)
{
    struct usb_host_virt_endpoint   *ep = NULL;
    struct hc_gen_dev               *hcd = NULL;
    struct list_head            *tmp;
    s32  retval = 0;
    uint32_t sr;

    if (!urb)
    {
        hal_log_err("ERR: urb is NULL");
        return -EINVAL;
    }

    if (!urb->dev)
    {
        hal_log_err("ERR: urb dev is invalid");
        return -ENODEV;
    }

    if (!urb->dev->bus)
    {
        hal_log_err("ERR: urb bus is invalid");
        return -ENODEV;
    }

    //--<1>--通过urb找到ep
     ep = (usb_pipein(urb->pipe) ? urb->dev->ep_in : urb->dev->ep_out)[usb_pipeendpoint(urb->pipe)];

     if (!ep)
     {
        hal_log_err("ERR: ep is invalid");
        return -ENODEV;
     }


    /*
     * we contend for urb->status with the hcd core,
     * which changes it while returning the urb.
     *
     * Caller guaranteed that the urb pointer hasn't been freed, and
     * that it was submitted.  But as a rule it can't know whether or
     * not it's already been unlinked ... so we respect the reversed
     * lock sequence needed for the usb_hcd_giveback_urb() code paths
     * (urb lock, then hcd_data_lock) in case some other CPU is now
     * unlinking it.
     */
    sr = hal_spin_lock_irqsave(&urb->lock_urb);
    //--<1>--通过urb找到hcd
    hcd = urb->dev->bus->hcpriv;

    if (hcd == NULL)
    {
        hal_log_err("ERR: hcd is invalid");
        retval = -ENODEV;
        goto done;
    }

    /* running ~= hc unlink handshake works (irq, timer, etc)
     * halted ~= no unlink handshake is needed
     * suspended, resuming == should never happen
     */
    if (!HC_GEN_DEV_IS_RUNNING(hcd->state) && hcd->state != HC_GEN_DEV_STATE_HALT)
    {
        hal_log_err("PANIC : hcd_ops_unlink_urb() fail");
    }

    // insist the urb is still queued
    list_for_each(tmp, &(ep->urb_list))
    {
        if (tmp == &(urb->urb_list))
            break;
    }

    if (tmp != &(urb->urb_list))
    {
        hal_log_err("PANIC : hcd_ops_unlink_urb() not in ep->urb_list");
        retval = -EIDRM;
        goto done;
    }

    /* Any status except -EINPROGRESS means something already started to
     * unlink this URB from the hardware.  So there's no more work to do.
     */
    if (urb->status != -EINPROGRESS)
    {
        retval = -EBUSY;
        goto done;
    }

    /* IRQ setup can easily be broken so that USB controllers
     * never get completion IRQs ... maybe even the ones we need to
     * finish unlinking the initial failed usb_set_address()
     * or device descriptor fetch.
     */
    if (!hcd->saw_irq && hcd->self.root_hub != urb->dev)
    {
        hal_log_err("WRN: Unlink after no-IRQ?  "
                   "Controller is probably using the wrong IRQ."
                   "");
        hal_log_err("WRN: saw_irq = %d, root_hub = %x, dev = %x",
                   hcd->saw_irq, hcd->self.root_hub, urb->dev);
        hcd->saw_irq = 1;
    }

    urb->status = status;
    hal_spin_unlock_irqrestore(&urb->lock_urb, sr);
    retval = unlink1(hcd, urb);

    if (retval == 0)
    {
        hal_log_err("wrn: urb is dispose, but hcd_ops_unlink_urb happen");
        retval = -EINPROGRESS;
    }

    return retval;
done:
    hal_spin_unlock_irqrestore(&urb->lock_urb, sr);
    return retval;
}
/* sometimes alloc/free could use kmalloc with SLAB_DMA, for
 * better sharing and to leverage mm/slab.c intelligence.
 */
/*
********************************************************************************
*                     hcd_ops_buffer_alloc
* Description:
*     申请连续的物理内存
* Arguments:
*     hcd       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
#define USB_OS_PAGE_MALLOC_PAGE_SIZE 1024
void *hcd_ops_buffer_alloc(struct usb_virt_bus *bus,
                           u32 size,
                           u32 mem_flags,
                           u32 *dma)
{
    void *addr = 0;
    // int real_want_page = (size + USB_OS_PAGE_MALLOC_PAGE_SIZE - 1) / USB_OS_PAGE_MALLOC_PAGE_SIZE;
    addr = hal_malloc(size);

    if (dma)
    {
        *dma = 0;
    }

    return addr;
}

/*
********************************************************************************
*                     hcd_ops_buffer_free
* Description:
*     释放申请的物理内存
* Arguments:
*     hcd       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void hcd_ops_buffer_free(struct usb_virt_bus *bus,
                         u32 size,
                         u32 *addr,
                         u32 *dma)

{
    //    u32 real_free_pages  = (size + USB_OS_PAGE_MALLOC_PAGE_SIZE - 1) / USB_OS_PAGE_MALLOC_PAGE_SIZE;
    hal_free(addr);

    if (dma)
    {
        *dma = 0;
    }
}

/*-------------------------------------------------------------------------*/

/* disables the endpoint: cancels any pending urbs, then synchronizes with
 * the hcd to make sure all endpoint state is gone from hardware. use for
 * set_configuration, set_interface, driver removal, physical disconnect.
 *
 * example:  a qh stored in ep->hcpriv, holding state related to endpoint
 * type, maxpacket size, toggle, halt status, and scheduling.
 */
/*
********************************************************************************
*                     hcd_ops_endpoint_disable
* Description:
*     hcd的抽象ops
* Arguments:
*     hcd       : input.
*     mem_flags : input.
* Return value:
*     void
* note:
*
*********************************************************************************
*/
void hcd_ops_endpoint_disable(struct usb_host_virt_dev *udev, struct usb_host_virt_endpoint *ep)
{
    struct hc_gen_dev *hcd          = NULL;
    struct urb *urb                 = NULL;
    struct list_head *list_start   = NULL;
    struct list_head *list_now     = NULL;
    uint32_t cpu_sr = 0;

    if (udev == NULL || (udev->bus == NULL) || ep == NULL)
    {
        hal_log_err("PANIC : hcd_ops_endpoint_disable() :input :udev = %x ,bus = %x ,ep  == %x ",
                   udev, udev ? (udev->bus) : (0), ep);
        return ;
    }

    hcd = udev->bus->hcpriv;

    if (!HC_GEN_DEV_IS_RUNNING(hcd->state) && hcd->state != HC_GEN_DEV_STATE_HALT &&
        udev->state != USB_STATE_NOTATTACHED)
    {
        hal_log_err("PANIC : hcd_ops_endpoint_disable() : error state");
        return ;
    }

    /* FIXME move most of this into message.c as part of its
     * endpoint disable logic
     */
    /* ep is already gone from udev->ep_{in,out}[]; no more submits */
    cpu_sr = hal_spin_lock_irqsave(&gen_hcd_lock);
rescan:
    list_start = &(ep->urb_list);
    list_now = list_start->next;

    while (list_now != list_start)
    {
        int tmp = 0;
        // urb = (struct urb *)(list_now->data);
        urb = container_of(list_now, struct urb, urb_list);

        if (!urb)
        {
            hal_log_err("PANIC : hcd_ops_endpoint_disable() : urb = NULL");
            list_now = list_now->next;
            continue;
        }

        /* another cpu may be in hcd, spinning on hcd_data_lock
         * to giveback() this urb.  the races here should be
         * small, but a full fix needs a new "can't submit"
         * urb state.
         * FIXME urb->reject should allow that...
         */
        if (urb->status != -EINPROGRESS)
        {
            list_now = list_now->next;
            continue;
        }

        tmp = urb->status;

        if (tmp == -EINPROGRESS)
        {
            urb->status = -ESHUTDOWN;
        }

        /* kick hcd unless it's already returning this */
        if (tmp == -EINPROGRESS)
        {
            tmp = urb->pipe;
            unlink1(hcd, urb);
        }

        /* list contents may have changed */
        list_now = list_now->next;
        goto rescan;
    }

    hal_spin_unlock_irqrestore(&gen_hcd_lock, cpu_sr);

    /* synchronize with the hardware, so old configuration state
     * clears out immediately (and will be freed).
     */

    if (hcd->driver->endpoint_disable)
    {
        hcd->driver->endpoint_disable(hcd, ep);
    }
}

/*
void hcd_ops_endpoint_disable (struct usb_host_virt_dev *udev, struct usb_host_virt_endpoint *ep)
{
    struct hc_gen_dev       *hcd;
    struct urb      *urb;
    struct list_head * list_start = NULL;
    struct list_head * list_now = NULL;

    u32 flags;

    if( udev == NULL || (udev->bus == NULL)|| ep == NULL){
        hal_log_err("PANIC : hcd_ops_endpoint_disable() :input :udev = %x ,bus = %x ,ep  == %x ",
                     udev ,udev ? (udev->bus) : (0) , ep);
        return ;
    }
    hcd = udev->bus->hcpriv;
    if (!HC_GEN_DEV_IS_RUNNING (hcd->state) && hcd->state != HC_GEN_DEV_STATE_HALT &&
            udev->state != USB_STATE_NOTATTACHED){
        hal_log_err("PANIC : hcd_ops_endpoint_disable() : error state");
        return ;
    }


    // FIXME move most of this into message.c as part of its
    //endpoint disable logic


    // ep is already gone from udev->ep_{in,out}[]; no more submits //
rescan:
    hal_spin_lock_irqsave(flags);

    list_start = & (ep->urb_list);

    list_now = list_start->next;

    while(list_now != list_start ){
        int tmp;
        urb = (struct urb *)(list_now->data);
        if(!urb){
            hal_log_err("PANIC : hcd_ops_endpoint_disable() : urb = NULL");
        }
        // another cpu may be in hcd, spinning on hcd_data_lock
        // to giveback() this urb.  the races here should be
        // small, but a full fix needs a new "can't submit"
        // urb state.
        // FIXME urb->reject should allow that...

        if (urb->status != -EINPROGRESS){
            continue;
        }

        hal_spin_lock_irqsave (urb->lock_urb);
        tmp = urb->status;
        if (tmp == -EINPROGRESS){
            urb->status = -ESHUTDOWN;
        }
        hal_spin_unlock_irqrestore (urb->lock_urb);
        // kick hcd unless it's already returning this//
        if (tmp == -EINPROGRESS) {
            tmp = urb->pipe;
            unlink1 (hcd, urb);
            hal_log_info ("shutdown urb %p pipe %x ep%d%s",
                urb, tmp, usb_pipeendpoint (tmp),
                (tmp & USB_DIR_IN) ? "in" : "out");
        }

        //list contents may have changed //
        goto rescan;
    }
    hal_spin_unlock_irqrestore(flags);

    //synchronize with the hardware, so old configuration state
    // clears out immediately (and will be freed).
    //
//  might_sleep ();
    if (hcd->driver->endpoint_disable){
        hcd->driver->endpoint_disable (hcd, ep);
    }
}
*/
int usb_hcd_link_urb_to_ep(struct hc_gen_dev *hcd, struct urb *urb)
{
    int rc = 0;
    int flags;

    flags = hal_spin_lock_irqsave(&gen_hcd_lock);

    if (HC_GEN_DEV_IS_RUNNING(hcd->state))
    {
        list_add_tail(&(urb->urb_list), &(urb->ep->urb_list));
    }
    else
    {
        rc = -1;
    }

    hal_spin_unlock_irqrestore(&gen_hcd_lock, flags);

    return rc;
}

void usb_hcd_unlink_urb_from_ep(struct hc_gen_dev *hcd, struct urb *urb)
{
    int flags;

    flags = hal_spin_lock_irqsave(&gen_hcd_lock);
    list_del_init(&(urb->urb_list));
    hal_spin_unlock_irqrestore(&gen_hcd_lock, flags);
}

int usb_hcd_check_unlink_urb(struct hc_gen_dev *hcd, struct urb *urb)
{
    struct list_head    *tmp;

    /* insist the urb is still queued */
    list_for_each(tmp, &urb->ep->urb_list) {
        if (tmp == &urb->urb_list)
            break;
    }
    if (tmp != &urb->urb_list)
        return -EIDRM;

    /* Any status except -EINPROGRESS means something already started to
     * unlink this URB from the hardware.  So there's no more work to do.
     */
    if (urb->unlinked)
        return -EBUSY;
    urb->unlinked = urb->status;
    return 0;
}


#ifdef  CONFIG_USB_SUSPEND

static int hcd_ops_hub_suspend(struct usb_bus *bus)
{
    struct usb_hcd      *hcd;
    hcd = container_of(bus, struct usb_hcd, self);

    if (hcd->driver->hub_suspend)
    {
        return hcd->driver->hub_suspend(hcd);
    }

    return 0;
}

static int hcd_ops_hub_resume(struct usb_bus *bus)
{
    struct usb_hcd      *hcd;
    hcd = container_of(bus, struct usb_hcd, self);

    if (hcd->driver->hub_resume)
    {
        return hcd->driver->hub_resume(hcd);
    }

    return 0;
}
#endif

/**
 * usb_hub_clear_tt_buffer - clear control/bulk TT state in high speed hub
 * @urb: an URB associated with the failed or incomplete split transaction
 *
 * High speed HCDs use this to tell the hub driver that some split control or
 * bulk transaction failed in a way that requires clearing internal state of
 * a transaction translator.  This is normally detected (and reported) from
 * interrupt context.
 *
 * It may not be possible for that hub to handle additional full (or low)
 * speed transactions until that state is fully cleared out.
 *
 * Return: 0 if successful. A negative error code otherwise.
 */
// int usb_hub_clear_tt_buffer(struct urb *urb)
// {
//  //struct usb_device *udev = urb->dev;
//  struct usb_host_virt_dev    *udev = urb->dev;
//  int         pipe = urb->pipe;
//  struct usb_tt       *tt = udev->tt;
//  unsigned long       flags;
//  struct usb_tt_clear *clear;

//  /* we've got to cope with an arbitrary number of pending TT clears,
//   * since each TT has "at least two" buffers that can need it (and
//   * there can be many TTs per hub).  even if they're uncommon.
//   */
//  clear = hal_malloc(sizeof *clear);
//  if (clear == NULL) {
//      hal_log_err("can't save CLEAR_TT_BUFFER state\n");
//      /* FIXME recover somehow ... RESET_TT? */
//      return -ENOMEM;
//  }

//  /* info that CLEAR_TT_BUFFER needs */
//  clear->tt = tt->multi ? udev->ttport : 1;
//  clear->devinfo = usb_pipeendpoint (pipe);
//  clear->devinfo |= udev->devnum << 4;
//  clear->devinfo |= usb_pipecontrol(pipe)
//          ? (USB_ENDPOINT_XFER_CONTROL << 11)
//          : (USB_ENDPOINT_XFER_BULK << 11);
//  if (usb_pipein(pipe))
//      clear->devinfo |= 1 << 15;

//  /* info for completion callback */
//  clear->hcd = bus_to_hcd(udev->bus);
//  clear->ep = urb->ep;

//  /* tell keventd to clear state for this TT */
//  flags = hal_spin_lock_irqsave(&tt->lock);
//  list_add_tail(&clear->clear_list, &tt->clear_list);
//  // schedule_work(&tt->clear_work);//akira
//  hal_spin_unlock_irqrestore(&tt->lock, flags);
//  return 0;
// }

void usb_gen_hcd_init(void)
{
    usb_bus_list_lock = hal_sem_create(1);
}

void usb_gen_hcd_exit(void)
{
    hal_sem_delete(usb_bus_list_lock);
    usb_bus_list_lock = NULL;
}
